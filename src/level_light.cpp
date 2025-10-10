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

//
// All light from all light sources, combined.
//
void level_light_calculate(Gamep g, Levelsp v, Levelp l)
{
  TRACE_NO_INDENT();

  FovMap *fov_has_seen_tile = nullptr;

  memset(&v->light_map, 0, sizeof(v->light_map));

  FOR_ALL_THINGS_ON_LEVEL(g, v, l, t)
  {
    if (! thing_is_light_source(t)) {
      continue;
    }

    FovMap fov_can_see_tile = {};
    float  max_radius       = thing_is_light_source(t);

    level_fov(g, v, l, t, &fov_can_see_tile, fov_has_seen_tile, t->at, (int) max_radius);

    for (auto y = 0; y < MAP_HEIGHT; y++) {
      for (auto x = 0; x < MAP_WIDTH; x++) {
        if (fov_can_see_tile.can_see[ x ][ y ]) {
          float d        = distance(t->at, spoint(x, y));
          float strength = ((max_radius - d) / max_radius) * 255.0;

          if (strength > 255) {
            DIE("a");
            strength = 255;
          }
          if (strength < 0) {
            DIE("b");
            strength = 0;
          }

          auto    light_tile = &v->light_map.tile[ x ][ y ];
          uint8_t c          = (int) strength;

          light_tile->r += c;
          light_tile->g += c;
          light_tile->b += c;
          light_tile->sources = 1;
        }
      }
    }
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
      }
    }
  }
}
