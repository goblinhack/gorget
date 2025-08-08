//
// Copyright goblinhack@gmail.com
//

#include "../../my_callstack.hpp"
#include "../../my_tile.hpp"
#include "../../my_tp.hpp"
#include "../../my_tps.hpp"
#include "../../my_types.hpp"

bool tp_load_corridor(void)
{
  TRACE_NO_INDENT();

  auto tp   = tp_load("corridor"); // keep as string for scripts
  auto name = tp_name(tp);
  // begin sort marker1 {
  tp_flag_set(tp, is_blit_centered);
  tp_flag_set(tp, is_corridor);
  tp_weight_set(tp, WEIGHT_VVHEAVY); // grams
  tp_z_depth_set(tp, MAP_Z_DEPTH_FLOOR);
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
