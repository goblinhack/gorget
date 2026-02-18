//
// Copyright goblinhack@gmail.com
//

#include "my_ascii.hpp"
#include "my_backtrace.hpp"
#include "my_callstack.hpp"
#include "my_console.hpp"
#include "my_globals.hpp"
#include "my_log.hpp"
#include "my_main.hpp"
#include "my_ptrcheck.hpp"
#include "my_sdl_event.hpp"
#include "my_sdl_proto.hpp"
#include "my_string.hpp"
#include "my_wid_botcon.hpp"
#include "my_wid_console.hpp"
#include "my_wid_topcon.hpp"

#include <mutex>
#include <stdlib.h>
#include <sys/stat.h>

static void sdl_msgerr_(const char *fmt, va_list args)
{
  TRACE_NO_INDENT();

  char buf[ MAXLONGSTR ];
  buf[ 0 ] = '\0';

  vsnprintf(buf, MAXLONGSTR, fmt, args);

#if SDL_MAJOR_VERSION >= 2
  if (__unused__) {
    //
    // Not needed
    //
    SDL_Log("%s", buf);
  }

  //
  // Fullscreen sometimes hides the error, so create a temp window
  //
  LOG("Show SDL message box");

  auto *window = SDL_CreateWindow("gorget error", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 100, 100,
                                 SDL_WINDOW_SHOWN | SDL_WINDOW_ALWAYS_ON_TOP);
  SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Gorget", buf, window);
  LOG("Launched SDL message box");
  SDL_DestroyWindow(window);
#endif

  //
  // We are inside an error already, so do not call ERR
  //
  LOG("SDL: %s", buf);
}

void sdl_msg_box(const char *fmt, ...)
{
  TRACE_NO_INDENT();

  va_list args;

  va_start(args, fmt);
  sdl_msgerr_(fmt, args);
  va_end(args);
}
