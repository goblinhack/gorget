//
// Copyright goblinhack@gmail.com
//

#pragma once
#ifndef _MY_THING_TEMPLATE_CALLBACKS_H_
#define _MY_THING_TEMPLATE_CALLBACKS_H_

#include "my_tp.hpp"
#include <string>

typedef std::string (*tp_description_get_t)(Tpp, Thingp me, Thingp owner, point at);
void        tp_description_set(Tpp, tp_description_get_t);
std::string tp_description_get(Tpp, Thingp me, Thingp owner, point at);

#endif
