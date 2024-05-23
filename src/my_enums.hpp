//
// Copyright Neil McGill, goblinhack@gmail.com
//

#pragma once
#ifndef _MY_ENUMS_HPP_
#define _MY_ENUMS_HPP_

#include "my_enum.hpp"

enum {
  TILE_LAYER_BG_0,
  TILE_LAYER_BG_1,
  TILE_LAYER_FG_0,
  TILE_LAYER_FG_1,
  TILE_LAYER_FG_2,
  TILE_LAYER_FG_3,
  TILE_LAYER_FG_4,
  TILE_LAYER_FG_5,
  TILE_LAYER_FG_6,
  TILE_LAYER_FG_7,
  TILE_LAYER_FG_8,
  TILE_LAYER_FG_9,
  TILE_LAYER_MAX,
};

enum {
  MAP_Z_DEPTH_FLOOR,
  MAP_Z_DEPTH_WALL,
  MAP_Z_DEPTH_DOOR,
  MAP_Z_DEPTH_OBJ1,
  MAP_Z_DEPTH_OBJ2,
  MAP_Z_DEPTH_PLAYER,
  MAP_Z_DEPTH_CURSOR,
};

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

enum { MONST_CLASS_A, MONST_CLASS_MAX };

/* clang-format off */
#define THING_FLAG_ENUM(list_macro)                                              \
  list_macro(is_able_to_walk_through_walls,   "is_able_to_walk_through_walls"),  \
  list_macro(is_animated_can_hflip,           "is_animated_can_hflip"),          \
  list_macro(is_animated_no_dir,              "is_animated_no_dir"),             \
  list_macro(is_blit_centered,                "is_blit_centered"),               \
  list_macro(is_blit_on_ground,               "is_blit_on_ground"),              \
  list_macro(is_blit_outlined,                "is_blit_outlined"),               \
  list_macro(is_blit_square_outlined,         "is_blit_square_outlined"),        \
  list_macro(is_cursor,                       "is_cursor"),                      \
  list_macro(is_cursor_hazard,                "is_cursor_hazard"),               \
  list_macro(is_cursor_path_blocker,          "is_cursor_path_blocker"),         \
  list_macro(is_cursor_path_hazard,           "is_cursor_path_hazard"),          \
  list_macro(is_cursor_path,                  "is_cursor_path"),                 \
  list_macro(is_door,                         "is_door"),                        \
  list_macro(is_dungeon_entrance,             "is_dungeon_entrance"),            \
  list_macro(is_exit,                         "is_exit"),                        \
  list_macro(is_floor,                        "is_floor"),                       \
  list_macro(is_key,                          "is_key"),                         \
  list_macro(is_monst,                        "is_monst"),                       \
  list_macro(is_obs_monst,                    "is_obs_monst"),                   \
  list_macro(is_obs_player,                   "is_obs_player"),                  \
  list_macro(is_obs_wall_or_door,             "is_obs_wall_or_door"),            \
  list_macro(is_player,                       "is_player"),                      \
  list_macro(is_tiled,                        "is_tiled"),                       \
  list_macro(is_wall,                         "is_wall"),                        \
  list_macro(is_lava,                         "is_lava"),                        \
  list_macro(is_chasm,                        "is_chasm"),                       \
  list_macro(THING_FLAG_MAX,                  "THING_FLAG_MAX"),

/* clang-format on */

#define tp_is_able_to_walk_through_walls(tp) tp_flag(tp, is_able_to_walk_through_walls)
#define tp_is_animated_can_hflip(tp)         tp_flag(tp, is_animated_can_hflip)
#define tp_is_animated_no_dir(tp)            tp_flag(tp, is_animated_no_dir)
#define tp_is_blit_centered(tp)              tp_flag(tp, is_blit_centered)
#define tp_is_blit_on_ground(tp)             tp_flag(tp, is_blit_on_ground)
#define tp_is_blit_outlined(tp)              tp_flag(tp, is_blit_outlined)
#define tp_is_blit_square_outlined(tp)       tp_flag(tp, is_blit_square_outlined)
#define tp_is_cursor(tp)                     tp_flag(tp, is_cursor)
#define tp_is_cursor_hazard(tp)              tp_flag(tp, is_cursor_hazard)
#define tp_is_cursor_path_blocker(tp)        tp_flag(tp, is_cursor_path_blocker)
#define tp_is_cursor_path_hazard(tp)         tp_flag(tp, is_cursor_path_hazard)
#define tp_is_cursor_path(tp)                tp_flag(tp, is_cursor_path)
#define tp_is_door(tp)                       tp_flag(tp, is_door)
#define tp_is_dungeon_entrance(tp)           tp_flag(tp, is_dungeon_entrance)
#define tp_is_exit(tp)                       tp_flag(tp, is_exit)
#define tp_is_floor(tp)                      tp_flag(tp, is_floor)
#define tp_is_key(tp)                        tp_flag(tp, is_key)
#define tp_is_monst(tp)                      tp_flag(tp, is_monst)
#define tp_is_obs_monst(tp)                  tp_flag(tp, is_obs_monst)
#define tp_is_obs_player(tp)                 tp_flag(tp, is_obs_player)
#define tp_is_obs_wall_or_door(tp)           tp_flag(tp, is_obs_wall_or_door)
#define tp_is_player(tp)                     tp_flag(tp, is_player)
#define tp_is_tiled(tp)                      tp_flag(tp, is_tiled)
#define tp_is_wall(tp)                       tp_flag(tp, is_wall)
#define tp_is_lava(tp)                       tp_flag(tp, is_lava)
#define tp_is_chasm(tp)                      tp_flag(tp, is_chasm)

