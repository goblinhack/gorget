//
// Copyright goblinhack@gmail.com
//

#include "../../my_callstack.hpp"
#include "../../my_tile.hpp"
#include "../../my_tp.hpp"
#include "../../my_tps.hpp"
#include "../../my_types.hpp"

bool tp_load_level_final(void)
{
  TRACE_NO_INDENT();

  std::string name = "level_final";
  auto tp   = tp_load("level_final");

  // begin sort marker1 {
  tp_flag_set(tp, is_animated_sync_first);
  tp_flag_set(tp, is_animated);
  tp_flag_set(tp, is_blit_centered);
  tp_flag_set(tp, is_level_final);
  tp_z_depth_set(tp, MAP_Z_DEPTH_OBJ);
  tp_z_layer_set(tp, MAP_Z_LAYER_NORMAL);
  // end sort marker1 }

  for (auto frame = 0; frame < 2; frame++) {
    const auto delay = 500; /* ms */
    auto       tile  = tile_find_mand(name + std::string(".") + std::to_string(frame));
    tile_delay_ms_set(tile, delay);
    tp_tiles_push_back(tp, THING_ANIM_IDLE, tile);
  }

  return true;
}
