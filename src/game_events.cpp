//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_game.hpp"
#include "my_level.hpp"
#include "my_main.hpp"
#include "my_sdl_proto.hpp"
#include "my_wids.hpp"

//
// Return true on the event being consumed
//
uint8_t game_mouse_down(class Game *game, int x, int y, uint32_t button)
{
  DBG("Game mouse down");
  TRACE_AND_INDENT();

  if (! game) {
    DBG2("Game mouse down; no game or not started");
    return false;
  }

  if (wid_some_recent_event_occurred()) {
    DBG2("Game mouse down; some recent wid event occurred");
    return false;
  }

  return false;
}

uint8_t game_mouse_up(class Game *game, int x, int y, uint32_t button) { return false; }

uint8_t game_mouse_motion(class Game *game, int x, int y, int relx, int rely, int wheelx, int wheely)
{
  DBG2("Game mouse motion");
  TRACE_AND_INDENT();

  if (wid_some_recent_event_occurred()) {
    return false;
  }

  auto l = game_level_get(game);
  if (l) {
    level_scroll_delta(l, wheelx, wheely);
  }

  return true;
}

uint8_t game_input(class Game *game, const SDL_Keysym *key)
{
  TRACE_NO_INDENT();
  DBG("INF: Pressed a key");

  if (! game) {
    DBG("INF: Pressed a key; no game");
    return false;
  }

  auto l = game_level_get(game);
  if (! l) {
    DBG("INF: Pressed a key; no l");
    return false;
  }

  if (sdlk_eq(*key, game_key_console_get(game))) {
    DBG("INF: Pressed a key; over console, ignore");
    return false;
  }

  if (sdlk_eq(*key, game_key_unused1_get(game))) {
    // TODO
    return false; // To avoid click noise
  }

  //
  // attack
  //
  if (sdlk_eq(*key, game_key_attack_get(game))) {
    CON("TODO ATTACK");
    // game->player_tick(left, right, up, down, attack, wait, jump);
    return false; // To avoid click noise
  }

  if (sdlk_eq(*key, game_key_quit_get(game))) {
    LOG("INF: Pressed quit key");
    TRACE_AND_INDENT();
    if (g_opt_test_skip_main_menu) {
      DIE_CLEAN("Quick quit");
    }
    wid_quit_select(game);
    return true;
  }

  if (sdlk_eq(*key, game_key_help_get(game))) {
    LOG("INF: Pressed help key");
    TRACE_AND_INDENT();
    wid_cfg_keyboard_select(game);
    return true;
  }
  if (sdlk_eq(*key, game_key_load_get(game))) {
    LOG("INF: Pressed load key");
    TRACE_AND_INDENT();
    LOG("INF: Loading game");
    wid_load_select(game);
    return true;
  }
  if (sdlk_eq(*key, game_key_save_get(game))) {
    LOG("INF: Pressed save key");
    TRACE_AND_INDENT();
    LOG("INF: Saving the game");
    wid_save_select(game);
    return true;
  }

  return false;
}
