//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_cpp_template.hpp"
// REMOVED #include "my_level.hpp"
#include "my_thing_inlines.hpp"

static bool teleport_find_other(Gamep g, Levelsp v, Levelp l, spoint in, spoint &out)
{
  TRACE_NO_INDENT();

  std::vector< Thingp > teleports;

  FOR_ALL_THINGS_ON_LEVEL(g, v, l, t)
  {
    if (thing_at(t) == in) {
      continue;
    }

    if (thing_is_teleport(t)) {
      teleports.push_back(t);
    }
  }

  if (! teleports.size()) {
    return false;
  }

  auto other = pcg_rand_one_of(teleports);

  if (other) {
    //
    // Sets reference
    //
    out = thing_at(other);
    return true;
  }

  return false;
}

//
// Find a spot next to the teleport where we can land.
//
static bool teleport_find_landing_spot(Gamep g, Levelsp v, Levelp l, Thingp t, spoint &out)
{
  TRACE_NO_INDENT();

  spoint to;
  auto   delta = thing_at(t) - thing_old_at(t);
  to           = out + delta;

  if ((delta == spoint(0, 0)) || level_is_obs_to_teleporting_onto(g, v, l, to)) {
    delta = thing_get_delta_from_dir(t);
    to    = out + delta;
  }

  if ((delta == spoint(0, 0)) || level_is_obs_to_teleporting_onto(g, v, l, to)) {
    delta = thing_get_delta_from_dir(t);
    to    = out + delta;
  }

  if ((delta == spoint(0, 0)) || level_is_obs_to_teleporting_onto(g, v, l, to)) {
    const std::initializer_list< spoint > deltas = {
        spoint(1, 0),   spoint(-1, 0), spoint(0, 1),  spoint(0, -1),
        spoint(-1, -1), spoint(-1, 1), spoint(1, -1), spoint(1, 1),
    };

    //
    // Spawn adjacent fire
    //
    for (auto d : deltas) {
      delta = d;
      to    = out + delta;
      if (! level_is_obs_to_teleporting_onto(g, v, l, to)) {
        break;
      }
    }
  }

  to = out + delta;

  if ((delta == spoint(0, 0)) || level_is_obs_to_teleporting_onto(g, v, l, to)) {
    return false;
  }

  out = to;
  return true;
}

//
// Handles player and monster teleports
//
bool thing_teleport(Gamep g, Levelsp v, Levelp l, Thingp t)
{
  TRACE_NO_INDENT();

  THING_LOG(t, "teleport, try");
  if (thing_is_teleporting(t)) {
    return false;
  }

  if (thing_is_teleport_blocked(t)) {
    return false;
  }

  spoint to;
  if (! teleport_find_other(g, v, l, thing_at(t), to)) {
    return false;
  }

  if (is_oob(to)) {
    return false;
  }

  //
  // Where do we spawn?
  //
  if (! teleport_find_landing_spot(g, v, l, t, to)) {
    return false;
  }

  if (to == thing_at(t)) {
    return false;
  }

  THING_LOG(t, "pre teleport, warp to %d,%d", to.x, to.y);

  thing_warp_to(g, v, l, t, to);

  thing_is_teleporting_set(g, v, l, t);

  v->scroll_speed = MAP_SCROLL_TELEPORT_SPEED;

  thing_is_teleporting_set(g, v, l, t, 0);

  THING_LOG(t, "post teleport");

  thing_sound_play(g, v, l, t, "teleport");

  return true;
}
