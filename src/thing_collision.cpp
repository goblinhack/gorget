//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
// REMOVED #include "my_fpoint.hpp"
// REMOVED #include "my_globals.hpp"
#include "my_main.hpp"
#include "my_thing_inlines.hpp"

#include <algorithm>

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

  if (thing_is_projectile(me)) {
    auto source     = me;
    auto event_type = THING_EVENT_FIRE_DAMAGE;
    auto damage     = tp_damage(thing_tp(source), event_type);

    ThingEvent e {
        .reason     = "by explosion damage", //
        .event_type = event_type,            //
        .damage     = damage,                //
        .source     = source,                //
    };

    THING_LOG(me, "collison with");
    THING_LOG(obstacle, "me");

    thing_damage(g, v, l, obstacle, e);
  }

  if (thing_is_dead_on_collision(me)) {
    ThingEvent e {
        .reason     = "collided",                   //
        .event_type = THING_EVENT_LIFESPAN_EXPIRED, //
    };

    thing_dead(g, v, l, me, e);
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
  // Projectiles handled seperately.
  //
  if (thing_is_projectile(me)) {
    return;
  }

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
  float A_radius = thing_collision_radius(A);
  float B_radius = thing_collision_radius(B);

  float touching_dist = A_radius + B_radius;
  float dist          = distance(A_at, B_at);

  if (0) {
    THING_CON(A, "A %f,%f touching_dist %f dist %f ", A_at.x, A_at.y, touching_dist, dist);
    THING_CON(B, "B %f,%f", B_at.x, B_at.y);
  }

  if (dist >= touching_dist) {
    return false;
  }

  return true;
}

static bool thing_collision_check_circle_square(Gamep g, Levelsp v, Levelp l, Thingp C, fpoint C_at, Thingp B,
                                                fpoint B_at)
{
  float radius = thing_collision_radius(C);

  C_at.x += 0.5;
  C_at.y += 0.5;

  fpoint tl(B_at.x, B_at.y);
  fpoint br(B_at.x + 1, B_at.y + 1);

  //
  // This simpler check seems more accurate
  //
  if ((C_at.x >= tl.x) && (C_at.x <= br.x) && (C_at.y >= tl.y) && (C_at.y <= br.y)) {
    return true;
  }
  return false;

  fpoint B0(B_at.x - 0, B_at.y - 0);
  fpoint B1(B_at.x + 1, B_at.y - 0);
  fpoint B2(B_at.x - 0, B_at.y + 1);
  fpoint B3(B_at.x + 1, B_at.y + 1);

  //
  // Circle inside box
  //
  if (B_at == C_at) {
    return true;
  }

  //
  // Corner collisions.
  //
  if (distance(C_at, B0) < radius) {
    return true;
  }

  if (distance(C_at, B1) < radius) {
    return true;
  }

  if (distance(C_at, B2) < radius) {
    return true;
  }

  if (distance(C_at, B3) < radius) {
    return true;
  }

  fpoint *intersect_out = nullptr;
  float   dist;

  if (distance_to_line(C_at, B0, B1, &dist, intersect_out)) {
    if (dist < radius) {
      return true;
    }
  }

  if (distance_to_line(C_at, B1, B2, &dist, intersect_out)) {
    if (dist < radius) {
      return true;
    }
  }

  if (distance_to_line(C_at, B2, B3, &dist, intersect_out)) {
    if (dist < radius) {
      return true;
    }
  }

  if (distance_to_line(C_at, B3, B0, &dist, intersect_out)) {
    if (dist < radius) {
      return true;
    }
  }

  return false;
}

static bool thing_collision_check_squares(Gamep g, Levelsp v, Levelp l, Thingp A, fpoint A_at, Thingp B, fpoint B_at)
{
  fpoint A0(A_at.x - 0, A_at.y - 0);
  fpoint A1(A_at.x + 1, A_at.y - 0);
  fpoint A2(A_at.x - 0, A_at.y + 1);
  fpoint A3(A_at.x + 1, A_at.y + 1);

  fpoint tl(B_at.x - 0, B_at.y - 0);
  fpoint br(B_at.x + 1, B_at.y + 1);

  if ((A0.x >= tl.x) && (A0.x <= br.x) && (A0.y >= tl.y) && (A0.y <= br.y)) {
    return true;
  }
  if ((A1.x >= tl.x) && (A1.x <= br.x) && (A1.y >= tl.y) && (A1.y <= br.y)) {
    return true;
  }
  if ((A2.x >= tl.x) && (A2.x <= br.x) && (A2.y >= tl.y) && (A2.y <= br.y)) {
    return true;
  }
  if ((A3.x >= tl.x) && (A3.x <= br.x) && (A3.y >= tl.y) && (A3.y <= br.y)) {
    return true;
  }

  return false;
}

