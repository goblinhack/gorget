//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_level.hpp"
#include "my_thing.hpp"
#include "my_thing_callbacks.hpp"
#include "my_thing_inlines.hpp"
#include "my_tp.hpp"
#include "my_types.hpp"
#include "my_ui.hpp"

void thing_trap_handle(Gamep g, Levelsp v, Levelp l, Thingp me)
{
  TRACE();

  if (me->tick_trap == v->tick) {
    return;
  }
  me->tick_trap = v->tick;

  THING_DBG(g, v, l, me, "over trap");

  auto   at   = thing_at(g, v, l, me);
  Thingp trap = level_is_trap(g, v, l, at);

  if (trap == nullptr) {
    thing_err(g, v, l, me, "no trap of trap found to handle");
    return;
  }

  if (thing_is_player(me)) {
    topcon(UI_IMPORTANT_FMT_STR "You hear a click..." UI_RESET_FMT);
  }

  if (thing_on_activated(g, v, l, trap, me)) {
    //
    // Trap sprung
    //
    thing_sound_play(g, v, l, me, "click");
  } else {
    //
    // Lucky
    //
    if (thing_is_player(me)) {
      topcon(UI_IMPORTANT_FMT_STR "But nothing happens." UI_RESET_FMT);
    }
  }
}
