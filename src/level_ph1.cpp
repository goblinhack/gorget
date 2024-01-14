//
// Copyright Neil McGill, goblinhack@gmail.com
//

//
// Implements layered cycles that can be used to then create a set of rooms
//

#include <list>

#include "my_array_bounds_check.hpp"
#include "my_dmap.hpp"
#include "my_level_ph1.hpp"
#include "my_main.hpp"

static bool debug_enabled = false;

/*
 * Start with a grid of nodes and a start point.
 *
 *    x x x x x
 *
 *    x x S x x
 *
 *    x x x x x
 *
 *    x x x x x
 *
 *    x x x x x
 *
 * Recursive snake walk from a random start. Stop once you have a loop.
 *
 *    1-1-1-1 x
 *          |
 *    x 1-1-1 x
 *      |   |
 *    x 1-1-1-1
 *
 *    x x x x x
 *
 *    x x x x x
 *
 * The above is depth 1 of our loop. Choose an adjacent node for depth 2
 *
 *    1-1-1-1 x
 *          |
 *    x 1-1-1 x
 *      |   |
 *    x 1-1-1-1
 *      .   .
 *    x D-2-D x
 *      |   |
 *    x 2-2-2 x
 *
 * Again stop when a loop. Choose random 1 - 2 connections and make those doors.
 *
 * Repeat for depth 3
 *
 *    1-1-1-1 x
 *          |
 *    x 1-1-1 x
 *      |   |
 *    x 1-1-1-1
 *      .   .
 *    x D-2-D.D
 *      |   | |
 *    x 2-2-2 3
 *
 * Remove disconnected nodes.
 *
 *    - 1-1-1 -
 *          |
 *    - 1-1-1 -
 *      |   |
 *    - 1-1-1-1
 *      .   .
 *    - D-2-D.D
 *      |   | |
 *    - 2-2-2 3
 *
 * Do a djkstra flood from a random end point in 3
 *
 *    - 1-2-3 -
 *          |
 *    - 2-4-4 -
 *      |   |
 *    - 3-4-6-4
 *      .   .
 *    - 4-5-7=8
 *      |   | |
 *    - 4-5-6 9
 *
 * Choose the furthest point as the start.
 *
 *      S-1-1
 *          |
 *      1-1-1
 *      |   |
 *      1-1-1-1
 *      .   .
 *      2-2-2=3
 *      |   | |
 *      2-2-2 E
 *
 * Place a key room one per depth. A key need not be a real key, but
 * something that unlocks an node between 1 and 2
 *
 *      S-1-1
 *          |
 *      1-1-*
 *      |   |
 *      1-1-1-1
 *      .   .
 *      2-2-2=3
 *      |   | |
 *      2-2-* E
 */

void LevelPh1::construct(void)
{
redo:
  init_nodes();

  //
  // Place the depth and join up the nodes. Add occasional
  // secret jumps between nodes in the depth
  //
  auto pass        = 1;
  auto depth       = 1;
  auto depth_limit = LEVEL_PH1_LOCK_DEPTH;

  while (depth <= depth_limit) {
    set_max_depth();

    int placed = snake_walk(depth, 6, pass);

    if (debug_enabled) {
      LOG("Phase1: Level depth %d placed %d nodes", depth, placed);
    }

    if (! placed) {
      break;
    }

    //
    // We need at least 2 nodes per depth as one can be a lock
    // and the other a key per depth
    //
    if (depth == 1) {
      //
      // Need an extra one on level one for the entrance
      //
      if (placed < 3) {
        debug("failed initial level, did not place enough nodes");
        if (debug_enabled) {
          LOG("Phase1: Failed level depth %d placed only %d nodes, redo", depth, placed);
        }
        goto redo;
      }
    } else {
      if (placed < 2) {
        debug("failed level, did not place enough nodes at depth");
        if (debug_enabled) {
          LOG("Phase1: Failed level depth %d placed only %d nodes, redo", depth, placed);
        }
        goto redo;
      }
    }

    join_nodes_of_same_depth(depth, pass);
    depth++;
  }

  set_max_depth();

  if (max_depth < 2) {
    debug("redo, not enough depth challenges");
    goto redo;
  }

  if (max_vdepth < grid_height - 2) {
    debug("redo, not enough vertical depth challenges");
    goto redo;
  }

  debug("done first pass of rooms at same depth");

  for (auto join = 1; join < depth - 1; join++) {
    join_depth_to_next_depth(join, pass);
  }
  debug("done first pass of rooms and joined rooms to next depth");

  remove_stubs();
  debug("removed stubs");

  for (auto join = 1; join < depth - 2; join++) {
    join_depth_secret(join, pass);
  }
  debug("done first pass of rooms and joined secret rooms");

  //
  // Now place secret rooms and join them to the main depth via secret doors
  //
  pass              = 2;
  auto secret_depth = 1;
  while (secret_depth < 10) {
    auto placed = snake_walk(secret_depth, 10, pass);

    if (debug_enabled) {
      LOG("Phase1: Level depth %d placed %d secret nodes", secret_depth, placed);
    }

    if (! placed) {
      break;
    }

    join_nodes_of_same_depth(secret_depth, pass);
    secret_depth++;
  }
  debug("done snake walk of secret rooms");

  for (auto join = 1; join < depth; join++) {
    join_depth_to_next_depth(join, pass);
  }
  debug("done first pass of secret rooms and joined rooms to next depth");

  for (auto join = 1; join < depth; join++) {
    join_depth_secret(join, pass);
  }
  debug("done second pass of secret rooms and joined secret rooms to next depth");

  remove_stubs();
  debug("removed stubs");

  set_max_depth();
  debug("placed keys");

  //
  // Add start and exit
  //
  if (! place_entrance()) {
    debug("redo, failed to place entrance");
    goto redo;
  }

  if (! place_exit()) {
    debug("redo, failed to place exit");
    goto redo;
  }

  //
  // First time we consider secret exits
  //
  create_path_to_exit(1);
  debug("created path to exit");

  //
  // Second time we ignore them to ensure they are not considered
  // as on the main path
  //
  if (! create_path_to_exit(2)) {
    debug("redo, too short a path to exit");
    goto redo;
  }

  //
  // Make nodes not on the direct path to the exit, bi directional so you cannot get stuck
  //
  make_paths_off_critical_path_reachable();
  debug("made critical paths reachable");

  //
  // Add keys for moving between levels
  //
  for (auto depth = 2; depth <= max_depth; depth++) {
    if (! place_lock(depth, 1)) {
      debug("redo, failed to place lock");
      goto redo;
    }
  }
  debug("placed locks");

  //
  // Get rid of other paths that avoid the lock.
  //
  for (auto depth = 2; depth <= max_depth; depth++) {
    hide_other_locks(depth, 1);
  }
  debug("hid other locks");

  for (auto depth = 1; depth < max_depth; depth++) {
    if (! place_key(depth, 1)) {
      debug("redo, failed to place key");
      goto redo;
    }
  }
  debug("placed keys");

  //
  // Ensure each key can reach each lock
  //
  for (auto depth = 1; depth < max_depth; depth++) {
    create_path_lock_to_key(depth);
  }
  debug("created path from keys to locks");

  //
  // If the exit flow of the level matches that of the direction
  // then we don't really have a different direction to consider.
  //
  if (0) {
    remove_redundant_directions();

    while (remove_dead_end_paths()) {}
  }

  remove_stubs();

  IF_DEBUG2
  {
    dump();
    LOG("Final map: ^^^^^^^^^^");
  }

  ok = true;
}

