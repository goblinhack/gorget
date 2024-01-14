//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_level_data.hpp"
#include "my_main.hpp"
#include "my_thing_template.hpp"
#include "my_thing_templates.hpp"

bool tp_load_entrance(void)
{
  TRACE_NO_INDENT();

  auto tp = tp_load("entrance");
  if (! tp) {
    ERR("failed to load template entrance");
    return false;
  }

  tp->z_depth_set(MAP_DEPTH_OBJ1);
  tp->is_entrance       = true;
  tp->is_blit_on_ground = true;

  tp->tiles.push_back(tile_find("entrance"));

  return true;
}
