//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_main.hpp"
#include "my_random.hpp"
#include "my_thing_inlines.hpp"

#include <cstring>
#include <iostream>
#include <mutex>

static std::mutex thing_mutex;

#ifdef ENABLE_PER_THING_MEMORY
static bool memory_test = true;
#endif

[[nodiscard]] static bool thing_ext_alloc(Levelsp v, Thingp t)
{
  TRACE_NO_INDENT();

  static uint32_t last_ext_id;

  //
  // Continue from the last successful allocation
  //
  thing_mutex.lock();
  for (auto tries = 0; tries < THING_EXT_MAX; tries++) {
    ThingExtId ext_id = last_ext_id + tries;
    ext_id %= THING_EXT_MAX;
    if (unlikely(! ext_id)) {
      continue;
    }

    if (unlikely(v->thing_ext[ ext_id ].in_use)) {
      continue;
    }

    v->thing_ext[ ext_id ].in_use = true;
    v->thing_ext_count++;
    t->ext_id   = ext_id;
    last_ext_id = ext_id;

    thing_mutex.unlock();
    return true;
  }

  thing_mutex.unlock();
  CROAK("out of Thing ext IDs: max is %d", THING_EXT_MAX);

  return false;
}

static void thing_ext_free(Levelsp v, Thingp t)
{
  TRACE_NO_INDENT();

  auto ext_id = t->ext_id;
  if (ext_id == 0U) {
    return;
  }

  if (! v->thing_ext[ ext_id ].in_use) {
    ERR("freeing unused Thing ext ID is not in use, %" PRIX32 "", ext_id);
  }

  v->thing_ext[ ext_id ].in_use = false;
  v->thing_ext_count--;
  if (v->thing_ext_count < 0) {
    CROAK("bad thing_ext count");
  }

  t->ext_id = 0;
}

[[nodiscard]] static bool thing_fov_alloc(Levelsp v, Thingp t)
{
  TRACE_NO_INDENT();

  static uint32_t last_fov_id;

  //
  // Continue from the last successful allocation
  //
  thing_mutex.lock();
  for (auto tries = 0; tries < THING_FOV_MAX; tries++) {
    ThingFovId fov_id = last_fov_id + tries;
    fov_id %= THING_FOV_MAX;
    if (unlikely(! fov_id)) {
      continue;
    }

    if (unlikely(v->thing_fov[ fov_id ].in_use)) {
      continue;
    }

    v->thing_fov[ fov_id ].in_use = true;
    v->thing_fov_count++;
    t->fov_id   = fov_id;
    last_fov_id = fov_id;

    thing_mutex.unlock();
    return true;
  }

  thing_mutex.unlock();
  CROAK("out of Thing fov IDs: max is %d", THING_FOV_MAX);

  return false;
}

static void thing_fov_free(Levelsp v, Thingp t)
{
  TRACE_NO_INDENT();

  auto fov_id = t->fov_id;
  if (fov_id == 0U) {
    return;
  }

  if (! v->thing_fov[ fov_id ].in_use) {
    ERR("freeing unused Thing fov ID is not in use, %" PRIX32 "", fov_id);
  }

  v->thing_fov[ fov_id ].in_use = false;
  v->thing_fov_count--;
  if (v->thing_fov_count < 0) {
    CROAK("bad thing_fov count");
  }

  t->fov_id = 0;
}

static Thingp thing_alloc_do(Gamep g, Levelsp v, Levelp l, Tpp tp, ThingIdPacked id, bool needs_ext_memory,
                             bool needs_fov_memory, bool need_mutex)
{
  TRACE_NO_INDENT();

  const auto tp_id = tp_id_get(tp);

  //
  // Use the full range of IDs. If we can, we will use part of this as the level as
  // it allows threads to avoid mutexes.
  //
  // Intentionally using OS rand here, as if we had a conflict with another thread
  // we would end up with multiple rand calls - and that would make level gen inconsistent
  // across seeds.
  //

  //
  // Check if there is anything at this index
  //
  auto  arr_index = id.c.arr_index;
  auto *t         = &v->thing_body[ arr_index ];
  if (unlikely(t->tp_id)) {
    //
    // Some other thread grabbed it already?
    //
    return nullptr;
  }

  //
  // If we need a mutex, lock the thing population for this slot
  //
  if (unlikely(need_mutex)) {
    thing_mutex.lock();

    //
    // Just in case someone else grabbed it while locking...
    //
    if (unlikely(t->tp_id)) {
      thing_mutex.unlock();
      return nullptr;
    }

    //
    // We safely have this slot
    //
    t->tp_id = tp_id;
    thing_mutex.unlock();
  } else {
    //
    // No need to worry about other threads
    //
    if (unlikely(t->tp_id)) {
      return nullptr;
    }

    t->tp_id = tp_id;
  }

  //
  // Zero the thing out. TAKE CARE not to zero tp_id
  //
  memset((char *) t + SIZEOF(t->tp_id), 0, SIZEOF(*t) - SIZEOF(t->tp_id));

  //
  // Create the final ID with some rando entropy
  //
  static uint16_t entropy;
  entropy++;
  if (entropy == 0U) {
    entropy++;
  }
  id.c.entropy = ++entropy;

  //
  // The thing has the full ID, including entropy
  //
  t->id = id.a.val;

  if (compiler_unused) {
    LOG("Thing alloc %08" PRIX32 //
        " (level: %" PRIu32      //
        " id: %08" PRIX32        //
        " entropy: %08" PRIX32   //
        ")",                     //
        t->id,                   //
        id.b.level_num,          //
        id.b.per_level_id,       //
        id.b.entropy);
  }

  if (needs_ext_memory) {
    if (! thing_ext_alloc(v, t)) {
      thing_free(g, v, l, t);
      return nullptr;
    }
  }

  if (needs_fov_memory) {
    if (! thing_fov_alloc(v, t)) {
      thing_free(g, v, l, t);
      return nullptr;
    }
  }

#ifdef ENABLE_PER_THING_MEMORY
  if (memory_test) {
    auto tmp = malloc(sizeof(*t));
    memcpy(tmp, t, sizeof(*t));
    t                                = (Thingp) tmp;
    v->thing_body_debug[ arr_index ] = t;
  }
#endif

  return t;
}

