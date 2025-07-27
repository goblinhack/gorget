//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_game.hpp"
#include "my_level.hpp"
#include "my_main.hpp"
#include "my_random.hpp"
#include "my_tile.hpp"
#include "my_tp.hpp"
#include "my_ui.hpp"

static void thing_fall_end(Gamep g, Levelsp v, Levelp l, Thingp t)
{
  TRACE_NO_INDENT();

  auto next_level = level_select_get_next_level_down(g, v, l);
  if (! next_level) {
    return;
  }

  if (thing_is_player(t)) {
    TOPCON_NEW_LINE();
    TOPCON(UI_IMPORTANT_FMT_STR "You tumble into the void." UI_RESET_FMT);

    l = level_change(g, v, next_level->level_num);
    if (next_level != l) {
      ERR("unexpected level found");
      return;
    }
  }

  thing_warp_to(g, v, next_level, t, t->at);
  if (thing_is_player(t)) {
    level_scroll_warp_to_focus(g, v, l);
  }
}

//
// Falling time step
//
void thing_fall_time_step(Gamep g, Levelsp v, Levelp l, Thingp t, int time_step)
{
  TRACE_NO_INDENT();

  if (thing_is_falling_incr(g, v, l, t, time_step) > MAX_FALL_TIME_MS) {
    thing_is_falling_set(g, v, l, t, 0);
    thing_fall_end(g, v, l, t);
  }
}
