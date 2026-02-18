//
// Copyright goblinhack@gmail.com
//

#include <algorithm>

#include "my_callstack.hpp"
#include "my_charmap.hpp"
#include "my_dice_rolls.hpp"
#include "my_game.hpp"
#include "my_globals.hpp"
#include "my_level.hpp"
#include "my_main.hpp"
#include "my_random.hpp"
#include "my_sprintf.hpp"
#include "my_thing_inlines.hpp"
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
  if (p.x >= LEVEL_ACROSS) {
    return true;
  }
  if (p.y >= LEVEL_DOWN) {
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
  if (x >= LEVEL_ACROSS) {
    return true;
  }
  if (y >= LEVEL_DOWN) {
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

  auto  *level_select = game_level_get(g, v, LEVEL_SELECT_ID);
  Levelp level_over   = nullptr;

  auto *tp_is_level_not_visited_icon = tp_first(is_level_not_visited_icon);
  auto *tp_is_level_curr             = tp_first(is_level_curr);
  auto *tp_is_level_final_icon       = tp_first(is_level_final_icon);
  auto *tp_is_level_visited_icon     = tp_first(is_level_visited_icon);
  auto *tp_is_level_next_icon        = tp_first(is_level_next_icon);

  FOR_ALL_THINGS_AT(g, v, level_select, t, v->cursor_at)
  {
    auto *tp = thing_tp(t);

    if ((tp == tp_is_level_not_visited_icon) || (tp == tp_is_level_curr) || (tp == tp_is_level_final_icon)
        || (tp == tp_is_level_visited_icon) || (tp == tp_is_level_next_icon)) {
      auto at             = thing_at(t);
      auto level_num_over = v->level_select.tile_to_level[ at.x ][ at.y ];
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

  if (v == nullptr) {
    return nullptr;
  }

  if (level_select_is_oob(p)) {
    return nullptr;
  }

  auto *s = &v->level_select.data[ p.x ][ p.y ];
  if (s->is_set == 0U) {
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

  if (l->level_num_next_set) {
    return game_level_get(g, v, l->level_num_next);
  }

  return nullptr;
}

//
// Attempt to find the next level for this thing to fall into
//
Levelp level_select_calculate_next_level_down(Gamep g, Levelsp v, Levelp l, bool redo)
{
  TRACE_NO_INDENT();

  LevelSelect *s = &v->level_select;
  if (s == nullptr) {
    CROAK("missing level select pointer");
  }

  auto   p         = l->level_select_at;
  Levelp level_out = nullptr;
  int    tries     = 0;

  //
  // Tests need to re-reun this each time a new level is added.
  //
  if (! redo) {
    if (l->level_num_next_set) {
      return game_level_get(g, v, l->level_num_next);
    }
  }

  if (__unused__) {
    CON("-");
    CON("level %d at %u,%u", l->level_num, l->level_select_at.x, l->level_select_at.y);
  }

  //
  // Try diagonally left first
  //
  while (tries++ < LEVEL_ACROSS * 2) {
    p.y++;
    if ((p.x >= LEVEL_DOWN) || (p.y >= LEVEL_ACROSS)) {
      //
      // Failed. Try the other direction.
      //
      p = l->level_select_at;
      break;
    }

    if (__unused__) {
      CON("level %d -> next (look diagonally left at %u,%u)", l->level_num, p.x, p.y);
    }

    auto *cand = level_select_get_level_from_grid_coords(g, v, p);
    if ((cand != nullptr) && (cand != l)) {
      level_out = cand;
      goto got_level;
    }
  }

  //
  // Try diagonally right
  //
  while (tries++ < LEVEL_ACROSS * 2) {
    p.x++;
    p.y++;
    if ((p.x >= LEVEL_DOWN) || (p.y >= LEVEL_ACROSS)) {
      //
      // Failed. Try the other direction.
      //
      p = l->level_select_at;
      break;
    }

    if (__unused__) {
      CON("level %d -> next (look diagonally right at %u,%u)", l->level_num, p.x, p.y);
    }

    auto *cand = level_select_get_level_from_grid_coords(g, v, p);
    if ((cand != nullptr) && (cand != l)) {
      level_out = cand;
      goto got_level;
    }
  }

  //
  // Get the next sequential level, in terms of level number. This is used for tests.
  //
  for (int y = 0; y < LEVEL_DOWN; y++) {
    for (auto &x : s->data) {
      LevelSelectCell *c = &x[ y ];
      if (c->is_set == 0U) {
        continue;
      }

      auto *cand = game_level_get(g, v, c->level_num);
      if (cand == nullptr) {
        continue;
      }

      if (__unused__) {
        CON("level %d -> next %d (sequential)", l->level_num, cand->level_num);
      }

      if (cand->level_num == l->level_num + 1) {
        level_out = cand;
        goto got_level;
      }
    }
  }

  if (l->level_num == v->level_count) {
    auto *cand = game_level_get(g, v, 0);
    if (cand != nullptr) {
      if (__unused__) {
        CON("level %d -> next (first level)", l->level_num);
      }
      level_out = cand;
      goto got_level;
    }
  }

  //
  // Nothing to fall onto. Try a random level.
  //
  tries = 0;
  while (tries++ < LEVEL_DOWN * LEVEL_ACROSS * 2) {
    if (__unused__) {
      CON("level %d -> next (random)", l->level_num);
    }
    spoint random_p(pcg_random_range(0, LEVEL_ACROSS), pcg_random_range(0, LEVEL_DOWN));

    auto *cand = level_select_get_level_from_grid_coords(g, v, random_p);
    if ((cand != nullptr) && (cand != l)) {
      level_out = cand;
      goto got_level;
    }
  }

  //
  // Some tests have only 1 level
  //
  if (! g_opt_tests) {
    CROAK("failed to find a next level down");
  }

got_level:
  if (level_out != nullptr) {
    l->level_num_next_set = true;
    l->level_num_next     = level_out->level_num;
    if (__unused__) {
      CON("level %d -> next %d at %u,%u", l->level_num, l->level_num_next, l->level_select_at.x,
          l->level_select_at.y);
    }
  }

  return level_out;
}

//
// This is the thing that is used to represent the current level. We focus the mouse zoom on this.
//
Thingp thing_level_select(Gamep g)
{
  TRACE_NO_INDENT();

  auto *v = game_levels_get(g);
  if (v == nullptr) {
    return nullptr;
  }

  if (v->level_select_id == 0U) {
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

  for (int y = 0; y < LEVEL_DOWN; y++) {
    std::string out;
    for (auto &x : s->data) {
      out += (x[ y ].is_set != 0U) ? CHARMAP_FLOOR : CHARMAP_EMPTY;
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

  for (int y = 0; y < LEVEL_DOWN; y++) {
    for (int x = 0; x < LEVEL_ACROSS; x++) {
      if (s->data[ x ][ y ].is_set != 0U) {
        auto *l = game_level_get(g, v, n);
        if (l == nullptr) {
          CROAK("ran out of levels to assign to grid, %u", n);
        }

        if (! l->is_initialized) {
          CROAK("trying to use a level that is not initialized, %u", n);
        }

        auto *c            = &s->data[ x ][ y ];
        l->level_select_at = spoint(x, y);

        c->level_num = l->level_num;
        if ((x == LEVEL_ACROSS - 1) && (y == LEVEL_DOWN - 1)) {
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
  if (s == nullptr) {
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

  for (int y = 0; y < LEVEL_DOWN; y++) {
    for (auto &x : s->data) {
      if (x[ y ].is_set != 0U) {
        s->level_count++;
      }
    }
  }
  return s->level_count;
}

static void snake_dive(Gamep g, Levelsp v, LevelSelect *s, spoint at, int dive_chance)
{
  TRACE_NO_INDENT();

  spoint end(LEVEL_ACROSS - 1, LEVEL_DOWN - 1);

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

    s->data[ at.x ][ at.y ].is_set = 1U;

    if (chance < dive_chance) {
      at.y++;
    } else {
      at.x++;
    }

    at.x = std::min< int >(at.x, LEVEL_ACROSS - 1);
    at.y = std::min< int >(at.y, LEVEL_DOWN - 1);
  }

  s->data[ at.x ][ at.y ].is_set = 1U;
}

static void snake_dive(Gamep g, Levelsp v, LevelSelect *s, int dive_chance)
{
  TRACE_NO_INDENT();

  while (true) {
    auto x = pcg_random_range(0, LEVEL_ACROSS);
    auto y = pcg_random_range(0, LEVEL_DOWN);

    if (s->data[ x ][ y ].is_set != 0U) {
      snake_dive(g, v, s, spoint(x, y), dive_chance);

      return;
    }
  }
}

//
// Create a Thing for each level
//
[[nodiscard]] static bool level_select_map_set(Gamep g, Levelsp v)
{
  LOG("Level select map");
  TRACE_NO_INDENT();

  LevelSelect *s            = &v->level_select;
  auto         level_num    = LEVEL_SELECT_ID;
  auto        *level_select = game_level_get(g, v, level_num);

  auto  *player       = thing_player(g);
  Levelp player_level = thing_player_level(g);

  //
  // Clean up all previous things
  //
  FOR_ALL_THINGS_ON_LEVEL(g, v, level_select, t)
  {
    // newline
    thing_fini(g, v, level_select, t);
  }

  memset(level_select->debug, ' ', SIZEOF(level_select->debug));

  auto *tp_is_level_not_visited_icon = tp_first(is_level_not_visited_icon);
  auto *tp_is_level_curr             = tp_first(is_level_curr);
  auto *tp_is_level_across_icon      = tp_first(is_level_across_icon);
  auto *tp_is_level_down_icon        = tp_first(is_level_down_icon);
  auto *tp_is_level_final_icon       = tp_first(is_level_final_icon);
  auto *tp_is_level_visited_icon     = tp_first(is_level_visited_icon);
  auto *tp_is_level_next_icon        = tp_first(is_level_next_icon);

  spoint map_offset(MAP_WIDTH / 2, 1);

  for (auto y = 0; y < LEVEL_DOWN; y++) {
    for (auto x = 0; x < LEVEL_ACROSS; x++) {
      LevelSelectCell *c = &s->data[ x ][ y ];
      if (c->is_set == 0U) {
        continue;
      }

      auto *l = game_level_get(g, v, c->level_num);
      if (l == nullptr) {
        ERR("missing level in select map");
        continue;
      }

      //
      // Default
      //
      Tpp tp = tp_is_level_not_visited_icon;

      //
      // Can we enter this level?
      //
      l->player_can_enter_this_level_next = false;

      //
      // If not visited, is it a next level for the current level?
      //
      if ((player_level != nullptr)
          && (player_level->player_completed_level_via_exit || player_level->player_fell_out_of_level)) {
        if (y > 0) {
          LevelSelectCell *o = &s->data[ x ][ y - 1 ]; // limit to adjacent levels
          if ((o != nullptr) && (o->is_set != 0U) && (o->level_num == player_level->level_num)) {
            tp                                  = tp_is_level_next_icon;
            l->player_can_enter_this_level_next = true;
          }
        }
        if (x > 0) {
          LevelSelectCell *o = &s->data[ x - 1 ][ y ]; // limit to adjacent levels
          if ((o != nullptr) && (o->is_set != 0U) && (o->level_num == player_level->level_num)) {
            tp                                  = tp_is_level_next_icon;
            l->player_can_enter_this_level_next = true;
          }
        }

        if (y < LEVEL_DOWN - 1) {
          LevelSelectCell *o = &s->data[ x ][ y + 1 ]; // limit to adjacent levels
          if ((o != nullptr) && (o->is_set != 0U) && (o->level_num == player_level->level_num)) {
            tp                                  = tp_is_level_next_icon;
            l->player_can_enter_this_level_next = true;
          }
        }
        if (x < LEVEL_ACROSS - 1) {
          LevelSelectCell *o = &s->data[ x + 1 ][ y ]; // limit to adjacent levels
          if ((o != nullptr) && (o->is_set != 0U) && (o->level_num == player_level->level_num)) {
            tp                                  = tp_is_level_next_icon;
            l->player_can_enter_this_level_next = true;
          }
        }
      }

      //
      // Allow backwards moves to completed levels
      //
      if ((player_level != nullptr) && (l->player_completed_level_via_exit || l->player_fell_out_of_level)) {
        if (y > 0) {
          LevelSelectCell *o = &s->data[ x ][ y - 1 ]; // limit to adjacent levels
          if ((o != nullptr) && (o->is_set != 0U) && (o->level_num == player_level->level_num)) {
            tp                                  = tp_is_level_next_icon;
            l->player_can_enter_this_level_next = true;
          }
        }
        if (x > 0) {
          LevelSelectCell *o = &s->data[ x - 1 ][ y ]; // limit to adjacent levels
          if ((o != nullptr) && (o->is_set != 0U) && (o->level_num == player_level->level_num)) {
            tp                                  = tp_is_level_next_icon;
            l->player_can_enter_this_level_next = true;
          }
        }

        if (y < LEVEL_DOWN - 1) {
          LevelSelectCell *o = &s->data[ x ][ y + 1 ]; // limit to adjacent levels
          if ((o != nullptr) && (o->is_set != 0U) && (o->level_num == player_level->level_num)) {
            tp                                  = tp_is_level_next_icon;
            l->player_can_enter_this_level_next = true;
          }
        }
        if (x < LEVEL_ACROSS - 1) {
          LevelSelectCell *o = &s->data[ x + 1 ][ y ]; // limit to adjacent levels
          if ((o != nullptr) && (o->is_set != 0U) && (o->level_num == player_level->level_num)) {
            tp                                  = tp_is_level_next_icon;
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
      if ((x == LEVEL_ACROSS - 1) && (y == LEVEL_DOWN - 1)) {
        tp = tp_is_level_final_icon;
      }

      //
      // Completed levels
      //
      if (l->player_completed_level_via_exit || l->player_fell_out_of_level) {
        tp = tp_is_level_visited_icon;
      }

      if (player != nullptr) {
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

      if (tp != nullptr) {
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

        if (tp == tp_is_level_not_visited_icon) {
          level_select->debug[ at.x ][ at.y ] = '?';
        }
        if (tp == tp_is_level_curr) {
          level_select->debug[ at.x ][ at.y ] = '@';
        }
        if (tp == tp_is_level_final_icon) {
          level_select->debug[ at.x ][ at.y ] = 'E';
        }
        if (tp == tp_is_level_next_icon) {
          level_select->debug[ at.x ][ at.y ] = '?';
        }

        //
        // Show all levels as next when debugging
        //
        if (g_opt_level_select_menu && (tp == tp_is_level_not_visited_icon)) {
          tp = tp_is_level_next_icon;
        }

        if (thing_spawn(g, v, level_select, tp, at) == nullptr) {
          return false;
        }
        v->level_select.tile_to_level[ at.x ][ at.y ] = l->level_num;
      }
    }
  }

  //
  // Add horizontal level connector
  //
  for (auto y = 0; y < LEVEL_DOWN; y++) {
    for (auto x = 0; x < LEVEL_ACROSS - 1; x++) {
      LevelSelectCell *c = &s->data[ x ][ y ];
      if (c->is_set == 0U) {
        continue;
      }
      LevelSelectCell *n = &s->data[ x + 1 ][ y ];
      if (n->is_set == 0U) {
        continue;
      }

      spoint at((x * 2) + 1, y * 2);
      at = car_to_iso(at);
      at += map_offset;
      if (is_oob(at)) {
        continue;
      }

      level_select->debug[ at.x ][ at.y ] = '-';

      if (thing_spawn(g, v, level_select, tp_is_level_across_icon, at) == nullptr) {
        return false;
      }
    }
  }

  //
  // Add vertical level connector
  //
  for (auto y = 0; y < LEVEL_DOWN - 1; y++) {
    for (auto x = 0; x < LEVEL_ACROSS; x++) {
      LevelSelectCell *c = &s->data[ x ][ y ];
      if (c->is_set == 0U) {
        continue;
      }
      LevelSelectCell *n = &s->data[ x ][ y + 1 ];
      if (n->is_set == 0U) {
        continue;
      }

      spoint at(x * 2, (y * 2) + 1);
      at = car_to_iso(at);
      at += map_offset;
      if (is_oob(at)) {
        continue;
      }

      level_select->debug[ at.x ][ at.y ] = '|';

      if (thing_spawn(g, v, level_select, tp_is_level_down_icon, at) == nullptr) {
        return false;
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
      if (count == 0) {
        auto *tp_rock = tp_first(is_dirt);
        if (thing_spawn(g, v, level_select, tp_rock, at) == nullptr) {
          return false;
        }
      }
    }
  }

  //
  // Create joined up tiles (for the rocks)
  //
  level_assign_tiles(g, v, level_select);

  return true;
}

//
// Create the level grid
//
static void level_select_create(Gamep g, Levelsp v, LevelSelect *s)
{
  TRACE_NO_INDENT();

  if (s->is_populated != 0U) {
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

  s->is_populated = 1U;
}

//
// Create the things that are used to represent levels
//
void level_select_update_grid_tiles(Gamep g, Levelsp v)
{
  TRACE_NO_INDENT();

  auto  level_num = LEVEL_SELECT_ID;
  auto *l         = game_level_get(g, v, level_num);

  level_init(g, v, l, level_num);
  l->info.seed_num = game_seed_num_get(g);

  (void) level_select_map_set(g, v);
}

//
// Create the special level used to walk other levels
//
void level_select_grid_of_empty_levels(Gamep g)
{
  LOG("Level select generate");
  TRACE_AND_INDENT();

  auto *v = levels_memory_alloc(g);
  (void) game_levels_set(g, v);
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

  if ((l == nullptr) || ! l->is_initialized) {
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

  if (map_in.empty()) {
    return;
  }

  {
    auto s1 = string_sprintf(" %s:", map_name.c_str());
    parent->log(g, UI_INFO_FMT_STR + std::string(s1) + UI_RESET_FMT, TEXT_FORMAT_LHS);
  }

  while (static_cast< unsigned int >(! map_in.empty()) != 0U) {
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
      auto       *tp   = tp_find_mand(highest);
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
  if (level_over == nullptr) {
    return;
  }

  parent->log_empty_line(g);

  Levelp player_level = thing_player_level(g);

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

  level_minimaps_update(g, v, level_over);
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
  if (level_over == nullptr) {
    return;
  }

  game_request_to_remake_ui_set(g);
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
  if (level_over == nullptr) {
    return;
  }

  auto  *player       = thing_player(g);
  Levelp player_level = thing_player_level(g);

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
  if (new_level != nullptr) {
    if (new_level->player_completed_level_via_exit) {
      thing_level_warp_to_exit(g, v, new_level, player);
    } else if (new_level->player_fell_out_of_level) {
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

  auto *v = levels_memory_alloc(g);
  (void) game_levels_set(g, v);
  LevelSelect *s = &v->level_select;

  level_select_create(g, v, s);
  level_select_dump(g, v, s);
  level_select_count_levels(g, v, s);
}
