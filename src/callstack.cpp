//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_main.hpp"
#include "my_sprintf.hpp"
#include "my_string.hpp"
#include "my_wid_console.hpp"

thread_local struct callframe callframes[ MAXCALLFRAME ];
thread_local unsigned char    g_callframes_depth;
thread_local unsigned char    g_callframes_indent;

std::string callstack_string(void)
{
  std::string sout;

  sout = "code trace\n";
  sout += "==========\n";

  for (auto depth = 0; depth < g_callframes_depth; depth++) {
    auto iter = &callframes[ depth ];
    sout += string_sprintf("(callstack) %d %s, line %u\n", depth, iter->func, iter->line);
  }

  return sout;
}

void callstack_dump_stderr(void)
{
  auto bt = callstack_string();
  fprintf(stderr, "%s", bt.c_str());
  fprintf(stderr, "\n");
}

void callstack_dump(void)
{
  auto bt = callstack_string();
  fprintf(MY_STDERR, "%s", bt.c_str());
  wid_console_log(bt);
  fprintf(stderr, "\n");
}
