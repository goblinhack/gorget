//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_charmap.hpp"
#include "my_level.hpp"
#include "my_main.hpp"
#include "my_ptrcheck.hpp"
#include <stdarg.h>
#include <vector>

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
  // For keeping track of which rooms we add
  //
  const char *file = {};
  int         line = {};
};

static int                         room_no;
static std::vector< class Room * > rooms;

static class Room *room_rotate(Gamep g, class Room *r)
{
  TRACE_NO_INDENT();

  auto n = new Room();
  rooms.push_back(n);

  n->room_no = r->room_no;
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
  return n;
}

static class Room *room_flip_horiz(Gamep g, class Room *r)
{
  TRACE_NO_INDENT();

  auto n = new Room();
  rooms.push_back(n);

  n->room_no = r->room_no;
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

  return n;
}

//
// Add a room and copies with all possible rotations
//
static void room_add(Gamep g, const char *file, int line, const char *lines, ...)
{
  TRACE_NO_INDENT();

  va_list ap;
  int     room_width  = 0;
  int     room_height = 0;

  //
  // First scan, get width and height
  //
  va_start(ap, lines);

  for (;;) {
    char *room_line = va_arg(ap, char *);
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
        ERR("room has inconsistent width in room %s:%d", file, line);
        return;
      }
    }

    //
    // Check the room contents are known characters
    //
    for (auto i = 0; i < room_width; i++) {
      switch (room_line[ i ]) {
        case CHARMAP_CHASM :
        case CHARMAP_DOOR :
        case CHARMAP_EMPTY :
        case CHARMAP_FLOOR :
        case CHARMAP_EXIT :
        case CHARMAP_KEY :
        case CHARMAP_MONST1 :
        case CHARMAP_PLAYER :
        case CHARMAP_TREASURE :
        case CHARMAP_WALL : break;
        default : ERR("room has unknown char [%c] in room %s:%d", room_line[ i ], file, line); return;
      }
    }

    room_height++;
  }

  va_end(ap);

  //
  // Check the room sizes
  //
  if (! room_width) {
    ERR("room has no width in room %s:%d", file, line);
    return;
  }
  if (! room_height) {
    ERR("room has no height in room %s:%d", file, line);
    return;
  }
  if (room_width >= MAP_WIDTH) {
    ERR("room is too wide in room %s:%d", file, line);
    return;
  }
  if (room_height >= MAP_HEIGHT) {
    ERR("room is too tall in room %s:%d", file, line);
    return;
  }

  //
  // Allocate space for the room
  //
  class Room *r = new Room();
  rooms.push_back(r);

  r->room_no = ++room_no;
  r->file    = file;
  r->line    = line;
  r->width   = room_width;
  r->height  = room_height;
  r->data    = (char *) myzalloc(room_width * room_height, "room data");

  //
  // Now read the room again
  //
  va_start(ap, lines);

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
}

static void room_dump(Gamep g, class Room *r)
{
  TRACE_NO_INDENT();

  LOG("Room %d, %s:%d", r->room_no, r->file, r->line);
  for (int y = 0; y < r->height; y++) {
    std::string tmp;
    for (int x = 0; x < r->width; x++) {
      tmp += r->data[ (y * r->width) + x ];
    }
    LOG("[%s]", tmp.c_str());
  }
  LOG("-");
}

static void rooms_dump(Gamep g)
{
  TRACE_NO_INDENT();

  for (auto r : rooms) {
    room_dump(g, r);
  }
}

void rooms_fini(Gamep g)
{
  TRACE_NO_INDENT();

  for (auto r : rooms) {
    delete r;
  }
}

void rooms_init(Gamep g)
{
  TRACE_NO_INDENT();

  /* clang-format off */
  room_add(g, __FUNCTION__, __LINE__,
           (const char *)"      D   ",
           (const char *)"    ..... ",
           (const char *)"D........ ",
           (const char *)"    ..... ",
           (const char *)"    .....D",
           (const char *)"    ..... ",
           (const char *)"       D  ",
           nullptr);
  /* clang-format on */
}

void rooms_test(Gamep g)
{
  TRACE_NO_INDENT();
  rooms_dump(g);
}
