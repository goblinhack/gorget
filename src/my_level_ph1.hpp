//
// Copyright Neil McGill, goblinhack@gmail.com
//

#pragma once

//
// Implements layered cycles that can be used to then create a set of rooms
//
#include "my_fwd.hpp"
#include "my_game_defs.hpp"
#include "my_point.hpp"
#include "my_random.hpp"

class Level1Node
{
public:
  //
  // LevelPh1 have a depth number, optional key, start and exit and corridors
  // to adjoining depths. Depth increases as we get closer to the exit.
  //
  int depth {0};

  //
  // Used only in the game start when creating a grid of levels
  //
  int walk_order_level_no {};

  //
  // pass 1 is the critical path
  // pass 2 are secret levels
  //
  int pass {0};
  int x, y;
  //
  // Not necessarily an actual key or lock, but something allowing access
  // to the other node. Only one key per node depth.
  //
  bool is_walked {false};
  bool is_secret {false};
  bool is_key {false};
  bool is_lock {false};
  bool is_entrance {false};
  bool is_dungeon_exit {false};
  bool on_critical_path {false};
  bool has_door {false};
  bool has_door_up {false};
  bool has_door_down {false};
  bool has_door_left {false};
  bool has_door_right {false};
  bool has_secret_dungeon_exit_up {false};
  bool has_secret_dungeon_exit_down {false};
  bool has_secret_dungeon_exit_left {false};
  bool has_secret_dungeon_exit_right {false};
  bool dir_up {false};
  bool dir_down {false};
  bool dir_left {false};
  bool dir_right {false};

  //
  // Update init_nodes on changes
  //
  bool has_path(void) { return (dir_down || dir_up || dir_left || dir_right); }

  void set_has_door_up(bool v)
  {
    has_door                   = v;
    has_door_up                = v;
    has_secret_dungeon_exit_up = false;
  }
  void set_has_door_down(bool v)
  {
    has_door                     = v;
    has_door_down                = v;
    has_secret_dungeon_exit_down = false;
  }
  void set_has_door_right(bool v)
  {
    has_door                      = v;
    has_door_right                = v;
    has_secret_dungeon_exit_right = false;
  }
  void set_has_door_left(bool v)
  {
    has_door                     = v;
    has_door_left                = v;
    has_secret_dungeon_exit_left = false;
  }
  void set_has_secret_dungeon_exit_up(bool v)
  {
    has_secret_dungeon_exit_up = v;
    has_door                   = false;
    has_door_up                = false;
  }
  void set_has_secret_dungeon_exit_down(bool v)
  {
    has_secret_dungeon_exit_down = v;
    has_door                     = false;
    has_door_down                = false;
  }
  void set_has_secret_dungeon_exit_right(bool v)
  {
    has_secret_dungeon_exit_right = v;
    has_door                      = false;
    has_door_right                = false;
  }
  void set_has_secret_dungeon_exit_left(bool v)
  {
    has_secret_dungeon_exit_left = v;
    has_door                     = false;
    has_door_left                = false;
  }
};

class LevelPh1
{
public:
  //
  // Set on success
  //
  bool ok {};

  std::vector< Level1Node > nodes;

  int grid_width {LEVEL_PH1_WIDTH};
  int grid_height {LEVEL_PH1_HEIGHT};

  int max_depth {0};
  int max_vdepth {0};

  //
  // Water, rocks etc...
  //
  int depth_obstacle {-1};

  LevelPh1(int grid_width, int grid_height) : grid_width(grid_width), grid_height(grid_height) {}

  bool create_path_to_dungeon_exit(int pass);
  bool is_oob(const int x, const int y) const;
  bool node_is_a_room(Level1Node *n);
  bool node_is_free(Level1Node *n);
  bool place_entrance(void);
  bool place_dungeon_exit(void);
  bool place_key(int depth, int pass);
  bool place_lock(int depth, int pass);
  bool remove_dead_end_paths(void);

  const Level1Node *get_node_ptr_const(const int x, const int y) const;
  Level1Node       *get_node_ptr(const int x, const int y);
  Level1Node       *node_addr(const int x, const int y);

  int offset(const int x, const int y) const;
  int snake_walk(int depth, int max_placed, int pass);

  point random_dir(void);

  void create_path_lock_to_key(int depth);
  void debug(std::string msg);
  void dmap_print_walls(Dmapp d);
  void dump(void);
  void construct(void);
  void hide_other_locks(int depth, int pass);
  void init_nodes(void);
  void join_depth_secret(int depth, int pass);
  void join_depth_to_next_depth(int depth, int pass);
  void join_nodes_of_same_depth(int depth, int pass);
  void log(void);
  void make_paths_off_critical_path_reachable(void);
  void putn(const int x, const int y, const Level1Node n);
  void random_dir(int *dx, int *dy);
  void remove_redundant_directions(void);
  void remove_stubs();
  void set_max_depth(void);
};

LevelPh1 level_ph1(void);
