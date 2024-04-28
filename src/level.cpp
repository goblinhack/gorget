//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_level.hpp"
#include "my_ptrcheck.hpp"
#include "my_tile.hpp"

#if 0
void level_map_constructor(Levelp l)
{
  TRACE_NO_INDENT();

  for (;;) {

#if 0
    /*
     * Phase 1: create a framework for the level solution e.g.
     *
     *           v    v  * v
     *     1----1----1---S1
     *      >  <|>  <|>  <|
     *          |    |    |
     *          |    |    |
     *          |   *|v  *|
     *    s.    1----1----1
     *         ^?>  <|>  <
     *          ?    |
     *          ?    |
     *      v   ?   *|   * v
     *     2???s1???K1---D2
     *     |        ^ >  <|
     *     |              |
     *     |              |
     *     |   *    *    *|
     *     2---E2----2----2
     *    ^ >  <    <    <
     */
    auto ph1 = level_ph1();
    if (! ph1.ok) {
      CON("COULD NOT SOLVE PH1");
      continue;
    }
    ph1.dump();

    /*
     * Phase 2: create a set of rooms that satisfy the solution e.g.:
     *
     * 1111111111 1........1 1111111111 1111111111
     * 1111111111 1........1 1111111111 1111111111
     * 11........ 11...S..11 11......11 ........11
     * 11........ 11..111.11 11......11 ........11
     * 11........ 11..111.11 11......11 ........11
     * 11........ .......... .......... ........11
     * 11111..111 1111111111 11..111111 11..111111
     * 111111.111 1111111111 111.111111 11.1111111
     *
     * 111111s111 1111111111 111.111111 11.1111111
     * 111111..11 1111111111 111.111111 11.1111111
     * 11......11 11........ 11......11 11......11
     * 11......11 11........ 11......11 11......11
     * 11......11 11........ 11......11 11......11
     * 11......11 11........ .......... ........11
     * 111...1111 1111111111 1111..1111 11111..111
     * 1111s11111 1111111111 11111.1111 11111.1111
     *
     * 1111.11111 1111111111 11111.1111 11111.1111
     * 1111.11111 1111111111 11111.1111 1111....11
     * 11......11 11......11 11......11 11......11
     * 11......11 11......11 11......11 11......11
     * 11......11 11......11 11......11 11......11
     * 11........ .......... ........11 11......11
     * ...1111111 1111111111 1111111... 1111111111
     * .111111111 1111111111 111111111. 1111111111
     *
     * ..11111111 1111111111 111111111. 1111111111
     * ....111111 1111111111 111111111. 1111111111
     * 11......11 11........ 11........ ........11
     * 11......11 11........ 11......11 ........11
     * 11......11 11...E.... 11......11 ........11
     * 11......11 11..111... .......... ........11
     * 1111111111 1111111111 1111111111 1111111111
     * 1111111111 1111111111 1111111111 1111111111
     */
    auto ph2 = level_ph2(ph1);
    if (! ph2.ok) {
      CON("COULD NOT SOLVE PH2");
      continue;
    }
    ph2.dump();

    /*
     * Phase 3: Blocks joined and obstacles merged
     *
     * RRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRR
     * R11111...k1........1.11111111111111111111R
     * R......1111.111..S...11111111111111111111R
     * R...............111.111......11........11R
     * R.111...1..11.......111................11R
     * R.111................11................11R
     * R.....1111.................1...........11R
     * R1.........11111...1.1111.11|.11111111..1R
     * R1111......1111111111111111111111111111.1R
     * R1......H..1111111111111111111111111111.1R
     * R111...1H111.......11111111111111111111.1R
     * R1......H....11.11..111........11.......1R
     * R11111..H...........111........11......11R
     * R1...1..H....11111.1111........11......11R
     * R1...D..H...........11.................11R
     * R1..11111111........1...11111111..1111111R
     * R1.111111111111111111.1111111111.11111111R
     * R..111111111111111111.1111111111.11111111R
     * R...11111111111111111...11111111.11111111R
     * R1.........11......1111......111.......11R
     * R11........11......1111......1111......11R
     * R11........11......1111......1111......11R
     * R11....................................11R
     * R11111111111111111..11111111111111111..11R
     * R11111111111111111.111111111111111111.111R
     * R11111111111111111.111111111111111111s111R
     * R11......111111111.111111111111111111.111R
     * R1........111......1111......111.......11R
     * R1.........11......1111......111.......11R
     * R1E........11......1111......111.......11R
     * R1111..........................s.......11R
     * R11.1.1111.111111111111111111111111111111R
     * R11.1......111111111111111111111111111111R
     * RRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRR
     */
    auto ph3 = level_ph3(ph2);
    if (! ph3.ok) {
      CON("COULD NOT SOLVE PH3");
      continue;
    }

    /*
     * Phase 4: replace all chars with objects
     */
    auto ph4 = level_ph4(ph3);
    if (! ph4.ok) {
      CON("COULD NOT SOLVE PH4");
      continue;
    }
#endif

#if 0
    *level = ph4.data;
#endif

    return level;
  }
}
#endif

