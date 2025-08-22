//
// Copyright goblinhack@gmail.com
//

#include "my_ascii.hpp"
#include "my_callstack.hpp"
#include "my_main.hpp"
#include "my_ptrcheck.hpp"
#include "my_sdl_proto.hpp"
#include "my_wid_popup.hpp"

static int progress_steps = 32;

WidPopup *wid_progress_bar_window;

void wid_progress_bar_destroy(Gamep g)
{
  TRACE_NO_INDENT();
  delete wid_progress_bar_window;
  wid_progress_bar_window = nullptr;
}

void wid_progress_bar(Gamep g, const std::string &title, float pct)
{
  verify(MTYPE_GAME, g);
  LOG("Progress bar: %s, %f pct", title.c_str(), pct);
  TRACE_NO_INDENT();

  if (wid_progress_bar_window) {
    wid_progress_bar_destroy(g);
  }

  int tile_num = (int) ((float) progress_steps * pct);
  if (tile_num > progress_steps) {
    tile_num = progress_steps;
  }
  if (tile_num < 1) {
    tile_num = 1;
  }

  std::string tilename = "progress_bar." + std::to_string(tile_num);

  auto   m  = TERM_WIDTH / 2;
  auto   n  = TERM_HEIGHT / 2;
  spoint tl = spoint(m - UI_WID_POPUP_WIDTH_WIDE / 2, n - 3);
  spoint br = spoint(m + UI_WID_POPUP_WIDTH_WIDE / 2, n + 4);

  wid_progress_bar_window = new WidPopup(g, "Progress bar", tl, br, nullptr, "", false, false);

  int y_at = 0;
  {
    TRACE_NO_INDENT();
    auto p = wid_progress_bar_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(g, p, "Title");

    spoint tl2 = spoint(0, y_at);
    spoint br2 = spoint(UI_WID_POPUP_WIDTH_WIDE, y_at);
    wid_set_shape_none(w);
    wid_set_pos(w, tl2, br2);
    wid_set_text(w, title);
  }

  y_at = 2;
  {
    TRACE_NO_INDENT();
    auto p = wid_progress_bar_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(g, p, "Progress");

    int x_at = UI_WID_POPUP_WIDTH_WIDE - progress_steps;
    x_at /= 2;
    spoint tl2 = spoint(x_at, y_at);
    spoint br2 = spoint(x_at + progress_steps - 1, y_at + 3);
    wid_set_pos(w, tl2, br2);
    wid_set_style(w, UI_WID_STYLE_HORIZ_DARK);
    wid_set_tilename(TILE_LAYER_FG_1, w, tilename);
  }

  wid_update(g, wid_progress_bar_window->wid_text_area->wid_text_area);

  sdl_flush_display(g, true /* force */);
}
