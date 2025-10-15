//
// Copyright goblinhack@gmail.com
//

#pragma once
#ifndef _MY_LIGHT_H_
#define _MY_LIGHT_H_

#include "my_color_defs.hpp"
#include "my_game.hpp"
#include "my_level.hpp"

void player_light_render(Gamep g, Levelsp v, Levelp l, int fbo);
void player_light_fini(void);

#endif // LIGHT_H_
