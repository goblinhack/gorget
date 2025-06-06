//
// Copyright goblinhack@gmail.com
//

#pragma once
#ifndef _MY_THING_TEMPLATE_H_
#define _MY_THING_TEMPLATE_H_

#include "my_enum.hpp"
#include "my_minimal.hpp"

#include <stdarg.h>

#define THING_FLAG_ENUM(list_macro)                                                                                  \
  list_macro(is_walk_through_walls, "is_walk_through_walls"),                     /* ............................ */ \
      list_macro(is_able_to_walk_through_walls, "is_able_to_walk_through_walls"), /* ............................ */ \
      list_macro(is_animated_can_hflip, "is_animated_can_hflip"),                 /* ............................ */ \
      list_macro(is_animated_no_dir, "is_animated_no_dir"),                       /* ............................ */ \
      list_macro(is_animated_same_first_tile, "is_animated_same_first_tile"),     /* ............................ */ \
      list_macro(is_animated, "is_animated"),                                     /* ............................ */ \
      list_macro(is_barrel, "is_barrel"),                                         /* ............................ */ \
      list_macro(is_blit_centered, "is_blit_centered"),                           /* ............................ */ \
      list_macro(is_blit_on_ground, "is_blit_on_ground"),                         /* ............................ */ \
      list_macro(is_blit_outlined, "is_blit_outlined"),                           /* ............................ */ \
      list_macro(is_blit_square_outlined, "is_blit_square_outlined"),             /* ............................ */ \
      list_macro(is_brazier, "is_brazier"),                                       /* ............................ */ \
      list_macro(is_bridge, "is_bridge"),                                         /* ............................ */ \
      list_macro(is_chasm, "is_chasm"),                                           /* ............................ */ \
      list_macro(is_corridor, "is_corridor"),                                     /* ............................ */ \
      list_macro(is_crushable_underfoot, "is_crushable_underfoot"),               /* ............................ */ \
      list_macro(is_cursor_hazard, "is_cursor_hazard"),                           /* ............................ */ \
      list_macro(is_cursor_path_blocker, "is_cursor_path_blocker"),               /* ............................ */ \
      list_macro(is_cursor_path_hazard, "is_cursor_path_hazard"),                 /* ............................ */ \
      list_macro(is_cursor_path, "is_cursor_path"),                               /* ............................ */ \
      list_macro(is_cursor, "is_cursor"),                                         /* ............................ */ \
      list_macro(is_deep_water, "is_deep_water"),                                 /* ............................ */ \
      list_macro(is_described_cursor, "is_described_cursor"),                     /* ............................ */ \
      list_macro(is_dirt, "is_dirt"),                                             /* ............................ */ \
      list_macro(is_door, "is_door"),                                             /* ............................ */ \
      list_macro(is_dungeon_entrance, "is_dungeon_entrance"),                     /* ............................ */ \
      list_macro(is_entrance, "is_entrance"),                                     /* ............................ */ \
      list_macro(is_ethereal, "is_ethereal"),                                     /* ............................ */ \
      list_macro(is_exit, "is_exit"),                                             /* ............................ */ \
      list_macro(is_floor, "is_floor"),                                           /* ............................ */ \
      list_macro(is_foliage, "is_foliage"),                                       /* ............................ */ \
      list_macro(is_ghost, "is_ghost"),                                           /* ............................ */ \
      list_macro(is_goblin, "is_goblin"),                                         /* ............................ */ \
      list_macro(is_grass, "is_grass"),                                           /* ............................ */ \
      list_macro(is_key, "is_key"),                                               /* ............................ */ \
      list_macro(is_lava, "is_lava"),                                             /* ............................ */ \
      list_macro(is_level_across, "is_level_across"),                             /* ............................ */ \
      list_macro(is_level_curr, "is_level_curr"),                                 /* ............................ */ \
      list_macro(is_level_down, "is_level_down"),                                 /* ............................ */ \
      list_macro(is_level_final, "is_level_final"),                               /* ............................ */ \
      list_macro(is_level_next, "is_level_next"),                                 /* ............................ */ \
      list_macro(is_level_not_visited, "is_level_not_visited"),                   /* ............................ */ \
      list_macro(is_level_visited, "is_level_visited"),                           /* ............................ */ \
      list_macro(is_levitating, "is_levitating"),                                 /* ............................ */ \
      list_macro(is_light_source, "is_light_source"),                             /* ............................ */ \
      list_macro(is_minion, "is_minion"),                                         /* ............................ */ \
      list_macro(is_mob, "is_mob"),                                               /* ............................ */ \
      list_macro(is_mob1, "is_mob1"),                                             /* ............................ */ \
      list_macro(is_mob2, "is_mob2"),                                             /* ............................ */ \
      list_macro(is_monst, "is_monst"),                                           /* ............................ */ \
      list_macro(is_monst1, "is_monst1"),                                         /* ............................ */ \
      list_macro(is_monst2, "is_monst2"),                                         /* ............................ */ \
      list_macro(is_obstacle_block_or_door, "is_obstacle_block_or_door"),         /* ............................ */ \
      list_macro(is_obstacle_block, "is_obstacle_block"),                         /* ............................ */ \
      list_macro(is_pillar, "is_pillar"),                                         /* ............................ */ \
      list_macro(is_player, "is_player"),                                         /* ............................ */ \
      list_macro(is_rock, "is_rock"),                                             /* ............................ */ \
      list_macro(is_secret_door, "is_secret_door"),                               /* ............................ */ \
      list_macro(is_slime, "is_slime"),                                           /* ............................ */ \
      list_macro(is_teleport, "is_teleport"),                                     /* ............................ */ \
      list_macro(is_tickable, "is_tickable"),                                     /* ............................ */ \
      list_macro(is_tiled, "is_tiled"),                                           /* ............................ */ \
      list_macro(is_trap, "is_trap"),                                             /* ............................ */ \
      list_macro(is_treasure, "is_treasure"),                                     /* ............................ */ \
      list_macro(is_treasure1, "is_treasure1"),                                   /* ............................ */ \
      list_macro(is_treasure2, "is_treasure2"),                                   /* ............................ */ \
      list_macro(is_unused1, "is_unused1"),                                       /* ............................ */ \
      list_macro(is_unused10, "is_unused10"),                                     /* ............................ */ \
      list_macro(is_unused11, "is_unused11"),                                     /* ............................ */ \
      list_macro(is_unused12, "is_unused12"),                                     /* ............................ */ \
      list_macro(is_unused13, "is_unused13"),                                     /* ............................ */ \
      list_macro(is_unused14, "is_unused14"),                                     /* ............................ */ \
      list_macro(is_unused15, "is_unused15"),                                     /* ............................ */ \
      list_macro(is_unused16, "is_unused16"),                                     /* ............................ */ \
      list_macro(is_unused17, "is_unused17"),                                     /* ............................ */ \
      list_macro(is_unused18, "is_unused18"),                                     /* ............................ */ \
      list_macro(is_unused19, "is_unused19"),                                     /* ............................ */ \
      list_macro(is_unused2, "is_unused2"),                                       /* ............................ */ \
      list_macro(is_unused20, "is_unused20"),                                     /* ............................ */ \
      list_macro(is_unused21, "is_unused21"),                                     /* ............................ */ \
      list_macro(is_unused22, "is_unused22"),                                     /* ............................ */ \
      list_macro(is_unused23, "is_unused23"),                                     /* ............................ */ \
      list_macro(is_unused24, "is_unused24"),                                     /* ............................ */ \
      list_macro(is_unused25, "is_unused25"),                                     /* ............................ */ \
      list_macro(is_unused26, "is_unused26"),                                     /* ............................ */ \
      list_macro(is_unused27, "is_unused27"),                                     /* ............................ */ \
      list_macro(is_unused28, "is_unused28"),                                     /* ............................ */ \
      list_macro(is_unused29, "is_unused29"),                                     /* ............................ */ \
      list_macro(is_unused3, "is_unused3"),                                       /* ............................ */ \
      list_macro(is_unused30, "is_unused30"),                                     /* ............................ */ \
      list_macro(is_unused31, "is_unused31"),                                     /* ............................ */ \
      list_macro(is_unused32, "is_unused32"),                                     /* ............................ */ \
      list_macro(is_unused33, "is_unused33"),                                     /* ............................ */ \
      list_macro(is_unused34, "is_unused34"),                                     /* ............................ */ \
      list_macro(is_unused35, "is_unused35"),                                     /* ............................ */ \
      list_macro(is_unused36, "is_unused36"),                                     /* ............................ */ \
      list_macro(is_unused37, "is_unused37"),                                     /* ............................ */ \
      list_macro(is_unused38, "is_unused38"),                                     /* ............................ */ \
      list_macro(is_unused39, "is_unused39"),                                     /* ............................ */ \
      list_macro(is_unused4, "is_unused4"),                                       /* ............................ */ \
      list_macro(is_unused40, "is_unused40"),                                     /* ............................ */ \
      list_macro(is_unused41, "is_unused41"),                                     /* ............................ */ \
      list_macro(is_unused42, "is_unused42"),                                     /* ............................ */ \
      list_macro(is_unused43, "is_unused43"),                                     /* ............................ */ \
      list_macro(is_unused44, "is_unused44"),                                     /* ............................ */ \
      list_macro(is_unused45, "is_unused45"),                                     /* ............................ */ \
      list_macro(is_unused46, "is_unused46"),                                     /* ............................ */ \
      list_macro(is_unused47, "is_unused47"),                                     /* ............................ */ \
      list_macro(is_unused48, "is_unused48"),                                     /* ............................ */ \
      list_macro(is_unused49, "is_unused49"),                                     /* ............................ */ \
      list_macro(is_unused5, "is_unused5"),                                       /* ............................ */ \
      list_macro(is_unused50, "is_unused50"),                                     /* ............................ */ \
      list_macro(is_unused51, "is_unused51"),                                     /* ............................ */ \
      list_macro(is_unused52, "is_unused52"),                                     /* ............................ */ \
      list_macro(is_unused53, "is_unused53"),                                     /* ............................ */ \
      list_macro(is_unused54, "is_unused54"),                                     /* ............................ */ \
      list_macro(is_unused55, "is_unused55"),                                     /* ............................ */ \
      list_macro(is_unused56, "is_unused56"),                                     /* ............................ */ \
      list_macro(is_loggable, "is_loggable"),                                     /* ............................ */ \
      list_macro(is_unused6, "is_unused6"),                                       /* ............................ */ \
      list_macro(is_unused7, "is_unused7"),                                       /* ............................ */ \
      list_macro(is_unused8, "is_unused8"),                                       /* ............................ */ \
      list_macro(is_unused9, "is_unused9"),                                       /* ............................ */ \
      list_macro(is_wall, "is_wall"),                                             /* ............................ */ \
      list_macro(is_water, "is_water"),                                           /* ............................ */ \
      list_macro(THING_FLAG_MAX, "THING_FLAG_MAX"),

