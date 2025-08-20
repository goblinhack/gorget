//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_cpp_template.hpp"
#include "my_fpoint.hpp"
#include "my_game_popups.hpp"
#include "my_level.hpp"
#include "my_main.hpp"
#include "my_ptrcheck.hpp"
#include "my_random.hpp"
#include "my_sound.hpp"
#include "my_tile.hpp"
#include "my_tp_callbacks.hpp"

static bool teleport_find_other(Gamep g, Levelsp v, Levelp l, spoint in, spoint &out)
{
  TRACE_NO_INDENT();

  std::vector< Thingp > teleports;

  FOR_ALL_THINGS_ON_LEVEL(g, v, l, t)
  {
    if (t->at == in) {
      continue;
    }

    if (thing_is_teleport(t)) {
      teleports.push_back(t);
    }
  }

  if (! teleports.size()) {
    return false;
  }

  auto destination = pcg_rand_one_of(teleports);

  out = destination->at;

  return true;
}

//
// Handles player and monster teleports
//
bool thing_teleport(Gamep g, Levelsp v, Levelp l, Thingp t)
{
  TRACE_NO_INDENT();

  if (thing_is_teleporting(t)) {
    return false;
  }

  if (thing_is_teleport_blocked(t)) {
    return false;
  }

  if (thing_is_ethereal(t)) {
    return false;
  }

  if (thing_is_gaseous(t)) {
    return false;
  }

  spoint to;
  if (! teleport_find_other(g, v, l, t->at, to)) {
    return false;
  }

  if (is_oob(to)) {
    return false;
  }

  if (to == t->at) {
    return false;
  }

  THING_LOG(t, "pre teleport");

  thing_warp_to(g, v, l, t, to);

  thing_is_teleporting_set(g, v, l, t);

  thing_is_teleporting_set(g, v, l, t, 0);

  THING_LOG(t, "post teleport");

  return true;
}
