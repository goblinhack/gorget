//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_cave.hpp"
#include "my_charmap.hpp"
#include "my_dice.hpp"
#include "my_game.hpp"
#include "my_level.hpp"
#include "my_main.hpp"
#include "my_point.hpp"
#include "my_ptrcheck.hpp"
#include "my_random.hpp"

#include <stdlib.h>

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
static void level_select_assign_levels(Gamep g, Levelsp v, LevelSelect *s)
{
  TRACE_NO_INDENT();

  auto n = 0;

  for (int y = 0; y < LEVELS_DOWN; y++) {
    for (int x = 0; x < LEVELS_ACROSS; x++) {
      if (s->data[ x ][ y ].is_set) {
        auto l = game_level_get(g, v, n);
        if (! l) {
          DIE("ran out of levels to assign to grid, %u", n);
        }

        s->data[ x ][ y ].level = l;
        l->level_select_at      = point(x, y);

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

static void snake_dive(Gamep g, Levelsp v, LevelSelect *s, point at, int dive_chance)
{
  TRACE_NO_INDENT();

  point end(LEVELS_ACROSS - 1, LEVELS_DOWN - 1);

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
      snake_dive(g, v, s, point(x, y), dive_chance);

      return;
    }
  }
}

//
// Create a Thing for each level
//
static void level_select_map_set(Gamep g, Levelsp v, LevelSelect *s)
{
  TRACE_NO_INDENT();

  auto level_num    = LEVEL_SELECT_ID;
  auto level_select = game_level_get(g, v, level_num);
  auto player       = thing_player(g);

  Levelp player_level = nullptr;
  if (player) {
    player_level = game_level_get(g, v, player->level_num);
  }

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

      Levelp l = c->level;
      if (! l) {
        ERR("missing level in select map");
        continue;
      }

      //
      // Default
      //
      Tpp tp = tp = tp_is_level_not_visited;

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

      //
      // Completed levels
      //
      if (l->completed) {
        tp = tp_is_level_visited;
      }

      //
      // If not visited, is it a next level for the current level?
      //
      if (player_level && (tp == tp_is_level_not_visited)) {
        if (y < LEVELS_DOWN - 1) {
          LevelSelectCell *o = &s->data[ x ][ y + 1 ];
          if (o->level == player_level) {
            tp = tp_is_level_next;
          }
        }
        if (x < LEVELS_ACROSS - 1) {
          LevelSelectCell *o = &s->data[ x + 1 ][ y ];
          if (o->level == player_level) {
            tp = tp_is_level_next;
          }
        }
        if (y > 0) {
          LevelSelectCell *o = &s->data[ x ][ y - 1 ];
          if (o->level == player_level) {
            tp = tp_is_level_next;
          }
        }
        if (x < 0) {
          LevelSelectCell *o = &s->data[ x - 1 ][ y ];
          if (o->level == player_level) {
            tp = tp_is_level_next;
          }
        }
      }

      //
      // Final level
      //
      if ((x == LEVELS_ACROSS - 1) && (y == LEVELS_DOWN - 1)) {
        tp = tp_is_level_final;
      }

      if (tp) {
        point at(x * LEVEL_SCALE + 1, y * LEVEL_SCALE + 1);
        auto  t = thing_init(g, v, level_select, tp, at);
        if (t) {
          thing_push(g, v, level_select, t);
        }
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

      {
        point at(x * LEVEL_SCALE + 2, y * LEVEL_SCALE + 1);
        auto  t = thing_init(g, v, level_select, tp_is_level_across, at);
        if (t) {
          thing_push(g, v, level_select, t);
        }
      }

      {
        point at(x * LEVEL_SCALE + 3, y * LEVEL_SCALE + 1);
        auto  t = thing_init(g, v, level_select, tp_is_level_across, at);
        if (t) {
          thing_push(g, v, level_select, t);
        }
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

      {
        point at(x * LEVEL_SCALE + 1, y * LEVEL_SCALE + 2);
        auto  t = thing_init(g, v, level_select, tp_is_level_down, at);
        if (t) {
          thing_push(g, v, level_select, t);
        }
      }

      {
        point at(x * LEVEL_SCALE + 1, y * LEVEL_SCALE + 3);
        auto  t = thing_init(g, v, level_select, tp_is_level_down, at);
        if (t) {
          thing_push(g, v, level_select, t);
        }
      }
    }
  }
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

  s->is_populated = true;

  //
  // Use a consistent seed
  //
  uint32_t seed_num = game_seed_num_get(g);
  pcg_srand(seed_num);

  snake_dive(g, v, s, point(0, 0), 90);
  snake_dive(g, v, s, 90);
  snake_dive(g, v, s, point(0, 0), 50);
  snake_dive(g, v, s, point(0, 0), 30);
  snake_dive(g, v, s, point(0, 0), 30);
  snake_dive(g, v, s, point(0, 0), 30);
  snake_dive(g, v, s, 30);
}

//
// Create the things that are used to represent levels
//
static void level_select_create_things(Gamep g, Levelsp v, LevelSelect *s)
{
  TRACE_NO_INDENT();

  auto level_num = LEVEL_SELECT_ID;
  auto l         = game_level_get(g, v, level_num);

  //
  // Level select is called upon each level exit, so need to start with a clean slate
  //
  level_destroy(g, v, l);

  l->initialized = true;
  l->level_num   = level_num;

  level_select_map_set(g, v, s);
}

//
// Create the special level used to walk other levels
//
void level_select_create_levels(Gamep g)
{
  LOG("Level select generate");
  TRACE_AND_INDENT();

  auto v = levels_memory_alloc(g);
  game_levels_set(g, v);
  LevelSelect *s = &v->level_select;

  level_select_create(g, v, s);
  level_select_dump(g, v, s);
  level_select_count_levels(g, v, s);
  level_select_assign_levels(g, v, s);
  level_select_create_things(g, v, s);
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
  memset(s, 0, sizeof(*s));
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
