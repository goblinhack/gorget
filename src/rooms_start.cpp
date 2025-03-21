//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_charmap.hpp"
#include "my_level.hpp"

//
// Create all start rooms
//
void rooms_start(Gamep g)
{
  TRACE_NO_INDENT();

  /* clang-format off */

  room_add(g, true /* check exits */, __FUNCTION__, __LINE__, 
           (const char *)"    ^      ",
           (const char *)" xxx.xxxxx ",
           (const char *)" x.......x ",
           (const char *)" x.......x ",
           (const char *)"^........x ",
           (const char *)" x...@...x ",
           (const char *)" x.......x ",
           (const char *)" x........^",
           (const char *)" x.......x ",
           (const char *)" xxxxxx.xx ",
           (const char *)"       ^   ",
           nullptr);

  room_add(g, true /* check exits */, __FUNCTION__, __LINE__, 
           (const char *)"    ^      ",
           (const char *)" xxx.xxxxx ",
           (const char *)" x.......x ",
           (const char *)" x.......x ",
           (const char *)"^........x ",
           (const char *)" x...@...x ",
           (const char *)" x.......x ",
           (const char *)" x........^",
           (const char *)" x.......x ",
           (const char *)" xxxxxxxxx ",
           (const char *)"           ",
           nullptr);

  room_add(g, true /* check exits */, __FUNCTION__, __LINE__, 
           (const char *)"    ^      ",
           (const char *)" xxx.xxxxx ",
           (const char *)" x.......x ",
           (const char *)" x.......x ",
           (const char *)"^........x ",
           (const char *)" x.......x ",
           (const char *)" x.......x ",
           (const char *)" x...@...x ",
           (const char *)" x.......x ",
           (const char *)" xxxxxxxxx ",
           (const char *)"           ",
           nullptr);

  room_add(g, true /* check exits */, __FUNCTION__, __LINE__, 
           (const char *)"    ^      ",
           (const char *)" xxx.xxxxx ",
           (const char *)" x.......x ",
           (const char *)" x.......x ",
           (const char *)" x.......x ",
           (const char *)" x.......x ",
           (const char *)" x.......x ",
           (const char *)" x...@...x ",
           (const char *)" x.......x ",
           (const char *)" xxxxxxxxx ",
           (const char *)"           ",
           nullptr);

  room_add(g, true /* check exits */, __FUNCTION__, __LINE__, 
           (const char *)"    ^      ",
           (const char *)"   x.xxxxx ",
           (const char *)"   x.....x ",
           (const char *)"   x.....x ",
           (const char *)" xxx.....x ",
           (const char *)" x.......x ",
           (const char *)" x.......x ",
           (const char *)" x...@...x ",
           (const char *)" x.......x ",
           (const char *)" xxxxxxxxx ",
           (const char *)"           ",
           nullptr);

  room_add(g, true /* check exits */, __FUNCTION__, __LINE__, 
           (const char *)"    ^      ",
           (const char *)"   x.xxx   ",
           (const char *)"   x...x   ",
           (const char *)"   x...xxx ",
           (const char *)" xxx.....x ",
           (const char *)" x.......x ",
           (const char *)" x.......x ",
           (const char *)" x...@...x ",
           (const char *)" x.......x ",
           (const char *)" xxxxxxxxx ",
           (const char *)"           ",
           nullptr);

  room_add(g, true /* check exits */, __FUNCTION__, __LINE__, 
           (const char *)"    ^      ",
           (const char *)"   x.xxx   ",
           (const char *)"   x...x   ",
           (const char *)"   x...xxx ",
           (const char *)" xxx.....x ",
           (const char *)" x.......x ",
           (const char *)" x.......x ",
           (const char *)" x...@...x ",
           (const char *)" x.......x ",
           (const char *)" xxxxxxxxx ",
           (const char *)"           ",
           nullptr);

  room_add(g, true /* check exits */, __FUNCTION__, __LINE__, 
           (const char *)"    ^      ",
           (const char *)"   x.xxx   ",
           (const char *)"   x...x   ",
           (const char *)"   x...xxx ",
           (const char *)" xxx.....x ",
           (const char *)" x.......x ",
           (const char *)" x.......x ",
           (const char *)" xxx.@...x ",
           (const char *)"   x.....x ",
           (const char *)"   xxxxxxx ",
           (const char *)"           ",
           nullptr);

  room_add(g, true /* check exits */, __FUNCTION__, __LINE__, 
           (const char *)"    ^      ",
           (const char *)"   x.xxx   ",
           (const char *)"   x...x   ",
           (const char *)"   x...xxx ",
           (const char *)" xxx.....x ",
           (const char *)" x.......x ",
           (const char *)" x.....xxx ",
           (const char *)" xxx.@.x   ",
           (const char *)"   x...x   ",
           (const char *)"   xxxxx   ",
           (const char *)"           ",
           nullptr);

  room_add(g, true /* check exits */, __FUNCTION__, __LINE__, 
           (const char *)"    ^      ",
           (const char *)"   x.xxx   ",
           (const char *)"   x...x   ",
           (const char *)"   x...xxx ",
           (const char *)"   x.....x ",
           (const char *)"   x.....x ",
           (const char *)"   x...xxx ",
           (const char *)"   x.@.x   ",
           (const char *)"   x...x   ",
           (const char *)"   xxxxx   ",
           (const char *)"           ",
           nullptr);

  room_add(g, true /* check exits */, __FUNCTION__, __LINE__, 
           (const char *)"    ^      ",
           (const char *)"   x.xxx   ",
           (const char *)"   x...x   ",
           (const char *)"   x...x   ",
           (const char *)"   x...x   ",
           (const char *)"   x...x   ",
           (const char *)"   x...x   ",
           (const char *)"   x.@.x   ",
           (const char *)"   x...x   ",
           (const char *)"   xxxxx   ",
           (const char *)"           ",
           nullptr);

  room_add(g, true /* check exits */, __FUNCTION__, __LINE__, 
           (const char *)"    ^      ",
           (const char *)"   x.xxx   ",
           (const char *)"   x...x   ",
           (const char *)"   x...x   ",
           (const char *)"   x.@.x   ",
           (const char *)"   x...x   ",
           (const char *)"   xxxxx   ",
           (const char *)"           ",
           nullptr);

  room_add(g, true /* check exits */, __FUNCTION__, __LINE__, 
           (const char *)"    ^             ",
           (const char *)"   x.xxxxxxxxxx   ",
           (const char *)"   x..........x   ",
           (const char *)"   xxxxxxxx...x   ",
           (const char *)"          x.@.x   ",
           (const char *)"          x...x   ",
           (const char *)"          xxxxx   ",
           (const char *)"                  ",
           nullptr);

  room_add(g, true /* check exits */, __FUNCTION__, __LINE__, 
           (const char *)"     ^      ",
           (const char *)"  xxx.xxxxx ",
           (const char *)"  x.......xx",
           (const char *)" xx.x.x.x..x",
           (const char *)"^..........x",
           (const char *)" xx.x......x",
           (const char *)"  x.....@..x",
           (const char *)"  x.x......x",
           (const char *)"  x.......xx",
           (const char *)"  xxxxxxxxxx",
           nullptr);

  room_add(g, true /* check exits */, __FUNCTION__, __LINE__, 
           (const char *)" ^       ",
           (const char *)"x.xxxxxx ",
           (const char *)"x......x ",
           (const char *)" x.....xx",
           (const char *)" x......x",
           (const char *)" x......x",
           (const char *)" xx...@.x",
           (const char *)"  xx....x",
           (const char *)"  xxxxxxx",
           nullptr);

  room_add(g, true /* check exits */, __FUNCTION__, __LINE__, 
           (const char *)"   xxxxxxx  ",
           (const char *)" xxx.....xx ",
           (const char *)"^.........xx",
           (const char *)" xxxxx.....x",
           (const char *)"     x|....x",
           (const char *)" ....s..@..x",
           (const char *)" .$. x|....x",
           (const char *)" ... xxxxxxx",
           nullptr);

  room_add(g, true /* check exits */, __FUNCTION__, __LINE__, 
           (const char *)"   xxxxxxx  ",
           (const char *)" xxx.....xx ",
           (const char *)"^.........xx",
           (const char *)" xxxxx.....x",
           (const char *)"     x|....x",
           (const char *)" ....s..@..x",
           (const char *)" .m. x|....x",
           (const char *)" ... xxxxxxx",
           nullptr);

  room_add(g, true /* check exits */, __FUNCTION__, __LINE__, 
           (const char *)"   xxxxxxx  ",
           (const char *)" xxx.....xx ",
           (const char *)"^.........xx",
           (const char *)" xxxxx.....x",
           (const char *)"     x|....x",
           (const char *)" ...Cs..@..x",
           (const char *)" .$. x|....x",
           (const char *)" m.. xxxxxxx",
           nullptr);

  room_add(g, true /* check exits */, __FUNCTION__, __LINE__, 
           (const char *)"  xxxxxxxxx",
           (const char *)" xx.CCCCCCx",
           (const char *)"^....CCCCCx",
           (const char *)" xxC..CCCCx",
           (const char *)"  xCC.....x",
           (const char *)"  xxx...@.x",
           (const char *)"    x.....x",
           (const char *)"    xxxxxxx",
           nullptr);

  room_add(g, true /* check exits */, __FUNCTION__, __LINE__, 
           (const char *)"      ^  ",
           (const char *)"     x.x ",
           (const char *)"     x.x ",
           (const char *)"    xx.xx",
           (const char *)"    xB.Bx",
           (const char *)"xxxxx...x",
           (const char *)"x.......x",
           (const char *)"x.......x",
           (const char *)"x.@.....x",
           (const char *)"x.......x",
           (const char *)"xxxxxxxxx",
           nullptr);

  room_add(g, true /* check exits */, __FUNCTION__, __LINE__, 
           (const char *)"      ^  ",
           (const char *)"     x.x ",
           (const char *)"     x.x ",
           (const char *)"    xx.xx",
           (const char *)"    x|.|x",
           (const char *)"    x...x",
           (const char *)"    x|.|x",
           (const char *)"    x...x",
           (const char *)"xxxxx|.|x",
           (const char *)"x.......x",
           (const char *)"x.......x",
           (const char *)"x.@.....x",
           (const char *)"x.......x",
           (const char *)"xxxxxxxxx",
           nullptr);

  room_add(g, true /* check exits */, __FUNCTION__, __LINE__, 
           (const char *)"      ^  ",
           (const char *)"     x.x ",
           (const char *)"     x.x ",
           (const char *)"    xx.xx",
           (const char *)"    xC.Cx",
           (const char *)"    x...x",
           (const char *)"    xC.Cx",
           (const char *)"    x...x",
           (const char *)"xxxxxC.Cx",
           (const char *)"x.......x",
           (const char *)"x.......x",
           (const char *)"x.@.....x",
           (const char *)"x.......x",
           (const char *)"xxxxxxxxx",
           nullptr);

  room_add(g, true /* check exits */, __FUNCTION__, __LINE__, 
           (const char *)"      ^  ",
           (const char *)"     x.x ",
           (const char *)"     x.x ",
           (const char *)"    xx.xx",
           (const char *)"    xB.Bx",
           (const char *)"    x...x",
           (const char *)"xxxxxB.Bx",
           (const char *)"x.......x",
           (const char *)"x.......x",
           (const char *)"x.@.....x",
           (const char *)"x.......x",
           (const char *)"xxxxxxxxx",
           nullptr);

  room_add(g, true /* check exits */, __FUNCTION__, __LINE__, 
           (const char *)" ^        ",
           (const char *)"x.xxxxxx  ",
           (const char *)"x......x  ",
           (const char *)"x.cCCc.x  ",
           (const char *)"x.CCCC.x  ",
           (const char *)"x...CC.xxx",
           (const char *)"xx..CC...x",
           (const char *)" x..cC.@.x",
           (const char *)" x.......x",
           (const char *)" xxxxxxxxx",
           nullptr);

  /* clang-format on */
}
