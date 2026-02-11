//
// Copyright goblinhack@gmail.com
//

#pragma once
#ifndef _MY_GAME_DEFS_HPP_
#define _MY_GAME_DEFS_HPP_

//
// The level map dimensions
//
#define MAP_HEIGHT 48
#define MAP_WIDTH  48
#define MAP_SLOTS  14

//
// The world map is smaller than the level map by a factor.
//
#define LEVEL_SCALE     6
#define LEVEL_ACROSS    (MAP_WIDTH / LEVEL_SCALE)
#define LEVEL_DOWN      (MAP_HEIGHT / LEVEL_SCALE)
#define LEVEL_SELECT_ID (LEVEL_MAX - 1) // The level select level
#define LEVEL_MAX       ((LEVEL_ACROSS * LEVEL_DOWN) + 1)

//
// Entropy is always > 0 for Thing IDs to distinguish them
// A thing ID is composed as: [ Entropy bits ] [ ID bits ]
//
//                       31      |       |       |      0
//                       +-------------------------------
//                       0LLLLLLIIIIIIIIIIIIIIIEEEEEEEEEE
//
// E Entropy
// I Per level ID (enough for THING_ID_PER_LEVEL_REQ)
// L Level        (enough for LEVEL_MAX - 1)
//
#define THING_LEVEL_ID_BITS           6
#define THING_PER_LEVEL_THING_ID_BITS 15
#define THING_ENTROPY_BITS            10

#define THING_ARR_INDEX_BITS (THING_LEVEL_ID_BITS + THING_PER_LEVEL_THING_ID_BITS)

#define THING_ID_MAX (1 << THING_ARR_INDEX_BITS)

#define THING_ID_PER_LEVEL_REQ (MAP_SLOTS * MAP_WIDTH * MAP_HEIGHT)
#define THING_ID_PER_LEVEL_MAX (1 << THING_PER_LEVEL_THING_ID_BITS)

#define LEVEL_ID_REQ (LEVEL_ACROSS * LEVEL_DOWN)
#define LEVEL_ID_MAX (1 << THING_LEVEL_ID_BITS)

//
// In the world minimap, this is how large each level tile is
//
#define MAP_WORLD_MAP_PIXEL_SIZE_PER_LEVEL 4

//
// Number of light rays the player casts
//
#define LIGHT_MAX_RAYS_MAX (360 * 4)

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
#define MAX_HIT_TIME_MS            250
#define MAX_TESTED_LEVELS          1000
#define POPUP_DURATION_MS          2000
#define POPUP_DURATION_TILE_HEIGHT 6
#define POPUP_TEXT_SCALE_ACROSS    3
#define POPUP_TEXT_SCALE_DOWN      1.5
#define TEST_SEED                  "test-seed"
#define TEST_ITERATIONS            1000
#define TICK_DURATION_MS           100

#define WALL_VARIANTS  12
#define FLOOR_VARIANTS 10

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
#define MAP_SCROLL_EDGE       0.45
#define MAP_SCROLL_OUTER_EDGE 0.1

//
// Collision detection radii
//
#define THING_COLLISION_CIRCLE_SMALL_RADIUS 0.025f
#define THING_COLLISION_CIRCLE_LARGE_RADIUS 0.5f

//
// Need a small fraction to account for comparisons of very similar floats where
// we end up shooting the player upon firing
//
#define THING_COLLISION_FIRING_OFFSET 0.01f

#endif
