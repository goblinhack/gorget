//
// Copyright goblinhack@gmail.com
//

#ifndef MY_LINE_HPP_
#define MY_LINE_HPP_

#include "my_spoint.hpp"

#include <vector>

auto draw_line(spoint s, spoint e, size_t max_elems = -1) -> std::vector< spoint >;

#endif
