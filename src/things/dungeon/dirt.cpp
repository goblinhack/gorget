//
// Copyright goblinhack@gmail.com
//

#include "../../my_callstack.hpp"
#include "../../my_types.hpp"
#include "../../my_tile.hpp"
#include "../../my_tp.hpp"
#include "../../my_tps.hpp"

bool tp_load_dirt(void)
{
  TRACE_NO_INDENT();

  auto tp = tp_load("dirt");
  // begin sort marker1 {
  tp_flag_set(tp, is_blit_centered);
  tp_flag_set(tp, is_dirt);
  tp_z_depth_set(tp, MAP_Z_DEPTH_FLOOR);
  tp_z_prio_set(tp, MAP_Z_PRIO_BEHIND);
  // end sort marker1 }

  tp_tiles_push_back(tp, THING_ANIM_IDLE, tile_find_mand("dirt.1"));
  tp_tiles_push_back(tp, THING_ANIM_IDLE, tile_find_mand("dirt.2"));
  tp_tiles_push_back(tp, THING_ANIM_IDLE, tile_find_mand("dirt.3"));
  tp_tiles_push_back(tp, THING_ANIM_IDLE, tile_find_mand("dirt.4"));
  tp_tiles_push_back(tp, THING_ANIM_IDLE, tile_find_mand("dirt.5"));
  tp_tiles_push_back(tp, THING_ANIM_IDLE, tile_find_mand("dirt.6"));
  tp_tiles_push_back(tp, THING_ANIM_IDLE, tile_find_mand("dirt.7"));
  tp_tiles_push_back(tp, THING_ANIM_IDLE, tile_find_mand("dirt.8"));
  tp_tiles_push_back(tp, THING_ANIM_IDLE, tile_find_mand("dirt.9"));
  tp_tiles_push_back(tp, THING_ANIM_IDLE, tile_find_mand("dirt.10"));
  tp_tiles_push_back(tp, THING_ANIM_IDLE, tile_find_mand("dirt.11"));
  tp_tiles_push_back(tp, THING_ANIM_IDLE, tile_find_mand("dirt.12"));
  tp_tiles_push_back(tp, THING_ANIM_IDLE, tile_find_mand("dirt.13"));
  tp_tiles_push_back(tp, THING_ANIM_IDLE, tile_find_mand("dirt.14"));
  tp_tiles_push_back(tp, THING_ANIM_IDLE, tile_find_mand("dirt.15"));
  tp_tiles_push_back(tp, THING_ANIM_IDLE, tile_find_mand("dirt.16"));

  return true;
}
