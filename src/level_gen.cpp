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
#include <array>
#include <map>
#include <stdarg.h>
#include <thread>
#include <unordered_map>
#include <vector>

//
// How many times to try creating a single level
//
static const int MAX_LEVELS                        = 100;
static const int MAX_LEVEL_GEN_TRIES_FOR_SAME_SEED = 1000000;

//
// How many times to try adding a room
//
static const int MAX_LEVEL_GEN_TRIES_CREATE_ROOM = 1000;

//
// How many times to try adding the first room
//
static const int MAX_LEVEL_GEN_TRIES_CREATE_FIRST_ROOM = 200;

//
// How many times to try placing a random room next to a door
//
static const int MAX_LEVEL_GEN_ROOM_PLACE_TRIES = 200;

//
// After this length, corridors become bridges
//
static const int MAX_LEVEL_GEN_MIN_BRIDGE_LEN = 6;

//
// How many times to try to replace part of the dungeon
//
static const int MAX_LEVEL_GEN_FRAGMENT_TRIES = 100;

//
// The max amount of fragments to create
//
static const int MAX_LEVEL_GEN_FRAGMENTS = 20;

//
// How far away the start and exit should be at a minimum
//
static const int MIN_LEVEL_EXIT_DISTANCE = MAP_WIDTH / 4;

//
// How many rooms qualify as a dungeon. This increases with depth.
//
static const int MIN_LEVEL_ROOM_COUNT = 15;

//
// Cellular auto fill prob
//
static const int LEVEL_BLOB_GEN_FILL_PROB = 1200;

//
// Chance of creating a pool on a level
//
static const int LEVEL_BLOB_GEN_PROB = 80;

//
// Chances of creating, tested in the following order, with the default being water
//
static const int LEVEL_BLOB_LAVA_GEN_PROB  = 5;
static const int LEVEL_BLOB_CHASM_GEN_PROB = 10;

class Cell;
class Room;
class LevelGen;

//
// Statistics
//
static int level_create_fail;
static int level_place_first_room_fail;
static int level_place_subsequent_room_fail;
static int level_tried_to_place_existing_room_fail;
static int level_find_door_fail_count;
static int level_not_enough_rooms;
static int level_no_exit_room;

static void level_gen_dump(Gamep g, class LevelGen *l, const char *msg = nullptr);

class Cell
{
private:
public:
  Cell(void) {}
  ~Cell(void) {}

  //
  // Room char
  //
  char c = {};

  //
  // The room this cell was sourced from
  //
  class Room *room = {};
};

class LevelGen
{
private:
public:
  LevelGen(void)
  {
    for (int y = 0; y < MAP_HEIGHT; y++) {
      for (int x = 0; x < MAP_WIDTH; x++) {
        data[ x ][ y ].c    = CHARMAP_EMPTY;
        data[ x ][ y ].room = nullptr;
      }
    }
  }
  ~LevelGen(void) {}

  //
  // Dump levels as generating them, enable via -debug
  //
  bool debug {};

  //
  // This is a copy of the game seed
  //
  std::string seed;
  uint32_t    seed_num {};

  //
  // Sub level
  //
  int which {};

  //
  // The number of rooms to aim for for a given depth.
  //
  int min_room_count {};
  int max_room_count {};

  //
  // How many room fragments we've added
  //
  int fragment_count {};

  //
  // The starting room
  //
  class Room *room_first = {};

  //
  // Used to make sure we place each room uniquely per level
  //
  std::unordered_map< class Room *, bool > rooms_placed;

  //
  // Which doors we expanded off of.
  //
  std::map< point, bool > doors_walked;

  //
  // All level doors.
  //
  std::vector< point > doors_not_explored;

  //
  // Rooms that can reach each other via a door.
  //
  std::map< std::pair< class Room *, class Room * >, bool > rooms_connected;

  //
  // Additional adjacent rooms connected from the first pass
  //
  int rooms_adj_connected = {};

  //
  // Only one exit per level
  //
  bool has_placed_exit = {};

  //
  // Where the player start is
  //
  point start;

  //
  // Where the exit is
  //
  point exit;

  //
  // Level tiles and room info
  //
  Cell data[ MAP_WIDTH ][ MAP_HEIGHT ];

  Cave cave = {};
};

typedef enum {
  ROOM_TYPE_START,
#define ROOM_TYPE_FIRST ROOM_TYPE_START
  ROOM_TYPE_NORMAL,
  ROOM_TYPE_EXIT,
  ROOM_TYPE_MAX
} RoomType;

class Room
{
private:
public:
  Room(void) {}
  ~Room(void) { myfree(data); }

  //
  // Globally unique
  //
  int id = {};

  //
  // Chance of appearing
  //
  int chance = {CHANCE_NORMAL};

  //
  // Start room?
  //
  RoomType room_type;

  //
  // Room size
  //
  int width  = {};
  int height = {};

  //
  // Room data
  //
  char *data = {};

  //
  // For keeping track of source location
  //
  const char *file = {};
  int         line = {};

  //
  // All doors in the room
  //
  std::vector< point > doors;

  //
  // Points adjacent to doors
  //
  std::vector< point > door_adjacent_tile;
};

static int                         room_no;
static std::vector< class Room * > rooms_all[ ROOM_TYPE_MAX ];

class FragmentAlt
{
private:
public:
  FragmentAlt(void) {}
  ~FragmentAlt(void) { myfree(data); }

  //
  // Globally unique
  //
  int id = {};

  //
  // Chance of appearing
  //
  int chance = {CHANCE_NORMAL};

  //
  // FragmentAlt size
  //
  int width  = {};
  int height = {};

  //
  // FragmentAlt data
  //
  char *data = {};

  //
  // For keeping track of source location
  //
  const char *file = {};
  int         line = {};
};

static int                                fragment_alt_no;
static std::vector< class FragmentAlt * > fragment_alts_all;
static std::vector< class FragmentAlt * > fragment_alts_curr;

class Fragment
{
private:
public:
  Fragment(void) {}
  ~Fragment(void) { myfree(data); }

  //
  // Globally unique
  //
  int id = {};

  //
  // Chance of appearing
  //
  int chance = {CHANCE_NORMAL};

  //
  // Fragment size
  //
  int width  = {};
  int height = {};

  //
  // Fragment data
  //
  char *data = {};

  //
  // For keeping track of source location
  //
  const char *file = {};
  int         line = {};

  //
  // Alternatives for this fragment
  //
  std::vector< class FragmentAlt * > fragment_alts;
};

static int                             fragment_no;
static std::vector< class Fragment * > fragments_all;
static std::vector< class Fragment * > fragments_curr;

//
// Read a room char
//
static char room_char(Gamep g, class Room *r, int x, int y)
{
  if (x < 0) {
    return CHARMAP_EMPTY;
  }
  if (y < 0) {
    return CHARMAP_EMPTY;
  }
  if (x >= r->width) {
    return CHARMAP_EMPTY;
  }
  if (y >= r->height) {
    return CHARMAP_EMPTY;
  }

  return r->data[ (y * r->width) + x ];
}

//
// Scan the room now it is created, for any things of interest
//
static void room_scan(Gamep g, class Room *r)
{
  TRACE_NO_INDENT();

  for (int y = 0; y < r->height; y++) {
    for (int x = 0; x < r->width; x++) {
      auto c = room_char(g, r, x, y);

      if (c == CHARMAP_JOIN) {
        point p(x, y);
        r->doors.push_back(p);

        //
        // Look for tiles next to the door. We will use these to check if room placement works
        //
        if (room_char(g, r, x - 1, y) != CHARMAP_EMPTY) {
          r->door_adjacent_tile.push_back(point(x - 1, y));
        }
        if (room_char(g, r, x + 1, y) != CHARMAP_EMPTY) {
          r->door_adjacent_tile.push_back(point(x + 1, y));
        }
        if (room_char(g, r, x, y - 1) != CHARMAP_EMPTY) {
          r->door_adjacent_tile.push_back(point(x, y - 1));
        }
        if (room_char(g, r, x, y + 1) != CHARMAP_EMPTY) {
          r->door_adjacent_tile.push_back(point(x, y + 1));
        }
      }
    }
  }
}

//
// Rotate the current room clockwise and put that into a new room
//
static class Room *room_rotate(Gamep g, class Room *r)
{
  TRACE_NO_INDENT();

  auto n = new Room();
  rooms_all[ r->room_type ].push_back(n);

  n->id        = room_no++;
  n->chance    = r->chance;
  n->room_type = r->room_type;
  n->file      = r->file;
  n->line      = r->line;
  n->width     = r->height;
  n->height    = r->width;
  n->data      = (char *) myzalloc(r->width * r->height, "room data");

  for (int y = 0; y < r->height; y++) {
    for (int x = 0; x < r->width; x++) {
      int nx                          = n->width - y - 1;
      int ny                          = x;
      n->data[ (ny * n->width) + nx ] = r->data[ (y * r->width) + x ];
    }
  }

  room_scan(g, n);

  return n;
}

//
// Flip the current room horizontally and put that into a new room
//
static class Room *room_flip_horiz(Gamep g, class Room *r)
{
  TRACE_NO_INDENT();

  auto n = new Room();
  rooms_all[ r->room_type ].push_back(n);

  n->id        = room_no++;
  n->chance    = r->chance;
  n->room_type = r->room_type;
  n->file      = r->file;
  n->line      = r->line;
  n->width     = r->width;
  n->height    = r->height;
  n->data      = (char *) myzalloc(r->width * r->height, "room data");

  for (int y = 0; y < r->height; y++) {
    for (int x = 0; x < r->width; x++) {
      int nx                          = r->width - x - 1;
      int ny                          = y;
      n->data[ (ny * r->width) + nx ] = r->data[ (y * r->width) + x ];
    }
  }

  room_scan(g, n);

  return n;
}