Levelp level_constructor(void)
{
  TRACE_NO_INDENT();

  //
  // Allocate the level as a flat C structure to allow history rewind
  //
  Levelp l = (Levelp) myzalloc(sizeof(*l), "l");
  if (! l) {
    return nullptr;
  }

  level_dungeon_create_and_place(l);
  level_assign_tiles(l);
  level_thing_player_create_and_place(l);
  level_scroll_warp_to_player(l);

  return l;
}

void level_destructor(Levelp l)
{
  TRACE_NO_INDENT();

  myfree(l);
}

bool is_oob(Level *l, int x, int y)
{
  if (x < 0) {
    return true;
  }
  if (y < 0) {
    return true;
  }
  if (x >= MAP_WIDTH) {
    return true;
  }
  if (y >= MAP_HEIGHT) {
    return true;
  }
  return false;
}

bool level_is_oob(Levelp l, int x, int y)
{
  if (x < 0) {
    return true;
  }
  if (y < 0) {
    return true;
  }
  if (x >= MAP_WIDTH) {
    return true;
  }
  if (y >= MAP_HEIGHT) {
    return true;
  }
  return false;
}

bool level_set_id(Levelp l, int x, int y, uint8_t slot, Id id)
{
  if (level_is_oob(l, x, y)) {
    return false;
  }
  l->obj[ x ][ y ][ slot ].id = id;
  return true;
}

void level_set_id_no_check(Levelp l, int x, int y, uint8_t slot, Id id) { l->obj[ x ][ y ][ slot ].id = id; }

Id level_get_id(Levelp l, int x, int y, uint8_t slot)
{
  if (level_is_oob(l, x, y)) {
    return 0;
  }
  return l->obj[ x ][ y ][ slot ].id;
}

Id level_get_id_no_check(Levelp l, int x, int y, uint8_t slot) { return l->obj[ x ][ y ][ slot ].id; }

bool level_set_tile(Levelp l, int x, int y, uint8_t slot, Tilep tile)
{
  if (level_is_oob(l, x, y)) {
    return false;
  }
  if (tile) {
    l->obj[ x ][ y ][ slot ].tile = tile_global_index(tile);
  } else {
    l->obj[ x ][ y ][ slot ].tile = 0;
  }
  return true;
}

void level_set_tile_no_check(Levelp l, int x, int y, uint8_t slot, Tilep tile)
{
  l->obj[ x ][ y ][ slot ].tile = tile_global_index(tile);
}

Tilep level_get_tile(Levelp l, int x, int y, uint8_t slot)
{
  if (level_is_oob(l, x, y)) {
    return nullptr;
  }
  return tile_index_to_tile(l->obj[ x ][ y ][ slot ].tile);
}

Tilep level_get_tile_no_check(Levelp l, int x, int y, uint8_t slot)
{
  return tile_index_to_tile(l->obj[ x ][ y ][ slot ].tile);
}
