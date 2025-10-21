//
// Copyright goblinhack@gmail.com
//

#pragma once
#ifndef _MY_LEVEL_H_
#define _MY_LEVEL_H_

#include "my_game_defs.hpp"
#include "my_ptrcheck.hpp"
#include "my_thing.hpp"
#include "my_types.hpp"

#include <vector>

enum {
  CURSOR_NONE,
  CURSOR_PATH,
  CURSOR_AT,
};

//
// Player state
//
#define PLAYER_STATE_ENUM(list_macro)                                                                                \
  clang_format_indent()                                                /* dummy line for clang indentation fixup */  \
      list_macro(PLAYER_STATE_INIT, "INIT"),                           /* newline */                                 \
      list_macro(PLAYER_STATE_DEAD, "DEAD"),                           /* newline */                                 \
      list_macro(PLAYER_STATE_NORMAL, "NORMAL"),                       /* newline */                                 \
      list_macro(PLAYER_STATE_PATH_REQUESTED, "PATH-REQUESTED"),       /* newline */                                 \
      list_macro(PLAYER_STATE_MOVE_CONFIRM_REQUESTED, "MOVE-CONFIRM"), /* newline */                                 \
      list_macro(PLAYER_STATE_FOLLOWING_A_PATH, "FOLLOW-PATH"),        /* newline */

ENUM_DEF_H(PLAYER_STATE_ENUM, PlayerState)

typedef struct LevelInfo_ {
  //////////////////////////////////////////////////////////////
  // No c++ types can be used here, to allow easy level replay
  //
  // Why C types only ? For large data structures it is visibly
  // faster to malloc and memset versus default construction.
  //////////////////////////////////////////////////////////////

  //
  // Seed used to generated this level
  //
  uint32_t seed_num;

  //
  // Where the player start is
  //
  spoint entrance_at;

  //
  // Where the exit is
  //
  spoint exit_at;

  //
  // Is this tile on the main flood fill path from start to exit
  //
  uint8_t on_path_entrance_to_exit[ MAP_WIDTH ][ MAP_HEIGHT ];

  //
  // How many rooms?
  //
  int room_count;

  //
  // How many monsters?
  //
  int monst_count;
  int monst_group_mob_count;
  int monst_group_easy_count;
  int monst_group_hard_count;

  //
  // How much treasure?
  //
  int treasure_count;

  //
  // How many teleports. Needs to be > 1
  //
  int teleport_count;

  //
  // How many locked doors. Must have corresponding key counts.
  //
  int door_locked_count;
  int key_count;

  //
  // How many room fragments we've added
  //
  int fragment_count;

  //////////////////////////////////////////////////////////////
  // No c++ types can be used here, to allow easy level replay
  //////////////////////////////////////////////////////////////
} LevelInfo;

typedef struct {
  //
  // The color of this tile
  //
  color c;
  //
  // The total of all lights intersecting here, which is then scaled into the final light
  //
  int16_t r;
  int16_t g;
  int16_t b;
  uint8_t lit;
} LightTile;

//
// Light map for the level
//
typedef struct LightMap_ {
  LightTile tile[ MAP_WIDTH ][ MAP_HEIGHT ];
} LightMap;

typedef struct Level_ {
  //////////////////////////////////////////////////////////////
  // No c++ types can be used here, to allow easy level replay
  //
  // Why C types only ? For large data structures it is visibly
  // faster to malloc and memset versus default construction.
  //////////////////////////////////////////////////////////////
  //
  // Where this level is in the bigger map
  //
  LevelNum level_num;
  //
  // Level generation info
  //
  LevelInfo info;
  //
  // Where on the level select grid is this level
  //
  spoint level_select_at;
  //
  // Where to being this level
  //
  spoint entrance;
  //
  // Where to exit this level
  //
  spoint exit;
  //
  // Flags
  //
  uint8_t initialized : 1;
  //
  // Booleans that are set whenever something of this type is created on the level
  // and then cleared at end of tick.
  //
  uint8_t is_tick_delay_on_spawn : 1;
  //
  // Player has entered level
  //
  uint8_t player_has_entered_level : 1;
  //
  // Player has completed level on way or another
  //
  uint8_t player_completed_level_via_exit : 1;
  uint8_t player_fell_out_of_level        : 1;
  //
  // Player can enter this level
  //
  uint8_t player_can_enter_this_level_next : 1;
  //
  // Level needs tiles updated
  //
  uint8_t tile_update_required : 1;
  //
  // When a tile is destroyed, we need to update adjacent tiles. This limits the update to only changed tiles.
  //
  uint8_t _tile_update_required[ MAP_WIDTH ][ MAP_HEIGHT ];
  //
  // What things are where? Each Id points to a thing structure.
  //
  ThingId thing_id[ MAP_WIDTH ][ MAP_HEIGHT ][ MAP_SLOTS ];
  //
  // What we have ever seen
  //
  FovMap player_fov_has_seen_tile;
  //
  // Has the player been on this tile?
  //
  uint8_t player_has_walked_tile[ MAP_WIDTH ][ MAP_HEIGHT ];
  //
  // Original character map when the level was generated
  //
  char debug[ MAP_WIDTH ][ MAP_HEIGHT ];
  //////////////////////////////////////////////////////////////
  // No c++ types can be used here, to allow easy level replay
  //////////////////////////////////////////////////////////////
} Level;

