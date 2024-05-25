//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_enums.hpp"
#include "my_level.hpp"
#include "my_main.hpp"
#include "my_minimal.hpp"
#include "my_random.hpp"
#include "my_tile.hpp"
#include "my_tp.hpp"

#include <cinttypes>
#include <iostream>
#include <map>
#include <sstream>
#include <string.h>
#include <string>

ENUM_DEF_C(THING_FLAG_ENUM, ThingFlag)

static Thingp thing_alloc(Levelp l, Tpp tp, int x, int y, int z);
static void   thing_free(Levelp l, Thingp t);

static ThingAip thing_ai_alloc(Levelp l, Thingp t);
static void     thing_ai_free(Levelp l, Thingp t);

Tpp thing_tp(Thingp t)
{
  if (t->tp_id) {
    return tp_find(t->tp_id);
  }

  return nullptr;
}

Thingp thing_init(Levelp l, Tpp tp, int x, int y, int z)
{
  TRACE_NO_INDENT();

  auto t = thing_alloc(l, tp, x, y, z);
  if (! t) {
    return nullptr;
  }

  t->x = x;
  t->y = y;
  t->z = z;

  t->old_x = x;
  t->old_y = y;
  t->old_z = z;

  t->pix_x = t->x * TILE_WIDTH;
  t->pix_y = t->y * TILE_HEIGHT;

  //
  // Assign an initial tile
  //
  auto index = pcg_rand() % tp_tiles_size(tp);
  auto tile  = tp_tiles_get(tp, index);
  if (tile) {
    t->tile_index = tile_index(tile);
    auto i        = pcg_random_range_inclusive(0, tp_tiles_size(tp) - 1);
    t->anim_index = i;
  }

  //
  // Assign the player
  //
  if (tp_is_player(tp)) {
    if (tp_player_index_get(tp) == l->player_index) {
      l->player = t->id;
    }
  }

  thing_update(l, t);

  return t;
}

void thing_fini(Levelp l, Thingp t)
{
  TRACE_NO_INDENT();

  thing_free(l, t);
}

static Thingp thing_alloc(Levelp l, Tpp tp, int x, int y, int z)
{
  TRACE_NO_INDENT();

  for (auto index = 0; index < (1 << THING_COMMON_ID_BITS); index++) {
    auto t = &l->thing_body[ index ];
    if (t->id) {
      continue;
    }

    static uint16_t entropy;
    entropy++;
    entropy &= (1 << THING_COMMON_ID_ENTROPY_BITS) - 1;
    if (! entropy) {
      entropy++;
    }

    memset(t, 0, SIZEOF(*t));

    ThingId thing_id;
    thing_id = (entropy << THING_COMMON_ID_BITS) | index;
    t->id    = thing_id;
    t->tp_id = tp_id_get(tp);

    if (thing_is_monst(t) || thing_is_player(t)) {
      thing_ai_alloc(l, t);
    }

    return t;
  }

  DIE("out of things");
}

static void thing_free(Levelp l, Thingp t)
{
  TRACE_NO_INDENT();

  auto o = thing_find(l, t->id);
  if (t != o) {
    DIE("Thing mismatch found for id, %" PRIX32 "", t->id);
  }

  thing_ai_free(l, t);

  memset(t, 0, SIZEOF(*t));
}

static ThingAip thing_ai_alloc(Levelp l, Thingp t)
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

    if (! l->thing_ai[ ai_id ].in_use) {
      l->thing_ai[ ai_id ].in_use = true;
      t->ai_id                    = ai_id;
      last_index                  = ai_id;
      return &l->thing_ai[ ai_id ];
    }
  }

  ERR("out of Thing AI IDs");
  return 0;
}

static void thing_ai_free(Levelp l, Thingp t)
{
  TRACE_NO_INDENT();

  auto ai_id = t->ai_id;
  if (! ai_id) {
    return;
  }

  if (! l->thing_ai[ ai_id ].in_use) {
    ERR("freeing unused Thing AI ID is not in use, %" PRIX32 "", ai_id);
  }

  l->thing_ai[ ai_id ].in_use = false;
  t->ai_id                    = 0;
}

ThingAip thing_ai(Levelp l, Thingp t)
{
  TRACE_NO_INDENT();

  auto ai_id = t->ai_id;
  if (! ai_id) {
    return nullptr;
  }

  return &l->thing_ai[ ai_id ];
}

void thing_update(Level *l, Thingp t)
{
  TRACE_NO_INDENT();

  auto tp = thing_tp(t);

  t->speed = tp_speed_get(tp);
}

Thingp thing_get(Levelp l, int x, int y, int z, int slot)
{
  TRACE_NO_INDENT();

  ThingId id = l->thing_id[ x ][ y ][ z ][ slot ];

  if (! id) {
    return nullptr;
  }

  auto t = thing_find(l, id);
  if (! t) {
    return nullptr;
  }

  return t;
}

Thingp thing_and_tp_get(Levelp l, int x, int y, int z, int slot, Tpp *out)
{
  TRACE_NO_INDENT();

  ThingId id = l->thing_id[ x ][ y ][ z ][ slot ];

  if (out) {
    *out = nullptr;
  }

  if (! id) {
    return nullptr;
  }

  auto t = thing_find(l, id);
  if (! t) {
    return nullptr;
  }

  if (out) {
    *out = tp_find(t->tp_id);
  }

  return t;
}

Thingp thing_find_optional(Level *l, ThingId id)
{
  TRACE_NO_INDENT();

  if (! id) {
    return nullptr;
  }

  auto thing_id = id;
  auto index    = THING_COMMON_ID_GET(thing_id);

  ASSERT_EX(index, <, (1 << THING_COMMON_ID_BITS));

  auto t = &l->thing_body[ index ];
  if (t->id == thing_id) {
    return t;
  }
  return nullptr;
}

Thingp thing_find(Levelp l, ThingId id)
{
  TRACE_NO_INDENT();

  auto thing_id = id;
  auto index    = THING_COMMON_ID_GET(thing_id);

  ASSERT_EX(index, <, (1 << THING_COMMON_ID_BITS));

  auto t = &l->thing_body[ index ];
  if (! t) {
    DIE("Thing not found for id, %" PRIX32 "", id);
  }

  if (t->id != id) {
    DIE("Thing found but entropy mismatch for id, %" PRIX32 "", id);
  }

  return t;
}
