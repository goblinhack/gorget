//
// Copyright goblinhack@gmail.com
//

bool tests_init(void);

/* begin shell marker1 */
/* shell for i in $(find . -name "*.cpp" | xargs grep -h "^bool test_load" | awk '{print $2}' | cut -d'(' -f1 ) */
/* shell do */
/* shell echo "bool $i();" */
/* shell done */
bool test_load_collision_mob();
bool test_load_collision_barrel();
bool test_load_collision_wall();
bool test_load_collision_mob_lava();
bool test_load_collision_brazier_shove_ok();
bool test_load_collision_grass();
bool test_load_collision_player_lava();
bool test_load_move_ok();
bool test_load_collision_brazier_shove_into_mob();
bool test_load_collision_brazier_shove_fail();
/* end shell marker1 */
