//
// Copyright goblinhack@gmail.com
//

#pragma once
#ifndef _MY_COLOR_HPP_
#define _MY_COLOR_HPP_

#include "my_types.hpp"

#include <string>

typedef struct color {
  unsigned char r;
  unsigned char g;
  unsigned char b;
  unsigned char a;
} color;

color color_change_hue(const color &in, const float fHue);
color color_find(const char *s);
color string2color(const char **s);
color string2color(std::string &s);
color string2color(std::string &s, int *len);
void  color_fini(void);
void  color_init1(void);
void  color_init2(void);
void  color_init3(void);
void  color_init4(void);
void  color_init(void);
void  color_set(std::string name, color *c, uint8_t r, uint8_t g, uint8_t b, uint8_t a);
bool  color_eq(const color &a, const color &b);
bool  color_neq(const color &a, const color &b);

#define glcolor(_c_) glColor4ub(_c_.r, _c_.g, _c_.b, _c_.a)

#endif // _MY_COLOR_HPP_
