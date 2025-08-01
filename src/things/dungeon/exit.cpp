//
// Copyright goblinhack@gmail.com
//

#include "../../my_callstack.hpp"
#include "../../my_tile.hpp"
#include "../../my_tp.hpp"
#include "../../my_tp_callbacks.hpp"
#include "../../my_tps.hpp"
#include "../../my_types.hpp"

#include <string>

static std::string tp_exit_description_get(Gamep g, Levelsp v, Levelp l, Thingp me)
{
  TRACE_NO_INDENT();

  return "slime covered stairs leading down";
}

bool tp_load_exit(void)
{
  TRACE_NO_INDENT();

  auto tp = tp_load("exit");
  // begin sort marker1 {
  tp_description_set(tp, tp_exit_description_get);
  tp_flag_set(tp, is_animated);
  tp_flag_set(tp, is_blit_centered);
  tp_flag_set(tp, is_described_cursor);
  tp_flag_set(tp, is_exit);
  tp_flag_set(tp, is_indestructible);
  tp_flag_set(tp, is_obstacle_to_landing);
  tp_weight_set(tp, WEIGHT_VHEAVY); // grams
  tp_z_depth_set(tp, MAP_Z_DEPTH_OBJ);
  // end sort marker1 }

  for (auto frame = 0; frame < 2; frame++) {
    const auto delay = 1000; /* ms */
    auto       tile  = tile_find_mand("exit." + std::to_string(frame));
    tile_delay_ms_set(tile, delay);
    tp_tiles_push_back(tp, THING_ANIM_IDLE, tile);
  }

  return true;
}
