//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
// REMOVED #include "my_cave.hpp"
#include "my_charmap.hpp"
#include "my_color_defs.hpp"
#include "my_dice.hpp"
#include "my_game.hpp"
#include "my_level.hpp"
// REMOVED #include "my_main.hpp"
#include "my_ptrcheck.hpp"
#include "my_random.hpp"
#include "my_string.hpp"
// REMOVED #include "my_tp.hpp"
#include "my_ui.hpp"
// REMOVED #include "my_wid.hpp"
#include "my_wids.hpp"

// REMOVED #include <map>
// REMOVED #include <stdlib.h>

bool level_select_is_oob(spoint p)
{
  TRACE_NO_INDENT();

  if (p.x < 0) {
    return true;
  }
  if (p.y < 0) {
    return true;
  }
  if (p.x >= LEVELS_ACROSS) {
    return true;
  }
  if (p.y >= LEVELS_DOWN) {
    return true;
  }
  return false;
}

bool level_select_is_oob(int x, int y)
{
  TRACE_NO_INDENT();

  if (x < 0) {
    return true;
  }
  if (y < 0) {
    return true;
  }
  if (x >= LEVELS_ACROSS) {
    return true;
  }
  if (y >= LEVELS_DOWN) {
    return true;
  }
  return false;
}

//
// Given a point in the level select grid, return the corresponding level,
// if one exists there.
//
Levelp level_select_get_level(Gamep g, Levelsp v, Levelp l, spoint p)
{
  TRACE_NO_INDENT();

  if (! v) {
    return nullptr;
  }

  if (level_select_is_oob(p)) {
    return nullptr;
  }

  auto s = &v->level_select.data[ p.x ][ p.y ];
  if (! s->is_set) {
    return nullptr;
  }

  auto level_num = s->level_num;
  if (level_num < 0) {
    return nullptr;
  }

  if (level_num >= LEVEL_SELECT_ID) {
    return nullptr;
  }

  return &v->level[ level_num ];
}

//
// Attempt to find the next level for this thing to fall into
//
Levelp level_select_get_next_level_down(Gamep g, Levelsp v, Levelp l)
{
  TRACE_NO_INDENT();

  auto p     = l->level_select_at;
  int  tries = 0;

  while (tries++ < LEVELS_DOWN * 2) {
    p.y++;
    if (p.y >= LEVELS_DOWN) {
      p.y = 0;
    }

    auto cand = level_select_get_level(g, v, l, p);
    if (cand && (cand != l)) {
      return cand;
    }
  }

  //
  // Nothing to fall onto. Try a random level.
  //
  for (;;) {
    spoint random_p(pcg_random_range(0, LEVELS_ACROSS), pcg_random_range(0, LEVELS_DOWN));

    auto cand = level_select_get_level(g, v, l, random_p);
    if (cand && (cand != l)) {
      return cand;
    }
  }
}

//
// This is the thing that is used to represent the current level. We focus the mouse zoom on this.
//
Thingp thing_level_select(Gamep g)
{
  TRACE_NO_INDENT();

  auto v = game_levels_get(g);
  if (! v) {
    return nullptr;
  }

  if (! v->level_select_id) {
    return nullptr;
  }

  return thing_find(g, v, v->level_select_id);
}

//
// Dump a level
//
static void level_select_dump(Gamep g, Levelsp v, LevelSelect *s)
{
  TRACE_NO_INDENT();

  LOG("LevelSelect, level count %d", s->level_count);

  for (int y = 0; y < LEVELS_DOWN; y++) {
    std::string out;
    for (int x = 0; x < LEVELS_ACROSS; x++) {
      out += s->data[ x ][ y ].is_set ? CHARMAP_FLOOR : CHARMAP_EMPTY;
    }
    LOG("%s", out.c_str());
  }
  LOG("-");
}

