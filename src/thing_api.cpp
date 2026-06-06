//
// Copyright goblinhack@gmail.com
//

#include <algorithm>
#include <cstdint>
#include <limits>
#include <utility>

#include "my_bpoint.hpp"
#include "my_callstack.hpp"
#include "my_fpoint.hpp"
#include "my_game_defs.hpp"
#include "my_globals.hpp"
#include "my_level.hpp"
#include "my_main.hpp"
#include "my_spoint.hpp"
#include "my_thing.hpp"
#include "my_thing_callbacks.hpp"
#include "my_thing_inlines.hpp"
#include "my_tp.hpp"
#include "my_types.hpp"

[[nodiscard]] auto thing_at(Thingp t) -> bpoint
{
  TRACE_DEBUG();

  if (t == nullptr) {
    CROAK("no thing pointer");
  }
  return make_bpoint(t->_at);
}

void thing_at_set(Gamep /*g*/, Levelsp /*v*/, Levelp l, Thingp t, const bpoint &val)
{
  TRACE_DEBUG();

  if (t == nullptr) {
    CROAK("no thing pointer");
  }

  auto valf = make_fpoint(val);

  if (thing_is_player(t)) {
    if (t->_at != valf) {
      l->request_to_update_per_tile_visibility = true;
    }
  }

  t->_old_at = t->_at;
  t->_at     = valf;
}

[[nodiscard]] auto thing_real_at(Thingp t) -> fpoint
{
  TRACE_DEBUG();

  if (t == nullptr) {
    CROAK("no thing pointer");
  }
  return t->_at;
}

void thing_at_set(Gamep /*g*/, Levelsp /*v*/, Levelp l, Thingp t, const fpoint &val)
{
  TRACE_DEBUG();

  if (t == nullptr) {
    CROAK("no thing pointer");
  }

  if (thing_is_player(t)) {
    if (t->_at != val) {
      l->request_to_update_per_tile_visibility = true;
    }
  }

  t->_old_at = t->_at;
  t->_at     = val;
}

[[nodiscard]] auto thing_old_at(Thingp t) -> bpoint
{
  TRACE_DEBUG();

  if (t == nullptr) {
    CROAK("no thing pointer");
  }
  return make_bpoint(t->_old_at);
}

[[nodiscard]] auto thing_prev_pix_at(Thingp t) -> spoint
{
  TRACE_DEBUG();

  if (t == nullptr) {
    CROAK("no thing pointer");
  }
  return t->_prev_pix_at;
}

void thing_prev_pix_at_set(Gamep /*g*/, Levelsp v, Levelp l, Thingp t, const spoint &val)
{
  TRACE_DEBUG();

  if (t == nullptr) {
    CROAK("no thing pointer");
  }
  t->_prev_pix_at = val;
}

void thing_pix_at_set(Gamep /*g*/, Levelsp /*v*/, Levelp l, Thingp t, const spoint &val)
{
  TRACE_DEBUG();

  if (t == nullptr) {
    CROAK("no thing pointer");
  }

  if (thing_is_player(t)) {
    if (t->_curr_pix_at != val) {
      l->request_to_update_per_pixel_visibility = true;
    }
  }

  t->_prev_pix_at = t->_curr_pix_at;
  t->_curr_pix_at = val;
}

void thing_pix_at_set(Gamep /*g*/, Levelsp /*v*/, Levelp l, Thingp t, short x, short y)
{
  TRACE_DEBUG();

  if (t == nullptr) {
    CROAK("no thing pointer");
  }

  spoint const val(x, y);

  if (thing_is_player(t)) {
    if (t->_curr_pix_at != val) {
      l->request_to_update_per_pixel_visibility = true;
    }
  }

  t->_prev_pix_at = t->_curr_pix_at;
  t->_curr_pix_at = val;
}

[[nodiscard]] auto thing_moving_from(Thingp t) -> bpoint
{
  TRACE_DEBUG();

  if (t == nullptr) {
    CROAK("no thing pointer");
  }
  return t->_moving_from;
}

void thing_moving_from_set(Thingp t, const bpoint &val)
{
  TRACE_DEBUG();

  if (t == nullptr) {
    CROAK("no thing pointer");
  }
  t->_moving_from = val;
}

[[nodiscard]] auto thing_speed(Thingp t) -> int
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return 0;
  }
  return t->_speed;
}

[[nodiscard]] auto thing_speed_set(Gamep /*g*/, Levelsp v, Levelp l, Thingp t, int val) -> int
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return 0;
  }

  if (std::cmp_greater(val, std::numeric_limits< decltype(t->_speed) >::max())) {
    thing_err(t, "value overflow: %d", val);
    return 0;
  }

  return t->_speed = val;
}

[[nodiscard]] auto thing_weight(Thingp t) -> int
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return 0;
  }
  return t->_weight;
}

[[nodiscard]] auto thing_weight_set(Gamep /*g*/, Levelsp v, Levelp l, Thingp t, uint32_t val) -> int
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return 0;
  }

  if (val > std::numeric_limits< decltype(t->_weight) >::max()) {
    thing_err(t, "value overflow: %d", val);
    return 0;
  }

  return t->_weight = val;
}

void thing_is_falling_set(Gamep g, Levelsp v, Levelp l, Thingp t, bool val)
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return;
  }

  //
  // Once falling, it is treated as a counter
  //
  if (val) {
    //
    // Start falling if not doing do
    //
    if (static_cast< bool >(t->_fall_ms)) {
      return;
    }
  } else {
    //
    // Stop falling
    //
    if (! static_cast< bool >(t->_fall_ms)) {
      return;
    }
  }
  t->_fall_ms = static_cast< uint16_t >(val);

  if (val) {
    thing_on_fall_begin(g, v, l, t);
  } else {
    thing_on_fall_end(g, v, l, t);
  }
}

[[nodiscard]] auto thing_is_falling_incr(Gamep /*g*/, Levelsp v, Levelp l, Thingp t, int val) -> int
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return 0;
  }

  if (t->_fall_ms + val > THING_FALL_ANIM_MS) {
    return t->_fall_ms = THING_FALL_ANIM_MS;
  }

  return t->_fall_ms += val;
}

[[nodiscard]] auto thing_is_falling_continues(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }

  return t->_is_falling_continues;
}

void thing_is_falling_continues_set(Gamep g, Levelsp v, Levelp l, Thingp t, bool val)
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return;
  }

  if (t->_is_falling_continues == static_cast< int >(val)) {
    return;
  }
  t->_is_falling_continues = val;

  if (val) {
    THING_DBG(t, "is falling continues set");
  }

  level_request_to_cleanup_things_set(g, v, l);
}

