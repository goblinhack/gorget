//
// Copyright goblinhack@gmail.com
//

#pragma once
#ifndef _MY_THING_TEMPLATE_H_
#define _MY_THING_TEMPLATE_H_

#include "my_color.hpp"
#include "my_enum.hpp"
#include "my_types.hpp"

#include <stdarg.h>
#include <string>

//
// Thing flags enum
//
#define THING_FLAG_ENUM(list_macro)                                                                                  \
  clang_format_indent()                                                 /* dummy line for clang indentation fixup */ \
      list_macro(is_able_to_collect_items, "is_able_to_collect_items"), /* newline */                                \
      list_macro(is_able_to_collect_keys, "is_able_to_collect_keys"),   /* newline */                                \
      list_macro(is_able_to_crush_grass, "is_able_to_crush_grass"),     /* newline */                                \
      list_macro(is_able_to_fall, "is_able_to_fall"),                   /* newline */                                \
      list_macro(is_able_to_jump, "is_able_to_jump"),                   /* newline */                                \
      list_macro(is_able_to_open, "is_able_to_open"),                   /* newline */                                \
      list_macro(is_able_to_shove, "is_able_to_shove"),                 /* newline */                                \
      list_macro(is_animated_can_hflip, "is_animated_can_hflip"),       /* newline */                                \
      list_macro(is_animated_no_dir, "is_animated_no_dir"),             /* newline */                                \
      list_macro(is_animated_sync_first, "is_animated_sync_first"),     /* newline */                                \
      list_macro(is_animated, "is_animated"),                           /* newline */                                \
      list_macro(is_barrel, "is_barrel"),                               /* newline */                                \
      list_macro(is_blit_centered, "is_blit_centered"),                 /* newline */                                \
      list_macro(is_blit_colored_always, "is_blit_colored_always"),     /* newline */                                \
      list_macro(is_blit_on_ground, "is_blit_on_ground"),               /* newline */                                \
      list_macro(is_blit_outlined, "is_blit_outlined"),                 /* newline */                                \
      list_macro(is_blit_square_outlined, "is_blit_square_outlined"),   /* newline */                                \
      list_macro(is_brazier, "is_brazier"),                             /* newline */                                \
      list_macro(is_bridge, "is_bridge"),                               /* newline */                                \
      list_macro(is_broken_on_death, "is_broken_on_death"),             /* newline */                                \
      list_macro(is_burnable, "is_burnable"),                           /* newline */                                \
      list_macro(is_chasm, "is_chasm"),                                 /* newline */                                \
      list_macro(is_collectable, "is_collectable"),                     /* newline */                                \
      list_macro(is_combustible, "is_combustible"),                     /* newline */                                \
      list_macro(is_corpse_on_death, "is_corpse_on_death"),             /* newline */                                \
      list_macro(is_corridor, "is_corridor"),                           /* newline */                                \
      list_macro(is_crushable, "is_crushable"),                         /* newline */                                \
      list_macro(is_cursor_hazard, "is_cursor_hazard"),                 /* newline */                                \
      list_macro(is_cursor_path_hazard, "is_cursor_path_hazard"),       /* newline */                                \
      list_macro(is_cursor_path_none, "is_cursor_path_none"),           /* newline */                                \
      list_macro(is_cursor_path, "is_cursor_path"),                     /* newline */                                \
      list_macro(is_cursor, "is_cursor"),                               /* newline */                                \
      list_macro(is_damage_capped, "is_damage_capped"),                 /* newline */                                \
      list_macro(is_dead_on_shoving, "is_dead_on_shoving"),             /* newline */                                \
      list_macro(is_deep_water, "is_deep_water"),                       /* newline */                                \
      list_macro(is_described_cursor, "is_described_cursor"),           /* newline */                                \
      list_macro(is_dirt, "is_dirt"),                                   /* newline */                                \
      list_macro(is_door_locked, "is_door_locked"),                     /* newline */                                \
      list_macro(is_door_secret, "is_door_secret"),                     /* newline */                                \
      list_macro(is_door_unlocked, "is_door_unlocked"),                 /* newline */                                \
      list_macro(is_dungeon_entrance, "is_dungeon_entrance"),           /* newline */                                \
      list_macro(is_entrance, "is_entrance"),                           /* newline */                                \
      list_macro(is_ethereal, "is_ethereal"),                           /* newline */                                \
      list_macro(is_exit, "is_exit"),                                   /* newline */                                \
      list_macro(is_explosion, "is_explosion"),                         /* newline */                                \
      list_macro(is_extinguished_on_death, "is_extinguished_on_death"), /* newline */                                \
      list_macro(is_fire, "is_fire"),                                   /* newline */                                \
      list_macro(is_floating, "is_floating"),                           /* newline */                                \
      list_macro(is_floor, "is_floor"),                                 /* newline */                                \
      list_macro(is_flying, "is_flying"),                               /* newline */                                \
      list_macro(is_foliage, "is_foliage"),                             /* newline */                                \
      list_macro(is_gaseous, "is_gaseous"),                             /* newline */                                \
      list_macro(is_ghost, "is_ghost"),                                 /* newline */                                \
      list_macro(is_grass, "is_grass"),                                 /* newline */                                \
      list_macro(is_health_bar_shown, "is_health_bar_shown"),           /* newline */                                \
      list_macro(is_indestructible, "is_indestructible"),               /* newline */                                \
      list_macro(is_inventory_item, "is_inventory_item"),               /* newline */                                \
      list_macro(is_item_droppable, "is_item_droppable"),               /* newline */                                \
      list_macro(is_item_equipable, "is_item_equipable"),               /* newline */                                \
      list_macro(is_item_mergeable, "is_item_mergeable"),               /* newline */                                \
      list_macro(is_item, "is_item"),                                   /* newline */                                \
      list_macro(is_key, "is_key"),                                     /* newline */                                \
      list_macro(is_kobalos, "is_kobalos"),                             /* newline */                                \
      list_macro(is_lava, "is_lava"),                                   /* newline */                                \
      list_macro(is_level_across, "is_level_across"),                   /* newline */                                \
      list_macro(is_level_curr, "is_level_curr"),                       /* newline */                                \
      list_macro(is_level_down, "is_level_down"),                       /* newline */                                \
      list_macro(is_level_final, "is_level_final"),                     /* newline */                                \
      list_macro(is_level_next, "is_level_next"),                       /* newline */                                \
      list_macro(is_level_not_visited, "is_level_not_visited"),         /* newline */                                \
      list_macro(is_level_visited, "is_level_visited"),                 /* newline */                                \
      list_macro(is_levitating, "is_levitating"),                       /* newline */                                \
      list_macro(is_obs_to_vision, "is_obs_to_vision"),                 /* newline */                                \
      list_macro(is_light_source, "is_light_source"),                   /* newline */                                \
      list_macro(is_loggable, "is_loggable"),                           /* newline */                                \
      list_macro(is_minion, "is_minion"),                               /* newline */                                \
      list_macro(is_mob, "is_mob"),                                     /* newline */                                \
      list_macro(is_mob1, "is_mob1"),                                   /* newline */                                \
      list_macro(is_mob2, "is_mob2"),                                   /* newline */                                \
      list_macro(is_monst_group_mob, "is_monst_group_mob"),             /* newline */                                \
      list_macro(is_monst_group_easy, "is_monst_group_easy"),           /* newline */                                \
      list_macro(is_monst_group_hard, "is_monst_group_hard"),           /* newline */                                \
      list_macro(is_monst, "is_monst"),                                 /* newline */                                \
      list_macro(is_needs_move_confirm, "is_needs_move_confirm"),       /* newline */                                \
      list_macro(is_obs_to_cursor_path, "is_obs_to_cursor_path"),       /* newline */                                \
      list_macro(is_obs_to_explosion, "is_obs_to_explosion"),           /* newline */                                \
      list_macro(is_obs_to_falling_onto, "is_obs_to_falling_onto"),     /* newline */                                \
      list_macro(is_obs_to_fire, "is_obs_to_fire"),                     /* newline */                                \
      list_macro(is_obs_to_jump_over, "is_obs_to_jump_over"),           /* newline */                                \
      list_macro(is_obs_to_jumping_onto, "is_obs_to_jumping_onto"),     /* newline */                                \
      list_macro(is_obs_to_movement, "is_obs_to_movement"),             /* newline */                                \
      list_macro(is_openable, "is_openable"),                           /* newline */                                \
      list_macro(is_physics_explosion, "is_physics_explosion"),         /* newline */                                \
      list_macro(is_physics_temperature, "is_physics_temperature"),     /* newline */                                \
      list_macro(is_physics_water, "is_physics_water"),                 /* newline */                                \
      list_macro(is_pillar, "is_pillar"),                               /* newline */                                \
      list_macro(is_player, "is_player"),                               /* newline */                                \
      list_macro(is_rock, "is_rock"),                                   /* newline */                                \
      list_macro(is_shovable, "is_shovable"),                           /* newline */                                \
      list_macro(is_slime, "is_slime"),                                 /* newline */                                \
      list_macro(is_smoke, "is_smoke"),                                 /* newline */                                \
      list_macro(is_steam, "is_steam"),                                 /* newline */                                \
      list_macro(is_submergible, "is_submergible"),                     /* newline */                                \
      list_macro(is_teleport_blocked, "is_teleport_blocked"),           /* newline */                                \
      list_macro(is_teleport, "is_teleport"),                           /* newline */                                \
      list_macro(is_tick_delay_on_spawn, "is_tick_delay_on_spawn"),     /* newline */                                \
      list_macro(is_tickable, "is_tickable"),                           /* newline */                                \
      list_macro(is_tiled, "is_tiled"),                                 /* newline */                                \
      list_macro(is_trap, "is_trap"),                                   /* newline */                                \
      list_macro(is_treasure, "is_treasure"),                           /* newline */                                \
      list_macro(is_undead, "is_undead"),                               /* newline */                                \
      list_macro(is_unused1, "is_unused1"),                             /* newline */                                \
      list_macro(is_unused2, "is_unused2"),                             /* newline */                                \
      list_macro(is_unused3, "is_unused3"),                             /* newline */                                \
      list_macro(is_unused4, "is_unused4"),                             /* newline */                                \
      list_macro(is_blit_if_has_seen, "is_blit_if_has_seen"),           /* newline */                                \
      list_macro(is_wait_on_dead_anim, "is_wait_on_dead_anim"),         /* newline */                                \
      list_macro(is_walk_through_walls, "is_walk_through_walls"),       /* newline */                                \
      list_macro(is_wall, "is_wall"),                                   /* newline */                                \
      list_macro(is_water, "is_water"),                                 /* newline */

ENUM_DEF_H(THING_FLAG_ENUM, ThingFlag)

//
// Things all at the same z layer that can be drawn at the same x,y
//
#define MAP_Z_DEPTH_ENUM(list_macro)                                                                                 \
  clang_format_indent()                                    /* dummy line for clang indentation fixup */              \
      list_macro(MAP_Z_DEPTH_CHASM, "chasm"),              /* newline */                                             \
      list_macro(MAP_Z_DEPTH_FLOOR, "floor"),              /* newline */                                             \
      list_macro(MAP_Z_DEPTH_LIQUID, "e.g. water"),        /* newline */                                             \
      list_macro(MAP_Z_DEPTH_LIQUID2, "e.g. deep water"),  /* newline */                                             \
      list_macro(MAP_Z_DEPTH_GRASS, "grass"),              /* newline */                                             \
      list_macro(MAP_Z_DEPTH_OBJ, "monsts"),               /* newline */                                             \
      list_macro(MAP_Z_DEPTH_PLAYER, "monsts"),            /* newline */                                             \
      list_macro(MAP_Z_DEPTH_FOLIAGE, "obscuring plants"), /* newline */                                             \
      list_macro(MAP_Z_DEPTH_GAS, "fire, smoke"),          /* newline */

ENUM_DEF_H(MAP_Z_DEPTH_ENUM, MapZDepth)

#define MAP_Z_DEPTH_ENUM_FIRST ((MapZDepth) 0)

#define FOR_ALL_MAP_Z_DEPTH(_iter_)                                                                                  \
  for (MapZDepth _iter_ = MAP_Z_DEPTH_ENUM_FIRST; /* newline */                                                      \
       _iter_ < MAP_Z_DEPTH_ENUM_MAX;             /* newline */                                                      \
       _iter_ = static_cast< MapZDepth >(static_cast< int >(_iter_) + 1))

//
// Monst challenge level
//
#define MONST_GROUP_ENUM(list_macro)                                                                                 \
  clang_format_indent()                  /* dummy line for clang indentation fixup */                                \
      list_macro(MONST_GROUP_MOB, "0"),  /* Used for monsters that are only generated by mobs */                     \
      list_macro(MONST_GROUP_EASY, "1"), /* newline */                                                               \
      list_macro(MONST_GROUP_HARD, "2"), /* newline */

ENUM_DEF_H(MONST_GROUP_ENUM, ThingMonstGroup)

