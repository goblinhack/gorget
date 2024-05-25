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
  list_macro(is_walk_through_walls,   "is_walk_through_walls"),  \
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

#define tp_is_walk_through_walls(tp)   tp_flag(tp, is_walk_through_walls)
#define tp_is_animated_can_hflip(tp)   tp_flag(tp, is_animated_can_hflip)
#define tp_is_animated_no_dir(tp)      tp_flag(tp, is_animated_no_dir)
#define tp_is_blit_centered(tp)        tp_flag(tp, is_blit_centered)
#define tp_is_blit_on_ground(tp)       tp_flag(tp, is_blit_on_ground)
#define tp_is_blit_outlined(tp)        tp_flag(tp, is_blit_outlined)
#define tp_is_blit_square_outlined(tp) tp_flag(tp, is_blit_square_outlined)
#define tp_is_cursor(tp)               tp_flag(tp, is_cursor)
#define tp_is_cursor_hazard(tp)        tp_flag(tp, is_cursor_hazard)
#define tp_is_cursor_path_blocker(tp)  tp_flag(tp, is_cursor_path_blocker)
#define tp_is_cursor_path_hazard(tp)   tp_flag(tp, is_cursor_path_hazard)
#define tp_is_cursor_path(tp)          tp_flag(tp, is_cursor_path)
#define tp_is_door(tp)                 tp_flag(tp, is_door)
#define tp_is_dungeon_entrance(tp)     tp_flag(tp, is_dungeon_entrance)
#define tp_is_exit(tp)                 tp_flag(tp, is_exit)
#define tp_is_floor(tp)                tp_flag(tp, is_floor)
#define tp_is_key(tp)                  tp_flag(tp, is_key)
#define tp_is_monst(tp)                tp_flag(tp, is_monst)
#define tp_is_obs_monst(tp)            tp_flag(tp, is_obs_monst)
#define tp_is_obs_player(tp)           tp_flag(tp, is_obs_player)
#define tp_is_obs_wall_or_door(tp)     tp_flag(tp, is_obs_wall_or_door)
#define tp_is_player(tp)               tp_flag(tp, is_player)
#define tp_is_tiled(tp)                tp_flag(tp, is_tiled)
#define tp_is_wall(tp)                 tp_flag(tp, is_wall)
#define tp_is_lava(tp)                 tp_flag(tp, is_lava)
#define tp_is_chasm(tp)                tp_flag(tp, is_chasm)

#define thing_is_walk_through_walls(thing)   tp_flag(thing_tp(thing), is_walk_through_walls)
#define thing_is_animated_can_hflip(thing)   tp_flag(thing_tp(thing), is_animated_can_hflip)
#define thing_is_animated_no_dir(thing)      tp_flag(thing_tp(thing), is_animated_no_dir)
#define thing_is_blit_centered(thing)        tp_flag(thing_tp(thing), is_blit_centered)
#define thing_is_blit_on_ground(thing)       tp_flag(thing_tp(thing), is_blit_on_ground)
#define thing_is_blit_outlined(thing)        tp_flag(thing_tp(thing), is_blit_outlined)
#define thing_is_blit_square_outlined(thing) tp_flag(thing_tp(thing), is_blit_square_outlined)
#define thing_is_cursor(thing)               tp_flag(thing_tp(thing), is_cursor)
#define thing_is_cursor_hazard(thing)        tp_flag(thing_tp(thing), is_cursor_hazard)
#define thing_is_cursor_path_blocker(thing)  tp_flag(thing_tp(thing), is_cursor_path_blocker)
#define thing_is_cursor_path_hazard(thing)   tp_flag(thing_tp(thing), is_cursor_path_hazard)
#define thing_is_cursor_path(thing)          tp_flag(thing_tp(thing), is_cursor_path)
#define thing_is_door(thing)                 tp_flag(thing_tp(thing), is_door)
#define thing_is_dungeon_entrance(thing)     tp_flag(thing_tp(thing), is_dungeon_entrance)
#define thing_is_exit(thing)                 tp_flag(thing_tp(thing), is_exit)
#define thing_is_floor(thing)                tp_flag(thing_tp(thing), is_floor)
#define thing_is_key(thing)                  tp_flag(thing_tp(thing), is_key)
#define thing_is_monst(thing)                tp_flag(thing_tp(thing), is_monst)
#define thing_is_obs_monst(thing)            tp_flag(thing_tp(thing), is_obs_monst)
#define thing_is_obs_player(thing)           tp_flag(thing_tp(thing), is_obs_player)
#define thing_is_obs_wall_or_door(thing)     tp_flag(thing_tp(thing), is_obs_wall_or_door)
#define thing_is_player(thing)               tp_flag(thing_tp(thing), is_player)
#define thing_is_tiled(thing)                tp_flag(thing_tp(thing), is_tiled)
#define thing_is_wall(thing)                 tp_flag(thing_tp(thing), is_wall)
#define thing_is_lava(thing)                 tp_flag(thing_tp(thing), is_lava)
#define thing_is_chasm(thing)                tp_flag(thing_tp(thing), is_chasm)

