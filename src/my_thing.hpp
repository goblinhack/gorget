//
// Copyright Neil McGill, goblinhack@gmail.com
//

#pragma once
#ifndef _MY_THING_HPP_
#define _MY_THING_HPP_

#include "my_minimal.hpp"

#define THING_ID_ENTROPY_BITS 6
#define THING_ID_X_BITS       5
#define THING_ID_Y_BITS       5

//
// IDs below this are for templates
//
#define THING_ID_BASE (1U << (THING_ID_X_BITS + THING_ID_Y_BITS))

//
// A thing ID is composed like:
// [ Entropy bits] [ X bits ] [ Y bits]
//
#define THING_ID_ENTROPY_MASK (((1U << THING_ID_ENTROPY_BITS) - 1) << (THING_ID_X_BITS + THING_ID_Y_BITS))
#define THING_ID_X_MASK       (((1U << THING_ID_X_BITS) - 1) << THING_ID_Y_BITS)
#define THING_ID_Y_MASK       ((1U << THING_ID_Y_BITS) - 1)

#define THING_ID_GET_ENTROPY(id) ((id & THING_ID_ENTROPY_MASK) >> (THING_ID_X_BITS + THING_ID_Y_BITS))
#define THING_ID_GET_X(id)       ((id & THING_ID_X_MASK) >> (THING_ID_Y_BITS))
#define THING_ID_GET_Y(id)       ((id & THING_ID_Y_MASK))

struct Thing {
  ThingId  id;
  uint16_t tp_id;
  uint16_t tick;
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
  // Move speed, with 100 being normal. Updated at start of tick.
  //
  int16_t speed;
  //
  // Increases per tick and when it reaches 1, allows the thing to move
  //
  float thing_dt;
  //
  // Interpolated co-ords in pixels
  //
  int16_t pix_x;
  int16_t pix_y;
  uint8_t dir_up    : 1;
  uint8_t dir_down  : 1;
  uint8_t dir_left  : 1;
  uint8_t dir_right : 1;
};

using Thingp = struct Thing *;

#endif
