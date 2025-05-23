//
// Copyright goblinhack@gmail.com
//

#pragma once

void wid_console_fini(Gamep);
bool wid_console_init(Gamep);
void wid_console_log(std::string s);
void wid_console_hello(Gamep);

#include "my_wid.hpp"

//
// Global widgets.
//
extern Widp wid_console_input_line;
extern Widp wid_console_window;
extern Widp wid_console_container;

bool wid_console_receive_input(Gamep g, Widp w, const SDL_Keysym *key);

std::vector< std::string > wid_console_serialize(void);

void wid_console_deserialize(std::vector< std::string > r);
