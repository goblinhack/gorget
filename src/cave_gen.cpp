//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_cave.hpp"
#include "my_charmap.hpp"
#include "my_game.hpp"
#include "my_main.hpp"
#include "my_point.hpp"
#include "my_ptrcheck.hpp"
#include "my_random.hpp"

static const int MAP_LEVEL_BLOB_CENTERING = MAP_WIDTH / 4;

void cave_dump(Gamep g, Cave *c)
{
  uint8_t x, y;

  printf("+");
  for (x = 0; x < MAP_WIDTH; x++) {
    printf("-");
  }
  printf("+");
  printf("\n");

  for (y = 0; y < MAP_HEIGHT; y++) {
    printf("|");
    for (x = 0; x < MAP_WIDTH; x++) {
      if (c->curr[ x + MAP_LEVEL_CELLULAR_BORDER ][ y + MAP_LEVEL_CELLULAR_BORDER ]) {
        printf("x");
      } else {
        printf(" ");
      }
    }
    printf("|");
    printf("\n");
  }

  printf("+");
  for (x = 0; x < MAP_WIDTH; x++) {
    printf("-");
  }
  printf("+");
  printf("\n");
}

//
// Iterate a single generations for cellular automata
//
static void cave_generation(Gamep g, Cave *c, uint32_t fill_prob, int r1, int r2, int map_generations)
{
  uint8_t x, y;

  //
  // Reset the cave map on the first generation
  //
  if (! map_generations) {
    memset(c->curr, 0, sizeof(c->curr));

    for (x = 0; x < MAP_WIDTH; x++) {
      for (y = 0; y < MAP_HEIGHT; y++) {
        if (pcg_random_range(0, 10000) < fill_prob) {
          c->curr[ x + MAP_LEVEL_CELLULAR_BORDER ][ y + MAP_LEVEL_CELLULAR_BORDER ] = 1;
        }
      }
    }
  }

  if (0) {
    printf("before:\n");
    cave_dump(g, c);
  }

  for (x = 0; x < MAP_WIDTH; x++) {
    for (y = 0; y < MAP_HEIGHT; y++) {

      uint8_t adjcount = 0;

#define ADJ(i, j) adjcount += c->curr[ x + i + MAP_LEVEL_CELLULAR_BORDER ][ y + j + MAP_LEVEL_CELLULAR_BORDER ];

      ADJ(-1, -1);
      ADJ(-1, 0);
      ADJ(-1, 1);

      ADJ(0, -1);
      ADJ(0, 0);
      ADJ(0, 1);

      ADJ(1, -1);
      ADJ(1, 0);
      ADJ(1, 1);

      if (adjcount >= r1) {
        continue;
      }

      ADJ(-2, -1);
      ADJ(-2, 0);
      ADJ(-2, 1);

      ADJ(-1, -2);
      ADJ(-1, 2);

      ADJ(0, -2);
      ADJ(0, 2);

      ADJ(1, -2);
      ADJ(1, 2);

      ADJ(2, -1);
      ADJ(2, 0);
      ADJ(2, 1);

      //
      // Adjust for the grow threshold for rock or flow.
      //
      if (adjcount <= r2) {
        //
        // prev set to 0 already.
        //
      } else {
        c->prev[ x + MAP_LEVEL_CELLULAR_BORDER ][ y + MAP_LEVEL_CELLULAR_BORDER ] = 1;
      }
    }
  }

  if (0) {
    printf("after:\n");
    cave_dump(g, c);
  }
}

//
// Iterate the generations for cellular automata
//
void cave_create(Gamep g, Cave *c, uint32_t fill_prob, int r1, int r2, int map_generations)
{
  for (auto gen = 0; gen < map_generations; gen++) {
    cave_generation(g, c, fill_prob, r1, r2, gen);
    memcpy(c->curr, c->prev, sizeof(c->prev));
    memset(c->prev, 0, sizeof(c->prev));
  }
}

//
// Recursive flood fill
//
int cave_generation_fill_blob_cand(Gamep g, Cave *c, int x, int y, uint16_t size, uint16_t id)
{
  //
  // Already walked?
  //
  if (c->blob.id[ x ][ y ]) {
    return size;
  }
  c->blob.id[ x ][ y ] = id;

  //
  // If nothing here, stop the recurse
  //
  auto i = c->curr[ x + MAP_LEVEL_CELLULAR_BORDER ][ y + MAP_LEVEL_CELLULAR_BORDER ];
  if (! i) {
    return size;
  }

  //
  // Increase the blob size
  //
  size += i;
  if (x > 0) {
    size = cave_generation_fill_blob_cand(g, c, x - 1, y, size, id);
  }
  if (x < MAP_WIDTH - 1) {
    size = cave_generation_fill_blob_cand(g, c, x + 1, y, size, id);
  }
  if (y > 0) {
    size = cave_generation_fill_blob_cand(g, c, x, y - 1, size, id);
  }
  if (y < MAP_HEIGHT - 1) {
    size = cave_generation_fill_blob_cand(g, c, x, y + 1, size, id);
  }

  return size;
}

