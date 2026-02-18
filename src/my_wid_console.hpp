//
// Copyright goblinhack@gmail.com
//


void wid_console_fini(Gamep g);
bool wid_console_init(Gamep g);
void wid_console_log(std::string s);
void wid_console_raise(Gamep g);
void wid_console_flush(Gamep g);

#include "my_wid.hpp"

//
// Global widgets.
//
extern Widp wid_console_input_line;
extern Widp wid_console_window;
extern Widp wid_console_container;

bool wid_console_receive_input(Gamep g, Widp w, const SDL_Keysym *key);

std::vector< std::string > wid_console_serialize();

void wid_console_deserialize(std::vector< std::string > r);
