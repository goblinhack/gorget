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

static std::string tp_door_description_get(Gamep g, Levelsp v, Levelp l, Thingp t)
{
  TRACE_NO_INDENT();

  if (thing_is_open(t)) {
    return "open door";
  }
  if (thing_is_dead(t)) {
    return "broken door";
  }
  return "closed door";
}

static bool tp_door_mouse_down(Gamep g, Levelsp v, Levelp l, Thingp t, int x, int y, int button)
{
  TRACE_NO_INDENT();

  auto player = thing_player(g);
  if (! player) {
    return false;
  }

  if (thing_is_dead(player)) {
    return false;
  }

  if (distance(t->at, player->at) <= 1) {
    if (thing_is_open(t)) {
      thing_close(g, v, l, t, player /* opener */);
      //
      // Processed the mouse event
      //
      return true;
    } else {
      thing_open(g, v, l, t, player /* opener */);
      //
      // Processed the mouse event
      //
      return true;
    }
  }
  return false;
}

static bool tp_door_on_open_request(Gamep g, Levelsp v, Levelp l, Thingp t, Thingp opener)
{
  TRACE_NO_INDENT();

  //
  // Doors need keys
  //
  if (! thing_keys_carried(opener)) {
    if (thing_is_unlocked(t)) {
      //
      // Door was unlocked already
      //
    } else {
      //
      // Need a key
      //
      if (thing_is_player(opener)) {
        TOPCON("You need a key!");
      }

      return false;
    }
  }
  thing_keys_carried_decr(g, v, l, opener, 1);

  if (thing_is_player(opener)) {
    TOPCON("The door opens.");

    thing_is_unlocked_set(g, v, l, t);
  }

  sound_play(g, "door");

  return true;
}

static bool tp_door_on_close_request(Gamep g, Levelsp v, Levelp l, Thingp t, Thingp opener)
{
  TRACE_NO_INDENT();

  if (thing_is_player(opener)) {
    TOPCON("The door closes.");
  }

  sound_play(g, "door");

  return true;
}

bool tp_load_door(void)
{
  TRACE_NO_INDENT();

  auto tp   = tp_load("door"); // keep as string for scripts
  auto name = tp_name(tp);
  // begin sort marker1 {
  tp_chance_set(tp, THING_CHANCE_CONTINUE_TO_BURN, "1d2"); // roll max to continue burning
  tp_description_set(tp, tp_door_description_get);
  tp_flag_set(tp, is_blit_centered);
  tp_flag_set(tp, is_burnable);    // is capable of being burned by fire
  tp_flag_set(tp, is_combustible); // will continue to burn once on fire
  tp_flag_set(tp, is_described_cursor);
  tp_flag_set(tp, is_door);
  tp_flag_set(tp, is_loggable);
  tp_flag_set(tp, is_obs_to_cursor_path);
  tp_flag_set(tp, is_obs_to_falling_onto);
  tp_flag_set(tp, is_obs_to_jump_over);
  tp_mouse_down_set(tp, tp_door_mouse_down);
  tp_flag_set(tp, is_obs_to_jumping_onto);
  tp_flag_set(tp, is_obs_to_movement);
  tp_flag_set(tp, is_openable);
  tp_flag_set(tp, is_physics_explosion);
  tp_flag_set(tp, is_physics_temperature);
  tp_flag_set(tp, is_teleport_blocked);
  tp_flag_set(tp, is_tickable);
  tp_health_set(tp, "1d100");
  tp_is_immunity_add(tp, THING_EVENT_WATER_DAMAGE);
  tp_long_name_set(tp, name);
  tp_on_open_request_set(tp, tp_door_on_open_request);
  tp_on_close_request_set(tp, tp_door_on_close_request);
  tp_temperature_burns_at_set(tp, 100);  // celsius
  tp_temperature_damage_at_set(tp, 100); // celsius
  tp_temperature_initial_set(tp, 20);    // celsius
  tp_weight_set(tp, WEIGHT_HEAVY);       // grams
  tp_z_depth_set(tp, MAP_Z_DEPTH_OBJ);
  // end sort marker1 }

  tp_tiles_push_back(tp, THING_ANIM_IDLE, tile_find_mand("door.idle.0"));
  tp_tiles_push_back(tp, THING_ANIM_OPEN, tile_find_mand("door.open.0"));

  return true;
}
