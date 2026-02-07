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

static std::array< std::array< char, MAP_HEIGHT >, MAP_WIDTH > astar_debug {};

class Goal
{
public:
  int         prio  = {0};
  int         score = {0};
  spoint      at;
  std::string msg;
  Thingp      what {};
  bool        avoid {};

  Goal() = default;
  Goal(int prio, int score, spoint at, const std::string &msg) : prio(prio), score(score), at(at), msg(msg) {}
  Goal(int prio, int score, spoint at, const std::string &msg, bool avoid)
      : prio(prio), score(score), at(at), msg(msg), avoid(avoid)
  {
  }
  Goal(int prio, int score, spoint at, const std::string &msg, Thingp what)
      : prio(prio), score(score), at(at), msg(msg), what(what)
  {
  }
  Goal(int prio, int score, spoint at, const std::string &msg, Thingp what, bool avoid)
      : prio(prio), score(score), at(at), msg(msg), what(what), avoid(avoid)
  {
  }
};

class Path
{
public:
  Path() = default;
  Path(std::vector< spoint > &p, int c, const Goal &g) : path(p), cost(c), goal(g) {}

  std::vector< spoint > path;
  int                   cost {};
  Goal                  goal;
};

class Nodecost
{
public:
  Nodecost(void) = default;
  Nodecost(int c) : cost(c)
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

  int cost {};
  int tiebreak {};
};

class Node
{
public:
  Node(void) = default;
  Node(Thingp t, spoint p, Nodecost c) : cost(c), at(p) {}

  class Node *came_from {};
  Nodecost    cost;
  spoint      at;
  bool        is_disliked;
};

typedef std::map< Nodecost, Node * > Nodemap;

class Astar
{
public:
  Astar(spoint s, spoint g, const Dmap *d) : start(s), goal(g), dmap(d) {}

  std::array< std::array< Node *, MAP_HEIGHT >, MAP_WIDTH > open   = {};
  std::array< std::array< Node *, MAP_HEIGHT >, MAP_WIDTH > closed = {};
  Nodemap                                                   open_nodes;
  Nodemap                                                   closed_nodes;
  spoint                                                    start;
  spoint                                                    goal;
  const Dmap                                               *dmap {};

