//
// Copyright goblinhack@gmail.com
//

#ifndef _MY_SPOINT_HPP_
#define _MY_SPOINT_HPP_

using spoint = struct my_spoint {
public:
  short x;
  short y;

#if 0
  my_spoint(const struct my_spoint &a) : x(a.x), y(a.y) {}
  my_spoint(short _x, short _y) : x(_x), y(_y) {}
  my_spoint(void) : x(0), y(0) {}
#endif
  void                operator+=(my_spoint const &b);
  void                operator-=(my_spoint const &b);
  void                operator*=(short b);
  void                operator/=(short b);
  [[nodiscard]] float length() const;
  void                unit();
};

bool   operator<(spoint const &a, spoint const &b); // Needed for std::map
bool   operator==(spoint const &a, spoint const &b);
spoint operator+(spoint const &a, spoint const &b);
spoint operator-(spoint const &a, spoint const &b);
spoint operator*(spoint const &a, short b);
spoint operator/(spoint const &a, short b);

static inline spoint make_spoint(const spoint &f) { return spoint(f.x, f.y); }
static inline spoint make_spoint(spoint &f) { return spoint(f.x, f.y); }
static inline spoint make_spoint(short x, short y) { return spoint(x, y); }

float distance(spoint a, spoint b);

#endif // _MY_SPOINT_HPP_
