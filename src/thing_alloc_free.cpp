//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_level.hpp"
#include "my_random.hpp"

#include <iostream>
#include <mutex>

static std::mutex thing_mutex;

Thingp thing_alloc(Gamep g, Levelsp v, Levelp l, Tpp tp, spoint)
{
  TRACE_NO_INDENT();

  if (unlikely(! tp)) {
    DIE("no template set for thing allocation");
  }

  const auto tp_id                       = tp_id_get(tp);
  int        id_attempts_using_level_num = 100;
  bool       need_mutex;

  //
  // Repeatedly try to allocate an ID.
  //
  for (auto tries = 0; tries < (1 << THING_INDEX_BITS); tries++) {
    ThingIdPacked index_packed = {};

    //
    // Use the full range of IDs. If we can, we will use part of this as the level as
    // it allows threads to avoid mutexes.
    //
    // Intentionally using OS rand here, as if we had a conflict with another thread
    // we would end up with multiple rand calls - and that would make level gen inconsistent
    // across seeds.
    //
    index_packed.c.index = os_random_range(1, 1 << THING_INDEX_BITS);

    if (id_attempts_using_level_num-- > 0) {
      //
      // Thread should be isolated from the others by virtue of the level num being different
      // and hence using a different ID space
      //
      index_packed.b.level_num = l->level_num;
      need_mutex               = false;
    } else {
      //
      // Could conflict with other threads
      //
      need_mutex = true;
    }

    //
    // Check if there is anything at this index
    //
    auto index = index_packed.c.index;
    auto t     = &v->thing_body[ index ];
    if (t->tp_id) {
      continue;
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
        continue;
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
        continue;
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
    index_packed.c.entropy = ++entropy;

    //
    // The thing has the full ID, including entropy
    //
    t->id = index_packed.a.val;

    if (0) {
      LOG("Thing alloc %08" PRIx32     //
          " (level: %" PRIu32          //
          " id: %08" PRIx32            //
          " entropy: %08" PRIx32       //
          ")",                         //
          t->id,                       //
          index_packed.b.level_num,    //
          index_packed.b.per_level_id, //
          index_packed.b.entropy);
    }

    if (thing_is_monst(t) || thing_is_player(t)) {
      thing_ai_alloc(g, v, l, t);
    }

    return t;
  }

  DIE("out of things");
}

void thing_free(Gamep g, Levelsp v, Levelp l, Thingp t)
{
  TRACE_NO_INDENT();

  auto o = thing_find(g, v, t->id);
  if (t != o) {
    DIE("Thing mismatch found for id, %08" PRIx32 "", t->id);
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
  thing_ai_free(g, v, l, t);
  memset((void *) t, 0, SIZEOF(*t));
  thing_mutex.unlock();
}

ThingAip thing_ai_alloc(Gamep g, Levelsp v, Levelp l, Thingp t)
{
  TRACE_NO_INDENT();

  //
  // Continue from the last successful allocation
  //
  for (auto tries = 0; tries < THING_AI_MAX; tries++) {
    ThingAiId ai_id = os_random_range(1, THING_AI_MAX - 1);
    if (v->thing_ai[ ai_id ].in_use) {
      continue;
    }

    thing_mutex.lock();
    {
      if (unlikely(v->thing_ai[ ai_id ].in_use)) {
        thing_mutex.unlock();
        continue;
      }
      v->thing_ai[ ai_id ].in_use = true;
    }
    thing_mutex.unlock();

    t->ai_id = ai_id;
    return &v->thing_ai[ ai_id ];
  }

  ERR("out of Thing AI IDs");
  return 0;
}

void thing_ai_free(Gamep g, Levelsp v, Levelp l, Thingp t)
{
  TRACE_NO_INDENT();

  auto ai_id = t->ai_id;
  if (! ai_id) {
    return;
  }

  if (! v->thing_ai[ ai_id ].in_use) {
    ERR("freeing unused Thing AI ID is not in use, %" PRIx32 "", ai_id);
  }

  v->thing_ai[ ai_id ].in_use = false;
  t->ai_id                    = 0;
}
