//
// Copyright goblinhack@gmail.com
//

#pragma once
#ifndef _MY_THING_HPP_
#define _MY_THING_HPP_

#include "my_color.hpp"
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
  //
  // Holds the cursor path as we walk it
  //
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
  // Weight in grams. Impacts things like grass being crushed.
  //
  int32_t _weight;
  //
  // Temperature in celsius.
  //
  int16_t _temperature;
  int16_t _value1;
  int16_t _value2;
  int16_t _value3;
  int16_t _value4;
  int16_t _value5;
  int16_t _value6;
  int16_t _value7;
  int16_t _value8;
  int16_t _value9;
  int16_t _value10;
  int16_t _value11;
  int16_t _value12;
  int16_t _value13;
  int16_t _value14;
  int16_t _value15;
  int16_t _value16;
  int16_t _value17;
  int16_t _value18;
  int16_t _value19;
  int16_t _value20;
  int16_t _value21;
  int16_t _value22;
  int16_t _value23;
  int16_t _value24;
  int16_t _value25;
  int16_t _value26;
  int16_t _value27;
  int16_t _value28;
  int16_t _jump_distance;
  //
  // Lifespan remaining in ticks
  //
  int16_t _lifespan;
  //
  // How long this thing has lived
  //
  int16_t _age;
  //
  // Used in lava, water etc...
  //
  int16_t _submerged_pct;
  //
  // Health of the item.
  //
  int16_t _health;
  //
  // Accumulates and holds the amount of time we've been falling.
  //
  int16_t _is_falling;
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
  // Was set fire to.
  //
  bool _is_burning : 1;
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
  //
  // Currently teleporting between tiles. The thing is already at the destination.
  //
  bool _is_teleporting : 1;
  //
  // Currently jumping between tiles. The thing is already at the destination.
  //
  bool _is_jumping : 1;
} Thing;

Tpp thing_tp(Thingp);

Thingp thing_and_tp_get_at(Gamep, Levelsp, Levelp, spoint p, int slot, Tpp * = nullptr);
Thingp thing_find(Gamep, Levelsp, ThingId id);
Thingp thing_find_optional(Gamep, Levelsp, ThingId id);
Thingp thing_get(Gamep, Levelsp, Levelp, spoint p, int slot);
Thingp thing_init(Gamep, Levelsp, Levelp, Tpp, spoint);
Thingp thing_spawn(Gamep, Levelsp, Levelp, Tpp, spoint);
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
void thing_move_or_jump_finish(Gamep, Levelsp, Levelp, Thingp);
void thing_tick_end(Gamep, Levelsp, Levelp, Thingp);
void thing_tick_idle(Gamep, Levelsp, Levelp, Thingp);
void thing_tick_begin(Gamep, Levelsp, Levelp, Thingp);
void thing_pop(Gamep, Levelsp, Thingp);
void thing_push(Gamep, Levelsp, Levelp, Thingp);
void thing_set_dir_from_delta(Thingp, int dx, int dy);
void thing_level_warp_to_entrance(Gamep, Levelsp, Levelp, Thingp);
void thing_collision_handle(Gamep, Levelsp, Levelp, Thingp);
void thing_temperature_handle(Gamep, Levelsp, Levelp, Thingp it, Thingp me, int t);
void thing_temperature_damage_handle(Gamep, Levelsp, Levelp, Thingp it, Thingp me, int t);
void thing_water_handle(Gamep, Levelsp, Levelp, Thingp me);
void thing_explosion_handle(Gamep, Levelsp, Levelp, Thingp me);
void thing_chasm_handle(Gamep, Levelsp, Levelp, Thingp me);
bool thing_shove_handle(Gamep, Levelsp, Levelp, Thingp, spoint at);
void thing_update_pos(Gamep, Thingp);
void thing_dead(Gamep, Levelsp, Levelp, Thingp, ThingEvent &);
void thing_fall(Gamep, Levelsp, Levelp, Thingp);
void thing_open(Gamep, Levelsp, Levelp, Thingp);
void thing_damage(Gamep, Levelsp, Levelp, Thingp, ThingEvent &);
void thing_anim_time_step(Gamep, Levelsp, Levelp, Thingp, int time_step);
void thing_fall_time_step(Gamep, Levelsp, Levelp, Thingp, int time_step);
void thing_anim_init(Gamep, Levelsp, Levelp, Thingp);
void thing_is_dead_handle(Gamep, Levelsp, Levelp, Thingp);
void thing_is_burning_handle(Gamep, Levelsp, Levelp, Thingp);
void thing_continue_to_burn_check(Gamep, Levelsp, Levelp, Thingp);