typedef struct LevelSelectCell_ {
  //
  // If there is a level here
  //
  uint8_t is_set;
  //
  // Back pointer to the level here, if any
  //
  LevelNum level_num;
} LevelSelectCell;

typedef struct LevelSelect_ {
  //
  // Set when we have populated the levels.
  //
  uint8_t is_populated;

  //
  // How many levels generated
  //
  LevelNum level_count;

  //
  // How many ms to create all the lvels
  //
  uint32_t create_time;

  //
  // Level tiles and grid info
  //
  LevelSelectCell data[ LEVELS_ACROSS ][ LEVELS_DOWN ];
} LevelSelect;

typedef struct Levels_ {
  //////////////////////////////////////////////////////////////
  // No c++ types can be used here, to allow easy level replay
  //
  // Why C types only ? For large data structures it is visibly
  // faster to malloc and memset versus default construction.
  //////////////////////////////////////////////////////////////
  //
  // Current level being played
  //
  LevelNum level_num;
  //
  // Increments once per event loop.
  //
  uint32_t frame;
  //
  // Tick increases one per player move.
  //
  uint32_t tick;
  //
  // Used to keep track if we have ran the temperature checks yet this tick.
  //
  uint32_t tick_temperature;
  //
  // When the tick began in ms
  //
  uint32_t frame_begin;
  //
  // Ranges from 0 to 1 when a tick is in progress.
  //
  float time_step;
  float last_time_step;
  //
  // Flag array of all levels. The levels equate to one tile in the level grid.
  //
  Level level[ MAX_LEVELS ];
  //
  // Level lighting
  //
  LightMap light_map;
  //
  // Which levels are where
  //
  LevelSelect level_select;
  //
  // All things structure memory.
  //
  Thing thing_body[ 1 << THING_INDEX_BITS ];
  //
  // Space for monster AI
  //
  ThingExt thing_ext[ THING_EXT_MAX ];
  //
  // Space for player AI
  //
  ThingPlayer thing_player;
  //
  // The current player.
  //
  ThingId player_id;
  //
  // Used in level selection, this is the current level thing
  //
  ThingId level_select_id;
  //
  // Things described in the rightbar.
  //
  ThingId describe[ THING_DESCRIBE_MAX ];
  uint8_t describe_count;
  //
  // The cursor path highlighted.
  //
  uint8_t cursor[ MAP_WIDTH ][ MAP_HEIGHT ];
  //
  // What the player is currently highlighting.
  //
  spoint cursor_at;
  //
  // Previous cursor. Used to detect changes.
  //
  spoint old_cursor_at;
  //
  // Map scroll offset.
  //
  spoint pixel_map_at;
  //
  // Maximum pixel bound
  //
  spoint pixel_max;
  //
  // Levels display bounds
  //
  int minx;
  int miny;
  int maxx;
  int maxy;
  //
  // Player movement state
  //
  PlayerState _player_state;
  //
  // Is the cursor over the map?
  //
  uint8_t cursor_at_valid : 1;
  //
  // Mouse moved?
  //
  uint8_t cursor_moved : 1;
  //
  // We have to interpolate movement and this indicates that is in progress.
  //
  uint8_t tick_in_progress : 1;
  //
  // Some things like explosions, we want to wait for the explosion to finish before
  // moving to the next tick.
  //
  uint8_t tick_wait_on_anim : 1;
  //
  // Ensure things have finished their move before ending the tick
  //
  uint8_t tick_wait_on_things : 1;
  //
  // Player has moved.
  //
  uint8_t tick_begin_requested : 1;
  uint8_t tick_end_requested   : 1;
  //
  // If the player has moved, we need to scroll the map
  //
  uint8_t requested_auto_scroll : 1;
  //
  // For a time period e.g. post teleport, we want to ignore mouse moves until the player is
  // centered once more.
  //
  uint8_t requested_forced_auto_scroll : 1;
  //
  // Player move request.
  //
  uint8_t requested_move_left  : 1;
  uint8_t requested_move_keft  : 1;
  uint8_t requested_move_right : 1;
  uint8_t requested_move_up    : 1;
  //
  // Set when something modifies the map and we need to update caches.
  //
  uint8_t is_map_changed : 1;
  //////////////////////////////////////////////////////////////
  // No c++ types can be used here, to allow easy level replay
  //////////////////////////////////////////////////////////////
} Levels;

