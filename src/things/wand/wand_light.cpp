//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_main.hpp"
#include "my_thing_callbacks.hpp"
#include "my_thing_inlines.hpp"
#include "my_tile.hpp"
#include "my_tp.hpp"
#include "my_tps.hpp"
#include "my_types.hpp"
#include "my_ui.hpp"

static auto tp_wand_light_description_get(Gamep g, Levelsp v, Levelp l, Thingp t) -> std::string
{
  TRACE();

  return "wand_light";
}

static auto tp_wand_light_detail_get(Gamep g, Levelsp v, Levelp l, Thingp t) -> std::string
{
  TRACE();

  return                                                                                                       //
      UI_INFO1_FMT_STR "This wand of light unleashes a dazzling beam of pure energy but without heat. \n"      //
      UI_INFO2_FMT_STR "Strategy: unlike wands of fire, this wand is safe to use in dense foliage. \n"         //
      UI_INFO2_FMT_STR "Strategy: for extra points, line up certain types of enemies for group punishment. \n" //
      UI_INFO3_FMT_STR "Strategy: wands operate at near infinite speed and monsters cannot avoid them. \n"     //
      UI_INFO4_FMT_STR "Info: wands are generally more powerful than staffs, but have fewer charges. \n";
}

[[nodiscard]] static auto tp_wand_light_on_carry_request(Gamep g, Levelsp v, Levelp l, Thingp t, Thingp collector, ThingEvent &e) -> bool
{
  TRACE();

  return true;
}

[[nodiscard]] static auto tp_wand_light_on_drop_request(Gamep g, Levelsp v, Levelp l, Thingp t, Thingp dropper, ThingEvent &e) -> bool
{
  TRACE();

  return true;
}

[[nodiscard]] static auto tp_wand_light_on_carry_success(Gamep g, Levelsp v, Levelp l, Thingp t, Thingp collector, ThingEvent &e) -> bool
{
  TRACE();

  if (e.event_type == THING_EVENT_USER_INITIATED) {
    if (thing_is_player(collector)) {
      thing_sound_play(g, v, l, collector, "item_collect");
    }
  }

  return true;
}

[[nodiscard]] static auto tp_wand_light_on_drop_success(Gamep g, Levelsp v, Levelp l, Thingp t, Thingp dropper, ThingEvent &e) -> bool
{
  TRACE();

  if (thing_is_player(dropper)) {
    thing_sound_play(g, v, l, dropper, "item_drop");
  }

  return true;
}

[[nodiscard]] static auto tp_wand_light_on_wield_request(Gamep g, Levelsp v, Levelp l, Thingp t, Thingp user) -> bool
{
  TRACE();

  return true;
}

[[nodiscard]] static auto tp_wand_light_on_light_weapon_request(Gamep g, Levelsp v, Levelp l, Thingp t, Thingp user) -> Tpp
{
  TRACE();

  static Tpp what;
  if (! what) {
    what = tp_find_mand("laser_light");
  }

  return what;
}

[[nodiscard]] auto tp_load_wand_light() -> bool
{
  TRACE();

  auto *tp   = tp_load("wand_light"); // keep as string for scripts
  auto  name = tp_name(tp);

  // begin sort marker1 {
  thing_description_set(tp, tp_wand_light_description_get);
  thing_detail_set(tp, tp_wand_light_detail_get);
  thing_on_carry_request_set(tp, tp_wand_light_on_carry_request);
  thing_on_carry_success_set(tp, tp_wand_light_on_carry_success);
  thing_on_drop_request_set(tp, tp_wand_light_on_drop_request);
  thing_on_drop_success_set(tp, tp_wand_light_on_drop_success);
  thing_on_use_weapon_request_set(tp, tp_wand_light_on_light_weapon_request);
  thing_on_wield_request_set(tp, tp_wand_light_on_wield_request);
  tp_charge_count_set(tp, 500);
  tp_flag_set(tp, is_able_to_fall_sound);
  tp_flag_set(tp, is_able_to_fall);
  tp_flag_set(tp, is_animated);
  tp_flag_set(tp, is_auto_wield);
  tp_flag_set(tp, is_blit_centered);
  tp_flag_set(tp, is_blit_hit_outline_w_black_inside);
  tp_flag_set(tp, is_blit_shown_in_chasms);
  tp_flag_set(tp, is_collectable);
  tp_flag_set(tp, is_collision_circle_small);
  tp_flag_set(tp, is_combustible); // will continue to burn once on light
  tp_flag_set(tp, is_dead_when_discharged);
  tp_flag_set(tp, is_described_cursor);
  tp_flag_set(tp, is_droppable);
  tp_flag_set(tp, is_inventory_item);
  tp_flag_set(tp, is_item);
  tp_flag_set(tp, is_light_source, 2);
  tp_flag_set(tp, is_loggable);
  tp_flag_set(tp, is_physics_explosion);
  tp_flag_set(tp, is_physics_temperature);
  tp_flag_set(tp, is_submergible); // is seen submerged when in water
  tp_flag_set(tp, is_tick_on_drop);
  tp_flag_set(tp, is_tickable);
  tp_flag_set(tp, is_treasure);
  tp_flag_set(tp, is_wand);
  tp_flag_set(tp, is_wood);
  tp_flag_set(tp, wieldable);
  tp_health_set(tp, "1d4");
  tp_is_immune_add(tp, THING_EVENT_FIRE_DAMAGE);
  tp_light_color_set(tp, "red");
  tp_name_a_or_an_set(tp, "a wand of light");
  tp_name_apostrophize_set(tp, "wand of light's");
  tp_name_long_set(tp, "wand of light");
  tp_name_pluralize_set(tp, "wands of light");
  tp_name_short_set(tp, "wand of light");
  tp_priority_set(tp, THING_PRIORITY_OBJECT);
  tp_rarity_set(tp, THING_RARITY_UNCOMMON);
  tp_temperature_burns_at_set(tp, 30);  // celsius
  tp_temperature_damage_at_set(tp, 30); // celsius
  tp_temperature_initial_set(tp, 20);   // celsius
  tp_weight_set(tp, WEIGHT_LIGHT);      // grams
  tp_z_depth_set(tp, MAP_Z_DEPTH_OBJ);
  // end sort marker1 }

  auto delay = 20;

  for (auto frame = 0; frame < 2; frame++) {
    auto *tile = tile_find_mand(name + std::string(".") + std::to_string(frame));
    tile_size_set(tile, TILE_WIDTH, TILE_HEIGHT);
    tile_delay_ms_set(tile, delay);
    tp_tiles_push_back(tp, THING_ANIM_IDLE, tile);
  }

  return true;
}
