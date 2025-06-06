//
// Copyright goblinhack@gmail.com
//

#include "my_ascii.hpp"
#include "my_backtrace.hpp"
#include "my_callstack.hpp"
#include "my_console.hpp"
#include "my_log.hpp"
#include "my_sdl_event.hpp"
#include "my_sdl_proto.hpp"
#include "my_string.hpp"
#include "my_wid_botcon.hpp"
#include "my_wid_console.hpp"
#include "my_wid_topcon.hpp"

#include <stdarg.h>
#include <string.h>

void log_(const char *fmt, va_list args)
{
  TRACE_NO_INDENT();

  char buf[ MAXLONGSTR ];
  int  len = 0;

  buf[ 0 ] = '\0';
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
  int  len = 0;

  buf[ 0 ] = '\0';
  get_timestamp(buf, MAXLONGSTR);
  len = (int) strlen(buf);
  vsnprintf(buf + len, MAXLONGSTR - len, fmt, args);

  putf(MY_STDOUT, buf);
  FLUSH_THE_CONSOLE();

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
  int  len = 0;

  buf[ 0 ] = '\0';
  get_timestamp(buf, MAXLONGSTR);
  len = (int) strlen(buf);
  vsnprintf(buf + len, MAXLONGSTR - len, fmt, args);

  putf(MY_STDOUT, buf);

  term_log(buf);
  putchar('\n');

  wid_console_log(buf);

  FLUSH_THE_CONSOLE();
}

void CON(const char *fmt, ...)
{
  TRACE_NO_INDENT();

  va_list args;
  va_start(args, fmt);
  con_(fmt, args);
  va_end(args);
}

static void dying_(const char *fmt, va_list args)
{
  TRACE_NO_INDENT();

  char buf[ MAXLONGSTR ];
  int  len = 0;
  buf[ 0 ] = '\0';
  get_timestamp(buf, MAXLONGSTR);
  len = (int) strlen(buf);
  snprintf(buf + len, MAXLONGSTR - len, "DIE: ");
  len = (int) strlen(buf);
  vsnprintf(buf + len, MAXLONGSTR - len, fmt, args);

  fprintf(stderr, "%s\n", buf);
  putf(MY_STDOUT, buf);

  FLUSH_THE_CONSOLE_FOR_ALL_PLATFORMS();
}

static void err_(const char *fmt, va_list args)
{
  TRACE_NO_INDENT();

  static bool nested_error;
  if (nested_error) {
    return;
  }
  nested_error = true;

  callstack_dump();
  backtrace_dump();

  char error_buf[ MAXLONGSTR ];
  {
    int len;

    error_buf[ 0 ] = '\0';
    len            = (int) strlen(error_buf);
    vsnprintf(error_buf + len, MAXLONGSTR - len, fmt, args);

    error_handler(error_buf);
  }

  {
    char buf[ MAXLONGSTR ];
    int  len = 0;

    buf[ 0 ] = '\0';
    {
      get_timestamp(buf, MAXLONGSTR);
      len = (int) strlen(buf);
    }

    if (snprintf(buf + len, MAXLONGSTR - len, "ERROR: " UI_IMPORTANT_FMT_STR "%s" UI_RESET_FMT "", error_buf) < 0) {
      ERR("truncation");
      return;
    }

    putf(MY_STDERR, buf);
    putf(MY_STDOUT, buf);

    term_log(buf);
    putchar('\n');

    wid_console_log(buf);
  }

  FLUSH_THE_CONSOLE_FOR_ALL_PLATFORMS();
  nested_error = false;
}

static void croak_(const char *fmt, va_list args)
{
  TRACE_NO_INDENT();

  if (g_die_occurred) {
    fprintf(stderr, "\nNESTED FATAL ERROR %s %s %d ", __FILE__, __FUNCTION__, __LINE__);
    exit(1);
  }
  g_die_occurred = true;

  char buf[ MAXLONGSTR ];
  int  len   = 0;
  int  tslen = 0;

  buf[ 0 ] = '\0';
  get_timestamp(buf, MAXLONGSTR);
  tslen = len = (int) strlen(buf);

  snprintf(buf + len, MAXLONGSTR - len, "FATAL ERROR: ");

  len = (int) strlen(buf);
  vsnprintf(buf + len, MAXLONGSTR - len, fmt, args);

  fprintf(stderr, "%s\n", buf);

  ERR("%s", buf + tslen);
  FLUSH_THE_CONSOLE_FOR_ALL_PLATFORMS();

  die();
}

