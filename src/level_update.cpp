//
// Copyright goblinhack@gmail.com
//

#include "my_bits.hpp"
#include "my_callstack.hpp"
#include "my_globals.hpp"
#include "my_level.hpp"
#include "my_main.hpp"
#include "my_random.hpp"
#include "my_tile.hpp"

#include <map>
#include <string.h>

void level_update_paths_set(Gamep g, Levelsp v, Levelp l, spoint p)
{
  TRACE_NO_INDENT();

  l->request_to_update_paths = true;

  for (auto dx = -1; dx <= 1; dx++) {
    for (auto dy = -1; dy <= 1; dy++) {
      auto x = p.x + dx;
      auto y = p.y + dy;
      if (! is_oob(x, y)) {
        l->is_modified_tile[ x ][ y ] = 1U;
      }
    }
  }
}

void level_update_paths(Gamep g, Levelsp v, Levelp l)
{
  TRACE_NO_INDENT();

  if (! l->request_to_update_paths) {
    return;
  }
  l->request_to_update_paths = false;

  level_update_tiles(g, v, l);
  level_dmap(g, v, l);

  memset(l->is_modified_tile, 0, SIZEOF(l->is_modified_tile));
}
