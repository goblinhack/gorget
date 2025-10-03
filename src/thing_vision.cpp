//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_level.hpp"

void thing_vision_reset(Gamep g, Levelsp v, Levelp l, Thingp t)
{
  TRACE_NO_INDENT();

  auto ai = thing_ai_struct(g, t);
  if (! ai) {
    ERR("missing ai struct");
    return;
  }

  ai->fov_can_see_tile       = {{{0}}};
  ai->fov_has_seen_tile = {{{0}}};
}

bool thing_vision_can_see_tile(Gamep g, Levelsp v, Levelp l, Thingp t, spoint p)
{
  TRACE_NO_INDENT();

  auto ai = thing_ai_struct(g, t);
  if (! ai) {
    ERR("missing ai struct");
    return false;
  }

  if (is_oob(p)) {
    return false;
  }
  return ai->fov_can_see_tile.can_see[ p.x ][ p.y ];
}

bool thing_vision_has_seen_tile(Gamep g, Levelsp v, Levelp l, Thingp t, spoint p)
{
  TRACE_NO_INDENT();

  auto ai = thing_ai_struct(g, t);
  if (! ai) {
    ERR("missing ai struct");
    return false;
  }

  if (is_oob(p)) {
    return false;
  }
  return ai->fov_has_seen_tile.can_see[ p.x ][ p.y ];
}
