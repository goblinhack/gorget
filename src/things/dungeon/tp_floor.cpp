//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "../../my_minimal.hpp"
#include "../../my_tile.hpp"
#include "../../my_tp.hpp"
#include "../../my_tps.hpp"

bool tp_load_floor(void)
{
  auto tp = tp_load("floor");
  // begin sort marker1 {
  tp_flag_set(tp, is_blit_centered, true);
  tp_flag_set(tp, is_floor, true);
  tp_z_depth_set(tp, MAP_Z_DEPTH_FLOOR);
  tp_z_prio_set(tp, MAP_Z_PRIO_BEHIND);
  // end sort marker1 }

  tp_tiles_push_back(tp, tile_find_mand("floor.1"));
  tp_tiles_push_back(tp, tile_find_mand("floor.2"));
  tp_tiles_push_back(tp, tile_find_mand("floor.3"));
  tp_tiles_push_back(tp, tile_find_mand("floor.4"));
  tp_tiles_push_back(tp, tile_find_mand("floor.5"));
  tp_tiles_push_back(tp, tile_find_mand("floor.6"));

  return true;
}
