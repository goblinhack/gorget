//
// Copyright Neil McGill, goblinhack@gmail.com
//

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
    level->data->pixel_map_at_x += wheelx;
    level->data->pixel_map_at_y -= wheely;
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

  if (sdlk_eq(*key, game->config.key_zoom_out)) {
    CON("INF: Zoom out.");
    config_game_pix_zoom_out();
    return true;
  }

  if (sdlk_eq(*key, game->config.key_zoom_in)) {
    CON("INF: Zoom in.");
    config_game_pix_zoom_in();
    return true;
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

  //
  // jump
  //
  if (sdlk_eq(*key, game->config.key_jump)) {
    CON("TODO JUMP");
    // game->player_tick(left, right, up, down, attack, wait, jump);
    return false; // To avoid click noise
  }

  if (sdlk_eq(*key, game->config.key_quit)) {
    CON("INF: Pressed quit key");
    TRACE_AND_INDENT();
    game->change_state(Game::STATE_NORMAL, "key press");
    game->quit_select();
    return true;
  }

  if (sdlk_eq(*key, game->config.key_drop)) {
    CON("INF: Pressed drop key");
    TRACE_AND_INDENT();
    return true;
  }

  if (sdlk_eq(*key, game->config.key_help)) {
    CON("INF: Pressed help key");
    TRACE_AND_INDENT();
    game->change_state(Game::STATE_NORMAL, "key press");
    game->wid_cfg_keyboard_select();
    return true;
  }
  if (sdlk_eq(*key, game->config.key_load)) {
    CON("INF: Pressed load key");
    TRACE_AND_INDENT();
    game->change_state(Game::STATE_NORMAL, "key press");
    CON("INF: Loading game");
    game->wid_load_select();
    return true;
  }
  if (sdlk_eq(*key, game->config.key_save)) {
    CON("INF: Pressed save key");
    TRACE_AND_INDENT();
    game->change_state(Game::STATE_NORMAL, "key press");
    CON("INF: Saving the game");
    game->wid_save_select();
    return true;
  }

  if (key->scancode == SDL_SCANCODE_KP_1) {
    // 7 8 9
    // 4   6
    // 1 2 3
    CON("TODO keypad");
    return false; // To avoid click noise
  }
  if (key->scancode == SDL_SCANCODE_KP_2) {
    // 7 8 9
    // 4   6
    // 1 2 3
    CON("TODO keypad");
    return false; // To avoid click noise
  }
  if (key->scancode == SDL_SCANCODE_KP_3) {
    // 7 8 9
    // 4   6
    // 1 2 3
    CON("TODO keypad");
    return false; // To avoid click noise
  }
  if (key->scancode == SDL_SCANCODE_KP_4) {
    // 7 8 9
    // 4   6
    // 1 2 3
    CON("TODO keypad");
    return false; // To avoid click noise
  }
  if (key->scancode == SDL_SCANCODE_KP_6) {
    // 7 8 9
    // 4   6
    // 1 2 3
    CON("TODO keypad");
    return false; // To avoid click noise
  }
  if (key->scancode == SDL_SCANCODE_KP_7) {
    // 7 8 9
    // 4   6
    // 1 2 3
    CON("TODO keypad");
    return false; // To avoid click noise
  }
  if (key->scancode == SDL_SCANCODE_KP_8) {
    // 7 8 9
    // 4   6
    // 1 2 3
    CON("TODO keypad");
    return false; // To avoid click noise
  }
  if (key->scancode == SDL_SCANCODE_KP_9) {
    // 7 8 9
    // 4   6
    // 1 2 3
    CON("TODO keypad");
    return false; // To avoid click noise
  }

  if (sdlk_eq(*key, game->config.key_move_left)) {
    level->player_move_left();
    return false; // To avoid click noise
  }
  if (sdlk_eq(*key, game->config.key_move_right)) {
    level->player_move_right();
    return false; // To avoid click noise
  }
  if (sdlk_eq(*key, game->config.key_move_up)) {
    level->player_move_up();
    return false; // To avoid click noise
  }
  if (sdlk_eq(*key, game->config.key_move_down)) {
    level->player_move_down();
    return false; // To avoid click noise
  }

  return false;
}
