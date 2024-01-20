
//
// Copyright Neil McGill, goblinhack@gmail.com
//
#include <array>
#include <string.h>

#include "my_array_bounds_check.hpp"
#include "my_level.hpp"
#include "my_level_data.hpp"
#include "my_main.hpp"
#include "my_point.hpp"
#include "my_random.hpp"
#include "my_template.hpp"
#include "my_thing_template.hpp"
#include "my_tile.hpp"

void Level::assign_tiles(void)
{
  TRACE_NO_INDENT();

  for (auto slot = 0; slot < MAP_SLOTS; slot++) {
    for (auto y = 0; y < MAP_HEIGHT; y++) {
      for (auto x = 0; x < MAP_WIDTH; x++) {
        point p(x, y);
        auto  tp = tp_get(p, slot);
        if (! tp) {
          continue;
        }

        if (! tp->tiles.size()) {
          continue;
        }

        if (tp->is_wall) {
          auto tile = tile_find("wall." + std::to_string(x % 6) + "." + std::to_string(y % 6));
          if (tile) {
            set_tile(p, slot, tile);
          }

          if (! is_wall(point(x, y - 1))) {
            data->obj[ x ][ y ][ slot ].dir_up = 1;
          }

          if (! is_wall(point(x, y + 1))) {
            data->obj[ x ][ y ][ slot ].dir_down = 1;
          }

          if (! is_wall(point(x - 1, y))) {
            data->obj[ x ][ y ][ slot ].dir_left = 1;
          }

          if (! is_wall(point(x + 1, y))) {
            data->obj[ x ][ y ][ slot ].dir_right = 1;
          }

          if (! is_wall(point(x - 1, y - 1)) && ! is_wall(point(x - 1, y)) && ! is_wall(point(x, y - 1))) {
            data->obj[ x ][ y ][ slot ].dir_tl = 1;
          }

          if (! is_wall(point(x + 1, y - 1)) && ! is_wall(point(x + 1, y)) && ! is_wall(point(x, y - 1))) {
            data->obj[ x ][ y ][ slot ].dir_tr = 1;
          }

          if (! is_wall(point(x - 1, y + 1)) && ! is_wall(point(x - 1, y)) && ! is_wall(point(x, y + 1))) {
            data->obj[ x ][ y ][ slot ].dir_bl = 1;
          }

          if (! is_wall(point(x + 1, y + 1)) && ! is_wall(point(x + 1, y)) && ! is_wall(point(x, y + 1))) {
            data->obj[ x ][ y ][ slot ].dir_br = 1;
          }

        } else if (tp->is_rock) {
          auto tile = tile_find("rock." + std::to_string(x % 6) + "." + std::to_string(y % 6));
          if (tile) {
            set_tile(p, slot, tile);
          }

          if (y > 0) {
            if (! is_rock(point(x, y - 1))) {
              data->obj[ x ][ y ][ slot ].dir_up = 1;
            }
          }

          if (y < MAP_HEIGHT - 1) {
            if (! is_rock(point(x, y + 1))) {
              data->obj[ x ][ y ][ slot ].dir_down = 1;
            }
          }

          if (x > 0) {
            if (! is_rock(point(x - 1, y))) {
              data->obj[ x ][ y ][ slot ].dir_left = 1;
            }
          }

          if (x < MAP_WIDTH - 1) {
            if (! is_rock(point(x + 1, y))) {
              data->obj[ x ][ y ][ slot ].dir_right = 1;
            }
          }

          if ((x == 0) && (y == 0)) {
            data->obj[ x ][ y ][ slot ].dir_br = 1;
          }

          if ((x == MAP_WIDTH - 1) && (y == 0)) {
            data->obj[ x ][ y ][ slot ].dir_bl = 1;
          }

          if ((x == 0) && (y == MAP_HEIGHT - 1)) {
            data->obj[ x ][ y ][ slot ].dir_tr = 1;
          }

          if ((x == MAP_WIDTH - 1) && (y == MAP_HEIGHT - 1)) {
            data->obj[ x ][ y ][ slot ].dir_tl = 1;
          }

        } else {
          auto tile = one_of(tp->tiles);
          if (tile) {
            set_tile(p, slot, tile);
          }
        }
      }
    }
  }
}
