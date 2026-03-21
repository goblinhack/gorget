//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_charmap.hpp"
#include "my_level.hpp"

//
// 1000 rooms of type 'cross_sym' from seed 'maniac'
//
void rooms_cross_sym(Gamep g)
{
  TRACE();

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^       ",
           /* line */ (const char *) "   .       ",
           /* line */ (const char *) "   .       ",
           /* line */ (const char *) "   ..      ",
           /* line */ (const char *) " ......    ",
           /* line */ (const char *) "^.........^",
           /* line */ (const char *) "   ..      ",
           /* line */ (const char *) "   ^       ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^   ",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) "^.......^",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "     ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^      ",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) " .|..g..^",
           /* line */ (const char *) "^....... ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "     .   ",
           /* line */ (const char *) "     .   ",
           /* line */ (const char *) "     .   ",
           /* line */ (const char *) "     ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^   ",
           /* line */ (const char *) "    .   ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "^......^",
           /* line */ (const char *) "  ....  ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "    .   ",
           /* line */ (const char *) "    .   ",
           /* line */ (const char *) "    ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^     ",
           /* line */ (const char *) "  .     ",
           /* line */ (const char *) "  ..    ",
           /* line */ (const char *) "^......^",
           /* line */ (const char *) " ....   ",
           /* line */ (const char *) "  ..    ",
           /* line */ (const char *) "   ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^      ",
           /* line */ (const char *) "   .....   ",
           /* line */ (const char *) "^...|.x...^",
           /* line */ (const char *) "   .....   ",
           /* line */ (const char *) "     ..    ",
           /* line */ (const char *) "     ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^       ",
           /* line */ (const char *) "    .       ",
           /* line */ (const char *) "    .       ",
           /* line */ (const char *) "    ..      ",
           /* line */ (const char *) "^..........^",
           /* line */ (const char *) "  ......    ",
           /* line */ (const char *) "    ..      ",
           /* line */ (const char *) "     ^      ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^    ",
           /* line */ (const char *) "   .    ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "^...... ",
           /* line */ (const char *) " ......^",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "    ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "      ^   ",
           /* line */ (const char *) "   .....  ",
           /* line */ (const char *) "   .G.x.  ",
           /* line */ (const char *) "^........^",
           /* line */ (const char *) "     ..   ",
           /* line */ (const char *) "      .   ",
           /* line */ (const char *) "      ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^   ",
           /* line */ (const char *) "    .   ",
           /* line */ (const char *) "    ..  ",
           /* line */ (const char *) "   .... ",
           /* line */ (const char *) "^......^",
           /* line */ (const char *) "    ..  ",
           /* line */ (const char *) "     ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^  ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "    .  ",
           /* line */ (const char *) "    .  ",
           /* line */ (const char *) "    .  ",
           /* line */ (const char *) "    ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "      ^    ",
           /* line */ (const char *) "      .    ",
           /* line */ (const char *) "^........  ",
           /* line */ (const char *) "  .g..x..  ",
           /* line */ (const char *) "  ........^",
           /* line */ (const char *) "     ..    ",
           /* line */ (const char *) "     .     ",
           /* line */ (const char *) "     ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^    ",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) " .x.g. ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "    ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^      ",
           /* line */ (const char *) "  .....   ",
           /* line */ (const char *) "  .g.m...^",
           /* line */ (const char *) "^......   ",
           /* line */ (const char *) "    ..    ",
           /* line */ (const char *) "    .     ",
           /* line */ (const char *) "    ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^  ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "^....^",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "   ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "      ^    ",
           /* line */ (const char *) " .........^",
           /* line */ (const char *) " .......   ",
           /* line */ (const char *) "^.......   ",
           /* line */ (const char *) "    ..     ",
           /* line */ (const char *) "     .     ",
           /* line */ (const char *) "     .     ",
           /* line */ (const char *) "     ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^     ",
           /* line */ (const char *) "  ..... ",
           /* line */ (const char *) "  ..... ",
           /* line */ (const char *) "^......^",
           /* line */ (const char *) "    ..  ",
           /* line */ (const char *) "    .   ",
           /* line */ (const char *) "    .   ",
           /* line */ (const char *) "    ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^     ",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) "^.......^",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^    ",
           /* line */ (const char *) "    .    ",
           /* line */ (const char *) " .......^",
           /* line */ (const char *) "^.g.m.   ",
           /* line */ (const char *) " .....   ",
           /* line */ (const char *) "   ..    ",
           /* line */ (const char *) "    .    ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^    ",
           /* line */ (const char *) "  ..    ",
           /* line */ (const char *) " ....   ",
           /* line */ (const char *) "^......^",
           /* line */ (const char *) "  ..    ",
           /* line */ (const char *) "  ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "      ^  ",
           /* line */ (const char *) "     ..  ",
           /* line */ (const char *) "^....... ",
           /* line */ (const char *) "    ....^",
           /* line */ (const char *) "     ..  ",
           /* line */ (const char *) "     .   ",
           /* line */ (const char *) "     ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^    ",
           /* line */ (const char *) " .......^",
           /* line */ (const char *) " ..g.g.. ",
           /* line */ (const char *) "^....... ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "     ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^    ",
           /* line */ (const char *) "   .    ",
           /* line */ (const char *) "   .    ",
           /* line */ (const char *) "  .....^",
           /* line */ (const char *) "^..g.x. ",
           /* line */ (const char *) "  ..... ",
           /* line */ (const char *) "    ..  ",
           /* line */ (const char *) "     .  ",
           /* line */ (const char *) "     ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^    ",
           /* line */ (const char *) "  ....... ",
           /* line */ (const char *) "  .......^",
           /* line */ (const char *) "^........ ",
           /* line */ (const char *) "     ..   ",
           /* line */ (const char *) "     .    ",
           /* line */ (const char *) "     .    ",
           /* line */ (const char *) "     ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^   ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "^....^",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "   ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^     ",
           /* line */ (const char *) "    ..     ",
           /* line */ (const char *) "  ........^",
           /* line */ (const char *) "^.......   ",
           /* line */ (const char *) "    ..     ",
           /* line */ (const char *) "     ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^     ",
           /* line */ (const char *) "^.....^",
           /* line */ (const char *) " .|.x. ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "      ^  ",
           /* line */ (const char *) "^.......^",
           /* line */ (const char *) " .|.|.|. ",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "     ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^      ",
           /* line */ (const char *) "    .      ",
           /* line */ (const char *) "   ..      ",
           /* line */ (const char *) "^.........^",
           /* line */ (const char *) " ......    ",
           /* line */ (const char *) "   ..      ",
           /* line */ (const char *) "   .       ",
           /* line */ (const char *) "   ^       ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^   ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^       ",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) " ..g.m.. ",
           /* line */ (const char *) "^.......^",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "     ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^   ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) " ......^",
           /* line */ (const char *) "^...... ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "   ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^     ",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) " ..x.x..^",
           /* line */ (const char *) "^....... ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^       ",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) "^.......^",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "     ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "       ^     ",
           /* line */ (const char *) "       .     ",
           /* line */ (const char *) "^.........   ",
           /* line */ (const char *) "   .|..x..   ",
           /* line */ (const char *) "   .........^",
           /* line */ (const char *) "      ..     ",
           /* line */ (const char *) "       .     ",
           /* line */ (const char *) "       ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^       ",
           /* line */ (const char *) " .......^",
           /* line */ (const char *) "^....... ",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^   ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "^....^",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^    ",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) "^.......^",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^   ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) " ......^",
           /* line */ (const char *) "^...... ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "    ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^   ",
           /* line */ (const char *) "    ..  ",
           /* line */ (const char *) "   ....^",
           /* line */ (const char *) "^...... ",
           /* line */ (const char *) "    ..  ",
           /* line */ (const char *) "     .  ",
           /* line */ (const char *) "     ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^   ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) " ....^",
           /* line */ (const char *) "^.... ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^     ",
           /* line */ (const char *) "   .     ",
           /* line */ (const char *) "   .     ",
           /* line */ (const char *) "  ..     ",
           /* line */ (const char *) "^.......^",
           /* line */ (const char *) " ....    ",
           /* line */ (const char *) "  ..     ",
           /* line */ (const char *) "  ^      ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^    ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) " ...... ",
           /* line */ (const char *) "^......^",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "   ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^      ",
           /* line */ (const char *) " .......^",
           /* line */ (const char *) "^....... ",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^  ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "^.....^",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^     ",
           /* line */ (const char *) "     .     ",
           /* line */ (const char *) "   ....... ",
           /* line */ (const char *) "   ....... ",
           /* line */ (const char *) "^.........^",
           /* line */ (const char *) "      ..   ",
           /* line */ (const char *) "      ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^      ",
           /* line */ (const char *) "   ..      ",
           /* line */ (const char *) "^.........^",
           /* line */ (const char *) " ......    ",
           /* line */ (const char *) "   ..      ",
           /* line */ (const char *) "   .       ",
           /* line */ (const char *) "   .       ",
           /* line */ (const char *) "   ^       ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^   ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) " ......^",
           /* line */ (const char *) "^...... ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "    ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^   ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "^....^",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "   ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^   ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "^....^",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "   ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "       ^   ",
           /* line */ (const char *) "       .   ",
           /* line */ (const char *) "       .   ",
           /* line */ (const char *) "   ....... ",
           /* line */ (const char *) "^......... ",
           /* line */ (const char *) "   .......^",
           /* line */ (const char *) "      ..   ",
           /* line */ (const char *) "      .    ",
           /* line */ (const char *) "      .    ",
           /* line */ (const char *) "      ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "      ^  ",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) "^.g..g.. ",
           /* line */ (const char *) " .......^",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^  ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " .x.m. ",
           /* line */ (const char *) "^.....^",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^       ",
           /* line */ (const char *) " .....   ",
           /* line */ (const char *) "^.......^",
           /* line */ (const char *) " .....   ",
           /* line */ (const char *) "   ..    ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^     ",
           /* line */ (const char *) "     .     ",
           /* line */ (const char *) "     ..    ",
           /* line */ (const char *) "^.........^",
           /* line */ (const char *) "    ....   ",
           /* line */ (const char *) "     ..    ",
           /* line */ (const char *) "     ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^    ",
           /* line */ (const char *) "     .    ",
           /* line */ (const char *) "    ..    ",
           /* line */ (const char *) "   ......^",
           /* line */ (const char *) "^......   ",
           /* line */ (const char *) "    ..    ",
           /* line */ (const char *) "     .    ",
           /* line */ (const char *) "     ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^    ",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) "^.......^",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "     ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "      ^    ",
           /* line */ (const char *) "     ..    ",
           /* line */ (const char *) "    ....   ",
           /* line */ (const char *) "^.........^",
           /* line */ (const char *) "     ..    ",
           /* line */ (const char *) "     ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^   ",
           /* line */ (const char *) " .......^",
           /* line */ (const char *) "^.g.|.|. ",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "     ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^     ",
           /* line */ (const char *) "  .......^",
           /* line */ (const char *) "^..g.x.   ",
           /* line */ (const char *) "  .....   ",
           /* line */ (const char *) "    ..    ",
           /* line */ (const char *) "    .     ",
           /* line */ (const char *) "    ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^   ",
           /* line */ (const char *) "     .   ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "^.......^",
           /* line */ (const char *) "  ...... ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "     .   ",
           /* line */ (const char *) "     ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^     ",
           /* line */ (const char *) "  ..     ",
           /* line */ (const char *) "^....    ",
           /* line */ (const char *) " .......^",
           /* line */ (const char *) "  ..     ",
           /* line */ (const char *) "  ^      ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^   ",
           /* line */ (const char *) "     .   ",
           /* line */ (const char *) "     .   ",
           /* line */ (const char *) "     .   ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "^.......^",
           /* line */ (const char *) "  ...... ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "     .   ",
           /* line */ (const char *) "     ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "      ^    ",
           /* line */ (const char *) "      .    ",
           /* line */ (const char *) "     ..    ",
           /* line */ (const char *) "^.........^",
           /* line */ (const char *) "   ......  ",
           /* line */ (const char *) "     ..    ",
           /* line */ (const char *) "      ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^    ",
           /* line */ (const char *) "    .    ",
           /* line */ (const char *) "    .    ",
           /* line */ (const char *) "   ..... ",
           /* line */ (const char *) "^.......^",
           /* line */ (const char *) "   ..... ",
           /* line */ (const char *) "     ..  ",
           /* line */ (const char *) "     .   ",
           /* line */ (const char *) "     .   ",
           /* line */ (const char *) "     ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^   ",
           /* line */ (const char *) "     .   ",
           /* line */ (const char *) "     .   ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "^.......^",
           /* line */ (const char *) "   ....  ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "    .    ",
           /* line */ (const char *) "    .    ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^   ",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "    ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^       ",
           /* line */ (const char *) "^....... ",
           /* line */ (const char *) " .x.|.|.^",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^    ",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) " .g.M.|. ",
           /* line */ (const char *) "^.......^",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "     ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^     ",
           /* line */ (const char *) "   ..     ",
           /* line */ (const char *) "^........^",
           /* line */ (const char *) " ......   ",
           /* line */ (const char *) "   ..     ",
           /* line */ (const char *) "   .      ",
           /* line */ (const char *) "   ^      ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^    ",
           /* line */ (const char *) " .......^",
           /* line */ (const char *) "^.g..|.. ",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "     ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^     ",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) " ..G.g..^",
           /* line */ (const char *) "^....... ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "     ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "      ^  ",
           /* line */ (const char *) " .......^",
           /* line */ (const char *) "^.m.g.m. ",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "     ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^    ",
           /* line */ (const char *) "^....... ",
           /* line */ (const char *) " .......^",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "     ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "      ^  ",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) "^.......^",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "     ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "       ^   ",
           /* line */ (const char *) "       .   ",
           /* line */ (const char *) "      ..   ",
           /* line */ (const char *) "    ...... ",
           /* line */ (const char *) "^.........^",
           /* line */ (const char *) "      ..   ",
           /* line */ (const char *) "       .   ",
           /* line */ (const char *) "       ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^    ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "^...... ",
           /* line */ (const char *) " ......^",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "   ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^     ",
           /* line */ (const char *) "^....... ",
           /* line */ (const char *) " .g..g.. ",
           /* line */ (const char *) " .......^",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^    ",
           /* line */ (const char *) "   .    ",
           /* line */ (const char *) "  ..    ",
           /* line */ (const char *) " ....   ",
           /* line */ (const char *) "^......^",
           /* line */ (const char *) "  ..    ",
           /* line */ (const char *) "  ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^    ",
           /* line */ (const char *) "    .    ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "^.......^",
           /* line */ (const char *) "  ...... ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^    ",
           /* line */ (const char *) "   .    ",
           /* line */ (const char *) "   .    ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) " ...... ",
           /* line */ (const char *) "^......^",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "   ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^    ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "^......^",
           /* line */ (const char *) " ...... ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "    ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^  ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "^....^",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "   ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^     ",
           /* line */ (const char *) "     .     ",
           /* line */ (const char *) "^.........^",
           /* line */ (const char *) "   .....   ",
           /* line */ (const char *) "   .....   ",
           /* line */ (const char *) "     ..    ",
           /* line */ (const char *) "     .     ",
           /* line */ (const char *) "     ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^     ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "    ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^    ",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) " ..|..^",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^    ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "    ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^   ",
           /* line */ (const char *) "   .   ",
           /* line */ (const char *) "   .   ",
           /* line */ (const char *) "  ..   ",
           /* line */ (const char *) "^.....^",
           /* line */ (const char *) " ....  ",
           /* line */ (const char *) "  ..   ",
           /* line */ (const char *) "  ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^   ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) " ....^",
           /* line */ (const char *) "^.... ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^     ",
           /* line */ (const char *) "   .     ",
           /* line */ (const char *) "   .     ",
           /* line */ (const char *) " .......^",
           /* line */ (const char *) "^.|.m.   ",
           /* line */ (const char *) " .....   ",
           /* line */ (const char *) "   ..    ",
           /* line */ (const char *) "    .    ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^    ",
           /* line */ (const char *) "   .    ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "^.....  ",
           /* line */ (const char *) "  .....^",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "   ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^    ",
           /* line */ (const char *) "    .    ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "  ......^",
           /* line */ (const char *) "^....... ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "    .    ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^   ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "^......^",
           /* line */ (const char *) " ...... ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "   ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^       ",
           /* line */ (const char *) "^....... ",
           /* line */ (const char *) " .......^",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "     .   ",
           /* line */ (const char *) "     .   ",
           /* line */ (const char *) "     ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^    ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) "^.x.m. ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "      ^  ",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) "^.......^",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "     ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^    ",
           /* line */ (const char *) "   .    ",
           /* line */ (const char *) "^.....  ",
           /* line */ (const char *) " .....  ",
           /* line */ (const char *) " ......^",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "    .   ",
           /* line */ (const char *) "    ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^    ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "^.....^",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "    ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^     ",
           /* line */ (const char *) "    .     ",
           /* line */ (const char *) "   ..     ",
           /* line */ (const char *) "^......   ",
           /* line */ (const char *) " ........^",
           /* line */ (const char *) "   ..     ",
           /* line */ (const char *) "    .     ",
           /* line */ (const char *) "    ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^    ",
           /* line */ (const char *) "^.....^",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "    ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^   ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) " ...... ",
           /* line */ (const char *) "^......^",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "    ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^       ",
           /* line */ (const char *) "^.....   ",
           /* line */ (const char *) " .g.g...^",
           /* line */ (const char *) " .....   ",
           /* line */ (const char *) "   ..    ",
           /* line */ (const char *) "    .    ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^    ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " ..m..^",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^     ",
           /* line */ (const char *) "  .     ",
           /* line */ (const char *) "^......^",
           /* line */ (const char *) "  .|.|. ",
           /* line */ (const char *) "  ..... ",
           /* line */ (const char *) "    ..  ",
           /* line */ (const char *) "    .   ",
           /* line */ (const char *) "    ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^  ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) " ....^",
           /* line */ (const char *) "^.... ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "   ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^   ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) " ...... ",
           /* line */ (const char *) "^......^",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "    ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^  ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^     ",
           /* line */ (const char *) "  .     ",
           /* line */ (const char *) "  .     ",
           /* line */ (const char *) "  ..    ",
           /* line */ (const char *) "^......^",
           /* line */ (const char *) " ....   ",
           /* line */ (const char *) "  ..    ",
           /* line */ (const char *) "  .     ",
           /* line */ (const char *) "  ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^  ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "^.... ",
           /* line */ (const char *) " ....^",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "   ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^      ",
           /* line */ (const char *) "    .      ",
           /* line */ (const char *) "    .      ",
           /* line */ (const char *) "  ........^",
           /* line */ (const char *) "  .......  ",
           /* line */ (const char *) "^........  ",
           /* line */ (const char *) "     ..    ",
           /* line */ (const char *) "     .     ",
           /* line */ (const char *) "     ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^   ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) " ...... ",
           /* line */ (const char *) "^......^",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "    ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "        ^    ",
           /* line */ (const char *) "       ..    ",
           /* line */ (const char *) "     ......  ",
           /* line */ (const char *) "^...........^",
           /* line */ (const char *) "       ..    ",
           /* line */ (const char *) "       .     ",
           /* line */ (const char *) "       ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^    ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) " ......^",
           /* line */ (const char *) "^...... ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "    ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^  ",
           /* line */ (const char *) "^.....^",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "    ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "      ^  ",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) "^....... ",
           /* line */ (const char *) " .......^",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "     ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^  ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " .|.G. ",
           /* line */ (const char *) "^.....^",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^       ",
           /* line */ (const char *) "   .       ",
           /* line */ (const char *) "  .......  ",
           /* line */ (const char *) "  ........^",
           /* line */ (const char *) "^........  ",
           /* line */ (const char *) "     ..    ",
           /* line */ (const char *) "     ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^       ",
           /* line */ (const char *) " .       ",
           /* line */ (const char *) "^.....   ",
           /* line */ (const char *) " .m.|.   ",
           /* line */ (const char *) " .......^",
           /* line */ (const char *) "   ..    ",
           /* line */ (const char *) "    .    ",
           /* line */ (const char *) "    .    ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^    ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "^.|.|. ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^       ",
           /* line */ (const char *) "^..........^",
           /* line */ (const char *) " .......    ",
           /* line */ (const char *) " .......    ",
           /* line */ (const char *) "    ..      ",
           /* line */ (const char *) "     .      ",
           /* line */ (const char *) "     ^      ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^    ",
           /* line */ (const char *) "   .    ",
           /* line */ (const char *) "   .    ",
           /* line */ (const char *) "  ..    ",
           /* line */ (const char *) " ....   ",
           /* line */ (const char *) "^......^",
           /* line */ (const char *) "  ..    ",
           /* line */ (const char *) "  .     ",
           /* line */ (const char *) "  ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "      ^        ",
           /* line */ (const char *) "   ...........^",
           /* line */ (const char *) "^.........     ",
           /* line */ (const char *) "   .......     ",
           /* line */ (const char *) "      ..       ",
           /* line */ (const char *) "       ^       ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^    ",
           /* line */ (const char *) "    .    ",
           /* line */ (const char *) "    .    ",
           /* line */ (const char *) "    .    ",
           /* line */ (const char *) "    .    ",
           /* line */ (const char *) "^....... ",
           /* line */ (const char *) "   .g.|. ",
           /* line */ (const char *) "   .....^",
           /* line */ (const char *) "     ..  ",
           /* line */ (const char *) "      .  ",
           /* line */ (const char *) "      ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^   ",
           /* line */ (const char *) "  ..   ",
           /* line */ (const char *) "^.....^",
           /* line */ (const char *) " ....  ",
           /* line */ (const char *) "  ..   ",
           /* line */ (const char *) "   .   ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^   ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "^.m.|.^",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^    ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^   ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "   .....^",
           /* line */ (const char *) "^......  ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "    .    ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^     ",
           /* line */ (const char *) "     .     ",
           /* line */ (const char *) "     ..    ",
           /* line */ (const char *) "^.........^",
           /* line */ (const char *) "   ......  ",
           /* line */ (const char *) "     ..    ",
           /* line */ (const char *) "      .    ",
           /* line */ (const char *) "      ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^   ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) " ....^",
           /* line */ (const char *) "^.... ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "   ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^       ",
           /* line */ (const char *) "  .....   ",
           /* line */ (const char *) "^......   ",
           /* line */ (const char *) "  .......^",
           /* line */ (const char *) "    ..    ",
           /* line */ (const char *) "     ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^   ",
           /* line */ (const char *) "    .   ",
           /* line */ (const char *) "    ..  ",
           /* line */ (const char *) "^...... ",
           /* line */ (const char *) "   ....^",
           /* line */ (const char *) "    ..  ",
           /* line */ (const char *) "    .   ",
           /* line */ (const char *) "    ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^     ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "^.....^",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "    ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^    ",
           /* line */ (const char *) "    .    ",
           /* line */ (const char *) "   ..    ",
           /* line */ (const char *) " ......  ",
           /* line */ (const char *) "^.......^",
           /* line */ (const char *) "   ..    ",
           /* line */ (const char *) "    .    ",
           /* line */ (const char *) "    .    ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^   ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "^....^",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "   ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^    ",
           /* line */ (const char *) "^.......^",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^   ",
           /* line */ (const char *) "    .   ",
           /* line */ (const char *) "    .   ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "  ....  ",
           /* line */ (const char *) "^......^",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "   .    ",
           /* line */ (const char *) "   ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^  ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "^.....^",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^   ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "^....^",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^     ",
           /* line */ (const char *) "    ..     ",
           /* line */ (const char *) "^......    ",
           /* line */ (const char *) "   .......^",
           /* line */ (const char *) "    ..     ",
           /* line */ (const char *) "     ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^     ",
           /* line */ (const char *) "   .     ",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) "^.......^",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "    .    ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^      ",
           /* line */ (const char *) "    .......^",
           /* line */ (const char *) "    .x..|.. ",
           /* line */ (const char *) "^.......... ",
           /* line */ (const char *) "       ..   ",
           /* line */ (const char *) "        ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^     ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "^..|.. ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^     ",
           /* line */ (const char *) " .......^",
           /* line */ (const char *) "^....... ",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^  ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "^.....^",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "    ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^   ",
           /* line */ (const char *) " .......^",
           /* line */ (const char *) "^....... ",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^  ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "^....^",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "   ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^   ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) " ......^",
           /* line */ (const char *) "^...... ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "    ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^    ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) "^..g.. ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "    ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^   ",
           /* line */ (const char *) "^....... ",
           /* line */ (const char *) " .|..g..^",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "     ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^   ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "^...... ",
           /* line */ (const char *) " ......^",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "   ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^        ",
           /* line */ (const char *) "    .......   ",
           /* line */ (const char *) "    ..g.x....^",
           /* line */ (const char *) "^..........   ",
           /* line */ (const char *) "       ..     ",
           /* line */ (const char *) "        .     ",
           /* line */ (const char *) "        ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "        ^  ",
           /* line */ (const char *) "^......... ",
           /* line */ (const char *) "   .g.|.g.^",
           /* line */ (const char *) "   ....... ",
           /* line */ (const char *) "      ..   ",
           /* line */ (const char *) "      ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^    ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "^...... ",
           /* line */ (const char *) " ......^",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "   ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^     ",
           /* line */ (const char *) "   .     ",
           /* line */ (const char *) "   ..    ",
           /* line */ (const char *) "^.....   ",
           /* line */ (const char *) "  ......^",
           /* line */ (const char *) "   ..    ",
           /* line */ (const char *) "   .     ",
           /* line */ (const char *) "   ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^    ",
           /* line */ (const char *) "     ..   ",
           /* line */ (const char *) "   ...... ",
           /* line */ (const char *) "^........^",
           /* line */ (const char *) "     ..   ",
           /* line */ (const char *) "      ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^    ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "^.....^",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^    ",
           /* line */ (const char *) "   .    ",
           /* line */ (const char *) "   .    ",
           /* line */ (const char *) "  ..... ",
           /* line */ (const char *) "  .x.G.^",
           /* line */ (const char *) "^...... ",
           /* line */ (const char *) "    ..  ",
           /* line */ (const char *) "     .  ",
           /* line */ (const char *) "     .  ",
           /* line */ (const char *) "     ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^     ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " .g.g.^",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "    ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^  ",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) " .x.m.^",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^    ",
           /* line */ (const char *) "  ......^",
           /* line */ (const char *) "^......  ",
           /* line */ (const char *) "  .....  ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^    ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "^...... ",
           /* line */ (const char *) " ......^",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "    ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^     ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "    ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^   ",
           /* line */ (const char *) "   .   ",
           /* line */ (const char *) "  ..   ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) "^....  ",
           /* line */ (const char *) "  ..   ",
           /* line */ (const char *) "  ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^      ",
           /* line */ (const char *) "^......  ",
           /* line */ (const char *) "  ..g..  ",
           /* line */ (const char *) "  ......^",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "    .    ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^  ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "^....^",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^    ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "^...... ",
           /* line */ (const char *) " ......^",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "    ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^   ",
           /* line */ (const char *) "^....... ",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) " .......^",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^   ",
           /* line */ (const char *) "    ..  ",
           /* line */ (const char *) "^......^",
           /* line */ (const char *) "   .... ",
           /* line */ (const char *) "    ..  ",
           /* line */ (const char *) "    .   ",
           /* line */ (const char *) "    .   ",
           /* line */ (const char *) "    ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^     ",
           /* line */ (const char *) "     .     ",
           /* line */ (const char *) "^........  ",
           /* line */ (const char *) "  ........^",
           /* line */ (const char *) "  .......  ",
           /* line */ (const char *) "     ..    ",
           /* line */ (const char *) "     .     ",
           /* line */ (const char *) "     ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "      ^    ",
           /* line */ (const char *) "      .    ",
           /* line */ (const char *) "      .    ",
           /* line */ (const char *) "      .    ",
           /* line */ (const char *) "   .....   ",
           /* line */ (const char *) "^...x.|...^",
           /* line */ (const char *) "   .....   ",
           /* line */ (const char *) "     ..    ",
           /* line */ (const char *) "      ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^    ",
           /* line */ (const char *) "   .....  ",
           /* line */ (const char *) "^........^",
           /* line */ (const char *) "   .....  ",
           /* line */ (const char *) "     ..   ",
           /* line */ (const char *) "      ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^     ",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) " ..g..|.^",
           /* line */ (const char *) "^....... ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^    ",
           /* line */ (const char *) "   .    ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "^.....  ",
           /* line */ (const char *) "  .....^",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "    .   ",
           /* line */ (const char *) "    .   ",
           /* line */ (const char *) "    ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "      ^      ",
           /* line */ (const char *) "   .......   ",
           /* line */ (const char *) "^...m.x.x.   ",
           /* line */ (const char *) "   .........^",
           /* line */ (const char *) "      ..     ",
           /* line */ (const char *) "       .     ",
           /* line */ (const char *) "       .     ",
           /* line */ (const char *) "       ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^   ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) "^..|.. ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^      ",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) "^....... ",
           /* line */ (const char *) " .......^",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "     ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^  ",
           /* line */ (const char *) "    .  ",
           /* line */ (const char *) "    .  ",
           /* line */ (const char *) "    .  ",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "  .... ",
           /* line */ (const char *) "^.....^",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "    .  ",
           /* line */ (const char *) "    ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^  ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) " ....^",
           /* line */ (const char *) "^.... ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^  ",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) "  ....^",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "    ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^    ",
           /* line */ (const char *) "   .    ",
           /* line */ (const char *) "   .    ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "  ....  ",
           /* line */ (const char *) "^......^",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "   .    ",
           /* line */ (const char *) "   ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^    ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) " ......^",
           /* line */ (const char *) "^...... ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "   ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^     ",
           /* line */ (const char *) " .     ",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "   .   ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^      ",
           /* line */ (const char *) " .......^",
           /* line */ (const char *) " ..x..|. ",
           /* line */ (const char *) "^....... ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^      ",
           /* line */ (const char *) "^....... ",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) " .......^",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "     ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^   ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "^....^",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^   ",
           /* line */ (const char *) "     .   ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "^.......^",
           /* line */ (const char *) "  ...... ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "     .   ",
           /* line */ (const char *) "     ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^      ",
           /* line */ (const char *) "     ..     ",
           /* line */ (const char *) "^........   ",
           /* line */ (const char *) "   ........^",
           /* line */ (const char *) "     ..     ",
           /* line */ (const char *) "     ^      ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^    ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "^.......^",
           /* line */ (const char *) "  ...... ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "    .    ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^   ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) " ......^",
           /* line */ (const char *) "^...... ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "   ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "      ^   ",
           /* line */ (const char *) "      .   ",
           /* line */ (const char *) "     ..   ",
           /* line */ (const char *) "^........^",
           /* line */ (const char *) "    ....  ",
           /* line */ (const char *) "     ..   ",
           /* line */ (const char *) "     ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^        ",
           /* line */ (const char *) "    ........^",
           /* line */ (const char *) "    .|.|.m.  ",
           /* line */ (const char *) "^..........  ",
           /* line */ (const char *) "       ..    ",
           /* line */ (const char *) "       .     ",
           /* line */ (const char *) "       .     ",
           /* line */ (const char *) "       ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^    ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "^...... ",
           /* line */ (const char *) " ......^",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "   ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^  ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "^.... ",
           /* line */ (const char *) " ....^",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "      ^    ",
           /* line */ (const char *) " .......   ",
           /* line */ (const char *) "^.......   ",
           /* line */ (const char *) " .........^",
           /* line */ (const char *) "    ..     ",
           /* line */ (const char *) "     .     ",
           /* line */ (const char *) "     ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^     ",
           /* line */ (const char *) "  .....  ",
           /* line */ (const char *) "  .g.m..^",
           /* line */ (const char *) "^......  ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^    ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "   ....  ",
           /* line */ (const char *) "^.......^",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "    .    ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^    ",
           /* line */ (const char *) "  ......^",
           /* line */ (const char *) "^......  ",
           /* line */ (const char *) "  .....  ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "     .   ",
           /* line */ (const char *) "     .   ",
           /* line */ (const char *) "     ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "        ^     ",
           /* line */ (const char *) "        .     ",
           /* line */ (const char *) "   .......    ",
           /* line */ (const char *) "^............^",
           /* line */ (const char *) "   .......    ",
           /* line */ (const char *) "      ..      ",
           /* line */ (const char *) "      .       ",
           /* line */ (const char *) "      ^       ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^    ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) " ......^",
           /* line */ (const char *) "^...... ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "    ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^   ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " .m.|.^",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^  ",
           /* line */ (const char *) "   .  ",
           /* line */ (const char *) "   .  ",
           /* line */ (const char *) "   .  ",
           /* line */ (const char *) "   .  ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) " ....^",
           /* line */ (const char *) "^.... ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "  .   ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^       ",
           /* line */ (const char *) "  .       ",
           /* line */ (const char *) " ........^",
           /* line */ (const char *) " ..x.m..  ",
           /* line */ (const char *) "^.......  ",
           /* line */ (const char *) "    ..    ",
           /* line */ (const char *) "     .    ",
           /* line */ (const char *) "     ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^  ",
           /* line */ (const char *) "  ..... ",
           /* line */ (const char *) "  ..|.. ",
           /* line */ (const char *) "^......^",
           /* line */ (const char *) "    ..  ",
           /* line */ (const char *) "    .   ",
           /* line */ (const char *) "    .   ",
           /* line */ (const char *) "    ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^   ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "^....^",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^      ",
           /* line */ (const char *) "   .      ",
           /* line */ (const char *) "   ......^",
           /* line */ (const char *) "   .....  ",
           /* line */ (const char *) "^.......  ",
           /* line */ (const char *) "     ..   ",
           /* line */ (const char *) "      .   ",
           /* line */ (const char *) "      ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "      ^      ",
           /* line */ (const char *) "     ..      ",
           /* line */ (const char *) "   .........^",
           /* line */ (const char *) "^........    ",
           /* line */ (const char *) "     ..      ",
           /* line */ (const char *) "     ^       ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^    ",
           /* line */ (const char *) "     .    ",
           /* line */ (const char *) "    ..    ",
           /* line */ (const char *) "^........^",
           /* line */ (const char *) "   ....   ",
           /* line */ (const char *) "    ..    ",
           /* line */ (const char *) "     .    ",
           /* line */ (const char *) "     ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^        ",
           /* line */ (const char *) "    .        ",
           /* line */ (const char *) "    ..       ",
           /* line */ (const char *) "^.......     ",
           /* line */ (const char *) "  ..........^",
           /* line */ (const char *) "    ..       ",
           /* line */ (const char *) "    .        ",
           /* line */ (const char *) "    ^        ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^    ",
           /* line */ (const char *) "    ..    ",
           /* line */ (const char *) "   ....   ",
           /* line */ (const char *) "^........^",
           /* line */ (const char *) "    ..    ",
           /* line */ (const char *) "    .     ",
           /* line */ (const char *) "    .     ",
           /* line */ (const char *) "    ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^     ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "^.x.|. ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "    ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^    ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "^.....^",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "    ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^   ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "^....^",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^   ",
           /* line */ (const char *) "  .   ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "^....^",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "  .   ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^    ",
           /* line */ (const char *) "  .    ",
           /* line */ (const char *) "  .    ",
           /* line */ (const char *) "  .    ",
           /* line */ (const char *) "  ..   ",
           /* line */ (const char *) " ....  ",
           /* line */ (const char *) "^.....^",
           /* line */ (const char *) "  ..   ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^   ",
           /* line */ (const char *) "     .   ",
           /* line */ (const char *) " .......^",
           /* line */ (const char *) "^....... ",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "     ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^   ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "^...... ",
           /* line */ (const char *) " ......^",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "   ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^    ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "^...... ",
           /* line */ (const char *) " ......^",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "   ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^    ",
           /* line */ (const char *) " .......^",
           /* line */ (const char *) "^..x..|. ",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "     ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^       ",
           /* line */ (const char *) "    ..       ",
           /* line */ (const char *) "  ..........^",
           /* line */ (const char *) "^.......     ",
           /* line */ (const char *) "    ..       ",
           /* line */ (const char *) "    ^        ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^     ",
           /* line */ (const char *) "^.....^",
           /* line */ (const char *) " ..g.. ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^  ",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) " .G.|. ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^   ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "^....^",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "   ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^      ",
           /* line */ (const char *) "^.......^",
           /* line */ (const char *) " .g.m.g. ",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^        ",
           /* line */ (const char *) "  .        ",
           /* line */ (const char *) "^.........^",
           /* line */ (const char *) "  .......  ",
           /* line */ (const char *) "  .......  ",
           /* line */ (const char *) "     ..    ",
           /* line */ (const char *) "      .    ",
           /* line */ (const char *) "      ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^   ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "^...... ",
           /* line */ (const char *) " ......^",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "    ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^   ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) " ......^",
           /* line */ (const char *) "^...... ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "   ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^  ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "^....^",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "   ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^    ",
           /* line */ (const char *) "    .    ",
           /* line */ (const char *) "    .    ",
           /* line */ (const char *) "^.......^",
           /* line */ (const char *) "   ..... ",
           /* line */ (const char *) "   ..... ",
           /* line */ (const char *) "     ..  ",
           /* line */ (const char *) "     .   ",
           /* line */ (const char *) "     ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^    ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) " ...... ",
           /* line */ (const char *) "^......^",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "   ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^   ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) " ....^",
           /* line */ (const char *) "^.... ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "   ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^       ",
           /* line */ (const char *) "^....... ",
           /* line */ (const char *) " ..g..|. ",
           /* line */ (const char *) " .......^",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^   ",
           /* line */ (const char *) "^.......^",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "     ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^        ",
           /* line */ (const char *) "  .        ",
           /* line */ (const char *) " .......   ",
           /* line */ (const char *) "^.......   ",
           /* line */ (const char *) " .........^",
           /* line */ (const char *) "    ..     ",
           /* line */ (const char *) "     ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^    ",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) " .......^",
           /* line */ (const char *) "^....... ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^    ",
           /* line */ (const char *) " .......^",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) "^....... ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "     ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^   ",
           /* line */ (const char *) "   .   ",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "  .... ",
           /* line */ (const char *) "^.....^",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "   .   ",
           /* line */ (const char *) "   .   ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^  ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) " .x.g. ",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^       ",
           /* line */ (const char *) "^....... ",
           /* line */ (const char *) " .x.m.m. ",
           /* line */ (const char *) " .......^",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "     ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^      ",
           /* line */ (const char *) "^.......^",
           /* line */ (const char *) " ..g..   ",
           /* line */ (const char *) " .....   ",
           /* line */ (const char *) "   ..    ",
           /* line */ (const char *) "    .    ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "      ^  ",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) " .......^",
           /* line */ (const char *) "^....... ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^     ",
           /* line */ (const char *) "   ..    ",
           /* line */ (const char *) "^.....   ",
           /* line */ (const char *) "  ......^",
           /* line */ (const char *) "   ..    ",
           /* line */ (const char *) "   .     ",
           /* line */ (const char *) "   .     ",
           /* line */ (const char *) "   .     ",
           /* line */ (const char *) "   ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^    ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "    ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^    ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) " ...... ",
           /* line */ (const char *) "^......^",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "   ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^   ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "^.....^",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^     ",
           /* line */ (const char *) "   ..     ",
           /* line */ (const char *) "^......   ",
           /* line */ (const char *) " ........^",
           /* line */ (const char *) "   ..     ",
           /* line */ (const char *) "   .      ",
           /* line */ (const char *) "   .      ",
           /* line */ (const char *) "   ^      ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^   ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "^...... ",
           /* line */ (const char *) " ......^",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "   ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "       ^   ",
           /* line */ (const char *) "  .......  ",
           /* line */ (const char *) "^.........^",
           /* line */ (const char *) "  .......  ",
           /* line */ (const char *) "     ..    ",
           /* line */ (const char *) "     ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^    ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "^......^",
           /* line */ (const char *) " ...... ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "   ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^    ",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) "^....... ",
           /* line */ (const char *) " .......^",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "     ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^   ",
           /* line */ (const char *) "    .   ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "^.....  ",
           /* line */ (const char *) "  .....^",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "    .   ",
           /* line */ (const char *) "    ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^    ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "^......^",
           /* line */ (const char *) " ...... ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "   ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^     ",
           /* line */ (const char *) "   ..    ",
           /* line */ (const char *) " .......^",
           /* line */ (const char *) "^......  ",
           /* line */ (const char *) "   ..    ",
           /* line */ (const char *) "    .    ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "      ^     ",
           /* line */ (const char *) "    .....   ",
           /* line */ (const char *) "^........   ",
           /* line */ (const char *) "    .......^",
           /* line */ (const char *) "      ..    ",
           /* line */ (const char *) "      ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^  ",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) " ..|..^",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "    ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^   ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) " ....^",
           /* line */ (const char *) "^.... ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "   ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^    ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "^.....^",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "    ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^  ",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) " .|.g. ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^   ",
           /* line */ (const char *) "   .   ",
           /* line */ (const char *) "  ..   ",
           /* line */ (const char *) "^.....^",
           /* line */ (const char *) " ....  ",
           /* line */ (const char *) "  ..   ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^   ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "^...... ",
           /* line */ (const char *) " ......^",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "   ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^  ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) " ....^",
           /* line */ (const char *) "^.... ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^      ",
           /* line */ (const char *) "^....... ",
           /* line */ (const char *) " .......^",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^   ",
           /* line */ (const char *) "^.....^",
           /* line */ (const char *) " .m.m. ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "    ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^    ",
           /* line */ (const char *) "   .    ",
           /* line */ (const char *) "   .    ",
           /* line */ (const char *) " .....  ",
           /* line */ (const char *) " .....  ",
           /* line */ (const char *) "^......^",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "   .    ",
           /* line */ (const char *) "   ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^      ",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) "^..g..m. ",
           /* line */ (const char *) " .......^",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "     ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^   ",
           /* line */ (const char *) "    .   ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "  ....  ",
           /* line */ (const char *) "^......^",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "    .   ",
           /* line */ (const char *) "    .   ",
           /* line */ (const char *) "    ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^   ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) " ......^",
           /* line */ (const char *) "^...... ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "    ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^   ",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) "^.......^",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "     ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^     ",
           /* line */ (const char *) "   .     ",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) "^.g..x.. ",
           /* line */ (const char *) " .......^",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "    .    ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^     ",
           /* line */ (const char *) "   ..    ",
           /* line */ (const char *) "^.....   ",
           /* line */ (const char *) "  ......^",
           /* line */ (const char *) "   ..    ",
           /* line */ (const char *) "    .    ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^  ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) " ....^",
           /* line */ (const char *) "^.... ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^    ",
           /* line */ (const char *) "^.......^",
           /* line */ (const char *) " .m.x.x. ",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^  ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) " ....^",
           /* line */ (const char *) "^.... ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^  ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "^.... ",
           /* line */ (const char *) " ....^",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^   ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "^....^",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "   ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^  ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) " ....^",
           /* line */ (const char *) "^.... ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "   ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^   ",
           /* line */ (const char *) "     .   ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "^.......^",
           /* line */ (const char *) "   ....  ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "    .    ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^       ",
           /* line */ (const char *) "    ........^",
           /* line */ (const char *) "^.....m.m..  ",
           /* line */ (const char *) "    .......  ",
           /* line */ (const char *) "       ..    ",
           /* line */ (const char *) "       ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^     ",
           /* line */ (const char *) "  .....    ",
           /* line */ (const char *) "^.........^",
           /* line */ (const char *) "  .....    ",
           /* line */ (const char *) "    ..     ",
           /* line */ (const char *) "     ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^     ",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "    ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^    ",
           /* line */ (const char *) "  ..   ",
           /* line */ (const char *) "^....  ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) "  ..   ",
           /* line */ (const char *) "   .   ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^  ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) " ....^",
           /* line */ (const char *) "^.... ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "   ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^  ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) " ....^",
           /* line */ (const char *) "^.... ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "   ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^       ",
           /* line */ (const char *) " .......^",
           /* line */ (const char *) "^.x.m.m. ",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "     ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^      ",
           /* line */ (const char *) " .....  ",
           /* line */ (const char *) "^.m.x..^",
           /* line */ (const char *) " .....  ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "   .    ",
           /* line */ (const char *) "   ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^  ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) " ....^",
           /* line */ (const char *) "^.... ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^   ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) " ....^",
           /* line */ (const char *) "^.... ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "   ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^     ",
           /* line */ (const char *) "^.....^",
           /* line */ (const char *) " ..g.. ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^    ",
           /* line */ (const char *) "^.......^",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "     ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^   ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "^...... ",
           /* line */ (const char *) " ......^",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "   ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^   ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) " ....^",
           /* line */ (const char *) "^.... ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^           ",
           /* line */ (const char *) "   .......     ",
           /* line */ (const char *) "   .......     ",
           /* line */ (const char *) "^.............^",
           /* line */ (const char *) "      ..       ",
           /* line */ (const char *) "       ^       ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^   ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) " ....^",
           /* line */ (const char *) "^.... ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "   ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^   ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "^....^",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "   ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^    ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) " ......^",
           /* line */ (const char *) "^...... ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "   ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "      ^    ",
           /* line */ (const char *) "   .....   ",
           /* line */ (const char *) "^.........^",
           /* line */ (const char *) "   .....   ",
           /* line */ (const char *) "     ..    ",
           /* line */ (const char *) "      ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^         ",
           /* line */ (const char *) "   .         ",
           /* line */ (const char *) "   .........^",
           /* line */ (const char *) "^.........   ",
           /* line */ (const char *) "   .......   ",
           /* line */ (const char *) "      ..     ",
           /* line */ (const char *) "       ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^    ",
           /* line */ (const char *) "   .    ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "  ....  ",
           /* line */ (const char *) "^......^",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "   .    ",
           /* line */ (const char *) "   .    ",
           /* line */ (const char *) "   .    ",
           /* line */ (const char *) "   .    ",
           /* line */ (const char *) "   ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^    ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) " ...... ",
           /* line */ (const char *) "^......^",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "   ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^    ",
           /* line */ (const char *) "     .    ",
           /* line */ (const char *) "  .......^",
           /* line */ (const char *) "^........ ",
           /* line */ (const char *) "  ....... ",
           /* line */ (const char *) "     ..   ",
           /* line */ (const char *) "      .   ",
           /* line */ (const char *) "      ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^    ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) " ......^",
           /* line */ (const char *) "^...... ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "   ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^  ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "^.....^",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^  ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "^....^",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "   ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "      ^  ",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) " .g.g.x. ",
           /* line */ (const char *) "^.......^",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "     ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "      ^   ",
           /* line */ (const char *) "      .   ",
           /* line */ (const char *) "   .....  ",
           /* line */ (const char *) "^.......  ",
           /* line */ (const char *) "   ......^",
           /* line */ (const char *) "     ..   ",
           /* line */ (const char *) "      .   ",
           /* line */ (const char *) "      .   ",
           /* line */ (const char *) "      ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^  ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "^....^",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^     ",
           /* line */ (const char *) "    .     ",
           /* line */ (const char *) "    .     ",
           /* line */ (const char *) "    ..... ",
           /* line */ (const char *) "^....|.x.^",
           /* line */ (const char *) "    ..... ",
           /* line */ (const char *) "      ..  ",
           /* line */ (const char *) "       .  ",
           /* line */ (const char *) "       ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^      ",
           /* line */ (const char *) "    .      ",
           /* line */ (const char *) "    .      ",
           /* line */ (const char *) "    .      ",
           /* line */ (const char *) "   ..      ",
           /* line */ (const char *) "^.........^",
           /* line */ (const char *) " ......    ",
           /* line */ (const char *) "   ..      ",
           /* line */ (const char *) "   ^       ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^    ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) " ......^",
           /* line */ (const char *) "^...... ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "    ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^      ",
           /* line */ (const char *) "^......  ",
           /* line */ (const char *) "  ..|...^",
           /* line */ (const char *) "  .....  ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^     ",
           /* line */ (const char *) "^.....^",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "      ^  ",
           /* line */ (const char *) "^....... ",
           /* line */ (const char *) " ..m..g.^",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "     ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^   ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "^....^",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^   ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) "^.x.g. ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^    ",
           /* line */ (const char *) "    .    ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "^....... ",
           /* line */ (const char *) "  ......^",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "     .   ",
           /* line */ (const char *) "     .   ",
           /* line */ (const char *) "     ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "      ^  ",
           /* line */ (const char *) "^.......^",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^  ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "    ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^      ",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) " .......^",
           /* line */ (const char *) "^....... ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "      ^      ",
           /* line */ (const char *) "   .......   ",
           /* line */ (const char *) "^.........   ",
           /* line */ (const char *) "   .........^",
           /* line */ (const char *) "      ..     ",
           /* line */ (const char *) "      ^      ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^    ",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) " .g.m. ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^  ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "^....^",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^  ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) " ....^",
           /* line */ (const char *) "^.... ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^  ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "^....^",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^   ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) " ....^",
           /* line */ (const char *) "^.... ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "   ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^     ",
           /* line */ (const char *) "  .     ",
           /* line */ (const char *) "^...... ",
           /* line */ (const char *) "  .....^",
           /* line */ (const char *) "  ..... ",
           /* line */ (const char *) "    ..  ",
           /* line */ (const char *) "     ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^    ",
           /* line */ (const char *) "    .    ",
           /* line */ (const char *) "   ..    ",
           /* line */ (const char *) " ......  ",
           /* line */ (const char *) "^.......^",
           /* line */ (const char *) "   ..    ",
           /* line */ (const char *) "   .     ",
           /* line */ (const char *) "   ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "        ^   ",
           /* line */ (const char *) "        .   ",
           /* line */ (const char *) "   .......  ",
           /* line */ (const char *) "^.........  ",
           /* line */ (const char *) "   ........^",
           /* line */ (const char *) "      ..    ",
           /* line */ (const char *) "      .     ",
           /* line */ (const char *) "      ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^      ",
           /* line */ (const char *) "^.......^",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "      ^  ",
           /* line */ (const char *) "     ..  ",
           /* line */ (const char *) "^.......^",
           /* line */ (const char *) "    .... ",
           /* line */ (const char *) "     ..  ",
           /* line */ (const char *) "      .  ",
           /* line */ (const char *) "      ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^  ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) " ....^",
           /* line */ (const char *) "^.... ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "        ^   ",
           /* line */ (const char *) "^.........  ",
           /* line */ (const char *) "   ..g.m...^",
           /* line */ (const char *) "   .......  ",
           /* line */ (const char *) "      ..    ",
           /* line */ (const char *) "       .    ",
           /* line */ (const char *) "       ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "      ^     ",
           /* line */ (const char *) "      .     ",
           /* line */ (const char *) "^.......    ",
           /* line */ (const char *) " ..|..|.    ",
           /* line */ (const char *) " ..........^",
           /* line */ (const char *) "    ..      ",
           /* line */ (const char *) "    ^       ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^   ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "^.... ",
           /* line */ (const char *) " ....^",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "   ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^    ",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) "^.......^",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "     ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^     ",
           /* line */ (const char *) "     ..    ",
           /* line */ (const char *) "   ......  ",
           /* line */ (const char *) "^.........^",
           /* line */ (const char *) "     ..    ",
           /* line */ (const char *) "      ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^      ",
           /* line */ (const char *) "    .      ",
           /* line */ (const char *) "    ..     ",
           /* line */ (const char *) "  ......   ",
           /* line */ (const char *) "^.........^",
           /* line */ (const char *) "    ..     ",
           /* line */ (const char *) "    ^      ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^     ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "    ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^      ",
           /* line */ (const char *) "   .      ",
           /* line */ (const char *) "^........ ",
           /* line */ (const char *) "  .g..x.. ",
           /* line */ (const char *) "  .......^",
           /* line */ (const char *) "     ..   ",
           /* line */ (const char *) "     ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^  ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "^.... ",
           /* line */ (const char *) " ....^",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "   ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^       ",
           /* line */ (const char *) "^....... ",
           /* line */ (const char *) " .g.|.m.^",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "     ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^   ",
           /* line */ (const char *) "    .   ",
           /* line */ (const char *) "  ..... ",
           /* line */ (const char *) "^......^",
           /* line */ (const char *) "  ..... ",
           /* line */ (const char *) "    ..  ",
           /* line */ (const char *) "    .   ",
           /* line */ (const char *) "    .   ",
           /* line */ (const char *) "    .   ",
           /* line */ (const char *) "    ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^     ",
           /* line */ (const char *) "   ......^",
           /* line */ (const char *) "^.......  ",
           /* line */ (const char *) "   .....  ",
           /* line */ (const char *) "     ..   ",
           /* line */ (const char *) "     .    ",
           /* line */ (const char *) "     ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^     ",
           /* line */ (const char *) "    ..     ",
           /* line */ (const char *) "^......    ",
           /* line */ (const char *) "   .......^",
           /* line */ (const char *) "    ..     ",
           /* line */ (const char *) "     .     ",
           /* line */ (const char *) "     .     ",
           /* line */ (const char *) "     ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^     ",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^   ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "^...... ",
           /* line */ (const char *) " ......^",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "   ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^     ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "^.....^",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "    ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^   ",
           /* line */ (const char *) " .......^",
           /* line */ (const char *) " .|.x.x. ",
           /* line */ (const char *) "^....... ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "     ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^   ",
           /* line */ (const char *) "   .   ",
           /* line */ (const char *) "   .   ",
           /* line */ (const char *) "  ..   ",
           /* line */ (const char *) " ....  ",
           /* line */ (const char *) "^.....^",
           /* line */ (const char *) "  ..   ",
           /* line */ (const char *) "   .   ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^     ",
           /* line */ (const char *) "    .     ",
           /* line */ (const char *) "    .     ",
           /* line */ (const char *) "   ..     ",
           /* line */ (const char *) "^......   ",
           /* line */ (const char *) " ........^",
           /* line */ (const char *) "   ..     ",
           /* line */ (const char *) "    ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "       ^   ",
           /* line */ (const char *) "   ....... ",
           /* line */ (const char *) "   ..g.g.. ",
           /* line */ (const char *) "^.........^",
           /* line */ (const char *) "      ..   ",
           /* line */ (const char *) "       .   ",
           /* line */ (const char *) "       ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^      ",
           /* line */ (const char *) "   .      ",
           /* line */ (const char *) "   .      ",
           /* line */ (const char *) "^........^",
           /* line */ (const char *) "  ....... ",
           /* line */ (const char *) "  ....... ",
           /* line */ (const char *) "     ..   ",
           /* line */ (const char *) "     .    ",
           /* line */ (const char *) "     ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^     ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "^.x.x. ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^   ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " ..g.. ",
           /* line */ (const char *) "^.....^",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^       ",
           /* line */ (const char *) "   .       ",
           /* line */ (const char *) "   .       ",
           /* line */ (const char *) "  .......  ",
           /* line */ (const char *) "^...|.g...^",
           /* line */ (const char *) "  .......  ",
           /* line */ (const char *) "     ..    ",
           /* line */ (const char *) "      .    ",
           /* line */ (const char *) "      ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^      ",
           /* line */ (const char *) "    ..     ",
           /* line */ (const char *) "^.........^",
           /* line */ (const char *) "  ......   ",
           /* line */ (const char *) "    ..     ",
           /* line */ (const char *) "     ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^  ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "^....^",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^      ",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) "^....... ",
           /* line */ (const char *) " .......^",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "     ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^    ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "^......^",
           /* line */ (const char *) " ...... ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "   ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^    ",
           /* line */ (const char *) " .......^",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) "^....... ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^    ",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) "^.m.|.m.^",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "     ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^    ",
           /* line */ (const char *) "    .    ",
           /* line */ (const char *) "    .    ",
           /* line */ (const char *) "    .    ",
           /* line */ (const char *) "   ..    ",
           /* line */ (const char *) " ......  ",
           /* line */ (const char *) "^.......^",
           /* line */ (const char *) "   ..    ",
           /* line */ (const char *) "   .     ",
           /* line */ (const char *) "   ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^   ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "^.......^",
           /* line */ (const char *) "  ...... ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "     .   ",
           /* line */ (const char *) "     ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^     ",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^   ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) " ...... ",
           /* line */ (const char *) "^......^",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "   ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^    ",
           /* line */ (const char *) "    .    ",
           /* line */ (const char *) " .....   ",
           /* line */ (const char *) " .|.x.   ",
           /* line */ (const char *) "^.......^",
           /* line */ (const char *) "   ..    ",
           /* line */ (const char *) "    .    ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^   ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) " ...... ",
           /* line */ (const char *) "^......^",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "   ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^      ",
           /* line */ (const char *) "    .      ",
           /* line */ (const char *) "    .      ",
           /* line */ (const char *) "    ..     ",
           /* line */ (const char *) "^.......   ",
           /* line */ (const char *) "  ........^",
           /* line */ (const char *) "    ..     ",
           /* line */ (const char *) "    .      ",
           /* line */ (const char *) "    ^      ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^     ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "^.m.|. ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^     ",
           /* line */ (const char *) "  ....... ",
           /* line */ (const char *) "  .......^",
           /* line */ (const char *) "^........ ",
           /* line */ (const char *) "     ..   ",
           /* line */ (const char *) "     .    ",
           /* line */ (const char *) "     ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^     ",
           /* line */ (const char *) "   ..    ",
           /* line */ (const char *) " .......^",
           /* line */ (const char *) "^......  ",
           /* line */ (const char *) "   ..    ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^       ",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) " .|.m.g. ",
           /* line */ (const char *) "^.......^",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^   ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "^......^",
           /* line */ (const char *) " ...... ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "    ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^      ",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) " .......^",
           /* line */ (const char *) "^....... ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^    ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "^......^",
           /* line */ (const char *) " ...... ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "    ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^   ",
           /* line */ (const char *) "     .   ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "  ......^",
           /* line */ (const char *) "^....... ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "    .    ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^   ",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^      ",
           /* line */ (const char *) "    ..     ",
           /* line */ (const char *) "^.......   ",
           /* line */ (const char *) "  ........^",
           /* line */ (const char *) "    ..     ",
           /* line */ (const char *) "    .      ",
           /* line */ (const char *) "    .      ",
           /* line */ (const char *) "    ^      ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^      ",
           /* line */ (const char *) "  .....  ",
           /* line */ (const char *) "^......  ",
           /* line */ (const char *) "  ......^",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "      ^   ",
           /* line */ (const char *) "      .   ",
           /* line */ (const char *) "  ....... ",
           /* line */ (const char *) "  .x.m.|. ",
           /* line */ (const char *) "^........^",
           /* line */ (const char *) "     ..   ",
           /* line */ (const char *) "      .   ",
           /* line */ (const char *) "      ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^     ",
           /* line */ (const char *) "    ..    ",
           /* line */ (const char *) "  ......  ",
           /* line */ (const char *) "^........^",
           /* line */ (const char *) "    ..    ",
           /* line */ (const char *) "    .     ",
           /* line */ (const char *) "    ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^    ",
           /* line */ (const char *) "    .    ",
           /* line */ (const char *) "^.......^",
           /* line */ (const char *) "  .m.|.  ",
           /* line */ (const char *) "  .....  ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "    .    ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^   ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "^......^",
           /* line */ (const char *) " ...... ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "   ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^  ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "^....^",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^   ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "^......^",
           /* line */ (const char *) " ...... ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "   ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^     ",
           /* line */ (const char *) "    .     ",
           /* line */ (const char *) "    ..    ",
           /* line */ (const char *) "^........^",
           /* line */ (const char *) "  ......  ",
           /* line */ (const char *) "    ..    ",
           /* line */ (const char *) "     .    ",
           /* line */ (const char *) "     .    ",
           /* line */ (const char *) "     ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^     ",
           /* line */ (const char *) "   .     ",
           /* line */ (const char *) "   .....^",
           /* line */ (const char *) "^....... ",
           /* line */ (const char *) "   ..... ",
           /* line */ (const char *) "     ..  ",
           /* line */ (const char *) "      .  ",
           /* line */ (const char *) "      .  ",
           /* line */ (const char *) "      .  ",
           /* line */ (const char *) "      ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^   ",
           /* line */ (const char *) "^.....  ",
           /* line */ (const char *) " .....  ",
           /* line */ (const char *) " ......^",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "    .   ",
           /* line */ (const char *) "    .   ",
           /* line */ (const char *) "    ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^     ",
           /* line */ (const char *) "   .     ",
           /* line */ (const char *) "  .....  ",
           /* line */ (const char *) "  .....  ",
           /* line */ (const char *) "^.......^",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^    ",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) " ..x.. ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "    ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "      ^  ",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) " .x.M.x.^",
           /* line */ (const char *) "^....... ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "     ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^       ",
           /* line */ (const char *) "  ........^",
           /* line */ (const char *) "^........  ",
           /* line */ (const char *) "  .......  ",
           /* line */ (const char *) "     ..    ",
           /* line */ (const char *) "      .    ",
           /* line */ (const char *) "      ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^    ",
           /* line */ (const char *) "  .    ",
           /* line */ (const char *) "  ..   ",
           /* line */ (const char *) "^....  ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) "  ..   ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^  ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "^....^",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^   ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) " ......^",
           /* line */ (const char *) "^...... ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "    ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "      ^      ",
           /* line */ (const char *) "      .      ",
           /* line */ (const char *) "    .......  ",
           /* line */ (const char *) "^....g.x.|..^",
           /* line */ (const char *) "    .......  ",
           /* line */ (const char *) "       ..    ",
           /* line */ (const char *) "       .     ",
           /* line */ (const char *) "       ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^   ",
           /* line */ (const char *) "    .   ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "  ....  ",
           /* line */ (const char *) "^......^",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "    .   ",
           /* line */ (const char *) "    ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^   ",
           /* line */ (const char *) "    .   ",
           /* line */ (const char *) "    .   ",
           /* line */ (const char *) "    .   ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "^......^",
           /* line */ (const char *) "  ....  ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "    .   ",
           /* line */ (const char *) "    ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^    ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " ..M.. ",
           /* line */ (const char *) "^.....^",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "    ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^   ",
           /* line */ (const char *) "^.....^",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "    ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^       ",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) " .......^",
           /* line */ (const char *) "^....... ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^  ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "^.... ",
           /* line */ (const char *) " ....^",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "   ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^     ",
           /* line */ (const char *) "  .......^",
           /* line */ (const char *) "^...g..M. ",
           /* line */ (const char *) "  ....... ",
           /* line */ (const char *) "     ..   ",
           /* line */ (const char *) "      ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^     ",
           /* line */ (const char *) "     .     ",
           /* line */ (const char *) "  ........^",
           /* line */ (const char *) "^..g.|.g.  ",
           /* line */ (const char *) "  .......  ",
           /* line */ (const char *) "     ..    ",
           /* line */ (const char *) "     ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^   ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "^......^",
           /* line */ (const char *) " ...... ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "   ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^     ",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) " .......^",
           /* line */ (const char *) "^....... ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^       ",
           /* line */ (const char *) "    ..      ",
           /* line */ (const char *) "^..........^",
           /* line */ (const char *) "  ......    ",
           /* line */ (const char *) "    ..      ",
           /* line */ (const char *) "    .       ",
           /* line */ (const char *) "    ^       ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^      ",
           /* line */ (const char *) "    .      ",
           /* line */ (const char *) "    ..     ",
           /* line */ (const char *) "  ......   ",
           /* line */ (const char *) "^.........^",
           /* line */ (const char *) "    ..     ",
           /* line */ (const char *) "     .     ",
           /* line */ (const char *) "     ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "        ^  ",
           /* line */ (const char *) "        .  ",
           /* line */ (const char *) "   ....... ",
           /* line */ (const char *) "^....m..g.^",
           /* line */ (const char *) "   ....... ",
           /* line */ (const char *) "      ..   ",
           /* line */ (const char *) "       .   ",
           /* line */ (const char *) "       ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^      ",
           /* line */ (const char *) "  ......^",
           /* line */ (const char *) "^..|.|.  ",
           /* line */ (const char *) "  .....  ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "     .   ",
           /* line */ (const char *) "     ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^   ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) " ...... ",
           /* line */ (const char *) "^......^",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "    ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^   ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) " ...... ",
           /* line */ (const char *) "^......^",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "   ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "      ^       ",
           /* line */ (const char *) "^..........   ",
           /* line */ (const char *) "    .........^",
           /* line */ (const char *) "    .......   ",
           /* line */ (const char *) "       ..     ",
           /* line */ (const char *) "        .     ",
           /* line */ (const char *) "        ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^   ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "^....^",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "   ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^    ",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) " .|.g.|.^",
           /* line */ (const char *) "^....... ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "     ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^  ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "^....^",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "   ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "        ^   ",
           /* line */ (const char *) "        .   ",
           /* line */ (const char *) "^.........  ",
           /* line */ (const char *) "   .......  ",
           /* line */ (const char *) "   ........^",
           /* line */ (const char *) "      ..    ",
           /* line */ (const char *) "      .     ",
           /* line */ (const char *) "      ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^      ",
           /* line */ (const char *) "  .....  ",
           /* line */ (const char *) "  ..m..  ",
           /* line */ (const char *) "^.......^",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "     ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^   ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "^....^",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^       ",
           /* line */ (const char *) " .       ",
           /* line */ (const char *) " .       ",
           /* line */ (const char *) "^.......^",
           /* line */ (const char *) " ..|.g.. ",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^    ",
           /* line */ (const char *) "    .    ",
           /* line */ (const char *) "^.......^",
           /* line */ (const char *) "  .....  ",
           /* line */ (const char *) "  .....  ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "     .   ",
           /* line */ (const char *) "     .   ",
           /* line */ (const char *) "     .   ",
           /* line */ (const char *) "     .   ",
           /* line */ (const char *) "     ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^  ",
           /* line */ (const char *) "    .  ",
           /* line */ (const char *) "    .  ",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) "  ....^",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "    .  ",
           /* line */ (const char *) "    ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "      ^  ",
           /* line */ (const char *) " .......^",
           /* line */ (const char *) " ..g..m. ",
           /* line */ (const char *) "^....... ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "     ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^    ",
           /* line */ (const char *) "     .    ",
           /* line */ (const char *) "     .    ",
           /* line */ (const char *) "    ..    ",
           /* line */ (const char *) "   ......^",
           /* line */ (const char *) "^......   ",
           /* line */ (const char *) "    ..    ",
           /* line */ (const char *) "     .    ",
           /* line */ (const char *) "     .    ",
           /* line */ (const char *) "     ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^   ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "^....^",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "   ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^    ",
           /* line */ (const char *) "  .....   ",
           /* line */ (const char *) "^......   ",
           /* line */ (const char *) "  .......^",
           /* line */ (const char *) "    ..    ",
           /* line */ (const char *) "    ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "      ^  ",
           /* line */ (const char *) "^....... ",
           /* line */ (const char *) " .......^",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^     ",
           /* line */ (const char *) "   .     ",
           /* line */ (const char *) "   .     ",
           /* line */ (const char *) "^......  ",
           /* line */ (const char *) "  .|.x.  ",
           /* line */ (const char *) "  ......^",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "    .    ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^    ",
           /* line */ (const char *) "    .    ",
           /* line */ (const char *) "    .    ",
           /* line */ (const char *) "   ..    ",
           /* line */ (const char *) "^.......^",
           /* line */ (const char *) " ......  ",
           /* line */ (const char *) "   ..    ",
           /* line */ (const char *) "   ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^   ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) " ...... ",
           /* line */ (const char *) "^......^",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "   ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^    ",
           /* line */ (const char *) "  ..   ",
           /* line */ (const char *) " ....  ",
           /* line */ (const char *) "^.....^",
           /* line */ (const char *) "  ..   ",
           /* line */ (const char *) "   .   ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^   ",
           /* line */ (const char *) "    .   ",
           /* line */ (const char *) "  .....^",
           /* line */ (const char *) "  ..|.. ",
           /* line */ (const char *) "^...... ",
           /* line */ (const char *) "    ..  ",
           /* line */ (const char *) "     .  ",
           /* line */ (const char *) "     ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^    ",
           /* line */ (const char *) "   .    ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "  ....  ",
           /* line */ (const char *) "^......^",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "   ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^      ",
           /* line */ (const char *) " .      ",
           /* line */ (const char *) " ......^",
           /* line */ (const char *) " .x.x.  ",
           /* line */ (const char *) "^.....  ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "    .   ",
           /* line */ (const char *) "    ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^     ",
           /* line */ (const char *) "   .     ",
           /* line */ (const char *) "   ..    ",
           /* line */ (const char *) "  ....   ",
           /* line */ (const char *) "^.......^",
           /* line */ (const char *) "   ..    ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^  ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "^.... ",
           /* line */ (const char *) " ....^",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "   ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^   ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "^......^",
           /* line */ (const char *) " ...... ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "    ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^  ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "^....^",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "   ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^     ",
           /* line */ (const char *) "   ..    ",
           /* line */ (const char *) "^......  ",
           /* line */ (const char *) " .......^",
           /* line */ (const char *) "   ..    ",
           /* line */ (const char *) "   ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "      ^    ",
           /* line */ (const char *) "      .    ",
           /* line */ (const char *) "^.......   ",
           /* line */ (const char *) " ..m.|..   ",
           /* line */ (const char *) " .........^",
           /* line */ (const char *) "    ..     ",
           /* line */ (const char *) "     ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^    ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) " ...... ",
           /* line */ (const char *) "^......^",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "    ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^    ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "^......^",
           /* line */ (const char *) " ...... ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "   ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^       ",
           /* line */ (const char *) "   .....   ",
           /* line */ (const char *) "^.......   ",
           /* line */ (const char *) "   .......^",
           /* line */ (const char *) "     ..    ",
           /* line */ (const char *) "      .    ",
           /* line */ (const char *) "      ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "      ^    ",
           /* line */ (const char *) "      .    ",
           /* line */ (const char *) "      .    ",
           /* line */ (const char *) "      ..   ",
           /* line */ (const char *) "^......... ",
           /* line */ (const char *) "    ......^",
           /* line */ (const char *) "      ..   ",
           /* line */ (const char *) "       .   ",
           /* line */ (const char *) "       ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^   ",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) "^.|.g.|. ",
           /* line */ (const char *) " .......^",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "      ^  ",
           /* line */ (const char *) "      .  ",
           /* line */ (const char *) "      .  ",
           /* line */ (const char *) "   .....^",
           /* line */ (const char *) "^....... ",
           /* line */ (const char *) "   ..... ",
           /* line */ (const char *) "     ..  ",
           /* line */ (const char *) "      ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^   ",
           /* line */ (const char *) "  .   ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) " ....^",
           /* line */ (const char *) "^.... ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "   ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^    ",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) " .|.m.|.^",
           /* line */ (const char *) "^....... ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "     ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^       ",
           /* line */ (const char *) "   .....    ",
           /* line */ (const char *) "^...|.x....^",
           /* line */ (const char *) "   .....    ",
           /* line */ (const char *) "     ..     ",
           /* line */ (const char *) "      .     ",
           /* line */ (const char *) "      .     ",
           /* line */ (const char *) "      ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^    ",
           /* line */ (const char *) "    .    ",
           /* line */ (const char *) "   .....^",
           /* line */ (const char *) "^....... ",
           /* line */ (const char *) "   ..... ",
           /* line */ (const char *) "     ..  ",
           /* line */ (const char *) "     .   ",
           /* line */ (const char *) "     ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "      ^  ",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) "^.x.m.x. ",
           /* line */ (const char *) " .......^",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^   ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "^....^",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "   ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^      ",
           /* line */ (const char *) " .......^",
           /* line */ (const char *) " ..g.|.. ",
           /* line */ (const char *) "^....... ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^    ",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) " .|.m.^",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^      ",
           /* line */ (const char *) "   .      ",
           /* line */ (const char *) "   .      ",
           /* line */ (const char *) " .......  ",
           /* line */ (const char *) "^.g.m.x..^",
           /* line */ (const char *) " .......  ",
           /* line */ (const char *) "    ..    ",
           /* line */ (const char *) "    ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^      ",
           /* line */ (const char *) "     .      ",
           /* line */ (const char *) "     ..     ",
           /* line */ (const char *) "   ......   ",
           /* line */ (const char *) "^..........^",
           /* line */ (const char *) "     ..     ",
           /* line */ (const char *) "     .      ",
           /* line */ (const char *) "     ^      ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "      ^   ",
           /* line */ (const char *) "  ....... ",
           /* line */ (const char *) "^...M..g.^",
           /* line */ (const char *) "  ....... ",
           /* line */ (const char *) "     ..   ",
           /* line */ (const char *) "      ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^  ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "^....^",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^     ",
           /* line */ (const char *) "^....... ",
           /* line */ (const char *) " .m.m.G.^",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "     ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^    ",
           /* line */ (const char *) "   ..    ",
           /* line */ (const char *) "  ....   ",
           /* line */ (const char *) "^.......^",
           /* line */ (const char *) "   ..    ",
           /* line */ (const char *) "   .     ",
           /* line */ (const char *) "   ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^    ",
           /* line */ (const char *) "   .    ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "  .....^",
           /* line */ (const char *) "^.....  ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "    .   ",
           /* line */ (const char *) "    ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^  ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) " ....^",
           /* line */ (const char *) "^.... ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^     ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^       ",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) "^.......^",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^    ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "^......^",
           /* line */ (const char *) " ...... ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "    ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^     ",
           /* line */ (const char *) "^....... ",
           /* line */ (const char *) " .g.g.g. ",
           /* line */ (const char *) " .......^",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^   ",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) " ..g.. ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "    ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^   ",
           /* line */ (const char *) "   .   ",
           /* line */ (const char *) "   .   ",
           /* line */ (const char *) "  ..   ",
           /* line */ (const char *) " ....  ",
           /* line */ (const char *) "^.....^",
           /* line */ (const char *) "  ..   ",
           /* line */ (const char *) "   .   ",
           /* line */ (const char *) "   .   ",
           /* line */ (const char *) "   .   ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "      ^   ",
           /* line */ (const char *) "     ..   ",
           /* line */ (const char *) "^........^",
           /* line */ (const char *) "    ....  ",
           /* line */ (const char *) "     ..   ",
           /* line */ (const char *) "      .   ",
           /* line */ (const char *) "      .   ",
           /* line */ (const char *) "      ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^   ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "^.... ",
           /* line */ (const char *) " ....^",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^    ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "^......^",
           /* line */ (const char *) " ...... ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "   ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^       ",
           /* line */ (const char *) "  .       ",
           /* line */ (const char *) "  .       ",
           /* line */ (const char *) "  .......^",
           /* line */ (const char *) "  ....... ",
           /* line */ (const char *) "^........ ",
           /* line */ (const char *) "     ..   ",
           /* line */ (const char *) "     .    ",
           /* line */ (const char *) "     ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^        ",
           /* line */ (const char *) "  .        ",
           /* line */ (const char *) "  .......  ",
           /* line */ (const char *) "  ........^",
           /* line */ (const char *) "^........  ",
           /* line */ (const char *) "     ..    ",
           /* line */ (const char *) "      .    ",
           /* line */ (const char *) "      .    ",
           /* line */ (const char *) "      ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^  ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) " ..m.. ",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "    ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^       ",
           /* line */ (const char *) "  .       ",
           /* line */ (const char *) "  .....   ",
           /* line */ (const char *) "  .......^",
           /* line */ (const char *) "^......   ",
           /* line */ (const char *) "    ..    ",
           /* line */ (const char *) "    .     ",
           /* line */ (const char *) "    ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^   ",
           /* line */ (const char *) "^.....^",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^    ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) " ...... ",
           /* line */ (const char *) "^......^",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "   ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^         ",
           /* line */ (const char *) "^........    ",
           /* line */ (const char *) "  ..........^",
           /* line */ (const char *) "  .......    ",
           /* line */ (const char *) "     ..      ",
           /* line */ (const char *) "      .      ",
           /* line */ (const char *) "      ^      ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^   ",
           /* line */ (const char *) "^....... ",
           /* line */ (const char *) " .......^",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "     ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "       ^   ",
           /* line */ (const char *) "       .   ",
           /* line */ (const char *) "  .......  ",
           /* line */ (const char *) "  ........^",
           /* line */ (const char *) "^........  ",
           /* line */ (const char *) "     ..    ",
           /* line */ (const char *) "     ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^    ",
           /* line */ (const char *) "  .    ",
           /* line */ (const char *) "  .    ",
           /* line */ (const char *) "  ..   ",
           /* line */ (const char *) " ....  ",
           /* line */ (const char *) "^.....^",
           /* line */ (const char *) "  ..   ",
           /* line */ (const char *) "  .    ",
           /* line */ (const char *) "  .    ",
           /* line */ (const char *) "  ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^      ",
           /* line */ (const char *) "^....... ",
           /* line */ (const char *) " ..g.g.. ",
           /* line */ (const char *) " .......^",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^    ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) " ......^",
           /* line */ (const char *) "^...... ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "    ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^     ",
           /* line */ (const char *) "  ......^",
           /* line */ (const char *) "  .g.x.  ",
           /* line */ (const char *) "^......  ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "     .   ",
           /* line */ (const char *) "     ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^   ",
           /* line */ (const char *) "   .   ",
           /* line */ (const char *) "   .   ",
           /* line */ (const char *) "   .   ",
           /* line */ (const char *) "  ..   ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) "^....  ",
           /* line */ (const char *) "  ..   ",
           /* line */ (const char *) "   .   ",
           /* line */ (const char *) "   .   ",
           /* line */ (const char *) "   .   ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^   ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "^......  ",
           /* line */ (const char *) "   .....^",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "    .    ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^  ",
           /* line */ (const char *) "    ..  ",
           /* line */ (const char *) "   .... ",
           /* line */ (const char *) "^......^",
           /* line */ (const char *) "    ..  ",
           /* line */ (const char *) "     ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^     ",
           /* line */ (const char *) "^.......  ",
           /* line */ (const char *) "   ..|..  ",
           /* line */ (const char *) "   ......^",
           /* line */ (const char *) "     ..   ",
           /* line */ (const char *) "     .    ",
           /* line */ (const char *) "     .    ",
           /* line */ (const char *) "     .    ",
           /* line */ (const char *) "     ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^   ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "^......^",
           /* line */ (const char *) " ...... ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "    ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^        ",
           /* line */ (const char *) "   ..       ",
           /* line */ (const char *) " ......     ",
           /* line */ (const char *) "^..........^",
           /* line */ (const char *) "   ..       ",
           /* line */ (const char *) "   ^        ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^       ",
           /* line */ (const char *) " ........^",
           /* line */ (const char *) "^.......  ",
           /* line */ (const char *) " .......  ",
           /* line */ (const char *) "    ..    ",
           /* line */ (const char *) "    ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^  ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) " ....^",
           /* line */ (const char *) "^.... ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "   ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^     ",
           /* line */ (const char *) "^.......^",
           /* line */ (const char *) " ..m..|. ",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "     ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^    ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "^...... ",
           /* line */ (const char *) " ......^",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "   ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^      ",
           /* line */ (const char *) "     ..     ",
           /* line */ (const char *) "^..........^",
           /* line */ (const char *) "   ......   ",
           /* line */ (const char *) "     ..     ",
           /* line */ (const char *) "      .     ",
           /* line */ (const char *) "      ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "      ^    ",
           /* line */ (const char *) "      .    ",
           /* line */ (const char *) "      .    ",
           /* line */ (const char *) "      ..   ",
           /* line */ (const char *) "     ....  ",
           /* line */ (const char *) "^.........^",
           /* line */ (const char *) "      ..   ",
           /* line */ (const char *) "       .   ",
           /* line */ (const char *) "       .   ",
           /* line */ (const char *) "       ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^    ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "^...... ",
           /* line */ (const char *) " ......^",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "    ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "      ^      ",
           /* line */ (const char *) "      ..     ",
           /* line */ (const char *) "    ........^",
           /* line */ (const char *) "^.........   ",
           /* line */ (const char *) "      ..     ",
           /* line */ (const char *) "      .      ",
           /* line */ (const char *) "      ^      ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^  ",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^       ",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) "^.x.m.|. ",
           /* line */ (const char *) " .......^",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "     ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^   ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) " ...... ",
           /* line */ (const char *) "^......^",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "   ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^     ",
           /* line */ (const char *) "    .     ",
           /* line */ (const char *) "    .     ",
           /* line */ (const char *) "   ..     ",
           /* line */ (const char *) " ........^",
           /* line */ (const char *) "^......   ",
           /* line */ (const char *) "   ..     ",
           /* line */ (const char *) "   .      ",
           /* line */ (const char *) "   .      ",
           /* line */ (const char *) "   ^      ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^    ",
           /* line */ (const char *) "  ..... ",
           /* line */ (const char *) "  .m.|. ",
           /* line */ (const char *) "^......^",
           /* line */ (const char *) "    ..  ",
           /* line */ (const char *) "    ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^       ",
           /* line */ (const char *) "     ..      ",
           /* line */ (const char *) "^...........^",
           /* line */ (const char *) "   ......    ",
           /* line */ (const char *) "     ..      ",
           /* line */ (const char *) "      ^      ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^  ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) " ..m.. ",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^    ",
           /* line */ (const char *) "^....... ",
           /* line */ (const char *) " .x.|.m.^",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^  ",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "^.....^",
           /* line */ (const char *) "  .... ",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "   .   ",
           /* line */ (const char *) "   .   ",
           /* line */ (const char *) "   .   ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^  ",
           /* line */ (const char *) "    .  ",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "  ....^",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "    .  ",
           /* line */ (const char *) "    ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^      ",
           /* line */ (const char *) "     ..     ",
           /* line */ (const char *) "^.......    ",
           /* line */ (const char *) "    .......^",
           /* line */ (const char *) "     ..     ",
           /* line */ (const char *) "     .      ",
           /* line */ (const char *) "     ^      ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^       ",
           /* line */ (const char *) " .......^",
           /* line */ (const char *) "^.m.x.m. ",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^     ",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) "^.|.g.m.^",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "     ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^    ",
           /* line */ (const char *) "    .    ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "   ....  ",
           /* line */ (const char *) "^.......^",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "     .   ",
           /* line */ (const char *) "     ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^    ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) " ...... ",
           /* line */ (const char *) "^......^",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "    ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "      ^    ",
           /* line */ (const char *) "      .    ",
           /* line */ (const char *) " .......   ",
           /* line */ (const char *) "^.x..x....^",
           /* line */ (const char *) " .......   ",
           /* line */ (const char *) "    ..     ",
           /* line */ (const char *) "    ^      ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^    ",
           /* line */ (const char *) "    .    ",
           /* line */ (const char *) "    .    ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "^....... ",
           /* line */ (const char *) "  ......^",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "     ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^     ",
           /* line */ (const char *) "    .     ",
           /* line */ (const char *) "    .     ",
           /* line */ (const char *) "  ....... ",
           /* line */ (const char *) "  .|..x..^",
           /* line */ (const char *) "^........ ",
           /* line */ (const char *) "     ..   ",
           /* line */ (const char *) "      .   ",
           /* line */ (const char *) "      ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^    ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) " ...... ",
           /* line */ (const char *) "^......^",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "    ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^   ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "    ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^    ",
           /* line */ (const char *) "    ..    ",
           /* line */ (const char *) "^.......  ",
           /* line */ (const char *) "  .......^",
           /* line */ (const char *) "    ..    ",
           /* line */ (const char *) "    ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^   ",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) " .......^",
           /* line */ (const char *) "^....... ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^  ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "    ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "      ^      ",
           /* line */ (const char *) "     ..      ",
           /* line */ (const char *) "   .........^",
           /* line */ (const char *) "^........    ",
           /* line */ (const char *) "     ..      ",
           /* line */ (const char *) "      ^      ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^     ",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) " .g.g. ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "    ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^       ",
           /* line */ (const char *) "  ..........^",
           /* line */ (const char *) "^........    ",
           /* line */ (const char *) "  .......    ",
           /* line */ (const char *) "     ..      ",
           /* line */ (const char *) "     ^       ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^    ",
           /* line */ (const char *) "    .    ",
           /* line */ (const char *) "   ..    ",
           /* line */ (const char *) "  ....   ",
           /* line */ (const char *) "^.......^",
           /* line */ (const char *) "   ..    ",
           /* line */ (const char *) "    .    ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^   ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) " ....^",
           /* line */ (const char *) "^.... ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^    ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "^.m.x.^",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "    ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^   ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^     ",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) " .m.g.G. ",
           /* line */ (const char *) "^.......^",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^   ",
           /* line */ (const char *) "    .   ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) " ...... ",
           /* line */ (const char *) "^......^",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "    ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "      ^     ",
           /* line */ (const char *) "   ........^",
           /* line */ (const char *) "   ..m.m..  ",
           /* line */ (const char *) "^.........  ",
           /* line */ (const char *) "      ..    ",
           /* line */ (const char *) "      ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^    ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) " ......^",
           /* line */ (const char *) "^...... ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "    ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^      ",
           /* line */ (const char *) "   ..     ",
           /* line */ (const char *) "^......   ",
           /* line */ (const char *) " ........^",
           /* line */ (const char *) "   ..     ",
           /* line */ (const char *) "   ^      ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^   ",
           /* line */ (const char *) "     .   ",
           /* line */ (const char *) "     .   ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "^......  ",
           /* line */ (const char *) "   .....^",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "     ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^    ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) " .g.m. ",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^      ",
           /* line */ (const char *) "    .      ",
           /* line */ (const char *) "    .      ",
           /* line */ (const char *) "  .......  ",
           /* line */ (const char *) "^..|.m.x.  ",
           /* line */ (const char *) "  ........^",
           /* line */ (const char *) "     ..    ",
           /* line */ (const char *) "      .    ",
           /* line */ (const char *) "      .    ",
           /* line */ (const char *) "      ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^      ",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) "^.m..|..^",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^   ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) " ...... ",
           /* line */ (const char *) "^......^",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "    ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "          ^  ",
           /* line */ (const char *) "          .  ",
           /* line */ (const char *) "     .......^",
           /* line */ (const char *) "^........... ",
           /* line */ (const char *) "     ....... ",
           /* line */ (const char *) "        ..   ",
           /* line */ (const char *) "        .    ",
           /* line */ (const char *) "        ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^    ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "    ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^   ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " .m.g.^",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^    ",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) " ..g..^",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "    ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^  ",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) " ..|..^",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^       ",
           /* line */ (const char *) " .       ",
           /* line */ (const char *) " .       ",
           /* line */ (const char *) " .....   ",
           /* line */ (const char *) " .......^",
           /* line */ (const char *) "^.....   ",
           /* line */ (const char *) "   ..    ",
           /* line */ (const char *) "   .     ",
           /* line */ (const char *) "   .     ",
           /* line */ (const char *) "   .     ",
           /* line */ (const char *) "   ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^    ",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) " ..g..x. ",
           /* line */ (const char *) "^.......^",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "     ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^   ",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) " ..g..^",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "    ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^   ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "^....^",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^     ",
           /* line */ (const char *) "^.....^",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^      ",
           /* line */ (const char *) "  ......^",
           /* line */ (const char *) "^......  ",
           /* line */ (const char *) "  .....  ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "     ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^   ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "^.... ",
           /* line */ (const char *) " ....^",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^    ",
           /* line */ (const char *) "     .    ",
           /* line */ (const char *) "   .....  ",
           /* line */ (const char *) "   .....  ",
           /* line */ (const char *) "^........^",
           /* line */ (const char *) "     ..   ",
           /* line */ (const char *) "      ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^     ",
           /* line */ (const char *) "    .     ",
           /* line */ (const char *) "    ..    ",
           /* line */ (const char *) "  ......  ",
           /* line */ (const char *) "^........^",
           /* line */ (const char *) "    ..    ",
           /* line */ (const char *) "     ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^     ",
           /* line */ (const char *) " ......^",
           /* line */ (const char *) " .....  ",
           /* line */ (const char *) "^.....  ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "   .    ",
           /* line */ (const char *) "   ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^   ",
           /* line */ (const char *) "   .   ",
           /* line */ (const char *) "   .   ",
           /* line */ (const char *) "  ..   ",
           /* line */ (const char *) " ....  ",
           /* line */ (const char *) "^.....^",
           /* line */ (const char *) "  ..   ",
           /* line */ (const char *) "   .   ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^     ",
           /* line */ (const char *) "^.....^",
           /* line */ (const char *) " .g.m. ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "    ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^     ",
           /* line */ (const char *) "   ..    ",
           /* line */ (const char *) " .......^",
           /* line */ (const char *) "^......  ",
           /* line */ (const char *) "   ..    ",
           /* line */ (const char *) "    .    ",
           /* line */ (const char *) "    .    ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^    ",
           /* line */ (const char *) "  ..... ",
           /* line */ (const char *) "^......^",
           /* line */ (const char *) "  ..... ",
           /* line */ (const char *) "    ..  ",
           /* line */ (const char *) "    ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^    ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "^......^",
           /* line */ (const char *) "  ....  ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "    .   ",
           /* line */ (const char *) "    ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^    ",
           /* line */ (const char *) "^.......^",
           /* line */ (const char *) " .x..m.. ",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^  ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "^....^",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^  ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) " ....^",
           /* line */ (const char *) "^.... ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^     ",
           /* line */ (const char *) "    .     ",
           /* line */ (const char *) "   ..     ",
           /* line */ (const char *) "^......   ",
           /* line */ (const char *) " ........^",
           /* line */ (const char *) "   ..     ",
           /* line */ (const char *) "    ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^   ",
           /* line */ (const char *) "   .   ",
           /* line */ (const char *) "  ..   ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) "^....  ",
           /* line */ (const char *) "  ..   ",
           /* line */ (const char *) "  .    ",
           /* line */ (const char *) "  ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "      ^  ",
           /* line */ (const char *) "^....... ",
           /* line */ (const char *) " ..g.m..^",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "     ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^   ",
           /* line */ (const char *) "     .   ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "  ...... ",
           /* line */ (const char *) "^.......^",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "    .    ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^   ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "  ....  ",
           /* line */ (const char *) "^......^",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "    .   ",
           /* line */ (const char *) "    .   ",
           /* line */ (const char *) "    .   ",
           /* line */ (const char *) "    ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^  ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "^.... ",
           /* line */ (const char *) " ....^",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "   ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^   ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "^....^",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^     ",
           /* line */ (const char *) "  ........^",
           /* line */ (const char *) "  .m.x.|.  ",
           /* line */ (const char *) "^........  ",
           /* line */ (const char *) "     ..    ",
           /* line */ (const char *) "     .     ",
           /* line */ (const char *) "     .     ",
           /* line */ (const char *) "     ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^   ",
           /* line */ (const char *) "^....... ",
           /* line */ (const char *) " .x.|.m. ",
           /* line */ (const char *) " .......^",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "     ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^    ",
           /* line */ (const char *) " .......^",
           /* line */ (const char *) " ..|.m.. ",
           /* line */ (const char *) "^....... ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^   ",
           /* line */ (const char *) "     .   ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "   .....^",
           /* line */ (const char *) "^......  ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "     .   ",
           /* line */ (const char *) "     ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^    ",
           /* line */ (const char *) "   ..    ",
           /* line */ (const char *) "^.......^",
           /* line */ (const char *) " ......  ",
           /* line */ (const char *) "   ..    ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^     ",
           /* line */ (const char *) "^.....^",
           /* line */ (const char *) " .x.m. ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "    ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^      ",
           /* line */ (const char *) "^.......^",
           /* line */ (const char *) " .m..g.. ",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^     ",
           /* line */ (const char *) "     .     ",
           /* line */ (const char *) "  ........^",
           /* line */ (const char *) "^........  ",
           /* line */ (const char *) "  .......  ",
           /* line */ (const char *) "     ..    ",
           /* line */ (const char *) "     .     ",
           /* line */ (const char *) "     ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^   ",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) " .m..|.. ",
           /* line */ (const char *) "^.......^",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^    ",
           /* line */ (const char *) "    .    ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "  ...... ",
           /* line */ (const char *) "^.......^",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "    .    ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^        ",
           /* line */ (const char *) " .        ",
           /* line */ (const char *) " .        ",
           /* line */ (const char *) " .......  ",
           /* line */ (const char *) " .......  ",
           /* line */ (const char *) "^........^",
           /* line */ (const char *) "    ..    ",
           /* line */ (const char *) "     .    ",
           /* line */ (const char *) "     .    ",
           /* line */ (const char *) "     ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^   ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " ..g..^",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^      ",
           /* line */ (const char *) "    .      ",
           /* line */ (const char *) "    ..     ",
           /* line */ (const char *) "  ......   ",
           /* line */ (const char *) "^.........^",
           /* line */ (const char *) "    ..     ",
           /* line */ (const char *) "     ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^  ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) " ....^",
           /* line */ (const char *) "^.... ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^    ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "^....... ",
           /* line */ (const char *) "  ......^",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "     ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^      ",
           /* line */ (const char *) "   .      ",
           /* line */ (const char *) "   .      ",
           /* line */ (const char *) "   .      ",
           /* line */ (const char *) "   ..     ",
           /* line */ (const char *) "  .......^",
           /* line */ (const char *) "^.....    ",
           /* line */ (const char *) "   ..     ",
           /* line */ (const char *) "   .      ",
           /* line */ (const char *) "   .      ",
           /* line */ (const char *) "   .      ",
           /* line */ (const char *) "   ^      ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^  ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) " .x.|. ",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "    ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^   ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "^....^",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "   ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^        ",
           /* line */ (const char *) "   .        ",
           /* line */ (const char *) "  .........^",
           /* line */ (const char *) "^...m.g..   ",
           /* line */ (const char *) "  .......   ",
           /* line */ (const char *) "     ..     ",
           /* line */ (const char *) "      ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^  ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "    ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^     ",
           /* line */ (const char *) " .......^",
           /* line */ (const char *) " .x.m.x. ",
           /* line */ (const char *) "^....... ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^        ",
           /* line */ (const char *) "  ........^",
           /* line */ (const char *) "  .......  ",
           /* line */ (const char *) "^........  ",
           /* line */ (const char *) "     ..    ",
           /* line */ (const char *) "      .    ",
           /* line */ (const char *) "      ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^    ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "^...... ",
           /* line */ (const char *) " ......^",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "   ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^   ",
           /* line */ (const char *) "^....... ",
           /* line */ (const char *) " .......^",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "     ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^    ",
           /* line */ (const char *) "    .    ",
           /* line */ (const char *) "   ..    ",
           /* line */ (const char *) "^.......^",
           /* line */ (const char *) "  ....   ",
           /* line */ (const char *) "   ..    ",
           /* line */ (const char *) "   .     ",
           /* line */ (const char *) "   .     ",
           /* line */ (const char *) "   ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^   ",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) "^....... ",
           /* line */ (const char *) " .......^",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^  ",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^     ",
           /* line */ (const char *) "     ..    ",
           /* line */ (const char *) "   ......  ",
           /* line */ (const char *) "^.........^",
           /* line */ (const char *) "     ..    ",
           /* line */ (const char *) "     .     ",
           /* line */ (const char *) "     .     ",
           /* line */ (const char *) "     ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^   ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "^......^",
           /* line */ (const char *) " ...... ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "   ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^   ",
           /* line */ (const char *) " .......^",
           /* line */ (const char *) " .x.|.|. ",
           /* line */ (const char *) "^....... ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^     ",
           /* line */ (const char *) "    .     ",
           /* line */ (const char *) "^.......  ",
           /* line */ (const char *) " .......  ",
           /* line */ (const char *) " ........^",
           /* line */ (const char *) "    ..    ",
           /* line */ (const char *) "    ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^     ",
           /* line */ (const char *) "^.......^",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "     ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^      ",
           /* line */ (const char *) " .......^",
           /* line */ (const char *) " .m.|.M. ",
           /* line */ (const char *) "^....... ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "     ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^      ",
           /* line */ (const char *) "^......   ",
           /* line */ (const char *) "  .......^",
           /* line */ (const char *) "  .....   ",
           /* line */ (const char *) "    ..    ",
           /* line */ (const char *) "     .    ",
           /* line */ (const char *) "     .    ",
           /* line */ (const char *) "     ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^   ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) " ......^",
           /* line */ (const char *) "^...... ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "   ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "      ^  ",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) " .|.g.|.^",
           /* line */ (const char *) "^....... ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^    ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) " .g.m. ",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "    ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^   ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "   ....  ",
           /* line */ (const char *) "^.......^",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "    .    ",
           /* line */ (const char *) "    .    ",
           /* line */ (const char *) "    .    ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^     ",
           /* line */ (const char *) "  ........^",
           /* line */ (const char *) "^........  ",
           /* line */ (const char *) "  .......  ",
           /* line */ (const char *) "     ..    ",
           /* line */ (const char *) "      .    ",
           /* line */ (const char *) "      ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^    ",
           /* line */ (const char *) " .......^",
           /* line */ (const char *) "^....... ",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^     ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) "^..m.. ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^     ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) " .m.x. ",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^     ",
           /* line */ (const char *) "    .     ",
           /* line */ (const char *) "^......   ",
           /* line */ (const char *) "  .......^",
           /* line */ (const char *) "  .....   ",
           /* line */ (const char *) "    ..    ",
           /* line */ (const char *) "     ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^   ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) " ......^",
           /* line */ (const char *) "^...... ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "    ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^   ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "^......^",
           /* line */ (const char *) " ...... ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "    ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^       ",
           /* line */ (const char *) " .....     ",
           /* line */ (const char *) "^.....     ",
           /* line */ (const char *) " .........^",
           /* line */ (const char *) "   ..      ",
           /* line */ (const char *) "   ^       ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^  ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "    ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^   ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "^.....  ",
           /* line */ (const char *) "  .....^",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "   .    ",
           /* line */ (const char *) "   ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^    ",
           /* line */ (const char *) "^.....^",
           /* line */ (const char *) " ..g.. ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^    ",
           /* line */ (const char *) "  ..   ",
           /* line */ (const char *) "^.....^",
           /* line */ (const char *) " ....  ",
           /* line */ (const char *) "  ..   ",
           /* line */ (const char *) "  .    ",
           /* line */ (const char *) "  ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^   ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "^....^",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^     ",
           /* line */ (const char *) "  .     ",
           /* line */ (const char *) "  .     ",
           /* line */ (const char *) "^......^",
           /* line */ (const char *) " .....  ",
           /* line */ (const char *) " .....  ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "   ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^     ",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) "^..m..|.^",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^    ",
           /* line */ (const char *) "^....... ",
           /* line */ (const char *) " .m.|.x. ",
           /* line */ (const char *) " .......^",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "     ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^  ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) " ....^",
           /* line */ (const char *) "^.... ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^  ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "    .  ",
           /* line */ (const char *) "    ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^       ",
           /* line */ (const char *) "  .......    ",
           /* line */ (const char *) "^........    ",
           /* line */ (const char *) "  ..........^",
           /* line */ (const char *) "     ..      ",
           /* line */ (const char *) "     ^       ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^   ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "^......^",
           /* line */ (const char *) " ...... ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "    ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "      ^  ",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) "^.......^",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "      ^    ",
           /* line */ (const char *) "      .    ",
           /* line */ (const char *) "   ....... ",
           /* line */ (const char *) "   .g.|.|.^",
           /* line */ (const char *) "^......... ",
           /* line */ (const char *) "      ..   ",
           /* line */ (const char *) "      .    ",
           /* line */ (const char *) "      ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "      ^   ",
           /* line */ (const char *) "     ..   ",
           /* line */ (const char *) "^.......  ",
           /* line */ (const char *) "    .....^",
           /* line */ (const char *) "     ..   ",
           /* line */ (const char *) "     ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^  ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "^....^",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^   ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "^......^",
           /* line */ (const char *) " ...... ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "    ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^    ",
           /* line */ (const char *) "   .    ",
           /* line */ (const char *) "   .    ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "^......^",
           /* line */ (const char *) "  ....  ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "    .   ",
           /* line */ (const char *) "    .   ",
           /* line */ (const char *) "    ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^   ",
           /* line */ (const char *) "     .   ",
           /* line */ (const char *) "     ..  ",
           /* line */ (const char *) "^....... ",
           /* line */ (const char *) "    ....^",
           /* line */ (const char *) "     ..  ",
           /* line */ (const char *) "     .   ",
           /* line */ (const char *) "     .   ",
           /* line */ (const char *) "     ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^   ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^   ",
           /* line */ (const char *) "   .   ",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "  ....^",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^    ",
           /* line */ (const char *) "^....... ",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) " .......^",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^    ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "^......^",
           /* line */ (const char *) " ...... ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "   ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^   ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "^.....^",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "    ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^         ",
           /* line */ (const char *) "  .         ",
           /* line */ (const char *) "  .......   ",
           /* line */ (const char *) "  .x.m.m...^",
           /* line */ (const char *) "^........   ",
           /* line */ (const char *) "     ..     ",
           /* line */ (const char *) "      .     ",
           /* line */ (const char *) "      ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^    ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^    ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) " ...... ",
           /* line */ (const char *) "^......^",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "   ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^  ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) "^..m.. ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^       ",
           /* line */ (const char *) "   .       ",
           /* line */ (const char *) "   .       ",
           /* line */ (const char *) "   .....   ",
           /* line */ (const char *) "^.......   ",
           /* line */ (const char *) "   .......^",
           /* line */ (const char *) "     ..    ",
           /* line */ (const char *) "     .     ",
           /* line */ (const char *) "     ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^     ",
           /* line */ (const char *) "  .     ",
           /* line */ (const char *) "  ..... ",
           /* line */ (const char *) "  ..... ",
           /* line */ (const char *) "^......^",
           /* line */ (const char *) "    ..  ",
           /* line */ (const char *) "    .   ",
           /* line */ (const char *) "    ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^   ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "^.... ",
           /* line */ (const char *) " ....^",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "   ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^  ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^    ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) "^..|.. ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "    ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^      ",
           /* line */ (const char *) "  .....  ",
           /* line */ (const char *) "  ..G..  ",
           /* line */ (const char *) "^.......^",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "    .    ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^     ",
           /* line */ (const char *) "    ..    ",
           /* line */ (const char *) "   ....   ",
           /* line */ (const char *) "^........^",
           /* line */ (const char *) "    ..    ",
           /* line */ (const char *) "    .     ",
           /* line */ (const char *) "    ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^    ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) " ...... ",
           /* line */ (const char *) "^......^",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "   ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^    ",
           /* line */ (const char *) "   ..    ",
           /* line */ (const char *) " ......  ",
           /* line */ (const char *) "^.......^",
           /* line */ (const char *) "   ..    ",
           /* line */ (const char *) "   ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^    ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "^...... ",
           /* line */ (const char *) " ......^",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "   ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^    ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "^......^",
           /* line */ (const char *) " ...... ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "    ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^    ",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) " ..m.g.. ",
           /* line */ (const char *) "^.......^",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^      ",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) "^.......^",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "     ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^    ",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) "^..g.x.. ",
           /* line */ (const char *) " .......^",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "     ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^    ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "^......^",
           /* line */ (const char *) " ...... ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "    ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^   ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " ..|..^",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^     ",
           /* line */ (const char *) "^.......^",
           /* line */ (const char *) "   ..... ",
           /* line */ (const char *) "   ..... ",
           /* line */ (const char *) "     ..  ",
           /* line */ (const char *) "     ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^     ",
           /* line */ (const char *) "   .     ",
           /* line */ (const char *) "   .     ",
           /* line */ (const char *) "  .....  ",
           /* line */ (const char *) "  .....  ",
           /* line */ (const char *) "^.......^",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "     .   ",
           /* line */ (const char *) "     ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^  ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "^....^",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "   ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^     ",
           /* line */ (const char *) "   .     ",
           /* line */ (const char *) "   ..    ",
           /* line */ (const char *) "^.......^",
           /* line */ (const char *) " ......  ",
           /* line */ (const char *) "   ..    ",
           /* line */ (const char *) "    .    ",
           /* line */ (const char *) "    .    ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^   ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "^......^",
           /* line */ (const char *) " ...... ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "    ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^    ",
           /* line */ (const char *) "  ..   ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) "^....  ",
           /* line */ (const char *) "  ..   ",
           /* line */ (const char *) "   .   ",
           /* line */ (const char *) "   .   ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^    ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "^...... ",
           /* line */ (const char *) " ......^",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "    ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "      ^     ",
           /* line */ (const char *) "      .     ",
           /* line */ (const char *) "      ..    ",
           /* line */ (const char *) "^..........^",
           /* line */ (const char *) "    ......  ",
           /* line */ (const char *) "      ..    ",
           /* line */ (const char *) "      .     ",
           /* line */ (const char *) "      ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^   ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "^......^",
           /* line */ (const char *) " ...... ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "   ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^   ",
           /* line */ (const char *) "   .   ",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "^.....^",
           /* line */ (const char *) "  .... ",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "    .  ",
           /* line */ (const char *) "    .  ",
           /* line */ (const char *) "    ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^       ",
           /* line */ (const char *) "    .       ",
           /* line */ (const char *) "    .......^",
           /* line */ (const char *) "    ....... ",
           /* line */ (const char *) "^.......... ",
           /* line */ (const char *) "       ..   ",
           /* line */ (const char *) "        ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^  ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) " .|.x. ",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "    ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^   ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "^.....  ",
           /* line */ (const char *) "  .....^",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "    .   ",
           /* line */ (const char *) "    .   ",
           /* line */ (const char *) "    ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^  ",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^   ",
           /* line */ (const char *) "     .   ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "  ......^",
           /* line */ (const char *) "^....... ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "     .   ",
           /* line */ (const char *) "     ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^   ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "^...... ",
           /* line */ (const char *) " ......^",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "    ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^  ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "^.|.|.^",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^  ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "^....^",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^   ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) " ...... ",
           /* line */ (const char *) "^......^",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "   ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^     ",
           /* line */ (const char *) "     .     ",
           /* line */ (const char *) "     .     ",
           /* line */ (const char *) "     ..    ",
           /* line */ (const char *) "   ......  ",
           /* line */ (const char *) "^.........^",
           /* line */ (const char *) "     ..    ",
           /* line */ (const char *) "     ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^  ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) " ....^",
           /* line */ (const char *) "^.... ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "   ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^      ",
           /* line */ (const char *) "   .......  ",
           /* line */ (const char *) "^...|..g...^",
           /* line */ (const char *) "   .......  ",
           /* line */ (const char *) "      ..    ",
           /* line */ (const char *) "       ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^    ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) " ......^",
           /* line */ (const char *) "^...... ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "   ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^   ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "^....^",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^          ",
           /* line */ (const char *) "   .          ",
           /* line */ (const char *) "   .......    ",
           /* line */ (const char *) "^....g..x....^",
           /* line */ (const char *) "   .......    ",
           /* line */ (const char *) "      ..      ",
           /* line */ (const char *) "       .      ",
           /* line */ (const char *) "       ^      ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^   ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "^....^",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "   ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^     ",
           /* line */ (const char *) "   .     ",
           /* line */ (const char *) "   .     ",
           /* line */ (const char *) "   ..    ",
           /* line */ (const char *) "^......  ",
           /* line */ (const char *) " .......^",
           /* line */ (const char *) "   ..    ",
           /* line */ (const char *) "    .    ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^   ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) " ....^",
           /* line */ (const char *) "^.... ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "      ^   ",
           /* line */ (const char *) "      .   ",
           /* line */ (const char *) "  ....... ",
           /* line */ (const char *) "  ....... ",
           /* line */ (const char *) "^........^",
           /* line */ (const char *) "     ..   ",
           /* line */ (const char *) "     ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^  ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) " ....^",
           /* line */ (const char *) "^.... ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "   ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^    ",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) " .|.x.x.^",
           /* line */ (const char *) "^....... ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "     ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^      ",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) " .......^",
           /* line */ (const char *) "^....... ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "     ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^  ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "^.... ",
           /* line */ (const char *) " ....^",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "      ^  ",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) "^.......^",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^   ",
           /* line */ (const char *) "^.....^",
           /* line */ (const char *) " .|.|. ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "      ^      ",
           /* line */ (const char *) "^...........^",
           /* line */ (const char *) "   .......   ",
           /* line */ (const char *) "   .......   ",
           /* line */ (const char *) "      ..     ",
           /* line */ (const char *) "      ^      ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^    ",
           /* line */ (const char *) "   .....  ",
           /* line */ (const char *) "   ..|...^",
           /* line */ (const char *) "^.......  ",
           /* line */ (const char *) "     ..   ",
           /* line */ (const char *) "      ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^   ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "^....^",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "   ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "       ^    ",
           /* line */ (const char *) "       .    ",
           /* line */ (const char *) "      ..    ",
           /* line */ (const char *) "    ......  ",
           /* line */ (const char *) "^..........^",
           /* line */ (const char *) "      ..    ",
           /* line */ (const char *) "       .    ",
           /* line */ (const char *) "       .    ",
           /* line */ (const char *) "       ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "       ^    ",
           /* line */ (const char *) "       .    ",
           /* line */ (const char *) "      ..    ",
           /* line */ (const char *) "    ......  ",
           /* line */ (const char *) "^..........^",
           /* line */ (const char *) "      ..    ",
           /* line */ (const char *) "       ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^   ",
           /* line */ (const char *) "  .   ",
           /* line */ (const char *) "  .   ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "^....^",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "   .  ",
           /* line */ (const char *) "   ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^    ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "^...... ",
           /* line */ (const char *) " ......^",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "    ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^   ",
           /* line */ (const char *) " .......^",
           /* line */ (const char *) "^.|.G.|. ",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "     ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^    ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "^.....  ",
           /* line */ (const char *) "  .....^",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "   .    ",
           /* line */ (const char *) "   ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^        ",
           /* line */ (const char *) "   .......    ",
           /* line */ (const char *) "   .m.g.x....^",
           /* line */ (const char *) "^.........    ",
           /* line */ (const char *) "      ..      ",
           /* line */ (const char *) "      ^       ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "      ^    ",
           /* line */ (const char *) "      .    ",
           /* line */ (const char *) "      .    ",
           /* line */ (const char *) "^.......   ",
           /* line */ (const char *) " ..g.|....^",
           /* line */ (const char *) " .......   ",
           /* line */ (const char *) "    ..     ",
           /* line */ (const char *) "    ^      ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^    ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "^......^",
           /* line */ (const char *) " ...... ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "    ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "        ^  ",
           /* line */ (const char *) "        .  ",
           /* line */ (const char *) "^.........^",
           /* line */ (const char *) "   ....... ",
           /* line */ (const char *) "   ....... ",
           /* line */ (const char *) "      ..   ",
           /* line */ (const char *) "       ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^  ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "^....^",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "   .  ",
           /* line */ (const char *) "   .  ",
           /* line */ (const char *) "   .  ",
           /* line */ (const char *) "   .  ",
           /* line */ (const char *) "   ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^   ",
           /* line */ (const char *) "   .   ",
           /* line */ (const char *) "  ..   ",
           /* line */ (const char *) "^.....^",
           /* line */ (const char *) " ....  ",
           /* line */ (const char *) "  ..   ",
           /* line */ (const char *) "   .   ",
           /* line */ (const char *) "   .   ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^   ",
           /* line */ (const char *) "     .   ",
           /* line */ (const char *) "  .....  ",
           /* line */ (const char *) "^......  ",
           /* line */ (const char *) "  ......^",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "     .   ",
           /* line */ (const char *) "     ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "      ^      ",
           /* line */ (const char *) "  .......    ",
           /* line */ (const char *) "^..|..|.....^",
           /* line */ (const char *) "  .......    ",
           /* line */ (const char *) "     ..      ",
           /* line */ (const char *) "      .      ",
           /* line */ (const char *) "      ^      ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^   ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "^...... ",
           /* line */ (const char *) " ......^",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "   ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^   ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "  .....^",
           /* line */ (const char *) "^.....  ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "   .    ",
           /* line */ (const char *) "   ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^   ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "^......^",
           /* line */ (const char *) "  ....  ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "    ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^    ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) " ...... ",
           /* line */ (const char *) "^......^",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "   ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^  ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "^.....^",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^   ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) " ....^",
           /* line */ (const char *) "^.... ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^  ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "^....^",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "   ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^   ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "^...... ",
           /* line */ (const char *) " ......^",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "   ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^   ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "^....... ",
           /* line */ (const char *) "  ......^",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "     ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^   ",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) "^.......^",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "     ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^   ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) " ...... ",
           /* line */ (const char *) "^......^",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "   ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^     ",
           /* line */ (const char *) "    .     ",
           /* line */ (const char *) "    ..    ",
           /* line */ (const char *) "^........^",
           /* line */ (const char *) "  ......  ",
           /* line */ (const char *) "    ..    ",
           /* line */ (const char *) "    ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^  ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "^..m.. ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^   ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "^....^",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "   ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^   ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "^....^",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^   ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "^.....^",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^    ",
           /* line */ (const char *) "    .    ",
           /* line */ (const char *) "    .    ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "^.......^",
           /* line */ (const char *) "  ...... ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^    ",
           /* line */ (const char *) "^....... ",
           /* line */ (const char *) " ..g.m.. ",
           /* line */ (const char *) " .......^",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "     ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^   ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "^......^",
           /* line */ (const char *) " ...... ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "    ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^     ",
           /* line */ (const char *) "^.........^",
           /* line */ (const char *) "  .....    ",
           /* line */ (const char *) "  .....    ",
           /* line */ (const char *) "    ..     ",
           /* line */ (const char *) "     .     ",
           /* line */ (const char *) "     ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^    ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) " ......^",
           /* line */ (const char *) "^...... ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "    ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^  ",
           /* line */ (const char *) "^.....^",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "    ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^   ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "^......^",
           /* line */ (const char *) " ...... ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "   ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^  ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "^....^",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^     ",
           /* line */ (const char *) "    .     ",
           /* line */ (const char *) "    ..    ",
           /* line */ (const char *) "^........^",
           /* line */ (const char *) "  ......  ",
           /* line */ (const char *) "    ..    ",
           /* line */ (const char *) "    ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^   ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "^....^",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^     ",
           /* line */ (const char *) "    ..     ",
           /* line */ (const char *) "  ........^",
           /* line */ (const char *) "^.......   ",
           /* line */ (const char *) "    ..     ",
           /* line */ (const char *) "     .     ",
           /* line */ (const char *) "     .     ",
           /* line */ (const char *) "     ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^   ",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) "^....... ",
           /* line */ (const char *) " .......^",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "     ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^   ",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "  ....^",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "   .   ",
           /* line */ (const char *) "   .   ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^    ",
           /* line */ (const char *) "^....... ",
           /* line */ (const char *) " .......^",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "     ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "      ^     ",
           /* line */ (const char *) "      .     ",
           /* line */ (const char *) "^.........  ",
           /* line */ (const char *) "   ..m..G..^",
           /* line */ (const char *) "   .......  ",
           /* line */ (const char *) "      ..    ",
           /* line */ (const char *) "       .    ",
           /* line */ (const char *) "       .    ",
           /* line */ (const char *) "       ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^  ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "^....^",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^   ",
           /* line */ (const char *) "  .   ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "^....^",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "   .  ",
           /* line */ (const char *) "   .  ",
           /* line */ (const char *) "   ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^   ",
           /* line */ (const char *) "     .   ",
           /* line */ (const char *) "     .   ",
           /* line */ (const char *) "     .   ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "  ......^",
           /* line */ (const char *) "^....... ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "    .    ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^  ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) " ....^",
           /* line */ (const char *) "^.... ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "   ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^  ",
           /* line */ (const char *) "    .  ",
           /* line */ (const char *) "^.....^",
           /* line */ (const char *) " .x.x. ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "   .   ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^  ",
           /* line */ (const char *) "^.....^",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^  ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "^....^",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^         ",
           /* line */ (const char *) "^........     ",
           /* line */ (const char *) "  ..|..|.     ",
           /* line */ (const char *) "  ...........^",
           /* line */ (const char *) "     ..       ",
           /* line */ (const char *) "     .        ",
           /* line */ (const char *) "     .        ",
           /* line */ (const char *) "     ^        ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^  ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "^.... ",
           /* line */ (const char *) " ....^",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "   ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^    ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^  ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "^.... ",
           /* line */ (const char *) " ....^",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "   ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^   ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) " ...... ",
           /* line */ (const char *) "^......^",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "   ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^   ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "^....^",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^      ",
           /* line */ (const char *) "^.....     ",
           /* line */ (const char *) " .....     ",
           /* line */ (const char *) " .........^",
           /* line */ (const char *) "   ..      ",
           /* line */ (const char *) "    .      ",
           /* line */ (const char *) "    ^      ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^    ",
           /* line */ (const char *) " .......^",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) "^....... ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "     ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^    ",
           /* line */ (const char *) "     .    ",
           /* line */ (const char *) "    ..    ",
           /* line */ (const char *) "^.......  ",
           /* line */ (const char *) "  .......^",
           /* line */ (const char *) "    ..    ",
           /* line */ (const char *) "     .    ",
           /* line */ (const char *) "     ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^  ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) " ....^",
           /* line */ (const char *) "^.... ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "  .   ",
           /* line */ (const char *) "  .   ",
           /* line */ (const char *) "  .   ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^     ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) "^..|.. ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "    ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^   ",
           /* line */ (const char *) "   .   ",
           /* line */ (const char *) "  ..   ",
           /* line */ (const char *) "^....  ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) "  ..   ",
           /* line */ (const char *) "   .   ",
           /* line */ (const char *) "   .   ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^    ",
           /* line */ (const char *) "   ..    ",
           /* line */ (const char *) "^......  ",
           /* line */ (const char *) " .......^",
           /* line */ (const char *) "   ..    ",
           /* line */ (const char *) "    .    ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^   ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " .x.g.^",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "    ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^       ",
           /* line */ (const char *) "  .       ",
           /* line */ (const char *) "  .       ",
           /* line */ (const char *) "  ....... ",
           /* line */ (const char *) "  .g..|.. ",
           /* line */ (const char *) "^........^",
           /* line */ (const char *) "     ..   ",
           /* line */ (const char *) "      .   ",
           /* line */ (const char *) "      .   ",
           /* line */ (const char *) "      ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^   ",
           /* line */ (const char *) "     .   ",
           /* line */ (const char *) "     ..  ",
           /* line */ (const char *) "    .... ",
           /* line */ (const char *) "^.......^",
           /* line */ (const char *) "     ..  ",
           /* line */ (const char *) "      ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^    ",
           /* line */ (const char *) "    .    ",
           /* line */ (const char *) "   ..    ",
           /* line */ (const char *) "^.......^",
           /* line */ (const char *) " ......  ",
           /* line */ (const char *) "   ..    ",
           /* line */ (const char *) "   ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "         ^    ",
           /* line */ (const char *) "         .    ",
           /* line */ (const char *) "^..........   ",
           /* line */ (const char *) "    .|.|.x.   ",
           /* line */ (const char *) "    .........^",
           /* line */ (const char *) "       ..     ",
           /* line */ (const char *) "        ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "       ^   ",
           /* line */ (const char *) "       .   ",
           /* line */ (const char *) "^........  ",
           /* line */ (const char *) "  ..g..x.  ",
           /* line */ (const char *) "  ........^",
           /* line */ (const char *) "     ..    ",
           /* line */ (const char *) "     .     ",
           /* line */ (const char *) "     ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^     ",
           /* line */ (const char *) "  .     ",
           /* line */ (const char *) "  .     ",
           /* line */ (const char *) "^...... ",
           /* line */ (const char *) "  .x.m. ",
           /* line */ (const char *) "  .....^",
           /* line */ (const char *) "    ..  ",
           /* line */ (const char *) "     .  ",
           /* line */ (const char *) "     ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^     ",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) " .......^",
           /* line */ (const char *) "^....... ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "     ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^  ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "^.... ",
           /* line */ (const char *) " ....^",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "      ^    ",
           /* line */ (const char *) "      .    ",
           /* line */ (const char *) "   .....   ",
           /* line */ (const char *) "   .g.G.   ",
           /* line */ (const char *) "^.........^",
           /* line */ (const char *) "     ..    ",
           /* line */ (const char *) "      .    ",
           /* line */ (const char *) "      ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^    ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "^...... ",
           /* line */ (const char *) " ......^",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "    ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^      ",
           /* line */ (const char *) "     .      ",
           /* line */ (const char *) "^........   ",
           /* line */ (const char *) "  .........^",
           /* line */ (const char *) "  .......   ",
           /* line */ (const char *) "     ..     ",
           /* line */ (const char *) "      .     ",
           /* line */ (const char *) "      ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "      ^    ",
           /* line */ (const char *) " .......   ",
           /* line */ (const char *) " .x.|.g...^",
           /* line */ (const char *) "^.......   ",
           /* line */ (const char *) "    ..     ",
           /* line */ (const char *) "    ^      ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "      ^    ",
           /* line */ (const char *) "      ..   ",
           /* line */ (const char *) "^......... ",
           /* line */ (const char *) "    ......^",
           /* line */ (const char *) "      ..   ",
           /* line */ (const char *) "      .    ",
           /* line */ (const char *) "      .    ",
           /* line */ (const char *) "      ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^  ",
           /* line */ (const char *) "    .  ",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "  .... ",
           /* line */ (const char *) "^.....^",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^   ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "^....^",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "   ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^      ",
           /* line */ (const char *) "   ..     ",
           /* line */ (const char *) "  .......^",
           /* line */ (const char *) "^.....    ",
           /* line */ (const char *) "   ..     ",
           /* line */ (const char *) "    .     ",
           /* line */ (const char *) "    .     ",
           /* line */ (const char *) "    ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^        ",
           /* line */ (const char *) "    .......  ",
           /* line */ (const char *) "^....m.|.m.  ",
           /* line */ (const char *) "    ........^",
           /* line */ (const char *) "       ..    ",
           /* line */ (const char *) "       .     ",
           /* line */ (const char *) "       .     ",
           /* line */ (const char *) "       ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^        ",
           /* line */ (const char *) "    .......  ",
           /* line */ (const char *) "^..........  ",
           /* line */ (const char *) "    ........^",
           /* line */ (const char *) "       ..    ",
           /* line */ (const char *) "       ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^     ",
           /* line */ (const char *) "    .     ",
           /* line */ (const char *) "    .     ",
           /* line */ (const char *) "   ..     ",
           /* line */ (const char *) "^......   ",
           /* line */ (const char *) " ........^",
           /* line */ (const char *) "   ..     ",
           /* line */ (const char *) "   ^      ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^     ",
           /* line */ (const char *) "   .     ",
           /* line */ (const char *) "  ..     ",
           /* line */ (const char *) " .......^",
           /* line */ (const char *) "^....    ",
           /* line */ (const char *) "  ..     ",
           /* line */ (const char *) "  ^      ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^    ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "^......^",
           /* line */ (const char *) " ...... ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "   ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^      ",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) "^.......^",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^   ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "^....^",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^   ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) " ....^",
           /* line */ (const char *) "^.... ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^   ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "^...... ",
           /* line */ (const char *) " ......^",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "   ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^    ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "^...... ",
           /* line */ (const char *) " ......^",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "   ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^    ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) " ......^",
           /* line */ (const char *) "^...... ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "    ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^   ",
           /* line */ (const char *) "    .   ",
           /* line */ (const char *) "    .   ",
           /* line */ (const char *) "    .   ",
           /* line */ (const char *) " ......^",
           /* line */ (const char *) "^.....  ",
           /* line */ (const char *) " .....  ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "   .    ",
           /* line */ (const char *) "   ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^     ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "^.m.g.^",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^    ",
           /* line */ (const char *) "    .    ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "^.......^",
           /* line */ (const char *) "  ...... ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "     ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "       ^    ",
           /* line */ (const char *) "       .    ",
           /* line */ (const char *) "  .......   ",
           /* line */ (const char *) "  .g.|.m.   ",
           /* line */ (const char *) "^..........^",
           /* line */ (const char *) "     ..     ",
           /* line */ (const char *) "     ^      ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^   ",
           /* line */ (const char *) "^.....^",
           /* line */ (const char *) " .g.g. ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^  ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^    ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) " ...... ",
           /* line */ (const char *) "^......^",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "    ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^    ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "^...... ",
           /* line */ (const char *) " ......^",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "   ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^       ",
           /* line */ (const char *) "    .       ",
           /* line */ (const char *) "    ..      ",
           /* line */ (const char *) "^.......    ",
           /* line */ (const char *) "  .........^",
           /* line */ (const char *) "    ..      ",
           /* line */ (const char *) "     ^      ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^    ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) " ...... ",
           /* line */ (const char *) "^......^",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "    ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^     ",
           /* line */ (const char *) "   .     ",
           /* line */ (const char *) "   ..    ",
           /* line */ (const char *) "^......  ",
           /* line */ (const char *) " .......^",
           /* line */ (const char *) "   ..    ",
           /* line */ (const char *) "    .    ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^    ",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "    ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^      ",
           /* line */ (const char *) "   .      ",
           /* line */ (const char *) "   ..     ",
           /* line */ (const char *) " ......   ",
           /* line */ (const char *) "^........^",
           /* line */ (const char *) "   ..     ",
           /* line */ (const char *) "   .      ",
           /* line */ (const char *) "   ^      ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^       ",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) " .|..g..^",
           /* line */ (const char *) "^....... ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^   ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "^......^",
           /* line */ (const char *) " ...... ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "   ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^   ",
           /* line */ (const char *) "   .   ",
           /* line */ (const char *) "   .   ",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) "  ....^",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "    .  ",
           /* line */ (const char *) "    .  ",
           /* line */ (const char *) "    .  ",
           /* line */ (const char *) "    .  ",
           /* line */ (const char *) "    ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^     ",
           /* line */ (const char *) "  .......  ",
           /* line */ (const char *) "^..x.M.m.  ",
           /* line */ (const char *) "  ........^",
           /* line */ (const char *) "     ..    ",
           /* line */ (const char *) "      .    ",
           /* line */ (const char *) "      .    ",
           /* line */ (const char *) "      ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^  ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "^....^",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "   ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^   ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "^.... ",
           /* line */ (const char *) " ....^",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^  ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "^.... ",
           /* line */ (const char *) " ....^",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "   ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^  ",
           /* line */ (const char *) "    .  ",
           /* line */ (const char *) "    .  ",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) "  ....^",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "   .   ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^  ",
           /* line */ (const char *) "^.....^",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "    ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "       ^   ",
           /* line */ (const char *) "  ........^",
           /* line */ (const char *) "  ..G.m..  ",
           /* line */ (const char *) "^........  ",
           /* line */ (const char *) "     ..    ",
           /* line */ (const char *) "     .     ",
           /* line */ (const char *) "     .     ",
           /* line */ (const char *) "     ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^     ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "^.g.g.^",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "    ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "      ^   ",
           /* line */ (const char *) "     ..   ",
           /* line */ (const char *) "^........^",
           /* line */ (const char *) "   ...... ",
           /* line */ (const char *) "     ..   ",
           /* line */ (const char *) "      .   ",
           /* line */ (const char *) "      ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^  ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "^....^",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^  ",
           /* line */ (const char *) "    ..  ",
           /* line */ (const char *) "   .... ",
           /* line */ (const char *) "^......^",
           /* line */ (const char *) "    ..  ",
           /* line */ (const char *) "    .   ",
           /* line */ (const char *) "    ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^   ",
           /* line */ (const char *) "  .   ",
           /* line */ (const char *) "  .   ",
           /* line */ (const char *) "  .   ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "^.... ",
           /* line */ (const char *) " ....^",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "  .   ",
           /* line */ (const char *) "  .   ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^     ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) " ..g.. ",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "    ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^   ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "^....^",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^    ",
           /* line */ (const char *) "     ..   ",
           /* line */ (const char *) "^........^",
           /* line */ (const char *) "   ...... ",
           /* line */ (const char *) "     ..   ",
           /* line */ (const char *) "      .   ",
           /* line */ (const char *) "      ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^  ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "^.... ",
           /* line */ (const char *) " ....^",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^    ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "^...... ",
           /* line */ (const char *) " ......^",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "   ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^    ",
           /* line */ (const char *) "    .    ",
           /* line */ (const char *) "   ..    ",
           /* line */ (const char *) "^.......^",
           /* line */ (const char *) "  ....   ",
           /* line */ (const char *) "   ..    ",
           /* line */ (const char *) "    .    ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^    ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) " ......^",
           /* line */ (const char *) "^...... ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "   ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^    ",
           /* line */ (const char *) "  .    ",
           /* line */ (const char *) "  ..   ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) "^....  ",
           /* line */ (const char *) "  ..   ",
           /* line */ (const char *) "  .    ",
           /* line */ (const char *) "  .    ",
           /* line */ (const char *) "  ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^    ",
           /* line */ (const char *) "  .    ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "    .  ",
           /* line */ (const char *) "    ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^     ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) " .|.|. ",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^    ",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^    ",
           /* line */ (const char *) "  .    ",
           /* line */ (const char *) "  ..   ",
           /* line */ (const char *) "^.....^",
           /* line */ (const char *) " ....  ",
           /* line */ (const char *) "  ..   ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^  ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " .|.|. ",
           /* line */ (const char *) "^.....^",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^   ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "^.... ",
           /* line */ (const char *) " ....^",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^    ",
           /* line */ (const char *) "     .    ",
           /* line */ (const char *) "     ..   ",
           /* line */ (const char *) "    .....^",
           /* line */ (const char *) "^.......  ",
           /* line */ (const char *) "     ..   ",
           /* line */ (const char *) "     .    ",
           /* line */ (const char *) "     ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^    ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) " ...... ",
           /* line */ (const char *) "^......^",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "   ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^    ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) " ......^",
           /* line */ (const char *) "^...... ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "    ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^  ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "^.... ",
           /* line */ (const char *) " ....^",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "   ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^        ",
           /* line */ (const char *) "   .        ",
           /* line */ (const char *) "   .        ",
           /* line */ (const char *) "  .......   ",
           /* line */ (const char *) "^........   ",
           /* line */ (const char *) "  .........^",
           /* line */ (const char *) "     ..     ",
           /* line */ (const char *) "     ^      ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^    ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "    ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^   ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) " ......^",
           /* line */ (const char *) "^...... ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "    ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^   ",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "    ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^     ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "^.....^",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "    ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^   ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "^.... ",
           /* line */ (const char *) " ....^",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "   ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^     ",
           /* line */ (const char *) "    .     ",
           /* line */ (const char *) "    ..    ",
           /* line */ (const char *) "^......   ",
           /* line */ (const char *) "   ......^",
           /* line */ (const char *) "    ..    ",
           /* line */ (const char *) "     .    ",
           /* line */ (const char *) "     ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^    ",
           /* line */ (const char *) "   .    ",
           /* line */ (const char *) "   .    ",
           /* line */ (const char *) " .....  ",
           /* line */ (const char *) " ..x...^",
           /* line */ (const char *) "^.....  ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "   .    ",
           /* line */ (const char *) "   .    ",
           /* line */ (const char *) "   .    ",
           /* line */ (const char *) "   ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^     ",
           /* line */ (const char *) "    ..    ",
           /* line */ (const char *) "  .......^",
           /* line */ (const char *) "^.......  ",
           /* line */ (const char *) "    ..    ",
           /* line */ (const char *) "    .     ",
           /* line */ (const char *) "    .     ",
           /* line */ (const char *) "    ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^   ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) " ......^",
           /* line */ (const char *) "^...... ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "   ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^       ",
           /* line */ (const char *) "^....... ",
           /* line */ (const char *) " ..m..x.^",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "     ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "       ^  ",
           /* line */ (const char *) "^........ ",
           /* line */ (const char *) "  ..g.g.. ",
           /* line */ (const char *) "  .......^",
           /* line */ (const char *) "     ..   ",
           /* line */ (const char *) "     .    ",
           /* line */ (const char *) "     ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^  ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "^.... ",
           /* line */ (const char *) " ....^",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "       ^    ",
           /* line */ (const char *) "    .......^",
           /* line */ (const char *) "^........   ",
           /* line */ (const char *) "    .....   ",
           /* line */ (const char *) "      ..    ",
           /* line */ (const char *) "       .    ",
           /* line */ (const char *) "       .    ",
           /* line */ (const char *) "       ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^      ",
           /* line */ (const char *) "    .      ",
           /* line */ (const char *) "    ..     ",
           /* line */ (const char *) "^.......   ",
           /* line */ (const char *) "  ........^",
           /* line */ (const char *) "    ..     ",
           /* line */ (const char *) "    ^      ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^    ",
           /* line */ (const char *) "^.....  ",
           /* line */ (const char *) " .....  ",
           /* line */ (const char *) " ......^",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "    .   ",
           /* line */ (const char *) "    ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^         ",
           /* line */ (const char *) "  .......    ",
           /* line */ (const char *) "  .......    ",
           /* line */ (const char *) "^...........^",
           /* line */ (const char *) "     ..      ",
           /* line */ (const char *) "      ^      ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "       ^  ",
           /* line */ (const char *) "       .  ",
           /* line */ (const char *) "    .....^",
           /* line */ (const char *) "    ..... ",
           /* line */ (const char *) "^........ ",
           /* line */ (const char *) "      ..  ",
           /* line */ (const char *) "       .  ",
           /* line */ (const char *) "       ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^   ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "^....^",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "   ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^    ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "^.....^",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "    ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^   ",
           /* line */ (const char *) "    .   ",
           /* line */ (const char *) "    .   ",
           /* line */ (const char *) "    .   ",
           /* line */ (const char *) "    .   ",
           /* line */ (const char *) " ......^",
           /* line */ (const char *) "^.....  ",
           /* line */ (const char *) " .....  ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "    .   ",
           /* line */ (const char *) "    ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^    ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "^......^",
           /* line */ (const char *) " ...... ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "   ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^  ",
           /* line */ (const char *) "    .  ",
           /* line */ (const char *) "    .  ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "    .  ",
           /* line */ (const char *) "    .  ",
           /* line */ (const char *) "    ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^      ",
           /* line */ (const char *) "   .      ",
           /* line */ (const char *) "   .      ",
           /* line */ (const char *) "   ..     ",
           /* line */ (const char *) "^........^",
           /* line */ (const char *) " ......   ",
           /* line */ (const char *) "   ..     ",
           /* line */ (const char *) "   .      ",
           /* line */ (const char *) "   ^      ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^     ",
           /* line */ (const char *) " .....   ",
           /* line */ (const char *) " .|.m.   ",
           /* line */ (const char *) "^.......^",
           /* line */ (const char *) "   ..    ",
           /* line */ (const char *) "    .    ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^        ",
           /* line */ (const char *) "     .......  ",
           /* line */ (const char *) "^...........  ",
           /* line */ (const char *) "     ........^",
           /* line */ (const char *) "        ..    ",
           /* line */ (const char *) "         .    ",
           /* line */ (const char *) "         ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^     ",
           /* line */ (const char *) "    .     ",
           /* line */ (const char *) "    ..    ",
           /* line */ (const char *) "  .......^",
           /* line */ (const char *) "^.......  ",
           /* line */ (const char *) "    ..    ",
           /* line */ (const char *) "     .    ",
           /* line */ (const char *) "     ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^   ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) " ......^",
           /* line */ (const char *) "^...... ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "   ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^  ",
           /* line */ (const char *) "     .  ",
           /* line */ (const char *) "    ..  ",
           /* line */ (const char *) "   .... ",
           /* line */ (const char *) "^......^",
           /* line */ (const char *) "    ..  ",
           /* line */ (const char *) "    .   ",
           /* line */ (const char *) "    ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "       ^    ",
           /* line */ (const char *) "       ..   ",
           /* line */ (const char *) "^..........^",
           /* line */ (const char *) "      ....  ",
           /* line */ (const char *) "       ..   ",
           /* line */ (const char *) "       .    ",
           /* line */ (const char *) "       ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^    ",
           /* line */ (const char *) "    .    ",
           /* line */ (const char *) "    .    ",
           /* line */ (const char *) "   ..... ",
           /* line */ (const char *) "   .M.m.^",
           /* line */ (const char *) "^....... ",
           /* line */ (const char *) "     ..  ",
           /* line */ (const char *) "     ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^   ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "^...... ",
           /* line */ (const char *) " ......^",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "    ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^   ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) " ......^",
           /* line */ (const char *) "^...... ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "    ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^  ",
           /* line */ (const char *) "   .  ",
           /* line */ (const char *) "   .  ",
           /* line */ (const char *) "   .  ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "^....^",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "  .   ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^   ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "^....^",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^      ",
           /* line */ (const char *) "   .      ",
           /* line */ (const char *) "   .      ",
           /* line */ (const char *) "  ..      ",
           /* line */ (const char *) "^....     ",
           /* line */ (const char *) " ........^",
           /* line */ (const char *) "  ..      ",
           /* line */ (const char *) "   .      ",
           /* line */ (const char *) "   ^      ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^    ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "^...... ",
           /* line */ (const char *) " ......^",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "    ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "      ^   ",
           /* line */ (const char *) "      .   ",
           /* line */ (const char *) "     ..   ",
           /* line */ (const char *) "   ...... ",
           /* line */ (const char *) "^........^",
           /* line */ (const char *) "     ..   ",
           /* line */ (const char *) "      ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^   ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "^....^",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^     ",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "    ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^  ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "^....^",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "   ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^  ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) " ....^",
           /* line */ (const char *) "^.... ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "   ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^    ",
           /* line */ (const char *) "     .    ",
           /* line */ (const char *) "^........ ",
           /* line */ (const char *) "  .m..|..^",
           /* line */ (const char *) "  ....... ",
           /* line */ (const char *) "     ..   ",
           /* line */ (const char *) "     ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^   ",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) " .M.x. ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "    ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "       ^    ",
           /* line */ (const char *) "       .    ",
           /* line */ (const char *) "^........   ",
           /* line */ (const char *) "  .........^",
           /* line */ (const char *) "  .......   ",
           /* line */ (const char *) "     ..     ",
           /* line */ (const char *) "     ^      ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^       ",
           /* line */ (const char *) "    .....    ",
           /* line */ (const char *) "^...........^",
           /* line */ (const char *) "    .....    ",
           /* line */ (const char *) "      ..     ",
           /* line */ (const char *) "      ^      ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^     ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^    ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "^......^",
           /* line */ (const char *) " ...... ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "    ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^    ",
           /* line */ (const char *) " .......^",
           /* line */ (const char *) "^....... ",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "     ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^   ",
           /* line */ (const char *) " .......^",
           /* line */ (const char *) "^.|.g.|. ",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "     ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^     ",
           /* line */ (const char *) "    ..    ",
           /* line */ (const char *) "  .......^",
           /* line */ (const char *) "^.......  ",
           /* line */ (const char *) "    ..    ",
           /* line */ (const char *) "    ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "       ^    ",
           /* line */ (const char *) "      ..    ",
           /* line */ (const char *) "     ....   ",
           /* line */ (const char *) "^..........^",
           /* line */ (const char *) "      ..    ",
           /* line */ (const char *) "      .     ",
           /* line */ (const char *) "      ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^   ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "^.... ",
           /* line */ (const char *) " ....^",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^     ",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) " .|.g.^",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "    ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^     ",
           /* line */ (const char *) "    .     ",
           /* line */ (const char *) "    ..    ",
           /* line */ (const char *) "^........^",
           /* line */ (const char *) "  ......  ",
           /* line */ (const char *) "    ..    ",
           /* line */ (const char *) "    ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^      ",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) "^.......^",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "     ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^  ",
           /* line */ (const char *) "     .  ",
           /* line */ (const char *) "     .  ",
           /* line */ (const char *) "     .  ",
           /* line */ (const char *) "    ..  ",
           /* line */ (const char *) "^...... ",
           /* line */ (const char *) "   ....^",
           /* line */ (const char *) "    ..  ",
           /* line */ (const char *) "    ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^   ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "^.... ",
           /* line */ (const char *) " ....^",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^    ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "^...... ",
           /* line */ (const char *) " ......^",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "    ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^   ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) " ......^",
           /* line */ (const char *) "^...... ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "    ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^  ",
           /* line */ (const char *) "    .  ",
           /* line */ (const char *) "    .  ",
           /* line */ (const char *) "    .  ",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) "  ....^",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "    .  ",
           /* line */ (const char *) "    ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^   ",
           /* line */ (const char *) "   .   ",
           /* line */ (const char *) "   .   ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "^.m.m.^",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "    ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^     ",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "    ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^    ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) " ...... ",
           /* line */ (const char *) "^......^",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "    ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^   ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) " ...... ",
           /* line */ (const char *) "^......^",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "   ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^     ",
           /* line */ (const char *) "     .     ",
           /* line */ (const char *) "   ....... ",
           /* line */ (const char *) "^......... ",
           /* line */ (const char *) "   .......^",
           /* line */ (const char *) "      ..   ",
           /* line */ (const char *) "      ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^       ",
           /* line */ (const char *) "  .       ",
           /* line */ (const char *) "  .......^",
           /* line */ (const char *) "  .....   ",
           /* line */ (const char *) "^......   ",
           /* line */ (const char *) "    ..    ",
           /* line */ (const char *) "     ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^   ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) " ...... ",
           /* line */ (const char *) "^......^",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "   ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^    ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) " .g.|. ",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^  ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "^....^",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "   ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^        ",
           /* line */ (const char *) "  .        ",
           /* line */ (const char *) "  .......  ",
           /* line */ (const char *) "  ..m..x.  ",
           /* line */ (const char *) "^.........^",
           /* line */ (const char *) "     ..    ",
           /* line */ (const char *) "     .     ",
           /* line */ (const char *) "     .     ",
           /* line */ (const char *) "     ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^       ",
           /* line */ (const char *) " .......^",
           /* line */ (const char *) "^....... ",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^   ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "^...... ",
           /* line */ (const char *) " ......^",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "    ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^    ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "^...... ",
           /* line */ (const char *) " ......^",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "   ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^  ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) " .g.x. ",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^   ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) " ...... ",
           /* line */ (const char *) "^......^",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "    ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^   ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) " ...... ",
           /* line */ (const char *) "^......^",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "   ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^    ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "^......^",
           /* line */ (const char *) " ...... ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "   ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^       ",
           /* line */ (const char *) "    .......^",
           /* line */ (const char *) "    .|.m.x. ",
           /* line */ (const char *) "^.......... ",
           /* line */ (const char *) "       ..   ",
           /* line */ (const char *) "       ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^   ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) " ....^",
           /* line */ (const char *) "^.... ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^     ",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) " ..g.. ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "      ^   ",
           /* line */ (const char *) "      .   ",
           /* line */ (const char *) "^.......  ",
           /* line */ (const char *) "   .M.g.  ",
           /* line */ (const char *) "   ......^",
           /* line */ (const char *) "     ..   ",
           /* line */ (const char *) "      ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^    ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "^...... ",
           /* line */ (const char *) " ......^",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "   ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^    ",
           /* line */ (const char *) "^....... ",
           /* line */ (const char *) " .x..|.. ",
           /* line */ (const char *) " .......^",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^   ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "^.....^",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "    ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^    ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "^......^",
           /* line */ (const char *) " ...... ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "    ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^   ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "^......^",
           /* line */ (const char *) " ...... ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "    ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^   ",
           /* line */ (const char *) "  .   ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "^.... ",
           /* line */ (const char *) " ....^",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "  .   ",
           /* line */ (const char *) "  .   ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^   ",
           /* line */ (const char *) " .......^",
           /* line */ (const char *) "^..|..m. ",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^    ",
           /* line */ (const char *) "  .    ",
           /* line */ (const char *) "  ..   ",
           /* line */ (const char *) " ....  ",
           /* line */ (const char *) "^.....^",
           /* line */ (const char *) "  ..   ",
           /* line */ (const char *) "  .    ",
           /* line */ (const char *) "  ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^   ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "^....^",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^    ",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) " .G.g. ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^   ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "^.... ",
           /* line */ (const char *) " ....^",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "   ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "         ^  ",
           /* line */ (const char *) "         .  ",
           /* line */ (const char *) "    ....... ",
           /* line */ (const char *) "^..........^",
           /* line */ (const char *) "    ....... ",
           /* line */ (const char *) "       ..   ",
           /* line */ (const char *) "        ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^    ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "^...... ",
           /* line */ (const char *) " ......^",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "    ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^  ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) " ....^",
           /* line */ (const char *) "^.... ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^      ",
           /* line */ (const char *) " .......^",
           /* line */ (const char *) "^..m..|. ",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "     ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^     ",
           /* line */ (const char *) " .....  ",
           /* line */ (const char *) "^.....  ",
           /* line */ (const char *) " ......^",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "   .    ",
           /* line */ (const char *) "   ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^      ",
           /* line */ (const char *) "  .      ",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) " .......^",
           /* line */ (const char *) "^....... ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "     ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^      ",
           /* line */ (const char *) " .......   ",
           /* line */ (const char *) " .x..x....^",
           /* line */ (const char *) "^.......   ",
           /* line */ (const char *) "    ..     ",
           /* line */ (const char *) "     .     ",
           /* line */ (const char *) "     ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^        ",
           /* line */ (const char *) " .        ",
           /* line */ (const char *) " .....    ",
           /* line */ (const char *) " .m.m.    ",
           /* line */ (const char *) "^........^",
           /* line */ (const char *) "   ..     ",
           /* line */ (const char *) "    .     ",
           /* line */ (const char *) "    ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^   ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) " ......^",
           /* line */ (const char *) "^...... ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "   ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^    ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) " ......^",
           /* line */ (const char *) "^...... ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "   ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^   ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) " ...... ",
           /* line */ (const char *) "^......^",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "    ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^   ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " ..|..^",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^    ",
           /* line */ (const char *) "    .    ",
           /* line */ (const char *) "    .    ",
           /* line */ (const char *) "   ..    ",
           /* line */ (const char *) "^......  ",
           /* line */ (const char *) " .......^",
           /* line */ (const char *) "   ..    ",
           /* line */ (const char *) "    .    ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "      ^      ",
           /* line */ (const char *) "      .      ",
           /* line */ (const char *) "      ..     ",
           /* line */ (const char *) "    ......   ",
           /* line */ (const char *) "^...........^",
           /* line */ (const char *) "      ..     ",
           /* line */ (const char *) "       ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^    ",
           /* line */ (const char *) "^.....^",
           /* line */ (const char *) " .m.|. ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "    ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^  ",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^    ",
           /* line */ (const char *) "    .    ",
           /* line */ (const char *) "   ..    ",
           /* line */ (const char *) "  ....   ",
           /* line */ (const char *) "^.......^",
           /* line */ (const char *) "   ..    ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^       ",
           /* line */ (const char *) "  .       ",
           /* line */ (const char *) "  ....... ",
           /* line */ (const char *) "  ....... ",
           /* line */ (const char *) "^........^",
           /* line */ (const char *) "     ..   ",
           /* line */ (const char *) "      ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^      ",
           /* line */ (const char *) " .......^",
           /* line */ (const char *) " .m.x.m. ",
           /* line */ (const char *) "^....... ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^  ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "    ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^          ",
           /* line */ (const char *) "  .......    ",
           /* line */ (const char *) "  ..g..|....^",
           /* line */ (const char *) "^........    ",
           /* line */ (const char *) "     ..      ",
           /* line */ (const char *) "      ^      ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^  ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " .m.g. ",
           /* line */ (const char *) "^.....^",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^     ",
           /* line */ (const char *) "     .     ",
           /* line */ (const char *) "     .     ",
           /* line */ (const char *) "     ..    ",
           /* line */ (const char *) "^.........^",
           /* line */ (const char *) "   ......  ",
           /* line */ (const char *) "     ..    ",
           /* line */ (const char *) "     ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^    ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) " ......^",
           /* line */ (const char *) "^...... ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "   ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^    ",
           /* line */ (const char *) "   .    ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "  ....  ",
           /* line */ (const char *) "^......^",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "    .   ",
           /* line */ (const char *) "    .   ",
           /* line */ (const char *) "    ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^   ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "^...... ",
           /* line */ (const char *) " ......^",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "    ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^    ",
           /* line */ (const char *) "   ..    ",
           /* line */ (const char *) "^......  ",
           /* line */ (const char *) " .......^",
           /* line */ (const char *) "   ..    ",
           /* line */ (const char *) "    .    ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^    ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "^......^",
           /* line */ (const char *) " ...... ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "   ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^   ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "^...... ",
           /* line */ (const char *) " ......^",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "   ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^    ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "^..|..^",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^   ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "^..m.. ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "    ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^    ",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) "^..x..|. ",
           /* line */ (const char *) " .......^",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "     ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^   ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "^.... ",
           /* line */ (const char *) " ....^",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "   ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^     ",
           /* line */ (const char *) "    .     ",
           /* line */ (const char *) "  .....   ",
           /* line */ (const char *) "^......   ",
           /* line */ (const char *) "  .......^",
           /* line */ (const char *) "    ..    ",
           /* line */ (const char *) "     ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^    ",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) " .|.m.g.^",
           /* line */ (const char *) "^....... ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "     ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^     ",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) "^.......^",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^   ",
           /* line */ (const char *) "  .   ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) " ....^",
           /* line */ (const char *) "^.... ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "   .  ",
           /* line */ (const char *) "   .  ",
           /* line */ (const char *) "   .  ",
           /* line */ (const char *) "   ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^  ",
           /* line */ (const char *) "^.....^",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "    ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^    ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "^...... ",
           /* line */ (const char *) " ......^",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "    ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^    ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "^...... ",
           /* line */ (const char *) " ......^",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "    ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^   ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) " ...... ",
           /* line */ (const char *) "^......^",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "   ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^  ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "^....^",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^  ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "^....^",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "   ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^  ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) " ....^",
           /* line */ (const char *) "^.... ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^   ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "  ......^",
           /* line */ (const char *) "^....... ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "     .   ",
           /* line */ (const char *) "     .   ",
           /* line */ (const char *) "     ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^  ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "^....^",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "   ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^    ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) " ......^",
           /* line */ (const char *) "^...... ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "    ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^    ",
           /* line */ (const char *) "  .    ",
           /* line */ (const char *) "  .    ",
           /* line */ (const char *) "  .    ",
           /* line */ (const char *) "  ..   ",
           /* line */ (const char *) "^....  ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) "  ..   ",
           /* line */ (const char *) "   .   ",
           /* line */ (const char *) "   .   ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "        ^  ",
           /* line */ (const char *) "   ....... ",
           /* line */ (const char *) "   .......^",
           /* line */ (const char *) "^......... ",
           /* line */ (const char *) "      ..   ",
           /* line */ (const char *) "       ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "       ^      ",
           /* line */ (const char *) "      ..      ",
           /* line */ (const char *) "    ......    ",
           /* line */ (const char *) "^............^",
           /* line */ (const char *) "      ..      ",
           /* line */ (const char *) "      .       ",
           /* line */ (const char *) "      ^       ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^   ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "^...... ",
           /* line */ (const char *) " ......^",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "   ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^      ",
           /* line */ (const char *) "^.......^",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^   ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "^.....^",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^      ",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) " ..g.x.. ",
           /* line */ (const char *) "^.......^",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "     ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^   ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "^......^",
           /* line */ (const char *) " ...... ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "   ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^    ",
           /* line */ (const char *) "  .    ",
           /* line */ (const char *) "  .    ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) " .|.m. ",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "    ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^    ",
           /* line */ (const char *) "     .    ",
           /* line */ (const char *) "     ..   ",
           /* line */ (const char *) "   ...... ",
           /* line */ (const char *) "^........^",
           /* line */ (const char *) "     ..   ",
           /* line */ (const char *) "      .   ",
           /* line */ (const char *) "      ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^   ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) " ......^",
           /* line */ (const char *) "^...... ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "    ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^   ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "^...... ",
           /* line */ (const char *) " ......^",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "    ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^  ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "^.....^",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "    ^  ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^    ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) " ......^",
           /* line */ (const char *) "^...... ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "    .   ",
           /* line */ (const char *) "    ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^  ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "^....^",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^       ",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) " .......^",
           /* line */ (const char *) "^....... ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^  ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) " ....^",
           /* line */ (const char *) "^.... ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^   ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "^......^",
           /* line */ (const char *) " ...... ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "   ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^     ",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) "^..m..x.^",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "     ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^   ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) " ...... ",
           /* line */ (const char *) "^......^",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "   ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^  ",
           /* line */ (const char *) "     .  ",
           /* line */ (const char *) "     .  ",
           /* line */ (const char *) "  ..... ",
           /* line */ (const char *) "^..g.x.^",
           /* line */ (const char *) "  ..... ",
           /* line */ (const char *) "    ..  ",
           /* line */ (const char *) "    ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^     ",
           /* line */ (const char *) "    .     ",
           /* line */ (const char *) " ........^",
           /* line */ (const char *) " .......  ",
           /* line */ (const char *) "^.......  ",
           /* line */ (const char *) "    ..    ",
           /* line */ (const char *) "    ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^    ",
           /* line */ (const char *) "     .    ",
           /* line */ (const char *) "^......   ",
           /* line */ (const char *) "  .......^",
           /* line */ (const char *) "  .....   ",
           /* line */ (const char *) "    ..    ",
           /* line */ (const char *) "     .    ",
           /* line */ (const char *) "     .    ",
           /* line */ (const char *) "     ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^   ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) " ...... ",
           /* line */ (const char *) "^......^",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "   ^    ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^  ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "^.... ",
           /* line */ (const char *) " ....^",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^    ",
           /* line */ (const char *) "    .    ",
           /* line */ (const char *) "   ..    ",
           /* line */ (const char *) "^.....   ",
           /* line */ (const char *) "  ......^",
           /* line */ (const char *) "   ..    ",
           /* line */ (const char *) "   .     ",
           /* line */ (const char *) "   .     ",
           /* line */ (const char *) "   .     ",
           /* line */ (const char *) "   ^     ",
           /* end */ nullptr);

  room_add(g, CHANCE_NORMAL, NO_FLAGS, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^      ",
           /* line */ (const char *) "   ..     ",
           /* line */ (const char *) "  .......^",
           /* line */ (const char *) "^.....    ",
           /* line */ (const char *) "   ..     ",
           /* line */ (const char *) "   ^      ",
           /* end */ nullptr);

}
