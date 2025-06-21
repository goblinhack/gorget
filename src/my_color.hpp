//
// Copyright goblinhack@gmail.com
//

#pragma once
#ifndef _MY_COLOR_HPP_
#define _MY_COLOR_HPP_

#include "my_types.hpp"

#include <string>

class color
{
public:
  unsigned char r {};
  unsigned char g {};
  unsigned char b {};
  unsigned char a {};

  color(void) = default;

  color(unsigned char vr, unsigned char vg, unsigned char vb, unsigned char va) : r(vr), g(vg), b(vb), a(va) {}

  friend bool operator==(const color &c, const color &in)
  {
    return (c.r == in.r) && (c.g == in.g) && (c.b == in.b) && (c.a == in.a);
  }
};

extern color gl_last_color;
extern color gl_save_color;

color color_change_hue(const color &in, const float fHue);
color color_find(const char *s);
color color_to_mono(color a);
color gl_color_current(void);
color string2color(const char **s);
color string2color(std::string &s);
color string2color(std::string &s, int *len);

const char *string2colorname(const char **s);

std::string string2colorname(std::string &s);

void color_fini(void);
void color_init1(void);
void color_init2(void);
void color_init3(void);
void color_init4(void);
void color_init(void);
void color_set(std::string name, color *c, uint8_t r, uint8_t g, uint8_t b, uint8_t a);
void glcolor_restore(void);
void glcolor_save(void);

#endif // _MY_COLOR_HPP_
