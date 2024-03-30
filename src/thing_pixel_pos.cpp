//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_level.hpp"
#include "my_tp.hpp"

void thing_update_pixel_pos(LevelData *data, Thingp t, float dt)
{
  if ((t->old_x == t->x) && (t->old_y == t->y)) {
    return;
  }

  t->pix_x = t->old_x + (int) (((float) (t->x - t->old_x)) * dt);
  t->pix_y = t->old_y + (int) (((float) (t->y - t->old_y)) * dt);
}

void Level::thing_update_pixel_pos(Thingp t, float dt)
{
  TRACE_NO_INDENT();
  return ::thing_update_pixel_pos(data, t, dt);
}
