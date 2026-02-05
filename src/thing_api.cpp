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
  if (! t) {
    CROAK("No thing pointer set");
  }
  return make_spoint(t->_at);
}

void thing_at_set(Thingp t, const spoint &val)
{
  TRACE_NO_INDENT();
  if (! t) {
    CROAK("No thing pointer set");
  }

  t->_old_at = t->_at;
  t->_at     = make_fpoint(val);
}

fpoint thing_real_at(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    CROAK("No thing pointer set");
  }
  return t->_at;
}

void thing_at_set(Thingp t, const fpoint &val)
{
  TRACE_NO_INDENT();
  if (! t) {
    CROAK("No thing pointer set");
  }

  t->_old_at = t->_at;
  t->_at     = val;
}

spoint thing_old_at(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    CROAK("No thing pointer set");
  }
  return make_spoint(t->_old_at);
}

spoint thing_prev_pix_at(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    CROAK("No thing pointer set");
  }
  return t->_prev_pix_at;
}

void thing_prev_pix_at_set(Gamep g, Levelsp v, Levelp l, Thingp t, const spoint &val)
{
  TRACE_NO_INDENT();
  if (! t) {
    CROAK("No thing pointer set");
  }
  t->_prev_pix_at = val;
}

void thing_pix_at_set(Gamep g, Levelsp v, Levelp l, Thingp t, const spoint &val)
{
  TRACE_NO_INDENT();
  if (! t) {
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
  if (! t) {
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
  if (! t) {
    CROAK("No thing pointer set");
  }
  return t->_moving_from;
}

void thing_moving_from_set(Thingp t, const spoint &val)
{
  TRACE_NO_INDENT();
  if (! t) {
    CROAK("No thing pointer set");
  }
  t->_moving_from = val;
}

int thing_speed(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_speed;
}

int thing_speed_set(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_speed = val;
}

int thing_weight(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_weight;
}

int thing_weight_set(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_weight = val;
}

int thing_health(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_health;
}

int thing_health_set(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return 0;
  }
  game_request_to_remake_ui_set(g);
  return t->_health = val;
}

int thing_health_incr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return 0;
  }
  game_request_to_remake_ui_set(g);
  return t->_health += val;
}

int thing_health_decr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return 0;
  }
  game_request_to_remake_ui_set(g);
  return t->_health -= val;
}

void thing_is_falling_set(Gamep g, Levelsp v, Levelp l, Thingp t, bool val)
{
  TRACE_NO_INDENT();
  if (! t) {
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
    if (t->_is_falling_ms) {
      return;
    }
  } else {
    //
    // Stop falling
    //
    if (! t->_is_falling_ms) {
      return;
    }
  }
  t->_is_falling_ms = val;

  if (val) {
    thing_on_fall_begin(g, v, l, t);
  } else {
    thing_on_fall_end(g, v, l, t);
  }
}

int thing_is_falling_incr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
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
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }

  return t->_is_falling_continues;
}

void thing_is_falling_continues_set(Gamep g, Levelsp v, Levelp l, Thingp t, bool val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return;
  }

  if (t->_is_falling_continues == val) {
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
  return thing_is_falling_continues_set(g, v, l, t, false);
}

void thing_is_hit_set(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return;
  }

  //
  // Once hit, it is treated as a counter
  //
  if (val) {
    //
    // Start the hit counter if not doing do
    //
    if (t->_is_hit) {
      return;
    }
  } else {
    //
    // Stop hit
    //
    if (! t->_is_hit) {
      return;
    }
  }

  t->_is_hit = val;

  if (val) {
    thing_on_hit_begin(g, v, l, t);
  } else {
    thing_on_hit_end(g, v, l, t);
  }
}

int thing_is_hit_incr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return 0;
  }

  if (! t->_is_hit && val) {
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
  if (! t) {
    ERR("No thing pointer set");
    return 0;
  }

  if ((int) t->_is_hit - val <= 0) {
    if (t->_is_hit) {
      thing_on_hit_end(g, v, l, t);
    }
    return t->_is_hit = 0;
  }

  return t->_is_hit -= val;
}