//
// Add a room and copies with all possible rotations
//
void room_add(Gamep g, int chance, bool check_exits, const char *file, int line, ...)
{
  TRACE_NO_INDENT();

  va_list ap;
  int     room_width  = 0;
  int     room_height = 0;

  //
  // We scan the room to work out the room type
  //
  RoomType room_type = ROOM_TYPE_NORMAL;

  //
  // First scan, get width and height
  //
  va_start(ap, line);

  for (;;) {
    const char *room_line = va_arg(ap, const char *);
    if (! room_line) {
      break;
    }

    int this_line_width = (int) strlen(room_line);

    if (! room_width) {
      //
      // Get the room width
      //
      room_width = this_line_width;
    } else {
      //
      // Check width is constant
      //
      if (room_width != this_line_width) {
        DIE("room has inconsistent width in room %s:%d", file, line);
        return;
      }
    }

    //
    // Check the room contents are known characters
    //
    for (auto i = 0; i < room_width; i++) {
      switch (room_line[ i ]) {
        case CHARMAP_BARREL : break;
        case CHARMAP_BRAZIER : break;
        case CHARMAP_BRIDGE : break;
        case CHARMAP_CHASM : break;
        case CHARMAP_CHASM_50 : break;
        case CHARMAP_CORRIDOR : break;
        case CHARMAP_DOOR : break;
        case CHARMAP_DRY_GRASS : break;
        case CHARMAP_EMPTY : break;
        case CHARMAP_EXIT : room_type = ROOM_TYPE_EXIT; break;
        case CHARMAP_FLOOR : break;
        case CHARMAP_FLOOR_50 : break;
        case CHARMAP_FOLIAGE : break;
        case CHARMAP_JOIN : break;
        case CHARMAP_KEY : break;
        case CHARMAP_LAVA : break;
        case CHARMAP_MOB1 : break;
        case CHARMAP_MOB2 : break;
        case CHARMAP_MONST1 : break;
        case CHARMAP_MONST2 : break;
        case CHARMAP_PILLAR : break;
        case CHARMAP_SECRET_DOOR : break;
        case CHARMAP_START : room_type = ROOM_TYPE_START; break;
        case CHARMAP_TELEPORT : break;
        case CHARMAP_TRAP : break;
        case CHARMAP_TREASURE1 : break;
        case CHARMAP_TREASURE2 : break;
        case CHARMAP_WALL : break;
        case CHARMAP_WATER : break;
        default : DIE("room has unknown char [%c] in room %s:%d", room_line[ i ], file, line); return;
      }
    }

    room_height++;
  }

  va_end(ap);

  //
  // Check the room sizes
  //
  if (! room_width) {
    DIE("room has no width in room %s:%d", file, line);
    return;
  }
  if (! room_height) {
    DIE("room has no height in room %s:%d", file, line);
    return;
  }
  if (room_width >= MAP_WIDTH) {
    DIE("room is too wide in room %s:%d", file, line);
    return;
  }
  if (room_height >= MAP_HEIGHT) {
    DIE("room is too tall in room %s:%d", file, line);
    return;
  }

  //
  // Allocate space for the room
  //
  class Room *r = new Room();
  rooms_all[ room_type ].push_back(r);

  r->id        = room_no++;
  r->chance    = chance;
  r->room_type = room_type;
  r->file      = file;
  r->line      = line;
  r->width     = room_width;
  r->height    = room_height;
  r->data      = (char *) myzalloc(room_width * room_height, "room data");

  //
  // Keep track of exits so we can sanity check the edges of the room
  //
  bool has_exit_up {};
  bool has_exit_down {};
  bool has_exit_left {};
  bool has_exit_right {};

  //
  // Now read the room again
  //
  va_start(ap, line);

  for (int y = 0; y < r->height; y++) {
    const char *room_line = va_arg(ap, char *);
    for (int x = 0; x < r->width; x++) {
      auto c = room_line[ x ];

      //
      // Keep track of exits
      //
      if (c == CHARMAP_JOIN) {
        if (y == 0) {
          has_exit_up = true;
        }
        if (y == r->height - 1) {
          has_exit_down = true;
        }
        if (x == 0) {
          has_exit_left = true;
        }
        if (x == r->width - 1) {
          has_exit_right = true;
        }
      }

      r->data[ (y * r->width) + x ] = room_line[ x ];
    }
  }

  va_end(ap);

  if (! has_exit_up && ! has_exit_down && ! has_exit_left && ! has_exit_right) {
    DIE("room has no exits %s:%d", file, line);
    return;
  }

  //
  // Sanity check on exits that we have no tiles in the same column or row
  // as an exit; it makes it harder to join rooms together
  //
  if (check_exits) {
    for (int y = 0; y < r->height; y++) {
      for (int x = 0; x < r->width; x++) {
        auto c = r->data[ (y * r->width) + x ];
        if ((c != CHARMAP_EMPTY) && (c != CHARMAP_JOIN)) {

          //
          // Exclude corners
          //
          if ((x == 0) && (y == 0)) {
            continue;
          }
          if ((x == 0) && (y == r->height - 1)) {
            continue;
          }
          if ((x == r->width - 1) && (y == 0)) {
            continue;
          }
          if ((x == r->width - 1) && (y == r->height - 1)) {
            continue;
          }

          if ((y == 0) && has_exit_up) {
            DIE("room has exit up and tiles in same row %s:%d", file, line);
            return;
          }
          if ((y == r->height - 1) && has_exit_down) {
            DIE("room has exit down and tiles in same row %s:%d", file, line);
            return;
          }
          if ((x == 0) && has_exit_left) {
            DIE("room has exit left and tiles in same column %s:%d", file, line);
            return;
          }
          if ((x == r->width - 1) && has_exit_right) {
            DIE("room has exit right and tiles in same column %s:%d", file, line);
            return;
          }
        }
      }
    }
  }

  //
  // Make alternate rooms
  //
  room_rotate(g, room_rotate(g, room_rotate(g, r)));
  room_rotate(g, room_rotate(g, room_rotate(g, room_flip_horiz(g, r))));

  room_scan(g, r);
}

//
// Get a random room.
//
static class Room *room_random_get(Gamep g, class LevelGen *l, RoomType room_type)
{
  TRACE_NO_INDENT();

  if (! rooms_all[ room_type ].size()) {
    DIE("no rooms of type %d", room_type);
  }

  return rooms_all[ room_type ][ pcg_random_range(0, rooms_all[ room_type ].size()) ];
}

//
// Dump a room
//
static void room_dump(Gamep g, class Room *r)
{
  TRACE_NO_INDENT();

  LOG("Room %d %s:%d", r->id, r->file, r->line);

  for (int y = 0; y < r->height; y++) {
    std::string tmp;
    for (int x = 0; x < r->width; x++) {
      tmp += r->data[ (y * r->width) + x ];
    }
    LOG("[%s]", tmp.c_str());
  }

  LOG("-");
}

//
// Dump all rooms
//
void rooms_dump(Gamep g)
{
  TRACE_NO_INDENT();

  for (auto room_type = (int) ROOM_TYPE_FIRST; room_type < (int) ROOM_TYPE_MAX; room_type++) {
    for (auto r : rooms_all[ room_type ]) {
      room_dump(g, r);
    }
  }
}

//
// Can we place a room here on the level?
//
static bool room_can_place_at(Gamep g, class LevelGen *l, class Room *r, point at, int rx, int ry)
{
  //
  // Check we have something to place here.
  //
  char room_c = r->data[ (ry * r->width) + rx ];
  if (unlikely(room_c == CHARMAP_EMPTY)) {
    return true;
  }

  //
  // Where we're placing tiles
  //
  point p(rx + at.x, ry + at.y);

  //
  // We need one tile of edge around rooms.
  //
  if (unlikely(p.x <= 0)) {
    return false;
  }
  if (unlikely(p.x >= MAP_WIDTH - 1)) {
    return false;
  }
  if (unlikely(p.y <= 0)) {
    return false;
  }
  if (unlikely(p.y >= MAP_HEIGHT - 1)) {
    return false;
  }

  //
  // Special door handling
  //
  if (unlikely(room_c == CHARMAP_JOIN)) {
    //
    // Doors can overlap.
    //
    if (l->data[ p.x ][ p.y ].c == CHARMAP_JOIN) {
      return true;
    }
  }

  //
  // Check all adjacent tiles for an adjacent room
  //
  for (int dy = -1; dy <= 1; dy++) {
    for (int dx = -1; dx <= 1; dx++) {
      if (! dx && ! dy) {
        switch (l->data[ p.x + dx ][ p.y + dy ].c) {
          case CHARMAP_JOIN :
          case CHARMAP_EMPTY : break;
          default : return false;
        }
      } else {
        //
        // Allow certain tiles, like water to be adjacent. This way a room can be created
        // right at the water edge.
        //
        switch (l->data[ p.x + dx ][ p.y + dy ].c) {
          case CHARMAP_WATER :
          case CHARMAP_LAVA :
          case CHARMAP_CHASM :
          case CHARMAP_JOIN :
          case CHARMAP_EMPTY : break;
          default : return false;
        }
      }
    }
  }

  //
  // Can place here
  //
  return true;
}

//
// Can we place a room here on the level?
//
static bool room_can_place_at(Gamep g, class LevelGen *l, class Room *r, point at)
{
  //
  // Optimization, check edge tiles first
  //
  for (auto p : r->door_adjacent_tile) {
    if (! room_can_place_at(g, l, r, at, p.x, p.y)) {
      return false;
    }
  }

  //
  // Check the room is clear to be placed here.
  //
  // Also check 1 adjoining tile
  //
  for (int ry = 0; ry < r->height; ry++) {
    for (int rx = 0; rx < r->width; rx++) {
      if (! room_can_place_at(g, l, r, at, rx, ry)) {
        return false;
      }
    }
  }

  //
  // Can place here
  //
  return true;
}

//
// Place a room on the level
//
static void room_place_at(Gamep g, class LevelGen *l, class Room *r, point at)
{
  //
  // The room should be clear to place at this point
  //
  for (int ry = 0; ry < r->height; ry++) {
    for (int rx = 0; rx < r->width; rx++) {
      //
      // Check we have something to place here.
      //
      char room_c = r->data[ (ry * r->width) + rx ];
      if (room_c == CHARMAP_EMPTY) {
        continue;
      }

      //
      // Check if we need to modify tiles when placing
      //
      switch (room_c) {
        case CHARMAP_CHASM_50 :
          if (d100() > 50) {
            room_c = CHARMAP_FLOOR;
          } else {
            room_c = CHARMAP_CHASM;
          }
          break;
        case CHARMAP_FLOOR_50 :
          if (d100() > 50) {
            room_c = CHARMAP_EMPTY;
          } else {
            room_c = CHARMAP_FLOOR;
          }
          break;
        default : break;
      }

      if (room_c == CHARMAP_EMPTY) {
        continue;
      }

      //
      // Where we're placing tiles
      //
      point p(rx + at.x, ry + at.y);

      if (room_c == CHARMAP_START) {
        l->start = p;
      }
      if (room_c == CHARMAP_EXIT) {
        l->exit = p;
      }

      class Cell *cell = &l->data[ p.x ][ p.y ];
      cell->c          = room_c;
      cell->room       = r;
    }
  }

  l->rooms_placed[ r ] = true;
}

//
// Clean up rooms
//
void rooms_fini(Gamep g)
{
  TRACE_NO_INDENT();

  for (auto room_type = (int) ROOM_TYPE_FIRST; room_type < (int) ROOM_TYPE_MAX; room_type++) {
    for (auto r : rooms_all[ room_type ]) {
      delete r;
    }
  }
}

//
// Read a fragment_alt char
//
static char fragment_alt_char(Gamep g, class FragmentAlt *r, int x, int y)
{
  if (x < 0) {
    return CHARMAP_EMPTY;
  }
  if (y < 0) {
    return CHARMAP_EMPTY;
  }
  if (x >= r->width) {
    return CHARMAP_EMPTY;
  }
  if (y >= r->height) {
    return CHARMAP_EMPTY;
  }

  return r->data[ (y * r->width) + x ];
}

