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
  int16_t  pix_x;
  int16_t  pix_y;
  int8_t   dx;
  int8_t   dy;
  uint8_t  dir_up    : 1;
  uint8_t  dir_down  : 1;
  uint8_t  dir_left  : 1;
  uint8_t  dir_right : 1;
};

using Thingp = struct Thing *;

#endif
