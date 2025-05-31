//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_charmap.hpp"
#include "my_dice.hpp"
#include "my_game.hpp"
#include "my_game_defs.hpp"
#include "my_level.hpp"
#include "my_main.hpp"
#include "my_ptrcheck.hpp"
#include "my_tile.hpp"
#include "my_tp.hpp"
#include "my_ui.hpp"
#include "my_wids.hpp"

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

void level_dump(Gamep g, Levelsp v, Levelp l)
{
  TRACE_NO_INDENT();

  LOG("Level         : %d", l->level_num);
  LOG("Seed          : %u", l->info.seed_num);

  if (l->info.room_count) {
    LOG("Room count    : %d", l->info.room_count);
    LOG("Fragment count: %d", l->info.fragment_count);
    LOG("Treasure count: %d (normal:%d enhanced:%d)", l->info.treasure_count, l->info.treasure1_count,
        l->info.treasure2_count);
    LOG("Monst count   : %d (normal:%d enhanced:%d)", l->info.monst_count, l->info.monst1_count,
        l->info.monst2_count);
  }

  for (int y = 0; y < MAP_HEIGHT; y++) {
    std::string tmp;
    for (int x = 0; x < MAP_WIDTH; x++) {
      point p(x, y);

      tmp += l->debug[ x ][ y ];
    }
    LOG("[%s]", tmp.c_str());
  }

  LOG("-");
}

Levelsp levels_memory_alloc(Gamep g)
{
  LOG("Levels alloc memory");
  TRACE_NO_INDENT();

  auto v = game_levels_get(g);
  if (v) {
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

void level_entered(Gamep g, Levelsp v, Levelp l)
{
  LOG("Level entered: %u", l->level_num);
  TRACE_AND_INDENT();

  l->entered = true;
}

void level_completed(Gamep g, Levelsp v, Levelp l)
{
  LOG("Level completed: %u", l->level_num);
  TRACE_AND_INDENT();

  l->completed = true;
}

//
// Change the current
//
Levelp level_change(Gamep g, Levelsp v, LevelNum level_num)
{
  LOG("Level change to %u", level_num);
  TRACE_AND_INDENT();

  Level *old_level = game_level_get(g, v);
  game_level_set(g, v, level_num);
  Level *new_level = game_level_get(g, v);

  if (old_level == new_level) {
    if (new_level->level_num == 0) {
      TOPCON("Welcome to bla bla bla..., " UI_IMPORTANT_FMT_STR "Gorget" UI_RESET_FMT ".");
    }
    return new_level;
  }

  level_scroll_warp_to_focus(g, v, new_level);
  level_dump(g, v, new_level);

  if (level_num == LEVEL_SELECT_ID) {
    TOPCON("");
    TOPCON(UI_WARNING_FMT_STR "Choose your next level." UI_RESET_FMT);
    TOPCON("Mouse over levels for monster/treasure info.");
  } else if (new_level->completed) {
    TOPCON("");
    TOPCON(UI_WARNING_FMT_STR "You re-enter level %u of dungeon %s." UI_RESET_FMT "", new_level->level_num + 1,
           game_seed_name_get(g));
  } else if (level_num > 0) {
    TOPCON("");
    TOPCON(UI_WARNING_FMT_STR "You enter level %u of dungeon %s." UI_RESET_FMT "", new_level->level_num + 1,
           game_seed_name_get(g));
  }

  //
  // Enable/disable load and save buttons
  //
  wid_actionbar_fini(g);
  wid_actionbar_init(g);

  return new_level;
}

void level_destroy(Gamep g, Levelsp v, Levelp l)
{
  TRACE_NO_INDENT();
  if (! l || ! l->initialized) {
    return;
  }

  DBG("Level destroy %u", l->level_num);

  //
  // Remove all things
  //
  FOR_ALL_THINGS_ON_LEVEL(g, v, l, t) { thing_fini(g, v, l, t); }

  //
  // Clean up the level select snake walk
  //
  if (l->level_num == LEVEL_SELECT_ID) {
    level_select_destroy(g, v, l);
  }

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

void level_bounds_set(Gamep g, Levelsp v, Levelp l)
{
  TRACE_NO_INDENT();

  int  zoom = game_map_zoom_get(g);
  auto dw   = INNER_TILE_WIDTH * zoom;
  auto dh   = INNER_TILE_HEIGHT * zoom;

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

  //
  // We need to animate all the level tiles in sync, so might as well draw the whole level
  //
  if (l->level_num == LEVEL_SELECT_ID) {
    v->minx = 0;
    v->miny = 0;
    v->maxx = MAP_WIDTH;
    v->maxy = MAP_HEIGHT;
  }
}
