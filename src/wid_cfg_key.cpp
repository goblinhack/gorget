//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_ascii.hpp"
#include "my_callstack.hpp"
#include "my_color_defs.hpp"
#include "my_game.hpp"
#include "my_main.hpp"
#include "my_sdl_event.hpp"
#include "my_sdl_proto.hpp"
#include "my_wid_notice.hpp"
#include "my_wids.hpp"

static int  last_vert_scroll_offset = -1;
WidPopup   *wid_cfg_keyboard_window;
static bool local_g_config_changed;

static void wid_cfg_check_for_conflicts(Gamep g, SDL_Keysym code)
{
  TRACE_NO_INDENT();
  SDL_Keysym none = {};

  if (sdlk_eq(game_key_help_get(g), code)) {
    CON("%%fg=orange$Conflicting keyboard mapping, disabling key help.%%fg=reset$");
    game_key_help_set(g, none);
  }
  if (sdlk_eq(game_key_load_get(g), code)) {
    CON("%%fg=orange$Conflicting keyboard mapping, disabling key load.%%fg=reset$");
    game_key_load_set(g, none);
  }
  if (sdlk_eq(game_key_move_down_get(g), code)) {
    CON("%%fg=orange$Conflicting keyboard mapping, disabling key move down.%%fg=reset$");
    game_key_move_down_set(g, none);
  }
  if (sdlk_eq(game_key_move_left_get(g), code)) {
    CON("%%fg=orange$Conflicting keyboard mapping, disabling key move left.%%fg=reset$");
    game_key_move_left_set(g, none);
  }
  if (sdlk_eq(game_key_move_right_get(g), code)) {
    CON("%%fg=orange$Conflicting keyboard mapping, disabling key move right.%%fg=reset$");
    game_key_move_right_set(g, none);
  }
  if (sdlk_eq(game_key_move_up_get(g), code)) {
    CON("%%fg=orange$Conflicting keyboard mapping, disabling key move up.%%fg=reset$");
    game_key_move_up_set(g, none);
  }
  if (sdlk_eq(game_key_quit_get(g), code)) {
    CON("%%fg=orange$Conflicting keyboard mapping, disabling key quit.%%fg=reset$");
    game_key_quit_set(g, none);
  }
  if (sdlk_eq(game_key_save_get(g), code)) {
    CON("%%fg=orange$Conflicting keyboard mapping, disabling key save.%%fg=reset$");
    game_key_save_set(g, none);
  }
  if (sdlk_eq(game_key_screenshot_get(g), code)) {
    CON("%%fg=orange$Conflicting keyboard mapping, disabling key screenshot.%%fg=reset$");
    game_key_screenshot_set(g, none);
  }
  if (sdlk_eq(game_key_console_get(g), code)) {
    CON("%%fg=orange$Conflicting keyboard mapping, disabling key console%%fg=reset$");
    game_key_console_set(g, none);
  }
  if (sdlk_eq(game_key_unused1_get(g), code)) {
    CON("%%fg=orange$Conflicting keyboard mapping, disabling key unused1%%fg=reset$");
    game_key_unused1_set(g, none);
  }
}

void wid_cfg_keyboard_destroy(Gamep g)
{
  TRACE_NO_INDENT();
  local_g_config_changed = false;

  if (! wid_cfg_keyboard_window) {
    return;
  }

  auto w                  = wid_cfg_keyboard_window->wid_text_area->wid_vert_scroll;
  last_vert_scroll_offset = wid_get_tl_y(w) - wid_get_tl_y(wid_get_parent(w));

  delete wid_cfg_keyboard_window;
  wid_cfg_keyboard_window = nullptr;
  game_state_reset(g, "wid keyboard destroy");
}

static bool wid_cfg_keyboard_cancel(Gamep g, Widp w, int x, int y, uint32_t button)
{
  TRACE_NO_INDENT();
  CON("Reload config");
  if (local_g_config_changed) {
    local_g_config_changed = false;
    game_load_config(g);
  }
  wid_cfg_keyboard_destroy(g);

  if (game_levels_get(g)) {
    //
    // Back to the game
    //
  } else {
    wid_cfg_top_menu(g);
  }

  return true;
}

