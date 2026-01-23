//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_level.hpp"
#include "my_thing.hpp"
#include "my_thing_inlines.hpp"
#include "my_tp.hpp"

//
// Hot animation time step
//
void thing_hot_time_step(Gamep g, Levelsp v, Levelp l, Thingp t, int time_step)
{
  TRACE_NO_INDENT();

  auto T = thing_temperature(t);
  if (! thing_is_physics_temperature(t)) {
    return;
  }

  auto tp    = thing_tp(t);
  auto limit = std::max(tp_temperature_burns_at_get(tp), tp_temperature_melts_at_get(tp)) / 2;
  if (! limit) {
    return;
  }

  auto time_damp = 3;
  auto dt        = time_step / time_damp;
  if (! dt) {
    dt = time_step;
  }

  auto is_hot = thing_is_hot_decr(g, v, l, t, dt);
  if (! is_hot) {
    if (T > limit) {
      thing_is_hot_set(g, v, l, t, 255);
    }
  }
  if (is_hot) {
    THING_TOPCON(t, "temp %d", thing_temperature(t));
  }
}
