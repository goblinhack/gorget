//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_main.hpp"
#include "my_sprintf.hpp"
#include "my_string.hpp"

thread_local struct callframe callframes[ MAXCALLFRAME ];
thread_local unsigned char    g_callframes_depth;
thread_local unsigned char    g_callframes_indent;

void callstack_dump_stderr(void)
{
  fprintf(stderr, "code trace\n");
  fprintf(stderr, "==========\n");
  auto s = callstack_string();
  fprintf(stderr, "%s", s.c_str());
}

void callstack_dump(void)
{
  fprintf(MY_STDERR, "code trace\n");
  fprintf(MY_STDERR, "==========\n");
  auto s = callstack_string();
  fprintf(MY_STDERR, "%s", s.c_str());
}

std::string callstack_string(void)
{
  std::string sout;

  for (auto depth = 0; depth < g_callframes_depth; depth++) {
    auto iter = &callframes[ depth ];
    sout += string_sprintf("(callstack) %d %s, line %u\n", depth, iter->func, iter->line);
  }

  return sout;
}