static bool wid_cfg_keyboard_save(Gamep g, Widp w, int x, int y, uint32_t button)
{
  TRACE_NO_INDENT();
  CON("Save config");
  game_save_config(g);
  wid_cfg_keyboard_destroy(g);

  if (game_levels_get(g)) {
    //
    // Back to the game
    //
  } else {
    wid_cfg_top_menu(g);
  }

  return true;
}

static bool wid_cfg_keyboard_back(Gamep g, Widp w, int x, int y, uint32_t button)
{
  TRACE_NO_INDENT();
  wid_cfg_keyboard_destroy(g);

  if (game_levels_get(g)) {
    //
    // Back to the game
    //
  } else {
    wid_cfg_top_menu(g);
  }

  return true;
}

static SDL_Keysym none = {};

static void wid_cfg_key_move_left_set(Gamep g, SDL_Keysym code)
{
  TRACE_NO_INDENT();
  local_g_config_changed = true;
  game_key_move_left_set(g, none);
  wid_cfg_check_for_conflicts(g, code);
  game_key_move_left_set(g, code);
  wid_cfg_keyboard_select(g);
}

static void wid_cfg_key_move_right_set(Gamep g, SDL_Keysym code)
{
  TRACE_NO_INDENT();
  local_g_config_changed = true;
  game_key_move_right_set(g, none);
  wid_cfg_check_for_conflicts(g, code);
  game_key_move_right_set(g, code);
  wid_cfg_keyboard_select(g);
}

static void wid_cfg_key_move_up_set(Gamep g, SDL_Keysym code)
{
  TRACE_NO_INDENT();
  local_g_config_changed = true;
  game_key_move_up_set(g, none);
  wid_cfg_check_for_conflicts(g, code);
  game_key_move_up_set(g, code);
  wid_cfg_keyboard_select(g);
}

static void wid_cfg_key_move_down_set(Gamep g, SDL_Keysym code)
{
  TRACE_NO_INDENT();
  local_g_config_changed = true;
  game_key_move_down_set(g, none);
  wid_cfg_check_for_conflicts(g, code);
  game_key_move_down_set(g, code);
  wid_cfg_keyboard_select(g);
}

static void wid_cfg_key_attack_set(Gamep g, SDL_Keysym code)
{
  TRACE_NO_INDENT();
  local_g_config_changed = true;
  game_key_attack_set(g, none);
  wid_cfg_check_for_conflicts(g, code);
  game_key_attack_set(g, code);
  wid_cfg_keyboard_select(g);
}

static void wid_cfg_key_unused1_set(Gamep g, SDL_Keysym code)
{
  TRACE_NO_INDENT();
  local_g_config_changed = true;
  game_key_unused1_set(g, none);
  wid_cfg_check_for_conflicts(g, code);
  game_key_unused1_set(g, code);
  wid_cfg_keyboard_select(g);
}

static void wid_cfg_key_save_set(Gamep g, SDL_Keysym code)
{
  TRACE_NO_INDENT();
  local_g_config_changed = true;
  game_key_save_set(g, none);
  wid_cfg_check_for_conflicts(g, code);
  game_key_save_set(g, code);
  wid_cfg_keyboard_select(g);
}

static void wid_cfg_key_load_set(Gamep g, SDL_Keysym code)
{
  TRACE_NO_INDENT();
  local_g_config_changed = true;
  game_key_load_set(g, none);
  wid_cfg_check_for_conflicts(g, code);
  game_key_load_set(g, code);
  wid_cfg_keyboard_select(g);
}

static void wid_cfg_key_help_set(Gamep g, SDL_Keysym code)
{
  TRACE_NO_INDENT();
  local_g_config_changed = true;
  game_key_help_set(g, none);
  wid_cfg_check_for_conflicts(g, code);
  game_key_help_set(g, code);
  wid_cfg_keyboard_select(g);
}

static void wid_cfg_key_console_set(Gamep g, SDL_Keysym code)
{
  TRACE_NO_INDENT();
  local_g_config_changed = true;
  game_key_console_set(g, none);
  wid_cfg_check_for_conflicts(g, code);
  game_key_console_set(g, code);
  wid_cfg_keyboard_select(g);
}

static void wid_cfg_key_quit_set(Gamep g, SDL_Keysym code)
{
  TRACE_NO_INDENT();
  local_g_config_changed = true;
  game_key_quit_set(g, none);
  wid_cfg_check_for_conflicts(g, code);
  game_key_quit_set(g, code);
  wid_cfg_keyboard_select(g);
}

