//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_main.hpp"
#include "my_random.hpp"
#include "my_thing_inlines.hpp"

#include <iostream>
#include <mutex>
#include <string.h>

static std::mutex thing_mutex;

[[nodiscard]] static bool thing_ext_alloc_do(Gamep g, Levelsp v, Levelp l, Thingp t, ThingExtId ext_id)
{
  TRACE_NO_INDENT();

  thing_mutex.lock();
  {
    if (unlikely(v->thing_ext[ ext_id ].in_use)) {
      thing_mutex.unlock();
      return false;
    }
    v->thing_ext[ ext_id ].in_use = true;
    v->thing_ext_count++;
  }
  thing_mutex.unlock();

  t->ext_id = ext_id;
  return true;
}

[[nodiscard]] static bool thing_ext_alloc(Gamep g, Levelsp v, Levelp l, Thingp t)
{
  TRACE_NO_INDENT();

  //
  // Continue from the last successful allocation
  //
  for (auto tries = 0; tries < THING_EXT_MAX; tries++) {
    ThingExtId ext_id = os_random_range(1, THING_EXT_MAX - 1);
    if (v->thing_ext[ ext_id ].in_use) {
      continue;
    }

    if (thing_ext_alloc_do(g, v, l, t, ext_id)) {
      return true;
    }
  }

  //
  // Last resort
  //
  for (auto ext_id = THING_EXT_MAX - 1; ext_id > 0; ext_id--) {
    if (v->thing_ext[ ext_id ].in_use) {
      continue;
    }

    if (thing_ext_alloc_do(g, v, l, t, ext_id)) {
      return true;
    }
  }

  CROAK("out of Thing ext IDs: max is %d", THING_EXT_MAX);

  return false;
}

static void thing_ext_free(Gamep g, Levelsp v, Levelp l, Thingp t)
{
  TRACE_NO_INDENT();

  auto ext_id = t->ext_id;
  if (! ext_id) {
    return;
  }

  if (! v->thing_ext[ ext_id ].in_use) {
    ERR("freeing unused Thing AI ID is not in use, %" PRIx32 "", ext_id);
  }

  v->thing_ext[ ext_id ].in_use = false;
  v->thing_ext_count--;
  if (v->thing_ext_count < 0) {
    CROAK("bad thing_ext count");
  }

  t->ext_id = 0;
}

static Thingp thing_alloc_do(Gamep g, Levelsp v, Levelp l, Tpp tp, spoint p, ThingIdPacked id, bool needs_ext_memory,
                             bool need_mutex)
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
  auto arr_index = id.c.arr_index;
  auto t         = &v->thing_body[ arr_index ];
  if (t->tp_id) {
    return nullptr;
  }

  //
  // If we need a mutex, lock the thing population for this slot
  //
  if (need_mutex) {
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
  if (! entropy) {
    entropy++;
  }
  id.c.entropy = ++entropy;

  //
  // The thing has the full ID, including entropy
  //
  t->id = id.a.val;

  if (0) {
    LOG("Thing alloc %08" PRIx32 //
        " (level: %" PRIu32      //
        " id: %08" PRIx32        //
        " entropy: %08" PRIx32   //
        ")",                     //
        t->id,                   //
        id.b.level_num,          //
        id.b.per_level_id,       //
        id.b.entropy);
  }

  if (needs_ext_memory) {
    if (! thing_ext_alloc(g, v, l, t)) {
      thing_free(g, v, l, t);
      return nullptr;
    }
  }

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
  auto needs_ext_memory = tp_is_monst(tp) || tp_is_player(tp);
  if (needs_ext_memory) {
    if (v->thing_ext_count >= THING_EXT_MAX - 1) {
      TP_LOG(tp, "out of ext thing memory");
      return nullptr;
    }
  }

  //
  // The level select level doesn't have a dedicated bit slot so just use a level that
  // is not initialized
  //
  auto level_num = l->level_num;
  if (level_num == LEVEL_SELECT_ID) {
    for (auto i = 0; i < LEVEL_MAX; i++) {
      if (! v->level[ i ].is_initialized) {
        level_num = i;
        break;
      }
    }
  }

  //
  // Repeatedly try to allocate an ID.
  //
  // Use the level_num as scoping so that we do not need to use a mutex as different
  // levels will allocate from different regions of the array.
  //
  for (uint32_t tries = 0; tries < (1 << THING_PER_LEVEL_THING_ID_BITS) / 2; tries++) {
    ThingIdPacked id  = {};
    id.b.level_num    = l->level_num;
    id.b.per_level_id = os_random_range(1, (1 << THING_PER_LEVEL_THING_ID_BITS) - 1);

    auto t = thing_alloc_do(g, v, l, tp, p, id, needs_ext_memory, false /* no mutex */);
    if (t) {
      return t;
    }
  }

  //
  // The level is getting full. Try a linear search of that level's IDs.
  //
  for (uint32_t tries = 1; tries < (1 << THING_PER_LEVEL_THING_ID_BITS); tries++) {
    ThingIdPacked id  = {};
    id.b.level_num    = l->level_num;
    id.b.per_level_id = tries;

    auto t = thing_alloc_do(g, v, l, tp, p, id, needs_ext_memory, false /* mutex */);
    if (t) {
      return t;
    }
  }

  if (v->is_generating_levels) {
    CROAK("ran out of thing IDs while doing multi threaded level gen");
  }

  //
  // Last resort, allocate from the last ID towards the front.
  //
  static uint32_t last_id;

  if (last_id) {
    for (uint32_t tries = last_id; tries > 0; tries--) {
      ThingIdPacked id = {};
      id.c.arr_index   = tries;

      auto t = thing_alloc_do(g, v, l, tp, p, id, needs_ext_memory, true /* mutex */);
      if (t) {
        last_id = tries;
        return t;
      }
    }
  }

  //
  // Last lasst resort, allocate from the end as less likely to be used.
  //
  for (uint32_t tries = THING_ID_MAX - 1; tries > 0; tries--) {
    ThingIdPacked id = {};
    id.c.arr_index   = tries;

    auto t = thing_alloc_do(g, v, l, tp, p, id, needs_ext_memory, true /* mutex */);
    if (t) {
      last_id = tries;
      return t;
    }
  }

  CROAK("out of Thing IDs: max is %d", THING_ID_MAX);
  return nullptr;
}

void thing_free(Gamep g, Levelsp v, Levelp l, Thingp t)
{
  TRACE_NO_INDENT();

  auto o = thing_find(g, v, t->id);
  if (t != o) {
    CROAK("Thing mismatch found for id, %08" PRIx32 "", t->id);
  }

  auto tp = thing_tp(t);

  //
  // Clean up references
  //
  if (tp_is_player(tp)) {
    v->player_id = 0;
  }

  if (tp_is_level_curr(tp)) {
    v->level_select_id = 0;
  }

  if (0) {
    THING_LOG(t, "free");
  }

  thing_pop(g, v, t);

  thing_mutex.lock();
  thing_ext_free(g, v, l, t);
  memset((void *) t, 0, SIZEOF(*t));

  thing_mutex.unlock();
}
