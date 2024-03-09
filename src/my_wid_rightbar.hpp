//
// Copyright Neil McGill, goblinhack@gmail.com
//

#pragma once

void wid_rightbar_fini(void);
bool wid_rightbar_init(void);
bool wid_rightbar_ascii_create(void);

#include "my_wid.hpp"

//
// Global widgets.
//
extern Widp wid_rightbar_window;
extern Widp wid_map_mini;
extern Widp wid_rightbar;

extern bool is_mouse_over_rightbar(void);