//
// Rotate the current fragment_alt clockwise and put that into a new fragment_alt
//
static class FragmentAlt *fragment_alt_rotate(Gamep g, class FragmentAlt *r)
{
  TRACE_NO_INDENT();

  auto n = new FragmentAlt();
  fragment_alts_all.push_back(n);
  fragment_alts_curr.push_back(n);

  n->id     = fragment_no++;
  n->chance = r->chance;
  n->file   = r->file;
  n->line   = r->line;
  n->width  = r->height;
  n->height = r->width;
  n->data   = (char *) myzalloc(r->width * r->height, "fragment_alt data");

  for (int y = 0; y < r->height; y++) {
    for (int x = 0; x < r->width; x++) {
      int nx                          = n->width - y - 1;
      int ny                          = x;
      n->data[ (ny * n->width) + nx ] = r->data[ (y * r->width) + x ];
    }
  }

  return n;
}

//
// Flip the current fragment_alt horizontally and put that into a new fragment_alt
//
static class FragmentAlt *fragment_alt_flip_horiz(Gamep g, class FragmentAlt *r)
{
  TRACE_NO_INDENT();

  auto n = new FragmentAlt();
  fragment_alts_all.push_back(n);
  fragment_alts_curr.push_back(n);

  n->id     = fragment_alt_no++;
  n->chance = r->chance;
  n->file   = r->file;
  n->line   = r->line;
  n->width  = r->width;
  n->height = r->height;
  n->data   = (char *) myzalloc(r->width * r->height, "fragment_alt data");

  for (int y = 0; y < r->height; y++) {
    for (int x = 0; x < r->width; x++) {
      int nx                          = r->width - x - 1;
      int ny                          = y;
      n->data[ (ny * r->width) + nx ] = r->data[ (y * r->width) + x ];
    }
  }

  return n;
}

//
// Add a fragment_alt and copies with all possible rotations
//
bool fragment_alt_add(Gamep g, int chance, const char *file, int line, ...)
{
  TRACE_NO_INDENT();

  va_list ap;
  int     fragment_alt_width  = 0;
  int     fragment_alt_height = 0;

  //
  // First scan, get width and height
  //
  va_start(ap, line);

  for (;;) {
    const char *fragment_alt_line = va_arg(ap, const char *);
    if (! fragment_alt_line) {
      break;
    }

    int this_line_width = (int) strlen(fragment_alt_line);

    if (! fragment_alt_width) {
      //
      // Get the fragment_alt width
      //
      fragment_alt_width = this_line_width;
    } else {
      //
      // Check width is constant
      //
      if (fragment_alt_width != this_line_width) {
        DIE("fragment_alt has inconsistent width in fragment_alt %s:%d", file, line);
        return false;
      }
    }

    //
    // Check the fragment_alt contents are known characters
    //
    for (auto i = 0; i < fragment_alt_width; i++) {
      switch (fragment_alt_line[ i ]) {
        case CHARMAP_BARREL : break;
        case CHARMAP_BRAZIER : break;
        case CHARMAP_BRIDGE : break;
        case CHARMAP_CHASM : break;
        case CHARMAP_CHASM_50 : break;
        case CHARMAP_CORRIDOR : break;
        case CHARMAP_DOOR : break;
        case CHARMAP_DRY_GRASS : break;
        case CHARMAP_EMPTY : break;
        case CHARMAP_EXIT : break;
        case CHARMAP_FLOOR : break;
        case CHARMAP_FLOOR_50 : break;
        case CHARMAP_FOLIAGE : break;
        case CHARMAP_JOIN : break;
        case CHARMAP_KEY : break;
        case CHARMAP_LAVA : break;
        case CHARMAP_MOB1 : break;
        case CHARMAP_MOB2 : break;
        case CHARMAP_MONST1 : break;
        case CHARMAP_MONST2 : break;
        case CHARMAP_PILLAR : break;
        case CHARMAP_SECRET_DOOR : break;
        case CHARMAP_START : break;
        case CHARMAP_TELEPORT : break;
        case CHARMAP_TRAP : break;
        case CHARMAP_TREASURE1 : break;
        case CHARMAP_TREASURE2 : break;
        case CHARMAP_WALL : break;
        case CHARMAP_WATER : break;
        default :
          DIE("fragment_alt has unknown char [%c] in fragment_alt %s:%d", fragment_alt_line[ i ], file, line);
          return false;
      }
    }

    fragment_alt_height++;
  }

  va_end(ap);

  //
  // Check the fragment_alt sizes
  //
  if (! fragment_alt_width) {
    DIE("fragment_alt has no width in fragment_alt %s:%d", file, line);
    return false;
  }
  if (! fragment_alt_height) {
    DIE("fragment_alt has no height in fragment_alt %s:%d", file, line);
    return false;
  }
  if (fragment_alt_width >= MAP_WIDTH) {
    DIE("fragment_alt is too wide in fragment_alt %s:%d", file, line);
    return false;
  }
  if (fragment_alt_height >= MAP_HEIGHT) {
    DIE("fragment_alt is too tall in fragment_alt %s:%d", file, line);
    return false;
  }

  //
  // Allocate space for the fragment_alt
  //
  class FragmentAlt *r = new FragmentAlt();
  fragment_alts_all.push_back(r);

  fragment_alts_curr.clear();
  fragment_alts_curr.push_back(r);

  r->id     = fragment_alt_no++;
  r->chance = chance;
  r->file   = file;
  r->line   = line;
  r->width  = fragment_alt_width;
  r->height = fragment_alt_height;
  r->data   = (char *) myzalloc(fragment_alt_width * fragment_alt_height, "fragment_alt data");

  //
  // Now read the fragment_alt again
  //
  va_start(ap, line);

  for (int y = 0; y < r->height; y++) {
    const char *fragment_alt_line = va_arg(ap, char *);
    for (int x = 0; x < r->width; x++) {
      auto c = fragment_alt_line[ x ];

      r->data[ (y * r->width) + x ] = c;
    }
  }

  va_end(ap);

  //
  // Make alternate fragment_alts
  //
  fragment_alt_rotate(g, fragment_alt_rotate(g, fragment_alt_rotate(g, r)));
  fragment_alt_rotate(g, fragment_alt_rotate(g, fragment_alt_rotate(g, fragment_alt_flip_horiz(g, r))));

  //
  // Push the alternatives onto the end of each fragment
  //
  int i = 0;
  for (auto f : fragments_curr) {
    f->fragment_alts.push_back(fragment_alts_curr[ i++ ]);
  }

  return true;
}

//
// Get a random alt fragment.
//
static class FragmentAlt *fragment_alt_random_get(Gamep g, class LevelGen *l, Fragment *f)
{
  TRACE_NO_INDENT();

  if (! f->fragment_alts.size()) {
    return nullptr;
  }

  int tries = 0;
  while (tries++ < MAX_LEVEL_GEN_FRAGMENT_TRIES) {
    auto a = f->fragment_alts[ pcg_random_range(0, f->fragment_alts.size()) ];
    if (d10000() < a->chance) {
      return a;
    }
  }
  return nullptr;
}

//
// Dump a fragment_alt
//
static void fragment_alt_dump(Gamep g, class FragmentAlt *r)
{
  TRACE_NO_INDENT();

  LOG("FragmentAlt %d %s:%d", r->id, r->file, r->line);

  for (int y = 0; y < r->height; y++) {
    std::string tmp;
    for (int x = 0; x < r->width; x++) {
      tmp += r->data[ (y * r->width) + x ];
    }
    LOG("[%s]", tmp.c_str());
  }

  LOG("-");
}

//
// Dump all fragment_alts
//
void fragment_alts_dump(Gamep g)
{
  TRACE_NO_INDENT();

  for (auto r : fragment_alts_all) {
    fragment_alt_dump(g, r);
  }
}

//
// Clean up fragment_alts
//
void fragment_alts_fini(Gamep g)
{
  TRACE_NO_INDENT();

  for (auto r : fragment_alts_all) {
    delete r;
  }
}

//
// Read a fragment char
//
static char fragment_char(Gamep g, class Fragment *r, int x, int y)
{
  if (x < 0) {
    return CHARMAP_EMPTY;
  }
  if (y < 0) {
    return CHARMAP_EMPTY;
  }
  if (x >= r->width) {
    return CHARMAP_EMPTY;
  }
  if (y >= r->height) {
    return CHARMAP_EMPTY;
  }

  return r->data[ (y * r->width) + x ];
}

//
// Rotate the current fragment clockwise and put that into a new fragment
//
static class Fragment *fragment_rotate(Gamep g, class Fragment *r)
{
  TRACE_NO_INDENT();

  auto n = new Fragment();
  fragments_all.push_back(n);
  fragments_curr.push_back(n);

  n->id     = fragment_no++;
  n->chance = r->chance;
  n->file   = r->file;
  n->line   = r->line;
  n->width  = r->height;
  n->height = r->width;
  n->data   = (char *) myzalloc(r->width * r->height, "fragment data");

  for (int y = 0; y < r->height; y++) {
    for (int x = 0; x < r->width; x++) {
      int nx                          = n->width - y - 1;
      int ny                          = x;
      n->data[ (ny * n->width) + nx ] = r->data[ (y * r->width) + x ];
    }
  }

  return n;
}

//
// Flip the current fragment horizontally and put that into a new fragment
//
static class Fragment *fragment_flip_horiz(Gamep g, class Fragment *r)
{
  TRACE_NO_INDENT();

  auto n = new Fragment();
  fragments_all.push_back(n);
  fragments_curr.push_back(n);

  n->id     = fragment_no++;
  n->chance = r->chance;
  n->file   = r->file;
  n->line   = r->line;
  n->width  = r->width;
  n->height = r->height;
  n->data   = (char *) myzalloc(r->width * r->height, "fragment data");

  for (int y = 0; y < r->height; y++) {
    for (int x = 0; x < r->width; x++) {
      int nx                          = r->width - x - 1;
      int ny                          = y;
      n->data[ (ny * r->width) + nx ] = r->data[ (y * r->width) + x ];
    }
  }

  return n;
}

