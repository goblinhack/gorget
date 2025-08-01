//
// Copyright goblinhack@gmail.com
//

#pragma once
#ifndef _MY_THING_TEMPLATE_H_
#define _MY_THING_TEMPLATE_H_

#include "my_enum.hpp"
#include "my_types.hpp"

#include <stdarg.h>
#include <string>

//
// Thing flags enum
//
#define THING_FLAG_ENUM(list_macro)                                                                                  \
  clang_format_indent()                                                 /* dummy line for clang indentation fixup */ \
      list_macro(is_able_to_shove, "is_able_to_shove"),                 /* newline */                                \
      list_macro(is_animated_can_hflip, "is_animated_can_hflip"),       /* newline */                                \
      list_macro(is_animated_no_dir, "is_animated_no_dir"),             /* newline */                                \
      list_macro(is_animated_sync_first, "is_animated_sync_first"),     /* newline */                                \
      list_macro(is_animated, "is_animated"),                           /* newline */                                \
      list_macro(is_barrel, "is_barrel"),                               /* newline */                                \
      list_macro(is_blit_centered, "is_blit_centered"),                 /* newline */                                \
      list_macro(is_blit_on_ground, "is_blit_on_ground"),               /* newline */                                \
      list_macro(is_blit_outlined, "is_blit_outlined"),                 /* newline */                                \
      list_macro(is_blit_square_outlined, "is_blit_square_outlined"),   /* newline */                                \
      list_macro(is_brazier, "is_brazier"),                             /* newline */                                \
      list_macro(is_bridge, "is_bridge"),                               /* newline */                                \
      list_macro(is_broken_on_death, "is_broken_on_death"),             /* newline */                                \
      list_macro(is_burnable, "is_burnable"),                           /* newline */                                \
      list_macro(is_chasm, "is_chasm"),                                 /* newline */                                \
      list_macro(is_combustible, "is_combustible"),                     /* newline */                                \
      list_macro(is_corpse_on_death, "is_corpse_on_death"),             /* newline */                                \
      list_macro(is_corridor, "is_corridor"),                           /* newline */                                \
      list_macro(is_crushable, "is_crushable"),                         /* newline */                                \
      list_macro(is_cursor_hazard, "is_cursor_hazard"),                 /* newline */                                \
      list_macro(is_cursor_path_blocker, "is_cursor_path_blocker"),     /* newline */                                \
      list_macro(is_cursor_path_hazard, "is_cursor_path_hazard"),       /* newline */                                \
      list_macro(is_cursor_path, "is_cursor_path"),                     /* newline */                                \
      list_macro(is_cursor, "is_cursor"),                               /* newline */                                \
      list_macro(is_dead_on_shoving, "is_dead_on_shoving"),             /* newline */                                \
      list_macro(is_deep_water, "is_deep_water"),                       /* newline */                                \
      list_macro(is_described_cursor, "is_described_cursor"),           /* newline */                                \
      list_macro(is_dirt, "is_dirt"),                                   /* newline */                                \
      list_macro(is_door, "is_door"),                                   /* newline */                                \
      list_macro(is_dungeon_entrance, "is_dungeon_entrance"),           /* newline */                                \
      list_macro(is_entrance, "is_entrance"),                           /* newline */                                \
      list_macro(is_ethereal, "is_ethereal"),                           /* newline */                                \
      list_macro(is_exit, "is_exit"),                                   /* newline */                                \
      list_macro(is_explosion, "is_explosion"),                         /* newline */                                \
      list_macro(is_extinguished_on_death, "is_extinguished_on_death"), /* newline */                                \
      list_macro(is_fire, "is_fire"),                                   /* newline */                                \
      list_macro(is_floor, "is_floor"),                                 /* newline */                                \
      list_macro(is_foliage, "is_foliage"),                             /* newline */                                \
      list_macro(is_gaseous, "is_gaseous"),                             /* newline */                                \
      list_macro(is_ghost, "is_ghost"),                                 /* newline */                                \
      list_macro(is_goblin, "is_goblin"),                               /* newline */                                \
      list_macro(is_grass, "is_grass"),                                 /* newline */                                \
      list_macro(is_key, "is_key"),                                     /* newline */                                \
      list_macro(is_lava, "is_lava"),                                   /* newline */                                \
      list_macro(is_level_across, "is_level_across"),                   /* newline */                                \
      list_macro(is_level_curr, "is_level_curr"),                       /* newline */                                \
      list_macro(is_level_down, "is_level_down"),                       /* newline */                                \
      list_macro(is_level_final, "is_level_final"),                     /* newline */                                \
      list_macro(is_level_next, "is_level_next"),                       /* newline */                                \
      list_macro(is_level_not_visited, "is_level_not_visited"),         /* newline */                                \
      list_macro(is_level_visited, "is_level_visited"),                 /* newline */                                \
      list_macro(is_levitating, "is_levitating"),                       /* newline */                                \
      list_macro(is_light_source, "is_light_source"),                   /* newline */                                \
      list_macro(is_loggable, "is_loggable"),                           /* newline */                                \
      list_macro(is_minion, "is_minion"),                               /* newline */                                \
      list_macro(is_mob, "is_mob"),                                     /* newline */                                \
      list_macro(is_mob1, "is_mob1"),                                   /* newline */                                \
      list_macro(is_mob2, "is_mob2"),                                   /* newline */                                \
      list_macro(is_monst_group_0, "is_monst_group_0"),                 /* newline */                                \
      list_macro(is_monst_group_1, "is_monst_group_1"),                 /* newline */                                \
      list_macro(is_monst_group_2, "is_monst_group_2"),                 /* newline */                                \
      list_macro(is_monst, "is_monst"),                                 /* newline */                                \
      list_macro(is_obstacle_to_movement, "is_obstacle_to_movement"),   /* newline */                                \
      list_macro(is_pillar, "is_pillar"),                               /* newline */                                \
      list_macro(is_player, "is_player"),                               /* newline */                                \
      list_macro(is_rock, "is_rock"),                                   /* newline */                                \
      list_macro(is_secret_door, "is_secret_door"),                     /* newline */                                \
      list_macro(is_shovable, "is_shovable"),                           /* newline */                                \
      list_macro(is_slime, "is_slime"),                                 /* newline */                                \
      list_macro(is_smoke, "is_smoke"),                                 /* newline */                                \
      list_macro(is_steam, "is_steam"),                                 /* newline */                                \
      list_macro(is_teleport, "is_teleport"),                           /* newline */                                \
      list_macro(is_physics_temperature, "is_physics_temperature"),     /* newline */                                \
      list_macro(is_tickable, "is_tickable"),                           /* newline */                                \
      list_macro(is_tiled, "is_tiled"),                                 /* newline */                                \
      list_macro(is_trap, "is_trap"),                                   /* newline */                                \
      list_macro(is_treasure, "is_treasure"),                           /* newline */                                \
      list_macro(is_undead, "is_undead"),                               /* newline */                                \
      list_macro(is_unused1, "is_unused1"),                             /* newline */                                \
      list_macro(is_unused10, "is_unused10"),                           /* newline */                                \
      list_macro(is_unused11, "is_unused11"),                           /* newline */                                \
      list_macro(is_unused12, "is_unused12"),                           /* newline */                                \
      list_macro(is_unused13, "is_unused13"),                           /* newline */                                \
      list_macro(is_unused14, "is_unused14"),                           /* newline */                                \
      list_macro(is_unused15, "is_unused15"),                           /* newline */                                \
      list_macro(is_unused16, "is_unused16"),                           /* newline */                                \
      list_macro(is_unused17, "is_unused17"),                           /* newline */                                \
      list_macro(is_unused18, "is_unused18"),                           /* newline */                                \
      list_macro(is_unused19, "is_unused19"),                           /* newline */                                \
      list_macro(is_unused2, "is_unused2"),                             /* newline */                                \
      list_macro(is_unused20, "is_unused20"),                           /* newline */                                \
      list_macro(is_unused21, "is_unused21"),                           /* newline */                                \
      list_macro(is_unused22, "is_unused22"),                           /* newline */                                \
      list_macro(is_unused23, "is_unused23"),                           /* newline */                                \
      list_macro(is_unused24, "is_unused24"),                           /* newline */                                \
      list_macro(is_unused25, "is_unused25"),                           /* newline */                                \
      list_macro(is_unused26, "is_unused26"),                           /* newline */                                \
      list_macro(is_unused27, "is_unused27"),                           /* newline */                                \
      list_macro(is_unused28, "is_unused28"),                           /* newline */                                \
      list_macro(is_unused29, "is_unused29"),                           /* newline */                                \
      list_macro(is_unused3, "is_unused3"),                             /* newline */                                \
      list_macro(is_unused30, "is_unused30"),                           /* newline */                                \
      list_macro(is_unused31, "is_unused31"),                           /* newline */                                \
      list_macro(is_obstacle_to_landing, "is_obstacle_to_landing"),     /* newline */                                \
      list_macro(is_submergible, "is_submergible"),                     /* newline */                                \
      list_macro(is_physics_gravity, "is_physics_gravity"),             /* newline */                                \
      list_macro(is_physics_water, "is_physics_water"),                 /* newline */                                \
      list_macro(is_indestructible, "is_indestructible"),               /* newline */                                \
      list_macro(is_floating, "is_floating"),                           /* newline */                                \
      list_macro(is_obstacle_to_fire, "is_obstacle_to_fire"),           /* newline */                                \
      list_macro(is_unused4, "is_unused4"),                             /* newline */                                \
      list_macro(is_unused5, "is_unused5"),                             /* newline */                                \
      list_macro(is_unused6, "is_unused6"),                             /* newline */                                \
      list_macro(is_unused7, "is_unused7"),                             /* newline */                                \
      list_macro(is_unused8, "is_unused8"),                             /* newline */                                \
      list_macro(is_unused9, "is_unused9"),                             /* newline */                                \
      list_macro(is_wait_on_anim_when_dead, "is_wait_on_anim_when_dead"), /* newline */                              \
      list_macro(is_walk_through_walls, "is_walk_through_walls"),         /* newline */                              \
      list_macro(is_wall, "is_wall"),                                     /* newline */                              \
      list_macro(is_water, "is_water"),                                   /* newline */

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

