//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_thing_callbacks.hpp"
#include "my_thing_inlines.hpp"

//
// Get thing direction
//
bool thing_is_dir_br(Thingp t) { return (t->dir == THING_DIR_BR); }
bool thing_is_dir_tr(Thingp t) { return (t->dir == THING_DIR_TR); }
bool thing_is_dir_bl(Thingp t) { return (t->dir == THING_DIR_BL); }
bool thing_is_dir_tl(Thingp t) { return (t->dir == THING_DIR_TL); }
bool thing_is_dir_right(Thingp t) { return (t->dir == THING_DIR_RIGHT); }
bool thing_is_dir_none(Thingp t) { return (t->dir == THING_DIR_NONE); }
bool thing_is_dir_down(Thingp t) { return (t->dir == THING_DIR_DOWN); }
bool thing_is_dir_up(Thingp t) { return (t->dir == THING_DIR_UP); }
bool thing_is_dir_left(Thingp t) { return (t->dir == THING_DIR_LEFT); }

//
// Set thing direction
//
void thing_dir_set_none(Thingp t)
{
  TRACE_NO_INDENT();

  if (tp_is_animated_no_dir(thing_tp(t))) {
    return;
  }

  if (t->dir != THING_DIR_NONE) {
    t->dir = THING_DIR_NONE;
    // move_carried_items();
  }
}

//
// Set thing direction
//
void thing_dir_set_down(Thingp t)
{
  TRACE_NO_INDENT();

  if (tp_is_animated_no_dir(thing_tp(t))) {
    return;
  }

  if (t->dir != THING_DIR_DOWN) {
    t->dir = THING_DIR_DOWN;
    // move_carried_items();
  }
}

//
// Set thing direction
//
void thing_dir_set_up(Thingp t)
{
  TRACE_NO_INDENT();

  if (tp_is_animated_no_dir(thing_tp(t))) {
    return;
  }

  if (t->dir != THING_DIR_UP) {
    t->dir = THING_DIR_UP;
    // move_carried_items();
  }
}

//
// Set thing direction
//
void thing_dir_set_left(Thingp t)
{
  TRACE_NO_INDENT();

  if (tp_is_animated_no_dir(thing_tp(t))) {
    return;
  }

  if (t->dir != THING_DIR_LEFT) {
    t->dir = THING_DIR_LEFT;
    // move_carried_items();
  }
}

//
// Set thing direction
//
void thing_dir_set_right(Thingp t)
{
  TRACE_NO_INDENT();

  if (tp_is_animated_no_dir(thing_tp(t))) {
    return;
  }

  if (t->dir != THING_DIR_RIGHT) {
    t->dir = THING_DIR_RIGHT;
    // move_carried_items();
  }
}

//
// Set thing direction
//
void thing_dir_set_tl(Thingp t)
{
  TRACE_NO_INDENT();

  if (tp_is_animated_no_dir(thing_tp(t))) {
    return;
  }

  if (t->dir != THING_DIR_TL) {
    t->dir = THING_DIR_TL;
    // move_carried_items();
  }
}

//
// Set thing direction
//
void thing_dir_set_bl(Thingp t)
{
  TRACE_NO_INDENT();

  if (tp_is_animated_no_dir(thing_tp(t))) {
    return;
  }

  if (t->dir != THING_DIR_BL) {
    t->dir = THING_DIR_BL;
    // move_carried_items();
  }
}

//
// Set thing direction
//
void thing_dir_set_tr(Thingp t)
{
  TRACE_NO_INDENT();

  if (tp_is_animated_no_dir(thing_tp(t))) {
    return;
  }

  if (t->dir != THING_DIR_TR) {
    t->dir = THING_DIR_TR;
    // move_carried_items();
  }
}

//
// Set thing direction
//
void thing_dir_set_br(Thingp t)
{
  TRACE_NO_INDENT();

  if (tp_is_animated_no_dir(thing_tp(t))) {
    return;
  }

  if (t->dir != THING_DIR_BR) {
    t->dir = THING_DIR_BR;
    // move_carried_items();
  }
}

//
// Set tile direction from delta
//
void thing_set_dir_from_delta(Thingp t, int dx, int dy)
{
  TRACE_NO_INDENT();

  if (dx < 0) {
    if (dy > 0) {
      thing_dir_set_bl(t);
    } else if (dy < 0) {
      thing_dir_set_tl(t);
    } else {
      thing_dir_set_left(t);
    }
    return;
  }

  if (dx > 0) {
    if (dy > 0) {
      thing_dir_set_br(t);
    } else if (dy < 0) {
      thing_dir_set_tr(t);
    } else {
      thing_dir_set_right(t);
    }
    return;
  }

  if (dy > 0) {
    if (dx > 0) {
      thing_dir_set_br(t);
    } else if (dx < 0) {
      thing_dir_set_bl(t);
    } else {
      thing_dir_set_down(t);
    }
    return;
  }

  if (dy < 0) {
    if (dx > 0) {
      thing_dir_set_tr(t);
    } else if (dx < 0) {
      thing_dir_set_tl(t);
    } else {
      thing_dir_set_up(t);
    }
    return;
  }
}

