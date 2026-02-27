//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_level.hpp"
#include "my_level_inlines.hpp"
#include "my_thing_inlines.hpp"

//
// Handle things interacting with chasms
//
// This is needed for special cases that do not normally do collision detection e.g.
// - fire spawned on top of a teleport
//
void level_tick_teleport(Gamep g, Levelsp v, Levelp l)
{
  TRACE();

  int x = 0;
  int y = 0;

  FOR_ALL_MAP_POINTS(g, v, l, x, y)
  {
    spoint p(x, y);
    if (level_is_teleport(g, v, l, p) != nullptr) {
      FOR_ALL_THINGS_AT(g, v, l, t, p)
      {
        if (! thing_is_able_to_fall(t)) {
          continue;
        }

        THING_DBG(t, "over teleport");

        (void) thing_teleport_handle(g, v, l, t);
      }
    }
  }
}
