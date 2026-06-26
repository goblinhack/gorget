//
// Copyright goblinhack@gmail.com
//

#include "my_bpoint.hpp"
#include "my_callstack.hpp"
#include "my_dmap.hpp"
#include "my_level.hpp"
#include "my_thing.hpp"
#include "my_types.hpp"

[[nodiscard]] auto thing_vision_can_hear_tile(Gamep g, Levelsp v, Levelp l, Thingp t, bpoint p) -> bool
{
  TRACE();

  auto noise_level = v->dmap_noise.val[ p.x ][ p.y ];

  if (noise_level == DMAP_IS_WALL) {
    return false;
  }
  if (noise_level == DMAP_IS_PASSABLE) {
    return false;
  }
  if (noise_level == DMAP_IS_GOAL_REVERSE) {
    return false;
  }
  if (noise_level == DMAP_IS_GOAL) {
    return false;
  }

  auto actual_noise = DMAP_IS_GOAL_REVERSE - noise_level;

  if (compiler_unused) {
    log("noise_level %d", noise_level);
    log("actual_noise %d", actual_noise);
    log("thing_distance_hearing %d", thing_distance_hearing(t));
  }

  return actual_noise >= thing_distance_hearing(t);
}
