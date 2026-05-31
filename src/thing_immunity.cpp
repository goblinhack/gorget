//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_thing_inlines.hpp"
#include "my_tp.hpp"
#include "my_types.hpp"

[[nodiscard]] auto thing_is_immune_to(Thingp t, ThingEventType val) -> bool
{
  TRACE();

  auto *tp = thing_tp(t);

  return tp_is_immune_to(tp, val);
}

[[nodiscard]] auto thing_is_resistant_to(Thingp t, ThingEventType val) -> bool
{
  TRACE();

  auto *tp = thing_tp(t);

  return tp_is_resistant_to(tp, val);
}
