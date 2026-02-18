//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_game.hpp"
#include "my_globals.hpp"
#include "my_main.hpp"
#include "my_thing_callbacks.hpp"
#include "my_thing_inlines.hpp"

spoint thing_at(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    CROAK("No thing pointer set");
  }
  return make_spoint(t->_at);
}

void thing_at_set(Thingp t, const spoint &val)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    CROAK("No thing pointer set");
  }

  t->_old_at = t->_at;
  t->_at     = make_fpoint(val);
}

fpoint thing_real_at(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    CROAK("No thing pointer set");
  }
  return t->_at;
}

void thing_at_set(Thingp t, const fpoint &val)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    CROAK("No thing pointer set");
  }

  t->_old_at = t->_at;
  t->_at     = val;
}

spoint thing_old_at(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    CROAK("No thing pointer set");
  }
  return make_spoint(t->_old_at);
}

spoint thing_prev_pix_at(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    CROAK("No thing pointer set");
  }
  return t->_prev_pix_at;
}

void thing_prev_pix_at_set(Gamep g, Levelsp v, Levelp l, Thingp t, const spoint &val)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    CROAK("No thing pointer set");
  }
  t->_prev_pix_at = val;
}

void thing_pix_at_set(Gamep g, Levelsp v, Levelp l, Thingp t, const spoint &val)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    CROAK("No thing pointer set");
  }

  if (t->_curr_pix_at != val) {
    l->request_to_update_visibility = true;
  }

  t->_prev_pix_at = t->_curr_pix_at;
  t->_curr_pix_at = val;
}

void thing_pix_at_set(Gamep g, Levelsp v, Levelp l, Thingp t, short x, short y)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    CROAK("No thing pointer set");
  }

  spoint val(x, y);

  if (t->_curr_pix_at != val) {
    l->request_to_update_visibility = true;
  }

  t->_prev_pix_at = t->_curr_pix_at;
  t->_curr_pix_at = val;
}

spoint thing_moving_from(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    CROAK("No thing pointer set");
  }
  return t->_moving_from;
}

void thing_moving_from_set(Thingp t, const spoint &val)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    CROAK("No thing pointer set");
  }
  t->_moving_from = val;
}

int thing_speed(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_speed;
}

int thing_speed_set(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_speed = val;
}

int thing_weight(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_weight;
}

int thing_weight_set(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_weight = val;
}

int thing_health(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_health;
}

int thing_health_set(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return 0;
  }
  game_request_to_remake_ui_set(g);
  return t->_health = val;
}

int thing_health_incr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return 0;
  }
  game_request_to_remake_ui_set(g);
  return t->_health += val;
}

int thing_health_decr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return 0;
  }
  game_request_to_remake_ui_set(g);

  if ((int) t->_health - val <= 0) {
    return t->_health = 0;
  }

  return t->_health -= val;
}

void thing_is_falling_set(Gamep g, Levelsp v, Levelp l, Thingp t, bool val)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return;
  }

  //
  // Once falling, it is treated as a counter
  //
  if (val) {
    //
    // Start falling if not doing do
    //
    if (static_cast< bool >(t->_is_falling_ms)) {
      return;
    }
  } else {
    //
    // Stop falling
    //
    if (! static_cast< bool >(t->_is_falling_ms)) {
      return;
    }
  }
  t->_is_falling_ms = static_cast< uint16_t >(val);

  if (val) {
    thing_on_fall_begin(g, v, l, t);
  } else {
    thing_on_fall_end(g, v, l, t);
  }
}

int thing_is_falling_incr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return 0;
  }

  if (t->_is_falling_ms + val > MAX_FALL_TIME_MS) {
    return t->_is_falling_ms = MAX_FALL_TIME_MS;
  }

  return t->_is_falling_ms += val;
}

bool thing_is_falling_continues(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }

  return t->_is_falling_continues;
}

void thing_is_falling_continues_set(Gamep g, Levelsp v, Levelp l, Thingp t, bool val)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return;
  }

  if (t->_is_falling_continues == static_cast< int >(val)) {
    return;
  }
  t->_is_falling_continues = val;

  if (val) {
    THING_DBG(t, "is scheduled for cleanup");
  }

  level_request_to_cleanup_things_set(g, v, l);
}

void thing_is_falling_continues_unset(Gamep g, Levelsp v, Levelp l, Thingp t)
{
  TRACE_NO_INDENT();
  thing_is_falling_continues_set(g, v, l, t, false);
}

void thing_is_hit_set(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return;
  }

  //
  // Once hit, it is treated as a counter
  //
  if (val != 0) {
    //
    // Start the hit counter if not doing do
    //
    if (static_cast< bool >(t->_is_hit)) {
      return;
    }
  } else {
    //
    // Stop hit
    //
    if (! static_cast< bool >(t->_is_hit)) {
      return;
    }
  }

  t->_is_hit = val;

  if (val != 0) {
    thing_on_hit_begin(g, v, l, t);
  } else {
    thing_on_hit_end(g, v, l, t);
  }
}

int thing_is_hit_incr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return 0;
  }

  if ((! static_cast< bool >(t->_is_hit)) && (val != 0)) {
    thing_on_hit_begin(g, v, l, t);
  }

  if (t->_is_hit + val > 255) {
    return t->_is_hit = 255;
  }

  return t->_is_hit += val;
}

