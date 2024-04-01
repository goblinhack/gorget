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
  // Level number.
  //
  uint8_t num;

  //
  // Increments once per event loop.
  //
  uint32_t frame;

  //
  // Tick increases one per player move.
  //
  uint32_t tick;

  //
  // When the tick began in ms
  //
  uint32_t frame_begin;

  //
  // Ranges from 0 to 1 when a tick is in progress.
  //
  float time_step;
  float last_time_step;

  //
  // We have to interpolate movement and this indicates that is in progress.
  //
  uint8_t tick_in_progress : 1;

  //
  // Player has moved.
  //
  bool _tick_begin_requested : 1;
  bool _tick_end_requested   : 1;

  //
  // Player move request.
  //
  bool requested_move_left  : 1;
  bool requested_move_keft  : 1;
  bool requested_move_right : 1;
  bool requested_move_up    : 1;

  //
  // Map scroll offset.
  //
  int16_t pixel_map_at_x;
  int16_t pixel_map_at_y;

  ThingOrTp obj[ MAP_WIDTH ][ MAP_HEIGHT ][ MAP_SLOTS ];

  //
  // All thing structure memory.
  //
  Thing all_things[ 1 << THING_ID_X_BITS ][ 1 << THING_ID_Y_BITS ];

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

//
// Works on a copy of the level data, so things can move cells and we never
// walk anything twice.
//
#define FOR_ALL_THINGS(_data_, _t_)                                                                                  \
  static LevelData _data_copy_;                                                                                      \
  _data_copy_ = *_data_;                                                                                             \
  Thingp t;                                                                                                          \
  for (auto _x_ = 0; _x_ < 1 << THING_ID_X_BITS; _x_++)                                                              \
    for (auto _y_ = 0; _y_ < 1 << THING_ID_Y_BITS; _y_++)                                                            \
      if (_data_copy_.all_things[ _x_ ][ _y_ ].id)                                                                   \
        if ((_t_ = ::thing_find_optional(_data_, _data_copy_.all_things[ _x_ ][ _y_ ].id)))

#define FOR_ALL_TPS_AT(_data_, _t_, _tp_, _p_)                                                                       \
  Tpp _tp_;                                                                                                          \
  for (auto _slot_ = 0; ::thing_get(_data_, _p_, _slot_, &_tp_), _slot_ < MAP_SLOTS; _slot_++)                       \
    if (_tp_)

#define FOR_ALL_THINGS_AT(_data_, _t_, _tp_, _p_)                                                                    \
  Thingp _t_;                                                                                                        \
  Tpp    _tp_;                                                                                                       \
  for (auto _slot_ = 0; _t_ = ::thing_get(_data_, _p_, _slot_, &_tp_), _slot_ < MAP_SLOTS; _slot_++)                 \
    if (_tp_)

LevelDatap level_data_constructor(void);
void       level_data_destructor(LevelDatap);

bool thing_can_move(LevelData *, Thingp, point new_loc);
bool is_oob(LevelData *, point p);

Thingp thing_find(LevelData *, ThingId);
Thingp thing_find_optional(LevelData *, ThingId);
Thingp thing_get(LevelData *, point p, uint8_t slot, Tpp * = nullptr);
Thingp thing_new(LevelData *, Tpp, point);
Thingp thing_init(LevelData *, Tpp, point);

Tpp thing_tp(LevelData *, Thingp);
Tpp tp_get(LevelData *, point p, uint8_t slot);

void thing_move(LevelData *, Thingp, point new_loc);
void thing_free(LevelData *, Thingp);
void thing_pop(LevelData *, Thingp);
void thing_push(LevelData *, Thingp);
void thing_update(LevelData *, Thingp);
void tp_set(LevelData *, point p, Tpp);
void tp_unset(LevelData *, point p, Tpp);

#endif // _MY_LEVEL_DATA_H_
