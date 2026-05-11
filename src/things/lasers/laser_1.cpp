//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_dice_rolls.hpp"
#include "my_globals.hpp"
#include "my_level.hpp"
#include "my_thing_callbacks.hpp"
#include "my_tile.hpp"
#include "my_tp.hpp"
#include "my_tps.hpp"
#include "my_types.hpp"

static void tp_laser_1_on_spawned(Gamep g, Levelsp v, Levelp l, Thingp t)
{
  TRACE();

  thing_sound_play(g, v, l, t, "laser_1");
}

static void tp_laser_1_on_death(Gamep g, Levelsp v, Levelp l, Thingp t, ThingEvent &e)
{
  TRACE();

  thing_sound_play(g, v, l, t, "explosion");
}

auto tp_load_laser_1() -> bool
{
  auto *tp   = tp_load("laser_1"); // keep as string for scripts
  auto  name = tp_name(tp);

  // begin sort marker1 {
  thing_on_death_set(tp, tp_laser_1_on_death);
  thing_on_spawned_set(tp, tp_laser_1_on_spawned);
  tp_damage_set(tp, THING_EVENT_FIRE_DAMAGE, "1d4");
  tp_flag_set(tp, is_animated);
  tp_flag_set(tp, is_blit_centered);
  tp_flag_set(tp, is_blit_if_has_seen);
  tp_flag_set(tp, is_blit_shown_in_chasms);
  tp_flag_set(tp, is_blit_shown_in_overlay);
  tp_flag_set(tp, is_collision_circle_small);
  tp_flag_set(tp, is_collision_hit_first_on_tile);
  tp_flag_set(tp, is_dead_on_collision);
  tp_flag_set(tp, is_laser);
  tp_flag_set(tp, is_light_source, 2);
  tp_flag_set(tp, is_loggable);
  tp_flag_set(tp, is_physics_temperature);
  tp_flag_set(tp, is_projectile);
  tp_flag_set(tp, is_removable_on_err);
  tp_flag_set(tp, is_tickable);
  tp_health_set(tp, "1");
  tp_is_immunity_add(tp, THING_EVENT_FIRE_DAMAGE);
  tp_is_immunity_add(tp, THING_EVENT_HEAT_DAMAGE);
  tp_light_color_set(tp, "orange");
  tp_name_a_or_an_set(tp, "a beam of light");
  tp_name_apostrophize_set(tp, "beam's of light'");
  tp_name_long_set(tp, "beam of light");
  tp_name_pluralize_set(tp, "beams of light");
  tp_name_short_set(tp, "light beam");
  tp_priority_set(tp, THING_PRIORITY_PROJECTILE);
  tp_speed_set(tp, 800);
  tp_temperature_initial_set(tp, 500); // celsius
  tp_weight_set(tp, WEIGHT_NONE);      // grams
  tp_z_depth_set(tp, MAP_Z_DEPTH_PROJECTILE);
  // end sort marker1 }

  return true;
}
