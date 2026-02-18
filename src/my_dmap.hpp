//
// Copyright goblinhack@gmail.com
//

#pragma once
#ifndef _MY_DMAP_HPP_
#define MY_DMAP_HPP_

#include "my_game.hpp"
#include "my_game_defs.hpp"
#include "my_spoint.hpp"

#include <vector>

using Dmap = struct Dmap_ {
  //
  // memset is used to initialize this, so be careful if changing the size
  //
  unsigned char val[ MAP_WIDTH ][ MAP_HEIGHT ];
};

void dmap_process(Dmap *D, spoint tl, spoint br);
void dmap_process_reverse(Dmap *D, spoint tl, spoint br);
void dmap_print(const Dmap *d, spoint at, spoint start, spoint end);
void dmap_print(const Dmap *d);

[[nodiscard]] std::vector< spoint > dmap_solve(Gamep g, Levelsp v, Levelp l, Thingp t, const Dmap *d, spoint start);

#define DMAP_IS_WALL         ((unsigned char) 255)
#define DMAP_IS_PASSABLE     ((unsigned char) 254)
#define DMAP_IS_GOAL_REVERSE ((unsigned char) 252)
#define DMAP_IS_GOAL         ((unsigned char) 0)

#endif
