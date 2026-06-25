//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_color_defs.hpp"
#include "my_game_defs.hpp"
#include "my_game_popups.hpp"
#include "my_level.hpp"
#include "my_main.hpp"
#include "my_string.hpp"
#include "my_thing.hpp"
#include "my_thing_callbacks.hpp"
#include "my_thing_inlines.hpp"
#include "my_tp.hpp"
#include "my_types.hpp"
#include "my_ui.hpp"

#include <algorithm>
#include <string>

[[nodiscard]] auto thing_vision_can_hear_tile(Gamep g, Levelsp v, Levelp l, Thingp t, bpoint p) -> bool
{
  TRACE();

  auto noise_level = v->dmap_noise.val[ p.x ][ p.y ];

  topcon("noise %d", noise_level);
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
  topcon("actual_noise %d limit %d", actual_noise, thing_distance_hearing(t));
  if (actual_noise > thing_distance_hearing(t)) {
    return false;
  }

  return true;
}