#define level_is_walk_through_walls_at(level, x, y, z)   level_flag(level, is_walk_through_walls, point3d(x, y, z))
#define level_is_animated_can_hflip_at(level, x, y, z)   level_flag(level, is_animated_can_hflip, point3d(x, y, z))
#define level_is_animated_no_dir_at(level, x, y, z)      level_flag(level, is_animated_no_dir, point3d(x, y, z))
#define level_is_blit_centered_at(level, x, y, z)        level_flag(level, is_blit_centered, point3d(x, y, z))
#define level_is_blit_on_ground_at(level, x, y, z)       level_flag(level, is_blit_on_ground, point3d(x, y, z))
#define level_is_blit_outlined_at(level, x, y, z)        level_flag(level, is_blit_outlined, point3d(x, y, z))
#define level_is_blit_square_outlined_at(level, x, y, z) level_flag(level, is_blit_square_outlined, point3d(x, y, z))
#define level_is_cursor_at(level, x, y, z)               level_flag(level, is_cursor, point3d(x, y, z))
#define level_is_cursor_hazard_at(level, x, y, z)        level_flag(level, is_cursor_hazard, point3d(x, y, z))
#define level_is_cursor_path_blocker_at(level, x, y, z)  level_flag(level, is_cursor_path_blocker, point3d(x, y, z))
#define level_is_cursor_path_hazard_at(level, x, y, z)   level_flag(level, is_cursor_path_hazard, point3d(x, y, z))
#define level_is_cursor_path_at(level, x, y, z)          level_flag(level, is_cursor_path, point3d(x, y, z))
#define level_is_door_at(level, x, y, z)                 level_flag(level, is_door, point3d(x, y, z))
#define level_is_dungeon_entrance_at(level, x, y, z)     level_flag(level, is_dungeon_entrance, point3d(x, y, z))
#define level_is_exit_at(level, x, y, z)                 level_flag(level, is_exit, point3d(x, y, z))
#define level_is_floor_at(level, x, y, z)                level_flag(level, is_floor, point3d(x, y, z))
#define level_is_key_at(level, x, y, z)                  level_flag(level, is_key, point3d(x, y, z))
#define level_is_monst_at(level, x, y, z)                level_flag(level, is_monst, point3d(x, y, z))
#define level_is_obs_monst_at(level, x, y, z)            level_flag(level, is_obs_monst, point3d(x, y, z))
#define level_is_obs_player_at(level, x, y, z)           level_flag(level, is_obs_player, point3d(x, y, z))
#define level_is_obs_wall_or_door_at(level, x, y, z)     level_flag(level, is_obs_wall_or_door, point3d(x, y, z))
#define level_is_player_at(level, x, y, z)               level_flag(level, is_player, point3d(x, y, z))
#define level_is_tiled_at(level, x, y, z)                level_flag(level, is_tiled, point3d(x, y, z))
#define level_is_wall_at(level, x, y, z)                 level_flag(level, is_wall, point3d(x, y, z))
#define level_is_lava_at(level, x, y, z)                 level_flag(level, is_lava, point3d(x, y, z))
#define level_is_chasm_at(level, x, y, z)                level_flag(level, is_chasm, point3d(x, y, z))

#define level_is_walk_through_walls(level, p)   level_flag(level, is_walk_through_walls, p)
#define level_is_animated_can_hflip(level, p)   level_flag(level, is_animated_can_hflip, p)
#define level_is_animated_no_dir(level, p)      level_flag(level, is_animated_no_dir, p)
#define level_is_blit_centered(level, p)        level_flag(level, is_blit_centered, p)
#define level_is_blit_on_ground(level, p)       level_flag(level, is_blit_on_ground, p)
#define level_is_blit_outlined(level, p)        level_flag(level, is_blit_outlined, p)
#define level_is_blit_square_outlined(level, p) level_flag(level, is_blit_square_outlined, p)
#define level_is_cursor(level, p)               level_flag(level, is_cursor, p)
#define level_is_cursor_hazard(level, p)        level_flag(level, is_cursor_hazard, p)
#define level_is_cursor_path_blocker(level, p)  level_flag(level, is_cursor_path_blocker, p)
#define level_is_cursor_path_hazard(level, p)   level_flag(level, is_cursor_path_hazard, p)
#define level_is_cursor_path(level, p)          level_flag(level, is_cursor_path, p)
#define level_is_door(level, p)                 level_flag(level, is_door, p)
#define level_is_dungeon_entrance(level, p)     level_flag(level, is_dungeon_entrance, p)
#define level_is_exit(level, p)                 level_flag(level, is_exit, p)
#define level_is_floor(level, p)                level_flag(level, is_floor, p)
#define level_is_key(level, p)                  level_flag(level, is_key, p)
#define level_is_monst(level, p)                level_flag(level, is_monst, p)
#define level_is_obs_monst(level, p)            level_flag(level, is_obs_monst, p)
#define level_is_obs_player(level, p)           level_flag(level, is_obs_player, p)
#define level_is_obs_wall_or_door(level, p)     level_flag(level, is_obs_wall_or_door, p)
#define level_is_player(level, p)               level_flag(level, is_player, p)
#define level_is_tiled(level, p)                level_flag(level, is_tiled, p)
#define level_is_wall(level, p)                 level_flag(level, is_wall, p)
#define level_is_lava(level, p)                 level_flag(level, is_lava, p)
#define level_is_chasm(level, p)                level_flag(level, is_chasm, p)

ENUM_DEF_H(THING_FLAG_ENUM, ThingFlag)

#endif
