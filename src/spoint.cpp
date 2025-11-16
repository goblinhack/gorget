//
// Copyright goblinhack@gmail.com
//

#include "my_math.hpp"
#include "my_spoint.hpp"

#include <math.h>

bool   operator<(spoint const &a, spoint const &b) { return (a.x < b.x) || (a.x == b.x && a.y < b.y); }
spoint operator+(spoint const &a, spoint const &b) { return spoint(a.x + b.x, a.y + b.y); }
spoint operator-(spoint const &a, spoint const &b) { return spoint(a.x - b.x, a.y - b.y); }
spoint operator*(spoint const &a, short b) { return spoint(a.x * b, a.y * b); }
spoint operator/(spoint const &a, short b) { return spoint(a.x / b, a.y / b); }
bool   operator==(spoint const &a, spoint const &b) { return (a.x == b.x) && (a.y == b.y); }

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

float spoint::length(void) const { return ((float) sqrt(x * x + y * y)); }

void spoint::unit(void)
{
  short len = (int) sqrt(x * x + y * y);
  x /= len;
  y /= len;
}

float distance(const spoint a, const spoint b)
{
  return (float) DISTANCEf((float) a.x, (float) a.y, (float) b.x, (float) b.y);
}
