//
// Copyright goblinhack@gmail.com
//

#pragma once
#ifndef _MY_LOG_HPP_
#define _MY_LOG_HPP_

#include <stdio.h>

void putf(FILE *fp, const char *s);

#define FLUSH_THE_CONSOLE_FOR_ALL_PLATFORMS()                                                                        \
  fflush(stdout);                                                                                                    \
  fflush(stderr);                                                                                                    \
  fflush(MY_STDOUT);                                                                                                 \
  fflush(MY_STDERR);

#ifdef _WIN32
//
// windows is such utter garbage that if the program crashes it does not flush
// the goddamned console! So we need this...
//
#define FLUSH_THE_CONSOLE() FLUSH_THE_CONSOLE_FOR_ALL_PLATFORMS()
#else
#define FLUSH_THE_CONSOLE() // sensible OS
#endif

#endif
