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

static Widp wid_rightbar {};

static WidPopup *wid_rightbar_popup;

static bool wid_rightbar_create_window(Gamep g)
{
  TRACE_NO_INDENT();
  DBG2("Remake rightbar");

  wid_rightbar_fini(g);

  auto v = game_levels_get(g);
  if (! v) {
    return false;
  }

  auto x_at  = 1;
  auto y_at  = 4;
  auto width = UI_RIGHTBAR_WIDTH;

  {
    TRACE_NO_INDENT();
    point tl(TERM_WIDTH - width, 0);
    point br(TERM_WIDTH - 1, TERM_HEIGHT - 1);

    wid_rightbar = wid_new_square_window(g, "wid rightbar");
    wid_set_ignore_scroll_events(wid_rightbar, true);
    wid_set_pos(wid_rightbar, tl, br);
    wid_set_style(wid_rightbar, UI_WID_STYLE_NORMAL);
    wid_lower(g, wid_rightbar);
  }

  auto l = game_level_get(g, v);
  if (l->level_num == LEVEL_SELECT_ID) {
    //
    // If in level select mode, we show different contents
    //
    level_select_show_contents(g, v, l, wid_rightbar);
  } else {
    //
    // Normal level contents
    //
    {
      TRACE_NO_INDENT();
      auto  w = wid_new_square_button(g, wid_rightbar, "level");
      point tl(x_at, y_at);
      point br(width - 1, y_at);
      wid_set_color(w, WID_COLOR_TEXT_FG, GREEN);
      wid_set_pos(w, tl, br);
      auto s = dynprintf("Level %u Seed %s", l->level_num, game_seed_name_get(g));
      wid_set_text(w, s);
      wid_set_style(w, UI_WID_STYLE_NORMAL);
      wid_set_shape_none(w);
      wid_set_text_centerx(w, true);
      myfree(s);
      y_at++;
    }
  }

  wid_update(g, wid_rightbar);

  DBG2("Remade rightbar");

  return true;
}

void wid_rightbar_fini(Gamep g)
{
  TRACE_NO_INDENT();
  wid_destroy(g, &wid_rightbar);

  delete wid_rightbar_popup;
  wid_rightbar_popup = nullptr;
}

bool wid_rightbar_init(Gamep g)
{
  TRACE_NO_INDENT();
  return wid_rightbar_create_window(g);
}

bool wid_rightbar_create(Gamep g)
{
  wid_rightbar_fini(g);

  auto level = game_levels_get(g);
  if (! level) {
    return false;
  }

  return wid_rightbar_create_window(g);
}
