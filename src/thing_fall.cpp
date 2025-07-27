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

//
// Ok to land on this spot?
//
static bool thing_ok_landing_spot(Gamep g, Levelsp v, Levelp l, Thingp t, spoint p)
{
  TRACE_NO_INDENT();

  if (is_oob(p)) {
    return false;
  }

  if (level_is_obstacle_to_landing(g, v, l, p)) {
    return false;
  }

  return true;
}

//
// Try to find a spot clost to where we landed that is ok to exist in.
// i.e. no landing inside walls.
//
static spoint thing_choose_landing_spot(Gamep g, Levelsp v, Levelp l, Thingp t)
{
  TRACE_NO_INDENT();

  spoint p    = t->at;
  int    dist = 1;

  for (;;) {
    if (thing_ok_landing_spot(g, v, l, t, p)) {
      return p;
    }

    for (auto dx = -dist; dx <= dist; dx++) {
      for (auto dy = -dist; dy <= dist; dy++) {
        p.x = t->at.x + dx;
        p.y = t->at.y + dy;

        if (thing_ok_landing_spot(g, v, l, t, p)) {
          return p;
        }
      }
    }

    dist++;
  }

  return t->at;
}

//
// Complete the fall to the next level. If this is the player we also change level.
//
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

  auto new_location = thing_choose_landing_spot(g, v, next_level, t);
  thing_warp_to(g, v, next_level, t, new_location);
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
