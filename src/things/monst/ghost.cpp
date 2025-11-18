//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_thing_callbacks.hpp"
#include "my_tile.hpp"
#include "my_tp.hpp"
#include "my_tps.hpp"
#include "my_types.hpp"

static std::string tp_ghost_description_get(Gamep g, Levelsp v, Levelp l, Thingp t)
{
  TRACE_NO_INDENT();

  return "vengeful spirit";
}

static std::string tp_ghost_detail_get(Gamep g, Levelsp v, Levelp l, Thingp t)
{
  TRACE_NO_INDENT();

  return "The spirit of one less fortunate than you. Beware, such spirits can traverse chasms and float through "
         "solid rock.";
}

bool tp_load_ghost(void)
{
  auto tp   = tp_load("ghost"); // keep as string for scripts
  auto name = tp_name(tp);

  // begin sort marker1 {
  thing_description_set(tp, tp_ghost_description_get);
  thing_detail_set(tp, tp_ghost_detail_get);
  tp_flag_set(tp, is_animated_can_hflip);
  tp_flag_set(tp, is_animated);
  tp_flag_set(tp, is_blit_centered);
  tp_flag_set(tp, is_described_cursor);
  tp_flag_set(tp, is_ethereal);
  tp_flag_set(tp, is_ghost);
  tp_flag_set(tp, is_health_bar_shown);
  tp_flag_set(tp, is_levitating);
  tp_flag_set(tp, is_light_source, 1);
  tp_flag_set(tp, is_loggable);
  tp_flag_set(tp, is_minion);
  tp_flag_set(tp, is_monst);
  tp_flag_set(tp, is_tickable);
  tp_flag_set(tp, is_undead);
  tp_flag_set(tp, is_walk_through_walls);
  tp_health_set(tp, "1");
  tp_is_immunity_add(tp, THING_EVENT_FIRE_DAMAGE);
  tp_is_immunity_add(tp, THING_EVENT_HEAT_DAMAGE);
  tp_is_immunity_add(tp, THING_EVENT_WATER_DAMAGE);
  tp_light_color_set(tp, "cyan");
  tp_long_name_set(tp, name);
  tp_monst_group_add(tp, MONST_GROUP_MOB);
  tp_priority_set(tp, THING_PRIORITY_MONST);
  tp_speed_set(tp, 100);
  tp_temperature_initial_set(tp, -10); // celsius
  tp_weight_set(tp, WEIGHT_FEATHER);   // grams
  tp_z_depth_set(tp, MAP_Z_DEPTH_OBJ);
  // end sort marker1 }

  auto delay = 1000;

  for (auto frame = 0; frame < 2; frame++) {
    auto tile = tile_find_mand(name + std::string(".idle.") + std::to_string(frame));
    tile_delay_ms_set(tile, delay);
    tp_tiles_push_back(tp, THING_ANIM_IDLE, tile);
  }

  return true;
}