#define FOR_ALL_Z_DEPTH(_z_depth_)                                                                                   \
  for (uint8_t _z_depth_ = MAP_Z_DEPTH_ENUM_FIRST; _z_depth_ < MAP_Z_DEPTH_ENUM_MAX; _z_depth_++)

//
// Monst challenge level
//
#define MONST_GROUP_ENUM(list_macro)                                                                                 \
  clang_format_indent()               /* dummy line for clang indentation fixup */                                   \
      list_macro(MONST_GROUP_0, "0"), /* Used for monsters that are only generated by mobs */                        \
      list_macro(MONST_GROUP_1, "1"), /* newline */                                                                  \
      list_macro(MONST_GROUP_2, "2"), /* newline */

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
// Thing damage enum
//
#define THING_EVENT_ENUM(list_macro)                                                                                 \
  clang_format_indent()                                     /* dummy line for clang indentation fixup */             \
      list_macro(THING_EVENT_CRUSH, "crush"),               /* newline */                                            \
      list_macro(THING_EVENT_FALL, "falling"),              /* newline */                                            \
      list_macro(THING_EVENT_FIRE_DAMAGE, "fire"),          /* newline */                                            \
      list_macro(THING_EVENT_HEAT_DAMAGE, "heat"),          /* newline */                                            \
      list_macro(THING_EVENT_LIFESPAN_EXPIRED, "lifespan"), /* newline */                                            \
      list_macro(THING_EVENT_MELEE_DAMAGE, "melee"),        /* newline */                                            \
      list_macro(THING_EVENT_NONE, "none"),                 /* newline */                                            \
      list_macro(THING_EVENT_SHOVED, "shove"),              /* newline */                                            \
      list_macro(THING_EVENT_WATER_DAMAGE, "water"),        /* newline */

ENUM_DEF_H(THING_EVENT_ENUM, ThingEventType)

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

const char *tp_name(Tpp);

const char *tp_short_name(Tpp);
void        tp_short_name_set(Tpp, const char *);

const char *tp_long_name(Tpp);
void        tp_long_name_set(Tpp, const char *);

const char *tp_real_name(Tpp);
void        tp_real_name_set(Tpp, const char *);

void tp_light_color_set(Tpp, const char *);
void tp_light_color_apply(Tpp);

int   tp_tiles_size(Tpp, ThingAnim);
Tilep tp_first_tile(class Tp *, ThingAnim);
Tilep tp_tiles_get(Tpp, ThingAnim anim_type, int index);
void  tp_tiles_push_back(Tpp, ThingAnim, Tilep val);

void tp_damage_set(Tpp, ThingEventType, const char *);
int  tp_damage(Tpp, ThingEventType);

TpId tp_id_get(Tpp tp);
Tpp  tp_find(TpId id);
Tpp  tp_find_mand(const char *);
Tpp  tp_find_opt(const char *);

Tpp string2tp(const char **s, int *len = nullptr);
Tpp tp_load(const char *);
Tpp tp_random(ThingFlag);
Tpp tp_random_dungeon_entrance(void);
Tpp tp_random_exit(void);
Tpp tp_random_key(void);
Tpp tp_random_monst(int c);
Tpp tp_random_player(void);
Tpp tp_random_wall(void);

void con(Tpp, const char *fmt, ...) CHECK_FORMAT_STR(printf, 2, 3);
void con_(Tpp, const char *fmt, va_list args); // compile error without
void dbg_(Tpp, const char *fmt, ...) CHECK_FORMAT_STR(printf, 2, 3);
void die(Tpp, const char *fmt, ...) CHECK_FORMAT_STR(printf, 2, 3);
void die_(Tpp, const char *fmt, va_list args); // compile error without
void err(Tpp, const char *fmt, ...) CHECK_FORMAT_STR(printf, 2, 3);
void err_(Tpp, const char *fmt, va_list args); // compile error without
void log(Tpp, const char *fmt, ...) CHECK_FORMAT_STR(printf, 2, 3);
void log_(Tpp, const char *fmt, va_list args); // compile error without
void tp_fini(void);
void tp_get_id(const char *, int *id);

bool tp_flag(Tpp, ThingFlag);
void tp_flag_set(Tpp, ThingFlag, bool val = true);

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

void tp_health_initial_set(Tpp, const char *val);
int  tp_health_initial_get(Tpp tp);

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

void tp_value27_set(Tpp, int val);
int  tp_value27_get(Tpp tp);

void tp_value28_set(Tpp, int val);
int  tp_value28_get(Tpp tp);

void tp_value29_set(Tpp, int val);
int  tp_value29_get(Tpp tp);

void tp_lifespan_set(Tpp, const char *val);
int  tp_lifespan_get(Tpp tp);

void tp_is_immunity_add(Tpp, ThingEventType);
bool tp_is_immune_to(Tpp, ThingEventType);

void tp_monst_group_add(Tpp tp, ThingMonstGroup);

