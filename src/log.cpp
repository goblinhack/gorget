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
#include "my_string.hpp"
#include "my_wid_botcon.hpp"
#include "my_wid_console.hpp"
#include "my_wid_topcon.hpp"

#include <stdlib.h>
#include <sys/stat.h>

//
// Where all logs go
//
std::string log_dir_create(void)
{
  TRACE_NO_INDENT();

  const char *appdata;
  appdata = getenv("APPDATA");
  if (! appdata || ! appdata[ 0 ]) {
    appdata = "appdata";
  }

#ifdef _WIN32
  mkdir(appdata);
#else
  mkdir(appdata, 0700);
#endif

  char *dir = dynprintf("%s%s%s", appdata, DIR_SEP, "gorget");
#ifdef _WIN32
  mkdir(dir);
#else
  mkdir(dir, 0700);
#endif
  myfree(dir);

  return std::string(appdata);
}

void log_(const char *fmt, va_list args)
{
  TRACE_NO_INDENT();

  if (MY_STDOUT == stdout) {
    return;
  }

  char buf[ MAXLONGSTR ];
  buf[ 0 ] = '\0';
  int len  = 0;

  get_timestamp(buf, MAXLONGSTR);
  len = (int) strlen(buf);
  snprintf(buf + len, MAXLONGSTR - len, "%s%*s", "", g_callframes_indent, "");

  len = (int) strlen(buf);
  vsnprintf(buf + len, MAXLONGSTR - len, fmt, args);

  putf(MY_STDOUT, buf);
}

void LOG(const char *fmt, ...)
{
  TRACE_NO_INDENT();

  va_list args;
  va_start(args, fmt);
  log_(fmt, args);
  va_end(args);
}

static void warn_(const char *fmt, va_list args)
{
  TRACE_NO_INDENT();

  char buf[ MAXLONGSTR ];
  buf[ 0 ] = '\0';
  int len  = 0;

  get_timestamp(buf, MAXLONGSTR);
  len = (int) strlen(buf);
  vsnprintf(buf + len, MAXLONGSTR - len, fmt, args);

  putf(MY_STDOUT, buf);

  wid_console_log(buf);
}

void WARN(const char *fmt, ...)
{
  TRACE_NO_INDENT();

  va_list args;

  va_start(args, fmt);
  warn_(fmt, args);
  va_end(args);
}

static void con_(const char *fmt, va_list args)
{
  TRACE_NO_INDENT();

  char buf[ MAXLONGSTR ];
  buf[ 0 ] = '\0';
  int len  = 0;

  get_timestamp(buf, MAXLONGSTR);
  len = (int) strlen(buf);
  if (fmt) {
    vsnprintf(buf + len, MAXLONGSTR - len, fmt, args);
  }

  putf(MY_STDOUT, buf);

  if (! g_opt_tests) {
    term_log(buf);
    putchar('\n');
  }

  wid_console_log(buf);
}

void CON(const char *fmt, ...)
{
  TRACE_NO_INDENT();

  va_list args;
  va_start(args, fmt);
  con_(fmt, args);
  va_end(args);
}

void CON_NEW_LINE(void)
{
  TRACE_NO_INDENT();

  va_list args = {};
  con_(nullptr, args);
}

static void cleanup_err_wrapper_(const char *fmt, va_list args)
{
  TRACE_NO_INDENT();

  callstack_dump();
  backtrace_dump();

  char buf[ MAXLONGSTR ];
  buf[ 0 ]  = '\0';
  int len   = 0;
  int tslen = 0;

  get_timestamp(buf, MAXLONGSTR);
  tslen = len = (int) strlen(buf);

  snprintf(buf + len, MAXLONGSTR - len, "FATAL ERROR: ");

  len = (int) strlen(buf);
  vsnprintf(buf + len, MAXLONGSTR - len, fmt, args);

  fprintf(stderr, "%s\n", buf);
  fprintf(MY_STDERR, "%s\n", buf);

  CON("%s", buf + tslen);

  if (g_thread_id == -1) {
    cleanup();
  } else {
    //
    // Better to exit than cleanup, as we could crash in cleanup
    //
    exit(1);
  }
}

void CLEANUP_ERR(const char *fmt, ...)
{
  TRACE_NO_INDENT();

  va_list args;

  va_start(args, fmt);
  cleanup_err_wrapper_(fmt, args);
  va_end(args);
}

static void cleanup_ok_wrapper_(const char *fmt, va_list args)
{
  TRACE_NO_INDENT();

  cleanup();
}

void CLEANUP_OK(const char *fmt, ...)
{
  TRACE_NO_INDENT();

  va_list args;

  va_start(args, fmt);
  cleanup_ok_wrapper_(fmt, args);
  va_end(args);
}

