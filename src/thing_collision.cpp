//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_game.hpp"
#include "my_level.hpp"
#include "my_main.hpp"
#include "my_tile.hpp"
#include "my_tp.hpp"
#include "my_types.hpp"

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
  if (thing_is_crushable(it) && (thing_weight(me) > 10)) {
    //
    // Crush it
    //
    ThingEvent e {
        .reason     = "by crushing",     //
        .event_type = THING_EVENT_CRUSH, //
        .source     = me                 //
    };
    thing_dead(g, v, l, it, e);
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
    player_collision_handle(g, v, l, me);
    if (thing_is_dead(me)) {
      return;
    }
  }

  if (thing_is_ethereal(me)) {
    return;
  }

  //
  // Common collision handling for player and anything else
  //
  FOR_ALL_THINGS_AT(g, v, l, it, me->at)
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
