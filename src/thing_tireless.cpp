//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_main.hpp"
#include "my_thing.hpp"
#include "my_thing_inlines.hpp"
#include "my_tp.hpp"
#include "my_types.hpp"

[[nodiscard]] auto thing_is_tireless(Gamep g, Levelsp v, Levelp l, Thingp me) -> bool
{
  TRACE_DEBUG();

  if (me == nullptr) {
    ERR("no thing pointer");
    return false;
  }

  FOR_ALL_BUFFS(g, v, l, me, buff)
  {
    if (thing_is_tireless(g, v, l, buff)) {
      return true;
    }
  }

  return tp_flag(thing_tp(me), is_tireless) != 0;
}
