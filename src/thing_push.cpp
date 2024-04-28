//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include <string.h>

#include "my_callstack.hpp"
#include "my_level.hpp"
#include "my_main.hpp"
#include "my_tile.hpp"
#include "my_tp.hpp"

void level_thing_push(Levelp l, Thingp t)
{
  TRACE_NO_INDENT();

  int16_t x = t->pix_x / TILE_WIDTH;
  int16_t y = t->pix_y / TILE_HEIGHT;

  if (level_is_oob(l, x, y)) {
    return;
  }

  for (auto slot = 0; slot < MAP_SLOTS; slot++) {
    auto o = &l->obj[ x ][ y ][ slot ];
    if (o->id == t->id) {
      return;
    }
  }

  for (auto slot = 0; slot < MAP_SLOTS; slot++) {
    auto o = &l->obj[ x ][ y ][ slot ];
    if (! o->id) {
      o->id     = t->id;
      auto tp   = tp_find(t->tp_id);
      auto tile = tp_first_tile(tp);
      if (tile) {
        o->tile = tile_global_index(tile);
      }
      return;
    }
  }

  ERR("out of thing slots");
}
