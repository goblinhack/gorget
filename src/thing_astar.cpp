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
#include <set>

#define ENABLE_DEBUG_AI_ASTAR

static char astar_debug[ MAP_WIDTH ][ MAP_HEIGHT ];

class Path
{
public:
  Path() = default;
  Path(std::vector< spoint > &p, float c) : path(p), cost(c) {}

  std::vector< spoint > path;
  float                 cost {};
};

class Node
{
public:
  Node(void) = default;
  Node(Thingp t, spoint p, float c) : cost(c), at(p) {}

  class Node *came_from {};
  float       cost;
  spoint      at;
};

typedef std::set< Node * > Nodemap;

class Astar
{
public:
  Astar(spoint s, spoint g, const Dmap *d) : src(s), dst(g), dmap(d) {}

  Node       *open[ MAP_WIDTH ][ MAP_HEIGHT ]   = {};
  Node       *closed[ MAP_WIDTH ][ MAP_HEIGHT ] = {};
  Nodemap     open_nodes;
  Nodemap     closed_nodes;
  spoint      src;
  spoint      dst;
  const Dmap *dmap;

  void add_to_open(Gamep g, Levelsp v, Levelp l, Thingp t, Node *n)
  {
    auto p = n->at;
    auto o = &open[ p.x ][ p.y ];
    if (*o) {
      THING_ERR(t, "Already in open");
      return;
    }
    *o          = n;
    auto result = open_nodes.insert(n);
    if (! result.second) {
      THING_ERR(t, "open insert fail");
      return;
    }
  }

  void add_to_closed(Gamep g, Levelsp v, Levelp l, Thingp t, Node *n)
  {
    auto p = n->at;
    auto o = &closed[ p.x ][ p.y ];
    if (*o) {
      THING_ERR(t, "Already in closed");
      return;
    }
    *o          = n;
    auto result = closed_nodes.insert(n);
    if (! result.second) {
      THING_ERR(t, "closed insert fail");
      return;
    }
  }

  void remove_from_open(Gamep g, Levelsp v, Levelp l, Thingp t, Node *n)
  {
    auto p = n->at;
    auto o = &open[ p.x ][ p.y ];
    if (! *o) {
      THING_ERR(t, "not in open");
      return;
    }
    *o = nullptr;
    open_nodes.erase(n);
  }

  //
  // Manhattan distance.
  //
  float heuristic(Gamep g, Levelsp v, Levelp l, Thingp t, const spoint at) { return distance(at, dst); }

