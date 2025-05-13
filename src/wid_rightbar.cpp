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

  int width = UI_RIGHTBAR_WIDTH;
  int y_at  = 0;

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
    // Normal contents
    //
    y_at = 4;
    {
      TRACE_NO_INDENT();
      auto  w = wid_new_square_button(g, wid_rightbar, "level no");
      point tl(0, y_at);
      point br(width - 1, y_at);
      auto  s = dynprintf("Level %u", v->level_num);
      wid_set_pos(w, tl, br);
      wid_set_text(w, s);
      wid_set_style(w, UI_WID_STYLE_NORMAL);
      wid_set_shape_none(w);
      myfree(s);
    }

    if (0) {
      y_at++;
      TRACE_NO_INDENT();
      auto  w = wid_new_plain(g, wid_rightbar, "Seed");
      point tl(0, y_at);
      point br(width - 1, y_at);

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
    auto  w = wid_new_square_button(wid_rightbar, "player");
    point tl(0, y_at);
    point br(width - 1, y_at);
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
    auto  w = wid_new_square_button(wid_rightbar, "player2");
    point tl(0, y_at);
    point br(width - 1, y_at);
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
    auto  w = wid_new_square_button(wid_rightbar, "player2");
    point tl(0, y_at);
    point br(width - 1, y_at);
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
    auto  w = wid_new_square_button(wid_rightbar, "player2");
    point tl(0, y_at);
    point br(width - 1, y_at);
    auto  s = dynprintf("%4u %4u", 0, 100);
    wid_set_pos( w, tl, br);
    wid_set_text( w, s);
    wid_set_style( w, UI_WID_STYLE_NORMAL);
    wid_set_color(g, w, WID_COLOR_TEXT_FG, GREEN);
    wid_set_shape_none( w);
    myfree(s);
  }
#endif
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
