//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_color_defs.hpp"
#include "my_game.hpp"
#include "my_sdl_event.hpp"
#include "my_sdl_proto.hpp"
#include "my_ui.hpp"
#include "my_wid_notice.hpp"
#include "my_wids.hpp"

static int  last_vert_scroll_offset = -1;
WidPopup   *wid_cfg_keyboard_window;
static bool config_changed;

static void wid_cfg_check_for_conflicts(SDL_Keysym code)
{
  TRACE_AND_INDENT();
  SDL_Keysym none = {};

  if (sdlk_eq(game_key_help_get(game), code)) {
    CON("%%fg=orange$Conflicting keyboard mapping, disabling key help.%%fg=reset$");
    game_key_help_set(game, none);
  }
  if (sdlk_eq(game_key_load_get(game), code)) {
    CON("%%fg=orange$Conflicting keyboard mapping, disabling key load.%%fg=reset$");
    game_key_load_set(game, none);
  }
  if (sdlk_eq(game_key_move_down_get(game), code)) {
    CON("%%fg=orange$Conflicting keyboard mapping, disabling key move down.%%fg=reset$");
    game_key_move_down_set(game, none);
  }
  if (sdlk_eq(game_key_move_left_get(game), code)) {
    CON("%%fg=orange$Conflicting keyboard mapping, disabling key move left.%%fg=reset$");
    game_key_move_left_set(game, none);
  }
  if (sdlk_eq(game_key_move_right_get(game), code)) {
    CON("%%fg=orange$Conflicting keyboard mapping, disabling key move right.%%fg=reset$");
    game_key_move_right_set(game, none);
  }
  if (sdlk_eq(game_key_move_up_get(game), code)) {
    CON("%%fg=orange$Conflicting keyboard mapping, disabling key move up.%%fg=reset$");
    game_key_move_up_set(game, none);
  }
  if (sdlk_eq(game_key_quit_get(game), code)) {
    CON("%%fg=orange$Conflicting keyboard mapping, disabling key quit.%%fg=reset$");
    game_key_quit_set(game, none);
  }
  if (sdlk_eq(game_key_save_get(game), code)) {
    CON("%%fg=orange$Conflicting keyboard mapping, disabling key save.%%fg=reset$");
    game_key_save_set(game, none);
  }
  if (sdlk_eq(game_key_screenshot_get(game), code)) {
    CON("%%fg=orange$Conflicting keyboard mapping, disabling key screenshot.%%fg=reset$");
    game_key_screenshot_set(game, none);
  }
  if (sdlk_eq(game_key_console_get(game), code)) {
    CON("%%fg=orange$Conflicting keyboard mapping, disabling key console%%fg=reset$");
    game_key_console_set(game, none);
  }
  if (sdlk_eq(game_key_unused1_get(game), code)) {
    CON("%%fg=orange$Conflicting keyboard mapping, disabling key unused1%%fg=reset$");
    game_key_unused1_set(game, none);
  }
}

void wid_cfg_keyboard_destroy(class Game *game)
{
  TRACE_AND_INDENT();
  config_changed = false;

  if (! wid_cfg_keyboard_window) {
    return;
  }

  auto w                  = wid_cfg_keyboard_window->wid_text_area->wid_vert_scroll;
  last_vert_scroll_offset = wid_get_tl_y(w) - wid_get_tl_y(w->parent);

  delete wid_cfg_keyboard_window;
  wid_cfg_keyboard_window = nullptr;
  game_state_reset(game, "wid keyboard destroy");
}

static bool wid_cfg_keyboard_cancel(Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  CON("INF: Reload config");
  if (config_changed) {
    config_changed = false;
    game_load_config(game);
    sdl_config_update_all();
  }
  wid_cfg_keyboard_destroy(game);

  if (game_level_get(game)) {
    //
    // Back to the game
    //
  } else {
    wid_cfg_top_menu(game);
  }

  sdl_config_update_all();
  return true;
}

