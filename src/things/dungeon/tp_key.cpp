//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "../../my_minimal.hpp"
#include "../../my_tp.hpp"
#include "../../my_tps.hpp"

bool tp_load_key(void)
{
  auto tp = tp_load("key");
  // begin sort marker1 {
  tp_is_blit_on_ground_set(tp, true);
  tp_is_key_set(tp, true);
  tp_z_depth_set(tp, MAP_DEPTH_OBJ2);
  // end sort marker1 }

#if 0
  tp_tiles_push_back(tp, tile_find_mand("key0"));
#endif

  return true;
}
