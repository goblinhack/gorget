//
// Copyright goblinhack@gmail.com
//

#pragma once
#ifndef _MY_CAVE_H_
#define _MY_CAVE_H_

#include "my_game_defs.hpp"
#include "my_types.hpp"

//
// Cellular automata helpers
//
typedef struct {
  //
  // Keeps track of the largest blob so fat
  //
  uint8_t  largest_at_x;
  uint8_t  largest_at_y;
  uint16_t largest_size;

  //
  // Unique id per blob
  //
  uint16_t id[ MAP_WIDTH ][ MAP_HEIGHT ];
} Blob;

#define MAP_LEVEL_CELLULAR_BORDER 2

typedef struct {
  //
  // Used for cellular automata
  //
  uint8_t curr[ MAP_WIDTH + MAP_LEVEL_CELLULAR_BORDER * 2 ][ MAP_HEIGHT + MAP_LEVEL_CELLULAR_BORDER * 2 ];
  uint8_t prev[ MAP_WIDTH + MAP_LEVEL_CELLULAR_BORDER * 2 ][ MAP_HEIGHT + MAP_LEVEL_CELLULAR_BORDER * 2 ];

  //
  // Keeps track of the largest blob so fat
  //
  Blob blob;
} Cave;

void cave_dump(Gamep, Cave *);
void cave_create(Gamep, Cave *, uint32_t fill_prob, int r1, int r2, int map_generations);
int  cave_generation_fill_blob_cand(Gamep, Cave *c, int x, int y, uint16_t size, uint16_t id);
void cave_generation_keep_largest_blob(Gamep, Cave *c);
void cave_generation_center_blob(Gamep, Cave *c);

#endif // _MY_LEVEL_H_
