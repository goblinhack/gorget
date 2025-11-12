//
// Copyright goblinhack@gmail.com
//

#pragma once
#ifndef _MY_THING_TEMPLATE_CALLBACKS_H_
#define _MY_THING_TEMPLATE_CALLBACKS_H_

#include "my_thing.hpp"
#include "my_tp.hpp"
#include <string>

typedef std::string (*thing_description_get_t)(Gamep, Levelsp, Levelp, Thingp me);
void        thing_description_set(Tpp, thing_description_get_t);
std::string thing_description_get(Gamep, Levelsp, Levelp, Thingp me);

typedef std::string (*thing_detail_get_t)(Gamep, Levelsp, Levelp, Thingp me);
void        thing_detail_set(Tpp, thing_detail_get_t);
std::string thing_detail_get(Gamep, Levelsp, Levelp, Thingp me);

typedef bool (*thing_mouse_down_t)(Gamep, Levelsp, Levelp, Thingp me, int x, int y, int button);
void thing_mouse_down_set(Tpp, thing_mouse_down_t);
bool thing_mouse_down(Gamep, Levelsp, Levelp, Thingp me, int x, int y, int button);

typedef void (*thing_on_spawn_t)(Gamep, Levelsp, Levelp, Thingp me);
void thing_on_spawn_set(Tpp, thing_on_spawn_t);
void thing_on_spawn(Gamep, Levelsp, Levelp, Thingp me);

typedef void (*thing_on_level_enter_t)(Gamep, Levelsp, Levelp, Thingp me);
void thing_on_level_enter_set(Tpp, thing_on_level_enter_t);
void thing_on_level_enter(Gamep, Levelsp, Levelp, Thingp me);

typedef void (*thing_on_level_leave_t)(Gamep, Levelsp, Levelp, Thingp me);
void thing_on_level_leave_set(Tpp, thing_on_level_leave_t);
void thing_on_level_leave(Gamep, Levelsp, Levelp, Thingp me);

typedef void (*thing_on_level_populated_t)(Gamep, Levelsp, Levelp, Thingp me);
void thing_on_level_populated_set(Tpp, thing_on_level_populated_t);
void thing_on_level_populated(Gamep, Levelsp, Levelp, Thingp me);

typedef bool (*thing_on_carry_request_t)(Gamep, Levelsp, Levelp, Thingp me, Thingp player_or_monst);
void thing_on_carry_request_set(Tpp, thing_on_carry_request_t);
bool thing_on_carry_request(Gamep, Levelsp, Levelp, Thingp me, Thingp player_or_monst);

typedef bool (*thing_on_drop_request_t)(Gamep, Levelsp, Levelp, Thingp me, Thingp player_or_monst);
void thing_on_drop_request_set(Tpp, thing_on_drop_request_t);
bool thing_on_drop_request(Gamep, Levelsp, Levelp, Thingp me, Thingp player_or_monst);

typedef bool (*thing_on_open_request_t)(Gamep, Levelsp, Levelp, Thingp me, Thingp player_or_monst);
void thing_on_open_request_set(Tpp, thing_on_open_request_t);
bool thing_on_open_request(Gamep, Levelsp, Levelp, Thingp me, Thingp player_or_monst);

typedef bool (*thing_on_close_request_t)(Gamep, Levelsp, Levelp, Thingp me, Thingp player_or_monst);
void thing_on_close_request_set(Tpp, thing_on_close_request_t);
bool thing_on_close_request(Gamep, Levelsp, Levelp, Thingp me, Thingp player_or_monst);

typedef void (*thing_on_tick_idle_t)(Gamep, Levelsp, Levelp, Thingp me);
void thing_on_tick_idle_set(Tpp, thing_on_tick_idle_t);
void thing_on_tick_idle(Gamep, Levelsp, Levelp, Thingp me);

typedef void (*thing_on_tick_begin_t)(Gamep, Levelsp, Levelp, Thingp me);
void thing_on_tick_begin_set(Tpp, thing_on_tick_begin_t);
void thing_on_tick_begin(Gamep, Levelsp, Levelp, Thingp me);

typedef void (*thing_on_tick_end_t)(Gamep, Levelsp, Levelp, Thingp me);
void thing_on_tick_end_set(Tpp, thing_on_tick_end_t);
void thing_on_tick_end(Gamep, Levelsp, Levelp, Thingp me);

typedef void (*thing_on_death_t)(Gamep, Levelsp, Levelp, Thingp me, ThingEvent &);
void thing_on_death_set(Tpp, thing_on_death_t);
void thing_on_death(Gamep, Levelsp, Levelp, Thingp me, ThingEvent &);

typedef void (*thing_on_moved_t)(Gamep, Levelsp, Levelp, Thingp me);
void thing_on_moved_set(Tpp, thing_on_moved_t);
void thing_on_moved(Gamep, Levelsp, Levelp, Thingp me);

typedef void (*thing_on_teleported_t)(Gamep, Levelsp, Levelp, Thingp me);
void thing_on_teleported_set(Tpp, thing_on_teleported_t);
void thing_on_teleported(Gamep, Levelsp, Levelp, Thingp me);

typedef void (*thing_on_shoved_t)(Gamep, Levelsp, Levelp, Thingp me, Thingp shover);
void thing_on_shoved_set(Tpp, thing_on_shoved_t);
void thing_on_shoved(Gamep, Levelsp, Levelp, Thingp me, Thingp shover);

typedef void (*thing_on_jump_begin_t)(Gamep, Levelsp, Levelp, Thingp me);
void thing_on_jump_begin_set(Tpp, thing_on_jump_begin_t);
void thing_on_jump_begin(Gamep, Levelsp, Levelp, Thingp me);

typedef void (*thing_on_jump_end_t)(Gamep, Levelsp, Levelp, Thingp me);
void thing_on_jump_end_set(Tpp, thing_on_jump_end_t);
void thing_on_jump_end(Gamep, Levelsp, Levelp, Thingp me);

typedef void (*thing_on_fall_begin_t)(Gamep, Levelsp, Levelp, Thingp me);
void thing_on_fall_begin_set(Tpp, thing_on_fall_begin_t);
void thing_on_fall_begin(Gamep, Levelsp, Levelp, Thingp me);

typedef void (*thing_on_fall_end_t)(Gamep, Levelsp, Levelp, Thingp me);
void thing_on_fall_end_set(Tpp, thing_on_fall_end_t);
void thing_on_fall_end(Gamep, Levelsp, Levelp, Thingp me);

#endif
