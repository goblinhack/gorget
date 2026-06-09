//
// Copyright goblinhack@gmail.com
//

#include <limits>
#include <utility>

#include "my_callstack.hpp"
#include "my_main.hpp"
#include "my_thing.hpp"
#include "my_types.hpp"

[[nodiscard]] auto thing_speed(Thingp t) -> int
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return 0;
  }
  return t->_speed;
}

[[nodiscard]] auto thing_speed_set(Gamep g, Levelsp v, Levelp l, Thingp t, int val) -> int
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return 0;
  }

  if (std::cmp_greater(val, std::numeric_limits< decltype(t->_speed) >::max())) {
    thing_err(t, "value overflow: %d", val);
    return 0;
  }

  return t->_speed = val;
}

[[nodiscard]] auto thing_speed_incr(Gamep g, Levelsp v, Levelp l, Thingp t, int val) -> int
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return 0;
  }
  return t->_speed += val;
}

[[nodiscard]] auto thing_speed_decr(Gamep g, Levelsp v, Levelp l, Thingp t, int val) -> int
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return 0;
  }
  if (static_cast< int >(t->_speed) - val <= 0) {
    return t->_speed = 0;
  }
  return t->_speed -= val;
}
