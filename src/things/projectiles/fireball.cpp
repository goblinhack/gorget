//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_thing_callbacks.hpp"
#include "my_tile.hpp"
#include "my_tp.hpp"
#include "my_tps.hpp"
#include "my_types.hpp"

static void tp_fireball_spawn(Gamep g, Levelsp v, Levelp l, Thingp t)
{
  TRACE_NO_INDENT();

  thing_sound_play(g, v, l, t, "fireball");
}

static std::string tp_fireball_description_get(Gamep g, Levelsp v, Levelp l, Thingp t)
{
  TRACE_NO_INDENT();

  return "burning fireball";
}

bool tp_load_fireball(void)
{
  auto tp   = tp_load("fireball"); // keep as string for scripts
  auto name = tp_name(tp);

  // begin sort marker1 {
  thing_on_spawn_set(tp, tp_fireball_spawn);
  thing_description_set(tp, tp_fireball_description_get);
  tp_flag_set(tp, is_animated);
  tp_flag_set(tp, is_blit_centered);
  tp_flag_set(tp, is_blit_shown_in_chasms);
  tp_flag_set(tp, is_blit_shown_in_overlay);
  tp_flag_set(tp, is_blit_when_obscured);
  tp_flag_set(tp, is_described_cursor);
  tp_flag_set(tp, is_ethereal);
  tp_flag_set(tp, is_fireball);
  tp_flag_set(tp, is_light_source, 2);
  tp_flag_set(tp, is_loggable);
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
  tp_weight_set(tp, WEIGHT_FEATHER);   // grams
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