static void dying_(bool clean, const char *fmt, va_list args)
{
  TRACE_NO_INDENT();

  if (g_dying) {
    //
    // Could be a different thread also crashing.
    //
    exit(1);
    return;
  }
  g_dying = true;

  if (! clean) {
    callstack_dump_stderr();
    backtrace_dump_stderr();

    callstack_dump();
    backtrace_dump();
  }

  char buf[ MAXLONGSTR * 10 ];
  buf[ 0 ] = '\0';
  int len  = 0;

  get_timestamp(buf, MAXLONGSTR);
  len = (int) strlen(buf);
  snprintf(buf + len, MAXLONGSTR - len, "DIE: ");
  len = (int) strlen(buf);
  vsnprintf(buf + len, MAXLONGSTR - len, fmt, args);

  fprintf(stderr, "%s\n", buf);
  if (MY_STDERR != stderr) {
    fprintf(MY_STDERR, "%s\n", buf);
  }

#ifdef _WIN32
  //
  // windows is such utter garbage that if the program crashes it does not flush
  // the goddamned console! So we need this...
  //
  fflush(stdout);
  fflush(stderr);
  fflush(MY_STDOUT);
  fflush(MY_STDERR);
#endif
}

void DYING(bool clean, const char *fmt, ...)
{
  TRACE_NO_INDENT();

  va_list args;

  va_start(args, fmt);
  dying_(clean, fmt, args);
  va_end(args);
}

static void err_(const char *fmt, va_list args)
{
  TRACE_NO_INDENT();

  callstack_dump();
  backtrace_dump();

  char error_buf[ MAXLONGSTR ];
  {
    int len;

    error_buf[ 0 ] = '\0';
    len            = (int) strlen(error_buf);
    vsnprintf(error_buf + len, MAXLONGSTR - len, fmt, args);
  }

  {
    char buf[ MAXLONGSTR ];
    buf[ 0 ] = '\0';
    int len  = 0;

    {
      get_timestamp(buf, MAXLONGSTR);
      len = (int) strlen(buf);
    }

    if (snprintf(buf + len, MAXLONGSTR - len, "ERROR: " UI_IMPORTANT_FMT_STR "%s" UI_RESET_FMT "", error_buf) < 0) {
      ERR("truncation");
      return;
    }

    if (MY_STDERR != stderr) {
      putf(MY_STDERR, buf);
    }

    if (MY_STDERR != stdout) {
      putf(MY_STDOUT, buf);
    }

    term_log(buf);
    putchar('\n');

    wid_console_log(buf);
  }

  if (! g_opt_tests) {
    error_handler(error_buf);
  }
}

void err_wrapper(const char *fmt, ...)
{
  TRACE_NO_INDENT();

  extern Gamep game;
  auto         g = game;

  g_errored = true;
  va_list args;
  va_start(args, fmt);
  err_(fmt, args);
  va_end(args);

  wid_unset_focus(g);
  wid_unset_focus_lock();
  wid_console_raise(g);

  if (g_quitting) {
    DIE("Error while quitting");
  }
}

static void sdl_msgerr_(const char *fmt, va_list args)
{
  TRACE_NO_INDENT();

  char buf[ MAXLONGSTR ];
  buf[ 0 ] = '\0';

  vsnprintf(buf, MAXLONGSTR, fmt, args);

#if SDL_MAJOR_VERSION >= 2
  SDL_Log("%s", buf);

  //
  // Fullscreen sometimes hides the error, so create a temp window
  //
  LOG("Show SDL message box");

  auto window
      = SDL_CreateWindow("gorget error", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1, 1, SDL_WINDOW_SHOWN);
  SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "gorget", buf, window);
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

void putf(FILE *fp, const char *s)
{
  auto sp = s;
  while (*sp) {
    if (*sp == '%') {
      std::string out = ascii_strip(s);
      fputs(out.c_str(), fp);
      putc('\n', fp);
      return;
    }
    sp++;
  }

  fputs(s, fp);
  putc('\n', fp);
}

static void topcon_(const char *fmt, va_list args)
{
  TRACE_NO_INDENT();

  char buf[ MAXLONGSTR ];
  buf[ 0 ] = '\0';
  char ts[ MAXLONGSTR / 2 ];
  int  len = 0;

  get_timestamp(ts, MAXLONGSTR);
  snprintf(buf, SIZEOF(buf) - 1, "%s", ts);
  len = (int) strlen(buf);
  if (fmt) {
    vsnprintf(buf + len, MAXLONGSTR - len, fmt, args);
  }

  putf(MY_STDOUT, buf);

  if (! g_opt_tests) {
    term_log(buf);
    putchar('\n');
  }

  wid_topcon_log(buf + len);
  wid_console_log(buf + len);
}

void TOPCON(const char *fmt, ...)
{
  TRACE_NO_INDENT();

  va_list args;

  va_start(args, fmt);
  topcon_(fmt, args);
  va_end(args);
}

void TOPCON_NEW_LINE(void)
{
  TRACE_NO_INDENT();

  va_list args = {};
  topcon_(nullptr, args);
}

static void botcon_(const char *fmt, va_list args)
{
  TRACE_NO_INDENT();

  char buf[ MAXLONGSTR ];
  buf[ 0 ] = '\0';

  if (fmt) {
    vsnprintf(buf, MAXLONGSTR, fmt, args);
  }

  wid_botcon_log(buf);
}

void BOTCON(const char *fmt, ...)
{
  TRACE_NO_INDENT();

  va_list args;

  va_start(args, fmt);
  botcon_(fmt, args);
  va_end(args);
}

void BOTCON_NEW_LINE(void)
{
  TRACE_NO_INDENT();

  va_list args = {};

  botcon_(nullptr, args);
}
