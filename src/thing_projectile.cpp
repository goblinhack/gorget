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

//
// Add a projectile if possible
//
static auto thing_spawn_a_projectile(Gamep g, Levelsp v, Levelp l, Thingp me, Tpp what, const fpoint target) -> Thingp
{
  TRACE();

  if (me == nullptr) {
    return nullptr;
  }

  if (! thing_is_able_to_fire_weapons(me)) {
    thing_err(me, "thing trying to spawn projectiles when it cannot");
    return nullptr;
  }

  if (what == nullptr) {
    thing_err(me, "no projectile to spawn");
    return nullptr;
  }

  auto *ext_struct = thing_ext_struct(g, me);
  if (ext_struct == nullptr) {
    thing_err(me, "missing ext struct");
    return nullptr;
  }

  //
  // Too many projectiles
  //
  if (thing_fired_by_count_get(g, v, l, me) >= thing_fired_weapon_count_max(me)) {
    if (thing_is_player(me)) {
      topcon("Trying to fire too many projectiles!");
      return nullptr;
    }
    THING_DBG(me, "trying to fire too many projectiles");
    return nullptr;
  }

  //
  // Look for a free slot
  //
  FOR_ALL_WEAPON_SLOTS(g, v, l, me, slot, existing_projectile)
  {
    if (existing_projectile != nullptr) {
      continue;
    }

    //
    // Create the projectile. Should be no chance to fail now.
    //
    auto *new_projectile = thing_spawn(g, v, l, what, target);
    if (new_projectile == nullptr) {
      return nullptr;
    }

    memset(slot, 0, sizeof(*slot));
    slot->weapon_id             = new_projectile->id;
    new_projectile->fired_by_id = me->id;
    ext_struct->weapons.count++;

    THING_DBG(me, "spawned projectile %s", to_string(g, v, l, new_projectile).c_str());
    THING_DBG(new_projectile, "new born projectile");

    return new_projectile;
  }

  //
  // Out of slots; but we checked above
  //
  thing_err(me, "unexpectedly out of projectile slots");

  return nullptr;
}

static auto thing_projectile_get_delta_from_dt(Gamep g, Thingp t, float dt) -> fpoint
{
  TRACE();

  float s = 0;
  float c = 0;
  SINCOSF(t->angle, &s, &c);

  auto *player = thing_player(g);
  if (player == nullptr) [[unlikely]] {
    CROAK("no player struct found");
    return fpoint(0, 0);
  }

  const int   player_speed = thing_speed(player);
  const float t_speed      = thing_speed(t);
  const auto  tile_speed   = (t_speed / static_cast< float >(player_speed));

  auto delta = fpoint(c * dt * tile_speed, s * dt * tile_speed);
  if ((delta.x == 0) && (delta.y == 0)) {
    CROAK("no delta for projectile sin %f cos %f dt %f tile_speed %f", s, c, dt, tile_speed);
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

  fpoint proj_at = thing_real_at(me);

  //
  // Need a small fraction to account for comparisons of very similar floats where
  // we end up shooting the player upon firing
  //
  float const offset = thing_collision_radius(me) + tp_collision_radius(what) + THING_COLLISION_FIRING_OFFSET;
  proj_at.x += c * offset;
  proj_at.y += s * offset;

  auto *projectile = thing_spawn_a_projectile(g, v, l, me, what, proj_at);
  if (projectile == nullptr) {
    return false;
  }

  projectile->angle = static_cast< f16 >(angle);

  //
  // Set my direction based on where I fire
  //
  bpoint const dir    = make_bpoint(proj_at);
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

  auto delta = thing_projectile_get_delta_from_dt(g, me, dt);
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
