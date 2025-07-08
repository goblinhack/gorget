//
// Copyright goblinhack@gmail.com
//

#pragma once
#ifndef _MY_THING_HPP_
#define _MY_THING_HPP_

#include "my_game_defs.hpp"
#include "my_spoint.hpp"
#include "my_tp.hpp"
#include "my_types.hpp"

#include <string>

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

//
// Some kind of event that befalls a thing. Usually an attack
//
typedef struct ThingEvent_ {
  //
  // What happened?
  //
  std::string reason;
  //
  // What type of event/attack?
  //
  ThingEventType event_type = THING_EVENT_NONE;
  //
  // How much damage, if this is an attack?
  //
  int damage = 0;
  //
  // Whodunnit?
  //
  Thingp source = nullptr;
} ThingEvent;

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
  //
  // For hiscores
  //
  int16_t levels_completed;
  struct {
    spoint  points[ THING_MOVE_PATH_MAX ];
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
  // If owned, by whom
  //
  ThingId owner_id;
  //
  // For players and monsters
  //
  ThingAiId ai_id;
  //
  // Map co-ords.
  //
  spoint at;
  //
  // Which level am I on?
  //
  LevelNum level_num;
  //
  // Previous map co-ords. Does not change when the move finishes.
  //
  spoint old_at;
  //
  // Previous map co-ords used for interpolation when moving. Changes when
  // the move finishes.
  //
  spoint moving_from;
  //
  // Last location we were pushed onto the map.
  //
  spoint last_pushed_at;
  //
  // Direction
  //
  uint8_t dir;
  //
  // Idle etc...
  //
  ThingAnim anim_type;
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
  // Temperature in celsius.
  //
  int16_t _temperature;
  //
  // Health of the item.
  //
  int16_t _health;
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
  spoint pix_at;
  //
  // Increases per tick and when it reaches 1, allows the thing to move
  //
  float thing_dt;
  //
  // Keeps track of counters in the level this thing has modified.
  //
  uint8_t count[ THING_FLAG_ENUM_MAX ];
  //
  // Snuffed it.
  //
  bool _is_dead : 1;
  //
  // Snuffed it and is a corpse.
  //
  bool _is_corpse : 1;
  //
  // If a thing has died and leaves no corpse, schedule it to be removed from the game.
  //
  bool _is_scheduled_for_cleanup : 1;
  //
  // Zzz
  //
  bool _is_sleeping : 1;
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

Thingp thing_and_tp_get_at(Gamep, Levelsp, Levelp, spoint p, int slot, Tpp * = nullptr);
Thingp thing_find(Gamep, Levelsp, ThingId id);
Thingp thing_find_optional(Gamep, Levelsp, ThingId id);
Thingp thing_get(Gamep, Levelsp, Levelp, spoint p, int slot);
Thingp thing_init(Gamep, Levelsp, Levelp, Tpp, spoint p);
Levelp thing_level(Gamep, Levelsp, Thingp);
void   thing_stats_dump(Gamep, Levelsp);

ThingAip thing_ai(Gamep, Thingp);

void thing_dir_bl_set(Thingp, uint8_t);
void thing_dir_br_set(Thingp, uint8_t);
void thing_dir_down_set(Thingp, uint8_t);
void thing_dir_left_set(Thingp, uint8_t);
void thing_dir_right_set(Thingp, uint8_t);
void thing_dir_tl_set(Thingp, uint8_t);
void thing_dir_tr_set(Thingp, uint8_t);
void thing_dir_up_set(Thingp, uint8_t);
void thing_fini(Gamep, Levelsp, Levelp, Thingp);
void thing_interpolate(Gamep, Thingp, float dt);
void thing_move_finish(Gamep, Levelsp, Levelp, Thingp);
void thing_tick_end(Gamep, Levelsp, Levelp, Thingp);
void thing_tick_idle(Gamep, Levelsp, Levelp, Thingp);
void thing_tick_begin(Gamep, Levelsp, Levelp, Thingp);
void thing_pop(Gamep, Levelsp, Thingp);
void thing_push(Gamep, Levelsp, Levelp, Thingp);
void thing_set_dir_from_delta(Thingp, int dx, int dy);
void thing_level_warp_to_entrance(Gamep, Levelsp, Levelp, Thingp);
void thing_collision_handle(Gamep, Levelsp, Levelp, Thingp);
void thing_temperature_handle(Gamep, Levelsp, Levelp, Thingp it, Thingp me, int t);
bool thing_shove_handle(Gamep, Levelsp, Levelp, Thingp, spoint at);
void thing_update_pos(Gamep, Thingp);
void thing_dead(Gamep, Levelsp, Levelp, Thingp, ThingEvent &);
void thing_damage(Gamep, Levelsp, Levelp, Thingp, ThingEvent &);
void thing_anim_step(Gamep, Levelsp, Levelp, Thingp, int time_step);
void thing_anim_reset(Gamep, Levelsp, Levelp, Thingp);
void thing_anim_init(Gamep, Levelsp, Levelp, Thingp);
void thing_is_dead_handle(Gamep, Levelsp, Levelp, Thingp);

Thingp       thing_player(Gamep);
ThingPlayerp thing_player_struct(Gamep);

void player_map_center(Gamep, Levelsp, Levelp);
void player_move_accum(Gamep, Levelsp, Levelp, bool up, bool down, bool left, bool right);
void player_move_delta(Gamep, Levelsp, Levelp, int dx, int dy, int dz);
void player_move_reset(Gamep, Levelsp, Levelp);
void player_reached_exit(Gamep, Levelsp, Levelp, Thingp);
void player_reached_entrance(Gamep, Levelsp, Levelp, Thingp);
void player_collision_handle(Gamep, Levelsp, Levelp, Thingp);
bool player_move_request(Gamep, bool up, bool down, bool left, bool right);

bool thing_can_move_to(Gamep, Levelsp, Levelp, Thingp, spoint to);
bool thing_can_move_to_by_shoving(Gamep, Levelsp, Levelp, Thingp, spoint to);
bool thing_move_to_next(Gamep, Levelsp, Levelp, Thingp t);
bool thing_is_dir_down(Thingp);
bool thing_is_dir_tr(Thingp);
bool thing_move_to(Gamep, Levelsp, Levelp, Thingp, spoint to);
bool thing_shove_to(Gamep, Levelsp, Levelp, Thingp, spoint to);
bool thing_warp_to(Gamep, Levelsp, Levelp, Thingp, spoint to);
bool thing_is_dir_tl(Thingp);
bool thing_is_dir_br(Thingp);
bool thing_is_dir_bl(Thingp);
bool thing_is_dir_left(Thingp);
bool thing_is_dir_right(Thingp);
bool thing_is_dir_up(Thingp);

Thingp top_owner(Gamep, Levelsp, Levelp, Thingp);
Thingp immediate_owner(Gamep, Levelsp, Levelp, Thingp);

bool thing_is_dead(Thingp);
void thing_is_dead_set(Gamep, Levelsp, Levelp, Thingp, bool val = true);

bool thing_is_scheduled_for_cleanup(Thingp);
void thing_is_scheduled_for_cleanup_set(Gamep, Levelsp, Levelp, Thingp, bool val = true);

bool thing_is_corpse(Thingp);
void thing_is_corpse_set(Gamep, Levelsp, Levelp, Thingp, bool val = true);

bool thing_is_sleeping(Thingp);
void thing_is_sleeping_set(Gamep, Levelsp, Levelp, Thingp, bool val = true);

bool thing_is_open(Thingp);
void thing_is_open_set(Gamep, Levelsp, Levelp, Thingp, bool val = true);

bool thing_is_on_map(Thingp);
void thing_is_on_map_set(Gamep, Levelsp, Levelp, Thingp, bool val = true);

bool thing_is_moving(Thingp);
void thing_is_moving_set(Gamep, Levelsp, Levelp, Thingp, bool val = true);

int thing_speed(Thingp);
int thing_speed_set(Gamep, Levelsp, Levelp, Thingp, int val);

int thing_weight(Thingp);
int thing_weight_set(Gamep, Levelsp, Levelp, Thingp, int val);

int thing_temperature(Thingp);
int thing_temperature_set(Gamep, Levelsp, Levelp, Thingp, int val);
int thing_temperature_incr(Gamep, Levelsp, Levelp, Thingp, int val = 1);
int thing_temperature_decr(Gamep, Levelsp, Levelp, Thingp, int val = 1);

int thing_health(Thingp);
int thing_health_set(Gamep, Levelsp, Levelp, Thingp, int val);
int thing_health_incr(Gamep, Levelsp, Levelp, Thingp, int val = 1);
int thing_health_decr(Gamep, Levelsp, Levelp, Thingp, int val = 1);

bool thing_is_immune_to(Thingp, ThingEventType);

// begin sort marker1 {
bool thing_is_able_to_change_temperature(Thingp);
bool thing_is_able_to_shove(Thingp);
bool thing_is_able_to_walk_through_walls(Thingp);
bool thing_is_animated_can_hflip(Thingp);
bool thing_is_animated_no_dir(Thingp);
bool thing_is_animated_same_first_tile(Thingp);
bool thing_is_animated(Thingp);
bool thing_is_barrel(Thingp);
bool thing_is_blit_centered(Thingp);
bool thing_is_blit_on_ground(Thingp);
bool thing_is_blit_outlined(Thingp);
bool thing_is_blit_square_outlined(Thingp);
bool thing_is_brazier(Thingp);
bool thing_is_bridge(Thingp);
bool thing_is_broken_on_death(Thingp);
bool thing_is_burnable(Thingp);
bool thing_is_chasm(Thingp);
bool thing_is_corpse_on_death(Thingp);
bool thing_is_corridor(Thingp);
bool thing_is_crushable_underfoot(Thingp);
bool thing_is_cursor_hazard(Thingp);
bool thing_is_cursor_path_blocker(Thingp);
bool thing_is_cursor_path_hazard(Thingp);
bool thing_is_cursor_path(Thingp);
bool thing_is_cursor(Thingp);
bool thing_is_dead_on_shoving(Thingp);
bool thing_is_deep_water(Thingp);
bool thing_is_described_cursor(Thingp);
bool thing_is_dirt(Thingp);
bool thing_is_door(Thingp);
bool thing_is_dungeon_entrance(Thingp);
bool thing_is_entrance(Thingp);
bool thing_is_ethereal(Thingp);
bool thing_is_exit(Thingp);
bool thing_is_explosion(Thingp);
bool thing_is_extinguished_on_death(Thingp);
bool thing_is_fire(Thingp);
bool thing_is_floor(Thingp);
bool thing_is_foliage(Thingp);
bool thing_is_ghost(Thingp);
bool thing_is_goblin(Thingp);
bool thing_is_grass(Thingp);
bool thing_is_key(Thingp);
bool thing_is_lava(Thingp);
bool thing_is_level_across(Thingp);
bool thing_is_level_curr(Thingp);
bool thing_is_level_down(Thingp);
bool thing_is_level_final(Thingp);
bool thing_is_level_next(Thingp);
bool thing_is_level_not_visited(Thingp);
bool thing_is_level_visited(Thingp);
bool thing_is_levitating(Thingp);
bool thing_is_light_source(Thingp);
bool thing_is_loggable(Thingp);
bool thing_is_minion(Thingp);
bool thing_is_mob(Thingp);
bool thing_is_mob1(Thingp);
bool thing_is_mob2(Thingp);
bool thing_is_monst_group_0(Thingp);
bool thing_is_monst_group_1(Thingp);
bool thing_is_monst_group_2(Thingp);
bool thing_is_monst(Thingp);
bool thing_is_obstacle_block_or_door(Thingp);
bool thing_is_obstacle_block(Thingp);
bool thing_is_pillar(Thingp);
bool thing_is_player(Thingp);
bool thing_is_rock(Thingp);
bool thing_is_secret_door(Thingp);
bool thing_is_shovable(Thingp);
bool thing_is_slime(Thingp);
bool thing_is_smoke(Thingp);
bool thing_is_steam(Thingp);
bool thing_is_teleport(Thingp);
bool thing_is_tickable(Thingp);
bool thing_is_tiled(Thingp);
bool thing_is_trap(Thingp);
bool thing_is_treasure(Thingp);
bool thing_is_treasure1(Thingp);
bool thing_is_treasure2(Thingp);
bool thing_is_undead(Thingp);
bool thing_is_unused1(Thingp);
bool thing_is_unused10(Thingp);
bool thing_is_unused11(Thingp);
bool thing_is_unused12(Thingp);
bool thing_is_unused13(Thingp);
bool thing_is_unused14(Thingp);
bool thing_is_unused15(Thingp);
bool thing_is_unused16(Thingp);
bool thing_is_unused17(Thingp);
bool thing_is_unused18(Thingp);
bool thing_is_unused19(Thingp);
bool thing_is_unused2(Thingp);
bool thing_is_unused20(Thingp);
bool thing_is_unused21(Thingp);
bool thing_is_unused22(Thingp);
bool thing_is_unused23(Thingp);
bool thing_is_unused24(Thingp);
bool thing_is_unused25(Thingp);
bool thing_is_unused26(Thingp);
bool thing_is_unused27(Thingp);
bool thing_is_unused28(Thingp);
bool thing_is_unused29(Thingp);
bool thing_is_unused3(Thingp);
bool thing_is_unused30(Thingp);
bool thing_is_unused31(Thingp);
bool thing_is_unused32(Thingp);
bool thing_is_unused33(Thingp);
bool thing_is_unused34(Thingp);
bool thing_is_unused35(Thingp);
bool thing_is_unused36(Thingp);
bool thing_is_unused37(Thingp);
bool thing_is_unused38(Thingp);
bool thing_is_unused39(Thingp);
bool thing_is_unused4(Thingp);
bool thing_is_unused40(Thingp);
bool thing_is_unused5(Thingp);
bool thing_is_unused6(Thingp);
bool thing_is_unused7(Thingp);
bool thing_is_unused8(Thingp);
bool thing_is_unused9(Thingp);
bool thing_is_wait_on_anim_when_dead(Thingp);
bool thing_is_walk_through_walls(Thingp);
bool thing_is_wall(Thingp);
bool thing_is_water(Thingp);
// end sort marker1 }

void THING_CON(Thingp, const char *fmt, ...) CHECK_FORMAT_STR(printf, 2, 3);
void THING_DBG(Thingp, const char *fmt, ...) CHECK_FORMAT_STR(printf, 2, 3);
void THING_LOG(Thingp, const char *fmt, ...) CHECK_FORMAT_STR(printf, 2, 3);
void THING_WARN(Thingp, const char *fmt, ...) CHECK_FORMAT_STR(printf, 2, 3);
void THING_ERR(Thingp, const char *fmt, ...) CHECK_FORMAT_STR(printf, 2, 3);
void THING_TOPCON(Thingp, const char *fmt, ...) CHECK_FORMAT_STR(printf, 2, 3);
void THING_BOTCON(Thingp, const char *fmt, ...) CHECK_FORMAT_STR(printf, 2, 3);

std::string to_string(Thingp);
std::string to_string(ThingEvent &);
std::string thing_the_long_name(Gamep, Levelsp, Levelp, Thingp, bool include_owner = false);
std::string to_death_reason(ThingEvent &);

#endif
