//
// Copyright goblinhack@gmail.com
//

#include "my_ascii.hpp"
#include "my_backtrace.hpp"
#include "my_callstack.hpp"
#include "my_console.hpp"
#include "my_log.hpp"
#include "my_sdl_event.hpp"
#include "my_sdl_proto.hpp"
#include "my_sprintf.hpp"
#include "my_string.hpp"
#include "my_thing.hpp"

Thingp top_owner(Gamep g, Levelsp v, Levelp l, Thingp t)
{
  TRACE_NO_INDENT();

  if (! t->owner_id) {
    return nullptr;
  }

  auto o = thing_find(g, v, t->owner_id);
  if (! o) {
    return nullptr;
  }
  return top_owner(g, v, l, o);
}

Thingp immediate_owner(Gamep g, Levelsp v, Levelp l, Thingp t)
{
  TRACE_NO_INDENT();

  if (! t->owner_id) {
    return nullptr;
  }

  return thing_find(g, v, t->owner_id);
}
