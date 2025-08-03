//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_game.hpp"
#include "my_level.hpp"
#include "my_string.hpp"
#include "my_ui.hpp"
#include "my_wids.hpp"

//
// Do actions upon burning
//
void thing_is_burning_handle(Gamep g, Levelsp v, Levelp l, Thingp t)
{
  TRACE_NO_INDENT();

  if (thing_is_player(t)) {
    TOPCON(UI_IMPORTANT_FMT_STR "You are burning!" UI_RESET_FMT);
  }
}
