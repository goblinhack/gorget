//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_tests.hpp"

[[nodiscard]] auto tests_init() -> bool
{
  TRACE();

  // clang-format off
  /* begin shell marker1 */
  /* shell for i in $(find tests -name "*.cpp" | xargs grep -h "^..nodiscard.. auto test_load" | sort | awk '{print $3}' | cut -d'(' -f1 ) */
  /* shell do */
  /* shell echo "  if (!$i()) { return false; }" */
  /* shell done */
  if (!test_load_alloc_free_monsts()) { return false; }
  if (!test_load_alloc_free_walls()) { return false; }
  if (!test_load_barrel_explosion()) { return false; }
  if (!test_load_barrel()) { return false; }
  if (!test_load_beam_weapon_barrel_explosion()) { return false; }
  if (!test_load_beam_weapon_border_turns_to_lava()) { return false; }
  if (!test_load_beam_weapon_door_locked()) { return false; }
  if (!test_load_beam_weapon_door_secret()) { return false; }
  if (!test_load_beam_weapon_door_unlocked()) { return false; }
  if (!test_load_beam_weapon_mob()) { return false; }
  if (!test_load_beam_weapon_monst_chain()) { return false; }
  if (!test_load_beam_weapon_over_grass()) { return false; }
  if (!test_load_beam_weapon_over_water()) { return false; }
  if (!test_load_beam_weapon_rock_turns_to_lava()) { return false; }
  if (!test_load_beam_weapon_teleport()) { return false; }
  if (!test_load_beam_weapon_wall_turns_to_lava()) { return false; }
  if (!test_load_beam_weapon()) { return false; }
  if (!test_load_brazier_shove_chasm_twice()) { return false; }
  if (!test_load_brazier_shove_chasm()) { return false; }
  if (!test_load_brazier_shove_fail()) { return false; }
  if (!test_load_brazier_shove_into_mob()) { return false; }
  if (!test_load_brazier_shove_ok()) { return false; }
  if (!test_load_bridge_on_fire_over_lava()) { return false; }
  if (!test_load_bridge_on_fire()) { return false; }
  if (!test_load_drop_items()) { return false; }
  if (!test_load_drop_then_recollect_items()) { return false; }
  if (!test_load_fire_on_water()) { return false; }
  if (!test_load_fire_over_chasm()) { return false; }
  if (!test_load_foliage_on_fire()) { return false; }
  if (!test_load_jump_ok()) { return false; }
  if (!test_load_jump_truncated()) { return false; }
  if (!test_load_large_fire_water()) { return false; }
  if (!test_load_mob_shove_into_lava()) { return false; }
  if (!test_load_mob_water()) { return false; }
  if (!test_load_mob()) { return false; }
  if (!test_load_monst_avoids_chasm()) { return false; }
  if (!test_load_monst_avoids_lava()) { return false; }
  if (!test_load_monst_avoids_water_usually()) { return false; }
  if (!test_load_monst_avoids_water()) { return false; }
  if (!test_load_monst_crosses_chasm()) { return false; }
  if (!test_load_monst_crosses_lava()) { return false; }
  if (!test_load_monst_crosses_water()) { return false; }
  if (!test_load_monst_door_locked()) { return false; }
  if (!test_load_monst_door_slam_attack()) { return false; }
  if (!test_load_monst_door_unlocked()) { return false; }
  if (!test_load_monst_fast_attack_multi()) { return false; }
  if (!test_load_monst_fast()) { return false; }
  if (!test_load_monst_jumping_over_chasm()) { return false; }
  if (!test_load_monst_maze()) { return false; }
  if (!test_load_monst_mob_leash()) { return false; }
  if (!test_load_monst_mobbing()) { return false; }
  if (!test_load_monst_pass_through_open_door()) { return false; }
  if (!test_load_monst_pass_through_walls()) { return false; }
  if (!test_load_monst_secret_door()) { return false; }
  if (!test_load_monst_short_jump_around_chasm()) { return false; }
  if (!test_load_monst_slow_attack_single()) { return false; }
  if (!test_load_monst_slow()) { return false; }
  if (!test_load_monst_vision_direction()) { return false; }
  if (!test_load_move_ok()) { return false; }
  if (!test_load_no_change()) { return false; }
  if (!test_load_path_astar()) { return false; }
  if (!test_load_path_dmap_reverse()) { return false; }
  if (!test_load_path_dmap()) { return false; }
  if (!test_load_player_fall_chasm_into_lava()) { return false; }
  if (!test_load_player_fall_chasm_twice_into_lava()) { return false; }
  if (!test_load_player_fall_chasm_twice()) { return false; }
  if (!test_load_player_fall_while_on_fire()) { return false; }
  if (!test_load_player_hiding_behind_bush()) { return false; }
  if (!test_load_player_hiding_in_bush()) { return false; }
  if (!test_load_player_in_steam()) { return false; }
  if (!test_load_player_lava()) { return false; }
  if (!test_load_player_on_fire_move_into_water()) { return false; }
  if (!test_load_player_on_fire()) { return false; }
  if (!test_load_projectile_barrel_explosion()) { return false; }
  if (!test_load_projectile_border_turns_to_lava()) { return false; }
  if (!test_load_projectile_door_locked()) { return false; }
  if (!test_load_projectile_door_secret()) { return false; }
  if (!test_load_projectile_door_unlocked()) { return false; }
  if (!test_load_projectile_mob()) { return false; }
  if (!test_load_projectile_over_grass()) { return false; }
  if (!test_load_projectile_over_water()) { return false; }
  if (!test_load_projectile_rock_turns_to_lava()) { return false; }
  if (!test_load_projectile_teleport()) { return false; }
  if (!test_load_projectile_wall_turns_to_lava()) { return false; }
  if (!test_load_projectile()) { return false; }
  if (!test_load_save_load()) { return false; }
  if (!test_load_slots()) { return false; }
  if (!test_load_teleport_chasm()) { return false; }
  if (!test_load_teleport_shove_barrel()) { return false; }
  if (!test_load_teleport_shove_brazier()) { return false; }
  if (!test_load_teleport_shove_mob()) { return false; }
  if (!test_load_teleport()) { return false; }
  if (!test_load_throw_item_chasm()) { return false; }
  if (!test_load_throw_items()) { return false; }
  if (!test_load_throw_potion_healing_into_lava()) { return false; }
  if (!test_load_throw_potion_healing()) { return false; }
  if (!test_load_throw_potion_incin_chain_explosion()) { return false; }
  if (!test_load_throw_potion_incin_chasm()) { return false; }
  if (!test_load_throw_potion_incin_into_water()) { return false; }
  if (!test_load_throw_potion_incin()) { return false; }
  if (!test_load_trampled_grass()) { return false; }
  if (!test_load_wall()) { return false; }
  if (!test_load_weapon_discharge()) { return false; }
  if (!test_load_weapon_wield_unwield()) { return false; }
  /* end shell marker1 */
  // clang-format on

  return true;
}
