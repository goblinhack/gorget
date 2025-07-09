//
// Copyright goblinhack@gmail.com
//

#include "../../my_callstack.hpp"
#include "../../my_level.hpp"
#include "../../my_thing.hpp"
#include "../../my_tile.hpp"
#include "../../my_tp.hpp"
#include "../../my_tp_callbacks.hpp"
#include "../../my_tps.hpp"
#include "../../my_types.hpp"

static std::string tp_fire_description_get(Gamep g, Levelsp v, Levelp l, Thingp me, Thingp owner, spoint at)
{
  TRACE_NO_INDENT();

  return "brightly burning fire";
}

static void tp_fire_tick_begin(Gamep g, Levelsp v, Levelp l, Thingp me, Thingp owner, spoint at)
{
  TRACE_NO_INDENT();
  THING_TOPCON(me, "tick");
}

static void tp_fire_on_death(Gamep g, Levelsp v, Levelp l, Thingp me, Thingp owner, spoint at)
{
  TRACE_NO_INDENT();

  if (! level_is_smoke(g, v, l, me->at)) {
    thing_spawn(g, v, l, tp_random(is_smoke), me->at);
  }
}

bool tp_load_fire(void)
{
  TRACE_NO_INDENT();

  auto name = "fire";
  auto tp   = tp_load("fire");

  // begin sort marker1 {
  tp_damage_set(tp, THING_EVENT_FIRE, "1d6");
  tp_description_set(tp, tp_fire_description_get);
  tp_tick_begin_set(tp, tp_fire_tick_begin);
  tp_on_death_set(tp, tp_fire_on_death);
  tp_flag_set(tp, is_animated);
  tp_flag_set(tp, is_blit_centered);
  tp_flag_set(tp, is_cursor_path_hazard);
  tp_flag_set(tp, is_described_cursor);
  tp_flag_set(tp, is_tickable);
  tp_flag_set(tp, is_fire);
  tp_flag_set(tp, is_light_source, 3);
  tp_flag_set(tp, is_loggable);
  tp_is_immunity_add(tp, THING_EVENT_FIRE);
  tp_is_immunity_add(tp, THING_EVENT_HEAT);
  tp_lifespan_set(tp, "1d6+3");
  tp_light_color_set(tp, "orange");
  tp_temperature_initial_set(tp, 500); // celsius
  tp_z_depth_set(tp, MAP_Z_DEPTH_GAS);
  tp_z_layer_set(tp, MAP_Z_LAYER_NORMAL);
  // end sort marker1 }

  auto delay = 200;

  for (auto frame = 0; frame < 16; frame++) {
    auto tile = tile_find_mand(name + std::string(".idle.") + std::to_string(frame));
    tile_delay_ms_set(tile, delay);
    tp_tiles_push_back(tp, THING_ANIM_IDLE, tile);
  }

  return true;
}
