//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_game.hpp"
#include "my_level.hpp"
#include "my_main.hpp"
#include "my_tp_callbacks.hpp"

int thing_speed(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return 0;
  }
  return t->_speed;
}

int thing_speed_set(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return 0;
  }
  return t->_speed = val;
}

int thing_weight(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return 0;
  }
  return t->_weight;
}

int thing_weight_set(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return 0;
  }
  return t->_weight = val;
}

int thing_health(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return 0;
  }
  return t->_health;
}

int thing_health_set(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return 0;
  }
  game_request_to_remake_ui_set(g);
  return t->_health = val;
}

int thing_health_incr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return 0;
  }
  game_request_to_remake_ui_set(g);
  return t->_health += val;
}

int thing_health_decr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return 0;
  }
  game_request_to_remake_ui_set(g);
  return t->_health -= val;
}

int thing_is_falling(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return 0;
  }
  return t->_is_falling;
}

void thing_is_falling_set(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return;
  }

  //
  // Once falling, it is treated as a counter
  //
  if (val) {
    //
    // Start falling if not doing do
    //
    if (t->_is_falling) {
      return;
    }
  } else {
    //
    // Stop falling
    //
    if (! t->_is_falling) {
      return;
    }
  }
  t->_is_falling = val;

  if (val) {
    tp_on_fall_begin(g, v, l, t);
  } else {
    tp_on_fall_end(g, v, l, t);
  }
}

int thing_is_falling_incr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return 0;
  }
  return t->_is_falling += val;
}

int thing_is_falling_decr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return 0;
  }
  return t->_is_falling -= val;
}

int thing_temperature(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return 0;
  }
  return t->_temperature;
}

int thing_temperature_set(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return 0;
  }
  return t->_temperature = val;
}

int thing_temperature_incr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return 0;
  }
  return t->_temperature += val;
}

int thing_temperature_decr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return 0;
  }
  return t->_temperature -= val;
}

bool thing_is_dead(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return false;
  }
  return t->_is_dead;
}

void thing_is_dead_set(Gamep g, Levelsp v, Levelp l, Thingp t, bool val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return;
  }

  if (t->_is_dead == val) {
    return;
  }
  t->_is_dead = val;

  if (val && thing_is_loggable(t)) {
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
    ERR("no thing for %s", __FUNCTION__);
    return false;
  }
  return t->_is_burning;
}

void thing_is_burning_set(Gamep g, Levelsp v, Levelp l, Thingp t, bool val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return;
  }

  if (t->_is_burning == val) {
    return;
  }
  t->_is_burning = val;

  if (val && thing_is_loggable(t)) {
    THING_DBG(t, "is burning");
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
    ERR("no thing for %s", __FUNCTION__);
    return false;
  }
  return t->_is_corpse;
}

void thing_is_corpse_set(Gamep g, Levelsp v, Levelp l, Thingp t, bool val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return;
  }

  if (t->_is_corpse == val) {
    return;
  }
  t->_is_corpse = val;

  if (val && thing_is_loggable(t)) {
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
    ERR("no thing for %s", __FUNCTION__);
    return false;
  }

  return t->_is_scheduled_for_cleanup;
}

void thing_is_scheduled_for_cleanup_set(Gamep g, Levelsp v, Levelp l, Thingp t, bool val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return;
  }

  if (t->_is_scheduled_for_cleanup == val) {
    return;
  }
  t->_is_scheduled_for_cleanup = val;

  if (val && thing_is_loggable(t)) {
    THING_DBG(t, "is scheduled for cleanup");
  }

  game_request_to_cleanup_things_set(g);
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
    ERR("no thing for %s", __FUNCTION__);
    return false;
  }
  return t->_is_sleeping;
}

void thing_is_sleeping_set(Gamep g, Levelsp v, Levelp l, Thingp t, bool val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return;
  }
  t->_is_sleeping = val;
}

void thing_is_sleeping_unset(Gamep g, Levelsp v, Levelp l, Thingp t)
{
  TRACE_NO_INDENT();
  return thing_is_sleeping_set(g, v, l, t, false);
}

bool thing_is_open(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return false;
  }
  return t->_is_open;
}

void thing_is_open_set(Gamep g, Levelsp v, Levelp l, Thingp t, bool val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return;
  }
  t->_is_open = val;
}

void thing_is_open_unset(Gamep g, Levelsp v, Levelp l, Thingp t)
{
  TRACE_NO_INDENT();
  return thing_is_open_set(g, v, l, t, false);
}

