//
// Copyright goblinhack@gmail.com
//

#include "my_ascii.hpp"
#include "my_callstack.hpp"
#include "my_game.hpp"
#include "my_sdl_proto.hpp"
#include "my_wid_popup.hpp"

static WidPopup *wid_notice_window;

void wid_notice_destroy(void)
{
  TRACE_AND_INDENT();
  delete wid_notice_window;
  wid_notice_window = nullptr;
}

static bool wid_notice_ok(Gamep g, Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  wid_notice_destroy();
  return false;
}

static bool wid_notice_key_up(Gamep g, Widp w, const struct SDL_Keysym *key)
{
  TRACE_AND_INDENT();
  wid_notice_ok(g, nullptr, 0, 0, 0);
  return true;
}

static bool wid_notice_key_down(Gamep g, Widp w, const struct SDL_Keysym *key)
{
  TRACE_AND_INDENT();

  if (sdlk_eq(*key, game_key_console_get(g))) {
    return false;
  }

  return true;
}

void wid_notice(std::string s)
{
  TRACE_AND_INDENT();

  extern Gamep game;
  auto         g = game;

  if (wid_notice_window) {
    wid_notice_destroy();
  }

  auto   m = TERM_WIDTH / 2;
  auto   n = TERM_HEIGHT / 2;
  spoint tl(0, 0);
  spoint br(s.size() + 3, 8);
  spoint offset(m, n);
  offset.x -= s.size() / 2;
  tl += offset;
  br += offset;

  auto width = br.x - tl.x;

  wid_notice_window = new WidPopup(g, "Game notice", tl, br, nullptr, "", false, false);
  {
    TRACE_AND_INDENT();
    Widp w = wid_notice_window->wid_popup_container;
    wid_set_on_key_up(g, w, wid_notice_key_up);
    wid_set_on_key_down(g, w, wid_notice_key_down);
  }

  int y_at = 0;
  {
    TRACE_AND_INDENT();
    auto p = wid_notice_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(g, p, "notice");

    spoint tl1(0, y_at);
    spoint br1(width - 1, y_at + 1);
    wid_set_shape_none(w);
    wid_set_on_mouse_up(g, w, wid_notice_ok);
    wid_set_pos(w, tl1, br1);
    wid_set_text(w, s);
    wid_set_style(w, UI_WID_STYLE_GREEN);
  }

  y_at = 3;
  {
    TRACE_AND_INDENT();
    auto p = wid_notice_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(g, p, "ok");

    spoint tl2(width / 2 - 4, y_at);
    spoint br2(width / 2 + 4, y_at + 2);
    wid_set_style(w, UI_WID_STYLE_GREEN);
    wid_set_on_mouse_up(g, w, wid_notice_ok);
    wid_set_pos(w, tl2, br2);
    wid_set_text(w, "Ok!");
  }

  wid_update(g, wid_notice_window->wid_text_area->wid_text_area);
}
