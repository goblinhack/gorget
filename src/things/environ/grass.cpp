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

static std::string tp_grass_description_get(Gamep g, Levelsp v, Levelp l, Thingp me)
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

  std::string name = "grass";
  auto        tp   = tp_load("grass");

  // begin sort marker1 {
  tp_description_set(tp, tp_grass_description_get);
  tp_flag_set(tp, is_blit_centered);
  tp_flag_set(tp, is_burnable);    // is capable of being burned by fire
  tp_flag_set(tp, is_combustible); // will continue to burn once on fire
  tp_flag_set(tp, is_corpse_on_death);
  tp_flag_set(tp, is_crushable);
  tp_flag_set(tp, is_described_cursor);
  tp_flag_set(tp, is_grass);
  tp_flag_set(tp, is_physics_gravity);
  tp_flag_set(tp, is_physics_temperature);
  tp_health_initial_set(tp, "1");
  tp_is_immunity_add(tp, THING_EVENT_WATER_DAMAGE);
  tp_temperature_burns_at_set(tp, 100); // celsius
  tp_temperature_damage_at_set(tp, 50); // celsius
  tp_temperature_initial_set(tp, 20);   // celsius
  tp_weight_set(tp, WEIGHT_FEATHER);    // grams
  tp_z_depth_set(tp, MAP_Z_DEPTH_GRASS);
  // end sort marker1 }

  for (auto frame = 0; frame < 14; frame++) {
    auto tile = tile_find_mand(name + std::string(".idle.") + std::to_string(frame));
    tp_tiles_push_back(tp, THING_ANIM_IDLE, tile);
  }

  for (auto frame = 0; frame < 1; frame++) {
    auto tile = tile_find_mand(name + std::string(".dead.") + std::to_string(frame));
    tp_tiles_push_back(tp, THING_ANIM_DEAD, tile);
  }

  for (auto frame = 0; frame < 1; frame++) {
    auto tile = tile_find_mand(name + std::string(".burnt.") + std::to_string(frame));
    tp_tiles_push_back(tp, THING_ANIM_BURNT, tile);
  }

  return true;
}