void LevelPh1::dump(void)
{
  const auto                             step   = 5;
  const auto                             center = 3;
  const int                              h      = (LEVEL_PH1_HEIGHT + 1) * step;
  const int                              w      = (LEVEL_PH1_WIDTH + 1) * step;
  std::array< std::array< char, h >, w > out;

  for (auto y = 0; y < h; y++) {
    for (auto x = 0; x < w; x++) {
      set(out, x, y, ' ');
    }
  }

  for (auto y = 0; y < grid_height; y++) {
    for (auto x = 0; x < grid_width; x++) {
      auto ox   = (x * step) + center - 1;
      auto oy   = (y * step) + center - 1;
      auto node = get_node_ptr(x, y);
      if (node->has_door_down) {
        set(out, ox, oy + 1, '|');
        set(out, ox, oy + 2, '|');
      }
      if (node->has_door_up) {
        set(out, ox, oy - 1, '|');
        set(out, ox, oy - 2, '|');
      }
      if (node->has_door_left) {
        set(out, ox - 1, oy, '-');
        set(out, ox - 2, oy, '-');
      }
      if (node->has_door_right) {
        set(out, ox + 1, oy, '-');
        set(out, ox + 2, oy, '-');
      }
      if (node->has_secret_exit_down) {
        set(out, ox, oy + 1, '?');
        set(out, ox, oy + 2, '?');
      }
      if (node->has_secret_exit_up) {
        set(out, ox, oy - 1, '?');
        set(out, ox, oy - 2, '?');
      }
      if (node->has_secret_exit_left) {
        set(out, ox - 1, oy, '?');
        set(out, ox - 2, oy, '?');
      }
      if (node->has_secret_exit_right) {
        set(out, ox + 1, oy, '?');
        set(out, ox + 2, oy, '?');
      }
      if (node->dir_up) {
        set(out, ox - 1, oy + 1, '^');
      }
      if (node->dir_down) {
        set(out, ox + 1, oy - 1, 'v');
      }
      if (node->dir_left) {
        set(out, ox - 1, oy + 1, '<');
      }
      if (node->dir_right) {
        set(out, ox + 1, oy + 1, '>');
      }

      auto t = 0;
      if (node->is_entrance) {
        set(out, ox - 1, oy, 'S');
        t++;
      }
      if (node->is_exit) {
        set(out, ox - 1, oy, 'E');
        t++;
      }
      if (node->is_lock) {
        set(out, ox - 1, oy, 'D');
        t++;
      }
      if (node->is_key) {
        set(out, ox - 1, oy, 'K');
        t++;
      }
      if (node->is_secret) {
        set(out, ox - 1, oy, 's');
        t++;
      }

      if (t > 1) {
        ERR("Too many node types S %d E %d D %d k %d", node->is_entrance, node->is_exit, node->is_lock, node->is_key);
      }

      if (node->depth == depth_obstacle) {
        set(out, ox, oy, 'O');
      } else if (node->depth) {
        set(out, ox, oy, (char) ('0' + node->depth));
      } else {
        set(out, ox, oy, '.');
      }
      if (node->on_critical_path) {
        set(out, ox - 1, oy - 1, '*');
      }
    }
  }

  for (auto y = 0; y < grid_height * step; y++) {
    std::string s;
    for (auto x = 0; x < grid_width * step; x++) {
      s += get(out, x, y);
    }
    if (s != "") {
      LOG("Phase1: [%s]", s.c_str());
    }
  }
  LOG("Phase1: -");

  for (auto y = 0; y < grid_height; y++) {
    for (auto x = 0; x < grid_width; x++) {
      auto node = get_node_ptr(x, y);
      if (node->has_door_down) {
        if (y == grid_height - 1) {
          ERR("Level1Node %d,%d has exit down off end of map", x, y);
        }
      }
      if (node->has_door_right) {
        if (x == grid_width - 1) {
          ERR("Level1Node %d,%d has exit right off end of map", x, y);
        }
      }
      if (node->has_door_left) {
        if (x == 0) {
          ERR("Level1Node %d,%d has exit left off end of map", x, y);
        }
      }
      if (node->has_door_up) {
        if (y == 0) {
          ERR("Level1Node %d,%d has exit up off end of map", x, y);
        }
      }
      if (node->has_secret_exit_down) {
        if (y == grid_height - 1) {
          ERR("Level1Node %d,%d has secret exit down off end of map", x, y);
        }
      }
      if (node->has_secret_exit_right) {
        if (x == grid_width - 1) {
          ERR("Level1Node %d,%d has secret exit right off end of map", x, y);
        }
      }
      if (node->has_secret_exit_left) {
        if (x == 0) {
          ERR("Level1Node %d,%d has secret exit left off end of map", x, y);
        }
      }
      if (node->has_secret_exit_up) {
        if (y == 0) {
          ERR("Level1Node %d,%d has secret exit up off end of map", x, y);
        }
      }
    }
  }

  for (auto y = 0; y < grid_height; y++) {
    for (auto x = 0; x < grid_width; x++) {
      auto node = get_node_ptr(x, y);
      if (node->has_door_down) {
        auto o = get_node_ptr(x, y + 1);
        if (! o || ! o->depth) {
          ERR("Level1Node %d,%d has exit down but no node exists", x, y);
        }
      }
      if (node->has_door_right) {
        auto o = get_node_ptr(x + 1, y);
        if (! o || ! o->depth) {
          ERR("Level1Node %d,%d has exit right but no node exists", x, y);
        }
      }
      if (node->has_door_left) {
        auto o = get_node_ptr(x - 1, y);
        if (! o || ! o->depth) {
          ERR("Level1Node %d,%d has exit left but no node exists", x, y);
        }
      }
      if (node->has_door_up) {
        auto o = get_node_ptr(x, y - 1);
        if (! o || ! o->depth) {
          ERR("Level1Node %d,%d has exit up but no node exists", x, y);
        }
      }
    }
  }

  for (auto y = 0; y < grid_height; y++) {
    for (auto x = 0; x < grid_width; x++) {
      auto node = get_node_ptr(x, y);
      if (node->has_door_down) {
        auto o = get_node_ptr(x, y + 1);
        if (o->depth == depth_obstacle) {
          ERR("Level1Node %d,%d has exit down but that node is an obstacle", x, y);
        }
      }
      if (node->has_door_right) {
        auto o = get_node_ptr(x + 1, y);
        if (o->depth == depth_obstacle) {
          ERR("Level1Node %d,%d has exit right but that node is an obstacle", x, y);
        }
      }
      if (node->has_door_left) {
        auto o = get_node_ptr(x - 1, y);
        if (o->depth == depth_obstacle) {
          ERR("Level1Node %d,%d has exit left but that node is an obstacle", x, y);
        }
      }
      if (node->has_door_up) {
        auto o = get_node_ptr(x, y - 1);
        if (o->depth == depth_obstacle) {
          ERR("Level1Node %d,%d has exit up but that node is an obstacle", x, y);
        }
      }
      if (node->has_secret_exit_down) {
        auto o = get_node_ptr(x, y + 1);
        if (o->depth == depth_obstacle) {
          ERR("Level1Node %d,%d has secret exit down but that node is an obstacle", x, y);
        }
      }
      if (node->has_secret_exit_right) {
        auto o = get_node_ptr(x + 1, y);
        if (o->depth == depth_obstacle) {
          ERR("Level1Node %d,%d has secret exit right but that node is an obstacle", x, y);
        }
      }
      if (node->has_secret_exit_left) {
        auto o = get_node_ptr(x - 1, y);
        if (o->depth == depth_obstacle) {
          ERR("Level1Node %d,%d has secret exit left but that node is an obstacle", x, y);
        }
      }
      if (node->has_secret_exit_up) {
        auto o = get_node_ptr(x, y - 1);
        if (o->depth == depth_obstacle) {
          ERR("Level1Node %d,%d has secret exit up but that node is an obstacle", x, y);
        }
      }
    }
  }

  for (auto y = 0; y < grid_height; y++) {
    for (auto x = 0; x < grid_width; x++) {
      auto node = get_node_ptr(x, y);
      if (node->has_door_down) {
        if (node->has_secret_exit_down) {
          ERR("Level1Node %d,%d has both normal and secret exits down", x, y);
        }
      }
      if (node->has_door_right) {
        if (node->has_secret_exit_right) {
          ERR("Level1Node %d,%d has both normal and secret exits right", x, y);
        }
      }
      if (node->has_door_left) {
        if (node->has_secret_exit_left) {
          ERR("Level1Node %d,%d has both normal and secret exits left", x, y);
        }
      }
      if (node->has_door_up) {
        if (node->has_secret_exit_up) {
          ERR("Level1Node %d,%d has both normal and secret exits up", x, y);
        }
      }
    }
  }
}

