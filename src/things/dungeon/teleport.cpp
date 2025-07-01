//
// Copyright goblinhack@gmail.com
//

#include "../../my_callstack.hpp"
#include "../../my_tile.hpp"
#include "../../my_tp.hpp"
#include "../../my_tp_callbacks.hpp"
#include "../../my_tps.hpp"
#include "../../my_types.hpp"

static std::string tp_teleport_description_get(Gamep g, Levelsp v, Levelp l, Thingp me, Thingp owner, spoint at)
{
  TRACE_NO_INDENT();

  return "teleport";
}

bool tp_load_teleport(void)
{
  TRACE_NO_INDENT();

  auto name = "teleport";
  auto tp   = tp_load("teleport");

  // begin sort marker1 {
  tp_description_set(tp, tp_teleport_description_get);
  tp_flag_set(tp, is_animated);
  tp_flag_set(tp, is_blit_centered);
  tp_flag_set(tp, is_described_cursor);
  tp_flag_set(tp, is_loggable);
  tp_flag_set(tp, is_teleport);
  tp_is_immunity_add(tp, THING_DAMAGE_FIRE);
  tp_is_immunity_add(tp, THING_DAMAGE_HEAT);
  tp_is_immunity_add(tp, THING_DAMAGE_MELEE);
  tp_temperature_burns_at_set(tp, 300);  // celsius
  tp_temperature_damage_at_set(tp, 300); // celsius
  tp_temperature_initial_set(tp, 20);    // celsius
  tp_weight_set(tp, 1000);               // pounds
  tp_z_depth_set(tp, MAP_Z_DEPTH_OBJ);
  tp_z_prio_set(tp, MAP_Z_PRIO_NORMAL);
  // end sort marker1 }

  auto delay = 100;

  for (auto frame = 0; frame < 7; frame++) {
    auto tile = tile_find_mand(name + std::string(".idle.") + std::to_string(frame));
    tile_delay_ms_set(tile, delay);
    tp_tiles_push_back(tp, THING_ANIM_IDLE, tile);
  }

  return true;
}
