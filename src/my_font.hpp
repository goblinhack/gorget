//
// Copyright goblinhack@gmail.com
//

#ifndef _MY_FONT_HPP_
#define _MY_FONT_HPP_

#include "my_tile.hpp"
#include <array>

extern Fontp font_ui;

#define FONT_CHAR_MAX    ((int) ((int) '~' + 8))
#define FONT_CHAR_MIN    ((int) ' ')
#define FONT_CHAR_CURSOR ((int) ((int) '~' + 1))

#define FONT_TILENAME_UNKNOWN_STR "1.99"
#define FONT_TILENAME_BLOCK_STR   "1.97"
#define FONT_TILENAME_POINTER_STR "1.100"

void  font_fini();
bool  font_init();
Fontp font_find(std::string /*file*/);

class Font
{
public:
  Font()  = default;
  ~Font() = default;
  std::array< int, FONT_CHAR_MAX + 1 >   u_to_c {};
  std::array< Tilep, FONT_CHAR_MAX + 1 > cache {};
  int                                    tile_index;
  Tilep                                  font_get_tile(int u);
};
#endif