void thing_is_falling_continues_unset(Gamep g, Levelsp v, Levelp l, Thingp t)
{
  TRACE_DEBUG();

  thing_is_falling_continues_set(g, v, l, t, false);
}

[[nodiscard]] auto thing_temperature(Thingp t) -> int
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return 0;
  }
  return t->_temperature;
}

[[nodiscard]] auto thing_temperature_set(Gamep /*g*/, Levelsp v, Levelp l, Thingp t, int val) -> int
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return 0;
  }

  if (val > std::numeric_limits< decltype(t->_temperature) >::max()) {
    thing_err(t, "value overflow: %d", val);
    return 0;
  }

  if (! thing_is_physics_temperature(t)) {
    return 0;
  }

  //
  // Don't keep on heating up forever!
  //
  auto *tp    = thing_tp(t);
  auto  limit = std::max(tp_temperature_burns_at_get(tp), tp_temperature_melts_at_get(tp));
  if ((limit != 0) && (val > limit)) {
    val = limit;
  }

  IF_DEBUG2
  { //
    THING_DBG(t, "temperature set to %u degrees", val);
  }

  return t->_temperature = val;
}

[[nodiscard]] auto thing_temperature_incr(Gamep g, Levelsp v, Levelp l, Thingp t, int val) -> int
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return 0;
  }
  return thing_temperature_set(g, v, l, t, t->_temperature + val);
}

[[nodiscard]] auto thing_temperature_decr(Gamep g, Levelsp v, Levelp l, Thingp t, int val) -> int
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return 0;
  }
  return thing_temperature_set(g, v, l, t, t->_temperature - val);
}

[[nodiscard]] auto thing_damage_this_tick(Thingp t) -> int
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return 0;
  }
  return t->_damage_this_tick;
}

[[nodiscard]] auto thing_damage_this_tick_set(Gamep /*g*/, Levelsp v, Levelp l, Thingp t, int val) -> int
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return 0;
  }

  if (val > std::numeric_limits< decltype(t->_damage_this_tick) >::max()) {
    thing_err(t, "value overflow: %d", val);
    return 0;
  }

  return t->_damage_this_tick = val;
}

[[nodiscard]] auto thing_damage_this_tick_incr(Gamep /*g*/, Levelsp v, Levelp l, Thingp t, int val) -> int
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return 0;
  }
  return t->_damage_this_tick += val;
}

[[nodiscard]] auto thing_damage_this_tick_decr(Gamep /*g*/, Levelsp v, Levelp l, Thingp t, int val) -> int
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return 0;
  }
  return t->_damage_this_tick -= val;
}

[[nodiscard]] auto thing_keys_carried(Thingp t) -> int
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return 0;
  }
  return t->_keys_carried;
}

[[nodiscard]] auto thing_keys_carried_set(Gamep /*g*/, Levelsp v, Levelp l, Thingp t, int val) -> int
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return 0;
  }

  if (val > std::numeric_limits< decltype(t->_keys_carried) >::max()) {
    thing_err(t, "value overflow: %d", val);
    return 0;
  }

  return t->_keys_carried = val;
}

[[nodiscard]] auto thing_keys_carried_incr(Gamep /*g*/, Levelsp v, Levelp l, Thingp t, int val) -> int
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return 0;
  }
  return t->_keys_carried += val;
}

[[nodiscard]] auto thing_keys_carried_decr(Gamep /*g*/, Levelsp v, Levelp l, Thingp t, int val) -> int
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return 0;
  }

  if (static_cast< int >(t->_keys_carried) - val <= 0) {
    return t->_keys_carried = 0;
  }

  return t->_keys_carried -= val;
}

void thing_is_dead_set(Gamep /*g*/, Levelsp v, Levelp l, Thingp t, bool val)
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return;
  }

  if (t->_is_dead == static_cast< int >(val)) {
    return;
  }
  t->_is_dead = val;

  if (val) {
    THING_DBG(t, "is dead set");
  }
}

void thing_is_dead_unset(Gamep g, Levelsp v, Levelp l, Thingp t)
{
  TRACE_DEBUG();

  thing_is_dead_set(g, v, l, t, false);
}

[[nodiscard]] auto thing_is_burning(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return t->_is_burning;
}

void thing_is_burning_set(Gamep g, Levelsp v, Levelp l, Thingp t, bool val)
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return;
  }

  if (t->_is_burning == static_cast< int >(val)) {
    return;
  }
  t->_is_burning = val;

  if (val) {
    THING_DBG(t, "is burning set, %u degrees", thing_temperature(t));
  } else {
    //
    // Reset the temperature
    //
    auto *tp = thing_tp(t);
    (void) thing_temperature_set(g, v, l, t, tp_temperature_initial_get(tp));

    THING_DBG(t, "is no longer burning, %u degrees", thing_temperature(t));
  }

  thing_is_burning_handle(g, v, l, t);
}

void thing_is_burning_unset(Gamep g, Levelsp v, Levelp l, Thingp t)
{
  TRACE_DEBUG();

  thing_is_burning_set(g, v, l, t, false);
}

[[nodiscard]] auto thing_is_corpse(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return t->_is_corpse;
}

void thing_is_corpse_set(Gamep /*g*/, Levelsp v, Levelp l, Thingp t, bool val)
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return;
  }

  if (t->_is_corpse == static_cast< int >(val)) {
    return;
  }
  t->_is_corpse = val;

  if (val) {
    THING_DBG(t, "is corpse set");
  }
}

void thing_is_corpse_unset(Gamep g, Levelsp v, Levelp l, Thingp t)
{
  TRACE_DEBUG();

  thing_is_corpse_set(g, v, l, t, false);
}

[[nodiscard]] auto thing_is_scheduled_for_cleanup(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }

  return t->_is_scheduled_for_cleanup;
}

void thing_is_scheduled_for_cleanup_set(Gamep g, Levelsp v, Levelp l, Thingp t, bool val)
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return;
  }

  if (t->_is_scheduled_for_cleanup == static_cast< int >(val)) {
    return;
  }
  t->_is_scheduled_for_cleanup = val;

  if (val) {
    THING_DBG(t, "is scheduled for cleanup set");
  }

  level_request_to_cleanup_things_set(g, v, l);
}

void thing_is_scheduled_for_cleanup_unset(Gamep g, Levelsp v, Levelp l, Thingp t)
{
  TRACE_DEBUG();

  thing_is_scheduled_for_cleanup_set(g, v, l, t, false);
}

[[nodiscard]] auto thing_is_on_map(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return t->_is_on_map;
}

void thing_is_on_map_set(Gamep /*g*/, Levelsp v, Levelp l, Thingp t, bool val)
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return;
  }
  t->_is_on_map = val;
}

void thing_is_on_map_unset(Gamep g, Levelsp v, Levelp l, Thingp t)
{
  TRACE_DEBUG();

  thing_is_on_map_set(g, v, l, t, false);
}

