//
// Copyright goblinhack@gmail.com
//

#include "my_types.hpp"

#include "my_callstack.hpp"
#include "my_game.hpp"
#include "my_level.hpp"
#include "my_main.hpp"
#include "my_tp.hpp"

//
// Handle things interacting with water
//
void level_tick_begin_water(Gamep g, Levelsp v, Levelp l)
{
  TRACE_NO_INDENT();

  int x, y;

  FOR_ALL_MAP_POINTS(g, v, l, x, y)
  {
    spoint p(x, y);
    if (! level_is_water(g, v, l, p)) {
      continue;
    }

    FOR_ALL_THINGS_AT(g, v, l, t, p)
    {
      //
      // Skip dead monsters that take damage from water and leave a corpse?
      //
      if (thing_is_dead(t)) {
        continue;
      }

      if (! thing_is_physics_water(t)) {
        continue;
      }

      if (thing_is_loggable(t)) {
        THING_DBG(t, "over water");
      }

      thing_water_handle(g, v, l, t);
    }
  }
}
