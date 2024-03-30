//
// Copyright Neil McGill, goblinhack@gmail.com
//

#pragma once
#ifndef _MY_THING_HPP_
#define _MY_THING_HPP_

#include "my_sys.hpp"
#include "my_thing_id.hpp"

struct Thing {
  ThingId  id;
  uint16_t tp_id;
  uint16_t tick;
  //
  // Map co-ords
  //
  int8_t x;
  int8_t y;
  //
  // Old map co-ords
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
