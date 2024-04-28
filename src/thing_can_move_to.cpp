//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_level.hpp"
#include "my_tp.hpp"

bool level_thing_can_move(Levelp l, Thingp t, int new_loc_x, int new_loc_y)
{
  if (level_is_oob(l, new_loc_x, new_loc_y)) {
    return false;
  }

  if ((new_loc_x == t->x) && (new_loc_y == t->y)) {
    return true;
  }

  auto my_tp = level_thing_tp(l, t);

  FOR_ALL_TPS_AT(l, it, it_tp, new_loc_x, new_loc_y)
  {
    if (tp_is_player_get(my_tp) && tp_is_obs_player_get(it_tp)) {
      return false;
    }

    if (tp_is_monst_get(my_tp) && tp_is_obs_monst_get(it_tp)) {
      return false;
    }
  }

  return true;
}
