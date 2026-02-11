//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_level.hpp"
#include "my_main.hpp"
#include "my_sprintf.hpp"
#include "my_thing.hpp"
#include "my_thing_callbacks.hpp"
#include "my_thing_inlines.hpp"
#include "my_tp.hpp"

#include <limits> // do not remove
#include <map>

#define ENABLE_DEBUG_AI_ASTAR

static std::array< std::array< char, MAP_HEIGHT >, MAP_WIDTH > astar_debug;

typedef float Cost;

class Nodecost
{
public:
  Nodecost(void) = default;
  Nodecost(Cost c, int t) : cost(c), tiebreak(t) {}

  bool operator<(const Nodecost &rhs) const
  {
    if (cost < rhs.cost) {
      return true;
    }
    if (cost > rhs.cost) {
      return false;
    }

    return tiebreak < rhs.tiebreak;
  }

  Cost cost {};
  int  tiebreak {};
};

class Node
{
public:
  Node(void) = default;

  class Node *came_from {};
  Nodecost    cost {};
  spoint      at;
};

//
// The nodemap needs to be sorted by distance, and we can have multiple
// identical costs, so std::multimap must be used
//
//
typedef std::multimap< Nodecost, Node * > Nodemap;

class Astar
{
public:
  Astar() {}

  Gamep   g = {};
  Levelsp v = {};
  Levelp  l = {};
  Thingp  t = {};
  int     tiebreak;

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
  spoint src;
  spoint dst;

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
  std::array< std::array< Node, MAP_HEIGHT >, MAP_WIDTH > nodes;

  //
  // Cache of where this thing can move to
  //
  std::array< std::array< bool, MAP_HEIGHT >, MAP_WIDTH > can_move_to_tile;

  bool                  can_move_to(const spoint &to);
  Cost                  heuristic(const spoint at);
  Node                 *node_init(const spoint next_hop, Nodecost cost);
  std::vector< spoint > solve(bool allow_diagonal);
  void                  add_to_closed(Node *n);
  void                  add_to_open(Node *n);
  void                  dump(void);
  void                  eval_neighbor(Node *current, spoint delta);
  void                  init(void);
  void                  precalculate_can_move_to(void);
  void                  remove_from_open(Node *n);

  std::vector< spoint > create_path(const Node *came_from);
};

void Astar::add_to_open(Node *n)
{
  auto p = n->at;
  auto o = &open[ p.x ][ p.y ];
  if (*o) {
    THING_ERR(t, "Already in open");
    return;
  }
  *o = n;

  auto old_size = open_nodes.size();
  open_nodes.insert(std::make_pair(n->cost, n));
  auto new_size = open_nodes.size();
  if (old_size != new_size - 1) {
    THING_ERR(t, "open insert fail, old size %d, new size %d", (int) old_size, (int) new_size);
    return;
  }
}

void Astar::add_to_closed(Node *n)
{
  auto p = n->at;
  auto o = &closed[ p.x ][ p.y ];
  if (*o) {
    THING_ERR(t, "Already in closed");
    return;
  }
  *o = n;

  auto old_size = closed_nodes.size();
  closed_nodes.insert(std::make_pair(n->cost, n));
  auto new_size = closed_nodes.size();
  if (old_size != new_size - 1) {
    THING_ERR(t, "closed insert fail");
    return;
  }
}

void Astar::remove_from_open(Node *n)
{
  auto p = n->at;
  auto o = &open[ p.x ][ p.y ];
  if (! *o) {
    THING_ERR(t, "Not in open");
    return;
  }
  *o = nullptr;

  open_nodes.erase(n->cost);
}

Cost Astar::heuristic(const spoint at)
{
  //
  // This can create wiggles in the path as we're always looking at the distance
  // to the end point, and sometimes a diagonal move is closer.
  //
  return distance(dst, at);
}

Node *Astar::node_init(const spoint next_hop, Nodecost cost)
{
  auto n = &nodes[ next_hop.x ][ next_hop.y ];

  n->at = next_hop;

  switch (thing_assess_tile(g, v, l, next_hop, t)) {
    case THING_ENVIRON_HATES :    cost.cost += 10; break;
    case THING_ENVIRON_DISLIKES : cost.cost += 5; break;
    case THING_ENVIRON_NEUTRAL :  cost.cost += 1; break;
    case THING_ENVIRON_LIKES :    break;
    case THING_ENVIRON_ENUM_MAX : break;
  }

  n->cost = cost;

  //
  // Cost tiebreaker
  //
  tiebreak++;

  return n;
}

//
// Evaluate a neighbor for adding to the open set
//
void Astar::eval_neighbor(Node *current, spoint delta)
{
  auto next_hop = current->at + delta;

  //
  // If in the closed set already, ignore.
  //
  if (closed[ next_hop.x ][ next_hop.y ]) {
    return;
  }

  if (! can_move_to(next_hop)) {
    return;
  }

  Cost cost = current->cost.cost + heuristic(next_hop);

  Node *neighbor = open[ next_hop.x ][ next_hop.y ];
  if (! neighbor) {
    auto ncost          = Nodecost(cost, tiebreak);
    neighbor            = node_init(next_hop, ncost);
    neighbor->came_from = current;
    add_to_open(neighbor);
    return;
  }

  if (cost < neighbor->cost.cost) {
    auto ncost = Nodecost(cost, tiebreak);
    remove_from_open(neighbor);
    neighbor->came_from = current;
    neighbor->cost      = ncost;
    add_to_open(neighbor);
  }
}

std::vector< spoint > Astar::create_path(const Node *came_from)
{
  static const std::vector< spoint > empty;

  std::vector< spoint > out;

  while (came_from) {
    if (came_from->came_from) {
      out.push_back(came_from->at);
    }
    came_from = came_from->came_from;
  }

  return out;
}

void Astar::init(void)
{
#ifdef ENABLE_DEBUG_AI_ASTAR
  astar_debug = {};
#endif

  precalculate_can_move_to();
}

void Astar::precalculate_can_move_to(void)
{
  for (auto y = 0; y < MAP_HEIGHT; y++) {
    for (auto x = 0; x < MAP_WIDTH; x++) {
      can_move_to_tile[ x ][ y ] = thing_can_move_to_check_only(g, v, l, t, spoint(x, y));
    }
  }
}

bool Astar::can_move_to(const spoint &to) { return can_move_to_tile[ to.x ][ to.y ]; }

std::vector< spoint > Astar::solve(bool allow_diagonal)
{
  auto ncost    = Nodecost(heuristic(src), tiebreak);
  auto neighbor = node_init(src, ncost);

  add_to_open(neighbor);

  init();

  while (! open_nodes.empty()) {
    auto  c       = open_nodes.begin();
    Node *current = c->second;

    auto at = current->at;
    if (at == dst) {
      return create_path(current);
    }
    astar_debug[ at.x ][ at.y ] = '?';

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

void Astar::dump(void)
{
  THING_LOG(t, "ASTAR:");

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

std::vector< spoint > thing_astar_solve(Gamep g, Levelsp v, Levelp l, Thingp t, spoint src, spoint dst)
{
  TRACE_NO_INDENT();

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
#endif

  return path;
}
