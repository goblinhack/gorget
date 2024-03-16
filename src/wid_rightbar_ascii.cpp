//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_color_defs.hpp"
#include "my_game.hpp"
#include "my_level.hpp"
#include "my_level_data.hpp"
#include "my_ptrcheck.hpp"
#include "my_string.hpp"
#include "my_thing.hpp"
#include "my_ui.hpp"
#include "my_vector_bounds_check.hpp"
#include "my_wid_rightbar.hpp"

bool wid_rightbar_ascii_create(void)
{
  TRACE_AND_INDENT();
  DBG2("Remake rightbar");

  auto level = game->level;
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
    // wid_set_shape_none(wid_rightbar);
    wid_lower(wid_rightbar);
  }

  {
    TRACE_AND_INDENT();
    auto  w  = wid_new_square_button(wid_rightbar, "level no");
    point tl = make_point(0, y_at);
    point br = make_point(width - 1, y_at);
    auto  s  = dynprintf("Level %u", level->data->num);
    wid_set_pos(w, tl, br);
    wid_set_text(w, s);
    wid_set_style(w, UI_WID_STYLE_NORMAL);
    wid_set_shape_none(w);
    myfree(s);
  }

  {
    y_at++;
    TRACE_AND_INDENT();
    auto  w  = wid_new_plain(wid_rightbar, "Seed");
    point tl = make_point(0, y_at);
    point br = make_point(width - 1, y_at);

    auto s = dynprintf("%%fg=gray$%s", game->seed_name.c_str());
    wid_set_pos(w, tl, br);
    wid_set_text(w, s);
    wid_set_shape_none(w);
    myfree(s);
  }

  wid_update(wid_rightbar);

  DBG2("Remade rightbar");

  return true;
}
