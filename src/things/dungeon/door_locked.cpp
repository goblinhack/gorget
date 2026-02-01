//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_main.hpp"
#include "my_sound.hpp"
#include "my_thing.hpp"
#include "my_thing_callbacks.hpp"
#include "my_thing_inlines.hpp"
#include "my_tile.hpp"
#include "my_tp.hpp"
#include "my_tps.hpp"
#include "my_types.hpp"

static Tilep door_locked_idle_damaged;
static Tilep door_locked_open_damaged;
static Tilep door_locked_open;

static std::string tp_door_locked_description_get(Gamep g, Levelsp v, Levelp l, Thingp t)
{
  TRACE_NO_INDENT();

  if (thing_is_open(t)) {
    return "open door";
  }
  if (thing_is_dead(t)) {
    return "broken door";
  }
  auto tp = thing_tp(t);
  if (thing_health(t) < tp_health_max_get(tp)) {
    return "damaged locked door";
  }
  return "locked door";
}

static Tilep tp_door_locked_at_display_get_tile_info(Gamep g, Levelsp v, Levelp l, spoint p, Tpp tp,
                                                     Thingp t_maybe_null)
{
  TRACE_NO_INDENT();

  if (! t_maybe_null) {
    return nullptr;
  }

  if (thing_health(t_maybe_null) < tp_health_max_get(tp)) {
    if (thing_is_open(t_maybe_null)) {
      return door_locked_idle_damaged;
    } else {
      return door_locked_open_damaged;
    }
  }

  if (thing_is_open(t_maybe_null)) {
    return nullptr;
  }

  if (thing_is_unlocked(t_maybe_null)) {
    return door_locked_open;
  }

  return nullptr;
}

//
// Return trun on processing the mouse event
//
static bool tp_door_locked_mouse_down(Gamep g, Levelsp v, Levelp l, Thingp t, int x, int y, int button)
{
  TRACE_NO_INDENT();

  auto player = thing_player(g);
  if (! player) {
    return false;
  }

  if (thing_is_dead(player)) {
    return false;
  }

  if (distance(thing_at(t), thing_at(player)) <= 1) {
    if (thing_is_open(t)) {
      if (thing_close(g, v, l, t, player /* opener */)) {
        TOPCON("The door closes.");
      } else {
        TOPCON("The door wont close!");
      }
    } else {
      if (thing_open(g, v, l, t, player /* opener */)) {
        TOPCON("The door opens.");
      } else {
        TOPCON("The door wont open!");
      }
    }

    return true;
  }

  return false;
}

