//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_globals.hpp"
#include "my_level.hpp"
#include "my_level_inlines.hpp"
#include "my_main.hpp"
#include "my_math.hpp"
#include "my_thing_callbacks.hpp"
#include "my_thing_inlines.hpp"

#include <cmath>

auto thing_projectile_fire_at(Gamep g, Levelsp v, Levelp l, Thingp me, Tpp what, const fpoint target) -> bool
{
  THING_DBG(me, "fire projectile");
  TRACE_INDENT();

  auto delta = target - make_fpoint(thing_at(me));

  if ((delta.x == 0) && (delta.y == 0)) {
    delta.x = 1;
  }

  auto  angle = angle_radians(delta);
  float s     = 0;
  float c     = 0;
  SINCOSF(angle, &s, &c);

  fpoint projectile_at = thing_real_at(me);

  //
  // Need a small fraction to account for comparisons of very similar floats where
  // we end up shooting the player upon firing
  //
  float const offset = thing_collision_radius(me) + tp_collision_radius(what) + THING_COLLISION_FIRING_OFFSET;
  projectile_at.x += c * offset;
  projectile_at.y += s * offset;

  auto *projectile = thing_spawn_weapon(g, v, l, me, what, projectile_at);
  if (projectile == nullptr) {
    return false;
  }

  projectile->angle = static_cast< f16 >(angle);

  //
  // Set my direction based on where I fire
  //
  bpoint const dir    = make_bpoint(projectile_at);
  bpoint const source = thing_at(me);
  thing_set_dir_from_delta(me, dir.x - source.x, dir.y - source.y);

  thing_is_moving_set(g, v, l, projectile);

  auto real_at = thing_real_at(projectile);

  if (compiler_unused) {
    THING_DBG(projectile, "%f,%f", real_at.x, real_at.y);
  }

  return true;
}

auto thing_projectile_fire_at(Gamep g, Levelsp v, Levelp l, Thingp me, Tpp what, const bpoint target) -> bool
{
  return thing_projectile_fire_at(g, v, l, me, what, make_fpoint(target));
}

void thing_projectile_move(Gamep g, Levelsp v, Levelp l, Thingp me, float dt)
{
  TRACE();

  THING_DBG(me, "move");

  fpoint const old_at = thing_real_at(me);
  auto         at     = old_at;

  auto *player = thing_player(g);
  if (player == nullptr) [[unlikely]] {
    ERR("no player struct found");
    return;
  }

  auto delta = thing_weapon_get_delta_from_dt(g, me, dt);
  at.x += delta.x;
  at.y += delta.y;

  if (is_oob(at)) [[unlikely]] {
    THING_DBG(me, "is oob");
    TRACE_INDENT();

    ThingEvent e {
        .reason     = "oob",                        //
        .event_type = THING_EVENT_LIFESPAN_EXPIRED, //
    };

    THING_DBG(me, "dead due to oob");
    TRACE_INDENT();

    thing_dead(g, v, l, me, e);
    return;
  }

  //
  // No need to push/pop if on the same tile
  //
  if (at != old_at) {
    (void) thing_pop(g, v, me);
    thing_at_set(g, v, l, me, at);
    thing_update_pos(g, v, l, me);
    if (! thing_push(g, v, l, me)) {
      THING_DBG(me, "could not push, oob?");
      TRACE_INDENT();

      ThingEvent e {
          .reason     = "oob",                        //
          .event_type = THING_EVENT_LIFESPAN_EXPIRED, //
      };

      THING_DBG(me, "dead due to oob on push");
      TRACE_INDENT();

      thing_dead(g, v, l, me, e);
      return;
    }
  } else {
    thing_at_set(g, v, l, me, at);
    thing_update_pos(g, v, l, me);
  }

  thing_on_moved(g, v, l, me);

  thing_collision_handle_interpolated(g, v, l, me, old_at);
  THING_DBG(me, "post move of delta %f,%f dt %f", delta.x, delta.y, (float) me->thing_dt);
}
