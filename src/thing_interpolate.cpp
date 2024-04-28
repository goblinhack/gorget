//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_level.hpp"
#include "my_tile.hpp"
#include "my_tp.hpp"

void level_thing_interpolate(Level *l, Thingp t, float dt)
{
  if ((t->old_x == t->x) && (t->old_y == t->y)) {
    return;
  }

  float pix_x = (float) t->old_x + (((float) (t->x - t->old_x)) * dt);
  float pix_y = (float) t->old_y + (((float) (t->y - t->old_y)) * dt);

  t->pix_x = pix_x * TILE_WIDTH;
  t->pix_y = pix_y * TILE_HEIGHT;
}
