//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_main.hpp"
#include "my_tile.hpp"
#include "my_tp.hpp"
#include "my_tp_callbacks.hpp"
#include "my_tps.hpp"
#include "my_types.hpp"

static std::string tp_potion_description_get(Gamep g, Levelsp v, Levelp l, Thingp t)
{
  TRACE_NO_INDENT();

  return "potion";
}

static bool tp_potion_on_carry_request(Gamep g, Levelsp v, Levelp l, Thingp t, Thingp collecter)
{
  TRACE_NO_INDENT();

  return true;
}

static bool tp_potion_on_drop_request(Gamep g, Levelsp v, Levelp l, Thingp t, Thingp dropper)
{
  TRACE_NO_INDENT();

  return true;
}

bool tp_load_potion(void)
{
  TRACE_NO_INDENT();

  auto tp   = tp_load("potion"); // keep as string for scripts
  auto name = tp_name(tp);

  // begin sort marker1 {
  tp_chance_set(tp, THING_CHANCE_CONTINUE_TO_BURN, "1d2"); // roll max to continue burning
  tp_description_set(tp, tp_potion_description_get);
  tp_flag_set(tp, is_able_to_fall);
  tp_flag_set(tp, is_animated);
  tp_flag_set(tp, is_blit_centered);
  tp_flag_set(tp, is_burnable); // is capable of being burned by fire
  tp_flag_set(tp, is_collectable);
  tp_flag_set(tp, is_combustible); // will continue to burn once on fire
  tp_flag_set(tp, is_described_cursor);
  tp_flag_set(tp, is_item_mergeable);
  tp_flag_set(tp, is_inventory_item);
  tp_flag_set(tp, is_item);
  tp_flag_set(tp, is_loggable);
  tp_flag_set(tp, is_obs_to_falling_onto);
  tp_flag_set(tp, is_physics_explosion);
  tp_flag_set(tp, is_physics_temperature);
  tp_flag_set(tp, is_submergible); // is seen submerged when in water
  tp_flag_set(tp, is_tickable);
  tp_flag_set(tp, is_treasure);
  tp_long_name_set(tp, name);
  tp_on_carry_request_set(tp, tp_potion_on_carry_request);
  tp_on_drop_request_set(tp, tp_potion_on_drop_request);
  tp_temperature_burns_at_set(tp, 30);  // celsius
  tp_temperature_damage_at_set(tp, 30); // celsius
  tp_temperature_initial_set(tp, 20);   // celsius
  tp_weight_set(tp, WEIGHT_FEATHER);    // grams
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
