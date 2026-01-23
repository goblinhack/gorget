//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_cpp_template.hpp"
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

  auto   outf  = make_fpoint(out);
  fpoint delta = thing_real_at(t) - make_fpoint(thing_old_at(t));
  fpoint tof   = outf + delta;
  spoint to    = make_spoint(tof);

  //
  // No need to check for collisions for things like fireballs otherwise we will
  // not be able to say fire through a teleport and hit a barrel.
  //
  if (thing_is_projectile(t)) {
    delta = thing_get_direction(g, v, l, t);
    tof   = outf + delta;
    to    = make_spoint(tof);
    out   = to;
    THING_LOG(t, "teleport projectile, delta %f,%f spoint %d,%d", delta.x, delta.y, to.x, to.y);
    return true;
  }

  if ((delta == fpoint(0, 0)) || level_is_obs_to_teleporting_onto(g, v, l, to)) {
    delta = thing_get_direction(g, v, l, t);
    tof   = outf + delta;
    to    = make_spoint(tof);
  }

  if ((delta == fpoint(0, 0)) || level_is_obs_to_teleporting_onto(g, v, l, to)) {
    delta = thing_get_direction(g, v, l, t);
    tof   = outf + delta;
    to    = make_spoint(tof);
  }

  if ((delta == fpoint(0, 0)) || level_is_obs_to_teleporting_onto(g, v, l, to)) {
    const std::initializer_list< fpoint > deltas = {
        fpoint(1, 0),   fpoint(-1, 0), fpoint(0, 1),  fpoint(0, -1),
        fpoint(-1, -1), fpoint(-1, 1), fpoint(1, -1), fpoint(1, 1),
    };

    //
    // Spawn adjacent fire
    //
    for (auto d : deltas) {
      delta = d;
      tof   = outf + delta;
      to    = make_spoint(tof);
      if (! level_is_obs_to_teleporting_onto(g, v, l, to)) {
        break;
      }
    }
  }

  tof = outf + delta;
  to  = make_spoint(tof);

  THING_LOG(t, "delta %f,%f spoint %d,%d out %d,%d", delta.x, delta.y, to.x, to.y, out.x, out.y);
  if (level_is_obs_to_teleporting_onto(g, v, l, to)) {
    //
    // Not sure how this happens, but we need the teleport to take us somewhere.
    //
    return false;
  }

  if (delta == fpoint(0, 0)) {
    //
    // This can happen if the teleport is surrounded by chasms
    //
    return false;
  }

  out = to;
  return true;
}

//
// Handles player and monster teleports
//
bool thing_teleport_handle(Gamep g, Levelsp v, Levelp l, Thingp t)
{
  TRACE_NO_INDENT();

  THING_LOG(t, "teleport, try");

  if (t->tick_teleport == v->tick) {
    THING_LOG(t, "teleport, no; too frequent");
    return false;
  }

  if (thing_is_teleporting(t)) {
    THING_LOG(t, "teleport, no; already teleporting");
    return false;
  }

  if (thing_is_teleport_blocked(t)) {
    THING_LOG(t, "teleport, no; blocked");
    return false;
  }

  spoint to;
  if (! teleport_find_other(g, v, l, thing_at(t), to)) {
    THING_LOG(t, "teleport, no; none found");
    return false;
  }

  if (is_oob(to)) {
    THING_LOG(t, "teleport, no; oob");
    return false;
  }

  //
  // Where do we spawn?
  //
  if (! teleport_find_landing_spot(g, v, l, t, to)) {
    THING_LOG(t, "failed to find landing spot next to chosen teleport");
  }

  if (to == thing_at(t)) {
    THING_LOG(t, "teleport, no; same location");
    return false;
  }

  THING_LOG(t, "pre teleport, warp to %d,%d", to.x, to.y);

  thing_warp_to(g, v, l, t, to);

  thing_is_teleporting_set(g, v, l, t);

  v->scroll_speed = MAP_SCROLL_TELEPORT_SPEED;

  thing_is_teleporting_set(g, v, l, t, 0);

  THING_LOG(t, "post teleport");

  thing_sound_play(g, v, l, t, "teleport");

  t->tick_teleport = v->tick;

  return true;
}
