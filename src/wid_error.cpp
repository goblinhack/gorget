//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_ascii.hpp"
#include "my_backtrace.hpp"
#include "my_callstack.hpp"
#include "my_game.hpp"
#include "my_main.hpp"
#include "my_sdl_proto.hpp"
#include "my_wids.hpp"

static WidPopup *wid_error_window;

static void wid_error_destroy(void)
{
  TRACE_AND_INDENT();
  delete wid_error_window;
  wid_error_window = nullptr;

  wid_main_menu_select(game);
  CON("It all went dark briefly. What happened?");
}

static bool wid_error_key_up(Widp w, const struct SDL_Keysym *key)
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
              case '\n' :
              case 'b' :
              case 'B' :
              case SDLK_ESCAPE :
                {
                  TRACE_AND_INDENT();
                  wid_error_destroy();
                  return true;
                }
            }
          }
      }
  }

  return true;
}

static bool wid_error_key_down(Widp w, const struct SDL_Keysym *key)
{
  TRACE_AND_INDENT();

  if (sdlk_eq(*key, game_key_console_get(game))) {
    return false;
  }

  return true;
}

void wid_error(std::string error)
{
  TRACE_AND_INDENT();
  CON("ERROR: %s", error.c_str());

  if (wid_error_window) {
    wid_error_destroy();
  }

  point tl(5, 5);
  point br(TERM_WIDTH - 5, TERM_HEIGHT - 5);

  wid_error_window = new WidPopup("Game error", tl, br, nullptr, "");
  wid_set_on_key_up(wid_error_window->wid_popup_container, wid_error_key_up);
  wid_set_on_key_down(wid_error_window->wid_popup_container, wid_error_key_down);

  wid_set_do_not_lower(wid_error_window->wid_popup_container, true);

  wid_error_window->log("ERROR: %%fg=red$" + error);
  wid_error_window->log("Press ESCAPE to dismiss this window");
  wid_error_window->log(UI_LOGGING_EMPTY_LINE);
  wid_error_window->log(UI_LOGGING_EMPTY_LINE);
  wid_error_window->log(UI_LOGGING_EMPTY_LINE);
  wid_error_window->log("Please send a screenshot to %%fg=white$goblinhack@gmail.com");
  wid_error_window->log(UI_LOGGING_EMPTY_LINE);
  sdl_screenshot_do();

  {
    TRACE_AND_INDENT();
    auto bt = new Backtrace();
    bt->init();
    auto s = bt->to_string();
    wid_error_window->log(s, TEXT_FORMAT_LHS);
  }

  wid_update(wid_error_window->wid_text_area->wid_text_area);
}