bool thing_is_on_map(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return false;
  }
  return t->_is_on_map;
}

void thing_is_on_map_set(Gamep g, Levelsp v, Levelp l, Thingp t, bool val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return;
  }
  t->_is_on_map = val;
}

void thing_is_on_map_unset(Gamep g, Levelsp v, Levelp l, Thingp t)
{
  TRACE_NO_INDENT();
  return thing_is_on_map_set(g, v, l, t, false);
}

bool thing_is_moving(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return false;
  }
  return t->_is_moving;
}

void thing_is_moving_set(Gamep g, Levelsp v, Levelp l, Thingp t, bool val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return;
  }

  if (t->_is_moving == val) {
    return;
  }
  t->_is_moving = val;

  if (val) {
    tp_on_moved(g, v, l, t);
  }
}

void thing_is_moving_unset(Gamep g, Levelsp v, Levelp l, Thingp t)
{
  TRACE_NO_INDENT();
  return thing_is_moving_set(g, v, l, t, false);
}

bool thing_is_teleporting(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return false;
  }
  return t->_is_teleporting;
}

void thing_is_teleporting_set(Gamep g, Levelsp v, Levelp l, Thingp t, bool val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return;
  }

  if (t->_is_teleporting == val) {
    return;
  }
  t->_is_teleporting = val;

  if (val) {
    tp_on_teleported(g, v, l, t);
  }
}

void thing_is_teleporting_unset(Gamep g, Levelsp v, Levelp l, Thingp t)
{
  TRACE_NO_INDENT();
  return thing_is_teleporting_set(g, v, l, t, false);
}

bool thing_is_jumping(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return false;
  }
  return t->_is_jumping;
}

void thing_is_jumping_set(Gamep g, Levelsp v, Levelp l, Thingp t, bool val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return;
  }

  if (t->_is_jumping == val) {
    return;
  }
  t->_is_jumping = val;

  if (val) {
    tp_on_jump_begin(g, v, l, t);
  } else {
    tp_on_jump_end(g, v, l, t);
  }
}

void thing_is_jumping_unset(Gamep g, Levelsp v, Levelp l, Thingp t)
{
  TRACE_NO_INDENT();
  return thing_is_jumping_set(g, v, l, t, false);
}

bool thing_is_animated_can_hflip(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return false;
  }
  return tp_flag(thing_tp(t), is_animated_can_hflip);
}

bool thing_is_animated_no_dir(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return false;
  }
  return tp_flag(thing_tp(t), is_animated_no_dir);
}

bool thing_is_animated_sync_first(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return false;
  }
  return tp_flag(thing_tp(t), is_animated_sync_first);
}

bool thing_is_animated(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return false;
  }
  return tp_flag(thing_tp(t), is_animated);
}

bool thing_is_barrel(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return false;
  }
  return tp_flag(thing_tp(t), is_barrel);
}

bool thing_is_blit_centered(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return false;
  }
  return tp_flag(thing_tp(t), is_blit_centered);
}

bool thing_is_blit_on_ground(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return false;
  }
  return tp_flag(thing_tp(t), is_blit_on_ground);
}

bool thing_is_blit_outlined(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return false;
  }
  return tp_flag(thing_tp(t), is_blit_outlined);
}

bool thing_is_blit_square_outlined(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return false;
  }
  return tp_flag(thing_tp(t), is_blit_square_outlined);
}

bool thing_is_brazier(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return false;
  }
  return tp_flag(thing_tp(t), is_brazier);
}

bool thing_is_bridge(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return false;
  }
  return tp_flag(thing_tp(t), is_bridge);
}

bool thing_is_chasm(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return false;
  }
  return tp_flag(thing_tp(t), is_chasm);
}

bool thing_is_corridor(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return false;
  }
  return tp_flag(thing_tp(t), is_corridor);
}

bool thing_is_cursor_hazard(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return false;
  }
  return tp_flag(thing_tp(t), is_cursor_hazard);
}

bool thing_is_cursor_path_blocker(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return false;
  }
  return tp_flag(thing_tp(t), is_cursor_path_blocker);
}

bool thing_is_cursor_path_hazard(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return false;
  }
  return tp_flag(thing_tp(t), is_cursor_path_hazard);
}

bool thing_is_cursor_path(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return false;
  }
  return tp_flag(thing_tp(t), is_cursor_path);
}

