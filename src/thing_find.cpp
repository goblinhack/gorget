//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_game.hpp"
#include "my_globals.hpp"
#include "my_level.hpp"
#include "my_main.hpp"

//
// Slower version, packed with extra warnigns
//
Thingp thing_find_non_inline(Gamep g, Levelsp v, ThingId id)
{
#ifdef _DEBUG_BUILD_
  TRACE_NO_INDENT(); // expensive
#endif

  ThingIdPacked id_packed = {};
  id_packed.a.val         = id;
  auto arr_index          = id_packed.c.arr_index;

  auto t = &v->thing_body[ arr_index ];
  if (unlikely(! t)) {
    CROAK("Thing not found for as id 08%" PRIx32 //
          " (level: %" PRIu32                    //
          " id: %08" PRIx32                      //
          " entropy: %08" PRIx32                 //
          ")",                                   //
          id,                                    //
          id_packed.b.level_num,                 //
          id_packed.b.per_level_id,              //
          id_packed.b.entropy);
  }

  if (unlikely(t->id != id)) {
    ThingIdPacked id_found = {};
    id_found.a.val         = t->id;

    CROAK("Thing found as id 08%" PRIx32                         //
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