Thingp       thing_player(Gamep);
ThingPlayerp thing_player_struct(Gamep);

void player_map_center(Gamep, Levelsp, Levelp);
bool player_check_if_target_needs_move_confirm(Gamep, Levelsp, Levelp, spoint);
void player_move_accum(Gamep, Levelsp, Levelp, bool up, bool down, bool left, bool right);
void player_move_delta(Gamep, Levelsp, Levelp, int dx, int dy, int dz);
void player_move_reset(Gamep, Levelsp, Levelp);
void player_reached_exit(Gamep, Levelsp, Levelp, Thingp);
void player_reached_entrance(Gamep, Levelsp, Levelp, Thingp);
void player_fell(Gamep, Levelsp, Levelp, Levelp, Thingp);
void player_collision_handle(Gamep, Levelsp, Levelp, Thingp);
bool player_jump(Gamep, Levelsp, Levelp, Thingp, spoint);
bool player_move_request(Gamep, bool up, bool down, bool left, bool right);
bool player_move_to_next(Gamep, Levelsp, Levelp, Thingp);

bool thing_can_move_to(Gamep, Levelsp, Levelp, Thingp, spoint to);
bool thing_can_move_to_by_shoving(Gamep, Levelsp, Levelp, Thingp, spoint to);
bool thing_move_to_next(Gamep, Levelsp, Levelp, Thingp);
bool thing_is_dir_down(Thingp);
bool thing_is_dir_tr(Thingp);
bool thing_move_to(Gamep, Levelsp, Levelp, Thingp, spoint to);
bool thing_jump_to(Gamep, Levelsp, Levelp, Thingp, spoint to, bool warn = true);
bool thing_teleport(Gamep, Levelsp, Levelp, Thingp);
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
void thing_is_dead_unset(Gamep, Levelsp, Levelp, Thingp);

bool thing_is_burning(Thingp);
void thing_is_burning_set(Gamep, Levelsp, Levelp, Thingp, bool val = true);
void thing_is_burning_unset(Gamep, Levelsp, Levelp, Thingp);

bool thing_is_scheduled_for_cleanup(Thingp);
void thing_is_scheduled_for_cleanup_set(Gamep, Levelsp, Levelp, Thingp, bool val = true);
void thing_is_scheduled_for_cleanup_unset(Gamep, Levelsp, Levelp, Thingp);

bool thing_is_corpse(Thingp);
void thing_is_corpse_set(Gamep, Levelsp, Levelp, Thingp, bool val = true);
void thing_is_corpse_unset(Gamep, Levelsp, Levelp, Thingp);

bool thing_is_sleeping(Thingp);
void thing_is_sleeping_set(Gamep, Levelsp, Levelp, Thingp, bool val = true);
void thing_is_sleeping_unset(Gamep, Levelsp, Levelp, Thingp);

bool thing_is_on_map(Thingp);
void thing_is_on_map_set(Gamep, Levelsp, Levelp, Thingp, bool val = true);
void thing_is_on_map_unset(Gamep, Levelsp, Levelp, Thingp);

bool thing_is_moving(Thingp);
void thing_is_moving_set(Gamep, Levelsp, Levelp, Thingp, bool val = true);
void thing_is_moving_unset(Gamep, Levelsp, Levelp, Thingp);

