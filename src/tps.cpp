//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_level_data.hpp"
#include "my_tps.hpp"

bool templates_init(void)
{
  TRACE_NO_INDENT();

  if (! tp_load_player()) {
    return false;
  }

  if (! tp_load_key()) {
    return false;
  }

  if (! tp_load_dungeon_wall()) {
    return false;
  }

  if (! tp_load_dungeon_floor()) {
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
