//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_level.hpp"
#include "my_time.hpp"

//
// Hidden anim time step
//
void thing_hidden_time_step(Gamep g, Levelsp v, Levelp l, Thingp t, int time_step)
{
  TRACE();

  auto pulse = THING_IS_HIDDEN_PULSE_MS; // ms
  auto mid   = pulse / 2;
  auto n     = time_ms_cached() % pulse;

  if (n > mid) {
    n = mid - n;
  }

  auto i        = static_cast< int >((255 / static_cast< float >(mid)) * static_cast< float >(n));
  t->_is_hidden = ((static_cast< uint8_t >(i)) / 2) + 100;

  if (t->_is_hidden == 0u) {
    t->_is_hidden = 1;
  }
}

void thing_is_hidden_set(Gamep g, Levelsp v, Levelp l, Thingp t, bool val)
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return;
  }

  if (val) {
    if (t->_is_hidden != 0u) {
      return;
    }

    t->_is_hidden = 100;
  } else {
    t->_is_hidden = 0;
  }
}