bool thing_is_teleporting(Thingp);
void thing_is_teleporting_set(Gamep, Levelsp, Levelp, Thingp, bool val = true);
void thing_is_teleporting_unset(Gamep, Levelsp, Levelp, Thingp);

bool thing_is_jumping(Thingp);
void thing_is_jumping_set(Gamep, Levelsp, Levelp, Thingp, bool val = true);
void thing_is_jumping_unset(Gamep, Levelsp, Levelp, Thingp);

bool thing_is_open(Thingp);
void thing_is_open_set(Gamep, Levelsp, Levelp, Thingp, bool val = true);
void thing_is_open_unset(Gamep, Levelsp, Levelp, Thingp);

int  thing_is_falling(Thingp);
void thing_is_falling_set(Gamep, Levelsp, Levelp, Thingp, int val);
int  thing_is_falling_incr(Gamep, Levelsp, Levelp, Thingp, int val = 1);
int  thing_is_falling_decr(Gamep, Levelsp, Levelp, Thingp, int val = 1);

int thing_speed(Thingp);
int thing_speed_set(Gamep, Levelsp, Levelp, Thingp, int val);

int thing_weight(Thingp);
int thing_weight_set(Gamep, Levelsp, Levelp, Thingp, int val);

int thing_temperature(Thingp);
int thing_temperature_set(Gamep, Levelsp, Levelp, Thingp, int val);
int thing_temperature_incr(Gamep, Levelsp, Levelp, Thingp, int val = 1);
int thing_temperature_decr(Gamep, Levelsp, Levelp, Thingp, int val = 1);

int thing_value1(Thingp);
int thing_value1_set(Gamep, Levelsp, Levelp, Thingp, int val);
int thing_value1_incr(Gamep, Levelsp, Levelp, Thingp, int val = 1);
int thing_value1_decr(Gamep, Levelsp, Levelp, Thingp, int val = 1);

int thing_value2(Thingp);
int thing_value2_set(Gamep, Levelsp, Levelp, Thingp, int val);
int thing_value2_incr(Gamep, Levelsp, Levelp, Thingp, int val = 1);
int thing_value2_decr(Gamep, Levelsp, Levelp, Thingp, int val = 1);

int thing_value3(Thingp);
int thing_value3_set(Gamep, Levelsp, Levelp, Thingp, int val);
int thing_value3_incr(Gamep, Levelsp, Levelp, Thingp, int val = 1);
int thing_value3_decr(Gamep, Levelsp, Levelp, Thingp, int val = 1);

int thing_value4(Thingp);
int thing_value4_set(Gamep, Levelsp, Levelp, Thingp, int val);
int thing_value4_incr(Gamep, Levelsp, Levelp, Thingp, int val = 1);
int thing_value4_decr(Gamep, Levelsp, Levelp, Thingp, int val = 1);

int thing_value5(Thingp);
int thing_value5_set(Gamep, Levelsp, Levelp, Thingp, int val);
int thing_value5_incr(Gamep, Levelsp, Levelp, Thingp, int val = 1);
int thing_value5_decr(Gamep, Levelsp, Levelp, Thingp, int val = 1);

int thing_value6(Thingp);
int thing_value6_set(Gamep, Levelsp, Levelp, Thingp, int val);
int thing_value6_incr(Gamep, Levelsp, Levelp, Thingp, int val = 1);
int thing_value6_decr(Gamep, Levelsp, Levelp, Thingp, int val = 1);

int thing_value7(Thingp);
int thing_value7_set(Gamep, Levelsp, Levelp, Thingp, int val);
int thing_value7_incr(Gamep, Levelsp, Levelp, Thingp, int val = 1);
int thing_value7_decr(Gamep, Levelsp, Levelp, Thingp, int val = 1);

int thing_value8(Thingp);
int thing_value8_set(Gamep, Levelsp, Levelp, Thingp, int val);
int thing_value8_incr(Gamep, Levelsp, Levelp, Thingp, int val = 1);
int thing_value8_decr(Gamep, Levelsp, Levelp, Thingp, int val = 1);

