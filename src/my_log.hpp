//
// Copyright goblinhack@gmail.com
//

#ifndef MY_LOG_HPP
#define MY_LOG_HPP

#include <stdio.h>

void putf(FILE *fp, const char *s);
void log_(const char *fmt, va_list args);

#endif
