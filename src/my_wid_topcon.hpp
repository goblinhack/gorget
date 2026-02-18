//
// Copyright goblinhack@gmail.com
//


void wid_topcon_fini(Gamep g);
bool wid_topcon_init(Gamep g);
void wid_topcon_log(std::string s);
void wid_topcon_flush(Gamep g);

#include "my_wid.hpp"

//
// Global widgets.
//
extern Widp wid_topcon_input_line;
extern Widp wid_topcon_window;
extern Widp wid_topcon_container;
