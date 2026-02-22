//
// Copyright goblinhack@gmail.com
//

#ifndef MY_COLOR_HPP_
#define MY_COLOR_HPP_

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

auto       color_change_hue(const color &in, float fHue) -> color;
auto       color_find(const char *s) -> color;
auto       string2color(const char **s) -> color;
auto       string2color(std::string &s) -> color;
auto       string2color(std::string &s, int *len) -> color;
auto string2colorname(std::string &s, int *len) -> std::string;
void        color_fini();
void        color_init1();
void        color_init2();
void        color_init3();
void        color_init4();
void        color_init();
void        color_set(const std::string &name, color *c, uint8_t r, uint8_t g, uint8_t b, uint8_t a);
auto        color_eq(const color &a, const color &b) -> bool;
auto        color_neq(const color &a, const color &b) -> bool;

#define glcolor(_c_) glColor4ub((_c_).r, (_c_).g, (_c_).b, (_c_).a)

#endif // _MY_COLOR_HPP_
