//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_game.hpp"
#include "my_sdl_proto.hpp"
#include "my_ui.hpp"
#include "my_wid_popup.hpp"

WidPopup *wid_cfg_top_window;

static void wid_cfg_top_destroy(void)
{
  TRACE_AND_INDENT();
  delete wid_cfg_top_window;
  wid_cfg_top_window = nullptr;
}

static uint8_t wid_cfg_top_gfx(Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  wid_cfg_top_destroy();
  game->wid_cfg_gfx_select();
  return true;
}

static uint8_t wid_cfg_top_mouse(Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  wid_cfg_top_destroy();
  game->wid_cfg_mouse_select();
  return true;
}

static uint8_t wid_cfg_top_keyboard(Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  wid_cfg_top_destroy();
  game->wid_cfg_keyboard_select();
  return true;
}

static uint8_t wid_cfg_top_sound(Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  wid_cfg_top_destroy();
  game->wid_cfg_sound_select();
  return true;
}

static uint8_t wid_cfg_top_back(Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  wid_cfg_top_destroy();
  game->wid_main_menu_select();
  return true;
}

static uint8_t wid_cfg_top_key_up(Widp w, const struct SDL_Keysym *key)
{
  TRACE_AND_INDENT();
  if (sdlk_eq(*key, game->config.key_console)) {
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
              case 'g' : wid_cfg_top_gfx(nullptr, 0, 0, 0); return true;
              case 'm' : wid_cfg_top_mouse(nullptr, 0, 0, 0); return true;
              case 's' : wid_cfg_top_sound(nullptr, 0, 0, 0); return true;
              case 'k' : wid_cfg_top_keyboard(nullptr, 0, 0, 0); return true;
              case 'b' :
              case SDLK_ESCAPE : wid_cfg_top_back(nullptr, 0, 0, 0); return true;
            }
          }
      }
  }

  return false;
}

static uint8_t wid_cfg_top_key_down(Widp w, const struct SDL_Keysym *key)
{
  TRACE_AND_INDENT();

  if (sdlk_eq(*key, game->config.key_console)) {
    return false;
  }

  return true;
}

void Game::wid_cfg_top_menu(void)
{
  TRACE_AND_INDENT();
  CON("INF: Config menu");

  if (wid_cfg_top_window) {
    wid_cfg_top_destroy();
  }

  auto box_height          = 2;
  auto box_step            = 3;
  auto box_style           = UI_WID_STYLE_NORMAL;
  auto box_highlight_style = UI_WID_STYLE_NORMAL;

  int   menu_height  = 20;
  int   menu_width   = UI_WID_POPUP_WIDTH_NORMAL;
  point tl           = make_point(TERM_WIDTH / 2 - (menu_width / 2), TERM_HEIGHT / 2 - (menu_height / 2));
  point br           = make_point(TERM_WIDTH / 2 + (menu_width / 2), TERM_HEIGHT / 2 + (menu_height / 2));
  wid_cfg_top_window = new WidPopup("Config menu", tl, br, nullptr, "nothing", false, false);

  auto button_width = br.x - tl.x - 2;

  {
    TRACE_AND_INDENT();
    Widp w = wid_cfg_top_window->wid_popup_container;
    wid_set_on_key_up(w, wid_cfg_top_key_up);
    wid_set_on_key_down(w, wid_cfg_top_key_down);
  }

  int y_at = 0;
  {
    TRACE_AND_INDENT();
    auto p = wid_cfg_top_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "gfx");

    point tl = make_point(0, y_at);
    point br = make_point(button_width, y_at + box_height);
    wid_set_mode(w, WID_MODE_OVER);
    wid_set_style(w, box_highlight_style);
    wid_set_mode(w, WID_MODE_NORMAL);
    wid_set_style(w, box_style);
    wid_set_on_mouse_up(w, wid_cfg_top_gfx);
    wid_set_pos(w, tl, br);
    wid_set_text(w, "%%fg=white$G%%fg=reset$raphics");
  }
  y_at += box_step;
  {
    TRACE_AND_INDENT();
    auto p = wid_cfg_top_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "mouse");

    point tl = make_point(0, y_at);
    point br = make_point(button_width, y_at + box_height);
    wid_set_mode(w, WID_MODE_OVER);
    wid_set_style(w, box_highlight_style);
    wid_set_mode(w, WID_MODE_NORMAL);
    wid_set_style(w, box_style);
    wid_set_on_mouse_up(w, wid_cfg_top_mouse);
    wid_set_pos(w, tl, br);
    wid_set_text(w, "%%fg=white$M%%fg=reset$ouse");
  }
  y_at += box_step;
  {
    TRACE_AND_INDENT();
    auto p = wid_cfg_top_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "sound");

    point tl = make_point(0, y_at);
    point br = make_point(button_width, y_at + box_height);
    wid_set_mode(w, WID_MODE_OVER);
    wid_set_style(w, box_highlight_style);
    wid_set_mode(w, WID_MODE_NORMAL);
    wid_set_style(w, box_style);
    wid_set_on_mouse_up(w, wid_cfg_top_sound);
    wid_set_pos(w, tl, br);
    wid_set_text(w, "%%fg=white$S%%fg=reset$ound");
  }
  y_at += box_step;
  {
    TRACE_AND_INDENT();
    auto p = wid_cfg_top_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "keyboard");

    point tl = make_point(0, y_at);
    point br = make_point(button_width, y_at + box_height);
    wid_set_mode(w, WID_MODE_OVER);
    wid_set_style(w, box_highlight_style);
    wid_set_mode(w, WID_MODE_NORMAL);
    wid_set_style(w, box_style);
    wid_set_on_mouse_up(w, wid_cfg_top_keyboard);
    wid_set_pos(w, tl, br);
    wid_set_text(w, "%%fg=white$K%%fg=reset$eyboard");
  }
  y_at += box_step;
  {
    TRACE_AND_INDENT();
    auto p = wid_cfg_top_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "Back");

    point tl = make_point(0, y_at);
    point br = make_point(button_width, y_at + box_height);
    wid_set_mode(w, WID_MODE_OVER);
    wid_set_style(w, box_highlight_style);
    wid_set_mode(w, WID_MODE_NORMAL);
    wid_set_style(w, box_style);
    wid_set_on_mouse_up(w, wid_cfg_top_back);
    wid_set_pos(w, tl, br);
    wid_set_text(w, "%%fg=white$B%%fg=reset$ack");
  }

  wid_update(wid_cfg_top_window->wid_text_area->wid_text_area);
}
