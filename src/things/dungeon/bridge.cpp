//
// Copyright goblinhack@gmail.com
//

#include "../../my_callstack.hpp"
#include "../../my_tile.hpp"
#include "../../my_tp.hpp"
#include "../../my_tp_callbacks.hpp"
#include "../../my_tps.hpp"
#include "../../my_types.hpp"

static std::string tp_bridge_description_get(Gamep g, Levelsp v, Levelp l, Thingp me)
{
  TRACE_NO_INDENT();

  return "rickety bridge";
}

bool tp_load_bridge(void)
{
  TRACE_NO_INDENT();

  std::string name = std::string("bridge");
  auto        tp   = tp_load("bridge");
  // begin sort marker1 {
  tp_chance_set(tp, THING_CHANCE_CONTINUE_TO_BURN, "1d6");
  tp_description_set(tp, tp_bridge_description_get);
  tp_long_name_set(tp, name);
  tp_flag_set(tp, is_blit_centered);
  tp_flag_set(tp, is_bridge);
  tp_flag_set(tp, is_burnable);    // is capable of being burned by fire
  tp_flag_set(tp, is_combustible); // will continue to burn once on fire
  tp_flag_set(tp, is_described_cursor);
  tp_flag_set(tp, is_physics_temperature);
  tp_flag_set(tp, is_tiled);
  tp_health_initial_set(tp, "1d12");
  tp_temperature_burns_at_set(tp, 100);  // celsius
  tp_temperature_damage_at_set(tp, 100); // celsius
  tp_temperature_initial_set(tp, 20);    // celsius
  tp_weight_set(tp, WEIGHT_HEAVY);       // grams
  tp_z_depth_set(tp, MAP_Z_DEPTH_LIQUID);
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

  return true;
}
