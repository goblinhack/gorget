//
// Copyright goblinhack@gmail.com
//

#ifndef MY_DMAP_HPP
#define MY_DMAP_HPP

#include "my_bpoint.hpp"
#include "my_game.hpp"
#include "my_game_defs.hpp"

#include <vector>

using Dmap = struct Dmap {
  //
  // memset is used to initialize this, so be careful if changing the size
  //
  uint8_t val[ MAP_WIDTH ][ MAP_HEIGHT ];
};

void dmap_process(Dmap *D, bpoint tl, bpoint br);
void dmap_process_reverse(Dmap *D, bpoint tl, bpoint br);
void dmap_print(const Dmap *d, bpoint at, bpoint tl, bpoint br);
void dmap_print(const Dmap *d);

[[nodiscard]] auto dmap_solve(Gamep g, Levelsp v, Levelp l, Thingp t, const Dmap *d, bpoint start) -> std::vector< bpoint >;

#define DMAP_IS_WALL         ((uint8_t) 255)
#define DMAP_IS_PASSABLE     ((uint8_t) 254)
#define DMAP_IS_GOAL_REVERSE ((uint8_t) 252)
#define DMAP_IS_GOAL         ((uint8_t) 0)

#endif
