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
static const int MAX_LEVELS                                              = 100;
static const int MAX_LEVEL_GEN_TRIES_FOR_SAME_SEED                       = 100;
static const int MAX_LEVEL_GEN_TRIES_FOR_PLACING_ANY_ROOM_WITH_SAME_DOOR = 500;
static const int MAX_LEVEL_GEN_TRIES_FOR_WALKING_DOORS                   = 100;
static const int MAX_LEVEL_GEN_TRIES_FOR_PLACING_NEW_ROOMS               = 1000;
static const int MAX_LEVEL_GEN_CORRIDOR_LEN                              = 10;
static const int MAX_LEVEL_GEN_MIN_BRIDGE_LEN                            = 6;
static const int MAX_LEVEL_ROOM_COUNT                                    = 100;
static const int MIN_LEVEL_ROOM_COUNT                                    = 10;

class Cell;
class Room;
class LevelGen;

static int level_place_fail_count;

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
  std::vector< point > doors_all;

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
  // Statistics
  //
  int level_place_room_first_fail_count = {};
  int level_place_room_subs_fail_count  = {};
  int level_place_room_dup_count        = {};
  int level_find_door_fail_count        = {};

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
static void room_add(Gamep g, const char *file, int line, ...)
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
void level_gen_stats_dump(Gamep g, class LevelGen *l)
{
  TRACE_NO_INDENT();

  LOG("Global level errors:");
  LOG("- place level fail:             %d", level_place_fail_count);
  LOG("Per level errors:");
  LOG("- place first room fail:        %d", l->level_place_room_first_fail_count);
  LOG("- place subsequent room fail:   %d", l->level_place_room_subs_fail_count);
  LOG("- find door to place room fail: %d", l->level_find_door_fail_count);
  LOG("Per level info:");
  LOG("- duplicate room skipped:       %d", l->level_place_room_dup_count);
}

