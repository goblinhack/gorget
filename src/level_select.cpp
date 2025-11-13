//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_charmap.hpp"
#include "my_dice_rolls.hpp"
#include "my_game.hpp"
#include "my_globals.hpp"
#include "my_level.hpp"
#include "my_main.hpp"
#include "my_random.hpp"
#include "my_sprintf.hpp"
#include "my_ui.hpp"
#include "my_wids.hpp"

static spoint car_to_iso(spoint car)
{
  spoint iso;
  iso.y = car.x + car.y;
  iso.x = car.y - car.x;

  return iso;
}

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
// If in level select mode, enter the chosen level
//
Levelp level_select_get_level_at_tile_coords(Gamep g, Levelsp v, spoint p)
{
  TRACE_NO_INDENT();

  auto   level_select = game_level_get(g, v, LEVEL_SELECT_ID);
  Levelp level_over   = nullptr;

  auto tp_is_level_not_visited = tp_random(is_level_not_visited);
  auto tp_is_level_curr        = tp_random(is_level_curr);
  auto tp_is_level_final       = tp_random(is_level_final);
  auto tp_is_level_visited     = tp_random(is_level_visited);
  auto tp_is_level_next        = tp_random(is_level_next);

  FOR_ALL_THINGS_AT(g, v, level_select, t, v->cursor_at)
  {
    auto tp = thing_tp(t);

    if ((tp == tp_is_level_not_visited) || (tp == tp_is_level_curr) || (tp == tp_is_level_final)
        || (tp == tp_is_level_visited) || (tp == tp_is_level_next)) {
      auto level_num_over = v->level_select.tile_to_level[ t->at.x ][ t->at.y ];
      level_over          = game_level_get(g, v, level_num_over);
      break;
    }
  }

  return level_over;
}

//
// Given a point in the level select grid, return the corresponding level,
// if one exists there.
//
static Levelp level_select_get_level_from_grid_coords(Gamep g, Levelsp v, spoint p)
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

    auto cand = level_select_get_level_from_grid_coords(g, v, p);
    if (cand && (cand != l)) {
      return cand;
    }
  }

  //
  // Nothing to fall onto. Try a random level.
  //
  tries = 0;
  while (tries++ < LEVELS_DOWN * LEVELS_ACROSS * 2) {
    spoint random_p(pcg_random_range(0, LEVELS_ACROSS), pcg_random_range(0, LEVELS_DOWN));

    auto cand = level_select_get_level_from_grid_coords(g, v, random_p);
    if (cand && (cand != l)) {
      return cand;
    }
  }

  //
  // Some tests have only 1 level
  //
  if (! g_opt_tests) {
    DIE("failed to find a next level down");
  }

  return nullptr;
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

  IF_NODEBUG { return; }

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

        if (! l->is_initialized_level) {
          DIE("trying to use a level that is not initialized, %u", n);
        }

        auto c             = &s->data[ x ][ y ];
        l->level_select_at = spoint(x, y);

        c->level_num = l->level_num;
        if ((x == LEVELS_ACROSS - 1) && (y == LEVELS_DOWN - 1)) {
          c->final_level = true;
        }

        n++;
      }
    }
  }
}

