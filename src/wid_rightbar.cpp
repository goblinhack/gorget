//
// Copyright goblinhack@gmail.com
//

#include "my_ascii.hpp"
#include "my_callstack.hpp"
#include "my_color_defs.hpp"
#include "my_game.hpp"
#include "my_level.hpp"
#include "my_ptrcheck.hpp"
#include "my_string.hpp"
#include "my_tp_callbacks.hpp"
#include "my_wids.hpp"

static WidPopup *wid_rightbar;

static bool wid_rightbar_create_window(Gamep g)
{
  TRACE_NO_INDENT();
  DBG2("Remake rightbar");

  wid_rightbar_fini(g);

  auto v = game_levels_get(g);
  if (! v) {
    return false;
  }

  auto l = game_level_get(g, v);
  if (! l) {
    return false;
  }

  auto   width = UI_RIGHTBAR_WIDTH;
  spoint tl(TERM_WIDTH - width, 0);
  spoint br(TERM_WIDTH - 1, TERM_HEIGHT - 1);
  wid_rightbar = new WidPopup(g, "right bar", tl, br, nullptr, "", false, false);

  if (l->level_num == LEVEL_SELECT_ID) {
    //
    // If in level select mode, we show different contents
    //
    level_select_rightbar_show_contents(g, v, l, wid_rightbar);
    return true;
  }

  //
  // Normal level contents
  //
  wid_rightbar->log_empty_line(g);
  auto s = dynprintf("Level:%u Dungeon:%s", l->level_num + 1, game_seed_name_get(g));
  wid_rightbar->log(g, s);
  wid_rightbar->log_empty_line(g);
  myfree(s);

  for (auto n = 0; n < v->describe_count; n++) {
    auto t = thing_find_optional(g, v, v->describe[ n ]);
    if (! t) {
      continue;
    }
    if (thing_is_player(t)) {
      continue;
    }

    wid_thing_info(g, v, l, t, wid_rightbar);
  }

  return true;
}

void wid_rightbar_fini(Gamep g)
{
  TRACE_NO_INDENT();

  delete wid_rightbar;
  wid_rightbar = nullptr;
}

bool wid_rightbar_init(Gamep g)
{
  TRACE_NO_INDENT();
  return wid_rightbar_create_window(g);
}

bool wid_rightbar_create(Gamep g)
{
  auto level = game_levels_get(g);
  if (! level) {
    return false;
  }

  return wid_rightbar_create_window(g);
}
