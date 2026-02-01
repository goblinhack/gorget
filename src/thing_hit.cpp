//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_level.hpp"

//
// Hit time step
//
void thing_hit_time_step(Gamep g, Levelsp v, Levelp l, Thingp t, int time_step)
{
  TRACE_NO_INDENT();

  (void) thing_is_hit_decr(g, v, l, t, time_step);
}
