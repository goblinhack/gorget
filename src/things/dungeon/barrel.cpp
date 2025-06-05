//
// Copyright goblinhack@gmail.com
//

#include "../../my_callstack.hpp"
#include "../../my_minimal.hpp"
#include "../../my_tile.hpp"
#include "../../my_tp.hpp"
#include "../../my_tp_callbacks.hpp"
#include "../../my_tps.hpp"

static std::string tp_barrel_description_get(Tpp tp, Thingp me, Thingp owner, point at)
{
  TRACE_NO_INDENT();

  return "barrel of oil";
}

bool tp_load_barrel(void)
{
  TRACE_NO_INDENT();

  auto name = "barrel";
  auto tp   = tp_load("barrel");

  // begin sort marker1 {
  tp_description_set(tp, tp_barrel_description_get);
  tp_flag_set(tp, is_animated, true);
  tp_flag_set(tp, is_barrel, true);
  tp_flag_set(tp, is_blit_centered, true);
  tp_flag_set(tp, is_blit_square_outlined, true);
  tp_flag_set(tp, is_cursor_path_blocker, true);
  tp_flag_set(tp, is_described_cursor, true);
  tp_flag_set(tp, is_obstacle_block, true);
  tp_weight_set(tp, 200); // pounds
  tp_z_depth_set(tp, MAP_Z_DEPTH_OBJ);
  tp_z_prio_set(tp, MAP_Z_PRIO_NORMAL);
  // end sort marker1 }

  auto delay = 200;

  for (auto frame = 0; frame < 1; frame++) {
    auto tile = tile_find_mand(name + std::string(".idle.") + std::to_string(frame));
    tile_delay_ms_set(tile, delay);
    tp_tiles_push_back(tp, THING_ANIM_IDLE, tile);
  }

  return true;
}