//
// Add a fragment and copies with all possible rotations
//
bool fragment_add(Gamep g, int chance, const char *file, int line, ...)
{
  TRACE_NO_INDENT();

  va_list ap;
  int     fragment_width  = 0;
  int     fragment_height = 0;

  //
  // First scan, get width and height
  //
  va_start(ap, line);

  for (;;) {
    const char *fragment_line = va_arg(ap, const char *);
    if (! fragment_line) {
      break;
    }

    int this_line_width = (int) strlen(fragment_line);

    if (! fragment_width) {
      //
      // Get the fragment width
      //
      fragment_width = this_line_width;
    } else {
      //
      // Check width is constant
      //
      if (fragment_width != this_line_width) {
        DIE("fragment has inconsistent width in fragment %s:%d", file, line);
        return false;
      }
    }

    //
    // Check the fragment contents are known characters
    //
    for (auto i = 0; i < fragment_width; i++) {
      switch (fragment_line[ i ]) {
        case CHARMAP_BARREL : break;
        case CHARMAP_BRAZIER : break;
        case CHARMAP_BRIDGE : break;
        case CHARMAP_CHASM : break;
        case CHARMAP_CHASM_50 : break;
        case CHARMAP_CORRIDOR : break;
        case CHARMAP_DOOR : break;
        case CHARMAP_DRY_GRASS : break;
        case CHARMAP_EMPTY : break;
        case CHARMAP_EXIT : break;
        case CHARMAP_FLOOR : break;
        case CHARMAP_FLOOR_50 : break;
        case CHARMAP_FOLIAGE : break;
        case CHARMAP_JOIN : break;
        case CHARMAP_KEY : break;
        case CHARMAP_LAVA : break;
        case CHARMAP_MOB1 : break;
        case CHARMAP_MOB2 : break;
        case CHARMAP_MONST1 : break;
        case CHARMAP_MONST2 : break;
        case CHARMAP_PILLAR : break;
        case CHARMAP_SECRET_DOOR : break;
        case CHARMAP_START : break;
        case CHARMAP_TELEPORT : break;
        case CHARMAP_TRAP : break;
        case CHARMAP_TREASURE1 : break;
        case CHARMAP_TREASURE2 : break;
        case CHARMAP_WALL : break;
        case CHARMAP_WATER : break;
        case CHARMAP_WILDCARD : break;
        default :
          DIE("fragment has unknown char [%c] in fragment %s:%d", fragment_line[ i ], file, line);
          return false;
      }
    }

    fragment_height++;
  }

  va_end(ap);

  //
  // Check the fragment sizes
  //
  if (! fragment_width) {
    DIE("fragment has no width in fragment %s:%d", file, line);
    return false;
  }
  if (! fragment_height) {
    DIE("fragment has no height in fragment %s:%d", file, line);
    return false;
  }
  if (fragment_width >= MAP_WIDTH) {
    DIE("fragment is too wide in fragment %s:%d", file, line);
    return false;
  }
  if (fragment_height >= MAP_HEIGHT) {
    DIE("fragment is too tall in fragment %s:%d", file, line);
    return false;
  }

  //
  // Allocate space for the fragment
  //
  class Fragment *r = new Fragment();
  fragments_all.push_back(r);

  fragments_curr.clear();
  fragments_curr.push_back(r);

  r->id     = fragment_no++;
  r->chance = chance;
  r->file   = file;
  r->line   = line;
  r->width  = fragment_width;
  r->height = fragment_height;
  r->data   = (char *) myzalloc(fragment_width * fragment_height, "fragment data");

  //
  // Now read the fragment again
  //
  va_start(ap, line);

  for (int y = 0; y < r->height; y++) {
    const char *fragment_line = va_arg(ap, char *);
    for (int x = 0; x < r->width; x++) {
      auto c = fragment_line[ x ];

      r->data[ (y * r->width) + x ] = c;
    }
  }

  va_end(ap);

  //
  // Make alternate fragments
  //
  fragment_rotate(g, fragment_rotate(g, fragment_rotate(g, r)));
  fragment_rotate(g, fragment_rotate(g, fragment_rotate(g, fragment_flip_horiz(g, r))));

  return true;
}

//
// Get a random fragment.
//
static class Fragment *fragment_random_get(Gamep g, class LevelGen *l)
{
  TRACE_NO_INDENT();

  if (! fragments_all.size()) {
    DIE("no fragments");
  }

  int tries = 0;
  while (tries++ < MAX_LEVEL_GEN_FRAGMENT_TRIES) {
    auto f = fragments_all[ pcg_random_range(0, fragments_all.size()) ];
    if (d10000() < f->chance) {
      return f;
    }
  }
  return nullptr;
}

//
// Dump a fragment
//
static void fragment_dump(Gamep g, class Fragment *r)
{
  TRACE_NO_INDENT();

  LOG("Fragment %d %s:%d", r->id, r->file, r->line);

  for (int y = 0; y < r->height; y++) {
    std::string tmp;
    for (int x = 0; x < r->width; x++) {
      tmp += r->data[ (y * r->width) + x ];
    }
    LOG("[%s]", tmp.c_str());
  }

  LOG("-");
}

//
// Dump all fragments
//
void fragments_dump(Gamep g)
{
  TRACE_NO_INDENT();

  for (auto r : fragments_all) {
    fragment_dump(g, r);
  }
}

//
// Can we match a fragment against the location
//
static bool fragment_match(Gamep g, class LevelGen *l, class Fragment *f, point at)
{
  for (int ry = 0; ry < f->height; ry++) {
    for (int rx = 0; rx < f->width; rx++) {

      auto c = fragment_char(g, f, rx, ry);
      if (c == CHARMAP_WILDCARD) {
        continue;
      }

      point p(rx + at.x, ry + at.y);

      if (unlikely(p.x <= 0)) {
        return false;
      }
      if (unlikely(p.x >= MAP_WIDTH - 1)) {
        return false;
      }
      if (unlikely(p.y <= 0)) {
        return false;
      }
      if (unlikely(p.y >= MAP_HEIGHT - 1)) {
        return false;
      }
      if (c != l->data[ p.x ][ p.y ].c) {
        return false;
      }
    }
  }

  //
  // Match
  //
  return true;
}

//
// Place the fragment
//
static void fragment_put(Gamep g, class LevelGen *l, class Fragment *f, point at)
{
  TRACE_NO_INDENT();

  if (f->fragment_alts.empty()) {
    fragment_dump(g, f);
    DIE("no alternative fragments for fragment");
    return;
  }

  auto a = fragment_alt_random_get(g, l, f);
  if (! a) {
    return;
  }

  for (int ry = 0; ry < f->height; ry++) {
    for (int rx = 0; rx < f->width; rx++) {

      auto c = fragment_alt_char(g, a, rx, ry);
      if (c == CHARMAP_EMPTY) {
        continue;
      }

      point p(rx + at.x, ry + at.y);

      if (unlikely(p.x <= 0)) {
        continue;
      }
      if (unlikely(p.x >= MAP_WIDTH - 1)) {
        continue;
      }
      if (unlikely(p.y <= 0)) {
        continue;
      }
      if (unlikely(p.y >= MAP_HEIGHT - 1)) {
        continue;
      }

      l->data[ p.x ][ p.y ].c = c;
    }
  }
}

//
// Clean up fragments
//
void fragments_fini(Gamep g)
{
  TRACE_NO_INDENT();

  for (auto r : fragments_all) {
    delete r;
  }
}

//
// Dump a level
//
static void level_gen_dump(Gamep g, class LevelGen *l, const char *msg)
{
  TRACE_NO_INDENT();

  if (msg) {
    LOG("Level: %s.%d (%s)", l->seed.c_str(), l->which, msg);
  } else {
    LOG("Level: %s.%d", l->seed.c_str(), l->which);
  }

  LOG("Seed: %u", l->seed_num);
  LOG("Room count: %d", (int) l->rooms_placed.size());
  LOG("Fragment count: %d", l->fragment_count);

  for (int y = 0; y < MAP_HEIGHT; y++) {
    std::string tmp;
    for (int x = 0; x < MAP_WIDTH; x++) {
      point p(x, y);

      if (l->doors_walked.find(p) != l->doors_walked.end()) {
        if (l->debug) {
          tmp += "D";
        } else {
          tmp += l->data[ x ][ y ].c;
        }
      } else {
        tmp += l->data[ x ][ y ].c;
      }
    }
    LOG("[%s]", tmp.c_str());
  }

  LOG("-");
}

//
// Level stats
//
void level_gen_stats_dump(Gamep g)
{
  TRACE_NO_INDENT();

  LOG("Level errors:");
  LOG("- create level fail:               %d", level_create_fail);
  LOG("- place first room fail:           %d", level_place_first_room_fail);
  LOG("- place subsequent room fail:      %d", level_place_subsequent_room_fail);
  LOG("- find door to place room fail:    %d", level_find_door_fail_count);
  LOG("- tried to place a duplicate room: %d", level_tried_to_place_existing_room_fail);
  LOG("- not enough rooms generated:      %d", level_not_enough_rooms);
  LOG("- no exit room generated:          %d", level_no_exit_room);
}

//
// Update the list of all doors, and return a new unwalked door to use
//
static bool level_gen_random_door_get(Gamep g, class LevelGen *l, point *door_out, class Room **room_out)
{
  TRACE_NO_INDENT();

  l->doors_not_explored.clear();

  //
  // Build a vector of all doors that have not been walked before
  //
  for (int y = 0; y < MAP_HEIGHT; y++) {
    for (int x = 0; x < MAP_WIDTH; x++) {
      //
      // Filter to doors
      //
      if (l->data[ x ][ y ].c != CHARMAP_JOIN) {
        continue;
      }

      point p(x, y);

      //
      // If this door is walked already, ignore it
      //
      if (l->doors_walked.find(p) != l->doors_walked.end()) {
        continue;
      }

      //
      // Add to the candidates
      //
      l->doors_not_explored.push_back(point(x, y));
    }
  }

  //
  // Did we find any new doors?
  //
  if (! l->doors_not_explored.size()) {
    if (unlikely(l->debug)) {
      LOG("no more doors");
    }
    return false;
  }

  //
  // Return a random door
  //
  *door_out = l->doors_not_explored[ pcg_random_range(0, l->doors_not_explored.size()) ];
  *room_out = l->data[ door_out->x ][ door_out->y ].room;

  //
  // Don't try this door again
  //
  l->doors_walked[ *door_out ] = true;

  if (! *room_out) {
    ERR("Found a door with no room");
  }

  return true;
}

//
// Place a room of the given type at a specific door
//
static bool level_gen_place_room_at_door_intersection(Gamep g, LevelGen *l, const point door_other,
                                                      class Room *room_other, const RoomType room_type)
{
  TRACE_NO_INDENT();

  //
  // Try multiple rooms with this door
  //
  int room_place_tries   = 0;
  int room_width_failed  = 0;
  int room_height_failed = 0;

  while (room_place_tries++ < MAX_LEVEL_GEN_ROOM_PLACE_TRIES) {
    //
    // Get a new room we have not placed before to try to place
    //
    auto r = room_random_get(g, l, room_type);
    if (l->rooms_placed.find(r) != l->rooms_placed.end()) {
      level_tried_to_place_existing_room_fail++;
      continue;
    }

    //
    // If a certain size failed, do not try that or bigger again
    //
    if (room_width_failed) {
      if (r->width >= room_width_failed) {
        continue;
      }
      if (r->height >= room_height_failed) {
        continue;
      }
    }

    //
    // For each door in the room, can it be placed to connect to the door passed in?
    //
    for (auto d : r->doors) {
      //
      // Place at the D joining rooms e.g.:
      //
      //       ...
      //     D....
      //       ...
      //
      // ...   ...
      // ....D....
      // ...   ...
      //
      point door_intersection_at = door_other - d;
      if (! room_can_place_at(g, l, r, door_intersection_at)) {
        continue;
      }

      //
      // Place the room
      //
      room_place_at(g, l, r, door_intersection_at);

      //
      // Have placed an exit?
      //
      if (r->room_type == ROOM_TYPE_EXIT) {
        l->has_placed_exit = true;
      }

      //
      // Success
      //
      return true;
    }

    level_place_subsequent_room_fail++;
    room_width_failed  = r->width;
    room_height_failed = r->height;
  }

