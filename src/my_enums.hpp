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

#define THING_FLAG_ENUM(list_macro)                                                                                  \
  list_macro(is_walk_through_walls, "is_walk_through_walls"),         /* ............................ */             \
      list_macro(is_animated_can_hflip, "is_animated_can_hflip"),     /* ............................ */             \
      list_macro(is_animated_no_dir, "is_animated_no_dir"),           /* ............................ */             \
      list_macro(is_blit_centered, "is_blit_centered"),               /* ............................ */             \
      list_macro(is_blit_on_ground, "is_blit_on_ground"),             /* ............................ */             \
      list_macro(is_blit_outlined, "is_blit_outlined"),               /* ............................ */             \
      list_macro(is_blit_square_outlined, "is_blit_square_outlined"), /* ............................ */             \
      list_macro(is_cursor, "is_cursor"),                             /* ............................ */             \
      list_macro(is_cursor_hazard, "is_cursor_hazard"),               /* ............................ */             \
      list_macro(is_cursor_path_blocker, "is_cursor_path_blocker"),   /* ............................ */             \
      list_macro(is_cursor_path_hazard, "is_cursor_path_hazard"),     /* ............................ */             \
      list_macro(is_cursor_path, "is_cursor_path"),                   /* ............................ */             \
      list_macro(is_door, "is_door"),                                 /* ............................ */             \
      list_macro(is_dungeon_entrance, "is_dungeon_entrance"),         /* ............................ */             \
      list_macro(is_exit, "is_exit"),                                 /* ............................ */             \
      list_macro(is_floor, "is_floor"),                               /* ............................ */             \
      list_macro(is_key, "is_key"),                                   /* ............................ */             \
      list_macro(is_monst, "is_monst"),                               /* ............................ */             \
      list_macro(is_obs_monst, "is_obs_monst"),                       /* ............................ */             \
      list_macro(is_obs_player, "is_obs_player"),                     /* ............................ */             \
      list_macro(is_obs_wall_or_door, "is_obs_wall_or_door"),         /* ............................ */             \
      list_macro(is_player, "is_player"),                             /* ............................ */             \
      list_macro(is_tiled, "is_tiled"),                               /* ............................ */             \
      list_macro(is_wall, "is_wall"),                                 /* ............................ */             \
      list_macro(is_lava, "is_lava"),                                 /* ............................ */             \
      list_macro(is_chasm, "is_chasm"),                               /* ............................ */             \
      list_macro(is_unused1, "is_unused1"),                           /* ............................ */             \
      list_macro(is_unused2, "is_unused2"),                           /* ............................ */             \
      list_macro(is_unused3, "is_unused3"),                           /* ............................ */             \
      list_macro(is_unused4, "is_unused4"),                           /* ............................ */             \
      list_macro(is_unused5, "is_unused5"),                           /* ............................ */             \
      list_macro(is_unused6, "is_unused6"),                           /* ............................ */             \
      list_macro(is_unused7, "is_unused7"),                           /* ............................ */             \
      list_macro(is_unused8, "is_unused8"),                           /* ............................ */             \
      list_macro(is_unused9, "is_unused9"),                           /* ............................ */             \
      list_macro(is_unused10, "is_unused10"),                         /* ............................ */             \
      list_macro(is_unused11, "is_unused11"),                         /* ............................ */             \
      list_macro(is_unused12, "is_unused12"),                         /* ............................ */             \
      list_macro(is_unused13, "is_unused13"),                         /* ............................ */             \
      list_macro(is_unused14, "is_unused14"),                         /* ............................ */             \
      list_macro(is_unused15, "is_unused15"),                         /* ............................ */             \
      list_macro(is_unused16, "is_unused16"),                         /* ............................ */             \
      list_macro(is_unused17, "is_unused17"),                         /* ............................ */             \
      list_macro(is_unused18, "is_unused18"),                         /* ............................ */             \
      list_macro(is_unused19, "is_unused19"),                         /* ............................ */             \
      list_macro(is_unused20, "is_unused20"),                         /* ............................ */             \
      list_macro(is_unused21, "is_unused21"),                         /* ............................ */             \
      list_macro(is_unused22, "is_unused22"),                         /* ............................ */             \
      list_macro(is_unused23, "is_unused23"),                         /* ............................ */             \
      list_macro(is_unused24, "is_unused24"),                         /* ............................ */             \
      list_macro(is_unused25, "is_unused25"),                         /* ............................ */             \
      list_macro(is_unused26, "is_unused26"),                         /* ............................ */             \
      list_macro(is_unused27, "is_unused27"),                         /* ............................ */             \
      list_macro(is_unused28, "is_unused28"),                         /* ............................ */             \
      list_macro(is_unused29, "is_unused29"),                         /* ............................ */             \
      list_macro(is_unused30, "is_unused30"),                         /* ............................ */             \
      list_macro(is_unused31, "is_unused31"),                         /* ............................ */             \
      list_macro(is_unused32, "is_unused32"),                         /* ............................ */             \
      list_macro(is_unused33, "is_unused33"),                         /* ............................ */             \
      list_macro(is_unused34, "is_unused34"),                         /* ............................ */             \
      list_macro(is_unused35, "is_unused35"),                         /* ............................ */             \
      list_macro(is_unused36, "is_unused36"),                         /* ............................ */             \
      list_macro(is_unused37, "is_unused37"),                         /* ............................ */             \
      list_macro(is_unused38, "is_unused38"),                         /* ............................ */             \
      list_macro(is_unused39, "is_unused39"),                         /* ............................ */             \
      list_macro(is_unused40, "is_unused40"),                         /* ............................ */             \
      list_macro(is_unused41, "is_unused41"),                         /* ............................ */             \
      list_macro(is_unused42, "is_unused42"),                         /* ............................ */             \
      list_macro(is_unused43, "is_unused43"),                         /* ............................ */             \
      list_macro(is_unused44, "is_unused44"),                         /* ............................ */             \
      list_macro(is_unused45, "is_unused45"),                         /* ............................ */             \
      list_macro(is_unused46, "is_unused46"),                         /* ............................ */             \
      list_macro(is_unused47, "is_unused47"),                         /* ............................ */             \
      list_macro(is_unused48, "is_unused48"),                         /* ............................ */             \
      list_macro(is_unused49, "is_unused49"),                         /* ............................ */             \
      list_macro(is_unused50, "is_unused50"),                         /* ............................ */             \
      list_macro(is_unused51, "is_unused51"),                         /* ............................ */             \
      list_macro(is_unused52, "is_unused52"),                         /* ............................ */             \
      list_macro(is_unused53, "is_unused53"),                         /* ............................ */             \
      list_macro(is_unused54, "is_unused54"),                         /* ............................ */             \
      list_macro(is_unused55, "is_unused55"),                         /* ............................ */             \
      list_macro(is_unused56, "is_unused56"),                         /* ............................ */             \
      list_macro(is_unused57, "is_unused57"),                         /* ............................ */             \
      list_macro(is_unused58, "is_unused58"),                         /* ............................ */             \
      list_macro(is_unused59, "is_unused59"),                         /* ............................ */             \
      list_macro(is_unused60, "is_unused60"),                         /* ............................ */             \
      list_macro(is_unused61, "is_unused61"),                         /* ............................ */             \
      list_macro(is_unused62, "is_unused62"),                         /* ............................ */             \
      list_macro(is_unused63, "is_unused63"),                         /* ............................ */             \
      list_macro(is_unused64, "is_unused64"),                         /* ............................ */             \
      list_macro(is_unused65, "is_unused65"),                         /* ............................ */             \
      list_macro(is_unused66, "is_unused66"),                         /* ............................ */             \
      list_macro(is_unused67, "is_unused67"),                         /* ............................ */             \
      list_macro(is_unused68, "is_unused68"),                         /* ............................ */             \
      list_macro(is_unused69, "is_unused69"),                         /* ............................ */             \
      list_macro(is_unused70, "is_unused70"),                         /* ............................ */             \
      list_macro(is_unused71, "is_unused71"),                         /* ............................ */             \
      list_macro(is_unused72, "is_unused72"),                         /* ............................ */             \
      list_macro(is_unused73, "is_unused73"),                         /* ............................ */             \
      list_macro(is_unused74, "is_unused74"),                         /* ............................ */             \
      list_macro(is_unused75, "is_unused75"),                         /* ............................ */             \
      list_macro(is_unused76, "is_unused76"),                         /* ............................ */             \
      list_macro(is_unused77, "is_unused77"),                         /* ............................ */             \
      list_macro(is_unused78, "is_unused78"),                         /* ............................ */             \
      list_macro(is_unused79, "is_unused79"),                         /* ............................ */             \
      list_macro(is_unused80, "is_unused80"),                         /* ............................ */             \
      list_macro(is_unused81, "is_unused81"),                         /* ............................ */             \
      list_macro(is_unused82, "is_unused82"),                         /* ............................ */             \
      list_macro(is_unused83, "is_unused83"),                         /* ............................ */             \
      list_macro(is_unused84, "is_unused84"),                         /* ............................ */             \
      list_macro(is_unused85, "is_unused85"),                         /* ............................ */             \
      list_macro(is_unused86, "is_unused86"),                         /* ............................ */             \
      list_macro(is_unused87, "is_unused87"),                         /* ............................ */             \
      list_macro(is_unused88, "is_unused88"),                         /* ............................ */             \
      list_macro(is_unused89, "is_unused89"),                         /* ............................ */             \
      list_macro(is_unused90, "is_unused90"),                         /* ............................ */             \
      list_macro(is_unused91, "is_unused91"),                         /* ............................ */             \
      list_macro(is_unused92, "is_unused92"),                         /* ............................ */             \
      list_macro(is_unused93, "is_unused93"),                         /* ............................ */             \
      list_macro(is_unused94, "is_unused94"),                         /* ............................ */             \
      list_macro(is_unused95, "is_unused95"),                         /* ............................ */             \
      list_macro(is_unused96, "is_unused96"),                         /* ............................ */             \
      list_macro(is_unused97, "is_unused97"),                         /* ............................ */             \
      list_macro(is_unused98, "is_unused98"),                         /* ............................ */             \
      list_macro(is_unused99, "is_unused99"),                         /* ............................ */             \
      list_macro(is_tickable, "is_tickable"),                         /* ............................ */             \
      list_macro(THING_FLAG_MAX, "THING_FLAG_MAX"),

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
#define tp_is_unused1(tp)              tp_flag(tp, is_unused1)
#define tp_is_unused2(tp)              tp_flag(tp, is_unused2)
#define tp_is_unused3(tp)              tp_flag(tp, is_unused3)
#define tp_is_unused4(tp)              tp_flag(tp, is_unused4)
#define tp_is_unused5(tp)              tp_flag(tp, is_unused5)
#define tp_is_unused6(tp)              tp_flag(tp, is_unused6)
#define tp_is_unused7(tp)              tp_flag(tp, is_unused7)
#define tp_is_unused8(tp)              tp_flag(tp, is_unused8)
#define tp_is_unused9(tp)              tp_flag(tp, is_unused9)
#define tp_is_unused10(tp)             tp_flag(tp, is_unused10)
#define tp_is_unused11(tp)             tp_flag(tp, is_unused11)
#define tp_is_unused12(tp)             tp_flag(tp, is_unused12)
#define tp_is_unused13(tp)             tp_flag(tp, is_unused13)
#define tp_is_unused14(tp)             tp_flag(tp, is_unused14)
#define tp_is_unused15(tp)             tp_flag(tp, is_unused15)
#define tp_is_unused16(tp)             tp_flag(tp, is_unused16)
#define tp_is_unused17(tp)             tp_flag(tp, is_unused17)
#define tp_is_unused18(tp)             tp_flag(tp, is_unused18)
#define tp_is_unused19(tp)             tp_flag(tp, is_unused19)
#define tp_is_unused20(tp)             tp_flag(tp, is_unused20)
#define tp_is_unused21(tp)             tp_flag(tp, is_unused21)
#define tp_is_unused22(tp)             tp_flag(tp, is_unused22)
#define tp_is_unused23(tp)             tp_flag(tp, is_unused23)
#define tp_is_unused24(tp)             tp_flag(tp, is_unused24)
#define tp_is_unused25(tp)             tp_flag(tp, is_unused25)
#define tp_is_unused26(tp)             tp_flag(tp, is_unused26)
#define tp_is_unused27(tp)             tp_flag(tp, is_unused27)
#define tp_is_unused28(tp)             tp_flag(tp, is_unused28)
#define tp_is_unused29(tp)             tp_flag(tp, is_unused29)
#define tp_is_unused30(tp)             tp_flag(tp, is_unused30)
#define tp_is_unused31(tp)             tp_flag(tp, is_unused31)
#define tp_is_unused32(tp)             tp_flag(tp, is_unused32)
#define tp_is_unused33(tp)             tp_flag(tp, is_unused33)
#define tp_is_unused34(tp)             tp_flag(tp, is_unused34)
#define tp_is_unused35(tp)             tp_flag(tp, is_unused35)
#define tp_is_unused36(tp)             tp_flag(tp, is_unused36)
#define tp_is_unused37(tp)             tp_flag(tp, is_unused37)
#define tp_is_unused38(tp)             tp_flag(tp, is_unused38)
#define tp_is_unused39(tp)             tp_flag(tp, is_unused39)
#define tp_is_unused40(tp)             tp_flag(tp, is_unused40)
#define tp_is_unused41(tp)             tp_flag(tp, is_unused41)
#define tp_is_unused42(tp)             tp_flag(tp, is_unused42)
#define tp_is_unused43(tp)             tp_flag(tp, is_unused43)
#define tp_is_unused44(tp)             tp_flag(tp, is_unused44)
#define tp_is_unused45(tp)             tp_flag(tp, is_unused45)
#define tp_is_unused46(tp)             tp_flag(tp, is_unused46)
#define tp_is_unused47(tp)             tp_flag(tp, is_unused47)
#define tp_is_unused48(tp)             tp_flag(tp, is_unused48)
#define tp_is_unused49(tp)             tp_flag(tp, is_unused49)
#define tp_is_unused50(tp)             tp_flag(tp, is_unused50)
#define tp_is_unused51(tp)             tp_flag(tp, is_unused51)
#define tp_is_unused52(tp)             tp_flag(tp, is_unused52)
#define tp_is_unused53(tp)             tp_flag(tp, is_unused53)
#define tp_is_unused54(tp)             tp_flag(tp, is_unused54)
#define tp_is_unused55(tp)             tp_flag(tp, is_unused55)
#define tp_is_unused56(tp)             tp_flag(tp, is_unused56)
#define tp_is_unused57(tp)             tp_flag(tp, is_unused57)
#define tp_is_unused58(tp)             tp_flag(tp, is_unused58)
#define tp_is_unused59(tp)             tp_flag(tp, is_unused59)
#define tp_is_unused60(tp)             tp_flag(tp, is_unused60)
#define tp_is_unused61(tp)             tp_flag(tp, is_unused61)
#define tp_is_unused62(tp)             tp_flag(tp, is_unused62)
#define tp_is_unused63(tp)             tp_flag(tp, is_unused63)
#define tp_is_unused64(tp)             tp_flag(tp, is_unused64)
#define tp_is_unused65(tp)             tp_flag(tp, is_unused65)
#define tp_is_unused66(tp)             tp_flag(tp, is_unused66)
#define tp_is_unused67(tp)             tp_flag(tp, is_unused67)
#define tp_is_unused68(tp)             tp_flag(tp, is_unused68)
#define tp_is_unused69(tp)             tp_flag(tp, is_unused69)
#define tp_is_unused70(tp)             tp_flag(tp, is_unused70)
#define tp_is_unused71(tp)             tp_flag(tp, is_unused71)
#define tp_is_unused72(tp)             tp_flag(tp, is_unused72)
#define tp_is_unused73(tp)             tp_flag(tp, is_unused73)
#define tp_is_unused74(tp)             tp_flag(tp, is_unused74)
#define tp_is_unused75(tp)             tp_flag(tp, is_unused75)
#define tp_is_unused76(tp)             tp_flag(tp, is_unused76)
#define tp_is_unused77(tp)             tp_flag(tp, is_unused77)
#define tp_is_unused78(tp)             tp_flag(tp, is_unused78)
#define tp_is_unused79(tp)             tp_flag(tp, is_unused79)
#define tp_is_unused80(tp)             tp_flag(tp, is_unused80)
#define tp_is_unused81(tp)             tp_flag(tp, is_unused81)
#define tp_is_unused82(tp)             tp_flag(tp, is_unused82)
#define tp_is_unused83(tp)             tp_flag(tp, is_unused83)
#define tp_is_unused84(tp)             tp_flag(tp, is_unused84)
#define tp_is_unused85(tp)             tp_flag(tp, is_unused85)
#define tp_is_unused86(tp)             tp_flag(tp, is_unused86)
#define tp_is_unused87(tp)             tp_flag(tp, is_unused87)
#define tp_is_unused88(tp)             tp_flag(tp, is_unused88)
#define tp_is_unused89(tp)             tp_flag(tp, is_unused89)
#define tp_is_unused90(tp)             tp_flag(tp, is_unused90)
#define tp_is_unused91(tp)             tp_flag(tp, is_unused91)
#define tp_is_unused92(tp)             tp_flag(tp, is_unused92)
#define tp_is_unused93(tp)             tp_flag(tp, is_unused93)
#define tp_is_unused94(tp)             tp_flag(tp, is_unused94)
#define tp_is_unused95(tp)             tp_flag(tp, is_unused95)
#define tp_is_unused96(tp)             tp_flag(tp, is_unused96)
#define tp_is_unused97(tp)             tp_flag(tp, is_unused97)
#define tp_is_unused98(tp)             tp_flag(tp, is_unused98)
#define tp_is_tickable(tp)             tp_flag(tp, is_unused99)

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
#define thing_is_unused1(thing)              tp_flag(thing_tp(thing), is_unused1)
#define thing_is_unused2(thing)              tp_flag(thing_tp(thing), is_unused2)
#define thing_is_unused3(thing)              tp_flag(thing_tp(thing), is_unused3)
#define thing_is_unused4(thing)              tp_flag(thing_tp(thing), is_unused4)
#define thing_is_unused5(thing)              tp_flag(thing_tp(thing), is_unused5)
#define thing_is_unused6(thing)              tp_flag(thing_tp(thing), is_unused6)
#define thing_is_unused7(thing)              tp_flag(thing_tp(thing), is_unused7)
#define thing_is_unused8(thing)              tp_flag(thing_tp(thing), is_unused8)
#define thing_is_unused9(thing)              tp_flag(thing_tp(thing), is_unused9)
#define thing_is_unused10(thing)             tp_flag(thing_tp(thing), is_unused10)
#define thing_is_unused11(thing)             tp_flag(thing_tp(thing), is_unused11)
#define thing_is_unused12(thing)             tp_flag(thing_tp(thing), is_unused12)
#define thing_is_unused13(thing)             tp_flag(thing_tp(thing), is_unused13)
#define thing_is_unused14(thing)             tp_flag(thing_tp(thing), is_unused14)
#define thing_is_unused15(thing)             tp_flag(thing_tp(thing), is_unused15)
#define thing_is_unused16(thing)             tp_flag(thing_tp(thing), is_unused16)
#define thing_is_unused17(thing)             tp_flag(thing_tp(thing), is_unused17)
#define thing_is_unused18(thing)             tp_flag(thing_tp(thing), is_unused18)
#define thing_is_unused19(thing)             tp_flag(thing_tp(thing), is_unused19)
#define thing_is_unused20(thing)             tp_flag(thing_tp(thing), is_unused20)
#define thing_is_unused21(thing)             tp_flag(thing_tp(thing), is_unused21)
#define thing_is_unused22(thing)             tp_flag(thing_tp(thing), is_unused22)
#define thing_is_unused23(thing)             tp_flag(thing_tp(thing), is_unused23)
#define thing_is_unused24(thing)             tp_flag(thing_tp(thing), is_unused24)
#define thing_is_unused25(thing)             tp_flag(thing_tp(thing), is_unused25)
#define thing_is_unused26(thing)             tp_flag(thing_tp(thing), is_unused26)
#define thing_is_unused27(thing)             tp_flag(thing_tp(thing), is_unused27)
#define thing_is_unused28(thing)             tp_flag(thing_tp(thing), is_unused28)
#define thing_is_unused29(thing)             tp_flag(thing_tp(thing), is_unused29)
#define thing_is_unused30(thing)             tp_flag(thing_tp(thing), is_unused30)
#define thing_is_unused31(thing)             tp_flag(thing_tp(thing), is_unused31)
#define thing_is_unused32(thing)             tp_flag(thing_tp(thing), is_unused32)
#define thing_is_unused33(thing)             tp_flag(thing_tp(thing), is_unused33)
#define thing_is_unused34(thing)             tp_flag(thing_tp(thing), is_unused34)
#define thing_is_unused35(thing)             tp_flag(thing_tp(thing), is_unused35)
#define thing_is_unused36(thing)             tp_flag(thing_tp(thing), is_unused36)
#define thing_is_unused37(thing)             tp_flag(thing_tp(thing), is_unused37)
#define thing_is_unused38(thing)             tp_flag(thing_tp(thing), is_unused38)
#define thing_is_unused39(thing)             tp_flag(thing_tp(thing), is_unused39)
#define thing_is_unused40(thing)             tp_flag(thing_tp(thing), is_unused40)
#define thing_is_unused41(thing)             tp_flag(thing_tp(thing), is_unused41)
#define thing_is_unused42(thing)             tp_flag(thing_tp(thing), is_unused42)
#define thing_is_unused43(thing)             tp_flag(thing_tp(thing), is_unused43)
#define thing_is_unused44(thing)             tp_flag(thing_tp(thing), is_unused44)
#define thing_is_unused45(thing)             tp_flag(thing_tp(thing), is_unused45)
#define thing_is_unused46(thing)             tp_flag(thing_tp(thing), is_unused46)
#define thing_is_unused47(thing)             tp_flag(thing_tp(thing), is_unused47)
#define thing_is_unused48(thing)             tp_flag(thing_tp(thing), is_unused48)
#define thing_is_unused49(thing)             tp_flag(thing_tp(thing), is_unused49)
#define thing_is_unused50(thing)             tp_flag(thing_tp(thing), is_unused50)
#define thing_is_unused51(thing)             tp_flag(thing_tp(thing), is_unused51)
#define thing_is_unused52(thing)             tp_flag(thing_tp(thing), is_unused52)
#define thing_is_unused53(thing)             tp_flag(thing_tp(thing), is_unused53)
#define thing_is_unused54(thing)             tp_flag(thing_tp(thing), is_unused54)
#define thing_is_unused55(thing)             tp_flag(thing_tp(thing), is_unused55)
#define thing_is_unused56(thing)             tp_flag(thing_tp(thing), is_unused56)
#define thing_is_unused57(thing)             tp_flag(thing_tp(thing), is_unused57)
#define thing_is_unused58(thing)             tp_flag(thing_tp(thing), is_unused58)
#define thing_is_unused59(thing)             tp_flag(thing_tp(thing), is_unused59)
#define thing_is_unused60(thing)             tp_flag(thing_tp(thing), is_unused60)
#define thing_is_unused61(thing)             tp_flag(thing_tp(thing), is_unused61)
#define thing_is_unused62(thing)             tp_flag(thing_tp(thing), is_unused62)
#define thing_is_unused63(thing)             tp_flag(thing_tp(thing), is_unused63)
#define thing_is_unused64(thing)             tp_flag(thing_tp(thing), is_unused64)
#define thing_is_unused65(thing)             tp_flag(thing_tp(thing), is_unused65)
#define thing_is_unused66(thing)             tp_flag(thing_tp(thing), is_unused66)
#define thing_is_unused67(thing)             tp_flag(thing_tp(thing), is_unused67)
#define thing_is_unused68(thing)             tp_flag(thing_tp(thing), is_unused68)
#define thing_is_unused69(thing)             tp_flag(thing_tp(thing), is_unused69)
#define thing_is_unused70(thing)             tp_flag(thing_tp(thing), is_unused70)
#define thing_is_unused71(thing)             tp_flag(thing_tp(thing), is_unused71)
#define thing_is_unused72(thing)             tp_flag(thing_tp(thing), is_unused72)
#define thing_is_unused73(thing)             tp_flag(thing_tp(thing), is_unused73)
#define thing_is_unused74(thing)             tp_flag(thing_tp(thing), is_unused74)
#define thing_is_unused75(thing)             tp_flag(thing_tp(thing), is_unused75)
#define thing_is_unused76(thing)             tp_flag(thing_tp(thing), is_unused76)
#define thing_is_unused77(thing)             tp_flag(thing_tp(thing), is_unused77)
#define thing_is_unused78(thing)             tp_flag(thing_tp(thing), is_unused78)
#define thing_is_unused79(thing)             tp_flag(thing_tp(thing), is_unused79)
#define thing_is_unused80(thing)             tp_flag(thing_tp(thing), is_unused80)
#define thing_is_unused81(thing)             tp_flag(thing_tp(thing), is_unused81)
#define thing_is_unused82(thing)             tp_flag(thing_tp(thing), is_unused82)
#define thing_is_unused83(thing)             tp_flag(thing_tp(thing), is_unused83)
#define thing_is_unused84(thing)             tp_flag(thing_tp(thing), is_unused84)
#define thing_is_unused85(thing)             tp_flag(thing_tp(thing), is_unused85)
#define thing_is_unused86(thing)             tp_flag(thing_tp(thing), is_unused86)
#define thing_is_unused87(thing)             tp_flag(thing_tp(thing), is_unused87)
#define thing_is_unused88(thing)             tp_flag(thing_tp(thing), is_unused88)
#define thing_is_unused89(thing)             tp_flag(thing_tp(thing), is_unused89)
#define thing_is_unused90(thing)             tp_flag(thing_tp(thing), is_unused90)
#define thing_is_unused91(thing)             tp_flag(thing_tp(thing), is_unused91)
#define thing_is_unused92(thing)             tp_flag(thing_tp(thing), is_unused92)
#define thing_is_unused93(thing)             tp_flag(thing_tp(thing), is_unused93)
#define thing_is_unused94(thing)             tp_flag(thing_tp(thing), is_unused94)
#define thing_is_unused95(thing)             tp_flag(thing_tp(thing), is_unused95)
#define thing_is_unused96(thing)             tp_flag(thing_tp(thing), is_unused96)
#define thing_is_unused97(thing)             tp_flag(thing_tp(thing), is_unused97)
#define thing_is_unused98(thing)             tp_flag(thing_tp(thing), is_unused98)
#define thing_is_unused99(thing)             tp_flag(thing_tp(thing), is_unused99)
#define thing_is_tickable(thing)             tp_flag(thing_tp(thing), is_tickable)

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
#define level_is_unused1_at(level, x, y, z)              level_flag(level, is_unused1, point3d(x, y, z))
#define level_is_unused2_at(level, x, y, z)              level_flag(level, is_unused2, point3d(x, y, z))
#define level_is_unused3_at(level, x, y, z)              level_flag(level, is_unused3, point3d(x, y, z))
#define level_is_unused4_at(level, x, y, z)              level_flag(level, is_unused4, point3d(x, y, z))
#define level_is_unused5_at(level, x, y, z)              level_flag(level, is_unused5, point3d(x, y, z))
#define level_is_unused6_at(level, x, y, z)              level_flag(level, is_unused6, point3d(x, y, z))
#define level_is_unused7_at(level, x, y, z)              level_flag(level, is_unused7, point3d(x, y, z))
#define level_is_unused8_at(level, x, y, z)              level_flag(level, is_unused8, point3d(x, y, z))
#define level_is_unused9_at(level, x, y, z)              level_flag(level, is_unused9, point3d(x, y, z))
#define level_is_unused10_at(level, x, y, z)             level_flag(level, is_unused10, point3d(x, y, z))
#define level_is_unused11_at(level, x, y, z)             level_flag(level, is_unused11, point3d(x, y, z))
#define level_is_unused12_at(level, x, y, z)             level_flag(level, is_unused12, point3d(x, y, z))
#define level_is_unused13_at(level, x, y, z)             level_flag(level, is_unused13, point3d(x, y, z))
#define level_is_unused14_at(level, x, y, z)             level_flag(level, is_unused14, point3d(x, y, z))
#define level_is_unused15_at(level, x, y, z)             level_flag(level, is_unused15, point3d(x, y, z))
#define level_is_unused16_at(level, x, y, z)             level_flag(level, is_unused16, point3d(x, y, z))
#define level_is_unused17_at(level, x, y, z)             level_flag(level, is_unused17, point3d(x, y, z))
#define level_is_unused18_at(level, x, y, z)             level_flag(level, is_unused18, point3d(x, y, z))
#define level_is_unused19_at(level, x, y, z)             level_flag(level, is_unused19, point3d(x, y, z))
#define level_is_unused20_at(level, x, y, z)             level_flag(level, is_unused20, point3d(x, y, z))
#define level_is_unused21_at(level, x, y, z)             level_flag(level, is_unused21, point3d(x, y, z))
#define level_is_unused22_at(level, x, y, z)             level_flag(level, is_unused22, point3d(x, y, z))
#define level_is_unused23_at(level, x, y, z)             level_flag(level, is_unused23, point3d(x, y, z))
#define level_is_unused24_at(level, x, y, z)             level_flag(level, is_unused24, point3d(x, y, z))
#define level_is_unused25_at(level, x, y, z)             level_flag(level, is_unused25, point3d(x, y, z))
#define level_is_unused26_at(level, x, y, z)             level_flag(level, is_unused26, point3d(x, y, z))
#define level_is_unused27_at(level, x, y, z)             level_flag(level, is_unused27, point3d(x, y, z))
#define level_is_unused28_at(level, x, y, z)             level_flag(level, is_unused28, point3d(x, y, z))
#define level_is_unused29_at(level, x, y, z)             level_flag(level, is_unused29, point3d(x, y, z))
#define level_is_unused30_at(level, x, y, z)             level_flag(level, is_unused30, point3d(x, y, z))
#define level_is_unused31_at(level, x, y, z)             level_flag(level, is_unused31, point3d(x, y, z))
#define level_is_unused32_at(level, x, y, z)             level_flag(level, is_unused32, point3d(x, y, z))
#define level_is_unused33_at(level, x, y, z)             level_flag(level, is_unused33, point3d(x, y, z))
#define level_is_unused34_at(level, x, y, z)             level_flag(level, is_unused34, point3d(x, y, z))
#define level_is_unused35_at(level, x, y, z)             level_flag(level, is_unused35, point3d(x, y, z))
#define level_is_unused36_at(level, x, y, z)             level_flag(level, is_unused36, point3d(x, y, z))
#define level_is_unused37_at(level, x, y, z)             level_flag(level, is_unused37, point3d(x, y, z))
#define level_is_unused38_at(level, x, y, z)             level_flag(level, is_unused38, point3d(x, y, z))
#define level_is_unused39_at(level, x, y, z)             level_flag(level, is_unused39, point3d(x, y, z))
#define level_is_unused40_at(level, x, y, z)             level_flag(level, is_unused40, point3d(x, y, z))
#define level_is_unused41_at(level, x, y, z)             level_flag(level, is_unused41, point3d(x, y, z))
#define level_is_unused42_at(level, x, y, z)             level_flag(level, is_unused42, point3d(x, y, z))
#define level_is_unused43_at(level, x, y, z)             level_flag(level, is_unused43, point3d(x, y, z))
#define level_is_unused44_at(level, x, y, z)             level_flag(level, is_unused44, point3d(x, y, z))
#define level_is_unused45_at(level, x, y, z)             level_flag(level, is_unused45, point3d(x, y, z))
#define level_is_unused46_at(level, x, y, z)             level_flag(level, is_unused46, point3d(x, y, z))
#define level_is_unused47_at(level, x, y, z)             level_flag(level, is_unused47, point3d(x, y, z))
#define level_is_unused48_at(level, x, y, z)             level_flag(level, is_unused48, point3d(x, y, z))
#define level_is_unused49_at(level, x, y, z)             level_flag(level, is_unused49, point3d(x, y, z))
#define level_is_unused50_at(level, x, y, z)             level_flag(level, is_unused50, point3d(x, y, z))
#define level_is_unused51_at(level, x, y, z)             level_flag(level, is_unused51, point3d(x, y, z))
#define level_is_unused52_at(level, x, y, z)             level_flag(level, is_unused52, point3d(x, y, z))
#define level_is_unused53_at(level, x, y, z)             level_flag(level, is_unused53, point3d(x, y, z))
#define level_is_unused54_at(level, x, y, z)             level_flag(level, is_unused54, point3d(x, y, z))
#define level_is_unused55_at(level, x, y, z)             level_flag(level, is_unused55, point3d(x, y, z))
#define level_is_unused56_at(level, x, y, z)             level_flag(level, is_unused56, point3d(x, y, z))
#define level_is_unused57_at(level, x, y, z)             level_flag(level, is_unused57, point3d(x, y, z))
#define level_is_unused58_at(level, x, y, z)             level_flag(level, is_unused58, point3d(x, y, z))
#define level_is_unused59_at(level, x, y, z)             level_flag(level, is_unused59, point3d(x, y, z))
#define level_is_unused60_at(level, x, y, z)             level_flag(level, is_unused60, point3d(x, y, z))
#define level_is_unused61_at(level, x, y, z)             level_flag(level, is_unused61, point3d(x, y, z))
#define level_is_unused62_at(level, x, y, z)             level_flag(level, is_unused62, point3d(x, y, z))
#define level_is_unused63_at(level, x, y, z)             level_flag(level, is_unused63, point3d(x, y, z))
#define level_is_unused64_at(level, x, y, z)             level_flag(level, is_unused64, point3d(x, y, z))
#define level_is_unused65_at(level, x, y, z)             level_flag(level, is_unused65, point3d(x, y, z))
#define level_is_unused66_at(level, x, y, z)             level_flag(level, is_unused66, point3d(x, y, z))
#define level_is_unused67_at(level, x, y, z)             level_flag(level, is_unused67, point3d(x, y, z))
#define level_is_unused68_at(level, x, y, z)             level_flag(level, is_unused68, point3d(x, y, z))
#define level_is_unused69_at(level, x, y, z)             level_flag(level, is_unused69, point3d(x, y, z))
#define level_is_unused70_at(level, x, y, z)             level_flag(level, is_unused70, point3d(x, y, z))
#define level_is_unused71_at(level, x, y, z)             level_flag(level, is_unused71, point3d(x, y, z))
#define level_is_unused72_at(level, x, y, z)             level_flag(level, is_unused72, point3d(x, y, z))
#define level_is_unused73_at(level, x, y, z)             level_flag(level, is_unused73, point3d(x, y, z))
#define level_is_unused74_at(level, x, y, z)             level_flag(level, is_unused74, point3d(x, y, z))
#define level_is_unused75_at(level, x, y, z)             level_flag(level, is_unused75, point3d(x, y, z))
#define level_is_unused76_at(level, x, y, z)             level_flag(level, is_unused76, point3d(x, y, z))
#define level_is_unused77_at(level, x, y, z)             level_flag(level, is_unused77, point3d(x, y, z))
#define level_is_unused78_at(level, x, y, z)             level_flag(level, is_unused78, point3d(x, y, z))
#define level_is_unused79_at(level, x, y, z)             level_flag(level, is_unused79, point3d(x, y, z))
#define level_is_unused80_at(level, x, y, z)             level_flag(level, is_unused80, point3d(x, y, z))
#define level_is_unused81_at(level, x, y, z)             level_flag(level, is_unused81, point3d(x, y, z))
#define level_is_unused82_at(level, x, y, z)             level_flag(level, is_unused82, point3d(x, y, z))
#define level_is_unused83_at(level, x, y, z)             level_flag(level, is_unused83, point3d(x, y, z))
#define level_is_unused84_at(level, x, y, z)             level_flag(level, is_unused84, point3d(x, y, z))
#define level_is_unused85_at(level, x, y, z)             level_flag(level, is_unused85, point3d(x, y, z))
#define level_is_unused86_at(level, x, y, z)             level_flag(level, is_unused86, point3d(x, y, z))
#define level_is_unused87_at(level, x, y, z)             level_flag(level, is_unused87, point3d(x, y, z))
#define level_is_unused88_at(level, x, y, z)             level_flag(level, is_unused88, point3d(x, y, z))
#define level_is_unused89_at(level, x, y, z)             level_flag(level, is_unused89, point3d(x, y, z))
#define level_is_unused90_at(level, x, y, z)             level_flag(level, is_unused90, point3d(x, y, z))
#define level_is_unused91_at(level, x, y, z)             level_flag(level, is_unused91, point3d(x, y, z))
#define level_is_unused92_at(level, x, y, z)             level_flag(level, is_unused92, point3d(x, y, z))
#define level_is_unused93_at(level, x, y, z)             level_flag(level, is_unused93, point3d(x, y, z))
#define level_is_unused94_at(level, x, y, z)             level_flag(level, is_unused94, point3d(x, y, z))
#define level_is_unused95_at(level, x, y, z)             level_flag(level, is_unused95, point3d(x, y, z))
#define level_is_unused96_at(level, x, y, z)             level_flag(level, is_unused96, point3d(x, y, z))
#define level_is_unused97_at(level, x, y, z)             level_flag(level, is_unused97, point3d(x, y, z))
#define level_is_unused98_at(level, x, y, z)             level_flag(level, is_unused98, point3d(x, y, z))
#define level_is_unused99_at(level, x, y, z)             level_flag(level, is_unused99, point3d(x, y, z))
#define level_is_tickable_at(level, x, y, z)             level_flag(level, is_tickable, point3d(x, y, z))

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
#define level_is_unused1(level, p)              level_flag(level, is_unused1, p)
#define level_is_unused2(level, p)              level_flag(level, is_unused2, p)
#define level_is_unused3(level, p)              level_flag(level, is_unused3, p)
#define level_is_unused4(level, p)              level_flag(level, is_unused4, p)
#define level_is_unused5(level, p)              level_flag(level, is_unused5, p)
#define level_is_unused6(level, p)              level_flag(level, is_unused6, p)
#define level_is_unused7(level, p)              level_flag(level, is_unused7, p)
#define level_is_unused8(level, p)              level_flag(level, is_unused8, p)
#define level_is_unused9(level, p)              level_flag(level, is_unused9, p)
#define level_is_unused10(level, p)             level_flag(level, is_unused10, p)
#define level_is_unused11(level, p)             level_flag(level, is_unused11, p)
#define level_is_unused12(level, p)             level_flag(level, is_unused12, p)
#define level_is_unused13(level, p)             level_flag(level, is_unused13, p)
#define level_is_unused14(level, p)             level_flag(level, is_unused14, p)
#define level_is_unused15(level, p)             level_flag(level, is_unused15, p)
#define level_is_unused16(level, p)             level_flag(level, is_unused16, p)
#define level_is_unused17(level, p)             level_flag(level, is_unused17, p)
#define level_is_unused18(level, p)             level_flag(level, is_unused18, p)
#define level_is_unused19(level, p)             level_flag(level, is_unused19, p)
#define level_is_unused20(level, p)             level_flag(level, is_unused20, p)
#define level_is_unused21(level, p)             level_flag(level, is_unused21, p)
#define level_is_unused22(level, p)             level_flag(level, is_unused22, p)
#define level_is_unused23(level, p)             level_flag(level, is_unused23, p)
#define level_is_unused24(level, p)             level_flag(level, is_unused24, p)
#define level_is_unused25(level, p)             level_flag(level, is_unused25, p)
#define level_is_unused26(level, p)             level_flag(level, is_unused26, p)
#define level_is_unused27(level, p)             level_flag(level, is_unused27, p)
#define level_is_unused28(level, p)             level_flag(level, is_unused28, p)
#define level_is_unused29(level, p)             level_flag(level, is_unused29, p)
#define level_is_unused30(level, p)             level_flag(level, is_unused30, p)
#define level_is_unused31(level, p)             level_flag(level, is_unused31, p)
#define level_is_unused32(level, p)             level_flag(level, is_unused32, p)
#define level_is_unused33(level, p)             level_flag(level, is_unused33, p)
#define level_is_unused34(level, p)             level_flag(level, is_unused34, p)
#define level_is_unused35(level, p)             level_flag(level, is_unused35, p)
#define level_is_unused36(level, p)             level_flag(level, is_unused36, p)
#define level_is_unused37(level, p)             level_flag(level, is_unused37, p)
#define level_is_unused38(level, p)             level_flag(level, is_unused38, p)
#define level_is_unused39(level, p)             level_flag(level, is_unused39, p)
#define level_is_unused40(level, p)             level_flag(level, is_unused40, p)
#define level_is_unused41(level, p)             level_flag(level, is_unused41, p)
#define level_is_unused42(level, p)             level_flag(level, is_unused42, p)
#define level_is_unused43(level, p)             level_flag(level, is_unused43, p)
#define level_is_unused44(level, p)             level_flag(level, is_unused44, p)
#define level_is_unused45(level, p)             level_flag(level, is_unused45, p)
#define level_is_unused46(level, p)             level_flag(level, is_unused46, p)
#define level_is_unused47(level, p)             level_flag(level, is_unused47, p)
#define level_is_unused48(level, p)             level_flag(level, is_unused48, p)
#define level_is_unused49(level, p)             level_flag(level, is_unused49, p)
#define level_is_unused50(level, p)             level_flag(level, is_unused50, p)
#define level_is_unused51(level, p)             level_flag(level, is_unused51, p)
#define level_is_unused52(level, p)             level_flag(level, is_unused52, p)
#define level_is_unused53(level, p)             level_flag(level, is_unused53, p)
#define level_is_unused54(level, p)             level_flag(level, is_unused54, p)
#define level_is_unused55(level, p)             level_flag(level, is_unused55, p)
#define level_is_unused56(level, p)             level_flag(level, is_unused56, p)
#define level_is_unused57(level, p)             level_flag(level, is_unused57, p)
#define level_is_unused58(level, p)             level_flag(level, is_unused58, p)
#define level_is_unused59(level, p)             level_flag(level, is_unused59, p)
#define level_is_unused60(level, p)             level_flag(level, is_unused60, p)
#define level_is_unused61(level, p)             level_flag(level, is_unused61, p)
#define level_is_unused62(level, p)             level_flag(level, is_unused62, p)
#define level_is_unused63(level, p)             level_flag(level, is_unused63, p)
#define level_is_unused64(level, p)             level_flag(level, is_unused64, p)
#define level_is_unused65(level, p)             level_flag(level, is_unused65, p)
#define level_is_unused66(level, p)             level_flag(level, is_unused66, p)
#define level_is_unused67(level, p)             level_flag(level, is_unused67, p)
#define level_is_unused68(level, p)             level_flag(level, is_unused68, p)
#define level_is_unused69(level, p)             level_flag(level, is_unused69, p)
#define level_is_unused70(level, p)             level_flag(level, is_unused70, p)
#define level_is_unused71(level, p)             level_flag(level, is_unused71, p)
#define level_is_unused72(level, p)             level_flag(level, is_unused72, p)
#define level_is_unused73(level, p)             level_flag(level, is_unused73, p)
#define level_is_unused74(level, p)             level_flag(level, is_unused74, p)
#define level_is_unused75(level, p)             level_flag(level, is_unused75, p)
#define level_is_unused76(level, p)             level_flag(level, is_unused76, p)
#define level_is_unused77(level, p)             level_flag(level, is_unused77, p)
#define level_is_unused78(level, p)             level_flag(level, is_unused78, p)
#define level_is_unused79(level, p)             level_flag(level, is_unused79, p)
#define level_is_unused80(level, p)             level_flag(level, is_unused80, p)
#define level_is_unused81(level, p)             level_flag(level, is_unused81, p)
#define level_is_unused82(level, p)             level_flag(level, is_unused82, p)
#define level_is_unused83(level, p)             level_flag(level, is_unused83, p)
#define level_is_unused84(level, p)             level_flag(level, is_unused84, p)
#define level_is_unused85(level, p)             level_flag(level, is_unused85, p)
#define level_is_unused86(level, p)             level_flag(level, is_unused86, p)
#define level_is_unused87(level, p)             level_flag(level, is_unused87, p)
#define level_is_unused88(level, p)             level_flag(level, is_unused88, p)
#define level_is_unused89(level, p)             level_flag(level, is_unused89, p)
#define level_is_unused90(level, p)             level_flag(level, is_unused90, p)
#define level_is_unused91(level, p)             level_flag(level, is_unused91, p)
#define level_is_unused92(level, p)             level_flag(level, is_unused92, p)
#define level_is_unused93(level, p)             level_flag(level, is_unused93, p)
#define level_is_unused94(level, p)             level_flag(level, is_unused94, p)
#define level_is_unused95(level, p)             level_flag(level, is_unused95, p)
#define level_is_unused96(level, p)             level_flag(level, is_unused96, p)
#define level_is_unused97(level, p)             level_flag(level, is_unused97, p)
#define level_is_unused98(level, p)             level_flag(level, is_unused98, p)
#define level_is_unused99(level, p)             level_flag(level, is_unused99, p)
#define level_is_tickable(level, p)             level_flag(level, is_tickable, p)

ENUM_DEF_H(THING_FLAG_ENUM, ThingFlag)

#endif
