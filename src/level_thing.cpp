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

Tpp tp(Thingp t)
{
  if (t->tp_id) {
    return tp_find(t->tp_id);
  }

  return nullptr;
}

Thingp level_thing_get(Levelp l, int x, int y, int z, int slot)
{
  TRACE_NO_INDENT();

  ThingId id = l->thing_id[ x ][ y ][ z ][ slot ];

  if (! id) {
    return nullptr;
  }

  auto t = level_thing_find(l, id);
  if (! t) {
    return nullptr;
  }

  return t;
}

Thingp level_thing_and_tp_get(Levelp l, int x, int y, int z, int slot, Tpp *out)
{
  TRACE_NO_INDENT();

  ThingId id = l->thing_id[ x ][ y ][ z ][ slot ];

  if (out) {
    *out = nullptr;
  }

  if (! id) {
    return nullptr;
  }

  auto t = level_thing_find(l, id);
  if (! t) {
    return nullptr;
  }

  if (out) {
    *out = tp_find(t->tp_id);
  }

  return t;
}

Thingp level_thing_find_optional(Level *l, ThingId id)
{
  TRACE_NO_INDENT();

  if (! id) {
    return nullptr;
  }

  auto thing_id = id;
  auto index    = THING_ID_GET(thing_id);

  ASSERT_EX(index, <, (1 << THING_ID_BITS));

  auto t = &l->thing_body[ index ];
  if (t->id == thing_id) {
    return t;
  }
  return nullptr;
}

Thingp level_thing_find(Levelp l, ThingId id)
{
  TRACE_NO_INDENT();

  auto thing_id = id;
  auto index    = THING_ID_GET(thing_id);

  ASSERT_EX(index, <, (1 << THING_ID_BITS));

  auto t = &l->thing_body[ index ];
  if (! t) {
    DIE("Thing not found for id, %" PRIX32 "", id);
  }

  if (t->id != id) {
    DIE("Thing found but entropy mismatch for id, %" PRIX32 "", id);
  }

  return t;
}

Thingp level_thing_new(Levelp l, Tpp tp, int x, int y, int z)
{
  TRACE_NO_INDENT();

  for (auto index = 0; index < (1 << THING_ID_BITS); index++) {
    auto t = &l->thing_body[ index ];
    if (t->id) {
      continue;
    }

    static uint16_t entropy;
    entropy++;
    entropy &= (1 << THING_ID_ENTROPY_BITS) - 1;
    if (! entropy) {
      entropy++;
    }

    memset(t, 0, sizeof(*t));

    ThingId thing_id;
    thing_id = (entropy << THING_ID_BITS) | index;
    t->id    = thing_id;
    t->tp_id = tp_id_get(tp);

    return t;
  }

  DIE("out of things");
}

void level_thing_free(Levelp l, Thingp t)
{
  TRACE_NO_INDENT();

  auto o = level_thing_find(l, t->id);
  if (t != o) {
    DIE("Thing mismatch found for id, %" PRIX32 "", t->id);
  }

  memset(t, 0, sizeof(*t));
}
