//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_game.hpp"
#include "my_level.hpp"
#include "my_main.hpp"
#include "my_minimal.hpp"
#include "my_random.hpp"
#include "my_tile.hpp"
#include "my_tp.hpp"

//
// Initiate the death process
//
void thing_dead(Gamep g, Levelsp v, Levelp l, Thingp it, Thingp me, std::string reason)
{
  TRACE_NO_INDENT();

  if (thing_is_dead(me)) {
    return;
  }

  //
  // Log the reason of demise?
  //
  if (thing_is_loggable(me)) {
    if (reason.empty()) {
      THING_LOG(me, "dead");
    } else {
      THING_LOG(me, "dead, reason: %s", reason.c_str());
    }
  }

  thing_is_dead_set(g, v, l, me);
}

//
// Complete the death process
//
void thing_is_dead_handle(Gamep g, Levelsp v, Levelp l, Thingp t)
{
  TRACE_NO_INDENT();

  //
  // Update the animation, for example, flattened grass
  //
  t->anim_type = THING_ANIM_DEAD;
  thing_anim_init(g, v, l, t);

  //
  // Stop it moving
  //
  thing_move_finish(g, v, l, t);
}
