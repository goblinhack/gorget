//
// Copyright Neil McGill, goblinhack@gmail.com
//

#pragma once
#ifndef _MY_GAME_DEFS_HPP_
#define _MY_GAME_DEFS_HPP_

/*
 * Phase 1: create a framework for the level solution e.g.
 *
 *           v    v  * v
 *     1----1----1---S1
 *      >  <|>  <|>  <|
 *          |    |    |
 *          |    |    |
 *          |   *|v  *|
 *    s.    1----1----1
 *         ^?>  <|>  <
 *          ?    |
 *          ?    |
 *      v   ?   *|   * v
 *     2???s1???K1---D2
 *     |        ^ >  <|
 *     |              |
 *     |              |
 *     |   *    *    *|
 *     2---E2----2----2
 *    ^ >  <    <    <
 */
#define LEVEL_PH1_WIDTH      4 // Levels are split into grids. Each grid can have a room.
#define LEVEL_PH1_HEIGHT     4 // Levels are split into grids. Each grid can have a room.
#define LEVEL_PH1_LOCK_DEPTH 2 // Max difficulty level

/*
 * Phase 2: create a set of rooms that satisfy the solution e.g.:
 *
 * 1111111111 1........1 1111111111 1111111111
 * 1111111111 1........1 1111111111 1111111111
 * 11........ 11...S..11 11......11 ........11
 * 11........ 11..111.11 11......11 ........11
 * 11........ 11..111.11 11......11 ........11
 * 11........ .......... .......... ........11
 * 11111..111 1111111111 11..111111 11..111111
 * 111111.111 1111111111 111.111111 11.1111111
 *
 * 111111s111 1111111111 111.111111 11.1111111
 * 111111..11 1111111111 111.111111 11.1111111
 * 11......11 11........ 11......11 11......11
 * 11......11 11........ 11......11 11......11
 * 11......11 11........ 11......11 11......11
 * 11......11 11........ .......... ........11
 * 111...1111 1111111111 1111..1111 11111..111
 * 1111s11111 1111111111 11111.1111 11111.1111
 *
 * 1111.11111 1111111111 11111.1111 11111.1111
 * 1111.11111 1111111111 11111.1111 1111....11
 * 11......11 11......11 11......11 11......11
 * 11......11 11......11 11......11 11......11
 * 11......11 11......11 11......11 11......11
 * 11........ .......... ........11 11......11
 * ...1111111 1111111111 1111111... 1111111111
 * .111111111 1111111111 111111111. 1111111111
 *
 * ..11111111 1111111111 111111111. 1111111111
 * ....111111 1111111111 111111111. 1111111111
 * 11......11 11........ 11........ ........11
 * 11......11 11........ 11......11 ........11
 * 11......11 11...E.... 11......11 ........11
 * 11......11 11..111... .......... ........11
 * 1111111111 1111111111 1111111111 1111111111
 * 1111111111 1111111111 1111111111 1111111111
 */
#define LEVEL_PH2_WIDTH       LEVEL_PH1_WIDTH
#define LEVEL_PH2_HEIGHT      LEVEL_PH1_HEIGHT
#define LEVEL_PH2_ROOM_WIDTH  10 // Max room dimensions
#define LEVEL_PH2_ROOM_HEIGHT 8  // Max room dimensions

/*
 * Phase 3: join the rooms together and expand any wildcards
 *
 * RRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRR
 * R111111111111......1111111111111111111111R
 * R11111111111....S...111111111111111111111R
 * R11........122.11122111......11........11R
 * R11........1........111......11........11R
 * R11........125****..111......11........11R
 * R11..........*****.....................11R
 * R1111..11111.*****.211111111111111..11111R
 * R11111.111111111111111111111111111.111111R
 * R11111.111111111111111111111111111.111111R
 * R11111.111111111111111111111111111.111111R
 * R11......11........1111........11......11R
 * R11......11........1111........11......11R
 * R11......11........1111........11......11R
 * R11................1111................11R
 * R11111.111111111111111..11111111111..1111R
 * R11111.1111111111111111.11111111111.11111R
 * R11111.1111111111111111.11111111111.11111R
 * R11111.111111111111111..11111111111.11111R
 * R11........11......111.......1111......11R
 * R11........11......1111......1111......11R
 * R11........11......1111......1111......11R
 * R11....................................11R
 * R11111111111111..111111111111111111.11111R
 * R11111111111111.1111111111111111111.11111R
 * R11111111111111.1111111111111111111s11111R
 * R11111111111111.1111111111111111111.11111R
 * R11........11......1111......111.......11R
 * R11........11......1111......111.......11R
 * R11...E....11......1111......111.......11R
 * R11..111.......................s.......11R
 * R1111111111111111111111111111111111111111R
 * R1111111111111111111111111111111111111111R
 * RRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRR
 */
#define LEVEL_PH3_MAP_BORDER      1 // Border around the level
#define LEVEL_PH3_WIDTH           ((LEVEL_PH2_WIDTH * LEVEL_PH2_ROOM_WIDTH) + (LEVEL_PH3_MAP_BORDER * 2))
#define LEVEL_PH3_HEIGHT          ((LEVEL_PH2_HEIGHT * LEVEL_PH2_ROOM_HEIGHT) + (LEVEL_PH3_MAP_BORDER * 2))
#define LEVEL_PH3_OBSTACLE_WIDTH  5 // Max obstacle dimensions
#define LEVEL_PH3_OBSTACLE_HEIGHT 3 // Max obstacle dimensions

/*
 * Phase 4: replace all chars with objects
 */
#define LEVEL_PH4_WIDTH  LEVEL_PH3_WIDTH
#define LEVEL_PH4_HEIGHT LEVEL_PH3_HEIGHT

#define MAP_WIDTH  LEVEL_PH4_WIDTH
#define MAP_HEIGHT LEVEL_PH4_HEIGHT
#define MAP_SLOTS  16

#define GAME_MOST_ZOOMED_IN   5
#define GAME_MOST_ZOOMED_OUT  1
#define GAME_DEFAULT_UI_ZOOM  1
#define GAME_DEFAULT_PIX_ZOOM GAME_MOST_ZOOMED_OUT

/*
 * Accounts for fractions of a pixel
 */
#define PIX_SCALE 8

#define THING_MAX_SPEED 15

#endif
