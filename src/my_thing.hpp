//
// Copyright goblinhack@gmail.com
//

#pragma once
#ifndef _MY_THING_HPP_
#define _MY_THING_HPP_

#include "my_color.hpp"
#include "my_dmap.hpp"
#include "my_fpoint.hpp"
#include "my_game_defs.hpp"
#include "my_gl.hpp"
#include "my_spoint.hpp"
#include "my_tp.hpp"
#include "my_types.hpp"

#include <string>
#include <vector>

#define MY_ITERS_MAX 4

typedef union {
  struct {
    unsigned int val : 32;
  } __attribute__((__packed__)) a;
  struct {
    unsigned int entropy      : THING_ENTROPY_BITS;
    unsigned int per_level_id : THING_PER_LEVEL_THING_ID_BITS;
    unsigned int level_num    : THING_LEVEL_ID_BITS;
  } __attribute__((__packed__)) b;
  struct {
    unsigned int entropy   : THING_ENTROPY_BITS;
    unsigned int arr_index : THING_ARR_INDEX_BITS;
  } __attribute__((__packed__)) c;
} __attribute__((__packed__)) ThingIdPacked;

//
// Essentially equates to the max number of monsters+light sources per level
//
#define THING_EXT_MAX       (LEVEL_MAX * 500)        // The size of thing_ext
#define THING_FOV_MAX       (LEVEL_MAX * 500)        // The size of thing_ext
#define THING_DESCRIBE_MAX  10                       // The number of things we can show in the rightbar
#define THING_MOVE_PATH_MAX (MAP_WIDTH + MAP_HEIGHT) // Player/monster move paths (max size uint8_t)
#define THING_INVENTORY_MAX 26
#define THING_MINION_MAX    10

enum {
  TEXT_INCLUDE_OWNER = 1,
  TEXT_EXCLUDE_DEATH = 2,
  TEXT_APOSTROPHIZE  = 4,
  TEXT_PLURALIZE     = 8,
};

typedef uint8_t ThingTextFlags;

//
// Player state
//
#define PLAYER_STATE_ENUM(list_macro)                                                                                \
  clang_format_indent()                                          /* dummy line for clang indentation fixup */        \
      list_macro(PLAYER_STATE_INIT, "INIT"),                     /* newline */                                       \
      list_macro(PLAYER_STATE_DEAD, "DEAD"),                     /* newline */                                       \
      list_macro(PLAYER_STATE_NORMAL, "NORMAL"),                 /* newline */                                       \
      list_macro(PLAYER_STATE_PATH_REQUESTED, "PATH-REQUESTED"), /* newline */                                       \
      list_macro(PLAYER_STATE_MOVE_CONFIRM_REQUESTED, "MOVE-CONFIRM-REQ"), /* newline */                             \
      list_macro(PLAYER_STATE_FOLLOWING_PATH, "FOLLOWING-PATH"),           /* newline */

ENUM_DEF_H(PLAYER_STATE_ENUM, PlayerState)

//
// Monst state
//
#define MONST_STATE_ENUM(list_macro)                                                                                 \
  clang_format_indent()                           /* dummy line for clang indentation fixup */                       \
      list_macro(MONST_STATE_INIT, "INIT"),       /* newline */                                                      \
      list_macro(MONST_STATE_DEAD, "DEAD"),       /* newline */                                                      \
      list_macro(MONST_STATE_NORMAL, "NORMAL"),   /* newline */                                                      \
      list_macro(MONST_STATE_CHASING, "CHASING"), /* newline */                                                      \
      list_macro(MONST_STATE_WANDER, "WANDER"),   /* newline */

ENUM_DEF_H(MONST_STATE_ENUM, MonstState)

//
// Field of view for a monster or player
//
typedef struct FovMap_ {
  uint8_t can_see[ MAP_WIDTH ][ MAP_HEIGHT ];
} FovMap;

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
// Minions
//
typedef struct ThingMinion_ {
  ThingId minion_id;
} ThingMinion;

//
// Per mob minions
//
typedef struct ThingMinions_ {
  ThingMinion minion[ THING_MINION_MAX ];
  int8_t      count;
} ThingMinions;

//
// Per thing extended memory
//
typedef struct ThingExt_ {
  uint8_t in_use : 1;
  //
  // All minions for this mob
  //
  ThingMinions minions;
  //
  // Can be per monster or shared per mob memory of the preferred target,
  // usually the player.
  //
  Dmap dmap;
  //
  // What we have ever seen
  //
  FovMap fov_has_seen_tile;
  //
  // Holds the path as we or the monster walk it
  //
  struct {
    spoint points[ THING_MOVE_PATH_MAX ];
    int8_t size;
  } move_path;
} ThingExt;

//
// Per thing lighting memory
//
typedef struct ThingFov_ {
  uint8_t in_use : 1;
  //
  // What we can currently see (monst) or is lit (light source)
  //
  FovMap fov_can_see_tile;
} ThingFov;

//
// Inventory items
//
typedef struct ThingSlot_ {
  ThingId item_id;
  //
  // How many of this identical item are there?
  //
  int8_t count;
} ThingSlot;

//
// Per thing inventory memory
//
typedef struct ThingInventory_ {
  //
  // This is the max any player or monster can carry
  //
  ThingSlot slots[ THING_INVENTORY_MAX ];
} ThingInventory;

//
// Player specific memory
//
typedef struct ThingPlayer_ {
  //
  // For hiscores
  //
  int16_t levels_completed;
  //
  // What we're carrying
  //
  ThingInventory inventory;
} ThingPlayer;

typedef struct Thing_ {
  //////////////////////////////////////////////////////////////
  // No c++ types can be used here, to allow easy level replay
  //
  // Why C types only ? For large data structures it is visibly
  // faster to malloc and memset versus default construction.
  //////////////////////////////////////////////////////////////

  //////////////////////////////////////////////////////////////
  // Template ID. MUST BE FIRST AS WE memset the Thing after this.
  uint16_t tp_id;
  // Template ID. MUST BE FIRST AS WE memset the Thing after this.
  //////////////////////////////////////////////////////////////

  //
  // Direction
  //
  uint8_t dir;
  //
  // The current tiles[] index for this object
  //
  uint8_t anim_index;
  //
  // Unused for player.
  //
  MonstState _monst_state;
  //
  // For event processing. Lower is better. Player is 0
  //
  ThingPriorityType _priority;
  //
  // Vision in tiles.
  //
  int8_t _distance_vision;
  //
  // Distance from mob
  //
  int8_t _distance_minion_from_mob_max;
  //
  // Jump distance in tiles.
  //
  int8_t _distance_jump;
  //
  // Decrements each frame. Increments if hit.
  //
  uint8_t _is_hit;
  //
  // Decrements each frame. Resets if still too hot when we reach zero.
  //
  uint8_t _is_hot;
  //
  // Used so often, we cache it
  //
  uint8_t _is_player : 1;
  //
  // Snuffed it.
  //
  uint8_t _is_dead : 1;
  //
  // Was set fire to.
  //
  uint8_t _is_burning : 1;
  //
  // Snuffed it and is a corpse.
  //
  uint8_t _is_corpse : 1;
  //
  // If a thing has died and leaves no corpse, schedule it to be removed from the game.
  //
  uint8_t _is_scheduled_for_cleanup : 1;
  //
  // If you've fallen through a chasm twice, more damage.
  //
  uint8_t _is_falling_continues : 1;
  //
  // Zzz
  //
  uint8_t _is_sleeping : 1;
  //
  // For doors, so we do not need keys forever
  //
  uint8_t _is_unlocked : 1;
  //
  // For doors, chests etc...
  //
  uint8_t _is_open : 1;
  //
  // Is being carried
  //
  uint8_t _is_carried : 1;
  //
  // Pushed onto the map?
  //
  uint8_t _is_on_map : 1;
  //
  // Currently moving between tiles. The thing is already at the destination.
  //
  uint8_t _is_moving : 1;
  //
  // Temporary flag set when a thing is newly spawned.
  //
  uint8_t _is_spawned : 1;
  //
  // Currently teleporting between tiles. The thing is already at the destination.
  //
  uint8_t _is_teleporting : 1;
  //
  // Currently jumping between tiles. The thing is already at the destination.
  //
  uint8_t _is_jumping : 1;
  //
  // Idle etc...
  //
  ThingAnim anim_type;
  //
  // Which level am I on?
  //
  LevelNum level_num;
  //
  // Current tile.
  //
  uint16_t tile_index;
  //
  // Count down until the next animation frame should start
  //
  int16_t anim_ms_remaining;
  //
  // Move speed, with 100 being player.
  //
  int16_t _speed;
  //
  // This is the amount move moving (the speed above) we can do per tick.
  //
  // If we are 200 and the player is 100, then we get 2 moves per tick.
  //
  // If we are 50 then we get to move every other tick.
  //
  // Each tick, this amount is incremented by the speed value until it
  // is >= the player's speed. At which point the monst can move.
  //
  int16_t _move_remaining;
  //
  // Temperature in celsius.
  //
  int16_t _temperature;
  //
  // Damage can be capped per tick to a limit so we don't kill a player in one go
  //
  int16_t _damage_this_tick;
  //
  // How many keys are carried
  //
  int16_t _keys_carried;
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
  //
  // How many minions this mob can spawn
  //
  uint8_t _minion_max;
  //
  // The type of wall
  //
  uint8_t _variant;
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
  uint16_t _is_falling_ms;
  //
  // Weight in grams. Impacts things like grass being crushed.
  //
  int32_t _weight;
  //
  // Current game tick this thing has completed
  //
  uint32_t tick;
  //
  // Used to keep track if we have ran the temperature checks yet this tick.
  //
  uint32_t tick_temperature;
  uint32_t tick_temperature_last_change;
  //
  // Used to only tick things once per loop, even if they move slot
  //
  uint32_t iter[ MY_ITERS_MAX ];
  //
  // When this poor thing died.
  //
  uint32_t tick_dead;
  //
  // Avoid fast teleport loops
  //
  uint32_t tick_teleport;
  //
  // Unique ID with some entropy built in
  //
  ThingId id;
  //
  // If owned, by whom
  //
  ThingId owner_id;
  //
  // If a mob spawned me, whom
  //
  ThingId mob_id;
  //
  // For player and monsters
  //
  ThingExtId ext_id;
  //
  // For light sources and player and monsters
  //
  ThingFovId fov_id;
  //
  // Interpolated co-ords in pixels
  //
  spoint _prev_pix_at;
  spoint _curr_pix_at;
  //
  // Previous map co-ords used for interpolation when moving. Changes when
  // the move finishes.
  //
  spoint _moving_from;
  //
  // Last location we were pushed onto the map.
  //
  spoint last_pushed_at;
  //
  // Increases per tick and when it reaches 1, allows the thing to move
  //
  float thing_dt;
  //
  // Angle of movement.
  //
  float angle;
  //
  // Previous map co-ords. Does not change when the move finishes.
  //
  fpoint _old_at;
  //
  // Map co-ords. This is the slot the thing is at when rounded.
  //
  // However some things like missiles can be at fractional positions.
  //
  fpoint _at;
  //
  // What we're chasing currently. Might be the player or some random tile.
  //
  spoint _target;
} Thing;