void LevelPh1::debug(std::string msg)
{
  if (! debug_enabled) {
    return;
  }

  dump();
  LOG("Phase1: ^^^^^ %s ^^^^^", msg.c_str());
}

int LevelPh1::offset(const int x, const int y) const
{
  auto offset = grid_width * y;
  offset += x;

  return offset;
}

bool LevelPh1::is_oob(const int x, const int y) const
{
  return ((x < 0) || (x >= grid_width) || (y < 0) || (y >= grid_height));
}

Level1Node *LevelPh1::node_addr(const int x, const int y)
{
  if (unlikely(is_oob(x, y))) {
    return nullptr;
  }

  return (&nodes[ offset(x, y) ]);
}

void LevelPh1::putn(const int x, const int y, const Level1Node n)
{
  auto p = node_addr(x, y);
  if (p != nullptr) {
    *p = n;
  }
}

Level1Node *LevelPh1::get_node_ptr(const int x, const int y) { return node_addr(x, y); }

const Level1Node *LevelPh1::get_node_ptr_const(const int x, const int y) const
{
  if (unlikely(is_oob(x, y))) {
    return nullptr;
  }

  return (&nodes[ offset(x, y) ]);
}

point LevelPh1::random_dir(void)
{
  auto dx = 0, dy = 0;

  switch (pcg_random_range(0, 4)) {
    case 0 :
      dx = -1;
      dy = 0;
      break;
    case 1 :
      dx = 1;
      dy = 0;
      break;
    case 2 :
      dx = 0;
      dy = -1;
      break;
    case 3 :
      dx = 0;
      dy = 1;
      break;
  }
  return (point(dx, dy));
}

void LevelPh1::random_dir(int *dx, int *dy)
{
  switch (pcg_random_range(0, 4)) {
    case 0 :
      *dx = -1;
      *dy = 0;
      break;
    case 1 :
      *dx = 1;
      *dy = 0;
      break;
    case 2 :
      *dx = 0;
      *dy = -1;
      break;
    case 3 :
      *dx = 0;
      *dy = 1;
      break;
  }
}

//
// Set up nodes so they know their coords
//
void LevelPh1::init_nodes(void)
{
  nodes.resize(grid_width * grid_height);

  std::vector< std::pair< point, point > > s;

  for (auto x = 0; x < grid_width; x++) {
    for (auto y = 0; y < grid_height; y++) {
      auto n              = get_node_ptr(x, y);
      n->depth            = 0;
      n->pass             = 0;
      n->x                = x;
      n->y                = y;
      n->is_key           = false;
      n->is_lock          = false;
      n->is_entrance      = false;
      n->is_exit          = false;
      n->on_critical_path = false;
      n->dir_up           = false;
      n->dir_down         = false;
      n->dir_left         = false;
      n->dir_right        = false;
      n->set_has_door_up(false);
      n->set_has_door_down(false);
      n->set_has_door_left(false);
      n->set_has_door_right(false);
      n->set_has_secret_exit_up(false);
      n->set_has_secret_exit_down(false);
      n->set_has_secret_exit_left(false);
      n->set_has_secret_exit_right(false);
    }
  }

  auto obstacles = ((grid_width * grid_height) / 10);

  if (0) {
    while (obstacles--) {
      auto x = pcg_random_range(0, grid_width);
      auto y = pcg_random_range(0, grid_height);

      auto o   = get_node_ptr(x, y);
      o->depth = depth_obstacle;
    }
  }

  max_depth  = 0;
  max_vdepth = 0;
}

//
// Walk the depth randomly, ala snake until you hit your own tail,
// forking randomly also
//
bool LevelPh1::node_is_free(Level1Node *n) { return (n && ! n->depth); }

bool LevelPh1::node_is_a_room(Level1Node *n) { return (n && n->depth && (n->depth != depth_obstacle)); }

