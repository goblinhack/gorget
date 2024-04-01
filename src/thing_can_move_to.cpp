//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_level.hpp"
#include "my_tp.hpp"

bool thing_can_move(LevelData *data, Thingp t, point new_loc)
{
  if (::is_oob(data, new_loc)) {
    return false;
  }

  point my_loc(t->x, t->y);
  if (new_loc == my_loc) {
    return true;
  }

  auto my_tp = ::thing_tp(data, t);

  FOR_ALL_TPS_AT(data, it, it_tp, new_loc)
  {
    if (my_tp->is_player && it_tp->is_obs_player) {
      return false;
    }

    if (my_tp->is_monst && it_tp->is_obs_monst) {
      return false;
    }
  }

  return true;
}

bool Level::thing_can_move(Thingp t, point new_loc)
{
  TRACE_NO_INDENT();
  return ::thing_can_move(data, t, new_loc);
}