//
// Assign levels to their position in the grid
//
void level_select_assign_levels_to_grid(Gamep g, Levelsp v)
{
  TRACE_NO_INDENT();

  LevelSelect *s = &v->level_select;

  auto n = 0;

  for (int y = 0; y < LEVELS_DOWN; y++) {
    for (int x = 0; x < LEVELS_ACROSS; x++) {
      if (s->data[ x ][ y ].is_set) {
        auto l = game_level_get(g, v, n);
        if (! l) {
          DIE("ran out of levels to assign to grid, %u", n);
        }

        if (! l->initialized) {
          DIE("trying to use a level that is not initialized, %u", n);
        }

        s->data[ x ][ y ].level_num = l->level_num;
        l->level_select_at          = spoint(x, y);

        n++;
      }
    }
  }
}

//
// Count the levels created
//
static int level_select_count_levels(Gamep g, Levelsp v, LevelSelect *s)
{
  TRACE_NO_INDENT();

  s->level_count = 0;

  for (int y = 0; y < LEVELS_DOWN; y++) {
    for (int x = 0; x < LEVELS_ACROSS; x++) {
      if (s->data[ x ][ y ].is_set) {
        s->level_count++;
      }
    }
  }
  return s->level_count;
}

static void snake_dive(Gamep g, Levelsp v, LevelSelect *s, spoint at, int dive_chance)
{
  TRACE_NO_INDENT();

  spoint end(LEVELS_ACROSS - 1, LEVELS_DOWN - 1);

  while (at != end) {
    //
    // Ensure we never try to create too many levels
    //
    // Keep one free for the select level
    //
    if (level_select_count_levels(g, v, s) >= LEVEL_SELECT_ID) {
      return;
    }

    auto chance = d100();

    s->data[ at.x ][ at.y ].is_set = true;

    if (chance < dive_chance) {
      at.y++;
    } else {
      at.x++;
    }

    if (at.x > LEVELS_ACROSS - 1) {
      at.x = LEVELS_ACROSS - 1;
    }
    if (at.y > LEVELS_DOWN - 1) {
      at.y = LEVELS_DOWN - 1;
    }
  }

  s->data[ at.x ][ at.y ].is_set = true;
}

static void snake_dive(Gamep g, Levelsp v, LevelSelect *s, int dive_chance)
{
  TRACE_NO_INDENT();

  while (true) {
    auto x = pcg_random_range(0, LEVELS_ACROSS);
    auto y = pcg_random_range(0, LEVELS_DOWN);

    if (s->data[ x ][ y ].is_set) {
      snake_dive(g, v, s, spoint(x, y), dive_chance);

      return;
    }
  }
}

