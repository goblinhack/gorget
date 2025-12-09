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

  void  operator+=(my_fpoint const &);
  void  operator-=(my_fpoint const &);
  void  operator*=(float);
  void  operator/=(float);
  float length(void) const;
  void  unit(void);
} fpoint;

bool   operator==(fpoint const &, fpoint const &);
fpoint operator+(fpoint const &, fpoint const &);
fpoint operator-(fpoint const &, fpoint const &);
fpoint operator*(fpoint const &, float);
fpoint operator/(fpoint const &, float);

fpoint rotate_radians(float angle, const fpoint &p, const fpoint &origin);
fpoint rotate_radians(const fpoint &p, float angle);
fpoint normal(const fpoint &p);
fpoint unit(const fpoint &p);

float distance(const fpoint &a, const fpoint &b);
float angle_radians(const fpoint &p);

static inline fpoint make_fpoint(const spoint f) { return fpoint(f.x, f.y); }

static inline spoint make_spoint(const fpoint &f) { return spoint((int) floor(f.x), (int) floor(f.y)); }

#endif // _MY_FPOINT_HPP_
