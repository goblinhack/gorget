//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_level.hpp"

//
// Handle interactions for a thing at its location with a dead thing
//
static void thing_collision_handle_dead_thing(Gamep g, Levelsp v, Levelp l, Thingp me, Thingp it)
{
  TRACE_NO_INDENT();

  //
  // TODO
  //
}

//
// Handle interactions for a thing at its location with an alive thing
//
static void thing_collision_handle_alive_thing(Gamep g, Levelsp v, Levelp l, Thingp me, Thingp it)
{
  TRACE_NO_INDENT();

  //
  // Crush it
  //
  if (thing_crush(g, v, l, me, it)) {
    return;
  }

  //
  // Collect keys?
  //
  if (thing_collect_key(g, v, l, me, it)) {
    return;
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
      thing_collision_handle_dead_thing(g, v, l, me, it);
    } else {
      //
      // Alive things
      //
      thing_collision_handle_alive_thing(g, v, l, me, it);
    }
  }
}
