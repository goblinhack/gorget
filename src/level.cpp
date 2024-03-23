//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_level.hpp"

Level::Level()
{
  TRACE_NO_INDENT();

  data = level_data_constructor();

  dungeon_create_and_place();
  assign_tiles();
  player_map_center();
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
