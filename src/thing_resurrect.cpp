//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_main.hpp"
#include "my_thing.hpp"
#include "my_types.hpp"

[[nodiscard]] auto thing_ticks_to_stay_dead(Gamep g, Levelsp v, Levelp l, Thingp t) -> int
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return 0;
  }
  return t->_ticks_to_stay_dead;
}

[[nodiscard]] auto thing_ticks_to_stay_dead_set(Gamep g, Levelsp v, Levelp l, Thingp t, int val) -> int
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return 0;
  }
  return t->_ticks_to_stay_dead = val;
}

[[nodiscard]] auto thing_ticks_to_stay_dead_incr(Gamep g, Levelsp v, Levelp l, Thingp t, int val) -> int
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return 0;
  }
  return t->_ticks_to_stay_dead += val;
}

[[nodiscard]] auto thing_ticks_to_stay_dead_decr(Gamep g, Levelsp v, Levelp l, Thingp t, int val) -> int
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return 0;
  }
  if (static_cast< int >(t->_ticks_to_stay_dead) - val <= 0) {
    return t->_ticks_to_stay_dead = 0;
  }
  return t->_ticks_to_stay_dead -= val;
}

[[nodiscard]] auto thing_ticks_to_stay_dead_initial(Thingp t) -> int
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return 0;
  }
  return t->_ticks_to_stay_dead_initial;
}

[[nodiscard]] auto thing_ticks_to_stay_dead_initial_set(Gamep g, Levelsp v, Levelp l, Thingp t, int val) -> int
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return 0;
  }
  return t->_ticks_to_stay_dead_initial = val;
}

[[nodiscard]] auto thing_ticks_to_stay_dead_initial_incr(Gamep g, Levelsp v, Levelp l, Thingp t, int val) -> int
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return 0;
  }
  return t->_ticks_to_stay_dead_initial += val;
}

[[nodiscard]] auto thing_ticks_to_stay_dead_initial_decr(Gamep g, Levelsp v, Levelp l, Thingp t, int val) -> int
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return 0;
  }
  if (static_cast< int >(t->_ticks_to_stay_dead_initial) - val <= 0) {
    return t->_ticks_to_stay_dead_initial = 0;
  }
  return t->_ticks_to_stay_dead_initial -= val;
}
