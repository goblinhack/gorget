//
// Copyright goblinhack@gmail.com
//

#include "my_dmap.hpp"
#include "my_sprintf.hpp"
#include "my_thing.hpp"

#include <array>

void dmap_print(const Dmap *D, spoint at, spoint tl, spoint br)
{
  int x;
  int y;

  int minx, miny, maxx, maxy;
  if (tl.x < br.x) {
    minx = tl.x;
    maxx = br.x;
  } else {
    minx = br.x;
    maxx = tl.x;
  }
  if (tl.y < br.y) {
    miny = tl.y;
    maxy = br.y;
  } else {
    miny = br.y;
    maxy = tl.y;
  }

  if (minx < 0) {
    minx = 0;
  }
  if (miny < 0) {
    miny = 0;
  }
  if (maxx >= MAP_WIDTH) {
    maxx = MAP_WIDTH - 1;
  }
  if (maxy >= MAP_HEIGHT) {
    maxy = MAP_HEIGHT - 1;
  }

  bool all_walls;

  //
  // Try to minimize the DMAP area if it is mostly walls at the edges, for speed.
  //
  all_walls = true;
  for (x = minx; (x <= maxx) && all_walls; x++) {
    for (y = miny; (y <= maxy) && all_walls; y++) {
      all_walls = (D->val[ x ][ y ] == DMAP_IS_WALL);
    }
    if (all_walls) {
      minx = x;
    }
  }

  all_walls = true;
  for (x = maxx; (x > minx) && all_walls; x--) {
    for (y = miny; (y <= maxy) && all_walls; y++) {
      all_walls = (D->val[ x ][ y ] == DMAP_IS_WALL);
    }
    if (all_walls) {
      maxx = x;
    }
  }

  all_walls = true;
  for (y = miny; (y <= maxy) && all_walls; y++) {
    for (x = minx; (x <= maxx) && all_walls; x++) {
      all_walls = (D->val[ x ][ y ] == DMAP_IS_WALL);
    }
    if (all_walls) {
      miny = y;
    }
  }

  all_walls = true;
  for (y = maxy; (y > miny) && all_walls; y--) {
    for (x = minx; (x <= maxx) && all_walls; x++) {
      all_walls = (D->val[ x ][ y ] == DMAP_IS_WALL);
    }
    if (all_walls) {
      maxy = y;
    }
  }

  LOG("DMAP: tl %d,%d br %d %d at %d,%d", minx, miny, maxx, maxy, at.x, at.y);

  for (y = miny; y <= maxy; y++) {
    std::string debug;
    for (x = minx; x <= maxx; x++) {
      uint8_t e = D->val[ x ][ y ];
      if (spoint(x, y) == at) {
        debug += ("  @");
        continue;
      }
      if (e == DMAP_IS_WALL) {
        debug += (" ##");
        continue;
      }
      if (e == DMAP_IS_PASSABLE) {
        debug += ("  p");
        continue;
      }

      if (e > 0) {
        debug += string_sprintf("%3X", e);
      } else {
        debug += "  *";
      }
    }
    LOG("DMAP: %s", debug.c_str());
  }
}

void dmap_print(const Dmap *D)
{
  int x;
  int y;

  LOG("DMAP:");

  for (y = 0; y < MAP_HEIGHT; y++) {
    std::string debug;
    for (x = 0; x < MAP_WIDTH; x++) {
      uint8_t e = D->val[ x ][ y ];
      if (e == DMAP_IS_WALL) {
        debug += ("##");
        continue;
      }
      if (e == DMAP_IS_PASSABLE) {
        debug += (" .");
        continue;
      }

      if (e > 0) {
        debug += string_sprintf("%2X", e);
      } else {
        debug += " *";
      }
    }
    LOG("DMAP: %s", debug.c_str());
  }
}

