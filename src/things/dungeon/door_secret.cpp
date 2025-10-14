//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_main.hpp"
#include "my_sound.hpp"
#include "my_thing.hpp"
#include "my_tile.hpp"
#include "my_tp.hpp"
#include "my_tp_callbacks.hpp"
#include "my_tps.hpp"
#include "my_types.hpp"

static std::string tp_door_secret_description_get(Gamep g, Levelsp v, Levelp l, Thingp t)
{
  TRACE_NO_INDENT();

  if (thing_is_open(t)) {
    return "secret door";
  }

  return "odd looking rock";
}

static bool tp_door_secret_on_open_request(Gamep g, Levelsp v, Levelp l, Thingp t, Thingp opener)
{
  TRACE_NO_INDENT();

  ThingEvent e {
      .reason     = "by opening",     //
      .event_type = THING_EVENT_OPEN, //
  };

  if (thing_is_player(opener)) {
    TOPCON("A secret door creaks open!");
  }

  sound_play(g, "door_secret");

  thing_dead(g, v, l, t, e);

  return true;
}

bool tp_load_door_secret(void)
{
  TRACE_NO_INDENT();

  auto tp   = tp_load("door_secret"); // keep as string for scripts
  auto name = tp_name(tp);
  // begin sort marker1 {
  tp_description_set(tp, tp_door_secret_description_get);
  tp_flag_set(tp, is_blit_centered);
  tp_flag_set(tp, is_blit_colored_always);
  tp_flag_set(tp, is_blit_if_has_seen);
  tp_flag_set(tp, is_described_cursor);
  tp_flag_set(tp, is_door_secret);
  tp_flag_set(tp, is_obs_to_vision);
  tp_flag_set(tp, is_loggable);
  tp_flag_set(tp, is_obs_to_cursor_path);
  tp_flag_set(tp, is_obs_to_explosion);
  tp_flag_set(tp, is_obs_to_falling_onto);
  tp_flag_set(tp, is_obs_to_fire);
  tp_flag_set(tp, is_obs_to_jumping_onto);
  tp_flag_set(tp, is_openable);
  tp_flag_set(tp, is_physics_explosion);
  tp_flag_set(tp, is_physics_temperature);
  tp_flag_set(tp, is_teleport_blocked);
  tp_flag_set(tp, is_tickable);
  tp_health_set(tp, "200");
  tp_is_immunity_add(tp, THING_EVENT_FIRE_DAMAGE);
  tp_is_immunity_add(tp, THING_EVENT_HEAT_DAMAGE);
  tp_is_immunity_add(tp, THING_EVENT_MELEE_DAMAGE);
  tp_is_immunity_add(tp, THING_EVENT_WATER_DAMAGE);
  tp_long_name_set(tp, "secret door");
  tp_on_open_request_set(tp, tp_door_secret_on_open_request);
  tp_weight_set(tp, WEIGHT_VHEAVY); // grams
  tp_z_depth_set(tp, MAP_Z_DEPTH_OBJ);
  // end sort marker1 }

  tp_tiles_push_back(tp, THING_ANIM_IDLE, tile_find_mand("door_secret.idle.0"));
  tp_tiles_push_back(tp, THING_ANIM_OPEN, tile_find_mand("door_secret.open.0"));

  return true;
}
