//
// Copyright goblinhack@gmail.com
//

#include "../../my_minimal.hpp"
#include "../../my_tile.hpp"
#include "../../my_tp.hpp"
#include "../../my_tps.hpp"

bool tp_load_cursor_at(void)
{
  auto tp = tp_load("cursor_at");
  // begin sort marker1 {
  tp_flag_set(tp, is_blit_centered, true);
  tp_flag_set(tp, is_blit_square_outlined, true);
  tp_flag_set(tp, is_cursor, true);
  tp_z_prio_set(tp, MAP_Z_PRIO_NORMAL);
  // end sort marker1 }

  tp_tiles_push_back(tp, tile_find_mand("cursor_at"));

  return true;
}