  //
  // Failed
  //
  return false;
}

//
// Place a room of the given type at a random door
//
static bool level_gen_create_another_room(Gamep g, LevelGen *l, RoomType room_type)
{
  TRACE_NO_INDENT();

  //
  // Find a random door that we have not walked before
  //
  point       door_other;
  class Room *room_other = {};
  if (! level_gen_random_door_get(g, l, &door_other, &room_other)) {
    level_find_door_fail_count++;
    return false;
  }

  //
  // If this door is too close, then switch to a normal room
  //
  if (room_type == ROOM_TYPE_EXIT) {
    if (distance(door_other, l->start) < MIN_LEVEL_EXIT_DISTANCE) {
      room_type = ROOM_TYPE_NORMAL;
    }
  }

  //
  // Try multiple rooms with this door
  //
  if (level_gen_place_room_at_door_intersection(g, l, door_other, room_other, room_type)) {
    return true;
  }

  //
  // Try again
  //
  if (room_type == ROOM_TYPE_EXIT) {
    room_type = ROOM_TYPE_NORMAL;
    return level_gen_place_room_at_door_intersection(g, l, door_other, room_other, room_type);
  }

  return false;
}

//
// The first room has been placed. Place all the rest.
//
static void level_gen_create_remaining_rooms(Gamep g, LevelGen *l)
{
  TRACE_NO_INDENT();

  int attempts = 0;

  //
  // Keep placing rooms until we hit the max allowed
  //
  while ((int) l->rooms_placed.size() < l->max_room_count) {
    if (unlikely(l->debug)) {
      LOG("rooms placed %d (max %d) attempts %d doors-tried %d doors-not-tried %d", (int) l->rooms_placed.size(),
          l->max_room_count, attempts, (int) l->doors_walked.size(), (int) l->doors_not_explored.size());
    }

    //
    // Ensure we loop only so many times
    //
    if (attempts++ > MAX_LEVEL_GEN_TRIES_CREATE_ROOM) {
      if (unlikely(l->debug)) {
        LOG("have tried enough times to place a room");
      }
      break;
    }

    //
    // Ran out of doors to try?
    //
    if ((int) l->doors_walked.size()) {
      if (l->doors_not_explored.empty()) {
        if (unlikely(l->debug)) {
          LOG("have tried all doors");
        }
        break;
      }
    }

    RoomType room_type = ROOM_TYPE_NORMAL;

    //
    // If we have not yet placed an exit room, should we?
    //
    if (! l->has_placed_exit) {
      if (d100() < 50) {
        room_type = ROOM_TYPE_EXIT;
      } else if ((int) l->rooms_placed.size() > l->min_room_count) {
        //
        // If we have the minimum rooms, then likely we're far enough away from
        // the start room now to try placing an exit room.
        //
        if (d100() < 50) {
          room_type = ROOM_TYPE_EXIT;
        }
      } else if (attempts > (MAX_LEVEL_GEN_TRIES_CREATE_ROOM / 2)) {
        //
        // If we're running out of room place attempts, try an exit room
        //
        if (d100() < 50) {
          room_type = ROOM_TYPE_EXIT;
        }
      }
    }

    if (unlikely(l->debug)) {
      level_gen_dump(g, l, "placed another room");
    }

    //
    // Create another room if possible
    //
    level_gen_create_another_room(g, l, room_type);

    //
    // If we are out of doors to walk, no point in continuing.
    //
    if (! l->doors_not_explored.size()) {
      return;
    }
  }
}

//
// Place the first room
//
static bool level_gen_create_first_room(Gamep g, LevelGen *l)
{
  TRACE_NO_INDENT();

  //
  // Choose a random start point for the rooms
  //
  int border = MAP_WIDTH / 4;
  int x;
  int y;

  //
  // Start somewhere central
  //
  x = pcg_random_range(border, MAP_WIDTH - border);
  y = pcg_random_range(border, MAP_HEIGHT - border);

  point at(x, y);

  //
  // Choose a random first room and place it
  //
  auto r = l->room_first = room_random_get(g, l, ROOM_TYPE_START);
  if (! room_can_place_at(g, l, r, at)) {
    return false;
  }

  room_place_at(g, l, r, at);

  //
  // Placed the first room
  //
  if (unlikely(l->debug)) {
    level_gen_dump(g, l, "placed first room");
  }

  return true;
}

static void cave_dump(Gamep g, class LevelGen *l)
{
  uint8_t x, y;

  printf("+");
  for (x = 0; x < MAP_WIDTH; x++) {
    printf("-");
  }
  printf("+");
  printf("\n");

  for (y = 0; y < MAP_HEIGHT; y++) {
    printf("|");
    for (x = 0; x < MAP_WIDTH; x++) {
      if (l->cave.curr[ x + MAP_LEVEL_CELLULAR_BORDER ][ y + MAP_LEVEL_CELLULAR_BORDER ]) {
        printf("x");
      } else {
        printf(" ");
      }
    }
    printf("|");
    printf("\n");
  }

  printf("+");
  for (x = 0; x < MAP_WIDTH; x++) {
    printf("-");
  }
  printf("+");
  printf("\n");
}

//
// Place a single large pool of water/lava/chasm on the level
//
static void level_gen_single_large_blob_in_center(Gamep g, class LevelGen *l, char c)
{
  uint8_t  x, y;
  uint32_t fill_prob       = LEVEL_BLOB_GEN_FILL_PROB;
  int      r1              = 10; // higher r1 gives a more rounded look
  int      r2              = 4;  // larger r2 gives a smaller pool
  int      map_generations = 3;

  //
  // Generate a cave
  //
  cave_create(g, &l->cave, fill_prob, r1, r2, map_generations);

  //
  // Keep a single large blob for the lake
  //
  cave_generation_keep_largest_blob(g, &l->cave);

  //
  // And put in the middle of the level
  //
  cave_generation_center_blob(g, &l->cave);

  if (0) {
    cave_dump(g, l);
    level_gen_dump(g, l);
  }

  for (x = 0; x < MAP_WIDTH; x++) {
    for (y = 0; y < MAP_HEIGHT; y++) {
      if (l->cave.curr[ x + MAP_LEVEL_CELLULAR_BORDER ][ y + MAP_LEVEL_CELLULAR_BORDER ]) {

        switch (l->data[ x ][ y ].c) {
          case CHARMAP_BARREL :
          case CHARMAP_BRAZIER :
          case CHARMAP_BRIDGE :
          case CHARMAP_CHASM :
          case CHARMAP_CORRIDOR :
          case CHARMAP_DOOR :
          case CHARMAP_DRY_GRASS :
          case CHARMAP_EXIT :
          case CHARMAP_FLOOR :
          case CHARMAP_FOLIAGE :
          case CHARMAP_JOIN :
          case CHARMAP_KEY :
          case CHARMAP_LAVA :
          case CHARMAP_MOB1 :
          case CHARMAP_MOB2 :
          case CHARMAP_MONST1 :
          case CHARMAP_MONST2 :
          case CHARMAP_PILLAR :
          case CHARMAP_SECRET_DOOR :
          case CHARMAP_START :
          case CHARMAP_TELEPORT :
          case CHARMAP_TRAP :
          case CHARMAP_TREASURE1 :
          case CHARMAP_TREASURE2 :
          case CHARMAP_WALL :
            //
            // No water
            //
            break;
          case CHARMAP_EMPTY :
            //
            // Perma water
            //
            l->data[ x ][ y ].c = c;
            break;
        }
      }
    }
  }
}

//
// Create rooms from the current seed
//
static class LevelGen *level_gen_create_rooms(Gamep g, int which)
{
  TRACE_NO_INDENT();

  LevelGen *l = {};

  bool add_blob = d100() < LEVEL_BLOB_GEN_PROB;

  for (int level_gen_tries = 0; level_gen_tries < MAX_LEVEL_GEN_TRIES_FOR_SAME_SEED; level_gen_tries++) {
    //
    // Start with a fresh level each try
    //
    if (l) {
      delete l;
      l = nullptr;
    }

    l                 = new LevelGen();
    l->seed           = std::string(game_seed_name_get(g));
    l->which          = which;
    l->min_room_count = MIN_LEVEL_ROOM_COUNT + (which / 10);
    l->max_room_count = l->min_room_count + 10;
    l->debug          = g_opt_debug1;

    //
    // Add a blob of hazard in the center of the level
    //
    if (add_blob) {
      //
      // The blob type
      //
      auto chance    = d100();
      char blob_type = CHARMAP_WATER;

      if (chance < LEVEL_BLOB_LAVA_GEN_PROB) {
        blob_type = CHARMAP_LAVA;
      } else if (chance < LEVEL_BLOB_CHASM_GEN_PROB) {
        blob_type = CHARMAP_CHASM;
      } else {
        blob_type = CHARMAP_WATER;
      }

      level_gen_single_large_blob_in_center(g, l, blob_type);
    }

    //
    // Place the first room
    //
    bool first_room_placed = false;
    for (auto attempts = 0; attempts < MAX_LEVEL_GEN_TRIES_CREATE_FIRST_ROOM; attempts++) {
      if (level_gen_create_first_room(g, l)) {
        first_room_placed = true;
        break;
      }
    }
    if (! first_room_placed) {
      level_place_first_room_fail++;
      continue;
    }

    //
    // Place the remaining rooms
    //
    level_gen_create_remaining_rooms(g, l);

    //
    // Check we have enough rooms. Add a few more for deeper levels.
    //
    if ((int) l->rooms_placed.size() < l->min_room_count) {
      level_not_enough_rooms++;
      continue;
    }

    //
    // Check we have an exit room
    //
    if (! l->has_placed_exit) {
      level_no_exit_room++;
      continue;
    }

    //
    // Success
    //
    return l;
  }

  delete l;
  l = nullptr;

  level_create_fail++;

  if (unlikely(l->debug)) {
    LOG("Failed to create room with seed: %s", game_seed_name_get(g));
  }

  return nullptr;
}

//
// Has to be a tile you could walk on
//
static bool level_gen_tile_is_walkable(Gamep g, class LevelGen *l, int x, int y)
{
  switch (l->data[ x ][ y ].c) {
    case CHARMAP_BARREL : return true;
    case CHARMAP_BRAZIER : return true;
    case CHARMAP_BRIDGE : return true;
    case CHARMAP_CORRIDOR : return true;
    case CHARMAP_DOOR : return true;
    case CHARMAP_DRY_GRASS : return true;
    case CHARMAP_EXIT : return true;
    case CHARMAP_FLOOR : return true;
    case CHARMAP_FOLIAGE : return true;
    case CHARMAP_JOIN : return true;
    case CHARMAP_KEY : return true;
    case CHARMAP_MOB1 : return true;
    case CHARMAP_MOB2 : return true;
    case CHARMAP_MONST1 : return true;
    case CHARMAP_MONST2 : return true;
    case CHARMAP_PILLAR : return true;
    case CHARMAP_SECRET_DOOR : return true;
    case CHARMAP_START : return true;
    case CHARMAP_TELEPORT : return true;
    case CHARMAP_TRAP : return true;
    case CHARMAP_TREASURE1 : return true;
    case CHARMAP_TREASURE2 : return true;
    case CHARMAP_WATER : return true;
    default : return false;
  }
}

