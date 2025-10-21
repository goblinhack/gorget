//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_cave.hpp"
#include "my_charmap.hpp"
#include "my_game.hpp"
#include "my_gl.hpp"
#include "my_level.hpp"
#include "my_light.hpp"
#include "my_random.hpp"
#include "my_time.hpp"

static float light_fade[ MAP_WIDTH ];

void level_light_precalculate(Gamep g)
{
  static const char light_fade_map[]
      = "xxxx                                            " //
        "    xx                                          " //
        "      x                                         " //
        "       x                                        " //
        "        x                                       " //
        "        x                                       " //
        "         x                                      " //
        "         x                                      " //
        "          x                                     " //
        "          x                                     " //
        "          x                                     " //
        "          x                                     " //
        "          x                                     " //
        "          x                                     " //
        "           x                                    " //
        "           x                                    " //
        "           x                                    " //
        "           x                                    " //
        "           x                                    " //
        "            x                                   " //
        "            x                                   " //
        "            x                                   " //
        "            x                                   " //
        "            x                                   " //
        "             x                                  " //
        "             x                                  " //
        "             x                                  " //
        "              x                                 " //
        "              x                                 " //
        "              x                                 " //
        "               x                                " //
        "               x                                " //
        "                x                               " //
        "                 x                              " //
        "                  xx                            " //
        "                    xxx                         " //
        "                       xxxx                     " //
        "                           xxxxxx               " //
        "                                 xxxxxxx        " //
        "                                        xxxxxxxx" //
        "                                                " //
        "                                                " //
        "                                                " //
        "                                                " //
        "                                                " //
        "                                                " //
        "                                                " //
        "                                                " //
      ;

  for (auto x = 0; x < MAP_WIDTH; x++) {
    for (auto y = 0; y < MAP_HEIGHT; y++) {
      auto c = light_fade_map[ (MAP_WIDTH * y) + x ];
      if (c == 'x') {
        if (light_fade[ x ] == 0) {
          light_fade[ x ] = 1.0f - ((float) y / MAP_HEIGHT);
        }
      }
    }
  }
}

//
// All light from all light sources, combined.
//
void level_light_calculate_can_see_callback(Gamep g, Levelsp v, Levelp l, Thingp t, spoint pov, spoint p,
                                            int max_radius)
{
  auto light_fade_index = (int) ((distance(pov, p) / (float) max_radius) * (float) MAP_WIDTH);
  if (unlikely(light_fade_index >= MAP_WIDTH)) {
    light_fade_index = MAP_WIDTH - 1;
  }

  auto light_tile = &v->light_map.tile[ p.x ][ p.y ];
  auto strength   = light_fade[ light_fade_index ];

  color c = tp_light_color(thing_tp(t));

  light_tile->r += (int) (strength * c.r);
  light_tile->g += (int) (strength * c.g);
  light_tile->b += (int) (strength * c.b);
  light_tile->r = 255;
  light_tile->g = 255;
  light_tile->b = 255;

  //
  // This is the ray count
  //
  if (light_tile->lit < 255) {
    light_tile->lit++;
  }
}

//
// All light from all light sources, combined.
//
void level_light_calculate(Gamep g, Levelsp v, Levelp l)
{
  TRACE_NO_INDENT();

  FovMap *fov_has_seen_tile = nullptr;
  FovMap *fov_can_see_tile  = nullptr;

  memset(&v->light_map, 0, sizeof(v->light_map));

  //
  // Now do the same for the player
  //
  level_light_calculate_for_player(g, v, l, FBO_MAP_LIGHT);

  //
  // Calculate all lit tiles for non player things
  //
  if (0) {
    FOR_ALL_THINGS_ON_LEVEL(g, v, l, t)
    {
      int max_radius = thing_is_light_source(t);
      if (! max_radius) {
        continue;
      }

      if (thing_is_player(t)) {
        continue;
      }

      level_fov(g, v, l, t, fov_can_see_tile, fov_has_seen_tile, t->at, max_radius,
                level_light_calculate_can_see_callback);
    }
  }

  //
  // Calculate the total light color per tile
  //
  for (auto x = 0; x < MAP_WIDTH; x++) {
    for (auto y = 0; y < MAP_HEIGHT; y++) {
      auto light_tile = &v->light_map.tile[ x ][ y ];

      if (light_tile->lit) {
        auto c_r = light_tile->r;
        if (c_r > 255) {
          c_r = 255;
        }
        auto c_g = light_tile->g;
        if (c_g > 255) {
          c_g = 255;
        }
        auto c_b = light_tile->b;
        if (c_b > 255) {
          c_b = 255;
        }

        light_tile->c.r = (uint8_t) c_r;
        light_tile->c.g = (uint8_t) c_g;
        light_tile->c.b = (uint8_t) c_b;
        light_tile->c.a = 255;
      }
    }
  }
}
