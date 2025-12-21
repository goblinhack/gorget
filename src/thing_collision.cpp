//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_globals.hpp"
#include "my_main.hpp"
#include "my_thing_inlines.hpp"

//
// Handle interactions for a thing at its location with a dead thing
//
static void thing_collision_handle_dead_thing(Gamep g, Levelsp v, Levelp l, Thingp obstacle, Thingp me)
{
  TRACE_NO_INDENT();

  //
  // TODO
  //
}

//
// Handle interactions for a thing at its location with an alive thing
//
static void thing_collision_handle_alive_thing(Gamep g, Levelsp v, Levelp l, Thingp obstacle, Thingp me)
{
  TRACE_NO_INDENT();

  //
  // Crush obstacle
  //
  if (thing_crush(g, v, l, obstacle, me)) {
    return;
  }

  //
  // Collect keys?
  //
  if (thing_collect_key(g, v, l, obstacle, me)) {
    return;
  }

  //
  // Collect items?
  //
  if (thing_carry_item(g, v, l, obstacle, me)) {
    return;
  }
}

//
// Handle interactions for a thing at its location
//
static void thing_collision_handle_thing(Gamep g, Levelsp v, Levelp l, Thingp obstacle, Thingp me)
{
  TRACE_NO_INDENT();

  if (obstacle == me) {
    return;
  }

  if (thing_is_dead(me)) {
    return;
  }

  if (thing_is_ethereal(me)) {
    return;
  }

  if (thing_is_dead(obstacle)) {
    //
    // Dead things
    //
    thing_collision_handle_dead_thing(g, v, l, obstacle, me);
  } else {
    //
    // Alive things
    //
    thing_collision_handle_alive_thing(g, v, l, obstacle, me);
  }
}

//
// Handle interactions for a thing at its location
//
void thing_collision_handle(Gamep g, Levelsp v, Levelp l, Thingp me)
{
  TRACE_NO_INDENT();

  //
  // Handle player specific actions first, like leaving levels
  //
  if (thing_is_player(me)) {
    player_collision_handle(g, v, l, me);
  }

  //
  // Common collision handling for player and anything else
  //
  auto at = thing_at(me);
  FOR_ALL_THINGS_AT(g, v, l, obstacle, at)
  {
    // newline
    thing_collision_handle_thing(g, v, l, obstacle, me);
  }
}

static bool thing_collision_check_circle_circle(Gamep g, Levelsp v, Levelp l, Thingp A, fpoint A_at, Thingp B,
                                                fpoint B_at)
{
  float A_radius = thing_is_collision_circle_small(A) ? 0.5 : 1.0;
  float B_radius = thing_is_collision_circle_small(B) ? 0.5 : 1.0;

  fpoint n             = B_at - A_at;
  double touching_dist = A_radius + B_radius;
  double dist_squared  = n.x * n.x + n.y * n.y;

  double diff = dist_squared - touching_dist * touching_dist;
  if (diff > 0.0) {
    // Circles are not touching
    return false;
  }

  return true;
}

static bool thing_collision_check_circle_small_circle_small(Gamep g, Levelsp v, Levelp l, Thingp me, fpoint me_at,
                                                            Thingp o, fpoint o_at)
{
  TRACE_NO_INDENT();
  return thing_collision_check_circle_circle(g, v, l, me, me_at, o, o_at);
  return false;
}

static bool thing_collision_check_circle_small_circle_large(Gamep g, Levelsp v, Levelp l, Thingp me, fpoint me_at,
                                                            Thingp o, fpoint o_at)
{
  TRACE_NO_INDENT();
  return thing_collision_check_circle_circle(g, v, l, me, me_at, o, o_at);
  return false;
}

static bool thing_collision_check_circle_small_square(Gamep g, Levelsp v, Levelp l, Thingp me, fpoint me_at, Thingp o,
                                                      fpoint o_at)
{
  TRACE_NO_INDENT();
  ERR("TODO");
  return false;
}

static bool thing_collision_check_circle_large_circle_large(Gamep g, Levelsp v, Levelp l, Thingp me, fpoint me_at,
                                                            Thingp o, fpoint o_at)
{
  TRACE_NO_INDENT();
  return thing_collision_check_circle_circle(g, v, l, me, me_at, o, o_at);
  return false;
}

static bool thing_collision_check_circle_large_square(Gamep g, Levelsp v, Levelp l, Thingp me, fpoint me_at, Thingp o,
                                                      fpoint o_at)
{
  TRACE_NO_INDENT();
  ERR("TODO");
  return false;
}

static bool thing_collision_check_square_square(Gamep g, Levelsp v, Levelp l, Thingp me, fpoint me_at, Thingp o,
                                                fpoint o_at)
{
  TRACE_NO_INDENT();
  ERR("TODO");
  return false;
}

//
// For fast moving objects, they might jump 1 or 2 tiles, so we need to collision detect
// for enough points in between to make sense.
//
void thing_collision_handle_interpolated(Gamep g, Levelsp v, Levelp l, Thingp me, fpoint old_at)
{
  TRACE_NO_INDENT();

  auto  at    = thing_real_at(me);
  auto  src   = thing_at(me);
  float dist  = distance(at, old_at);
  float steps = ceil(dist) * 10;
  auto  diff  = at - old_at;
  float stepx = diff.x / steps;
  float stepy = diff.y / steps;

  for (auto step = 0; step < steps; step++) {
    fpoint me_at(old_at.x + stepx * step, old_at.y + stepy * step);

    for (auto dx = -1; dx <= 1; dx++) {
      for (auto dy = -1; dy <= 1; dy++) {

        spoint collision_at(src.x + dx, src.y + dy);
        FOR_ALL_THINGS_AT(g, v, l, o, collision_at)
        {
          auto o_at      = thing_real_at(o);
          auto collision = false;

          if (thing_is_collision_circle_small(me)) {
            if (thing_is_collision_circle_small(o)) {
              collision = thing_collision_check_circle_small_circle_small(g, v, l, me, me_at, o, o_at);
            } else if (thing_is_collision_circle_large(o)) {
              collision = thing_collision_check_circle_small_circle_large(g, v, l, me, me_at, o, o_at);
            } else if (thing_is_collision_square(o)) {
              collision = thing_collision_check_circle_small_square(g, v, l, me, me_at, o, o_at);
            } else {
              continue;
            }
          } else if (thing_is_collision_circle_large(me)) {
            if (thing_is_collision_circle_small(o)) {
              collision = thing_collision_check_circle_small_circle_large(g, v, l, me, me_at, o, o_at);
            } else if (thing_is_collision_circle_large(o)) {
              collision = thing_collision_check_circle_large_circle_large(g, v, l, me, me_at, o, o_at);
            } else if (thing_is_collision_square(o)) {
              collision = thing_collision_check_circle_large_square(g, v, l, me, me_at, o, o_at);
            } else {
              continue;
            }
          } else if (thing_is_collision_square(me)) {
            if (thing_is_collision_circle_small(o)) {
              collision = thing_collision_check_circle_small_square(g, v, l, o, o_at, me, me_at);
            } else if (thing_is_collision_circle_large(o)) {
              collision = thing_collision_check_circle_large_square(g, v, l, o, o_at, me, me_at);
            } else if (thing_is_collision_square(o)) {
              collision = thing_collision_check_square_square(g, v, l, o, o_at, me, me_at);
            } else {
              continue;
            }
          } else {
            THING_ERR(me, "no collision type set");
            continue;
          }

          if (collision) {
            thing_collision_handle_thing(g, v, l, o, me);
          }
        }
      }
    }
  }
}
