//
// Copyright goblinhack@gmail.com
//

#pragma once
#ifndef _MY_THING_HPP_
#define _MY_THING_HPP_

#include "my_game_defs.hpp"
#include "my_minimal.hpp"
#include "my_point.hpp" // does not seem to make the compile speed much worse
#include "my_tp.hpp"    // does not seem to make the compile speed much worse

//
// Entropy is always > 0 for Thing IDs to distinguish them
// A thing ID is composed as: [ Entropy bits] [ ID bits ]
//
#define THING_COMMON_ID_ENTROPY_BITS    6
#define THING_COMMON_ID_BITS            21
#define THING_COMMON_ID_BASE            (1U << (THING_COMMON_ID_BITS))
#define THING_COMMON_ID_ENTROPY_MASK    (((1U << THING_COMMON_ID_ENTROPY_BITS) - 1) << THING_COMMON_ID_BITS)
#define THING_COMMON_ID_MASK            ((1U << THING_COMMON_ID_BITS) - 1)
#define THING_COMMON_ID_GET_ENTROPY(id) ((id & THING_COMMON_ID_ENTROPY_MASK) >> THING_COMMON_ID_BITS)
#define THING_COMMON_ID_GET(id)         (id & THING_COMMON_ID_MASK)

//
// Essentially equates to the max number of monsters
//
#define THING_AI_MAX        65535 /* The size of thing_ai */
#define THING_MOVE_PATH_MAX (MAP_WIDTH * 4)

enum {
  THING_RARITY_COMMON,
  THING_RARITY_UNCOMMON,
  THING_RARITY_RARE,
  THING_RARITY_VERY_RARE,
  THING_RARITY_UNIQUE,
};

enum {
  THING_DIR_NONE,
  THING_DIR_DOWN,
  THING_DIR_UP,
  THING_DIR_LEFT,
  THING_DIR_RIGHT,
  THING_DIR_TL,
  THING_DIR_BL,
  THING_DIR_TR,
  THING_DIR_BR,
};

//
// Per thing AI memory
//
typedef struct ThingAi_ {
  uint8_t in_use : 1;
} ThingAi;

//
// Player specific memory
//
typedef struct ThingPlayer_ {
  struct {
    point   points[ THING_MOVE_PATH_MAX ];
    int16_t size;
  } move_path;
} ThingPlayer;

typedef struct Thing_ {
  //////////////////////////////////////////////////////////////
  // No c++ types can be used here, to allow easy level replay
  //
  // Why C types only ? For large data structures it is visibly
  // faster to malloc and memset versus default construction.
  //////////////////////////////////////////////////////////////
  //
  // Unique ID
  //
  ThingId id;
  //
  // For players and monsters
  //
  ThingAiId ai_id;
  //
  // Map co-ords.
  //
  point at;
  //
  // Which level am I on?
  //
  LevelNum level_num;
  //
  // Previous map co-ords. Does not change when the move finishes.
  //
  point old_at;
  //
  // Previous map co-ords used for interpolation when moving. Changes when
  // the move finishes.
  //
  point moving_from;
  //
  // Last location we were pushed onto the map.
  //
  point last_pushed_at;
  //
  // Direction
  //
  uint8_t dir;
  //
  // Idle etc...
  //
  uint8_t anim_class;
  //
  // The current tiles[] index for this object
  //
  uint8_t anim_index;
  //
  // Current tile.
  //
  uint16_t tile_index;
  //
  // Count down until the next animation frame should start
  //
  int16_t anim_ms_remaining;
  //
  // Move speed, with 100 being normal. Updated at start of tick.
  //
  int16_t speed;
  //
  // Template ID
  //
  uint16_t tp_id;
  //
  // Current game tick this thing has completed
  //
  uint16_t tick;
  //
  // Interpolated co-ords in pixels
  //
  point pix_at;
  //
  // Increases per tick and when it reaches 1, allows the thing to move
  //
  float thing_dt;
  //
  // Keeps track of counters in the level this thing has modified.
  //
  uint8_t count[ THING_FLAG_MAX ];
  //
  // Pushed onto the map?
  //
  bool is_on_map : 1;
  bool is_moving : 1;
} Thing;

Tpp thing_tp(Thingp t);

Thingp thing_and_tp_get_at(Gamep, Levelsp, Levelp, point p, int slot, Tpp * = nullptr);
Thingp thing_find(Gamep, Levelsp, ThingId id);
Thingp thing_find_optional(Gamep, Levelsp, ThingId id);
Thingp thing_get(Gamep, Levelsp, Levelp, point p, int slot);
Thingp thing_init(Gamep, Levelsp, Levelp, Tpp, point p);
Thingp thing_player(Gamep);
Levelp thing_level(Gamep, Levelsp, Thingp);
void   thing_stats_dump(Gamep, Levelsp);

ThingAip     thing_ai(Gamep, Thingp);
ThingPlayerp thing_player(Gamep, Thingp);

void thing_dir_bl_set(Thingp, uint8_t);
void thing_dir_br_set(Thingp, uint8_t);
void thing_dir_down_set(Thingp, uint8_t);
void thing_dir_left_set(Thingp, uint8_t);
void thing_dir_right_set(Thingp, uint8_t);
void thing_dir_tl_set(Thingp, uint8_t);
void thing_dir_tr_set(Thingp, uint8_t);
void thing_dir_up_set(Thingp, uint8_t);
void thing_fini(Gamep, Levelsp, Levelp, Thingp);
void thing_interpolate(Gamep, Thingp, float dt);
void thing_player_map_center(Gamep, Levelsp, Levelp);
void thing_player_move_accum(Gamep, Levelsp, Levelp, bool up, bool down, bool left, bool right);
void thing_player_move_delta(Gamep, Levelsp, Levelp, int dx, int dy, int dz);
void thing_player_move_reset(Gamep, Levelsp, Levelp);
void thing_move_finish(Gamep, Levelsp, Levelp, Thingp);
void thing_tick_end(Gamep, Levelsp, Levelp, Thingp);
void thing_tick_idle(Gamep, Levelsp, Levelp, Thingp);
void thing_tick_begin(Gamep, Levelsp, Levelp, Thingp);
void thing_pop(Gamep, Levelsp, Thingp);
void thing_push(Gamep, Levelsp, Levelp, Thingp);
void thing_set_dir_from_delta(Thingp, int dx, int dy);
void thing_level_change(Gamep, Levelsp, Levelp, Thingp);
void thing_update_pos(Gamep, Thingp);

bool thing_can_move_to(Gamep, Levelsp, Levelp, Thingp, point to);
bool thing_move_to_next(Gamep, Levelsp, Levelp, Thingp t);
bool thing_player_move_request(Gamep, bool up, bool down, bool left, bool right);
bool thing_is_dir_down(Thingp t);
bool thing_is_dir_tr(Thingp t);
bool thing_move_to(Gamep, Levelsp, Levelp, Thingp, point to);
bool thing_warp_to(Gamep, Levelsp, Levelp, Thingp, point to);
bool thing_is_dir_tl(Thingp t);
bool thing_is_dir_br(Thingp t);
bool thing_is_dir_bl(Thingp t);
bool thing_is_dir_left(Thingp t);
bool thing_is_dir_right(Thingp t);
bool thing_is_dir_up(Thingp t);

#endif
