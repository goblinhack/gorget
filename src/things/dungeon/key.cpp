//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_tile.hpp"
#include "my_tp.hpp"
#include "my_tp_callbacks.hpp"
#include "my_tps.hpp"
#include "my_types.hpp"

static std::string tp_key_description_get(Gamep g, Levelsp v, Levelp l, Thingp t)
{
  TRACE_NO_INDENT();

  return "a... key";
}

bool tp_load_key(void)
{
  TRACE_NO_INDENT();

  auto tp   = tp_load("key"); // keep as string for scripts
  auto name = tp_name(tp);

  // begin sort marker1 {
  tp_description_set(tp, tp_key_description_get);
  tp_flag_set(tp, is_animated);
  tp_flag_set(tp, is_blit_centered);
  tp_flag_set(tp, is_collectable);
  tp_flag_set(tp, is_described_cursor);
  tp_flag_set(tp, is_key);
  tp_flag_set(tp, is_loggable);
  tp_flag_set(tp, is_physics_gravity);
  tp_flag_set(tp, is_submergible); // is seen submerged when in water
  tp_long_name_set(tp, name);
  tp_weight_set(tp, WEIGHT_FEATHER); // grams
  tp_z_depth_set(tp, MAP_Z_DEPTH_OBJ);
  // end sort marker1 }

  auto delay = 1000;

  for (auto frame = 0; frame < 2; frame++) {
    auto tile = tile_find_mand(name + std::string(".") + std::to_string(frame));
    tile_delay_ms_set(tile, delay);
    tp_tiles_push_back(tp, THING_ANIM_IDLE, tile);
  }

  return true;
}