void thing_is_hot_set(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return;
  }

  //
  // Once hot, it is treated as a counter
  //
  if (val) {
    //
    // Start the hot counter if not doing do
    //
    if (t->_is_hot) {
      return;
    }
  } else {
    //
    // Stop hot
    //
    if (! t->_is_hot) {
      return;
    }
  }

  t->_is_hot = val;
}

int thing_is_hot_incr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
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
  if (! t) {
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
  if (! t) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_temperature;
}

int thing_temperature_set(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return 0;
  }

  if (! thing_is_physics_temperature(t)) {
    return 0;
  }

  //
  // Don't keep on heating up forever!
  //
  auto tp    = thing_tp(t);
  auto limit = std::max(tp_temperature_burns_at_get(tp), tp_temperature_melts_at_get(tp));
  if (limit && (val > limit)) {
    val = limit;
  }

  IF_DEBUG2 { THING_DBG(t, "temperature set to %u degrees", val); }

  return t->_temperature = val;
}

int thing_temperature_incr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return 0;
  }
  return thing_temperature_set(g, v, l, t, t->_temperature + val);
}

int thing_temperature_decr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return 0;
  }
  return thing_temperature_set(g, v, l, t, t->_temperature - val);
}

int thing_damage_this_tick(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_damage_this_tick;
}

int thing_damage_this_tick_set(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_damage_this_tick = val;
}

int thing_damage_this_tick_incr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_damage_this_tick += val;
}

int thing_damage_this_tick_decr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_damage_this_tick -= val;
}

int thing_keys_carried(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_keys_carried;
}

int thing_keys_carried_set(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_keys_carried = val;
}

int thing_keys_carried_incr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_keys_carried += val;
}

int thing_keys_carried_decr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_keys_carried -= val;
}

void thing_is_dead_set(Gamep g, Levelsp v, Levelp l, Thingp t, bool val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return;
  }

  if (t->_is_dead == val) {
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
  return thing_is_dead_set(g, v, l, t, false);
}

bool thing_is_burning(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return t->_is_burning;
}

void thing_is_burning_set(Gamep g, Levelsp v, Levelp l, Thingp t, bool val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return;
  }

  if (t->_is_burning == val) {
    return;
  }
  t->_is_burning = val;

  if (val) {
    THING_DBG(t, "is burning, %u degrees", thing_temperature(t));
  } else {
    //
    // Reset the temperature
    //
    auto tp = thing_tp(t);
    (void) thing_temperature_set(g, v, l, t, tp_temperature_initial_get(tp));

    THING_DBG(t, "is no longer burning, %u degrees", thing_temperature(t));
  }

  thing_is_burning_handle(g, v, l, t);
}

void thing_is_burning_unset(Gamep g, Levelsp v, Levelp l, Thingp t)
{
  TRACE_NO_INDENT();
  return thing_is_burning_set(g, v, l, t, false);
}

bool thing_is_corpse(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return t->_is_corpse;
}

void thing_is_corpse_set(Gamep g, Levelsp v, Levelp l, Thingp t, bool val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return;
  }

  if (t->_is_corpse == val) {
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
  return thing_is_corpse_set(g, v, l, t, false);
}

bool thing_is_scheduled_for_cleanup(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }

  return t->_is_scheduled_for_cleanup;
}

void thing_is_scheduled_for_cleanup_set(Gamep g, Levelsp v, Levelp l, Thingp t, bool val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return;
  }

  if (t->_is_scheduled_for_cleanup == val) {
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
  return thing_is_scheduled_for_cleanup_set(g, v, l, t, false);
}

bool thing_is_sleeping(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return t->_is_sleeping;
}

void thing_is_sleeping_set(Gamep g, Levelsp v, Levelp l, Thingp t, bool val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return;
  }
  t->_is_sleeping = val;
}

void thing_is_sleeping_unset(Gamep g, Levelsp v, Levelp l, Thingp t)
{
  TRACE_NO_INDENT();
  return thing_is_sleeping_set(g, v, l, t, false);
}

bool thing_is_unlocked(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return t->_is_unlocked;
}

void thing_is_unlocked_set(Gamep g, Levelsp v, Levelp l, Thingp t, bool val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return;
  }
  t->_is_unlocked = val;
}

