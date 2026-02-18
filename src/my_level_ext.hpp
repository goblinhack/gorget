//
// Copyright goblinhack@gmail.com
//

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
using Override  = std::function< Tpp(char, spoint) >;
using Overrides = std::map< char, Override >;

extern Overrides no_overrides;

void level_fixed_add(Gamep g, int chance, LevelType /*level_type*/, const std::string &alias, const char * /*file*/,
                     int line, Overrides /*overrides*/, ...);
[[nodiscard]] bool level_populate(Gamep g, Levelsp v, Levelp l, class LevelGen * /*level_gen*/, const char * /*in*/,
                                  Overrides /*overrides*/ = no_overrides);
[[nodiscard]] bool level_populate(Gamep g, Levelsp v, Levelp l, class LevelGen * /*level_gen*/, int w, int h,
                                  const char * /*in*/, Overrides /*overrides*/ = no_overrides);

#endif
