//
// Copyright goblinhack@gmail.com
//

#ifndef MY_LEVEL_INLINES_HPP
#define MY_LEVEL_INLINES_HPP

#include "my_level.hpp"

static inline auto is_oob(fpoint p) -> bool
{
  return (p.x < 0) || (p.y < 0) || (p.x >= static_cast< float >(MAP_WIDTH)) || (p.y >= static_cast< float >(MAP_HEIGHT));
}
static inline auto is_oob(spoint p) -> bool { return (p.x < 0) || (p.y < 0) || (p.x >= MAP_WIDTH) || (p.y >= MAP_HEIGHT); }
static inline auto is_oob(int x, int y) -> bool { return (x < 0) || (y < 0) || (x >= MAP_WIDTH) || (y >= MAP_HEIGHT); }

//
// Something blocking the fov?
//
static inline auto level_light_blocker_at_cached(Gamep g, Levelsp v, Levelp l, const spoint &p) -> bool
{
  return l->is_light_blocker_cache[ p.x ][ p.y ] != 0;
}

//
// Has the player seen this tile?
//
static inline auto level_has_seen_cached(Gamep g, Levelsp v, Levelp l, const spoint &p) -> bool
{
  return l->player_has_seen_tile_cache[ p.x ][ p.y ] != 0;
}

#endif // MY_LEVEL_INLINES_HPP