int LevelPh1::snake_walk(int depth, int max_placed, int pass)
{
  std::list< point > s;

  auto dx = 0;
  auto dy = 0;
  auto x  = 0;
  auto y  = 0;

  if (depth == 1) {
    if (pass == 1) {
      //
      // Start anywhere
      //
      auto tries = 100;
      while (tries--) {
        x = pcg_random_range(0, grid_width);
        y = 0;

        auto o = get_node_ptr(x, y);
        if (node_is_free(o)) {
          s.push_back(point(x, y));
          random_dir(&dx, &dy);
          dy = 0;
          break;
        }
      }

      if (tries < 0) {
        return 0;
      }
    } else {
      //
      // Start adjacent to a non hidden level node and connect to it
      //
      auto tries = 100;
      while (tries--) {
        x = pcg_random_range(0, grid_width);
        y = pcg_random_range(0, grid_height);
        random_dir(&dx, &dy);

        auto o = get_node_ptr(x, y);
        auto n = get_node_ptr(x + dx, y + dy);

        if (node_is_free(o) && node_is_a_room(n) && (n->pass != pass)) {
          s.push_back(point(x, y));

          if (dx == 1) {
            o->set_has_secret_exit_right(true);
            n->set_has_secret_exit_left(true);
          }

          if (dx == -1) {
            o->set_has_secret_exit_left(true);
            n->set_has_secret_exit_right(true);
          }

          if (dy == 1) {
            o->set_has_secret_exit_down(true);
            n->set_has_secret_exit_up(true);
          }

          if (dy == -1) {
            o->set_has_secret_exit_up(true);
            n->set_has_secret_exit_down(true);
          }
          break;
        }
      }

      if (tries < 0) {
        return 0;
      }
    }
  } else {
    if (pass == 1) {
      //
      // Else start adjacent next to the old max depth
      //
      auto tries = 100;
      while (tries--) {
        x = pcg_random_range(0, grid_width);
        y = max_vdepth;

        random_dir(&dx, &dy);

        auto o = get_node_ptr(x, y);
        auto n = get_node_ptr(x + dx, y + dy);

        if (node_is_free(o) && node_is_a_room(n) && (n->pass == pass) && (n->depth == depth - 1)) {
          s.push_back(point(x, y));

          if (dx == 1) {
            o->set_has_door_right(true);
            n->set_has_door_left(true);
          }

          if (dx == -1) {
            o->set_has_door_left(true);
            n->set_has_door_right(true);
          }

          if (dy == 1) {
            o->set_has_door_down(true);
            n->set_has_door_up(true);
          }

          if (dy == -1) {
            o->set_has_door_up(true);
            n->set_has_door_down(true);
          }
          break;
        }
      }

      if (tries < 0) {
        return 0;
      }
    } else {
      //
      // Else start adjacent next to the old secret depth
      //
      auto tries = 100;
      while (tries--) {
        x = pcg_random_range(0, grid_width);
        y = pcg_random_range(0, grid_height);
        random_dir(&dx, &dy);

        auto o = get_node_ptr(x, y);
        auto n = get_node_ptr(x + dx, y + dy);

        if (node_is_free(o) && node_is_a_room(n) && (n->pass == pass) && (n->depth == depth - 1)) {
          s.push_back(point(x, y));

          if (dx == 1) {
            o->set_has_secret_exit_right(true);
            n->set_has_secret_exit_left(true);
          }

          if (dx == -1) {
            o->set_has_secret_exit_left(true);
            n->set_has_secret_exit_right(true);
          }

          if (dy == 1) {
            o->set_has_secret_exit_down(true);
            n->set_has_secret_exit_up(true);
          }

          if (dy == -1) {
            o->set_has_secret_exit_up(true);
            n->set_has_secret_exit_down(true);
          }
          break;
        }
      }

      if (tries < 0) {
        return 0;
      }
    }
  }

  auto placed = 0;
  dy          = 0;

  do {
    auto p = s.front();
    s.pop_front();

    auto x = p.x;
    auto y = p.y;

    //
    // Get next empty cell
    //
    auto n = get_node_ptr(x, y);
    if (! n || n->depth) {
      continue;
    }

    if (n->pass && (n->pass != pass)) {
      continue;
    }

    placed++;
    n->depth = depth;
    n->pass  = pass;

    //
    // Change dir
    //
    random_dir(&dx, &dy);
    if (dy < 0) {
      if (pcg_random_range(0, 100) < 20) {
        dy = 0;
      }
    }
    if (dy > 0) {
      if (pcg_random_range(0, 100) < 20) {
        dy = 0;
      }
    }

    auto old = n;

    //
    // Create forks but make sure the old corridor knows
    // where the fork corridor is
    //
    if (placed < max_placed) {
      if (x < grid_width - 1) {
        auto f = get_node_ptr(x + 1, y);
        if (node_is_free(f)) {
          s.push_back(point(x + 1, y));
          n->set_has_door_right(true);
        }
      }
      if (x > 0) {
        auto f = get_node_ptr(x - 1, y);
        if (node_is_free(f)) {
          s.push_back(point(x - 1, y));
          n->set_has_door_left(true);
        }
      }

      if (pcg_random_range(0, 100) < 5) {
        if (y < grid_height - 1) {
          auto f = get_node_ptr(x, y + 1);
          if (node_is_free(f)) {
            s.push_back(point(x, y + 1));
            n->set_has_door_down(true);
          }
        }
      }

      if (y < depth + 2) {
        if (pcg_random_range(0, 100) < 5) {
          if (y > 0) {
            auto f = get_node_ptr(x, y - 1);
            if (node_is_free(f)) {
              s.push_back(point(x, y - 1));
              n->set_has_door_up(true);
            }
          }
        }
      }
      if (dy < 0) {
        dy = 0;
      }

      //
      // Get the next move, or change dir again if blocked.
      //
      n = get_node_ptr(x + dx, y + dy);
      if (! node_is_free(n)) {
        auto tries = 20;
        while (tries--) {
          random_dir(&dx, &dy);
          n = get_node_ptr(x + dx, y + dy);
          if (node_is_free(n)) {
            break;
          }
        }

        if (tries < 0) {
          continue;
        }
      }

      s.push_back(point(x + dx, y + dy));

      if (dx == 1) {
        old->set_has_door_right(true);
      }
      if (dx == -1) {
        old->set_has_door_left(true);
      }
      if (dy == 1) {
        old->set_has_door_down(true);
      }
      if (dy == -1) {
        old->set_has_door_up(true);
      }
    }

  } while (s.size());

  return placed;
}

void LevelPh1::join_nodes_of_same_depth(int depth, int pass)
{
  //
  // Connect up the nodes on the same depth
  //
  for (auto x = 0; x < grid_width; x++) {
    for (auto y = 0; y < grid_height; y++) {
      auto o = get_node_ptr(x, y);
      if (o->depth != depth) {
        continue;
      }

      if (o->pass && (o->pass != pass)) {
        continue;
      }

      if (o->has_door_right) {
        auto n = get_node_ptr(x + 1, y);
        if (n && (n->pass == pass) && (n->depth == depth)) {
          n->set_has_door_left(true);
        } else {
          o->set_has_door_right(false);
        }
      }

      if (o->has_door_left) {
        auto n = get_node_ptr(x - 1, y);
        if (n && (n->pass == pass) && (n->depth == depth)) {
          n->set_has_door_right(true);
        } else {
          o->set_has_door_left(false);
        }
      }

      if (o->has_door_down) {
        auto n = get_node_ptr(x, y + 1);
        if (n && (n->pass == pass) && (n->depth == depth)) {
          n->set_has_door_up(true);
        } else {
          o->set_has_door_down(false);
        }
      }

      if (o->has_door_up) {
        auto n = get_node_ptr(x, y - 1);
        if (n && (n->pass == pass) && (n->depth == depth)) {
          n->set_has_door_down(true);
        } else {
          o->set_has_door_up(false);
        }
      }
    }
  }
}

//
// Connect up the nodes to the next depth. We need at least one.
//
void LevelPh1::join_depth_to_next_depth(int depth, int pass)
{
  std::vector< std::pair< point, point > > s;

  for (auto x = 0; x < grid_width; x++) {
    for (auto y = 0; y < grid_height; y++) {
      auto o = get_node_ptr(x, y);
      if (o->depth != depth) {
        continue;
      }
      if (o->pass && (o->pass != pass)) {
        continue;
      }

      auto n = get_node_ptr(x + 1, y);
      if (n && (n->pass == pass) && (n->depth == depth + 1)) {
        s.push_back(std::make_pair(point(x, y), point(x + 1, y)));
      }

      n = get_node_ptr(x - 1, y);
      if (n && (n->pass == pass) && (n->depth == depth + 1)) {
        s.push_back(std::make_pair(point(x, y), point(x - 1, y)));
      }

      n = get_node_ptr(x, y + 1);
      if (n && (n->pass == pass) && (n->depth == depth + 1)) {
        s.push_back(std::make_pair(point(x, y), point(x, y + 1)));
      }

      n = get_node_ptr(x, y - 1);
      if (n && (n->pass == pass) && (n->depth == depth + 1)) {
        s.push_back(std::make_pair(point(x, y), point(x, y - 1)));
      }
    }
  }

  if (! s.size()) {
    if (pass == 1) {
      debug("error");
      ERR("No exits from %d to %d", depth, depth + 1);
    }
    return;
  }

  auto r = pcg_random_range(0, s.size());

  if (! r) {
    r = 1;
  }

  while (r--) {
    auto i = pcg_random_range(0, s.size());
    auto p = s[ i ];
    auto a = p.first;
    auto b = p.second;

    auto dx = b.x - a.x;
    auto dy = b.y - a.y;

    auto n = get_node_ptr(b.x, b.y);
    if (! n) {
      DIE("No new pos");
    }
    auto o = get_node_ptr(a.x, a.y);
    if (! o) {
      DIE("No old pos");
    }

    if (dx == 1) {
      o->set_has_door_right(true);
      n->set_has_door_left(true);
    }

    if (dx == -1) {
      o->set_has_door_left(true);
      n->set_has_door_right(true);
    }

    if (dy == 1) {
      o->set_has_door_down(true);
      n->set_has_door_up(true);
    }

    if (dy == -1) {
      o->set_has_door_up(true);
      n->set_has_door_down(true);
    }
  }
}

