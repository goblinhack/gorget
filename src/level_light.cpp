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
          light_fade[ x ] = 1.0F - (static_cast< float >(y) / static_cast< float >(MAP_HEIGHT));
        }
      }
    }
  }
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
    if (max_radius == 0) [[likely]] {
      continue;
    }

    if (thing_is_player(t)) [[unlikely]] {
      continue;
    }

    auto *light = thing_light_struct(g, t);

    //
    // + here needed for light edges for smoothly moving things
    //
    if (thing_is_projectile(t)) [[unlikely]] {
      max_radius += 2;
    }

    FovContext ctx;

    ctx.g                        = g;
    ctx.v                        = v;
    ctx.l                        = l;
    ctx.me                       = t;
    ctx.pov                      = thing_at(t);
    ctx.light_color              = tp_light_color(thing_tp(t));
    ctx.light_strength_in_pixels = thing_is_light_source(t) * TILE_WIDTH;
    ctx.thing_at_in_pixels       = thing_pix_at(t);
    ctx.light_fade_map           = light_fade;
    ctx.can_see_callback         = level_light_per_pixel;
    ctx.max_radius               = max_radius;
    ctx.fov_can_see_tile         = &light->is_lit;
    ctx.fov_has_seen_tile        = nullptr;

    level_fov(ctx);
  }
}
