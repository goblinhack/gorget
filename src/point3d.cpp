//
// Copyright goblinhack@gmail.com
//

#include "my_point3d.hpp"

template < typename T > auto operator+(MyApoint3d< T > const &a, MyApoint3d< T > const &b) -> MyApoint3d< T >
{
  return MyApoint3d< T >(a.x + b.x, a.y + b.y, a.z + b.z);
}
template MyApoint3d< short > operator+ < short >(MyApoint3d< short > const &, MyApoint3d< short > const &);
template MyApoint3d< float > operator+ < float >(MyApoint3d< float > const &, MyApoint3d< float > const &);

template < typename T > auto operator-(MyApoint3d< T > const &a, MyApoint3d< T > const &b) -> MyApoint3d< T >
{
  return MyApoint3d< T >(a.x - b.x, a.y - b.y, a.z - b.z);
}
template MyApoint3d< short > operator- < short >(MyApoint3d< short > const &, MyApoint3d< short > const &);
template MyApoint3d< float > operator- < float >(MyApoint3d< float > const &, MyApoint3d< float > const &);

template < typename T > auto operator*(MyApoint3d< T > const &a, T b) -> MyApoint3d< T >
{
  return MyApoint3d< T >(a.x * b, a.y * b, a.z * b);
}
template MyApoint3d< short > operator* < short >(MyApoint3d< short > const &, short);
template MyApoint3d< float > operator* < float >(MyApoint3d< float > const &, float);

template < typename T > auto operator/(MyApoint3d< T > const &a, T b) -> MyApoint3d< T >
{
  return MyApoint3d< T >(a.x / b, a.y / b, a.z / b);
}
template MyApoint3d< short > operator/ < short >(MyApoint3d< short > const &, short);
template MyApoint3d< float > operator/ < float >(MyApoint3d< float > const &, float);

template < typename T > auto operator==(MyApoint3d< T > const &a, MyApoint3d< T > const &b) -> bool
{
  return (a.x == b.x) && (a.y == b.y) && (a.z == b.z);
}
template bool operator== < short >(MyApoint3d< short > const &, MyApoint3d< short > const &);
template bool operator== < float >(MyApoint3d< float > const &, MyApoint3d< float > const &);

template < typename T > void MyApoint3d< T >::operator+=(MyApoint3d< T > const &b)
{
  x += b.x;
  y += b.y;
  z += b.z;
}
template void MyApoint3d< short >::operator+=(MyApoint3d< short > const &);
template void MyApoint3d< float >::operator+=(MyApoint3d< float > const &);

template < typename T > void MyApoint3d< T >::operator-=(MyApoint3d< T > const &b)
{
  x -= b.x;
  y -= b.y;
  z -= b.z;
}
template void MyApoint3d< short >::operator-=(MyApoint3d< short > const &);
template void MyApoint3d< float >::operator-=(MyApoint3d< float > const &);

template < typename T > void MyApoint3d< T >::operator*=(T b)
{
  x *= b;
  y *= b;
  z *= b;
}
template void MyApoint3d< short >::operator*=(short);
template void MyApoint3d< float >::operator*=(float);

template < typename T > void MyApoint3d< T >::operator/=(T b)
{
  x /= b;
  y /= b;
  z /= b;
}
template void MyApoint3d< short >::operator/=(short);
template void MyApoint3d< float >::operator/=(float);
