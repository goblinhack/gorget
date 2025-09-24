//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_game.hpp"
#include "my_level.hpp"
#include "my_main.hpp"
#include "my_tp_callbacks.hpp"

Thingp thing_init(Gamep g, Levelsp v, Levelp l, Tpp tp, spoint at)
{
  TRACE_NO_INDENT();

  auto t = thing_alloc(g, v, l, tp, at);
  if (! t) {
    return nullptr;
  }

  t->at          = at;
  t->old_at      = at;
  t->moving_from = at;
  t->level_num   = l->level_num;

  //
  // Assign an initial tile
  //
  thing_anim_init(g, v, l, t, THING_ANIM_IDLE);

  //
  // Assign the player
  //
  if (tp_is_player(tp)) {
    //
    // Reset the player state
    //
    player_state_change(g, v, PLAYER_STATE_NORMAL);

    v->player_id = t->id;

    //
    // First time entering this level?
    //
    if (! l->entered) {
      level_entered(g, v, l);
    }
  }

  //
  // Assign the current level select id. This is only valid when in the select screen.
  //
  if (tp_is_level_curr(tp)) {
    v->level_select_id = t->id;
  }

  thing_speed_set(g, v, l, t, tp_speed_get(tp));
  thing_weight_set(g, v, l, t, tp_weight_get(tp));
  thing_temperature_set(g, v, l, t, tp_temperature_initial_get(tp));
  thing_value1_set(g, v, l, t, tp_value1_get(tp));
  thing_value2_set(g, v, l, t, tp_value2_get(tp));
  thing_value3_set(g, v, l, t, tp_value3_get(tp));
  thing_value4_set(g, v, l, t, tp_value4_get(tp));
  thing_value5_set(g, v, l, t, tp_value5_get(tp));
  thing_value6_set(g, v, l, t, tp_value6_get(tp));
  thing_value7_set(g, v, l, t, tp_value7_get(tp));
  thing_value8_set(g, v, l, t, tp_value8_get(tp));
  thing_value9_set(g, v, l, t, tp_value9_get(tp));
  thing_value10_set(g, v, l, t, tp_value10_get(tp));
  thing_value11_set(g, v, l, t, tp_value11_get(tp));
  thing_value12_set(g, v, l, t, tp_value12_get(tp));
  thing_value13_set(g, v, l, t, tp_value13_get(tp));
  thing_value14_set(g, v, l, t, tp_value14_get(tp));
  thing_value15_set(g, v, l, t, tp_value15_get(tp));
  thing_value16_set(g, v, l, t, tp_value16_get(tp));
  thing_value17_set(g, v, l, t, tp_value17_get(tp));
  thing_value18_set(g, v, l, t, tp_value18_get(tp));
  thing_value19_set(g, v, l, t, tp_value19_get(tp));
  thing_value20_set(g, v, l, t, tp_value20_get(tp));
  thing_value21_set(g, v, l, t, tp_value21_get(tp));
  thing_value22_set(g, v, l, t, tp_value22_get(tp));
  thing_value23_set(g, v, l, t, tp_value23_get(tp));
  thing_value24_set(g, v, l, t, tp_value24_get(tp));
  thing_value25_set(g, v, l, t, tp_value25_get(tp));
  thing_value26_set(g, v, l, t, tp_value26_get(tp));
  thing_value27_set(g, v, l, t, tp_value27_get(tp));
  thing_value28_set(g, v, l, t, tp_value28_get(tp));
  thing_jump_distance_set(g, v, l, t, tp_jump_distance_get(tp));
  thing_health_set(g, v, l, t, tp_health_max_get(tp));

  //
  // More consistent for tests to use max values
  //
  if (g_opt_tests) {
    thing_lifespan_set(g, v, l, t, tp_lifespan_max_get(tp));
  } else {
    thing_lifespan_set(g, v, l, t, tp_lifespan_get(tp));
  }

  //
  // Need to update with the new pixel position
  //
  thing_update_pos(g, t);

  //
  // Do adjacent tiles need updating due to the destruction of this tiled thing?
  //
  if (thing_is_tiled(t)) {
    level_tile_update_set(g, v, l, t->at);
  }

  return t;
}
