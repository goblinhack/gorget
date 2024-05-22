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
  // TODO
  // Set when something modifies the map and we need to update caches.
  //
  bool is_map_changed : 1;
  //
  // What things are where? Each Id points to a thing structure.
  //
  ThingId thing_id[ MAP_WIDTH ][ MAP_HEIGHT ][ MAP_DEPTH ][ MAP_SLOTS ];
  //
  // All thing structure memory.
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
  int     cursor_x;
  int     cursor_y;
  int     old_cursor_x;
  int     old_cursor_y;
  //
  // Map scroll offset.
  //
  int pixel_map_at_x;
  int pixel_map_at_y;
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

// begin sort marker1 {
bool    level_is_oob(Levelp, int x, int y);
bool    level_is_oob(Levelp, int x, int y, int z);
bool    level_is_same_type(Levelp, int x, int y, int z, Tpp);
bool    level_set_thing_id(Levelp, int x, int y, int z, int slot, ThingId);
bool    level_thing_can_move_to(Levelp, Thingp, int new_loc_x, int new_loc_y, int new_loc_z);
bool    level_thing_player_move_request(Levelp, bool up, bool down, bool left, bool right);
bool    level_tick_is_in_progress(Levelp);
Levelp  level_constructor(void);
ThingId level_get_thing_id(Levelp, int x, int y, int z, int slot);
Thingp  level_thing_and_tp_get(Levelp, int x, int y, int z, int slot, Tpp  * = nullptr);
Thingp  level_thing_find(Levelp, ThingId id);
Thingp  level_thing_find_optional(Levelp, ThingId id);
Thingp  level_thing_get(Levelp, int x, int y, int z, int slot);
Thingp  level_thing_init(Levelp, Tpp, int x, int y, int z);
Thingp  level_thing_new(Levelp, Tpp, int x, int y, int z);
Thingp  level_thing_player(Levelp);
Tpp     level_thing_tp(Levelp, Thingp);
void    level_anim(Levelp);
void    level_assign_tiles(Levelp, int z);
void    level_bounds_set(Levelp);
void    level_cursor_update(Levelp);
void    level_destructor(Levelp);
void    level_display(Levelp);
void    level_dungeon_create_and_place(Levelp, int z);
void    level_map_set(Levelp, int z, const char *);
void    level_mouse_position_get(Levelp);
void    level_scroll_delta(Levelp, int, int);
void    level_scroll_to_player(Levelp);
void    level_scroll_warp_to_player(Levelp);
void    level_thing_free(Levelp, Thingp);
void    level_thing_interpolate(Levelp, Thingp, float dt);
void    level_thing_move(Levelp, Thingp, int new_x, int new_y, int new_z);
void    level_thing_player_map_center(Levelp);
void    level_thing_player_move_accum(Levelp, bool up, bool down, bool left, bool right);
void    level_thing_player_move_delta(Levelp, int dx, int dy, int dz);
void    level_thing_player_move_reset(Levelp);
void    level_thing_pop(Levelp, Thingp);
void    level_thing_push(Levelp, Thingp);
void    level_thing_update(Levelp, Thingp);
void    level_tick_begin(Levelp);
void    level_tick_begin_requested(Levelp, const char *);
void    level_tick_body(Levelp, float dt);
void    level_tick_end_requested(Levelp);
void    level_tick(Levelp);
void    level_tick_time_step(Levelp);
// end sort marker1 }

bool level_flag(Levelp, ThingFlag, int x, int y, int z);

void level_cursor_set(Levelp, int x, int y);

//
// Works on a copy of the level data, so things can move cells and we never
// walk anything twice.
//
#define FOR_ALL_THINGS(_l_, _t_)                                                                                     \
  static Level _l_copy_;                                                                                             \
  _l_copy_ = *_l_;                                                                                                   \
  Thingp t;                                                                                                          \
  for (auto _id_ = 0; _id_ < 1 << THING_COMMON_ID_BITS; _id_++)                                                      \
    if (_l_copy_.thing_body[ _id_ ].id)                                                                              \
      if ((_t_ = level_thing_find_optional(_l_, _l_copy_.thing_body[ _id_ ].id)))

#define FOR_ALL_THINGS_AT(_l_, _t_, _x_, _y_, _z_)                                                                   \
  Thingp _t_;                                                                                                        \
  for (auto _slot_ = 0; _t_ = level_thing_get(_l_, _x_, _y_, _z_, _slot_), _slot_ < MAP_SLOTS; _slot_++)             \
    if (_t_)

#define FOR_ALL_THINGS_AND_TPS_AT(_l_, _t_, _tp_, _x_, _y_, _z_)                                                     \
  Thingp _t_;                                                                                                        \
  Tpp    _tp_;                                                                                                       \
  for (auto _slot_ = 0; _t_ = level_thing_and_tp_get(_l_, _x_, _y_, _z_, _slot_, &_tp_), _slot_ < MAP_SLOTS;         \
       _slot_++)                                                                                                     \
    if (_t_)

#endif // _MY_LEVEL_H_
