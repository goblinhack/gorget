//
// Copyright goblinhack@gmail.com
//

// REMOVED #include "my_ascii.hpp"
// REMOVED #include "my_backtrace.hpp"
#include "my_callstack.hpp"
// REMOVED #include "my_console.hpp"
// REMOVED #include "my_log.hpp"
// REMOVED #include "my_sdl_event.hpp"
// REMOVED #include "my_sdl_proto.hpp"
// REMOVED #include "my_sprintf.hpp"
// REMOVED #include "my_string.hpp"
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