void thing_is_unlocked_unset(Gamep g, Levelsp v, Levelp l, Thingp t)
{
  TRACE_NO_INDENT();
  return thing_is_unlocked_set(g, v, l, t, false);
}

bool thing_is_on_map(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return t->_is_on_map;
}

void thing_is_on_map_set(Gamep g, Levelsp v, Levelp l, Thingp t, bool val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return;
  }
  t->_is_on_map = val;
}

void thing_is_on_map_unset(Gamep g, Levelsp v, Levelp l, Thingp t)
{
  TRACE_NO_INDENT();
  return thing_is_on_map_set(g, v, l, t, false);
}

void thing_is_moving_set(Gamep g, Levelsp v, Levelp l, Thingp t, bool val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return;
  }

  if (t->_is_moving == val) {
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
  return thing_is_moving_set(g, v, l, t, false);
}

void thing_is_spawned_set(Gamep g, Levelsp v, Levelp l, Thingp t, bool val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return;
  }

  if (t->_is_spawned == val) {
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
  return thing_is_spawned_set(g, v, l, t, false);
}

bool thing_is_teleporting(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return t->_is_teleporting;
}

void thing_is_teleporting_set(Gamep g, Levelsp v, Levelp l, Thingp t, bool val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return;
  }

  if (t->_is_teleporting == val) {
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
  return thing_is_teleporting_set(g, v, l, t, false);
}

void thing_is_jumping_set(Gamep g, Levelsp v, Levelp l, Thingp t, bool val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return;
  }

  if (t->_is_jumping == val) {
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
  return thing_is_jumping_set(g, v, l, t, false);
}

//
// Returns true/false on success/fail
//
bool thing_is_open_try_set(Gamep g, Levelsp v, Levelp l, Thingp t, Thingp opener, bool val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }

  if (t->_is_open == val) {
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
  if (! t) {
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

  if (! item) {
    ERR("No thing pointer set");
    return false;
  }

  if (item->_is_carried == val) {
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
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_animated_can_hflip);
}

bool thing_is_animated_no_dir(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_animated_no_dir);
}

bool thing_is_animated_sync_first(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_animated_sync_first);
}

bool thing_is_animated(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_animated);
}

bool thing_is_barrel(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_barrel);
}

bool thing_is_blit_centered(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_blit_centered);
}

bool thing_is_blit_flush_per_line(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_blit_flush_per_line);
}

bool thing_is_blit_outlined(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_blit_outlined);
}

bool thing_is_blit_square_outlined(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_blit_square_outlined);
}

bool thing_is_brazier(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_brazier);
}

bool thing_is_bridge(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_bridge);
}

bool thing_is_chasm(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_chasm);
}

bool thing_is_corridor(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_corridor);
}

bool thing_is_collision_square(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_collision_square);
}

bool thing_is_obs_to_cursor_path(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
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

  return tp_flag(thing_tp(t), is_obs_to_cursor_path);
}

bool thing_is_cursor_path_hazard(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_cursor_path_hazard);
}

bool thing_is_cursor_path(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_cursor_path);
}

bool thing_is_cursor(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_cursor);
}

bool thing_is_deep_water(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_deep_water);
}

bool thing_is_described_cursor(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_described_cursor);
}

bool thing_is_dirt(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_dirt);
}

bool thing_is_door_unlocked(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_door_unlocked);
}

bool thing_is_dungeon_entrance(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_dungeon_entrance);
}

bool thing_is_entrance(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_entrance);
}

bool thing_is_exit(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_exit);
}

bool thing_is_floor(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_floor);
}

bool thing_is_foliage(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_foliage);
}

bool thing_is_ghost(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_ghost);
}

bool thing_is_kobalos(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_kobalos);
}

bool thing_is_grass(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_grass);
}

bool thing_is_key(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_key);
}

bool thing_is_lava(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_lava);
}

bool thing_is_level_across(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_level_across);
}

bool thing_is_level_curr(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_level_curr);
}

bool thing_is_level_down(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_level_down);
}

bool thing_is_level_final(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_level_final);
}

bool thing_is_level_next(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_level_next);
}

bool thing_is_level_not_visited(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_level_not_visited);
}

bool thing_is_level_visited(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_level_visited);
}

bool thing_is_minion(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_minion);
}

