//
// Copyright goblinhack@gmail.com
//

#pragma once
#ifndef _MY_POINT3D_HPP_
#define MY_POINT3D_HPP_

template < typename T > struct my_apoint3d {
public:
  T x {};
  T y {};
  T z {};

  my_apoint3d(void) : x(0), y(0), z(0) {}
  my_apoint3d(T vx, T vy, T vz) : x(vx), y(vy), z(vz) {}

  void operator+=(my_apoint3d< T > const & /*b*/);
  void operator-=(my_apoint3d< T > const & /*b*/);
  void operator*=(T /*b*/);
  void operator/=(T /*b*/);
};

template < typename T > bool             operator==(my_apoint3d< T > const             &/*a*/, my_apoint3d< T > const             &/*b*/);
template < typename T > my_apoint3d< T > operator+(my_apoint3d< T > const & /*a*/, my_apoint3d< T > const & /*b*/);
template < typename T > my_apoint3d< T > operator-(my_apoint3d< T > const & /*a*/, my_apoint3d< T > const & /*b*/);
template < typename T > my_apoint3d< T > operator*(my_apoint3d< T > const & /*a*/, T /*b*/);
template < typename T > my_apoint3d< T > operator/(my_apoint3d< T > const & /*a*/, T /*b*/);

using point3d = my_apoint3d< short >;

#endif // _MY_POINT3D_HPP_
