//
// Copyright goblinhack@gmail.com
//

#include "../../my_callstack.hpp"
#include "../../my_thing.hpp"
#include "../../my_tile.hpp"
#include "../../my_tp.hpp"
#include "../../my_tp_callbacks.hpp"
#include "../../my_tps.hpp"
#include "../../my_types.hpp"

static std::string tp_secret_door_description_get(Gamep g, Levelsp v, Levelp l, Thingp me)
{
  TRACE_NO_INDENT();

  if (thing_is_open(me)) {
    return "secret door";
  }

  return "odd looking rock";
}

bool tp_load_secret_door(void)
{
  TRACE_NO_INDENT();

  auto tp = tp_load("secret_door");
  // begin sort marker1 {
  tp_description_set(tp, tp_secret_door_description_get);
  tp_flag_set(tp, is_blit_centered);
  tp_flag_set(tp, is_cursor_path_blocker);
  tp_flag_set(tp, is_described_cursor);
  tp_flag_set(tp, is_door);
  tp_flag_set(tp, is_loggable);
  tp_flag_set(tp, is_obstacle_to_fire);
  tp_flag_set(tp, is_obstacle_to_landing);
  tp_flag_set(tp, is_obstacle_to_movement);
  tp_flag_set(tp, is_physics_temperature);
  tp_flag_set(tp, is_secret_door);
  tp_health_initial_set(tp, "1d200");
  tp_is_immunity_add(tp, THING_EVENT_FIRE_DAMAGE);
  tp_is_immunity_add(tp, THING_EVENT_HEAT_DAMAGE);
  tp_is_immunity_add(tp, THING_EVENT_MELEE_DAMAGE);
  tp_is_immunity_add(tp, THING_EVENT_WATER_DAMAGE);
  tp_weight_set(tp, WEIGHT_VHEAVY); // grams
  tp_z_depth_set(tp, MAP_Z_DEPTH_OBJ);
  // end sort marker1 }

  tp_tiles_push_back(tp, THING_ANIM_IDLE, tile_find_mand("secret_door.idle.0"));
  tp_tiles_push_back(tp, THING_ANIM_OPEN, tile_find_mand("secret_door.open.0"));

  return true;
}