int thing_value9(Thingp);
int thing_value9_set(Gamep, Levelsp, Levelp, Thingp, int val);
int thing_value9_incr(Gamep, Levelsp, Levelp, Thingp, int val = 1);
int thing_value9_decr(Gamep, Levelsp, Levelp, Thingp, int val = 1);

int thing_value10(Thingp);
int thing_value10_set(Gamep, Levelsp, Levelp, Thingp, int val);
int thing_value10_incr(Gamep, Levelsp, Levelp, Thingp, int val = 1);
int thing_value10_decr(Gamep, Levelsp, Levelp, Thingp, int val = 1);

int thing_value11(Thingp);
int thing_value11_set(Gamep, Levelsp, Levelp, Thingp, int val);
int thing_value11_incr(Gamep, Levelsp, Levelp, Thingp, int val = 1);
int thing_value11_decr(Gamep, Levelsp, Levelp, Thingp, int val = 1);

int thing_value12(Thingp);
int thing_value12_set(Gamep, Levelsp, Levelp, Thingp, int val);
int thing_value12_incr(Gamep, Levelsp, Levelp, Thingp, int val = 1);
int thing_value12_decr(Gamep, Levelsp, Levelp, Thingp, int val = 1);

int thing_value13(Thingp);
int thing_value13_set(Gamep, Levelsp, Levelp, Thingp, int val);
int thing_value13_incr(Gamep, Levelsp, Levelp, Thingp, int val = 1);
int thing_value13_decr(Gamep, Levelsp, Levelp, Thingp, int val = 1);

int thing_value14(Thingp);
int thing_value14_set(Gamep, Levelsp, Levelp, Thingp, int val);
int thing_value14_incr(Gamep, Levelsp, Levelp, Thingp, int val = 1);
int thing_value14_decr(Gamep, Levelsp, Levelp, Thingp, int val = 1);

int thing_value15(Thingp);
int thing_value15_set(Gamep, Levelsp, Levelp, Thingp, int val);
int thing_value15_incr(Gamep, Levelsp, Levelp, Thingp, int val = 1);
int thing_value15_decr(Gamep, Levelsp, Levelp, Thingp, int val = 1);

int thing_value16(Thingp);
int thing_value16_set(Gamep, Levelsp, Levelp, Thingp, int val);
int thing_value16_incr(Gamep, Levelsp, Levelp, Thingp, int val = 1);
int thing_value16_decr(Gamep, Levelsp, Levelp, Thingp, int val = 1);

int thing_value17(Thingp);
int thing_value17_set(Gamep, Levelsp, Levelp, Thingp, int val);
int thing_value17_incr(Gamep, Levelsp, Levelp, Thingp, int val = 1);
int thing_value17_decr(Gamep, Levelsp, Levelp, Thingp, int val = 1);

int thing_value18(Thingp);
int thing_value18_set(Gamep, Levelsp, Levelp, Thingp, int val);
int thing_value18_incr(Gamep, Levelsp, Levelp, Thingp, int val = 1);
int thing_value18_decr(Gamep, Levelsp, Levelp, Thingp, int val = 1);

int thing_value19(Thingp);
int thing_value19_set(Gamep, Levelsp, Levelp, Thingp, int val);
int thing_value19_incr(Gamep, Levelsp, Levelp, Thingp, int val = 1);
int thing_value19_decr(Gamep, Levelsp, Levelp, Thingp, int val = 1);

int thing_value20(Thingp);
int thing_value20_set(Gamep, Levelsp, Levelp, Thingp, int val);
int thing_value20_incr(Gamep, Levelsp, Levelp, Thingp, int val = 1);
int thing_value20_decr(Gamep, Levelsp, Levelp, Thingp, int val = 1);

int thing_value21(Thingp);
int thing_value21_set(Gamep, Levelsp, Levelp, Thingp, int val);
int thing_value21_incr(Gamep, Levelsp, Levelp, Thingp, int val = 1);
int thing_value21_decr(Gamep, Levelsp, Levelp, Thingp, int val = 1);

