//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_game.hpp"
#include "my_level.hpp"
#include "my_main.hpp"
#include "my_random.hpp"
#include "my_tp_callbacks.hpp"

#include <iostream>
#include <mutex>

static std::mutex thing_mutex;

Thingp thing_alloc(Gamep g, Levelsp v, Levelp l, Tpp tp, spoint)
{
  TRACE_NO_INDENT();

  if (! tp) {
    DIE("no template set for thing allocation");
  }

  const auto tp_id = tp_id_get(tp);

  for (auto tries = 0; tries < (1 << THING_COMMON_ID_BITS); tries++) {
    auto index = pcg_random_range(1, 1 << THING_COMMON_ID_BITS);
    auto t     = &v->thing_body[ index ];
    if (t->tp_id) {
      continue;
    }

    thing_mutex.lock();
    {
      if (unlikely(t->tp_id)) {
        thing_mutex.unlock();
        continue;
      }
      t->tp_id = tp_id;
      thing_mutex.unlock();
    }

    memset((char *) t + SIZEOF(t->tp_id), 0, SIZEOF(*t) - SIZEOF(t->tp_id));

    static uint16_t entropy;
    entropy++;
    entropy &= (1 << THING_COMMON_ID_ENTROPY_BITS) - 1;
    if (! entropy) {
      entropy++;
    }

    ThingId thing_id;
    thing_id = (entropy << THING_COMMON_ID_BITS) | index;
    t->id    = thing_id;

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
    DIE("Thing mismatch found for id, %" PRIx32 "", t->id);
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
    ThingAiId ai_id = pcg_random_range(1, THING_AI_MAX - 1);
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
