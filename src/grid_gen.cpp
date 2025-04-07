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

class Grid
{
private:
public:
  Grid(void)
  {
    for (int y = 0; y < LEVELS_DOWN; y++) {
      for (int x = 0; x < LEVELS_ACROSS; x++) {
        data[ x ][ y ] = CHARMAP_EMPTY;
      }
    }
  }
  ~Grid(void) {}

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
static void grid_dump(Gamep g, Grid *grid)
{
  TRACE_NO_INDENT();

  LOG("Grid, level count %d", grid->level_count);

  for (int y = 0; y < LEVELS_DOWN; y++) {
    std::string(s);
    for (int x = 0; x < LEVELS_ACROSS; x++) {
      s += grid->data[ x ][ y ];
    }
    LOG("%s", s.c_str());
  }
  LOG("-");
}

//
// Clear the grid
//
static void grid_clear(Gamep g, Grid *grid)
{
  TRACE_NO_INDENT();

  memset(grid->data, CHARMAP_EMPTY, sizeof(grid->data));
}

//
// Count the levels created
//
static int grid_count_levels(Gamep g, Grid *grid)
{
  TRACE_NO_INDENT();

  grid->level_count = 0;

  for (int y = 0; y < LEVELS_DOWN; y++) {
    for (int x = 0; x < LEVELS_ACROSS; x++) {
      if (grid->data[ x ][ y ] == CHARMAP_FLOOR) {
        grid->level_count++;
      }
    }
  }
  return grid->level_count;
}

static void snake_walk(Gamep g, Grid *grid, point at, int turn_chance, int count)
{
  TRACE_NO_INDENT();

  point dir(1, 0);
  point end(LEVELS_ACROSS - 1, LEVELS_DOWN - 1);

  while (count-- > 0) {
    //
    // Ensure we never try to create too many levels
    //
    if (grid_count_levels(g, grid) >= LEVELS_COUNT) {
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

    grid->data[ at.x ][ at.y ] = CHARMAP_FLOOR;

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

  grid->data[ at.x ][ at.y ] = CHARMAP_FLOOR;
}

static void snake_walk(Gamep g, Grid *grid, int turn_chance, int count)
{
  TRACE_NO_INDENT();

  while (true) {
    auto x = pcg_random_range(0, LEVELS_ACROSS);
    auto y = pcg_random_range(0, LEVELS_DOWN);

    if (grid->data[ x ][ y ] == CHARMAP_FLOOR) {
      snake_walk(g, grid, point(x, y), turn_chance, count);
      return;
    }
  }
}

static void snake_dive(Gamep g, Grid *grid, point at, int dive_chance)
{
  TRACE_NO_INDENT();

  point end(LEVELS_ACROSS - 1, LEVELS_DOWN - 1);

  while (at != end) {
    //
    // Ensure we never try to create too many levels
    //
    if (grid_count_levels(g, grid) >= LEVELS_COUNT) {
      return;
    }

    auto chance = d100();

    grid->data[ at.x ][ at.y ] = CHARMAP_FLOOR;

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

  grid->data[ at.x ][ at.y ] = CHARMAP_FLOOR;
}

static void snake_dive(Gamep g, Grid *grid, int dive_chance)
{
  TRACE_NO_INDENT();

  while (true) {
    auto x = pcg_random_range(0, LEVELS_ACROSS);
    auto y = pcg_random_range(0, LEVELS_DOWN);

    if (grid->data[ x ][ y ] == CHARMAP_FLOOR) {
      snake_dive(g, grid, point(x, y), dive_chance);

      return;
    }
  }
}

void grid_test(Gamep g)
{
  TRACE_NO_INDENT();

  Grid grid;

  int len         = 10;
  int turn_chance = 10;
  int nwalks      = 10;

  grid_clear(g, &grid);
  snake_dive(g, &grid, point(0, 0), 90);
  snake_dive(g, &grid, point(0, 0), 40);
  snake_dive(g, &grid, point(0, 0), 10);
  snake_dive(g, &grid, 10);

  for (auto walks = 0; walks < nwalks; walks++) {
    snake_walk(g, &grid, turn_chance, len);
  }

  grid_count_levels(g, &grid);
  grid_dump(g, &grid);
}