#define FOR_ALL_LEVELS(_g_, _v_, _l_)                                                                                \
  if (_g_ && _v_)                                                                                                    \
    for (auto _n_ = 0; _n_ < MAX_LEVELS; _n_++)                                                                      \
      if ((_l_ = &v->level[ _n_ ]))

//
// Walk all things, all levels
//
#define FOR_ALL_THINGS_ALL_LEVELS(_g_, _v_, _t_)                                                                     \
  if (_g_ && _v_)                                                                                                    \
    for (Thingp _t_ = nullptr, loop2 = (Thingp) 1; loop2 == (Thingp) 1; loop2 = (Thingp) 0)                          \
      if (_g_ && _v_)                                                                                                \
        for (auto _id_ = 0; _id_ < 1 << THING_COMMON_ID_BITS; _id_++)                                                \
          if (_l_->thing_body[ _id_ ].id)                                                                            \
            if ((_t_ = thing_find_optional(_l_, _l_->thing_body[ _id_ ].id)))

//
// For all things on the map
//
#define FOR_ALL_MAP_POINTS(_g_, _v_, _l_, _x_, _y_)                                                                  \
  if (_g_ && _v_ && _l_)                                                                                             \
    for (_y_ = 0; _y_ < MAP_HEIGHT; _y_++)                                                                           \
      for (_x_ = 0; _x_ < MAP_WIDTH; _x_++)

//
// For all things at this Z depth
//
#define FOR_ALL_THINGS_ON_LEVEL(_g_, _v_, _l_, _t_)                                                                  \
  if (_g_ && _v_ && _l_)                                                                                             \
    for (auto _y_ = 0; _y_ < MAP_HEIGHT; _y_++)                                                                      \
      for (auto _x_ = 0; _x_ < MAP_WIDTH; _x_++)                                                                     \
        for (Tpp _tp_ = nullptr, loop1 = (Tpp) 1; loop1 == (Tpp) 1; loop1 = (Tpp) 0)                                 \
          for (Thingp _t_ = nullptr, loop2 = (Thingp) 1; loop2 == (Thingp) 1; loop2 = (Thingp) 0)                    \
            for (auto _slot_ = 0; _slot_ < MAP_SLOTS; _slot_++)                                                      \
              if ((_t_ = thing_and_tp_get_at(_g_, _v_, _l_, spoint(_x_, _y_), _slot_, &_tp_)))

//
// For all things at a specific location
//
#define FOR_ALL_THINGS_AT(_g_, _v_, _l_, _t_, _p_)                                                                   \
  if (_g_ && _v_ && _l_)                                                                                             \
    for (Thingp _t_ = nullptr, loop2 = (Thingp) 1; loop2 == (Thingp) 1; loop2 = (Thingp) 0)                          \
      for (auto _slot_ = 0; _slot_ < MAP_SLOTS; _slot_++)                                                            \
        if ((_t_ = thing_get(_g_, _v_, _l_, _p_, _slot_)))

#define FOR_ALL_TPS_AT(_g_, _v_, _l_, _tp_, _p_)                                                                     \
  if (_g_ && _v_ && _l_)                                                                                             \
    for (Tpp _tp_ = nullptr, loop1 = (Tpp) 1; loop1 == (Tpp) 1; loop1 = (Tpp) 0)                                     \
      for (Thingp _t_ = nullptr, loop2 = (Thingp) 1; loop2 == (Thingp) 1; loop2 = (Thingp) 0)                        \
        for (auto _slot_ = 0; _slot_ < MAP_SLOTS; _slot_++)                                                          \
          if ((_t_ = thing_and_tp_get_at(_g_, _v_, _l_, _p_, _slot_, &_tp_)))