// begin sort marker1 {
#define tp_is_able_to_shove(tp)          tp_flag(tp, is_able_to_shove)
#define tp_is_animated_can_hflip(tp)     tp_flag(tp, is_animated_can_hflip)
#define tp_is_animated_no_dir(tp)        tp_flag(tp, is_animated_no_dir)
#define tp_is_animated_sync_first(tp)    tp_flag(tp, is_animated_sync_first)
#define tp_is_animated(tp)               tp_flag(tp, is_animated)
#define tp_is_barrel(tp)                 tp_flag(tp, is_barrel)
#define tp_is_blit_centered(tp)          tp_flag(tp, is_blit_centered)
#define tp_is_blit_on_ground(tp)         tp_flag(tp, is_blit_on_ground)
#define tp_is_blit_outlined(tp)          tp_flag(tp, is_blit_outlined)
#define tp_is_blit_square_outlined(tp)   tp_flag(tp, is_blit_square_outlined)
#define tp_is_brazier(tp)                tp_flag(tp, is_brazier)
#define tp_is_bridge(tp)                 tp_flag(tp, is_bridge)
#define tp_is_broken_on_death(tp)        tp_flag(tp, is_broken_on_death)
#define tp_is_burnable(tp)               tp_flag(tp, is_burnable)
#define tp_is_chasm(tp)                  tp_flag(tp, is_chasm)
#define tp_is_combustible(tp)            tp_flag(tp, is_combustible)
#define tp_is_corpse_on_death(tp)        tp_flag(tp, is_corpse_on_death)
#define tp_is_corridor(tp)               tp_flag(tp, is_corridor)
#define tp_is_crushable(tp)              tp_flag(tp, is_crushable)
#define tp_is_cursor_hazard(tp)          tp_flag(tp, is_cursor_hazard)
#define tp_is_cursor_path_blocker(tp)    tp_flag(tp, is_cursor_path_blocker)
#define tp_is_cursor_path_hazard(tp)     tp_flag(tp, is_cursor_path_hazard)
#define tp_is_cursor_path(tp)            tp_flag(tp, is_cursor_path)
#define tp_is_cursor(tp)                 tp_flag(tp, is_cursor)
#define tp_is_dead_on_shoving(tp)        tp_flag(tp, is_dead_on_shoving)
#define tp_is_deep_water(tp)             tp_flag(tp, is_deep_water)
#define tp_is_described_cursor(tp)       tp_flag(tp, is_described_cursor)
#define tp_is_dirt(tp)                   tp_flag(tp, is_dirt)
#define tp_is_door(tp)                   tp_flag(tp, is_door)
#define tp_is_dungeon_entrance(tp)       tp_flag(tp, is_dungeon_entrance)
#define tp_is_entrance(tp)               tp_flag(tp, is_entrance)
#define tp_is_ethereal(tp)               tp_flag(tp, is_ethereal)
#define tp_is_exit(tp)                   tp_flag(tp, is_exit)
#define tp_is_explosion(tp)              tp_flag(tp, is_explosion)
#define tp_is_extinguished_on_death(tp)  tp_flag(tp, is_extinguished_on_death)
#define tp_is_fire(tp)                   tp_flag(tp, is_fire)
#define tp_is_floating(tp)               tp_flag(tp, is_floating)
#define tp_is_floor(tp)                  tp_flag(tp, is_floor)
#define tp_is_foliage(tp)                tp_flag(tp, is_foliage)
#define tp_is_gaseous(tp)                tp_flag(tp, is_gaseous)
#define tp_is_ghost(tp)                  tp_flag(tp, is_ghost)
#define tp_is_goblin(tp)                 tp_flag(tp, is_goblin)
#define tp_is_grass(tp)                  tp_flag(tp, is_grass)
#define tp_is_indestructible(tp)         tp_flag(tp, is_indestructible)
#define tp_is_key(tp)                    tp_flag(tp, is_key)
#define tp_is_lava(tp)                   tp_flag(tp, is_lava)
#define tp_is_level_across(tp)           tp_flag(tp, is_level_across)
#define tp_is_level_curr(tp)             tp_flag(tp, is_level_curr)
#define tp_is_level_down(tp)             tp_flag(tp, is_level_down)
#define tp_is_level_final(tp)            tp_flag(tp, is_level_final)
#define tp_is_level_next(tp)             tp_flag(tp, is_level_next)
#define tp_is_level_not_visited(tp)      tp_flag(tp, is_level_not_visited)
#define tp_is_level_visited(tp)          tp_flag(tp, is_level_visited)
#define tp_is_levitating(tp)             tp_flag(tp, is_levitating)
#define tp_is_light_source(tp)           tp_flag(tp, is_light_source)
#define tp_is_loggable(tp)               tp_flag(tp, is_loggable)
#define tp_is_minion(tp)                 tp_flag(tp, is_minion)
#define tp_is_mob(tp)                    tp_flag(tp, is_mob)
#define tp_is_mob1(tp)                   tp_flag(tp, is_mob1)
#define tp_is_mob2(tp)                   tp_flag(tp, is_mob2)
#define tp_is_monst_group_0(tp)          tp_flag(tp, is_monst_group_0)
#define tp_is_monst_group_1(tp)          tp_flag(tp, is_monst_group_1)
#define tp_is_monst_group_2(tp)          tp_flag(tp, is_monst_group_2)
#define tp_is_monst(tp)                  tp_flag(tp, is_monst)
#define tp_is_obstacle_to_fire(tp)       tp_flag(tp, is_obstacle_to_fire)
#define tp_is_obstacle_to_landing(tp)    tp_flag(tp, is_obstacle_to_landing)
#define tp_is_obstacle_to_movement(tp)   tp_flag(tp, is_obstacle_to_movement)
#define tp_is_physics_gravity(tp)        tp_flag(tp, is_physics_gravity)
#define tp_is_physics_temperature(tp)    tp_flag(tp, is_physics_temperature)
#define tp_is_physics_water(tp)          tp_flag(tp, is_physics_water)
#define tp_is_pillar(tp)                 tp_flag(tp, is_pillar)
#define tp_is_player(tp)                 tp_flag(tp, is_player)
#define tp_is_rock(tp)                   tp_flag(tp, is_rock)
#define tp_is_secret_door(tp)            tp_flag(tp, is_secret_door)
#define tp_is_shovable(tp)               tp_flag(tp, is_shovable)
#define tp_is_slime(tp)                  tp_flag(tp, is_slime)
#define tp_is_smoke(tp)                  tp_flag(tp, is_smoke)
#define tp_is_steam(tp)                  tp_flag(tp, is_steam)
#define tp_is_submergible(tp)            tp_flag(tp, is_submergible)
#define tp_is_teleport(tp)               tp_flag(tp, is_teleport)
#define tp_is_tickable(tp)               tp_flag(tp, is_tickable)
#define tp_is_tiled(tp)                  tp_flag(tp, is_tiled)
#define tp_is_trap(tp)                   tp_flag(tp, is_trap)
#define tp_is_treasure(tp)               tp_flag(tp, is_treasure)
#define tp_is_undead(tp)                 tp_flag(tp, is_undead)
#define tp_is_unused1(tp)                tp_flag(tp, is_unused1)
#define tp_is_unused10(tp)               tp_flag(tp, is_unused10)
#define tp_is_unused11(tp)               tp_flag(tp, is_unused11)
#define tp_is_unused12(tp)               tp_flag(tp, is_unused12)
#define tp_is_unused13(tp)               tp_flag(tp, is_unused13)
#define tp_is_unused14(tp)               tp_flag(tp, is_unused14)
#define tp_is_unused15(tp)               tp_flag(tp, is_unused15)
#define tp_is_unused16(tp)               tp_flag(tp, is_unused16)
#define tp_is_unused17(tp)               tp_flag(tp, is_unused17)
#define tp_is_unused18(tp)               tp_flag(tp, is_unused18)
#define tp_is_unused19(tp)               tp_flag(tp, is_unused19)
#define tp_is_unused2(tp)                tp_flag(tp, is_unused2)
#define tp_is_unused20(tp)               tp_flag(tp, is_unused20)
#define tp_is_unused21(tp)               tp_flag(tp, is_unused21)
#define tp_is_unused22(tp)               tp_flag(tp, is_unused22)
#define tp_is_unused23(tp)               tp_flag(tp, is_unused23)
#define tp_is_unused24(tp)               tp_flag(tp, is_unused24)
#define tp_is_unused25(tp)               tp_flag(tp, is_unused25)
#define tp_is_unused26(tp)               tp_flag(tp, is_unused26)
#define tp_is_unused27(tp)               tp_flag(tp, is_unused27)
#define tp_is_unused28(tp)               tp_flag(tp, is_unused28)
#define tp_is_unused29(tp)               tp_flag(tp, is_unused29)
#define tp_is_unused3(tp)                tp_flag(tp, is_unused3)
#define tp_is_unused30(tp)               tp_flag(tp, is_unused30)
#define tp_is_unused31(tp)               tp_flag(tp, is_unused31)
#define tp_is_unused4(tp)                tp_flag(tp, is_unused4)
#define tp_is_unused5(tp)                tp_flag(tp, is_unused5)
#define tp_is_unused6(tp)                tp_flag(tp, is_unused6)
#define tp_is_unused7(tp)                tp_flag(tp, is_unused7)
#define tp_is_unused8(tp)                tp_flag(tp, is_unused8)
#define tp_is_unused9(tp)                tp_flag(tp, is_unused9)
#define tp_is_wait_on_anim_when_dead(tp) tp_flag(tp, is_wait_on_anim_when_dead)
#define tp_is_walk_through_walls(tp)     tp_flag(tp, is_walk_through_walls)
#define tp_is_wall(tp)                   tp_flag(tp, is_wall)
#define tp_is_water(tp)                  tp_flag(tp, is_water)
// end sort marker1 }