[[nodiscard]] auto thing_is_animated_can_hflip(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_animated_can_hflip) != 0;
}

[[nodiscard]] auto thing_is_animated_no_dir(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_animated_no_dir) != 0;
}

[[nodiscard]] auto thing_is_animated_sync_first(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_animated_sync_first) != 0;
}

[[nodiscard]] auto thing_is_animated(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_animated) != 0;
}

[[nodiscard]] auto thing_is_barrel(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_barrel) != 0;
}

[[nodiscard]] auto thing_is_blit_centered(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_blit_centered) != 0;
}

[[nodiscard]] auto thing_is_blit_flush_per_line(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_blit_flush_per_line) != 0;
}

[[nodiscard]] auto thing_is_blit_outlined(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_blit_outlined) != 0;
}

[[nodiscard]] auto thing_is_blit_square_outlined(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_blit_square_outlined) != 0;
}

[[nodiscard]] auto thing_is_brazier(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_brazier) != 0;
}

[[nodiscard]] auto thing_is_bridge(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_bridge) != 0;
}

[[nodiscard]] auto thing_is_chasm(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_chasm) != 0;
}

[[nodiscard]] auto thing_is_corridor(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_corridor) != 0;
}

[[nodiscard]] auto thing_is_collision_square(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_collision_square) != 0;
}

[[nodiscard]] auto thing_is_obs_to_cursor_path(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }

  //
  // Unless open
  //
  if (thing_is_openable(t)) {
    if (thing_is_open(t)) {
      return false;
    }
  }

  return tp_flag(thing_tp(t), is_obs_to_cursor_path) != 0;
}

[[nodiscard]] auto thing_is_cursor_path_hazard(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_cursor_path_hazard) != 0;
}

[[nodiscard]] auto thing_is_cursor_path(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_cursor_path) != 0;
}

[[nodiscard]] auto thing_is_cursor(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_cursor) != 0;
}

[[nodiscard]] auto thing_is_deep_water(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_deep_water) != 0;
}

[[nodiscard]] auto thing_is_described_cursor(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_described_cursor) != 0;
}

[[nodiscard]] auto thing_is_dirt(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_dirt) != 0;
}

[[nodiscard]] auto thing_is_door_unlocked(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_door_unlocked) != 0;
}

[[nodiscard]] auto thing_is_dungeon_entrance(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_dungeon_entrance) != 0;
}

[[nodiscard]] auto thing_is_entrance(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_entrance) != 0;
}

[[nodiscard]] auto thing_is_exit(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_exit) != 0;
}

[[nodiscard]] auto thing_is_ghost(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_ghost) != 0;
}

[[nodiscard]] auto thing_is_kobalos(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_kobalos) != 0;
}

[[nodiscard]] auto thing_is_grass(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_grass) != 0;
}

[[nodiscard]] auto thing_is_key(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_key) != 0;
}

[[nodiscard]] auto thing_is_lava(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_lava) != 0;
}

[[nodiscard]] auto thing_is_usable(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_usable) != 0;
}

[[nodiscard]] auto thing_is_level_curr(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_level_curr) != 0;
}

[[nodiscard]] auto thing_is_critical_to_level(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_critical_to_level) != 0;
}

[[nodiscard]] auto thing_is_level_final_icon(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_level_final_icon) != 0;
}

[[nodiscard]] auto thing_is_level_next_icon(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_level_next_icon) != 0;
}

[[nodiscard]] auto thing_is_level_locked_icon(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_level_locked_icon) != 0;
}

[[nodiscard]] auto thing_is_level_closed_icon(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_level_closed_icon) != 0;
}

[[nodiscard]] auto thing_is_minion(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_minion) != 0;
}

[[nodiscard]] auto thing_is_mob(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_mob) != 0;
}

[[nodiscard]] auto thing_is_mob1(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_mob1) != 0;
}

[[nodiscard]] auto thing_is_mob2(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_mob2) != 0;
}

[[nodiscard]] auto thing_is_monst(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_monst) != 0;
}

[[nodiscard]] auto thing_is_monst1(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_monst1) != 0;
}

[[nodiscard]] auto thing_is_monst2(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_monst2) != 0;
}

[[nodiscard]] auto thing_is_obs_to_movement(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }

  //
  // Unless open
  //
  if (thing_is_openable(t)) {
    if (thing_is_open(t)) {
      return false;
    }
  }

  return tp_flag(thing_tp(t), is_obs_to_movement) != 0;
}

[[nodiscard]] auto thing_is_pillar(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_pillar) != 0;
}

[[nodiscard]] auto thing_is_rock(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_rock) != 0;
}

[[nodiscard]] auto thing_is_door_secret(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_door_secret) != 0;
}

[[nodiscard]] auto thing_is_slime(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_slime) != 0;
}

[[nodiscard]] auto thing_is_teleport(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_teleport) != 0;
}

[[nodiscard]] auto thing_is_tickable(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_tickable) != 0;
}

[[nodiscard]] auto thing_is_tiled(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_tiled) != 0;
}

[[nodiscard]] auto thing_is_trap(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_trap) != 0;
}

[[nodiscard]] auto thing_is_treasure(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_treasure) != 0;
}

[[nodiscard]] auto thing_is_unused1(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_unused1) != 0;
}

[[nodiscard]] auto thing_is_unused2(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_unused2) != 0;
}

[[nodiscard]] auto thing_is_unused3(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_unused3) != 0;
}

[[nodiscard]] auto thing_is_unused4(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_unused4) != 0;
}

[[nodiscard]] auto thing_is_unused5(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_unused5) != 0;
}

[[nodiscard]] auto thing_is_unused6(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_unused6) != 0;
}

[[nodiscard]] auto thing_is_unused7(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_unused7) != 0;
}

[[nodiscard]] auto thing_is_unused8(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_unused8) != 0;
}

[[nodiscard]] auto thing_is_unused9(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_unused9) != 0;
}

[[nodiscard]] auto thing_is_unused10(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_unused10) != 0;
}

[[nodiscard]] auto thing_is_unused11(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_unused11) != 0;
}

[[nodiscard]] auto thing_is_unused12(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_unused12) != 0;
}

[[nodiscard]] auto thing_is_unused13(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_unused13) != 0;
}

[[nodiscard]] auto thing_is_unused14(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_unused14) != 0;
}

[[nodiscard]] auto thing_is_unused15(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_unused15) != 0;
}

[[nodiscard]] auto thing_is_unused16(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_unused16) != 0;
}

[[nodiscard]] auto thing_is_buff(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_buff) != 0;
}

[[nodiscard]] auto thing_is_able_to_be_buffed(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_able_to_be_buffed) != 0;
}

