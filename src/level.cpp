//
// Copyright goblinhack@gmail.com
//

#include "my_charmap.hpp"
#include "my_globals.hpp"
#include "my_level.hpp"
#include "my_main.hpp"
#include "my_test.hpp"
#include "my_thing_inlines.hpp"
#include "my_ui.hpp"
#include "my_wids.hpp"

#include <format>

LevelOpt g_level_opt;

bool is_oob(fpoint p)
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

bool is_oob(spoint p)
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

bool is_oob(int x, int y)
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

bool level_request_to_cleanup_things_get(Gamep g, Levelsp v, Levelp l)
{
  TRACE_NO_INDENT();

  return l->request_to_cleanup_things;
}

void level_request_to_cleanup_things_set(Gamep g, Levelsp v, Levelp l)
{
  TRACE_NO_INDENT();

  l->request_to_cleanup_things = true;
}

void level_request_to_cleanup_things_unset(Gamep g, Levelsp v, Levelp l)
{
  TRACE_NO_INDENT();

  l->request_to_cleanup_things = false;
}

//
// Are we on the level selection level?
//
bool level_is_level_select(Gamep g, Levelsp v, Levelp l)
{
  TRACE_NO_INDENT();

  if (! g || ! v || ! l) {
    return false;
  }

  return l->level_num == LEVEL_SELECT_ID;
}

//
// Print a level string
//
static void level_dump(Gamep g, Levelsp v, Levelp l, int w, int h, std::string s)
{
  TRACE_NO_INDENT();

  CON("Level: %u", l->level_num + 1);
  for (int y = 0; y < h; y++) {
    std::string line;

    for (int x = 0; x < w; x++) {
      auto offset = (w * y) + x;
      auto c      = s[ offset ];
      if (c) {
        line += c;
      }
    }

    if (! line.empty()) {
      CON("[%s]", line.c_str());
    }
  }
}

//
// Print a level string
//
void level_dump(Gamep g, Levelsp v, Levelp l, int w, int h)
{
  TRACE_NO_INDENT();

  std::string s = level_string(g, v, l, w, h);

  level_dump(g, v, l, w, h, s);
}

//
// Compare level contents
//
bool level_match_contents(Gamep g, Levelsp v, Levelp l, Testp t, int w, int h, const char *expected)
{
  TRACE_NO_INDENT();

  LEVEL_LOG(l, "match");
  std::string found = level_string(g, v, l, w, h);

  for (int y = 0; y < h; y++) {
    std::string line;

    for (int x = 0; x < w; x++) {
      auto offset = (w * y) + x;
      auto c      = found[ offset ];
      auto e      = expected[ offset ];
      if (c != e) {
        CON_NEW_LINE();
        CON("Expected:");
        level_dump(g, v, l, w, h, expected);
        CON_NEW_LINE();
        CON("Found:");
        level_dump(g, v, l, w, h);
        CON_NEW_LINE();
        TEST_CON(t, "Level contents not as expected");
        return false;
      }
    }
  }

  return true;
}

void level_init(Gamep g, Levelsp v, Levelp l, LevelNum n)
{
  TRACE_NO_INDENT();

  memset(l, 0, SIZEOF(*l));

  l->is_initialized = true;
  l->level_num      = n;
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
  v = (Levelsp) myzalloc(SIZEOF(*v), "v");
  if (! v) {
    return nullptr;
  }
  newptr(MTYPE_LEVELS, v, "levels");

  return v;
}

static void levels_memory_free(Gamep g, Levelsp v)
{
  LOG("Levels free memory");
  TRACE_NO_INDENT();

  verify(MTYPE_LEVELS, v);
  myfree(v);
  oldptr(MTYPE_LEVELS, v);

  game_levels_set(g, nullptr);
}

void levels_destroy(Gamep g, Levelsp v)
{
  LOG("Levels destroy");
  TRACE_AND_INDENT();

  FOR_ALL_LEVELS(g, v, iter)
  {
    TRACE_NO_INDENT();
    level_destroy(g, v, iter);
  }

  levels_memory_free(g, v);
}

void level_finalize(Gamep g, Levelsp v, Levelp l)
{
  LEVEL_LOG(l, "Level finalize");
  TRACE_AND_INDENT();

  level_select_calculate_next_level_down(g, v, l, true);
  v->level_count++;
}

void levels_finalize(Gamep g, Levelsp v)
{
  LOG("Levels finalize");
  TRACE_AND_INDENT();

  if (! g) {
    DIE("no game pointer");
  }

  if (! v) {
    DIE("no levels pointer");
  }

  v->level_count = 0;
  FOR_ALL_LEVELS(g, v, iter)
  {
    TRACE_NO_INDENT();
    level_finalize(g, v, iter);
  }
}

