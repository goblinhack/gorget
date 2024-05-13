//
// Copyright Neil McGill, goblinhack@gmail.com
//

#pragma once
#ifndef _MY_THING_HPP_
#define _MY_THING_HPP_

#include "my_enums.hpp"
#include "my_minimal.hpp"

#define THING_ID_ENTROPY_BITS 6
#define THING_ID_BITS         16

//
// IDs below this are for templates
//
// Entropy is always > 0 for Thing IDs to distinguish them
//
#define THING_ID_BASE (1U << (THING_ID_BITS))

//
// A thing ID is composed like:
// [ Entropy bits] [ X bits ] [ Y bits]
//
#define THING_ID_ENTROPY_MASK (((1U << THING_ID_ENTROPY_BITS) - 1) << THING_ID_BITS)
#define THING_ID_MASK         ((1U << THING_ID_BITS) - 1)

#define THING_ID_GET_ENTROPY(id) ((id & THING_ID_ENTROPY_MASK) >> THING_ID_BITS)
#define THING_ID_GET(id)         (id & THING_ID_MASK)

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

typedef struct Thing_ {
  //
  // Unique ID
  //
  ThingId id;
  //
  // Map co-ords.
  //
  int8_t x;
  int8_t y;
  //
  // Old map co-ords used for interpolation when moving.
  //
  int8_t old_x;
  int8_t old_y;
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
  int16_t pix_x;
  int16_t pix_y;
  //
  // Increases per tick and when it reaches 1, allows the thing to move
  //
  float thing_dt;
  //
  // Keeps track of counters in the level this thing has modified.
  //
  uint8_t count[ THING_FLAG_MAX ];
} Thing;

Tpp      tp(Thingp t);
bool     thing_is_dir_down(Thingp t);
bool     thing_is_dir_tr(Thingp t);
bool     thing_is_dir_tl(Thingp t);
bool     thing_is_dir_br(Thingp t);
bool     thing_is_dir_bl(Thingp t);
bool     thing_is_dir_left(Thingp t);
bool     thing_is_dir_right(Thingp t);
bool     thing_is_dir_up(Thingp t);
float    thing_thing_dt_get(Thingp t);
int16_t  thing_pix_x_get(Thingp t);
int16_t  thing_pix_y_get(Thingp t);
int16_t  thing_speed_get(Thingp t);
int8_t   thing_old_x_get(Thingp t);
int8_t   thing_old_y_get(Thingp t);
int8_t   thing_x_get(Thingp t);
int8_t   thing_y_get(Thingp t);
ThingId  thing_id_get(Thingp t);
uint16_t thing_tick_get(Thingp t);
uint16_t thing_tp_id_get(Thingp t);
void     thing_dir_tr_set(Thingp t, uint8_t);
void     thing_dir_tl_set(Thingp t, uint8_t);
void     thing_dir_br_set(Thingp t, uint8_t);
void     thing_dir_bl_set(Thingp t, uint8_t);
void     thing_dir_down_set(Thingp t, uint8_t);
void     thing_dir_left_set(Thingp t, uint8_t);
void     thing_dir_right_set(Thingp t, uint8_t);
void     thing_dir_up_set(Thingp t, uint8_t);
void     thing_id_set(Thingp t, ThingId id);
void     thing_old_x_set(Thingp t, int8_t old_x);
void     thing_old_y_set(Thingp t, int8_t old_y);
void     thing_pix_x_set(Thingp t, int16_t pix_x);
void     thing_pix_y_set(Thingp t, int16_t pix_y);
void     thing_speed_set(Thingp t, int16_t speed);
void     thing_thing_dt_set(Thingp t, float thing_dt);
void     thing_tick_set(Thingp t, uint16_t tick);
void     thing_tp_id_set(Thingp t, uint16_t tp_id);
void     thing_x_set(Thingp t, int8_t x);
void     thing_y_set(Thingp t, int8_t y);
void     thing_set_dir_from_delta(Thingp, int dx, int dy);

#endif
