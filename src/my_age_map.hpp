//
// Copyright goblinhack@gmail.com
//

#ifndef MY_AGE_MAP_HPP
#define MY_AGE_MAP_HPP

#include "my_game_defs.hpp"
#include "my_bpoint.hpp"
#include "my_types.hpp"

//
// Age map for a monster or player
//
using AgeMap = struct AgeMap {
  //
  // Is incremented each time the field is set
  //
  uint8_t val[ MAP_WIDTH ][ MAP_HEIGHT ];
};

void               age_map_incr(AgeMap *m, const bpoint &pov, uint8_t val);
[[nodiscard]] auto age_map_get(const AgeMap *m, const bpoint &pov) -> uint8_t;

#endif // MY_AGE_MAP_HPP
