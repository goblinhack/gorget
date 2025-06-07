//
// Copyright goblinhack@gmail.com
//

bool tests_init(void);

/* begin shell marker1 */
/* shell for i in $(find . -name "*.cpp" | xargs grep -h "^bool test_load" | awk '{print $2}' | cut -d'(' -f1 ) */
/* shell do */
/* shell echo "bool $i();" */
/* shell done */
bool test_load_move();
/* end shell marker1 */
