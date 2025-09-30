//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_game.hpp"
#include "my_level.hpp"

Thingp thing_find_optional(Gamep g, Levelsp v, ThingId id)
{
  TRACE_NO_INDENT();

  if (! id) {
    return nullptr;
  }

  ThingIdPacked id_packed;
  id_packed.a.val = id;
  auto index      = id_packed.c.index;

  auto t = &v->thing_body[ index ];
  if (! t) {
    return nullptr;
  }

  if (t->id == id) {
    return t;
  }

  return nullptr;
}

Thingp thing_find(Gamep g, Levelsp v, ThingId id)
{
  TRACE_NO_INDENT();

  ThingIdPacked id_packed = {};
  id_packed.a.val         = id;
  auto index              = id_packed.c.index;

  auto t = &v->thing_body[ index ];
  if (! t) {
    DIE("Thing not found for as id 08%" PRIx32 //
        " (level: %" PRIu32                    //
        " id: %08" PRIx32                      //
        " entropy: %08" PRIx32                 //
        ")",                                   //
        id,                                    //
        id_packed.b.level_num,                 //
        id_packed.b.per_level_id,              //
        id_packed.b.entropy);
  }

  if (t->id != id) {
    ThingIdPacked id_found = {};
    id_found.a.val         = t->id;

    DIE("Thing found as id 08%" PRIx32                         //
        " (level: %" PRIu32                                    //
        " id: %08" PRIx32                                      //
        " entropy: %08" PRIx32                                 //
        "), but entropy mismatch with expected id, 08%" PRIx32 //
        " (level: %" PRIu32                                    //
        " id: %08" PRIx32                                      //
        " entropy: %08" PRIx32                                 //
        ")",                                                   //
        t->id,                                                 //
        id_found.b.level_num,                                  //
        id_found.b.per_level_id,                               //
        id_found.b.entropy,                                    //
        id,                                                    //
        id_packed.b.level_num,                                 //
        id_packed.b.per_level_id,                              //
        id_packed.b.entropy);
  }

  return t;
}
