//
// Copyright goblinhack@gmail.com
//

#pragma once
#ifndef _MY_THING_TEMPLATE_CALLBACKS_H_
#define _MY_THING_TEMPLATE_CALLBACKS_H_

#include "my_tp.hpp"
#include <string>

typedef std::string (*tp_description_get_t)(Gamep, Levelsp, Levelp, Thingp me, Thingp owner, spoint at);
void        tp_description_set(Tpp, tp_description_get_t);
std::string tp_description_get(Gamep g, Levelsp v, Levelp l, Thingp me, Thingp owner, spoint at);

#endif
