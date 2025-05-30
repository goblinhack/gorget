//
// Copyright goblinhack@gmail.com
//

#include "../../my_callstack.hpp"
#include "../../my_minimal.hpp"
#include "../../my_tile.hpp"
#include "../../my_tp.hpp"
#include "../../my_tps.hpp"

bool tp_load_foliage(void)
{
  TRACE_NO_INDENT();

  auto tp = tp_load("foliage");
  // begin sort marker1 {
  tp_flag_set(tp, is_blit_on_ground, true);
  tp_flag_set(tp, is_blit_square_outlined, true);
  tp_flag_set(tp, is_foliage, true);
  tp_z_depth_set(tp, MAP_Z_DEPTH_OBJ);
  tp_z_prio_set(tp, MAP_Z_PRIO_INFRONT);
  // end sort marker1 }

  tp_tiles_push_back(tp, THING_ANIM_IDLE, tile_find_mand("foliage.1"));
  tp_tiles_push_back(tp, THING_ANIM_IDLE, tile_find_mand("foliage.2"));
  tp_tiles_push_back(tp, THING_ANIM_IDLE, tile_find_mand("foliage.3"));
  tp_tiles_push_back(tp, THING_ANIM_IDLE, tile_find_mand("foliage.4"));
  tp_tiles_push_back(tp, THING_ANIM_IDLE, tile_find_mand("foliage.5"));
  tp_tiles_push_back(tp, THING_ANIM_IDLE, tile_find_mand("foliage.6"));
  tp_tiles_push_back(tp, THING_ANIM_IDLE, tile_find_mand("foliage.7"));
  tp_tiles_push_back(tp, THING_ANIM_IDLE, tile_find_mand("foliage.8"));
  tp_tiles_push_back(tp, THING_ANIM_IDLE, tile_find_mand("foliage.9"));
  tp_tiles_push_back(tp, THING_ANIM_IDLE, tile_find_mand("foliage.10"));
  tp_tiles_push_back(tp, THING_ANIM_IDLE, tile_find_mand("foliage.11"));
  tp_tiles_push_back(tp, THING_ANIM_IDLE, tile_find_mand("foliage.12"));
  tp_tiles_push_back(tp, THING_ANIM_IDLE, tile_find_mand("foliage.13"));
  tp_tiles_push_back(tp, THING_ANIM_IDLE, tile_find_mand("foliage.14"));
  tp_tiles_push_back(tp, THING_ANIM_IDLE, tile_find_mand("foliage.15"));
  tp_tiles_push_back(tp, THING_ANIM_IDLE, tile_find_mand("foliage.16"));

  return true;
}
