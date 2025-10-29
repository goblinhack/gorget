//
// Copyright goblinhack@gmail.com
//

#pragma once

#include <stdlib.h>

#ifndef _MY_MATH_UTIL_HPP_
#define _MY_MATH_UTIL_HPP_

#ifdef __APPLE__
#define sincos(x, s, c)  __sincos(x, s, c)
#define sincosf(x, s, c) __sincosf(x, s, c)
#define sincos(x, s, c)  __sincos(x, s, c)
#endif

#undef SQUARED
#define SQUARED(x) ((x) * (x))

#define ROUNDUP(x, r) ((r) * floor(((x) + (r)) / (r)))

#define DISTANCEf(xa, ya, xb, yb) sqrtf((float) (SQUARED((xb) - (xa)) + SQUARED((yb) - (ya))))
#define DISTANCEd(xa, ya, xb, yb) sqrt((double) (SQUARED((xb) - (xa)) + SQUARED((yb) - (ya))))

#define PI      3.14159265358979323846f        // pi
#define RAD_45  0.78539816339744830962f        // pi/4
#define RAD_90  1.57079632679489661923f        // pi/2
#define RAD_180 3.14159265358979323846f        // pi
#define RAD_360 (2.0 * 3.14159265358979323846) // 2pi
#define RAD_270 (RAD_180 + RAD_90)

unsigned int nextpoweroftwo(unsigned int val);

#endif