static bool wid_cfg_keyboard_save(Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  CON("INF: Save config");
  game_save_config(game);
  wid_cfg_keyboard_destroy(game);

  if (game_level_get(game)) {
    //
    // Back to the game
    //
  } else {
    wid_cfg_top_menu(game);
  }

  return true;
}

static bool wid_cfg_keyboard_back(Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  wid_cfg_keyboard_destroy(game);

  if (game_level_get(game)) {
    //
    // Back to the game
    //
  } else {
    wid_cfg_top_menu(game);
  }

  return true;
}

static SDL_Keysym none = {};

static void wid_cfg_key_move_left_set(SDL_Keysym code)
{
  TRACE_AND_INDENT();
  config_changed = true;
  game_key_move_left_set(game, none);
  wid_cfg_check_for_conflicts(code);
  game_key_move_left_set(game, code);
  wid_cfg_keyboard_select(game);
}

static void wid_cfg_key_move_right_set(SDL_Keysym code)
{
  TRACE_AND_INDENT();
  config_changed = true;
  game_key_move_right_set(game, none);
  wid_cfg_check_for_conflicts(code);
  game_key_move_right_set(game, code);
  wid_cfg_keyboard_select(game);
}

static void wid_cfg_key_move_up_set(SDL_Keysym code)
{
  TRACE_AND_INDENT();
  config_changed = true;
  game_key_move_up_set(game, none);
  wid_cfg_check_for_conflicts(code);
  game_key_move_up_set(game, code);
  wid_cfg_keyboard_select(game);
}

static void wid_cfg_key_move_down_set(SDL_Keysym code)
{
  TRACE_AND_INDENT();
  config_changed = true;
  game_key_move_down_set(game, none);
  wid_cfg_check_for_conflicts(code);
  game_key_move_down_set(game, code);
  wid_cfg_keyboard_select(game);
}

static void wid_cfg_key_attack_set(SDL_Keysym code)
{
  TRACE_AND_INDENT();
  config_changed = true;
  game_key_attack_set(game, none);
  wid_cfg_check_for_conflicts(code);
  game_key_attack_set(game, code);
  wid_cfg_keyboard_select(game);
}

static void wid_cfg_key_unused1_set(SDL_Keysym code)
{
  TRACE_AND_INDENT();
  config_changed = true;
  game_key_unused1_set(game, none);
  wid_cfg_check_for_conflicts(code);
  game_key_unused1_set(game, code);
  wid_cfg_keyboard_select(game);
}

static void wid_cfg_key_save_set(SDL_Keysym code)
{
  TRACE_AND_INDENT();
  config_changed = true;
  game_key_save_set(game, none);
  wid_cfg_check_for_conflicts(code);
  game_key_save_set(game, code);
  wid_cfg_keyboard_select(game);
}

static void wid_cfg_key_load_set(SDL_Keysym code)
{
  TRACE_AND_INDENT();
  config_changed = true;
  game_key_load_set(game, none);
  wid_cfg_check_for_conflicts(code);
  game_key_load_set(game, code);
  wid_cfg_keyboard_select(game);
}

static void wid_cfg_key_help_set(SDL_Keysym code)
{
  TRACE_AND_INDENT();
  config_changed = true;
  game_key_help_set(game, none);
  wid_cfg_check_for_conflicts(code);
  game_key_help_set(game, code);
  wid_cfg_keyboard_select(game);
}

static void wid_cfg_key_console_set(SDL_Keysym code)
{
  TRACE_AND_INDENT();
  config_changed = true;
  game_key_console_set(game, none);
  wid_cfg_check_for_conflicts(code);
  game_key_console_set(game, code);
  wid_cfg_keyboard_select(game);
}

static void wid_cfg_key_quit_set(SDL_Keysym code)
{
  TRACE_AND_INDENT();
  config_changed = true;
  game_key_quit_set(game, none);
  wid_cfg_check_for_conflicts(code);
  game_key_quit_set(game, code);
  wid_cfg_keyboard_select(game);
}

