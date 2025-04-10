//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_game.hpp"
#include "my_gl.hpp"
#include "my_level.hpp"
#include "my_main.hpp"
#include "my_sdl_proto.hpp"
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
  if (v) {
    v->player_pressed_button_and_waiting_for_a_path = true;
    return true;
  }

  return false;
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
  if (v) {
    level_scroll_delta(g, v, point(wheelx, -wheely));
  }

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

    if (game_map_zoom_get(g) == 1) {
      game_map_zoom_set(g, 2);
    } else {
      game_map_zoom_set(g, 1);
    }

    //
    // Need to resize the map buffers and re-center
    //
    config_game_gfx_update(g);
    gl_init_fbo(g, FBO_MAP);

    //
    // If following the player already, then no need to re-center
    //
    if (! v->requested_auto_scroll) {
      level_scroll_warp_to_player(g, v);
    }

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
    LOG("Pressed quit key");
    TRACE_AND_INDENT();
    if (g_opt_test_start) {
      DIE_CLEAN("Quick quit");
    }
    wid_quit_select(g);
    return true;
  }

  if (sdlk_eq(*key, game_key_help_get(g))) {
    LOG("Pressed help key");
    TRACE_AND_INDENT();
    wid_cfg_keyboard_select(g);
    return true;
  }
  if (sdlk_eq(*key, game_key_load_get(g))) {
    LOG("Pressed load key");
    TRACE_AND_INDENT();
    LOG("Loading game");
    wid_load_select(g);
    return true;
  }
  if (sdlk_eq(*key, game_key_save_get(g))) {
    LOG("Pressed save key");
    TRACE_AND_INDENT();
    LOG("Saving the game");
    wid_save_select(g);
    return true;
  }

  return false;
}