enum {
  CHANCE_VVV_UNLIKELY = 1,
  CHANCE_VV_UNLIKELY  = 10,
  CHANCE_V_UNLIKELY   = 100,
  CHANCE_UNLIKELY     = 1000,
  CHANCE_NORMAL       = 10000,
};

enum {
  NO_FLAGS = 0x0,
  //
  // Sanity check on exits that we have no tiles in the same column or row
  // as an exit; it makes it harder to join rooms together
  //
  ROOM_FLAG_CHECK_EXITS = 0x1,
  //
  // Secret rooms which need a key to enter
  //
  ROOM_FLAG_LOCKED = 0x2,
  //
  // Key room
  //
  ROOM_FLAG_HAS_KEY = 0x4,
  ROOM_FLAG_NEXT    = 0x8,
};

enum {
  //
  // A test level
  //
  LEVEL_TEST_FLAG = 1,
};

bool is_oob(spoint);
bool is_oob(int, int);

bool    level_alive_flag(Gamep, Levelsp, Levelp, ThingFlag, spoint);
bool    level_cursor_describe_add(Gamep, Levelsp, Thingp);
bool    level_cursor_describe_remove(Gamep, Levelsp, Thingp);
bool    level_cursor_is_valid(Gamep, Levelsp);
bool    level_flag(Gamep, Levelsp, Levelp, ThingFlag, spoint p);
bool    level_is_same_obj_type_at(Gamep, Levelsp, Levelp, spoint, Tpp);
bool    level_match_contents(Gamep, Levelsp, Levelp, Testp, int w, int h, const char *in);
bool    level_open_flag(Gamep, Levelsp, Levelp, ThingFlag, spoint);
bool    level_populate_thing_id_at(Gamep, Levelsp, Levelp, spoint, int slot, ThingId);
bool    level_tick_is_in_progress(Gamep, Levelsp, Levelp);
int     level_count_flag(Gamep, Levelsp, Levelp, ThingFlag, spoint);
Levelp  level_change(Gamep, Levelsp, LevelNum);
Levelsp levels_memory_alloc(Gamep);
ThingId level_get_thing_id_at(Gamep, Levelsp, Levelp, spoint p, int slot);
Thingp  level_afirst_flag(Gamep, Levelsp, Levelp, ThingFlag, spoint);
Thingp  level_first_flag(Gamep, Levelsp, Levelp, ThingFlag, spoint);
Thingp  level_ofirst_flag(Gamep, Levelsp, Levelp, ThingFlag, spoint);
void    level_anim(Gamep, Levelsp, Levelp);
void    level_assign_tiles(Gamep, Levelsp, Levelp);
void    level_bounds_set(Gamep, Levelsp, Levelp);
void    level_count_items(Gamep, Levelsp, Levelp);
void    level_cursor_copy_mouse_path_to_player(Gamep, Levelsp, Levelp);
void    level_light_calculate_can_see_callback(Gamep, Levelsp, Levelp, Thingp, spoint pov, spoint p, int max_radius);
void    level_cursor_copy_path_to_player(Gamep, Levelsp, Levelp, std::vector< spoint > &move_path);
void    level_cursor_describe_clear(Gamep, Levelsp);
void    level_cursor_describe_update(Gamep, Levelsp);
void    level_cursor_describe(Gamep, Levelsp, Levelp);
void    level_cursor_path_recreate(Gamep, Levelsp, Levelp);
void    level_cursor_path_reset(Gamep, Levelsp);
void    level_cursor_set(Gamep, Levelsp, spoint);
void    level_debug_stats(Gamep);
void    level_debug(Gamep, Levelsp, Levelp);
void    level_destroy(Gamep, Levelsp, Levelp);
void    level_display_obj(Gamep, Levelsp, Levelp, spoint, Tpp, Thingp);
void    level_display(Gamep, Levelsp, Levelp);
void    level_dump(Gamep, Levelsp, Levelp, int w = MAP_WIDTH, int h = MAP_HEIGHT);
void    level_enter(Gamep, Levelsp, Levelp);
void    level_forced_auto_scroll(Gamep, Levelsp, Levelp);
void    level_init(Gamep, Levelsp, Levelp, LevelNum);
void    level_is_completed_by_player_exiting(Gamep, Levelsp, Levelp);
void    level_is_completed_by_player_falling(Gamep, Levelsp, Levelp);
void    level_light_calculate(Gamep, Levelsp, Levelp);
void    level_mouse_position_get(Gamep, Levelsp, Levelp);
void    level_populate(Gamep, Levelsp, Levelp, const char *);
void    level_populate(Gamep, Levelsp, Levelp, int w, int h, const char *);
void    level_scroll_delta(Gamep, Levelsp, Levelp, spoint);
void    level_scroll_to_focus(Gamep, Levelsp, Levelp);
void    level_scroll_warp_to_focus(Gamep, Levelsp, Levelp);
void    level_tick_begin_requested(Gamep, Levelsp, Levelp, const char *);
void    level_tick_begin_temperature(Gamep, Levelsp, Levelp);
void    level_tick_chasm(Gamep, Levelsp, Levelp);
void    level_light_precalculate(Gamep);
void    level_tick_end_temperature(Gamep, Levelsp, Levelp);
void    level_tick_explosion(Gamep, Levelsp, Levelp);
void    level_tick_teleport(Gamep, Levelsp, Levelp);
void    level_tick_water(Gamep, Levelsp, Levelp);
void    level_tick(Gamep, Levelsp, Levelp);
bool    level_is_level_select(Gamep, Levelsp, Levelp);
void    level_tile_update_set(Gamep, Levelsp, Levelp, spoint);
void    level_tile_update(Gamep, Levelsp, Levelp);
void    levels_destroy(Gamep, Levelsp);
void    level_gen_create_levels(Gamep, Levelsp);
void    level_gen_stats_dump(Gamep);
void    level_gen_test(Gamep);
void    level_water_display(Gamep, Levelsp, Levelp, spoint, int, int16_t, int16_t, int16_t, int16_t);
void    level_water_tick(Gamep, Levelsp, Levelp);
void    level_water_update(Gamep, Levelsp, Levelp);