//
// Get direction; need to also account for projectiles that move at an angle.
//
fpoint thing_get_direction(Gamep g, Levelsp v, Levelp l, Thingp t)
{
  TRACE_NO_INDENT();

  if (thing_is_projectile(t)) {
    return thing_projectile_get_direction(g, v, l, t);
  }

  switch (t->dir) {
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
bool thing_move_to(Gamep g, Levelsp v, Levelp l, Thingp t, spoint to)
{
  TRACE_NO_INDENT();

  if (is_oob(to)) {
    return false;
  }

  auto at = thing_at(t);
  if (to == at) {
    return false;
  }

  thing_pop(g, v, t);

  spoint pix_at;
  pix_at.x = at.x * TILE_WIDTH;
  pix_at.y = at.y * TILE_HEIGHT;
  thing_pix_at_set(g, v, l, t, pix_at);

  (void) thing_moving_from_set(t, at);
  (void) thing_at_set(t, to);

  (void) thing_push(g, v, l, t);

  thing_is_moving_set(g, v, l, t);
  THING_LOG(t, "move to");

  return true;
}

//
// Handles shoving to a location. We can't move there yet.
//
bool thing_shove_to(Gamep g, Levelsp v, Levelp l, Thingp t, spoint to)
{
  TRACE_NO_INDENT();

  if (is_oob(to)) {
    return false;
  }

  auto at = thing_at(t);
  if (to == at) {
    return false;
  }

  auto ret = thing_shove_handle(g, v, l, t, to);
  if (ret) {
    THING_LOG(t, "shoved");
  } else {
    THING_LOG(t, "failed to shove");
  }

  return ret;
}

//
// Handles immediate moves even across levels.
//
bool thing_warp_to(Gamep g, Levelsp v, Levelp new_level, Thingp t, spoint to)
{
  TRACE_NO_INDENT();

  if (is_oob(to)) {
    return false;
  }

  THING_LOG(t, "pre teleport");

  bool level_changed = false;
  auto old_level     = thing_level(g, v, t);

  //
  // Need to reset vision when leaving a level
  //
  if (old_level != new_level) {
    level_changed = true;
  }

  if (level_changed) {
    thing_on_level_leave(g, v, old_level, t);
  }

  //
  // Check if already present at the destination.
  //
  auto at = thing_at(t);
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
    if (thing_is_player(t)) {
      player_state_change(g, v, PLAYER_STATE_NORMAL);
    }

    //
    // Complete the current move
    //
    thing_move_or_jump_finish(g, v, old_level, t);

    //
    // Remove from the current level or position
    //
    thing_pop(g, v, t);
  }

  spoint pix_at;
  pix_at.x = at.x * TILE_WIDTH;
  pix_at.y = at.y * TILE_HEIGHT;
  thing_pix_at_set(g, v, new_level, t, pix_at);

  (void) thing_at_set(t, to);

  //
  // Join the level.
  //
  (void) thing_push(g, v, new_level, t);

  //
  // Need to update with the new pixel position
  //
  thing_update_pos(g, v, new_level, t);

  //
  // For a time period e.g. post teleport, we want to ignore mouse moves until the player is
  // centered once more.
  //
  if (thing_is_player(t)) {
    level_forced_auto_scroll(g, v, new_level);
  }

  //
  // Enter the new level callback. Do this after updating position so that light update works.
  //
  if (level_changed) {
    thing_on_level_enter(g, v, new_level, t);
  }

  //
  // In case of level change or teleport, need to update things
  //
  if (thing_is_player(t)) {
    //
    // Update minimaps and lighting
    //
    level_update_visibility(g, v, new_level);
  }

  new_level->is_tick_requested = true;

  THING_LOG(t, "teleported");

  return true;
}

//
// Move to the next tile is completed. Need to stop interpolating.
// There could be more tiles to pop.
//
void thing_move_or_jump_finish(Gamep g, Levelsp v, Levelp l, Thingp t)
{
  TRACE_NO_INDENT();

  auto player_struct = thing_player_struct(g);
  if (! player_struct) {
    return;
  }

  auto at = thing_at(t);
  (void) thing_moving_from_set(t, at);

  thing_is_teleporting_unset(g, v, l, t);
  thing_is_moving_unset(g, v, l, t);
  thing_is_jumping_unset(g, v, l, t);
}

//
// Returns true if the thing can move to this location
//
bool thing_can_move_to(Gamep g, Levelsp v, Levelp l, Thingp t, spoint to)
{
  TRACE_NO_INDENT();

  if (is_oob(to)) {
    return false;
  }

  auto at = thing_at(t);
  if (to == at) {
    return true;
  }

  auto dx = to.x - at.x;
  auto dy = to.y - at.y;
  thing_set_dir_from_delta(t, dx, dy);

  FOR_ALL_THINGS_AT(g, v, l, it, to)
  {
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
bool thing_can_move_to_by_shoving(Gamep g, Levelsp v, Levelp l, Thingp t, spoint to)
{
  TRACE_NO_INDENT();

  if (is_oob(to)) {
    return false;
  }

  auto at = thing_at(t);
  if (to == at) {
    return true;
  }

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
      // But make exceptions for things like braziers
      //
      if (thing_is_able_to_shove(t)) {
        if (thing_is_shovable(it)) {
          continue;
        }
      }

      return false;
    }
  }

  return true;
}

//
// Post init/warp, we need to update the position so we can determine the level draw bounds
//
void thing_update_pos(Gamep g, Levelsp v, Levelp l, Thingp t)
{
  TRACE_NO_INDENT();

  auto   real_at = thing_real_at(t);
  spoint pix_at;
  pix_at.x = (int) (real_at.x * (float) TILE_WIDTH);
  pix_at.y = (int) (real_at.y * (float) TILE_HEIGHT);
  thing_pix_at_set(g, v, l, t, pix_at);
}
