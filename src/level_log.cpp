//
// Copyright goblinhack@gmail.com
//

#include "my_backtrace.hpp"
#include "my_callstack.hpp"
#include "my_console.hpp"
#include "my_globals.hpp"
#include "my_level.hpp"
#include "my_log.hpp"
#include "my_main.hpp"
#include "my_string.hpp"
#include "my_wid_botcon.hpp"
#include "my_wid_console.hpp"
#include "my_wid_topcon.hpp"

#include <string.h>

static void level_log_(Levelp l, const char *fmt, va_list args)
{
  TRACE_NO_INDENT();

  char buf[ MAXLONGSTR ];
  int  len = 0;

  buf[ 0 ] = '\0';
  get_timestamp(buf, MAXLONGSTR);
  len = (int) strlen(buf);
  snprintf(buf + len, MAXLONGSTR - len, "%s: ", to_string(nullptr, l).c_str());
  len = (int) strlen(buf);
  vsnprintf(buf + len, MAXLONGSTR - len, fmt, args);

  putf(MY_STDOUT, buf);
}

void LEVEL_LOG(Levelp l, const char *fmt, ...)
{
  TRACE_NO_INDENT();

  va_list args;
  va_start(args, fmt);
  level_log_(l, fmt, args);
  va_end(args);
}

void LEVEL_DBG(Levelp l, const char *fmt, ...)
{
  TRACE_NO_INDENT();

  IF_NODEBUG return;

  va_list args;
  va_start(args, fmt);
  level_log_(l, fmt, args);
  va_end(args);
}

static void level_warn_(Levelp l, const char *fmt, va_list args)
{
  TRACE_NO_INDENT();

  char buf[ MAXLONGSTR ];
  int  len = 0;

  buf[ 0 ] = '\0';
  get_timestamp(buf, MAXLONGSTR);
  len = (int) strlen(buf);
  snprintf(buf + len, MAXLONGSTR - len, "%s: ", to_string(nullptr, l).c_str());
  len = (int) strlen(buf);
  vsnprintf(buf + len, MAXLONGSTR - len, fmt, args);

  putf(MY_STDOUT, buf);
  wid_console_log(buf);
}

void LEVEL_WARN(Levelp l, const char *fmt, ...)
{
  TRACE_NO_INDENT();

  va_list args;

  va_start(args, fmt);
  level_warn_(l, fmt, args);
  va_end(args);
}

static void level_con_(Levelp l, const char *fmt, va_list args)
{
  TRACE_NO_INDENT();

  char buf[ MAXLONGSTR ];
  int  len = 0;

  buf[ 0 ] = '\0';
  get_timestamp(buf, MAXLONGSTR);
  len = (int) strlen(buf);
  snprintf(buf + len, MAXLONGSTR - len, "%s: ", to_string(nullptr, l).c_str());
  len = (int) strlen(buf);
  vsnprintf(buf + len, MAXLONGSTR - len, fmt, args);
  putf(MY_STDOUT, buf);

  if (! g_opt_tests) {
    term_log(buf);
    putchar('\n');
  }

  wid_console_log(buf);
}

void LEVEL_CON(Levelp l, const char *fmt, ...)
{
  TRACE_NO_INDENT();

  va_list args;
  va_start(args, fmt);
  level_con_(l, fmt, args);
  va_end(args);
}

static void level_err_(Levelp l, const char *fmt, va_list args)
{
  char buf[ MAXLONGSTR ];
  int  len = 0;

  buf[ 0 ] = '\0';
  snprintf(buf + len, MAXLONGSTR - len, "%s: ", to_string(nullptr, l).c_str());
  len = (int) strlen(buf);
  vsnprintf(buf + len, MAXLONGSTR - len, fmt, args);

  ERR("%s", buf);
}

void LEVEL_ERR(Levelp l, const char *fmt, ...)
{
  TRACE_NO_INDENT();

  va_list args;
  va_start(args, fmt);
  level_err_(l, fmt, args);
  va_end(args);
}

static void level_topcon_(Levelp l, const char *fmt, va_list args)
{
  TRACE_NO_INDENT();

  char buf[ MAXLONGSTR ];
  int  len = 0;

  buf[ 0 ] = '\0';
  get_timestamp(buf, MAXLONGSTR);
  len = (int) strlen(buf);
  snprintf(buf + len, MAXLONGSTR - len, "%s: ", to_string(nullptr, l).c_str());
  len = (int) strlen(buf);
  vsnprintf(buf + len, MAXLONGSTR - len, fmt, args);

  putf(MY_STDOUT, buf);

  if (! g_opt_tests) {
    term_log(buf);
    putchar('\n');
  }

  wid_topcon_log(buf);
  wid_console_log(buf);
}

void LEVEL_TOPCON(Levelp l, const char *fmt, ...)
{
  TRACE_NO_INDENT();

  va_list args;

  va_start(args, fmt);
  level_topcon_(l, fmt, args);
  va_end(args);
}

static void level_botcon_(Levelp l, const char *fmt, va_list args)
{
  TRACE_NO_INDENT();

  char buf[ MAXLONGSTR ];
  int  len = 0;

  buf[ 0 ] = '\0';
  get_timestamp(buf, MAXLONGSTR);
  len = (int) strlen(buf);
  snprintf(buf + len, MAXLONGSTR - len, "%s: ", to_string(nullptr, l).c_str());
  len = (int) strlen(buf);
  vsnprintf(buf + len, MAXLONGSTR - len, fmt, args);

  wid_botcon_log(buf);
}

void LEVEL_BOTCON(Levelp l, const char *fmt, ...)
{
  TRACE_NO_INDENT();

  va_list args;

  va_start(args, fmt);
  level_botcon_(l, fmt, args);
  va_end(args);
}