// begin sort marker3 {
#define level_is_able_to_shove(g, v, l, p)          level_flag(g, v, l, is_able_to_shove, p)
#define level_is_animated_can_hflip(g, v, l, p)     level_flag(g, v, l, is_animated_can_hflip, p)
#define level_is_animated_no_dir(g, v, l, p)        level_flag(g, v, l, is_animated_no_dir, p)
#define level_is_animated_sync_first(g, v, l, p)    level_flag(g, v, l, is_animated_sync_first, p)
#define level_is_animated(g, v, l, p)               level_flag(g, v, l, is_animated, p)
#define level_is_barrel(g, v, l, p)                 level_flag(g, v, l, is_barrel, p)
#define level_is_blit_centered(g, v, l, p)          level_flag(g, v, l, is_blit_centered, p)
#define level_is_blit_on_ground(g, v, l, p)         level_flag(g, v, l, is_blit_on_ground, p)
#define level_is_blit_outlined(g, v, l, p)          level_flag(g, v, l, is_blit_outlined, p)
#define level_is_blit_square_outlined(g, v, l, p)   level_flag(g, v, l, is_blit_square_outlined, p)
#define level_is_brazier(g, v, l, p)                level_flag(g, v, l, is_brazier, p)
#define level_is_bridge(g, v, l, p)                 level_flag(g, v, l, is_bridge, p)
#define level_is_broken_on_death(g, v, l, p)        level_flag(g, v, l, is_broken_on_death, p)
#define level_is_burnable(g, v, l, p)               level_flag(g, v, l, is_burnable, p)
#define level_is_chasm(g, v, l, p)                  level_flag(g, v, l, is_chasm, p)
#define level_is_combustible(g, v, l, p)            level_flag(g, v, l, is_combustible, p)
#define level_is_corpse_on_death(g, v, l, p)        level_flag(g, v, l, is_corpse_on_death, p)
#define level_is_corridor(g, v, l, p)               level_flag(g, v, l, is_corridor, p)
#define level_is_crushable(g, v, l, p)              level_flag(g, v, l, is_crushable, p)
#define level_is_cursor_hazard(g, v, l, p)          level_flag(g, v, l, is_cursor_hazard, p)
#define level_is_cursor_path_blocker(g, v, l, p)    level_flag(g, v, l, is_cursor_path_blocker, p)
#define level_is_cursor_path_hazard(g, v, l, p)     level_flag(g, v, l, is_cursor_path_hazard, p)
#define level_is_cursor_path(g, v, l, p)            level_flag(g, v, l, is_cursor_path, p)
#define level_is_cursor(g, v, l, p)                 level_flag(g, v, l, is_cursor, p)
#define level_is_dead_on_shoving(g, v, l, p)        level_flag(g, v, l, is_dead_on_shoving, p)
#define level_is_deep_water(g, v, l, p)             level_flag(g, v, l, is_deep_water, p)
#define level_is_described_cursor(g, v, l, p)       level_flag(g, v, l, is_described_cursor, p)
#define level_is_dirt(g, v, l, p)                   level_flag(g, v, l, is_dirt, p)
#define level_is_door(g, v, l, p)                   level_flag(g, v, l, is_door, p)
#define level_is_dungeon_entrance(g, v, l, p)       level_flag(g, v, l, is_dungeon_entrance, p)
#define level_is_entrance(g, v, l, p)               level_flag(g, v, l, is_entrance, p)
#define level_is_ethereal(g, v, l, p)               level_flag(g, v, l, is_ethereal, p)
#define level_is_exit(g, v, l, p)                   level_flag(g, v, l, is_exit, p)
#define level_is_explosion(g, v, l, p)              level_flag(g, v, l, is_explosion, p)
#define level_is_extinguished_on_death(g, v, l, p)  level_flag(g, v, l, is_extinguished_on_death, p)
#define level_is_fire(g, v, l, p)                   level_flag(g, v, l, is_fire, p)
#define level_is_floating(g, v, l, p)               level_flag(g, v, l, is_floating, p)
#define level_is_floor(g, v, l, p)                  level_flag(g, v, l, is_floor, p)
#define level_is_foliage(g, v, l, p)                level_flag(g, v, l, is_foliage, p)
#define level_is_gaseous(g, v, l, p)                level_flag(g, v, l, is_gaseous, p)
#define level_is_ghost(g, v, l, p)                  level_flag(g, v, l, is_ghost, p)
#define level_is_goblin(g, v, l, p)                 level_flag(g, v, l, is_goblin, p)
#define level_is_grass(g, v, l, p)                  level_flag(g, v, l, is_grass, p)
#define level_is_indestructible(g, v, l, p)         level_flag(g, v, l, is_indestructible, p)
#define level_is_key(g, v, l, p)                    level_flag(g, v, l, is_key, p)
#define level_is_lava(g, v, l, p)                   level_flag(g, v, l, is_lava, p)
#define level_is_level_across(g, v, l, p)           level_flag(g, v, l, is_level_across, p)
#define level_is_level_curr(g, v, l, p)             level_flag(g, v, l, is_level_curr, p)
#define level_is_level_down(g, v, l, p)             level_flag(g, v, l, is_level_down, p)
#define level_is_level_final(g, v, l, p)            level_flag(g, v, l, is_level_final, p)
#define level_is_level_next(g, v, l, p)             level_flag(g, v, l, is_level_next, p)
#define level_is_level_not_visited(g, v, l, p)      level_flag(g, v, l, is_level_not_visited, p)
#define level_is_level_visited(g, v, l, p)          level_flag(g, v, l, is_level_visited, p)
#define level_is_levitating(g, v, l, p)             level_flag(g, v, l, is_levitating, p)
#define level_is_light_source(g, v, l, p)           level_flag(g, v, l, is_light_source, p)
#define level_is_loggable(g, v, l, p)               level_flag(g, v, l, is_loggable, p)
#define level_is_minion(g, v, l, p)                 level_flag(g, v, l, is_minion, p)
#define level_is_mob(g, v, l, p)                    level_flag(g, v, l, is_mob, p)
#define level_is_mob1(g, v, l, p)                   level_flag(g, v, l, is_mob1, p)
#define level_is_mob2(g, v, l, p)                   level_flag(g, v, l, is_mob2, p)
#define level_is_monst_group_0(g, v, l, p)          level_flag(g, v, l, is_monst_group_0, p)
#define level_is_monst_group_1(g, v, l, p)          level_flag(g, v, l, is_monst_group_1, p)
#define level_is_monst_group_2(g, v, l, p)          level_flag(g, v, l, is_monst_group_2, p)
#define level_is_monst(g, v, l, p)                  level_flag(g, v, l, is_monst, p)
#define level_is_obstacle_to_fire(g, v, l, p)       level_flag(g, v, l, is_obstacle_to_fire, p)
#define level_is_obstacle_to_landing(g, v, l, p)    level_flag(g, v, l, is_obstacle_to_landing, p)
#define level_is_obstacle_to_movement(g, v, l, p)   level_flag(g, v, l, is_obstacle_to_movement, p)
#define level_is_physics_gravity(g, v, l, p)        level_flag(g, v, l, is_physics_gravity, p)
#define level_is_physics_temperature(g, v, l, p)    level_flag(g, v, l, is_physics_temperature, p)
#define level_is_physics_water(g, v, l, p)          level_flag(g, v, l, is_physics_water, p)
#define level_is_pillar(g, v, l, p)                 level_flag(g, v, l, is_pillar, p)
#define level_is_player(g, v, l, p)                 level_flag(g, v, l, is_player, p)
#define level_is_rock(g, v, l, p)                   level_flag(g, v, l, is_rock, p)
#define level_is_secret_door(g, v, l, p)            level_flag(g, v, l, is_secret_door, p)
#define level_is_shovable(g, v, l, p)               level_flag(g, v, l, is_shovable, p)
#define level_is_slime(g, v, l, p)                  level_flag(g, v, l, is_slime, p)
#define level_is_smoke(g, v, l, p)                  level_flag(g, v, l, is_smoke, p)
#define level_is_steam(g, v, l, p)                  level_flag(g, v, l, is_steam, p)
#define level_is_submergible(g, v, l, p)            level_flag(g, v, l, is_submergible, p)
#define level_is_teleport(g, v, l, p)               level_flag(g, v, l, is_teleport, p)
#define level_is_tickable(g, v, l, p)               level_flag(g, v, l, is_tickable, p)
#define level_is_tiled(g, v, l, p)                  level_flag(g, v, l, is_tiled, p)
#define level_is_trap(g, v, l, p)                   level_flag(g, v, l, is_trap, p)
#define level_is_treasure(g, v, l, p)               level_flag(g, v, l, is_treasure, p)
#define level_is_undead(g, v, l, p)                 level_flag(g, v, l, is_undead, p)
#define level_is_unused1(g, v, l, p)                level_flag(g, v, l, is_unused1, p)
#define level_is_unused10(g, v, l, p)               level_flag(g, v, l, is_unused10, p)
#define level_is_unused11(g, v, l, p)               level_flag(g, v, l, is_unused11, p)
#define level_is_unused12(g, v, l, p)               level_flag(g, v, l, is_unused12, p)
#define level_is_unused13(g, v, l, p)               level_flag(g, v, l, is_unused13, p)
#define level_is_unused14(g, v, l, p)               level_flag(g, v, l, is_unused14, p)
#define level_is_unused15(g, v, l, p)               level_flag(g, v, l, is_unused15, p)
#define level_is_unused16(g, v, l, p)               level_flag(g, v, l, is_unused16, p)
#define level_is_unused17(g, v, l, p)               level_flag(g, v, l, is_unused17, p)
#define level_is_unused18(g, v, l, p)               level_flag(g, v, l, is_unused18, p)
#define level_is_unused19(g, v, l, p)               level_flag(g, v, l, is_unused19, p)
#define level_is_unused2(g, v, l, p)                level_flag(g, v, l, is_unused2, p)
#define level_is_unused20(g, v, l, p)               level_flag(g, v, l, is_unused20, p)
#define level_is_unused21(g, v, l, p)               level_flag(g, v, l, is_unused21, p)
#define level_is_unused22(g, v, l, p)               level_flag(g, v, l, is_unused22, p)
#define level_is_unused23(g, v, l, p)               level_flag(g, v, l, is_unused23, p)
#define level_is_unused24(g, v, l, p)               level_flag(g, v, l, is_unused24, p)
#define level_is_unused25(g, v, l, p)               level_flag(g, v, l, is_unused25, p)
#define level_is_unused26(g, v, l, p)               level_flag(g, v, l, is_unused26, p)
#define level_is_unused27(g, v, l, p)               level_flag(g, v, l, is_unused27, p)
#define level_is_unused28(g, v, l, p)               level_flag(g, v, l, is_unused28, p)
#define level_is_unused29(g, v, l, p)               level_flag(g, v, l, is_unused29, p)
#define level_is_unused3(g, v, l, p)                level_flag(g, v, l, is_unused3, p)
#define level_is_unused30(g, v, l, p)               level_flag(g, v, l, is_unused30, p)
#define level_is_unused31(g, v, l, p)               level_flag(g, v, l, is_unused31, p)
#define level_is_unused4(g, v, l, p)                level_flag(g, v, l, is_unused4, p)
#define level_is_unused5(g, v, l, p)                level_flag(g, v, l, is_unused5, p)
#define level_is_unused6(g, v, l, p)                level_flag(g, v, l, is_unused6, p)
#define level_is_unused7(g, v, l, p)                level_flag(g, v, l, is_unused7, p)
#define level_is_unused8(g, v, l, p)                level_flag(g, v, l, is_unused8, p)
#define level_is_unused9(g, v, l, p)                level_flag(g, v, l, is_unused9, p)
#define level_is_wait_on_anim_when_dead(g, v, l, p) level_flag(g, v, l, is_wait_on_anim_when_dead, p)
#define level_is_walk_through_walls(g, v, l, p)     level_flag(g, v, l, is_walk_through_walls, p)
#define level_is_wall(g, v, l, p)                   level_flag(g, v, l, is_wall, p)
#define level_is_water(g, v, l, p)                  level_flag(g, v, l, is_water, p)
// end sort marker3 }

