//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_thing_inlines.hpp"

//
// Open doors
//
auto thing_open(Gamep g, Levelsp v, Levelp l, Thingp me, Thingp player_or_monst) -> bool
{
  TRACE_NO_INDENT();

  if (! thing_is_player(player_or_monst) && ! thing_is_monst(player_or_monst)) {
    THING_ERR(player_or_monst, "unexpected thing for %s", __FUNCTION__);
    return false;
  }

  if (! thing_is_openable(me)) {
    return false;
  }

  bool const success = thing_is_open_try_set(g, v, l, me, player_or_monst);
  if (success) {
    if (thing_is_player(player_or_monst)) {
      level_tick_begin_requested(g, v, l, "player opened something");
      THING_LOG(player_or_monst, "opened %s", to_string(g, v, l, me).c_str());
    }
  }

  return success;
}

//
// Close doors
//
auto thing_close(Gamep g, Levelsp v, Levelp l, Thingp me, Thingp player_or_monst) -> bool
{
  TRACE_NO_INDENT();

  if (! thing_is_player(player_or_monst) && ! thing_is_monst(player_or_monst)) {
    THING_ERR(player_or_monst, "unexpected thing for %s", __FUNCTION__);
    return false;
  }

  if (! thing_is_openable(me)) {
    return false;
  }

  bool const success = thing_is_open_try_unset(g, v, l, me, player_or_monst);
  if (success) {
    if (thing_is_player(player_or_monst)) {
      level_tick_begin_requested(g, v, l, "player closed something");
      THING_LOG(player_or_monst, "closed %s", to_string(g, v, l, me).c_str());
    }
  }

  return success;
}

//
// Returns true if we can move to this location by opening a door
//
auto thing_can_move_to_attempt_by_opening(Gamep g, Levelsp v, Levelp l, Thingp me, spoint to) -> bool
{
  TRACE_NO_INDENT();

  if (IS_OOB(to)) {
    return false;
  }

  if (to == thing_at(me)) {
    return true;
  }

  auto at = thing_at(me);
  auto dx = to.x - at.x;
  auto dy = to.y - at.y;
  thing_set_dir_from_delta(me, dx, dy);

  if (! thing_is_able_to_open(me)) {
    return false;
  }

  FOR_ALL_THINGS_AT(g, v, l, it, to)
  {
    //
    // A wall or pillar or somesuch?
    //
    if (thing_is_obs_to_movement(it)) {
      //
      // But make exceptions for things like doors
      //
      if (thing_is_openable(it)) {
        if (thing_open(g, v, l, it, me)) {
          return true;
        }
      }

      return false;
    }
  }

  return true;
}
