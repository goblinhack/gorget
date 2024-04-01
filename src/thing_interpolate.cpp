//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_level.hpp"
#include "my_tp.hpp"

void thing_interpolate(LevelData *data, Thingp t, float dt)
{
  if ((t->old_x == t->x) && (t->old_y == t->y)) {
    return;
  }

  float pix_x = (float) t->old_x + (((float) (t->x - t->old_x)) * dt);
  float pix_y = (float) t->old_y + (((float) (t->y - t->old_y)) * dt);

  t->pix_x = pix_x * TILE_WIDTH;
  t->pix_y = pix_y * TILE_HEIGHT;
}

void Level::thing_interpolate(Thingp t, float dt)
{
  TRACE_NO_INDENT();
  return ::thing_interpolate(data, t, dt);
}