[[nodiscard]] auto thing_is_tick_on_drop(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_tick_on_drop) != 0;
}

[[nodiscard]] auto thing_is_tick_on_use(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_tick_on_use) != 0;
}

[[nodiscard]] auto thing_is_able_to_throw_items(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_able_to_throw_items) != 0;
}

[[nodiscard]] auto thing_is_throwable(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_throwable) != 0;
}

[[nodiscard]] auto thing_is_described_when_killed(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_described_when_killed) != 0;
}

[[nodiscard]] auto thing_is_chest(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_chest) != 0;
}

[[nodiscard]] auto thing_is_flammable(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_flammable) != 0;
}

[[nodiscard]] auto thing_is_auto_wield(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_auto_wield) != 0;
}

[[nodiscard]] auto thing_is_dead_when_discharged(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_dead_when_discharged) != 0;
}

[[nodiscard]] auto thing_is_able_to_fire_weapons(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_able_to_fire_weapons) != 0;
}

[[nodiscard]] auto thing_wieldable(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), wieldable) != 0;
}

[[nodiscard]] auto thing_is_able_to_wield_items(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_able_to_wield_items) != 0;
}

[[nodiscard]] auto thing_is_wand(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_wand) != 0;
}

[[nodiscard]] auto thing_is_staff(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_staff) != 0;
}

[[nodiscard]] auto thing_is_argusul(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_argusul) != 0;
}

[[nodiscard]] auto thing_is_wait_on_anim(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_wait_on_anim) != 0;
}

[[nodiscard]] auto thing_is_flat(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_flat) != 0;
}

[[nodiscard]] auto thing_is_obs_to_laser(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_obs_to_laser) != 0;
}

[[nodiscard]] auto thing_is_laser(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_laser) != 0;
}

[[nodiscard]] auto thing_is_vault(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_vault) != 0;
}

[[nodiscard]] auto thing_is_biome_underhell(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_biome_underhell) != 0;
}

[[nodiscard]] auto thing_is_biome_graveyard(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_biome_graveyard) != 0;
}

[[nodiscard]] auto thing_is_biome_nethervoid(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_biome_nethervoid) != 0;
}

[[nodiscard]] auto thing_is_biome_bogland(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_biome_bogland) != 0;
}

[[nodiscard]] auto thing_is_biome_dungeon(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_biome_dungeon) != 0;
}

[[nodiscard]] auto thing_is_level_open_icon(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_level_open_icon) != 0;
}

[[nodiscard]] auto thing_is_blit_bg(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_blit_bg) != 0;
}

[[nodiscard]] auto thing_is_level_select_bg(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_level_select_bg) != 0;
}

[[nodiscard]] auto thing_is_blit_hit_outline_w_black_inside(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_blit_hit_outline_w_black_inside) != 0;
}

[[nodiscard]] auto thing_is_able_to_fall_sound(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_able_to_fall_sound) != 0;
}

[[nodiscard]] auto thing_is_collision_hit_first_on_tile(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_collision_hit_first_on_tile) != 0;
}

[[nodiscard]] auto thing_is_collision_hit_all_on_tile(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_collision_hit_all_on_tile) != 0;
}

[[nodiscard]] auto thing_is_blit_hit_outline_w_invis_inside(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_blit_hit_outline_w_invis_inside) != 0;
}

[[nodiscard]] auto thing_is_blit_when_obscured_outline(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_blit_when_obscured_outline) != 0;
}

[[nodiscard]] auto thing_is_attackable_by_player(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_attackable_by_player) != 0;
}

[[nodiscard]] auto thing_is_attackable_by_monst(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_attackable_by_monst) != 0;
}

[[nodiscard]] auto thing_is_effect(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_effect) != 0;
}

[[nodiscard]] auto thing_is_effect_attack(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_effect_attack) != 0;
}

[[nodiscard]] auto thing_is_effect_blood(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_effect_blood) != 0;
}

[[nodiscard]] auto thing_is_hit_when_dead(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_hit_when_dead) != 0;
}

[[nodiscard]] auto thing_is_blitzhound(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_blitzhound) != 0;
}

[[nodiscard]] auto thing_is_potion(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_potion) != 0;
}

[[nodiscard]] auto thing_is_grouped_thing(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_grouped_thing) != 0;
}

[[nodiscard]] auto thing_is_able_to_lunge(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_able_to_lunge) != 0;
}

[[nodiscard]] auto thing_is_obs_to_paths(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_obs_to_paths) != 0;
}

[[nodiscard]] auto thing_is_removable_when_dead_on_err(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_removable_when_dead_on_err) != 0;
}

[[nodiscard]] auto thing_is_removable_on_err(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_removable_on_err) != 0;
}

[[nodiscard]] auto thing_is_obs_when_dead(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_obs_when_dead) != 0;
}

[[nodiscard]] auto thing_is_able_to_fall_repeatedly(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_able_to_fall_repeatedly) != 0;
}

[[nodiscard]] auto thing_is_able_to_move_through_walls(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_able_to_move_through_walls) != 0;
}

[[nodiscard]] auto thing_is_able_to_move_diagonally(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_able_to_move_diagonally) != 0;
}

[[nodiscard]] auto thing_is_blit_on_ground(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_blit_on_ground) != 0;
}

[[nodiscard]] auto thing_is_insectoid(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_insectoid) != 0;
}

[[nodiscard]] auto thing_is_mantisman(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_mantisman) != 0;
}

[[nodiscard]] auto thing_is_dmap(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_dmap) != 0;
}

[[nodiscard]] auto thing_is_obs_to_spawning(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_obs_to_spawning) != 0;
}

[[nodiscard]] auto thing_is_mob_kill_minions_on_death(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_mob_kill_minions_on_death) != 0;
}

[[nodiscard]] auto thing_is_border(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_border) != 0;
}

[[nodiscard]] auto thing_is_collision_detection_enabled(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_collision_detection_enabled) != 0;
}

[[nodiscard]] auto thing_is_gold(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_gold) != 0;
}

[[nodiscard]] auto thing_is_glass(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_glass) != 0;
}

[[nodiscard]] auto thing_is_plant(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_plant) != 0;
}

[[nodiscard]] auto thing_is_wood(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_wood) != 0;
}

[[nodiscard]] auto thing_is_metal(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_metal) != 0;
}

[[nodiscard]] auto thing_is_flesh(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_flesh) != 0;
}

[[nodiscard]] auto thing_is_stone(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_stone) != 0;
}

[[nodiscard]] auto thing_is_meltable(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_meltable) != 0;
}

[[nodiscard]] auto thing_is_blit_per_pixel_lighting(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_blit_per_pixel_lighting) != 0;
}

[[nodiscard]] auto thing_is_dead_on_collision(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_dead_on_collision) != 0;
}

