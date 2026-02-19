//
// Copyright goblinhack@gmail.com
//

#include "my_ascii.hpp"
#include "my_callstack.hpp"
#include "my_game.hpp"
#include "my_globals.hpp"
#include "my_main.hpp"
#include "my_sdl_proto.hpp"
#include "my_sound.hpp"
#include "my_wid_warning.hpp"
#include "my_wids.hpp"

WidPopup *wid_warning_window;

static void wid_warning_destroy()
{
  TRACE_NO_INDENT();
  delete wid_warning_window;
  wid_warning_window = nullptr;
}

[[nodiscard]] static bool wid_warning_key_down(Gamep g, Widp w, const struct SDL_Keysym *key)
{
  DBG("Key press for wid warning");
  TRACE_AND_INDENT();

  if (sdlk_eq(*key, game_key_console_get(g))) {
    sound_play(g, "keypress");
    return false;
  }

  auto callback = (wid_warning_callback_t) wid_get_void_context(w);

  switch (key->mod) {
    case KMOD_LCTRL :
    case KMOD_RCTRL :
    default :
      switch (key->sym) {
        default :
          {
            auto c = wid_event_to_char(key);
            switch (c) {
              case 'y' :
              case 'Y' :
                DBG("Wid warning: yes");
                if (callback != nullptr) {
                  sound_play(g, "keypress");
                  (callback)(g, true);
                }
                wid_warning_destroy();
                break;
              case 'n' :
              case 'N' :
                DBG("Wid warning: no");
                if (callback != nullptr) {
                  sound_play(g, "keypress");
                  (callback)(g, false);
                }
                wid_warning_destroy();
                break;
              case '\n' :
              case 'b' :
              case 'B' :
              case SDLK_ESCAPE :
                {
                  if (callback != nullptr) {
                    DBG("Wid warning: default, no");
                    sound_play(g, "keypress");
                    (callback)(g, false);
                  }
                  wid_warning_destroy();
                  return true;
                }
            }
          }
      }
  }

  return true;
}

[[nodiscard]] static bool wid_warning_yes(Gamep g, Widp w, int x, int y, uint32_t button)
{
  DBG("Wid warning: yes");
  TRACE_AND_INDENT();

  auto callback = (wid_warning_callback_t) wid_get_void_context(w);
  if (callback != nullptr) {
    (callback)(g, true);
  }
  wid_warning_destroy();
  return true;
}

[[nodiscard]] static bool wid_warning_no(Gamep g, Widp w, int x, int y, uint32_t button)
{
  DBG("Wid warning: no");
  TRACE_AND_INDENT();

  auto callback = (wid_warning_callback_t) wid_get_void_context(w);
  if (callback != nullptr) {
    (callback)(g, false);
  }
  wid_warning_destroy();
  return true;
}

void wid_warning(Gamep g, const std::string &warning, wid_warning_callback_t callback)
{
  TRACE_NO_INDENT();

  if (wid_warning_window != nullptr) {
    wid_warning_destroy();
  }

  auto   m = TERM_WIDTH / 2;
  auto   n = TERM_HEIGHT / 2;
  spoint tl(m - (UI_WID_POPUP_WIDTH_WIDE / 2), n - 5);
  spoint br(m + (UI_WID_POPUP_WIDTH_WIDE / 2), n + 5);
  auto   width = br.x - tl.x;

  wid_warning_window = new WidPopup(g, "Game warning", tl, br, nullptr, "", false, false);
  wid_set_on_key_down(wid_warning_window->wid_popup_container, wid_warning_key_down);
  wid_set_do_not_lower(wid_warning_window->wid_popup_container);
  wid_set_void_context(wid_warning_window->wid_popup_container, (void *) callback);

  wid_warning_window->log_empty_line(g);
  wid_warning_window->log(g, warning);
  wid_warning_window->log_empty_line(g);

  auto y_at = 4;
  {
    TRACE_NO_INDENT();
    auto *p = wid_warning_window->wid_text_area->wid_text_area;
    auto *w = wid_new_red_button(g, p, "No");

    spoint tl1((width / 2) - 12, y_at + 2);
    spoint br1((width / 2) - 2, y_at + 4);
    wid_set_on_mouse_down(w, wid_warning_no);
    wid_set_void_context(w, (void *) callback);
    wid_set_pos(w, tl1, br1);
    wid_set_text(w, "No");
  }

  {
    TRACE_NO_INDENT();
    auto *p = wid_warning_window->wid_text_area->wid_text_area;
    auto *w = wid_new_green_button(g, p, "Yes");

    spoint tl2((width / 2) + 0, y_at + 2);
    spoint br2((width / 2) + 10, y_at + 4);
    wid_set_on_mouse_down(w, wid_warning_yes);
    wid_set_void_context(w, (void *) callback);
    wid_set_pos(w, tl2, br2);
    wid_set_text(w, "Yes");
  }
  wid_update(g, wid_warning_window->wid_text_area->wid_text_area);
}
