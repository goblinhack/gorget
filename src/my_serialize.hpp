//
// Copyright goblinhack@gmail.com
//

#pragma once
#ifndef _MY_SERIALIZE_HPP_
#define _MY_SERIALIZE_HPP_

#include "c_plus_plus_serializer.hpp"
#include "my_hiscore.hpp"
#include "my_point.hpp"

#include <SDL.h>

std::istream &operator>>(std::istream &in, Bits< point & > my);
std::ostream &operator<<(std::ostream &out, Bits< const point & > const my);
std::istream &operator>>(std::istream &in, Bits< fpoint & > my);
std::ostream &operator<<(std::ostream &out, Bits< const fpoint & > const my);
std::ostream &operator<<(std::ostream &out, Bits< const HiScore & > const my);  // save
std::istream &operator>>(std::istream &in, Bits< HiScore & > my);               // load
std::ostream &operator<<(std::ostream &out, Bits< const HiScores & > const my); // save
std::istream &operator>>(std::istream &in, Bits< HiScores & > my);              // load
std::istream &operator>>(std::istream &in, Bits< SDL_Keysym & > my);
std::ostream &operator<<(std::ostream &out, Bits< const SDL_Keysym & > const my);

#endif
