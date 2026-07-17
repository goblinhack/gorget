//
// Copyright goblinhack@gmail.com
//

#include "my_bpoint.hpp"
#include "my_callstack.hpp"
#include "my_level.hpp"
#include "my_level_inlines.hpp"
#include "my_main.hpp"
#include "my_thing.hpp"
#include "my_thing_callbacks.hpp"
#include "my_thing_inlines.hpp"
#include "my_tp.hpp"
#include "my_types.hpp"

//
// Returns true/false on success/fail
//
[[nodiscard]] auto thing_is_engulfed_try_set(Gamep g, Levelsp v, Levelp l, Thingp t, Thingp engulfer, bool val = true) -> bool
{
  THING_DBG(g, v, l, t, "%s", __FUNCTION__);
  TRACE_INDENT();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }

  if (t->_is_engulfed == static_cast< int >(val)) {
    return true;
  }
  t->_is_engulfed = val;

  //
  // Attempt the engulf. It can fail.
  //
  if (val) {
    //
    // Try to engulf
    //
    if (! thing_on_engulf_request(g, v, l, t, engulfer)) {
      //
      // Engulf failed
      //
      THING_DBG(g, v, l, t, "engulf failed");
      t->_is_engulfed = false;
      return false;
    }

    //
    // Reset animation
    //
    THING_DBG(g, v, l, t, "engulf success");
    thing_anim_init(g, v, l, t, THING_ANIM_IDLE);
  } else {
    //
    // Un-engulfed
    //
    THING_DBG(g, v, l, t, "un-engulf success");
    thing_anim_init(g, v, l, t, THING_ANIM_IDLE);
  }

  return true;
}

[[nodiscard]] auto thing_is_engulfed_try_unset(Gamep g, Levelsp v, Levelp l, Thingp t, Thingp engulfer) -> bool
{
  TRACE_DEBUG();

  return thing_is_engulfed_try_set(g, v, l, t, engulfer, false);
}

//
// Engulf things
//
[[nodiscard]] auto thing_engulf(Gamep g, Levelsp v, Levelp l, Thingp me, Thingp engulfer) -> bool
{
  THING_DBG(g, v, l, me, "%s", __FUNCTION__);
  TRACE_INDENT();

  if (! thing_is_player(engulfer) && ! thing_is_monst(engulfer)) {
    thing_err(g, v, l, engulfer, "unexpected thing for %s", __FUNCTION__);
    return false;
  }

  if (! thing_is_able_to_be_engulfed(me)) {
    return false;
  }

  if (! thing_is_able_to_engulf(engulfer)) {
    return false;
  }

  bool const success = thing_is_engulfed_try_set(g, v, l, me, engulfer);
  if (success) {
    if (thing_is_player(engulfer)) {
      (void) level_tick_begin_requested(g, v, l, "player engulfed something");
      THING_DBG(g, v, l, engulfer, "engulfed %s", to_string(g, v, l, me).c_str());
    }
  }

  return success;
}

//
// Unengulf
//
[[nodiscard]] auto thing_unengulf(Gamep g, Levelsp v, Levelp l, Thingp me, Thingp engulfer) -> bool
{
  THING_DBG(g, v, l, me, "%s", __FUNCTION__);
  TRACE_INDENT();

  if (! thing_is_player(engulfer) && ! thing_is_monst(engulfer)) {
    thing_err(g, v, l, engulfer, "unexpected thing for %s", __FUNCTION__);
    return false;
  }

  if (! thing_is_able_to_be_engulfed(me)) {
    return false;
  }

  if (! thing_is_able_to_engulf(engulfer)) {
    return false;
  }

  if (! thing_is_engulfed(me)) {
    return false;
  }

  bool const success = thing_is_engulfed_try_unset(g, v, l, me, engulfer);
  if (success) {
    if (thing_is_player(engulfer)) {
      (void) level_tick_begin_requested(g, v, l, "player closed something");
      THING_DBG(g, v, l, engulfer, "closed %s", to_string(g, v, l, me).c_str());
    }
  }

  return success;
}

//
// Returns true if we can move to this location by engulfing a door
//
[[nodiscard]] auto thing_can_move_to_attempt_by_engulfing(Gamep g, Levelsp v, Levelp l, Thingp me, bpoint to) -> bool
{
  TRACE();

  if (is_oob_or_border(to)) [[unlikely]] {
    return false;
  }

  if (to == thing_at(g, v, l, me)) {
    return true;
  }

  auto at = thing_at(g, v, l, me);
  auto dx = to.x - at.x;
  auto dy = to.y - at.y;
  thing_set_dir_from_delta(g, v, l, me, dx, dy);

  if (! thing_is_able_to_engulf(me)) {
    (void) thing_lunge(g, v, l, me, to);
    return false;
  }

  //
  // Needs to be something we can engulf
  //
  if (! level_is_able_to_be_engulfed_bool(g, v, l, to)) {
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
      if (thing_is_able_to_be_engulfed(it)) {
        if (thing_engulf(g, v, l, it, me)) {
          return true;
        }
      }

      return false;
    }
  }

  return true;
}
