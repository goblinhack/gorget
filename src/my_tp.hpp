//
// Copyright Neil McGill, goblinhack@gmail.com
//

#pragma once
#ifndef _MY_THING_TEMPLATE_H_
#define _MY_THING_TEMPLATE_H_

#include "my_minimal.hpp"

#include <stdarg.h>

class Tp;

enum {
  MAP_DEPTH_FLOOR,
  MAP_DEPTH_WALL,
  MAP_DEPTH_DOOR,
  MAP_DEPTH_OBJ1,
  MAP_DEPTH_OBJ2,
  MAP_DEPTH_PLAYER,
};

enum {
  THING_RARITY_COMMON,
  THING_RARITY_UNCOMMON,
  THING_RARITY_RARE,
  THING_RARITY_VERY_RARE,
  THING_RARITY_UNIQUE,
};

enum { MONST_CLASS_A, MONST_CLASS_MAX };

bool tp_init(void);

const char *tp_name(Tpp);
const char *text_a_or_an(Tpp);
const char *text_long_capitalised(Tpp);
const char *text_short_capitalised(Tpp);
const char *to_short_string(Tpp);
const char *to_string(Tpp);

int   tp_tiles_size(Tpp tp);
Tilep tp_first_tile(class Tp *);
Tilep tp_tiles_get(Tpp tp, int index);
void  tp_tiles_push_back(Tpp tp, Tilep val);

TpId tp_id_get(Tpp tp);
Tpp  tp_find(TpId id);

Tpp string2tp(const char **s);
Tpp string2tp(const char **s, int *len);
Tpp tp_find(const char *);
Tpp tp_load(const char *);
Tpp tp_random_dungeon_entrance(void);
Tpp tp_random_exit(void);
Tpp tp_random_key(void);
Tpp tp_random_monst(int c);
Tpp tp_random_player(void);
Tpp tp_random_wall(void);

void con(Tpp, const char *fmt, ...) CHECK_FORMAT_STR(printf, 2, 3);
void con_(Tpp, const char *fmt, va_list args); // compile error without
void dbg_(Tpp, const char *fmt, ...) CHECK_FORMAT_STR(printf, 2, 3);
void die(Tpp, const char *fmt, ...) CHECK_FORMAT_STR(printf, 2, 3);
void die_(Tpp, const char *fmt, va_list args); // compile error without
void err(Tpp, const char *fmt, ...) CHECK_FORMAT_STR(printf, 2, 3);
void err_(Tpp, const char *fmt, va_list args); // compile error without
void log(Tpp, const char *fmt, ...) CHECK_FORMAT_STR(printf, 2, 3);
void log_(Tpp, const char *fmt, va_list args); // compile error without
void tp_fini(void);
void tp_fixup(void);
void tp_get_id(const char *, int *id);
void tp_random_dungeon_init(void);

const char *tp_name(Tpp tp);
const char *to_string(Tpp tp);
const char *to_short_string(Tpp tp);

bool tp_is_animated_can_hflip_get(Tpp tp);
void tp_is_animated_can_hflip_set(Tpp tp, bool val);

bool tp_is_animated_no_dir_get(Tpp tp);
void tp_is_animated_no_dir_set(Tpp tp, bool val);

bool tp_is_blit_centered_get(Tpp tp);
void tp_is_blit_centered_set(Tpp tp, bool val);

bool tp_is_blit_on_ground_get(Tpp tp);
void tp_is_blit_on_ground_set(Tpp tp, bool val);

bool tp_is_blit_outlined_get(Tpp tp);
void tp_is_blit_outlined_set(Tpp tp, bool val);

bool tp_is_blit_square_outlined_get(Tpp tp);
void tp_is_blit_square_outlined_set(Tpp tp, bool val);

bool tp_is_blit_tiled_get(Tpp tp);
void tp_is_blit_tiled_set(Tpp tp, bool val);

bool tp_is_cursor_get(Tpp tp);
void tp_is_cursor_set(Tpp tp, bool val);

bool tp_is_door_get(Tpp tp);
void tp_is_door_set(Tpp tp, bool val);

bool tp_is_dungeon_entrance_get(Tpp tp);
void tp_is_dungeon_entrance_set(Tpp tp, bool val);

bool tp_is_exit_get(Tpp tp);
void tp_is_exit_set(Tpp tp, bool val);

bool tp_is_floor_get(Tpp tp);
void tp_is_floor_set(Tpp tp, bool val);

bool tp_is_key_get(Tpp tp);
void tp_is_key_set(Tpp tp, bool val);

bool tp_is_monst_get(Tpp tp);
void tp_is_monst_set(Tpp tp, bool val);

bool tp_is_monst_class_get(Tpp tp, int val);
void tp_is_monst_class_set(Tpp tp, bool val);

bool tp_is_obs_monst_get(Tpp tp);
void tp_is_obs_monst_set(Tpp tp, bool val);

bool tp_is_obs_player_get(Tpp tp);
void tp_is_obs_player_set(Tpp tp, bool val);

bool tp_is_player_get(Tpp tp);
void tp_is_player_set(Tpp tp, bool val);

bool tp_is_wall_get(Tpp tp);
void tp_is_wall_set(Tpp tp, bool val);

uint8_t tp_player_index_get(Tpp tp);
void    tp_player_index_set(Tpp tp, uint8_t val);

void    tp_z_depth_set(Tpp tp, uint8_t val);
uint8_t tp_z_depth_get(Tpp tp);

void tp_speed_set(Tpp tp, int val);
int  tp_speed_get(Tpp tp);

#endif // THING_TEMPLATE_H_
