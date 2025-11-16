//
// Copyright goblinhack@gmail.com
//

#include "my_backtrace.hpp"
#include "my_callstack.hpp"
#include "my_console.hpp"
#include "my_globals.hpp"
#include "my_log.hpp"
#include "my_main.hpp"
#include "my_string.hpp"
#include "my_thing.hpp"
#include "my_wid_botcon.hpp"
#include "my_wid_console.hpp"
#include "my_wid_topcon.hpp"

#include <string.h>

static void thing_log_(Thingp t, const char *fmt, va_list args)
{
  TRACE_NO_INDENT();

  char buf[ MAXLONGSTR ];
  int  len = 0;

  buf[ 0 ] = '\0';
  get_timestamp(buf, MAXLONGSTR);
  len = (int) strlen(buf);
  snprintf(buf + len, MAXLONGSTR - len, "%-50s: %*s", to_string(nullptr, t).c_str(), g_callframes_indent, "");
  len = (int) strlen(buf);
  vsnprintf(buf + len, MAXLONGSTR - len, fmt, args);

  putf(MY_STDOUT, buf);
}

void THING_LOG(Thingp t, const char *fmt, ...)
{
  TRACE_NO_INDENT();

  if (! thing_is_loggable(t)) {
    return;
  }

  va_list args;
  va_start(args, fmt);
  thing_log_(t, fmt, args);
  va_end(args);
}

void THING_DBG(Thingp t, const char *fmt, ...)
{
  TRACE_NO_INDENT();

  IF_NODEBUG return;

  if (! thing_is_loggable(t)) {
    return;
  }

  va_list args;
  va_start(args, fmt);
  thing_log_(t, fmt, args);
  va_end(args);
}

static void thing_warn_(Thingp t, const char *fmt, va_list args)
{
  TRACE_NO_INDENT();

  char buf[ MAXLONGSTR ];
  int  len = 0;

  buf[ 0 ] = '\0';
  get_timestamp(buf, MAXLONGSTR);
  len = (int) strlen(buf);
  snprintf(buf + len, MAXLONGSTR - len, "%s: ", to_string(nullptr, t).c_str());
  len = (int) strlen(buf);
  vsnprintf(buf + len, MAXLONGSTR - len, fmt, args);

  putf(MY_STDOUT, buf);
  wid_console_log(buf);
}

void THING_WARN(Thingp t, const char *fmt, ...)
{
  TRACE_NO_INDENT();

  va_list args;

  va_start(args, fmt);
  thing_warn_(t, fmt, args);
  va_end(args);
}

static void thing_con_(Thingp t, const char *fmt, va_list args)
{
  TRACE_NO_INDENT();

  char buf[ MAXLONGSTR ];
  int  len = 0;

  buf[ 0 ] = '\0';
  get_timestamp(buf, MAXLONGSTR);
  len = (int) strlen(buf);
  snprintf(buf + len, MAXLONGSTR - len, "%s: ", to_string(nullptr, t).c_str());
  len = (int) strlen(buf);
  vsnprintf(buf + len, MAXLONGSTR - len, fmt, args);
  putf(MY_STDOUT, buf);

  if (! g_opt_tests) {
    term_log(buf);
    putchar('\n');
  }

  wid_console_log(buf);
}

void THING_CON(Thingp t, const char *fmt, ...)
{
  TRACE_NO_INDENT();

  va_list args;
  va_start(args, fmt);
  thing_con_(t, fmt, args);
  va_end(args);
}

static void thing_err_(Thingp t, const char *fmt, va_list args)
{
  TRACE_NO_INDENT();

  callstack_dump();
  backtrace_dump();

  char buf[ MAXLONGSTR ];
  int  len = 0;

  buf[ 0 ] = '\0';
  get_timestamp(buf, MAXLONGSTR);
  len = (int) strlen(buf);
  snprintf(buf + len, MAXLONGSTR - len, "%s: ", to_string(nullptr, t).c_str());
  len = (int) strlen(buf);
  snprintf(buf + len, MAXLONGSTR - len, "ERROR: ");
  len = (int) strlen(buf);
  vsnprintf(buf + len, MAXLONGSTR - len, fmt, args);

  error_handler(buf);

  putf(MY_STDERR, buf);
  putf(MY_STDOUT, buf);

  term_log(buf);
  putchar('\n');

  wid_console_log(buf);
}

void THING_ERR(Thingp t, const char *fmt, ...)
{
  TRACE_NO_INDENT();

  extern Gamep game;
  auto         g = game;

  //
  // If multiple errors are going on, we don't need popups for all of them
  //
  if (AN_ERROR_OCCURRED()) {
    va_list args;
    va_start(args, fmt);
    thing_log_(t, fmt, args);
    va_end(args);
    return;
  }

  g_errored_thread_id = g_thread_id;
  va_list args;
  va_start(args, fmt);
  thing_err_(t, fmt, args);
  va_end(args);

  wid_unset_focus(g);
  wid_unset_focus_lock();
  wid_console_raise(g);

  if (g_quitting) {
    DIE("Error while quitting");
  }
}

static void thing_topcon_(Thingp t, const char *fmt, va_list args)
{
  TRACE_NO_INDENT();

  char buf[ MAXLONGSTR ];
  int  len = 0;

  buf[ 0 ] = '\0';
  get_timestamp(buf, MAXLONGSTR);
  len = (int) strlen(buf);
  snprintf(buf + len, MAXLONGSTR - len, "%s: ", to_string(nullptr, t).c_str());
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

void THING_TOPCON(Thingp t, const char *fmt, ...)
{
  TRACE_NO_INDENT();

  va_list args;

  va_start(args, fmt);
  thing_topcon_(t, fmt, args);
  va_end(args);
}

static void thing_botcon_(Thingp t, const char *fmt, va_list args)
{
  TRACE_NO_INDENT();

  char buf[ MAXLONGSTR ];
  int  len = 0;

  buf[ 0 ] = '\0';
  get_timestamp(buf, MAXLONGSTR);
  len = (int) strlen(buf);
  snprintf(buf + len, MAXLONGSTR - len, "%s: ", to_string(nullptr, t).c_str());
  len = (int) strlen(buf);
  vsnprintf(buf + len, MAXLONGSTR - len, fmt, args);

  wid_botcon_log(buf);
}

void THING_BOTCON(Thingp t, const char *fmt, ...)
{
  TRACE_NO_INDENT();

  va_list args;

  va_start(args, fmt);
  thing_botcon_(t, fmt, args);
  va_end(args);
}
