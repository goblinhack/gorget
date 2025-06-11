//
// Copyright goblinhack@gmail.com
//

#include "my_backtrace.hpp"
#include "my_callstack.hpp"
#include "my_console.hpp"
#include "my_log.hpp"
#include "my_main.hpp"
#include "my_ptrcheck.hpp"
#include "my_string.hpp"
#include "my_tp.hpp"
#include "my_wid_console.hpp"

#include <string.h>

void log_(Tpp tp, const char *fmt, va_list args)
{
  verify(MTYPE_TP, tp);
  char buf[ MAXLONGSTR ];
  int  len = 0;

  buf[ 0 ] = '\0';
  get_timestamp(buf, MAXLONGSTR);
  len = (int) strlen(buf);

  snprintf(buf + len, MAXLONGSTR - len, "%100s: %*s", tp_name(tp), g_callframes_indent, "");

  len = (int) strlen(buf);
  vsnprintf(buf + len, MAXLONGSTR - len, fmt, args);

  putf(MY_STDOUT, buf);
}

void log(Tpp tp, const char *fmt, ...)
{
  verify(MTYPE_TP, tp);

  va_list args;
  va_start(args, fmt);
  log_(tp, fmt, args);
  va_end(args);
}

void dbg_(Tpp tp, const char *fmt, ...)
{
  IF_NODEBUG { return; }

  verify(MTYPE_TP, tp);

  va_list args;
  va_start(args, fmt);
  log_(tp, fmt, args);
  va_end(args);
}

void die_(Tpp tp, const char *fmt, va_list args)
{
  verify(MTYPE_TP, tp);
  char buf[ MAXLONGSTR ];
  int  len = 0;

  buf[ 0 ] = '\0';
  get_timestamp(buf, MAXLONGSTR);
  len = (int) strlen(buf);
  snprintf(buf + len, MAXLONGSTR - len, "%s: ", tp_name(tp));

  len = (int) strlen(buf);
  vsnprintf(buf + len, MAXLONGSTR - len, fmt, args);

  DIE("%s", buf);
}

void die(Tpp tp, const char *fmt, ...)
{
  g_errored = true;

  verify(MTYPE_TP, tp);
  va_list args;

  va_start(args, fmt);
  die_(tp, fmt, args);
  va_end(args);
}

void con_(Tpp tp, const char *fmt, va_list args)
{
  verify(MTYPE_TP, tp);
  char buf[ MAXLONGSTR ];
  int  len = 0;

  buf[ 0 ] = '\0';
  get_timestamp(buf, MAXLONGSTR);
  len = (int) strlen(buf);
  snprintf(buf + len, MAXLONGSTR - len, "%s: ", tp_name(tp));

  len = (int) strlen(buf);
  vsnprintf(buf + len, MAXLONGSTR - len, fmt, args);

  putf(MY_STDOUT, buf);

  term_log(buf);
  putchar('\n');
  wid_console_log(buf);
  FLUSH_TERMINAL();
}

void con(Tpp tp, const char *fmt, ...)
{
  verify(MTYPE_TP, tp);
  va_list args;

  va_start(args, fmt);
  con_(tp, fmt, args);
  va_end(args);
}

void err_(Tpp tp, const char *fmt, va_list args)
{
  static bool nested_error;
  if (nested_error) {
    return;
  }
  nested_error = true;

  verify(MTYPE_TP, tp);
  char buf[ MAXLONGSTR ];
  int  len = 0;

  callstack_dump();
  backtrace_dump();

  buf[ 0 ] = '\0';
  get_timestamp(buf, MAXLONGSTR);
  len = (int) strlen(buf);
  snprintf(buf + len, MAXLONGSTR - len, "ERROR: Thing %s: ", tp_name(tp));

  len = (int) strlen(buf);
  vsnprintf(buf + len, MAXLONGSTR - len, fmt, args);

  putf(MY_STDOUT, buf);

  putf(MY_STDERR, buf);

  fprintf(stderr, "%s\n", buf);

  wid_console_log(buf);
  TRACE_NO_INDENT();
  FLUSH_TERMINAL_FOR_ALL_PLATFORMS();

  nested_error = false;
}

void err(Tpp tp, const char *fmt, ...)
{
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
    log_(tp, fmt, args);
    va_end(args);
  } else {
    g_errored = true;
    va_list args;
    va_start(args, fmt);
    err_(tp, fmt, args);
    va_end(args);
  }

  nested_error = false;
}
