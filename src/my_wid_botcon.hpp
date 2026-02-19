//
// Copyright goblinhack@gmail.com
//

#ifndef _MY_WID_BOTCON_HPP
#define _MY_WID_BOTCON_HPP

void wid_botcon_fini(Gamep g);
bool wid_botcon_init(Gamep g);
void wid_botcon_log(std::string s);
void wid_botcon_flush(Gamep g);

#include "my_wid.hpp"

//
// Global widgets.
//
extern Widp wid_botcon_input_line;
extern Widp wid_botcon_window;
extern Widp wid_botcon_container;

#endif
