//
// Copyright Neil McGill, goblinhack@gmail.com
//

#pragma once
#ifndef _MY_SIZE_HPP_
#define _MY_SIZE_HPP_

template < class T > class my_asize
{
public:
  T w {};
  T h {};

  my_asize(void) : w(0), h(0) {}

  my_asize(T w, T h) : w(w), h(h) {}

  my_asize(const my_asize &a) : w(a.w), h(a.h) {}

  void operator+=(my_asize a)
  {
    w += a.w;
    h += a.h;
  }

  void operator-=(my_asize a)
  {
    w -= a.w;
    h -= a.h;
  }

  void operator/=(my_asize a)
  {
    w /= a.w;
    h /= a.h;
  }

  void operator*=(my_asize a)
  {
    w *= a.w;
    h *= a.h;
  }

  friend my_asize operator/(my_asize a, T i) { return (my_asize(a.w / i, a.h / i)); }

  friend my_asize operator*(my_asize a, T i) { return (my_asize(a.w * i, a.h * i)); }

  friend my_asize operator+(my_asize a, my_asize b) { return (my_asize(a.w + b.w, a.h + b.h)); }

  friend my_asize operator-(my_asize a, my_asize b) { return (my_asize(a.w - b.w, a.h - b.h)); }

  friend my_asize operator/(my_asize a, my_asize b) { return (my_asize(a.w / b.w, a.h / b.h)); }

  friend my_asize operator*(my_asize a, my_asize b) { return (my_asize(a.w * b.w, a.h * b.h)); }

  friend bool operator==(my_asize a, my_asize b) { return (a.w == b.w) && (a.h == b.h); }

  friend bool operator!=(my_asize a, my_asize b) { return (! (a == b)); }

  //
  // Compare areas of a and b
  //
  friend bool operator<(my_asize a, my_asize b) { return (a.w * a.h) < (b.w * b.h); }

  //
  // Compare areas of a and b
  //
  friend bool operator>(my_asize a, my_asize b) { return (a.w * a.h) > (b.w * b.h); }
};

using isize = my_asize< int16_t >;
using fsize = my_asize< float >;

#endif // _MY_SIZE_HPP_
