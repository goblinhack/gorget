//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_globals.hpp"
#include "my_level.hpp"
#include "my_main.hpp"
#include "my_tile.hpp"

//
// For things moving between tiles, calculate the pixel they are at based on the timestep
//
void thing_interpolate(Gamep g, Thingp t, float dt)
{
  TRACE_NO_INDENT();

  auto at = thing_at(t);

  if (0) {
    THING_TOPCON(t, "from %d,%d to %d,%d dt %f", t->moving_from.x, t->moving_from.y, at.x, at.y, dt);
  }

  if (t->moving_from == at) {
    return;
  }

  if (dt < 0) {
    DIE("negative dt %f", dt);
  }

  float pix_x = (float) t->moving_from.x + (((float) (at.x - t->moving_from.x)) * dt);
  float pix_y = (float) t->moving_from.y + (((float) (at.y - t->moving_from.y)) * dt);

  spoint pix_at;
  pix_at.x = (int) (pix_x * INNER_TILE_WIDTH);
  pix_at.y = (int) (pix_y * INNER_TILE_HEIGHT);
  thing_pix_at_set(t, pix_at);
}
