//
// Changed by goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_globals.hpp"
#include "my_level.hpp"
#include "my_main.hpp"

void fov_map_set(FovMap *fov, const uint8_t x, const uint8_t y, const uint8_t val)
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

[[nodiscard]] auto fov_map_get(const FovMap *fov, const uint8_t x, const uint8_t y) -> bool
{
  const uint16_t bit    = (((uint16_t) y * MAP_WIDTH) + (uint16_t) x);
  const uint8_t  index  = bit / 8U;
  const uint8_t  offset = bit % 8U;
  return (fov->bits[ index ] & (1U << offset)) != 0;
}

void fov_map_set(FovMap *m, const spoint &pov, const bool val)
{
#ifdef _DEBUG_BUILD_
  if (IS_OOB(pov)) {
    ERR("overflow");
    return;
  }
#endif

  if (m != nullptr) {
    fov_map_set(m, pov.x, pov.y, static_cast< uint8_t >(val));
  }
}

[[nodiscard]] auto fov_map_get(const FovMap *m, const spoint &pov) -> bool
{
#ifdef _DEBUG_BUILD_
  if (IS_OOB(pov)) {
    ERR("overflow");
    return false;
  }
#endif
  if (m == nullptr) {
    return false;
  }

  return fov_map_get(m, pov.x, pov.y);
}
