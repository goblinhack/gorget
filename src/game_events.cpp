//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_game.hpp"
#include "my_globals.hpp"
#include "my_level.hpp"
#include "my_main.hpp"
#include "my_sdl_proto.hpp"
#include "my_sound.hpp"
#include "my_thing_inlines.hpp"
#include "my_ui.hpp"
#include "my_wids.hpp"

//
// Return true on the event being consumed
//
bool game_mouse_down(Gamep g, int x, int y, uint32_t button)
{
  DBG("Game mouse down");
  TRACE_AND_INDENT();

  if (wid_some_recent_event_occurred()) {
    DBG("Game mouse down, ignore, some event occurred");
    return false;
  }

  if (! g) {
    DBG("Game mouse down, ignore, no game");
    return false;
  }

  if (game_state(g) != STATE_PLAYING) {
    DBG("Game mouse down, ignore, not playing");
    return false;
  }

  //
  // Follow the mouse path?
  //
  auto v = game_levels_get(g);
  if (! v) {
    DBG("Game mouse down, ignore, no levels");
    return true;
  }

  //
  // Have a level?
  //
  auto l = game_level_get(g, v);
  if (! l) {
    DBG("Game mouse down, ignore, no level");
    return false;
  }

  //
  // Over the map?
  //
  if (! level_cursor_is_valid(g, v)) {
    DBG("Game mouse down, ignore, no cursor valid");
    return false;
  }

  //
  // If in level select mode, enter the new level
  //
  if (level_is_level_select(g, v, l)) {
    level_select_mouse_down(g, v, l);
    return true;
  }

  //
  // Returns true on the event being consumed
  //
  return thing_player_mouse_down(g, v, l, x, y, button);
}

bool game_mouse_up(Gamep g, int x, int y, uint32_t button) { return false; }

bool game_mouse_motion(Gamep g, int x, int y, int relx, int rely, int wheelx, int wheely)
{
  DBG2("Game mouse motion");
  TRACE_NO_INDENT();

  if (wid_some_recent_event_occurred()) {
    return false;
  }

  if (! g) {
    DBG("Game motion, ignore, no game");
    return false;
  }

  if (game_state(g) != STATE_PLAYING) {
    DBG("Game motion, ignore, not playing");
    return false;
  }

  auto v = game_levels_get(g);
  if (! v) {
    return false;
  }

  //
  // Have a level?
  //
  auto l = game_level_get(g, v);
  if (! l) {
    return false;
  }

  //
  // Over the map?
  //
  if (! level_cursor_is_valid(g, v)) {
    return false;
  }

  //
  // Update the cursor path
  //
  if (! wheelx && ! wheely) {
    game_request_to_update_cursor_set(g);
  }

  level_scroll_delta(g, v, l, spoint(wheelx, -wheely));

  return true;
}

bool game_event_save(Gamep g)
{
  DBG("Saving");
  TRACE_AND_INDENT();

  auto v = game_levels_get(g);
  if (! v) {
    return false;
  }

  auto l = game_level_get(g, v);
  if (! l) {
    return false;
  }

  auto player = thing_player(g);
  if (! player) {
    return false;
  }

  if (thing_is_dead(player)) {
    return false;
  }

  if (! level_is_level_select(g, v, l)) {
    if (g_opt_debug1) {
      //
      // Allow when debugging
      //
    } else {
      TOPCON(UI_WARNING_FMT_STR "You can only save games when you exit the level." UI_RESET_FMT);
      sound_play(g, "error");
      return true;
    }
  }

  if (l->tick_in_progress) {
    game_request_to_save_game_set(g);
  } else {
    wid_save_select(g);
  }

  return true;
}

bool game_event_load(Gamep g)
{
  DBG("Loading");
  TRACE_AND_INDENT();

  wid_load_select(g);

  return true;
}