//
// Thing anim enum
//
#define THING_ANIM_ENUM(list_macro)                                                                                  \
  clang_format_indent()                                    /* dummy line for clang indentation fixup */              \
      list_macro(THING_ANIM_JOIN_BL, "IS_JOIN_BL"),        /* newline */                                             \
      list_macro(THING_ANIM_JOIN_BL2, "IS_JOIN_BL2"),      /* newline */                                             \
      list_macro(THING_ANIM_JOIN_BLOCK, "IS_JOIN_BLOCK"),  /* newline */                                             \
      list_macro(THING_ANIM_JOIN_BOT, "IS_JOIN_BOT"),      /* newline */                                             \
      list_macro(THING_ANIM_JOIN_BR, "IS_JOIN_BR"),        /* newline */                                             \
      list_macro(THING_ANIM_JOIN_BR2, "IS_JOIN_BR2"),      /* newline */                                             \
      list_macro(THING_ANIM_JOIN_HORIZ, "IS_JOIN_HORIZ"),  /* newline */                                             \
      list_macro(THING_ANIM_JOIN_HORIZ2, "IS_JOIN_HORIZ"), /* newline */                                             \
      list_macro(THING_ANIM_JOIN_LEFT, "IS_JOIN_LEFT"),    /* newline */                                             \
      list_macro(THING_ANIM_JOIN_NODE, "IS_JOIN_NODE"),    /* newline */                                             \
      list_macro(THING_ANIM_JOIN_RIGHT, "IS_JOIN_RIGHT"),  /* newline */                                             \
      list_macro(THING_ANIM_JOIN_T_1, "IS_JOIN_T_1"),      /* newline */                                             \
      list_macro(THING_ANIM_JOIN_T_2, "IS_JOIN_T_2"),      /* newline */                                             \
      list_macro(THING_ANIM_JOIN_T_3, "IS_JOIN_T_3"),      /* newline */                                             \
      list_macro(THING_ANIM_JOIN_T, "IS_JOIN_T"),          /* newline */                                             \
      list_macro(THING_ANIM_JOIN_T180_1, "IS_JOIN_T180_"), /* newline */                                             \
      list_macro(THING_ANIM_JOIN_T180_2, "IS_JOIN_T180_"), /* newline */                                             \
      list_macro(THING_ANIM_JOIN_T180_3, "IS_JOIN_T180_"), /* newline */                                             \
      list_macro(THING_ANIM_JOIN_T180, "IS_JOIN_T180"),    /* newline */                                             \
      list_macro(THING_ANIM_JOIN_T270_1, "IS_JOIN_T270_"), /* newline */                                             \
      list_macro(THING_ANIM_JOIN_T270_2, "IS_JOIN_T270_"), /* newline */                                             \
      list_macro(THING_ANIM_JOIN_T270_3, "IS_JOIN_T270_"), /* newline */                                             \
      list_macro(THING_ANIM_JOIN_T270, "IS_JOIN_T270"),    /* newline */                                             \
      list_macro(THING_ANIM_JOIN_T90_1, "IS_JOIN_T90_1"),  /* newline */                                             \
      list_macro(THING_ANIM_JOIN_T90_2, "IS_JOIN_T90_2"),  /* newline */                                             \
      list_macro(THING_ANIM_JOIN_T90_3, "IS_JOIN_T90_3"),  /* newline */                                             \
      list_macro(THING_ANIM_JOIN_T90, "IS_JOIN_T90"),      /* newline */                                             \
      list_macro(THING_ANIM_JOIN_TL, "IS_JOIN_TL"),        /* newline */                                             \
      list_macro(THING_ANIM_JOIN_TL2, "IS_JOIN_TL2"),      /* newline */                                             \
      list_macro(THING_ANIM_JOIN_TOP, "IS_JOIN_TOP"),      /* newline */                                             \
      list_macro(THING_ANIM_JOIN_TR, "IS_JOIN_TR"),        /* newline */                                             \
      list_macro(THING_ANIM_JOIN_TR2, "IS_JOIN_TR2"),      /* newline */                                             \
      list_macro(THING_ANIM_JOIN_VERT, "IS_JOIN_VERT"),    /* newline */                                             \
      list_macro(THING_ANIM_JOIN_VERT2, "IS_JOIN_VERT2"),  /* newline */                                             \
      list_macro(THING_ANIM_JOIN_X, "IS_JOIN_X"),          /* newline */                                             \
      list_macro(THING_ANIM_JOIN_X1_180, "IS_JOIN_X1_18"), /* newline */                                             \
      list_macro(THING_ANIM_JOIN_X1_270, "IS_JOIN_X1_27"), /* newline */                                             \
      list_macro(THING_ANIM_JOIN_X1_90, "IS_JOIN_X1_90"),  /* newline */                                             \
      list_macro(THING_ANIM_JOIN_X1, "IS_JOIN_X1"),        /* newline */                                             \
      list_macro(THING_ANIM_JOIN_X2_180, "IS_JOIN_X2_18"), /* newline */                                             \
      list_macro(THING_ANIM_JOIN_X2_270, "IS_JOIN_X2_27"), /* newline */                                             \
      list_macro(THING_ANIM_JOIN_X2_90, "IS_JOIN_X2_90"),  /* newline */                                             \
      list_macro(THING_ANIM_JOIN_X2, "IS_JOIN_X2"),        /* newline */                                             \
      list_macro(THING_ANIM_JOIN_X3_180, "IS_JOIN_X3_18"), /* newline */                                             \
      list_macro(THING_ANIM_JOIN_X3, "IS_JOIN_X3"),        /* newline */                                             \
      list_macro(THING_ANIM_JOIN_X4_180, "IS_JOIN_X4_18"), /* newline */                                             \
      list_macro(THING_ANIM_JOIN_X4_270, "IS_JOIN_X4_27"), /* newline */                                             \
      list_macro(THING_ANIM_JOIN_X4_90, "IS_JOIN_X4_90"),  /* newline */                                             \
      list_macro(THING_ANIM_JOIN_X4, "IS_JOIN_X4"),        /* newline */                                             \
      list_macro(THING_ANIM_IDLE, "idle"),                 /* newline */                                             \
      list_macro(THING_ANIM_OPEN, "open"),                 /* newline */                                             \
      list_macro(THING_ANIM_DEAD, "dead"),                 /* newline */                                             \
      list_macro(THING_ANIM_BURNT, "burnt"),               /* newline */

ENUM_DEF_H(THING_ANIM_ENUM, ThingAnim)

//
// Thing event enum
//
#define THING_EVENT_ENUM(list_macro)                                                                                 \
  clang_format_indent()                                         /* dummy line for clang indentation fixup */         \
      list_macro(THING_EVENT_CRUSH, "crushing"),                /* newline */                                        \
      list_macro(THING_EVENT_FALL, "falling"),                  /* newline */                                        \
      list_macro(THING_EVENT_FIRE_DAMAGE, "burning"),           /* newline */                                        \
      list_macro(THING_EVENT_HEAT_DAMAGE, "scalding"),          /* newline */                                        \
      list_macro(THING_EVENT_LIFESPAN_EXPIRED, "life"),         /* newline */                                        \
      list_macro(THING_EVENT_MELEE_DAMAGE, "melee"),            /* newline */                                        \
      list_macro(THING_EVENT_OPEN, "open"),                     /* newline */                                        \
      list_macro(THING_EVENT_NONE, "none"),                     /* newline */                                        \
      list_macro(THING_EVENT_SHOVED, "shove"),                  /* newline */                                        \
      list_macro(THING_EVENT_WATER_DAMAGE, "water"),            /* newline */                                        \
      list_macro(THING_EVENT_EXPLOSION_DAMAGE, "explosion"),    /* newline */                                        \
      list_macro(THING_EVENT_CARRIED, "carried"),               /* newline */                                        \
      list_macro(THING_EVENT_CARRIED_MERGED, "carried-merged"), /* newline */

ENUM_DEF_H(THING_EVENT_ENUM, ThingEventType)

#define THING_EVENT_ENUM_FIRST ((ThingEventType) 0)

#define FOR_ALL_THING_EVENT(_iter_)                                                                                  \
  for (ThingEventType _iter_ = THING_EVENT_ENUM_FIRST; /* newline */                                                 \
       _iter_ < THING_EVENT_ENUM_MAX;                  /* newline */                                                 \
       _iter_ = static_cast< ThingEventType >(static_cast< int >(_iter_) + 1))

//
// Thing priority enum
//
#define THING_PRIORITY_ENUM(list_macro)                                                                              \
  clang_format_indent()                               /* dummy line for clang indentation fixup */                   \
      list_macro(THING_PRIORITY_EXPLOSION, "player"), /* newline */                                                  \
      list_macro(THING_PRIORITY_LAVA, "lava"),        /* newline */                                                  \
      list_macro(THING_PRIORITY_FIRE, "lava"),        /* newline */                                                  \
      list_macro(THING_PRIORITY_STEAM, "steam"),      /* newline */                                                  \
      list_macro(THING_PRIORITY_PLAYER, "player"),    /* newline */                                                  \
      list_macro(THING_PRIORITY_MOB, "mob"),          /* newline */                                                  \
      list_macro(THING_PRIORITY_MONST, "monst"),      /* newline */                                                  \
      list_macro(THING_PRIORITY_WATER, "water"),      /* newline */                                                  \
      list_macro(THING_PRIORITY_SMOKE, "smoke"),      /* newline */                                                  \
      list_macro(THING_PRIORITY_OBJECT, "object"),    /* newline */                                                  \
      list_macro(THING_PRIORITY_LOW, "low"),          /* newline */

ENUM_DEF_H(THING_PRIORITY_ENUM, ThingPriorityType)

//
// Thing chance enum
//
#define THING_CHANCE_ENUM(list_macro)                                                                                \
  clang_format_indent()                                  /* dummy line for clang indentation fixup */                \
      list_macro(THING_CHANCE_CONTINUE_TO_BURN, "burn"), /* newline */

ENUM_DEF_H(THING_CHANCE_ENUM, ThingChanceType)

//
// Thing rarity enum
//
#define THING_RARITY_ENUM(list_macro)                                                                                \
  clang_format_indent()                                /* dummy line for clang indentation fixup */                  \
      list_macro(THING_RARITY_COMMON, "common"),       /* newline */                                                 \
      list_macro(THING_RARITY_UNCOMMON, "uncommon"),   /* newline */                                                 \
      list_macro(THING_RARITY_RARE, "rare"),           /* newline */                                                 \
      list_macro(THING_RARITY_VERY_RARE, "very_rare"), /* newline */                                                 \
      list_macro(THING_RARITY_UNIQUE, "unique"),       /* newline */

ENUM_DEF_H(THING_RARITY_ENUM, ThingRarity)

//
// Thing dir enum
//
#define THING_DIR_ENUM(list_macro)                                                                                   \
  clang_format_indent()                               /* dummy line for clang indentation fixup */                   \
      list_macro(THING_DIR_NONE, "THING_DIR_NONE"),   /* newline */                                                  \
      list_macro(THING_DIR_DOWN, "THING_DIR_DOWN"),   /* newline */                                                  \
      list_macro(THING_DIR_UP, "THING_DIR_UP"),       /* newline */                                                  \
      list_macro(THING_DIR_LEFT, "THING_DIR_LEFT"),   /* newline */                                                  \
      list_macro(THING_DIR_RIGHT, "THING_DIR_RIGHT"), /* newline */                                                  \
      list_macro(THING_DIR_TL, "THING_DIR_TL"),       /* newline */                                                  \
      list_macro(THING_DIR_BL, "THING_DIR_BL"),       /* newline */                                                  \
      list_macro(THING_DIR_TR, "THING_DIR_TR"),       /* newline */                                                  \
      list_macro(THING_DIR_BR, "THING_DIR_BR"),       /* newline */

ENUM_DEF_H(THING_DIR_ENUM, ThingDir)

class Tp;

bool tp_init(void);

std::string tp_name(Tpp);

std::string tp_short_name(Tpp);
void        tp_short_name_set(Tpp, const std::string &);

std::string tp_long_name(Tpp);
void        tp_long_name_set(Tpp, const std::string &);

std::string tp_pluralize_name(Tpp);
void        tp_pluralize_name_set(Tpp, const std::string &);

std::string tp_apostrophize_name(Tpp);
void        tp_apostrophize_name_set(Tpp, const std::string &);

std::string tp_real_name(Tpp);
void        tp_real_name_set(Tpp, const std::string &);

void  tp_light_color_set(Tpp, const std::string &);
void  tp_light_color_apply(Tpp);
color tp_light_color(Tpp);

int   tp_tiles_size(Tpp, ThingAnim);
Tilep tp_first_tile(class Tp *, ThingAnim);
Tilep tp_tiles_get(Tpp, ThingAnim anim_type, int index);
void  tp_tiles_push_back(Tpp, ThingAnim, Tilep val);

void tp_damage_set(Tpp, ThingEventType, const std::string &);
int  tp_damage(Tpp, ThingEventType);

void tp_chance_set(Tpp, ThingChanceType, const std::string &);
int  tp_chance(Tpp, ThingChanceType);
bool tp_chance_success(Tpp, ThingChanceType);
bool tp_chance_fail(Tpp, ThingChanceType);

TpId tp_id_get(Tpp tp);
Tpp  tp_find(TpId id);
Tpp  tp_find_mand(const std::string &);
Tpp  tp_find_opt(const std::string &);

Tpp string2tp(const char **s, int *len = nullptr);
Tpp tp_load(const std::string &);
Tpp tp_random(ThingFlag);
Tpp tp_random_dungeon_entrance(void);
Tpp tp_random_exit(void);
Tpp tp_random_key(void);
Tpp tp_random_monst(int c);
Tpp tp_random_player(void);
Tpp tp_random_wall(void);

void TP_CON(Tpp, const char *fmt, ...) CHECK_FORMAT_STR(printf, 2, 3);
void TP_CON_(Tpp, const char *fmt, va_list args); // compile error without
void TP_DBG_(Tpp, const char *fmt, ...) CHECK_FORMAT_STR(printf, 2, 3);
void TP_DIE(Tpp, const char *fmt, ...) CHECK_FORMAT_STR(printf, 2, 3);
void TP_DIE_(Tpp, const char *fmt, va_list args); // compile error without
void TP_ERR(Tpp, const char *fmt, ...) CHECK_FORMAT_STR(printf, 2, 3);
void TP_ERR_(Tpp, const char *fmt, va_list args); // compile error without
void TP_LOG(Tpp, const char *fmt, ...) CHECK_FORMAT_STR(printf, 2, 3);
void TP_LOG_(Tpp, const char *fmt, va_list args); // compile error without
                                                  //
void tp_fini(void);
void tp_get_id(const char *, int *id);

int  tp_flag(Tpp, ThingFlag);
void tp_flag_set(Tpp, ThingFlag, int val = 1);

void    tp_z_depth_set(Tpp, MapZDepth val);
uint8_t tp_z_depth_get(Tpp tp);

void tp_speed_set(Tpp, int val);
int  tp_speed_get(Tpp tp);

#define ONE_KG          1000
#define WEIGHT_VVVHEAVY (ONE_KG * 1000)
#define WEIGHT_VVHEAVY  (ONE_KG * 500)
#define WEIGHT_VHEAVY   (ONE_KG * 200)
#define WEIGHT_HEAVY    (ONE_KG * 100)
#define WEIGHT_HUMAN    (ONE_KG * 50)
#define WEIGHT_MEDIUM   (ONE_KG * 10)
#define WEIGHT_LIGHT    (ONE_KG * 1)
#define WEIGHT_FEATHER  (1)
#define WEIGHT_NONE     (0)

void tp_weight_set(Tpp, int val);
int  tp_weight_get(Tpp tp);

void tp_health_set(Tpp, const std::string &val);
int  tp_health_get(Tpp tp);
int  tp_health_max_get(Tpp tp);

void tp_temperature_initial_set(Tpp, int val);
int  tp_temperature_initial_get(Tpp tp);

void tp_temperature_burns_at_set(Tpp, int val);
int  tp_temperature_burns_at_get(Tpp tp);

void tp_temperature_damage_at_set(Tpp, int val);
int  tp_temperature_damage_at_get(Tpp tp);

void tp_value1_set(Tpp, int val);
int  tp_value1_get(Tpp tp);

void tp_value2_set(Tpp, int val);
int  tp_value2_get(Tpp tp);

void tp_value3_set(Tpp, int val);
int  tp_value3_get(Tpp tp);

void tp_value4_set(Tpp, int val);
int  tp_value4_get(Tpp tp);

void tp_value5_set(Tpp, int val);
int  tp_value5_get(Tpp tp);

void tp_value6_set(Tpp, int val);
int  tp_value6_get(Tpp tp);

void tp_value7_set(Tpp, int val);
int  tp_value7_get(Tpp tp);

void tp_value8_set(Tpp, int val);
int  tp_value8_get(Tpp tp);

void tp_value9_set(Tpp, int val);
int  tp_value9_get(Tpp tp);

void tp_value10_set(Tpp, int val);
int  tp_value10_get(Tpp tp);

void tp_value11_set(Tpp, int val);
int  tp_value11_get(Tpp tp);

void tp_value12_set(Tpp, int val);
int  tp_value12_get(Tpp tp);

