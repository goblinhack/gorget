//
// Copyright goblinhack@gmail.com
//

#include "math.h"
#include "my_callstack.hpp"
#include "my_level.hpp"

#include <unordered_map>

//
// Handle things interacting with chasms
//
void level_tick_end_teleport(Gamep g, Levelsp v, Levelp l)
{
  TRACE_NO_INDENT();

  int x, y;

  std::unordered_map< ThingId, bool > processed;

  FOR_ALL_MAP_POINTS(g, v, l, x, y)
  {
    spoint p(x, y);
    if (level_is_teleport(g, v, l, p)) {
      FOR_ALL_THINGS_AT(g, v, l, t, p)
      {
        if (processed[ t->id ]) {
          continue;
        }
        processed[ t->id ] = true;

        if (thing_is_loggable(t)) {
          THING_DBG(t, "over teleport");
        }

        thing_teleport(g, v, l, t);
      }
    }
  }
}