//
// Post generation of the cave, keep all but the largest blob
//
void cave_generation_keep_largest_blob(Gamep g, Cave *c)
{
  uint16_t x, y;
  uint16_t id = 1;

  //
  // Reset the set of walked tiles
  //
  memset(c->blob.id, 0, sizeof(c->blob.id));

  //
  // Keep track of the largest blob
  //
  c->blob.largest_size = 0;

  //
  // Scan a central chunk of the level so we ignore blobs on the edges
  //
  for (x = MAP_LEVEL_BLOB_CENTERING; x < MAP_WIDTH - MAP_LEVEL_BLOB_CENTERING; x++) {
    for (y = MAP_LEVEL_BLOB_CENTERING; y < MAP_HEIGHT - MAP_LEVEL_BLOB_CENTERING; y++) {
      if (c->curr[ x + MAP_LEVEL_CELLULAR_BORDER ][ y + MAP_LEVEL_CELLULAR_BORDER ] && ! c->blob.id[ x ][ y ]) {
        //
        // Flood fill and get the size of this blob
        //
        auto size = cave_generation_fill_blob_cand(g, c, x, y, 0, id++);
        if (size > c->blob.largest_size) {
          c->blob.largest_size = size;
          c->blob.largest_at_x = x;
          c->blob.largest_at_y = y;
        }
      }
    }
  }

  //
  // If we found a large blob, then erase all other tiles
  //
  if (! c->blob.largest_size) {
    return;
  }

  x                = c->blob.largest_at_x;
  y                = c->blob.largest_at_y;
  uint16_t best_id = c->blob.id[ x ][ y ];

  for (x = 0; x < MAP_WIDTH; x++) {
    for (y = 0; y < MAP_HEIGHT; y++) {
      //
      // Remove all other blobs. Keep the largest.
      //
      if (c->blob.id[ x ][ y ] != best_id) {
        c->curr[ x + MAP_LEVEL_CELLULAR_BORDER ][ y + MAP_LEVEL_CELLULAR_BORDER ] = 0;
      }
    }
  }
}

//
// Post generation of the cave, keep all but the largest blob
//
void cave_generation_center_blob(Gamep g, Cave *c)
{
  int x, y;

  spoint tl(999, 999);
  spoint br(-1, -1);

  //
  // Get the top left and bottom right bounds
  //
  for (y = 0; y < MAP_HEIGHT; y++) {
    for (x = 0; x < MAP_WIDTH; x++) {
      if (c->curr[ x + MAP_LEVEL_CELLULAR_BORDER ][ y + MAP_LEVEL_CELLULAR_BORDER ]) {
        if (x < tl.x) {
          tl.x = x;
        }
        if (y < tl.y) {
          tl.y = y;
        }
        if (x > br.x) {
          br.x = x;
        }
        if (y > br.y) {
          br.y = y;
        }
      }
    }
  }

  if (tl.x == 999) {
    return;
  }
  if (tl.y == 999) {
    return;
  }
  if (br.x == -1) {
    return;
  }
  if (br.y == -1) {
    return;
  }

  //
  // Save curr to preve so we can reposition it
  //
  memcpy(c->prev, c->curr, sizeof(c->prev));
  memset(c->curr, 0, sizeof(c->curr));

  //
  // Get the required offset to center this blob
  //
  int tx = tl.x / 2;
  int ty = tl.y / 2;
  int bx = (MAP_WIDTH - br.x) / 2;
  int by = (MAP_HEIGHT - br.y) / 2;

  //
  // Move the blob
  //
  for (x = 0; x < MAP_WIDTH; x++) {
    for (y = 0; y < MAP_HEIGHT; y++) {
      int ox = x + MAP_LEVEL_CELLULAR_BORDER;
      int oy = y + MAP_LEVEL_CELLULAR_BORDER;
      int nx = ox - tx + bx;
      int ny = oy - ty + by;

      if (nx < 0) {
        continue;
      }
      if (ny < 0) {
        continue;
      }
      if (nx > MAP_WIDTH - 1) {
        continue;
      }
      if (ny > MAP_HEIGHT - 1) {
        continue;
      }

      if (c->prev[ ox ][ oy ]) {
        c->curr[ nx ][ ny ] = 1;
      }
    }
  }
}
