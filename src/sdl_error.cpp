//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_main.hpp"
#include "my_string.hpp"

#include <SDL_log.h>
#include <SDL_messagebox.h>
#include <SDL_version.h>
#include <SDL_video.h>
#include <cmath>
#include <cstdarg>
#include <cstdio>
#include <cstdlib>

static void sdl_msgerr_(const char *fmt, va_list args)
{
  TRACE();

  char buf[ MAXLONGSTR ];
  buf[ 0 ] = '\0';

  vsnprintf(buf, MAXLONGSTR, fmt, args);

#if SDL_MAJOR_VERSION >= 2
  if (compiler_unused) {
    //
    // Not needed
    //
    SDL_Log("%s", buf);
  }

  //
  // Fullscreen sometimes hides the error, so create a temp window
  //
  log("show SDL message box");

  auto *window = SDL_CreateWindow("sacrecant error", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 100, 100,
                                  SDL_WINDOW_SHOWN | SDL_WINDOW_ALWAYS_ON_TOP);
  SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Sacrecant", buf, window);
  log("launched SDL message box");
  SDL_DestroyWindow(window);
#endif

  //
  // We are inside an error already, so do not call ERR
  //
  log("SDL: %s", buf);
}

void sdl_msg_box(const char *fmt, ...)
{
  TRACE();

  va_list args = {};

  va_start(args, fmt);
  sdl_msgerr_(fmt, args);
  va_end(args);
}
