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

static std::string tp_secret_door_description_get(Gamep g, Levelsp v, Levelp l, Thingp me, Thingp owner, spoint at)
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
  tp_flag_set(tp, is_burnable);
  tp_flag_set(tp, is_cursor_path_blocker);
  tp_flag_set(tp, is_described_cursor);
  tp_flag_set(tp, is_door);
  tp_flag_set(tp, is_loggable);
  tp_flag_set(tp, is_obstacle_block);
  tp_flag_set(tp, is_secret_door);
  tp_health_initial_set(tp, 200);
  tp_is_immunity_add(tp, THING_EVENT_FIRE);
  tp_is_immunity_add(tp, THING_EVENT_HEAT);
  tp_is_immunity_add(tp, THING_EVENT_MELEE);
  tp_temperature_burns_at_set(tp, 300);  // celsius
  tp_temperature_damage_at_set(tp, 300); // celsius
  tp_temperature_initial_set(tp, 20);    // celsius
  tp_weight_set(tp, 1000);               // pounds
  tp_z_depth_set(tp, MAP_Z_DEPTH_OBJ);
  tp_z_prio_set(tp, MAP_Z_PRIO_NORMAL);
  // end sort marker1 }

  tp_tiles_push_back(tp, THING_ANIM_IDLE, tile_find_mand("secret_door.idle.0"));
  tp_tiles_push_back(tp, THING_ANIM_OPEN, tile_find_mand("secret_door.open.0"));

  return true;
}