void tp_value13_set(Tpp, int val);
int  tp_value13_get(Tpp tp);

void tp_value14_set(Tpp, int val);
int  tp_value14_get(Tpp tp);

void tp_value15_set(Tpp, int val);
int  tp_value15_get(Tpp tp);

void tp_value16_set(Tpp, int val);
int  tp_value16_get(Tpp tp);

void tp_value17_set(Tpp, int val);
int  tp_value17_get(Tpp tp);

void tp_value18_set(Tpp, int val);
int  tp_value18_get(Tpp tp);

void tp_value19_set(Tpp, int val);
int  tp_value19_get(Tpp tp);

void tp_value20_set(Tpp, int val);
int  tp_value20_get(Tpp tp);

void tp_value21_set(Tpp, int val);
int  tp_value21_get(Tpp tp);

void tp_value22_set(Tpp, int val);
int  tp_value22_get(Tpp tp);

void tp_value23_set(Tpp, int val);
int  tp_value23_get(Tpp tp);

void tp_value24_set(Tpp, int val);
int  tp_value24_get(Tpp tp);

void tp_value25_set(Tpp, int val);
int  tp_value25_get(Tpp tp);

void tp_value26_set(Tpp, int val);
int  tp_value26_get(Tpp tp);

void              tp_priority_set(Tpp, ThingPriorityType val);
ThingPriorityType tp_priority_get(Tpp tp);

void tp_vision_distance_set(Tpp, int val);
int  tp_vision_distance_get(Tpp tp);

void tp_jump_distance_set(Tpp, int val);
int  tp_jump_distance_get(Tpp tp);

void tp_lifespan_set(Tpp, const std::string &val);
int  tp_lifespan_get(Tpp tp);
int  tp_lifespan_max_get(Tpp tp);

void tp_is_immunity_add(Tpp, ThingEventType);
bool tp_is_immune_to(Tpp, ThingEventType);

void tp_monst_group_add(Tpp tp, ThingMonstGroup);

// begin sort marker1 {
#define tp_is_able_to_collect_items(tp) tp_flag(tp, is_able_to_collect_items)
#define tp_is_able_to_collect_keys(tp)  tp_flag(tp, is_able_to_collect_keys)
#define tp_is_able_to_crush_grass(tp)   tp_flag(tp, is_able_to_crush_grass)
#define tp_is_able_to_fall(tp)          tp_flag(tp, is_able_to_fall)
#define tp_is_able_to_jump(tp)          tp_flag(tp, is_able_to_jump)
#define tp_is_able_to_open(tp)          tp_flag(tp, is_able_to_open)
#define tp_is_able_to_shove(tp)         tp_flag(tp, is_able_to_shove)
#define tp_is_animated_can_hflip(tp)    tp_flag(tp, is_animated_can_hflip)
#define tp_is_animated_no_dir(tp)       tp_flag(tp, is_animated_no_dir)
#define tp_is_animated_sync_first(tp)   tp_flag(tp, is_animated_sync_first)
#define tp_is_animated(tp)              tp_flag(tp, is_animated)
#define tp_is_barrel(tp)                tp_flag(tp, is_barrel)
#define tp_is_blit_centered(tp)         tp_flag(tp, is_blit_centered)
#define tp_is_blit_colored_always(tp)   tp_flag(tp, is_blit_colored_always)
#define tp_is_blit_if_has_seen(tp)      tp_flag(tp, is_blit_if_has_seen)
#define tp_is_blit_on_ground(tp)        tp_flag(tp, is_blit_on_ground)
#define tp_is_blit_outlined(tp)         tp_flag(tp, is_blit_outlined)
#define tp_is_blit_square_outlined(tp)  tp_flag(tp, is_blit_square_outlined)
#define tp_is_brazier(tp)               tp_flag(tp, is_brazier)
#define tp_is_bridge(tp)                tp_flag(tp, is_bridge)
#define tp_is_broken_on_death(tp)       tp_flag(tp, is_broken_on_death)
#define tp_is_burnable(tp)              tp_flag(tp, is_burnable)
#define tp_is_chasm(tp)                 tp_flag(tp, is_chasm)
#define tp_is_collectable(tp)           tp_flag(tp, is_collectable)
#define tp_is_combustible(tp)           tp_flag(tp, is_combustible)
#define tp_is_corpse_on_death(tp)       tp_flag(tp, is_corpse_on_death)
#define tp_is_corridor(tp)              tp_flag(tp, is_corridor)
#define tp_is_crushable(tp)             tp_flag(tp, is_crushable)
#define tp_is_cursor_hazard(tp)         tp_flag(tp, is_cursor_hazard)
#define tp_is_cursor_path_hazard(tp)    tp_flag(tp, is_cursor_path_hazard)
#define tp_is_cursor_path_none(tp)      tp_flag(tp, is_cursor_path_none)
#define tp_is_cursor_path(tp)           tp_flag(tp, is_cursor_path)
#define tp_is_cursor(tp)                tp_flag(tp, is_cursor)
#define tp_is_damage_capped(tp)         tp_flag(tp, is_damage_capped)
#define tp_is_dead_on_shoving(tp)       tp_flag(tp, is_dead_on_shoving)
#define tp_is_deep_water(tp)            tp_flag(tp, is_deep_water)
#define tp_is_described_cursor(tp)      tp_flag(tp, is_described_cursor)
#define tp_is_dirt(tp)                  tp_flag(tp, is_dirt)
#define tp_is_door_locked(tp)           tp_flag(tp, is_door_locked)
#define tp_is_door_secret(tp)           tp_flag(tp, is_door_secret)
#define tp_is_door_unlocked(tp)         tp_flag(tp, is_door_unlocked)
#define tp_is_dungeon_entrance(tp)      tp_flag(tp, is_dungeon_entrance)
#define tp_is_entrance(tp)              tp_flag(tp, is_entrance)
#define tp_is_ethereal(tp)              tp_flag(tp, is_ethereal)
#define tp_is_exit(tp)                  tp_flag(tp, is_exit)
#define tp_is_explosion(tp)             tp_flag(tp, is_explosion)
#define tp_is_extinguished_on_death(tp) tp_flag(tp, is_extinguished_on_death)
#define tp_is_fire(tp)                  tp_flag(tp, is_fire)
#define tp_is_floating(tp)              tp_flag(tp, is_floating)
#define tp_is_floor(tp)                 tp_flag(tp, is_floor)
#define tp_is_flying(tp)                tp_flag(tp, is_flying)
#define tp_is_foliage(tp)               tp_flag(tp, is_foliage)
#define tp_is_gaseous(tp)               tp_flag(tp, is_gaseous)
#define tp_is_ghost(tp)                 tp_flag(tp, is_ghost)
#define tp_is_grass(tp)                 tp_flag(tp, is_grass)
#define tp_is_health_bar_shown(tp)      tp_flag(tp, is_health_bar_shown)
#define tp_is_indestructible(tp)        tp_flag(tp, is_indestructible)
#define tp_is_inventory_item(tp)        tp_flag(tp, is_inventory_item)
#define tp_is_item_droppable(tp)        tp_flag(tp, is_item_droppable)
#define tp_is_item_equipable(tp)        tp_flag(tp, is_item_equipable)
#define tp_is_item_mergeable(tp)        tp_flag(tp, is_item_mergeable)
#define tp_is_item(tp)                  tp_flag(tp, is_item)
#define tp_is_key(tp)                   tp_flag(tp, is_key)
#define tp_is_kobalos(tp)               tp_flag(tp, is_kobalos)
#define tp_is_lava(tp)                  tp_flag(tp, is_lava)
#define tp_is_level_across(tp)          tp_flag(tp, is_level_across)
#define tp_is_level_curr(tp)            tp_flag(tp, is_level_curr)
#define tp_is_level_down(tp)            tp_flag(tp, is_level_down)
#define tp_is_level_final(tp)           tp_flag(tp, is_level_final)
#define tp_is_level_next(tp)            tp_flag(tp, is_level_next)
#define tp_is_level_not_visited(tp)     tp_flag(tp, is_level_not_visited)
#define tp_is_level_visited(tp)         tp_flag(tp, is_level_visited)
#define tp_is_levitating(tp)            tp_flag(tp, is_levitating)
#define tp_is_light_source(tp)          tp_flag(tp, is_light_source)
#define tp_is_loggable(tp)              tp_flag(tp, is_loggable)
#define tp_is_minion(tp)                tp_flag(tp, is_minion)
#define tp_is_mob(tp)                   tp_flag(tp, is_mob)
#define tp_is_mob1(tp)                  tp_flag(tp, is_mob1)
#define tp_is_mob2(tp)                  tp_flag(tp, is_mob2)
#define tp_is_monst_group_easy(tp)      tp_flag(tp, is_monst_group_easy)
#define tp_is_monst_group_hard(tp)      tp_flag(tp, is_monst_group_hard)
#define tp_is_monst_group_mob(tp)       tp_flag(tp, is_monst_group_mob)
#define tp_is_monst(tp)                 tp_flag(tp, is_monst)
#define tp_is_needs_move_confirm(tp)    tp_flag(tp, is_needs_move_confirm)
#define tp_is_obs_to_cursor_path(tp)    tp_flag(tp, is_obs_to_cursor_path)
#define tp_is_obs_to_explosion(tp)      tp_flag(tp, is_obs_to_explosion)
#define tp_is_obs_to_falling_onto(tp)   tp_flag(tp, is_obs_to_falling_onto)
#define tp_is_obs_to_fire(tp)           tp_flag(tp, is_obs_to_fire)
#define tp_is_obs_to_jump_over(tp)      tp_flag(tp, is_obs_to_jump_over)
#define tp_is_obs_to_jumping_onto(tp)   tp_flag(tp, is_obs_to_jumping_onto)
#define tp_is_obs_to_movement(tp)       tp_flag(tp, is_obs_to_movement)
#define tp_is_obs_to_vision(tp)         tp_flag(tp, is_obs_to_vision)
#define tp_is_openable(tp)              tp_flag(tp, is_openable)
#define tp_is_physics_explosion(tp)     tp_flag(tp, is_physics_explosion)
#define tp_is_physics_temperature(tp)   tp_flag(tp, is_physics_temperature)
#define tp_is_physics_water(tp)         tp_flag(tp, is_physics_water)
#define tp_is_pillar(tp)                tp_flag(tp, is_pillar)
#define tp_is_player(tp)                tp_flag(tp, is_player)
#define tp_is_rock(tp)                  tp_flag(tp, is_rock)
#define tp_is_shovable(tp)              tp_flag(tp, is_shovable)
#define tp_is_slime(tp)                 tp_flag(tp, is_slime)
#define tp_is_smoke(tp)                 tp_flag(tp, is_smoke)
#define tp_is_steam(tp)                 tp_flag(tp, is_steam)
#define tp_is_submergible(tp)           tp_flag(tp, is_submergible)
#define tp_is_teleport_blocked(tp)      tp_flag(tp, is_teleport_blocked)
#define tp_is_teleport(tp)              tp_flag(tp, is_teleport)
#define tp_is_tick_delay_on_spawn(tp)   tp_flag(tp, is_tick_delay_on_spawn)
#define tp_is_tickable(tp)              tp_flag(tp, is_tickable)
#define tp_is_tiled(tp)                 tp_flag(tp, is_tiled)
#define tp_is_trap(tp)                  tp_flag(tp, is_trap)
#define tp_is_treasure(tp)              tp_flag(tp, is_treasure)
#define tp_is_undead(tp)                tp_flag(tp, is_undead)
#define tp_is_unused1(tp)               tp_flag(tp, is_unused1)
#define tp_is_unused2(tp)               tp_flag(tp, is_unused2)
#define tp_is_unused3(tp)               tp_flag(tp, is_unused3)
#define tp_is_unused4(tp)               tp_flag(tp, is_unused4)
#define tp_is_wait_on_dead_anim(tp)     tp_flag(tp, is_wait_on_dead_anim)
#define tp_is_walk_through_walls(tp)    tp_flag(tp, is_walk_through_walls)
#define tp_is_wall(tp)                  tp_flag(tp, is_wall)
#define tp_is_water(tp)                 tp_flag(tp, is_water)
// end sort marker1 }

