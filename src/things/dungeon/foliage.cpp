//
// Copyright goblinhack@gmail.com
//

#include "../../my_callstack.hpp"
#include "../../my_minimal.hpp"
#include "../../my_tile.hpp"
#include "../../my_tp.hpp"
#include "../../my_tp_callbacks.hpp"
#include "../../my_tps.hpp"

static std::string tp_foliage_description_get(Gamep g, Levelsp v, Levelp l, Thingp me, Thingp owner, spoint at)
{
  TRACE_NO_INDENT();

  return "sickly looking foliage";
}

bool tp_load_foliage(void)
{
  TRACE_NO_INDENT();

  auto tp = tp_load("foliage");
  // begin sort marker1 {
  tp_description_set(tp, tp_foliage_description_get);
  tp_flag_set(tp, is_blit_centered);
  tp_flag_set(tp, is_burnable);
  tp_flag_set(tp, is_described_cursor);
  tp_flag_set(tp, is_foliage);
  tp_flag_set(tp, is_loggable);
  tp_health_initial_set(tp, 5);
  tp_temperature_burns_at_set(tp, 50);  // celsius
  tp_temperature_damage_at_set(tp, 50); // celsius
  tp_temperature_initial_set(tp, 20);   // celsius
  tp_weight_set(tp, 10);                // pounds
  tp_z_depth_set(tp, MAP_Z_DEPTH_OBJ);
  tp_z_prio_set(tp, MAP_Z_PRIO_INFRONT);
  // end sort marker1 }

  tp_tiles_push_back(tp, THING_ANIM_IDLE, tile_find_mand("foliage.1"));
  tp_tiles_push_back(tp, THING_ANIM_IDLE, tile_find_mand("foliage.2"));
  tp_tiles_push_back(tp, THING_ANIM_IDLE, tile_find_mand("foliage.3"));
  tp_tiles_push_back(tp, THING_ANIM_IDLE, tile_find_mand("foliage.4"));
  tp_tiles_push_back(tp, THING_ANIM_IDLE, tile_find_mand("foliage.5"));
  tp_tiles_push_back(tp, THING_ANIM_IDLE, tile_find_mand("foliage.6"));
  tp_tiles_push_back(tp, THING_ANIM_IDLE, tile_find_mand("foliage.7"));
  tp_tiles_push_back(tp, THING_ANIM_IDLE, tile_find_mand("foliage.8"));
  tp_tiles_push_back(tp, THING_ANIM_IDLE, tile_find_mand("foliage.9"));
  tp_tiles_push_back(tp, THING_ANIM_IDLE, tile_find_mand("foliage.10"));
  tp_tiles_push_back(tp, THING_ANIM_IDLE, tile_find_mand("foliage.11"));
  tp_tiles_push_back(tp, THING_ANIM_IDLE, tile_find_mand("foliage.12"));
  tp_tiles_push_back(tp, THING_ANIM_IDLE, tile_find_mand("foliage.13"));
  tp_tiles_push_back(tp, THING_ANIM_IDLE, tile_find_mand("foliage.14"));
  tp_tiles_push_back(tp, THING_ANIM_IDLE, tile_find_mand("foliage.15"));
  tp_tiles_push_back(tp, THING_ANIM_IDLE, tile_find_mand("foliage.16"));

  return true;
}
