//
// Copyright goblinhack@gmail.com
//

#ifndef MY_LEVEL_LIGHT_INLINES_HPP
#define MY_LEVEL_LIGHT_INLINES_HPP

#include "my_callstack.hpp"
#include "my_globals.hpp"
#include "my_level.hpp"
#include "my_main.hpp"
#include "my_math.hpp"

//
// A player specific version of this function that has less overhead
//
static void level_light_per_pixel(const FovContext &ctx, const spoint &p)
{
  TRACE_DEBUG();

  auto *const light_tile = &ctx.v->light_map.tile[ p.x ][ p.y ];

  float const col_r = ctx.light_color.r;
  float const col_g = ctx.light_color.g;
  float const col_b = ctx.light_color.b;

  uint16_t light_pixel_at_y = (p.y * TILE_WIDTH) - (TILE_WIDTH / 2);
  for (uint8_t pixy = 0; pixy < LIGHT_PIXEL; pixy++, light_pixel_at_y++) {

    uint16_t light_pixel_at_x = (p.x * TILE_WIDTH) - (TILE_WIDTH / 2);
    for (uint8_t pixx = 0; pixx < LIGHT_PIXEL; pixx++, light_pixel_at_x++) {

      float const dist_in_pixels = DISTANCEf(light_pixel_at_x, light_pixel_at_y, // newline
                                             (float) ctx.thing_at_in_pixels.x, (float) ctx.thing_at_in_pixels.y);

      //
      // No point in calculating beyond the maximum light distance.
      //
      if (dist_in_pixels >= ctx.light_strength_in_pixels) [[unlikely]] {
        continue;
      }

      auto light_fade_index
          = static_cast< uint8_t >(static_cast< int >((dist_in_pixels / ctx.light_strength_in_pixels) * static_cast< float >(MAP_WIDTH)));

#ifdef DEBUG_BUILD
      //
      // Should not happen
      //
      if ((light_fade_index >= MAP_WIDTH)) [[unlikely]] {
        light_fade_index = MAP_WIDTH - 1;
        CROAK("unexpected overflow");
      }
#endif

      auto       *light_pixel = &light_tile->pixels.pixel[ pixx ][ pixy ];
      float const fade        = ctx.light_fade_map[ light_fade_index ];

      light_pixel->r += fade * col_r;
      light_pixel->g += fade * col_g;
      light_pixel->b += fade * col_b;
    }
  }
}

#endif // MY_LEVEL_LIGHT_INLINES_HPP
