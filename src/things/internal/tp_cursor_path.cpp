//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "../../my_minimal.hpp"
#include "../../my_tile.hpp"
#include "../../my_tp.hpp"
#include "../../my_tps.hpp"

bool tp_load_cursor_path(void)
{
  auto tp = tp_load("cursor_path");
  // begin sort marker1 {
  tp_flag_set(tp, is_blit_centered, true);
  tp_flag_set(tp, is_blit_on_ground, true);
  tp_flag_set(tp, is_cursor_path, true);
  tp_z_depth_set(tp, MAP_Z_DEPTH_CURSOR);
  // end sort marker1 }

  tp_tiles_push_back(tp, tile_find_mand("cursor_path"));

  return true;
}
