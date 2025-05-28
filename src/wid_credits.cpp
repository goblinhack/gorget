//
// Copyright goblinhack@gmail.com
//

#include "my_ascii.hpp"
#include "my_callstack.hpp"
#include "my_game.hpp"
#include "my_main.hpp"
#include "my_sdl_proto.hpp"
#include "my_wids.hpp"

static WidPopup *wid_credits_window;

static void wid_credits_destroy(Gamep g)
{
  TRACE_AND_INDENT();
  delete wid_credits_window;
  wid_credits_window = nullptr;
  wid_main_menu_select(g);
}

static bool wid_credits_key_up(Gamep g, Widp w, const struct SDL_Keysym *key)
{
  TRACE_AND_INDENT();

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
            TRACE_AND_INDENT();
            auto c = wid_event_to_char(key);
            switch (c) {
              case 'b' :
              case 'B' :
              case SDLK_ESCAPE :
                {
                  TRACE_AND_INDENT();
                  wid_credits_destroy(g);
                  return true;
                }
            }
          }
      }
  }

  return true;
}

static bool wid_credits_key_down(Gamep g, Widp w, const struct SDL_Keysym *key)
{
  TRACE_AND_INDENT();

  if (sdlk_eq(*key, game_key_console_get(g))) {
    return false;
  }

  //
  // So screenshots can work
  //
  return false;
}

static bool wid_credits_mouse_up(Gamep g, Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  wid_credits_destroy(g);
  return true;
}

void wid_credits_select(Gamep g)
{
  TRACE_AND_INDENT();
  CON("Credits");

  if (wid_credits_window) {
    wid_credits_destroy(g);
  }

  int   menu_height = 18;
  int   menu_width  = UI_WID_POPUP_WIDTH_NORMAL * 2;
  point outer_tl(TERM_WIDTH / 2 - (menu_width / 2), TERM_HEIGHT / 2 - (menu_height / 2));
  point outer_br(TERM_WIDTH / 2 + (menu_width / 2), TERM_HEIGHT / 2 + (menu_height / 2));
  wid_credits_window = new WidPopup(g, "Credits", outer_tl, outer_br, nullptr, "", false, false);

  wid_set_on_key_up(g, wid_credits_window->wid_popup_container, wid_credits_key_up);
  wid_set_on_key_down(g, wid_credits_window->wid_popup_container, wid_credits_key_down);

  wid_credits_window->log(g, "" UI_HIGHLIGHT_FMT_STR "Development");
  wid_credits_window->log(g, "goblinhack@gmail.com");
  wid_credits_window->log_empty_line(g);
  wid_credits_window->log(g, "" UI_HIGHLIGHT_FMT_STR "Graphics");
  wid_credits_window->log(g, "Urizen 1 bit tileset");
  wid_credits_window->log(g, "goblinhack@gmail.com");
  wid_credits_window->log_empty_line(g);
  wid_credits_window->log(g, "" UI_HIGHLIGHT_FMT_STR "Music");
  wid_credits_window->log(g, "Markus Heichelbech");
  wid_credits_window->log(g, "C.E.McGill");
  wid_credits_window->log_empty_line(g);
  wid_credits_window->log(g, "" UI_HIGHLIGHT_FMT_STR "Sounds");
  wid_credits_window->log(g, "See README.md");

  {
    TRACE_AND_INDENT();
    auto p = wid_credits_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(g, p, "credits");

    point tl(menu_width / 2 - 4, menu_height - 4);
    point br(menu_width / 2 + 3, menu_height - 2);

    wid_set_style(w, UI_WID_STYLE_NORMAL);
    wid_set_on_mouse_up(g, w, wid_credits_mouse_up);

    wid_set_pos(w, tl, br);
    wid_set_text(w, "BACK");
  }

  wid_update(g, wid_credits_window->wid_text_area->wid_text_area);
}
