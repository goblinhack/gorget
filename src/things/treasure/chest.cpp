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

static std::string tp_chest_description_get(Tpp tp, Thingp me, Thingp owner, point at)
{
  TRACE_NO_INDENT();

  if (thing_is_open(me)) {
    return "open chest";
  }
  if (thing_is_dead(me)) {
    return "broken chest";
  }
  return "closed chest";
}

bool tp_load_treasure(void)
{
  TRACE_NO_INDENT();

  auto name = "chest";
  auto tp   = tp_load("chest");

  // begin sort marker1 {
  tp_description_set(tp, tp_chest_description_get);
  tp_flag_set(tp, is_animated, true);
  tp_flag_set(tp, is_blit_centered, true);
  tp_flag_set(tp, is_described_cursor, true);
  tp_flag_set(tp, is_treasure, true);
  tp_flag_set(tp, is_treasure2, true);
  tp_z_depth_set(tp, MAP_Z_DEPTH_OBJ);
  tp_z_prio_set(tp, MAP_Z_PRIO_NORMAL);
  // end sort marker1 }

  auto delay = 1000;

  for (auto frame = 0; frame < 2; frame++) {
    auto tile = tile_find_mand(name + std::string(".") + std::to_string(frame));
    tile_delay_ms_set(tile, delay);
    tp_tiles_push_back(tp, THING_ANIM_IDLE, tile);
  }

  return true;
}
