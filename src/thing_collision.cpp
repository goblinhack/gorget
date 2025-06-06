//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_game.hpp"
#include "my_level.hpp"
#include "my_main.hpp"
#include "my_minimal.hpp"
#include "my_tile.hpp"
#include "my_tp.hpp"

#include <string.h>

//
// Handle interactions for a thing at its location with a dead thing
//
static void thing_collision_handle_dead_thing(Gamep g, Levelsp v, Levelp l, Thingp it, Thingp me)
{
  TRACE_NO_INDENT();

  //
  // TODO
  //
}

//
// Handle interactions for a thing at its location with an alive thing
//
static void thing_collision_handle_alive_thing(Gamep g, Levelsp v, Levelp l, Thingp it, Thingp me)
{
  TRACE_NO_INDENT();

  //
  // Is this grass that needs to be flattened?
  //
  if (thing_is_crushable_underfoot(it) && (thing_weight(me) > 10)) {
    //
    // Crush it
    //
    thing_dead(g, v, l, it, me, "by crushing");
  }
}

//
// Handle interactions for a thing at its location
//
void thing_collision_handle(Gamep g, Levelsp v, Levelp l, Thingp me)
{
  TRACE_NO_INDENT();

  //
  // Handle player specific actions first, like leaving levels
  //
  if (thing_is_player(me)) {
    thing_player_collision_handle(g, v, l, me);
    if (thing_is_dead(me)) {
      return;
    }
  }

  //
  // Common collision handling for player and anything else
  //
  FOR_ALL_THINGS_AND_TPS_AT(g, v, l, it, it_tp, me->at)
  {
    if (thing_is_dead(it)) {
      //
      // Dead things
      //
      thing_collision_handle_dead_thing(g, v, l, it, me);
    } else {
      //
      // Alive things
      //
      thing_collision_handle_alive_thing(g, v, l, it, me);
    }
  }
}
