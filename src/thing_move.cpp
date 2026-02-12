//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_thing_callbacks.hpp"
#include "my_thing_inlines.hpp"

//
// Get thing direction
//
bool thing_is_dir_br(Thingp me) { return (me->dir == THING_DIR_BR); }
bool thing_is_dir_tr(Thingp me) { return (me->dir == THING_DIR_TR); }
bool thing_is_dir_bl(Thingp me) { return (me->dir == THING_DIR_BL); }
bool thing_is_dir_tl(Thingp me) { return (me->dir == THING_DIR_TL); }
bool thing_is_dir_right(Thingp me) { return (me->dir == THING_DIR_RIGHT); }
bool thing_is_dir_none(Thingp me) { return (me->dir == THING_DIR_NONE); }
bool thing_is_dir_down(Thingp me) { return (me->dir == THING_DIR_DOWN); }
bool thing_is_dir_up(Thingp me) { return (me->dir == THING_DIR_UP); }
bool thing_is_dir_left(Thingp me) { return (me->dir == THING_DIR_LEFT); }

//
// Set thing direction
//
void thing_dir_set_none(Thingp me)
{
  TRACE_NO_INDENT();

  if (tp_is_animated_no_dir(thing_tp(me))) {
    return;
  }

  if (me->dir != THING_DIR_NONE) {
    me->dir = THING_DIR_NONE;
    // move_carried_items();
  }
}

//
// Set thing direction
//
void thing_dir_set_down(Thingp me)
{
  TRACE_NO_INDENT();

  if (tp_is_animated_no_dir(thing_tp(me))) {
    return;
  }

  if (me->dir != THING_DIR_DOWN) {
    me->dir = THING_DIR_DOWN;
    // move_carried_items();
  }
}

//
// Set thing direction
//
void thing_dir_set_up(Thingp me)
{
  TRACE_NO_INDENT();

  if (tp_is_animated_no_dir(thing_tp(me))) {
    return;
  }

  if (me->dir != THING_DIR_UP) {
    me->dir = THING_DIR_UP;
    // move_carried_items();
  }
}

//
// Set thing direction
//
void thing_dir_set_left(Thingp me)
{
  TRACE_NO_INDENT();

  if (tp_is_animated_no_dir(thing_tp(me))) {
    return;
  }

  if (me->dir != THING_DIR_LEFT) {
    me->dir = THING_DIR_LEFT;
    // move_carried_items();
  }
}

//
// Set thing direction
//
void thing_dir_set_right(Thingp me)
{
  TRACE_NO_INDENT();

  if (tp_is_animated_no_dir(thing_tp(me))) {
    return;
  }

  if (me->dir != THING_DIR_RIGHT) {
    me->dir = THING_DIR_RIGHT;
    // move_carried_items();
  }
}

//
// Set thing direction
//
void thing_dir_set_tl(Thingp me)
{
  TRACE_NO_INDENT();

  if (tp_is_animated_no_dir(thing_tp(me))) {
    return;
  }

  if (me->dir != THING_DIR_TL) {
    me->dir = THING_DIR_TL;
    // move_carried_items();
  }
}

//
// Set thing direction
//
void thing_dir_set_bl(Thingp me)
{
  TRACE_NO_INDENT();

  if (tp_is_animated_no_dir(thing_tp(me))) {
    return;
  }

  if (me->dir != THING_DIR_BL) {
    me->dir = THING_DIR_BL;
    // move_carried_items();
  }
}

//
// Set thing direction
//
void thing_dir_set_tr(Thingp me)
{
  TRACE_NO_INDENT();

  if (tp_is_animated_no_dir(thing_tp(me))) {
    return;
  }

  if (me->dir != THING_DIR_TR) {
    me->dir = THING_DIR_TR;
    // move_carried_items();
  }
}

//
// Set thing direction
//
void thing_dir_set_br(Thingp me)
{
  TRACE_NO_INDENT();

  if (tp_is_animated_no_dir(thing_tp(me))) {
    return;
  }

  if (me->dir != THING_DIR_BR) {
    me->dir = THING_DIR_BR;
    // move_carried_items();
  }
}

//
// Set tile direction from delta
//
void thing_set_dir_from_delta(Thingp me, int dx, int dy)
{
  TRACE_NO_INDENT();

  if (dx < 0) {
    if (dy > 0) {
      thing_dir_set_bl(me);
    } else if (dy < 0) {
      thing_dir_set_tl(me);
    } else {
      thing_dir_set_left(me);
    }
    return;
  }

  if (dx > 0) {
    if (dy > 0) {
      thing_dir_set_br(me);
    } else if (dy < 0) {
      thing_dir_set_tr(me);
    } else {
      thing_dir_set_right(me);
    }
    return;
  }

  if (dy > 0) {
    if (dx > 0) {
      thing_dir_set_br(me);
    } else if (dx < 0) {
      thing_dir_set_bl(me);
    } else {
      thing_dir_set_down(me);
    }
    return;
  }

  if (dy < 0) {
    if (dx > 0) {
      thing_dir_set_tr(me);
    } else if (dx < 0) {
      thing_dir_set_tl(me);
    } else {
      thing_dir_set_up(me);
    }
    return;
  }
}

