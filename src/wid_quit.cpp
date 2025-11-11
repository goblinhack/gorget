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

static WidPopup *wid_quit_window;

void wid_quit_destroy(Gamep g)
{
  TRACE_NO_INDENT();

  if (wid_quit_window) {
    delete wid_quit_window;
    wid_quit_window = nullptr;
    game_state_reset(g, "wid quit destroy");
  }
}

static bool wid_quit_yes(Gamep g, Widp w, int x, int y, uint32_t button)
{
  TRACE_NO_INDENT();
  LOG("Quit, yes");

  if (game_levels_get(g)) {
    LOG("Continue game");

    game_destroy_levels(g);
    wid_quit_destroy(g);
    wid_main_menu_select(g);
  } else {
    LOG("Exit game");

    wid_quit_destroy(g);
    DIE_CLEAN("Quit");
  }
  return true;
}

static bool wid_quit_no(Gamep g, Widp w, int x, int y, uint32_t button)
{
  TRACE_NO_INDENT();
  LOG("Quit, no");

  wid_quit_destroy(g);

  if (! game_levels_get(g)) {
    wid_main_menu_select(g);
  }
  return true;
}

static bool wid_quit_key_down(Gamep g, Widp w, const struct SDL_Keysym *key)
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
              case 'y' :
              case 'Y' :
                sound_play(g, "keypress");
                wid_quit_yes(g, nullptr, 0, 0, 0);
                return true;
              case 'n' :
              case 'N' :
                sound_play(g, "keypress");
                wid_quit_no(g, nullptr, 0, 0, 0);
                return true;
              case 'b' :
              case 'B' :
              case SDLK_ESCAPE :
                sound_play(g, "keypress");
                wid_quit_no(g, nullptr, 0, 0, 0);
                return true;
            }
          }
      }
  }

  return false;
}

void wid_quit_select(Gamep g)
{
  TRACE_NO_INDENT();
  LOG("Quit select");

  if (wid_quit_window) {
    wid_quit_destroy(g);
  }

  auto m = TERM_WIDTH / 2;
  auto n = TERM_HEIGHT / 2;

  if (game_levels_get(g)) {
    n = TERM_HEIGHT / 3;
  }

  spoint outer_tl(m - UI_WID_POPUP_WIDTH_NORMAL / 2, n - 3);
  spoint outer_br(m + UI_WID_POPUP_WIDTH_NORMAL / 2, n + 3);
  auto   width = outer_br.x - outer_tl.x;

  wid_quit_window = new WidPopup(g, "Game quit", outer_tl, outer_br, nullptr, "", false, false);
  {
    TRACE_NO_INDENT();
    Widp w = wid_quit_window->wid_popup_container;
    wid_set_on_key_down(g, w, wid_quit_key_down);
  }

  int y_at = 0;
  {
    TRACE_NO_INDENT();
    auto p = wid_quit_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(g, p, "Quit");

    spoint tl(0, y_at);
    spoint br(width, y_at);
    wid_set_shape_none(w);
    wid_set_pos(w, tl, br);
    wid_set_text(w, "Quit game?");
  }

  y_at = 2;
  {
    TRACE_NO_INDENT();
    auto p = wid_quit_window->wid_text_area->wid_text_area;
    auto w = wid_new_red_button(g, p, "Yes");

    spoint tl(0, y_at);
    spoint br(width / 2 - 2, y_at + 2);
    wid_set_on_mouse_up(g, w, wid_quit_yes);
    wid_set_pos(w, tl, br);
    wid_set_text(w, UI_HIGHLIGHT_FMT_STR "Y" UI_RESET_FMT "es");
  }

  {
    TRACE_NO_INDENT();
    auto p = wid_quit_window->wid_text_area->wid_text_area;
    auto w = wid_new_green_button(g, p, "No");

    spoint tl(width / 2, y_at);
    spoint br(width - 2, y_at + 2);
    wid_set_on_mouse_up(g, w, wid_quit_no);
    wid_set_pos(w, tl, br);
    wid_set_text(w, UI_HIGHLIGHT_FMT_STR "N" UI_RESET_FMT "o");
  }

  wid_update(g, wid_quit_window->wid_text_area->wid_text_area);

  game_state_change(g, STATE_QUIT_MENU, "quit select");
}