void LevelPh1::join_depth_secret(int depth, int pass)
{
  std::vector< std::pair< point, point > > s;

  for (auto x = 0; x < grid_width; x++) {
    for (auto y = 0; y < grid_height; y++) {
      auto o = get_node_ptr(x, y);
      if (o->depth != depth) {
        continue;
      }
      if (o->pass && (o->pass != pass)) {
        continue;
      }

      if (pass == 1) {
        auto n = get_node_ptr(x + 1, y);
        if (n && (n->pass == pass) && (n->depth > depth + 1)) {
          s.push_back(std::make_pair(point(x, y), point(x + 1, y)));
        }

        n = get_node_ptr(x - 1, y);
        if (n && (n->pass == pass) && (n->depth > depth + 1)) {
          s.push_back(std::make_pair(point(x, y), point(x - 1, y)));
        }

        n = get_node_ptr(x, y + 1);
        if (n && (n->pass == pass) && (n->depth > depth + 1)) {
          s.push_back(std::make_pair(point(x, y), point(x, y + 1)));
        }

        n = get_node_ptr(x, y - 1);
        if (n && (n->pass == pass) && (n->depth > depth + 1)) {
          s.push_back(std::make_pair(point(x, y), point(x, y - 1)));
        }
      } else {
        auto n = get_node_ptr(x + 1, y);
        if (n && (n->pass != pass) && (n->depth >= depth)) {
          s.push_back(std::make_pair(point(x, y), point(x + 1, y)));
        }

        n = get_node_ptr(x - 1, y);
        if (n && (n->pass != pass) && (n->depth >= depth)) {
          s.push_back(std::make_pair(point(x, y), point(x - 1, y)));
        }

        n = get_node_ptr(x, y + 1);
        if (n && (n->pass != pass) && (n->depth >= depth)) {
          s.push_back(std::make_pair(point(x, y), point(x, y + 1)));
        }

        n = get_node_ptr(x, y - 1);
        if (n && (n->pass != pass) && (n->depth >= depth)) {
          s.push_back(std::make_pair(point(x, y), point(x, y - 1)));
        }
      }
    }
  }

  if (! s.size()) {
    return;
  }

  auto r = pcg_random_range(0, s.size());
  if (! r) {
    r = 1;
  }

  if (pass == 2) {
    r = s.size() / 2;
  }

  while (r--) {
    auto i = pcg_random_range(0, s.size());
    auto p = s[ i ];
    auto a = p.first;
    auto b = p.second;

    auto dx = b.x - a.x;
    auto dy = b.y - a.y;

    auto n = get_node_ptr(b.x, b.y);
    if (! n) {
      DIE("No new pos");
    }
    auto o = get_node_ptr(a.x, a.y);
    if (! o) {
      DIE("No old pos");
    }

    if (dx == 1) {
      o->set_has_secret_exit_right(true);
      n->set_has_secret_exit_left(true);
    }

    if (dx == -1) {
      o->set_has_secret_exit_left(true);
      n->set_has_secret_exit_right(true);
    }

    if (dy == 1) {
      o->set_has_secret_exit_down(true);
      n->set_has_secret_exit_up(true);
    }

    if (dy == -1) {
      o->set_has_secret_exit_up(true);
      n->set_has_secret_exit_down(true);
    }
  }
}

bool LevelPh1::place_lock(int depth, int pass)
{
  std::vector< point > s;

  for (auto x = 0; x < grid_width; x++) {
    for (auto y = 0; y < grid_height; y++) {
      auto o = get_node_ptr(x, y);
      if (o->pass != pass) {
        continue;
      }
      if (o->depth != depth) {
        continue;
      }
      if (o->is_exit) {
        continue;
      }
      if (o->is_entrance) {
        continue;
      }
      if (! o->on_critical_path) {
        continue;
      }

      auto n = get_node_ptr(x + 1, y);
      if (n && (n->on_critical_path) && (n->pass == pass) && (n->depth == depth - 1) && o->has_door_right) {
        s.push_back(point(x, y));
      }
      n = get_node_ptr(x - 1, y);
      if (n && (n->on_critical_path) && (n->pass == pass) && (n->depth == depth - 1) && o->has_door_left) {
        s.push_back(point(x, y));
      }
      n = get_node_ptr(x, y - 1);
      if (n && (n->on_critical_path) && (n->pass == pass) && (n->depth == depth - 1) && o->has_door_up) {
        s.push_back(point(x, y));
      }
      n = get_node_ptr(x, y + 1);
      if (n && (n->on_critical_path) && (n->pass == pass) && (n->depth == depth - 1) && o->has_door_down) {
        s.push_back(point(x, y));
      }
    }
  }

  if (! s.size()) {
    debug("no lock placed for depth");
    if (debug_enabled) {
      LOG("No lock placed for depth %d", depth);
    }
    return false;
  }

  auto i     = pcg_random_range(0, s.size());
  auto p     = s[ i ];
  auto n     = get_node_ptr(p.x, p.y);
  n->is_lock = true;
  return true;
}

void LevelPh1::hide_other_locks(int depth, int pass)
{
  std::vector< point > s;

  for (auto x = 0; x < grid_width; x++) {
    for (auto y = 0; y < grid_height; y++) {
      auto o = get_node_ptr(x, y);
      if (o->pass != pass) {
        continue;
      }
      if (o->depth != depth) {
        continue;
      }
      if (o->is_lock) {
        continue;
      }

      auto n = get_node_ptr(x + 1, y);
      if (n && (n->pass == pass) && (n->depth == depth - 1) && o->has_door_right) {
        o->set_has_door_right(false);
        o->set_has_secret_exit_right(true);
        n->set_has_door_left(false);
        n->set_has_secret_exit_left(true);
      }
      n = get_node_ptr(x - 1, y);
      if (n && (n->pass == pass) && (n->depth == depth - 1) && o->has_door_left) {
        o->set_has_door_left(false);
        o->set_has_secret_exit_left(true);
        n->set_has_door_right(false);
        n->set_has_secret_exit_right(true);
      }
      n = get_node_ptr(x, y - 1);
      if (n && (n->pass == pass) && (n->depth == depth - 1) && o->has_door_up) {
        o->set_has_door_up(false);
        o->set_has_secret_exit_up(true);
        n->set_has_door_down(false);
        n->set_has_secret_exit_down(true);
      }
      n = get_node_ptr(x, y + 1);
      if (n && (n->pass == pass) && (n->depth == depth - 1) && o->has_door_down) {
        o->set_has_door_down(false);
        o->set_has_secret_exit_down(true);
        n->set_has_door_up(false);
        n->set_has_secret_exit_up(true);
      }
    }
  }
}

bool LevelPh1::place_key(int depth, int pass)
{
  std::vector< point > s;

  for (auto x = 0; x < grid_width; x++) {
    for (auto y = 0; y < grid_height; y++) {
      auto o = get_node_ptr(x, y);
      if (o->pass != pass) {
        continue;
      }
      if (o->depth != depth) {
        continue;
      }
      if (o->is_lock) {
        continue;
      }
      if (o->is_entrance) {
        continue;
      }
      if (o->is_exit) {
        continue;
      }
      if (! o->on_critical_path) {
        continue;
      }

      s.push_back(point(x, y));
    }
  }

  if (! s.size()) {
    debug("no key placed");
    if (debug_enabled) {
      LOG("No key placed for depth %d", depth);
    }
    return false;
  }

  auto i    = pcg_random_range(0, s.size());
  auto p    = s[ i ];
  auto n    = get_node_ptr(p.x, p.y);
  n->is_key = true;
  return true;
}

