//
// Copyright goblinhack@gmail.com
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

void levels_stats_dump(Gamep g)
{
  TRACE_NO_INDENT();

  auto v = game_levels_get(g);
  if (! v) {
    return;
  }

  LOG("Level stats:");
  LOG("- Total memory:       %lu Mb", sizeof(Levels) / (1024 * 1024));
  LOG("- Per level memory:   %lu Kb", sizeof(Level) / (1024));
  LOG("- Thing AI:           %lu Mb", sizeof(v->thing_ai) / (1024 * 1024));
  LOG("- Thing structs:      %lu Mb", sizeof(v->thing_body) / (1024 * 1024));
  LOG("- Levels:             %lu Mb", sizeof(v->level) / (1024 * 1024));
  LOG("- Thing size:         %lu b", sizeof(Thing));
  LOG("- Max things:         %u", THING_COMMON_ID_BASE - 1);

  thing_stats_dump(g, v);
}

Levelsp levels_memory_alloc(Gamep g)
{
  LOG("Levels alloc memory");
  TRACE_NO_INDENT();

  auto v = game_levels_get(g);
  if (v) {
    ERR("levels already allocated");
    return v;
  }

  //
  // Allocate the level as a flat C structure to allow history rewind
  //
  // NOTE: if we use "new" here, the initialization is visibly slower.
  // DO NOT USE C++ classes or types
  //
  v = (Levelsp) myzalloc(sizeof(*v), "v");
  if (! v) {
    return nullptr;
  }

  return v;
}

static void levels_memory_free(Gamep g, Levelsp v)
{
  LOG("Levels free memory");
  TRACE_NO_INDENT();

  myfree(v);

  game_levels_set(g, nullptr);
}

void levels_destroy(Gamep g, Levelsp v)
{
  LOG("Levels destroy");
  TRACE_AND_INDENT();

  Levelp l;

  FOR_ALL_LEVELS(g, v, l)
  {
    TRACE_NO_INDENT();
    level_destroy(g, v, l);
  }

  levels_memory_free(g, v);
}

Levelp level_change(Gamep g, Levelsp v, int level_num)
{
  LOG("Level change to %u", level_num);
  TRACE_AND_INDENT();

  Level *l = game_level_get(g, v, level_num);

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

  LOG("Level destroy %u", l->level_num);
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

  auto tp_wall       = tp_random(is_wall);
  auto tp_rock       = tp_random(is_rock);
  auto tp_water      = tp_random(is_water);
  auto tp_deep_water = tp_random(is_deep_water);
  auto tp_door       = tp_find_mand("door");
  auto tp_floor      = tp_find_mand("floor");
  auto tp_exit       = tp_find_mand("exit");
  auto tp_player     = tp_find_mand("player");
  //  auto tp_entrance = tp_find_mand("entrance");

  for (auto y = 0; y < MAP_HEIGHT; y++) {
    for (auto x = 0; x < MAP_WIDTH; x++) {
      auto offset = (row_len * y) + x;
      auto c      = in[ offset ];
      Tpp  tp     = nullptr;
      Tpp  tp2    = nullptr;

      bool need_floor = false;

      switch (c) {
        case CHARMAP_CHASM :
          tp = nullptr; /* todo */
          continue;
        case CHARMAP_WALL :
          need_floor = true;
          tp         = tp_wall;
          break;
        case CHARMAP_JOIN :
          need_floor = true;
          tp         = tp_door;
          break;
        case CHARMAP_TREASURE1 :
          need_floor = true;
          tp         = nullptr; /* todo */
          break;
        case CHARMAP_TREASURE2 :
          need_floor = true;
          tp         = nullptr; /* todo */
          break;
        case CHARMAP_TELEPORT :
          need_floor = true;
          tp         = nullptr; /* todo */
          break;
        case CHARMAP_FOLIAGE :
          need_floor = true;
          tp         = nullptr; /* todo */
          break;
        case CHARMAP_DEEP_WATER :
          need_floor = true;
          tp         = tp_deep_water;
          tp2        = tp_water;
          break;
        case CHARMAP_WATER :
          need_floor = true;
          tp         = tp_water;
          break;
        case CHARMAP_BARREL :
          need_floor = true;
          tp         = nullptr; /* todo */
          break;
        case CHARMAP_PILLAR :
          need_floor = true;
          tp         = nullptr; /* todo */
          break;
        case CHARMAP_TRAP :
          need_floor = true;
          tp         = nullptr; /* todo */
          break;
        case CHARMAP_LAVA :
          need_floor = true;
          tp         = nullptr; /* todo */
          break;
        case CHARMAP_BRIDGE :
          tp = nullptr; /* todo */
          break;
        case CHARMAP_BRAZIER :
          need_floor = true;
          tp         = nullptr; /* todo */
          break;
        case CHARMAP_DOOR :
          need_floor = true;
          tp         = nullptr; /* todo */
          break;
        case CHARMAP_SECRET_DOOR :
          need_floor = true;
          tp         = nullptr; /* todo */
          break;
        case CHARMAP_DRY_GRASS :
          need_floor = true;
          tp         = nullptr; /* todo */
          break;
        case CHARMAP_MONST1 :
          need_floor = true;
          tp         = nullptr; /* todo */
          break;
        case CHARMAP_MONST2 :
          need_floor = true;
          tp         = nullptr; /* todo */
          break;
        case CHARMAP_MOB1 :
          need_floor = true;
          tp         = nullptr; /* todo */
          break;
        case CHARMAP_MOB2 :
          need_floor = true;
          tp         = nullptr; /* todo */
          break;
        case CHARMAP_ENTRANCE :
          need_floor = true;
          if (l->level_num == 0) {
            tp = tp_player;
          } else {
            // tp = tp_entrance;
            tp = nullptr; /* todo */
          }
          break;
        case CHARMAP_EXIT :
          need_floor = true;
          tp         = tp_exit;
          break;
        case CHARMAP_KEY :
          need_floor = true;
          tp         = nullptr; /* todo */
          break;
        case CHARMAP_FLOOR :
          need_floor = true;
          tp         = nullptr; /* todo */
          break;
        case CHARMAP_EMPTY :
          need_floor = true;
          tp         = tp_rock;
          break;
        default :
          if (! g_opt_test_levels) {
            //            DIE("unexpected map char '%c'", c);
          }
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

      if (tp2) {
        t = thing_init(g, v, l, tp2, point(x, y));
        if (t) {
          thing_push(g, v, l, t);
        }
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

  int  zoom = game_map_zoom_get(g);
  auto dw   = TILE_WIDTH * zoom;
  auto dh   = TILE_HEIGHT * zoom;

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

  int max_pix_x = (MAP_WIDTH * dw) - game_map_fbo_width_get(g);
  int max_pix_y = (MAP_HEIGHT * dh) - game_map_fbo_height_get(g);

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

  int tmp_maxx = (v->pixel_map_at.x + game_map_fbo_width_get(g)) / dw;
  int tmp_maxy = (v->pixel_map_at.y + game_map_fbo_height_get(g)) / dh;

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