static void wid_cfg_key_screenshot_set(SDL_Keysym code)
{
  TRACE_AND_INDENT();
  config_changed = true;
  game_key_screenshot_set(game, none);
  wid_cfg_check_for_conflicts(code);
  game_key_screenshot_set(game, code);
  wid_cfg_keyboard_select(game);
}

static void grab_key(const std::string which)
{
  TRACE_AND_INDENT();
  wid_notice("Press a key for " + which);
  g_grab_next_key = true;
  config_changed  = true;
}

static bool wid_cfg_keyboard_profile_arrow_keys(Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  SDL_Keysym none = {};
  SDL_Keysym k {};

  config_changed = true;
  game_key_move_up_set(game, none);
  k.sym = SDLK_UP;
  wid_cfg_check_for_conflicts(k);
  game_key_move_up_set(game, k);

  game_key_move_left_set(game, none);
  k.sym = SDLK_LEFT;
  wid_cfg_check_for_conflicts(k);
  game_key_move_left_set(game, k);

  game_key_move_down_set(game, none);
  k.sym = SDLK_DOWN;
  wid_cfg_check_for_conflicts(k);
  game_key_move_down_set(game, k);

  game_key_move_right_set(game, none);
  k.sym = SDLK_RIGHT;
  wid_cfg_check_for_conflicts(k);
  game_key_move_right_set(game, k);

  wid_cfg_keyboard_select(game);

  return true;
}

static bool wid_cfg_keyboard_profile_wasd(Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  SDL_Keysym k = {};

  config_changed = true;
  game_key_move_up_set(game, none);
  k.sym = SDLK_w;
  wid_cfg_check_for_conflicts(k);
  game_key_move_up_set(game, k);

  game_key_move_left_set(game, none);
  k.sym = SDLK_a;
  wid_cfg_check_for_conflicts(k);
  game_key_move_left_set(game, k);

  game_key_move_down_set(game, none);
  k.sym = SDLK_s;
  wid_cfg_check_for_conflicts(k);
  game_key_move_down_set(game, k);

  game_key_move_right_set(game, none);
  k.sym = SDLK_d;
  wid_cfg_check_for_conflicts(k);
  game_key_move_right_set(game, k);

  wid_cfg_keyboard_select(game);

  return true;
}

static bool wid_cfg_key_move_left(Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  grab_key("move left");
  sdl.on_sdl_key_grab = wid_cfg_key_move_left_set;
  config_changed      = true;
  return true;
}

static bool wid_cfg_key_move_right(Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  grab_key("move right");
  sdl.on_sdl_key_grab = wid_cfg_key_move_right_set;
  config_changed      = true;
  return true;
}

static bool wid_cfg_key_move_up(Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  grab_key("move up");
  sdl.on_sdl_key_grab = wid_cfg_key_move_up_set;
  config_changed      = true;
  return true;
}

static bool wid_cfg_key_move_down(Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  grab_key("move down");
  sdl.on_sdl_key_grab = wid_cfg_key_move_down_set;
  config_changed      = true;
  return true;
}

static bool wid_cfg_key_attack(Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  grab_key("attack");
  sdl.on_sdl_key_grab = wid_cfg_key_attack_set;
  config_changed      = true;
  return true;
}

static bool wid_cfg_key_unused1(Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  grab_key("item unused1");
  sdl.on_sdl_key_grab = wid_cfg_key_unused1_set;
  config_changed      = true;
  return true;
}

static bool wid_cfg_key_save(Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  grab_key("save game");
  sdl.on_sdl_key_grab = wid_cfg_key_save_set;
  config_changed      = true;
  return true;
}

static bool wid_cfg_key_load(Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  grab_key("load game");
  sdl.on_sdl_key_grab = wid_cfg_key_load_set;
  config_changed      = true;
  return true;
}

static bool wid_cfg_key_help(Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  grab_key("help");
  sdl.on_sdl_key_grab = wid_cfg_key_help_set;
  config_changed      = true;
  return true;
}

static bool wid_cfg_key_console(Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  grab_key("toggle console");
  sdl.on_sdl_key_grab = wid_cfg_key_console_set;
  config_changed      = true;
  return true;
}

