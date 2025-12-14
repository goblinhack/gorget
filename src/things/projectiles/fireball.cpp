//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_dice_rolls.hpp"
#include "my_level.hpp"
#include "my_thing_callbacks.hpp"
#include "my_tile.hpp"
#include "my_tp.hpp"
#include "my_tps.hpp"
#include "my_types.hpp"

static void tp_fireball_on_spawn(Gamep g, Levelsp v, Levelp l, Thingp t)
{
  TRACE_NO_INDENT();

  thing_sound_play(g, v, l, t, "fireball");
}

static void tp_fireball_on_death(Gamep g, Levelsp v, Levelp l, Thingp t, ThingEvent &e)
{
  TRACE_NO_INDENT();

  thing_sound_play(g, v, l, t, "explosion");
}

static std::string tp_fireball_description_get(Gamep g, Levelsp v, Levelp l, Thingp t)
{
  TRACE_NO_INDENT();

  return "burning fireball";
}

static void tp_fireball_on_moved(Gamep g, Levelsp v, Levelp l, Thingp t)
{
  TRACE_NO_INDENT();

  //
  // The fireball doesn't heat water up quick enough, so add this cheap effect
  //
  if (level_is_water(g, v, l, t)) {
    if (! level_is_steam(g, v, l, t)) {
      if (d100() < 50) {
        thing_spawn(g, v, l, tp_first(is_steam), thing_at(t));
      }
    }
  }
}

bool tp_load_fireball(void)
{
  auto tp   = tp_load("fireball"); // keep as string for scripts
  auto name = tp_name(tp);

  // begin sort marker1 {
  thing_description_set(tp, tp_fireball_description_get);
  thing_on_death_set(tp, tp_fireball_on_death);
  thing_on_moved_set(tp, tp_fireball_on_moved);
  thing_on_spawn_set(tp, tp_fireball_on_spawn);
  tp_damage_set(tp, THING_EVENT_FIRE_DAMAGE, "1d4");
  tp_damage_set(tp, THING_EVENT_HEAT_DAMAGE, "1d4");
  tp_flag_set(tp, is_animated);
  tp_flag_set(tp, is_blit_centered);
  tp_flag_set(tp, is_blit_if_has_seen);
  tp_flag_set(tp, is_blit_shown_in_chasms);
  tp_flag_set(tp, is_blit_shown_in_overlay);
  tp_flag_set(tp, is_collision_circle_small);
  tp_flag_set(tp, is_described_cursor);
  tp_flag_set(tp, is_ethereal);
  tp_flag_set(tp, is_fireball);
  tp_flag_set(tp, is_light_source, 2);
  tp_flag_set(tp, is_loggable);
  tp_flag_set(tp, is_physics_temperature);
  tp_flag_set(tp, is_projectile);
  tp_flag_set(tp, is_tickable);
  tp_health_set(tp, "1");
  tp_is_immunity_add(tp, THING_EVENT_FIRE_DAMAGE);
  tp_is_immunity_add(tp, THING_EVENT_HEAT_DAMAGE);
  tp_light_color_set(tp, "orange");
  tp_long_name_set(tp, name);
  tp_priority_set(tp, THING_PRIORITY_PROJECTILE);
  tp_speed_set(tp, 1000);
  tp_temperature_initial_set(tp, 500); // celsius
  tp_weight_set(tp, WEIGHT_NONE);      // grams
  tp_z_depth_set(tp, MAP_Z_DEPTH_PROJECTILE);
  // end sort marker1 }

  auto delay = 200;

  for (auto frame = 0; frame < 2; frame++) {
    auto tile = tile_find_mand(name + "." + std::to_string(frame));
    tile_delay_ms_set(tile, delay);
    tp_tiles_push_back(tp, THING_ANIM_IDLE, tile);
  }

  return true;
}
