//
// Copyright goblinhack@gmail.com
//

#ifndef MY_TERM_HPP_
#define MY_TERM_HPP_

#include "my_color.hpp"

using term_color = enum term_color_ {
  TERM_COLOR_BLACK,
  TERM_COLOR_RED,
  TERM_COLOR_GREEN,
  TERM_COLOR_YELLOW,
  TERM_COLOR_BLUE,
  TERM_COLOR_PINK,
  TERM_COLOR_CYAN,
  TERM_COLOR_WHITE,
  TERM_COLOR_RESET,
  TERM_COLOR_MAX,
};

extern auto term_color_to_console_color(color c) -> int;
extern void term_log(const char *s);

#endif
