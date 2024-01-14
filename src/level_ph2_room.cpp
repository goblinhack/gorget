//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include <string.h>

#include "my_array_bounds_check.hpp"
#include "my_charmap.hpp"
#include "my_level_ph2_room.hpp"
#include "my_ptrcheck.hpp"

LevelPh2Rooms LevelPh2Room::all_rooms_of_type[ ROOM_TYPE_MAX ];
LevelPh2Rooms LevelPh2Room::all_rooms;

void level_ph2_init(void) { TRACE_NO_INDENT(); }

void level_ph2_fini(void)
{
  TRACE_NO_INDENT();
  for (auto &r : LevelPh2Room::all_rooms) {
    delete r;
  }
}

LevelPh2Room::LevelPh2Room(void)
{
  TRACE_NO_INDENT();
  this->roomno = all_rooms.size();
  newptr(MTYPE_ROOM, this, "room");
}

LevelPh2Room::~LevelPh2Room(void)
{
  TRACE_NO_INDENT();
  oldptr(MTYPE_ROOM, this);
}

LevelPh2Roomp LevelPh2Room::flip(void)
{
  TRACE_NO_INDENT();
  auto f = new LevelPh2Room();

  f->type        = type;
  f->exits_up    = 0;
  f->exits_down  = 0;
  f->exits_left  = exits_right;
  f->exits_right = exits_left;

  //
  // Bit reverse
  //
  for (auto x = 0; x < LEVEL_PH2_ROOM_WIDTH; x++) {
    if (exits_up & (1 << x)) {
      f->exits_up |= 1 << (LEVEL_PH2_ROOM_WIDTH - x - 1);
    }
    if (exits_down & (1 << x)) {
      f->exits_down |= 1 << (LEVEL_PH2_ROOM_WIDTH - x - 1);
    }
  }

  for (auto x = 0; x < LEVEL_PH2_ROOM_WIDTH; x++) {
    for (auto y = 0; y < LEVEL_PH2_ROOM_HEIGHT; y++) {
      auto c = get(data, x, y);
      set(f->data, LEVEL_PH2_ROOM_WIDTH - x - 1, y, c);
    }
  }

  return f;
}

void LevelPh2Room::dump(void)
{
  TRACE_NO_INDENT();

  LOG("LevelPh2Roomno: %u", roomno);

  std::array< std::array< char, LEVEL_PH2_ROOM_WIDTH >, LEVEL_PH2_ROOM_HEIGHT > out {};

  for (auto ry = 0; ry < LEVEL_PH2_ROOM_HEIGHT; ry++) {
    for (auto rx = 0; rx < LEVEL_PH2_ROOM_WIDTH; rx++) {
      auto c = get(data, rx, ry);
      set(out, rx, ry, c);
    }
  }

  for (auto y = 0; y < LEVEL_PH2_ROOM_HEIGHT; y++) {
    std::string s;
    for (auto x = 0; x < LEVEL_PH2_ROOM_WIDTH; x++) {
      auto c = get(out, x, y);
      if (c) {
        s += c;
      } else {
        s += ' ';
      }
    }
    LOG("%s", s.c_str());
  }

  LOG("Exits left %x right %x up %x down %x", exits_left, exits_right, exits_up, exits_down);
  LOG("-");
}

LevelPh2Roomp room_new(void)
{
  TRACE_NO_INDENT();
  auto r = new LevelPh2Room();
  LevelPh2Room::all_rooms.push_back(r);
  return r;
}

