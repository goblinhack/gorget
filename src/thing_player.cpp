//
// Copyright goblinhack@gmail.com
//

#include <ranges>

#include "my_callstack.hpp"
#include "my_game.hpp"
#include "my_globals.hpp"
#include "my_line.hpp"
#include "my_main.hpp"
#include "my_thing_callbacks.hpp"
#include "my_thing_inlines.hpp"
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

Levelp thing_player_level(Gamep g)
{
  TRACE_NO_INDENT();

  auto me = thing_player(g);
  if (! me) {
    return nullptr;
  }

  auto v = game_levels_get(g);
  if (! v) {
    return nullptr;
  }

  return game_level_get(g, v, me->level_num);
}

//
// Replace the mouse path upon mouse down events
//
[[nodiscard]] static bool thing_player_replace_current_mouse_path(Gamep g, Levelsp v, Levelp l)
{
  TRACE_NO_INDENT();

  //
  // Need to recreate the path first, as the me may have moved since the last mouse move
  //
  level_cursor_path_recreate(g, v, l);

  player_state_change(g, v, l, PLAYER_STATE_PATH_REQUESTED);

  //
  // Apply the new path
  //
  level_cursor_copy_mouse_path_to_player(g, v, l);

  return player_check_if_target_needs_move_confirm(g, v, l, v->cursor_at);
}

