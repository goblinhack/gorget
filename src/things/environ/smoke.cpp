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

static std::string tp_smoke_description_get(Gamep g, Levelsp v, Levelp l, Thingp me)
{
  TRACE_NO_INDENT();

  return "thick smoke";
}

bool tp_load_smoke(void)
{
  TRACE_NO_INDENT();

  std::string name = "smoke";
  auto        tp   = tp_load("smoke");

  // begin sort marker1 {
  tp_description_set(tp, tp_smoke_description_get);
  tp_flag_set(tp, is_animated);
  tp_flag_set(tp, is_blit_centered);
  tp_flag_set(tp, is_described_cursor);
  tp_flag_set(tp, is_gaseous);
  tp_flag_set(tp, is_indestructible);
  tp_flag_set(tp, is_loggable);
  tp_flag_set(tp, is_smoke);
  tp_flag_set(tp, is_tickable);
  tp_lifespan_set(tp, "1d6+3");
  tp_weight_set(tp, WEIGHT_NONE); // grams
  tp_z_depth_set(tp, MAP_Z_DEPTH_GAS);
  // end sort marker1 }

  auto delay = 200;

  for (auto frame = 0; frame < 16; frame++) {
    auto tile = tile_find_mand(name + std::string(".idle.") + std::to_string(frame));
    tile_delay_ms_set(tile, delay);
    tp_tiles_push_back(tp, THING_ANIM_IDLE, tile);
  }

  return true;
}
