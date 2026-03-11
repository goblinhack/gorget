//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_game.hpp"
#include "my_globals.hpp"
#include "my_level_inlines.hpp"
#include "my_main.hpp"
#include "my_thing_callbacks.hpp"
#include "my_thing_inlines.hpp"
#include "my_ui.hpp"

//
// Allowed to place a corpse here?
//
bool thing_corpse_allowed(Gamep g, Levelsp v, Levelp l, Thingp t)
{
  TRACE();

  auto tp = thing_tp(t);

  //
  // Leaves a corpse?
  //
  if (! thing_is_corpse_on_death(t)) {
    return false;
  }

  //
  // Look for other corpses
  //
  auto corpse_count = 0;

  FOR_ALL_THINGS_AT_UNSAFE(g, v, l, o, thing_at(t))
  {
    if (o == t) {
      continue;
    }

    //
    // If there is a corpse of the same thing here, then avoid corpse pileup of similar things
    //
    if (thing_is_dead(o)) {
      if (tp == thing_tp(o)) {
        return false;
      }

      corpse_count++;
    }

    //
    // Again, but across species
    //
    if (corpse_count > MAX_CORPSES_PER_TILE) {
      return false;
    }
  }

  return true;
}
