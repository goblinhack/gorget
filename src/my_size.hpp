//
// Copyright goblinhack@gmail.com
//

#ifndef MY_SIZE_HPP
#define MY_SIZE_HPP

#include "my_types.hpp"

template < class T > class MyAsize
{
public:
  T w {};
  T h {};

  MyAsize() : w(0), h(0) {}
  MyAsize(T vw, T vh) : w(vw), h(vh) {}

  void operator+=(MyAsize a)
  {
    w += a.w;
    h += a.h;
  }

  void operator-=(MyAsize a)
  {
    w -= a.w;
    h -= a.h;
  }

  void operator/=(MyAsize a)
  {
    w /= a.w;
    h /= a.h;
  }

  void operator*=(MyAsize a)
  {
    w *= a.w;
    h *= a.h;
  }

  friend auto operator/(MyAsize a, T i) -> MyAsize { return (MyAsize(a.w / i, a.h / i)); }

  friend auto operator*(MyAsize a, T i) -> MyAsize { return (MyAsize(a.w * i, a.h * i)); }

  friend auto operator+(MyAsize a, MyAsize b) -> MyAsize { return (MyAsize(a.w + b.w, a.h + b.h)); }

  friend auto operator-(MyAsize a, MyAsize b) -> MyAsize { return (MyAsize(a.w - b.w, a.h - b.h)); }

  friend auto operator/(MyAsize a, MyAsize b) -> MyAsize { return (MyAsize(a.w / b.w, a.h / b.h)); }

  friend auto operator*(MyAsize a, MyAsize b) -> MyAsize { return (MyAsize(a.w * b.w, a.h * b.h)); }

  friend auto operator==(MyAsize a, MyAsize b) -> bool { return (a.w == b.w) && (a.h == b.h); }

  friend auto operator!=(MyAsize a, MyAsize b) -> bool { return (! (a == b)); }

  //
  // Compare areas of a and b
  //
  friend auto operator<(MyAsize a, MyAsize b) -> bool { return (a.w * a.h) < (b.w * b.h); }

  //
  // Compare areas of a and b
  //
  friend auto operator>(MyAsize a, MyAsize b) -> bool { return (a.w * a.h) > (b.w * b.h); }
};

using isize = MyAsize< int16_t >;
using fsize = MyAsize< float >;

#endif // MY_SIZE_HPP
