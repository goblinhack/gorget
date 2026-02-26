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
#include "my_wids.hpp"

#include <cstring>

void TP_LOG_(Tpp tp, const char *fmt, va_list args)
{
  TRACE();

  VERIFY(MTYPE_TP, tp);
  char buf[ MAXLONGSTR ];
  int  len = 0;

  buf[ 0 ] = '\0';
  get_timestamp(buf, MAXLONGSTR);
  len = (int) strlen(buf);

  snprintf(buf + len, MAXLONGSTR - len, "[%-50s]: %*s", tp_name(tp).c_str(), g_callframes_depth, "");

  len = (int) strlen(buf);
  vsnprintf(buf + len, MAXLONGSTR - len, fmt, args);

  putf(MY_STDOUT, buf);
}

void TP_LOG(Tpp tp, const char *fmt, ...)
{
  TRACE();

  VERIFY(MTYPE_TP, tp);

  va_list args = {};
  va_start(args, fmt);
  TP_LOG_(tp, fmt, args);
  va_end(args);
}

void TP_DBG_(Tpp tp, const char *fmt, ...)
{
  TRACE();

  IF_NODEBUG { return; }

  VERIFY(MTYPE_TP, tp);

  va_list args = {};
  va_start(args, fmt);
  TP_LOG_(tp, fmt, args);
  va_end(args);
}

void TP_DIE_(Tpp tp, const char *fmt, va_list args)
{
  TRACE();

  VERIFY(MTYPE_TP, tp);
  char buf[ MAXLONGSTR ];
  int  len = 0;

  buf[ 0 ] = '\0';
  get_timestamp(buf, MAXLONGSTR);
  len = (int) strlen(buf);
  snprintf(buf + len, MAXLONGSTR - len, "%s: ", tp_name(tp).c_str());

  len = (int) strlen(buf);
  vsnprintf(buf + len, MAXLONGSTR - len, fmt, args);

  CROAK("%s", buf);
}

void TP_DIE(Tpp tp, const char *fmt, ...)
{
  TRACE();

  VERIFY(MTYPE_TP, tp);
  va_list args = {};

  va_start(args, fmt);
  TP_DIE_(tp, fmt, args);
  va_end(args);
}

void TP_CON_(Tpp tp, const char *fmt, va_list args)
{
  TRACE();

  VERIFY(MTYPE_TP, tp);
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
  TRACE();

  VERIFY(MTYPE_TP, tp);
  va_list args = {};

  va_start(args, fmt);
  TP_CON_(tp, fmt, args);
  va_end(args);
}

void TP_ERR_(Tpp tp, const char *fmt, va_list args)
{
  char buf[ MAXLONGSTR ];
  int  len = 0;

  buf[ 0 ] = '\0';
  snprintf(buf + len, MAXLONGSTR - len, "%s: ", tp_name(tp).c_str());
  len = (int) strlen(buf);
  vsnprintf(buf + len, MAXLONGSTR - len, fmt, args);

  ERR("%s", buf);
}

void TP_ERR(Tpp tp, const char *fmt, ...)
{
  TRACE();

  va_list args = {};
  va_start(args, fmt);
  TP_ERR_(tp, fmt, args);
  va_end(args);
}
