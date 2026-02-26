//
// Copyright goblinhack@gmail.com
//

#include "my_ascii.hpp"
#include "my_callstack.hpp"
#include "my_game.hpp"
#include "my_globals.hpp"
#include "my_main.hpp"
#include "my_thing_inlines.hpp"
#include "my_wids.hpp"

static WidPopup *wid_leftbar;

[[nodiscard]] static auto wid_leftbar_create_window(Gamep g) -> bool
{
  TRACE();
  DBG2("Remake leftbar");

  wid_leftbar_fini(g);

  auto *v = game_levels_get(g);
  if (v == nullptr) {
    return false;
  }

  auto         width = UI_LEFTBAR_WIDTH;
  spoint const tl(0, 0);
  spoint const br(width - 1, TERM_HEIGHT - 1);
  wid_leftbar = new WidPopup(g, "left bar", tl, br, nullptr, "", false, false);

  auto *player = thing_player(g);
  if (player == nullptr) [[unlikely]] {
    return false;
  }

  auto *l = game_level_get(g, v);
  if (l == nullptr) {
    return false;
  }

  auto *tp = thing_tp(player);
  if (tp == nullptr) [[unlikely]] {
    return false;
  }

  wid_thing_info(g, v, l, player, wid_leftbar, UI_LEFTBAR_WIDTH);

  return true;
}

void wid_leftbar_fini(Gamep g)
{
  TRACE();

  delete wid_leftbar;
  wid_leftbar = nullptr;
}

auto wid_leftbar_init(Gamep g) -> bool
{
  TRACE();
  return wid_leftbar_create_window(g);
}
