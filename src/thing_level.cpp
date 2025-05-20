//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_game.hpp"
#include "my_level.hpp"
#include "my_main.hpp"
#include "my_minimal.hpp"
#include "my_tile.hpp"
#include "my_tp.hpp"

#include <string.h>

//
// Handle common level exit interactions
//
static void thing_level_leave(Gamep g, Levelsp v, Levelp l, Thingp t)
{
  TRACE_NO_INDENT();

  level_select_update_grid_tiles(g, v);
  level_cursor_path_reset(g, v, l);
  level_change(g, v, LEVEL_SELECT_ID);
}

//
// Handle level exit interactions
//
void thing_level_reached_exit(Gamep g, Levelsp v, Levelp l, Thingp t)
{
  TRACE_NO_INDENT();

  l->completed = true;
  thing_level_leave(g, v, l, t);
}

//
// Handle level entrance interactions
//
void thing_level_reached_entrance(Gamep g, Levelsp v, Levelp l, Thingp t)
{
  TRACE_NO_INDENT();

  thing_level_leave(g, v, l, t);
}

//
// Move the thing immediately to the new level entrance
//
void thing_level_warp_to_entrance(Gamep g, Levelsp v, Levelp new_level, Thingp t)
{
  TRACE_NO_INDENT();

  if (! t) {
    return;
  }

  auto old_level = game_level_get(g, v, t->level_num);
  if (old_level == new_level) {
    return;
  }

  //
  // Leave the old level
  //
  thing_pop(g, v, t);

  //
  // Join the level, but at the old position
  //
  thing_push(g, v, new_level, t);

  //
  // Now move to the correct location
  //
  thing_warp_to(g, v, new_level, t, new_level->entrance);
}
