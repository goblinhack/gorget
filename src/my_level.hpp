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

  bool set_id(point p, uint8_t z, Id);
  void set_id_no_check(point p, uint8_t z, Id);
  Id   get_id(point p, uint8_t z);
  Id   get_id_no_check(point p, uint8_t z);

  bool  set_tile(point p, uint8_t z, Tilep);
  void  set_tile_no_check(point p, uint8_t z, Tilep);
  Tilep get_tile(point p, uint8_t z);
  Tilep get_tile_no_check(point p, uint8_t z);

  Tpp    tp_get(point p, uint8_t slot);
  void   tp_set(point p, Tpp);
  void   tp_unset(point p, Tpp);
  Thingp thing_get(point p, uint8_t slot, Tpp * = nullptr);

  void anim(void);
  void assign_tiles(void);
  void display(void);
  void display_dungeon_tile(Tpp, Tilep, point tl, point br, point offset);
  void display_dungeon_tile(Tpp, uint16_t, point tl, point br, point offset);
  void display_dungeon(void);
  void display_dungeon_z_layer(int x, int y, int slot, int z, bool deco);
  void map_set(LevelDatap, const char *);
  void player_map_center(void);
  void player_create_and_place(void);
  void player_move_down(void);
  void player_move(int8_t, int8_t);
  void player_move_left(void);
  void player_move_right(void);
  void player_move_up(void);
  void set_display_bounds(void);
  void tick(void);
  void dungeon_create_and_place(void);

  bool is_same_type(point p, Tpp);

  Thingp thing_find_optional(ThingId id);
  Thingp thing_find(ThingId id);
  Thingp thing_new(Tpp, point p);
  void   thing_free(Thingp);
  void   thing_update_pos(Thingp);
  void   thing_push(Thingp);
  void   thing_pop(Thingp);
};

#endif // _MY_LEVEL_H_