bool thing_is_mob(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_mob);
}

bool thing_is_mob1(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_mob1);
}

bool thing_is_mob2(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_mob2);
}

bool thing_is_monst(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_monst);
}

bool thing_is_monst_group_easy(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_monst_group_easy);
}

bool thing_is_monst_group_hard(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_monst_group_hard);
}

bool thing_is_obs_to_movement(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
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

  return tp_flag(thing_tp(t), is_obs_to_movement);
}

bool thing_is_pillar(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_pillar);
}

bool thing_is_rock(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_rock);
}

bool thing_is_door_secret(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_door_secret);
}

bool thing_is_slime(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_slime);
}

bool thing_is_teleport(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_teleport);
}

bool thing_is_tickable(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_tickable);
}

bool thing_is_tiled(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_tiled);
}

bool thing_is_trap(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_trap);
}

bool thing_is_treasure(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_treasure);
}

bool thing_is_unused1(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_unused1);
}

bool thing_is_unused2(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_unused2);
}

bool thing_is_unused3(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_unused3);
}

bool thing_is_unused4(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_unused4);
}

bool thing_is_unused5(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_unused5);
}

bool thing_is_unused6(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_unused6);
}

bool thing_is_unused7(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_unused7);
}

bool thing_is_unused8(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_unused8);
}

bool thing_is_unused9(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_unused9);
}

bool thing_is_unused10(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_unused10);
}

bool thing_is_unused11(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_unused11);
}

bool thing_is_unused12(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_unused12);
}

bool thing_is_unused13(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_unused13);
}

bool thing_is_unused14(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_unused14);
}

bool thing_is_unused15(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_unused15);
}

bool thing_is_unused16(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_unused16);
}

bool thing_is_unused17(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_unused17);
}

bool thing_is_unused18(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_unused18);
}

bool thing_is_unused19(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_unused19);
}

bool thing_is_unused20(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_unused20);
}

bool thing_is_unused21(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_unused21);
}

bool thing_is_unused22(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_unused22);
}

bool thing_is_unused23(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_unused23);
}

bool thing_is_unused24(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_unused24);
}

bool thing_is_unused25(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_unused25);
}

bool thing_is_unused26(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_unused26);
}

bool thing_is_unused27(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_unused27);
}

bool thing_is_unused28(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_unused28);
}

bool thing_is_unused29(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_unused29);
}

bool thing_is_unused30(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_unused30);
}

bool thing_is_unused31(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_unused31);
}

bool thing_is_unused32(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_unused32);
}

bool thing_is_unused33(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_unused33);
}

bool thing_is_unused34(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_unused34);
}

bool thing_is_unused35(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_unused35);
}

bool thing_is_unused36(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_unused36);
}

bool thing_is_unused37(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_unused37);
}

bool thing_is_unused38(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_unused38);
}

bool thing_is_unused39(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_unused39);
}

bool thing_is_unused40(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_unused40);
}

bool thing_is_unused41(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_unused41);
}

bool thing_is_unused42(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_unused42);
}

bool thing_is_unused43(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_unused43);
}

bool thing_is_unused44(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_unused44);
}

bool thing_is_unused45(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_unused45);
}

bool thing_is_unused46(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_unused46);
}

bool thing_is_unused47(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_unused47);
}

bool thing_is_unused48(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_unused48);
}

bool thing_is_unused49(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_unused49);
}

bool thing_is_unused50(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_unused50);
}

bool thing_is_unused51(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_unused51);
}

bool thing_is_unused52(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_unused52);
}

bool thing_is_unused53(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_unused53);
}

bool thing_is_unused54(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_unused54);
}

bool thing_is_unused55(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_unused55);
}

bool thing_is_unused56(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_unused56);
}

bool thing_is_unused57(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_unused57);
}

bool thing_is_unused58(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_unused58);
}

bool thing_is_unused59(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_unused59);
}

bool thing_is_unused60(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_unused60);
}

bool thing_is_unused61(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_unused61);
}

bool thing_is_unused62(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_unused62);
}

bool thing_is_unused63(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_unused63);
}

bool thing_is_unused64(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_unused64);
}

bool thing_is_unused65(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_unused65);
}

bool thing_is_unused66(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_unused66);
}

