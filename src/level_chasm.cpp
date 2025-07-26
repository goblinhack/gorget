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
// Handle things interacting with chasms
//
void level_tick_begin_chasm(Gamep g, Levelsp v, Levelp l)
{
  TRACE_NO_INDENT();

  int x, y;

  FOR_ALL_MAP_POINTS(g, v, l, x, y)
  {
    spoint p(x, y);
    if (! level_is_chasm(g, v, l, p)) {
      continue;
    }

    FOR_ALL_THINGS_AT(g, v, l, t, p)
    {
      if (! thing_is_physics_gravity(t)) {
        continue;
      }

      if (thing_is_loggable(t)) {
        THING_DBG(t, "over chasm");
      }

      thing_chasm_handle(g, v, l, t);
    }
  }
}
