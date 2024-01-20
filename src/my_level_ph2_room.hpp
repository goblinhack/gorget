//
// Copyright Neil McGill, goblinhack@gmail.com
//

#pragma once
#ifndef _MY_LEVEL_PH2_ROOM_HPP_
#define _MY_LEVEL_PH2_ROOM_HPP_

#include <array>
#include <string>

#include "my_fwd.hpp"
#include "my_game_defs.hpp"
#include "my_level_ph2_room.hpp"

using LevelPh2Rooms = std::vector< LevelPh2Roomp >;

typedef enum {
  ROOM_TYPE_MAP,
  ROOM_TYPE_NORMAL,
  ROOM_TYPE_ENTRANCE,
  ROOM_TYPE_EXIT,
  ROOM_TYPE_KEY,
  ROOM_TYPE_LOCK,
  ROOM_TYPE_SECRET,
  ROOM_TYPE_MAX,
} RoomType;

class LevelPh2Room
{
private:
public:
  static LevelPh2Rooms all_rooms_of_type[ ROOM_TYPE_MAX ];
  static LevelPh2Rooms all_rooms;

  LevelPh2Room(void);
  ~LevelPh2Room(void);

  //
  // Unique per room.
  //
  uint32_t roomno {0};
  RoomType type;
  uint8_t  width {LEVEL_PH2_ROOM_WIDTH};
  uint8_t  height {LEVEL_PH2_ROOM_HEIGHT};

  std::array< std::array< char, LEVEL_PH2_ROOM_HEIGHT >, LEVEL_PH2_ROOM_WIDTH > data {};

  uint16_t exits_up {};
  uint16_t exits_down {};
  uint16_t exits_left {};
  uint16_t exits_right {};

  LevelPh2Roomp flip(void);
  void          dump(void);
};

void level_ph2_init(void);
void level_ph2_fini(void);
void level_ph2_room_set_add(RoomType, const char *);

LevelPh2Roomp room_new(void);

#endif