[[nodiscard]] auto thing_is_obs_to_jumping_out_of(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_obs_to_jumping_out_of) != 0;
}

[[nodiscard]] auto thing_is_cursor_path_warning(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_cursor_path_warning) != 0;
}

[[nodiscard]] auto thing_is_collision_circle_large(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_collision_circle_large) != 0;
}

[[nodiscard]] auto thing_is_collision_circle_small(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_collision_circle_small) != 0;
}

[[nodiscard]] auto thing_is_fireball(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_fireball) != 0;
}

[[nodiscard]] auto thing_is_projectile(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_projectile) != 0;
}

[[nodiscard]] auto thing_is_item_mergeable(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_item_mergeable) != 0;
}

[[nodiscard]] auto thing_is_door_locked(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_door_locked) != 0;
}

[[nodiscard]] auto thing_is_inventory_item(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_inventory_item) != 0;
}

[[nodiscard]] auto thing_is_able_to_open_things(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_able_to_open_things) != 0;
}

[[nodiscard]] auto thing_is_item(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_item) != 0;
}

[[nodiscard]] auto thing_is_able_to_crush_grass(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_able_to_crush_grass) != 0;
}

[[nodiscard]] auto thing_is_able_to_collect_keys(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_able_to_collect_keys) != 0;
}

[[nodiscard]] auto thing_is_able_to_collect_items(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_able_to_collect_items) != 0;
}

[[nodiscard]] auto thing_is_collectable(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_collectable) != 0;
}

[[nodiscard]] auto thing_is_blit_when_obscured_faded(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_blit_when_obscured_faded) != 0;
}

[[nodiscard]] auto thing_is_openable(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_openable) != 0;
}

[[nodiscard]] auto thing_is_tick_end_delay(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_tick_end_delay) != 0;
}

[[nodiscard]] auto thing_is_damage_capped(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_damage_capped) != 0;
}

[[nodiscard]] auto thing_is_physics_explosion(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_physics_explosion) != 0;
}

[[nodiscard]] auto thing_is_explosion(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_explosion) != 0;
}

[[nodiscard]] auto thing_is_obs_to_explosion(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }

  //
  // Unless open
  //
  if (thing_is_openable(t)) {
    if (thing_is_open(t)) {
      return false;
    }
  }

  return tp_flag(thing_tp(t), is_obs_to_explosion) != 0;
}

[[nodiscard]] auto thing_is_obs_to_jump_over(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }

  //
  // Unless open
  //
  if (thing_is_openable(t)) {
    if (thing_is_open(t)) {
      return false;
    }
  }

  return tp_flag(thing_tp(t), is_obs_to_jump_over) != 0;
}

[[nodiscard]] auto thing_is_teleport_blocked(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_teleport_blocked) != 0;
}

[[nodiscard]] auto thing_is_cursor_path_none(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_cursor_path_none) != 0;
}

[[nodiscard]] auto thing_is_able_to_jump(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_able_to_jump) != 0;
}

[[nodiscard]] auto thing_is_blit_obscures(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_blit_obscures) != 0;
}

[[nodiscard]] auto thing_is_flying(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_flying) != 0;
}

[[nodiscard]] auto thing_is_needs_move_confirm(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_needs_move_confirm) != 0;
}

[[nodiscard]] auto thing_is_obs_to_falling_onto(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }

  //
  // Unless open
  //
  if (thing_is_openable(t)) {
    if (thing_is_open(t)) {
      return false;
    }
  }

  return tp_flag(thing_tp(t), is_obs_to_falling_onto) != 0;
}

[[nodiscard]] auto thing_is_obs_to_jumping_onto(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }

  //
  // Unless open
  //
  if (thing_is_openable(t)) {
    if (thing_is_open(t)) {
      return false;
    }
  }

  return tp_flag(thing_tp(t), is_obs_to_jumping_onto) != 0;
}

[[nodiscard]] auto thing_is_obs_to_teleporting_onto(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }

  //
  // Unless open
  //
  if (thing_is_openable(t)) {
    if (thing_is_open(t)) {
      return false;
    }
  }

  return tp_flag(thing_tp(t), is_obs_to_teleporting_onto) != 0;
}

[[nodiscard]] auto thing_is_able_to_fall(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_able_to_fall) != 0;
}

[[nodiscard]] auto thing_is_physics_water(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_physics_water) != 0;
}

[[nodiscard]] auto thing_is_indestructible(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_indestructible) != 0;
}

[[nodiscard]] auto thing_is_floating(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_floating) != 0;
}

[[nodiscard]] auto thing_is_obs_to_fire(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }

  //
  // Unless open
  //
  if (thing_is_openable(t)) {
    if (thing_is_open(t)) {
      return false;
    }
  }

  return tp_flag(thing_tp(t), is_obs_to_fire) != 0;
}

[[nodiscard]] auto thing_is_combustible(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_combustible) != 0;
}

[[nodiscard]] auto thing_is_blit_shown_in_chasms(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_blit_shown_in_chasms) != 0;
}

[[nodiscard]] auto thing_is_gaseous(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_gaseous) != 0;
}

[[nodiscard]] auto thing_is_extinguished_on_death(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_extinguished_on_death) != 0;
}

[[nodiscard]] auto thing_is_broken_on_death(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_broken_on_death) != 0;
}

[[nodiscard]] auto thing_is_undead(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_undead) != 0;
}

[[nodiscard]] auto thing_is_wait_on_dead_anim(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_wait_on_dead_anim) != 0;
}

[[nodiscard]] auto thing_is_corpse_on_death(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_corpse_on_death) != 0;
}

[[nodiscard]] auto thing_is_blit_if_has_seen(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_blit_if_has_seen) != 0;
}

[[nodiscard]] auto thing_is_smoke(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_smoke) != 0;
}

[[nodiscard]] auto thing_is_steam(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_steam) != 0;
}

[[nodiscard]] auto thing_is_fire(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_fire) != 0;
}

[[nodiscard]] auto thing_is_burnable(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_burnable) != 0;
}

[[nodiscard]] auto thing_is_dead_on_shoving(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_dead_on_shoving) != 0;
}

[[nodiscard]] auto thing_is_able_to_shove(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_able_to_shove) != 0;
}

[[nodiscard]] auto thing_is_shovable(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_shovable) != 0;
}

[[nodiscard]] auto thing_is_loggable(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }

  if (g_opt_tests) {
    //
    // Everything is logged
    //
    return true;
  }

  IF_DEBUG2
  {
    //
    // Everything is logged
    //
    return true;
  }

  return tp_flag(thing_tp(t), is_loggable) != 0;
}

[[nodiscard]] auto thing_is_crushable(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_crushable) != 0;
}

