//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_level.hpp"
#include "my_main.hpp"
#include "my_ptrcheck.hpp"
#include "my_tile.hpp"
#include "my_tp_callbacks.hpp"

//
// Shorten paths, but don't cut corners
//
// x..##    x..##
// xx.##    .x.##
// .xx## -> ..x##
// ..xxx    ..xxx
//
void thing_path_shorten(Gamep g, Levelsp v, Levelp l, Thingp t, std::vector< spoint > &path)
{
  //
  // Trim short paths
  //
  if (path.size() == 2) {
    auto px = t->at.x;
    auto py = t->at.y;

    auto n  = path[ 0 ];
    auto nx = n.x;
    auto ny = n.y;

    auto m  = path[ 1 ];
    auto mx = m.x;
    auto my = m.y;

    //
    // .....     .....
    // .....     .....
    // ..@.. --> ..@..
    // .mn..     .m...
    // .....     .....
    //
    // .....     .....
    // .....     .....
    // .X@.. --> .X@..
    // .mn..     .mn..
    // .....     .....
    //
    if (px - 1 == mx && py + 1 == my && px == nx && py + 1 == ny
        && ! level_is_obs_to_cursor_path(g, v, l, spoint(px - 1, py))) {
      path.erase(path.begin());
      return;
    }

    //
    // .....     .....
    // .....     .....
    // .n@.. --> ..@..
    // .m...     .m...
    // .....     .....
    //
    // .....     .....
    // .....     .....
    // .n@.. --> .n@..
    // .mX..     .mX..
    // .....     .....
    //
    if (px - 1 == mx && py + 1 == my && px - 1 == nx && py == ny
        && ! level_is_obs_to_cursor_path(g, v, l, spoint(px, py + 1))) {
      path.erase(path.begin());
      return;
    }

    if (px + 1 == mx && py + 1 == my && px == nx && py + 1 == ny
        && ! level_is_obs_to_cursor_path(g, v, l, spoint(px + 1, py))) {
      path.erase(path.begin());
      return;
    }

    if (px + 1 == mx && py + 1 == my && px + 1 == nx && py == ny
        && ! level_is_obs_to_cursor_path(g, v, l, spoint(px, py + 1))) {
      path.erase(path.begin());
      return;
    }

    if (px - 1 == mx && py - 1 == my && px == nx && py - 1 == ny
        && ! level_is_obs_to_cursor_path(g, v, l, spoint(px - 1, py))) {
      path.erase(path.begin());
      return;
    }

    if (px - 1 == mx && py - 1 == my && px - 1 == nx && py == ny
        && ! level_is_obs_to_cursor_path(g, v, l, spoint(px, py - 1))) {
      path.erase(path.begin());
      return;
    }

    if (px + 1 == mx && py - 1 == my && px == nx && py - 1 == ny
        && ! level_is_obs_to_cursor_path(g, v, l, spoint(px + 1, py))) {
      path.erase(path.begin());
      return;
    }

    if (px + 1 == mx && py - 1 == my && px + 1 == nx && py == ny
        && ! level_is_obs_to_cursor_path(g, v, l, spoint(px, py - 1))) {
      path.erase(path.begin());
      return;
    }
  }

  if (path.size()) {
    if (path[ 0 ] == t->at) {
      path.erase(path.begin());
    }
  }

  for (; /*ever*/;) {
    auto   modified = false;
    size_t i        = 0;

    for (; /*ever*/;) {
      if (i + 2 >= path.size()) {
        break;
      }

      auto p  = path[ i ];
      auto px = p.x;
      auto py = p.y;

      auto n  = path[ i + 1 ];
      auto nx = n.x;
      auto ny = n.y;

      auto m  = path[ i + 2 ];
      auto mx = m.x;
      auto my = m.y;

      if (px - 1 == mx && py + 1 == my && px == nx && py + 1 == ny
          && ! level_is_obs_to_cursor_path(g, v, l, spoint(px - 1, py))) {
        path.erase(path.begin() + i + 1);
        modified = true;
        break;
      }

      if (px - 1 == mx && py + 1 == my && px - 1 == nx && py == ny
          && ! level_is_obs_to_cursor_path(g, v, l, spoint(px, py + 1))) {
        path.erase(path.begin() + i + 1);
        modified = true;
        break;
      }

      if (px + 1 == mx && py + 1 == my && px == nx && py + 1 == ny
          && ! level_is_obs_to_cursor_path(g, v, l, spoint(px + 1, py))) {
        path.erase(path.begin() + i + 1);
        modified = true;
        break;
      }

      if (px + 1 == mx && py + 1 == my && px + 1 == nx && py == ny
          && ! level_is_obs_to_cursor_path(g, v, l, spoint(px, py + 1))) {
        path.erase(path.begin() + i + 1);
        modified = true;
        break;
      }

      if (px - 1 == mx && py - 1 == my && px == nx && py - 1 == ny
          && ! level_is_obs_to_cursor_path(g, v, l, spoint(px - 1, py))) {
        path.erase(path.begin() + i + 1);
        modified = true;
        break;
      }

      if (px - 1 == mx && py - 1 == my && px - 1 == nx && py == ny
          && ! level_is_obs_to_cursor_path(g, v, l, spoint(px, py - 1))) {
        path.erase(path.begin() + i + 1);
        modified = true;
        break;
      }

      if (px + 1 == mx && py - 1 == my && px == nx && py - 1 == ny
          && ! level_is_obs_to_cursor_path(g, v, l, spoint(px + 1, py))) {
        path.erase(path.begin() + i + 1);
        modified = true;
        break;
      }

      if (px + 1 == mx && py - 1 == my && px + 1 == nx && py == ny
          && ! level_is_obs_to_cursor_path(g, v, l, spoint(px, py - 1))) {
        path.erase(path.begin() + i + 1);
        modified = true;
        break;
      }

      i++;
    }

    if (! modified) {
      break;
    }
  }
}
