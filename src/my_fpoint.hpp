//
// Copyright goblinhack@gmail.com
//

#ifndef MY_FPOINT_HPP
#define MY_FPOINT_HPP

#include "my_spoint.hpp"

#include <math.h>

using fpoint = struct my_fpoint {
public:
  float x;
  float y;

  void               operator+=(my_fpoint const &b);
  void               operator-=(my_fpoint const &b);
  void               operator*=(float b);
  void               operator/=(float b);
  [[nodiscard]] auto length() const -> float;
  void               unit();
};

auto operator==(fpoint const &a, fpoint const &b) -> bool;
auto operator+(fpoint const &a, fpoint const &b) -> fpoint;
auto operator-(fpoint const &a, fpoint const &b) -> fpoint;
auto operator*(fpoint const &a, float b) -> fpoint;
auto operator/(fpoint const &a, float b) -> fpoint;

auto rotate_radians(float angle, const fpoint &p, const fpoint &origin) -> fpoint;
auto rotate_radians(const fpoint &p, float angle) -> fpoint;
auto normal(const fpoint &p) -> fpoint;
auto unit(const fpoint &p) -> fpoint;

auto distance(const fpoint &a, const fpoint &b) -> float;
auto angle_radians(const fpoint &p) -> float;
auto distance_to_line(fpoint P0, fpoint L0, fpoint L1, float *dist, fpoint *intersect_out) -> int;

static inline auto make_fpoint(const spoint f) -> fpoint { return fpoint(f.x, f.y); }

//
// round() is better than floor() as if we do a jump on a diagonal, that is 0.707
// units. We want to round to 1.0 so the diagonal move works and not 0.0.
//
static inline auto make_spoint(const fpoint &f) -> spoint { return spoint((int) roundf(f.x), (int) roundf(f.y)); }

#endif // _MY_FPOINT_HPP