typedef void (*level_fov_can_see_callback_t)(Gamep, Levelsp, Levelp, Thingp me, spoint pov, spoint p, int max_radius);
void level_fov(Gamep, Levelsp, Levelp, Thingp, FovMap *curr, FovMap *ever, spoint pov, int max_radius,
               level_fov_can_see_callback_t = nullptr);

typedef enum {
  LEVEL_TYPE_NORMAL,
  LEVEL_TYPE_TEST,
  LEVEL_TYPE_BOSS,
#define LEVEL_TYPE_FIRST LEVEL_TYPE_NORMAL
  LEVEL_TYPE_MAX
} LevelType;

void level_add(Gamep, int chance, LevelType, const std::string &alias, const char *file, int line, ...);
void levels_init(Gamep);
void levels_fini(Gamep);
void levels_test(Gamep);
void levels_fixed(Gamep);

void rooms_test(Gamep);
void rooms_init(Gamep);
void rooms_fini(Gamep);
void room_add(Gamep, int chance, int flags, const char *file, int line, ...);
void rooms_blend1(Gamep);
void rooms_blend2(Gamep);
void rooms_chunky(Gamep);
void rooms_circular(Gamep);
void rooms_cross(Gamep);
void rooms_cross_sym(Gamep);
void rooms_small(Gamep);
void rooms_medium(Gamep);
void rooms_start(Gamep);
void rooms_exit(Gamep);
void rooms_key(Gamep);
void rooms_prefab(Gamep);
void rooms_prefab_secret(Gamep);

void fragments_init(Gamep);
void fragments_fini(Gamep);
void fragment_alts_fini(Gamep);
bool fragment_add(Gamep, int chance, const char *file, int line, ...);
bool fragment_alt_add(Gamep, int chance, const char *file, int line, ...);

bool   level_select_is_oob(int x, int y);
bool   level_select_is_oob(spoint);
Levelp level_select_get_level(Gamep, Levelsp, Levelp, spoint);
Levelp level_select_get_next_level_down(Gamep, Levelsp, Levelp);
Thingp thing_level_select(Gamep);
void   level_select_assign_levels_to_grid(Gamep, Levelsp);
void   level_select_destroy(Gamep, Levelsp, Levelp);
void   level_select_grid_of_empty_levels(Gamep);
void   level_select_rightbar_needs_update(Gamep, Levelsp, Levelp);
void   level_select_rightbar_show_contents(Gamep, Levelsp, Levelp, WidPopup *);
void   level_select_test(Gamep);
void   level_select_update_grid_tiles(Gamep, Levelsp);
void   level_select_user_chose_a_level(Gamep, Levelsp, Levelp);

std::string player_state_to_string(PlayerState);
PlayerState player_state(Gamep, Levelsp);
void        player_state_change(Gamep, Levelsp, PlayerState new_state);

#endif // _MY_LEVEL_H_
