//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_level.hpp"
#include "my_tile.hpp"
#include "my_tp.hpp"

#include <string.h>

void level_thing_pop(Levelp l, Thingp t)
{
  TRACE_NO_INDENT();

  uint8_t x = t->pix_x / TILE_WIDTH;
  uint8_t y = t->pix_y / TILE_HEIGHT;

  if (level_is_oob(l, x, y)) {
    return;
  }

  for (auto slot = 0; slot < MAP_SLOTS; slot++) {
    auto o = &l->obj[ x ][ y ][ slot ];
    if (o->id == t->id) {
      memset(o, 0, sizeof(*o));
      return;
    }
  }
}
