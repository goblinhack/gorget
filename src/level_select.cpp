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

class LevelSelect
{
private:
public:
  LevelSelect(void)
  {
    for (int y = 0; y < LEVELS_DOWN; y++) {
      for (int x = 0; x < LEVELS_ACROSS; x++) {
        data[ x ][ y ] = CHARMAP_EMPTY;
      }
    }
  }
  ~LevelSelect(void) {}

  //
  // Level tiles and grid info
  //
  char data[ LEVELS_ACROSS ][ LEVELS_DOWN ] = {};

  //
  // How many levels generated
  //
  int level_count;
};

//
// Dump a level
//
static void level_select_dump(Gamep g, LevelSelect *l)
{
  TRACE_NO_INDENT();

  LOG("LevelSelect, level count %d", l->level_count);

  for (int y = 0; y < LEVELS_DOWN; y++) {
    std::string(s);
    for (int x = 0; x < LEVELS_ACROSS; x++) {
      s += l->data[ x ][ y ];
    }
    LOG("%s", s.c_str());
  }
  LOG("-");
}

//
// Clear the levels
//
static void level_select_clear(Gamep g, LevelSelect *l)
{
  TRACE_NO_INDENT();

  memset(l->data, CHARMAP_EMPTY, sizeof(l->data));
}

//
// Count the levels created
//
static int level_select_count_levels(Gamep g, LevelSelect *l)
{
  TRACE_NO_INDENT();

  l->level_count = 0;

  for (int y = 0; y < LEVELS_DOWN; y++) {
    for (int x = 0; x < LEVELS_ACROSS; x++) {
      if (l->data[ x ][ y ] == CHARMAP_FLOOR) {
        l->level_count++;
      }
    }
  }
  return l->level_count;
}

static void snake_walk(Gamep g, LevelSelect *l, point at, int turn_chance, int count)
{
  TRACE_NO_INDENT();

  point dir(1, 0);
  point end(LEVELS_ACROSS - 1, LEVELS_DOWN - 1);

  while (count-- > 0) {
    //
    // Ensure we never try to create too many levels
    //
    // Keep one free for the select level
    //
    if (level_select_count_levels(g, l) >= MAX_LEVELS - 1) {
      return;
    }

    at += dir;

    if (at.x < 0) {
      at.x = 0;
    }
    if (at.y < 0) {
      at.y = 0;
    }
    if (at.x > LEVELS_ACROSS - 1) {
      at.x = LEVELS_ACROSS - 1;
    }
    if (at.y > LEVELS_DOWN - 1) {
      at.y = LEVELS_DOWN - 1;
    }

    l->data[ at.x ][ at.y ] = CHARMAP_FLOOR;

    auto chance = d100();
    if (chance < turn_chance) {
      if (dir == point(1, 0)) {
        dir = point(0, 1);
      } else if (dir == point(0, 1)) {
        dir = point(-1, 0);
      } else if (dir == point(-1, 0)) {
        dir = point(0, -1);
      } else if (dir == point(0, -1)) {
        dir = point(1, 0);
      }
    }
  }

  l->data[ at.x ][ at.y ] = CHARMAP_FLOOR;
}

static void snake_walk(Gamep g, LevelSelect *l, int turn_chance, int count)
{
  TRACE_NO_INDENT();

  while (true) {
    auto x = pcg_random_range(0, LEVELS_ACROSS);
    auto y = pcg_random_range(0, LEVELS_DOWN);

    if (l->data[ x ][ y ] == CHARMAP_FLOOR) {
      snake_walk(g, l, point(x, y), turn_chance, count);
      return;
    }
  }
}

