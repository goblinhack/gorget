//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_game.hpp"
#include "my_level.hpp"
#include "my_main.hpp"
#include "my_sdl_proto.hpp"
#include "my_ui.hpp"
#include "my_wids.hpp"

//
// Return true on the event being consumed
//
uint8_t game_mouse_down(Gamep g, int x, int y, uint32_t button)
{
  LOG("Game mouse down");
  TRACE_AND_INDENT();

  if (wid_some_recent_event_occurred()) {
    return false;
  }

  if (! g) {
    return false;
  }

  if (game_state(g) != STATE_PLAYING) {
    return false;
  }

  //
  // Follow the mouse path?
  //
  auto v = game_levels_get(g);
  if (! v) {
    return true;
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
  // If in level select mode, enter the new level
  //
  if (l->level_num == LEVEL_SELECT_ID) {
    level_select_user_chose_a_level(g, v, l);
    return true;
  }

  //
  // Else start following the cursor path
  //
  v->player_pressed_button_and_waiting_for_a_path = true;
  return true;
}

uint8_t game_mouse_up(Gamep g, int x, int y, uint32_t button) { return false; }

uint8_t game_mouse_motion(Gamep g, int x, int y, int relx, int rely, int wheelx, int wheely)
{
  DBG2("Game mouse motion");
  TRACE_NO_INDENT();

  if (wid_some_recent_event_occurred()) {
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

  level_scroll_delta(g, v, l, point(wheelx, -wheely));

  return true;
}

bool game_event_save(Gamep g)
{
  LOG("Saving");
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

  if (l->level_num != LEVEL_SELECT_ID) {
    if (g_opt_debug1) {
      //
      // Allow when debugging
      //
    } else {
      TOPCON(UI_WARNING_FMT_STR "You can only save games when you exit the level." UI_RESET_FMT);
      return true;
    }
  }
  if (v->tick_in_progress) {
    game_request_to_save_game_set(g);
  } else {
    wid_save_select(g);
  }

  return true;
}

bool game_event_load(Gamep g)
{
  LOG("Loading");
  TRACE_AND_INDENT();

  wid_load_select(g);

  return true;
}

bool game_event_wait(Gamep g)
{
  LOG("Wait");
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

  TOPCON("TODO Waiting");
  // g->player_tick(left, right, up, down, attack, wait, jump);

  return true;
}

bool game_event_descend(Gamep g)
{
  LOG("Descend");
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

  if (! level_is_exit(g, v, l, player->at)) {
    TOPCON(UI_WARNING_FMT_STR "There is no level exit here to descend." UI_RESET_FMT);
    return false;
  }

  thing_player_reached_exit(g, v, l, player);

  return true;
}

bool game_event_ascend(Gamep g)
{
  LOG("Ascend");
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

  if (! level_is_entrance(g, v, l, player->at)) {
    TOPCON(UI_WARNING_FMT_STR "There is no level entrance here to ascend." UI_RESET_FMT);
    return false;
  }

  thing_player_reached_entrance(g, v, l, player);

  return true;
}

bool game_event_help(Gamep g)
{
  LOG("Help");
  TRACE_AND_INDENT();

  wid_cfg_keyboard_select(g);

  return true;
}

bool game_event_quit(Gamep g)
{
  LOG("Quitting");
  TRACE_AND_INDENT();

  if (g_opt_test_start) {
    DIE_CLEAN("Quick quit");
  }
  if (g_opt_test_level_select_menu) {
    DIE_CLEAN("Quick quit");
  }

  wid_quit_select(g);

  return true;
}

uint8_t game_input(Gamep g, const SDL_Keysym *key)
{
  LOG("Pressed a key");
  TRACE_NO_INDENT();

  if (! g) {
    DBG("Pressed a key; no game");
    return false;
  }

  auto v = game_levels_get(g);
  if (! v) {
    DBG("Pressed a key; no levels");
    return false;
  }

  if (sdlk_eq(*key, game_key_console_get(g))) {
    DBG("Pressed a key; over console, ignore");
    return false;
  }

  if (sdlk_eq(*key, game_key_zoom_get(g))) {
    DBG("Zoom alt");
    game_map_zoom_toggle(g);
    return false; // To avoid click noise
  }

  if (sdlk_eq(*key, game_key_wait_get(g))) {
    LOG("Pressed wait key");
    game_event_wait(g);
    return false; // To avoid click noise
  }

  if (sdlk_eq(*key, game_key_ascend_get(g))) {
    LOG("Pressed ascend key");
    game_event_ascend(g);
    return false; // To avoid click noise
  }

  if (sdlk_eq(*key, game_key_descend_get(g))) {
    LOG("Pressed descend key");
    game_event_descend(g);
    return false; // To avoid click noise
  }

  if (sdlk_eq(*key, game_key_quit_get(g))) {
    LOG("Pressed quit key");
    game_event_quit(g);
    return true;
  }

  if (sdlk_eq(*key, game_key_help_get(g))) {
    LOG("Pressed help key");
    TRACE_AND_INDENT();
    game_event_help(g);
    return true;
  }

  if (sdlk_eq(*key, game_key_load_get(g))) {
    LOG("Pressed load key");
    TRACE_AND_INDENT();
    LOG("Loading game");
    game_event_load(g);
    return true;
  }

  if (sdlk_eq(*key, game_key_save_get(g))) {
    LOG("Pressed save key");
    TRACE_AND_INDENT();
    game_event_save(g);
    return true;
  }

  if (sdlk_eq(*key, game_key_ascend_get(g))) {
    LOG("Pressed ascend key");
    game_event_ascend(g);
    return true;
  }

  if (sdlk_eq(*key, game_key_descend_get(g))) {
    LOG("Pressed descend key");
    game_event_descend(g);
    return true;
  }

  return false;
}
