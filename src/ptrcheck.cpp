//
// Copyright goblinhack@gmail.com
//

#include "my_backtrace.hpp"
#include "my_callstack.hpp"
#include "my_globals.hpp"
#include "my_main.hpp"
#include "my_ptrcheck.hpp"
#include "my_sprintf.hpp"
#include "my_time.hpp"

#include <iostream>
#include <mutex>
#include <string.h>
#include <vector>

static std::mutex ptrcheck_mutex;

class Ptrcheck_history;
static std::vector< class Ptrcheck_history * > all_Ptrcheck_history {};

//
// A single event in the life of a pointer.
//
class Ptrcheck_history
{
public:
  const char *file {};
  const char *func {};
  char        ts[ MY_TIMESTAMP_SIZE ];
  int         line {};
  std::string bt;

  Ptrcheck_history()
  {
    ts[ 0 ] = '\0';
    all_Ptrcheck_history.push_back(this);
  }
  Ptrcheck_history(const Ptrcheck_history &other)
  {
    all_Ptrcheck_history.push_back(this);
    file = other.file;
    func = other.func;
    line = other.line;
    strcpy(ts, other.ts);
    bt = other.bt;
  }
  ~Ptrcheck_history() {}
};

//
// The life of a single pointer.
//
class Ptrcheck
{
public:
  Ptrcheck(void) = default;

  //
  // For sanity, the pointer itself.
  //
  void *ptr {};

  //
  // The type of memory.
  //
  const char *what;

  //
  // How much memory it is using.
  //
  int size {};

  //
  // Where did the pointer get allocated/freed/last_seen from?
  //
  Ptrcheck_history *allocated_by {};
  Ptrcheck_history *freed_by {};
#ifdef ENABLE_PTRCHECK_HISTORY
  std::array< Ptrcheck_history *, ENABLE_PTRCHECK_HISTORY > last_seen {};
#endif

  //
  // Where in the history buffer we are.
  //
  int last_seen_at {};
  int last_seen_size {};
};

#ifndef CROAK
static void die(void)
{
  std::cerr << "exit(1) error" << std::endl;
  exit(1);
}

static void cleanup_wrapper_(const char *fmt, va_list args)
{
  auto err = "\n" + timestamp();
  err += ": PTRCHECK: FATAL ERROR: ";
  err += string_sprintf(fmt, args);
  std::cerr << err << std::endl;
  die();
}

void CLEANUP(const char *fmt, ...)
{
  va_list args;
  va_start(args, fmt);
  cleanup_wrapper_(fmt, args);
  va_end(args);
}

static void error_(const char *fmt, va_list args)
{
  auto err = timestamp();
  err += ": PTRCHECK: ERROR: ";
  err += string_sprintf(fmt, args);
  std::cerr << err << std::endl;
}

void ERROR(const char *fmt, ...) CHECK_FORMAT_STR(printf, 1, 2);
void ERROR(const char *fmt, ...)
{
  va_list args;
  va_start(args, fmt);
  error_(fmt, args);
  va_end(args);
}

#define CROAK(args...)                                                                                               \
  std::cerr << string_sprintf("Died at %s:%s line %u", SRC_FILE_NAME, SRC_FUNC_NAME, SRC_LINE_NUM);                  \
  CLEANUP(args);

#define ERR(args...)                                                                                                 \
  std::cerr << string_sprintf("Error at %s:%s line %u", SRC_FILE_NAME, SRC_FUNC_NAME, SRC_LINE_NUM);                 \
  ERROR(args);

#endif

//
// A hash table so we can check pointers fast.
//
typedef struct hash_elem_t_ {
  struct hash_elem_t_ *next;
  Ptrcheck            *pc;
} hash_elem_t;

typedef struct hash_t_ {
  int           hash_size;
  hash_elem_t **elements;
} hash_t;

static hash_t *ptrcheck_hash[ MTYPE_MAX ];

//
// How many old/freed pointers do we keep track of. We use this when we find
// an unknown pointer to find when it last lived.
//
static const int                                      ringbuf_max_size = 100000;
static int                                            ringbuf_current_size[ MTYPE_MAX ];
static std::array< class Ptrcheck, ringbuf_max_size > ringbuf[ MTYPE_MAX ];
static Ptrcheck                                      *ringbuf_next[ MTYPE_MAX ];
static Ptrcheck                                      *ringbuf_base[ MTYPE_MAX ];

