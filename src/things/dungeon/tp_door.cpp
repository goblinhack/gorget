//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "../../my_minimal.hpp"
#include "../../my_tile.hpp"
#include "../../my_tp.hpp"
#include "../../my_tps.hpp"

bool tp_load_door(void)
{
  auto tp = tp_load("door");
  // begin sort marker1 {
  tp_flag_set(tp, is_blit_centered, true);
  tp_flag_set(tp, is_cursor_path_blocker, true);
  tp_flag_set(tp, is_door, true);
  tp_flag_set(tp, is_obs_monst, true);
  tp_flag_set(tp, is_obs_player, true);
  tp_flag_set(tp, is_tiled, true);
  tp_z_depth_set(tp, MAP_Z_DEPTH_OBJ);
  tp_z_prio_set(tp, MAP_Z_PRIO_NORMAL);
  // end sort marker1 }

  tp_tiles_push_back(tp, tile_find_mand("door.IS_JOIN_TL2"));
  tp_tiles_push_back(tp, tile_find_mand("door.IS_JOIN_T_3"));
  tp_tiles_push_back(tp, tile_find_mand("door.IS_JOIN_TR2"));
  tp_tiles_push_back(tp, tile_find_mand("door.IS_JOIN_TOP"));
  tp_tiles_push_back(tp, tile_find_mand("door.IS_JOIN_X4_180"));
  tp_tiles_push_back(tp, tile_find_mand("door.IS_JOIN_X4_270"));
  tp_tiles_push_back(tp, tile_find_mand("door.IS_JOIN_X2_270"));
  tp_tiles_push_back(tp, tile_find_mand("door.IS_JOIN_X2"));
  tp_tiles_push_back(tp, tile_find_mand("door.IS_JOIN_X1_180"));
  tp_tiles_push_back(tp, tile_find_mand("door.IS_JOIN_X1"));
  tp_tiles_push_back(tp, tile_find_mand("door.IS_JOIN_X"));
  tp_tiles_push_back(tp, tile_find_mand("door.IS_JOIN_T270_3"));
  tp_tiles_push_back(tp, tile_find_mand("door.IS_JOIN_BLOCK"));
  tp_tiles_push_back(tp, tile_find_mand("door.IS_JOIN_T90_3"));
  tp_tiles_push_back(tp, tile_find_mand("door.IS_JOIN_VERT"));
  tp_tiles_push_back(tp, tile_find_mand("door.IS_JOIN_X4_90"));
  tp_tiles_push_back(tp, tile_find_mand("door.IS_JOIN_X4"));
  tp_tiles_push_back(tp, tile_find_mand("door.IS_JOIN_X2_180"));
  tp_tiles_push_back(tp, tile_find_mand("door.IS_JOIN_X2_90"));
  tp_tiles_push_back(tp, tile_find_mand("door.IS_JOIN_X1_90"));
  tp_tiles_push_back(tp, tile_find_mand("door.IS_JOIN_X1_270"));
  tp_tiles_push_back(tp, tile_find_mand("door.IS_JOIN_X3_180"));
  tp_tiles_push_back(tp, tile_find_mand("door.IS_JOIN_X3"));
  tp_tiles_push_back(tp, tile_find_mand("door.IS_JOIN_T_1"));
  tp_tiles_push_back(tp, tile_find_mand("door.IS_JOIN_T_2"));
  tp_tiles_push_back(tp, tile_find_mand("door.IS_JOIN_T270_2"));
  tp_tiles_push_back(tp, tile_find_mand("door.IS_JOIN_T90_1"));
  tp_tiles_push_back(tp, tile_find_mand("door.IS_JOIN_T"));
  tp_tiles_push_back(tp, tile_find_mand("door.IS_JOIN_T90"));
  tp_tiles_push_back(tp, tile_find_mand("door.IS_JOIN_TL"));
  tp_tiles_push_back(tp, tile_find_mand("door.IS_JOIN_TR"));
  tp_tiles_push_back(tp, tile_find_mand("door.IS_JOIN_LEFT"));
  tp_tiles_push_back(tp, tile_find_mand("door.IS_JOIN_HORIZ"));
  tp_tiles_push_back(tp, tile_find_mand("door.IS_JOIN_RIGHT"));
  tp_tiles_push_back(tp, tile_find_mand("door.IS_JOIN_NODE"));
  tp_tiles_push_back(tp, tile_find_mand("door.IS_JOIN_T180_2"));
  tp_tiles_push_back(tp, tile_find_mand("door.IS_JOIN_T180_1"));
  tp_tiles_push_back(tp, tile_find_mand("door.IS_JOIN_T270_1"));
  tp_tiles_push_back(tp, tile_find_mand("door.IS_JOIN_T90_2"));
  tp_tiles_push_back(tp, tile_find_mand("door.IS_JOIN_T270"));
  tp_tiles_push_back(tp, tile_find_mand("door.IS_JOIN_T180"));
  tp_tiles_push_back(tp, tile_find_mand("door.IS_JOIN_BL"));
  tp_tiles_push_back(tp, tile_find_mand("door.IS_JOIN_BR"));

  return true;
}
