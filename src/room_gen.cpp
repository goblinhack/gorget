//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_charmap.hpp"
#include "my_game.hpp"
#include "my_level.hpp"
#include "my_main.hpp"
#include "my_ptrcheck.hpp"
#include "my_random.hpp"

#include <stdlib.h>

static const int MAX_ROOMS   = 10;
static const int ROOM_BORDER = 2;

class Grid
{
private:
public:
  Grid(void)
  {
    for (int y = 0; y < MAP_HEIGHT; y++) {
      for (int x = 0; x < MAP_WIDTH; x++) {
        data[ x ][ y ] = CHARMAP_EMPTY;
      }
    }
  }
  ~Grid(void) {}

  //
  // Level tiles and room info
  //
  char data[ MAP_WIDTH ][ MAP_HEIGHT ] = {};

  //
  // Top left and bottom right bounds
  //
  point tl;
  point br;

  int room_width {};
  int room_height {};
  int door_count {};
};

//
// Dump a level
//
static void grid_dump(Gamep g, Grid *grid)
{
  TRACE_NO_INDENT();

  printf("room_add(g, __FUNCTION__, __LINE__,\n");

  for (int y = 0; y < MAP_HEIGHT; y++) {
    printf("         (const char *)\"");
    for (int x = 0; x < MAP_WIDTH; x++) {
      printf("%c", grid->data[ x ][ y ]);
    }
    printf("\",\n");
  }
  printf("         nullptr);\n");
  printf("\n");
}

//
// Dump a level
//
static void grid_room_only_dump(Gamep g, Grid *grid)
{
  TRACE_NO_INDENT();

  printf("room_add(g, __FUNCTION__, __LINE__,\n");

  for (int y = grid->tl.y; y <= grid->br.y; y++) {
    printf("         (const char *)\"");
    for (int x = grid->tl.x; x <= grid->br.x; x++) {
      printf("%c", grid->data[ x ][ y ]);
    }
    printf("\",\n");
  }
  printf("         nullptr);\n");
  printf("\n");
}

static void grid_clear(Gamep g, Grid *grid)
{
  TRACE_NO_INDENT();

  memset(grid->data, CHARMAP_EMPTY, sizeof(grid->data));
}

//
// Get the top left and bottom right bounds of the room
//
static bool grid_get_bounds(Gamep g, class Grid *grid)
{
  int x, y;

  point tl(999, 999);
  point br(-1, -1);

  //
  // Get the top left and bottom right bounds
  //
  for (y = 0; y < MAP_HEIGHT; y++) {
    for (x = 0; x < MAP_WIDTH; x++) {
      if (grid->data[ x ][ y ] != CHARMAP_EMPTY) {
        if (x < tl.x) {
          tl.x = x;
        }
        if (y < tl.y) {
          tl.y = y;
        }
        if (x > br.x) {
          br.x = x;
        }
        if (y > br.y) {
          br.y = y;
        }
      }
    }
  }

  if (tl.x == 999) {
    return false;
  }
  if (tl.y == 999) {
    return false;
  }
  if (br.x == -1) {
    return false;
  }
  if (br.y == -1) {
    return false;
  }

  if (tl.x < ROOM_BORDER) {
    return false;
  }
  if (tl.y < ROOM_BORDER) {
    return false;
  }
  if (br.x >= MAP_WIDTH - ROOM_BORDER) {
    return false;
  }
  if (br.x >= MAP_HEIGHT - ROOM_BORDER) {
    return false;
  }

  grid->tl = tl;
  grid->br = br;

  grid->room_width  = br.x - tl.x;
  grid->room_height = br.y - tl.y;

  if (grid->room_width <= 0) {
    return false;
  }
  if (grid->room_height <= 0) {
    return false;
  }

  return true;
}

//
// Draw a rectangle in the buffer, checking for oob
//
static void grid_draw_rectangle(Gamep g, Grid *grid, uint8_t x, uint8_t y, uint8_t width, uint8_t height, char c)
{
  TRACE_NO_INDENT();

  for (auto i = x; i < x + width; i++) {
    for (auto j = y; j < y + height; j++) {
      point p(i, j);
      if (is_oob(p)) {
        continue;
      }
      grid->data[ i ][ j ] = c;
    }
  }
}

