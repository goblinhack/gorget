//
// Copyright Neil McGill, goblinhack@gmail.com
//

#pragma once
#ifndef _MY_LEVEL_H_
#define _MY_LEVEL_H_

#include "my_game_defs.hpp"
#include "my_minimal.hpp"
#include "my_thing.hpp"

enum {
  CURSOR_NONE,
  CURSOR_PATH,
  CURSOR_AT,
};

typedef struct Level_ {
  //////////////////////////////////////////////////////////////
  // No c++ types can be used here, to allow easy level replay
  //
  // Why C types only ? For large data structures it is visibly
  // faster to malloc and memset versus default construction.
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
  bool tick_begin_requested : 1;
  bool tick_end_requested   : 1;
  //
  // If the player has moved, we need to scroll the map
  //
  bool requested_auto_scroll : 1;
  //
  // Player move request.
  //
  bool requested_move_left  : 1;
  bool requested_move_keft  : 1;
  bool requested_move_right : 1;
  bool requested_move_up    : 1;
  //
  // The user has pressed the mouse and wants to follow the mouse path.
  //
  bool request_follow_path : 1;
  //
  // set when the player starts following the mouse path.
  //
  bool is_following_a_path : 1;
  //
  // TODO
  // Set when something modifies the map and we need to update caches.
  //
  bool is_map_changed : 1;
  //
  // What things are where? Each Id points to a thing structure.
  //
  ThingId thing_id[ MAP_WIDTH ][ MAP_HEIGHT ][ MAP_DEPTH ][ MAP_SLOTS ];
  //
  // All things structure memory.
  //
  Thing thing_body[ 1 << THING_COMMON_ID_BITS ];
  //
  // Space for player and monster AI
  //
  ThingAi thing_ai[ THING_AI_MAX ];
  //
  // The current player.
  //
  ThingId player;
  //
  // Which player are we controlling.
  //
  uint8_t player_index;
  //
  // Has the player been on this tile?
  //
  bool is_walked[ MAP_WIDTH ][ MAP_HEIGHT ][ MAP_DEPTH ];
  //
  // What the player is currently highlighting.
  //
  uint8_t cursor[ MAP_WIDTH ][ MAP_HEIGHT ];
  point   cursor_at;
  point   old_cursor_at;
  //
  // Map scroll offset.
  //
  point pixel_map_at;
  //
  // Level display bounds
  //
  int minx;
  int miny;
  int maxx;
  int maxy;
  //////////////////////////////////////////////////////////////
  // No c++ types can be used here, to allow easy level replay
  //////////////////////////////////////////////////////////////
} Level;

Levelp level_new(void);

ThingId level_get_thing_id(Levelp, point3d, int slot);

bool level_flag(Levelp, ThingFlag, point3d);
bool level_is_oob(Levelp, point);
bool level_is_oob(Levelp, point3d);
bool level_is_same_type(Levelp, point3d, Tpp);
bool level_set_thing_id(Levelp, point3d, int slot, ThingId);
bool level_tick_is_in_progress(Levelp);

void level_anim(Levelp);
void level_assign_tiles(Levelp, int z);
void level_bounds_set(Levelp);
void level_cursor_set(Levelp, point);
void level_cursor_update(Levelp);
void level_display(Levelp);
void level_dungeon_create_and_place(Levelp, int z);
void level_fini(Levelp);
void level_map_set(Levelp, int z, const char *);
void level_mouse_position_get(Levelp);
void level_scroll_delta(Levelp, point);
void level_cursor_path_reset(Levelp);
void level_scroll_to_player(Levelp);
void level_scroll_warp_to_player(Levelp);
void level_tick_begin_requested(Levelp, const char *);
void level_tick(Levelp);

//
// Walk all things on all Z depths
//
#define FOR_ALL_THINGS_ALL_DEPTHS(_l_, _t_)                                                                          \
  Thingp t;                                                                                                          \
  for (auto _id_ = 0; _id_ < 1 << THING_COMMON_ID_BITS; _id_++)                                                      \
    if (_l_->thing_body[ _id_ ].id)                                                                                  \
      if ((_t_ = thing_find_optional(_l_, _l_->thing_body[ _id_ ].id)))

//
// For all things at this Z depth
//
#define FOR_ALL_THINGS_Z_DEPTH(_l_, _t_, _z_)                                                                        \
  Thingp _t_;                                                                                                        \
  Tpp    _tp_;                                                                                                       \
  for (auto _y_ = 0; _y_ < MAP_HEIGHT; _y_++)                                                                        \
    for (auto _x_ = 0; _x_ < MAP_WIDTH; _x_++)                                                                       \
      for (auto _slot_ = 0; _t_ = thing_and_tp_get(_l_, point3d(_x_, _y_, _z_), _slot_, &_tp_), _slot_ < MAP_SLOTS;  \
           _slot_++)                                                                                                 \
        if (_t_)

//
// For all things at a specific location
//
#define FOR_ALL_THINGS_AT(_l_, _t_, _p_)                                                                             \
  Thingp _t_;                                                                                                        \
  for (auto _slot_ = 0; _t_ = thing_get(_l_, _p_, _slot_), _slot_ < MAP_SLOTS; _slot_++)                             \
    if (_t_)

#define FOR_ALL_THINGS_AND_TPS_AT(_l_, _t_, _tp_, _p_)                                                               \
  Thingp _t_;                                                                                                        \
  Tpp    _tp_;                                                                                                       \
  for (auto _slot_ = 0; _t_ = thing_and_tp_get(_l_, _p_, _slot_, &_tp_), _slot_ < MAP_SLOTS; _slot_++)               \
    if (_t_)

#endif // _MY_LEVEL_H_
