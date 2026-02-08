//
// Copyright goblinhack@gmail.com
//

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

class Path
{
public:
  Path() = default;
  Path(std::vector< spoint > &p, Cost c) : path(p), cost(c) {}

  std::vector< spoint > path;

  Cost cost {};
};

class Nodecost
{
public:
  Nodecost(void) = default;
  Nodecost(Cost c) : cost(c)
  {
    static int tiebreak_;
    tiebreak = tiebreak_++;
  }

  bool operator<(const Nodecost &rhs) const
  {
    if (cost < rhs.cost) {
      return true;
    }
    if (cost > rhs.cost) {
      return false;
    }
    return (tiebreak < rhs.tiebreak);
  }

  Cost cost {};
  int  tiebreak {};
};

class Node
{
public:
  Node(void) = default;

  class Node *came_from {};
  Nodecost    cost;
  spoint      at;
  bool        is_disliked {};
};

//
// The nodemap needs to be sorted by distance, so std::map must be used
//
typedef std::map< Nodecost, Node * > Nodemap;

class Astar
{
public:
  Astar() {}

  Gamep       g = {};
  Levelsp     v = {};
  Levelp      l = {};
  Thingp      t = {};
  const Dmap *dmap {};

  std::array< std::array< Node *, MAP_HEIGHT >, MAP_WIDTH > open   = {};
  std::array< std::array< Node *, MAP_HEIGHT >, MAP_WIDTH > closed = {};
  std::array< std::array< Node, MAP_HEIGHT >, MAP_WIDTH >   nodes;

  Nodemap open_nodes;
  Nodemap closed_nodes;
  spoint  src;
  spoint  dst;

  void  add_to_open(Node *n);
  void  add_to_closed(Node *n);
  void  remove_from_open(Node *n);
  Node *node_init(const spoint next_hop, Nodecost cost);
  Cost  heuristic(const spoint at);
  void  eval_neighbor(Node *current, spoint delta);
  void  dump(void);

  std::tuple< std::vector< spoint >, Cost > create_path(const Node *came_from, Cost);

  Path solve(bool allow_diagonal);
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