bool thing_is_cursor(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return false;
  }
  return tp_flag(thing_tp(t), is_cursor);
}

bool thing_is_deep_water(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return false;
  }
  return tp_flag(thing_tp(t), is_deep_water);
}

bool thing_is_described_cursor(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return false;
  }
  return tp_flag(thing_tp(t), is_described_cursor);
}

bool thing_is_dirt(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return false;
  }
  return tp_flag(thing_tp(t), is_dirt);
}

bool thing_is_door(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return false;
  }
  return tp_flag(thing_tp(t), is_door);
}

bool thing_is_dungeon_entrance(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return false;
  }
  return tp_flag(thing_tp(t), is_dungeon_entrance);
}

bool thing_is_entrance(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return false;
  }
  return tp_flag(thing_tp(t), is_entrance);
}

bool thing_is_exit(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return false;
  }
  return tp_flag(thing_tp(t), is_exit);
}

bool thing_is_floor(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return false;
  }
  return tp_flag(thing_tp(t), is_floor);
}

bool thing_is_foliage(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return false;
  }
  return tp_flag(thing_tp(t), is_foliage);
}

bool thing_is_ghost(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return false;
  }
  return tp_flag(thing_tp(t), is_ghost);
}

bool thing_is_goblin(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return false;
  }
  return tp_flag(thing_tp(t), is_goblin);
}

bool thing_is_grass(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return false;
  }
  return tp_flag(thing_tp(t), is_grass);
}

bool thing_is_key(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return false;
  }
  return tp_flag(thing_tp(t), is_key);
}

bool thing_is_lava(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return false;
  }
  return tp_flag(thing_tp(t), is_lava);
}

bool thing_is_level_across(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return false;
  }
  return tp_flag(thing_tp(t), is_level_across);
}

bool thing_is_level_curr(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return false;
  }
  return tp_flag(thing_tp(t), is_level_curr);
}

bool thing_is_level_down(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return false;
  }
  return tp_flag(thing_tp(t), is_level_down);
}

bool thing_is_level_final(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return false;
  }
  return tp_flag(thing_tp(t), is_level_final);
}

bool thing_is_level_next(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return false;
  }
  return tp_flag(thing_tp(t), is_level_next);
}

bool thing_is_level_not_visited(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return false;
  }
  return tp_flag(thing_tp(t), is_level_not_visited);
}

bool thing_is_level_visited(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return false;
  }
  return tp_flag(thing_tp(t), is_level_visited);
}

bool thing_is_light_source(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return false;
  }
  return tp_flag(thing_tp(t), is_light_source);
}

bool thing_is_minion(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return false;
  }
  return tp_flag(thing_tp(t), is_minion);
}

bool thing_is_mob(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return false;
  }
  return tp_flag(thing_tp(t), is_mob);
}

bool thing_is_mob1(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return false;
  }
  return tp_flag(thing_tp(t), is_mob1);
}

bool thing_is_mob2(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return false;
  }
  return tp_flag(thing_tp(t), is_mob2);
}

bool thing_is_monst(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return false;
  }
  return tp_flag(thing_tp(t), is_monst);
}

bool thing_is_monst_group_1(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return false;
  }
  return tp_flag(thing_tp(t), is_monst_group_1);
}

bool thing_is_monst_group_2(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return false;
  }
  return tp_flag(thing_tp(t), is_monst_group_2);
}

bool thing_is_obstacle_to_movement(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return false;
  }
  return tp_flag(thing_tp(t), is_obstacle_to_movement);
}

bool thing_is_pillar(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return false;
  }
  return tp_flag(thing_tp(t), is_pillar);
}

bool thing_is_player(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return false;
  }
  return tp_flag(thing_tp(t), is_player);
}

bool thing_is_rock(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return false;
  }
  return tp_flag(thing_tp(t), is_rock);
}

bool thing_is_secret_door(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return false;
  }
  return tp_flag(thing_tp(t), is_secret_door);
}

bool thing_is_slime(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return false;
  }
  return tp_flag(thing_tp(t), is_slime);
}

bool thing_is_teleport(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return false;
  }
  return tp_flag(thing_tp(t), is_teleport);
}

bool thing_is_tickable(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return false;
  }
  return tp_flag(thing_tp(t), is_tickable);
}

bool thing_is_tiled(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return false;
  }
  return tp_flag(thing_tp(t), is_tiled);
}

