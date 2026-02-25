//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_level.hpp"
#include "my_thing_inlines.hpp"

//
// Handle things interacting with chasms
//
// This is needed for special cases that do not normally do collision detection e.g.
// - a bridge that is suddenly over a chasm due to the bridge burning
// - a thing that has fallen through a chasm but has landed on a chasm again
//
void level_tick_chasm(Gamep g, Levelsp v, Levelp l)
{
  TRACE_NO_INDENT();

  int x = 0;
  int y = 0;

  FOR_ALL_MAP_POINTS(g, v, l, x, y)
  {
    spoint p(x, y);
    if (level_is_chasm(g, v, l, p) != nullptr) {
      FOR_ALL_THINGS_AT(g, v, l, t, p)
      {
        if (! thing_is_able_to_fall(t)) {
          continue;
        }

        THING_DBG(t, "over chasm");

        thing_chasm_handle(g, v, l, t);
      }
    }
  }
}