  auto result = open_nodes.insert(std::make_pair(n->cost, n));
  if (! result.second) {
    THING_ERR(t, "Open insert fail");
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

  auto result = closed_nodes.insert(std::make_pair(n->cost, n));
  if (! result.second) {
    THING_ERR(t, "Closed insert fail");
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

Cost Astar::heuristic(const spoint at) { return distance(dst, at); }

Node *Astar::node_init(const spoint next_hop, Nodecost cost)
{
  auto n = &nodes[ next_hop.x ][ next_hop.y ];

  n->at          = next_hop;
  n->cost        = cost;
  n->is_disliked = thing_assess_tile(g, v, l, next_hop, t) == THING_ENVIRON_DISLIKES;

  return n;
}

//
// Evaluate a neighbor for adding to the open set
//
void Astar::eval_neighbor(Node *current, spoint delta)
{
  auto next_hop = current->at + delta;

  if ((next_hop.x <= 0) || (next_hop.y <= 0) || (next_hop.x >= MAP_WIDTH - 1) || (next_hop.y >= MAP_HEIGHT - 1)) {
    return;
  }

  //
  // Ignore walls.
  //
  if (dmap->val[ next_hop.x ][ next_hop.y ] == DMAP_IS_WALL) {
    return;
  }

  //
  // If in the closed set already, ignore.
  //
  if (closed[ next_hop.x ][ next_hop.y ]) {
    return;
  }

  Cost  cost     = current->cost.cost + heuristic(next_hop);
  Node *neighbor = open[ next_hop.x ][ next_hop.y ];
  if (! neighbor) {
    auto ncost          = Nodecost(cost);
    neighbor            = node_init(next_hop, ncost);
    neighbor->came_from = current;
    add_to_open(neighbor);
    return;
  }

  if (cost < neighbor->cost.cost) {
    remove_from_open(neighbor);
    neighbor->came_from = current;
    neighbor->cost      = cost;
    add_to_open(neighbor);
  }
}

std::tuple< std::vector< spoint >, Cost > Astar::create_path(const Node *came_from, Cost best_cost)
{
  static const std::vector< spoint > empty;

  std::vector< spoint > out;
  Cost                  cost               = came_from->cost.cost;
  int                   consecutive_hazard = 0;

  while (came_from) {
    //
    // No point continuing if the path is going to exceed the best.
    //
    if (cost >= best_cost) {
      return {empty, std::numeric_limits< int >::max()};
    }

    if (came_from->came_from) {
      out.push_back(came_from->at);

      //
      // If we pass over too many consecutive things we do not like, like chasms
      // then we cannot use this path.
      //
      if (came_from->is_disliked) {
        consecutive_hazard++;
        if (consecutive_hazard > 2) {
          return {empty, std::numeric_limits< int >::max()};
        }

        //
        // Not sure on the best value for this. We need something to increase the apparent cost.
        //
        cost += 5;
      } else {
        consecutive_hazard = 0;
      }
    }
    came_from = came_from->came_from;
  }

  return {out, cost};
}

Path Astar::solve(bool allow_diagonal)
{
  auto distance_to_next_hop = 0;
  auto ncost                = Nodecost(distance_to_next_hop + heuristic(src));
  auto neighbor             = node_init(src, ncost);
  add_to_open(neighbor);
  Path best;
  best.cost = std::numeric_limits< float >::max();

#ifdef ENABLE_DEBUG_AI_ASTAR
  astar_debug = {};
#endif

  while (! open_nodes.empty()) {
    auto  c       = open_nodes.begin();
    Node *current = c->second;

    auto at = current->at;
    if (at == dst) {
      auto [ path, cost ] = create_path(current, best.cost);

      if (cost < best.cost) {
        best.path = path;
        best.cost = cost;
      }

      remove_from_open(current);
      add_to_closed(current);
      continue;
    }

    remove_from_open(current);
    add_to_closed(current);

    eval_neighbor(current, spoint(-1, 0));
    eval_neighbor(current, spoint(1, 0));
    eval_neighbor(current, spoint(0, -1));
    eval_neighbor(current, spoint(0, 1));

    if (allow_diagonal) {
      if (thing_is_ethereal(t)) {
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
        if ((dmap->val[ at.x - 1 ][ at.y ] == DMAP_IS_WALL) || (dmap->val[ at.x ][ at.y - 1 ] == DMAP_IS_WALL)) {
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

        if ((dmap->val[ at.x - 1 ][ at.y ] == DMAP_IS_WALL) || (dmap->val[ at.x ][ at.y + 1 ] == DMAP_IS_WALL)) {
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

        if ((dmap->val[ at.x + 1 ][ at.y ] == DMAP_IS_WALL) || (dmap->val[ at.x ][ at.y - 1 ] == DMAP_IS_WALL)) {
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

        if ((dmap->val[ at.x + 1 ][ at.y ] == DMAP_IS_WALL) || (dmap->val[ at.x ][ at.y + 1 ] == DMAP_IS_WALL)) {
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

#ifdef ENABLE_DEBUG_AI_ASTAR
  for (const auto &p : best.path) {
    astar_debug[ p.x ][ p.y ] = 'b';
  }
#endif

  return best;
}

void Astar::dump(void)
{
  THING_LOG(t, "ASTAR:");

  for (auto y = 0; y < MAP_HEIGHT; y++) {
    std::string s;
    for (auto x = 0; x < MAP_WIDTH; x++) {

      auto        e = dmap->val[ x ][ y ];
      std::string buf;
      if (e == DMAP_IS_WALL) {
        buf = "#";
      } else if (e == DMAP_IS_PASSABLE) {
        buf = ".";
      } else {
        buf = " ";
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

void thing_astar_solve(Gamep g, Levelsp v, Levelp l, Thingp t, spoint src, spoint dst, const Dmap *dmap,
                       bool allow_diagonal)
{
  TRACE_NO_INDENT();

  auto a  = new Astar();
  a->g    = g;
  a->v    = v;
  a->l    = l;
  a->t    = t;
  a->src  = src;
  a->dst  = dst;
  a->dmap = dmap;

  auto path = a->solve(allow_diagonal);

  a->dump();

  delete a;
}
