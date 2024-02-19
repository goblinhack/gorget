//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_level.hpp"

void Level::dungeon_create_and_place()
{
  TRACE_NO_INDENT();
  map_set(data,
          "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx"
          "x...x...........x..............x"
          "x...x.xx..x.....x..xxxx..xxxx..x"
          "x...x..x...x....x..xxxx..xxxx..x"
          "x...x..xx...x...x..xxx....xxx..x"
          "x.....xx........x..............x"
          "x......x........x..xxx....xxx..x"
          "xxxxxxxx........x..xxxx..xxxx..x"
          "x...............x..xxxx..xxxx..x"
          "x..xxxxxxx......x..............x"
          "x..x.....x..xxxxx...x.......x..x"
          "x..x.xxx.x..x...x..x.x.....x...x"
          "x......x........x...x.....x....x"
          "xx...xxx........x........x.....x"
          "x..............x........x......x"
          "xxxx.xxxxxxxxxx..x.....x.......x"
          "x..x.x...........xx............x"
          "x..x.x............x.x......x...x"
          "x..x.x....xxx.......x..xxxxxxx.x"
          "x.........x.x.....xxx....x.....x"
          "x..xxx.x..xxx.....xx...........x"
          "x...x..x...........x...x....x..x"
          "x.........xxx...........x..x...x"
          "x...x..xx.xxx......x...x.......x"
          "x..xxx....xxx.xxxxxx....x...x..x"
          "x...x...x..........x...x...x...x"
          "x.......x..........x....x......x"
          "x.......x..........x...........x"
          "x.......x.........xxxxxxxxxxxxxx"
          "x.......x......................x"
          "x.......x......................x"
          "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
}
