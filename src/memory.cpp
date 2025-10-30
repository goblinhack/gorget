//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_globals.hpp"
#include "my_main.hpp"
#include "my_ptrcheck.hpp"

#include <string.h>

void *myzalloc_(int size, const char *what, const char *file, const char *func, int line)
{
  TRACE_NO_INDENT();

  void *ptr = calloc(1, size);

  if (unlikely(! ptr)) {
    DIE("No memory, %s:%s:%u, size %u", file, func, line, size);
  }

  IF_DEBUG2 { ptrcheck_alloc(MTYPE_MISC, ptr, what, size, file, func, line); }

  // callstack_dump();
  g_memory_allocated++;

  return ptr;
}

void *mymalloc_(int size, const char *what, const char *file, const char *func, int line)
{
  TRACE_NO_INDENT();

  void *ptr = malloc(size);

  if (unlikely(! ptr)) {
    DIE("No memory, %s:%s:%u", file, func, line);
  }

  IF_DEBUG2 { ptrcheck_alloc(MTYPE_MISC, ptr, what, size, file, func, line); }

  // callstack_dump();
  g_memory_allocated++;

  return ptr;
}

void *myrealloc_(void *ptr, int size, const char *what, const char *file, const char *func, int line)
{
  TRACE_NO_INDENT();
  IF_DEBUG2 { ptrcheck_free(MTYPE_MISC, ptr, file, func, line); }

  ptr = realloc(ptr, size);
  if (unlikely(! ptr)) {
    DIE("No memory, %s:%s:%u", file, func, line);
  }

  IF_DEBUG2 { ptrcheck_alloc(MTYPE_MISC, ptr, what, size, file, func, line); }

  // callstack_dump();
  g_memory_allocated++;

  return ptr;
}

void myfree_(void *ptr, const char *file, const char *func, int line)
{
  TRACE_NO_INDENT();

  IF_DEBUG2 { ptrcheck_free(MTYPE_MISC, ptr, file, func, line); }

  // callstack_dump();
  g_memory_allocated++;

  free(ptr);
}

char *mydupstr_(const char *in, const char *what, const char *file, const char *func, int line)
{
  TRACE_NO_INDENT();

  if (unlikely(! in)) {
    ERR("No string to duplicate");
    return nullptr;
  }

  char *ptr = strdup(in);
  if (unlikely(! ptr)) {
    DIE("No memory, %s:%s:%u", file, func, line);
  }

  IF_DEBUG2
  {
    int size = (__typeof__(size)) strlen(in);

    ptrcheck_alloc(MTYPE_MISC, ptr, what, size, file, func, line);
  }

  // callstack_dump();
  g_memory_allocated++;

  return ptr;
}
