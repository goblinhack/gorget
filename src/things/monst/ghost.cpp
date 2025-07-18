//
// Copyright goblinhack@gmail.com
//

#include "../../my_callstack.hpp"
#include "../../my_tile.hpp"
#include "../../my_tp.hpp"
#include "../../my_tp_callbacks.hpp"
#include "../../my_tps.hpp"
#include "../../my_types.hpp"

static std::string tp_ghost_description_get(Gamep g, Levelsp v, Levelp l, Thingp me, Thingp owner, spoint at)
{
  TRACE_NO_INDENT();

  return "vengeful spirit";
}

bool tp_load_ghost(void)
{
  std::string name = "ghost";
  auto tp   = tp_load("ghost");

  // begin sort marker1 {
  tp_description_set(tp, tp_ghost_description_get);
  tp_flag_set(tp, is_animated_can_hflip);
  tp_flag_set(tp, is_animated);
  tp_flag_set(tp, is_blit_centered);
  tp_flag_set(tp, is_described_cursor);
  tp_flag_set(tp, is_ethereal);
  tp_flag_set(tp, is_ghost);
  tp_flag_set(tp, is_levitating);
  tp_flag_set(tp, is_loggable);
  tp_flag_set(tp, is_minion);
  tp_flag_set(tp, is_monst);
  tp_flag_set(tp, is_tickable);
  tp_flag_set(tp, is_undead);
  tp_flag_set(tp, is_walk_through_walls);
  tp_health_initial_set(tp, 1);
  tp_is_immunity_add(tp, THING_EVENT_FIRE);
  tp_is_immunity_add(tp, THING_EVENT_HEAT);
  tp_monst_group_add(tp, MONST_GROUP_0);
  tp_speed_set(tp, 100);
  tp_temperature_initial_set(tp, -10); // celsius
  tp_weight_set(tp, WEIGHT_FEATHER);   // grams
  tp_z_depth_set(tp, MAP_Z_DEPTH_OBJ);
  tp_z_layer_set(tp, MAP_Z_LAYER_NORMAL);
  // end sort marker1 }

  auto delay = 1000;

  for (auto frame = 0; frame < 2; frame++) {
    auto tile = tile_find_mand(name + std::string(".idle.") + std::to_string(frame));
    tile_delay_ms_set(tile, delay);
    tp_tiles_push_back(tp, THING_ANIM_IDLE, tile);
  }

  return true;
}
