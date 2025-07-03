//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_game.hpp"
#include "my_level.hpp"
#include "my_main.hpp"
#include "my_random.hpp"
#include "my_tile.hpp"
#include "my_tp.hpp"
#include "my_types.hpp"

//
// Apply a damage type to a thing
//
void thing_damage(Gamep g, Levelsp v, Levelp l, Thingp t, ThingEvent &e)
{
  TRACE_AND_INDENT();

  if (thing_is_dead(t)) {
    //
    // Log the reason for attack?
    //
    if (thing_is_loggable(t)) {
      THING_LOG(t, "%s: no damage as already dead", to_string(e).c_str());
    }
    return;
  }

  //
  // Immune to this attack?
  //
  if (thing_is_immune_to(t, e.damage_type)) {
    if (thing_is_loggable(t)) {
      THING_LOG(t, "%s: no damage as immune", to_string(e).c_str());
    }
    return;
  }

  //
  // Log the reason for attack?
  //
  if (thing_is_loggable(t)) {
    THING_LOG(t, "%s: apply damage", to_string(e).c_str());
  }

  //
  // Change the health
  //
  if (thing_health_decr(g, v, l, t, e.damage) <= 0) {
    thing_dead(g, v, l, t, e);
  }

  THING_LOG(t, "post damage");
}
