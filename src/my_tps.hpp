//
// Copyright Neil McGill, goblinhack@gmail.com
//

/* clang-format off */
bool templates_init(void);

/* begin shell marker1 */
/* shell for i in $(find . -name "*.cpp" | xargs grep -h "^bool tp_load" | awk '{print $2}' | cut -d'(' -f1 ) */
/* shell do */
/* shell echo "bool $i();" */
/* shell done */
bool tp_load_player();
bool tp_load_cursor_path();
bool tp_load_cursor_at();
bool tp_load_key();
bool tp_load_exit();
bool tp_load_door();
bool tp_load_wall();
bool tp_load_floor();
/* end shell marker1 */
/* clang-format on */