static bool thing_collision_check_circle_small_circle_small(Gamep g, Levelsp v, Levelp l, Thingp me, fpoint me_at,
                                                            Thingp o, fpoint o_at)
{
  TRACE_NO_INDENT();
  return thing_collision_check_circle_circle(g, v, l, me, me_at, o, o_at);
}

static bool thing_collision_check_circle_small_circle_large(Gamep g, Levelsp v, Levelp l, Thingp me, fpoint me_at,
                                                            Thingp o, fpoint o_at)
{
  TRACE_NO_INDENT();
  return thing_collision_check_circle_circle(g, v, l, me, me_at, o, o_at);
}

static bool thing_collision_check_circle_small_square(Gamep g, Levelsp v, Levelp l, Thingp me, fpoint me_at, Thingp o,
                                                      fpoint o_at)
{
  TRACE_NO_INDENT();
  return thing_collision_check_circle_square(g, v, l, me, me_at, o, o_at);
}

static bool thing_collision_check_circle_large_circle_large(Gamep g, Levelsp v, Levelp l, Thingp me, fpoint me_at,
                                                            Thingp o, fpoint o_at)
{
  TRACE_NO_INDENT();
  return thing_collision_check_circle_circle(g, v, l, me, me_at, o, o_at);
}

static bool thing_collision_check_circle_large_square(Gamep g, Levelsp v, Levelp l, Thingp me, fpoint me_at, Thingp o,
                                                      fpoint o_at)
{
  TRACE_NO_INDENT();
  return thing_collision_check_circle_square(g, v, l, me, me_at, o, o_at);
}

static bool thing_collision_check_square_square(Gamep g, Levelsp v, Levelp l, Thingp me, fpoint me_at, Thingp o,
                                                fpoint o_at)
{
  TRACE_NO_INDENT();
  return thing_collision_check_squares(g, v, l, me, me_at, o, o_at);
}

//
// For fast moving objects, they might jump 1 or 2 tiles, so we need to collision detect
// for enough points in between to make sense.
//
void thing_collision_handle_interpolated(Gamep g, Levelsp v, Levelp l, Thingp me, fpoint old_at)
{
  TRACE_NO_INDENT();

  if (0) {
    THING_CON(me, "thing_collision_handle_interpolated");
  }
  auto  at    = thing_real_at(me);
  auto  src   = thing_at(me);
  float dist  = distance(at, old_at);
  float steps = ceil(dist) * 10;
  auto  diff  = at - old_at;
  float stepx = diff.x / steps;
  float stepy = diff.y / steps;

  for (auto step = 0; step < steps; step++) {
    std::vector< std::pair< float, Thingp > > pairs;
    fpoint                                    me_at(old_at.x + stepx * step, old_at.y + stepy * step);

    for (auto dx = -1; dx <= 1; dx++) {
      for (auto dy = -1; dy <= 1; dy++) {

        spoint collision_at(src.x + dx, src.y + dy);
        FOR_ALL_THINGS_AT(g, v, l, o, collision_at)
        {
          if (o == me) {
            continue;
          }

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
            float                      o_dist = distance(at, o_at);
            std::pair< float, Thingp > p      = std::make_pair(o_dist, o);
            pairs.push_back(p);
          }
        }
      }
    }

    //
    // Sort by distance
    //
    std::sort(pairs.begin(), pairs.end(),
              [](const std::pair< float, Thingp > &a, const std::pair< float, Thingp > &b) {
                auto d1 = a.first;
                auto d2 = b.first;
                auto t1 = a.second;
                auto t2 = b.second;
                return (d1 < d2) && t1->_priority < t2->_priority;
              });

    if (0) {
      for (auto a_pair : pairs) {
        auto o_dist = a_pair.first;
        auto o      = a_pair.second;

        THING_CON(o, "distance %f prio %u", o_dist, o->_priority);
      }
    }

    for (auto a_pair : pairs) {
      auto o = a_pair.second;

      thing_is_hit_set(g, v, l, o, MAX_HIT_TIME_MS);

      thing_collision_handle_thing(g, v, l, o, me);

      if (thing_is_dead(me)) {
        return;
      }
    }
  }

  if (0) {
    CON("-");
  }
}
