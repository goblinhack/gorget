//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_globals.hpp"
#include "my_main.hpp"
#include "my_thing_inlines.hpp"
#include "my_tp_class.hpp"
#include "my_ui.hpp"

void thing_description_set(Tpp tp, thing_description_get_t callback)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("No thing template pointer set");
    return;
  }
  tp->description_get = callback;
}

std::string thing_description_get(Gamep g, Levelsp v, Levelp l, Thingp me)
{
  TRACE_NO_INDENT();
  auto tp = thing_tp(me);
  if (! tp) {
    ERR("No thing template pointer set");
    return "<no description>";
  }
  if (! tp->description_get) {
    return "";
  }
  return tp->description_get(g, v, l, me);
}

void thing_detail_set(Tpp tp, thing_detail_get_t callback)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("No thing template pointer set");
    return;
  }
  tp->detail_get = callback;
}

std::string thing_detail_get(Gamep g, Levelsp v, Levelp l, Thingp me)
{
  TRACE_NO_INDENT();
  auto tp = thing_tp(me);
  if (! tp) {
    ERR("No thing template pointer set");
    return "<no detail>";
  }
  if (! tp->detail_get) {
    return "";
  }
  return tp->detail_get(g, v, l, me);
}

void thing_mouse_down_set(Tpp tp, thing_mouse_down_t callback)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("No thing template pointer set");
    return;
  }
  tp->mouse_down = callback;
}

bool thing_mouse_down(Gamep g, Levelsp v, Levelp l, Thingp me, int x, int y, int button)
{
  TRACE_NO_INDENT();
  auto tp = thing_tp(me);
  if (! tp) {
    ERR("No thing template pointer set");
    return false;
  }
  if (! tp->mouse_down) {
    return false;
  }
  return tp->mouse_down(g, v, l, me, x, y, button);
}

void thing_on_tick_idle_set(Tpp tp, thing_on_tick_idle_t callback)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("No thing template pointer set");
    return;
  }
  tp->tick_idle = callback;
}

void thing_on_tick_idle(Gamep g, Levelsp v, Levelp l, Thingp me)
{
  TRACE_NO_INDENT();
  auto tp = thing_tp(me);
  if (! tp) {
    ERR("No thing template pointer set");
    return;
  }
  if (! tp->tick_idle) {
    return;
  }
  return tp->tick_idle(g, v, l, me);
}

void thing_on_tick_begin_set(Tpp tp, thing_on_tick_begin_t callback)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("No thing template pointer set");
    return;
  }
  tp->tick_begin = callback;
}

void thing_on_tick_begin(Gamep g, Levelsp v, Levelp l, Thingp me)
{
  TRACE_NO_INDENT();
  auto tp = thing_tp(me);
  if (! tp) {
    ERR("No thing template pointer set");
    return;
  }
  if (! tp->tick_begin) {
    return;
  }
  return tp->tick_begin(g, v, l, me);
}

void thing_on_tick_end_set(Tpp tp, thing_on_tick_end_t callback)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("No thing template pointer set");
    return;
  }
  tp->tick_end = callback;
}

void thing_on_tick_end(Gamep g, Levelsp v, Levelp l, Thingp me)
{
  TRACE_NO_INDENT();
  auto tp = thing_tp(me);
  if (! tp) {
    ERR("No thing template pointer set");
    return;
  }
  if (! tp->tick_end) {
    return;
  }
  return tp->tick_end(g, v, l, me);
}

void thing_on_spawn_set(Tpp tp, thing_on_spawn_t callback)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("No thing template pointer set");
    return;
  }
  tp->on_spawn = callback;
}

void thing_on_spawn(Gamep g, Levelsp v, Levelp l, Thingp me)
{
  TRACE_NO_INDENT();
  auto tp = thing_tp(me);
  if (! tp) {
    ERR("No thing template pointer set");
    return;
  }
  if (! tp->on_spawn) {
    return;
  }
  return tp->on_spawn(g, v, l, me);
}

void thing_on_level_populated_set(Tpp tp, thing_on_level_populated_t callback)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("No thing template pointer set");
    return;
  }
  tp->on_level_populated = callback;
}

void thing_on_level_populated(Gamep g, Levelsp v, Levelp l, Thingp me)
{
  TRACE_NO_INDENT();
  auto tp = thing_tp(me);
  if (! tp) {
    ERR("No thing template pointer set");
    return;
  }
  if (! tp->on_level_populated) {
    return;
  }
  return tp->on_level_populated(g, v, l, me);
}

void thing_on_level_enter_set(Tpp tp, thing_on_level_enter_t callback)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("No thing template pointer set");
    return;
  }
  tp->on_level_enter = callback;
}

