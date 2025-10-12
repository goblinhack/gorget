//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_sound.hpp"
#include "my_tile.hpp"
#include "my_tp.hpp"
#include "my_tp_callbacks.hpp"
#include "my_tps.hpp"
#include "my_types.hpp"

static std::string tp_ghost_mob_description_get(Gamep g, Levelsp v, Levelp l, Thingp t)
{
  TRACE_NO_INDENT();

  return "pile of bones";
}

static std::string tp_ghost_mob_detail_get(Gamep g, Levelsp v, Levelp l, Thingp t)
{
  TRACE_NO_INDENT();

  return "This large pile of bones, whispers and moans as spectral creations dance around it.";
}

static void tp_ghost_mob_on_death(Gamep g, Levelsp v, Levelp l, Thingp t, ThingEvent &e)
{
  TRACE_NO_INDENT();

  sound_play(g, "explosion");
}

bool tp_load_ghost_mob(void)
{
  auto tp   = tp_load("ghost_mob"); // keep as string for scripts
  auto name = tp_name(tp);

  // begin sort marker1 {
  tp_apostrophize_name_set(tp, "ghosts mob's");
  tp_description_set(tp, tp_ghost_mob_description_get);
  tp_detail_set(tp, tp_ghost_mob_detail_get);
  tp_flag_set(tp, is_able_to_fall);
  tp_flag_set(tp, is_animated_can_hflip);
  tp_flag_set(tp, is_animated);
  tp_flag_set(tp, is_blit_centered);
  tp_flag_set(tp, is_blit_if_has_seen);
  tp_flag_set(tp, is_burnable);    // is capable of being burned by fire
  tp_flag_set(tp, is_combustible); // will continue to burn once on fire
  tp_flag_set(tp, is_corpse_on_death);
  tp_flag_set(tp, is_cursor_path_hazard);
  tp_flag_set(tp, is_described_cursor);
  tp_flag_set(tp, is_health_bar_shown);
  tp_flag_set(tp, is_light_source, 3);
  tp_flag_set(tp, is_loggable);
  tp_flag_set(tp, is_mob);
  tp_flag_set(tp, is_mob1);
  tp_flag_set(tp, is_obs_to_falling_onto);
  tp_flag_set(tp, is_obs_to_jumping_onto);
  tp_flag_set(tp, is_obs_to_movement);
  tp_flag_set(tp, is_physics_explosion);
  tp_flag_set(tp, is_physics_temperature);
  tp_flag_set(tp, is_physics_water);
  tp_flag_set(tp, is_shovable);
  tp_flag_set(tp, is_submergible); // is seen submerged when in water
  tp_flag_set(tp, is_tickable);
  tp_flag_set(tp, is_wait_on_dead_anim);
  tp_health_set(tp, "1d3+2");
  tp_light_color_set(tp, "cyan");
  tp_long_name_set(tp, "ghost mob");
  tp_on_death_set(tp, tp_ghost_mob_on_death);
  tp_pluralize_name_set(tp, "ghostly mobs");
  tp_short_name_set(tp, "pile of bones");
  tp_speed_set(tp, 100);
  tp_temperature_burns_at_set(tp, 100);  // celsius
  tp_temperature_damage_at_set(tp, 100); // celsius
  tp_temperature_initial_set(tp, 0);     // celsius
  tp_weight_set(tp, WEIGHT_HEAVY);       // grams
  tp_z_depth_set(tp, MAP_Z_DEPTH_OBJ);
  // end sort marker1 }

  auto delay = 1000;

  for (auto frame = 0; frame < 2; frame++) {
    auto tile = tile_find_mand(name + std::string(".idle.") + std::to_string(frame));
    tile_delay_ms_set(tile, delay);
    tp_tiles_push_back(tp, THING_ANIM_IDLE, tile);
  }

  delay = 100;

  for (auto frame = 0; frame < 6; frame++) {
    auto tile = tile_find_mand(name + std::string(".dead.") + std::to_string(frame));
    tile_delay_ms_set(tile, delay);
    tp_tiles_push_back(tp, THING_ANIM_DEAD, tile);

    if (frame == 5) {
      tile_is_cleanup_on_end_of_anim_set(tile);
    }
  }

  return true;
}
