//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_level.hpp"
#include "my_main.hpp"
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

  //
  // If halfway towards burning/melting, make it pulse
  //
  auto *tp          = thing_tp(t);
  auto upper_limit = std::max(tp_temperature_burns_at_get(tp), tp_temperature_melts_at_get(tp));
  if (upper_limit == 0) {
    return;
  }

  auto lower_limit = tp_temperature_initial_get(tp);
  if (lower_limit == 0) {
    return;
  }

  auto threshold = ((upper_limit - lower_limit) / 2) + lower_limit;

  if (__unused__) {
    THING_LOG(t, "lower_limit %d upper_limit %d threshold %d temp %d", lower_limit, upper_limit, threshold, T);
  }

  //
  // Slow the pulsing down a bit
  //
  auto time_damp = 3;
  auto dt        = time_step / time_damp;
  if (dt == 0) {
    dt = time_step;
  }

  auto is_hot = thing_is_hot_decr(g, v, l, t, dt);
  if (is_hot == 0) {
    if (T > threshold) {
      thing_is_hot_set(g, v, l, t, 255);
    }
  }
}
