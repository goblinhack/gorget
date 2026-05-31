//
// Copyright goblinhack@gmail.com
//

#ifndef MY_TESTS_HPP
#define MY_TESTS_HPP

[[nodiscard]] auto tests_init() ->  bool;

// clang-format off
/* begin shell marker1 */
/* shell for i in $(find tests -name "*.cpp" | xargs grep -h "^auto test_load" | sort | awk '{print $2}' | cut -d'(' -f1 ) */
/* shell do */
/* shell echo "auto $i() -> bool;" */
/* shell done */
[[nodiscard]] auto test_load_alloc_free_monsts() ->  bool;
[[nodiscard]] auto test_load_alloc_free_walls() ->  bool;
[[nodiscard]] auto test_load_barrel_explosion() ->  bool;
[[nodiscard]] auto test_load_barrel() ->  bool;
[[nodiscard]] auto test_load_brazier_shove_chasm_twice() ->  bool;
[[nodiscard]] auto test_load_brazier_shove_chasm() ->  bool;
[[nodiscard]] auto test_load_brazier_shove_fail() ->  bool;
[[nodiscard]] auto test_load_brazier_shove_into_mob() ->  bool;
[[nodiscard]] auto test_load_brazier_shove_ok() ->  bool;
[[nodiscard]] auto test_load_bridge_on_fire_over_lava() ->  bool;
[[nodiscard]] auto test_load_bridge_on_fire() ->  bool;
[[nodiscard]] auto test_load_fire_on_water() ->  bool;
[[nodiscard]] auto test_load_fire_over_chasm() ->  bool;
[[nodiscard]] auto test_load_foliage_on_fire() ->  bool;
[[nodiscard]] auto test_load_jump_ok() ->  bool;
[[nodiscard]] auto test_load_jump_truncated() ->  bool;
[[nodiscard]] auto test_load_large_fire_water() ->  bool;
[[nodiscard]] auto test_load_laser_barrel_explosion() ->  bool;
[[nodiscard]] auto test_load_laser_border_turns_to_lava() ->  bool;
[[nodiscard]] auto test_load_laser_door_locked() ->  bool;
[[nodiscard]] auto test_load_laser_door_secret() ->  bool;
[[nodiscard]] auto test_load_laser_door_unlocked() ->  bool;
[[nodiscard]] auto test_load_laser_mob() ->  bool;
[[nodiscard]] auto test_load_laser_monst_chain() ->  bool;
[[nodiscard]] auto test_load_laser_over_grass() ->  bool;
[[nodiscard]] auto test_load_laser_over_water() ->  bool;
[[nodiscard]] auto test_load_laser_rock_turns_to_lava() ->  bool;
[[nodiscard]] auto test_load_laser_teleport() ->  bool;
[[nodiscard]] auto test_load_laser_wall_turns_to_lava() ->  bool;
[[nodiscard]] auto test_load_laser() ->  bool;
[[nodiscard]] auto test_load_mob_shove_into_lava() ->  bool;
[[nodiscard]] auto test_load_mob_water() ->  bool;
[[nodiscard]] auto test_load_mob() ->  bool;
[[nodiscard]] auto test_load_monst_avoids_chasm() ->  bool;
[[nodiscard]] auto test_load_monst_avoids_lava() ->  bool;
[[nodiscard]] auto test_load_monst_avoids_water_usually() ->  bool;
[[nodiscard]] auto test_load_monst_avoids_water() ->  bool;
[[nodiscard]] auto test_load_monst_crosses_chasm() ->  bool;
[[nodiscard]] auto test_load_monst_crosses_lava() ->  bool;
[[nodiscard]] auto test_load_monst_crosses_water() ->  bool;
[[nodiscard]] auto test_load_monst_door_locked() ->  bool;
[[nodiscard]] auto test_load_monst_door_slam_attack() ->  bool;
[[nodiscard]] auto test_load_monst_door_unlocked() ->  bool;
[[nodiscard]] auto test_load_monst_fast() ->  bool;
[[nodiscard]] auto test_load_monst_jump_over_chasm() ->  bool;
[[nodiscard]] auto test_load_monst_maze() ->  bool;
[[nodiscard]] auto test_load_monst_mob_leash() ->  bool;
[[nodiscard]] auto test_load_monst_mobbing() ->  bool;
[[nodiscard]] auto test_load_monst_pass_through_open_door() ->  bool;
[[nodiscard]] auto test_load_monst_pass_through_walls() ->  bool;
[[nodiscard]] auto test_load_monst_secret_door() ->  bool;
[[nodiscard]] auto test_load_monst_short_jump_around_chasm() ->  bool;
[[nodiscard]] auto test_load_monst_slow() ->  bool;
[[nodiscard]] auto test_load_monst_vision_direction() ->  bool;
[[nodiscard]] auto test_load_move_ok() ->  bool;
[[nodiscard]] auto test_load_no_change() ->  bool;
[[nodiscard]] auto test_load_path_astar() ->  bool;
[[nodiscard]] auto test_load_path_dmap_reverse() ->  bool;
[[nodiscard]] auto test_load_path_dmap() ->  bool;
[[nodiscard]] auto test_load_player_fall_chasm_into_lava() ->  bool;
[[nodiscard]] auto test_load_player_fall_chasm_twice_into_lava() ->  bool;
[[nodiscard]] auto test_load_player_fall_chasm_twice() ->  bool;
[[nodiscard]] auto test_load_player_fall_while_on_fire() ->  bool;
[[nodiscard]] auto test_load_player_hiding_behind_bush() ->  bool;
[[nodiscard]] auto test_load_player_hiding_in_bush() ->  bool;
[[nodiscard]] auto test_load_player_in_steam() ->  bool;
[[nodiscard]] auto test_load_player_lava() ->  bool;
[[nodiscard]] auto test_load_player_on_fire_move_into_water() ->  bool;
[[nodiscard]] auto test_load_player_on_fire() ->  bool;
[[nodiscard]] auto test_load_projectile_barrel_explosion() ->  bool;
[[nodiscard]] auto test_load_projectile_border_turns_to_lava() ->  bool;
[[nodiscard]] auto test_load_projectile_discharge() ->  bool;
[[nodiscard]] auto test_load_projectile_door_locked() ->  bool;
[[nodiscard]] auto test_load_projectile_door_secret() ->  bool;
[[nodiscard]] auto test_load_projectile_door_unlocked() ->  bool;
[[nodiscard]] auto test_load_projectile_mob() ->  bool;
[[nodiscard]] auto test_load_projectile_over_grass() ->  bool;
[[nodiscard]] auto test_load_projectile_over_water() ->  bool;
[[nodiscard]] auto test_load_projectile_rock_turns_to_lava() ->  bool;
[[nodiscard]] auto test_load_projectile_teleport() ->  bool;
[[nodiscard]] auto test_load_projectile_wall_turns_to_lava() ->  bool;
[[nodiscard]] auto test_load_projectile_wield() ->  bool;
[[nodiscard]] auto test_load_projectile() ->  bool;
[[nodiscard]] auto test_load_save_load() ->  bool;
[[nodiscard]] auto test_load_slots() ->  bool;
[[nodiscard]] auto test_load_teleport_chasm() ->  bool;
[[nodiscard]] auto test_load_teleport_shove_barrel() ->  bool;
[[nodiscard]] auto test_load_teleport_shove_brazier() ->  bool;
[[nodiscard]] auto test_load_teleport_shove_mob() ->  bool;
[[nodiscard]] auto test_load_teleport() ->  bool;
[[nodiscard]] auto test_load_trampled_grass() ->  bool;
[[nodiscard]] auto test_load_wall() ->  bool;
  /* end shell marker1 */
#endif // MY_TESTS_HPP