//
// Wrapper for calloc.
//
static void *local_zalloc(int size)
{
  void *p;
  p = calloc(1, size);
  return p;
}

//
// World a pointer to a hash slot.
//
static hash_elem_t **ptr2hash(hash_t *hash_table, void *ptr)
{
  int slot;

  //
  // Knock lower 2 bits off of pointer - these are always 0.
  //
  slot = (int) ((((uintptr_t) (ptr)) >> 2) % hash_table->hash_size);

  return &hash_table->elements[ slot ];
}

//
// Create a hash table for all pointers.
//
static hash_t *hash_init(int hash_size)
{
  hash_t *hash_table;

  hash_table = (__typeof__(hash_table)) local_zalloc(SIZEOF(hash_t));

  hash_table->hash_size = hash_size;

  hash_table->elements = (__typeof__(hash_table->elements)) local_zalloc(hash_size * SIZEOF(hash_elem_t *));

  return hash_table;
}

//
// Store a pointer in our hash.
//
static void hash_add(hash_t *hash_table, Ptrcheck *pc)
{
  hash_elem_t **slot;
  hash_elem_t  *elem;

  if (! g_ptrcheck_inited) {
    if (g_memory_allocated > 0) {
      CROAK("memory has already been allocated prior to invoking ptrcheck (%d times)", g_memory_allocated);
    }
    g_ptrcheck_inited = true;
  }

  if (! pc) {
    return;
  }

  if (! hash_table) {
    delete pc;
    return;
  }

  slot = ptr2hash(hash_table, pc->ptr);
  elem = *slot;
  while (elem && (elem->pc->ptr != pc->ptr)) {
    elem = elem->next;
  }

  if (elem != nullptr) {
    delete pc;
    return;
  }

  elem       = (__typeof__(elem)) local_zalloc(SIZEOF(*elem));
  elem->pc   = pc;
  elem->next = *slot;
  *slot      = elem;
}

//
// Find a pointer in our hash.
//
static hash_elem_t *hash_find(hash_t *hash_table, void *ptr)
{
  hash_elem_t **slot;
  hash_elem_t  *elem;

  if (! hash_table) {
    return nullptr;
  }

  slot = ptr2hash(hash_table, ptr);
  elem = *slot;
  while (elem && (elem->pc->ptr != ptr)) {
    elem = elem->next;
  }

  return elem;
}

//
// Free a pointer from our hash.
//
static void hash_free(hash_t *hash_table, void *ptr)
{
  hash_elem_t **slot;
  hash_elem_t  *prev;
  hash_elem_t  *elem;

  if (! hash_table) {
    return;
  }

  if (! ptr) {
    return;
  }

  slot = ptr2hash(hash_table, ptr);
  elem = *slot;
  prev = nullptr;

  while (elem && (elem->pc->ptr != ptr)) {
    prev = elem;
    elem = elem->next;
  }

  if (! elem) {
    return;
  }

  if (prev) {
    prev->next = elem->next;
  } else {
    *slot = elem->next;
  }

  delete elem->pc;
  free(elem);
}

