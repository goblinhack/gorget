//
// Copyright goblinhack@gmail.com
//

#include "my_bits.hpp"
#include "my_callstack.hpp"
#include "my_level.hpp"
#include "my_main.hpp"
#include "my_random.hpp"
#include "my_tile.hpp"

#include <map>

/* clang-format off */
#define IS_JOIN_ENUM(list_macro)                  \
    list_macro(IS_JOIN_BL,     "IS_JOIN_BL"),     \
    list_macro(IS_JOIN_BL2,    "IS_JOIN_BL2"),    \
    list_macro(IS_JOIN_BLOCK,  "IS_JOIN_BLOCK"),  \
    list_macro(IS_JOIN_BOT,    "IS_JOIN_BOT"),    \
    list_macro(IS_JOIN_BR,     "IS_JOIN_BR"),     \
    list_macro(IS_JOIN_BR2,    "IS_JOIN_BR2"),    \
    list_macro(IS_JOIN_HORIZ,  "IS_JOIN_HORIZ"),  \
    list_macro(IS_JOIN_HORIZ2, "IS_JOIN_HORIZ2"), \
    list_macro(IS_JOIN_LEFT,   "IS_JOIN_LEFT"),   \
    list_macro(IS_JOIN_NODE,   "IS_JOIN_NODE"),   \
    list_macro(IS_JOIN_RIGHT,  "IS_JOIN_RIGHT"),  \
    list_macro(IS_JOIN_T_1,    "IS_JOIN_T_1"),    \
    list_macro(IS_JOIN_T_2,    "IS_JOIN_T_2"),    \
    list_macro(IS_JOIN_T_3,    "IS_JOIN_T_3"),    \
    list_macro(IS_JOIN_T,      "IS_JOIN_T"),      \
    list_macro(IS_JOIN_T180_1, "IS_JOIN_T180_1"), \
    list_macro(IS_JOIN_T180_2, "IS_JOIN_T180_2"), \
    list_macro(IS_JOIN_T180_3, "IS_JOIN_T180_3"), \
    list_macro(IS_JOIN_T180,   "IS_JOIN_T180"),   \
    list_macro(IS_JOIN_T270_1, "IS_JOIN_T270_1"), \
    list_macro(IS_JOIN_T270_2, "IS_JOIN_T270_2"), \
    list_macro(IS_JOIN_T270_3, "IS_JOIN_T270_3"), \
    list_macro(IS_JOIN_T270,   "IS_JOIN_T270"),   \
    list_macro(IS_JOIN_T90_1,  "IS_JOIN_T90_1"),  \
    list_macro(IS_JOIN_T90_2,  "IS_JOIN_T90_2"),  \
    list_macro(IS_JOIN_T90_3,  "IS_JOIN_T90_3"),  \
    list_macro(IS_JOIN_T90,    "IS_JOIN_T90"),    \
    list_macro(IS_JOIN_TL,     "IS_JOIN_TL"),     \
    list_macro(IS_JOIN_TL2,    "IS_JOIN_TL2"),    \
    list_macro(IS_JOIN_TOP,    "IS_JOIN_TOP"),    \
    list_macro(IS_JOIN_TR,     "IS_JOIN_TR"),     \
    list_macro(IS_JOIN_TR2,    "IS_JOIN_TR2"),    \
    list_macro(IS_JOIN_VERT,   "IS_JOIN_VERT"),   \
    list_macro(IS_JOIN_VERT2,  "IS_JOIN_VERT2"),  \
    list_macro(IS_JOIN_X,      "IS_JOIN_X"),      \
    list_macro(IS_JOIN_X1_180, "IS_JOIN_X1_180"), \
    list_macro(IS_JOIN_X1_270, "IS_JOIN_X1_270"), \
    list_macro(IS_JOIN_X1_90,  "IS_JOIN_X1_90"),  \
    list_macro(IS_JOIN_X1,     "IS_JOIN_X1"),     \
    list_macro(IS_JOIN_X2_180, "IS_JOIN_X2_180"), \
    list_macro(IS_JOIN_X2_270, "IS_JOIN_X2_270"), \
    list_macro(IS_JOIN_X2_90,  "IS_JOIN_X2_90"),  \
    list_macro(IS_JOIN_X2,     "IS_JOIN_X2"),     \
    list_macro(IS_JOIN_X3_180, "IS_JOIN_X3_180"), \
    list_macro(IS_JOIN_X3,     "IS_JOIN_X3"),     \
    list_macro(IS_JOIN_X4_180, "IS_JOIN_X4_180"), \
    list_macro(IS_JOIN_X4_270, "IS_JOIN_X4_270"), \
    list_macro(IS_JOIN_X4_90,  "IS_JOIN_X4_90"),  \
    list_macro(IS_JOIN_X4,     "IS_JOIN_X4"),

/* clang-format on */

ENUM_DEF_H(IS_JOIN_ENUM, is_join_enum)
ENUM_DEF_C(IS_JOIN_ENUM, is_join_enum)

