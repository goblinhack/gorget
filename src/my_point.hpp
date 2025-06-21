//
// Copyright goblinhack@gmail.com
//

#pragma once
#ifndef _MY_POINT_HPP_
#define _MY_POINT_HPP_

typedef struct my_spoint {
public:
  short x;
  short y;

  void  operator+=(my_spoint const &);
  void  operator-=(my_spoint const &);
  void  operator*=(short);
  void  operator/=(short);
  float length(void) const;
  void  unit(void);
} spoint;

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

bool   operator<(spoint const &a, spoint const &b); // Needed for std::map
bool   operator==(spoint const &, spoint const &);
spoint operator+(spoint const &, spoint const &);
spoint operator-(spoint const &, spoint const &);
spoint operator*(spoint const &, short);
spoint operator/(spoint const &, short);

bool   operator==(fpoint const &, fpoint const &);
fpoint operator+(fpoint const &, fpoint const &);
fpoint operator-(fpoint const &, fpoint const &);
fpoint operator*(fpoint const &, float);
fpoint operator/(fpoint const &, float);

static inline fpoint make_fpoint(const float x = 0, const float y = 0) { return fpoint(x, y); }
static inline fpoint make_fpoint(const spoint &f) { return fpoint(f.x, f.y); }

fpoint rotate_radians(float angle, const fpoint &p, const fpoint &origin);
fpoint rotate_radians(const fpoint &p, float angle);
fpoint normal(const fpoint &p);
fpoint unit(const fpoint &p);

float distance(const fpoint &a, const fpoint &b);
float distance(const spoint a, const spoint b);
float angle_radians(const fpoint &p);

#endif // _MY_POINT_HPP_
