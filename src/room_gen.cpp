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
#include "my_random.hpp"

static const int MAX_ROOM_CORRIDOR = 3;
static const int ROOM_BORDER       = 2;

enum {
  ROOM_TYPE_CROSS,
  ROOM_TYPE_CROSS_SYM,
  ROOM_TYPE_SMALL,
  ROOM_TYPE_MEDIUM,
  ROOM_TYPE_CIRCULAR,
  ROOM_TYPE_CHUNKY,
  ROOM_TYPE_BLEND1,
  ROOM_TYPE_BLEND2,
};

class RoomGen
{
private:
public:
  RoomGen(void)
  {
    for (int y = 0; y < MAP_HEIGHT; y++) {
      for (int x = 0; x < MAP_WIDTH; x++) {
        data[ x ][ y ] = CHARMAP_EMPTY;
      }
    }
  }
  ~RoomGen(void) {}

  //
  // Level tiles and room info
  //
  char data[ MAP_WIDTH ][ MAP_HEIGHT ] = {};

  //
  // Top left and bottom right bounds
  //
  spoint tl = spoint();
  spoint br = spoint();

  int room_width {};
  int room_height {};
  int door_count {};

  //
  // Where to write the room data to
  //
  FILE *out;
};

//
// Dump a level
//
static void room_gen_dump(Gamep g, RoomGen *grid)
{
  TRACE_NO_INDENT();

  fprintf(grid->out, "  room_add(g, CHANCE_NORMAL, ROOM_CHECK_EXIT_FLAG, __FUNCTION__, __LINE__,\n");

  for (int y = 0; y < MAP_HEIGHT; y++) {
    fprintf(grid->out, "           /* line */ (const char *) \"");
    for (int x = 0; x < MAP_WIDTH; x++) {
      fprintf(grid->out, "%c", grid->data[ x ][ y ]);
    }
    fprintf(grid->out, "\",\n");
  }
  fprintf(grid->out, "           /* end */ nullptr);\n");
  fprintf(grid->out, "\n");
}

//
// Dump a level
//
static void room_gen_room_only_dump(Gamep g, RoomGen *grid)
{
  TRACE_NO_INDENT();

  fprintf(grid->out, "  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,\n");

  for (int y = grid->tl.y; y <= grid->br.y; y++) {
    fprintf(grid->out, "           /* line */ (const char *) \"");
    for (int x = grid->tl.x; x <= grid->br.x; x++) {
      fprintf(grid->out, "%c", grid->data[ x ][ y ]);
    }
    fprintf(grid->out, "\",\n");
  }
  fprintf(grid->out, "           /* end */ nullptr);\n");
  fprintf(grid->out, "\n");
}

static void room_gen_clear(Gamep g, RoomGen *grid)
{
  TRACE_NO_INDENT();

  memset(grid->data, CHARMAP_EMPTY, SIZEOF(grid->data));
}

//
// Get the top left and bottom right bounds of the room
//
static bool room_gen_keep_largest_chunk(Gamep g, class RoomGen *grid)
{
  Cave cave = {};
  int  x, y;

  //
  // Populate the cave with the room
  //
  for (y = 0; y < MAP_HEIGHT; y++) {
    for (x = 0; x < MAP_WIDTH; x++) {
      if (grid->data[ x ][ y ] != CHARMAP_EMPTY) {
        cave.curr[ x + MAP_LEVEL_CELLULAR_BORDER ][ y + MAP_LEVEL_CELLULAR_BORDER ] = 1;
      }
    }
  }

  //
  // Keep largest blob only
  //
  cave_generation_keep_largest_blob(g, &cave);

  //
  // Map that back to a room shape
  //
  room_gen_clear(g, grid);

  for (y = 0; y < MAP_HEIGHT; y++) {
    for (x = 0; x < MAP_WIDTH; x++) {
      if (cave.curr[ x + MAP_LEVEL_CELLULAR_BORDER ][ y + MAP_LEVEL_CELLULAR_BORDER ]) {
        grid->data[ x ][ y ] = CHARMAP_FLOOR;
      }
    }
  }

  return true;
}