int thing_value22(Thingp);
int thing_value22_set(Gamep, Levelsp, Levelp, Thingp, int val);
int thing_value22_incr(Gamep, Levelsp, Levelp, Thingp, int val = 1);
int thing_value22_decr(Gamep, Levelsp, Levelp, Thingp, int val = 1);

int thing_value23(Thingp);
int thing_value23_set(Gamep, Levelsp, Levelp, Thingp, int val);
int thing_value23_incr(Gamep, Levelsp, Levelp, Thingp, int val = 1);
int thing_value23_decr(Gamep, Levelsp, Levelp, Thingp, int val = 1);

int thing_value24(Thingp);
int thing_value24_set(Gamep, Levelsp, Levelp, Thingp, int val);
int thing_value24_incr(Gamep, Levelsp, Levelp, Thingp, int val = 1);
int thing_value24_decr(Gamep, Levelsp, Levelp, Thingp, int val = 1);

int thing_value25(Thingp);
int thing_value25_set(Gamep, Levelsp, Levelp, Thingp, int val);
int thing_value25_incr(Gamep, Levelsp, Levelp, Thingp, int val = 1);
int thing_value25_decr(Gamep, Levelsp, Levelp, Thingp, int val = 1);

int thing_value26(Thingp);
int thing_value26_set(Gamep, Levelsp, Levelp, Thingp, int val);
int thing_value26_incr(Gamep, Levelsp, Levelp, Thingp, int val = 1);
int thing_value26_decr(Gamep, Levelsp, Levelp, Thingp, int val = 1);

int thing_value27(Thingp);
int thing_value27_set(Gamep, Levelsp, Levelp, Thingp, int val);
int thing_value27_incr(Gamep, Levelsp, Levelp, Thingp, int val = 1);
int thing_value27_decr(Gamep, Levelsp, Levelp, Thingp, int val = 1);

int thing_value28(Thingp);
int thing_value28_set(Gamep, Levelsp, Levelp, Thingp, int val);
int thing_value28_incr(Gamep, Levelsp, Levelp, Thingp, int val = 1);
int thing_value28_decr(Gamep, Levelsp, Levelp, Thingp, int val = 1);

int thing_jump_distance(Thingp);
int thing_jump_distance_set(Gamep, Levelsp, Levelp, Thingp, int val);
int thing_jump_distance_incr(Gamep, Levelsp, Levelp, Thingp, int val = 1);
int thing_jump_distance_decr(Gamep, Levelsp, Levelp, Thingp, int val = 1);

int thing_lifespan(Thingp);
int thing_lifespan_set(Gamep, Levelsp, Levelp, Thingp, int val);
int thing_lifespan_incr(Gamep, Levelsp, Levelp, Thingp, int val = 1);
int thing_lifespan_decr(Gamep, Levelsp, Levelp, Thingp, int val = 1);

int thing_submerged_pct(Thingp);
int thing_submerged_pct_set(Gamep, Levelsp, Levelp, Thingp, int val);
int thing_submerged_pct_incr(Gamep, Levelsp, Levelp, Thingp, int val = 1);
int thing_submerged_pct_decr(Gamep, Levelsp, Levelp, Thingp, int val = 1);

int thing_age(Thingp);
int thing_age_set(Gamep, Levelsp, Levelp, Thingp, int val);
int thing_age_incr(Gamep, Levelsp, Levelp, Thingp, int val = 1);
int thing_age_decr(Gamep, Levelsp, Levelp, Thingp, int val = 1);

int thing_health(Thingp);
int thing_health_set(Gamep, Levelsp, Levelp, Thingp, int val);
int thing_health_incr(Gamep, Levelsp, Levelp, Thingp, int val = 1);
int thing_health_decr(Gamep, Levelsp, Levelp, Thingp, int val = 1);

bool thing_is_immune_to(Thingp, ThingEventType);

