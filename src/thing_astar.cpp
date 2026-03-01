//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_globals.hpp"
#include "my_level.hpp"
#include "my_main.hpp"
#include "my_sprintf.hpp"
#include "my_thing.hpp"
#include "my_thing_callbacks.hpp"
#include "my_thing_inlines.hpp"
#include "my_tp.hpp"

#include <algorithm> // do not remove
#include <array>     // do not remove
#include <limits>    // do not remove
#include <map>

#ifdef ENABLE_DEBUG_AI_ASTAR
static std::array< std::array< char, MAP_HEIGHT >, MAP_WIDTH > astar_debug;
#endif

using Cost = float;

static int16_t g_tiebreak;

class Nodecost
{
public:
  Nodecost() = default;
  explicit Nodecost(Cost c) : cost(c), tiebreak(g_tiebreak++) {}

  auto operator<(const Nodecost &rhs) const -> bool
  {
    if (cost < rhs.cost) {
      return true;
    }
    if (cost > rhs.cost) {
      return false;
    }

    return tiebreak < rhs.tiebreak;
  }

  Cost    cost {};
  int16_t tiebreak {};
};

class Node
{
public:
  Node() = default;

  class Node *came_from {};
  Nodecost    cost;
  spoint      at {};
};

//
// The nodemap needs to be sorted by distance so std::map must be used
//
using Nodemap = std::map< Nodecost, Node * >;

class Astar
{
public:
  Astar() = default;

  Gamep   g = {};
  Levelsp v = {};
  Levelp  l = {};
  Thingp  t = {};

  //
  // These are the nodes still to evaluate
  //
  Nodemap open_nodes;

  //
  // These are the nodes we have evaluated
  //
  Nodemap closed_nodes;

  //
  // Start and desired end of the search
  //
  spoint src {};
  spoint dst {};

  //
  // Indicates which nodes in the grid we've searched and added to the open list
  //
  std::array< std::array< Node *, MAP_HEIGHT >, MAP_WIDTH > open = {};

  //
  // Indicates which nodes in the grid we've searched and added to the closed list
  //
  std::array< std::array< Node *, MAP_HEIGHT >, MAP_WIDTH > closed = {};

  //
  // A node per grid element. Avoids needing to allocate memory
  //
  std::array< std::array< Node, MAP_HEIGHT >, MAP_WIDTH > nodes = {};

  //
  // Cache of where this thing can move to
  //
  std::array< std::array< bool, MAP_HEIGHT >, MAP_WIDTH > can_move_to_tile     = {};
  std::array< std::array< bool, MAP_HEIGHT >, MAP_WIDTH > can_move_to_tile_set = {};

  auto               can_move_to(const spoint &to) -> bool;
  [[nodiscard]] auto heuristic(spoint at) const -> Cost;
  auto               node_init(spoint next_hop, Nodecost cost) -> Node *;
  void               add_to_closed(Node *n);
  void               add_to_open(Node *n);
  void               dump();
  void               eval_neighbor(Node *current, const spoint &delta);
  static void        init();
  void               remove_from_open(Node *n);

  auto        solve(bool allow_diagonal) -> std::vector< spoint >;
  static auto create_path(const Node *came_from) -> std::vector< spoint >;
};

void Astar::add_to_open(Node *n)
{
  auto  p = n->at;
  auto *o = &open[ p.x ][ p.y ];
  if (*o != nullptr) {
    THING_ERR(t, "Already in open");
    return;
  }
  *o = n;

  auto result = open_nodes.insert(std::make_pair(n->cost, n));
  if (! result.second) {
    THING_ERR(t, "open insert fail");
    return;
  }
}

void Astar::add_to_closed(Node *n)
{
  auto  p = n->at;
  auto *o = &closed[ p.x ][ p.y ];
  if (*o != nullptr) {
    THING_ERR(t, "Already in closed");
    return;
  }
  *o = n;

  auto result = closed_nodes.insert(std::make_pair(n->cost, n));
  if (! result.second) {
    THING_ERR(t, "closed insert fail");
    return;
  }
}

