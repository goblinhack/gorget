//
// Copyright goblinhack@gmail.com
//

#include "my_bpoint.hpp"
#include "my_level.hpp"
#include "my_level_inlines.hpp" // NOLINT
#include "my_thing.hpp"
#include "my_thing_inlines.hpp" // NOLINT
#include "my_types.hpp"

//
// Something blocking the fov?
//
auto level_light_blocker_at(Gamep g, Levelsp v, Levelp l, const bpoint &pov, Thingp me) -> Thingp
{
  FOR_ALL_THINGS_AT_UNSAFE(g, v, l, it, pov)
  {
    if (thing_vision_blocker(g, v, l, me, it)) {
      return it;
    }
  }

  return nullptr;
}
