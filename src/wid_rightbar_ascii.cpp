//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_ascii.hpp"
#include "my_callstack.hpp"
#include "my_color_defs.hpp"
#include "my_game.hpp"
#include "my_level.hpp"
#include "my_ptrcheck.hpp"
#include "my_string.hpp"
#include "my_wids.hpp"

bool wid_rightbar_ascii_create(class Game *g)
{
  TRACE_AND_INDENT();
  DBG2("Remake rightbar");

  auto level = game_level_get(g);
  if (! level) {
    return false;
  }

  int width = UI_RIGHTBAR_WIDTH;
  int y_at  = 0;

  {
    TRACE_AND_INDENT();
    point tl = make_point(TERM_WIDTH - width, 0);
    point br = make_point(TERM_WIDTH - 1, TERM_HEIGHT - 1);

    wid_rightbar = wid_new_square_window("wid rightbar");
    wid_set_ignore_scroll_events(wid_rightbar, true);
    wid_set_pos(wid_rightbar, tl, br);
    wid_set_style(wid_rightbar, UI_WID_STYLE_NORMAL);
    wid_set_tilename(TILE_LAYER_BG_0, wid_rightbar, "ui_rightbar");
    wid_lower(wid_rightbar);
  }

  y_at = 4;
  {
    TRACE_AND_INDENT();
    auto  w  = wid_new_square_button(wid_rightbar, "level no");
    point tl = make_point(0, y_at);
    point br = make_point(width - 1, y_at);
    auto  s  = dynprintf("Level %u", level->num);
    wid_set_pos(w, tl, br);
    wid_set_text(w, s);
    wid_set_style(w, UI_WID_STYLE_NORMAL);
    wid_set_shape_none(w);
    myfree(s);
  }

  if (0) {
    y_at++;
    TRACE_AND_INDENT();
    auto  w  = wid_new_plain(wid_rightbar, "Seed");
    point tl = make_point(0, y_at);
    point br = make_point(width - 1, y_at);

    auto s = dynprintf("Seed: %%fg=gray$%s", game_seed_name_get(game));
    wid_set_pos(w, tl, br);
    wid_set_text(w, s);
    wid_set_shape_none(w);
    myfree(s);
  }

  y_at = 8;
  {
    TRACE_AND_INDENT();
    auto  w  = wid_new_square_button(wid_rightbar, "player1");
    point tl = make_point(0, y_at);
    point br = make_point(width - 1, y_at);
    auto  s  = dynprintf("%04u %04u", 0, 100);
    wid_set_pos(w, tl, br);
    wid_set_text(w, s);
    wid_set_style(w, UI_WID_STYLE_NORMAL);
    wid_set_color(w, WID_COLOR_TEXT_FG, RED);
    wid_set_shape_none(w);
    myfree(s);
  }

  y_at = 13;
  {
    TRACE_AND_INDENT();
    auto  w  = wid_new_square_button(wid_rightbar, "player2");
    point tl = make_point(0, y_at);
    point br = make_point(width - 1, y_at);
    auto  s  = dynprintf("%4u %4u", 0, 100);
    wid_set_pos(w, tl, br);
    wid_set_text(w, s);
    wid_set_style(w, UI_WID_STYLE_NORMAL);
    wid_set_color(w, WID_COLOR_TEXT_FG, DODGERBLUE);
    wid_set_shape_none(w);
    myfree(s);
  }

  y_at = 18;
  {
    TRACE_AND_INDENT();
    auto  w  = wid_new_square_button(wid_rightbar, "player2");
    point tl = make_point(0, y_at);
    point br = make_point(width - 1, y_at);
    auto  s  = dynprintf("%4u %4u", 0, 100);
    wid_set_pos(w, tl, br);
    wid_set_text(w, s);
    wid_set_style(w, UI_WID_STYLE_NORMAL);
    wid_set_color(w, WID_COLOR_TEXT_FG, YELLOW);
    wid_set_shape_none(w);
    myfree(s);
  }

  y_at = 23;
  {
    TRACE_AND_INDENT();
    auto  w  = wid_new_square_button(wid_rightbar, "player2");
    point tl = make_point(0, y_at);
    point br = make_point(width - 1, y_at);
    auto  s  = dynprintf("%4u %4u", 0, 100);
    wid_set_pos(w, tl, br);
    wid_set_text(w, s);
    wid_set_style(w, UI_WID_STYLE_NORMAL);
    wid_set_color(w, WID_COLOR_TEXT_FG, GREEN);
    wid_set_shape_none(w);
    myfree(s);
  }

  wid_update(wid_rightbar);

  DBG2("Remade rightbar");

  return true;
}
