//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_thing_callbacks.hpp"
#include "my_tile.hpp"
#include "my_tp.hpp"
#include "my_tps.hpp"
#include "my_types.hpp"

static std::string tp_lava_description_get(Gamep g, Levelsp v, Levelp l, Thingp t)
{
  TRACE_NO_INDENT();

  return "lovely lava";
}

bool tp_load_lava(void)
{
  TRACE_NO_INDENT();

  auto tp   = tp_load("lava"); // keep as string for scripts
  auto name = tp_name(tp);
  // begin sort marker1 {
  thing_description_set(tp, tp_lava_description_get);
  tp_damage_set(tp, THING_EVENT_FIRE_DAMAGE, "1d20+20");
  tp_damage_set(tp, THING_EVENT_HEAT_DAMAGE, "1d20+20");
  tp_flag_set(tp, is_animated);
  tp_flag_set(tp, is_blit_centered);
  tp_flag_set(tp, is_blit_if_has_seen);
  tp_flag_set(tp, is_cursor_path_hazard);
  tp_flag_set(tp, is_described_cursor);
  tp_flag_set(tp, is_lava);
  tp_flag_set(tp, is_light_source, 2);
  tp_flag_set(tp, is_needs_move_confirm);
  tp_flag_set(tp, is_physics_temperature);
  tp_flag_set(tp, is_physics_water);
  tp_flag_set(tp, is_teleport_blocked);
  tp_flag_set(tp, is_tick_delay_on_spawn);
  tp_flag_set(tp, is_tiled);
  tp_is_immunity_add(tp, THING_EVENT_FIRE_DAMAGE);
  tp_is_immunity_add(tp, THING_EVENT_HEAT_DAMAGE);
  tp_is_immunity_add(tp, THING_EVENT_MELEE_DAMAGE);
  tp_light_color_set(tp, "orange");
  tp_long_name_set(tp, name);
  tp_priority_set(tp, THING_PRIORITY_LAVA);
  tp_temperature_initial_set(tp, 1000); // celsius
  tp_weight_set(tp, WEIGHT_VVVHEAVY);   // grams
  tp_z_depth_set(tp, MAP_Z_DEPTH_LIQUID);
  // end sort marker1 }

  for (auto frame = 0; frame < 8; frame++) {
    auto frame_string = std::to_string(frame);
    tp_tiles_push_back(tp, THING_ANIM_JOIN_BL, tile_find_mand(name + ".IS_JOIN_BL." + frame_string));
    tp_tiles_push_back(tp, THING_ANIM_JOIN_BL2, tile_find_mand(name + ".IS_JOIN_BL2." + frame_string));
    tp_tiles_push_back(tp, THING_ANIM_JOIN_BLOCK, tile_find_mand(name + ".IS_JOIN_BLOCK." + frame_string));
    tp_tiles_push_back(tp, THING_ANIM_JOIN_BR, tile_find_mand(name + ".IS_JOIN_BR." + frame_string));
    tp_tiles_push_back(tp, THING_ANIM_JOIN_BR2, tile_find_mand(name + ".IS_JOIN_BR2." + frame_string));
    tp_tiles_push_back(tp, THING_ANIM_JOIN_HORIZ, tile_find_mand(name + ".IS_JOIN_HORIZ." + frame_string));
    tp_tiles_push_back(tp, THING_ANIM_JOIN_LEFT, tile_find_mand(name + ".IS_JOIN_LEFT." + frame_string));
    tp_tiles_push_back(tp, THING_ANIM_JOIN_NODE, tile_find_mand(name + ".IS_JOIN_NODE." + frame_string));
    tp_tiles_push_back(tp, THING_ANIM_JOIN_RIGHT, tile_find_mand(name + ".IS_JOIN_RIGHT." + frame_string));
    tp_tiles_push_back(tp, THING_ANIM_JOIN_T_1, tile_find_mand(name + ".IS_JOIN_T_1." + frame_string));
    tp_tiles_push_back(tp, THING_ANIM_JOIN_T_2, tile_find_mand(name + ".IS_JOIN_T_2." + frame_string));
    tp_tiles_push_back(tp, THING_ANIM_JOIN_T_3, tile_find_mand(name + ".IS_JOIN_T_3." + frame_string));
    tp_tiles_push_back(tp, THING_ANIM_JOIN_T, tile_find_mand(name + ".IS_JOIN_T." + frame_string));
    tp_tiles_push_back(tp, THING_ANIM_JOIN_T180_1, tile_find_mand(name + ".IS_JOIN_T180_1." + frame_string));
    tp_tiles_push_back(tp, THING_ANIM_JOIN_T180_2, tile_find_mand(name + ".IS_JOIN_T180_2." + frame_string));
    tp_tiles_push_back(tp, THING_ANIM_JOIN_T180_3, tile_find_mand(name + ".IS_JOIN_T180_3." + frame_string));
    tp_tiles_push_back(tp, THING_ANIM_JOIN_T180, tile_find_mand(name + ".IS_JOIN_T180." + frame_string));
    tp_tiles_push_back(tp, THING_ANIM_JOIN_T270_1, tile_find_mand(name + ".IS_JOIN_T270_1." + frame_string));
    tp_tiles_push_back(tp, THING_ANIM_JOIN_T270_2, tile_find_mand(name + ".IS_JOIN_T270_2." + frame_string));
    tp_tiles_push_back(tp, THING_ANIM_JOIN_T270_3, tile_find_mand(name + ".IS_JOIN_T270_3." + frame_string));
    tp_tiles_push_back(tp, THING_ANIM_JOIN_T270, tile_find_mand(name + ".IS_JOIN_T270." + frame_string));
    tp_tiles_push_back(tp, THING_ANIM_JOIN_T90_1, tile_find_mand(name + ".IS_JOIN_T90_1." + frame_string));
    tp_tiles_push_back(tp, THING_ANIM_JOIN_T90_2, tile_find_mand(name + ".IS_JOIN_T90_2." + frame_string));
    tp_tiles_push_back(tp, THING_ANIM_JOIN_T90_3, tile_find_mand(name + ".IS_JOIN_T90_3." + frame_string));
    tp_tiles_push_back(tp, THING_ANIM_JOIN_T90, tile_find_mand(name + ".IS_JOIN_T90." + frame_string));
    tp_tiles_push_back(tp, THING_ANIM_JOIN_TL, tile_find_mand(name + ".IS_JOIN_TL." + frame_string));
    tp_tiles_push_back(tp, THING_ANIM_JOIN_TL2, tile_find_mand(name + ".IS_JOIN_TL2." + frame_string));
    tp_tiles_push_back(tp, THING_ANIM_JOIN_TOP, tile_find_mand(name + ".IS_JOIN_TOP." + frame_string));
    tp_tiles_push_back(tp, THING_ANIM_JOIN_BOT, tile_find_mand(name + ".IS_JOIN_BOT." + frame_string));
    tp_tiles_push_back(tp, THING_ANIM_JOIN_TR, tile_find_mand(name + ".IS_JOIN_TR." + frame_string));
    tp_tiles_push_back(tp, THING_ANIM_JOIN_TR2, tile_find_mand(name + ".IS_JOIN_TR2." + frame_string));
    tp_tiles_push_back(tp, THING_ANIM_JOIN_VERT, tile_find_mand(name + ".IS_JOIN_VERT." + frame_string));
    tp_tiles_push_back(tp, THING_ANIM_JOIN_X, tile_find_mand(name + ".IS_JOIN_X." + frame_string));
    tp_tiles_push_back(tp, THING_ANIM_JOIN_X1_180, tile_find_mand(name + ".IS_JOIN_X1_180." + frame_string));
    tp_tiles_push_back(tp, THING_ANIM_JOIN_X1_270, tile_find_mand(name + ".IS_JOIN_X1_270." + frame_string));
    tp_tiles_push_back(tp, THING_ANIM_JOIN_X1_90, tile_find_mand(name + ".IS_JOIN_X1_90." + frame_string));
    tp_tiles_push_back(tp, THING_ANIM_JOIN_X1, tile_find_mand(name + ".IS_JOIN_X1." + frame_string));
    tp_tiles_push_back(tp, THING_ANIM_JOIN_X2_180, tile_find_mand(name + ".IS_JOIN_X2_180." + frame_string));
    tp_tiles_push_back(tp, THING_ANIM_JOIN_X2_270, tile_find_mand(name + ".IS_JOIN_X2_270." + frame_string));
    tp_tiles_push_back(tp, THING_ANIM_JOIN_X2_90, tile_find_mand(name + ".IS_JOIN_X2_90." + frame_string));
    tp_tiles_push_back(tp, THING_ANIM_JOIN_X2, tile_find_mand(name + ".IS_JOIN_X2." + frame_string));
    tp_tiles_push_back(tp, THING_ANIM_JOIN_X3_180, tile_find_mand(name + ".IS_JOIN_X3_180." + frame_string));
    tp_tiles_push_back(tp, THING_ANIM_JOIN_X3, tile_find_mand(name + ".IS_JOIN_X3." + frame_string));
    tp_tiles_push_back(tp, THING_ANIM_JOIN_X4_180, tile_find_mand(name + ".IS_JOIN_X4_180." + frame_string));
    tp_tiles_push_back(tp, THING_ANIM_JOIN_X4_270, tile_find_mand(name + ".IS_JOIN_X4_270." + frame_string));
    tp_tiles_push_back(tp, THING_ANIM_JOIN_X4_90, tile_find_mand(name + ".IS_JOIN_X4_90." + frame_string));
    tp_tiles_push_back(tp, THING_ANIM_JOIN_X4, tile_find_mand(name + ".IS_JOIN_X4." + frame_string));
  }

  return true;
}
