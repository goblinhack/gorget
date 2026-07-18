//
// Copyright goblinhack@gmail.com
//

#ifndef MY_TESTS_HPP
#define MY_TESTS_HPP

[[nodiscard]] auto tests_init() -> bool;

// clang-format off
/* begin shell marker1 */
/* shell for i in $(find tests -name "*.cpp" | xargs grep -h "^..nodiscard.. auto test_load" | sort | awk '{print $3}' | cut -d'(' -f1 ) */
/* shell do */
/* shell echo "auto $i() -> bool;" */
/* shell done */
auto test_load_alloc_free_monsts() -> bool;
auto test_load_alloc_free_walls() -> bool;
auto test_load_barrel_explosion() -> bool;
auto test_load_barrel() -> bool;
auto test_load_beam_weapon_barrel_explosion() -> bool;
auto test_load_beam_weapon_border_turns_to_lava() -> bool;
auto test_load_beam_weapon_door_locked() -> bool;
auto test_load_beam_weapon_door_secret() -> bool;
auto test_load_beam_weapon_door_unlocked() -> bool;
auto test_load_beam_weapon_mob() -> bool;
auto test_load_beam_weapon_monst_chain() -> bool;
auto test_load_beam_weapon_over_grass() -> bool;
auto test_load_beam_weapon_over_water() -> bool;
auto test_load_beam_weapon_rock_turns_to_lava() -> bool;
auto test_load_beam_weapon_teleport() -> bool;
auto test_load_beam_weapon_wall_turns_to_lava() -> bool;
auto test_load_beam_weapon() -> bool;
auto test_load_brazier_shove_chasm_twice() -> bool;
auto test_load_brazier_shove_chasm() -> bool;
auto test_load_brazier_shove_fail() -> bool;
auto test_load_brazier_shove_into_mob() -> bool;
auto test_load_brazier_shove_ok() -> bool;
auto test_load_bridge_on_fire_over_lava() -> bool;
auto test_load_bridge_on_fire() -> bool;
auto test_load_drop_items() -> bool;
auto test_load_drop_then_recollect_items() -> bool;
auto test_load_fire_on_water() -> bool;
auto test_load_fire_over_chasm() -> bool;
auto test_load_foliage_on_fire() -> bool;
auto test_load_items_drift_away() -> bool;
auto test_load_jump_ok() -> bool;
auto test_load_jump_truncated() -> bool;
auto test_load_large_fire_water() -> bool;
auto test_load_mob_shove_into_lava() -> bool;
auto test_load_mob_water() -> bool;
auto test_load_mob() -> bool;
auto test_load_monst_avoids_chasm() -> bool;
auto test_load_monst_avoids_lava() -> bool;
auto test_load_monst_avoids_player() -> bool;
auto test_load_monst_avoids_water_usually() -> bool;
auto test_load_monst_avoids_water() -> bool;
auto test_load_monst_blasts_player() -> bool;
auto test_load_monst_crosses_chasm() -> bool;
auto test_load_monst_crosses_lava() -> bool;
auto test_load_monst_crosses_water() -> bool;
auto test_load_monst_door_locked() -> bool;
auto test_load_monst_door_slam_attack() -> bool;
auto test_load_monst_door_unlocked() -> bool;
auto test_load_monst_fast_attack_multi() -> bool;
auto test_load_monst_fast() -> bool;
auto test_load_monst_jumping_over_chasm() -> bool;
auto test_load_monst_maze() -> bool;
auto test_load_monst_mob_leash() -> bool;
auto test_load_monst_mobbing() -> bool;
auto test_load_monst_pass_through_open_door() -> bool;
auto test_load_monst_pass_through_walls() -> bool;
auto test_load_monst_secret_door() -> bool;
auto test_load_monst_short_jump_around_chasm() -> bool;
auto test_load_monst_slow_attack_single() -> bool;
auto test_load_monst_slow() -> bool;
auto test_load_monst_vision_direction() -> bool;
auto test_load_no_change() -> bool;
auto test_load_path_astar() -> bool;
auto test_load_path_dmap_reverse() -> bool;
auto test_load_path_dmap() -> bool;
auto test_load_player_did_not_trigger() -> bool;
auto test_load_player_engulfed_multiple() -> bool;
auto test_load_player_engulfed() -> bool;
auto test_load_player_fall_chasm_into_lava() -> bool;
auto test_load_player_fall_chasm_twice_into_lava() -> bool;
auto test_load_player_fall_chasm_twice() -> bool;
auto test_load_player_fall_while_on_fire() -> bool;
auto test_load_player_hiding_behind_foliage() -> bool;
auto test_load_player_hiding_in_foliage() -> bool;
auto test_load_player_in_steam() -> bool;
auto test_load_player_lava() -> bool;
auto test_load_player_melee() -> bool;
auto test_load_player_move_ok() -> bool;
auto test_load_player_moving_in_foliage() -> bool;
auto test_load_player_on_fire_move_into_water() -> bool;
auto test_load_player_on_fire() -> bool;
auto test_load_player_triggered() -> bool;
auto test_load_potion_healing() -> bool;
auto test_load_potion_stealth() -> bool;
auto test_load_potion_tireless() -> bool;
auto test_load_projectile_barrel_explosion() -> bool;
auto test_load_projectile_border_turns_to_lava() -> bool;
auto test_load_projectile_door_locked() -> bool;
auto test_load_projectile_door_secret() -> bool;
auto test_load_projectile_door_unlocked() -> bool;
auto test_load_projectile_mob() -> bool;
auto test_load_projectile_over_grass() -> bool;
auto test_load_projectile_over_water() -> bool;
auto test_load_projectile_rock_turns_to_lava() -> bool;
auto test_load_projectile_teleport() -> bool;
auto test_load_projectile_wall_turns_to_lava() -> bool;
auto test_load_projectile() -> bool;
auto test_load_save_load() -> bool;
auto test_load_slots() -> bool;
auto test_load_teleport_chasm() -> bool;
auto test_load_teleport_shove_barrel() -> bool;
auto test_load_teleport_shove_brazier() -> bool;
auto test_load_teleport_shove_mob() -> bool;
auto test_load_teleport() -> bool;
auto test_load_throw_item_at_monst() -> bool;
auto test_load_throw_item_chasm() -> bool;
auto test_load_throw_items() -> bool;
auto test_load_throw_potion_healing_into_lava() -> bool;
auto test_load_throw_potion_healing() -> bool;
auto test_load_throw_potion_incin_chain_explosion() -> bool;
auto test_load_throw_potion_incin_chasm() -> bool;
auto test_load_throw_potion_incin_into_water() -> bool;
auto test_load_throw_potion_incin() -> bool;
auto test_load_trampled_grass() -> bool;
auto test_load_wall() -> bool;
auto test_load_weapon_discharge() -> bool;
auto test_load_weapon_wield_unwield() -> bool;
  /* end shell marker1 */

#endif // MY_TESTS_HPP