//
// Create a Thing for each level
//
static void level_select_map_set(Gamep g, Levelsp v)
{
  LOG("level select map");
  TRACE_NO_INDENT();

  LevelSelect *s            = &v->level_select;
  auto         level_num    = LEVEL_SELECT_ID;
  auto         level_select = game_level_get(g, v, level_num);

  auto   player       = thing_player(g);
  Levelp player_level = nullptr;
  if (player) {
    player_level = game_level_get(g, v, player->level_num);
  }

  memset(level_select->debug, ' ', SIZEOF(level_select->debug));

  auto tp_is_level_not_visited = tp_random(is_level_not_visited);
  auto tp_is_level_curr        = tp_random(is_level_curr);
  auto tp_is_level_across      = tp_random(is_level_across);
  auto tp_is_level_down        = tp_random(is_level_down);
  auto tp_is_level_final       = tp_random(is_level_final);
  auto tp_is_level_visited     = tp_random(is_level_visited);
  auto tp_is_level_next        = tp_random(is_level_next);

  for (auto y = 0; y < LEVELS_DOWN; y++) {
    for (auto x = 0; x < LEVELS_ACROSS; x++) {
      LevelSelectCell *c = &s->data[ x ][ y ];
      if (! c->is_set) {
        continue;
      }

      auto l = game_level_get(g, v, c->level_num);
      if (! l) {
        ERR("missing level in select map");
        continue;
      }

      //
      // Default
      //
      Tpp tp = tp_is_level_not_visited;

      //
      // Completed levels
      //
      if (l->player_completed_level_via_exit || l->player_fell_out_of_level) {
        tp = tp_is_level_visited;
      }

      //
      // Can we enter this level?
      //
      l->next_level = false;

      //
      // If not visited, is it a next level for the current level?
      //
      if (player_level && (player_level->player_completed_level_via_exit || player_level->player_fell_out_of_level)
          && (tp == tp_is_level_not_visited)) {
        if (y > 0) {
          LevelSelectCell *o = &s->data[ x ][ y - 1 ];
          if (o && o->is_set && (o->level_num == player_level->level_num)) {
            tp            = tp_is_level_next;
            l->next_level = true;
          }
        }
        if (x > 0) {
          LevelSelectCell *o = &s->data[ x - 1 ][ y ];
          if (o && o->is_set && (o->level_num == player_level->level_num)) {
            tp            = tp_is_level_next;
            l->next_level = true;
          }
        }

        if (y < LEVELS_DOWN - 1) {
          LevelSelectCell *o = &s->data[ x ][ y + 1 ];
          if (o && o->is_set && (o->level_num == player_level->level_num)) {
            tp            = tp_is_level_next;
            l->next_level = true;
          }
        }
        if (x < LEVELS_ACROSS - 1) {
          LevelSelectCell *o = &s->data[ x + 1 ][ y ];
          if (o && o->is_set && (o->level_num == player_level->level_num)) {
            tp            = tp_is_level_next;
            l->next_level = true;
          }
        }
      }

      //
      // Allow backwards moves to completed levels
      //
      if (player_level && (l->player_completed_level_via_exit || l->player_fell_out_of_level)
          && (tp == tp_is_level_visited)) {
        if (y > 0) {
          LevelSelectCell *o = &s->data[ x ][ y - 1 ];
          if (o && o->is_set && (o->level_num == player_level->level_num)) {
            tp            = tp_is_level_next;
            l->next_level = true;
          }
        }
        if (x > 0) {
          LevelSelectCell *o = &s->data[ x - 1 ][ y ];
          if (o && o->is_set && (o->level_num == player_level->level_num)) {
            tp            = tp_is_level_next;
            l->next_level = true;
          }
        }

        if (y < LEVELS_DOWN - 1) {
          LevelSelectCell *o = &s->data[ x ][ y + 1 ];
          if (o && o->is_set && (o->level_num == player_level->level_num)) {
            tp            = tp_is_level_next;
            l->next_level = true;
          }
        }
        if (x < LEVELS_ACROSS - 1) {
          LevelSelectCell *o = &s->data[ x + 1 ][ y ];
          if (o && o->is_set && (o->level_num == player_level->level_num)) {
            tp            = tp_is_level_next;
            l->next_level = true;
          }
        }
      }

      if (g_opt_quick_start_level_select_menu) {
        l->next_level = true;
      }

      //
      // Final level
      //
      if ((x == LEVELS_ACROSS - 1) && (y == LEVELS_DOWN - 1)) {
        tp = tp_is_level_final;
      }

      if (player) {
        //
        // Where the player is currently
        //
        if (player->level_num == l->level_num) {
          tp = tp_is_level_curr;
        }
      } else if ((x == 0) && (y == 0)) {
        //
        // Where the player is initially
        //
        tp = tp_is_level_curr;
      }

      if (tp) {
        spoint at(x * LEVEL_SCALE + 1, y * LEVEL_SCALE + 1);

        //
        // Save debugging
        //
        level_select->debug[ at.x ][ at.y ] = '#';

        if (tp == tp_is_level_not_visited) {
          level_select->debug[ at.x ][ at.y ] = '?';
        }
        if (tp == tp_is_level_curr) {
          level_select->debug[ at.x ][ at.y ] = '@';
        }
        if (tp == tp_is_level_final) {
          level_select->debug[ at.x ][ at.y ] = 'E';
        }
        if (tp == tp_is_level_next) {
          level_select->debug[ at.x ][ at.y ] = '?';
        }

        //
        // Show all levels as next when debugging
        //
        if (g_opt_quick_start_level_select_menu && (tp == tp_is_level_not_visited)) {
          tp = tp_is_level_next;
        }

        thing_spawn(g, v, level_select, tp, at);
      }
    }
  }

  //
  // Add horizontal level connector
  //
  for (auto y = 0; y < LEVELS_DOWN; y++) {
    for (auto x = 0; x < LEVELS_ACROSS - 1; x++) {
      LevelSelectCell *c = &s->data[ x ][ y ];
      if (! c->is_set) {
        continue;
      }
      LevelSelectCell *n = &s->data[ x + 1 ][ y ];
      if (! n->is_set) {
        continue;
      }

      for (auto div = 0; div < LEVEL_SCALE - 1; div++) {
        spoint at(x * LEVEL_SCALE + div + 2, y * LEVEL_SCALE + 1);
        level_select->debug[ at.x ][ at.y ] = '-';

        thing_spawn(g, v, level_select, tp_is_level_across, at);
      }
    }
  }

  //
  // Add vertical level connector
  //
  for (auto y = 0; y < LEVELS_DOWN - 1; y++) {
    for (auto x = 0; x < LEVELS_ACROSS; x++) {
      LevelSelectCell *c = &s->data[ x ][ y ];
      if (! c->is_set) {
        continue;
      }
      LevelSelectCell *n = &s->data[ x ][ y + 1 ];
      if (! n->is_set) {
        continue;
      }

      for (auto div = 0; div < LEVEL_SCALE - 1; div++) {
        spoint at(x * LEVEL_SCALE + 1, y * LEVEL_SCALE + div + 2);
        level_select->debug[ at.x ][ at.y ] = '|';

        thing_spawn(g, v, level_select, tp_is_level_down, at);
      }
    }
  }

  //
  // Add some rocks in empty spaces
  //
  for (auto y = 0; y < MAP_HEIGHT; y++) {
    for (auto x = 0; x < MAP_WIDTH; x++) {
      auto   count = 0;
      spoint at(x, y);
      FOR_ALL_THINGS_AT(g, v, level_select, it, at) { count++; }
      if (! count) {
        auto tp_rock = tp_random(is_dirt);
        thing_spawn(g, v, level_select, tp_rock, at);
      }
    }
  }

  //
  // Create joined up tiles (for the rocks)
  //
  level_assign_tiles(g, v, level_select);
}

