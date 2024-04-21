//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_level.hpp"
#include "my_tp.hpp"

void thing_move(LevelData *data, Thingp t, int new_x, int new_y)
{
  if (::is_oob(data, new_x, new_y)) {
    return;
  }

  if ((new_x == t->x) && (new_y == t->y)) {
    return;
  }

  ::thing_pop(data, t);

  t->pix_x = t->x * TILE_WIDTH;
  t->pix_y = t->y * TILE_HEIGHT;

  t->old_x = t->x;
  t->old_y = t->y;

  t->x = new_x;
  t->y = new_y;

  ::thing_push(data, t);
}

void Level::thing_move(Thingp t, int new_x, int new_y)
{
  TRACE_NO_INDENT();
  return ::thing_move(data, t, new_x, new_y);
}
