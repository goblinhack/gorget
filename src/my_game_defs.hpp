//
// Copyright goblinhack@gmail.com
//

#pragma once
#ifndef _MY_GAME_DEFS_HPP_
#define _MY_GAME_DEFS_HPP_

#define LEVEL_SCALE          4
#define LEVELS_ACROSS        (MAP_WIDTH / LEVEL_SCALE)
#define LEVELS_DOWN          (MAP_HEIGHT / LEVEL_SCALE)
#define MAX_LEVELS           101
#define MAX_FALL_TIME_MS     2500
#define MAX_FALL_TILE_HEIGHT 4
#define MAX_TESTED_LEVELS    1000
#define LEVEL_SELECT_ID      (MAX_LEVELS - 1)
#define MAP_WIDTH            48
#define MAP_HEIGHT           48
#define MAP_SLOTS            16
#define MAP_ZOOM_DEF         2
#define MAP_SCROLL_BORDER    0.5
#define MAP_SCROLL_SPEED     50
#define TICK_DURATION_MS     50
#define MAP_TILES_ACROSS_DEF 16
#define MAP_TILES_DOWN_DEF   16

#endif
