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
#include <vector>

//
// How many times to try creating a single level
//
static int MAX_LEVEL_GEN_TRIES_FOR_SAME_SEED                       = 100;
static int MAX_LEVEL_GEN_TRIES_FOR_PLACING_ANY_ROOM_WITH_SAME_DOOR = 500;
static int MAX_LEVEL_GEN_TRIES_FOR_WALKING_DOORS                   = 500;
static int MAX_LEVEL_GEN_TRIES_FOR_PLACING_NEW_ROOMS               = 100;
static int MAX_LEVEL_ROOM_COUNT                                    = 100;
static int MIN_LEVEL_ROOM_COUNT                                    = 10;

//
// Statistics
//
static int level_place_room_first_fail_count;
static int level_place_room_subs_fail_count;
static int level_place_room_dup_count;
static int level_place_fail_count;
static int level_find_door_fail_count;

class Cell;
class Room;
class LevelGen;

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
  // Level tiles and room info
  //
  Cell data[ MAP_WIDTH ][ MAP_HEIGHT ];
};

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
  // Room size
  //
  int width  = {};
  int height = {};

  //
  // Room data
  //
  char *data = {};

  //
  // For debugging
  //
  std::string name;

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
static std::vector< class Room * > rooms;

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
        case CHARMAP_DOOR : r->doors.push_back(point(x, y)); continue;
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
  rooms.push_back(n);

  n->room_no = ++room_no;
  n->name    = r->name;
  n->file    = r->file;
  n->line    = r->line;
  n->width   = r->height;
  n->height  = r->width;
  n->data    = (char *) myzalloc(r->width * r->height, "room data");

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
  rooms.push_back(n);

  n->room_no = ++room_no;
  n->name    = r->name;
  n->file    = r->file;
  n->line    = r->line;
  n->width   = r->width;
  n->height  = r->height;
  n->data    = (char *) myzalloc(r->width * r->height, "room data");

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
static void room_add(Gamep g, const char *file, int line, const char *name, ...)
{
  TRACE_NO_INDENT();

  va_list ap;
  int     room_width  = 0;
  int     room_height = 0;

  //
  // First scan, get width and height
  //
  va_start(ap, name);

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
        case CHARMAP_CHASM :
        case CHARMAP_CHASM_50 :
        case CHARMAP_DOOR :
        case CHARMAP_EMPTY :
        case CHARMAP_FLOOR :
        case CHARMAP_EXIT :
        case CHARMAP_KEY :
        case CHARMAP_MONST1 :
        case CHARMAP_PLAYER :
        case CHARMAP_TREASURE :
        case CHARMAP_FLOOR_50 :
        case CHARMAP_FLOOR_40 :
        case CHARMAP_FLOOR_30 :
        case CHARMAP_FLOOR_20 :
        case CHARMAP_FLOOR_10 :
        case CHARMAP_WALL : break;
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
  rooms.push_back(r);

  r->room_no = ++room_no;
  r->name    = std::string(name);
  r->file    = file;
  r->line    = line;
  r->width   = room_width;
  r->height  = room_height;
  r->data    = (char *) myzalloc(room_width * room_height, "room data");

  //
  // Now read the room again
  //
  va_start(ap, name);

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
static class Room *room_random_get(Gamep g, class LevelGen *l)
{
  TRACE_NO_INDENT();

  return rooms[ pcg_random_range(0, rooms.size()) ];
}

//
// Dump a room
//
static void room_dump(Gamep g, class Room *r)
{
  TRACE_NO_INDENT();

  LOG("Room %d %s %s:%d", r->room_no, r->name.c_str(), r->file, r->line);

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

  for (auto r : rooms) {
    room_dump(g, r);
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
      if (unlikely(room_c == CHARMAP_DOOR)) {
        //
        // Doors can overlap doors in the same tile.
        //
        switch (l->data[ p.x ][ p.y ].c) {
          case CHARMAP_CHASM :
          case CHARMAP_EMPTY :
          case CHARMAP_DOOR :
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
              case CHARMAP_DOOR :
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
            case CHARMAP_DOOR :
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
        case CHARMAP_CHASM : break;
        case CHARMAP_CHASM_50 :
          if (d100() > 50) {
            room_c = CHARMAP_FLOOR;
          } else {
            room_c = CHARMAP_CHASM;
          }
          break;
        case CHARMAP_DOOR : break;
        case CHARMAP_EMPTY : break;
        case CHARMAP_FLOOR : break;
        case CHARMAP_EXIT : break;
        case CHARMAP_KEY : break;
        case CHARMAP_MONST1 : break;
        case CHARMAP_PLAYER : break;
        case CHARMAP_TREASURE :
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
        case CHARMAP_WALL : break;
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

  for (auto r : rooms) {
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
    LOG("Level: %s (%s)", l->seed.c_str(), msg);
  } else {
    LOG("Level: %s", l->seed.c_str());
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
void level_gen_stats_dump(Gamep g)
{
  TRACE_NO_INDENT();

  LOG("Level errors:");
  LOG("- place level fail:             %d", level_place_fail_count);
  LOG("- place first room fail:        %d", level_place_room_first_fail_count);
  LOG("- place subsequent room fail:   %d", level_place_room_subs_fail_count);
  LOG("- find door to place room fail: %d", level_find_door_fail_count);
  LOG("Level info:");
  LOG("- place room duplicate found: %d", level_place_room_dup_count);
}

//
// Update the list of all doors, and return a new unwalked door to use
//
static bool level_gen_random_door_get(Gamep g, class LevelGen *l, point *door)
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
      if (l->data[ x ][ y ].c != CHARMAP_DOOR) {
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
  *door = l->doors_all[ pcg_random_range(0, l->doors_all.size()) ];

  return true;
}

//
// Create rooms from the current seed
//
static class LevelGen *level_gen_create_rooms(Gamep g)
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

    l       = new LevelGen();
    l->seed = std::string(game_get_seed(g));

    //
    // Choose a random start point for the rooms
    //
    int   x = pcg_random_range(0, MAP_WIDTH);
    int   y = pcg_random_range(0, MAP_HEIGHT);
    point at(x, y);

    //
    // Choose a random first room and place it
    //
    auto r = l->room_first = room_random_get(g, l);

    if (! room_can_place_at(g, l, r, at)) {
      level_place_room_first_fail_count++;
      continue;
    }

    room_place_at(g, l, r, at);

    //
    // Placed the first room
    //
    level_gen_dump(g, l, "placed first room");

    //
    // Ok, we have our first room. Keep placing rooms now.
    //
    int  door_place_tries = 0;
    bool rooms_place_fail = false;

    //
    // Up to the maximum rooms per level
    //
    int room_placed_failure_count = 0;
    while ((int) l->rooms_placed.size() < MAX_LEVEL_ROOM_COUNT) {
      LOG("rooms placed %d door_place_tries %d room_placed_failure_count %d", (int) l->rooms_placed.size(),
          door_place_tries, room_placed_failure_count);
      //
      // Only try to place rooms against doors so many times
      //
      if (door_place_tries++ > MAX_LEVEL_GEN_TRIES_FOR_WALKING_DOORS) {
        rooms_place_fail = true;
        break;
      }

      //
      // Tried enough times to place rooms and failed
      //
      if (room_placed_failure_count > MAX_LEVEL_GEN_TRIES_FOR_PLACING_NEW_ROOMS) {
        break;
      }

      //
      // Find a random door that we have not walked before
      //
      point door_at;
      if (! level_gen_random_door_get(g, l, &door_at)) {
        level_find_door_fail_count++;
        rooms_place_fail = true;
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
        r = room_random_get(g, l);
        if (l->rooms_placed.find(r) != l->rooms_placed.end()) {
          level_place_room_dup_count++;
          rooms_place_fail = true;
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
          point door_intersection_at = door_at - d;
          if (! room_can_place_at(g, l, r, door_intersection_at)) {
            level_place_room_subs_fail_count++;
            continue;
          }

          //
          // Place the room
          //
          room_place_at(g, l, r, door_intersection_at);

          //
          // Don't try this door again
          //
          l->doors_walked[ door_at ] = true;

          room_was_placed = true;
          break;
        }

        if (room_was_placed) {
          level_gen_dump(g, l, "placed another room");
          room_placed_failure_count = 0;
          break;
        }
      }
      room_placed_failure_count++;
    }

    if (rooms_place_fail) {
      //
      // If we placed enough rooms, this level is good enough to go
      //
      if ((int) l->rooms_placed.size() > MIN_LEVEL_ROOM_COUNT) {
        return l;
      }

      //
      // Not enough rooms
      //
      continue;
    }

    //
    // Success
    //
    return l;
  }

  delete l;

  level_place_fail_count++;
  LOG("Failed to create room with seed: %s", game_get_seed(g));

  return nullptr;
}

//
// Create a level from the current game seed
//
static class LevelGen *level_gen(Gamep g)
{
  TRACE_NO_INDENT();

  LevelGen *l = level_gen_create_rooms(g);
  if (! l) {
    return l;
  }

  // level_gen_trim_dead_end_doors(l);

  return l;
}

void level_gen_test(Gamep g)
{
  TRACE_NO_INDENT();

  auto l = level_gen(g);
  if (l) {
    level_gen_dump(g, l);
  }

  level_gen_stats_dump(g);
}

//
// Create all rooms
//
void rooms_init(Gamep g)
{
  TRACE_NO_INDENT();

  /* clang-format off */
  room_add(g, __FUNCTION__, __LINE__, "no-name",
           (const char *)"  D 55",
           (const char *)" ....5",
           (const char *)"D.... ",
           (const char *)" ....D",
           (const char *)"   D  ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__, "no-name",
           (const char *)"   D    ",
           (const char *)" 5....5 ",
           (const char *)"D...... ",
           (const char *)" 5.....D",
           (const char *)"    D   ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__, "no-name",
           (const char *)"   D    ",
           (const char *)" ...555 ",
           (const char *)" .....5 ",
           (const char *)"D.....5 ",
           (const char *)" 555...D",
           (const char *)"    D 5 ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__, "no-name",
           (const char *)"   D    ",
           (const char *)" ...555 ",
           (const char *)" .....5 ",
           (const char *)"D.....5 ",
           (const char *)" 5....5 ",
           (const char *)" 555...D",
           (const char *)"    D 5 ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__, "no-name",
           (const char *)"     D   ",
           (const char *)" ..55.55 ",
           (const char *)" ......5 ",
           (const char *)"D......5 ",
           (const char *)" 5.....5 ",
           (const char *)" 555....D",
           (const char *)"    D  5 ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__, "no-name",
           (const char *)"     D    ",
           (const char *)" ..55.555 ",
           (const char *)" .......5 ",
           (const char *)"D.......5 ",
           (const char *)" 5......5 ",
           (const char *)" 555.....D",
           (const char *)"    D   5 ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__, "no-name",
           (const char *)"     D     ",
           (const char *)" ..55.5555 ",
           (const char *)" ........5 ",
           (const char *)"D........5 ",
           (const char *)" 5.......5 ",
           (const char *)" 555.5....D",
           (const char *)"    D 5555 ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__, "no-name",
           (const char *)"        D   ",
           (const char *)" .....55.55 ",
           (const char *)" .........5 ",
           (const char *)"D.........5 ",
           (const char *)" 5........5 ",
           (const char *)" 555.5..5..D",
           (const char *)"    D 55 55 ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__, "no-name",
           (const char *)"  D     ",
           (const char *)" 5..... ",
           (const char *)" 5..... ",
           (const char *)"D......5",
           (const char *)" 5.....5",
           (const char *)" 5....5 ",
           (const char *)" 555...D",
           (const char *)"    D 5 ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__, "no-name",
           (const char *)"   D    ",
           (const char *)" 55.....",
           (const char *)" 5......",
           (const char *)"D.......",
           (const char *)" 5......",
           (const char *)" 5....5 ",
           (const char *)" 5....5 ",
           (const char *)" 555...D",
           (const char *)"    D . ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__, "no-name",
           (const char *)"   D   ",
           (const char *)" 5.....",
           (const char *)" 5.....",
           (const char *)" 5.....",
           (const char *)"D......",
           (const char *)" 5...5 ",
           (const char *)" 5...5 ",
           (const char *)" 5...5 ",
           (const char *)" 5....D",
           (const char *)"  D    ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__, "no-name",
           (const char *)"   D   ",
           (const char *)" ...55 ",
           (const char *)" ....5 ",
           (const char *)" ..    ",
           (const char *)" ..    ",
           (const char *)" ..... ",
           (const char *)" ..... ",
           (const char *)" ..... ",
           (const char *)" ..... ",
           (const char *)"D..... ",
           (const char *)" 5.... ",
           (const char *)" 5.... ",
           (const char *)" 5.... ",
           (const char *)" 5....D",
           (const char *)"  D    ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__, "no-name",
           (const char *)"   D   ",
           (const char *)" ...55 ",
           (const char *)" ....5 ",
           (const char *)" ..... ",
           (const char *)"   ... ",
           (const char *)"   c..c",
           (const char *)" ..cCCc",
           (const char *)" ..c..c",
           (const char *)" ..... ",
           (const char *)"D..... ",
           (const char *)" 5.... ",
           (const char *)" 5.... ",
           (const char *)" 5.... ",
           (const char *)" 5....D",
           (const char *)"  D    ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__, "no-name",
           (const char *)"   D    ",
           (const char *)" ...55  ",
           (const char *)" ....5  ",
           (const char *)" .....  ",
           (const char *)" .....  ",
           (const char *)" .....  ",
           (const char *)"  ..... ",
           (const char *)"  ..... ",
           (const char *)"  ..... ",
           (const char *)"D...... ",
           (const char *)"  5.... ",
           (const char *)"  5.... ",
           (const char *)"  5.... ",
           (const char *)"  5....D",
           (const char *)"   D    ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__, "no-name",
           (const char *)"   D         ",
           (const char *)" 5.......... ",
           (const char *)" 5..........D",
           (const char *)" 5.......... ",
           (const char *)"D....5555    ",
           (const char *)" 5...5       ",
           (const char *)" 5...5       ",
           (const char *)" 5...5       ",
           (const char *)" 5.555       ",
           (const char *)"  D          ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__, "no-name",
           (const char *)"  D     ",
           (const char *)" 5..... ",
           (const char *)" 5..... ",
           (const char *)" 5..... ",
           (const char *)"D......5",
           (const char *)" ......5",
           (const char *)"5.....5 ",
           (const char *)"5...... ",
           (const char *)" 5.555.D",
           (const char *)"  D     ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__, "no-name",
           (const char *)"    D     ",
           (const char *)"   5.555  ",
           (const char *)"   5....5 ",
           (const char *)"  5.....5 ",
           (const char *)"D.......5 ",
           (const char *)"  5.....5 ",
           (const char *)".........D",
           (const char *)".......55 ",
           (const char *)".....55   ",
           (const char *)"    D     ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__, "no-name",
           (const char *)"    D     ",
           (const char *)"   5..... ",
           (const char *)"  5...... ",
           (const char *)" 5....... ",
           (const char *)"D........ ",
           (const char *)" 555..... ",
           (const char *)"    5....D",
           (const char *)"     5..5 ",
           (const char *)"     5.5  ",
           (const char *)"      D   ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__, "no-name",
           (const char *)"    D     ",
           (const char *)"  55.55.. ",
           (const char *)" 5....... ",
           (const char *)" 5....... ",
           (const char *)"D........ ",
           (const char *)" 5....... ",
           (const char *)"  5......D",
           (const char *)"  5....55 ",
           (const char *)"   5.55   ",
           (const char *)"    D     ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__, "no-name",
           (const char *)"    D   55",
           (const char *)"  ...555.5",
           (const char *)"  .......5",
           (const char *)"  ......5 ",
           (const char *)"D.......5 ",
           (const char *)"  5.....5 ",
           (const char *)"  5......D",
           (const char *)" 5.5...55 ",
           (const char *)"5.5 .55   ",
           (const char *)"55  D     ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__, "no-name",
           (const char *)" D           ",
           (const char *)" ..........  ",
           (const char *)" 5.........  ",
           (const char *)" 5.........5 ",
           (const char *)"D..........5 ",
           (const char *)" 55........5 ",
           (const char *)"  5.........D",
           (const char *)"  5........5 ",
           (const char *)"   5.555555  ",
           (const char *)"    D        ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__, "no-name",
           (const char *)" D           ",
           (const char *)" .555        ",
           (const char *)" ...5   5555 ",
           (const char *)"  5.55  5..5 ",
           (const char *)"D.....cc...5 ",
           (const char *)"  5..5  5..5 ",
           (const char *)"  5..5  5...D",
           (const char *)"  5..5  5555 ",
           (const char *)"   5.5       ",
           (const char *)"    D        ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__, "no-name",
           (const char *)"D........555 ",
           (const char *)" ..55.......5",
           (const char *)"    CCc.....5",
           (const char *)"   CCCCc..cC ",
           (const char *)"    CCc....5 ",
           (const char *)"D..55.......D",
           (const char *)" .........5  ",
           (const char *)" 5...55555   ",
           (const char *)"    D        ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__, "no-name",
           (const char *)"D.........   ",
           (const char *)" 555........ ",
           (const char *)"    5ccc.... ",
           (const char *)"     CCCc... ",
           (const char *)"     CCc.... ",
           (const char *)" 5555cc..... ",
           (const char *)"D...........D",
           (const char *)" 5........5  ",
           (const char *)"  5.....5    ",
           (const char *)"    D        ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__, "no-name",
           (const char *)"     D       ",
           (const char *)"  5.....5    ",
           (const char *)" 5........5  ",
           (const char *)"D...cccc....D",
           (const char *)" 5..cCCc.... ",
           (const char *)"D...cccc....D",
           (const char *)" 5........5  ",
           (const char *)"  5.....5    ",
           (const char *)"    D        ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__, "no-name",
           (const char *)"     D       ",
           (const char *)"  5....5  .. ",
           (const char *)" 5......cc.. ",
           (const char *)"D.....CCCc   ",
           (const char *)" 5.....CCCc. ",
           (const char *)"D...........D",
           (const char *)" 5........5  ",
           (const char *)"  5.....5    ",
           (const char *)"    D        ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__, "no-name",
           (const char *)"         D   ",
           (const char *)"         ..5 ",
           (const char *)"         ... ",
           (const char *)"   5........ ",
           (const char *)"D........... ",
           (const char *)"  5......... ",
           (const char *)"   55555....D",
           (const char *)"       5.... ",
           (const char *)"       5.... ",
           (const char *)"       55... ",
           (const char *)"           D ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__, "no-name",
           (const char *)"         D   ",
           (const char *)"         ..5 ",
           (const char *)"         ... ",
           (const char *)"          c  ",
           (const char *)"          c  ",
           (const char *)"          c  ",
           (const char *)"         ... ",
           (const char *)"         ... ",
           (const char *)"   5........ ",
           (const char *)"D........... ",
           (const char *)"  5......... ",
           (const char *)"   55555....D",
           (const char *)"           D ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__, "no-name",
           (const char *)"         D   ",
           (const char *)"  ....   ..5 ",
           (const char *)"  ....cCc... ",
           (const char *)"  ....    .  ",
           (const char *)"  ....    c  ",
           (const char *)"          .  ",
           (const char *)"         ... ",
           (const char *)"         ... ",
           (const char *)"   5........ ",
           (const char *)"D........... ",
           (const char *)"  5......... ",
           (const char *)"   55555....D",
           (const char *)"           D ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__, "no-name",
           (const char *)"         D   ",
           (const char *)"   ........5 ",
           (const char *)"   c........ ",
           (const char *)"    cc.......",
           (const char *)"     cC......",
           (const char *)"     cCC.....",
           (const char *)"     cCCCcCCc",
           (const char *)"    cC.......",
           (const char *)"   5.........",
           (const char *)"D............",
           (const char *)"  5......... ",
           (const char *)"   55555....D",
           (const char *)"           D ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__, "no-name",
           (const char *)"         D   ",
           (const char *)"        5..55",
           (const char *)"       5....5",
           (const char *)"     55.....5",
           (const char *)"    5.......5",
           (const char *)"   5.......5 ",
           (const char *)"   5.CCc...5 ",
           (const char *)"      CCc....",
           (const char *)"   5.CCc.....",
           (const char *)"D....cc......",
           (const char *)"  5......... ",
           (const char *)"   55555....D",
           (const char *)"           D ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__, "no-name",
           (const char *)"         D   ",
           (const char *)"        5..5 ",
           (const char *)" 5     55... ",
           (const char *)"D..... ..... ",
           (const char *)" 5....c..... ",
           (const char *)" 55... .....D",
           (const char *)"        D    ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__, "no-name",
           (const char *)"         D   ",
           (const char *)"        5..5 ",
           (const char *)"        5... ",
           (const char *)"D..... ..... ",
           (const char *)" 5....c..... ",
           (const char *)" 5.... ..... ",
           (const char *)" 5...   .... ",
           (const char *)" 55..   ....D",
           (const char *)"   D         ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__, "no-name",
           (const char *)"         D   ",
           (const char *)"        5..5 ",
           (const char *)"        5... ",
           (const char *)"D........... ",
           (const char *)" 5.......... ",
           (const char *)" 5.......... ",
           (const char *)" 5.......... ",
           (const char *)" 55.........D",
           (const char *)"   D         ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__, "no-name",
           (const char *)"    D    D   ",
           (const char *)"  5..5  5..5 ",
           (const char *)"  ...5  5... ",
           (const char *)"D........... ",
           (const char *)" 5.......... ",
           (const char *)" 55.........D",
           (const char *)"        D    ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__, "no-name",
           (const char *)"         D   ",
           (const char *)" 55......... ",
           (const char *)" 5.........5 ",
           (const char *)"D..........5 ",
           (const char *)" 5.........5 ",
           (const char *)" 55.........D",
           (const char *)"        D    ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__, "no-name",
           (const char *)"         D   ",
           (const char *)" 55.........D",
           (const char *)" 5.........5 ",
           (const char *)"D..........5 ",
           (const char *)" 5.   .....5 ",
           (const char *)" 55   ....55 ",
           (const char *)"        D    ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__, "no-name",
           (const char *)"         D   ",
           (const char *)"       5...  ",
           (const char *)"      5....  ",
           (const char *)"     5...... ",
           (const char *)"     5...... ",
           (const char *)"   55....... ",
           (const char *)"D........... ",
           (const char *)"   ......... ",
           (const char *)"   .........D",
           (const char *)"   ......... ",
           (const char *)"   ......... ",
           (const char *)"   5........ ",
           (const char *)"           D ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__, "no-name",
           (const char *)"         D   ",
           (const char *)"     5555..  ",
           (const char *)"     5.....  ",
           (const char *)"     5...... ",
           (const char *)"     5...... ",
           (const char *)"   55....... ",
           (const char *)"D........... ",
           (const char *)"   .........D",
           (const char *)"   5........ ",
           (const char *)"           D ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__, "no-name",
           (const char *)"             D  ",
           (const char *)"     5555.....  ",
           (const char *)"     5........  ",
           (const char *)"     5......... ",
           (const char *)"     5......... ",
           (const char *)"   55.......... ",
           (const char *)"D.............. ",
           (const char *)"   ............D",
           (const char *)"   5........... ",
           (const char *)"      5...5   D ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__, "no-name",
           (const char *)"             D     ",
           (const char *)"     5555......55  ",
           (const char *)"     5..........5  ",
           (const char *)"     5...........5 ",
           (const char *)"     5............ ",
           (const char *)"   55.............D",
           (const char *)"D..............5   ",
           (const char *)"   ............    ",
           (const char *)"   5...........    ",
           (const char *)"      5...5   D    ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__, "no-name",
           (const char *)"             D        ",
           (const char *)"     5555.........5   ",
           (const char *)"     5.............5  ",
           (const char *)"     5............... ",
           (const char *)"     5............... ",
           (const char *)"   55................D",
           (const char *)"D..............5      ",
           (const char *)"   ............       ",
           (const char *)"   5...........       ",
           (const char *)"      5...5   D       ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__, "no-name",
           (const char *)"     D          ",
           (const char *)"  55...5        ",
           (const char *)" 5......5       ",
           (const char *)" 5.......5....  ",
           (const char *)" 5............  ",
           (const char *)"5............5  ",
           (const char *)"5.............5 ",
           (const char *)"5.............5 ",
           (const char *)" 5...........5  ",
           (const char *)" 5...........5  ",
           (const char *)" 5...........5  ",
           (const char *)"D..............D",
           (const char *)" 5..........55  ",
           (const char *)"  5.....5       ",
           (const char *)"    D           ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__, "no-name",
           (const char *)"         D         ",
           (const char *)"  55......5        ",
           (const char *)" 5.........5       ",
           (const char *)" 5..........5....  ",
           (const char *)" 5...............  ",
           (const char *)"5...............5  ",
           (const char *)"5................5 ",
           (const char *)"5................5 ",
           (const char *)" 5..............5  ",
           (const char *)" 5..............5  ",
           (const char *)" 5..............5  ",
           (const char *)"D.................D",
           (const char *)" 5.............55  ",
           (const char *)"  5........5       ",
           (const char *)"    D              ",
           nullptr);

  room_add(g, __FUNCTION__, __LINE__, "no-name",
           (const char *)"             D        ",
           (const char *)"     5555.........5   ",
           (const char *)"     5.............5  ",
           (const char *)"     5............... ",
           (const char *)"     5............... ",
           (const char *)"   55................D",
           (const char *)" 5...............     ",
           (const char *)"5...............5     ",
           (const char *)"5................5    ",
           (const char *)"5................5    ",
           (const char *)" 5..............5     ",
           (const char *)" 5..............5     ",
           (const char *)" 5..............5     ",
           (const char *)"D.................D   ",
           (const char *)" 5.............55     ",
           (const char *)"  5........5          ",
           (const char *)"    D                 ",
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
