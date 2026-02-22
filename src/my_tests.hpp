//
// Copyright goblinhack@gmail.com
//

#ifndef MY_TESTS_HPP_
#define MY_TESTS_HPP_

extern auto tests_init() -> bool;

// clang-format off
/* begin shell marker1 */
/* shell for i in $(find . -name "*.cpp" | xargs grep -h "^bool test_load" | sort | awk '{print $2}' | cut -d'(' -f1 ) */
/* shell do */
/* shell echo "extern bool $i();" */
/* shell done */
extern auto test_load_alloc_free_monsts() -> bool;
extern auto test_load_alloc_free_walls() -> bool;
extern auto test_load_barrel_explosion() -> bool;
extern auto test_load_barrel() -> bool;
extern auto test_load_brazier_shove_chasm_twice() -> bool;
extern auto test_load_brazier_shove_chasm() -> bool;
extern auto test_load_brazier_shove_fail() -> bool;
extern auto test_load_brazier_shove_into_mob() -> bool;
extern auto test_load_brazier_shove_ok() -> bool;
extern auto test_load_bridge_on_fire_over_lava() -> bool;
extern auto test_load_bridge_on_fire() -> bool;
extern auto test_load_door_secret() -> bool;
extern auto test_load_fire_on_water() -> bool;
extern auto test_load_fire_over_chasm() -> bool;
extern auto test_load_foliage_on_fire() -> bool;
extern auto test_load_jump_ok() -> bool;
extern auto test_load_jump_truncated() -> bool;
extern auto test_load_large_fire_water() -> bool;
extern auto test_load_mob_shove_into_lava() -> bool;
extern auto test_load_mob_water() -> bool;
extern auto test_load_mob() -> bool;
extern auto test_load_move_ok() -> bool;
extern auto test_load_no_change() -> bool;
extern auto test_load_open_locked_door_fail() -> bool;
extern auto test_load_open_locked_door_success() -> bool;
extern auto test_load_open_unlocked_door() -> bool;
extern auto test_load_path_astar() -> bool;
extern auto test_load_path_dmap_reverse() -> bool;
extern auto test_load_path_dmap() -> bool;
extern auto test_load_player_fall_chasm_into_lava() -> bool;
extern auto test_load_player_fall_chasm_twice_into_lava() -> bool;
extern auto test_load_player_fall_chasm_twice() -> bool;
extern auto test_load_player_fall_while_on_fire() -> bool;
extern auto test_load_player_in_steam() -> bool;
extern auto test_load_player_lava() -> bool;
extern auto test_load_player_on_fire_move_into_water() -> bool;
extern auto test_load_player_on_fire() -> bool;
extern auto test_load_projectile_barrel_explosion() -> bool;
extern auto test_load_projectile_border_turns_to_lava() -> bool;
extern auto test_load_projectile_locked_door() -> bool;
extern auto test_load_projectile_mob() -> bool;
extern auto test_load_projectile_over_water() -> bool;
extern auto test_load_projectile_rock_turns_to_lava() -> bool;
extern auto test_load_projectile_secret_door() -> bool;
extern auto test_load_projectile_unlocked_door() -> bool;
extern auto test_load_projectile_wall_turns_to_lava() -> bool;
extern auto test_load_projectile() -> bool;
extern auto test_load_save_load() -> bool;
extern auto test_load_slots() -> bool;
extern auto test_load_teleport_chasm() -> bool;
extern auto test_load_teleport_shove_barrel() -> bool;
extern auto test_load_teleport_shove_brazier() -> bool;
extern auto test_load_teleport_shove_mob() -> bool;
extern auto test_load_teleport() -> bool;
extern auto test_load_trampled_grass() -> bool;
extern auto test_load_wall() -> bool;
  /* end shell marker1 */
#endif // _MY_TESTS_HPP_
