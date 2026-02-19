//
// Copyright goblinhack@gmail.com
//

#include "my_ascii.hpp"
#include "my_callstack.hpp"
#include "my_game.hpp"
#include "my_gl.hpp"
#include "my_globals.hpp"
#include "my_level.hpp"
#include "my_main.hpp"
#include "my_sprintf.hpp"
#include "my_thing_inlines.hpp"
#include "my_wids.hpp"

#include <print>
#include <utility>

static WidPopup *wid_rightbar;
static auto      minimap_size = 14;

static void wid_rightbar_create_minimap_level(Gamep g)
{
  TRACE_NO_INDENT();

  {
    auto  *w = wid_new_square_button(g, wid_rightbar->wid_popup_container, "level map text");
    spoint minimap_tl(1, TERM_HEIGHT - minimap_size);
    spoint minimap_br(minimap_size + 2, TERM_HEIGHT - minimap_size);
    wid_set_text(w, "Level:");
    wid_set_text_lhs(w);
    wid_set_text_top(w);
    wid_set_style(w, UI_WID_STYLE_SPARSE_NONE);
    wid_set_pos(w, minimap_tl, minimap_br);
    wid_set_mode(w, WID_MODE_OVER);
    wid_set_color(w, WID_COLOR_BG, WHITE);
    wid_set_mode(w, WID_MODE_NORMAL);
    wid_set_color(w, WID_COLOR_BG, WHITE);
  }

  {
    auto  *w = wid_new_square_button(g, wid_rightbar->wid_popup_container, "level map");
    spoint minimap_tl(1, TERM_HEIGHT - minimap_size + 1);
    spoint minimap_br(minimap_size + 2, TERM_HEIGHT - 2);
    wid_set_tilename(TILE_LAYER_FG_0, w, "FBO_MINIMAP_LEVEL");
    wid_set_text_lhs(w);
    wid_set_text_top(w);
    wid_set_style(w, UI_WID_STYLE_SPARSE_NONE);
    wid_set_pos(w, minimap_tl, minimap_br);
    wid_set_mode(w, WID_MODE_OVER);
    wid_set_color(w, WID_COLOR_BG, WHITE);
    wid_set_mode(w, WID_MODE_NORMAL);
    wid_set_color(w, WID_COLOR_BG, WHITE);
  }
}

static void wid_rightbar_create_minimap_world(Gamep g)
{
  TRACE_NO_INDENT();

  {
    auto  *w = wid_new_square_button(g, wid_rightbar->wid_popup_container, "world map text");
    spoint minimap_tl(minimap_size + 3, TERM_HEIGHT - minimap_size);
    spoint minimap_br(minimap_size + minimap_size + 4, TERM_HEIGHT - minimap_size);
    wid_set_text(w, "World:");
    wid_set_text_lhs(w);
    wid_set_text_top(w);
    wid_set_style(w, UI_WID_STYLE_SPARSE_NONE);
    wid_set_pos(w, minimap_tl, minimap_br);
    wid_set_mode(w, WID_MODE_OVER);
    wid_set_color(w, WID_COLOR_BG, WHITE);
    wid_set_mode(w, WID_MODE_NORMAL);
    wid_set_color(w, WID_COLOR_BG, WHITE);
  }

  {
    auto  *w = wid_new_square_button(g, wid_rightbar->wid_popup_container, "world map");
    spoint minimap_tl(minimap_size + 3, TERM_HEIGHT - minimap_size + 1);
    spoint minimap_br(minimap_size + minimap_size + 4, TERM_HEIGHT - 2);
    wid_set_tilename(TILE_LAYER_FG_0, w, "FBO_MINIMAP_WORLD_ROTATED");
    wid_set_style(w, UI_WID_STYLE_SPARSE_NONE);
    wid_set_pos(w, minimap_tl, minimap_br);
    wid_set_mode(w, WID_MODE_OVER);
    wid_set_color(w, WID_COLOR_BG, WHITE);
    wid_set_mode(w, WID_MODE_NORMAL);
    wid_set_color(w, WID_COLOR_BG, WHITE);
  }
}

[[nodiscard]] static bool wid_rightbar_create_window(Gamep g)
{
  TRACE_NO_INDENT();
  DBG2("Remake rightbar");

  wid_rightbar_fini(g);

  auto *v = game_levels_get(g);
  if (v == nullptr) {
    return false;
  }

  auto *l = game_level_get(g, v);
  if (l == nullptr) {
    return false;
  }

  auto   width = UI_RIGHTBAR_WIDTH;
  spoint tl(TERM_WIDTH - width, 0);
  spoint br(TERM_WIDTH - 1, TERM_HEIGHT - 1);
  wid_rightbar = new WidPopup(g, "right bar", tl, br, nullptr, "", false, false);

  if (level_is_level_select(g, v, l)) {
    //
    // If in level select mode, we show different contents
    //
    level_select_rightbar_show_contents(g, v, l, wid_rightbar);
  } else {
    //
    // Normal level contents
    //
    wid_rightbar->log_empty_line(g);
    auto s = std::format("Level:{} Dungeon:{}", l->level_num + 1, game_seed_name_get(g));
    wid_rightbar->log(g, s);

    IF_DEBUG
    {
      s = std::format("Move:{}", v->tick);
      wid_rightbar->log(g, s);
    }

    for (auto n = 0; std::cmp_less(n, v->describe_count); n++) {
      auto *t = thing_find_optional(g, v, v->describe[ n ]);
      if (t == nullptr) {
        continue;
      }

      if (thing_is_player(t)) {
        continue;
      }

      wid_thing_info(g, v, l, t, wid_rightbar, UI_RIGHTBAR_WIDTH);
    }
  }

  //
  // Always show minimaps
  //
  wid_rightbar_create_minimap_level(g);
  wid_rightbar_create_minimap_world(g);

  wid_update(g, wid_rightbar->wid_popup_container);

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
  auto *level = game_levels_get(g);
  if (level == nullptr) {
    return false;
  }

  return wid_rightbar_create_window(g);
}
