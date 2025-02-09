//
// Copyright Neil McGill, goblinhack@gmail.com
//

#pragma once
#ifndef _MY_THING_TEMPLATE_H_
#define _MY_THING_TEMPLATE_H_

#include "my_enums.hpp"
#include "my_minimal.hpp"

#include <stdarg.h>

class Tp;

bool tp_init(void);

const char *text_a_or_an(Tpp);
const char *text_long_capitalised(Tpp);
const char *text_short_capitalised(Tpp);
const char *to_short_string(Tpp);
const char *to_string(Tpp);
const char *tp_name(Tpp);

int   tp_tiles_size(Tpp tp);
Tilep tp_first_tile(class Tp *);
Tilep tp_tiles_get(Tpp tp, int index);
void  tp_tiles_push_back(Tpp tp, Tilep val);

TpId tp_id_get(Tpp tp);
Tpp  tp_find(TpId id);
Tpp  tp_find_mand(const char *);
Tpp  tp_find_opt(const char *);

Tpp string2tp(const char **s);
Tpp string2tp(const char **s, int *len);
Tpp tp_load(const char *);
Tpp tp_random(ThingFlag);
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

bool tp_flag(Tpp tp, ThingFlag);
void tp_flag_set(Tpp tp, ThingFlag, bool val);

void    tp_z_depth_set(Tpp tp, uint8_t val);
uint8_t tp_z_depth_get(Tpp tp);

void    tp_z_prio_set(Tpp tp, uint8_t val);
uint8_t tp_z_prio_get(Tpp tp);

void tp_speed_set(Tpp tp, int val);
int  tp_speed_get(Tpp tp);

#endif // THING_TEMPLATE_H_
