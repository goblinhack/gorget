//
// Copyright goblinhack@gmail.com
//

#include "my_bpoint.hpp"
#include "my_callstack.hpp"
#include "my_level.hpp"
#include "my_level_inlines.hpp" // NOLINT
#include "my_thing.hpp"
#include "my_thing_inlines.hpp" // NOLINT
#include "my_types.hpp"

//
// Handle things interacting with water
//
void level_tick_water(Gamep g, Levelsp v, Levelp l)
{
  TRACE();

  int x = 0;
  int y = 0;

  level_log(g, v, l, "tick water");
  FOR_ALL_MAP_POINTS(g, v, l, x, y)
  {
    bpoint p(x, y);

    if (! level_is_water_bool(g, v, l, p)) {
      continue;
    }

    FOR_ALL_THINGS_AT(g, v, l, t, p)
    {
      if (! thing_is_physics_water(t)) {
        continue;
      }

      //
      // Skip dead monsters that take damage from water and leave a corpse?
      //
      if (thing_is_dead(t)) {
        continue;
      }

      thing_water_handle(g, v, l, t);
    }
  }
}