// begin sort marker4 {
#define level_is_alive_able_to_shove(g, v, l, p)          level_alive_and_flag(g, v, l, is_able_to_shove, p)
#define level_is_alive_animated_can_hflip(g, v, l, p)     level_alive_and_flag(g, v, l, is_animated_can_hflip, p)
#define level_is_alive_animated_no_dir(g, v, l, p)        level_alive_and_flag(g, v, l, is_animated_no_dir, p)
#define level_is_alive_animated_sync_first(g, v, l, p)    level_alive_and_flag(g, v, l, is_animated_sync_first, p)
#define level_is_alive_animated(g, v, l, p)               level_alive_and_flag(g, v, l, is_animated, p)
#define level_is_alive_barrel(g, v, l, p)                 level_alive_and_flag(g, v, l, is_barrel, p)
#define level_is_alive_blit_centered(g, v, l, p)          level_alive_and_flag(g, v, l, is_blit_centered, p)
#define level_is_alive_blit_on_ground(g, v, l, p)         level_alive_and_flag(g, v, l, is_blit_on_ground, p)
#define level_is_alive_blit_outlined(g, v, l, p)          level_alive_and_flag(g, v, l, is_blit_outlined, p)
#define level_is_alive_blit_square_outlined(g, v, l, p)   level_alive_and_flag(g, v, l, is_blit_square_outlined, p)
#define level_is_alive_brazier(g, v, l, p)                level_alive_and_flag(g, v, l, is_brazier, p)
#define level_is_alive_bridge(g, v, l, p)                 level_alive_and_flag(g, v, l, is_bridge, p)
#define level_is_alive_broken_on_death(g, v, l, p)        level_alive_and_flag(g, v, l, is_broken_on_death, p)
#define level_is_alive_burnable(g, v, l, p)               level_alive_and_flag(g, v, l, is_burnable, p)
#define level_is_alive_chasm(g, v, l, p)                  level_alive_and_flag(g, v, l, is_chasm, p)
#define level_is_alive_combustible(g, v, l, p)            level_alive_and_flag(g, v, l, is_combustible, p)
#define level_is_alive_corpse_on_death(g, v, l, p)        level_alive_and_flag(g, v, l, is_corpse_on_death, p)
#define level_is_alive_corridor(g, v, l, p)               level_alive_and_flag(g, v, l, is_corridor, p)
#define level_is_alive_crushable_underfoot(g, v, l, p)    level_alive_and_flag(g, v, l, is_crushable, p)
#define level_is_alive_cursor_hazard(g, v, l, p)          level_alive_and_flag(g, v, l, is_cursor_hazard, p)
#define level_is_alive_cursor_path_blocker(g, v, l, p)    level_alive_and_flag(g, v, l, is_cursor_path_blocker, p)
#define level_is_alive_cursor_path_hazard(g, v, l, p)     level_alive_and_flag(g, v, l, is_cursor_path_hazard, p)
#define level_is_alive_cursor_path(g, v, l, p)            level_alive_and_flag(g, v, l, is_cursor_path, p)
#define level_is_alive_cursor(g, v, l, p)                 level_alive_and_flag(g, v, l, is_cursor, p)
#define level_is_alive_dead_on_shoving(g, v, l, p)        level_alive_and_flag(g, v, l, is_dead_on_shoving, p)
#define level_is_alive_deep_water(g, v, l, p)             level_alive_and_flag(g, v, l, is_deep_water, p)
#define level_is_alive_described_cursor(g, v, l, p)       level_alive_and_flag(g, v, l, is_described_cursor, p)
#define level_is_alive_dirt(g, v, l, p)                   level_alive_and_flag(g, v, l, is_dirt, p)
#define level_is_alive_door(g, v, l, p)                   level_alive_and_flag(g, v, l, is_door, p)
#define level_is_alive_dungeon_entrance(g, v, l, p)       level_alive_and_flag(g, v, l, is_dungeon_entrance, p)
#define level_is_alive_entrance(g, v, l, p)               level_alive_and_flag(g, v, l, is_entrance, p)
#define level_is_alive_ethereal(g, v, l, p)               level_alive_and_flag(g, v, l, is_ethereal, p)
#define level_is_alive_exit(g, v, l, p)                   level_alive_and_flag(g, v, l, is_exit, p)
#define level_is_alive_explosion(g, v, l, p)              level_alive_and_flag(g, v, l, is_explosion, p)
#define level_is_alive_extinguished_on_death(g, v, l, p)  level_alive_and_flag(g, v, l, is_extinguished_on_death, p)
#define level_is_alive_fire(g, v, l, p)                   level_alive_and_flag(g, v, l, is_fire, p)
#define level_is_alive_floor(g, v, l, p)                  level_alive_and_flag(g, v, l, is_floor, p)
#define level_is_alive_foliage(g, v, l, p)                level_alive_and_flag(g, v, l, is_foliage, p)
#define level_is_alive_gaseous(g, v, l, p)                level_alive_and_flag(g, v, l, is_gaseous, p)
#define level_is_alive_ghost(g, v, l, p)                  level_alive_and_flag(g, v, l, is_ghost, p)
#define level_is_alive_goblin(g, v, l, p)                 level_alive_and_flag(g, v, l, is_goblin, p)
#define level_is_alive_grass(g, v, l, p)                  level_alive_and_flag(g, v, l, is_grass, p)
#define level_is_alive_key(g, v, l, p)                    level_alive_and_flag(g, v, l, is_key, p)
#define level_is_alive_lava(g, v, l, p)                   level_alive_and_flag(g, v, l, is_lava, p)
#define level_is_alive_level_across(g, v, l, p)           level_alive_and_flag(g, v, l, is_level_across, p)
#define level_is_alive_level_curr(g, v, l, p)             level_alive_and_flag(g, v, l, is_level_curr, p)
#define level_is_alive_level_down(g, v, l, p)             level_alive_and_flag(g, v, l, is_level_down, p)
#define level_is_alive_level_final(g, v, l, p)            level_alive_and_flag(g, v, l, is_level_final, p)
#define level_is_alive_level_next(g, v, l, p)             level_alive_and_flag(g, v, l, is_level_next, p)
#define level_is_alive_level_not_visited(g, v, l, p)      level_alive_and_flag(g, v, l, is_level_not_visited, p)
#define level_is_alive_level_visited(g, v, l, p)          level_alive_and_flag(g, v, l, is_level_visited, p)
#define level_is_alive_levitating(g, v, l, p)             level_alive_and_flag(g, v, l, is_levitating, p)
#define level_is_alive_light_source(g, v, l, p)           level_alive_and_flag(g, v, l, is_light_source, p)
#define level_is_alive_loggable(g, v, l, p)               level_alive_and_flag(g, v, l, is_loggable, p)
#define level_is_alive_minion(g, v, l, p)                 level_alive_and_flag(g, v, l, is_minion, p)
#define level_is_alive_mob(g, v, l, p)                    level_alive_and_flag(g, v, l, is_mob, p)
#define level_is_alive_mob1(g, v, l, p)                   level_alive_and_flag(g, v, l, is_mob1, p)
#define level_is_alive_mob2(g, v, l, p)                   level_alive_and_flag(g, v, l, is_mob2, p)
#define level_is_alive_monst_group_0(g, v, l, p)          level_alive_and_flag(g, v, l, is_monst_group_0, p)
#define level_is_alive_monst_group_1(g, v, l, p)          level_alive_and_flag(g, v, l, is_monst_group_1, p)
#define level_is_alive_monst_group_2(g, v, l, p)          level_alive_and_flag(g, v, l, is_monst_group_2, p)
#define level_is_alive_monst(g, v, l, p)                  level_alive_and_flag(g, v, l, is_monst, p)
#define level_is_alive_obstacle_block(g, v, l, p)         level_alive_and_flag(g, v, l, is_obstacle_to_movement, p)
#define level_is_alive_physics_temperature(g, v, l, p)    level_alive_and_flag(g, v, l, is_physics_temperature, p)
#define level_is_alive_pillar(g, v, l, p)                 level_alive_and_flag(g, v, l, is_pillar, p)
#define level_is_alive_player(g, v, l, p)                 level_alive_and_flag(g, v, l, is_player, p)
#define level_is_alive_rock(g, v, l, p)                   level_alive_and_flag(g, v, l, is_rock, p)
#define level_is_alive_secret_door(g, v, l, p)            level_alive_and_flag(g, v, l, is_secret_door, p)
#define level_is_alive_shovable(g, v, l, p)               level_alive_and_flag(g, v, l, is_shovable, p)
#define level_is_alive_slime(g, v, l, p)                  level_alive_and_flag(g, v, l, is_slime, p)
#define level_is_alive_smoke(g, v, l, p)                  level_alive_and_flag(g, v, l, is_smoke, p)
#define level_is_alive_steam(g, v, l, p)                  level_alive_and_flag(g, v, l, is_steam, p)
#define level_is_alive_teleport(g, v, l, p)               level_alive_and_flag(g, v, l, is_teleport, p)
#define level_is_alive_tickable(g, v, l, p)               level_alive_and_flag(g, v, l, is_tickable, p)
#define level_is_alive_tiled(g, v, l, p)                  level_alive_and_flag(g, v, l, is_tiled, p)
#define level_is_alive_trap(g, v, l, p)                   level_alive_and_flag(g, v, l, is_trap, p)
#define level_is_alive_treasure(g, v, l, p)               level_alive_and_flag(g, v, l, is_treasure, p)
#define level_is_alive_undead(g, v, l, p)                 level_alive_and_flag(g, v, l, is_undead, p)
#define level_is_alive_unused1(g, v, l, p)                level_alive_and_flag(g, v, l, is_unused1, p)
#define level_is_alive_unused10(g, v, l, p)               level_alive_and_flag(g, v, l, is_unused10, p)
#define level_is_alive_unused11(g, v, l, p)               level_alive_and_flag(g, v, l, is_unused11, p)
#define level_is_alive_unused12(g, v, l, p)               level_alive_and_flag(g, v, l, is_unused12, p)
#define level_is_alive_unused13(g, v, l, p)               level_alive_and_flag(g, v, l, is_unused13, p)
#define level_is_alive_unused14(g, v, l, p)               level_alive_and_flag(g, v, l, is_unused14, p)
#define level_is_alive_unused15(g, v, l, p)               level_alive_and_flag(g, v, l, is_unused15, p)
#define level_is_alive_unused16(g, v, l, p)               level_alive_and_flag(g, v, l, is_unused16, p)
#define level_is_alive_unused17(g, v, l, p)               level_alive_and_flag(g, v, l, is_unused17, p)
#define level_is_alive_unused18(g, v, l, p)               level_alive_and_flag(g, v, l, is_unused18, p)
#define level_is_alive_unused19(g, v, l, p)               level_alive_and_flag(g, v, l, is_unused19, p)
#define level_is_alive_unused2(g, v, l, p)                level_alive_and_flag(g, v, l, is_unused2, p)
#define level_is_alive_unused20(g, v, l, p)               level_alive_and_flag(g, v, l, is_unused20, p)
#define level_is_alive_unused21(g, v, l, p)               level_alive_and_flag(g, v, l, is_unused21, p)
#define level_is_alive_unused22(g, v, l, p)               level_alive_and_flag(g, v, l, is_unused22, p)
#define level_is_alive_unused23(g, v, l, p)               level_alive_and_flag(g, v, l, is_unused23, p)
#define level_is_alive_unused24(g, v, l, p)               level_alive_and_flag(g, v, l, is_unused24, p)
#define level_is_alive_unused25(g, v, l, p)               level_alive_and_flag(g, v, l, is_unused25, p)
#define level_is_alive_unused26(g, v, l, p)               level_alive_and_flag(g, v, l, is_unused26, p)
#define level_is_alive_unused27(g, v, l, p)               level_alive_and_flag(g, v, l, is_unused27, p)
#define level_is_alive_unused28(g, v, l, p)               level_alive_and_flag(g, v, l, is_unused28, p)
#define level_is_alive_unused29(g, v, l, p)               level_alive_and_flag(g, v, l, is_unused29, p)
#define level_is_alive_unused3(g, v, l, p)                level_alive_and_flag(g, v, l, is_unused3, p)
#define level_is_alive_unused30(g, v, l, p)               level_alive_and_flag(g, v, l, is_unused30, p)
#define level_is_alive_unused31(g, v, l, p)               level_alive_and_flag(g, v, l, is_unused31, p)
#define level_is_alive_unused32(g, v, l, p)               level_alive_and_flag(g, v, l, is_obstacle_to_landing, p)
#define level_is_alive_unused33(g, v, l, p)               level_alive_and_flag(g, v, l, is_submergible, p)
#define level_is_alive_unused34(g, v, l, p)               level_alive_and_flag(g, v, l, is_physics_gravity, p)
#define level_is_alive_unused35(g, v, l, p)               level_alive_and_flag(g, v, l, is_physics_water, p)
#define level_is_alive_unused36(g, v, l, p)               level_alive_and_flag(g, v, l, is_indestructible, p)
#define level_is_alive_unused37(g, v, l, p)               level_alive_and_flag(g, v, l, is_floating, p)
#define level_is_alive_unused38(g, v, l, p)               level_alive_and_flag(g, v, l, is_obstacle_to_fire, p)
#define level_is_alive_unused4(g, v, l, p)                level_alive_and_flag(g, v, l, is_unused4, p)
#define level_is_alive_unused5(g, v, l, p)                level_alive_and_flag(g, v, l, is_unused5, p)
#define level_is_alive_unused6(g, v, l, p)                level_alive_and_flag(g, v, l, is_unused6, p)
#define level_is_alive_unused7(g, v, l, p)                level_alive_and_flag(g, v, l, is_unused7, p)
#define level_is_alive_unused8(g, v, l, p)                level_alive_and_flag(g, v, l, is_unused8, p)
#define level_is_alive_unused9(g, v, l, p)                level_alive_and_flag(g, v, l, is_unused9, p)
#define level_is_alive_wait_on_anim_when_dead(g, v, l, p) level_alive_and_flag(g, v, l, is_wait_on_anim_when_dead, p)
#define level_is_alive_walk_through_walls(g, v, l, p)     level_alive_and_flag(g, v, l, is_walk_through_walls, p)
#define level_is_alive_wall(g, v, l, p)                   level_alive_and_flag(g, v, l, is_wall, p)
#define level_is_alive_water(g, v, l, p)                  level_alive_and_flag(g, v, l, is_water, p)
// end sort marker4 }