//
// Get the top left and bottom right bounds of the room
//
static bool room_gen_get_bounds(Gamep g, class RoomGen *grid)
{
  int x, y;

  spoint tl(999, 999);
  spoint br(-1, -1);

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
static void room_gen_draw_rectangle(Gamep g, RoomGen *grid, int x, int y, int width, int height, char c)
{
  TRACE_NO_INDENT();

  for (auto i = x; i < x + width; i++) {
    for (auto j = y; j < y + height; j++) {
      spoint p(i, j);
      if (is_oob(p)) {
        continue;
      }
      grid->data[ i ][ j ] = c;
    }
  }
}

static void room_gen_draw_circle(Gamep g, RoomGen *grid, int x, int y, int radius, char value)
{
  TRACE_NO_INDENT();

  int i, j;

  for (i = std::max(0, x - radius - 1); i < std::max(MAP_WIDTH, x + radius); i++) {
    for (j = std::max(0, y - radius - 1); j < std::max(MAP_HEIGHT, y + radius); j++) {
      if ((i - x) * (i - x) + (j - y) * (j - y) < radius * radius + radius) {
        spoint p(i, j);
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
static void room_gen_add_exits(Gamep g, RoomGen *grid)
{
  TRACE_NO_INDENT();

  int x;
  int y;

  for (;;) {
    //
    // Top door
    //
    x = grid->tl.x + pcg_random_range(0, grid->room_width);
    y = grid->tl.y - 1;

    if ((grid->data[ x ][ y ] == CHARMAP_EMPTY) && (grid->data[ x ][ y + 1 ] == CHARMAP_FLOOR)) {
      grid->data[ x ][ y ] = CHARMAP_JOIN;
      grid->door_count++;
      break;
    }
  }

  for (;;) {
    //
    // Bottom door
    //
    x = grid->tl.x + pcg_random_range(0, grid->room_width);
    y = grid->br.y + 1;

    if ((grid->data[ x ][ y ] == CHARMAP_EMPTY) && (grid->data[ x ][ y - 1 ] == CHARMAP_FLOOR)) {
      grid->data[ x ][ y ] = CHARMAP_JOIN;
      grid->door_count++;
      break;
    }
  }

  for (;;) {
    //
    // Left door
    //
    x = grid->tl.x - 1;
    y = grid->tl.y + pcg_random_range(0, grid->room_height);

    if ((grid->data[ x ][ y ] == CHARMAP_EMPTY) && (grid->data[ x + 1 ][ y ] == CHARMAP_FLOOR)) {
      grid->data[ x ][ y ] = CHARMAP_JOIN;
      grid->door_count++;
      break;
    }
  }

  for (;;) {
    //
    // Right door
    //
    x = grid->br.x + 1;
    y = grid->tl.y + pcg_random_range(0, grid->room_height);

    if ((grid->data[ x ][ y ] == CHARMAP_EMPTY) && (grid->data[ x - 1 ][ y ] == CHARMAP_FLOOR)) {
      grid->data[ x ][ y ] = CHARMAP_JOIN;
      grid->door_count++;
      break;
    }
  }
}

//
// Extend an existing exit
//
static void room_gen_add_corridor(Gamep g, RoomGen *grid)
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
static void room_gen_design_cross_room(Gamep g, RoomGen *grid)
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

  room_gen_draw_rectangle(g, grid, roomX - 5, roomY + 5, roomWidth, roomHeight, CHARMAP_FLOOR);
  room_gen_draw_rectangle(g, grid, roomX2 - 5, roomY2 + 5, roomWidth2, roomHeight2, CHARMAP_FLOOR);
}

//
// Borrowed from Brogue; makes a symmetrical cross room
//
static void room_gen_design_cross_room_symmetrical(Gamep g, RoomGen *grid)
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

  room_gen_draw_rectangle(g, grid, (MAP_WIDTH - majorWidth) / 2, (MAP_HEIGHT - minorHeight) / 2, majorWidth,
                          minorHeight, CHARMAP_FLOOR);
  room_gen_draw_rectangle(g, grid, (MAP_WIDTH - minorWidth) / 2, (MAP_HEIGHT - majorHeight) / 2, minorWidth,
                          majorHeight, CHARMAP_FLOOR);
}

static void room_gen_design_small_room(Gamep g, RoomGen *grid)
{
  TRACE_NO_INDENT();

  int width, height;

  width  = pcg_random_range(3, 6);
  height = pcg_random_range(3, 6);

  room_gen_draw_rectangle(g, grid, (MAP_WIDTH - width) / 2, (MAP_HEIGHT - height) / 2, width, height, CHARMAP_FLOOR);
}

static void room_gen_design_medium_room(Gamep g, RoomGen *grid)
{
  TRACE_NO_INDENT();

  int width, height;

  width  = pcg_random_range(6, 10);
  height = pcg_random_range(4, 10);

  room_gen_draw_rectangle(g, grid, (MAP_WIDTH - width) / 2, (MAP_HEIGHT - height) / 2, width, height, CHARMAP_FLOOR);
}

static void room_gen_design_circular_room(Gamep g, RoomGen *grid)
{
  int radius;

  if (d100() < 5) {
    radius = pcg_random_range(4, 10);
  } else {
    radius = pcg_random_range(2, 4);
  }

  room_gen_draw_circle(g, grid, MAP_WIDTH / 2, MAP_HEIGHT / 2, radius, CHARMAP_FLOOR);

  if (radius > 6 && d100() < 50) {
    room_gen_draw_circle(g, grid, MAP_WIDTH / 2, MAP_HEIGHT / 2, pcg_random_range(3, radius - 3), CHARMAP_EMPTY);
  }
}

static void room_gen_design_chunky_room(Gamep g, RoomGen *grid)
{
  TRACE_NO_INDENT();

  int i, x, y;
  int minX, maxX, minY, maxY;
  int chunkCount = pcg_random_range(2, 8);

  room_gen_draw_circle(g, grid, MAP_WIDTH / 2, MAP_HEIGHT / 2, 2, CHARMAP_FLOOR);

  minX = MAP_WIDTH / 2 - 3;
  maxX = MAP_WIDTH / 2 + 3;
  minY = MAP_HEIGHT / 2 - 3;
  maxY = MAP_HEIGHT / 2 + 3;

  for (i = 0; i < chunkCount;) {
    x = pcg_random_range(minX, maxX);
    y = pcg_random_range(minY, maxY);

    if (grid->data[ x ][ y ] != CHARMAP_EMPTY) {
      room_gen_draw_circle(g, grid, x, y, 2, CHARMAP_FLOOR);

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
static bool rooms_dump_one(Gamep g, FILE *out, int which)
{
  TRACE_NO_INDENT();

  RoomGen grid;

  room_gen_clear(g, &grid);

  grid.out = out;

  switch (which) {
    case ROOM_TYPE_CROSS :     room_gen_design_cross_room(g, &grid); break;
    case ROOM_TYPE_CROSS_SYM : room_gen_design_cross_room_symmetrical(g, &grid); break;
    case ROOM_TYPE_SMALL :     room_gen_design_small_room(g, &grid); break;
    case ROOM_TYPE_MEDIUM :    room_gen_design_medium_room(g, &grid); break;
    case ROOM_TYPE_CIRCULAR :  room_gen_design_circular_room(g, &grid); break;
    case ROOM_TYPE_CHUNKY :    room_gen_design_chunky_room(g, &grid); break;
    case ROOM_TYPE_BLEND1 :
      room_gen_design_cross_room(g, &grid);
      room_gen_design_chunky_room(g, &grid);
      room_gen_design_circular_room(g, &grid);
      break;
    case ROOM_TYPE_BLEND2 :
      room_gen_design_chunky_room(g, &grid);
      room_gen_design_chunky_room(g, &grid);
      break;
  }

  //
  // Always ensure we have a contiguous blob. If we have two seperate room fragments,
  // this will end up with only one.
  //
  room_gen_keep_largest_chunk(g, &grid);

  if (! room_gen_get_bounds(g, &grid)) {
    return false;
  }
  if (0) {
    room_gen_dump(g, &grid);
  }

  //
  // Add room exits
  //
  room_gen_add_exits(g, &grid);
  if (! room_gen_get_bounds(g, &grid)) {
    return false;
  }

  //
  // Add corridors
  //
  if (d100() < 50) {
    for (auto corridors = 0; corridors < MAX_ROOM_CORRIDOR; corridors++) {
      room_gen_add_corridor(g, &grid);
      if (! room_gen_get_bounds(g, &grid)) {
        return false;
      }

      room_gen_add_corridor(g, &grid);
      if (! room_gen_get_bounds(g, &grid)) {
        return false;
      }
    }
  }

  room_gen_room_only_dump(g, &grid);
  return true;
}

//
// Dump a random room of the given type
//
static void rooms_write_source_file_for_n_rooms(Gamep g, int n, int which, const char *name)
{
  TRACE_NO_INDENT();

  std::string f = "src/rooms_" + std::string(name) + ".cpp";

  CON("Write to %s", f.c_str());

  FILE *out = fopen(f.c_str(), "w+");
  if (! out) {
    DIE("could not write to %s", f.c_str());
  }

  fprintf(out, "//\n");
  fprintf(out, "// Copyright goblinhack@gmail.com\n");
  fprintf(out, "//\n");
  fprintf(out, "\n");
  fprintf(out, "#include \"my_callstack.hpp\"\n");
  fprintf(out, "#include \"my_charmap.hpp\"\n");
  fprintf(out, "#include \"my_level.hpp\"\n");
  fprintf(out, "\n");
  fprintf(out, "//\n");
  fprintf(out, "// %d rooms of type '%s' from seed '%s'\n", n, name, game_seed_name_get(g));
  fprintf(out, "//\n");
  fprintf(out, "void rooms_%s(Gamep g)\n", name);
  fprintf(out, "{\n");
  fprintf(out, "  TRACE_NO_INDENT();\n");
  fprintf(out, "\n");

  for (auto r = 0; r < n; r++) {
    rooms_dump_one(g, out, which);
  }

  fprintf(out, "}\n");

  fclose(out);
}

void rooms_test(Gamep g)
{
  TRACE_NO_INDENT();

  rooms_write_source_file_for_n_rooms(g, 500, ROOM_TYPE_CROSS, "cross");
  rooms_write_source_file_for_n_rooms(g, 500, ROOM_TYPE_CROSS_SYM, "cross_sym");
  rooms_write_source_file_for_n_rooms(g, 500, ROOM_TYPE_SMALL, "small");
  rooms_write_source_file_for_n_rooms(g, 1000, ROOM_TYPE_MEDIUM, "medium");
  rooms_write_source_file_for_n_rooms(g, 200, ROOM_TYPE_CIRCULAR, "circular");
  rooms_write_source_file_for_n_rooms(g, 500, ROOM_TYPE_CHUNKY, "chunky");
  rooms_write_source_file_for_n_rooms(g, 500, ROOM_TYPE_BLEND2, "blend2");
  rooms_write_source_file_for_n_rooms(g, 500, ROOM_TYPE_BLEND1, "blend1");
}
