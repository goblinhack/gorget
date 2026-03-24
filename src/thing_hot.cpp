//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_level.hpp"
#include "my_main.hpp"
#include "my_thing.hpp"
#include "my_thing_inlines.hpp"
#include "my_time.hpp"
#include "my_tp.hpp"

//
// Hot animation time step
//
void thing_hot_time_step(Gamep g, Levelsp v, Levelp l, Thingp t, int time_step)
{
  TRACE();

  auto T = thing_temperature(t);
  if (! thing_is_physics_temperature(t)) {
    return;
  }

  //
  // If halfway towards burning/melting, make it pulse
  //
  auto *tp          = thing_tp(t);
  auto  upper_limit = std::max(tp_temperature_burns_at_get(tp), tp_temperature_melts_at_get(tp));
  if (upper_limit == 0) {
    return;
  }

  auto lower_limit = tp_temperature_initial_get(tp);
  if (lower_limit == 0) {
    return;
  }

  auto threshold = ((upper_limit - lower_limit) / 2) + lower_limit;

  if (compiler_unused) {
    THING_DBG(t, "lower_limit %d upper_limit %d threshold %d temp %d", lower_limit, upper_limit, threshold, T);
  }

  if (T < threshold) {
    t->_is_hot = 0;
    return;
  }

  auto pulse = THING_IS_HOT_PULSE_MS; // ms
  auto mid   = pulse / 2;
  auto n     = time_ms_cached() % pulse;

  if (n > mid) {
    n = mid - n;
  }

  auto i     = static_cast< int >((255 / static_cast< float >(mid)) * static_cast< float >(n));
  t->_is_hot = ((static_cast< uint8_t >(i)) / 2) + 100;
}

//
// Hot animation time step
//
auto thing_is_hot_check(Gamep g, Levelsp v, Levelp l, Thingp t) -> bool
{
  TRACE();

  auto T = thing_temperature(t);
  if (! thing_is_physics_temperature(t)) {
    return false;
  }

  //
  // If halfway towards burning/melting, make it pulse
  //
  auto *tp          = thing_tp(t);
  auto  upper_limit = std::max(tp_temperature_burns_at_get(tp), tp_temperature_melts_at_get(tp));
  if (upper_limit == 0) {
    return false;
  }

  auto lower_limit = tp_temperature_initial_get(tp);
  if (lower_limit == 0) {
    return false;
  }

  auto threshold = ((upper_limit - lower_limit) / 2) + lower_limit;

  if (T < threshold) {
    thing_is_hot_set(g, v, l, t, false);
    return true;
  }

  thing_is_hot_set(g, v, l, t, true);
  return false;
}

void thing_is_hot_set(Gamep g, Levelsp v, Levelp l, Thingp t, bool val)
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return;
  }

  if (val) {
    if (t->_is_hot != 0U) {
      return;
    }

    t->_is_hot = 100;
  } else {
    t->_is_hot = 0;
  }
}
