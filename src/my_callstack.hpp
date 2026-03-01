//
// Copyright goblinhack@gmail.com
//
#ifndef MY_CALLSTACK_HPP
#define MY_CALLSTACK_HPP

#include "my_source_loc.hpp"
#include "my_types.hpp"

#define CAT(A, B)  A##B
#define CAT2(A, B) CAT(A, B)

#ifdef ENABLE_DEBUG_TRACE

#ifdef DEBUG_BUILD
#define TRACE_DEBUG() const TracerT CAT2(__my_trace__, __LINE__)(SRC_FUNC_NAME, SRC_LINE_NUM);
#else
#define TRACE_DEBUG()
#endif

#define TRACE()        const TracerT CAT2(__my_trace__, __LINE__)(SRC_FUNC_NAME, SRC_LINE_NUM);
#define TRACE_INDENT() const TracerIndentT CAT2(__my_trace__, __LINE__)(SRC_FUNC_NAME, SRC_LINE_NUM);

#else
#define TRACE_DEBUG()
#define TRACE()
#define TRACE_INDENT()
#endif

struct Callframe {
  const char    *func;
  unsigned short line;
};

//
// I used to use a c++ vector here, but global destructor order meant
// this was unreliable for tracing classes as they are destroyed after
// the callstack vector
//
// No needs for bounds checking if we use unsigned char as the size, as
// the index will wrap around to 0 if we hit some endless recursion.
//
enum { MAXCALLFRAME = 256 };

#define USE_THREADS

extern thread_local struct Callframe callframes[ MAXCALLFRAME ];
extern thread_local unsigned char    g_callframes_depth;
extern thread_local unsigned char    g_callframes_indent;

class TracerT
{
public:
  TracerT(const char *func, const unsigned short line)
  {
    Callframe *c = &callframes[ g_callframes_depth++ ];
    c->func      = func;
    c->line      = line;
  }

  ~TracerT() { g_callframes_depth--; }
};

class TracerIndentT
{
public:
  TracerIndentT(const char *func, const unsigned short line)
  {
    Callframe *c = &callframes[ g_callframes_depth++ ];
    g_callframes_indent++;
    c->func = func;
    c->line = line;
  }

  ~TracerIndentT()
  {
    g_callframes_depth--;
    g_callframes_indent--;
  }
};

extern void callstack_dump(FILE *fp);
extern void callstack_dump();
extern auto callstack_string() -> std::string;

#endif