void level_ph2_room_set_add(RoomType specified_type, const char *data)
{
  TRACE_NO_INDENT();
  const auto row_len      = (((LEVEL_PH2_ROOM_WIDTH + 1) * LEVEL_PH1_WIDTH) + 1);
  auto       expected_len = (row_len) * (((LEVEL_PH2_ROOM_HEIGHT + 1) * LEVEL_PH1_HEIGHT) + 1);

  if ((int) strlen(data) != expected_len) {
    DIE("bad room size, expected %d, got %d", (int) strlen(data), (int) expected_len);
  }

  //
  // Break the grid of rooms up into individual rooms
  //
  for (auto room_across = 0; room_across < LEVEL_PH1_WIDTH; room_across++) {
    for (auto room_down = 0; room_down < LEVEL_PH1_HEIGHT; room_down++) {
      auto r  = room_new();
      r->type = ROOM_TYPE_NORMAL;

      for (auto ry = 0; ry < LEVEL_PH2_ROOM_HEIGHT; ry++) {
        for (auto rx = 0; rx < LEVEL_PH2_ROOM_WIDTH; rx++) {
          auto offset = row_len + (((LEVEL_PH2_ROOM_HEIGHT + 1) * room_down) * row_len) + (row_len * ry)
                      + (room_across * (LEVEL_PH2_ROOM_WIDTH + 1)) + rx + 1;
          auto c = data[ offset ];

          switch (c) {
            case PH2_CHAR_ROCK : break;
            case PH2_CHAR_WILDCARD : break;
            case PH2_CHAR_WALL_100_PERCENT : break;
            case PH2_CHAR_WALL_50_PERCENT : break;
            case PH2_CHAR_SPIKE_33_PERCENT : break;
            case PH2_CHAR_OBSTACLE_GROUND : break;
            case PH2_CHAR_OBSTACLE_AIR : break;
            case PH2_CHAR_LADDER : break;
            case PH2_CHAR_ROCK_GOLD : break;
            case PH2_CHAR_BLOCK : break;
            case PH2_CHAR_CRYSTAL : break;
            case PH2_CHAR_TREASURE : break;
            case PH2_CHAR_MONST1 : break;
            case PH2_CHAR_ENTRANCE :
              if (r->type != ROOM_TYPE_NORMAL) {
                DIE("room type already set when trying to set entrance");
              }
              r->type = ROOM_TYPE_ENTRANCE;
              break;
            case PH2_CHAR_EXIT :
              if (r->type != ROOM_TYPE_NORMAL) {
                DIE("room type already set when trying to set as exit");
              }
              r->type = ROOM_TYPE_EXIT;
              break;
            case PH2_CHAR_LOCK :
              if ((r->type != ROOM_TYPE_NORMAL) && (r->type != ROOM_TYPE_LOCK)) {
                DIE("room type already set when trying to set as lock");
              }
              r->type = ROOM_TYPE_LOCK;
              break;
            case PH2_CHAR_KEY :
              if ((r->type != ROOM_TYPE_NORMAL) && (r->type != ROOM_TYPE_KEY)) {
                DIE("room type already set when trying to set as key");
              }
              r->type = ROOM_TYPE_KEY;
              break;
            case PH2_CHAR_SECRET_DOOR :
              if ((r->type != ROOM_TYPE_NORMAL) && (r->type != ROOM_TYPE_SECRET)) {
                DIE("room type already set when trying to set as secret");
              }
              r->type = ROOM_TYPE_SECRET;
              break;
            case PH2_CHAR_EMPTY : break;
            default : DIE("unexpected room char '%c'", c);
          }

          r->data[ rx ][ ry ] = c;

          if (rx == 0) {
            auto c = data[ offset - 1 ];
            if ((c == PH2_CHAR_CONNECTOR) || (c == PH2_CHAR_LEFT)) {
              r->exits_left |= 1U << (LEVEL_PH2_ROOM_HEIGHT - ry - 1);
            }
          } else if (rx == LEVEL_PH2_ROOM_WIDTH - 1) {
            auto c = data[ offset + 1 ];
            if ((c == PH2_CHAR_CONNECTOR) || (c == PH2_CHAR_RIGHT)) {
              r->exits_right |= 1U << (LEVEL_PH2_ROOM_HEIGHT - ry - 1);
            }
          }

          if (ry == 0) {
            auto c = data[ offset - row_len ];
            if ((c == PH2_CHAR_CONNECTOR) || (c == PH2_CHAR_UP)) {
              r->exits_up |= 1U << (LEVEL_PH2_ROOM_WIDTH - rx - 1);
            }
          } else if (ry == LEVEL_PH2_ROOM_HEIGHT - 1) {
            auto c = data[ offset + row_len ];
            if ((c == PH2_CHAR_CONNECTOR) || (c == PH2_CHAR_DOWN)) {
              r->exits_down |= 1U << (LEVEL_PH2_ROOM_WIDTH - rx - 1);
            }
          }
        }
      }

      if (r->type != specified_type) {
        DIE("room type does not match expected");
      }

      if (r->type != ROOM_TYPE_SECRET) {
        if (! r->exits_left && ! r->exits_right && ! r->exits_up && ! r->exits_down) {
          DIE("room %u has no exits", r->roomno);
        }
      }

      if (r->type == ROOM_TYPE_ENTRANCE) {
        r->exits_up = 0;
      }

      if (r->type == ROOM_TYPE_EXIT) {
        r->exits_down = 0;
      }

      LevelPh2Room::all_rooms_of_type[ r->type ].push_back(r);
      // r->dump();

      auto f = r->flip();
      LevelPh2Room::all_rooms_of_type[ f->type ].push_back(f);
      // f->dump();
    }
  }
}