int thing_is_hit_decr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return 0;
  }

  if ((int) t->_is_hit - val <= 0) {
    if (static_cast< bool >(t->_is_hit)) {
      thing_on_hit_end(g, v, l, t);
    }
    return t->_is_hit = 0;
  }

  return t->_is_hit -= val;
}

void thing_is_hot_set(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return;
  }

  //
  // Once hot, it is treated as a counter
  //
  if (val != 0) {
    //
    // Start the hot counter if not doing do
    //
    if (static_cast< bool >(t->_is_hot)) {
      return;
    }
  } else {
    //
    // Stop hot
    //
    if (! static_cast< bool >(t->_is_hot)) {
      return;
    }
  }

  t->_is_hot = val;
}

int thing_is_hot_incr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return 0;
  }

  if (t->_is_hot + val > 255) {
    return t->_is_hot = 255;
  }

  return t->_is_hot += val;
}

int thing_is_hot_decr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return 0;
  }

  if ((int) t->_is_hot - val <= 0) {
    return t->_is_hot = 0;
  }

  return t->_is_hot -= val;
}

int thing_temperature(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_temperature;
}

int thing_temperature_set(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
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
  { // newline
    THING_DBG(t, "temperature set to %u degrees", val);
  }

  return t->_temperature = val;
}

int thing_temperature_incr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return 0;
  }
  return thing_temperature_set(g, v, l, t, t->_temperature + val);
}

int thing_temperature_decr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return 0;
  }
  return thing_temperature_set(g, v, l, t, t->_temperature - val);
}

int thing_damage_this_tick(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_damage_this_tick;
}

int thing_damage_this_tick_set(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_damage_this_tick = val;
}

int thing_damage_this_tick_incr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_damage_this_tick += val;
}

int thing_damage_this_tick_decr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_damage_this_tick -= val;
}

int thing_keys_carried(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_keys_carried;
}

int thing_keys_carried_set(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_keys_carried = val;
}

int thing_keys_carried_incr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_keys_carried += val;
}

int thing_keys_carried_decr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return 0;
  }

  if ((int) t->_keys_carried - val <= 0) {
    return t->_keys_carried = 0;
  }

  return t->_keys_carried -= val;
}

void thing_is_dead_set(Gamep g, Levelsp v, Levelp l, Thingp t, bool val)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return;
  }

  if (t->_is_dead == static_cast< int >(val)) {
    return;
  }
  t->_is_dead = val;

  if (val) {
    THING_DBG(t, "is dead");
  }

  thing_is_dead_handle(g, v, l, t);
}

void thing_is_dead_unset(Gamep g, Levelsp v, Levelp l, Thingp t)
{
  TRACE_NO_INDENT();
  thing_is_dead_set(g, v, l, t, false);
}

bool thing_is_burning(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return t->_is_burning;
}

void thing_is_burning_set(Gamep g, Levelsp v, Levelp l, Thingp t, bool val)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return;
  }

  if (t->_is_burning == static_cast< int >(val)) {
    return;
  }
  t->_is_burning = val;

  if (val) {
    THING_DBG(t, "is burning, %u degrees", thing_temperature(t));
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
  TRACE_NO_INDENT();
  thing_is_burning_set(g, v, l, t, false);
}

bool thing_is_corpse(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return t->_is_corpse;
}

void thing_is_corpse_set(Gamep g, Levelsp v, Levelp l, Thingp t, bool val)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return;
  }

  if (t->_is_corpse == static_cast< int >(val)) {
    return;
  }
  t->_is_corpse = val;

  if (val) {
    THING_DBG(t, "is corpse");
  }
}

void thing_is_corpse_unset(Gamep g, Levelsp v, Levelp l, Thingp t)
{
  TRACE_NO_INDENT();
  thing_is_corpse_set(g, v, l, t, false);
}

bool thing_is_scheduled_for_cleanup(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }

  return t->_is_scheduled_for_cleanup;
}

void thing_is_scheduled_for_cleanup_set(Gamep g, Levelsp v, Levelp l, Thingp t, bool val)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return;
  }

  if (t->_is_scheduled_for_cleanup == static_cast< int >(val)) {
    return;
  }
  t->_is_scheduled_for_cleanup = val;

  if (val) {
    THING_DBG(t, "is scheduled for cleanup");
  }

  level_request_to_cleanup_things_set(g, v, l);
}

void thing_is_scheduled_for_cleanup_unset(Gamep g, Levelsp v, Levelp l, Thingp t)
{
  TRACE_NO_INDENT();
  thing_is_scheduled_for_cleanup_set(g, v, l, t, false);
}

bool thing_is_sleeping(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return t->_is_sleeping;
}

void thing_is_sleeping_set(Gamep g, Levelsp v, Levelp l, Thingp t, bool val)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return;
  }
  t->_is_sleeping = val;
}

void thing_is_sleeping_unset(Gamep g, Levelsp v, Levelp l, Thingp t)
{
  TRACE_NO_INDENT();
  thing_is_sleeping_set(g, v, l, t, false);
}

bool thing_is_unlocked(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return t->_is_unlocked;
}

void thing_is_unlocked_set(Gamep g, Levelsp v, Levelp l, Thingp t, bool val)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return;
  }
  t->_is_unlocked = val;
}

