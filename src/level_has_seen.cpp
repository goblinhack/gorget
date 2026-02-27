//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_fov_map.hpp"
#include "my_fov_map_inlines.hpp"
#include "my_game.hpp"
#include "my_level.hpp"
#include "my_level_inlines.hpp"
#include "my_thing_inlines.hpp"

auto level_has_seen(Gamep g, Levelsp v, Levelp l, const spoint &p) -> bool
{
  TRACE();

  auto *player = thing_player(g);
  if (player == nullptr) [[unlikely]] {
    return false;
  }

  auto *ext = thing_ext_struct(g, player);
  if (ext == nullptr) [[unlikely]] {
    return false;
  }

  if (is_oob(p)) [[unlikely]] {
    return false;
  }

  return static_cast< unsigned int >(fov_map_get(&ext->has_seen, p.x, p.y)) != 0U;
}

//
// Update all tiles the player has seen.
//
void level_has_seen_update(Gamep g, Levelsp v, Levelp l)
{
  TRACE();

  auto *player = thing_player(g);
  if (player == nullptr) [[unlikely]] {
    return;
  }

  auto *ext = thing_ext_struct(g, player);
  if (ext == nullptr) [[unlikely]] {
    return;
  }

  for (auto x = 0; x < MAP_WIDTH; x++) {
    for (auto y = 0; y < MAP_HEIGHT; y++) {
      if (static_cast< unsigned int >(fov_map_get(&ext->has_seen, x, y)) != 0U) {
        l->player_has_seen_tile_cache[ x ][ y ] = 1U;
      } else {
        l->player_has_seen_tile_cache[ x ][ y ] = 0U;
      }
    }
  }
}
