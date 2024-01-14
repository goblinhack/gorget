//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_level_data.hpp"
#include "my_main.hpp"
#include "my_thing_template.hpp"
#include "my_thing_templates.hpp"

bool tp_load_block(void)
{
  TRACE_NO_INDENT();

  auto tp = tp_load("block");
  if (! tp) {
    ERR("failed to load template block");
    return false;
  }

  tp->z_depth_set(MAP_DEPTH_OBJ1);
  tp->is_block = true;

  for (auto frame = 0; frame < 5; frame++) {
    auto tile = tile_find_mand("block." + std::to_string(frame));
    tp->tiles.push_back(tile);
  }

  return true;
}
