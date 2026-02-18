//
// Copyright goblinhack@gmail.com
//

#include "my_globals.hpp"
#include "my_level.hpp"
#include "my_main.hpp"

#include <format>

static int g_iter;

MyIter::MyIter(Gamep g, Levelsp _v, int *out_iter, const char *_func, const unsigned short _line)
{
  if (g_thread_id != MAIN_THREAD) {
    CROAK("using iterator, but not on main thread, thread=%d", g_thread_id);
  }

  this->v    = _v;
  this->func = _func;
  this->line = _line;

  iter = *out_iter = g_iter++;

  if (g_iter >= MY_ITERS_MAX) {
    CROAK("%s:%u exceeded number of iterators", func, line);
  }

  if (v->in_iter[ iter ] != 0U) {
    CROAK("%s:%u nested loop for iter %d", func, line, iter);
  }

  v->in_iter[ iter ] = 1U;

  //
  // This is the iterator value we compare with things to check if they've been walked already.
  //
  v->iter[ iter ]++;

  //
  // Handle wraparound
  //
  if (v->iter[ iter ] == 0U) {
    v->iter[ iter ]++;
  }

#if 0
  fprintf(stderr, "ITER %u %s:%u {\n", iter, func, line);
#endif
}

MyIter::~MyIter()
{
  if (g_thread_id != MAIN_THREAD) {
    CROAK("%s:%u using iterator, but not on main thread, thread=%d", func, line, g_thread_id);
  }

  if (v->in_iter[ iter ] == 0U) {
    CROAK("%s:%u bad loop end for iter %d", func, line, iter);
  }
  v->in_iter[ iter ] = 0U;

  g_iter--;

  if (g_iter < 0) {
    CROAK("%s:%u underflow for number of iterators", func, line);
  }

#if 0
  fprintf(stderr, "ITER %u %s:%u }\n", iter, func, line);
#endif
}