[[nodiscard]] auto thing_is_ethereal(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_ethereal) != 0;
}

[[nodiscard]] auto thing_is_blit_shown_in_overlay(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_blit_shown_in_overlay) != 0;
}

[[nodiscard]] auto thing_is_levitating(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_levitating) != 0;
}

[[nodiscard]] auto thing_is_equippable(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_equippable) != 0;
}

[[nodiscard]] auto thing_is_droppable(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_droppable) != 0;
}

[[nodiscard]] auto thing_is_able_to_walk_through_walls(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_able_to_walk_through_walls) != 0;
}

[[nodiscard]] auto thing_value1(Thingp t) -> int
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return 0;
  }
  return t->_value1;
}

[[nodiscard]] auto thing_value1_set(Gamep /*g*/, Levelsp v, Levelp l, Thingp t, int val) -> int
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return 0;
  }
  return t->_value1 = val;
}

[[nodiscard]] auto thing_value1_incr(Gamep /*g*/, Levelsp v, Levelp l, Thingp t, int val) -> int
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return 0;
  }
  return t->_value1 += val;
}

[[nodiscard]] auto thing_value1_decr(Gamep /*g*/, Levelsp v, Levelp l, Thingp t, int val) -> int
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return 0;
  }
  if (static_cast< int >(t->_value1) - val <= 0) {
    return t->_value1 = 0;
  }
  return t->_value1 -= val;
}
[[nodiscard]] auto thing_value2(Thingp t) -> int
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return 0;
  }
  return t->_value2;
}

[[nodiscard]] auto thing_value2_set(Gamep /*g*/, Levelsp v, Levelp l, Thingp t, int val) -> int
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return 0;
  }
  return t->_value2 = val;
}

[[nodiscard]] auto thing_value2_incr(Gamep /*g*/, Levelsp v, Levelp l, Thingp t, int val) -> int
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return 0;
  }
  return t->_value2 += val;
}

[[nodiscard]] auto thing_value2_decr(Gamep /*g*/, Levelsp v, Levelp l, Thingp t, int val) -> int
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return 0;
  }
  if (static_cast< int >(t->_value2) - val <= 0) {
    return t->_value2 = 0;
  }
  return t->_value2 -= val;
}
[[nodiscard]] auto thing_value3(Thingp t) -> int
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return 0;
  }
  return t->_value3;
}

[[nodiscard]] auto thing_value3_set(Gamep /*g*/, Levelsp v, Levelp l, Thingp t, int val) -> int
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return 0;
  }
  return t->_value3 = val;
}

[[nodiscard]] auto thing_value3_incr(Gamep /*g*/, Levelsp v, Levelp l, Thingp t, int val) -> int
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return 0;
  }
  return t->_value3 += val;
}

[[nodiscard]] auto thing_value3_decr(Gamep /*g*/, Levelsp v, Levelp l, Thingp t, int val) -> int
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return 0;
  }
  if (static_cast< int >(t->_value3) - val <= 0) {
    return t->_value3 = 0;
  }
  return t->_value3 -= val;
}
[[nodiscard]] auto thing_value4(Thingp t) -> int
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return 0;
  }
  return t->_value4;
}

[[nodiscard]] auto thing_value4_set(Gamep /*g*/, Levelsp v, Levelp l, Thingp t, int val) -> int
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return 0;
  }
  return t->_value4 = val;
}

[[nodiscard]] auto thing_value4_incr(Gamep /*g*/, Levelsp v, Levelp l, Thingp t, int val) -> int
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return 0;
  }
  return t->_value4 += val;
}

[[nodiscard]] auto thing_value4_decr(Gamep /*g*/, Levelsp v, Levelp l, Thingp t, int val) -> int
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return 0;
  }
  if (static_cast< int >(t->_value4) - val <= 0) {
    return t->_value4 = 0;
  }
  return t->_value4 -= val;
}
[[nodiscard]] auto thing_value5(Thingp t) -> int
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return 0;
  }
  return t->_value5;
}

[[nodiscard]] auto thing_value5_set(Gamep /*g*/, Levelsp v, Levelp l, Thingp t, int val) -> int
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return 0;
  }
  return t->_value5 = val;
}

[[nodiscard]] auto thing_value5_incr(Gamep /*g*/, Levelsp v, Levelp l, Thingp t, int val) -> int
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return 0;
  }
  return t->_value5 += val;
}

[[nodiscard]] auto thing_value5_decr(Gamep /*g*/, Levelsp v, Levelp l, Thingp t, int val) -> int
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return 0;
  }
  if (static_cast< int >(t->_value5) - val <= 0) {
    return t->_value5 = 0;
  }
  return t->_value5 -= val;
}
[[nodiscard]] auto thing_value6(Thingp t) -> int
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return 0;
  }
  return t->_value6;
}

[[nodiscard]] auto thing_value6_set(Gamep /*g*/, Levelsp v, Levelp l, Thingp t, int val) -> int
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return 0;
  }
  return t->_value6 = val;
}

[[nodiscard]] auto thing_value6_incr(Gamep /*g*/, Levelsp v, Levelp l, Thingp t, int val) -> int
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return 0;
  }
  return t->_value6 += val;
}

[[nodiscard]] auto thing_value6_decr(Gamep /*g*/, Levelsp v, Levelp l, Thingp t, int val) -> int
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return 0;
  }
  if (static_cast< int >(t->_value6) - val <= 0) {
    return t->_value6 = 0;
  }
  return t->_value6 -= val;
}
[[nodiscard]] auto thing_value7(Thingp t) -> int
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return 0;
  }
  return t->_value7;
}

[[nodiscard]] auto thing_value7_set(Gamep /*g*/, Levelsp v, Levelp l, Thingp t, int val) -> int
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return 0;
  }
  return t->_value7 = val;
}

[[nodiscard]] auto thing_value7_incr(Gamep /*g*/, Levelsp v, Levelp l, Thingp t, int val) -> int
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return 0;
  }
  return t->_value7 += val;
}

[[nodiscard]] auto thing_value7_decr(Gamep /*g*/, Levelsp v, Levelp l, Thingp t, int val) -> int
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return 0;
  }
  if (static_cast< int >(t->_value7) - val <= 0) {
    return t->_value7 = 0;
  }
  return t->_value7 -= val;
}
[[nodiscard]] auto thing_value8(Thingp t) -> int
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return 0;
  }
  return t->_value8;
}

[[nodiscard]] auto thing_value8_set(Gamep /*g*/, Levelsp v, Levelp l, Thingp t, int val) -> int
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return 0;
  }
  return t->_value8 = val;
}

[[nodiscard]] auto thing_value8_incr(Gamep /*g*/, Levelsp v, Levelp l, Thingp t, int val) -> int
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return 0;
  }
  return t->_value8 += val;
}