bool thing_is_unused67(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_unused67);
}

bool thing_is_unused68(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_unused68);
}

bool thing_is_unused69(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_unused69);
}

bool thing_is_unused70(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_unused70);
}

bool thing_is_unused71(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_unused71);
}

bool thing_is_unused72(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_unused72);
}

bool thing_is_unused73(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_unused73);
}

bool thing_is_unused74(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_unused74);
}

bool thing_is_blit_on_ground(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_blit_on_ground);
}

bool thing_is_insectoid(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_insectoid);
}

bool thing_is_mantisman(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_mantisman);
}

bool thing_is_dmap(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_dmap);
}

bool thing_is_obs_to_spawning(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_obs_to_spawning);
}

bool thing_is_mob_kill_minions_on_death(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_mob_kill_minions_on_death);
}

bool thing_is_border(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_border);
}

bool thing_is_collision_detection_enabled(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_collision_detection_enabled);
}

bool thing_is_gold(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_gold);
}

bool thing_is_glass(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_glass);
}

bool thing_is_plant(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_plant);
}

bool thing_is_wood(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_wood);
}

bool thing_is_metal(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_metal);
}

bool thing_is_flesh(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_flesh);
}

bool thing_is_stone(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_stone);
}

bool thing_is_meltable(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_meltable);
}

bool thing_is_blit_pixel_lighting(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_blit_pixel_lighting);
}

bool thing_is_dead_on_collision(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_dead_on_collision);
}

bool thing_is_obs_to_jumping_out_of(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_obs_to_jumping_out_of);
}

bool thing_is_cursor_path_warning(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_cursor_path_warning);
}

bool thing_is_collision_circle_large(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_collision_circle_large);
}

bool thing_is_collision_circle_small(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_collision_circle_small);
}

bool thing_is_fireball(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_fireball);
}

bool thing_is_projectile(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_projectile);
}

bool thing_is_health_bar_shown(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_health_bar_shown);
}

bool thing_is_item_mergeable(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_item_mergeable);
}

bool thing_is_door_locked(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_door_locked);
}

bool thing_is_inventory_item(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_inventory_item);
}

bool thing_is_able_to_open(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_able_to_open);
}

bool thing_is_item(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_item);
}

bool thing_is_able_to_crush_grass(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_able_to_crush_grass);
}

bool thing_is_able_to_collect_keys(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_able_to_collect_keys);
}

bool thing_is_able_to_collect_items(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_able_to_collect_items);
}

bool thing_is_collectable(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_collectable);
}

bool thing_is_blit_when_obscured(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_blit_when_obscured);
}

bool thing_is_openable(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_openable);
}

bool thing_is_tick_end_delay(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_tick_end_delay);
}

bool thing_is_damage_capped(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_damage_capped);
}

bool thing_is_physics_explosion(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_physics_explosion);
}

bool thing_is_explosion(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_explosion);
}

bool thing_is_obs_to_explosion(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
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

  return tp_flag(thing_tp(t), is_obs_to_explosion);
}

bool thing_is_obs_to_jump_over(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
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

  return tp_flag(thing_tp(t), is_obs_to_jump_over);
}

bool thing_is_teleport_blocked(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_teleport_blocked);
}

bool thing_is_cursor_path_none(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_cursor_path_none);
}

bool thing_is_able_to_jump(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_able_to_jump);
}

bool thing_is_blit_obscures(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_blit_obscures);
}

bool thing_is_flying(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_flying);
}

bool thing_is_needs_move_confirm(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_needs_move_confirm);
}

bool thing_is_obs_to_falling_onto(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
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

  return tp_flag(thing_tp(t), is_obs_to_falling_onto);
}

bool thing_is_obs_to_jumping_onto(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
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

  return tp_flag(thing_tp(t), is_obs_to_jumping_onto);
}

bool thing_is_obs_to_teleporting_onto(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
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

  return tp_flag(thing_tp(t), is_obs_to_teleporting_onto);
}

bool thing_is_submergible(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_submergible);
}

bool thing_is_able_to_fall(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_able_to_fall);
}

bool thing_is_physics_water(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_physics_water);
}

bool thing_is_indestructible(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_indestructible);
}

bool thing_is_floating(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_floating);
}

