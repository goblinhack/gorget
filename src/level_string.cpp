//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_game.hpp"
#include "my_globals.hpp"
#include "my_level.hpp"
#include "my_main.hpp"
#include "my_sprintf.hpp"

std::string to_string(Gamep g, Levelp l)
{
  TRACE_NO_INDENT();

  if (! l) {
    ERR("No level pointer set");
    return "<no level>";
  }

  return (string_sprintf("L%u%s",
                         /* newline */ l->level_num + 1,
                         /* newline */ l->is_current_level ? "/curr" : ""));
}