//
// Create the level grid
//
static void level_select_create(Gamep g, Levelsp v, LevelSelect *s)
{
  TRACE_NO_INDENT();

  if (s->is_populated) {
    return;
  }

  //
  // Use a consistent seed
  //
  uint32_t seed_num = game_seed_num_get(g);
  pcg_srand(seed_num);

  snake_dive(g, v, s, spoint(0, 0), 90);
  snake_dive(g, v, s, 90);
  snake_dive(g, v, s, spoint(0, 0), 50);
  snake_dive(g, v, s, spoint(0, 0), 30);
  snake_dive(g, v, s, spoint(0, 0), 30);
  snake_dive(g, v, s, spoint(0, 0), 30);
  snake_dive(g, v, s, 30);
  snake_dive(g, v, s, 30);
  snake_dive(g, v, s, 30);

  s->is_populated = true;
}

//
// Create the things that are used to represent levels
//
void level_select_update_grid_tiles(Gamep g, Levelsp v)
{
  TRACE_NO_INDENT();

  auto level_num = LEVEL_SELECT_ID;
  auto l         = game_level_get(g, v, level_num);

  l->initialized   = true;
  l->level_num     = level_num;
  l->info.seed_num = game_seed_num_get(g);

  level_select_map_set(g, v);
}

//
// Create the special level used to walk other levels
//
void level_select_grid_of_empty_levels(Gamep g)
{
  LOG("Level select generate");
  TRACE_AND_INDENT();

  auto v = levels_memory_alloc(g);
  game_levels_set(g, v);
  LevelSelect *s = &v->level_select;

  level_select_create(g, v, s);
  level_select_dump(g, v, s);
  level_select_count_levels(g, v, s);
}

//
// Clean up the level select snake walk
//
void level_select_destroy(Gamep g, Levelsp v, Levelp l)
{
  LOG("Level select destroy");
  TRACE_AND_INDENT();

  if (! l || ! l->initialized) {
    return;
  }

  LevelSelect *s = &v->level_select;
  memset(s, 0, SIZEOF(*s));
}

