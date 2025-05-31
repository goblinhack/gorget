//
// Copyright goblinhack@gmail.com
//

#include "../../my_callstack.hpp"
#include "../../my_minimal.hpp"
#include "../../my_tile.hpp"
#include "../../my_tp.hpp"
#include "../../my_tps.hpp"

bool tp_load_pillar(void)
{
  TRACE_NO_INDENT();

  auto name = "pillar";
  auto tp   = tp_load("pillar");

  // begin sort marker1 {
  tp_flag_set(tp, is_blit_centered, true);
  tp_flag_set(tp, is_cursor_path_blocker, true);
  tp_flag_set(tp, is_obstacle_block, true);
  tp_flag_set(tp, is_pillar, true);
  tp_z_depth_set(tp, MAP_Z_DEPTH_OBJ);
  tp_z_prio_set(tp, MAP_Z_PRIO_NORMAL);
  // end sort marker1 }

  for (auto frame = 0; frame < 16; frame++) {
    auto tile = tile_find_mand(name + std::string(".") + std::to_string(frame));
    tp_tiles_push_back(tp, THING_ANIM_IDLE, tile);
  }

  return true;
}