//
// Return the level
//
LevelSelectCell *level_select_get(Gamep g, Levelsp v, spoint p)
{
  TRACE_NO_INDENT();

  LevelSelect *s = &v->level_select;
  if (! s) {
    ERR("null level select");
    return nullptr;
  }

  if (level_select_is_oob(p)) {
    ERR("level select out of range");
    return nullptr;
  }

  return &s->data[ p.x ][ p.y ];
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
  LOG("Level select map");
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

  spoint map_offset(MAP_WIDTH / 2, 1);

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
      l->player_can_enter_this_level_next = false;

      //
      // If not visited, is it a next level for the current level?
      //
      if (player_level && (player_level->player_completed_level_via_exit || player_level->player_fell_out_of_level)
          && (tp == tp_is_level_not_visited)) {
        if (y > 0) {
          LevelSelectCell *o = &s->data[ x ][ y - 1 ];
          if (o && o->is_set && (o->level_num == player_level->level_num)) {
            tp                                  = tp_is_level_next;
            l->player_can_enter_this_level_next = true;
          }
        }
        if (x > 0) {
          LevelSelectCell *o = &s->data[ x - 1 ][ y ];
          if (o && o->is_set && (o->level_num == player_level->level_num)) {
            tp                                  = tp_is_level_next;
            l->player_can_enter_this_level_next = true;
          }
        }

        if (y < LEVELS_DOWN - 1) {
          LevelSelectCell *o = &s->data[ x ][ y + 1 ];
          if (o && o->is_set && (o->level_num == player_level->level_num)) {
            tp                                  = tp_is_level_next;
            l->player_can_enter_this_level_next = true;
          }
        }
        if (x < LEVELS_ACROSS - 1) {
          LevelSelectCell *o = &s->data[ x + 1 ][ y ];
          if (o && o->is_set && (o->level_num == player_level->level_num)) {
            tp                                  = tp_is_level_next;
            l->player_can_enter_this_level_next = true;
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
            tp                                  = tp_is_level_next;
            l->player_can_enter_this_level_next = true;
          }
        }
        if (x > 0) {
          LevelSelectCell *o = &s->data[ x - 1 ][ y ];
          if (o && o->is_set && (o->level_num == player_level->level_num)) {
            tp                                  = tp_is_level_next;
            l->player_can_enter_this_level_next = true;
          }
        }

        if (y < LEVELS_DOWN - 1) {
          LevelSelectCell *o = &s->data[ x ][ y + 1 ];
          if (o && o->is_set && (o->level_num == player_level->level_num)) {
            tp                                  = tp_is_level_next;
            l->player_can_enter_this_level_next = true;
          }
        }
        if (x < LEVELS_ACROSS - 1) {
          LevelSelectCell *o = &s->data[ x + 1 ][ y ];
          if (o && o->is_set && (o->level_num == player_level->level_num)) {
            tp                                  = tp_is_level_next;
            l->player_can_enter_this_level_next = true;
          }
        }
      }

      if (g_opt_level_select_menu) {
        l->player_can_enter_this_level_next = true;
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
        spoint at(x * 2, y * 2);
        at = car_to_iso(at);
        at += map_offset;
        if (is_oob(at)) {
          continue;
        }

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
        if (g_opt_level_select_menu && (tp == tp_is_level_not_visited)) {
          tp = tp_is_level_next;
        }

        thing_spawn(g, v, level_select, tp, at);
        v->level_select.tile_to_level[ at.x ][ at.y ] = l->level_num;
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

      spoint at(x * 2 + 1, y * 2);
      at = car_to_iso(at);
      at += map_offset;
      if (is_oob(at)) {
        continue;
      }

      level_select->debug[ at.x ][ at.y ] = '-';

      thing_spawn(g, v, level_select, tp_is_level_across, at);
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

      spoint at(x * 2, y * 2 + 1);
      at = car_to_iso(at);
      at += map_offset;
      if (is_oob(at)) {
        continue;
      }

      level_select->debug[ at.x ][ at.y ] = '|';

      thing_spawn(g, v, level_select, tp_is_level_down, at);
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

  l->is_initialized_level = true;
  l->level_num            = level_num;
  l->info.seed_num        = game_seed_num_get(g);

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

  if (! l || ! l->is_initialized_level) {
    return;
  }

  LevelSelect *s = &v->level_select;
  memset(s, 0, SIZEOF(*s));
}

//
// Show a sorted list of vales
//
static void level_select_show_sorted_values(Gamep g, Levelsp v, Levelp l, WidPopup *parent,
                                            std::map< std::string, int > &map_in, std::string map_name)
{
  TRACE_NO_INDENT();

  if (! map_in.size()) {
    return;
  }

  {
    auto s1 = string_sprintf(" %s:", map_name.c_str());
    parent->log(g, UI_INFO_FMT_STR + std::string(s1) + UI_RESET_FMT, TEXT_FORMAT_LHS);
  }

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
      auto        tp   = tp_find_mand(highest.c_str());
      std::string name = tp_short_name(tp);

      auto s2 = string_sprintf("  %u x %%tp=%s$ %s", map_in[ highest ], highest.c_str(), name.c_str());
      parent->log(g, s2, TEXT_FORMAT_LHS);
    }

    map_in.erase(highest);
  }
}