//
// Get rid of tiles that go nowhere
//
static bool level_gen_trim_dead_tiles(Gamep g, class LevelGen *l)
{
  TRACE_NO_INDENT();

  bool did_something = false;

  for (int y = 1; y < MAP_HEIGHT - 1; y++) {
    for (int x = 1; x < MAP_WIDTH - 1; x++) {
      switch (l->data[ x ][ y ].c) {
        case CHARMAP_CORRIDOR :
        case CHARMAP_TRAP :
        case CHARMAP_DOOR :
        case CHARMAP_JOIN :
          {
            //
            // Check the door/corridor goes from and to somewhere. Diagonals don't count.
            //
            int walkable_tile = 0;

            walkable_tile += level_gen_tile_is_walkable(g, l, x - 1, y) ? 1 : 0;
            walkable_tile += level_gen_tile_is_walkable(g, l, x + 1, y) ? 1 : 0;
            walkable_tile += level_gen_tile_is_walkable(g, l, x, y - 1) ? 1 : 0;
            walkable_tile += level_gen_tile_is_walkable(g, l, x, y + 1) ? 1 : 0;

            if (walkable_tile <= 1) {
              l->data[ x ][ y ].c    = CHARMAP_EMPTY;
              l->data[ x ][ y ].room = nullptr;
              did_something          = true;
            }
            break;
          }
        case CHARMAP_FLOOR :
          {
            //
            // Choose 3 not 4 nebs to make the rooms have fewer single random tiles
            // on the edges. Makes it look more formed.
            //
            int empty_tile = 0;

            empty_tile += (l->data[ x - 1 ][ y ].c == CHARMAP_EMPTY) ? 1 : 0;
            empty_tile += (l->data[ x + 1 ][ y ].c == CHARMAP_EMPTY) ? 1 : 0;
            empty_tile += (l->data[ x ][ y - 1 ].c == CHARMAP_EMPTY) ? 1 : 0;
            empty_tile += (l->data[ x ][ y + 1 ].c == CHARMAP_EMPTY) ? 1 : 0;

            if (empty_tile >= 3) {
              l->data[ x ][ y ].c    = CHARMAP_EMPTY;
              l->data[ x ][ y ].room = nullptr;
              did_something          = true;
            }
            break;
          }
      }
    }
  }
  return did_something;
}

//
// Keep track of which room is connected to another via a door
//
static void level_gen_scan_connected_rooms(Gamep g, class LevelGen *l)
{
  TRACE_NO_INDENT();

  for (int y = 1; y < MAP_HEIGHT - 1; y++) {
    for (int x = 1; x < MAP_WIDTH - 1; x++) {
      switch (l->data[ x ][ y ].c) {
        case CHARMAP_JOIN :
          {
            {
              auto room_a = l->data[ x - 1 ][ y ].room;
              auto room_b = l->data[ x + 1 ][ y ].room;

              if (room_a && room_b) {
                if (room_a < room_b) {
                  std::pair< class Room *, class Room * > conn(room_a, room_b);
                  l->rooms_connected[ conn ] = true;
                } else {
                  std::pair< class Room *, class Room * > conn(room_b, room_a);
                  l->rooms_connected[ conn ] = true;
                }
              }
            }

            {
              auto room_a = l->data[ x ][ y + 1 ].room;
              auto room_b = l->data[ x ][ y - 1 ].room;

              if (room_a && room_b) {
                if (room_a < room_b) {
                  std::pair< class Room *, class Room * > conn(room_a, room_b);
                  l->rooms_connected[ conn ] = true;
                } else {
                  std::pair< class Room *, class Room * > conn(room_b, room_a);
                  l->rooms_connected[ conn ] = true;
                }
              }
            }

            break;
          }
      }
    }
  }
}

//
// Add corridors between rooms that are not connected
// Shortest distance is 2, which is ". ."
//
static void level_gen_connect_adjacent_rooms_with_distance_and_chance(Gamep g, class LevelGen *l, int dist,
                                                                      int chance)
{
  TRACE_NO_INDENT();

  const std::initializer_list< point > directions = {point(-1, 0), point(1, 0), point(0, -1), point(0, 1)};

  for (int y = dist; y < MAP_HEIGHT - dist - 1; y++) {
    for (int x = dist; x < MAP_WIDTH - dist - 1; x++) {
      switch (l->data[ x ][ y ].c) {
        case CHARMAP_FLOOR :
          {
            //
            // Decrease the chance of connecting leaf rooms so we don't get too many
            //
            if (d100() > chance) {
              continue;
            }

            for (auto direction : directions) {
              //
              // Check there is nothing in the way
              //
              bool has_clear_path = true;
              for (auto d = 1; d < dist; d++) {
                point adj(x + direction.x * d, y + direction.y * d);
                switch (l->data[ adj.x ][ adj.y ].c) {
                  case CHARMAP_WATER :
                  case CHARMAP_CHASM :
                  case CHARMAP_LAVA :
                  case CHARMAP_EMPTY : break;
                  default : has_clear_path = false; break;
                }
              }

              if (! has_clear_path) {
                continue;
              }

              //
              // Check there is a room at the end of the blank space
              //
              point dest(x + direction.x * dist, y + direction.y * dist);
              if (l->data[ dest.x ][ dest.y ].c != CHARMAP_FLOOR) {
                continue;
              }

              auto room_a = l->data[ x ][ y ].room;
              auto room_b = l->data[ dest.x ][ dest.y ].room;

              //
              // Check the two rooms at either end of the corridor are different.
              //
              if (room_a == room_b) {
                continue;
              }

              //
              // Keep connections to the start room minimal
              //
              if (room_a->room_type == ROOM_TYPE_START) {
                continue;
              }
              if (room_b->room_type == ROOM_TYPE_START) {
                continue;
              }

              std::pair< class Room *, class Room * > conn;
              if (room_a && room_b) {
                if (room_a < room_b) {
                  conn.first  = room_a;
                  conn.second = room_b;
                } else {
                  conn.first  = room_b;
                  conn.second = room_a;
                }
              }

              //
              // If the rooms are not connected, then join them via a corridor
              //
              if (l->rooms_connected.find(conn) == l->rooms_connected.end()) {
                l->rooms_adj_connected++;
                l->rooms_connected[ conn ] = true;
                for (auto d = 1; d < dist; d++) {
                  point adj(x + direction.x * d, y + direction.y * d);

                  if (dist >= MAX_LEVEL_GEN_MIN_BRIDGE_LEN) {
                    l->data[ adj.x ][ adj.y ].c = CHARMAP_BRIDGE;
                  } else {
                    l->data[ adj.x ][ adj.y ].c = CHARMAP_CORRIDOR;
                  }

                  l->data[ adj.x ][ adj.y ].room = room_a;
                }
              }
            }

            break;
          }
      }
    }
  }
}

//
// Add corridors between rooms that are not connected
// Shortest distance is 2, which is ". ."
//
static void level_gen_connect_adjacent_rooms(Gamep g, class LevelGen *l)
{
  TRACE_NO_INDENT();

  const std::initializer_list< std::pair< int, int > > dists = {
      std::pair(2 /* corridor length */, 20 /* percentage chance of occuring */),
      std::pair(3 /* corridor length */, 20 /* percentage chance of occuring */),
      std::pair(4 /* corridor length */, 20 /* percentage chance of occuring */),
      std::pair(5 /* corridor length */, 20 /* percentage chance of occuring */),
      std::pair(6 /* corridor length */, 20 /* percentage chance of occuring */),
      std::pair(7 /* corridor length */, 20 /* percentage chance of occuring */),
      std::pair(8 /* corridor length */, 20 /* percentage chance of occuring */),
      std::pair(9 /* corridor length */, 20 /* percentage chance of occuring */),
      std::pair(10 /* corridor length */, 20 /* percentage chance of occuring */),
      std::pair(11 /* corridor length */, 20 /* percentage chance of occuring */),
      std::pair(12 /* corridor length */, 20 /* percentage chance of occuring */),
      std::pair(13 /* corridor length */, 20 /* percentage chance of occuring */),
      std::pair(14 /* corridor length */, 20 /* percentage chance of occuring */),
      std::pair(15 /* corridor length */, 20 /* percentage chance of occuring */),
      std::pair(16 /* corridor length */, 20 /* percentage chance of occuring */),
      std::pair(17 /* corridor length */, 20 /* percentage chance of occuring */),
      std::pair(18 /* corridor length */, 20 /* percentage chance of occuring */),
      std::pair(19 /* corridor length */, 20 /* percentage chance of occuring */),
      std::pair(20 /* corridor length */, 20 /* percentage chance of occuring */),
  };
  for (auto d : dists) {
    level_gen_connect_adjacent_rooms_with_distance_and_chance(g, l, d.first, d.second);
  }
}

//
// Make bridges dramatic by adding chasms around them
//
static void level_gen_add_chasms_around_bridges(Gamep g, class LevelGen *l)
{
  TRACE_NO_INDENT();

  char bridge_type = CHARMAP_CHASM;

  //
  // If adjacent to water, make the bridge over water
  //
  for (int y = 1; y < MAP_HEIGHT - 1; y++) {
    for (int x = 1; x < MAP_WIDTH - 1; x++) {
      for (int dy = -1; dy <= 1; dy++) {
        for (int dx = -1; dx <= 1; dx++) {
          if (l->data[ x + dx ][ y + dy ].c == CHARMAP_WATER) {
            bridge_type = CHARMAP_WATER;
            goto add_bridge;
          }
          if (l->data[ x + dx ][ y + dy ].c == CHARMAP_LAVA) {
            bridge_type = CHARMAP_LAVA;
            goto add_bridge;
          }
        }
      }
    }
  }

add_bridge:
  //
  // Create the bridge
  //
  for (int y = 1; y < MAP_HEIGHT - 1; y++) {
    for (int x = 1; x < MAP_WIDTH - 1; x++) {
      switch (l->data[ x ][ y ].c) {
        case CHARMAP_BRIDGE :
          {
            if (l->data[ x - 1 ][ y ].c == CHARMAP_EMPTY) {
              l->data[ x - 1 ][ y ].c = bridge_type;
            }
            if (l->data[ x + 1 ][ y ].c == CHARMAP_EMPTY) {
              l->data[ x + 1 ][ y ].c = bridge_type;
            }
            if (l->data[ x ][ y - 1 ].c == CHARMAP_EMPTY) {
              l->data[ x ][ y - 1 ].c = bridge_type;
            }
            if (l->data[ x ][ y + 1 ].c == CHARMAP_EMPTY) {
              l->data[ x ][ y + 1 ].c = bridge_type;
            }
            break;
          }
      }
    }
  }
}