//
// Show a sorted list of vales
//
static int level_select_show_sorted_values(Gamep g, Levelsp v, Levelp l, Widp parent,
                                           std::map< std::string, int > map_in, std::string map_name, int width,
                                           int x_at, int y_at)
{
  TRACE_NO_INDENT();

  if (! map_in.size()) {
    return y_at;
  }

  {
    TRACE_NO_INDENT();
    auto   w = wid_new_square_button(g, parent, map_name);
    spoint tl(x_at, y_at);
    spoint br(width - 1, y_at);
    auto   s1 = dynprintf(" %s:", map_name.c_str());
    wid_set_color(w, WID_COLOR_TEXT_FG, YELLOW);
    wid_set_pos(w, tl, br);
    wid_set_text(w, s1);
    wid_set_style(w, UI_WID_STYLE_NORMAL);
    wid_set_shape_none(w);
    wid_set_text_lhs(w, true);
    myfree(s1);
  }
  y_at++;

  while (map_in.size()) {
    std::string highest;
    for (auto m : map_in) {
      auto name = m.first;
      auto val  = m.second;
      if (highest.empty()) {
        highest = name;
      } else if (val > map_in[ highest ]) {
        highest = name;
      }
    }

    {
      TRACE_NO_INDENT();
      auto   w = wid_new_square_button(g, parent, map_name);
      spoint tl(x_at, y_at);
      spoint br(width - 1, y_at);

      auto        tp   = tp_find_mand(highest.c_str());
      std::string name = tp_short_name(tp);

      auto s2 = dynprintf("  %u x %%tp=%s$ %s", map_in[ highest ], highest.c_str(), name.c_str());

      wid_set_color(w, WID_COLOR_TEXT_FG, WHITE);
      wid_set_pos(w, tl, br);
      wid_set_text(w, s2);
      wid_set_style(w, UI_WID_STYLE_NORMAL);
      wid_set_shape_none(w);
      wid_set_text_lhs(w, true);
      myfree(s2);
    }
    y_at++;

    map_in.erase(highest);
  }

  return y_at;
}

