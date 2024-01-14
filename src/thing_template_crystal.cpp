//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_level_data.hpp"
#include "my_main.hpp"
#include "my_thing_template.hpp"
#include "my_thing_templates.hpp"

bool tp_load_crystal(void)
{
  TRACE_NO_INDENT();

  for (auto c = 0; c < 7; c++) {
    std::string name = "crystal" + std::to_string(c);

    auto tp = tp_load(name);
    if (! tp) {
      ERR("failed to load template crystal");
      return false;
    }

    tp->z_depth_set(MAP_DEPTH_OBJ2);
    tp->is_crystal        = true;
    tp->is_blit_on_ground = true;

    tp->tiles.push_back(tile_find_mand(name));
  }

  return true;
}
