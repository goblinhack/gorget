//
// Copyright Neil McGill, goblinhack@gmail.com
//

#pragma once
#ifndef _MY_LEVEL_DATA_H_
#define _MY_LEVEL_DATA_H_

#include <array>
#include <inttypes.h>

#include "my_depth.hpp"
#include "my_fwd.hpp"
#include "my_game_defs.hpp"
#include "my_point.hpp"
#include "my_thing.hpp"
#include "my_thing_id.hpp"

//
// Simple things like walls that do not change much
//
typedef struct ThingOrTp_ {
  //
  // The thing template index
  //
  Id id;
  //
  // Layers of tiles, used in walls. Only layer 0 is animated.
  //
  uint16_t tile;
  //
  // Count down until the next animation frame should start
  //
  int16_t anim_ms_remaining;
  //
  // The current tiles[] index for this object
  //
  uint8_t anim_index;
  //
  // Direction of tile decorations. Multiple directions can be set at the
  // same time for rocks as this is used for rock decorations.
  //
  uint8_t dir_up    : 1;
  uint8_t dir_down  : 1;
  uint8_t dir_left  : 1;
  uint8_t dir_right : 1;
  uint8_t dir_tl    : 1;
  uint8_t dir_tr    : 1;
  uint8_t dir_bl    : 1;
  uint8_t dir_br    : 1;
} ThingOrTp;

typedef struct LevelData_ {
  //////////////////////////////////////////////////////////////
  // No c++ types can be used here, to allow easy level replay
  //////////////////////////////////////////////////////////////

  //
  // Level number
  //
  uint8_t num;

  //
  // Map scroll offset
  //
  int16_t pixel_map_at_x;
  int16_t pixel_map_at_y;

  ThingOrTp obj[ MAP_WIDTH ][ MAP_HEIGHT ][ MAP_SLOTS ];

  Thing things[ 1 << THING_ID_X_BITS ][ 1 << THING_ID_Y_BITS ];

  ThingId player;

  //////////////////////////////////////////////////////////////
  // No c++ types can be used here, to allow easy level replay
  //////////////////////////////////////////////////////////////
} LevelData;

LevelDatap level_data_constructor(void);
void       level_data_destructor(LevelDatap);

bool is_oob(LevelData *, point p);

Thingp thing_find_optional(LevelData *, ThingId);
Thingp thing_find(LevelData *, ThingId);
Thingp thing_new(LevelData *, Tpp, point);
Thingp thing_get(LevelData *, point p, uint8_t slot, Tpp * = nullptr);

void thing_free(LevelData *, Thingp);
void thing_push(LevelData *, Thingp);
void thing_pop(LevelData *, Thingp);

Tpp  tp_get(LevelData *, point p, uint8_t slot);
void tp_set(LevelData *, point p, Tpp);

#endif // _MY_LEVEL_DATA_H_
