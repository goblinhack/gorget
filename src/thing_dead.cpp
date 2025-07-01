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
// Initiate the death process
//
void thing_dead(Gamep g, Levelsp v, Levelp l, Thingp t, ThingEvent &e)
{
  TRACE_NO_INDENT();

  if (thing_is_dead(t)) {
    return;
  }

  //
  // Log the reason of demise?
  //
  if (thing_is_loggable(t)) {
    if (e.reason.empty()) {
      THING_LOG(t, "dead");
    } else {
      THING_LOG(t, "dead, reason: %s", e.reason.c_str());
    }
  }

  thing_is_dead_set(g, v, l, t);

  if (thing_is_corpse_on_death(t)) {
    //
    // Keep the thing on the map, but in dead state.
    //
    thing_is_corpse_set(g, v, l, t);
  } else {
    //
    // Schedule for removal from the map and freeing
    //
    thing_is_scheduled_for_cleanup_set(g, v, l, t);
  }
}

//
// Complete the death process
//
void thing_is_dead_handle(Gamep g, Levelsp v, Levelp l, Thingp t)
{
  TRACE_NO_INDENT();

  //
  // Update the animation, for example, flattened grass
  //
  t->anim_type = THING_ANIM_DEAD;
  thing_anim_init(g, v, l, t);

  //
  // Stop it moving
  //
  thing_move_finish(g, v, l, t);

  //
  // Restart the animation if we have dead frames
  //
  thing_anim_reset(g, v, l, t);
}
