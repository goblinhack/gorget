//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_dice.hpp"
#include "my_level.hpp"
#include "my_main.hpp"
#include "my_random.hpp"
#include "my_ui.hpp"

//
// Open doors
//
bool thing_open(Gamep g, Levelsp v, Levelp l, Thingp t, Thingp opener)
{
  TRACE_NO_INDENT();

  if (! thing_is_openable(t)) {
    return false;
  }

  return thing_is_open_try_set(g, v, l, t, opener);
}

//
// Close doors
//
bool thing_close(Gamep g, Levelsp v, Levelp l, Thingp t, Thingp closer)
{
  TRACE_NO_INDENT();

  if (! thing_is_openable(t)) {
    return false;
  }

  return thing_is_open_try_unset(g, v, l, t, closer);
}

//
// Returns true if we can move to this location by opening a door
//
bool thing_can_move_to_by_opening(Gamep g, Levelsp v, Levelp l, Thingp t, spoint to)
{
  TRACE_NO_INDENT();

  if (is_oob(to)) {
    return false;
  }

  if (to == t->at) {
    return true;
  }

  auto dx = to.x - t->at.x;
  auto dy = to.y - t->at.y;
  thing_set_dir_from_delta(t, dx, dy);

  FOR_ALL_THINGS_AT(g, v, l, it, to)
  {
    //
    // A wall or pillar or somesuch?
    //
    if (thing_is_obs_to_movement(it)) {
      //
      // But make exceptions for things like doors
      //
      if (thing_is_able_to_open(t)) {
        if (thing_is_openable(it)) {
          if (thing_open(g, v, l, it, t)) {
            return true;
          }
        }
      }

      return false;
    }
  }

  return true;
}