#define thing_is_able_to_walk_through_walls(thing) tp_flag(thing_tp(thing), is_able_to_walk_through_walls)
#define thing_is_animated_can_hflip(thing)         tp_flag(thing_tp(thing), is_animated_can_hflip)
#define thing_is_animated_no_dir(thing)            tp_flag(thing_tp(thing), is_animated_no_dir)
#define thing_is_blit_centered(thing)              tp_flag(thing_tp(thing), is_blit_centered)
#define thing_is_blit_on_ground(thing)             tp_flag(thing_tp(thing), is_blit_on_ground)
#define thing_is_blit_outlined(thing)              tp_flag(thing_tp(thing), is_blit_outlined)
#define thing_is_blit_square_outlined(thing)       tp_flag(thing_tp(thing), is_blit_square_outlined)
#define thing_is_cursor(thing)                     tp_flag(thing_tp(thing), is_cursor)
#define thing_is_cursor_hazard(thing)              tp_flag(thing_tp(thing), is_cursor_hazard)
#define thing_is_cursor_path_blocker(thing)        tp_flag(thing_tp(thing), is_cursor_path_blocker)
#define thing_is_cursor_path_hazard(thing)         tp_flag(thing_tp(thing), is_cursor_path_hazard)
#define thing_is_cursor_path(thing)                tp_flag(thing_tp(thing), is_cursor_path)
#define thing_is_door(thing)                       tp_flag(thing_tp(thing), is_door)
#define thing_is_dungeon_entrance(thing)           tp_flag(thing_tp(thing), is_dungeon_entrance)
#define thing_is_exit(thing)                       tp_flag(thing_tp(thing), is_exit)
#define thing_is_floor(thing)                      tp_flag(thing_tp(thing), is_floor)
#define thing_is_key(thing)                        tp_flag(thing_tp(thing), is_key)
#define thing_is_monst(thing)                      tp_flag(thing_tp(thing), is_monst)
#define thing_is_obs_monst(thing)                  tp_flag(thing_tp(thing), is_obs_monst)
#define thing_is_obs_player(thing)                 tp_flag(thing_tp(thing), is_obs_player)
#define thing_is_obs_wall_or_door(thing)           tp_flag(thing_tp(thing), is_obs_wall_or_door)
#define thing_is_player(thing)                     tp_flag(thing_tp(thing), is_player)
#define thing_is_tiled(thing)                      tp_flag(thing_tp(thing), is_tiled)
#define thing_is_wall(thing)                       tp_flag(thing_tp(thing), is_wall)
#define thing_is_lava(thing)                       tp_flag(thing_tp(thing), is_lava)
#define thing_is_chasm(thing)                      tp_flag(thing_tp(thing), is_chasm)

#define level_is_able_to_walk_through_walls(level, x, y, z) level_flag(level, is_able_to_walk_through_walls, x, y, z)
#define level_is_animated_can_hflip(level, x, y, z)         level_flag(level, is_animated_can_hflip, x, y, z)
#define level_is_animated_no_dir(level, x, y, z)            level_flag(level, is_animated_no_dir, x, y, z)
#define level_is_blit_centered(level, x, y, z)              level_flag(level, is_blit_centered, x, y, z)
#define level_is_blit_on_ground(level, x, y, z)             level_flag(level, is_blit_on_ground, x, y, z)
#define level_is_blit_outlined(level, x, y, z)              level_flag(level, is_blit_outlined, x, y, z)
#define level_is_blit_square_outlined(level, x, y, z)       level_flag(level, is_blit_square_outlined, x, y, z)
#define level_is_cursor(level, x, y, z)                     level_flag(level, is_cursor, x, y, z)
#define level_is_cursor_hazard(level, x, y, z)              level_flag(level, is_cursor_hazard, x, y, z)
#define level_is_cursor_path_blocker(level, x, y, z)        level_flag(level, is_cursor_path_blocker, x, y, z)
#define level_is_cursor_path_hazard(level, x, y, z)         level_flag(level, is_cursor_path_hazard, x, y, z)
#define level_is_cursor_path(level, x, y, z)                level_flag(level, is_cursor_path, x, y, z)
#define level_is_door(level, x, y, z)                       level_flag(level, is_door, x, y, z)
#define level_is_dungeon_entrance(level, x, y, z)           level_flag(level, is_dungeon_entrance, x, y, z)
#define level_is_exit(level, x, y, z)                       level_flag(level, is_exit, x, y, z)
#define level_is_floor(level, x, y, z)                      level_flag(level, is_floor, x, y, z)
#define level_is_key(level, x, y, z)                        level_flag(level, is_key, x, y, z)
#define level_is_monst(level, x, y, z)                      level_flag(level, is_monst, x, y, z)
#define level_is_obs_monst(level, x, y, z)                  level_flag(level, is_obs_monst, x, y, z)
#define level_is_obs_player(level, x, y, z)                 level_flag(level, is_obs_player, x, y, z)
#define level_is_obs_wall_or_door(level, x, y, z)           level_flag(level, is_obs_wall_or_door, x, y, z)
#define level_is_player(level, x, y, z)                     level_flag(level, is_player, x, y, z)
#define level_is_tiled(level, x, y, z)                      level_flag(level, is_tiled, x, y, z)
#define level_is_wall(level, x, y, z)                       level_flag(level, is_wall, x, y, z)
#define level_is_lava(level, x, y, z)                       level_flag(level, is_lava, x, y, z)
#define level_is_chasm(level, x, y, z)                      level_flag(level, is_chasm, x, y, z)

ENUM_DEF_H(THING_FLAG_ENUM, ThingFlag)

#endif
