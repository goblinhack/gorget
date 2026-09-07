//
// Changed by goblinhack@gmail.com
//

#include "my_bpoint.hpp"
#include "my_fov_map.hpp"
#include "my_fov_map_inlines.hpp"
#include "my_level_inlines.hpp" // NOLINT

#include <cstdint>

void fov_map_set(FovMap *m, const bpoint &pov, const bool val)
{
#ifdef DEBUG_BUILD
  if (is_oob(pov)) [[unlikely]] {
    ERR("overflow");
    return;
  }
#endif

  if (m != nullptr) {
    fov_map_set(m, pov.x, pov.y, static_cast< uint8_t >(val));
  }
}

[[nodiscard]] auto fov_map_get(const FovMap *m, const bpoint &pov) -> bool
{
#ifdef DEBUG_BUILD
  if (is_oob(pov)) [[unlikely]] {
    ERR("overflow");
    return false;
  }
#endif
  if (m == nullptr) {
    return false;
  }

  return fov_map_get(m, pov.x, pov.y);
}
