//
// Copyright goblinhack@gmail.com
//

#include "my_ascii.hpp"
#include "my_callstack.hpp"
#include "my_game.hpp"
#include "my_level.hpp"
#include "my_main.hpp"
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

  auto player = thing_player(g);
  if (! player) {
    return false;
  }

  auto tp = thing_tp(player);

  y_at += 2;

  {
    TRACE_AND_INDENT();
    auto   w = wid_new_plain(g, wid_leftbar, "Health-bar");
    spoint tl(1, y_at);
    spoint br(width - 2, y_at);
    wid_set_pos(w, tl, br);

    int i     = (int) (((float) thing_health(player) / (float) tp_health_initial_get(tp))
                   * ((float) UI_HEALTH_BAR_STEPS - 1));
    i         = std::min(i, UI_HEALTH_BAR_STEPS - 1);
    i         = std::max(i, 0);
    auto icon = "health_bar." + std::to_string(i + 1);
    wid_set_tilename(TILE_LAYER_FG_0, w, icon);
  }
  {
    TRACE_AND_INDENT();
    auto   w = wid_new_plain(g, wid_leftbar, "Health");
    spoint tl(1, y_at);
    spoint br(width - 2, y_at);
    wid_set_pos(w, tl, br);
    wid_set_text(w, " Health");
    wid_set_shape_none(w);
    wid_set_text_lhs(w, true);
  }
  {
    TRACE_AND_INDENT();
    auto   w = wid_new_plain(g, wid_leftbar, "health-value");
    spoint tl(1, y_at);
    spoint br(tl.x + width - 4, tl.y);
    wid_set_pos(w, tl, br);
    wid_set_shape_none(w);

    std::string s = std::to_string(thing_health(player)) + "/" + std::to_string(tp_health_initial_get(tp));
    wid_set_text(w, s);
    wid_set_text_rhs(w, true);
  }

  wid_update(g, wid_leftbar);

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
