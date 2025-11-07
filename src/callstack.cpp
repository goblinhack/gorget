//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_main.hpp"
#include "my_string.hpp"

#define __MAIN__

thread_local struct callframe callframes[ MAXCALLFRAME ];
thread_local unsigned char    g_callframes_depth;
thread_local unsigned char    g_callframes_indent;

void callstack_dump_stderr(void)
{
  fprintf(stderr, "code trace\n");
  fprintf(stderr, "==========\n");
  for (auto depth = 0; depth < g_callframes_depth; depth++) {
    auto iter = &callframes[ depth ];
    fprintf(stderr, "(trace) %d %s, line %u\n", depth, iter->func, iter->line);
  }
}

void callstack_dump(void)
{
  fprintf(MY_STDERR, "code trace\n");
  fprintf(MY_STDERR, "==========\n");
  for (auto depth = 0; depth < g_callframes_depth; depth++) {
    auto iter = &callframes[ depth ];
    fprintf(MY_STDERR, "(trace) %d %s, line %u\n", depth, iter->func, iter->line);
  }
}

std::string callstack_string(void)
{
  char tmp[ MAXLONGSTR ];

  *tmp = '\0';

  for (auto depth = 0; depth < g_callframes_depth; depth++) {
    auto iter = &callframes[ depth ];
    snprintf(tmp + strlen(tmp), SIZEOF(tmp) - strlen(tmp), "(strace) %d %s, line %u\n", depth, iter->func,
             iter->line);
  }

  return std::string(tmp);
}
