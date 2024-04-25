//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "../../my_minimal.hpp"
#include "../../my_tile.hpp"
#include "../../my_tp.hpp"
#include "../../my_tps.hpp"

#include <string>

bool tp_load_exit(void)
{
  auto tp = tp_load("exit");
  // begin sort marker1 {
  tp_is_blit_on_ground_set(tp, true);
  tp_is_exit_set(tp, true);
  tp_z_depth_set(tp, MAP_DEPTH_OBJ1);
  // end sort marker1 }

  for (auto frame = 0; frame < 1; frame++) {
    const auto delay = 100; /* ms */
    auto       tile  = tile_find_mand("exit." + std::to_string(frame));
    tile->delay_ms   = delay;
    tp_tiles_push_back(tp, tile);
  }

  return true;
}
