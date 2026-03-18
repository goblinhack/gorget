//
// Copyright goblinhack@gmail.com
//

#include "my_line.hpp"

#include <cmath>
#include <vector>

auto draw_line(const spoint s, const spoint e, size_t max_elems) -> std::vector< spoint >
{
  std::vector< spoint > out;

  short       x0 = s.x;
  short       y0 = s.y;
  short const x1 = e.x;
  short const y1 = e.y;

  short const dx  = abs(x1 - x0);
  short const sx  = x0 < x1 ? 1 : -1;
  short const dy  = -abs(y1 - y0);
  short const sy  = y0 < y1 ? 1 : -1;
  short       err = dx + dy;
  short       e2  = 0; /* error value e_xy */

  for (;;) { /* loop */
    out.push_back(spoint(x0, y0));

    if (max_elems > 0) {
      if (out.size() >= max_elems) {
        return out;
      }
    }

    if (x0 == x1 && y0 == y1) {
      break;
    }

    e2 = 2 * err;
    if (e2 >= dy) {
      err += dy;
      x0 += sx;
    } /* e_xy+e_x > 0 */
    if (e2 <= dx) {
      err += dx;
      y0 += sy;
    } /* e_xy+e_y < 0 */
  }
  return out;
}

auto draw_line(const bpoint s, const bpoint e, size_t max_elems) -> std::vector< bpoint >
{
  std::vector< bpoint > out;

  int8_t       x0 = s.x;
  int8_t       y0 = s.y;
  int8_t const x1 = e.x;
  int8_t const y1 = e.y;

  int8_t const dx  = abs(x1 - x0);
  int8_t const sx  = x0 < x1 ? 1 : -1;
  int8_t const dy  = -abs(y1 - y0);
  int8_t const sy  = y0 < y1 ? 1 : -1;
  int8_t       err = dx + dy;
  int8_t       e2  = 0; /* error value e_xy */

  for (;;) { /* loop */
    out.push_back(bpoint(x0, y0));

    if (max_elems > 0) {
      if (out.size() >= max_elems) {
        return out;
      }
    }

    if (x0 == x1 && y0 == y1) {
      break;
    }

    e2 = 2 * err;
    if (e2 >= dy) {
      err += dy;
      x0 += sx;
    } /* e_xy+e_x > 0 */
    if (e2 <= dx) {
      err += dx;
      y0 += sy;
    } /* e_xy+e_y < 0 */
  }
  return out;
}
