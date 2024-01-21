//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_level_data.hpp"
#include "my_main.hpp"
#include "my_tp.hpp"
#include "my_tps.hpp"

bool templates_init(void)
{
  TRACE_NO_INDENT();

  if (! tp_load_world_mountains()) {
    return false;
  }

  if (! tp_load_world_forest()) {
    return false;
  }

  if (! tp_load_player()) {
    return false;
  }

  if (! tp_load_key()) {
    return false;
  }

  if (! tp_load_dungeon_entrance()) {
    return false;
  }

  if (! tp_load_dungeon_exit()) {
    return false;
  }

  return true;
}
