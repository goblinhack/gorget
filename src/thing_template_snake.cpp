//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_level_data.hpp"
#include "my_main.hpp"
#include "my_thing_template.hpp"
#include "my_thing_templates.hpp"

bool tp_load_snake(void)
{
  TRACE_NO_INDENT();

  auto tp = tp_load("snake");
  if (! tp) {
    ERR("failed to load template crystal");
    return false;
  }

  tp->z_depth_set(MAP_DEPTH_OBJ2);
  tp->is_monst1             = true;
  tp->is_blit_on_ground     = true;
  tp->is_animated_can_hflip = true;

  auto delay = 200;

  for (auto frame = 0; frame < 4; frame++) {
    auto tile      = tile_find_mand("snake." + std::to_string(frame));
    tile->delay_ms = delay;
    tp->tiles.push_back(tile);
  }

  return true;
}
