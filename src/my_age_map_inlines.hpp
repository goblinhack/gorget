//
// Copyright goblinhack@gmail.com
//

#ifndef MY_AGE_MAP_INLINES_HPP
#define MY_AGE_MAP_INLINES_HPP

#include "my_age_map.hpp"
#include "my_callstack.hpp"

static inline void age_map_incr(AgeMap *age, const uint8_t x, const uint8_t y, const uint8_t val)
{
  TRACE_DEBUG();

  if (val != 0U) {
    age->val[ x ][ y ] += val;
  } else {
    age->val[ x ][ y ] = val;
  }
}

static inline void age_map_set(AgeMap *age, const uint8_t x, const uint8_t y, const uint8_t val)
{
  TRACE_DEBUG();

  age->val[ x ][ y ] = val;
}

[[nodiscard]] static inline auto age_map_get(const AgeMap *age, const uint8_t x, const uint8_t y) -> uint8_t
{
  TRACE_DEBUG();

  return age->val[ x ][ y ];
}

#endif // MY_AGE_MAP_INLINES_HPP
