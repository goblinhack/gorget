//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_charmap.hpp"
#include "my_level.hpp"

//
// Rooms of type 'cross_sym'
//
void rooms_cross_sym(Gamep g)
{
  TRACE_NO_INDENT();

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^    ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) " ......^",
           /* line */ (const char *) "^...... ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "   ^    ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^       ",
           /* line */ (const char *) "^....... ",
           /* line */ (const char *) " .......^",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^   ",
           /* line */ (const char *) "^....... ",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) " .......^",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^      ",
           /* line */ (const char *) "    .      ",
           /* line */ (const char *) "    ..     ",
           /* line */ (const char *) "  ......   ",
           /* line */ (const char *) "^.........^",
           /* line */ (const char *) "    ..     ",
           /* line */ (const char *) "    .      ",
           /* line */ (const char *) "    ^      ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^  ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "^.... ",
           /* line */ (const char *) " ....^",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "      ^     ",
           /* line */ (const char *) "      .     ",
           /* line */ (const char *) "   .....    ",
           /* line */ (const char *) "   ........^",
           /* line */ (const char *) "^.......    ",
           /* line */ (const char *) "     ..     ",
           /* line */ (const char *) "      .     ",
           /* line */ (const char *) "      ^     ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^    ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) " ...... ",
           /* line */ (const char *) "^......^",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "    ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^   ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "^.....  ",
           /* line */ (const char *) "  .....^",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "    .   ",
           /* line */ (const char *) "    .   ",
           /* line */ (const char *) "    ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^   ",
           /* line */ (const char *) "    .   ",
           /* line */ (const char *) "    .   ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "  .....^",
           /* line */ (const char *) "^.....  ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "    ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^     ",
           /* line */ (const char *) "^.....^",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^   ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "^.... ",
           /* line */ (const char *) " ....^",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "   ^  ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^    ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "^...... ",
           /* line */ (const char *) " ......^",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "    ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^   ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) " ...... ",
           /* line */ (const char *) "^......^",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "   ^    ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^  ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "    ^  ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^   ",
           /* line */ (const char *) "     .   ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "   ....  ",
           /* line */ (const char *) "^.......^",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "     .   ",
           /* line */ (const char *) "     ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^     ",
           /* line */ (const char *) "^...... ",
           /* line */ (const char *) "  ..... ",
           /* line */ (const char *) "  .....^",
           /* line */ (const char *) "    ..  ",
           /* line */ (const char *) "     .  ",
           /* line */ (const char *) "     .  ",
           /* line */ (const char *) "     ^  ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^   ",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) " .......^",
           /* line */ (const char *) "^....... ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "     ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^   ",
           /* line */ (const char *) "     .   ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "^.......^",
           /* line */ (const char *) "   ....  ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "    .    ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^    ",
           /* line */ (const char *) "     .    ",
           /* line */ (const char *) "     .    ",
           /* line */ (const char *) "^.......  ",
           /* line */ (const char *) "   ......^",
           /* line */ (const char *) "   .....  ",
           /* line */ (const char *) "     ..   ",
           /* line */ (const char *) "     ^    ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^    ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "    ^  ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^      ",
           /* line */ (const char *) "  .      ",
           /* line */ (const char *) "  .....  ",
           /* line */ (const char *) "^.......^",
           /* line */ (const char *) "  .....  ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "     .   ",
           /* line */ (const char *) "     ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^   ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) " ....^",
           /* line */ (const char *) "^.... ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^   ",
           /* line */ (const char *) "     .   ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "^.......^",
           /* line */ (const char *) "  ...... ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "      ^  ",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) "^.......^",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "       ^     ",
           /* line */ (const char *) "       .     ",
           /* line */ (const char *) "  ..........^",
           /* line */ (const char *) "^........    ",
           /* line */ (const char *) "  .......    ",
           /* line */ (const char *) "     ..      ",
           /* line */ (const char *) "     .       ",
           /* line */ (const char *) "     ^       ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^    ",
           /* line */ (const char *) "   .    ",
           /* line */ (const char *) "   .    ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "  ....  ",
           /* line */ (const char *) "^......^",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "    .   ",
           /* line */ (const char *) "    ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^   ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "^......^",
           /* line */ (const char *) " ...... ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "   ^    ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^     ",
           /* line */ (const char *) "  ....... ",
           /* line */ (const char *) "^........ ",
           /* line */ (const char *) "  .......^",
           /* line */ (const char *) "     ..   ",
           /* line */ (const char *) "     ^    ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^   ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "      ^  ",
           /* line */ (const char *) "      .  ",
           /* line */ (const char *) "     ..  ",
           /* line */ (const char *) "^.......^",
           /* line */ (const char *) "    .... ",
           /* line */ (const char *) "     ..  ",
           /* line */ (const char *) "      .  ",
           /* line */ (const char *) "      ^  ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^   ",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "^.....^",
           /* line */ (const char *) "  .... ",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "    ^  ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^    ",
           /* line */ (const char *) "^.......^",
           /* line */ (const char *) "  .....  ",
           /* line */ (const char *) "  .....  ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "     .   ",
           /* line */ (const char *) "     .   ",
           /* line */ (const char *) "     ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^    ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "^...... ",
           /* line */ (const char *) " ......^",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "    ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^  ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) " ....^",
           /* line */ (const char *) "^.... ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^      ",
           /* line */ (const char *) "   ..      ",
           /* line */ (const char *) " .........^",
           /* line */ (const char *) "^......    ",
           /* line */ (const char *) "   ..      ",
           /* line */ (const char *) "    .      ",
           /* line */ (const char *) "    ^      ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^     ",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^    ",
           /* line */ (const char *) "    .    ",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) "^.......^",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "        ^   ",
           /* line */ (const char *) "^..........^",
           /* line */ (const char *) "   .......  ",
           /* line */ (const char *) "   .......  ",
           /* line */ (const char *) "      ..    ",
           /* line */ (const char *) "      ^     ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^   ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "^......^",
           /* line */ (const char *) " ...... ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "    ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^       ",
           /* line */ (const char *) " .......^",
           /* line */ (const char *) "^....... ",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "     ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^     ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^  ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "^....^",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^      ",
           /* line */ (const char *) "     .      ",
           /* line */ (const char *) "^.........  ",
           /* line */ (const char *) "   ........^",
           /* line */ (const char *) "   .......  ",
           /* line */ (const char *) "      ..    ",
           /* line */ (const char *) "      .     ",
           /* line */ (const char *) "      ^     ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^    ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^       ",
           /* line */ (const char *) " .       ",
           /* line */ (const char *) " .       ",
           /* line */ (const char *) " .....   ",
           /* line */ (const char *) "^.....   ",
           /* line */ (const char *) " .......^",
           /* line */ (const char *) "   ..    ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^    ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "^...... ",
           /* line */ (const char *) " ......^",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "   ^    ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^   ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) " ......^",
           /* line */ (const char *) "^...... ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "    ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^       ",
           /* line */ (const char *) "    .       ",
           /* line */ (const char *) "    .       ",
           /* line */ (const char *) "  .......   ",
           /* line */ (const char *) "  .........^",
           /* line */ (const char *) "^........   ",
           /* line */ (const char *) "     ..     ",
           /* line */ (const char *) "     ^      ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^    ",
           /* line */ (const char *) "^...... ",
           /* line */ (const char *) "  ..... ",
           /* line */ (const char *) "  .....^",
           /* line */ (const char *) "    ..  ",
           /* line */ (const char *) "     .  ",
           /* line */ (const char *) "     .  ",
           /* line */ (const char *) "     .  ",
           /* line */ (const char *) "     ^  ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "      ^    ",
           /* line */ (const char *) " .......   ",
           /* line */ (const char *) " .........^",
           /* line */ (const char *) "^.......   ",
           /* line */ (const char *) "    ..     ",
           /* line */ (const char *) "    ^      ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^    ",
           /* line */ (const char *) " .......^",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) "^....... ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^        ",
           /* line */ (const char *) "  .......  ",
           /* line */ (const char *) "  .......  ",
           /* line */ (const char *) "^.........^",
           /* line */ (const char *) "     ..    ",
           /* line */ (const char *) "     .     ",
           /* line */ (const char *) "     ^     ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^   ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "^......^",
           /* line */ (const char *) " ...... ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "   ^    ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^   ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "^....^",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^   ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "^....^",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^       ",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) "^....... ",
           /* line */ (const char *) " .......^",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^  ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "^.... ",
           /* line */ (const char *) " ....^",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^       ",
           /* line */ (const char *) "^........ ",
           /* line */ (const char *) "  .......^",
           /* line */ (const char *) "  ....... ",
           /* line */ (const char *) "     ..   ",
           /* line */ (const char *) "      .   ",
           /* line */ (const char *) "      ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^     ",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "    ^  ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^   ",
           /* line */ (const char *) " .......^",
           /* line */ (const char *) "^....... ",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "     ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^  ",
           /* line */ (const char *) "^.....^",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^   ",
           /* line */ (const char *) "    ..  ",
           /* line */ (const char *) "^...... ",
           /* line */ (const char *) "   ....^",
           /* line */ (const char *) "    ..  ",
           /* line */ (const char *) "     ^  ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^    ",
           /* line */ (const char *) "  .    ",
           /* line */ (const char *) "  .    ",
           /* line */ (const char *) "  ..   ",
           /* line */ (const char *) "^.....^",
           /* line */ (const char *) " ....  ",
           /* line */ (const char *) "  ..   ",
           /* line */ (const char *) "   .   ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^   ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "    ^  ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "       ^   ",
           /* line */ (const char *) "       .   ",
           /* line */ (const char *) "    .....  ",
           /* line */ (const char *) "^........  ",
           /* line */ (const char *) "    ......^",
           /* line */ (const char *) "      ..   ",
           /* line */ (const char *) "       .   ",
           /* line */ (const char *) "       ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^   ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) " ....^",
           /* line */ (const char *) "^.... ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^   ",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "    ^  ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^    ",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) "^....... ",
           /* line */ (const char *) " .......^",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "     ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^   ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) " ......^",
           /* line */ (const char *) "^...... ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "    ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^   ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "^...... ",
           /* line */ (const char *) " ......^",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "    ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^    ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "^......^",
           /* line */ (const char *) " ...... ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "    ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^   ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "^...... ",
           /* line */ (const char *) " ......^",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "    ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^    ",
           /* line */ (const char *) "    .    ",
           /* line */ (const char *) "    .    ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "^.......^",
           /* line */ (const char *) "  ...... ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^  ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "^.... ",
           /* line */ (const char *) " ....^",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "   ^  ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^    ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "^...... ",
           /* line */ (const char *) " ......^",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "   ^    ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^     ",
           /* line */ (const char *) "   .....  ",
           /* line */ (const char *) "   ......^",
           /* line */ (const char *) "^.......  ",
           /* line */ (const char *) "     ..   ",
           /* line */ (const char *) "      .   ",
           /* line */ (const char *) "      ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^       ",
           /* line */ (const char *) "    .       ",
           /* line */ (const char *) "^........   ",
           /* line */ (const char *) "  .......   ",
           /* line */ (const char *) "  .........^",
           /* line */ (const char *) "     ..     ",
           /* line */ (const char *) "      ^     ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^     ",
           /* line */ (const char *) "  .......^",
           /* line */ (const char *) "  ....... ",
           /* line */ (const char *) "^........ ",
           /* line */ (const char *) "     ..   ",
           /* line */ (const char *) "      .   ",
           /* line */ (const char *) "      ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^   ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) " ...... ",
           /* line */ (const char *) "^......^",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "   ^    ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^    ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "^...... ",
           /* line */ (const char *) " ......^",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "   ^    ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^   ",
           /* line */ (const char *) "     .   ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "^.......^",
           /* line */ (const char *) "  ...... ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "      ^  ",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) "^....... ",
           /* line */ (const char *) " .......^",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "     ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^    ",
           /* line */ (const char *) "    .    ",
           /* line */ (const char *) "   ..    ",
           /* line */ (const char *) "^.....   ",
           /* line */ (const char *) "  ......^",
           /* line */ (const char *) "   ..    ",
           /* line */ (const char *) "    .    ",
           /* line */ (const char *) "    .    ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "       ^   ",
           /* line */ (const char *) "       .   ",
           /* line */ (const char *) "       .   ",
           /* line */ (const char *) "      ..   ",
           /* line */ (const char *) "    ......^",
           /* line */ (const char *) "^......... ",
           /* line */ (const char *) "      ..   ",
           /* line */ (const char *) "      ^    ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^  ",
           /* line */ (const char *) "     .  ",
           /* line */ (const char *) "    ..  ",
           /* line */ (const char *) "^......^",
           /* line */ (const char *) "   .... ",
           /* line */ (const char *) "    ..  ",
           /* line */ (const char *) "    .   ",
           /* line */ (const char *) "    ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^  ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "^.... ",
           /* line */ (const char *) " ....^",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "      ^     ",
           /* line */ (const char *) "     ..     ",
           /* line */ (const char *) "   ......   ",
           /* line */ (const char *) "^..........^",
           /* line */ (const char *) "     ..     ",
           /* line */ (const char *) "      ^     ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^   ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) " ...... ",
           /* line */ (const char *) "^......^",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "    ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^       ",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) "^.......^",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "     ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "      ^      ",
           /* line */ (const char *) "   .........^",
           /* line */ (const char *) "   .......   ",
           /* line */ (const char *) "^.........   ",
           /* line */ (const char *) "      ..     ",
           /* line */ (const char *) "       .     ",
           /* line */ (const char *) "       .     ",
           /* line */ (const char *) "       ^     ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^      ",
           /* line */ (const char *) "  .....   ",
           /* line */ (const char *) "  .......^",
           /* line */ (const char *) "^......   ",
           /* line */ (const char *) "    ..    ",
           /* line */ (const char *) "     .    ",
           /* line */ (const char *) "     ^    ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "       ^    ",
           /* line */ (const char *) "      ..    ",
           /* line */ (const char *) "    ......  ",
           /* line */ (const char *) "^..........^",
           /* line */ (const char *) "      ..    ",
           /* line */ (const char *) "      .     ",
           /* line */ (const char *) "      .     ",
           /* line */ (const char *) "      ^     ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^    ",
           /* line */ (const char *) "  .    ",
           /* line */ (const char *) "  .    ",
           /* line */ (const char *) "  ..   ",
           /* line */ (const char *) " ....  ",
           /* line */ (const char *) "^.....^",
           /* line */ (const char *) "  ..   ",
           /* line */ (const char *) "  .    ",
           /* line */ (const char *) "  ^    ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^         ",
           /* line */ (const char *) "  .......   ",
           /* line */ (const char *) "^........   ",
           /* line */ (const char *) "  .........^",
           /* line */ (const char *) "     ..     ",
           /* line */ (const char *) "     ^      ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^    ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "^...... ",
           /* line */ (const char *) " ......^",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "    ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^  ",
           /* line */ (const char *) "  .....^",
           /* line */ (const char *) "  ..... ",
           /* line */ (const char *) "^...... ",
           /* line */ (const char *) "    ..  ",
           /* line */ (const char *) "     .  ",
           /* line */ (const char *) "     ^  ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^     ",
           /* line */ (const char *) "   .     ",
           /* line */ (const char *) "   .     ",
           /* line */ (const char *) "  .....  ",
           /* line */ (const char *) "^.......^",
           /* line */ (const char *) "  .....  ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "    .    ",
           /* line */ (const char *) "    .    ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^    ",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^    ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) " ...... ",
           /* line */ (const char *) "^......^",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "    ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^   ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "^....^",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^     ",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) " .......^",
           /* line */ (const char *) "^....... ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "     ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^   ",
           /* line */ (const char *) "    .   ",
           /* line */ (const char *) "    .   ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "^......^",
           /* line */ (const char *) "  ....  ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "   ^    ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^     ",
           /* line */ (const char *) " .......^",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) "^....... ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "     ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^    ",
           /* line */ (const char *) "  .....  ",
           /* line */ (const char *) "^.......^",
           /* line */ (const char *) "  .....  ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "       ^    ",
           /* line */ (const char *) "       .    ",
           /* line */ (const char *) "       .    ",
           /* line */ (const char *) "       .    ",
           /* line */ (const char *) "      ..    ",
           /* line */ (const char *) "    ......  ",
           /* line */ (const char *) "^..........^",
           /* line */ (const char *) "      ..    ",
           /* line */ (const char *) "       ^    ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^   ",
           /* line */ (const char *) "   .   ",
           /* line */ (const char *) "   .   ",
           /* line */ (const char *) "   .   ",
           /* line */ (const char *) "  ..   ",
           /* line */ (const char *) "^....  ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) "  ..   ",
           /* line */ (const char *) "  ^    ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^      ",
           /* line */ (const char *) "^....... ",
           /* line */ (const char *) " .......^",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "     ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^    ",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) "^.......^",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^   ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) " ......^",
           /* line */ (const char *) "^...... ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "   ^    ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^    ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "^......^",
           /* line */ (const char *) " ...... ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "    ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^   ",
           /* line */ (const char *) "   .   ",
           /* line */ (const char *) "   .   ",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "  .... ",
           /* line */ (const char *) "^.....^",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "   .   ",
           /* line */ (const char *) "   .   ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^   ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) " ....^",
           /* line */ (const char *) "^.... ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^   ",
           /* line */ (const char *) "     .   ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "^......  ",
           /* line */ (const char *) "   .....^",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "     ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^      ",
           /* line */ (const char *) "    .....  ",
           /* line */ (const char *) "^........  ",
           /* line */ (const char *) "    ......^",
           /* line */ (const char *) "      ..   ",
           /* line */ (const char *) "       ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^     ",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "    ^  ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "      ^     ",
           /* line */ (const char *) "     ..     ",
           /* line */ (const char *) "   ......   ",
           /* line */ (const char *) "^..........^",
           /* line */ (const char *) "     ..     ",
           /* line */ (const char *) "     .      ",
           /* line */ (const char *) "     ^      ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^    ",
           /* line */ (const char *) "^.......^",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "      ^    ",
           /* line */ (const char *) "      .    ",
           /* line */ (const char *) "     ..    ",
           /* line */ (const char *) "^.......   ",
           /* line */ (const char *) "    ......^",
           /* line */ (const char *) "     ..    ",
           /* line */ (const char *) "     .     ",
           /* line */ (const char *) "     ^     ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^       ",
           /* line */ (const char *) " ........^",
           /* line */ (const char *) "^.......  ",
           /* line */ (const char *) " .......  ",
           /* line */ (const char *) "    ..    ",
           /* line */ (const char *) "    ^     ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^       ",
           /* line */ (const char *) "^....... ",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) " .......^",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^     ",
           /* line */ (const char *) "     .     ",
           /* line */ (const char *) "^........  ",
           /* line */ (const char *) "  ........^",
           /* line */ (const char *) "  .......  ",
           /* line */ (const char *) "     ..    ",
           /* line */ (const char *) "      .    ",
           /* line */ (const char *) "      ^    ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^   ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) " ......^",
           /* line */ (const char *) "^...... ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "    ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^   ",
           /* line */ (const char *) "  .   ",
           /* line */ (const char *) "  .   ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "^....^",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "  .   ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^   ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "^......^",
           /* line */ (const char *) " ...... ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "   ^    ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^    ",
           /* line */ (const char *) "^.....^",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^       ",
           /* line */ (const char *) "  .......   ",
           /* line */ (const char *) "  .........^",
           /* line */ (const char *) "^........   ",
           /* line */ (const char *) "     ..     ",
           /* line */ (const char *) "      .     ",
           /* line */ (const char *) "      .     ",
           /* line */ (const char *) "      ^     ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^   ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "^.... ",
           /* line */ (const char *) " ....^",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^  ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "^....^",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "   ^  ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^  ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "^.... ",
           /* line */ (const char *) " ....^",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^      ",
           /* line */ (const char *) "    ..     ",
           /* line */ (const char *) "^.........^",
           /* line */ (const char *) "  ......   ",
           /* line */ (const char *) "    ..     ",
           /* line */ (const char *) "     ^     ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^           ",
           /* line */ (const char *) " .           ",
           /* line */ (const char *) " .           ",
           /* line */ (const char *) " ...........^",
           /* line */ (const char *) "^.......     ",
           /* line */ (const char *) " .......     ",
           /* line */ (const char *) "    ..       ",
           /* line */ (const char *) "     ^       ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^    ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "    ^  ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^    ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "^...... ",
           /* line */ (const char *) " ......^",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "    ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^    ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^  ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "^....^",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "   ^  ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^       ",
           /* line */ (const char *) "    .       ",
           /* line */ (const char *) "    ..      ",
           /* line */ (const char *) "^..........^",
           /* line */ (const char *) "  ......    ",
           /* line */ (const char *) "    ..      ",
           /* line */ (const char *) "    .       ",
           /* line */ (const char *) "    ^       ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^  ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "    ^  ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^    ",
           /* line */ (const char *) "   .    ",
           /* line */ (const char *) "  ..    ",
           /* line */ (const char *) "^......^",
           /* line */ (const char *) " ....   ",
           /* line */ (const char *) "  ..    ",
           /* line */ (const char *) "   ^    ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "      ^  ",
           /* line */ (const char *) " .......^",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) "^....... ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^    ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "^......^",
           /* line */ (const char *) " ...... ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "    ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^  ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) " ....^",
           /* line */ (const char *) "^.... ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "   ^  ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^   ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "^....^",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "   ^  ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^   ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) " ....^",
           /* line */ (const char *) "^.... ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^    ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) " ......^",
           /* line */ (const char *) "^...... ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "   ^    ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^    ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^  ",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "    .  ",
           /* line */ (const char *) "    .  ",
           /* line */ (const char *) "    ^  ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^   ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) " ....^",
           /* line */ (const char *) "^.... ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^  ",
           /* line */ (const char *) "  ..... ",
           /* line */ (const char *) "  .....^",
           /* line */ (const char *) "^...... ",
           /* line */ (const char *) "    ..  ",
           /* line */ (const char *) "     .  ",
           /* line */ (const char *) "     .  ",
           /* line */ (const char *) "     ^  ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^    ",
           /* line */ (const char *) "  .    ",
           /* line */ (const char *) "  .    ",
           /* line */ (const char *) "  .    ",
           /* line */ (const char *) "  ..   ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) "^....  ",
           /* line */ (const char *) "  ..   ",
           /* line */ (const char *) "  .    ",
           /* line */ (const char *) "  ^    ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^    ",
           /* line */ (const char *) "    ..    ",
           /* line */ (const char *) "  ......  ",
           /* line */ (const char *) "^........^",
           /* line */ (const char *) "    ..    ",
           /* line */ (const char *) "    .     ",
           /* line */ (const char *) "    .     ",
           /* line */ (const char *) "    ^     ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^   ",
           /* line */ (const char *) "    ..  ",
           /* line */ (const char *) "   .... ",
           /* line */ (const char *) "^......^",
           /* line */ (const char *) "    ..  ",
           /* line */ (const char *) "     .  ",
           /* line */ (const char *) "     .  ",
           /* line */ (const char *) "     ^  ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^    ",
           /* line */ (const char *) "     .    ",
           /* line */ (const char *) "     .    ",
           /* line */ (const char *) "     .    ",
           /* line */ (const char *) "    ..    ",
           /* line */ (const char *) "^........^",
           /* line */ (const char *) "  ......  ",
           /* line */ (const char *) "    ..    ",
           /* line */ (const char *) "    .     ",
           /* line */ (const char *) "    .     ",
           /* line */ (const char *) "    ^     ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^   ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "  .....^",
           /* line */ (const char *) "^.....  ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "    .   ",
           /* line */ (const char *) "    .   ",
           /* line */ (const char *) "    .   ",
           /* line */ (const char *) "    ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^   ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) " ......^",
           /* line */ (const char *) "^...... ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "   ^    ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "        ^     ",
           /* line */ (const char *) "        .     ",
           /* line */ (const char *) "    .........^",
           /* line */ (const char *) "^..........   ",
           /* line */ (const char *) "    .......   ",
           /* line */ (const char *) "       ..     ",
           /* line */ (const char *) "        ^     ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^    ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) " ...... ",
           /* line */ (const char *) "^......^",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "    ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^   ",
           /* line */ (const char *) "     .   ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "   ....  ",
           /* line */ (const char *) "^.......^",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "    .    ",
           /* line */ (const char *) "    .    ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^   ",
           /* line */ (const char *) "    .   ",
           /* line */ (const char *) "  ..... ",
           /* line */ (const char *) "^......^",
           /* line */ (const char *) "  ..... ",
           /* line */ (const char *) "    ..  ",
           /* line */ (const char *) "    .   ",
           /* line */ (const char *) "    .   ",
           /* line */ (const char *) "    ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "      ^     ",
           /* line */ (const char *) "      .     ",
           /* line */ (const char *) "^........   ",
           /* line */ (const char *) "  .........^",
           /* line */ (const char *) "  .......   ",
           /* line */ (const char *) "     ..     ",
           /* line */ (const char *) "      ^     ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^       ",
           /* line */ (const char *) "  .       ",
           /* line */ (const char *) "^.......  ",
           /* line */ (const char *) " .......  ",
           /* line */ (const char *) " ........^",
           /* line */ (const char *) "    ..    ",
           /* line */ (const char *) "    .     ",
           /* line */ (const char *) "    ^     ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^    ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "^...... ",
           /* line */ (const char *) " ......^",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "    ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^  ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "^....^",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^    ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "^.....^",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^   ",
           /* line */ (const char *) "     .   ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "^.......^",
           /* line */ (const char *) "  ...... ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "    .    ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^     ",
           /* line */ (const char *) "   ..    ",
           /* line */ (const char *) "  ......^",
           /* line */ (const char *) "^.....   ",
           /* line */ (const char *) "   ..    ",
           /* line */ (const char *) "   .     ",
           /* line */ (const char *) "   .     ",
           /* line */ (const char *) "   ^     ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^     ",
           /* line */ (const char *) " .     ",
           /* line */ (const char *) "^.....^",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "   .   ",
           /* line */ (const char *) "   .   ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "      ^       ",
           /* line */ (const char *) "^.........    ",
           /* line */ (const char *) "   ..........^",
           /* line */ (const char *) "   .......    ",
           /* line */ (const char *) "      ..      ",
           /* line */ (const char *) "      ^       ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^   ",
           /* line */ (const char *) "   .   ",
           /* line */ (const char *) "   .   ",
           /* line */ (const char *) "  ..   ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) "^....  ",
           /* line */ (const char *) "  ..   ",
           /* line */ (const char *) "   .   ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^     ",
           /* line */ (const char *) " .....    ",
           /* line */ (const char *) " .....    ",
           /* line */ (const char *) "^........^",
           /* line */ (const char *) "   ..     ",
           /* line */ (const char *) "   ^      ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^  ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "^.....^",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^    ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "^...... ",
           /* line */ (const char *) " ......^",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "   .    ",
           /* line */ (const char *) "   .    ",
           /* line */ (const char *) "   .    ",
           /* line */ (const char *) "   ^    ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^   ",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "^.....^",
           /* line */ (const char *) "  .... ",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^   ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "^....^",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^    ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "^...... ",
           /* line */ (const char *) " ......^",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "    ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^   ",
           /* line */ (const char *) "^.....^",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "    ^  ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "      ^  ",
           /* line */ (const char *) " .......^",
           /* line */ (const char *) "^....... ",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "     ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^   ",
           /* line */ (const char *) " .......^",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) "^....... ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^   ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "  ...... ",
           /* line */ (const char *) "^.......^",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "     ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "       ^   ",
           /* line */ (const char *) "       .   ",
           /* line */ (const char *) "   ....... ",
           /* line */ (const char *) "   .......^",
           /* line */ (const char *) "^......... ",
           /* line */ (const char *) "      ..   ",
           /* line */ (const char *) "      ^    ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^      ",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) "^.......^",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^      ",
           /* line */ (const char *) "  .      ",
           /* line */ (const char *) "  .      ",
           /* line */ (const char *) "^.......^",
           /* line */ (const char *) "  .....  ",
           /* line */ (const char *) "  .....  ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "     .   ",
           /* line */ (const char *) "     ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^    ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) " ...... ",
           /* line */ (const char *) "^......^",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "   .    ",
           /* line */ (const char *) "   ^    ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^         ",
           /* line */ (const char *) "   ..        ",
           /* line */ (const char *) "^......      ",
           /* line */ (const char *) " ...........^",
           /* line */ (const char *) "   ..        ",
           /* line */ (const char *) "    ^        ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^   ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "^....^",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "   ^  ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "      ^  ",
           /* line */ (const char *) "^....... ",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) " .......^",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "     ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^    ",
           /* line */ (const char *) "    .    ",
           /* line */ (const char *) "  ......^",
           /* line */ (const char *) "^......  ",
           /* line */ (const char *) "  .....  ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "     .   ",
           /* line */ (const char *) "     .   ",
           /* line */ (const char *) "     .   ",
           /* line */ (const char *) "     ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "        ^  ",
           /* line */ (const char *) "        .  ",
           /* line */ (const char *) "        .  ",
           /* line */ (const char *) "     .....^",
           /* line */ (const char *) "     ..... ",
           /* line */ (const char *) "^......... ",
           /* line */ (const char *) "       ..  ",
           /* line */ (const char *) "       .   ",
           /* line */ (const char *) "       .   ",
           /* line */ (const char *) "       ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^   ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "^.... ",
           /* line */ (const char *) " ....^",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "   ^  ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^   ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) " ......^",
           /* line */ (const char *) "^...... ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "   ^    ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "      ^     ",
           /* line */ (const char *) "     ..     ",
           /* line */ (const char *) "^........   ",
           /* line */ (const char *) "   ........^",
           /* line */ (const char *) "     ..     ",
           /* line */ (const char *) "      .     ",
           /* line */ (const char *) "      ^     ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^    ",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) "^.......^",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^     ",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^      ",
           /* line */ (const char *) "^.......^",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^  ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "^....^",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^    ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "^......^",
           /* line */ (const char *) " ...... ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "    ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^    ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "^...... ",
           /* line */ (const char *) " ......^",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "    ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^       ",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) " .......^",
           /* line */ (const char *) "^....... ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "     ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^  ",
           /* line */ (const char *) "    .  ",
           /* line */ (const char *) "    .  ",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "  .... ",
           /* line */ (const char *) "^.....^",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "   .   ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^  ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) " ....^",
           /* line */ (const char *) "^.... ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "   ^  ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^        ",
           /* line */ (const char *) "   .        ",
           /* line */ (const char *) "  .........^",
           /* line */ (const char *) "  .......   ",
           /* line */ (const char *) "^........   ",
           /* line */ (const char *) "     ..     ",
           /* line */ (const char *) "      ^     ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^     ",
           /* line */ (const char *) "  .     ",
           /* line */ (const char *) "^.....  ",
           /* line */ (const char *) " .....  ",
           /* line */ (const char *) " ......^",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "   ^    ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^  ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "^.... ",
           /* line */ (const char *) " ....^",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^    ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "    ^  ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^     ",
           /* line */ (const char *) "  .     ",
           /* line */ (const char *) "^...... ",
           /* line */ (const char *) "  ..... ",
           /* line */ (const char *) "  .....^",
           /* line */ (const char *) "    ..  ",
           /* line */ (const char *) "     ^  ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^    ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) " ......^",
           /* line */ (const char *) "^...... ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "   ^    ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^     ",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "    ^  ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^   ",
           /* line */ (const char *) "^....... ",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) " .......^",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^  ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "^....^",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "      ^   ",
           /* line */ (const char *) "      .   ",
           /* line */ (const char *) "     ..   ",
           /* line */ (const char *) "    ....  ",
           /* line */ (const char *) "^........^",
           /* line */ (const char *) "     ..   ",
           /* line */ (const char *) "      .   ",
           /* line */ (const char *) "      ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^   ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) " ....^",
           /* line */ (const char *) "^.... ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^  ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "^....^",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "   ^  ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^       ",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) "^....... ",
           /* line */ (const char *) " .......^",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "     ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^     ",
           /* line */ (const char *) "  ..     ",
           /* line */ (const char *) "^.......^",
           /* line */ (const char *) " ....    ",
           /* line */ (const char *) "  ..     ",
           /* line */ (const char *) "   ^     ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^   ",
           /* line */ (const char *) "^.....^",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^      ",
           /* line */ (const char *) "  .      ",
           /* line */ (const char *) "  .      ",
           /* line */ (const char *) "  .      ",
           /* line */ (const char *) "  ..     ",
           /* line */ (const char *) "^....    ",
           /* line */ (const char *) " .......^",
           /* line */ (const char *) "  ..     ",
           /* line */ (const char *) "   .     ",
           /* line */ (const char *) "   ^     ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "      ^    ",
           /* line */ (const char *) "      ..   ",
           /* line */ (const char *) "^......... ",
           /* line */ (const char *) "    ......^",
           /* line */ (const char *) "      ..   ",
           /* line */ (const char *) "      .    ",
           /* line */ (const char *) "      ^    ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^        ",
           /* line */ (const char *) "^.........   ",
           /* line */ (const char *) "   .........^",
           /* line */ (const char *) "   .......   ",
           /* line */ (const char *) "      ..     ",
           /* line */ (const char *) "      ^      ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^    ",
           /* line */ (const char *) "    .    ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "^....... ",
           /* line */ (const char *) "  ......^",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "     ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^       ",
           /* line */ (const char *) "     .       ",
           /* line */ (const char *) "^.........   ",
           /* line */ (const char *) "   .........^",
           /* line */ (const char *) "   .......   ",
           /* line */ (const char *) "      ..     ",
           /* line */ (const char *) "      ^      ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^       ",
           /* line */ (const char *) " .......^",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) "^....... ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^     ",
           /* line */ (const char *) "    .     ",
           /* line */ (const char *) "    ..    ",
           /* line */ (const char *) "^......   ",
           /* line */ (const char *) "   ......^",
           /* line */ (const char *) "    ..    ",
           /* line */ (const char *) "    .     ",
           /* line */ (const char *) "    ^     ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^    ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "^.....^",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "    ^  ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^    ",
           /* line */ (const char *) "     .    ",
           /* line */ (const char *) "    ..    ",
           /* line */ (const char *) "  ......  ",
           /* line */ (const char *) "^........^",
           /* line */ (const char *) "    ..    ",
           /* line */ (const char *) "    ^     ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "       ^  ",
           /* line */ (const char *) "       .  ",
           /* line */ (const char *) "       .  ",
           /* line */ (const char *) "    .....^",
           /* line */ (const char *) "^........ ",
           /* line */ (const char *) "    ..... ",
           /* line */ (const char *) "      ..  ",
           /* line */ (const char *) "       ^  ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^    ",
           /* line */ (const char *) "   .    ",
           /* line */ (const char *) "   .    ",
           /* line */ (const char *) "  .....^",
           /* line */ (const char *) "^...... ",
           /* line */ (const char *) "  ..... ",
           /* line */ (const char *) "    ..  ",
           /* line */ (const char *) "    .   ",
           /* line */ (const char *) "    ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^   ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "^....^",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^   ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "^....^",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "   ^  ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^     ",
           /* line */ (const char *) "    ..    ",
           /* line */ (const char *) "  ......  ",
           /* line */ (const char *) "^........^",
           /* line */ (const char *) "    ..    ",
           /* line */ (const char *) "     .    ",
           /* line */ (const char *) "     .    ",
           /* line */ (const char *) "     ^    ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "      ^   ",
           /* line */ (const char *) "      .   ",
           /* line */ (const char *) " .......  ",
           /* line */ (const char *) "^.......  ",
           /* line */ (const char *) " ........^",
           /* line */ (const char *) "    ..    ",
           /* line */ (const char *) "     ^    ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^       ",
           /* line */ (const char *) "   .       ",
           /* line */ (const char *) "  .......  ",
           /* line */ (const char *) "  ........^",
           /* line */ (const char *) "^........  ",
           /* line */ (const char *) "     ..    ",
           /* line */ (const char *) "      .    ",
           /* line */ (const char *) "      ^    ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^   ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "^.... ",
           /* line */ (const char *) " ....^",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "   ^  ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^    ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) " ...... ",
           /* line */ (const char *) "^......^",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "    ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^    ",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) "^.......^",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^      ",
           /* line */ (const char *) "     .      ",
           /* line */ (const char *) "    ..      ",
           /* line */ (const char *) "^.......    ",
           /* line */ (const char *) "  .........^",
           /* line */ (const char *) "    ..      ",
           /* line */ (const char *) "    .       ",
           /* line */ (const char *) "    ^       ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^   ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "^......^",
           /* line */ (const char *) " ...... ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "   ^    ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^   ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "^.... ",
           /* line */ (const char *) " ....^",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "   ^  ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^    ",
           /* line */ (const char *) "    ..    ",
           /* line */ (const char *) "  .......^",
           /* line */ (const char *) "^.......  ",
           /* line */ (const char *) "    ..    ",
           /* line */ (const char *) "    .     ",
           /* line */ (const char *) "    ^     ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^     ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "^.....^",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "    ^  ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^   ",
           /* line */ (const char *) "    .   ",
           /* line */ (const char *) "  ..... ",
           /* line */ (const char *) "^......^",
           /* line */ (const char *) "  ..... ",
           /* line */ (const char *) "    ..  ",
           /* line */ (const char *) "    ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^  ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) " ....^",
           /* line */ (const char *) "^.... ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "   ^  ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "       ^   ",
           /* line */ (const char *) "       .   ",
           /* line */ (const char *) "       .   ",
           /* line */ (const char *) "       ..  ",
           /* line */ (const char *) "      .... ",
           /* line */ (const char *) "^.........^",
           /* line */ (const char *) "       ..  ",
           /* line */ (const char *) "        ^  ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^   ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) " ......^",
           /* line */ (const char *) "^...... ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "    ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^  ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "^....^",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^   ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "^.....^",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^   ",
           /* line */ (const char *) "     .   ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "  ...... ",
           /* line */ (const char *) "^.......^",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "     .   ",
           /* line */ (const char *) "     ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^    ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "^......^",
           /* line */ (const char *) " ...... ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "   ^    ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^  ",
           /* line */ (const char *) "   .  ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "^.... ",
           /* line */ (const char *) " ....^",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "  .   ",
           /* line */ (const char *) "  .   ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^     ",
           /* line */ (const char *) "^....... ",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) " .......^",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "    .    ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^    ",
           /* line */ (const char *) "^....... ",
           /* line */ (const char *) " .......^",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^      ",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) "^.......^",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "     ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^  ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "^.....^",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^   ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "^...... ",
           /* line */ (const char *) " ......^",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "   ^    ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^      ",
           /* line */ (const char *) "    ..     ",
           /* line */ (const char *) "^.........^",
           /* line */ (const char *) "  ......   ",
           /* line */ (const char *) "    ..     ",
           /* line */ (const char *) "    .      ",
           /* line */ (const char *) "    ^      ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^    ",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) " .......^",
           /* line */ (const char *) "^....... ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "     .   ",
           /* line */ (const char *) "     ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^   ",
           /* line */ (const char *) "    .   ",
           /* line */ (const char *) "    .   ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "^...... ",
           /* line */ (const char *) " ......^",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "   ^    ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^   ",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) " .......^",
           /* line */ (const char *) "^....... ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^   ",
           /* line */ (const char *) "     .   ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "   .....^",
           /* line */ (const char *) "^......  ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^   ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "^....^",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^    ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) " ......^",
           /* line */ (const char *) "^...... ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "   ^    ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^  ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "^.... ",
           /* line */ (const char *) " ....^",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^      ",
           /* line */ (const char *) "   .      ",
           /* line */ (const char *) "^.....    ",
           /* line */ (const char *) " ........^",
           /* line */ (const char *) " .....    ",
           /* line */ (const char *) "   ..     ",
           /* line */ (const char *) "    .     ",
           /* line */ (const char *) "    .     ",
           /* line */ (const char *) "    ^     ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^    ",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "    ^  ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^   ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "^.....^",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^    ",
           /* line */ (const char *) "     .    ",
           /* line */ (const char *) "    ..    ",
           /* line */ (const char *) "  .......^",
           /* line */ (const char *) "^.......  ",
           /* line */ (const char *) "    ..    ",
           /* line */ (const char *) "    ^     ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^      ",
           /* line */ (const char *) " .......^",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) "^....... ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "     ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^  ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "    ^  ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^  ",
           /* line */ (const char *) "    .  ",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) "  ....^",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "   .   ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^          ",
           /* line */ (const char *) " .......    ",
           /* line */ (const char *) " ..........^",
           /* line */ (const char *) "^.......    ",
           /* line */ (const char *) "    ..      ",
           /* line */ (const char *) "    .       ",
           /* line */ (const char *) "    .       ",
           /* line */ (const char *) "    ^       ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^     ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^   ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "^.... ",
           /* line */ (const char *) " ....^",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^       ",
           /* line */ (const char *) "    ..      ",
           /* line */ (const char *) "  ......    ",
           /* line */ (const char *) "^..........^",
           /* line */ (const char *) "    ..      ",
           /* line */ (const char *) "    .       ",
           /* line */ (const char *) "    ^       ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^   ",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) "^....... ",
           /* line */ (const char *) " .......^",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "     ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^  ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) " ....^",
           /* line */ (const char *) "^.... ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "   ^  ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^    ",
           /* line */ (const char *) "   ..    ",
           /* line */ (const char *) "  ....   ",
           /* line */ (const char *) "^.......^",
           /* line */ (const char *) "   ..    ",
           /* line */ (const char *) "   .     ",
           /* line */ (const char *) "   .     ",
           /* line */ (const char *) "   ^     ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^   ",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) "^.......^",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^    ",
           /* line */ (const char *) "    ..... ",
           /* line */ (const char *) "    .....^",
           /* line */ (const char *) "^........ ",
           /* line */ (const char *) "      ..  ",
           /* line */ (const char *) "      .   ",
           /* line */ (const char *) "      ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^        ",
           /* line */ (const char *) "  .......  ",
           /* line */ (const char *) "^.........^",
           /* line */ (const char *) "  .......  ",
           /* line */ (const char *) "     ..    ",
           /* line */ (const char *) "     ^     ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^     ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "^.....^",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^     ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "^.....^",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^       ",
           /* line */ (const char *) "^..........  ",
           /* line */ (const char *) "    .......  ",
           /* line */ (const char *) "    ........^",
           /* line */ (const char *) "       ..    ",
           /* line */ (const char *) "       ^     ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^   ",
           /* line */ (const char *) " .......^",
           /* line */ (const char *) "^....... ",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^  ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "^....^",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "   ^  ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^    ",
           /* line */ (const char *) "^.....^",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "    ^  ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "      ^   ",
           /* line */ (const char *) "     ..   ",
           /* line */ (const char *) "   ...... ",
           /* line */ (const char *) "^........^",
           /* line */ (const char *) "     ..   ",
           /* line */ (const char *) "     .    ",
           /* line */ (const char *) "     .    ",
           /* line */ (const char *) "     ^    ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^     ",
           /* line */ (const char *) "   ..     ",
           /* line */ (const char *) "^......   ",
           /* line */ (const char *) " ........^",
           /* line */ (const char *) "   ..     ",
           /* line */ (const char *) "    ^     ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^   ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "^......^",
           /* line */ (const char *) " ...... ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "    ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "      ^    ",
           /* line */ (const char *) "  .......  ",
           /* line */ (const char *) "  .......  ",
           /* line */ (const char *) "^.........^",
           /* line */ (const char *) "     ..    ",
           /* line */ (const char *) "     .     ",
           /* line */ (const char *) "     ^     ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^     ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "^.....^",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^   ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) " ....^",
           /* line */ (const char *) "^.... ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^   ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) " ....^",
           /* line */ (const char *) "^.... ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "   ^  ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^    ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "    ^  ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^    ",
           /* line */ (const char *) "    ..    ",
           /* line */ (const char *) "  ......  ",
           /* line */ (const char *) "^........^",
           /* line */ (const char *) "    ..    ",
           /* line */ (const char *) "     ^    ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^  ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "^.....^",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "      ^  ",
           /* line */ (const char *) "^....... ",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) " .......^",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^    ",
           /* line */ (const char *) "  ......^",
           /* line */ (const char *) "  .....  ",
           /* line */ (const char *) "^......  ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^     ",
           /* line */ (const char *) "    ..     ",
           /* line */ (const char *) "^.........^",
           /* line */ (const char *) "  ......   ",
           /* line */ (const char *) "    ..     ",
           /* line */ (const char *) "    ^      ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^     ",
           /* line */ (const char *) "     .     ",
           /* line */ (const char *) "    .....  ",
           /* line */ (const char *) "    ......^",
           /* line */ (const char *) "^........  ",
           /* line */ (const char *) "      ..   ",
           /* line */ (const char *) "      .    ",
           /* line */ (const char *) "      ^    ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^     ",
           /* line */ (const char *) "   ..    ",
           /* line */ (const char *) "^......  ",
           /* line */ (const char *) " .......^",
           /* line */ (const char *) "   ..    ",
           /* line */ (const char *) "   ^     ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^    ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "^.......^",
           /* line */ (const char *) "  ...... ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "     .   ",
           /* line */ (const char *) "     ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^   ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "^......^",
           /* line */ (const char *) " ...... ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "   .    ",
           /* line */ (const char *) "   ^    ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^       ",
           /* line */ (const char *) "  .       ",
           /* line */ (const char *) "^......   ",
           /* line */ (const char *) "  .....   ",
           /* line */ (const char *) "  .......^",
           /* line */ (const char *) "    ..    ",
           /* line */ (const char *) "     ^    ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^      ",
           /* line */ (const char *) "^....... ",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) " .......^",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^         ",
           /* line */ (const char *) "^.......    ",
           /* line */ (const char *) " ..........^",
           /* line */ (const char *) " .......    ",
           /* line */ (const char *) "    ..      ",
           /* line */ (const char *) "    ^       ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^   ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "^....^",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^      ",
           /* line */ (const char *) " .......^",
           /* line */ (const char *) "^....... ",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^    ",
           /* line */ (const char *) "  .    ",
           /* line */ (const char *) "  ..   ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) "^....  ",
           /* line */ (const char *) "  ..   ",
           /* line */ (const char *) "   .   ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^   ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) " ...... ",
           /* line */ (const char *) "^......^",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "   ^    ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^         ",
           /* line */ (const char *) "   .         ",
           /* line */ (const char *) "   .......   ",
           /* line */ (const char *) "   .......   ",
           /* line */ (const char *) "^...........^",
           /* line */ (const char *) "      ..     ",
           /* line */ (const char *) "      .      ",
           /* line */ (const char *) "      .      ",
           /* line */ (const char *) "      ^      ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^  ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) " ....^",
           /* line */ (const char *) "^.... ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "   ^  ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^  ",
           /* line */ (const char *) "    .  ",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) "  ....^",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "    .  ",
           /* line */ (const char *) "    .  ",
           /* line */ (const char *) "    ^  ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^       ",
           /* line */ (const char *) "  .       ",
           /* line */ (const char *) "  .       ",
           /* line */ (const char *) "^.......  ",
           /* line */ (const char *) " .......  ",
           /* line */ (const char *) " ........^",
           /* line */ (const char *) "    ..    ",
           /* line */ (const char *) "    ^     ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^    ",
           /* line */ (const char *) "   .    ",
           /* line */ (const char *) "  ..    ",
           /* line */ (const char *) "^....   ",
           /* line */ (const char *) " ......^",
           /* line */ (const char *) "  ..    ",
           /* line */ (const char *) "   ^    ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^     ",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "    ^  ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^   ",
           /* line */ (const char *) "     .   ",
           /* line */ (const char *) "     .   ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "^......  ",
           /* line */ (const char *) "   .....^",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "    .    ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "      ^  ",
           /* line */ (const char *) "     ..  ",
           /* line */ (const char *) "    .... ",
           /* line */ (const char *) "^.......^",
           /* line */ (const char *) "     ..  ",
           /* line */ (const char *) "      .  ",
           /* line */ (const char *) "      ^  ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^    ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "    ^  ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "       ^     ",
           /* line */ (const char *) "   .......   ",
           /* line */ (const char *) "^...........^",
           /* line */ (const char *) "   .......   ",
           /* line */ (const char *) "      ..     ",
           /* line */ (const char *) "      .      ",
           /* line */ (const char *) "      ^      ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^   ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "^....^",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^  ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "^....^",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^    ",
           /* line */ (const char *) "  .    ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "^.....^",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "    .  ",
           /* line */ (const char *) "    ^  ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^  ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "^....^",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^       ",
           /* line */ (const char *) " .......^",
           /* line */ (const char *) "^....... ",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "     .   ",
           /* line */ (const char *) "     ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^  ",
           /* line */ (const char *) "^.....^",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^  ",
           /* line */ (const char *) "   .  ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) " ....^",
           /* line */ (const char *) "^.... ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "   .  ",
           /* line */ (const char *) "   .  ",
           /* line */ (const char *) "   .  ",
           /* line */ (const char *) "   ^  ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^   ",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) "^.......^",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^   ",
           /* line */ (const char *) "   .   ",
           /* line */ (const char *) "  ..   ",
           /* line */ (const char *) "^....  ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) "  ..   ",
           /* line */ (const char *) "  ^    ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^   ",
           /* line */ (const char *) "^....... ",
           /* line */ (const char *) " .......^",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^   ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "^......^",
           /* line */ (const char *) " ...... ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "    ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "      ^    ",
           /* line */ (const char *) "   .......^",
           /* line */ (const char *) "   ....... ",
           /* line */ (const char *) "^......... ",
           /* line */ (const char *) "      ..   ",
           /* line */ (const char *) "      ^    ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^       ",
           /* line */ (const char *) " .......  ",
           /* line */ (const char *) " ........^",
           /* line */ (const char *) "^.......  ",
           /* line */ (const char *) "    ..    ",
           /* line */ (const char *) "     .    ",
           /* line */ (const char *) "     ^    ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "       ^  ",
           /* line */ (const char *) "^........ ",
           /* line */ (const char *) "  ....... ",
           /* line */ (const char *) "  .......^",
           /* line */ (const char *) "     ..   ",
           /* line */ (const char *) "      ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^       ",
           /* line */ (const char *) "   .       ",
           /* line */ (const char *) "   .       ",
           /* line */ (const char *) "  .......  ",
           /* line */ (const char *) "^.........^",
           /* line */ (const char *) "  .......  ",
           /* line */ (const char *) "     ..    ",
           /* line */ (const char *) "      .    ",
           /* line */ (const char *) "      .    ",
           /* line */ (const char *) "      ^    ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^    ",
           /* line */ (const char *) " ........^",
           /* line */ (const char *) " .......  ",
           /* line */ (const char *) "^.......  ",
           /* line */ (const char *) "    ..    ",
           /* line */ (const char *) "    ^     ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^   ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^    ",
           /* line */ (const char *) "   .    ",
           /* line */ (const char *) "  ..    ",
           /* line */ (const char *) " ......^",
           /* line */ (const char *) "^....   ",
           /* line */ (const char *) "  ..    ",
           /* line */ (const char *) "  .     ",
           /* line */ (const char *) "  ^     ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^     ",
           /* line */ (const char *) "   .     ",
           /* line */ (const char *) " .......^",
           /* line */ (const char *) "^.....   ",
           /* line */ (const char *) " .....   ",
           /* line */ (const char *) "   ..    ",
           /* line */ (const char *) "    .    ",
           /* line */ (const char *) "    .    ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^   ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "^.......^",
           /* line */ (const char *) "  ...... ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^    ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "^...... ",
           /* line */ (const char *) " ......^",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "   ^    ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^     ",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) "^....... ",
           /* line */ (const char *) " .......^",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^    ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "    ^  ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^    ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) " ...... ",
           /* line */ (const char *) "^......^",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "    .   ",
           /* line */ (const char *) "    .   ",
           /* line */ (const char *) "    ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^     ",
           /* line */ (const char *) "    ..    ",
           /* line */ (const char *) "^.......  ",
           /* line */ (const char *) "  .......^",
           /* line */ (const char *) "    ..    ",
           /* line */ (const char *) "    .     ",
           /* line */ (const char *) "    .     ",
           /* line */ (const char *) "    ^     ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^   ",
           /* line */ (const char *) "  .   ",
           /* line */ (const char *) "  .   ",
           /* line */ (const char *) "  .   ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "^....^",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "  .   ",
           /* line */ (const char *) "  .   ",
           /* line */ (const char *) "  .   ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^   ",
           /* line */ (const char *) "  .   ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "^.... ",
           /* line */ (const char *) " ....^",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "  .   ",
           /* line */ (const char *) "  .   ",
           /* line */ (const char *) "  .   ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^     ",
           /* line */ (const char *) "    .     ",
           /* line */ (const char *) " ........^",
           /* line */ (const char *) " .......  ",
           /* line */ (const char *) "^.......  ",
           /* line */ (const char *) "    ..    ",
           /* line */ (const char *) "    .     ",
           /* line */ (const char *) "    .     ",
           /* line */ (const char *) "    .     ",
           /* line */ (const char *) "    ^     ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "      ^  ",
           /* line */ (const char *) " .......^",
           /* line */ (const char *) "^....... ",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "     ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^     ",
           /* line */ (const char *) "   ..    ",
           /* line */ (const char *) "^......  ",
           /* line */ (const char *) " .......^",
           /* line */ (const char *) "   ..    ",
           /* line */ (const char *) "   ^     ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^  ",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "    ^  ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^   ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "^.... ",
           /* line */ (const char *) " ....^",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "   ^  ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^     ",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^     ",
           /* line */ (const char *) "   .     ",
           /* line */ (const char *) "   .     ",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) "^.......^",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "    .    ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^  ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) " ....^",
           /* line */ (const char *) "^.... ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "   ^  ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^     ",
           /* line */ (const char *) "    .     ",
           /* line */ (const char *) "   ......^",
           /* line */ (const char *) "^.......  ",
           /* line */ (const char *) "   .....  ",
           /* line */ (const char *) "     ..   ",
           /* line */ (const char *) "      ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^    ",
           /* line */ (const char *) "  .    ",
           /* line */ (const char *) "  .    ",
           /* line */ (const char *) "  ..   ",
           /* line */ (const char *) "^.....^",
           /* line */ (const char *) " ....  ",
           /* line */ (const char *) "  ..   ",
           /* line */ (const char *) "  ^    ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^    ",
           /* line */ (const char *) "    .    ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "  ...... ",
           /* line */ (const char *) "^.......^",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "     ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^    ",
           /* line */ (const char *) "     .    ",
           /* line */ (const char *) "     .    ",
           /* line */ (const char *) "     .    ",
           /* line */ (const char *) " .......  ",
           /* line */ (const char *) "^.......  ",
           /* line */ (const char *) " ........^",
           /* line */ (const char *) "    ..    ",
           /* line */ (const char *) "     .    ",
           /* line */ (const char *) "     .    ",
           /* line */ (const char *) "     .    ",
           /* line */ (const char *) "     ^    ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^  ",
           /* line */ (const char *) "    ..  ",
           /* line */ (const char *) "   .... ",
           /* line */ (const char *) "^......^",
           /* line */ (const char *) "    ..  ",
           /* line */ (const char *) "     .  ",
           /* line */ (const char *) "     .  ",
           /* line */ (const char *) "     ^  ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^   ",
           /* line */ (const char *) "^....... ",
           /* line */ (const char *) " .......^",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^   ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "^....^",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "   ^  ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^  ",
           /* line */ (const char *) "     .  ",
           /* line */ (const char *) "    ..  ",
           /* line */ (const char *) "   ....^",
           /* line */ (const char *) "^...... ",
           /* line */ (const char *) "    ..  ",
           /* line */ (const char *) "     .  ",
           /* line */ (const char *) "     ^  ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "      ^  ",
           /* line */ (const char *) "^....... ",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) " .......^",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "     ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^    ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) " ......^",
           /* line */ (const char *) "^...... ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "    ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^    ",
           /* line */ (const char *) "     .    ",
           /* line */ (const char *) "    ..    ",
           /* line */ (const char *) "  ......  ",
           /* line */ (const char *) "^........^",
           /* line */ (const char *) "    ..    ",
           /* line */ (const char *) "     ^    ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "      ^  ",
           /* line */ (const char *) "^....... ",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) " .......^",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "     ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "       ^    ",
           /* line */ (const char *) "       .    ",
           /* line */ (const char *) "      ..    ",
           /* line */ (const char *) "    ......  ",
           /* line */ (const char *) "^..........^",
           /* line */ (const char *) "      ..    ",
           /* line */ (const char *) "       .    ",
           /* line */ (const char *) "       ^    ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^  ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) " ....^",
           /* line */ (const char *) "^.... ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "   ^  ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^   ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) " ....^",
           /* line */ (const char *) "^.... ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^   ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "^....^",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "   ^  ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^     ",
           /* line */ (const char *) "     .     ",
           /* line */ (const char *) "     ..    ",
           /* line */ (const char *) "^.........^",
           /* line */ (const char *) "   ......  ",
           /* line */ (const char *) "     ..    ",
           /* line */ (const char *) "     ^     ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^   ",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "    ^  ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^  ",
           /* line */ (const char *) "    .  ",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) "  ....^",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "    .  ",
           /* line */ (const char *) "    .  ",
           /* line */ (const char *) "    ^  ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^  ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "^.....^",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "       ^    ",
           /* line */ (const char *) "^..........^",
           /* line */ (const char *) "   .......  ",
           /* line */ (const char *) "   .......  ",
           /* line */ (const char *) "      ..    ",
           /* line */ (const char *) "      ^     ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "       ^  ",
           /* line */ (const char *) "       .  ",
           /* line */ (const char *) "  .......^",
           /* line */ (const char *) "  ....... ",
           /* line */ (const char *) "^........ ",
           /* line */ (const char *) "     ..   ",
           /* line */ (const char *) "      .   ",
           /* line */ (const char *) "      ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^   ",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "    ^  ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^   ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "^......^",
           /* line */ (const char *) " ...... ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "    ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^  ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "^.... ",
           /* line */ (const char *) " ....^",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "   ^  ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^    ",
           /* line */ (const char *) "^.....   ",
           /* line */ (const char *) " .....   ",
           /* line */ (const char *) " .......^",
           /* line */ (const char *) "   ..    ",
           /* line */ (const char *) "    .    ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^      ",
           /* line */ (const char *) " .      ",
           /* line */ (const char *) "^.....  ",
           /* line */ (const char *) " ......^",
           /* line */ (const char *) " .....  ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "   ^    ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^       ",
           /* line */ (const char *) "  .....    ",
           /* line */ (const char *) "  ........^",
           /* line */ (const char *) "^......    ",
           /* line */ (const char *) "    ..     ",
           /* line */ (const char *) "     .     ",
           /* line */ (const char *) "     .     ",
           /* line */ (const char *) "     ^     ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^     ",
           /* line */ (const char *) "   .     ",
           /* line */ (const char *) "  .....  ",
           /* line */ (const char *) "^.......^",
           /* line */ (const char *) "  .....  ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "    .    ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^     ",
           /* line */ (const char *) "  .     ",
           /* line */ (const char *) "  ..    ",
           /* line */ (const char *) " ....   ",
           /* line */ (const char *) "^......^",
           /* line */ (const char *) "  ..    ",
           /* line */ (const char *) "   .    ",
           /* line */ (const char *) "   ^    ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^      ",
           /* line */ (const char *) "     .      ",
           /* line */ (const char *) "   ........^",
           /* line */ (const char *) "^.......    ",
           /* line */ (const char *) "   .....    ",
           /* line */ (const char *) "     ..     ",
           /* line */ (const char *) "     .      ",
           /* line */ (const char *) "     ^      ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^   ",
           /* line */ (const char *) "  ......^",
           /* line */ (const char *) "  .....  ",
           /* line */ (const char *) "^......  ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "    .    ",
           /* line */ (const char *) "    .    ",
           /* line */ (const char *) "    .    ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "      ^  ",
           /* line */ (const char *) "^....... ",
           /* line */ (const char *) " .......^",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "     ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^     ",
           /* line */ (const char *) "^....... ",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) " .......^",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "     ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^   ",
           /* line */ (const char *) "   .   ",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) "  ....^",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^    ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "    ^  ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^   ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "^.....  ",
           /* line */ (const char *) "  .....^",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "   .    ",
           /* line */ (const char *) "   ^    ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^    ",
           /* line */ (const char *) "     .    ",
           /* line */ (const char *) "     ..   ",
           /* line */ (const char *) "   ......^",
           /* line */ (const char *) "^........ ",
           /* line */ (const char *) "     ..   ",
           /* line */ (const char *) "      .   ",
           /* line */ (const char *) "      .   ",
           /* line */ (const char *) "      ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^       ",
           /* line */ (const char *) "   ..      ",
           /* line */ (const char *) "^......    ",
           /* line */ (const char *) " .........^",
           /* line */ (const char *) "   ..      ",
           /* line */ (const char *) "   ^       ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^  ",
           /* line */ (const char *) "^.....^",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "    ^  ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^   ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "^...... ",
           /* line */ (const char *) " ......^",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "    ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^    ",
           /* line */ (const char *) "   .    ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "  ....  ",
           /* line */ (const char *) "^......^",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "   .    ",
           /* line */ (const char *) "   ^    ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^  ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "^.....^",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^   ",
           /* line */ (const char *) "   .   ",
           /* line */ (const char *) "  ..   ",
           /* line */ (const char *) "^....  ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) "  ..   ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^        ",
           /* line */ (const char *) "  .        ",
           /* line */ (const char *) "  .......  ",
           /* line */ (const char *) "  .......  ",
           /* line */ (const char *) "^.........^",
           /* line */ (const char *) "     ..    ",
           /* line */ (const char *) "     .     ",
           /* line */ (const char *) "     ^     ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^   ",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) "^.......^",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^   ",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) "^.......^",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "     ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^  ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "^.... ",
           /* line */ (const char *) " ....^",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^   ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "^....^",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "   ^  ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^    ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^   ",
           /* line */ (const char *) "    .   ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) " ...... ",
           /* line */ (const char *) "^......^",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "   .    ",
           /* line */ (const char *) "   .    ",
           /* line */ (const char *) "   .    ",
           /* line */ (const char *) "   ^    ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^  ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "^....^",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "   ^  ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^    ",
           /* line */ (const char *) "  .    ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "^.....^",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "    ^  ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^    ",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) "^.......^",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "     ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^       ",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) "^....... ",
           /* line */ (const char *) " .......^",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^    ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^     ",
           /* line */ (const char *) "  .......^",
           /* line */ (const char *) "  .....   ",
           /* line */ (const char *) "^......   ",
           /* line */ (const char *) "    ..    ",
           /* line */ (const char *) "    ^     ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^   ",
           /* line */ (const char *) " .......^",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) "^....... ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "     ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^   ",
           /* line */ (const char *) "    ..  ",
           /* line */ (const char *) "^......^",
           /* line */ (const char *) "   .... ",
           /* line */ (const char *) "    ..  ",
           /* line */ (const char *) "     .  ",
           /* line */ (const char *) "     ^  ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^    ",
           /* line */ (const char *) " .......^",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) "^....... ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "     ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "      ^  ",
           /* line */ (const char *) " .......^",
           /* line */ (const char *) "^....... ",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "     ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^   ",
           /* line */ (const char *) "    ..  ",
           /* line */ (const char *) "^...... ",
           /* line */ (const char *) "   ....^",
           /* line */ (const char *) "    ..  ",
           /* line */ (const char *) "     .  ",
           /* line */ (const char *) "     ^  ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^  ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) " ....^",
           /* line */ (const char *) "^.... ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^  ",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) "  ....^",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "    .  ",
           /* line */ (const char *) "    .  ",
           /* line */ (const char *) "    ^  ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^  ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "^....^",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "   .  ",
           /* line */ (const char *) "   ^  ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^    ",
           /* line */ (const char *) "^......  ",
           /* line */ (const char *) "  .....  ",
           /* line */ (const char *) "  ......^",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "    .    ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^   ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "^...... ",
           /* line */ (const char *) " ......^",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "    ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^  ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "^....^",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^       ",
           /* line */ (const char *) "   .......   ",
           /* line */ (const char *) "   .........^",
           /* line */ (const char *) "^.........   ",
           /* line */ (const char *) "      ..     ",
           /* line */ (const char *) "       ^     ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "      ^    ",
           /* line */ (const char *) "      .    ",
           /* line */ (const char *) " .......   ",
           /* line */ (const char *) "^.........^",
           /* line */ (const char *) " .......   ",
           /* line */ (const char *) "    ..     ",
           /* line */ (const char *) "    ^      ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^    ",
           /* line */ (const char *) "   .    ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "^......^",
           /* line */ (const char *) "  ....  ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "    ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^    ",
           /* line */ (const char *) "  .    ",
           /* line */ (const char *) "  .    ",
           /* line */ (const char *) "  ..   ",
           /* line */ (const char *) " ....  ",
           /* line */ (const char *) "^.....^",
           /* line */ (const char *) "  ..   ",
           /* line */ (const char *) "   .   ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^     ",
           /* line */ (const char *) " .     ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "    .  ",
           /* line */ (const char *) "    ^  ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^    ",
           /* line */ (const char *) "    ..    ",
           /* line */ (const char *) "  ......  ",
           /* line */ (const char *) "^........^",
           /* line */ (const char *) "    ..    ",
           /* line */ (const char *) "    .     ",
           /* line */ (const char *) "    .     ",
           /* line */ (const char *) "    ^     ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^   ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) " ......^",
           /* line */ (const char *) "^...... ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "   ^    ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^         ",
           /* line */ (const char *) "   .         ",
           /* line */ (const char *) "^.........   ",
           /* line */ (const char *) "   .......   ",
           /* line */ (const char *) "   .........^",
           /* line */ (const char *) "      ..     ",
           /* line */ (const char *) "      ^      ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^      ",
           /* line */ (const char *) "    .      ",
           /* line */ (const char *) "    ..     ",
           /* line */ (const char *) "^.......   ",
           /* line */ (const char *) "  ........^",
           /* line */ (const char *) "    ..     ",
           /* line */ (const char *) "    ^      ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^    ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) " ......^",
           /* line */ (const char *) "^...... ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "   ^    ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^   ",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) "^.......^",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "     ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "       ^   ",
           /* line */ (const char *) "       .   ",
           /* line */ (const char *) "    .....  ",
           /* line */ (const char *) "    .....  ",
           /* line */ (const char *) "^.........^",
           /* line */ (const char *) "      ..   ",
           /* line */ (const char *) "      ^    ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^     ",
           /* line */ (const char *) "  .     ",
           /* line */ (const char *) "  .     ",
           /* line */ (const char *) " ......^",
           /* line */ (const char *) "^.....  ",
           /* line */ (const char *) " .....  ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "    .   ",
           /* line */ (const char *) "    ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "          ^   ",
           /* line */ (const char *) "^...........  ",
           /* line */ (const char *) "     .......  ",
           /* line */ (const char *) "     ........^",
           /* line */ (const char *) "        ..    ",
           /* line */ (const char *) "        ^     ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "       ^  ",
           /* line */ (const char *) "  ....... ",
           /* line */ (const char *) "  .......^",
           /* line */ (const char *) "^........ ",
           /* line */ (const char *) "     ..   ",
           /* line */ (const char *) "     .    ",
           /* line */ (const char *) "     ^    ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^      ",
           /* line */ (const char *) "  .      ",
           /* line */ (const char *) "  ..     ",
           /* line */ (const char *) " ....    ",
           /* line */ (const char *) "^.......^",
           /* line */ (const char *) "  ..     ",
           /* line */ (const char *) "  .      ",
           /* line */ (const char *) "  ^      ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^    ",
           /* line */ (const char *) "   .    ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) " ......^",
           /* line */ (const char *) "^...... ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "   ^    ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "      ^  ",
           /* line */ (const char *) "^....... ",
           /* line */ (const char *) " .......^",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^   ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) " ......^",
           /* line */ (const char *) "^...... ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "   ^    ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^      ",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) "^....... ",
           /* line */ (const char *) " .......^",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "     ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^     ",
           /* line */ (const char *) "   .......^",
           /* line */ (const char *) "   .....   ",
           /* line */ (const char *) "^.......   ",
           /* line */ (const char *) "     ..    ",
           /* line */ (const char *) "      .    ",
           /* line */ (const char *) "      ^    ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^    ",
           /* line */ (const char *) "   .    ",
           /* line */ (const char *) "  ..    ",
           /* line */ (const char *) "^....   ",
           /* line */ (const char *) " ......^",
           /* line */ (const char *) "  ..    ",
           /* line */ (const char *) "  .     ",
           /* line */ (const char *) "  ^     ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "      ^     ",
           /* line */ (const char *) "      .     ",
           /* line */ (const char *) "  .......   ",
           /* line */ (const char *) "  .......   ",
           /* line */ (const char *) "^..........^",
           /* line */ (const char *) "     ..     ",
           /* line */ (const char *) "      .     ",
           /* line */ (const char *) "      ^     ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^     ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "    ^  ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^   ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) " ....^",
           /* line */ (const char *) "^.... ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "   ^  ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^     ",
           /* line */ (const char *) "    .     ",
           /* line */ (const char *) "   ..     ",
           /* line */ (const char *) "  ....    ",
           /* line */ (const char *) "^........^",
           /* line */ (const char *) "   ..     ",
           /* line */ (const char *) "   .      ",
           /* line */ (const char *) "   ^      ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^     ",
           /* line */ (const char *) "^....... ",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) " .......^",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "    .    ",
           /* line */ (const char *) "    .    ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^        ",
           /* line */ (const char *) "   .        ",
           /* line */ (const char *) "   .        ",
           /* line */ (const char *) "   .        ",
           /* line */ (const char *) "   .......  ",
           /* line */ (const char *) "   .......  ",
           /* line */ (const char *) "^..........^",
           /* line */ (const char *) "      ..    ",
           /* line */ (const char *) "      .     ",
           /* line */ (const char *) "      ^     ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^   ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "^......^",
           /* line */ (const char *) " ...... ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "    ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^    ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "^...... ",
           /* line */ (const char *) " ......^",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "    ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^   ",
           /* line */ (const char *) "^.....^",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^     ",
           /* line */ (const char *) "   ......^",
           /* line */ (const char *) "^.......  ",
           /* line */ (const char *) "   .....  ",
           /* line */ (const char *) "     ..   ",
           /* line */ (const char *) "      ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^      ",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) "^....... ",
           /* line */ (const char *) " .......^",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^   ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) " ....^",
           /* line */ (const char *) "^.... ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "   ^  ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^     ",
           /* line */ (const char *) "^....... ",
           /* line */ (const char *) " .......^",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "     ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^       ",
           /* line */ (const char *) "   .......  ",
           /* line */ (const char *) "^..........^",
           /* line */ (const char *) "   .......  ",
           /* line */ (const char *) "      ..    ",
           /* line */ (const char *) "       ^    ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^       ",
           /* line */ (const char *) "   ..      ",
           /* line */ (const char *) "^.........^",
           /* line */ (const char *) "  ....     ",
           /* line */ (const char *) "   ..      ",
           /* line */ (const char *) "   ^       ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^    ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "^......^",
           /* line */ (const char *) " ...... ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "   ^    ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^   ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "^...... ",
           /* line */ (const char *) " ......^",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "   ^    ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^   ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "^.... ",
           /* line */ (const char *) " ....^",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^   ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) " ......^",
           /* line */ (const char *) "^...... ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "    ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^  ",
           /* line */ (const char *) "  .....^",
           /* line */ (const char *) "^...... ",
           /* line */ (const char *) "  ..... ",
           /* line */ (const char *) "    ..  ",
           /* line */ (const char *) "    .   ",
           /* line */ (const char *) "    ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^  ",
           /* line */ (const char *) "   .  ",
           /* line */ (const char *) "   .  ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) " ....^",
           /* line */ (const char *) "^.... ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "  .   ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^     ",
           /* line */ (const char *) "  .....   ",
           /* line */ (const char *) "^........^",
           /* line */ (const char *) "  .....   ",
           /* line */ (const char *) "    ..    ",
           /* line */ (const char *) "    .     ",
           /* line */ (const char *) "    ^     ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^     ",
           /* line */ (const char *) "   ..    ",
           /* line */ (const char *) " .......^",
           /* line */ (const char *) "^......  ",
           /* line */ (const char *) "   ..    ",
           /* line */ (const char *) "   ^     ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^       ",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) "^.......^",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "     ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^   ",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^    ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "^...... ",
           /* line */ (const char *) " ......^",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "    ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^    ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "^......^",
           /* line */ (const char *) " ...... ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "   ^    ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^   ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) " .... ",
           /* line */ (const char *) "^....^",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^  ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) " ....^",
           /* line */ (const char *) "^.... ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "  ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "      ^     ",
           /* line */ (const char *) "      .     ",
           /* line */ (const char *) "    .....   ",
           /* line */ (const char *) "^........   ",
           /* line */ (const char *) "    .......^",
           /* line */ (const char *) "      ..    ",
           /* line */ (const char *) "      ^     ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^  ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "^.....^",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "    ^  ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^  ",
           /* line */ (const char *) "     .  ",
           /* line */ (const char *) "^...... ",
           /* line */ (const char *) "  ..... ",
           /* line */ (const char *) "  .....^",
           /* line */ (const char *) "    ..  ",
           /* line */ (const char *) "    ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^     ",
           /* line */ (const char *) "  .     ",
           /* line */ (const char *) "  ..... ",
           /* line */ (const char *) "^......^",
           /* line */ (const char *) "  ..... ",
           /* line */ (const char *) "    ..  ",
           /* line */ (const char *) "     .  ",
           /* line */ (const char *) "     ^  ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^   ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) " ......^",
           /* line */ (const char *) "^...... ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "    ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^     ",
           /* line */ (const char *) "    ..     ",
           /* line */ (const char *) "^......    ",
           /* line */ (const char *) "   .......^",
           /* line */ (const char *) "    ..     ",
           /* line */ (const char *) "     .     ",
           /* line */ (const char *) "     .     ",
           /* line */ (const char *) "     ^     ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^    ",
           /* line */ (const char *) "  .    ",
           /* line */ (const char *) "  .    ",
           /* line */ (const char *) "  ..   ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) "^....  ",
           /* line */ (const char *) "  ..   ",
           /* line */ (const char *) "  .    ",
           /* line */ (const char *) "  ^    ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^    ",
           /* line */ (const char *) "    .    ",
           /* line */ (const char *) " .....   ",
           /* line */ (const char *) " .....   ",
           /* line */ (const char *) "^.......^",
           /* line */ (const char *) "   ..    ",
           /* line */ (const char *) "   .     ",
           /* line */ (const char *) "   ^     ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^      ",
           /* line */ (const char *) "^....... ",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) " .......^",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^   ",
           /* line */ (const char *) "     .   ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "   ....  ",
           /* line */ (const char *) "^.......^",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "     ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^    ",
           /* line */ (const char *) "     .    ",
           /* line */ (const char *) "     .    ",
           /* line */ (const char *) "     .    ",
           /* line */ (const char *) "    ..    ",
           /* line */ (const char *) "   ....   ",
           /* line */ (const char *) "^........^",
           /* line */ (const char *) "    ..    ",
           /* line */ (const char *) "    .     ",
           /* line */ (const char *) "    ^     ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^   ",
           /* line */ (const char *) "^.......^",
           /* line */ (const char *) "  .....  ",
           /* line */ (const char *) "  .....  ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "     .   ",
           /* line */ (const char *) "     .   ",
           /* line */ (const char *) "     ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^       ",
           /* line */ (const char *) " .......  ",
           /* line */ (const char *) " .......  ",
           /* line */ (const char *) "^........^",
           /* line */ (const char *) "    ..    ",
           /* line */ (const char *) "    .     ",
           /* line */ (const char *) "    ^     ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^     ",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "    ^  ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^   ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "^....... ",
           /* line */ (const char *) "  ......^",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "    .    ",
           /* line */ (const char *) "    .    ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "  ^      ",
           /* line */ (const char *) "^....... ",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) " .......^",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^     ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "^.....^",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^   ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) "^..... ",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "    ^  ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^   ",
           /* line */ (const char *) "    .   ",
           /* line */ (const char *) "    .   ",
           /* line */ (const char *) "    .   ",
           /* line */ (const char *) "    ..  ",
           /* line */ (const char *) "^...... ",
           /* line */ (const char *) "   ....^",
           /* line */ (const char *) "    ..  ",
           /* line */ (const char *) "     ^  ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^    ",
           /* line */ (const char *) "     .    ",
           /* line */ (const char *) "     .    ",
           /* line */ (const char *) "     ..   ",
           /* line */ (const char *) "^........ ",
           /* line */ (const char *) "   ......^",
           /* line */ (const char *) "     ..   ",
           /* line */ (const char *) "      .   ",
           /* line */ (const char *) "      .   ",
           /* line */ (const char *) "      ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^      ",
           /* line */ (const char *) "     .      ",
           /* line */ (const char *) "  .......   ",
           /* line */ (const char *) "^..........^",
           /* line */ (const char *) "  .......   ",
           /* line */ (const char *) "     ..     ",
           /* line */ (const char *) "      .     ",
           /* line */ (const char *) "      ^     ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^  ",
           /* line */ (const char *) "^.....^",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "   ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^   ",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) " ...... ",
           /* line */ (const char *) "^......^",
           /* line */ (const char *) "   ..   ",
           /* line */ (const char *) "    ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^   ",
           /* line */ (const char *) "   .   ",
           /* line */ (const char *) "  ..   ",
           /* line */ (const char *) "^....  ",
           /* line */ (const char *) " .....^",
           /* line */ (const char *) "  ..   ",
           /* line */ (const char *) "  .    ",
           /* line */ (const char *) "  ^    ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "   ^  ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) " ....^",
           /* line */ (const char *) "^.... ",
           /* line */ (const char *) "  ..  ",
           /* line */ (const char *) "   ^  ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^  ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) " ..... ",
           /* line */ (const char *) "^.....^",
           /* line */ (const char *) "   ..  ",
           /* line */ (const char *) "    ^  ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "    ^   ",
           /* line */ (const char *) "    ..  ",
           /* line */ (const char *) "   .... ",
           /* line */ (const char *) "^......^",
           /* line */ (const char *) "    ..  ",
           /* line */ (const char *) "    ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) " ^       ",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) "^.......^",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "     ^   ",
           /* end */ nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           /* line */ (const char *) "     ^   ",
           /* line */ (const char *) " .......^",
           /* line */ (const char *) " ....... ",
           /* line */ (const char *) "^....... ",
           /* line */ (const char *) "    ..   ",
           /* line */ (const char *) "    ^    ",
           /* end */ nullptr);

}
