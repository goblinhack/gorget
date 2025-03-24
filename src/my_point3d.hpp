//
// Copyright goblinhack@gmail.com
//

#pragma once
#ifndef _MY_POINT3D_HPP_
#define _MY_POINT3D_HPP_

template < typename T > struct my_apoint3d {
public:
  T x {};
  T y {};
  T z {};

  my_apoint3d(void) : x(0), y(0), z(0) {}
  my_apoint3d(T vx, T vy, T vz) : x(vx), y(vy), z(vz) {}

  void operator+=(my_apoint3d< T > const &);
  void operator-=(my_apoint3d< T > const &);
  void operator*=(T);
  void operator/=(T);
};

template < typename T > bool             operator==(my_apoint3d< T > const &, my_apoint3d< T > const &);
template < typename T > my_apoint3d< T > operator+(my_apoint3d< T > const &, my_apoint3d< T > const &);
template < typename T > my_apoint3d< T > operator-(my_apoint3d< T > const &, my_apoint3d< T > const &);
template < typename T > my_apoint3d< T > operator*(my_apoint3d< T > const &, T);
template < typename T > my_apoint3d< T > operator/(my_apoint3d< T > const &, T);

using point3d = my_apoint3d< short >;

extern point make_point(const point3d &);

#endif // _MY_POINT3D_HPP_