static void snake_dive(Gamep g, LevelSelect *l, point at, int dive_chance)
{
  TRACE_NO_INDENT();

  point end(LEVELS_ACROSS - 1, LEVELS_DOWN - 1);

  while (at != end) {
    //
    // Ensure we never try to create too many levels
    //
    // Keep one free for the select level
    //
    if (level_select_count_levels(g, l) >= MAX_LEVELS - 1) {
      return;
    }

    auto chance = d100();

    l->data[ at.x ][ at.y ] = CHARMAP_FLOOR;

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

  l->data[ at.x ][ at.y ] = CHARMAP_FLOOR;
}

static void snake_dive(Gamep g, LevelSelect *l, int dive_chance)
{
  TRACE_NO_INDENT();

  while (true) {
    auto x = pcg_random_range(0, LEVELS_ACROSS);
    auto y = pcg_random_range(0, LEVELS_DOWN);

    if (l->data[ x ][ y ] == CHARMAP_FLOOR) {
      snake_dive(g, l, point(x, y), dive_chance);

      return;
    }
  }
}

//
// Convert the level gen output into a single string
//
static std::string level_select_string(Gamep g, class LevelSelect *l)
{
  TRACE_NO_INDENT();

  std::string out;

  for (int y = 0; y < LEVELS_DOWN; y++) {
    for (int x = 0; x < LEVELS_ACROSS; x++) {
      out += l->data[ x ][ y ];
    }
  }

  return out;
}

//
// Create a Thing for each level
//
static void level_select_map_set(Gamep g, Levelsp v, Levelp l, const char *in)
{
  TRACE_NO_INDENT();

  const auto row_len                              = LEVELS_ACROSS;
  auto       expected_len                         = row_len * LEVELS_DOWN;
  bool       level_map[ MAP_WIDTH ][ MAP_HEIGHT ] = {};

  if ((int) strlen(in) != expected_len) {
    DIE("bad level select map size, expected %d, got %d", (int) strlen(in), (int) expected_len);
  }

  auto tp_is_level_not_visited = tp_random(is_level_not_visited);
  auto tp_is_level_curr        = tp_random(is_level_curr);
  auto tp_is_level_across      = tp_random(is_level_across);
  auto tp_is_level_down        = tp_random(is_level_down);
  auto tp_is_level_final       = tp_random(is_level_final);
#if 0
  auto tp_is_level_next        = tp_random(is_level_next);
  auto tp_is_level_visited     = tp_random(is_level_visited);
#endif

  for (auto y = 0; y < LEVELS_DOWN; y++) {
    for (auto x = 0; x < LEVELS_ACROSS; x++) {
      auto offset = (row_len * y) + x;
      auto c      = in[ offset ];
      Tpp  tp     = nullptr;

      switch (c) {
        case CHARMAP_FLOOR :
          tp = tp_is_level_not_visited;
          if ((x == 0) && (y == 0)) {
            tp = tp_is_level_curr;
          }
          if ((x == LEVELS_ACROSS - 1) && (y == LEVELS_DOWN - 1)) {
            tp = tp_is_level_final;
          }
          break;
        default : break;
      }

      if (tp) {
        point at(x * LEVEL_SCALE + 1, y * LEVEL_SCALE + 1);
        auto  t = thing_init(g, v, l, tp, at);
        if (t) {
          thing_push(g, v, l, t);
          level_map[ x ][ y ] = true;
        }
      }
    }
  }

  for (auto y = 0; y < MAP_HEIGHT - 1; y++) {
    for (auto x = 0; x < MAP_WIDTH - 1; x++) {
      if (level_map[ x ][ y ] && level_map[ x + 1 ][ y ]) {
        {
          point at(x * LEVEL_SCALE + 2, y * LEVEL_SCALE + 1);
          auto  t = thing_init(g, v, l, tp_is_level_across, at);
          if (t) {
            thing_push(g, v, l, t);
            level_map[ x ][ y ] = true;
          }
        }
        {
          point at(x * LEVEL_SCALE + 3, y * LEVEL_SCALE + 1);
          auto  t = thing_init(g, v, l, tp_is_level_across, at);
          if (t) {
            thing_push(g, v, l, t);
            level_map[ x ][ y ] = true;
          }
        }
      }
    }
  }

  for (auto y = 0; y < MAP_HEIGHT - 1; y++) {
    for (auto x = 0; x < MAP_WIDTH - 1; x++) {
      if (level_map[ x ][ y ] && level_map[ x ][ y + 1 ]) {
        {
          point at(x * LEVEL_SCALE + 1, y * LEVEL_SCALE + 2);
          auto  t = thing_init(g, v, l, tp_is_level_down, at);
          if (t) {
            thing_push(g, v, l, t);
            level_map[ x ][ y ] = true;
          }
        }
        {
          point at(x * LEVEL_SCALE + 1, y * LEVEL_SCALE + 3);
          auto  t = thing_init(g, v, l, tp_is_level_down, at);
          if (t) {
            thing_push(g, v, l, t);
            level_map[ x ][ y ] = true;
          }
        }
      }
    }
  }
}

void level_select_create(Gamep g, class LevelSelect *l)
{
  TRACE_NO_INDENT();

  auto level_num    = MAX_LEVELS - 1;
  auto v            = game_levels_get(g);
  auto level_string = level_select_string(g, l);
  auto level        = game_level_get(g, v, level_num);

  level->initialized = true;
  level->level_num   = level_num;

  level_select_map_set(g, v, level, level_string.c_str());
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

  LevelSelect l;

  int len         = 10;
  int turn_chance = 10;
  int nwalks      = 10;

  level_select_clear(g, &l);
  snake_dive(g, &l, point(0, 0), 90);
  snake_dive(g, &l, point(0, 0), 40);
  snake_dive(g, &l, point(0, 0), 10);
  snake_dive(g, &l, 10);

  for (auto walks = 0; walks < nwalks; walks++) {
    snake_walk(g, &l, turn_chance, len);
  }

  level_select_count_levels(g, &l);
  level_select_dump(g, &l);
  level_select_create(g, &l);
}

void level_select_test(Gamep g)
{
  TRACE_NO_INDENT();

  LevelSelect l;

  int len         = 10;
  int turn_chance = 10;
  int nwalks      = 10;

  level_select_clear(g, &l);
  snake_dive(g, &l, point(0, 0), 90);
  snake_dive(g, &l, point(0, 0), 40);
  snake_dive(g, &l, point(0, 0), 10);
  snake_dive(g, &l, 10);

  for (auto walks = 0; walks < nwalks; walks++) {
    snake_walk(g, &l, turn_chance, len);
  }

  level_select_count_levels(g, &l);
  level_select_dump(g, &l);
}
