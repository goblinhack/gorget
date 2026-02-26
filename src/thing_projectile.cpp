//
// Copyright goblinhack@gmail.com
//

#include <cmath>

#include "my_callstack.hpp"
#include "my_globals.hpp"
#include "my_level.hpp"
#include "my_main.hpp"
#include "my_math.hpp"
#include "my_thing_callbacks.hpp"

static auto thing_projectile_get_delta_from_dt(Gamep g, Thingp t, float dt) -> fpoint
{
  TRACE();

  float s = 0;
  float c = 0;
  SINCOSF(t->angle, &s, &c);

  auto *player = thing_player(g);
  UNLIKELY if (player == nullptr) {
    CROAK("No player struct found");
    return fpoint(0, 0);
  }

  const int   player_speed = thing_speed(player);
  const float t_speed      = thing_speed(t);
  const auto  tile_speed   = (t_speed / (float) player_speed);

  auto delta = fpoint(c * dt * tile_speed, s * dt * tile_speed);
  if ((delta.x == 0) && (delta.y == 0)) {
    CROAK("No delta for projectile sin %f cos %f dt %f tile_speed %f", s, c, dt, tile_speed);
  }

  return delta;
}

auto thing_projectile_get_direction(Gamep g, Levelsp v, Levelp l, Thingp t) -> fpoint
{
  TRACE();

  return unit(thing_projectile_get_delta_from_dt(g, t, 1.0));
}

auto thing_projectile_fire_at(Gamep g, Levelsp v, Levelp l, Thingp me, Tpp what, const fpoint target) -> bool
{
  TRACE();

  THING_LOG(me, "fire projectile");

  auto delta = target - make_fpoint(thing_at(me));

  if ((delta.x == 0) && (delta.y == 0)) {
    delta.x = 1;
  }

  auto  angle = angle_radians(delta);
  float s     = 0;
  float c     = 0;
  SINCOSF(angle, &s, &c);

  fpoint proj_at = thing_real_at(me);

  //
  // Need a small fraction to account for comparisons of very similar floats where
  // we end up shooting the player upon firing
  //
  float const offset = thing_collision_radius(me) + tp_collision_radius(what) + THING_COLLISION_FIRING_OFFSET;
  proj_at.x += c * offset;
  proj_at.y += s * offset;

  auto *projectile = thing_spawn(g, v, l, what, proj_at);
  if (projectile == nullptr) {
    return false;
  }

  projectile->angle = angle;

  //
  // Set my direction based on where I fire
  //
  spoint const dir    = make_spoint(proj_at);
  spoint const source = thing_at(me);
  thing_set_dir_from_delta(me, dir.x - source.x, dir.y - source.y);

  thing_is_moving_set(g, v, l, projectile);

  auto real_at = thing_real_at(projectile);

  if (compiler_unused) {
    THING_LOG(projectile, "%f,%f", real_at.x, real_at.y);
  }

  return true;
}

auto thing_projectile_fire_at(Gamep g, Levelsp v, Levelp l, Thingp me, Tpp what, const spoint target) -> bool
{
  return thing_projectile_fire_at(g, v, l, me, what, make_fpoint(target));
}

void thing_projectile_move(Gamep g, Levelsp v, Levelp l, Thingp t, float dt)
{
  TRACE();

  fpoint const old_at = thing_real_at(t);
  auto         at     = old_at;

  auto *player = thing_player(g);
  UNLIKELY if (player == nullptr) {
    ERR("No player struct found");
    return;
  }

  auto delta = thing_projectile_get_delta_from_dt(g, t, dt);
  at.x += delta.x;
  at.y += delta.y;

  UNLIKELY if (is_oob(at)) {
    ThingEvent e {
        .reason     = "oob",                        //
        .event_type = THING_EVENT_LIFESPAN_EXPIRED, //
    };

    thing_dead(g, v, l, t, e);
    return;
  }

  //
  // No need to push/pop if on the same tile
  //
  if (at != old_at) {
    (void) thing_pop(g, v, t);
    thing_at_set(t, at);
    thing_update_pos(g, v, l, t);
    if (! thing_push(g, v, l, t)) {
      return;
    }
  } else {
    thing_at_set(t, at);
    thing_update_pos(g, v, l, t);
  }

  thing_on_moved(g, v, l, t);

  thing_collision_handle_interpolated(g, v, l, t, old_at);
  THING_LOG(t, "post move of delta %f,%f dt %f", delta.x, delta.y, t->thing_dt);
}
