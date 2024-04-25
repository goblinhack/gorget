//
// Copyright Neil McGill, goblinhack@gmail.com
//

#pragma once
#ifndef _MY_TILE_HPP_
#define _MY_TILE_HPP_

#include <vector>

#include "my_gl.hpp"
#include "my_minimal.hpp"

class Tile;
using Tilevec = std::vector< class Tile * >;

#define TILE_VARIANTS   6
#define TILE_HEIGHT     16
#define TILE_WIDTH      16
#define TILE_HEIGHT_MAX 64
#define TILE_WIDTH_MAX  64 // Largest tile for collisions

class Tex *tile_tex(Tilep);

int tile_height(Tilep);
int tile_width(Tilep);
int tile_n(Tilevec *tmap, Tile *p);

std::string tile_name_get(Tilep);

Tilep string2tile(const char **s);
Tilep string2tile(std::string &s, int *len);
Tilep string2tile(std::string &s, int *len);
Tilep tile_find_mand(std::string name);
Tilep tile_first(Tilevec *root);
Tilep tile_from_surface(struct SDL_Surface *surface, std::string optional_file, std::string name);
Tilep tile_index_to_tile(uint16_t i);
Tilep tile_next(Tilevec *root, Tilep in);
Tilep tile_n(Tilevec *root, int n);
Tilep tile_random(Tilevec *root);
Tilep tile_find(std::string name);
Tilep tile_frame(Tilevec *tmap, uint32_t frame);

uint32_t tile_delay_ms(Tilep);
void     tile_delay_ms_set(Tilep, uint32_t);

uint32_t tile_global_index(Tilep);
void     tile_global_index_set(Tilep, uint32_t);

uint32_t tile_frame(Tilep);
uint32_t tile_index(Tilep);
uint32_t tile_move(Tilep);

uint8_t gfx_outline_index_offset(Tilep);
uint8_t tile_init(void);
uint8_t tile_is_alive_on_end_of_anim(Tilep);
uint8_t tile_is_dead_on_end_of_anim(Tilep);
uint8_t tile_is_dead(Tilep);
uint8_t tile_is_dir_bl(Tilep);
uint8_t tile_is_dir_br(Tilep);
uint8_t tile_is_dir_down(Tilep);
uint8_t tile_is_dir_left(Tilep);
uint8_t tile_is_dir_none(Tilep);
uint8_t tile_is_dir_right(Tilep);
uint8_t tile_is_dir_tl(Tilep);
uint8_t tile_is_dir_tr(Tilep);
uint8_t tile_is_dir_up(Tilep);
uint8_t tile_is_end_of_anim(Tilep);
uint8_t tile_is_invisible(Tilep);
uint8_t tile_is_moving(Tilep);
uint8_t tile_is_open(Tilep);
uint8_t tile_is_resurrecting(Tilep);
uint8_t tile_is_sleeping(Tilep);

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
void tile_blit_outline(const Tilep &tile, const point tl, const point br, const color &c, bool square = false);
void tile_blit_outline(const Tilep &tile, const point tl, const point br, const color &c, const color &o,
                       bool square = false);
void tile_blit_outline(uint16_t index, const point tl, const point br, const color &c, bool square = false);
void tile_blit_outline_section(const Tilep &tile, const point tile_tl, const point tile_br, const point tl,
                               const point br);
void tile_blit_outline_section(uint16_t index, const point tile_tl, const point tile_br, const point tl,
                               const point br);
void tile_blit_outline_section_colored(const Tilep &tile, const fpoint &tile_tl, const fpoint &tile_br,
                                       const point tl, const point br, color color_bl, color color_br, color color_tl,
                                       color color_tr);
void tile_blit_outline_section_colored(const Tilep &tile, const fpoint &tile_tl, const fpoint &tile_br,
                                       const point tl, const point br, color color_bl, color color_br, color color_tl,
                                       color color_tr, float scale);
void tile_blit_outline_section_colored(uint16_t index, const fpoint &tile_tl, const fpoint &tile_br, const point tl,
                                       const point br, color color_bl, color color_br, color color_tl,
                                       color color_tr);
void tile_blit_outline_section_colored(uint16_t index, const fpoint &tile_tl, const fpoint &tile_br, const point tl,
                                       const point br, color color_bl, color color_br, color color_tl, color color_tr,
                                       float scale);
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
void tile_fini(void);
void tile_free(Tilep);
void tile_coords(Tilep, float *x1, float *y1, float *x2, float *y2);
void tile_load(std::string file, uint32_t width, uint32_t height, uint32_t nargs, ...);
void tile_load_arr(std::string file, std::string tex_name, uint32_t width, uint32_t height,
                   const std::vector< std::string > &arr);
void tile_load_arr(std::string file, std::string tex_name, uint32_t width, uint32_t height, uint32_t nargs,
                   const char *arr[]);
void tile_load_arr_sprites(std::string file, std::string name, uint32_t width, uint32_t height,
                           const std::vector< std::string > &arr, int gl_mode = GL_NEAREST);
void tile_load_arr_sprites(std::string file, std::string tex_name, uint32_t width, uint32_t height, uint32_t nargs,
                           const char *arr[], int gl_mode = GL_NEAREST);
void tile_blit_frozen(const Tilep &tile, const point tl, const point br);
void tile_blit_burnt(const Tilep &tile, const point tl, const point br);
void tile_blit_outline_only(const Tilep &tile, const point tl, const point br, color c);

#endif
