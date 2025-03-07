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
#include <map>
#include <stdarg.h>
#include <thread>
#include <vector>

//
// How many times to try creating a single level
//
static const int MAX_LEVELS                        = 100;
static const int MAX_LEVEL_GEN_TRIES_FOR_SAME_SEED = 1000;
static const int MAX_LEVEL_GEN_ROOM_PLACE_TRIES    = 500;
static const int MAX_LEVEL_GEN_CORRIDOR_LEN        = 20;
static const int MAX_LEVEL_GEN_MIN_BRIDGE_LEN      = 6;
static const int MAX_LEVEL_ROOM_COUNT              = 25;
static const int MAX_LEVEL_GEN_TRIES_CREATE_ROOM   = MAX_LEVEL_ROOM_COUNT * 2;
static const int MIN_LEVEL_ROOM_COUNT              = 10;

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
  // This is a copy of the game seed
  //
  std::string seed;

  //
  // Sub level
  //
  int which;

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
  // Level tiles and room info
  //
  Cell data[ MAP_WIDTH ][ MAP_HEIGHT ];
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
void room_add(Gamep g, const char *file, int line, ...)
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
        case CHARMAP_KEY :
        case CHARMAP_MONST1 : break;
        case CHARMAP_MONST2 : break;
        case CHARMAP_MOB1 : break;
        case CHARMAP_MOB2 : break;
        case CHARMAP_TREASURE1 : break;
        case CHARMAP_TREASURE2 : break;
        case CHARMAP_SHALLOW_WATER : break;
        case CHARMAP_DEEP_WATER : break;
        case CHARMAP_TELEPORT : break;
        case CHARMAP_FOLIAGE : break;
        case CHARMAP_FOOD : break;
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
  // Now read the room again
  //
  va_start(ap, line);

  for (int y = 0; y < r->height; y++) {
    const char *room_line = va_arg(ap, char *);
    for (int x = 0; x < r->width; x++) {
      r->data[ (y * r->width) + x ] = room_line[ x ];
    }
  }

  va_end(ap);

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
static void rooms_dump(Gamep g)
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
        // Doors can overlap doors in the same tile.
        //
        switch (l->data[ p.x ][ p.y ].c) {
          case CHARMAP_SHALLOW_WATER :
          case CHARMAP_DEEP_WATER :
            //
            // Ok to overwrite a chasm tile
            //
            break;
          case CHARMAP_CHASM :
            //
            // Ok to overwrite a chasm tile
            //
            break;
          case CHARMAP_LAVA :
            //
            // Ok to overwrite a chasm tile
            //
            break;
          case CHARMAP_EMPTY :
            //
            // Ok to overwrite an empty tile
            //
            break;
          case CHARMAP_JOIN :
            //
            // ok
            //
            break;
          default :
            //
            // Collision.
            //
            return false;
        }

        for (int dy = -1; dy <= 1; dy++) {
          for (int dx = -1; dx <= 1; dx++) {
            if (! dx && ! dy) {
              continue;
            }

            //
            // No doors next to each other
            //
            switch (l->data[ p.x + dx ][ p.y + dy ].c) {
              case CHARMAP_CHASM :
              case CHARMAP_JOIN :
                //
                // Collision.
                //
                return false;
              default :
                //
                // ok
                //
                break;
            }
          }
        }
        continue;
      }

      //
      // Check all adjacent tiles
      //
      for (int dy = -1; dy <= 1; dy++) {
        for (int dx = -1; dx <= 1; dx++) {
          switch (l->data[ p.x + dx ][ p.y + dy ].c) {
            case CHARMAP_CHASM :
            case CHARMAP_EMPTY :
            case CHARMAP_JOIN :
              //
              // ok
              //
              break;
            default :
              //
              // Collision.
              //
              return false;
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
  while ((int) l->rooms_placed.size() < MAX_LEVEL_ROOM_COUNT) {
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
      if ((int) l->rooms_placed.size() > MIN_LEVEL_ROOM_COUNT) {
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

    l        = new LevelGen();
    l->seed  = std::string(game_get_seed(g));
    l->which = which;

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
    // Check we have enough rooms
    //
    if ((int) l->rooms_placed.size() < MIN_LEVEL_ROOM_COUNT) {
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
    case CHARMAP_DEEP_WATER : return true;
    case CHARMAP_DOOR : return true;
    case CHARMAP_DRY_GRASS : return true;
    case CHARMAP_EXIT : return true;
    case CHARMAP_FLOOR : return true;
    case CHARMAP_FOLIAGE : return true;
    case CHARMAP_FOOD : return true;
    case CHARMAP_JOIN : return true;
    case CHARMAP_KEY : return true;
    case CHARMAP_MOB1 : return true;
    case CHARMAP_MOB2 : return true;
    case CHARMAP_MONST1 : return true;
    case CHARMAP_MONST2 : return true;
    case CHARMAP_PILLAR : return true;
    case CHARMAP_SECRET_DOOR : return true;
    case CHARMAP_SHALLOW_WATER : return true;
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
              l->data[ x ][ y ].c = CHARMAP_EMPTY;
              did_something       = true;
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
              l->data[ x ][ y ].c = CHARMAP_EMPTY;
              did_something       = true;
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
//
static void level_gen_connect_adjacent_rooms(Gamep g, class LevelGen *l, bool debug)
{
  TRACE_NO_INDENT();

  const std::initializer_list< point > directions = {point(-1, 0), point(1, 0), point(0, -1), point(0, 1)};

  //
  // Shortest distance is 2, which is ". ."
  //
  for (int dist = 2; dist < MAX_LEVEL_GEN_CORRIDOR_LEN; dist++) {
    for (int y = dist; y < MAP_HEIGHT - dist - 1; y++) {
      for (int x = dist; x < MAP_WIDTH - dist - 1; x++) {
        switch (l->data[ x ][ y ].c) {
          case CHARMAP_FLOOR :
            {
              //
              // Decrease the chance of connecting leaf rooms so we don't get too many
              //
              if (d100() > 10 - l->rooms_adj_connected) {
                continue;
              }

              for (auto direction : directions) {
                //
                // Check there is nothing in the way
                //
                bool has_clear_path = true;
                for (auto d = 1; d < dist; d++) {
                  point adj(x + direction.x * d, y + direction.y * d);
                  if ((l->data[ adj.x ][ adj.y ].c != CHARMAP_EMPTY)) {
                    has_clear_path = false;
                    break;
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
                if (room_a->room_type != room_b->room_type) {
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
}

//
// Make bridges dramatic...
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

  while (level_gen_trim_dead_tiles(g, l, debug)) {}

  level_gen_scan_connected_rooms(g, l, debug);
  level_gen_connect_adjacent_rooms(g, l, debug);
  level_gen_add_chasms_around_bridges(g, l, debug);

  return l;
}

//
// Test rooms
//
void rooms_test(Gamep g)
{
  TRACE_NO_INDENT();
  rooms_dump(g);
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
  auto seed = game_get_seed_num(g);
  game_set_seed_for_thread(g, seed * which);

  auto l          = level_gen(g, which);
  levels[ which ] = l;
}

void level_gen_test(Gamep g)
{
  TRACE_NO_INDENT();

  int                        max_threads = MAX_LEVELS;
  std::vector< std::thread > threads;

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
