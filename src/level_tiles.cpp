//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_bits.hpp"
#include "my_enum.hpp"
#include "my_enums.hpp"
#include "my_level.hpp"
#include "my_template.hpp"
#include "my_tp.hpp"

/* clang-format off */
#define IS_JOIN_ENUM(list_macro)                  \
    list_macro(IS_JOIN_BLOCK,  "IS_JOIN_BLOCK"),  \
    list_macro(IS_JOIN_HORIZ,  "IS_JOIN_HORIZ"),  \
    list_macro(IS_JOIN_VERT,   "IS_JOIN_VERT"),   \
    list_macro(IS_JOIN_NODE,   "IS_JOIN_NODE"),   \
    list_macro(IS_JOIN_LEFT,   "IS_JOIN_LEFT"),   \
    list_macro(IS_JOIN_RIGHT,  "IS_JOIN_RIGHT"),  \
    list_macro(IS_JOIN_TOP,    "IS_JOIN_TOP"),    \
    list_macro(IS_JOIN_BOT,    "IS_JOIN_BOT"),    \
    list_macro(IS_JOIN_TL,     "IS_JOIN_TL"),     \
    list_macro(IS_JOIN_TR,     "IS_JOIN_TR"),     \
    list_macro(IS_JOIN_BL,     "IS_JOIN_BL"),     \
    list_macro(IS_JOIN_BR,     "IS_JOIN_BR"),     \
    list_macro(IS_JOIN_T,      "IS_JOIN_T"),      \
    list_macro(IS_JOIN_T90,    "IS_JOIN_T90"),    \
    list_macro(IS_JOIN_T180,   "IS_JOIN_T180"),   \
    list_macro(IS_JOIN_T270,   "IS_JOIN_T270"),   \
    list_macro(IS_JOIN_X,      "IS_JOIN_X"),      \
    list_macro(IS_JOIN_TL2,    "IS_JOIN_TL2"),    \
    list_macro(IS_JOIN_TR2,    "IS_JOIN_TR2"),    \
    list_macro(IS_JOIN_BL2,    "IS_JOIN_BL2"),    \
    list_macro(IS_JOIN_BR2,    "IS_JOIN_BR2"),    \
    list_macro(IS_JOIN_T_1,    "IS_JOIN_T_1"),    \
    list_macro(IS_JOIN_T_2,    "IS_JOIN_T_2"),    \
    list_macro(IS_JOIN_T_3,    "IS_JOIN_T_3"),    \
    list_macro(IS_JOIN_T90_1,  "IS_JOIN_T90_1"),  \
    list_macro(IS_JOIN_T90_2,  "IS_JOIN_T90_2"),  \
    list_macro(IS_JOIN_T90_3,  "IS_JOIN_T90_3"),  \
    list_macro(IS_JOIN_T180_1, "IS_JOIN_T180_1"), \
    list_macro(IS_JOIN_T180_2, "IS_JOIN_T180_2"), \
    list_macro(IS_JOIN_T180_3, "IS_JOIN_T180_3"), \
    list_macro(IS_JOIN_T270_1, "IS_JOIN_T270_1"), \
    list_macro(IS_JOIN_T270_2, "IS_JOIN_T270_2"), \
    list_macro(IS_JOIN_T270_3, "IS_JOIN_T270_3"), \
    list_macro(IS_JOIN_X1,     "IS_JOIN_X1"),     \
    list_macro(IS_JOIN_X1_270, "IS_JOIN_X1_270"), \
    list_macro(IS_JOIN_X1_180, "IS_JOIN_X1_180"), \
    list_macro(IS_JOIN_X1_90,  "IS_JOIN_X1_90"),  \
    list_macro(IS_JOIN_X2,     "IS_JOIN_X2"),     \
    list_macro(IS_JOIN_X2_270, "IS_JOIN_X2_270"), \
    list_macro(IS_JOIN_X2_180, "IS_JOIN_X2_180"), \
    list_macro(IS_JOIN_X2_90,  "IS_JOIN_X2_90"),  \
    list_macro(IS_JOIN_X3,     "IS_JOIN_X3"),     \
    list_macro(IS_JOIN_X3_180, "IS_JOIN_X3_180"), \
    list_macro(IS_JOIN_X4,     "IS_JOIN_X4"),     \
    list_macro(IS_JOIN_X4_270, "IS_JOIN_X4_270"), \
    list_macro(IS_JOIN_X4_180, "IS_JOIN_X4_180"), \
    list_macro(IS_JOIN_X4_90,  "IS_JOIN_X4_90"),  \
    list_macro(IS_JOIN_VERT2,  "IS_JOIN_VERT2"),  \
    list_macro(IS_JOIN_HORIZ2, "IS_JOIN_HORIZ2"), \
    list_macro(IS_JOIN_MAX,    "IS_JOIN_MAX")

/* clang-format on */

ENUM_DEF_H(IS_JOIN_ENUM, is_join_enum)
ENUM_DEF_C(IS_JOIN_ENUM, is_join_enum)

void Level::assign_tiles(void)
{
  TRACE_NO_INDENT();

  for (auto slot = 0; slot < MAP_SLOTS; slot++) {
    for (auto y = 0; y < MAP_HEIGHT; y++) {
      for (auto x = 0; x < MAP_WIDTH; x++) {
        point p(x, y);
        auto  tp = tp_get(p, slot);
        if (! tp) {
          continue;
        }

        if (! tp->tiles.size()) {
          continue;
        }

        if (tp->is_blit_tiled) {
          auto tile_name = tp->name;

          uint16_t A = is_same_type(point(x - 1, y - 1), tp) ? 1 : 0;
          uint16_t B = is_same_type(point(x, y - 1), tp) ? 1 : 0;
          uint16_t C = is_same_type(point(x + 1, y - 1), tp) ? 1 : 0;
          uint16_t D = is_same_type(point(x - 1, y), tp) ? 1 : 0;
          uint16_t E = is_same_type(point(x, y), tp) ? 1 : 0;
          uint16_t F = is_same_type(point(x + 1, y), tp) ? 1 : 0;
          uint16_t G = is_same_type(point(x - 1, y + 1), tp) ? 1 : 0;
          uint16_t H = is_same_type(point(x, y + 1), tp) ? 1 : 0;
          uint16_t I = is_same_type(point(x + 1, y + 1), tp) ? 1 : 0;

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
            DIE("no block type found for %s", tile_name.c_str());
          }

          auto which = tile_name + "." + is_join_enum_val2str((is_join_enum) block_type);
          auto tile  = tile_find_mand(which);
          set_tile(p, slot, tile);

          data->obj[ x ][ y ][ slot ].anim_index        = pcg_random_range_inclusive(0, tp->tiles.size() - 1);
          data->obj[ x ][ y ][ slot ].anim_ms_remaining = pcg_random_range_inclusive(0, tile->delay_ms);
        } else {
          auto tile = one_of(tp->tiles);
          if (tile) {
            set_tile(p, slot, tile);
            auto i                                 = pcg_random_range_inclusive(0, tp->tiles.size() - 1);
            data->obj[ x ][ y ][ slot ].anim_index = i;
          }
        }
      }
    }
  }
}
