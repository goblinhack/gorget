#ifndef MY_RANDOM_HPP_
#define MY_RANDOM_HPP_

////////////////////////////////////////////////////////////////////////////
// Random numbers
////////////////////////////////////////////////////////////////////////////

//
// Enhanced random number mob.
//
#include "my_pcg_basic.hpp"

//
// For randomness that matters for reproducability.
//
#define pcg_rand()                       pcg32_random(__FUNCTION__, __LINE__)
#define pcg_srand(a)                     pcg32_srandom(a, a)
#define pcg_random_range(a, b)           ((b) > (a) ? pcg32_boundedrand(__FUNCTION__, __LINE__, (b) - (a)) + (a) : (a))
#define pcg_random_range_inclusive(a, b) ((b) > (a) ? pcg32_boundedrand(__FUNCTION__, __LINE__, (b) - (a) + 1) + (a) : (a))

//
// For randomness that does not matter for reproducability.
//
#define os_rand()                       rand()
#define os_srand(a)                     srand(a)
#define os_random_range(a, b)           ((b) > (a) ? rand() % ((b) - (a)) + (a) : (a))
#define os_random_range_inclusive(a, b) ((b) > (a) ? rand() % ((b) - (a) + 1) + (a) : (a))

#endif
