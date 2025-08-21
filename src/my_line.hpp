//
// Copyright goblinhack@gmail.com
//

#pragma once

#ifndef _MY_LINE_HPP_
#define _MY_LINE_HPP_

#include "my_spoint.hpp"

#include <vector>

std::vector< spoint > draw_line(const spoint s, const spoint e, size_t max_elems = -1);

#endif
