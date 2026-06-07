//
// Copyright goblinhack@gmail.com
//

#ifndef MY_LEVEL_INLINES_HPP
#define MY_LEVEL_INLINES_HPP

#include "my_bpoint.hpp"
#include "my_fpoint.hpp"
#include "my_level.hpp"

static inline auto is_oob(fpoint p) -> bool
{
  return (p.x < 0) || (p.y < 0) ||                   //
         (p.x >= static_cast< float >(MAP_WIDTH)) || //
         (p.y >= static_cast< float >(MAP_HEIGHT));
}

static inline auto is_oob(bpoint p) -> bool
{ //
  return (p.x < 0) || (p.y < 0) || (p.x >= MAP_WIDTH) || (p.y >= MAP_HEIGHT);
}

static inline auto is_oob(int x, int y) -> bool
{ //
  return (x < 0) || (y < 0) || (x >= MAP_WIDTH) || (y >= MAP_HEIGHT);
}

static const auto BORDER_CHARS = 1;

static inline auto is_oob_or_border(fpoint p) -> bool
{
  return (p.x < BORDER_CHARS) ||                                    //
         (p.y < BORDER_CHARS) ||                                    //
         (p.x >= static_cast< float >(MAP_WIDTH - BORDER_CHARS)) || //
         (p.y >= static_cast< float >(MAP_HEIGHT - BORDER_CHARS));
}

static inline auto is_oob_or_border(bpoint p) -> bool
{                                             //
  return (p.x < BORDER_CHARS) ||              //
         (p.y < BORDER_CHARS) ||              //
         (p.x >= MAP_WIDTH - BORDER_CHARS) || //
         (p.y >= MAP_HEIGHT - BORDER_CHARS);
}

static inline auto is_oob_or_border(int x, int y) -> bool
{                                           //
  return (x < BORDER_CHARS) ||              //
         (y < BORDER_CHARS) ||              //
         (x >= MAP_WIDTH - BORDER_CHARS) || //
         (y >= MAP_HEIGHT - BORDER_CHARS);
}

//
// Has the player seen this tile?
//
static inline auto level_has_seen_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  return l->player_has_seen_tile_cache[ p.x ][ p.y ] != 0;
}

#endif // MY_LEVEL_INLINES_HPP
