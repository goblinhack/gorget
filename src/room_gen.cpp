//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_charmap.hpp"
#include "my_dice.hpp"
#include "my_game.hpp"
#include "my_level.hpp"
#include "my_main.hpp"
#include "my_ptrcheck.hpp"
#include "my_random.hpp"

#include <stdlib.h>

static const int MAX_ROOMS         = 100;
static const int MAX_ROOM_CORRIDOR = 3;
static const int ROOM_BORDER       = 2;

enum {
  ROOM_TYPE_CROSS,
  ROOM_TYPE_CROSS_SYM,
  ROOM_TYPE_SMALL,
  ROOM_TYPE_CIRCULAR,
  ROOM_TYPE_CHUNKY,
  ROOM_TYPE_BLEND1,
  ROOM_TYPE_BLEND2,
};

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
static void grid_draw_rectangle(Gamep g, Grid *grid, int x, int y, int width, int height, char c)
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

static void grid_draw_circle(Gamep g, Grid *grid, int x, int y, int radius, char value)
{
  TRACE_NO_INDENT();

  int i, j;

  for (i = std::max(0, x - radius - 1); i < std::max(MAP_WIDTH, x + radius); i++) {
    for (j = std::max(0, y - radius - 1); j < std::max(MAP_HEIGHT, y + radius); j++) {
      if ((i - x) * (i - x) + (j - y) * (j - y) < radius * radius + radius) {
        point p(i, j);
        if (is_oob(p)) {
          continue;
        }
        grid->data[ i ][ j ] = value;
      }
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
// Extend an existing exit
//
static void grid_add_corridor(Gamep g, Grid *grid)
{
  TRACE_NO_INDENT();

  int x;
  int y;

  //
  // Top door
  //
  x = grid->tl.x + pcg_random_range(0, grid->room_width);
  y = grid->tl.y - 1;

  if ((grid->data[ x ][ y ] == CHARMAP_EMPTY) && (grid->data[ x ][ y + 1 ] == CHARMAP_JOIN)) {
    grid->data[ x ][ y ]     = CHARMAP_JOIN;
    grid->data[ x ][ y + 1 ] = CHARMAP_FLOOR;
    grid->door_count++;
  }

  //
  // Bottom door
  //
  x = grid->tl.x + pcg_random_range(0, grid->room_width);
  y = grid->br.y + 1;

  if ((grid->data[ x ][ y ] == CHARMAP_EMPTY) && (grid->data[ x ][ y - 1 ] == CHARMAP_JOIN)) {
    grid->data[ x ][ y ]     = CHARMAP_JOIN;
    grid->data[ x ][ y - 1 ] = CHARMAP_FLOOR;
    grid->door_count++;
  }

  //
  // Left door
  //
  x = grid->tl.x - 1;
  y = grid->tl.y + pcg_random_range(0, grid->room_height);

  if ((grid->data[ x ][ y ] == CHARMAP_EMPTY) && (grid->data[ x + 1 ][ y ] == CHARMAP_JOIN)) {
    grid->data[ x ][ y ]     = CHARMAP_JOIN;
    grid->data[ x + 1 ][ y ] = CHARMAP_FLOOR;
    grid->door_count++;
  }

  //
  // Right door
  //
  x = grid->br.x + 1;
  y = grid->tl.y + pcg_random_range(0, grid->room_height);

  if ((grid->data[ x ][ y ] == CHARMAP_EMPTY) && (grid->data[ x - 1 ][ y ] == CHARMAP_JOIN)) {
    grid->data[ x ][ y ]     = CHARMAP_JOIN;
    grid->data[ x - 1 ][ y ] = CHARMAP_FLOOR;
    grid->door_count++;
  }
}

//
// Borrowed from Brogue; makes a crossbar room
//
static void grid_design_cross_room(Gamep g, Grid *grid)
{
  TRACE_NO_INDENT();

  int roomWidth, roomHeight, roomWidth2, roomHeight2, roomX, roomY, roomX2, roomY2;

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

//
// Borrowed from Brogue; makes a symmetrical cross room
//
static void grid_design_cross_room_symmetrical(Gamep g, Grid *grid)
{
  TRACE_NO_INDENT();

  int majorWidth, majorHeight, minorWidth, minorHeight;

  majorWidth  = pcg_random_range(4, 8);
  majorHeight = pcg_random_range(4, 5);

  minorWidth = pcg_random_range(3, 4);
  if (majorHeight % 2 == 0) {
    minorWidth -= 1;
  }
  minorHeight = 3; // pcg_random_range(2, 3);
  if (majorWidth % 2 == 0) {
    minorHeight -= 1;
  }

  grid_draw_rectangle(g, grid, (MAP_WIDTH - majorWidth) / 2, (MAP_HEIGHT - minorHeight) / 2, majorWidth, minorHeight,
                      CHARMAP_FLOOR);
  grid_draw_rectangle(g, grid, (MAP_WIDTH - minorWidth) / 2, (MAP_HEIGHT - majorHeight) / 2, minorWidth, majorHeight,
                      CHARMAP_FLOOR);
}

static void grid_design_small_room(Gamep g, Grid *grid)
{
  TRACE_NO_INDENT();

  int width, height;

  width  = pcg_random_range(3, 6);
  height = pcg_random_range(2, 4);

  grid_draw_rectangle(g, grid, (MAP_WIDTH - width) / 2, (MAP_HEIGHT - height) / 2, width, height, CHARMAP_FLOOR);
}

static void grid_design_circular_room(Gamep g, Grid *grid)
{
  int radius;

  if (d100() < 5) {
    radius = pcg_random_range(4, 10);
  } else {
    radius = pcg_random_range(2, 4);
  }

  grid_draw_circle(g, grid, MAP_WIDTH / 2, MAP_HEIGHT / 2, radius, CHARMAP_FLOOR);

  if (radius > 6 && d100() < 50) {
    grid_draw_circle(g, grid, MAP_WIDTH / 2, MAP_HEIGHT / 2, pcg_random_range(3, radius - 3), CHARMAP_EMPTY);
  }
}

static void grid_design_chunky_room(Gamep g, Grid *grid)
{
  TRACE_NO_INDENT();

  int i, x, y;
  int minX, maxX, minY, maxY;
  int chunkCount = pcg_random_range(2, 8);

  grid_draw_circle(g, grid, MAP_WIDTH / 2, MAP_HEIGHT / 2, 2, CHARMAP_FLOOR);

  minX = MAP_WIDTH / 2 - 3;
  maxX = MAP_WIDTH / 2 + 3;
  minY = MAP_HEIGHT / 2 - 3;
  maxY = MAP_HEIGHT / 2 + 3;

  for (i = 0; i < chunkCount;) {
    x = pcg_random_range(minX, maxX);
    y = pcg_random_range(minY, maxY);

    if (grid->data[ x ][ y ] != CHARMAP_EMPTY) {
      grid_draw_circle(g, grid, x, y, 2, CHARMAP_FLOOR);

      i++;
      minX = std::max(1, std::min(x - 3, minX));
      maxX = std::min(MAP_WIDTH - 2, std::max(x + 3, maxX));
      minY = std::max(1, std::min(y - 3, minY));
      maxY = std::min(MAP_HEIGHT - 2, std::max(y + 3, maxY));
    }
  }
}

//
// Dump a random room of the given type
//
static bool rooms_dump_one(Gamep g, int which)
{
  TRACE_NO_INDENT();

  Grid grid;
  grid_clear(g, &grid);

  switch (which) {
    case ROOM_TYPE_CROSS : grid_design_cross_room(g, &grid); break;
    case ROOM_TYPE_CROSS_SYM : grid_design_cross_room_symmetrical(g, &grid); break;
    case ROOM_TYPE_SMALL : grid_design_small_room(g, &grid); break;
    case ROOM_TYPE_CIRCULAR : grid_design_circular_room(g, &grid); break;
    case ROOM_TYPE_CHUNKY : grid_design_chunky_room(g, &grid); break;
    case ROOM_TYPE_BLEND1 :
      grid_design_cross_room(g, &grid);
      grid_design_chunky_room(g, &grid);
      grid_design_circular_room(g, &grid);
      break;
    case ROOM_TYPE_BLEND2 :
      grid_design_chunky_room(g, &grid);
      grid_design_chunky_room(g, &grid);
      break;
  }

  if (! grid_get_bounds(g, &grid)) {
    return false;
  }
  if (0) {
    grid_dump(g, &grid);
  }

  //
  // Add room exits
  //
  grid_add_exits(g, &grid);
  if (! grid_get_bounds(g, &grid)) {
    return false;
  }

  //
  // Add corridors
  //
  if (d100() < 50) {
    for (auto corridors = 0; corridors < MAX_ROOM_CORRIDOR; corridors++) {
      grid_add_corridor(g, &grid);
      if (! grid_get_bounds(g, &grid)) {
        return false;
      }

      grid_add_corridor(g, &grid);
      if (! grid_get_bounds(g, &grid)) {
        return false;
      }
    }
  }

  grid_room_only_dump(g, &grid);
  return true;
}

void rooms_test(Gamep g)
{
  for (auto r = 0; r < MAX_ROOMS; r++) {
    // rooms_dump_one(g, ROOM_TYPE_CROSS);
    //    rooms_dump_one(g, ROOM_TYPE_CROSS_SYM);
    //    rooms_dump_one(g, ROOM_TYPE_SMALL);
    //    rooms_dump_one(g, ROOM_TYPE_CIRCULAR);
    //    rooms_dump_one(g, ROOM_TYPE_CHUNKY);
    rooms_dump_one(g, ROOM_TYPE_BLEND1);
    // rooms_dump_one(g, ROOM_TYPE_BLEND2);
  }
}

