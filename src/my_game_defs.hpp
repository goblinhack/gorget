//
// Copyright goblinhack@gmail.com
//

#pragma once
#ifndef _MY_GAME_DEFS_HPP_
#define _MY_GAME_DEFS_HPP_

//
// The world map is smaller than the level map by a factor.
//
#define LEVEL_SCALE 6

//
// The world map dimentions
//
#define LEVELS_ACROSS (MAP_WIDTH / LEVEL_SCALE)
#define LEVELS_DOWN   (MAP_HEIGHT / LEVEL_SCALE)

//
// The level select level
//
#define LEVEL_SELECT_ID (MAX_LEVELS - 1)

//
// If the world map is full populated, this is all the space we need
//
#define MAX_LEVELS ((LEVELS_ACROSS * LEVELS_DOWN) + 1)

//
// In the world minimap, this is how large each level tile is
//
#define MAP_WORLD_MAP_PIXEL_SIZE_PER_LEVEL 4

//
// Number of light rays the player casts
//
#define LIGHT_MAX_RAYS_MAX (360 * 4)

//
// The level map dimensions
//
#define MAP_HEIGHT 48
#define MAP_WIDTH  48
#define MAP_SLOTS  16

#define MAP_SCROLL_SPEED          50
#define MAP_SCROLL_TELEPORT_SPEED 200

//
// How many on screen tiles we aim to have
//
#define MAP_TILES_ACROSS_DEF 16
#define MAP_TILES_DOWN_DEF   16

//
// Visible map zoom level
//
#define MAP_ZOOM_FULL_MAP 1
#define MAP_ZOOM_DEF      2
#define MAP_ZOOM_MAX      16

#define MAX_FALL_TILE_HEIGHT       4
#define MAX_FALL_TIME_MS           250
#define MAX_TESTED_LEVELS          1000
#define POPUP_DURATION_MS          2000
#define POPUP_DURATION_TILE_HEIGHT 6
#define POPUP_TEXT_SCALE_ACROSS    3
#define POPUP_TEXT_SCALE_DOWN      1.5
#define TEST_SEED                  "test-seed"
#define TICK_DURATION_MS           100

//
// 'x' is the edge of the visible map
// 'o' is the outer scroll barrier that kicks in if the player moved the mouse
//     after the character started to move (and disabled auto scrolling).
//     hitting this will re-enable auto scrolling to attempt to center the
//     player.
// 'i' inner is normally where we try and keep scrolling.
//
// xxxxxxxxxxxxxxxxxxxxxxxxxxxx
// x..........................x
// x.oooooooooooooooooooooooo.x
// x.o......................o.x
// x.o......................o.x
// x.o........iiiiii........o.x
// x.o........i....i........o.x
// x.o........i.@..i........o.x
// x.o........i....i........o.x
// x.o........iiiiii........o.x
// x.o......................o.x
// x.o......................o.x
// x.oooooooooooooooooooooooo.x
// x..........................x
// xxxxxxxxxxxxxxxxxxxxxxxxxxxx
//
#define MAP_SCROLL_EDGE 0.45
#define MAP_SCROLL_OUTER_EDGE 0.1

#endif
