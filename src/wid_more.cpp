//
// Copyright goblinhack@gmail.com
//

#include "my_ascii.hpp"
#include "my_callstack.hpp"
#include "my_game.hpp"
#include "my_main.hpp"
#include "my_sdl_proto.hpp"
#include "my_sound.hpp"
#include "my_wids.hpp"

static WidPopup *wid_more_window;

static void wid_more_destroy(Gamep g)
{
  TRACE_NO_INDENT();
  delete wid_more_window;
  wid_more_window = nullptr;
}

static bool wid_more_credits(Gamep g, Widp w, int x, int y, uint32_t button)
{
  TRACE_NO_INDENT();
  wid_more_destroy(g);
  wid_credits_select(g);
  return true;
}

static bool wid_more_hiscores(Gamep g, Widp w, int x, int y, uint32_t button)
{
  TRACE_NO_INDENT();
  wid_more_destroy(g);
  wid_hiscores_show(g);
  return true;
}

static bool wid_more_back(Gamep g, Widp w, int x, int y, uint32_t button)
{
  TRACE_NO_INDENT();
  wid_more_destroy(g);
  wid_main_menu_select(g);
  return true;
}

static bool wid_more_key_down(Gamep g, Widp w, const struct SDL_Keysym *key)
{
  TRACE_NO_INDENT();

  if (sdlk_eq(*key, game_key_console_get(g))) {
    sound_play(g, "keypress");
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
              case 'c' :
              case 'C' :
                sound_play(g, "keypress");
                wid_more_credits(g, nullptr, 0, 0, 0);
                return true;
              case 'h' :
              case 'H' :
                sound_play(g, "keypress");
                wid_more_hiscores(g, nullptr, 0, 0, 0);
                return true;
              case 'b' :
              case 'B' :
              case SDLK_ESCAPE :
                sound_play(g, "keypress");
                wid_more_back(g, nullptr, 0, 0, 0);
                return true;
            }
          }
      }
  }

  return false;
}

void wid_more_select(Gamep g)
{
  TRACE_NO_INDENT();
  CON("Config menu");

  if (wid_more_window) {
    wid_more_destroy(g);
  }

  auto box_height          = 2;
  auto box_step            = 3;
  auto box_style           = UI_WID_STYLE_NORMAL;
  auto box_highlight_style = UI_WID_STYLE_NORMAL;

  int    menu_height = 14;
  int    menu_width  = UI_WID_POPUP_WIDTH_NORMAL;
  spoint outer_tl(TERM_WIDTH / 2 - (menu_width / 2), TERM_HEIGHT / 2 - (menu_height / 2));
  spoint outer_br(TERM_WIDTH / 2 + (menu_width / 2), TERM_HEIGHT / 2 + (menu_height / 2));
  wid_more_window = new WidPopup(g, "Config menu", outer_tl, outer_br, nullptr, "nothing", false, false);

  auto button_width = outer_br.x - outer_tl.x - 2;

  {
    TRACE_NO_INDENT();
    Widp w = wid_more_window->wid_popup_container;
    wid_set_on_key_down(g, w, wid_more_key_down);
  }

  int y_at = 0;

  y_at += box_step;
  {
    TRACE_NO_INDENT();
    auto p = wid_more_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(g, p, "Credits");

    spoint tl(0, y_at);
    spoint br(button_width, y_at + box_height);
    wid_set_mode(g, w, WID_MODE_OVER);
    wid_set_style(w, box_highlight_style);
    wid_set_mode(g, w, WID_MODE_NORMAL);
    wid_set_style(w, box_style);
    wid_set_on_mouse_up(g, w, wid_more_credits);
    wid_set_pos(w, tl, br);
    wid_set_text(w, UI_HIGHLIGHT_FMT_STR "C" UI_FMT_STR "redits");
  }
  y_at += box_step;
  {
    TRACE_NO_INDENT();
    auto p = wid_more_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(g, p, "Hiscores");

    spoint tl(0, y_at);
    spoint br(button_width, y_at + box_height);
    wid_set_mode(g, w, WID_MODE_OVER);
    wid_set_style(w, box_highlight_style);
    wid_set_mode(g, w, WID_MODE_NORMAL);
    wid_set_style(w, box_style);
    wid_set_on_mouse_up(g, w, wid_more_hiscores);
    wid_set_pos(w, tl, br);
    wid_set_text(w, UI_HIGHLIGHT_FMT_STR "H" UI_FMT_STR "iscores");
  }
  y_at += box_step;
  {
    TRACE_NO_INDENT();
    auto p = wid_more_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(g, p, "Back");

    spoint tl(0, y_at);
    spoint br(button_width, y_at + box_height);
    wid_set_mode(g, w, WID_MODE_OVER);
    wid_set_style(w, box_highlight_style);
    wid_set_mode(g, w, WID_MODE_NORMAL);
    wid_set_style(w, box_style);
    wid_set_on_mouse_up(g, w, wid_more_back);
    wid_set_pos(w, tl, br);
    wid_set_text(w, UI_HIGHLIGHT_FMT_STR "B" UI_RESET_FMT "ack");
  }

  wid_update(g, wid_more_window->wid_text_area->wid_text_area);

  game_state_change(g, STATE_MAIN_MENU, "main menu");
}
