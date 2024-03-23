//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "../../my_depth.hpp"
#include "../../my_main.hpp"
#include "../../my_tp.hpp"
#include "../../my_tps.hpp"

bool tp_load_exit(void)
{
  TRACE_NO_INDENT();

  auto tp = tp_load("exit");
  // begin sort marker1 {
  tp->z_depth_set(MAP_DEPTH_OBJ1);
  tp->is_exit   = true;
  tp->is_blit_on_ground = true;
  // end sort marker1 }

  for (auto frame = 0; frame < 1; frame++) {
    const auto delay = 100; /* ms */
    auto       tile  = tile_find_mand("exit." + std::to_string(frame));
    tile->delay_ms   = delay;
    tp->tiles.push_back(tile);
  }

  return true;
}
