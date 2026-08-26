//
// Copyright goblinhack@gmail.com
//

#ifndef MY_WID_TILES_HPP
#define MY_WID_TILES_HPP

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

[[nodiscard]] auto wid_tiles_init() -> bool;

auto wid_tiles_fini() -> void;

[[nodiscard]] auto wid_tiles_load(const std::string &name, float scale) -> wid_tilesp;
[[nodiscard]] auto wid_tiles_find(const std::string &file) -> wid_tilesp;

#endif
