//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_level_data.hpp"
#include "my_main.hpp"
#include "my_tp.hpp"
#include "my_tps.hpp"

bool tp_load_dungeon_exit(void)
{
  TRACE_NO_INDENT();

  auto tp = tp_load("dungeon_exit");
  // begin sort marker1 {
  tp->z_depth_set(MAP_DEPTH_OBJ1);
  tp->is_dungeon_exit   = true;
  tp->is_blit_on_ground = true;
  // end sort marker1 }

  for (auto frame = 0; frame < 8; frame++) {
    const auto delay = 100; /* ms */
    auto       tile  = tile_find_mand("dungeon_exit." + std::to_string(frame));
    tile->delay_ms   = delay;
    tp->tiles.push_back(tile);
  }

  return true;
}