//
// If in level select mode, update what we're hovering over
//
void level_select_rightbar_show_contents(Gamep g, Levelsp v, Levelp l, WidPopup *parent)
{
  TRACE_NO_INDENT();

  if (! level_is_level_select(g, v, l)) {
    return;
  }

  Levelp level_over = level_select_get_level_at_tile_coords(g, v, v->cursor_at);
  if (! level_over) {
    return;
  }

  parent->log_empty_line(g);

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

  auto tmp = string_sprintf("Level %u", level_over->level_num + 1);
  parent->log(g, UI_INFO_FMT_STR + std::string(tmp) + UI_RESET_FMT);
  parent->log_empty_line(g);

  if (level_over->player_can_enter_this_level_next) {
    if (player_level->player_completed_level_via_exit) {
      parent->log(g, " You can enter here", TEXT_FORMAT_LHS);
    } else if (player_level->player_fell_out_of_level) {
      parent->log(g, " You can climb back here", TEXT_FORMAT_LHS);
    } else {
      parent->log(g, " You can go back here", TEXT_FORMAT_LHS);
    }
  } else if (level_over != player_level) {
    parent->log(g, " You cannot enter here", TEXT_FORMAT_LHS);
  } else {
    parent->log(g, " You can re-enter here", TEXT_FORMAT_LHS);
  }

  if (level_over->player_completed_level_via_exit) {
    parent->log(g, " You completed this level", TEXT_FORMAT_LHS);
  } else if (level_over->player_fell_out_of_level) {
    parent->log(g, " You fell out of this level", TEXT_FORMAT_LHS);
  }

  {
    parent->log_empty_line(g);
    parent->log(g, " Contents:", TEXT_FORMAT_LHS);
  }

  level_select_show_sorted_values(g, v, level_over, parent, mobs, "Mobs");
  level_select_show_sorted_values(g, v, level_over, parent, monsts, "Monsters");
  level_select_show_sorted_values(g, v, level_over, parent, treasure, "Loot");
}

//
// If in level select mode, update what we're hovering over
//
void level_select_mouse_motion(Gamep g, Levelsp v, Levelp l)
{
  TRACE_NO_INDENT();

  if (! level_is_level_select(g, v, l)) {
    return;
  }

  Levelp level_over = level_select_get_level_at_tile_coords(g, v, v->cursor_at);
  if (! level_over) {
    return;
  }

  game_request_to_remake_ui_set(g);

  level_minimaps_update(g, v, level_over);
}

//
// If in level select mode, enter the chosen level
//
void level_select_mouse_down(Gamep g, Levelsp v, Levelp l)
{
  TRACE_NO_INDENT();

  if (! level_is_level_select(g, v, l)) {
    return;
  }

  Levelp level_over = level_select_get_level_at_tile_coords(g, v, v->cursor_at);
  if (! level_over) {
    return;
  }

  auto   player       = thing_player(g);
  Levelp player_level = nullptr;
  if (player) {
    player_level = game_level_get(g, v, player->level_num);
  }

  //
  // We're hovering over a level and have pressed the mouse
  //
  Levelp new_level = nullptr;

  //
  // Switch to the chosen level if possible; allow going back to the old level to clean up if needed
  //
  if ((level_over == player_level) || level_over->player_can_enter_this_level_next) {
    new_level = level_change(g, v, level_over->level_num);
  } else {
    TOPCON("You cannot enter this level yet. Choose an open door.");
  }

  //
  // Move the player also
  //
  if (new_level) {
    if (new_level->player_completed_level_via_exit) {
      thing_level_warp_to_exit(g, v, new_level, player);
    } else {
      thing_level_warp_to_entrance(g, v, new_level, player);
    }
    level_scroll_warp_to_focus(g, v, l);

    //
    // Disable load and save buttons
    //
    game_request_to_remake_ui_set(g);
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
