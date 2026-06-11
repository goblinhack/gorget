//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_thing.hpp"
#include "my_tp.hpp"
#include "my_types.hpp"

//
// Given an existing thing, enhance it with the tp. This way we can apply buffs repeatedly.
//
void thing_enhance(Gamep g, Levelsp v, Levelp l, Thingp t, Tpp tp)
{
  TRACE();

  if (t == nullptr) {
    return;
  }

  if (tp == nullptr) {
    return;
  }

  (void) thing_health_max_incr(g, v, l, t, thing_health_incr(g, v, l, t, tp_health_max_get(tp)));
  (void) thing_stamina_max_incr(g, v, l, t, thing_stamina_incr(g, v, l, t, tp_stamina_max_get(tp)));
  (void) thing_distance_jump_incr(g, v, l, t, tp_distance_jump_get(tp));
  (void) thing_distance_vision_incr(g, v, l, t, tp_distance_vision_get(tp));
  (void) thing_minion_max_incr(g, v, l, t, tp_minion_max_get(tp));
  (void) thing_missile_count_max_incr(g, v, l, t, tp_missile_count_max_get(tp));
  (void) thing_score_value_incr(g, v, l, t, tp_score_value_get(tp));
  (void) thing_speed_incr(g, v, l, t, tp_speed_get(tp));
  (void) thing_temperature_incr(g, v, l, t, tp_temperature_initial_get(tp));
  (void) thing_charge_count_incr(g, v, l, t, tp_charge_count_get(tp));
  (void) thing_distance_avoid_target_incr(g, v, l, t, tp_distance_avoid_target_get(tp));
  (void) thing_lifespan_initial_set(g, v, l, t, thing_lifespan_incr(g, v, l, t, tp_lifespan_get(tp)));
  (void) thing_value1_incr(g, v, l, t, tp_value1_get(tp));
  (void) thing_value10_incr(g, v, l, t, tp_value10_get(tp));
  (void) thing_value11_incr(g, v, l, t, tp_value11_get(tp));
  (void) thing_value12_incr(g, v, l, t, tp_value12_get(tp));
  (void) thing_value13_incr(g, v, l, t, tp_value13_get(tp));
  (void) thing_value14_incr(g, v, l, t, tp_value14_get(tp));
  (void) thing_value15_incr(g, v, l, t, tp_value15_get(tp));
  (void) thing_distance_throw_incr(g, v, l, t, tp_distance_throw_get(tp));
  (void) thing_value2_incr(g, v, l, t, tp_value2_get(tp));
  (void) thing_value3_incr(g, v, l, t, tp_value3_get(tp));
  (void) thing_value4_incr(g, v, l, t, tp_value4_get(tp));
  (void) thing_value5_incr(g, v, l, t, tp_value5_get(tp));
  (void) thing_value6_incr(g, v, l, t, tp_value6_get(tp));
  (void) thing_value7_incr(g, v, l, t, tp_value7_get(tp));
  (void) thing_value8_incr(g, v, l, t, tp_value8_get(tp));
  (void) thing_value9_incr(g, v, l, t, tp_value9_get(tp));
}
