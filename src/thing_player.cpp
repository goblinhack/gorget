//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_game.hpp"
#include "my_globals.hpp"
#include "my_level.hpp"
#include "my_line.hpp"
#include "my_main.hpp"
#include "my_sound.hpp"
#include "my_thing_callbacks.hpp"
#include "my_wid_warning.hpp"

Thingp thing_player(Gamep g)
{
  TRACE_NO_INDENT();

  auto v = game_levels_get(g);
  if (! v) {
    return nullptr;
  }

  if (! v->player_id) {
    return nullptr;
  }

  return thing_find(g, v, v->player_id);
}

//
// Replace the mouse path upon mouse down events
//
static bool thing_player_replace_current_mouse_path(Gamep g, Levelsp v, Levelp l)
{
  TRACE_NO_INDENT();

  //
  // Need to recreate the path first, as the player may have moved since the last mouse move
  //
  level_cursor_path_recreate(g, v, l);

  player_state_change(g, v, PLAYER_STATE_PATH_REQUESTED);

  //
  // Apply the new path
  //
  level_cursor_copy_mouse_path_to_player(g, v, l);

  return player_check_if_target_needs_move_confirm(g, v, l, v->cursor_at);
}

//
// Pass the event to things for consumption e.g. doors
//
static bool thing_player_pass_event_to_other_things(Gamep g, Levelsp v, Levelp l, int x, int y, uint32_t button)
{
  TRACE_NO_INDENT();

  FOR_ALL_THINGS_AT(g, v, l, it, v->cursor_at)
  {
    if (thing_mouse_down(g, v, l, it, x, y, button)) {
      //
      // Processed an event, like door closing
      //
      return true;
    }
  }

  return false;
}

//
// Return true on the event being consumed
//
bool thing_player_mouse_down(Gamep g, Levelsp v, Levelp l, int x, int y, uint32_t button)
{
  LOG("Thing mouse down");
  TRACE_NO_INDENT();

  switch (player_state(g, v)) {
    case PLAYER_STATE_INIT :
      //
      // Player not initialized yet
      //
      break;
    case PLAYER_STATE_DEAD :
      //
      // No player mouse events when dead
      //
      break;
    case PLAYER_STATE_NORMAL :
      //
      // Give a chance to open/close doors first.
      //
      if (thing_player_pass_event_to_other_things(g, v, l, x, y, button)) {
        return true;
      }

      //
      // Replace the mouse path
      //
      return thing_player_replace_current_mouse_path(g, v, l);
    case PLAYER_STATE_PATH_REQUESTED :
      //
      // Player wants to start following or replace the current path.
      //
      break;
    case PLAYER_STATE_MOVE_CONFIRM_REQUESTED :
      //
      // Wait for confirmation.
      //
      break;
    case PLAYER_STATE_FOLLOWING_A_PATH :
      //
      // Already following a path. Allow the player to change the path.
      //
      return thing_player_replace_current_mouse_path(g, v, l);
    case PLAYER_STATE_ENUM_MAX : break;
  }

  return false;
}

//
// Called per display loop
//
static void thing_player_cursor_loop(Gamep g, Levelsp v, Levelp l)
{
  TRACE_NO_INDENT();

  //
  // If the cursor moved, update what we see
  //
  if (game_request_to_update_cursor_get(g)) {
    level_cursor_path_recreate(g, v, l);
    level_cursor_describe(g, v, l);
    game_request_to_update_cursor_unset(g);
  }
}

