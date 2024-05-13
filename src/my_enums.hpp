//
// Copyright Neil McGill, goblinhack@gmail.com
//

#pragma once
#ifndef _MY_ENUMS_HPP_
#define _MY_ENUMS_HPP_

#include "my_enum.hpp"

enum {
  TILE_LAYER_BG_0,
  TILE_LAYER_BG_1,
  TILE_LAYER_FG_0,
  TILE_LAYER_FG_1,
  TILE_LAYER_FG_2,
  TILE_LAYER_FG_3,
  TILE_LAYER_FG_4,
  TILE_LAYER_FG_5,
  TILE_LAYER_FG_6,
  TILE_LAYER_FG_7,
  TILE_LAYER_FG_8,
  TILE_LAYER_FG_9,
  TILE_LAYER_MAX,
};

enum {
  MAP_DEPTH_FLOOR,
  MAP_DEPTH_WALL,
  MAP_DEPTH_DOOR,
  MAP_DEPTH_OBJ1,
  MAP_DEPTH_OBJ2,
  MAP_DEPTH_PLAYER,
  MAP_DEPTH_CURSOR,
};

enum {
  THING_RARITY_COMMON,
  THING_RARITY_UNCOMMON,
  THING_RARITY_RARE,
  THING_RARITY_VERY_RARE,
  THING_RARITY_UNIQUE,
};

enum { MONST_CLASS_A, MONST_CLASS_MAX };

/* clang-format off */
#define THING_FLAG_ENUM(list_macro)                 \
  list_macro(is_wall,          "is_wall"),          \
  list_macro(is_door,          "is_door"),          \
  list_macro(is_cursor_hazard, "is_cursor_hazard"), \
  list_macro(THING_FLAG_MAX, "THING_FLAG_MAX"),

/* clang-format on */

ENUM_DEF_H(THING_FLAG_ENUM, ThingFlag)

#endif