void level_enter(Gamep g, Levelsp v, Levelp l)
{
  LEVEL_LOG(l, "Level entered");
  TRACE_AND_INDENT();

  l->player_has_entered_level = true;
}

void level_is_completed_by_player_exiting(Gamep g, Levelsp v, Levelp l)
{
  //
  // Clear signs of previous failure
  //
  l->player_fell_out_of_level = false;

  if (l->player_completed_level_via_exit) {
    return;
  }
  l->player_completed_level_via_exit = true;

  LEVEL_LOG(l, "Level completed");
  TRACE_AND_INDENT();

  auto player_struct = thing_player_struct(g);
  if (player_struct) {
    player_struct->levels_completed++;
  }
}

void level_is_completed_by_player_falling(Gamep g, Levelsp v, Levelp l)
{
  l->player_fell_out_of_level = true;

  TOPCON(UI_IMPORTANT_FMT_STR "You tumble into the void." UI_RESET_FMT);
}

//
// Change the current level
//
Levelp level_change(Gamep g, Levelsp v, LevelNum level_num)
{
  LOG("Level change to %u", level_num);
  TRACE_AND_INDENT();

  verify(MTYPE_LEVELS, v);

  //
  // Check we're not trying to jump off the end of the levels
  //
  LevelSelect *s = &v->level_select;
  if (! s) {
    ERR("No level selection created");
    return nullptr;
  }

  if (level_num == LEVEL_SELECT_ID) {
    //
    // Enter level selectionm
    //
  } else if ((level_num > s->level_count) && s->level_count) {
    //
    // Jump tot the last real level
    //
    level_num = s->level_count - 1;
    LOG("Level change to %u (max level)", level_num);
  }

  Level *old_level = game_level_get(g, v);
  game_level_populate(g, v, level_num);
  Level *new_level = game_level_get(g, v);

  verify(MTYPE_LEVELS, v);

  if (old_level == new_level) {
    if (new_level->level_num == 0) {
      TOPCON("Welcome to " UI_IMPORTANT_FMT_STR "Gorget" UI_RESET_FMT ". A literal work in progress...");
    }
    return new_level;
  }

  level_scroll_warp_to_focus(g, v, new_level);
  level_debug(g, v, new_level);

  if (level_is_level_select(g, v, new_level)) {
    BOTCON_NEW_LINE();
    TOPCON_NEW_LINE();
    TOPCON("Choose your next level.");
    TOPCON("Mouse over levels for monster/treasure info.");
  } else if (new_level->player_completed_level_via_exit) {
    TOPCON_NEW_LINE();
    TOPCON("You re-enter level %u of dungeon %s.", new_level->level_num + 1, game_seed_name_get(g));
  } else if (new_level->player_fell_out_of_level) {
    TOPCON_NEW_LINE();
    TOPCON("You stumble back into level %u of dungeon %s.", new_level->level_num + 1, game_seed_name_get(g));
  } else if (level_num > 0) {
    TOPCON_NEW_LINE();
    TOPCON("You enter level %u of dungeon %s.", new_level->level_num + 1, game_seed_name_get(g));
  }

  level_update_visibility(g, v, new_level);
  game_request_to_remake_ui_set(g);

  return new_level;
}

void level_destroy(Gamep g, Levelsp v, Levelp l)
{
  TRACE_NO_INDENT();

  if (! l || ! l->is_initialized) {
    return;
  }

  DBG2("Level destroy %u", l->level_num);

  //
  // Remove all things
  //
  FOR_ALL_THINGS_ON_LEVEL(g, v, l, t)
  {
    // newline
    thing_fini(g, v, l, t);
  }

  //
  // Clean up the level select snake walk
  //
  if (level_is_level_select(g, v, l)) {
    level_select_destroy(g, v, l);
  }

  memset(l, 0, SIZEOF(*l));
}

bool level_populate_thing_id_at(Gamep g, Levelsp v, Levelp l, spoint p, int slot, ThingId id)
{
  TRACE_NO_INDENT();

  if (is_oob(p)) {
    return false;
  }
  l->thing_id[ p.x ][ p.y ][ slot ] = id;
  return true;
}

ThingId level_get_thing_id_at(Gamep g, Levelsp v, Levelp l, spoint p, int slot)
{
  TRACE_NO_INDENT();

  if (is_oob(p)) {
    return 0;
  }
  return l->thing_id[ p.x ][ p.y ][ slot ];
}