//
// Called per display loop
//
void thing_player_event_loop(Gamep g, Levelsp v, Levelp l)
{
  TRACE_NO_INDENT();

  switch (game_state(g)) {
    case STATE_INIT :      break;
    case STATE_MAIN_MENU : break;
    case STATE_QUITTING :  break;
    case STATE_PLAYING :
      //
      // If the player pressed the mouse, we need to apply the current cursor path and start moving.
      //
      switch (player_state(g, v)) {
        case PLAYER_STATE_INIT :
          //
          // Player not initialized yet
          //
          if (g_opt_quick_start_level_select_menu) {
            thing_player_cursor_loop(g, v, l);
          }
          break;
        case PLAYER_STATE_DEAD :
          //
          // No moving when dead
          //
          break;
        case PLAYER_STATE_NORMAL :
          //
          // If the cursor moved, update what we see
          //
          thing_player_cursor_loop(g, v, l);
          break;
        case PLAYER_STATE_PATH_REQUESTED :
          //
          // Player wants to start following or replace the current path.
          //
          level_cursor_copy_mouse_path_to_player(g, v, l);
          break;
        case PLAYER_STATE_MOVE_CONFIRM_REQUESTED :
          //
          // Wait for confirmation.
          //
          break;
        case PLAYER_STATE_FOLLOWING_A_PATH :
          //
          // Already following a path. Allow the player to mouse around looking for
          // a better path while moving.
          //
          thing_player_cursor_loop(g, v, l);
          break;
        case PLAYER_STATE_ENUM_MAX : break;
      }
      break;
    case STATE_DEAD_MENU :
      //
      // If the cursor moved, update what we see
      //
      thing_player_cursor_loop(g, v, l);
      break;
    case STATE_MOVE_WARNING_MENU : break;
    case STATE_KEYBOARD_MENU :     break;
    case STATE_LOAD_MENU :         break;
    case STATE_LOADED :            break;
    case STATE_SAVE_MENU :         break;
    case STATE_QUIT_MENU :         break;
    case STATE_INVENTORY :         break;
    case STATE_ITEM_MENU :         break;
    case STATE_GENERATING :        break;
    case STATE_GENERATED :         break;
    case GAME_STATE_ENUM_MAX :     break;
  }
}

std::string player_state_to_string(PlayerState state)
{
  TRACE_NO_INDENT();
  return PlayerState_to_string(state);
}

PlayerState player_state(Gamep g, Levelsp v)
{
  TRACE_NO_INDENT();
  return v->_player_state;
}

void player_state_change(Gamep g, Levelsp v, PlayerState new_state)
{
  TRACE_NO_INDENT();

  auto player = thing_player(g);
  if (! player) {
    return;
  }

  auto old_state = v->_player_state;

  switch (old_state) {
    case PLAYER_STATE_INIT :
      //
      // Player not initialized yet
      //
      break;
    case PLAYER_STATE_DEAD :
      //
      // Player is dead.
      //
      return;
    case PLAYER_STATE_NORMAL :
      //
      // Replace the mouse path
      //
      break;
    case PLAYER_STATE_PATH_REQUESTED :
      //
      // Player wants to start following or replace the current path.
      //
      break;
    case PLAYER_STATE_MOVE_CONFIRM_REQUESTED :
      //
      // Wait for confirmation.
      //
      break;
    case PLAYER_STATE_FOLLOWING_A_PATH :
      //
      // Already following a path, stick to it until completion.
      //
      break;
    case PLAYER_STATE_ENUM_MAX : break;
  }

  if (v->_player_state == new_state) {
    return;
  }

  //
  // Set here to stop recursion.
  //
  v->_player_state = new_state;

  //
  // Why oh why change state
  //
  LOG("Player state change: %s -> %s", player_state_to_string(old_state).c_str(),
      player_state_to_string(new_state).c_str());

  switch (new_state) {
    case PLAYER_STATE_INIT :
      //
      // Player not initialized yet
      //
      break;
    case PLAYER_STATE_DEAD :
      //
      // No need of a mouse path when dead.
      //
      level_cursor_path_reset(g, v);
      break;
    case PLAYER_STATE_NORMAL :
      //
      // Replace the mouse path
      //
      if (old_state == PLAYER_STATE_FOLLOWING_A_PATH) {
        //
        // Only auto scroll at the start and end of moving
        //
        v->requested_auto_scroll = true;
      }
      break;
    case PLAYER_STATE_PATH_REQUESTED :
      //
      // Player wants to start following or replace the current path.
      //
      break;
    case PLAYER_STATE_MOVE_CONFIRM_REQUESTED :
      //
      // Wait for confirmation.
      //
      break;
    case PLAYER_STATE_FOLLOWING_A_PATH :
      //
      // Already following a path, stick to it until completion.
      //
      if (old_state != PLAYER_STATE_FOLLOWING_A_PATH) {
        //
        // Only auto scroll at the start and end of moving
        //
        v->requested_auto_scroll = true;
      }
      break;
    case PLAYER_STATE_ENUM_MAX : break;
  }
}

