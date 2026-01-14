//
// Copyright goblinhack@gmail.com
//

#include "math.h"
#include "my_callstack.hpp"
#include "my_level.hpp"
#include "my_main.hpp"
#include "my_thing_inlines.hpp"

#include <unordered_map>

//
// Handle things interacting with chasms
//
void level_tick_teleport(Gamep g, Levelsp v, Levelp l)
{
  TRACE_NO_INDENT();

  int x, y;

  std::unordered_map< ThingId, bool > processed;

  LOG("teleport check");
  FOR_ALL_MAP_POINTS(g, v, l, x, y)
  {
    spoint p(x, y);
    if (level_is_teleport(g, v, l, p)) {
      LOG("teleport check %d,%d", p.x, p.y);
      FOR_ALL_THINGS_AT(g, v, l, t, p)
      {
        auto at = thing_at(t);
        THING_DBG(t, "over teleport at %d,%d p %d,%d", at.x, at.y, p.x, p.y);
        if (processed[ t->id ]) {
          THING_DBG(t, "skip teleport at %d,%d p %d,%d", at.x, at.y, p.x, p.y);
          continue;
        }
        processed[ t->id ] = true;

        if (thing_is_teleport_blocked(t)) {
          THING_DBG(t, "skip2 teleport at %d,%d p %d,%d", at.x, at.y, p.x, p.y);
          continue;
        }

        thing_teleport(g, v, l, t);
      }
    }
  }
}
