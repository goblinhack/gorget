//
// Copyright goblinhack@gmail.com
//

#pragma once
#ifndef _MY_ASCII_HPP_
#define _MY_ASCII_HPP_

#include "my_tex.hpp"
#include "my_tile.hpp"
#include "my_ui.hpp"

#define TERM_WIDTH_DEF  240
#define TERM_HEIGHT_DEF 120

#define TERM_WIDTH_MIN  120
#define TERM_HEIGHT_MIN 60

#define TERM_WIDTH_MAX  TERM_WIDTH_DEF
#define TERM_HEIGHT_MAX TERM_HEIGHT_DEF

class AsciiCell
{
public:
  char  ch[ TILE_LAYER_MAX ] {};
  Tilep tile[ TILE_LAYER_MAX ] {};

  Texp tex[ TILE_LAYER_MAX ] {};

  float tx[ TILE_LAYER_MAX ] {};
  float ty[ TILE_LAYER_MAX ] {};
  float dx[ TILE_LAYER_MAX ] {};
  float dy[ TILE_LAYER_MAX ] {};

  color color_tl[ TILE_LAYER_MAX ];
  color color_bl[ TILE_LAYER_MAX ];
  color color_tr[ TILE_LAYER_MAX ];
  color color_br[ TILE_LAYER_MAX ];

  //
  // Is reset each frame, and so although a pointer potentially should be
  // zeroed out on game load once it is used.
  //
  void *context {};

  AsciiCell(void) = default;
};

using ascii_key_down_callback   = int (*)(int, int, const struct SDL_Keysym *);
using ascii_mouse_down_callback = int (*)(int, int, int);
using ascii_mouse_over_callback = int (*)(int, int);

typedef std::array< Tilep, TILE_LAYER_MAX > TileLayers;

using button_args = struct {
  int x;
  int y;
  int width;
  int over;

  int sdl_mod;
  int sdl_key;
  int mouse_button;

  color col;

  ascii_key_down_callback   key_down;
  ascii_mouse_down_callback mouse_down;
  ascii_mouse_over_callback mouse_over;

  void *context;
};

using box_args = struct box_args_ {
  int x;
  int y;
  int width;
  int height;
  int over;

  int sdl_mod;
  int sdl_key;
  int mouse_button;

  color col_bg;
  color col_text;

  ascii_key_down_callback   key_down;
  ascii_mouse_down_callback mouse_down;
  ascii_mouse_over_callback mouse_over;

  void *context;
};

bool ascii_is_empty(int x, int y);

color ascii_get_color(int x, int y, int z);

int ascii_ok(int x, int y);
int ascii_ok_for_scissors(int x, int y);
int ascii_strlen(std::string const &);
int ascii_tp_br1_tile(int x, int y, fpoint *);
int ascii_tp_tile_mid(int x, int y, fpoint *);
int ascii_tp_tl1_tile(int x, int y, fpoint *);
int ascii_x_ok(int x);
int ascii_y_ok(int y);

std::string ascii_strip(std::string const &text);

void *ascii_get_stat_context(int x, int y);

void ascii_blit_layer(int z, int no_color);
void ascii_clear_display(void);
void ascii_clear_scissors(void);
void ascii_dim(int x, int y, int z, float alpha);
void ascii_display(Gamep);
void ascii_draw_line(int depth, int x0, int y0, int x1, int y1, char ch, color c);
void ascii_draw_line(int x0, int y0, int x1, int y1, const char *tilename, color c);
void ascii_draw_line(int x0, int y0, int x1, int y1, Tilep what, color c);
void ascii_draw_line(int x0, int y0, int x1, int y1, char what, color c);
void ascii_dump_to_console(FILE *, bool no_color);
void ascii_init(void);
void ascii_put_bg_square(int tlx, int tly, int brx, int bry, const char *tilename, color c);
void ascii_put_bg_square(int tlx, int tly, int brx, int bry, Tilep what, color c);
void ascii_put_bg_square(int tlx, int tly, int brx, int bry, char what, color c);
void ascii_put_box(box_args b, int style, const TileLayers, const char *fmt, ...);
void ascii_putf(int x, int y, color fg, color bg, const std::string fmt, ...);
void ascii_putf__(int x, int y, color fg, color bg, const std::string text);
void ascii_putf(int x, int y, color fg, color bg, const char *fmt, ...);
void ascii_putf(int x, int y, color fg, const std::string fmt, ...);
void ascii_putf(int x, int y, color fg, const char *fmt, ...);
void ascii_putf(int x, int y, const std::string fmt, ...);
void ascii_putf(int x, int y, const char *fmt, ...);
void ascii_set_context(int x, int y, void *context);
void ascii_set(int depth, int x, int y, color c);
void ascii_set(int depth, int x, int y, const char *tilename, const char);
void ascii_set(int depth, int x, int y, const char);
void ascii_set(int depth, int x, int y, Texp, float tx, float ty, float dx, float dy);
void ascii_set(int depth, int x, int y, Tilep);
void ascii_set(int depth, int x, int y, Tilep, const char);
void ascii_set(int depth, int x, int y, Tilep, float tx, float ty, float dx, float dy);
void ascii_set_scissors(spoint tl, spoint br);
void pixel_to_ascii(Gamep, int *x, int *y);

extern float tile_pix_w;
extern float tile_pix_h;

extern int TERM_WIDTH;
extern int TERM_HEIGHT;

extern int ascii_mouse_x;
extern int ascii_mouse_y;

#endif
