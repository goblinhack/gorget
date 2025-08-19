//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_level.hpp"
#include "my_main.hpp"
#include "my_ptrcheck.hpp"
#include "my_tile.hpp"

//
// For things moving between tiles, calculate the pixel they are at based on the timestep
//
void thing_interpolate(Gamep g, Thingp t, float dt)
{
  TRACE_NO_INDENT();

  if (0) {
    if (thing_is_player(t)) {
      THING_TOPCON(t, "from %d,%d to %d,%d dt %f", t->moving_from.x, t->moving_from.y, t->at.x, t->at.y, dt);
    }
  }

  if (t->moving_from == t->at) {
    return;
  }

  float pix_x = (float) t->moving_from.x + (((float) (t->at.x - t->moving_from.x)) * dt);
  float pix_y = (float) t->moving_from.y + (((float) (t->at.y - t->moving_from.y)) * dt);

  t->pix_at.x = (int) (pix_x * INNER_TILE_WIDTH);
  t->pix_at.y = (int) (pix_y * INNER_TILE_HEIGHT);
}