//
// Pass the event to things for consumption e.g. doors
//
[[nodiscard]] static bool thing_player_pass_event_to_other_things(Gamep g, Levelsp v, Levelp l, int x, int y,
                                                                  uint32_t button)
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
      // No me mouse events when dead
      //
      break;
    case PLAYER_STATE_NORMAL :
      //
      // Give a chance to open/close doors first.
      //
      if (thing_player_pass_event_to_other_things(g, v, l, x, y, button)) {
        break;
      }

      //
      // Replace the mouse path
      //
      (void) thing_player_replace_current_mouse_path(g, v, l);
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
    case PLAYER_STATE_FOLLOWING_PATH :
      //
      // Already following a path. Allow the me to change the path.
      //
      (void) thing_player_replace_current_mouse_path(g, v, l);
      break;
    case PLAYER_STATE_ENUM_MAX : break;
  }

  //
  // Suppress mouse click
  //
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
      // If the me pressed the mouse, we need to apply the current cursor path and start moving.
      //
      switch (player_state(g, v)) {
        case PLAYER_STATE_INIT :
          //
          // Player not initialized yet
          //
          if (g_opt_level_select_menu) {
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
        case PLAYER_STATE_FOLLOWING_PATH :
          //
          // Already following a path. Allow the me to mouse around looking for
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
    case STATE_INVENTORY_MENU :    break;
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

void player_state_change(Gamep g, Levelsp v, Levelp l, PlayerState new_state)
{
  TRACE_NO_INDENT();

  auto me = thing_player(g);
  if (! me) {
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
    case PLAYER_STATE_FOLLOWING_PATH :
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
  THING_LOG(me, "state change: %s -> %s", player_state_to_string(old_state).c_str(),
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
      level_cursor_path_reset(g, v, l);
      break;
    case PLAYER_STATE_NORMAL :
      //
      // Replace the mouse path
      //
      if (old_state == PLAYER_STATE_FOLLOWING_PATH) {
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
    case PLAYER_STATE_FOLLOWING_PATH :
      //
      // Already following a path, stick to it until completion.
      //
      if (old_state != PLAYER_STATE_FOLLOWING_PATH) {
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
  if (val) {
    game_state_change(g, STATE_PLAYING, "callback: got 'Yes' warning confirmation");
  } else {
    game_state_change(g, STATE_PLAYING, "callback: got 'No' warning confirmation");
  }

  auto v = game_levels_get(g);
  if (! v) {
    return;
  }

  auto l = game_level_get(g, v);
  if (! l) {
    return;
  }

  auto me = thing_player(g);
  if (! me) {
    return;
  }

  if (! val) {
    level_cursor_path_reset(g, v, l);
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
        THING_LOG(me, "confirmed move");
        player_state_change(g, v, l, PLAYER_STATE_FOLLOWING_PATH);
      } else {
        THING_LOG(me, "declined move");
        player_state_change(g, v, l, PLAYER_STATE_NORMAL);
      }
      break;
    case PLAYER_STATE_FOLLOWING_PATH :
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
  auto me = thing_player(g);
  if (! me) {
    return false;
  }

  THING_LOG(me, "me move");

  TRACE_AND_INDENT();

  //
  // Double check before jumping in chasms or lava
  //
  if (level_is_needs_move_confirm(g, v, l, to)) {
    if (! thing_is_ethereal(me) && ! thing_is_floating(me) && ! thing_is_flying(me)) {
      if (level_is_chasm(g, v, l, to)) {
        std::string msg = "Do you really want to leap into a chasm?";
        player_state_change(g, v, l, PLAYER_STATE_MOVE_CONFIRM_REQUESTED);
        game_state_change(g, STATE_MOVE_WARNING_MENU, "need warning confirmation");
        if (g_opt_tests) {
          player_check_if_target_needs_move_confirm_callback(g, true);
        } else {
          wid_warning(g, msg, player_check_if_target_needs_move_confirm_callback);
        }
        return false;
      }

      if (level_alive_is_brazier(g, v, l, to)) {
        std::string msg = "Do you really want to kick over the brazier?";
        player_state_change(g, v, l, PLAYER_STATE_MOVE_CONFIRM_REQUESTED);
        game_state_change(g, STATE_MOVE_WARNING_MENU, "need warning confirmation");
        if (g_opt_tests) {
          player_check_if_target_needs_move_confirm_callback(g, true);
        } else {
          wid_warning(g, msg, player_check_if_target_needs_move_confirm_callback);
        }
        return false;
      }

      //
      // If not already in lava, warn about moving into it
      //
      if (! level_is_lava(g, v, l, me)) {
        if (level_is_lava(g, v, l, to)) {
          if (! thing_is_immune_to(me, THING_EVENT_HEAT_DAMAGE)
              && ! thing_is_immune_to(me, THING_EVENT_FIRE_DAMAGE)) {
            std::string msg = "Do you really want to leap into lava?";
            player_state_change(g, v, l, PLAYER_STATE_MOVE_CONFIRM_REQUESTED);
            game_state_change(g, STATE_MOVE_WARNING_MENU, "need warning confirmation");
            if (g_opt_tests) {
              player_check_if_target_needs_move_confirm_callback(g, true);
            } else {
              wid_warning(g, msg, player_check_if_target_needs_move_confirm_callback);
            }
            return false;
          }
        }
      }
    }
  }

  return true;
}

//
// Return true on a successful move (or a popup asking more info)
//
[[nodiscard]] static bool player_move_try(Gamep g, Levelsp v, Levelp l, Thingp me, spoint to, bool need_path)
{
  THING_LOG(me, "move try");

  TRACE_AND_INDENT();

  if (thing_can_move_to_attempt(g, v, l, me, to)) {
    //
    // Fake a mouse path for movement
    //
    THING_LOG(me, "move try: can move to");
    if (need_path) {
      std::vector< spoint > move_path;
      move_path.push_back(to);
      player_state_change(g, v, l, PLAYER_STATE_PATH_REQUESTED);
      level_cursor_copy_path_to_player(g, v, l, move_path);
      if (! player_check_if_target_needs_move_confirm(g, v, l, to)) {
        //
        // A popup is present
        //
      }
    }
    return true;
  }
  if (thing_can_move_to_attempt_by_shoving(g, v, l, me, to)) {
    //
    // Can we shove it out of the way to move?
    //
    THING_LOG(me, "move try: can move to by shoving");

    if (need_path) {
      std::vector< spoint > move_path;
      move_path.push_back(to);
      player_state_change(g, v, l, PLAYER_STATE_PATH_REQUESTED);
      level_cursor_copy_path_to_player(g, v, l, move_path);

      //
      // If this needs confirmation, then do not continue onto shoving.
      //
      if (! player_check_if_target_needs_move_confirm(g, v, l, to)) {
        //
        // A popup is present
        //
        return true;
      }
    }

    if (thing_shove_to(g, v, l, me, to)) {
      level_tick_begin_requested(g, v, l, "me shoved");

      //
      // Do not step onto the thing we just shoved.
      //
      if (level_is_dead_on_shoving(g, v, l, to)) {
        return false;
      } else {
        return true;
      }
    } else {
      level_tick_begin_requested(g, v, l, "me failed to shove");
    }
  } else if (thing_can_move_to_attempt_by_opening(g, v, l, me, to)) {
    //
    // Can we open it allow movement?
    //
    THING_LOG(me, "move try: can move to by opening");
    if (thing_move_to(g, v, l, me, to)) {
      level_tick_begin_requested(g, v, l, "me opened a door to move");
      return true;
    } else {
      level_tick_begin_requested(g, v, l, "me failed to open something in the way");
    }
  } else {
    level_tick_begin_requested(g, v, l, "me bumped into obstacle");
  }
  return false;
}

static void player_move_delta(Gamep g, Levelsp v, Levelp l, int dx, int dy)
{
  TRACE_NO_INDENT();

  if (game_state(g) != STATE_PLAYING) {
    player_move_reset(g, v, l);
    return;
  }

  auto me = thing_player(g);
  if (! me) {
    return;
  }

  //
  // Override any mouse request with the key move.
  //
  level_cursor_path_reset(g, v, l);

  //
  // Wait until the end of the tick
  //
  if (level_tick_is_in_progress(g, v, l)) {
    return;
  }

  auto   at = thing_at(me);
  spoint to(at.x + dx, at.y + dy);

  (void) player_move_try(g, v, l, me, to, true);

  player_move_reset(g, v, l);
}

void player_fire(Gamep g, Levelsp v, Levelp l, int dx, int dy, Tpp fire_what)
{
  TRACE_NO_INDENT();

  auto me = thing_player(g);
  if (! me) {
    ERR("No me found");
    return;
  }

  auto ext_struct = thing_ext_struct(g, me);
  if (! ext_struct) {
    ERR("No me struct found");
    return;
  }

  if (! fire_what) {
    ERR("Nothing to fire");
    return;
  }

  if (game_state(g) != STATE_PLAYING) {
    player_move_reset(g, v, l);
    return;
  }

  //
  // Wait until the end of the tick
  //
  if (level_tick_is_in_progress(g, v, l)) {
    return;
  }

  thing_set_dir_from_delta(me, dx, dy);

  spoint target;

  if (v->cursor_visible) {
    target = v->cursor_at;
  } else {
    fpoint delta = thing_get_direction(g, v, l, me);
    target       = make_spoint(thing_real_at(me) + delta);
  }

  player_move_reset(g, v, l);

  if (! thing_projectile_fire_at(g, v, l, me, fire_what, target)) {
    return;
  }

  level_tick_begin_requested(g, v, l, "me fired");
}

//
// All keys have been released, forget any accumulation of events
//
void player_move_reset(Gamep g, Levelsp v, Levelp l)
{
  TRACE_NO_INDENT();

  v->requested_fire       = false;
  v->requested_move_up    = false;
  v->requested_move_down  = false;
  v->requested_move_left  = false;
  v->requested_move_right = false;
}

//
// Allow moves to accumulate so we can do diagonal moves.
//
void player_move_accum(Gamep g, Levelsp v, Levelp l, bool up, bool down, bool left, bool right, bool fire)
{
  TRACE_NO_INDENT();

  if (fire) {
    v->requested_fire = fire;
  }

  if (up) {
    v->requested_move_up = up;
  }

  if (down) {
    v->requested_move_down = down;
  }

  if (left) {
    v->requested_move_left = left;
  }

  if (right) {
    v->requested_move_right = right;
  }
}

//
// Attempt to move
//
bool player_move_request(Gamep g, bool up, bool down, bool left, bool right, bool fire)
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

  player_move_accum(g, v, l, up, down, left, right, fire);

  //
  // If a move is in progress, do nothing
  //
  if (level_tick_is_in_progress(g, v, l)) {
    return false;
  }

  //
  // TODO
  //
  static Tpp tp_fireball;
  if (! tp_fireball) {
    tp_fireball = tp_find_mand("fireball");
  }

  if (v->requested_fire) {
    if (v->requested_move_up) {
      if (v->requested_move_left) {
        player_fire(g, v, l, -1, -1, tp_fireball);
      } else if (v->requested_move_right) {
        player_fire(g, v, l, 1, -1, tp_fireball);
      } else {
        player_fire(g, v, l, 0, -1, tp_fireball);
      }
    } else if (v->requested_move_down) {
      if (v->requested_move_left) {
        player_fire(g, v, l, -1, 1, tp_fireball);
      } else if (v->requested_move_right) {
        player_fire(g, v, l, 1, 1, tp_fireball);
      } else {
        player_fire(g, v, l, 0, 1, tp_fireball);
      }
    } else if (v->requested_move_left) {
      player_fire(g, v, l, -1, 0, tp_fireball);
    } else if (v->requested_move_right) {
      player_fire(g, v, l, 1, 0, tp_fireball);
    } else {
      player_fire(g, v, l, 0, 0, tp_fireball);
    }
  }

  if (v->requested_move_up) {
    if (v->requested_move_left) {
      player_move_delta(g, v, l, -1, -1);
    } else if (v->requested_move_right) {
      player_move_delta(g, v, l, 1, -1);
    } else {
      player_move_delta(g, v, l, 0, -1);
    }
  } else if (v->requested_move_down) {
    if (v->requested_move_left) {
      player_move_delta(g, v, l, -1, 1);
    } else if (v->requested_move_right) {
      player_move_delta(g, v, l, 1, 1);
    } else {
      player_move_delta(g, v, l, 0, 1);
    }
  } else if (v->requested_move_left) {
    player_move_delta(g, v, l, -1, 0);
  } else if (v->requested_move_right) {
    player_move_delta(g, v, l, 1, 0);
  }

  return true;
}

//
// Handle common level exit interactions
//
static void player_leave_current_level_and_change_to_level_num(Gamep g, Levelsp v,
                                                               LevelNum level_num = LEVEL_SELECT_ID)
{
  TRACE_NO_INDENT();

  level_select_update_grid_tiles(g, v);
  level_cursor_path_reset(g, v, game_level_get(g, v));
  (void) level_change(g, v, level_num);
  game_request_to_remake_ui_set(g);
}

//
// Force move a me to a specific level
//
void player_warp_to_specific_level(Gamep g, Levelsp v, LevelNum level_num)
{
  TRACE_NO_INDENT();

  player_leave_current_level_and_change_to_level_num(g, v, level_num);

  auto me = thing_player(g);
  if (! me) {
    ERR("No me found");
    return;
  }

  auto new_level = level_change(g, v, level_num);
  if (! new_level) {
    THING_ERR(me, "failed to move me to level %u", level_num);
    return;
  }

  thing_level_warp_to_entrance(g, v, new_level, me);
}

//
// Handle level exit interactions
//
void player_reached_exit(Gamep g, Levelsp v, Levelp l)
{
  TRACE_NO_INDENT();

  level_is_completed_by_player_exiting(g, v, l);
  player_leave_current_level_and_change_to_level_num(g, v, LEVEL_SELECT_ID);
}

//
// Handle level entrance interactions
//
void player_reached_entrance(Gamep g, Levelsp v, Levelp l)
{
  TRACE_NO_INDENT();

  player_leave_current_level_and_change_to_level_num(g, v, LEVEL_SELECT_ID);
}

//
// Handle the me falling out of the level
//
void player_fell(Gamep g, Levelsp v, Levelp l, Levelp next_level, Thingp me)
{
  TRACE_NO_INDENT();

  level_cursor_path_reset(g, v, l);
  level_is_completed_by_player_falling(g, v, l);

  if (next_level != level_change(g, v, next_level->level_num)) {
    ERR("unexpected level found");
    return;
  }
}

//
// Handle interactions for a thing at its location
//
void player_collision_handle(Gamep g, Levelsp v, Levelp l, Thingp me)
{
  TRACE_NO_INDENT();

  auto ext_struct = thing_ext_struct(g, me);
  if (! ext_struct) {
    return;
  }

  auto at = thing_at(me);
  FOR_ALL_THINGS_AT(g, v, l, it, at)
  {
    //
    // Open secret doors automatically
    //
    if (thing_is_openable(it)) {
      if (thing_open(g, v, l, it, me /* opener */)) {
        if (thing_is_dead(it)) {
          continue;
        }
      }
    }

    //
    // At the end of the popped path or not?
    //
    if (thing_move_path_size(g, v, l, me)) {
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
        player_reached_exit(g, v, l);
        return;
      }

      if (thing_is_entrance(it)) {
        //
        // Ascend
        //
        player_reached_entrance(g, v, l);
        return;
      }
    }
  }
}

//
// Handle me jumping
//
bool player_jump(Gamep g, Levelsp v, Levelp l, Thingp me, spoint to)
{
  TRACE_NO_INDENT();

  auto player_struct = thing_player_struct(g);
  if (! player_struct) {
    ERR("No me struct found");
    return false;
  }

  auto at        = thing_at(me);
  auto jump_path = draw_line(at, to, thing_distance_jump(me) + 1);
  bool warn      = true;

  for (auto intermediate : std::ranges::reverse_view(jump_path)) {
    if (thing_jump_to(g, v, l, me, intermediate, warn)) {
      level_tick_begin_requested(g, v, l, "me jumped");
      player_state_change(g, v, l, PLAYER_STATE_FOLLOWING_PATH);
      return true;
    }
    warn = false;
  }

  return false;
}

//
// Move to the next path on the popped path if it exits.
//
bool player_move_to_next(Gamep g, Levelsp v, Levelp l, Thingp me)
{
  TRACE_NO_INDENT();

  //
  // If already moving, do not pop the next path tile
  //
  if (thing_is_moving(me)) {
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
    case PLAYER_STATE_FOLLOWING_PATH :
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
  if (! thing_move_path_pop(g, v, l, me, move_next)) {
    //
    // If could not pop, then no path is left
    //
    player_state_change(g, v, l, PLAYER_STATE_NORMAL);
    return false;
  }

  spoint move_destination = {};
  if (thing_move_path_target(g, v, l, me, move_destination)) {
    if (level_is_cursor_path_hazard(g, v, l, move_next)) {
      if (thing_jump_to(g, v, l, me, move_destination)) {
        //
        // If could jump, then abort the path walk
        //
        level_tick_begin_requested(g, v, l, "me jumped to avoid a hazard");
        player_state_change(g, v, l, PLAYER_STATE_NORMAL);
        return false;
      }

      //
      // Something was in the way of jumping. Best to stop rather than accidentally
      // walk into a chasm.
      //
      level_tick_begin_requested(g, v, l, "me fail to jump to avoid a hazard");
      player_state_change(g, v, l, PLAYER_STATE_NORMAL);
      return false;
    }
  }

  if (! player_move_try(g, v, l, me, move_next, false)) {
    //
    // If could not move, then abort the path walk
    //
    player_state_change(g, v, l, PLAYER_STATE_NORMAL);
    return false;
  }

  if (thing_move_to(g, v, l, me, move_next)) {
    if (thing_is_player(me)) {
      level_tick_begin_requested(g, v, l, "me moved to next");
    }
  } else {
    if (thing_is_player(me)) {
      level_tick_begin_requested(g, v, l, "me faled moved to next location");
    }
  }

  return true;
}
