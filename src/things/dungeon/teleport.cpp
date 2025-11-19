//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_thing_callbacks.hpp"
#include "my_tile.hpp"
#include "my_tp.hpp"
#include "my_tps.hpp"
#include "my_types.hpp"

static std::string tp_teleport_description_get(Gamep g, Levelsp v, Levelp l, Thingp t)
{
  TRACE_NO_INDENT();

  return "teleport";
}

static std::string tp_teleport_detail_get(Gamep g, Levelsp v, Levelp l, Thingp t)
{
  TRACE_NO_INDENT();

  return "Run of the mill teleport.";
}

bool tp_load_teleport(void)
{
  TRACE_NO_INDENT();

  auto tp   = tp_load("teleport"); // keep as string for scripts
  auto name = tp_name(tp);

  // begin sort marker1 {
  thing_description_set(tp, tp_teleport_description_get);
  thing_detail_set(tp, tp_teleport_detail_get);
  tp_flag_set(tp, is_animated);
  tp_flag_set(tp, is_blit_centered);
  tp_flag_set(tp, is_blit_colored_always);
  tp_flag_set(tp, is_blit_if_has_seen);
  tp_flag_set(tp, is_blit_in_chasm);
  tp_flag_set(tp, is_described_cursor);
  tp_flag_set(tp, is_indestructible);
  tp_flag_set(tp, is_light_source, 4);
  tp_flag_set(tp, is_obs_to_falling_onto);
  tp_flag_set(tp, is_teleport_blocked);
  tp_flag_set(tp, is_teleport);
  tp_is_immunity_add(tp, THING_EVENT_WATER_DAMAGE);
  tp_light_color_set(tp, "red");
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