void Astar::remove_from_open(Node *n)
{
  auto  p = n->at;
  auto *o = &open[ p.x ][ p.y ];
  if (*o == nullptr) {
    THING_ERR(t, "Not in open");
    return;
  }
  *o = nullptr;

  open_nodes.erase(n->cost);
}

auto Astar::heuristic(const spoint at) const -> Cost
{
  //
  // This can create wiggles in the path as we're always looking at the distance
  // to the end point, and sometimes a diagonal move is closer.
  //
  // Euclidian
  return distance(dst, at);
  //
  // Chebyshev for octagonal movement
  // return std::max(abs(dst.x - at.x), abs(dst.y - at.y));
}

auto Astar::node_init(const spoint next_hop, Nodecost cost) -> Node *
{
  auto *n = &nodes[ next_hop.x ][ next_hop.y ];

  n->at   = next_hop;
  n->cost = cost;

  return n;
}

//
// Evaluate a neighbor for adding to the open set
//
void Astar::eval_neighbor(Node *current, const spoint &delta)
{
  const auto next_hop = current->at + delta;

  //
  // If in the closed set already, ignore.
  //
  if (closed[ next_hop.x ][ next_hop.y ] != nullptr) {
    return;
  }

  if (! can_move_to(next_hop)) {
    return;
  }

  Cost const cost = current->cost.cost + heuristic(next_hop);

  Node *neighbor = open[ next_hop.x ][ next_hop.y ];
  if (neighbor == nullptr) {
    auto ncost          = Nodecost(cost);
    neighbor            = node_init(next_hop, ncost);
    neighbor->came_from = current;
    add_to_open(neighbor);
    return;
  }

  if (cost < neighbor->cost.cost) {
    auto ncost = Nodecost(cost);
    remove_from_open(neighbor);
    neighbor->came_from = current;
    neighbor->cost      = ncost;
    add_to_open(neighbor);
  }
}

auto Astar::create_path(const Node *came_from) -> std::vector< spoint >
{
  static const std::vector< spoint > empty;

  std::vector< spoint > out;

  while (came_from != nullptr) {
    if (came_from->came_from != nullptr) {
      out.push_back(came_from->at);
    }
    came_from = came_from->came_from;
  }

  std::ranges::reverse(out);
  return out;
}

void Astar::init()
{
  g_tiebreak = 0;

#ifdef ENABLE_DEBUG_AI_ASTAR
  astar_debug = {};
#endif
}

auto Astar::can_move_to(const spoint &to) -> bool
{
  if (to == dst) {
    return true;
  }

  if (! can_move_to_tile_set[ to.x ][ to.y ]) {
    can_move_to_tile_set[ to.x ][ to.y ]    = true;
    return can_move_to_tile[ to.x ][ to.y ] = thing_can_move_to_check_if_is_possible(g, v, l, t, to);
  }

  return can_move_to_tile[ to.x ][ to.y ];
}