static bool wid_cfg_key_quit(Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  grab_key("quit");
  sdl.on_sdl_key_grab = wid_cfg_key_quit_set;
  config_changed      = true;
  return true;
}

static bool wid_cfg_key_screenshot(Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  grab_key("screenshot grab");
  config_changed      = true;
  sdl.on_sdl_key_grab = wid_cfg_key_screenshot_set;
  return true;
}

static bool wid_cfg_keyboard_key_up(Widp w, const struct SDL_Keysym *key)
{
  TRACE_AND_INDENT();

  if (sdlk_eq(*key, game_key_console_get(game))) {
    return false;
  }

  switch (key->mod) {
    case KMOD_LCTRL :
    case KMOD_RCTRL :
    default :
      switch (key->sym) {
        default :
          {
            TRACE_AND_INDENT();
            auto c = wid_event_to_char(key);
            switch (c) {
              case 'b' :
              case 'B' :
              case SDLK_ESCAPE : wid_cfg_keyboard_cancel(nullptr, 0, 0, 0); return true;
            }
          }
      }
  }

  return false;
}

static bool wid_cfg_keyboard_key_down(Widp w, const struct SDL_Keysym *key)
{
  TRACE_AND_INDENT();

  if (sdlk_eq(*key, game_key_console_get(game))) {
    return false;
  }

  return true;
}