// begin sort marker1 {
[[nodiscard]] bool   player_check_if_target_needs_move_confirm(Gamep g, Levelsp v, Levelp l, spoint to);
[[nodiscard]] bool   player_jump(Gamep g, Levelsp v, Levelp l, Thingp me, spoint to);
[[nodiscard]] bool   player_mouse_down(Gamep, Levelsp, Levelp, int x, int y, uint32_t button);
[[nodiscard]] bool   player_move_request(Gamep g, bool up, bool down, bool left, bool right, bool fire);
[[nodiscard]] bool   player_move_to_next(Gamep g, Levelsp v, Levelp l, Thingp me);
[[nodiscard]] bool   thing_can_move_to_ai(Gamep, Levelsp, Levelp, Thingp me, spoint to);
[[nodiscard]] bool   thing_can_move_to_attempt_by_opening(Gamep, Levelsp, Levelp, Thingp me, spoint to);
[[nodiscard]] bool   thing_can_move_to_attempt_by_shoving(Gamep, Levelsp, Levelp, Thingp me, spoint to);
[[nodiscard]] bool   thing_can_move_to_attempt(Gamep, Levelsp, Levelp, Thingp me, spoint to);
[[nodiscard]] bool   thing_can_move_to_check_if_is_possible(Gamep, Levelsp, Levelp, Thingp me, spoint to);
[[nodiscard]] bool   thing_carry_item(Gamep g, Levelsp v, Levelp l, Thingp item, Thingp player_or_monst);
[[nodiscard]] bool   thing_close(Gamep, Levelsp, Levelp, Thingp me, Thingp player_or_monst);
[[nodiscard]] bool   thing_collect_key(Gamep g, Levelsp v, Levelp l, Thingp it, Thingp player_or_monst);
[[nodiscard]] bool   thing_crush(Gamep, Levelsp, Levelp, Thingp it, Thingp player_or_monst);
[[nodiscard]] bool   thing_debug(Gamep g, Levelsp v, Levelp l, Thingp t, uint32_t iter_index);
[[nodiscard]] bool   thing_drop_item(Gamep g, Levelsp v, Levelp l, Thingp item, Thingp player_or_monst);
[[nodiscard]] bool   thing_inventory_add(Gamep, Levelsp, Levelp, Thingp player_or_monst, Thingp it);
[[nodiscard]] bool   thing_inventory_is_empty(Gamep, Levelsp, Levelp, Thingp t);
[[nodiscard]] bool   thing_inventory_item_mergeable(Gamep, Levelsp, Levelp, Thingp a, Thingp b);
[[nodiscard]] bool   thing_inventory_remove(Gamep, Levelsp, Levelp, Thingp player_or_monst, Thingp it);
[[nodiscard]] bool   thing_is_able_to_collect_items(Thingp t);
[[nodiscard]] bool   thing_is_able_to_collect_keys(Thingp t);
[[nodiscard]] bool   thing_is_able_to_crush_grass(Thingp t);
[[nodiscard]] bool   thing_is_able_to_fall_repeatedly(Thingp t);
[[nodiscard]] bool   thing_is_able_to_fall(Thingp t);
[[nodiscard]] bool   thing_is_able_to_jump(Thingp t);
[[nodiscard]] bool   thing_is_able_to_move_diagonally(Thingp t);
[[nodiscard]] bool   thing_is_able_to_move_through_walls(Thingp t);
[[nodiscard]] bool   thing_is_able_to_open(Thingp t);
[[nodiscard]] bool   thing_is_able_to_shove(Thingp t);
[[nodiscard]] bool   thing_is_able_to_walk_through_walls(Thingp t);
[[nodiscard]] bool   thing_is_animated_can_hflip(Thingp t);
[[nodiscard]] bool   thing_is_animated_no_dir(Thingp t);
[[nodiscard]] bool   thing_is_animated_sync_first(Thingp t);
[[nodiscard]] bool   thing_is_animated(Thingp t);
[[nodiscard]] bool   thing_is_barrel(Thingp t);
[[nodiscard]] bool   thing_is_blit_centered(Thingp t);
[[nodiscard]] bool   thing_is_blit_flush_per_line(Thingp t);
[[nodiscard]] bool   thing_is_blit_if_has_seen(Thingp t);
[[nodiscard]] bool   thing_is_blit_obscures(Thingp t);
[[nodiscard]] bool   thing_is_blit_on_ground(Thingp t);
[[nodiscard]] bool   thing_is_blit_outlined(Thingp t);
[[nodiscard]] bool   thing_is_blit_per_pixel_lighting(Thingp t);
[[nodiscard]] bool   thing_is_blit_shown_in_chasms(Thingp t);
[[nodiscard]] bool   thing_is_blit_shown_in_overlay(Thingp t);
[[nodiscard]] bool   thing_is_blit_square_outlined(Thingp t);
[[nodiscard]] bool   thing_is_blit_when_obscured(Thingp t);
[[nodiscard]] bool   thing_is_border(Thingp t);
[[nodiscard]] bool   thing_is_brazier(Thingp t);
[[nodiscard]] bool   thing_is_bridge(Thingp t);
[[nodiscard]] bool   thing_is_broken_on_death(Thingp t);
[[nodiscard]] bool   thing_is_burnable(Thingp t);
[[nodiscard]] bool   thing_is_burning(Thingp t);
[[nodiscard]] bool   thing_is_carried_try_set(Gamep, Levelsp, Levelp, Thingp item, Thingp carrier, bool val = true);
[[nodiscard]] bool   thing_is_carried_try_unset(Gamep, Levelsp, Levelp, Thingp item, Thingp dropr);
[[nodiscard]] bool   thing_is_carried(Thingp t);
[[nodiscard]] bool   thing_is_chasm(Thingp t);
[[nodiscard]] bool   thing_is_collectable(Thingp t);
[[nodiscard]] bool   thing_is_collision_circle_large(Thingp t);
[[nodiscard]] bool   thing_is_collision_circle_small(Thingp t);
[[nodiscard]] bool   thing_is_collision_detection_enabled(Thingp t);
[[nodiscard]] bool   thing_is_collision_square(Thingp t);
[[nodiscard]] bool   thing_is_combustible(Thingp t);
[[nodiscard]] bool   thing_is_corpse_on_death(Thingp t);
[[nodiscard]] bool   thing_is_corpse(Thingp t);
[[nodiscard]] bool   thing_is_corridor(Thingp t);
[[nodiscard]] bool   thing_is_crushable(Thingp t);
[[nodiscard]] bool   thing_is_cursor_path_hazard(Thingp t);
[[nodiscard]] bool   thing_is_cursor_path_none(Thingp t);
[[nodiscard]] bool   thing_is_cursor_path_warning(Thingp t);
[[nodiscard]] bool   thing_is_cursor_path(Thingp t);
[[nodiscard]] bool   thing_is_cursor(Thingp t);
[[nodiscard]] bool   thing_is_damage_capped(Thingp t);
[[nodiscard]] bool   thing_is_dead_on_collision(Thingp t);
[[nodiscard]] bool   thing_is_dead_on_shoving(Thingp t);
[[nodiscard]] bool   thing_is_deep_water(Thingp t);
[[nodiscard]] bool   thing_is_described_cursor(Thingp t);
[[nodiscard]] bool   thing_is_dir_bl(Thingp me);
[[nodiscard]] bool   thing_is_dir_br(Thingp me);
[[nodiscard]] bool   thing_is_dir_down(Thingp me);
[[nodiscard]] bool   thing_is_dir_left(Thingp me);
[[nodiscard]] bool   thing_is_dir_right(Thingp me);
[[nodiscard]] bool   thing_is_dir_tl(Thingp me);
[[nodiscard]] bool   thing_is_dir_tr(Thingp me);
[[nodiscard]] bool   thing_is_dir_up(Thingp me);
[[nodiscard]] bool   thing_is_dirt(Thingp t);
[[nodiscard]] bool   thing_is_dmap(Thingp t);
[[nodiscard]] bool   thing_is_door_locked(Thingp t);
[[nodiscard]] bool   thing_is_door_secret(Thingp t);
[[nodiscard]] bool   thing_is_door_unlocked(Thingp t);
[[nodiscard]] bool   thing_is_dungeon_entrance(Thingp t);
[[nodiscard]] bool   thing_is_entrance(Thingp t);
[[nodiscard]] bool   thing_is_ethereal(Thingp t);
[[nodiscard]] bool   thing_is_exit(Thingp t);
[[nodiscard]] bool   thing_is_explosion(Thingp t);
[[nodiscard]] bool   thing_is_extinguished_on_death(Thingp t);
[[nodiscard]] bool   thing_is_falling_continues(Thingp t);
[[nodiscard]] bool   thing_is_fire(Thingp t);
[[nodiscard]] bool   thing_is_fireball(Thingp t);
[[nodiscard]] bool   thing_is_flesh(Thingp t);
[[nodiscard]] bool   thing_is_floating(Thingp t);
[[nodiscard]] bool   thing_is_floor(Thingp t);
[[nodiscard]] bool   thing_is_flying(Thingp t);
[[nodiscard]] bool   thing_is_foliage(Thingp t);
[[nodiscard]] bool   thing_is_gaseous(Thingp t);
[[nodiscard]] bool   thing_is_ghost(Thingp t);
[[nodiscard]] bool   thing_is_glass(Thingp t);
[[nodiscard]] bool   thing_is_gold(Thingp t);
[[nodiscard]] bool   thing_is_grass(Thingp t);
[[nodiscard]] bool   thing_is_health_bar_shown(Thingp t);
[[nodiscard]] bool   thing_is_immune_to(Thingp t, ThingEventType val);
[[nodiscard]] bool   thing_is_indestructible(Thingp t);
[[nodiscard]] bool   thing_is_insectoid(Thingp t);
[[nodiscard]] bool   thing_is_inventory_item(Thingp t);
[[nodiscard]] bool   thing_is_item_droppable(Thingp t);
[[nodiscard]] bool   thing_is_item_equipable(Thingp t);
[[nodiscard]] bool   thing_is_item_mergeable(Thingp t);
[[nodiscard]] bool   thing_is_item(Thingp t);
[[nodiscard]] bool   thing_is_key(Thingp t);
[[nodiscard]] bool   thing_is_kobalos(Thingp t);
[[nodiscard]] bool   thing_is_lava(Thingp t);
[[nodiscard]] bool   thing_is_level_across_icon(Thingp t);
[[nodiscard]] bool   thing_is_level_curr(Thingp t);
[[nodiscard]] bool   thing_is_level_down_icon(Thingp t);
[[nodiscard]] bool   thing_is_level_final_icon(Thingp t);
[[nodiscard]] bool   thing_is_level_next_icon(Thingp t);
[[nodiscard]] bool   thing_is_level_not_visited_icon(Thingp t);
[[nodiscard]] bool   thing_is_level_visited_icon(Thingp t);
[[nodiscard]] bool   thing_is_levitating(Thingp t);
[[nodiscard]] bool   thing_is_loggable(Thingp t);
[[nodiscard]] bool   thing_is_mantisman(Thingp t);
[[nodiscard]] bool   thing_is_meltable(Thingp t);
[[nodiscard]] bool   thing_is_metal(Thingp t);
[[nodiscard]] bool   thing_is_minion(Thingp t);
[[nodiscard]] bool   thing_is_mob_kill_minions_on_death(Thingp t);
[[nodiscard]] bool   thing_is_mob(Thingp t);
[[nodiscard]] bool   thing_is_mob1(Thingp t);
[[nodiscard]] bool   thing_is_mob2(Thingp t);
[[nodiscard]] bool   thing_is_monst_group_easy(Thingp t);
[[nodiscard]] bool   thing_is_monst_group_hard(Thingp t);
[[nodiscard]] bool   thing_is_monst_group_mob(Thingp t);
[[nodiscard]] bool   thing_is_monst(Thingp t);
[[nodiscard]] bool   thing_is_needs_move_confirm(Thingp t);
[[nodiscard]] bool   thing_is_obs_to_cursor_path(Thingp t);
[[nodiscard]] bool   thing_is_obs_to_explosion(Thingp t);
[[nodiscard]] bool   thing_is_obs_to_falling_onto(Thingp t);
[[nodiscard]] bool   thing_is_obs_to_fire(Thingp t);
[[nodiscard]] bool   thing_is_obs_to_jump_over(Thingp t);
[[nodiscard]] bool   thing_is_obs_to_jumping_onto(Thingp t);
[[nodiscard]] bool   thing_is_obs_to_jumping_out_of(Thingp t);
[[nodiscard]] bool   thing_is_obs_to_movement(Thingp t);
[[nodiscard]] bool   thing_is_obs_to_spawning(Thingp t);
[[nodiscard]] bool   thing_is_obs_to_teleporting_onto(Thingp t);
[[nodiscard]] bool   thing_is_obs_when_dead(Thingp t);
[[nodiscard]] bool   thing_is_on_map(Thingp t);
[[nodiscard]] bool   thing_is_open_try_set(Gamep, Levelsp, Levelp, Thingp t, Thingp opener, bool val = true);
[[nodiscard]] bool   thing_is_open_try_unset(Gamep, Levelsp, Levelp, Thingp t, Thingp closer);
[[nodiscard]] bool   thing_is_openable(Thingp t);
[[nodiscard]] bool   thing_is_physics_explosion(Thingp t);
[[nodiscard]] bool   thing_is_physics_water(Thingp t);
[[nodiscard]] bool   thing_is_pillar(Thingp t);
[[nodiscard]] bool   thing_is_plant(Thingp t);
[[nodiscard]] bool   thing_is_projectile(Thingp t);
[[nodiscard]] bool   thing_is_removable_on_err(Thingp t);
[[nodiscard]] bool   thing_is_removable_when_dead_on_err(Thingp t);
[[nodiscard]] bool   thing_is_rock(Thingp t);
[[nodiscard]] bool   thing_is_scheduled_for_cleanup(Thingp t);
[[nodiscard]] bool   thing_is_shovable(Thingp t);
[[nodiscard]] bool   thing_is_sleeping(Thingp t);
[[nodiscard]] bool   thing_is_slime(Thingp t);
[[nodiscard]] bool   thing_is_smoke(Thingp t);
[[nodiscard]] bool   thing_is_steam(Thingp t);
[[nodiscard]] bool   thing_is_stone(Thingp t);
[[nodiscard]] bool   thing_is_submergible(Thingp t);
[[nodiscard]] bool   thing_is_teleport_blocked(Thingp t);
[[nodiscard]] bool   thing_is_teleport(Thingp t);
[[nodiscard]] bool   thing_is_teleporting(Thingp t);
[[nodiscard]] bool   thing_is_tick_end_delay(Thingp t);
[[nodiscard]] bool   thing_is_tickable(Thingp t);
[[nodiscard]] bool   thing_is_tiled(Thingp t);
[[nodiscard]] bool   thing_is_trap(Thingp t);
[[nodiscard]] bool   thing_is_treasure(Thingp t);
[[nodiscard]] bool   thing_is_undead(Thingp t);
[[nodiscard]] bool   thing_is_unlocked(Thingp t);
[[nodiscard]] bool   thing_is_unused1(Thingp t);
[[nodiscard]] bool   thing_is_unused10(Thingp t);
[[nodiscard]] bool   thing_is_unused11(Thingp t);
[[nodiscard]] bool   thing_is_unused12(Thingp t);
[[nodiscard]] bool   thing_is_unused13(Thingp t);
[[nodiscard]] bool   thing_is_unused14(Thingp t);
[[nodiscard]] bool   thing_is_unused15(Thingp t);
[[nodiscard]] bool   thing_is_unused16(Thingp t);
[[nodiscard]] bool   thing_is_unused17(Thingp t);
[[nodiscard]] bool   thing_is_unused18(Thingp t);
[[nodiscard]] bool   thing_is_unused19(Thingp t);
[[nodiscard]] bool   thing_is_unused2(Thingp t);
[[nodiscard]] bool   thing_is_unused20(Thingp t);
[[nodiscard]] bool   thing_is_unused21(Thingp t);
[[nodiscard]] bool   thing_is_unused22(Thingp t);
[[nodiscard]] bool   thing_is_unused23(Thingp t);
[[nodiscard]] bool   thing_is_unused24(Thingp t);
[[nodiscard]] bool   thing_is_unused25(Thingp t);
[[nodiscard]] bool   thing_is_unused26(Thingp t);
[[nodiscard]] bool   thing_is_unused27(Thingp t);
[[nodiscard]] bool   thing_is_unused28(Thingp t);
[[nodiscard]] bool   thing_is_unused29(Thingp t);
[[nodiscard]] bool   thing_is_unused3(Thingp t);
[[nodiscard]] bool   thing_is_unused30(Thingp t);
[[nodiscard]] bool   thing_is_unused31(Thingp t);
[[nodiscard]] bool   thing_is_unused32(Thingp t);
[[nodiscard]] bool   thing_is_unused33(Thingp t);
[[nodiscard]] bool   thing_is_unused34(Thingp t);
[[nodiscard]] bool   thing_is_unused35(Thingp t);
[[nodiscard]] bool   thing_is_unused36(Thingp t);
[[nodiscard]] bool   thing_is_unused37(Thingp t);
[[nodiscard]] bool   thing_is_unused38(Thingp t);
[[nodiscard]] bool   thing_is_unused39(Thingp t);
[[nodiscard]] bool   thing_is_unused4(Thingp t);
[[nodiscard]] bool   thing_is_unused40(Thingp t);
[[nodiscard]] bool   thing_is_unused41(Thingp t);
[[nodiscard]] bool   thing_is_unused42(Thingp t);
[[nodiscard]] bool   thing_is_unused43(Thingp t);
[[nodiscard]] bool   thing_is_unused44(Thingp t);
[[nodiscard]] bool   thing_is_unused45(Thingp t);
[[nodiscard]] bool   thing_is_unused46(Thingp t);
[[nodiscard]] bool   thing_is_unused47(Thingp t);
[[nodiscard]] bool   thing_is_unused48(Thingp t);
[[nodiscard]] bool   thing_is_unused49(Thingp t);
[[nodiscard]] bool   thing_is_unused5(Thingp t);
[[nodiscard]] bool   thing_is_unused50(Thingp t);
[[nodiscard]] bool   thing_is_unused51(Thingp t);
[[nodiscard]] bool   thing_is_unused52(Thingp t);
[[nodiscard]] bool   thing_is_unused53(Thingp t);
[[nodiscard]] bool   thing_is_unused54(Thingp t);
[[nodiscard]] bool   thing_is_unused55(Thingp t);
[[nodiscard]] bool   thing_is_unused56(Thingp t);
[[nodiscard]] bool   thing_is_unused57(Thingp t);
[[nodiscard]] bool   thing_is_unused58(Thingp t);
[[nodiscard]] bool   thing_is_unused59(Thingp t);
[[nodiscard]] bool   thing_is_unused6(Thingp t);
[[nodiscard]] bool   thing_is_unused60(Thingp t);
[[nodiscard]] bool   thing_is_unused61(Thingp t);
[[nodiscard]] bool   thing_is_unused62(Thingp t);
[[nodiscard]] bool   thing_is_unused63(Thingp t);
[[nodiscard]] bool   thing_is_unused64(Thingp t);
[[nodiscard]] bool   thing_is_unused65(Thingp t);
[[nodiscard]] bool   thing_is_unused66(Thingp t);
[[nodiscard]] bool   thing_is_unused67(Thingp t);
[[nodiscard]] bool   thing_is_unused68(Thingp t);
[[nodiscard]] bool   thing_is_unused7(Thingp t);
[[nodiscard]] bool   thing_is_unused8(Thingp t);
[[nodiscard]] bool   thing_is_unused9(Thingp t);
[[nodiscard]] bool   thing_is_wait_on_dead_anim(Thingp t);
[[nodiscard]] bool   thing_is_wall(Thingp t);
[[nodiscard]] bool   thing_is_water(Thingp t);
[[nodiscard]] bool   thing_is_wood(Thingp t);
[[nodiscard]] bool   thing_jump_to(Gamep g, Levelsp v, Levelp l, Thingp t, spoint to, bool warn = true);
[[nodiscard]] bool   thing_minion_choose_target_near_mob(Gamep g, Levelsp v, Levelp l, Thingp minion);
[[nodiscard]] bool   thing_minion_detach_me_from_mob(Gamep g, Levelsp v, Levelp l, Thingp minion);
[[nodiscard]] bool   thing_mob_detach_all_minions(Gamep g, Levelsp v, Levelp l, Thingp mob);
[[nodiscard]] bool   thing_mob_detach_minion(Gamep g, Levelsp v, Levelp l, Thingp mob, Thingp minion);
[[nodiscard]] bool   thing_mob_kill_all_minions(Gamep g, Levelsp v, Levelp l, Thingp mob, ThingEvent &e);
[[nodiscard]] bool   thing_monst_choose_target_player(Gamep g, Levelsp v, Levelp l, Thingp minion);
[[nodiscard]] bool   thing_move_path_apply(Gamep, Levelsp, Levelp, Thingp t, std::vector< spoint > &move_path);
[[nodiscard]] bool   thing_move_path_pop(Gamep, Levelsp, Levelp, Thingp t, spoint &out);
[[nodiscard]] bool   thing_move_path_target(Gamep, Levelsp, Levelp, Thingp t, spoint &out);
[[nodiscard]] bool   thing_move_to_next(Gamep, Levelsp, Levelp, Thingp);
[[nodiscard]] bool   thing_move_to(Gamep, Levelsp, Levelp, Thingp me, spoint to);
[[nodiscard]] bool   thing_on_same_level_as_player(Gamep g, Levelsp v, Thingp t);
[[nodiscard]] bool   thing_open(Gamep, Levelsp, Levelp, Thingp me, Thingp opener);
[[nodiscard]] bool   thing_player_mouse_down(Gamep g, Levelsp v, Levelp l, int x, int y, uint32_t button);
[[nodiscard]] bool   thing_pop(Gamep g, Levelsp v, Thingp t);
[[nodiscard]] bool   thing_projectile_fire_at(Gamep, Levelsp, Levelp, Thingp me, Tpp what, fpoint target);
[[nodiscard]] bool   thing_projectile_fire_at(Gamep, Levelsp, Levelp, Thingp me, Tpp what, spoint target);
[[nodiscard]] bool   thing_push(Gamep g, Levelsp v, Levelp l, Thingp t);
[[nodiscard]] bool   thing_shove_handle(Gamep, Levelsp, Levelp, Thingp shover, spoint at);
[[nodiscard]] bool   thing_shove_to(Gamep, Levelsp, Levelp, Thingp me, spoint to);
[[nodiscard]] bool   thing_teleport_handle(Gamep g, Levelsp v, Levelp l, Thingp t);
[[nodiscard]] bool   thing_vision_can_see_tile(Gamep g, Levelsp v, Levelp l, Thingp t, spoint p);
[[nodiscard]] bool   thing_vision_player_has_seen_tile(Gamep g, Levelsp v, Levelp l, spoint p);
[[nodiscard]] bool   thing_warp_to(Gamep, Levelsp, Levelp new_level, Thingp me, spoint to);
[[nodiscard]] Dmap  *thing_get_dmap(Gamep g, Levelsp v, Levelp l, Thingp me);
[[nodiscard]] Dmap  *thing_minion_get_mob_dmap(Gamep g, Levelsp v, Levelp l, Thingp me);
[[nodiscard]] float  thing_collision_radius(Thingp t);
[[nodiscard]] fpoint thing_get_direction(Gamep, Levelsp, Levelp, Thingp me);
[[nodiscard]] fpoint thing_projectile_get_direction(Gamep, Levelsp, Levelp, Thingp t);
[[nodiscard]] fpoint thing_real_at(Thingp t);
[[nodiscard]] int    thing_age_decr(Gamep, Levelsp, Levelp, Thingp t, int val = 1);
[[nodiscard]] int    thing_age_incr(Gamep, Levelsp, Levelp, Thingp t, int val = 1);
[[nodiscard]] int    thing_age_set(Gamep, Levelsp, Levelp, Thingp t, int val);
[[nodiscard]] int    thing_age(Thingp t);
[[nodiscard]] int    thing_damage_this_tick_decr(Gamep, Levelsp, Levelp, Thingp t, int val = 1);
[[nodiscard]] int    thing_damage_this_tick_incr(Gamep, Levelsp, Levelp, Thingp t, int val = 1);
[[nodiscard]] int    thing_damage_this_tick_set(Gamep, Levelsp, Levelp, Thingp t, int val);
[[nodiscard]] int    thing_damage_this_tick(Thingp t);
[[nodiscard]] int    thing_distance_jump_decr(Gamep, Levelsp, Levelp, Thingp t, int val = 1);
[[nodiscard]] int    thing_distance_jump_incr(Gamep, Levelsp, Levelp, Thingp t, int val = 1);
[[nodiscard]] int    thing_distance_jump_set(Gamep, Levelsp, Levelp, Thingp t, int val);
[[nodiscard]] int    thing_distance_jump(Thingp t);
[[nodiscard]] int    thing_distance_minion_from_mob_max_decr(Gamep, Levelsp, Levelp, Thingp t, int val = 1);
[[nodiscard]] int    thing_distance_minion_from_mob_max_incr(Gamep, Levelsp, Levelp, Thingp t, int val = 1);
[[nodiscard]] int    thing_distance_minion_from_mob_max_set(Gamep, Levelsp, Levelp, Thingp t, int val);
[[nodiscard]] int    thing_distance_minion_from_mob_max(Thingp t);
[[nodiscard]] int    thing_distance_vision_decr(Gamep, Levelsp, Levelp, Thingp t, int val = 1);
[[nodiscard]] int    thing_distance_vision_incr(Gamep, Levelsp, Levelp, Thingp t, int val = 1);
[[nodiscard]] int    thing_distance_vision_set(Gamep, Levelsp, Levelp, Thingp t, int val);
[[nodiscard]] int    thing_distance_vision(Thingp t);
[[nodiscard]] int    thing_health_decr(Gamep, Levelsp, Levelp, Thingp t, int val = 1);
[[nodiscard]] int    thing_health_incr(Gamep, Levelsp, Levelp, Thingp t, int val = 1);
[[nodiscard]] int    thing_health_set(Gamep, Levelsp, Levelp, Thingp t, int val);
[[nodiscard]] int    thing_health(Thingp t);
[[nodiscard]] int    thing_is_falling_incr(Gamep, Levelsp, Levelp, Thingp t, int val = 1);
[[nodiscard]] int    thing_is_hit_decr(Gamep, Levelsp, Levelp, Thingp t, int val = 1);
[[nodiscard]] int    thing_is_hit_incr(Gamep, Levelsp, Levelp, Thingp t, int val = 1);
[[nodiscard]] int    thing_is_hot_decr(Gamep, Levelsp, Levelp, Thingp t, int val = 1);
[[nodiscard]] int    thing_is_hot_incr(Gamep, Levelsp, Levelp, Thingp t, int val = 1);
[[nodiscard]] int    thing_keys_carried_decr(Gamep, Levelsp, Levelp, Thingp t, int val = 1);
[[nodiscard]] int    thing_keys_carried_incr(Gamep, Levelsp, Levelp, Thingp t, int val = 1);
[[nodiscard]] int    thing_keys_carried_set(Gamep, Levelsp, Levelp, Thingp t, int val);
[[nodiscard]] int    thing_keys_carried(Thingp t);
[[nodiscard]] int    thing_lifespan_decr(Gamep, Levelsp, Levelp, Thingp t, int val = 1);
[[nodiscard]] int    thing_lifespan_incr(Gamep, Levelsp, Levelp, Thingp t, int val = 1);
[[nodiscard]] int    thing_lifespan_set(Gamep, Levelsp, Levelp, Thingp t, int val);
[[nodiscard]] int    thing_lifespan(Thingp t);
[[nodiscard]] int    thing_minion_max_decr(Gamep, Levelsp, Levelp, Thingp t, int val = 1);
[[nodiscard]] int    thing_minion_max_incr(Gamep, Levelsp, Levelp, Thingp t, int val = 1);
[[nodiscard]] int    thing_minion_max_set(Gamep, Levelsp, Levelp, Thingp t, int val);
[[nodiscard]] int    thing_minion_max(Thingp t);
[[nodiscard]] int    thing_mob_minion_count_get(Gamep g, Levelsp v, Levelp l, Thingp mob);
[[nodiscard]] int    thing_move_path_size(Gamep, Levelsp, Levelp, Thingp t);
[[nodiscard]] int    thing_move_remaining_decr(Gamep, Levelsp, Levelp, Thingp t, int val = 1);
[[nodiscard]] int    thing_move_remaining_incr(Gamep, Levelsp, Levelp, Thingp t, int val = 1);
[[nodiscard]] int    thing_move_remaining_set(Gamep, Levelsp, Levelp, Thingp t, int val);
[[nodiscard]] int    thing_move_remaining(Thingp t);
[[nodiscard]] int    thing_speed_set(Gamep, Levelsp, Levelp, Thingp t, int val);
[[nodiscard]] int    thing_speed(Thingp t);
[[nodiscard]] int    thing_submerged_pct_decr(Gamep, Levelsp, Levelp, Thingp t, int val = 1);
[[nodiscard]] int    thing_submerged_pct_incr(Gamep, Levelsp, Levelp, Thingp t, int val = 1);
[[nodiscard]] int    thing_submerged_pct_set(Gamep, Levelsp, Levelp, Thingp t, int val);
[[nodiscard]] int    thing_submerged_pct(Thingp t);
[[nodiscard]] int    thing_temperature_decr(Gamep, Levelsp, Levelp, Thingp t, int val = 1);
[[nodiscard]] int    thing_temperature_incr(Gamep, Levelsp, Levelp, Thingp t, int val = 1);
[[nodiscard]] int    thing_temperature_set(Gamep, Levelsp, Levelp, Thingp t, int val);
[[nodiscard]] int    thing_temperature(Thingp t);
[[nodiscard]] int    thing_value1_decr(Gamep, Levelsp, Levelp, Thingp t, int val = 1);
[[nodiscard]] int    thing_value1_incr(Gamep, Levelsp, Levelp, Thingp t, int val = 1);
[[nodiscard]] int    thing_value1_set(Gamep, Levelsp, Levelp, Thingp t, int val);
[[nodiscard]] int    thing_value1(Thingp t);
[[nodiscard]] int    thing_value10_decr(Gamep, Levelsp, Levelp, Thingp t, int val = 1);
[[nodiscard]] int    thing_value10_incr(Gamep, Levelsp, Levelp, Thingp t, int val = 1);
[[nodiscard]] int    thing_value10_set(Gamep, Levelsp, Levelp, Thingp t, int val);
[[nodiscard]] int    thing_value10(Thingp t);
[[nodiscard]] int    thing_value11_decr(Gamep, Levelsp, Levelp, Thingp t, int val = 1);
[[nodiscard]] int    thing_value11_incr(Gamep, Levelsp, Levelp, Thingp t, int val = 1);
[[nodiscard]] int    thing_value11_set(Gamep, Levelsp, Levelp, Thingp t, int val);
[[nodiscard]] int    thing_value11(Thingp t);
[[nodiscard]] int    thing_value12_decr(Gamep, Levelsp, Levelp, Thingp t, int val = 1);
[[nodiscard]] int    thing_value12_incr(Gamep, Levelsp, Levelp, Thingp t, int val = 1);
[[nodiscard]] int    thing_value12_set(Gamep, Levelsp, Levelp, Thingp t, int val);
[[nodiscard]] int    thing_value12(Thingp t);
[[nodiscard]] int    thing_value13_decr(Gamep, Levelsp, Levelp, Thingp t, int val = 1);
[[nodiscard]] int    thing_value13_incr(Gamep, Levelsp, Levelp, Thingp t, int val = 1);
[[nodiscard]] int    thing_value13_set(Gamep, Levelsp, Levelp, Thingp t, int val);
[[nodiscard]] int    thing_value13(Thingp t);
[[nodiscard]] int    thing_value14_decr(Gamep, Levelsp, Levelp, Thingp t, int val = 1);
[[nodiscard]] int    thing_value14_incr(Gamep, Levelsp, Levelp, Thingp t, int val = 1);
[[nodiscard]] int    thing_value14_set(Gamep, Levelsp, Levelp, Thingp t, int val);
[[nodiscard]] int    thing_value14(Thingp t);
[[nodiscard]] int    thing_value15_decr(Gamep, Levelsp, Levelp, Thingp t, int val = 1);
[[nodiscard]] int    thing_value15_incr(Gamep, Levelsp, Levelp, Thingp t, int val = 1);
[[nodiscard]] int    thing_value15_set(Gamep, Levelsp, Levelp, Thingp t, int val);
[[nodiscard]] int    thing_value15(Thingp t);
[[nodiscard]] int    thing_value16_decr(Gamep, Levelsp, Levelp, Thingp t, int val = 1);
[[nodiscard]] int    thing_value16_incr(Gamep, Levelsp, Levelp, Thingp t, int val = 1);
[[nodiscard]] int    thing_value16_set(Gamep, Levelsp, Levelp, Thingp t, int val);
[[nodiscard]] int    thing_value16(Thingp t);
[[nodiscard]] int    thing_value17_decr(Gamep, Levelsp, Levelp, Thingp t, int val = 1);
[[nodiscard]] int    thing_value17_incr(Gamep, Levelsp, Levelp, Thingp t, int val = 1);
[[nodiscard]] int    thing_value17_set(Gamep, Levelsp, Levelp, Thingp t, int val);
[[nodiscard]] int    thing_value17(Thingp t);
[[nodiscard]] int    thing_value18_decr(Gamep, Levelsp, Levelp, Thingp t, int val = 1);
[[nodiscard]] int    thing_value18_incr(Gamep, Levelsp, Levelp, Thingp t, int val = 1);
[[nodiscard]] int    thing_value18_set(Gamep, Levelsp, Levelp, Thingp t, int val);
[[nodiscard]] int    thing_value18(Thingp t);
[[nodiscard]] int    thing_value19_decr(Gamep, Levelsp, Levelp, Thingp t, int val = 1);
[[nodiscard]] int    thing_value19_incr(Gamep, Levelsp, Levelp, Thingp t, int val = 1);
[[nodiscard]] int    thing_value19_set(Gamep, Levelsp, Levelp, Thingp t, int val);
[[nodiscard]] int    thing_value19(Thingp t);
[[nodiscard]] int    thing_value2_decr(Gamep, Levelsp, Levelp, Thingp t, int val = 1);
[[nodiscard]] int    thing_value2_incr(Gamep, Levelsp, Levelp, Thingp t, int val = 1);
[[nodiscard]] int    thing_value2_set(Gamep, Levelsp, Levelp, Thingp t, int val);
[[nodiscard]] int    thing_value2(Thingp t);
[[nodiscard]] int    thing_value20_decr(Gamep, Levelsp, Levelp, Thingp t, int val = 1);
[[nodiscard]] int    thing_value20_incr(Gamep, Levelsp, Levelp, Thingp t, int val = 1);
[[nodiscard]] int    thing_value20_set(Gamep, Levelsp, Levelp, Thingp t, int val);
[[nodiscard]] int    thing_value20(Thingp t);
[[nodiscard]] int    thing_value3_decr(Gamep, Levelsp, Levelp, Thingp t, int val = 1);
[[nodiscard]] int    thing_value3_incr(Gamep, Levelsp, Levelp, Thingp t, int val = 1);
[[nodiscard]] int    thing_value3_set(Gamep, Levelsp, Levelp, Thingp t, int val);
[[nodiscard]] int    thing_value3(Thingp t);
[[nodiscard]] int    thing_value4_decr(Gamep, Levelsp, Levelp, Thingp t, int val = 1);
[[nodiscard]] int    thing_value4_incr(Gamep, Levelsp, Levelp, Thingp t, int val = 1);
[[nodiscard]] int    thing_value4_set(Gamep, Levelsp, Levelp, Thingp t, int val);
[[nodiscard]] int    thing_value4(Thingp t);
[[nodiscard]] int    thing_value5_decr(Gamep, Levelsp, Levelp, Thingp t, int val = 1);
[[nodiscard]] int    thing_value5_incr(Gamep, Levelsp, Levelp, Thingp t, int val = 1);
[[nodiscard]] int    thing_value5_set(Gamep, Levelsp, Levelp, Thingp t, int val);
[[nodiscard]] int    thing_value5(Thingp t);
[[nodiscard]] int    thing_value6_decr(Gamep, Levelsp, Levelp, Thingp t, int val = 1);
[[nodiscard]] int    thing_value6_incr(Gamep, Levelsp, Levelp, Thingp t, int val = 1);
[[nodiscard]] int    thing_value6_set(Gamep, Levelsp, Levelp, Thingp t, int val);
[[nodiscard]] int    thing_value6(Thingp t);
[[nodiscard]] int    thing_value7_decr(Gamep, Levelsp, Levelp, Thingp t, int val = 1);
[[nodiscard]] int    thing_value7_incr(Gamep, Levelsp, Levelp, Thingp t, int val = 1);
[[nodiscard]] int    thing_value7_set(Gamep, Levelsp, Levelp, Thingp t, int val);
[[nodiscard]] int    thing_value7(Thingp t);
[[nodiscard]] int    thing_value8_decr(Gamep, Levelsp, Levelp, Thingp t, int val = 1);
[[nodiscard]] int    thing_value8_incr(Gamep, Levelsp, Levelp, Thingp t, int val = 1);
[[nodiscard]] int    thing_value8_set(Gamep, Levelsp, Levelp, Thingp t, int val);
[[nodiscard]] int    thing_value8(Thingp t);
[[nodiscard]] int    thing_value9_decr(Gamep, Levelsp, Levelp, Thingp t, int val = 1);
[[nodiscard]] int    thing_value9_incr(Gamep, Levelsp, Levelp, Thingp t, int val = 1);
[[nodiscard]] int    thing_value9_set(Gamep, Levelsp, Levelp, Thingp t, int val);
[[nodiscard]] int    thing_value9(Thingp t);
[[nodiscard]] int    thing_variant_set(Gamep, Levelsp, Levelp, Thingp t, int val);
[[nodiscard]] int    thing_variant(Thingp t);
[[nodiscard]] int    thing_weight_set(Gamep, Levelsp, Levelp, Thingp t, int val);
[[nodiscard]] int    thing_weight(Thingp t);
[[nodiscard]] Levelp thing_level(Gamep g, Levelsp v, Thingp t);
[[nodiscard]] Levelp thing_player_level(Gamep g);
[[nodiscard]] MonstState  monst_state(Gamep g, Levelsp v, Levelp l, Thingp me);
[[nodiscard]] spoint      thing_at(Thingp t);
[[nodiscard]] spoint      thing_moving_from(Thingp t);
[[nodiscard]] spoint      thing_old_at(Thingp t);
[[nodiscard]] spoint      thing_prev_pix_at(Thingp t);
[[nodiscard]] spoint      thing_target(Thingp t);
[[nodiscard]] std::string monst_state_to_string(MonstState state);
[[nodiscard]] std::string thing_apostrophize_name(Thingp, ThingTextFlags);
[[nodiscard]] std::string thing_long_name(Gamep g, Levelsp v, Levelp l, Thingp t, ThingTextFlags flags = 0);
[[nodiscard]] std::string thing_pluralize_name(Thingp, ThingTextFlags);
[[nodiscard]] std::string thing_short_name(Gamep g, Levelsp v, Levelp l, Thingp t, ThingTextFlags flags = 0);
[[nodiscard]] std::string thing_the_long_name(Gamep g, Levelsp v, Levelp l, Thingp t, ThingTextFlags flags = 0);
[[nodiscard]] std::string thing_the_short_name(Gamep g, Levelsp v, Levelp l, Thingp t, ThingTextFlags flags = 0);
[[nodiscard]] std::string to_death_reason_string(Gamep, Levelsp, Levelp, Thingp t, ThingEvent &e);
[[nodiscard]] std::string to_string(Gamep, Levelsp, Levelp, ThingEvent &e);
[[nodiscard]] std::string to_string(Gamep, Levelsp, Levelp, Thingp t);
[[nodiscard]] ThingExtp   thing_ext_struct(Gamep g, Thingp t);
[[nodiscard]] ThingFovp   thing_fov_struct(Gamep g, Thingp t);
[[nodiscard]] Thingp      immediate_owner(Gamep g, Levelsp v, Levelp l, Thingp t);
[[nodiscard]] Thingp      thing_alloc(Gamep g, Levelsp v, Levelp l, Tpp tp, spoint p);
[[nodiscard]] Thingp      thing_and_tp_get_at_safe(Gamep g, Levelsp v, Levelp l, spoint p, int slot, Tpp *out);
[[nodiscard]] Thingp      thing_and_tp_get_at(Gamep g, Levelsp v, Levelp l, spoint p, int slot, Tpp *out);
[[nodiscard]] Thingp      thing_find_non_inline(Gamep g, Levelsp v, ThingId id);
[[nodiscard]] Thingp      thing_get_at_safe(Gamep g, Levelsp v, Levelp l, spoint p, int slot);
[[nodiscard]] Thingp      thing_get(Gamep g, Levelsp v, Levelp l, spoint p, int slot);
[[nodiscard]] Thingp      thing_init(Gamep g, Levelsp v, Levelp l, Tpp tp, const fpoint &real_at);
[[nodiscard]] Thingp      thing_init(Gamep g, Levelsp v, Levelp l, Tpp tp, const spoint &at);
[[nodiscard]] Thingp      thing_minion_mob_get(Gamep g, Levelsp v, Levelp l, Thingp minion);
[[nodiscard]] Thingp      thing_mob_spawn_a_minion(Gamep g, Levelsp v, Levelp l, Thingp mob, Tpp tp_minion);
[[nodiscard]] Thingp      thing_player(Gamep g);
[[nodiscard]] Thingp      thing_spawn(Gamep, Levelsp, Levelp, Tpp tp, const fpoint &at);
[[nodiscard]] Thingp      thing_spawn(Gamep, Levelsp, Levelp, Tpp tp, const spoint &at);
[[nodiscard]] Thingp      thing_spawn(Gamep, Levelsp, Levelp, Tpp tp, Thingp thing_at);
[[nodiscard]] Thingp      top_owner(Gamep g, Levelsp v, Levelp l, Thingp t);
[[nodiscard]] Thingp      wid_get_thing_context(Gamep g, Levelsp v, Widp w, int which);
[[nodiscard]] ThingPriorityType thing_priority_set(Gamep, Levelsp, Levelp, Thingp t, ThingPriorityType val);
[[nodiscard]] ThingPriorityType thing_priority(Thingp t);
ThingPlayerp                    thing_player_struct(Gamep g);
// end sort marker1 }

