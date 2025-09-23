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

//
// Display detailed thing information
//
void wid_thing_info(Gamep g, Levelsp v, Levelp l, Thingp t, WidPopup *parent)
{
  ////////////////////////////////////////////////////////////////////////////////
  // Careful here. If we invoked the random number generator in here it can throw
  // off tests.
  ////////////////////////////////////////////////////////////////////////////////

  TRACE_NO_INDENT();

  if (! t) {
    return;
  }

  auto tp = thing_tp(t);
  if (! tp) {
    return;
  }

  //
  // The thing name
  //
  std::string s;
  if (thing_is_player(t)) {
    s = game_player_name_get(g);
  } else {
    s = tp_long_name(tp);
  }
  s = capitalize(s);

  parent->log(g, UI_INFO_FMT_STR + s + UI_RESET_FMT);
  parent->log_empty_line(g);
  parent->log(g, tp_detail_get(g, v, l, t), TEXT_FORMAT_LHS);
  parent->log_empty_line(g);

  char tmp[ UI_RIGHTBAR_WIDTH * 2 ];
  memset(tmp, 0, sizeof(tmp));
  memset(tmp, ' ', sizeof(tmp) - 1);
  strncpy(tmp + 1, "Health", sizeof("Health") - 1);
  auto        health_max = tp_health_max_get(tp);
  std::string health_str = std::to_string(thing_health(t)) + "/" + std::to_string(health_max);
  strncpy(tmp + UI_RIGHTBAR_WIDTH - health_str.size() - 3, health_str.c_str(), UI_RIGHTBAR_WIDTH - health_str.size());
  tmp[ strlen(tmp) ] = ' ';

  auto w = parent->log(g, std::string(tmp));
  if (w) {
    wid_set_shape_square(w);
    wid_set_style(w, UI_WID_STYLE_SPARSE_NONE);

    int i     = (int) (((float) thing_health(t) / (float) health_max) * ((float) UI_HEALTH_BAR_STEPS - 1));
    i         = std::min(i, UI_HEALTH_BAR_STEPS - 1);
    i         = std::max(i, 0);
    auto icon = "health_bar." + std::to_string(i + 1);
    wid_set_color(w, WID_COLOR_TEXT_FG, UI_HIGHLIGHT_COLOR);
    wid_set_tilename(TILE_LAYER_BG_0, w, icon);
    wid_set_text_lhs(w, true);
  }
}
