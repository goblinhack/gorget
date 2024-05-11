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

typedef struct Level_ {
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
  // If the player has moved, we need to scroll the map
  //
  bool requested_auto_scroll : 1;

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
  // What the player is currently highlighting.
  //
  uint8_t cursor[ MAP_WIDTH ][ MAP_HEIGHT ];

  //
  // The current player.
  //
  ThingId player;

  //
  // Which player are we controlling.
  //
  uint8_t player_index;

  //
  // Level display bounds
  //
  int16_t minx = {};
  int16_t miny = {};
  int16_t maxx = {};
  int16_t maxy = {};

  //////////////////////////////////////////////////////////////
  // No c++ types can be used here, to allow easy level replay
  //////////////////////////////////////////////////////////////
} Level;

// begin sort marker1 {
bool   level_is_oob(Levelp, int x, int y);
bool   level_is_same_type(Levelp, int x, int y, Tpp);
bool   level_set_id(Levelp, int x, int y, uint8_t z, Id);
bool   level_set_tile(Levelp, int x, int y, uint8_t z, Tilep);
bool   level_thing_can_move_to(Levelp, Thingp, int, int);
bool   level_thing_player_move_request(Levelp, bool up, bool down, bool left, bool right);
bool   level_tick_is_in_progress(Levelp);
Id     level_get_id(Levelp, int x, int y, uint8_t z);
Id     level_get_id_no_check(Levelp, int x, int y, uint8_t z);
Levelp level_constructor(void);
Thingp level_thing_find(Levelp, ThingId id);
Thingp level_thing_find_optional(Levelp, ThingId id);
Thingp level_thing_init(Levelp, Tpp, int x, int y);
Thingp level_thing_new(Levelp, Tpp, int x, int y);
Thingp level_thing_or_tp_get(Levelp, int x, int y, uint8_t slot, Tpp * = nullptr);
Thingp level_thing_player(Levelp);
Tilep  level_get_tile(Levelp, int x, int y, uint8_t z);
Tilep  level_get_tile_no_check(Levelp, int x, int y, uint8_t z);
Tpp    level_thing_tp(Levelp, Thingp);
void   level_anim(Levelp);
void   level_assign_tiles(Levelp);
void   level_bounds_set(Levelp);
void   level_cursor_reset(Levelp);
void   level_destructor(Levelp);
void   level_display(Levelp);
void   level_dungeon_create_and_place(Levelp);
void   level_map_set(Levelp, const char *);
void   level_scroll_delta(Levelp, int, int);
void   level_scroll_to_player(Levelp);
void   level_scroll_warp_to_player(Levelp);
void   level_set_id_no_check(Levelp, int x, int y, uint8_t z, Id);
void   level_set_tile_no_check(Levelp, int x, int y, uint8_t z, Tilep);
void   level_thing_free(Levelp, Thingp);
void   level_thing_interpolate(Levelp, Thingp, float dt);
void   level_thing_move(Levelp, Thingp, int, int);
void   level_thing_player_create_and_place(Levelp);
void   level_thing_player_map_center(Levelp);
void   level_thing_player_move_accum(Levelp, bool up, bool down, bool left, bool right);
void   level_thing_player_move_delta(Levelp, int, int);
void   level_thing_player_move_reset(Levelp);
void   level_thing_pop(Levelp, Thingp);
void   level_thing_push(Levelp, Thingp);
void   level_thing_update(Levelp, Thingp);
void   level_tick_begin(Levelp);
void   level_tick_begin_requested(Levelp, const char *);
void   level_tick_body(Levelp, float dt);
void   level_tick_end_requested(Levelp);
void   level_tick(Levelp);
void   level_tick_time_step(Levelp);
// end sort marker1 }

Tpp  level_tp_get(Levelp, int x, int y, uint8_t slot);
void level_tp_set(Levelp, int x, int y, Tpp);
void level_tp_unset(Levelp, int x, int y, Tpp);

int  level_cursor_get(Levelp, int x, int y);
void level_cursor_set(Levelp, int x, int y, int);
void level_cursor_unset(Levelp, int x, int y, int);

//
// Works on a copy of the level data, so things can move cells and we never
// walk anything twice.
//
#define FOR_ALL_THINGS(_l_, _t_)                                                                                     \
  static Level _l_copy_;                                                                                             \
  _l_copy_ = *_l_;                                                                                                   \
  Thingp t;                                                                                                          \
  for (auto _x_ = 0; _x_ < 1 << THING_ID_X_BITS; _x_++)                                                              \
    for (auto _y_ = 0; _y_ < 1 << THING_ID_Y_BITS; _y_++)                                                            \
      if (_l_copy_.all_things[ _x_ ][ _y_ ].id)                                                                      \
        if ((_t_ = level_thing_find_optional(_l_, _l_copy_.all_things[ _x_ ][ _y_ ].id)))

#define FOR_ALL_TPS_AT(_l_, _t_, _tp_, _x_, _y_)                                                                     \
  Tpp _tp_;                                                                                                          \
  for (auto _slot_ = 0; level_thing_or_tp_get(_l_, _x_, _y_, _slot_, &_tp_), _slot_ < MAP_SLOTS; _slot_++)           \
    if (_tp_)

#define FOR_ALL_THINGS_AT(_l_, _t_, _tp_, _x_, _y_)                                                                  \
  Thingp _t_;                                                                                                        \
  Tpp    _tp_;                                                                                                       \
  for (auto _slot_ = 0; _t_ = level_thing_or_tp_get(_l_, _x_, _y_, _slot_, &_tp_), _slot_ < MAP_SLOTS; _slot_++)     \
    if (_tp_)

#endif // _MY_LEVEL_H_
