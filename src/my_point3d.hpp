//
// Copyright goblinhack@gmail.com
//

#ifndef MY_POINT3D_HPP
#define MY_POINT3D_HPP

template < typename T > struct my_apoint3d {
public:
  T x {};
  T y {};
  T z {};

  my_apoint3d() : x(0), y(0), z(0) {}
  my_apoint3d(T vx, T vy, T vz) : x(vx), y(vy), z(vz) {}

  void operator+=(my_apoint3d< T > const &b);
  void operator-=(my_apoint3d< T > const &b);
  void operator*=(T b);
  void operator/=(T b);
};

template < typename T > auto operator==(my_apoint3d< T > const &a, my_apoint3d< T > const &b) -> bool;
template < typename T > auto operator+(my_apoint3d< T > const &a, my_apoint3d< T > const &b) -> my_apoint3d< T >;
template < typename T > auto operator-(my_apoint3d< T > const &a, my_apoint3d< T > const &b) -> my_apoint3d< T >;
template < typename T > auto operator*(my_apoint3d< T > const &a, T b) -> my_apoint3d< T >;
template < typename T > auto operator/(my_apoint3d< T > const &a, T b) -> my_apoint3d< T >;

using point3d = my_apoint3d< short >;

#endif // _MY_POINT3D_HPP