//
// Pre:
//
// 9 9 9 9 9
// 9 9 9 9 9
// 9 9 9 9 9
// 9 9 0 9 9
// 9 9 9 9 9
// 9 9 9 9 9
// 9 9 9 9 9
//
// Post:
//
// 3 3 3 3 3
// 2 2 2 2 2
// 2 1 1 1 2
// 3 1 0 1 2
// 2 1 1 1 2
// 2 2 2 2 2
// 3 3 3 3 3
//
void dmap_process(Dmap *D, spoint tl, spoint br)
{
  uint8_t  x;
  uint8_t  y;
  uint8_t  a;
  uint8_t  b;
  uint8_t  c;
  uint8_t  d;
  uint8_t *e;
  uint8_t  f;
  uint8_t  g;
  uint8_t  h;
  uint8_t  i;
  uint8_t  lowest;
  uint8_t  changed;
  uint8_t  minx, miny, maxx, maxy;
  auto     orig = *D;

  if (tl.x < br.x) {
    minx = tl.x;
    maxx = br.x;
  } else {
    minx = br.x;
    maxx = tl.x;
  }
  if (tl.y < br.y) {
    miny = tl.y;
    maxy = br.y;
  } else {
    miny = br.y;
    maxy = tl.y;
  }

  //
  // Need a wall around the dmap or the search will sort of trickle off the map
  //
  for (y = miny; y <= maxy; y++) {
    D->val[ minx ][ y ] = DMAP_IS_WALL;
    D->val[ maxx ][ y ] = DMAP_IS_WALL;
  }
  for (x = minx; x <= maxx; x++) {
    D->val[ x ][ miny ] = DMAP_IS_WALL;
    D->val[ x ][ maxy ] = DMAP_IS_WALL;
  }

  //
  // Walk inside the above boundary.
  //
  minx++;
  miny++;
  maxx--;
  maxy--;

  do {
    changed = false;

    for (y = miny; y <= maxy; y++) {
      for (x = minx; x <= maxx; x++) {
        if (orig.val[ x ][ y ] == DMAP_IS_WALL) {
          continue;
        }

        e = &D->val[ x ][ y ];

        a = D->val[ x - 1 ][ y - 1 ];
        b = D->val[ x ][ y - 1 ];
        c = D->val[ x + 1 ][ y - 1 ];
        d = D->val[ x - 1 ][ y ];
        f = D->val[ x + 1 ][ y ];
        g = D->val[ x - 1 ][ y + 1 ];
        h = D->val[ x ][ y + 1 ];
        i = D->val[ x + 1 ][ y + 1 ];

        //
        // a b c
        // d e f
        // g h i
        //
        // No corner cutting
        //
        if ((b == DMAP_IS_WALL) && (d == DMAP_IS_WALL)) {
          a = DMAP_IS_WALL;
        }
        if ((b == DMAP_IS_WALL) && (f == DMAP_IS_WALL)) {
          c = DMAP_IS_WALL;
        }
        if ((d == DMAP_IS_WALL) && (h == DMAP_IS_WALL)) {
          g = DMAP_IS_WALL;
        }
        if ((f == DMAP_IS_WALL) && (h == DMAP_IS_WALL)) {
          i = DMAP_IS_WALL;
        }

        if (a < b) {
          lowest = a;
        } else {
          lowest = b;
        }

        if (c < lowest) {
          lowest = c;
        }
        if (d < lowest) {
          lowest = d;
        }
        if (f < lowest) {
          lowest = f;
        }
        if (g < lowest) {
          lowest = g;
        }
        if (h < lowest) {
          lowest = h;
        }
        if (i < lowest) {
          lowest = i;
        }

        if (*e - lowest >= 2) {
          *e      = lowest + 1;
          changed = true;
        }
      }
    }
  } while (changed);
}