static void level_assign_tiles_at(Gamep g, Levelsp v, Levelp l, spoint p)
{
  TRACE_NO_INDENT();

  auto x = p.x;
  auto y = p.y;

  for (auto slot = 0; slot < MAP_SLOTS; slot++) {
    Tpp tp;

    auto t = thing_and_tp_get_at(g, v, l, p, slot, &tp);
    if (! t) {
      continue;
    }

    if (tp_is_tiled(tp)) {
      auto tile_name = tp_name(tp);

      uint16_t A = level_is_same_obj_type_at(g, v, l, spoint(x - 1, y - 1), tp) ? 1 : 0;
      uint16_t B = level_is_same_obj_type_at(g, v, l, spoint(x, y - 1), tp) ? 1 : 0;
      uint16_t C = level_is_same_obj_type_at(g, v, l, spoint(x + 1, y - 1), tp) ? 1 : 0;
      uint16_t D = level_is_same_obj_type_at(g, v, l, spoint(x - 1, y), tp) ? 1 : 0;
      uint16_t E = level_is_same_obj_type_at(g, v, l, spoint(x, y), tp) ? 1 : 0;
      uint16_t F = level_is_same_obj_type_at(g, v, l, spoint(x + 1, y), tp) ? 1 : 0;
      uint16_t G = level_is_same_obj_type_at(g, v, l, spoint(x - 1, y + 1), tp) ? 1 : 0;
      uint16_t H = level_is_same_obj_type_at(g, v, l, spoint(x, y + 1), tp) ? 1 : 0;
      uint16_t I = level_is_same_obj_type_at(g, v, l, spoint(x + 1, y + 1), tp) ? 1 : 0;

      const uint16_t omask
          = (I << 8) | (H << 7) | (G << 6) | (F << 5) | (E << 4) | (D << 3) | (C << 2) | (B << 1) | (A << 0);

      uint8_t  block_type_score;
      uint8_t  best_block_type = 0;
      int8_t   block_type      = -1;
      uint16_t mask;

#define BLOCK(a, b, c, d, e, f, g, h, i, _index_)                                                                    \
  mask = (i << 8) | (h << 7) | (g << 6) | (f << 5) | (e << 4) | (d << 3) | (c << 2) | (b << 1) | (a << 0);           \
                                                                                                                     \
  if ((mask & omask) == mask) {                                                                                      \
    uint32_t difference = mask ^ omask;                                                                              \
    BITCOUNT(difference);                                                                                            \
    block_type_score = 32 - difference;                                                                              \
    if (block_type_score > best_block_type) {                                                                        \
      best_block_type = block_type_score;                                                                            \
      block_type      = _index_;                                                                                     \
    }                                                                                                                \
  }

      BLOCK(1, 1, 1, 1, 1, 1, 1, 1, 1, IS_JOIN_BLOCK)
      BLOCK(0, 0, 0, 0, 1, 0, 0, 0, 0, IS_JOIN_NODE)
      BLOCK(0, 0, 0, 0, 0, 0, 0, 0, 0, IS_JOIN_NODE) // moving blocks
      BLOCK(0, 0, 0, 0, 1, 1, 0, 0, 0, IS_JOIN_LEFT)
      BLOCK(0, 0, 0, 0, 1, 0, 0, 1, 0, IS_JOIN_TOP)
      BLOCK(0, 0, 0, 1, 1, 0, 0, 0, 0, IS_JOIN_RIGHT)
      BLOCK(0, 1, 0, 0, 1, 0, 0, 0, 0, IS_JOIN_BOT)
      BLOCK(0, 0, 0, 1, 1, 1, 0, 0, 0, IS_JOIN_HORIZ)
      BLOCK(0, 1, 0, 0, 1, 0, 0, 1, 0, IS_JOIN_VERT)
      BLOCK(0, 0, 0, 0, 1, 1, 0, 1, 1, IS_JOIN_TL2)
      BLOCK(0, 1, 1, 0, 1, 1, 0, 0, 0, IS_JOIN_BL2)
      BLOCK(1, 1, 0, 1, 1, 0, 0, 0, 0, IS_JOIN_BR2)
      BLOCK(0, 0, 0, 1, 1, 0, 1, 1, 0, IS_JOIN_TR2)
      BLOCK(0, 0, 0, 0, 1, 1, 0, 1, 0, IS_JOIN_TL)
      BLOCK(0, 1, 0, 0, 1, 1, 0, 0, 0, IS_JOIN_BL)
      BLOCK(0, 1, 0, 1, 1, 0, 0, 0, 0, IS_JOIN_BR)
      BLOCK(0, 0, 0, 1, 1, 0, 0, 1, 0, IS_JOIN_TR)
      BLOCK(1, 1, 0, 1, 1, 0, 1, 1, 0, IS_JOIN_T90_3)
      BLOCK(1, 1, 1, 1, 1, 1, 0, 0, 0, IS_JOIN_T180_3)
      BLOCK(0, 1, 1, 0, 1, 1, 0, 1, 1, IS_JOIN_T270_3)
      BLOCK(0, 0, 0, 1, 1, 1, 1, 1, 1, IS_JOIN_T_3)
      BLOCK(0, 1, 0, 0, 1, 1, 0, 1, 0, IS_JOIN_T270)
      BLOCK(0, 1, 0, 1, 1, 1, 0, 0, 0, IS_JOIN_T180)
      BLOCK(0, 1, 0, 1, 1, 0, 0, 1, 0, IS_JOIN_T90)
      BLOCK(0, 0, 0, 1, 1, 1, 0, 1, 0, IS_JOIN_T)
      BLOCK(0, 1, 1, 0, 1, 1, 0, 1, 0, IS_JOIN_T270_2)
      BLOCK(1, 1, 0, 1, 1, 1, 0, 0, 0, IS_JOIN_T180_2)
      BLOCK(0, 1, 0, 1, 1, 0, 1, 1, 0, IS_JOIN_T90_2)
      BLOCK(0, 0, 0, 1, 1, 1, 0, 1, 1, IS_JOIN_T_2)
      BLOCK(0, 1, 0, 0, 1, 1, 0, 1, 1, IS_JOIN_T270_1)
      BLOCK(0, 1, 1, 1, 1, 1, 0, 0, 0, IS_JOIN_T180_1)
      BLOCK(1, 1, 0, 1, 1, 0, 0, 1, 0, IS_JOIN_T90_1)
      BLOCK(0, 0, 0, 1, 1, 1, 1, 1, 0, IS_JOIN_T_1)
      BLOCK(0, 1, 0, 1, 1, 1, 0, 1, 0, IS_JOIN_X)
      BLOCK(0, 1, 0, 1, 1, 1, 0, 1, 1, IS_JOIN_X1)
      BLOCK(0, 1, 1, 1, 1, 1, 0, 1, 0, IS_JOIN_X1_270)
      BLOCK(1, 1, 0, 1, 1, 1, 0, 1, 0, IS_JOIN_X1_180)
      BLOCK(0, 1, 0, 1, 1, 1, 1, 1, 0, IS_JOIN_X1_90)
      BLOCK(0, 1, 0, 1, 1, 1, 1, 1, 1, IS_JOIN_X2)
      BLOCK(0, 1, 1, 1, 1, 1, 0, 1, 1, IS_JOIN_X2_270)
      BLOCK(1, 1, 1, 1, 1, 1, 0, 1, 0, IS_JOIN_X2_180)
      BLOCK(1, 1, 0, 1, 1, 1, 1, 1, 0, IS_JOIN_X2_90)
      BLOCK(0, 1, 1, 1, 1, 1, 1, 1, 0, IS_JOIN_X3)
      BLOCK(1, 1, 0, 1, 1, 1, 0, 1, 1, IS_JOIN_X3_180)
      BLOCK(0, 1, 1, 1, 1, 1, 1, 1, 1, IS_JOIN_X4)
      BLOCK(1, 1, 1, 1, 1, 1, 0, 1, 1, IS_JOIN_X4_270)
      BLOCK(1, 1, 1, 1, 1, 1, 1, 1, 0, IS_JOIN_X4_180)
      BLOCK(1, 1, 0, 1, 1, 1, 1, 1, 1, IS_JOIN_X4_90)

      if (block_type == -1) {
        DIE("no block type found for %s", tile_name);
      }

      auto which = std::string(tile_name) + "." + is_join_enum_to_string((is_join_enum) block_type);

      if (tp_is_animated(tp)) {
        which += ".0";
      }

      auto tile = tile_find_mand(which.c_str());
      if (tile) {
        t->tile_index        = tile_global_index(tile);
        t->anim_type         = (ThingAnim) block_type;
        t->anim_index        = pcg_random_range_inclusive(0, tp_tiles_size(tp, t->anim_type) - 1);
        t->anim_ms_remaining = pcg_random_range_inclusive(0, tile_delay_ms(tile));
      }
    }
  }
}

