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

void thing_fire_at(Gamep g, Levelsp v, Levelp l, Thingp me, const std::string &what, const fpoint target)
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

  thing_spawn(g, v, l, tp_find_mand(what), at);
}

void thing_fire_at(Gamep g, Levelsp v, Levelp l, Thingp me, const std::string &what, const spoint target)
{
  thing_fire_at(g, v, l, me, what, make_fpoint(target));
}
