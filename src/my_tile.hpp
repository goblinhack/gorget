//
// Copyright goblinhack@gmail.com
//

#pragma once
#ifndef _MY_TILE_HPP_
#define _MY_TILE_HPP_

#include "my_color.hpp"
#include "my_enum.hpp"
#include "my_fpoint.hpp"
#include "my_gl.hpp"
#include "my_spoint.hpp"
#include "my_types.hpp"

class Tile;

//
// This is the actual tile sizw
//
#define INNER_TILE_HEIGHT 12
#define INNER_TILE_WIDTH  12

//
// This is the tile size with outline padding. Only the actual tile size is used in game.
//
#define OUTER_TILE_HEIGHT (INNER_TILE_WIDTH + 2)
#define OUTER_TILE_WIDTH  (INNER_TILE_HEIGHT + 2)

#define TILE_HEIGHT_MAX OUTER_TILE_HEIGHT
#define TILE_WIDTH_MAX  OUTER_TILE_WIDTH // Largest tile for collisions

//
// Frame buffer objects
//
#define TILE_LAYER_ENUM(list_macro)                                                                                  \
  clang_format_indent()                               /* dummy line for clang indentation fixup */                   \
      list_macro(TILE_LAYER_BG_0, "TILE_LAYER_BG_0"), /* newline */                                                  \
      list_macro(TILE_LAYER_BG_1, "TILE_LAYER_BG_1"), /* newline */                                                  \
      list_macro(TILE_LAYER_FG_0, "TILE_LAYER_FG_0"), /* newline */                                                  \
      list_macro(TILE_LAYER_FG_1, "TILE_LAYER_FG_1"), /* newline */

ENUM_DEF_H(TILE_LAYER_ENUM, TileLayerEnum);

class Tex *tile_tex(Tilep);

bool        tile_init(void);
bool        tile_is_alive_on_end_of_anim(Tilep);
bool        tile_is_cleanup_on_end_of_anim(Tilep);
bool        tile_is_dead(Tilep);
bool        tile_is_end_of_anim(Tilep);
bool        tile_is_loggable(Tilep);
bool        tile_is_open(Tilep);
int         tile_height(Tilep);
int         tile_width(Tilep);
int         tile_gl_binding(Tilep);
std::string tile_name_get(Tilep);
Tilep       string2tile(const char **s, int *len = nullptr);
Tilep       string2tile(std::string &s, int *len = nullptr);
Tilep       tile_find_mand(std::string name);
Tilep       tile_find(std::string name);
Tilep       tile_index_to_tile(int i);
uint32_t    tile_delay_ms(Tilep);
uint32_t    tile_global_index(Tilep);
uint32_t    tile_index(Tilep);
uint32_t    tile_move(Tilep);
void        tile_coords(Tilep, float *x1, float *y1, float *x2, float *y2);
void        tile_delay_ms_set(Tilep, uint32_t);
void        tile_fini(void);
void        tile_free(Tilep);
void        tile_global_index_set(Tilep, uint32_t);
void        tile_is_alive_on_end_of_anim_set(Tilep);
void        tile_is_cleanup_on_end_of_anim_set(Tilep);
void        tile_load(const char *, uint32_t width, uint32_t height, uint32_t nargs, ...);
void        tile_from_fbo(Gamep, FboEnum);

void tile_load_arr(const char *file, const char *tex_name, uint32_t w, uint32_t h, uint32_t nargs, const char *arr[]);
void tile_submerge_pct(Gamep, spoint &tl, spoint &br, float &x1, float &x2, float &y1, float &y2, float percent);
void tile_load_arr_sprites(const char *file, const char *tex, uint32_t w, uint32_t h, uint32_t nargs,
                           const char *arr[], int gl_mode = GL_NEAREST);

void tile_blit(const Tilep &tile, const spoint tl, const spoint br, const color &c);
void tile_blit(const Tilep &tile, float x1, float x2, float y1, float y2, const spoint tl, const spoint br,
               const color &c);
void tile_blit(const Tilep &tile, spoint tl, spoint br, color color_tl, color color_tr, color color_bl,
               color color_br);
void tile_blit_section(const Tilep &tile, const fpoint &tile_tl, const fpoint &tile_br, const spoint tl,
                       const spoint br, const color &color_tl, const color &color_tr, const color &color_bl,
                       const color &color_br);
void tile_blit_outline(const Tilep &tile, float x1, float x2, float y1, float y2, const spoint tl, const spoint br,
                       const color &c, const color &outline, int single_pix_size, bool square);

#endif
