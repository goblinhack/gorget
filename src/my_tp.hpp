//
// Copyright Neil McGill, goblinhack@gmail.com
//

#pragma once
#ifndef _MY_THING_TEMPLATE_H_
#define _MY_THING_TEMPLATE_H_

#include "my_main.hpp"
#include "my_tile.hpp"
#include <map>

using Tpidmap   = std::vector< class Tp   *>;
using Tpnamemap = std::map< std::string, class Tp * >;

enum {
  THING_RARITY_COMMON,
  THING_RARITY_UNCOMMON,
  THING_RARITY_RARE,
  THING_RARITY_VERY_RARE,
  THING_RARITY_UNIQUE,
};

class Tp
{
public:
  uint8_t z_depth {};

  TpId    id {};
  Tilevec tiles;

  // begin sort marker1 {
  bool is_animated_can_hflip {};
  bool is_blit_centered {};
  bool is_blit_on_ground {};
  bool is_blit_outlined {};
  bool is_blit_square_outlined {};
  bool is_blit_tiled {};
  bool is_dungeon_entrance {};
  bool is_dungeon_exit {};
  bool is_key {};
  bool is_monst1 {};
  bool is_player {};
  bool is_dungeon_wall {};
  // end sort marker1 }

  // begin sort marker2 {
  int chance_d1000_appearing {};
  int rarity {};
  // end sort marker2 }

  Tp(void);
  ~Tp(void);

  void chance_d1000_appearing_set(int v);
  void name_set(const std::string &v);
  void rarity_set(int v);
  void text_real_name_set(const std::string &v);
  void text_short_name_set(const std::string &v);
  void z_depth_set(int v);

  std::string name;
  std::string text_real_name;
  std::string text_short_name;

  void dbg_(const char *fmt, ...) CHECK_FORMAT_STR(printf, 2, 3);
  void err(const char *fmt, ...) CHECK_FORMAT_STR(printf, 2, 3);
  void err_(const char *fmt, va_list args); // compile error without
  void log(const char *fmt, ...) CHECK_FORMAT_STR(printf, 2, 3);
  void log_(const char *fmt, va_list args); // compile error without
  void die(const char *fmt, ...) CHECK_FORMAT_STR(printf, 2, 3);
  void die_(const char *fmt, va_list args); // compile error without
  void con(const char *fmt, ...) CHECK_FORMAT_STR(printf, 2, 3);
  void con_(const char *fmt, va_list args); // compile error without

  std::string text_short_capitalised(void) const;
  std::string text_long_capitalised(void) const;
  std::string text_a_or_an(void) const;
  std::string to_string(void);
  std::string to_short_string(void);
};

Tpp string2tp(const char **s);
Tpp string2tp(const std::string &s, int *len);
Tpp tp_find(const std::string &name);
Tpp tp_find(TpId id);
Tpp tp_load(const std::string &name);
Tpp tp_get_with_rarity_filter(Tpidmap &m);
Tpp tp_random_monst1(void);
Tpp tp_random_player(void);
Tpp tp_random_key(void);
Tpp tp_random_dungeon_entrance(void);
Tpp tp_random_dungeon_exit(void);

Tilep tp_first_tile(class Tp *);

uint8_t tp_init(void);

void tp_random_dungeon_init(void);
void tp_fini(void);
void tp_fixup(void);
void tp_get_id(const std::string &tp_name, int *id);

extern Tpidmap   tp_id_map;
extern Tpnamemap tp_name_map;

#endif // THING_TEMPLATE_H_
