//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_game.hpp"
#include "my_level.hpp"
#include "my_main.hpp"
#include "my_thing.hpp"

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
  return t->_health = val;
}

int thing_health_incr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return 0;
  }
  return t->_health += val;
}

int thing_health_decr(Gamep g, Levelsp v, Levelp l, Thingp t, int val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return 0;
  }
  return t->_health -= val;
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
  thing_is_dead_handle(g, v, l, t);
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
  t->_is_moving = val;
}

bool thing_is_able_to_walk_through_walls(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return false;
  }
  return tp_flag(thing_tp(t), is_able_to_walk_through_walls);
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

bool thing_is_animated_same_first_tile(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return false;
  }
  return tp_flag(thing_tp(t), is_animated_same_first_tile);
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

bool thing_is_monst1(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return false;
  }
  return tp_flag(thing_tp(t), is_monst1);
}

bool thing_is_monst2(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return false;
  }
  return tp_flag(thing_tp(t), is_monst2);
}

bool thing_is_obstacle_block_or_door(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return false;
  }
  return tp_flag(thing_tp(t), is_obstacle_block_or_door);
}

bool thing_is_obstacle_block(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return false;
  }
  return tp_flag(thing_tp(t), is_obstacle_block);
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

bool thing_is_treasure1(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return false;
  }
  return tp_flag(thing_tp(t), is_treasure1);
}

bool thing_is_treasure2(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return false;
  }
  return tp_flag(thing_tp(t), is_treasure2);
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

bool thing_is_unused26(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return false;
  }
  return tp_flag(thing_tp(t), is_unused26);
}

bool thing_is_unused27(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return false;
  }
  return tp_flag(thing_tp(t), is_unused27);
}

bool thing_is_unused28(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return false;
  }
  return tp_flag(thing_tp(t), is_unused28);
}

bool thing_is_unused29(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return false;
  }
  return tp_flag(thing_tp(t), is_unused29);
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

bool thing_is_unused30(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return false;
  }
  return tp_flag(thing_tp(t), is_unused30);
}

bool thing_is_unused31(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return false;
  }
  return tp_flag(thing_tp(t), is_unused31);
}

bool thing_is_unused32(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return false;
  }
  return tp_flag(thing_tp(t), is_unused32);
}

bool thing_is_unused33(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return false;
  }
  return tp_flag(thing_tp(t), is_unused33);
}

bool thing_is_unused34(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return false;
  }
  return tp_flag(thing_tp(t), is_unused34);
}

bool thing_is_unused35(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return false;
  }
  return tp_flag(thing_tp(t), is_unused35);
}

bool thing_is_unused36(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return false;
  }
  return tp_flag(thing_tp(t), is_unused36);
}

bool thing_is_unused37(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return false;
  }
  return tp_flag(thing_tp(t), is_unused37);
}

bool thing_is_unused38(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return false;
  }
  return tp_flag(thing_tp(t), is_unused38);
}

bool thing_is_unused39(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return false;
  }
  return tp_flag(thing_tp(t), is_unused39);
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

bool thing_is_unused40(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return false;
  }
  return tp_flag(thing_tp(t), is_unused40);
}

bool thing_is_unused41(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return false;
  }
  return tp_flag(thing_tp(t), is_unused41);
}

bool thing_is_unused42(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return false;
  }
  return tp_flag(thing_tp(t), is_unused42);
}

bool thing_is_unused43(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return false;
  }
  return tp_flag(thing_tp(t), is_unused43);
}

bool thing_is_unused44(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return false;
  }
  return tp_flag(thing_tp(t), is_unused44);
}

bool thing_is_unused45(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return false;
  }
  return tp_flag(thing_tp(t), is_unused45);
}

bool thing_is_unused46(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return false;
  }
  return tp_flag(thing_tp(t), is_unused46);
}

bool thing_is_unused47(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return false;
  }
  return tp_flag(thing_tp(t), is_unused47);
}

bool thing_is_unused48(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return false;
  }
  return tp_flag(thing_tp(t), is_unused48);
}

bool thing_is_able_to_change_temperature(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return false;
  }
  return tp_flag(thing_tp(t), is_able_to_change_temperature);
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

bool thing_is_crushable_underfoot(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return false;
  }
  return tp_flag(thing_tp(t), is_crushable_underfoot);
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
