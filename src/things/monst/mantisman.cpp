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
#include "my_ui.hpp"

static std::string tp_mantisman_description_get(Gamep g, Levelsp v, Levelp l, Thingp t)
{
  TRACE_NO_INDENT();

  if (thing_is_dead(t)) {
    return "dead mantisman";
  }
  return "living mantisman";
}

static std::string tp_mantisman_detail_get(Gamep g, Levelsp v, Levelp l, Thingp t)
{
  TRACE_NO_INDENT();

  return                                                                                                // newline
      UI_INFO1_FMT_STR "MantisMan: half-mantis, half-man but which half?\n"                             // newline
      UI_INFO2_FMT_STR "These tall bipedal insectoids linger in the spaces that nature forgets.\n"      // newline
      UI_INFO3_FMT_STR "They hunger for human flesh especially and hang around in chittering groups.\n" // newline
      UI_INFO4_FMT_STR "The one thing they do not do... is pray.";
}

ThingEnviron tp_mantisman_assess_tile(Gamep g, Levelsp v, Levelp l, spoint at, Thingp t)
{
  TRACE_NO_INDENT();

  if (level_is_lava(g, v, l, at)) {
    return THING_ENVIRON_HATES;
  }

  if (level_is_chasm(g, v, l, at)) {
    return THING_ENVIRON_HATES;
  }

  if (level_is_water(g, v, l, at)) {
    return THING_ENVIRON_DISLIKES;
  }

  return THING_ENVIRON_NEUTRAL;
}

bool tp_load_mantisman(void)
{
  auto *tp   = tp_load("mantisman"); // keep as string for scripts
  auto name = tp_name(tp);

  // begin sort marker1 {
  thing_assess_tile_set(tp, tp_mantisman_assess_tile);
  thing_description_set(tp, tp_mantisman_description_get);
  thing_detail_set(tp, tp_mantisman_detail_get);
  tp_chance_set(tp, THING_CHANCE_CONTINUE_TO_BURN, "1d6"); // roll max to continue burning
  tp_chance_set(tp, THING_CHANCE_START_BURNING, "1d2");    // roll max to continue burning
  tp_distance_vision_set(tp, 10);
  tp_flag_set(tp, is_able_to_crush_grass);
  tp_flag_set(tp, is_able_to_fall);
  tp_flag_set(tp, is_able_to_move_diagonally);
  tp_flag_set(tp, is_animated_can_hflip);
  tp_flag_set(tp, is_animated);
  tp_flag_set(tp, is_blit_centered);
  tp_flag_set(tp, is_blit_shown_in_chasms);
  tp_flag_set(tp, is_burnable); // is capable of being burned by fire
  tp_flag_set(tp, is_collision_circle_large);
  tp_flag_set(tp, is_described_cursor);
  tp_flag_set(tp, is_health_bar_shown);
  tp_flag_set(tp, is_insectoid);
  tp_flag_set(tp, is_loggable);
  tp_flag_set(tp, is_mantisman);
  tp_flag_set(tp, is_monst);
  tp_flag_set(tp, is_obs_to_jumping_onto);
  tp_flag_set(tp, is_obs_to_movement);
  tp_flag_set(tp, is_obs_to_teleporting_onto);
  tp_flag_set(tp, is_physics_explosion);
  tp_flag_set(tp, is_physics_temperature);
  tp_flag_set(tp, is_removable_when_dead_on_err);
  tp_flag_set(tp, is_submergible); // is seen submerged when in water
  tp_flag_set(tp, is_tickable);
  tp_health_set(tp, "1d6");
  tp_is_immunity_add(tp, THING_EVENT_WATER_DAMAGE);
  tp_long_name_set(tp, "mantisman");
  tp_monst_group_add(tp, MONST_GROUP_EASY);
  tp_priority_set(tp, THING_PRIORITY_MONST);
  tp_speed_set(tp, 100);
  tp_temperature_burns_at_set(tp, 50);  // celsius
  tp_temperature_damage_at_set(tp, 35); // celsius
  tp_temperature_initial_set(tp, 20);   // celsius
  tp_weight_set(tp, WEIGHT_HEAVY);      // grams
  tp_z_depth_set(tp, MAP_Z_DEPTH_OBJ);
  // end sort marker1 }

  auto delay = 500;

  for (auto loops = 0; loops < 10; loops++) {
    for (auto frame = 0; frame < 4; frame++) {
      auto *tile = tile_find_mand(name + std::string(".idle.") + std::to_string(frame));
      tile_size_set(tile, OUTLINE_TILE_WIDTH, OUTLINE_TILE_HEIGHT);
      tile_delay_ms_set(tile, delay);
      tp_tiles_push_back(tp, THING_ANIM_IDLE, tile);
    }
  }
  for (auto frame = 0; frame < 6; frame++) {
    auto *tile = tile_find_mand(name + std::string(".idle.") + std::to_string(frame));
    tile_size_set(tile, OUTLINE_TILE_WIDTH, OUTLINE_TILE_HEIGHT);
    tile_delay_ms_set(tile, delay);
    tp_tiles_push_back(tp, THING_ANIM_IDLE, tile);
  }

  return true;
}
