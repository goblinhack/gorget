//
// Copyright goblinhack@gmail.com
//

// REMOVED #include "my_math.hpp"

unsigned int nextpoweroftwo(unsigned int val)
{
  val--;
  val = (val >> 1) | val;
  val = (val >> 2) | val;
  val = (val >> 4) | val;
  val = (val >> 8) | val;
  val = (val >> 16) | val;
  val++; // Val is now the next highest power of 2

  return (val);
}
