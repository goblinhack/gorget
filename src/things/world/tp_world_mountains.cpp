//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "../../my_level_data.hpp"
#include "../../my_main.hpp"
#include "../../my_tp.hpp"
#include "../../my_tps.hpp"

bool tp_load_world_mountains(void)
{
  TRACE_NO_INDENT();

  auto tp = tp_load("world_mountains");
  // begin sort marker1 {
  tp->z_depth_set(MAP_DEPTH_MOUNTAINS);
  tp->is_world_mountains = true;
  tp->is_blit_on_ground  = true;
  // end sort marker1 }

  for (auto x = 0; x < 1; x++) {
    auto tile = tile_find_mand(tp->name + "." + std::to_string(x));
    tp->tiles.push_back(tile);
  }

  return true;
}
