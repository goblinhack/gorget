//
// Copyright goblinhack@gmail.com
//
#pragma once
#ifndef _MY_CALLSTACK_HPP_
#define MY_CALLSTACK_HPP_

#include "my_source_loc.hpp"
#include "my_types.hpp"

#define CAT(A, B)  A##B
#define CAT2(A, B) CAT(A, B)

#ifdef ENABLE_DEBUG_TRACE
#define TRACE_AND_INDENT() tracer_t CAT2(__my_trace__, __LINE__)(SRC_FUNC_NAME, SRC_LINE_NUM);
#define TRACE_NO_INDENT()  tracer_no_indent_t CAT2(__my_trace__, __LINE__)(SRC_FUNC_NAME, SRC_LINE_NUM);
#else
#define TRACE_AND_INDENT()
#define TRACE_NO_INDENT()
#endif

struct callframe {
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

extern thread_local struct callframe callframes[ MAXCALLFRAME ];
extern thread_local unsigned char    g_callframes_depth;
extern thread_local unsigned char    g_callframes_indent;

struct tracer_t {
  tracer_t(const char *func, const unsigned short line)
  {
// useful for code tracing in real time
// fprintf(stderr, "%s %s() line %d\n", file, func, line);
#ifdef ENABLE_DEBUG_TRACE
    g_callframes_indent++;
    callframe *c = &callframes[ g_callframes_depth++ ];
    c->func      = func;
    c->line      = line;
#endif
  }

  ~tracer_t()
  {
#ifdef ENABLE_DEBUG_TRACE
    g_callframes_indent--;
    g_callframes_depth--;
#endif
  }
};

struct tracer_no_indent_t {
  tracer_no_indent_t(const char *func, const unsigned short line)
  {
// useful for code tracing in real time
// fprintf(stderr, "%s %s() line %d\n", file, func, line);
#ifdef ENABLE_DEBUG_TRACE
    callframe *c = &callframes[ g_callframes_depth++ ];
    c->func      = func;
    c->line      = line;
#endif
  }

  ~tracer_no_indent_t()
  {
#ifdef ENABLE_DEBUG_TRACE
    g_callframes_depth--;
#endif
  }
};

extern void        callstack_dump(FILE        */*fp*/);
extern void        callstack_dump();
extern std::string callstack_string();

#endif
