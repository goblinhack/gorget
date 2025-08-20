//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_tile.hpp"
#include "my_tp.hpp"
#include "my_tp_callbacks.hpp"
#include "my_tps.hpp"
#include "my_types.hpp"

static std::string tp_teleport_description_get(Gamep g, Levelsp v, Levelp l, Thingp t)
{
  TRACE_NO_INDENT();

  return "teleport";
}

bool tp_load_teleport(void)
{
  TRACE_NO_INDENT();

  auto tp   = tp_load("teleport"); // keep as string for scripts
  auto name = tp_name(tp);

  // begin sort marker1 {
  tp_description_set(tp, tp_teleport_description_get);
  tp_flag_set(tp, is_animated);
  tp_flag_set(tp, is_blit_centered);
  tp_flag_set(tp, is_described_cursor);
  tp_flag_set(tp, is_indestructible);
  tp_flag_set(tp, is_obstacle_to_landing);
  tp_flag_set(tp, is_teleport);
  tp_long_name_set(tp, name);
  tp_weight_set(tp, WEIGHT_VVHEAVY); // grams
  tp_z_depth_set(tp, MAP_Z_DEPTH_OBJ);
  // end sort marker1 }

  auto delay = 100;

  for (auto frame = 0; frame < 7; frame++) {
    auto tile = tile_find_mand(name + std::string(".idle.") + std::to_string(frame));
    tile_delay_ms_set(tile, delay);
    tp_tiles_push_back(tp, THING_ANIM_IDLE, tile);
  }

  return true;
}