static Ptrcheck *ptrcheck_describe_pointer(int mtype, const void *ptr)
{
  int ring_ptr_size;

  //
  // Currently active pointer?
  //
  auto elem = hash_find(ptrcheck_hash[ mtype ], (void *) ptr);
  if (elem) {
    auto pc = elem->pc;

    auto a = pc->allocated_by;
    if (a) {
      fprintf(stderr, "PTRCHECK: Currently allocated at %p \"%s\" (%u bytes) at %s:%s line %u at %s\n", pc->ptr,
              pc->what, pc->size, a->file, a->func, a->line, a->ts);

      fprintf(stderr, "%s", a->bt.c_str());
    }

    //
    // Dump the pointer history.
    //
#ifdef ENABLE_PTRCHECK_HISTORY
    int h = pc->last_seen_at;
    for (auto j = 0; j < pc->last_seen_size; j++) {
      if (--h < 0) {
        h = ENABLE_PTRCHECK_HISTORY - 1;
      }

      auto H = pc->last_seen[ h ];
      if (H) {
        fprintf(stderr, "PTRCHECK: Last seen at [%u] at %s:%s line %u at %s\n", j, H->file, H->func, H->line, H->ts);
        fprintf(stderr, "%s", H->bt.c_str());
      }
    }
#endif
  }

  //
  // Check the ring buffer to see if we've seen this pointer before.
  //
  auto pc = &ringbuf_next[ mtype ][ 0 ];
  pc--;

  if (pc < ringbuf_base[ mtype ]) {
    pc = ringbuf_base[ mtype ] + ringbuf_max_size - 1;
  }

  ring_ptr_size = ringbuf_current_size[ mtype ];

  fprintf(stderr, "vvvvv Pointer history for %p vvvvv (max %u ptrs saved)", ptr, ring_ptr_size);

  //
  // Walk back through the ring buffer.
  //
  while (ring_ptr_size) {
    //
    // Found a match?
    //
    if (pc->ptr == ptr) {
      auto a = pc->allocated_by;
      if (a) {
        fprintf(stderr, "PTRCHECK: %p allocated at \"%s\" (%u bytes) at %s:%s line %u at %s\n%s\n", ptr, pc->what,
                pc->size, a->file, a->func, a->line, a->ts, a->bt.c_str());
      }

      auto f = pc->freed_by;
      if (f) {
        fprintf(stderr, "PTRCHECK: %p freed at %s:%s line %u at %s\n%s\n", ptr, f->file, f->func, f->line, f->ts,
                f->bt.c_str());
      }

      //
      // Dump the pointer history.
      //
#ifdef ENABLE_PTRCHECK_HISTORY
      int h = pc->last_seen_at;
      for (auto i = 0; i < pc->last_seen_size; i++) {
        if (--h < 0) {
          h = ENABLE_PTRCHECK_HISTORY - 1;
        }

        auto H = pc->last_seen[ h ];
        if (H) {
          fprintf(stderr, "PTRCHECK: %p last seen at [%u] at %s:%s line %u at %s\n%s\n", ptr, i, H->file, H->func,
                  H->line, H->ts, H->bt.c_str());
        }
      }
#endif
      //
      // Memory reuse can cause a lot of false hits, so stop after
      // the first match.
      //
      break;
    }

    ring_ptr_size--;
    pc--;

    //
    // Handle wraps.
    //
    if (pc < ringbuf_base[ mtype ]) {
      pc = ringbuf_base[ mtype ] + ringbuf_max_size - 1;
    }
  }

  fprintf(stderr, "^^^^^ End of pointer history for %p ^^^^^", ptr);
  return nullptr;
}

//
// Check a pointer for validity.
//
static Ptrcheck *ptrcheck_verify_pointer(int mtype, const void *ptr, const char *func, const char *file, int line,
                                         int dont_store)
{
  static const char *unknown_ptr_warning  = "** UNKNOWN POINTER ** ";
  static const char *null_pointer_warning = "** NULL POINTER ** ";
  Ptrcheck          *pc;
  hash_elem_t       *e;

  //
  // Check the robust handle is valid.
  //
  e = hash_find(ptrcheck_hash[ mtype ], (void *) ptr);
  if (e) {
    pc = e->pc;

    if (dont_store) {
#if 0
#ifdef ENABLE_DEBUG_PTRCHECK
      std::cerr << string_sprintf("PTRCHECK: %p verified at \"%s\" (%u bytes) at %s:%s line %u (do not store)\n", ptr,
                                  pc->what, pc->size, file, func, line);
#endif
#endif
      return pc;
    }

    //
    // Add some free information that we know the pointer is safe at this
    // point in time.
    //
#ifdef ENABLE_PTRCHECK_HISTORY
    IF_DEBUG
    {
      auto l = pc->last_seen[ pc->last_seen_at ];
      if (! l) {
        l = pc->last_seen[ pc->last_seen_at ] = new Ptrcheck_history();
      }
      l->file = file;
      l->func = func;
      l->line = line;

      l->bt = callstack_string();
      timestamp(l->ts, SIZEOF(l->ts));

#ifdef ENABLE_DEBUG_PTRCHECK
      std::cerr << string_sprintf("PTRCHECK: %p verified at \"%s\" (%u bytes) at %s:%s line %u at %s\n", ptr,
                                  pc->what, pc->size, file, func, line, l->ts);
#endif

      pc->last_seen_at++;
      pc->last_seen_size++;

      if (pc->last_seen_at >= ENABLE_PTRCHECK_HISTORY) {
        pc->last_seen_at = 0;
      }

      if (pc->last_seen_size >= ENABLE_PTRCHECK_HISTORY) {
        pc->last_seen_size = ENABLE_PTRCHECK_HISTORY;
      }
    }
#endif
    return pc;
  }
  if (! ptr) {
    ERR("%s%p NULL pointer %s:%s line %u", null_pointer_warning, ptr, file, func, line);
    return nullptr;
  }

  //
  // We may be about to crash. Complain!
  //
  fprintf(stderr, "%s%p %s:%s line %u, see below logs", unknown_ptr_warning, ptr, file, func, line);
  ptrcheck_describe_pointer(mtype, ptr);
  CROAK("%s%p %s:%s line %u, see above logs", unknown_ptr_warning, ptr, file, func, line);
  return nullptr;
}

