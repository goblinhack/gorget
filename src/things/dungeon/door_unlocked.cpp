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

static Tilep door_unlocked_idle_damaged;
static Tilep door_unlocked_open_damaged;

static std::string tp_door_unlocked_description_get(Gamep g, Levelsp v, Levelp l, Thingp t)
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
    return "damaged unlocked door";
  }
  return "unlocked door";
}

static Tilep tp_door_unlocked_at_display_get_tile_info(Gamep g, Levelsp v, Levelp l, spoint p, Tpp tp,
                                                       Thingp t_maybe_null)
{
  TRACE_NO_INDENT();

  if (! t_maybe_null) {
    return nullptr;
  }

  Tilep alt_tile = nullptr;
  if (thing_is_open(t_maybe_null)) {
    alt_tile = door_unlocked_idle_damaged;
  } else {
    alt_tile = door_unlocked_open_damaged;
  }

  if (thing_health(t_maybe_null) < tp_health_max_get(tp)) {
    return alt_tile;
  }

  return nullptr;
}

static bool tp_door_unlocked_mouse_down(Gamep g, Levelsp v, Levelp l, Thingp t, int x, int y, int button)
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

static bool tp_door_unlocked_on_open_request(Gamep g, Levelsp v, Levelp l, Thingp t, Thingp opener)
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

  if (thing_is_player(opener)) {
    TOPCON("The door opens.");

    thing_is_unlocked_set(g, v, l, t);
  }

  thing_sound_play(g, v, l, t, "door");

  return true;
}

static bool tp_door_unlocked_on_close_request(Gamep g, Levelsp v, Levelp l, Thingp t, Thingp opener)
{
  TRACE_NO_INDENT();

  if (thing_is_player(opener)) {
    TOPCON("The door closes.");
  }

  thing_sound_play(g, v, l, t, "door");

  return true;
}

static void tp_door_unlocked_on_death(Gamep g, Levelsp v, Levelp l, Thingp t, ThingEvent &e)
{
  TRACE_NO_INDENT();

  auto player = thing_player(g);
  if (player) {
    auto at = thing_at(player);
    if (thing_on_same_level_as_player(g, v, t)) {
      if (thing_vision_can_see_tile(g, v, l, player, at)) {
        TOPCON("The door breaks!");
      } else {
        TOPCON("You hear a door break!");
      }
    } else {
      TOPCON("You hear a very distant door break!");
    }
  }
}

bool tp_load_door_unlocked(void)
{
  TRACE_NO_INDENT();

  auto tp   = tp_load("door_unlocked"); // keep as string for scripts
  auto name = tp_name(tp);
  // begin sort marker1 {
  thing_description_set(tp, tp_door_unlocked_description_get);
  thing_mouse_down_set(tp, tp_door_unlocked_mouse_down);
  thing_on_close_request_set(tp, tp_door_unlocked_on_close_request);
  thing_on_open_request_set(tp, tp_door_unlocked_on_open_request);
  thing_on_death_set(tp, tp_door_unlocked_on_death);
  tp_chance_set(tp, THING_CHANCE_CONTINUE_TO_BURN, "1d2"); // roll max to continue burning
  tp_chance_set(tp, THING_CHANCE_START_BURNING, "1d2");    // roll max to continue burning
  tp_flag_set(tp, is_animated);
  tp_flag_set(tp, is_blit_if_has_seen);
  tp_flag_set(tp, is_blit_shown_in_chasms);
  tp_flag_set(tp, is_burnable);    // is capable of being burned by fire
  tp_flag_set(tp, is_combustible); // will continue to burn once on fire
  tp_flag_set(tp, is_described_cursor);
  tp_flag_set(tp, is_door_unlocked);
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
  tp_flag_set(tp, is_collision_square);
  tp_flag_set(tp, is_teleport_blocked);
  tp_flag_set(tp, is_tickable);
  tp_flag_set(tp, is_wood);
  tp_health_set(tp, "200");
  tp_is_immunity_add(tp, THING_EVENT_WATER_DAMAGE);
  tp_long_name_set(tp, name);
  tp_priority_set(tp, THING_PRIORITY_OBJECT);
  tp_temperature_burns_at_set(tp, 100);  // celsius
  tp_temperature_damage_at_set(tp, 100); // celsius
  thing_display_get_tile_info_set(tp, tp_door_unlocked_at_display_get_tile_info);
  tp_temperature_initial_set(tp, 20); // celsius
  tp_weight_set(tp, WEIGHT_HEAVY);    // grams
  tp_z_depth_set(tp, MAP_Z_DEPTH_OBJ);
  // end sort marker1 }

  auto delay = 500;

  for (auto frame = 0; frame < 2; frame++) {
    auto tile = tile_find_mand(name + std::string(".idle.") + std::to_string(frame));
    tile_size_set(tile, TILE_WIDTH, TILE_HEIGHT);
    tile_delay_ms_set(tile, delay);
    tp_tiles_push_back(tp, THING_ANIM_IDLE, tile);
  }

  auto tile = tile_find_mand("door_unlocked.open.0");
  tile_size_set(tile, TILE_WIDTH, TILE_HEIGHT);
  tp_tiles_push_back(tp, THING_ANIM_OPEN, tile);

  door_unlocked_idle_damaged = tile_find_mand("door_unlocked.idle.damaged");
  tile_size_set(door_unlocked_idle_damaged, TILE_WIDTH, TILE_HEIGHT);

  door_unlocked_open_damaged = tile_find_mand("door_unlocked.open.damaged");
  tile_size_set(door_unlocked_open_damaged, TILE_WIDTH, TILE_HEIGHT);

  return true;
}
