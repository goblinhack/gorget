//
// Copyright goblinhack@gmail.com
//

#include "../../my_callstack.hpp"
#include "../../my_minimal.hpp"
#include "../../my_tile.hpp"
#include "../../my_tp.hpp"
#include "../../my_tps.hpp"

bool tp_load_goblin_mob(void)
{
  auto name = "goblin-mob";
  auto tp   = tp_load("goblin-mob");

  // begin sort marker1 {
  tp_flag_set(tp, is_animated_can_hflip, true);
  tp_flag_set(tp, is_animated, true);
  tp_flag_set(tp, is_blit_on_ground, true);
  tp_flag_set(tp, is_blit_outlined, true);
  tp_flag_set(tp, is_mob, true);
  tp_flag_set(tp, is_mob1, true);
  tp_flag_set(tp, is_tickable, true);
  tp_speed_set(tp, 100);
  tp_z_depth_set(tp, MAP_Z_DEPTH_OBJ);
  tp_z_prio_set(tp, MAP_Z_PRIO_NORMAL);
  // end sort marker1 }

  auto delay = 1000;

  for (auto frame = 0; frame < 2; frame++) {
    auto tile = tile_find_mand(name + std::string(".idle.") + std::to_string(frame));
    tile_delay_ms_set(tile, delay);
    tp_tiles_push_back(tp, THING_ANIM_IDLE, tile);
  }

  return true;
}
