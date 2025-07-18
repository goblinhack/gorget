//
// Copyright goblinhack@gmail.com
//

#include "my_ascii.hpp"
#include "my_callstack.hpp"
#include "my_game.hpp"
#include "my_main.hpp"
#include "my_sdl_proto.hpp"
#include "my_wids.hpp"

WidPopup *wid_cfg_window;

static void wid_cfg_destroy(Gamep g)
{
  TRACE_NO_INDENT();
  delete wid_cfg_window;
  wid_cfg_window = nullptr;
}

static bool wid_cfg_gfx(Gamep g, Widp w, int x, int y, uint32_t button)
{
  TRACE_NO_INDENT();
  wid_cfg_destroy(g);
  wid_cfg_gfx_select(g);
  return true;
}

static bool wid_cfg_seed(Gamep g, Widp w, int x, int y, uint32_t button)
{
  TRACE_NO_INDENT();
  wid_cfg_destroy(g);
  wid_seed_select(g);
  return false;
}

static bool wid_cfg_player_name(Gamep g, Widp w, int x, int y, uint32_t button)
{
  TRACE_NO_INDENT();
  wid_cfg_destroy(g);
  wid_player_name_select(g);
  return false;
}

static bool wid_cfg_mouse(Gamep g, Widp w, int x, int y, uint32_t button)
{
  TRACE_NO_INDENT();
  wid_cfg_destroy(g);
  wid_cfg_mouse_select(g);
  return true;
}

static bool wid_cfg_keyboard(Gamep g, Widp w, int x, int y, uint32_t button)
{
  TRACE_NO_INDENT();
  wid_cfg_destroy(g);
  wid_cfg_keyboard_select(g);
  return true;
}

static bool wid_cfg_sound(Gamep g, Widp w, int x, int y, uint32_t button)
{
  TRACE_NO_INDENT();
  wid_cfg_destroy(g);
  wid_cfg_sound_select(g);
  return true;
}

static bool wid_cfg_back(Gamep g, Widp w, int x, int y, uint32_t button)
{
  TRACE_NO_INDENT();
  wid_cfg_destroy(g);
  wid_main_menu_select(g);
  return true;
}

static bool wid_cfg_key_down(Gamep g, Widp w, const struct SDL_Keysym *key)
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
              case 'g' :
              case 'G' :         wid_cfg_gfx(g, nullptr, 0, 0, 0); return true;
              case 'm' :
              case 'M' :         wid_cfg_mouse(g, nullptr, 0, 0, 0); return true;
              case 's' :
              case 'S' :         wid_cfg_sound(g, nullptr, 0, 0, 0); return true;
              case 'k' :
              case 'K' :         wid_cfg_keyboard(g, nullptr, 0, 0, 0); return true;
              case 'c' :
              case 'C' :         wid_cfg_seed(g, nullptr, 0, 0, 0); return true;
              case 'p' :
              case 'P' :         wid_cfg_player_name(g, nullptr, 0, 0, 0); return true;
              case 'b' :
              case 'B' :
              case SDLK_ESCAPE : wid_cfg_back(g, nullptr, 0, 0, 0); return true;
            }
          }
      }
  }

  return false;
}

