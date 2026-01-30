//
// Copyright goblinhack@gmail.com
//

#pragma once
#ifndef _MY_TESTS_HPP_
#define _MY_TESTS_HPP_

extern bool tests_init(void);

// clang-format off
/* begin shell marker1 */
/* shell for i in $(find . -name "*.cpp" | xargs grep -h "^bool test_load" | sort | awk '{print $2}' | cut -d'(' -f1 ) */
/* shell do */
/* shell echo "extern bool $i();" */
/* shell done */
extern bool test_load_alloc_free_monsts();
extern bool test_load_alloc_free_walls();
extern bool test_load_barrel_explosion();
extern bool test_load_barrel();
extern bool test_load_brazier_shove_chasm_twice();
extern bool test_load_brazier_shove_chasm();
extern bool test_load_brazier_shove_fail();
extern bool test_load_brazier_shove_into_mob();
extern bool test_load_brazier_shove_ok();
extern bool test_load_bridge_on_fire_over_lava();
extern bool test_load_bridge_on_fire();
extern bool test_load_door_secret();
extern bool test_load_fire_on_water();
extern bool test_load_fire_over_chasm();
extern bool test_load_foliage_on_fire();
extern bool test_load_jump_ok();
extern bool test_load_jump_truncated();
extern bool test_load_large_fire_water();
extern bool test_load_mob_shove_into_lava();
extern bool test_load_mob_water();
extern bool test_load_mob();
extern bool test_load_move_ok();
extern bool test_load_no_change();
extern bool test_load_open_locked_door_fail();
extern bool test_load_open_locked_door_success();
extern bool test_load_open_unlocked_door();
extern bool test_load_player_fall_chasm_into_lava();
extern bool test_load_player_fall_chasm_twice_into_lava();
extern bool test_load_player_fall_chasm_twice();
extern bool test_load_player_fall_while_on_fire();
extern bool test_load_player_in_steam();
extern bool test_load_player_lava();
extern bool test_load_player_on_fire_move_into_water();
extern bool test_load_player_on_fire();
extern bool test_load_projectile_barrel_explosion();
extern bool test_load_projectile_border_turns_to_lava();
extern bool test_load_projectile_locked_door();
extern bool test_load_projectile_mob();
extern bool test_load_projectile_over_water();
extern bool test_load_projectile_rock_turns_to_lava();
extern bool test_load_projectile_secret_door();
extern bool test_load_projectile_unlocked_door();
extern bool test_load_projectile_wall_turns_to_lava();
extern bool test_load_projectile();
extern bool test_load_save_load();
extern bool test_load_teleport_chasm();
extern bool test_load_teleport_shove_barrel();
extern bool test_load_teleport_shove_brazier();
extern bool test_load_teleport_shove_mob();
extern bool test_load_teleport();
extern bool test_load_trampled_grass();
extern bool test_load_wall();
  /* end shell marker1 */
#endif // _MY_TESTS_HPP_
