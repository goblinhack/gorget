//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "../../my_depth.hpp"
#include "../../my_main.hpp"
#include "../../my_tp.hpp"
#include "../../my_tps.hpp"

bool tp_load_floor(void)
{
  TRACE_NO_INDENT();

  auto tp = tp_load("floor");
  // begin sort marker1 {
  tp->z_depth_set(MAP_DEPTH_FLOOR);
  tp->is_floor  = true;
  tp->is_blit_on_ground = true;
  tp->is_blit_centered  = true;
  // end sort marker1 }

  tp->tiles.push_back(tile_find_mand("floor.1"));
  tp->tiles.push_back(tile_find_mand("floor.2"));
  tp->tiles.push_back(tile_find_mand("floor.3"));
  tp->tiles.push_back(tile_find_mand("floor.4"));

  return true;
}