[[nodiscard]] auto thing_value8_decr(Gamep /*g*/, Levelsp v, Levelp l, Thingp t, int val) -> int
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return 0;
  }
  if (static_cast< int >(t->_value8) - val <= 0) {
    return t->_value8 = 0;
  }
  return t->_value8 -= val;
}
[[nodiscard]] auto thing_value9(Thingp t) -> int
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return 0;
  }
  return t->_value9;
}

[[nodiscard]] auto thing_value9_set(Gamep /*g*/, Levelsp v, Levelp l, Thingp t, int val) -> int
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return 0;
  }
  return t->_value9 = val;
}

[[nodiscard]] auto thing_value9_incr(Gamep /*g*/, Levelsp v, Levelp l, Thingp t, int val) -> int
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return 0;
  }
  return t->_value9 += val;
}

[[nodiscard]] auto thing_value9_decr(Gamep /*g*/, Levelsp v, Levelp l, Thingp t, int val) -> int
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return 0;
  }
  if (static_cast< int >(t->_value9) - val <= 0) {
    return t->_value9 = 0;
  }
  return t->_value9 -= val;
}
[[nodiscard]] auto thing_value10(Thingp t) -> int
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return 0;
  }
  return t->_value10;
}

[[nodiscard]] auto thing_value10_set(Gamep /*g*/, Levelsp v, Levelp l, Thingp t, int val) -> int
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return 0;
  }
  return t->_value10 = val;
}

[[nodiscard]] auto thing_value10_incr(Gamep /*g*/, Levelsp v, Levelp l, Thingp t, int val) -> int
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return 0;
  }
  return t->_value10 += val;
}

[[nodiscard]] auto thing_value10_decr(Gamep /*g*/, Levelsp v, Levelp l, Thingp t, int val) -> int
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return 0;
  }
  if (static_cast< int >(t->_value10) - val <= 0) {
    return t->_value10 = 0;
  }
  return t->_value10 -= val;
}
[[nodiscard]] auto thing_value11(Thingp t) -> int
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return 0;
  }
  return t->_value11;
}

[[nodiscard]] auto thing_value11_set(Gamep /*g*/, Levelsp v, Levelp l, Thingp t, int val) -> int
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return 0;
  }
  return t->_value11 = val;
}

[[nodiscard]] auto thing_value11_incr(Gamep /*g*/, Levelsp v, Levelp l, Thingp t, int val) -> int
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return 0;
  }
  return t->_value11 += val;
}

[[nodiscard]] auto thing_value11_decr(Gamep /*g*/, Levelsp v, Levelp l, Thingp t, int val) -> int
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return 0;
  }
  if (static_cast< int >(t->_value11) - val <= 0) {
    return t->_value11 = 0;
  }
  return t->_value11 -= val;
}
[[nodiscard]] auto thing_value12(Thingp t) -> int
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return 0;
  }
  return t->_value12;
}

[[nodiscard]] auto thing_value12_set(Gamep /*g*/, Levelsp v, Levelp l, Thingp t, int val) -> int
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return 0;
  }
  return t->_value12 = val;
}

[[nodiscard]] auto thing_value12_incr(Gamep /*g*/, Levelsp v, Levelp l, Thingp t, int val) -> int
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return 0;
  }
  return t->_value12 += val;
}

[[nodiscard]] auto thing_value12_decr(Gamep /*g*/, Levelsp v, Levelp l, Thingp t, int val) -> int
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return 0;
  }
  if (static_cast< int >(t->_value12) - val <= 0) {
    return t->_value12 = 0;
  }
  return t->_value12 -= val;
}
[[nodiscard]] auto thing_value13(Thingp t) -> int
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return 0;
  }
  return t->_value13;
}

[[nodiscard]] auto thing_value13_set(Gamep /*g*/, Levelsp v, Levelp l, Thingp t, int val) -> int
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return 0;
  }
  return t->_value13 = val;
}

[[nodiscard]] auto thing_value13_incr(Gamep /*g*/, Levelsp v, Levelp l, Thingp t, int val) -> int
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return 0;
  }
  return t->_value13 += val;
}

[[nodiscard]] auto thing_value13_decr(Gamep /*g*/, Levelsp v, Levelp l, Thingp t, int val) -> int
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return 0;
  }
  if (static_cast< int >(t->_value13) - val <= 0) {
    return t->_value13 = 0;
  }
  return t->_value13 -= val;
}
[[nodiscard]] auto thing_value14(Thingp t) -> int
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return 0;
  }
  return t->_value14;
}

[[nodiscard]] auto thing_value14_set(Gamep /*g*/, Levelsp v, Levelp l, Thingp t, int val) -> int
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return 0;
  }
  return t->_value14 = val;
}

[[nodiscard]] auto thing_value14_incr(Gamep /*g*/, Levelsp v, Levelp l, Thingp t, int val) -> int
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return 0;
  }
  return t->_value14 += val;
}

[[nodiscard]] auto thing_value14_decr(Gamep /*g*/, Levelsp v, Levelp l, Thingp t, int val) -> int
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return 0;
  }
  if (static_cast< int >(t->_value14) - val <= 0) {
    return t->_value14 = 0;
  }
  return t->_value14 -= val;
}
[[nodiscard]] auto thing_value15(Thingp t) -> int
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return 0;
  }
  return t->_value15;
}

[[nodiscard]] auto thing_value15_set(Gamep /*g*/, Levelsp v, Levelp l, Thingp t, int val) -> int
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return 0;
  }
  return t->_value15 = val;
}

[[nodiscard]] auto thing_value15_incr(Gamep /*g*/, Levelsp v, Levelp l, Thingp t, int val) -> int
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return 0;
  }
  return t->_value15 += val;
}

[[nodiscard]] auto thing_value15_decr(Gamep /*g*/, Levelsp v, Levelp l, Thingp t, int val) -> int
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return 0;
  }
  if (static_cast< int >(t->_value15) - val <= 0) {
    return t->_value15 = 0;
  }
  return t->_value15 -= val;
}
[[nodiscard]] auto thing_value16(Thingp t) -> int
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return 0;
  }
  return t->_value16;
}

[[nodiscard]] auto thing_value16_set(Gamep /*g*/, Levelsp v, Levelp l, Thingp t, int val) -> int
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return 0;
  }
  return t->_value16 = val;
}

[[nodiscard]] auto thing_value16_incr(Gamep /*g*/, Levelsp v, Levelp l, Thingp t, int val) -> int
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return 0;
  }
  return t->_value16 += val;
}

