//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_game.hpp"
#include "my_globals.hpp"
#include "my_level.hpp"
#include "my_main.hpp"

void thing_vision_reset(Gamep g, Levelsp v, Levelp l, Thingp t)
{
  TRACE_NO_INDENT();

  auto ext = thing_ext_struct(g, t);
  if (! ext) {
    THING_ERR(t, "missing ext struct");
    return;
  }

  ext->fov_can_see_tile = {{{0}}};
}

bool thing_vision_can_see_tile(Gamep g, Levelsp v, Levelp l, Thingp t, spoint p)
{
  TRACE_NO_INDENT();

  auto ext = thing_ext_struct(g, t);
  if (! ext) {
    THING_ERR(t, "missing ext struct");
    return false;
  }

  if (is_oob(p)) {
    return false;
  }

  //
  // Check the thing is on the same level.
  //
  auto t_level = game_level_get(g, v, t->level_num);
  if (t_level && (t_level != l)) {
    return false;
  }

  return ext->fov_can_see_tile.can_see[ p.x ][ p.y ];
}

bool thing_vision_player_has_seen_tile(Gamep g, Levelsp v, Levelp l, spoint p)
{
  TRACE_NO_INDENT();

  if (is_oob(p)) {
    return false;
  }

  return l->player_fov_has_seen_tile.can_see[ p.x ][ p.y ];
}
