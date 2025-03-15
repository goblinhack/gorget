//
// Copyright Neil McGill, goblinhack@gmail.com
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
#include <map>
#include <stdarg.h>
#include <thread>
#include <vector>

//
// How many times to try creating a single level
//
static const int MAX_LEVELS                        = 1;
static const int MAX_LEVEL_GEN_TRIES_FOR_SAME_SEED = 1000;
static const int MAX_LEVEL_GEN_ROOM_PLACE_TRIES    = 200;
static const int MAX_LEVEL_GEN_MIN_BRIDGE_LEN      = 6;
static const int MAX_LEVEL_GEN_TRIES_CREATE_ROOM   = 100;
static const int MIN_LEVEL_EXIT_DISTANCE           = MAP_WIDTH / 4;
static const int MIN_LEVEL_ROOM_COUNT              = 5;
static const int LEVEL_WATER_GEN_PROB              = 1200;

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
static int level_exit_is_too_close_to_start;
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
  int min_level_room_count {};
  int max_level_room_count {};

  //
  // The starting room
  //
  class Room *room_first = {};

  //
  // Used to make sure we place each room uniquely per level
  //
  std::map< class Room *, bool > rooms_placed;

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
  int room_no = {};

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
  // For keeping track of which rooms we add
  //
  const char *file = {};
  int         line = {};

  //
  // All doors in the room
  //
  std::vector< point > doors;
};

static int                         room_no;
static std::vector< class Room * > rooms_all[ ROOM_TYPE_MAX ];

