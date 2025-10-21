//
// Copyright goblinhack@gmail.com
//

#pragma once
#ifndef _MY_GAME_DEFS_HPP_
#define _MY_GAME_DEFS_HPP_

#define LEVEL_SCALE                4
#define LEVEL_SELECT_ID            (MAX_LEVELS - 1)
#define LEVELS_ACROSS              (MAP_WIDTH / LEVEL_SCALE)
#define LEVELS_DOWN                (MAP_HEIGHT / LEVEL_SCALE)
#define LIGHT_MAX_RAYS_MAX         (360 * 4)
#define MAP_HEIGHT                 48
#define MAP_SCROLL_BORDER          0.5
#define MAP_SCROLL_SPEED           50
#define MAP_SLOTS                  16
#define MAP_TILES_ACROSS_DEF       16
#define MAP_TILES_DOWN_DEF         16
#define MAP_WIDTH                  48
#define MAP_ZOOM_DEF               2
#define MAX_FALL_TILE_HEIGHT       4
#define MAX_FALL_TIME_MS           250
#define MAX_LEVELS                 101
#define MAX_TESTED_LEVELS          1000
#define POPUP_DURATION_MS          2000
#define POPUP_DURATION_TILE_HEIGHT 6
#define POPUP_TEXT_SCALE_ACROSS    3
#define POPUP_TEXT_SCALE_DOWN      1.5
#define TEST_SEED                  "test-seed"
#define TICK_DURATION_MS           100

#endif
