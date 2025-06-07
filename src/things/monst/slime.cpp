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

static std::string tp_slime_description_get(Gamep g, Levelsp v, Levelp l, Thingp me, Thingp owner, point at)
{
  TRACE_NO_INDENT();

  if (thing_is_dead(me)) {
    return "dead slime";
  }
  return "living slime";
}

bool tp_load_slime(void)
{
  auto name = "slime";
  auto tp   = tp_load("slime");

  // begin sort marker1 {
  tp_description_set(tp, tp_slime_description_get);
  tp_flag_set(tp, is_animated_can_hflip);
  tp_flag_set(tp, is_animated);
  tp_flag_set(tp, is_blit_centered);
  tp_flag_set(tp, is_described_cursor);
  tp_flag_set(tp, is_loggable);
  tp_flag_set(tp, is_minion);
  tp_flag_set(tp, is_monst);
  tp_flag_set(tp, is_monst2);
  tp_flag_set(tp, is_slime);
  tp_flag_set(tp, is_tickable);
  tp_speed_set(tp, 100);
  tp_weight_set(tp, 200); // pounds
  tp_z_depth_set(tp, MAP_Z_DEPTH_OBJ);
  tp_z_prio_set(tp, MAP_Z_PRIO_NORMAL);
  // end sort marker1 }

  auto delay = 1000;

  for (auto frame = 0; frame < 2; frame++) {
    auto tile = tile_find_mand(name + std::string(".idle.") + std::to_string(frame));
    tile_delay_ms_set(tile, delay);
    tp_tiles_push_back(tp, THING_ANIM_IDLE, tile);
  }

  return true;
}
