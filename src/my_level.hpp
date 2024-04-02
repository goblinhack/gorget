//
// Copyright Neil McGill, goblinhack@gmail.com
//

#pragma once
#ifndef _MY_LEVEL_H_
#define _MY_LEVEL_H_

#include <inttypes.h>

#include "my_fwd.hpp"
#include "my_level_data.hpp"
#include "my_point.hpp"

class Level
{
public:
  Level();
  ~Level();

  LevelDatap data {};

  //
  // Level display bounds
  //
  int16_t minx = {};
  int16_t miny = {};
  int16_t maxx = {};
  int16_t maxy = {};

  bool is_oob(point p);
  bool is_same_type(point p, Tpp);
  bool set_id(point p, uint8_t z, Id);
  bool set_tile(point p, uint8_t z, Tilep);
  bool tick_is_in_progress(void);
  bool thing_player_move_request(bool up, bool down, bool left, bool right);
  bool thing_can_move(Thingp, point new_loc);

  Id get_id_no_check(point p, uint8_t z);
  Id get_id(point p, uint8_t z);

  Thingp thing_player(void);
  Thingp thing_find_optional(ThingId id);
  Thingp thing_find(ThingId id);
  Thingp thing_get(point p, uint8_t slot, Tpp * = nullptr);
  Thingp thing_init(Tpp, point p);
  Thingp thing_new(Tpp, point p);

  Tilep get_tile_no_check(point p, uint8_t z);
  Tilep get_tile(point p, uint8_t z);

  Tpp thing_tp(Thingp);
  Tpp tp_get(point p, uint8_t slot);

  void anim(void);
  void assign_tiles(void);
  void bounds_set(void);
  void display_dungeon_tile(Tpp, Tilep, point tl, point br, point offset);
  void display_dungeon_tile(Tpp, uint16_t, point tl, point br, point offset);
  void display_dungeon(void);
  void display_dungeon_z_layer(int x, int y, int slot, int z, bool deco);
  void display(void);
  void dungeon_create_and_place(void);
  void map_set(LevelDatap, const char *);
  void scroll_delta(int, int);
  void scroll_to_player(void);
  void scroll_warp_to_player(void);
  void set_id_no_check(point p, uint8_t z, Id);
  void set_tile_no_check(point p, uint8_t z, Tilep);
  void thing_free(Thingp);
  void thing_interpolate(Thingp, float dt);
  void thing_move(Thingp, point new_loc);
  void thing_player_create_and_place(void);
  void thing_player_map_center(void);
  void thing_player_move_accum(bool up, bool down, bool left, bool right);
  void thing_player_move_delta(point);
  void thing_player_move_reset(void);
  void thing_pop(Thingp);
  void thing_push(Thingp);
  void thing_update(Thingp);
  void tick_begin_requested(const std::string &why);
  void tick_begin(void);
  void tick_body(float dt);
  void tick_end_requested(void);
  void tick_time_step(void);
  void tick(void);
  void tp_set(point p, Tpp);
  void tp_unset(point p, Tpp);
};

#endif // _MY_LEVEL_H_
