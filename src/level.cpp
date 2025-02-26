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

Levelsp levels_create(Gamep g)
{
  LOG("Levels create");
  TRACE_AND_INDENT();

  //
  // Allocate the level as a flat C structure to allow history rewind
  //
  // NOTE: if we use "new" here, the initialization is visibly slower.
  // DO NOT USE C++ classes or types
  //
  Levelsp v;
  LOG("Levels memory:  %lu Mb", sizeof(Levels) / (1024 * 1024));
  LOG("Level memory:   %lu Mb", sizeof(Level) / (1024 * 1024));
  LOG("Thing AI:       %lu Mb", sizeof(v->thing_ai) / (1024 * 1024));
  LOG("Thing structs:  %lu Mb", sizeof(v->thing_body) / (1024 * 1024));
  LOG("Thing levels:   %lu Mb", sizeof(v->level) / (1024 * 1024));
  LOG("Thing size:     %lu b", sizeof(Thing));
  LOG("Max things:     %u", THING_COMMON_ID_BASE - 1);

  v = (Levelsp) myzalloc(sizeof(*v), "v");
  if (! v) {
    return nullptr;
  }

  level_create(g, v, point(0, 0));

  return v;
}

void levels_destroy(Gamep g, Levelsp v)
{
  LOG("Levels fini");
  TRACE_AND_INDENT();

  Levelp l;

  FOR_ALL_LEVELS(g, v, l)
  {
    TRACE_NO_INDENT();
    level_destroy(g, v, l);
  }

  myfree(v);
  game_levels_set(g, nullptr);
}

#if 0
void level_map_constructor(Gamep g, Levelsp v, Levelp l)
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

Levelp level_create(Gamep g, Levelsp v, point level_num)
{
  LOG("Level create %u,%u", level_num.x, level_num.y);
  TRACE_AND_INDENT();

  auto l = game_level_get(g, v, level_num.x, level_num.y);
  memset(l, 0, sizeof(*l));
  l->level_num   = level_num;
  l->initialized = true;

  level_dungeon_create_and_place(g, v, l);
  level_assign_tiles(g, v, l);
  level_scroll_warp_to_player(g, v);

  return l;
}

void level_destroy(Gamep g, Levelsp v, Levelp l)
{
  TRACE_NO_INDENT();
  if (! l || ! l->initialized) {
    return;
  }

  LOG("Level destroy %u,%u", l->level_num.x, l->level_num.y);
  TRACE_AND_INDENT();

  FOR_ALL_THINGS_ON_LEVEL(g, v, l, t) { thing_fini(g, v, l, t); }
  memset(l, 0, sizeof(*l));
}

bool level_set_thing_id_at(Gamep g, Levelsp v, Levelp l, point p, int slot, ThingId id)
{
  if (is_oob(p)) {
    return false;
  }
  l->thing_id[ p.x ][ p.y ][ slot ] = id;
  return true;
}

ThingId level_get_thing_id_at(Gamep g, Levelsp v, Levelp l, point p, int slot)
{
  if (is_oob(p)) {
    return 0;
  }
  return l->thing_id[ p.x ][ p.y ][ slot ];
}

bool level_flag(Gamep g, Levelsp v, Levelp l, ThingFlag f, point p)
{
  FOR_ALL_THINGS_AND_TPS_AT(g, v, l, it, it_tp, p)
  {
    if (tp_flag(it_tp, f)) {
      return true;
    }
  }
  return false;
}

bool is_oob(point p)
{
  if (p.x < 0) {
    return true;
  }
  if (p.y < 0) {
    return true;
  }
  if (p.x >= MAP_WIDTH) {
    return true;
  }
  if (p.y >= MAP_HEIGHT) {
    return true;
  }
  return false;
}

void level_map_set(Gamep g, Levelsp v, Levelp l, const char *in)
{
  TRACE_NO_INDENT();
  const auto row_len      = MAP_WIDTH;
  auto       expected_len = row_len * MAP_HEIGHT;

  if ((int) strlen(in) != expected_len) {
    DIE("bad map size, expected %d, got %d", (int) strlen(in), (int) expected_len);
  }

  auto tp_wall   = tp_random(is_wall);
  auto tp_door   = tp_find_mand("door");
  auto tp_floor  = tp_find_mand("floor");
  auto tp_exit   = tp_find_mand("exit");
  auto tp_player = tp_find_mand("player");

  for (auto y = 0; y < MAP_HEIGHT; y++) {
    for (auto x = 0; x < MAP_WIDTH; x++) {
      auto offset = (row_len * y) + x;
      auto c      = in[ offset ];
      Tpp  tp     = nullptr;

      bool need_floor = false;

      switch (c) {
        case CHARMAP_CHASM : continue;
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
        case CHARMAP_PLAYER :
          need_floor = true;
          tp         = tp_player;
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
        auto tp_add = tp_floor;
        auto t      = thing_init(g, v, l, tp_add, point(x, y));
        if (t) {
          thing_push(g, v, l, t);
        }
      }

      if (! tp) {
        continue;
      }

      auto t = thing_init(g, v, l, tp, point(x, y));
      if (t) {
        thing_push(g, v, l, t);
      }
    }
  }
}

bool level_is_same_obj_type_at(Gamep g, Levelsp v, Levelp l, point p, Tpp tp)
{
  TRACE_NO_INDENT();

  if (! l) {
    return false;
  }

  if (is_oob(p)) {
    return false;
  }

  for (auto slot = 0; slot < MAP_SLOTS; slot++) {
    Tpp    it_tp;
    Thingp it = thing_and_tp_get_at(g, v, l, p, slot, &it_tp);
    if (! it) {
      continue;
    }
    if (it_tp == tp) {
      return true;
    }
  }
  return false;
}

void level_bounds_set(Gamep g, Levelsp v)
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
  if (v->pixel_map_at.x < 0) {
    v->pixel_map_at.x = 0;
  }
  if (v->pixel_map_at.y < 0) {
    v->pixel_map_at.y = 0;
  }

  int max_pix_x = (MAP_WIDTH * dw) - game_pix_width_get(g);
  int max_pix_y = (MAP_HEIGHT * dh) - game_pix_height_get(g);

  if (v->pixel_map_at.x > max_pix_x) {
    v->pixel_map_at.x = max_pix_x;
  }
  if (v->pixel_map_at.y > max_pix_y) {
    v->pixel_map_at.y = max_pix_y;
  }

  //
  // Set the tile bounds
  //
  int tmp_minx = v->pixel_map_at.x / dw;
  int tmp_miny = v->pixel_map_at.y / dh;
  tmp_minx -= clipping_border;
  tmp_minx -= clipping_border;

  if (tmp_minx < 0) {
    tmp_minx = 0;
  }
  if (tmp_miny < 0) {
    tmp_miny = 0;
  }

  int tmp_maxx = (v->pixel_map_at.x + game_map_pix_width_get(g)) / dw;
  int tmp_maxy = (v->pixel_map_at.y + game_map_pix_height_get(g)) / dh;

  tmp_maxx += clipping_border;
  tmp_maxy += clipping_border;

  if (tmp_maxx >= MAP_WIDTH) {
    tmp_maxx = MAP_WIDTH;
  }
  if (tmp_maxy >= MAP_HEIGHT) {
    tmp_maxy = MAP_HEIGHT;
  }

  v->minx = tmp_minx;
  v->miny = tmp_miny;
  v->maxx = tmp_maxx;
  v->maxy = tmp_maxy;
}
