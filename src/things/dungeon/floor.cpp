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

  for (auto variant = 1; variant <= FLOOR_VARIANTS; variant++) {
    std::string name = "floor" + std::to_string(variant);
    auto        tp   = tp_load(name.c_str());
    // begin sort marker1 {
    tp_variant_set(tp, variant);
    tp_flag_set(tp, is_blit_if_has_seen);
    tp_flag_set(tp, is_blit_shown_in_chasms);
    tp_flag_set(tp, is_floor);
    tp_flag_set(tp, is_teleport_blocked);
    tp_weight_set(tp, WEIGHT_VVHEAVY); // grams
    tp_z_depth_set(tp, MAP_Z_DEPTH_FLOOR);
    // end sort marker1 }

    tp_tiles_push_back(tp, THING_ANIM_IDLE, tile_find_mand(name + ".1"));
    tp_tiles_push_back(tp, THING_ANIM_IDLE, tile_find_mand(name + ".2"));
    tp_tiles_push_back(tp, THING_ANIM_IDLE, tile_find_mand(name + ".3"));
    tp_tiles_push_back(tp, THING_ANIM_IDLE, tile_find_mand(name + ".4"));
    tp_tiles_push_back(tp, THING_ANIM_IDLE, tile_find_mand(name + ".5"));
    tp_tiles_push_back(tp, THING_ANIM_IDLE, tile_find_mand(name + ".6"));
    tp_tiles_push_back(tp, THING_ANIM_IDLE, tile_find_mand(name + ".7"));
    tp_tiles_push_back(tp, THING_ANIM_IDLE, tile_find_mand(name + ".8"));
    tp_tiles_push_back(tp, THING_ANIM_IDLE, tile_find_mand(name + ".9"));
    tp_tiles_push_back(tp, THING_ANIM_IDLE, tile_find_mand(name + ".10"));
    tp_tiles_push_back(tp, THING_ANIM_IDLE, tile_find_mand(name + ".11"));
    tp_tiles_push_back(tp, THING_ANIM_IDLE, tile_find_mand(name + ".12"));
    tp_tiles_push_back(tp, THING_ANIM_IDLE, tile_find_mand(name + ".13"));
    tp_tiles_push_back(tp, THING_ANIM_IDLE, tile_find_mand(name + ".14"));
    tp_tiles_push_back(tp, THING_ANIM_IDLE, tile_find_mand(name + ".15"));
    tp_tiles_push_back(tp, THING_ANIM_IDLE, tile_find_mand(name + ".16"));
  }

  return true;
}