//
// If in level select mode, update what we're hovering over
//
void level_select_rightbar_show_contents(Gamep g, Levelsp v, Levelp l, Widp parent)
{
  TRACE_NO_INDENT();

  int x  = (v->cursor_at.x - 1) / LEVEL_SCALE;
  int y  = (v->cursor_at.y - 1) / LEVEL_SCALE;
  int dx = (v->cursor_at.x - 1) % LEVEL_SCALE;
  int dy = (v->cursor_at.y - 1) % LEVEL_SCALE;

  if (dx || dy) {
    return;
  }

  LevelSelect *s = &v->level_select;
  Levelp       level_over;
  if (s->data[ x ][ y ].is_set) {
    level_over = game_level_get(g, v, s->data[ x ][ y ].level_num);
  } else {
    level_over = nullptr;
  }

  if (! level_over) {
    return;
  }

  LOG("show level contents for level %d,%d mod %d,%d %p level num %u", x, y, dx, dy, (void *) level_over,
      level_over->level_num);

  auto   player       = thing_player(g);
  Levelp player_level = nullptr;
  if (player) {
    player_level = game_level_get(g, v, player->level_num);
  }

  std::map< std::string, int > mobs;
  std::map< std::string, int > monsts;
  std::map< std::string, int > treasure;

  FOR_ALL_THINGS_ON_LEVEL(g, v, level_over, t)
  {
    auto name = tp_name(thing_tp(t));

    if (thing_is_mob(t)) {
      mobs[ name ]++;
    }

    if (thing_is_monst(t)) {
      monsts[ name ]++;
    }

    if (thing_is_treasure(t)) {
      treasure[ name ]++;
    }
  }

  auto x_at  = 1;
  auto y_at  = 4;
  auto width = UI_RIGHTBAR_WIDTH;

  {
    TRACE_NO_INDENT();
    auto   w = wid_new_square_button(g, parent, "level");
    spoint tl(x_at, y_at);
    spoint br(width - 1, y_at);
    wid_set_color(w, WID_COLOR_TEXT_FG, GREEN);
    wid_set_pos(w, tl, br);
    auto tmp = dynprintf("Level %u", level_over->level_num + 1);
    wid_set_text(w, tmp);
    wid_set_style(w, UI_WID_STYLE_NORMAL);
    wid_set_shape_none(w);
    wid_set_text_lhs(w, true);
    myfree(tmp);
    y_at++;
  }

  if (level_over->next_level) {
    if (player_level->player_completed_level_via_exit) {
      TRACE_NO_INDENT();
      auto   w = wid_new_square_button(g, parent, "level");
      spoint tl(x_at, y_at);
      spoint br(width - 1, y_at);
      wid_set_color(w, WID_COLOR_TEXT_FG, WHITE);
      wid_set_pos(w, tl, br);
      wid_set_text(w, " You can enter here");
      wid_set_style(w, UI_WID_STYLE_NORMAL);
      wid_set_shape_none(w);
      wid_set_text_lhs(w, true);
      y_at++;
    } else if (player_level->player_fell_out_of_level) {
      TRACE_NO_INDENT();
      auto   w = wid_new_square_button(g, parent, "level");
      spoint tl(x_at, y_at);
      spoint br(width - 1, y_at);
      wid_set_color(w, WID_COLOR_TEXT_FG, WHITE);
      wid_set_pos(w, tl, br);
      wid_set_text(w, " You can climb back here");
      wid_set_style(w, UI_WID_STYLE_NORMAL);
      wid_set_shape_none(w);
      wid_set_text_lhs(w, true);
      y_at++;
    } else {
      TRACE_NO_INDENT();
      auto   w = wid_new_square_button(g, parent, "level");
      spoint tl(x_at, y_at);
      spoint br(width - 1, y_at);
      wid_set_color(w, WID_COLOR_TEXT_FG, WHITE);
      wid_set_pos(w, tl, br);
      wid_set_text(w, " You can go back here");
      wid_set_style(w, UI_WID_STYLE_NORMAL);
      wid_set_shape_none(w);
      wid_set_text_lhs(w, true);
      y_at++;
    }
  } else if (level_over != player_level) {
    TRACE_NO_INDENT();
    auto   w = wid_new_square_button(g, parent, "level");
    spoint tl(x_at, y_at);
    spoint br(width - 1, y_at);
    wid_set_color(w, WID_COLOR_TEXT_FG, RED);
    wid_set_pos(w, tl, br);
    wid_set_text(w, " You cannot enter here yet");
    wid_set_style(w, UI_WID_STYLE_NORMAL);
    wid_set_shape_none(w);
    wid_set_text_lhs(w, true);
    y_at++;
  } else {
    TRACE_NO_INDENT();
    auto   w = wid_new_square_button(g, parent, "level");
    spoint tl(x_at, y_at);
    spoint br(width - 1, y_at);
    wid_set_color(w, WID_COLOR_TEXT_FG, WHITE);
    wid_set_pos(w, tl, br);
    wid_set_text(w, " You can re-enter here");
    wid_set_style(w, UI_WID_STYLE_NORMAL);
    wid_set_shape_none(w);
    wid_set_text_lhs(w, true);
    y_at++;
  }

  if (level_over->player_completed_level_via_exit) {
    TRACE_NO_INDENT();
    auto   w = wid_new_square_button(g, parent, "level");
    spoint tl(x_at, y_at);
    spoint br(width - 1, y_at);
    wid_set_color(w, WID_COLOR_TEXT_FG, WHITE);
    wid_set_pos(w, tl, br);
    wid_set_text(w, " You completed this level");
    wid_set_style(w, UI_WID_STYLE_NORMAL);
    wid_set_shape_none(w);
    wid_set_text_lhs(w, true);
    y_at++;
  } else if (level_over->player_fell_out_of_level) {
    TRACE_NO_INDENT();
    auto   w = wid_new_square_button(g, parent, "level");
    spoint tl(x_at, y_at);
    spoint br(width - 1, y_at);
    wid_set_color(w, WID_COLOR_TEXT_FG, WHITE);
    wid_set_pos(w, tl, br);
    wid_set_text(w, " You fell out of this level");
    wid_set_style(w, UI_WID_STYLE_NORMAL);
    wid_set_shape_none(w);
    wid_set_text_lhs(w, true);
    y_at++;
  }

  y_at++;

  {
    TRACE_NO_INDENT();
    auto   w = wid_new_square_button(g, parent, "contents");
    spoint tl(x_at, y_at);
    spoint br(width - 1, y_at);
    wid_set_color(w, WID_COLOR_TEXT_FG, GREEN);
    wid_set_pos(w, tl, br);
    wid_set_text(w, "Contents:");
    wid_set_style(w, UI_WID_STYLE_NORMAL);
    wid_set_shape_none(w);
    wid_set_text_lhs(w, true);
    y_at++;
  }

  y_at = level_select_show_sorted_values(g, v, level_over, parent, mobs, "Mobs", width, x_at, y_at);
  y_at = level_select_show_sorted_values(g, v, level_over, parent, monsts, "Monsters", width, x_at, y_at);
  y_at = level_select_show_sorted_values(g, v, level_over, parent, treasure, "Loot", width, x_at, y_at);
}

