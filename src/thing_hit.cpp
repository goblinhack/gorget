//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
// REMOVED #include "my_dice_rolls.hpp"
// REMOVED #include "my_game.hpp"
// REMOVED #include "my_globals.hpp"
#include "my_level.hpp"
// REMOVED #include "my_main.hpp"
// REMOVED #include "my_random.hpp"
// REMOVED #include "my_thing_inlines.hpp"
// REMOVED #include "my_ui.hpp"

//
// Hit time step
//
void thing_hit_time_step(Gamep g, Levelsp v, Levelp l, Thingp t, int time_step)
{
  TRACE_NO_INDENT();

  thing_is_hit_decr(g, v, l, t, time_step);
}
