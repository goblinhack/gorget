//
// Copyright goblinhack@gmail.com
//

#ifndef MY_TESTS_HPP_
#define MY_TESTS_HPP_

auto tests_init() -> bool;

// clang-format off
/* begin shell marker1 */
/* shell for i in $(find tests -name "*.cpp" | xargs grep -h "^auto test_load" | sort | awk '{print $2}' | cut -d'(' -f1 ) */
/* shell do */
/* shell echo "auto $i() -> bool;" */
/* shell done */
bool test_load_alloc_free_monsts();
bool test_load_alloc_free_walls();
bool test_load_barrel_explosion();
bool test_load_barrel();
bool test_load_brazier_shove_chasm_twice();
bool test_load_brazier_shove_chasm();
bool test_load_brazier_shove_fail();
bool test_load_brazier_shove_into_mob();
bool test_load_brazier_shove_ok();
bool test_load_bridge_on_fire_over_lava();
bool test_load_bridge_on_fire();
bool test_load_door_secret();
bool test_load_fire_on_water();
bool test_load_fire_over_chasm();
bool test_load_foliage_on_fire();
bool test_load_jump_ok();
bool test_load_jump_truncated();
bool test_load_large_fire_water();
bool test_load_mob_shove_into_lava();
bool test_load_mob_water();
bool test_load_mob();
bool test_load_move_ok();
bool test_load_no_change();
bool test_load_open_locked_door_fail();
bool test_load_open_locked_door_success();
bool test_load_open_unlocked_door();
bool test_load_path_astar();
bool test_load_path_dmap_reverse();
bool test_load_path_dmap();
bool test_load_player_fall_chasm_into_lava();
bool test_load_player_fall_chasm_twice_into_lava();
bool test_load_player_fall_chasm_twice();
bool test_load_player_fall_while_on_fire();
bool test_load_player_in_steam();
bool test_load_player_lava();
bool test_load_player_on_fire_move_into_water();
bool test_load_player_on_fire();
bool test_load_projectile_barrel_explosion();
bool test_load_projectile_border_turns_to_lava();
bool test_load_projectile_locked_door();
bool test_load_projectile_mob();
bool test_load_projectile_over_water();
bool test_load_projectile_rock_turns_to_lava();
bool test_load_projectile_secret_door();
bool test_load_projectile_unlocked_door();
bool test_load_projectile_wall_turns_to_lava();
bool test_load_projectile();
bool test_load_save_load();
bool test_load_slots();
bool test_load_teleport_chasm();
bool test_load_teleport_shove_barrel();
bool test_load_teleport_shove_brazier();
bool test_load_teleport_shove_mob();
bool test_load_teleport();
bool test_load_trampled_grass();
bool test_load_wall();
  /* end shell marker1 */
#endif // _MY_TESTS_HPP_