bool thing_is_obs_to_fire(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
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

  return tp_flag(thing_tp(t), is_obs_to_fire);
}

bool thing_is_combustible(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_combustible);
}

bool thing_is_blit_shown_in_chasms(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_blit_shown_in_chasms);
}

bool thing_is_gaseous(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_gaseous);
}

bool thing_is_extinguished_on_death(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_extinguished_on_death);
}

bool thing_is_broken_on_death(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_broken_on_death);
}

bool thing_is_undead(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_undead);
}

bool thing_is_wait_on_dead_anim(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_wait_on_dead_anim);
}

bool thing_is_corpse_on_death(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_corpse_on_death);
}

bool thing_is_monst_group_mob(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_monst_group_mob);
}

bool thing_is_blit_if_has_seen(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_blit_if_has_seen);
}

bool thing_is_smoke(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_smoke);
}

bool thing_is_steam(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_steam);
}

bool thing_is_fire(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_fire);
}

bool thing_is_burnable(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_burnable);
}

bool thing_is_dead_on_shoving(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_dead_on_shoving);
}

bool thing_is_able_to_shove(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_able_to_shove);
}

bool thing_is_shovable(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_shovable);
}

bool thing_is_loggable(Thingp t)
{
  TRACE_NO_INDENT();

  if (! t) {
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

  return tp_flag(thing_tp(t), is_loggable);
}

bool thing_is_crushable(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_crushable);
}

bool thing_is_ethereal(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_ethereal);
}

bool thing_is_blit_shown_in_overlay(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_blit_shown_in_overlay);
}

bool thing_is_levitating(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_levitating);
}

bool thing_is_item_equipable(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_item_equipable);
}

bool thing_is_item_droppable(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_item_droppable);
}

bool thing_is_walk_through_walls(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_walk_through_walls);
}

bool thing_is_wall(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_wall);
}

bool thing_is_water(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
  return tp_flag(thing_tp(t), is_water);
}

int thing_value1(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_value1;
}

int thing_value1_set(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_value1 = val;
}

int thing_value1_incr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_value1 += val;
}

int thing_value1_decr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_value1 -= val;
}
int thing_value2(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_value2;
}

int thing_value2_set(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_value2 = val;
}

int thing_value2_incr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_value2 += val;
}

int thing_value2_decr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_value2 -= val;
}
int thing_value3(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_value3;
}

int thing_value3_set(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_value3 = val;
}

int thing_value3_incr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_value3 += val;
}

int thing_value3_decr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_value3 -= val;
}
int thing_value4(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_value4;
}

int thing_value4_set(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_value4 = val;
}

int thing_value4_incr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_value4 += val;
}

int thing_value4_decr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_value4 -= val;
}
int thing_value5(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_value5;
}

int thing_value5_set(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_value5 = val;
}

int thing_value5_incr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_value5 += val;
}

int thing_value5_decr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_value5 -= val;
}
int thing_value6(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_value6;
}

int thing_value6_set(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_value6 = val;
}

int thing_value6_incr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_value6 += val;
}

int thing_value6_decr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_value6 -= val;
}
int thing_value7(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_value7;
}

int thing_value7_set(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_value7 = val;
}

int thing_value7_incr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_value7 += val;
}

int thing_value7_decr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_value7 -= val;
}
int thing_value8(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_value8;
}

int thing_value8_set(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_value8 = val;
}

int thing_value8_incr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_value8 += val;
}

int thing_value8_decr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_value8 -= val;
}
int thing_value9(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_value9;
}

int thing_value9_set(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_value9 = val;
}

int thing_value9_incr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_value9 += val;
}

int thing_value9_decr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_value9 -= val;
}
int thing_value10(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_value10;
}

int thing_value10_set(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_value10 = val;
}

int thing_value10_incr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_value10 += val;
}

int thing_value10_decr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_value10 -= val;
}
int thing_value11(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_value11;
}

int thing_value11_set(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_value11 = val;
}

int thing_value11_incr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_value11 += val;
}

int thing_value11_decr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_value11 -= val;
}
int thing_value12(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_value12;
}

int thing_value12_set(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_value12 = val;
}

int thing_value12_incr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_value12 += val;
}