  void add_to_open(Gamep g, Levelsp v, Levelp l, Thingp t, Node *n)
  {
    auto p = n->at;
    auto o = &open[ p.x ][ p.y ];
    if (*o) {
      THING_ERR(t, "Already in open");
      return;
    }
    *o          = n;
    auto result = open_nodes.insert(std::make_pair(n->cost, n));
    if (! result.second) {
      THING_ERR(t, "Open insert fail");
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
    auto result = closed_nodes.insert(std::make_pair(n->cost, n));
    if (! result.second) {
      THING_ERR(t, "Closed insert fail");
      return;
    }
  }

  void remove_from_open(Gamep g, Levelsp v, Levelp l, Thingp t, Node *n)
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

  // Manhattan distance.
  int heuristic(Gamep g, Levelsp v, Levelp l, Thingp t, const spoint at)
  {
    // return (abs(goal.x - at.x) + abs(goal.y - at.y));
    return 1;
  }

  // Evaluate a neighbor for adding to the open set
  void eval_neighbor(Gamep g, Levelsp v, Levelp l, Thingp t, Node *current, spoint delta)
  {
    auto next_hop = current->at + delta;

    if ((next_hop.x < 0) || (next_hop.y < 0) || (next_hop.x > MAP_WIDTH - 1) || (next_hop.y > MAP_HEIGHT - 1)) {
      return;
    }

    // Ignore walls.
    if (dmap->val[ next_hop.x ][ next_hop.y ] == DMAP_IS_WALL) {
      return;
    }

    // If in the closed set already, ignore.
    if (closed[ next_hop.x ][ next_hop.y ]) {
      return;
    }

    int distance_to_next_hop = dmap->val[ next_hop.x ][ next_hop.y ];
    if (distance_to_next_hop == DMAP_IS_PASSABLE) {
      distance_to_next_hop = 0;
    }

    int  cost     = current->cost.cost + distance_to_next_hop + heuristic(g, v, l, t, next_hop);
    auto neighbor = open[ next_hop.x ][ next_hop.y ];
    if (! neighbor) {
      auto ncost          = Nodecost(cost + heuristic(g, v, l, t, next_hop));
      neighbor            = new Node(t, next_hop, ncost);
      neighbor->came_from = current;
      add_to_open(g, v, l, t, neighbor);
      return;
    }

    if (cost < neighbor->cost.cost) {
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
    int                   cost               = came_from->cost.cost;
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

  std::pair< Path, Path > solve(Gamep g, Levelsp v, Levelp l, Thingp t, const Goal *goalp, char *path_debug,
                                bool allow_diagonal)
  {
    auto distance_to_next_hop = 0;
    auto ncost                = Nodecost(distance_to_next_hop + heuristic(g, v, l, t, start));
    auto neighbor             = new Node(t, start, ncost);
    add_to_open(g, v, l, t, neighbor);
    Path best;
    best.cost = std::numeric_limits< int >::max();
    Path fallback;
    fallback.cost = std::numeric_limits< int >::max();

    float fallback_dist = distance(start, goal);

    while (! open_nodes.empty()) {
      auto  c       = open_nodes.begin();
      Node *current = c->second;

      auto at                     = current->at;
      astar_debug[ at.x ][ at.y ] = (char) ('?');
      if (at == goal) {
        auto [ path, cost ] = create_path(g, v, l, t, current);

        if (cost < best.cost) {
          if (goalp) {
            best.goal = *goalp;
          }
          best.path = path;
          best.cost = cost;
#ifdef ENABLE_DEBUG_AI_ASTAR
          for (const auto &p : path) {
            set(astar_debug, p.x, p.y, (char) ('A' + *path_debug));
          }
          (*path_debug)++;
#endif
        } else {
#ifdef ENABLE_DEBUG_AI_ASTAR
          for (const auto &p : path) {
            set(astar_debug, p.x, p.y, (char) ('a' + *path_debug));
          }
          (*path_debug)++;
#endif
        }
        remove_from_open(g, v, l, t, current);
        add_to_closed(g, v, l, t, current);
        continue;
      } else {
        //
        // Create any old path in case we cannot reach the goal
        //
        float dist = distance(goal, current->at);
        if (dist < fallback_dist) {
          fallback_dist       = dist;
          auto [ path, cost ] = create_path(g, v, l, t, current);
          if (goalp) {
            fallback.goal = *goalp;
          }
          fallback.path = path;
          fallback.cost = cost;
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

void astar_dump(Gamep g, Levelsp v, Levelp l, const Dmap *dmap, const spoint at, const spoint start, const spoint end)
{
  int x;
  int y;

  LOG("ASTAR:");
  for (y = start.y - 10; y < end.y + 10; y++) {
    std::string s;

    if (y < 0) {
      continue;
    }
    if (y >= MAP_WIDTH) {
      continue;
    }

    for (x = start.x - 10; x < end.x + 10; x++) {
      if (x < 0) {
        continue;
      }
      if (x >= MAP_WIDTH) {
        continue;
      }

      uint16_t e = dmap->val[ x ][ y ];

      std::string buf;
      if (e == DMAP_IS_WALL) {
        buf = "## ";
      } else if (e == DMAP_IS_PASSABLE) {
        buf = ".  ";
      } else if (e > 0) {
        buf = string_sprintf("%-3X", e);
      } else {
        buf = "*  ";
      }

      if (spoint(x, y) == at) {
        buf = " @ ";
      }

#ifdef ENABLE_DEBUG_AI_ASTAR
      if (get(astar_debug, x, y)) {
        buf[ 2 ] = get(astar_debug, x, y);
      }
#endif
      s += buf;
    }
    LOG("ASTAR:%s", s.c_str());
  }
}

void thing_astar_solve(Gamep g, Levelsp v, Levelp l, Thingp t, char path_debug, spoint src, spoint dst, const Dmap *d,
                       bool allow_diagonal)
{
  Goal goal;
  char tmp = path_debug;
  auto a   = Astar(src, dst, d);
  auto ret = a.solve(g, v, l, t, &goal, &tmp, allow_diagonal);
#ifdef ENABLE_DEBUG_AI_ASTAR
  astar_dump(d, s, s, g);
#endif
}
