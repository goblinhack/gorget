//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_game.hpp"
#include "my_level.hpp"
#include "my_main.hpp"
#include "my_random.hpp"
#include "my_tile.hpp"
#include "my_tp.hpp"
#include "my_types.hpp"

#include <cinttypes>
#include <iostream>
#include <map>
#include <mutex>
#include <sstream>
#include <string.h>
#include <string>

static std::mutex thing_mutex;

static Thingp thing_alloc(Gamep, Levelsp, Levelp, Tpp tp, spoint);
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

Thingp thing_init(Gamep g, Levelsp v, Levelp l, Tpp tp, spoint at)
{
  TRACE_NO_INDENT();

  auto t = thing_alloc(g, v, l, tp, at);
  if (! t) {
    return nullptr;
  }

  t->at          = at;
  t->old_at      = at;
  t->moving_from = at;
  t->anim_type   = THING_ANIM_IDLE;
  t->level_num   = l->level_num;

  //
  // Assign an initial tile
  //
  thing_anim_init(g, v, l, t);

  //
  // Assign the player
  //
  if (tp_is_player(tp)) {
    v->player_id = t->id;

    //
    // First time entering this level?
    //
    if (! l->entered) {
      level_entered(g, v, l);
    }
  }

  //
  // Assign the current level select id. This is only valid when in the select screen.
  //
  if (tp_is_level_curr(tp)) {
    v->level_select_id = t->id;
  }

  thing_speed_set(g, v, l, t, tp_speed_get(tp));
  thing_weight_set(g, v, l, t, tp_weight_get(tp));
  thing_temperature_set(g, v, l, t, tp_temperature_initial_get(tp));
  thing_value1_set(g, v, l, t, tp_value1_get(tp));
  thing_value2_set(g, v, l, t, tp_value2_get(tp));
  thing_value3_set(g, v, l, t, tp_value3_get(tp));
  thing_value4_set(g, v, l, t, tp_value4_get(tp));
  thing_value5_set(g, v, l, t, tp_value5_get(tp));
  thing_value6_set(g, v, l, t, tp_value6_get(tp));
  thing_value7_set(g, v, l, t, tp_value7_get(tp));
  thing_value8_set(g, v, l, t, tp_value8_get(tp));
  thing_value9_set(g, v, l, t, tp_value9_get(tp));
  thing_value10_set(g, v, l, t, tp_value10_get(tp));
  thing_value11_set(g, v, l, t, tp_value11_get(tp));
  thing_value12_set(g, v, l, t, tp_value12_get(tp));
  thing_value13_set(g, v, l, t, tp_value13_get(tp));
  thing_value14_set(g, v, l, t, tp_value14_get(tp));
  thing_value15_set(g, v, l, t, tp_value15_get(tp));
  thing_value16_set(g, v, l, t, tp_value16_get(tp));
  thing_value17_set(g, v, l, t, tp_value17_get(tp));
  thing_value18_set(g, v, l, t, tp_value18_get(tp));
  thing_value19_set(g, v, l, t, tp_value19_get(tp));
  thing_value20_set(g, v, l, t, tp_value20_get(tp));
  thing_value21_set(g, v, l, t, tp_value21_get(tp));
  thing_value22_set(g, v, l, t, tp_value22_get(tp));
  thing_value23_set(g, v, l, t, tp_value23_get(tp));
  thing_value24_set(g, v, l, t, tp_value24_get(tp));
  thing_value25_set(g, v, l, t, tp_value25_get(tp));
  thing_value26_set(g, v, l, t, tp_value26_get(tp));
  thing_value27_set(g, v, l, t, tp_value27_get(tp));
  thing_value28_set(g, v, l, t, tp_value28_get(tp));
  thing_value29_set(g, v, l, t, tp_value29_get(tp));
  thing_lifespan_set(g, v, l, t, tp_lifespan_get(tp));
  thing_health_set(g, v, l, t, tp_health_initial_get(tp));

  //
  // Need to update with the new pixel position
  //
  thing_update_pos(g, t);

  return t;
}

Thingp thing_spawn(Gamep g, Levelsp v, Levelp l, Tpp tp, spoint at)
{
  TRACE_NO_INDENT();

  auto t = thing_init(g, v, l, tp, at);
  if (t) {
    thing_push(g, v, l, t);
  }
  return t;
}

void thing_fini(Gamep g, Levelsp v, Levelp l, Thingp t)
{
  TRACE_NO_INDENT();

  IF_DEBUG
  if (thing_is_loggable(t)) {
    THING_DBG(t, "fini");
  }

  thing_free(g, v, l, t);
}

static Thingp thing_alloc(Gamep g, Levelsp v, Levelp l, Tpp tp, spoint)
{
  TRACE_NO_INDENT();

  if (! tp) {
    DIE("no template set for thing allocation");
  }

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
  thing_ai_free(g, v, l, t);

  memset((void *) t, 0, SIZEOF(*t));

  thing_mutex.unlock();
}

//
// Return the level of the thing
//
Levelp thing_level(Gamep g, Levelsp v, Thingp t)
{
  TRACE_NO_INDENT();

  auto o = thing_find(g, v, t->id);
  if (t != o) {
    DIE("Thing mismatch found for id, %" PRIx32 "", t->id);
  }

  return game_level_get(g, v, t->level_num);
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

ThingPlayerp thing_player_struct(Gamep g)
{
  TRACE_NO_INDENT();

  auto v = game_levels_get(g);
  if (! v) {
    return nullptr;
  }

  return &v->thing_player;
}

Thingp thing_get(Gamep g, Levelsp v, Levelp l, spoint p, int slot)
{
  TRACE_NO_INDENT();

  if (! l) {
    ERR("trying to get a thing on a null level");
    return nullptr;
  }

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

Thingp thing_and_tp_get_at(Gamep g, Levelsp v, Levelp l, spoint p, int slot, Tpp *out)
{
  TRACE_NO_INDENT();

  if (! l) {
    ERR("trying to get a thing on a null level");
    return nullptr;
  }

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
