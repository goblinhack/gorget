//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_level.hpp"
#include "my_thing_inlines.hpp"

//
// Handle things interacting with explosion
//
void level_tick_explosion(Gamep g, Levelsp v, Levelp l)
{
  TRACE_NO_INDENT();

  int x;
  int y;

  FOR_ALL_MAP_POINTS(g, v, l, x, y)
  {
    spoint p(x, y);
    if (! level_is_explosion(g, v, l, p)) {
      continue;
    }

    FOR_ALL_THINGS_AT(g, v, l, t, p)
    {
      //
      // Skip dead monsters that take damage from explosion and leave a corpse?
      //
      if (thing_is_dead(t)) {
        continue;
      }

      if (! thing_is_physics_explosion(t)) {
        continue;
      }

      THING_DBG(t, "over explosion");

      thing_explosion_handle(g, v, l, t);
    }
  }
}
