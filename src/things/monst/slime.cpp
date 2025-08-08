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

static std::string tp_slime_description_get(Gamep g, Levelsp v, Levelp l, Thingp me)
{
  TRACE_NO_INDENT();

  if (thing_is_dead(me)) {
    return "dead slime";
  }
  return "living slime";
}

bool tp_load_slime(void)
{
  auto tp   = tp_load("slime"); // keep as string for scripts
  auto name = tp_name(tp);

  // begin sort marker1 {
  tp_chance_set(tp, THING_CHANCE_CONTINUE_TO_BURN, "1d6");
  tp_description_set(tp, tp_slime_description_get);
  tp_flag_set(tp, is_animated_can_hflip);
  tp_flag_set(tp, is_animated);
  tp_flag_set(tp, is_blit_centered);
  tp_flag_set(tp, is_burnable);    // is capable of being burned by fire
  tp_flag_set(tp, is_combustible); // will continue to burn once on fire
  tp_flag_set(tp, is_described_cursor);
  tp_flag_set(tp, is_loggable);
  tp_flag_set(tp, is_minion);
  tp_flag_set(tp, is_monst);
  tp_flag_set(tp, is_obstacle_to_landing);
  tp_flag_set(tp, is_physics_gravity);
  tp_flag_set(tp, is_physics_temperature);
  tp_flag_set(tp, is_slime);
  tp_flag_set(tp, is_submergible); // is seen submerged when in water
  tp_flag_set(tp, is_tickable);
  tp_health_initial_set(tp, "1d10+4");
  tp_long_name_set(tp, name);
  tp_monst_group_add(tp, MONST_GROUP_2);
  tp_speed_set(tp, 100);
  tp_temperature_burns_at_set(tp, 30);  // celsius
  tp_temperature_damage_at_set(tp, 30); // celsius
  tp_temperature_initial_set(tp, 20);   // celsius
  tp_weight_set(tp, WEIGHT_VHEAVY);     // grams
  tp_z_depth_set(tp, MAP_Z_DEPTH_OBJ);
  // end sort marker1 }

  auto delay = 1000;

  for (auto frame = 0; frame < 2; frame++) {
    auto tile = tile_find_mand(name + std::string(".idle.") + std::to_string(frame));
    tile_delay_ms_set(tile, delay);
    tp_tiles_push_back(tp, THING_ANIM_IDLE, tile);
  }

  return true;
}
