//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_globals.hpp"
#include "my_level.hpp"
#include "my_main.hpp"

//
// For things moving between tiles, calculate the pixel they are at based on the timestep
//
void thing_interpolate(Gamep g, Levelsp v, Levelp l, Thingp t, float dt)
{
  TRACE();

  auto at          = thing_at(t);
  auto moving_from = thing_moving_from(t);

  if (compiler_unused) {
    THING_LOG(t, "from %d,%d to %d,%d dt %f", moving_from.x, moving_from.y, at.x, at.y, dt);
  }

  if (moving_from == at) {
    return;
  }

  if (dt < 0) {
    CROAK("negative dt %f", dt);
  }

  //
  // Cannot use thing_update_pos here, as the thing is already at the destination
  //
  float const pix_x = (float) moving_from.x + (((float) (at.x - moving_from.x)) * dt);
  float const pix_y = (float) moving_from.y + (((float) (at.y - moving_from.y)) * dt);

  spoint pix_at;
  pix_at.x = (int) (pix_x * (float) TILE_WIDTH);
  pix_at.y = (int) (pix_y * (float) TILE_HEIGHT);
  thing_pix_at_set(g, v, l, t, pix_at);
}
