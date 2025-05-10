//
// Copyright goblinhack@gmail.com
//

#pragma once
#ifndef _MY_TILE_HPP_
#define _MY_TILE_HPP_

#include "my_color.hpp"
#include "my_minimal.hpp"
#include "my_point.hpp"

class Tile;

#define TILE_HEIGHT     12
#define TILE_WIDTH      12
#define TILE_HEIGHT_MAX TILE_HEIGHT
#define TILE_WIDTH_MAX  TILE_WIDTH // Largest tile for collisions

enum {
  TILE_LAYER_BG_0,
  TILE_LAYER_BG_1,
  TILE_LAYER_FG_0,
  TILE_LAYER_FG_1,
  TILE_LAYER_MAX,
};

class Tex *tile_tex(Tilep);

bool tile_init(void);
void tile_fini(void);

int tile_height(Tilep);
int tile_width(Tilep);

std::string tile_name_get(Tilep);

Tilep string2tile(const char **s, int *len = nullptr);
Tilep string2tile(std::string &s, int *len = nullptr);
Tilep tile_find_mand(std::string name);
Tilep tile_index_to_tile(int i);
Tilep tile_find(std::string name);

uint32_t tile_delay_ms(Tilep);
void     tile_delay_ms_set(Tilep, uint32_t);

uint32_t tile_global_index(Tilep);
void     tile_global_index_set(Tilep, uint32_t);

uint32_t tile_index(Tilep);
uint32_t tile_move(Tilep);

bool tile_is_alive_on_end_of_anim(Tilep);
bool tile_is_dead_on_end_of_anim(Tilep);
bool tile_is_dead(Tilep);
bool tile_is_end_of_anim(Tilep);
bool tile_is_moving(Tilep);
bool tile_is_open(Tilep);
bool tile_is_resurrecting(Tilep);
bool tile_is_sleeping(Tilep);

void tile_blit(const Tilep &tile, const point tl, const point br);
void tile_blit_mask(const Tilep &tile, const point tl, const point br);
void tile_blit(const Tilep &tile, const point tl, const point br, const color &c);
void tile_blit(const Tilep &tile, const point tl, const point tr, const point bl, const point br);
void tile_blit(const Tilep &tile, const point at);
void tile_blit(const class Tp *&tp, const Tilep &tile, const point tl, const point br);
void tile_blit(const class Tp *&tp, uint16_t index, const point tl, const point br);
void tile_blit(uint16_t index, const point tl, const point br);
void tile_blit(uint16_t index, const point at);
void tile_blit_at(const Tilep &tile, const point tl, const point br);
void tile_blit_at(uint16_t index, const point tl, const point br);
void tile_blit_colored(Tilep tile, point tl, point br, color color_tl, color color_tr, color color_bl,
                       color color_br);
void tile_blit_colored_fat(Tilep tile, point tl, point br, color color_tl, color color_tr, color color_bl,
                           color color_br);
void tile_blit_outline(const Tilep &tile, const point tl, const point br, const color &c, int single_pix_size,
                       bool square = false);
void tile_blit_outline(const Tilep &tile, const point tl, const point br, const color &c, const color &o,
                       int single_pix_size, bool square = false);
void tile_blit_outline(uint16_t index, const point tl, const point br, const color &c, int single_pix_size,
                       bool square = false);
void tile_blit_section(const Tilep &tile, const point tile_tl, const point tile_br, const point tl, const point br);
void tile_blit_section(uint16_t index, const point tile_tl, const point tile_br, const point tl, const point br);
void tile_blit_section_colored(const Tilep &tile, const fpoint &tile_tl, const fpoint &tile_br, const point tl,
                               const point br, color color_tl, color color_tr, color color_bl, color color_br);
void tile_blit_section_colored(uint16_t index, const fpoint &tile_tl, const fpoint &tile_br, const point tl,
                               const point br, color color_tl, color color_tr, color color_bl, color color_br);
void tile_blit_shadow(const class Tp *&tp, const Tilep &tile, const point tl, const point br);
void tile_blit_shadow(const class Tp *&tp, uint16_t index, const point tl, const point br);
void tile_blit_shadow_section(const class Tp *&tp, const Tilep &tile, const point tile_tl, const point tile_br,
                              const point tl, const point br);
void tile_blit_shadow_section(const class Tp *&tp, uint16_t index, const point tile_tl, const point tile_br,
                              const point tl, const point br);
void tile_free(Tilep);
void tile_coords(Tilep, float *x1, float *y1, float *x2, float *y2);
void tile_load(const char *, uint32_t width, uint32_t height, uint32_t nargs, ...);
void tile_load_arr(const char *file, const char *tex_name, uint32_t width, uint32_t height, uint32_t nargs,
                   const char *arr[]);
void tile_load_arr_sprites(const char *file, const char *tex_name, uint32_t width, uint32_t height, uint32_t nargs,
                           const char *arr[], int gl_mode);
void tile_blit_frozen(const Tilep &tile, const point tl, const point br);
void tile_blit_burnt(const Tilep &tile, const point tl, const point br);
int  tile_gl_binding(Tilep);

#endif