//
// Return true on the event being consumed
//
static void player_check_if_target_needs_move_confirm_callback(Gamep g, bool val)
{
  game_state_change(g, STATE_PLAYING, "got warning confirmation");

  auto v = game_levels_get(g);
  if (! v) {
    return;
  }

  if (! val) {
    level_cursor_path_reset(g, v);
  }

  switch (player_state(g, v)) {
    case PLAYER_STATE_INIT :
      //
      // Player not initialized yet
      //
      break;
    case PLAYER_STATE_DEAD :
      //
      // Player is dead
      //
      return;
    case PLAYER_STATE_NORMAL :
      //
      // Replace the mouse path
      //
      break;
    case PLAYER_STATE_PATH_REQUESTED :
      //
      // Player wants to start following or replace the current path.
      //
      break;
    case PLAYER_STATE_MOVE_CONFIRM_REQUESTED :
      //
      // Wait for confirmation.
      //
      if (val) {
        LOG("Player confirmed move");
        player_state_change(g, v, PLAYER_STATE_FOLLOWING_A_PATH);
      } else {
        LOG("Player declined move");
        player_state_change(g, v, PLAYER_STATE_NORMAL);
      }
      break;
    case PLAYER_STATE_FOLLOWING_A_PATH :
      //
      // Already following a path, stick to it until completion.
      //
      break;
    case PLAYER_STATE_ENUM_MAX : break;
  }
}

//
// Return true on the event being consumed
//
bool player_check_if_target_needs_move_confirm(Gamep g, Levelsp v, Levelp l, spoint to)
{
  LOG("Player move");
  TRACE_AND_INDENT();

  auto player = thing_player(g);
  if (! player) {
    return false;
  }

  //
  // Double check before jumping in chasms or lava
  //
  if (! g_opt_tests) {
    if (level_is_needs_move_confirm(g, v, l, to)) {
      if (! thing_is_ethereal(player) && ! thing_is_floating(player) && ! thing_is_flying(player)) {
        if (level_is_chasm(g, v, l, to)) {
          std::string msg = "Do you really want to leap into a chasm.";
          player_state_change(g, v, PLAYER_STATE_MOVE_CONFIRM_REQUESTED);
          game_state_change(g, STATE_MOVE_WARNING_MENU, "need warning confirmation");
          wid_warning(g, msg, player_check_if_target_needs_move_confirm_callback);
          return false;
        }

        //
        // If not already in lava, warn about moving into it
        //
        if (! level_is_lava(g, v, l, player->at)) {
          if (level_is_lava(g, v, l, to)) {
            if (! thing_is_immune_to(player, THING_EVENT_HEAT_DAMAGE)
                && ! thing_is_immune_to(player, THING_EVENT_FIRE_DAMAGE)) {
              std::string msg = "Do you really want to leap into lava.";
              player_state_change(g, v, PLAYER_STATE_MOVE_CONFIRM_REQUESTED);
              game_state_change(g, STATE_MOVE_WARNING_MENU, "need warning confirmation");
              wid_warning(g, msg, player_check_if_target_needs_move_confirm_callback);
              return false;
            }
          }
        }
      }
    }
  }

  return true;
}