void thing_is_unlocked_unset(Gamep g, Levelsp v, Levelp l, Thingp t)
{
  TRACE_NO_INDENT();
  thing_is_unlocked_set(g, v, l, t, false);
}

bool thing_is_on_map(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return t->_is_on_map;
}

void thing_is_on_map_set(Gamep g, Levelsp v, Levelp l, Thingp t, bool val)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return;
  }
  t->_is_on_map = val;
}

void thing_is_on_map_unset(Gamep g, Levelsp v, Levelp l, Thingp t)
{
  TRACE_NO_INDENT();
  thing_is_on_map_set(g, v, l, t, false);
}

void thing_is_moving_set(Gamep g, Levelsp v, Levelp l, Thingp t, bool val)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return;
  }

  if (t->_is_moving == static_cast< int >(val)) {
    return;
  }
  t->_is_moving = val;

  if (val) {
    thing_on_moved(g, v, l, t);
  }
}

void thing_is_moving_unset(Gamep g, Levelsp v, Levelp l, Thingp t)
{
  TRACE_NO_INDENT();
  thing_is_moving_set(g, v, l, t, false);
}

void thing_is_spawned_set(Gamep g, Levelsp v, Levelp l, Thingp t, bool val)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return;
  }

  if (t->_is_spawned == static_cast< int >(val)) {
    return;
  }
  t->_is_spawned = val;

  if (val) {
    //
    // Callback upon spawning
    //
    thing_on_spawned(g, v, l, t);
  }
}

void thing_is_spawned_unset(Gamep g, Levelsp v, Levelp l, Thingp t)
{
  TRACE_NO_INDENT();
  thing_is_spawned_set(g, v, l, t, false);
}

bool thing_is_teleporting(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return t->_is_teleporting;
}

void thing_is_teleporting_set(Gamep g, Levelsp v, Levelp l, Thingp t, bool val)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return;
  }

  if (t->_is_teleporting == static_cast< int >(val)) {
    return;
  }
  t->_is_teleporting = val;

  if (val) {
    thing_on_teleported(g, v, l, t);
  }
}

void thing_is_teleporting_unset(Gamep g, Levelsp v, Levelp l, Thingp t)
{
  TRACE_NO_INDENT();
  thing_is_teleporting_set(g, v, l, t, false);
}

void thing_is_jumping_set(Gamep g, Levelsp v, Levelp l, Thingp t, bool val)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return;
  }

  if (t->_is_jumping == static_cast< int >(val)) {
    return;
  }
  t->_is_jumping = val;

  if (val) {
    thing_on_jump_begin(g, v, l, t);
  } else {
    thing_on_jump_end(g, v, l, t);
  }
}

void thing_is_jumping_unset(Gamep g, Levelsp v, Levelp l, Thingp t)
{
  TRACE_NO_INDENT();
  thing_is_jumping_set(g, v, l, t, false);
}

//
// Returns true/false on success/fail
//
bool thing_is_open_try_set(Gamep g, Levelsp v, Levelp l, Thingp t, Thingp opener, bool val)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }

  if (t->_is_open == static_cast< int >(val)) {
    return true;
  }
  t->_is_open = val;

  //
  // Attempt the open/close. It can fail.
  //
  if (val) {
    //
    // Try to open
    //
    if (! thing_on_open_request(g, v, l, t, opener)) {
      //
      // Open failed
      //
      t->_is_open = false;
      return false;
    }

    //
    // Reset animation
    //
    thing_anim_init(g, v, l, t, THING_ANIM_OPEN);
  } else {
    //
    // Try to close
    //
    if (! thing_on_close_request(g, v, l, t, opener)) {
      //
      // Close failed
      //
      t->_is_open = true;
      return false;
    }

    //
    // Reset animation
    //
    thing_anim_init(g, v, l, t, THING_ANIM_IDLE);
  }

  return true;
}

bool thing_is_open_try_unset(Gamep g, Levelsp v, Levelp l, Thingp t, Thingp closer)
{
  TRACE_NO_INDENT();
  return thing_is_open_try_set(g, v, l, t, closer, false);
}

bool thing_is_carried(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return t->_is_carried;
}

