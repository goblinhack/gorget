//
//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_thing_callbacks.hpp"
#include "my_tile.hpp"
#include "my_tp.hpp"
#include "my_tps.hpp"
#include "my_types.hpp"

static void tp_key_on_death(Gamep g, Levelsp v, Levelp l, Thingp t, ThingEvent &e)
{
  TRACE_NO_INDENT();

  if ((e.event_type == THING_EVENT_CARRIED) || // newline
      (e.event_type == THING_EVENT_CARRIED_MERGED)) {
    thing_sound_play(g, v, l, t, "key");
  }
}

static std::string tp_key_description_get(Gamep g, Levelsp v, Levelp l, Thingp t)
{
  TRACE_NO_INDENT();

  return "a... key";
}

bool tp_load_key()
{
  TRACE_NO_INDENT();

  auto *tp   = tp_load("key"); // keep as string for scripts
  auto  name = tp_name(tp);

  // begin sort marker1 {
  thing_description_set(tp, tp_key_description_get);
  thing_on_death_set(tp, tp_key_on_death);
  tp_flag_set(tp, is_able_to_fall);
  tp_flag_set(tp, is_animated);
  tp_flag_set(tp, is_blit_shown_in_chasms);
  tp_flag_set(tp, is_collectable);
  tp_flag_set(tp, is_described_cursor);
  tp_flag_set(tp, is_key);
  tp_flag_set(tp, is_light_source, 2);
  tp_flag_set(tp, is_loggable);
  tp_flag_set(tp, is_metal);
  tp_flag_set(tp, is_submergible); // is seen submerged when in water
  tp_is_immunity_add(tp, THING_EVENT_WATER_DAMAGE);
  tp_light_color_set(tp, "yellow");
  tp_long_name_set(tp, name);
  tp_weight_set(tp, WEIGHT_FEATHER); // grams
  tp_z_depth_set(tp, MAP_Z_DEPTH_OBJ);
  // end sort marker1 }

  auto delay = 1000;

  for (auto frame = 0; frame < 2; frame++) {
    auto *tile = tile_find_mand(name + std::string(".") + std::to_string(frame));
    tile_size_set(tile, TILE_WIDTH, TILE_HEIGHT);
    tile_delay_ms_set(tile, delay);
    tp_tiles_push_back(tp, THING_ANIM_IDLE, tile);
  }

  return true;
}
