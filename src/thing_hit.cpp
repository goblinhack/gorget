//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_dice_rolls.hpp"
#include "my_game.hpp"
#include "my_globals.hpp"
#include "my_level.hpp"
#include "my_main.hpp"
#include "my_random.hpp"
#include "my_thing_inlines.hpp"
#include "my_ui.hpp"

//
// Hit time step
//
void thing_hit_time_step(Gamep g, Levelsp v, Levelp l, Thingp t, int time_step)
{
  TRACE_NO_INDENT();

  thing_is_hit_decr(g, v, l, t, time_step);
}
