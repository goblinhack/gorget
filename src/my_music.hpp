//
// Copyright goblinhack@gmail.com
//

#ifndef MY_MUSIC_HPP
#define MY_MUSIC_HPP

#include "my_types.hpp"

#include <string>

[[nodiscard]] auto music_init() -> bool;
[[nodiscard]] auto music_load(Gamep g, uint32_t rate, const char *file, const char *name) -> bool;
[[nodiscard]] auto music_play(Gamep g, const std::string &name) -> bool;
[[nodiscard]] auto music_halt() -> bool;

auto music_fini() -> void;
auto music_update_volume(Gamep g) -> void;
auto music_load(Gamep g) -> void;

#endif