ENUM_DEF_H(THING_FLAG_ENUM, ThingFlag)

// begin sort marker1 {
#define tp_is_able_to_walk_through_walls(tp) tp_flag(tp, is_able_to_walk_through_walls)
#define tp_is_animated_can_hflip(tp)         tp_flag(tp, is_animated_can_hflip)
#define tp_is_animated_no_dir(tp)            tp_flag(tp, is_animated_no_dir)
#define tp_is_animated_same_first_tile(tp)   tp_flag(tp, is_animated_same_first_tile)
#define tp_is_animated(tp)                   tp_flag(tp, is_animated)
#define tp_is_barrel(tp)                     tp_flag(tp, is_barrel)
#define tp_is_blit_centered(tp)              tp_flag(tp, is_blit_centered)
#define tp_is_blit_on_ground(tp)             tp_flag(tp, is_blit_on_ground)
#define tp_is_blit_outlined(tp)              tp_flag(tp, is_blit_outlined)
#define tp_is_blit_square_outlined(tp)       tp_flag(tp, is_blit_square_outlined)
#define tp_is_brazier(tp)                    tp_flag(tp, is_brazier)
#define tp_is_bridge(tp)                     tp_flag(tp, is_bridge)
#define tp_is_chasm(tp)                      tp_flag(tp, is_chasm)
#define tp_is_corridor(tp)                   tp_flag(tp, is_corridor)
#define tp_is_crushable_underfoot(tp)        tp_flag(tp, is_crushable_underfoot)
#define tp_is_cursor_hazard(tp)              tp_flag(tp, is_cursor_hazard)
#define tp_is_cursor_path_blocker(tp)        tp_flag(tp, is_cursor_path_blocker)
#define tp_is_cursor_path_hazard(tp)         tp_flag(tp, is_cursor_path_hazard)
#define tp_is_cursor_path(tp)                tp_flag(tp, is_cursor_path)
#define tp_is_cursor(tp)                     tp_flag(tp, is_cursor)
#define tp_is_deep_water(tp)                 tp_flag(tp, is_deep_water)
#define tp_is_described_cursor(tp)           tp_flag(tp, is_described_cursor)
#define tp_is_dirt(tp)                       tp_flag(tp, is_dirt)
#define tp_is_door(tp)                       tp_flag(tp, is_door)
#define tp_is_dungeon_entrance(tp)           tp_flag(tp, is_dungeon_entrance)
#define tp_is_entrance(tp)                   tp_flag(tp, is_entrance)
#define tp_is_ethereal(tp)                   tp_flag(tp, is_ethereal)
#define tp_is_exit(tp)                       tp_flag(tp, is_exit)
#define tp_is_floor(tp)                      tp_flag(tp, is_floor)
#define tp_is_foliage(tp)                    tp_flag(tp, is_foliage)
#define tp_is_ghost(tp)                      tp_flag(tp, is_ghost)
#define tp_is_goblin(tp)                     tp_flag(tp, is_goblin)
#define tp_is_grass(tp)                      tp_flag(tp, is_grass)
#define tp_is_key(tp)                        tp_flag(tp, is_key)
#define tp_is_lava(tp)                       tp_flag(tp, is_lava)
#define tp_is_level_across(tp)               tp_flag(tp, is_level_across)
#define tp_is_level_curr(tp)                 tp_flag(tp, is_level_curr)
#define tp_is_level_down(tp)                 tp_flag(tp, is_level_down)
#define tp_is_level_final(tp)                tp_flag(tp, is_level_final)
#define tp_is_level_next(tp)                 tp_flag(tp, is_level_next)
#define tp_is_level_not_visited(tp)          tp_flag(tp, is_level_not_visited)
#define tp_is_level_visited(tp)              tp_flag(tp, is_level_visited)
#define tp_is_levitating(tp)                 tp_flag(tp, is_levitating)
#define tp_is_light_source(tp)               tp_flag(tp, is_light_source)
#define tp_is_loggable(tp)                   tp_flag(tp, is_loggable)
#define tp_is_minion(tp)                     tp_flag(tp, is_minion)
#define tp_is_mob(tp)                        tp_flag(tp, is_mob)
#define tp_is_mob1(tp)                       tp_flag(tp, is_mob1)
#define tp_is_mob2(tp)                       tp_flag(tp, is_mob2)
#define tp_is_monst(tp)                      tp_flag(tp, is_monst)
#define tp_is_monst1(tp)                     tp_flag(tp, is_monst1)
#define tp_is_monst2(tp)                     tp_flag(tp, is_monst2)
#define tp_is_obstacle_block_or_door(tp)     tp_flag(tp, is_obstacle_block_or_door)
#define tp_is_obstacle_block(tp)             tp_flag(tp, is_obstacle_block)
#define tp_is_pillar(tp)                     tp_flag(tp, is_pillar)
#define tp_is_player(tp)                     tp_flag(tp, is_player)
#define tp_is_rock(tp)                       tp_flag(tp, is_rock)
#define tp_is_secret_door(tp)                tp_flag(tp, is_secret_door)
#define tp_is_slime(tp)                      tp_flag(tp, is_slime)
#define tp_is_teleport(tp)                   tp_flag(tp, is_teleport)
#define tp_is_tickable(tp)                   tp_flag(tp, is_tickable)
#define tp_is_tiled(tp)                      tp_flag(tp, is_tiled)
#define tp_is_trap(tp)                       tp_flag(tp, is_trap)
#define tp_is_treasure(tp)                   tp_flag(tp, is_treasure)
#define tp_is_treasure1(tp)                  tp_flag(tp, is_treasure1)
#define tp_is_treasure2(tp)                  tp_flag(tp, is_treasure2)
#define tp_is_unused1(tp)                    tp_flag(tp, is_unused1)
#define tp_is_unused10(tp)                   tp_flag(tp, is_unused10)
#define tp_is_unused11(tp)                   tp_flag(tp, is_unused11)
#define tp_is_unused12(tp)                   tp_flag(tp, is_unused12)
#define tp_is_unused13(tp)                   tp_flag(tp, is_unused13)
#define tp_is_unused14(tp)                   tp_flag(tp, is_unused14)
#define tp_is_unused15(tp)                   tp_flag(tp, is_unused15)
#define tp_is_unused16(tp)                   tp_flag(tp, is_unused16)
#define tp_is_unused17(tp)                   tp_flag(tp, is_unused17)
#define tp_is_unused18(tp)                   tp_flag(tp, is_unused18)
#define tp_is_unused19(tp)                   tp_flag(tp, is_unused19)
#define tp_is_unused2(tp)                    tp_flag(tp, is_unused2)
#define tp_is_unused20(tp)                   tp_flag(tp, is_unused20)
#define tp_is_unused21(tp)                   tp_flag(tp, is_unused21)
#define tp_is_unused22(tp)                   tp_flag(tp, is_unused22)
#define tp_is_unused23(tp)                   tp_flag(tp, is_unused23)
#define tp_is_unused24(tp)                   tp_flag(tp, is_unused24)
#define tp_is_unused25(tp)                   tp_flag(tp, is_unused25)
#define tp_is_unused26(tp)                   tp_flag(tp, is_unused26)
#define tp_is_unused27(tp)                   tp_flag(tp, is_unused27)
#define tp_is_unused28(tp)                   tp_flag(tp, is_unused28)
#define tp_is_unused29(tp)                   tp_flag(tp, is_unused29)
#define tp_is_unused3(tp)                    tp_flag(tp, is_unused3)
#define tp_is_unused30(tp)                   tp_flag(tp, is_unused30)
#define tp_is_unused31(tp)                   tp_flag(tp, is_unused31)
#define tp_is_unused32(tp)                   tp_flag(tp, is_unused32)
#define tp_is_unused33(tp)                   tp_flag(tp, is_unused33)
#define tp_is_unused34(tp)                   tp_flag(tp, is_unused34)
#define tp_is_unused35(tp)                   tp_flag(tp, is_unused35)
#define tp_is_unused36(tp)                   tp_flag(tp, is_unused36)
#define tp_is_unused37(tp)                   tp_flag(tp, is_unused37)
#define tp_is_unused38(tp)                   tp_flag(tp, is_unused38)
#define tp_is_unused39(tp)                   tp_flag(tp, is_unused39)
#define tp_is_unused4(tp)                    tp_flag(tp, is_unused4)
#define tp_is_unused40(tp)                   tp_flag(tp, is_unused40)
#define tp_is_unused41(tp)                   tp_flag(tp, is_unused41)
#define tp_is_unused42(tp)                   tp_flag(tp, is_unused42)
#define tp_is_unused43(tp)                   tp_flag(tp, is_unused43)
#define tp_is_unused44(tp)                   tp_flag(tp, is_unused44)
#define tp_is_unused45(tp)                   tp_flag(tp, is_unused45)
#define tp_is_unused46(tp)                   tp_flag(tp, is_unused46)
#define tp_is_unused47(tp)                   tp_flag(tp, is_unused47)
#define tp_is_unused48(tp)                   tp_flag(tp, is_unused48)
#define tp_is_unused49(tp)                   tp_flag(tp, is_unused49)
#define tp_is_unused5(tp)                    tp_flag(tp, is_unused5)
#define tp_is_unused50(tp)                   tp_flag(tp, is_unused50)
#define tp_is_unused51(tp)                   tp_flag(tp, is_unused51)
#define tp_is_unused52(tp)                   tp_flag(tp, is_unused52)
#define tp_is_unused53(tp)                   tp_flag(tp, is_unused53)
#define tp_is_unused54(tp)                   tp_flag(tp, is_unused54)
#define tp_is_unused55(tp)                   tp_flag(tp, is_unused55)
#define tp_is_unused56(tp)                   tp_flag(tp, is_unused56)
#define tp_is_unused6(tp)                    tp_flag(tp, is_unused6)
#define tp_is_unused7(tp)                    tp_flag(tp, is_unused7)
#define tp_is_unused8(tp)                    tp_flag(tp, is_unused8)
#define tp_is_unused9(tp)                    tp_flag(tp, is_unused9)
#define tp_is_walk_through_walls(tp)         tp_flag(tp, is_walk_through_walls)
#define tp_is_wall(tp)                       tp_flag(tp, is_wall)
#define tp_is_water(tp)                      tp_flag(tp, is_water)
// end sort marker1 }

