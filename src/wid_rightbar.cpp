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

  auto width = UI_RIGHTBAR_WIDTH;

  {
    TRACE_NO_INDENT();
    spoint tl(TERM_WIDTH - width, 0);
    spoint br(TERM_WIDTH - 1, TERM_HEIGHT - 1);

    wid_rightbar = new WidPopup(g, "right bar", tl, br, nullptr, "", false, false);
  }

  if (l->level_num == LEVEL_SELECT_ID) {
    //
    // If in level select mode, we show different contents
    //
    level_select_rightbar_show_contents(g, v, l, wid_rightbar);
  } else {
    //
    // Normal level contents
    //
    {
      TRACE_NO_INDENT();
      wid_rightbar->log_empty_line(g);
      auto s = dynprintf("Level:%u Dungeon:%s", l->level_num + 1, game_seed_name_get(g));
      wid_rightbar->log(g, s);
      wid_rightbar->log_empty_line(g);
      myfree(s);
    }

    {
      TRACE_NO_INDENT();
      if (v->describe_count) {
        wid_rightbar->log_empty_line(g);
      }

      for (auto n = 0; n < v->describe_count; n++) {
        auto t = thing_find_optional(g, v, v->describe[ n ]);
        if (! t) {
          continue;
        }
        if (thing_is_player(t)) {
          continue;
        }
        auto tp = thing_tp(t);
        auto s  = capitalize(tp_long_name(tp));
        wid_rightbar->log(g, UI_INFO_FMT_STR + s + UI_RESET_FMT);
        wid_rightbar->log_empty_line(g);
        wid_rightbar->log(g, tp_detail_get(g, v, l, t), TEXT_FORMAT_LHS);
        wid_rightbar->log_empty_line(g);

        char tmp[ UI_RIGHTBAR_WIDTH * 2 ];
        memset(tmp, 0, sizeof(tmp));
        memset(tmp, ' ', sizeof(tmp) - 1);
        strncpy(tmp + 1, "Health", sizeof("Health") - 1);
        auto        health_max = tp_health_max_get(tp);
        std::string health_str = std::to_string(thing_health(t)) + "/" + std::to_string(health_max);
        strncpy(tmp + UI_RIGHTBAR_WIDTH - health_str.size() - 3, health_str.c_str(),
                UI_RIGHTBAR_WIDTH - health_str.size());
        tmp[ strlen(tmp) ] = ' ';

        auto w = wid_rightbar->log(g, std::string(tmp));
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
    }
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
