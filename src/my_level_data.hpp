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
  // Tick increases one per player move
  //
  uint32_t tick;

  //
  // When the tick began in ms
  //
  uint32_t tick_start;

  //
  // We have to interpolate movement and this indicates that is in progress
  //
  uint8_t tick_in_progress : 1;

  //
  // Player has moved.
  //
  uint8_t tick_start_requested : 1;
  uint8_t tick_end_requested   : 1;

  //
  // Map scroll offset
  //
  int16_t pixel_map_at_x;
  int16_t pixel_map_at_y;

  ThingOrTp obj[ MAP_WIDTH ][ MAP_HEIGHT ][ MAP_SLOTS ];

  Thing things[ 1 << THING_ID_X_BITS ][ 1 << THING_ID_Y_BITS ];

  //
  // The current player.
  //
  ThingId player;

  //
  // Which player are we controlling.
  //
  uint8_t player_index;

  //////////////////////////////////////////////////////////////
  // No c++ types can be used here, to allow easy level replay
  //////////////////////////////////////////////////////////////
} LevelData;

LevelDatap level_data_constructor(void);
void       level_data_destructor(LevelDatap);

bool is_oob(LevelData *, point p);

Thingp thing_find(LevelData *, ThingId);
Thingp thing_find_optional(LevelData *, ThingId);
Thingp thing_get(LevelData *, point p, uint8_t slot, Tpp * = nullptr);
Thingp thing_new(LevelData *, Tpp, point);
Thingp thing_init(LevelData *, Tpp, point);

Tpp thing_tp(LevelData *, Thingp);
Tpp tp_get(LevelData *, point p, uint8_t slot);

void thing_free(LevelData *, Thingp);
void thing_pop(LevelData *, Thingp);
void thing_push(LevelData *, Thingp);
void thing_update(LevelData *, Thingp);
void tp_set(LevelData *, point p, Tpp);
void tp_unset(LevelData *, point p, Tpp);

#endif // _MY_LEVEL_DATA_H_
