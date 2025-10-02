//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_thing.hpp"
#include "my_tile.hpp"
#include "my_tp.hpp"
#include "my_tp_callbacks.hpp"
#include "my_tps.hpp"
#include "my_types.hpp"

static std::string tp_steam_description_get(Gamep g, Levelsp v, Levelp l, Thingp t)
{
  TRACE_NO_INDENT();

  return "thick steam";
}

bool tp_load_steam(void)
{
  TRACE_NO_INDENT();

  auto tp   = tp_load("steam"); // keep as string for scripts
  auto name = tp_name(tp);

  // begin sort marker1 {
  tp_damage_set(tp, THING_EVENT_HEAT_DAMAGE, "1d4");
  tp_description_set(tp, tp_steam_description_get);
  tp_flag_set(tp, is_animated);
  tp_flag_set(tp, is_blit_centered);
  tp_flag_set(tp, is_described_cursor);
  tp_flag_set(tp, is_gaseous);
  tp_flag_set(tp, is_indestructible);
  tp_flag_set(tp, is_light_blocker);
  tp_flag_set(tp, is_loggable);
  tp_flag_set(tp, is_physics_temperature);
  tp_flag_set(tp, is_steam);
  tp_flag_set(tp, is_teleport_blocked);
  tp_flag_set(tp, is_tick_delay_on_spawn);
  tp_flag_set(tp, is_tickable);
  tp_lifespan_set(tp, "1d6+3");
  tp_long_name_set(tp, name);
  tp_temperature_initial_set(tp, 100); // celsius
  tp_weight_set(tp, WEIGHT_NONE);      // grams
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
