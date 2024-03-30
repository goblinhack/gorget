//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include <string.h>

#include "my_level.hpp"
#include "my_tp.hpp"

void thing_push(LevelData *data, Thingp t)
{
  TRACE_NO_INDENT();

  int16_t x = t->pix_x / TILE_WIDTH;
  int16_t y = t->pix_y / TILE_HEIGHT;
  point   p(x, y);

  if (is_oob(data, p)) {
    return;
  }

  for (auto slot = 0; slot < MAP_SLOTS; slot++) {
    auto o = &data->obj[ x ][ y ][ slot ];
    if (o->id == t->id) {
      return;
    }
  }

  for (auto slot = 0; slot < MAP_SLOTS; slot++) {
    auto o = &data->obj[ x ][ y ][ slot ];
    if (! o->id) {
      o->id     = t->id;
      auto tp   = tp_find(t->tp_id);
      auto tile = tp_first_tile(tp);
      if (tile) {
        o->tile = tile->global_index;
      }
      return;
    }
  }

  ERR("out of thing slots");
}

void Level::thing_push(Thingp t)
{
  TRACE_NO_INDENT();
  return ::thing_push(data, t);
}
