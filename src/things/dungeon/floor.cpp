//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_tile.hpp"
#include "my_tp.hpp"
#include "my_tps.hpp"
#include "my_types.hpp"

bool tp_load_floor(void)
{
  TRACE_NO_INDENT();

  auto tp   = tp_load("floor"); // keep as string for scripts
  auto name = tp_name(tp);
  // begin sort marker1 {
  tp_flag_set(tp, is_blit_centered);
  tp_flag_set(tp, is_floor);
  tp_flag_set(tp, is_teleport_blocked);
  tp_weight_set(tp, WEIGHT_VVHEAVY); // grams
  tp_z_depth_set(tp, MAP_Z_DEPTH_FLOOR);
  // end sort marker1 }

  tp_tiles_push_back(tp, THING_ANIM_IDLE, tile_find_mand("floor.1"));
  tp_tiles_push_back(tp, THING_ANIM_IDLE, tile_find_mand("floor.2"));
  tp_tiles_push_back(tp, THING_ANIM_IDLE, tile_find_mand("floor.3"));
  tp_tiles_push_back(tp, THING_ANIM_IDLE, tile_find_mand("floor.4"));
  tp_tiles_push_back(tp, THING_ANIM_IDLE, tile_find_mand("floor.5"));
  tp_tiles_push_back(tp, THING_ANIM_IDLE, tile_find_mand("floor.6"));
  tp_tiles_push_back(tp, THING_ANIM_IDLE, tile_find_mand("floor.7"));
  tp_tiles_push_back(tp, THING_ANIM_IDLE, tile_find_mand("floor.8"));
  tp_tiles_push_back(tp, THING_ANIM_IDLE, tile_find_mand("floor.9"));
  tp_tiles_push_back(tp, THING_ANIM_IDLE, tile_find_mand("floor.10"));
  tp_tiles_push_back(tp, THING_ANIM_IDLE, tile_find_mand("floor.11"));
  tp_tiles_push_back(tp, THING_ANIM_IDLE, tile_find_mand("floor.12"));
  tp_tiles_push_back(tp, THING_ANIM_IDLE, tile_find_mand("floor.13"));
  tp_tiles_push_back(tp, THING_ANIM_IDLE, tile_find_mand("floor.14"));
  tp_tiles_push_back(tp, THING_ANIM_IDLE, tile_find_mand("floor.15"));
  tp_tiles_push_back(tp, THING_ANIM_IDLE, tile_find_mand("floor.16"));

  return true;
}
