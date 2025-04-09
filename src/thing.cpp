//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_enums.hpp"
#include "my_game.hpp"
#include "my_level.hpp"
#include "my_main.hpp"
#include "my_minimal.hpp"
#include "my_random.hpp"
#include "my_tile.hpp"
#include "my_tp.hpp"

#include <cinttypes>
#include <iostream>
#include <map>
#include <mutex>
#include <sstream>
#include <string.h>
#include <string>

ENUM_DEF_C(THING_FLAG_ENUM, ThingFlag)

static std::mutex thing_mutex;

static Thingp thing_alloc(Gamep, Levelsp, Levelp, Tpp tp, point);
static void   thing_free(Gamep, Levelsp, Levelp, Thingp t);

static ThingAip thing_ai_alloc(Gamep, Levelsp, Levelp, Thingp t);
static void     thing_ai_free(Gamep, Levelsp, Levelp, Thingp t);

Tpp thing_tp(Thingp t)
{
  if (t->tp_id) {
    return tp_find(t->tp_id);
  }

  return nullptr;
}

Thingp thing_init(Gamep g, Levelsp v, Levelp l, Tpp tp, point at)
{
  TRACE_NO_INDENT();

  auto t = thing_alloc(g, v, l, tp, at);
  if (! t) {
    return nullptr;
  }

  t->at          = at;
  t->old_at      = at;
  t->moving_from = at;

  t->pix_at.x = t->at.x * TILE_WIDTH;
  t->pix_at.y = t->at.y * TILE_HEIGHT;

  //
  // Assign an initial tile
  //
  auto index = pcg_rand() % tp_tiles_size(tp);
  auto tile  = tp_tiles_get(tp, index);
  if (tile) {
    t->tile_index = tile_global_index(tile);

    if (tp_is_animated(tp)) {
      auto i        = pcg_random_range_inclusive(0, tp_tiles_size(tp) - 1);
      t->anim_index = i;
    }
  }

  //
  // Assign the player
  //
  if (tp_is_player(tp)) {
    v->player_id = t->id;
  }

  thing_update(g, t);

  return t;
}

void thing_fini(Gamep g, Levelsp v, Levelp l, Thingp t)
{
  TRACE_NO_INDENT();

  thing_free(g, v, l, t);
}

static Thingp thing_alloc(Gamep g, Levelsp v, Levelp l, Tpp tp, point)
{
  TRACE_NO_INDENT();

  thing_mutex.lock();

  static ThingId last_index;

  for (ThingId n = 0; n < (1 << THING_COMMON_ID_BITS); n++) {
    //
    // Wrap around
    //
    ThingId index = (last_index + n + 1) % (1 << THING_COMMON_ID_BITS);

    //
    // Skip index 0
    //
    if (! index) {
      continue;
    }

    auto t = &v->thing_body[ index ];
    if (t->id) {
      continue;
    }

    static uint16_t entropy;
    entropy++;
    entropy &= (1 << THING_COMMON_ID_ENTROPY_BITS) - 1;
    if (! entropy) {
      entropy++;
    }

    memset((void *) t, 0, SIZEOF(*t));

    ThingId thing_id;
    thing_id = (entropy << THING_COMMON_ID_BITS) | index;
    t->id    = thing_id;
    t->tp_id = tp_id_get(tp);

    if (thing_is_monst(t) || thing_is_player(t)) {
      thing_ai_alloc(g, v, l, t);
    }

    last_index = index;

    thing_mutex.unlock();

    return t;
  }

  thing_mutex.unlock();

  DIE("out of things");
}

static void thing_free(Gamep g, Levelsp v, Levelp l, Thingp t)
{
  TRACE_NO_INDENT();

  thing_mutex.lock();

  auto o = thing_find(g, v, t->id);
  if (t != o) {
    DIE("Thing mismatch found for id, %" PRIx32 "", t->id);
  }

  thing_pop(g, v, l, t);
  thing_ai_free(g, v, l, t);

  memset((void *) t, 0, SIZEOF(*t));

  thing_mutex.unlock();
}

void thing_stats_dump(Gamep g, Levelsp v)
{
  TRACE_NO_INDENT();

  int in_use_things = 0;
  int free_things   = 0;

  for (ThingId index = 0; index < (1 << THING_COMMON_ID_BITS); index++) {
    auto t = &v->thing_body[ index ];
    if (t->id) {
      in_use_things++;
    } else {
      free_things++;
    }
  }

  LOG("Thing stats:");
  LOG("- Total things        %u", in_use_things + free_things);
  LOG("- In use things       %u", in_use_things);
  LOG("- Free things         %u", free_things);
}