//
// Returns true/false on success/fail
//
bool thing_is_carried_try_set(Gamep g, Levelsp v, Levelp l, Thingp item, Thingp player_or_monst, bool val)
{
  TRACE_NO_INDENT();

  if (! thing_is_player(player_or_monst) && ! thing_is_monst(player_or_monst)) {
    THING_ERR(player_or_monst, "unexpected thing for %s", __FUNCTION__);
    return false;
  }

  if (item == nullptr) {
    ERR("No thing pointer set");
    return false;
  }

  if (item->_is_carried == static_cast< int >(val)) {
    auto s = to_string(g, v, l, item);
    THING_LOG(player_or_monst, "carry-try: %s (failed, already carried)", s.c_str());
    return true;
  }
  auto old_value    = item->_is_carried;
  item->_is_carried = val;

  //
  // Attempt the collect/drop. It can fail.
  //
  if (val) {
    //
    // Try to collect
    //
    if (! thing_on_carry_request(g, v, l, item, player_or_monst)) {
      //
      // Collect failed
      //
      item->_is_carried = old_value;

      auto s = to_string(g, v, l, item);
      THING_LOG(player_or_monst, "carry-try: %s (failed, carry request)", s.c_str());
      return false;
    }

    //
    // Add to the inventory.
    //
    if (! thing_inventory_add(g, v, l, item, player_or_monst)) {
      //
      // Possibly out of slots
      //
      item->_is_carried = old_value;

      auto s = to_string(g, v, l, item);
      THING_LOG(player_or_monst, "carry-try: %s (failed, inventory add)", s.c_str());
      return false;
    }

  } else {
    //
    // Try to drop
    //
    if (! thing_on_drop_request(g, v, l, item, player_or_monst)) {
      //
      // Drop failed
      //
      item->_is_carried = old_value;

      auto s = to_string(g, v, l, item);
      THING_LOG(player_or_monst, "drop-try: %s (failed, drop request)", s.c_str());
      return false;
    }

    //
    // Remove from the inventory.
    //
    if (! thing_inventory_remove(g, v, l, item, player_or_monst)) {
      item->_is_carried = old_value;

      auto s = to_string(g, v, l, item);
      THING_LOG(player_or_monst, "drop-try: %s (failed, inventory remove)", s.c_str());
      return false;
    }
  }

  //
  // Reset animation
  //
  thing_anim_init(g, v, l, item, THING_ANIM_IDLE);

  return true;
}

bool thing_is_carried_try_unset(Gamep g, Levelsp v, Levelp l, Thingp item, Thingp player_or_monst)
{
  TRACE_NO_INDENT();
  return thing_is_carried_try_set(g, v, l, item, player_or_monst, false);
}

bool thing_is_animated_can_hflip(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_animated_can_hflip) != 0;
}

bool thing_is_animated_no_dir(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_animated_no_dir) != 0;
}

bool thing_is_animated_sync_first(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_animated_sync_first) != 0;
}

bool thing_is_animated(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_animated) != 0;
}

bool thing_is_barrel(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_barrel) != 0;
}

bool thing_is_blit_centered(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_blit_centered) != 0;
}

bool thing_is_blit_flush_per_line(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_blit_flush_per_line) != 0;
}

bool thing_is_blit_outlined(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_blit_outlined) != 0;
}

bool thing_is_blit_square_outlined(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_blit_square_outlined) != 0;
}

bool thing_is_brazier(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_brazier) != 0;
}

bool thing_is_bridge(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_bridge) != 0;
}

bool thing_is_chasm(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_chasm) != 0;
}

bool thing_is_corridor(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_corridor) != 0;
}

bool thing_is_collision_square(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_collision_square) != 0;
}

bool thing_is_obs_to_cursor_path(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
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

bool thing_is_cursor_path_hazard(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_cursor_path_hazard) != 0;
}

bool thing_is_cursor_path(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_cursor_path) != 0;
}

bool thing_is_cursor(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_cursor) != 0;
}

bool thing_is_deep_water(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_deep_water) != 0;
}

bool thing_is_described_cursor(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_described_cursor) != 0;
}

bool thing_is_dirt(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_dirt) != 0;
}

bool thing_is_door_unlocked(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_door_unlocked) != 0;
}

bool thing_is_dungeon_entrance(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_dungeon_entrance) != 0;
}

bool thing_is_entrance(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_entrance) != 0;
}

bool thing_is_exit(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_exit) != 0;
}

bool thing_is_floor(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_floor) != 0;
}

bool thing_is_foliage(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_foliage) != 0;
}

bool thing_is_ghost(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_ghost) != 0;
}

bool thing_is_kobalos(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_kobalos) != 0;
}

bool thing_is_grass(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_grass) != 0;
}

bool thing_is_key(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_key) != 0;
}

bool thing_is_lava(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_lava) != 0;
}

bool thing_is_level_across_icon(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_level_across_icon) != 0;
}

bool thing_is_level_curr(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_level_curr) != 0;
}

bool thing_is_level_down_icon(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_level_down_icon) != 0;
}

bool thing_is_level_final_icon(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_level_final_icon) != 0;
}

bool thing_is_level_next_icon(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_level_next_icon) != 0;
}

bool thing_is_level_not_visited_icon(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_level_not_visited_icon) != 0;
}

bool thing_is_level_visited_icon(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_level_visited_icon) != 0;
}

bool thing_is_minion(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_minion) != 0;
}

bool thing_is_mob(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_mob) != 0;
}

bool thing_is_mob1(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_mob1) != 0;
}

bool thing_is_mob2(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_mob2) != 0;
}

bool thing_is_monst(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_monst) != 0;
}

bool thing_is_monst_group_easy(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_monst_group_easy) != 0;
}

bool thing_is_monst_group_hard(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_monst_group_hard) != 0;
}

bool thing_is_obs_to_movement(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
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

bool thing_is_pillar(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_pillar) != 0;
}

bool thing_is_rock(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_rock) != 0;
}

bool thing_is_door_secret(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_door_secret) != 0;
}

bool thing_is_slime(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_slime) != 0;
}

bool thing_is_teleport(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_teleport) != 0;
}

bool thing_is_tickable(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_tickable) != 0;
}

bool thing_is_tiled(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_tiled) != 0;
}

bool thing_is_trap(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_trap) != 0;
}

bool thing_is_treasure(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_treasure) != 0;
}

bool thing_is_unused1(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_unused1) != 0;
}

