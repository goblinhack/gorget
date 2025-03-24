//
// Copyright goblinhack@gmail.com
//

#include "my_serialize.hpp"

std::istream &operator>>(std::istream &in, Bits< point & > my)
{
  in >> bits(my.t.x) >> bits(my.t.y);
  return in;
}

std::ostream &operator<<(std::ostream &out, Bits< const point & > const my)
{
  out << bits(my.t.x) << bits(my.t.y);
  return out;
}

std::istream &operator>>(std::istream &in, Bits< fpoint & > my)
{
  in >> bits(my.t.x) >> bits(my.t.y);
  return in;
}

std::ostream &operator<<(std::ostream &out, Bits< const fpoint & > const my)
{
  out << bits(my.t.x) << bits(my.t.y);
  return out;
}