Thingp thing_alloc(Gamep g, Levelsp v, Levelp l, Tpp tp, spoint p)
{
  TRACE_NO_INDENT();

  if (unlikely(! tp)) {
    CROAK("no template set for thing allocation");
  }

  //
  // Check we cannot overflow on monsters
  //
  // Light source need to avoid foving the same cell more than once, hence their presence.
  //
  auto needs_ext_memory = tp_is_mob(tp) || tp_is_monst(tp) || tp_is_player(tp);
  if (needs_ext_memory) {
    if (v->thing_ext_count >= THING_EXT_MAX - 1) {
      TP_LOG(tp, "out of ext thing memory");
      return nullptr;
    }
  }

  auto needs_fov_memory = tp_is_light_source(tp) || tp_is_player(tp) || (tp_distance_vision_get(tp) != 0);
  if (needs_fov_memory) {
    if (v->thing_fov_count >= THING_FOV_MAX - 1) {
      TP_LOG(tp, "out of fov thing memory");
      return nullptr;
    }
  }

  //
  // The level select level doesn't have a dedicated bit slot so just use a level that
  // is not initialized
  //
  auto level_num = l->level_num;
  if (level_num == LEVEL_SELECT_ID) {
    if (v->is_generating_levels) {
      CROAK("cannot allocate level select while mutexes are off");
    }

    for (auto i = 0; i < LEVEL_MAX; i++) {
      if (! v->level[ i ].is_initialized) {
        level_num = i;
        break;
      }
    }
  }

  static uint32_t last_per_level_id[ LEVEL_MAX ];

  //
  // Sequentially try to allocate an ID from the last ID allocated.
  // Use the level_num as scoping so that we do not need to use a mutex as different
  // levels will allocate from different regions of the array.
  //
  for (uint32_t tries = 0; tries < (1 << THING_PER_LEVEL_THING_ID_BITS); tries++) {
    uint32_t per_level_id = tries + last_per_level_id[ level_num ] + 1;
    if (per_level_id == 0U) {
      per_level_id = 1;
    }

    ThingIdPacked id  = {};
    id.b.level_num    = level_num;
    id.b.per_level_id = per_level_id;

    auto *t = thing_alloc_do(g, v, l, tp, id, needs_ext_memory, needs_fov_memory, false /* mutex */);
    if (t != nullptr) {
      last_per_level_id[ level_num ] = per_level_id;
      return t;
    }
  }

  //
  // If we hit this, it turns out we should have been using mutexes. We have no idea
  // if this will collide with something else not using a mutex.
  //
  if (v->is_generating_levels) {
    CROAK("ran out of thing IDs while doing multi threaded level gen");
  }

  //
  // Last resort, allocate from the end backwards.
  //
  static uint32_t last_arr_index = THING_ID_MAX - 1;
  for (uint32_t arr_index = last_arr_index - 1; arr_index > 0; arr_index--) {
    ThingIdPacked id = {};
    id.c.arr_index   = arr_index;

    auto *t = thing_alloc_do(g, v, l, tp, id, needs_ext_memory, needs_fov_memory, true /* mutex */);
    if (t != nullptr) {
      last_arr_index = arr_index;
      return t;
    }
  }

  CROAK("out of Thing IDs: max is %d", THING_ID_MAX);
  return nullptr;
}

void thing_free(Gamep g, Levelsp v, Levelp l, Thingp t)
{
  TRACE_NO_INDENT();

  auto *o = thing_find(g, v, t->id);
  if (t != o) {
    CROAK("Thing mismatch found for id, %p %08" PRIX32 "", (void *) t, t->id);
  }

  auto *tp = thing_tp(t);

  //
  // Clean up references
  //
  if (tp_is_player(tp)) {
    v->player_id = 0;
  }

  if (tp_is_level_curr(tp)) {
    v->level_select_id = 0;
  }

  if (compiler_unused) {
    THING_LOG(t, "free");
  }

  if (v->is_generating_levels) {
    CROAK("unexpected to be freeing things during creation");
  }

  (void) thing_pop(g, v, t);

  thing_ext_free(v, t);
  thing_fov_free(v, t);
  memset((void *) t, 0, SIZEOF(*t));

#ifdef ENABLE_PER_THING_MEMORY
  if (memory_test) {
    free(t);
  }
#endif
}
