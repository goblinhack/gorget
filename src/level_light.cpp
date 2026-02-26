//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_globals.hpp"
#include "my_level.hpp"
#include "my_main.hpp"
#include "my_math.hpp"
#include "my_thing_inlines.hpp"
#include "my_tile.hpp"
#include "my_ui.hpp"

#include <cmath>

#include <array>
#include <cstring>

static float player_light_fade[ MAP_WIDTH ];
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

  static const char player_light_fade_map[]
      = "xx                                              " //
        "  xx                                            " //
        "    x                                           " //
        "     x                                          " //
        "      x                                         " //
        "       x                                        " //
        "        x                                       " //
        "        x                                       " //
        "         x                                      " //
        "         x                                      " //
        "          x                                     " //
        "          x                                     " //
        "           x                                    " //
        "           x                                    " //
        "            x                                   " //
        "            x                                   " //
        "             x                                  " //
        "             x                                  " //
        "              x                                 " //
        "              x                                 " //
        "               x                                " //
        "               x                                " //
        "               x                                " //
        "                x                               " //
        "                x                               " //
        "                x                               " //
        "                 x                              " //
        "                 x                              " //
        "                 x                              " //
        "                 x                              " //
        "                 x                              " //
        "                  x                             " //
        "                  x                             " //
        "                  x                             " //
        "                   x                            " //
        "                   x                            " //
        "                   x                            " //
        "                    x                           " //
        "                    x                           " //
        "                     x                          " //
        "                     x                          " //
        "                      x                         " //
        "                       x                        " //
        "                        x                       " //
        "                         x                      " //
        "                          xx                    " //
        "                            xxxxxxxxxxxxxxxxxxxx" //
        "                                                " //
      ;

  for (auto x = 0; x < MAP_WIDTH; x++) {
    for (auto y = 0; y < MAP_HEIGHT; y++) {
      {
        auto c = player_light_fade_map[ (MAP_WIDTH * y) + x ];
        if (c == 'x') {
          if (player_light_fade[ x ] == 0) {
            player_light_fade[ x ] = 1.0F - ((float) y / (float) MAP_HEIGHT);
          }
        }
      }

      {
        auto c = light_fade_map[ (MAP_WIDTH * y) + x ];
        if (c == 'x') {
          if (light_fade[ x ] == 0) {
            light_fade[ x ] = 1.0F - ((float) y / (float) MAP_HEIGHT);
          }
        }
      }
    }
  }
}

//
// All light from all light sources, combined.
//
void level_light_per_pixel_lighting(Gamep g, Levelsp v, Levelp l, Thingp t, spoint /*pov*/, spoint p)
{
  const color  light_color              = tp_light_color(thing_tp(t));
  const float  light_strength_in_pixels = thing_is_light_source(t) * TILE_WIDTH;
  auto *const  light_tile               = &v->light_map.tile[ p.x ][ p.y ];
  const float *light_fade_map           = nullptr;
  const spoint thing_at_in_pixels       = thing_pix_at(t);

  if (light_strength_in_pixels == 0.0F) {
    THING_ERR(t, "thing has no light source");
  }

  float const col_r = light_color.r;
  float const col_g = light_color.g;
  float const col_b = light_color.b;

  if (thing_is_player(t)) {
    //
    // More dramatic lighting. Allows other lights to appear stronger
    //
    light_fade_map = player_light_fade;
  } else {
    light_fade_map = light_fade;
  }

  uint16_t light_pixel_at_y = (p.y * TILE_WIDTH) - (TILE_WIDTH / 2);
  for (uint8_t pixy = 0; pixy < LIGHT_PIXEL; pixy++, light_pixel_at_y++) {

    uint16_t light_pixel_at_x = (p.x * TILE_WIDTH) - (TILE_WIDTH / 2);
    for (uint8_t pixx = 0; pixx < LIGHT_PIXEL; pixx++, light_pixel_at_x++) {

      float const dist_in_pixels
          = DISTANCEf(light_pixel_at_x, light_pixel_at_y, (float) thing_at_in_pixels.x, (float) thing_at_in_pixels.y);

      auto light_fade_index = (uint8_t) (int) ((dist_in_pixels / light_strength_in_pixels) * (float) MAP_WIDTH);
      if ((light_fade_index >= MAP_WIDTH)) [[unlikely]] {
        light_fade_index = MAP_WIDTH - 1;
      }

      auto       *light_pixel = &light_tile->pixels.pixel[ pixx ][ pixy ];
      float const fade        = light_fade_map[ light_fade_index ];

      light_pixel->r += fade * col_r;
      light_pixel->g += fade * col_g;
      light_pixel->b += fade * col_b;
    }
  }
}

//
// Something blocking the fov?
//
auto level_light_blocker_at(Gamep g, Levelsp v, Levelp l, const spoint &pov) -> Thingp
{
  FOR_ALL_THINGS_AT_UNSAFE(g, v, l, it, pov)
  {
    //
    // Dead foliage should not block
    //
    if (thing_is_dead(it)) {
      continue;
    }

    //
    // Open doors should not block
    //
    if (thing_is_open(it)) {
      continue;
    }

    if (thing_is_obs_to_vision(it)) {
      if (compiler_unused) {
        THING_LOG(it, "block");
      }
      return it;
    }
  }

  return nullptr;

#if 0
    if (me->is_monst()) {
      if (! light_blocker) {
        light_blocker = is_obs_to_vision_for_monst(p);
      }

      if (! light_blocker) {
        if (! me->is_player()) {
          if (! me->is_able_to_see_in_magical_darkness()) {
            light_blocker = is_darkness(p);
          }
        }
      }
    }
#endif
}

//
// Something blocking the fov?
//
auto level_light_blocker_at_cached(Gamep g, Levelsp v, Levelp l, const spoint &p) -> bool
{
  return l->is_light_blocker_cache[ p.x ][ p.y ] != 0;
}

//
// Update all light blockers. This is done per tick to avoid having to redo this
// check for every monster during vision checks.
//
void level_light_blocker_update(Gamep g, Levelsp v, Levelp l)
{
  TRACE();

  for (auto x = 0; x < MAP_WIDTH; x++) {
    for (auto y = 0; y < MAP_HEIGHT; y++) {
      if (level_light_blocker_at(g, v, l, spoint(x, y)) != nullptr) {
        l->is_light_blocker_cache[ x ][ y ] = 1U;
      } else {
        l->is_light_blocker_cache[ x ][ y ] = 0U;
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
  level_light_raycast(g, v, l, FBO_MAP_LIGHT);

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
