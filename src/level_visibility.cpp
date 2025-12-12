//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_level.hpp"
#include "my_main.hpp"
#include "my_thing.hpp"

//
// Update lighting and minimaps when things change substantially, like a teleport, or level change
//
void level_update_visibility(Gamep g, Levelsp v, Levelp l)
{
  TRACE_NO_INDENT();

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

  bool update_visibiliy = false;

  if (l->tick_in_progress) {
    //
    // Limit the updates unless asked (due to a moving thing likely) as this path
    // is called many times per second.
    //
    if (l->request_to_update_visibility) {
      l->request_to_update_visibility = false;
      update_visibiliy                = true;
    }
  } else {
    //
    // Some event, like tick end or teleport occurred.
    //
    update_visibiliy = true;
  }

  if (! update_visibiliy) {
    return;
  }

  //
  // We only care about pixel moves.
  //
  level_light_calculate_all(g, v, l);

  //
  // Update minimaps
  //
  level_minimaps_update(g, v, l);
}
