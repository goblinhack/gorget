//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_level.hpp"
#include "my_thing.hpp"

//
// Update lighting and minimaps when things change substantially, like a teleport, or level change
//
void level_update_visibility(Gamep g, Levelsp v, Levelp l)
{
  TRACE_NO_INDENT();

  bool do_something = false;

  auto player = thing_player(g);
  if (! player) {
    return;
  }

  if (! g || ! v || ! l) {
    return;
  }

  //
  // If the player is not on the level being lit, then nothing to do
  //
  if (l->level_num != player->level_num) {
    return;
  }

  if (l->tick_in_progress) {
    //
    // Limit the updates as tick interpolation occurs many times per second.
    //
    if (thing_pix_at(player) == player->prev_pix_at) {
      do_something = true;
    }
  } else {
    //
    // Some event, like tick end or teleport occurred.
    //
    do_something = true;
  }

  if (! do_something) {
    return;
  }

  //
  // We only care about pixel moves.
  //

  //
  // First lighting update
  //
  level_light_calcuate_all(g, v, l);

  //
  // Update minimaps
  //
  level_minimaps_update(g, v, l, false);
}
