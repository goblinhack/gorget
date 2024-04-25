//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_level.hpp"

Level::Level()
{
  TRACE_NO_INDENT();

  data = level_data_constructor();

  dungeon_create_and_place();
  assign_tiles();
  thing_player_create_and_place();
  scroll_warp_to_player();
}

Level::~Level()
{
  TRACE_NO_INDENT();

  auto d = data;
  if (d) {
    data = nullptr;
    level_data_destructor(d);
  }
}