bool thing_is_unused2(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_unused2) != 0;
}

bool thing_is_unused3(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_unused3) != 0;
}

bool thing_is_unused4(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_unused4) != 0;
}

bool thing_is_unused5(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_unused5) != 0;
}

bool thing_is_unused6(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_unused6) != 0;
}

bool thing_is_unused7(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_unused7) != 0;
}

bool thing_is_unused8(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_unused8) != 0;
}

bool thing_is_unused9(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_unused9) != 0;
}

bool thing_is_unused10(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_unused10) != 0;
}

bool thing_is_unused11(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_unused11) != 0;
}

bool thing_is_unused12(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_unused12) != 0;
}

bool thing_is_unused13(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_unused13) != 0;
}

bool thing_is_unused14(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_unused14) != 0;
}

bool thing_is_unused15(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_unused15) != 0;
}

bool thing_is_unused16(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_unused16) != 0;
}

bool thing_is_unused17(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_unused17) != 0;
}

bool thing_is_unused18(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_unused18) != 0;
}

bool thing_is_unused19(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_unused19) != 0;
}

bool thing_is_unused20(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_unused20) != 0;
}

bool thing_is_unused21(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_unused21) != 0;
}

bool thing_is_unused22(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_unused22) != 0;
}

bool thing_is_unused23(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_unused23) != 0;
}

bool thing_is_unused24(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_unused24) != 0;
}

bool thing_is_unused25(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_unused25) != 0;
}

bool thing_is_unused26(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_unused26) != 0;
}

bool thing_is_unused27(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_unused27) != 0;
}

bool thing_is_unused28(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_unused28) != 0;
}

bool thing_is_unused29(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_unused29) != 0;
}

bool thing_is_unused30(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_unused30) != 0;
}

bool thing_is_unused31(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_unused31) != 0;
}

bool thing_is_unused32(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_unused32) != 0;
}

bool thing_is_unused33(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_unused33) != 0;
}

bool thing_is_unused34(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_unused34) != 0;
}

bool thing_is_unused35(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_unused35) != 0;
}

bool thing_is_unused36(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_unused36) != 0;
}

bool thing_is_unused37(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_unused37) != 0;
}

bool thing_is_unused38(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_unused38) != 0;
}

bool thing_is_unused39(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_unused39) != 0;
}

bool thing_is_unused40(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_unused40) != 0;
}

bool thing_is_unused41(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_unused41) != 0;
}

bool thing_is_unused42(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_unused42) != 0;
}

bool thing_is_unused43(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_unused43) != 0;
}

bool thing_is_unused44(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_unused44) != 0;
}

bool thing_is_unused45(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_unused45) != 0;
}

bool thing_is_unused46(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_unused46) != 0;
}

bool thing_is_unused47(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_unused47) != 0;
}

bool thing_is_unused48(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_unused48) != 0;
}

bool thing_is_unused49(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_unused49) != 0;
}

bool thing_is_unused50(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_unused50) != 0;
}

bool thing_is_unused51(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_unused51) != 0;
}

bool thing_is_unused52(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_unused52) != 0;
}

bool thing_is_unused53(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_unused53) != 0;
}

bool thing_is_unused54(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_unused54) != 0;
}

bool thing_is_unused55(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_unused55) != 0;
}

bool thing_is_unused56(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_unused56) != 0;
}

bool thing_is_unused57(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_unused57) != 0;
}

bool thing_is_unused58(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_unused58) != 0;
}

bool thing_is_unused59(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_unused59) != 0;
}

bool thing_is_unused60(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_unused60) != 0;
}

bool thing_is_unused61(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_unused61) != 0;
}

bool thing_is_unused62(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_unused62) != 0;
}

bool thing_is_unused63(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_unused63) != 0;
}

bool thing_is_unused64(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_unused64) != 0;
}

bool thing_is_unused65(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_unused65) != 0;
}

bool thing_is_unused66(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_unused66) != 0;
}

bool thing_is_unused67(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_unused67) != 0;
}

bool thing_is_unused68(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_unused68) != 0;
}

bool thing_is_removable_when_dead_on_err(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_removable_when_dead_on_err) != 0;
}

bool thing_is_removable_on_err(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_removable_on_err) != 0;
}

bool thing_is_obs_when_dead(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_obs_when_dead) != 0;
}

bool thing_is_able_to_fall_repeatedly(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_able_to_fall_repeatedly) != 0;
}

bool thing_is_able_to_move_through_walls(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_able_to_move_through_walls) != 0;
}

bool thing_is_able_to_move_diagonally(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_able_to_move_diagonally) != 0;
}

bool thing_is_blit_on_ground(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_blit_on_ground) != 0;
}

bool thing_is_insectoid(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_insectoid) != 0;
}

bool thing_is_mantisman(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_mantisman) != 0;
}

bool thing_is_dmap(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_dmap) != 0;
}

bool thing_is_obs_to_spawning(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_obs_to_spawning) != 0;
}

bool thing_is_mob_kill_minions_on_death(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_mob_kill_minions_on_death) != 0;
}

bool thing_is_border(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_border) != 0;
}

bool thing_is_collision_detection_enabled(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_collision_detection_enabled) != 0;
}

bool thing_is_gold(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_gold) != 0;
}

bool thing_is_glass(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_glass) != 0;
}

