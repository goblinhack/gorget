//
// Copyright goblinhack@gmail.com
//

#include "../../my_callstack.hpp"
#include "../../my_minimal.hpp"
#include "../../my_tile.hpp"
#include "../../my_tp.hpp"
#include "../../my_tp_callbacks.hpp"
#include "../../my_tps.hpp"

static std::string tp_ghost_description_get(Tpp tp, Thingp me, Thingp owner, point at)
{
  TRACE_NO_INDENT();

  return "vengeful spirit";
}

bool tp_load_ghost(void)
{
  auto name = "ghost";
  auto tp   = tp_load("ghost");

  // begin sort marker1 {
  tp_description_set(tp, tp_ghost_description_get);
  tp_flag_set(tp, is_able_to_walk_through_walls, true);
  tp_flag_set(tp, is_animated_can_hflip, true);
  tp_flag_set(tp, is_animated, true);
  tp_flag_set(tp, is_ethereal, true);
  tp_flag_set(tp, is_levitating, true);
  tp_flag_set(tp, is_blit_centered, true);
  tp_flag_set(tp, is_described_cursor, true);
  tp_flag_set(tp, is_ghost, true);
  tp_flag_set(tp, is_minion, true);
  tp_flag_set(tp, is_monst, true);
  tp_flag_set(tp, is_tickable, true);
  tp_speed_set(tp, 100);
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