//
// Update the list of all doors, and return a new unwalked door to use
//
static bool level_gen_random_door_get(Gamep g, class LevelGen *l, point *door_out, class Room **room_out)
{
  TRACE_NO_INDENT();

  l->doors_all.clear();

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
      l->doors_all.push_back(point(x, y));
    }
  }

  //
  // Did we find any new doors?
  //
  if (! l->doors_all.size()) {
    return false;
  }

  //
  // Return a random door
  //
  *door_out = l->doors_all[ pcg_random_range(0, l->doors_all.size()) ];
  *room_out = l->data[ door_out->x ][ door_out->y ].room;

  if (! *room_out) {
    ERR("Found a door with no room");
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
    // Choose a random start point for the rooms
    //
    int   border = MAP_WIDTH / 4;
    int   x      = pcg_random_range(border, MAP_WIDTH - border);
    int   y      = pcg_random_range(border, MAP_HEIGHT - border);
    point at(x, y);

    //
    // Choose a random first room and place it
    //
    auto r = l->room_first = room_random_get(g, l, ROOM_TYPE_START);

    if (! room_can_place_at(g, l, r, at)) {
      l->level_place_room_first_fail_count++;
      continue;
    }

    room_place_at(g, l, r, at);

    //
    // Placed the first room
    //
    if (unlikely(debug)) {
      level_gen_dump(g, l, "placed first room");
    }

    //
    // Ok, we have our first room. Keep placing rooms now.
    //
    int door_place_tries = 0;

    //
    // Up to the maximum rooms per level
    //
    int room_placed_failure_count = 0;
    while ((int) l->rooms_placed.size() < MAX_LEVEL_ROOM_COUNT) {
      if (unlikely(debug)) {
        LOG("rooms placed %d door_place_tries %d room_placed_failure_count %d", (int) l->rooms_placed.size(),
            door_place_tries, room_placed_failure_count);
      }

      //
      // Only try to place rooms against doors so many times
      //
      if (door_place_tries++ > MAX_LEVEL_GEN_TRIES_FOR_WALKING_DOORS) {
        break;
      }

      //
      // Tried enough times to place rooms and failed
      //
      if (room_placed_failure_count > MAX_LEVEL_GEN_TRIES_FOR_PLACING_NEW_ROOMS) {
        break;
      }

      //
      // If struggling to place a room, try an exit
      //
      RoomType room_type = ROOM_TYPE_NORMAL;

      if (! l->has_placed_exit) {
        if ((int) l->rooms_placed.size() > MIN_LEVEL_ROOM_COUNT) {
          room_type = ROOM_TYPE_EXIT;
        } else if (room_placed_failure_count > (MAX_LEVEL_GEN_TRIES_FOR_PLACING_NEW_ROOMS / 10) * 5) {
          room_type = ROOM_TYPE_EXIT;
        }
      }

      //
      // Find a random door that we have not walked before
      //
      point       door_other;
      class Room *room_other = {};

      if (! level_gen_random_door_get(g, l, &door_other, &room_other)) {
        l->level_find_door_fail_count++;
        break;
      }

      //
      // Try multiple rooms with this door
      //
      bool room_was_placed  = false;
      int  room_place_tries = 0;
      while (room_place_tries++ < MAX_LEVEL_GEN_TRIES_FOR_PLACING_ANY_ROOM_WITH_SAME_DOOR) {
        //
        // Get a new room we have not placed before to try to place
        //
        r = room_random_get(g, l, room_type);

        if (l->rooms_placed.find(r) != l->rooms_placed.end()) {
          l->level_place_room_dup_count++;
          continue;
        }

        //
        // For each door in the room, can it be placed to connect to this door?
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
            l->level_place_room_subs_fail_count++;
            continue;
          }

          //
          // Place the room
          //
          room_place_at(g, l, r, door_intersection_at);

          if (r->room_type == ROOM_TYPE_EXIT) {
            l->has_placed_exit = true;
          }

          //
          // Don't try this door again
          //
          l->doors_walked[ door_other ] = true;

          room_was_placed = true;
          break;
        }

        if (room_was_placed) {
          if (unlikely(debug)) {
            level_gen_dump(g, l, "placed another room");
          }
          room_placed_failure_count = 0;
          break;
        }
      }
      room_placed_failure_count++;
    }

    //
    // If we placed enough rooms, this level is good enough to go
    //
    if ((int) l->rooms_placed.size() > MIN_LEVEL_ROOM_COUNT) {
      //
      // Success
      //
      if (! l->has_placed_exit) {
        CON("failed to place exit");
      }
      return l;
    }

    //
    // Not enough rooms
    //
  }

  delete l;
  l = nullptr;

  level_place_fail_count++;

  if (unlikely(debug)) {
    LOG("Failed to create room with seed: %s", game_get_seed(g));
  }

  return nullptr;
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
            // Check the door goes from and to somewhere. Diagonals don't count.
            //
            int neb_count = 0;

            neb_count += (l->data[ x - 1 ][ y ].c != CHARMAP_EMPTY) ? 1 : 0;
            neb_count += (l->data[ x + 1 ][ y ].c != CHARMAP_EMPTY) ? 1 : 0;
            neb_count += (l->data[ x ][ y - 1 ].c != CHARMAP_EMPTY) ? 1 : 0;
            neb_count += (l->data[ x ][ y + 1 ].c != CHARMAP_EMPTY) ? 1 : 0;

            if (neb_count <= 1) {
              l->data[ x ][ y ].c = CHARMAP_EMPTY;
              did_something       = true;
            }
            break;
          }
        case CHARMAP_FLOOR :
          {
            //
            // Check the floor tile is not alone in the world.
            //
            int neb_count = 0;

            neb_count += (l->data[ x - 1 ][ y ].c == CHARMAP_EMPTY) ? 1 : 0;
            neb_count += (l->data[ x + 1 ][ y ].c == CHARMAP_EMPTY) ? 1 : 0;
            neb_count += (l->data[ x ][ y - 1 ].c == CHARMAP_EMPTY) ? 1 : 0;
            neb_count += (l->data[ x ][ y + 1 ].c == CHARMAP_EMPTY) ? 1 : 0;

            //
            // Choose 3 not 4 to make the rooms have fewer single random tiles
            // on the edges. Makes it look more formed.
            //
            if (neb_count >= 3) {
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
// Create all rooms
//
void rooms_init(Gamep g)
{
  TRACE_NO_INDENT();

  /* clang-format off */

  room_add(g, __FUNCTION__, __LINE__, 
           (const char *)"    ^     ",
           (const char *)"    .     ",
           (const char *)"  ........",
           (const char *)"  ........",
           (const char *)"^.........",
           (const char *)"  ........",
           (const char *)"  .....@..",
           (const char *)"  ........",
           (const char *)"  ........",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__, 
           (const char *)"^......  ",
           (const char *)"  ...... ",
           (const char *)"  .......",
           (const char *)"  .......",
           (const char *)"   ...@..",
           (const char *)"    .....",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__, 
           (const char *)"  .......",
           (const char *)"^........",
           (const char *)"  .......",
           (const char *)"  .......",
           (const char *)"    ...@.",
           (const char *)"    .....",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__, 
           (const char *)"     ^ ",
           (const char *)"    ...",
           (const char *)"    ...",
           (const char *)".......",
           (const char *)".......",
           (const char *)".@.....",
           (const char *)".......",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__, 
           (const char *)"^......",
           (const char *)"      .",
           (const char *)"      .",
           (const char *)" ......",
           (const char *)".......",
           (const char *)".@.....",
           (const char *)"...... ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__, 
           (const char *)"......   ",
           (const char *)".@....   ",
           (const char *)"........^",
           (const char *)"......   ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__, 
           (const char *)"  ^     ",
           (const char *)"  . 55  ",
           (const char *)" ....5  ",
           (const char *)"^.m..5  ",
           (const char *)" ......^",
           (const char *)"   ^    ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__, 
           (const char *)"  ^     ",
           (const char *)"  . 55  ",
           (const char *)"^....55 ",
           (const char *)" .m....^",
           (const char *)"   ^    ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__, 
           (const char *)"  ^            ",
           (const char *)"  . 55 55 55   ",
           (const char *)"^.....g......5 ",
           (const char *)" 5........g...^",
           (const char *)"   ^    55     ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__, 
           (const char *)"  ^            ",
           (const char *)"  .            ",
           (const char *)"^....g.......5 ",
           (const char *)" 5....g.......^",
           (const char *)"   ^    55     ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__, 
           (const char *)"  ^  5....5    ",
           (const char *)"  . 5......5   ",
           (const char *)"^........m...5 ",
           (const char *)" 5............^",
           (const char *)"   ^  5555     ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__, 
           (const char *)"  ^ 55   ",
           (const char *)" ....5   ",
           (const char *)"^.m..55  ",
           (const char *)" .......^",
           (const char *)"   ^     ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__, 
           (const char *)"  ^ 55   ",
           (const char *)" ....5   ",
           (const char *)" .m..5   ",
           (const char *)" ....5   ",
           (const char *)" ....5   ",
           (const char *)"^....55  ",
           (const char *)" .......^",
           (const char *)"   ^     ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__, 
           (const char *)"  ^ 55   ",
           (const char *)" ....5   ",
           (const char *)"^....55  ",
           (const char *)" .......^",
           (const char *)" .m.....^",
           (const char *)" .......^",
           (const char *)"   ^     ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__, 
           (const char *)"   ^    ",
           (const char *)" 5....5 ",
           (const char *)"^...g.. ",
           (const char *)" 5.....^",
           (const char *)"  55.5  ",
           (const char *)"    .   ",
           (const char *)"    ^   ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__, 
           (const char *)"   ^      ",
           (const char *)" 5...555  ",
           (const char *)"^......5  ",
           (const char *)" 5.......^",
           (const char *)"  cCCCc   ",
           (const char *)"  5...5   ",
           (const char *)"  5.g.5   ",
           (const char *)"  5...5   ",
           (const char *)"    .     ",
           (const char *)"    ^     ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__, 
           (const char *)"   ^    ",
           (const char *)" ...555 ",
           (const char *)" .....5 ",
           (const char *)"^..g..5 ",
           (const char *)" 555...^",
           (const char *)"    ^ 5 ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__, 
           (const char *)"   ^            ",
           (const char *)" 5..    55  55  ",
           (const char *)" ...55  55  55  ",
           (const char *)"^.......g...... ",
           (const char *)" 5.....5555....^",
           (const char *)"    ^ 55  55    ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__, 
           (const char *)"   ^            ",
           (const char *)" 5..    55  55  ",
           (const char *)" ...55555555555 ",
           (const char *)"^........555...5",
           (const char *)" 5....m........5",
           (const char *)" 55............ ",
           (const char *)"  5....5555....^",
           (const char *)"    ^ 55  55    ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__, 
           (const char *)"   ^    ",
           (const char *)" ...555 ",
           (const char *)" .....5 ",
           (const char *)"^.....5 ",
           (const char *)" 5....5 ",
           (const char *)" 555...^",
           (const char *)"    ^ 5 ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__, 
           (const char *)"   ^     ",
           (const char *)" ...555  ",
           (const char *)" .....5  ",
           (const char *)"^......5 ",
           (const char *)" 5.....5 ",
           (const char *)" 5.....5 ",
           (const char *)" 5....5  ",
           (const char *)" 555....^",
           (const char *)"    ^ 5  ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__, 
           (const char *)"     ^   ",
           (const char *)" ..55.55 ",
           (const char *)" ......5 ",
           (const char *)"^......5 ",
           (const char *)" 5.....5 ",
           (const char *)" 555....^",
           (const char *)"    ^  5 ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__, 
           (const char *)"     ^    ",
           (const char *)" ..55.555 ",
           (const char *)" .......5 ",
           (const char *)"^.m.....5 ",
           (const char *)" 5......5 ",
           (const char *)" 555.....^",
           (const char *)"    ^   5 ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__, 
           (const char *)"     ^     ",
           (const char *)" ..55.5555 ",
           (const char *)" .m......5 ",
           (const char *)"^........5 ",
           (const char *)" 5.......5 ",
           (const char *)" 555.5....^",
           (const char *)"    ^ 5555 ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__, 
           (const char *)"        ^   ",
           (const char *)" .....55.55 ",
           (const char *)" .........5 ",
           (const char *)"^.......m.5 ",
           (const char *)" 5........5 ",
           (const char *)" 555.5..5..^",
           (const char *)"    ^ 55 55 ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__, 
           (const char *)"  ^     ",
           (const char *)" 5..... ",
           (const char *)" 5.g... ",
           (const char *)"^......5",
           (const char *)" 5.....5",
           (const char *)" 5....5 ",
           (const char *)" 555...^",
           (const char *)"    ^ 5 ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__, 
           (const char *)"   ^    ",
           (const char *)" 55.....",
           (const char *)" 5....g.",
           (const char *)"^.......",
           (const char *)" 5......",
           (const char *)" 5....5 ",
           (const char *)" 5....5 ",
           (const char *)" 555...^",
           (const char *)"    ^ . ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__, 
           (const char *)"   ^   ",
           (const char *)" 5.....",
           (const char *)" 5...g.",
           (const char *)" 5.....",
           (const char *)"^......",
           (const char *)" 5...5 ",
           (const char *)" 5...5 ",
           (const char *)" 5...5 ",
           (const char *)" 5....^",
           (const char *)"  ^    ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__, 
           (const char *)"   ^   ",
           (const char *)" ...55 ",
           (const char *)" ....5 ",
           (const char *)" ..    ",
           (const char *)" ..    ",
           (const char *)" ..... ",
           (const char *)" ...g. ",
           (const char *)" ..... ",
           (const char *)" ..... ",
           (const char *)"^..... ",
           (const char *)" 5.... ",
           (const char *)" 5.... ",
           (const char *)" 5.... ",
           (const char *)" 5....^",
           (const char *)"  ^    ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__, 
           (const char *)"   ^               ",
           (const char *)" ...............55 ",
           (const char *)" .g..............5 ",
           (const char *)" ..............55  ",
           (const char *)" ..............5   ",
           (const char *)" .....55           ",
           (const char *)" .....5            ",
           (const char *)" ccccc             ",
           (const char *)" .....             ",
           (const char *)"^.....             ",
           (const char *)" 5....             ",
           (const char *)" 5....             ",
           (const char *)" 5....             ",
           (const char *)" 5....^            ",
           (const char *)"  ^                ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__, 
           (const char *)"   ^               ",
           (const char *)" .....             ",
           (const char *)" .m...             ",
           (const char *)" .....5            ",
           (const char *)" .....55           ",
           (const char *)" ........c......55 ",
           (const char *)" ........c.......5 ",
           (const char *)" .......c..g...55  ",
           (const char *)" .......c......5   ",
           (const char *)"^.....             ",
           (const char *)" 5....             ",
           (const char *)" 5....             ",
           (const char *)" 5....             ",
           (const char *)" 5....^            ",
           (const char *)"  ^                ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__, 
           (const char *)"   ^   ",
           (const char *)" ...55 ",
           (const char *)" ....5 ",
           (const char *)" ..... ",
           (const char *)"   ... ",
           (const char *)"   c..c",
           (const char *)" ..cCCc",
           (const char *)" ..c..c",
           (const char *)" .m... ",
           (const char *)"^..... ",
           (const char *)" 5.... ",
           (const char *)" 5.... ",
           (const char *)" 5.... ",
           (const char *)" 5....^",
           (const char *)"  ^    ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__, 
           (const char *)"   ^    ",
           (const char *)" ...55  ",
           (const char *)" ....5  ",
           (const char *)" .....  ",
           (const char *)" .....  ",
           (const char *)" .....  ",
           (const char *)"  ..... ",
           (const char *)"  ..... ",
           (const char *)"  ..m.. ",
           (const char *)"^...... ",
           (const char *)"  5.... ",
           (const char *)"  5.... ",
           (const char *)"  5.... ",
           (const char *)"  5....^",
           (const char *)"   ^    ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__, 
           (const char *)"   ^         ",
           (const char *)" 5.......... ",
           (const char *)" 5.m........^",
           (const char *)" 5.......... ",
           (const char *)"^....5555    ",
           (const char *)" 5...5       ",
           (const char *)" 5...5       ",
           (const char *)" 5...5       ",
           (const char *)" 5.555       ",
           (const char *)"  ^          ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__, 
           (const char *)"  ^     ",
           (const char *)" 5..... ",
           (const char *)" 5..... ",
           (const char *)" 5..... ",
           (const char *)"^....m.5",
           (const char *)" ......5",
           (const char *)"5.....5 ",
           (const char *)"5...... ",
           (const char *)" 5.555.^",
           (const char *)"  ^     ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__, 
           (const char *)"    ^     ",
           (const char *)"   5.555  ",
           (const char *)"   5....5 ",
           (const char *)"  5..m..5 ",
           (const char *)"^.......5 ",
           (const char *)"  5.....5 ",
           (const char *)".........^",
           (const char *)".......55 ",
           (const char *)".....55   ",
           (const char *)"    ^     ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__, 
           (const char *)"    ^     ",
           (const char *)"   5..... ",
           (const char *)"  5...m.. ",
           (const char *)" 5....... ",
           (const char *)"^........ ",
           (const char *)" 555..... ",
           (const char *)"    5....^",
           (const char *)"     5..5 ",
           (const char *)"     5.5  ",
           (const char *)"      ^   ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__, 
           (const char *)"    ^     ",
           (const char *)"  55.55.. ",
           (const char *)" 5....... ",
           (const char *)" 5....... ",
           (const char *)"^....m... ",
           (const char *)" 5....... ",
           (const char *)"  5......^",
           (const char *)"  5....55 ",
           (const char *)"   5.55   ",
           (const char *)"    ^     ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__, 
           (const char *)"    ^   55",
           (const char *)"  ...555.5",
           (const char *)"  .......5",
           (const char *)"  ...m..5 ",
           (const char *)"^.......5 ",
           (const char *)"  5.....5 ",
           (const char *)"  5......^",
           (const char *)" 5.5...55 ",
           (const char *)"5.5 .55   ",
           (const char *)"55  ^     ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__, 
           (const char *)" ^           ",
           (const char *)" ..........  ",
           (const char *)" 5.........  ",
           (const char *)" 5.......m.5 ",
           (const char *)"^..........5 ",
           (const char *)" 55........5 ",
           (const char *)"  5.........^",
           (const char *)"  5........5 ",
           (const char *)"   5.555555  ",
           (const char *)"    ^        ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__, 
           (const char *)" ^           ",
           (const char *)" .555        ",
           (const char *)" ...5   5555 ",
           (const char *)"  5.55  5g.5 ",
           (const char *)"^.....cc...5 ",
           (const char *)"  5..5  5..5 ",
           (const char *)"  5..5  5...^",
           (const char *)"  5..5  5555 ",
           (const char *)"   5.5       ",
           (const char *)"    ^        ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__, 
           (const char *)"^........555 ",
           (const char *)" ..55....g..5",
           (const char *)"    CCc.....5",
           (const char *)"   CCCCc..cC ",
           (const char *)"    CCc....5 ",
           (const char *)"^..55.......^",
           (const char *)" .........5  ",
           (const char *)" 5...55555   ",
           (const char *)"    ^        ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__, 
           (const char *)"^.........   ",
           (const char *)" 555........ ",
           (const char *)"    5ccc.... ",
           (const char *)"     CCCc.g. ",
           (const char *)"     CCc.... ",
           (const char *)" 5555cc..... ",
           (const char *)"^...........^",
           (const char *)" 5........5  ",
           (const char *)"  5.....5    ",
           (const char *)"    ^        ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__, 
           (const char *)"     ^       ",
           (const char *)"  5..g..5    ",
           (const char *)" 5........5  ",
           (const char *)"^...cccc....^",
           (const char *)" 5..cCCc.... ",
           (const char *)"^...cccc....^",
           (const char *)" 5........5  ",
           (const char *)"  5.....5    ",
           (const char *)"    ^        ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__, 
           (const char *)"     ^       ",
           (const char *)"  5....5  .. ",
           (const char *)" 5......cc.. ",
           (const char *)"^.....CCCc   ",
           (const char *)" 5.....CCCc. ",
           (const char *)"^...g.......^",
           (const char *)" 5........5  ",
           (const char *)"  5.....5    ",
           (const char *)"    ^        ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__, 
           (const char *)"         ^   ",
           (const char *)"         ..5 ",
           (const char *)"         ... ",
           (const char *)"   5........ ",
           (const char *)"^....g...... ",
           (const char *)"  5......... ",
           (const char *)"   55555....^",
           (const char *)"       5.... ",
           (const char *)"       5.... ",
           (const char *)"       55... ",
           (const char *)"           ^ ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__, 
           (const char *)"         ^   ",
           (const char *)"         ..5 ",
           (const char *)"         ... ",
           (const char *)"          c  ",
           (const char *)"          c  ",
           (const char *)"          c  ",
           (const char *)"         ... ",
           (const char *)"         ... ",
           (const char *)"   5........ ",
           (const char *)"^.........g. ",
           (const char *)"  5......... ",
           (const char *)"   55555....^",
           (const char *)"           ^ ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__, 
           (const char *)"         ^   ",
           (const char *)"  ....   ..5 ",
           (const char *)"  ....cCc... ",
           (const char *)"  .g..    .  ",
           (const char *)"  $...    c  ",
           (const char *)"          .  ",
           (const char *)"         ... ",
           (const char *)"         ... ",
           (const char *)"   5........ ",
           (const char *)"^........... ",
           (const char *)"  5......... ",
           (const char *)"   55555....^",
           (const char *)"           ^ ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__, 
           (const char *)"         ^   ",
           (const char *)"   ........5 ",
           (const char *)"   c........ ",
           (const char *)"    cc.......",
           (const char *)"     cC......",
           (const char *)"     cCC.....",
           (const char *)"     cCCCcCCc",
           (const char *)"    cC.......",
           (const char *)"   5.....g...",
           (const char *)"^............",
           (const char *)"  5......... ",
           (const char *)"   55555....^",
           (const char *)"           ^ ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__, 
           (const char *)"         ^   ",
           (const char *)"        5..55",
           (const char *)"       5....5",
           (const char *)"     55..g..5",
           (const char *)"    5.......5",
           (const char *)"   5.......5 ",
           (const char *)"   5.CCc...5 ",
           (const char *)"      CCc....",
           (const char *)"   5.CCc.....",
           (const char *)"^....cc......",
           (const char *)"  5......... ",
           (const char *)"   55555....^",
           (const char *)"           ^ ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__, 
           (const char *)"         ^   ",
           (const char *)"...........55",
           (const char *)"..g.........5",
           (const char *)"5...........5",
           (const char *)" 5...........",
           (const char *)"  5..........",
           (const char *)"   5.........",
           (const char *)"   5.........",
           (const char *)"   5.........",
           (const char *)"^............",
           (const char *)"  5......... ",
           (const char *)"   55555....^",
           (const char *)"        ^  . ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__, 
           (const char *)"         ^   ",
           (const char *)"        5..5 ",
           (const char *)" 5     55... ",
           (const char *)"^.....c..... ",
           (const char *)" 5..g.c..... ",
           (const char *)" 55...c.....^",
           (const char *)"        ^    ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__, 
           (const char *)"         ^   ",
           (const char *)"        5..5 ",
           (const char *)"        5... ",
           (const char *)"^.....c..... ",
           (const char *)" 5....c..g.. ",
           (const char *)" 5....c..... ",
           (const char *)" 5...   .... ",
           (const char *)" 55..   ....^",
           (const char *)"   ^         ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__, 
           (const char *)"         ^   ",
           (const char *)"        5..5 ",
           (const char *)"        5... ",
           (const char *)"^.....c..... ",
           (const char *)" 5....c..... ",
           (const char *)" 5....c..... ",
           (const char *)" 5...ccc.... ",
           (const char *)" 55..ccc.g.. ",
           (const char *)" 5...ccc.... ",
           (const char *)" 55...c.....^",
           (const char *)"   ^         ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__, 
           (const char *)"         ^   ",
           (const char *)"        5..5 ",
           (const char *)"        5... ",
           (const char *)"^........... ",
           (const char *)" 5.......... ",
           (const char *)" 5......g... ",
           (const char *)" 5...m...... ",
           (const char *)" 55.........^",
           (const char *)"   ^         ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__, 
           (const char *)"    ^    ^   ",
           (const char *)"  5..5  5..5 ",
           (const char *)"  ...5  5... ",
           (const char *)"^.....cc.... ",
           (const char *)" 5..m.cc..g. ",
           (const char *)" 55...cc....^",
           (const char *)"        ^    ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__, 
           (const char *)"         ^   ",
           (const char *)" 55......... ",
           (const char *)" 5.........5 ",
           (const char *)"^.......m..5 ",
           (const char *)" 5.........5 ",
           (const char *)" 55.........^",
           (const char *)"        ^    ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__, 
           (const char *)"         ^   ",
           (const char *)" 55..c......^",
           (const char *)" 5....c....5 ",
           (const char *)"^......c.m.5 ",
           (const char *)" 5.   c....5 ",
           (const char *)" 55   ....55 ",
           (const char *)"        ^    ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__, 
           (const char *)"         ^   ",
           (const char *)"       5...  ",
           (const char *)"      5....  ",
           (const char *)"     5...... ",
           (const char *)"     5...... ",
           (const char *)"   55....... ",
           (const char *)"^.c......m.. ",
           (const char *)"  c......... ",
           (const char *)"  c.........^",
           (const char *)"  c......... ",
           (const char *)"  c......... ",
           (const char *)"   5........ ",
           (const char *)"           ^ ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__, 
           (const char *)"         ^   ",
           (const char *)"     5555..  ",
           (const char *)"     5.....  ",
           (const char *)"     5..cc.. ",
           (const char *)"     5..ccc. ",
           (const char *)"   55...ccc. ",
           (const char *)"^......ccc.. ",
           (const char *)"   ......c..^",
           (const char *)"   5..m..... ",
           (const char *)"           ^ ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__, 
           (const char *)"             ^  ",
           (const char *)"     5555.....  ",
           (const char *)"     5........  ",
           (const char *)"     5......... ",
           (const char *)"     5...m..... ",
           (const char *)"   55.......... ",
           (const char *)"^.............. ",
           (const char *)"   ............^",
           (const char *)"   5........... ",
           (const char *)"      5...5   ^ ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__, 
           (const char *)"             ^     ",
           (const char *)"     5555......55  ",
           (const char *)"     5..........5  ",
           (const char *)"     5...........5 ",
           (const char *)"     5............ ",
           (const char *)"   55.............^",
           (const char *)"^..............5   ",
           (const char *)"   ....m.......    ",
           (const char *)"   5...........    ",
           (const char *)"      5...5   ^    ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__, 
           (const char *)"             ^        ",
           (const char *)"     5555.........5   ",
           (const char *)"     5.............5  ",
           (const char *)"     5............... ",
           (const char *)"     5............... ",
           (const char *)"   55................^",
           (const char *)"^......m.......5      ",
           (const char *)"   ............       ",
           (const char *)"   5...........       ",
           (const char *)"      5...5   ^       ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__, 
           (const char *)"     ^          ",
           (const char *)"  55...5        ",
           (const char *)" 5......5       ",
           (const char *)" 5.......5....  ",
           (const char *)" 5............  ",
           (const char *)"5............5  ",
           (const char *)"5....m........5 ",
           (const char *)"5.............5 ",
           (const char *)" 5...........5  ",
           (const char *)" 5...........5  ",
           (const char *)" 5...........5  ",
           (const char *)"^..............^",
           (const char *)" 5..........55  ",
           (const char *)"  5.....5       ",
           (const char *)"    ^           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__, 
           (const char *)"         ^         ",
           (const char *)"  55......5        ",
           (const char *)" 5.........5       ",
           (const char *)" 5..........5....  ",
           (const char *)" 5...............  ",
           (const char *)"5...............5  ",
           (const char *)"5......m.........5 ",
           (const char *)"5................5 ",
           (const char *)" 5..............5  ",
           (const char *)" 5g.............5  ",
           (const char *)" 5..............5  ",
           (const char *)"^.................^",
           (const char *)" 5.............55  ",
           (const char *)"  5........5       ",
           (const char *)"    ^              ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__, 
           (const char *)"         ^               ",
           (const char *)"  55......5              ",
           (const char *)" 5.........5             ",
           (const char *)" 5..........5...5        ",
           (const char *)" 5.....m...C.....        ",
           (const char *)"5...........CCCC.5....5  ",
           (const char *)"5..........CCg.CC.......^",
           (const char *)"5.........C..C..CC.....5 ",
           (const char *)" 5..............55       ",
           (const char *)" 5..............5        ",
           (const char *)" 5...........m..5        ",
           (const char *)"^................5       ",
           (const char *)" 5.............55        ",
           (const char *)"  5........5             ",
           (const char *)"    ^                    ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__, 
           (const char *)"             ^        ",
           (const char *)"  5555555.........5   ",
           (const char *)"  555555...........5  ",
           (const char *)"  5555.5............. ",
           (const char *)"  55555.............. ",
           (const char *)"  555................^",
           (const char *)" 5...............55   ",
           (const char *)"5...............5555  ",
           (const char *)"5................5555 ",
           (const char *)"55...........m...5555 ",
           (const char *)" 555............5555  ",
           (const char *)" 5555...........555   ",
           (const char *)" 5..............5     ",
           (const char *)"^.................^   ",
           (const char *)" 5.............55     ",
           (const char *)"  5........5          ",
           (const char *)"    ^                 ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__, 
           (const char *)"             ^        ",
           (const char *)"         55.......5   ",
           (const char *)"         55........5  ",
           (const char *)"         ............ ",
           (const char *)"         ....m....... ",
           (const char *)"        5............^",
           (const char *)" 5...............55   ",
           (const char *)"5...............5555  ",
           (const char *)"5................5555 ",
           (const char *)"55....m..........5555 ",
           (const char *)" 555............5555  ",
           (const char *)" 5555...........555   ",
           (const char *)" 5..............5     ",
           (const char *)"^........             ",
           (const char *)" 5.......^            ",
           (const char *)"  5......             ",
           (const char *)"    ^                 ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__, 
           (const char *)"             ^      ",
           (const char *)"         55......55 ",
           (const char *)"         55.......5 ",
           (const char *)"         .......... ",
           (const char *)"         ....m..... ",
           (const char *)"        5..........^",
           (const char *)" 5..............555 ",
           (const char *)"^........5          ",
           (const char *)"^........           ",
           (const char *)"^........           ",
           (const char *)" 5....m..^          ",
           (const char *)" 55......           ",
           (const char *)"    ^               ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__, 
           (const char *)"             ^      ",
           (const char *)"   CCCCCCC5......55 ",
           (const char *)"   C......5..m....5 ",
           (const char *)"   C.CCCC.......... ",
           (const char *)"   C.CCCC.......... ",
           (const char *)"   C.CCCC..........^",
           (const char *)" 5..............555 ",
           (const char *)"^........CCCCCCCC   ",
           (const char *)"^........CCCCCCCC   ",
           (const char *)"^........CCC....C   ",
           (const char *)" 5.....m.   .m$.    ",
           (const char *)" 55......   ....    ",
           (const char *)"    ^               ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__, 
           (const char *)"             ^      ",
           (const char *)"   CCCCCCCC....C.55 ",
           (const char *)"  5C......C....C..5 ",
           (const char *)"  5C.CCCC...C..C... ",
           (const char *)"  5C.CCCC...C...... ",
           (const char *)"  5C.CCCC...C......^",
           (const char *)"    ^               ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__, "",
           (const char *)"             ^          ",
           (const char *)"      5555.......555555 ",
           (const char *)"     5555..........5555 ",
           (const char *)"     55..............55 ",
           (const char *)"   5555................ ",
           (const char *)"   5555................ ",
           (const char *)"   5555.......m........ ",
           (const char *)"  555..................^",
           (const char *)" 55................55   ",
           (const char *)"55................5555  ",
           (const char *)"55.................5555 ",
           (const char *)"55.................5555 ",
           (const char *)" 55...............5555  ",
           (const char *)" 55...............555   ",
           (const char *)" 5................5     ",
           (const char *)"^.....................^ ",
           (const char *)" 5...........555555     ",
           (const char *)"  5.....555555          ",
           (const char *)"    ^                   ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__, "",
           (const char *)"             ^          ",
           (const char *)"      5555.......555555 ",
           (const char *)"     5555..........5555 ",
           (const char *)"     55..............55 ",
           (const char *)"   5555................ ",
           (const char *)"   5555......m......... ",
           (const char *)"   555................. ",
           (const char *)"   555.......... ...... ",
           (const char *)"   555.........   ..... ",
           (const char *)"   555.......... ...... ",
           (const char *)"   55.................. ",
           (const char *)"  555..... ............^",
           (const char *)" 55......   .......55   ",
           (const char *)"55... .... .......5555  ",
           (const char *)"55..  .............5555 ",
           (const char *)"55.$ ..............5555 ",
           (const char *)" 55 ..............5555  ",
           (const char *)" 55...............555   ",
           (const char *)" 5........m.......5     ",
           (const char *)"^.....................^ ",
           (const char *)" 5...........555555     ",
           (const char *)"  5.....555555          ",
           (const char *)"    ^                   ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__, "",
           (const char *)"                ^          ",
           (const char *)"      5555..........55555  ",
           (const char *)"     5555.............5555 ",
           (const char *)"     55............m....55 ",
           (const char *)"   5555....C.............5 ",
           (const char *)"   5555...CCC...........5  ",
           (const char *)"   555.....C...........5   ",
           (const char *)"   555.............C...5   ",
           (const char *)"   555............CCC..55  ",
           (const char *)"   555.............C.....5 ",
           (const char *)"   55..................... ",
           (const char *)"  555........C....m.......^",
           (const char *)" 55......CCCCCC.......55   ",
           (const char *)"55...........C.......5555  ",
           (const char *)"55...m................5555 ",
           (const char *)"55....................5555 ",
           (const char *)" 55.....C............5555  ",
           (const char *)" 55....CCC...........555   ",
           (const char *)" 5......C............5     ",
           (const char *)"^.....................^    ",
           (const char *)" 5..............555555     ",
           (const char *)"  5.....55...5555          ",
           (const char *)"    ^                      ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)" ... ..... ",
           (const char *)" .T. ..@..^",
           (const char *)" ... ..b.. ",
           (const char *)" ...   s   ",
           (const char *)" .$.  ...  ",
           (const char *)" ...  .$.  ",
           (const char *)"       C   ",
           (const char *)" .... ...  ",
           (const char *)" .f..C.T.  ",
           (const char *)" .m.. ...  ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)" ... ..... ",
           (const char *)" .T. ..@..^",
           (const char *)" ... ..b.. ",
           (const char *)" ...   s   ",
           (const char *)" .$.  ...  ",
           (const char *)" ...  .$.  ",
           (const char *)"       C   ",
           (const char *)" .... ...  ",
           (const char *)" .f..C.T.  ",
           (const char *)" .m.. ...  ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"    .....  ",
           (const char *)"    .   f  ",
           (const char *)"    s      ",
           (const char *)"    ....^  ",
           (const char *)"........   ",
           (const char *)"....@...   ",
           (const char *)".......    ",
           (const char *)"....       ",
           (const char *)" ..        ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"$ Wwwwwww. ",
           (const char *)".sWWww .@. ",
           (const char *)"       ... ",
           (const char *)"^..... ... ",
           (const char *)" ..... ... ",
           (const char *)" ......... ",
           (const char *)" .T.......^",
           (const char *)"         ^ ",
           (const char *)" .T....    ",
           (const char *)" ......    ",
           (const char *)" .m...$    ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"  ^        ",
           (const char *)"  . .....m ",
           (const char *)"  . .T.... ",
           (const char *)"  . $....m ",
           (const char *)"  .     s  ",
           (const char *)"..... f w  ",
           (const char *)"..... s W  ",
           (const char *)"...@..w W  ",
           (const char *)".....wwWWw^",
           (const char *)"....www    ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"    ^      ",
           (const char *)"    .      ",
           (const char *)"   .....   ",
           (const char *)".. ....f   ",
           (const char *)"$.s.@...   ",
           (const char *)".. ......^ ",
           (const char *)"   ^       ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"     ^     ",
           (const char *)"...`m.``...",
           (const char *)"..``.....`.",
           (const char *)".`.`.......",
           (const char *)"...........",
           (const char *)"......... f",
           (const char *)"    C=C    ",
           (const char *)"    C=C    ",
           (const char *)"    C=C ...",
           (const char *)"    ... ...",
           (const char *)"    .....@.",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"     ^     ",
           (const char *)"     #     ",
           (const char *)"     #     ",
           (const char *)"$CC``.. .. ",
           (const char *)"mCCC`.. CCC",
           (const char *)".CC``...==@",
           (const char *)".CCC .. CCC",
           (const char *)".CC. ..    ",
           (const char *)"fCC.... ...",
           (const char *)".CC...bs..m",
           (const char *)" ....`` ..$",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"  ^        ",
           (const char *)" ##      m.",
           (const char *)" #        .",
           (const char *)" #  ```.==.",
           (const char *)" #  ````  s",
           (const char *)" .  ````  .",
           (const char *)" .    `  ..",
           (const char *)" .    `` .$",
           (const char *)" ...  .`   ",
           (const char *)"^C@.  .CCCC",
           (const char *)" ......CCCC",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"     ^     ",
           (const char *)"... C=C    ",
           (const char *)".@. C=C    ",
           (const char *)"... C=C  ..",
           (const char *)" .. C=C  ..",
           (const char *)"C.CCC=C  ..",
           (const char *)"....C=C  ..",
           (const char *)".C`.C=C  ..",
           (const char *)".CC.....   ",
           (const char *)".CCCCCC. ..",
           (const char *)"      `==..",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"     ^ ....",
           (const char *)" m.......@.",
           (const char *)" `.`.  ....",
           (const char *)"  ```  ... ",
           (const char *)"  CCC  ``..",
           (const char *)" ....   .`.",
           (const char *)" ....   ...",
           (const char *)" ..$.  C=C ",
           (const char *)" $...  C=C ",
           (const char *)"^....  C=C ",
           (const char *)"  ....m... ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"     ^     ",
           (const char *)"... .CCm   ",
           (const char *)"m.. .... .$",
           (const char *)" .   .   ..",
           (const char *)"...... ....",
           (const char *)"....@. ...m",
           (const char *)"...... .CCC",
           (const char *)"...... .===",
           (const char *)"CCC CC  CCC",
           (const char *)"... .```...",
           (const char *)"..$ .......",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"     ^     ",
           (const char *)"    C=C    ",
           (const char *)"    C=C    ",
           (const char *)"$CC``=C...^",
           (const char *)".CCC`..... ",
           (const char *)".CC``..@.. ",
           (const char *)" CCC       ",
           (const char *)" CC ...... ",
           (const char *)" CC .    . ",
           (const char *)"^......  ..",
           (const char *)"        $..",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"  ^        ",
           (const char *)" ####    ..",
           (const char *)" #  #     .",
           (const char *)" #  ####CC.",
           (const char *)" #  #  #   ",
           (const char *)" .  #  #   ",
           (const char *)" .  .  #   ",
           (const char *)" .  ..``   ",
           (const char *)" .  ...`   ",
           (const char *)"^....@..^  ",
           (const char *)" .......   ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"     ^     ",
           (const char *)"..ww #     ",
           (const char *)".@.w #     ",
           (const char *)".... #.CC. ",
           (const char *)".... #   . ",
           (const char *)" .   #   . ",
           (const char *)".... #   . ",
           (const char *)".C`. #   . ",
           (const char *)".CC..... . ",
           (const char *)".CCCCCCm . ",
           (const char *)"       ^ .^",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"     ^     ",
           (const char *)" .......ww ",
           (const char *)" w...@...w ",
           (const char *)" www...... ",
           (const char *)"        `. ",
           (const char *)" ....   ``^",
           (const char *)" ....   `  ",
           (const char *)" ..$.   C  ",
           (const char *)" $...   C  ",
           (const char *)"^....   C  ",
           (const char *)"    .m...  ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"     ^     ",
           (const char *)" .......   ",
           (const char *)" .....     ",
           (const char *)"..`.....   ",
           (const char *)"....`....  ",
           (const char *)".........  ",
           (const char *)" ...C=C..  ",
           (const char *)" ...C=C.   ",
           (const char *)"    C=C    ",
           (const char *)"    .@.    ",
           (const char *)"    |.|    ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"     ^     ",
           (const char *)"     #     ",
           (const char *)"     #     ",
           (const char *)"$CC``..... ",
           (const char *)".CC`...... ",
           (const char *)".CC`..C@.. ",
           (const char *)"     .CC.. ",
           (const char *)" ......... ",
           (const char *)" ........  ",
           (const char *)"^......    ",
           (const char *)" ......    ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"  ^        ",
           (const char *)"  #    CC..",
           (const char *)"  #    C ..",
           (const char *)"  ####=CC..",
           (const char *)"     C=CC..",
           (const char *)" ... C=CC..",
           (const char *)" ... C=CC..",
           (const char *)" ... C.....",
           (const char *)"   CCC.....",
           (const char *)"^.    ..@..",
           (const char *)" ...$......",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"     ^     ",
           (const char *)"...  #     ",
           (const char *)"......     ",
           (const char *)".......``..",
           (const char *)".......  ..",
           (const char *)"..@....  ..",
           (const char *)".......  ..",
           (const char *)" ......  ..",
           (const char *)" .       ..",
           (const char *)" .    .....",
           (const char *)" ^    ...m.",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"     ^     ",
           (const char *)" ......... ",
           (const char *)" ....@.... ",
           (const char *)" ......... ",
           (const char *)"   C=C ... ",
           (const char *)"   C=C  .  ",
           (const char *)"   C=C     ",
           (const char *)" ..```...  ",
           (const char *)" .........^",
           (const char *)"^......... ",
           (const char *)"    ^      ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"     ^     ",
           (const char *)"     #     ",
           (const char *)"     #     ",
           (const char *)"   $`...   ",
           (const char *)"   ``...   ",
           (const char *)"  .......  ",
           (const char *)"  .    ..  ",
           (const char *)" ...   ... ",
           (const char *)" .@....... ",
           (const char *)" ...   ... ",
           (const char *)"        ^  ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"     ^     ",
           (const char *)"     #  ..^",
           (const char *)"     #   . ",
           (const char *)"     ..... ",
           (const char *)"    ...... ",
           (const char *)"    ...@...",
           (const char *)"    `......",
           (const char *)"^.````.....",
           (const char *)"       ....",
           (const char *)"        ...",
           (const char *)"         ^ ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"  ^        ",
           (const char *)"  ####     ",
           (const char *)"  #  t     ",
           (const char *)"  #####    ",
           (const char *)"    # #    ",
           (const char *)"    # #  . ",
           (const char *)"    # #  ..",
           (const char *)"    #......",
           (const char *)"      ...@.",
           (const char *)"  $````....",
           (const char *)"       ^   ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"     ^     ",
           (const char *)"     #     ",
           (const char *)" $``..     ",
           (const char *)" ``...     ",
           (const char *)" `........ ",
           (const char *)" ......@.. ",
           (const char *)"^......... ",
           (const char *)"     ...`. ",
           (const char *)"     .....^",
           (const char *)"     ..`.. ",
           (const char *)"       ^   ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"     ^     ",
           (const char *)"   ...``   ",
           (const char *)"   ....`   ",
           (const char *)"^m........^",
           (const char *)"   .`..    ",
           (const char *)"   ....    ",
           (const char *)"CCCC..`.   ",
           (const char *)"C.|.....   ",
           (const char *)"C.@....    ",
           (const char *)"C.|..`$    ",
           (const char *)"CCCCC      ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"     ^     ",
           (const char *)"     #     ",
           (const char *)"     #  ...",
           (const char *)" ``........",
           (const char *)" ` ........",
           (const char *)" . ........",
           (const char *)" ` ..@.....",
           (const char *)" ` ........",
           (const char *)" .         ",
           (const char *)" ..`...$   ",
           (const char *)" ^         ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"     ^     ",
           (const char *)"     #     ",
           (const char *)"     #     ",
           (const char *)" .```. ... ",
           (const char *)" CCCC. .@. ",
           (const char *)" CCCC..... ",
           (const char *)" CCCC. .   ",
           (const char *)"^.```  .   ",
           (const char *)"      .....",
           (const char *)"      .....",
           (const char *)"         ^ ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"  ^        ",
           (const char *)"  ###......",
           (const char *)"  # #    ..",
           (const char *)"  t####  ..",
           (const char *)"   `  #  ..",
           (const char *)"   `  #  ..",
           (const char *)"   `  #  ..",
           (const char *)"  `.  ....^",
           (const char *)"  .   .....",
           (const char *)"  $   ..@..",
           (const char *)"  .CCC. ...",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"     ^     ",
           (const char *)"     #``m  ",
           (const char *)".. ...  $  ",
           (const char *)"......     ",
           (const char *)"...... ....",
           (const char *)"...... ....",
           (const char *)"`..... ....",
           (const char *)"b..... ....",
           (const char *)"s .... ....",
           (const char *)".. ......@^",
           (const char *)"$.   . ..^.",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"     ^     ",
           (const char *)"^m.........",
           (const char *)"     ......",
           (const char *)"  ``sb.....",
           (const char *)"  $`  .....",
           (const char *)"       .   ",
           (const char *)" ...   .   ",
           (const char *)".... ....`.",
           (const char *)"...........",
           (const char *)".``. ..@..^",
           (const char *)" ... ......",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"     ^     ",
           (const char *)"     #     ",
           (const char *)"     #     ",
           (const char *)"   ...wW   ",
           (const char *)"   ...ww   ",
           (const char *)"  w....w   ",
           (const char *)"  ww.@.... ",
           (const char *)"  Www..... ",
           (const char *)"  w....... ",
           (const char *)"  w......w ",
           (const char *)"   ....wwW ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"     ^     ",
           (const char *)" `..## WWW ",
           (const char *)" w.    W w ",
           (const char *)" w. wwww w ",
           (const char *)" .. ..ww . ",
           (const char *)" .w ...@ . ",
           (const char *)" .w      w ",
           (const char *)" .....w.ww ",
           (const char *)"  .....wwW ",
           (const char *)"  ww...wwW ",
           (const char *)"   ww.....^",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"  ^        ",
           (const char *)"  #        ",
           (const char *)"  #        ",
           (const char *)"  #####    ",
           (const char *)"   #  #    ",
           (const char *)"   #t##    ",
           (const char *)"   #  #    ",
           (const char *)"   ......w ",
           (const char *)"   ww....w ",
           (const char *)" WWWWw..@. ",
           (const char *)"   ww.....^",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"     ^     ",
           (const char *)"     #     ",
           (const char *)"m`wwww     ",
           (const char *)"..`www     ",
           (const char *)"...``w     ",
           (const char *)"...........",
           (const char *)"..........^",
           (const char *)"     ......",
           (const char *)" Ww....... ",
           (const char *)" ww.@...ww ",
           (const char *)" .....wWWW ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"     ^     ",
           (const char *)"   w`...   ",
           (const char *)"   ``...   ",
           (const char *)"   `....   ",
           (const char *)"   .....   ",
           (const char *)"^......... ",
           (const char *)"  ........ ",
           (const char *)"  .........",
           (const char *)"   `..@...^",
           (const char *)"   ........",
           (const char *)"      .^...",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"     ^     ",
           (const char *)".....#.....",
           (const char *)".    #    s",
           (const char *)". ww..wWs..",
           (const char *)". w...ww ..",
           (const char *)". w....w ..",
           (const char *)". ww.@.w ..",
           (const char *)". Www..w .$",
           (const char *)".     .   s",
           (const char *)"........L..",
           (const char *)"    ...LLL ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"     ^     ",
           (const char *)"     #     ",
           (const char *)".``  #     ",
           (const char *)"..`  ..www ",
           (const char *)"...  ....w ",
           (const char *)"..w  w....^",
           (const char *)"..w  ww... ",
           (const char *)"..w  Www.. ",
           (const char *)"... .......",
           (const char *)"..@........",
           (const char *)"...........",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"  ^        ",
           (const char *)"  #      ..",
           (const char *)"  #      ..",
           (const char *)"  #####  ..",
           (const char *)"  #   #  ..",
           (const char *)" wwww #  ..",
           (const char *)"wwwww #  ..",
           (const char *)"  www......",
           (const char *)"     ..@...",
           (const char *)"^WWWWw....w",
           (const char *)"     wwwwww",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"     ^     ",
           (const char *)"     #     ",
           (const char *)" .wwww     ",
           (const char *)" ..wwww    ",
           (const char *)".....ww... ",
           (const char *)"......w... ",
           (const char *)"......ww...",
           (const char *)".. wwwww.@.",
           (const char *)"..   www...",
           (const char *)"..         ",
           (const char *)"^          ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"     ^     ",
           (const char *)"  wwwwww   ",
           (const char *)"  www...   ",
           (const char *)"  www...   ",
           (const char *)"   w....   ",
           (const char *)"..  ....   ",
           (const char *)"...  .     ",
           (const char *)".... ....  ",
           (const char *)".... ..... ",
           (const char *)"..@....... ",
           (const char *)"....     ^ ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"     ^     ",
           (const char *)"     #     ",
           (const char *)" ww  #     ",
           (const char *)" www..wW   ",
           (const char *)" ww...ww   ",
           (const char *)"  w....w   ",
           (const char *)"  ww.@..ww ",
           (const char *)" WWww..www ",
           (const char *)"  Wwww ww  ",
           (const char *)"           ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"     ^     ",
           (const char *)"     #     ",
           (const char *)"     #     ",
           (const char *)"``.....www ",
           (const char *)"`........w ",
           (const char *)"`....w.@.. ",
           (const char *)"...wwww... ",
           (const char *)"..wWWWww.. ",
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"  ^        ",
           (const char *)"  #        ",
           (const char *)"  #        ",
           (const char *)"  #####    ",
           (const char *)"      #    ",
           (const char *)"..``  #    ",
           (const char *)"...`  #   w",
           (const char *)"....  ...ww",
           (const char *)"..........w",
           (const char *)".@........w",
           (const char *)"......wwwww",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"     ^     ",
           (const char *)"     #     ",
           (const char *)" .wwww     ",
           (const char *)" ..wwww    ",
           (const char *)" ....www .$",
           (const char *)" .....wbs.$",
           (const char *)" .....ww .$",
           (const char *)" w.wwwww   ",
           (const char *)" ....www   ",
           (const char *)" .@.. w    ",
           (const char *)" ....      ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"     ^     ",
           (const char *)"  wwwwwww  ",
           (const char *)"  www.www^ ",
           (const char *)"  www.w.   ",
           (const char *)"   ww..    ",
           (const char *)"  ........ ",
           (const char *)"  ........ ",
           (const char *)"         . ",
           (const char *)" ....... . ",
           (const char *)"^. ..@.. . ",
           (const char *)"   ....... ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"     ^     ",
           (const char *)" ww  #     ",
           (const char *)" www..wW   ",
           (const char *)" ww...ww   ",
           (const char *)"  w....w   ",
           (const char *)"  ww.@..ww ",
           (const char *)" WWww..www ",
           (const char *)"  Wwww ww  ",
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"     ^     ",
           (const char *)"     #     ",
           (const char *)"``.....www ",
           (const char *)"`........w ",
           (const char *)"`....w.@.. ",
           (const char *)" ..wwww..  ",
           (const char *)"  wWWWww   ",
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"  ^        ",
           (const char *)"  #        ",
           (const char *)"  #####    ",
           (const char *)"      #    ",
           (const char *)"..`$  #    ",
           (const char *)"...`  #   w",
           (const char *)" s    ...ww",
           (const char *)"..........w",
           (const char *)".@.......ww",
           (const char *)"......wwwww",
           (const char *)" ..wwwwwWWW",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"     ^     ",
           (const char *)" .wwww     ",
           (const char *)" ..wwww    ",
           (const char *)" ....www ..",
           (const char *)" .....wWs.m",
           (const char *)" .....ww ..",
           (const char *)" wbwwwww  s",
           (const char *)"  s  www ..",
           (const char *)"..... w  .$",
           (const char *)"..@..   ...",
           (const char *)".....sb....",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"     ^     ",
           (const char *)"  www.www^ ",
           (const char *)"  www.w..  ",
           (const char *)"  .ww....  ",
           (const char *)"  ..... .  ",
           (const char *)"  .......  ",
           (const char *)"    .      ",
           (const char *)".......... ",
           (const char *)"^....@...w ",
           (const char *)"  .....www ",
           (const char *)"   ..wwwwW ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"     ^     ",
           (const char *)"...  #     ",
           (const char *)"...........",
           (const char *)"...........",
           (const char *)"........  .",
           (const char *)".....@.....",
           (const char *)"...........",
           (const char *)"  D    D   ",
           (const char *)"..t.  .t.. ",
           (const char *)"....  .... ",
           (const char *)"..m.  ..$. ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"     ^     ",
           (const char *)" CCCC#CCCCC",
           (const char *)"CC........C",
           (const char *)"C.........C",
           (const char *)"C......@..C",
           (const char *)"C........CC",
           (const char *)"CC......CC ",
           (const char *)" CCCCCCCC  ",
           (const char *)"$.C....C...",
           (const char *)".tC.m..C...",
           (const char *)"..C....C.$.",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"  ^        ",
           (const char *)"  #        ",
           (const char *)"  #####    ",
           (const char *)"      #    ",
           (const char *)"..`$  #    ",
           (const char *)"...`  #   .",
           (const char *)" s    .....",
           (const char *)".......CCC.",
           (const char *)".@...CCCCC.",
           (const char *)".....CCCCC.",
           (const char *)" ......t.. ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"     ^     ",
           (const char *)" .....     ",
           (const char *)" .CCC..    ",
           (const char *)" .CCC... ..",
           (const char *)" .CCC...s.m",
           (const char *)" ....... ..",
           (const char *)" .b.....  s",
           (const char *)"  s  ... ..",
           (const char *)"..... .  .$",
           (const char *)"..@..   ...",
           (const char *)".....sb....",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"     ^     ",
           (const char *)"  .......^ ",
           (const char *)"  $CCCCC.  ",
           (const char *)"  tCCCCC.  ",
           (const char *)"  .CCCCC.  ",
           (const char *)"  .......  ",
           (const char *)"    .      ",
           (const char *)".......... ",
           (const char *)"^....@..C. ",
           (const char *)"  .....CC. ",
           (const char *)"   ....... ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"     ^     ",
           (const char *)"     #  ..$",
           (const char *)"     #  s  ",
           (const char *)".m. ....b  ",
           (const char *)"... .....  ",
           (const char *)"...C.....C ",
           (const char *)"CCCCCCtCCC ",
           (const char *)"C.......CC ",
           (const char *)"C...... CC ",
           (const char *)"C.@...``C. ",
           (const char *)"C.....``C. ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"     ^     ",
           (const char *)"     # m.. ",
           (const char *)"     #   s ",
           (const char *)"     ..... ",
           (const char *)"     ..LL. ",
           (const char *)".... ...L. ",
           (const char *)".... ..... ",
           (const char *)"C.C  .     ",
           (const char *)"C``@`````  ",
           (const char *)"CCCCCCCC   ",
           (const char *)" C........$",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"  ^        ",
           (const char *)" C#C       ",
           (const char *)" C#CCCCC   ",
           (const char *)" C#####C   ",
           (const char *)" CCCCC#C.. ",
           (const char *)" CCCCCtC.. ",
           (const char *)" CCCCC#C.. ",
           (const char *)" CCCCC.... ",
           (const char *)" CCCC......",
           (const char *)" .......@..",
           (const char *)" ..........",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"     ^     ",
           (const char *)"     #     ",
           (const char *)" ..... ....",
           (const char *)" .....C....",
           (const char *)" ..... .m..",
           (const char *)"     .     ",
           (const char *)"ww. ...www ",
           (const char *)"ww......ww ",
           (const char *)"w........w ",
           (const char *)"CCC.@..... ",
           (const char *)"  C.....CC ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"     ^  .  ",
           (const char *)"^.......   ",
           (const char *)"  .......  ",
           (const char *)"  .m... .. ",
           (const char *)" .. .....  ",
           (const char *)" ......... ",
           (const char *)"      .    ",
           (const char *)"  .......ww",
           (const char *)"  .@.....wW",
           (const char *)" .......wwW",
           (const char *)" ......ww  ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"     ^     ",
           (const char *)"     #  .. ",
           (const char *)"     #  .. ",
           (const char *)"m.C.....CC ",
           (const char *)"..C....... ",
           (const char *)"..C....... ",
           (const char *)"..C..@.... ",
           (const char *)".CCCC. CCC ",
           (const char *)".C.... C.. ",
           (const char *)".C.... C.. ",
           (const char *)".......C.$ ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"     ^     ",
           (const char *)"     #     ",
           (const char *)"     #     ",
           (const char *)"m    ..... ",
           (const char *)"...C ..... ",
           (const char *)"...C...@.. ",
           (const char *)"...C ..... ",
           (const char *)"...C .....^",
           (const char *)"  .  CCCCC ",
           (const char *)"  . $CC... ",
           (const char *)"  ........ ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"  ^        ",
           (const char *)"  #        ",
           (const char *)"  #  CCC   ",
           (const char *)"  #####C   ",
           (const char *)"     C#C   ",
           (const char *)"      #    ",
           (const char *)" .... # .. ",
           (const char *)" ....C.... ",
           (const char *)" ..CC..... ",
           (const char *)" .CC....@.^",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"     ^     ",
           (const char *)"     #     ",
           (const char *)" .....     ",
           (const char *)" ..........",
           (const char *)" ........@.",
           (const char *)" ..........",
           (const char *)" ...... CC ",
           (const char *)"   CCCC .. ",
           (const char *)"   C... .. ",
           (const char *)"   C... .. ",
           (const char *)"   C......^",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"     ^  .  ",
           (const char *)" m......   ",
           (const char *)"  `......  ",
           (const char *)"  ``...... ",
           (const char *)" `.  ..... ",
           (const char *)" `.`  CCC. ",
           (const char *)"   .` C....",
           (const char *)"   $  C....",
           (const char *)"      C..@.",
           (const char *)"       ....",
           (const char *)"       ^   ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"     ^     ",
           (const char *)"     #     ",
           (const char *)"     #     ",
           (const char *)"   .....   ",
           (const char *)"   .CCC..  ",
           (const char *)"   ......  ",
           (const char *)"   ......  ",
           (const char *)"    .      ",
           (const char *)"   ......  ",
           (const char *)"   ..@..w  ",
           (const char *)"   ....ww  ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"     ^     ",
           (const char *)"     #     ",
           (const char *)"     #     ",
           (const char *)"     .....^",
           (const char *)"    ...... ",
           (const char *)"    `..@.. ",
           (const char *)"    `..... ",
           (const char *)"|M..s`.... ",
           (const char *)".$$.   ... ",
           (const char *)"|..|       ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"  ^        ",
           (const char *)"  #        ",
           (const char *)"  #  CCCCC.",
           (const char *)"  #####CCC$",
           (const char *)"    CC#CCC.",
           (const char *)" .$ CC#    ",
           (const char *)" ``   #    ",
           (const char *)" `.   .... ",
           (const char *)" ..CCC.... ",
           (const char *)" ..C....@.^",
           (const char *)" ......... ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"     ^     ",
           (const char *)"     #     ",
           (const char *)"   `..C... ",
           (const char *)"  ``..C... ",
           (const char *)" .....C..$ ",
           (const char *)" .@...CC.. ",
           (const char *)" .....CCC. ",
           (const char *)" CCCCCCCC. ",
           (const char *)" ....CC.C.^",
           (const char *)" .m......  ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"     ^     ",
           (const char *)"   `....   ",
           (const char *)"   ..@..   ",
           (const char *)"  C.....   ",
           (const char *)" CCC       ",
           (const char *)"  C        ",
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"     ^     ",
           (const char *)"     #     ",
           (const char *)"     #     ",
           (const char *)"   C....   ",
           (const char *)"   .....   ",
           (const char *)"... ....   ",
           (const char *)"...  ...   ",
           (const char *)"...   .C.. ",
           (const char *)".@.....C.. ",
           (const char *)"......     ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"     ^     ",
           (const char *)"..$  #     ",
           (const char *)".m.  # CCCC",
           (const char *)"...  ...CCC",
           (const char *)" C    . CCC",
           (const char *)" .    .   $",
           (const char *)" .    .   .",
           (const char *)" .  ..... .",
           (const char *)" .....@.. .",
           (const char *)"    .....s.",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"  ^        ",
           (const char *)"  #   $... ",
           (const char *)"  #      C ",
           (const char *)"  #####  C ",
           (const char *)"      #  C ",
           (const char *)"$..   #  . ",
           (const char *)"  .   #  . ",
           (const char *)".........C ",
           (const char *)".......... ",
           (const char *)"........@. ",
           (const char *)" .....C    ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"     ^     ",
           (const char *)"     #     ",
           (const char *)".C....     ",
           (const char *)"......     ",
           (const char *)".....C     ",
           (const char *)".....C     ",
           (const char *)"CCCtCC     ",
           (const char *)"....C..    ",
           (const char *)"....C...   ",
           (const char *)".@..C...   ",
           (const char *)"....C..    ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"     ^     ",
           (const char *)"^.C....CC.$",
           (const char *)" .C....CC..",
           (const char *)" .C....CC C",
           (const char *)" CCCtCCCC C",
           (const char *)"CCCC....C .",
           (const char *)".......CC .",
           (const char *)"...........",
           (const char *)"....@......",
           (const char *)".......    ",
           (const char *)"     ^     ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"     ^     ",
           (const char *)"     #     ",
           (const char *)"   CC#CC   ",
           (const char *)"   C...C   ",
           (const char *)"    .L.    ",
           (const char *)"    .L.    ",
           (const char *)"    .L.    ",
           (const char *)"    .L.    ",
           (const char *)"    ...    ",
           (const char *)"   |.@.|   ",
           (const char *)"    ...    ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"     ^     ",
           (const char *)"     #     ",
           (const char *)"     #     ",
           (const char *)" LLLL....  ",
           (const char *)" LLL...... ",
           (const char *)" LL....... ",
           (const char *)" LL..@.... ",
           (const char *)"  L.......^",
           (const char *)"    L..    ",
           (const char *)"    LL.    ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"  ^        ",
           (const char *)"  #     #  ",
           (const char *)"  #     #  ",
           (const char *)"  #######  ",
           (const char *)"     C#C   ",
           (const char *)"     C#C   ",
           (const char *)"     C#C   ",
           (const char *)"   .......^",
           (const char *)"  ........ ",
           (const char *)"  .@....LL ",
           (const char *)"   ...LLLL ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"     ^     ",
           (const char *)"     #     ",
           (const char *)"    ..     ",
           (const char *)"   ...     ",
           (const char *)" .........^",
           (const char *)" ........  ",
           (const char *)" .......   ",
           (const char *)" .......   ",
           (const char *)" L...@..   ",
           (const char *)" LL.....   ",
           (const char *)"      ^    ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"     ^     ",
           (const char *)"     #     ",
           (const char *)"     #     ",
           (const char *)"    ....   ",
           (const char *)"   .....   ",
           (const char *)"   ....    ",
           (const char *)".......... ",
           (const char *)".....@.... ",
           (const char *)"..........^",
           (const char *)"  .....    ",
           (const char *)"    ^      ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"     ^     ",
           (const char *)"     #     ",
           (const char *)"     #     ",
           (const char *)"   .....   ",
           (const char *)"   tBtBt   ",
           (const char *)"   ......  ",
           (const char *)"   ......  ",
           (const char *)"   ....... ",
           (const char *)"   .......^",
           (const char *)"   ..@.... ",
           (const char *)"   .....   ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"     ^     ",
           (const char *)"     #     ",
           (const char *)"     #     ",
           (const char *)" ......... ",
           (const char *)" .......B. ",
           (const char *)" ......... ",
           (const char *)" ....@.... ",
           (const char *)" .........^",
           (const char *)"   .....   ",
           (const char *)"   .....   ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"  ^        ",
           (const char *)"  #     #  ",
           (const char *)"  #     #  ",
           (const char *)"  #######  ",
           (const char *)"      #    ",
           (const char *)"      #    ",
           (const char *)"  ..  #    ",
           (const char *)" ......... ",
           (const char *)".........B ",
           (const char *)"...@...... ",
           (const char *)" .........^",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"     ^     ",
           (const char *)"     #     ",
           (const char *)" .....     ",
           (const char *)" .B...     ",
           (const char *)" ......... ",
           (const char *)" .@....... ",
           (const char *)" ......... ",
           (const char *)"    .....  ",
           (const char *)"    .....  ",
           (const char *)"    .....  ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"     ^     ",
           (const char *)"     #     ",
           (const char *)"     #     ",
           (const char *)" ..........",
           (const char *)" ....@.....",
           (const char *)" ..........",
           (const char *)" ......    ",
           (const char *)" ......    ",
           (const char *)"   .ww.    ",
           (const char *)"   .ww.    ",
           (const char *)"   ....^   ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"     ^     ",
           (const char *)"     #     ",
           (const char *)"     #     ",
           (const char *)"   .BtB.   ",
           (const char *)"   .....   ",
           (const char *)"  .......  ",
           (const char *)" B...@...B ",
           (const char *)"   .....   ",
           (const char *)"  B.....B  ",
           (const char *)"   .....   ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"     ^     ",
           (const char *)"     #     ",
           (const char *)"     #     ",
           (const char *)"    B.B..  ",
           (const char *)"   ....... ",
           (const char *)"    ...@.. ",
           (const char *)"   ....... ",
           (const char *)"    ...... ",
           (const char *)"      . .  ",
           (const char *)"           ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"  ^        ",
           (const char *)"  #        ",
           (const char *)"  #        ",
           (const char *)"  #####    ",
           (const char *)"      #    ",
           (const char *)"      #    ",
           (const char *)"      #    ",
           (const char *)" ....B.B.. ",
           (const char *)" .........^",
           (const char *)" .......@. ",
           (const char *)"       ... ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"     ^     ",
           (const char *)"     #     ",
           (const char *)" ...B.     ",
           (const char *)" .....B    ",
           (const char *)" .......   ",
           (const char *)" .@......  ",
           (const char *)" ......... ",
           (const char *)"   ....... ",
           (const char *)"   ....... ",
           (const char *)"   .......^",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"     ^     ",
           (const char *)"   C...C   ",
           (const char *)"   CB.BC   ",
           (const char *)"   C...C   ",
           (const char *)"   CB.BC   ",
           (const char *)"   C...C   ",
           (const char *)"   CB.BC   ",
           (const char *)"  .......^ ",
           (const char *)"  .......  ",
           (const char *)"^......@.. ",
           (const char *)" ......... ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"     ^     ",
           (const char *)" ...B..... ",
           (const char *)" .@...wwWw ",
           (const char *)" ......www ",
           (const char *)"^.........^",
           (const char *)" ......... ",
           (const char *)" ......... ",
           (const char *)"   ...=... ",
           (const char *)"   CCC=CCC ",
           (const char *)"   CCC=CCC ",
           (const char *)"     ^     ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"     ^     ",
           (const char *)"     #     ",
           (const char *)"   $....   ",
           (const char *)"   .....   ",
           (const char *)"^..........",
           (const char *)" CC...f.   ",
           (const char *)"CC......CCC",
           (const char *)"CC......CCC",
           (const char *)"CC...@..CC.",
           (const char *)"CCCC....CC.",
           (const char *)"CCCCC..CCC$",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"    B.B    ",
           (const char *)"    .@.    ",
           (const char *)"   .....   ",
           (const char *)"   .....   ",
           (const char *)"^##.C.C.##^",
           (const char *)"   .CCC.   ",
           (const char *)"   .....   ",
           (const char *)"   s       ",
           (const char *)"   `   m$  ",
           (const char *)"   .....   ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"..   ^     ",
           (const char *)".... # ..  ",
           (const char *)".........  ",
           (const char *)"  .......  ",
           (const char *)" .....CCC  ",
           (const char *)"  ....C..  ",
           (const char *)"   ...C..  ",
           (const char *)" $s...C..^ ",
           (const char *)"   ...CCC  ",
           (const char *)" ...@..... ",
           (const char *)" ^ ....... ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"     ^     ",
           (const char *)" .......CC ",
           (const char *)" ........C ",
           (const char *)" ........C ",
           (const char *)" .B...B... ",
           (const char *)"^...@..... ",
           (const char *)" .B...B. .^",
           (const char *)" .....     ",
           (const char *)" C.C..s..$ ",
           (const char *)" CCC.. ..$ ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"     ^     ",
           (const char *)"    ...    ",
           (const char *)"    .@.... ",
           (const char *)" ......... ",
           (const char *)"^....C=C..^",
           (const char *)" ....C=C.. ",
           (const char *)"   ..C=C.. ",
           (const char *)"   ..C.C.. ",
           (const char *)"   C. . .$ ",
           (const char *)"   C. .    ",
           (const char *)"    ^      ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"      ^    ",
           (const char *)"     C.C   ",
           (const char *)"  CCCC.C   ",
           (const char *)" CC....CCC ",
           (const char *)"^....@....^",
           (const char *)" CC...CCCC ",
           (const char *)"   C....C  ",
           (const char *)"      C.C  ",
           (const char *)"      C.C  ",
           (const char *)"      C.C  ",
           (const char *)"       ^   ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"     CC.C  ",
           (const char *)"  CC....CC ",
           (const char *)"  C......C ",
           (const char *)"^#...@....^",
           (const char *)"  C......C ",
           (const char *)"  CC....CC ",
           (const char *)"  ...C.C   ",
           (const char *)"  ...C.C   ",
           (const char *)"    .C.C   ",
           (const char *)"      ^    ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"     ^     ",
           (const char *)"    C.C    ",
           (const char *)"    C.C   .",
           (const char *)"  .........",
           (const char *)" ..b...@...",
           (const char *)"    .......",
           (const char *)"    C..... ",
           (const char *)"       C.C ",
           (const char *)"       C.C ",
           (const char *)"       C.C ",
           (const char *)"        ^  ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"     ^     ",
           (const char *)"    C.....^",
           (const char *)"    C.C    ",
           (const char *)"  $...C    ",
           (const char *)"  ..CCC    ",
           (const char *)"^#..CCC    ",
           (const char *)"  CCC.C    ",
           (const char *)"...........",
           (const char *)"......@....",
           (const char *)"...........",
           (const char *)"         ^ ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"     ^     ",
           (const char *)" ....#.... ",
           (const char *)" ....#.... ",
           (const char *)" ......... ",
           (const char *)"^.........^",
           (const char *)" .k.@..... ",
           (const char *)" ........  ",
           (const char *)".........  ",
           (const char *)".........  ",
           (const char *)"..b......  ",
           (const char *)"     ^     ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"     ^     ",
           (const char *)"     #     ",
           (const char *)"   $....   ",
           (const char *)"   .....   ",
           (const char *)"^..........",
           (const char *)"   ...f.   ",
           (const char *)"  ...... $$",
           (const char *)"  ...... CC",
           (const char *)"  ...... ..",
           (const char *)"  ...@.. ..",
           (const char *)"   .....sm.",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"  .......  ",
           (const char *)"   .....   ",
           (const char *)"   .....   ",
           (const char *)"^##..@..## ",
           (const char *)"   .....   ",
           (const char *)"   .....   ",
           (const char *)"   s       ",
           (const char *)"   `   m$  ",
           (const char *)"   ``...   ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"     ^     ",
           (const char *)" ... # ..  ",
           (const char *)"  .......  ",
           (const char *)"  .......  ",
           (const char *)" ..... D   ",
           (const char *)" .@... .!  ",
           (const char *)"...... ..  ",
           (const char *)"   ...s.$  ",
           (const char *)"   ...     ",
           (const char *)" ........  ",
           (const char *)"     ...   ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)" ....#..ww ",
           (const char *)" ....#...w ",
           (const char *)" ........w ",
           (const char *)" ....B.... ",
           (const char *)"^...@..... ",
           (const char *)" ..B.... . ",
           (const char *)" ......    ",
           (const char *)" w.w.. ..$ ",
           (const char *)" Www..s..m ",
           (const char *)"       ^   ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"     ^     ",
           (const char *)" ......... ",
           (const char *)" ......... ",
           (const char *)" .$....... ",
           (const char *)"^...CCCCCC^",
           (const char *)" ...====== ",
           (const char *)" ...CCCCCC ",
           (const char *)" ......b   ",
           (const char *)" .@.....D..",
           (const char *)" ......  .$",
           (const char *)"     ^     ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"     ^     ",
           (const char *)"     #     ",
           (const char *)"   .....   ",
           (const char *)"   .....   ",
           (const char *)"^##......#^",
           (const char *)"   ...f.   ",
           (const char *)"  ...... . ",
           (const char *)"  ...... . ",
           (const char *)"  ...... . ",
           (const char *)"    .@.. . ",
           (const char *)" ........m ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"  ..   ..  ",
           (const char *)"  .......  ",
           (const char *)"   .L.L.   ",
           (const char *)"^##..@..##^",
           (const char *)"   .L.L.   ",
           (const char *)"   .....   ",
           (const char *)"   s       ",
           (const char *)"   . ..m$  ",
           (const char *)"   ......  ",
           (const char *)"   .....$  ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)" ... ^     ",
           (const char *)" ... . ..  ",
           (const char *)"  .......  ",
           (const char *)"  b..@...  ",
           (const char *)" ......    ",
           (const char *)" ..... .m. ",
           (const char *)"   ...s... ",
           (const char *)"..s... ..$ ",
           (const char *)".  ...   s ",
           (const char *)".    s   . ",
           (const char *)"$...s..... ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"      ^    ",
           (const char *)" .......ww ",
           (const char *)" ........w ",
           (const char *)" .......bw ",
           (const char *)" ......... ",
           (const char *)"^..C@C.... ",
           (const char *)" ....... . ",
           (const char *)" ......    ",
           (const char *)" w.w...s.. ",
           (const char *)" Www..  .$ ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"      ^    ",
           (const char *)"     C=C.. ",
           (const char *)"    .C=C.. ",
           (const char *)"   ..C=C.. ",
           (const char *)"^.........^",
           (const char *)"   .....@. ",
           (const char *)"  ........ ",
           (const char *)"  ....  D  ",
           (const char *)" ..... LLL ",
           (const char *)" .. .. m.$ ",
           (const char *)"     ^     ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"       ^   ",
           (const char *)"     . ..  ",
           (const char *)" $....b..  ",
           (const char *)"  ......   ",
           (const char *)" ....@....^",
           (const char *)" .......   ",
           (const char *)" ........  ",
           (const char *)"  ...  ..  ",
           (const char *)"  ..$   #  ",
           (const char *)"        #  ",
           (const char *)"        ^  ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"       ^   ",
           (const char *)" ....  #.. ",
           (const char *)" ......... ",
           (const char *)" ...L.L... ",
           (const char *)"^...L@L... ",
           (const char *)" ...LLL... ",
           (const char *)" .........^",
           (const char *)" ...b..... ",
           (const char *)" ...... .$ ",
           (const char *)" ...... .. ",
           (const char *)"      ^    ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"     ^     ",
           (const char *)"   .... .. ",
           (const char *)"  .b...... ",
           (const char *)" .........^",
           (const char *)" ......... ",
           (const char *)" .@......  ",
           (const char *)" .....  .  ",
           (const char *)"  ....  .  ",
           (const char *)"     s  .  ",
           (const char *)"  $m..  ^  ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"^...D...w  ",
           (const char *)"     ..@ww ",
           (const char *)" . ......w ",
           (const char *)" . ....... ",
           (const char *)" ..CC.C..  ",
           (const char *)" ...C.C..  ",
           (const char *)" ...C.CCC.^",
           (const char *)" w.......w ",
           (const char *)" www|.|www ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"     ^     ",
           (const char *)"    ...m.. ",
           (const char *)"    ...... ",
           (const char *)"   .. . .. ",
           (const char *)"^#........^",
           (const char *)"   ...b... ",
           (const char *)"  LL...... ",
           (const char *)"  fLL......",
           (const char *)"  ..L....@.",
           (const char *)"   . .LL...",
           (const char *)"     ^     ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"     ^     ",
           (const char *)"     #     ",
           (const char *)"   B....   ",
           (const char *)"   .... ..^",
           (const char *)" ....@.D.$ ",
           (const char *)"  w.... .. ",
           (const char *)"  ww....   ",
           (const char *)"    w....  ",
           (const char *)"     $  #  ",
           (const char *)"        ^  ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"  ww   #   ",
           (const char *)"  ww...#   ",
           (const char *)"   wwww.   ",
           (const char *)"^...w@w..  ",
           (const char *)"   .wwww.  ",
           (const char *)"  w...www  ",
           (const char *)"   ww..    ",
           (const char *)"      .    ",
           (const char *)"      .    ",
           (const char *)"      ^    ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"     ^     ",
           (const char *)"     #     ",
           (const char *)"  g....... ",
           (const char *)"  .... ...^",
           (const char *)" .... . .. ",
           (const char *)" .@. ... . ",
           (const char *)" ......... ",
           (const char *)" s  ...... ",
           (const char *)" .   ..... ",
           (const char *)" ...!   .  ",
           (const char *)" ..m!   ^  ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"     ^     ",
           (const char *)" .$ .#..CC ",
           (const char *)" . .....CC ",
           (const char *)" .....wB.C ",
           (const char *)" ...wWWw.. ",
           (const char *)"^..wW@WWw  ",
           (const char *)" ...wWWWw.^",
           (const char *)" ...ww.... ",
           (const char *)" w.......w ",
           (const char *)" Ww....www ",
           (const char *)" WWww..w   ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"     ^  ...",
           (const char *)"    w.. .@.",
           (const char *)"    w.. ...",
           (const char *)"    ... .. ",
           (const char *)"^.....b ..^",
           (const char *)"   ....  . ",
           (const char *)"   ww..... ",
           (const char *)"    ww.... ",
           (const char *)"    Ww.... ",
           (const char *)"   W ..w   ",
           (const char *)"     ^     ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"     ^     ",
           (const char *)"     #     ",
           (const char *)"    ...... ",
           (const char *)"   ...B... ",
           (const char *)" ....@....^",
           (const char *)"   ...B... ",
           (const char *)"    ...... ",
           (const char *)"    www..w ",
           (const char *)"    wWwW.w ",
           (const char *)"        ^  ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"       ^   ",
           (const char *)" ...   #.  ",
           (const char *)"  .......  ",
           (const char *)"   .B.B..  ",
           (const char *)" ....@....^",
           (const char *)"   .B....  ",
           (const char *)" ........  ",
           (const char *)"  .....    ",
           (const char *)"      .    ",
           (const char *)"      .    ",
           (const char *)"      ^    ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"     ^     ",
           (const char *)"     #     ",
           (const char *)"  g....... ",
           (const char *)"  .....  . ",
           (const char *)" ......... ",
           (const char *)" ....... . ",
           (const char *)" .@....... ",
           (const char *)" ......  . ",
           (const char *)"   ....... ",
           (const char *)"        .  ",
           (const char *)"        ^  ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"     ^     ",
           (const char *)" .$ .....w ",
           (const char *)" .     .ww ",
           (const char *)" .....w..w ",
           (const char *)" ...wwWw.. ",
           (const char *)"^..wWWWWw  ",
           (const char *)" .wWW@WWw.^",
           (const char *)" ..wwwww.. ",
           (const char *)" w......w. ",
           (const char *)" www...www ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"     ^     ",
           (const char *)"     .     ",
           (const char *)"    B.B    ",
           (const char *)"     .     ",
           (const char *)"^##.......^",
           (const char *)"   .m..... ",
           (const char *)"   ....... ",
           (const char *)"   ...@... ",
           (const char *)"   B.....$ ",
           (const char *)"     .     ",
           (const char *)"     ^     ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"      ^    ",
           (const char *)"      #    ",
           (const char *)"      #    ",
           (const char *)"   ....... ",
           (const char *)" ##..@....^",
           (const char *)"   ....... ",
           (const char *)"   B...... ",
           (const char *)"       #   ",
           (const char *)"       #   ",
           (const char *)"       m   ",
           (const char *)"       ^   ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"       ^   ",
           (const char *)"      .#.  ",
           (const char *)"    .....  ",
           (const char *)"  B....bb. ",
           (const char *)" ###.@.bm.^",
           (const char *)"  B....bb. ",
           (const char *)"     ....  ",
           (const char *)"     ...   ",
           (const char *)"      #    ",
           (const char *)"     B#B   ",
           (const char *)"      ^    ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"     ^     ",
           (const char *)"     #     ",
           (const char *)"     # ....",
           (const char *)"  .........",
           (const char *)" ###...@...",
           (const char *)"    .......",
           (const char *)"    B......",
           (const char *)"        #  ",
           (const char *)"       B#B ",
           (const char *)"        #  ",
           (const char *)"        ^  ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"     ^     ",
           (const char *)"    B#B wwW",
           (const char *)"     #   wW",
           (const char *)"  $...^  ww",
           (const char *)"  ..wwww  w",
           (const char *)"^..wW@www w",
           (const char *)"  wWWwwwwww",
           (const char *)"    s     w",
           (const char *)"   .....  w",
           (const char *)"   .....s.W",
           (const char *)"   $.m.$   ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"     ^     ",
           (const char *)"   . t .   ",
           (const char *)"  .. . ... ",
           (const char *)"^#.. . ...^",
           (const char *)"  .. . ... ",
           (const char *)" ..........",
           (const char *)" .....@....",
           (const char *)" ..........",
           (const char *)"  .........",
           (const char *)"    ......m",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"      ^    ",
           (const char *)"      #    ",
           (const char *)"      #    ",
           (const char *)"   .....   ",
           (const char *)" ....@....^",
           (const char *)"   ....... ",
           (const char *)" $ ....... ",
           (const char *)" . .....   ",
           (const char *)" .......   ",
           (const char *)"       #   ",
           (const char *)"       ^   ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"       ^   ",
           (const char *)"      B.B  ",
           (const char *)"    !....  ",
           (const char *)"  B......B ",
           (const char *)" ....@....^",
           (const char *)"  B......B ",
           (const char *)"   ..L.L.  ",
           (const char *)"   .LLLLL  ",
           (const char *)" $s....L.. ",
           (const char *)" m       . ",
           (const char *)" .......s. ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"     ^     ",
           (const char *)"     #     ",
           (const char *)"     #     ",
           (const char *)"  !....... ",
           (const char *)" ......@.. ",
           (const char *)"  ........ ",
           (const char *)"  ........ ",
           (const char *)"  $......  ",
           (const char *)"        #  ",
           (const char *)"        ^  ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)" !m  ^     ",
           (const char *)"  s  #     ",
           (const char *)" ..  ...$  ",
           (const char *)"  ....  .  ",
           (const char *)"  ..www..  ",
           (const char *)"^..wWWw... ",
           (const char *)"  wWWw.... ",
           (const char *)"   Ww.@... ",
           (const char *)"     ..... ",
           (const char *)"           ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"     ^     ",
           (const char *)"   .....   ",
           (const char *)"  ........ ",
           (const char *)"^.........^",
           (const char *)"  ........ ",
           (const char *)" ..........",
           (const char *)" .....@....",
           (const char *)" .b........",
           (const char *)"  bb.......",
           (const char *)"    ......m",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"      ^    ",
           (const char *)"      #    ",
           (const char *)"      #    ",
           (const char *)"   ...t.   ",
           (const char *)" ##..@...#^",
           (const char *)"   ....... ",
           (const char *)" $ ....... ",
           (const char *)" . .....   ",
           (const char *)" ```....   ",
           (const char *)"       #   ",
           (const char *)"       ^   ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"       ^   ",
           (const char *)"      B.B  ",
           (const char *)"    !..... ",
           (const char *)"  B....... ",
           (const char *)" ....@....^",
           (const char *)"  B....... ",
           (const char *)"   ..LLL.. ",
           (const char *)"   .LLL... ",
           (const char *)" $s....... ",
           (const char *)" m       . ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"     ^     ",
           (const char *)"     #     ",
           (const char *)"     #     ",
           (const char *)"  !..#...  ",
           (const char *)" ......@.  ",
           (const char *)"  .......  ",
           (const char *)"  .......  ",
           (const char *)"  $.b....  ",
           (const char *)"        .  ",
           (const char *)"        ^  ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)" !m  ^     ",
           (const char *)" s   #     ",
           (const char *)" ..  #..$  ",
           (const char *)"  ....  .  ",
           (const char *)"  ..wwW .  ",
           (const char *)"^..wWWw .  ",
           (const char *)"  wWWw. .  ",
           (const char *)"   Ww.....^",
           (const char *)"     ...   ",
           (const char *)"     .@.   ",
           (const char *)"     ...   ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"  ^        ",
           (const char *)" ......... ",
           (const char *)" ......... ",
           (const char *)" ......... ",
           (const char *)" ......... ",
           (const char *)" ......... ",
           (const char *)"   ....... ",
           (const char *)"   ...@... ",
           (const char *)"   B.....$ ",
           (const char *)"     #     ",
           (const char *)"     ^     ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"   ^       ",
           (const char *)" Wwww...ww ",
           (const char *)" www.....w ",
           (const char *)" w........ ",
           (const char *)"^....@....^",
           (const char *)" ........w ",
           (const char *)" ......www ",
           (const char *)" .....wwWW ",
           (const char *)"       .   ",
           (const char *)"       .   ",
           (const char *)"       ^   ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"       ^   ",
           (const char *)"  ....wwww ",
           (const char *)"  ......ww ",
           (const char *)" C........ ",
           (const char *)"^C...@....^",
           (const char *)" C........ ",
           (const char *)"  ........ ",
           (const char *)"  w.....ww ",
           (const char *)"  ww...ww  ",
           (const char *)"      m    ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"  ^        ",
           (const char *)" ......... ",
           (const char *)" ......... ",
           (const char *)" ......... ",
           (const char *)"^......@.. ",
           (const char *)" .........^",
           (const char *)" ......... ",
           (const char *)"    ...... ",
           (const char *)"    .....  ",
           (const char *)"        ^  ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"     ^     ",
           (const char *)" ..  #     ",
           (const char *)" .f  #     ",
           (const char *)" . ..t.....",
           (const char *)" s .ww.....",
           (const char *)"^..wWWw.. .",
           (const char *)"  wWWWw....",
           (const char *)"  WWWWw....",
           (const char *)"       ..@.",
           (const char *)"       ....",
           (const char *)"       ....",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"  ^        ",
           (const char *)" ......... ",
           (const char *)" ...CCCC.. ",
           (const char *)" ...CCCC.. ",
           (const char *)" ....CC... ",
           (const char *)" ......... ",
           (const char *)"   ....... ",
           (const char *)"   ...@... ",
           (const char *)"   ....... ",
           (const char *)"     #     ",
           (const char *)"     ^     ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"   ^       ",
           (const char *)" ....wwwwW ",
           (const char *)" ......www ",
           (const char *)" ......... ",
           (const char *)"^....@....^",
           (const char *)" ......... ",
           (const char *)" www...... ",
           (const char *)" Wwwww.... ",
           (const char *)"       ... ",
           (const char *)"       ... ",
           (const char *)"       ^   ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"       ^   ",
           (const char *)" .LL..|.|. ",
           (const char *)" LLL...... ",
           (const char *)" LL......| ",
           (const char *)"^L...@....^",
           (const char *)" LL......| ",
           (const char *)" LLL...... ",
           (const char *)" LLLL....L ",
           (const char *)"  LLLL..LL ",
           (const char *)"      .    ",
           (const char *)"      ^    ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"     ^     ",
           (const char *)" ........w ",
           (const char *)" ......... ",
           (const char *)" .....B.B. ",
           (const char *)"^......@.. ",
           (const char *)" .......B.^",
           (const char *)" ......... ",
           (const char *)"    ...... ",
           (const char *)"    ...... ",
           (const char *)"       ..  ",
           (const char *)"        ^  ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"     ^     ",
           (const char *)"     #     ",
           (const char *)"    |t|... ",
           (const char *)"   ........",
           (const char *)"   .ww.....",
           (const char *)"^..wWWw....",
           (const char *)"  wWWWw....",
           (const char *)"  WWWWw..@.",
           (const char *)"   WWWWw...",
           (const char *)"    WWWWw.w",
           (const char *)"      Wwwww",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"     ^     ",
           (const char *)"     m ... ",
           (const char *)"     # ... ",
           (const char *)" ^##......^",
           (const char *)"  .. .L. . ",
           (const char *)"  ...LLL.. ",
           (const char *)"  ..LLL. . ",
           (const char *)"  LLL....@ ",
           (const char *)"  LL..b... ",
           (const char *)"     ^     ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"      ^    ",
           (const char *)"      #    ",
           (const char *)"  ....#..  ",
           (const char *)"  ........ ",
           (const char *)" ....@....^",
           (const char *)"  ........ ",
           (const char *)"  ........ ",
           (const char *)"   ....... ",
           (const char *)"   ....m   ",
           (const char *)"       ^   ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"       ^   ",
           (const char *)"   LL..... ",
           (const char *)"  LL...... ",
           (const char *)"  L....... ",
           (const char *)"^....@....^",
           (const char *)"  ........ ",
           (const char *)"  ........ ",
           (const char *)"  ........ ",
           (const char *)"   ....... ",
           (const char *)"      .    ",
           (const char *)"      ^    ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"     ^     ",
           (const char *)"     # ... ",
           (const char *)"     # ... ",
           (const char *)"  ...#..@..",
           (const char *)" ..........",
           (const char *)"  .........",
           (const char *)"  ........ ",
           (const char *)"  ........ ",
           (const char *)"  ..m...#  ",
           (const char *)"        ^  ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"     ^     ",
           (const char *)"     #     ",
           (const char *)"     #     ",
           (const char *)" WwwwwwwwW ",
           (const char *)" ww.....ww ",
           (const char *)"^w...@...w ",
           (const char *)" w.......w ",
           (const char *)" w.....www ",
           (const char *)" ww...wwwW ",
           (const char *)" Ww....wWW ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"     ^     ",
           (const char *)"     .     ",
           (const char *)" CCC...CCC ",
           (const char *)" CC....CCC ",
           (const char *)" CC.....CC ",
           (const char *)"  C.b.b.C  ",
           (const char *)"  C.....C  ",
           (const char *)"  C..@..C  ",
           (const char *)"    ...    ",
           (const char *)"^C........^",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"      ^    ",
           (const char *)" CCCCC.CCC ",
           (const char *)" C......CC ",
           (const char *)" C.......C ",
           (const char *)"^..b.@...C^",
           (const char *)" C.......C ",
           (const char *)" CC......C ",
           (const char *)" CCCCCC.CC ",
           (const char *)" CCCCC.... ",
           (const char *)"       ^   ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"  ^        ",
           (const char *)"  .        ",
           (const char *)" C........ ",
           (const char *)" CCCCCCCC. ",
           (const char *)"^.........^",
           (const char *)" C.CCCCCC. ",
           (const char *)" C.CCC.CC@ ",
           (const char *)" CCCC .    ",
           (const char *)"  CC  .... ",
           (const char *)"  $   . .. ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"     ^     ",
           (const char *)"     . ... ",
           (const char *)"  ........ ",
           (const char *)"  ......@. ",
           (const char *)"^..C..CC.. ",
           (const char *)" ..C...C...",
           (const char *)" ..CC......",
           (const char *)" ..CCCCC...",
           (const char *)" ..........",
           (const char *)"  .........",
           (const char *)"         ^ ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"     ^     ",
           (const char *)"     .     ",
           (const char *)"     .     ",
           (const char *)"    wwwwwW ",
           (const char *)"   .....ww ",
           (const char *)"^....@...w ",
           (const char *)" w.......w ",
           (const char *)" w.....www ",
           (const char *)" ww...wwwW ",
           (const char *)" WwwwwwwW  ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"     ^     ",
           (const char *)"     .     ",
           (const char *)" www...www ",
           (const char *)" ww....www ",
           (const char *)" ww.....ww ",
           (const char *)"  w.b.b.w  ",
           (const char *)"  w.....w  ",
           (const char *)"  w..@..w  ",
           (const char *)"    ...    ",
           (const char *)"^w........^",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"      ^    ",
           (const char *)" wwwww.www ",
           (const char *)" w......ww ",
           (const char *)" w.......w ",
           (const char *)"^..b.@...w^",
           (const char *)" w.......w ",
           (const char *)" ww......w ",
           (const char *)" Wwwwww.ww ",
           (const char *)" WWwww.... ",
           (const char *)"       ^   ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"  ^        ",
           (const char *)"  .        ",
           (const char *)" w........ ",
           (const char *)" wwwwwwww. ",
           (const char *)"^.........^",
           (const char *)" w.wwwwww..",
           (const char *)" w.www.ww@.",
           (const char *)" wwww .....",
           (const char *)"  ww  .... ",
           (const char *)"  $   . .. ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"     ^     ",
           (const char *)"     .     ",
           (const char *)"  ........ ",
           (const char *)"  ......@. ",
           (const char *)"^..w..ww.. ",
           (const char *)" ..w...w...",
           (const char *)" ..ww......",
           (const char *)" ..wwwww...",
           (const char *)" ..........",
           (const char *)"  .........",
           (const char *)"         ^ ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"     ^     ",
           (const char *)"     .     ",
           (const char *)"     .     ",
           (const char *)"    wwwwwW ",
           (const char *)"   .....ww ",
           (const char *)"^. ..@...w ",
           (const char *)" w ......w ",
           (const char *)" w  ...www ",
           (const char *)" W  ..wwwW ",
           (const char *)" WWwwwwwW  ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"  T        ",
           (const char *)"  .        ",
           (const char *)"  .  E     ",
           (const char *)"  . ...    ",
           (const char *)"  s..M..   ",
           (const char *)"  ......f  ",
           (const char *)" ......... ",
           (const char *)"    |.|    ",
           (const char *)"     .     ",
           (const char *)"     ^     ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"     E     ",
           (const char *)"    ...    ",
           (const char *)"   ..M..   ",
           (const char *)"  .......  ",
           (const char *)" f........ ",
           (const char *)"    |.|    ",
           (const char *)"     .     ",
           (const char *)"     .....^",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"     E     ",
           (const char *)"    ...    ",
           (const char *)"   ..M..   ",
           (const char *)"  .......  ",
           (const char *)" ..f...... ",
           (const char *)"    |.|    ",
           (const char *)"     .     ",
           (const char *)"^.........^",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)" ..$       ",
           (const char *)" ...       ",
           (const char *)" T..       ",
           (const char *)"     E     ",
           (const char *)"    ...    ",
           (const char *)"   ..M.f   ",
           (const char *)"  .......  ",
           (const char *)" G.......G ",
           (const char *)"    |.|    ",
           (const char *)"    |.|    ",
           (const char *)"     ^     ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"     E     ",
           (const char *)"    ...    ",
           (const char *)"   G...G   ",
           (const char *)"  .......  ",
           (const char *)" ......... ",
           (const char *)"    .f.    ",
           (const char *)"    ...    ",
           (const char *)"     ^     ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"     f     ",
           (const char *)"     .     ",
           (const char *)"    ...    ",
           (const char *)"    .E.    ",
           (const char *)"   ..t..   ",
           (const char *)"   .....   ",
           (const char *)"  .......  ",
           (const char *)"  ..|.|..  ",
           (const char *)" ......... ",
           (const char *)" G..|.|... ",
           (const char *)"     ^     ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"     f     ",
           (const char *)"     .     ",
           (const char *)"    ...    ",
           (const char *)"    .E.    ",
           (const char *)"   .....   ",
           (const char *)"   .....   ",
           (const char *)"  .......  ",
           (const char *)"  ..|.|..  ",
           (const char *)" ......... ",
           (const char *)" ...|.|..G ",
           (const char *)"     ^     ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"     $     ",
           (const char *)"     s     ",
           (const char *)"    ...    ",
           (const char *)"    .E.    ",
           (const char *)"   .|.|.   ",
           (const char *)"   .....   ",
           (const char *)"  g.....g  ",
           (const char *)"  ..f....  ",
           (const char *)" G.. . ..G ",
           (const char *)" .........^",
           (const char *)"     ^     ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"     .s$   ",
           (const char *)"     .     ",
           (const char *)"    ...    ",
           (const char *)"    .E.    ",
           (const char *)"   .....   ",
           (const char *)"   .G.G.   ",
           (const char *)"  .......  ",
           (const char *)"  ..|.|..  ",
           (const char *)" ......... ",
           (const char *)" f..|.|...^",
           (const char *)"     ^     ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"     .     ",
           (const char *)"     .     ",
           (const char *)"    ...    ",
           (const char *)"    .E.    ",
           (const char *)"   ....f   ",
           (const char *)"   .....   ",
           (const char *)"  .......  ",
           (const char *)"  .......  ",
           (const char *)" ..G...G.. ",
           (const char *)"^.........^",
           (const char *)"     ^     ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"...        ",
           (const char *)".M....     ",
           (const char *)"...  .     ",
           (const char *)".f.  .     ",
           (const char *)"...  s     ",
           (const char *)" s   .....^",
           (const char *)"..$  .   s ",
           (const char *)"     .   . ",
           (const char *)"E..| .   . ",
           (const char *)"......s..$ ",
           (const char *)"...|       ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"...        ",
           (const char *)".M....     ",
           (const char *)"...  s     ",
           (const char *)"  s  .     ",
           (const char *)"...  .| |  ",
           (const char *)".f.  .....^",
           (const char *)"$..  .| |  ",
           (const char *)"     .     ",
           (const char *)"E..  s     ",
           (const char *)".....t     ",
           (const char *)"...        ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"...        ",
           (const char *)".M....     ",
           (const char *)"...  .     ",
           (const char *)" s   .     ",
           (const char *)" ... s     ",
           (const char *)" ... .....^",
           (const char *)" M.$ .     ",
           (const char *)"     .     ",
           (const char *)"E..  .     ",
           (const char *)"......     ",
           (const char *)"..f        ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"...     ^  ",
           (const char *)"..M...  .  ",
           (const char *)"...  .  .  ",
           (const char *)"  s  .  .  ",
           (const char *)"  .  s||.  ",
           (const char *)"  $  .....^",
           (const char *)"  .  .||   ",
           (const char *)"  s  .     ",
           (const char *)"E..  .     ",
           (const char *)"...LL.     ",
           (const char *)"..f        ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"...     ^  ",
           (const char *)"M.....  .  ",
           (const char *)"...  .  .  ",
           (const char *)"...  .  .  ",
           (const char *)"...  s  .  ",
           (const char *)"..$  .....^",
           (const char *)"     w  .  ",
           (const char *)"     w  .  ",
           (const char *)"E..  w  .  ",
           (const char *)"...www  .  ",
           (const char *)"f..     ^  ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"...        ",
           (const char *)".M....     ",
           (const char *)"...  .     ",
           (const char *)"     .     ",
           (const char *)"     .     ",
           (const char *)"     t....^",
           (const char *)"     .     ",
           (const char *)"     .     ",
           (const char *)"E..| .     ",
           (const char *)"......     ",
           (const char *)".f.|       ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"...        ",
           (const char *)".M....     ",
           (const char *)"...  .     ",
           (const char *)"  s  s     ",
           (const char *)"...  .B B  ",
           (const char *)"...  .....^",
           (const char *)"$..  .B B  ",
           (const char *)"     s     ",
           (const char *)"E..  .     ",
           (const char *)"f.....     ",
           (const char *)"...        ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"...        ",
           (const char *)".M....     ",
           (const char *)"...  .     ",
           (const char *)" s   .     ",
           (const char *)" ... .     ",
           (const char *)" ... .....^",
           (const char *)" M.$ .     ",
           (const char *)"     .     ",
           (const char *)"E..  .     ",
           (const char *)"......     ",
           (const char *)".f.        ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"...     ^  ",
           (const char *)"..M...  .  ",
           (const char *)"...  .  .  ",
           (const char *)"  s  .  .  ",
           (const char *)"  t  .||.  ",
           (const char *)"  .  .....^",
           (const char *)"  .  .||   ",
           (const char *)"  .  .     ",
           (const char *)"E..  .     ",
           (const char *)"...CCt     ",
           (const char *)"..f        ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"...     ^  ",
           (const char *)"M.....  .  ",
           (const char *)"...  .  .  ",
           (const char *)"     .  .  ",
           (const char *)"     .  .  ",
           (const char *)"     .....^",
           (const char *)"     w  .  ",
           (const char *)"     w  .  ",
           (const char *)"E..  w  .  ",
           (const char *)"...www  .  ",
           (const char *)"f..     ^  ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"www        ",
           (const char *)"wMwwww     ",
           (const char *)"www  w     ",
           (const char *)"     w     ",
           (const char *)"     w     ",
           (const char *)"     wwwww^",
           (const char *)"     w     ",
           (const char *)"     w     ",
           (const char *)"Eww| w     ",
           (const char *)"wfwwww     ",
           (const char *)"www|       ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"www        ",
           (const char *)"wMwwww     ",
           (const char *)"www  s     ",
           (const char *)"  s  w     ",
           (const char *)"www  w| B  ",
           (const char *)"www  wwwww^",
           (const char *)"$ww  w| B  ",
           (const char *)"     w     ",
           (const char *)"Eww  s     ",
           (const char *)"wwwwww     ",
           (const char *)"wwf        ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"www        ",
           (const char *)"wMwwww     ",
           (const char *)"www  w     ",
           (const char *)" s   w     ",
           (const char *)" www w     ",
           (const char *)" www wwwww^",
           (const char *)" Mw$ w     ",
           (const char *)"     w     ",
           (const char *)"Eww  w     ",
           (const char *)"wwwwww     ",
           (const char *)"wwf        ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"www     ^  ",
           (const char *)"wwMwww  w  ",
           (const char *)"www  w  w  ",
           (const char *)"  s  w  w  ",
           (const char *)"  w  w||w  ",
           (const char *)"  t  WWWWw^",
           (const char *)"  w  w||   ",
           (const char *)"  w  W     ",
           (const char *)"Eww  W     ",
           (const char *)"wwwWWW     ",
           (const char *)"wwf        ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"www     ^  ",
           (const char *)"Mwwwww  w  ",
           (const char *)"fww  w  w  ",
           (const char *)"     w  w  ",
           (const char *)"     w  w  ",
           (const char *)"     wwwww^",
           (const char *)"     w  w  ",
           (const char *)"     w  w  ",
           (const char *)"Eww  w  w  ",
           (const char *)"wwwwww  w  ",
           (const char *)"www     ^  ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"  ^        ",
           (const char *)"  .  . .CC ",
           (const char *)"  .ww.`..  ",
           (const char *)"   www`.   ",
           (const char *)"  ^.wEw.^  ",
           (const char *)"   .www.   ",
           (const char *)"...M..www  ",
           (const char *)"..g.C.Cwwf ",
           (const char *)"    C.C    ",
           (const char *)"    C.C    ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"     ^     ",
           (const char *)"     .     ",
           (const char *)"  f.....   ",
           (const char *)" C`.B.B.   ",
           (const char *)"^....E...t^",
           (const char *)" C `.....  ",
           (const char *)" C```.M....",
           (const char *)"  ..CCC....",
           (const char *)"  $gCCCC...",
           (const char *)"  CCC   CC ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"       ^   ",
           (const char *)"       g!  ",
           (const char *)"   ......  ",
           (const char *)"   .``..   ",
           (const char *)"^...```.^  ",
           (const char *)"   .``..   ",
           (const char *)"   .....f  ",
           (const char *)"   C...C   ",
           (const char *)".. .B.B. ..",
           (const char *)".....EM....",
           (const char *)"..... .....",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"     ^     ",
           (const char *)"   ``.``.! ",
           (const char *)"   `..B``` ",
           (const char *)"^........E ",
           (const char *)"   ...B``` ",
           (const char *)"   f...``. ",
           (const char *)"       CCD ",
           (const char *)"   ..$CCC. ",
           (const char *)"   ...CCC. ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"     ^     ",
           (const char *)"     .     ",
           (const char *)"   ..C.C!  ",
           (const char *)" f.....CC  ",
           (const char *)"  .......  ",
           (const char *)" ...M....  ",
           (const char *)" ......C   ",
           (const char *)" CC...CE   ",
           (const char *)" CCC.CC    ",
           (const char *)"  CCCC   ..",
           (const char *)"   .......$",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"  ^        ",
           (const char *)"  .  . .CC ",
           (const char *)"  .ww.`..  ",
           (const char *)"   ww``.   ",
           (const char *)"  ^..E`.^  ",
           (const char *)"   .www.   ",
           (const char *)"  .M..www  ",
           (const char *)"  g. . wwf ",
           (const char *)"     .     ",
           (const char *)"     .     ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"     ^     ",
           (const char *)"     .     ",
           (const char *)"  f.....   ",
           (const char *)"  `.B.B.   ",
           (const char *)"^....E..t.^",
           (const char *)"   w....   ",
           (const char *)"  www.M.   ",
           (const char *)"  ..       ",
           (const char *)"  $g       ",
           (const char *)"           ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"       ^   ",
           (const char *)"       g!  ",
           (const char *)"   ......  ",
           (const char *)"   .ww..   ",
           (const char *)"^...www.^  ",
           (const char *)"   .ww..   ",
           (const char *)"   .....f  ",
           (const char *)"    .t.    ",
           (const char *)" ...|E|... ",
           (const char *)" . ...M. . ",
           (const char *)" ......... ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"     ^     ",
           (const char *)"   ``.ww.! ",
           (const char *)"   `..Bwww ",
           (const char *)"^........E ",
           (const char *)"   ...Bwww ",
           (const char *)"   f...ww. ",
           (const char *)"         s ",
           (const char *)"  C..$CCC. ",
           (const char *)"  Cm..CCC. ",
           (const char *)"  CCCCCCCC ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"     ^     ",
           (const char *)"     .     ",
           (const char *)"   ..C.C!  ",
           (const char *)" f.....CC  ",
           (const char *)"  .......  ",
           (const char *)" ...M....  ",
           (const char *)" ......C   ",
           (const char *)" CC...CE   ",
           (const char *)" CCC.      ",
           (const char *)"           ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"  ^        ",
           (const char *)"  .        ",
           (const char *)"  .  . .CC ",
           (const char *)"  .ww.`..  ",
           (const char *)"   ww``.   ",
           (const char *)"  ^..E`.^  ",
           (const char *)"   .www.   ",
           (const char *)"  .M..www  ",
           (const char *)"  g. . wwf ",
           (const char *)"     .     ",
           (const char *)"     .     ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"     ^     ",
           (const char *)"     .     ",
           (const char *)"  f.....   ",
           (const char *)"  `.....   ",
           (const char *)"^....E....^",
           (const char *)"   L....   ",
           (const char *)" LLLL.M.   ",
           (const char *)"LL..       ",
           (const char *)"L $g       ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"       ^   ",
           (const char *)"       g!  ",
           (const char *)"   ......  ",
           (const char *)"   .LL..   ",
           (const char *)"^....LL.^  ",
           (const char *)"   .LL..   ",
           (const char *)"   .....f  ",
           (const char *)"    .E.    ",
           (const char *)"   .|.|.   ",
           (const char *)"   ...M.   ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"     ^     ",
           (const char *)"   ``.LL.! ",
           (const char *)"   `..BLLL ",
           (const char *)"^........E ",
           (const char *)"   ...BLLL ",
           (const char *)"   f...LL. ",
           (const char *)"         D ",
           (const char *)"   $.$ ... ",
           (const char *)"   $m.s... ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"     ^     ",
           (const char *)"     .     ",
           (const char *)"   ..C.C!  ",
           (const char *)" f.....CC  ",
           (const char *)"  .......  ",
           (const char *)" ...M....  ",
           (const char *)" .....tC   ",
           (const char *)" CC...CE   ",
           (const char *)" CCC.      ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"     ^ ..  ",
           (const char *)"   f...b.  ",
           (const char *)"   .....   ",
           (const char *)"  ^..E..^  ",
           (const char *)"   .....   ",
           (const char *)"  .M.....  ",
           (const char *)"  g. . .!  ",
           (const char *)"     .     ",
           (const char *)"     .     ",
           (const char *)"     ^     ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"     ^     ",
           (const char *)"   f...    ",
           (const char *)"   ..t..   ",
           (const char *)"   ..E..   ",
           (const char *)"  !.....   ",
           (const char *)"   b..M.   ",
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"   M.b..!  ",
           (const char *)"   .b...   ",
           (const char *)"^.........^",
           (const char *)"   ..E..   ",
           (const char *)"   .....f  ",
           (const char *)"    ...    ",
           (const char *)"    B.B    ",
           (const char *)"     .     ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"     ^     ",
           (const char *)"     .     ",
           (const char *)"   ....C.. ",
           (const char *)"   ...B... ",
           (const char *)"  ^......E ",
           (const char *)"   ...B... ",
           (const char *)"   ....C.. ",
           (const char *)"     s   s ",
           (const char *)"   !..G  ..",
           (const char *)"   ....s...",
           (const char *)"   ...f  ..",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"     ^     ",
           (const char *)"     .     ",
           (const char *)"^...C..    ",
           (const char *)"     ..    ",
           (const char *)"     ....f ",
           (const char *)"     .LL.  ",
           (const char *)"     .LL.  ",
           (const char *)"     M..E  ",
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"  LLLELLLLL",
           (const char *)"  LLL.LLLL.",
           (const char *)"   LL.LL. .",
           (const char *)"   LLMLL  .",
           (const char *)"   .LLL.  .",
           (const char *)"     .    .",
           (const char *)"^....!    .",
           (const char *)"   M.......",
           (const char *)"   $f.LLLLL",
           (const char *)"     .     ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"      g..^ ",
           (const char *)"       C   ",
           (const char *)"   f....   ",
           (const char *)"   ..CCCCC ",
           (const char *)"^....C.M.E ",
           (const char *)"   ..C.C.C ",
           (const char *)"      .C.  ",
           (const char *)"     ....  ",
           (const char *)"     .     ",
           (const char *)"    ..     ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"   ^    f  ",
           (const char *)"   ......  ",
           (const char *)"   |LL..   ",
           (const char *)"^...LLL.!  ",
           (const char *)"   |LL..   ",
           (const char *)"   .....g  ",
           (const char *)"    ...    ",
           (const char *)"    B.B    ",
           (const char *)"    BEB    ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"        ^  ",
           (const char *)"   f.L.... ",
           (const char *)"   .LLLLL. ",
           (const char *)"   LLLLLLL ",
           (const char *)"^.........!",
           (const char *)"   LLLLLLL ",
           (const char *)"   ....... ",
           (const char *)"   s     s ",
           (const char *)"   .  E  . ",
           (const char *)"   .  C  . ",
           (const char *)"   $..C..m ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"     ^     ",
           (const char *)"    C=C    ",
           (const char *)"    C=C    ",
           (const char *)"    C=C    ",
           (const char *)" f..C=C...^",
           (const char *)" ...C=C... ",
           (const char *)"  .......  ",
           (const char *)"   ..M..   ",
           (const char *)"   . E .   ",
           (const char *)"   .   .   ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"    wEw    ",
           (const char *)"   ww=ww   ",
           (const char *)"   ww=ww   ",
           (const char *)"   ww=ww   ",
           (const char *)"^.......   ",
           (const char *)"       .   ",
           (const char *)"       .   ",
           (const char *)"       .   ",
           (const char *)"       .   ",
           (const char *)"       .   ",
           (const char *)"       ^   ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"   !....   ",
           (const char *)"   ..wwwww ",
           (const char *)"^.......ME ",
           (const char *)"   ..wwwww ",
           (const char *)"   f  w    ",
           (const char *)"      w    ",
           (const char *)"      ww   ",
           (const char *)"      ww$  ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"   ww...!  ",
           (const char *)"   www..   ",
           (const char *)"^.wwwww.   ",
           (const char *)"   www..   ",
           (const char *)"   ..E..f  ",
           (const char *)"    ...    ",
           (const char *)"    B.B    ",
           (const char *)"    BMB    ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"     ^     ",
           (const char *)"     .     ",
           (const char *)"   www...! ",
           (const char *)"   wwwwwww ",
           (const char *)"^......w..^",
           (const char *)"  fwwwwwww ",
           (const char *)"   www.... ",
           (const char *)"   s     s ",
           (const char *)"   .  E  . ",
           (const char *)"   M  L  . ",
           (const char *)"   m..L..$ ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"     ^     ",
           (const char *)"     .     ",
           (const char *)"    www    ",
           (const char *)"    www    ",
           (const char *)"  f.wwwf.  ",
           (const char *)"  .wwww..  ",
           (const char *)" ..wwww.M. ",
           (const char *)" s  www  . ",
           (const char *)" .   E   . ",
           (const char *)" $       C ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"    .E.    ",
           (const char *)"   f....   ",
           (const char *)"   .....   ",
           (const char *)"   ..M..   ",
           (const char *)"^......!   ",
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"   M....   ",
           (const char *)"   ...!... ",
           (const char *)"^........E ",
           (const char *)"   f...... ",
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"   f       ",
           (const char *)"   ....MC$ ",
           (const char *)" B |....C. ",
           (const char *)"^...tE.!C. ",
           (const char *)" B |...CC. ",
           (const char *)"    ..CCC. ",
           (const char *)"     .     ",
           (const char *)"    B.B    ",
           (const char *)"     .     ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"     ^     ",
           (const char *)"     .     ",
           (const char *)"   .....Bf ",
           (const char *)"   .b....B ",
           (const char *)"^.....!... ",
           (const char *)"   ....... ",
           (const char *)"   ......f ",
           (const char *)"   s       ",
           (const char *)"   .CCECC$ ",
           (const char *)"   .CC.CCC ",
           (const char *)"   ...mCC. ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"     ^     ",
           (const char *)"     .     ",
           (const char *)"    ...    ",
           (const char *)"    ...    ",
           (const char *)"  .......  ",
           (const char *)"  .!.E...  ",
           (const char *)"  f.....M  ",
           (const char *)"     s     ",
           (const char *)"     .     ",
           (const char *)"   .....   ",
           (const char *)"   $m..$   ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"    LML    ",
           (const char *)"   LL.LL   ",
           (const char *)"   LL.LL   ",
           (const char *)"   LL.LLL .",
           (const char *)"^........s$",
           (const char *)"   LL.LLL .",
           (const char *)"   LL.LL  .",
           (const char *)"   LL.LL  .",
           (const char *)"    L.L   .",
           (const char *)"    ELL g.!",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"  CCCCCCC  ",
           (const char *)"  C!....C  ",
           (const char *)"  C..CCCCC ",
           (const char *)"^....C...E ",
           (const char *)"  C..CCCCC ",
           (const char *)"  C....MC  ",
           (const char *)"  CCCCCCC  ",
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"   C.M.C   ",
           (const char *)"  CC.C.C   ",
           (const char *)"  C.CbC.CCB",
           (const char *)"^.t.CC.C..E",
           (const char *)"  C.C.C.CCB",
           (const char *)"  CC.C.C   ",
           (const char *)"   C..!C   ",
           (const char *)"    CCCC   ",
           (const char *)"           ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"     ^     ",
           (const char *)"     .     ",
           (const char *)"   ....L.. ",
           (const char *)"   LLLLLLL ",
           (const char *)"^...L....g ",
           (const char *)"   LLL.LLL ",
           (const char *)"   ....... ",
           (const char *)"   D       ",
           (const char *)"   .  ...! ",
           (const char *)"   E.s..M. ",
           (const char *)"      .... ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"     ^     ",
           (const char *)"     .     ",
           (const char *)"    C.C    ",
           (const char *)" CCCCtCCCC ",
           (const char *)" CB.....gC ",
           (const char *)" C...C...C ",
           (const char *)" CB.!...BC ",
           (const char *)" CCCC.CCCC ",
           (const char *)"    CEC    ",
           (const char *)"    CCC    ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"           ",
           (const char *)" LLLL....! ",
           (const char *)" LE.LL..b. ",
           (const char *)" LLLLLL... ",
           (const char *)" ...t..... ",
           (const char *)" .LLLLLL.. ",
           (const char *)" .LLLLL... ",
           (const char *)" .......m. ",
           (const char *)"     ^     ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"     ....! ",
           (const char *)"    .L....^",
           (const char *)"   .LL.... ",
           (const char *)"^.gLLLLL.. ",
           (const char *)" ...LL.... ",
           (const char *)" ....L..   ",
           (const char *)" f.....    ",
           (const char *)"      E    ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"           ",
           (const char *)" !.m..L..B ",
           (const char *)" ....L..m. ",
           (const char *)" ...LL.... ",
           (const char *)"^..LLLLL.. ",
           (const char *)"        .  ",
           (const char *)"       LLL ",
           (const char *)"       LEL ",
           (const char *)"           ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"  ^        ",
           (const char *)"^........B ",
           (const char *)" ....L.... ",
           (const char *)" ...LL.... ",
           (const char *)" ..LLLLL.. ",
           (const char *)" .  .g.  . ",
           (const char *)" .       . ",
           (const char *)" !...$m... ",
           (const char *)"    .LLL.  ",
           (const char *)"    .LEL.  ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"     ^     ",
           (const char *)"     .     ",
           (const char *)" $.. . .$. ",
           (const char *)" LLL . LLL ",
           (const char *)" .....s..m ",
           (const char *)" .m. . .E. ",
           (const char *)" ... L .!. ",
           (const char *)" .!. .D..f ",
           (const char *)" ... .  s $",
           (const char *)" ... L  .LL",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)" ........B ",
           (const char *)" ....w.... ",
           (const char *)" ...www... ",
           (const char *)" ..ww!ww.. ",
           (const char *)" ...ww.... ",
           (const char *)" ....w..f. ",
           (const char *)" E........ ",
           (const char *)"     ^     ",
           (const char *)"           ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"     ^     ",
           (const char *)"     ....f ",
           (const char *)"    .w.... ",
           (const char *)"   .ww....^",
           (const char *)" .gwWwww.. ",
           (const char *)" ...ww.... ",
           (const char *)"^.!..w..   ",
           (const char *)" B....E    ",
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)" ..m..w..B ",
           (const char *)" ....w.... ",
           (const char *)"^...ww..!. ",
           (const char *)" ..wwwww.. ",
           (const char *)"    wEw    ",
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"       ^   ",
           (const char *)" B.......B ",
           (const char *)" ....w....^",
           (const char *)" ...ww..!. ",
           (const char *)" ..wwwww.. ",
           (const char *)" .ww.g.ww. ",
           (const char *)" .wwwwwww. ",
           (const char *)" ....$m... ",
           (const char *)"    .www.  ",
           (const char *)"    ....E  ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"     ^     ",
           (const char *)"     .     ",
           (const char *)" $.. . $.. ",
           (const char *)" CCC . CCC ",
           (const char *)" ... . ..m ",
           (const char *)" .m. . .!. ",
           (const char *)" ... w ... ",
           (const char *)" CCC .D..C ",
           (const char *)" .E.s.     ",
           (const char *)" ... .  .! ",
           (const char *)"     ^     ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"   B.!.B   ",
           (const char *)"    .C.    ",
           (const char *)"    .C.    ",
           (const char *)"^..C.C....^",
           (const char *)"    .C.    ",
           (const char *)"    mC.    ",
           (const char *)"   B...B   ",
           (const char *)"     E     ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"  B B B !  ",
           (const char *)"  .......  ",
           (const char *)"^.gCCECCt.^",
           (const char *)"  .......  ",
           (const char *)"   B B B   ",
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"C.CCCCC... ",
           (const char *)" .C..CCCCC ",
           (const char *)"  CCCC..C. ",
           (const char *)" ...CC.!CC ",
           (const char *)"^..CCCCCC. ",
           (const char *)" ...C.E.CC ",
           (const char *)" ...C...C  ",
           (const char *)" g.CCCCCC  ",
           (const char *)"           ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"         ^ ",
           (const char *)" .....C... ",
           (const char *)" .!..CC... ",
           (const char *)" ...CCC.m. ",
           (const char *)" ..CC.C... ",
           (const char *)" CCCCCCCCC ",
           (const char *)" ....C....^",
           (const char *)" ....C.m.. ",
           (const char *)" .CCCCCCC. ",
           (const char *)" E...$...f ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"     ^     ",
           (const char *)" m....  .g ",
           (const char *)" ..!.C  .. ",
           (const char *)" B..CC  .. ",
           (const char *)" CCCC..... ",
           (const char *)" CCCCCCCC. ",
           (const char *)" CCCCCCC.. ",
           (const char *)" g........ ",
           (const char *)"  ^      E ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"      ^    ",
           (const char *)" .  ...... ",
           (const char *)" ....L.  . ",
           (const char *)"    .L.    ",
           (const char *)"^....L.!..^",
           (const char *)"    .L.    ",
           (const char *)"    .L.  $ ",
           (const char *)"    E.m  . ",
           (const char *)"     s   . ",
           (const char *)"     ..... ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"  .LLLL.L. ",
           (const char *)"  .LLLL... ",
           (const char *)"  .LLLLLL. ",
           (const char *)"^..LL$LLL. ",
           (const char *)"  ........ ",
           (const char *)"  .LLLLLL. ",
           (const char *)"  .LLELLL. ",
           (const char *)"  .LLLLLL. ",
           (const char *)"  ...m.... ",
           (const char *)"         ^ ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"L.LLLLL... ",
           (const char *)" .L..LLLLL ",
           (const char *)"     L..L. ",
           (const char *)"     Lt.LL ",
           (const char *)"^..LLLLLL.^",
           (const char *)" ...LE..LL ",
           (const char *)" ...L...L  ",
           (const char *)" g.LLLLLL  ",
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)" .....L... ",
           (const char *)" .!..LL... ",
           (const char *)" ...LLL.m. ",
           (const char *)" ..LLEL... ",
           (const char *)" LLLLLLLLL ",
           (const char *)"^....L.... ",
           (const char *)"     L.m.. ",
           (const char *)"     LLLL. ",
           (const char *)"     $...f ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)" m....  .g ",
           (const char *)" ....L  .. ",
           (const char *)"     L  .. ",
           (const char *)" LLLL..... ",
           (const char *)" LLELLLLL.^",
           (const char *)"^LLLLLLL.. ",
           (const char *)" g...t...! ",
           (const char *)"     ^     ",
           (const char *)"           ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"    ww.    ",
           (const char *)"    .w.    ",
           (const char *)"    .w.    ",
           (const char *)"^....w!...^",
           (const char *)"    .w.    ",
           (const char *)"    .w.    ",
           (const char *)"    E.m    ",
           (const char *)"           ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"       ^   ",
           (const char *)"  wwwww.w. ",
           (const char *)"  wwwww...^",
           (const char *)"  ww!wwww. ",
           (const char *)" .www$www. ",
           (const char *)"  .ww.www. ",
           (const char *)"  .wwwwww. ",
           (const char *)"  .wwEwww. ",
           (const char *)"  .wwwwww. ",
           (const char *)"  ...m.... ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"w.wwwww...^",
           (const char *)"     wwwww ",
           (const char *)"     w..w.^",
           (const char *)" ...ww..ww ",
           (const char *)"^..wwwwww. ",
           (const char *)"     .f.ww ",
           (const char *)"     ..Ew  ",
           (const char *)" g.wwwwww  ",
           (const char *)"           ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)" ^         ",
           (const char *)" .....w... ",
           (const char *)" ....ww...^",
           (const char *)" ...www.m. ",
           (const char *)" ..wEww... ",
           (const char *)" wwww!wwww ",
           (const char *)" ..www.... ",
           (const char *)" ww..w.m.. ",
           (const char *)" .wwwwwww. ",
           (const char *)" ....$..ww ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"     ^     ",
           (const char *)" m....  .g ",
           (const char *)" ....w  .. ",
           (const char *)"     w  ..^",
           (const char *)"     t.... ",
           (const char *)" wwww!www. ",
           (const char *)" wwEwwww.. ",
           (const char *)" g........ ",
           (const char *)"           ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"   Lm..L   ",
           (const char *)"   L.C.L   ",
           (const char *)"   L.C.L   ",
           (const char *)"^..L.C...t^",
           (const char *)"   L.C.L   ",
           (const char *)"   L.C.L   ",
           (const char *)"  EL!..L   ",
           (const char *)"   LLLLL   ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"  .CCCC.C. ",
           (const char *)"  .CCCC...^",
           (const char *)"  .CCCCCC. ",
           (const char *)"^..CC$.CC. ",
           (const char *)"  .CC!.CC. ",
           (const char *)"  .CCCCCC. ",
           (const char *)"  ...CCCC. ",
           (const char *)"  .C.CCCC. ",
           (const char *)"  f..m...E ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"C.CCCCC...^",
           (const char *)" .C..CC.CC ",
           (const char *)"  CCCC!.C. ",
           (const char *)" ...CC     ",
           (const char *)"^..CCC     ",
           (const char *)" ....f     ",
           (const char *)" ...C...C  ",
           (const char *)" g.CCCCCC  ",
           (const char *)"     E     ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)" ^         ",
           (const char *)" .....C.!. ",
           (const char *)" .E..CC...^",
           (const char *)" ...C.C.m. ",
           (const char *)"     ..... ",
           (const char *)"     CCCCC ",
           (const char *)"     C.... ",
           (const char *)" ....C.m.. ",
           (const char *)" .CCCCCCC. ",
           (const char *)" ....$.... ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"     ^     ",
           (const char *)" m....  .$ ",
           (const char *)" ....C  LL ",
           (const char *)"^...CC  .. ",
           (const char *)" CC.C..... ",
           (const char *)" CC.CCCCC. ",
           (const char *)" CC.CCCC.. ",
           (const char *)" g.......! ",
           (const char *)"      E    ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"    E..    ",
           (const char *)"    .w.    ",
           (const char *)"    .w.    ",
           (const char *)"^..B.!....^",
           (const char *)"    .w.    ",
           (const char *)"    .w.    ",
           (const char *)"    ...    ",
           (const char *)"      ^    ",
           (const char *)"           ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"  .w.wwww. ",
           (const char *)"  .wwEwww. ",
           (const char *)"  .wwww!w. ",
           (const char *)" ..ww$www. ",
           (const char *)"  .ww.www. ",
           (const char *)"  .wwwwfw. ",
           (const char *)"  .wwwwww. ",
           (const char *)"  .wwwww.. ",
           (const char *)"  ...m.... ",
           (const char *)"       ^   ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"w.wwwww... ",
           (const char *)" .w..wwwww ",
           (const char *)" !wwwwt.w. ",
           (const char *)" ...ww..ww ",
           (const char *)"^..wwwwww. ",
           (const char *)" ...w..tww ",
           (const char *)" ...wE..w  ",
           (const char *)" g.wwwwww  ",
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"   ^       ",
           (const char *)" B....w..B ",
           (const char *)" ....ww... ",
           (const char *)" ...www.m. ",
           (const char *)" ..ww!w... ",
           (const char *)" wwwwwwwww ",
           (const char *)" ...Ew...f ",
           (const char *)" ....w.m.. ",
           (const char *)" .wwwwwww. ",
           (const char *)" ....$....^",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"   ^       ",
           (const char *)" m....  Bg ",
           (const char *)" ....w  .. ",
           (const char *)" ...ww  .. ",
           (const char *)" wwww..... ",
           (const char *)" w!wwwwww. ",
           (const char *)" wwwwwww.. ",
           (const char *)" g.......B ",
           (const char *)"        E  ",
           (const char *)"           ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"     E     ",
           (const char *)"   CCCCC   ",
           (const char *)" CCC...CCC ",
           (const char *)"^..B..!...^",
           (const char *)" CCC...CfC ",
           (const char *)"   CCCCC   ",
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"  .$.m..$E ",
           (const char *)"      .    ",
           (const char *)" CCCCCCCCC ",
           (const char *)"^====!====^",
           (const char *)" CCCCCCCCC ",
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)" .wwwww.$E ",
           (const char *)" $w..wwwww ",
           (const char *)"  wwww..w. ",
           (const char *)"        w  ",
           (const char *)"^...t.....^",
           (const char *)" CCCCCCCCC ",
           (const char *)" CCCCCCCC  ",
           (const char *)" g....!.$  ",
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)" $.....    ",
           (const char *)" .CCC=C    ",
           (const char *)" CCCC=C    ",
           (const char *)" CCCC=CCCC ",
           (const char *)"^....=....^",
           (const char *)" CCCCCCCCC ",
           (const char *)"        .g ",
           (const char *)"     !...  ",
           (const char *)"     E     ",
           (const char *)"           ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"^m....  Bg ",
           (const char *)" .!..w  .. ",
           (const char *)" ...ww  .. ",
           (const char *)" wwww..... ",
           (const char *)" wwwwwwww. ",
           (const char *)" wwwwwww..^",
           (const char *)" g.......B ",
           (const char *)"  .    E   ",
           (const char *)"  t        ",
           (const char *)"  ^        ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"   ^       ",
           (const char *)" ..t.|.... ",
           (const char *)"^..|gL.|.. ",
           (const char *)" ...LLL... ",
           (const char *)" .|LLfLL|.^",
           (const char *)" ...LLL... ",
           (const char *)" ..|.Lg|.. ",
           (const char *)"  ...|...  ",
           (const char *)"    ...    ",
           (const char *)"     ^     ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"  .......  ",
           (const char *)"^......... ",
           (const char *)" ...L.L... ",
           (const char *)" ...L.L...^",
           (const char *)" LLLLLLLLL ",
           (const char *)" .LLLLLLL. ",
           (const char *)" ..m.....$ ",
           (const char *)"           ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"    ^      ",
           (const char *)"  ......LL ",
           (const char *)" m.......L ",
           (const char *)" ...L..... ",
           (const char *)" ...Lg.... ",
           (const char *)" ...LLLL..^",
           (const char *)" L...L..   ",
           (const char *)" LL....  $ ",
           (const char *)"      s  L ",
           (const char *)" $.......m ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"^........m ",
           (const char *)" LLLL...b. ",
           (const char *)" ...L..... ",
           (const char *)" ...L..... ",
           (const char *)" ...LLLL.. ",
           (const char *)" ......L.. ",
           (const char *)" ...m..L..^",
           (const char *)"           ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"     ^     ",
           (const char *)" ...L...bb ",
           (const char *)" .b.L..... ",
           (const char *)" ...L.LLLL ",
           (const char *)" LLLL.....^",
           (const char *)" ...LLL... ",
           (const char *)"^....L.... ",
           (const char *)" $...LL.m. ",
           (const char *)"           ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"   ^       ",
           (const char *)" ......... ",
           (const char *)"^..|gL.... ",
           (const char *)" ..LLLL... ",
           (const char *)" ....fLL|.^",
           (const char *)" ..LLLL... ",
           (const char *)" ...LLg|.. ",
           (const char *)"  ...|...  ",
           (const char *)"    ...    ",
           (const char *)"     ^     ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"  .......  ",
           (const char *)" ...|.|... ",
           (const char *)"^...L.L... ",
           (const char *)" ...L.L... ",
           (const char *)" LLLL.LLLL ",
           (const char *)" .LLL.LLL.^",
           (const char *)" ..m.....$ ",
           (const char *)"           ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"  ......LL ",
           (const char *)" ........L ",
           (const char *)" |..L..... ",
           (const char *)"^...Lg.... ",
           (const char *)" |..LLLL..^",
           (const char *)" L...L..   ",
           (const char *)" LL....  $ ",
           (const char *)" LLLL..  L ",
           (const char *)" .LLLLL..m ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"           ",
           (const char *)" ...|.|..f ",
           (const char *)" LLL...... ",
           (const char *)" |.LLL..b. ",
           (const char *)"^...LLL... ",
           (const char *)" |..LLLL.. ",
           (const char *)" .....LL..^",
           (const char *)" ...m..L.. ",
           (const char *)"           ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"         ^ ",
           (const char *)" ...L..... ",
           (const char *)" ...L..LL. ",
           (const char *)" ..LL.LLLL ",
           (const char *)" LLLL...LL ",
           (const char *)"^...LLL..L ",
           (const char *)" ....L....^",
           (const char *)" $...LL.m. ",
           (const char *)"           ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"   ^       ",
           (const char *)" ......... ",
           (const char *)"^.|LL.LL|. ",
           (const char *)" LLLL.LLL. ",
           (const char *)" .LLLMLLL.^",
           (const char *)" .LLL.LLLL ",
           (const char *)" .|LL.LL|. ",
           (const char *)" ......... ",
           (const char *)"    C.C    ",
           (const char *)"     ^     ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)" g..C.C... ",
           (const char *)" ...C.CC.. ",
           (const char *)" ..CC.CCC. ",
           (const char *)"^..CC.CC.. ",
           (const char *)" CCCC.CCC. ",
           (const char *)" ...C.CC.. ",
           (const char *)" CC....... ",
           (const char *)" .C        ",
           (const char *)" .......$  ",
           (const char *)"  .......$ ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"    ^      ",
           (const char *)"  .....    ",
           (const char *)" .......   ",
           (const char *)" |..C....| ",
           (const char *)"^...Cg....^",
           (const char *)" |..CCC..| ",
           (const char *)"   ..CC..  ",
           (const char *)"$$  ... s  ",
           (const char *)"s       .  ",
           (const char *)"..... .sL  ",
           (const char *)"..m ... .  ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"     ^     ",
           (const char *)"   ....... ",
           (const char *)"  .....L.. ",
           (const char *)" ...L.LLL. ",
           (const char *)" ...L..LL. ",
           (const char *)" ...LLLL.. ",
           (const char *)" s ...LL.  ",
           (const char *)" . ....... ",
           (const char *)" .       . ",
           (const char *)" ..$   g.g ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"     ^     ",
           (const char *)"  ......   ",
           (const char *)" ..|...|.  ",
           (const char *)" ...LLL..  ",
           (const char *)" ..LLLLg..^",
           (const char *)"^...LLL..  ",
           (const char *)" |.......| ",
           (const char *)"     s     ",
           (const char *)"    $..    ",
           (const char *)"    ..M    ",
           (const char *)"  .......  ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"   ^       ",
           (const char *)" ..t.|.... ",
           (const char *)"^...gC.... ",
           (const char *)" ...CCC... ",
           (const char *)" .|CCfCC|.^",
           (const char *)" ...CCC... ",
           (const char *)" ....Cg... ",
           (const char *)"  ...|...  ",
           (const char *)"    ...    ",
           (const char *)"     ^     ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"  .......  ",
           (const char *)"^......... ",
           (const char *)" ...C.C... ",
           (const char *)" ...C.C...^",
           (const char *)" CCCCCCCCC ",
           (const char *)" .CCCCCCC. ",
           (const char *)" ..m.....$ ",
           (const char *)"           ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"    ^      ",
           (const char *)"  ......CC ",
           (const char *)" m.......C ",
           (const char *)" ...C..... ",
           (const char *)" ...Cg.... ",
           (const char *)" ...CCCC..^",
           (const char *)" C...C..   ",
           (const char *)" CC....  $ ",
           (const char *)"      s  C ",
           (const char *)" $.......m ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"^........m ",
           (const char *)" CCCC...b. ",
           (const char *)" ...C..... ",
           (const char *)" ...C..... ",
           (const char *)" ...CCCC.. ",
           (const char *)" ......C.. ",
           (const char *)" ...m..C..^",
           (const char *)"           ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"     ^     ",
           (const char *)" ...C...bb ",
           (const char *)" .b.C..... ",
           (const char *)" ...C.CCCC ",
           (const char *)" CCCC.....^",
           (const char *)" ...CCC... ",
           (const char *)"^....C.... ",
           (const char *)" $...CC.m. ",
           (const char *)"           ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"   ^       ",
           (const char *)" ......... ",
           (const char *)"^..|gC.... ",
           (const char *)" ..CCCC... ",
           (const char *)" ....fCC|.^",
           (const char *)" ..CCCC... ",
           (const char *)" ...CCg|.. ",
           (const char *)"  ...|...  ",
           (const char *)"    ...    ",
           (const char *)"     ^     ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"  .......  ",
           (const char *)" ...|.|... ",
           (const char *)"^...C.C... ",
           (const char *)" ...C.C... ",
           (const char *)" CCCC.CCCC ",
           (const char *)" .CCC.CCC.^",
           (const char *)" ..m.....$ ",
           (const char *)"           ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"  ......CC ",
           (const char *)" ........C ",
           (const char *)" |..C..... ",
           (const char *)"^...Cg.... ",
           (const char *)" |..CCCC..^",
           (const char *)" C...C..   ",
           (const char *)" CC....  $ ",
           (const char *)" CCCC..  C ",
           (const char *)" .CCCCC..m ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"           ",
           (const char *)" ...|.|..f ",
           (const char *)" CCC...... ",
           (const char *)" |.CCC..b. ",
           (const char *)"^...CCC... ",
           (const char *)" |..CCCC.. ",
           (const char *)" .....CC..^",
           (const char *)" ...m..C.. ",
           (const char *)"           ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"         ^ ",
           (const char *)" ...C..... ",
           (const char *)" ...C..CC. ",
           (const char *)" ..CC.CCCC ",
           (const char *)" CCCC...CC ",
           (const char *)"^...CCC..C ",
           (const char *)" ....C....^",
           (const char *)" $...CC.m. ",
           (const char *)"           ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"   ^       ",
           (const char *)" ......... ",
           (const char *)"^.|CC.CC|. ",
           (const char *)" CCCC.CCC. ",
           (const char *)" .CCCMCCC.^",
           (const char *)" .CCC.CCCC ",
           (const char *)" .|CC.CC|. ",
           (const char *)" ......... ",
           (const char *)"    C.C    ",
           (const char *)"     ^     ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)" g..C.C... ",
           (const char *)" ...C.CC.. ",
           (const char *)" ..CC.CCC. ",
           (const char *)"^..CC.CC.. ",
           (const char *)" CCCC.CCC. ",
           (const char *)" ...C.CC.. ",
           (const char *)" CC....... ",
           (const char *)" .C        ",
           (const char *)" .......$  ",
           (const char *)"  .......$ ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"    ^      ",
           (const char *)"  .....    ",
           (const char *)" .......   ",
           (const char *)" |..C....| ",
           (const char *)"^...Cg....^",
           (const char *)" |..CCC..| ",
           (const char *)"   ..CC..  ",
           (const char *)"$$  ... s  ",
           (const char *)"s       .  ",
           (const char *)"..... .sC  ",
           (const char *)"..m ... .  ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"     ^     ",
           (const char *)"   ....... ",
           (const char *)"  .....C.. ",
           (const char *)" ...C.CCC. ",
           (const char *)" ...C..CC. ",
           (const char *)" ...CCCC.. ",
           (const char *)" s ...CC.  ",
           (const char *)" . ....... ",
           (const char *)" .       . ",
           (const char *)" ..$   g.g ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"     ^     ",
           (const char *)"  ......   ",
           (const char *)" ..|...|.  ",
           (const char *)" ...CCC..  ",
           (const char *)" ..CCCCg..^",
           (const char *)"^...CCC..  ",
           (const char *)" |.......| ",
           (const char *)"     s     ",
           (const char *)"    $..    ",
           (const char *)"    ..M    ",
           (const char *)"  .......  ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"   ^       ",
           (const char *)" ....|...  ",
           (const char *)"^..|g..|.. ",
           (const char *)" ......... ",
           (const char *)" .|..f..|.^",
           (const char *)" ......... ",
           (const char *)" ..|..g|.. ",
           (const char *)"  ...|...  ",
           (const char *)"    ...    ",
           (const char *)"     ^     ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"  ... ...  ",
           (const char *)" .... .... ",
           (const char *)"^.... .... ",
           (const char *)" ....t.... ",
           (const char *)" .... .... ",
           (const char *)" .... ....^",
           (const char *)" ..m. ...$ ",
           (const char *)"           ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"  ........ ",
           (const char *)" m..... .. ",
           (const char *)" ...... .. ",
           (const char *)"    .g.  .^",
           (const char *)" ......... ",
           (const char *)"^....... s ",
           (const char *)" ......  $ ",
           (const char *)"         . ",
           (const char *)" ........m ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"           ",
           (const char *)" ... ....m ",
           (const char *)" ... ...b. ",
           (const char *)" ... .....^",
           (const char *)" ...    .. ",
           (const char *)" ......... ",
           (const char *)"^......... ",
           (const char *)" ...m..... ",
           (const char *)"           ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"           ",
           (const char *)" .......bb ",
           (const char *)" .b.. .... ",
           (const char *)"^.... .... ",
           (const char *)"      .... ",
           (const char *)" ......... ",
           (const char *)" .........^",
           (const char *)" $......m. ",
           (const char *)"           ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"   ^       ",
           (const char *)"  .......  ",
           (const char *)"^..|g..... ",
           (const char *)" ......... ",
           (const char *)" ....f..|.^",
           (const char *)" ......... ",
           (const char *)" .....g|.. ",
           (const char *)"  ...|...  ",
           (const char *)"    ...    ",
           (const char *)"     ^     ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"  .......  ",
           (const char *)" ...|.|... ",
           (const char *)" ......... ",
           (const char *)" ...C.C... ",
           (const char *)" ...CtC... ",
           (const char *)" ...C.C... ",
           (const char *)"  .m.....$ ",
           (const char *)"      ^    ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"  ........ ",
           (const char *)" ......  . ",
           (const char *)" |...... . ",
           (const char *)" ....g.... ",
           (const char *)" |........^",
           (const char *)" .......   ",
           (const char *)" ......  $ ",
           (const char *)" ......  . ",
           (const char *)" ........m ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"           ",
           (const char *)" ...|.|..f ",
           (const char *)" ......... ",
           (const char *)" |.. . .b. ",
           (const char *)" ......... ",
           (const char *)" |.. . ... ",
           (const char *)" .........^",
           (const char *)" ...m..... ",
           (const char *)"           ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"  ........ ",
           (const char *)" ....... .^",
           (const char *)" ...... .. ",
           (const char *)" ..... ... ",
           (const char *)" .... .... ",
           (const char *)"^... ..... ",
           (const char *)" $......m. ",
           (const char *)"           ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"   ^       ",
           (const char *)" ......... ",
           (const char *)"^.|.....|. ",
           (const char *)" ......... ",
           (const char *)" ....M....^",
           (const char *)" ......... ",
           (const char *)" .|.....|. ",
           (const char *)" ......... ",
           (const char *)"    C.C    ",
           (const char *)"     ^     ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)" g..C.C... ",
           (const char *)" ...C.CC.. ",
           (const char *)" ..CC.CCC. ",
           (const char *)"^..CCtCC.. ",
           (const char *)" CCCC.CCC. ",
           (const char *)" ...C.CC..^",
           (const char *)" CC....... ",
           (const char *)" .C        ",
           (const char *)" .......$  ",
           (const char *)"  .......$ ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"  .....    ",
           (const char *)" .......   ",
           (const char *)" |..C....| ",
           (const char *)"^...Cg....^",
           (const char *)" |..CCC..| ",
           (const char *)"   ..CC..  ",
           (const char *)"    ...    ",
           (const char *)"      ^    ",
           (const char *)"           ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"     ^     ",
           (const char *)"   ....... ",
           (const char *)"  .....  . ",
           (const char *)" ....... . ",
           (const char *)" ......... ",
           (const char *)"^......... ",
           (const char *)" s ......  ",
           (const char *)" . ....... ",
           (const char *)" .       . ",
           (const char *)" ..$   g.g ",
           (const char *)"        ^  ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"     ^     ",
           (const char *)"  ......   ",
           (const char *)" ..|...|.  ",
           (const char *)" ........  ",
           (const char *)" ......g..^",
           (const char *)"^........  ",
           (const char *)" |.......| ",
           (const char *)"     s     ",
           (const char *)"    $..    ",
           (const char *)"    ..M    ",
           (const char *)"  .......  ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)" .C....... ",
           (const char *)"^.C..k..T. ",
           (const char *)" .C....... ",
           (const char *)" .CCCC.... ",
           (const char *)" ....C.... ",
           (const char *)" ..CGC.... ",
           (const char *)" ..===.... ",
           (const char *)" ..CGC.... ",
           (const char *)" ..CCCCC.. ",
           (const char *)" ......C..^",
           (const char *)" T.....C.. ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)" ^         ",
           (const char *)".....C...G ",
           (const char *)".....C.... ",
           (const char *)"...CCC.... ",
           (const char *)"...C....T. ",
           (const char *)"...C.k.... ",
           (const char *)"...C...... ",
           (const char *)"...CCCCC.. ",
           (const char *)".....G.C.. ",
           (const char *)"...T...C.. ",
           (const char *)".......C..^",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"         ^ ",
           (const char *)" ........G ",
           (const char *)" ....k.... ",
           (const char *)" ......... ",
           (const char *)" CCCCCC... ",
           (const char *)"^.....C... ",
           (const char *)" ....CCC.. ",
           (const char *)" ....=C=.. ",
           (const char *)" .T..CCC.. ",
           (const char *)" .....C... ",
           (const char *)" G....C...^",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"        ^  ",
           (const char *)" .C.k..C.. ",
           (const char *)" .C....C.. ",
           (const char *)"^.CCCCCC.g ",
           (const char *)" ..C...CCC ",
           (const char *)" ..C.CCC.. ",
           (const char *)" ..C.C...C ",
           (const char *)" ..CCCCCCC ",
           (const char *)" ....C..CC ",
           (const char *)" g...C....^",
           (const char *)"   ^       ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"   ^       ",
           (const char *)" ......... ",
           (const char *)" CC....... ",
           (const char *)" CCCCCC...^",
           (const char *)" .Cg..C... ",
           (const char *)" .C.k.C... ",
           (const char *)" .C..gC... ",
           (const char *)" .CCCCCC.. ",
           (const char *)"^.....CC.. ",
           (const char *)" ......... ",
           (const char *)"        ^  ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)" .L.....L. ",
           (const char *)"^.L..k.... ",
           (const char *)" .L....L.. ",
           (const char *)" ..LLLL... ",
           (const char *)" ....L..L. ",
           (const char *)" .LLGLLL.. ",
           (const char *)" ......... ",
           (const char *)" ..LGL.LL. ",
           (const char *)" .LLLLLLL. ",
           (const char *)" LL...LL..^",
           (const char *)" ...LLLL.. ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)" ^         ",
           (const char *)"..LLLLL..G ",
           (const char *)".....L.... ",
           (const char *)"....L..... ",
           (const char *)"...L...... ",
           (const char *)"...L.k.... ",
           (const char *)"...L...... ",
           (const char *)"....LLL... ",
           (const char *)".....G.L.. ",
           (const char *)".......L.. ",
           (const char *)".......L..^",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"         ^ ",
           (const char *)" L.......G ",
           (const char *)" LL..k..T. ",
           (const char *)" LL..LLL.. ",
           (const char *)" LLLLLLL.. ",
           (const char *)"^.LL..LLLL ",
           (const char *)" ..LLLLLL. ",
           (const char *)" .....L... ",
           (const char *)" ..LLLLLL. ",
           (const char *)" ...LLL... ",
           (const char *)" G....L...^",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"        ^  ",
           (const char *)" .L.k..L.. ",
           (const char *)" .L....L.. ",
           (const char *)"^.LL...L.g ",
           (const char *)" ..L...LLL ",
           (const char *)" ..L.LLL.. ",
           (const char *)" ..LLLLL.L ",
           (const char *)" ..LLLLLLL ",
           (const char *)" ....L..LL ",
           (const char *)" g...L....^",
           (const char *)"   ^       ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"   ^       ",
           (const char *)" ......LL. ",
           (const char *)" LL...LLL. ",
           (const char *)" LLLLLLL..^",
           (const char *)" LLg..LLL. ",
           (const char *)" .L.k.L... ",
           (const char *)" LL..gLLLL ",
           (const char *)" LLLLLLL.. ",
           (const char *)"^.L..LLL.. ",
           (const char *)" ...LLL... ",
           (const char *)"        ^  ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)" .C.....C. ",
           (const char *)"^.C..kCC.. ",
           (const char *)" .C..CCC.. ",
           (const char *)" .CCCCC... ",
           (const char *)" ....C.... ",
           (const char *)" .CCGCCCC. ",
           (const char *)" .=======. ",
           (const char *)" .CCGCCCC. ",
           (const char *)" .CCCCCCC. ",
           (const char *)" CC...CC..^",
           (const char *)" ...CCCC.. ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)" ^         ",
           (const char *)".....C...G ",
           (const char *)".....C...C ",
           (const char *)"....CCCCCC ",
           (const char *)"C..C.....C ",
           (const char *)"CCCC.k.... ",
           (const char *)"...C...... ",
           (const char *)"....CCC... ",
           (const char *)".....G.C.. ",
           (const char *)".......C.. ",
           (const char *)"......CCC.^",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"         ^ ",
           (const char *)" C.......G ",
           (const char *)" CC..k..T. ",
           (const char *)" CC..CCC.. ",
           (const char *)" CCCCCCC.. ",
           (const char *)"^.CC..CCCC ",
           (const char *)" ....CCCC. ",
           (const char *)" ....=C=.. ",
           (const char *)" ...CCCC.. ",
           (const char *)" ..CCCC... ",
           (const char *)" G....C...^",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"        ^  ",
           (const char *)" .C.k..C.. ",
           (const char *)" .C....C.. ",
           (const char *)"^.CC...C.g ",
           (const char *)" ..C...CCC ",
           (const char *)" ..C.CCC.. ",
           (const char *)" ..CCCCC.C ",
           (const char *)" ..=====.C ",
           (const char *)" ..CCCCCCC ",
           (const char *)" g..CCCCC.^",
           (const char *)"   ^       ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"   ^       ",
           (const char *)" ......CC. ",
           (const char *)" CC...CCC. ",
           (const char *)" CCCCCCC..^",
           (const char *)" CCg..CCC. ",
           (const char *)" .C.k.C... ",
           (const char *)" CC..gCCCC ",
           (const char *)" CCCCCCC.. ",
           (const char *)"^.C..CCC.. ",
           (const char *)" ...CCC... ",
           (const char *)"        ^  ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)" .C....... ",
           (const char *)"^.C..k.... ",
           (const char *)" .C....... ",
           (const char *)" .CCCC.... ",
           (const char *)" ....C.... ",
           (const char *)" ..CGC.... ",
           (const char *)" ..===.... ",
           (const char *)" ..CGC.... ",
           (const char *)" ..CCCCC.. ",
           (const char *)" ......C..^",
           (const char *)" ......C.. ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)" ^         ",
           (const char *)".....C...G ",
           (const char *)".....C.... ",
           (const char *)"...CCC.... ",
           (const char *)"...C...... ",
           (const char *)"...C.k.... ",
           (const char *)"...C...... ",
           (const char *)"...CCCCC.. ",
           (const char *)".....G.C.. ",
           (const char *)".......C.. ",
           (const char *)".......C..^",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"         ^ ",
           (const char *)" ........G ",
           (const char *)" ....k..T. ",
           (const char *)" ......... ",
           (const char *)" CCCCCC... ",
           (const char *)"^.....C... ",
           (const char *)" ....CCC.. ",
           (const char *)" ....=C=.. ",
           (const char *)" ....CCC.. ",
           (const char *)" .....C... ",
           (const char *)" G....C...^",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"        ^  ",
           (const char *)" .C.k..C.. ",
           (const char *)" .C....C.. ",
           (const char *)"^.CCCCCC.g ",
           (const char *)" ..C...CCC ",
           (const char *)" ..C.CCC.. ",
           (const char *)" ..C.C...C ",
           (const char *)" ..CCCCCCC ",
           (const char *)" ....C..CC ",
           (const char *)" g...C....^",
           (const char *)"   ^       ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"   ^       ",
           (const char *)" ......... ",
           (const char *)" CC....... ",
           (const char *)" CCCCCC...^",
           (const char *)" .Cg..C... ",
           (const char *)" .C.k.C... ",
           (const char *)" .C..gC... ",
           (const char *)" .CCCCCC.. ",
           (const char *)"^.....CC.. ",
           (const char *)" ......... ",
           (const char *)"        ^  ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"  ..=CC.kg ",
           (const char *)" ...=CC... ",
           (const char *)" ...=CCCCC ",
           (const char *)" ====CCC   ",
           (const char *)" CCCCC.... ",
           (const char *)" C..m.C... ",
           (const char *)" CC...C..C ",
           (const char *)"       ^   ",
           (const char *)"           ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"  ........ ",
           (const char *)" ...CCCC.. ",
           (const char *)" ..CCCCCC. ",
           (const char *)" ..CC.gCC.^",
           (const char *)" ..CCk.CC. ",
           (const char *)" ..CCCCCC. ",
           (const char *)" g........ ",
           (const char *)" .       . ",
           (const char *)" .CC$CC... ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"  ^        ",
           (const char *)" ..C..g.C. ",
           (const char *)" ..Ck..CC. ",
           (const char *)" ..CCCCC.. ",
           (const char *)" ..CCCCC.. ",
           (const char *)" ...CCC... ",
           (const char *)" ...C.C...^",
           (const char *)"     s     ",
           (const char *)" ....C.... ",
           (const char *)" ......... ",
           (const char *)" g...T...$ ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"  C=CCC..g ",
           (const char *)" CC=CCC.k. ",
           (const char *)" CC=CCC... ",
           (const char *)" ===CCCCCC ",
           (const char *)" CCCCCCCCC ",
           (const char *)"^......... ",
           (const char *)" C.......C ",
           (const char *)"   CC.CC   ",
           (const char *)"    C.C  . ",
           (const char *)"    |g|..$ ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"^.....CC.k ",
           (const char *)" ....CCC.. ",
           (const char *)" ...CCCCCC ",
           (const char *)" CCC.CCCCC ",
           (const char *)" ......CC. ",
           (const char *)" ......C.g ",
           (const char *)"  ....C..$ ",
           (const char *)"     .     ",
           (const char *)"     .     ",
           (const char *)"     ^     ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"    CCCC   ",
           (const char *)" CCCCCCCCC ",
           (const char *)"^=========^",
           (const char *)" CCCCCCCCC ",
           (const char *)"  CCCC..CC ",
           (const char *)"    CCk.CC ",
           (const char *)"    CC..C  ",
           (const char *)"     C..   ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"   CCC     ",
           (const char *)"  CCCCCC   ",
           (const char *)" CCC...CCC ",
           (const char *)"^===.k.CCC ",
           (const char *)" CCC...===^",
           (const char *)"  CCCC=CCC ",
           (const char *)"   CCC=CC  ",
           (const char *)"    CC=C   ",
           (const char *)"     C=C   ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"    .T.    ",
           (const char *)"   C...C   ",
           (const char *)"  CCk..CC  ",
           (const char *)" CCCCCCCCC ",
           (const char *)"^=========^",
           (const char *)" CCCCCCCCC ",
           (const char *)"  CCCCCCC  ",
           (const char *)"      ..   ",
           (const char *)"      .$   ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"           ",
           (const char *)" CCCCCC... ",
           (const char *)" CCCCCC.k. ",
           (const char *)" CCCCCCCCC ",
           (const char *)"^=========^",
           (const char *)" CCCCCCCCC ",
           (const char *)" CCCCCCCCC ",
           (const char *)" CCCCCCCCC ",
           (const char *)"           ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"         ^ ",
           (const char *)"^...CCCC.. ",
           (const char *)" ...====.. ",
           (const char *)" ...CCCC.. ",
           (const char *)" ....CCCCC ",
           (const char *)" ......CC.^",
           (const char *)" ......C.g ",
           (const char *)"  ....C.k$ ",
           (const char *)"           ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"  ..=C...g ",
           (const char *)" ...=C.... ",
           (const char *)" ...=Ck... ",
           (const char *)" ====C..   ",
           (const char *)" CCCCC.... ",
           (const char *)" L..m.L... ",
           (const char *)" LL...L..L ",
           (const char *)"       ^   ",
           (const char *)"           ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"  T....... ",
           (const char *)"^......... ",
           (const char *)" ...CCC... ",
           (const char *)" ...C.CC.. ",
           (const char *)" ...Ck.C.. ",
           (const char *)" ...CCCC.. ",
           (const char *)" g........^",
           (const char *)" .       . ",
           (const char *)" .CC$CC... ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)" ..C....C. ",
           (const char *)" ..Ck..CC. ",
           (const char *)" ..CCCCC.. ",
           (const char *)" .........^",
           (const char *)" ...CCC... ",
           (const char *)"^...C.C... ",
           (const char *)"     s     ",
           (const char *)" ....C.... ",
           (const char *)" ......... ",
           (const char *)" g.......$ ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"       ^   ",
           (const char *)"  C=C.C..g ",
           (const char *)" CC=CCC.k. ",
           (const char *)" CC=CCC...^",
           (const char *)"^===C.CCCC ",
           (const char *)" CCCC..C.. ",
           (const char *)" ......... ",
           (const char *)" C.......C ",
           (const char *)"   CC.CC   ",
           (const char *)"    C.C  . ",
           (const char *)"    |g|..$ ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"        ^  ",
           (const char *)"^.....LL.k ",
           (const char *)" ....L.L.. ",
           (const char *)" ...L..LLL ",
           (const char *)" LLL.m...L ",
           (const char *)" .......L. ",
           (const char *)" ......L.. ",
           (const char *)"  ....L..$ ",
           (const char *)"     .     ",
           (const char *)"     .     ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"  .......g ",
           (const char *)" ......... ",
           (const char *)" |....k... ",
           (const char *)" ...CCCC..^",
           (const char *)" |.CCCCCC. ",
           (const char *)" ...m.CCC. ",
           (const char *)" B........ ",
           (const char *)"       ^   ",
           (const char *)"           ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"   ^       ",
           (const char *)"  |.|...Bf ",
           (const char *)" ........B ",
           (const char *)"^...CCC... ",
           (const char *)" ...C.CC.. ",
           (const char *)" ...Ck.C.. ",
           (const char *)" ...CCCC.. ",
           (const char *)" g........ ",
           (const char *)" .       . ",
           (const char *)" .CC$CC... ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"  ^        ",
           (const char *)" ..CCC$.C. ",
           (const char *)" ..CCCCCC. ",
           (const char *)" ..CCCCC.. ",
           (const char *)" ......CC. ",
           (const char *)" .....CC..^",
           (const char *)" .....C... ",
           (const char *)" .....CC.. ",
           (const char *)" B   .CCC. ",
           (const char *)" .   .CCC. ",
           (const char *)" gk  ....$ ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"   ^       ",
           (const char *)"  ...CC..g ",
           (const char *)" ....CC...^",
           (const char *)" ....CC..$ ",
           (const char *)"^.....CCCC ",
           (const char *)" ......CCC ",
           (const char *)"  .......  ",
           (const char *)"    C.C    ",
           (const char *)"    C.C    ",
           (const char *)"    C.C  k ",
           (const char *)"    CgC..$ ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"   ^       ",
           (const char *)" $.. .CC.k ",
           (const char *)" ... ..C.. ",
           (const char *)" ... ..CCC ",
           (const char *)" LLL m...C ",
           (const char *)" ... ...C.^",
           (const char *)" ......C.. ",
           (const char *)" B.......$ ",
           (const char *)"   ^       ",
           (const char *)"           ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"   LLL...g ",
           (const char *)"   LL..... ",
           (const char *)"   LL.LLLL ",
           (const char *)" ...L.kL.. ",
           (const char *)"   .LLLL.. ",
           (const char *)"   ....... ",
           (const char *)"   ...B.B  ",
           (const char *)"       ^   ",
           (const char *)"           ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"  ......B  ",
           (const char *)" .........^",
           (const char *)" ...CCC... ",
           (const char *)" ...CgCC.. ",
           (const char *)" .  C..C.. ",
           (const char *)" .  C..C.. ",
           (const char *)" t  C..C.. ",
           (const char *)" .  C..CC. ",
           (const char *)" $  C..kCC ",
           (const char *)"     ^     ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"      ^    ",
           (const char *)" ......... ",
           (const char *)" .CCCCCCC. ",
           (const char *)" .C.....C. ",
           (const char *)" .C.CCC.C. ",
           (const char *)" .C.Ck..C. ",
           (const char *)" .C.CCCCC. ",
           (const char *)" .C.......^",
           (const char *)"^........B ",
           (const char *)" CCC   CCC ",
           (const char *)" g.......$ ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"   ^       ",
           (const char *)" .m..C.C.C ",
           (const char *)" .....C.Ck ",
           (const char *)" ....C.C.C ",
           (const char *)" ...C.C.C. ",
           (const char *)" ....C.C.. ",
           (const char *)" .....C..m ",
           (const char *)" .T....... ",
           (const char *)" ........$ ",
           (const char *)"      ^    ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"   ^       ",
           (const char *)"   .CCCCCC ",
           (const char *)"   .CCC.kC ",
           (const char *)"   .CCC..C ",
           (const char *)"   .CCCCCC ",
           (const char *)"   .CCm.C  ",
           (const char *)"   ..C..C  ",
           (const char *)" CCC..CCC  ",
           (const char *)" m.C...... ",
           (const char *)" $.C....m. ",
           (const char *)"     ^     ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"   B...LLL ",
           (const char *)"   .....LL ",
           (const char *)"   ......L ",
           (const char *)"^.....g..L ",
           (const char *)"   .......^",
           (const char *)"   ....... ",
           (const char *)" LL......B ",
           (const char *)"LLkLL  .   ",
           (const char *)"LLLL   .   ",
           (const char *)"LL     ^   ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"  .......  ",
           (const char *)" CCCCCCB..^",
           (const char *)" ......... ",
           (const char *)" ..BCCCCCC ",
           (const char *)"  ........ ",
           (const char *)"   CCCCCB.^",
           (const char *)"  ........ ",
           (const char *)"  ..BCCCCC ",
           (const char *)" ^......gk ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)" ...CkC... ",
           (const char *)" .|CCCCCC. ",
           (const char *)" .CCCCCCg. ",
           (const char *)"^.=======.^",
           (const char *)" .CCCCCCC. ",
           (const char *)" .gCCCCCC. ",
           (const char *)" .CCCCCC|. ",
           (const char *)" .....CC.. ",
           (const char *)"           ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"   ^       ",
           (const char *)" B...C.C.C ",
           (const char *)" .....C.C. ",
           (const char *)" ....C.C.C ",
           (const char *)" ...C.CkC. ",
           (const char *)" ....C.C.. ",
           (const char *)" .....C... ",
           (const char *)" B......$. ",
           (const char *)" .B.......^",
           (const char *)"           ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"   ^       ",
           (const char *)"   .CCCCCC ",
           (const char *)"   .CCC.kC ",
           (const char *)"   .CCC..C ",
           (const char *)"   .CCCCCC ",
           (const char *)"   .CC..C  ",
           (const char *)"   ..C.mC  ",
           (const char *)" CCC..CCC  ",
           (const char *)" f.B......^",
           (const char *)" ..B...... ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"   .....LL ",
           (const char *)"   ......L ",
           (const char *)"   ....... ",
           (const char *)"^.....g... ",
           (const char *)"   .......^",
           (const char *)"  L....... ",
           (const char *)" LL....... ",
           (const char *)" LkLL  .   ",
           (const char *)" LLL   .   ",
           (const char *)"       ^   ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"  .......  ",
           (const char *)" LLLLLLL.. ",
           (const char *)" ......... ",
           (const char *)" ..LLLLLLL ",
           (const char *)"  ........ ",
           (const char *)"   LLLLLL.^",
           (const char *)"  ........ ",
           (const char *)"  ..LLLLLL ",
           (const char *)"  ......gk ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"  ^        ",
           (const char *)" ...LkL... ",
           (const char *)" ..LLgLL.. ",
           (const char *)" .LLL.LLL. ",
           (const char *)" .LLL.LLL.^",
           (const char *)" .LLL.LLL. ",
           (const char *)" .LLL.LLL. ",
           (const char *)" ..LL.LL.. ",
           (const char *)" ......... ",
           (const char *)"    ^      ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"   ^       ",
           (const char *)"  .....L.L ",
           (const char *)" .......L. ",
           (const char *)" ....L.LkL ",
           (const char *)" ...L...L. ",
           (const char *)" ....L....^",
           (const char *)" .....L... ",
           (const char *)"  ........ ",
           (const char *)"   ......$ ",
           (const char *)"           ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)" ^         ",
           (const char *)"^.....LLLL ",
           (const char *)" L...LL.kL ",
           (const char *)" LL.LLL..L ",
           (const char *)" LL.LLL.LL ",
           (const char *)" LLLLL..L  ",
           (const char *)" .L..L..L  ",
           (const char *)" .LL....L  ",
           (const char *)" ..L...... ",
           (const char *)" L........^",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"   ^       ",
           (const char *)"   .....LL ",
           (const char *)"   ......L ",
           (const char *)"   ....... ",
           (const char *)"^.g....... ",
           (const char *)"   .......^",
           (const char *)"   ....... ",
           (const char *)" LLL...... ",
           (const char *)" LkLLLL.   ",
           (const char *)" .....g.   ",
           (const char *)"       ^   ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"  .......  ",
           (const char *)" LLLLLLL.. ",
           (const char *)" ..L...... ",
           (const char *)" ..LLL.LLL ",
           (const char *)"  ...L.... ",
           (const char *)"   LLL.LL.^",
           (const char *)"  .....L.. ",
           (const char *)"  ..LLLLLL ",
           (const char *)"  ......gk ",
           (const char *)"   ^       ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)" ...LkL... ",
           (const char *)" ..LLgLL.. ",
           (const char *)" .LL...LL. ",
           (const char *)" ......LL. ",
           (const char *)" .LL......^",
           (const char *)" .LL...LL. ",
           (const char *)" ..LLgLL.. ",
           (const char *)" ......... ",
           (const char *)"  ^        ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"   ^       ",
           (const char *)"  .....L.L ",
           (const char *)" .......Lk ",
           (const char *)" ....L.L.L ",
           (const char *)" ...L.g.L. ",
           (const char *)" ....L.... ",
           (const char *)" .....L... ",
           (const char *)"  ........ ",
           (const char *)"   ......$ ",
           (const char *)"      ^    ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"   ^       ",
           (const char *)" .....LLLL ",
           (const char *)" ....LL.kL ",
           (const char *)" L..LLL..L ",
           (const char *)" L..LL...L ",
           (const char *)" LLLL...L  ",
           (const char *)" .L.....L  ",
           (const char *)" .LL....L  ",
           (const char *)" ..LL..... ",
           (const char *)" ...LL.... ",
           (const char *)"  ^        ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"   ^       ",
           (const char *)"   .....CC ",
           (const char *)"   ......C ",
           (const char *)"   .....C. ",
           (const char *)"^.g....C.. ",
           (const char *)"   ....C..^",
           (const char *)"   ...C... ",
           (const char *)" CCC.CC... ",
           (const char *)" CkCCCC.   ",
           (const char *)" .....g.   ",
           (const char *)"       ^   ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"  .......  ",
           (const char *)" CCCCCCC.. ",
           (const char *)" ..CC..... ",
           (const char *)" ..CCC.CCC ",
           (const char *)"  ..CC.... ",
           (const char *)"   CCC.CC.^",
           (const char *)"  .....C.. ",
           (const char *)"  ..CCCCCC ",
           (const char *)"  ......gk ",
           (const char *)"   ^       ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)" ...CkC... ",
           (const char *)" ..CCgCC.. ",
           (const char *)" .CC...CC. ",
           (const char *)" .C....CC. ",
           (const char *)" .CC....C.^",
           (const char *)" .CC...CC. ",
           (const char *)" ..CCgCC.. ",
           (const char *)" ...C.C... ",
           (const char *)"  ^        ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"   ^       ",
           (const char *)"  ...CCCCC ",
           (const char *)" ......CCk ",
           (const char *)" ....CCCCC ",
           (const char *)" ...CCg.CC ",
           (const char *)" ....C.... ",
           (const char *)" ...C.CCCC ",
           (const char *)"  ...C.... ",
           (const char *)"   .C....$ ",
           (const char *)"      ^    ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"   ^       ",
           (const char *)" .....CCCC ",
           (const char *)" ....CC.kC ",
           (const char *)" C..CCC..C ",
           (const char *)" C..CC...C ",
           (const char *)" CCCC...C  ",
           (const char *)" .C.....C  ",
           (const char *)" .CC....C  ",
           (const char *)" ..CC..... ",
           (const char *)" ...CC.... ",
           (const char *)"  ^        ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"   ....... ",
           (const char *)"   ....... ",
           (const char *)"   ....... ",
           (const char *)"^.....g... ",
           (const char *)"   .......^",
           (const char *)"   ....... ",
           (const char *)" ..B...... ",
           (const char *)" .k.   .   ",
           (const char *)" ... $ .   ",
           (const char *)"       ^   ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"  ....C..  ",
           (const char *)" .....C... ",
           (const char *)" .....CC.. ",
           (const char *)" ......C.. ",
           (const char *)"  .....CC. ",
           (const char *)"   .....C.^",
           (const char *)"  ......C. ",
           (const char *)"  ........ ",
           (const char *)"  ......gk ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)" CC..k.... ",
           (const char *)" C...g.... ",
           (const char *)" ......... ",
           (const char *)" ......... ",
           (const char *)" ......... ",
           (const char *)" ......... ",
           (const char *)" ........  ",
           (const char *)" .......   ",
           (const char *)"  ^        ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"   ^       ",
           (const char *)"  ...C.... ",
           (const char *)" ....C..k. ",
           (const char *)" ....C.... ",
           (const char *)" ....CCCCC ",
           (const char *)" ......... ",
           (const char *)" ......... ",
           (const char *)"  ........ ",
           (const char *)"   ......$ ",
           (const char *)"       ^   ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"  ........ ",
           (const char *)" .......k. ",
           (const char *)" ......... ",
           (const char *)" ......... ",
           (const char *)" ........  ",
           (const char *)" ........  ",
           (const char *)" ........  ",
           (const char *)" ......... ",
           (const char *)" .........^",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"   ....... ",
           (const char *)"   ..CCCCC ",
           (const char *)"   ..Cg..C ",
           (const char *)"^.t..CkC.C ",
           (const char *)"   ..CCC.C^",
           (const char *)"   ......C ",
           (const char *)" ..CCCCCCC ",
           (const char *)" .k.   .   ",
           (const char *)" ...   .   ",
           (const char *)"       ^   ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"  ^        ",
           (const char *)"  .......  ",
           (const char *)" ......... ",
           (const char *)" ......... ",
           (const char *)" ....C.... ",
           (const char *)"  ..CCC... ",
           (const char *)"   ..C....^",
           (const char *)"  ........ ",
           (const char *)"  .......g ",
           (const char *)"  ......gk ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)" ^         ",
           (const char *)" ...CkC... ",
           (const char *)" ....g.... ",
           (const char *)" ......... ",
           (const char *)" ......... ",
           (const char *)" ....C.... ",
           (const char *)" ....CC... ",
           (const char *)" .....CC.. ",
           (const char *)" .........^",
           (const char *)"           ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"   ^       ",
           (const char *)"  .... .CC ",
           (const char *)" ..... ... ",
           (const char *)" ..... k.. ",
           (const char *)" ..... CgC ",
           (const char *)" ......... ",
           (const char *)" ......... ",
           (const char *)"  ........^",
           (const char *)"   ......$ ",
           (const char *)"           ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)" ^         ",
           (const char *)" ..... ...^",
           (const char *)" ..... .k. ",
           (const char *)" ..... ... ",
           (const char *)" ..... ... ",
           (const char *)" ..... ..  ",
           (const char *)" ..... ..  ",
           (const char *)" ..... ..  ",
           (const char *)" ..... ... ",
           (const char *)" ......... ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"      .....",
           (const char *)"^...  .   .",
           (const char *)"   .      .",
           (const char *)"...... ....",
           (const char *)".    . w  w",
           (const char *)".  ... w  w",
           (const char *)"   .   w  w",
           (const char *)"  ....ww ww",
           (const char *)"...  .   w ",
           (const char *)"  .  .ww w^",
           (const char *)".....M     ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"....   ....",
           (const char *)".  .www.  .",
           (const char *)".  . w .  .",
           (const char *)".  . w ....",
           (const char *)"     w  w  ",
           (const char *)"^wwwww  w.^",
           (const char *)"     w  w  ",
           (const char *)".... .  ...",
           (const char *)".  . .    .",
           (const char *)".    .ww...",
           (const char *)"......     ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"....   ....",
           (const char *)".  .www..$.",
           (const char *)".  . w ....",
           (const char *)".... w ....",
           (const char *)"     w  w  ",
           (const char *)"^wwwww  w  ",
           (const char *)"     w  w  ",
           (const char *)"......  ..^",
           (const char *)"..LLL.  M. ",
           (const char *)".LLL..ww.. ",
           (const char *)"......  ^  ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"....   ...M",
           (const char *)".w..www.  .",
           (const char *)"..w. w .  .",
           (const char *)".... w ....",
           (const char *)"     w  w  ",
           (const char *)"^wwwww  w.^",
           (const char *)"     s  s  ",
           (const char *)"......  ...",
           (const char *)"..M.ww  ...",
           (const char *)"..wwwwww..$",
           (const char *)".wwwww     ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"...M   ^   ",
           (const char *)".LL.sww....",
           (const char *)".LL. w .  .",
           (const char *)"$... w ....",
           (const char *)"     w  w  ",
           (const char *)"^wwwww  w.^",
           (const char *)"     s  w  ",
           (const char *)" .....  ...",
           (const char *)"^.LLL.  ...",
           (const char *)" .LLL.ww...",
           (const char *)" ...L.  ^  ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"....   ....",
           (const char *)".M..www....",
           (const char *)".... w ....",
           (const char *)".... w ....",
           (const char *)"     w  w  ",
           (const char *)"     w  w.^",
           (const char *)"     w  w  ",
           (const char *)"......  ...",
           (const char *)"......  ...",
           (const char *)"......ww...",
           (const char *)"......     ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"....   ....",
           (const char *)".M..www....",
           (const char *)".... w ....",
           (const char *)".... w ....",
           (const char *)"     w  w  ",
           (const char *)"^wwwww  wt^",
           (const char *)"     w  w  ",
           (const char *)"......  ...",
           (const char *)"......  ...",
           (const char *)"......ww...",
           (const char *)"......     ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"....   ....",
           (const char *)".M..www....",
           (const char *)".... w ....",
           (const char *)".... w ....",
           (const char *)"     w  w  ",
           (const char *)"^wwwww  w.^",
           (const char *)"     w  w  ",
           (const char *)"......  ...",
           (const char *)"......  ...",
           (const char *)"......ww...",
           (const char *)"......  ^  ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"....   ....",
           (const char *)".M..www....",
           (const char *)".... w ....",
           (const char *)".... w ....",
           (const char *)"     w  w  ",
           (const char *)"^wwwww  w.^",
           (const char *)"     s  s  ",
           (const char *)"......  ...",
           (const char *)"..M...  ...",
           (const char *)"......ww..$",
           (const char *)"......     ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"....   ^   ",
           (const char *)".M..www....",
           (const char *)".... w ....",
           (const char *)".... w ....",
           (const char *)"     w  w  ",
           (const char *)"^wwwww  w.^",
           (const char *)"     w  w  ",
           (const char *)" .....  ...",
           (const char *)"^.....  ...",
           (const char *)" .....ww...",
           (const char *)" .....  ^  ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"....   ....",
           (const char *)".T..CCC..T.",
           (const char *)".... C ....",
           (const char *)".... C ....",
           (const char *)"     C  C  ",
           (const char *)"     C  C.^",
           (const char *)"     C  C. ",
           (const char *)"......  ...",
           (const char *)"....T.  .T.",
           (const char *)"......CC...",
           (const char *)"......     ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"....   ....",
           (const char *)".T..CCC....",
           (const char *)".... C ....",
           (const char *)".... C ....",
           (const char *)"     C  C  ",
           (const char *)"^CCCCC  C.^",
           (const char *)"     C  C. ",
           (const char *)"......  ...",
           (const char *)"......  ..T",
           (const char *)".T....CC...",
           (const char *)"......     ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"....   ....",
           (const char *)".T..CCC....",
           (const char *)".... C ..T.",
           (const char *)".... C ....",
           (const char *)"     C  C  ",
           (const char *)"^CCCCC  Ct^",
           (const char *)"     C  C. ",
           (const char *)"......  ...",
           (const char *)"......  ...",
           (const char *)"......CC...",
           (const char *)"......  ^  ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"....   ....",
           (const char *)".T..CCC..T.",
           (const char *)".... C ....",
           (const char *)".... C ....",
           (const char *)"     C  C  ",
           (const char *)"^CCCCC  C.^",
           (const char *)"     s  s. ",
           (const char *)"......  ...",
           (const char *)"..T...  ...",
           (const char *)"......CC.T$",
           (const char *)"......     ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"....   ^   ",
           (const char *)".T..CCC....",
           (const char *)".... C ..T.",
           (const char *)".... C ....",
           (const char *)"     C  C  ",
           (const char *)"^CCCCC  C.^",
           (const char *)"     C  C. ",
           (const char *)" .....  ...",
           (const char *)"^...T.  .T.",
           (const char *)" .....CC...",
           (const char *)" .....  ^  ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"....   ....",
           (const char *)".M..www....",
           (const char *)".... w ....",
           (const char *)".... w ....",
           (const char *)"     w  w  ",
           (const char *)"     w  w.^",
           (const char *)"     w  w  ",
           (const char *)"......  ...",
           (const char *)". ....  ...",
           (const char *)".... .ww...",
           (const char *)"......     ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"....   ....",
           (const char *)".M..www....",
           (const char *)".... w ....",
           (const char *)".... w ....",
           (const char *)"     w  w  ",
           (const char *)"^wwwww  w.^",
           (const char *)"     w  w  ",
           (const char *)"......  ...",
           (const char *)". ....  ...",
           (const char *)"......ww...",
           (const char *)"......     ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"....   ....",
           (const char *)".M..www....",
           (const char *)".... w ....",
           (const char *)".... w ....",
           (const char *)"     w  w  ",
           (const char *)"^wwwww  w.^",
           (const char *)"     w  w  ",
           (const char *)"......  ...",
           (const char *)"......  ...",
           (const char *)"......ww...",
           (const char *)"......  ^  ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"....   ....",
           (const char *)".M..www....",
           (const char *)".... w .. .",
           (const char *)".... w ....",
           (const char *)"     w  w  ",
           (const char *)"^wwwww  w.^",
           (const char *)"     s  s  ",
           (const char *)"......  ...",
           (const char *)"..M...  ...",
           (const char *)"......ww..$",
           (const char *)"......     ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"....   ^   ",
           (const char *)".M..www....",
           (const char *)".... w ....",
           (const char *)".... w ....",
           (const char *)"     w  w  ",
           (const char *)"^wwwww  w.^",
           (const char *)"     w  w  ",
           (const char *)" .....  ...",
           (const char *)"^... .  ...",
           (const char *)" .....ww...",
           (const char *)" .....  ^  ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"....   ...$",
           (const char *)".M..'''.LL.",
           (const char *)".... ' .LL.",
           (const char *)".... ' ....",
           (const char *)"     '  '  ",
           (const char *)"     '  '.^",
           (const char *)"     '  '  ",
           (const char *)"......  ...",
           (const char *)". ....  ...",
           (const char *)".... .''...",
           (const char *)"......     ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"....   ....",
           (const char *)".M..'''....",
           (const char *)".... ' ....",
           (const char *)".... ' ....",
           (const char *)"     '  '  ",
           (const char *)"^'''''  '.^",
           (const char *)"     '  '  ",
           (const char *)"......  ...",
           (const char *)". ....  ...",
           (const char *)"......''...",
           (const char *)"......     ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"....   ....",
           (const char *)".M..'''....",
           (const char *)".... ' ....",
           (const char *)".... ' ....",
           (const char *)"     '  '  ",
           (const char *)"^''''t  '.^",
           (const char *)"     '  '  ",
           (const char *)"......  ...",
           (const char *)"......  ...",
           (const char *)"......''...",
           (const char *)"......  ^  ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"....   ....",
           (const char *)".M..'''....",
           (const char *)".... ' .. .",
           (const char *)".... ' ....",
           (const char *)"     '  '  ",
           (const char *)"^'''''  '.^",
           (const char *)"     s  s  ",
           (const char *)"......  ...",
           (const char *)"..M...  ...",
           (const char *)"......''..$",
           (const char *)"......     ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"....   ^   ",
           (const char *)".M..'''....",
           (const char *)".... ' ....",
           (const char *)".... ' ....",
           (const char *)"     '  '  ",
           (const char *)"^'''''  '.^",
           (const char *)"     '  '  ",
           (const char *)" .....  ...",
           (const char *)"^... .  .L.",
           (const char *)" .....''...",
           (const char *)" .....  ^  ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"  ^        ",
           (const char *)"^..        ",
           (const char *)" ...       ",
           (const char *)"  ..m      ",
           (const char *)"   ... ... ",
           (const char *)"   ...s..$ ",
           (const char *)"   ... ... ",
           (const char *)"    ...    ",
           (const char *)"     ...   ",
           (const char *)"      .... ",
           (const char *)"         ^ ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"  ^        ",
           (const char *)" ..        ",
           (const char *)" ..        ",
           (const char *)"^..        ",
           (const char *)" .m        ",
           (const char *)" .........^",
           (const char *)" ...       ",
           (const char *)"  ...      ",
           (const char *)"   ...     ",
           (const char *)"    ...    ",
           (const char *)"      ^    ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"       ^   ",
           (const char *)" ..    .   ",
           (const char *)"  ..   .   ",
           (const char *)"   ..  .   ",
           (const char *)"    ...t..^",
           (const char *)"     ..    ",
           (const char *)"     ..    ",
           (const char *)" ......    ",
           (const char *)" ..m..     ",
           (const char *)" ....      ",
           (const char *)" ^         ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"    ^      ",
           (const char *)"    ..     ",
           (const char *)"^......    ",
           (const char *)"    ....   ",
           (const char *)"    .m...  ",
           (const char *)"   .......^",
           (const char *)"   ..  ..  ",
           (const char *)"   ..  ..  ",
           (const char *)"   ..  ..  ",
           (const char *)"   ......  ",
           (const char *)"     ^     ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)" ^         ",
           (const char *)" ....      ",
           (const char *)"    .      ",
           (const char *)"    .      ",
           (const char *)"   ..m...  ",
           (const char *)"^...    .  ",
           (const char *)"   .    ..^",
           (const char *)"   ......  ",
           (const char *)"    .      ",
           (const char *)"    .      ",
           (const char *)"    ^      ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"  .......  ",
           (const char *)"  .$..M..  ",
           (const char *)"  ...|s|. $",
           (const char *)"      w   .",
           (const char *)"      ws..s",
           (const char *)"^..   s   .",
           (const char *)"  .....   m",
           (const char *)"  w....    ",
           (const char *)"  ww....   ",
           (const char *)"       ... ",
           (const char *)"         ^ ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"  ^   $.m. ",
           (const char *)"  .   .... ",
           (const char *)"  .   .... ",
           (const char *)"  .   ..T. ",
           (const char *)"  .        ",
           (const char *)"  .        ",
           (const char *)"  ...      ",
           (const char *)"  .w.C..T  ",
           (const char *)"  ...      ",
           (const char *)"    ...    ",
           (const char *)"      ^    ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"       ^   ",
           (const char *)"       .   ",
           (const char *)"       .   ",
           (const char *)"       t   ",
           (const char *)"       .   ",
           (const char *)"^...   t   ",
           (const char *)" .w.   .   ",
           (const char *)" .w.....   ",
           (const char *)" ..m.      ",
           (const char *)" ....      ",
           (const char *)" ^         ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"    ^      ",
           (const char *)"    .      ",
           (const char *)"    .      ",
           (const char *)"    .      ",
           (const char *)"    .      ",
           (const char *)"    .      ",
           (const char *)"^......    ",
           (const char *)"   .ww...^ ",
           (const char *)"   ..w.    ",
           (const char *)"   ....    ",
           (const char *)"     ^     ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"           ",
           (const char *)" ^         ",
           (const char *)" ..        ",
           (const char *)"  ....     ",
           (const char *)"  .ww....^ ",
           (const char *)"  ....     ",
           (const char *)"    .      ",
           (const char *)"    ^      ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"       ....",
           (const char *)"       $...",
           (const char *)"       ....",
           (const char *)"       s   ",
           (const char *)"       w   ",
           (const char *)"^..    w   ",
           (const char *)"  .....s   ",
           (const char *)"  L....    ",
           (const char *)"  LL....   ",
           (const char *)"       ... ",
           (const char *)"         ^ ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"  ^        ",
           (const char *)"  .   ...$ ",
           (const char *)"  ... .... ",
           (const char *)"  .T. T..m ",
           (const char *)"  ...      ",
           (const char *)"    ...    ",
           (const char *)"      ^    ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"       ^   ",
           (const char *)"^...   .   ",
           (const char *)" .L.   .   ",
           (const char *)" .L.....   ",
           (const char *)" ..m.      ",
           (const char *)" ....      ",
           (const char *)" ^         ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"    ^      ",
           (const char *)"    .      ",
           (const char *)"^......    ",
           (const char *)"   .LL...^ ",
           (const char *)"   ..L.    ",
           (const char *)"   ....    ",
           (const char *)"     ^     ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"           ",
           (const char *)" ^         ",
           (const char *)" ..        ",
           (const char *)"  ....     ",
           (const char *)"  .LL....^ ",
           (const char *)"  ....     ",
           (const char *)"    .      ",
           (const char *)"    ^      ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"^..        ",
           (const char *)"  .....    ",
           (const char *)"  C....    ",
           (const char *)"  CC....   ",
           (const char *)"       ... ",
           (const char *)"         ^ ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"  ^        ",
           (const char *)"  .        ",
           (const char *)"  ...      ",
           (const char *)"  .C.      ",
           (const char *)"  ...      ",
           (const char *)"    ...    ",
           (const char *)"      ^    ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"       ^   ",
           (const char *)"^...   .   ",
           (const char *)" .C.   .   ",
           (const char *)" .C.....   ",
           (const char *)" ..m.      ",
           (const char *)" ....      ",
           (const char *)" ^         ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"    ^      ",
           (const char *)"    .      ",
           (const char *)"^......    ",
           (const char *)"   .CC...^ ",
           (const char *)"   ..C.    ",
           (const char *)"   ....    ",
           (const char *)"     ^     ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"           ",
           (const char *)" ^         ",
           (const char *)" ..        ",
           (const char *)"  ....     ",
           (const char *)"  .CC....^ ",
           (const char *)"  ....     ",
           (const char *)"    .      ",
           (const char *)"    ^      ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)" ^         ",
           (const char *)"C..C       ",
           (const char *)" ...C      ",
           (const char *)" C..mCC    ",
           (const char *)" CC...CC   ",
           (const char *)" CC...CC   ",
           (const char *)" CC...CC   ",
           (const char *)"  CC...C   ",
           (const char *)"    C...C  ",
           (const char *)"     C...C ",
           (const char *)"         ^ ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"  ^        ",
           (const char *)" ..C       ",
           (const char *)" ..C       ",
           (const char *)" ..C       ",
           (const char *)" .mCCCCCCC ",
           (const char *)" .........^",
           (const char *)" ...CCCCCC ",
           (const char *)" C...C     ",
           (const char *)"  C...C    ",
           (const char *)"   C...C   ",
           (const char *)"      ^    ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"       ^   ",
           (const char *)" ..   C.C  ",
           (const char *)"  ..  C.C  ",
           (const char *)"   ..CC.C  ",
           (const char *)"   C......^",
           (const char *)"    C..CC  ",
           (const char *)"     ..    ",
           (const char *)" ......    ",
           (const char *)" ..m..     ",
           (const char *)" ....      ",
           (const char *)" ^         ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"    ^      ",
           (const char *)"    ..     ",
           (const char *)"^......    ",
           (const char *)"    ....   ",
           (const char *)"    .m...  ",
           (const char *)"   .......^",
           (const char *)"   ..CC..  ",
           (const char *)"   ..CC..  ",
           (const char *)"   ..CC..  ",
           (const char *)"   ......  ",
           (const char *)"     ^     ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)" ^         ",
           (const char *)" ....      ",
           (const char *)"    .      ",
           (const char *)"    .      ",
           (const char *)"   ..m...  ",
           (const char *)"^...CCCC.  ",
           (const char *)"   .CCCC..^",
           (const char *)"   ......  ",
           (const char *)"    .      ",
           (const char *)"    .      ",
           (const char *)"    ^      ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"       ^   ",
           (const char *)"  ......   ",
           (const char *)"  .        ",
           (const char *)"C..C       ",
           (const char *)" ...C      ",
           (const char *)" C..mCC    ",
           (const char *)"    C...C  ",
           (const char *)"     C...C ",
           (const char *)"         ^ ",
           (const char *)"           ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"        ^  ",
           (const char *)"  ....  .  ",
           (const char *)"  .  .  .  ",
           (const char *)" ..C ....  ",
           (const char *)" ..C       ",
           (const char *)"^..C       ",
           (const char *)"  C...C    ",
           (const char *)"   C...C   ",
           (const char *)"      ^    ",
           (const char *)"           ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"       ^   ",
           (const char *)" ..   C.C  ",
           (const char *)"  ..  C.C  ",
           (const char *)"   ..CC.C  ",
           (const char *)" ..m..     ",
           (const char *)" ....^     ",
           (const char *)" ^         ",
           (const char *)"           ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"    ^      ",
           (const char *)"    ..     ",
           (const char *)"^......    ",
           (const char *)"    ....   ",
           (const char *)"   ..CC..  ",
           (const char *)"   ......^ ",
           (const char *)"     ^     ",
           (const char *)"           ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"           ",
           (const char *)" ^         ",
           (const char *)" ....^     ",
           (const char *)"    .      ",
           (const char *)"    .      ",
           (const char *)"    .      ",
           (const char *)"    .      ",
           (const char *)"    ^      ",
           (const char *)"           ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"   ^       ",
           (const char *)"^...       ",
           (const char *)" CC..      ",
           (const char *)" CCC=CC    ",
           (const char *)" CCC=CCC   ",
           (const char *)" CCC=CCC   ",
           (const char *)" CCC=CCC   ",
           (const char *)"  CC=CCC   ",
           (const char *)"   C=CCCC  ",
           (const char *)"   C=CCCCC ",
           (const char *)"   CCCCC.^ ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"  ^        ",
           (const char *)" C=C       ",
           (const char *)" C=C       ",
           (const char *)" C=CCC.... ",
           (const char *)" C=CCC...m ",
           (const char *)" C=CCC.... ",
           (const char *)" C=CCC..$. ",
           (const char *)" C=CCCs    ",
           (const char *)" C=CCCs    ",
           (const char *)" ......    ",
           (const char *)"      ^    ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"       ^   ",
           (const char *)"     CC=CC ",
           (const char *)"     CC=CC ",
           (const char *)"    CCC=CCC",
           (const char *)"    C.....C",
           (const char *)"    C.....C",
           (const char *)"    CCC=CCC",
           (const char *)"     CC=CC ",
           (const char *)"     CC=CC ",
           (const char *)"     CC=CC ",
           (const char *)"       ^   ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"    ^      ",
           (const char *)"  CC=CC    ",
           (const char *)"  CC=CC    ",
           (const char *)"  CC=CC    ",
           (const char *)"  CC=CC    ",
           (const char *)"   .......^",
           (const char *)"   ..CC..  ",
           (const char *)"   ..CC..  ",
           (const char *)"   ..CC..  ",
           (const char *)"   ......  ",
           (const char *)"     ^     ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)" ^         ",
           (const char *)" ....      ",
           (const char *)"   C=C     ",
           (const char *)"   C=C     ",
           (const char *)"   C=C...  ",
           (const char *)"^....CCC.  ",
           (const char *)"   ....C..^",
           (const char *)"   ......  ",
           (const char *)"    .      ",
           (const char *)"    .      ",
           (const char *)"    ^      ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"  ^        ",
           (const char *)"w..w       ",
           (const char *)" ...w      ",
           (const char *)" w...ww    ",
           (const char *)" ww...ww   ",
           (const char *)" wwt.mww   ",
           (const char *)" ww.t.ww   ",
           (const char *)"  ww...w   ",
           (const char *)"    w...w  ",
           (const char *)"     w...w ",
           (const char *)"         ^ ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"  ^        ",
           (const char *)" ..w       ",
           (const char *)" ..w       ",
           (const char *)" ..w       ",
           (const char *)" ..wwwwwww ",
           (const char *)" .....m...^",
           (const char *)" ...wwwwww ",
           (const char *)" w...w     ",
           (const char *)"  w...w    ",
           (const char *)"   w...w   ",
           (const char *)"      ^    ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"       ^   ",
           (const char *)" ..   w.w  ",
           (const char *)"  m.  w.w  ",
           (const char *)"   ..ww.w  ",
           (const char *)"   w......^",
           (const char *)"    w..ww  ",
           (const char *)"     ..    ",
           (const char *)" ......    ",
           (const char *)" .....     ",
           (const char *)" ....      ",
           (const char *)" ^         ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"    ^      ",
           (const char *)"    ..     ",
           (const char *)"^......    ",
           (const char *)"    ....   ",
           (const char *)"    ..m..  ",
           (const char *)"   .......^",
           (const char *)"   ..ww..  ",
           (const char *)"   ..ww..  ",
           (const char *)"   ..ww..  ",
           (const char *)"   ......  ",
           (const char *)"     ^     ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)" ^         ",
           (const char *)" ....      ",
           (const char *)"    .      ",
           (const char *)"    .      ",
           (const char *)"   ......  ",
           (const char *)"^...wwww.  ",
           (const char *)"   .wwww..^",
           (const char *)"   .m....  ",
           (const char *)"    .      ",
           (const char *)"    .      ",
           (const char *)"    ^      ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"   ^       ",
           (const char *)"....       ",
           (const char *)" .m..      ",
           (const char *)" ......    ",
           (const char *)" ..CCC..CCC",
           (const char *)" ..CCC..CCC",
           (const char *)" ..CCC.tCCC",
           (const char *)"  ......   ",
           (const char *)"    .....  ",
           (const char *)"     ..... ",
           (const char *)"         ^ ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"  ^        ",
           (const char *)" ...CC     ",
           (const char *)" m..CCC    ",
           (const char *)" ...CCCC   ",
           (const char *)" ......... ",
           (const char *)" CCCCCCCCC^",
           (const char *)" ......... ",
           (const char *)" .....     ",
           (const char *)"  .....    ",
           (const char *)"   .....   ",
           (const char *)"      ^    ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"       ^   ",
           (const char *)" ..   ...  ",
           (const char *)" C..  ...  ",
           (const char *)" CC......  ",
           (const char *)" CC...m...^",
           (const char *)" CCC.....  ",
           (const char *)" CCCC..    ",
           (const char *)" ......    ",
           (const char *)" .....     ",
           (const char *)" ....      ",
           (const char *)" ^         ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"    ^      ",
           (const char *)" CCC..     ",
           (const char *)"^......    ",
           (const char *)" CCC....   ",
           (const char *)"   C.....  ",
           (const char *)"   .......^",
           (const char *)"   .m....  ",
           (const char *)"   .CCCC.  ",
           (const char *)"   .CCCC.  ",
           (const char *)"   ......  ",
           (const char *)"     ^     ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)" ^         ",
           (const char *)" ....C     ",
           (const char *)"   C.C     ",
           (const char *)"  CC.C     ",
           (const char *)"  C......  ",
           (const char *)"^...CCCC.  ",
           (const char *)"   .CCCC..^",
           (const char *)"   .m....C ",
           (const char *)"    .CCCCC ",
           (const char *)"    .      ",
           (const char *)"    ^      ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"  ^        ",
           (const char *)" ...       ",
           (const char *)"^....      ",
           (const char *)" ......    ",
           (const char *)" ........C.",
           (const char *)" ..m.....C.",
           (const char *)" ........C.",
           (const char *)"  ......   ",
           (const char *)"    .....  ",
           (const char *)"     ..... ",
           (const char *)"         ^ ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"  ^        ",
           (const char *)" .....     ",
           (const char *)" .C....    ",
           (const char *)" CCC....   ",
           (const char *)" .C...|... ",
           (const char *)" .C.....m.^",
           (const char *)" .C...|... ",
           (const char *)" .....     ",
           (const char *)"  .....    ",
           (const char *)"   .....   ",
           (const char *)"      ^    ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"       ^   ",
           (const char *)" ..   .m.  ",
           (const char *)" ...  ...  ",
           (const char *)" C.......  ",
           (const char *)" CCCCCCC..^",
           (const char *)" C.......  ",
           (const char *)" ......    ",
           (const char *)" ......    ",
           (const char *)" .....     ",
           (const char *)" ....      ",
           (const char *)" ^         ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"    ^      ",
           (const char *)" .....     ",
           (const char *)"^m.....    ",
           (const char *)" .......   ",
           (const char *)"   .C...|  ",
           (const char *)"   .C.....^",
           (const char *)"   .CC..|  ",
           (const char *)"   .CCC..  ",
           (const char *)"   .CCCC.  ",
           (const char *)"   ......  ",
           (const char *)"     ^     ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)" ^         ",
           (const char *)" .....     ",
           (const char *)"   .C.     ",
           (const char *)"  ..C.     ",
           (const char *)"  ..C....  ",
           (const char *)"^...CCCC.  ",
           (const char *)"   ....C..^",
           (const char *)"   ..m.C.. ",
           (const char *)"    ...... ",
           (const char *)"    .      ",
           (const char *)"    ^      ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"   ^       ",
           (const char *)"   .       ",
           (const char *)"   .       ",
           (const char *)"   .       ",
           (const char *)"^........B ",
           (const char *)" ....C....^",
           (const char *)" ...CC...B ",
           (const char *)"  CCC..... ",
           (const char *)"  ...      ",
           (const char *)"  .m.      ",
           (const char *)"   ^       ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"        ^  ",
           (const char *)" ww..C...B ",
           (const char *)" w...CC... ",
           (const char *)" .....CCCC ",
           (const char *)"^......... ",
           (const char *)" .....ww.. ",
           (const char *)" ...wwww.. ",
           (const char *)" ..wwWwww. ",
           (const char *)" .       . ",
           (const char *)" . f.wWWw. ",
           (const char *)" ..wwmwww. ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)" ...C....  ",
           (const char *)" ...CC.m.. ",
           (const char *)" ....C.... ",
           (const char *)"^....C.... ",
           (const char *)" ....C....^",
           (const char *)"  ...CC... ",
           (const char *)"   ...CC.. ",
           (const char *)"      C    ",
           (const char *)"           ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"   ^       ",
           (const char *)"  |.|..... ",
           (const char *)"  ........ ",
           (const char *)"  ........ ",
           (const char *)"^......... ",
           (const char *)"  ........ ",
           (const char *)"  ........ ",
           (const char *)"     .. CC ",
           (const char *)"     .. CC ",
           (const char *)" .C.... CC.",
           (const char *)" .C.... ..$",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"   ^       ",
           (const char *)" .|.|..... ",
           (const char *)" .........^",
           (const char *)" ......... ",
           (const char *)" ......... ",
           (const char *)" ...m..... ",
           (const char *)" ......... ",
           (const char *)" ......... ",
           (const char *)"      ..   ",
           (const char *)"       ^   ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"  ....w.w. ",
           (const char *)" ...wwwwww ",
           (const char *)" ....wwwww ",
           (const char *)"^....ww..B ",
           (const char *)" ....w.... ",
           (const char *)" ..mwww..B ",
           (const char *)"  ........ ",
           (const char *)"  .f   ^   ",
           (const char *)"           ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"        ^  ",
           (const char *)" ww......B ",
           (const char *)" www...... ",
           (const char *)" .w.w..... ",
           (const char *)"^...www... ",
           (const char *)" ...mwww.. ",
           (const char *)" ...www... ",
           (const char *)" ..ww..... ",
           (const char *)"   ww    . ",
           (const char *)"    ww  f. ",
           (const char *)" $www      ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)" f.ww....  ",
           (const char *)" ...ww.m.. ",
           (const char *)" ..ww ww.. ",
           (const char *)"^..ww ww.. ",
           (const char *)" ...w w... ",
           (const char *)" ...www... ",
           (const char *)" B....ww.. ",
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)" ... ..... ",
           (const char *)" ...  ..f. ",
           (const char *)" .... .... ",
           (const char *)"^.... ..m. ",
           (const char *)" ....L.... ",
           (const char *)" LLLLLL... ",
           (const char *)" ..... ..$ ",
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"   ^       ",
           (const char *)" ...L....f ",
           (const char *)" ...LL.... ",
           (const char *)" ....Lm... ",
           (const char *)" m...L.... ",
           (const char *)"^......... ",
           (const char *)" LLL.LL...^",
           (const char *)" $.....L.. ",
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"  ....     ",
           (const char *)" ......    ",
           (const char *)" ......    ",
           (const char *)" ......    ",
           (const char *)" ......... ",
           (const char *)" ..m.....B ",
           (const char *)"  ....ww.. ",
           (const char *)"      ww   ",
           (const char *)"       w   ",
           (const char *)"       ^   ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"        ^  ",
           (const char *)"  .....B.B ",
           (const char *)"  .CCC.... ",
           (const char *)"  .CCCCC.  ",
           (const char *)" ....C.... ",
           (const char *)" ...mC.... ",
           (const char *)" ......... ",
           (const char *)" ....C.... ",
           (const char *)"   CCCC .. ",
           (const char *)"        f. ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"      ^    ",
           (const char *)" f...C...  ",
           (const char *)" ....C.m.. ",
           (const char *)" ......... ",
           (const char *)" ....C.... ",
           (const char *)" ......... ",
           (const char *)" ....C.... ",
           (const char *)" B...CC... ",
           (const char *)"   CCCCC   ",
           (const char *)"  CCC      ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"     ^     ",
           (const char *)" ...w..... ",
           (const char *)" ...ww..f. ",
           (const char *)" ....w.... ",
           (const char *)" ....w..m. ",
           (const char *)" ...ww.... ",
           (const char *)" wwwwww... ",
           (const char *)" WWWWwww.. ",
           (const char *)"  WWWW     ",
           (const char *)"   WWWW    ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)" ^         ",
           (const char *)" .wwww..   ",
           (const char *)" .wwWw...  ",
           (const char *)" ...wwww.. ",
           (const char *)" m...wwWw. ",
           (const char *)"^...wWWw.. ",
           (const char *)"  ..wwWw.. ",
           (const char *)"   ...wwww ",
           (const char *)"     wwww  ",
           (const char *)"           ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"  ....L.L. ",
           (const char *)" ...LLLLLL ",
           (const char *)" ....LLLLL ",
           (const char *)" ....LL... ",
           (const char *)" ....L.... ",
           (const char *)" ...LLL... ",
           (const char *)"  f....... ",
           (const char *)"       ^   ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"     ^     ",
           (const char *)" LL......  ",
           (const char *)" LLL....f. ",
           (const char *)" .L.L..... ",
           (const char *)" ...LLL... ",
           (const char *)" ....LLL.. ",
           (const char *)" ...LLL...^",
           (const char *)" ..LL..... ",
           (const char *)"           ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"        ^  ",
           (const char *)" ..LL....  ",
           (const char *)" ...LL.m.. ",
           (const char *)" ....L.... ",
           (const char *)" ......... ",
           (const char *)" ....L.... ",
           (const char *)" ...LLL... ",
           (const char *)"  ....LL..^",
           (const char *)"           ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"        ^  ",
           (const char *)" ...L..... ",
           (const char *)" ...LL.... ",
           (const char *)" ....L.... ",
           (const char *)" .......m. ",
           (const char *)" ......... ",
           (const char *)" LLLL.....^",
           (const char *)" .....L..$ ",
           (const char *)"           ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"  ^        ",
           (const char *)" ...L..... ",
           (const char *)" ...LL.... ",
           (const char *)" ..LLLLL..^",
           (const char *)" m.LL.LL.. ",
           (const char *)" ..LL.$L.. ",
           (const char *)" ...LLLLL. ",
           (const char *)" ......... ",
           (const char *)" .f..      ",
           (const char *)" ....      ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"  .......  ",
           (const char *)"  ...   .  ",
           (const char *)"  .m.  f.  ",
           (const char *)" ....      ",
           (const char *)"  ........ ",
           (const char *)"  .....b.. ",
           (const char *)"  B....... ",
           (const char *)"       ^   ",
           (const char *)"           ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"   ...f    ",
           (const char *)"   ..b.    ",
           (const char *)"   B......^",
           (const char *)" ......... ",
           (const char *)" ......L.. ",
           (const char *)" C         ",
           (const char *)" . $...... ",
           (const char *)" .       m ",
           (const char *)"^......... ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"      L    ",
           (const char *)"    LLLL   ",
           (const char *)" .LLLLLLL. ",
           (const char *)"^....m....^",
           (const char *)" .LLLLLLL. ",
           (const char *)"   LLLL    ",
           (const char *)"     L     ",
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)" ....L  $. ",
           (const char *)" ...LL  .. ",
           (const char *)" ...LL  .. ",
           (const char *)"^...LL  .. ",
           (const char *)" .LLLL   . ",
           (const char *)" LLLL.....^",
           (const char *)" LL      . ",
           (const char *)"   ff..... ",
           (const char *)"   ff      ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"  ^        ",
           (const char *)"  ....     ",
           (const char *)"  ..m.     ",
           (const char *)"  f..B     ",
           (const char *)"  C D      ",
           (const char *)"  C ...f   ",
           (const char *)"  C ....^  ",
           (const char *)"  C .m..   ",
           (const char *)"  C    s   ",
           (const char *)"^.$    ... ",
           (const char *)" ..D.ms..$ ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"  ...      ",
           (const char *)"  .m.      ",
           (const char *)"  ...      ",
           (const char *)" ....      ",
           (const char *)"  f....... ",
           (const char *)"    . ..f. ",
           (const char *)" $..s .... ",
           (const char *)" ....  ^   ",
           (const char *)" m...      ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"   ....LLL ",
           (const char *)"   .b..LLL ",
           (const char *)"   ....... ",
           (const char *)"^......... ",
           (const char *)"    |.|  . ",
           (const char *)"     .   C ",
           (const char *)"     s   C ",
           (const char *)"   .....CC ",
           (const char *)"   .....C  ",
           (const char *)"   .$..$   ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"           ",
           (const char *)" .LLLLLLL. ",
           (const char *)"^.........^",
           (const char *)" .LLL.LLL. ",
           (const char *)"     .     ",
           (const char *)"     s     ",
           (const char *)"  C.....C  ",
           (const char *)"  C...$.C  ",
           (const char *)"  CCCCCCC  ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"         ^ ",
           (const char *)"^...LL  .. ",
           (const char *)" ...LLL .. ",
           (const char *)" ......... ",
           (const char *)" ...LL  .. ",
           (const char *)" .LLLL   . ",
           (const char *)" LLLL    . ",
           (const char *)"         . ",
           (const char *)" $L      C ",
           (const char *)" .LLLLL  C ",
           (const char *)" LLLLLL    ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"     ^     ",
           (const char *)"  ....     ",
           (const char *)"  ....     ",
           (const char *)"  ....     ",
           (const char *)"     D     ",
           (const char *)"$.. ...f   ",
           (const char *)"...D....   ",
           (const char *)"... ..m.^  ",
           (const char *)" s         ",
           (const char *)"..... $..  ",
           (const char *)"$.... $..  ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"  ...LLLL. ",
           (const char *)"  ...L.. L ",
           (const char *)"  ...LL..L ",
           (const char *)"^.....LLLL ",
           (const char *)"  ........ ",
           (const char *)"    s  ... ",
           (const char *)" $... .... ",
           (const char *)" .L..  .   ",
           (const char *)" m...  .   ",
           (const char *)"       ^   ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"   ..LLLLL ",
           (const char *)" fC....LLL ",
           (const char *)"   ..L...L ",
           (const char *)"^........f ",
           (const char *)"   .|.|... ",
           (const char *)"     .     ",
           (const char *)"     s     ",
           (const char *)"$L.........",
           (const char *)"LL..L.L..LL",
           (const char *)"...$.m.$.L$",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"   LL      ",
           (const char *)"   LLLL    ",
           (const char *)" .LLLLLLL. ",
           (const char *)"^.........^",
           (const char *)" .LLLLLLL. ",
           (const char *)"   L LLL   ",
           (const char *)"     s     ",
           (const char *)" CC.....   ",
           (const char *)" .......   ",
           (const char *)" m....$.   ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"         ^ ",
           (const char *)" ...LL  f. ",
           (const char *)" ...LL  .. ",
           (const char *)" .....  .. ",
           (const char *)" ...LL  .. ",
           (const char *)" LLLLLL  . ",
           (const char *)" LLLLL.... ",
           (const char *)"    LLL  . ",
           (const char *)" $L .LL  C ",
           (const char *)" .LLLLL  L ",
           (const char *)" LLLLLL    ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)" ^         ",
           (const char *)" .......LL.",
           (const char *)" .......LL$",
           (const char *)" ff.....LL.",
           (const char *)"     D     ",
           (const char *)"..C CCC... ",
           (const char *)"..CD...... ",
           (const char *)"..C ..m... ",
           (const char *)" s    D    ",
           (const char *)".CC.. ..$.^",
           (const char *)"..$.. f$f. ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"  ....C.C. ",
           (const char *)" ...CCCCCC ",
           (const char *)" ....CCCCC ",
           (const char *)" ...CCC... ",
           (const char *)" ...===... ",
           (const char *)" ...CCC... ",
           (const char *)"  f.CCC... ",
           (const char *)"       ^   ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"     ^     ",
           (const char *)" CC......  ",
           (const char *)" CCC....f. ",
           (const char *)" .C.C..... ",
           (const char *)" ...CCC... ",
           (const char *)" ....CCC.. ",
           (const char *)" ...CCC...^",
           (const char *)" ..CC..... ",
           (const char *)"           ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"        ^  ",
           (const char *)" ..CC....  ",
           (const char *)" ...CC.m.. ",
           (const char *)" ....C.... ",
           (const char *)" ......... ",
           (const char *)" ....C.... ",
           (const char *)" ...CCC... ",
           (const char *)"  ....CC..^",
           (const char *)"           ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"        ^  ",
           (const char *)" ...C..... ",
           (const char *)" ...CC.... ",
           (const char *)" ....C.... ",
           (const char *)" .......m. ",
           (const char *)" ......... ",
           (const char *)" CCCC.....^",
           (const char *)" .....C..$ ",
           (const char *)"           ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"  ^        ",
           (const char *)" ...C..... ",
           (const char *)" ...CC.... ",
           (const char *)" ..CCCCC..^",
           (const char *)" m.CC.CC.. ",
           (const char *)" ..CC.$C.. ",
           (const char *)" ...CCCCC. ",
           (const char *)" ......... ",
           (const char *)" .f..      ",
           (const char *)" ....      ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"  .......  ",
           (const char *)"  ...   .  ",
           (const char *)"  .m.  f.  ",
           (const char *)" ....      ",
           (const char *)"  ........ ",
           (const char *)"  .....b.. ",
           (const char *)"  B....... ",
           (const char *)"       ^   ",
           (const char *)"           ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"   ...f    ",
           (const char *)"   ..b.    ",
           (const char *)"   B......^",
           (const char *)" ......... ",
           (const char *)" ......C.. ",
           (const char *)" C         ",
           (const char *)" . $...... ",
           (const char *)" .       m ",
           (const char *)"^......... ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"      C    ",
           (const char *)"    C C  C ",
           (const char *)"    CCCCCC ",
           (const char *)" .CCCCCCCC ",
           (const char *)"^....m....^",
           (const char *)" CCCCCCCCC ",
           (const char *)" CCCCCCCCC ",
           (const char *)" CC CCCC C ",
           (const char *)"  C  CCC   ",
           (const char *)"     CC    ",
           (const char *)"     C     ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)" ....C  $. ",
           (const char *)" ...CC  .. ",
           (const char *)" ...CC  .. ",
           (const char *)"^...CC  .. ",
           (const char *)" .CCCC   . ",
           (const char *)" CCCC.....^",
           (const char *)" CC      . ",
           (const char *)"   ff..... ",
           (const char *)"   ff      ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"  ^        ",
           (const char *)"  ....     ",
           (const char *)"  ..m.     ",
           (const char *)" .f..B     ",
           (const char *)"C.C D      ",
           (const char *)"C=C ...f   ",
           (const char *)"C=C ....^  ",
           (const char *)"C=C .m..   ",
           (const char *)"C.C    s   ",
           (const char *)"^..    ... ",
           (const char *)" ..D.ms..$ ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"  ...      ",
           (const char *)"  .m.      ",
           (const char *)"  ...      ",
           (const char *)" ....      ",
           (const char *)"  f....... ",
           (const char *)"    . ..f. ",
           (const char *)" $..s .... ",
           (const char *)" ....  ^   ",
           (const char *)" m...      ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"   ....CCC ",
           (const char *)"   .b..CCC ",
           (const char *)"   ....... ",
           (const char *)"^......... ",
           (const char *)"    |.|  . ",
           (const char *)"     .   C ",
           (const char *)"     s   C ",
           (const char *)"   .....CC ",
           (const char *)"   .....C  ",
           (const char *)"   .$..$   ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"           ",
           (const char *)" .CCCCCCC. ",
           (const char *)"^.........^",
           (const char *)" .CCC.CCC. ",
           (const char *)"     .     ",
           (const char *)"     s     ",
           (const char *)"  C.....C  ",
           (const char *)"  C...$.C  ",
           (const char *)"  CCCCCCC  ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"         ^ ",
           (const char *)"^...CC  .. ",
           (const char *)" ...CCC .. ",
           (const char *)" ......... ",
           (const char *)" ...CC  .. ",
           (const char *)" .CCCC   . ",
           (const char *)" CCCC    . ",
           (const char *)"         . ",
           (const char *)" $C      C ",
           (const char *)" .CCCCC  C ",
           (const char *)" CCCCCC    ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"     ^     ",
           (const char *)"  ....     ",
           (const char *)"  ....     ",
           (const char *)"  ....     ",
           (const char *)"     D     ",
           (const char *)"$.. ...f   ",
           (const char *)"...D....   ",
           (const char *)"... ..m.^  ",
           (const char *)" s         ",
           (const char *)"..... $..  ",
           (const char *)"$.... $..  ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"  ...CCCC. ",
           (const char *)"  ...C.. C ",
           (const char *)"  ...CC..C ",
           (const char *)"^.....CCCC ",
           (const char *)"  ........ ",
           (const char *)"    s  ... ",
           (const char *)" $... .... ",
           (const char *)" .C..  .   ",
           (const char *)" m...  .   ",
           (const char *)"       ^   ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"   ..CCCCC ",
           (const char *)" fC....CCC ",
           (const char *)"   ..C...C ",
           (const char *)"^........f ",
           (const char *)"   .|.|... ",
           (const char *)"     .     ",
           (const char *)"     s     ",
           (const char *)"$C.........",
           (const char *)"CC..C.C..CC",
           (const char *)"...$.m.$.C$",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"   CC      ",
           (const char *)"   CCCC    ",
           (const char *)" .CCCCCCC. ",
           (const char *)"^.........^",
           (const char *)" .CCCCCCC. ",
           (const char *)"   C CCC   ",
           (const char *)"     s     ",
           (const char *)" CC.....   ",
           (const char *)" .......   ",
           (const char *)" m....$.   ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"         ^ ",
           (const char *)" ...CC  f. ",
           (const char *)" ...CC  .. ",
           (const char *)" .....  .. ",
           (const char *)" ...CC  .. ",
           (const char *)" CCCCCC  . ",
           (const char *)" CCCCC.... ",
           (const char *)"    CCC  . ",
           (const char *)" $C .CC  C ",
           (const char *)" .CCCCC  C ",
           (const char *)" CCCCCC    ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)" ^         ",
           (const char *)" .......CC.",
           (const char *)" .......CC$",
           (const char *)" ff.....CC.",
           (const char *)"     D     ",
           (const char *)"..C CCC... ",
           (const char *)"..CD...... ",
           (const char *)"..C ..m... ",
           (const char *)" s    D    ",
           (const char *)".CC.. ..$.^",
           (const char *)"..$.. f$f. ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"  ....w.w. ",
           (const char *)" f..wwwwww ",
           (const char *)" ....wwwww ",
           (const char *)" ....ww..B ",
           (const char *)" ....w.... ",
           (const char *)" ..mwww..B ",
           (const char *)"  ........^",
           (const char *)"       ^   ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"        ^  ",
           (const char *)" ww......B ",
           (const char *)" www...... ",
           (const char *)" .w.w..... ",
           (const char *)" ...www... ",
           (const char *)" ...mwww.. ",
           (const char *)" ...www...^",
           (const char *)" ..ww...f. ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"           ",
           (const char *)" ..ww....  ",
           (const char *)" f..ww.m.. ",
           (const char *)" ....w.... ",
           (const char *)" ....w.... ",
           (const char *)" ....w.... ",
           (const char *)" ...www...^",
           (const char *)" B....ww.. ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"           ",
           (const char *)" ...C.....^",
           (const char *)" ...CC..f. ",
           (const char *)" ....C.... ",
           (const char *)" ....C..m. ",
           (const char *)" ....C.... ",
           (const char *)" CCCCCC... ",
           (const char *)" .....C..$ ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"       ^   ",
           (const char *)" ...C....f ",
           (const char *)" ...CC.... ",
           (const char *)" ....Cm...^",
           (const char *)" m...C.... ",
           (const char *)"^......... ",
           (const char *)" CCC.CC... ",
           (const char *)" $.....C.. ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"  ....w.w. ",
           (const char *)" f..wwwwww ",
           (const char *)" ....w.... ",
           (const char *)" ..mwww..B ",
           (const char *)"  ........^",
           (const char *)"       ^   ",
           (const char *)"           ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"        ^  ",
           (const char *)" ww......B ",
           (const char *)" www...... ",
           (const char *)" ...mwww.. ",
           (const char *)" ...www...^",
           (const char *)" ..ww...f. ",
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"           ",
           (const char *)" ^         ",
           (const char *)" ..ww....  ",
           (const char *)" f..ww.m.. ",
           (const char *)" ....w.... ",
           (const char *)" ...www... ",
           (const char *)" B....ww.. ",
           (const char *)"         ^ ",
           (const char *)"           ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"           ",
           (const char *)" ...C.....^",
           (const char *)" ...CC..f. ",
           (const char *)" ....C.... ",
           (const char *)" CCCCCC... ",
           (const char *)"^.....C..$ ",
           (const char *)" ^         ",
           (const char *)"           ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"       ^   ",
           (const char *)" ...C....f ",
           (const char *)" ...CC.... ",
           (const char *)"^......... ",
           (const char *)" CCC.CC... ",
           (const char *)" $.....C.. ",
           (const char *)"         ^ ",
           (const char *)"           ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"  ....C.C. ",
           (const char *)" ...CCCCCC ",
           (const char *)" ....CCCCC ",
           (const char *)" ....CC... ",
           (const char *)" ....C..f. ",
           (const char *)" ...CCC... ",
           (const char *)"  ........ ",
           (const char *)"       ^   ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"           ",
           (const char *)" CC....... ",
           (const char *)" CCC...f.. ",
           (const char *)" .C.C..... ",
           (const char *)" ...CCC...^",
           (const char *)" ....CCC.. ",
           (const char *)" ...CCC... ",
           (const char *)"^..CC..... ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"           ",
           (const char *)" ^         ",
           (const char *)" ..CC....f ",
           (const char *)" ...CC.m..^",
           (const char *)" ....C.... ",
           (const char *)" ...CCC... ",
           (const char *)" ....C.... ",
           (const char *)" ...CCC... ",
           (const char *)"  ....CC.. ",
           (const char *)"        ^  ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"           ",
           (const char *)" ...C..... ",
           (const char *)"^...CC..f. ",
           (const char *)" ....C.... ",
           (const char *)" .......m. ",
           (const char *)" .........^",
           (const char *)" CCCCCC... ",
           (const char *)" .....C..$ ",
           (const char *)"    ^      ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"      ^    ",
           (const char *)" ...C...f. ",
           (const char *)" ...CC.... ",
           (const char *)" ..CCCCC.. ",
           (const char *)" m.CC.CC.. ",
           (const char *)" ..CC.$C.. ",
           (const char *)"^...CCCCC. ",
           (const char *)"  ....C...^",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"  ...      ",
           (const char *)"  ...      ",
           (const char *)"  .m.      ",
           (const char *)" ....      ",
           (const char *)"  ........ ",
           (const char *)"  .....b.. ",
           (const char *)"  B.f.....^",
           (const char *)"       ^   ",
           (const char *)"           ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"   ....    ",
           (const char *)"   ..b.    ",
           (const char *)"   B.....f ",
           (const char *)" ......... ",
           (const char *)" ......C..^",
           (const char *)" C         ",
           (const char *)" . $...... ",
           (const char *)" .       m ",
           (const char *)" ......... ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"           ",
           (const char *)" .CCCCCCC. ",
           (const char *)"^....m....^",
           (const char *)" .CCCCCCC. ",
           (const char *)"   CCCCC   ",
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)" ^         ",
           (const char *)" ...CC  $. ",
           (const char *)" ...CC  .. ",
           (const char *)" ...CC  .. ",
           (const char *)" ...CC  .. ",
           (const char *)" CCCCC   .^",
           (const char *)" CCCC..... ",
           (const char *)" CC        ",
           (const char *)"  C      f ",
           (const char *)"           ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"  ^        ",
           (const char *)"  ....     ",
           (const char *)"  ..m.     ",
           (const char *)"  f..B     ",
           (const char *)"    D      ",
           (const char *)"    ......^",
           (const char *)"    ....   ",
           (const char *)"    .m..   ",
           (const char *)"       D   ",
           (const char *)" .$    ... ",
           (const char *)" ..s.mD..$ ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"  f.. .... ",
           (const char *)"  .m.s.... ",
           (const char *)"  ... ...$ ",
           (const char *)" ..        ",
           (const char *)" ..s......^",
           (const char *)"    . ..f. ",
           (const char *)" $..s .... ",
           (const char *)" ....  ^   ",
           (const char *)" m...      ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"   f...CCC ",
           (const char *)"   .b..CCC ",
           (const char *)"   ....... ",
           (const char *)"^......... ",
           (const char *)"    |.|  .^",
           (const char *)"     .     ",
           (const char *)"     s     ",
           (const char *)"   m....   ",
           (const char *)"   ..m..   ",
           (const char *)"   ....$   ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"           ",
           (const char *)" .CCCCCCC. ",
           (const char *)"^.........^",
           (const char *)" .CCC.CCC. ",
           (const char *)"     .     ",
           (const char *)"     D     ",
           (const char *)"  C.....C  ",
           (const char *)"  C.m.$.C  ",
           (const char *)"  CCCCCCC  ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"         ^ ",
           (const char *)" ...CC  f.^",
           (const char *)" ...CC  .. ",
           (const char *)" ......... ",
           (const char *)" ...CC  .. ",
           (const char *)" CCCCC   . ",
           (const char *)" CCCC    . ",
           (const char *)"         . ",
           (const char *)" $C      C ",
           (const char *)" .CCCCC  C ",
           (const char *)" CCCCCC    ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"  ^        ",
           (const char *)"  ....  ..^",
           (const char *)"  ....D..m ",
           (const char *)"  ....  .. ",
           (const char *)"     D     ",
           (const char *)"$.. ...f   ",
           (const char *)"...D.... f ",
           (const char *)"... ..m. f ",
           (const char *)" s         ",
           (const char *)"..... $..  ",
           (const char *)"$...$ $..  ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"  ...CCCCC ",
           (const char *)"  ...C...C ",
           (const char *)"  ...C...C ",
           (const char *)" ....CCCCC ",
           (const char *)"  ........ ",
           (const char *)"    s  ... ",
           (const char *)" .... .... ",
           (const char *)" .C..  .   ",
           (const char *)" m..$  .   ",
           (const char *)"       ^   ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"   ....CCC ",
           (const char *)" fC....CCC ",
           (const char *)"   ....... ",
           (const char *)"^......... ",
           (const char *)"   .|.|...^",
           (const char *)"     .     ",
           (const char *)"     s     ",
           (const char *)"   .....   ",
           (const char *)"   .C.C.   ",
           (const char *)"   $.m.$   ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"           ",
           (const char *)" .CCCCCCC. ",
           (const char *)"^.........^",
           (const char *)" .CCCCCCC. ",
           (const char *)"     C     ",
           (const char *)"     .     ",
           (const char *)" CC.....   ",
           (const char *)"   .....   ",
           (const char *)"   .....   ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)" ^         ",
           (const char *)" ...CC  .. ",
           (const char *)" ...CC  .. ",
           (const char *)" .....  .. ",
           (const char *)" ...CC  .. ",
           (const char *)" CCCCCC... ",
           (const char *)" CCCCC.  . ",
           (const char *)"    CCC  . ",
           (const char *)" $C .CC  C ",
           (const char *)" .CCCCC  C ",
           (const char *)" CCCCCC    ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"      ^    ",
           (const char *)" .......   ",
           (const char *)" .......   ",
           (const char *)" .f.....   ",
           (const char *)"     D     ",
           (const char *)"..C CCC... ",
           (const char *)"..CD...... ",
           (const char *)"..C ..m... ",
           (const char *)" s    s    ",
           (const char *)".CC.. ..$. ",
           (const char *)"...$. f$f. ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"  ....w.w. ",
           (const char *)" ...wwwwww ",
           (const char *)" ....wwwww ",
           (const char *)" ....ww..B ",
           (const char *)" ....w.... ",
           (const char *)" ..mwww..B ",
           (const char *)"  ........ ",
           (const char *)"       ^   ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"        ^  ",
           (const char *)" ww......B ",
           (const char *)" www...... ",
           (const char *)" .w.w..... ",
           (const char *)" ...www... ",
           (const char *)" ...mwww.. ",
           (const char *)" ...www... ",
           (const char *)" ..ww..... ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"       ^   ",
           (const char *)" ..ww....  ",
           (const char *)" ...ww.m..^",
           (const char *)" ....w.... ",
           (const char *)" ....w.... ",
           (const char *)" ....w.... ",
           (const char *)" ...www... ",
           (const char *)" B....ww.. ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"  ^        ",
           (const char *)"  . .....  ",
           (const char *)" .........^",
           (const char *)"  ........ ",
           (const char *)" .......m. ",
           (const char *)"  ........ ",
           (const char *)"^......... ",
           (const char *)"  . .....$ ",
           (const char *)"  ^        ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"       ^   ",
           (const char *)"   ....... ",
           (const char *)"   ....... ",
           (const char *)" .....m...^",
           (const char *)" m......   ",
           (const char *)" .......s. ",
           (const char *)"^....... . ",
           (const char *)" $...... $ ",
           (const char *)"    ^      ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"...wwwwwww ",
           (const char *)".....ww..B ",
           (const char *)".......... ",
           (const char *)"       ^   ",
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"        ^  ",
           (const char *)" ww......B.",
           (const char *)" Wwwwww....",
           (const char *)" wwww......",
           (const char *)" ^         ",
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"       ^   ",
           (const char *)"^..wwww....",
           (const char *)" ...wwwww..",
           (const char *)" B.wwwwwww.",
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"  ^        ",
           (const char *)"  ..wwww...",
           (const char *)"^...www.m..",
           (const char *)"  .wwww..$.",
           (const char *)"  ^        ",
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"       ^   ",
           (const char *)"   ..www.. ",
           (const char *)" m..www...^",
           (const char *)" $.www...$ ",
           (const char *)"    ^      ",
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"$..LLLLLLL ",
           (const char *)"..LL.LL... ",
           (const char *)".LLL...... ",
           (const char *)"       ^   ",
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"        ^  ",
           (const char *)" LL........",
           (const char *)" .LLLLL....",
           (const char *)" .LLL......",
           (const char *)" ^         ",
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"       ^   ",
           (const char *)"^..LLLL....",
           (const char *)" ...LLLLL..",
           (const char *)" ..LLLLLLL.",
           (const char *)"  s       s",
           (const char *)"  .........",
           (const char *)"           ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"  ^        ",
           (const char *)"  ..LLLL...",
           (const char *)"^...LLL.m..",
           (const char *)"  .LLLL..$.",
           (const char *)"  s    s. .",
           (const char *)"  ......  .",
           (const char *)"          ^",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"       ^   ",
           (const char *)"   ..LLL.. ",
           (const char *)" m..L.L...^",
           (const char *)" $.LLLL..$ ",
           (const char *)"    ^      ",
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"     ^     ",
           (const char *)"  wwwwwwww ",
           (const char *)" wwwwwwwww^",
           (const char *)" wwww wwww ",
           (const char *)" wWwwww w  ",
           (const char *)" wwwwwwwww ",
           (const char *)" www wwWWw ",
           (const char *)"  wwwwwwww ",
           (const char *)"       ^   ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"       ^   ",
           (const char *)"   wwwwwww ",
           (const char *)"  w`wwww w ",
           (const char *)" ww``wwwww ",
           (const char *)" www`wwwww^",
           (const char *)" wwwwwwwww ",
           (const char *)" wwWWWWww  ",
           (const char *)" wwwwwww   ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"   ^       ",
           (const char *)" wwwwwwww  ",
           (const char *)" wwwwwwmww ",
           (const char *)" w    wwWw ",
           (const char *)" w mws`www ",
           (const char *)" w    `www ",
           (const char *)" ww```wwww ",
           (const char *)"  wwwwwwww^",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"    ^      ",
           (const char *)" wwwwwww`` ",
           (const char *)" wwWWWwww` ",
           (const char *)" wWWWWwwww ",
           (const char *)" wwwwwwwmw ",
           (const char *)" w     www ",
           (const char *)" w wmw www^",
           (const char *)" wsww$ ww$ ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"       ^   ",
           (const char *)" wwwwwwwww ",
           (const char *)" wwWww   w ",
           (const char *)" wWWww $ w ",
           (const char *)" mWWww s w ",
           (const char *)" wWWww www ",
           (const char *)"^wwwwwwwww ",
           (const char *)"  wwwwwwww ",
           (const char *)"   ^       ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"  ...      ",
           (const char *)"  ...      ",
           (const char *)"  .m.      ",
           (const char *)" ....      ",
           (const char *)"  ........ ",
           (const char *)"  .....b..^",
           (const char *)"  B....... ",
           (const char *)"       ^   ",
           (const char *)"           ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"   ....    ",
           (const char *)"   ..b.    ",
           (const char *)"   B...... ",
           (const char *)" .........^",
           (const char *)" ......... ",
           (const char *)" C         ",
           (const char *)" . $...... ",
           (const char *)" .       m ",
           (const char *)" ......... ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"        ^  ",
           (const char *)" $..... .. ",
           (const char *)" ....m. .. ",
           (const char *)"^......... ",
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"         ^ ",
           (const char *)"^.....   . ",
           (const char *)" .m...   . ",
           (const char *)" .....   . ",
           (const char *)" .....   . ",
           (const char *)" .....   . ",
           (const char *)" ......... ",
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"    ^      ",
           (const char *)"  ....     ",
           (const char *)"  ..m.....^",
           (const char *)"  f..B     ",
           (const char *)"    D      ",
           (const char *)"    ....   ",
           (const char *)"    ....   ",
           (const char *)"    .m..   ",
           (const char *)"       D   ",
           (const char *)" .$    ... ",
           (const char *)" ..s.mD..$ ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"  ^        ",
           (const char *)"  ...      ",
           (const char *)"  .m.      ",
           (const char *)"  ...      ",
           (const char *)" ....      ",
           (const char *)"  ........ ",
           (const char *)"    . ..f. ",
           (const char *)"....D ....^",
           (const char *)".....  ^   ",
           (const char *)".m...      ",
           (const char *)"....$      ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"         ^ ",
           (const char *)"   ....... ",
           (const char *)"   .b..... ",
           (const char *)"   ....... ",
           (const char *)"^......... ",
           (const char *)"    |.|  .^",
           (const char *)"     .     ",
           (const char *)"     s     ",
           (const char *)"m.. ... $.$",
           (const char *)".m.s...s...",
           (const char *)"m.. ... $.$",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"        ^  ",
           (const char *)" ........L ",
           (const char *)" L......LL ",
           (const char *)" LL.....LL ",
           (const char *)"     .     ",
           (const char *)"     D     ",
           (const char *)"  C.....C  ",
           (const char *)"  CC.m.CC  ",
           (const char *)"  $CCCCCC  ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"   ^       ",
           (const char *)" .....  .. ",
           (const char *)" .L...  .. ",
           (const char *)" .L....... ",
           (const char *)" .L...  .. ",
           (const char *)" .L...   . ",
           (const char *)" ....    . ",
           (const char *)" s       . ",
           (const char *)" $.      C ",
           (const char *)" ......  C ",
           (const char *)" ......    ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"    ^      ",
           (const char *)"  ....     ",
           (const char *)"  ....     ",
           (const char *)"  ....     ",
           (const char *)"     D     ",
           (const char *)"$.. ...f   ",
           (const char *)"...s....   ",
           (const char *)"... ..m.   ",
           (const char *)" s         ",
           (const char *)"..... $..  ",
           (const char *)"$....s$..  ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"         ^ ",
           (const char *)"  LL...... ",
           (const char *)"  L....... ",
           (const char *)"  ........ ",
           (const char *)" ......... ",
           (const char *)"  ........ ",
           (const char *)"    s  ... ",
           (const char *)" ....CC... ",
           (const char *)" ....CC.   ",
           (const char *)" m..$CC.   ",
           (const char *)"       ^   ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"        ^  ",
           (const char *)"   ......L ",
           (const char *)" fC....... ",
           (const char *)"   ....... ",
           (const char *)" ......... ",
           (const char *)"   .|.|... ",
           (const char *)"     .     ",
           (const char *)"     D     ",
           (const char *)"   .....   ",
           (const char *)"   .....   ",
           (const char *)"   $.m.$   ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"     ^     ",
           (const char *)" LL......L ",
           (const char *)" L.......L ",
           (const char *)" L......LL ",
           (const char *)"     C     ",
           (const char *)"     C     ",
           (const char *)"$CC.....   ",
           (const char *)"   .......^",
           (const char *)"   ....$   ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)" ^         ",
           (const char *)" ..... C.. ",
           (const char *)" ..... C.. ",
           (const char *)" ..... C.. ",
           (const char *)" .....CC.. ",
           (const char *)" ......CC. ",
           (const char *)" ......CC. ",
           (const char *)"    ```CC.^",
           (const char *)" $. ..`CCC ",
           (const char *)" ......CCC ",
           (const char *)" ...$..  $ ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"      ^    ",
           (const char *)" .......   ",
           (const char *)" .......   ",
           (const char *)" .f.......^",
           (const char *)"     D     ",
           (const char *)"..C CCC... ",
           (const char *)"..CD...... ",
           (const char *)"..C ..m... ",
           (const char *)" s    s    ",
           (const char *)".CC.. ..$. ",
           (const char *)"..... f$f. ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"         ^ ",
           (const char *)" .CCCCCCC. ",
           (const char *)".CCCCCCCCC.",
           (const char *)"CCCCCCCCC. ",
           (const char *)"CCCCCCCC.CC",
           (const char *)"CCC.CCC.CCC",
           (const char *)"$CCCCCCC.CC",
           (const char *)"..CCCCCCC. ",
           (const char *)"...CCCCC.  ",
           (const char *)".m..CCC..  ",
           (const char *)"       ^   ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"         ^ ",
           (const char *)" .CCCCCCC. ",
           (const char *)".CCCCCCCCC.",
           (const char *)"CC.CC.CCC. ",
           (const char *)"CCCCCCCC.C ",
           (const char *)"=======.CCC",
           (const char *)".CCCCCCC.CC",
           (const char *)"..CCC.CCC. ",
           (const char *)"...CCCCC.  ",
           (const char *)".m..CCC..  ",
           (const char *)"       ^   ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"         ^ ",
           (const char *)" .CCCCCCC. ",
           (const char *)".C.==.CCCC.",
           (const char *)"CC=CCCCCC. ",
           (const char *)"CC=CCCCC.CC",
           (const char *)"CC.CCCC.CCC",
           (const char *)"$CCCCCCC.C ",
           (const char *)"..CCCCCCC. ",
           (const char *)"...CCCCC.  ",
           (const char *)".m..CCC..  ",
           (const char *)"       ^   ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"         ^ ",
           (const char *)" .CCCCCCC. ",
           (const char *)".CC.==.CCC.",
           (const char *)"CCCCCCCCC. ",
           (const char *)".CCCCCCC.CC",
           (const char *)"CCCCCCC.CC ",
           (const char *)"$CCCCCCC.CC",
           (const char *)"..CCCCCCC. ",
           (const char *)"..CCCCCC.  ",
           (const char *)".mCCCCC..  ",
           (const char *)"       ^   ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"         ^ ",
           (const char *)" .CCCCCCC. ",
           (const char *)".CCCCCCCCC.",
           (const char *)"CCCCCCCCC. ",
           (const char *)"CCCCCCCC.C ",
           (const char *)"CCC.CCC.CCC",
           (const char *)"$CCCCCCC.C ",
           (const char *)"..CCCCCCC. ",
           (const char *)"..CCCCCC.  ",
           (const char *)".m.CCCC..  ",
           (const char *)"       ^   ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"         ^ ",
           (const char *)" .CCCCCCC. ",
           (const char *)".CCCCCCCCC.",
           (const char *)"CCCCCCCCC. ",
           (const char *)"CCCCCCCC.CC",
           (const char *)"CCC.CCC.CC ",
           (const char *)"$CCCCCCC.CC",
           (const char *)"..CCCCCCC. ",
           (const char *)"...CCCCC.  ",
           (const char *)".m..CCC..  ",
           (const char *)"       ^   ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"         ^ ",
           (const char *)" .CCCCCCC. ",
           (const char *)".CCCCCCCCC.",
           (const char *)"CCCCCCCCC. ",
           (const char *)"CC...CCC.C ",
           (const char *)"CC.m.CC.CCC",
           (const char *)"$CC..CCC.C ",
           (const char *)".CCCCCCCC. ",
           (const char *)"..CCCCCC.  ",
           (const char *)".m.CCCC..  ",
           (const char *)"       ^   ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"         ^ ",
           (const char *)" ..=CCCCC. ",
           (const char *)".CC=CCCCCC.",
           (const char *)"=CC=CCCCC. ",
           (const char *)"=CC=CCCC.C ",
           (const char *)"=CC.===.CC ",
           (const char *)"=CCCCCCC.C ",
           (const char *)"...CCCCCC. ",
           (const char *)"...CCCCC.  ",
           (const char *)"$m.CCCC..  ",
           (const char *)"       ^   ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"         ^ ",
           (const char *)" ......... ",
           (const char *)". .........",
           (const char *)".. ....... ",
           (const char *)"..g .......",
           (const char *)".... ......",
           (const char *)"$.... g....",
           (const char *)"...... ... ",
           (const char *)"....... .  ",
           (const char *)".m.......  ",
           (const char *)"       ^   ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"         ^ ",
           (const char *)" ......... ",
           (const char *)". .........",
           (const char *)".. ....... ",
           (const char *)"... ...... ",
           (const char *)"...........",
           (const char *)"..... .....",
           (const char *)"...... ... ",
           (const char *)"....... .  ",
           (const char *)".m......   ",
           (const char *)"       ^   ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"         ^ ",
           (const char *)" ..........",
           (const char *)". .........",
           (const char *)".. ...g... ",
           (const char *)"... ..... .",
           (const char *)".... ... ..",
           (const char *)"$.... . .. ",
           (const char *)".......... ",
           (const char *)".........  ",
           (const char *)".m.......  ",
           (const char *)"       ^   ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"         ^ ",
           (const char *)"..C..... . ",
           (const char *)".. ..... ..",
           (const char *)"..t..... . ",
           (const char *)".. . ... ..",
           (const char *)"..  g .. . ",
           (const char *)"$.   ......",
           (const char *)"..         ",
           (const char *)".........  ",
           (const char *)".g.......  ",
           (const char *)"       ^   ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"         ^ ",
           (const char *)" ......... ",
           (const char *)".......g ..",
           (const char *)"......g .. ",
           (const char *)".....g ... ",
           (const char *)"...........",
           (const char *)"$.. ...... ",
           (const char *)".... ..... ",
           (const char *)"..... ...  ",
           (const char *)".m.......  ",
           (const char *)"       ^   ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"         ^ ",
           (const char *)" ......... ",
           (const char *)"...........",
           (const char *)".... . ... ",
           (const char *)"..... .....",
           (const char *)".... . ... ",
           (const char *)"$..........",
           (const char *)".......... ",
           (const char *)".........  ",
           (const char *)".m.......  ",
           (const char *)"       ^   ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"         ^ ",
           (const char *)" ......... ",
           (const char *)"........ ..",
           (const char *)".. ....... ",
           (const char *)".......... ",
           (const char *)"...m... ...",
           (const char *)"$......... ",
           (const char *)".... ..... ",
           (const char *)".........  ",
           (const char *)".m.......  ",
           (const char *)"       ^   ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"         ^ ",
           (const char *)" ......... ",
           (const char *)"...... ....",
           (const char *)".......... ",
           (const char *)"... ...... ",
           (const char *)"........ . ",
           (const char *)".......... ",
           (const char *)".... ..... ",
           (const char *)".........  ",
           (const char *)"$m.. ....  ",
           (const char *)"       ^   ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"         ^ ",
           (const char *)"..CCCCCCC.C",
           (const char *)".        CC",
           (const char *)".CCCCCCCC.C",
           (const char *)"$        tC",
           (const char *)".CCCCCCCC.C",
           (const char *)".        CC",
           (const char *)"..CCCCCCC.C",
           (const char *)".        .C",
           (const char *)".m..CCC...C",
           (const char *)"    CCC^ CC",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"         ^ ",
           (const char *)"..CCCCCCC.C",
           (const char *)".        .C",
           (const char *)".CCCCCCCC.C",
           (const char *)"$        tC",
           (const char *)".CCCCCCCC.C",
           (const char *)".        .C",
           (const char *)"..CCCCCCC.C",
           (const char *)".        .C",
           (const char *)".m..CCC...C",
           (const char *)"    CCC^ CC",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"         ^ ",
           (const char *)"..CCCCCCC.C",
           (const char *)".   CCC  .C",
           (const char *)".CCCCCCCC.C",
           (const char *)"$   CCC  .C",
           (const char *)".CCCCCCCC.C",
           (const char *)".   CCC  .C",
           (const char *)"..CCCCCCC.C",
           (const char *)".   CCC  .C",
           (const char *)".m..CCC...C",
           (const char *)"    CCC^ CC",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"         ^ ",
           (const char *)"..CCCCCCC.C",
           (const char *)".    C   CC",
           (const char *)".CCCCCCCC.C",
           (const char *)"$    C   tC",
           (const char *)".CCCCCCCC.C",
           (const char *)".    C   CC",
           (const char *)"..CCCCCCC.C",
           (const char *)".....C   .C",
           (const char *)".m..CCC...C",
           (const char *)"... CCC^ CC",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"         ^ ",
           (const char *)"..CCCCCCC.C",
           (const char *)".    CCCCCC",
           (const char *)".CCCCCCCC.C",
           (const char *)"$   CCCCCtC",
           (const char *)".CCCCCCCC.C",
           (const char *)".     CCCCC",
           (const char *)"..CCCCCCC.C",
           (const char *)".....CCCC.C",
           (const char *)".m..CCC...C",
           (const char *)"....CCC^ CC",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"         ^ ",
           (const char *)"..CCCCCCC.C",
           (const char *)".CCCC.CCCCC",
           (const char *)".CCCC..CC.C",
           (const char *)"$C......CtC",
           (const char *)".CCCC..CC.C",
           (const char *)".CCCC.CCCCC",
           (const char *)"..CCCCCCC.C",
           (const char *)"....CCCCC.C",
           (const char *)".m..CCC...C",
           (const char *)"....CCC^ CC",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"         ^ ",
           (const char *)"...C.C....C",
           (const char *)".CCCCCCCCCC",
           (const char *)".CCCCCCCC.C",
           (const char *)"tCCCCCCCCtC",
           (const char *)".CCCCCCCC.C",
           (const char *)".CCCCCCCCCC",
           (const char *)"..CCCCCCC.C",
           (const char *)".CCCCCCCC.C",
           (const char *)".m..CCC...C",
           (const char *)"....CCC^ CC",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)" ........^ ",
           (const char *)"..CCCCCCC.C",
           (const char *)".CCCCCCCC=C",
           (const char *)"=CCCCCCCC=C",
           (const char *)"=CCCCCCCC=C",
           (const char *)"=CCCCCCCC=C",
           (const char *)"tCCCCCCCC=C",
           (const char *)"..CCCCCCC=C",
           (const char *)".CCCCCCCC.C",
           (const char *)".m..CCC...C",
           (const char *)"....CCC^ CC",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"         ^ ",
           (const char *)"        C.C",
           (const char *)"      L.CCC",
           (const char *)"     LL.C.C",
           (const char *)"    LLL.CtC",
           (const char *)" LLLLLL.C.C",
           (const char *)" L   LL.CCC",
           (const char *)" L    L.C.C",
           (const char *)" ...$   C.C",
           (const char *)" ...$  ... ",
           (const char *)" $$$$  ^   ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"         ^ ",
           (const char *)"        C.C",
           (const char *)"       CC.C",
           (const char *)"      CCCCC",
           (const char *)"     CCCCtC",
           (const char *)"       CCCC",
           (const char *)"     CCCC.C",
           (const char *)"        C.C",
           (const char *)"    CCCCC.C",
           (const char *)"   CCCC...C",
           (const char *)"  CCCCC^CCC",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"         ^ ",
           (const char *)".D.m.... . ",
           (const char *)".      D . ",
           (const char *)". .... . . ",
           (const char *)". .  . . . ",
           (const char *)". . $. m . ",
           (const char *)". .    . . ",
           (const char *)". .m..D. . ",
           (const char *)".        . ",
           (const char *)"..C.C.C... ",
           (const char *)"       ^   ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"         ^ ",
           (const char *)"         . ",
           (const char *)"         C ",
           (const char *)" LLLLLLL . ",
           (const char *)" Lg..... t ",
           (const char *)" L.$CC.. . ",
           (const char *)" L.$CC..DC ",
           (const char *)" Lg..... . ",
           (const char *)" LLLLLLL . ",
           (const char *)"       ... ",
           (const char *)"       ^   ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"         ^ ",
           (const char *)".C.C.C.C.. ",
           (const char *)".        . ",
           (const char *)".  ....$ . ",
           (const char *)".  .www. . ",
           (const char *)".  .www. . ",
           (const char *)".  ..... . ",
           (const char *)"D  D     . ",
           (const char *)"....     . ",
           (const char *)".m..   ... ",
           (const char *)"..$.   ^   ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"         ^ ",
           (const char *)"  CCCC   . ",
           (const char *)"  CCCCC  . ",
           (const char *)" CCCCCCCC. ",
           (const char *)"$========t ",
           (const char *)".CCCCCCCC. ",
           (const char *)".  CCCCC . ",
           (const char *)"..  CCC. . ",
           (const char *)"....     . ",
           (const char *)".m..CCC... ",
           (const char *)"....   ^   ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"m... www ^ ",
           (const char *)"....Dw$w . ",
           (const char *)"..C. www C ",
           (const char *)"  D      . ",
           (const char *)"....     t ",
           (const char *)"....     . ",
           (const char *)".C..     C ",
           (const char *)" D       . ",
           (const char *)"....     . ",
           (const char *)".m..CCC... ",
           (const char *)"....   ^   ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)" ........^ ",
           (const char *)"..       . ",
           (const char *)".  ..... = ",
           (const char *)"=  ...g. = ",
           (const char *)"=  ..$.. = ",
           (const char *)"=  .g... = ",
           (const char *)"t  ..... = ",
           (const char *)".. D     = ",
           (const char *)"....     . ",
           (const char *)".m..CCC... ",
           (const char *)"....   ^   ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"     ^     ",
           (const char *)"   ..t..   ",
           (const char *)"  ..`....  ",
           (const char *)" ...|`|... ",
           (const char *)"^...`T`...^",
           (const char *)" ...|`|... ",
           (const char *)"  ....`..  ",
           (const char *)"   .....   ",
           (const char *)"     .     ",
           (const char *)"     ^     ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"       ^   ",
           (const char *)"     ...   ",
           (const char *)"    .....  ",
           (const char *)"   ..```.. ",
           (const char *)" ...CCC`.. ",
           (const char *)" ..`C!C`.  ",
           (const char *)"  .`CCC.   ",
           (const char *)"   ````    ",
           (const char *)"           ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"     ^     ",
           (const char *)"    .t.    ",
           (const char *)"   ..C..   ",
           (const char *)" ...CC.... ",
           (const char *)" ..CCCCC..^",
           (const char *)"   .....   ",
           (const char *)"    `..    ",
           (const char *)"    |`|    ",
           (const char *)"     !     ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"     ^     ",
           (const char *)"   .....   ",
           (const char *)"  ...C...  ",
           (const char *)" ...CCC... ",
           (const char *)" ..CC!CC.. ",
           (const char *)" ...CCC...^",
           (const char *)"  ...CCC.. ",
           (const char *)"   ..$m... ",
           (const char *)"    ...... ",
           (const char *)"     ...`  ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"     ^     ",
           (const char *)"     .     ",
           (const char *)"    ...    ",
           (const char *)"   .. ..   ",
           (const char *)"  .......  ",
           (const char *)" .. ` . $.^",
           (const char *)"  ..``...  ",
           (const char *)"   `````   ",
           (const char *)"    CCC    ",
           (const char *)"    .!.    ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"        ^  ",
           (const char *)" .m...C..f ",
           (const char *)" ...CCC... ",
           (const char *)" .CCCCCCC. ",
           (const char *)" ..=====.. ",
           (const char *)" .CCCCCCC. ",
           (const char *)" ...CCC... ",
           (const char *)" B..CC...! ",
           (const char *)"       .   ",
           (const char *)"       .   ",
           (const char *)"       ...^",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"       ^   ",
           (const char *)"     ..!.B ",
           (const char *)"    .C.... ",
           (const char *)"   .CC.... ",
           (const char *)" .gCCCCC.. ",
           (const char *)" ...CC....^",
           (const char *)" ..$.C..   ",
           (const char *)" B.....    ",
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"         ^ ",
           (const char *)" B.m..C... ",
           (const char *)" ....C..!. ",
           (const char *)" ...CCCC.. ",
           (const char *)" ..CCCCCC.^",
           (const char *)"  CCCCC!   ",
           (const char *)"   CCCCC   ",
           (const char *)"   ..mCCCC ",
           (const char *)"   $.CCCCC ",
           (const char *)"  CCCCC    ",
           (const char *)"    CCCCC.$",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"      ^    ",
           (const char *)" B.......B ",
           (const char *)" ....C...m ",
           (const char *)" ...CC....M",
           (const char *)" ..CCCCC.. ",
           (const char *)" t   T   . ",
           (const char *)" .       . ",
           (const char *)" .!..$m... ",
           (const char *)"   .       ",
           (const char *)"   .  M....",
           (const char *)"   ^  .$ T.",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"     ^     ",
           (const char *)"     t     ",
           (const char *)" $.. . ...M",
           (const char *)" CCC . CCC ",
           (const char *)" ...===..m ",
           (const char *)" .!. . ... ",
           (const char *)" ... C  .. ",
           (const char *)" B...CCD.$ ",
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"    ^      ",
           (const char *)" C.C.C.C.C ",
           (const char *)" .C...C. . ",
           (const char *)" C. .C.C.C ",
           (const char *)"^.C.C.t.C.^",
           (const char *)" C.C.C.g.C ",
           (const char *)" ... .C.C. ",
           (const char *)" C.C.C. .C ",
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"     ^     ",
           (const char *)" !..C=C..  ",
           (const char *)" ...C=C... ",
           (const char *)" ...C=C..$ ",
           (const char *)" CCCC=C... ",
           (const char *)"^=====Ct..^",
           (const char *)" CCCCCC... ",
           (const char *)" ......... ",
           (const char *)" ...m..... ",
           (const char *)"  .......  ",
           (const char *)"     ^.    ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)" g.....C.. ",
           (const char *)" .b...CCC. ",
           (const char *)" ......C.. ",
           (const char *)"^...C..... ",
           (const char *)" ..CCC....^",
           (const char *)" ...C..b.. ",
           (const char *)" .......g. ",
           (const char *)"  .......b ",
           (const char *)"   . . .   ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"   ^       ",
           (const char *)"   . ...M. ",
           (const char *)"   . .$... ",
           (const char *)"   .    .. ",
           (const char *)"^...... .T ",
           (const char *)"      s    ",
           (const char *)" ....|.|.. ",
           (const char *)" ......... ",
           (const char *)" CCC....b. ",
           (const char *)" ..C..m... ",
           (const char *)" T.C......^",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"    ^      ",
           (const char *)"  ....     ",
           (const char *)"  ....     ",
           (const char *)"  CCCCCCC..",
           (const char *)"  ....===.m",
           (const char *)"  ....CCC..",
           (const char *)"  ....     ",
           (const char *)"  b..b     ",
           (const char *)"  ........ ",
           (const char *)"  ......m.^",
           (const char *)"  ^        ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"    ^      ",
           (const char *)" ..C.C.C.. ",
           (const char *)" .C...C.C. ",
           (const char *)" C.C.C.C.C ",
           (const char *)" .C.C.t...^",
           (const char *)" C.C.C.m.C ",
           (const char *)" ...C...CC ",
           (const char *)"^..C.C.CC. ",
           (const char *)"         s ",
           (const char *)"      .... ",
           (const char *)"      ..$. ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"  .C.....  ",
           (const char *)" C.C.|.|.. ",
           (const char *)" C.C...... ",
           (const char *)".CmCbCCC...",
           (const char *)"^=======.g^",
           (const char *)".C.CbCCC...",
           (const char *)" C.C...... ",
           (const char *)" C.C. . .. ",
           (const char *)"  .C.....  ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"     ^     ",
           (const char *)"     .     ",
           (const char *)"  kC...C$  ",
           (const char *)"  CC...CC  ",
           (const char *)"^....g...  ",
           (const char *)"  ........^",
           (const char *)"  CC...CC  ",
           (const char *)" .$C...C$. ",
           (const char *)" .   .   . ",
           (const char *)" ...m..... ",
           (const char *)"     ^     ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"   ^       ",
           (const char *)"   .       ",
           (const char *)"  |.|      ",
           (const char *)"   .       ",
           (const char *)"^..t...    ",
           (const char *)"      D    ",
           (const char *)" g.......$ ",
           (const char *)" .....m...^",
           (const char *)" ......... ",
           (const char *)" CCC  D    ",
           (const char *)"      ^    ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"     ^     ",
           (const char *)"  ....     ",
           (const char *)" LLLLL     ",
           (const char *)" L....     ",
           (const char *)"  ...mL    ",
           (const char *)"  LLLLL    ",
           (const char *)"  ....L    ",
           (const char *)"  ....L    ",
           (const char *)"^....LL... ",
           (const char *)"  ...L....^",
           (const char *)"  ..LL.... ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"        ^  ",
           (const char *)" C........ ",
           (const char *)" .C.CC.... ",
           (const char *)" .CC..C... ",
           (const char *)" ..CCCC... ",
           (const char *)" ...CCC... ",
           (const char *)" ...CCC... ",
           (const char *)" m..C....g ",
           (const char *)"       ^   ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"         ^ ",
           (const char *)"  ....C... ",
           (const char *)"  ....C.!. ",
           (const char *)" ..m..C... ",
           (const char *)" ...CCCCCC ",
           (const char *)" ...CC.... ",
           (const char *)" ...C.  .. ",
           (const char *)" .g.C....  ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"           ",
           (const char *)" ^         ",
           (const char *)" ...C....B ",
           (const char *)" ...CCCC.. ",
           (const char *)" . ..CC... ",
           (const char *)" ...CCC... ",
           (const char *)" . .C.m... ",
           (const char *)" ...CCC... ",
           (const char *)" B....C..m ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"     ^     ",
           (const char *)" ...C....G ",
           (const char *)" CCCCCC... ",
           (const char *)" ....CC... ",
           (const char *)" ...CCCC.. ",
           (const char *)" ..CCt.... ",
           (const char *)" ...CCCCCC ",
           (const char *)" .m....... ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"         ^ ",
           (const char *)" G....C... ",
           (const char *)" ...CCC... ",
           (const char *)" ....CCCC. ",
           (const char *)" CCCCCCC.. ",
           (const char *)" ...C..... ",
           (const char *)" ...CCC... ",
           (const char *)" ...C.C..$ ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"           ",
           (const char *)" ^         ",
           (const char *)" ....C..g$ ",
           (const char *)" ....Ct... ",
           (const char *)" ....CCt.. ",
           (const char *)" ....CCCCC ",
           (const char *)" ......... ",
           (const char *)" .........^",
           (const char *)" m........ ",
           (const char *)"       ^   ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"   ^       ",
           (const char *)"  .....    ",
           (const char *)"  ......   ",
           (const char *)" ..m..C... ",
           (const char *)" .....C... ",
           (const char *)" ....CC... ",
           (const char *)" CCCCCCt.. ",
           (const char *)" g....t..  ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"   ^       ",
           (const char *)"   ..C...B ",
           (const char *)"  ..CC.... ",
           (const char *)" ...C..... ",
           (const char *)" ..C...... ",
           (const char *)" .C...m... ",
           (const char *)" ...   ... ",
           (const char *)" B..   ..m ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"   ^       ",
           (const char *)" ........G ",
           (const char *)" .b.... .. ",
           (const char *)" ...C... . ",
           (const char *)" ....C.... ",
           (const char *)" .....C... ",
           (const char *)" ...   ... ",
           (const char *)" ...   .m. ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"       ^   ",
           (const char *)" G...  ... ",
           (const char *)" ..... . . ",
           (const char *)" .....C... ",
           (const char *)"     .C. . ",
           (const char *)"     .C... ",
           (const char *)" .....C... ",
           (const char *)" ..m.....$ ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"   ^       ",
           (const char *)"  B.B .... ",
           (const char *)"  ... ...$ ",
           (const char *)"  ... T..M ",
           (const char *)"^....      ",
           (const char *)"  ........ ",
           (const char *)"  .m....T. ",
           (const char *)"  B....... ",
           (const char *)"       ^   ",
           (const char *)"           ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"    ^      ",
           (const char *)"   ...B  T ",
           (const char *)"   ....  s ",
           (const char *)"   ....... ",
           (const char *)" .......m. ",
           (const char *)" .........^",
           (const char *)"  w        ",
           (const char *)"  W   M..$ ",
           (const char *)"  W   .LL. ",
           (const char *)" |w|  .LL. ",
           (const char *)"  ^   T..M ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"       ^   ",
           (const char *)" B.......B ",
           (const char *)"^...m..... ",
           (const char *)" B.......B ",
           (const char *)"     s     ",
           (const char *)"    |.|    ",
           (const char *)"     .     ",
           (const char *)"   .....   ",
           (const char *)"   ....$   ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"         ^ ",
           (const char *)" .B.B.  $. ",
           (const char *)" .....  .. ",
           (const char *)" B....  .. ",
           (const char *)" .m...  .. ",
           (const char *)" B....   . ",
           (const char *)" ......... ",
           (const char *)"       w   ",
           (const char *)"       W   ",
           (const char *)"       W   ",
           (const char *)"       ^   ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"    ^      ",
           (const char *)"  .m..     ",
           (const char *)"  ......t.^",
           (const char *)"  Bf.B  w  ",
           (const char *)"        w  ",
           (const char *)"        w  ",
           (const char *)"        w  ",
           (const char *)"        W  ",
           (const char *)"^..wwwwwW  ",
           (const char *)"        W  ",
           (const char *)"        ^  ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"  ^        ",
           (const char *)"  ...C.    ",
           (const char *)"  ...C$    ",
           (const char *)"  ...C.    ",
           (const char *)" ....      ",
           (const char *)"  D   .... ",
           (const char *)"  m   ....^",
           (const char *)" .D..D.... ",
           (const char *)" ....  .   ",
           (const char *)" G... B.B  ",
           (const char *)"       ^   ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"   ^       ",
           (const char *)" . .....b. ",
           (const char *)" . ......b ",
           (const char *)" ! ....... ",
           (const char *)" ......... ",
           (const char *)"    |.|  . ",
           (const char *)"     .     ",
           (const char *)"     D     ",
           (const char *)"   .BCB.   ",
           (const char *)"   .....   ",
           (const char *)"   ....$   ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"        ^  ",
           (const char *)" ...b..... ",
           (const char *)" ......m..^",
           (const char *)" ......... ",
           (const char *)"     .     ",
           (const char *)"     D     ",
           (const char *)"   .CCC.   ",
           (const char *)"   .m..$   ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"  ^        ",
           (const char *)" .....   .^",
           (const char *)" .CC..  .. ",
           (const char *)" .C...CC.m ",
           (const char *)" .CC..  .. ",
           (const char *)" ..C..   . ",
           (const char *)" ....    . ",
           (const char *)"  s      . ",
           (const char *)"  C      C ",
           (const char *)" ......  C ",
           (const char *)" ..m..$    ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"  ^        ",
           (const char *)"  ....C$   ",
           (const char *)"  .CC.     ",
           (const char *)"  ....     ",
           (const char *)"     D     ",
           (const char *)"... ......^",
           (const char *)"...D....   ",
           (const char *)"... ..G.   ",
           (const char *)" s         ",
           (const char *)"..... ...  ",
           (const char *)".....D.m.  ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"      ^    ",
           (const char *)"  .......B ",
           (const char *)"  .b...... ",
           (const char *)"  ....m... ",
           (const char *)" ......... ",
           (const char *)"  ........ ",
           (const char *)"    D .... ",
           (const char *)" $... .... ",
           (const char *)" ....  ^   ",
           (const char *)" G.$.      ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"       ^   ",
           (const char *)"   ......B ",
           (const char *)"   ....... ",
           (const char *)"   ...m... ",
           (const char *)"^......... ",
           (const char *)"   .|.|...^",
           (const char *)"     .     ",
           (const char *)"     D     ",
           (const char *)"   .....   ",
           (const char *)"   .m...   ",
           (const char *)"   ....$   ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"       ^   ",
           (const char *)" ....B.... ",
           (const char *)"^.......b. ",
           (const char *)" ...B.B...^",
           (const char *)"     s     ",
           (const char *)"     .     ",
           (const char *)"   .....   ",
           (const char *)"   ...m$   ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"    ^      ",
           (const char *)" B....  .  ",
           (const char *)" .....  .. ",
           (const char *)" ..M..  .. ",
           (const char *)" .....  .. ",
           (const char *)" ......s.. ",
           (const char *)" ......  m ",
           (const char *)"    .t.  . ",
           (const char *)" $. ...  C ",
           (const char *)" ......  . ",
           (const char *)" ......  $ ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"     ^     ",
           (const char *)"^.....     ",
           (const char *)"  ....     ",
           (const char *)"  B...     ",
           (const char *)"     D     ",
           (const char *)"... ....   ",
           (const char *)"...D....   ",
           (const char *)"... ..G.   ",
           (const char *)" s    D    ",
           (const char *)"..... ....^",
           (const char *)"$...B B..  ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"  ^        ",
           (const char *)"  D        ",
           (const char *)"  m.mm.D..^",
           (const char *)"  .m.m.    ",
           (const char *)"  $.mm.    ",
           (const char *)"  .m.m$    ",
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"   ^       ",
           (const char *)"   .       ",
           (const char *)"   .......^",
           (const char *)"   ....... ",
           (const char *)" .s....... ",
           (const char *)" .  .....  ",
           (const char *)" .   .t.   ",
           (const char *)" .    .    ",
           (const char *)" .    s    ",
           (const char *)"$.LL..m..  ",
           (const char *)"$.LL.m...  ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"        ^  ",
           (const char *)"        .  ",
           (const char *)"        .  ",
           (const char *)" m.... b.. ",
           (const char *)" ..m......^",
           (const char *)" m..m. b.. ",
           (const char *)"     .     ",
           (const char *)"     D     ",
           (const char *)"   .CCC.   ",
           (const char *)"   $$$$$   ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"  ^        ",
           (const char *)"  . $$   .^",
           (const char *)"  C ..  .. ",
           (const char *)"  . ..ss.m ",
           (const char *)"  C ..   C ",
           (const char *)"  . .. $ . ",
           (const char *)"  Cs.. C C ",
           (const char *)"  .    . . ",
           (const char *)"  C .... C ",
           (const char *)" .....m... ",
           (const char *)" ..m....m. ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"  ^        ",
           (const char *)"  .m..s... ",
           (const char *)"  .mm.   . ",
           (const char *)"  m...   $ ",
           (const char *)"     C     ",
           (const char *)"... G...C.^",
           (const char *)".m.C.G..   ",
           (const char *)"... ..G.   ",
           (const char *)" s         ",
           (const char *)"..... .$$  ",
           (const char *)".m...DM$$  ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"  ^        ",
           (const char *)"  D        ",
           (const char *)"  m.mm.D..^",
           (const char *)"  .m.m.    ",
           (const char *)"  $.mm.    ",
           (const char *)"  .m.m$    ",
           (const char *)"   s       ",
           (const char *)"  ....     ",
           (const char *)"  ...LL..$.",
           (const char *)"  ..LL.M..$",
           (const char *)"  .LL....$.",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"   ^       ",
           (const char *)"   . b..b  ",
           (const char *)" .s.......^",
           (const char *)" ` ...M... ",
           (const char *)" . ....... ",
           (const char *)" .  b...b  ",
           (const char *)" M   ...   ",
           (const char *)" .    .    ",
           (const char *)" .    s    ",
           (const char *)"$.LL..m..  ",
           (const char *)"$.LL.m...  ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"        ^  ",
           (const char *)" ........  ",
           (const char *)" D         ",
           (const char *)" m.... b.. ",
           (const char *)" ..m......^",
           (const char *)" m..m. b.. ",
           (const char *)"     s     ",
           (const char *)"     D     ",
           (const char *)"   .CCC.   ",
           (const char *)"   $$$$$   ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"  ^        ",
           (const char *)"  . $$   .^",
           (const char *)"  L ..  .. ",
           (const char *)"  . ..ss.m ",
           (const char *)"  L ..   L ",
           (const char *)"  . .. $ . ",
           (const char *)"  Ls.. L L ",
           (const char *)"  .    . . ",
           (const char *)"  L L... L ",
           (const char *)" ..L..m... ",
           (const char *)" .Lm....m. ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"  ^        ",
           (const char *)"  G..bs... ",
           (const char *)"  ....   . ",
           (const char *)"  b..G   $ ",
           (const char *)"     C     ",
           (const char *)"... G...C.^",
           (const char *)".m.C.G..   ",
           (const char *)"... ..G.   ",
           (const char *)" s         ",
           (const char *)"..... .$$  ",
           (const char *)".m...DM$$  ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"  ^        ",
           (const char *)"  D        ",
           (const char *)"  .....Dt.^",
           (const char *)"  .....    ",
           (const char *)"  $....    ",
           (const char *)"  .b..$    ",
           (const char *)"   s       ",
           (const char *)"  ....     ",
           (const char *)"  ...ww..$.",
           (const char *)"  ..ww....$",
           (const char *)"  .ww....$.",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"   ^       ",
           (const char *)"   . b..b  ",
           (const char *)" .sb......^",
           (const char *)" ` ....... ",
           (const char *)" . ....... ",
           (const char *)" .  b...b  ",
           (const char *)" .   ...   ",
           (const char *)" .    .    ",
           (const char *)" .    s    ",
           (const char *)"$.ww.....  ",
           (const char *)"$.ww.....  ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"        ^  ",
           (const char *)" ........  ",
           (const char *)" D         ",
           (const char *)" ..... b.. ",
           (const char *)" .LLL.....^",
           (const char *)" ..... b.. ",
           (const char *)"     s     ",
           (const char *)"     D     ",
           (const char *)"   .CCC.   ",
           (const char *)"$$ ..... $$",
           (const char *)"$$s..M..s$$",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"  ^        ",
           (const char *)"  . $$   .^",
           (const char *)"  w ..  .. ",
           (const char *)"  . ..ss.. ",
           (const char *)"  w ..   w ",
           (const char *)"  . .. $ . ",
           (const char *)"  ws.. w w ",
           (const char *)"  .    . . ",
           (const char *)"  w w... w ",
           (const char *)" ..w...... ",
           (const char *)" .w....... ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"  ^        ",
           (const char *)"  m..bs... ",
           (const char *)"  ....   . ",
           (const char *)"  b..m   $ ",
           (const char *)"     C     ",
           (const char *)"... G...C.^",
           (const char *)"...C.G..   ",
           (const char *)"... ..G.   ",
           (const char *)" s         ",
           (const char *)"..... .$$  ",
           (const char *)".....D.$$  ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"      ^    ",
           (const char *)" B.......B ",
           (const char *)" ...CCC... ",
           (const char *)" . .CCC. . ",
           (const char *)" ..CCCCC.. ",
           (const char *)" ..CCCC. . ",
           (const char *)" . .CCC... ",
           (const char *)" G.......B ",
           (const char *)"       ^   ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"     ^     ",
           (const char *)" .M....C.. ",
           (const char *)" ...CCC... ",
           (const char *)" ..CC!CC.. ",
           (const char *)" ...CCCC.b ",
           (const char *)" ....GC... ",
           (const char *)" ...CCC... ",
           (const char *)" B........ ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"   ^       ",
           (const char *)" .b.....B  ",
           (const char *)" ...CCC..  ",
           (const char *)" . ..GC... ",
           (const char *)" ...CCC... ",
           (const char *)" . ...C... ",
           (const char *)" ...CCC... ",
           (const char *)" B.......M ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"     ^     ",
           (const char *)"   .....   ",
           (const char *)"  ..CCC.   ",
           (const char *)" .....C... ",
           (const char *)" ..CCCCG.. ",
           (const char *)" ..CM$C... ",
           (const char *)" ..CCCC... ",
           (const char *)"  .......  ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"     ^     ",
           (const char *)" G......B  ",
           (const char *)" ...CCC..  ",
           (const char *)"^. ...C..^ ",
           (const char *)"  ..CCC.   ",
           (const char *)" .....C.   ",
           (const char *)"   .CCC.   ",
           (const char *)"  ......B  ",
           (const char *)"   ^       ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"        ^  ",
           (const char *)" .....L..L ",
           (const char *)" M..LLL... ",
           (const char *)" ...LLL..b ",
           (const char *)" ..LLLL... ",
           (const char *)" .....L..M ",
           (const char *)" ..L..L... ",
           (const char *)" ..L...... ",
           (const char *)"       ^   ",
           (const char *)"           ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"        ^  ",
           (const char *)" ...t..L.. ",
           (const char *)" M..L.LL.. ",
           (const char *)" ...LLLL..^",
           (const char *)" ...LLL... ",
           (const char *)" ....LL... ",
           (const char *)" L...LL... ",
           (const char *)" LL..LL..L ",
           (const char *)"    . L    ",
           (const char *)"    t L    ",
           (const char *)"    ^      ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"      ^    ",
           (const char *)" ........L ",
           (const char *)" LLLLLL... ",
           (const char *)" ...LLLL.. ",
           (const char *)" . .LLL... ",
           (const char *)" .....L... ",
           (const char *)" ..M..L. . ",
           (const char *)"  ....t... ",
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"      ^    ",
           (const char *)"  .t...... ",
           (const char *)" ...L.LLLL ",
           (const char *)" ...LMLL.. ",
           (const char *)" ...LLLL..^",
           (const char *)" . ..LL... ",
           (const char *)" .. ..L... ",
           (const char *)"  ....L.G$ ",
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"      ^    ",
           (const char *)"^...t.t..  ",
           (const char *)" ...L.L...^",
           (const char *)" ...L.L... ",
           (const char *)" LLLLLL... ",
           (const char *)" ..LLLLLLL ",
           (const char *)" .....LL..^",
           (const char *)" $..m.L..  ",
           (const char *)"        ^  ",
           (const char *)"           ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)" M........ ",
           (const char *)" ...LLLLLL ",
           (const char *)" ..LLL...f ",
           (const char *)" ...LLL... ",
           (const char *)" .....L... ",
           (const char *)" ..LLLL... ",
           (const char *)" ..L.....G ",
           (const char *)"      ..w  ",
           (const char *)"       .w  ",
           (const char *)"        ^  ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"   ^       ",
           (const char *)" ........M ",
           (const char *)" M..LLL... ",
           (const char *)" ...L..... ",
           (const char *)" ..LLfL.f. ",
           (const char *)" .....L... ",
           (const char *)" ...LLL... ",
           (const char *)" M......b. ",
           (const char *)"      ^    ",
           (const char *)"           ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"  ^        ",
           (const char *)"  ....LL.. ",
           (const char *)" ...LLLL..^",
           (const char *)" ...L!LL.. ",
           (const char *)" ..LL.LL.. ",
           (const char *)" ..LM.L... ",
           (const char *)" ..LLLL..  ",
           (const char *)" ..M....   ",
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"   ^       ",
           (const char *)" ........G ",
           (const char *)" M..LLL... ",
           (const char *)" ...LLLL.. ",
           (const char *)" ..LLLL.M. ",
           (const char *)" ..LLLL... ",
           (const char *)"  .LLLL..  ",
           (const char *)"   .LL..   ",
           (const char *)"    L      ",
           (const char *)"    LL  LL ",
           (const char *)"        LL ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)" ^         ",
           (const char *)"^......    ",
           (const char *)" ...LLL..  ",
           (const char *)" LLLLL...  ",
           (const char *)" Lf..fL... ",
           (const char *)" L..M.L...^",
           (const char *)" LLLLLL.   ",
           (const char *)" ..L.L.... ",
           (const char *)"         ^ ",
           (const char *)"           ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"        ^  ",
           (const char *)" .....C..C ",
           (const char *)" M..CCC... ",
           (const char *)" ...CCC..b ",
           (const char *)" ..CCCC... ",
           (const char *)" .....C..M ",
           (const char *)" ..C..C... ",
           (const char *)" ..C...... ",
           (const char *)"       ^   ",
           (const char *)"           ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"        ^  ",
           (const char *)" ...t..C.. ",
           (const char *)" M..C.CC.. ",
           (const char *)" ...CCCC..^",
           (const char *)" ...CCC... ",
           (const char *)" ....CC... ",
           (const char *)" C...CC... ",
           (const char *)" CC..CC..C ",
           (const char *)"    . C    ",
           (const char *)"    t C    ",
           (const char *)"    ^      ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"      ^    ",
           (const char *)" ........C ",
           (const char *)" CCCCCC... ",
           (const char *)" ...CCCC.. ",
           (const char *)" . .CCC... ",
           (const char *)" .....C... ",
           (const char *)" ..M..C. . ",
           (const char *)"  ....t... ",
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"      ^    ",
           (const char *)"  .t...... ",
           (const char *)" ...C.CCCC ",
           (const char *)" ...CMCC.. ",
           (const char *)" ...CCCC..^",
           (const char *)" . ..CC... ",
           (const char *)" .. ..C... ",
           (const char *)"  ....C.G$ ",
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"      ^    ",
           (const char *)"^...t.t..  ",
           (const char *)" ...C.C...^",
           (const char *)" ...C.C... ",
           (const char *)" CCCCCC... ",
           (const char *)" ..CCCCCCC ",
           (const char *)" .....CC..^",
           (const char *)" $..m.C..  ",
           (const char *)"        ^  ",
           (const char *)"           ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)" M........ ",
           (const char *)" ...CCCCCC ",
           (const char *)" ..CCC...f ",
           (const char *)" ...CCC... ",
           (const char *)" .....C... ",
           (const char *)" ..CCCC... ",
           (const char *)" ..C.....G ",
           (const char *)"      ..w  ",
           (const char *)"       .w  ",
           (const char *)"        ^  ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"   ^       ",
           (const char *)" ........M ",
           (const char *)" M..CCC... ",
           (const char *)" ...C..... ",
           (const char *)" ..CCfC.f. ",
           (const char *)" .....C... ",
           (const char *)" ...CCC... ",
           (const char *)" M......b. ",
           (const char *)"      ^    ",
           (const char *)"           ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"  ^        ",
           (const char *)"  ....CC.. ",
           (const char *)" ...CCCC..^",
           (const char *)" ...C!CC.. ",
           (const char *)" ..CC.CC.. ",
           (const char *)" ..CM.C... ",
           (const char *)" ..CCCC..  ",
           (const char *)" ..M....   ",
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"   ^       ",
           (const char *)" ........G ",
           (const char *)" M..CCC... ",
           (const char *)" ...CCCC.. ",
           (const char *)" ..CCCC.M. ",
           (const char *)" ..CCCC... ",
           (const char *)"  .CCCC..  ",
           (const char *)"   .CC..   ",
           (const char *)"    C      ",
           (const char *)"    CC  CC ",
           (const char *)"        CC ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)" ^         ",
           (const char *)"^......    ",
           (const char *)" ...CCC..  ",
           (const char *)" CCCCC...  ",
           (const char *)" Cf..fC... ",
           (const char *)" C..M.C...^",
           (const char *)" CCCCCC.   ",
           (const char *)" ..C.C.... ",
           (const char *)"         ^ ",
           (const char *)"           ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)" B...www.. ",
           (const char *)" ...www... ",
           (const char *)" ...ww.M.. ",
           (const char *)" ..wwww... ",
           (const char *)" ..wwWw... ",
           (const char *)"  ..www... ",
           (const char *)"   ......B ",
           (const char *)"       .   ",
           (const char *)"  wwwwww   ",
           (const char *)"  ^        ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)" wwww....B ",
           (const char *)" ..wwww... ",
           (const char *)" ...w..... ",
           (const char *)" ...wwwM..^",
           (const char *)" ...wWw... ",
           (const char *)" ...www... ",
           (const char *)" B..www..b ",
           (const char *)"   .www..  ",
           (const char *)"    .ww.   ",
           (const char *)"     .w.   ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)" .www....B ",
           (const char *)" ...www.M. ",
           (const char *)" ...w..... ",
           (const char *)" . .www... ",
           (const char *)" ...wWw. . ",
           (const char *)" M..www... ",
           (const char *)" .....ww.. ",
           (const char *)"   .       ",
           (const char *)"   .       ",
           (const char *)"   ^       ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"   ^       ",
           (const char *)" B.......  ",
           (const char *)" ...www... ",
           (const char *)" . .w....M ",
           (const char *)" ...www...^",
           (const char *)" ...wWw... ",
           (const char *)" M.wwww. . ",
           (const char *)" .ww...... ",
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"   ^       ",
           (const char *)"^........M ",
           (const char *)" ...www... ",
           (const char *)" ...w....B ",
           (const char *)" ...www. .^",
           (const char *)" M..wWw... ",
           (const char *)" ..wwwww.. ",
           (const char *)" .www..ww. ",
           (const char *)"      .    ",
           (const char *)"      .    ",
           (const char *)"      ^    ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"      .b.  ",
           (const char *)"      M$.^ ",
           (const char *)"      .b.  ",
           (const char *)"       s   ",
           (const char *)"      b.b  ",
           (const char *)"      .$.  ",
           (const char *)"      b.b  ",
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"   .$.     ",
           (const char *)"   $.$     ",
           (const char *)"   LLL     ",
           (const char *)"   LLL     ",
           (const char *)"    s      ",
           (const char *)"    M...^  ",
           (const char *)"   ...b.   ",
           (const char *)"   .$...   ",
           (const char *)"   .b..    ",
           (const char *)"           ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"  ^....    ",
           (const char *)"    ...... ",
           (const char *)"    .M..$. ",
           (const char *)"      ....^",
           (const char *)"         ^ ",
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"  ^        ",
           (const char *)"  .        ",
           (const char *)"  .        ",
           (const char *)"  .        ",
           (const char *)"  .        ",
           (const char *)"  M..      ",
           (const char *)"  .....    ",
           (const char *)"  .$...    ",
           (const char *)"  ........^",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"    ^      ",
           (const char *)"    .      ",
           (const char *)"    M      ",
           (const char *)".. ...     ",
           (const char *)"$.s.$.     ",
           (const char *)".. ......^ ",
           (const char *)"   ^       ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)" $t......B ",
           (const char *)" t.LLL.... ",
           (const char *)" LLLLkL... ",
           (const char *)" ..L.L.... ",
           (const char *)" ....L.... ",
           (const char *)" ....L.... ",
           (const char *)" !$....... ",
           (const char *)"       ^   ",
           (const char *)"           ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)" g........ ",
           (const char *)" ...LL..!. ",
           (const char *)" ..LkLL... ",
           (const char *)" ..L.L.... ",
           (const char *)" LLL.L....^",
           (const char *)" ....LLL.. ",
           (const char *)" $...L.... ",
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)" LL.....L  ",
           (const char *)" L..LL...L ",
           (const char *)" ..LLLL.!. ",
           (const char *)" ...kL....^",
           (const char *)" ....L.m.. ",
           (const char *)" ..m.L.... ",
           (const char *)" ....L...$ ",
           (const char *)"  s  .     ",
           (const char *)" $!  .     ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)" L......L! ",
           (const char *)" ...LLL... ",
           (const char *)" LLLL!LLLL ",
           (const char *)" ...LLL...^",
           (const char *)" ....L..b. ",
           (const char *)" L ..L.... ",
           (const char *)" L ......$ ",
           (const char *)" .     s   ",
           (const char *)" .     ..$ ",
           (const char *)"       .$! ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"   ^       ",
           (const char *)" L.....L.$ ",
           (const char *)" ...LL.L.. ",
           (const char *)" ..LLLL.LL^",
           (const char *)" ....L.... ",
           (const char *)" ...kL..L. ",
           (const char *)" LLLLL.LL. ",
           (const char *)" ......... ",
           (const char *)"  s      . ",
           (const char *)" !.   m..s ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)" !.......B ",
           (const char *)" ..CCC.... ",
           (const char *)" CCCCCC... ",
           (const char *)" ..CCC.... ",
           (const char *)" ....C.... ",
           (const char *)" ....C.... ",
           (const char *)" $$....... ",
           (const char *)"       .   ",
           (const char *)"       .   ",
           (const char *)"       ^   ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)" g.......! ",
           (const char *)" ...CC.... ",
           (const char *)" ..CCCC...^",
           (const char *)" ....C.... ",
           (const char *)" CCC.C.... ",
           (const char *)" ....CCC.. ",
           (const char *)" $...C.... ",
           (const char *)"    s      ",
           (const char *)"   $..$    ",
           (const char *)"   $..$    ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)" CC....CCk ",
           (const char *)" C..CC..CC^",
           (const char *)" ..CCCC..C ",
           (const char *)" ....C.... ",
           (const char *)" ....C.m.. ",
           (const char *)" ..m.C.... ",
           (const char *)" !...C.... ",
           (const char *)" s   .  s  ",
           (const char *)" $   .  .$ ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"   ^       ",
           (const char *)" C....CCCC ",
           (const char *)" ...CCC.!C ",
           (const char *)" CCC..CCCC ",
           (const char *)" ....CCCC. ",
           (const char *)" ....C..b. ",
           (const char *)" C ..C.... ",
           (const char *)" C ......! ",
           (const char *)" s      s  ",
           (const char *)" .   $. .$ ",
           (const char *)" CCCC$. .. ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"   ^       ",
           (const char *)" C.....C.k ",
           (const char *)" ...CCCC.. ",
           (const char *)" ..CCCC$CC ",
           (const char *)" ....CCCC. ",
           (const char *)" ...!C..C.^",
           (const char *)" CCCCC.CC! ",
           (const char *)" ......... ",
           (const char *)" ..      . ",
           (const char *)"^..      .^",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)" k.......B ",
           (const char *)" ..www.... ",
           (const char *)" www!ww... ",
           (const char *)" ..www.... ",
           (const char *)" ....w.CCCC",
           (const char *)" ....w.CC..",
           (const char *)"      ..C..",
           (const char *)" ...$  .  .",
           (const char *)" T...  .  T",
           (const char *)" ...$  ^   ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)" g.....b.$ ",
           (const char *)" ...ww.... ",
           (const char *)" ..wwww... ",
           (const char *)" ....w..!. ",
           (const char *)" www.w....^",
           (const char *)" ....www.. ",
           (const char *)" $...w.... ",
           (const char *)"           ",
           (const char *)" .m..C...T ",
           (const char *)" T...C.$.m ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)" ww......  ",
           (const char *)" w..ww...w ",
           (const char *)" ..ww$w... ",
           (const char *)" ....w.... ",
           (const char *)" !...w.m..^",
           (const char *)" ..m.w.... ",
           (const char *)" k...w...$ ",
           (const char *)"     .     ",
           (const char *)" $..s.     ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)" w......w  ",
           (const char *)" ..wwwww.. ",
           (const char *)" wwww$wwww ",
           (const char *)" ..wwww... ",
           (const char *)" ....w.... ",
           (const char *)" w ..w....^",
           (const char *)" w ....... ",
           (const char *)" .         ",
           (const char *)" .$!   ..$ ",
           (const char *)"        .. ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"     ^     ",
           (const char *)" w.....w.  ",
           (const char *)"^...ww.w.. ",
           (const char *)" ..wwww.ww ",
           (const char *)" ....w..k$ ",
           (const char *)" ....w..w.^",
           (const char *)" wwwww.ww. ",
           (const char *)" ......... ",
           (const char *)" s       . ",
           (const char *)" ..      . ",
           (const char *)" $!        ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)" .... ..$  ",
           (const char *)" .b..D...  ",
           (const char *)" .... ..$  ",
           (const char *)" ....      ",
           (const char *)" ......... ",
           (const char *)"   D   C   ",
           (const char *)"  ..!  t   ",
           (const char *)"  ...  C   ",
           (const char *)"  $m$  .   ",
           (const char *)"       ^   ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)"   wwww..$ ",
           (const char *)"  ww!www.. ",
           (const char *)"   wwww... ",
           (const char *)" ...www...^",
           (const char *)"  s .www.. ",
           (const char *)"  $ .www.w ",
           (const char *)"  m .wwwww ",
           (const char *)"  .      . ",
           (const char *)"  .      C ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"    ^      ",
           (const char *)" ww.....w  ",
           (const char *)" w.. B...w ",
           (const char *)" ...B$B... ",
           (const char *)" ..!.B....^",
           (const char *)" ....w.m.. ",
           (const char *)" ..m.w.... ",
           (const char *)" ....w...$ ",
           (const char *)"     .     ",
           (const char *)" $   .   $ ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)" w......w  ",
           (const char *)" ..wwwww.. ",
           (const char *)" wwww$wwww ",
           (const char *)" ..wwww... ",
           (const char *)" ....w.... ",
           (const char *)" w ..w....^",
           (const char *)" w ......! ",
           (const char *)" C         ",
           (const char *)" .     ..$ ",
           (const char *)"        .. ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"   ^       ",
           (const char *)"   .       ",
           (const char *)"  ......Ct ",
           (const char *)"  .      C ",
           (const char *)"^.. $!$$ . ",
           (const char *)"  . ...! . ",
           (const char *)"  . D    .^",
           (const char *)" s........ ",
           (const char *)" .    .    ",
           (const char *)" ..$  .    ",
           (const char *)" $$$  ^    ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"      ^    ",
           (const char *)" k.......B ",
           (const char *)" ..```.... ",
           (const char *)" ```!``... ",
           (const char *)"   s `.... ",
           (const char *)" ... `.... ",
           (const char *)" ... `.... ",
           (const char *)" $$. ..... ",
           (const char *)"       ^   ",
           (const char *)"           ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"     ^     ",
           (const char *)" g.....b.$ ",
           (const char *)" ...``.... ",
           (const char *)" ..````... ",
           (const char *)" ....`..!. ",
           (const char *)" s         ",
           (const char *)" ....s``.. ",
           (const char *)" $... ...$ ",
           (const char *)"           ",
           (const char *)"           ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"   ^       ",
           (const char *)" ``. ....  ",
           (const char *)" `..s`...` ",
           (const char *)" ..` $`... ",
           (const char *)" ... `.... ",
           (const char *)" !.. `.m.. ",
           (const char *)" ..m `.... ",
           (const char *)" k.. `...$ ",
           (const char *)"     .     ",
           (const char *)" $..s.     ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"     ^     ",
           (const char *)" `......`  ",
           (const char *)"     s     ",
           (const char *)" ````$```` ",
           (const char *)" ..````... ",
           (const char *)" ....`.... ",
           (const char *)" s ..`.... ",
           (const char *)" ` ....... ",
           (const char *)" .         ",
           (const char *)" .$!   ..$ ",
           (const char *)"        .. ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)" ^         ",
           (const char *)" `.....`.  ",
           (const char *)" ...``.`.. ",
           (const char *)" ..````.`` ",
           (const char *)" ....`..k$^",
           (const char *)" ....`..`. ",
           (const char *)" `````.``. ",
           (const char *)" ......... ",
           (const char *)"  s      s ",
           (const char *)" ..      . ",
           (const char *)" $!      ^ ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)" .... ..$  ",
           (const char *)" .b..s...  ",
           (const char *)" .... ..$  ",
           (const char *)" ....      ",
           (const char *)" ......... ",
           (const char *)"   D   .   ",
           (const char *)"  ..!  .   ",
           (const char *)"  ...  .   ",
           (const char *)"  $m$  .   ",
           (const char *)"       ^   ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"   ^       ",
           (const char *)"   ````..$ ",
           (const char *)"  ``!```.. ",
           (const char *)"   ````... ",
           (const char *)"^...```... ",
           (const char *)"    .```.. ",
           (const char *)"  $ .```.` ",
           (const char *)"  m .````` ",
           (const char *)"  .      . ",
           (const char *)"  .s.C.C.C ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"    ^      ",
           (const char *)" ``.....`  ",
           (const char *)" `.. B...` ",
           (const char *)" ...B$B... ",
           (const char *)"^..!.B.... ",
           (const char *)" ....`.m.. ",
           (const char *)" ..m.`.... ",
           (const char *)" ....`...$ ",
           (const char *)"     .     ",
           (const char *)" $..s.s..$ ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"        ^  ",
           (const char *)" `......`  ",
           (const char *)" ..`````.. ",
           (const char *)"^````$```` ",
           (const char *)" ..````... ",
           (const char *)" ....`.... ",
           (const char *)" ` ..`.... ",
           (const char *)" ` ......! ",
           (const char *)" C     s   ",
           (const char *)" .     ..$ ",
           (const char *)"       $.. ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"   ^       ",
           (const char *)"   .       ",
           (const char *)"  ........ ",
           (const char *)"  .      . ",
           (const char *)"^.. $!$$ . ",
           (const char *)"  . ...! . ",
           (const char *)"  . D    .^",
           (const char *)" s........ ",
           (const char *)" .    .    ",
           (const char *)" .$   .    ",
           (const char *)" $$   ^    ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)" .... m.m  ",
           (const char *)" ..m.D...  ",
           (const char *)" m... m.m  ",
           (const char *)" ...m      ",
           (const char *)" .....www. ",
           (const char *)"   D  |w|  ",
           (const char *)"  m.m  w   ",
           (const char *)"  .m.  w   ",
           (const char *)"  m!m  .   ",
           (const char *)"       ^   ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"        ^  ",
           (const char *)"   $$!...$ ",
           (const char *)"  $$.$$!.. ",
           (const char *)"   $$$!..m ",
           (const char *)" .m.$!..m. ",
           (const char *)"    ..$!.. ",
           (const char *)"  $ m$$..! ",
           (const char *)"  m .m$..! ",
           (const char *)"  .      . ",
           (const char *)"  .      C ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"    ^      ",
           (const char *)" g.......g ",
           (const char *)" ... !.... ",
           (const char *)" ...$$!... ",
           (const char *)" ....!.... ",
           (const char *)" !.....m.. ",
           (const char *)" ..m...... ",
           (const char *)" g.......g ",
           (const char *)"     C     ",
           (const char *)" $   C   $ ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"    ^      ",
           (const char *)" WWwww..w  ",
           (const char *)" W D       ",
           (const char *)" w ....... ",
           (const char *)" w ...!... ",
           (const char *)" . ....... ",
           (const char *)" w ....www ",
           (const char *)" w M..www$ ",
           (const char *)" .       s ",
           (const char *)" ......s.$ ",
           (const char *)" ...... $. ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"   ^       ",
           (const char *)"   .       ",
           (const char *)"  .......! ",
           (const char *)"  .      . ",
           (const char *)"^.. $!$M . ",
           (const char *)"  . .... . ",
           (const char *)"  . D    .^",
           (const char *)"  ........ ",
           (const char *)"  s   .    ",
           (const char *)" .!   .    ",
           (const char *)"      ^    ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"           ",
           (const char *)" m... ...  ",
           (const char *)" ....s...  ",
           (const char *)" .!.. ...  ",
           (const char *)" .... .m.  ",
           (const char *)" .... .... ",
           (const char *)"   D  |.|  ",
           (const char *)" $..$  .   ",
           (const char *)" .... |.|  ",
           (const char *)" ....  .   ",
           (const char *)"       ^   ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"       ^   ",
           (const char *)"   $$$!..$ ",
           (const char *)"  $$$!$!.. ",
           (const char *)"   $$$!..m ",
           (const char *)" .m.$$!.m. ",
           (const char *)"    .$$!.. ",
           (const char *)"  $ m$$$.! ",
           (const char *)"  m .m$$$! ",
           (const char *)"  .      . ",
           (const char *)"  .  !   C ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"    ^      ",
           (const char *)"  .......  ",
           (const char *)" ... $..!. ",
           (const char *)" ...$$!... ",
           (const char *)" ....!.... ",
           (const char *)" .!....m.. ",
           (const char *)" ..m...... ",
           (const char *)"  .....!.  ",
           (const char *)"     C     ",
           (const char *)" $   C   ! ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"       ^   ",
           (const char *)" WWwww..w  ",
           (const char *)" W D       ",
           (const char *)" w ....... ",
           (const char *)" w .....!. ",
           (const char *)" . ....... ",
           (const char *)" w ....www ",
           (const char *)" w M..www$ ",
           (const char *)"   ....  D ",
           (const char *)"   ...  .$ ",
           (const char *)"   ....D$. ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"   ^       ",
           (const char *)"   .       ",
           (const char *)"  ........ ",
           (const char *)"  .    D . ",
           (const char *)"^.. $!$M . ",
           (const char *)"  . .... . ",
           (const char *)"  . !... .^",
           (const char *)"  . $..$ . ",
           (const char *)"      D    ",
           (const char *)"      .    ",
           (const char *)"      ^    ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"   ^       ",
           (const char *)"   .       ",
           (const char *)"  |.|LLL   ",
           (const char *)"  ...LLL   ",
           (const char *)"  |.|      ",
           (const char *)"  ....LLL  ",
           (const char *)"   D  LLL  ",
           (const char *)" $...!     ",
           (const char *)" b....     ",
           (const char *)" .m..m     ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"   ^       ",
           (const char *)"   ....L.$ ",
           (const char *)"         . ",
           (const char *)" ....C...m ",
           (const char *)"     s     ",
           (const char *)" C...L...C ",
           (const char *)"  .        ",
           (const char *)"...m...... ",
           (const char *)"D D        ",
           (const char *)". .     $! ",
           (const char *)"....!.DC$! ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"    ^      ",
           (const char *)" LL C...!  ",
           (const char *)" $L .$..!  ",
           (const char *)" LL.$$!.m  ",
           (const char *)" .  .!...  ",
           (const char *)"LLL     L  ",
           (const char *)"LLL     L  ",
           (const char *)"LL    LLLL ",
           (const char *)"  $$!  LLL ",
           (const char *)"  $!$   L  ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"   ^       ",
           (const char *)"   =     $ ",
           (const char *)"   =     . ",
           (const char *)"   =     . ",
           (const char *)"   =     . ",
           (const char *)"   =     . ",
           (const char *)"   =     . ",
           (const char *)"   M     C ",
           (const char *)"   D..!  D ",
           (const char *)"   ...  .$ ",
           (const char *)"   !.CCC$. ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"   ^       ",
           (const char *)"   .       ",
           (const char *)"  ........ ",
           (const char *)"  .    s . ",
           (const char *)"  . $!$m . ",
           (const char *)"  . g!m! . ",
           (const char *)"  . m$!m . ",
           (const char *)"  . $mf$ . ",
           (const char *)"  .      . ",
           (const char *)"  .......m^",
           (const char *)"         ^ ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"   ^       ",
           (const char *)"   .       ",
           (const char *)"   L.LLL$  ",
           (const char *)"   L.LLLm  ",
           (const char *)"   s       ",
           (const char *)"  .L..LLL$ ",
           (const char *)" ..!..LLLm ",
           (const char *)" ....      ",
           (const char *)" b....     ",
           (const char *)" .....CCC! ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"   ^       ",
           (const char *)" ......... ",
           (const char *)" .CCCCCC.. ",
           (const char *)" ........m ",
           (const char *)"  LLLLL    ",
           (const char *)"   LLL     ",
           (const char *)"  LLL      ",
           (const char *)" LLL       ",
           (const char *)" .!.       ",
           (const char *)"           ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"    ^      ",
           (const char *)" LL.C...!  ",
           (const char *)" !L..$..!  ",
           (const char *)" LLL$$!.m  ",
           (const char *)" LLL.$..!  ",
           (const char *)" LL ...    ",
           (const char *)"LL   LLL   ",
           (const char *)"      LLL  ",
           (const char *)"  $$!  LLL ",
           (const char *)"  $!$.s..  ",
           (const char *)"           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"   ^       ",
           (const char *)"   = !CCC. ",
           (const char *)"   =     . ",
           (const char *)"   =     C ",
           (const char *)"   =     C ",
           (const char *)"   =     C ",
           (const char *)"   =     C ",
           (const char *)"   M     C ",
           (const char *)"   D..!  D ",
           (const char *)"   ...  .$ ",
           (const char *)"  !..sCC$. ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"   ^       ",
           (const char *)"   .       ",
           (const char *)"  ........ ",
           (const char *)"  s      s ",
           (const char *)"  ..$!$m.. ",
           (const char *)" L..g!m!.. ",
           (const char *)" L..m$!m.. ",
           (const char *)" L..$mf$.. ",
           (const char *)" L.!...... ",
           (const char *)" L......!.^",
           (const char *)"  ^        ",
           nullptr);
  /* clang-format on */
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
}
