//
// Copyright goblinhack@gmail.com
//

#ifndef MY_POINT3D_HPP
#define MY_POINT3D_HPP

template < typename T > struct MyApoint3d {
public:
  T x {};
  T y {};
  T z {};

  MyApoint3d() : x(0), y(0), z(0) {}
  MyApoint3d(T vx, T vy, T vz) : x(vx), y(vy), z(vz) {}

  void operator+=(MyApoint3d< T > const &b);
  void operator-=(MyApoint3d< T > const &b);
  void operator*=(T b);
  void operator/=(T b);
};

template < typename T > auto operator==(MyApoint3d< T > const &a, MyApoint3d< T > const &b) -> bool;
template < typename T > auto operator+(MyApoint3d< T > const &a, MyApoint3d< T > const &b) -> MyApoint3d< T >;
template < typename T > auto operator-(MyApoint3d< T > const &a, MyApoint3d< T > const &b) -> MyApoint3d< T >;
template < typename T > auto operator*(MyApoint3d< T > const &a, T b) -> MyApoint3d< T >;
template < typename T > auto operator/(MyApoint3d< T > const &a, T b) -> MyApoint3d< T >;

using point3d = MyApoint3d< short >;

#endif // MY_POINT3D_HPP
