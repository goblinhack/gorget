//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_level.hpp"
#include "my_thing.hpp"
#include "my_tile.hpp"
#include "my_tp.hpp"
#include "my_tp_callbacks.hpp"
#include "my_tps.hpp"
#include "my_types.hpp"

static std::string tp_brazier_description_get(Gamep g, Levelsp v, Levelp l, Thingp me)
{
  TRACE_NO_INDENT();

  if (thing_is_dead(me)) {
    return "extinguished brazier";
  }

  return "brightly burning brazier";
}

static void tp_brazier_on_shoved(Gamep g, Levelsp v, Levelp l, Thingp me, Thingp shover)
{
  TRACE_NO_INDENT();

  //
  // If extinguished, do not generate more smoke
  //
  if (thing_is_dead(me)) {
    if (! level_is_smoke(g, v, l, me->at)) {
      thing_spawn(g, v, l, tp_random(is_smoke), me->at);
    }
    return;
  }

  //
  // Attempt to spawn fire in the direction of shoving
  //
  if (shover) {
    auto direction = me->at - shover->at;
    auto fire_at   = me->at + direction;

    if (level_is_obstacle_to_fire(g, v, l, fire_at)) {
      //
      // If we can't, then spawn over the brazier
      //
      if (! level_is_fire(g, v, l, me->at)) {
        thing_spawn(g, v, l, tp_random(is_fire), me->at);
      }
    } else {
      if (! level_is_fire(g, v, l, fire_at)) {
        thing_spawn(g, v, l, tp_random(is_fire), fire_at);
      }

      if (! level_is_smoke(g, v, l, me->at)) {
        thing_spawn(g, v, l, tp_random(is_smoke), me->at);
      }
    }
  } else {
    //
    // Spawn over the brazier
    //
    if (! level_is_fire(g, v, l, me->at)) {
      thing_spawn(g, v, l, tp_random(is_fire), me->at);
    }
  }
}

static void tp_brazier_on_death(Gamep g, Levelsp v, Levelp l, Thingp me, ThingEvent &e)
{
  TRACE_NO_INDENT();

  //
  // Allow things to continue to burn if we still have some burnable material
  //
  if (e.event_type != THING_EVENT_SHOVED) {
    if (! level_is_fire(g, v, l, me->at)) {
      thing_spawn(g, v, l, tp_random(is_fire), me->at);
    }
  }

  if (! level_is_smoke(g, v, l, me->at)) {
    thing_spawn(g, v, l, tp_random(is_smoke), me->at);
  }
}

bool tp_load_brazier(void)
{
  TRACE_NO_INDENT();

  auto tp   = tp_load("brazier"); // keep as string for scripts
  auto name = tp_name(tp);

  // begin sort marker1 {
  tp_description_set(tp, tp_brazier_description_get);
  tp_flag_set(tp, is_animated);
  tp_flag_set(tp, is_blit_centered);
  tp_flag_set(tp, is_blit_square_outlined);
  tp_flag_set(tp, is_brazier);
  tp_flag_set(tp, is_corpse_on_death);
  tp_flag_set(tp, is_cursor_path_hazard);
  tp_flag_set(tp, is_dead_on_shoving);
  tp_flag_set(tp, is_described_cursor);
  tp_flag_set(tp, is_extinguished_on_death);
  tp_flag_set(tp, is_light_source, 3);
  tp_flag_set(tp, is_loggable);
  tp_flag_set(tp, is_obstacle_to_landing);
  tp_flag_set(tp, is_obstacle_to_movement);
  tp_flag_set(tp, is_physics_gravity);
  tp_flag_set(tp, is_physics_water);
  tp_flag_set(tp, is_shovable);
  tp_flag_set(tp, is_submergible); // is seen submerged when in water
  tp_light_color_set(tp, "orange");
  tp_long_name_set(tp, name);
  tp_on_death_set(tp, tp_brazier_on_death);
  tp_on_shoved_set(tp, tp_brazier_on_shoved);
  tp_weight_set(tp, WEIGHT_MEDIUM); // grams
  tp_z_depth_set(tp, MAP_Z_DEPTH_OBJ);
  // end sort marker1 }

  auto delay = 200;

  for (auto frame = 0; frame < 31; frame++) {
    auto tile = tile_find_mand(name + std::string(".idle.") + std::to_string(frame));
    tile_delay_ms_set(tile, delay);
    tp_tiles_push_back(tp, THING_ANIM_IDLE, tile);
  }

  for (auto frame = 0; frame < 1; frame++) {
    auto tile = tile_find_mand(name + std::string(".dead.") + std::to_string(frame));
    tile_delay_ms_set(tile, delay);
    tp_tiles_push_back(tp, THING_ANIM_DEAD, tile);
  }

  return true;
}