bool thing_is_trap(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return false;
  }
  return tp_flag(thing_tp(t), is_trap);
}

bool thing_is_treasure(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return false;
  }
  return tp_flag(thing_tp(t), is_treasure);
}

bool thing_is_unused1(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return false;
  }
  return tp_flag(thing_tp(t), is_unused1);
}

bool thing_is_unused10(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return false;
  }
  return tp_flag(thing_tp(t), is_unused10);
}

bool thing_is_unused11(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return false;
  }
  return tp_flag(thing_tp(t), is_unused11);
}

bool thing_is_unused12(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return false;
  }
  return tp_flag(thing_tp(t), is_unused12);
}

bool thing_is_unused13(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return false;
  }
  return tp_flag(thing_tp(t), is_unused13);
}

bool thing_is_unused14(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return false;
  }
  return tp_flag(thing_tp(t), is_unused14);
}

bool thing_is_unused15(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return false;
  }
  return tp_flag(thing_tp(t), is_unused15);
}

bool thing_is_unused16(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return false;
  }
  return tp_flag(thing_tp(t), is_unused16);
}

bool thing_is_unused17(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return false;
  }
  return tp_flag(thing_tp(t), is_unused17);
}

bool thing_is_unused18(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return false;
  }
  return tp_flag(thing_tp(t), is_unused18);
}

bool thing_is_unused19(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return false;
  }
  return tp_flag(thing_tp(t), is_unused19);
}

bool thing_is_unused2(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return false;
  }
  return tp_flag(thing_tp(t), is_unused2);
}

bool thing_is_unused20(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return false;
  }
  return tp_flag(thing_tp(t), is_unused20);
}

bool thing_is_unused21(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return false;
  }
  return tp_flag(thing_tp(t), is_unused21);
}

bool thing_is_unused22(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return false;
  }
  return tp_flag(thing_tp(t), is_unused22);
}

bool thing_is_unused23(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return false;
  }
  return tp_flag(thing_tp(t), is_unused23);
}

bool thing_is_unused24(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return false;
  }
  return tp_flag(thing_tp(t), is_unused24);
}

bool thing_is_unused25(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return false;
  }
  return tp_flag(thing_tp(t), is_unused25);
}

bool thing_is_obstacle_to_jump_over(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return false;
  }
  return tp_flag(thing_tp(t), is_obstacle_to_jump_over);
}

bool thing_is_teleport_blocked(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return false;
  }
  return tp_flag(thing_tp(t), is_teleport_blocked);
}

bool thing_is_cursor_path_none(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return false;
  }
  return tp_flag(thing_tp(t), is_cursor_path_none);
}

bool thing_is_able_to_jump(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return false;
  }
  return tp_flag(thing_tp(t), is_able_to_jump);
}

bool thing_is_unused3(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return false;
  }
  return tp_flag(thing_tp(t), is_unused3);
}

bool thing_is_flying(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return false;
  }
  return tp_flag(thing_tp(t), is_flying);
}

bool thing_is_needs_move_confirm(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return false;
  }
  return tp_flag(thing_tp(t), is_needs_move_confirm);
}

bool thing_is_obstacle_to_falling(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return false;
  }
  return tp_flag(thing_tp(t), is_obstacle_to_falling);
}

bool thing_is_obstacle_to_jump_landing(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return false;
  }
  return tp_flag(thing_tp(t), is_obstacle_to_jump_landing);
}

bool thing_is_submergible(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return false;
  }
  return tp_flag(thing_tp(t), is_submergible);
}

bool thing_is_physics_gravity(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return false;
  }
  return tp_flag(thing_tp(t), is_physics_gravity);
}

bool thing_is_physics_water(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return false;
  }
  return tp_flag(thing_tp(t), is_physics_water);
}

bool thing_is_indestructible(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return false;
  }
  return tp_flag(thing_tp(t), is_indestructible);
}

bool thing_is_floating(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return false;
  }
  return tp_flag(thing_tp(t), is_floating);
}

bool thing_is_obstacle_to_fire(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return false;
  }
  return tp_flag(thing_tp(t), is_obstacle_to_fire);
}

bool thing_is_combustible(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return false;
  }
  return tp_flag(thing_tp(t), is_combustible);
}

bool thing_is_unused4(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return false;
  }
  return tp_flag(thing_tp(t), is_unused4);
}

bool thing_is_gaseous(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return false;
  }
  return tp_flag(thing_tp(t), is_gaseous);
}