static bool tp_door_locked_on_open_request(Gamep g, Levelsp v, Levelp l, Thingp t, Thingp opener)
{
  TRACE_NO_INDENT();

  auto tp = thing_tp(t);

  if (thing_health(t) < tp_health_max_get(tp)) {
    if (thing_is_player(opener)) {
      TOPCON("The door is damaged and won't open!");
    }
    return false;
  }

  if (thing_is_hot(t)) {
    if (thing_is_player(opener)) {
      TOPCON("The door is too hot to touch!");
    }
    return false;
  }

  //
  // Doors need keys
  //
  if (! thing_keys_carried(opener)) {
    //
    // No keys are carried
    //
    if (thing_is_unlocked(t)) {
      //
      // Door was unlocked already. No need to decrement keys.
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

  if (thing_is_unlocked(t)) {
    //
    // No need to decrement keys
    //
  } else {
    //
    // Remove a key permanently
    //
    (void) thing_keys_carried_decr(g, v, l, opener, 1);
  }

  if (thing_is_player(opener)) {
    TOPCON("The locked door opens.");

    thing_is_unlocked_set(g, v, l, t);
  }

  thing_sound_play(g, v, l, t, "door");

  return true;
}

static bool tp_door_locked_on_close_request(Gamep g, Levelsp v, Levelp l, Thingp t, Thingp opener)
{
  TRACE_NO_INDENT();

  if (thing_is_player(opener)) {
    TOPCON("The locked door closes.");
  }

  thing_sound_play(g, v, l, t, "door");

  return true;
}

static void tp_door_locked_on_death(Gamep g, Levelsp v, Levelp l, Thingp t, ThingEvent &e)
{
  TRACE_NO_INDENT();

  auto player = thing_player(g);
  if (player) {
    auto at = thing_at(player);
    if (thing_on_same_level_as_player(g, v, t)) {
      if (thing_vision_can_see_tile(g, v, l, player, at)) {
        TOPCON("The locked door breaks!");
      } else {
        TOPCON("You hear a locked door break!");
      }
    } else {
      TOPCON("You hear a very distant locked door break!");
    }
  }
}

bool tp_load_door_locked(void)
{
  TRACE_NO_INDENT();

  auto tp   = tp_load("door_locked"); // keep as string for scripts
  auto name = tp_name(tp);
  // begin sort marker1 {
  thing_description_set(tp, tp_door_locked_description_get);
  thing_display_get_tile_info_set(tp, tp_door_locked_at_display_get_tile_info);
  thing_mouse_down_set(tp, tp_door_locked_mouse_down);
  thing_on_close_request_set(tp, tp_door_locked_on_close_request);
  thing_on_death_set(tp, tp_door_locked_on_death);
  thing_on_open_request_set(tp, tp_door_locked_on_open_request);
  tp_chance_set(tp, THING_CHANCE_CONTINUE_TO_BURN, "1d2"); // roll max to continue burning
  tp_chance_set(tp, THING_CHANCE_START_BURNING, "1d2");    // roll max to continue burning
  tp_flag_set(tp, is_animated);
  tp_flag_set(tp, is_blit_if_has_seen);
  tp_flag_set(tp, is_blit_shown_in_chasms);
  tp_flag_set(tp, is_burnable); // is capable of being burned by fire
  tp_flag_set(tp, is_collision_square);
  tp_flag_set(tp, is_combustible); // will continue to burn once on fire
  tp_flag_set(tp, is_described_cursor);
  tp_flag_set(tp, is_door_locked);
  tp_flag_set(tp, is_loggable);
  tp_flag_set(tp, is_obs_to_cursor_path);
  tp_flag_set(tp, is_obs_to_falling_onto);
  tp_flag_set(tp, is_obs_to_jump_over);
  tp_flag_set(tp, is_obs_to_jumping_onto);
  tp_flag_set(tp, is_obs_to_movement);
  tp_flag_set(tp, is_obs_to_teleporting_onto);
  tp_flag_set(tp, is_obs_to_vision);
  tp_flag_set(tp, is_openable);
  tp_flag_set(tp, is_physics_explosion);
  tp_flag_set(tp, is_physics_temperature);
  tp_flag_set(tp, is_submergible);
  tp_flag_set(tp, is_teleport_blocked);
  tp_flag_set(tp, is_tickable);
  tp_flag_set(tp, is_wood);
  tp_health_set(tp, "200");
  tp_is_immunity_add(tp, THING_EVENT_WATER_DAMAGE);
  tp_long_name_set(tp, name);
  tp_priority_set(tp, THING_PRIORITY_OBJECT);
  tp_temperature_burns_at_set(tp, 100);  // celsius
  tp_temperature_damage_at_set(tp, 100); // celsius
  tp_temperature_initial_set(tp, 20);    // celsius
  tp_weight_set(tp, WEIGHT_HEAVY);       // grams
  tp_z_depth_set(tp, MAP_Z_DEPTH_OBJ);
  // end sort marker1 }

  auto delay = 500;

  for (auto frame = 0; frame < 2; frame++) {
    auto tile = tile_find_mand(name + std::string(".idle.") + std::to_string(frame));
    tile_size_set(tile, TILE_WIDTH, TILE_HEIGHT);
    tile_delay_ms_set(tile, delay);
    tp_tiles_push_back(tp, THING_ANIM_IDLE, tile);
  }

  auto tile = tile_find_mand("door_locked.open.0");
  tile_size_set(tile, TILE_WIDTH, TILE_HEIGHT);
  tp_tiles_push_back(tp, THING_ANIM_OPEN, tile);

  door_locked_idle_damaged = tile_find_mand("door_locked.idle.damaged");
  tile_size_set(door_locked_idle_damaged, TILE_WIDTH, TILE_HEIGHT);

  door_locked_open_damaged = tile_find_mand("door_locked.open.damaged");
  tile_size_set(door_locked_open_damaged, TILE_WIDTH, TILE_HEIGHT);

  door_locked_open = tile_find_mand("door_locked.idle.1");
  tile_size_set(door_locked_open, TILE_WIDTH, TILE_HEIGHT);

  return true;
}