//
// If in level select mode, update what we're hovering over
//
void level_select_rightbar_needs_update(Gamep g, Levelsp v, Levelp l)
{
  TRACE_NO_INDENT();

  if (l->level_num != LEVEL_SELECT_ID) {
    return;
  }

  FOR_ALL_THINGS_AT(g, v, l, it, v->cursor_at)
  {
    int x  = (v->cursor_at.x - 1) / LEVEL_SCALE;
    int y  = (v->cursor_at.y - 1) / LEVEL_SCALE;
    int dx = (v->cursor_at.x - 1) % LEVEL_SCALE;
    int dy = (v->cursor_at.y - 1) % LEVEL_SCALE;

    if (! dx && ! dy) {
      LevelSelect *s = &v->level_select;
      Levelp       level_over;
      if (s->data[ x ][ y ].is_set) {
        level_over = game_level_get(g, v, s->data[ x ][ y ].level_num);
      } else {
        level_over = nullptr;
      }

      if (level_over) {
        game_request_to_remake_ui_set(g);
      }
    }
  }
}

//
// If in level select mode, enter the chosen level
//
void level_select_user_chose_a_level(Gamep g, Levelsp v, Levelp l)
{
  TRACE_NO_INDENT();

  auto   player       = thing_player(g);
  Levelp player_level = nullptr;
  if (player) {
    player_level = game_level_get(g, v, player->level_num);
  }

  if (l->level_num != LEVEL_SELECT_ID) {
    return;
  }

  FOR_ALL_THINGS_AT(g, v, l, it, v->cursor_at)
  {
    int          x  = (v->cursor_at.x - 1) / LEVEL_SCALE;
    int          y  = (v->cursor_at.y - 1) / LEVEL_SCALE;
    int          dx = (v->cursor_at.x - 1) % LEVEL_SCALE;
    int          dy = (v->cursor_at.y - 1) % LEVEL_SCALE;
    LevelSelect *s  = &v->level_select;
    Levelp       level_over;
    if (s->data[ x ][ y ].is_set) {
      level_over = game_level_get(g, v, s->data[ x ][ y ].level_num);
    } else {
      level_over = nullptr;
    }

    if (! dx && ! dy && level_over) {
      //
      // We're hovering over a level and have pressed the mouse
      //
      Levelp new_level = nullptr;

      //
      // Switch to the chosen level if possible; allow going back to the old level to clean up if needed
      //
      if ((level_over == player_level) || level_over->next_level) {
        new_level = level_change(g, v, level_over->level_num);
      } else {
        TOPCON("You cannot enter this level. Yet. Choose a flashing level.");
      }

      //
      // Move the player also
      //
      if (new_level) {
        thing_level_warp_to_entrance(g, v, new_level, thing_player(g));
        level_scroll_warp_to_focus(g, v, l);

        //
        // Disable load and save buttons
        //
        wid_actionbar_fini(g);
        wid_actionbar_init(g);
      }

      return;
    }
  }
}

void level_select_test(Gamep g)
{
  TRACE_NO_INDENT();

  auto v = levels_memory_alloc(g);
  game_levels_set(g, v);
  LevelSelect *s = &v->level_select;

  level_select_create(g, v, s);
  level_select_dump(g, v, s);
  level_select_count_levels(g, v, s);
}
