//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_game.hpp"
#include "my_level.hpp"
#include "my_tile.hpp"

void level_display(Levelp l)
{
  TRACE_NO_INDENT();

  level_display_dungeon(l);
}