// begin sort marker2 {
void LEVEL_BOTCON(Gamep g, Levelsp v, Levelp l, const char *fmt, ...) CHECK_FORMAT_STR(printf, 4, 5);
void LEVEL_CON(Gamep g, Levelsp v, Levelp l, const char *fmt, ...) CHECK_FORMAT_STR(printf, 4, 5);
void LEVEL_DBG(Gamep g, Levelsp v, Levelp l, const char *fmt, ...) CHECK_FORMAT_STR(printf, 4, 5);
void LEVEL_ERR(Gamep g, Levelsp v, Levelp l, const char *fmt, ...) CHECK_FORMAT_STR(printf, 4, 5);
void LEVEL_LOG(Gamep g, Levelsp v, Levelp l, const char *fmt, ...) CHECK_FORMAT_STR(printf, 4, 5);
void LEVEL_TOPCON(Gamep g, Levelsp v, Levelp l, const char *fmt, ...) CHECK_FORMAT_STR(printf, 4, 5);
void LEVEL_WARN(Gamep g, Levelsp v, Levelp l, const char *fmt, ...) CHECK_FORMAT_STR(printf, 4, 5);
void monst_state_change(Gamep g, Levelsp v, Levelp l, Thingp me, MonstState new_state);
void player_collision_handle(Gamep g, Levelsp v, Levelp l, Thingp me);
void player_fell(Gamep g, Levelsp v, Levelp l, Levelp next_level, Thingp me);
void player_fire(Gamep g, Levelsp v, Levelp l, int dx, int dy, Tpp what);
void player_map_center(Gamep, Levelsp, Levelp);
void player_move_accum(Gamep g, Levelsp v, Levelp l, bool up, bool down, bool left, bool right, bool fire);
void player_move_reset(Gamep g, Levelsp v, Levelp l);
void player_reached_entrance(Gamep g, Levelsp v, Levelp l);
void player_reached_exit(Gamep g, Levelsp v, Levelp l);
void player_warp_to_specific_level(Gamep g, Levelsp v, LevelNum level_num);
void thing_anim_init(Gamep, Levelsp, Levelp, Thingp t, ThingAnim anim_type);
void thing_anim_time_step(Gamep, Levelsp, Levelp, Thingp t, Tpp tp, int time_step);
void thing_at_set(Thingp t, const fpoint &val);
void thing_at_set(Thingp t, const spoint &val);
void THING_BOTCON(Thingp t, const char *fmt, ...) CHECK_FORMAT_STR(printf, 2, 3);
void thing_chasm_handle(Gamep g, Levelsp v, Levelp l, Thingp me);
void thing_collision_handle_interpolated(Gamep, Levelsp, Levelp, Thingp me, fpoint old_at);
void thing_collision_handle(Gamep, Levelsp, Levelp, Thingp me);
void THING_CON(Thingp t, const char *fmt, ...) CHECK_FORMAT_STR(printf, 2, 3);
void thing_continue_to_burn_check(Gamep g, Levelsp v, Levelp l, Thingp t);
void thing_damage(Gamep g, Levelsp v, Levelp l, Thingp t, ThingEvent &e);
void THING_DBG(Thingp t, const char *fmt, ...) CHECK_FORMAT_STR(printf, 2, 3);
void thing_dead(Gamep g, Levelsp v, Levelp l, Thingp t, ThingEvent &e);
void thing_dir_bl_set(Thingp, uint8_t);
void thing_dir_br_set(Thingp, uint8_t);
void thing_dir_down_set(Thingp, uint8_t);
void thing_dir_left_set(Thingp, uint8_t);
void thing_dir_right_set(Thingp, uint8_t);
void thing_dir_tl_set(Thingp, uint8_t);
void thing_dir_tr_set(Thingp, uint8_t);
void thing_dir_up_set(Thingp, uint8_t);
void thing_dmap(Gamep g, Levelsp v, Levelp l, Thingp me, bool reverse = false);
void THING_ERR(Thingp t, const char *fmt, ...) CHECK_FORMAT_STR(printf, 2, 3);
void thing_explosion_handle(Gamep, Levelsp, Levelp, Thingp t);
void thing_fall_end_check(Gamep, Levelsp, Levelp, Thingp t);
void thing_fall_time_step(Gamep, Levelsp, Levelp, Thingp t, int time_step);
void thing_fall(Gamep, Levelsp, Levelp, Thingp t);
void thing_fini(Gamep g, Levelsp v, Levelp l, Thingp t);
void thing_free(Gamep g, Levelsp v, Levelp l, Thingp t);
void thing_hit_time_step(Gamep g, Levelsp v, Levelp l, Thingp t, int time_step);
void thing_hot_time_step(Gamep g, Levelsp v, Levelp l, Thingp t, int time_step);
void thing_interpolate(Gamep, Levelsp, Levelp, Thingp t, float dt);
void thing_inventory_dump(Gamep, Levelsp, Levelp, Thingp player_or_monst);
void thing_is_burning_handle(Gamep g, Levelsp v, Levelp l, Thingp t);
void thing_is_burning_set(Gamep, Levelsp, Levelp, Thingp t, bool val = true);
void thing_is_burning_unset(Gamep, Levelsp, Levelp, Thingp t);
void thing_is_corpse_set(Gamep, Levelsp, Levelp, Thingp t, bool val = true);
void thing_is_corpse_unset(Gamep, Levelsp, Levelp, Thingp t);
void thing_is_dead_handle(Gamep g, Levelsp v, Levelp l, Thingp t);
void thing_is_dead_set(Gamep, Levelsp, Levelp, Thingp t, bool val = true);
void thing_is_dead_unset(Gamep, Levelsp, Levelp, Thingp t);
void thing_is_falling_continues_set(Gamep, Levelsp, Levelp, Thingp t, bool val = true);
void thing_is_falling_continues_unset(Gamep, Levelsp, Levelp, Thingp t);
void thing_is_falling_set(Gamep, Levelsp, Levelp, Thingp t, bool val);
void thing_is_hit_set(Gamep, Levelsp, Levelp, Thingp t, int val);
void thing_is_hot_set(Gamep, Levelsp, Levelp, Thingp t, int val);
void thing_is_jumping_set(Gamep, Levelsp, Levelp, Thingp t, bool val = true);
void thing_is_jumping_unset(Gamep, Levelsp, Levelp, Thingp t);
void thing_is_moving_set(Gamep, Levelsp, Levelp, Thingp t, bool val = true);
void thing_is_moving_unset(Gamep, Levelsp, Levelp, Thingp t);
void thing_is_on_map_set(Gamep, Levelsp, Levelp, Thingp t, bool val = true);
void thing_is_on_map_unset(Gamep, Levelsp, Levelp, Thingp t);
void thing_is_scheduled_for_cleanup_set(Gamep, Levelsp, Levelp, Thingp t, bool val = true);
void thing_is_scheduled_for_cleanup_unset(Gamep, Levelsp, Levelp, Thingp t);
void thing_is_sleeping_set(Gamep, Levelsp, Levelp, Thingp t, bool val = true);
void thing_is_sleeping_unset(Gamep, Levelsp, Levelp, Thingp t);
void thing_is_spawned_set(Gamep, Levelsp, Levelp, Thingp t, bool val = true);
void thing_is_spawned_unset(Gamep, Levelsp, Levelp, Thingp t);
void thing_is_teleporting_set(Gamep, Levelsp, Levelp, Thingp t, bool val = true);
void thing_is_teleporting_unset(Gamep, Levelsp, Levelp, Thingp t);
void thing_is_unlocked_set(Gamep, Levelsp, Levelp, Thingp t, bool val = true);
void thing_is_unlocked_unset(Gamep, Levelsp, Levelp, Thingp t);
void thing_level_warp_to_entrance(Gamep g, Levelsp v, Levelp new_level, Thingp t);
void thing_level_warp_to_exit(Gamep g, Levelsp v, Levelp new_level, Thingp t);
void THING_LOG(Thingp t, const char *fmt, ...) CHECK_FORMAT_STR(printf, 2, 3);
void thing_melt(Gamep, Levelsp, Levelp, Thingp t);
void thing_mob_dump_minions(Gamep g, Levelsp v, Levelp l, Thingp mob);
void thing_monst_event_loop(Gamep g, Levelsp v, Levelp l, Thingp me);
void thing_monst_tick(Gamep g, Levelsp v, Levelp l, Thingp me);
void thing_move_or_jump_finish(Gamep, Levelsp, Levelp, Thingp me);
void thing_move_path_reset(Gamep, Levelsp, Levelp, Thingp t);
void thing_moving_from_set(Thingp t, const spoint &val);
void thing_path_shorten(Gamep, Levelsp, Levelp, Thingp t, std::vector< spoint > &path);
void thing_pix_at_set(Gamep, Levelsp, Levelp, Thingp t, const spoint &val);
void thing_pix_at_set(Gamep, Levelsp, Levelp, Thingp t, short x, short y);
void thing_player_event_loop(Gamep g, Levelsp v, Levelp l);
void thing_prev_pix_at_set(Gamep, Levelsp, Levelp, Thingp t, const spoint &val);
void thing_projectile_move(Gamep, Levelsp, Levelp, Thingp t, float dt);
void thing_set_dir_from_delta(Thingp me, int dx, int dy);
void thing_sound_play(Gamep g, Levelsp v, Levelp l, Thingp t, const std::string &alias);
void thing_stats_dump(Gamep g, Levelsp v);
void thing_target_set(Gamep, Levelsp, Levelp, Thingp t, const spoint &val);
void thing_temperature_damage_handle(Gamep, Levelsp, Levelp, Thingp it, Thingp me, int t);
void thing_temperature_handle(Gamep, Levelsp, Levelp, Thingp it, Thingp me, int t);
void thing_tick_begin(Gamep g, Levelsp v, Levelp l, Thingp t);
void thing_tick_end(Gamep g, Levelsp v, Levelp l, Thingp t);
void thing_tick_idle(Gamep g, Levelsp v, Levelp l, Thingp t);
void THING_TOPCON(Thingp t, const char *fmt, ...) CHECK_FORMAT_STR(printf, 2, 3);
void thing_update_pos(Gamep, Levelsp, Levelp, Thingp me);
void thing_vision_reset(Gamep g, Levelsp v, Levelp l, Thingp t);
void THING_WARN(Thingp t, const char *fmt, ...) CHECK_FORMAT_STR(printf, 2, 3);
void thing_water_handle(Gamep g, Levelsp v, Levelp l, Thingp me);
void tp_collision_init(Tpp tp);
void tp_temperature_init(Tpp tp);
void wid_set_thing_context(Gamep g, Levelsp v, Widp w, Thingp t);
void wid_thing_info(Gamep g, Levelsp v, Levelp l, Thingp t, WidPopup *parent, int width);
void wid_unset_thing_context(Gamep g, Levelsp v, Widp w, Thingp t);
// end sort marker2 }

