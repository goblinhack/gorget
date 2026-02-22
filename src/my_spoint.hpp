//
// Copyright goblinhack@gmail.com
//

#ifndef MY_SPOINT_HPP_
#define MY_SPOINT_HPP_

using spoint = struct my_spoint {
public:
  short x;
  short y;

#if 0
  my_spoint(const struct my_spoint &a) : x(a.x), y(a.y) {}
  my_spoint(short _x, short _y) : x(_x), y(_y) {}
  my_spoint(void) : x(0), y(0) {}
#endif
  void               operator+=(my_spoint const &b);
  void               operator-=(my_spoint const &b);
  void               operator*=(short b);
  void               operator/=(short b);
  [[nodiscard]] auto length() const -> float;
  void               unit();
};

auto operator<(spoint const &a, spoint const &b) -> bool; // Needed for std::map
auto operator==(spoint const &a, spoint const &b) -> bool;
auto operator+(spoint const &a, spoint const &b) -> spoint;
auto operator-(spoint const &a, spoint const &b) -> spoint;
auto operator*(spoint const &a, short b) -> spoint;
auto operator/(spoint const &a, short b) -> spoint;

static inline auto make_spoint(const spoint &f) -> spoint { return spoint(f.x, f.y); }
static inline auto make_spoint(spoint &f) -> spoint { return spoint(f.x, f.y); }
static inline auto make_spoint(short x, short y) -> spoint { return spoint(x, y); }

auto distance(spoint a, spoint b) -> float;

#endif // _MY_SPOINT_HPP_
