//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_thing_inlines.hpp"

auto thing_is_immune_to(Thingp t, ThingEventType val) -> bool
{
  TRACE();

  auto *tp = thing_tp(t);

  return tp_is_immune_to(tp, val);
}
