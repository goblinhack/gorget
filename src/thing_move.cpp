//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_level.hpp"
#include "my_tile.hpp"
#include "my_tp.hpp"

void level_thing_move(Levelp l, Thingp t, int new_x, int new_y)
{
  if (level_is_oob(l, new_x, new_y)) {
    return;
  }

  if ((new_x == t->x) && (new_y == t->y)) {
    return;
  }

  level_thing_pop(l, t);

  t->pix_x = t->x * TILE_WIDTH;
  t->pix_y = t->y * TILE_HEIGHT;

  t->old_x = t->x;
  t->old_y = t->y;

  t->x = new_x;
  t->y = new_y;

  level_thing_push(l, t);
}