//
// Add random exits to the room
//
static void grid_add_exits(Gamep g, Grid *grid)
{
  TRACE_NO_INDENT();

  int x;
  int y;

  while (grid->door_count == 0) {
    //
    // Top door
    //
    x = grid->tl.x + pcg_random_range(0, grid->room_width);
    y = grid->tl.y - 1;

    if ((grid->data[ x ][ y ] == CHARMAP_EMPTY) && (grid->data[ x ][ y + 1 ] == CHARMAP_FLOOR)) {
      grid->data[ x ][ y ] = CHARMAP_JOIN;
      grid->door_count++;
    }

    //
    // Bottom door
    //
    x = grid->tl.x + pcg_random_range(0, grid->room_width);
    y = grid->br.y + 1;

    if ((grid->data[ x ][ y ] == CHARMAP_EMPTY) && (grid->data[ x ][ y - 1 ] == CHARMAP_FLOOR)) {
      grid->data[ x ][ y ] = CHARMAP_JOIN;
      grid->door_count++;
    }

    //
    // Left door
    //
    x = grid->tl.x - 1;
    y = grid->tl.y + pcg_random_range(0, grid->room_height);

    if ((grid->data[ x ][ y ] == CHARMAP_EMPTY) && (grid->data[ x + 1 ][ y ] == CHARMAP_FLOOR)) {
      grid->data[ x ][ y ] = CHARMAP_JOIN;
      grid->door_count++;
    }

    //
    // Right door
    //
    x = grid->br.x + 1;
    y = grid->tl.y + pcg_random_range(0, grid->room_height);

    if ((grid->data[ x ][ y ] == CHARMAP_EMPTY) && (grid->data[ x - 1 ][ y ] == CHARMAP_FLOOR)) {
      grid->data[ x ][ y ] = CHARMAP_JOIN;
      grid->door_count++;
    }
  }
}

//
// Borrowed from Brogue; makes a crossbar room
//
static void grid_design_cross_room(Gamep g, Grid *grid)
{
  TRACE_NO_INDENT();

  uint8_t roomWidth, roomHeight, roomWidth2, roomHeight2, roomX, roomY, roomX2, roomY2;

  roomWidth  = pcg_random_range(3, 12);
  roomX      = pcg_random_range(std::max(0, MAP_WIDTH / 2 - (roomWidth - 1)), std::min(MAP_WIDTH, MAP_WIDTH / 2));
  roomWidth2 = pcg_random_range(4, 20);
  roomX2     = (roomX + (roomWidth / 2) + pcg_random_range(0, 2) + pcg_random_range(0, 2) - 3) - (roomWidth2 / 2);

  roomHeight = pcg_random_range(3, 7);
  roomY      = (MAP_HEIGHT / 2 - roomHeight);

  roomHeight2 = pcg_random_range(2, 5);
  roomY2      = (MAP_HEIGHT / 2 - roomHeight2 - (pcg_random_range(0, 2) + pcg_random_range(0, 1)));

  grid_draw_rectangle(g, grid, roomX - 5, roomY + 5, roomWidth, roomHeight, CHARMAP_FLOOR);
  grid_draw_rectangle(g, grid, roomX2 - 5, roomY2 + 5, roomWidth2, roomHeight2, CHARMAP_FLOOR);
}

void rooms_test(Gamep g)
{
  for (auto r = 0; r < MAX_ROOMS; r++) {
    Grid grid;
    grid_clear(g, &grid);
    switch (pcg_random_range(0, 10)) {
      default : grid_design_cross_room(g, &grid); break;
    }

    if (! grid_get_bounds(g, &grid)) {
      continue;
    }

    grid_add_exits(g, &grid);

    if (! grid_get_bounds(g, &grid)) {
      continue;
    }

    if (0) {
      grid_dump(g, &grid);
    }

    grid_room_only_dump(g, &grid);
  }
}

