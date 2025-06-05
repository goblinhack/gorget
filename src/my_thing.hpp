//
// Copyright goblinhack@gmail.com
//

#pragma once
#ifndef _MY_THING_HPP_
#define _MY_THING_HPP_

#include "my_game_defs.hpp"
#include "my_minimal.hpp"
#include "my_point.hpp" // does not seem to make the compile speed much worse
#include "my_tp.hpp"    // does not seem to make the compile speed much worse

//
// Entropy is always > 0 for Thing IDs to distinguish them
// A thing ID is composed as: [ Entropy bits] [ ID bits ]
//
#define THING_COMMON_ID_ENTROPY_BITS    6
#define THING_COMMON_ID_BITS            21
#define THING_COMMON_ID_BASE            (1U << (THING_COMMON_ID_BITS))
#define THING_COMMON_ID_ENTROPY_MASK    (((1U << THING_COMMON_ID_ENTROPY_BITS) - 1) << THING_COMMON_ID_BITS)
#define THING_COMMON_ID_MASK            ((1U << THING_COMMON_ID_BITS) - 1)
#define THING_COMMON_ID_GET_ENTROPY(id) ((id & THING_COMMON_ID_ENTROPY_MASK) >> THING_COMMON_ID_BITS)
#define THING_COMMON_ID_GET(id)         (id & THING_COMMON_ID_MASK)

//
// Essentially equates to the max number of monsters
//
#define THING_AI_MAX        65535 /* The size of thing_ai */
#define THING_MOVE_PATH_MAX (MAP_WIDTH * 4)

enum {
  THING_RARITY_COMMON,
  THING_RARITY_UNCOMMON,
  THING_RARITY_RARE,
  THING_RARITY_VERY_RARE,
  THING_RARITY_UNIQUE,
};

enum {
  THING_DIR_NONE,
  THING_DIR_DOWN,
  THING_DIR_UP,
  THING_DIR_LEFT,
  THING_DIR_RIGHT,
  THING_DIR_TL,
  THING_DIR_BL,
  THING_DIR_TR,
  THING_DIR_BR,
};

//
// Per thing AI memory
//
typedef struct ThingAi_ {
  uint8_t in_use : 1;
} ThingAi;

//
// Player specific memory
//
typedef struct ThingPlayer_ {
  struct {
    point   points[ THING_MOVE_PATH_MAX ];
    int16_t size;
  } move_path;
} ThingPlayer;

typedef struct Thing_ {
  //////////////////////////////////////////////////////////////
  // No c++ types can be used here, to allow easy level replay
  //
  // Why C types only ? For large data structures it is visibly
  // faster to malloc and memset versus default construction.
  //////////////////////////////////////////////////////////////
  //
  // Unique ID
  //
  ThingId id;
  //
  // For players and monsters
  //
  ThingAiId ai_id;
  //
  // Map co-ords.
  //
  point at;
  //
  // Which level am I on?
  //
  LevelNum level_num;
  //
  // Previous map co-ords. Does not change when the move finishes.
  //
  point old_at;
  //
  // Previous map co-ords used for interpolation when moving. Changes when
  // the move finishes.
  //
  point moving_from;
  //
  // Last location we were pushed onto the map.
  //
  point last_pushed_at;
  //
  // Direction
  //
  uint8_t dir;
  //
  // Idle etc...
  //
  uint8_t anim_class;
  //
  // The current tiles[] index for this object
  //
  uint8_t anim_index;
  //
  // Current tile.
  //
  uint16_t tile_index;
  //
  // Count down until the next animation frame should start
  //
  int16_t anim_ms_remaining;
  //
  // Move speed, with 100 being normal. Updated at start of tick.
  //
  int16_t _speed;
  //
  // Weight in pounds. Impacts things like grass being crushed.
  //
  int16_t _weight;
  //
  // Template ID
  //
  uint16_t tp_id;
  //
  // Current game tick this thing has completed
  //
  uint16_t tick;
  //
  // Interpolated co-ords in pixels
  //
  point pix_at;
  //
  // Increases per tick and when it reaches 1, allows the thing to move
  //
  float thing_dt;
  //
  // Keeps track of counters in the level this thing has modified.
  //
  uint8_t count[ THING_FLAG_MAX ];
  //
  // Snuffed it.
  //
  bool _is_dead : 1;
  //
  // For doors, chests etc...
  //
  bool _is_open : 1;
  //
  // Pushed onto the map?
  //
  bool _is_on_map : 1;
  //
  // Currently moving between tiles. The thing is already at the destination.
  //
  bool _is_moving : 1;
} Thing;

Tpp thing_tp(Thingp);

