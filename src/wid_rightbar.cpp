//
// Copyright Neil McGill, goblinhack@gmail.com
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

Widp wid_rightbar {};
Widp wid_map_mini {};

static WidPopup *wid_rightbar_popup;

static bool wid_rightbar_create_window(class Game *g)
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
    point tl(TERM_WIDTH - width, 0);
    point br(TERM_WIDTH - 1, TERM_HEIGHT - 1);

    wid_rightbar = wid_new_square_window("wid rightbar");
    wid_set_ignore_scroll_events(wid_rightbar, true);
    wid_set_pos(wid_rightbar, tl, br);
    wid_set_style(wid_rightbar, UI_WID_STYLE_NORMAL);
    wid_lower(wid_rightbar);
  }

  y_at = 4;
  {
    TRACE_AND_INDENT();
    auto  w = wid_new_square_button(wid_rightbar, "level no");
    point tl(0, y_at);
    point br(width - 1, y_at);
    auto  s = dynprintf("Level %u", level->num);
    wid_set_pos(w, tl, br);
    wid_set_text(w, s);
    wid_set_style(w, UI_WID_STYLE_NORMAL);
    wid_set_shape_none(w);
    myfree(s);
  }

  if (0) {
    y_at++;
    TRACE_AND_INDENT();
    auto  w = wid_new_plain(wid_rightbar, "Seed");
    point tl(0, y_at);
    point br(width - 1, y_at);

    auto s = dynprintf("Seed: %%fg=gray$%s", game_seed_name_get(game));
    wid_set_pos(w, tl, br);
    wid_set_text(w, s);
    wid_set_shape_none(w);
    myfree(s);
  }

#if 0
  y_at = 8;
  {
    TRACE_AND_INDENT();
    auto  w = wid_new_square_button(wid_rightbar, "player1");
    point tl(0, y_at);
    point br(width - 1, y_at);
    auto  s = dynprintf("%04u %04u", 0, 100);
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
    auto  w = wid_new_square_button(wid_rightbar, "player2");
    point tl(0, y_at);
    point br(width - 1, y_at);
    auto  s = dynprintf("%4u %4u", 0, 100);
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
    auto  w = wid_new_square_button(wid_rightbar, "player2");
    point tl(0, y_at);
    point br(width - 1, y_at);
    auto  s = dynprintf("%4u %4u", 0, 100);
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
    auto  w = wid_new_square_button(wid_rightbar, "player2");
    point tl(0, y_at);
    point br(width - 1, y_at);
    auto  s = dynprintf("%4u %4u", 0, 100);
    wid_set_pos(w, tl, br);
    wid_set_text(w, s);
    wid_set_style(w, UI_WID_STYLE_NORMAL);
    wid_set_color(w, WID_COLOR_TEXT_FG, GREEN);
    wid_set_shape_none(w);
    myfree(s);
  }
#endif

  wid_update(wid_rightbar);

  DBG2("Remade rightbar");

  return true;
}

void wid_rightbar_fini(class Game *g)
{
  TRACE_AND_INDENT();
  wid_destroy(&wid_rightbar);
  wid_destroy(&wid_map_mini);

  delete wid_rightbar_popup;
  wid_rightbar_popup = nullptr;
}

bool wid_rightbar_init(class Game *g)
{
  TRACE_AND_INDENT();
  return wid_rightbar_create_window(g);
}

bool wid_rightbar_create(class Game *g)
{
  wid_rightbar_fini(g);

  auto level = game_level_get(g);
  if (! level) {
    return false;
  }

  return wid_rightbar_create_window(g);
}

bool is_mouse_over_rightbar(void)
{
  if (! wid_rightbar) {
    return false;
  }

  //
  // If we are in the portion of the lower screen above the itembar
  // then do not scroll
  //
  int x = sdl.mouse_x;
  int y = sdl.mouse_y;
  pixel_to_ascii(&x, &y);

  static int tlx, tly, brx, bry, cached;
  if (cached != TERM_HEIGHT) {
    cached = TERM_HEIGHT;
  }

  wid_get_tl_x_tl_y_br_x_br_y(wid_rightbar, &tlx, &tly, &brx, &bry);

  //
  // Add some border
  //
  tlx -= 1;
  brx++;
  tly -= 1;
  bry++;

  if ((x >= tlx) && (x < brx) && (y >= tly)) {
    // CON("    rightbar %d %d %d", tlx, brx, x);
    return true;
  }
  // CON("NOT rightbar %d %d %d", tlx, brx, x);

  return false;
}
