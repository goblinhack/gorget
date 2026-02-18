//
// Copyright goblinhack@gmail.com
//

#ifndef _MY_TPS_HPP_
#define _MY_TPS_HPP_

bool templates_init();

// clang-format off
/* begin shell marker1 */
/* shell for i in $(find . -name "*.cpp" | xargs grep -h "^bool tp_load" | sort | awk '{print $2}' | cut -d'(' -f1 ) */
/* shell do */
/* shell echo "bool $i();" */
/* shell done */
bool tp_load_barrel();
bool tp_load_border();
bool tp_load_brazier();
bool tp_load_bridge();
bool tp_load_chasm();
bool tp_load_corridor();
bool tp_load_cursor_at();
bool tp_load_cursor_path();
bool tp_load_deep_water();
bool tp_load_dirt();
bool tp_load_door_locked();
bool tp_load_door_secret();
bool tp_load_door_unlocked();
bool tp_load_entrance();
bool tp_load_exit();
bool tp_load_explosion();
bool tp_load_fire();
bool tp_load_fireball();
bool tp_load_floor();
bool tp_load_foliage();
bool tp_load_ghost_mob();
bool tp_load_ghost();
bool tp_load_glorp();
bool tp_load_grass();
bool tp_load_key();
bool tp_load_kobalos_mob();
bool tp_load_kobalos();
bool tp_load_lava();
bool tp_load_level_across();
bool tp_load_level_curr();
bool tp_load_level_down();
bool tp_load_level_final();
bool tp_load_level_next();
bool tp_load_level_not_visited();
bool tp_load_level_visited();
bool tp_load_mantisman();
bool tp_load_pillar();
bool tp_load_player();
bool tp_load_potion();
bool tp_load_rock();
bool tp_load_smoke();
bool tp_load_steam();
bool tp_load_teleport();
bool tp_load_trap();
bool tp_load_treasure();
bool tp_load_wall();
bool tp_load_water();
  /* end shell marker1 */

#endif
