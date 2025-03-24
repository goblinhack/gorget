//
// Copyright goblinhack@gmail.com
//

#include "my_ascii.hpp"
#include "my_backtrace.hpp"
#include "my_callstack.hpp"
#include "my_game.hpp"
#include "my_main.hpp"
#include "my_sdl_proto.hpp"
#include "my_wids.hpp"

static WidPopup *wid_error_window;

static void wid_error_destroy(Gamep g)
{
  TRACE_AND_INDENT();
  delete wid_error_window;
  wid_error_window = nullptr;

  wid_main_menu_select(g);
  CON("It all went dark briefly. What happened?");
}

static bool wid_error_key_up(Gamep g, Widp w, const struct SDL_Keysym *key)
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
              case '\n' :
              case 'b' :
              case 'B' :
              case SDLK_ESCAPE :
                {
                  TRACE_AND_INDENT();
                  wid_error_destroy(g);
                  return true;
                }
            }
          }
      }
  }

  return true;
}

static bool wid_error_key_down(Gamep g, Widp w, const struct SDL_Keysym *key)
{
  TRACE_AND_INDENT();

  if (sdlk_eq(*key, game_key_console_get(g))) {
    return false;
  }

  return true;
}

void wid_error(Gamep g, std::string error)
{
  TRACE_AND_INDENT();
  CON("ERROR: %s", error.c_str());

  if (wid_error_window) {
    wid_error_destroy(g);
  }

  point tl(5, 5);
  point br(TERM_WIDTH - 5, TERM_HEIGHT - 5);

  wid_error_window = new WidPopup(g, "Game error", tl, br, nullptr, "");
  wid_set_on_key_up(g, wid_error_window->wid_popup_container, wid_error_key_up);
  wid_set_on_key_down(g, wid_error_window->wid_popup_container, wid_error_key_down);

  wid_set_do_not_lower(wid_error_window->wid_popup_container, true);

  wid_error_window->log(g, "ERROR: %%fg=red$" + error);
  wid_error_window->log(g, "Press ESCAPE to dismiss this window");
  wid_error_window->log(g, UI_LOGGING_EMPTY_LINE);
  wid_error_window->log(g, UI_LOGGING_EMPTY_LINE);
  wid_error_window->log(g, UI_LOGGING_EMPTY_LINE);
  wid_error_window->log(g, "Please send a screenshot to %%fg=white$goblinhack@gmail.com");
  wid_error_window->log(g, UI_LOGGING_EMPTY_LINE);
  sdl_screenshot_do(g);

  {
    TRACE_AND_INDENT();
    auto bt = new Backtrace();
    bt->init();
    auto s = bt->to_string();
    wid_error_window->log(g, s, TEXT_FORMAT_LHS);
  }

  wid_update(g, wid_error_window->wid_text_area->wid_text_area);
}
