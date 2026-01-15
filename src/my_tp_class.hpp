//
// Copyright goblinhack@gmail.com
//

#pragma once
#ifndef _MY_TP_CLASS_H_
#define _MY_TP_CLASS_H_

#include "my_color_defs.hpp"
#include "my_dice_class.hpp"
#include "my_thing.hpp"
#include "my_thing_callbacks.hpp"
#include "my_tp.hpp"

#include <string>
#include <vector>

class Tp
{
public:
  TpId id {};

  //
  // This allows us to draw floors, then objs and walls in order
  //
  uint8_t z_depth {};

  //
  // This is for objects at the same z depth
  //
  uint8_t z_layer {};

  //
  // See ThingFlag
  //
  int flag[ THING_FLAG_ENUM_MAX ] = {};

  //
  // Animation tiles
  //
  std::vector< class Tile * > tiles[ THING_ANIM_ENUM_MAX ];

  //
  // Which classes does this monst belong too
  //
  bool is_monst_group[ MONST_GROUP_ENUM_MAX ] {};

  //
  // Immunity to various damage types
  //
  bool is_immune[ THING_EVENT_ENUM_MAX ] {};

  //
  // Chance of this appearing on a level
  //
  int chance_d1000_appearing {};

  //
  // Speed compared to player
  //
  int speed {100};

  //
  // Weight in grams
  //
  int weight {0};

  //
  // Starting health.
  //
  Dice health_initial;

  //
  // Temperature in celsius
  //
  int temperature_initial {0};

  //
  // When the thing catches fire
  //
  int temperature_burns_at {0};

  //
  // When the thing takes damage from heat
  //
  int temperature_damage_at {0};

  //
  // For event processing. Lower is higher priority.
  //
  ThingPriorityType priority {THING_PRIORITY_LOW};

  //
  // In tiles
  //
  int vision_distance {0};

  //
  // In tiles
  //
  int jump_distance {0};

  int value1 {0};
  int value2 {0};
  int value3 {0};
  int value4 {0};
  int value5 {0};
  int value6 {0};
  int value7 {0};
  int value8 {0};
  int value9 {0};
  int value10 {0};
  int value11 {0};
  int value12 {0};
  int value13 {0};
  int value14 {0};
  int value15 {0};
  int value16 {0};
  int value17 {0};
  int value18 {0};
  int value19 {0};
  int value20 {0};
  int value21 {0};
  int value22 {0};
  int value23 {0};
  int value24 {0};
  int value25 {0};
  int variant {0};

  //
  // Lifespan in ticks. -1 is forever.
  //
  Dice lifespan;

  //
  // Internal name
  //
  std::string name;

  //
  // For mimics
  //
  std::string real_name;

  //
  // Short name for lists
  //
  std::string short_name;

  //
  // Longer name for attacks text
  //
  std::string long_name;

  //
  // monster's
  //
  std::string apostrophize_name;

  //
  // monsters
  //
  std::string pluralize_name;

  //
  // Damage types, in dice
  //
  Dice damage[ THING_EVENT_ENUM_MAX ];

  //
  // Chance types, in dice
  //
  Dice chance[ THING_EVENT_ENUM_MAX ];

  //
  // For braziers and more
  //
  color light_color = {WHITE};

  //
  // Callbacks
  //
  thing_description_get_t       description_get       = {};
  thing_detail_get_t            detail_get            = {};
  thing_mouse_down_t            mouse_down            = {};
  thing_on_spawned_t            on_spawned            = {};
  thing_on_level_populated_t    on_level_populated    = {};
  thing_on_level_enter_t        on_level_enter        = {};
  thing_on_level_leave_t        on_level_leave        = {};
  thing_on_open_request_t       on_open_request       = {};
  thing_on_carry_request_t      on_carry_request      = {};
  thing_on_drop_request_t       on_drop_request       = {};
  thing_on_close_request_t      on_close_request      = {};
  thing_on_tick_idle_t          tick_idle             = {};
  thing_on_tick_begin_t         tick_begin            = {};
  thing_on_tick_end_t           tick_end              = {};
  thing_on_death_t              on_death              = {};
  thing_on_moved_t              on_moved              = {};
  thing_on_teleported_t         on_teleported         = {};
  thing_on_shoved_t             on_shoved             = {};
  thing_on_jump_end_t           on_jump_end           = {};
  thing_on_jump_begin_t         on_jump_begin         = {};
  thing_on_fall_begin_t         on_fall_begin         = {};
  thing_on_fall_end_t           on_fall_end           = {};
  thing_on_hit_begin_t          on_hit_begin          = {};
  thing_on_hit_end_t            on_hit_end            = {};
  thing_display_get_tile_info_t display_get_tile_info = {};

  Tp(void);
  ~Tp(void);
};

#endif
