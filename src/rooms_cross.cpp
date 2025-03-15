//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_charmap.hpp"
#include "my_level.hpp"

//
// Rooms of type 'cross'
//
void rooms_cross(Gamep g)
{
  TRACE_NO_INDENT();

  /* clang-format off */

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"       ^   ",
           (const char *)" .........^",
           (const char *)"^......... ",
           (const char *)" ......... ",
           (const char *)" ......... ",
           (const char *)" ^         ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"        ^   ",
           (const char *)"  .........^",
           (const char *)"  ......... ",
           (const char *)"........... ",
           (const char *)"........... ",
           (const char *)"  ......... ",
           (const char *)"     ^      ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"      ^     ",
           (const char *)"      .     ",
           (const char *)"   .......  ",
           (const char *)"^..........^",
           (const char *)"   .......  ",
           (const char *)"   ^        ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"   ..........   ",
           (const char *)"   ..........   ",
           (const char *)"^..............^",
           (const char *)" ............   ",
           (const char *)"     ^          ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"       ^     ",
           (const char *)"^........... ",
           (const char *)"   .........^",
           (const char *)"   ......... ",
           (const char *)"        .    ",
           (const char *)"        .    ",
           (const char *)"        ^    ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"     ....   ",
           (const char *)"^..........^",
           (const char *)" ........   ",
           (const char *)" ........   ",
           (const char *)" ........   ",
           (const char *)" .          ",
           (const char *)" ^          ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"     ^  ",
           (const char *)"^...... ",
           (const char *)" ......^",
           (const char *)" ...... ",
           (const char *)" ...... ",
           (const char *)" ...... ",
           (const char *)"    ^   ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"        ......    ",
           (const char *)"        ......    ",
           (const char *)"        ......    ",
           (const char *)"..................",
           (const char *)"..................",
           (const char *)"                ^ ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"    ^                ",
           (const char *)" ...................^",
           (const char *)" ................... ",
           (const char *)"^................... ",
           (const char *)" ................... ",
           (const char *)"          ....       ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"   ......... ",
           (const char *)" ........... ",
           (const char *)"^........... ",
           (const char *)" ........... ",
           (const char *)" ...........^",
           (const char *)"   ......... ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"     ......    ",
           (const char *)"     ......    ",
           (const char *)".............  ",
           (const char *)"..............^",
           (const char *)".............  ",
           (const char *)"          ^    ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"       ^   ",
           (const char *)"       .   ",
           (const char *)"  .......  ",
           (const char *)"  .......  ",
           (const char *)"^.........^",
           (const char *)"    .....  ",
           (const char *)"       .   ",
           (const char *)"       .   ",
           (const char *)"       .   ",
           (const char *)"       ^   ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"     ^   ",
           (const char *)"     .   ",
           (const char *)"     ... ",
           (const char *)" ....... ",
           (const char *)" ....... ",
           (const char *)" .......^",
           (const char *)"^....... ",
           (const char *)"     ... ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"          ^     ",
           (const char *)"^.............. ",
           (const char *)" .............. ",
           (const char *)" ..............^",
           (const char *)" .............. ",
           (const char *)"  ^             ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"         ^        ",
           (const char *)"         .        ",
           (const char *)"^..........       ",
           (const char *)"  ............    ",
           (const char *)"  ...............^",
           (const char *)"  ............    ",
           (const char *)"     ^            ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"       ......      ",
           (const char *)"       ......      ",
           (const char *)"...................",
           (const char *)"...................",
           (const char *)"       ^           ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"         ^        ",
           (const char *)"         .        ",
           (const char *)"       .......... ",
           (const char *)"       .......... ",
           (const char *)"..................",
           (const char *)"..................",
           (const char *)"       .......... ",
           (const char *)"         .        ",
           (const char *)"         ^        ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"         ^    ",
           (const char *)"   .........  ",
           (const char *)"   ...........",
           (const char *)"^.............",
           (const char *)"   ...........",
           (const char *)"     ^        ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"   .....^",
           (const char *)"......   ",
           (const char *)"......   ",
           (const char *)"......   ",
           (const char *)"   ...   ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)" .......... ",
           (const char *)" .......... ",
           (const char *)"...........^",
           (const char *)"........... ",
           (const char *)"........... ",
           (const char *)"........... ",
           (const char *)"       ^    ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"          ^    ",
           (const char *)"       .....   ",
           (const char *)"^.............^",
           (const char *)" ............. ",
           (const char *)"       .....   ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"          ^   ",
           (const char *)"    .........^",
           (const char *)"^............ ",
           (const char *)" ............ ",
           (const char *)" ............ ",
           (const char *)" ............ ",
           (const char *)"       ^      ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"        ^   ",
           (const char *)"        .   ",
           (const char *)"  ........  ",
           (const char *)"^..........^",
           (const char *)"    ......  ",
           (const char *)"       ^    ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"                 ^     ",
           (const char *)"                 .     ",
           (const char *)"    ..................^",
           (const char *)"^....................  ",
           (const char *)"         ...........   ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"           ^    ",
           (const char *)"      ......... ",
           (const char *)"      ......... ",
           (const char *)"      ......... ",
           (const char *)"      .........^",
           (const char *)"............... ",
           (const char *)"............... ",
           (const char *)"             ^  ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"      ^     ",
           (const char *)" ........   ",
           (const char *)"^.......... ",
           (const char *)" ..........^",
           (const char *)" .......... ",
           (const char *)"      ^     ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"    ^    ",
           (const char *)" ....... ",
           (const char *)"^....... ",
           (const char *)" .......^",
           (const char *)" ....... ",
           (const char *)"  ...... ",
           (const char *)"  .      ",
           (const char *)"  ^      ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"   ^    ",
           (const char *)" ...... ",
           (const char *)" ...... ",
           (const char *)"....... ",
           (const char *)"....... ",
           (const char *)".......^",
           (const char *)" ...... ",
           (const char *)"    ^   ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"   ^     ",
           (const char *)"^....    ",
           (const char *)" ........",
           (const char *)" ........",
           (const char *)"  .......",
           (const char *)"      ^  ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"   ^                 ",
           (const char *)"^...............     ",
           (const char *)"   .................^",
           (const char *)"   .............     ",
           (const char *)"   .............     ",
           (const char *)"   ^                 ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"     ^       ",
           (const char *)"   .........^",
           (const char *)"............ ",
           (const char *)"............ ",
           (const char *)"............ ",
           (const char *)"       ^     ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"   ^              ",
           (const char *)" ................ ",
           (const char *)" ................ ",
           (const char *)"^................^",
           (const char *)" ................ ",
           (const char *)"          ^       ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"      ^          ",
           (const char *)"     ........... ",
           (const char *)"     ........... ",
           (const char *)"     ........... ",
           (const char *)" ................",
           (const char *)"^................",
           (const char *)"     ........... ",
           (const char *)"               ^ ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"               ^  ",
           (const char *)"       .........  ",
           (const char *)"       .........  ",
           (const char *)"^................^",
           (const char *)" ................ ",
           (const char *)"   ^              ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"        ^       ",
           (const char *)"   ............^",
           (const char *)"   ..........   ",
           (const char *)"   ..........   ",
           (const char *)".............   ",
           (const char *)".............   ",
           (const char *)" .              ",
           (const char *)" .              ",
           (const char *)" ^              ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"      ^              ",
           (const char *)"^................... ",
           (const char *)" ...................^",
           (const char *)" ................... ",
           (const char *)" ................... ",
           (const char *)"         ......      ",
           (const char *)"         ^           ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"               ^     ",
           (const char *)"         .......     ",
           (const char *)"    ...............  ",
           (const char *)"^...................^",
           (const char *)"    ...............  ",
           (const char *)"         .......     ",
           (const char *)"               .     ",
           (const char *)"               ^     ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"         ^   ",
           (const char *)"         .   ",
           (const char *)"       ....  ",
           (const char *)"^...........^",
           (const char *)"    .......  ",
           (const char *)"       ....  ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"     ........    ",
           (const char *)"     ...........^",
           (const char *)".............    ",
           (const char *)".............    ",
           (const char *)"    ^            ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"      ^      ",
           (const char *)"    ........^",
           (const char *)"^..........  ",
           (const char *)"   ........  ",
           (const char *)"   ........  ",
           (const char *)"      ^      ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"       ^        ",
           (const char *)"  .............^",
           (const char *)"^...........    ",
           (const char *)"  ..........    ",
           (const char *)"       .        ",
           (const char *)"       ^        ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"  ^      ",
           (const char *)" ....... ",
           (const char *)" ....... ",
           (const char *)" .......^",
           (const char *)"........ ",
           (const char *)"........ ",
           (const char *)"^        ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"         ^   ",
           (const char *)"         .   ",
           (const char *)" ..........  ",
           (const char *)" ..........  ",
           (const char *)"^...........^",
           (const char *)" ..........  ",
           (const char *)" ..........  ",
           (const char *)"     ^       ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"          ^    ",
           (const char *)"          .    ",
           (const char *)"      .....    ",
           (const char *)"   .........   ",
           (const char *)"   ...........^",
           (const char *)"^...........   ",
           (const char *)"      .....    ",
           (const char *)"         ^     ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"             ^      ",
           (const char *)"            ...     ",
           (const char *)"            ...     ",
           (const char *)"^...................",
           (const char *)"  ..................",
           (const char *)"            ...     ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"    ^       ",
           (const char *)"  ......... ",
           (const char *)" ..........^",
           (const char *)"^.......... ",
           (const char *)"  ......... ",
           (const char *)"   ^        ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"     ^     ",
           (const char *)"   ....... ",
           (const char *)"   ....... ",
           (const char *)"   .......^",
           (const char *)".......... ",
           (const char *)".......... ",
           (const char *)"   ....... ",
           (const char *)"     ^     ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"  ^                  ",
           (const char *)"^................... ",
           (const char *)" ...................^",
           (const char *)" ................... ",
           (const char *)" ................... ",
           (const char *)"         .......     ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"         ...      ",
           (const char *)"         ...      ",
           (const char *)".................^",
           (const char *)"................. ",
           (const char *)"................. ",
           (const char *)"         ...      ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"       ^  ",
           (const char *)" ........ ",
           (const char *)"^.........",
           (const char *)" .........",
           (const char *)"    ......",
           (const char *)"    ^     ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"     ^     ",
           (const char *)" ......... ",
           (const char *)" ......... ",
           (const char *)"^.........^",
           (const char *)" ......... ",
           (const char *)" ......... ",
           (const char *)"     ^     ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"      ^            ",
           (const char *)"     ...........   ",
           (const char *)"     ...........   ",
           (const char *)".................. ",
           (const char *)"..................^",
           (const char *)"     ...........   ",
           (const char *)"        ^          ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"           ^   ",
           (const char *)" ............. ",
           (const char *)"^............. ",
           (const char *)" ............. ",
           (const char *)" .............^",
           (const char *)"     .......   ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)" ^         ",
           (const char *)"^.........^",
           (const char *)" ......... ",
           (const char *)" ......... ",
           (const char *)"     ..... ",
           (const char *)"      ^    ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"      ..........   ",
           (const char *)"..................^",
           (const char *)".................. ",
           (const char *)"          ^        ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"        ^                ",
           (const char *)"    ..................   ",
           (const char *)"^.......................^",
           (const char *)"    ..................   ",
           (const char *)"          ^              ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"   ^                ",
           (const char *)"^..................^",
           (const char *)" .................. ",
           (const char *)" .................. ",
           (const char *)" .................. ",
           (const char *)"               ^    ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"           ^   ",
           (const char *)"           .   ",
           (const char *)"       ......  ",
           (const char *)"       ......  ",
           (const char *)"       ......  ",
           (const char *)"       ......  ",
           (const char *)"^..............",
           (const char *)"   ............",
           (const char *)"    .          ",
           (const char *)"    ^          ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"            ^     ",
           (const char *)" ................^",
           (const char *)"^................ ",
           (const char *)" ................ ",
           (const char *)" ................ ",
           (const char *)"       ^          ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"       ^   ",
           (const char *)"     ..... ",
           (const char *)"     .....^",
           (const char *)".......... ",
           (const char *)".......... ",
           (const char *)"      ^    ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)" ^       ",
           (const char *)" .......^",
           (const char *)" ......  ",
           (const char *)".......  ",
           (const char *)".......  ",
           (const char *)" ......  ",
           (const char *)"  ^      ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"              ^    ",
           (const char *)" ................. ",
           (const char *)"^.................^",
           (const char *)" ................. ",
           (const char *)"            ^      ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"       .... ",
           (const char *)"       .... ",
           (const char *)"       .... ",
           (const char *)"............",
           (const char *)"............",
           (const char *)"     ^      ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"         ^  ",
           (const char *)"    ......  ",
           (const char *)"    ......  ",
           (const char *)"    ......  ",
           (const char *)" ...........",
           (const char *)"^...........",
           (const char *)"    ......  ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"        ^         ",
           (const char *)"   .............  ",
           (const char *)"^...............  ",
           (const char *)"   .............  ",
           (const char *)"   ..............^",
           (const char *)"        .....     ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"  ^           ",
           (const char *)"  .           ",
           (const char *)" ............^",
           (const char *)" ..........   ",
           (const char *)" ..........   ",
           (const char *)"...........   ",
           (const char *)"...........   ",
           (const char *)"    .         ",
           (const char *)"    .         ",
           (const char *)"    ^         ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"       ^      ",
           (const char *)"       .      ",
           (const char *)"^...........  ",
           (const char *)"   ..........^",
           (const char *)"   .........  ",
           (const char *)"      .       ",
           (const char *)"      ^       ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"   ^            ",
           (const char *)"^............   ",
           (const char *)" .............. ",
           (const char *)" ..............^",
           (const char *)" .............. ",
           (const char *)" ^              ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"             ^    ",
           (const char *)" ................^",
           (const char *)" ................ ",
           (const char *)"^................ ",
           (const char *)" ................ ",
           (const char *)"         ....     ",
           (const char *)"         ^        ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"            ^     ",
           (const char *)"            .     ",
           (const char *)"     ..........   ",
           (const char *)"^..............   ",
           (const char *)"     ..........   ",
           (const char *)"     ..........   ",
           (const char *)"     ............^",
           (const char *)"     ..........   ",
           (const char *)"          .       ",
           (const char *)"          ^       ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"            ^      ",
           (const char *)"           ...     ",
           (const char *)"^................. ",
           (const char *)" .................^",
           (const char *)" ................. ",
           (const char *)" ................. ",
           (const char *)"           ...     ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"      ^      ",
           (const char *)" ........... ",
           (const char *)" ........... ",
           (const char *)"^...........^",
           (const char *)" ........... ",
           (const char *)" ........... ",
           (const char *)"         ^   ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"        ^  ",
           (const char *)" ......... ",
           (const char *)"^.........^",
           (const char *)" ......... ",
           (const char *)"     ...   ",
           (const char *)"       ^   ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"     ^      ",
           (const char *)"     .      ",
           (const char *)"     .      ",
           (const char *)"   .......  ",
           (const char *)"   .......  ",
           (const char *)"^..........^",
           (const char *)" .........  ",
           (const char *)"       .    ",
           (const char *)"       ^    ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"   ^     ",
           (const char *)" ......  ",
           (const char *)" .......^",
           (const char *)" ....... ",
           (const char *)"^....... ",
           (const char *)"    .... ",
           (const char *)"      ^  ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"    ^        ",
           (const char *)"  .......... ",
           (const char *)"  .......... ",
           (const char *)"  .......... ",
           (const char *)"  .......... ",
           (const char *)"............^",
           (const char *)"............ ",
           (const char *)" ^           ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"      ^     ",
           (const char *)" ..........^",
           (const char *)" .......... ",
           (const char *)"^.......... ",
           (const char *)" .......... ",
           (const char *)" .......... ",
           (const char *)"         ^  ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"    ^  ",
           (const char *)" ..... ",
           (const char *)"^..... ",
           (const char *)" .....^",
           (const char *)" ..... ",
           (const char *)" ^     ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"         ^       ",
           (const char *)"     ...........^",
           (const char *)" ............... ",
           (const char *)"^............... ",
           (const char *)" ............... ",
           (const char *)" ............... ",
           (const char *)"   .             ",
           (const char *)"   ^             ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"          ...    ",
           (const char *)"^.............   ",
           (const char *)"    ............^",
           (const char *)"          ...    ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"  ^           ",
           (const char *)"  ........... ",
           (const char *)"  ........... ",
           (const char *)"  ........... ",
           (const char *)".............^",
           (const char *)"............. ",
           (const char *)"  ........... ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"         ^          ",
           (const char *)"^.................  ",
           (const char *)" ..................^",
           (const char *)" .................  ",
           (const char *)"         ^          ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"      ^       ",
           (const char *)"  ........... ",
           (const char *)"  ........... ",
           (const char *)"^............^",
           (const char *)"  ........... ",
           (const char *)"    ........  ",
           (const char *)"      ^       ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"       ....... ",
           (const char *)"       ....... ",
           (const char *)"..............^",
           (const char *)".............. ",
           (const char *)".............. ",
           (const char *)"       ....... ",
           (const char *)"       .       ",
           (const char *)"       ^       ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"         ^     ",
           (const char *)"       .....   ",
           (const char *)"   ...........^",
           (const char *)"   .........   ",
           (const char *)"   .........   ",
           (const char *)"^...........   ",
           (const char *)"       .....   ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"  ^       ",
           (const char *)" ......   ",
           (const char *)" ......   ",
           (const char *)"^........ ",
           (const char *)" ........^",
           (const char *)"     .... ",
           (const char *)"      ^   ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"    ^        ",
           (const char *)"    ......   ",
           (const char *)"    ......   ",
           (const char *)"    ......   ",
           (const char *)" ........... ",
           (const char *)"^...........^",
           (const char *)" ........... ",
           (const char *)"    ^        ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"    ^         ",
           (const char *)"  ........... ",
           (const char *)" ............ ",
           (const char *)"^............^",
           (const char *)" ............ ",
           (const char *)" ^            ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"         ^   ",
           (const char *)" ........... ",
           (const char *)"^........... ",
           (const char *)" ........... ",
           (const char *)" ...........^",
           (const char *)" ........... ",
           (const char *)" ........... ",
           (const char *)"       ^     ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"        ^  ",
           (const char *)" ......... ",
           (const char *)"..........^",
           (const char *)".......... ",
           (const char *)"  ^        ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"        ^           ",
           (const char *)"^..................^",
           (const char *)" .................. ",
           (const char *)" .................. ",
           (const char *)"        ......      ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"            ^  ",
           (const char *)"    .......... ",
           (const char *)"    .......... ",
           (const char *)"^............. ",
           (const char *)" .............^",
           (const char *)" ............. ",
           (const char *)"    .......... ",
           (const char *)"      ^        ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"      ^         ",
           (const char *)"^.............. ",
           (const char *)" ..............^",
           (const char *)" .............. ",
           (const char *)"        ....    ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"            ^        ",
           (const char *)" ................... ",
           (const char *)"^...................^",
           (const char *)" ................... ",
           (const char *)"          ......     ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"    .....   ",
           (const char *)"    .....   ",
           (const char *)"    .....   ",
           (const char *)" ..........^",
           (const char *)"^........   ",
           (const char *)" ........   ",
           (const char *)"       .    ",
           (const char *)"       ^    ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"     ....  ",
           (const char *)"^.........^",
           (const char *)" ......... ",
           (const char *)"    ^      ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"          ^     ",
           (const char *)"^.............  ",
           (const char *)"  .............^",
           (const char *)"  ............  ",
           (const char *)"  ............  ",
           (const char *)"          ^     ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"      ^     ",
           (const char *)"      .     ",
           (const char *)"^.......... ",
           (const char *)"     ......^",
           (const char *)"     ...... ",
           (const char *)"        ^   ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"         ^         ",
           (const char *)"        .......    ",
           (const char *)".................. ",
           (const char *)"..................^",
           (const char *)".................. ",
           (const char *)"   ^               ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)" .......^",
           (const char *)" ....... ",
           (const char *)"........ ",
           (const char *)"........ ",
           (const char *)" ....... ",
           (const char *)"   .     ",
           (const char *)"   ^     ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"   ^          ",
           (const char *)"^..........   ",
           (const char *)"   ..........^",
           (const char *)"   ........   ",
           (const char *)"      ^       ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"       ^         ",
           (const char *)"       .........^",
           (const char *)"^............... ",
           (const char *)" ............... ",
           (const char *)"   .             ",
           (const char *)"   ^             ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"       ^   ",
           (const char *)"    ...... ",
           (const char *)"    ......^",
           (const char *)"    ...... ",
           (const char *)"    ...... ",
           (const char *)".......... ",
           (const char *)".......... ",
           (const char *)"        ^  ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"    ^      ",
           (const char *)"    .      ",
           (const char *)"    .      ",
           (const char *)"   .....   ",
           (const char *)"^.........^",
           (const char *)"   ......  ",
           (const char *)"   ......  ",
           (const char *)"       ^   ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"         ^     ",
           (const char *)"  ...........  ",
           (const char *)"  ............^",
           (const char *)"^............  ",
           (const char *)"     ........  ",
           (const char *)"           .   ",
           (const char *)"           ^   ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"     ^     ",
           (const char *)" ......... ",
           (const char *)"^......... ",
           (const char *)" ..........",
           (const char *)" ..........",
           (const char *)" ..........",
           (const char *)"        ^  ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"       .........      ",
           (const char *)"...................   ",
           (const char *)".....................^",
           (const char *)"       .........      ",
           (const char *)"              ^       ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"         ^   ",
           (const char *)" ........... ",
           (const char *)" ...........^",
           (const char *)" ........... ",
           (const char *)" ........... ",
           (const char *)"............ ",
           (const char *)"............ ",
           (const char *)"       ^     ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"    ^     ",
           (const char *)" ........^",
           (const char *)" ........ ",
           (const char *)"^........ ",
           (const char *)" ........ ",
           (const char *)"    ..... ",
           (const char *)"     ^    ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"   ^        ",
           (const char *)"   .        ",
           (const char *)" ..........^",
           (const char *)" .........  ",
           (const char *)" .........  ",
           (const char *)"^.........  ",
           (const char *)"     ...    ",
           (const char *)"      .     ",
           (const char *)"      ^     ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"           ...      ",
           (const char *)"           ...      ",
           (const char *)" .................. ",
           (const char *)"^.................. ",
           (const char *)" ..................^",
           (const char *)" .................. ",
           (const char *)"              ^     ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"         ^             ",
           (const char *)"   ..................  ",
           (const char *)"   ..................  ",
           (const char *)"   ...................^",
           (const char *)"^....................  ",
           (const char *)"           .........   ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"         ^       ",
           (const char *)"      ..........^",
           (const char *)"................ ",
           (const char *)"................ ",
           (const char *)"      .......... ",
           (const char *)"         ^       ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"       ^        ",
           (const char *)"      .......   ",
           (const char *)"...............^",
           (const char *)"............... ",
           (const char *)"............... ",
           (const char *)"............... ",
           (const char *)"          ^     ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"     ....  ",
           (const char *)"     ....  ",
           (const char *)"^..........",
           (const char *)"  .........",
           (const char *)"     .     ",
           (const char *)"     ^     ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"             ^     ",
           (const char *)" .................^",
           (const char *)"^................. ",
           (const char *)" ................. ",
           (const char *)" ................. ",
           (const char *)"       ^           ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"          ^      ",
           (const char *)"     ........... ",
           (const char *)"     ........... ",
           (const char *)"................^",
           (const char *)"................ ",
           (const char *)"................ ",
           (const char *)"     ........... ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"          ^       ",
           (const char *)"       ........   ",
           (const char *)"       ........   ",
           (const char *)"^.................",
           (const char *)" .................",
           (const char *)"  ^               ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"      ^         ",
           (const char *)"^..............^",
           (const char *)"  ............  ",
           (const char *)"  ............  ",
           (const char *)"  ............  ",
           (const char *)"          .     ",
           (const char *)"          ^     ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)" ....     ",
           (const char *)" ....     ",
           (const char *)" ........ ",
           (const char *)"^........^",
           (const char *)" ........ ",
           (const char *)"  ^       ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"        ^   ",
           (const char *)"        .   ",
           (const char *)"  ........  ",
           (const char *)"  ........  ",
           (const char *)"  .........^",
           (const char *)"^.........  ",
           (const char *)"  ........  ",
           (const char *)"        ^   ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"             ^      ",
           (const char *)"          .....     ",
           (const char *)"          .....     ",
           (const char *)"..................  ",
           (const char *)"...................^",
           (const char *)"..................  ",
           (const char *)"        .           ",
           (const char *)"        ^           ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"            ....   ",
           (const char *)"     .............^",
           (const char *)"     ............  ",
           (const char *)"^................  ",
           (const char *)"            ....   ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"              ^     ",
           (const char *)"  ...............   ",
           (const char *)"^................   ",
           (const char *)"  .................^",
           (const char *)"  ...............   ",
           (const char *)"          .         ",
           (const char *)"          ^         ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"    ^    ",
           (const char *)"  ......^",
           (const char *)"  ...... ",
           (const char *)"^....... ",
           (const char *)" ....... ",
           (const char *)"    ^    ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"     ^          ",
           (const char *)"     ......     ",
           (const char *)"     ......     ",
           (const char *)"     ......     ",
           (const char *)"     ......     ",
           (const char *)"...............^",
           (const char *)"............    ",
           (const char *)"^               ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"      ^             ",
           (const char *)"^.................. ",
           (const char *)" ..................^",
           (const char *)" .................. ",
           (const char *)"        .........   ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"       ........ ",
           (const char *)"^...............",
           (const char *)" ...............",
           (const char *)"   ^            ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"   ^            ",
           (const char *)"^..............^",
           (const char *)" .............. ",
           (const char *)" .............. ",
           (const char *)"        ......  ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"           ^       ",
           (const char *)"          ...      ",
           (const char *)"^.................^",
           (const char *)" ................. ",
           (const char *)"        ^          ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"            ^   ",
           (const char *)"^.............. ",
           (const char *)" .............. ",
           (const char *)" ..............^",
           (const char *)" .............. ",
           (const char *)"      ^         ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"         ........    ",
           (const char *)"^...................^",
           (const char *)" ..................  ",
           (const char *)"  ^                  ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"    ^     ",
           (const char *)" ........^",
           (const char *)"^........ ",
           (const char *)" ........ ",
           (const char *)" ........ ",
           (const char *)"    ^     ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"         .......   ",
           (const char *)"^.................^",
           (const char *)" ................. ",
           (const char *)"         .......   ",
           (const char *)"          ^        ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"       ^      ",
           (const char *)"  ........... ",
           (const char *)"  ...........^",
           (const char *)"............. ",
           (const char *)"............. ",
           (const char *)"............. ",
           (const char *)"  ........... ",
           (const char *)"   ^          ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"        ^            ",
           (const char *)"        .........    ",
           (const char *)"        .........    ",
           (const char *)"        .........    ",
           (const char *)"        .........    ",
           (const char *)"^...................^",
           (const char *)" ................... ",
           (const char *)"                  ^  ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"     ^        ",
           (const char *)"^............^",
           (const char *)"  ..........  ",
           (const char *)"  ..........  ",
           (const char *)"  ..........  ",
           (const char *)"         ^    ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"          ^    ",
           (const char *)"     ......    ",
           (const char *)"     ......    ",
           (const char *)".............  ",
           (const char *)"..............^",
           (const char *)".............  ",
           (const char *)"         ^     ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"             ^    ",
           (const char *)"    ...........   ",
           (const char *)"^................^",
           (const char *)"    ...........   ",
           (const char *)"    ...........   ",
           (const char *)"    .             ",
           (const char *)"    ^             ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"          ^   ",
           (const char *)"  ........... ",
           (const char *)"  ...........^",
           (const char *)"  ........... ",
           (const char *)"............. ",
           (const char *)"............. ",
           (const char *)"............. ",
           (const char *)"           ^  ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"         ...     ",
           (const char *)"         ...     ",
           (const char *)"................ ",
           (const char *)"................^",
           (const char *)"         ...     ",
           (const char *)"         ^       ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"          ^     ",
           (const char *)"          .     ",
           (const char *)"    ...........^",
           (const char *)"    ..........  ",
           (const char *)"..............  ",
           (const char *)"..............  ",
           (const char *)"..............  ",
           (const char *)"    ..........  ",
           (const char *)"      ^         ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"       ^     ",
           (const char *)"    ........ ",
           (const char *)"    ........ ",
           (const char *)"^............",
           (const char *)" ............",
           (const char *)" ............",
           (const char *)"    ........ ",
           (const char *)"     ^       ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"   ......      ",
           (const char *)"^.............^",
           (const char *)"   ........... ",
           (const char *)"    .......... ",
           (const char *)"         ^     ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"      ^       ",
           (const char *)"  ........... ",
           (const char *)"  ...........^",
           (const char *)"^............ ",
           (const char *)"  ........... ",
           (const char *)"      ....... ",
           (const char *)"      ^       ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"    .......  ",
           (const char *)"............^",
           (const char *)"...........  ",
           (const char *)"...........  ",
           (const char *)"...........  ",
           (const char *)"    .......  ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"      ^          ",
           (const char *)" ............... ",
           (const char *)" ...............^",
           (const char *)"^............... ",
           (const char *)" ............... ",
           (const char *)"        .....    ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"     ^  ",
           (const char *)"^...... ",
           (const char *)" ......^",
           (const char *)" ...... ",
           (const char *)" ...... ",
           (const char *)"   ^    ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"      .......  ",
           (const char *)"      ........^",
           (const char *)"      .......  ",
           (const char *)"^............  ",
           (const char *)"    .........  ",
           (const char *)"      .......  ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"     ^          ",
           (const char *)"    .........   ",
           (const char *)"    .........   ",
           (const char *)"    .........   ",
           (const char *)"............... ",
           (const char *)"...............^",
           (const char *)"    .........   ",
           (const char *)"      ^         ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"       ^         ",
           (const char *)"      ........   ",
           (const char *)"      ........   ",
           (const char *)"      ........   ",
           (const char *)"      ........   ",
           (const char *)"^...............^",
           (const char *)"   ...........   ",
           (const char *)"        ^        ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"       .... ",
           (const char *)"       .... ",
           (const char *)"       ....^",
           (const char *)"^.......... ",
           (const char *)" .......... ",
           (const char *)"       ^    ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"           ^   ",
           (const char *)" ............. ",
           (const char *)"^............. ",
           (const char *)" .............^",
           (const char *)"       ....... ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"       ^          ",
           (const char *)"       .          ",
           (const char *)"   ............   ",
           (const char *)"   ..............^",
           (const char *)"^...............  ",
           (const char *)"     ...........  ",
           (const char *)"             .    ",
           (const char *)"             ^    ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"   ^   ",
           (const char *)"   ... ",
           (const char *)"   ... ",
           (const char *)"   ... ",
           (const char *)" ..... ",
           (const char *)"^.....^",
           (const char *)" ..... ",
           (const char *)"    ^  ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"               ^  ",
           (const char *)" ................ ",
           (const char *)" ................ ",
           (const char *)" ................ ",
           (const char *)"^................^",
           (const char *)"          .....   ",
           (const char *)"             ^    ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"        ^     ",
           (const char *)"    ........  ",
           (const char *)"    ........  ",
           (const char *)"    ........  ",
           (const char *)"    ........  ",
           (const char *)".............^",
           (const char *)"............. ",
           (const char *)"      ^       ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"   ^       ",
           (const char *)" ......... ",
           (const char *)" ......... ",
           (const char *)"..........^",
           (const char *)".......... ",
           (const char *)"      ^    ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"          ^         ",
           (const char *)"        ........    ",
           (const char *)"        ........    ",
           (const char *)"        ........    ",
           (const char *)"        ........    ",
           (const char *)"^...................",
           (const char *)" ...................",
           (const char *)"           ^        ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"     ^       ",
           (const char *)" ........... ",
           (const char *)" ...........^",
           (const char *)"^........... ",
           (const char *)" ........... ",
           (const char *)"       ..... ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"  ^        ",
           (const char *)" .......   ",
           (const char *)"..........^",
           (const char *)".......... ",
           (const char *)".......... ",
           (const char *)"   ^       ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"    ....^",
           (const char *)"^......  ",
           (const char *)" ......  ",
           (const char *)" ......  ",
           (const char *)" ......  ",
           (const char *)"    ...  ",
           (const char *)"     .   ",
           (const char *)"     ^   ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"        ^           ",
           (const char *)"^.................  ",
           (const char *)"  ................  ",
           (const char *)"  .................^",
           (const char *)"  ................  ",
           (const char *)"          .......   ",
           (const char *)"              .     ",
           (const char *)"              ^     ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"     ......... ",
           (const char *)"     .........^",
           (const char *)"     ......... ",
           (const char *)".............. ",
           (const char *)".............. ",
           (const char *)".............. ",
           (const char *)"   .           ",
           (const char *)"   ^           ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"           ^   ",
           (const char *)"       .......^",
           (const char *)"  ............ ",
           (const char *)"^............. ",
           (const char *)"  ............ ",
           (const char *)"  ............ ",
           (const char *)"        ^      ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"      ^             ",
           (const char *)"    ...............^",
           (const char *)"^..............     ",
           (const char *)"       ......       ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"         ^         ",
           (const char *)"         .         ",
           (const char *)"        ......     ",
           (const char *)"        ......     ",
           (const char *)"..................^",
           (const char *)"................   ",
           (const char *)"................   ",
           (const char *)"  .                ",
           (const char *)"  ^                ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"      ..........   ",
           (const char *)"      ............^",
           (const char *)"^...............   ",
           (const char *)"   .............   ",
           (const char *)"          ^        ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"          ^   ",
           (const char *)"^............ ",
           (const char *)" ............^",
           (const char *)" ............ ",
           (const char *)" ............ ",
           (const char *)"    ......... ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"    ^        ",
           (const char *)"^...........^",
           (const char *)"   .......   ",
           (const char *)"   .......   ",
           (const char *)"      ....   ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"         ^     ",
           (const char *)"      ........ ",
           (const char *)"^.............^",
           (const char *)" ............. ",
           (const char *)" ............. ",
           (const char *)" ............. ",
           (const char *)"     ^         ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"       ^      ",
           (const char *)"       .      ",
           (const char *)"   ......     ",
           (const char *)"  ...........^",
           (const char *)"^...........  ",
           (const char *)"  ..........  ",
           (const char *)"     .        ",
           (const char *)"     ^        ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"     ^  ",
           (const char *)" ...... ",
           (const char *)"^...... ",
           (const char *)" ......^",
           (const char *)" ...... ",
           (const char *)"   .... ",
           (const char *)"    ^   ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)" ^        ",
           (const char *)" .....    ",
           (const char *)"^........ ",
           (const char *)" ........^",
           (const char *)" ........ ",
           (const char *)"    ..... ",
           (const char *)"    ^     ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"     ^         ",
           (const char *)"   ..........  ",
           (const char *)"^.............^",
           (const char *)"     ........  ",
           (const char *)"     ^         ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"        ...   ",
           (const char *)"        ...   ",
           (const char *)"        ...   ",
           (const char *)"        ...   ",
           (const char *)"^.............",
           (const char *)" .............",
           (const char *)"  ^           ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"          ........   ",
           (const char *)"          ........   ",
           (const char *)"    .................",
           (const char *)"^....................",
           (const char *)"    .................",
           (const char *)"                   ^ ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"         ^    ",
           (const char *)"         .    ",
           (const char *)"  ........... ",
           (const char *)"  ........... ",
           (const char *)"  ........... ",
           (const char *)"  ........... ",
           (const char *)".............^",
           (const char *)"............. ",
           (const char *)"           ^  ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"      ^   ",
           (const char *)"      .   ",
           (const char *)" .......  ",
           (const char *)" .......  ",
           (const char *)".........^",
           (const char *)"........  ",
           (const char *)"........  ",
           (const char *)"      .   ",
           (const char *)"      ^   ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)" ^         ",
           (const char *)" .         ",
           (const char *)"^....      ",
           (const char *)" ....      ",
           (const char *)" ........  ",
           (const char *)" .........^",
           (const char *)"  .......  ",
           (const char *)"   .       ",
           (const char *)"   .       ",
           (const char *)"   .       ",
           (const char *)"   ^       ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)" ^    ",
           (const char *)" .... ",
           (const char *)" .... ",
           (const char *)".....^",
           (const char *)"..... ",
           (const char *)"   ^  ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"       ^   ",
           (const char *)"^......... ",
           (const char *)" ......... ",
           (const char *)" ......... ",
           (const char *)" .........^",
           (const char *)" ......... ",
           (const char *)"      ^    ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"   ^          ",
           (const char *)"   .........  ",
           (const char *)".............^",
           (const char *)"............. ",
           (const char *)"............. ",
           (const char *)"............. ",
           (const char *)"   .........  ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"   ^         ",
           (const char *)" ...........^",
           (const char *)"^........... ",
           (const char *)" ........... ",
           (const char *)" ........... ",
           (const char *)" ........... ",
           (const char *)"  ^          ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"        ........ ",
           (const char *)"        ........ ",
           (const char *)"  ...............",
           (const char *)"^................",
           (const char *)"  ...............",
           (const char *)"         ^       ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"         ^      ",
           (const char *)"  ............. ",
           (const char *)"^.............. ",
           (const char *)"  .............^",
           (const char *)"  ............. ",
           (const char *)"    ........... ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"       ..........  ",
           (const char *)"       ..........  ",
           (const char *)"       ..........  ",
           (const char *)"       ..........  ",
           (const char *)"..................^",
           (const char *)".................. ",
           (const char *)"                ^  ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"            .....    ",
           (const char *)"   .................^",
           (const char *)"^..................  ",
           (const char *)"   ................  ",
           (const char *)"            .....    ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"    ........ ",
           (const char *)"    ........ ",
           (const char *)"    ........^",
           (const char *)"    ........ ",
           (const char *)"............ ",
           (const char *)"............ ",
           (const char *)"     ^       ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"            ...     ",
           (const char *)"            ...     ",
           (const char *)"  ..................",
           (const char *)"  ..................",
           (const char *)"^...................",
           (const char *)"            ...     ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"     ^      ",
           (const char *)"^.........  ",
           (const char *)" ..........^",
           (const char *)" .......... ",
           (const char *)" .......... ",
           (const char *)"        ^   ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"       ...........    ",
           (const char *)"       ...........    ",
           (const char *)"^...................  ",
           (const char *)"  ...................^",
           (const char *)"  ..................  ",
           (const char *)"         ^            ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"            ^   ",
           (const char *)"    ........... ",
           (const char *)" ..............^",
           (const char *)"^.............. ",
           (const char *)"    ........... ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"           ^     ",
           (const char *)"^...............^",
           (const char *)" ............... ",
           (const char *)" ............... ",
           (const char *)" ............... ",
           (const char *)"         ^       ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"                ^      ",
           (const char *)"                .      ",
           (const char *)"   ..................  ",
           (const char *)"^.....................^",
           (const char *)"         ..........    ",
           (const char *)"             ^         ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"       ^       ",
           (const char *)" ............. ",
           (const char *)"^............. ",
           (const char *)" .............^",
           (const char *)"      ......   ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"          ^         ",
           (const char *)"        ........    ",
           (const char *)"^..................^",
           (const char *)" .................. ",
           (const char *)"        ^           ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"   ^     ",
           (const char *)"   ..... ",
           (const char *)"   ..... ",
           (const char *)"   .....^",
           (const char *)"........ ",
           (const char *)"........ ",
           (const char *)"........ ",
           (const char *)"      ^  ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"   ^    ",
           (const char *)" ...... ",
           (const char *)"^......^",
           (const char *)" ...... ",
           (const char *)"   ^    ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)" ^         ",
           (const char *)" .         ",
           (const char *)" ......    ",
           (const char *)".......    ",
           (const char *)"..........^",
           (const char *)" ......    ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"          .....     ",
           (const char *)"          .....     ",
           (const char *)" .................. ",
           (const char *)"^.................. ",
           (const char *)" ..................^",
           (const char *)"          .....     ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)" .......... ",
           (const char *)" .......... ",
           (const char *)"...........^",
           (const char *)"........... ",
           (const char *)"........... ",
           (const char *)"........... ",
           (const char *)" .          ",
           (const char *)" ^          ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"            ^      ",
           (const char *)"  ................^",
           (const char *)"^...............   ",
           (const char *)"  ..............   ",
           (const char *)"        .          ",
           (const char *)"        ^          ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"       .........  ",
           (const char *)"^................^",
           (const char *)"   .............  ",
           (const char *)"   .............  ",
           (const char *)"       .........  ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"         .......   ",
           (const char *)"         .......   ",
           (const char *)"...................",
           (const char *)"...................",
           (const char *)"...................",
           (const char *)"...................",
           (const char *)"              ^    ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"              ^          ",
           (const char *)"              .          ",
           (const char *)"^.......................^",
           (const char *)"     ................... ",
           (const char *)"              ...        ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"          ...     ",
           (const char *)"^................^",
           (const char *)"   ............   ",
           (const char *)"          ...     ",
           (const char *)"           .      ",
           (const char *)"           .      ",
           (const char *)"           ^      ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"       ......     ",
           (const char *)"       ......     ",
           (const char *)" ................^",
           (const char *)"^................ ",
           (const char *)" ................ ",
           (const char *)"       ......     ",
           (const char *)"        .         ",
           (const char *)"        ^         ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"        ^    ",
           (const char *)" ........... ",
           (const char *)"^...........^",
           (const char *)" ........... ",
           (const char *)" ........... ",
           (const char *)" ^           ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"           ^    ",
           (const char *)"    ..........  ",
           (const char *)"    ..........  ",
           (const char *)"    ..........  ",
           (const char *)"^..............^",
           (const char *)"    ..........  ",
           (const char *)"      .         ",
           (const char *)"      ^         ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"    ^              ",
           (const char *)"^................. ",
           (const char *)" .................^",
           (const char *)"        ....       ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"      ^          ",
           (const char *)" ...............^",
           (const char *)"^............... ",
           (const char *)" ............... ",
           (const char *)" ............... ",
           (const char *)"       ......    ",
           (const char *)"       ^         ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"               ^    ",
           (const char *)"           .....    ",
           (const char *)"^.................. ",
           (const char *)" ..................^",
           (const char *)"           .....    ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"     ^      ",
           (const char *)"     .      ",
           (const char *)"     .      ",
           (const char *)"^.........  ",
           (const char *)"  .........^",
           (const char *)"  ........  ",
           (const char *)"  ........  ",
           (const char *)"     ^      ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"             ^      ",
           (const char *)" ..................^",
           (const char *)" .................. ",
           (const char *)"^.................. ",
           (const char *)"       ...........  ",
           (const char *)"       ^            ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"    ........      ",
           (const char *)".................^",
           (const char *)"...............   ",
           (const char *)"   ^              ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"        ^           ",
           (const char *)"       ...........  ",
           (const char *)" .................  ",
           (const char *)" ..................^",
           (const char *)" .................  ",
           (const char *)"^.................  ",
           (const char *)"       ...........  ",
           (const char *)"            ^       ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"     ....    ",
           (const char *)" ........... ",
           (const char *)"^...........^",
           (const char *)" ........... ",
           (const char *)" ........... ",
           (const char *)"     ....    ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"           ^      ",
           (const char *)"        ....      ",
           (const char *)"  ..............  ",
           (const char *)"^................^",
           (const char *)"        ....      ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"  ^               ",
           (const char *)" ................ ",
           (const char *)" ................ ",
           (const char *)" ................ ",
           (const char *)"^................^",
           (const char *)"     ...........  ",
           (const char *)"      ^           ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"          ...        ",
           (const char *)"....................^",
           (const char *)"..................   ",
           (const char *)"          ...        ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"       ^       ",
           (const char *)"       ....    ",
           (const char *)"  ............^",
           (const char *)"^...........   ",
           (const char *)"  ..........   ",
           (const char *)"      ^        ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"         .....     ",
           (const char *)" ................. ",
           (const char *)" .................^",
           (const char *)"^................. ",
           (const char *)" ................. ",
           (const char *)"         .....     ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"      ^    ",
           (const char *)"      .    ",
           (const char *)"      ...  ",
           (const char *)"^.........^",
           (const char *)"  .......  ",
           (const char *)"  .......  ",
           (const char *)"  .        ",
           (const char *)"  .        ",
           (const char *)"  ^        ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"   ........   ",
           (const char *)"   ..........^",
           (const char *)"^..........   ",
           (const char *)" ..........   ",
           (const char *)"      .       ",
           (const char *)"      ^       ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"       ... ",
           (const char *)"       ... ",
           (const char *)"       ... ",
           (const char *)"       ... ",
           (const char *)"...........",
           (const char *)"...........",
           (const char *)".          ",
           (const char *)".          ",
           (const char *)"^          ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"        ^     ",
           (const char *)"    ......... ",
           (const char *)"............. ",
           (const char *)".............^",
           (const char *)"    ......... ",
           (const char *)"     ^        ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"          ^       ",
           (const char *)"     ..........   ",
           (const char *)"     ..........   ",
           (const char *)"     ..........   ",
           (const char *)".................^",
           (const char *)"................. ",
           (const char *)"    ^             ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"           ^           ",
           (const char *)"^..................... ",
           (const char *)"    ..................^",
           (const char *)"    .................. ",
           (const char *)"              ^        ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"    ^       ",
           (const char *)" ..........^",
           (const char *)" .......... ",
           (const char *)" .......... ",
           (const char *)" .......... ",
           (const char *)"^.......... ",
           (const char *)" .......... ",
           (const char *)"   ^        ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"     ^         ",
           (const char *)"^.............^",
           (const char *)" ............. ",
           (const char *)"     ......... ",
           (const char *)"           ^   ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"                 ^   ",
           (const char *)"^................... ",
           (const char *)"  ..................^",
           (const char *)"  .................. ",
           (const char *)"     ^               ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"      ^     ",
           (const char *)"    ......  ",
           (const char *)"    ......  ",
           (const char *)"^...........",
           (const char *)" ...........",
           (const char *)" ...........",
           (const char *)"          . ",
           (const char *)"          . ",
           (const char *)"          . ",
           (const char *)"          ^ ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"         ^     ",
           (const char *)" ............. ",
           (const char *)" ............. ",
           (const char *)" ............. ",
           (const char *)"^.............^",
           (const char *)"        ...    ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"     ........  ",
           (const char *)" .............^",
           (const char *)" ............. ",
           (const char *)"^............. ",
           (const char *)" ............. ",
           (const char *)"            ^  ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"         ^      ",
           (const char *)"         .      ",
           (const char *)"    ........    ",
           (const char *)"...............^",
           (const char *)"..............  ",
           (const char *)"..............  ",
           (const char *)"..............  ",
           (const char *)"          ^     ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"     ^          ",
           (const char *)" .............. ",
           (const char *)" ..............^",
           (const char *)"^.............. ",
           (const char *)" .............. ",
           (const char *)"     ^          ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"      ..... ",
           (const char *)"............",
           (const char *)"............",
           (const char *)"       ^    ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"          ^  ",
           (const char *)"^...........^",
           (const char *)" ........... ",
           (const char *)"   ......... ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"        ....     ",
           (const char *)"        ....     ",
           (const char *)"...............  ",
           (const char *)"................^",
           (const char *)"...............  ",
           (const char *)"     .           ",
           (const char *)"     ^           ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"    ^         ",
           (const char *)" ............ ",
           (const char *)" ............^",
           (const char *)"^............ ",
           (const char *)" ............ ",
           (const char *)" ^            ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"     ^              ",
           (const char *)" .................. ",
           (const char *)" .................. ",
           (const char *)"^..................^",
           (const char *)"         .......    ",
           (const char *)"         ^          ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"   ^   ",
           (const char *)" ..... ",
           (const char *)" .....^",
           (const char *)"^..... ",
           (const char *)" ..... ",
           (const char *)"   ^   ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"      ^      ",
           (const char *)"      .      ",
           (const char *)"      .      ",
           (const char *)"   ........  ",
           (const char *)"   ........  ",
           (const char *)"   ........  ",
           (const char *)"^...........^",
           (const char *)"   ........  ",
           (const char *)"         .   ",
           (const char *)"         ^   ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"      ....... ",
           (const char *)"      ....... ",
           (const char *)"^............^",
           (const char *)" ............ ",
           (const char *)" ............ ",
           (const char *)"      ....... ",
           (const char *)"        ^     ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"   ....... ",
           (const char *)"   .......^",
           (const char *)"   ....... ",
           (const char *)".......... ",
           (const char *)".......... ",
           (const char *)"       ^   ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"          ^    ",
           (const char *)"      ......   ",
           (const char *)"   .........   ",
           (const char *)"^.............^",
           (const char *)"      ......   ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"  ^              ",
           (const char *)"  .              ",
           (const char *)"  ...........    ",
           (const char *)"^............    ",
           (const char *)"  ..............^",
           (const char *)"  ...........    ",
           (const char *)"       ...       ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"  ^    ",
           (const char *)"  ....^",
           (const char *)"^..... ",
           (const char *)" ..... ",
           (const char *)" ..... ",
           (const char *)" ..... ",
           (const char *)"    ^  ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)" ^            ",
           (const char *)" ............ ",
           (const char *)" ............ ",
           (const char *)"^............^",
           (const char *)"  ........... ",
           (const char *)"      ^       ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"              ^  ",
           (const char *)"          .....  ",
           (const char *)"          .....  ",
           (const char *)"          .....  ",
           (const char *)"^................",
           (const char *)" ................",
           (const char *)"      ^          ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"      ^   ",
           (const char *)"^........ ",
           (const char *)" ........^",
           (const char *)" ........ ",
           (const char *)" ........ ",
           (const char *)" ........ ",
           (const char *)"    ^     ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"  ^       ",
           (const char *)" ........ ",
           (const char *)"^........ ",
           (const char *)" ........^",
           (const char *)" ........ ",
           (const char *)"   ...... ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"         ^     ",
           (const char *)"         ...   ",
           (const char *)" ............. ",
           (const char *)"^.............^",
           (const char *)" ............. ",
           (const char *)"         ...   ",
           (const char *)"         ^     ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"       ^     ",
           (const char *)"       .     ",
           (const char *)" ........... ",
           (const char *)"^...........^",
           (const char *)" ........... ",
           (const char *)"      ^      ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"            ^       ",
           (const char *)"  ...............   ",
           (const char *)"  ...............   ",
           (const char *)"^..................^",
           (const char *)"  ...............   ",
           (const char *)"     ^              ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"     ^    ",
           (const char *)"  .......^",
           (const char *)"  ....... ",
           (const char *)"^........ ",
           (const char *)" ........ ",
           (const char *)"  ^       ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"       ......... ",
           (const char *)"       ......... ",
           (const char *)"^................",
           (const char *)"   ..............",
           (const char *)"               ^ ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"    ^           ",
           (const char *)" .............. ",
           (const char *)" .............. ",
           (const char *)"^..............^",
           (const char *)" .............. ",
           (const char *)"       ......   ",
           (const char *)"          ^     ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)" ^         ",
           (const char *)" .......   ",
           (const char *)" .......   ",
           (const char *)" .........^",
           (const char *)"........   ",
           (const char *)"........   ",
           (const char *)" .         ",
           (const char *)" ^         ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"     ^      ",
           (const char *)"    ....    ",
           (const char *)"    .......^",
           (const char *)"........    ",
           (const char *)"........    ",
           (const char *)"........    ",
           (const char *)"........    ",
           (const char *)"^           ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"       ^  ",
           (const char *)"    ....  ",
           (const char *)" ........ ",
           (const char *)" ........^",
           (const char *)"^........ ",
           (const char *)"    ....  ",
           (const char *)"      ^   ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"  ..... ",
           (const char *)"  ..... ",
           (const char *)"  ..... ",
           (const char *)".......^",
           (const char *)"....... ",
           (const char *)"....... ",
           (const char *)"    ^   ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"       ^   ",
           (const char *)"   .......^",
           (const char *)"^......... ",
           (const char *)" ......... ",
           (const char *)"       ^   ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"   ....... ",
           (const char *)"   ....... ",
           (const char *)" ......... ",
           (const char *)"^.........^",
           (const char *)"   ....... ",
           (const char *)"       ^   ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"        ....       ",
           (const char *)".................. ",
           (const char *)"..................^",
           (const char *)".................. ",
           (const char *)".................. ",
           (const char *)"        ....       ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"      ^     ",
           (const char *)"   ......   ",
           (const char *)"   ......   ",
           (const char *)" ........   ",
           (const char *)"^..........^",
           (const char *)" ........   ",
           (const char *)"      ^     ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"                  ^     ",
           (const char *)"   ....................^",
           (const char *)"   ...................  ",
           (const char *)"   ...................  ",
           (const char *)"^.....................  ",
           (const char *)"         ..........     ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"                 ^   ",
           (const char *)" ................... ",
           (const char *)" ................... ",
           (const char *)" ................... ",
           (const char *)"^...................^",
           (const char *)"         .....       ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"       ...   ",
           (const char *)"............^",
           (const char *)"............ ",
           (const char *)"       ...   ",
           (const char *)"       ^     ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"        ^        ",
           (const char *)"        .        ",
           (const char *)"        ......   ",
           (const char *)"^................",
           (const char *)" ................",
           (const char *)"               . ",
           (const char *)"               . ",
           (const char *)"               ^ ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"          ^      ",
           (const char *)" ............... ",
           (const char *)" ............... ",
           (const char *)"^...............^",
           (const char *)"        .....    ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"    ... ",
           (const char *)"    ... ",
           (const char *)"    ...^",
           (const char *)"....... ",
           (const char *)"....... ",
           (const char *)"....... ",
           (const char *)" ^      ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"       .....    ",
           (const char *)"       .....    ",
           (const char *)"       .....    ",
           (const char *)"       .....    ",
           (const char *)"................",
           (const char *)"................",
           (const char *)"       ^        ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"     ^   ",
           (const char *)"     .   ",
           (const char *)"     .   ",
           (const char *)"    .... ",
           (const char *)"    .... ",
           (const char *)"    .... ",
           (const char *)"^........",
           (const char *)" ........",
           (const char *)" ........",
           (const char *)"       ^ ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"    .........  ",
           (const char *)"    .........  ",
           (const char *)"    .........  ",
           (const char *)"    ..........^",
           (const char *)".............  ",
           (const char *)".............  ",
           (const char *)"      ^        ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"            ...       ",
           (const char *)"            ...       ",
           (const char *)"            ...       ",
           (const char *)"^....................^",
           (const char *)"   ................   ",
           (const char *)"             ^        ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"        ^      ",
           (const char *)"        .      ",
           (const char *)"    .....      ",
           (const char *)"^............  ",
           (const char *)"  ............^",
           (const char *)"  ...........  ",
           (const char *)"  ...........  ",
           (const char *)"      ^        ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"   ........ ",
           (const char *)"   ........^",
           (const char *)"   ........ ",
           (const char *)"   ........ ",
           (const char *)"........... ",
           (const char *)"........... ",
           (const char *)"         ^  ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"         ^         ",
           (const char *)"         .         ",
           (const char *)"      ...........  ",
           (const char *)"      ...........  ",
           (const char *)"...................",
           (const char *)"...................",
           (const char *)"...................",
           (const char *)"              ^    ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"          ...      ",
           (const char *)"          ...      ",
           (const char *)"          ...      ",
           (const char *)"..................^",
           (const char *)".................. ",
           (const char *)"               ^   ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"      ^      ",
           (const char *)"      .      ",
           (const char *)"      .      ",
           (const char *)"   .......   ",
           (const char *)"^...........^",
           (const char *)"  ........   ",
           (const char *)"   .......   ",
           (const char *)"        ^    ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"          ^    ",
           (const char *)"          .    ",
           (const char *)"          .    ",
           (const char *)"   ........... ",
           (const char *)"   ...........^",
           (const char *)"   ........... ",
           (const char *)"^............. ",
           (const char *)"         ..... ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"          ^  ",
           (const char *)"    ........ ",
           (const char *)"............^",
           (const char *)"............ ",
           (const char *)"    ........ ",
           (const char *)"         ^   ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"     ^    ",
           (const char *)"     .... ",
           (const char *)"     .... ",
           (const char *)" ........^",
           (const char *)" ........ ",
           (const char *)"^........ ",
           (const char *)" ........ ",
           (const char *)" ^        ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"           ^      ",
           (const char *)" ................^",
           (const char *)"^................ ",
           (const char *)" ................ ",
           (const char *)"            ^     ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"              ^     ",
           (const char *)"  ...............   ",
           (const char *)"^................   ",
           (const char *)"  .................^",
           (const char *)"  ...............   ",
           (const char *)"    .               ",
           (const char *)"    ^               ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"       ^      ",
           (const char *)"      ......  ",
           (const char *)"      ......  ",
           (const char *)" .............",
           (const char *)"^.............",
           (const char *)" .............",
           (const char *)"        .     ",
           (const char *)"        ^     ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)" ^            ",
           (const char *)"^............ ",
           (const char *)" ............^",
           (const char *)"       .....  ",
           (const char *)"        ^     ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"          ....       ",
           (const char *)"....................^",
           (const char *)"..................   ",
           (const char *)"..................   ",
           (const char *)"..................   ",
           (const char *)"          ....       ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"         .........  ",
           (const char *)" .................. ",
           (const char *)" ..................^",
           (const char *)"^.................. ",
           (const char *)" .................. ",
           (const char *)"   ^                ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"      ^        ",
           (const char *)"      .        ",
           (const char *)"      .        ",
           (const char *)"   ........... ",
           (const char *)"...............",
           (const char *)"...............",
           (const char *)"     ^         ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"      ^  ",
           (const char *)"      .  ",
           (const char *)"     ...^",
           (const char *)"     ... ",
           (const char *)"     ... ",
           (const char *)"     ... ",
           (const char *)"........ ",
           (const char *)"........ ",
           (const char *)"^        ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"  ^        ",
           (const char *)"  .......  ",
           (const char *)"  .......  ",
           (const char *)"  .......  ",
           (const char *)"  ........^",
           (const char *)".........  ",
           (const char *)".........  ",
           (const char *)"      .    ",
           (const char *)"      ^    ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"     ^         ",
           (const char *)"     ......    ",
           (const char *)".............. ",
           (const char *)"..............^",
           (const char *)"     ......    ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"      ^        ",
           (const char *)" ..........    ",
           (const char *)" ..........    ",
           (const char *)"^.............^",
           (const char *)" ............. ",
           (const char *)"     ......... ",
           (const char *)"            ^  ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"   ^                 ",
           (const char *)"   .                 ",
           (const char *)"   .................^",
           (const char *)"^.................   ",
           (const char *)"   ...............   ",
           (const char *)"     ^               ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"        ^      ",
           (const char *)"        .      ",
           (const char *)"   .......     ",
           (const char *)"   .......     ",
           (const char *)"   ...........^",
           (const char *)"..........     ",
           (const char *)"..........     ",
           (const char *)"   .......     ",
           (const char *)"       .       ",
           (const char *)"       .       ",
           (const char *)"       ^       ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"  ^           ",
           (const char *)"  .           ",
           (const char *)"  .           ",
           (const char *)" ...........  ",
           (const char *)" ...........  ",
           (const char *)"^...........  ",
           (const char *)" ............^",
           (const char *)" ...........  ",
           (const char *)" ...........  ",
           (const char *)"       .      ",
           (const char *)"       ^      ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"        ..........   ",
           (const char *)" ...................^",
           (const char *)"^................... ",
           (const char *)" ................... ",
           (const char *)"          ^          ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"           ^    ",
           (const char *)"          ...   ",
           (const char *)"          ...   ",
           (const char *)"................",
           (const char *)"................",
           (const char *)"................",
           (const char *)"         .      ",
           (const char *)"         ^      ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"       ...  ",
           (const char *)"       ...  ",
           (const char *)"       ...  ",
           (const char *)"...........^",
           (const char *)"........... ",
           (const char *)"^           ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"  .....^",
           (const char *)"  ....  ",
           (const char *)"  ....  ",
           (const char *)"  ....  ",
           (const char *)"......  ",
           (const char *)"......  ",
           (const char *)".       ",
           (const char *)".       ",
           (const char *)"^       ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)" ^      ",
           (const char *)" ...... ",
           (const char *)"^...... ",
           (const char *)" ......^",
           (const char *)" ...... ",
           (const char *)" ...... ",
           (const char *)" ...... ",
           (const char *)"     ^  ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"          ^     ",
           (const char *)"    ...........^",
           (const char *)"............... ",
           (const char *)"............... ",
           (const char *)"             ^  ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"    ........   ",
           (const char *)"    ........   ",
           (const char *)" ............. ",
           (const char *)"^.............^",
           (const char *)" ............. ",
           (const char *)"            ^  ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"    ^            ",
           (const char *)" ............... ",
           (const char *)"^............... ",
           (const char *)" ...............^",
           (const char *)" ............... ",
           (const char *)"         ...     ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"   ^               ",
           (const char *)" ................. ",
           (const char *)"^................. ",
           (const char *)" .................^",
           (const char *)"          ....     ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"      ^       ",
           (const char *)"      ....... ",
           (const char *)"      ....... ",
           (const char *)"      ....... ",
           (const char *)" .............",
           (const char *)"^.............",
           (const char *)"      ....... ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"  ^       ",
           (const char *)" .......  ",
           (const char *)"^........ ",
           (const char *)" ........^",
           (const char *)" ........ ",
           (const char *)"      ... ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)" ^         ",
           (const char *)" .         ",
           (const char *)" .         ",
           (const char *)" .....     ",
           (const char *)" ........  ",
           (const char *)"^.........^",
           (const char *)"  .......  ",
           (const char *)"  .        ",
           (const char *)"  ^        ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"      ^       ",
           (const char *)"   .......... ",
           (const char *)"^............ ",
           (const char *)"   .......... ",
           (const char *)"   ..........^",
           (const char *)"   .......... ",
           (const char *)"      .       ",
           (const char *)"      ^       ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"      ^     ",
           (const char *)"     ......^",
           (const char *)"     .....  ",
           (const char *)"^.........  ",
           (const char *)"  ........  ",
           (const char *)"  ........  ",
           (const char *)"  .         ",
           (const char *)"  ^         ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)" ^       ",
           (const char *)" ......  ",
           (const char *)"^.......^",
           (const char *)" ....... ",
           (const char *)" ....... ",
           (const char *)" ^       ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"         ^        ",
           (const char *)"^................ ",
           (const char *)" ................ ",
           (const char *)" ................^",
           (const char *)"       ........   ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"         ^     ",
           (const char *)"   ........... ",
           (const char *)"   ...........^",
           (const char *)"   ........... ",
           (const char *)" ............. ",
           (const char *)"^............. ",
           (const char *)" ............. ",
           (const char *)"    ^          ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"          ....    ",
           (const char *)"          ....    ",
           (const char *)"          ....    ",
           (const char *)"          ....    ",
           (const char *)"..................",
           (const char *)"..................",
           (const char *)"      .           ",
           (const char *)"      .           ",
           (const char *)"      ^           ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"        ........     ",
           (const char *)"  ...............    ",
           (const char *)"^...................^",
           (const char *)"  ...............    ",
           (const char *)"   ^                 ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"            ^    ",
           (const char *)"   ............. ",
           (const char *)"^...............^",
           (const char *)"   ............. ",
           (const char *)"          .      ",
           (const char *)"          ^      ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"           ^  ",
           (const char *)"     ........ ",
           (const char *)"     ........ ",
           (const char *)" ............ ",
           (const char *)"^............^",
           (const char *)"     ........ ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"          ...     ",
           (const char *)" .................",
           (const char *)"^.................",
           (const char *)" .................",
           (const char *)" .................",
           (const char *)"             .    ",
           (const char *)"             ^    ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"  ^       ",
           (const char *)" ........ ",
           (const char *)"^........^",
           (const char *)" ........ ",
           (const char *)" ........ ",
           (const char *)"    ^     ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"   ......... ",
           (const char *)"............ ",
           (const char *)"............^",
           (const char *)"   ......... ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"       ^        ",
           (const char *)"       .        ",
           (const char *)"       .....    ",
           (const char *)"       .....    ",
           (const char *)"       .....    ",
           (const char *)" ...............",
           (const char *)"^...............",
           (const char *)" ...............",
           (const char *)"              . ",
           (const char *)"              . ",
           (const char *)"              ^ ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"            ^     ",
           (const char *)"            .     ",
           (const char *)"       .........  ",
           (const char *)"       .........  ",
           (const char *)"       .........  ",
           (const char *)"..................",
           (const char *)"..................",
           (const char *)"       ^          ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"          ^     ",
           (const char *)"^.............  ",
           (const char *)" .............  ",
           (const char *)" .............  ",
           (const char *)" ..............^",
           (const char *)"       .....    ",
           (const char *)"       ^        ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"        ......     ",
           (const char *)"        ......     ",
           (const char *)"...................",
           (const char *)"...................",
           (const char *)"             ^     ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"       ...  ",
           (const char *)"       ...  ",
           (const char *)"       ...  ",
           (const char *)"       ...  ",
           (const char *)"............",
           (const char *)"............",
           (const char *)"         ^  ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"       ^         ",
           (const char *)"       .         ",
           (const char *)"     ..........  ",
           (const char *)" ...............^",
           (const char *)"^............... ",
           (const char *)" ............... ",
           (const char *)"            ^    ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"           ^       ",
           (const char *)"           .       ",
           (const char *)"           .       ",
           (const char *)" ................. ",
           (const char *)" .................^",
           (const char *)" ................. ",
           (const char *)"^................. ",
           (const char *)"       .......     ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"        ^            ",
           (const char *)"^...................^",
           (const char *)"  ................   ",
           (const char *)"  ................   ",
           (const char *)"  ................   ",
           (const char *)"        ^            ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"            ^  ",
           (const char *)"     .........^",
           (const char *)"     ......... ",
           (const char *)"^............. ",
           (const char *)" ............. ",
           (const char *)" ............. ",
           (const char *)"           ^   ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"        ^            ",
           (const char *)" ................... ",
           (const char *)"^................... ",
           (const char *)" ...................^",
           (const char *)" ................... ",
           (const char *)"        .......      ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"       ...  ",
           (const char *)"^..........^",
           (const char *)" .......... ",
           (const char *)" .......... ",
           (const char *)"       ^    ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"       ...........  ",
           (const char *)"  ................  ",
           (const char *)"  ................  ",
           (const char *)"  .................^",
           (const char *)"^.................  ",
           (const char *)"       ...........  ",
           (const char *)"               ^    ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"        ......      ",
           (const char *)"  ................. ",
           (const char *)"  ................. ",
           (const char *)"  ................. ",
           (const char *)"^..................^",
           (const char *)"        ......      ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"  ^            ",
           (const char *)" ............. ",
           (const char *)" .............^",
           (const char *)"^............. ",
           (const char *)"        ...    ",
           (const char *)"          ^    ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"          ^ ",
           (const char *)"          . ",
           (const char *)"^.......... ",
           (const char *)"  ..........",
           (const char *)"  ..........",
           (const char *)"  ..........",
           (const char *)"  ..........",
           (const char *)"  ^         ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"     ^         ",
           (const char *)" ............  ",
           (const char *)" ............  ",
           (const char *)"^..............",
           (const char *)" ..............",
           (const char *)"    ...........",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"   ^         ",
           (const char *)"   ......... ",
           (const char *)"   .........^",
           (const char *)"  .......... ",
           (const char *)"^........... ",
           (const char *)"  .......... ",
           (const char *)"  .......... ",
           (const char *)"         ^   ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"    ......... ",
           (const char *)"............. ",
           (const char *)"............. ",
           (const char *)".............^",
           (const char *)"    ......... ",
           (const char *)"    ^         ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"          ^      ",
           (const char *)" ...............^",
           (const char *)" ............... ",
           (const char *)"^............... ",
           (const char *)" ............... ",
           (const char *)"        .....    ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"        ...    ",
           (const char *)"        ...    ",
           (const char *)"^............. ",
           (const char *)"  ............ ",
           (const char *)"  ............^",
           (const char *)"  ............ ",
           (const char *)"  .            ",
           (const char *)"  ^            ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"   ^        ",
           (const char *)" .......... ",
           (const char *)"^..........^",
           (const char *)" .......... ",
           (const char *)" .......... ",
           (const char *)"  ^         ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"            ^       ",
           (const char *)"         ........   ",
           (const char *)"         ........   ",
           (const char *)"^...................",
           (const char *)" ...................",
           (const char *)" ...................",
           (const char *)" ^                  ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"     ..... ",
           (const char *)"   .......^",
           (const char *)"^......... ",
           (const char *)"   ....... ",
           (const char *)"        .  ",
           (const char *)"        ^  ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"        ^  ",
           (const char *)"    .....  ",
           (const char *)"    .....  ",
           (const char *)"    .....  ",
           (const char *)"...........",
           (const char *)"...........",
           (const char *)"    .....  ",
           (const char *)"        ^  ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"   ....^",
           (const char *)"....... ",
           (const char *)"....... ",
           (const char *)"     ^  ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"        ^        ",
           (const char *)"      .........  ",
           (const char *)"      .........  ",
           (const char *)"................ ",
           (const char *)"................^",
           (const char *)"................ ",
           (const char *)"      .........  ",
           (const char *)"             ^   ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"     ....... ",
           (const char *)"     ....... ",
           (const char *)"............^",
           (const char *)"............ ",
           (const char *)" ^           ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"                 ^    ",
           (const char *)"^...................  ",
           (const char *)" ...................  ",
           (const char *)" ...................  ",
           (const char *)" ....................^",
           (const char *)"          .....       ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"        ^          ",
           (const char *)"      ..........   ",
           (const char *)"      ..........   ",
           (const char *)" ..................",
           (const char *)" ..................",
           (const char *)"^..................",
           (const char *)"      ..........   ",
           (const char *)"           ^       ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"      ^       ",
           (const char *)"^............^",
           (const char *)"   .........  ",
           (const char *)"   .........  ",
           (const char *)"   ^          ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"       ^   ",
           (const char *)"  ........ ",
           (const char *)"  ........ ",
           (const char *)"  ........ ",
           (const char *)"  ........ ",
           (const char *)"^.........^",
           (const char *)" ......... ",
           (const char *)"   ^       ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"            ....        ",
           (const char *)"^...................    ",
           (const char *)"  ..................    ",
           (const char *)"  .....................^",
           (const char *)"  ..................    ",
           (const char *)"            ....        ",
           (const char *)"            ^           ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"      ^      ",
           (const char *)"  ........   ",
           (const char *)"^.........   ",
           (const char *)"  ...........",
           (const char *)"  ...........",
           (const char *)"    .........",
           (const char *)"         .   ",
           (const char *)"         ^   ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"       ^    ",
           (const char *)"      ..... ",
           (const char *)"      ..... ",
           (const char *)" .......... ",
           (const char *)"^.......... ",
           (const char *)" ..........^",
           (const char *)" .......... ",
           (const char *)"      ^     ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"       ^    ",
           (const char *)"       .    ",
           (const char *)"^.........  ",
           (const char *)" ..........^",
           (const char *)" .........  ",
           (const char *)"  ........  ",
           (const char *)"     .      ",
           (const char *)"     .      ",
           (const char *)"     ^      ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"             ^      ",
           (const char *)"          .......   ",
           (const char *)"          .......   ",
           (const char *)"          .......   ",
           (const char *)"^.................. ",
           (const char *)" ..................^",
           (const char *)"          .......   ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"      ^         ",
           (const char *)"    ..........  ",
           (const char *)"................",
           (const char *)"................",
           (const char *)"................",
           (const char *)"................",
           (const char *)"    ..........  ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"            ^  ",
           (const char *)" .............^",
           (const char *)" ............. ",
           (const char *)"^............. ",
           (const char *)" ............. ",
           (const char *)"     .......   ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"    .........   ",
           (const char *)"    ...........^",
           (const char *)"    .........   ",
           (const char *)".............   ",
           (const char *)".............   ",
           (const char *)"           ^    ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"          ^    ",
           (const char *)"       ......  ",
           (const char *)"  ...........  ",
           (const char *)"  ............^",
           (const char *)"  ...........  ",
           (const char *)"^............  ",
           (const char *)"       ......  ",
           (const char *)"           ^   ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"      ^    ",
           (const char *)" ......... ",
           (const char *)"^......... ",
           (const char *)" ......... ",
           (const char *)" .........^",
           (const char *)" ......... ",
           (const char *)"     ^     ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"       ^       ",
           (const char *)"      .......  ",
           (const char *)"      .......  ",
           (const char *)" ............. ",
           (const char *)" ............. ",
           (const char *)"^.............^",
           (const char *)"      .......  ",
           (const char *)"       ^       ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"          ^       ",
           (const char *)"          .       ",
           (const char *)"      ...........^",
           (const char *)"   .............. ",
           (const char *)"^................ ",
           (const char *)"   .............. ",
           (const char *)"    .             ",
           (const char *)"    ^             ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"          ^     ",
           (const char *)"   .........    ",
           (const char *)"^..............^",
           (const char *)"       ...      ",
           (const char *)"        .       ",
           (const char *)"        ^       ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"    ^       ",
           (const char *)"^.......... ",
           (const char *)" .......... ",
           (const char *)" ..........^",
           (const char *)" .......... ",
           (const char *)" ^          ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"       ^             ",
           (const char *)"^................... ",
           (const char *)" ...................^",
           (const char *)" ................... ",
           (const char *)" ................... ",
           (const char *)"                 ^   ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"     ^    ",
           (const char *)" ........ ",
           (const char *)"^........ ",
           (const char *)" ........^",
           (const char *)" ........ ",
           (const char *)" ........ ",
           (const char *)" ........ ",
           (const char *)"      ^   ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"           ^       ",
           (const char *)"        .......... ",
           (const char *)"        .......... ",
           (const char *)"^..................",
           (const char *)" ..................",
           (const char *)" ..................",
           (const char *)" ..................",
           (const char *)"                 ^ ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"    .........  ",
           (const char *)"    .........  ",
           (const char *)"    .........  ",
           (const char *)"..............^",
           (const char *)".............  ",
           (const char *)".............  ",
           (const char *)"  .            ",
           (const char *)"  ^            ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"           ^   ",
           (const char *)"  ............ ",
           (const char *)"^............. ",
           (const char *)"  ............^",
           (const char *)"  ............ ",
           (const char *)"            ^  ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"           ^        ",
           (const char *)"           .        ",
           (const char *)"           ...      ",
           (const char *)"           ...      ",
           (const char *)" ...................",
           (const char *)" ...................",
           (const char *)"^...................",
           (const char *)" ...................",
           (const char *)"            ^       ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"         ^      ",
           (const char *)"        ....    ",
           (const char *)"^..............^",
           (const char *)" .............. ",
           (const char *)" .............. ",
           (const char *)" .............. ",
           (const char *)"          ^     ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"            ^   ",
           (const char *)"      ......... ",
           (const char *)"      ......... ",
           (const char *)"^.............. ",
           (const char *)" .............. ",
           (const char *)" ..............^",
           (const char *)"      ......... ",
           (const char *)"          ^     ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"  ^       ",
           (const char *)" ........ ",
           (const char *)"^........^",
           (const char *)" ........ ",
           (const char *)"   ^      ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"          ^      ",
           (const char *)"        .......  ",
           (const char *)"^...............^",
           (const char *)"     ..........  ",
           (const char *)"     ..........  ",
           (const char *)"        .......  ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"        ^             ",
           (const char *)"        ...........   ",
           (const char *)"   ................   ",
           (const char *)"   ................   ",
           (const char *)"^....................^",
           (const char *)"        ...........   ",
           (const char *)"                 ^    ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"              ^      ",
           (const char *)" ...................^",
           (const char *)" ................... ",
           (const char *)"^................... ",
           (const char *)"           .....     ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"             ^    ",
           (const char *)"      ........... ",
           (const char *)"      ........... ",
           (const char *)"      ........... ",
           (const char *)"..................",
           (const char *)"..................",
           (const char *)"               ^  ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"           ^  ",
           (const char *)"           .  ",
           (const char *)"      ....... ",
           (const char *)"      ....... ",
           (const char *)"      ....... ",
           (const char *)"      ....... ",
           (const char *)"..............",
           (const char *)"..............",
           (const char *)"          ^   ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"          ^           ",
           (const char *)"^....................^",
           (const char *)"  ..................  ",
           (const char *)"  ..................  ",
           (const char *)"  ..................  ",
           (const char *)"   ^                  ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"              ^   ",
           (const char *)"^................ ",
           (const char *)" ................^",
           (const char *)" ................ ",
           (const char *)"        ....      ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"   ^             ",
           (const char *)"^...............^",
           (const char *)" ............... ",
           (const char *)" ............... ",
           (const char *)" ............... ",
           (const char *)"  ^              ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"    ... ",
           (const char *)"    ... ",
           (const char *)"    ... ",
           (const char *)"    ... ",
           (const char *)"........",
           (const char *)"........",
           (const char *)"    ^   ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)" ....     ",
           (const char *)" ....     ",
           (const char *)"..........",
           (const char *)"..........",
           (const char *)"..........",
           (const char *)"  .       ",
           (const char *)"  .       ",
           (const char *)"  ^       ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"           ^   ",
           (const char *)"    ..........^",
           (const char *)"    .......... ",
           (const char *)" ............. ",
           (const char *)"^............. ",
           (const char *)" ............. ",
           (const char *)" ^             ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"   ^     ",
           (const char *)" ......  ",
           (const char *)" ......  ",
           (const char *)".......  ",
           (const char *)".......  ",
           (const char *)"........^",
           (const char *)".......  ",
           (const char *)" ^       ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"         ^      ",
           (const char *)"  .............^",
           (const char *)"  ...........   ",
           (const char *)"  ...........   ",
           (const char *)"  ...........   ",
           (const char *)"^............   ",
           (const char *)"  ...........   ",
           (const char *)"           ^    ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"    ^       ",
           (const char *)"^.......... ",
           (const char *)" ..........^",
           (const char *)" .......... ",
           (const char *)"       ^    ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"              ^      ",
           (const char *)" ................... ",
           (const char *)"^...................^",
           (const char *)" ................... ",
           (const char *)"         ......      ",
           (const char *)"           ^         ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"         ... ",
           (const char *)"         ... ",
           (const char *)"         ... ",
           (const char *)"^............",
           (const char *)"   ..........",
           (const char *)"         ... ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"   ......^",
           (const char *)"......... ",
           (const char *)"......... ",
           (const char *)"......... ",
           (const char *)"      ^   ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"      ^          ",
           (const char *)"      .          ",
           (const char *)"    ...........  ",
           (const char *)"   .............^",
           (const char *)"   ............  ",
           (const char *)"^..............  ",
           (const char *)"   ............  ",
           (const char *)"    ...........  ",
           (const char *)"         ^       ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"  ^        ",
           (const char *)"  ........^",
           (const char *)".........  ",
           (const char *)".........  ",
           (const char *)"   .       ",
           (const char *)"   .       ",
           (const char *)"   ^       ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"         ...  ",
           (const char *)"         ...  ",
           (const char *)"    .........^",
           (const char *)"^...........  ",
           (const char *)"         ...  ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"       ^      ",
           (const char *)"^............ ",
           (const char *)" ............ ",
           (const char *)" ............^",
           (const char *)" ............ ",
           (const char *)"    ......... ",
           (const char *)"         ^    ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"         ....      ",
           (const char *)"..................^",
           (const char *)".................. ",
           (const char *)".................. ",
           (const char *)"         ....      ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"          ^  ",
           (const char *)" ........... ",
           (const char *)" ...........^",
           (const char *)"^........... ",
           (const char *)" ........... ",
           (const char *)"   ......... ",
           (const char *)"         .   ",
           (const char *)"         ^   ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"            ^     ",
           (const char *)"      ........... ",
           (const char *)"      ...........^",
           (const char *)" ................ ",
           (const char *)" ................ ",
           (const char *)"^................ ",
           (const char *)"      ........... ",
           (const char *)"      ^           ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"           ^      ",
           (const char *)"          ...     ",
           (const char *)"          ...     ",
           (const char *)"          ...     ",
           (const char *)"^................^",
           (const char *)" ................ ",
           (const char *)"               ^  ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"          ....       ",
           (const char *)"          ....       ",
           (const char *)" ................... ",
           (const char *)"^...................^",
           (const char *)" ................... ",
           (const char *)"             ^       ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"     ....   ",
           (const char *)" ..........^",
           (const char *)" .......... ",
           (const char *)"^.......... ",
           (const char *)" .......... ",
           (const char *)"    ^       ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)" ^        ",
           (const char *)"^........ ",
           (const char *)" ........^",
           (const char *)"    ..... ",
           (const char *)"     ^    ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"          ......     ",
           (const char *)"  ..................^",
           (const char *)"^.................   ",
           (const char *)"  ................   ",
           (const char *)"          ......     ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"      ....    ",
           (const char *)"............. ",
           (const char *)"............. ",
           (const char *)".............^",
           (const char *)"............. ",
           (const char *)"           ^  ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"            ^    ",
           (const char *)"^..............  ",
           (const char *)"  .............  ",
           (const char *)"  ..............^",
           (const char *)"  .............  ",
           (const char *)"       .....     ",
           (const char *)"        ^        ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"    ....... ",
           (const char *)"^..........^",
           (const char *)" .......... ",
           (const char *)" .......... ",
           (const char *)"    ....... ",
           (const char *)"         ^  ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"     ..........    ",
           (const char *)"     ..........    ",
           (const char *)" .................^",
           (const char *)"^................. ",
           (const char *)"     ..........    ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"        ^     ",
           (const char *)"        ...   ",
           (const char *)"        ...   ",
           (const char *)"   .........  ",
           (const char *)"^............^",
           (const char *)"   .........  ",
           (const char *)"        ...   ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"      ...    ",
           (const char *)"      ...    ",
           (const char *)"............^",
           (const char *)".........    ",
           (const char *)"   .         ",
           (const char *)"   .         ",
           (const char *)"   ^         ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"            ^        ",
           (const char *)" ..................  ",
           (const char *)" ..................  ",
           (const char *)"^...................^",
           (const char *)" ..................  ",
           (const char *)"               ^     ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"       ....    ",
           (const char *)"       ....    ",
           (const char *)"       ....    ",
           (const char *)"..............^",
           (const char *)".............. ",
           (const char *)"       ....    ",
           (const char *)"        ^      ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"      .......    ",
           (const char *)"      .......    ",
           (const char *)"      .......    ",
           (const char *)"      .......    ",
           (const char *)".................",
           (const char *)".................",
           (const char *)"              ^  ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"       ^      ",
           (const char *)"       .      ",
           (const char *)"  ...........^",
           (const char *)"  .........   ",
           (const char *)"^..........   ",
           (const char *)"  .........   ",
           (const char *)"        .     ",
           (const char *)"        ^     ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"            ^    ",
           (const char *)"     ........... ",
           (const char *)"     ........... ",
           (const char *)"     ........... ",
           (const char *)"^................",
           (const char *)" ................",
           (const char *)" ................",
           (const char *)"             ^   ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"       ^  ",
           (const char *)" ........ ",
           (const char *)" ........ ",
           (const char *)"......... ",
           (const char *)".........^",
           (const char *)" ........ ",
           (const char *)"      ^   ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"        ^  ",
           (const char *)" .........^",
           (const char *)" ......... ",
           (const char *)"^......... ",
           (const char *)" ......... ",
           (const char *)"        ^  ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"   ^                   ",
           (const char *)"   .                   ",
           (const char *)"   .                   ",
           (const char *)"^.....................^",
           (const char *)"  ...................  ",
           (const char *)"       ...........     ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"     ^      ",
           (const char *)" .......... ",
           (const char *)" ..........^",
           (const char *)"^.......... ",
           (const char *)" .......... ",
           (const char *)"     ^      ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"      ...  ",
           (const char *)"^........  ",
           (const char *)"  ........^",
           (const char *)"  .......  ",
           (const char *)"   .       ",
           (const char *)"   .       ",
           (const char *)"   ^       ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"   ^     ",
           (const char *)" ....... ",
           (const char *)" ........",
           (const char *)"^........",
           (const char *)" ........",
           (const char *)"   ......",
           (const char *)"   ^     ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"    .... ",
           (const char *)"    .... ",
           (const char *)"^....... ",
           (const char *)" .......^",
           (const char *)"    .... ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"  ^              ",
           (const char *)"^...............^",
           (const char *)" ..............  ",
           (const char *)" ..............  ",
           (const char *)" ..............  ",
           (const char *)"         ...     ",
           (const char *)"         ^       ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"   .....   ",
           (const char *)"   .......^",
           (const char *)"   .....   ",
           (const char *)"........   ",
           (const char *)"........   ",
           (const char *)" .         ",
           (const char *)" ^         ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"     ^       ",
           (const char *)"   ......... ",
           (const char *)"^........... ",
           (const char *)" ........... ",
           (const char *)" ...........^",
           (const char *)"   ......... ",
           (const char *)"   ^         ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"       ^       ",
           (const char *)"       ....... ",
           (const char *)"       ....... ",
           (const char *)"       ....... ",
           (const char *)" ............. ",
           (const char *)"^.............^",
           (const char *)"       ....... ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"     ........ ",
           (const char *)"     ........ ",
           (const char *)"^............ ",
           (const char *)" ............ ",
           (const char *)" ............^",
           (const char *)"     ........ ",
           (const char *)"       ^      ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"  ^      ",
           (const char *)"  ...... ",
           (const char *)".........",
           (const char *)".........",
           (const char *)"  ...... ",
           (const char *)"  ^      ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"^......     ",
           (const char *)" ...........",
           (const char *)" ...........",
           (const char *)" ...........",
           (const char *)"     ^      ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"        ^       ",
           (const char *)"        .       ",
           (const char *)"    ........    ",
           (const char *)"^..............^",
           (const char *)"    ........    ",
           (const char *)"          .     ",
           (const char *)"          .     ",
           (const char *)"          ^     ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"       ^   ",
           (const char *)"    .....  ",
           (const char *)"    .....  ",
           (const char *)"...........",
           (const char *)"...........",
           (const char *)"    .....  ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"       ......      ",
           (const char *)"       ......      ",
           (const char *)"..................^",
           (const char *)".................  ",
           (const char *)".................  ",
           (const char *)" ^                 ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"    .... ",
           (const char *)"    ....^",
           (const char *)"    .... ",
           (const char *)"........ ",
           (const char *)"........ ",
           (const char *)"     ^   ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)" ^          ",
           (const char *)" ..........^",
           (const char *)" .......... ",
           (const char *)"^.......... ",
           (const char *)" .......... ",
           (const char *)" .......... ",
           (const char *)"         ^  ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)" ^           ",
           (const char *)"^...........^",
           (const char *)" ........... ",
           (const char *)" ........... ",
           (const char *)" ........... ",
           (const char *)"          ^  ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"      ........  ",
           (const char *)"      ........  ",
           (const char *)"   ............^",
           (const char *)"^.............  ",
           (const char *)"   ...........  ",
           (const char *)"   ...........  ",
           (const char *)"         ^      ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"     ^        ",
           (const char *)"  ........... ",
           (const char *)"............. ",
           (const char *)".............^",
           (const char *)"............. ",
           (const char *)"        .     ",
           (const char *)"        ^     ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"          ^    ",
           (const char *)"      ......   ",
           (const char *)"      ......   ",
           (const char *)"..............^",
           (const char *)".............. ",
           (const char *)" ^             ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"  .....^",
           (const char *)"^...... ",
           (const char *)" ...... ",
           (const char *)" ...... ",
           (const char *)" ...... ",
           (const char *)"  ..... ",
           (const char *)"  ^     ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"          ...    ",
           (const char *)"          ...    ",
           (const char *)"          ...    ",
           (const char *)"          ...    ",
           (const char *)".................",
           (const char *)".................",
           (const char *)"               ^ ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"            ....         ",
           (const char *)"^.......................^",
           (const char *)"   ...................   ",
           (const char *)"           ^             ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"     ^              ",
           (const char *)"^..................^",
           (const char *)"  ................. ",
           (const char *)"  ................. ",
           (const char *)"  ................. ",
           (const char *)"                 .  ",
           (const char *)"                 ^  ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"        ^    ",
           (const char *)"        .    ",
           (const char *)"  ..........^",
           (const char *)"  .........  ",
           (const char *)"  .........  ",
           (const char *)"...........  ",
           (const char *)"...........  ",
           (const char *)"...........  ",
           (const char *)" ^           ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"           ....      ",
           (const char *)"^...................^",
           (const char *)" ................... ",
           (const char *)"           ....      ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"         .........  ",
           (const char *)" .................. ",
           (const char *)"^.................. ",
           (const char *)" ..................^",
           (const char *)" .................. ",
           (const char *)"           ^        ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"  ^           ",
           (const char *)"^............^",
           (const char *)" ............ ",
           (const char *)" ............ ",
           (const char *)" ............ ",
           (const char *)"   ^          ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"         ^            ",
           (const char *)"^...................  ",
           (const char *)"   .................  ",
           (const char *)"   ..................^",
           (const char *)"          .......     ",
           (const char *)"              ^       ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"       ^       ",
           (const char *)"       .       ",
           (const char *)" ..........    ",
           (const char *)" ..........    ",
           (const char *)" ..........    ",
           (const char *)" ..........    ",
           (const char *)"..............^",
           (const char *)"...........    ",
           (const char *)"    .          ",
           (const char *)"    ^          ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"          ^      ",
           (const char *)"          ...    ",
           (const char *)"          ...    ",
           (const char *)" ............... ",
           (const char *)"^............... ",
           (const char *)" ...............^",
           (const char *)" ............... ",
           (const char *)"        ^        ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"     ^       ",
           (const char *)"  ........   ",
           (const char *)" .........   ",
           (const char *)"^.........   ",
           (const char *)" ...........^",
           (const char *)"  ........   ",
           (const char *)"   ^         ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"  ^    ",
           (const char *)"^....  ",
           (const char *)" ......",
           (const char *)" ......",
           (const char *)"  .....",
           (const char *)"    ^  ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"    ........... ",
           (const char *)"    ........... ",
           (const char *)"    ........... ",
           (const char *)"...............^",
           (const char *)"............... ",
           (const char *)"............... ",
           (const char *)"^               ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)" ....   ",
           (const char *)"^.......",
           (const char *)" .......",
           (const char *)"  ......",
           (const char *)"    ^   ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"           ^  ",
           (const char *)"           .  ",
           (const char *)"  ........... ",
           (const char *)"^............ ",
           (const char *)"  ...........^",
           (const char *)"  ........... ",
           (const char *)"   .          ",
           (const char *)"   ^          ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"         ^               ",
           (const char *)"         ......          ",
           (const char *)"         ......          ",
           (const char *)"   .................     ",
           (const char *)"^...................     ",
           (const char *)"   .....................^",
           (const char *)"         ......          ",
           (const char *)"           ^             ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"   ^          ",
           (const char *)"^............^",
           (const char *)" ............ ",
           (const char *)" ............ ",
           (const char *)"           ^  ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"            ^   ",
           (const char *)"      ......... ",
           (const char *)"      ......... ",
           (const char *)"      ......... ",
           (const char *)" ..............^",
           (const char *)"^.............. ",
           (const char *)" .............. ",
           (const char *)"            .   ",
           (const char *)"            .   ",
           (const char *)"            ^   ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"       ...     ",
           (const char *)"       ...     ",
           (const char *)"       ...     ",
           (const char *)"       ...     ",
           (const char *)"...............",
           (const char *)"...............",
           (const char *)"        ^      ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"  ^         ",
           (const char *)"^..........^",
           (const char *)" .......... ",
           (const char *)"     ...... ",
           (const char *)"         ^  ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"     ^      ",
           (const char *)"     .      ",
           (const char *)" .......    ",
           (const char *)" ..........^",
           (const char *)"^.......    ",
           (const char *)"   .....    ",
           (const char *)"      .     ",
           (const char *)"      ^     ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"          ^        ",
           (const char *)"          ....     ",
           (const char *)"          ....     ",
           (const char *)"          ....     ",
           (const char *)"...................",
           (const char *)"...................",
           (const char *)"...................",
           (const char *)"       ^           ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"      ^      ",
           (const char *)"    .......  ",
           (const char *)"    .......  ",
           (const char *)"    .......  ",
           (const char *)".............",
           (const char *)".............",
           (const char *)"         ^   ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"    ^       ",
           (const char *)"  .........^",
           (const char *)"  ......... ",
           (const char *)"^.......... ",
           (const char *)" .......... ",
           (const char *)"  ......... ",
           (const char *)"         ^  ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)" ^       ",
           (const char *)" ......  ",
           (const char *)"^....... ",
           (const char *)" .......^",
           (const char *)" ....... ",
           (const char *)"   ^     ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"      ^      ",
           (const char *)" ........... ",
           (const char *)" ........... ",
           (const char *)" ........... ",
           (const char *)" ...........^",
           (const char *)"^........... ",
           (const char *)" ........... ",
           (const char *)"        ^    ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"          ^               ",
           (const char *)"          .               ",
           (const char *)"      ..................  ",
           (const char *)"      ..................  ",
           (const char *)"^.......................  ",
           (const char *)"      ...................^",
           (const char *)"              .......     ",
           (const char *)"                    ^     ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"    ^       ",
           (const char *)"^.....      ",
           (const char *)"  .........^",
           (const char *)"  ........  ",
           (const char *)"  ........  ",
           (const char *)"        .   ",
           (const char *)"        ^   ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"         ^        ",
           (const char *)"         .....    ",
           (const char *)"         .....    ",
           (const char *)"         .....    ",
           (const char *)"..................",
           (const char *)"..................",
           (const char *)"            ^     ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"  ^            ",
           (const char *)"^............  ",
           (const char *)" ............  ",
           (const char *)" .............^",
           (const char *)" ............. ",
           (const char *)"     ......... ",
           (const char *)"           ^   ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"     ^    ",
           (const char *)"    .....^",
           (const char *)"^........ ",
           (const char *)" ........ ",
           (const char *)" ........ ",
           (const char *)"     ^    ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"            ....     ",
           (const char *)"            ....     ",
           (const char *)"   ..................",
           (const char *)"^....................",
           (const char *)"            ....     ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"        .........  ",
           (const char *)"        .........  ",
           (const char *)"        .........  ",
           (const char *)"        .........  ",
           (const char *)"^..................",
           (const char *)" ..................",
           (const char *)"   ^               ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"        ^       ",
           (const char *)"     .......... ",
           (const char *)"     ..........^",
           (const char *)"     .......... ",
           (const char *)"^.............. ",
           (const char *)" .............. ",
           (const char *)" ^              ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"            ^    ",
           (const char *)"   ............. ",
           (const char *)"   ............. ",
           (const char *)"   .............^",
           (const char *)"^............... ",
           (const char *)"        ......   ",
           (const char *)"             .   ",
           (const char *)"             ^   ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"       ......   ",
           (const char *)"^..............^",
           (const char *)" .............. ",
           (const char *)"  ^             ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"     .......       ",
           (const char *)"^.................^",
           (const char *)"    ...........    ",
           (const char *)"    ...........    ",
           (const char *)"           ^       ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"        ...  ",
           (const char *)"        ...  ",
           (const char *)" ............",
           (const char *)" ............",
           (const char *)"^............",
           (const char *)"        ...  ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"  ^           ",
           (const char *)" ............^",
           (const char *)"^............ ",
           (const char *)" ............ ",
           (const char *)" ............ ",
           (const char *)"     ........ ",
           (const char *)"         ^    ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"    .......   ",
           (const char *)"    .......   ",
           (const char *)"    .......   ",
           (const char *)"  .........   ",
           (const char *)"^............^",
           (const char *)"  .........   ",
           (const char *)"        ^     ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"      ^        ",
           (const char *)"^............. ",
           (const char *)" ............. ",
           (const char *)" ............. ",
           (const char *)" .............^",
           (const char *)"    ........   ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"     ^     ",
           (const char *)"     .     ",
           (const char *)"     .     ",
           (const char *)" ........  ",
           (const char *)"..........^",
           (const char *)".........  ",
           (const char *)".          ",
           (const char *)"^          ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"           ^    ",
           (const char *)"    ........... ",
           (const char *)"    ........... ",
           (const char *)"...............^",
           (const char *)"............... ",
           (const char *)"    ........... ",
           (const char *)"            ^   ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"        ......    ",
           (const char *)"        ......    ",
           (const char *)".................^",
           (const char *)"................  ",
           (const char *)"  ^               ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"  ^            ",
           (const char *)" ............. ",
           (const char *)"^............. ",
           (const char *)" .............^",
           (const char *)"    ........   ",
           (const char *)"    ^          ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"     ^       ",
           (const char *)"  .......... ",
           (const char *)"^...........^",
           (const char *)" ........... ",
           (const char *)"         ^   ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"     ^     ",
           (const char *)" ......... ",
           (const char *)"^......... ",
           (const char *)" .........^",
           (const char *)" ......... ",
           (const char *)"      ^    ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"    ^         ",
           (const char *)"   ..........^",
           (const char *)"^............ ",
           (const char *)"   .......... ",
           (const char *)"     ........ ",
           (const char *)"           .  ",
           (const char *)"           .  ",
           (const char *)"           ^  ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"    ^       ",
           (const char *)"    ....... ",
           (const char *)"........... ",
           (const char *)"...........^",
           (const char *)"........... ",
           (const char *)"........... ",
           (const char *)"      .     ",
           (const char *)"      ^     ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"   ...........   ",
           (const char *)"   ...........   ",
           (const char *)"   ...........   ",
           (const char *)"   ...........   ",
           (const char *)"................^",
           (const char *)"...............  ",
           (const char *)"  ^              ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"        .......      ",
           (const char *)" ................... ",
           (const char *)"^...................^",
           (const char *)" ................... ",
           (const char *)" ................... ",
           (const char *)"            ^        ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"        ^     ",
           (const char *)"   ..........^",
           (const char *)"   .........  ",
           (const char *)"   .........  ",
           (const char *)"............  ",
           (const char *)"............  ",
           (const char *)"............  ",
           (const char *)" ^            ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)" ^                   ",
           (const char *)"^................... ",
           (const char *)" ...................^",
           (const char *)" ................... ",
           (const char *)" ................... ",
           (const char *)"           ....      ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"  ^                  ",
           (const char *)"  .                  ",
           (const char *)"  .                  ",
           (const char *)" ................... ",
           (const char *)" ...................^",
           (const char *)"^................... ",
           (const char *)" ................... ",
           (const char *)"                  .  ",
           (const char *)"                  ^  ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"     .........     ",
           (const char *)"     .........     ",
           (const char *)" .................^",
           (const char *)"^..............    ",
           (const char *)" ..............    ",
           (const char *)"        ^          ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"      ......... ",
           (const char *)"      ......... ",
           (const char *)"      ......... ",
           (const char *)"      ......... ",
           (const char *)"^...............",
           (const char *)" ...............",
           (const char *)"              ^ ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"    ^       ",
           (const char *)" ..........^",
           (const char *)" ........   ",
           (const char *)".........   ",
           (const char *)".........   ",
           (const char *)".........   ",
           (const char *)"  .         ",
           (const char *)"  ^         ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"               ^    ",
           (const char *)"^.................. ",
           (const char *)" ..................^",
           (const char *)"          ....      ",
           nullptr);

  room_add(g, false /* check */, __FUNCTION__, __LINE__,
           (const char *)"     ........     ",
           (const char *)"     ........     ",
           (const char *)".................^",
           (const char *)"................  ",
           (const char *)"        ^         ",
           nullptr);

  /* clang-format on */
}