bool LevelPh1::place_entrance(void)
{
  std::vector< point > s;

  for (auto x = 0; x < grid_width; x++) {
    auto y = 0;
    auto o = get_node_ptr(x, y);
    if (o->pass != 1) {
      continue;
    }
    if (o->depth != 1) {
      continue;
    }
    if (o->is_key) {
      continue;
    }
    if (o->is_lock) {
      continue;
    }
    if (o->is_entrance) {
      continue;
    }
    if (o->is_exit) {
      continue;
    }

    s.push_back(point(x, y));
  }

  if (! s.size()) {
    debug("entrance not found");
    return false;
  }

  auto i         = pcg_random_range(0, s.size());
  auto p         = s[ i ];
  auto n         = get_node_ptr(p.x, p.y);
  n->is_entrance = true;

  return true;
}

bool LevelPh1::place_exit(void)
{
  std::vector< point > s;

  for (auto x = 0; x < grid_width; x++) {
    auto y = grid_height - 1;
    auto o = get_node_ptr(x, y);
    if (o->pass != 1) {
      continue;
    }

    if (o->is_key) {
      continue;
    }
    if (o->is_lock) {
      continue;
    }
    if (o->is_entrance) {
      continue;
    }
    if (o->is_exit) {
      continue;
    }
    if (o->depth == max_depth) {
      s.push_back(point(x, y));
    }
  }

  if (! s.size()) {
    debug("exit is no deep enough");
    return false;
  }

  auto i     = pcg_random_range(0, s.size());
  auto p     = s[ i ];
  auto n     = get_node_ptr(p.x, p.y);
  n->is_exit = true;

  return true;
}

void LevelPh1::remove_stubs(void)
{
  std::vector< point > s;

  for (auto y = 0; y < grid_height; y++) {
    for (auto x = 0; x < grid_width; x++) {
      auto node = get_node_ptr(x, y);

      if (node->has_door_down) {
        auto o = get_node_ptr(x, y + 1);
        if (! o->has_door_up) {
          node->set_has_door_down(false);
        }
      }
      if (node->has_door_up) {
        auto o = get_node_ptr(x, y - 1);
        if (! o->has_door_down) {
          node->set_has_door_up(false);
        }
      }
      if (node->has_door_right) {
        auto o = get_node_ptr(x + 1, y);
        if (! o->has_door_left) {
          node->set_has_door_right(false);
        }
      }
      if (node->has_door_left) {
        auto o = get_node_ptr(x - 1, y);
        if (! o->has_door_right) {
          node->set_has_door_left(false);
        }
      }
      if (node->has_secret_exit_down) {
        auto o = get_node_ptr(x, y + 1);
        if (! o->has_secret_exit_up) {
          node->set_has_secret_exit_down(false);
        }
      }
      if (node->has_secret_exit_up) {
        auto o = get_node_ptr(x, y - 1);
        if (! o->has_secret_exit_down) {
          node->set_has_secret_exit_up(false);
        }
      }
      if (node->has_secret_exit_right) {
        auto o = get_node_ptr(x + 1, y);
        if (! o->has_secret_exit_left) {
          node->set_has_secret_exit_right(false);
        }
      }
      if (node->has_secret_exit_left) {
        auto o = get_node_ptr(x - 1, y);
        if (! o->has_secret_exit_right) {
          node->set_has_secret_exit_left(false);
        }
      }
    }
  }
}

void LevelPh1::dmap_print_walls(Dmap *d)
{
  for (auto y = 0; y < grid_height * 2 + 1; y++) {
    for (auto x = 0; x < grid_width * 2 + 1; x++) {
      uint16_t e = get(d->val, x, y);
      if (e == DMAP_IS_WALL) {
        printf("#");
        continue;
      }
      if (e == DMAP_IS_PASSABLE) {
        printf(".");
        continue;
      }

      if (e > 0) {
        printf("%d", e % 10);
      } else {
        printf(" ");
      }
    }
    printf("\n");
  }
  printf("\n");
}

bool LevelPh1::create_path_to_exit(int pass)
{
  //
  // Choose start and end of the dmap
  //
  point start;
  point end;

  for (auto y = 0; y < grid_height; y++) {
    for (auto x = 0; x < grid_width; x++) {
      auto n = get_node_ptr(x, y);
      if (! n) {
        continue;
      }
      if (n->is_entrance) {
        start = point(x, y);
      }
      if (n->is_exit) {
        end = point(x, y);
      }
    }
  }

  Dmap d {};

  int minx, miny, maxx, maxy;

  minx = 0;
  miny = 0;
  maxx = grid_width * 2 + 1;
  maxy = grid_height * 2 + 1;

  //
  // Set up obstacles for the exit search
  //
  for (auto y = miny; y < maxy; y++) {
    for (auto x = minx; x < maxx; x++) {
      set(d.val, x, y, DMAP_IS_WALL);
    }
  }

  if (pass == 1) {
    for (auto y = 0; y < grid_height; y++) {
      for (auto x = 0; x < grid_width; x++) {
        auto n = get_node_ptr(x, y);
        auto X = (x * 2) + 1;
        auto Y = (y * 2) + 1;
        if (n && node_is_a_room(n)) {
          if (n->has_door_up || n->has_secret_exit_up) {
            set(d.val, X, Y - 1, DMAP_IS_PASSABLE);
          }
          if (n->has_door_down || n->has_secret_exit_down) {
            set(d.val, X, Y + 1, DMAP_IS_PASSABLE);
          }
          if (n->has_door_right || n->has_secret_exit_right) {
            set(d.val, X + 1, Y, DMAP_IS_PASSABLE);
          }
          if (n->has_door_left || n->has_secret_exit_left) {
            set(d.val, X - 1, Y, DMAP_IS_PASSABLE);
          }
          set(d.val, X, Y, DMAP_IS_PASSABLE);
        } else {
          set(d.val, X, Y, DMAP_IS_WALL);
        }
      }
    }
  } else {
    for (auto y = 0; y < grid_height; y++) {
      for (auto x = 0; x < grid_width; x++) {
        auto n = get_node_ptr(x, y);
        auto X = (x * 2) + 1;
        auto Y = (y * 2) + 1;
        if (n && node_is_a_room(n)) {
          if (n->has_door_up) {
            set(d.val, X, Y - 1, DMAP_IS_PASSABLE);
          }
          if (n->has_door_down) {
            set(d.val, X, Y + 1, DMAP_IS_PASSABLE);
          }
          if (n->has_door_right) {
            set(d.val, X + 1, Y, DMAP_IS_PASSABLE);
          }
          if (n->has_door_left) {
            set(d.val, X - 1, Y, DMAP_IS_PASSABLE);
          }
          set(d.val, X, Y, DMAP_IS_PASSABLE);
        } else {
          set(d.val, X, Y, DMAP_IS_WALL);
        }
      }
    }
  }

  set(d.val, end.x * 2 + 1, end.y * 2 + 1, DMAP_IS_GOAL);
  set(d.val, start.x * 2 + 1, start.y * 2 + 1, DMAP_IS_PASSABLE);

  point dmap_start(minx, miny);
  point dmap_end(maxx, maxy);
  dmap_process_no_diagonals(&d, dmap_start, dmap_end, false);
  // dmap_print_walls(&d);

  //
  // Ensure the exit is not too close
  //
  if (pass == 2) {
    auto s = point(start.x * 2 + 1, start.y * 2 + 1);
    auto p = dmap_solve_manhattan(&d, s);
    if (p.size() < (unsigned) (grid_width * 2)) {
      return false;
    }
  }

  for (auto y = 0; y < grid_height; y++) {
    for (auto x = 0; x < grid_width; x++) {
      auto n = get_node_ptr(x, y);
      auto X = x * 2 + 1;
      auto Y = y * 2 + 1;

      if (n && node_is_a_room(n)) {
        if (get(d.val, X + 1, Y) < d.val[ X ][ Y ]) {
          auto o = get_node_ptr(x + 1, y);
          if (o && (o->pass == n->pass) && node_is_a_room(o)) {
            n->dir_up    = false;
            n->dir_down  = false;
            n->dir_left  = false;
            n->dir_right = false;
            n->dir_right = true;
          }
        }
        if (get(d.val, X - 1, Y) < d.val[ X ][ Y ]) {
          auto o = get_node_ptr(x - 1, y);
          if (o && (o->pass == n->pass) && node_is_a_room(o)) {
            n->dir_up    = false;
            n->dir_down  = false;
            n->dir_left  = false;
            n->dir_right = false;
            n->dir_left  = true;
          }
        }
        if (get(d.val, X, Y + 1) < d.val[ X ][ Y ]) {
          auto o = get_node_ptr(x, y + 1);
          if (o && (o->pass == n->pass) && node_is_a_room(o)) {
            n->dir_up    = false;
            n->dir_down  = false;
            n->dir_left  = false;
            n->dir_right = false;
            n->dir_down  = true;
          }
        }
        if (get(d.val, X, Y - 1) < d.val[ X ][ Y ]) {
          auto o = get_node_ptr(x, y - 1);
          if (o && (o->pass == n->pass) && node_is_a_room(o)) {
            n->dir_up    = false;
            n->dir_down  = false;
            n->dir_left  = false;
            n->dir_right = false;
            n->dir_up    = true;
          }
        }
      }
    }
  }

  return true;
}

