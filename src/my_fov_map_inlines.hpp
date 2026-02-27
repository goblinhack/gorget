//
// Copyright goblinhack@gmail.com
//

#ifndef MY_FOV_MAP_INLINES_HPP
#define MY_FOV_MAP_INLINES_HPP

#include "my_fov_map.hpp"

static inline void fov_map_set(FovMap *fov, const uint8_t x, const uint8_t y, const uint8_t val)
{
  const uint16_t bit    = (((uint16_t) y * MAP_WIDTH) + (uint16_t) x);
  const uint8_t  index  = bit / 8U;
  const uint8_t  offset = bit % 8U;
  if (val != 0U) {
    fov->bits[ index ] |= 1U << offset;
  } else {
    fov->bits[ index ] &= ~(1U << offset);
  }
}

[[nodiscard]] static inline auto fov_map_get(const FovMap *fov, const uint8_t x, const uint8_t y) -> bool
{
  const uint16_t bit    = (((uint16_t) y * MAP_WIDTH) + (uint16_t) x);
  const uint8_t  index  = bit / 8U;
  const uint8_t  offset = bit % 8U;
  return (fov->bits[ index ] & (1U << offset)) != 0;
}

#endif // MY_FOV_MAP_INLINES_HPP
