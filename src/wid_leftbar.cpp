//
// Copyright goblinhack@gmail.com
//

#include "my_ascii.hpp"
#include "my_callstack.hpp"
#include "my_game.hpp"
#include "my_level.hpp"
#include "my_main.hpp"
#include "my_wids.hpp"

static WidPopup *wid_leftbar;

static bool wid_leftbar_create_window(Gamep g)
{
  TRACE_NO_INDENT();
  DBG2("Remake leftbar");

  wid_leftbar_fini(g);

  auto v = game_levels_get(g);
  if (! v) {
    return false;
  }

  auto   width = UI_LEFTBAR_WIDTH;
  spoint tl(0, 0);
  spoint br(width - 1, TERM_HEIGHT - 1);
  wid_leftbar = new WidPopup(g, "left bar", tl, br, nullptr, "", false, false);

  auto player = thing_player(g);
  if (! player) {
    return false;
  }

  auto l = game_level_get(g, v);
  if (! l) {
    return false;
  }

  auto tp = thing_tp(player);
  if (! tp) {
    return false;
  }

  wid_leftbar->log_empty_line(g);

  wid_thing_info(g, v, l, player, wid_leftbar);

  return true;
}

void wid_leftbar_fini(Gamep g)
{
  TRACE_NO_INDENT();

  delete wid_leftbar;
  wid_leftbar = nullptr;
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