void LevelPh1::create_path_lock_to_key(int depth)
{
  //
  // Choose start and end of the dmap
  //
  point start;
  point end;

  for (auto y = 0; y < grid_height; y++) {
    for (auto x = 0; x < grid_width; x++) {
      auto n = get_node_ptr(x, y);
      if (! n) {
        continue;
      }
      if (n->depth == depth) {
        if (n->is_key) {
          end = point(x, y);
        }
        continue;
      }
      if (n->depth == depth + 1) {
        if (n->is_lock) {
          start = point(x, y);
        }
      }
    }
  }

  Dmap d {};

  int minx, miny, maxx, maxy;

  minx = 0;
  miny = 0;
  maxx = grid_width * 2 + 1;
  maxy = grid_height * 2 + 1;

  //
  // Set up obstacles for the exit search
  //
  for (auto y = miny; y < maxy; y++) {
    for (auto x = minx; x < maxx; x++) {
      set(d.val, x, y, DMAP_IS_WALL);
    }
  }

  for (auto y = 0; y < grid_height; y++) {
    for (auto x = 0; x < grid_width; x++) {
      auto n = get_node_ptr(x, y);
      auto X = (x * 2) + 1;
      auto Y = (y * 2) + 1;
      if (n && (n->pass == 1) && (n->depth == depth) && node_is_a_room(n)) {
        if (n->has_door_up) {
          set(d.val, X, Y - 1, DMAP_IS_PASSABLE);
        }
        if (n->has_door_down) {
          set(d.val, X, Y + 1, DMAP_IS_PASSABLE);
        }
        if (n->has_door_right) {
          set(d.val, X + 1, Y, DMAP_IS_PASSABLE);
        }
        if (n->has_door_left) {
          set(d.val, X - 1, Y, DMAP_IS_PASSABLE);
        }
        set(d.val, X, Y, DMAP_IS_PASSABLE);
      } else {
        set(d.val, X, Y, DMAP_IS_WALL);
      }
    }
  }

  set(d.val, end.x * 2 + 1, end.y * 2 + 1, DMAP_IS_GOAL);
  set(d.val, start.x * 2 + 1, start.y * 2 + 1, DMAP_IS_PASSABLE);

  point dmap_start(minx, miny);
  point dmap_end(maxx, maxy);
  dmap_process_no_diagonals(&d, dmap_start, dmap_end, false);
  // dmap_print_walls(&d);

  for (auto y = 0; y < grid_height; y++) {
    for (auto x = 0; x < grid_width; x++) {
      auto n = get_node_ptr(x, y);
      auto X = x * 2 + 1;
      auto Y = y * 2 + 1;

      if (get(d.val, X, Y) == DMAP_IS_WALL) {
        continue;
      }
      if (n && node_is_a_room(n)) {
        if (get(d.val, X + 1, Y) < d.val[ X ][ Y ]) {
          auto o = get_node_ptr(x + 1, y);
          if (o && node_is_a_room(o)) {
            n->dir_right = true;
            o->dir_left  = true;
          }
        }
        if (get(d.val, X - 1, Y) < d.val[ X ][ Y ]) {
          auto o = get_node_ptr(x - 1, y);
          if (o && node_is_a_room(o)) {
            n->dir_left  = true;
            o->dir_right = true;
          }
        }
        if (get(d.val, X, Y + 1) < d.val[ X ][ Y ]) {
          auto o = get_node_ptr(x, y + 1);
          if (o && node_is_a_room(o)) {
            n->dir_down = true;
            o->dir_up   = true;
          }
        }
        if (get(d.val, X, Y - 1) < d.val[ X ][ Y ]) {
          auto o = get_node_ptr(x, y - 1);
          if (o && node_is_a_room(o)) {
            n->dir_up   = true;
            o->dir_down = true;
          }
        }
      }
    }
  }
}