bool game_event_wait(Gamep g)
{
  DBG("Wait");
  TRACE_AND_INDENT();

  auto v = game_levels_get(g);
  if (! v) {
    return false;
  }

  auto l = game_level_get(g, v);
  if (! l) {
    return false;
  }

  auto player = thing_player(g);
  if (! player) {
    return false;
  }

  if (thing_is_dead(player)) {
    return false;
  }

  TOPCON("You wait...");
  level_tick_begin_requested(g, v, l, "player waiting");

  return true;
}

bool game_event_inventory(Gamep g)
{
  DBG("Inventory");
  TRACE_AND_INDENT();

  auto v = game_levels_get(g);
  if (! v) {
    return false;
  }

  auto l = game_level_get(g, v);
  if (! l) {
    return false;
  }

  auto player = thing_player(g);
  if (! player) {
    return false;
  }

  wid_inventory_show(g, v, l, player);

  return true;
}

bool game_event_descend(Gamep g)
{
  DBG("Descend");
  TRACE_AND_INDENT();

  auto v = game_levels_get(g);
  if (! v) {
    return false;
  }

  auto l = game_level_get(g, v);
  if (! l) {
    return false;
  }

  auto player = thing_player(g);
  if (! player) {
    return false;
  }

  if (thing_is_dead(player)) {
    return false;
  }

  if (! level_is_exit(g, v, l, player)) {
    TOPCON(UI_WARNING_FMT_STR "There is no level exit here to descend." UI_RESET_FMT);
    sound_play(g, "error");
    return false;
  }

  player_reached_exit(g, v, l);

  return true;
}

bool game_event_ascend(Gamep g)
{
  DBG("Ascend");
  TRACE_AND_INDENT();

  auto v = game_levels_get(g);
  if (! v) {
    return false;
  }

  auto l = game_level_get(g, v);
  if (! l) {
    return false;
  }

  auto player = thing_player(g);
  if (! player) {
    return false;
  }

  if (thing_is_dead(player)) {
    return false;
  }

  if (! level_is_entrance(g, v, l, player)) {
    TOPCON(UI_WARNING_FMT_STR "There is no level entrance here to ascend." UI_RESET_FMT);
    sound_play(g, "error");
    return false;
  }

  player_reached_entrance(g, v, l);

  return true;
}

bool game_event_jump(Gamep g)
{
  DBG("Jump");
  TRACE_AND_INDENT();

  auto v = game_levels_get(g);
  if (! v) {
    return false;
  }

  auto l = game_level_get(g, v);
  if (! l) {
    return false;
  }

  auto player = thing_player(g);
  if (! player) {
    return false;
  }

  if (thing_is_dead(player)) {
    return false;
  }

  if (level_is_cursor_path_hazard(g, v, l, v->cursor_at)) {
    //
    // If there is a hazard at the target, then go through the normal mouse
    // code which will walk up to the edge of the chasm and then jump, and
    // can offer a confirm box.
    //
    player_state_change(g, v, l, PLAYER_STATE_PATH_REQUESTED);
    level_cursor_copy_mouse_path_to_player(g, v, l);
    return player_check_if_target_needs_move_confirm(g, v, l, v->cursor_at);
  } else {
    //
    // Else, just jump, which cannot be done by mouse means unless it is
    // obvious and the target is a chasm.
    //
    return player_jump(g, v, l, player, v->cursor_at);
  }
}

bool game_event_help(Gamep g)
{
  DBG("Help");
  TRACE_AND_INDENT();

  auto player = thing_player(g);
  if (! player) {
    return false;
  }

  if (thing_is_dead(player)) {
    return false;
  }

  wid_cfg_help_select(g);

  return true;
}

bool game_event_quit(Gamep g)
{
  DBG("Quitting");
  TRACE_AND_INDENT();

  if (g_opt_quick_start) {
    DIE_CLEAN("Quick quit");
  }

  if (g_opt_level_select_menu) {
    DIE_CLEAN("Quick quit");
  }

  wid_quit_select(g);

  return true;
}