void level_assign_tiles(Gamep g, Levelsp v, Levelp l)
{
  TRACE_NO_INDENT();

  for (auto y = 0; y < MAP_HEIGHT; y++) {
    for (auto x = 0; x < MAP_WIDTH; x++) {
      spoint p(x, y);
      level_assign_tiles_at(g, v, l, p);
    }
  }
}

void level_tile_update_set(Gamep g, Levelsp v, Levelp l, spoint p)
{
  TRACE_NO_INDENT();

  l->tile_update_required = true;

  for (auto dx = -1; dx <= 1; dx++) {
    for (auto dy = -1; dy <= 1; dy++) {
      auto x = p.x + dx;
      auto y = p.y + dy;
      if (! is_oob(x, y)) {
        l->tiles_for_update[ x ][ y ] = true;
      }
    }
  }
}

void level_tile_update(Gamep g, Levelsp v, Levelp l)
{
  TRACE_NO_INDENT();

  if (! l->tile_update_required) {
    return;
  }
  l->tile_update_required = false;

  for (auto y = 0; y < MAP_HEIGHT; y++) {
    for (auto x = 0; x < MAP_WIDTH; x++) {
      if (l->tiles_for_update[ x ][ y ]) {
        level_assign_tiles_at(g, v, l, spoint(x, y));
      }
    }
  }

  memset(l->tiles_for_update, 0, sizeof(l->tiles_for_update));
}
