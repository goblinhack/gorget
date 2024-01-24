//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_level.hpp"
// REMOVED #include "my_level_ph1.hpp"
// REMOVED #include "my_level_ph2.hpp"
// REMOVED #include "my_level_ph3.hpp"
// REMOVED #include "my_level_ph4.hpp"
// REMOVED #include "my_ptrcheck.hpp"

Level::Level()
{
  TRACE_NO_INDENT();

  data = level_data_constructor();

  world_create_and_place();
  assign_tiles();
  player_create_and_place();
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