void wid_cfg_select(Gamep g)
{
  TRACE_NO_INDENT();
  CON("Config menu");

  if (wid_cfg_window) {
    wid_cfg_destroy(g);
  }

  auto box_height          = 2;
  auto box_step            = 3;
  auto box_style           = UI_WID_STYLE_NORMAL;
  auto box_highlight_style = UI_WID_STYLE_NORMAL;

  int    menu_height = 26;
  int    menu_width  = UI_WID_POPUP_WIDTH_NORMAL;
  spoint outer_tl(TERM_WIDTH / 2 - (menu_width / 2), TERM_HEIGHT / 2 - (menu_height / 2));
  spoint outer_br(TERM_WIDTH / 2 + (menu_width / 2), TERM_HEIGHT / 2 + (menu_height / 2));
  wid_cfg_window = new WidPopup(g, "Config menu", outer_tl, outer_br, nullptr, "nothing", false, false);

  auto button_width = outer_br.x - outer_tl.x - 2;

  {
    TRACE_NO_INDENT();
    Widp w = wid_cfg_window->wid_popup_container;
    wid_set_on_key_down(g, w, wid_cfg_key_down);
  }

  int y_at = 0;
  {
    TRACE_NO_INDENT();
    auto p = wid_cfg_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(g, p, "Choose seed");

    spoint tl(0, y_at);
    spoint br(button_width, y_at + box_height);
    wid_set_mode(g, w, WID_MODE_OVER);
    wid_set_style(w, box_highlight_style);
    wid_set_mode(g, w, WID_MODE_NORMAL);
    wid_set_style(w, box_style);
    wid_set_on_mouse_up(g, w, wid_cfg_seed);
    wid_set_pos(w, tl, br);
    wid_set_text(w, UI_HIGHLIGHT_FMT_STR "C" UI_FMT_STR "hange seed");
  }
  y_at += box_step;
  {
    TRACE_NO_INDENT();
    auto p = wid_cfg_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(g, p, "Choose player name");

    spoint tl(0, y_at);
    spoint br(button_width, y_at + box_height);
    wid_set_mode(g, w, WID_MODE_OVER);
    wid_set_style(w, box_highlight_style);
    wid_set_mode(g, w, WID_MODE_NORMAL);
    wid_set_style(w, box_style);
    wid_set_on_mouse_up(g, w, wid_cfg_player_name);
    wid_set_pos(w, tl, br);
    wid_set_text(w, UI_HIGHLIGHT_FMT_STR "P" UI_FMT_STR "layer name");
  }
  y_at += box_step;
  {
    TRACE_NO_INDENT();
    auto p = wid_cfg_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(g, p, "gfx");

    spoint tl(0, y_at);
    spoint br(button_width, y_at + box_height);
    wid_set_mode(g, w, WID_MODE_OVER);
    wid_set_style(w, box_highlight_style);
    wid_set_mode(g, w, WID_MODE_NORMAL);
    wid_set_style(w, box_style);
    wid_set_on_mouse_up(g, w, wid_cfg_gfx);
    wid_set_pos(w, tl, br);
    wid_set_text(w, UI_HIGHLIGHT_FMT_STR "G" UI_RESET_FMT "raphics");
  }
  y_at += box_step;
  {
    TRACE_NO_INDENT();
    auto p = wid_cfg_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(g, p, "mouse");

    spoint tl(0, y_at);
    spoint br(button_width, y_at + box_height);
    wid_set_mode(g, w, WID_MODE_OVER);
    wid_set_style(w, box_highlight_style);
    wid_set_mode(g, w, WID_MODE_NORMAL);
    wid_set_style(w, box_style);
    wid_set_on_mouse_up(g, w, wid_cfg_mouse);
    wid_set_pos(w, tl, br);
    wid_set_text(w, UI_HIGHLIGHT_FMT_STR "M" UI_RESET_FMT "ouse");
  }
  y_at += box_step;
  {
    TRACE_NO_INDENT();
    auto p = wid_cfg_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(g, p, "sound");

    spoint tl(0, y_at);
    spoint br(button_width, y_at + box_height);
    wid_set_mode(g, w, WID_MODE_OVER);
    wid_set_style(w, box_highlight_style);
    wid_set_mode(g, w, WID_MODE_NORMAL);
    wid_set_style(w, box_style);
    wid_set_on_mouse_up(g, w, wid_cfg_sound);
    wid_set_pos(w, tl, br);
    wid_set_text(w, UI_HIGHLIGHT_FMT_STR "S" UI_RESET_FMT "ound");
  }
  y_at += box_step;
  {
    TRACE_NO_INDENT();
    auto p = wid_cfg_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(g, p, "keyboard");

    spoint tl(0, y_at);
    spoint br(button_width, y_at + box_height);
    wid_set_mode(g, w, WID_MODE_OVER);
    wid_set_style(w, box_highlight_style);
    wid_set_mode(g, w, WID_MODE_NORMAL);
    wid_set_style(w, box_style);
    wid_set_on_mouse_up(g, w, wid_cfg_keyboard);
    wid_set_pos(w, tl, br);
    wid_set_text(w, UI_HIGHLIGHT_FMT_STR "K" UI_RESET_FMT "eyboard");
  }
  y_at += box_step;
  {
    TRACE_NO_INDENT();
    auto p = wid_cfg_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(g, p, "Back");

    spoint tl(0, y_at);
    spoint br(button_width, y_at + box_height);
    wid_set_mode(g, w, WID_MODE_OVER);
    wid_set_style(w, box_highlight_style);
    wid_set_mode(g, w, WID_MODE_NORMAL);
    wid_set_style(w, box_style);
    wid_set_on_mouse_up(g, w, wid_cfg_back);
    wid_set_pos(w, tl, br);
    wid_set_text(w, UI_HIGHLIGHT_FMT_STR "B" UI_RESET_FMT "ack");
  }

  wid_update(g, wid_cfg_window->wid_text_area->wid_text_area);

  game_state_change(g, STATE_MAIN_MENU, "main menu");
}
