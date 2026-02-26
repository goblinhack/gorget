//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_thing_callbacks.hpp"
#include "my_thing_inlines.hpp"

//
// Returns true if the thing can move to this location
//
auto thing_can_move_to_attempt(Gamep g, Levelsp v, Levelp l, Thingp me, spoint to) -> bool
{
  TRACE();

  UNLIKELY if (is_oob(to)) {
    return false;
  }

  auto at = thing_at(me);
  if (to == at) {
    return true;
  }

  auto dx = to.x - at.x;
  auto dy = to.y - at.y;
  thing_set_dir_from_delta(me, dx, dy);

  return thing_can_move_to_check_if_is_possible(g, v, l, me, to);
}

//
// Returns true if for the purposes of AI, a monst would be able to move
// to this location. For a chasm, it is unlikely a monst would want to if
// it means falling to its demise.
//
auto thing_can_move_to_ai(Gamep g, Levelsp v, Levelp l, Thingp me, spoint to) -> bool
{
  TRACE();

  FOR_ALL_THINGS_AT_UNSAFE(g, v, l, it, to)
  {
    //
    // Allow walking over the dead
    //
    if (thing_is_dead(it)) {
      if (thing_is_obs_when_dead(it)) {
        return false;
      }
      continue;
    }

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
// Returns true if it is POSSIBLE for this thing to move to this location.
// e.g. it is possible for a chasm or monst to move into a chasm. Does not
// mean the monst wants to do that.
//
// We do not change direction upon this attempt; purely a check only
//
auto thing_can_move_to_check_if_is_possible(Gamep g, Levelsp v, Levelp l, Thingp me, spoint to) -> bool
{
  TRACE();

  FOR_ALL_THINGS_AT_UNSAFE(g, v, l, it, to)
  {
    //
    // Allow walking over the dead
    //
    if (thing_is_dead(it)) {
      if (thing_is_obs_when_dead(it)) {
        return false;
      }
      continue;
    }

    //
    // Walls are not always obstacles
    //
    if (thing_is_wall(it)) {
      if (thing_is_able_to_move_through_walls(me)) {
        continue;
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
auto thing_can_move_to_attempt_by_shoving(Gamep g, Levelsp v, Levelp l, Thingp me, spoint to) -> bool
{
  TRACE();

  UNLIKELY if (is_oob(to)) {
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
