//
// Copyright goblinhack@gmail.com
//

#include "../../my_callstack.hpp"
#include "../../my_thing.hpp"
#include "../../my_tile.hpp"
#include "../../my_tp.hpp"
#include "../../my_tp_callbacks.hpp"
#include "../../my_tps.hpp"
#include "../../my_types.hpp"

static std::string tp_trap_description_get(Gamep g, Levelsp v, Levelp l, Thingp me, Thingp owner, spoint at)
{
  TRACE_NO_INDENT();

  if (thing_is_open(me)) {
    return "sprung trap";
  }

  return "odd looking floor tile";
}

bool tp_load_trap(void)
{
  TRACE_NO_INDENT();

  std::string name = "trap";
  auto        tp   = tp_load("trap");

  // begin sort marker1 {
  tp_description_set(tp, tp_trap_description_get);
  tp_flag_set(tp, is_blit_centered);
  tp_flag_set(tp, is_described_cursor);
  tp_flag_set(tp, is_loggable);
  tp_flag_set(tp, is_physics_gravity);
  tp_flag_set(tp, is_trap);
  tp_weight_set(tp, WEIGHT_FEATHER); // grams
  tp_z_depth_set(tp, MAP_Z_DEPTH_OBJ);
  tp_z_layer_set(tp, MAP_Z_LAYER_NORMAL);
  // end sort marker1 }

  for (auto frame = 0; frame < 1; frame++) {
    auto tile = tile_find_mand(name + std::string(".") + std::to_string(frame));
    tp_tiles_push_back(tp, THING_ANIM_IDLE, tile);
  }

  return true;
}
