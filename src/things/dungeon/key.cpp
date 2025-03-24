//
// Copyright goblinhack@gmail.com
//

#include "../../my_minimal.hpp"
#include "../../my_tp.hpp"
#include "../../my_tps.hpp"

bool tp_load_key(void)
{
  auto tp = tp_load("key");
  // begin sort marker1 {
  tp_flag_set(tp, is_blit_on_ground, true);
  tp_flag_set(tp, is_key, true);
  tp_z_depth_set(tp, MAP_Z_DEPTH_OBJ);
  tp_z_prio_set(tp, MAP_Z_PRIO_NORMAL);
  // end sort marker1 }

#if 0
  tp_tiles_push_back(tp, tile_find_mand("key0"));
#endif

  return true;
}