static bool player_move_try(Gamep g, Levelsp v, Levelp l, Thingp t, spoint to, bool need_path)
{
  TRACE_NO_INDENT();
  LOG("Player move try");

  if (thing_can_move_to(g, v, l, t, to)) {
    //
    // Fake a mouse path for movement
    //
    LOG("Player move try: can move to");
    if (need_path) {
      std::vector< spoint > move_path;
      move_path.push_back(to);
      player_state_change(g, v, PLAYER_STATE_PATH_REQUESTED);
      level_cursor_copy_path_to_player(g, v, l, move_path);
      player_check_if_target_needs_move_confirm(g, v, l, to);
    }
    return true;
  } else if (thing_can_move_to_by_shoving(g, v, l, t, to)) {
    //
    // Can we shove it out of the way to move?
    //
    LOG("Player move try: can move to by shoving");
    if (thing_shove_to(g, v, l, t, to)) {
      level_tick_begin_requested(g, v, l, "player shoved");
      return true;
    } else {
      level_tick_begin_requested(g, v, l, "player failed to shove");
    }
  } else if (thing_can_move_to_by_opening(g, v, l, t, to)) {
    //
    // Can we open it allow movement?
    //
    LOG("Player move try: can move to by opening");
    if (thing_move_to(g, v, l, t, to)) {
      level_tick_begin_requested(g, v, l, "player opened a door to move");
      return true;
    } else {
      level_tick_begin_requested(g, v, l, "player failed to open something in the way");
    }
  } else {
    level_tick_begin_requested(g, v, l, "player bumped into obstacle");
  }
  return false;
}

void player_move_delta(Gamep g, Levelsp v, Levelp l, int dx, int dy, int dz)
{
  TRACE_NO_INDENT();

  if (game_state(g) != STATE_PLAYING) {
    player_move_reset(g, v, l);
    return;
  }

  auto t = thing_player(g);
  if (! t) {
    return;
  }

  //
  // Override any mouse request with the key move.
  //
  level_cursor_path_reset(g, v);

  //
  // Wait until the end of the tick
  //
  if (level_tick_is_in_progress(g, v, l)) {
    return;
  }

  spoint to(t->at.x + dx, t->at.y + dy);

  player_move_try(g, v, l, t, to, true);

  player_move_reset(g, v, l);
}

//
// All keys have been released, forget any accumulation of events
//
void player_move_reset(Gamep g, Levelsp v, Levelp l)
{
  TRACE_NO_INDENT();

  v->requested_move_up    = false;
  v->requested_move_left  = false;
  v->requested_move_keft  = false;
  v->requested_move_right = false;
}

//
// Allow moves to accumulate so we can do diagonal moves.
//
void player_move_accum(Gamep g, Levelsp v, Levelp l, bool up, bool down, bool left, bool right)
{
  TRACE_NO_INDENT();

  if (up) {
    v->requested_move_up = up;
  }

  if (down) {
    v->requested_move_left = down;
  }

  if (left) {
    v->requested_move_keft = left;
  }

  if (right) {
    v->requested_move_right = right;
  }
}

//
// Attempt to move
//
bool player_move_request(Gamep g, bool up, bool down, bool left, bool right)
{
  TRACE_NO_INDENT();

  auto v = game_levels_get(g);
  if (! v) {
    return false;
  }

  auto l = game_level_get(g, v);
  if (! l) {
    return false;
  }

  if (game_state(g) != STATE_PLAYING) {
    player_move_reset(g, v, l);
    return false;
  }

  player_move_accum(g, v, l, up, down, left, right);

  //
  // If a move is in progress, do nothing
  //
  if (level_tick_is_in_progress(g, v, l)) {
    //
    // But if the player presses the keys again towards the end of the tick, allow that.
    //
    return false;
  }

  if (v->requested_move_up) {
    if (v->requested_move_keft) {
      player_move_delta(g, v, l, -1, -1, 0);
    } else if (v->requested_move_right) {
      player_move_delta(g, v, l, 1, -1, 0);
    } else {
      player_move_delta(g, v, l, 0, -1, 0);
    }
  } else if (v->requested_move_left) {
    if (v->requested_move_keft) {
      player_move_delta(g, v, l, -1, 1, 0);
    } else if (v->requested_move_right) {
      player_move_delta(g, v, l, 1, 1, 0);
    } else {
      player_move_delta(g, v, l, 0, 1, 0);
    }
  } else if (v->requested_move_keft) {
    player_move_delta(g, v, l, -1, 0, 0);
  } else if (v->requested_move_right) {
    player_move_delta(g, v, l, 1, 0, 0);
  }

  return true;
}

