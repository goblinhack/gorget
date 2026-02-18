//
// Copyright goblinhack@gmail.com
//

#include <print>
#include <utility>

#include "my_callstack.hpp"
#include "my_main.hpp"
#include "my_sprintf.hpp"
#include "my_string.hpp"
#include "my_wid_console.hpp"

thread_local struct callframe callframes[ MAXCALLFRAME ];
thread_local unsigned char    g_callframes_depth;
thread_local unsigned char    g_callframes_indent;

std::string callstack_string()
{
  std::string sout;

  sout = "code trace\n";
  sout += "==========\n";

  for (auto depth = 0; std::cmp_less(depth, g_callframes_depth); depth++) {
    auto *iter = &callframes[ depth ];
    sout += string_sprintf("(callstack) %s, line %u\n", iter->func, iter->line);
  }

  return sout;
}

void callstack_dump(FILE *fp)
{
  auto bt = callstack_string();
  std::print(fp, "{}", bt);
  std::println(fp, "");
}

void callstack_dump()
{
  auto bt = callstack_string();
  std::print(MY_STDERR, "{}", bt);
  wid_console_log(bt);
  std::println(MY_STDERR, "");
}