static void wid_cfg_key_screenshot_set(Gamep g, SDL_Keysym code)
{
  TRACE_NO_INDENT();
  local_g_config_changed = true;
  game_key_screenshot_set(g, none);
  wid_cfg_check_for_conflicts(g, code);
  game_key_screenshot_set(g, code);
  wid_cfg_keyboard_select(g);
}

static void grab_key(Gamep g, const std::string which)
{
  TRACE_NO_INDENT();
  wid_notice("Press a key for " + which);
  g_grab_next_key        = true;
  local_g_config_changed = true;
}

static bool wid_cfg_keyboard_profile_arrow_keys(Gamep g, Widp w, int x, int y, uint32_t button)
{
  TRACE_NO_INDENT();
  SDL_Keysym k {};

  local_g_config_changed = true;
  game_key_move_up_set(g, none);
  k.sym = SDLK_UP;
  wid_cfg_check_for_conflicts(g, k);
  game_key_move_up_set(g, k);

  game_key_move_left_set(g, none);
  k.sym = SDLK_LEFT;
  wid_cfg_check_for_conflicts(g, k);
  game_key_move_left_set(g, k);

  game_key_move_down_set(g, none);
  k.sym = SDLK_DOWN;
  wid_cfg_check_for_conflicts(g, k);
  game_key_move_down_set(g, k);

  game_key_move_right_set(g, none);
  k.sym = SDLK_RIGHT;
  wid_cfg_check_for_conflicts(g, k);
  game_key_move_right_set(g, k);

  wid_cfg_keyboard_select(g);

  return true;
}

static bool wid_cfg_keyboard_profile_wasd(Gamep g, Widp w, int x, int y, uint32_t button)
{
  TRACE_NO_INDENT();
  SDL_Keysym k = {};

  local_g_config_changed = true;
  game_key_move_up_set(g, none);
  k.sym = SDLK_w;
  wid_cfg_check_for_conflicts(g, k);
  game_key_move_up_set(g, k);

  game_key_move_left_set(g, none);
  k.sym = SDLK_a;
  wid_cfg_check_for_conflicts(g, k);
  game_key_move_left_set(g, k);

  game_key_move_down_set(g, none);
  k.sym = SDLK_s;
  wid_cfg_check_for_conflicts(g, k);
  game_key_move_down_set(g, k);

  game_key_move_right_set(g, none);
  k.sym = SDLK_d;
  wid_cfg_check_for_conflicts(g, k);
  game_key_move_right_set(g, k);

  wid_cfg_keyboard_select(g);

  return true;
}

static bool wid_cfg_key_move_left(Gamep g, Widp w, int x, int y, uint32_t button)
{
  TRACE_NO_INDENT();
  grab_key(g, "move left");
  sdl.on_sdl_key_grab    = wid_cfg_key_move_left_set;
  local_g_config_changed = true;
  return true;
}

static bool wid_cfg_key_move_right(Gamep g, Widp w, int x, int y, uint32_t button)
{
  TRACE_NO_INDENT();
  grab_key(g, "move right");
  sdl.on_sdl_key_grab    = wid_cfg_key_move_right_set;
  local_g_config_changed = true;
  return true;
}

static bool wid_cfg_key_move_up(Gamep g, Widp w, int x, int y, uint32_t button)
{
  TRACE_NO_INDENT();
  grab_key(g, "move up");
  sdl.on_sdl_key_grab    = wid_cfg_key_move_up_set;
  local_g_config_changed = true;
  return true;
}

static bool wid_cfg_key_move_down(Gamep g, Widp w, int x, int y, uint32_t button)
{
  TRACE_NO_INDENT();
  grab_key(g, "move down");
  sdl.on_sdl_key_grab    = wid_cfg_key_move_down_set;
  local_g_config_changed = true;
  return true;
}

static bool wid_cfg_key_attack(Gamep g, Widp w, int x, int y, uint32_t button)
{
  TRACE_NO_INDENT();
  grab_key(g, "attack");
  sdl.on_sdl_key_grab    = wid_cfg_key_attack_set;
  local_g_config_changed = true;
  return true;
}

static bool wid_cfg_key_unused1(Gamep g, Widp w, int x, int y, uint32_t button)
{
  TRACE_NO_INDENT();
  grab_key(g, "item unused1");
  sdl.on_sdl_key_grab    = wid_cfg_key_unused1_set;
  local_g_config_changed = true;
  return true;
}

