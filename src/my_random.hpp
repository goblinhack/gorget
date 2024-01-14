#pragma once
#ifndef _MY_RANDOM_HPP_
#define _MY_RANDOM_HPP_

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
#define pcg_rand()                       pcg32_random()
#define pcg_srand(a)                     pcg32_srandom(a, a)
#define pcg_random_range(a, b)           (pcg32_boundedrand((b) - (a)) + (a))
#define pcg_random_range_inclusive(a, b) (pcg32_boundedrand((b) - (a) + 1) + (a))

#endif
