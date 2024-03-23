//
// Copyright Neil McGill, goblinhack@gmail.com
//

bool templates_init(void);

/* begin shell marker1 */
/* shell for i in $(find . -name "*.cpp" | xargs grep -h "^bool tp_load" | awk '{print $2}' | cut -d'(' -f1 ) */
/* shell do */
/* shell echo "bool $i();" */
/* shell done */
bool tp_load_cursor();
bool tp_load_player();
bool tp_load_dungeon_door();
bool tp_load_dungeon_floor();
bool tp_load_dungeon_entrance();
bool tp_load_key();
bool tp_load_dungeon_exit();
bool tp_load_dungeon_wall();
/* end shell marker1 */
