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
    auto   w = wid_new_square_button(g, wid_leftbar, "player name");
    spoint tl(0, y_at);
    spoint br(width - 1, y_at);
    wid_set_pos(w, tl, br);
    wid_set_text(w, game_player_name_get(g));
    wid_set_style(w, UI_WID_STYLE_NORMAL);
    wid_set_shape_none(w);
  }

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
