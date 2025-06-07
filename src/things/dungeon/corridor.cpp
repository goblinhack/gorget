//
// Copyright goblinhack@gmail.com
//

#include "../../my_callstack.hpp"
#include "../../my_minimal.hpp"
#include "../../my_tile.hpp"
#include "../../my_tp.hpp"
#include "../../my_tps.hpp"

bool tp_load_corridor(void)
{
  TRACE_NO_INDENT();

  auto tp = tp_load("corridor");
  // begin sort marker1 {
  tp_flag_set(tp, is_blit_centered);
  tp_flag_set(tp, is_corridor);
  tp_flag_set(tp, is_loggable);
  tp_z_depth_set(tp, MAP_Z_DEPTH_FLOOR);
  tp_z_prio_set(tp, MAP_Z_PRIO_BEHIND);
  // end sort marker1 }

  tp_tiles_push_back(tp, THING_ANIM_IDLE, tile_find_mand("corridor.1"));
  tp_tiles_push_back(tp, THING_ANIM_IDLE, tile_find_mand("corridor.2"));
  tp_tiles_push_back(tp, THING_ANIM_IDLE, tile_find_mand("corridor.3"));
  tp_tiles_push_back(tp, THING_ANIM_IDLE, tile_find_mand("corridor.4"));
  tp_tiles_push_back(tp, THING_ANIM_IDLE, tile_find_mand("corridor.5"));
  tp_tiles_push_back(tp, THING_ANIM_IDLE, tile_find_mand("corridor.6"));
  tp_tiles_push_back(tp, THING_ANIM_IDLE, tile_find_mand("corridor.7"));
  tp_tiles_push_back(tp, THING_ANIM_IDLE, tile_find_mand("corridor.8"));
  tp_tiles_push_back(tp, THING_ANIM_IDLE, tile_find_mand("corridor.9"));
  tp_tiles_push_back(tp, THING_ANIM_IDLE, tile_find_mand("corridor.10"));
  tp_tiles_push_back(tp, THING_ANIM_IDLE, tile_find_mand("corridor.11"));
  tp_tiles_push_back(tp, THING_ANIM_IDLE, tile_find_mand("corridor.12"));
  tp_tiles_push_back(tp, THING_ANIM_IDLE, tile_find_mand("corridor.13"));
  tp_tiles_push_back(tp, THING_ANIM_IDLE, tile_find_mand("corridor.14"));
  tp_tiles_push_back(tp, THING_ANIM_IDLE, tile_find_mand("corridor.15"));
  tp_tiles_push_back(tp, THING_ANIM_IDLE, tile_find_mand("corridor.16"));

  return true;
}
