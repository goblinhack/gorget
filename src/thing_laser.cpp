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
// Can't shoot too far
//
static auto thing_laser_truncate(Gamep g, Levelsp v, Levelp l, Thingp me, fpoint &to) -> float
{
  auto        curr_at                 = thing_real_at(me);
  float const how_far_i_want_to_shoot = distance(curr_at, to);
  float const how_far_i_can_shoot     = THING_LASER_DISTANCE_MAX;

  if (how_far_i_want_to_shoot > how_far_i_can_shoot) {
    //
    // Yep. Trying to shoot too far.
    //
    fpoint u = to - curr_at;
    u.unit();
    u *= how_far_i_can_shoot;

    to = curr_at + u;
  }

  return distance(curr_at, to);
}

auto thing_laser_fire_at(Gamep g, Levelsp v, Levelp l, Thingp me, Tpp what, const fpoint target) -> bool
{
  THING_DBG(me, "fire laser");
  TRACE_INDENT();

  //
  // Can't shoot too far
  //
  auto to       = target;
  auto distance = thing_laser_truncate(g, v, l, me, to);

  auto delta = to - make_fpoint(thing_at(me));

  if ((delta.x == 0) && (delta.y == 0)) {
    delta.x = 1;
  }

  auto  angle = angle_radians(delta);
  float s     = 0;
  float c     = 0;
  SINCOSF(angle, &s, &c);

  fpoint laser_at = thing_real_at(me);

  //
  // Need a small fraction to account for comparisons of very similar floats where
  // we end up shooting the player upon firing
  //
  float const offset = thing_collision_radius(me) + tp_collision_radius(what) + THING_COLLISION_FIRING_OFFSET;
  laser_at.x += c * offset;
  laser_at.y += s * offset;

  //
  // Create all the fragments of the laser
  //
  auto        laser_target_distance = floor(distance);
  const float avoid_gaps_in_tiles   = 0.94f;
  for (auto step = 0; step < laser_target_distance; step++) {
    if (0) {
      thing_topcon(me, "%f,%f step %d", laser_at.x, laser_at.y, step);
    }

    auto *laser = thing_spawn_weapon(g, v, l, me, what, laser_at);

    if (laser == nullptr) {
      return false;
    }

    laser->angle = static_cast< f16 >(angle);

    laser_at.x += c * avoid_gaps_in_tiles;
    laser_at.y += s * avoid_gaps_in_tiles;

    if (step == laser_target_distance - 1) {
      laser->anim_index = THING_LASER_DISTANCE_MAX - 1;
    } else {
      laser->anim_index = step;
    }
  }

  //
  // Set my direction based on where I fire
  //
  bpoint const dir    = make_bpoint(laser_at);
  bpoint const source = thing_at(me);
  thing_set_dir_from_delta(me, dir.x - source.x, dir.y - source.y);

  return true;
}

auto thing_laser_fire_at(Gamep g, Levelsp v, Levelp l, Thingp me, Tpp what, const bpoint target) -> bool
{
  return thing_laser_fire_at(g, v, l, me, what, make_fpoint(target));
}
