//
// Copyright goblinhack@gmail.com
//

#ifndef MY_FOV_MAP_HPP
#define MY_FOV_MAP_HPP

#include "my_game_defs.hpp"
#include "my_spoint.hpp"
#include "my_types.hpp"

//
// Field of view for a monster or player
//
using FovMap = struct FovMap {
  uint8_t bits[ (MAP_WIDTH * MAP_HEIGHT) / 8 ];
};

void               fov_map_set(FovMap *m, const spoint &pov, bool val);
[[nodiscard]] auto fov_map_get(const FovMap *m, const spoint &pov) -> bool;

#endif // MY_FOV_MAP_HPP