[[nodiscard]] auto thing_value16_decr(Gamep /*g*/, Levelsp v, Levelp l, Thingp t, int val) -> int
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return 0;
  }
  if (static_cast< int >(t->_value16) - val <= 0) {
    return t->_value16 = 0;
  }
  return t->_value16 -= val;
}
[[nodiscard]] auto thing_distance_avoid_target(Thingp t) -> int
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return 0;
  }
  return t->_distance_avoid_target;
}

[[nodiscard]] auto thing_distance_avoid_target_set(Gamep /*g*/, Levelsp v, Levelp l, Thingp t, int val) -> int
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return 0;
  }
  return t->_distance_avoid_target = val;
}

[[nodiscard]] auto thing_distance_avoid_target_incr(Gamep /*g*/, Levelsp v, Levelp l, Thingp t, int val) -> int
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return 0;
  }
  return t->_distance_avoid_target += val;
}

[[nodiscard]] auto thing_distance_avoid_target_decr(Gamep /*g*/, Levelsp v, Levelp l, Thingp t, int val) -> int
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return 0;
  }
  if (static_cast< int >(t->_distance_avoid_target) - val <= 0) {
    return t->_distance_avoid_target = 0;
  }
  return t->_distance_avoid_target -= val;
}

[[nodiscard]] auto thing_minion_max(Gamep /*g*/, Levelsp v, Levelp l, Thingp t) -> int
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return 0;
  }
  return t->_minion_max;
}

[[nodiscard]] auto thing_minion_max_set(Gamep /*g*/, Levelsp v, Levelp l, Thingp t, int val) -> int
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return 0;
  }

  if (val > THING_MINION_MAX) {
    thing_croak(t, "trying to set minion max too high");
    val = THING_MINION_MAX;
  }

  return t->_minion_max = val;
}

[[nodiscard]] auto thing_minion_max_incr(Gamep /*g*/, Levelsp v, Levelp l, Thingp t, int val) -> int
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return 0;
  }

  if (t->_minion_max + val >= THING_MINION_MAX) {
    return t->_minion_max = THING_MINION_MAX;
  }

  return t->_minion_max += val;
}

[[nodiscard]] auto thing_minion_max_decr(Gamep /*g*/, Levelsp v, Levelp l, Thingp t, int val) -> int
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return 0;
  }
  if (static_cast< int >(t->_minion_max) - val <= 0) {
    return t->_minion_max = 0;
  }
  return t->_minion_max -= val;
}

[[nodiscard]] auto thing_distance_minion_from_mob_max(Gamep /*g*/, Levelsp v, Levelp l, Thingp t) -> int
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return 0;
  }
  return t->_distance_minion_from_mob_max;
}

[[nodiscard]] auto thing_distance_minion_from_mob_max_set(Gamep /*g*/, Levelsp v, Levelp l, Thingp t, int val) -> int
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return 0;
  }
  return t->_distance_minion_from_mob_max = val;
}

[[nodiscard]] auto thing_variant(Thingp t) -> int
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return 0;
  }
  return t->_variant;
}

[[nodiscard]] auto thing_variant_set(Gamep /*g*/, Levelsp v, Levelp l, Thingp t, int val) -> int
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return 0;
  }
  return t->_variant = val;
}

[[nodiscard]] auto thing_priority(Thingp t) -> ThingPriorityType
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return THING_PRIORITY_LOWEST;
  }
  if (thing_is_dead(t)) {
    return THING_PRIORITY_DEAD;
  }
  return t->_priority;
}

[[nodiscard]] auto thing_priority_set(Gamep /*g*/, Levelsp v, Levelp l, Thingp t, ThingPriorityType val) -> ThingPriorityType
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return THING_PRIORITY_LOWEST;
  }
  return t->_priority = val;
}

[[nodiscard]] auto thing_lifespan(Thingp t) -> int
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return 0;
  }
  return t->_lifespan;
}

[[nodiscard]] auto thing_lifespan_set(Gamep /*g*/, Levelsp v, Levelp l, Thingp t, int val) -> int
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return 0;
  }
  return t->_lifespan = val;
}

[[nodiscard]] auto thing_lifespan_incr(Gamep /*g*/, Levelsp v, Levelp l, Thingp t, int val) -> int
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return 0;
  }
  return t->_lifespan += val;
}

[[nodiscard]] auto thing_lifespan_decr(Gamep /*g*/, Levelsp v, Levelp l, Thingp t, int val) -> int
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return 0;
  }
  if (static_cast< int >(t->_lifespan) - val <= 0) {
    return t->_lifespan = 0;
  }
  return t->_lifespan -= val;
}

[[nodiscard]] auto thing_age(Thingp t) -> int
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return 0;
  }
  return t->_age;
}

[[nodiscard]] auto thing_age_set(Gamep /*g*/, Levelsp v, Levelp l, Thingp t, int val) -> int
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return 0;
  }
  return t->_age = val;
}

[[nodiscard]] auto thing_age_incr(Gamep /*g*/, Levelsp v, Levelp l, Thingp t, int val) -> int
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return 0;
  }
  return t->_age += val;
}

[[nodiscard]] auto thing_age_decr(Gamep /*g*/, Levelsp v, Levelp l, Thingp t, int val) -> int
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return 0;
  }
  if (t->_age - val <= 0) {
    return t->_age = 0;
  }
  return t->_age -= val;
}

[[nodiscard]] auto thing_move_remaining(Thingp t) -> int
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return 0;
  }
  return t->_move_remaining;
}

[[nodiscard]] auto thing_move_remaining_set(Gamep /*g*/, Levelsp v, Levelp l, Thingp t, int val) -> int
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return 0;
  }
  return t->_move_remaining = val;
}

[[nodiscard]] auto thing_move_remaining_incr(Gamep /*g*/, Levelsp v, Levelp l, Thingp t, int val) -> int
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return 0;
  }
  return t->_move_remaining += val;
}

[[nodiscard]] auto thing_move_remaining_decr(Gamep /*g*/, Levelsp v, Levelp l, Thingp t, int val) -> int
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return 0;
  }
  if (t->_move_remaining - val <= 0) {
    return t->_move_remaining = 0;
  }
  return t->_move_remaining -= val;
}

[[nodiscard]] auto thing_collision_radius(Thingp t) -> float
{
  TRACE_DEBUG();

  return thing_is_collision_circle_small(t) ? THING_COLLISION_CIRCLE_SMALL_RADIUS : THING_COLLISION_CIRCLE_LARGE_RADIUS;
}

[[nodiscard]] auto thing_target(Thingp t) -> bpoint
{
  TRACE_DEBUG();

  if (t == nullptr) {
    CROAK("no thing pointer");
  }

  return t->_target;
}

void thing_target_set(Gamep /*g*/, Levelsp v, Levelp l, Thingp t, const bpoint &val)
{
  TRACE_DEBUG();

  if (t == nullptr) {
    CROAK("no thing pointer");
  }

  t->_target = val;
}
