//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_fpoint.hpp"
#include "my_game.hpp"
#include "my_globals.hpp"
#include "my_level.hpp"
#include "my_main.hpp"
#include "my_math.hpp"
#include "my_thing.hpp"

void thing_projectile_fire_at(Gamep g, Levelsp v, Levelp l, Thingp me, const std::string &what, const fpoint target)
{
  TRACE_NO_INDENT();

  auto delta = target - make_fpoint(thing_at(me));

  auto  angle = angle_radians(delta);
  float s;
  float c;
  sincosf(angle, &s, &c);

  fpoint at     = thing_real_at(me);
  float  offset = 0.5;
  at.x += c * offset;
  at.y += s * offset;

  auto projectile = thing_spawn(g, v, l, tp_find_mand(what), at);
  if (projectile) {
    projectile->angle = angle;
  }
}

void thing_projectile_fire_at(Gamep g, Levelsp v, Levelp l, Thingp me, const std::string &what, const spoint target)
{
  thing_projectile_fire_at(g, v, l, me, what, make_fpoint(target));
}

void thing_projectile_move(Gamep g, Levelsp v, Levelp l, Thingp t, float dt)
{
  TRACE_NO_INDENT();

  float s;
  float c;
  sincosf(t->angle, &s, &c);
  fpoint at = thing_real_at(t);
  at.x += c * dt;
  at.y += s * dt;

  if (is_oob(at)) {
    ThingEvent e {
        .reason     = "oob",                        //
        .event_type = THING_EVENT_LIFESPAN_EXPIRED, //
    };

    thing_dead(g, v, l, t, e);
    return;
  }

  thing_at_set(t, at);

  thing_update_pos(g, v, l, t);
}
