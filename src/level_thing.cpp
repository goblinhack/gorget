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

Thingp level_thing_get(Levelp l, int x, int y, uint8_t slot, Tpp *out)
{
  TRACE_NO_INDENT();

  Id id = l->obj[ x ][ y ][ slot ].id;

  if (out) {
    *out = nullptr;
  }

  if (! id) {
    return nullptr;
  }

  if (id >= THING_ID_BASE) {
    auto t = level_thing_find(l, id);
    if (! t) {
      return nullptr;
    }

    if (out) {
      *out = tp_find(t->tp_id);
    }

    return t;
  }

  if (out) {
    *out = tp_find(id);
  }

  return nullptr;
}

Thingp level_thing_find_optional(Level *l, ThingId id)
{
  TRACE_NO_INDENT();

  if (! id) {
    return nullptr;
  }

  auto thing_id = id;
  auto x        = THING_ID_GET_X(thing_id);
  auto y        = THING_ID_GET_Y(thing_id);

  ASSERT_EX(x, <, (1 << THING_ID_X_BITS));
  ASSERT_EX(y, <, (1 << THING_ID_Y_BITS));

  auto t = &l->all_things[ x ][ y ];
  if (t->id == thing_id) {
    return t;
  }
  return nullptr;
}

Thingp level_thing_find(Levelp l, ThingId id)
{
  TRACE_NO_INDENT();

  auto thing_id = id;
  auto x        = THING_ID_GET_X(thing_id);
  auto y        = THING_ID_GET_Y(thing_id);

  ASSERT_EX(x, <, (1 << THING_ID_X_BITS));
  ASSERT_EX(y, <, (1 << THING_ID_Y_BITS));

  auto t = &l->all_things[ x ][ y ];
  if (! t) {
    DIE("Thing not found for id, %" PRIX32 "", id);
  }

  if (t->id != id) {
    DIE("Thing found but entropy mismatch for id, %" PRIX32 "", id);
  }

  return t;
}

Thingp level_thing_new(Levelp l, Tpp tp, int tx, int ty)
{
  TRACE_NO_INDENT();

  int16_t x = 0;
  int16_t y = 0;

  for (x = 0; x < (1 << THING_ID_X_BITS); x++) {
    for (y = 0; y < (1 << THING_ID_Y_BITS); y++) {
      auto t = &l->all_things[ x ][ y ];
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
      thing_id = (entropy << (THING_ID_X_BITS + THING_ID_Y_BITS)) | (x << THING_ID_Y_BITS) | y;
      t->id    = thing_id;
      t->pix_x = (int) tx * TILE_WIDTH;
      t->pix_y = (int) ty * TILE_HEIGHT;

      if (tp) {
        t->tp_id = tp_id_get(tp);
      }

      return t;
    }
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
