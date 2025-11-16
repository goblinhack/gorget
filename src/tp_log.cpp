//
// Copyright goblinhack@gmail.com
//

#include "my_backtrace.hpp"
#include "my_callstack.hpp"
#include "my_console.hpp"
#include "my_globals.hpp"
#include "my_log.hpp"
#include "my_main.hpp"
#include "my_ptrcheck.hpp"
#include "my_string.hpp"
#include "my_tp.hpp"
#include "my_wid_console.hpp"

#include <string.h>

void TP_LOG_(Tpp tp, const char *fmt, va_list args)
{
  verify(MTYPE_TP, tp);
  char buf[ MAXLONGSTR ];
  int  len = 0;

  buf[ 0 ] = '\0';
  get_timestamp(buf, MAXLONGSTR);
  len = (int) strlen(buf);

  snprintf(buf + len, MAXLONGSTR - len, "%100s: %*s", tp_name(tp).c_str(), g_callframes_indent, "");

  len = (int) strlen(buf);
  vsnprintf(buf + len, MAXLONGSTR - len, fmt, args);

  putf(MY_STDOUT, buf);
}

void TP_LOG(Tpp tp, const char *fmt, ...)
{
  verify(MTYPE_TP, tp);

  va_list args;
  va_start(args, fmt);
  TP_LOG_(tp, fmt, args);
  va_end(args);
}

void TP_DBG_(Tpp tp, const char *fmt, ...)
{
  IF_NODEBUG { return; }

  verify(MTYPE_TP, tp);

  va_list args;
  va_start(args, fmt);
  TP_LOG_(tp, fmt, args);
  va_end(args);
}

void TP_DIE_(Tpp tp, const char *fmt, va_list args)
{
  verify(MTYPE_TP, tp);
  char buf[ MAXLONGSTR ];
  int  len = 0;

  buf[ 0 ] = '\0';
  get_timestamp(buf, MAXLONGSTR);
  len = (int) strlen(buf);
  snprintf(buf + len, MAXLONGSTR - len, "%s: ", tp_name(tp).c_str());

  len = (int) strlen(buf);
  vsnprintf(buf + len, MAXLONGSTR - len, fmt, args);

  DIE("%s", buf);
}

void TP_DIE(Tpp tp, const char *fmt, ...)
{
  verify(MTYPE_TP, tp);
  va_list args;

  va_start(args, fmt);
  TP_DIE_(tp, fmt, args);
  va_end(args);
}

void TP_CON_(Tpp tp, const char *fmt, va_list args)
{
  verify(MTYPE_TP, tp);
  char buf[ MAXLONGSTR ];
  int  len = 0;

  buf[ 0 ] = '\0';
  get_timestamp(buf, MAXLONGSTR);
  len = (int) strlen(buf);
  snprintf(buf + len, MAXLONGSTR - len, "%s: ", tp_name(tp).c_str());

  len = (int) strlen(buf);
  vsnprintf(buf + len, MAXLONGSTR - len, fmt, args);

  putf(MY_STDOUT, buf);

  if (! g_opt_tests) {
    term_log(buf);
    putchar('\n');
  }

  wid_console_log(buf);
}

void TP_CON(Tpp tp, const char *fmt, ...)
{
  verify(MTYPE_TP, tp);
  va_list args;

  va_start(args, fmt);
  TP_CON_(tp, fmt, args);
  va_end(args);
}

void TP_ERR_(Tpp tp, const char *fmt, va_list args)
{
  verify(MTYPE_TP, tp);
  char buf[ MAXLONGSTR ];
  int  len = 0;

  callstack_dump();
  backtrace_dump();

  buf[ 0 ] = '\0';
  get_timestamp(buf, MAXLONGSTR);
  len = (int) strlen(buf);
  snprintf(buf + len, MAXLONGSTR - len, "ERROR: Thing %s: ", tp_name(tp).c_str());

  len = (int) strlen(buf);
  vsnprintf(buf + len, MAXLONGSTR - len, fmt, args);

  putf(MY_STDOUT, buf);

  putf(MY_STDERR, buf);

  fprintf(stderr, "%s\n", buf);

  wid_console_log(buf);
}

void TP_ERR(Tpp tp, const char *fmt, ...)
{
  extern Gamep game;
  auto         g = game;

  //
  // If multiple errors are going on, we don't need popups for all of them
  //
  if (AN_ERROR_OCCURRED()) {
    va_list args;
    va_start(args, fmt);
    TP_LOG_(tp, fmt, args);
    va_end(args);
    return;
  }

  g_errored_thread_id = g_thread_id;
  va_list args;
  va_start(args, fmt);
  TP_ERR_(tp, fmt, args);
  va_end(args);

  wid_unset_focus(g);
  wid_unset_focus_lock();
  wid_console_raise(g);

  if (g_quitting) {
    DIE("Error while quitting");
  }
}