bool thing_is_plant(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_plant) != 0;
}

bool thing_is_wood(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_wood) != 0;
}

bool thing_is_metal(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_metal) != 0;
}

bool thing_is_flesh(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_flesh) != 0;
}

bool thing_is_stone(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_stone) != 0;
}

bool thing_is_meltable(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_meltable) != 0;
}

bool thing_is_blit_per_pixel_lighting(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_blit_per_pixel_lighting) != 0;
}

bool thing_is_dead_on_collision(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_dead_on_collision) != 0;
}

bool thing_is_obs_to_jumping_out_of(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_obs_to_jumping_out_of) != 0;
}

bool thing_is_cursor_path_warning(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_cursor_path_warning) != 0;
}

bool thing_is_collision_circle_large(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_collision_circle_large) != 0;
}

bool thing_is_collision_circle_small(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_collision_circle_small) != 0;
}

bool thing_is_fireball(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_fireball) != 0;
}

bool thing_is_projectile(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_projectile) != 0;
}

bool thing_is_health_bar_shown(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_health_bar_shown) != 0;
}

bool thing_is_item_mergeable(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_item_mergeable) != 0;
}

bool thing_is_door_locked(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_door_locked) != 0;
}

bool thing_is_inventory_item(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_inventory_item) != 0;
}

bool thing_is_able_to_open(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_able_to_open) != 0;
}

bool thing_is_item(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_item) != 0;
}

bool thing_is_able_to_crush_grass(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_able_to_crush_grass) != 0;
}

bool thing_is_able_to_collect_keys(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_able_to_collect_keys) != 0;
}

bool thing_is_able_to_collect_items(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_able_to_collect_items) != 0;
}

bool thing_is_collectable(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_collectable) != 0;
}

bool thing_is_blit_when_obscured(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_blit_when_obscured) != 0;
}

bool thing_is_openable(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_openable) != 0;
}

bool thing_is_tick_end_delay(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_tick_end_delay) != 0;
}

bool thing_is_damage_capped(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_damage_capped) != 0;
}

bool thing_is_physics_explosion(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_physics_explosion) != 0;
}

bool thing_is_explosion(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_explosion) != 0;
}

bool thing_is_obs_to_explosion(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
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

bool thing_is_obs_to_jump_over(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
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

bool thing_is_teleport_blocked(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_teleport_blocked) != 0;
}

bool thing_is_cursor_path_none(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_cursor_path_none) != 0;
}

bool thing_is_able_to_jump(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_able_to_jump) != 0;
}

bool thing_is_blit_obscures(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_blit_obscures) != 0;
}

bool thing_is_flying(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_flying) != 0;
}

bool thing_is_needs_move_confirm(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_needs_move_confirm) != 0;
}

bool thing_is_obs_to_falling_onto(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
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

bool thing_is_obs_to_jumping_onto(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
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

bool thing_is_obs_to_teleporting_onto(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
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

bool thing_is_submergible(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_submergible) != 0;
}

bool thing_is_able_to_fall(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_able_to_fall) != 0;
}

bool thing_is_physics_water(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_physics_water) != 0;
}

bool thing_is_indestructible(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_indestructible) != 0;
}

bool thing_is_floating(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_floating) != 0;
}

bool thing_is_obs_to_fire(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
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

bool thing_is_combustible(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_combustible) != 0;
}

bool thing_is_blit_shown_in_chasms(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_blit_shown_in_chasms) != 0;
}

bool thing_is_gaseous(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_gaseous) != 0;
}

bool thing_is_extinguished_on_death(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_extinguished_on_death) != 0;
}

bool thing_is_broken_on_death(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_broken_on_death) != 0;
}

bool thing_is_undead(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_undead) != 0;
}

bool thing_is_wait_on_dead_anim(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_wait_on_dead_anim) != 0;
}

bool thing_is_corpse_on_death(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_corpse_on_death) != 0;
}

bool thing_is_monst_group_mob(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_monst_group_mob) != 0;
}

bool thing_is_blit_if_has_seen(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_blit_if_has_seen) != 0;
}

bool thing_is_smoke(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_smoke) != 0;
}

bool thing_is_steam(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_steam) != 0;
}

bool thing_is_fire(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_fire) != 0;
}

bool thing_is_burnable(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_burnable) != 0;
}

bool thing_is_dead_on_shoving(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_dead_on_shoving) != 0;
}

bool thing_is_able_to_shove(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_able_to_shove) != 0;
}

bool thing_is_shovable(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_shovable) != 0;
}

bool thing_is_loggable(Thingp t)
{
  TRACE_NO_INDENT();

  if (t == nullptr) {
    ERR("No thing pointer set");
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

bool thing_is_crushable(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_crushable) != 0;
}

bool thing_is_ethereal(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_ethereal) != 0;
}

bool thing_is_blit_shown_in_overlay(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_blit_shown_in_overlay) != 0;
}

bool thing_is_levitating(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_levitating) != 0;
}

bool thing_is_item_equipable(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_item_equipable) != 0;
}

bool thing_is_item_droppable(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_item_droppable) != 0;
}

bool thing_is_able_to_walk_through_walls(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_able_to_walk_through_walls) != 0;
}

bool thing_is_wall(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_wall) != 0;
}

bool thing_is_water(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_water) != 0;
}