void thing_display_get_tile_info(Gamep g, Levelsp v, Levelp l, spoint p, Tpp tp_maybe_null, Thingp t_maybe_null,
                                 spoint *tl, spoint *br, uint16_t *tile_index);

void thing_display(Gamep g, Levelsp v, Levelp l, spoint p, Tpp tp, Thingp t_maybe_null, spoint tl, spoint br,
                   uint16_t tile_index, FboEnum fbo);

void thing_blit_text(Gamep g, Levelsp v, Levelp l, spoint tl, spoint br, std::string const &text, color fg,
                     bool outline);

std::vector< spoint > astar_solve(Gamep, Levelsp, Levelp, Thingp t, spoint src, spoint dst);

#define FOR_ALL_MINION_SLOTS(_g_, _v_, _l_, _mob_, _slot_, _minion_)                                                 \
  if (_g_ && _v_ && _l_)                                                                                             \
    for (auto _ext_ = thing_ext_struct(_g_, _mob_); _ext_; _ext_ = nullptr)                                          \
      for (auto _n_ = 0; _n_ < THING_MINION_MAX; _n_++)                                                              \
        for (auto _slot_ = &_ext_->minions.minion[ _n_ ]; _slot_; _slot_ = nullptr)                                  \
          for (auto _minion_ = thing_find_optional(g, v, _slot_->minion_id), loop2 = (Thingp) 1;                     \
               loop2 == (Thingp) 1; loop2 = (Thingp) 0)

