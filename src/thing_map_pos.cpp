//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_level.hpp"
#include "my_tp.hpp"

void thing_update_map_pos(LevelData *data, Thingp t, int8_t new_x, int8_t new_y)
{
  if ((new_x == t->x) && (new_y == t->y)) {
    return;
  }

  t->pix_x = t->x * TILE_WIDTH;
  t->pix_y = t->y * TILE_HEIGHT;

  t->old_x = t->x;
  t->old_y = t->y;

  t->x = new_x;
  t->y = new_y;
}

void Level::thing_update_map_pos(Thingp t, int8_t new_x, int8_t new_y)
{
  TRACE_NO_INDENT();
  return ::thing_update_map_pos(data, t, new_x, new_y);
}
