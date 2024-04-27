//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_ascii.hpp"
#include "my_callstack.hpp"
#include "my_game.hpp"
#include "my_main.hpp"
#include "my_sdl_proto.hpp"
#include "my_wids.hpp"

static WidPopup *wid_credits_window;

static void wid_credits_destroy(void)
{
  TRACE_AND_INDENT();
  delete wid_credits_window;
  wid_credits_window = nullptr;
  wid_main_menu_select(game);
}

static bool wid_credits_key_up(Widp w, const struct SDL_Keysym *key)
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
              case SDLK_ESCAPE :
                {
                  TRACE_AND_INDENT();
                  wid_credits_destroy();
                  return true;
                }
            }
          }
      }
  }

  return true;
}

static bool wid_credits_key_down(Widp w, const struct SDL_Keysym *key)
{
  TRACE_AND_INDENT();

  if (sdlk_eq(*key, game_key_console_get(game))) {
    return false;
  }

  //
  // So screenshots can work
  //
  return false;
}

static bool wid_credits_mouse_up(Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  wid_credits_destroy();
  return true;
}

void wid_credits_select(class Game *game)
{
  TRACE_AND_INDENT();
  CON("INF: Credits");

  if (wid_credits_window) {
    wid_credits_destroy();
  }

  int   menu_height  = 18;
  int   menu_width   = UI_WID_POPUP_WIDTH_NORMAL * 2;
  point tl           = make_point(TERM_WIDTH / 2 - (menu_width / 2), TERM_HEIGHT / 2 - (menu_height / 2));
  point br           = make_point(TERM_WIDTH / 2 + (menu_width / 2), TERM_HEIGHT / 2 + (menu_height / 2));
  wid_credits_window = new WidPopup("Credits", tl, br, nullptr, "", false, false);

  wid_set_on_key_up(wid_credits_window->wid_popup_container, wid_credits_key_up);
  wid_set_on_key_down(wid_credits_window->wid_popup_container, wid_credits_key_down);

  wid_credits_window->log("%%fg=white$Development");
  wid_credits_window->log("goblinhack@gmail.com");
  wid_credits_window->log(UI_LOGGING_EMPTY_LINE);
  wid_credits_window->log("%%fg=white$Graphics");
  wid_credits_window->log("goblinhack@gmail.com");
  wid_credits_window->log(UI_LOGGING_EMPTY_LINE);
  wid_credits_window->log("%%fg=white$Music");
  wid_credits_window->log("Markus Heichelbech");
  wid_credits_window->log("C.E.McGill");
  wid_credits_window->log(UI_LOGGING_EMPTY_LINE);
  wid_credits_window->log("%%fg=white$Sounds");
  wid_credits_window->log("See README.md");

  {
    TRACE_AND_INDENT();
    auto p = wid_credits_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "credits");

    point tl = make_point(menu_width / 2 - 4, menu_height - 4);
    point br = make_point(menu_width / 2 + 3, menu_height - 2);

    wid_set_style(w, UI_WID_STYLE_NORMAL);
    wid_set_on_mouse_up(w, wid_credits_mouse_up);

    wid_set_pos(w, tl, br);
    wid_set_text(w, "BACK");
  }

  wid_update(wid_credits_window->wid_text_area->wid_text_area);
}