// begin sort marker3 {
#define level_is_able_to_walk_through_walls(g, v, l, p) level_flag(g, v, l, is_able_to_walk_through_walls, p)
#define level_is_animated_can_hflip(g, v, l, p)         level_flag(g, v, l, is_animated_can_hflip, p)
#define level_is_animated_no_dir(g, v, l, p)            level_flag(g, v, l, is_animated_no_dir, p)
#define level_is_animated_same_first_tile(g, v, l, p)   level_flag(g, v, l, is_animated_same_first_tile, p)
#define level_is_animated(g, v, l, p)                   level_flag(g, v, l, is_animated, p)
#define level_is_barrel(g, v, l, p)                     level_flag(g, v, l, is_barrel, p)
#define level_is_blit_centered(g, v, l, p)              level_flag(g, v, l, is_blit_centered, p)
#define level_is_blit_on_ground(g, v, l, p)             level_flag(g, v, l, is_blit_on_ground, p)
#define level_is_blit_outlined(g, v, l, p)              level_flag(g, v, l, is_blit_outlined, p)
#define level_is_blit_square_outlined(g, v, l, p)       level_flag(g, v, l, is_blit_square_outlined, p)
#define level_is_brazier(g, v, l, p)                    level_flag(g, v, l, is_brazier, p)
#define level_is_bridge(g, v, l, p)                     level_flag(g, v, l, is_bridge, p)
#define level_is_chasm(g, v, l, p)                      level_flag(g, v, l, is_chasm, p)
#define level_is_corridor(g, v, l, p)                   level_flag(g, v, l, is_corridor, p)
#define level_is_crushable_underfoot(g, v, l, p)        level_flag(g, v, l, is_crushable_underfoot, p)
#define level_is_cursor_hazard(g, v, l, p)              level_flag(g, v, l, is_cursor_hazard, p)
#define level_is_cursor_path_blocker(g, v, l, p)        level_flag(g, v, l, is_cursor_path_blocker, p)
#define level_is_cursor_path_hazard(g, v, l, p)         level_flag(g, v, l, is_cursor_path_hazard, p)
#define level_is_cursor_path(g, v, l, p)                level_flag(g, v, l, is_cursor_path, p)
#define level_is_cursor(g, v, l, p)                     level_flag(g, v, l, is_cursor, p)
#define level_is_deep_water(g, v, l, p)                 level_flag(g, v, l, is_deep_water, p)
#define level_is_described_cursor(g, v, l, p)           level_flag(g, v, l, is_described_cursor, p)
#define level_is_dirt(g, v, l, p)                       level_flag(g, v, l, is_dirt, p)
#define level_is_door(g, v, l, p)                       level_flag(g, v, l, is_door, p)
#define level_is_dungeon_entrance(g, v, l, p)           level_flag(g, v, l, is_dungeon_entrance, p)
#define level_is_entrance(g, v, l, p)                   level_flag(g, v, l, is_entrance, p)
#define level_is_ethereal(g, v, l, p)                   level_flag(g, v, l, is_ethereal, p)
#define level_is_exit(g, v, l, p)                       level_flag(g, v, l, is_exit, p)
#define level_is_floor(g, v, l, p)                      level_flag(g, v, l, is_floor, p)
#define level_is_foliage(g, v, l, p)                    level_flag(g, v, l, is_foliage, p)
#define level_is_ghost(g, v, l, p)                      level_flag(g, v, l, is_ghost, p)
#define level_is_goblin(g, v, l, p)                     level_flag(g, v, l, is_goblin, p)
#define level_is_grass(g, v, l, p)                      level_flag(g, v, l, is_grass, p)
#define level_is_key(g, v, l, p)                        level_flag(g, v, l, is_key, p)
#define level_is_lava(g, v, l, p)                       level_flag(g, v, l, is_lava, p)
#define level_is_level_across(g, v, l, p)               level_flag(g, v, l, is_level_across, p)
#define level_is_level_curr(g, v, l, p)                 level_flag(g, v, l, is_level_curr, p)
#define level_is_level_down(g, v, l, p)                 level_flag(g, v, l, is_level_down, p)
#define level_is_level_final(g, v, l, p)                level_flag(g, v, l, is_level_final, p)
#define level_is_level_next(g, v, l, p)                 level_flag(g, v, l, is_level_next, p)
#define level_is_level_not_visited(g, v, l, p)          level_flag(g, v, l, is_level_not_visited, p)
#define level_is_level_visited(g, v, l, p)              level_flag(g, v, l, is_level_visited, p)
#define level_is_levitating(g, v, l, p)                 level_flag(g, v, l, is_levitating, p)
#define level_is_light_source(g, v, l, p)               level_flag(g, v, l, is_light_source, p)
#define level_is_loggable(g, v, l, p)                   level_flag(g, v, l, is_loggable, p)
#define level_is_minion(g, v, l, p)                     level_flag(g, v, l, is_minion, p)
#define level_is_mob(g, v, l, p)                        level_flag(g, v, l, is_mob, p)
#define level_is_mob1(g, v, l, p)                       level_flag(g, v, l, is_mob1, p)
#define level_is_mob2(g, v, l, p)                       level_flag(g, v, l, is_mob2, p)
#define level_is_monst(g, v, l, p)                      level_flag(g, v, l, is_monst, p)
#define level_is_monst1(g, v, l, p)                     level_flag(g, v, l, is_monst1, p)
#define level_is_monst2(g, v, l, p)                     level_flag(g, v, l, is_monst2, p)
#define level_is_obstacle_block_or_door(g, v, l, p)     level_flag(g, v, l, is_obstacle_block_or_door, p)
#define level_is_obstacle_block(g, v, l, p)             level_flag(g, v, l, is_obstacle_block, p)
#define level_is_pillar(g, v, l, p)                     level_flag(g, v, l, is_pillar, p)
#define level_is_player(g, v, l, p)                     level_flag(g, v, l, is_player, p)
#define level_is_rock(g, v, l, p)                       level_flag(g, v, l, is_rock, p)
#define level_is_secret_door(g, v, l, p)                level_flag(g, v, l, is_secret_door, p)
#define level_is_slime(g, v, l, p)                      level_flag(g, v, l, is_slime, p)
#define level_is_teleport(g, v, l, p)                   level_flag(g, v, l, is_teleport, p)
#define level_is_tickable(g, v, l, p)                   level_flag(g, v, l, is_tickable, p)
#define level_is_tiled(g, v, l, p)                      level_flag(g, v, l, is_tiled, p)
#define level_is_trap(g, v, l, p)                       level_flag(g, v, l, is_trap, p)
#define level_is_treasure(g, v, l, p)                   level_flag(g, v, l, is_treasure, p)
#define level_is_treasure1(g, v, l, p)                  level_flag(g, v, l, is_treasure1, p)
#define level_is_treasure2(g, v, l, p)                  level_flag(g, v, l, is_treasure2, p)
#define level_is_unused1(g, v, l, p)                    level_flag(g, v, l, is_unused1, p)
#define level_is_unused10(g, v, l, p)                   level_flag(g, v, l, is_unused10, p)
#define level_is_unused11(g, v, l, p)                   level_flag(g, v, l, is_unused11, p)
#define level_is_unused12(g, v, l, p)                   level_flag(g, v, l, is_unused12, p)
#define level_is_unused13(g, v, l, p)                   level_flag(g, v, l, is_unused13, p)
#define level_is_unused14(g, v, l, p)                   level_flag(g, v, l, is_unused14, p)
#define level_is_unused15(g, v, l, p)                   level_flag(g, v, l, is_unused15, p)
#define level_is_unused16(g, v, l, p)                   level_flag(g, v, l, is_unused16, p)
#define level_is_unused17(g, v, l, p)                   level_flag(g, v, l, is_unused17, p)
#define level_is_unused18(g, v, l, p)                   level_flag(g, v, l, is_unused18, p)
#define level_is_unused19(g, v, l, p)                   level_flag(g, v, l, is_unused19, p)
#define level_is_unused2(g, v, l, p)                    level_flag(g, v, l, is_unused2, p)
#define level_is_unused20(g, v, l, p)                   level_flag(g, v, l, is_unused20, p)
#define level_is_unused21(g, v, l, p)                   level_flag(g, v, l, is_unused21, p)
#define level_is_unused22(g, v, l, p)                   level_flag(g, v, l, is_unused22, p)
#define level_is_unused23(g, v, l, p)                   level_flag(g, v, l, is_unused23, p)
#define level_is_unused24(g, v, l, p)                   level_flag(g, v, l, is_unused24, p)
#define level_is_unused25(g, v, l, p)                   level_flag(g, v, l, is_unused25, p)
#define level_is_unused26(g, v, l, p)                   level_flag(g, v, l, is_unused26, p)
#define level_is_unused27(g, v, l, p)                   level_flag(g, v, l, is_unused27, p)
#define level_is_unused28(g, v, l, p)                   level_flag(g, v, l, is_unused28, p)
#define level_is_unused29(g, v, l, p)                   level_flag(g, v, l, is_unused29, p)
#define level_is_unused3(g, v, l, p)                    level_flag(g, v, l, is_unused3, p)
#define level_is_unused30(g, v, l, p)                   level_flag(g, v, l, is_unused30, p)
#define level_is_unused31(g, v, l, p)                   level_flag(g, v, l, is_unused31, p)
#define level_is_unused32(g, v, l, p)                   level_flag(g, v, l, is_unused32, p)
#define level_is_unused33(g, v, l, p)                   level_flag(g, v, l, is_unused33, p)
#define level_is_unused34(g, v, l, p)                   level_flag(g, v, l, is_unused34, p)
#define level_is_unused35(g, v, l, p)                   level_flag(g, v, l, is_unused35, p)
#define level_is_unused36(g, v, l, p)                   level_flag(g, v, l, is_unused36, p)
#define level_is_unused37(g, v, l, p)                   level_flag(g, v, l, is_unused37, p)
#define level_is_unused38(g, v, l, p)                   level_flag(g, v, l, is_unused38, p)
#define level_is_unused39(g, v, l, p)                   level_flag(g, v, l, is_unused39, p)
#define level_is_unused4(g, v, l, p)                    level_flag(g, v, l, is_unused4, p)
#define level_is_unused40(g, v, l, p)                   level_flag(g, v, l, is_unused40, p)
#define level_is_unused41(g, v, l, p)                   level_flag(g, v, l, is_unused41, p)
#define level_is_unused42(g, v, l, p)                   level_flag(g, v, l, is_unused42, p)
#define level_is_unused43(g, v, l, p)                   level_flag(g, v, l, is_unused43, p)
#define level_is_unused44(g, v, l, p)                   level_flag(g, v, l, is_unused44, p)
#define level_is_unused45(g, v, l, p)                   level_flag(g, v, l, is_unused45, p)
#define level_is_unused46(g, v, l, p)                   level_flag(g, v, l, is_unused46, p)
#define level_is_unused47(g, v, l, p)                   level_flag(g, v, l, is_unused47, p)
#define level_is_unused48(g, v, l, p)                   level_flag(g, v, l, is_unused48, p)
#define level_is_unused49(g, v, l, p)                   level_flag(g, v, l, is_unused49, p)
#define level_is_unused5(g, v, l, p)                    level_flag(g, v, l, is_unused5, p)
#define level_is_unused50(g, v, l, p)                   level_flag(g, v, l, is_unused50, p)
#define level_is_unused51(g, v, l, p)                   level_flag(g, v, l, is_unused51, p)
#define level_is_unused52(g, v, l, p)                   level_flag(g, v, l, is_unused52, p)
#define level_is_unused53(g, v, l, p)                   level_flag(g, v, l, is_unused53, p)
#define level_is_unused54(g, v, l, p)                   level_flag(g, v, l, is_unused54, p)
#define level_is_unused55(g, v, l, p)                   level_flag(g, v, l, is_unused55, p)
#define level_is_unused56(g, v, l, p)                   level_flag(g, v, l, is_unused56, p)
#define level_is_unused6(g, v, l, p)                    level_flag(g, v, l, is_unused6, p)
#define level_is_unused7(g, v, l, p)                    level_flag(g, v, l, is_unused7, p)
#define level_is_unused8(g, v, l, p)                    level_flag(g, v, l, is_unused8, p)
#define level_is_unused9(g, v, l, p)                    level_flag(g, v, l, is_unused9, p)
#define level_is_walk_through_walls(g, v, l, p)         level_flag(g, v, l, is_walk_through_walls, p)
#define level_is_wall(g, v, l, p)                       level_flag(g, v, l, is_wall, p)
#define level_is_water(g, v, l, p)                      level_flag(g, v, l, is_water, p)
// end sort marker3 }

