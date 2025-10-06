//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_game.hpp"
#include "my_level.hpp"

#include <iostream>

Tpp thing_tp(Thingp t)
{
  if (t->tp_id) {
    return tp_find(t->tp_id);
  }

  return nullptr;
}

Thingp thing_get(Gamep g, Levelsp v, Levelp l, spoint p, int slot)
{
  TRACE_NO_INDENT();

  if (! l) {
    ERR("trying to get a thing on a null level");
    return nullptr;
  }

  if (is_oob(p)) {
    ERR("out of bounds %d,%d, slot %d", p.x, p.y, slot);
    return nullptr;
  }

  if ((slot < 0) || (slot >= MAP_SLOTS)) {
    ERR("slot out of bounds %d,%d, slot %d", p.x, p.y, slot);
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

  if (is_oob(p)) {
    ERR("out of bounds %d,%d, slot %d", p.x, p.y, slot);
    return nullptr;
  }

  if ((slot < 0) || (slot >= MAP_SLOTS)) {
    ERR("slot out of bounds %d,%d, slot %d", p.x, p.y, slot);
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

void thing_stats_dump(Gamep g, Levelsp v)
{
  TRACE_NO_INDENT();

  int in_use_things = 0;
  int free_things   = 0;

  for (ThingId index = 0; index < (1 << THING_INDEX_BITS); index++) {
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

ThingAip thing_ai_struct(Gamep g, Thingp t)
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
