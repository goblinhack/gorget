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

static auto tp_potion_incineration_description_get(Gamep g, Levelsp v, Levelp l, Thingp t) -> std::string
{
  TRACE();

  return "potion, incineration";
}

static auto tp_potion_incineration_detail_get(Gamep g, Levelsp v, Levelp l, Thingp t) -> std::string
{
  TRACE();

  return UI_INFO1_FMT_STR "Consume this potion to set yourself on fire! Or give it to someone else...";
}

[[nodiscard]] static auto tp_potion_incineration_on_carry_request(Gamep g, Levelsp v, Levelp l, Thingp t, Thingp collector, ThingEvent &e)
    -> bool
{
  TRACE();

  return true;
}

[[nodiscard]] static auto tp_potion_incineration_on_drop_request(Gamep g, Levelsp v, Levelp l, Thingp t, Thingp dropper, ThingEvent &e)
    -> bool
{
  TRACE();

  return true;
}

[[nodiscard]] static auto tp_potion_incineration_on_carry_success(Gamep g, Levelsp v, Levelp l, Thingp t, Thingp collector, ThingEvent &e)
    -> bool
{
  TRACE();

  if (thing_is_player(collector)) {
    thing_sound_play(g, v, l, collector, "item_collect");
  }

  return true;
}

[[nodiscard]] static auto tp_potion_incineration_on_drop_success(Gamep g, Levelsp v, Levelp l, Thingp t, Thingp dropper, ThingEvent &e)
    -> bool
{
  TRACE();

  if (e.event_type == THING_EVENT_USER_INITIATED) {
    if (thing_is_player(dropper)) {
      thing_sound_play(g, v, l, dropper, "item_drop");
    }
  }

  return true;
}

static void tp_potion_incineration_spawn_explosion(Gamep g, Levelsp v, Levelp l, Thingp t)
{
  TRACE();

  const std::initializer_list< bpoint > points = {
      bpoint(-1, -1), bpoint(1, -1), bpoint(0, -1), bpoint(-1, 0), bpoint(1, 0), bpoint(0, 0), bpoint(-1, 1), bpoint(1, 1), bpoint(0, 1),
  };

  auto at = thing_at(t);

  for (auto delta : points) {
    auto p = at + delta;
    if (level_is_obs_to_explosion(g, v, l, p) == nullptr) {
      if (level_is_explosion(g, v, l, p) == nullptr) {
        (void) thing_spawn(g, v, l, tp_first(is_explosion), p);
      }
    }
  }

  auto *player = thing_player(g);
  if (player != nullptr) {
    if (thing_on_same_level_as_player(g, v, t)) {
      if (thing_vision_can_see_tile(g, v, l, player, at)) {
        topcon("The potion explodes!");
      } else {
        topcon("You hear a distant explosion!");
      }
    } else {
      topcon("You hear a very muffled explosion!");
    }
  }
}

static void tp_potion_incinertaion_on_thrown(Gamep g, Levelsp v, Levelp l, Thingp t, Thingp thrower)
{
  TRACE();

  //
  // Soft landing?
  //
  if ((level_is_chasm(g, v, l, thing_at(t)) != nullptr) || // newline
      (level_is_water(g, v, l, thing_at(t)) != nullptr)) {
    return;
  }

  ThingEvent e {
      .reason     = "by being thrown",  //
      .event_type = THING_EVENT_THROWN, //
  };

  THING_DBG(t, "dead due to being thrown");
  TRACE_INDENT();

  thing_dead(g, v, l, t, e);
}

static bool tp_potion_incineration_on_use(Gamep g, Levelsp v, Levelp l, Thingp t, Thingp user)
{
  TRACE();

  return true;
}

static void tp_potion_incineration_on_death(Gamep g, Levelsp v, Levelp l, Thingp t, ThingEvent &e)
{
  TRACE();

  if ((e.event_type == THING_EVENT_CARRIED) ||        //
      (e.event_type == THING_EVENT_CARRIED_MERGED) || //
      (e.event_type == THING_EVENT_USED)) {
    return;
  }

  tp_potion_incineration_spawn_explosion(g, v, l, t);
}

[[nodiscard]] auto tp_load_potion_incineration() -> bool
{
  TRACE();

  auto *tp   = tp_load("potion_incineration"); // keep as string for scripts
  auto  name = tp_name(tp);

  // begin sort marker1 {
  thing_description_set(tp, tp_potion_incineration_description_get);
  thing_detail_set(tp, tp_potion_incineration_detail_get);
  thing_on_carry_request_set(tp, tp_potion_incineration_on_carry_request);
  thing_on_carry_success_set(tp, tp_potion_incineration_on_carry_success);
  thing_on_death_set(tp, tp_potion_incineration_on_death);
  thing_on_drop_request_set(tp, tp_potion_incineration_on_drop_request);
  thing_on_drop_success_set(tp, tp_potion_incineration_on_drop_success);
  thing_on_thrown_set(tp, tp_potion_incinertaion_on_thrown);
  thing_on_use_set(tp, tp_potion_incineration_on_use);
  tp_chance_set(tp, THING_CHANCE_CONTINUE_TO_BURN, "1"); // roll max to continue burning
  tp_flag_set(tp, is_able_to_fall_sound);
  tp_flag_set(tp, is_able_to_fall);
  tp_flag_set(tp, is_animated);
  tp_flag_set(tp, is_blit_centered);
  tp_flag_set(tp, is_blit_hit_outline_w_black_inside);
  tp_flag_set(tp, is_blit_shown_in_chasms);
  tp_flag_set(tp, is_burnable); // is capable of being burned by fire
  tp_flag_set(tp, is_collectable);
  tp_flag_set(tp, is_collision_circle_small);
  tp_flag_set(tp, is_combustible); // will continue to burn once on fire
  tp_flag_set(tp, is_described_cursor);
  tp_flag_set(tp, is_droppable);
  tp_flag_set(tp, is_flammable); // easily catches fire
  tp_flag_set(tp, is_glass);
  tp_flag_set(tp, is_inventory_item);
  tp_flag_set(tp, is_item_mergeable);
  tp_flag_set(tp, is_item);
  tp_flag_set(tp, is_light_source, 2);
  tp_flag_set(tp, is_loggable);
  tp_flag_set(tp, is_physics_explosion);
  tp_flag_set(tp, is_physics_temperature);
  tp_flag_set(tp, is_submergible); // is seen submerged when in water
  tp_flag_set(tp, is_throwable);
  tp_flag_set(tp, is_tick_on_use);
  tp_flag_set(tp, is_tickable);
  tp_flag_set(tp, is_treasure);
  tp_flag_set(tp, is_usable);
  tp_health_set(tp, "1d4");
  tp_is_immune_add(tp, THING_EVENT_WATER_DAMAGE);
  tp_light_color_set(tp, "red");
  tp_name_a_or_an_set(tp, "a potion of incineration");
  tp_name_apostrophize_set(tp, "potion of incineration's");
  tp_name_long_set(tp, "potion of incineration");
  tp_name_pluralize_set(tp, "potions of incineration");
  tp_name_short_set(tp, "potion, incineration");
  tp_priority_set(tp, THING_PRIORITY_OBJECT);
  tp_rarity_set(tp, THING_RARITY_COMMON);
  tp_temperature_burns_at_set(tp, 30);  // celsius
  tp_temperature_damage_at_set(tp, 30); // celsius
  tp_temperature_initial_set(tp, 20);   // celsius
  tp_weight_set(tp, WEIGHT_LIGHT);      // grams
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
