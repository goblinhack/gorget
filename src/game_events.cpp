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
uint8_t game_mouse_down(class Game *g, int x, int y, uint32_t button)
{
  DBG("Game mouse down");
  TRACE_AND_INDENT();

  if (wid_some_recent_event_occurred()) {
    return false;
  }

  if (! g) {
    return false;
  }

  //
  // Follow the mouse path?
  //
  auto l = game_level_get(g);
  if (l) {
    l->request_follow_path = true;
    return true;
  }

  return false;
}

uint8_t game_mouse_up(class Game *g, int x, int y, uint32_t button) { return false; }

uint8_t game_mouse_motion(class Game *g, int x, int y, int relx, int rely, int wheelx, int wheely)
{
  DBG2("Game mouse motion");
  TRACE_AND_INDENT();

  if (wid_some_recent_event_occurred()) {
    return false;
  }

  auto l = game_level_get(g);
  if (l) {
    level_scroll_delta(l, point(wheelx, -wheely));
  }

  return true;
}

uint8_t game_input(class Game *g, const SDL_Keysym *key)
{
  TRACE_NO_INDENT();
  DBG("INF: Pressed a key");

  if (! g) {
    DBG("INF: Pressed a key; no game");
    return false;
  }

  auto l = game_level_get(g);
  if (! l) {
    DBG("INF: Pressed a key; no l");
    return false;
  }

  if (sdlk_eq(*key, game_key_console_get(g))) {
    DBG("INF: Pressed a key; over console, ignore");
    return false;
  }

  if (sdlk_eq(*key, game_key_unused1_get(g))) {
    // TODO
    return false; // To avoid click noise
  }

  //
  // attack
  //
  if (sdlk_eq(*key, game_key_attack_get(g))) {
    CON("TODO ATTACK");
    // g->player_tick(left, right, up, down, attack, wait, jump);
    return false; // To avoid click noise
  }

  if (sdlk_eq(*key, game_key_quit_get(g))) {
    LOG("INF: Pressed quit key");
    TRACE_AND_INDENT();
    if (g_opt_quick_start) {
      DIE_CLEAN("Quick quit");
    }
    wid_quit_select(g);
    return true;
  }

  if (sdlk_eq(*key, game_key_help_get(g))) {
    LOG("INF: Pressed help key");
    TRACE_AND_INDENT();
    wid_cfg_keyboard_select(g);
    return true;
  }
  if (sdlk_eq(*key, game_key_load_get(g))) {
    LOG("INF: Pressed load key");
    TRACE_AND_INDENT();
    LOG("INF: Loading g");
    wid_load_select(g);
    return true;
  }
  if (sdlk_eq(*key, game_key_save_get(g))) {
    LOG("INF: Pressed save key");
    TRACE_AND_INDENT();
    LOG("INF: Saving the g");
    wid_save_select(g);
    return true;
  }

  return false;
}
