//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_level_data.hpp"
#include "my_main.hpp"
#include "my_thing_template.hpp"
#include "my_thing_templates.hpp"

bool tp_load_rock_gold(void)
{
  TRACE_NO_INDENT();

  auto tp = tp_load("rock_gold");
  if (! tp) {
    ERR("failed to load template rock_gold");
    return false;
  }

  tp->z_depth_set(MAP_DEPTH_OBJ1);
  tp->is_rock_gold     = true;
  tp->is_blit_centered = true;

  for (auto frame = 0; frame < 5; frame++) {
    auto tile = tile_find_mand("rock_gold." + std::to_string(frame));
    tp->tiles.push_back(tile);
  }

  return true;
}
