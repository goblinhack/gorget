//
// Copyright goblinhack@gmail.com
//

#include "my_bpoint.hpp"
#include "my_callstack.hpp"
#include "my_dmap.hpp"
#include "my_level.hpp"
#include "my_main.hpp"
#include "my_thing.hpp"
#include "my_types.hpp"
#include <cmath>

[[nodiscard]] auto thing_vision_can_hear_tile(Gamep g, Levelsp v, Levelp l, Thingp t, bpoint p) -> bool
{
  TRACE();

  auto noise = v->dmap_noise.val[ p.x ][ p.y ];

  if (noise == DMAP_IS_WALL) {
    return false;
  }
  if (noise == DMAP_IS_PASSABLE) {
    return false;
  }
  if (noise == DMAP_IS_GOAL_REVERSE) {
    return false;
  }
  if (noise == DMAP_IS_GOAL) {
    return false;
  }

  auto actual_noise = DMAP_IS_GOAL_REVERSE - noise;

  //
  //        xxxxx
  //     xxx.....xxx
  //   xx...........xx
  //  x...............x
  // x.................x
  // x.................x
  // x........@98765432100000
  //                   |
  //                   + noise level 9
  //
  //           yyyyyyyyynnnnnn (monst with hearing level 1) best hearing
  //           yyyyyyyynnnnnnn (monst with hearing level 2)
  //           yyyyyyynnnnnnnn (monst with hearing level 3)
  //           yyyyyynnnnnnnnn (monst with hearing level 4)
  //           yyyyynnnnnnnnnn (monst with hearing level 5)
  //           yyyynnnnnnnnnnn (monst with hearing level 6)
  //           yyynnnnnnnnnnnn (monst with hearing level 7)
  //           yynnnnnnnnnnnnn (monst with hearing level 8)
  //           ynnnnnnnnnnnnnn (monst with hearing level 9) worst hearing
  //
  // y - can hear
  // n - cannot hear

  if (compiler_unused) {
    THING_DBG(g, v, l, t, "tile dmap value         : %d", noise);
    THING_DBG(g, v, l, t, " actual_noise           : %d", actual_noise);
    THING_DBG(g, v, l, t, " thing_hearing_threshold: %d", thing_hearing_threshold(t));
    THING_DBG(g, v, l, t, " can hear               : %d", actual_noise >= thing_hearing_threshold(t) ? true : false);
  }

  return actual_noise >= thing_hearing_threshold(t) ? true : false;
}
