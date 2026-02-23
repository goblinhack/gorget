//
// Copyright goblinhack@gmail.com
//

#include <print>

#include "my_level.hpp"

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
  bool const debug = false;

  auto at = thing_at(t);
  if (debug) {
    std::println("start (player {},{})", at.x, at.y);
    for (auto p : path) {
      std::print("({},{}), ", p.x, p.y);
    }
    std::println("");
    std::println("");
  }

  //
  // Trim short paths
  //
  if (path.size() == 2) {
    auto px = at.x;
    auto py = at.y;

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
    if (px - 1 == mx && py + 1 == my && px == nx && py + 1 == ny && ! level_alive_is_obs_to_cursor_path(g, v, l, spoint(px - 1, py))) {
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
    if (px - 1 == mx && py + 1 == my && px - 1 == nx && py == ny && ! level_alive_is_obs_to_cursor_path(g, v, l, spoint(px, py + 1))) {
      path.erase(path.begin());
      return;
    }

    if (px + 1 == mx && py + 1 == my && px == nx && py + 1 == ny && ! level_alive_is_obs_to_cursor_path(g, v, l, spoint(px + 1, py))) {
      path.erase(path.begin());
      return;
    }

    if (px + 1 == mx && py + 1 == my && px + 1 == nx && py == ny && ! level_alive_is_obs_to_cursor_path(g, v, l, spoint(px, py + 1))) {
      path.erase(path.begin());
      return;
    }

    if (px - 1 == mx && py - 1 == my && px == nx && py - 1 == ny && ! level_alive_is_obs_to_cursor_path(g, v, l, spoint(px - 1, py))) {
      path.erase(path.begin());
      return;
    }

    if (px - 1 == mx && py - 1 == my && px - 1 == nx && py == ny && ! level_alive_is_obs_to_cursor_path(g, v, l, spoint(px, py - 1))) {
      path.erase(path.begin());
      return;
    }

    if (px + 1 == mx && py - 1 == my && px == nx && py - 1 == ny && ! level_alive_is_obs_to_cursor_path(g, v, l, spoint(px + 1, py))) {
      path.erase(path.begin());
      return;
    }

    if (px + 1 == mx && py - 1 == my && px + 1 == nx && py == ny && ! level_alive_is_obs_to_cursor_path(g, v, l, spoint(px, py - 1))) {
      path.erase(path.begin());
      return;
    }
  }

  for (; /*ever*/;) {
    auto   modified = false;
    size_t i        = 0;

    for (; /*ever*/;) {
      if (i + 2 >= path.size()) {
        break;
      }

      if (debug) {
        for (auto p : path) {
          std::print("({},{}), ", p.x, p.y);
        }
        std::println("");
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

      if (px - 1 == mx && py + 1 == my && px == nx && py + 1 == ny && ! level_alive_is_obs_to_cursor_path(g, v, l, spoint(px - 1, py))) {
        path.erase(path.begin() + i + 1);
        modified = true;
        break;
      }

      if (px - 1 == mx && py + 1 == my && px - 1 == nx && py == ny && ! level_alive_is_obs_to_cursor_path(g, v, l, spoint(px, py + 1))) {
        path.erase(path.begin() + i + 1);
        modified = true;
        break;
      }

      if (px + 1 == mx && py + 1 == my && px == nx && py + 1 == ny && ! level_alive_is_obs_to_cursor_path(g, v, l, spoint(px + 1, py))) {
        path.erase(path.begin() + i + 1);
        modified = true;
        break;
      }

      if (px + 1 == mx && py + 1 == my && px + 1 == nx && py == ny && ! level_alive_is_obs_to_cursor_path(g, v, l, spoint(px, py + 1))) {
        path.erase(path.begin() + i + 1);
        modified = true;
        break;
      }

      if (px - 1 == mx && py - 1 == my && px == nx && py - 1 == ny && ! level_alive_is_obs_to_cursor_path(g, v, l, spoint(px - 1, py))) {
        path.erase(path.begin() + i + 1);
        modified = true;
        break;
      }

      if (px - 1 == mx && py - 1 == my && px - 1 == nx && py == ny && ! level_alive_is_obs_to_cursor_path(g, v, l, spoint(px, py - 1))) {
        path.erase(path.begin() + i + 1);
        modified = true;
        break;
      }

      if (px + 1 == mx && py - 1 == my && px == nx && py - 1 == ny && ! level_alive_is_obs_to_cursor_path(g, v, l, spoint(px + 1, py))) {
        path.erase(path.begin() + i + 1);
        modified = true;
        break;
      }

      if (px + 1 == mx && py - 1 == my && px + 1 == nx && py == ny && ! level_alive_is_obs_to_cursor_path(g, v, l, spoint(px, py - 1))) {
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

  if (static_cast< unsigned int >(! path.empty()) != 0U) {
    if (path[ 0 ] == at) {
      path.erase(path.begin());
    }
  }

  if (debug) {
    std::println("final (player {},{})", at.x, at.y);
    for (auto p : path) {
      std::print("({},{}), ", p.x, p.y);
    }
    std::println("");
    std::println("");
  }
}