int thing_value1(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_value1;
}

int thing_value1_set(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_value1 = val;
}

int thing_value1_incr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_value1 += val;
}

int thing_value1_decr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return 0;
  }
  if ((int) t->_value1 - val <= 0) {
    return t->_value1 = 0;
  }
  return t->_value1 -= val;
}
int thing_value2(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_value2;
}

int thing_value2_set(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_value2 = val;
}

int thing_value2_incr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_value2 += val;
}

int thing_value2_decr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return 0;
  }
  if ((int) t->_value2 - val <= 0) {
    return t->_value2 = 0;
  }
  return t->_value2 -= val;
}
int thing_value3(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_value3;
}

int thing_value3_set(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_value3 = val;
}

int thing_value3_incr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_value3 += val;
}

int thing_value3_decr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return 0;
  }
  if ((int) t->_value3 - val <= 0) {
    return t->_value3 = 0;
  }
  return t->_value3 -= val;
}
int thing_value4(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_value4;
}

int thing_value4_set(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_value4 = val;
}

int thing_value4_incr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_value4 += val;
}

int thing_value4_decr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return 0;
  }
  if ((int) t->_value4 - val <= 0) {
    return t->_value4 = 0;
  }
  return t->_value4 -= val;
}
int thing_value5(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_value5;
}

int thing_value5_set(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_value5 = val;
}

int thing_value5_incr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_value5 += val;
}

int thing_value5_decr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return 0;
  }
  if ((int) t->_value5 - val <= 0) {
    return t->_value5 = 0;
  }
  return t->_value5 -= val;
}
int thing_value6(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_value6;
}

int thing_value6_set(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_value6 = val;
}

int thing_value6_incr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_value6 += val;
}

int thing_value6_decr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return 0;
  }
  if ((int) t->_value6 - val <= 0) {
    return t->_value6 = 0;
  }
  return t->_value6 -= val;
}
int thing_value7(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_value7;
}

int thing_value7_set(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_value7 = val;
}

int thing_value7_incr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_value7 += val;
}

int thing_value7_decr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return 0;
  }
  if ((int) t->_value7 - val <= 0) {
    return t->_value7 = 0;
  }
  return t->_value7 -= val;
}
int thing_value8(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_value8;
}

int thing_value8_set(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_value8 = val;
}

int thing_value8_incr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_value8 += val;
}

int thing_value8_decr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return 0;
  }
  if ((int) t->_value8 - val <= 0) {
    return t->_value8 = 0;
  }
  return t->_value8 -= val;
}
int thing_value9(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_value9;
}

int thing_value9_set(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_value9 = val;
}

int thing_value9_incr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_value9 += val;
}

int thing_value9_decr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return 0;
  }
  if ((int) t->_value9 - val <= 0) {
    return t->_value9 = 0;
  }
  return t->_value9 -= val;
}
int thing_value10(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_value10;
}

int thing_value10_set(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_value10 = val;
}

int thing_value10_incr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_value10 += val;
}

int thing_value10_decr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return 0;
  }
  if ((int) t->_value10 - val <= 0) {
    return t->_value10 = 0;
  }
  return t->_value10 -= val;
}
int thing_value11(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_value11;
}

int thing_value11_set(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_value11 = val;
}

int thing_value11_incr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_value11 += val;
}

int thing_value11_decr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return 0;
  }
  if ((int) t->_value11 - val <= 0) {
    return t->_value11 = 0;
  }
  return t->_value11 -= val;
}
int thing_value12(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_value12;
}

int thing_value12_set(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_value12 = val;
}

int thing_value12_incr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_value12 += val;
}

int thing_value12_decr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return 0;
  }
  if ((int) t->_value12 - val <= 0) {
    return t->_value12 = 0;
  }
  return t->_value12 -= val;
}
int thing_value13(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_value13;
}

int thing_value13_set(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_value13 = val;
}

int thing_value13_incr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_value13 += val;
}

int thing_value13_decr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return 0;
  }
  if ((int) t->_value13 - val <= 0) {
    return t->_value13 = 0;
  }
  return t->_value13 -= val;
}
int thing_value14(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_value14;
}

int thing_value14_set(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_value14 = val;
}

int thing_value14_incr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_value14 += val;
}

int thing_value14_decr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return 0;
  }
  if ((int) t->_value14 - val <= 0) {
    return t->_value14 = 0;
  }
  return t->_value14 -= val;
}
int thing_value15(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_value15;
}

int thing_value15_set(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_value15 = val;
}

int thing_value15_incr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_value15 += val;
}

int thing_value15_decr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return 0;
  }
  if ((int) t->_value15 - val <= 0) {
    return t->_value15 = 0;
  }
  return t->_value15 -= val;
}
int thing_value16(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_value16;
}

int thing_value16_set(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_value16 = val;
}

int thing_value16_incr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_value16 += val;
}

int thing_value16_decr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return 0;
  }
  if ((int) t->_value16 - val <= 0) {
    return t->_value16 = 0;
  }
  return t->_value16 -= val;
}
int thing_value17(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_value17;
}

int thing_value17_set(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_value17 = val;
}

int thing_value17_incr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_value17 += val;
}

int thing_value17_decr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return 0;
  }
  if ((int) t->_value17 - val <= 0) {
    return t->_value17 = 0;
  }
  return t->_value17 -= val;
}
int thing_value18(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_value18;
}