  //
  // Evaluate a neighbor for adding to the open set
  //
  void eval_neighbor(Gamep g, Levelsp v, Levelp l, Thingp t, Node *current, spoint delta)
  {
    auto next_hop = current->at + delta;

    if ((next_hop.x < 0) || (next_hop.y < 0) || (next_hop.x > MAP_WIDTH - 1) || (next_hop.y > MAP_HEIGHT - 1)) {
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

    float h        = heuristic(g, v, l, t, next_hop);
    float cost     = current->cost + h;
    auto  neighbor = open[ next_hop.x ][ next_hop.y ];
    if (! neighbor) {
      neighbor            = new Node(t, next_hop, cost);
      neighbor->came_from = current;
      add_to_open(g, v, l, t, neighbor);
      return;
    }

    if (cost < neighbor->cost) {
      remove_from_open(g, v, l, t, neighbor);
      neighbor->came_from = current;
      neighbor->cost      = cost;
      add_to_open(g, v, l, t, neighbor);
    }
  }

  void cleanup(void)
  {
    for (auto y = 0; y < MAP_HEIGHT; y++) {
      for (auto x = 0; x < MAP_WIDTH; x++) {
        if (open[ x ][ y ]) {
          delete open[ x ][ y ];
        }
        if (closed[ x ][ y ]) {
          delete closed[ x ][ y ];
        }
      }
    }
  }

  std::tuple< std::vector< spoint >, int > create_path(Gamep g, Levelsp v, Levelp l, Thingp t, const Node *came_from)
  {
    std::vector< spoint > out;
    float                 cost               = came_from->cost;
    int                   consecutive_hazard = 0;

    while (came_from) {
      if (came_from->came_from) {
        auto p = came_from->at;
        out.push_back(p);

        //
        // If we pass over too many consecutive things we do not like, like chasms
        // then we cannot use this path.
        //
        if (thing_assess_tile(g, v, l, p, t) == THING_ENVIRON_DISLIKES) {
          consecutive_hazard++;
          if (consecutive_hazard > 2) {
            out.clear();
            return {out, std::numeric_limits< int >::max()};
          }
        } else {
          consecutive_hazard = 0;
        }
      }
      came_from = came_from->came_from;
    }

    return {out, cost};
  }

  std::pair< Path, Path > solve(Gamep g, Levelsp v, Levelp l, Thingp t, char *path_debug, bool allow_diagonal)
  {
    float ncost    = heuristic(g, v, l, t, src);
    auto  neighbor = new Node(t, src, ncost);
    add_to_open(g, v, l, t, neighbor);
    Path best;
    best.cost = std::numeric_limits< float >::max();
    Path fallback;
    fallback.cost = std::numeric_limits< float >::max();

    float fallback_dist = distance(src, dst);

    while (! open_nodes.empty()) {
      auto  c       = open_nodes.begin();
      Node *current = *c;

      auto at = current->at;
      // astar_debug[ at.x ][ at.y ] = (char) ('?');
      if (at == dst) {
        auto [ path, cost ] = create_path(g, v, l, t, current);

        if (cost < best.cost) {
          best.path = path;
          best.cost = cost;
#if 0
          for (const auto &p : path) {
            astar_debug[ p.x ][ p.y ] = (char) ('A' + *path_debug);
          }
          (*path_debug)++;
#endif
        } else {
#if 0
          for (const auto &p : path) {
            astar_debug[ p.x ][ p.y ] = (char) ('a' + *path_debug);
          }
          (*path_debug)++;
#endif
        }
        remove_from_open(g, v, l, t, current);
        add_to_closed(g, v, l, t, current);
        continue;
      } else {
        //
        // Create any old path in case we cannot reach the dst
        //
        float dist = distance(dst, current->at);
        if (dist < fallback_dist) {
          fallback_dist       = dist;
          auto [ path, cost ] = create_path(g, v, l, t, current);
          fallback.path       = path;
          fallback.cost       = cost;
        }
      }

      remove_from_open(g, v, l, t, current);
      add_to_closed(g, v, l, t, current);

      eval_neighbor(g, v, l, t, current, spoint(-1, 0));
      eval_neighbor(g, v, l, t, current, spoint(1, 0));
      eval_neighbor(g, v, l, t, current, spoint(0, -1));
      eval_neighbor(g, v, l, t, current, spoint(0, 1));

      //
      // This leads to the robot taking diagonals across lava which looks like cheating.
      //
      // Also leads to zig zag paths over chasms that would need optimized.
      //
      if (allow_diagonal) {
        if ((dmap->val[ at.x - 1 ][ at.y ] == DMAP_IS_WALL) || dmap->val[ at.x ][ at.y - 1 ] == DMAP_IS_WALL) {
          eval_neighbor(g, v, l, t, current, spoint(-1, -1));
        }
        if ((dmap->val[ at.x - 1 ][ at.y ] == DMAP_IS_WALL) || dmap->val[ at.x ][ at.y + 1 ] == DMAP_IS_WALL) {
          eval_neighbor(g, v, l, t, current, spoint(-1, 1));
        }
        if ((dmap->val[ at.x + 1 ][ at.y ] == DMAP_IS_WALL) || dmap->val[ at.x ][ at.y - 1 ] == DMAP_IS_WALL) {
          eval_neighbor(g, v, l, t, current, spoint(1, -1));
        }
        if ((dmap->val[ at.x + 1 ][ at.y ] == DMAP_IS_WALL) || dmap->val[ at.x ][ at.y + 1 ] == DMAP_IS_WALL) {
          eval_neighbor(g, v, l, t, current, spoint(1, 1));
        }
      }
    }

    cleanup();

    return (std::pair(best, fallback));
  }
};

void astar_dump(Gamep g, Levelsp v, Levelp l, Thingp t, const Dmap *dmap, const spoint src, const spoint dst)
{
  THING_LOG(t, "ASTAR:");
  for (auto y = 0; y < MAP_HEIGHT; y++) {
    std::string s;
    for (auto x = 0; x < MAP_WIDTH; x++) {
      uint8_t e = dmap->val[ x ][ y ];

      char buf = ' ';
      if (e == DMAP_IS_WALL) {
        buf = '#';
      }

#ifdef ENABLE_DEBUG_AI_ASTAR
      if (astar_debug[ x ][ y ]) {
        buf = astar_debug[ x ][ y ];
      }
#endif

      if (spoint(x, y) == src) {
        buf = '@';
      }

      if (spoint(x, y) == dst) {
        buf = '*';
      }

      s += buf;
    }
    THING_LOG(t, "ASTAR:%s", s.c_str());
  }
}

void thing_astar_solve(Gamep g, Levelsp v, Levelp l, Thingp t, char path_debug, spoint src, spoint dst, const Dmap *d,
                       bool allow_diagonal)
{
  char tmp = path_debug;
  memset(astar_debug, 0, sizeof(astar_debug));
  auto a   = Astar(src, dst, d);
  auto ret = a.solve(g, v, l, t, &tmp, allow_diagonal);
#ifdef ENABLE_DEBUG_AI_ASTAR
  for (const auto &p : ret.second.path) {
    astar_debug[ p.x ][ p.y ] = 'f';
  }
  for (const auto &p : ret.first.path) {
    astar_debug[ p.x ][ p.y ] = 'B';
  }
  astar_dump(g, v, l, t, d, src, dst);
#endif
}