//
// Scan the room now it is created, for any things of interest
//
static void room_scan(Gamep g, class Room *r)
{
  TRACE_NO_INDENT();

  for (int y = 0; y < r->height; y++) {
    for (int x = 0; x < r->width; x++) {
      auto c = r->data[ (y * r->width) + x ];

      switch (c) {
        case CHARMAP_JOIN : r->doors.push_back(point(x, y)); continue;
        default : break;
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

  n->room_no   = ++room_no;
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

  n->room_no   = ++room_no;
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
void room_add(Gamep g, bool check, const char *file, int line, ...)
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
        case CHARMAP_CHASM : break;
        case CHARMAP_CHASM_50 : break;
        case CHARMAP_JOIN : break;
        case CHARMAP_EMPTY : break;
        case CHARMAP_FLOOR : break;
        case CHARMAP_KEY : break;
        case CHARMAP_MONST1 : break;
        case CHARMAP_MONST2 : break;
        case CHARMAP_MOB1 : break;
        case CHARMAP_MOB2 : break;
        case CHARMAP_TREASURE1 : break;
        case CHARMAP_TREASURE2 : break;
        case CHARMAP_WATER : break;
        case CHARMAP_TELEPORT : break;
        case CHARMAP_FOLIAGE : break;
        case CHARMAP_DOOR : break;
        case CHARMAP_SECRET_DOOR : break;
        case CHARMAP_DRY_GRASS : break;
        case CHARMAP_BARREL : break;
        case CHARMAP_CORRIDOR : break;
        case CHARMAP_PILLAR : break;
        case CHARMAP_TRAP : break;
        case CHARMAP_LAVA : break;
        case CHARMAP_BRIDGE : break;
        case CHARMAP_BRAZIER : break;
        case CHARMAP_FLOOR_50 : break;
        case CHARMAP_FLOOR_40 : break;
        case CHARMAP_FLOOR_30 : break;
        case CHARMAP_FLOOR_20 : break;
        case CHARMAP_FLOOR_10 : break;
        case CHARMAP_WALL : break;
        case CHARMAP_EXIT : room_type = ROOM_TYPE_EXIT; break;
        case CHARMAP_START : room_type = ROOM_TYPE_START; break;
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

  r->room_no   = ++room_no;
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
  if (check) {
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

  LOG("Room %d %s:%d", r->room_no, r->file, r->line);

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
static bool room_can_place_at(Gamep g, class LevelGen *l, class Room *r, point at)
{
  //
  // Check the room is clear to be placed here.
  //
  // Also check 1 adjoining tile
  //
  for (int ry = 0; ry < r->height; ry++) {
    for (int rx = 0; rx < r->width; rx++) {
      //
      // Check we have something to place here.
      //
      char room_c = r->data[ (ry * r->width) + rx ];
      if (unlikely(room_c == CHARMAP_EMPTY)) {
        continue;
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
          continue;
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
        case CHARMAP_FLOOR_40 :
          if (d100() > 40) {
            room_c = CHARMAP_EMPTY;
          } else {
            room_c = CHARMAP_FLOOR;
          }
          break;
        case CHARMAP_FLOOR_30 :
          if (d100() > 30) {
            room_c = CHARMAP_EMPTY;
          } else {
            room_c = CHARMAP_FLOOR;
          }
          break;
        case CHARMAP_FLOOR_20 :
          if (d100() > 20) {
            room_c = CHARMAP_EMPTY;
          } else {
            room_c = CHARMAP_FLOOR;
          }
          break;
        case CHARMAP_FLOOR_10 :
          if (d100() > 10) {
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

  for (int y = 0; y < MAP_HEIGHT; y++) {
    std::string tmp;
    for (int x = 0; x < MAP_WIDTH; x++) {
      tmp += l->data[ x ][ y ].c;
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
  LOG("- exit was too close to the start: %d", level_exit_is_too_close_to_start);
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
    return false;
  }

  //
  // Return a random door
  //
  *door_out = l->doors_not_explored[ pcg_random_range(0, l->doors_not_explored.size()) ];
  *room_out = l->data[ door_out->x ][ door_out->y ].room;

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
  int room_place_tries = 0;

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
        level_place_subsequent_room_fail++;
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
      // Don't try this door again
      //
      l->doors_walked[ door_other ] = true;

      //
      // Success
      //
      return true;
    }
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
  // Don't place the exit too close to the start point
  //
  if (room_type == ROOM_TYPE_EXIT) {
    if (distance(door_other, l->start) < MIN_LEVEL_EXIT_DISTANCE) {
      level_exit_is_too_close_to_start++;
      return false;
    }
  }

  //
  // Try multiple rooms with this door
  //
  return level_gen_place_room_at_door_intersection(g, l, door_other, room_other, room_type);
}

//
// The first room has been placed. Place all the rest.
//
static void level_gen_create_remaining_rooms(Gamep g, LevelGen *l, bool debug)
{
  TRACE_NO_INDENT();

  int attempts = 0;

  //
  // Keep placing rooms until we hit the max allowed
  //
  while ((int) l->rooms_placed.size() < l->max_level_room_count) {
    if (unlikely(debug)) {
      LOG("rooms placed %d attempts %d", (int) l->rooms_placed.size(), attempts);
    }

    //
    // Ensure we loop only so many times
    //
    if (attempts++ > MAX_LEVEL_GEN_TRIES_CREATE_ROOM) {
      break;
    }

    //
    // The room type to place
    //
    RoomType room_type = ROOM_TYPE_NORMAL;

    //
    // If we have not yet placed an exit room, should we?
    //
    if (! l->has_placed_exit) {
      if ((int) l->rooms_placed.size() > l->min_level_room_count) {
        //
        // If we have the minimum rooms, then likely we're far enough away from
        // the start room now to try placing an exit room.
        //
        room_type = ROOM_TYPE_EXIT;
      } else if (attempts > (MAX_LEVEL_GEN_TRIES_CREATE_ROOM / 2)) {
        //
        // If we're running out of room place attempts, try an exit room
        //
        room_type = ROOM_TYPE_EXIT;
      }
    }

    if (0) {
      level_gen_dump(g, l);
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
static bool level_gen_create_first_room(Gamep g, LevelGen *l, bool debug)
{
  TRACE_NO_INDENT();

  //
  // Choose a random start point for the rooms
  //
  int border = MAP_WIDTH / 3;
  int x;
  int y;
  if (l->which == 0) {
    //
    // First level start in the top left
    //
    x = pcg_random_range(0, border);
    y = pcg_random_range(0, border);
  } else {
    //
    // Other levels start somewhere central
    //
    x = pcg_random_range(border, MAP_WIDTH - border);
    y = pcg_random_range(border, MAP_HEIGHT - border);
  }

  point at(x, y);

  //
  // Choose a random first room and place it
  //
  auto r = l->room_first = room_random_get(g, l, ROOM_TYPE_START);
  if (! room_can_place_at(g, l, r, at)) {
    level_place_first_room_fail++;
    return false;
  }

  room_place_at(g, l, r, at);

  //
  // Placed the first room
  //
  if (unlikely(debug)) {
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
// Place a single large pool of water on the level
//
static void level_gen_single_large_pool_in_center(Gamep g, class LevelGen *l)
{
  uint8_t  x, y;
  uint32_t fill_prob       = LEVEL_WATER_GEN_PROB;
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
          case CHARMAP_KEY :
          case CHARMAP_LAVA :
          case CHARMAP_BRIDGE :
          case CHARMAP_EXIT :
          case CHARMAP_START :
          case CHARMAP_DOOR :
          case CHARMAP_JOIN :
          case CHARMAP_CORRIDOR :
          case CHARMAP_FLOOR :
          case CHARMAP_PILLAR :
          case CHARMAP_FOLIAGE :
          case CHARMAP_TREASURE1 :
          case CHARMAP_TREASURE2 :
          case CHARMAP_MONST1 :
          case CHARMAP_MONST2 :
          case CHARMAP_TRAP :
          case CHARMAP_BRAZIER :
          case CHARMAP_SECRET_DOOR :
          case CHARMAP_DRY_GRASS :
          case CHARMAP_BARREL :
          case CHARMAP_TELEPORT :
          case CHARMAP_MOB1 :
          case CHARMAP_MOB2 :
          case CHARMAP_CHASM :
          case CHARMAP_WALL :
            //
            // No water
            //
            break;
          case CHARMAP_EMPTY :
            //
            // Perma water
            //
            l->data[ x ][ y ].c = CHARMAP_WATER;
            break;
        }
      }
    }
  }
}

//
// Create rooms from the current seed
//
static class LevelGen *level_gen_create_rooms(Gamep g, int which, bool debug)
{
  TRACE_NO_INDENT();

  LevelGen *l = {};

  for (int level_gen_tries = 0; level_gen_tries < MAX_LEVEL_GEN_TRIES_FOR_SAME_SEED; level_gen_tries++) {
    //
    // Start with a fresh level each try
    //
    if (l) {
      delete l;
      l = nullptr;
    }

    l                       = new LevelGen();
    l->seed                 = std::string(game_get_seed(g));
    l->which                = which;
    l->min_level_room_count = MIN_LEVEL_ROOM_COUNT + (which / 10);
    l->max_level_room_count = l->min_level_room_count + 5;

    //
    // Add water
    //
    level_gen_single_large_pool_in_center(g, l);

    //
    // Place the first room
    //
    if (! level_gen_create_first_room(g, l, debug)) {
      continue;
    }

    //
    // Place the remaining rooms
    //
    level_gen_create_remaining_rooms(g, l, debug);

    //
    // Check we have enough rooms. Add a few more for deeper levels.
    //
    if ((int) l->rooms_placed.size() < l->min_level_room_count) {
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

  if (unlikely(debug)) {
    LOG("Failed to create room with seed: %s", game_get_seed(g));
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
    case CHARMAP_WATER : return true;
    case CHARMAP_START : return true;
    case CHARMAP_TELEPORT : return true;
    case CHARMAP_TRAP : return true;
    case CHARMAP_TREASURE1 : return true;
    case CHARMAP_TREASURE2 : return true;
    default : return false;
  }
}

//
// Get rid of tiles that go nowhere
//
static bool level_gen_trim_dead_tiles(Gamep g, class LevelGen *l, bool debug)
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
static void level_gen_scan_connected_rooms(Gamep g, class LevelGen *l, bool debug)
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
                                                                      int chance, bool debug)
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
            if (d100() > chance - l->rooms_adj_connected * 5) {
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
static void level_gen_connect_adjacent_rooms(Gamep g, class LevelGen *l, bool debug)
{
  TRACE_NO_INDENT();

  const std::initializer_list< std::pair< int, int > > dists = {
      std::pair(2 /* corridor length */, 100 /* percentage chance of occuring */),
      std::pair(3 /* corridor length */, 100 /* percentage chance of occuring */),
      std::pair(4 /* corridor length */, 100 /* percentage chance of occuring */),
      std::pair(5 /* corridor length */, 90 /* percentage chance of occuring */),
      std::pair(6 /* corridor length */, 90 /* percentage chance of occuring */),
      std::pair(7 /* corridor length */, 90 /* percentage chance of occuring */),
      std::pair(8 /* corridor length */, 50 /* percentage chance of occuring */),
      std::pair(9 /* corridor length */, 50 /* percentage chance of occuring */),
      std::pair(10 /* corridor length */, 50 /* percentage chance of occuring */),
      std::pair(11 /* corridor length */, 50 /* percentage chance of occuring */),
      std::pair(12 /* corridor length */, 10 /* percentage chance of occuring */),
      std::pair(13 /* corridor length */, 10 /* percentage chance of occuring */),
      std::pair(14 /* corridor length */, 10 /* percentage chance of occuring */),
      std::pair(15 /* corridor length */, 10 /* percentage chance of occuring */),
      std::pair(16 /* corridor length */, 5 /* percentage chance of occuring */),
      std::pair(17 /* corridor length */, 5 /* percentage chance of occuring */),
      std::pair(18 /* corridor length */, 5 /* percentage chance of occuring */),
      std::pair(19 /* corridor length */, 5 /* percentage chance of occuring */),
      std::pair(20 /* corridor length */, 5 /* percentage chance of occuring */),
  };
  for (auto d : dists) {
    level_gen_connect_adjacent_rooms_with_distance_and_chance(g, l, d.first, d.second, debug);
  }
}

//
// Make bridges dramatic by adding chasms around them
//
static void level_gen_add_chasms_around_bridges(Gamep g, class LevelGen *l, bool debug)
{
  TRACE_NO_INDENT();

  for (int y = 1; y < MAP_HEIGHT - 1; y++) {
    for (int x = 1; x < MAP_WIDTH - 1; x++) {
      switch (l->data[ x ][ y ].c) {
        case CHARMAP_BRIDGE :
          {
            if (l->data[ x - 1 ][ y ].c == CHARMAP_EMPTY) {
              l->data[ x - 1 ][ y ].c = CHARMAP_CHASM;
            }
            if (l->data[ x + 1 ][ y ].c == CHARMAP_EMPTY) {
              l->data[ x + 1 ][ y ].c = CHARMAP_CHASM;
            }
            if (l->data[ x ][ y - 1 ].c == CHARMAP_EMPTY) {
              l->data[ x ][ y - 1 ].c = CHARMAP_CHASM;
            }
            if (l->data[ x ][ y + 1 ].c == CHARMAP_EMPTY) {
              l->data[ x ][ y + 1 ].c = CHARMAP_CHASM;
            }
            break;
          }
      }
    }
  }
}

//
// Make bridges dramatic by adding chasms around them
//
static void level_gen_add_walls_around_rooms(Gamep g, class LevelGen *l, bool debug)
{
  TRACE_NO_INDENT();

  for (int y = 1; y < MAP_HEIGHT - 1; y++) {
    for (int x = 1; x < MAP_WIDTH - 1; x++) {
      auto c = l->data[ x ][ y ].c;
      if (c == CHARMAP_WATER) {
        continue;
      }

      switch (c) {
        case CHARMAP_EMPTY :
        case CHARMAP_WALL : break;
        case CHARMAP_CHASM :
        case CHARMAP_CHASM_50 :
        case CHARMAP_JOIN :
        case CHARMAP_FLOOR :
        case CHARMAP_KEY :
        case CHARMAP_MONST1 :
        case CHARMAP_MONST2 :
        case CHARMAP_MOB1 :
        case CHARMAP_MOB2 :
        case CHARMAP_TREASURE1 :
        case CHARMAP_TREASURE2 :
        case CHARMAP_WATER :
        case CHARMAP_TELEPORT :
        case CHARMAP_FOLIAGE :
        case CHARMAP_DOOR :
        case CHARMAP_SECRET_DOOR :
        case CHARMAP_DRY_GRASS :
        case CHARMAP_BARREL :
        case CHARMAP_CORRIDOR :
        case CHARMAP_PILLAR :
        case CHARMAP_TRAP :
        case CHARMAP_LAVA :
        case CHARMAP_BRIDGE :
        case CHARMAP_BRAZIER :
        case CHARMAP_FLOOR_50 :
        case CHARMAP_FLOOR_40 :
        case CHARMAP_FLOOR_30 :
        case CHARMAP_FLOOR_20 :
        case CHARMAP_FLOOR_10 :
        case CHARMAP_EXIT :
        case CHARMAP_START :
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
// Create a level from the current game seed
//
static class LevelGen *level_gen(Gamep g, int which)
{
  TRACE_NO_INDENT();

  bool debug = false;

  LevelGen *l = level_gen_create_rooms(g, which, debug);
  if (! l) {
    return l;
  }

  //
  // Get rid of tiles that go nowhere
  //
  while (level_gen_trim_dead_tiles(g, l, debug)) {}

  //
  // Keep track of which room is connected to another via a door
  //
  level_gen_scan_connected_rooms(g, l, debug);

  //
  // Add corridors between rooms that are not connected
  //
  level_gen_connect_adjacent_rooms(g, l, debug);

  //
  // Make bridges dramatic by adding chasms around them
  //
  level_gen_add_chasms_around_bridges(g, l, debug);

  //
  // Add walls
  //
  level_gen_add_walls_around_rooms(g, l, debug);

  //
  // Add water
  //
  // level_gen_single_large_pool_in_center(g, l);

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
  uint32_t seed_num = game_get_seed_num(g);
  seed_num += seed_num * which;
  game_set_seed_for_thread(g, seed_num);

  auto l          = level_gen(g, which);
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