//
// Handle common level exit interactions
//
static void player_level_leave(Gamep g, Levelsp v, Levelp l, Thingp t)
{
  TRACE_NO_INDENT();

  level_select_update_grid_tiles(g, v);
  level_cursor_path_reset(g, v);
  level_change(g, v, LEVEL_SELECT_ID);
  TOPCON("LEAVE");
  game_request_to_remake_ui_set(g);
}

//
// Handle level exit interactions
//
void player_reached_exit(Gamep g, Levelsp v, Levelp l, Thingp t)
{
  TRACE_NO_INDENT();

  level_is_completed_by_player_exiting(g, v, l);
  player_level_leave(g, v, l, t);
}

//
// Handle level entrance interactions
//
void player_reached_entrance(Gamep g, Levelsp v, Levelp l, Thingp t)
{
  TRACE_NO_INDENT();

  player_level_leave(g, v, l, t);
}

//
// Handle the player falling out of the level
//
void player_fell(Gamep g, Levelsp v, Levelp l, Levelp next_level, Thingp t)
{
  TRACE_NO_INDENT();

  level_cursor_path_reset(g, v);
  level_is_completed_by_player_falling(g, v, l);

  if (next_level != level_change(g, v, next_level->level_num)) {
    ERR("unexpected level found");
    return;
  }
}

//
// Handle interactions for a thing at its location
//
void player_collision_handle(Gamep g, Levelsp v, Levelp l, Thingp t)
{
  TRACE_NO_INDENT();

  auto player_struct = thing_player_struct(g);
  if (! player_struct) {
    return;
  }

  FOR_ALL_THINGS_AT(g, v, l, it, t->at)
  {
    //
    // Open secret doors automatically
    //
    if (thing_is_openable(it)) {
      if (thing_open(g, v, l, it, t /* opener */)) {
        if (thing_is_dead(it)) {
          continue;
        }
      }
    }

    //
    // At the end of the popped path or not?
    //
    if (player_struct->move_path.size) {
      //
      // If still more tiles to pop, do not descend automatically
      //
      if (thing_is_exit(it)) {
        //
        // To enabled the descend shortcut
        //
        game_request_to_remake_ui_set(g);
        return;
      }

      if (thing_is_entrance(it)) {
        //
        // To enabled the ascent shortcut
        //
        game_request_to_remake_ui_set(g);
        return;
      }
    } else {
      //
      // If at the end of the move path then we can enter or leave when we get to that final tile.
      //
      if (thing_is_exit(it)) {
        //
        // Descend
        //
        player_reached_exit(g, v, l, t);
        return;
      }

      if (thing_is_entrance(it)) {
        //
        // Ascend
        //
        player_reached_entrance(g, v, l, t);
        return;
      }
    }
  }
}

//
// Handle player jumping
//
bool player_jump(Gamep g, Levelsp v, Levelp l, Thingp t, spoint to)
{
  TRACE_NO_INDENT();

  auto player_struct = thing_player_struct(g);
  if (! player_struct) {
    return false;
  }

  auto jump_path = draw_line(t->at, to, thing_jump_distance(t) + 1);
  bool warn      = true;

  for (auto i = jump_path.rbegin(); i != jump_path.rend(); i++) {
    spoint intermediate = *i;
    if (thing_jump_to(g, v, l, t, intermediate, warn)) {
      level_tick_begin_requested(g, v, l, "player jumped");
      player_state_change(g, v, PLAYER_STATE_FOLLOWING_A_PATH);
      return true;
    }
    warn = false;
  }

  return false;
}

