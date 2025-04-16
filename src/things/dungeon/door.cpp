//
// Copyright goblinhack@gmail.com
//

#include "../../my_minimal.hpp"
#include "../../my_tile.hpp"
#include "../../my_tp.hpp"
#include "../../my_tps.hpp"

bool tp_load_door(void)
{
  auto tp = tp_load("door");
  // begin sort marker1 {
  tp_flag_set(tp, is_blit_centered, true);
  tp_flag_set(tp, is_cursor_path_blocker, true);
  tp_flag_set(tp, is_door, true);
  tp_flag_set(tp, is_obs_monst, true);
  tp_flag_set(tp, is_obs_player, true);
  tp_z_depth_set(tp, MAP_Z_DEPTH_OBJ);
  tp_z_prio_set(tp, MAP_Z_PRIO_NORMAL);
  // end sort marker1 }

  tp_tiles_push_back(tp, THING_ANIM_IDLE, tile_find_mand("door.0"));

  return true;
}
