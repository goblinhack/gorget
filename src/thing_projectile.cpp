//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_globals.hpp"
#include "my_level.hpp"
#include "my_main.hpp"
#include "my_math.hpp"
#include "my_thing_callbacks.hpp"

static fpoint thing_projectile_get_delta_from_dt(Gamep g, Levelsp v, Levelp l, Thingp t, float dt)
{
  TRACE_NO_INDENT();

  float s;
  float c;
  sincosf(t->angle, &s, &c);

  auto player = thing_player(g);
  if (! player) {
    DIE("No player struct found");
    return fpoint(0, 0);
  }

  const int   player_speed = thing_speed(player);
  const float t_speed      = thing_speed(t);
  const auto  tile_speed   = (t_speed / (float) player_speed);

  return fpoint(c * dt * tile_speed, s * dt * tile_speed);
}

fpoint thing_projectile_get_direction(Gamep g, Levelsp v, Levelp l, Thingp t)
{
  TRACE_NO_INDENT();

  return unit(thing_projectile_get_delta_from_dt(g, v, l, t, 1.0));
}

void thing_projectile_fire_at(Gamep g, Levelsp v, Levelp l, Thingp me, const std::string &what, const fpoint target)
{
  TRACE_NO_INDENT();

  auto delta = target - make_fpoint(thing_at(me));

  if ((delta.x == 0) && (delta.y == 0)) {
    delta.x = 1;
  }

  auto  angle = angle_radians(delta);
  float s;
  float c;
  sincosf(angle, &s, &c);

  auto   tp_what = tp_find_mand(what);
  fpoint at      = thing_real_at(me);

  //
  // Need a small fraction to account for comparisons of very similar floats where
  // we end up shooting the player upon firing
  //
  float offset = thing_collision_radius(me) + tp_collision_radius(tp_what) + 0.01f;
  at.x += c * offset;
  at.y += s * offset;

  auto projectile = thing_spawn(g, v, l, tp_what, at);
  if (projectile) {
    projectile->angle = angle;
  }

  thing_is_moving_set(g, v, l, projectile);
}

void thing_projectile_fire_at(Gamep g, Levelsp v, Levelp l, Thingp me, const std::string &what, const spoint target)
{
  thing_projectile_fire_at(g, v, l, me, what, make_fpoint(target));
}

void thing_projectile_move(Gamep g, Levelsp v, Levelp l, Thingp t, float dt)
{
  TRACE_NO_INDENT();

  THING_LOG(t, "proj move");
  fpoint old_at = thing_real_at(t);
  auto   at     = old_at;

  auto player = thing_player(g);
  if (! player) {
    ERR("No player struct found");
    return;
  }

  auto delta = thing_projectile_get_delta_from_dt(g, v, l, t, dt);
  at.x += delta.x;
  at.y += delta.y;

  if (is_oob(at)) {
    ThingEvent e {
        .reason     = "oob",                        //
        .event_type = THING_EVENT_LIFESPAN_EXPIRED, //
    };

    thing_dead(g, v, l, t, e);
    return;
  }

  thing_pop(g, v, t);
  thing_at_set(t, at);
  thing_update_pos(g, v, l, t);
  thing_push(g, v, l, t);

  thing_on_moved(g, v, l, t);

  if (t->thing_dt > 0) {
    //
    // Handle interactions for a thing at its new location
    //
    thing_collision_handle_interpolated(g, v, l, t, old_at);
  }
  THING_LOG(t, "post move of delta %f,%f", delta.x, delta.y);
}
