//
// Copyright goblinhack@gmail.com
//

#pragma once
#ifndef _MY_SPOINT_HPP_
#define _MY_SPOINT_HPP_

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

bool   operator<(spoint const &a, spoint const &b); // Needed for std::map
bool   operator==(spoint const &, spoint const &);
spoint operator+(spoint const &, spoint const &);
spoint operator-(spoint const &, spoint const &);
spoint operator*(spoint const &, short);
spoint operator/(spoint const &, short);

float distance(const spoint a, const spoint b);

#endif // _MY_SPOINT_HPP_
