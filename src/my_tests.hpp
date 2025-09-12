//
// Copyright goblinhack@gmail.com
//

bool tests_init(void);

// clang-format off
/* begin shell marker1 */
/* shell for i in $(find . -name "*.cpp" | xargs grep -h "^bool test_load" | sort | awk '{print $2}' | cut -d'(' -f1 ) */
/* shell do */
/* shell echo "bool $i();" */
/* shell done */
bool test_load_barrel_explosion();
bool test_load_barrel();
bool test_load_brazier_shove_chasm();
bool test_load_brazier_shove_fail();
bool test_load_brazier_shove_into_mob();
bool test_load_brazier_shove_ok();
bool test_load_bridge_on_fire_over_lava();
bool test_load_bridge_on_fire();
bool test_load_door_type_secret();
bool test_load_fire_on_water();
bool test_load_fire_over_chasm();
bool test_load_foliage_on_fire();
bool test_load_jump_ok();
bool test_load_jump_truncated();
bool test_load_large_fire_water();
bool test_load_mob_lava();
bool test_load_mob_water();
bool test_load_mob();
bool test_load_move_ok();
bool test_load_open_door();
bool test_load_player_fall_chasm_into_lava();
bool test_load_player_lava();
bool test_load_save_load();
bool test_load_teleport();
bool test_load_trampled_grass();
bool test_load_wall();
  /* end shell marker1 */
