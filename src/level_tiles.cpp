
//
// Copyright Neil McGill, goblinhack@gmail.com
//
// REMOVED #include <array>
// REMOVED #include <string.h>

// REMOVED #include "my_array_bounds_check.hpp"
#include "my_level.hpp"
// REMOVED #include "my_level_data.hpp"
// REMOVED #include "my_main.hpp"
// REMOVED #include "my_point.hpp"
// REMOVED #include "my_random.hpp"
#include "my_template.hpp"
// REMOVED #include "my_tile.hpp"
#include "my_tp.hpp"

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

        if (tp->is_blit_tiled) {
          auto tile_variants = tp->tiles.size();
          auto tile_which    = pcg_random_range_inclusive(0, tile_variants - 1);
          auto tile_name     = tp->name + "." + std::to_string(tile_which);
          auto tile          = tile_find_mand(tile_name);
          if (tile) {
            set_tile(p, slot, tile);

            if (! is_same_type(point(x, y - 1), tp)) {
              data->obj[ x ][ y ][ slot ].dir_up = 1;
            }

            if (! is_same_type(point(x, y + 1), tp)) {
              data->obj[ x ][ y ][ slot ].dir_down = 1;
            }

            if (! is_same_type(point(x - 1, y), tp)) {
              data->obj[ x ][ y ][ slot ].dir_left = 1;
            }

            if (! is_same_type(point(x + 1, y), tp)) {
              data->obj[ x ][ y ][ slot ].dir_right = 1;
            }

            if (! is_same_type(point(x - 1, y - 1), tp) && ! is_same_type(point(x - 1, y), tp)
                && ! is_same_type(point(x, y - 1), tp)) {
              data->obj[ x ][ y ][ slot ].dir_tl = 1;
            }

            if (! is_same_type(point(x + 1, y - 1), tp) && ! is_same_type(point(x + 1, y), tp)
                && ! is_same_type(point(x, y - 1), tp)) {
              data->obj[ x ][ y ][ slot ].dir_tr = 1;
            }

            if (! is_same_type(point(x - 1, y + 1), tp) && ! is_same_type(point(x - 1, y), tp)
                && ! is_same_type(point(x, y + 1), tp)) {
              data->obj[ x ][ y ][ slot ].dir_bl = 1;
            }

            if (! is_same_type(point(x + 1, y + 1), tp) && ! is_same_type(point(x + 1, y), tp)
                && ! is_same_type(point(x, y + 1), tp)) {
              data->obj[ x ][ y ][ slot ].dir_br = 1;
            }

            data->obj[ x ][ y ][ slot ].anim_index        = pcg_random_range_inclusive(0, tp->tiles.size() - 1);
            data->obj[ x ][ y ][ slot ].anim_ms_remaining = pcg_random_range_inclusive(0, tile->delay_ms);
          }

        } else {
          auto tile = one_of(tp->tiles);
          if (tile) {
            set_tile(p, slot, tile);
            auto i                                 = pcg_random_range_inclusive(0, tp->tiles.size() - 1);
            data->obj[ x ][ y ][ slot ].anim_index = i;
          }
        }
      }
    }
  }
}
