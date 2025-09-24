//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_level.hpp"
#include "my_tile.hpp"
#include "my_tp.hpp"
#include "my_tp_callbacks.hpp"
#include "my_tps.hpp"
#include "my_types.hpp"

static std::string tp_barrel_description_get(Gamep g, Levelsp v, Levelp l, Thingp t)
{
  TRACE_NO_INDENT();

  return "barrel of oil";
}

static std::string tp_barrel_detail_get(Gamep g, Levelsp v, Levelp l, Thingp t)
{
  TRACE_NO_INDENT();

  return "A not out of place in a dungeon, barrel of oil.";
}

static void tp_barrel_spawn_explosion(Gamep g, Levelsp v, Levelp l, Thingp t)
{
  TRACE_NO_INDENT();

  const std::initializer_list< spoint > points = {
      spoint(-1, -1), spoint(1, -1), spoint(0, -1), spoint(-1, 0), spoint(1, 0),
      spoint(0, 0),   spoint(-1, 1), spoint(1, 1),  spoint(0, 1),
  };

  for (auto delta : points) {
    auto p = t->at + delta;
    if (! level_is_obs_to_explosion(g, v, l, p)) {
      if (! level_is_explosion(g, v, l, p)) {
        thing_spawn(g, v, l, tp_random(is_explosion), p);
      }
    }
  }
}

static void tp_barrel_on_death(Gamep g, Levelsp v, Levelp l, Thingp t, ThingEvent &e)
{
  TRACE_NO_INDENT();

  tp_barrel_spawn_explosion(g, v, l, t);
}

static void tp_barrel_on_fall_end(Gamep g, Levelsp v, Levelp l, Thingp t)
{
  TRACE_NO_INDENT();

  ThingEvent e {
      .reason     = "by barrel falling", //
      .event_type = THING_EVENT_FALL,    //
  };
  thing_dead(g, v, l, t, e);
}

bool tp_load_barrel(void)
{
  TRACE_NO_INDENT();

  auto tp   = tp_load("barrel"); // keep as string for scripts
  auto name = tp_name(tp);

  // begin sort marker1 {
  tp_chance_set(tp, THING_CHANCE_CONTINUE_TO_BURN, "1d2"); // roll max to stop burning
  tp_description_set(tp, tp_barrel_description_get);
  tp_detail_set(tp, tp_barrel_detail_get);
  tp_flag_set(tp, is_able_to_fall);
  tp_flag_set(tp, is_animated);
  tp_flag_set(tp, is_barrel);
  tp_flag_set(tp, is_blit_centered);
  tp_flag_set(tp, is_blit_square_outlined);
  tp_flag_set(tp, is_broken_on_death);
  tp_flag_set(tp, is_burnable);    // is capable of being burned by fire
  tp_flag_set(tp, is_combustible); // will continue to burn once on fire
  tp_flag_set(tp, is_described_cursor);
  tp_flag_set(tp, is_loggable);
  tp_flag_set(tp, is_obs_to_cursor_path);
  tp_flag_set(tp, is_obs_to_falling_onto);
  tp_flag_set(tp, is_obs_to_jumping_onto);
  tp_flag_set(tp, is_obs_to_movement);
  tp_flag_set(tp, is_physics_explosion);
  tp_flag_set(tp, is_physics_temperature);
  tp_flag_set(tp, is_shovable);
  tp_flag_set(tp, is_submergible); // is seen submerged when in water
  tp_flag_set(tp, is_tickable);
  tp_health_set(tp, "1d6");
  tp_is_immunity_add(tp, THING_EVENT_WATER_DAMAGE);
  tp_long_name_set(tp, name);
  tp_on_death_set(tp, tp_barrel_on_death);
  tp_on_fall_end_set(tp, tp_barrel_on_fall_end);
  tp_temperature_burns_at_set(tp, 50);  // celsius
  tp_temperature_damage_at_set(tp, 50); // celsius
  tp_temperature_initial_set(tp, 20);   // celsius
  tp_weight_set(tp, WEIGHT_HEAVY);      // grams
  tp_z_depth_set(tp, MAP_Z_DEPTH_OBJ);
  // end sort marker1 }

  auto delay = 200;

  for (auto frame = 0; frame < 1; frame++) {
    auto tile = tile_find_mand(name + std::string(".idle.") + std::to_string(frame));
    tile_delay_ms_set(tile, delay);
    tp_tiles_push_back(tp, THING_ANIM_IDLE, tile);
  }

  return true;
}
