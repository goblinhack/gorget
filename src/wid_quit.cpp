//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_game.hpp"
#include "my_sdl_proto.hpp"
#include "my_ui.hpp"
#include "my_wid_popup.hpp"

WidPopup *wid_quit_window;

void wid_quit_destroy(void)
{
  TRACE_NO_INDENT();

  if (wid_quit_window) {
    delete wid_quit_window;
    wid_quit_window = nullptr;
    game->state_reset("wid quit destroy");
  }
}

static uint8_t wid_quit_yes(Widp w, int x, int y, uint32_t button)
{
  TRACE_NO_INDENT();
  LOG("INF: Quit, yes");

  if (game->level) {
    LOG("INF: Continue game");

    game->fini();
    wid_quit_destroy();
    game->wid_main_menu_select();
  } else {
    LOG("INF: Exit game");

    wid_quit_destroy();
    DIE_CLEAN("Quit");
  }
  return true;
}

static uint8_t wid_quit_no(Widp w, int x, int y, uint32_t button)
{
  TRACE_NO_INDENT();
  LOG("INF: Quit, no");

  wid_quit_destroy();

  if (! game->level) {
    game->wid_main_menu_select();
  }
  return true;
}

static uint8_t wid_quit_key_up(Widp w, const struct SDL_Keysym *key)
{
  TRACE_NO_INDENT();

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
            TRACE_NO_INDENT();
            auto c = wid_event_to_char(key);
            switch (c) {
              case 'y' :
              case 'Y' : wid_quit_yes(nullptr, 0, 0, 0); return true;
              case 'n' :
              case 'N' : wid_quit_no(nullptr, 0, 0, 0); return true;
              case 'b' :
              case 'B' :
              case SDLK_ESCAPE : wid_quit_no(nullptr, 0, 0, 0); return true;
            }
          }
      }
  }

  return false;
}

static uint8_t wid_quit_key_down(Widp w, const struct SDL_Keysym *key)
{
  TRACE_NO_INDENT();

  if (sdlk_eq(*key, game->config.key_console)) {
    return false;
  }

  return true;
}

void Game::wid_quit_select(void)
{
  TRACE_NO_INDENT();
  LOG("INF: Quit select");

  if (wid_quit_window) {
    wid_quit_destroy();
  }

  auto m = TERM_WIDTH / 2;
  auto n = TERM_HEIGHT / 2;

  if (game->level) {
    n = TERM_HEIGHT / 3;
  }

  point tl    = make_point(m - UI_WID_POPUP_WIDTH_NORMAL / 2, n - 3);
  point br    = make_point(m + UI_WID_POPUP_WIDTH_NORMAL / 2, n + 3);
  auto  width = br.x - tl.x;

  wid_quit_window = new WidPopup("Game quit", tl, br, nullptr, "", false, false);
  {
    TRACE_NO_INDENT();
    Widp w = wid_quit_window->wid_popup_container;
    wid_set_on_key_up(w, wid_quit_key_up);
    wid_set_on_key_down(w, wid_quit_key_down);
  }

  int y_at = 0;
  {
    TRACE_NO_INDENT();
    auto p = wid_quit_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "Quit");

    point tl = make_point(0, y_at);
    point br = make_point(width, y_at);
    wid_set_shape_none(w);
    wid_set_pos(w, tl, br);
    wid_set_text(w, "Quit game?");
  }

  y_at = 2;
  {
    TRACE_NO_INDENT();
    auto p = wid_quit_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "Yes");

    point tl = make_point(0, y_at);
    point br = make_point(width / 2 - 2, y_at + 2);
    wid_set_style(w, UI_WID_STYLE_RED);
    wid_set_on_mouse_up(w, wid_quit_yes);
    wid_set_pos(w, tl, br);
    wid_set_text(w, "%%fg=white$Y%%fg=reset$es");
  }

  {
    TRACE_NO_INDENT();
    auto p = wid_quit_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "No");

    point tl = make_point(width / 2, y_at);
    point br = make_point(width - 2, y_at + 2);
    wid_set_style(w, UI_WID_STYLE_GREEN);
    wid_set_on_mouse_up(w, wid_quit_no);
    wid_set_pos(w, tl, br);
    wid_set_text(w, "%%fg=white$N%%fg=reset$o");
  }

  wid_update(wid_quit_window->wid_text_area->wid_text_area);

  game->state_change(Game::STATE_QUIT_MENU, "quit select");
}