auto Astar::solve(bool allow_diagonal) -> std::vector< spoint >
{
  auto  ncost    = Nodecost(heuristic(src));
  auto *neighbor = node_init(src, ncost);

  add_to_open(neighbor);

  init();

  while (! open_nodes.empty()) {
    auto  c       = open_nodes.begin();
    Node *current = c->second;

    //
    // Reached the target?
    //
    auto at = current->at;
    if (at == dst) {
      return create_path(current);
    }

#ifdef ENABLE_DEBUG_AI_ASTAR
    astar_debug[ at.x ][ at.y ] = '?';
#endif

    remove_from_open(current);
    add_to_closed(current);

    //
    // No moving into the border
    //
    if ((at.x == 0) || (at.x == MAP_WIDTH - 1) || (at.y == 0) || (at.y == MAP_HEIGHT - 1)) {
      continue;
    }

    eval_neighbor(current, spoint(-1, 0));
    eval_neighbor(current, spoint(1, 0));
    eval_neighbor(current, spoint(0, -1));
    eval_neighbor(current, spoint(0, 1));

    if (allow_diagonal) {
      if (thing_is_able_to_move_through_walls(t)) {
        //
        // Can move through walls in any direction
        //
        eval_neighbor(current, spoint(-1, -1));
        eval_neighbor(current, spoint(-1, 1));
        eval_neighbor(current, spoint(1, -1));
        eval_neighbor(current, spoint(1, 1));
      } else {
        //
        // Don't allow shortcuts through diagonal walls
        //
        if (! can_move_to(spoint(at.x - 1, at.y)) || ! can_move_to(spoint(at.x, at.y - 1))) {
          //
          // Block these paths
          //

          // b#.
          // #a.
          // ...

          // b..
          // #a.
          // ...

          // b#.
          // .a.
          // ...
        } else {
          eval_neighbor(current, spoint(-1, -1));
        }

        if (! can_move_to(spoint(at.x - 1, at.y)) || ! can_move_to(spoint(at.x, at.y + 1))) {
          //
          // Block these paths
          //

          // ...
          // #a.
          // .#.

          // ...
          // #a.
          // ...

          // ...
          // .a.
          // .#.
        } else {
          eval_neighbor(current, spoint(-1, 1));
        }

        if (! can_move_to(spoint(at.x + 1, at.y)) || ! can_move_to(spoint(at.x, at.y - 1))) {
          //
          // Block these paths
          //

          // .#.
          // .a#
          // ...

          // ...
          // .a#
          // ...

          // .#.
          // .a.
          // ...
        } else {
          eval_neighbor(current, spoint(1, -1));
        }

        if (! can_move_to(spoint(at.x + 1, at.y)) || ! can_move_to(spoint(at.x, at.y + 1))) {
          //
          // Block these paths
          //

          // ...
          // .a#
          // .#.

          // ...
          // .a#
          // ...

          // ...
          // .a.
          // .#.
        } else {
          eval_neighbor(current, spoint(1, 1));
        }
      }
    }
  }

  static const std::vector< spoint > empty;
  return empty;
}

void Astar::dump()
{
  THING_LOG(t, "ASTAR:");
  TRACE_INDENT();

  for (auto y = 0; y < MAP_HEIGHT; y++) {
    std::string s;
    for (auto x = 0; x < MAP_WIDTH; x++) {
      std::string buf;

      if (can_move_to(spoint(x, y))) {
        buf = ".";
      } else {
        buf = "#";
      }

#ifdef ENABLE_DEBUG_AI_ASTAR
      if (astar_debug[ x ][ y ]) {
        buf = astar_debug[ x ][ y ];
      }
#endif

      if (spoint(x, y) == src) {
        buf = "@";
      }
      if (spoint(x, y) == dst) {
        buf = "*";
      }

      s += buf;
    }
    THING_LOG(t, "ASTAR:%s", s.c_str());
  }
}

auto astar_solve(Gamep g, Levelsp v, Levelp l, Thingp t, spoint src, spoint dst) -> std::vector< spoint >
{
  TRACE();

  Astar a;
  a.g   = g;
  a.v   = v;
  a.l   = l;
  a.t   = t;
  a.src = src;
  a.dst = dst;

  auto allow_diagonal = thing_is_able_to_move_diagonally(t);
  auto path           = a.solve(allow_diagonal);

#ifdef ENABLE_DEBUG_AI_ASTAR
  for (const auto &p : path) {
    astar_debug[ p.x ][ p.y ] = '^';
  }

  a.dump();

  //
  // Tests don't have floors everywhere
  //
  if (level_is_floor(g, v, l, dst)) {
    if (! path.size()) {
      CROAK("no path");
    }
  }
#endif

  return path;
}
