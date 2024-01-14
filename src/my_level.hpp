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
  int8_t minx = {};
  int8_t miny = {};
  int8_t maxx = {};
  int8_t maxy = {};

  bool is_oob(int8_t x, int8_t y);

  bool set_id(int8_t x, int8_t y, uint8_t z, Id);
  void set_id_no_check(int8_t x, int8_t y, uint8_t z, Id);
  Id   get_id(int8_t x, int8_t y, uint8_t z);
  Id   get_id_no_check(int8_t x, int8_t y, uint8_t z);

  bool  set_tile(int8_t x, int8_t y, uint8_t z, Tilep);
  void  set_tile_no_check(int8_t x, int8_t y, uint8_t z, Tilep);
  Tilep get_tile(int8_t x, int8_t y, uint8_t z);
  Tilep get_tile_no_check(int8_t x, int8_t y, uint8_t z);

  Tpp    tp_get(int8_t x, int8_t y, uint8_t slot);
  Thingp thing_get(int8_t x, int8_t y, uint8_t slot, Tpp * = nullptr);

  void anim(void);
  void assign_tiles(void);
  void display_tile(Tpp, Tilep, point tl, point br, point offset, bool shadow);
  void display_tile(Tpp, uint16_t, point tl, point br, point offset, bool shadow);
  void display(void);
  void display_z_layer(int z, bool shadow, bool deco);
  void place_create_and_place(void);
  void player_map_center(void);
  void player_move_down(void);
  void player_move_left(void);
  void player_move_right(void);
  void player_move_up(void);
  void player_move(int8_t, int8_t);
  void set_display_bounds(void);
  void tick(void);

  bool is_wall(const uint8_t x, const uint8_t y);
  bool is_wall(const point p);

  bool is_rock(const uint8_t x, const uint8_t y);
  bool is_rock(const point p);

  bool is_ladder(const uint8_t x, const uint8_t y);
  bool is_ladder(const point p);

  bool is_block(const uint8_t x, const uint8_t y);
  bool is_block(const point p);

  Thingp thing_find_optional(ThingId id);
  Thingp thing_find(ThingId id);
  Thingp thing_new(Tpp, int8_t x, int8_t y);
  void   thing_free(Thingp);
  void   thing_update_pos(Thingp);
  void   thing_update_speed(Thingp);
  void   thing_push(Thingp);
  void   thing_pop(Thingp);
};

#endif // _MY_LEVEL_H_
