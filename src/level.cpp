//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_charmap.hpp"
#include "my_game.hpp"
#include "my_game_defs.hpp"
#include "my_level.hpp"
#include "my_main.hpp"
#include "my_ptrcheck.hpp"
#include "my_tile.hpp"
#include "my_tp.hpp"

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

  int z = 0;
  level_dungeon_create_and_place(l, z);
  level_assign_tiles(l, z);
  level_scroll_warp_to_player(l);

  return l;
}

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

void level_destructor(Levelp l)
{
  TRACE_NO_INDENT();

  myfree(l);
}

bool level_set_thing_id(Levelp l, int x, int y, int z, int slot, ThingId id)
{
  if (level_is_oob(l, x, y)) {
    return false;
  }
  l->thing_id[ x ][ y ][ z ][ slot ] = id;
  return true;
}

ThingId level_get_thing_id(Levelp l, int x, int y, int z, int slot)
{
  if (level_is_oob(l, x, y)) {
    return 0;
  }
  return l->thing_id[ x ][ y ][ z ][ slot ];
}

bool level_flag(Levelp l, ThingFlag f, int x, int y, int z)
{
  FOR_ALL_THINGS_AND_TPS_AT(l, it, it_tp, x, y, z)
  {
    auto it_tp = level_thing_tp(l, it);
    if (tp_flag(it_tp, f)) {
      return true;
    }
  }
  return false;
}

bool level_is_oob(Level *l, int x, int y)
{
  if (! l) {
    return true;
  }
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

void level_map_set(Levelp l, int z, const char *in)
{
  TRACE_NO_INDENT();
  const auto row_len      = MAP_WIDTH;
  auto       expected_len = row_len * MAP_HEIGHT;

  if ((int) strlen(in) != expected_len) {
    DIE("bad map size, expected %d, got %d", (int) strlen(in), (int) expected_len);
  }

  auto tp_wall    = tp_random(is_wall);
  auto tp_door    = tp_find_mand("door");
  auto tp_floor   = tp_find_mand("floor");
  auto tp_exit    = tp_find_mand("exit");
  auto tp_player1 = tp_find_mand("player1");
  auto tp_player2 = tp_find_mand("player2");
  auto tp_player3 = tp_find_mand("player3");
  auto tp_player4 = tp_find_mand("player4");

  for (auto y = 0; y < MAP_HEIGHT; y++) {
    for (auto x = 0; x < MAP_WIDTH; x++) {
      auto offset = (row_len * y) + x;
      auto c      = in[ offset ];
      Tpp  tp     = nullptr;

      bool need_floor = false;

      switch (c) {
        case CHARMAP_WALL :
          need_floor = true;
          tp         = tp_wall;
          break;
        case CHARMAP_DOOR :
          need_floor = true;
          tp         = tp_door;
          break;
        case CHARMAP_TREASURE : break;
        case CHARMAP_MONST1 : break;
        case CHARMAP_PLAYER1 :
          need_floor = true;
          tp         = tp_player1;
          break;
        case CHARMAP_PLAYER2 :
          need_floor = true;
          tp         = tp_player2;
          break;
        case CHARMAP_PLAYER3 :
          need_floor = true;
          tp         = tp_player3;
          break;
        case CHARMAP_PLAYER4 :
          need_floor = true;
          tp         = tp_player4;
          break;
        case CHARMAP_EXIT :
          need_floor = true;
          tp         = tp_exit;
          break;
        case CHARMAP_KEY : need_floor = true; break;
        case CHARMAP_EMPTY : need_floor = true; break;
        default : DIE("unexpected map char '%c'", c);
      }

      if (need_floor) {
        auto tp = tp_floor;
        auto t  = level_thing_init(l, tp, x, y, z);
        if (t) {
          level_thing_push(l, t);
        }
      }

      if (! tp) {
        continue;
      }

      auto t = level_thing_init(l, tp, x, y, z);
      if (t) {
        level_thing_push(l, t);
      }
    }
  }
}

bool level_is_same_type(Levelp l, int x, int y, int z, Tpp tp)
{
  TRACE_NO_INDENT();

  if (! l) {
    return false;
  }

  if (level_is_oob(l, x, y)) {
    return false;
  }

  auto id = l->thing_id[ x ][ y ][ z ][ tp_z_depth_get(tp) ];
  if (! id) {
    return false;
  }

  return id == tp_id_get(tp);
}

void level_bounds_set(Levelp l)
{
  TRACE_NO_INDENT();

  auto dw = TILE_WIDTH;
  auto dh = TILE_HEIGHT;

  //
  // The number of tiles additionally to draw to avoid clipping
  //
  auto clipping_border = 2;

  //
  // Set the scroll bounds
  //
  if (l->pixel_map_at_x < 0) {
    l->pixel_map_at_x = 0;
  }
  if (l->pixel_map_at_y < 0) {
    l->pixel_map_at_y = 0;
  }

  //
  // Square map
  //
  auto max_pix_x = (MAP_WIDTH * dw) - game_pix_height_get(game);
  auto max_pix_y = (MAP_HEIGHT * dh) - game_pix_height_get(game);

  if (l->pixel_map_at_x > max_pix_x) {
    l->pixel_map_at_x = max_pix_x;
  }
  if (l->pixel_map_at_y > max_pix_y) {
    l->pixel_map_at_y = max_pix_y;
  }

  //
  // Set the tile bounds
  //
  int tmp_minx = l->pixel_map_at_x / dw;
  int tmp_miny = l->pixel_map_at_y / dh;
  tmp_minx -= clipping_border;
  tmp_minx -= clipping_border;

  if (tmp_minx < 0) {
    tmp_minx = 0;
  }
  if (tmp_miny < 0) {
    tmp_miny = 0;
  }

  int tmp_maxx = (l->pixel_map_at_x + game_map_pix_width_get(game)) / dw;
  int tmp_maxy = (l->pixel_map_at_y + game_map_pix_height_get(game)) / dh;

  tmp_maxx += clipping_border;
  tmp_maxy += clipping_border;

  if (tmp_maxx >= MAP_WIDTH) {
    tmp_maxx = MAP_WIDTH;
  }
  if (tmp_maxy >= MAP_HEIGHT) {
    tmp_maxy = MAP_HEIGHT;
  }

  l->minx = tmp_minx;
  l->miny = tmp_miny;
  l->maxx = tmp_maxx;
  l->maxy = tmp_maxy;
}
