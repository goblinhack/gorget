//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_game.hpp"
#include "my_level.hpp"
#include "my_sdl_proto.hpp"
#include "my_wid.hpp"

//
// Return true on the event being consumed
//
uint8_t game_mouse_down(int x, int y, uint32_t button)
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

uint8_t game_mouse_up(int x, int y, uint32_t button) { return false; }

uint8_t game_mouse_motion(int x, int y, int relx, int rely, int wheelx, int wheely)
{
  DBG2("Game mouse motion");
  TRACE_AND_INDENT();

  if (wid_some_recent_event_occurred()) {
    return false;
  }

  auto level = game->level;
  if (level) {
    level->scroll_delta(wheelx, wheely);
  }

  return true;
}

uint8_t game_input(const SDL_Keysym *key)
{
  TRACE_NO_INDENT();
  DBG("INF: Pressed a key");

  if (! game) {
    DBG("INF: Pressed a key; no game");
    return false;
  }

  auto level = game->level;
  if (! level) {
    DBG("INF: Pressed a key; no level");
    return false;
  }

  if (sdlk_eq(*key, game->config.key_console)) {
    DBG("INF: Pressed a key; over console, ignore");
    return false;
  }

  if (sdlk_eq(*key, game->config.key_unused1)) {
    // TODO
    return false; // To avoid click noise
  }

  if (sdlk_eq(*key, game->config.key_unused2)) {
    // TODO
    return false; // To avoid click noise
  }

  if (sdlk_eq(*key, game->config.key_unused3)) {
    // TODO
    return false; // To avoid click noise
  }

  if (sdlk_eq(*key, game->config.key_unused4)) {
    // TODO
    return false; // To avoid click noise
  }

  if (sdlk_eq(*key, game->config.key_unused5)) {
    // TODO
    return false; // To avoid click noise
  }

  if (sdlk_eq(*key, game->config.key_unused6)) {
    // TODO
    return false; // To avoid click noise
  }

  if (sdlk_eq(*key, game->config.key_unused7)) {
    // TODO
    return false; // To avoid click noise
  }

  if (sdlk_eq(*key, game->config.key_unused8)) {
    // TODO
    return false; // To avoid click noise
  }

  if (sdlk_eq(*key, game->config.key_unused9)) {
    // TODO
    return false; // To avoid click noise
  }

  if (sdlk_eq(*key, game->config.key_unused10)) {
    // TODO
    return false; // To avoid click noise
  }

  if (sdlk_eq(*key, game->config.key_unused11)) {
    // TODO
    return false; // To avoid click noise
  }

  if (sdlk_eq(*key, game->config.key_unused12)) {
    // TODO
    return false; // To avoid click noise
  }

  if (sdlk_eq(*key, game->config.key_unused13)) {
    // TODO
    return false; // To avoid click noise
  }

  if (sdlk_eq(*key, game->config.key_unused14)) {
    // TODO
    return false; // To avoid click noise
  }

  if (sdlk_eq(*key, game->config.key_unused15)) {
    // TODO
    return false; // To avoid click noise
  }

  if (sdlk_eq(*key, game->config.key_unused16)) {
    // TODO
    return false; // To avoid click noise
  }

  if (sdlk_eq(*key, game->config.key_unused17)) {
    // TODO
    return false; // To avoid click noise
  }

  if (sdlk_eq(*key, game->config.key_unused18)) {
    // TODO
    return false; // To avoid click noise
  }

  if (sdlk_eq(*key, game->config.key_unused19)) {
    // TODO
    return false; // To avoid click noise
  }

  if (sdlk_eq(*key, game->config.key_unused20)) {
    // TODO
    return false; // To avoid click noise
  }

  //
  // attack
  //
  if (sdlk_eq(*key, game->config.key_attack)) {
    CON("TODO ATTACK");
    // game->player_tick(left, right, up, down, attack, wait, jump);
    return false; // To avoid click noise
  }

  if (sdlk_eq(*key, game->config.key_quit)) {
    LOG("INF: Pressed quit key");
    TRACE_AND_INDENT();
    if (g_opt_test_skip_main_menu) {
      DIE_CLEAN("Quick quit");
    }
    game->wid_quit_select();
    return true;
  }

  if (sdlk_eq(*key, game->config.key_help)) {
    LOG("INF: Pressed help key");
    TRACE_AND_INDENT();
    game->wid_cfg_keyboard_select();
    return true;
  }
  if (sdlk_eq(*key, game->config.key_load)) {
    LOG("INF: Pressed load key");
    TRACE_AND_INDENT();
    LOG("INF: Loading game");
    game->wid_load_select();
    return true;
  }
  if (sdlk_eq(*key, game->config.key_save)) {
    LOG("INF: Pressed save key");
    TRACE_AND_INDENT();
    LOG("INF: Saving the game");
    game->wid_save_select();
    return true;
  }

  return false;
}
