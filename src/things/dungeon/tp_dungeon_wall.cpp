//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "../../my_depth.hpp"
#include "../../my_main.hpp"
#include "../../my_tp.hpp"
#include "../../my_tps.hpp"

bool tp_load_dungeon_wall(void)
{
  TRACE_NO_INDENT();

  auto tp = tp_load("dungeon_wall");
  // begin sort marker1 {
  tp->z_depth_set(MAP_DEPTH_WALL);
  tp->is_dungeon_wall  = true;
  tp->is_blit_tiled    = true;
  tp->is_blit_centered = true;
  // end sort marker1 }

  tp->tiles.push_back(tile_find_mand("dungeon_wall.IS_JOIN_TL2"));
  tp->tiles.push_back(tile_find_mand("dungeon_wall.IS_JOIN_T_3"));
  tp->tiles.push_back(tile_find_mand("dungeon_wall.IS_JOIN_TR2"));
  tp->tiles.push_back(tile_find_mand("dungeon_wall.IS_JOIN_TOP"));
  tp->tiles.push_back(tile_find_mand("dungeon_wall.IS_JOIN_X4_180"));
  tp->tiles.push_back(tile_find_mand("dungeon_wall.IS_JOIN_X4_270"));
  tp->tiles.push_back(tile_find_mand("dungeon_wall.IS_JOIN_X2_270"));
  tp->tiles.push_back(tile_find_mand("dungeon_wall.IS_JOIN_X2"));
  tp->tiles.push_back(tile_find_mand("dungeon_wall.IS_JOIN_X1_180"));
  tp->tiles.push_back(tile_find_mand("dungeon_wall.IS_JOIN_X1"));
  tp->tiles.push_back(tile_find_mand("dungeon_wall.IS_JOIN_X"));
  tp->tiles.push_back(tile_find_mand("dungeon_wall.IS_JOIN_T270_3"));
  tp->tiles.push_back(tile_find_mand("dungeon_wall.IS_JOIN_BLOCK"));
  tp->tiles.push_back(tile_find_mand("dungeon_wall.IS_JOIN_T90_3"));
  tp->tiles.push_back(tile_find_mand("dungeon_wall.IS_JOIN_VERT"));
  tp->tiles.push_back(tile_find_mand("dungeon_wall.IS_JOIN_X4_90"));
  tp->tiles.push_back(tile_find_mand("dungeon_wall.IS_JOIN_X4"));
  tp->tiles.push_back(tile_find_mand("dungeon_wall.IS_JOIN_X2_180"));
  tp->tiles.push_back(tile_find_mand("dungeon_wall.IS_JOIN_X2_90"));
  tp->tiles.push_back(tile_find_mand("dungeon_wall.IS_JOIN_X1_90"));
  tp->tiles.push_back(tile_find_mand("dungeon_wall.IS_JOIN_X1_270"));
  tp->tiles.push_back(tile_find_mand("dungeon_wall.IS_JOIN_X3_180"));
  tp->tiles.push_back(tile_find_mand("dungeon_wall.IS_JOIN_X3"));
  tp->tiles.push_back(tile_find_mand("dungeon_wall.IS_JOIN_T_1"));
  tp->tiles.push_back(tile_find_mand("dungeon_wall.IS_JOIN_T_2"));
  tp->tiles.push_back(tile_find_mand("dungeon_wall.IS_JOIN_T270_2"));
  tp->tiles.push_back(tile_find_mand("dungeon_wall.IS_JOIN_T90_1"));
  tp->tiles.push_back(tile_find_mand("dungeon_wall.IS_JOIN_T"));
  tp->tiles.push_back(tile_find_mand("dungeon_wall.IS_JOIN_T90"));
  tp->tiles.push_back(tile_find_mand("dungeon_wall.IS_JOIN_TL"));
  tp->tiles.push_back(tile_find_mand("dungeon_wall.IS_JOIN_TR"));
  tp->tiles.push_back(tile_find_mand("dungeon_wall.IS_JOIN_LEFT"));
  tp->tiles.push_back(tile_find_mand("dungeon_wall.IS_JOIN_HORIZ"));
  tp->tiles.push_back(tile_find_mand("dungeon_wall.IS_JOIN_RIGHT"));
  tp->tiles.push_back(tile_find_mand("dungeon_wall.IS_JOIN_NODE"));
  tp->tiles.push_back(tile_find_mand("dungeon_wall.IS_JOIN_T180_2"));
  tp->tiles.push_back(tile_find_mand("dungeon_wall.IS_JOIN_T180_1"));
  tp->tiles.push_back(tile_find_mand("dungeon_wall.IS_JOIN_T270_1"));
  tp->tiles.push_back(tile_find_mand("dungeon_wall.IS_JOIN_T90_2"));
  tp->tiles.push_back(tile_find_mand("dungeon_wall.IS_JOIN_T270"));
  tp->tiles.push_back(tile_find_mand("dungeon_wall.IS_JOIN_T180"));
  tp->tiles.push_back(tile_find_mand("dungeon_wall.IS_JOIN_BL"));
  tp->tiles.push_back(tile_find_mand("dungeon_wall.IS_JOIN_BR"));

  return true;
}
