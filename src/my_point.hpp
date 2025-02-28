//
// Copyright Neil McGill, goblinhack@gmail.com
//

#pragma once
#ifndef _MY_POINT_HPP_
#define _MY_POINT_HPP_

template < typename T > struct my_apoint {
public:
  T x {};
  T y {};

  my_apoint(T vx, T vy) : x(vx), y(vy) {}
  my_apoint(void) : x(0), y(0) {};

  void  operator+=(my_apoint< T > const &);
  void  operator-=(my_apoint< T > const &);
  void  operator*=(T);
  void  operator/=(T);
  float length(void) const;
  void  unit(void);
};

using point  = my_apoint< short >;
using fpoint = my_apoint< float >;

//
// Needed for std::map
//
template < typename T > bool operator<(my_apoint< T > const &a, my_apoint< T > const &b)
{
  return (a.x < b.x) || (a.x == b.x && a.y < b.y);
}

template < typename T > bool           operator==(my_apoint< T > const &, my_apoint< T > const &);
template < typename T > my_apoint< T > operator+(my_apoint< T > const &, my_apoint< T > const &);
template < typename T > my_apoint< T > operator-(my_apoint< T > const &, my_apoint< T > const &);
template < typename T > my_apoint< T > operator*(my_apoint< T > const &, T);
template < typename T > my_apoint< T > operator/(my_apoint< T > const &, T);

static inline point make_point(const int x, const int y) { return point(x, y); }

static inline point make_point(const fpoint &f) { return point(f.x, f.y); }

static inline fpoint make_fpoint(const point f) { return fpoint(f.x, f.y); }

fpoint rotate_radians(float angle, const fpoint &p, const fpoint &origin);
fpoint rotate_radians(const fpoint &p, float angle);
fpoint normal(const fpoint &p);
fpoint unit(const fpoint &p);

float distance(const fpoint &a, const fpoint &b);
float distance(const point a, const point b);
float angle_radians(const fpoint &p);

#endif // _MY_POINT_HPP_
