//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
// REMOVED #include "my_level.hpp"
// REMOVED #include "my_thing.hpp"
#include "my_thing_inlines.hpp"

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
