//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "../../my_minimal.hpp"
#include "../../my_tile.hpp"
#include "../../my_tp.hpp"
#include "../../my_tps.hpp"

bool tp_load_cursor_at(void)
{
  auto tp = tp_load("cursor_at");
  // begin sort marker1 {
  tp_is_blit_centered_set(tp, true);
  tp_is_blit_on_ground_set(tp, true);
  tp_is_blit_square_outlined_set(tp, true);
  tp_is_cursor_at_set(tp, true);
  tp_z_depth_set(tp, MAP_DEPTH_CURSOR);
  // end sort marker1 }

  tp_tiles_push_back(tp, tile_find_mand("cursor_at"));

  return true;
}