enum {
  MAP_Z_DEPTH_FLOOR,
  MAP_Z_DEPTH_LIQUID,  /* e.g. water */
  MAP_Z_DEPTH_LIQUID2, /* e.g. deep water */
  MAP_Z_DEPTH_OBJ,     /* e.g water */
  MAP_Z_DEPTH_LAST
};
#define MAP_Z_DEPTH_FIRST MAP_Z_DEPTH_FLOOR

#define FOR_ALL_Z_DEPTH(_z_depth_)                                                                                   \
  for (uint8_t _z_depth_ = MAP_Z_DEPTH_FIRST; _z_depth_ < MAP_Z_DEPTH_LAST; _z_depth_++)

enum { MAP_Z_PRIO_BEHIND, MAP_Z_PRIO_NORMAL, MAP_Z_PRIO_INFRONT, MAP_Z_PRIO_LAST };
#define MAP_Z_PRIO_FIRST MAP_Z_PRIO_BEHIND

#define FOR_ALL_Z_PRIO(_z_prio_) for (uint8_t _z_prio_ = MAP_Z_PRIO_FIRST; _z_prio_ < MAP_Z_PRIO_LAST; _z_prio_++)

enum { MONST_CLASS_A, MONST_CLASS_MAX };

enum {
  THING_ANIM_JOIN_BL,     /* alias for IS_JOIN_BL,   */
  THING_ANIM_JOIN_BL2,    /* alias for IS_JOIN_BL2,  */
  THING_ANIM_JOIN_BLOCK,  /* alias for IS_JOIN_BLOCK */
  THING_ANIM_JOIN_BOT,    /* alias for IS_JOIN_BOT,  */
  THING_ANIM_JOIN_BR,     /* alias for IS_JOIN_BR,   */
  THING_ANIM_JOIN_BR2,    /* alias for IS_JOIN_BR2,  */
  THING_ANIM_JOIN_HORIZ,  /* alias for IS_JOIN_HORIZ */
  THING_ANIM_JOIN_HORIZ2, /* alias for IS_JOIN_HORIZ */
  THING_ANIM_JOIN_LEFT,   /* alias for IS_JOIN_LEFT, */
  THING_ANIM_JOIN_NODE,   /* alias for IS_JOIN_NODE, */
  THING_ANIM_JOIN_RIGHT,  /* alias for IS_JOIN_RIGHT */
  THING_ANIM_JOIN_T_1,    /* alias for IS_JOIN_T_1,  */
  THING_ANIM_JOIN_T_2,    /* alias for IS_JOIN_T_2,  */
  THING_ANIM_JOIN_T_3,    /* alias for IS_JOIN_T_3,  */
  THING_ANIM_JOIN_T,      /* alias for IS_JOIN_T,    */
  THING_ANIM_JOIN_T180_1, /* alias for IS_JOIN_T180_ */
  THING_ANIM_JOIN_T180_2, /* alias for IS_JOIN_T180_ */
  THING_ANIM_JOIN_T180_3, /* alias for IS_JOIN_T180_ */
  THING_ANIM_JOIN_T180,   /* alias for IS_JOIN_T180, */
  THING_ANIM_JOIN_T270_1, /* alias for IS_JOIN_T270_ */
  THING_ANIM_JOIN_T270_2, /* alias for IS_JOIN_T270_ */
  THING_ANIM_JOIN_T270_3, /* alias for IS_JOIN_T270_ */
  THING_ANIM_JOIN_T270,   /* alias for IS_JOIN_T270, */
  THING_ANIM_JOIN_T90_1,  /* alias for IS_JOIN_T90_1 */
  THING_ANIM_JOIN_T90_2,  /* alias for IS_JOIN_T90_2 */
  THING_ANIM_JOIN_T90_3,  /* alias for IS_JOIN_T90_3 */
  THING_ANIM_JOIN_T90,    /* alias for IS_JOIN_T90,  */
  THING_ANIM_JOIN_TL,     /* alias for IS_JOIN_TL,   */
  THING_ANIM_JOIN_TL2,    /* alias for IS_JOIN_TL2,  */
  THING_ANIM_JOIN_TOP,    /* alias for IS_JOIN_TOP,  */
  THING_ANIM_JOIN_TR,     /* alias for IS_JOIN_TR,   */
  THING_ANIM_JOIN_TR2,    /* alias for IS_JOIN_TR2,  */
  THING_ANIM_JOIN_VERT,   /* alias for IS_JOIN_VERT, */
  THING_ANIM_JOIN_VERT2,  /* alias for IS_JOIN_VERT2 */
  THING_ANIM_JOIN_X,      /* alias for IS_JOIN_X,    */
  THING_ANIM_JOIN_X1_180, /* alias for IS_JOIN_X1_18 */
  THING_ANIM_JOIN_X1_270, /* alias for IS_JOIN_X1_27 */
  THING_ANIM_JOIN_X1_90,  /* alias for IS_JOIN_X1_90 */
  THING_ANIM_JOIN_X1,     /* alias for IS_JOIN_X1,   */
  THING_ANIM_JOIN_X2_180, /* alias for IS_JOIN_X2_18 */
  THING_ANIM_JOIN_X2_270, /* alias for IS_JOIN_X2_27 */
  THING_ANIM_JOIN_X2_90,  /* alias for IS_JOIN_X2_90 */
  THING_ANIM_JOIN_X2,     /* alias for IS_JOIN_X2,   */
  THING_ANIM_JOIN_X3_180, /* alias for IS_JOIN_X3_18 */
  THING_ANIM_JOIN_X3,     /* alias for IS_JOIN_X3,   */
  THING_ANIM_JOIN_X4_180, /* alias for IS_JOIN_X4_18 */
  THING_ANIM_JOIN_X4_270, /* alias for IS_JOIN_X4_27 */
  THING_ANIM_JOIN_X4_90,  /* alias for IS_JOIN_X4_90 */
  THING_ANIM_JOIN_X4,     /* alias for IS_JOIN_X4,   */
  THING_ANIM_IDLE,
  THING_ANIM_OPEN,
  THING_ANIM_DEAD,
  THING_ANIM_MAX
};

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

int   tp_tiles_size(Tpp tp, int anim_class);
Tilep tp_first_tile(class Tp *, int anim_class);
Tilep tp_tiles_get(Tpp tp, int anim_class, int index);
void  tp_tiles_push_back(Tpp tp, int amim_class, Tilep val);

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
void tp_fixup(void);
void tp_get_id(const char *, int *id);
void tp_random_dungeon_init(void);

bool tp_flag(Tpp tp, ThingFlag);
void tp_flag_set(Tpp tp, ThingFlag, bool val = true);

void    tp_z_depth_set(Tpp tp, uint8_t val);
uint8_t tp_z_depth_get(Tpp tp);

void    tp_z_prio_set(Tpp tp, uint8_t val);
uint8_t tp_z_prio_get(Tpp tp);

void tp_speed_set(Tpp tp, int val);
int  tp_speed_get(Tpp tp);

void tp_weight_set(Tpp tp, int val);
int  tp_weight_get(Tpp tp);

#endif // _MY_THING_TEMPLATE_H_