Thingp thing_and_tp_get_at(Gamep, Levelsp, Levelp, point p, int slot, Tpp * = nullptr);
Thingp thing_find(Gamep, Levelsp, ThingId id);
Thingp thing_find_optional(Gamep, Levelsp, ThingId id);
Thingp thing_get(Gamep, Levelsp, Levelp, point p, int slot);
Thingp thing_init(Gamep, Levelsp, Levelp, Tpp, point p);
Levelp thing_level(Gamep, Levelsp, Thingp);
void   thing_stats_dump(Gamep, Levelsp);

ThingAip thing_ai(Gamep, Thingp);

void         thing_dir_bl_set(Thingp, uint8_t);
void         thing_dir_br_set(Thingp, uint8_t);
void         thing_dir_down_set(Thingp, uint8_t);
void         thing_dir_left_set(Thingp, uint8_t);
void         thing_dir_right_set(Thingp, uint8_t);
void         thing_dir_tl_set(Thingp, uint8_t);
void         thing_dir_tr_set(Thingp, uint8_t);
void         thing_dir_up_set(Thingp, uint8_t);
void         thing_fini(Gamep, Levelsp, Levelp, Thingp);
void         thing_interpolate(Gamep, Thingp, float dt);
void         thing_move_finish(Gamep, Levelsp, Levelp, Thingp);
void         thing_tick_end(Gamep, Levelsp, Levelp, Thingp);
void         thing_tick_idle(Gamep, Levelsp, Levelp, Thingp);
void         thing_tick_begin(Gamep, Levelsp, Levelp, Thingp);
void         thing_pop(Gamep, Levelsp, Thingp);
void         thing_push(Gamep, Levelsp, Levelp, Thingp);
void         thing_set_dir_from_delta(Thingp, int dx, int dy);
void         thing_level_warp_to_entrance(Gamep, Levelsp, Levelp, Thingp);
void         thing_collision_handle(Gamep, Levelsp, Levelp, Thingp);
void         thing_update_pos(Gamep, Thingp);
Thingp       thing_player(Gamep);
ThingPlayerp thing_player(Gamep, Thingp);

void thing_player_map_center(Gamep, Levelsp, Levelp);
void thing_player_move_accum(Gamep, Levelsp, Levelp, bool up, bool down, bool left, bool right);
void thing_player_move_delta(Gamep, Levelsp, Levelp, int dx, int dy, int dz);
void thing_player_move_reset(Gamep, Levelsp, Levelp);
void thing_player_reached_exit(Gamep, Levelsp, Levelp, Thingp);
void thing_player_reached_entrance(Gamep, Levelsp, Levelp, Thingp);
void thing_player_collision_handle(Gamep, Levelsp, Levelp, Thingp);
bool thing_player_move_request(Gamep, bool up, bool down, bool left, bool right);

bool thing_can_move_to(Gamep, Levelsp, Levelp, Thingp, point to);
bool thing_move_to_next(Gamep, Levelsp, Levelp, Thingp t);
bool thing_is_dir_down(Thingp);
bool thing_is_dir_tr(Thingp);
bool thing_move_to(Gamep, Levelsp, Levelp, Thingp, point to);
bool thing_warp_to(Gamep, Levelsp, Levelp, Thingp, point to);
bool thing_is_dir_tl(Thingp);
bool thing_is_dir_br(Thingp);
bool thing_is_dir_bl(Thingp);
bool thing_is_dir_left(Thingp);
bool thing_is_dir_right(Thingp);
bool thing_is_dir_up(Thingp);

bool thing_is_dead(Thingp);
void thing_is_dead_set(Thingp, bool val = true);

bool thing_is_open(Thingp);
void thing_is_open_set(Thingp, bool val = true);

bool thing_is_on_map(Thingp);
void thing_is_on_map_set(Thingp, bool val = true);

bool thing_is_moving(Thingp);
void thing_is_moving_set(Thingp, bool val = true);

int  thing_speed(Thingp);
void thing_speed_set(Thingp, int val);

int  thing_weight(Thingp t);
void thing_weight_set(Thingp, int val);

