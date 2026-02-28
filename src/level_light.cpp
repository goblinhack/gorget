//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_globals.hpp"
#include "my_level.hpp"
#include "my_level_light_inlines.hpp"
#include "my_main.hpp"
#include "my_math.hpp"
#include "my_thing_inlines.hpp"
#include "my_tile.hpp"
#include "my_ui.hpp"

#include <cmath>

#include <array>
#include <cstring>

static float light_fade[ MAP_WIDTH ];

void level_light_precalculate(Gamep g)
{
  static const char light_fade_map[]
      = "x                                               " //
        " x                                              " //
        "  x                                             " //
        "   x                                            " //
        "    x                                           " //
        "     x                                          " //
        "      x                                         " //
        "       x                                        " //
        "        x                                       " //
        "         x                                      " //
        "          x                                     " //
        "           x                                    " //
        "            x                                   " //
        "             x                                  " //
        "              x                                 " //
        "               x                                " //
        "                x                               " //
        "                 x                              " //
        "                  x                             " //
        "                   x                            " //
        "                    x                           " //
        "                     x                          " //
        "                      x                         " //
        "                       x                        " //
        "                        x                       " //
        "                         x                      " //
        "                          x                     " //
        "                           x                    " //
        "                            x                   " //
        "                             x                  " //
        "                              x                 " //
        "                               x                " //
        "                                x               " //
        "                                 x              " //
        "                                  x             " //
        "                                   x            " //
        "                                    x           " //
        "                                     x          " //
        "                                      x         " //
        "                                       x        " //
        "                                        x       " //
        "                                         x      " //
        "                                          x     " //
        "                                           x    " //
        "                                            x   " //
        "                                             x  " //
        "                                              x " //
        "                                               x" //
      ;

  for (auto x = 0; x < MAP_WIDTH; x++) {
    for (auto y = 0; y < MAP_HEIGHT; y++) {
      auto c = light_fade_map[ (MAP_WIDTH * y) + x ];
      if (c == 'x') {
        if (light_fade[ x ] == 0) {
          light_fade[ x ] = 1.0F - ((float) y / (float) MAP_HEIGHT);
        }
      }
    }
  }
}

//
// All light from all light sources, combined.
//
void level_light_per_pixel_lighting(Gamep g, Levelsp v, Levelp l, Thingp t, spoint /*pov*/, spoint tile)
{
  const color  light_color              = tp_light_color(thing_tp(t));
  const float  light_strength_in_pixels = thing_is_light_source(t) * TILE_WIDTH;
  const spoint thing_at_in_pixels       = thing_pix_at(t);

  level_light_per_pixel(g, v, l, t, tile, light_color, light_strength_in_pixels, thing_at_in_pixels, light_fade);
}

//
// All light from all light sources, combined.
//
void level_light_calculate_all(Gamep g, Levelsp v, Levelp l)
{
  TRACE();

  auto *player = thing_player(g);

  if (player == nullptr) [[unlikely]] {
    return;
  }

  if ((g == nullptr) || (v == nullptr) || (l == nullptr)) [[unlikely]] {
    return;
  }

  //
  // If the player is not on the level being lit, then nothing to do
  //
  if (l->level_num != player->level_num) {
    return;
  }

  v->light_map = {};

  //
  // Now do the same for the player
  //
  level_raycast(g, v, l, FBO_MAP_LIGHT);

  //
  // Calculate all lit tiles for non player things
  //
  FOR_ALL_THINGS_ON_LEVEL(g, v, l, t)
  {
    int max_radius = thing_is_light_source(t);
    if (max_radius == 0) {
      continue;
    }

    if (thing_is_player(t)) {
      continue;
    }

    auto *ext   = thing_ext_struct(g, t);
    auto *light = thing_light_struct(g, t);

    //
    // + here needed for light edges for smoothly moving things
    //
    if (thing_is_projectile(t)) {
      max_radius += 2;
    }

    level_fov_can_see_callback_t callback = nullptr;
    if (thing_is_light_source(t) != 0) {
      callback = level_light_per_pixel_lighting;
    } else {
      callback = nullptr;
    }

    level_fov(g, v, l, t,                                    // newline
              (light != nullptr) ? &light->is_lit : nullptr, // newline
              (ext != nullptr) ? &ext->has_seen : nullptr,   // newline
              thing_at(t), max_radius, callback);
  }
}
