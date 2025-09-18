//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_level.hpp"
#include "my_main.hpp"
#include "my_ptrcheck.hpp"
#include "my_tile.hpp"
#include "my_tp_callbacks.hpp"

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
// Handles manual and mouse follow moves
//
bool thing_move_to(Gamep g, Levelsp v, Levelp l, Thingp t, spoint to)
{
  TRACE_NO_INDENT();

  if (is_oob(to)) {
    return false;
  }

  if (to == t->at) {
    return false;
  }

  thing_pop(g, v, t);

  t->pix_at.x = t->at.x * INNER_TILE_WIDTH;
  t->pix_at.y = t->at.y * INNER_TILE_HEIGHT;

  t->old_at      = t->at;
  t->moving_from = t->at;
  t->at          = to;

  thing_push(g, v, l, t);

  thing_is_moving_set(g, v, l, t);

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

  if (to == t->at) {
    return false;
  }

  return thing_shove_handle(g, v, l, t, to);
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

  //
  // Check if already present.
  //
  auto curr_level = thing_level(g, v, t);
  if ((new_level == curr_level) && (to == t->at)) {
    //
    // No need to pop. If might be an inventory item though, so make sure and push.
    //
  } else {
    //
    // Remove from the currentl level or position
    //
    thing_pop(g, v, t);
  }

  t->pix_at.x = t->at.x * INNER_TILE_WIDTH;
  t->pix_at.y = t->at.y * INNER_TILE_HEIGHT;

  t->old_at = t->at;
  t->at     = to;

  thing_push(g, v, new_level, t);

  //
  // Need to update with the new pixel position
  //
  thing_update_pos(g, t);

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

  t->moving_from = t->at;

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
void thing_update_pos(Gamep g, Thingp t)
{
  TRACE_NO_INDENT();

  t->pix_at.x = t->at.x * INNER_TILE_WIDTH;
  t->pix_at.y = t->at.y * INNER_TILE_HEIGHT;
}
