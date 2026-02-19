//
// Copyright goblinhack@gmail.com
//

#ifndef _MY_COLOR_HPP_
#define _MY_COLOR_HPP_

#include "my_types.hpp"

#include <string>

//
// Must be a struct and not a class as we save this structure as is
//
using color = struct color_ {
  unsigned char r;
  unsigned char g;
  unsigned char b;
  unsigned char a;
};

color       color_change_hue(const color &in, float fHue);
color       color_find(const char *s);
color       string2color(const char **s);
color       string2color(std::string &s);
color       string2color(std::string &s, int *len);
std::string string2colorname(std::string &s, int *len);
void        color_fini();
void        color_init1();
void        color_init2();
void        color_init3();
void        color_init4();
void        color_init();
void        color_set(const std::string &name, color *c, uint8_t r, uint8_t g, uint8_t b, uint8_t a);
bool        color_eq(const color &a, const color &b);
bool        color_neq(const color &a, const color &b);

#define glcolor(_c_) glColor4ub((_c_).r, (_c_).g, (_c_).b, (_c_).a)

#endif // _MY_COLOR_HPP_
