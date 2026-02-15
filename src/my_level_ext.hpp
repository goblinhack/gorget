//
// Copyright goblinhack@gmail.com
//

#pragma once
#ifndef _MY_LEVEL_EXT_HPP
#define _MY_LEVEL_EXT_HPP

#include "my_level.hpp"
#include "my_spoint.hpp"
#include "my_tp.hpp"

#include <functional>
#include <map>

//
// Overriding specific characters
//
typedef std::function< Tpp(char, spoint) > Override;
typedef std::map< char, Override >         Overrides;

extern Overrides no_overrides;

void level_fixed_add(Gamep, int chance, LevelType, const std::string &alias, const char *, int line, Overrides, ...);
[[nodiscard]] bool level_populate(Gamep, Levelsp, Levelp, class LevelGen *, const char *, Overrides = no_overrides);
[[nodiscard]] bool level_populate(Gamep, Levelsp, Levelp, class LevelGen *, int w, int h, const char *,
                                  Overrides = no_overrides);

#endif
