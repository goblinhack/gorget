//
// Copyright goblinhack@gmail.com
//

#include "my_math.hpp"
#include "my_spoint.hpp"

#include <cmath>

auto operator<(spoint const &a, spoint const &b) -> bool { return (a.x < b.x) || (a.x == b.x && a.y < b.y); }
auto operator+(spoint const &a, spoint const &b) -> spoint { return spoint(a.x + b.x, a.y + b.y); }
auto operator-(spoint const &a, spoint const &b) -> spoint { return spoint(a.x - b.x, a.y - b.y); }
auto operator*(spoint const &a, short b) -> spoint { return spoint(a.x * b, a.y * b); }
auto operator/(spoint const &a, short b) -> spoint { return spoint(a.x / b, a.y / b); }
auto operator==(spoint const &a, spoint const &b) -> bool { return (a.x == b.x) && (a.y == b.y); }

void spoint::operator+=(spoint const &b)
{
  x += b.x;
  y += b.y;
}

void spoint::operator-=(spoint const &b)
{
  x -= b.x;
  y -= b.y;
}

void spoint::operator*=(short b)
{
  x *= b;
  y *= b;
}

void spoint::operator/=(short b)
{
  x /= b;
  y /= b;
}

auto spoint::length() const -> float { return ((float) sqrt((x * x) + (y * y))); }

void spoint::unit()
{
  short const len = (int) sqrt((x * x) + (y * y));
  x /= len;
  y /= len;
}

auto distance(const spoint a, const spoint b) -> float
{
  return (float) DISTANCEf((float) a.x, (float) a.y, (float) b.x, (float) b.y);
}
