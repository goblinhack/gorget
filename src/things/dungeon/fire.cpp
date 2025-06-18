//
// Copyright goblinhack@gmail.com
//

#include "../../my_callstack.hpp"
#include "../../my_minimal.hpp"
#include "../../my_thing.hpp"
#include "../../my_tile.hpp"
#include "../../my_tp.hpp"
#include "../../my_tp_callbacks.hpp"
#include "../../my_tps.hpp"

static std::string tp_fire_description_get(Gamep g, Levelsp v, Levelp l, Thingp me, Thingp owner, point at)
{
  TRACE_NO_INDENT();

  return "brightly burning fire";
}

bool tp_load_fire(void)
{
  TRACE_NO_INDENT();

  auto name = "fire";
  auto tp   = tp_load("fire");

  // begin sort marker1 {
  tp_description_set(tp, tp_fire_description_get);
  tp_flag_set(tp, is_animated);
  tp_flag_set(tp, is_blit_centered);
  tp_flag_set(tp, is_cursor_path_hazard);
  tp_flag_set(tp, is_described_cursor);
  tp_flag_set(tp, is_fire);
  tp_flag_set(tp, is_light_source, 3);
  tp_flag_set(tp, is_loggable);
  tp_light_color_set(tp, "orange");
  tp_temp_initial_set(tp, 500); // celsius
  tp_z_depth_set(tp, MAP_Z_DEPTH_OBJ);
  tp_z_prio_set(tp, MAP_Z_PRIO_NORMAL);
  // end sort marker1 }

  if (g_opt_tests) {
    return true;
  }

  auto delay = 200;

  for (auto frame = 0; frame < 16; frame++) {
    auto tile = tile_find_mand(name + std::string(".idle.") + std::to_string(frame));
    tile_delay_ms_set(tile, delay);
    tp_tiles_push_back(tp, THING_ANIM_IDLE, tile);
  }

  return true;
}