//
// Get direction; need to also account for projectiles that move at an angle.
//
fpoint thing_get_direction(Gamep g, Levelsp v, Levelp l, Thingp me)
{
  TRACE_NO_INDENT();

  if (thing_is_projectile(me)) {
    return thing_projectile_get_direction(g, v, l, me);
  }

  switch (me->dir) {
    case THING_DIR_BR :    return fpoint(1, 1);
    case THING_DIR_TR :    return fpoint(1, -1);
    case THING_DIR_BL :    return fpoint(-1, 1);
    case THING_DIR_TL :    return fpoint(-1, -1);
    case THING_DIR_RIGHT : return fpoint(1, 0);
    case THING_DIR_NONE :  return fpoint(0, 0);
    case THING_DIR_DOWN :  return fpoint(0, 1);
    case THING_DIR_UP :    return fpoint(0, -1);
    case THING_DIR_LEFT :  return fpoint(-1, 0);
    default :              return fpoint(0, 0);
  }
}

//
// Handles manual and mouse follow moves
//
bool thing_move_to(Gamep g, Levelsp v, Levelp l, Thingp me, spoint to)
{
  TRACE_NO_INDENT();

  if (is_oob(to)) {
    return false;
  }

  auto at = thing_at(me);
  if (to == at) {
    return false;
  }

  thing_pop(g, v, me);

  spoint pix_at;
  pix_at.x = at.x * TILE_WIDTH;
  pix_at.y = at.y * TILE_HEIGHT;

  thing_pix_at_set(g, v, l, me, pix_at);
  thing_moving_from_set(me, at);
  thing_at_set(me, to);
  (void) thing_push(g, v, l, me);

  thing_is_moving_set(g, v, l, me);
  THING_LOG(me, "move to");

  return true;
}

//
// Handles shoving to a location. We can'me move there yet.
//
bool thing_shove_to(Gamep g, Levelsp v, Levelp l, Thingp me, spoint to)
{
  TRACE_NO_INDENT();

  if (is_oob(to)) {
    return false;
  }

  auto at = thing_at(me);
  if (to == at) {
    return false;
  }

  auto ret = thing_shove_handle(g, v, l, me, to);
  if (ret) {
    THING_LOG(me, "shoved");
  } else {
    THING_LOG(me, "failed to shove");
  }

  return ret;
}

//
// Handles immediate moves even across levels.
//
bool thing_warp_to(Gamep g, Levelsp v, Levelp new_level, Thingp me, spoint to)
{
  TRACE_NO_INDENT();

  if (is_oob(to)) {
    return false;
  }

  THING_LOG(me, "pre teleport");

  bool level_changed = false;
  auto old_level     = thing_level(g, v, me);

  //
  // Need to reset vision when leaving a level
  //
  if (old_level != new_level) {
    level_changed = true;
  }

  if (level_changed) {
    thing_on_level_leave(g, v, old_level, me);
  }

  //
  // Check if already present at the destination.
  //
  auto at = thing_at(me);
  if ((new_level == old_level) && (to == at)) {
    //
    // No need to pop. If might be an inventory item though, so make sure and push
    // it onto the map after this check.
    //
  } else {
    //
    // If the player is following a path and we teleport warp, then we want to stop
    // following that path.
    //
    if (thing_is_player(me)) {
      player_state_change(g, v, old_level, PLAYER_STATE_NORMAL);
    }

    //
    // Complete the current move
    //
    thing_move_or_jump_finish(g, v, old_level, me);

    //
    // Remove from the current level or position
    //
    thing_pop(g, v, me);
  }

  spoint pix_at;
  pix_at.x = at.x * TILE_WIDTH;
  pix_at.y = at.y * TILE_HEIGHT;

  thing_pix_at_set(g, v, new_level, me, pix_at);
  thing_at_set(me, to);

  //
  // Join the level.
  //
  (void) thing_push(g, v, new_level, me);

  //
  // Need to update with the new pixel position
  //
  thing_update_pos(g, v, new_level, me);

  //
  // For a time period e.g. post teleport, we want to ignore mouse moves until the player is
  // centered once more.
  //
  if (thing_is_player(me)) {
    level_forced_auto_scroll(g, v, new_level);
  }

  //
  // Enter the new level callback. Do this after updating position so that light update works.
  //
  if (level_changed) {
    thing_on_level_enter(g, v, new_level, me);
  }

  //
  // In case of level change or teleport, need to update things
  //
  if (thing_is_player(me)) {
    //
    // Update minimaps and lighting
    //
    level_update_visibility(g, v, new_level);
  }

  new_level->is_tick_requested = true;

  THING_LOG(me, "teleported");

  return true;
}

//
// Move to the next tile is completed. Need to stop interpolating.
// There could be more tiles to pop.
//
void thing_move_or_jump_finish(Gamep g, Levelsp v, Levelp l, Thingp me)
{
  TRACE_NO_INDENT();

  auto player_struct = thing_player_struct(g);
  if (! player_struct) {
    return;
  }

  auto at = thing_at(me);
  (void) thing_moving_from_set(me, at);

  thing_is_teleporting_unset(g, v, l, me);
  thing_is_moving_unset(g, v, l, me);
  thing_is_jumping_unset(g, v, l, me);
  thing_dmap(g, v, l, me);
}

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

  FOR_ALL_THINGS_AT(g, v, l, it, to)
  {
    //
    // Walls are not always obstacles
    //
    if (thing_is_wall(it)) {
      if (thing_is_able_to_move_through_walls(me)) {
        continue;
      }
    }

    if (unlikely(it == me)) {
      continue;
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

//
// Post init/warp, we need to update the position so we can determine the level draw bounds
//
void thing_update_pos(Gamep g, Levelsp v, Levelp l, Thingp me)
{
  TRACE_NO_INDENT();

  auto   real_at = thing_real_at(me);
  spoint pix_at;
  pix_at.x = (int) (real_at.x * (float) TILE_WIDTH);
  pix_at.y = (int) (real_at.y * (float) TILE_HEIGHT);
  (void) thing_pix_at_set(g, v, l, me, pix_at);
}
