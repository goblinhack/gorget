//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_game.hpp"
#include "my_level.hpp"
#include "my_main.hpp"
#include "my_random.hpp"
#include "my_tile.hpp"
#include "my_time.hpp"
#include "my_tp.hpp"

//
// Falling time step
//
void thing_fall_time_step(Gamep g, Levelsp v, Levelp l, Thingp t, int time_step)
{
  TRACE_NO_INDENT();

  if (thing_is_falling_incr(g, v, l, t, time_step) > MAX_FALL_TIME_MS) {
    thing_is_falling_set(g, v, l, t, 0);
  }
}
