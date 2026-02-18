//
// Copyright goblinhack@gmail.com
//

#include <algorithm>
#include <print>

#include "my_callstack.hpp"
#include "my_cave.hpp"
#include "my_charmap.hpp"
#include "my_dice_rolls.hpp"
#include "my_game.hpp"
#include "my_globals.hpp"
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
  RoomGen()
  {
    for (int y = 0; y < MAP_HEIGHT; y++) {
      for (auto &x : data) {
        x[ y ] = CHARMAP_EMPTY;
      }
    }
  }
  ~RoomGen() = default;

  //
  // Level tiles and room info
  //
  char data[ MAP_WIDTH ][ MAP_HEIGHT ] = {};

  //
  // Top left and bottom right bounds
  //
  spoint tl = {};
  spoint br = {};

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

  std::println(grid->out, "  room_add(g, CHANCE_NORMAL, ROOM_FLAG_CHECK_EXITS, __FUNCTION__, __LINE__,");

  for (int y = 0; y < MAP_HEIGHT; y++) {
    std::print(grid->out, "           /* line */ (const char *) \"");
    for (auto &x : grid->data) {
      std::print(grid->out, "{}", x[ y ]);
    }
    std::println(grid->out, "\",");
  }
  std::println(grid->out, "           /* end */ nullptr);");
  std::println(grid->out, "");
}

//
// Dump a level
//
static void room_gen_room_only_dump(Gamep g, RoomGen *grid)
{
  TRACE_NO_INDENT();

  std::println(grid->out, "  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,");

  for (int y = grid->tl.y; y <= grid->br.y; y++) {
    std::print(grid->out, "           /* line */ (const char *) \"");
    for (int x = grid->tl.x; x <= grid->br.x; x++) {
      std::print(grid->out, "{}", grid->data[ x ][ y ]);
    }
    std::println(grid->out, "\",");
  }
  std::println(grid->out, "           /* end */ nullptr);");
  std::println(grid->out, "");
}

static void room_gen_clear(Gamep g, RoomGen *grid)
{
  TRACE_NO_INDENT();

  memset(grid->data, CHARMAP_EMPTY, SIZEOF(grid->data));
}

//
// Get the top left and bottom right bounds of the room
//
static void room_gen_keep_largest_chunk(Gamep g, class RoomGen *grid)
{
  Cave cave = {};
  int  x;
  int  y;

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
      if (cave.curr[ x + MAP_LEVEL_CELLULAR_BORDER ][ y + MAP_LEVEL_CELLULAR_BORDER ] != 0U) {
        grid->data[ x ][ y ] = CHARMAP_FLOOR;
      }
    }
  }
}

