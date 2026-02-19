//
// Copyright goblinhack@gmail.com
//

#ifndef _MY_WID_TILES_HPP_
#define _MY_WID_TILES_HPP_

#include "my_types.hpp"

#include <array>

using wid_tilesp = class WidTiles *;

class WidTiles
{
public:
  WidTiles() = default;

  ~WidTiles() = default;

  int                                       across = {};
  int                                       down   = {};
  int                                       tile_w = {};
  int                                       tile_h = {};
  double                                    scale  = {};
  std::array< std::array< Tilep, 32 >, 32 > tile {};
};

bool wid_tiles_init();

void wid_tiles_fini();

wid_tilesp wid_tiles_load(std::string name, double scale);
wid_tilesp wid_tiles_find(const std::string &name);

#endif