//
// Pre:
//
// 0 0 0 0 0
// 0 0 0 0 0
// 0 0 0 0 0
// 0 0 3 0 0
// 0 0 0 0 0
// 0 0 0 0 0
// 0 0 0 0 0
//
// Post:
//
// 0 0 0 0 0
// 0 1 1 1 0
// 1 2 2 2 1
// 1 2 3 2 1
// 1 2 2 2 1
// 0 1 1 1 0
// 0 0 0 0 0
//
void dmap_process_reverse(Dmap *D, spoint tl, spoint br)
{
  uint8_t  x;
  uint8_t  y;
  uint8_t  a;
  uint8_t  b;
  uint8_t  c;
  uint8_t  d;
  uint8_t *e;
  uint8_t  f;
  uint8_t  g;
  uint8_t  h;
  uint8_t  i;
  uint8_t  highest;
  uint8_t  changed;
  uint8_t  minx, miny, maxx, maxy;
  auto     orig = *D;

  if (tl.x < br.x) {
    minx = tl.x;
    maxx = br.x;
  } else {
    minx = br.x;
    maxx = tl.x;
  }
  if (tl.y < br.y) {
    miny = tl.y;
    maxy = br.y;
  } else {
    miny = br.y;
    maxy = tl.y;
  }

  //
  // Need a wall around the dmap or the search will sort of trickle off the map
  //
  for (y = miny; y <= maxy; y++) {
    D->val[ minx ][ y ] = DMAP_IS_WALL;
    D->val[ maxx ][ y ] = DMAP_IS_WALL;
  }
  for (x = minx; x <= maxx; x++) {
    D->val[ x ][ miny ] = DMAP_IS_WALL;
    D->val[ x ][ maxy ] = DMAP_IS_WALL;
  }

  //
  // Walk inside the above boundary.
  //
  minx++;
  miny++;
  maxx--;
  maxy--;

  do {
    changed = false;

    for (y = miny; y <= maxy; y++) {
      for (x = minx; x <= maxx; x++) {
        if (orig.val[ x ][ y ] == DMAP_IS_WALL) {
          continue;
        }

        e = &D->val[ x ][ y ];

        a = D->val[ x - 1 ][ y - 1 ];
        b = D->val[ x ][ y - 1 ];
        c = D->val[ x + 1 ][ y - 1 ];
        d = D->val[ x - 1 ][ y ];
        f = D->val[ x + 1 ][ y ];
        g = D->val[ x - 1 ][ y + 1 ];
        h = D->val[ x ][ y + 1 ];
        i = D->val[ x + 1 ][ y + 1 ];

        //
        // a b c
        // d e f
        // g h i
        //
        // No corner cutting
        //
        if ((b == DMAP_IS_WALL) && (d == DMAP_IS_WALL)) {
          a = DMAP_IS_WALL;
        }
        if ((b == DMAP_IS_WALL) && (f == DMAP_IS_WALL)) {
          c = DMAP_IS_WALL;
        }
        if ((d == DMAP_IS_WALL) && (h == DMAP_IS_WALL)) {
          g = DMAP_IS_WALL;
        }
        if ((f == DMAP_IS_WALL) && (h == DMAP_IS_WALL)) {
          i = DMAP_IS_WALL;
        }

        if (a >= DMAP_IS_PASSABLE) {
          a = 0;
        }
        if (b >= DMAP_IS_PASSABLE) {
          b = 0;
        }
        if (c >= DMAP_IS_PASSABLE) {
          c = 0;
        }
        if (d >= DMAP_IS_PASSABLE) {
          d = 0;
        }
        if (f >= DMAP_IS_PASSABLE) {
          f = 0;
        }
        if (g >= DMAP_IS_PASSABLE) {
          g = 0;
        }
        if (h >= DMAP_IS_PASSABLE) {
          h = 0;
        }
        if (i >= DMAP_IS_PASSABLE) {
          i = 0;
        }

        if (a > b) {
          highest = a;
        } else {
          highest = b;
        }

        if (c > highest) {
          highest = c;
        }
        if (d > highest) {
          highest = d;
        }
        if (f > highest) {
          highest = f;
        }
        if (g > highest) {
          highest = g;
        }
        if (h > highest) {
          highest = h;
        }
        if (i > highest) {
          highest = i;
        }

        if (highest - *e >= 2) {
          *e      = highest - 1;
          changed = true;
        }
      }
    }
  } while (changed);
}

