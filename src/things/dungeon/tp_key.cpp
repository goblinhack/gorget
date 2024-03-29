//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "../../my_depth.hpp"
#include "../../my_main.hpp"
#include "../../my_tp.hpp"
#include "../../my_tps.hpp"

bool tp_load_key(void)
{
  TRACE_NO_INDENT();

  auto tp = tp_load("key");
  // begin sort marker1 {
  tp->z_depth_set(MAP_DEPTH_OBJ2);
  tp->is_key            = true;
  tp->is_blit_on_ground = true;
  // end sort marker1 }

#if 0
  tp->tiles.push_back(tile_find_mand("key0"));
#endif

  return true;
}
