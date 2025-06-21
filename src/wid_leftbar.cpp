//
// Copyright goblinhack@gmail.com
//

#include "my_ascii.hpp"
#include "my_callstack.hpp"
#include "my_color_defs.hpp"
#include "my_game.hpp"
#include "my_level.hpp"
#include "my_main.hpp"
#include "my_ptrcheck.hpp"
#include "my_sdl_event.hpp"
#include "my_string.hpp"
#include "my_wids.hpp"

static Widp wid_leftbar {};

static WidPopup *wid_leftbar_popup;

static bool wid_leftbar_create_window(Gamep g)
{
  TRACE_NO_INDENT();
  DBG2("Remake leftbar");

  wid_leftbar_fini(g);

  auto v = game_levels_get(g);
  if (! v) {
    return false;
  }

  int width = UI_RIGHTBAR_WIDTH;
  int y_at  = 0;

  {
    TRACE_NO_INDENT();
    spoint tl(0, 0);
    spoint br(width - 1, TERM_HEIGHT - 1);

    wid_leftbar = wid_new_square_window(g, "wid leftbar");
    wid_set_ignore_scroll_events(wid_leftbar, true);
    wid_set_pos(wid_leftbar, tl, br);
    wid_set_style(wid_leftbar, UI_WID_STYLE_NORMAL);
    wid_lower(g, wid_leftbar);
  }

  y_at = 4;
  {
    TRACE_NO_INDENT();
    auto   w = wid_new_square_button(g, wid_leftbar, "todo");
    spoint tl(0, y_at);
    spoint br(width - 1, y_at);
    wid_set_pos(w, tl, br);
    wid_set_text(w, "TODO");
    wid_set_style(w, UI_WID_STYLE_NORMAL);
    wid_set_shape_none(w);
  }

  if (0) {
    y_at++;
    TRACE_NO_INDENT();
    auto   w = wid_new_plain(g, wid_leftbar, "Seed");
    spoint tl(0, y_at);
    spoint br(width - 1, y_at);

    auto s = dynprintf("Seed: %%fg=gray$%s", game_seed_name_get(g));
    wid_set_pos(w, tl, br);
    wid_set_text(w, s);
    wid_set_shape_none(w);
    myfree(s);
  }

#if 0
  y_at = 8;
  {
    TRACE_NO_INDENT();
    auto  w = wid_new_square_button(wid_leftbar, "player");
    spoint tl(0, y_at);
    spoint br(width - 1, y_at);
    auto  s = dynprintf("%04u %04u", 0, 100);
    wid_set_pos( w, tl, br);
    wid_set_text( w, s);
    wid_set_style( w, UI_WID_STYLE_NORMAL);
    wid_set_color(g, w, WID_COLOR_TEXT_FG, RED);
    wid_set_shape_none( w);
    myfree(s);
  }

  y_at = 13;
  {
    TRACE_NO_INDENT();
    auto  w = wid_new_square_button(wid_leftbar, "player2");
    spoint tl(0, y_at);
    spoint br(width - 1, y_at);
    auto  s = dynprintf("%4u %4u", 0, 100);
    wid_set_pos( w, tl, br);
    wid_set_text( w, s);
    wid_set_style( w, UI_WID_STYLE_NORMAL);
    wid_set_color(g, w, WID_COLOR_TEXT_FG, DODGERBLUE);
    wid_set_shape_none( w);
    myfree(s);
  }

  y_at = 18;
  {
    TRACE_NO_INDENT();
    auto  w = wid_new_square_button(wid_leftbar, "player2");
    spoint tl(0, y_at);
    spoint br(width - 1, y_at);
    auto  s = dynprintf("%4u %4u", 0, 100);
    wid_set_pos( w, tl, br);
    wid_set_text( w, s);
    wid_set_style( w, UI_WID_STYLE_NORMAL);
    wid_set_color(g, w, WID_COLOR_TEXT_FG, YELLOW);
    wid_set_shape_none( w);
    myfree(s);
  }

  y_at = 23;
  {
    TRACE_NO_INDENT();
    auto  w = wid_new_square_button(wid_leftbar, "player2");
    spoint tl(0, y_at);
    spoint br(width - 1, y_at);
    auto  s = dynprintf("%4u %4u", 0, 100);
    wid_set_pos( w, tl, br);
    wid_set_text( w, s);
    wid_set_style( w, UI_WID_STYLE_NORMAL);
    wid_set_color(g, w, WID_COLOR_TEXT_FG, GREEN);
    wid_set_shape_none( w);
    myfree(s);
  }
#endif

  wid_update(g, wid_leftbar);

  DBG2("Remade leftbar");

  return true;
}

void wid_leftbar_fini(Gamep g)
{
  TRACE_NO_INDENT();
  wid_destroy(g, &wid_leftbar);

  delete wid_leftbar_popup;
  wid_leftbar_popup = nullptr;
}

bool wid_leftbar_init(Gamep g)
{
  TRACE_NO_INDENT();
  return wid_leftbar_create_window(g);
}

bool wid_leftbar_create(Gamep g)
{
  wid_leftbar_fini(g);

  auto level = game_levels_get(g);
  if (! level) {
    return false;
  }

  return wid_leftbar_create_window(g);
}
