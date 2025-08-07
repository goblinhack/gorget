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

static std::string tp_goblin_description_get(Gamep g, Levelsp v, Levelp l, Thingp me)
{
  TRACE_NO_INDENT();

  if (thing_is_dead(me)) {
    return "dead goblin";
  }
  return "starter pack goblin";
}

bool tp_load_goblin(void)
{
  std::string name = "goblin";
  auto        tp   = tp_load("goblin");

  // begin sort marker1 {
  tp_chance_set(tp, THING_CHANCE_CONTINUE_TO_BURN, "1d6");
  tp_description_set(tp, tp_goblin_description_get);
  tp_long_name_set(tp, name);
  tp_flag_set(tp, is_animated_can_hflip);
  tp_flag_set(tp, is_animated);
  tp_flag_set(tp, is_blit_centered);
  tp_flag_set(tp, is_burnable); // is capable of being burned by fire
  tp_flag_set(tp, is_corpse_on_death);
  tp_flag_set(tp, is_described_cursor);
  tp_flag_set(tp, is_goblin);
  tp_flag_set(tp, is_loggable);
  tp_flag_set(tp, is_minion);
  tp_flag_set(tp, is_monst);
  tp_flag_set(tp, is_obstacle_to_landing);
  tp_flag_set(tp, is_physics_gravity);
  tp_flag_set(tp, is_physics_temperature);
  tp_flag_set(tp, is_submergible); // is seen submerged when in water
  tp_flag_set(tp, is_tickable);
  tp_health_initial_set(tp, "1d4");
  tp_monst_group_add(tp, MONST_GROUP_1);
  tp_speed_set(tp, 100);
  tp_temperature_burns_at_set(tp, 100); // celsius
  tp_temperature_damage_at_set(tp, 50); // celsius
  tp_temperature_initial_set(tp, 20);   // celsius
  tp_weight_set(tp, WEIGHT_HUMAN);      // grams
  tp_z_depth_set(tp, MAP_Z_DEPTH_OBJ);
  // end sort marker1 }

  auto delay = 1000;

  for (auto frame = 0; frame < 2; frame++) {
    auto tile = tile_find_mand(name + std::string(".idle.") + std::to_string(frame));
    tile_delay_ms_set(tile, delay);
    tp_tiles_push_back(tp, THING_ANIM_IDLE, tile);
  }

  for (auto frame = 0; frame < 1; frame++) {
    auto tile = tile_find_mand(name + std::string(".dead.") + std::to_string(frame));
    tile_delay_ms_set(tile, delay);
    tp_tiles_push_back(tp, THING_ANIM_DEAD, tile);
  }

  return true;
}