// begin sort marker5 {
#define level_first_able_to_shove(g, v, l, p)          level_first_with_flag(g, v, l, is_able_to_shove, p)
#define level_first_animated_can_hflip(g, v, l, p)     level_first_with_flag(g, v, l, is_animated_can_hflip, p)
#define level_first_animated_no_dir(g, v, l, p)        level_first_with_flag(g, v, l, is_animated_no_dir, p)
#define level_first_animated_sync_first(g, v, l, p)    level_first_with_flag(g, v, l, is_animated_sync_first, p)
#define level_first_animated(g, v, l, p)               level_first_with_flag(g, v, l, is_animated, p)
#define level_first_barrel(g, v, l, p)                 level_first_with_flag(g, v, l, is_barrel, p)
#define level_first_blit_centered(g, v, l, p)          level_first_with_flag(g, v, l, is_blit_centered, p)
#define level_first_blit_on_ground(g, v, l, p)         level_first_with_flag(g, v, l, is_blit_on_ground, p)
#define level_first_blit_outlined(g, v, l, p)          level_first_with_flag(g, v, l, is_blit_outlined, p)
#define level_first_blit_square_outlined(g, v, l, p)   level_first_with_flag(g, v, l, is_blit_square_outlined, p)
#define level_first_brazier(g, v, l, p)                level_first_with_flag(g, v, l, is_brazier, p)
#define level_first_bridge(g, v, l, p)                 level_first_with_flag(g, v, l, is_bridge, p)
#define level_first_broken_on_death(g, v, l, p)        level_first_with_flag(g, v, l, is_broken_on_death, p)
#define level_first_burnable(g, v, l, p)               level_first_with_flag(g, v, l, is_burnable, p)
#define level_first_chasm(g, v, l, p)                  level_first_with_flag(g, v, l, is_chasm, p)
#define level_first_combustible(g, v, l, p)            level_first_with_flag(g, v, l, is_combustible, p)
#define level_first_corpse_on_death(g, v, l, p)        level_first_with_flag(g, v, l, is_corpse_on_death, p)
#define level_first_corridor(g, v, l, p)               level_first_with_flag(g, v, l, is_corridor, p)
#define level_first_crushable_underfoot(g, v, l, p)    level_first_with_flag(g, v, l, is_crushable, p)
#define level_first_cursor_hazard(g, v, l, p)          level_first_with_flag(g, v, l, is_cursor_hazard, p)
#define level_first_cursor_path_blocker(g, v, l, p)    level_first_with_flag(g, v, l, is_cursor_path_blocker, p)
#define level_first_cursor_path_hazard(g, v, l, p)     level_first_with_flag(g, v, l, is_cursor_path_hazard, p)
#define level_first_cursor_path(g, v, l, p)            level_first_with_flag(g, v, l, is_cursor_path, p)
#define level_first_cursor(g, v, l, p)                 level_first_with_flag(g, v, l, is_cursor, p)
#define level_first_dead_on_shoving(g, v, l, p)        level_first_with_flag(g, v, l, is_dead_on_shoving, p)
#define level_first_deep_water(g, v, l, p)             level_first_with_flag(g, v, l, is_deep_water, p)
#define level_first_described_cursor(g, v, l, p)       level_first_with_flag(g, v, l, is_described_cursor, p)
#define level_first_dirt(g, v, l, p)                   level_first_with_flag(g, v, l, is_dirt, p)
#define level_first_door(g, v, l, p)                   level_first_with_flag(g, v, l, is_door, p)
#define level_first_dungeon_entrance(g, v, l, p)       level_first_with_flag(g, v, l, is_dungeon_entrance, p)
#define level_first_entrance(g, v, l, p)               level_first_with_flag(g, v, l, is_entrance, p)
#define level_first_ethereal(g, v, l, p)               level_first_with_flag(g, v, l, is_ethereal, p)
#define level_first_exit(g, v, l, p)                   level_first_with_flag(g, v, l, is_exit, p)
#define level_first_explosion(g, v, l, p)              level_first_with_flag(g, v, l, is_explosion, p)
#define level_first_extinguished_on_death(g, v, l, p)  level_first_with_flag(g, v, l, is_extinguished_on_death, p)
#define level_first_fire(g, v, l, p)                   level_first_with_flag(g, v, l, is_fire, p)
#define level_first_floor(g, v, l, p)                  level_first_with_flag(g, v, l, is_floor, p)
#define level_first_foliage(g, v, l, p)                level_first_with_flag(g, v, l, is_foliage, p)
#define level_first_gaseous(g, v, l, p)                level_first_with_flag(g, v, l, is_gaseous, p)
#define level_first_ghost(g, v, l, p)                  level_first_with_flag(g, v, l, is_ghost, p)
#define level_first_goblin(g, v, l, p)                 level_first_with_flag(g, v, l, is_goblin, p)
#define level_first_grass(g, v, l, p)                  level_first_with_flag(g, v, l, is_grass, p)
#define level_first_key(g, v, l, p)                    level_first_with_flag(g, v, l, is_key, p)
#define level_first_lava(g, v, l, p)                   level_first_with_flag(g, v, l, is_lava, p)
#define level_first_level_across(g, v, l, p)           level_first_with_flag(g, v, l, is_level_across, p)
#define level_first_level_curr(g, v, l, p)             level_first_with_flag(g, v, l, is_level_curr, p)
#define level_first_level_down(g, v, l, p)             level_first_with_flag(g, v, l, is_level_down, p)
#define level_first_level_final(g, v, l, p)            level_first_with_flag(g, v, l, is_level_final, p)
#define level_first_level_next(g, v, l, p)             level_first_with_flag(g, v, l, is_level_next, p)
#define level_first_level_not_visited(g, v, l, p)      level_first_with_flag(g, v, l, is_level_not_visited, p)
#define level_first_level_visited(g, v, l, p)          level_first_with_flag(g, v, l, is_level_visited, p)
#define level_first_levitating(g, v, l, p)             level_first_with_flag(g, v, l, is_levitating, p)
#define level_first_light_source(g, v, l, p)           level_first_with_flag(g, v, l, is_light_source, p)
#define level_first_loggable(g, v, l, p)               level_first_with_flag(g, v, l, is_loggable, p)
#define level_first_minion(g, v, l, p)                 level_first_with_flag(g, v, l, is_minion, p)
#define level_first_mob(g, v, l, p)                    level_first_with_flag(g, v, l, is_mob, p)
#define level_first_mob1(g, v, l, p)                   level_first_with_flag(g, v, l, is_mob1, p)
#define level_first_mob2(g, v, l, p)                   level_first_with_flag(g, v, l, is_mob2, p)
#define level_first_monst_group_0(g, v, l, p)          level_first_with_flag(g, v, l, is_monst_group_0, p)
#define level_first_monst_group_1(g, v, l, p)          level_first_with_flag(g, v, l, is_monst_group_1, p)
#define level_first_monst_group_2(g, v, l, p)          level_first_with_flag(g, v, l, is_monst_group_2, p)
#define level_first_monst(g, v, l, p)                  level_first_with_flag(g, v, l, is_monst, p)
#define level_first_obstacle_block(g, v, l, p)         level_first_with_flag(g, v, l, is_obstacle_to_movement, p)
#define level_first_physics_temperature(g, v, l, p)    level_first_with_flag(g, v, l, is_physics_temperature, p)
#define level_first_pillar(g, v, l, p)                 level_first_with_flag(g, v, l, is_pillar, p)
#define level_first_player(g, v, l, p)                 level_first_with_flag(g, v, l, is_player, p)
#define level_first_rock(g, v, l, p)                   level_first_with_flag(g, v, l, is_rock, p)
#define level_first_secret_door(g, v, l, p)            level_first_with_flag(g, v, l, is_secret_door, p)
#define level_first_shovable(g, v, l, p)               level_first_with_flag(g, v, l, is_shovable, p)
#define level_first_slime(g, v, l, p)                  level_first_with_flag(g, v, l, is_slime, p)
#define level_first_smoke(g, v, l, p)                  level_first_with_flag(g, v, l, is_smoke, p)
#define level_first_steam(g, v, l, p)                  level_first_with_flag(g, v, l, is_steam, p)
#define level_first_teleport(g, v, l, p)               level_first_with_flag(g, v, l, is_teleport, p)
#define level_first_tickable(g, v, l, p)               level_first_with_flag(g, v, l, is_tickable, p)
#define level_first_tiled(g, v, l, p)                  level_first_with_flag(g, v, l, is_tiled, p)
#define level_first_trap(g, v, l, p)                   level_first_with_flag(g, v, l, is_trap, p)
#define level_first_treasure(g, v, l, p)               level_first_with_flag(g, v, l, is_treasure, p)
#define level_first_undead(g, v, l, p)                 level_first_with_flag(g, v, l, is_undead, p)
#define level_first_unused1(g, v, l, p)                level_first_with_flag(g, v, l, is_unused1, p)
#define level_first_unused10(g, v, l, p)               level_first_with_flag(g, v, l, is_unused10, p)
#define level_first_unused11(g, v, l, p)               level_first_with_flag(g, v, l, is_unused11, p)
#define level_first_unused12(g, v, l, p)               level_first_with_flag(g, v, l, is_unused12, p)
#define level_first_unused13(g, v, l, p)               level_first_with_flag(g, v, l, is_unused13, p)
#define level_first_unused14(g, v, l, p)               level_first_with_flag(g, v, l, is_unused14, p)
#define level_first_unused15(g, v, l, p)               level_first_with_flag(g, v, l, is_unused15, p)
#define level_first_unused16(g, v, l, p)               level_first_with_flag(g, v, l, is_unused16, p)
#define level_first_unused17(g, v, l, p)               level_first_with_flag(g, v, l, is_unused17, p)
#define level_first_unused18(g, v, l, p)               level_first_with_flag(g, v, l, is_unused18, p)
#define level_first_unused19(g, v, l, p)               level_first_with_flag(g, v, l, is_unused19, p)
#define level_first_unused2(g, v, l, p)                level_first_with_flag(g, v, l, is_unused2, p)
#define level_first_unused20(g, v, l, p)               level_first_with_flag(g, v, l, is_unused20, p)
#define level_first_unused21(g, v, l, p)               level_first_with_flag(g, v, l, is_unused21, p)
#define level_first_unused22(g, v, l, p)               level_first_with_flag(g, v, l, is_unused22, p)
#define level_first_unused23(g, v, l, p)               level_first_with_flag(g, v, l, is_unused23, p)
#define level_first_unused24(g, v, l, p)               level_first_with_flag(g, v, l, is_unused24, p)
#define level_first_unused25(g, v, l, p)               level_first_with_flag(g, v, l, is_unused25, p)
#define level_first_unused26(g, v, l, p)               level_first_with_flag(g, v, l, is_unused26, p)
#define level_first_unused27(g, v, l, p)               level_first_with_flag(g, v, l, is_unused27, p)
#define level_first_unused28(g, v, l, p)               level_first_with_flag(g, v, l, is_unused28, p)
#define level_first_unused29(g, v, l, p)               level_first_with_flag(g, v, l, is_unused29, p)
#define level_first_unused3(g, v, l, p)                level_first_with_flag(g, v, l, is_unused3, p)
#define level_first_unused30(g, v, l, p)               level_first_with_flag(g, v, l, is_unused30, p)
#define level_first_unused31(g, v, l, p)               level_first_with_flag(g, v, l, is_unused31, p)
#define level_first_unused32(g, v, l, p)               level_first_with_flag(g, v, l, is_obstacle_to_landing, p)
#define level_first_unused33(g, v, l, p)               level_first_with_flag(g, v, l, is_submergible, p)
#define level_first_unused34(g, v, l, p)               level_first_with_flag(g, v, l, is_physics_gravity, p)
#define level_first_unused35(g, v, l, p)               level_first_with_flag(g, v, l, is_physics_water, p)
#define level_first_unused36(g, v, l, p)               level_first_with_flag(g, v, l, is_indestructible, p)
#define level_first_unused37(g, v, l, p)               level_first_with_flag(g, v, l, is_floating, p)
#define level_first_unused38(g, v, l, p)               level_first_with_flag(g, v, l, is_obstacle_to_fire, p)
#define level_first_unused4(g, v, l, p)                level_first_with_flag(g, v, l, is_unused4, p)
#define level_first_unused5(g, v, l, p)                level_first_with_flag(g, v, l, is_unused5, p)
#define level_first_unused6(g, v, l, p)                level_first_with_flag(g, v, l, is_unused6, p)
#define level_first_unused7(g, v, l, p)                level_first_with_flag(g, v, l, is_unused7, p)
#define level_first_unused8(g, v, l, p)                level_first_with_flag(g, v, l, is_unused8, p)
#define level_first_unused9(g, v, l, p)                level_first_with_flag(g, v, l, is_unused9, p)
#define level_first_wait_on_anim_when_dead(g, v, l, p) level_first_with_flag(g, v, l, is_wait_on_anim_when_dead, p)
#define level_first_walk_through_walls(g, v, l, p)     level_first_with_flag(g, v, l, is_walk_through_walls, p)
#define level_first_wall(g, v, l, p)                   level_first_with_flag(g, v, l, is_wall, p)
#define level_first_water(g, v, l, p)                  level_first_with_flag(g, v, l, is_water, p)
// end sort marker5 }

#endif // _MY_THING_TEMPLATE_H_