//
// Return true if there is a move to pop.
//
static bool player_move_path_pop(Gamep g, Levelsp v, Levelp l, Thingp t, spoint *out)
{
  TRACE_NO_INDENT();

  auto player_struct = thing_player_struct(g);
  if (! player_struct) {
    return false;
  }

  if (! player_struct->move_path.size) {
    return false;
  }

  *out = player_struct->move_path.points[ 0 ];

  for (int index = 0; index < player_struct->move_path.size - 1; index++) {
    player_struct->move_path.points[ index ] = player_struct->move_path.points[ index + 1 ];
  }
  player_struct->move_path.size--;

  return true;
}

//
// Return true if there is a move to pop.
//
static bool player_move_path_destination(Gamep g, Levelsp v, Levelp l, Thingp t, spoint *out)
{
  TRACE_NO_INDENT();

  auto player_struct = thing_player_struct(g);
  if (! player_struct) {
    return false;
  }

  if (! player_struct->move_path.size) {
    return false;
  }

  *out = player_struct->move_path.points[ player_struct->move_path.size - 1 ];

  return true;
}

//
// Move to the next path on the popped path if it exits.
//
bool player_move_to_next(Gamep g, Levelsp v, Levelp l, Thingp t)
{
  TRACE_NO_INDENT();

  //
  // If already moving, do not pop the next path tile
  //
  if (thing_is_moving(t)) {
    return false;
  }

  //
  // If not following a path, then nothing to pop
  //
  switch (player_state(g, v)) {
    case PLAYER_STATE_INIT :
      //
      // Player not initialized yet
      //
      break;
    case PLAYER_STATE_DEAD :
      //
      // No moving when dead
      //
      return false;
    case PLAYER_STATE_NORMAL :
      //
      // Replace the mouse path
      //
      return false;
    case PLAYER_STATE_PATH_REQUESTED :
      //
      // Player wants to start following or replace the current path.
      //
      return false;
    case PLAYER_STATE_MOVE_CONFIRM_REQUESTED :
      //
      // Wait for confirmation.
      //
      return false;
    case PLAYER_STATE_FOLLOWING_A_PATH :
      //
      // Already following a path, stick to it until completion.
      //
      break;
    case PLAYER_STATE_ENUM_MAX : break;
  }

  //
  // Get the next tile to move to
  //
  spoint move_next = {};
  if (! player_move_path_pop(g, v, l, t, &move_next)) {
    //
    // If could not pop, then no path is left
    //
    player_state_change(g, v, PLAYER_STATE_NORMAL);
    return false;
  }

  spoint move_destination = {};
  if (player_move_path_destination(g, v, l, t, &move_destination)) {
    if (level_is_cursor_path_hazard(g, v, l, move_next)) {
      if (thing_jump_to(g, v, l, t, move_destination)) {
        //
        // If could jump, then abort the path walk
        //
        level_tick_begin_requested(g, v, l, "player to avoid a hazard");
        player_state_change(g, v, PLAYER_STATE_NORMAL);
        return false;
      }
    }
  }

  if (! player_move_try(g, v, l, t, move_next, false)) {
    //
    // If could not move, then abort the path walk
    //
    player_state_change(g, v, PLAYER_STATE_NORMAL);
    return false;
  }

  if (thing_move_to(g, v, l, t, move_next)) {
    if (thing_is_player(t)) {
      level_tick_begin_requested(g, v, l, "player moved to next");
    }
  } else {
    if (thing_is_player(t)) {
      level_tick_begin_requested(g, v, l, "player faled moved to next location");
    }
  }

  sound_play(g, "footstep");

  return true;
}