// begin sort marker1 {
bool thing_is_able_to_walk_through_walls(Thingp t);
bool thing_is_animated_can_hflip(Thingp t);
bool thing_is_animated_no_dir(Thingp t);
bool thing_is_animated_same_first_tile(Thingp t);
bool thing_is_animated(Thingp t);
bool thing_is_barrel(Thingp t);
bool thing_is_blit_centered(Thingp t);
bool thing_is_blit_on_ground(Thingp t);
bool thing_is_blit_outlined(Thingp t);
bool thing_is_blit_square_outlined(Thingp t);
bool thing_is_brazier(Thingp t);
bool thing_is_bridge(Thingp t);
bool thing_is_chasm(Thingp t);
bool thing_is_corridor(Thingp t);
bool thing_is_crushable_underfoot(Thingp t);
bool thing_is_cursor_hazard(Thingp t);
bool thing_is_cursor_path_blocker(Thingp t);
bool thing_is_cursor_path_hazard(Thingp t);
bool thing_is_cursor_path(Thingp t);
bool thing_is_cursor(Thingp t);
bool thing_is_deep_water(Thingp t);
bool thing_is_described_cursor(Thingp t);
bool thing_is_dirt(Thingp t);
bool thing_is_door(Thingp t);
bool thing_is_dungeon_entrance(Thingp t);
bool thing_is_entrance(Thingp t);
bool thing_is_ethereal(Thingp t);
bool thing_is_exit(Thingp t);
bool thing_is_floor(Thingp t);
bool thing_is_foliage(Thingp t);
bool thing_is_ghost(Thingp t);
bool thing_is_goblin(Thingp t);
bool thing_is_grass(Thingp t);
bool thing_is_key(Thingp t);
bool thing_is_lava(Thingp t);
bool thing_is_level_across(Thingp t);
bool thing_is_level_curr(Thingp t);
bool thing_is_level_down(Thingp t);
bool thing_is_level_final(Thingp t);
bool thing_is_level_next(Thingp t);
bool thing_is_level_not_visited(Thingp t);
bool thing_is_level_visited(Thingp t);
bool thing_is_levitating(Thingp t);
bool thing_is_light_source(Thingp t);
bool thing_is_minion(Thingp t);
bool thing_is_mob(Thingp t);
bool thing_is_mob1(Thingp t);
bool thing_is_mob2(Thingp t);
bool thing_is_monst(Thingp t);
bool thing_is_monst1(Thingp t);
bool thing_is_monst2(Thingp t);
bool thing_is_obstacle_block_or_door(Thingp t);
bool thing_is_obstacle_block(Thingp t);
bool thing_is_pillar(Thingp t);
bool thing_is_player(Thingp t);
bool thing_is_rock(Thingp t);
bool thing_is_secret_door(Thingp t);
bool thing_is_slime(Thingp t);
bool thing_is_teleport(Thingp t);
bool thing_is_tickable(Thingp t);
bool thing_is_tiled(Thingp t);
bool thing_is_trap(Thingp t);
bool thing_is_treasure(Thingp t);
bool thing_is_treasure1(Thingp t);
bool thing_is_treasure2(Thingp t);
bool thing_is_unused1(Thingp t);
bool thing_is_unused10(Thingp t);
bool thing_is_unused11(Thingp t);
bool thing_is_unused12(Thingp t);
bool thing_is_unused13(Thingp t);
bool thing_is_unused14(Thingp t);
bool thing_is_unused15(Thingp t);
bool thing_is_unused16(Thingp t);
bool thing_is_unused17(Thingp t);
bool thing_is_unused18(Thingp t);
bool thing_is_unused19(Thingp t);
bool thing_is_unused2(Thingp t);
bool thing_is_unused20(Thingp t);
bool thing_is_unused21(Thingp t);
bool thing_is_unused22(Thingp t);
bool thing_is_unused23(Thingp t);
bool thing_is_unused24(Thingp t);
bool thing_is_unused25(Thingp t);
bool thing_is_unused26(Thingp t);
bool thing_is_unused27(Thingp t);
bool thing_is_unused28(Thingp t);
bool thing_is_unused29(Thingp t);
bool thing_is_unused3(Thingp t);
bool thing_is_unused30(Thingp t);
bool thing_is_unused31(Thingp t);
bool thing_is_unused32(Thingp t);
bool thing_is_unused33(Thingp t);
bool thing_is_unused34(Thingp t);
bool thing_is_unused35(Thingp t);
bool thing_is_unused36(Thingp t);
bool thing_is_unused37(Thingp t);
bool thing_is_unused38(Thingp t);
bool thing_is_unused39(Thingp t);
bool thing_is_unused4(Thingp t);
bool thing_is_unused40(Thingp t);
bool thing_is_unused41(Thingp t);
bool thing_is_unused42(Thingp t);
bool thing_is_unused43(Thingp t);
bool thing_is_unused44(Thingp t);
bool thing_is_unused45(Thingp t);
bool thing_is_unused46(Thingp t);
bool thing_is_unused47(Thingp t);
bool thing_is_unused48(Thingp t);
bool thing_is_unused49(Thingp t);
bool thing_is_unused5(Thingp t);
bool thing_is_unused50(Thingp t);
bool thing_is_unused51(Thingp t);
bool thing_is_unused52(Thingp t);
bool thing_is_unused53(Thingp t);
bool thing_is_unused54(Thingp t);
bool thing_is_unused55(Thingp t);
bool thing_is_unused56(Thingp t);
bool thing_is_unused57(Thingp t);
bool thing_is_unused6(Thingp t);
bool thing_is_unused7(Thingp t);
bool thing_is_unused8(Thingp t);
bool thing_is_unused9(Thingp t);
bool thing_is_walk_through_walls(Thingp t);
bool thing_is_wall(Thingp t);
bool thing_is_water(Thingp t);
// end sort marker1 }

#endif