static std::vector< spoint > dmap_solve_(const Dmap *D, const spoint start, const std::vector< spoint > &all_deltas,
                                         bool allow_diagonals)
{
  std::array< std::array< bool, MAP_HEIGHT >, MAP_WIDTH > walked = {};
  std::vector< spoint >                                   out    = {};
  auto                                                    at     = start;

  for (; /*ever*/;) {
    auto x = at.x;
    auto y = at.y;

    if (unlikely((x >= MAP_WIDTH - 1) || (y >= MAP_HEIGHT - 1) || (x < 1) || (y < 1))) {
      return out;
    }

    uint8_t lowest = D->val[ x ][ y ];
    bool    got    = false;
    spoint  best   = {};

    if (D->val[ x ][ y ] == DMAP_IS_WALL) {
      return out;
    }

    for (const auto &d : all_deltas) {
      auto t  = at + d;
      auto tx = t.x;
      auto ty = t.y;

      if (walked[ tx ][ ty ]) {
        continue;
      }

      if (D->val[ tx ][ ty ] == DMAP_IS_WALL) {
        continue;
      }

      if (D->val[ tx ][ ty ] == DMAP_IS_PASSABLE) {
        continue;
      }

      //
      // Don't allow diagonal shortcuts if an obstacle would be crossed in an adjacent tile
      // Yes, this should be a not check to allow the player to move diagonally.
      //
      if (! allow_diagonals) {
        if (d.x < 0) {
          if (d.y < 0) {
            if ((D->val[ at.x - 1 ][ at.y ] == DMAP_IS_WALL) || (D->val[ at.x ][ at.y - 1 ] == DMAP_IS_WALL)) {
              continue;
            }
          } else if (d.y > 0) {
            if ((D->val[ at.x - 1 ][ at.y ] == DMAP_IS_WALL) || (D->val[ at.x ][ at.y + 1 ] == DMAP_IS_WALL)) {
              continue;
            }
          }
        } else if (d.x > 0) {
          if (d.y < 0) {
            if ((D->val[ at.x + 1 ][ at.y ] == DMAP_IS_WALL) || (D->val[ at.x ][ at.y - 1 ] == DMAP_IS_WALL)) {
              continue;
            }
          } else if (d.y > 0) {
            if ((D->val[ at.x + 1 ][ at.y ] == DMAP_IS_WALL) || (D->val[ at.x ][ at.y + 1 ] == DMAP_IS_WALL)) {
              continue;
            }
          }
        }
      }

      int c = D->val[ tx ][ ty ];
      if (c <= lowest) {
        got    = true;
        best   = t;
        lowest = c;
      }
    }

    if (! got) {
      return out;
    }

    out.push_back(best);
    at                         = best;
    walked[ best.x ][ best.y ] = true;
  }
  return out;
}

std::vector< spoint > dmap_solve_allow_diagonal(const Dmap *D, const spoint start)
{
  static const std::vector< spoint > all_deltas = {
      spoint(-1, -1), spoint(1, -1), spoint(-1, 1), spoint(1, 1),
      spoint(0, -1),  spoint(-1, 0), spoint(1, 0),  spoint(0, 1),
  };
  return (dmap_solve_(D, start, all_deltas, true));
}

std::vector< spoint > dmap_solve_manhattan(const Dmap *D, const spoint start)
{
  static const std::vector< spoint > all_deltas = {
      spoint(0, -1),
      spoint(-1, 0),
      spoint(1, 0),
      spoint(0, 1),
  };
  return (dmap_solve_(D, start, all_deltas, false));
}

//
// Try to solve diagonally first. Then fallback to manhattan if we cannot.
//
std::vector< spoint > dmap_solve(Gamep g, Levelsp v, Levelp l, Thingp t, const Dmap *D, const spoint start)
{
  //
  // No path? Intentionally not allowing diagonal moves here as that allows the
  // player to take a shortcut around walls. e.g.
  //
  // ..###    ..###
  // ..#$#    ..#$#
  // .@### -> ..###
  // .....    ..@..
  //
  // if we allow the diagonal move then the hidden treasure in the middle of the
  // wall gets exposed.
  //
  auto p = dmap_solve_manhattan(D, start);

  //
  // Shorten paths, but don't cut corners
  //
  // x..##    x..##
  // xx.##    .x.##
  // .xx## -> ..x##
  // ..xxx    ..xxx
  //
  thing_path_shorten(g, v, l, t, p);
  return p;
}