bool thing_is_extinguished_on_death(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return false;
  }
  return tp_flag(thing_tp(t), is_extinguished_on_death);
}

bool thing_is_broken_on_death(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return false;
  }
  return tp_flag(thing_tp(t), is_broken_on_death);
}

bool thing_is_undead(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return false;
  }
  return tp_flag(thing_tp(t), is_undead);
}

bool thing_is_wait_on_anim_when_dead(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return false;
  }
  return tp_flag(thing_tp(t), is_wait_on_anim_when_dead);
}

bool thing_is_explosion(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return false;
  }
  return tp_flag(thing_tp(t), is_explosion);
}

bool thing_is_corpse_on_death(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return false;
  }
  return tp_flag(thing_tp(t), is_corpse_on_death);
}

bool thing_is_monst_group_0(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return false;
  }
  return tp_flag(thing_tp(t), is_monst_group_0);
}

bool thing_is_physics_temperature(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return false;
  }
  return tp_flag(thing_tp(t), is_physics_temperature);
}

bool thing_is_unused5(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return false;
  }
  return tp_flag(thing_tp(t), is_unused5);
}

bool thing_is_smoke(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return false;
  }
  return tp_flag(thing_tp(t), is_smoke);
}

bool thing_is_steam(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return false;
  }
  return tp_flag(thing_tp(t), is_steam);
}

bool thing_is_fire(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return false;
  }
  return tp_flag(thing_tp(t), is_fire);
}

bool thing_is_burnable(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return false;
  }
  return tp_flag(thing_tp(t), is_burnable);
}

bool thing_is_dead_on_shoving(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return false;
  }
  return tp_flag(thing_tp(t), is_dead_on_shoving);
}

bool thing_is_able_to_shove(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return false;
  }
  return tp_flag(thing_tp(t), is_able_to_shove);
}

bool thing_is_shovable(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return false;
  }
  return tp_flag(thing_tp(t), is_shovable);
}

bool thing_is_loggable(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return false;
  }
  return tp_flag(thing_tp(t), is_loggable);
}

bool thing_is_crushable(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return false;
  }
  return tp_flag(thing_tp(t), is_crushable);
}

bool thing_is_ethereal(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return false;
  }
  return tp_flag(thing_tp(t), is_ethereal);
}

bool thing_is_unused6(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return false;
  }
  return tp_flag(thing_tp(t), is_unused6);
}

bool thing_is_levitating(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return false;
  }
  return tp_flag(thing_tp(t), is_levitating);
}

bool thing_is_unused7(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return false;
  }
  return tp_flag(thing_tp(t), is_unused7);
}

bool thing_is_unused8(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return false;
  }
  return tp_flag(thing_tp(t), is_unused8);
}

bool thing_is_unused9(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return false;
  }
  return tp_flag(thing_tp(t), is_unused9);
}

bool thing_is_walk_through_walls(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return false;
  }
  return tp_flag(thing_tp(t), is_walk_through_walls);
}

bool thing_is_wall(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return false;
  }
  return tp_flag(thing_tp(t), is_wall);
}

bool thing_is_water(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return false;
  }
  return tp_flag(thing_tp(t), is_water);
}

int thing_value1(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return 0;
  }
  return t->_value1;
}

int thing_value1_set(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return 0;
  }
  return t->_value1 = val;
}

int thing_value1_incr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return 0;
  }
  return t->_value1 += val;
}

int thing_value1_decr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return 0;
  }
  return t->_value1 -= val;
}
int thing_value2(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return 0;
  }
  return t->_value2;
}

int thing_value2_set(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return 0;
  }
  return t->_value2 = val;
}

int thing_value2_incr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return 0;
  }
  return t->_value2 += val;
}

int thing_value2_decr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return 0;
  }
  return t->_value2 -= val;
}
int thing_value3(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return 0;
  }
  return t->_value3;
}

int thing_value3_set(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return 0;
  }
  return t->_value3 = val;
}

int thing_value3_incr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return 0;
  }
  return t->_value3 += val;
}

int thing_value3_decr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return 0;
  }
  return t->_value3 -= val;
}
int thing_value4(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return 0;
  }
  return t->_value4;
}

int thing_value4_set(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return 0;
  }
  return t->_value4 = val;
}

int thing_value4_incr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return 0;
  }
  return t->_value4 += val;
}

int thing_value4_decr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return 0;
  }
  return t->_value4 -= val;
}
int thing_value5(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return 0;
  }
  return t->_value5;
}