//
// Additional level flag filters e.g. open doors are not obstacles
//
static bool level_flag_filter(Gamep g, Levelsp v, Levelp l, ThingFlag f, Thingp it)
{
  TRACE_NO_INDENT();

  switch (f) {
    case is_obs_to_cursor_path :
    case is_obs_to_explosion :
    case is_obs_to_falling_onto :
    case is_obs_to_fire :
    case is_obs_to_jump_over :
    case is_obs_to_jumping_onto :
    case is_obs_to_teleporting_onto :
    case is_obs_to_movement :
      if (thing_is_open(it)) {
        return true; // filter out
      }
      break;
    case is_able_to_fall :
      if (thing_is_falling(it)) {
        return true; // filter out
      }
      break;
    default : break;
  }

  return false;
}

Thingp level_flag(Gamep g, Levelsp v, Levelp l, ThingFlag f, spoint p)
{
  TRACE_NO_INDENT();

  FOR_ALL_THINGS_AT_UNSAFE(g, v, l, it, p)
  {
    if (level_flag_filter(g, v, l, f, it)) {
      continue;
    }

    if (tp_flag(thing_tp(it), f)) {
      return it;
    }
  }

  return nullptr;
}

Thingp level_flag(Gamep g, Levelsp v, Levelp l, ThingFlag f, Thingp at)
{
  TRACE_NO_INDENT();

  if (! at) {
    ERR("No thing pointer");
    return nullptr;
  }

  return level_flag(g, v, l, f, thing_at(at));
}

//
// Filter to only alive things
//
Thingp level_alive(Gamep g, Levelsp v, Levelp l, ThingFlag f, spoint p)
{
  TRACE_NO_INDENT();

  FOR_ALL_THINGS_AT_UNSAFE(g, v, l, it, p)
  {
    if (level_flag_filter(g, v, l, f, it)) {
      continue;
    }

    if (thing_is_dead(it)) {
      continue;
    }

    if (tp_flag(thing_tp(it), f)) {
      return it;
    }
  }

  return nullptr;
}

Thingp level_alive(Gamep g, Levelsp v, Levelp l, ThingFlag f, Thingp at)
{
  TRACE_NO_INDENT();

  if (! at) {
    ERR("No thing pointer");
    return nullptr;
  }

  return level_alive(g, v, l, f, thing_at(at));
}

//
// Flag + is open
//
Thingp level_open(Gamep g, Levelsp v, Levelp l, ThingFlag f, spoint p)
{
  TRACE_NO_INDENT();

  FOR_ALL_THINGS_AT_UNSAFE(g, v, l, it, p)
  {
    if (level_flag_filter(g, v, l, f, it)) {
      continue;
    }

    if (! thing_is_open(it)) {
      continue;
    }

    if (tp_flag(thing_tp(it), f)) {
      return it;
    }
  }

  return nullptr;
}

Thingp level_open(Gamep g, Levelsp v, Levelp l, ThingFlag f, Thingp at)
{
  TRACE_NO_INDENT();

  if (! at) {
    ERR("No thing pointer");
    return nullptr;
  }

  return level_open(g, v, l, f, thing_at(at));
}

//
// Count things
//
int level_count(Gamep g, Levelsp v, Levelp l, ThingFlag f, spoint p)
{
  TRACE_NO_INDENT();

  int count = 0;

  FOR_ALL_THINGS_AT_UNSAFE(g, v, l, it, p)
  {
    if (level_flag_filter(g, v, l, f, it)) {
      continue;
    }

    if (thing_is_dead(it)) {
      continue;
    }

    if (tp_flag(thing_tp(it), f)) {
      count++;
    }
  }

  return count;
}

int level_count(Gamep g, Levelsp v, Levelp l, ThingFlag f, Thingp t)
{
  TRACE_NO_INDENT();

  return level_count(g, v, l, f, thing_at(t));
}

bool level_is_same_obj_type_at(Gamep g, Levelsp v, Levelp l, spoint p, Tpp tp)
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

    //
    // This check is needed to handle walls that are destroyed, but not yet popped.
    //
    if (thing_is_dead(it)) {
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

  verify(MTYPE_LEVELS, v);

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

  v->pixel_max.x = (MAP_WIDTH * dw) - game_map_fbo_width_get(g);
  v->pixel_max.y = (MAP_HEIGHT * dh) - game_map_fbo_height_get(g);

  //
  // Overflow?
  //
  if (v->pixel_map_at.x > v->pixel_max.x) {
    v->pixel_map_at.x = v->pixel_max.x;
  }

  if (v->pixel_map_at.y > v->pixel_max.y) {
    v->pixel_map_at.y = v->pixel_max.y;
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
  if (level_is_level_select(g, v, l)) {
    v->minx = 0;
    v->miny = 0;
    v->maxx = MAP_WIDTH;
    v->maxy = MAP_HEIGHT;
  }
}