//
// Grow lakes, chasms etc...
//
static void level_gen_grow_hazards(Gamep g, class LevelGen *l)
{
  TRACE_NO_INDENT();

  char changed[ MAP_WIDTH ][ MAP_HEIGHT ] = {};

  for (int y = 1; y < MAP_HEIGHT - 1; y++) {
    for (int x = 1; x < MAP_WIDTH - 1; x++) {
      auto c = l->data[ x ][ y ].c;

      switch (c) {
        case CHARMAP_CHASM :
        case CHARMAP_LAVA :
        case CHARMAP_WATER :
          if (d100() < 50) {
            continue;
          }

          if (l->data[ x - 1 ][ y - 1 ].c == CHARMAP_EMPTY) {
            if (d100() < 50) {
              changed[ x - 1 ][ y - 1 ] = c;
            }
          }
          if (l->data[ x - 1 ][ y + 1 ].c == CHARMAP_EMPTY) {
            if (d100() < 50) {
              changed[ x - 1 ][ y + 1 ] = c;
            }
          }
          if (l->data[ x + 1 ][ y - 1 ].c == CHARMAP_EMPTY) {
            if (d100() < 50) {
              changed[ x + 1 ][ y - 1 ] = c;
            }
          }
          if (l->data[ x + 1 ][ y + 1 ].c == CHARMAP_EMPTY) {
            if (d100() < 50) {
              changed[ x + 1 ][ y + 1 ] = c;
            }
          }
          if (l->data[ x - 1 ][ y ].c == CHARMAP_EMPTY) {
            if (d100() < 50) {
              changed[ x - 1 ][ y ] = c;
            }
          }
          if (l->data[ x + 1 ][ y ].c == CHARMAP_EMPTY) {
            if (d100() < 50) {
              changed[ x + 1 ][ y ] = c;
            }
          }
          if (l->data[ x ][ y - 1 ].c == CHARMAP_EMPTY) {
            if (d100() < 50) {
              changed[ x ][ y - 1 ] = c;
            }
          }
          if (l->data[ x ][ y + 1 ].c == CHARMAP_EMPTY) {
            if (d100() < 50) {
              changed[ x ][ y + 1 ] = c;
            }
          }
          break;
      }
    }
  }

  for (int y = 0; y < MAP_HEIGHT; y++) {
    for (int x = 0; x < MAP_WIDTH; x++) {
      auto c = changed[ x ][ y ];
      if (c) {
        l->data[ x ][ y ].c = c;
      }
    }
  }
}

//
// Grow island of safety
//
static void level_gen_grow_islands(Gamep g, class LevelGen *l)
{
  TRACE_NO_INDENT();

  char changed[ MAP_WIDTH ][ MAP_HEIGHT ] = {};

  for (int y = 1; y < MAP_HEIGHT - 1; y++) {
    for (int x = 1; x < MAP_WIDTH - 1; x++) {
      auto c = l->data[ x ][ y ].c;

      switch (c) {
        case CHARMAP_DIRT :

          if (l->data[ x - 1 ][ y - 1 ].c == CHARMAP_WATER) {
            if (d100() < 50) {
              changed[ x - 1 ][ y - 1 ] = c;
            }
          }
          if (l->data[ x - 1 ][ y + 1 ].c == CHARMAP_WATER) {
            if (d100() < 50) {
              changed[ x - 1 ][ y + 1 ] = c;
            }
          }
          if (l->data[ x + 1 ][ y - 1 ].c == CHARMAP_WATER) {
            if (d100() < 50) {
              changed[ x + 1 ][ y - 1 ] = c;
            }
          }
          if (l->data[ x + 1 ][ y + 1 ].c == CHARMAP_WATER) {
            if (d100() < 50) {
              changed[ x + 1 ][ y + 1 ] = c;
            }
          }
          if (l->data[ x - 1 ][ y ].c == CHARMAP_WATER) {
            if (d100() < 50) {
              changed[ x - 1 ][ y ] = c;
            }
          }
          if (l->data[ x + 1 ][ y ].c == CHARMAP_WATER) {
            if (d100() < 50) {
              changed[ x + 1 ][ y ] = c;
            }
          }
          if (l->data[ x ][ y - 1 ].c == CHARMAP_WATER) {
            if (d100() < 50) {
              changed[ x ][ y - 1 ] = c;
            }
          }
          if (l->data[ x ][ y + 1 ].c == CHARMAP_WATER) {
            if (d100() < 50) {
              changed[ x ][ y + 1 ] = c;
            }
          }
          break;
      }
    }
  }

  for (int y = 0; y < MAP_HEIGHT; y++) {
    for (int x = 0; x < MAP_WIDTH; x++) {
      auto c = changed[ x ][ y ];
      if (c) {
        l->data[ x ][ y ].c = c;
      }
    }
  }
}

//
// Add islands of safety
//
static void level_gen_add_islands(Gamep g, class LevelGen *l)
{
  TRACE_NO_INDENT();

  char changed[ MAP_WIDTH ][ MAP_HEIGHT ] = {};

  for (int y = 1; y < MAP_HEIGHT - 1; y++) {
    for (int x = 1; x < MAP_WIDTH - 1; x++) {
      auto c = l->data[ x ][ y ].c;

      switch (c) {
        case CHARMAP_CHASM :
        case CHARMAP_LAVA :
        case CHARMAP_WATER :
          if (d100() < 95) {
            continue;
          }

          if (/* top left  */ l->data[ x - 1 ][ y - 1 ].c == c &&
              /* bot right */ l->data[ x - 1 ][ y + 1 ].c == c &&
              /* top right */ l->data[ x + 1 ][ y - 1 ].c == c &&
              /* bot right */ l->data[ x + 1 ][ y + 1 ].c == c &&
              /* left      */ l->data[ x - 1 ][ y ].c == c &&
              /* right     */ l->data[ x + 1 ][ y ].c == c &&
              /* top       */ l->data[ x ][ y - 1 ].c == c &&
              /* bot       */ l->data[ x ][ y + 1 ].c == c) {
            changed[ x ][ y + 1 ] = CHARMAP_DIRT;
          }
          break;
      }
    }
  }

  for (int y = 0; y < MAP_HEIGHT; y++) {
    for (int x = 0; x < MAP_WIDTH; x++) {
      auto c = changed[ x ][ y ];
      if (c) {
        l->data[ x ][ y ].c = c;
      }
    }
  }
}

//
// Make bridges dramatic by adding chasms around them
//
static void level_gen_add_walls_around_rooms(Gamep g, class LevelGen *l)
{
  TRACE_NO_INDENT();

  for (int y = 1; y < MAP_HEIGHT - 1; y++) {
    for (int x = 1; x < MAP_WIDTH - 1; x++) {
      auto c = l->data[ x ][ y ].c;
      switch (c) {
        case CHARMAP_WATER :
        case CHARMAP_LAVA :
        case CHARMAP_CHASM :
        case CHARMAP_CHASM_50 :
        case CHARMAP_EMPTY :
        case CHARMAP_WALL : break;
        case CHARMAP_BARREL :
        case CHARMAP_BRAZIER :
        case CHARMAP_BRIDGE :
        case CHARMAP_CORRIDOR :
        case CHARMAP_DOOR :
        case CHARMAP_DRY_GRASS :
        case CHARMAP_EXIT :
        case CHARMAP_FLOOR :
        case CHARMAP_FLOOR_50 :
        case CHARMAP_FOLIAGE :
        case CHARMAP_JOIN :
        case CHARMAP_KEY :
        case CHARMAP_MOB1 :
        case CHARMAP_MOB2 :
        case CHARMAP_MONST1 :
        case CHARMAP_MONST2 :
        case CHARMAP_PILLAR :
        case CHARMAP_SECRET_DOOR :
        case CHARMAP_START :
        case CHARMAP_TELEPORT :
        case CHARMAP_TRAP :
        case CHARMAP_TREASURE1 :
        case CHARMAP_TREASURE2 :
          if (l->data[ x - 1 ][ y - 1 ].c == CHARMAP_EMPTY) {
            l->data[ x - 1 ][ y - 1 ].c = CHARMAP_WALL;
          }
          if (l->data[ x - 1 ][ y + 1 ].c == CHARMAP_EMPTY) {
            l->data[ x - 1 ][ y + 1 ].c = CHARMAP_WALL;
          }
          if (l->data[ x + 1 ][ y - 1 ].c == CHARMAP_EMPTY) {
            l->data[ x + 1 ][ y - 1 ].c = CHARMAP_WALL;
          }
          if (l->data[ x + 1 ][ y + 1 ].c == CHARMAP_EMPTY) {
            l->data[ x + 1 ][ y + 1 ].c = CHARMAP_WALL;
          }
          if (l->data[ x - 1 ][ y ].c == CHARMAP_EMPTY) {
            l->data[ x - 1 ][ y ].c = CHARMAP_WALL;
          }
          if (l->data[ x + 1 ][ y ].c == CHARMAP_EMPTY) {
            l->data[ x + 1 ][ y ].c = CHARMAP_WALL;
          }
          if (l->data[ x ][ y - 1 ].c == CHARMAP_EMPTY) {
            l->data[ x ][ y - 1 ].c = CHARMAP_WALL;
          }
          if (l->data[ x ][ y + 1 ].c == CHARMAP_EMPTY) {
            l->data[ x ][ y + 1 ].c = CHARMAP_WALL;
          }
          break;
      }
    }
  }
}

