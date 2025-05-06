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

#if 0
void level_map_set(Gamep g, Levelsp v, Levelp l, const char *in)
{
  TRACE_NO_INDENT();

  const auto row_len      = MAP_WIDTH;
  auto       expected_len = row_len * MAP_HEIGHT;

  if ((int) strlen(in) != expected_len) {
    DIE("bad map size, expected %d, got %d", (int) strlen(in), (int) expected_len);
  }

  auto tp_wall       = tp_random(is_wall);
  auto tp_rock       = tp_random(is_rock);
  auto tp_water      = tp_random(is_water);
  auto tp_lava       = tp_random(is_lava);
  auto tp_bridge     = tp_random(is_bridge);
  auto tp_chasm      = tp_random(is_chasm);
  auto tp_deep_water = tp_random(is_deep_water);
  auto tp_treasure1  = tp_random(is_treasure1);
  auto tp_treasure2  = tp_random(is_treasure2);
  auto tp_door       = tp_find_mand("door");
  auto tp_floor      = tp_find_mand("floor");
  auto tp_corridor   = tp_find_mand("corridor");
  auto tp_foliage    = tp_find_mand("foliage");
  auto tp_dirt       = tp_find_mand("dirt");
  auto tp_exit       = tp_find_mand("exit");
  auto tp_player     = tp_find_mand("player");
  //  auto tp_entrance = tp_find_mand("entrance");

  for (auto y = 0; y < MAP_HEIGHT; y++) {
    for (auto x = 0; x < MAP_WIDTH; x++) {
      auto offset = (row_len * y) + x;
      auto c      = in[ offset ];
      Tpp  tp     = nullptr;

      bool need_floor   = false;
      bool need_water   = false;
      bool need_dirt    = false;
      bool need_foliage = false;

      switch (c) {
        case CHARMAP_FLOOR :
          need_floor = true;
          if (d100() < 5) {
            need_foliage = true;
          }
          break;
        case CHARMAP_DIRT :
          need_dirt = true;
          if (d100() < 50) {
            need_foliage = true;
          }
          break;
        case CHARMAP_CHASM : tp = tp_chasm; break;
        case CHARMAP_JOIN : tp = tp_corridor; break;
        case CHARMAP_CORRIDOR : tp = tp_corridor; break;
        case CHARMAP_BRIDGE : tp = tp_bridge; break;
        case CHARMAP_WALL :
          need_floor = true;
          tp         = tp_wall;
          break;
        case CHARMAP_TREASURE1 :
          need_floor = true;
          tp         = tp_treasure1;
          break;
        case CHARMAP_TREASURE2 :
          need_floor = true;
          tp         = tp_treasure2;
          break;
        case CHARMAP_TELEPORT :
          need_floor = true;
          tp         = nullptr; /* todo */
          break;
        case CHARMAP_FOLIAGE :
          need_floor   = true;
          need_foliage = true;
          break;
        case CHARMAP_DEEP_WATER :
          need_dirt  = true;
          tp         = tp_deep_water;
          need_water = true;
          break;
        case CHARMAP_WATER :
          need_dirt  = true;
          need_water = true;
          if (d100() < 5) {
            need_foliage = true;
          }
          break;
        case CHARMAP_BARREL :
          need_floor = true;
          tp         = nullptr; /* todo */
          break;
        case CHARMAP_PILLAR :
          need_floor = true;
          tp         = nullptr; /* todo */
          break;
        case CHARMAP_TRAP :
          need_floor = true;
          tp         = nullptr; /* todo */
          break;
        case CHARMAP_LAVA :
          need_floor = true;
          tp         = tp_lava;
          break;
        case CHARMAP_BRAZIER :
          need_floor = true;
          tp         = nullptr; /* todo */
          break;
        case CHARMAP_DOOR :
          need_floor = true;
          tp         = tp_door;
          break;
        case CHARMAP_SECRET_DOOR :
          need_floor = true;
          tp         = nullptr; /* todo */
          break;
        case CHARMAP_DRY_GRASS :
          need_floor = true;
          tp         = nullptr; /* todo */
          break;
        case CHARMAP_MONST1 :
          need_floor = true;
          tp         = tp_random(is_monst1);
          break;
        case CHARMAP_MONST2 :
          need_floor = true;
          tp         = nullptr; /* todo */
          break;
        case CHARMAP_MOB1 :
          need_floor = true;
          tp         = tp_random(is_mob1);
          break;
        case CHARMAP_MOB2 :
          need_floor = true;
          tp         = nullptr; /* todo */
          break;
        case CHARMAP_ENTRANCE :
          need_floor = true;
          if (l->level_num == 0) {
            tp = tp_player;
          } else {
            // tp = tp_entrance;
            tp = nullptr; /* todo */
          }
          break;
        case CHARMAP_EXIT :
          need_floor = true;
          tp         = tp_exit;
          break;
        case CHARMAP_KEY :
          need_floor = true;
          tp         = nullptr; /* todo */
          break;
        case CHARMAP_EMPTY :
          need_dirt = true;
          tp        = tp_rock;
          break;
        default :
          if (! g_opt_test_level_gen) {
            //            DIE("unexpected map char '%c'", c);
          }
      }

      if (need_floor) {
        auto tp_add = tp_floor;
        auto t      = thing_init(g, v, l, tp_add, point(x, y));
        if (t) {
          thing_push(g, v, l, t);
        }
      }

      if (need_dirt) {
        auto tp_add = tp_dirt;
        auto t      = thing_init(g, v, l, tp_add, point(x, y));
        if (t) {
          thing_push(g, v, l, t);
        }
      }

      if (need_water) {
        auto t = thing_init(g, v, l, tp_water, point(x, y));
        if (t) {
          thing_push(g, v, l, t);
        }
      }

      if (need_foliage) {
        auto tp_add = tp_foliage;
        auto t      = thing_init(g, v, l, tp_add, point(x, y));
        if (t) {
          thing_push(g, v, l, t);
        }
      }

      if (tp) {
        auto t = thing_init(g, v, l, tp, point(x, y));
        if (t) {
          thing_push(g, v, l, t);
        }
      }
    }
  }
}
#endif

void level_select_create(Gamep g, class LevelSelect *l)
{
  TRACE_NO_INDENT();

  auto level_num    = MAX_LEVELS - 1;
  auto v            = game_levels_get(g);
  auto level_string = level_select_string(g, l);
  auto level        = game_level_get(g, v, level_num);

  level->initialized = true;
  level->level_num   = level_num;

#if 0
  level_map_set(g, v, level, level_string.c_str());
#endif
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
