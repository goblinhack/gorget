//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_game.hpp"
#include "my_level.hpp"
#include "my_tile.hpp"

void Level::display(void)
{
  TRACE_NO_INDENT();

  display_dungeon();
}
