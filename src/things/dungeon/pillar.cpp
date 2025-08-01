//
// Copyright goblinhack@gmail.com
//

#include "../../my_callstack.hpp"
#include "../../my_tile.hpp"
#include "../../my_tp.hpp"
#include "../../my_tp_callbacks.hpp"
#include "../../my_tps.hpp"
#include "../../my_types.hpp"

static std::string tp_pillar_description_get(Gamep g, Levelsp v, Levelp l, Thingp me)
{
  TRACE_NO_INDENT();

  return "ancient moss covered pillar";
}

bool tp_load_pillar(void)
{
  TRACE_NO_INDENT();

  std::string name = "pillar";
  auto        tp   = tp_load("pillar");

  // begin sort marker1 {
  tp_description_set(tp, tp_pillar_description_get);
  tp_flag_set(tp, is_blit_centered);
  tp_flag_set(tp, is_cursor_path_blocker);
  tp_flag_set(tp, is_described_cursor);
  tp_flag_set(tp, is_obstacle_to_fire);
  tp_flag_set(tp, is_obstacle_to_landing);
  tp_flag_set(tp, is_obstacle_to_movement);
  tp_flag_set(tp, is_physics_gravity);
  tp_flag_set(tp, is_pillar);
  tp_flag_set(tp, is_submergible); // is seen submerged when in water
  tp_health_initial_set(tp, "1d500");
  tp_is_immunity_add(tp, THING_EVENT_FIRE_DAMAGE);
  tp_is_immunity_add(tp, THING_EVENT_HEAT_DAMAGE);
  tp_is_immunity_add(tp, THING_EVENT_MELEE_DAMAGE);
  tp_is_immunity_add(tp, THING_EVENT_WATER_DAMAGE);
  tp_weight_set(tp, WEIGHT_VVVHEAVY); // grams
  tp_z_depth_set(tp, MAP_Z_DEPTH_OBJ);
  // end sort marker1 }

  for (auto frame = 0; frame < 16; frame++) {
    auto tile = tile_find_mand(name + std::string(".") + std::to_string(frame));
    tp_tiles_push_back(tp, THING_ANIM_IDLE, tile);
  }

  return true;
}
