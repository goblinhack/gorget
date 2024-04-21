//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include <string.h>

#include "my_level.hpp"
#include "my_tp.hpp"

void thing_pop(LevelData *data, Thingp t)
{
  TRACE_NO_INDENT();

  uint8_t x = t->pix_x / TILE_WIDTH;
  uint8_t y = t->pix_y / TILE_HEIGHT;

  if (is_oob(data, x, y)) {
    return;
  }

  for (auto slot = 0; slot < MAP_SLOTS; slot++) {
    auto o = &data->obj[ x ][ y ][ slot ];
    if (o->id == t->id) {
      memset(o, 0, sizeof(*o));
      return;
    }
  }
}

void Level::thing_pop(Thingp t)
{
  TRACE_NO_INDENT();
  return ::thing_pop(data, t);
}
