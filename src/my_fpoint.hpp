//
// Copyright goblinhack@gmail.com
//

#pragma once
#ifndef _MY_FPOINT_HPP_
#define _MY_FPOINT_HPP_

#include "my_spoint.hpp"

#include <math.h>

typedef struct my_fpoint {
public:
  float x;
  float y;

  void  operator+=(my_fpoint const & /*b*/);
  void  operator-=(my_fpoint const & /*b*/);
  void  operator*=(float /*b*/);
  void  operator/=(float /*b*/);
  float length(void) const;
  void  unit(void);
} fpoint;

bool   operator==(fpoint const & /*a*/, fpoint const & /*b*/);
fpoint operator+(fpoint const & /*a*/, fpoint const & /*b*/);
fpoint operator-(fpoint const & /*a*/, fpoint const & /*b*/);
fpoint operator*(fpoint const & /*a*/, float /*b*/);
fpoint operator/(fpoint const & /*a*/, float /*b*/);

fpoint rotate_radians(float angle, const fpoint &p, const fpoint &origin);
fpoint rotate_radians(const fpoint &p, float angle);
fpoint normal(const fpoint &p);
fpoint unit(const fpoint &p);

float distance(const fpoint &a, const fpoint &b);
float angle_radians(const fpoint &p);
int   distance_to_line(fpoint P0, fpoint L0, fpoint L1, float *dist, fpoint *intersect_out);

static inline fpoint make_fpoint(const spoint f) { return fpoint(f.x, f.y); }

//
// round() is better than floor() as if we do a jump on a diagonal, that is 0.707
// units. We want to round to 1.0 so the diagonal move works and not 0.0.
//
static inline spoint make_spoint(const fpoint &f) { return spoint((int) roundf(f.x), (int) roundf(f.y)); }

#endif // _MY_FPOINT_HPP_