int thing_value18_set(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_value18 = val;
}

int thing_value18_incr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_value18 += val;
}

int thing_value18_decr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return 0;
  }
  if ((int) t->_value18 - val <= 0) {
    return t->_value18 = 0;
  }
  return t->_value18 -= val;
}
int thing_value19(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_value19;
}

int thing_value19_set(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_value19 = val;
}

int thing_value19_incr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_value19 += val;
}

int thing_value19_decr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return 0;
  }
  if ((int) t->_value19 - val <= 0) {
    return t->_value19 = 0;
  }
  return t->_value19 -= val;
}
int thing_value20(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_value20;
}

int thing_value20_set(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_value20 = val;
}

int thing_value20_incr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_value20 += val;
}

int thing_value20_decr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return 0;
  }
  if ((int) t->_value20 - val <= 0) {
    return t->_value20 = 0;
  }
  return t->_value20 -= val;
}
int thing_minion_max(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_minion_max;
}

int thing_minion_max_set(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_minion_max = val;
}

int thing_minion_max_incr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_minion_max += val;
}

int thing_minion_max_decr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return 0;
  }
  if ((int) t->_minion_max - val <= 0) {
    return t->_minion_max = 0;
  }
  return t->_minion_max -= val;
}
int thing_distance_minion_from_mob_max(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_distance_minion_from_mob_max;
}

int thing_distance_minion_from_mob_max_set(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_distance_minion_from_mob_max = val;
}

int thing_distance_minion_from_mob_max_incr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_distance_minion_from_mob_max += val;
}

int thing_distance_minion_from_mob_max_decr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return 0;
  }
  if ((int) t->_distance_minion_from_mob_max - val <= 0) {
    return t->_distance_minion_from_mob_max = 0;
  }
  return t->_distance_minion_from_mob_max -= val;
}

int thing_distance_vision(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_distance_vision;
}

int thing_distance_vision_set(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_distance_vision = val;
}

int thing_distance_vision_incr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_distance_vision += val;
}

int thing_distance_vision_decr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return 0;
  }
  if ((int) t->_distance_vision - val <= 0) {
    return t->_distance_vision = 0;
  }
  return t->_distance_vision -= val;
}

int thing_variant(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_variant;
}

int thing_variant_set(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_variant = val;
}

ThingPriorityType thing_priority(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return THING_PRIORITY_LOW;
  }
  return t->_priority;
}

ThingPriorityType thing_priority_set(Gamep g, Levelsp v, Levelp l, Thingp t, ThingPriorityType val)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return THING_PRIORITY_LOW;
  }
  return t->_priority = val;
}

int thing_distance_jump(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_distance_jump;
}

int thing_distance_jump_set(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_distance_jump = val;
}

int thing_distance_jump_incr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_distance_jump += val;
}

int thing_distance_jump_decr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return 0;
  }
  if ((int) t->_distance_jump - val <= 0) {
    return t->_distance_jump = 0;
  }
  return t->_distance_jump -= val;
}

int thing_lifespan(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_lifespan;
}

int thing_lifespan_set(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_lifespan = val;
}

int thing_lifespan_incr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_lifespan += val;
}

int thing_lifespan_decr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return 0;
  }
  if ((int) t->_lifespan - val <= 0) {
    return t->_lifespan = 0;
  }
  return t->_lifespan -= val;
}

int thing_submerged_pct(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return 0;
  }

  //
  // Floating when dead?
  //
  if (thing_is_dead(t)) {
    return t->_submerged_pct / 2;
  }

  return t->_submerged_pct;
}

int thing_submerged_pct_set(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_submerged_pct = val;
}

int thing_submerged_pct_incr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_submerged_pct += val;
}

int thing_submerged_pct_decr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return 0;
  }
  if (t->_submerged_pct - val <= 0) {
    return t->_submerged_pct = 0;
  }
  return t->_submerged_pct -= val;
}

int thing_age(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_age;
}

int thing_age_set(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_age = val;
}

int thing_age_incr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_age += val;
}

int thing_age_decr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return 0;
  }
  if (t->_age - val <= 0) {
    return t->_age = 0;
  }
  return t->_age -= val;
}

int thing_move_remaining(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_move_remaining;
}

int thing_move_remaining_set(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_move_remaining = val;
}

int thing_move_remaining_incr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_move_remaining += val;
}

int thing_move_remaining_decr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    ERR("No thing pointer set");
    return 0;
  }
  if (t->_move_remaining - val <= 0) {
    return t->_move_remaining = 0;
  }
  return t->_move_remaining -= val;
}

float thing_collision_radius(Thingp t)
{
  TRACE_NO_INDENT();

  return thing_is_collision_circle_small(t) ? THING_COLLISION_CIRCLE_SMALL_RADIUS
                                            : THING_COLLISION_CIRCLE_LARGE_RADIUS;
}

spoint thing_target(Thingp t)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    CROAK("No thing pointer set");
  }
  return make_spoint(t->_target);
}

void thing_target_set(Gamep g, Levelsp v, Levelp l, Thingp t, const spoint &val)
{
  TRACE_NO_INDENT();
  if (t == nullptr) {
    CROAK("No thing pointer set");
  }

  t->_target = val;
}