int thing_value5_set(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return 0;
  }
  return t->_value5 = val;
}

int thing_value5_incr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return 0;
  }
  return t->_value5 += val;
}

int thing_value5_decr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return 0;
  }
  return t->_value5 -= val;
}
int thing_value6(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return 0;
  }
  return t->_value6;
}

int thing_value6_set(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return 0;
  }
  return t->_value6 = val;
}

int thing_value6_incr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return 0;
  }
  return t->_value6 += val;
}

int thing_value6_decr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return 0;
  }
  return t->_value6 -= val;
}
int thing_value7(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return 0;
  }
  return t->_value7;
}

int thing_value7_set(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return 0;
  }
  return t->_value7 = val;
}

int thing_value7_incr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return 0;
  }
  return t->_value7 += val;
}

int thing_value7_decr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return 0;
  }
  return t->_value7 -= val;
}
int thing_value8(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return 0;
  }
  return t->_value8;
}

int thing_value8_set(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return 0;
  }
  return t->_value8 = val;
}

int thing_value8_incr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return 0;
  }
  return t->_value8 += val;
}

int thing_value8_decr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return 0;
  }
  return t->_value8 -= val;
}
int thing_value9(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return 0;
  }
  return t->_value9;
}

int thing_value9_set(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return 0;
  }
  return t->_value9 = val;
}

int thing_value9_incr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return 0;
  }
  return t->_value9 += val;
}

int thing_value9_decr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return 0;
  }
  return t->_value9 -= val;
}
int thing_value10(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return 0;
  }
  return t->_value10;
}

int thing_value10_set(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return 0;
  }
  return t->_value10 = val;
}

int thing_value10_incr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return 0;
  }
  return t->_value10 += val;
}

int thing_value10_decr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return 0;
  }
  return t->_value10 -= val;
}
int thing_value11(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return 0;
  }
  return t->_value11;
}

int thing_value11_set(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return 0;
  }
  return t->_value11 = val;
}

int thing_value11_incr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return 0;
  }
  return t->_value11 += val;
}

int thing_value11_decr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return 0;
  }
  return t->_value11 -= val;
}
int thing_value12(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return 0;
  }
  return t->_value12;
}

int thing_value12_set(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return 0;
  }
  return t->_value12 = val;
}

int thing_value12_incr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return 0;
  }
  return t->_value12 += val;
}

int thing_value12_decr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return 0;
  }
  return t->_value12 -= val;
}
int thing_value13(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return 0;
  }
  return t->_value13;
}

int thing_value13_set(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return 0;
  }
  return t->_value13 = val;
}

int thing_value13_incr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return 0;
  }
  return t->_value13 += val;
}

int thing_value13_decr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return 0;
  }
  return t->_value13 -= val;
}
int thing_value14(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return 0;
  }
  return t->_value14;
}

int thing_value14_set(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return 0;
  }
  return t->_value14 = val;
}

int thing_value14_incr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return 0;
  }
  return t->_value14 += val;
}

int thing_value14_decr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return 0;
  }
  return t->_value14 -= val;
}
int thing_value15(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return 0;
  }
  return t->_value15;
}

int thing_value15_set(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return 0;
  }
  return t->_value15 = val;
}

int thing_value15_incr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return 0;
  }
  return t->_value15 += val;
}

int thing_value15_decr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return 0;
  }
  return t->_value15 -= val;
}
int thing_value16(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return 0;
  }
  return t->_value16;
}

int thing_value16_set(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return 0;
  }
  return t->_value16 = val;
}

int thing_value16_incr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return 0;
  }
  return t->_value16 += val;
}

int thing_value16_decr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return 0;
  }
  return t->_value16 -= val;
}
int thing_value17(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return 0;
  }
  return t->_value17;
}

int thing_value17_set(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return 0;
  }
  return t->_value17 = val;
}

int thing_value17_incr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return 0;
  }
  return t->_value17 += val;
}

int thing_value17_decr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return 0;
  }
  return t->_value17 -= val;
}
int thing_value18(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return 0;
  }
  return t->_value18;
}

int thing_value18_set(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return 0;
  }
  return t->_value18 = val;
}

int thing_value18_incr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return 0;
  }
  return t->_value18 += val;
}

int thing_value18_decr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return 0;
  }
  return t->_value18 -= val;
}
int thing_value19(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return 0;
  }
  return t->_value19;
}