//
// Record this pointer.
//
static void *ptrcheck_alloc_(int mtype, const void *ptr, const char *what, int size, const char *func,
                             const char *file, int line)
{
  Ptrcheck *pc;

#ifdef ENABLE_DEBUG_PTRCHECK
  char tmp[ MY_TIMESTAMP_SIZE ];
  auto ts = timestamp(tmp, SIZEOF(tmp));
  fprintf(stderr, "%s: PTRCHECK: Alloc %p \"%s\" (%u bytes) at %s:%s line %u\n", ts, ptr, what, size, file, func,
          line);
#endif

  if (! ptr) {
    ERR("Null pointer");
  }

  //
  // Create a hash table to store pointers.
  //
  if (! ptrcheck_hash[ mtype ]) {
    //
    // Create enough space for lots of pointers.
    //
    ptrcheck_hash[ mtype ] = hash_init(1046527 /* prime */);

    if (! ptrcheck_hash[ mtype ]) {
      return (void *) ptr;
    }

    //
    // And a ring buffer to store old pointer into.
    //
    ringbuf_next[ mtype ]         = &ringbuf[ mtype ][ 0 ];
    ringbuf_base[ mtype ]         = &ringbuf[ mtype ][ 0 ];
    ringbuf_current_size[ mtype ] = 0;
  }

  //
  // Missing an earlier free?
  //
  if (hash_find(ptrcheck_hash[ mtype ], (void *) ptr)) {
    ERR("Pointer %p already exists and attempting to add again", ptr);
    ptrcheck_describe_pointer(mtype, ptr);
    return (void *) ptr;
  }

  //
  // Allocate a block of data to describe the pointer and owner.
  //
  pc = new Ptrcheck();

  //
  // Populate the data block.
  //
  pc->ptr  = (void *) ptr;
  pc->what = what;
  pc->size = size;

  auto a = pc->allocated_by = new Ptrcheck_history();

  a->func = func;
  a->file = file;
  a->line = line;
  timestamp(a->ts, SIZEOF(a->ts));
  a->bt = callstack_string();

  //
  // Add it to the hash. Not the ring buffer (only when freed).
  //
  hash_add(ptrcheck_hash[ mtype ], pc);

  return (void *) ptr;
}

void *ptrcheck_alloc(int mtype, const void *ptr, const char *what, int size, const char *func, const char *file,
                     int line)
{
  ptrcheck_mutex.lock();
  TRACE_NO_INDENT();
  auto ret = ptrcheck_alloc_(mtype, ptr, what, size, func, file, line);
  ptrcheck_mutex.unlock();

  return ret;
}

//
// Check a pointer is valid and if so add it to the ring buffer. If not,
// return false and avert the myfree(), just in case.
//
static int ptrcheck_free_(int mtype, void *ptr, const char *func, const char *file, int line)
{
  Ptrcheck *pc;

#ifdef ENABLE_DEBUG_PTRCHECK
  char tmp[ MY_TIMESTAMP_SIZE ];
  auto ts = timestamp(tmp, SIZEOF(tmp));
  fprintf(stderr, "%s: PTRCHECK: Free %p at %s:%s line %u ringbuf_current_size %u\n", ts, ptr, file, func, line,
          ringbuf_current_size[ mtype ]);
#endif

  if (! ptr) {
    ERR("Null pointer");
    return false;
  }

  pc = ptrcheck_verify_pointer(mtype, ptr, file, func, line, true /* don't store */);
  if (! pc) {
    CROAK("Failed to save pointer history");
    return false;
  }

  //
  // Add some free information that we know the pointer is safe at this
  // point in time.
  //
  auto f = pc->freed_by = new Ptrcheck_history();

  f->file = file;
  f->func = func;
  f->line = line;
  f->bt   = callstack_string();
  timestamp(f->ts, SIZEOF(f->ts));

  //
  // Add the free info to the ring buffer.
  //
  *ringbuf_next[ mtype ] = *pc;

  //
  // Take care of wraps.
  //
  ringbuf_next[ mtype ]++;
  if (ringbuf_next[ mtype ] >= ringbuf_base[ mtype ] + ringbuf_max_size) {
    ringbuf_next[ mtype ] = ringbuf_base[ mtype ];
  }

  //
  // Increment the ring buffer used size up to the limit.
  //
  if (ringbuf_current_size[ mtype ] < ringbuf_max_size) {
    ringbuf_current_size[ mtype ]++;
  }

  hash_free(ptrcheck_hash[ mtype ], ptr);

  return true;
}