void CROAK(const char *fmt, ...)
{
  TRACE_NO_INDENT();

  va_list args;

  va_start(args, fmt);
  croak_(fmt, args);
  va_end(args);
}

static void croak_clean_(const char *fmt, va_list args)
{
  TRACE_NO_INDENT();

  if (g_die_occurred) {
    fprintf(stderr, "\nNESTED FATAL ERROR %s %s %d ", __FILE__, __FUNCTION__, __LINE__);
    exit(1);
  }
  g_die_occurred = true;

  FLUSH_THE_CONSOLE_FOR_ALL_PLATFORMS();

  die();
}

void CROAK_CLEAN(const char *fmt, ...)
{
  TRACE_NO_INDENT();

  va_list args;

  va_start(args, fmt);
  croak_clean_(fmt, args);
  va_end(args);
}

void DYING(const char *fmt, ...)
{
  TRACE_NO_INDENT();

  va_list args;

  va_start(args, fmt);
  dying_(fmt, args);
  va_end(args);
}

void myerr(const char *fmt, ...)
{
  TRACE_NO_INDENT();

  extern Gamep game;
  auto         g = game;

  static bool nested_error;
  if (nested_error) {
    return;
  }
  bool old_nested_error = nested_error;
  nested_error          = true;

  if (old_nested_error) {
    //
    // Subsequent errors on quitting, avoid error logging
    //
    va_list args;
    va_start(args, fmt);
    log_(fmt, args);
    va_end(args);
  } else {
    g_errored = true;
    va_list args;
    va_start(args, fmt);
    err_(fmt, args);
    va_end(args);
  }

  wid_unset_focus(g);
  wid_unset_focus_lock();

  nested_error = false;

  if (g_quitting) {
    DIE("Error while quitting");
  }
}

static void msgerr_(const char *fmt, va_list args)
{
  TRACE_NO_INDENT();

  char buf[ MAXLONGSTR ];
  int  len = 0;

  callstack_dump();
  backtrace_dump();

  buf[ 0 ] = '\0';
  get_timestamp(buf, MAXLONGSTR);
  len = (int) strlen(buf);
  snprintf(buf + len, MAXLONGSTR - len, "ERROR: " UI_IMPORTANT_FMT_STR);
  len = (int) strlen(buf);
  vsnprintf(buf + len, MAXLONGSTR - len, fmt, args);
  len = (int) strlen(buf);
  snprintf(buf + len, MAXLONGSTR - len, UI_RESET_FMT);

  putf(MY_STDERR, buf);
  putf(MY_STDOUT, buf);

  fprintf(stderr, "%s\n", buf);

  wid_console_log(buf);

  FLUSH_THE_CONSOLE_FOR_ALL_PLATFORMS();
}

void GAME_UI_MSG_BOX(const char *fmt, ...)
{
  TRACE_NO_INDENT();

  va_list args;

  va_start(args, fmt);
  msgerr_(fmt, args);
  va_end(args);
}

static void sdl_msgerr_(const char *fmt, va_list args)
{
  TRACE_NO_INDENT();

  char buf[ MAXLONGSTR ];

  vsnprintf(buf, MAXLONGSTR, fmt, args);

#if SDL_MAJOR_VERSION >= 2
  CON("Show SDL message box");
  //
  // The window is needed else the box appears behind the main window.
  //
  SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "gorget", buf, sdl.window);
  CON("Launched SDL message box");
#endif
}

void SDL_MSG_BOX(const char *fmt, ...)
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
  char ts[ MAXLONGSTR / 2 ];
  int  len = 0;

  buf[ 0 ] = '\0';
  get_timestamp(ts, MAXLONGSTR);
  snprintf(buf, SIZEOF(buf) - 1, "%s", ts);
  len = (int) strlen(buf);
  vsnprintf(buf + len, MAXLONGSTR - len, fmt, args);

  putf(MY_STDOUT, buf);

  term_log(buf);
  putchar('\n');

  wid_topcon_log(buf + len);
  wid_console_log(buf + len);
  FLUSH_THE_CONSOLE();
}

void TOPCON(const char *fmt, ...)
{
  TRACE_NO_INDENT();

  va_list args;

  va_start(args, fmt);
  topcon_(fmt, args);
  va_end(args);
}

static void botcon_(const char *fmt, va_list args)
{
  TRACE_NO_INDENT();

  char buf[ MAXLONGSTR ];

  vsnprintf(buf, MAXLONGSTR, fmt, args);

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
