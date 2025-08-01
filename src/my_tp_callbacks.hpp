//
// Copyright goblinhack@gmail.com
//

#pragma once
#ifndef _MY_THING_TEMPLATE_CALLBACKS_H_
#define _MY_THING_TEMPLATE_CALLBACKS_H_

#include "my_thing.hpp"
#include "my_tp.hpp"
#include <string>

typedef std::string (*tp_description_get_t)(Gamep, Levelsp, Levelp, Thingp me);
void        tp_description_set(Tpp, tp_description_get_t);
std::string tp_description_get(Gamep g, Levelsp v, Levelp l, Thingp me);

typedef void (*tp_tick_idle_t)(Gamep, Levelsp, Levelp, Thingp me);
void tp_tick_idle_set(Tpp, tp_tick_idle_t);
void tp_tick_idle(Gamep g, Levelsp v, Levelp l, Thingp me);

typedef void (*tp_tick_begin_t)(Gamep, Levelsp, Levelp, Thingp me);
void tp_tick_begin_set(Tpp, tp_tick_begin_t);
void tp_tick_begin(Gamep g, Levelsp v, Levelp l, Thingp me);

typedef void (*tp_tick_end_t)(Gamep, Levelsp, Levelp, Thingp me);
void tp_tick_end_set(Tpp, tp_tick_end_t);
void tp_tick_end(Gamep g, Levelsp v, Levelp l, Thingp me);

typedef void (*tp_on_death_t)(Gamep, Levelsp, Levelp, Thingp me, ThingEvent &);
void tp_on_death_set(Tpp, tp_on_death_t);
void tp_on_death(Gamep g, Levelsp v, Levelp l, Thingp me, ThingEvent &);

typedef void (*tp_on_shoved_t)(Gamep, Levelsp, Levelp, Thingp me, Thingp shover);
void tp_on_shoved_set(Tpp, tp_on_shoved_t);
void tp_on_shoved(Gamep g, Levelsp v, Levelp l, Thingp me, Thingp shover);

typedef void (*tp_on_over_chasm_t)(Gamep, Levelsp, Levelp, Thingp me);
void tp_on_over_chasm_set(Tpp, tp_on_over_chasm_t);
void tp_on_over_chasm(Gamep g, Levelsp v, Levelp l, Thingp me);

#endif
