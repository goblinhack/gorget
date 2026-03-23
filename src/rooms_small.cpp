//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_charmap.hpp"
#include "my_level.hpp"

//
// 1000 rooms of type 'small' from seed 'maniac'
//
void rooms_small(Gamep g)
{
  TRACE();

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^    ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "^....^",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^     ",
           /* line */ (const char *) "   .......^",
           /* line */ (const char *) "^...g.|.   ",
           /* line */ (const char *) "   .....   ",
           /* line */ (const char *) "     .     ",
           /* line */ (const char *) "     ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^    ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "^.....^",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "      ^       ",
           /* line */ (const char *) "^............^",
           /* line */ (const char *) "     .....    ",
           /* line */ (const char *) "     .....    ",
           /* line */ (const char *) "      .       ",
           /* line */ (const char *) "      ^       ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^  ",
           /* line */ (const char *) "^... ",
           /* line */ (const char *) " .|.^",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) "  ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^    ",
           /* line */ (const char *) "  .    ",
           /* line */ (const char *) "  .    ",
           /* line */ (const char *) "  .    ",
           /* line */ (const char *) "  ...  ",
           /* line */ (const char *) "  ...  ",
           /* line */ (const char *) "^..m.  ",
           /* line */ (const char *) "  ....^",
           /* line */ (const char *) "  ...  ",
           /* line */ (const char *) "   .   ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^    ",
           /* line */ (const char *) "   .    ",
           /* line */ (const char *) "  ..... ",
           /* line */ (const char *) "  ..m.. ",
           /* line */ (const char *) "^......^",
           /* line */ (const char *) "  .g.x. ",
           /* line */ (const char *) "  ..... ",
           /* line */ (const char *) "  ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^   ",
           /* line */ (const char *) "  .   ",
           /* line */ (const char *) "  .   ",
           /* line */ (const char *) "  ... ",
           /* line */ (const char *) "  ... ",
           /* line */ (const char *) "^..|. ",
           /* line */ (const char *) "  ...^",
           /* line */ (const char *) "  ... ",
           /* line */ (const char *) "   ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^  ",
           /* line */ (const char *) "    .  ",
           /* line */ (const char *) "    .  ",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) "   .|.^",
           /* line */ (const char *) "   ... ",
           /* line */ (const char *) "   .   ",
           /* line */ (const char *) "   .   ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^  ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " .m.^",
           /* line */ (const char *) "^... ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^     ",
           /* line */ (const char *) "  .     ",
           /* line */ (const char *) "  .     ",
           /* line */ (const char *) " ....   ",
           /* line */ (const char *) " ......^",
           /* line */ (const char *) "^....   ",
           /* line */ (const char *) " ....   ",
           /* line */ (const char *) "  .     ",
           /* line */ (const char *) "  .     ",
           /* line */ (const char *) "  ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^    ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "^.g... ",
           /* line */ (const char *) " ...g.^",
           /* line */ (const char *) "```... ",
           /* line */ (const char *) "````.. ",
           /* line */ (const char *) "m`  ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^     ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "^..|..^",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^     ",
           /* line */ (const char *) "     .     ",
           /* line */ (const char *) "    ......^",
           /* line */ (const char *) "    ..m..  ",
           /* line */ (const char *) "^........  ",
           /* line */ (const char *) "    .....  ",
           /* line */ (const char *) "    ^      ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^  ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " ...g.^",
           /* line */ (const char *) "^.x... ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^  ",
           /* line */ (const char *) "  .... ",
           /* line */ (const char *) "  .... ",
           /* line */ (const char *) "^.....^",
           /* line */ (const char *) "  .... ",
           /* line */ (const char *) "  .... ",
           /* line */ (const char *) "    ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^  ",
           /* line */ (const char *) "   .  ",
           /* line */ (const char *) "^.... ",
           /* line */ (const char *) "  .g. ",
           /* line */ (const char *) "  ... ",
           /* line */ (const char *) "  .|.^",
           /* line */ (const char *) "  ... ",
           /* line */ (const char *) "  .   ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^   ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "^.x.m.^",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^       ",
           /* line */ (const char *) " .....    ",
           /* line */ (const char *) " .|.|.    ",
           /* line */ (const char *) " ........^",
           /* line */ (const char *) "^.|.|.    ",
           /* line */ (const char *) " .....    ",
           /* line */ (const char *) "    .     ",
           /* line */ (const char *) "    .     ",
           /* line */ (const char *) "    ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^   ",
           /* line */ (const char *) " ....^",
           /* line */ (const char *) "^.... ",
           /* line */ (const char *) " ..x. ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "   ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^  ",
           /* line */ (const char *) "^.... ",
           /* line */ (const char *) " .m..^",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "   ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^  ",
           /* line */ (const char *) "    .  ",
           /* line */ (const char *) "^.....^",
           /* line */ (const char *) "  ..|. ",
           /* line */ (const char *) "  .... ",
           /* line */ (const char *) "    ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^       ",
           /* line */ (const char *) "  .       ",
           /* line */ (const char *) "^........^",
           /* line */ (const char *) "  .|..    ",
           /* line */ (const char *) "  ....    ",
           /* line */ (const char *) "   .      ",
           /* line */ (const char *) "   ^      ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^    ",
           /* line */ (const char *) "^...   ",
           /* line */ (const char *) " .x...^",
           /* line */ (const char *) " ...   ",
           /* line */ (const char *) "  ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^   ",
           /* line */ (const char *) "^.... ",
           /* line */ (const char *) " ..g. ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) " .g..^",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "   ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^    ",
           /* line */ (const char *) "   .    ",
           /* line */ (const char *) "   .    ",
           /* line */ (const char *) "^.....  ",
           /* line */ (const char *) "  .m...^",
           /* line */ (const char *) "  ....  ",
           /* line */ (const char *) "   ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^  ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) "^.m.^",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^   ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) "^.g.^",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) "  ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^     ",
           /* line */ (const char *) "^......  ",
           /* line */ (const char *) "   ..m..^",
           /* line */ (const char *) "   ....  ",
           /* line */ (const char *) "   .     ",
           /* line */ (const char *) "   ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^      ",
           /* line */ (const char *) "  ......^",
           /* line */ (const char *) "^..x.    ",
           /* line */ (const char *) "  ...    ",
           /* line */ (const char *) "  .      ",
           /* line */ (const char *) "  ^      ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^   ",
           /* line */ (const char *) "^... ",
           /* line */ (const char *) " .g.^",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^   ",
           /* line */ (const char *) " ...^",
           /* line */ (const char *) "^.m. ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^   ",
           /* line */ (const char *) "   .   ",
           /* line */ (const char *) "   .   ",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) " .x.m. ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^  ",
           /* line */ (const char *) " ...^",
           /* line */ (const char *) "^.x. ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) "  ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^   ",
           /* line */ (const char *) "    .   ",
           /* line */ (const char *) "   ...  ",
           /* line */ (const char *) "^...g..^",
           /* line */ (const char *) "   ...  ",
           /* line */ (const char *) "    .   ",
           /* line */ (const char *) "    .   ",
           /* line */ (const char *) "    ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^   ",
           /* line */ (const char *) "^...^",
           /* line */ (const char *) " .|. ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^      ",
           /* line */ (const char *) "  .      ",
           /* line */ (const char *) "  .      ",
           /* line */ (const char *) "  .      ",
           /* line */ (const char *) " .....   ",
           /* line */ (const char *) "^..x..   ",
           /* line */ (const char *) " x......^",
           /* line */ (const char *) " xx...   ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "m. ^  ",
           /* line */ (const char *) "..C.. ",
           /* line */ (const char *) " CC..^",
           /* line */ (const char *) "^.... ",
           /* line */ (const char *) " ..m. ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^   ",
           /* line */ (const char *) "  .   ",
           /* line */ (const char *) "  .   ",
           /* line */ (const char *) "  .   ",
           /* line */ (const char *) " ...  ",
           /* line */ (const char *) " .g.  ",
           /* line */ (const char *) "^....^",
           /* line */ (const char *) " ...  ",
           /* line */ (const char *) "  .   ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^    ",
           /* line */ (const char *) "^.... ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) " ..g.^",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "   ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^     ",
           /* line */ (const char *) "^........^",
           /* line */ (const char *) "  .g.|.   ",
           /* line */ (const char *) "  .....   ",
           /* line */ (const char *) "    .     ",
           /* line */ (const char *) "    .     ",
           /* line */ (const char *) "    ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^   ",
           /* line */ (const char *) "   ..... ",
           /* line */ (const char *) "   ...x.^",
           /* line */ (const char *) "^...xxx. ",
           /* line */ (const char *) "   .x... ",
           /* line */ (const char *) "   ..... ",
           /* line */ (const char *) "      .  ",
           /* line */ (const char *) "      ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^       ",
           /* line */ (const char *) " .......^",
           /* line */ (const char *) "^.....   ",
           /* line */ (const char *) " .....   ",
           /* line */ (const char *) " .       ",
           /* line */ (const char *) " ^       ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^     ",
           /* line */ (const char *) " ...xx ",
           /* line */ (const char *) " .x..x ",
           /* line */ (const char *) " .x... ",
           /* line */ (const char *) "^.xxx.^",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^       ",
           /* line */ (const char *) "   .       ",
           /* line */ (const char *) "   .       ",
           /* line */ (const char *) "   .       ",
           /* line */ (const char *) "^.......   ",
           /* line */ (const char *) "   .....   ",
           /* line */ (const char *) "   .......^",
           /* line */ (const char *) "   .....   ",
           /* line */ (const char *) "    .      ",
           /* line */ (const char *) "    ^      ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^   ",
           /* line */ (const char *) " xx..  ",
           /* line */ (const char *) " x...  ",
           /* line */ (const char *) " ..x.  ",
           /* line */ (const char *) "^.....^",
           /* line */ (const char *) " ....  ",
           /* line */ (const char *) " .     ",
           /* line */ (const char *) " ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^    ",
           /* line */ (const char *) " ....^",
           /* line */ (const char *) "^..m. ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^   ",
           /* line */ (const char *) "^....^",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "   ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^   ",
           /* line */ (const char *) " .   ",
           /* line */ (const char *) " .   ",
           /* line */ (const char *) "^... ",
           /* line */ (const char *) " ...^",
           /* line */ (const char *) " .g. ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) "  .  ",
           /* line */ (const char *) "  ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^     ",
           /* line */ (const char *) "^....... ",
           /* line */ (const char *) "   .....^",
           /* line */ (const char *) "   ..|.. ",
           /* line */ (const char *) "   ..... ",
           /* line */ (const char *) "   .     ",
           /* line */ (const char *) "   ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^    ",
           /* line */ (const char *) "  .    ",
           /* line */ (const char *) "  .    ",
           /* line */ (const char *) "  ...  ",
           /* line */ (const char *) "^..g..^",
           /* line */ (const char *) "  ...  ",
           /* line */ (const char *) "  ...  ",
           /* line */ (const char *) "  .    ",
           /* line */ (const char *) "  ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^       ",
           /* line */ (const char *) "  .       ",
           /* line */ (const char *) "^.....    ",
           /* line */ (const char *) "  .|.....^",
           /* line */ (const char *) "  ....    ",
           /* line */ (const char *) "  .       ",
           /* line */ (const char *) "  ^       ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^    ",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) " ..x..^",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^    ",
           /* line */ (const char *) "  .    ",
           /* line */ (const char *) "  .    ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) "^....  ",
           /* line */ (const char *) " ..|.  ",
           /* line */ (const char *) " ....  ",
           /* line */ (const char *) "  .    ",
           /* line */ (const char *) "  .    ",
           /* line */ (const char *) "  .    ",
           /* line */ (const char *) "  .    ",
           /* line */ (const char *) "  .    ",
           /* line */ (const char *) "  ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^    ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) "^.|.|. ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^   ",
           /* line */ (const char *) "    .   ",
           /* line */ (const char *) "    .   ",
           /* line */ (const char *) "   ...  ",
           /* line */ (const char *) "^...x.  ",
           /* line */ (const char *) "   ...  ",
           /* line */ (const char *) "   .m..^",
           /* line */ (const char *) "   ...  ",
           /* line */ (const char *) "    .   ",
           /* line */ (const char *) "    ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^    ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "^.....^",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^    ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "^.....^",
           /* line */ (const char *) " ..x.. ",
           /* line */ (const char *) " x.... ",
           /* line */ (const char *) " xx... ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^   ",
           /* line */ (const char *) "  .   ",
           /* line */ (const char *) "^....^",
           /* line */ (const char *) "  .m. ",
           /* line */ (const char *) "  ... ",
           /* line */ (const char *) "  ... ",
           /* line */ (const char *) "   .  ",
           /* line */ (const char *) "   .  ",
           /* line */ (const char *) "   ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "       ^  ",
           /* line */ (const char *) "       .  ",
           /* line */ (const char *) "       .  ",
           /* line */ (const char *) "    ..... ",
           /* line */ (const char *) "^........ ",
           /* line */ (const char *) "    .....^",
           /* line */ (const char *) "    ..... ",
           /* line */ (const char *) "    ..... ",
           /* line */ (const char *) "     ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^    ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) "^.x.x. ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "    ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^  ",
           /* line */ (const char *) "   ... ",
           /* line */ (const char *) "   .|.^",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) "   ... ",
           /* line */ (const char *) "    .  ",
           /* line */ (const char *) "    .  ",
           /* line */ (const char *) "    .  ",
           /* line */ (const char *) "    ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^   ",
           /* line */ (const char *) "  .   ",
           /* line */ (const char *) "^.... ",
           /* line */ (const char *) " ....^",
           /* line */ (const char *) " ..g. ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) " .    ",
           /* line */ (const char *) " ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^  ",
           /* line */ (const char *) " ...^",
           /* line */ (const char *) "^.x. ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^   ",
           /* line */ (const char *) "   .   ",
           /* line */ (const char *) "   .   ",
           /* line */ (const char *) "^.....^",
           /* line */ (const char *) "  .M.. ",
           /* line */ (const char *) "  .... ",
           /* line */ (const char *) "    .  ",
           /* line */ (const char *) "    ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^      ",
           /* line */ (const char *) "^.......^",
           /* line */ (const char *) " ..m.    ",
           /* line */ (const char *) " ....    ",
           /* line */ (const char *) " .|..    ",
           /* line */ (const char *) " ....    ",
           /* line */ (const char *) "   .     ",
           /* line */ (const char *) "   ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^  ",
           /* line */ (const char *) "^... ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " ...^",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^      ",
           /* line */ (const char *) "^.......^",
           /* line */ (const char *) "  ..m.   ",
           /* line */ (const char *) "  ....   ",
           /* line */ (const char *) "   ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^   ",
           /* line */ (const char *) " ...^",
           /* line */ (const char *) "^.M. ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^      ",
           /* line */ (const char *) " .      ",
           /* line */ (const char *) " ...    ",
           /* line */ (const char *) "^.m....^",
           /* line */ (const char *) " ...    ",
           /* line */ (const char *) " .      ",
           /* line */ (const char *) " ^      ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^  ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) "^... ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " ...^",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^   ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) " .|.. ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "^.g..^",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) " ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^  ",
           /* line */ (const char *) " xx... ",
           /* line */ (const char *) " x.... ",
           /* line */ (const char *) " ..x.. ",
           /* line */ (const char *) "^.....^",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^   ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) "^.x.^",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^        ",
           /* line */ (const char *) "  ........^",
           /* line */ (const char *) "  .....    ",
           /* line */ (const char *) "^......    ",
           /* line */ (const char *) "  .....    ",
           /* line */ (const char *) "   .       ",
           /* line */ (const char *) "   .       ",
           /* line */ (const char *) "   ^       ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^    ",
           /* line */ (const char *) "^..xx ",
           /* line */ (const char *) " ...x ",
           /* line */ (const char *) " ....^",
           /* line */ (const char *) " ..x. ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^   ",
           /* line */ (const char *) "^.....^",
           /* line */ (const char *) "  .|.  ",
           /* line */ (const char *) "  ...  ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^  ",
           /* line */ (const char *) "     .  ",
           /* line */ (const char *) "    ...^",
           /* line */ (const char *) "    ... ",
           /* line */ (const char *) "^....m. ",
           /* line */ (const char *) "    ... ",
           /* line */ (const char *) "     .  ",
           /* line */ (const char *) "     ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^  ",
           /* line */ (const char *) " ...^",
           /* line */ (const char *) " .g. ",
           /* line */ (const char *) "^... ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^   ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "^..|.^",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "   ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^  ",
           /* line */ (const char *) "   .  ",
           /* line */ (const char *) " ....^",
           /* line */ (const char *) "^.... ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "   .  ",
           /* line */ (const char *) "   ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^   ",
           /* line */ (const char *) " m.  .   ",
           /* line */ (const char *) " ..C...  ",
           /* line */ (const char *) "  CC.x..^",
           /* line */ (const char *) "^......  ",
           /* line */ (const char *) "  .....  ",
           /* line */ (const char *) "  .      ",
           /* line */ (const char *) "  ^      ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^     ",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) " .m.m.^",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " .|.|. ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "    ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^   ",
           /* line */ (const char *) "     .   ",
           /* line */ (const char *) "     .   ",
           /* line */ (const char *) "   .....^",
           /* line */ (const char *) "^....x.. ",
           /* line */ (const char *) "   ..... ",
           /* line */ (const char *) "    .    ",
           /* line */ (const char *) "    .    ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^   ",
           /* line */ (const char *) "^.....^",
           /* line */ (const char *) " .|... ",
           /* line */ (const char *) " ...```",
           /* line */ (const char *) " ..````",
           /* line */ (const char *) "  ^  `C",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^  ",
           /* line */ (const char *) "     .  ",
           /* line */ (const char *) "     .  ",
           /* line */ (const char *) "^......^",
           /* line */ (const char *) "   .x.. ",
           /* line */ (const char *) "   .... ",
           /* line */ (const char *) "     ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^   ",
           /* line */ (const char *) "   .....^",
           /* line */ (const char *) "^....g.  ",
           /* line */ (const char *) "   ....  ",
           /* line */ (const char *) "    .    ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^  ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) "^.g.^",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) "  ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^    ",
           /* line */ (const char *) "^......  ",
           /* line */ (const char *) "  .m.x..^",
           /* line */ (const char *) "  .....  ",
           /* line */ (const char *) "  .      ",
           /* line */ (const char *) "  ^      ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^  ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) "^.m.^",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^    ",
           /* line */ (const char *) "     .  `m",
           /* line */ (const char *) "    ..````",
           /* line */ (const char *) "    ...```",
           /* line */ (const char *) "^....|...^",
           /* line */ (const char *) "    ..... ",
           /* line */ (const char *) "    .     ",
           /* line */ (const char *) "    ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^       ",
           /* line */ (const char *) "  ....    ",
           /* line */ (const char *) "  .......^",
           /* line */ (const char *) "^.....    ",
           /* line */ (const char *) "  ....    ",
           /* line */ (const char *) "  ....    ",
           /* line */ (const char *) "   .      ",
           /* line */ (const char *) "   ^      ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^  ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " ..|.. ",
           /* line */ (const char *) "^.....^",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "  ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^     ",
           /* line */ (const char *) "  .     ",
           /* line */ (const char *) "  .     ",
           /* line */ (const char *) "^......^",
           /* line */ (const char *) "  ...   ",
           /* line */ (const char *) "  .g.   ",
           /* line */ (const char *) "  ...   ",
           /* line */ (const char *) "  .     ",
           /* line */ (const char *) "  ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^    ",
           /* line */ (const char *) "   .    ",
           /* line */ (const char *) " xx...  ",
           /* line */ (const char *) " x.....^",
           /* line */ (const char *) "^..x..  ",
           /* line */ (const char *) " .....  ",
           /* line */ (const char *) "   .    ",
           /* line */ (const char *) "   .    ",
           /* line */ (const char *) "   ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^    ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " .m...^",
           /* line */ (const char *) "^....` ",
           /* line */ (const char *) " .m.`` ",
           /* line */ (const char *) " ...```",
           /* line */ (const char *) "   ^``m",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^    ",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) " ..xx.^",
           /* line */ (const char *) " ..xx. ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "    ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^  ",
           /* line */ (const char *) " ...^",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) "^... ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^   ",
           /* line */ (const char *) "   .   ",
           /* line */ (const char *) "   .   ",
           /* line */ (const char *) "   .   ",
           /* line */ (const char *) "   .   ",
           /* line */ (const char *) "  ...  ",
           /* line */ (const char *) "^..m.  ",
           /* line */ (const char *) "  ....^",
           /* line */ (const char *) "  ...  ",
           /* line */ (const char *) "  .    ",
           /* line */ (const char *) "  ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^  ",
           /* line */ (const char *) "^.... ",
           /* line */ (const char *) " .|..^",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "   ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^    ",
           /* line */ (const char *) "    .    ",
           /* line */ (const char *) " .....   ",
           /* line */ (const char *) " .m~~.   ",
           /* line */ (const char *) "^.~~~...^",
           /* line */ (const char *) " .~~..   ",
           /* line */ (const char *) " .....   ",
           /* line */ (const char *) " .       ",
           /* line */ (const char *) " ^       ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^     ",
           /* line */ (const char *) "  ........^",
           /* line */ (const char *) "^..g.x.    ",
           /* line */ (const char *) "  .....    ",
           /* line */ (const char *) "     .     ",
           /* line */ (const char *) "     ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^   ",
           /* line */ (const char *) "   ....  ",
           /* line */ (const char *) "^...m...^",
           /* line */ (const char *) "   ....  ",
           /* line */ (const char *) "    .    ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^  ",
           /* line */ (const char *) " xxx.. ",
           /* line */ (const char *) " x.... ",
           /* line */ (const char *) " x.x.. ",
           /* line */ (const char *) "^.....^",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "  ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^    ",
           /* line */ (const char *) "  .....  ",
           /* line */ (const char *) "  ...x.  ",
           /* line */ (const char *) "  .x...  ",
           /* line */ (const char *) "^....g..^",
           /* line */ (const char *) "  .....  ",
           /* line */ (const char *) "   ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^    ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "^....^",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^     ",
           /* line */ (const char *) "^....   ",
           /* line */ (const char *) "  ...   ",
           /* line */ (const char *) "  .m.   ",
           /* line */ (const char *) "  .....^",
           /* line */ (const char *) "  ...   ",
           /* line */ (const char *) "   .    ",
           /* line */ (const char *) "   .    ",
           /* line */ (const char *) "   ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^   ",
           /* line */ (const char *) "  ...^",
           /* line */ (const char *) "  ... ",
           /* line */ (const char *) "  ... ",
           /* line */ (const char *) "^.... ",
           /* line */ (const char *) "  ... ",
           /* line */ (const char *) "   .  ",
           /* line */ (const char *) "   .  ",
           /* line */ (const char *) "   ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^  ",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) " .g.x.^",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "    ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^  ",
           /* line */ (const char *) "^....^",
           /* line */ (const char *) " ..x. ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^    ",
           /* line */ (const char *) "     .    ",
           /* line */ (const char *) "^......   ",
           /* line */ (const char *) "  .|.g...^",
           /* line */ (const char *) "  .....   ",
           /* line */ (const char *) "   ^      ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^   ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "^....^",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "   ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^   ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) "^... ",
           /* line */ (const char *) " ...^",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^   ",
           /* line */ (const char *) "^....^",
           /* line */ (const char *) " .x.. ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "C``^   ",
           /* line */ (const char *) "```... ",
           /* line */ (const char *) " ``... ",
           /* line */ (const char *) " `..g. ",
           /* line */ (const char *) "^.....^",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "    ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^   ",
           /* line */ (const char *) "^...^",
           /* line */ (const char *) " .g. ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^   ",
           /* line */ (const char *) " ....^",
           /* line */ (const char *) " .m.. ",
           /* line */ (const char *) "^.... ",
           /* line */ (const char *) " ..m. ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^    ",
           /* line */ (const char *) "    .    ",
           /* line */ (const char *) "    .    ",
           /* line */ (const char *) "    ....^",
           /* line */ (const char *) "^....... ",
           /* line */ (const char *) "    ..m. ",
           /* line */ (const char *) "    .... ",
           /* line */ (const char *) "      .  ",
           /* line */ (const char *) "      ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  m..^    ",
           /* line */ (const char *) "  .......^",
           /* line */ (const char *) "   ..|.   ",
           /* line */ (const char *) "^......   ",
           /* line */ (const char *) "   ....   ",
           /* line */ (const char *) "    .     ",
           /* line */ (const char *) "    ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^   ",
           /* line */ (const char *) "   .   ",
           /* line */ (const char *) "   .   ",
           /* line */ (const char *) "^.....^",
           /* line */ (const char *) "  .G.. ",
           /* line */ (const char *) "  .... ",
           /* line */ (const char *) "  .    ",
           /* line */ (const char *) "  ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^  ",
           /* line */ (const char *) "^... ",
           /* line */ (const char *) " ...^",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^  ",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) "  .x..^",
           /* line */ (const char *) "  .... ",
           /* line */ (const char *) "  .    ",
           /* line */ (const char *) "  ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^    ",
           /* line */ (const char *) "  .....^",
           /* line */ (const char *) "  .|.   ",
           /* line */ (const char *) "^....   ",
           /* line */ (const char *) "  .|.   ",
           /* line */ (const char *) "  ...   ",
           /* line */ (const char *) "   .    ",
           /* line */ (const char *) "   .    ",
           /* line */ (const char *) "   ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^    ",
           /* line */ (const char *) "   ..... ",
           /* line */ (const char *) "^...xx..^",
           /* line */ (const char *) "   .xx.. ",
           /* line */ (const char *) "   ..... ",
           /* line */ (const char *) "    .    ",
           /* line */ (const char *) "    .    ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^    ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "^.g..^",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) " ..x. ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "   ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "      ^    ",
           /* line */ (const char *) "      .    ",
           /* line */ (const char *) "^.........^",
           /* line */ (const char *) "   ..|..   ",
           /* line */ (const char *) "   .....   ",
           /* line */ (const char *) "    ^      ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^   ",
           /* line */ (const char *) "^...^",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) "  ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^  ",
           /* line */ (const char *) " $. .  ",
           /* line */ (const char *) " ..|.. ",
           /* line */ (const char *) "  |... ",
           /* line */ (const char *) "  ....^",
           /* line */ (const char *) "^...g. ",
           /* line */ (const char *) "  .... ",
           /* line */ (const char *) "  .    ",
           /* line */ (const char *) "  .    ",
           /* line */ (const char *) "  ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^    ",
           /* line */ (const char *) "^....   ",
           /* line */ (const char *) "  .g...^",
           /* line */ (const char *) "  ...   ",
           /* line */ (const char *) "  .x.   ",
           /* line */ (const char *) "  ...   ",
           /* line */ (const char *) "   .    ",
           /* line */ (const char *) "   ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^         ",
           /* line */ (const char *) " .....      ",
           /* line */ (const char *) " .g.m.      ",
           /* line */ (const char *) "^..........^",
           /* line */ (const char *) " .....      ",
           /* line */ (const char *) "    .       ",
           /* line */ (const char *) "    .       ",
           /* line */ (const char *) "    ^       ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^   ",
           /* line */ (const char *) "  .   ",
           /* line */ (const char *) "  ...^",
           /* line */ (const char *) "^..g. ",
           /* line */ (const char *) "  ... ",
           /* line */ (const char *) "   .  ",
           /* line */ (const char *) "   .  ",
           /* line */ (const char *) "   .  ",
           /* line */ (const char *) "   .  ",
           /* line */ (const char *) "   ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^   ",
           /* line */ (const char *) " ...^",
           /* line */ (const char *) "^.x. ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^   ",
           /* line */ (const char *) "^....^",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) " ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^   ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " .|. ",
           /* line */ (const char *) "^...^",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) "  ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^  ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "^..m.^",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) " ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^  .m",
           /* line */ (const char *) " ..C..",
           /* line */ (const char *) " ..CC ",
           /* line */ (const char *) " ....^",
           /* line */ (const char *) "^.g.. ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "   ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^   ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) "^...^",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) "  ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "      ^    ",
           /* line */ (const char *) "    ......^",
           /* line */ (const char *) "^........  ",
           /* line */ (const char *) "    .....  ",
           /* line */ (const char *) "      .    ",
           /* line */ (const char *) "      ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^    ",
           /* line */ (const char *) "  ...  ",
           /* line */ (const char *) "^....  ",
           /* line */ (const char *) "  .x.  ",
           /* line */ (const char *) "  ....^",
           /* line */ (const char *) "  ...  ",
           /* line */ (const char *) "  .    ",
           /* line */ (const char *) "  ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^   ",
           /* line */ (const char *) "     .   ",
           /* line */ (const char *) "   ....  ",
           /* line */ (const char *) "   .|...^",
           /* line */ (const char *) "^......  ",
           /* line */ (const char *) "   ..CC  ",
           /* line */ (const char *) "   ..C.. ",
           /* line */ (const char *) "    ^ .m ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^     ",
           /* line */ (const char *) "^.........^",
           /* line */ (const char *) "   ...x.   ",
           /* line */ (const char *) "  ```...   ",
           /* line */ (const char *) "  ````..   ",
           /* line */ (const char *) "  m`  ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^    ",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "    ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^   ",
           /* line */ (const char *) "  .   ",
           /* line */ (const char *) "  .   ",
           /* line */ (const char *) "  .   ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "^....^",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "  .   ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^   ",
           /* line */ (const char *) "^.... ",
           /* line */ (const char *) " ..g.^",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "   ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^      ",
           /* line */ (const char *) "  .....  ",
           /* line */ (const char *) "  ......^",
           /* line */ (const char *) "  .....  ",
           /* line */ (const char *) "^......  ",
           /* line */ (const char *) "  .....  ",
           /* line */ (const char *) "    .    ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^    ",
           /* line */ (const char *) "    .    ",
           /* line */ (const char *) "  .....  ",
           /* line */ (const char *) "  .g.g..^",
           /* line */ (const char *) "  .....  ",
           /* line */ (const char *) "^....``` ",
           /* line */ (const char *) "  ..```` ",
           /* line */ (const char *) "   ^  `C ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^  ",
           /* line */ (const char *) "   .  ",
           /* line */ (const char *) "^.... ",
           /* line */ (const char *) "  ... ",
           /* line */ (const char *) "  .|.^",
           /* line */ (const char *) "  ... ",
           /* line */ (const char *) "   .  ",
           /* line */ (const char *) "   .  ",
           /* line */ (const char *) "   ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^  ",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) " .x.|.^",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "  ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^  ",
           /* line */ (const char *) "^.... ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) " ..|.^",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^   ",
           /* line */ (const char *) " ..xx ",
           /* line */ (const char *) " ...x ",
           /* line */ (const char *) " ....^",
           /* line */ (const char *) "^..g. ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) " ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^  ",
           /* line */ (const char *) "   .  ",
           /* line */ (const char *) "   .  ",
           /* line */ (const char *) "  ... ",
           /* line */ (const char *) "  .|.^",
           /* line */ (const char *) "^.... ",
           /* line */ (const char *) "  ... ",
           /* line */ (const char *) "   .  ",
           /* line */ (const char *) "   ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "m`  ^  ",
           /* line */ (const char *) "````.. ",
           /* line */ (const char *) "```... ",
           /* line */ (const char *) "^...m.^",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "  ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^     ",
           /* line */ (const char *) "  .     ",
           /* line */ (const char *) "  .     ",
           /* line */ (const char *) " ......^",
           /* line */ (const char *) " .....  ",
           /* line */ (const char *) "^.....  ",
           /* line */ (const char *) " .....  ",
           /* line */ (const char *) " .....  ",
           /* line */ (const char *) "   ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^    ",
           /* line */ (const char *) "  ...   ",
           /* line */ (const char *) "^......^",
           /* line */ (const char *) "  ...   ",
           /* line */ (const char *) "  .     ",
           /* line */ (const char *) "  ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^  ",
           /* line */ (const char *) "^.... ",
           /* line */ (const char *) " ....^",
           /* line */ (const char *) " .M.. ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) " ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^     ",
           /* line */ (const char *) " ...xx ",
           /* line */ (const char *) "^....x ",
           /* line */ (const char *) " ..x.. ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^    ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) "^.xx.. ",
           /* line */ (const char *) " .xx.. ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "    ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^  ",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) " .x.m. ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " .g.m.^",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "    ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^     ",
           /* line */ (const char *) "  .     ",
           /* line */ (const char *) "^....   ",
           /* line */ (const char *) "  ...   ",
           /* line */ (const char *) "  .M.   ",
           /* line */ (const char *) "  .....^",
           /* line */ (const char *) "  ...   ",
           /* line */ (const char *) "  .     ",
           /* line */ (const char *) "  .     ",
           /* line */ (const char *) "  ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "       ^   ",
           /* line */ (const char *) "    .....  ",
           /* line */ (const char *) "^....m.m..^",
           /* line */ (const char *) "    .....  ",
           /* line */ (const char *) "     ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^     ",
           /* line */ (const char *) "  .     ",
           /* line */ (const char *) "  .     ",
           /* line */ (const char *) "  .....^",
           /* line */ (const char *) "^..G.   ",
           /* line */ (const char *) "  ...   ",
           /* line */ (const char *) "   .    ",
           /* line */ (const char *) "   ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^   ",
           /* line */ (const char *) "^....^",
           /* line */ (const char *) " .m.. ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "   ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "....^  ",
           /* line */ (const char *) "..m... ",
           /* line */ (const char *) "....m.^",
           /* line */ (const char *) "..x... ",
           /* line */ (const char *) "^....x ",
           /* line */ (const char *) " ...xx ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^  ",
           /* line */ (const char *) " xx..^",
           /* line */ (const char *) " x... ",
           /* line */ (const char *) "^..x. ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^    ",
           /* line */ (const char *) " .    ",
           /* line */ (const char *) " ...  ",
           /* line */ (const char *) "^.g.  ",
           /* line */ (const char *) " ....^",
           /* line */ (const char *) " .x.  ",
           /* line */ (const char *) " ...  ",
           /* line */ (const char *) " .    ",
           /* line */ (const char *) " ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^   ",
           /* line */ (const char *) " ...^",
           /* line */ (const char *) "^... ",
           /* line */ (const char *) " .g. ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^    ",
           /* line */ (const char *) "    .    ",
           /* line */ (const char *) "    .    ",
           /* line */ (const char *) "   ...   ",
           /* line */ (const char *) "^.....   ",
           /* line */ (const char *) "   .|...^",
           /* line */ (const char *) "   ...   ",
           /* line */ (const char *) "   .     ",
           /* line */ (const char *) "   .     ",
           /* line */ (const char *) "   ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^   ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "^.....^",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^  ",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "  ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^   ",
           /* line */ (const char *) " ....^",
           /* line */ (const char *) "^.|.. ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^       ",
           /* line */ (const char *) "  .       ",
           /* line */ (const char *) " ........^",
           /* line */ (const char *) "^.|.x.    ",
           /* line */ (const char *) " .....    ",
           /* line */ (const char *) "    ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^  ",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "    ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^   ",
           /* line */ (const char *) " ...^",
           /* line */ (const char *) "^.x. ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) "  ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^  ",
           /* line */ (const char *) " ...^",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) "^.m. ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^   ",
           /* line */ (const char *) "     .   ",
           /* line */ (const char *) "^.......^",
           /* line */ (const char *) "    .g.  ",
           /* line */ (const char *) "    ...  ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "      ^   ",
           /* line */ (const char *) "   .....  ",
           /* line */ (const char *) "   .g....^",
           /* line */ (const char *) "   ...xx  ",
           /* line */ (const char *) "^....xxx  ",
           /* line */ (const char *) "   ..xxx  ",
           /* line */ (const char *) "   ^      ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^    ",
           /* line */ (const char *) "^....^",
           /* line */ (const char *) " ..G. ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "   ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^   ",
           /* line */ (const char *) "    .   ",
           /* line */ (const char *) "^.....  ",
           /* line */ (const char *) "  ..m.  ",
           /* line */ (const char *) "  x....^",
           /* line */ (const char *) "  xx..  ",
           /* line */ (const char *) "    .   ",
           /* line */ (const char *) "    ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^     ",
           /* line */ (const char *) "^...... ",
           /* line */ (const char *) "  .xxx. ",
           /* line */ (const char *) "  .xms. ",
           /* line */ (const char *) "  .xxx.^",
           /* line */ (const char *) "  ..... ",
           /* line */ (const char *) "    ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^    ",
           /* line */ (const char *) "     .    ",
           /* line */ (const char *) "  .....   ",
           /* line */ (const char *) "^..M.|...^",
           /* line */ (const char *) "  .....   ",
           /* line */ (const char *) "  ^       ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^     ",
           /* line */ (const char *) "     .     ",
           /* line */ (const char *) "     .     ",
           /* line */ (const char *) "   .....   ",
           /* line */ (const char *) "   ...m.   ",
           /* line */ (const char *) "^...|...   ",
           /* line */ (const char *) "   ...m...^",
           /* line */ (const char *) "   .....   ",
           /* line */ (const char *) "     ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^     ",
           /* line */ (const char *) " ...xx ",
           /* line */ (const char *) " ....x ",
           /* line */ (const char *) "^..x..^",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^   ",
           /* line */ (const char *) " ...^",
           /* line */ (const char *) "^... ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^    ",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) " .x... ",
           /* line */ (const char *) " ...g.^",
           /* line */ (const char *) " CC... ",
           /* line */ (const char *) "..C... ",
           /* line */ (const char *) "m. ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^  ``C",
           /* line */ (const char *) " ...```",
           /* line */ (const char *) " .x.`` ",
           /* line */ (const char *) "^....` ",
           /* line */ (const char *) " ..|..^",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "    ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^     ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^  ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^    ",
           /* line */ (const char *) " .    ",
           /* line */ (const char *) " .    ",
           /* line */ (const char *) " .    ",
           /* line */ (const char *) " .    ",
           /* line */ (const char *) " ....^",
           /* line */ (const char *) "^...  ",
           /* line */ (const char *) " ...  ",
           /* line */ (const char *) "  .   ",
           /* line */ (const char *) "  .   ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^    ",
           /* line */ (const char *) "    .    ",
           /* line */ (const char *) "^......  ",
           /* line */ (const char *) "    ...  ",
           /* line */ (const char *) "    .x.  ",
           /* line */ (const char *) "    ....^",
           /* line */ (const char *) "    ...  ",
           /* line */ (const char *) "    .    ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^  ",
           /* line */ (const char *) "     .  ",
           /* line */ (const char *) "   ....^",
           /* line */ (const char *) "^...... ",
           /* line */ (const char *) "   .... ",
           /* line */ (const char *) "   .    ",
           /* line */ (const char *) "   .    ",
           /* line */ (const char *) "   ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^     ",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) " ..x..^",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^     ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) " ....  ",
           /* line */ (const char *) " .m..  ",
           /* line */ (const char *) "^....  ",
           /* line */ (const char *) " ....  ",
           /* line */ (const char *) "  ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^  ",
           /* line */ (const char *) "   .  ",
           /* line */ (const char *) "   .  ",
           /* line */ (const char *) "   .  ",
           /* line */ (const char *) "$. .  ",
           /* line */ (const char *) "..|..^",
           /* line */ (const char *) " |... ",
           /* line */ (const char *) "^..m. ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "  .   ",
           /* line */ (const char *) "  .   ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^  ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "^....^",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "   ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^   ",
           /* line */ (const char *) "^.... ",
           /* line */ (const char *) " ..x.^",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^    ",
           /* line */ (const char *) " .    ",
           /* line */ (const char *) "^.... ",
           /* line */ (const char *) " .x..^",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "  .   ",
           /* line */ (const char *) "  .   ",
           /* line */ (const char *) "  .   ",
           /* line */ (const char *) "  .   ",
           /* line */ (const char *) "  .   ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^    ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) " ..x.. ",
           /* line */ (const char *) "^....x ",
           /* line */ (const char *) " ...xx ",
           /* line */ (const char *) " ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^     ",
           /* line */ (const char *) "    .     ",
           /* line */ (const char *) "   .....  ",
           /* line */ (const char *) "^...G.g..^",
           /* line */ (const char *) "   .....  ",
           /* line */ (const char *) "      .   ",
           /* line */ (const char *) "      ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^ ..m",
           /* line */ (const char *) "^......",
           /* line */ (const char *) " .g.g.^",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "  ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^    ",
           /* line */ (const char *) "^.... ",
           /* line */ (const char *) " .m..^",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "   ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^    ",
           /* line */ (const char *) " ....^",
           /* line */ (const char *) "^.... ",
           /* line */ (const char *) " ..|. ",
           /* line */ (const char *) " x... ",
           /* line */ (const char *) " xx.. ",
           /* line */ (const char *) "   ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "       ^    ",
           /* line */ (const char *) "       .    ",
           /* line */ (const char *) "    .....   ",
           /* line */ (const char *) "    .....   ",
           /* line */ (const char *) "^..........^",
           /* line */ (const char *) "    .....   ",
           /* line */ (const char *) "      .     ",
           /* line */ (const char *) "      .     ",
           /* line */ (const char *) "      ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^   ",
           /* line */ (const char *) "^.... ",
           /* line */ (const char *) " ..g.^",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) " ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^     ",
           /* line */ (const char *) "     .     ",
           /* line */ (const char *) "     .     ",
           /* line */ (const char *) "     .     ",
           /* line */ (const char *) "   ....    ",
           /* line */ (const char *) "^.........^",
           /* line */ (const char *) "   ....    ",
           /* line */ (const char *) "     .     ",
           /* line */ (const char *) "     ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^   ",
           /* line */ (const char *) "  .   ",
           /* line */ (const char *) "  .   ",
           /* line */ (const char *) "^...  ",
           /* line */ (const char *) " .x..^",
           /* line */ (const char *) " ...  ",
           /* line */ (const char *) "  .   ",
           /* line */ (const char *) "  .   ",
           /* line */ (const char *) "  .   ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^    ",
           /* line */ (const char *) "^....^",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "   ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^   ",
           /* line */ (const char *) " .   ",
           /* line */ (const char *) "^...^",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " .   ",
           /* line */ (const char *) " .   ",
           /* line */ (const char *) " ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^    ",
           /* line */ (const char *) "  .....^",
           /* line */ (const char *) "  .x.   ",
           /* line */ (const char *) "^....   ",
           /* line */ (const char *) "  .g.   ",
           /* line */ (const char *) "  ...   ",
           /* line */ (const char *) "  ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^    ",
           /* line */ (const char *) "   ....  ",
           /* line */ (const char *) "^...x...^",
           /* line */ (const char *) "   ....  ",
           /* line */ (const char *) "     ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^    ",
           /* line */ (const char *) "   .    ",
           /* line */ (const char *) "  .....^",
           /* line */ (const char *) "^..x.   ",
           /* line */ (const char *) "  ...   ",
           /* line */ (const char *) "  .     ",
           /* line */ (const char *) "  ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^  ",
           /* line */ (const char *) "^....^",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^     ",
           /* line */ (const char *) "^.....^",
           /* line */ (const char *) " ..g.. ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^     ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) " ..CC. ",
           /* line */ (const char *) " .CCC. ",
           /* line */ (const char *) "^.CCm. ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "    ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^    ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "^....^",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "   ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^   ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) " ....^",
           /* line */ (const char *) "^..x. ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "   ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^      ",
           /* line */ (const char *) "^.......    ",
           /* line */ (const char *) "   .x.|....^",
           /* line */ (const char *) "   .....    ",
           /* line */ (const char *) "   .        ",
           /* line */ (const char *) "   .        ",
           /* line */ (const char *) "   ^        ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^    ",
           /* line */ (const char *) "   .    ",
           /* line */ (const char *) "   .    ",
           /* line */ (const char *) "   .... ",
           /* line */ (const char *) "^....x. ",
           /* line */ (const char *) "   ....^",
           /* line */ (const char *) "   .... ",
           /* line */ (const char *) "    .   ",
           /* line */ (const char *) "    .   ",
           /* line */ (const char *) "    .   ",
           /* line */ (const char *) "    ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^   ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^     ",
           /* line */ (const char *) " ...    ",
           /* line */ (const char *) " .x....^",
           /* line */ (const char *) "^...    ",
           /* line */ (const char *) " ...    ",
           /* line */ (const char *) "  .     ",
           /* line */ (const char *) "  .     ",
           /* line */ (const char *) "  ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^   ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) " .g... ",
           /* line */ (const char *) " ...xx ",
           /* line */ (const char *) "^..xxx ",
           /* line */ (const char *) " ..xxx ",
           /* line */ (const char *) "  ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "      ^    ",
           /* line */ (const char *) "   .....   ",
           /* line */ (const char *) "^....M....^",
           /* line */ (const char *) "   .....   ",
           /* line */ (const char *) "      ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^   ",
           /* line */ (const char *) "     .   ",
           /* line */ (const char *) "^......  ",
           /* line */ (const char *) "  ..m...^",
           /* line */ (const char *) "  .....  ",
           /* line */ (const char *) "  .      ",
           /* line */ (const char *) "  .      ",
           /* line */ (const char *) "  ^      ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^    ",
           /* line */ (const char *) "  .    ",
           /* line */ (const char *) "^.....^",
           /* line */ (const char *) "  ...  ",
           /* line */ (const char *) "  ...  ",
           /* line */ (const char *) "  .    ",
           /* line */ (const char *) "  .    ",
           /* line */ (const char *) "  ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^  ",
           /* line */ (const char *) "   .  ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "^....^",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "  .   ",
           /* line */ (const char *) "  .   ",
           /* line */ (const char *) "  .   ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^     ",
           /* line */ (const char *) "  ....  ",
           /* line */ (const char *) "  ....  ",
           /* line */ (const char *) "^......^",
           /* line */ (const char *) "  ....  ",
           /* line */ (const char *) "    ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^   ",
           /* line */ (const char *) "    .   ",
           /* line */ (const char *) "   ...  ",
           /* line */ (const char *) "   ...  ",
           /* line */ (const char *) "   .x..^",
           /* line */ (const char *) "^.....  ",
           /* line */ (const char *) "   ...  ",
           /* line */ (const char *) "    .   ",
           /* line */ (const char *) "    ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^   ",
           /* line */ (const char *) " xx... ",
           /* line */ (const char *) " x.... ",
           /* line */ (const char *) "^..x..^",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^      ",
           /* line */ (const char *) "  ......^",
           /* line */ (const char *) "^......  ",
           /* line */ (const char *) "  .....  ",
           /* line */ (const char *) "     ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^     ",
           /* line */ (const char *) "   .     ",
           /* line */ (const char *) "   .     ",
           /* line */ (const char *) "^......  ",
           /* line */ (const char *) "  ......^",
           /* line */ (const char *) "  .x.CC  ",
           /* line */ (const char *) "  ...C.. ",
           /* line */ (const char *) "  ^   .m ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^  ",
           /* line */ (const char *) "    .  ",
           /* line */ (const char *) "    .  ",
           /* line */ (const char *) "  .... ",
           /* line */ (const char *) "  ..g. ",
           /* line */ (const char *) "^.....^",
           /* line */ (const char *) "  ..|. ",
           /* line */ (const char *) "  .... ",
           /* line */ (const char *) "  .    ",
           /* line */ (const char *) "  ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^     ",
           /* line */ (const char *) " xx...   ",
           /* line */ (const char *) " x......^",
           /* line */ (const char *) "^....`   ",
           /* line */ (const char *) " .x.``   ",
           /* line */ (const char *) " ...```  ",
           /* line */ (const char *) "  . ``m  ",
           /* line */ (const char *) "  ^      ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^   ",
           /* line */ (const char *) "^... ",
           /* line */ (const char *) " .x.^",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " .m. ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) "  ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^      ",
           /* line */ (const char *) "     .      ",
           /* line */ (const char *) "     .      ",
           /* line */ (const char *) "     ......^",
           /* line */ (const char *) "^.....g.x.  ",
           /* line */ (const char *) "     .....  ",
           /* line */ (const char *) "      ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^    ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) "^..x.x ",
           /* line */ (const char *) " ....x ",
           /* line */ (const char *) " ..xxx ",
           /* line */ (const char *) "  ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^    ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) "^..m.. ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^  ",
           /* line */ (const char *) "^.... ",
           /* line */ (const char *) " .x..^",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) " ..g. ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) " ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "      ^    ",
           /* line */ (const char *) "      .    ",
           /* line */ (const char *) "    ....   ",
           /* line */ (const char *) "    ......^",
           /* line */ (const char *) "^.......   ",
           /* line */ (const char *) "    ....   ",
           /* line */ (const char *) "    ....   ",
           /* line */ (const char *) "      ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^     ",
           /* line */ (const char *) "^......  ",
           /* line */ (const char *) "   ..g..^",
           /* line */ (const char *) "   ....  ",
           /* line */ (const char *) "     ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^   ",
           /* line */ (const char *) "   .   ",
           /* line */ (const char *) "   .   ",
           /* line */ (const char *) "   .   ",
           /* line */ (const char *) "  ...  ",
           /* line */ (const char *) "^..|..^",
           /* line */ (const char *) "  ...  ",
           /* line */ (const char *) "   .   ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^      ",
           /* line */ (const char *) "   ......^",
           /* line */ (const char *) "   .xxx.  ",
           /* line */ (const char *) "   .xTs.  ",
           /* line */ (const char *) "^...xxx.  ",
           /* line */ (const char *) "  ......  ",
           /* line */ (const char *) "  m. .    ",
           /* line */ (const char *) "     ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^  ",
           /* line */ (const char *) "    .  ",
           /* line */ (const char *) "    .  ",
           /* line */ (const char *) "    .  ",
           /* line */ (const char *) "    .  ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "^.xx.. ",
           /* line */ (const char *) " .xx..^",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "  .    ",
           /* line */ (const char *) "  ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^   ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) "^... ",
           /* line */ (const char *) " .x.^",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^     ",
           /* line */ (const char *) "^.....^",
           /* line */ (const char *) " ..|.. ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^  ",
           /* line */ (const char *) "    .  ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^   ",
           /* line */ (const char *) "^....^",
           /* line */ (const char *) " m... ",
           /* line */ (const char *) " ...` ",
           /* line */ (const char *) " ..`` ",
           /* line */ (const char *) " ..```",
           /* line */ (const char *) " ^ ``$",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^  ",
           /* line */ (const char *) "^.... ",
           /* line */ (const char *) " .xx. ",
           /* line */ (const char *) " .xx. ",
           /* line */ (const char *) " ....^",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) " ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^   ",
           /* line */ (const char *) "^... ",
           /* line */ (const char *) " ...^",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^   ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " .m.^",
           /* line */ (const char *) "^... ",
           /* line */ (const char *) " .g. ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) "  ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^      ",
           /* line */ (const char *) "  .      ",
           /* line */ (const char *) " .......^",
           /* line */ (const char *) " ...     ",
           /* line */ (const char *) "^.G.     ",
           /* line */ (const char *) " ...     ",
           /* line */ (const char *) " ...     ",
           /* line */ (const char *) " .       ",
           /* line */ (const char *) " ^       ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^    ",
           /* line */ (const char *) "^....^",
           /* line */ (const char *) " .x.. ",
           /* line */ (const char *) " ...x ",
           /* line */ (const char *) " ..xx ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^    ",
           /* line */ (const char *) "  .  .$",
           /* line */ (const char *) " ...|..",
           /* line */ (const char *) "^....| ",
           /* line */ (const char *) " xx... ",
           /* line */ (const char *) " xxx..^",
           /* line */ (const char *) " xxx.. ",
           /* line */ (const char *) "    ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^    ",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^  ",
           /* line */ (const char *) "     .  ",
           /* line */ (const char *) "^......^",
           /* line */ (const char *) "   ..|. ",
           /* line */ (const char *) "   .... ",
           /* line */ (const char *) "     ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^   ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " .xxx. ",
           /* line */ (const char *) " .x...^",
           /* line */ (const char *) "^.x..x ",
           /* line */ (const char *) " ...xx ",
           /* line */ (const char *) " ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^   ",
           /* line */ (const char *) "^.....^",
           /* line */ (const char *) "  ...  ",
           /* line */ (const char *) "  .m.  ",
           /* line */ (const char *) "  ...  ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^   ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " .x. ",
           /* line */ (const char *) " ...^",
           /* line */ (const char *) "^.m. ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) "  ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^   ",
           /* line */ (const char *) " ...^",
           /* line */ (const char *) "^.m. ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " .g. ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " .   ",
           /* line */ (const char *) " .   ",
           /* line */ (const char *) " ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^   ",
           /* line */ (const char *) "  .   ",
           /* line */ (const char *) "^....^",
           /* line */ (const char *) " .g.  ",
           /* line */ (const char *) " ...  ",
           /* line */ (const char *) " .    ",
           /* line */ (const char *) " ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^    ",
           /* line */ (const char *) "   .    ",
           /* line */ (const char *) "   ...  ",
           /* line */ (const char *) "^.....  ",
           /* line */ (const char *) "   .x..^",
           /* line */ (const char *) "   ...  ",
           /* line */ (const char *) "    .   ",
           /* line */ (const char *) "    .   ",
           /* line */ (const char *) "    ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^   ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "^.....^",
           /* line */ (const char *) " .m..| ",
           /* line */ (const char *) " ...|..",
           /* line */ (const char *) "  ^  .$",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^    ",
           /* line */ (const char *) "^....   ",
           /* line */ (const char *) " ..|...^",
           /* line */ (const char *) " ....   ",
           /* line */ (const char *) " .      ",
           /* line */ (const char *) " ^      ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^  ",
           /* line */ (const char *) "^.....^",
           /* line */ (const char *) "  .... ",
           /* line */ (const char *) "  .... ",
           /* line */ (const char *) "  ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^  ",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) " ..x..^",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "  ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^   ",
           /* line */ (const char *) "^.... ",
           /* line */ (const char *) " ....^",
           /* line */ (const char *) " CC.. ",
           /* line */ (const char *) "..C.. ",
           /* line */ (const char *) "m. ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^   ",
           /* line */ (const char *) "^... ",
           /* line */ (const char *) " .x. ",
           /* line */ (const char *) " ...^",
           /* line */ (const char *) " .x. ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) "  ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^   ",
           /* line */ (const char *) " ...^",
           /* line */ (const char *) "^.g. ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) "  ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^       ",
           /* line */ (const char *) "  .....    ",
           /* line */ (const char *) "  ........^",
           /* line */ (const char *) "^..g.CC    ",
           /* line */ (const char *) "  ...C..   ",
           /* line */ (const char *) "   .  .m   ",
           /* line */ (const char *) "   ^       ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^   ",
           /* line */ (const char *) "   .   ",
           /* line */ (const char *) "   .   ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) "^...x. ",
           /* line */ (const char *) " .xxx. ",
           /* line */ (const char *) " .x... ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "  .    ",
           /* line */ (const char *) "  .    ",
           /* line */ (const char *) "  .    ",
           /* line */ (const char *) "  .    ",
           /* line */ (const char *) "  ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^    ",
           /* line */ (const char *) "  .    ",
           /* line */ (const char *) "^....  ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) " .m..  ",
           /* line */ (const char *) " ....  ",
           /* line */ (const char *) " ....  ",
           /* line */ (const char *) "   .   ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^  ",
           /* line */ (const char *) "^... ",
           /* line */ (const char *) " .M. ",
           /* line */ (const char *) " ...^",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) "  ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^     ",
           /* line */ (const char *) "   .     ",
           /* line */ (const char *) "   .     ",
           /* line */ (const char *) "^.......^",
           /* line */ (const char *) "   ....  ",
           /* line */ (const char *) "   ....  ",
           /* line */ (const char *) "     .   ",
           /* line */ (const char *) "     ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^      ",
           /* line */ (const char *) "^.....  ",
           /* line */ (const char *) " ..g..  ",
           /* line */ (const char *) " .....  ",
           /* line */ (const char *) " ..g...^",
           /* line */ (const char *) " .....  ",
           /* line */ (const char *) "  .     ",
           /* line */ (const char *) "  .     ",
           /* line */ (const char *) "  ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^     ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " .|.m. ",
           /* line */ (const char *) "^.....^",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^   ",
           /* line */ (const char *) "^... ",
           /* line */ (const char *) " .m.^",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " .m. ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) "  ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^  ",
           /* line */ (const char *) "^.... ",
           /* line */ (const char *) " .m.. ",
           /* line */ (const char *) " ....^",
           /* line */ (const char *) " .x.. ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^      ",
           /* line */ (const char *) "    .      ",
           /* line */ (const char *) "^........  ",
           /* line */ (const char *) "    ......^",
           /* line */ (const char *) "    ..x.x  ",
           /* line */ (const char *) "    ....x  ",
           /* line */ (const char *) "    ..xxx  ",
           /* line */ (const char *) "     ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^     ",
           /* line */ (const char *) "   .     ",
           /* line */ (const char *) "   .     ",
           /* line */ (const char *) "^.......^",
           /* line */ (const char *) "   ..m.  ",
           /* line */ (const char *) "   ....  ",
           /* line */ (const char *) "    .    ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^     ",
           /* line */ (const char *) "  ...xx  ",
           /* line */ (const char *) "  ....x  ",
           /* line */ (const char *) "^..|....^",
           /* line */ (const char *) "  .....  ",
           /* line */ (const char *) "     .   ",
           /* line */ (const char *) "     ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^       ",
           /* line */ (const char *) " .......^",
           /* line */ (const char *) "^..x..   ",
           /* line */ (const char *) " x....   ",
           /* line */ (const char *) " xx...   ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^   ",
           /* line */ (const char *) "    .   ",
           /* line */ (const char *) "^.....  ",
           /* line */ (const char *) " .|.|..^",
           /* line */ (const char *) " .....  ",
           /* line */ (const char *) "   .    ",
           /* line */ (const char *) "   ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^   ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) "^...^",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) "  ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^    ",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) " .xCx. ",
           /* line */ (const char *) " .C|C.^",
           /* line */ (const char *) " .xCx. ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^   ",
           /* line */ (const char *) "  .   ",
           /* line */ (const char *) "  .   ",
           /* line */ (const char *) "  .   ",
           /* line */ (const char *) "  .   ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) " ....^",
           /* line */ (const char *) "^.... ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "   .  ",
           /* line */ (const char *) "   ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^    ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "^..x.. ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^   ",
           /* line */ (const char *) " $.  .   ",
           /* line */ (const char *) " ..|...  ",
           /* line */ (const char *) "  |..|..^",
           /* line */ (const char *) "^......  ",
           /* line */ (const char *) "  .g.x.  ",
           /* line */ (const char *) "  .....  ",
           /* line */ (const char *) "  .      ",
           /* line */ (const char *) "  ^      ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^  ",
           /* line */ (const char *) "^... ",
           /* line */ (const char *) " .|. ",
           /* line */ (const char *) " ...^",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^   ",
           /* line */ (const char *) "^.....^",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^     ",
           /* line */ (const char *) "^.....^",
           /* line */ (const char *) " .M.|. ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^   ",
           /* line */ (const char *) " .   ",
           /* line */ (const char *) " .   ",
           /* line */ (const char *) " .   ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) "^... ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " ...^",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) "  .  ",
           /* line */ (const char *) "  .  ",
           /* line */ (const char *) "  .  ",
           /* line */ (const char *) "  ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^     ",
           /* line */ (const char *) "   .     ",
           /* line */ (const char *) "   .     ",
           /* line */ (const char *) "   ..... ",
           /* line */ (const char *) "   ...m. ",
           /* line */ (const char *) "^...x...^",
           /* line */ (const char *) "   ..... ",
           /* line */ (const char *) "     .   ",
           /* line */ (const char *) "     ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^    ",
           /* line */ (const char *) "   .    ",
           /* line */ (const char *) " ......^",
           /* line */ (const char *) "^.x.|.  ",
           /* line */ (const char *) " .....  ",
           /* line */ (const char *) "  .     ",
           /* line */ (const char *) "  .     ",
           /* line */ (const char *) "  ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^   ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " .g. ",
           /* line */ (const char *) " ...^",
           /* line */ (const char *) "^.g. ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) "  .  ",
           /* line */ (const char *) "  ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "$. ^   ",
           /* line */ (const char *) "..|...^",
           /* line */ (const char *) " |.... ",
           /* line */ (const char *) "^..|.. ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "  ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^  ",
           /* line */ (const char *) "^.... ",
           /* line */ (const char *) " ..m.^",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) " ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^  ",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) " .x.x.^",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "  ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "        ^   ",
           /* line */ (const char *) "        .   ",
           /* line */ (const char *) "     xx...  ",
           /* line */ (const char *) "     x....  ",
           /* line */ (const char *) "^......x...^",
           /* line */ (const char *) "     .....  ",
           /* line */ (const char *) "     .....  ",
           /* line */ (const char *) "     .      ",
           /* line */ (const char *) "     ^      ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^    ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "^....^",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) " ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^   ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "    ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^      ",
           /* line */ (const char *) "   .      ",
           /* line */ (const char *) "   .      ",
           /* line */ (const char *) "   ......^",
           /* line */ (const char *) "   ....   ",
           /* line */ (const char *) "^......   ",
           /* line */ (const char *) "   ....   ",
           /* line */ (const char *) "     .    ",
           /* line */ (const char *) "     ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^     ",
           /* line */ (const char *) "  .     ",
           /* line */ (const char *) "  .     ",
           /* line */ (const char *) " .....  ",
           /* line */ (const char *) "^..m..  ",
           /* line */ (const char *) " ......^",
           /* line */ (const char *) " .....  ",
           /* line */ (const char *) " .      ",
           /* line */ (const char *) " .      ",
           /* line */ (const char *) " ^      ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^    ",
           /* line */ (const char *) "   .    ",
           /* line */ (const char *) "  ...   ",
           /* line */ (const char *) "  .....^",
           /* line */ (const char *) "^....   ",
           /* line */ (const char *) "  ...   ",
           /* line */ (const char *) "  ...   ",
           /* line */ (const char *) "   .    ",
           /* line */ (const char *) "   .    ",
           /* line */ (const char *) "   ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^     ",
           /* line */ (const char *) "    .     ",
           /* line */ (const char *) "    .     ",
           /* line */ (const char *) "    .     ",
           /* line */ (const char *) "  .....   ",
           /* line */ (const char *) "  .....   ",
           /* line */ (const char *) "^........^",
           /* line */ (const char *) "  .....   ",
           /* line */ (const char *) "   ^      ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^   ",
           /* line */ (const char *) "    .   ",
           /* line */ (const char *) " .....  ",
           /* line */ (const char *) "^...g.  ",
           /* line */ (const char *) " `.....^",
           /* line */ (const char *) " ``.g.  ",
           /* line */ (const char *) "```...  ",
           /* line */ (const char *) "m``.    ",
           /* line */ (const char *) "   .    ",
           /* line */ (const char *) "   ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^   ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " .|. ",
           /* line */ (const char *) "^...^",
           /* line */ (const char *) " .|. ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) "  ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^      ",
           /* line */ (const char *) "   .      ",
           /* line */ (const char *) "^........^",
           /* line */ (const char *) "   ....   ",
           /* line */ (const char *) "   ..x.   ",
           /* line */ (const char *) "   ....   ",
           /* line */ (const char *) "     ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^  ",
           /* line */ (const char *) " xx..^",
           /* line */ (const char *) " x... ",
           /* line */ (const char *) "^..x. ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "   ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^   ",
           /* line */ (const char *) "    .   ",
           /* line */ (const char *) "  .....^",
           /* line */ (const char *) "^...g.  ",
           /* line */ (const char *) "  ....  ",
           /* line */ (const char *) "  .     ",
           /* line */ (const char *) "  ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^   ",
           /* line */ (const char *) "^... ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " .x. ",
           /* line */ (const char *) " ...^",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^   ",
           /* line */ (const char *) " ..xx ",
           /* line */ (const char *) " ...x ",
           /* line */ (const char *) "^.x.. ",
           /* line */ (const char *) " ....^",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "   ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^   ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " .|.x. ",
           /* line */ (const char *) "^.....^",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "  .    ",
           /* line */ (const char *) "  ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^   ",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) " ..g..^",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "    ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^  ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " .g. ",
           /* line */ (const char *) "^...^",
           /* line */ (const char *) " .m. ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) "  ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^   ",
           /* line */ (const char *) "     .   ",
           /* line */ (const char *) "    ....^",
           /* line */ (const char *) "    ...  ",
           /* line */ (const char *) "^....m.  ",
           /* line */ (const char *) "    ...  ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^   ",
           /* line */ (const char *) " xx... ",
           /* line */ (const char *) " x..x.^",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "^..|.. ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "  ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^   ",
           /* line */ (const char *) "   .   ",
           /* line */ (const char *) "^....  ",
           /* line */ (const char *) " .x...^",
           /* line */ (const char *) " ....  ",
           /* line */ (const char *) " CC..  ",
           /* line */ (const char *) "..C..  ",
           /* line */ (const char *) "m. ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^  ",
           /* line */ (const char *) "    .  ",
           /* line */ (const char *) "    .  ",
           /* line */ (const char *) "^.....^",
           /* line */ (const char *) " ...xx ",
           /* line */ (const char *) " ..xxx ",
           /* line */ (const char *) " ..xxx ",
           /* line */ (const char *) "  .    ",
           /* line */ (const char *) "  ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^     ",
           /* line */ (const char *) " .     ",
           /* line */ (const char *) " .     ",
           /* line */ (const char *) " . ``$ ",
           /* line */ (const char *) "^..``` ",
           /* line */ (const char *) " ..``  ",
           /* line */ (const char *) " ...`  ",
           /* line */ (const char *) " m....^",
           /* line */ (const char *) " ....  ",
           /* line */ (const char *) " .     ",
           /* line */ (const char *) " ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^      ",
           /* line */ (const char *) "  ......^",
           /* line */ (const char *) "^..x.g.  ",
           /* line */ (const char *) "  .....  ",
           /* line */ (const char *) "   ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^    ",
           /* line */ (const char *) "   .    ",
           /* line */ (const char *) "  ..... ",
           /* line */ (const char *) "^......^",
           /* line */ (const char *) "  ..... ",
           /* line */ (const char *) "   .    ",
           /* line */ (const char *) "   ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^  ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "^..m. ",
           /* line */ (const char *) " ....^",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "   ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^    ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) "^.x.m. ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^    ",
           /* line */ (const char *) "  .    ",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) " ...|.^",
           /* line */ (const char *) " .|... ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "  ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^   ",
           /* line */ (const char *) "^.....^",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "  ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^  ",
           /* line */ (const char *) " xx..^",
           /* line */ (const char *) " x... ",
           /* line */ (const char *) "^..x. ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) " ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^    ",
           /* line */ (const char *) " .    ",
           /* line */ (const char *) " ...  ",
           /* line */ (const char *) "^.m..^",
           /* line */ (const char *) " ...  ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^   ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) "^... ",
           /* line */ (const char *) " ...^",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) "  ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^      ",
           /* line */ (const char *) "  .      ",
           /* line */ (const char *) "  ....   ",
           /* line */ (const char *) "  ......^",
           /* line */ (const char *) "  .xx.   ",
           /* line */ (const char *) "^..xx.   ",
           /* line */ (const char *) "  ....   ",
           /* line */ (const char *) "  .      ",
           /* line */ (const char *) "  .      ",
           /* line */ (const char *) "  ^      ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^   ",
           /* line */ (const char *) " ....^",
           /* line */ (const char *) "^.|.. ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) " ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^  ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) "^... ",
           /* line */ (const char *) " .x.^",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) "  ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^   ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) "^.m.^",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) "  ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^  ",
           /* line */ (const char *) " ....^",
           /* line */ (const char *) "^..m. ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) " ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^   ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " .g.^",
           /* line */ (const char *) "^... ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^    ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "^.....^",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^   ",
           /* line */ (const char *) " ...  ",
           /* line */ (const char *) " ....^",
           /* line */ (const char *) "^...  ",
           /* line */ (const char *) " ...  ",
           /* line */ (const char *) " .    ",
           /* line */ (const char *) " .    ",
           /* line */ (const char *) " ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^    ",
           /* line */ (const char *) " .    ",
           /* line */ (const char *) " ....^",
           /* line */ (const char *) " .|.  ",
           /* line */ (const char *) " ...  ",
           /* line */ (const char *) "^.G.  ",
           /* line */ (const char *) " ...  ",
           /* line */ (const char *) "  .   ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^  ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) "^.m. ",
           /* line */ (const char *) " ...^",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) "  ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^   ",
           /* line */ (const char *) "^.... ",
           /* line */ (const char *) " ..g.^",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) " ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "      ^  ",
           /* line */ (const char *) "^....... ",
           /* line */ (const char *) "   ..... ",
           /* line */ (const char *) "   .g.|.^",
           /* line */ (const char *) "   ..... ",
           /* line */ (const char *) "   ..... ",
           /* line */ (const char *) "   ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^  ",
           /* line */ (const char *) "     .  ",
           /* line */ (const char *) "^...... ",
           /* line */ (const char *) "   .g..^",
           /* line */ (const char *) "   .... ",
           /* line */ (const char *) "   .    ",
           /* line */ (const char *) "   .    ",
           /* line */ (const char *) "   .    ",
           /* line */ (const char *) "   ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^  ",
           /* line */ (const char *) "^... ",
           /* line */ (const char *) " ...^",
           /* line */ (const char *) " .|. ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^   ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " ...^",
           /* line */ (const char *) "^... ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^  ",
           /* line */ (const char *) "^... ",
           /* line */ (const char *) " .x.^",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^  `C",
           /* line */ (const char *) " .````",
           /* line */ (const char *) "^..```",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) " .x..^",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^   ",
           /* line */ (const char *) "^....^",
           /* line */ (const char *) " .xx. ",
           /* line */ (const char *) " .xx. ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) " ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^   ",
           /* line */ (const char *) "   .   ",
           /* line */ (const char *) "   .   ",
           /* line */ (const char *) "  ....^",
           /* line */ (const char *) "^....  ",
           /* line */ (const char *) "  .g.  ",
           /* line */ (const char *) "  ...  ",
           /* line */ (const char *) "  .    ",
           /* line */ (const char *) "  ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^      ",
           /* line */ (const char *) "^........^",
           /* line */ (const char *) " ...x..   ",
           /* line */ (const char *) " ......   ",
           /* line */ (const char *) " ..|...   ",
           /* line */ (const char *) " .....    ",
           /* line */ (const char *) "     ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^   ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) "^.x..  ",
           /* line */ (const char *) " ....  ",
           /* line */ (const char *) " ....  ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^   ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "^..|..^",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "    ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^     ",
           /* line */ (const char *) "  .     ",
           /* line */ (const char *) "^......^",
           /* line */ (const char *) "  ..... ",
           /* line */ (const char *) "  ..... ",
           /* line */ (const char *) "  ..... ",
           /* line */ (const char *) "     ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^    ",
           /* line */ (const char *) "^.....^",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "  ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^  ",
           /* line */ (const char *) "   .  ",
           /* line */ (const char *) "   .  ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "^..M.^",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) " .    ",
           /* line */ (const char *) " ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^    ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) " ..|.^",
           /* line */ (const char *) "^.... ",
           /* line */ (const char *) " x... ",
           /* line */ (const char *) " xx.. ",
           /* line */ (const char *) "   ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^  ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^   ",
           /* line */ (const char *) " ....  ",
           /* line */ (const char *) "^.m...^",
           /* line */ (const char *) " ....  ",
           /* line */ (const char *) "   .   ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^     ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) "^.x.m. ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "    ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^   ",
           /* line */ (const char *) " .   ",
           /* line */ (const char *) " .   ",
           /* line */ (const char *) " ...^",
           /* line */ (const char *) " .x. ",
           /* line */ (const char *) "^... ",
           /* line */ (const char *) " .m. ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^   ",
           /* line */ (const char *) "    .   ",
           /* line */ (const char *) "   ...  ",
           /* line */ (const char *) "^...|.  ",
           /* line */ (const char *) "   ....^",
           /* line */ (const char *) "   ...  ",
           /* line */ (const char *) "    .   ",
           /* line */ (const char *) "    ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^  ",
           /* line */ (const char *) "^... ",
           /* line */ (const char *) " .g. ",
           /* line */ (const char *) " ...^",
           /* line */ (const char *) " .m. ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " .   ",
           /* line */ (const char *) " ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^   ",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) " .xxx. ",
           /* line */ (const char *) " .xxx.^",
           /* line */ (const char *) " .xxx. ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "  ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^    ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) "^..|.. ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^    ",
           /* line */ (const char *) " ....^",
           /* line */ (const char *) "^..xx ",
           /* line */ (const char *) " .xxx ",
           /* line */ (const char *) " .xxx ",
           /* line */ (const char *) " ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^   ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) "^...^",
           /* line */ (const char *) " .|. ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) "  ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^   ",
           /* line */ (const char *) "     .   ",
           /* line */ (const char *) "     .   ",
           /* line */ (const char *) "     .   ",
           /* line */ (const char *) "  .....  ",
           /* line */ (const char *) "  .x.g.  ",
           /* line */ (const char *) "  .....  ",
           /* line */ (const char *) "^..g.x..^",
           /* line */ (const char *) "  .....  ",
           /* line */ (const char *) "   ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^    ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) " .xx.^",
           /* line */ (const char *) "^.xx. ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "   ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^      ",
           /* line */ (const char *) "  .      ",
           /* line */ (const char *) "  ......^",
           /* line */ (const char *) "  ...x.  ",
           /* line */ (const char *) "^..g.... ",
           /* line */ (const char *) "  ....m. ",
           /* line */ (const char *) "  ...... ",
           /* line */ (const char *) "   ..... ",
           /* line */ (const char *) "   ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^   ",
           /* line */ (const char *) "  .   ",
           /* line */ (const char *) "  .   ",
           /* line */ (const char *) "  .   ",
           /* line */ (const char *) "  .   ",
           /* line */ (const char *) "  ... ",
           /* line */ (const char *) "^....^",
           /* line */ (const char *) "  ... ",
           /* line */ (const char *) "  .   ",
           /* line */ (const char *) "  .   ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^      ",
           /* line */ (const char *) "   .      ",
           /* line */ (const char *) " .....    ",
           /* line */ (const char *) "^.g.x....^",
           /* line */ (const char *) " .....    ",
           /* line */ (const char *) "  .       ",
           /* line */ (const char *) "  ^       ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^  ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " .x.^",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) "^.m. ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^  ",
           /* line */ (const char *) "^.....^",
           /* line */ (const char *) " ..x.. ",
           /* line */ (const char *) " ....x ",
           /* line */ (const char *) " ...xx ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^  ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " .m. ",
           /* line */ (const char *) "^... ",
           /* line */ (const char *) " .M.^",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^    ",
           /* line */ (const char *) "^.... ",
           /* line */ (const char *) " `...^",
           /* line */ (const char *) " ``.. ",
           /* line */ (const char *) "```.. ",
           /* line */ (const char *) "m``^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^    ",
           /* line */ (const char *) "  .    ",
           /* line */ (const char *) "  .    ",
           /* line */ (const char *) "^.....^",
           /* line */ (const char *) "  .|.  ",
           /* line */ (const char *) "  ...  ",
           /* line */ (const char *) "  .|.  ",
           /* line */ (const char *) "  ...  ",
           /* line */ (const char *) "  .    ",
           /* line */ (const char *) "  ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^   ",
           /* line */ (const char *) "^... ",
           /* line */ (const char *) " .m.^",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) "  ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^    ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) " ....^",
           /* line */ (const char *) "^.x.. ",
           /* line */ (const char *) " ...x ",
           /* line */ (const char *) " ..xx ",
           /* line */ (const char *) " ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^  ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) "^.|.^",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) "  ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^   ",
           /* line */ (const char *) "^.... ",
           /* line */ (const char *) " ....^",
           /* line */ (const char *) " ..x. ",
           /* line */ (const char *) " x... ",
           /* line */ (const char *) " xx.. ",
           /* line */ (const char *) "   ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^  `m",
           /* line */ (const char *) " .````",
           /* line */ (const char *) " ..```",
           /* line */ (const char *) "^....^",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^   ",
           /* line */ (const char *) "    ....^",
           /* line */ (const char *) "^....|.. ",
           /* line */ (const char *) "    .... ",
           /* line */ (const char *) "     .   ",
           /* line */ (const char *) "     .   ",
           /* line */ (const char *) "     ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^   ",
           /* line */ (const char *) "     .   ",
           /* line */ (const char *) "^......  ",
           /* line */ (const char *) "   .....^",
           /* line */ (const char *) "   ....  ",
           /* line */ (const char *) "     .   ",
           /* line */ (const char *) "     .   ",
           /* line */ (const char *) "     ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^   ",
           /* line */ (const char *) " ..xx ",
           /* line */ (const char *) "^...x ",
           /* line */ (const char *) " .x..^",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) " ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^     ",
           /* line */ (const char *) "   .....  ",
           /* line */ (const char *) "^...x.x..^",
           /* line */ (const char *) "   .....  ",
           /* line */ (const char *) "      .   ",
           /* line */ (const char *) "      ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^   ",
           /* line */ (const char *) " xx... ",
           /* line */ (const char *) " x..x.^",
           /* line */ (const char *) "^...x. ",
           /* line */ (const char *) " .xxx. ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^   ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "^.|.x. ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "  ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^   ",
           /* line */ (const char *) "^... ",
           /* line */ (const char *) " ...^",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^   ",
           /* line */ (const char *) " ...^",
           /* line */ (const char *) "^... ",
           /* line */ (const char *) " .|. ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) "  ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^      ",
           /* line */ (const char *) "  .      ",
           /* line */ (const char *) "  .      ",
           /* line */ (const char *) "^.....   ",
           /* line */ (const char *) " ..x....^",
           /* line */ (const char *) " .....   ",
           /* line */ (const char *) "    .    ",
           /* line */ (const char *) "    .    ",
           /* line */ (const char *) "    .    ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^     ",
           /* line */ (const char *) "  .     ",
           /* line */ (const char *) " ......^",
           /* line */ (const char *) "^..g.   ",
           /* line */ (const char *) " ....   ",
           /* line */ (const char *) " .      ",
           /* line */ (const char *) " .      ",
           /* line */ (const char *) " ^      ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^  ",
           /* line */ (const char *) "     .  ",
           /* line */ (const char *) "^...... ",
           /* line */ (const char *) "  .....^",
           /* line */ (const char *) "  ..... ",
           /* line */ (const char *) "  ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^  ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "^..m..^",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^   ",
           /* line */ (const char *) "     .   ",
           /* line */ (const char *) "     .   ",
           /* line */ (const char *) "   ....  ",
           /* line */ (const char *) "   .x...^",
           /* line */ (const char *) "^.....x  ",
           /* line */ (const char *) "   ..xx  ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^     ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) "^.x.   ",
           /* line */ (const char *) " ...   ",
           /* line */ (const char *) "  ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^  ",
           /* line */ (const char *) "  .  ",
           /* line */ (const char *) "  .  ",
           /* line */ (const char *) "^...^",
           /* line */ (const char *) " .g. ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) "  .  ",
           /* line */ (const char *) "  ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^     ",
           /* line */ (const char *) " .......^",
           /* line */ (const char *) " .....   ",
           /* line */ (const char *) " .....   ",
           /* line */ (const char *) "^.....   ",
           /* line */ (const char *) " .....   ",
           /* line */ (const char *) "    .    ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^  ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) "^... ",
           /* line */ (const char *) " .x.^",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^   ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) "^... ",
           /* line */ (const char *) " ...^",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) "  ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^    ",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) " .m.m. ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) " x..g. ",
           /* line */ (const char *) " xx... ",
           /* line */ (const char *) "    ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^    ",
           /* line */ (const char *) "^.... ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) " .x..^",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "   ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^  ",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^     ",
           /* line */ (const char *) "  .     ",
           /* line */ (const char *) "^.....  ",
           /* line */ (const char *) "  .M...^",
           /* line */ (const char *) "  ....  ",
           /* line */ (const char *) "   .    ",
           /* line */ (const char *) "   .    ",
           /* line */ (const char *) "   ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^     ",
           /* line */ (const char *) "    .     ",
           /* line */ (const char *) "    .     ",
           /* line */ (const char *) "    .....^",
           /* line */ (const char *) "^....g.   ",
           /* line */ (const char *) "    ...   ",
           /* line */ (const char *) "     ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^    ",
           /* line */ (const char *) "  .... ",
           /* line */ (const char *) "^.....^",
           /* line */ (const char *) "  .... ",
           /* line */ (const char *) "  .... ",
           /* line */ (const char *) "   .   ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^   ",
           /* line */ (const char *) "     .   ",
           /* line */ (const char *) " .....   ",
           /* line */ (const char *) " .m.....^",
           /* line */ (const char *) " ......  ",
           /* line */ (const char *) " ...x..  ",
           /* line */ (const char *) "^.....x  ",
           /* line */ (const char *) "  ...xx  ",
           /* line */ (const char *) "   .     ",
           /* line */ (const char *) "   .     ",
           /* line */ (const char *) "   ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^     ",
           /* line */ (const char *) "    .     ",
           /* line */ (const char *) "   ......^",
           /* line */ (const char *) "^.....`   ",
           /* line */ (const char *) "   ..``   ",
           /* line */ (const char *) "   ..```  ",
           /* line */ (const char *) "    ^``m  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^  ",
           /* line */ (const char *) " ...^",
           /* line */ (const char *) "^.|. ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) "  ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^   ",
           /* line */ (const char *) " ...^",
           /* line */ (const char *) "^.g. ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) "  ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^   ",
           /* line */ (const char *) "^... ",
           /* line */ (const char *) " .m.^",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^  ",
           /* line */ (const char *) "^...^",
           /* line */ (const char *) " .|. ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^   ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) " ..|.^",
           /* line */ (const char *) "^.... ",
           /* line */ (const char *) " CC.. ",
           /* line */ (const char *) "..C.. ",
           /* line */ (const char *) "m. ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^   ",
           /* line */ (const char *) "    .   ",
           /* line */ (const char *) "^.....  ",
           /* line */ (const char *) "   .g.  ",
           /* line */ (const char *) "   ...  ",
           /* line */ (const char *) "   .g..^",
           /* line */ (const char *) "   ...  ",
           /* line */ (const char *) "   .    ",
           /* line */ (const char *) "   ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^    ",
           /* line */ (const char *) "  .    ",
           /* line */ (const char *) "^....  ",
           /* line */ (const char *) " ....  ",
           /* line */ (const char *) " ..x..^",
           /* line */ (const char *) " ....  ",
           /* line */ (const char *) " ....  ",
           /* line */ (const char *) "  .    ",
           /* line */ (const char *) "  ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^    ",
           /* line */ (const char *) "   .    ",
           /* line */ (const char *) "   .    ",
           /* line */ (const char *) "   .    ",
           /* line */ (const char *) " xx...  ",
           /* line */ (const char *) " x..x..^",
           /* line */ (const char *) " ..x..  ",
           /* line */ (const char *) "^.x...  ",
           /* line */ (const char *) " .....  ",
           /* line */ (const char *) " .      ",
           /* line */ (const char *) " .      ",
           /* line */ (const char *) " ^      ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^       ",
           /* line */ (const char *) " .       ",
           /* line */ (const char *) " .       ",
           /* line */ (const char *) " .       ",
           /* line */ (const char *) "^..xx    ",
           /* line */ (const char *) " ...x    ",
           /* line */ (const char *) " ....    ",
           /* line */ (const char *) " ..m....^",
           /* line */ (const char *) " ....    ",
           /* line */ (const char *) "  ^      ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^     ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "^.xx..^",
           /* line */ (const char *) " .xx.. ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^   ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) "^.g.^",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) "  ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^     ",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) " .x.m.^",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "  ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^     ",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) " .xxx. ",
           /* line */ (const char *) " .xxx. ",
           /* line */ (const char *) " .xxx.^",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^   ",
           /* line */ (const char *) "  .   ",
           /* line */ (const char *) "  .   ",
           /* line */ (const char *) "  .   ",
           /* line */ (const char *) "^....^",
           /* line */ (const char *) " ...  ",
           /* line */ (const char *) " ...  ",
           /* line */ (const char *) " ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^    ",
           /* line */ (const char *) "   .    ",
           /* line */ (const char *) "^......^",
           /* line */ (const char *) "  .m.   ",
           /* line */ (const char *) "  ...   ",
           /* line */ (const char *) "   .    ",
           /* line */ (const char *) "   .    ",
           /* line */ (const char *) "   ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^  ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "^..x.^",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) " ..g. ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "   ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^   ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) "^.m.^",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^    ",
           /* line */ (const char *) "   .    ",
           /* line */ (const char *) "^.....  ",
           /* line */ (const char *) "   .g..^",
           /* line */ (const char *) "   ...  ",
           /* line */ (const char *) "    .   ",
           /* line */ (const char *) "    ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^      ",
           /* line */ (const char *) "   .      ",
           /* line */ (const char *) "^......   ",
           /* line */ (const char *) "  .......^",
           /* line */ (const char *) "  .....   ",
           /* line */ (const char *) "     .    ",
           /* line */ (const char *) "     ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^      ",
           /* line */ (const char *) "^.......   ",
           /* line */ (const char *) "   .m.|...^",
           /* line */ (const char *) "   .....   ",
           /* line */ (const char *) "   .       ",
           /* line */ (const char *) "   ^       ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^    ",
           /* line */ (const char *) " ...   ",
           /* line */ (const char *) " .g.   ",
           /* line */ (const char *) "^.....^",
           /* line */ (const char *) " ...   ",
           /* line */ (const char *) " .     ",
           /* line */ (const char *) " ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^   ",
           /* line */ (const char *) "   .   ",
           /* line */ (const char *) "   .   ",
           /* line */ (const char *) "   ... ",
           /* line */ (const char *) "^...m.^",
           /* line */ (const char *) "   ... ",
           /* line */ (const char *) "   .   ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^    ",
           /* line */ (const char *) "^....^",
           /* line */ (const char *) " .x.. ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "   ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^   ",
           /* line */ (const char *) "   .   ",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) " x.x.. ",
           /* line */ (const char *) " x.... ",
           /* line */ (const char *) " xxx.. ",
           /* line */ (const char *) "    ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^   ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) "^.|. ",
           /* line */ (const char *) " ...^",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) "  ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^  .$",
           /* line */ (const char *) " ..|..",
           /* line */ (const char *) "^...| ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) " ..x.^",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "  .   ",
           /* line */ (const char *) "  .   ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^    ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) "^.x.m. ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^     ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^   ",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) " .m.m.^",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^   ",
           /* line */ (const char *) "  .   ",
           /* line */ (const char *) "  .   ",
           /* line */ (const char *) "  ...^",
           /* line */ (const char *) "^.... ",
           /* line */ (const char *) "  ... ",
           /* line */ (const char *) "  ... ",
           /* line */ (const char *) "   ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^   ",
           /* line */ (const char *) "   .   ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) " ...`  ",
           /* line */ (const char *) "^..``  ",
           /* line */ (const char *) " ..``` ",
           /* line */ (const char *) " . ``C ",
           /* line */ (const char *) " .     ",
           /* line */ (const char *) " ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^      ",
           /* line */ (const char *) "^........^",
           /* line */ (const char *) "   ....   ",
           /* line */ (const char *) "   ....   ",
           /* line */ (const char *) "     .    ",
           /* line */ (const char *) "     .    ",
           /* line */ (const char *) "     ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^   ",
           /* line */ (const char *) " .   ",
           /* line */ (const char *) " .   ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " .|.^",
           /* line */ (const char *) "^... ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " .   ",
           /* line */ (const char *) " .   ",
           /* line */ (const char *) " ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^    ",
           /* line */ (const char *) "  .    ",
           /* line */ (const char *) "  ...  ",
           /* line */ (const char *) "  .x.  ",
           /* line */ (const char *) "^....  ",
           /* line */ (const char *) "  .g..^",
           /* line */ (const char *) "  ...  ",
           /* line */ (const char *) "  .    ",
           /* line */ (const char *) "  .    ",
           /* line */ (const char *) "  ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^    ",
           /* line */ (const char *) "    .    ",
           /* line */ (const char *) "    .    ",
           /* line */ (const char *) "  ......^",
           /* line */ (const char *) "^......  ",
           /* line */ (const char *) "  .....  ",
           /* line */ (const char *) "  ^      ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^    ",
           /* line */ (const char *) "    .    ",
           /* line */ (const char *) "^.....   ",
           /* line */ (const char *) " .x...   ",
           /* line */ (const char *) " ...m...^",
           /* line */ (const char *) " .....   ",
           /* line */ (const char *) "    .    ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^   ",
           /* line */ (const char *) "^.....  ",
           /* line */ (const char *) " .m.x..^",
           /* line */ (const char *) " .....  ",
           /* line */ (const char *) "    ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^      ",
           /* line */ (const char *) "  .      ",
           /* line */ (const char *) "^......  ",
           /* line */ (const char *) "  .....  ",
           /* line */ (const char *) "  ..x...^",
           /* line */ (const char *) "  ....x  ",
           /* line */ (const char *) "  ...xx  ",
           /* line */ (const char *) "  .      ",
           /* line */ (const char *) "  ^      ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^  ",
           /* line */ (const char *) " ...^",
           /* line */ (const char *) "^... ",
           /* line */ (const char *) " .m. ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^    ",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) " .g...^",
           /* line */ (const char *) " ...|. ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "    ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^   ",
           /* line */ (const char *) "   .   ",
           /* line */ (const char *) "   .   ",
           /* line */ (const char *) "^....  ",
           /* line */ (const char *) "  ...  ",
           /* line */ (const char *) "  .x.  ",
           /* line */ (const char *) "  ....^",
           /* line */ (const char *) "  ...  ",
           /* line */ (const char *) "   .   ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^     ",
           /* line */ (const char *) "^.....^",
           /* line */ (const char *) " .|.m. ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "  ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^   ",
           /* line */ (const char *) "  ....  ",
           /* line */ (const char *) "^.....  ",
           /* line */ (const char *) "  .x...^",
           /* line */ (const char *) "  ....  ",
           /* line */ (const char *) "    ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^   ",
           /* line */ (const char *) "^.... ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) " ....^",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) " ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^     ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) " .x... ",
           /* line */ (const char *) "^...m. ",
           /* line */ (const char *) " .x... ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^   ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "  ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^    ",
           /* line */ (const char *) "^.... ",
           /* line */ (const char *) " ....^",
           /* line */ (const char *) " ..x. ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "   ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^     ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " ...g.^",
           /* line */ (const char *) "^.|... ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^   ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " ..|.. ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) "^.m.m. ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^   ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) "^... ",
           /* line */ (const char *) " ...^",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) "  ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^    ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "^.|..^",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^    ",
           /* line */ (const char *) "    .    ",
           /* line */ (const char *) "^.....   ",
           /* line */ (const char *) "  .m....^",
           /* line */ (const char *) "  ....   ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^  .$",
           /* line */ (const char *) " ..|..",
           /* line */ (const char *) "^...| ",
           /* line */ (const char *) " .g..^",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "   ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^    ",
           /* line */ (const char *) "^.... ",
           /* line */ (const char *) " .|.. ",
           /* line */ (const char *) " ....^",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "   ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^  ",
           /* line */ (const char *) "    .  ",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) "   .x.^",
           /* line */ (const char *) "   ... ",
           /* line */ (const char *) "   .   ",
           /* line */ (const char *) "   .   ",
           /* line */ (const char *) "   .   ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^   ",
           /* line */ (const char *) "^.... ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) " ....^",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) " ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^   ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) "^..x.. ",
           /* line */ (const char *) " x.... ",
           /* line */ (const char *) " xx... ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^  ",
           /* line */ (const char *) "    .  ",
           /* line */ (const char *) "   ... ",
           /* line */ (const char *) "   ...^",
           /* line */ (const char *) "^...x. ",
           /* line */ (const char *) "   ... ",
           /* line */ (const char *) "   .   ",
           /* line */ (const char *) "   .   ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^     ",
           /* line */ (const char *) "^....  ",
           /* line */ (const char *) " ..m..^",
           /* line */ (const char *) " x...  ",
           /* line */ (const char *) " xx..  ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^    ",
           /* line */ (const char *) "  .    ",
           /* line */ (const char *) "  .    ",
           /* line */ (const char *) "^.....^",
           /* line */ (const char *) "  ...  ",
           /* line */ (const char *) "  ...  ",
           /* line */ (const char *) "   .   ",
           /* line */ (const char *) "   .   ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^      ",
           /* line */ (const char *) "  .      ",
           /* line */ (const char *) "  ...    ",
           /* line */ (const char *) "^..g....^",
           /* line */ (const char *) "  ...    ",
           /* line */ (const char *) "  ^      ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^   ",
           /* line */ (const char *) "^... ",
           /* line */ (const char *) " .m. ",
           /* line */ (const char *) " ...^",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) "  ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^   ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) "^..x.. ",
           /* line */ (const char *) " ....x ",
           /* line */ (const char *) " ...xx ",
           /* line */ (const char *) "  ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^     ",
           /* line */ (const char *) "  .     ",
           /* line */ (const char *) "  .     ",
           /* line */ (const char *) "  .     ",
           /* line */ (const char *) "  ...   ",
           /* line */ (const char *) "  .....^",
           /* line */ (const char *) "^....   ",
           /* line */ (const char *) "  ...   ",
           /* line */ (const char *) "   .    ",
           /* line */ (const char *) "   ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^      ",
           /* line */ (const char *) "   .      ",
           /* line */ (const char *) "^......   ",
           /* line */ (const char *) "   .G....^",
           /* line */ (const char *) "   ....   ",
           /* line */ (const char *) "   ....   ",
           /* line */ (const char *) "     .    ",
           /* line */ (const char *) "     .    ",
           /* line */ (const char *) "     ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^  ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " ..x.. ",
           /* line */ (const char *) " ..x.. ",
           /* line */ (const char *) "^.xxx.^",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^   ",
           /* line */ (const char *) "    .   ",
           /* line */ (const char *) "    .   ",
           /* line */ (const char *) " .....  ",
           /* line */ (const char *) " .....  ",
           /* line */ (const char *) "^......^",
           /* line */ (const char *) " .....  ",
           /* line */ (const char *) "   ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^      ",
           /* line */ (const char *) "   .      ",
           /* line */ (const char *) "^......   ",
           /* line */ (const char *) "  .......^",
           /* line */ (const char *) "  .....   ",
           /* line */ (const char *) "  .....   ",
           /* line */ (const char *) "     ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^   ",
           /* line */ (const char *) "   .   ",
           /* line */ (const char *) "   .   ",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) "   .g.^",
           /* line */ (const char *) "   ... ",
           /* line */ (const char *) "   ... ",
           /* line */ (const char *) "    .  ",
           /* line */ (const char *) "    ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^   ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "^.x...^",
           /* line */ (const char *) " ...|. ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "    ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^        ",
           /* line */ (const char *) "   .        ",
           /* line */ (const char *) "   .        ",
           /* line */ (const char *) " .....      ",
           /* line */ (const char *) " ..xx.      ",
           /* line */ (const char *) "^..xx......^",
           /* line */ (const char *) " .....      ",
           /* line */ (const char *) " ^          ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^   ",
           /* line */ (const char *) "^.... ",
           /* line */ (const char *) " ..g.^",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^   ",
           /* line */ (const char *) "^....^",
           /* line */ (const char *) " ..g. ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) " ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^   ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " .g.m. ",
           /* line */ (const char *) "^.....^",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^    ",
           /* line */ (const char *) "    .    ",
           /* line */ (const char *) "    .    ",
           /* line */ (const char *) "^.....   ",
           /* line */ (const char *) "  ....   ",
           /* line */ (const char *) "  ......^",
           /* line */ (const char *) "  ....   ",
           /* line */ (const char *) "   ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^   ",
           /* line */ (const char *) "  .   ",
           /* line */ (const char *) "^....^",
           /* line */ (const char *) "  ... ",
           /* line */ (const char *) "  ... ",
           /* line */ (const char *) "  ... ",
           /* line */ (const char *) "   ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^    ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "^....^",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^      ",
           /* line */ (const char *) " .      ",
           /* line */ (const char *) " .      ",
           /* line */ (const char *) "^......^",
           /* line */ (const char *) " ..m.   ",
           /* line */ (const char *) " ....   ",
           /* line */ (const char *) "  .     ",
           /* line */ (const char *) "  ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^    ",
           /* line */ (const char *) "^......^",
           /* line */ (const char *) "  ..|.  ",
           /* line */ (const char *) "  ....  ",
           /* line */ (const char *) "    ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^  ",
           /* line */ (const char *) " ...^",
           /* line */ (const char *) "^... ",
           /* line */ (const char *) " .x. ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^   ",
           /* line */ (const char *) "  ...^",
           /* line */ (const char *) "^..g. ",
           /* line */ (const char *) "  ... ",
           /* line */ (const char *) "  .   ",
           /* line */ (const char *) "  .   ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^   ",
           /* line */ (const char *) " ...^",
           /* line */ (const char *) "^.m. ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) "  ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^       ",
           /* line */ (const char *) "   ....    ",
           /* line */ (const char *) "^......    ",
           /* line */ (const char *) "   ..g....^",
           /* line */ (const char *) "   .....   ",
           /* line */ (const char *) "    . .m   ",
           /* line */ (const char *) "    ^      ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^   ",
           /* line */ (const char *) " ....^",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) " ..xx ",
           /* line */ (const char *) "^.xxx ",
           /* line */ (const char *) " .xxx ",
           /* line */ (const char *) " ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^   ",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^  ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "^....^",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^   ",
           /* line */ (const char *) "   .   ",
           /* line */ (const char *) "  ....^",
           /* line */ (const char *) "  .|.  ",
           /* line */ (const char *) "  ...  ",
           /* line */ (const char *) "^..|.  ",
           /* line */ (const char *) "  ...  ",
           /* line */ (const char *) "   .   ",
           /* line */ (const char *) "   .   ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^    ",
           /* line */ (const char *) " .    ",
           /* line */ (const char *) " .    ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "^.... ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) " ....^",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) " .    ",
           /* line */ (const char *) " .    ",
           /* line */ (const char *) " ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^   ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) "^.|.g. ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^     ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "  ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^     ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) "^..x.. ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^     ",
           /* line */ (const char *) "   ....   ",
           /* line */ (const char *) "   ....   ",
           /* line */ (const char *) "^...x....^",
           /* line */ (const char *) "   ...x   ",
           /* line */ (const char *) "   ..xx   ",
           /* line */ (const char *) "   ^      ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^  ",
           /* line */ (const char *) "^....^",
           /* line */ (const char *) " ..x. ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) " ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^  ",
           /* line */ (const char *) "   .  ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "^.... ",
           /* line */ (const char *) " ..M. ",
           /* line */ (const char *) " x...^",
           /* line */ (const char *) " xx.. ",
           /* line */ (const char *) "   ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^     ",
           /* line */ (const char *) "^.....^",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "  ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^     ",
           /* line */ (const char *) "    ...   ",
           /* line */ (const char *) "^....g...^",
           /* line */ (const char *) "    ...   ",
           /* line */ (const char *) "     ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^    ",
           /* line */ (const char *) "   .    ",
           /* line */ (const char *) "^.....  ",
           /* line */ (const char *) " ..m..  ",
           /* line */ (const char *) " .....  ",
           /* line */ (const char *) " ..G...^",
           /* line */ (const char *) " .....  ",
           /* line */ (const char *) "   .    ",
           /* line */ (const char *) "   .    ",
           /* line */ (const char *) "   ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^   ",
           /* line */ (const char *) "^...... ",
           /* line */ (const char *) "    ... ",
           /* line */ (const char *) "    .M. ",
           /* line */ (const char *) "    ...^",
           /* line */ (const char *) "    ... ",
           /* line */ (const char *) "     ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^       ",
           /* line */ (const char *) " .   .$  ",
           /* line */ (const char *) " ...|..  ",
           /* line */ (const char *) " .m..|   ",
           /* line */ (const char *) "^.......^",
           /* line */ (const char *) " .....   ",
           /* line */ (const char *) "    .    ",
           /* line */ (const char *) "    .    ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^  ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " .G.^",
           /* line */ (const char *) "^... ",
           /* line */ (const char *) " .x. ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^  ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "^..m..^",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "  ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^   ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) "^.|. ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " .g.^",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) "  ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^   ",
           /* line */ (const char *) "   .   ",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) "   .g.^",
           /* line */ (const char *) "   ... ",
           /* line */ (const char *) "    .  ",
           /* line */ (const char *) "    .  ",
           /* line */ (const char *) "    ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^   ",
           /* line */ (const char *) "     .   ",
           /* line */ (const char *) "   xx..  ",
           /* line */ (const char *) "   x...  ",
           /* line */ (const char *) "^.......^",
           /* line */ (const char *) "   ..m.  ",
           /* line */ (const char *) "   ....  ",
           /* line */ (const char *) "    .    ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^   ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) "^.M. ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " .m.^",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) "  ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^  ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) "^.x.^",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " .g. ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^  ",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) " ..x..^",
           /* line */ (const char *) " ....x ",
           /* line */ (const char *) " ...xx ",
           /* line */ (const char *) "  ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^   ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " .|. ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) "^.|.^",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^  ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) "^.x.^",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) "  ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^   ",
           /* line */ (const char *) "^... ",
           /* line */ (const char *) " .g.^",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^   ",
           /* line */ (const char *) " xx...^",
           /* line */ (const char *) " x.... ",
           /* line */ (const char *) "^..x.. ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^  ",
           /* line */ (const char *) "^.... ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) " ....^",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) " ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^   ",
           /* line */ (const char *) "     .   ",
           /* line */ (const char *) "  .....  ",
           /* line */ (const char *) "^..g.x..^",
           /* line */ (const char *) "  .....  ",
           /* line */ (const char *) "     .   ",
           /* line */ (const char *) "     .   ",
           /* line */ (const char *) "     ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^     ",
           /* line */ (const char *) "   .....^",
           /* line */ (const char *) "   ...   ",
           /* line */ (const char *) "^...|.   ",
           /* line */ (const char *) "   ...   ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^  ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) "^.|. ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " .x.^",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^   ",
           /* line */ (const char *) "^...^",
           /* line */ (const char *) " .m. ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) "  ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^    ",
           /* line */ (const char *) "  .....^",
           /* line */ (const char *) "^..x.   ",
           /* line */ (const char *) "  ...   ",
           /* line */ (const char *) "   .    ",
           /* line */ (const char *) "   ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^       ",
           /* line */ (const char *) " xx...     ",
           /* line */ (const char *) " x....     ",
           /* line */ (const char *) "^..x......^",
           /* line */ (const char *) " .....     ",
           /* line */ (const char *) "   .       ",
           /* line */ (const char *) "   ^       ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^  ",
           /* line */ (const char *) "^... ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " ...^",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) "  ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^   ",
           /* line */ (const char *) "     .   ",
           /* line */ (const char *) "  ......^",
           /* line */ (const char *) "^..xx..  ",
           /* line */ (const char *) "  .xx..  ",
           /* line */ (const char *) "  .....  ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^   ",
           /* line */ (const char *) " ...^",
           /* line */ (const char *) "^... ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^   ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "^..m.^",
           /* line */ (const char *) " .....",
           /* line */ (const char *) "   ^.m",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^  ",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) " .x...^",
           /* line */ (const char *) " ...M. ",
           /* line */ (const char *) " x.... ",
           /* line */ (const char *) " xx... ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "m. ^   ",
           /* line */ (const char *) "......^",
           /* line */ (const char *) "^..m...",
           /* line */ (const char *) " ....x.",
           /* line */ (const char *) " ......",
           /* line */ (const char *) "  ^....",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^     ",
           /* line */ (const char *) "  .     ",
           /* line */ (const char *) "  ...   ",
           /* line */ (const char *) "  .....^",
           /* line */ (const char *) "  ...   ",
           /* line */ (const char *) "^....   ",
           /* line */ (const char *) "  ...   ",
           /* line */ (const char *) "  ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^  ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " .g.^",
           /* line */ (const char *) "^... ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) "  ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^  ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) "^.|.|. ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "  ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^    ",
           /* line */ (const char *) " ....^",
           /* line */ (const char *) "^.g.. ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) " .x.. ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "   ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^    ",
           /* line */ (const char *) "   .    ",
           /* line */ (const char *) "   ....^",
           /* line */ (const char *) "^....x. ",
           /* line */ (const char *) "   .... ",
           /* line */ (const char *) "     .  ",
           /* line */ (const char *) "     ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^   ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "^.....^",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "  ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^    ",
           /* line */ (const char *) " ....^",
           /* line */ (const char *) "^..x. ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "   ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^   ",
           /* line */ (const char *) "     .   ",
           /* line */ (const char *) "  ......^",
           /* line */ (const char *) "^......  ",
           /* line */ (const char *) "  .....  ",
           /* line */ (const char *) "  .....  ",
           /* line */ (const char *) "     .   ",
           /* line */ (const char *) "     ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^      ",
           /* line */ (const char *) " .      ",
           /* line */ (const char *) " .      ",
           /* line */ (const char *) "^.....  ",
           /* line */ (const char *) " .....  ",
           /* line */ (const char *) " .....  ",
           /* line */ (const char *) " ......^",
           /* line */ (const char *) " .....  ",
           /* line */ (const char *) "   .    ",
           /* line */ (const char *) "   ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^   ",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) " .x.x.^",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^     ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "^.....^",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^``$",
           /* line */ (const char *) " ...```",
           /* line */ (const char *) "^.m.`` ",
           /* line */ (const char *) " ....` ",
           /* line */ (const char *) " .m...^",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^    ",
           /* line */ (const char *) " ....^",
           /* line */ (const char *) "^..m. ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) " ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^  ",
           /* line */ (const char *) "^....^",
           /* line */ (const char *) " .|.. ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "   ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^  ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " ...^",
           /* line */ (const char *) "^.M. ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^    ",
           /* line */ (const char *) " .    ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "^.... ",
           /* line */ (const char *) " .xx. ",
           /* line */ (const char *) " .xx.^",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "   ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^   ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "^.... ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) " ....^",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) " .    ",
           /* line */ (const char *) " ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^  ",
           /* line */ (const char *) "^... ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " .g.^",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) "  ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^    ",
           /* line */ (const char *) "   ....   ",
           /* line */ (const char *) "   ......^",
           /* line */ (const char *) "   ....   ",
           /* line */ (const char *) "^......   ",
           /* line */ (const char *) "   ....   ",
           /* line */ (const char *) "    .     ",
           /* line */ (const char *) "    .     ",
           /* line */ (const char *) "    .     ",
           /* line */ (const char *) "    ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^  ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) " .x.. ",
           /* line */ (const char *) "^....^",
           /* line */ (const char *) " ..x. ",
           /* line */ (const char *) " .....",
           /* line */ (const char *) " ^  .m",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^   ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "^.... ",
           /* line */ (const char *) " ....^",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) " ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^     ",
           /* line */ (const char *) "  ..... ",
           /* line */ (const char *) "^..g.x.^",
           /* line */ (const char *) "  ..... ",
           /* line */ (const char *) "    .   ",
           /* line */ (const char *) "    .   ",
           /* line */ (const char *) "    ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^    ",
           /* line */ (const char *) " $. .    ",
           /* line */ (const char *) " ..|...  ",
           /* line */ (const char *) "  |..g.  ",
           /* line */ (const char *) "^.......^",
           /* line */ (const char *) "  .....  ",
           /* line */ (const char *) "    .    ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^   ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " .g.^",
           /* line */ (const char *) "^... ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) "  ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "       ^   ",
           /* line */ (const char *) "       .   ",
           /* line */ (const char *) "       .   ",
           /* line */ (const char *) "       .   ",
           /* line */ (const char *) "^........  ",
           /* line */ (const char *) "    ......^",
           /* line */ (const char *) "    .....  ",
           /* line */ (const char *) "       .   ",
           /* line */ (const char *) "       .   ",
           /* line */ (const char *) "       ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "       ^    ",
           /* line */ (const char *) "       .    ",
           /* line */ (const char *) "^........   ",
           /* line */ (const char *) "    .......^",
           /* line */ (const char *) "    .....   ",
           /* line */ (const char *) "      ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "      ^  ",
           /* line */ (const char *) "      .  ",
           /* line */ (const char *) "    ....^",
           /* line */ (const char *) "^.....m. ",
           /* line */ (const char *) "    .... ",
           /* line */ (const char *) "      .  ",
           /* line */ (const char *) "      .  ",
           /* line */ (const char *) "      ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^   ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "^..x. ",
           /* line */ (const char *) " x...^",
           /* line */ (const char *) " xx.. ",
           /* line */ (const char *) "   ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^   ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " .m. ",
           /* line */ (const char *) "^... ",
           /* line */ (const char *) " .x.^",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^  ",
           /* line */ (const char *) " ....^",
           /* line */ (const char *) " m... ",
           /* line */ (const char *) " ...` ",
           /* line */ (const char *) "^..`` ",
           /* line */ (const char *) " ..```",
           /* line */ (const char *) "  ^``$",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^  ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "^.x..^",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) " ...x ",
           /* line */ (const char *) " ..xx ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^    ",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) " .x.G.^",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^  ",
           /* line */ (const char *) "     .  ",
           /* line */ (const char *) "   ....^",
           /* line */ (const char *) "^...x.. ",
           /* line */ (const char *) "   .... ",
           /* line */ (const char *) "    .   ",
           /* line */ (const char *) "    .   ",
           /* line */ (const char *) "    ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^    ",
           /* line */ (const char *) "    .    ",
           /* line */ (const char *) "    .    ",
           /* line */ (const char *) "^.......^",
           /* line */ (const char *) "    .|.  ",
           /* line */ (const char *) "    ...  ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^    ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " .x.m.^",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "  ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^    ",
           /* line */ (const char *) "^....^",
           /* line */ (const char *) " .|.. ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) " .m.. ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "  .   ",
           /* line */ (const char *) "  .   ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^    ",
           /* line */ (const char *) " .    ",
           /* line */ (const char *) " .    ",
           /* line */ (const char *) " .    ",
           /* line */ (const char *) " ....^",
           /* line */ (const char *) "^...  ",
           /* line */ (const char *) " ...  ",
           /* line */ (const char *) " .    ",
           /* line */ (const char *) " .    ",
           /* line */ (const char *) " .    ",
           /* line */ (const char *) " ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^   ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " .m. ",
           /* line */ (const char *) "^...^",
           /* line */ (const char *) " .g. ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^  ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) "^.M.^",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " .g. ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) "  ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^   ",
           /* line */ (const char *) "^.... ",
           /* line */ (const char *) " ....^",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^   ",
           /* line */ (const char *) "   .   ",
           /* line */ (const char *) "   .   ",
           /* line */ (const char *) " xx... ",
           /* line */ (const char *) " x.... ",
           /* line */ (const char *) " ..x.. ",
           /* line */ (const char *) "^.....^",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^     ",
           /* line */ (const char *) "     .     ",
           /* line */ (const char *) "     .     ",
           /* line */ (const char *) "    ....   ",
           /* line */ (const char *) "^.......   ",
           /* line */ (const char *) "    .x....^",
           /* line */ (const char *) "    ....   ",
           /* line */ (const char *) "     .     ",
           /* line */ (const char *) "     .     ",
           /* line */ (const char *) "     ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^  ",
           /* line */ (const char *) "   ...^",
           /* line */ (const char *) "^...g. ",
           /* line */ (const char *) "   ... ",
           /* line */ (const char *) "   .   ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^   ",
           /* line */ (const char *) " ...^",
           /* line */ (const char *) "^.x. ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) "  ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^     ",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) " ..x..^",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^   ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " .g.^",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) "^.G. ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) "  ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^    ",
           /* line */ (const char *) "  .    ",
           /* line */ (const char *) " ....  ",
           /* line */ (const char *) " ....  ",
           /* line */ (const char *) "^.....^",
           /* line */ (const char *) " ....  ",
           /* line */ (const char *) "   .   ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^      ",
           /* line */ (const char *) "   .      ",
           /* line */ (const char *) "^......   ",
           /* line */ (const char *) "   ......^",
           /* line */ (const char *) "   ....   ",
           /* line */ (const char *) "    ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^      ",
           /* line */ (const char *) "   .      ",
           /* line */ (const char *) "   ....   ",
           /* line */ (const char *) "^....m...^",
           /* line */ (const char *) "   ....   ",
           /* line */ (const char *) "   .      ",
           /* line */ (const char *) "   ^      ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^     ",
           /* line */ (const char *) "^...   ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) " .x.   ",
           /* line */ (const char *) " ...   ",
           /* line */ (const char *) " ...   ",
           /* line */ (const char *) " .     ",
           /* line */ (const char *) " ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^    ",
           /* line */ (const char *) "    .    ",
           /* line */ (const char *) "^.......^",
           /* line */ (const char *) "  .....  ",
           /* line */ (const char *) "  .....  ",
           /* line */ (const char *) "  .....  ",
           /* line */ (const char *) "  .....  ",
           /* line */ (const char *) "  .      ",
           /* line */ (const char *) "  .      ",
           /* line */ (const char *) "  ^      ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^  `$",
           /* line */ (const char *) "^.````",
           /* line */ (const char *) " ..```",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) " m.x.^",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^      ",
           /* line */ (const char *) "  .      ",
           /* line */ (const char *) "  ......^",
           /* line */ (const char *) "^..m.    ",
           /* line */ (const char *) "  ...    ",
           /* line */ (const char *) "  .      ",
           /* line */ (const char *) "  ^      ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^    ",
           /* line */ (const char *) "   .    ",
           /* line */ (const char *) "^...... ",
           /* line */ (const char *) "  .x.x.^",
           /* line */ (const char *) "  ..... ",
           /* line */ (const char *) "  ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^   ",
           /* line */ (const char *) "  .   ",
           /* line */ (const char *) " ...  ",
           /* line */ (const char *) "^....^",
           /* line */ (const char *) " ...  ",
           /* line */ (const char *) " ...  ",
           /* line */ (const char *) " ...  ",
           /* line */ (const char *) "  .   ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^   ",
           /* line */ (const char *) "^.....^",
           /* line */ (const char *) " ..|.. ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "    ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^  ",
           /* line */ (const char *) "   .  ",
           /* line */ (const char *) "   .  ",
           /* line */ (const char *) "^.... ",
           /* line */ (const char *) "  .m.^",
           /* line */ (const char *) "  ... ",
           /* line */ (const char *) "  ... ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^    ",
           /* line */ (const char *) " .    ",
           /* line */ (const char *) " .    ",
           /* line */ (const char *) " .    ",
           /* line */ (const char *) " ....^",
           /* line */ (const char *) " .m.  ",
           /* line */ (const char *) "^...  ",
           /* line */ (const char *) " ...  ",
           /* line */ (const char *) " .    ",
           /* line */ (const char *) " ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^  ",
           /* line */ (const char *) " ...^",
           /* line */ (const char *) "^... ",
           /* line */ (const char *) " .g. ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) "  ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^  ",
           /* line */ (const char *) "     .  ",
           /* line */ (const char *) "     .  ",
           /* line */ (const char *) "  .....^",
           /* line */ (const char *) "  ..... ",
           /* line */ (const char *) "^..|.g. ",
           /* line */ (const char *) "  ..... ",
           /* line */ (const char *) "    ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "      ^  ",
           /* line */ (const char *) "     ... ",
           /* line */ (const char *) "     .g. ",
           /* line */ (const char *) "^.......^",
           /* line */ (const char *) "     ... ",
           /* line */ (const char *) "     .   ",
           /* line */ (const char *) "     ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "m. ^   ",
           /* line */ (const char *) "....xx ",
           /* line */ (const char *) "^....x ",
           /* line */ (const char *) " ..x..^",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^   ",
           /* line */ (const char *) "^...^",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^   ",
           /* line */ (const char *) "^... ",
           /* line */ (const char *) " ...^",
           /* line */ (const char *) " .x. ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^    ",
           /* line */ (const char *) "   .    ",
           /* line */ (const char *) "   .    ",
           /* line */ (const char *) "  .....^",
           /* line */ (const char *) "  ...   ",
           /* line */ (const char *) "^..|.   ",
           /* line */ (const char *) "  ...   ",
           /* line */ (const char *) "  .     ",
           /* line */ (const char *) "  ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "      ^    ",
           /* line */ (const char *) "      .    ",
           /* line */ (const char *) "^.........^",
           /* line */ (const char *) "    ..g.   ",
           /* line */ (const char *) "    ....   ",
           /* line */ (const char *) "      ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^      ",
           /* line */ (const char *) " ......^",
           /* line */ (const char *) " .G...  ",
           /* line */ (const char *) "^...g.  ",
           /* line */ (const char *) " .....  ",
           /* line */ (const char *) "    .   ",
           /* line */ (const char *) "    ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^   ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) "^.|. ",
           /* line */ (const char *) " ...^",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) "  ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^    ",
           /* line */ (const char *) "   .    ",
           /* line */ (const char *) "   .    ",
           /* line */ (const char *) " ....   ",
           /* line */ (const char *) " .m..   ",
           /* line */ (const char *) "^......^",
           /* line */ (const char *) " x...   ",
           /* line */ (const char *) " xx..   ",
           /* line */ (const char *) "   .    ",
           /* line */ (const char *) "   ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^   ",
           /* line */ (const char *) "   xx... ",
           /* line */ (const char *) "   x..x.^",
           /* line */ (const char *) "^....... ",
           /* line */ (const char *) "   ..... ",
           /* line */ (const char *) "   .     ",
           /* line */ (const char *) "   ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^    ",
           /* line */ (const char *) "   .    ",
           /* line */ (const char *) "^......^",
           /* line */ (const char *) "   .x.  ",
           /* line */ (const char *) "   ...  ",
           /* line */ (const char *) "    ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^   `$",
           /* line */ (const char *) "^..````",
           /* line */ (const char *) " ...```",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) " .m... ",
           /* line */ (const char *) "    ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^      ",
           /* line */ (const char *) "^......    ",
           /* line */ (const char *) "  .m......^",
           /* line */ (const char *) "  ...m..   ",
           /* line */ (const char *) "  ......   ",
           /* line */ (const char *) "  .   .m   ",
           /* line */ (const char *) "  ^        ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^    ",
           /* line */ (const char *) "^.... ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) " ..x. ",
           /* line */ (const char *) " ....^",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) " ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^    ",
           /* line */ (const char *) " .    ",
           /* line */ (const char *) "^...  ",
           /* line */ (const char *) " ...  ",
           /* line */ (const char *) " ....^",
           /* line */ (const char *) " ...  ",
           /* line */ (const char *) " .    ",
           /* line */ (const char *) " ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^  ",
           /* line */ (const char *) "^...^",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " .g. ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) "  ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^      ",
           /* line */ (const char *) "  .      ",
           /* line */ (const char *) "  ....   ",
           /* line */ (const char *) "^.......^",
           /* line */ (const char *) "  ....   ",
           /* line */ (const char *) "    .    ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^   ",
           /* line */ (const char *) " ....^",
           /* line */ (const char *) "^.... ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) " ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^  ",
           /* line */ (const char *) " ....^",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "^.... ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) " ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^     ",
           /* line */ (const char *) " ...   ",
           /* line */ (const char *) " ...   ",
           /* line */ (const char *) "^.|...^",
           /* line */ (const char *) " ...   ",
           /* line */ (const char *) "  .    ",
           /* line */ (const char *) "  ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^  ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "^.... ",
           /* line */ (const char *) " ....^",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^    ",
           /* line */ (const char *) "   .    ",
           /* line */ (const char *) "  .....^",
           /* line */ (const char *) "^...g.  ",
           /* line */ (const char *) "  ....  ",
           /* line */ (const char *) "    .   ",
           /* line */ (const char *) "    ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^   ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) "^.|. ",
           /* line */ (const char *) " ...^",
           /* line */ (const char *) " .x. ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) "  ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^    ",
           /* line */ (const char *) "     .    ",
           /* line */ (const char *) "   ......^",
           /* line */ (const char *) "^.......  ",
           /* line */ (const char *) "   .....  ",
           /* line */ (const char *) "   .....  ",
           /* line */ (const char *) "   .....  ",
           /* line */ (const char *) "    .     ",
           /* line */ (const char *) "    .     ",
           /* line */ (const char *) "    ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^     ",
           /* line */ (const char *) " .     ",
           /* line */ (const char *) " .     ",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) " xx... ",
           /* line */ (const char *) " xxx..^",
           /* line */ (const char *) " xxx.. ",
           /* line */ (const char *) "    .  ",
           /* line */ (const char *) "    ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^    ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "^..M.^",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "   ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^    ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "^..x..^",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^     ",
           /* line */ (const char *) "^.........^",
           /* line */ (const char *) "    ..|.   ",
           /* line */ (const char *) "    ....   ",
           /* line */ (const char *) "     ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^        ",
           /* line */ (const char *) "  .        ",
           /* line */ (const char *) "^.........^",
           /* line */ (const char *) "  .m..     ",
           /* line */ (const char *) "  ....     ",
           /* line */ (const char *) "    ^      ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^  ",
           /* line */ (const char *) "^.... ",
           /* line */ (const char *) "  .m. ",
           /* line */ (const char *) "  ... ",
           /* line */ (const char *) "  .m.^",
           /* line */ (const char *) "  ... ",
           /* line */ (const char *) "   .  ",
           /* line */ (const char *) "   .  ",
           /* line */ (const char *) "   .  ",
           /* line */ (const char *) "   ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^   ",
           /* line */ (const char *) "^....^",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^   ",
           /* line */ (const char *) "^... ",
           /* line */ (const char *) " ...^",
           /* line */ (const char *) " .m. ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^     ",
           /* line */ (const char *) "   .     ",
           /* line */ (const char *) "  ......^",
           /* line */ (const char *) "  .....  ",
           /* line */ (const char *) "  .....  ",
           /* line */ (const char *) "^......  ",
           /* line */ (const char *) "  .....  ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^    ",
           /* line */ (const char *) " .    ",
           /* line */ (const char *) " .    ",
           /* line */ (const char *) " ...  ",
           /* line */ (const char *) "^.g.  ",
           /* line */ (const char *) " ....^",
           /* line */ (const char *) " .G.  ",
           /* line */ (const char *) " ...  ",
           /* line */ (const char *) " .    ",
           /* line */ (const char *) " ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^  ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " .|. ",
           /* line */ (const char *) "^...^",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) "  ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^     ",
           /* line */ (const char *) "   .     ",
           /* line */ (const char *) "^.......^",
           /* line */ (const char *) "   .|..  ",
           /* line */ (const char *) "   ....  ",
           /* line */ (const char *) "   .     ",
           /* line */ (const char *) "   .     ",
           /* line */ (const char *) "   ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^   ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " .g.^",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) "^.m. ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^   ",
           /* line */ (const char *) "  .   ",
           /* line */ (const char *) "  ... ",
           /* line */ (const char *) "^....^",
           /* line */ (const char *) "  ... ",
           /* line */ (const char *) "  ... ",
           /* line */ (const char *) "  .   ",
           /* line */ (const char *) "  .   ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^      ",
           /* line */ (const char *) "^........^",
           /* line */ (const char *) "  .....   ",
           /* line */ (const char *) "  ..xx.   ",
           /* line */ (const char *) "  ..xx.   ",
           /* line */ (const char *) "  .....   ",
           /* line */ (const char *) "     .    ",
           /* line */ (const char *) "     .    ",
           /* line */ (const char *) "     ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^    ",
           /* line */ (const char *) " .    ",
           /* line */ (const char *) " .    ",
           /* line */ (const char *) " .    ",
           /* line */ (const char *) " ...  ",
           /* line */ (const char *) " .|..^",
           /* line */ (const char *) "^...  ",
           /* line */ (const char *) " ...  ",
           /* line */ (const char *) " .    ",
           /* line */ (const char *) " .    ",
           /* line */ (const char *) " ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^  ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "^.m..^",
           /* line */ (const char *) " ...x ",
           /* line */ (const char *) " ..xx ",
           /* line */ (const char *) " ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^   ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " .m. ",
           /* line */ (const char *) "^...^",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) "  ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^      ",
           /* line */ (const char *) "   ......^",
           /* line */ (const char *) "   ....   ",
           /* line */ (const char *) "   ....   ",
           /* line */ (const char *) "^......   ",
           /* line */ (const char *) "   ....   ",
           /* line */ (const char *) "   ^      ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^  ",
           /* line */ (const char *) "^...... ",
           /* line */ (const char *) "    .|.^",
           /* line */ (const char *) "    ... ",
           /* line */ (const char *) "    .   ",
           /* line */ (const char *) "    ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^   ",
           /* line */ (const char *) "    .   ",
           /* line */ (const char *) "^.....  ",
           /* line */ (const char *) "  ..x..^",
           /* line */ (const char *) "  ....  ",
           /* line */ (const char *) "   ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^  ",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) " ...x.^",
           /* line */ (const char *) " ..x.. ",
           /* line */ (const char *) " .x..x ",
           /* line */ (const char *) " ...xx ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^   ",
           /* line */ (const char *) "   .   ",
           /* line */ (const char *) "  ....^",
           /* line */ (const char *) "^..|.  ",
           /* line */ (const char *) "  ...  ",
           /* line */ (const char *) "  ...  ",
           /* line */ (const char *) "  .    ",
           /* line */ (const char *) "  ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^    ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) "^..|.. ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "  ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^   ",
           /* line */ (const char *) "   .   ",
           /* line */ (const char *) "   .   ",
           /* line */ (const char *) " xx..  ",
           /* line */ (const char *) " x...  ",
           /* line */ (const char *) "^..x.  ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) " ....  ",
           /* line */ (const char *) "   .   ",
           /* line */ (const char *) "   .   ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^    ",
           /* line */ (const char *) "^....^",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) " .M.. ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "   ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^    ",
           /* line */ (const char *) "  .....  ",
           /* line */ (const char *) "^.......^",
           /* line */ (const char *) "  .....  ",
           /* line */ (const char *) "   .     ",
           /* line */ (const char *) "   .     ",
           /* line */ (const char *) "   ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^  ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "m`  ^  ",
           /* line */ (const char *) "````.. ",
           /* line */ (const char *) "```... ",
           /* line */ (const char *) " ...x. ",
           /* line */ (const char *) "^.m...^",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "    ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^    ",
           /* line */ (const char *) "^.... ",
           /* line */ (const char *) " ..x. ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) " .g..^",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) " ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^    ",
           /* line */ (const char *) "    .    ",
           /* line */ (const char *) "^......  ",
           /* line */ (const char *) "   .x...^",
           /* line */ (const char *) "   ....  ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^  ",
           /* line */ (const char *) "^...^",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) "  ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^    ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "^.xx.^",
           /* line */ (const char *) " .xx. ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) " ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^     ",
           /* line */ (const char *) " .     ",
           /* line */ (const char *) " .     ",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "    ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^  `m ",
           /* line */ (const char *) "  .```` ",
           /* line */ (const char *) "^...``` ",
           /* line */ (const char *) "  .....^",
           /* line */ (const char *) "  ..m.  ",
           /* line */ (const char *) "  ....  ",
           /* line */ (const char *) "    .   ",
           /* line */ (const char *) "    .   ",
           /* line */ (const char *) "    ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^   ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) "^...^",
           /* line */ (const char *) " .m. ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " m.^    ",
           /* line */ (const char *) " .....  ",
           /* line */ (const char *) "^......^",
           /* line */ (const char *) "  ..|.  ",
           /* line */ (const char *) "  ....  ",
           /* line */ (const char *) "  ....  ",
           /* line */ (const char *) "    .   ",
           /* line */ (const char *) "    ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^  ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) "^.g.^",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^  ",
           /* line */ (const char *) " ...^",
           /* line */ (const char *) "^.|. ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^    ",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) " .g.x.^",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "  ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^  ",
           /* line */ (const char *) "^...^",
           /* line */ (const char *) " .g. ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^      ",
           /* line */ (const char *) "  .      ",
           /* line */ (const char *) "^....    ",
           /* line */ (const char *) "  .g....^",
           /* line */ (const char *) "  ...    ",
           /* line */ (const char *) "  ^      ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^   ",
           /* line */ (const char *) " ...^",
           /* line */ (const char *) "^.m. ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^  ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "^.x.m.^",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "  ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^  ",
           /* line */ (const char *) "   .  ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "^....^",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "  .   ",
           /* line */ (const char *) "  .   ",
           /* line */ (const char *) "  .   ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^   ",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) " x.x.. ",
           /* line */ (const char *) " x.... ",
           /* line */ (const char *) " xxx.. ",
           /* line */ (const char *) "    ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^  ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) " ....^",
           /* line */ (const char *) "^.... ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) " ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^     ",
           /* line */ (const char *) " .     ",
           /* line */ (const char *) "^..xxx ",
           /* line */ (const char *) " ....x ",
           /* line */ (const char *) " ..x.x ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^    ",
           /* line */ (const char *) " ....^",
           /* line */ (const char *) "^.g.. ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^   ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "^....^",
           /* line */ (const char *) " .xx. ",
           /* line */ (const char *) " .xx. ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "   ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^    ",
           /* line */ (const char *) "^.... ",
           /* line */ (const char *) " .M..^",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) " ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^     ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " ..xx.^",
           /* line */ (const char *) "^..xx. ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^  ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) "^.m. ",
           /* line */ (const char *) " ...^",
           /* line */ (const char *) " .g. ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) "  ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^   ",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) " ..|..^",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^   ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "^.....^",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "  ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^  ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) "^.m.^",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^  ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) "^.|.|. ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^   ",
           /* line */ (const char *) " ....^",
           /* line */ (const char *) "^.... ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "  .   ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^  ",
           /* line */ (const char *) "^...^",
           /* line */ (const char *) " .|. ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^  ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "^....^",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^   ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) " ..G. ",
           /* line */ (const char *) "^....^",
           /* line */ (const char *) " ..|. ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^       ",
           /* line */ (const char *) " .....   ",
           /* line */ (const char *) " .....   ",
           /* line */ (const char *) "^..g..   ",
           /* line */ (const char *) " .......^",
           /* line */ (const char *) " .....   ",
           /* line */ (const char *) "  ^      ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^     ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^   ",
           /* line */ (const char *) "  .   ",
           /* line */ (const char *) "  .   ",
           /* line */ (const char *) "  .   ",
           /* line */ (const char *) " ...  ",
           /* line */ (const char *) " .x.  ",
           /* line */ (const char *) "^....^",
           /* line */ (const char *) " .|.  ",
           /* line */ (const char *) " ...  ",
           /* line */ (const char *) "  .   ",
           /* line */ (const char *) "  .   ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^   ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) "^... ",
           /* line */ (const char *) " .g.^",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^   ",
           /* line */ (const char *) "   .   ",
           /* line */ (const char *) "   .   ",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) "   .|.^",
           /* line */ (const char *) "   ... ",
           /* line */ (const char *) "   ... ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^  ",
           /* line */ (const char *) " xx.. ",
           /* line */ (const char *) " x... ",
           /* line */ (const char *) "^..x.^",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^      ",
           /* line */ (const char *) "^......   ",
           /* line */ (const char *) "   .|....^",
           /* line */ (const char *) "   ....   ",
           /* line */ (const char *) "   ^      ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^  ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) " ..|. ",
           /* line */ (const char *) " ....^",
           /* line */ (const char *) "^..G. ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "   ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^  ",
           /* line */ (const char *) "     .  ",
           /* line */ (const char *) "     .  ",
           /* line */ (const char *) "     .  ",
           /* line */ (const char *) "^......^",
           /* line */ (const char *) "  ..... ",
           /* line */ (const char *) "  ..... ",
           /* line */ (const char *) "  ..... ",
           /* line */ (const char *) "  .     ",
           /* line */ (const char *) "  .     ",
           /* line */ (const char *) "  .     ",
           /* line */ (const char *) "  .     ",
           /* line */ (const char *) "  ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^    ",
           /* line */ (const char *) "    .    ",
           /* line */ (const char *) "    ...  ",
           /* line */ (const char *) "^....g.  ",
           /* line */ (const char *) "    ....^",
           /* line */ (const char *) "    .|.  ",
           /* line */ (const char *) "    ...  ",
           /* line */ (const char *) "     .   ",
           /* line */ (const char *) "     ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^  ",
           /* line */ (const char *) " xx...^",
           /* line */ (const char *) " x.... ",
           /* line */ (const char *) "^..x.. ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^   ",
           /* line */ (const char *) "   .   ",
           /* line */ (const char *) "   .   ",
           /* line */ (const char *) "  ....^",
           /* line */ (const char *) "^..|.  ",
           /* line */ (const char *) "  ...  ",
           /* line */ (const char *) "  .x.  ",
           /* line */ (const char *) "  ...  ",
           /* line */ (const char *) "   .   ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "      ^  ",
           /* line */ (const char *) "      .  ",
           /* line */ (const char *) "    ....^",
           /* line */ (const char *) "    .... ",
           /* line */ (const char *) "    ..g. ",
           /* line */ (const char *) "^....... ",
           /* line */ (const char *) "    .... ",
           /* line */ (const char *) "     .   ",
           /* line */ (const char *) "     ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^  ",
           /* line */ (const char *) "     .  ",
           /* line */ (const char *) "  ..... ",
           /* line */ (const char *) "^..x... ",
           /* line */ (const char *) "  ...g.^",
           /* line */ (const char *) "  ..... ",
           /* line */ (const char *) "    .   ",
           /* line */ (const char *) "    ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "      ^  ",
           /* line */ (const char *) "   ..... ",
           /* line */ (const char *) "^....... ",
           /* line */ (const char *) "   .x.|. ",
           /* line */ (const char *) "   .....^",
           /* line */ (const char *) "   ..... ",
           /* line */ (const char *) "    .    ",
           /* line */ (const char *) "    .    ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^  ",
           /* line */ (const char *) "^...^",
           /* line */ (const char *) " .|. ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) "  ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^  ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) "^...^",
           /* line */ (const char *) " .|. ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^     ",
           /* line */ (const char *) "   .  .$ ",
           /* line */ (const char *) "^....|.. ",
           /* line */ (const char *) "   ...|  ",
           /* line */ (const char *) "   .....^",
           /* line */ (const char *) "   ..x.  ",
           /* line */ (const char *) "   ....  ",
           /* line */ (const char *) "     .   ",
           /* line */ (const char *) "     ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^  ",
           /* line */ (const char *) "^... ",
           /* line */ (const char *) " .g.^",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) "  ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^     ",
           /* line */ (const char *) " ...   ",
           /* line */ (const char *) "^.g...^",
           /* line */ (const char *) " ...   ",
           /* line */ (const char *) "  .    ",
           /* line */ (const char *) "  ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^  ",
           /* line */ (const char *) "^... ",
           /* line */ (const char *) " .x.^",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) "  ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^    ",
           /* line */ (const char *) "    .    ",
           /* line */ (const char *) "    .    ",
           /* line */ (const char *) "   ....  ",
           /* line */ (const char *) "   .m..  ",
           /* line */ (const char *) "   .....^",
           /* line */ (const char *) "^....G.  ",
           /* line */ (const char *) "   ....  ",
           /* line */ (const char *) "   .     ",
           /* line */ (const char *) "   .     ",
           /* line */ (const char *) "   ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^  ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) "^.x.^",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " .x. ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) "  ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^     ",
           /* line */ (const char *) "  ...   ",
           /* line */ (const char *) "  .g.   ",
           /* line */ (const char *) "  ...   ",
           /* line */ (const char *) "^..x...^",
           /* line */ (const char *) "  ...   ",
           /* line */ (const char *) "   ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^  ",
           /* line */ (const char *) "    .  ",
           /* line */ (const char *) "   ...^",
           /* line */ (const char *) "   .g. ",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) "   .g. ",
           /* line */ (const char *) "   ... ",
           /* line */ (const char *) "    .  ",
           /* line */ (const char *) "    ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^  ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "^..x.^",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "   ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^    ",
           /* line */ (const char *) "   .    ",
           /* line */ (const char *) "^......^",
           /* line */ (const char *) "  .x.   ",
           /* line */ (const char *) "  ...   ",
           /* line */ (const char *) "  .     ",
           /* line */ (const char *) "  ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^     ",
           /* line */ (const char *) "  .     ",
           /* line */ (const char *) "  .     ",
           /* line */ (const char *) " ......^",
           /* line */ (const char *) " ..|.   ",
           /* line */ (const char *) " ....   ",
           /* line */ (const char *) "^..|.   ",
           /* line */ (const char *) " ....   ",
           /* line */ (const char *) "   .    ",
           /* line */ (const char *) "   .    ",
           /* line */ (const char *) "   .    ",
           /* line */ (const char *) "   ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^   ",
           /* line */ (const char *) "  .   ",
           /* line */ (const char *) " ....^",
           /* line */ (const char *) "^...  ",
           /* line */ (const char *) " ...  ",
           /* line */ (const char *) " ...  ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^     ",
           /* line */ (const char *) "  .     ",
           /* line */ (const char *) "^.....  ",
           /* line */ (const char *) "  .x..  ",
           /* line */ (const char *) "  .....^",
           /* line */ (const char *) "  ....  ",
           /* line */ (const char *) "    .   ",
           /* line */ (const char *) "    ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^      ",
           /* line */ (const char *) "^........^",
           /* line */ (const char *) "   .x.x.  ",
           /* line */ (const char *) "   .....  ",
           /* line */ (const char *) "     .    ",
           /* line */ (const char *) "     .    ",
           /* line */ (const char *) "     ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^   ",
           /* line */ (const char *) " ...^",
           /* line */ (const char *) "^.|. ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) "  ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^   ",
           /* line */ (const char *) "    .   ",
           /* line */ (const char *) "  ....  ",
           /* line */ (const char *) "^..g...^",
           /* line */ (const char *) "  ..... ",
           /* line */ (const char *) "  .|.|. ",
           /* line */ (const char *) "  ..... ",
           /* line */ (const char *) "  ..... ",
           /* line */ (const char *) "  ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^   ",
           /* line */ (const char *) "  .   ",
           /* line */ (const char *) " ...  ",
           /* line */ (const char *) "^.g.  ",
           /* line */ (const char *) " ....^",
           /* line */ (const char *) " .|.  ",
           /* line */ (const char *) " ...  ",
           /* line */ (const char *) "  .   ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^     ",
           /* line */ (const char *) "     .     ",
           /* line */ (const char *) "     .     ",
           /* line */ (const char *) "   ....    ",
           /* line */ (const char *) "   .g.....^",
           /* line */ (const char *) "   ....    ",
           /* line */ (const char *) "^.....x    ",
           /* line */ (const char *) "   ..xx    ",
           /* line */ (const char *) "   .       ",
           /* line */ (const char *) "   ^       ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^     ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "^.....^",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "    ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^    ",
           /* line */ (const char *) "   .    ",
           /* line */ (const char *) "   .    ",
           /* line */ (const char *) "  ..... ",
           /* line */ (const char *) "^..xxx. ",
           /* line */ (const char *) "  .xxx.^",
           /* line */ (const char *) "  .xxx. ",
           /* line */ (const char *) "  ..... ",
           /* line */ (const char *) "   .    ",
           /* line */ (const char *) "   ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^     ",
           /* line */ (const char *) "   .     ",
           /* line */ (const char *) " .......^",
           /* line */ (const char *) "^.|..    ",
           /* line */ (const char *) " ...x    ",
           /* line */ (const char *) " ..xx    ",
           /* line */ (const char *) " ^       ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^    ",
           /* line */ (const char *) "  .    ",
           /* line */ (const char *) "^...   ",
           /* line */ (const char *) " .x...^",
           /* line */ (const char *) " ...   ",
           /* line */ (const char *) "  .    ",
           /* line */ (const char *) "  .    ",
           /* line */ (const char *) "  ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^        ",
           /* line */ (const char *) "   .....     ",
           /* line */ (const char *) "^.....x.     ",
           /* line */ (const char *) "   .x.......^",
           /* line */ (const char *) "   ...g.     ",
           /* line */ (const char *) "   .....     ",
           /* line */ (const char *) "      ^      ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^    ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) " ....^",
           /* line */ (const char *) " ..xx ",
           /* line */ (const char *) "^.xxx ",
           /* line */ (const char *) " .xxx ",
           /* line */ (const char *) " ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^   ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) " .xx. ",
           /* line */ (const char *) "^.xx.^",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) " ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^  ",
           /* line */ (const char *) "   .  ",
           /* line */ (const char *) " xx.. ",
           /* line */ (const char *) " x...^",
           /* line */ (const char *) "^..|. ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "  .   ",
           /* line */ (const char *) "  .   ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^   ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) "^...^",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^     ",
           /* line */ (const char *) "   .     ",
           /* line */ (const char *) "   .     ",
           /* line */ (const char *) "^.......^",
           /* line */ (const char *) "  ...    ",
           /* line */ (const char *) "  ...    ",
           /* line */ (const char *) "  ^      ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^   ",
           /* line */ (const char *) "   .   ",
           /* line */ (const char *) "  ...  ",
           /* line */ (const char *) "  ....^",
           /* line */ (const char *) "^....  ",
           /* line */ (const char *) "  ...  ",
           /* line */ (const char *) "  .    ",
           /* line */ (const char *) "  ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^  ",
           /* line */ (const char *) " ...^",
           /* line */ (const char *) "^.x. ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) "  ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^   ",
           /* line */ (const char *) "^... ",
           /* line */ (const char *) " .m. ",
           /* line */ (const char *) " ...^",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^  ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) "^...^",
           /* line */ (const char *) " .g. ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) "  ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^     ",
           /* line */ (const char *) "   .....   ",
           /* line */ (const char *) "   .xxx...^",
           /* line */ (const char *) "^...x...   ",
           /* line */ (const char *) "   .x..x   ",
           /* line */ (const char *) "   ...xx   ",
           /* line */ (const char *) "   ^       ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^   ",
           /* line */ (const char *) " ...^",
           /* line */ (const char *) "^.|. ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " .g. ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) "  ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^        ",
           /* line */ (const char *) "  .        ",
           /* line */ (const char *) "  ........^",
           /* line */ (const char *) "  .....    ",
           /* line */ (const char *) "^......    ",
           /* line */ (const char *) "  .....    ",
           /* line */ (const char *) "  .....    ",
           /* line */ (const char *) "    ^      ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^    ",
           /* line */ (const char *) "   .... ",
           /* line */ (const char *) "^...... ",
           /* line */ (const char *) "   .... ",
           /* line */ (const char *) "   ....^",
           /* line */ (const char *) "   .... ",
           /* line */ (const char *) "    .   ",
           /* line */ (const char *) "    ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^    ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) "^.|.x. ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "    ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^        ",
           /* line */ (const char *) "^....      ",
           /* line */ (const char *) "  .g......^",
           /* line */ (const char *) "  ...      ",
           /* line */ (const char *) "  .        ",
           /* line */ (const char *) "  ^        ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^   ",
           /* line */ (const char *) "^...^",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^   ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) "^.G.^",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) "  ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^  ",
           /* line */ (const char *) "^...^",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " .|. ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) "  ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^   ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) "^.g.^",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) "  ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^     ",
           /* line */ (const char *) "^......  ",
           /* line */ (const char *) "  ...x.  ",
           /* line */ (const char *) "  .x....^",
           /* line */ (const char *) "  ...g.  ",
           /* line */ (const char *) "  .....  ",
           /* line */ (const char *) "     .   ",
           /* line */ (const char *) "     ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "      ^   ",
           /* line */ (const char *) "      .   ",
           /* line */ (const char *) "^.......  ",
           /* line */ (const char *) "   .xxx.  ",
           /* line */ (const char *) "   ...x..^",
           /* line */ (const char *) "   x..x.  ",
           /* line */ (const char *) "   xx...  ",
           /* line */ (const char *) "     .    ",
           /* line */ (const char *) "     .    ",
           /* line */ (const char *) "     .    ",
           /* line */ (const char *) "     ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^   ",
           /* line */ (const char *) "^.... ",
           /* line */ (const char *) " ....^",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) " ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^   ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " .m...^",
           /* line */ (const char *) "^....` ",
           /* line */ (const char *) " .|.`` ",
           /* line */ (const char *) " ...```",
           /* line */ (const char *) " .  ``$",
           /* line */ (const char *) " ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^  ",
           /* line */ (const char *) "   .  ",
           /* line */ (const char *) "^.... ",
           /* line */ (const char *) " ....^",
           /* line */ (const char *) " .xx. ",
           /* line */ (const char *) " .xx. ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) " ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^   ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) " .x.. ",
           /* line */ (const char *) "^....^",
           /* line */ (const char *) " ..```",
           /* line */ (const char *) " .````",
           /* line */ (const char *) " ^  `m",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^    ",
           /* line */ (const char *) "^...  ",
           /* line */ (const char *) " .m..^",
           /* line */ (const char *) " ...  ",
           /* line */ (const char *) " .g.  ",
           /* line */ (const char *) " ...  ",
           /* line */ (const char *) " .    ",
           /* line */ (const char *) " ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^  ",
           /* line */ (const char *) "  xxx.. ",
           /* line */ (const char *) "  xxx.. ",
           /* line */ (const char *) "  xx...^",
           /* line */ (const char *) "^....|. ",
           /* line */ (const char *) "  ..... ",
           /* line */ (const char *) "    .   ",
           /* line */ (const char *) "    .   ",
           /* line */ (const char *) "    ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^      ",
           /* line */ (const char *) "^.....   ",
           /* line */ (const char *) " .m.m...^",
           /* line */ (const char *) " .....   ",
           /* line */ (const char *) " .x.m.   ",
           /* line */ (const char *) " .....   ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^  ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "^....^",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^    ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "  ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^  ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "^....^",
           /* line */ (const char *) " ..m. ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "   ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^    ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " .g... ",
           /* line */ (const char *) " ...m. ",
           /* line */ (const char *) "^.g...^",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "    ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^  ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " .x. ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) "^.m.^",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^     ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "^..xx. ",
           /* line */ (const char *) " ..xx.^",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^    ",
           /* line */ (const char *) "^....^",
           /* line */ (const char *) " .|.. ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) " ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^  ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "^....^",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^  ",
           /* line */ (const char *) "^.....^",
           /* line */ (const char *) " ..x.. ",
           /* line */ (const char *) " x.... ",
           /* line */ (const char *) " xx... ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^   ",
           /* line */ (const char *) "^... ",
           /* line */ (const char *) " .g. ",
           /* line */ (const char *) " ...^",
           /* line */ (const char *) " .x. ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^  ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "^.|.m.^",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^   ",
           /* line */ (const char *) "    .   ",
           /* line */ (const char *) "    .   ",
           /* line */ (const char *) "  xx...^",
           /* line */ (const char *) "  x.... ",
           /* line */ (const char *) "^...x.. ",
           /* line */ (const char *) "  ....x ",
           /* line */ (const char *) "  ...xx ",
           /* line */ (const char *) "    .   ",
           /* line */ (const char *) "    .   ",
           /* line */ (const char *) "    ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^    ",
           /* line */ (const char *) "^.... ",
           /* line */ (const char *) " ..|.^",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^     ",
           /* line */ (const char *) "   .     ",
           /* line */ (const char *) "   ..... ",
           /* line */ (const char *) "^.......^",
           /* line */ (const char *) "   ..|.. ",
           /* line */ (const char *) "   ..... ",
           /* line */ (const char *) "   .     ",
           /* line */ (const char *) "   .     ",
           /* line */ (const char *) "   ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^     ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "^..M.. ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "  ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^  ",
           /* line */ (const char *) "^.....^",
           /* line */ (const char *) " .|.g. ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "  ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^..m",
           /* line */ (const char *) " .....",
           /* line */ (const char *) "^.... ",
           /* line */ (const char *) " .|..^",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "   .  ",
           /* line */ (const char *) "   ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^     ",
           /* line */ (const char *) "  .     ",
           /* line */ (const char *) "  .....^",
           /* line */ (const char *) "^...... ",
           /* line */ (const char *) "  .x.CC ",
           /* line */ (const char *) "  ...C..",
           /* line */ (const char *) "    . .m",
           /* line */ (const char *) "    ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^    ",
           /* line */ (const char *) "  .    ",
           /* line */ (const char *) "  .    ",
           /* line */ (const char *) "  .    ",
           /* line */ (const char *) "  ....^",
           /* line */ (const char *) "^....  ",
           /* line */ (const char *) "  ...  ",
           /* line */ (const char *) "  ...  ",
           /* line */ (const char *) "   .   ",
           /* line */ (const char *) "   .   ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^   ",
           /* line */ (const char *) " .   ",
           /* line */ (const char *) " .   ",
           /* line */ (const char *) " .   ",
           /* line */ (const char *) "^... ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " .|. ",
           /* line */ (const char *) " ...^",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) "  .  ",
           /* line */ (const char *) "  .  ",
           /* line */ (const char *) "  .  ",
           /* line */ (const char *) "  .  ",
           /* line */ (const char *) "  ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^     ",
           /* line */ (const char *) "   .     ",
           /* line */ (const char *) "   .     ",
           /* line */ (const char *) "^......  ",
           /* line */ (const char *) "  .....  ",
           /* line */ (const char *) "  ......^",
           /* line */ (const char *) "  .....  ",
           /* line */ (const char *) "  ^      ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^   ",
           /* line */ (const char *) "    ....^",
           /* line */ (const char *) "    .... ",
           /* line */ (const char *) "^....... ",
           /* line */ (const char *) "    .... ",
           /* line */ (const char *) "      ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^  ",
           /* line */ (const char *) "^...^",
           /* line */ (const char *) " .x. ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^   ",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) " ..m.. ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^   ",
           /* line */ (const char *) "    .   ",
           /* line */ (const char *) "    ... ",
           /* line */ (const char *) "^....|.^",
           /* line */ (const char *) "    ... ",
           /* line */ (const char *) "     .  ",
           /* line */ (const char *) "     ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^     ",
           /* line */ (const char *) "   .     ",
           /* line */ (const char *) "   .     ",
           /* line */ (const char *) "   .     ",
           /* line */ (const char *) "  ......^",
           /* line */ (const char *) "  ...    ",
           /* line */ (const char *) "^....    ",
           /* line */ (const char *) "  ...    ",
           /* line */ (const char *) "   .     ",
           /* line */ (const char *) "   ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^    ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "^..x.^",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^    ",
           /* line */ (const char *) "^.....^",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^      ",
           /* line */ (const char *) " .      ",
           /* line */ (const char *) " .      ",
           /* line */ (const char *) " ...    ",
           /* line */ (const char *) "^.g....^",
           /* line */ (const char *) " ...    ",
           /* line */ (const char *) "  .     ",
           /* line */ (const char *) "  .     ",
           /* line */ (const char *) "  .     ",
           /* line */ (const char *) "  ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^   ",
           /* line */ (const char *) "^... ",
           /* line */ (const char *) " .|.^",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^    ",
           /* line */ (const char *) "   .....^",
           /* line */ (const char *) "   ....  ",
           /* line */ (const char *) "^....|.  ",
           /* line */ (const char *) "   ....  ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^   ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) "^.g.^",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) "  ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^   ",
           /* line */ (const char *) "^....^",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) " ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^   ",
           /* line */ (const char *) "^.... ",
           /* line */ (const char *) " .x..^",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) " ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^  ",
           /* line */ (const char *) " ....^",
           /* line */ (const char *) "^.... ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^     ",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^   ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " .xxx. ",
           /* line */ (const char *) "^.xxx. ",
           /* line */ (const char *) " .xxx.^",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "    ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^     ",
           /* line */ (const char *) "   .....   ",
           /* line */ (const char *) "   .......^",
           /* line */ (const char *) "^.......   ",
           /* line */ (const char *) "   .....   ",
           /* line */ (const char *) "      ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^  ",
           /* line */ (const char *) " ...^",
           /* line */ (const char *) "^.x. ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) "  ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^      ",
           /* line */ (const char *) " .      ",
           /* line */ (const char *) " .      ",
           /* line */ (const char *) " ...    ",
           /* line */ (const char *) "^.g.    ",
           /* line */ (const char *) " ...    ",
           /* line */ (const char *) " .x....^",
           /* line */ (const char *) " ...    ",
           /* line */ (const char *) " .      ",
           /* line */ (const char *) " .      ",
           /* line */ (const char *) " ^      ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^   ",
           /* line */ (const char *) "^... ",
           /* line */ (const char *) " .x. ",
           /* line */ (const char *) " ...^",
           /* line */ (const char *) " .m. ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^  ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " .m. ",
           /* line */ (const char *) " ...^",
           /* line */ (const char *) "^.g. ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^  ",
           /* line */ (const char *) "   .  ",
           /* line */ (const char *) "   .  ",
           /* line */ (const char *) "  ... ",
           /* line */ (const char *) "  ...^",
           /* line */ (const char *) "^.... ",
           /* line */ (const char *) "  ... ",
           /* line */ (const char *) "  ... ",
           /* line */ (const char *) "   .  ",
           /* line */ (const char *) "   .  ",
           /* line */ (const char *) "   .  ",
           /* line */ (const char *) "   ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^  ",
           /* line */ (const char *) "^...^",
           /* line */ (const char *) " .m. ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) "  ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^   ",
           /* line */ (const char *) "^...^",
           /* line */ (const char *) " .g. ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^   ",
           /* line */ (const char *) "  .   ",
           /* line */ (const char *) "  .   ",
           /* line */ (const char *) "  .   ",
           /* line */ (const char *) " ....^",
           /* line */ (const char *) "^...  ",
           /* line */ (const char *) " .|.  ",
           /* line */ (const char *) " ...  ",
           /* line */ (const char *) "  .   ",
           /* line */ (const char *) "  .   ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^   ",
           /* line */ (const char *) "^...^",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) "  ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^  ",
           /* line */ (const char *) "^.m...^",
           /* line */ (const char *) " ....` ",
           /* line */ (const char *) " .m.`` ",
           /* line */ (const char *) " ...```",
           /* line */ (const char *) " ^  ``$",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^     ",
           /* line */ (const char *) "   .     ",
           /* line */ (const char *) "   ...   ",
           /* line */ (const char *) "   ...   ",
           /* line */ (const char *) "   .x.   ",
           /* line */ (const char *) "^.......^",
           /* line */ (const char *) "   ...   ",
           /* line */ (const char *) "    .    ",
           /* line */ (const char *) "    .    ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^   ",
           /* line */ (const char *) "   .   ",
           /* line */ (const char *) "^.....^",
           /* line */ (const char *) "  ...  ",
           /* line */ (const char *) "  ...  ",
           /* line */ (const char *) "  ...  ",
           /* line */ (const char *) "  ...  ",
           /* line */ (const char *) "  ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^     ",
           /* line */ (const char *) "   .     ",
           /* line */ (const char *) "^.......^",
           /* line */ (const char *) "   ..m.  ",
           /* line */ (const char *) "   ....  ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^  ",
           /* line */ (const char *) " ...^",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) "^... ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) "  ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^  ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "^.|.x.^",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^    ",
           /* line */ (const char *) "^....^",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^   ",
           /* line */ (const char *) "   .   ",
           /* line */ (const char *) "  ....^",
           /* line */ (const char *) "^..g.. ",
           /* line */ (const char *) "  .... ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^    ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "    ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^    ",
           /* line */ (const char *) "  .    ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) " .x.|. ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "^.|.g. ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "  ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^  ",
           /* line */ (const char *) "  ... ",
           /* line */ (const char *) "  .g. ",
           /* line */ (const char *) "^....^",
           /* line */ (const char *) "  .m. ",
           /* line */ (const char *) "  ... ",
           /* line */ (const char *) "  .   ",
           /* line */ (const char *) "  .   ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "      ^     ",
           /* line */ (const char *) "      .     ",
           /* line */ (const char *) "      .     ",
           /* line */ (const char *) "    .....   ",
           /* line */ (const char *) "^.....x....^",
           /* line */ (const char *) "    .....   ",
           /* line */ (const char *) "    ^       ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^     ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "^.M.g.^",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "  ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^  ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " .m. ",
           /* line */ (const char *) "^...^",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^  ",
           /* line */ (const char *) "^.....^",
           /* line */ (const char *) "   .|. ",
           /* line */ (const char *) "   ... ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^     ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "^.g... ",
           /* line */ (const char *) " ...g.^",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "  ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^  ",
           /* line */ (const char *) "  .  ",
           /* line */ (const char *) "  .  ",
           /* line */ (const char *) "^... ",
           /* line */ (const char *) " ...^",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) "  .  ",
           /* line */ (const char *) "  .  ",
           /* line */ (const char *) "  ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^   ",
           /* line */ (const char *) "^...xx ",
           /* line */ (const char *) "  ...x ",
           /* line */ (const char *) "  .x.. ",
           /* line */ (const char *) "  ....^",
           /* line */ (const char *) "  .... ",
           /* line */ (const char *) "  .    ",
           /* line */ (const char *) "  ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^      ",
           /* line */ (const char *) " .  `m  ",
           /* line */ (const char *) "^.````  ",
           /* line */ (const char *) " ..```  ",
           /* line */ (const char *) " ....   ",
           /* line */ (const char *) " .|....^",
           /* line */ (const char *) " ....   ",
           /* line */ (const char *) "  .     ",
           /* line */ (const char *) "  ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^    ",
           /* line */ (const char *) "^.....^",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "  ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^   ",
           /* line */ (const char *) "^... ",
           /* line */ (const char *) " .|.^",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) "  ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^    ",
           /* line */ (const char *) " ...xx ",
           /* line */ (const char *) " ....x ",
           /* line */ (const char *) "^..x..^",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^   ",
           /* line */ (const char *) "^.....  ",
           /* line */ (const char *) " .....  ",
           /* line */ (const char *) " ......^",
           /* line */ (const char *) " .....  ",
           /* line */ (const char *) " .      ",
           /* line */ (const char *) " .      ",
           /* line */ (const char *) " .      ",
           /* line */ (const char *) " ^      ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^     ",
           /* line */ (const char *) "^.......^",
           /* line */ (const char *) "   ..m.  ",
           /* line */ (const char *) "   ....  ",
           /* line */ (const char *) "   .     ",
           /* line */ (const char *) "   ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^   ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) "^.x.|. ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^   ",
           /* line */ (const char *) "     .   ",
           /* line */ (const char *) "^......  ",
           /* line */ (const char *) "   .m...^",
           /* line */ (const char *) "   ....  ",
           /* line */ (const char *) "    .    ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^  ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " .m.^",
           /* line */ (const char *) "^... ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) "  ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^  ",
           /* line */ (const char *) " xx... ",
           /* line */ (const char *) " x.... ",
           /* line */ (const char *) "^..x..^",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^  ",
           /* line */ (const char *) "   .  ",
           /* line */ (const char *) "  ... ",
           /* line */ (const char *) "  ...^",
           /* line */ (const char *) "^..|. ",
           /* line */ (const char *) "  ... ",
           /* line */ (const char *) "   .  ",
           /* line */ (const char *) "   .  ",
           /* line */ (const char *) "   ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^     ",
           /* line */ (const char *) "^.....^",
           /* line */ (const char *) " .|.g. ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "    ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^  ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "^.xxx.^",
           /* line */ (const char *) " .x... ",
           /* line */ (const char *) " .x..x ",
           /* line */ (const char *) " ...xx ",
           /* line */ (const char *) " ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^     ",
           /* line */ (const char *) "^...xx ",
           /* line */ (const char *) " .x..x ",
           /* line */ (const char *) " .x... ",
           /* line */ (const char *) " .xxx.^",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^   ",
           /* line */ (const char *) " ...^",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) "^... ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) "  ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^  ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) "^.m.m. ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^    ",
           /* line */ (const char *) "^....^",
           /* line */ (const char *) " ..|. ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "   ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^   ",
           /* line */ (const char *) " ...^",
           /* line */ (const char *) "^.|. ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^   ",
           /* line */ (const char *) "^.......^",
           /* line */ (const char *) "   .m.m. ",
           /* line */ (const char *) "   ..... ",
           /* line */ (const char *) "      .  ",
           /* line */ (const char *) "      ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^   ",
           /* line */ (const char *) " ....^",
           /* line */ (const char *) "^..m. ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^      ",
           /* line */ (const char *) "  .      ",
           /* line */ (const char *) "^.......^",
           /* line */ (const char *) "  .|.    ",
           /* line */ (const char *) "  ...    ",
           /* line */ (const char *) "  .|.    ",
           /* line */ (const char *) "  ...    ",
           /* line */ (const char *) "   .     ",
           /* line */ (const char *) "   ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^    ",
           /* line */ (const char *) "    .    ",
           /* line */ (const char *) "    .    ",
           /* line */ (const char *) "    .    ",
           /* line */ (const char *) "  .....  ",
           /* line */ (const char *) "^..x.x..^",
           /* line */ (const char *) "  .....  ",
           /* line */ (const char *) "  ^      ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^     ",
           /* line */ (const char *) "  .     ",
           /* line */ (const char *) "  .     ",
           /* line */ (const char *) "  .     ",
           /* line */ (const char *) " ....   ",
           /* line */ (const char *) " ....   ",
           /* line */ (const char *) "^.x....^",
           /* line */ (const char *) " ....   ",
           /* line */ (const char *) " ....   ",
           /* line */ (const char *) "   .    ",
           /* line */ (const char *) "   ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^    ",
           /* line */ (const char *) "   ..... ",
           /* line */ (const char *) "   .|.m.^",
           /* line */ (const char *) "   ..... ",
           /* line */ (const char *) "^...g.g. ",
           /* line */ (const char *) "   ..... ",
           /* line */ (const char *) "     .   ",
           /* line */ (const char *) "     .   ",
           /* line */ (const char *) "     ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^  ",
           /* line */ (const char *) "  .  ",
           /* line */ (const char *) "  .  ",
           /* line */ (const char *) "  .  ",
           /* line */ (const char *) "  .  ",
           /* line */ (const char *) "  .  ",
           /* line */ (const char *) "^... ",
           /* line */ (const char *) " .m. ",
           /* line */ (const char *) " ...^",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " .   ",
           /* line */ (const char *) " .   ",
           /* line */ (const char *) " .   ",
           /* line */ (const char *) " ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^    ",
           /* line */ (const char *) "^......^",
           /* line */ (const char *) "   .M.. ",
           /* line */ (const char *) "   .... ",
           /* line */ (const char *) "    .   ",
           /* line */ (const char *) "    ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^   ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " .|.^",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) "^.|. ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^   ",
           /* line */ (const char *) "^... ",
           /* line */ (const char *) " .m.^",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) "  ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^  ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) "^... ",
           /* line */ (const char *) " .|.^",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) "  ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^      ",
           /* line */ (const char *) "    .      ",
           /* line */ (const char *) "^.........^",
           /* line */ (const char *) "   .|.|.   ",
           /* line */ (const char *) "   .....   ",
           /* line */ (const char *) "      .    ",
           /* line */ (const char *) "      ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^    ",
           /* line */ (const char *) "  .    ",
           /* line */ (const char *) "  .    ",
           /* line */ (const char *) " ....  ",
           /* line */ (const char *) "^..x..^",
           /* line */ (const char *) " ....  ",
           /* line */ (const char *) "   .   ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^    ",
           /* line */ (const char *) "    .    ",
           /* line */ (const char *) "  ......^",
           /* line */ (const char *) "  .....  ",
           /* line */ (const char *) "^......  ",
           /* line */ (const char *) "  .....  ",
           /* line */ (const char *) "   .     ",
           /* line */ (const char *) "   ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^     ",
           /* line */ (const char *) "  .     ",
           /* line */ (const char *) "^....   ",
           /* line */ (const char *) " ..g...^",
           /* line */ (const char *) " ....   ",
           /* line */ (const char *) " .      ",
           /* line */ (const char *) " ^      ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^    ",
           /* line */ (const char *) "  ...   ",
           /* line */ (const char *) "^......^",
           /* line */ (const char *) "  ...   ",
           /* line */ (const char *) "  ...   ",
           /* line */ (const char *) "   .    ",
           /* line */ (const char *) "   ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^   ",
           /* line */ (const char *) " ....^",
           /* line */ (const char *) "^.M.. ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "   ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^   ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "^.... ",
           /* line */ (const char *) " ....^",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "   ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "      ^  ",
           /* line */ (const char *) "      .  ",
           /* line */ (const char *) "   ..... ",
           /* line */ (const char *) "   .m... ",
           /* line */ (const char *) "^.....x.^",
           /* line */ (const char *) "   ..... ",
           /* line */ (const char *) "    .    ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^   ",
           /* line */ (const char *) " .   ",
           /* line */ (const char *) " .   ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " .x. ",
           /* line */ (const char *) "^... ",
           /* line */ (const char *) " .g.^",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) "  .  ",
           /* line */ (const char *) "  .  ",
           /* line */ (const char *) "  .  ",
           /* line */ (const char *) "  ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^     ",
           /* line */ (const char *) "     .     ",
           /* line */ (const char *) "     .     ",
           /* line */ (const char *) "^.......   ",
           /* line */ (const char *) "    ......^",
           /* line */ (const char *) "    ..|.   ",
           /* line */ (const char *) "    ....   ",
           /* line */ (const char *) "    .      ",
           /* line */ (const char *) "    .      ",
           /* line */ (const char *) "    ^      ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^    ",
           /* line */ (const char *) "^....^",
           /* line */ (const char *) " .m.. ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) " ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^   ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) "^.|.^",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^  ",
           /* line */ (const char *) " ...^",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) "^.m. ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "      ^   ",
           /* line */ (const char *) "^........^",
           /* line */ (const char *) "     .m.  ",
           /* line */ (const char *) "     ...  ",
           /* line */ (const char *) "     .    ",
           /* line */ (const char *) "     .    ",
           /* line */ (const char *) "     ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^    ",
           /* line */ (const char *) "^....... ",
           /* line */ (const char *) "   .M.M.^",
           /* line */ (const char *) "   ..... ",
           /* line */ (const char *) "      ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^    ",
           /* line */ (const char *) "   .    ",
           /* line */ (const char *) "  ..... ",
           /* line */ (const char *) "  .....^",
           /* line */ (const char *) "^...... ",
           /* line */ (const char *) "  ..... ",
           /* line */ (const char *) "  ..... ",
           /* line */ (const char *) "   .    ",
           /* line */ (const char *) "   ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "m.  ^  ",
           /* line */ (const char *) "..C... ",
           /* line */ (const char *) " CC...^",
           /* line */ (const char *) "^...g. ",
           /* line */ (const char *) " .x... ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "  ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^    ",
           /* line */ (const char *) "^.... ",
           /* line */ (const char *) " ..m.^",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "   ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^     ",
           /* line */ (const char *) "   .     ",
           /* line */ (const char *) "   .     ",
           /* line */ (const char *) "   ....  ",
           /* line */ (const char *) "^......  ",
           /* line */ (const char *) "   .....^",
           /* line */ (const char *) "   ....  ",
           /* line */ (const char *) "   ....  ",
           /* line */ (const char *) "     ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^      ",
           /* line */ (const char *) "   .      ",
           /* line */ (const char *) "   .....  ",
           /* line */ (const char *) "^.......  ",
           /* line */ (const char *) "   ......^",
           /* line */ (const char *) "   .....  ",
           /* line */ (const char *) "   .....  ",
           /* line */ (const char *) "    .     ",
           /* line */ (const char *) "    ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^    ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " .     ",
           /* line */ (const char *) " ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^  ",
           /* line */ (const char *) "^...^",
           /* line */ (const char *) " .g. ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) "  ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^  ",
           /* line */ (const char *) " ....^",
           /* line */ (const char *) "^.... ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^   ",
           /* line */ (const char *) " .   ",
           /* line */ (const char *) " .   ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) "^.g.^",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) "  .  ",
           /* line */ (const char *) "  ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^      ",
           /* line */ (const char *) "  .....   ",
           /* line */ (const char *) "^......   ",
           /* line */ (const char *) "  .x.g...^",
           /* line */ (const char *) " ......   ",
           /* line */ (const char *) " m.. ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^   ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " .m.^",
           /* line */ (const char *) "^... ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^   ",
           /* line */ (const char *) "^....^",
           /* line */ (const char *) " .|.. ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^    ",
           /* line */ (const char *) " ....^",
           /* line */ (const char *) "^.... ",
           /* line */ (const char *) " .x.. ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^     ",
           /* line */ (const char *) "^.....^",
           /* line */ (const char *) " .x.   ",
           /* line */ (const char *) " ...   ",
           /* line */ (const char *) " ...   ",
           /* line */ (const char *) "  .    ",
           /* line */ (const char *) "  .    ",
           /* line */ (const char *) "  .    ",
           /* line */ (const char *) "  ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^   ",
           /* line */ (const char *) "^... ",
           /* line */ (const char *) " ...^",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^    ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "^.xx. ",
           /* line */ (const char *) " .xx. ",
           /* line */ (const char *) " ....^",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) " ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^    ",
           /* line */ (const char *) " ....^",
           /* line */ (const char *) "^..m. ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "   ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^  ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) "^...^",
           /* line */ (const char *) " .m. ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) "  ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^   ",
           /* line */ (const char *) " .   ",
           /* line */ (const char *) " .   ",
           /* line */ (const char *) " .   ",
           /* line */ (const char *) " ...^",
           /* line */ (const char *) "^... ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) "  .  ",
           /* line */ (const char *) "  ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^   ",
           /* line */ (const char *) "^...... ",
           /* line */ (const char *) "    .|. ",
           /* line */ (const char *) "    ...^",
           /* line */ (const char *) "    ... ",
           /* line */ (const char *) "     ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^  ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " .g.|. ",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) " .g.m.^",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^    ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "^.....^",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^       ",
           /* line */ (const char *) "^......   ",
           /* line */ (const char *) "  .....   ",
           /* line */ (const char *) "  ..m..   ",
           /* line */ (const char *) "  .......^",
           /* line */ (const char *) "  .....   ",
           /* line */ (const char *) "   .      ",
           /* line */ (const char *) "   .      ",
           /* line */ (const char *) "   .      ",
           /* line */ (const char *) "   .      ",
           /* line */ (const char *) "   ^      ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^  ",
           /* line */ (const char *) "  .  ",
           /* line */ (const char *) "  .  ",
           /* line */ (const char *) "  .  ",
           /* line */ (const char *) "  .  ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) "^.m.^",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) "  .  ",
           /* line */ (const char *) "  ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^  ",
           /* line */ (const char *) " ....^",
           /* line */ (const char *) "^.... ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) " ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^   ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) "^.|.^",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) "  ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^   ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) "^... ",
           /* line */ (const char *) " ...^",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) "  ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^    ",
           /* line */ (const char *) "^.... ",
           /* line */ (const char *) " ....^",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) " ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^  ",
           /* line */ (const char *) " ...^",
           /* line */ (const char *) " .|. ",
           /* line */ (const char *) "^... ",
           /* line */ (const char *) " .g. ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) "  ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^   ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) "^..x.. ",
           /* line */ (const char *) " x.... ",
           /* line */ (const char *) " xx... ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^  ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) "^...^",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^  ",
           /* line */ (const char *) "    .  ",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) "  .... ",
           /* line */ (const char *) "  .g..^",
           /* line */ (const char *) "  .... ",
           /* line */ (const char *) "   .   ",
           /* line */ (const char *) "   .   ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^  ",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) " .m...^",
           /* line */ (const char *) " ...m. ",
           /* line */ (const char *) " x.... ",
           /* line */ (const char *) " xx... ",
           /* line */ (const char *) "    ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^     ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^   ",
           /* line */ (const char *) "   .   ",
           /* line */ (const char *) "   .   ",
           /* line */ (const char *) "  ..xx ",
           /* line */ (const char *) "  ...x ",
           /* line */ (const char *) "^..|..^",
           /* line */ (const char *) "  .... ",
           /* line */ (const char *) "   .   ",
           /* line */ (const char *) "   .   ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^   ",
           /* line */ (const char *) "  ......^",
           /* line */ (const char *) "^..x.m.  ",
           /* line */ (const char *) "  .....  ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^   ",
           /* line */ (const char *) " ...^",
           /* line */ (const char *) " .g. ",
           /* line */ (const char *) "^... ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^  ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " .xDx. ",
           /* line */ (const char *) " .xmx. ",
           /* line */ (const char *) "^.xxx.^",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "    ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^  ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) "^.x.|. ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "  ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^    ",
           /* line */ (const char *) "^.... ",
           /* line */ (const char *) " ....^",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) " ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^  .m ",
           /* line */ (const char *) " ..C.. ",
           /* line */ (const char *) " ..CC  ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) "^..|.  ",
           /* line */ (const char *) " ....  ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^    ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "^.x..^",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) " ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^    ",
           /* line */ (const char *) " .    ",
           /* line */ (const char *) " .    ",
           /* line */ (const char *) " .    ",
           /* line */ (const char *) " ...  ",
           /* line */ (const char *) " .x.  ",
           /* line */ (const char *) " ...  ",
           /* line */ (const char *) "^.m..^",
           /* line */ (const char *) " ...  ",
           /* line */ (const char *) "  .   ",
           /* line */ (const char *) "  .   ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^     ",
           /* line */ (const char *) "^.......  ",
           /* line */ (const char *) "    .....^",
           /* line */ (const char *) "    .g..  ",
           /* line */ (const char *) "    ....  ",
           /* line */ (const char *) "    ....  ",
           /* line */ (const char *) "    .     ",
           /* line */ (const char *) "    ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "m.^  `$  ",
           /* line */ (const char *) "...````  ",
           /* line */ (const char *) " ...```  ",
           /* line */ (const char *) "^.......^",
           /* line */ (const char *) " .m...   ",
           /* line */ (const char *) " ^       ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^   ",
           /* line */ (const char *) " xx..  ",
           /* line */ (const char *) " x...  ",
           /* line */ (const char *) "^..|.  ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " . ..m ",
           /* line */ (const char *) " .     ",
           /* line */ (const char *) " .     ",
           /* line */ (const char *) " ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^    ",
           /* line */ (const char *) "^.....  ",
           /* line */ (const char *) " ..|...^",
           /* line */ (const char *) " .....  ",
           /* line */ (const char *) "   .    ",
           /* line */ (const char *) "   ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^ .... ",
           /* line */ (const char *) "   ....G. ",
           /* line */ (const char *) "   ..x... ",
           /* line */ (const char *) "   .xxx.. ",
           /* line */ (const char *) "^....x...^",
           /* line */ (const char *) "   .....  ",
           /* line */ (const char *) "   ^      ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^  ",
           /* line */ (const char *) " xxx.. ",
           /* line */ (const char *) " x.... ",
           /* line */ (const char *) " x.x.. ",
           /* line */ (const char *) "^.....^",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "    ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^    ",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) " ..m..^",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^    ",
           /* line */ (const char *) "  .    ",
           /* line */ (const char *) "  .    ",
           /* line */ (const char *) "  .    ",
           /* line */ (const char *) "^.....^",
           /* line */ (const char *) "  .x.  ",
           /* line */ (const char *) "  ...  ",
           /* line */ (const char *) "  ...  ",
           /* line */ (const char *) "   .   ",
           /* line */ (const char *) "   .   ",
           /* line */ (const char *) "   .   ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^     ",
           /* line */ (const char *) "   .     ",
           /* line */ (const char *) " ...xx   ",
           /* line */ (const char *) " .g..x   ",
           /* line */ (const char *) "^.......^",
           /* line */ (const char *) " ..|..   ",
           /* line */ (const char *) " .....   ",
           /* line */ (const char *) "   ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^   ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "^....^",
           /* line */ (const char *) " ..x. ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^     ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "^.....^",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^   ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "^....^",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "   ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^   ",
           /* line */ (const char *) "  .   ",
           /* line */ (const char *) "  .   ",
           /* line */ (const char *) "  .   ",
           /* line */ (const char *) "  .   ",
           /* line */ (const char *) "^...  ",
           /* line */ (const char *) " .m..^",
           /* line */ (const char *) " ...  ",
           /* line */ (const char *) " .g.  ",
           /* line */ (const char *) " ...  ",
           /* line */ (const char *) "  .   ",
           /* line */ (const char *) "  .   ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^  ",
           /* line */ (const char *) "^.... ",
           /* line */ (const char *) " .x..^",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^   ",
           /* line */ (const char *) "^... ",
           /* line */ (const char *) " .x. ",
           /* line */ (const char *) " ...^",
           /* line */ (const char *) " .x. ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) "  ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^       ",
           /* line */ (const char *) "   .       ",
           /* line */ (const char *) "   .....   ",
           /* line */ (const char *) "^....m....^",
           /* line */ (const char *) "   .....   ",
           /* line */ (const char *) "     ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^     ",
           /* line */ (const char *) "   .     ",
           /* line */ (const char *) "   ....  ",
           /* line */ (const char *) "   ..m.  ",
           /* line */ (const char *) "   .....^",
           /* line */ (const char *) "^...x..  ",
           /* line */ (const char *) "   ....  ",
           /* line */ (const char *) "    .    ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^   ",
           /* line */ (const char *) "^... ",
           /* line */ (const char *) " .x.^",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^    ",
           /* line */ (const char *) "^.....^",
           /* line */ (const char *) " .x.|. ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^   ",
           /* line */ (const char *) "^.... ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) " .x..^",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "   ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^   ",
           /* line */ (const char *) "^...^",
           /* line */ (const char *) " .g. ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) "  ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^     ",
           /* line */ (const char *) "   .     ",
           /* line */ (const char *) "^....... ",
           /* line */ (const char *) "   .m... ",
           /* line */ (const char *) "   ...x.^",
           /* line */ (const char *) "   ..... ",
           /* line */ (const char *) "      ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^   ",
           /* line */ (const char *) " ...^",
           /* line */ (const char *) "^.|. ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) "  ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^   ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) " .|..^",
           /* line */ (const char *) "^.... ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "   ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^   ",
           /* line */ (const char *) "     .   ",
           /* line */ (const char *) "     .   ",
           /* line */ (const char *) "     .   ",
           /* line */ (const char *) "     .   ",
           /* line */ (const char *) "    ...  ",
           /* line */ (const char *) "^....G..^",
           /* line */ (const char *) "    ...  ",
           /* line */ (const char *) "    .g.  ",
           /* line */ (const char *) "    ...  ",
           /* line */ (const char *) "     .   ",
           /* line */ (const char *) "     .   ",
           /* line */ (const char *) "     ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^   ",
           /* line */ (const char *) "^...^",
           /* line */ (const char *) " .x. ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^    ",
           /* line */ (const char *) "  .    ",
           /* line */ (const char *) "  .    ",
           /* line */ (const char *) "  .    ",
           /* line */ (const char *) "  .    ",
           /* line */ (const char *) " ...   ",
           /* line */ (const char *) "^.x...^",
           /* line */ (const char *) " ...   ",
           /* line */ (const char *) " .m.   ",
           /* line */ (const char *) " ...   ",
           /* line */ (const char *) " ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^     ",
           /* line */ (const char *) "^.....^",
           /* line */ (const char *) " .m.m. ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^   ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "^....^",
           /* line */ (const char *) " .m.. ",
           /* line */ (const char *) " ...x ",
           /* line */ (const char *) " ..xx ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^  ",
           /* line */ (const char *) "   .  ",
           /* line */ (const char *) " ....^",
           /* line */ (const char *) "^..m. ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "   .  ",
           /* line */ (const char *) "   ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^    ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "  ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^   ",
           /* line */ (const char *) " ...^",
           /* line */ (const char *) "^.g. ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " .m. ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) "  ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^     ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) "^..m.. ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^    ",
           /* line */ (const char *) " .    ",
           /* line */ (const char *) " ....^",
           /* line */ (const char *) "^...  ",
           /* line */ (const char *) " ...  ",
           /* line */ (const char *) " ...  ",
           /* line */ (const char *) "  .   ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^  ",
           /* line */ (const char *) "  ... ",
           /* line */ (const char *) "  .G. ",
           /* line */ (const char *) "  ...^",
           /* line */ (const char *) "^..M. ",
           /* line */ (const char *) "  ... ",
           /* line */ (const char *) "  .   ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^   ",
           /* line */ (const char *) " ...^",
           /* line */ (const char *) "^... ",
           /* line */ (const char *) " .g. ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) "  ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^   ",
           /* line */ (const char *) "  .....  ",
           /* line */ (const char *) "^..xx..  ",
           /* line */ (const char *) "  .xx...^",
           /* line */ (const char *) "  .....  ",
           /* line */ (const char *) "     .   ",
           /* line */ (const char *) "     ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^      ",
           /* line */ (const char *) "   .      ",
           /* line */ (const char *) "  .....   ",
           /* line */ (const char *) "^......   ",
           /* line */ (const char *) "  .....   ",
           /* line */ (const char *) "  .......^",
           /* line */ (const char *) "  .....   ",
           /* line */ (const char *) "   .      ",
           /* line */ (const char *) "   ^      ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^       ",
           /* line */ (const char *) "  .       ",
           /* line */ (const char *) "^........^",
           /* line */ (const char *) "  .....   ",
           /* line */ (const char *) "  .....   ",
           /* line */ (const char *) "   .      ",
           /* line */ (const char *) "   .      ",
           /* line */ (const char *) "   ^      ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^     ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "    ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^    ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "      ^   ",
           /* line */ (const char *) "      .   ",
           /* line */ (const char *) "   ......^",
           /* line */ (const char *) "^...xxx.  ",
           /* line */ (const char *) "   .sTx.  ",
           /* line */ (const char *) "   .xxx.  ",
           /* line */ (const char *) "   .....  ",
           /* line */ (const char *) "   ^      ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^  ",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) " .g.m.^",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^    ",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) " x.x.. ",
           /* line */ (const char *) " x.... ",
           /* line */ (const char *) " xxx.. ",
           /* line */ (const char *) "    ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^  ",
           /* line */ (const char *) " xx..^",
           /* line */ (const char *) " x... ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "^.x.. ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "   ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^      ",
           /* line */ (const char *) " .....  ",
           /* line */ (const char *) "^.m.g..^",
           /* line */ (const char *) " .....  ",
           /* line */ (const char *) " .      ",
           /* line */ (const char *) " .      ",
           /* line */ (const char *) " ^      ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^    ",
           /* line */ (const char *) "^....^",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) " ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^     ",
           /* line */ (const char *) "  .     ",
           /* line */ (const char *) "  ....  ",
           /* line */ (const char *) "  ....  ",
           /* line */ (const char *) "  ....  ",
           /* line */ (const char *) "^......^",
           /* line */ (const char *) "  ....  ",
           /* line */ (const char *) "   .    ",
           /* line */ (const char *) "   ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^     ",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "  ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^   ",
           /* line */ (const char *) "^... ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " ...^",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^    ",
           /* line */ (const char *) "    ....  ",
           /* line */ (const char *) "^.......  ",
           /* line */ (const char *) "    ..|..^",
           /* line */ (const char *) "    ....  ",
           /* line */ (const char *) "     .    ",
           /* line */ (const char *) "     ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^   ",
           /* line */ (const char *) "    .   ",
           /* line */ (const char *) "    .   ",
           /* line */ (const char *) "    .   ",
           /* line */ (const char *) "    ...^",
           /* line */ (const char *) "^...... ",
           /* line */ (const char *) "    ... ",
           /* line */ (const char *) "     ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^   ",
           /* line */ (const char *) "   .   ",
           /* line */ (const char *) "  ...  ",
           /* line */ (const char *) "  .g..^",
           /* line */ (const char *) "^....  ",
           /* line */ (const char *) "  ...  ",
           /* line */ (const char *) "   .   ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^   ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "^....^",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "   ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^      ",
           /* line */ (const char *) "  .      ",
           /* line */ (const char *) "^.......^",
           /* line */ (const char *) "  .....  ",
           /* line */ (const char *) "  .....  ",
           /* line */ (const char *) "  .....  ",
           /* line */ (const char *) "  .....  ",
           /* line */ (const char *) "  ^      ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^     ",
           /* line */ (const char *) "     .     ",
           /* line */ (const char *) "  .....    ",
           /* line */ (const char *) "  .....    ",
           /* line */ (const char *) "^.........^",
           /* line */ (const char *) "  .....    ",
           /* line */ (const char *) "    ^      ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^    ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^    ",
           /* line */ (const char *) "   ....^",
           /* line */ (const char *) "^.....  ",
           /* line */ (const char *) "   .m.  ",
           /* line */ (const char *) "   ...  ",
           /* line */ (const char *) "    .   ",
           /* line */ (const char *) "    .   ",
           /* line */ (const char *) "    .   ",
           /* line */ (const char *) "    ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^  ",
           /* line */ (const char *) " ....^",
           /* line */ (const char *) "^.... ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "   ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^      ",
           /* line */ (const char *) " .......^",
           /* line */ (const char *) "^..m.    ",
           /* line */ (const char *) " ....    ",
           /* line */ (const char *) "   ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^    ",
           /* line */ (const char *) "  .    ",
           /* line */ (const char *) "  .    ",
           /* line */ (const char *) "  ...  ",
           /* line */ (const char *) "  ...  ",
           /* line */ (const char *) "^..G.  ",
           /* line */ (const char *) "  ....^",
           /* line */ (const char *) "  ...  ",
           /* line */ (const char *) "   .   ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^      ",
           /* line */ (const char *) "   .      ",
           /* line */ (const char *) "   .      ",
           /* line */ (const char *) "   .      ",
           /* line */ (const char *) "   ......^",
           /* line */ (const char *) "   ....   ",
           /* line */ (const char *) "   ..xx   ",
           /* line */ (const char *) "^...xxx   ",
           /* line */ (const char *) "   .xxx   ",
           /* line */ (const char *) "   .      ",
           /* line */ (const char *) "   ^      ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^    ",
           /* line */ (const char *) "   .    ",
           /* line */ (const char *) "  ..xx  ",
           /* line */ (const char *) "  ...x  ",
           /* line */ (const char *) "  .x...^",
           /* line */ (const char *) "^.....  ",
           /* line */ (const char *) "  ....  ",
           /* line */ (const char *) "  .     ",
           /* line */ (const char *) "  ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^   ",
           /* line */ (const char *) "^... ",
           /* line */ (const char *) " ...^",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^   ",
           /* line */ (const char *) "^... ",
           /* line */ (const char *) " .g.^",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) "  ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^     ",
           /* line */ (const char *) "  .     ",
           /* line */ (const char *) "  .     ",
           /* line */ (const char *) "  .....^",
           /* line */ (const char *) "^..g.   ",
           /* line */ (const char *) "  ...   ",
           /* line */ (const char *) "  .     ",
           /* line */ (const char *) "  .     ",
           /* line */ (const char *) "  .     ",
           /* line */ (const char *) "  ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^    ",
           /* line */ (const char *) "     .    ",
           /* line */ (const char *) "^........^",
           /* line */ (const char *) "   .....  ",
           /* line */ (const char *) "   .....  ",
           /* line */ (const char *) "    ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^     ",
           /* line */ (const char *) "    .     ",
           /* line */ (const char *) "^.......  ",
           /* line */ (const char *) "   .....  ",
           /* line */ (const char *) "   .xx..  ",
           /* line */ (const char *) "   .xx...^",
           /* line */ (const char *) "   .....  ",
           /* line */ (const char *) "    .     ",
           /* line */ (const char *) "    ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^    ",
           /* line */ (const char *) "  .    ",
           /* line */ (const char *) "  .    ",
           /* line */ (const char *) "  .    ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) " ..g.  ",
           /* line */ (const char *) " ....  ",
           /* line */ (const char *) "^..m.  ",
           /* line */ (const char *) " ....  ",
           /* line */ (const char *) "  ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^   ",
           /* line */ (const char *) "   .   ",
           /* line */ (const char *) " ....  ",
           /* line */ (const char *) " ..x..^",
           /* line */ (const char *) " ....  ",
           /* line */ (const char *) "^..|.  ",
           /* line */ (const char *) " ....  ",
           /* line */ (const char *) " .     ",
           /* line */ (const char *) " .     ",
           /* line */ (const char *) " ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^   ",
           /* line */ (const char *) "   .   ",
           /* line */ (const char *) "   .   ",
           /* line */ (const char *) "   .   ",
           /* line */ (const char *) " ....  ",
           /* line */ (const char *) "^.g...^",
           /* line */ (const char *) " ....  ",
           /* line */ (const char *) " ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^   ",
           /* line */ (const char *) " .   ",
           /* line */ (const char *) " .   ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " .x. ",
           /* line */ (const char *) " ...^",
           /* line */ (const char *) "^.x. ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) "  .  ",
           /* line */ (const char *) "  .  ",
           /* line */ (const char *) "  .  ",
           /* line */ (const char *) "  ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^   ",
           /* line */ (const char *) " ...^",
           /* line */ (const char *) "^.|. ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) "  ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^    ",
           /* line */ (const char *) " .    ",
           /* line */ (const char *) " .    ",
           /* line */ (const char *) " .    ",
           /* line */ (const char *) " ...  ",
           /* line */ (const char *) "^...  ",
           /* line */ (const char *) " ...  ",
           /* line */ (const char *) " ....^",
           /* line */ (const char *) " ...  ",
           /* line */ (const char *) " .    ",
           /* line */ (const char *) " ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^   ",
           /* line */ (const char *) " ...^",
           /* line */ (const char *) "^.m. ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) "  ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^  ",
           /* line */ (const char *) " ...^",
           /* line */ (const char *) "^... ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^        ",
           /* line */ (const char *) "  .        ",
           /* line */ (const char *) "  .....    ",
           /* line */ (const char *) "^.........^",
           /* line */ (const char *) "  .....    ",
           /* line */ (const char *) "  .        ",
           /* line */ (const char *) "  .        ",
           /* line */ (const char *) "  ^        ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^  ",
           /* line */ (const char *) "^...^",
           /* line */ (const char *) " .|. ",
           /* line */ (const char *) " ... ",
           /* line */ (const char *) " ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^     ",
           /* line */ (const char *) " ...    ",
           /* line */ (const char *) " .g.    ",
           /* line */ (const char *) "^......^",
           /* line */ (const char *) " ...    ",
           /* line */ (const char *) "  .     ",
           /* line */ (const char *) "  ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^   ",
           /* line */ (const char *) "   .   ",
           /* line */ (const char *) "  ...  ",
           /* line */ (const char *) "  ....^",
           /* line */ (const char *) "^....  ",
           /* line */ (const char *) "  ...  ",
           /* line */ (const char *) "   .   ",
           /* line */ (const char *) "   .   ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^  ",
           /* line */ (const char *) "^.... ",
           /* line */ (const char *) " ..|.^",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "  .   ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^     ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^   ",
           /* line */ (const char *) "^...xx ",
           /* line */ (const char *) " ....x ",
           /* line */ (const char *) " ..x..^",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^   ",
           /* line */ (const char *) "  ....^",
           /* line */ (const char *) "  .m.  ",
           /* line */ (const char *) "  ...  ",
           /* line */ (const char *) "^..m.  ",
           /* line */ (const char *) "  ...  ",
           /* line */ (const char *) "  .    ",
           /* line */ (const char *) "  .    ",
           /* line */ (const char *) "  ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^  ",
           /* line */ (const char *) "   .  ",
           /* line */ (const char *) "^.... ",
           /* line */ (const char *) "  ...^",
           /* line */ (const char *) "  ... ",
           /* line */ (const char *) "  ... ",
           /* line */ (const char *) "  .   ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);
}
