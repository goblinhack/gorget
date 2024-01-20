//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_level_data.hpp"
#include "my_main.hpp"
#include "my_thing_template.hpp"
#include "my_thing_templates.hpp"

bool tp_load_rock(void)
{
  TRACE_NO_INDENT();

  auto tp = tp_load("rock");
  if (! tp) {
    ERR("failed to load template rock");
    return false;
  }

  tp->z_depth_set(MAP_DEPTH_ROCK);
  tp->is_rock = true;

  for (auto x = 0; x < 6; x++) {
    for (auto y = 0; y < 6; y++) {
      auto tile = tile_find_mand("rock." + std::to_string(x) + "." + std::to_string(y));
      tp->tiles.push_back(tile);
    }
  }

  return true;
}
