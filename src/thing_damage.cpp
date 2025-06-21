//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_game.hpp"
#include "my_level.hpp"
#include "my_main.hpp"
#include "my_types.hpp"
#include "my_random.hpp"
#include "my_tile.hpp"
#include "my_tp.hpp"

//
// Apply a damage type to a thing
//
void thing_damage(Gamep g, Levelsp v, Levelp l, Thingp t, ThingEvent &event)
{
  TRACE_NO_INDENT();

  if (thing_is_dead(t)) {
    return;
  }

  //
  // Log the reason for attack?
  //
  if (thing_is_loggable(t)) {
    if (event.reason.empty()) {
      THING_LOG(t, "damage");
    } else {
      THING_LOG(t, "damage, reason: %s", event.reason.c_str());
    }
  }

  //
  // Change the health
  //
  if (thing_health_decr(g, v, l, t, event.damage) <= 0) {
    thing_dead(g, v, l, t, event);
  }
}
