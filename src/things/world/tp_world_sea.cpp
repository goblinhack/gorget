//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_level_data.hpp"
#include "my_main.hpp"
#include "my_tp.hpp"
#include "my_tps.hpp"

bool tp_load_world_sea(void)
{
  TRACE_NO_INDENT();

  auto tp = tp_load("world_sea");
  // begin sort marker1 {
  tp->z_depth_set(MAP_DEPTH_SEA);
  tp->is_world_sea  = true;
  tp->is_blit_tiled = true;
  // end sort marker1 }

  auto delay = 2000;
  for (auto x = 0; x < TILE_VARIANTS; x++) {
    auto tile      = tile_find_mand(tp->name + "." + std::to_string(x));
    tile->delay_ms = delay;
    tp->tiles.push_back(tile);
  }

  return true;
}