//
// Get the top left and bottom right bounds of the room
//
[[nodiscard]] static bool room_gen_get_bounds(Gamep g, class RoomGen *grid)
{
  int x;
  int y;

  spoint tl(999, 999);
  spoint br(-1, -1);

  //
  // Get the top left and bottom right bounds
  //
  for (y = 0; y < MAP_HEIGHT; y++) {
    for (x = 0; x < MAP_WIDTH; x++) {
      if (grid->data[ x ][ y ] != CHARMAP_EMPTY) {
        tl.x = std::min< int >(x, tl.x);
        tl.y = std::min< int >(y, tl.y);
        br.x = std::max< int >(x, br.x);
        br.y = std::max< int >(y, br.y);
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

  int i;
  int j;

  for (i = std::max(0, x - radius - 1); i < std::max((int) MAP_WIDTH, x + radius); i++) {
    for (j = std::max(0, y - radius - 1); j < std::max((int) MAP_HEIGHT, y + radius); j++) {
      if (((i - x) * (i - x)) + ((j - y) * (j - y)) < (radius * radius) + radius) {
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
// Inspired by brogue desing
//
static void room_gen_design_cross_room(Gamep g, RoomGen *grid)
{
  TRACE_NO_INDENT();

  int room_width;
  int room_height;
  int room_width2;
  int room_height2;
  int roomX;
  int roomY;
  int roomX2;
  int roomY2;

  room_width  = pcg_random_range(3, 12);
  roomX       = pcg_random_range(std::max(0, MAP_WIDTH / 2 - (room_width - 1)),
                                 std::min((int) MAP_WIDTH, (int) MAP_WIDTH / 2));
  room_width2 = pcg_random_range(4, 20);
  roomX2      = (roomX + (room_width / 2) + pcg_random_range(0, 2) + pcg_random_range(0, 2) - 3) - (room_width2 / 2);

  room_height = pcg_random_range(3, 7);
  roomY       = ((MAP_HEIGHT / 2) - room_height);

  room_height2 = pcg_random_range(2, 5);
  roomY2       = ((MAP_HEIGHT / 2) - room_height2 - (pcg_random_range(0, 2) + pcg_random_range(0, 1)));

  room_gen_draw_rectangle(g, grid, roomX - 5, roomY + 5, room_width, room_height, CHARMAP_FLOOR);
  room_gen_draw_rectangle(g, grid, roomX2 - 5, roomY2 + 5, room_width2, room_height2, CHARMAP_FLOOR);
}

//
// Inspired by brogue desing
//
static void room_gen_design_cross_room_symmetrical(Gamep g, RoomGen *grid)
{
  TRACE_NO_INDENT();

  int major_width;
  int major_height;
  int minor_width;
  int minor_height;

  major_width  = pcg_random_range(4, 8);
  major_height = pcg_random_range(4, 5);

  minor_width = pcg_random_range(3, 4);
  if (major_height % 2 == 0) {
    minor_width -= 1;
  }

  minor_height = 3; // pcg_random_range(2, 3);
  if (major_width % 2 == 0) {
    minor_height -= 1;
  }

  room_gen_draw_rectangle(g, grid, (MAP_WIDTH - major_width) / 2, (MAP_HEIGHT - minor_height) / 2, major_width,
                          minor_height, CHARMAP_FLOOR);
  room_gen_draw_rectangle(g, grid, (MAP_WIDTH - minor_width) / 2, (MAP_HEIGHT - major_height) / 2, minor_width,
                          major_height, CHARMAP_FLOOR);
}

static void room_gen_design_small_room(Gamep g, RoomGen *grid)
{
  TRACE_NO_INDENT();

  int width;
  int height;

  width  = pcg_random_range(3, 6);
  height = pcg_random_range(3, 6);

  room_gen_draw_rectangle(g, grid, (MAP_WIDTH - width) / 2, (MAP_HEIGHT - height) / 2, width, height, CHARMAP_FLOOR);
}

static void room_gen_design_medium_room(Gamep g, RoomGen *grid)
{
  TRACE_NO_INDENT();

  int width;
  int height;

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

  int i;
  int x;
  int y;
  int minX;
  int maxX;
  int minY;
  int maxY;
  int chunkCount = pcg_random_range(2, 8);

  room_gen_draw_circle(g, grid, MAP_WIDTH / 2, MAP_HEIGHT / 2, 2, CHARMAP_FLOOR);

  minX = (MAP_WIDTH / 2) - 3;
  maxX = (MAP_WIDTH / 2) + 3;
  minY = (MAP_HEIGHT / 2) - 3;
  maxY = (MAP_HEIGHT / 2) + 3;

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
[[nodiscard]] static bool rooms_dump_one(Gamep g, FILE *out, int which)
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
  if (compiler_unused) {
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
  if (out == nullptr) {
    CROAK("could not write to %s", f.c_str());
  }

  std::println(out, "//");
  std::println(out, "// Copyright goblinhack@gmail.com");
  std::println(out, "//");
  std::println(out, "");
  std::println(out, "#include \"my_callstack.hpp\"");
  std::println(out, "#include \"my_charmap.hpp\"");
  std::println(out, "#include \"my_level.hpp\"");
  std::println(out, "");
  std::println(out, "//");
  std::println(out, "// {} rooms of type '{}' from seed '{}'", n, name, game_seed_name_get(g));
  std::println(out, "//");
  std::println(out, "void rooms_{}(Gamep g)", name);
  std::println(out, "{{");
  std::println(out, "  TRACE_NO_INDENT();");
  std::println(out, "");

  for (auto r = 0; r < n; r++) {
    (void) rooms_dump_one(g, out, which);
  }

  std::println(out, "}}");

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
