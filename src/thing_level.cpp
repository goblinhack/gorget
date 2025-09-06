//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_game.hpp"
#include "my_level.hpp"

//
// Return the level of the thing
//
Levelp thing_level(Gamep g, Levelsp v, Thingp t)
{
  TRACE_NO_INDENT();

  auto o = thing_find(g, v, t->id);
  if (t != o) {
    DIE("Thing mismatch found for id, %" PRIx32 "", t->id);
  }

  return game_level_get(g, v, t->level_num);
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
