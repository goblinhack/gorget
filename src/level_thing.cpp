//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_level.hpp"
#include "my_main.hpp"
#include "my_minimal.hpp"
#include "my_tile.hpp"
#include "my_tp.hpp"

#include <cinttypes>
#include <iostream>
#include <sstream>
#include <string.h>

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

Thingp thing_new(Levelp l, Tpp tp, int x, int y, int z)
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

    memset(t, 0, sizeof(*t));

    ThingId thing_id;
    thing_id = (entropy << THING_COMMON_ID_BITS) | index;
    t->id    = thing_id;
    t->tp_id = tp_id_get(tp);

    if (thing_is_monst(t) || thing_is_player(t)) {
      thing_ai_new(l, t);
    }

    return t;
  }

  DIE("out of things");
}

void thing_free(Levelp l, Thingp t)
{
  TRACE_NO_INDENT();

  auto o = thing_find(l, t->id);
  if (t != o) {
    DIE("Thing mismatch found for id, %" PRIX32 "", t->id);
  }

  thing_ai_free(l, t);

  memset(t, 0, sizeof(*t));
}

ThingAip thing_ai_new(Levelp l, Thingp t)
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

void thing_ai_free(Levelp l, Thingp t)
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