int ptrcheck_free(int mtype, void *ptr, const char *func, const char *file, int line)
{
  ptrcheck_mutex.lock();
  TRACE_NO_INDENT();
  auto ret = ptrcheck_free_(mtype, ptr, func, file, line);
  ptrcheck_mutex.unlock();

  return ret;
}

//
// Check a pointer for validity with no recording of history.
//
int ptrcheck_verify(int mtype, const void *ptr, const char *func, const char *file, int line)
{
  ptrcheck_mutex.lock();
  TRACE_NO_INDENT();

  //
  // Handy if things get too slow, to see what is firing most
  //
  // fprintf(stderr, "PTRCHECK %s %s %d\n", file, func, line);
  auto ret = ptrcheck_verify_pointer(mtype, ptr, file, func, line, false /* don't store */) != nullptr;

  ptrcheck_mutex.unlock();

  return ret;
}

//
// Show any leaks
//
void ptrcheck_leak_print(int mtype)
{
  hash_elem_t **slot;
  hash_elem_t  *elem;
  Ptrcheck     *pc;
  int           i;

  if (! ptrcheck_hash[ mtype ]) {
    return;
  }

  for (i = 0; i < ptrcheck_hash[ mtype ]->hash_size; i++) {
    slot = &ptrcheck_hash[ mtype ]->elements[ i ];
    elem = *slot;

    while (elem) {
      pc = elem->pc;

      auto a = pc->allocated_by;
      if (a) {
        fprintf(stderr, "PTRCHECK: Leak %p \"%s\" (%u bytes) at %s:%s line %u at %s\n%s\n", pc->ptr, pc->what,
                pc->size, a->file, a->func, a->line, a->ts, a->bt.c_str());
      } else {
        fprintf(stderr, "PTRCHECK: Leak \"%s\" (%u bytes)\n", pc->what, pc->size);
      }

      //
      // Dump the pointer history.
      //
#ifdef ENABLE_PTRCHECK_HISTORY
      int h = pc->last_seen_at;
      for (auto j = 0; j < pc->last_seen_size; j++) {
        if (--h < 0) {
          h = ENABLE_PTRCHECK_HISTORY - 1;
        }

        auto H = pc->last_seen[ h ];
        if (H) {
          fprintf(stderr, "PTRCHECK: Last seen at [%u] at %s:%s line %u at %s\n%s\n", j, H->file, H->func, H->line,
                  H->ts, H->bt.c_str());
        }
      }
#endif
      if (elem->next == elem) {
        ERR("Hash table corruption");
      }

      elem = elem->next;
    }
  }
}

void ptrcheck_leak_print(void)
{
  for (int mtype = 0; mtype < MTYPE_MAX; mtype++) {
    ptrcheck_leak_print(mtype);
  }
}

static void ptrcheck_fini(int mtype)
{
  hash_elem_t **slot;
  hash_elem_t  *elem;
  int           i;

  if (! ptrcheck_hash[ mtype ]) {
    return;
  }

  for (auto p : all_Ptrcheck_history) {
    delete p;
  }
  all_Ptrcheck_history.clear();

  for (i = 0; i < ptrcheck_hash[ mtype ]->hash_size; i++) {
    slot = &ptrcheck_hash[ mtype ]->elements[ i ];
    elem = *slot;

    while (elem) {
      auto next = elem->next;
      delete elem->pc;
      free(elem);
      elem = next;
    }
  }

  free(ptrcheck_hash[ mtype ]->elements);
  free(ptrcheck_hash[ mtype ]);

  ptrcheck_hash[ mtype ] = nullptr;
}

void ptrcheck_fini(void)
{
  for (int mtype = 0; mtype < MTYPE_MAX; mtype++) {
    ptrcheck_fini(mtype);
  }
}