void thing_display(Gamep, Levelsp, Levelp, Tpp, Thingp, spoint tl, spoint br, uint16_t tile_index);
void thing_get_coords(Gamep, Levelsp, Levelp, spoint, Tpp, Thingp, spoint *, spoint *, uint16_t *tile_index);
void thing_blit_text(Gamep, Levelsp, Levelp, spoint tl, spoint br, std::string const &text, color fg, bool outline);

// begin sort marker1 {
bool thing_is_able_to_jump(Thingp);
bool thing_is_able_to_shove(Thingp);
bool thing_is_animated_can_hflip(Thingp);
bool thing_is_animated_no_dir(Thingp);
bool thing_is_animated_sync_first(Thingp);
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
bool thing_is_combustible(Thingp);
bool thing_is_corpse_on_death(Thingp);
bool thing_is_corridor(Thingp);
bool thing_is_crushable(Thingp);
bool thing_is_cursor_hazard(Thingp);
bool thing_is_cursor_path_hazard(Thingp);
bool thing_is_cursor_path_none(Thingp);
bool thing_is_cursor_path(Thingp);
bool thing_is_cursor(Thingp);
bool thing_is_damage_capped(Thingp);
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
bool thing_is_floating(Thingp);
bool thing_is_floor(Thingp);
bool thing_is_flying(Thingp);
bool thing_is_foliage(Thingp);
bool thing_is_gaseous(Thingp);
bool thing_is_ghost(Thingp);
bool thing_is_goblin(Thingp);
bool thing_is_grass(Thingp);
bool thing_is_indestructible(Thingp);
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
bool thing_is_needs_move_confirm(Thingp);
bool thing_is_obs_to_cursor_path(Thingp);
bool thing_is_obs_to_explosion(Thingp);
bool thing_is_obs_to_falling(Thingp);
bool thing_is_obs_to_fire(Thingp);
bool thing_is_obs_to_jump_landing(Thingp);
bool thing_is_obs_to_jump_over(Thingp);
bool thing_is_obs_to_movement(Thingp);
bool thing_is_physics_explosion(Thingp);
bool thing_is_physics_gravity(Thingp);
bool thing_is_physics_temperature(Thingp);
bool thing_is_physics_water(Thingp);
bool thing_is_pillar(Thingp);
bool thing_is_player(Thingp);
bool thing_is_rock(Thingp);
bool thing_is_secret_door(Thingp);
bool thing_is_shovable(Thingp);
bool thing_is_slime(Thingp);
bool thing_is_smoke(Thingp);
bool thing_is_steam(Thingp);
bool thing_is_submergible(Thingp);
bool thing_is_teleport_blocked(Thingp);
bool thing_is_teleport(Thingp);
bool thing_is_tick_delay_on_spawn(Thingp);
bool thing_is_tickable(Thingp);
bool thing_is_tiled(Thingp);
bool thing_is_trap(Thingp);
bool thing_is_treasure(Thingp);
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
bool thing_is_openable(Thingp);
bool thing_is_unused3(Thingp);
bool thing_is_unused4(Thingp);
bool thing_is_unused5(Thingp);
bool thing_is_unused6(Thingp);
bool thing_is_unused7(Thingp);
bool thing_is_unused8(Thingp);
bool thing_is_unused9(Thingp);
bool thing_is_wait_on_dead_anim(Thingp);
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

enum {
  TEXT_INCLUDE_OWNER = 1,
  TEXT_EXCLUDE_DEATH = 2,
  TEXT_APOSTROPHIZE  = 4,
  TEXT_PLURALIZE     = 8,
};

typedef uint8_t ThingTextFlags;

std::string to_string(Gamep, Thingp);
std::string to_string(Gamep, ThingEvent &);
std::string thing_apostrophize_name(Thingp, ThingTextFlags);
std::string thing_pluralize_name(Thingp, ThingTextFlags);
std::string thing_the_long_name(Gamep, Levelsp, Levelp, Thingp, ThingTextFlags flags = 0);
std::string thing_long_name(Gamep, Levelsp, Levelp, Thingp, ThingTextFlags flags = 0);
std::string to_death_reason_string(Gamep, Levelsp, Levelp, Thingp, ThingEvent &);

#endif
