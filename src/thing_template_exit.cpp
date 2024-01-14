//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_level_data.hpp"
#include "my_main.hpp"
#include "my_thing_template.hpp"
#include "my_thing_templates.hpp"

bool tp_load_exit(void)
{
  TRACE_NO_INDENT();

  auto tp = tp_load("exit");
  if (! tp) {
    ERR("failed to load template exit");
    return false;
  }

  tp->z_depth_set(MAP_DEPTH_OBJ1);
  tp->is_exit           = true;
  tp->is_blit_on_ground = true;

  for (auto frame = 0; frame < 8; frame++) {
    const auto delay = 100; /* ms */
    auto       tile  = tile_find_mand("exit." + std::to_string(frame));
    tile->delay_ms   = delay;
    tp->tiles.push_back(tile);
  }

  return true;
}
