//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_game.hpp"
#include "my_level.hpp"
#include "my_main.hpp"
// REMOVED #include "my_random.hpp"
// REMOVED #include "my_tile.hpp"
// REMOVED #include "my_tp.hpp"
// REMOVED #include "my_types.hpp"

// REMOVED #include <cinttypes>
// REMOVED #include <iostream>
// REMOVED #include <map>
// REMOVED #include <mutex>
// REMOVED #include <sstream>
// REMOVED #include <string.h>
// REMOVED #include <string>

Thingp thing_find_optional(Gamep g, Levelsp v, ThingId id)
{
  TRACE_NO_INDENT();

  if (! id) {
    return nullptr;
  }

  auto thing_id = id;
  auto index    = THING_COMMON_ID_GET(thing_id);

  ASSERT_EX(index, <, (1 << THING_COMMON_ID_BITS));

  auto t = &v->thing_body[ index ];
  if (! t) {
    return nullptr;
  }

  if (t->id == thing_id) {
    return t;
  }

  return nullptr;
}

Thingp thing_find(Gamep g, Levelsp v, ThingId id)
{
  TRACE_NO_INDENT();

  auto thing_id = id;
  auto index    = THING_COMMON_ID_GET(thing_id);

  ASSERT_EX(index, <, (1 << THING_COMMON_ID_BITS));

  auto t = &v->thing_body[ index ];
  if (! t) {
    DIE("Thing not found for id, %" PRIx32 "", id);
  }

  if (t->id != id) {
    DIE("Thing found as id %" PRIx32 " but entropy mismatch for id, %" PRIx32 "", t->id, id);
  }

  return t;
}
