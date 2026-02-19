//
// Copyright goblinhack@gmail.com
//

#ifndef _MY_CPP_TEMPLATE_HPP_
#define _MY_CPP_TEMPLATE_HPP_

#include "my_random.hpp"
#include <map>
#include <stdlib.h>

template < class T, template < typename ELEM, typename ALLOC = std::allocator< ELEM > > class C >

bool contains(C< T > *c, T t)
{
  typename C< T >::iterator i = c->begin();

  while (i != c->end()) {
    if (*i == t) {
      return true;
    }
    i++;
  }
  return false;
}

template < class T, template < typename ELEM, typename ALLOC = std::allocator< ELEM > > class C >

void push_back_if_unique(C< T > &c, const T &d)
{
  auto so = c.begin();
  auto eo = c.end();

  while (so != eo) {
    T t = *so;

    if (t == d) {
      return;
    }
    so++;
  }
  c.push_back(d);
}

template < class T, template < typename ELEM, typename ALLOC = std::allocator< ELEM > > class C >
T pcg_rand_one_of(C< T > &c)
{
  auto so = c.begin();
  auto eo = c.end();

  size_t const sz = eo - so;
  if (! sz) {
    return *so;
  }

  return *(so + (pcg_rand() % sz));
}

template < class T, template < typename ELEM, typename ALLOC = std::allocator< ELEM > > class C >
T rand_one_of(C< T > &c)
{
  auto so = c.begin();
  auto eo = c.end();

  size_t const sz = eo - so;
  if (! sz) {
    return *so;
  }

  return *(so + (rand() % sz));
}

#endif
