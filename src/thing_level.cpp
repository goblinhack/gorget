//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_game.hpp"
#include "my_globals.hpp"
#include "my_main.hpp"
#include "my_thing_inlines.hpp"

//
// Return the level of the thing
//
Levelp thing_level(Gamep g, Levelsp v, Thingp t)
{
  TRACE_NO_INDENT();

  auto o = thing_find(g, v, t->id);
  if (t != o) {
    DIE("Thing mismatch found for id, 08%" PRIx32 "", t->id);
  }

  return game_level_get(g, v, t->level_num);
}

bool thing_on_same_level_as_player(Gamep g, Levelsp v, Thingp t)
{
  TRACE_NO_INDENT();

  auto player = thing_player(g);
  if (! player) {
    return false;
  }

  Levelp player_level = thing_player_level(g);
  if (! player_level) {
    return false;
  }

  auto t_level = game_level_get(g, v, t->level_num);
  if (t_level != player_level) {
    return false;
  }

  return true;
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
  // Now move to the correct location
  //
  thing_warp_to(g, v, new_level, t, new_level->entrance);
}

//
// Move the thing immediately to the new level exit
//
void thing_level_warp_to_exit(Gamep g, Levelsp v, Levelp new_level, Thingp t)
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
  // Now move to the correct location
  //
  thing_warp_to(g, v, new_level, t, new_level->exit);
}
