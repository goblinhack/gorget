//
// Copyright goblinhack@gmail.com
//

#ifndef MY_LOG_HPP
#define MY_LOG_HPP

#include <stdio.h>

auto putf(FILE *fp, const char *s) -> void;
auto log_(const char *fmt, va_list args) -> void;

#endif
