//
// Copyright goblinhack@gmail.com
//

bool templates_init(void);

/* begin shell marker1 */
/* shell for i in $(find . -name "*.cpp" | xargs grep -h "^bool tp_load" | awk '{print $2}' | cut -d'(' -f1 ) */
/* shell do */
/* shell echo "bool $i();" */
/* shell done */
bool tp_load_exit();
bool tp_load_chasm();
bool tp_load_floor();
bool tp_load_foliage();
bool tp_load_wall();
bool tp_load_door();
bool tp_load_water();
bool tp_load_bridge();
bool tp_load_entrance();
bool tp_load_rock();
bool tp_load_lava();
bool tp_load_key();
bool tp_load_corridor();
bool tp_load_dirt();
bool tp_load_deep_water();
bool tp_load_cursor_path();
bool tp_load_cursor_at();
bool tp_load_goblin();
bool tp_load_ghost();
bool tp_load_level_curr();
bool tp_load_level_visited();
bool tp_load_level_across();
bool tp_load_level_next();
bool tp_load_level_not_visited();
bool tp_load_level_final();
bool tp_load_level_down();
bool tp_load_treasure();
bool tp_load_potion();
bool tp_load_ghost_mob();
bool tp_load_goblin_mob();
bool tp_load_player();
/* end shell marker1 */
