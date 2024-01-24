//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_tile.hpp"

void gfx_init10(void)
{
  {
    std::initializer_list< std::string > tiles = {
        "ui.10,0,0",   "ui.10,1,0",   "ui.10,2,0",   "ui.10,3,0",   "ui.10,4,0",   "ui.10,5,0",   "ui.10,6,0",
        "ui.10,7,0",   "ui.10,8,0",   "ui.10,9,0",   "ui.10,10,0",  "ui.10,11,0",  "ui.10,12,0",  "ui.10,13,0",
        "ui.10,14,0",  "ui.10,15,0",  "ui.10,0,1",   "ui.10,1,1",   "ui.10,2,1",   "ui.10,3,1",   "ui.10,4,1",
        "ui.10,5,1",   "ui.10,6,1",   "ui.10,7,1",   "ui.10,8,1",   "ui.10,9,1",   "ui.10,10,1",  "ui.10,11,1",
        "ui.10,12,1",  "ui.10,13,1",  "ui.10,14,1",  "ui.10,15,1",  "ui.10,0,2",   "ui.10,1,2",   "ui.10,2,2",
        "ui.10,3,2",   "ui.10,4,2",   "ui.10,5,2",   "ui.10,6,2",   "ui.10,7,2",   "ui.10,8,2",   "ui.10,9,2",
        "ui.10,10,2",  "ui.10,11,2",  "ui.10,12,2",  "ui.10,13,2",  "ui.10,14,2",  "ui.10,15,2",  "ui.10,0,3",
        "ui.10,1,3",   "ui.10,2,3",   "ui.10,3,3",   "ui.10,4,3",   "ui.10,5,3",   "ui.10,6,3",   "ui.10,7,3",
        "ui.10,8,3",   "ui.10,9,3",   "ui.10,10,3",  "ui.10,11,3",  "ui.10,12,3",  "ui.10,13,3",  "ui.10,14,3",
        "ui.10,15,3",  "ui.10,0,4",   "ui.10,1,4",   "ui.10,2,4",   "ui.10,3,4",   "ui.10,4,4",   "ui.10,5,4",
        "ui.10,6,4",   "ui.10,7,4",   "ui.10,8,4",   "ui.10,9,4",   "ui.10,10,4",  "ui.10,11,4",  "ui.10,12,4",
        "ui.10,13,4",  "ui.10,14,4",  "ui.10,15,4",  "ui.10,0,5",   "ui.10,1,5",   "ui.10,2,5",   "ui.10,3,5",
        "ui.10,4,5",   "ui.10,5,5",   "ui.10,6,5",   "ui.10,7,5",   "ui.10,8,5",   "ui.10,9,5",   "ui.10,10,5",
        "ui.10,11,5",  "ui.10,12,5",  "ui.10,13,5",  "ui.10,14,5",  "ui.10,15,5",  "ui.10,0,6",   "ui.10,1,6",
        "ui.10,2,6",   "ui.10,3,6",   "ui.10,4,6",   "ui.10,5,6",   "ui.10,6,6",   "ui.10,7,6",   "ui.10,8,6",
        "ui.10,9,6",   "ui.10,10,6",  "ui.10,11,6",  "ui.10,12,6",  "ui.10,13,6",  "ui.10,14,6",  "ui.10,15,6",
        "ui.10,0,7",   "ui.10,1,7",   "ui.10,2,7",   "ui.10,3,7",   "ui.10,4,7",   "ui.10,5,7",   "ui.10,6,7",
        "ui.10,7,7",   "ui.10,8,7",   "ui.10,9,7",   "ui.10,10,7",  "ui.10,11,7",  "ui.10,12,7",  "ui.10,13,7",
        "ui.10,14,7",  "ui.10,15,7",  "ui.10,0,8",   "ui.10,1,8",   "ui.10,2,8",   "ui.10,3,8",   "ui.10,4,8",
        "ui.10,5,8",   "ui.10,6,8",   "ui.10,7,8",   "ui.10,8,8",   "ui.10,9,8",   "ui.10,10,8",  "ui.10,11,8",
        "ui.10,12,8",  "ui.10,13,8",  "ui.10,14,8",  "ui.10,15,8",  "ui.10,0,9",   "ui.10,1,9",   "ui.10,2,9",
        "ui.10,3,9",   "ui.10,4,9",   "ui.10,5,9",   "ui.10,6,9",   "ui.10,7,9",   "ui.10,8,9",   "ui.10,9,9",
        "ui.10,10,9",  "ui.10,11,9",  "ui.10,12,9",  "ui.10,13,9",  "ui.10,14,9",  "ui.10,15,9",  "ui.10,0,10",
        "ui.10,1,10",  "ui.10,2,10",  "ui.10,3,10",  "ui.10,4,10",  "ui.10,5,10",  "ui.10,6,10",  "ui.10,7,10",
        "ui.10,8,10",  "ui.10,9,10",  "ui.10,10,10", "ui.10,11,10", "ui.10,12,10", "ui.10,13,10", "ui.10,14,10",
        "ui.10,15,10", "ui.10,0,11",  "ui.10,1,11",  "ui.10,2,11",  "ui.10,3,11",  "ui.10,4,11",  "ui.10,5,11",
        "ui.10,6,11",  "ui.10,7,11",  "ui.10,8,11",  "ui.10,9,11",  "ui.10,10,11", "ui.10,11,11", "ui.10,12,11",
        "ui.10,13,11", "ui.10,14,11", "ui.10,15,11", "ui.10,0,12",  "ui.10,1,12",  "ui.10,2,12",  "ui.10,3,12",
        "ui.10,4,12",  "ui.10,5,12",  "ui.10,6,12",  "ui.10,7,12",  "ui.10,8,12",  "ui.10,9,12",  "ui.10,10,12",
        "ui.10,11,12", "ui.10,12,12", "ui.10,13,12", "ui.10,14,12", "ui.10,15,12", "ui.10,0,13",  "ui.10,1,13",
        "ui.10,2,13",  "ui.10,3,13",  "ui.10,4,13",  "ui.10,5,13",  "ui.10,6,13",  "ui.10,7,13",  "ui.10,8,13",
        "ui.10,9,13",  "ui.10,10,13", "ui.10,11,13", "ui.10,12,13", "ui.10,13,13", "ui.10,14,13", "ui.10,15,13",
        "ui.10,0,14",  "ui.10,1,14",  "ui.10,2,14",  "ui.10,3,14",  "ui.10,4,14",  "ui.10,5,14",  "ui.10,6,14",
        "ui.10,7,14",  "ui.10,8,14",  "ui.10,9,14",  "ui.10,10,14", "ui.10,11,14", "ui.10,12,14", "ui.10,13,14",
        "ui.10,14,14", "ui.10,15,14", "ui.10,0,15",  "ui.10,1,15",  "ui.10,2,15",  "ui.10,3,15",  "ui.10,4,15",
        "ui.10,5,15",  "ui.10,6,15",  "ui.10,7,15",  "ui.10,8,15",  "ui.10,9,15",  "ui.10,10,15", "ui.10,11,15",
        "ui.10,12,15", "ui.10,13,15", "ui.10,14,15", "ui.10,15,15",
    };
    const std::vector< std::string > arr(tiles);
    tile_load_arr("data/gfx/ui/ui_horiz1.tga", "ui_box10", 8, 8, arr);
  }
}