void LevelPh1::make_paths_off_critical_path_reachable(void)
{
  //
  // Choose start and end of the dmap
  //
  point start;
  point end;

  for (auto y = 0; y < grid_height; y++) {
    for (auto x = 0; x < grid_width; x++) {
      auto n = get_node_ptr(x, y);
      if (! n) {
        continue;
      }
      if (n->is_entrance) {
        start = point(x, y);
      }
      if (n->is_exit) {
        end = point(x, y);
      }
    }
  }

  int minx, miny, maxx, maxy;

  minx = 0;
  miny = 0;
  maxx = grid_width * 2 + 1;
  maxy = grid_height * 2 + 1;

  Dmap d {};

  //
  // Set up obstacles for the exit search
  //
  for (auto y = miny; y < maxy; y++) {
    for (auto x = minx; x < maxx; x++) {
      set(d.val, x, y, DMAP_IS_WALL);
    }
  }

  for (auto y = 0; y < grid_height; y++) {
    for (auto x = 0; x < grid_width; x++) {
      auto n = get_node_ptr(x, y);
      auto X = (x * 2) + 1;
      auto Y = (y * 2) + 1;

      if (node_is_a_room(n)) {
        if (n->has_door_up) {
          set(d.val, X, Y - 1, DMAP_IS_PASSABLE);
        }
        if (n->has_door_down) {
          set(d.val, X, Y + 1, DMAP_IS_PASSABLE);
        }
        if (n->has_door_right) {
          set(d.val, X + 1, Y, DMAP_IS_PASSABLE);
        }
        if (n->has_door_left) {
          set(d.val, X - 1, Y, DMAP_IS_PASSABLE);
        }
        set(d.val, X, Y, DMAP_IS_PASSABLE);
      }
    }
  }

  point dmap_start(minx, miny);
  point dmap_end(maxx, maxy);

  start.x = (start.x * 2) + 1;
  start.y = (start.y * 2) + 1;
  end.x   = (end.x * 2) + 1;
  end.y   = (end.y * 2) + 1;

  set(d.val, end.x, end.y, DMAP_IS_GOAL);
  set(d.val, start.x, start.y, DMAP_IS_PASSABLE);

  dmap_process_no_diagonals(&d, dmap_start, dmap_end, false);
  // dmap_print_walls(&d);

  std::array< std::array< bool, LEVEL_PH1_HEIGHT >, LEVEL_PH1_WIDTH > on_critical_path = {};

  auto p = dmap_solve_manhattan(&d, start);
  for (auto c : p) {
    auto X = (c.x - 1) / 2;
    auto Y = (c.y - 1) / 2;

    if (X >= grid_width) {
      ERR("Bug");
    }
    if (Y >= grid_height) {
      ERR("Bug");
    }
    if (X < 0) {
      ERR("Bug");
    }
    if (Y < 0) {
      ERR("Bug");
    }

    set(on_critical_path, X, Y, true);
    auto n = get_node_ptr(X, Y);

    n->on_critical_path = true;
  }

  for (auto y = 0; y < grid_height; y++) {
    for (auto x = 0; x < grid_width; x++) {
      auto n = get_node_ptr(x, y);

      if (on_critical_path[ x ][ y ]) {
        continue;
      }

      if (! node_is_a_room(n)) {
        continue;
      }

      if (n->has_door_up) {
        auto o = get_node_ptr(x, y - 1);
        if (o && (o->pass == n->pass)) {
          n->dir_up   = true;
          o->dir_down = true;
        }
      }
      if (n->has_door_down) {
        auto o = get_node_ptr(x, y + 1);
        if (o && (o->pass == n->pass)) {
          n->dir_down = true;
          o->dir_up   = true;
        }
      }
      if (n->has_door_right) {
        auto o = get_node_ptr(x + 1, y);
        if (o && (o->pass == n->pass)) {
          n->dir_right = true;
          o->dir_left  = true;
        }
      }
      if (n->has_door_left) {
        auto o = get_node_ptr(x - 1, y);
        if (o && (o->pass == n->pass)) {
          n->dir_left  = true;
          o->dir_right = true;
        }
      }
    }
  }
}

void LevelPh1::set_max_depth(void)
{
  std::vector< point > s;
  auto                 max_depth_  = 0;
  auto                 max_vdepth_ = 0;

  for (auto x = 0; x < grid_width; x++) {
    for (auto y = 0; y < grid_height; y++) {
      auto o = get_node_ptr(x, y);
      if (o->pass != 1) {
        o->is_secret = true;
        continue;
      }
      o->is_secret = false;

      if (o->depth > max_depth_) {
        max_depth_ = o->depth;
      }
      if (y > max_vdepth_) {
        max_vdepth_ = y;
      }
    }
  }

  max_depth  = max_depth_;
  max_vdepth = max_vdepth_;
}

void LevelPh1::remove_redundant_directions(void)
{
  for (auto x = 0; x < grid_width; x++) {
    for (auto y = 0; y < grid_height; y++) {
      auto node = get_node_ptr(x, y);
      if (! node_is_a_room(node)) {
        continue;
      }

      auto e = 0;
      auto d = 0;

      if (node->has_door_down) {
        e <<= 1;
        e |= 1;
      }
      if (node->has_door_up) {
        e <<= 1;
        e |= 1;
      }
      if (node->has_door_left) {
        e <<= 1;
        e |= 1;
      }
      if (node->has_door_right) {
        e <<= 1;
        e |= 1;
      }

      if (node->dir_down) {
        d <<= 1;
        d |= 1;
      }
      if (node->dir_up) {
        d <<= 1;
        d |= 1;
      }
      if (node->dir_left) {
        d <<= 1;
        d |= 1;
      }
      if (node->dir_right) {
        d <<= 1;
        d |= 1;
      }

      if (d == e) {
        node->dir_down  = false;
        node->dir_up    = false;
        node->dir_left  = false;
        node->dir_right = false;
      }
    }
  }
}

bool LevelPh1::remove_dead_end_paths(void)
{
  bool got_one = false;

  for (auto x = 0; x < grid_width; x++) {
    for (auto y = 0; y < grid_height; y++) {
      auto node = get_node_ptr(x, y);
      if (! node_is_a_room(node)) {
        continue;
      }

      if (node->on_critical_path) {
        continue;
      }

      if (node->is_entrance) {
        continue;
      }

      if (node->is_exit) {
        continue;
      }

      if (node->is_lock) {
        continue;
      }

      if (node->is_key) {
        continue;
      }

      if (node->is_secret) {
        continue;
      }

      auto exits = (node->has_door_down ? 1 : 0) + (node->has_door_up ? 1 : 0) + (node->has_door_left ? 1 : 0)
                 + (node->has_door_right ? 1 : 0);

      if (exits > 1) {
        continue;
      }

      if (node->has_door_down) {
        auto o = get_node_ptr(x, y + 1);
        node->set_has_door_down(false);
        o->set_has_door_up(false);
        node->depth     = 0;
        got_one         = true;
        node->dir_up    = false;
        node->dir_down  = false;
        node->dir_left  = false;
        node->dir_right = false;
        node->set_has_secret_exit_up(false);
        node->set_has_secret_exit_down(false);
        node->set_has_secret_exit_left(false);
        node->set_has_secret_exit_right(false);
      }

      if (node->has_door_up) {
        auto o = get_node_ptr(x, y - 1);
        node->set_has_door_up(false);
        o->set_has_door_down(false);
        node->depth     = 0;
        got_one         = true;
        node->dir_up    = false;
        node->dir_down  = false;
        node->dir_left  = false;
        node->dir_right = false;
        node->set_has_secret_exit_up(false);
        node->set_has_secret_exit_down(false);
        node->set_has_secret_exit_left(false);
        node->set_has_secret_exit_right(false);
      }

      if (node->has_door_left) {
        auto o = get_node_ptr(x - 1, y);
        node->set_has_door_left(false);
        o->set_has_door_right(false);
        node->depth     = 0;
        got_one         = true;
        node->dir_up    = false;
        node->dir_down  = false;
        node->dir_left  = false;
        node->dir_right = false;
        node->set_has_secret_exit_up(false);
        node->set_has_secret_exit_down(false);
        node->set_has_secret_exit_left(false);
        node->set_has_secret_exit_right(false);
      }

      if (node->has_door_right) {
        auto o = get_node_ptr(x + 1, y);
        node->set_has_door_right(false);
        o->set_has_door_left(false);
        node->depth     = 0;
        got_one         = true;
        node->dir_up    = false;
        node->dir_down  = false;
        node->dir_left  = false;
        node->dir_right = false;
        node->set_has_secret_exit_up(false);
        node->set_has_secret_exit_down(false);
        node->set_has_secret_exit_left(false);
        node->set_has_secret_exit_right(false);
      }
    }
  }

  return got_one;
}

LevelPh1 level_ph1(void)
{
  TRACE_NO_INDENT();

  LevelPh1 ph1(LEVEL_PH1_WIDTH, LEVEL_PH1_HEIGHT);
  ph1.construct();
  return ph1;
}