static bool wid_cfg_key_save(Gamep g, Widp w, int x, int y, uint32_t button)
{
  TRACE_NO_INDENT();
  grab_key(g, "save game");
  sdl.on_sdl_key_grab    = wid_cfg_key_save_set;
  local_g_config_changed = true;
  return true;
}

static bool wid_cfg_key_load(Gamep g, Widp w, int x, int y, uint32_t button)
{
  TRACE_NO_INDENT();
  grab_key(g, "load game");
  sdl.on_sdl_key_grab    = wid_cfg_key_load_set;
  local_g_config_changed = true;
  return true;
}

static bool wid_cfg_key_help(Gamep g, Widp w, int x, int y, uint32_t button)
{
  TRACE_NO_INDENT();
  grab_key(g, "help");
  sdl.on_sdl_key_grab    = wid_cfg_key_help_set;
  local_g_config_changed = true;
  return true;
}

static bool wid_cfg_key_console(Gamep g, Widp w, int x, int y, uint32_t button)
{
  TRACE_NO_INDENT();
  grab_key(g, "toggle console");
  sdl.on_sdl_key_grab    = wid_cfg_key_console_set;
  local_g_config_changed = true;
  return true;
}

static bool wid_cfg_key_quit(Gamep g, Widp w, int x, int y, uint32_t button)
{
  TRACE_NO_INDENT();
  grab_key(g, "quit");
  sdl.on_sdl_key_grab    = wid_cfg_key_quit_set;
  local_g_config_changed = true;
  return true;
}

static bool wid_cfg_key_screenshot(Gamep g, Widp w, int x, int y, uint32_t button)
{
  TRACE_NO_INDENT();
  grab_key(g, "screenshot grab");
  local_g_config_changed = true;
  sdl.on_sdl_key_grab    = wid_cfg_key_screenshot_set;
  return true;
}

static bool wid_cfg_keyboard_key_up(Gamep g, Widp w, const struct SDL_Keysym *key)
{
  TRACE_NO_INDENT();

  if (sdlk_eq(*key, game_key_console_get(g))) {
    return false;
  }

  switch (key->mod) {
    case KMOD_LCTRL :
    case KMOD_RCTRL :
    default :
      switch (key->sym) {
        default :
          {
            TRACE_NO_INDENT();
            auto c = wid_event_to_char(key);
            switch (c) {
              case 'b' :
              case 'B' :
              case SDLK_ESCAPE : wid_cfg_keyboard_cancel(g, nullptr, 0, 0, 0); return true;
            }
          }
      }
  }

  return false;
}

static bool wid_cfg_keyboard_key_down(Gamep g, Widp w, const struct SDL_Keysym *key)
{
  TRACE_NO_INDENT();

  if (sdlk_eq(*key, game_key_console_get(g))) {
    return false;
  }

  return true;
}

