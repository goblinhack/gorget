//
// Copyright goblinhack@gmail.com
//

#pragma once
#ifndef _MY_TEX_HPP_
#define MY_TEX_HPP_

#include "my_gl.hpp"
#include "my_types.hpp"

#include <SDL.h>
#include <string>

int tex_get_gl_binding(Texp /*tex*/);

SDL_Surface *tex_get_surface(Texp /*tex*/);

Texp string2tex(const char **s);
Texp string2tex(std::string &s, int *len);
Texp tex_find(std::string name);
Texp tex_from_surface(SDL_Surface *surface, std::string file, std::string name, int mode);
Texp tex_load(std::string file, std::string name, int mode);
Texp tex_from_fbo(Gamep g, FboEnum fbo);

uint32_t tex_get_height(Texp /*tex*/);
uint32_t tex_get_width(Texp /*tex*/);

bool tex_init(void);

void tex_fini(void);
void tex_free(Texp tex);
void tex_load_sprites(Texp *tex, Texp *tex_monochrome, Texp *tex_mask, Texp *tex_outline, std::string file,
                      std::string name, uint32_t tile_width, uint32_t tile_height, int mode);

#endif
