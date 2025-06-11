//
// Copyright goblinhack@gmail.com
//

#include "../../my_callstack.hpp"
#include "../../my_minimal.hpp"
#include "../../my_tile.hpp"
#include "../../my_tp.hpp"
#include "../../my_tp_callbacks.hpp"
#include "../../my_tps.hpp"

static std::string tp_potion_description_get(Gamep g, Levelsp v, Levelp l, Thingp me, Thingp owner, point at)
{
  TRACE_NO_INDENT();

  return "potion";
}

bool tp_load_potion(void)
{
  TRACE_NO_INDENT();

  auto name = "potion";
  auto tp   = tp_load("potion");

  // begin sort marker1 {
  tp_description_set(tp, tp_potion_description_get);
  tp_flag_set(tp, is_animated);
  tp_flag_set(tp, is_blit_centered);
  tp_flag_set(tp, is_described_cursor);
  tp_flag_set(tp, is_loggable);
  tp_flag_set(tp, is_treasure);
  tp_flag_set(tp, is_treasure1);
  tp_weight_set(tp, 0); // pounds
  tp_z_depth_set(tp, MAP_Z_DEPTH_OBJ);
  tp_z_prio_set(tp, MAP_Z_PRIO_NORMAL);
  // end sort marker1 }

  if (g_opt_tests) {
    return true;
  }

  auto delay = 1000;

  for (auto frame = 0; frame < 2; frame++) {
    auto tile = tile_find_mand(name + std::string(".") + std::to_string(frame));
    tile_delay_ms_set(tile, delay);
    tp_tiles_push_back(tp, THING_ANIM_IDLE, tile);
  }

  return true;
}