void wid_cfg_keyboard_select(Gamep g)
{
  TRACE_NO_INDENT();
  wid_notice_destroy();

  if (wid_cfg_keyboard_window) {
    wid_cfg_keyboard_destroy(g);
  }

  auto box_style           = UI_WID_STYLE_HORIZ_DARK;
  auto box_highlight_style = UI_WID_STYLE_HORIZ_LIGHT;
  auto m                   = TERM_WIDTH / 2;

  point outer_tl(m - TERM_WIDTH / 4, 10);
  point outer_br(m + TERM_WIDTH / 4, TERM_HEIGHT - 10);
  auto  width = outer_br.x - outer_tl.x;

  wid_cfg_keyboard_window = new WidPopup(g, "Keyboard select", outer_tl, outer_br, nullptr, "", false, true);

  {
    TRACE_NO_INDENT();
    Widp w = wid_cfg_keyboard_window->wid_popup_container;
    wid_set_on_key_up(g, w, wid_cfg_keyboard_key_up);
    wid_set_on_key_down(g, w, wid_cfg_keyboard_key_down);
    wid_set_style(w, UI_WID_STYLE_NORMAL);
  }

  auto rhs_button_left  = 5;
  auto rhs_button_right = 33;

  int y_at = 0;
  {
    TRACE_NO_INDENT();
    auto p = wid_cfg_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(g, p, "Keyboard");

    point tl(0, y_at);
    point br(width, y_at);
    wid_set_shape_none(w);
    wid_set_pos(w, tl, br);
    wid_set_text(w, "Keyboard");
  }

  y_at = 2;
  {
    TRACE_NO_INDENT();
    auto p = wid_cfg_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(g, p, "Back");

    point tl(1, y_at);
    point br(8, y_at + 2);
    wid_set_shape_square(w);
    wid_set_style(w, UI_WID_STYLE_NORMAL);
    wid_set_on_mouse_up(g, w, wid_cfg_keyboard_back);
    wid_set_pos(w, tl, br);
    wid_set_text(w, "Back");
  }
  {
    TRACE_NO_INDENT();
    auto p = wid_cfg_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(g, p, "Save");

    point tl(width - 17, y_at);
    point br(width - 12, y_at + 2);
    wid_set_style(w, UI_WID_STYLE_GREEN);
    wid_set_on_mouse_up(g, w, wid_cfg_keyboard_save);
    wid_set_pos(w, tl, br);
    wid_set_text(w, "Save");
  }
  {
    TRACE_NO_INDENT();
    auto p = wid_cfg_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(g, p, "Cancel");

    point tl(width - 10, y_at);
    point br(width - 3, y_at + 2);
    wid_set_style(w, UI_WID_STYLE_RED);
    wid_set_on_mouse_up(g, w, wid_cfg_keyboard_cancel);
    wid_set_pos(w, tl, br);
    wid_set_text(w, "Cancel");
  }

  ///////////////////////////////////////////////////////////////////////
  y_at++;
  ///////////////////////////////////////////////////////////////////////

  y_at += 3;
  {
    TRACE_NO_INDENT();
    auto p = wid_cfg_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(g, p, "");

    point tl(1, y_at);
    point br(width - 3, y_at);
    wid_set_mode(g, w, WID_MODE_OVER);
    wid_set_style(w, box_highlight_style);
    wid_set_mode(g, w, WID_MODE_NORMAL);
    wid_set_style(w, box_style);
    wid_set_on_mouse_up(g, w, wid_cfg_keyboard_profile_wasd);
    wid_set_pos(w, tl, br);
    wid_set_text(w, "Use W,A,S,D for moving");
  }
  y_at++;
  {
    TRACE_NO_INDENT();
    auto p = wid_cfg_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(g, p, "");

    point tl(1, y_at);
    point br(width - 3, y_at);
    wid_set_mode(g, w, WID_MODE_OVER);
    wid_set_style(w, box_highlight_style);
    wid_set_mode(g, w, WID_MODE_NORMAL);
    wid_set_style(w, box_style);
    wid_set_on_mouse_up(g, w, wid_cfg_keyboard_profile_arrow_keys);
    wid_set_pos(w, tl, br);
    wid_set_text(w, "Use arrow keys for moving");
  }

  y_at++;
  ///////////////////////////////////////////////////////////////////////
  // save
  ///////////////////////////////////////////////////////////////////////
  y_at++;
  {
    TRACE_NO_INDENT();
    auto p = wid_cfg_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(g, p, "save");

    point tl(1, y_at);
    point br(width / 2, y_at);
    wid_set_shape_none(w);
    wid_set_pos(w, tl, br);
    wid_set_text_lhs(w, true);
    wid_set_text(w, "Save game");
  }
  {
    TRACE_NO_INDENT();
    auto p = wid_cfg_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(g, p, "value");

    point tl(width / 2 + rhs_button_left, y_at);
    point br(width / 2 + rhs_button_right, y_at);
    wid_set_mode(g, w, WID_MODE_OVER);
    wid_set_style(w, box_highlight_style);
    wid_set_mode(g, w, WID_MODE_NORMAL);
    wid_set_style(w, box_style);
    wid_set_pos(w, tl, br);
    wid_set_text(w, ::to_string(game_key_save_get(g)));
    wid_set_on_mouse_up(g, w, wid_cfg_key_save);
  }
  ///////////////////////////////////////////////////////////////////////
  // load
  ///////////////////////////////////////////////////////////////////////
  y_at++;
  {
    TRACE_NO_INDENT();
    auto p = wid_cfg_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(g, p, "load");

    point tl(1, y_at);
    point br(width / 2, y_at);
    wid_set_shape_none(w);
    wid_set_pos(w, tl, br);
    wid_set_text_lhs(w, true);
    wid_set_text(w, "Load game");
  }
  {
    TRACE_NO_INDENT();
    auto p = wid_cfg_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(g, p, "value");

    point tl(width / 2 + rhs_button_left, y_at);
    point br(width / 2 + rhs_button_right, y_at);
    wid_set_mode(g, w, WID_MODE_OVER);
    wid_set_style(w, box_highlight_style);
    wid_set_mode(g, w, WID_MODE_NORMAL);
    wid_set_style(w, box_style);
    wid_set_pos(w, tl, br);
    wid_set_text(w, ::to_string(game_key_load_get(g)));
    wid_set_on_mouse_up(g, w, wid_cfg_key_load);
  }

  ///////////////////////////////////////////////////////////////////////
  // Move up
  ///////////////////////////////////////////////////////////////////////
  y_at += 2;
  {
    TRACE_NO_INDENT();
    auto p = wid_cfg_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(g, p, "Move up");

    point tl(1, y_at);
    point br(width / 2, y_at);
    wid_set_shape_none(w);
    wid_set_pos(w, tl, br);
    wid_set_text_lhs(w, true);
    wid_set_mode(g, w, WID_MODE_OVER);
    wid_set_style(w, box_highlight_style);
    wid_set_mode(g, w, WID_MODE_NORMAL);
    wid_set_style(w, box_style);
    wid_set_text(w, "Move up");
  }
  {
    TRACE_NO_INDENT();
    auto p = wid_cfg_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(g, p, "value");

    point tl(width / 2 + rhs_button_left, y_at);
    point br(width / 2 + rhs_button_right, y_at);
    wid_set_color(w, WID_COLOR_BG, WHITE);
    wid_set_color(w, WID_COLOR_TEXT_FG, WHITE);
    wid_set_mode(g, w, WID_MODE_OVER);
    wid_set_style(w, box_highlight_style);
    wid_set_mode(g, w, WID_MODE_NORMAL);
    wid_set_style(w, box_style);
    wid_set_pos(w, tl, br);
    wid_set_text(w, ::to_string(game_key_move_up_get(g)));
    wid_set_on_mouse_up(g, w, wid_cfg_key_move_up);
  }
  ///////////////////////////////////////////////////////////////////////
  // Move left
  ///////////////////////////////////////////////////////////////////////
  y_at++;
  {
    TRACE_NO_INDENT();
    auto p = wid_cfg_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(g, p, "Move left");

    point tl(1, y_at);
    point br(width / 2, y_at);
    wid_set_shape_none(w);
    wid_set_pos(w, tl, br);
    wid_set_text_lhs(w, true);
    wid_set_text(w, "Move left");
  }
  {
    TRACE_NO_INDENT();
    auto p = wid_cfg_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(g, p, "value");

    point tl(width / 2 + rhs_button_left, y_at);
    point br(width / 2 + rhs_button_right, y_at);
    wid_set_mode(g, w, WID_MODE_OVER);
    wid_set_style(w, box_highlight_style);
    wid_set_mode(g, w, WID_MODE_NORMAL);
    wid_set_style(w, box_style);
    wid_set_pos(w, tl, br);
    wid_set_text(w, ::to_string(game_key_move_left_get(g)));
    wid_set_on_mouse_up(g, w, wid_cfg_key_move_left);
  }
  ///////////////////////////////////////////////////////////////////////
  // Move down
  ///////////////////////////////////////////////////////////////////////
  y_at++;
  {
    TRACE_NO_INDENT();
    auto p = wid_cfg_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(g, p, "Move down");

    point tl(1, y_at);
    point br(width / 2, y_at);
    wid_set_shape_none(w);
    wid_set_pos(w, tl, br);
    wid_set_text_lhs(w, true);
    wid_set_text(w, "Move down");
  }
  {
    TRACE_NO_INDENT();
    auto p = wid_cfg_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(g, p, "value");

    point tl(width / 2 + rhs_button_left, y_at);
    point br(width / 2 + rhs_button_right, y_at);
    wid_set_mode(g, w, WID_MODE_OVER);
    wid_set_style(w, box_highlight_style);
    wid_set_mode(g, w, WID_MODE_NORMAL);
    wid_set_style(w, box_style);
    wid_set_pos(w, tl, br);
    wid_set_text(w, ::to_string(game_key_move_down_get(g)));
    wid_set_on_mouse_up(g, w, wid_cfg_key_move_down);
  }
  ///////////////////////////////////////////////////////////////////////
  // Move right
  ///////////////////////////////////////////////////////////////////////
  y_at++;
  {
    TRACE_NO_INDENT();
    auto p = wid_cfg_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(g, p, "Move right");

    point tl(1, y_at);
    point br(width / 2, y_at);
    wid_set_shape_none(w);
    wid_set_pos(w, tl, br);
    wid_set_text_lhs(w, true);
    wid_set_text(w, "Move right");
  }
  {
    TRACE_NO_INDENT();
    auto p = wid_cfg_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(g, p, "value");

    point tl(width / 2 + rhs_button_left, y_at);
    point br(width / 2 + rhs_button_right, y_at);
    wid_set_mode(g, w, WID_MODE_OVER);
    wid_set_style(w, box_highlight_style);
    wid_set_mode(g, w, WID_MODE_NORMAL);
    wid_set_style(w, box_style);
    wid_set_pos(w, tl, br);
    wid_set_text(w, ::to_string(game_key_move_right_get(g)));
    wid_set_on_mouse_up(g, w, wid_cfg_key_move_right);
  }

  ///////////////////////////////////////////////////////////////////////
  y_at++;
  ///////////////////////////////////////////////////////////////////////

  ///////////////////////////////////////////////////////////////////////
  // attack
  ///////////////////////////////////////////////////////////////////////
  y_at++;
  {
    TRACE_NO_INDENT();
    auto p = wid_cfg_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(g, p, "Attack");

    point tl(1, y_at);
    point br(width / 2, y_at);
    wid_set_shape_none(w);
    wid_set_pos(w, tl, br);
    wid_set_text_lhs(w, true);
    wid_set_text(w, "Attack");
  }
  {
    TRACE_NO_INDENT();
    auto p = wid_cfg_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(g, p, "value");

    point tl(width / 2 + rhs_button_left, y_at);
    point br(width / 2 + rhs_button_right, y_at);
    wid_set_mode(g, w, WID_MODE_OVER);
    wid_set_style(w, box_highlight_style);
    wid_set_mode(g, w, WID_MODE_NORMAL);
    wid_set_style(w, box_style);
    wid_set_pos(w, tl, br);
    wid_set_text(w, ::to_string(game_key_attack_get(g)));
    wid_set_on_mouse_up(g, w, wid_cfg_key_attack);
  }

  ///////////////////////////////////////////////////////////////////////
  y_at++;
  ///////////////////////////////////////////////////////////////////////

  ///////////////////////////////////////////////////////////////////////
  // screenshot
  ///////////////////////////////////////////////////////////////////////
  y_at++;
  {
    TRACE_NO_INDENT();
    auto p = wid_cfg_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(g, p, "Take a screenshot");

    point tl(1, y_at);
    point br(width / 2, y_at);
    wid_set_shape_none(w);
    wid_set_pos(w, tl, br);
    wid_set_text_lhs(w, true);
    wid_set_text(w, "Take a screenshot");
  }
  {
    TRACE_NO_INDENT();
    auto p = wid_cfg_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(g, p, "value");

    point tl(width / 2 + rhs_button_left, y_at);
    point br(width / 2 + rhs_button_right, y_at);
    wid_set_mode(g, w, WID_MODE_OVER);
    wid_set_style(w, box_highlight_style);
    wid_set_mode(g, w, WID_MODE_NORMAL);
    wid_set_style(w, box_style);
    wid_set_pos(w, tl, br);
    wid_set_text(w, ::to_string(game_key_screenshot_get(g)));
    wid_set_on_mouse_up(g, w, wid_cfg_key_screenshot);
  }

  ///////////////////////////////////////////////////////////////////////
  y_at++;
  ///////////////////////////////////////////////////////////////////////

  ///////////////////////////////////////////////////////////////////////
  // quit
  ///////////////////////////////////////////////////////////////////////
  y_at++;
  {
    TRACE_NO_INDENT();
    auto p = wid_cfg_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(g, p, "quit");

    point tl(1, y_at);
    point br(width / 2, y_at);
    wid_set_shape_none(w);
    wid_set_pos(w, tl, br);
    wid_set_text_lhs(w, true);
    wid_set_text(w, "Quit");
  }
  {
    TRACE_NO_INDENT();
    auto p = wid_cfg_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(g, p, "value");

    point tl(width / 2 + rhs_button_left, y_at);
    point br(width / 2 + rhs_button_right, y_at);
    wid_set_mode(g, w, WID_MODE_OVER);
    wid_set_style(w, box_highlight_style);
    wid_set_mode(g, w, WID_MODE_NORMAL);
    wid_set_style(w, box_style);
    wid_set_pos(w, tl, br);
    wid_set_text(w, ::to_string(game_key_quit_get(g)));
    wid_set_on_mouse_up(g, w, wid_cfg_key_quit);
  }
  ///////////////////////////////////////////////////////////////////////
  // console
  ///////////////////////////////////////////////////////////////////////
  y_at++;
  {
    TRACE_NO_INDENT();
    auto p = wid_cfg_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(g, p, "console");

    point tl(1, y_at);
    point br(width / 2, y_at);
    wid_set_shape_none(w);
    wid_set_pos(w, tl, br);
    wid_set_text_lhs(w, true);
    wid_set_text(w, "Debug console (+shift)");
  }
  {
    TRACE_NO_INDENT();
    auto p = wid_cfg_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(g, p, "console");

    point tl(width / 2 + rhs_button_left, y_at);
    point br(width / 2 + rhs_button_right, y_at);
    wid_set_mode(g, w, WID_MODE_OVER);
    wid_set_style(w, box_highlight_style);
    wid_set_mode(g, w, WID_MODE_NORMAL);
    wid_set_style(w, box_style);
    wid_set_pos(w, tl, br);
    wid_set_text(w, ::to_string(game_key_console_get(g)));
    wid_set_on_mouse_up(g, w, wid_cfg_key_console);
  }
  ///////////////////////////////////////////////////////////////////////
  // help
  ///////////////////////////////////////////////////////////////////////
  y_at++;
  {
    TRACE_NO_INDENT();
    auto p = wid_cfg_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(g, p, "help");

    point tl(1, y_at);
    point br(width / 2, y_at);
    wid_set_shape_none(w);
    wid_set_pos(w, tl, br);
    wid_set_text_lhs(w, true);
    wid_set_text(w, "This useless help");
  }
  {
    TRACE_NO_INDENT();
    auto p = wid_cfg_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(g, p, "value");

    point tl(width / 2 + rhs_button_left, y_at);
    point br(width / 2 + rhs_button_right, y_at);
    wid_set_mode(g, w, WID_MODE_OVER);
    wid_set_style(w, box_highlight_style);
    wid_set_mode(g, w, WID_MODE_NORMAL);
    wid_set_style(w, box_style);
    wid_set_pos(w, tl, br);
    wid_set_text(w, ::to_string(game_key_help_get(g)));
    wid_set_on_mouse_up(g, w, wid_cfg_key_help);
  }

  y_at++;
  ///////////////////////////////////////////////////////////////////////
  // unused1
  ///////////////////////////////////////////////////////////////////////
  y_at++;
  {
    TRACE_NO_INDENT();
    auto p = wid_cfg_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(g, p, "unused1");

    point tl(1, y_at);
    point br(width / 2, y_at);
    wid_set_shape_none(w);
    wid_set_pos(w, tl, br);
    wid_set_text_lhs(w, true);
    wid_set_text(w, "Unused1");
  }
  {
    TRACE_NO_INDENT();
    auto p = wid_cfg_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(g, p, "value");

    point tl(width / 2 + rhs_button_left, y_at);
    point br(width / 2 + rhs_button_right, y_at);
    wid_set_mode(g, w, WID_MODE_OVER);
    wid_set_style(w, box_highlight_style);
    wid_set_mode(g, w, WID_MODE_NORMAL);
    wid_set_style(w, box_style);
    wid_set_pos(w, tl, br);
    wid_set_text(w, ::to_string(game_key_unused1_get(g)));
    wid_set_on_mouse_up(g, w, wid_cfg_key_unused1);
  }

  wid_update(g, wid_cfg_keyboard_window->wid_text_area->wid_text_area);

  if (last_vert_scroll_offset != -1) {
    auto w = wid_cfg_keyboard_window->wid_text_area->wid_vert_scroll;
    wid_move_to_y_off(g, w, last_vert_scroll_offset);
  }

  game_state_change(g, STATE_KEYBOARD_MENU, "configure keys");
}