int thing_value12_decr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_value12 -= val;
}
int thing_value13(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_value13;
}

int thing_value13_set(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_value13 = val;
}

int thing_value13_incr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_value13 += val;
}

int thing_value13_decr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_value13 -= val;
}
int thing_value14(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_value14;
}

int thing_value14_set(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_value14 = val;
}

int thing_value14_incr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_value14 += val;
}

int thing_value14_decr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_value14 -= val;
}
int thing_value15(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_value15;
}

int thing_value15_set(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_value15 = val;
}

int thing_value15_incr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_value15 += val;
}

int thing_value15_decr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_value15 -= val;
}
int thing_value16(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_value16;
}

int thing_value16_set(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_value16 = val;
}

int thing_value16_incr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_value16 += val;
}

int thing_value16_decr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_value16 -= val;
}
int thing_value17(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_value17;
}

int thing_value17_set(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_value17 = val;
}

int thing_value17_incr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_value17 += val;
}

int thing_value17_decr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_value17 -= val;
}
int thing_value18(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_value18;
}

int thing_value18_set(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_value18 = val;
}

int thing_value18_incr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_value18 += val;
}

int thing_value18_decr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_value18 -= val;
}
int thing_value19(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_value19;
}

int thing_value19_set(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_value19 = val;
}

int thing_value19_incr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_value19 += val;
}

int thing_value19_decr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_value19 -= val;
}
int thing_value20(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_value20;
}

int thing_value20_set(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_value20 = val;
}

int thing_value20_incr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_value20 += val;
}

int thing_value20_decr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_value20 -= val;
}
int thing_value21(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_value21;
}

int thing_value21_set(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_value21 = val;
}

int thing_value21_incr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_value21 += val;
}

int thing_value21_decr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_value21 -= val;
}
int thing_distance_minion_from_mob_max(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_distance_minion_from_mob_max;
}

int thing_distance_minion_from_mob_max_set(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_distance_minion_from_mob_max = val;
}

int thing_distance_minion_from_mob_max_incr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_distance_minion_from_mob_max += val;
}

int thing_distance_minion_from_mob_max_decr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_distance_minion_from_mob_max -= val;
}
int thing_distance_vision(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_distance_vision;
}

int thing_distance_vision_set(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_distance_vision = val;
}

int thing_distance_vision_incr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_distance_vision += val;
}

int thing_distance_vision_decr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_distance_vision -= val;
}

int thing_variant(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_variant;
}

int thing_variant_set(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_variant = val;
}

int thing_variant_incr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_variant += val;
}

int thing_variant_decr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_variant -= val;
}

ThingPriorityType thing_priority(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return THING_PRIORITY_LOW;
  }
  return t->_priority;
}

ThingPriorityType thing_priority_set(Gamep g, Levelsp v, Levelp l, Thingp t, ThingPriorityType val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return THING_PRIORITY_LOW;
  }
  return t->_priority = val;
}

int thing_vision_distance(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_vision_distance;
}

int thing_vision_distance_set(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_vision_distance = val;
}

int thing_vision_distance_incr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_vision_distance += val;
}

int thing_vision_distance_decr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_vision_distance -= val;
}

int thing_jump_distance(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_jump_distance;
}

int thing_jump_distance_set(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_jump_distance = val;
}

int thing_jump_distance_incr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_jump_distance += val;
}

int thing_jump_distance_decr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_jump_distance -= val;
}

int thing_lifespan(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_lifespan;
}

int thing_lifespan_set(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_lifespan = val;
}

int thing_lifespan_incr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_lifespan += val;
}

int thing_lifespan_decr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_lifespan -= val;
}

int thing_submerged_pct(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
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
  if (! t) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_submerged_pct = val;
}

int thing_submerged_pct_incr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_submerged_pct += val;
}

int thing_submerged_pct_decr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_submerged_pct -= val;
}

int thing_age(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_age;
}

int thing_age_set(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_age = val;
}

int thing_age_incr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_age += val;
}

int thing_age_decr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return 0;
  }
  return t->_age -= val;
}

float thing_collision_radius(Thingp t)
{
  TRACE_NO_INDENT();

  return thing_is_collision_circle_small(t) ? 0.025 : 0.5;
}