void thing_on_level_enter(Gamep g, Levelsp v, Levelp l, Thingp me)
{
  TRACE_NO_INDENT();
  auto tp = thing_tp(me);
  if (! tp) {
    ERR("No thing template pointer set");
    return;
  }
  if (! tp->on_level_enter) {
    return;
  }
  return tp->on_level_enter(g, v, l, me);
}

void thing_on_level_leave_set(Tpp tp, thing_on_level_leave_t callback)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("No thing template pointer set");
    return;
  }
  tp->on_level_leave = callback;
}

void thing_on_level_leave(Gamep g, Levelsp v, Levelp l, Thingp me)
{
  TRACE_NO_INDENT();
  auto tp = thing_tp(me);
  if (! tp) {
    ERR("No thing template pointer set");
    return;
  }
  if (! tp->on_level_leave) {
    return;
  }
  return tp->on_level_leave(g, v, l, me);
}

void thing_on_open_request_set(Tpp tp, thing_on_open_request_t callback)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("No thing template pointer set");
    return;
  }
  tp->on_open_request = callback;
}

bool thing_on_open_request(Gamep g, Levelsp v, Levelp l, Thingp me, Thingp player_or_monst)
{
  TRACE_NO_INDENT();
  auto tp = thing_tp(me);
  if (! tp) {
    ERR("No thing template pointer set");
    return false;
  }
  if (! tp->on_open_request) {
    //
    // Assume success
    //
    return true;
  }
  if (! thing_is_player(player_or_monst) && ! thing_is_monst(player_or_monst)) {
    THING_ERR(player_or_monst, "unexpected thing for %s", __FUNCTION__);
    return false;
  }
  return tp->on_open_request(g, v, l, me, player_or_monst);
}

void thing_on_close_request_set(Tpp tp, thing_on_close_request_t callback)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("No thing template pointer set");
    return;
  }
  tp->on_close_request = callback;
}

bool thing_on_close_request(Gamep g, Levelsp v, Levelp l, Thingp me, Thingp player_or_monst)
{
  TRACE_NO_INDENT();
  auto tp = thing_tp(me);
  if (! tp) {
    ERR("No thing template pointer set");
    return false;
  }
  if (! tp->on_close_request) {
    //
    // Assume success
    //
    return true;
  }
  if (! thing_is_player(player_or_monst) && ! thing_is_monst(player_or_monst)) {
    THING_ERR(player_or_monst, "unexpected thing for %s", __FUNCTION__);
    return false;
  }
  return tp->on_close_request(g, v, l, me, player_or_monst);
}

void thing_on_carry_request_set(Tpp tp, thing_on_carry_request_t callback)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("No thing template pointer set");
    return;
  }
  tp->on_carry_request = callback;
}

bool thing_on_carry_request(Gamep g, Levelsp v, Levelp l, Thingp me, Thingp player_or_monst)
{
  TRACE_NO_INDENT();
  auto tp = thing_tp(me);
  if (! tp) {
    ERR("No thing template pointer set");
    return false;
  }
  if (! tp->on_carry_request) {
    //
    // Assume success
    //
    return true;
  }
  if (! thing_is_player(player_or_monst) && ! thing_is_monst(player_or_monst)) {
    THING_ERR(player_or_monst, "unexpected thing for %s", __FUNCTION__);
    return false;
  }
  return tp->on_carry_request(g, v, l, me, player_or_monst);
}

void thing_on_drop_request_set(Tpp tp, thing_on_drop_request_t callback)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("No thing template pointer set");
    return;
  }
  tp->on_drop_request = callback;
}

bool thing_on_drop_request(Gamep g, Levelsp v, Levelp l, Thingp me, Thingp player_or_monst)
{
  TRACE_NO_INDENT();
  auto tp = thing_tp(me);
  if (! tp) {
    ERR("No thing template pointer set");
    return false;
  }
  if (! tp->on_drop_request) {
    //
    // Assume success
    //
    return true;
  }
  if (! thing_is_player(player_or_monst) && ! thing_is_monst(player_or_monst)) {
    THING_ERR(player_or_monst, "unexpected thing for %s", __FUNCTION__);
    return false;
  }
  return tp->on_drop_request(g, v, l, me, player_or_monst);
}

void thing_on_death_set(Tpp tp, thing_on_death_t callback)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("No thing template pointer set");
    return;
  }
  tp->on_death = callback;
}

void thing_on_death(Gamep g, Levelsp v, Levelp l, Thingp me, ThingEvent &e)
{
  TRACE_NO_INDENT();
  auto tp = thing_tp(me);
  if (! tp) {
    ERR("No thing template pointer set");
    return;
  }
  if (! tp->on_death) {
    return;
  }
  return tp->on_death(g, v, l, me, e);
}

