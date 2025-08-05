//
// Copyright goblinhack@gmail.com
//

#pragma once
#ifndef _MY_DMAP_HPP_
#define _MY_DMAP_HPP_

#include "my_game_defs.hpp"
#include "my_spoint.hpp"

#include <array>
#include <vector>

using Dmap = struct Dmap_ {
  std::array< std::array< unsigned char, MAP_HEIGHT >, MAP_WIDTH > val {};
};

extern void dmap_process_no_diagonals(Dmap *D, spoint tl, spoint br, bool place_border);
extern void dmap_process_allow_diagonals(Dmap *D, spoint tl, spoint br, bool place_border);
extern void dmap_process_reverse_allow_diagonals(Dmap *D, spoint tl, spoint br, bool place_border);
extern void dmap_print(const Dmap *d, spoint at, spoint start, spoint end);
extern void dmap_print(const Dmap *d);
extern void dmap_l_shaped_path_to_diag(const Dmap *D, std::vector< spoint > &path);
extern bool dmap_can_i_move_diagonally(const Dmap *D, const spoint p, const spoint n, const spoint m);

extern std::vector< spoint > dmap_solve(const Dmap *d, const spoint start);
extern std::vector< spoint > dmap_solve_manhattan(const Dmap *d, const spoint start);
extern std::vector< spoint > dmap_solve_allow_diagonal(const Dmap *d, const spoint start);

#define DMAP_IS_WALL                    ((unsigned char) 255)
#define DMAP_IS_PASSABLE                ((unsigned char) 254)
#define DMAP_LESS_PREFERRED_TERRAIN     ((unsigned char) 100)
#define DMAP_MAX_LESS_PREFERRED_TERRAIN ((unsigned char) 253)
#define DMAP_IS_GOAL                    ((unsigned char) 0)

#endif
