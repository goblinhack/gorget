//
// Copyright goblinhack@gmail.com
//

#include "../../my_callstack.hpp"
#include "../../my_minimal.hpp"
#include "../../my_tile.hpp"
#include "../../my_tp.hpp"
#include "../../my_tps.hpp"

bool tp_load_level_visited(void)
{
  TRACE_NO_INDENT();

  auto name = "level_visited";
  auto tp   = tp_load("level_visited");

  // begin sort marker1 {
  tp_flag_set(tp, is_animated, true);
  tp_flag_set(tp, is_blit_centered, true);
  tp_flag_set(tp, is_level_visited, true);
  tp_z_depth_set(tp, MAP_Z_DEPTH_OBJ);
  tp_z_prio_set(tp, MAP_Z_PRIO_NORMAL);
  // end sort marker1 }

  for (auto frame = 0; frame < 2; frame++) {
    const auto delay = 1000; /* ms */
    auto       tile  = tile_find_mand(name + std::string(".") + std::to_string(frame));
    tile_delay_ms_set(tile, delay);
    tp_tiles_push_back(tp, THING_ANIM_IDLE, tile);
  }

  return true;
}
