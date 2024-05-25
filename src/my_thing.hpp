//
// Copyright Neil McGill, goblinhack@gmail.com
//

#pragma once
#ifndef _MY_THING_HPP_
#define _MY_THING_HPP_

#include "my_enums.hpp"
#include "my_minimal.hpp"
#include "my_point.hpp"   // does not seem to make the compile speed much worse
#include "my_point3d.hpp" // does not seem to make the compile speed much worse

//
// Entropy is always > 0 for Thing IDs to distinguish them
// A thing ID is composed as: // [ Entropy bits] [ ID bits ]
//
#define THING_COMMON_ID_ENTROPY_BITS    6
#define THING_COMMON_ID_BITS            16
#define THING_COMMON_ID_BASE            (1U << (THING_COMMON_ID_BITS))
#define THING_COMMON_ID_ENTROPY_MASK    (((1U << THING_COMMON_ID_ENTROPY_BITS) - 1) << THING_COMMON_ID_BITS)
#define THING_COMMON_ID_MASK            ((1U << THING_COMMON_ID_BITS) - 1)
#define THING_COMMON_ID_GET_ENTROPY(id) ((id & THING_COMMON_ID_ENTROPY_MASK) >> THING_COMMON_ID_BITS)
#define THING_COMMON_ID_GET(id)         (id & THING_COMMON_ID_MASK)

//
// Essentially equates to the max number of monsters
//
#define THING_AI_MAX        65535 /* sizeof ai_id */
#define THING_MOVE_PATH_MAX (MAP_WIDTH * MAP_HEIGHT)

typedef struct ThingAi_ {
  //
  // Unique ID
  //
  uint8_t in_use : 1;
  struct {
    point   points[ THING_MOVE_PATH_MAX ];
    int16_t size;
  } move_path;
} ThingAi;

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
  point3d at;
  //
  // Old map co-ords used for interpolation when moving.
  //
  point3d old_at;
  //
  // Direction
  //
  uint8_t dir;
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
} Thing;

Tpp thing_tp(Thingp t);

Thingp thing_and_tp_get(Levelp, point3d, int slot, Tpp * = nullptr);
Thingp thing_find(Levelp, ThingId id);
Thingp thing_find_optional(Levelp, ThingId id);
Thingp thing_get(Levelp, point3d, int slot);
Thingp thing_init(Levelp, Tpp, point3d);
Thingp thing_player(Levelp);

ThingAip thing_ai(Levelp, Thingp);

void thing_dir_bl_set(Thingp, uint8_t);
void thing_dir_br_set(Thingp, uint8_t);
void thing_dir_down_set(Thingp, uint8_t);
void thing_dir_left_set(Thingp, uint8_t);
void thing_dir_right_set(Thingp, uint8_t);
void thing_dir_tl_set(Thingp, uint8_t);
void thing_dir_tr_set(Thingp, uint8_t);
void thing_dir_up_set(Thingp, uint8_t);
void thing_fini(Levelp, Thingp);
void thing_interpolate(Levelp, Thingp, float dt);
void thing_move(Levelp, Thingp, point3d to);
void thing_player_map_center(Levelp);
void thing_player_move_accum(Levelp, bool up, bool down, bool left, bool right);
void thing_player_move_delta(Levelp, int dx, int dy, int dz);
void thing_player_move_reset(Levelp);
void thing_pop(Levelp, Thingp);
void thing_push(Levelp, Thingp);
void thing_set_dir_from_delta(Thingp, int dx, int dy);
void thing_update(Levelp, Thingp);

bool thing_can_move_to(Levelp, Thingp, point3d to);
bool thing_player_move_request(Levelp, bool up, bool down, bool left, bool right);
bool thing_is_dir_down(Thingp t);
bool thing_is_dir_tr(Thingp t);
bool thing_is_dir_tl(Thingp t);
bool thing_is_dir_br(Thingp t);
bool thing_is_dir_bl(Thingp t);
bool thing_is_dir_left(Thingp t);
bool thing_is_dir_right(Thingp t);
bool thing_is_dir_up(Thingp t);

#endif