#define FOR_ALL_MINIONS(_g_, _v_, _l_, _mob_, _minion_)                                                              \
  if (_g_ && _v_ && _l_)                                                                                             \
    for (auto _ext_ = thing_ext_struct(_g_, _mob_); _ext_; _ext_ = nullptr)                                          \
      for (auto _n_ = 0; _n_ < THING_MINION_MAX; _n_++)                                                              \
        for (auto _slot_ = &_ext_->minions.minion[ _n_ ]; _slot_; _slot_ = nullptr)                                  \
          for (Thingp _minion_ = thing_find_optional(g, v, _slot_->minion_id); _minion_; _minion_ = nullptr)

#define FOR_ALL_INVENTORY_SLOTS(_g_, _v_, _l_, _owner_, _slot_, _item_)                                              \
  if (_g_ && _v_ && _l_)                                                                                             \
    for (auto _ext_ = thing_player_struct(_g_); _ext_; _ext_ = nullptr)                                              \
      for (auto _n_ = 0; _n_ < THING_INVENTORY_MAX; _n_++)                                                           \
        for (auto _slot_ = &_ext_->inventory.slots[ _n_ ]; _slot_; _slot_ = nullptr)                                 \
          for (auto _item_ = thing_find_optional(g, v, _slot_->item_id), loop2 = (Thingp) 1; loop2 == (Thingp) 1;    \
               loop2 = (Thingp) 0)

#define FOR_ALL_INVENTORY_ITEMS(_g_, _v_, _l_, _owner_, _item_)                                                      \
  if (_g_ && _v_ && _l_)                                                                                             \
    for (auto _ext_ = thing_player_struct(_g_); _ext_; _ext_ = nullptr)                                              \
      for (auto _n_ = 0; _n_ < THING_INVENTORY_MAX; _n_++)                                                           \
        for (auto _slot_ = &_ext_->inventory.slots[ _n_ ]; _slot_; _slot_ = nullptr)                                 \
          for (auto _item_ = thing_find_optional(g, v, _slot_->item_id); _item_; _item_ = nullptr)

#endif