// begin sort marker2 {
#define level_afirst_is_able_to_collect_items(g, v, l, p) level_afirst_flag(g, v, l, is_able_to_collect_items, p)
#define level_afirst_is_able_to_collect_keys(g, v, l, p)  level_afirst_flag(g, v, l, is_able_to_collect_keys, p)
#define level_afirst_is_able_to_crush_grass(g, v, l, p)   level_afirst_flag(g, v, l, is_able_to_crush_grass, p)
#define level_afirst_is_able_to_jump(g, v, l, p)          level_afirst_flag(g, v, l, is_able_to_jump, p)
#define level_afirst_is_able_to_open(g, v, l, p)          level_afirst_flag(g, v, l, is_able_to_open, p)
#define level_afirst_is_able_to_shove(g, v, l, p)         level_afirst_flag(g, v, l, is_able_to_shove, p)
#define level_afirst_is_animated_can_hflip(g, v, l, p)    level_afirst_flag(g, v, l, is_animated_can_hflip, p)
#define level_afirst_is_animated_no_dir(g, v, l, p)       level_afirst_flag(g, v, l, is_animated_no_dir, p)
#define level_afirst_is_animated(g, v, l, p)              level_afirst_flag(g, v, l, is_animated, p)
#define level_afirst_is_barrel(g, v, l, p)                level_afirst_flag(g, v, l, is_barrel, p)
#define level_afirst_is_blit_colored_always(g, v, l, p)   level_afirst_flag(g, v, l, is_blit_colored_always, p)
#define level_afirst_is_blit_if_has_seen(g, v, l, p)      level_afirst_flag(g, v, l, is_blit_if_has_seen, p)
#define level_afirst_is_brazier(g, v, l, p)               level_afirst_flag(g, v, l, is_brazier, p)
#define level_afirst_is_bridge(g, v, l, p)                level_afirst_flag(g, v, l, is_bridge, p)
#define level_afirst_is_broken_on_death(g, v, l, p)       level_afirst_flag(g, v, l, is_broken_on_death, p)
#define level_afirst_is_burnable(g, v, l, p)              level_afirst_flag(g, v, l, is_burnable, p)
#define level_afirst_is_chasm(g, v, l, p)                 level_afirst_flag(g, v, l, is_chasm, p)
#define level_afirst_is_collectable(g, v, l, p)           level_afirst_flag(g, v, l, is_collectable, p)
#define level_afirst_is_combustible(g, v, l, p)           level_afirst_flag(g, v, l, is_combustible, p)
#define level_afirst_is_corpse_on_death(g, v, l, p)       level_afirst_flag(g, v, l, is_corpse_on_death, p)
#define level_afirst_is_corridor(g, v, l, p)              level_afirst_flag(g, v, l, is_corridor, p)
#define level_afirst_is_crushable_underfoot(g, v, l, p)   level_afirst_flag(g, v, l, is_crushable, p)
#define level_afirst_is_cursor_hazard(g, v, l, p)         level_afirst_flag(g, v, l, is_cursor_hazard, p)
#define level_afirst_is_cursor_path_hazard(g, v, l, p)    level_afirst_flag(g, v, l, is_cursor_path_hazard, p)
#define level_afirst_is_cursor_path_none(g, v, l, p)      level_afirst_flag(g, v, l, is_cursor_path_none, p)
#define level_afirst_is_cursor_path(g, v, l, p)           level_afirst_flag(g, v, l, is_cursor_path, p)
#define level_afirst_is_cursor(g, v, l, p)                level_afirst_flag(g, v, l, is_cursor, p)
#define level_afirst_is_damage_capped(g, v, l, p)         level_afirst_flag(g, v, l, is_damage_capped, p)
#define level_afirst_is_dead_on_shoving(g, v, l, p)       level_afirst_flag(g, v, l, is_dead_on_shoving, p)
#define level_afirst_is_deep_water(g, v, l, p)            level_afirst_flag(g, v, l, is_deep_water, p)
#define level_afirst_is_described_cursor(g, v, l, p)      level_afirst_flag(g, v, l, is_described_cursor, p)
#define level_afirst_is_dirt(g, v, l, p)                  level_afirst_flag(g, v, l, is_dirt, p)
#define level_afirst_is_door_locked(g, v, l, p)           level_afirst_flag(g, v, l, is_door_locked, p)
#define level_afirst_is_door_secret(g, v, l, p)           level_afirst_flag(g, v, l, is_door_secret, p)
#define level_afirst_is_door_unlocked(g, v, l, p)         level_afirst_flag(g, v, l, is_door_unlocked, p)
#define level_afirst_is_dungeon_entrance(g, v, l, p)      level_afirst_flag(g, v, l, is_dungeon_entrance, p)
#define level_afirst_is_entrance(g, v, l, p)              level_afirst_flag(g, v, l, is_entrance, p)
#define level_afirst_is_ethereal(g, v, l, p)              level_afirst_flag(g, v, l, is_ethereal, p)
#define level_afirst_is_exit(g, v, l, p)                  level_afirst_flag(g, v, l, is_exit, p)
#define level_afirst_is_explosion(g, v, l, p)             level_afirst_flag(g, v, l, is_explosion, p)
#define level_afirst_is_extinguished_on_death(g, v, l, p) level_afirst_flag(g, v, l, is_extinguished_on_death, p)
#define level_afirst_is_fire(g, v, l, p)                  level_afirst_flag(g, v, l, is_fire, p)
#define level_afirst_is_floor(g, v, l, p)                 level_afirst_flag(g, v, l, is_floor, p)
#define level_afirst_is_flying(g, v, l, p)                level_afirst_flag(g, v, l, is_flying, p)
#define level_afirst_is_foliage(g, v, l, p)               level_afirst_flag(g, v, l, is_foliage, p)
#define level_afirst_is_gaseous(g, v, l, p)               level_afirst_flag(g, v, l, is_gaseous, p)
#define level_afirst_is_ghost(g, v, l, p)                 level_afirst_flag(g, v, l, is_ghost, p)
#define level_afirst_is_grass(g, v, l, p)                 level_afirst_flag(g, v, l, is_grass, p)
#define level_afirst_is_health_bar_shown(g, v, l, p)      level_afirst_flag(g, v, l, is_health_bar_shown, p)
#define level_afirst_is_inventory_item(g, v, l, p)        level_afirst_flag(g, v, l, is_inventory_item, p)
#define level_afirst_is_item_droppable(g, v, l, p)        level_afirst_flag(g, v, l, is_item_droppable, p)
#define level_afirst_is_item_equipable(g, v, l, p)        level_afirst_flag(g, v, l, is_item_equipable, p)
#define level_afirst_is_item_mergeable(g, v, l, p)        level_afirst_flag(g, v, l, is_item_mergeable, p)
#define level_afirst_is_item(g, v, l, p)                  level_afirst_flag(g, v, l, is_item, p)
#define level_afirst_is_key(g, v, l, p)                   level_afirst_flag(g, v, l, is_key, p)
#define level_afirst_is_kobalos(g, v, l, p)               level_afirst_flag(g, v, l, is_kobalos, p)
#define level_afirst_is_lava(g, v, l, p)                  level_afirst_flag(g, v, l, is_lava, p)
#define level_afirst_is_level_across(g, v, l, p)          level_afirst_flag(g, v, l, is_level_across, p)
#define level_afirst_is_level_curr(g, v, l, p)            level_afirst_flag(g, v, l, is_level_curr, p)
#define level_afirst_is_level_down(g, v, l, p)            level_afirst_flag(g, v, l, is_level_down, p)
#define level_afirst_is_level_final(g, v, l, p)           level_afirst_flag(g, v, l, is_level_final, p)
#define level_afirst_is_level_next(g, v, l, p)            level_afirst_flag(g, v, l, is_level_next, p)
#define level_afirst_is_level_not_visited(g, v, l, p)     level_afirst_flag(g, v, l, is_level_not_visited, p)
#define level_afirst_is_level_visited(g, v, l, p)         level_afirst_flag(g, v, l, is_level_visited, p)
#define level_afirst_is_levitating(g, v, l, p)            level_afirst_flag(g, v, l, is_levitating, p)
#define level_afirst_is_light_source(g, v, l, p)          level_afirst_flag(g, v, l, is_light_source, p)
#define level_afirst_is_loggable(g, v, l, p)              level_afirst_flag(g, v, l, is_loggable, p)
#define level_afirst_is_minion(g, v, l, p)                level_afirst_flag(g, v, l, is_minion, p)
#define level_afirst_is_mob(g, v, l, p)                   level_afirst_flag(g, v, l, is_mob, p)
#define level_afirst_is_mob1(g, v, l, p)                  level_afirst_flag(g, v, l, is_mob1, p)
#define level_afirst_is_mob2(g, v, l, p)                  level_afirst_flag(g, v, l, is_mob2, p)
#define level_afirst_is_monst_group_easy(g, v, l, p)      level_afirst_flag(g, v, l, is_monst_group_easy, p)
#define level_afirst_is_monst_group_hard(g, v, l, p)      level_afirst_flag(g, v, l, is_monst_group_hard, p)
#define level_afirst_is_monst_group_mob(g, v, l, p)       level_afirst_flag(g, v, l, is_monst_group_mob, p)
#define level_afirst_is_monst(g, v, l, p)                 level_afirst_flag(g, v, l, is_monst, p)
#define level_afirst_is_needs_move_confirm(g, v, l, p)    level_afirst_flag(g, v, l, is_submergible, p)
#define level_afirst_is_obs_block(g, v, l, p)             level_afirst_flag(g, v, l, is_obs_to_movement, p)
#define level_afirst_is_obs_to_cursor_path(g, v, l, p)    level_afirst_flag(g, v, l, is_obs_to_cursor_path, p)
#define level_afirst_is_obs_to_explosion(g, v, l, p)      level_afirst_flag(g, v, l, is_obs_to_explosion, p)
#define level_afirst_is_obs_to_jump_over(g, v, l, p)      level_afirst_flag(g, v, l, is_obs_to_jump_over, p)
#define level_afirst_is_obs_to_vision(g, v, l, p)         level_afirst_flag(g, v, l, is_obs_to_vision, p)
#define level_afirst_is_openable(g, v, l, p)              level_afirst_flag(g, v, l, is_openable, p)
#define level_afirst_is_physics_explosion(g, v, l, p)     level_afirst_flag(g, v, l, is_physics_explosion, p)
#define level_afirst_is_physics_temperature(g, v, l, p)   level_afirst_flag(g, v, l, is_physics_temperature, p)
#define level_afirst_is_pillar(g, v, l, p)                level_afirst_flag(g, v, l, is_pillar, p)
#define level_afirst_is_player(g, v, l, p)                level_afirst_flag(g, v, l, is_player, p)
#define level_afirst_is_rock(g, v, l, p)                  level_afirst_flag(g, v, l, is_rock, p)
#define level_afirst_is_shovable(g, v, l, p)              level_afirst_flag(g, v, l, is_shovable, p)
#define level_afirst_is_slime(g, v, l, p)                 level_afirst_flag(g, v, l, is_slime, p)
#define level_afirst_is_smoke(g, v, l, p)                 level_afirst_flag(g, v, l, is_smoke, p)
#define level_afirst_is_steam(g, v, l, p)                 level_afirst_flag(g, v, l, is_steam, p)
#define level_afirst_is_teleport_blocked(g, v, l, p)      level_afirst_flag(g, v, l, is_teleport_blocked, p)
#define level_afirst_is_teleport(g, v, l, p)              level_afirst_flag(g, v, l, is_teleport, p)
#define level_afirst_is_tick_delay_on_spawn(g, v, l, p)   level_afirst_flag(g, v, l, is_tick_delay_on_spawn, p)
#define level_afirst_is_tickable(g, v, l, p)              level_afirst_flag(g, v, l, is_tickable, p)
#define level_afirst_is_tiled(g, v, l, p)                 level_afirst_flag(g, v, l, is_tiled, p)
#define level_afirst_is_trap(g, v, l, p)                  level_afirst_flag(g, v, l, is_trap, p)
#define level_afirst_is_treasure(g, v, l, p)              level_afirst_flag(g, v, l, is_treasure, p)
#define level_afirst_is_undead(g, v, l, p)                level_afirst_flag(g, v, l, is_undead, p)
#define level_afirst_is_unused1(g, v, l, p)               level_afirst_flag(g, v, l, is_unused1, p)
#define level_afirst_is_unused2(g, v, l, p)               level_afirst_flag(g, v, l, is_unused2, p)
#define level_afirst_is_unused3(g, v, l, p)               level_afirst_flag(g, v, l, is_unused3, p)
#define level_afirst_is_unused34(g, v, l, p)              level_afirst_flag(g, v, l, is_able_to_fall, p)
#define level_afirst_is_unused35(g, v, l, p)              level_afirst_flag(g, v, l, is_physics_water, p)
#define level_afirst_is_unused36(g, v, l, p)              level_afirst_flag(g, v, l, is_indestructible, p)
#define level_afirst_is_unused37(g, v, l, p)              level_afirst_flag(g, v, l, is_floating, p)
#define level_afirst_is_unused38(g, v, l, p)              level_afirst_flag(g, v, l, is_obs_to_fire, p)
#define level_afirst_is_unused4(g, v, l, p)               level_afirst_flag(g, v, l, is_unused4, p)
#define level_afirst_is_wait_on_dead_anim(g, v, l, p)     level_afirst_flag(g, v, l, is_wait_on_dead_anim, p)
#define level_afirst_is_walk_through_walls(g, v, l, p)    level_afirst_flag(g, v, l, is_walk_through_walls, p)
#define level_afirst_is_wall(g, v, l, p)                  level_afirst_flag(g, v, l, is_wall, p)
#define level_afirst_is_water(g, v, l, p)                 level_afirst_flag(g, v, l, is_water, p)
#define level_alive_is_able_to_collect_items(g, v, l, p)  level_alive_flag(g, v, l, is_able_to_collect_items, p)
#define level_alive_is_able_to_collect_keys(g, v, l, p)   level_alive_flag(g, v, l, is_able_to_collect_keys, p)
#define level_alive_is_able_to_crush_grass(g, v, l, p)    level_alive_flag(g, v, l, is_able_to_crush_grass, p)
#define level_alive_is_able_to_jump(g, v, l, p)           level_alive_flag(g, v, l, is_able_to_jump, p)
#define level_alive_is_able_to_open(g, v, l, p)           level_alive_flag(g, v, l, is_able_to_open, p)
#define level_alive_is_able_to_shove(g, v, l, p)          level_alive_flag(g, v, l, is_able_to_shove, p)
#define level_alive_is_animated_can_hflip(g, v, l, p)     level_alive_flag(g, v, l, is_animated_can_hflip, p)
#define level_alive_is_animated_no_dir(g, v, l, p)        level_alive_flag(g, v, l, is_animated_no_dir, p)
#define level_alive_is_animated_sync_first(g, v, l, p)    level_alive_flag(g, v, l, is_animated_sync_first, p)
#define level_alive_is_animated(g, v, l, p)               level_alive_flag(g, v, l, is_animated, p)
#define level_alive_is_barrel(g, v, l, p)                 level_alive_flag(g, v, l, is_barrel, p)
#define level_alive_is_blit_colored_always(g, v, l, p)    level_alive_flag(g, v, l, is_blit_colored_always, p)
#define level_alive_is_blit_if_has_seen(g, v, l, p)       level_alive_flag(g, v, l, is_blit_if_has_seen, p)
#define level_alive_is_brazier(g, v, l, p)                level_alive_flag(g, v, l, is_brazier, p)
#define level_alive_is_bridge(g, v, l, p)                 level_alive_flag(g, v, l, is_bridge, p)
#define level_alive_is_broken_on_death(g, v, l, p)        level_alive_flag(g, v, l, is_broken_on_death, p)
#define level_alive_is_burnable(g, v, l, p)               level_alive_flag(g, v, l, is_burnable, p)
#define level_alive_is_chasm(g, v, l, p)                  level_alive_flag(g, v, l, is_chasm, p)
#define level_alive_is_collectable(g, v, l, p)            level_alive_flag(g, v, l, is_collectable, p)
#define level_alive_is_combustible(g, v, l, p)            level_alive_flag(g, v, l, is_combustible, p)
#define level_alive_is_corpse_on_death(g, v, l, p)        level_alive_flag(g, v, l, is_corpse_on_death, p)
#define level_alive_is_corridor(g, v, l, p)               level_alive_flag(g, v, l, is_corridor, p)
#define level_alive_is_crushable_underfoot(g, v, l, p)    level_alive_flag(g, v, l, is_crushable, p)
#define level_alive_is_cursor_hazard(g, v, l, p)          level_alive_flag(g, v, l, is_cursor_hazard, p)
#define level_alive_is_cursor_path_hazard(g, v, l, p)     level_alive_flag(g, v, l, is_cursor_path_hazard, p)
#define level_alive_is_cursor_path_none(g, v, l, p)       level_alive_flag(g, v, l, is_cursor_path_none, p)
#define level_alive_is_cursor_path(g, v, l, p)            level_alive_flag(g, v, l, is_cursor_path, p)
#define level_alive_is_cursor(g, v, l, p)                 level_alive_flag(g, v, l, is_cursor, p)
#define level_alive_is_damage_capped(g, v, l, p)          level_alive_flag(g, v, l, is_damage_capped, p)
#define level_alive_is_dead_on_shoving(g, v, l, p)        level_alive_flag(g, v, l, is_dead_on_shoving, p)
#define level_alive_is_deep_water(g, v, l, p)             level_alive_flag(g, v, l, is_deep_water, p)
#define level_alive_is_described_cursor(g, v, l, p)       level_alive_flag(g, v, l, is_described_cursor, p)
#define level_alive_is_dirt(g, v, l, p)                   level_alive_flag(g, v, l, is_dirt, p)
#define level_alive_is_door_locked(g, v, l, p)            level_alive_flag(g, v, l, is_door_locked, p)
#define level_alive_is_door_secret(g, v, l, p)            level_alive_flag(g, v, l, is_door_secret, p)
#define level_alive_is_door_unlocked(g, v, l, p)          level_alive_flag(g, v, l, is_door_unlocked, p)
#define level_alive_is_dungeon_entrance(g, v, l, p)       level_alive_flag(g, v, l, is_dungeon_entrance, p)
#define level_alive_is_entrance(g, v, l, p)               level_alive_flag(g, v, l, is_entrance, p)
#define level_alive_is_ethereal(g, v, l, p)               level_alive_flag(g, v, l, is_ethereal, p)
#define level_alive_is_exit(g, v, l, p)                   level_alive_flag(g, v, l, is_exit, p)
#define level_alive_is_explosion(g, v, l, p)              level_alive_flag(g, v, l, is_explosion, p)
#define level_alive_is_extinguished_on_death(g, v, l, p)  level_alive_flag(g, v, l, is_extinguished_on_death, p)
#define level_alive_is_fire(g, v, l, p)                   level_alive_flag(g, v, l, is_fire, p)
#define level_alive_is_floor(g, v, l, p)                  level_alive_flag(g, v, l, is_floor, p)
#define level_alive_is_flying(g, v, l, p)                 level_alive_flag(g, v, l, is_flying, p)
#define level_alive_is_foliage(g, v, l, p)                level_alive_flag(g, v, l, is_foliage, p)
#define level_alive_is_gaseous(g, v, l, p)                level_alive_flag(g, v, l, is_gaseous, p)
#define level_alive_is_ghost(g, v, l, p)                  level_alive_flag(g, v, l, is_ghost, p)
#define level_alive_is_grass(g, v, l, p)                  level_alive_flag(g, v, l, is_grass, p)
#define level_alive_is_health_bar_shown(g, v, l, p)       level_alive_flag(g, v, l, is_health_bar_shown, p)
#define level_alive_is_inventory_item(g, v, l, p)         level_alive_flag(g, v, l, is_inventory_item, p)
#define level_alive_is_item_droppable(g, v, l, p)         level_alive_flag(g, v, l, is_item_droppable, p)
#define level_alive_is_item_equipable(g, v, l, p)         level_alive_flag(g, v, l, is_item_equipable, p)
#define level_alive_is_item_mergeable(g, v, l, p)         level_alive_flag(g, v, l, is_item_mergeable, p)
#define level_alive_is_item(g, v, l, p)                   level_alive_flag(g, v, l, is_item, p)
#define level_alive_is_key(g, v, l, p)                    level_alive_flag(g, v, l, is_key, p)
#define level_alive_is_kobalos(g, v, l, p)                level_alive_flag(g, v, l, is_kobalos, p)
#define level_alive_is_lava(g, v, l, p)                   level_alive_flag(g, v, l, is_lava, p)
#define level_alive_is_level_across(g, v, l, p)           level_alive_flag(g, v, l, is_level_across, p)
#define level_alive_is_level_curr(g, v, l, p)             level_alive_flag(g, v, l, is_level_curr, p)
#define level_alive_is_level_down(g, v, l, p)             level_alive_flag(g, v, l, is_level_down, p)
#define level_alive_is_level_final(g, v, l, p)            level_alive_flag(g, v, l, is_level_final, p)
#define level_alive_is_level_next(g, v, l, p)             level_alive_flag(g, v, l, is_level_next, p)
#define level_alive_is_level_not_visited(g, v, l, p)      level_alive_flag(g, v, l, is_level_not_visited, p)
#define level_alive_is_level_visited(g, v, l, p)          level_alive_flag(g, v, l, is_level_visited, p)
#define level_alive_is_levitating(g, v, l, p)             level_alive_flag(g, v, l, is_levitating, p)
#define level_alive_is_light_source(g, v, l, p)           level_alive_flag(g, v, l, is_light_source, p)
#define level_alive_is_loggable(g, v, l, p)               level_alive_flag(g, v, l, is_loggable, p)
#define level_alive_is_minion(g, v, l, p)                 level_alive_flag(g, v, l, is_minion, p)
#define level_alive_is_mob(g, v, l, p)                    level_alive_flag(g, v, l, is_mob, p)
#define level_alive_is_mob1(g, v, l, p)                   level_alive_flag(g, v, l, is_mob1, p)
#define level_alive_is_mob2(g, v, l, p)                   level_alive_flag(g, v, l, is_mob2, p)
#define level_alive_is_monst_group_easy(g, v, l, p)       level_alive_flag(g, v, l, is_monst_group_easy, p)
#define level_alive_is_monst_group_hard(g, v, l, p)       level_alive_flag(g, v, l, is_monst_group_hard, p)
#define level_alive_is_monst_group_mob(g, v, l, p)        level_alive_flag(g, v, l, is_monst_group_mob, p)
#define level_alive_is_monst(g, v, l, p)                  level_alive_flag(g, v, l, is_monst, p)
#define level_alive_is_needs_move_confirm(g, v, l, p)     level_alive_flag(g, v, l, is_needs_move_confirm, p)
#define level_alive_is_obs_block(g, v, l, p)              level_alive_flag(g, v, l, is_obs_to_movement, p)
#define level_alive_is_obs_to_cursor_path(g, v, l, p)     level_alive_flag(g, v, l, is_obs_to_cursor_path, p)
#define level_alive_is_obs_to_explosion(g, v, l, p)       level_alive_flag(g, v, l, is_obs_to_explosion, p)
#define level_alive_is_obs_to_jump_over(g, v, l, p)       level_alive_flag(g, v, l, is_obs_to_jump_over, p)
#define level_alive_is_obs_to_vision(g, v, l, p)          level_alive_flag(g, v, l, is_obs_to_vision, p)
#define level_alive_is_openable(g, v, l, p)               level_alive_flag(g, v, l, is_openable, p)
#define level_alive_is_physics_explosion(g, v, l, p)      level_alive_flag(g, v, l, is_physics_explosion, p)
#define level_alive_is_physics_temperature(g, v, l, p)    level_alive_flag(g, v, l, is_physics_temperature, p)
#define level_alive_is_pillar(g, v, l, p)                 level_alive_flag(g, v, l, is_pillar, p)
#define level_alive_is_player(g, v, l, p)                 level_alive_flag(g, v, l, is_player, p)
#define level_alive_is_rock(g, v, l, p)                   level_alive_flag(g, v, l, is_rock, p)
#define level_alive_is_shovable(g, v, l, p)               level_alive_flag(g, v, l, is_shovable, p)
#define level_alive_is_slime(g, v, l, p)                  level_alive_flag(g, v, l, is_slime, p)
#define level_alive_is_smoke(g, v, l, p)                  level_alive_flag(g, v, l, is_smoke, p)
#define level_alive_is_steam(g, v, l, p)                  level_alive_flag(g, v, l, is_steam, p)
#define level_alive_is_teleport_blocked(g, v, l, p)       level_alive_flag(g, v, l, is_teleport_blocked, p)
#define level_alive_is_teleport(g, v, l, p)               level_alive_flag(g, v, l, is_teleport, p)
#define level_alive_is_tick_delay_on_spawn(g, v, l, p)    level_alive_flag(g, v, l, is_tick_delay_on_spawn, p)
#define level_alive_is_tickable(g, v, l, p)               level_alive_flag(g, v, l, is_tickable, p)
#define level_alive_is_tiled(g, v, l, p)                  level_alive_flag(g, v, l, is_tiled, p)
#define level_alive_is_trap(g, v, l, p)                   level_alive_flag(g, v, l, is_trap, p)
#define level_alive_is_treasure(g, v, l, p)               level_alive_flag(g, v, l, is_treasure, p)
#define level_alive_is_undead(g, v, l, p)                 level_alive_flag(g, v, l, is_undead, p)
#define level_alive_is_unused1(g, v, l, p)                level_alive_flag(g, v, l, is_unused1, p)
#define level_alive_is_unused2(g, v, l, p)                level_alive_flag(g, v, l, is_unused2, p)
#define level_alive_is_unused3(g, v, l, p)                level_alive_flag(g, v, l, is_unused3, p)
#define level_alive_is_unused34(g, v, l, p)               level_alive_flag(g, v, l, is_able_to_fall, p)
#define level_alive_is_unused35(g, v, l, p)               level_alive_flag(g, v, l, is_physics_water, p)
#define level_alive_is_unused36(g, v, l, p)               level_alive_flag(g, v, l, is_indestructible, p)
#define level_alive_is_unused37(g, v, l, p)               level_alive_flag(g, v, l, is_floating, p)
#define level_alive_is_unused38(g, v, l, p)               level_alive_flag(g, v, l, is_obs_to_fire, p)
#define level_alive_is_unused4(g, v, l, p)                level_alive_flag(g, v, l, is_unused4, p)
#define level_alive_is_wait_on_dead_anim(g, v, l, p)      level_alive_flag(g, v, l, is_wait_on_dead_anim, p)
#define level_alive_is_walk_through_walls(g, v, l, p)     level_alive_flag(g, v, l, is_walk_through_walls, p)
#define level_alive_is_wall(g, v, l, p)                   level_alive_flag(g, v, l, is_wall, p)
#define level_alive_is_water(g, v, l, p)                  level_alive_flag(g, v, l, is_water, p)
#define level_count_is_able_to_collect_items(g, v, l, p)  level_count_flag(g, v, l, is_able_to_collect_items, p)
#define level_count_is_able_to_collect_keys(g, v, l, p)   level_count_flag(g, v, l, is_able_to_collect_keys, p)
#define level_count_is_able_to_crush_grass(g, v, l, p)    level_count_flag(g, v, l, is_able_to_crush_grass, p)
#define level_count_is_able_to_jump(g, v, l, p)           level_count_flag(g, v, l, is_able_to_jump, p)
#define level_count_is_able_to_open(g, v, l, p)           level_count_flag(g, v, l, is_able_to_open, p)
#define level_count_is_able_to_shove(g, v, l, p)          level_count_flag(g, v, l, is_able_to_shove, p)
#define level_count_is_animated_can_hflip(g, v, l, p)     level_count_flag(g, v, l, is_animated_can_hflip, p)
#define level_count_is_animated_no_dir(g, v, l, p)        level_count_flag(g, v, l, is_animated_no_dir, p)
#define level_count_is_animated_sync_count(g, v, l, p)    level_count_flag(g, v, l, is_animated_sync_count, p)
#define level_count_is_animated(g, v, l, p)               level_count_flag(g, v, l, is_animated, p)
#define level_count_is_barrel(g, v, l, p)                 level_count_flag(g, v, l, is_barrel, p)
#define level_count_is_blit_colored_always(g, v, l, p)    level_count_flag(g, v, l, is_blit_colored_always, p)
#define level_count_is_blit_if_has_seen(g, v, l, p)       level_count_flag(g, v, l, is_blit_if_has_seen, p)
#define level_count_is_brazier(g, v, l, p)                level_count_flag(g, v, l, is_brazier, p)
#define level_count_is_bridge(g, v, l, p)                 level_count_flag(g, v, l, is_bridge, p)
#define level_count_is_broken_on_death(g, v, l, p)        level_count_flag(g, v, l, is_broken_on_death, p)
#define level_count_is_burnable(g, v, l, p)               level_count_flag(g, v, l, is_burnable, p)
#define level_count_is_chasm(g, v, l, p)                  level_count_flag(g, v, l, is_chasm, p)
#define level_count_is_collectable(g, v, l, p)            level_count_flag(g, v, l, is_collectable, p)
#define level_count_is_combustible(g, v, l, p)            level_count_flag(g, v, l, is_combustible, p)
#define level_count_is_corpse_on_death(g, v, l, p)        level_count_flag(g, v, l, is_corpse_on_death, p)
#define level_count_is_corridor(g, v, l, p)               level_count_flag(g, v, l, is_corridor, p)
#define level_count_is_crushable_underfoot(g, v, l, p)    level_count_flag(g, v, l, is_crushable, p)
#define level_count_is_cursor_hazard(g, v, l, p)          level_count_flag(g, v, l, is_cursor_hazard, p)
#define level_count_is_cursor_path_hazard(g, v, l, p)     level_count_flag(g, v, l, is_cursor_path_hazard, p)
#define level_count_is_cursor_path_none(g, v, l, p)       level_count_flag(g, v, l, is_cursor_path_none, p)
#define level_count_is_cursor_path(g, v, l, p)            level_count_flag(g, v, l, is_cursor_path, p)
#define level_count_is_cursor(g, v, l, p)                 level_count_flag(g, v, l, is_cursor, p)
#define level_count_is_damage_capped(g, v, l, p)          level_count_flag(g, v, l, is_damage_capped, p)
#define level_count_is_dead_on_shoving(g, v, l, p)        level_count_flag(g, v, l, is_dead_on_shoving, p)
#define level_count_is_deep_water(g, v, l, p)             level_count_flag(g, v, l, is_deep_water, p)
#define level_count_is_described_cursor(g, v, l, p)       level_count_flag(g, v, l, is_described_cursor, p)
#define level_count_is_dirt(g, v, l, p)                   level_count_flag(g, v, l, is_dirt, p)
#define level_count_is_door_locked(g, v, l, p)            level_count_flag(g, v, l, is_door_locked, p)
#define level_count_is_door_secret(g, v, l, p)            level_count_flag(g, v, l, is_door_secret, p)
#define level_count_is_door_unlocked(g, v, l, p)          level_count_flag(g, v, l, is_door_unlocked, p)
#define level_count_is_dungeon_entrance(g, v, l, p)       level_count_flag(g, v, l, is_dungeon_entrance, p)
#define level_count_is_entrance(g, v, l, p)               level_count_flag(g, v, l, is_entrance, p)
#define level_count_is_ethereal(g, v, l, p)               level_count_flag(g, v, l, is_ethereal, p)
#define level_count_is_exit(g, v, l, p)                   level_count_flag(g, v, l, is_exit, p)
#define level_count_is_explosion(g, v, l, p)              level_count_flag(g, v, l, is_explosion, p)
#define level_count_is_extinguished_on_death(g, v, l, p)  level_count_flag(g, v, l, is_extinguished_on_death, p)
#define level_count_is_fire(g, v, l, p)                   level_count_flag(g, v, l, is_fire, p)
#define level_count_is_floor(g, v, l, p)                  level_count_flag(g, v, l, is_floor, p)
#define level_count_is_flying(g, v, l, p)                 level_count_flag(g, v, l, is_flying, p)
#define level_count_is_foliage(g, v, l, p)                level_count_flag(g, v, l, is_foliage, p)
#define level_count_is_gaseous(g, v, l, p)                level_count_flag(g, v, l, is_gaseous, p)
#define level_count_is_ghost(g, v, l, p)                  level_count_flag(g, v, l, is_ghost, p)
#define level_count_is_grass(g, v, l, p)                  level_count_flag(g, v, l, is_grass, p)
#define level_count_is_health_bar_shown(g, v, l, p)       level_count_flag(g, v, l, is_health_bar_shown, p)
#define level_count_is_inventory_item(g, v, l, p)         level_count_flag(g, v, l, is_inventory_item, p)
#define level_count_is_item_droppable(g, v, l, p)         level_count_flag(g, v, l, is_item_droppable, p)
#define level_count_is_item_equipable(g, v, l, p)         level_count_flag(g, v, l, is_item_equipable, p)
#define level_count_is_item_mergeable(g, v, l, p)         level_count_flag(g, v, l, is_item_mergeable, p)
#define level_count_is_item(g, v, l, p)                   level_count_flag(g, v, l, is_item, p)
#define level_count_is_key(g, v, l, p)                    level_count_flag(g, v, l, is_key, p)
#define level_count_is_kobalos(g, v, l, p)                level_count_flag(g, v, l, is_kobalos, p)
#define level_count_is_lava(g, v, l, p)                   level_count_flag(g, v, l, is_lava, p)
#define level_count_is_level_across(g, v, l, p)           level_count_flag(g, v, l, is_level_across, p)
#define level_count_is_level_curr(g, v, l, p)             level_count_flag(g, v, l, is_level_curr, p)
#define level_count_is_level_down(g, v, l, p)             level_count_flag(g, v, l, is_level_down, p)
#define level_count_is_level_final(g, v, l, p)            level_count_flag(g, v, l, is_level_final, p)
#define level_count_is_level_next(g, v, l, p)             level_count_flag(g, v, l, is_level_next, p)
#define level_count_is_level_not_visited(g, v, l, p)      level_count_flag(g, v, l, is_level_not_visited, p)
#define level_count_is_level_visited(g, v, l, p)          level_count_flag(g, v, l, is_level_visited, p)
#define level_count_is_levitating(g, v, l, p)             level_count_flag(g, v, l, is_levitating, p)
#define level_count_is_light_source(g, v, l, p)           level_count_flag(g, v, l, is_light_source, p)
#define level_count_is_loggable(g, v, l, p)               level_count_flag(g, v, l, is_loggable, p)
#define level_count_is_minion(g, v, l, p)                 level_count_flag(g, v, l, is_minion, p)
#define level_count_is_mob(g, v, l, p)                    level_count_flag(g, v, l, is_mob, p)
#define level_count_is_mob1(g, v, l, p)                   level_count_flag(g, v, l, is_mob1, p)
#define level_count_is_mob2(g, v, l, p)                   level_count_flag(g, v, l, is_mob2, p)
#define level_count_is_monst_group_easy(g, v, l, p)       level_count_flag(g, v, l, is_monst_group_easy, p)
#define level_count_is_monst_group_hard(g, v, l, p)       level_count_flag(g, v, l, is_monst_group_hard, p)
#define level_count_is_monst_group_mob(g, v, l, p)        level_count_flag(g, v, l, is_monst_group_mob, p)
#define level_count_is_monst(g, v, l, p)                  level_count_flag(g, v, l, is_monst, p)
#define level_count_is_needs_move_confirm(g, v, l, p)     level_count_flag(g, v, l, is_submergible, p)
#define level_count_is_obs_block(g, v, l, p)              level_count_flag(g, v, l, is_obs_to_movement, p)
#define level_count_is_obs_to_cursor_path(g, v, l, p)     level_count_flag(g, v, l, is_obs_to_cursor_path, p)
#define level_count_is_obs_to_explosion(g, v, l, p)       level_count_flag(g, v, l, is_obs_to_explosion, p)
#define level_count_is_obs_to_jump_over(g, v, l, p)       level_count_flag(g, v, l, is_obs_to_jump_over, p)
#define level_count_is_obs_to_vision(g, v, l, p)          level_count_flag(g, v, l, is_obs_to_vision, p)
#define level_count_is_openable(g, v, l, p)               level_count_flag(g, v, l, is_openable, p)
#define level_count_is_physics_explosion(g, v, l, p)      level_count_flag(g, v, l, is_physics_explosion, p)
#define level_count_is_physics_temperature(g, v, l, p)    level_count_flag(g, v, l, is_physics_temperature, p)
#define level_count_is_pillar(g, v, l, p)                 level_count_flag(g, v, l, is_pillar, p)
#define level_count_is_player(g, v, l, p)                 level_count_flag(g, v, l, is_player, p)
#define level_count_is_rock(g, v, l, p)                   level_count_flag(g, v, l, is_rock, p)
#define level_count_is_shovable(g, v, l, p)               level_count_flag(g, v, l, is_shovable, p)
#define level_count_is_slime(g, v, l, p)                  level_count_flag(g, v, l, is_slime, p)
#define level_count_is_smoke(g, v, l, p)                  level_count_flag(g, v, l, is_smoke, p)
#define level_count_is_steam(g, v, l, p)                  level_count_flag(g, v, l, is_steam, p)
#define level_count_is_teleport_blocked(g, v, l, p)       level_count_flag(g, v, l, is_teleport_blocked, p)
#define level_count_is_teleport(g, v, l, p)               level_count_flag(g, v, l, is_teleport, p)
#define level_count_is_tick_delay_on_spawn(g, v, l, p)    level_count_flag(g, v, l, is_tick_delay_on_spawn, p)
#define level_count_is_tickable(g, v, l, p)               level_count_flag(g, v, l, is_tickable, p)
#define level_count_is_tiled(g, v, l, p)                  level_count_flag(g, v, l, is_tiled, p)
#define level_count_is_trap(g, v, l, p)                   level_count_flag(g, v, l, is_trap, p)
#define level_count_is_treasure(g, v, l, p)               level_count_flag(g, v, l, is_treasure, p)
#define level_count_is_undead(g, v, l, p)                 level_count_flag(g, v, l, is_undead, p)
#define level_count_is_unused1(g, v, l, p)                level_count_flag(g, v, l, is_unused1, p)
#define level_count_is_unused2(g, v, l, p)                level_count_flag(g, v, l, is_unused2, p)
#define level_count_is_unused3(g, v, l, p)                level_count_flag(g, v, l, is_unused3, p)
#define level_count_is_unused34(g, v, l, p)               level_count_flag(g, v, l, is_able_to_fall, p)
#define level_count_is_unused35(g, v, l, p)               level_count_flag(g, v, l, is_physics_water, p)
#define level_count_is_unused36(g, v, l, p)               level_count_flag(g, v, l, is_indestructible, p)
#define level_count_is_unused37(g, v, l, p)               level_count_flag(g, v, l, is_floating, p)
#define level_count_is_unused38(g, v, l, p)               level_count_flag(g, v, l, is_obs_to_fire, p)
#define level_count_is_unused4(g, v, l, p)                level_count_flag(g, v, l, is_unused4, p)
#define level_count_is_wait_on_dead_anim(g, v, l, p)      level_count_flag(g, v, l, is_wait_on_dead_anim, p)
#define level_count_is_walk_through_walls(g, v, l, p)     level_count_flag(g, v, l, is_walk_through_walls, p)
#define level_count_is_wall(g, v, l, p)                   level_count_flag(g, v, l, is_wall, p)
#define level_count_is_water(g, v, l, p)                  level_count_flag(g, v, l, is_water, p)
#define level_first_is_able_to_collect_items(g, v, l, p)  level_first_flag(g, v, l, is_able_to_collect_items, p)
#define level_first_is_able_to_collect_keys(g, v, l, p)   level_first_flag(g, v, l, is_able_to_collect_keys, p)
#define level_first_is_able_to_crush_grass(g, v, l, p)    level_first_flag(g, v, l, is_able_to_crush_grass, p)
#define level_first_is_able_to_jump(g, v, l, p)           level_first_flag(g, v, l, is_able_to_jump, p)
#define level_first_is_able_to_open(g, v, l, p)           level_first_flag(g, v, l, is_able_to_open, p)
#define level_first_is_able_to_shove(g, v, l, p)          level_first_flag(g, v, l, is_able_to_shove, p)
#define level_first_is_animated_can_hflip(g, v, l, p)     level_first_flag(g, v, l, is_animated_can_hflip, p)
#define level_first_is_animated_no_dir(g, v, l, p)        level_first_flag(g, v, l, is_animated_no_dir, p)
#define level_first_is_animated_sync_first_is(g, v, l, p) level_first_flag(g, v, l, is_animated_sync_first_is, p)
#define level_first_is_animated(g, v, l, p)               level_first_flag(g, v, l, is_animated, p)
#define level_first_is_barrel(g, v, l, p)                 level_first_flag(g, v, l, is_barrel, p)
#define level_first_is_blit_colored_always(g, v, l, p)    level_first_flag(g, v, l, is_blit_colored_always, p)
#define level_first_is_blit_if_has_seen(g, v, l, p)       level_first_flag(g, v, l, is_blit_if_has_seen, p)
#define level_first_is_brazier(g, v, l, p)                level_first_flag(g, v, l, is_brazier, p)
#define level_first_is_bridge(g, v, l, p)                 level_first_flag(g, v, l, is_bridge, p)
#define level_first_is_broken_on_death(g, v, l, p)        level_first_flag(g, v, l, is_broken_on_death, p)
#define level_first_is_burnable(g, v, l, p)               level_first_flag(g, v, l, is_burnable, p)
#define level_first_is_chasm(g, v, l, p)                  level_first_flag(g, v, l, is_chasm, p)
#define level_first_is_collectable(g, v, l, p)            level_first_flag(g, v, l, is_collectable, p)
#define level_first_is_combustible(g, v, l, p)            level_first_flag(g, v, l, is_combustible, p)
#define level_first_is_corpse_on_death(g, v, l, p)        level_first_flag(g, v, l, is_corpse_on_death, p)
#define level_first_is_corridor(g, v, l, p)               level_first_flag(g, v, l, is_corridor, p)
#define level_first_is_crushable_underfoot(g, v, l, p)    level_first_flag(g, v, l, is_crushable, p)
#define level_first_is_cursor_hazard(g, v, l, p)          level_first_flag(g, v, l, is_cursor_hazard, p)
#define level_first_is_cursor_path_hazard(g, v, l, p)     level_first_flag(g, v, l, is_cursor_path_hazard, p)
#define level_first_is_cursor_path_none(g, v, l, p)       level_first_flag(g, v, l, is_cursor_path_none, p)
#define level_first_is_cursor_path(g, v, l, p)            level_first_flag(g, v, l, is_cursor_path, p)
#define level_first_is_cursor(g, v, l, p)                 level_first_flag(g, v, l, is_cursor, p)
#define level_first_is_damage_capped(g, v, l, p)          level_first_flag(g, v, l, is_damage_capped, p)
#define level_first_is_dead_on_shoving(g, v, l, p)        level_first_flag(g, v, l, is_dead_on_shoving, p)
#define level_first_is_deep_water(g, v, l, p)             level_first_flag(g, v, l, is_deep_water, p)
#define level_first_is_described_cursor(g, v, l, p)       level_first_flag(g, v, l, is_described_cursor, p)
#define level_first_is_dirt(g, v, l, p)                   level_first_flag(g, v, l, is_dirt, p)
#define level_first_is_door_locked(g, v, l, p)            level_first_flag(g, v, l, is_door_locked, p)
#define level_first_is_door_secret(g, v, l, p)            level_first_flag(g, v, l, is_door_secret, p)
#define level_first_is_door_unlocked(g, v, l, p)          level_first_flag(g, v, l, is_door_unlocked, p)
#define level_first_is_dungeon_entrance(g, v, l, p)       level_first_flag(g, v, l, is_dungeon_entrance, p)
#define level_first_is_entrance(g, v, l, p)               level_first_flag(g, v, l, is_entrance, p)
#define level_first_is_ethereal(g, v, l, p)               level_first_flag(g, v, l, is_ethereal, p)
#define level_first_is_exit(g, v, l, p)                   level_first_flag(g, v, l, is_exit, p)
#define level_first_is_explosion(g, v, l, p)              level_first_flag(g, v, l, is_explosion, p)
#define level_first_is_extinguished_on_death(g, v, l, p)  level_first_flag(g, v, l, is_extinguished_on_death, p)
#define level_first_is_fire(g, v, l, p)                   level_first_flag(g, v, l, is_fire, p)
#define level_first_is_floor(g, v, l, p)                  level_first_flag(g, v, l, is_floor, p)
#define level_first_is_flying(g, v, l, p)                 level_first_flag(g, v, l, is_flying, p)
#define level_first_is_foliage(g, v, l, p)                level_first_flag(g, v, l, is_foliage, p)
#define level_first_is_gaseous(g, v, l, p)                level_first_flag(g, v, l, is_gaseous, p)
#define level_first_is_ghost(g, v, l, p)                  level_first_flag(g, v, l, is_ghost, p)
#define level_first_is_grass(g, v, l, p)                  level_first_flag(g, v, l, is_grass, p)
#define level_first_is_health_bar_shown(g, v, l, p)       level_first_flag(g, v, l, is_health_bar_shown, p)
#define level_first_is_inventory_item(g, v, l, p)         level_first_flag(g, v, l, is_inventory_item, p)
#define level_first_is_item_droppable(g, v, l, p)         level_first_flag(g, v, l, is_item_droppable, p)
#define level_first_is_item_equipable(g, v, l, p)         level_first_flag(g, v, l, is_item_equipable, p)
#define level_first_is_item_mergeable(g, v, l, p)         level_first_flag(g, v, l, is_item_mergeable, p)
#define level_first_is_item(g, v, l, p)                   level_first_flag(g, v, l, is_item, p)
#define level_first_is_key(g, v, l, p)                    level_first_flag(g, v, l, is_key, p)
#define level_first_is_kobalos(g, v, l, p)                level_first_flag(g, v, l, is_kobalos, p)
#define level_first_is_lava(g, v, l, p)                   level_first_flag(g, v, l, is_lava, p)
#define level_first_is_level_across(g, v, l, p)           level_first_flag(g, v, l, is_level_across, p)
#define level_first_is_level_curr(g, v, l, p)             level_first_flag(g, v, l, is_level_curr, p)
#define level_first_is_level_down(g, v, l, p)             level_first_flag(g, v, l, is_level_down, p)
#define level_first_is_level_final(g, v, l, p)            level_first_flag(g, v, l, is_level_final, p)
#define level_first_is_level_next(g, v, l, p)             level_first_flag(g, v, l, is_level_next, p)
#define level_first_is_level_not_visited(g, v, l, p)      level_first_flag(g, v, l, is_level_not_visited, p)
#define level_first_is_level_visited(g, v, l, p)          level_first_flag(g, v, l, is_level_visited, p)
#define level_first_is_levitating(g, v, l, p)             level_first_flag(g, v, l, is_levitating, p)
#define level_first_is_light_source(g, v, l, p)           level_first_flag(g, v, l, is_light_source, p)
#define level_first_is_loggable(g, v, l, p)               level_first_flag(g, v, l, is_loggable, p)
#define level_first_is_minion(g, v, l, p)                 level_first_flag(g, v, l, is_minion, p)
#define level_first_is_mob(g, v, l, p)                    level_first_flag(g, v, l, is_mob, p)
#define level_first_is_mob1(g, v, l, p)                   level_first_flag(g, v, l, is_mob1, p)
#define level_first_is_mob2(g, v, l, p)                   level_first_flag(g, v, l, is_mob2, p)
#define level_first_is_monst_group_easy(g, v, l, p)       level_first_flag(g, v, l, is_monst_group_easy, p)
#define level_first_is_monst_group_hard(g, v, l, p)       level_first_flag(g, v, l, is_monst_group_hard, p)
#define level_first_is_monst_group_mob(g, v, l, p)        level_first_flag(g, v, l, is_monst_group_mob, p)
#define level_first_is_monst(g, v, l, p)                  level_first_flag(g, v, l, is_monst, p)
#define level_first_is_needs_move_confirm(g, v, l, p)     level_first_flag(g, v, l, is_submergible, p)
#define level_first_is_obs_block(g, v, l, p)              level_first_flag(g, v, l, is_obs_to_movement, p)
#define level_first_is_obs_to_cursor_path(g, v, l, p)     level_first_flag(g, v, l, is_obs_to_cursor_path, p)
#define level_first_is_obs_to_explosion(g, v, l, p)       level_first_flag(g, v, l, is_obs_to_explosion, p)
#define level_first_is_obs_to_jump_over(g, v, l, p)       level_first_flag(g, v, l, is_obs_to_jump_over, p)
#define level_first_is_obs_to_vision(g, v, l, p)          level_first_flag(g, v, l, is_obs_to_vision, p)
#define level_first_is_openable(g, v, l, p)               level_first_flag(g, v, l, is_openable, p)
#define level_first_is_physics_explosion(g, v, l, p)      level_first_flag(g, v, l, is_physics_explosion, p)
#define level_first_is_physics_temperature(g, v, l, p)    level_first_flag(g, v, l, is_physics_temperature, p)
#define level_first_is_pillar(g, v, l, p)                 level_first_flag(g, v, l, is_pillar, p)
#define level_first_is_player(g, v, l, p)                 level_first_flag(g, v, l, is_player, p)
#define level_first_is_rock(g, v, l, p)                   level_first_flag(g, v, l, is_rock, p)
#define level_first_is_shovable(g, v, l, p)               level_first_flag(g, v, l, is_shovable, p)
#define level_first_is_slime(g, v, l, p)                  level_first_flag(g, v, l, is_slime, p)
#define level_first_is_smoke(g, v, l, p)                  level_first_flag(g, v, l, is_smoke, p)
#define level_first_is_steam(g, v, l, p)                  level_first_flag(g, v, l, is_steam, p)
#define level_first_is_teleport_blocked(g, v, l, p)       level_first_flag(g, v, l, is_teleport_blocked, p)
#define level_first_is_teleport(g, v, l, p)               level_first_flag(g, v, l, is_teleport, p)
#define level_first_is_tick_delay_on_spawn(g, v, l, p)    level_first_flag(g, v, l, is_tick_delay_on_spawn, p)
#define level_first_is_tickable(g, v, l, p)               level_first_flag(g, v, l, is_tickable, p)
#define level_first_is_tiled(g, v, l, p)                  level_first_flag(g, v, l, is_tiled, p)
#define level_first_is_trap(g, v, l, p)                   level_first_flag(g, v, l, is_trap, p)
#define level_first_is_treasure(g, v, l, p)               level_first_flag(g, v, l, is_treasure, p)
#define level_first_is_undead(g, v, l, p)                 level_first_flag(g, v, l, is_undead, p)
#define level_first_is_unused1(g, v, l, p)                level_first_flag(g, v, l, is_unused1, p)
#define level_first_is_unused2(g, v, l, p)                level_first_flag(g, v, l, is_unused2, p)
#define level_first_is_unused3(g, v, l, p)                level_first_flag(g, v, l, is_unused3, p)
#define level_first_is_unused34(g, v, l, p)               level_first_flag(g, v, l, is_able_to_fall, p)
#define level_first_is_unused35(g, v, l, p)               level_first_flag(g, v, l, is_physics_water, p)
#define level_first_is_unused36(g, v, l, p)               level_first_flag(g, v, l, is_indestructible, p)
#define level_first_is_unused37(g, v, l, p)               level_first_flag(g, v, l, is_floating, p)
#define level_first_is_unused38(g, v, l, p)               level_first_flag(g, v, l, is_obs_to_fire, p)
#define level_first_is_unused4(g, v, l, p)                level_first_flag(g, v, l, is_unused4, p)
#define level_first_is_wait_on_dead_anim(g, v, l, p)      level_first_flag(g, v, l, is_wait_on_dead_anim, p)
#define level_first_is_walk_through_walls(g, v, l, p)     level_first_flag(g, v, l, is_walk_through_walls, p)
#define level_first_is_wall(g, v, l, p)                   level_first_flag(g, v, l, is_wall, p)
#define level_first_is_water(g, v, l, p)                  level_first_flag(g, v, l, is_water, p)
#define level_is_able_to_collect_items(g, v, l, p)        level_flag(g, v, l, is_able_to_collect_items, p)
#define level_is_able_to_collect_keys(g, v, l, p)         level_flag(g, v, l, is_able_to_collect_keys, p)
#define level_is_able_to_crush_grass(g, v, l, p)          level_flag(g, v, l, is_able_to_crush_grass, p)
#define level_is_able_to_fall(g, v, l, p)                 level_flag(g, v, l, is_able_to_fall, p)
#define level_is_able_to_jump(g, v, l, p)                 level_flag(g, v, l, is_able_to_jump, p)
#define level_is_able_to_open(g, v, l, p)                 level_flag(g, v, l, is_able_to_open, p)
#define level_is_able_to_shove(g, v, l, p)                level_flag(g, v, l, is_able_to_shove, p)
#define level_is_animated_can_hflip(g, v, l, p)           level_flag(g, v, l, is_animated_can_hflip, p)
#define level_is_animated_no_dir(g, v, l, p)              level_flag(g, v, l, is_animated_no_dir, p)
#define level_is_animated_sync_first(g, v, l, p)          level_flag(g, v, l, is_animated_sync_first, p)
#define level_is_animated(g, v, l, p)                     level_flag(g, v, l, is_animated, p)
#define level_is_barrel(g, v, l, p)                       level_flag(g, v, l, is_barrel, p)
#define level_is_blit_centered(g, v, l, p)                level_flag(g, v, l, is_blit_centered, p)
#define level_is_blit_colored_always(g, v, l, p)          level_flag(g, v, l, is_blit_colored_always, p)
#define level_is_blit_if_has_seen(g, v, l, p)             level_flag(g, v, l, is_blit_if_has_seen, p)
#define level_is_blit_on_ground(g, v, l, p)               level_flag(g, v, l, is_blit_on_ground, p)
#define level_is_blit_outlined(g, v, l, p)                level_flag(g, v, l, is_blit_outlined, p)
#define level_is_blit_square_outlined(g, v, l, p)         level_flag(g, v, l, is_blit_square_outlined, p)
#define level_is_brazier(g, v, l, p)                      level_flag(g, v, l, is_brazier, p)
#define level_is_bridge(g, v, l, p)                       level_flag(g, v, l, is_bridge, p)
#define level_is_broken_on_death(g, v, l, p)              level_flag(g, v, l, is_broken_on_death, p)
#define level_is_burnable(g, v, l, p)                     level_flag(g, v, l, is_burnable, p)
#define level_is_chasm(g, v, l, p)                        level_flag(g, v, l, is_chasm, p)
#define level_is_collectable(g, v, l, p)                  level_flag(g, v, l, is_collectable, p)
#define level_is_combustible(g, v, l, p)                  level_flag(g, v, l, is_combustible, p)
#define level_is_corpse_on_death(g, v, l, p)              level_flag(g, v, l, is_corpse_on_death, p)
#define level_is_corridor(g, v, l, p)                     level_flag(g, v, l, is_corridor, p)
#define level_is_crushable(g, v, l, p)                    level_flag(g, v, l, is_crushable, p)
#define level_is_cursor_hazard(g, v, l, p)                level_flag(g, v, l, is_cursor_hazard, p)
#define level_is_cursor_path_hazard(g, v, l, p)           level_flag(g, v, l, is_cursor_path_hazard, p)
#define level_is_cursor_path_none(g, v, l, p)             level_flag(g, v, l, is_cursor_path_none, p)
#define level_is_cursor_path(g, v, l, p)                  level_flag(g, v, l, is_cursor_path, p)
#define level_is_cursor(g, v, l, p)                       level_flag(g, v, l, is_cursor, p)
#define level_is_damage_capped(g, v, l, p)                level_flag(g, v, l, is_damage_capped, p)
#define level_is_dead_on_shoving(g, v, l, p)              level_flag(g, v, l, is_dead_on_shoving, p)
#define level_is_deep_water(g, v, l, p)                   level_flag(g, v, l, is_deep_water, p)
#define level_is_described_cursor(g, v, l, p)             level_flag(g, v, l, is_described_cursor, p)
#define level_is_dirt(g, v, l, p)                         level_flag(g, v, l, is_dirt, p)
#define level_is_door_locked(g, v, l, p)                  level_flag(g, v, l, is_door_locked, p)
#define level_is_door_secret(g, v, l, p)                  level_flag(g, v, l, is_door_secret, p)
#define level_is_door_unlocked(g, v, l, p)                level_flag(g, v, l, is_door_unlocked, p)
#define level_is_dungeon_entrance(g, v, l, p)             level_flag(g, v, l, is_dungeon_entrance, p)
#define level_is_entrance(g, v, l, p)                     level_flag(g, v, l, is_entrance, p)
#define level_is_ethereal(g, v, l, p)                     level_flag(g, v, l, is_ethereal, p)
#define level_is_exit(g, v, l, p)                         level_flag(g, v, l, is_exit, p)
#define level_is_explosion(g, v, l, p)                    level_flag(g, v, l, is_explosion, p)
#define level_is_extinguished_on_death(g, v, l, p)        level_flag(g, v, l, is_extinguished_on_death, p)
#define level_is_fire(g, v, l, p)                         level_flag(g, v, l, is_fire, p)
#define level_is_floating(g, v, l, p)                     level_flag(g, v, l, is_floating, p)
#define level_is_floor(g, v, l, p)                        level_flag(g, v, l, is_floor, p)
#define level_is_flying(g, v, l, p)                       level_flag(g, v, l, is_flying, p)
#define level_is_foliage(g, v, l, p)                      level_flag(g, v, l, is_foliage, p)
#define level_is_gaseous(g, v, l, p)                      level_flag(g, v, l, is_gaseous, p)
#define level_is_ghost(g, v, l, p)                        level_flag(g, v, l, is_ghost, p)
#define level_is_grass(g, v, l, p)                        level_flag(g, v, l, is_grass, p)
#define level_is_health_bar_shown(g, v, l, p)             level_flag(g, v, l, is_health_bar_shown, p)
#define level_is_indestructible(g, v, l, p)               level_flag(g, v, l, is_indestructible, p)
#define level_is_inventory_item(g, v, l, p)               level_flag(g, v, l, is_inventory_item, p)
#define level_is_item_droppable(g, v, l, p)               level_flag(g, v, l, is_item_droppable, p)
#define level_is_item_equipable(g, v, l, p)               level_flag(g, v, l, is_item_equipable, p)
#define level_is_item_mergeable(g, v, l, p)               level_flag(g, v, l, is_item_mergeable, p)
#define level_is_item(g, v, l, p)                         level_flag(g, v, l, is_item, p)
#define level_is_key(g, v, l, p)                          level_flag(g, v, l, is_key, p)
#define level_is_kobalos(g, v, l, p)                      level_flag(g, v, l, is_kobalos, p)
#define level_is_lava(g, v, l, p)                         level_flag(g, v, l, is_lava, p)
#define level_is_level_across(g, v, l, p)                 level_flag(g, v, l, is_level_across, p)
#define level_is_level_curr(g, v, l, p)                   level_flag(g, v, l, is_level_curr, p)
#define level_is_level_down(g, v, l, p)                   level_flag(g, v, l, is_level_down, p)
#define level_is_level_final(g, v, l, p)                  level_flag(g, v, l, is_level_final, p)
#define level_is_level_next(g, v, l, p)                   level_flag(g, v, l, is_level_next, p)
#define level_is_level_not_visited(g, v, l, p)            level_flag(g, v, l, is_level_not_visited, p)
#define level_is_level_visited(g, v, l, p)                level_flag(g, v, l, is_level_visited, p)
#define level_is_levitating(g, v, l, p)                   level_flag(g, v, l, is_levitating, p)
#define level_is_light_source(g, v, l, p)                 level_flag(g, v, l, is_light_source, p)
#define level_is_loggable(g, v, l, p)                     level_flag(g, v, l, is_loggable, p)
#define level_is_minion(g, v, l, p)                       level_flag(g, v, l, is_minion, p)
#define level_is_mob(g, v, l, p)                          level_flag(g, v, l, is_mob, p)
#define level_is_mob1(g, v, l, p)                         level_flag(g, v, l, is_mob1, p)
#define level_is_mob2(g, v, l, p)                         level_flag(g, v, l, is_mob2, p)
#define level_is_monst_group_easy(g, v, l, p)             level_flag(g, v, l, is_monst_group_easy, p)
#define level_is_monst_group_hard(g, v, l, p)             level_flag(g, v, l, is_monst_group_hard, p)
#define level_is_monst_group_mob(g, v, l, p)              level_flag(g, v, l, is_monst_group_mob, p)
#define level_is_monst(g, v, l, p)                        level_flag(g, v, l, is_monst, p)
#define level_is_needs_move_confirm(g, v, l, p)           level_flag(g, v, l, is_needs_move_confirm, p)
#define level_is_obs_to_cursor_path(g, v, l, p)           level_flag(g, v, l, is_obs_to_cursor_path, p)
#define level_is_obs_to_explosion(g, v, l, p)             level_flag(g, v, l, is_obs_to_explosion, p)
#define level_is_obs_to_falling_onto(g, v, l, p)          level_flag(g, v, l, is_obs_to_falling_onto, p)
#define level_is_obs_to_fire(g, v, l, p)                  level_flag(g, v, l, is_obs_to_fire, p)
#define level_is_obs_to_jump_over(g, v, l, p)             level_flag(g, v, l, is_obs_to_jump_over, p)
#define level_is_obs_to_jumping_onto(g, v, l, p)          level_flag(g, v, l, is_obs_to_jumping_onto, p)
#define level_is_obs_to_movement(g, v, l, p)              level_flag(g, v, l, is_obs_to_movement, p)
#define level_is_obs_to_vision(g, v, l, p)                level_flag(g, v, l, is_obs_to_vision, p)
#define level_is_openable(g, v, l, p)                     level_flag(g, v, l, is_openable, p)
#define level_is_physics_explosion(g, v, l, p)            level_flag(g, v, l, is_physics_explosion, p)
#define level_is_physics_temperature(g, v, l, p)          level_flag(g, v, l, is_physics_temperature, p)
#define level_is_physics_water(g, v, l, p)                level_flag(g, v, l, is_physics_water, p)
#define level_is_pillar(g, v, l, p)                       level_flag(g, v, l, is_pillar, p)
#define level_is_player(g, v, l, p)                       level_flag(g, v, l, is_player, p)
#define level_is_rock(g, v, l, p)                         level_flag(g, v, l, is_rock, p)
#define level_is_shovable(g, v, l, p)                     level_flag(g, v, l, is_shovable, p)
#define level_is_slime(g, v, l, p)                        level_flag(g, v, l, is_slime, p)
#define level_is_smoke(g, v, l, p)                        level_flag(g, v, l, is_smoke, p)
#define level_is_steam(g, v, l, p)                        level_flag(g, v, l, is_steam, p)
#define level_is_submergible(g, v, l, p)                  level_flag(g, v, l, is_submergible, p)
#define level_is_teleport_blocked(g, v, l, p)             level_flag(g, v, l, is_teleport_blocked, p)
#define level_is_teleport(g, v, l, p)                     level_flag(g, v, l, is_teleport, p)
#define level_is_tick_delay_on_spawn(g, v, l, p)          level_flag(g, v, l, is_tick_delay_on_spawn, p)
#define level_is_tickable(g, v, l, p)                     level_flag(g, v, l, is_tickable, p)
#define level_is_tiled(g, v, l, p)                        level_flag(g, v, l, is_tiled, p)
#define level_is_trap(g, v, l, p)                         level_flag(g, v, l, is_trap, p)
#define level_is_treasure(g, v, l, p)                     level_flag(g, v, l, is_treasure, p)
#define level_is_undead(g, v, l, p)                       level_flag(g, v, l, is_undead, p)
#define level_is_unused1(g, v, l, p)                      level_flag(g, v, l, is_unused1, p)
#define level_is_unused2(g, v, l, p)                      level_flag(g, v, l, is_unused2, p)
#define level_is_unused3(g, v, l, p)                      level_flag(g, v, l, is_unused3, p)
#define level_is_unused4(g, v, l, p)                      level_flag(g, v, l, is_unused4, p)
#define level_is_wait_on_dead_anim(g, v, l, p)            level_flag(g, v, l, is_wait_on_dead_anim, p)
#define level_is_walk_through_walls(g, v, l, p)           level_flag(g, v, l, is_walk_through_walls, p)
#define level_is_wall(g, v, l, p)                         level_flag(g, v, l, is_wall, p)
#define level_is_water(g, v, l, p)                        level_flag(g, v, l, is_water, p)
#define level_open_is_able_to_collect_items(g, v, l, p)   level_open_flag(g, v, l, is_able_to_collect_items, p)
#define level_open_is_able_to_collect_keys(g, v, l, p)    level_open_flag(g, v, l, is_able_to_collect_keys, p)
#define level_open_is_able_to_crush_grass(g, v, l, p)     level_open_flag(g, v, l, is_able_to_crush_grass, p)
#define level_open_is_able_to_jump(g, v, l, p)            level_open_flag(g, v, l, is_able_to_jump, p)
#define level_open_is_able_to_open(g, v, l, p)            level_open_flag(g, v, l, is_able_to_open, p)
#define level_open_is_able_to_shove(g, v, l, p)           level_open_flag(g, v, l, is_able_to_shove, p)
#define level_open_is_animated_can_hflip(g, v, l, p)      level_open_flag(g, v, l, is_animated_can_hflip, p)
#define level_open_is_animated_no_dir(g, v, l, p)         level_open_flag(g, v, l, is_animated_no_dir, p)
#define level_open_is_animated_sync_first(g, v, l, p)     level_open_flag(g, v, l, is_animated_sync_first, p)
#define level_open_is_animated(g, v, l, p)                level_open_flag(g, v, l, is_animated, p)
#define level_open_is_barrel(g, v, l, p)                  level_open_flag(g, v, l, is_barrel, p)
#define level_open_is_blit_colored_always(g, v, l, p)     level_open_flag(g, v, l, is_blit_colored_always, p)
#define level_open_is_blit_if_has_seen(g, v, l, p)        level_open_flag(g, v, l, is_blit_if_has_seen, p)
#define level_open_is_brazier(g, v, l, p)                 level_open_flag(g, v, l, is_brazier, p)
#define level_open_is_bridge(g, v, l, p)                  level_open_flag(g, v, l, is_bridge, p)
#define level_open_is_broken_on_death(g, v, l, p)         level_open_flag(g, v, l, is_broken_on_death, p)
#define level_open_is_burnable(g, v, l, p)                level_open_flag(g, v, l, is_burnable, p)
#define level_open_is_chasm(g, v, l, p)                   level_open_flag(g, v, l, is_chasm, p)
#define level_open_is_collectable(g, v, l, p)             level_open_flag(g, v, l, is_collectable, p)
#define level_open_is_combustible(g, v, l, p)             level_open_flag(g, v, l, is_combustible, p)
#define level_open_is_corpse_on_death(g, v, l, p)         level_open_flag(g, v, l, is_corpse_on_death, p)
#define level_open_is_corridor(g, v, l, p)                level_open_flag(g, v, l, is_corridor, p)
#define level_open_is_crushable_underfoot(g, v, l, p)     level_open_flag(g, v, l, is_crushable, p)
#define level_open_is_cursor_hazard(g, v, l, p)           level_open_flag(g, v, l, is_cursor_hazard, p)
#define level_open_is_cursor_path_hazard(g, v, l, p)      level_open_flag(g, v, l, is_cursor_path_hazard, p)
#define level_open_is_cursor_path_none(g, v, l, p)        level_open_flag(g, v, l, is_cursor_path_none, p)
#define level_open_is_cursor_path(g, v, l, p)             level_open_flag(g, v, l, is_cursor_path, p)
#define level_open_is_cursor(g, v, l, p)                  level_open_flag(g, v, l, is_cursor, p)
#define level_open_is_damage_capped(g, v, l, p)           level_open_flag(g, v, l, is_damage_capped, p)
#define level_open_is_dead_on_shoving(g, v, l, p)         level_open_flag(g, v, l, is_dead_on_shoving, p)
#define level_open_is_deep_water(g, v, l, p)              level_open_flag(g, v, l, is_deep_water, p)
#define level_open_is_described_cursor(g, v, l, p)        level_open_flag(g, v, l, is_described_cursor, p)
#define level_open_is_dirt(g, v, l, p)                    level_open_flag(g, v, l, is_dirt, p)
#define level_open_is_door_locked(g, v, l, p)             level_open_flag(g, v, l, is_door_locked, p)
#define level_open_is_door_secret(g, v, l, p)             level_open_flag(g, v, l, is_door_secret, p)
#define level_open_is_door_unlocked(g, v, l, p)           level_open_flag(g, v, l, is_door_unlocked, p)
#define level_open_is_dungeon_entrance(g, v, l, p)        level_open_flag(g, v, l, is_dungeon_entrance, p)
#define level_open_is_entrance(g, v, l, p)                level_open_flag(g, v, l, is_entrance, p)
#define level_open_is_ethereal(g, v, l, p)                level_open_flag(g, v, l, is_ethereal, p)
#define level_open_is_exit(g, v, l, p)                    level_open_flag(g, v, l, is_exit, p)
#define level_open_is_explosion(g, v, l, p)               level_open_flag(g, v, l, is_explosion, p)
#define level_open_is_extinguished_on_death(g, v, l, p)   level_open_flag(g, v, l, is_extinguished_on_death, p)
#define level_open_is_fire(g, v, l, p)                    level_open_flag(g, v, l, is_fire, p)
#define level_open_is_floor(g, v, l, p)                   level_open_flag(g, v, l, is_floor, p)
#define level_open_is_flying(g, v, l, p)                  level_open_flag(g, v, l, is_flying, p)
#define level_open_is_foliage(g, v, l, p)                 level_open_flag(g, v, l, is_foliage, p)
#define level_open_is_gaseous(g, v, l, p)                 level_open_flag(g, v, l, is_gaseous, p)
#define level_open_is_ghost(g, v, l, p)                   level_open_flag(g, v, l, is_ghost, p)
#define level_open_is_grass(g, v, l, p)                   level_open_flag(g, v, l, is_grass, p)
#define level_open_is_health_bar_shown(g, v, l, p)        level_open_flag(g, v, l, is_health_bar_shown, p)
#define level_open_is_inventory_item(g, v, l, p)          level_open_flag(g, v, l, is_inventory_item, p)
#define level_open_is_item_droppable(g, v, l, p)          level_open_flag(g, v, l, is_item_droppable, p)
#define level_open_is_item_equipable(g, v, l, p)          level_open_flag(g, v, l, is_item_equipable, p)
#define level_open_is_item_mergeable(g, v, l, p)          level_open_flag(g, v, l, is_item_mergeable, p)
#define level_open_is_item(g, v, l, p)                    level_open_flag(g, v, l, is_item, p)
#define level_open_is_key(g, v, l, p)                     level_open_flag(g, v, l, is_key, p)
#define level_open_is_kobalos(g, v, l, p)                 level_open_flag(g, v, l, is_kobalos, p)
#define level_open_is_lava(g, v, l, p)                    level_open_flag(g, v, l, is_lava, p)
#define level_open_is_level_across(g, v, l, p)            level_open_flag(g, v, l, is_level_across, p)
#define level_open_is_level_curr(g, v, l, p)              level_open_flag(g, v, l, is_level_curr, p)
#define level_open_is_level_down(g, v, l, p)              level_open_flag(g, v, l, is_level_down, p)
#define level_open_is_level_final(g, v, l, p)             level_open_flag(g, v, l, is_level_final, p)
#define level_open_is_level_next(g, v, l, p)              level_open_flag(g, v, l, is_level_next, p)
#define level_open_is_level_not_visited(g, v, l, p)       level_open_flag(g, v, l, is_level_not_visited, p)
#define level_open_is_level_visited(g, v, l, p)           level_open_flag(g, v, l, is_level_visited, p)
#define level_open_is_levitating(g, v, l, p)              level_open_flag(g, v, l, is_levitating, p)
#define level_open_is_light_source(g, v, l, p)            level_open_flag(g, v, l, is_light_source, p)
#define level_open_is_loggable(g, v, l, p)                level_open_flag(g, v, l, is_loggable, p)
#define level_open_is_minion(g, v, l, p)                  level_open_flag(g, v, l, is_minion, p)
#define level_open_is_mob(g, v, l, p)                     level_open_flag(g, v, l, is_mob, p)
#define level_open_is_mob1(g, v, l, p)                    level_open_flag(g, v, l, is_mob1, p)
#define level_open_is_mob2(g, v, l, p)                    level_open_flag(g, v, l, is_mob2, p)
#define level_open_is_monst_group_easy(g, v, l, p)        level_open_flag(g, v, l, is_monst_group_easy, p)
#define level_open_is_monst_group_hard(g, v, l, p)        level_open_flag(g, v, l, is_monst_group_hard, p)
#define level_open_is_monst_group_mob(g, v, l, p)         level_open_flag(g, v, l, is_monst_group_mob, p)
#define level_open_is_monst(g, v, l, p)                   level_open_flag(g, v, l, is_monst, p)
#define level_open_is_needs_move_confirm(g, v, l, p)      level_open_flag(g, v, l, is_needs_move_confirm, p)
#define level_open_is_obs_block(g, v, l, p)               level_open_flag(g, v, l, is_obs_to_movement, p)
#define level_open_is_obs_to_cursor_path(g, v, l, p)      level_open_flag(g, v, l, is_obs_to_cursor_path, p)
#define level_open_is_obs_to_explosion(g, v, l, p)        level_open_flag(g, v, l, is_obs_to_explosion, p)
#define level_open_is_obs_to_jump_over(g, v, l, p)        level_open_flag(g, v, l, is_obs_to_jump_over, p)
#define level_open_is_obs_to_vision(g, v, l, p)           level_open_flag(g, v, l, is_obs_to_vision, p)
#define level_open_is_openable(g, v, l, p)                level_open_flag(g, v, l, is_openable, p)
#define level_open_is_physics_explosion(g, v, l, p)       level_open_flag(g, v, l, is_physics_explosion, p)
#define level_open_is_physics_temperature(g, v, l, p)     level_open_flag(g, v, l, is_physics_temperature, p)
#define level_open_is_pillar(g, v, l, p)                  level_open_flag(g, v, l, is_pillar, p)
#define level_open_is_player(g, v, l, p)                  level_open_flag(g, v, l, is_player, p)
#define level_open_is_rock(g, v, l, p)                    level_open_flag(g, v, l, is_rock, p)
#define level_open_is_shovable(g, v, l, p)                level_open_flag(g, v, l, is_shovable, p)
#define level_open_is_slime(g, v, l, p)                   level_open_flag(g, v, l, is_slime, p)
#define level_open_is_smoke(g, v, l, p)                   level_open_flag(g, v, l, is_smoke, p)
#define level_open_is_steam(g, v, l, p)                   level_open_flag(g, v, l, is_steam, p)
#define level_open_is_teleport_blocked(g, v, l, p)        level_open_flag(g, v, l, is_teleport_blocked, p)
#define level_open_is_teleport(g, v, l, p)                level_open_flag(g, v, l, is_teleport, p)
#define level_open_is_tick_delay_on_spawn(g, v, l, p)     level_open_flag(g, v, l, is_tick_delay_on_spawn, p)
#define level_open_is_tickable(g, v, l, p)                level_open_flag(g, v, l, is_tickable, p)
#define level_open_is_tiled(g, v, l, p)                   level_open_flag(g, v, l, is_tiled, p)
#define level_open_is_trap(g, v, l, p)                    level_open_flag(g, v, l, is_trap, p)
#define level_open_is_treasure(g, v, l, p)                level_open_flag(g, v, l, is_treasure, p)
#define level_open_is_undead(g, v, l, p)                  level_open_flag(g, v, l, is_undead, p)
#define level_open_is_unused1(g, v, l, p)                 level_open_flag(g, v, l, is_unused1, p)
#define level_open_is_unused2(g, v, l, p)                 level_open_flag(g, v, l, is_unused2, p)
#define level_open_is_unused3(g, v, l, p)                 level_open_flag(g, v, l, is_unused3, p)
#define level_open_is_unused34(g, v, l, p)                level_open_flag(g, v, l, is_able_to_fall, p)
#define level_open_is_unused35(g, v, l, p)                level_open_flag(g, v, l, is_physics_water, p)
#define level_open_is_unused36(g, v, l, p)                level_open_flag(g, v, l, is_indestructible, p)
#define level_open_is_unused37(g, v, l, p)                level_open_flag(g, v, l, is_floating, p)
#define level_open_is_unused38(g, v, l, p)                level_open_flag(g, v, l, is_obs_to_fire, p)
#define level_open_is_unused4(g, v, l, p)                 level_open_flag(g, v, l, is_unused4, p)
#define level_open_is_wait_on_dead_anim(g, v, l, p)       level_open_flag(g, v, l, is_wait_on_dead_anim, p)
#define level_open_is_walk_through_walls(g, v, l, p)      level_open_flag(g, v, l, is_walk_through_walls, p)
#define level_open_is_wall(g, v, l, p)                    level_open_flag(g, v, l, is_wall, p)
#define level_open_is_water(g, v, l, p)                   level_open_flag(g, v, l, is_water, p)
// end sort marker2 }

#endif // _MY_THING_TEMPLATE_H_
