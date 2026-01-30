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

#include <mutex>
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

static void croak_handle(bool clean, const char *fmt, va_list args)
{
  TRACE_NO_INDENT();

  extern Gamep game;
  auto         g = game;

  if (g_dying) {
    //
    // Could be a different thread also crashing.
    //
    fprintf(stderr, "Nested dying loop, exiting\n");
    exit(1);
  }
  g_dying = true;

  char buf[ MAXLONGSTR * 10 ];
  buf[ 0 ] = '\0';
  int len  = 0;

  get_timestamp(buf, MAXLONGSTR);
  len = (int) strlen(buf);
  if (clean) {
    snprintf(buf + len, MAXLONGSTR - len, "EXITED: ");
  } else {
    snprintf(buf + len, MAXLONGSTR - len, "FATAL ERROR: ");
  }
  len = (int) strlen(buf);
  vsnprintf(buf + len, MAXLONGSTR - len, fmt, args);

  if (clean) {
    fprintf(stderr, "%s\n", buf);
  } else {
    if (MY_STDERR != stderr) {
      fprintf(MY_STDERR, "%s\n", buf);
    }
    error_message(g, buf);
  }
}

void CROAK_HANDLE(bool clean, const char *fmt, ...)
{
  TRACE_NO_INDENT();

  va_list args;

  g_errored_thread_id = g_thread_id;

  va_start(args, fmt);
  croak_handle(clean, fmt, args);
  va_end(args);
}

static void err_handle(Gamep g, const char *fmt, va_list args)
{
  TRACE_NO_INDENT();

  char buf[ MAXLONGSTR * 10 ];
  buf[ 0 ] = '\0';
  int len  = 0;

  get_timestamp(buf, MAXLONGSTR);
  len = (int) strlen(buf);
  snprintf(buf + len, MAXLONGSTR - len, "ERROR: ");
  len = (int) strlen(buf);
  vsnprintf(buf + len, MAXLONGSTR - len, fmt, args);

  error_message(g, buf);
}

void ERR_HANDLE(const char *fmt, ...)
{
  TRACE_NO_INDENT();

  if (g_err_count++ > ENABLE_MAX_ERR_COUNT) {
    CROAK("Too many errors: %d, max %d", g_err_count, ENABLE_MAX_ERR_COUNT);
    exit(1);
  }

  extern Gamep game;
  auto         g      = game;
  g_errored_thread_id = g_thread_id;

  va_list args;
  va_start(args, fmt);
  err_handle(g, fmt, args);
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
