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
  tp_is_blit_centered_set(tp, true);
  tp_is_blit_on_ground_set(tp, true);
  tp_is_floor_set(tp, true);
  tp_z_depth_set(tp, MAP_DEPTH_FLOOR);
  // end sort marker1 }

  tp_tiles_push_back(tp, tile_find_mand("floor.1"));
  tp_tiles_push_back(tp, tile_find_mand("floor.2"));
  tp_tiles_push_back(tp, tile_find_mand("floor.3"));
  tp_tiles_push_back(tp, tile_find_mand("floor.4"));

  return true;
}