void thing_on_moved_set(Tpp tp, thing_on_moved_t callback)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("No thing template pointer set");
    return;
  }
  tp->on_moved = callback;
}

void thing_on_moved(Gamep g, Levelsp v, Levelp l, Thingp me)
{
  TRACE_NO_INDENT();
  auto tp = thing_tp(me);
  if (! tp) {
    ERR("No thing template pointer set");
    return;
  }
  if (! tp->on_moved) {
    return;
  }
  return tp->on_moved(g, v, l, me);
}

void thing_on_teleported_set(Tpp tp, thing_on_teleported_t callback)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("No thing template pointer set");
    return;
  }
  tp->on_teleported = callback;
}

void thing_on_teleported(Gamep g, Levelsp v, Levelp l, Thingp me)
{
  TRACE_NO_INDENT();
  auto tp = thing_tp(me);
  if (! tp) {
    ERR("No thing template pointer set");
    return;
  }
  if (! tp->on_teleported) {
    return;
  }
  return tp->on_teleported(g, v, l, me);
}

void thing_on_jump_begin_set(Tpp tp, thing_on_jump_begin_t callback)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("No thing template pointer set");
    return;
  }
  tp->on_jump_begin = callback;
}

void thing_on_jump_begin(Gamep g, Levelsp v, Levelp l, Thingp me)
{
  TRACE_NO_INDENT();
  auto tp = thing_tp(me);
  if (! tp) {
    ERR("No thing template pointer set");
    return;
  }
  if (! tp->on_jump_begin) {
    return;
  }
  return tp->on_jump_begin(g, v, l, me);
}

void thing_on_jump_end_set(Tpp tp, thing_on_jump_end_t callback)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("No thing template pointer set");
    return;
  }
  tp->on_jump_end = callback;
}

void thing_on_jump_end(Gamep g, Levelsp v, Levelp l, Thingp me)
{
  TRACE_NO_INDENT();
  auto tp = thing_tp(me);
  if (! tp) {
    ERR("No thing template pointer set");
    return;
  }
  if (! tp->on_jump_end) {
    return;
  }
  return tp->on_jump_end(g, v, l, me);
}

void thing_on_shoved_set(Tpp tp, thing_on_shoved_t callback)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("No thing template pointer set");
    return;
  }
  tp->on_shoved = callback;
}

void thing_on_shoved(Gamep g, Levelsp v, Levelp l, Thingp me, Thingp player_or_monst)
{
  TRACE_NO_INDENT();
  auto tp = thing_tp(me);
  if (! tp) {
    ERR("No thing template pointer set");
    return;
  }
  if (! tp->on_shoved) {
    return;
  }
  if (! thing_is_player(player_or_monst) && ! thing_is_monst(player_or_monst)) {
    THING_ERR(player_or_monst, "unexpected thing for %s", __FUNCTION__);
    return;
  }
  return tp->on_shoved(g, v, l, me, player_or_monst);
}

void thing_on_fall_begin_set(Tpp tp, thing_on_fall_begin_t callback)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("No thing template pointer set");
    return;
  }
  tp->on_fall_begin = callback;
}

void thing_on_fall_begin(Gamep g, Levelsp v, Levelp l, Thingp me)
{
  TRACE_NO_INDENT();
  auto tp = thing_tp(me);
  if (! tp) {
    ERR("No thing template pointer set");
    return;
  }
  if (! tp->on_fall_begin) {
    return;
  }
  return tp->on_fall_begin(g, v, l, me);
}

void thing_on_fall_end_set(Tpp tp, thing_on_fall_end_t callback)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("No thing template pointer set");
    return;
  }
  tp->on_fall_end = callback;
}

void thing_on_fall_end(Gamep g, Levelsp v, Levelp l, Thingp me)
{
  TRACE_NO_INDENT();
  auto tp = thing_tp(me);
  if (! tp) {
    ERR("No thing template pointer set");
    return;
  }

  if (! tp->on_fall_end) {
    return;
  }

  return tp->on_fall_end(g, v, l, me);
}

void thing_display_get_tile_info_set(Tpp tp, thing_display_get_tile_info_t callback)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("No thing template pointer set");
    return;
  }
  tp->display_get_tile_info = callback;
}

Tilep thing_display_get_tile_info(Gamep g, Levelsp v, Levelp l, spoint p, Tpp tp, Thingp t_maybe_null)
{
  TRACE_NO_INDENT();
  if (! tp) {
    return nullptr;
  }
  if (! tp->display_get_tile_info) {
    return nullptr;
  }
  return tp->display_get_tile_info(g, v, l, p, tp, t_maybe_null);
}
