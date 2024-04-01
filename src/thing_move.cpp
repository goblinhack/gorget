//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_level.hpp"
#include "my_tp.hpp"

void thing_move(LevelData *data, Thingp t, point new_loc)
{
  if (::is_oob(data, new_loc)) {
    return;
  }

  point my_loc(t->x, t->y);
  if (new_loc == my_loc) {
    return;
  }

  ::thing_pop(data, t);

  t->pix_x = t->x * TILE_WIDTH;
  t->pix_y = t->y * TILE_HEIGHT;

  t->old_x = t->x;
  t->old_y = t->y;

  t->x = new_loc.x;
  t->y = new_loc.y;

  ::thing_push(data, t);
}

void Level::thing_move(Thingp t, point new_loc)
{
  TRACE_NO_INDENT();
  return ::thing_move(data, t, new_loc);
}