//
// e.g. chasm next to water
//
static bool level_gen_remove_water_conflicts(Gamep g, class LevelGen *l)
{
  TRACE_NO_INDENT();

  bool did_something = false;

  for (int y = 1; y < MAP_HEIGHT - 1; y++) {
    for (int x = 1; x < MAP_WIDTH - 1; x++) {
      auto c = l->data[ x ][ y ].c;
      if (c == CHARMAP_WATER) {
        if ((l->data[ x - 1 ][ y - 1 ].c == CHARMAP_LAVA) || l->data[ x - 1 ][ y - 1 ].c == CHARMAP_CHASM) {
          l->data[ x - 1 ][ y - 1 ].c = CHARMAP_WATER;
          did_something               = true;
        }
        if ((l->data[ x - 1 ][ y + 1 ].c == CHARMAP_LAVA) || l->data[ x - 1 ][ y + 1 ].c == CHARMAP_CHASM) {
          l->data[ x - 1 ][ y + 1 ].c = CHARMAP_WATER;
          did_something               = true;
        }
        if ((l->data[ x + 1 ][ y - 1 ].c == CHARMAP_LAVA) || l->data[ x + 1 ][ y - 1 ].c == CHARMAP_CHASM) {
          l->data[ x + 1 ][ y - 1 ].c = CHARMAP_WATER;
          did_something               = true;
        }
        if ((l->data[ x + 1 ][ y + 1 ].c == CHARMAP_LAVA) || l->data[ x + 1 ][ y + 1 ].c == CHARMAP_CHASM) {
          l->data[ x + 1 ][ y + 1 ].c = CHARMAP_WATER;
          did_something               = true;
        }
        if ((l->data[ x - 1 ][ y ].c == CHARMAP_LAVA) || l->data[ x - 1 ][ y ].c == CHARMAP_CHASM) {
          l->data[ x - 1 ][ y ].c = CHARMAP_WATER;
          did_something           = true;
        }
        if ((l->data[ x + 1 ][ y ].c == CHARMAP_LAVA) || l->data[ x + 1 ][ y ].c == CHARMAP_CHASM) {
          l->data[ x + 1 ][ y ].c = CHARMAP_WATER;
          did_something           = true;
        }
        if ((l->data[ x ][ y - 1 ].c == CHARMAP_LAVA) || l->data[ x ][ y - 1 ].c == CHARMAP_CHASM) {
          l->data[ x ][ y - 1 ].c = CHARMAP_WATER;
          did_something           = true;
        }
        if ((l->data[ x ][ y + 1 ].c == CHARMAP_LAVA) || l->data[ x ][ y + 1 ].c == CHARMAP_CHASM) {
          l->data[ x ][ y + 1 ].c = CHARMAP_WATER;
          did_something           = true;
        }
      }
    }
  }
  return did_something;
}

//
// e.g. chasm next to lava
//
static bool level_gen_remove_lava_conflicts(Gamep g, class LevelGen *l)
{
  TRACE_NO_INDENT();

  bool did_something = false;

  for (int y = 1; y < MAP_HEIGHT - 1; y++) {
    for (int x = 1; x < MAP_WIDTH - 1; x++) {
      auto c = l->data[ x ][ y ].c;
      if (c == CHARMAP_LAVA) {
        if ((l->data[ x - 1 ][ y - 1 ].c == CHARMAP_WATER) || l->data[ x - 1 ][ y - 1 ].c == CHARMAP_CHASM) {
          l->data[ x - 1 ][ y - 1 ].c = CHARMAP_LAVA;
          did_something               = true;
        }
        if ((l->data[ x - 1 ][ y + 1 ].c == CHARMAP_WATER) || l->data[ x - 1 ][ y + 1 ].c == CHARMAP_CHASM) {
          l->data[ x - 1 ][ y + 1 ].c = CHARMAP_LAVA;
          did_something               = true;
        }
        if ((l->data[ x + 1 ][ y - 1 ].c == CHARMAP_WATER) || l->data[ x + 1 ][ y - 1 ].c == CHARMAP_CHASM) {
          l->data[ x + 1 ][ y - 1 ].c = CHARMAP_LAVA;
          did_something               = true;
        }
        if ((l->data[ x + 1 ][ y + 1 ].c == CHARMAP_WATER) || l->data[ x + 1 ][ y + 1 ].c == CHARMAP_CHASM) {
          l->data[ x + 1 ][ y + 1 ].c = CHARMAP_LAVA;
          did_something               = true;
        }
        if ((l->data[ x - 1 ][ y ].c == CHARMAP_WATER) || l->data[ x - 1 ][ y ].c == CHARMAP_CHASM) {
          l->data[ x - 1 ][ y ].c = CHARMAP_LAVA;
          did_something           = true;
        }
        if ((l->data[ x + 1 ][ y ].c == CHARMAP_WATER) || l->data[ x + 1 ][ y ].c == CHARMAP_CHASM) {
          l->data[ x + 1 ][ y ].c = CHARMAP_LAVA;
          did_something           = true;
        }
        if ((l->data[ x ][ y - 1 ].c == CHARMAP_WATER) || l->data[ x ][ y - 1 ].c == CHARMAP_CHASM) {
          l->data[ x ][ y - 1 ].c = CHARMAP_LAVA;
          did_something           = true;
        }
        if ((l->data[ x ][ y + 1 ].c == CHARMAP_WATER) || l->data[ x ][ y + 1 ].c == CHARMAP_CHASM) {
          l->data[ x ][ y + 1 ].c = CHARMAP_LAVA;
          did_something           = true;
        }
      }
    }
  }
  return did_something;
}

//
// e.g. water next to chasm
//
static bool level_gen_remove_chasm_conflicts(Gamep g, class LevelGen *l)
{
  TRACE_NO_INDENT();

  bool did_something = false;

  for (int y = 1; y < MAP_HEIGHT - 1; y++) {
    for (int x = 1; x < MAP_WIDTH - 1; x++) {
      auto c = l->data[ x ][ y ].c;
      if (c == CHARMAP_CHASM) {
        if ((l->data[ x - 1 ][ y - 1 ].c == CHARMAP_WATER) || l->data[ x - 1 ][ y - 1 ].c == CHARMAP_LAVA) {
          l->data[ x - 1 ][ y - 1 ].c = CHARMAP_CHASM;
          did_something               = true;
        }
        if ((l->data[ x - 1 ][ y + 1 ].c == CHARMAP_WATER) || l->data[ x - 1 ][ y + 1 ].c == CHARMAP_LAVA) {
          l->data[ x - 1 ][ y + 1 ].c = CHARMAP_CHASM;
          did_something               = true;
        }
        if ((l->data[ x + 1 ][ y - 1 ].c == CHARMAP_WATER) || l->data[ x + 1 ][ y - 1 ].c == CHARMAP_LAVA) {
          l->data[ x + 1 ][ y - 1 ].c = CHARMAP_CHASM;
          did_something               = true;
        }
        if ((l->data[ x + 1 ][ y + 1 ].c == CHARMAP_WATER) || l->data[ x + 1 ][ y + 1 ].c == CHARMAP_LAVA) {
          l->data[ x + 1 ][ y + 1 ].c = CHARMAP_CHASM;
          did_something               = true;
        }
        if ((l->data[ x - 1 ][ y ].c == CHARMAP_WATER) || l->data[ x - 1 ][ y ].c == CHARMAP_LAVA) {
          l->data[ x - 1 ][ y ].c = CHARMAP_CHASM;
          did_something           = true;
        }
        if ((l->data[ x + 1 ][ y ].c == CHARMAP_WATER) || l->data[ x + 1 ][ y ].c == CHARMAP_LAVA) {
          l->data[ x + 1 ][ y ].c = CHARMAP_CHASM;
          did_something           = true;
        }
        if ((l->data[ x ][ y - 1 ].c == CHARMAP_WATER) || l->data[ x ][ y - 1 ].c == CHARMAP_LAVA) {
          l->data[ x ][ y - 1 ].c = CHARMAP_CHASM;
          did_something           = true;
        }
        if ((l->data[ x ][ y + 1 ].c == CHARMAP_WATER) || l->data[ x ][ y + 1 ].c == CHARMAP_LAVA) {
          l->data[ x ][ y + 1 ].c = CHARMAP_CHASM;
          did_something           = true;
        }
      }
    }
  }
  return did_something;
}

//
// e.g. chasm next to water
//
static void level_gen_remove_conflicting_tiles(Gamep g, class LevelGen *l)
{
  TRACE_NO_INDENT();

  while (level_gen_remove_water_conflicts(g, l))
    ;
  while (level_gen_remove_lava_conflicts(g, l))
    ;
  while (level_gen_remove_chasm_conflicts(g, l))
    ;
}

static void level_gen_add_fragments(Gamep g, class LevelGen *l)
{
  TRACE_NO_INDENT();

  int tries = 0;
  while (tries++ < MAX_LEVEL_GEN_FRAGMENT_TRIES) {
    auto f = fragment_random_get(g, l);
    if (! f) {
      return;
    }

    std::vector< point > cands;

    for (int y = 0; y < MAP_HEIGHT - f->height; y++) {
      for (int x = 0; x < MAP_WIDTH - f->width; x++) {
        point at(x, y);
        if (fragment_match(g, l, f, at)) {
          cands.push_back(at);
        }
      }
    }

    if (cands.empty()) {
      continue;
    }

    auto cand = cands[ pcg_rand() % cands.size() ];
    fragment_put(g, l, f, cand);

    if (l->fragment_count++ >= MAX_LEVEL_GEN_FRAGMENTS) {
      return;
    }
  }
}

//
// Create a level from the current game seed
//
static class LevelGen *level_gen(Gamep g, int which)
{
  TRACE_NO_INDENT();

  LevelGen *l = level_gen_create_rooms(g, which);
  if (! l) {
    return l;
  }

  //
  // Get rid of tiles that go nowhere
  //
  while (level_gen_trim_dead_tiles(g, l)) {}

  //
  // Keep track of which room is connected to another via a door
  //
  level_gen_scan_connected_rooms(g, l);

  //
  // Add corridors between rooms that are not connected
  //
  level_gen_connect_adjacent_rooms(g, l);

  //
  // Make bridges dramatic by adding chasms around them
  //
  level_gen_add_chasms_around_bridges(g, l);

  //
  // Add islands of safety
  //
  level_gen_add_islands(g, l);

  //
  // Grow lakes, chasms etc...
  //
  level_gen_grow_hazards(g, l);

  //
  // Make islands bigger
  //
  level_gen_grow_islands(g, l);

  //
  // Add fragments before we add walls
  //
  level_gen_add_fragments(g, l);

  //
  // Add walls
  //
  level_gen_add_walls_around_rooms(g, l);

  //
  // And add again after, in case some can now match
  //
  level_gen_add_fragments(g, l);

  //
  // Add walls again in case a fragment extended the room
  //
  level_gen_add_walls_around_rooms(g, l);

  //
  // e.g. chasm next to water
  //
  level_gen_remove_conflicting_tiles(g, l);

  //
  // Remove chasms next to water etc...
  //
  return l;
}

static std::array< class LevelGen *, MAX_LEVELS > levels = {};

//
// Create a level and store in the array of levels
//
static void level_gen_create_level(Gamep g, int which)
{
  TRACE_NO_INDENT();

  //
  // Per thread seed
  //
  uint32_t seed_num = game_seed_num_get(g);
  seed_num += seed_num * which;
  pcg_srand(seed_num);

  auto l = level_gen(g, which);
  if (! l) {
    return;
  }

  l->seed_num     = seed_num;
  levels[ which ] = l;
}

void level_gen_test(Gamep g)
{
  TRACE_NO_INDENT();

  int                        max_threads = MAX_LEVELS;
  std::vector< std::thread > threads;

  if (0) {
    for (auto i = 0; i < MAX_LEVELS; i++) {
      level_gen_create_level(g, i);
    }
  }

  for (auto i = 0; i < max_threads; i++) {
    threads.push_back(std::thread(level_gen_create_level, g, i));
  }

  for (auto i = 0; i < max_threads; i++) {
    threads[ i ].join();
  }

  for (auto i = 0; i < max_threads; i++) {
    auto l = levels[ i ];
    if (l) {
      level_gen_dump(g, l);
    }
  }

  level_gen_stats_dump(g);
}
