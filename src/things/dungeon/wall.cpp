//
// Copyright goblinhack@gmail.com
//

#include "../../my_callstack.hpp"
#include "../../my_tile.hpp"
#include "../../my_tp.hpp"
#include "../../my_tps.hpp"
#include "../../my_types.hpp"

bool tp_load_wall(void)
{
  TRACE_NO_INDENT();

  for (auto variant = 1; variant <= 1; variant++) {
    auto name = "wall" + std::to_string(variant);
    auto tp   = tp_load(name.c_str());
    // begin sort marker1 {
    tp_flag_set(tp, is_blit_centered);
    tp_flag_set(tp, is_cursor_path_blocker);
    tp_flag_set(tp, is_obstacle_block);
    tp_flag_set(tp, is_tiled);
    tp_flag_set(tp, is_wall);
    tp_is_immunity_add(tp, THING_EVENT_FIRE);
    tp_is_immunity_add(tp, THING_EVENT_HEAT);
    tp_is_immunity_add(tp, THING_EVENT_MELEE);
    tp_weight_set(tp, 1000); // pounds
    tp_z_depth_set(tp, MAP_Z_DEPTH_OBJ);
    tp_z_layer_set(tp, MAP_Z_LAYER_NORMAL);
    // end sort marker1 }

    tp_tiles_push_back(tp, THING_ANIM_JOIN_BL, tile_find_mand(name + ".IS_JOIN_BL"));
    tp_tiles_push_back(tp, THING_ANIM_JOIN_BL2, tile_find_mand(name + ".IS_JOIN_BL2"));
    tp_tiles_push_back(tp, THING_ANIM_JOIN_BLOCK, tile_find_mand(name + ".IS_JOIN_BLOCK"));
    tp_tiles_push_back(tp, THING_ANIM_JOIN_BR, tile_find_mand(name + ".IS_JOIN_BR"));
    tp_tiles_push_back(tp, THING_ANIM_JOIN_BR2, tile_find_mand(name + ".IS_JOIN_BR2"));
    tp_tiles_push_back(tp, THING_ANIM_JOIN_HORIZ, tile_find_mand(name + ".IS_JOIN_HORIZ"));
    tp_tiles_push_back(tp, THING_ANIM_JOIN_LEFT, tile_find_mand(name + ".IS_JOIN_LEFT"));
    tp_tiles_push_back(tp, THING_ANIM_JOIN_NODE, tile_find_mand(name + ".IS_JOIN_NODE"));
    tp_tiles_push_back(tp, THING_ANIM_JOIN_RIGHT, tile_find_mand(name + ".IS_JOIN_RIGHT"));
    tp_tiles_push_back(tp, THING_ANIM_JOIN_T_1, tile_find_mand(name + ".IS_JOIN_T_1"));
    tp_tiles_push_back(tp, THING_ANIM_JOIN_T_2, tile_find_mand(name + ".IS_JOIN_T_2"));
    tp_tiles_push_back(tp, THING_ANIM_JOIN_T_3, tile_find_mand(name + ".IS_JOIN_T_3"));
    tp_tiles_push_back(tp, THING_ANIM_JOIN_T, tile_find_mand(name + ".IS_JOIN_T"));
    tp_tiles_push_back(tp, THING_ANIM_JOIN_T180_1, tile_find_mand(name + ".IS_JOIN_T180_1"));
    tp_tiles_push_back(tp, THING_ANIM_JOIN_T180_2, tile_find_mand(name + ".IS_JOIN_T180_2"));
    tp_tiles_push_back(tp, THING_ANIM_JOIN_T180_3, tile_find_mand(name + ".IS_JOIN_T180_3"));
    tp_tiles_push_back(tp, THING_ANIM_JOIN_T180, tile_find_mand(name + ".IS_JOIN_T180"));
    tp_tiles_push_back(tp, THING_ANIM_JOIN_T270_1, tile_find_mand(name + ".IS_JOIN_T270_1"));
    tp_tiles_push_back(tp, THING_ANIM_JOIN_T270_2, tile_find_mand(name + ".IS_JOIN_T270_2"));
    tp_tiles_push_back(tp, THING_ANIM_JOIN_T270_3, tile_find_mand(name + ".IS_JOIN_T270_3"));
    tp_tiles_push_back(tp, THING_ANIM_JOIN_T270, tile_find_mand(name + ".IS_JOIN_T270"));
    tp_tiles_push_back(tp, THING_ANIM_JOIN_T90_1, tile_find_mand(name + ".IS_JOIN_T90_1"));
    tp_tiles_push_back(tp, THING_ANIM_JOIN_T90_2, tile_find_mand(name + ".IS_JOIN_T90_2"));
    tp_tiles_push_back(tp, THING_ANIM_JOIN_T90_3, tile_find_mand(name + ".IS_JOIN_T90_3"));
    tp_tiles_push_back(tp, THING_ANIM_JOIN_T90, tile_find_mand(name + ".IS_JOIN_T90"));
    tp_tiles_push_back(tp, THING_ANIM_JOIN_TL, tile_find_mand(name + ".IS_JOIN_TL"));
    tp_tiles_push_back(tp, THING_ANIM_JOIN_TL2, tile_find_mand(name + ".IS_JOIN_TL2"));
    tp_tiles_push_back(tp, THING_ANIM_JOIN_TOP, tile_find_mand(name + ".IS_JOIN_TOP"));
    tp_tiles_push_back(tp, THING_ANIM_JOIN_BOT, tile_find_mand(name + ".IS_JOIN_BOT"));
    tp_tiles_push_back(tp, THING_ANIM_JOIN_TR, tile_find_mand(name + ".IS_JOIN_TR"));
    tp_tiles_push_back(tp, THING_ANIM_JOIN_TR2, tile_find_mand(name + ".IS_JOIN_TR2"));
    tp_tiles_push_back(tp, THING_ANIM_JOIN_VERT, tile_find_mand(name + ".IS_JOIN_VERT"));
    tp_tiles_push_back(tp, THING_ANIM_JOIN_X, tile_find_mand(name + ".IS_JOIN_X"));
    tp_tiles_push_back(tp, THING_ANIM_JOIN_X1_180, tile_find_mand(name + ".IS_JOIN_X1_180"));
    tp_tiles_push_back(tp, THING_ANIM_JOIN_X1_270, tile_find_mand(name + ".IS_JOIN_X1_270"));
    tp_tiles_push_back(tp, THING_ANIM_JOIN_X1_90, tile_find_mand(name + ".IS_JOIN_X1_90"));
    tp_tiles_push_back(tp, THING_ANIM_JOIN_X1, tile_find_mand(name + ".IS_JOIN_X1"));
    tp_tiles_push_back(tp, THING_ANIM_JOIN_X2_180, tile_find_mand(name + ".IS_JOIN_X2_180"));
    tp_tiles_push_back(tp, THING_ANIM_JOIN_X2_270, tile_find_mand(name + ".IS_JOIN_X2_270"));
    tp_tiles_push_back(tp, THING_ANIM_JOIN_X2_90, tile_find_mand(name + ".IS_JOIN_X2_90"));
    tp_tiles_push_back(tp, THING_ANIM_JOIN_X2, tile_find_mand(name + ".IS_JOIN_X2"));
    tp_tiles_push_back(tp, THING_ANIM_JOIN_X3_180, tile_find_mand(name + ".IS_JOIN_X3_180"));
    tp_tiles_push_back(tp, THING_ANIM_JOIN_X3, tile_find_mand(name + ".IS_JOIN_X3"));
    tp_tiles_push_back(tp, THING_ANIM_JOIN_X4_180, tile_find_mand(name + ".IS_JOIN_X4_180"));
    tp_tiles_push_back(tp, THING_ANIM_JOIN_X4_270, tile_find_mand(name + ".IS_JOIN_X4_270"));
    tp_tiles_push_back(tp, THING_ANIM_JOIN_X4_90, tile_find_mand(name + ".IS_JOIN_X4_90"));
    tp_tiles_push_back(tp, THING_ANIM_JOIN_X4, tile_find_mand(name + ".IS_JOIN_X4"));
  }

  return true;
}