static ThingAip thing_ai_alloc(Gamep g, Levelsp v, Levelp l, Thingp t)
{
  TRACE_NO_INDENT();

  static ThingAiId last_index;

  //
  // Continue from the last successful allocation
  //
  for (ThingAiId index = 0; index < THING_AI_MAX; index++) {
    ThingAiId ai_id = last_index + index;
    if (ai_id == 0) {
      continue;
    }

    if (! v->thing_ai[ ai_id ].in_use) {
      v->thing_ai[ ai_id ].in_use = true;
      t->ai_id                    = ai_id;
      last_index                  = ai_id;
      return &v->thing_ai[ ai_id ];
    }
  }

  ERR("out of Thing AI IDs");
  return 0;
}

static void thing_ai_free(Gamep g, Levelsp v, Levelp l, Thingp t)
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

ThingAip thing_ai(Gamep g, Thingp t)
{
  TRACE_NO_INDENT();

  auto v = game_levels_get(g);
  if (! v) {
    return nullptr;
  }

  auto ai_id = t->ai_id;
  if (! ai_id) {
    return nullptr;
  }

  return &v->thing_ai[ ai_id ];
}

void thing_update(Gamep g, Thingp t)
{
  TRACE_NO_INDENT();

  auto tp = thing_tp(t);

  t->speed = tp_speed_get(tp);
}

Thingp thing_get(Gamep g, Levelsp v, Levelp l, point p, int slot)
{
  TRACE_NO_INDENT();

  ThingId id = l->thing_id[ p.x ][ p.y ][ slot ];
  if (! id) {
    return nullptr;
  }

  auto t = thing_find(g, v, id);
  if (! t) {
    return nullptr;
  }

  return t;
}

Thingp thing_and_tp_get_at(Gamep g, Levelsp v, Levelp l, point p, int slot, Tpp *out)
{
  TRACE_NO_INDENT();

  ThingId id = l->thing_id[ p.x ][ p.y ][ slot ];

  if (out) {
    *out = nullptr;
  }

  if (! id) {
    return nullptr;
  }

  auto t = thing_find(g, v, id);
  if (! t) {
    return nullptr;
  }

  if (out) {
    *out = tp_find(t->tp_id);
  }

  return t;
}

Thingp thing_find_optional(Gamep g, Levelsp v, ThingId id)
{
  TRACE_NO_INDENT();

  if (! id) {
    return nullptr;
  }

  auto thing_id = id;
  auto index    = THING_COMMON_ID_GET(thing_id);

  ASSERT_EX(index, <, (1 << THING_COMMON_ID_BITS));

  auto t = &v->thing_body[ index ];
  if (t->id == thing_id) {
    return t;
  }
  return nullptr;
}

Thingp thing_find(Gamep g, Levelsp v, ThingId id)
{
  TRACE_NO_INDENT();

  auto thing_id = id;
  auto index    = THING_COMMON_ID_GET(thing_id);

  ASSERT_EX(index, <, (1 << THING_COMMON_ID_BITS));

  auto t = &v->thing_body[ index ];
  if (! t) {
    DIE("Thing not found for id, %" PRIx32 "", id);
  }

  if (t->id != id) {
    DIE("Thing found as id %" PRIx32 " but entropy mismatch for id, %" PRIx32 "", t->id, id);
  }

  return t;
}

//
// Called at the beginning of each tick
//
void thing_tick_begin(Gamep g, Levelsp v, Levelp l, Thingp t) { TRACE_NO_INDENT(); }

//
// Called when the level is idle
//
void thing_tick_idle(Gamep g, Levelsp v, Levelp l, Thingp t)
{
  TRACE_NO_INDENT();

  //
  // If asked to follow the mouse path, start walking
  //
  thing_move_to_next(g, v, l, t);
}

//
// Called at the end of each tick
//
void thing_tick_end(Gamep g, Levelsp v, Levelp l, Thingp t)
{
  TRACE_NO_INDENT();

  //
  // Mark the tick as completed
  //
  if (t->tick == v->tick) {
    return;
  }
  t->tick = v->tick;

  //
  // If following the mouse path, keep going
  //
  thing_move_to_next(g, v, l, t);
}
