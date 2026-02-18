//
// Copyright goblinhack@gmail.com
//

#include "my_line.hpp"

#include <cmath>
#include <vector>

std::vector< spoint > draw_line(const spoint s, const spoint e, size_t max_elems)
{
  std::vector< spoint > out;

  int x0 = s.x;
  int y0 = s.y;
  int x1 = e.x;
  int y1 = e.y;

  int dx  = abs(x1 - x0);
  int sx  = x0 < x1 ? 1 : -1;
  int dy  = -abs(y1 - y0);
  int sy  = y0 < y1 ? 1 : -1;
  int err = dx + dy;
  int e2; /* error value e_xy */

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
