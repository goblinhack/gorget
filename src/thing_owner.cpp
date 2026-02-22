//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_thing_inlines.hpp"

auto top_owner(Gamep g, Levelsp v, Levelp l, Thingp t) -> Thingp
{
  TRACE_NO_INDENT();

  if (! static_cast< bool >(t->owner_id)) {
    return nullptr;
  }

  auto *o = thing_find(g, v, t->owner_id);
  if (o == nullptr) {
    return nullptr;
  }
  return top_owner(g, v, l, o);
}

auto immediate_owner(Gamep g, Levelsp v, Levelp l, Thingp t) -> Thingp
{
  TRACE_NO_INDENT();

  if (! static_cast< bool >(t->owner_id)) {
    return nullptr;
  }

  return thing_find(g, v, t->owner_id);
}
