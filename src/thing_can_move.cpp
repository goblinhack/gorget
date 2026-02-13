//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_thing_callbacks.hpp"
#include "my_thing_inlines.hpp"

//
// Returns true if the thing can move to this location
//
bool thing_can_move_to_attempt(Gamep g, Levelsp v, Levelp l, Thingp me, spoint to)
{
  TRACE_NO_INDENT();

  if (is_oob(to)) {
    return false;
  }

  auto at = thing_at(me);
  if (to == at) {
    return true;
  }

  auto dx = to.x - at.x;
  auto dy = to.y - at.y;
  thing_set_dir_from_delta(me, dx, dy);

  return thing_can_move_to_check_only(g, v, l, me, to);
}

//
// Returns true if the thing can move to this location
//
// We do not change direction upon this attempt; purely a check only
//
bool thing_can_move_to_check_only(Gamep g, Levelsp v, Levelp l, Thingp me, spoint to)
{
  TRACE_NO_INDENT();

  FOR_ALL_THINGS_AT_UNSAFE(g, v, l, it, to)
  {
    //
    // Walls are not always obstacles
    //
    if (thing_is_wall(it)) {
      if (thing_is_able_to_move_through_walls(me)) {
        continue;
      }
    }

    //
    // Chasms are obstacles only if you can fall into them
    //
    if (thing_is_chasm(it)) {
      if (! thing_is_able_to_fall(me)) {
        continue;
      }

      if (thing_is_floating(me)) {
        continue;
      }

      if (thing_is_able_to_jump(me)) {
        continue;
      }

      if (0)
        return false;
    }

    if (unlikely(it == me)) {
      continue;
    }

    //
    // No stacking of ghosts
    //
    if (thing_is_ethereal(me)) {
      if (thing_is_ethereal(it)) {
        return false;
      }
    }

    //
    // No stacking of monsters
    //
    if (thing_is_monst(me)) {
      if (thing_is_monst(it)) {
        return false;
      }
    }

    //
    // A wall or pillar or somesuch?
    //
    if (thing_is_obs_to_movement(it)) {
      return false;
    }
  }

  return true;
}

//
// Returns true if we can move to this location by shoving
//
bool thing_can_move_to_attempt_by_shoving(Gamep g, Levelsp v, Levelp l, Thingp me, spoint to)
{
  TRACE_NO_INDENT();

  if (is_oob(to)) {
    return false;
  }

  auto at = thing_at(me);
  if (to == at) {
    return true;
  }

  auto dx = to.x - at.x;
  auto dy = to.y - at.y;
  thing_set_dir_from_delta(me, dx, dy);

  if (! thing_is_able_to_shove(me)) {
    return false;
  }

  FOR_ALL_THINGS_AT(g, v, l, it, to)
  {
    //
    // A wall or pillar or somesuch?
    //
    if (thing_is_obs_to_movement(it)) {
      //
      // But make exceptions for things like braziers
      //
      if (thing_is_shovable(it)) {
        continue;
      }

      return false;
    }
  }

  return true;
}
