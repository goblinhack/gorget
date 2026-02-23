//
// Copyright goblinhack@gmail.com
//

#ifndef MY_COLOR_HPP
#define MY_COLOR_HPP

#include "my_types.hpp"

#include <string>

//
// Must be a struct and not a class as we save this structure as is
//
using color = struct Color {
  unsigned char r;
  unsigned char g;
  unsigned char b;
  unsigned char a;
};

auto color_change_hue(const color &in, float fHue) -> color;
auto color_find(const char *s) -> color;
auto string2color(const char **s) -> color;
auto string2color(std::string &s) -> color;
auto string2color(std::string &s, int *len) -> color;
auto string2colorname(std::string &s, int *len) -> std::string;
void color_fini();
void color_init1();
void color_init2();
void color_init3();
void color_init4();
void color_init();
void color_set(const std::string &name, color *c, uint8_t r, uint8_t g, uint8_t b, uint8_t a);
auto color_eq(const color &col1, const color &col2) -> bool;
auto color_neq(const color &col1, const color &col2) -> bool;

#define GLCOLOR(_c_) glColor4ub((_c_).r, (_c_).g, (_c_).b, (_c_).a)

#endif // MY_COLOR_HPP
