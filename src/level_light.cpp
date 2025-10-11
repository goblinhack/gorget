//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_cave.hpp"
#include "my_charmap.hpp"
#include "my_dice.hpp"
#include "my_game.hpp"
#include "my_level.hpp"
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
          light_fade[ x ] = 1.0 - ((float) y / MAP_HEIGHT);
        }
      }
    }
  }
}

//
// All light from all light sources, combined.
//
static bool level_light_calculate_can_see_callback(Gamep g, Levelsp v, Levelp l, Thingp t, spoint pov, spoint p,
                                                   int max_radius)
{
  TRACE_NO_INDENT();

  int light_fade_index = (int) ((distance(pov, p) / (float) max_radius) * (float) MAP_WIDTH);
  if (light_fade_index >= MAP_WIDTH) {
    light_fade_index = MAP_WIDTH - 1;
  }

  auto light_tile = &v->light_map.tile[ p.x ][ p.y ];
  int  strength   = (int) (light_fade[ light_fade_index ] * 255.0);
  if (strength > 255) {
    DIE("x");
  }

  light_tile->r += strength;
  light_tile->g += strength;
  light_tile->b += strength;
  light_tile->sources = 1;

  return true;
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

  FOR_ALL_THINGS_ON_LEVEL(g, v, l, t)
  {
    int max_radius = thing_is_light_source(t);
    if (! max_radius) {
      continue;
    }

    level_fov(g, v, l, t, fov_can_see_tile, fov_has_seen_tile, t->at, max_radius,
              level_light_calculate_can_see_callback);
  }

  for (auto x = 0; x < MAP_WIDTH; x++) {
    for (auto y = 0; y < MAP_HEIGHT; y++) {
      auto light_tile = &v->light_map.tile[ x ][ y ];
      if (light_tile->sources) {
        float sources = light_tile->sources;

        float c_r = (float) light_tile->r / (float) sources;
        if (c_r > 255) {
          c_r = 255;
        }

        float c_g = (float) light_tile->g / (float) sources;
        if (c_g > 255) {
          c_g = 255;
        }

        float c_b = (float) light_tile->b / (float) sources;
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
