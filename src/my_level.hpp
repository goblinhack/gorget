//
// Copyright goblinhack@gmail.com
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
  // Where this level is in the bigger map
  //
  int level_num;
  //
  // Flags
  //
  uint8_t initialized : 1;
  //
  // What things are where? Each Id points to a thing structure.
  //
  ThingId thing_id[ MAP_WIDTH ][ MAP_HEIGHT ][ MAP_SLOTS ];
  //
  // Has the player been on this tile?
  //
  uint8_t is_walked[ MAP_WIDTH ][ MAP_HEIGHT ];
  //////////////////////////////////////////////////////////////
  // No c++ types can be used here, to allow easy level replay
  //////////////////////////////////////////////////////////////
} Level;

typedef struct Levels_ {
  //////////////////////////////////////////////////////////////
  // No c++ types can be used here, to allow easy level replay
  //
  // Why C types only ? For large data structures it is visibly
  // faster to malloc and memset versus default construction.
  //////////////////////////////////////////////////////////////
  //
  // Current level being played
  //
  int level_num;
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
  uint8_t tick_begin_requested : 1;
  uint8_t tick_end_requested   : 1;
  //
  // If the player has moved, we need to scroll the map
  //
  uint8_t requested_auto_scroll : 1;
  //
  // Player move request.
  //
  uint8_t requested_move_left  : 1;
  uint8_t requested_move_keft  : 1;
  uint8_t requested_move_right : 1;
  uint8_t requested_move_up    : 1;
  //
  // The user has pressed the mouse and wants to follow the mouse path.
  //
  uint8_t player_pressed_button_and_waiting_for_a_path : 1;
  //
  // set when the player starts following the mouse path.
  //
  uint8_t player_currently_following_a_path : 1;
  //
  // Set when something modifies the map and we need to update caches.
  //
  uint8_t is_map_changed : 1;
  //
  // Flag array of all levels. The levels equate to one tile in the level grid.
  //
  Level level[ MAX_LEVELS ];
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
  ThingId player_id;
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
  // Levels display bounds
  //
  int minx;
  int miny;
  int maxx;
  int maxy;
  //////////////////////////////////////////////////////////////
  // No c++ types can be used here, to allow easy level replay
  //////////////////////////////////////////////////////////////
} Levels;

#define FOR_ALL_LEVELS(_g_, _v_, _l_)                                                                                \
  for (auto _n_ = 0; _n_ < MAX_LEVELS; _n_++)                                                                        \
    if ((_l_ = &v->level[ _n_ ]))

//
// Walk all things, all levels
//
#define FOR_ALL_THINGS_ALL_LEVELS(_g_, _v_, _t_)                                                                     \
  Thingp t;                                                                                                          \
  for (auto _id_ = 0; _id_ < 1 << THING_COMMON_ID_BITS; _id_++)                                                      \
    if (_l_->thing_body[ _id_ ].id)                                                                                  \
      if ((_t_ = thing_find_optional(_l_, _l_->thing_body[ _id_ ].id)))

//
// For all things at this Z depth
//
#define FOR_ALL_THINGS_ON_LEVEL(_g_, _v_, _l_, _t_)                                                                  \
  Thingp _t_;                                                                                                        \
  Tpp    _tp_;                                                                                                       \
  for (auto _y_ = 0; _y_ < MAP_HEIGHT; _y_++)                                                                        \
    for (auto _x_ = 0; _x_ < MAP_WIDTH; _x_++)                                                                       \
      for (auto _slot_ = 0;                                                                                          \
           _t_ = thing_and_tp_get_at(_g_, _v_, _l_, point(_x_, _y_), _slot_, &_tp_), _slot_ < MAP_SLOTS; _slot_++)   \
        if (_t_)

//
// For all things at a specific location
//
#define FOR_ALL_THINGS_AT(_g_, _v_, _l_, _t_, _p_)                                                                   \
  Thingp _t_;                                                                                                        \
  for (auto _slot_ = 0; _t_ = thing_get(_g_, _v_, _l_, _p_, _slot_), _slot_ < MAP_SLOTS; _slot_++)                   \
    if (_t_)

#define FOR_ALL_THINGS_AND_TPS_AT(_g_, _v_, _l_, _t_, _tp_, _p_)                                                     \
  Thingp _t_;                                                                                                        \
  Tpp    _tp_;                                                                                                       \
  for (auto _slot_ = 0; _t_ = thing_and_tp_get_at(_g_, _v_, _l_, _p_, _slot_, &_tp_), _slot_ < MAP_SLOTS; _slot_++)  \
    if (_t_)

enum {
  CHANCE_VVV_UNLIKELY = 1,
  CHANCE_VV_UNLIKELY  = 10,
  CHANCE_V_UNLIKELY   = 100,
  CHANCE_UNLIKELY     = 1000,
  CHANCE_NORMAL       = 10000,
};

enum {
  NO_FLAGS             = 0,
  ROOM_CHECK_EXIT_FLAG = 1,
};

Levelsp levels_memory_alloc(Gamep);
void    levels_destroy(Gamep, Levelsp);
void    levels_stats_dump(Gamep g);

Levelp level_switch(Gamep, Levelsp, int);
void   level_destroy(Gamep, Levelsp, Levelp);

ThingId level_get_thing_id_at(Gamep, Levelsp, Levelp, point p, int slot);

bool is_oob(point);

bool level_flag(Gamep, Levelsp, Levelp, ThingFlag, point p);
bool level_is_same_obj_type_at(Gamep, Levelsp, Levelp, point p, Tpp);
bool level_set_thing_id_at(Gamep, Levelsp, Levelp, point p, int slot, ThingId);
bool level_tick_is_in_progress(Gamep, Levelsp, Levelp);

void level_anim(Gamep, Levelsp, Levelp);
void level_assign_tiles(Gamep, Levelsp, Levelp);
void level_bounds_set(Gamep, Levelsp);
void level_cursor_set(Gamep, Levelsp, point);
void level_cursor_update(Gamep, Levelsp, Levelp);
void level_display(Gamep, Levelsp, Levelp);
void level_map_set(Gamep, Levelsp, Levelp, const char *);
void level_mouse_position_get(Gamep, Levelsp, Levelp);
void level_scroll_delta(Gamep, Levelsp, point);
void level_cursor_path_reset(Gamep, Levelsp, Levelp);
void level_scroll_to_player(Gamep, Levelsp);
void level_scroll_warp_to_player(Gamep, Levelsp);
void level_tick_begin_requested(Gamep, Levelsp, Levelp, const char *);
void level_tick(Gamep, Levelsp, Levelp);

void grid_test(Gamep);

void rooms_test(Gamep);
void rooms_init(Gamep);
void rooms_fini(Gamep);
void room_add(Gamep, int chance, bool check, const char *file, int line, ...);
void rooms_blend1(Gamep);
void rooms_blend2(Gamep);
void rooms_chunky(Gamep);
void rooms_circular(Gamep);
void rooms_cross(Gamep);
void rooms_cross_sym(Gamep);
void rooms_small(Gamep);
void rooms_medium(Gamep);
void rooms_start(Gamep);
void rooms_exit(Gamep);
void rooms_prefab(Gamep);

void fragments_init(Gamep);
void fragments_fini(Gamep);
void fragment_alts_fini(Gamep);
bool fragment_add(Gamep, int chance, const char *file, int line, ...);
bool fragment_alt_add(Gamep, int chance, const char *file, int line, ...);

void level_gen_test(Gamep);
void level_gen_create_levels(Gamep);
void level_gen_stats_dump(Gamep);

#endif // _MY_LEVEL_H_