int thing_value19_set(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return 0;
  }
  return t->_value19 = val;
}

int thing_value19_incr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return 0;
  }
  return t->_value19 += val;
}

int thing_value19_decr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return 0;
  }
  return t->_value19 -= val;
}
int thing_value20(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return 0;
  }
  return t->_value20;
}

int thing_value20_set(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return 0;
  }
  return t->_value20 = val;
}

int thing_value20_incr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return 0;
  }
  return t->_value20 += val;
}

int thing_value20_decr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return 0;
  }
  return t->_value20 -= val;
}
int thing_value21(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return 0;
  }
  return t->_value21;
}

int thing_value21_set(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return 0;
  }
  return t->_value21 = val;
}

int thing_value21_incr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return 0;
  }
  return t->_value21 += val;
}

int thing_value21_decr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return 0;
  }
  return t->_value21 -= val;
}
int thing_value22(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return 0;
  }
  return t->_value22;
}

int thing_value22_set(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return 0;
  }
  return t->_value22 = val;
}

int thing_value22_incr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return 0;
  }
  return t->_value22 += val;
}

int thing_value22_decr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return 0;
  }
  return t->_value22 -= val;
}
int thing_value23(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return 0;
  }
  return t->_value23;
}

int thing_value23_set(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return 0;
  }
  return t->_value23 = val;
}

int thing_value23_incr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return 0;
  }
  return t->_value23 += val;
}

int thing_value23_decr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return 0;
  }
  return t->_value23 -= val;
}
int thing_value24(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return 0;
  }
  return t->_value24;
}

int thing_value24_set(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return 0;
  }
  return t->_value24 = val;
}

int thing_value24_incr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return 0;
  }
  return t->_value24 += val;
}

int thing_value24_decr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return 0;
  }
  return t->_value24 -= val;
}
int thing_value25(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return 0;
  }
  return t->_value25;
}

int thing_value25_set(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return 0;
  }
  return t->_value25 = val;
}

int thing_value25_incr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return 0;
  }
  return t->_value25 += val;
}

int thing_value25_decr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return 0;
  }
  return t->_value25 -= val;
}
int thing_value26(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return 0;
  }
  return t->_value26;
}

int thing_value26_set(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return 0;
  }
  return t->_value26 = val;
}

int thing_value26_incr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return 0;
  }
  return t->_value26 += val;
}

int thing_value26_decr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return 0;
  }
  return t->_value26 -= val;
}
int thing_value27(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return 0;
  }
  return t->_value27;
}

int thing_value27_set(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return 0;
  }
  return t->_value27 = val;
}

int thing_value27_incr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return 0;
  }
  return t->_value27 += val;
}

int thing_value27_decr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return 0;
  }
  return t->_value27 -= val;
}
int thing_value28(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return 0;
  }
  return t->_value28;
}

int thing_value28_set(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return 0;
  }
  return t->_value28 = val;
}

int thing_value28_incr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return 0;
  }
  return t->_value28 += val;
}

int thing_value28_decr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return 0;
  }
  return t->_value28 -= val;
}
int thing_jump_distance(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return 0;
  }
  return t->_jump_distance;
}

int thing_jump_distance_set(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return 0;
  }
  return t->_jump_distance = val;
}

int thing_jump_distance_incr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return 0;
  }
  return t->_jump_distance += val;
}

int thing_jump_distance_decr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return 0;
  }
  return t->_jump_distance -= val;
}

int thing_lifespan(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return 0;
  }
  return t->_lifespan;
}

int thing_lifespan_set(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return 0;
  }
  return t->_lifespan = val;
}

int thing_lifespan_incr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return 0;
  }
  return t->_lifespan += val;
}

int thing_lifespan_decr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return 0;
  }
  return t->_lifespan -= val;
}

int thing_submerged_pct(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
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
    ERR("no thing for %s", __FUNCTION__);
    return 0;
  }
  return t->_submerged_pct = val;
}

int thing_submerged_pct_incr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return 0;
  }
  return t->_submerged_pct += val;
}

int thing_submerged_pct_decr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return 0;
  }
  return t->_submerged_pct -= val;
}

int thing_age(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return 0;
  }
  return t->_age;
}

int thing_age_set(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return 0;
  }
  return t->_age = val;
}

int thing_age_incr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return 0;
  }
  return t->_age += val;
}

int thing_age_decr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return 0;
  }
  return t->_age -= val;
}
