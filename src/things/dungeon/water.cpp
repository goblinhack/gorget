//
// Copyright goblinhack@gmail.com
//

#include "../../my_minimal.hpp"
#include "../../my_tile.hpp"
#include "../../my_tp.hpp"
#include "../../my_tps.hpp"

bool tp_load_water(void)
{
  auto tp = tp_load("floor");
  // begin sort marker1 {
  tp_flag_set(tp, is_water, true);
  tp_z_depth_set(tp, MAP_Z_DEPTH_FLOOR);
  tp_z_prio_set(tp, MAP_Z_PRIO_BEHIND);
  // end sort marker1 }

  tp_tiles_push_back(tp, tile_find_mand("water.1"));
  tp_tiles_push_back(tp, tile_find_mand("water.2"));
  tp_tiles_push_back(tp, tile_find_mand("water.3"));
  tp_tiles_push_back(tp, tile_find_mand("water.4"));
  tp_tiles_push_back(tp, tile_find_mand("water.5"));
  tp_tiles_push_back(tp, tile_find_mand("water.6"));
  tp_tiles_push_back(tp, tile_find_mand("water.7"));
  tp_tiles_push_back(tp, tile_find_mand("water.8"));
  tp_tiles_push_back(tp, tile_find_mand("water.9"));
  tp_tiles_push_back(tp, tile_find_mand("water.10"));
  tp_tiles_push_back(tp, tile_find_mand("water.11"));
  tp_tiles_push_back(tp, tile_find_mand("water.12"));
  tp_tiles_push_back(tp, tile_find_mand("water.13"));
  tp_tiles_push_back(tp, tile_find_mand("water.14"));
  tp_tiles_push_back(tp, tile_find_mand("water.15"));
  tp_tiles_push_back(tp, tile_find_mand("water.16"));
  tp_tiles_push_back(tp, tile_find_mand("water.17"));
  tp_tiles_push_back(tp, tile_find_mand("water.18"));
  tp_tiles_push_back(tp, tile_find_mand("water.19"));
  tp_tiles_push_back(tp, tile_find_mand("water.20"));
  tp_tiles_push_back(tp, tile_find_mand("water.21"));
  tp_tiles_push_back(tp, tile_find_mand("water.22"));
  tp_tiles_push_back(tp, tile_find_mand("water.23"));
  tp_tiles_push_back(tp, tile_find_mand("water.24"));
  tp_tiles_push_back(tp, tile_find_mand("water.25"));
  tp_tiles_push_back(tp, tile_find_mand("water.26"));
  tp_tiles_push_back(tp, tile_find_mand("water.27"));
  tp_tiles_push_back(tp, tile_find_mand("water.28"));
  tp_tiles_push_back(tp, tile_find_mand("water.29"));
  tp_tiles_push_back(tp, tile_find_mand("water.30"));
  tp_tiles_push_back(tp, tile_find_mand("water.31"));
  tp_tiles_push_back(tp, tile_find_mand("water.32"));

  return true;
}
