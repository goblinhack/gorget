//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_thing.hpp"
#include "my_thing_callbacks.hpp"
#include "my_thing_inlines.hpp"
#include "my_tile.hpp"
#include "my_tp.hpp"
#include "my_tps.hpp"
#include "my_types.hpp"

static std::string tp_kobalos_description_get(Gamep g, Levelsp v, Levelp l, Thingp t)
{
  TRACE_NO_INDENT();

  if (thing_is_dead(t)) {
    return "dead kobalos";
  }
  return "kobalos";
}

static std::string tp_kobalos_detail_get(Gamep g, Levelsp v, Levelp l, Thingp t)
{
  TRACE_NO_INDENT();

  std::string s;
  s += "Kobalos are small green-skinned creatures that are identical in every possible way to a goblin. ";
  s += "They are vindictive, greedy little things and have a habit of thievery...";
  return s;
}

bool tp_load_kobalos(void)
{
  auto tp   = tp_load("kobalos"); // keep as string for scripts
  auto name = tp_name(tp);

  // begin sort marker1 {
  thing_description_set(tp, tp_kobalos_description_get);
  thing_detail_set(tp, tp_kobalos_detail_get);
  tp_chance_set(tp, THING_CHANCE_CONTINUE_TO_BURN, "1d6"); // roll max to continue burning
  tp_chance_set(tp, THING_CHANCE_START_BURNING, "1d2");    // roll max to continue burning
  tp_distance_minion_from_mob_max_set(tp, 10);
  tp_distance_vision_set(tp, 10);
  tp_flag_set(tp, is_able_to_crush_grass);
  tp_flag_set(tp, is_able_to_fall);
  tp_flag_set(tp, is_animated_can_hflip);
  tp_flag_set(tp, is_animated);
  tp_flag_set(tp, is_blit_centered);
  tp_flag_set(tp, is_blit_shown_in_chasms);
  tp_flag_set(tp, is_burnable); // is capable of being burned by fire
  tp_flag_set(tp, is_collision_circle_large);
  tp_flag_set(tp, is_corpse_on_death);
  tp_flag_set(tp, is_described_cursor);
  tp_flag_set(tp, is_flesh);
  tp_flag_set(tp, is_health_bar_shown);
  tp_flag_set(tp, is_kobalos);
  tp_flag_set(tp, is_loggable);
  tp_flag_set(tp, is_minion);
  tp_flag_set(tp, is_monst);
  tp_flag_set(tp, is_physics_explosion);
  tp_flag_set(tp, is_physics_temperature);
  tp_flag_set(tp, is_submergible); // is seen submerged when in water
  tp_flag_set(tp, is_tickable);
  tp_health_set(tp, "1d4");
  tp_is_immunity_add(tp, THING_EVENT_WATER_DAMAGE);
  tp_long_name_set(tp, name);
  tp_monst_group_add(tp, MONST_GROUP_EASY);
  tp_priority_set(tp, THING_PRIORITY_MONST);
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
    tile_size_set(tile, TILE_WIDTH, TILE_HEIGHT);
    tile_delay_ms_set(tile, delay);
    tp_tiles_push_back(tp, THING_ANIM_IDLE, tile);
  }

  for (auto frame = 0; frame < 1; frame++) {
    auto tile = tile_find_mand(name + std::string(".dead.") + std::to_string(frame));
    tile_size_set(tile, TILE_WIDTH, TILE_HEIGHT);
    tile_delay_ms_set(tile, delay);
    tp_tiles_push_back(tp, THING_ANIM_DEAD, tile);
  }

  return true;
}
