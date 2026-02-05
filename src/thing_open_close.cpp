//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_thing_inlines.hpp"

//
// Open doors
//
bool thing_open(Gamep g, Levelsp v, Levelp l, Thingp t, Thingp player_or_monst)
{
  TRACE_NO_INDENT();

  if (! thing_is_player(player_or_monst) && ! thing_is_monst(player_or_monst)) {
    THING_ERR(player_or_monst, "unexpected thing for %s", __FUNCTION__);
    return false;
  }

  if (! thing_is_openable(t)) {
    return false;
  }

  bool success = thing_is_open_try_set(g, v, l, t, player_or_monst);
  if (success) {
    if (thing_is_player(player_or_monst)) {
      level_tick_begin_requested(g, v, l, "player opened something");
      THING_LOG(player_or_monst, "opened %s", to_string(g, v, l, t).c_str());
    }
  }

  return success;
}

//
// Close doors
//
bool thing_close(Gamep g, Levelsp v, Levelp l, Thingp t, Thingp player_or_monst)
{
  TRACE_NO_INDENT();

  if (! thing_is_player(player_or_monst) && ! thing_is_monst(player_or_monst)) {
    THING_ERR(player_or_monst, "unexpected thing for %s", __FUNCTION__);
    return false;
  }

  if (! thing_is_openable(t)) {
    return false;
  }

  bool success = thing_is_open_try_unset(g, v, l, t, player_or_monst);
  if (success) {
    if (thing_is_player(player_or_monst)) {
      level_tick_begin_requested(g, v, l, "player closed something");
      THING_LOG(player_or_monst, "closed %s", to_string(g, v, l, t).c_str());
    }
  }

  return success;
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

  if (to == thing_at(t)) {
    return true;
  }

  auto at = thing_at(t);
  auto dx = to.x - at.x;
  auto dy = to.y - at.y;
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