bool game_input(Gamep g, const SDL_Keysym *key)
{
  DBG("Pressed a key");
  TRACE_AND_INDENT();

  if (! g) {
    DBG("Pressed a key; no game");
    return false;
  }

  if (game_state(g) != STATE_PLAYING) {
    return false;
  }

  auto v = game_levels_get(g);
  if (! v) {
    DBG("Pressed a key; no levels");
    return false;
  }

  auto player = thing_player(g);
  if (! player) {
    DBG("Pressed a key; no player");
    return false;
  }

  if (sdlk_eq(*key, game_key_console_get(g))) {
    DBG("Pressed a key; over console, ignore");
    sound_play(g, "keypress");
    return false;
  }

  if (sdlk_eq(*key, game_key_zoom_get(g))) {
    DBG("Zoom alt");
    game_map_zoom_toggle(g);
    sound_play(g, "keypress");
    return false; // To avoid click noise
  }

  if (sdlk_eq(*key, game_key_wait_get(g))) {
    DBG("Pressed wait key");
    game_event_wait(g);
    return false; // To avoid click noise
  }

  if (sdlk_eq(*key, game_key_inventory_get(g))) {
    DBG("Pressed inventory key");
    game_event_inventory(g);
    return false; // To avoid click noise
  }

  if (sdlk_eq(*key, game_key_ascend_get(g))) {
    DBG("Pressed ascend key");
    sound_play(g, "keypress");
    game_event_ascend(g);
    return false; // To avoid click noise
  }

  if (sdlk_eq(*key, game_key_descend_get(g))) {
    DBG("Pressed descend key");
    sound_play(g, "keypress");
    game_event_descend(g);
    return false; // To avoid click noise
  }

  if (sdlk_eq(*key, game_key_quit_get(g))) {
    DBG("Pressed quit key");
    sound_play(g, "keypress");
    game_event_quit(g);
    return true;
  }

  if (sdlk_eq(*key, game_key_help_get(g))) {
    DBG("Pressed help key");
    TRACE_AND_INDENT();
    sound_play(g, "keypress");
    game_event_help(g);
    return true;
  }

  if (sdlk_eq(*key, game_key_load_get(g))) {
    DBG("Pressed load key");
    TRACE_AND_INDENT();
    DBG("Loading game");
    sound_play(g, "keypress");
    game_event_load(g);
    return true;
  }

  if (sdlk_eq(*key, game_key_save_get(g))) {
    DBG("Pressed save key");
    TRACE_AND_INDENT();
    sound_play(g, "keypress");
    game_event_save(g);
    return true;
  }

  if (sdlk_eq(*key, game_key_jump_get(g))) {
    DBG("Pressed jump key");
    TRACE_AND_INDENT();
    game_event_jump(g);
    return true;
  }

  if (sdlk_eq(*key, game_key_fire_get(g))) {
    return false;
  }
  if (sdlk_eq(*key, game_key_move_up_get(g))) {
    return false;
  }
  if (sdlk_eq(*key, game_key_move_down_get(g))) {
    return false;
  }
  if (sdlk_eq(*key, game_key_move_left_get(g))) {
    return false;
  }
  if (sdlk_eq(*key, game_key_move_right_get(g))) {
    return false;
  }

  switch (key->mod) {
    case KMOD_LCTRL :
    case KMOD_RCTRL :
    default :
      switch (key->sym) {
        default :
          {
            auto c = wid_event_to_char(key);
            switch (c) {
              case '0' :
              case '1' :
              case '2' :
              case '3' :
              case '4' :
              case '5' :
              case '6' :
              case '7' :
              case '8' :
              case '9' :
              case 'a' :
              case 'b' :
              case 'c' :
              case 'd' :
              case 'e' :
              case 'f' :
              case 'g' :
              case 'h' :
              case 'i' :
              case 'j' :
              case 'k' :
              case 'l' :
              case 'm' :
              case 'n' :
              case 'o' :
              case 'p' :
              case 'q' :
              case 'r' :
              case 's' :
              case 't' :
              case 'u' :
              case 'v' :
              case 'w' :
              case 'x' :
              case 'y' :
              case 'z' :
              case '?' :
              case '-' :
              case '+' :
              case '=' : game_event_help(g);
            }
          }
      }
  }
  return false;
}