void wid_cfg_keyboard_select(class Game *game)
{
  TRACE_AND_INDENT();
  wid_notice_destroy();

  if (wid_cfg_keyboard_window) {
    wid_cfg_keyboard_destroy(game);
  }

  auto box_style           = UI_WID_STYLE_HORIZ_DARK;
  auto box_highlight_style = UI_WID_STYLE_HORIZ_LIGHT;
  auto m                   = TERM_WIDTH / 2;

  point tl    = make_point(m - TERM_WIDTH / 2, 2);
  point br    = make_point(m + TERM_WIDTH / 2 - 1, TERM_HEIGHT - 2);
  auto  width = br.x - tl.x;

  wid_cfg_keyboard_window = new WidPopup("Keyboard select", tl, br, nullptr, "", false, true);
  {
    TRACE_AND_INDENT();
    Widp w = wid_cfg_keyboard_window->wid_popup_container;
    wid_set_on_key_up(w, wid_cfg_keyboard_key_up);
    wid_set_on_key_down(w, wid_cfg_keyboard_key_down);
  }

  auto rhs_button_left  = 5;
  auto rhs_button_right = 20;

  int y_at = 0;
  {
    TRACE_AND_INDENT();
    auto p = wid_cfg_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "Keyboard");

    point tl = make_point(0, y_at);
    point br = make_point(width - 1, y_at);
    wid_set_shape_none(w);
    wid_set_pos(w, tl, br);
    wid_set_text(w, "Keyboard");
  }

  y_at = 2;
  {
    TRACE_AND_INDENT();
    auto p = wid_cfg_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "Back");

    point tl = make_point(1, y_at);
    point br = make_point(8, y_at + 2);
    wid_set_shape_square(w);
    wid_set_style(w, UI_WID_STYLE_NORMAL);
    wid_set_on_mouse_up(w, wid_cfg_keyboard_back);
    wid_set_pos(w, tl, br);
    wid_set_text(w, "Back");
  }
  {
    TRACE_AND_INDENT();
    auto p = wid_cfg_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "Save");

    point tl = make_point(width - 18, y_at);
    point br = make_point(width - 13, y_at + 2);
    wid_set_style(w, UI_WID_STYLE_GREEN);
    wid_set_on_mouse_up(w, wid_cfg_keyboard_save);
    wid_set_pos(w, tl, br);
    wid_set_text(w, "Save");
  }
  {
    TRACE_AND_INDENT();
    auto p = wid_cfg_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "Cancel");

    point tl = make_point(width - 11, y_at);
    point br = make_point(width - 4, y_at + 2);
    wid_set_style(w, UI_WID_STYLE_RED);
    wid_set_on_mouse_up(w, wid_cfg_keyboard_cancel);
    wid_set_pos(w, tl, br);
    wid_set_text(w, "Cancel");
  }

  ///////////////////////////////////////////////////////////////////////
  y_at++;
  ///////////////////////////////////////////////////////////////////////

  y_at += 3;
  {
    TRACE_AND_INDENT();
    auto p = wid_cfg_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "");

    point tl = make_point(1, y_at);
    point br = make_point(width - 4, y_at);
    wid_set_mode(w, WID_MODE_OVER);
    wid_set_style(w, box_highlight_style);
    wid_set_mode(w, WID_MODE_NORMAL);
    wid_set_style(w, box_style);
    wid_set_on_mouse_up(w, wid_cfg_keyboard_profile_wasd);
    wid_set_pos(w, tl, br);
    wid_set_text(w, "Use W,A,S,D for moving");
  }
  y_at++;
  {
    TRACE_AND_INDENT();
    auto p = wid_cfg_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "");

    point tl = make_point(1, y_at);
    point br = make_point(width - 4, y_at);
    wid_set_mode(w, WID_MODE_OVER);
    wid_set_style(w, box_highlight_style);
    wid_set_mode(w, WID_MODE_NORMAL);
    wid_set_style(w, box_style);
    wid_set_on_mouse_up(w, wid_cfg_keyboard_profile_arrow_keys);
    wid_set_pos(w, tl, br);
    wid_set_text(w, "Use arrow keys for moving");
  }

  y_at++;
  ///////////////////////////////////////////////////////////////////////
  // save
  ///////////////////////////////////////////////////////////////////////
  y_at++;
  {
    TRACE_AND_INDENT();
    auto p = wid_cfg_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "save");

    point tl = make_point(1, y_at);
    point br = make_point(width / 2, y_at);
    wid_set_shape_none(w);
    wid_set_pos(w, tl, br);
    wid_set_text_lhs(w, true);
    wid_set_text(w, "Save game");
  }
  {
    TRACE_AND_INDENT();
    auto p = wid_cfg_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "value");

    point tl = make_point(width / 2 + rhs_button_left, y_at);
    point br = make_point(width / 2 + rhs_button_right, y_at);
    wid_set_mode(w, WID_MODE_OVER);
    wid_set_style(w, box_highlight_style);
    wid_set_mode(w, WID_MODE_NORMAL);
    wid_set_style(w, box_style);
    wid_set_pos(w, tl, br);
    wid_set_text(w, ::to_string(game_key_save_get(game)));
    wid_set_on_mouse_up(w, wid_cfg_key_save);
  }
  ///////////////////////////////////////////////////////////////////////
  // load
  ///////////////////////////////////////////////////////////////////////
  y_at++;
  {
    TRACE_AND_INDENT();
    auto p = wid_cfg_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "load");

    point tl = make_point(1, y_at);
    point br = make_point(width / 2, y_at);
    wid_set_shape_none(w);
    wid_set_pos(w, tl, br);
    wid_set_text_lhs(w, true);
    wid_set_text(w, "Load game");
  }
  {
    TRACE_AND_INDENT();
    auto p = wid_cfg_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "value");

    point tl = make_point(width / 2 + rhs_button_left, y_at);
    point br = make_point(width / 2 + rhs_button_right, y_at);
    wid_set_mode(w, WID_MODE_OVER);
    wid_set_style(w, box_highlight_style);
    wid_set_mode(w, WID_MODE_NORMAL);
    wid_set_style(w, box_style);
    wid_set_pos(w, tl, br);
    wid_set_text(w, ::to_string(game_key_load_get(game)));
    wid_set_on_mouse_up(w, wid_cfg_key_load);
  }

  ///////////////////////////////////////////////////////////////////////
  // Move up
  ///////////////////////////////////////////////////////////////////////
  y_at += 2;
  {
    TRACE_AND_INDENT();
    auto p = wid_cfg_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "Move up");

    point tl = make_point(1, y_at);
    point br = make_point(width / 2, y_at);
    wid_set_shape_none(w);
    wid_set_pos(w, tl, br);
    wid_set_text_lhs(w, true);
    wid_set_mode(w, WID_MODE_OVER);
    wid_set_style(w, box_highlight_style);
    wid_set_mode(w, WID_MODE_NORMAL);
    wid_set_style(w, box_style);
    wid_set_text(w, "Move up");
  }
  {
    TRACE_AND_INDENT();
    auto p = wid_cfg_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "value");

    point tl = make_point(width / 2 + rhs_button_left, y_at);
    point br = make_point(width / 2 + rhs_button_right, y_at);
    wid_set_color(w, WID_COLOR_BG, WHITE);
    wid_set_color(w, WID_COLOR_TEXT_FG, WHITE);
    wid_set_mode(w, WID_MODE_OVER);
    wid_set_style(w, box_highlight_style);
    wid_set_mode(w, WID_MODE_NORMAL);
    wid_set_style(w, box_style);
    wid_set_pos(w, tl, br);
    wid_set_text(w, ::to_string(game_key_move_up_get(game)));
    wid_set_on_mouse_up(w, wid_cfg_key_move_up);
  }
  ///////////////////////////////////////////////////////////////////////
  // Move left
  ///////////////////////////////////////////////////////////////////////
  y_at++;
  {
    TRACE_AND_INDENT();
    auto p = wid_cfg_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "Move left");

    point tl = make_point(1, y_at);
    point br = make_point(width / 2, y_at);
    wid_set_shape_none(w);
    wid_set_pos(w, tl, br);
    wid_set_text_lhs(w, true);
    wid_set_text(w, "Move left");
  }
  {
    TRACE_AND_INDENT();
    auto p = wid_cfg_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "value");

    point tl = make_point(width / 2 + rhs_button_left, y_at);
    point br = make_point(width / 2 + rhs_button_right, y_at);
    wid_set_mode(w, WID_MODE_OVER);
    wid_set_style(w, box_highlight_style);
    wid_set_mode(w, WID_MODE_NORMAL);
    wid_set_style(w, box_style);
    wid_set_pos(w, tl, br);
    wid_set_text(w, ::to_string(game_key_move_left_get(game)));
    wid_set_on_mouse_up(w, wid_cfg_key_move_left);
  }
  ///////////////////////////////////////////////////////////////////////
  // Move down
  ///////////////////////////////////////////////////////////////////////
  y_at++;
  {
    TRACE_AND_INDENT();
    auto p = wid_cfg_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "Move down");

    point tl = make_point(1, y_at);
    point br = make_point(width / 2, y_at);
    wid_set_shape_none(w);
    wid_set_pos(w, tl, br);
    wid_set_text_lhs(w, true);
    wid_set_text(w, "Move down");
  }
  {
    TRACE_AND_INDENT();
    auto p = wid_cfg_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "value");

    point tl = make_point(width / 2 + rhs_button_left, y_at);
    point br = make_point(width / 2 + rhs_button_right, y_at);
    wid_set_mode(w, WID_MODE_OVER);
    wid_set_style(w, box_highlight_style);
    wid_set_mode(w, WID_MODE_NORMAL);
    wid_set_style(w, box_style);
    wid_set_pos(w, tl, br);
    wid_set_text(w, ::to_string(game_key_move_down_get(game)));
    wid_set_on_mouse_up(w, wid_cfg_key_move_down);
  }
  ///////////////////////////////////////////////////////////////////////
  // Move right
  ///////////////////////////////////////////////////////////////////////
  y_at++;
  {
    TRACE_AND_INDENT();
    auto p = wid_cfg_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "Move right");

    point tl = make_point(1, y_at);
    point br = make_point(width / 2, y_at);
    wid_set_shape_none(w);
    wid_set_pos(w, tl, br);
    wid_set_text_lhs(w, true);
    wid_set_text(w, "Move right");
  }
  {
    TRACE_AND_INDENT();
    auto p = wid_cfg_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "value");

    point tl = make_point(width / 2 + rhs_button_left, y_at);
    point br = make_point(width / 2 + rhs_button_right, y_at);
    wid_set_mode(w, WID_MODE_OVER);
    wid_set_style(w, box_highlight_style);
    wid_set_mode(w, WID_MODE_NORMAL);
    wid_set_style(w, box_style);
    wid_set_pos(w, tl, br);
    wid_set_text(w, ::to_string(game_key_move_right_get(game)));
    wid_set_on_mouse_up(w, wid_cfg_key_move_right);
  }

  ///////////////////////////////////////////////////////////////////////
  y_at++;
  ///////////////////////////////////////////////////////////////////////

  ///////////////////////////////////////////////////////////////////////
  // attack
  ///////////////////////////////////////////////////////////////////////
  y_at++;
  {
    TRACE_AND_INDENT();
    auto p = wid_cfg_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "Attack");

    point tl = make_point(1, y_at);
    point br = make_point(width / 2, y_at);
    wid_set_shape_none(w);
    wid_set_pos(w, tl, br);
    wid_set_text_lhs(w, true);
    wid_set_text(w, "Attack");
  }
  {
    TRACE_AND_INDENT();
    auto p = wid_cfg_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "value");

    point tl = make_point(width / 2 + rhs_button_left, y_at);
    point br = make_point(width / 2 + rhs_button_right, y_at);
    wid_set_mode(w, WID_MODE_OVER);
    wid_set_style(w, box_highlight_style);
    wid_set_mode(w, WID_MODE_NORMAL);
    wid_set_style(w, box_style);
    wid_set_pos(w, tl, br);
    wid_set_text(w, ::to_string(game_key_attack_get(game)));
    wid_set_on_mouse_up(w, wid_cfg_key_attack);
  }

  ///////////////////////////////////////////////////////////////////////
  y_at++;
  ///////////////////////////////////////////////////////////////////////

  ///////////////////////////////////////////////////////////////////////
  // screenshot
  ///////////////////////////////////////////////////////////////////////
  y_at++;
  {
    TRACE_AND_INDENT();
    auto p = wid_cfg_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "Take a screenshot");

    point tl = make_point(1, y_at);
    point br = make_point(width / 2, y_at);
    wid_set_shape_none(w);
    wid_set_pos(w, tl, br);
    wid_set_text_lhs(w, true);
    wid_set_text(w, "Take a screenshot");
  }
  {
    TRACE_AND_INDENT();
    auto p = wid_cfg_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "value");

    point tl = make_point(width / 2 + rhs_button_left, y_at);
    point br = make_point(width / 2 + rhs_button_right, y_at);
    wid_set_mode(w, WID_MODE_OVER);
    wid_set_style(w, box_highlight_style);
    wid_set_mode(w, WID_MODE_NORMAL);
    wid_set_style(w, box_style);
    wid_set_pos(w, tl, br);
    wid_set_text(w, ::to_string(game_key_screenshot_get(game)));
    wid_set_on_mouse_up(w, wid_cfg_key_screenshot);
  }

  ///////////////////////////////////////////////////////////////////////
  y_at++;
  ///////////////////////////////////////////////////////////////////////

  ///////////////////////////////////////////////////////////////////////
  // quit
  ///////////////////////////////////////////////////////////////////////
  y_at++;
  {
    TRACE_AND_INDENT();
    auto p = wid_cfg_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "quit");

    point tl = make_point(1, y_at);
    point br = make_point(width / 2, y_at);
    wid_set_shape_none(w);
    wid_set_pos(w, tl, br);
    wid_set_text_lhs(w, true);
    wid_set_text(w, "Quit");
  }
  {
    TRACE_AND_INDENT();
    auto p = wid_cfg_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "value");

    point tl = make_point(width / 2 + rhs_button_left, y_at);
    point br = make_point(width / 2 + rhs_button_right, y_at);
    wid_set_mode(w, WID_MODE_OVER);
    wid_set_style(w, box_highlight_style);
    wid_set_mode(w, WID_MODE_NORMAL);
    wid_set_style(w, box_style);
    wid_set_pos(w, tl, br);
    wid_set_text(w, ::to_string(game_key_quit_get(game)));
    wid_set_on_mouse_up(w, wid_cfg_key_quit);
  }
  ///////////////////////////////////////////////////////////////////////
  // console
  ///////////////////////////////////////////////////////////////////////
  y_at++;
  {
    TRACE_AND_INDENT();
    auto p = wid_cfg_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "console");

    point tl = make_point(1, y_at);
    point br = make_point(width / 2, y_at);
    wid_set_shape_none(w);
    wid_set_pos(w, tl, br);
    wid_set_text_lhs(w, true);
    wid_set_text(w, "Debug console (+shift)");
  }
  {
    TRACE_AND_INDENT();
    auto p = wid_cfg_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "console");

    point tl = make_point(width / 2 + rhs_button_left, y_at);
    point br = make_point(width / 2 + rhs_button_right, y_at);
    wid_set_mode(w, WID_MODE_OVER);
    wid_set_style(w, box_highlight_style);
    wid_set_mode(w, WID_MODE_NORMAL);
    wid_set_style(w, box_style);
    wid_set_pos(w, tl, br);
    wid_set_text(w, ::to_string(game_key_console_get(game)));
    wid_set_on_mouse_up(w, wid_cfg_key_console);
  }
  ///////////////////////////////////////////////////////////////////////
  // help
  ///////////////////////////////////////////////////////////////////////
  y_at++;
  {
    TRACE_AND_INDENT();
    auto p = wid_cfg_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "help");

    point tl = make_point(1, y_at);
    point br = make_point(width / 2, y_at);
    wid_set_shape_none(w);
    wid_set_pos(w, tl, br);
    wid_set_text_lhs(w, true);
    wid_set_text(w, "This useless help");
  }
  {
    TRACE_AND_INDENT();
    auto p = wid_cfg_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "value");

    point tl = make_point(width / 2 + rhs_button_left, y_at);
    point br = make_point(width / 2 + rhs_button_right, y_at);
    wid_set_mode(w, WID_MODE_OVER);
    wid_set_style(w, box_highlight_style);
    wid_set_mode(w, WID_MODE_NORMAL);
    wid_set_style(w, box_style);
    wid_set_pos(w, tl, br);
    wid_set_text(w, ::to_string(game_key_help_get(game)));
    wid_set_on_mouse_up(w, wid_cfg_key_help);
  }

  y_at++;
  ///////////////////////////////////////////////////////////////////////
  // unused1
  ///////////////////////////////////////////////////////////////////////
  y_at++;
  {
    TRACE_AND_INDENT();
    auto p = wid_cfg_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "unused1");

    point tl = make_point(1, y_at);
    point br = make_point(width / 2, y_at);
    wid_set_shape_none(w);
    wid_set_pos(w, tl, br);
    wid_set_text_lhs(w, true);
    wid_set_text(w, "Unused1");
  }
  {
    TRACE_AND_INDENT();
    auto p = wid_cfg_keyboard_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "value");

    point tl = make_point(width / 2 + rhs_button_left, y_at);
    point br = make_point(width / 2 + rhs_button_right, y_at);
    wid_set_mode(w, WID_MODE_OVER);
    wid_set_style(w, box_highlight_style);
    wid_set_mode(w, WID_MODE_NORMAL);
    wid_set_style(w, box_style);
    wid_set_pos(w, tl, br);
    wid_set_text(w, ::to_string(game_key_unused1_get(game)));
    wid_set_on_mouse_up(w, wid_cfg_key_unused1);
  }

  wid_update(wid_cfg_keyboard_window->wid_text_area->wid_text_area);

  if (last_vert_scroll_offset != -1) {
    auto w = wid_cfg_keyboard_window->wid_text_area->wid_vert_scroll;
    wid_move_to_y_off(w, last_vert_scroll_offset);
  }

  game_state_change(game, STATE_KEYBOARD_MENU, "configure keys");
}
