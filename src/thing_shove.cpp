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
static bool thing_shove_handle_dead_thing(Gamep g, Levelsp v, Levelp l, Thingp it, Thingp me, point from, point to,
                                          point direction)
{
  TRACE_NO_INDENT();

  bool ret = false;

  if (thing_can_move_to(g, v, l, it, to)) {
    if (thing_move_to(g, v, l, it, to)) {
      ret = true;
    }
  }

  return ret;
}

//
// Handle interactions for a thing at its location with an alive thing
//
static bool thing_shove_handle_alive_thing(Gamep g, Levelsp v, Levelp l, Thingp it, Thingp me, point from, point to,
                                           point direction)
{
  TRACE_NO_INDENT();

  bool ret = false;

  //
  // Some items, like braziers need to be knocked over first before shoving.
  //
  if (thing_is_dead_on_shoving(it)) {
    ThingEvent e {.reason = "by shoving", .attacker = me};
    thing_dead(g, v, l, it, e);
    return true;
  }

  if (thing_can_move_to(g, v, l, it, to)) {
    if (thing_move_to(g, v, l, it, to)) {
      ret = true;
    }
  }

  return ret;
}

//
// Can we shove something at the location "at"
//
// Returns true on success at shoving something
//
bool thing_shove_handle(Gamep g, Levelsp v, Levelp l, Thingp me, point at)
{
  TRACE_NO_INDENT();

  bool  ret       = false;
  auto  direction = at - me->at;
  point from      = at;
  point to        = at + direction;

  if (thing_is_ethereal(me)) {
    return false;
  }

  if (! thing_is_able_to_shove(me)) {
    return false;
  }

  //
  // Common shove handling for player and anything else
  //
  FOR_ALL_THINGS_AT(g, v, l, it, at)
  {

    if (! thing_is_shovable(it)) {
      continue;
    }

    if (thing_is_dead(it)) {
      //
      // Dead things
      //
      if (thing_shove_handle_dead_thing(g, v, l, it, me, from, to, direction)) {
        ret = true;
      }
    } else {
      //
      // Alive things
      //
      if (thing_shove_handle_alive_thing(g, v, l, it, me, from, to, direction)) {
        ret = true;
      }
    }
  }

  return ret;
}
