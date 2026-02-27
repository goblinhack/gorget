//
// Copyright goblinhack@gmail.com
//

#ifndef MY_CAVE_HPP
#define MY_CAVE_HPP

#include "my_game_defs.hpp"
#include "my_types.hpp"

//
// Cellular automata helpers
//
using Blob = struct Blob {
  //
  // Keeps track of the largest blob so fat
  //
  uint8_t largest_at_x;
  uint8_t largest_at_y;
  int     largest_size;

  //
  // Unique id per blob
  //
  uint16_t id[ MAP_WIDTH ][ MAP_HEIGHT ];
};

enum { MAP_LEVEL_CELLULAR_BORDER = 2 };

using Cave = struct Cave {
  //
  // Used for cellular automata
  //
  uint8_t curr[ MAP_WIDTH + (MAP_LEVEL_CELLULAR_BORDER * 2) ][ MAP_HEIGHT + (MAP_LEVEL_CELLULAR_BORDER * 2) ];
  uint8_t prev[ MAP_WIDTH + (MAP_LEVEL_CELLULAR_BORDER * 2) ][ MAP_HEIGHT + (MAP_LEVEL_CELLULAR_BORDER * 2) ];

  //
  // Keeps track of the largest blob so fat
  //
  Blob blob;
};

void cave_dump(Gamep g, Cave *c);
void cave_create(Gamep g, Cave *c, uint32_t fill_prob, uint8_t r1, uint8_t r2, int map_generations);
auto cave_generation_fill_blob_cand(Gamep g, Cave *c, int x, int y, uint16_t size, uint16_t id) -> int;
void cave_generation_keep_largest_blob(Gamep g, Cave *c);
void cave_generation_center_blob(Gamep g, Cave *c);

#endif // MY_CAVE_HPP
