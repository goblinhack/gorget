//
// Copyright goblinhack@gmail.com
//

#include "../../my_callstack.hpp"
#include "../../my_thing.hpp"
#include "../../my_tile.hpp"
#include "../../my_tp.hpp"
#include "../../my_tp_callbacks.hpp"
#include "../../my_tps.hpp"
#include "../../my_types.hpp"

static std::string tp_grass_description_get(Gamep g, Levelsp v, Levelp l, Thingp me, Thingp owner, spoint at)
{
  TRACE_NO_INDENT();

  if (thing_is_dead(me)) {
    return "trampled grass";
  }
  return "dry grass";
}

bool tp_load_grass(void)
{
  TRACE_NO_INDENT();

  auto name = "grass";
  auto tp   = tp_load("grass");

  // begin sort marker1 {
  tp_description_set(tp, tp_grass_description_get);
  tp_flag_set(tp, is_blit_centered);
  tp_flag_set(tp, is_burnable);
  tp_flag_set(tp, is_crushable_underfoot);
  tp_flag_set(tp, is_described_cursor);
  tp_flag_set(tp, is_grass);
  tp_health_initial_set(tp, 1);
  tp_temperature_burns_at_set(tp, 50);  // celsius
  tp_temperature_damage_at_set(tp, 50); // celsius
  tp_temperature_initial_set(tp, 20);   // celsius
  tp_z_depth_set(tp, MAP_Z_DEPTH_OBJ);
  tp_z_prio_set(tp, MAP_Z_PRIO_NORMAL);
  // end sort marker1 }

  if (g_opt_tests) {
    return true;
  }

  for (auto frame = 0; frame < 15; frame++) {
    auto tile = tile_find_mand(name + std::string(".idle.") + std::to_string(frame));
    tp_tiles_push_back(tp, THING_ANIM_IDLE, tile);
  }

  for (auto frame = 0; frame < 1; frame++) {
    auto tile = tile_find_mand(name + std::string(".dead.") + std::to_string(frame));
    tp_tiles_push_back(tp, THING_ANIM_DEAD, tile);
  }

  return true;
}
