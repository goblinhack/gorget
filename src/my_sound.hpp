//
// Copyright goblinhack@gmail.com
//

#ifndef MY_SOUND_HPP
#define MY_SOUND_HPP

#include "my_game.hpp"

#include <string>

class Sound;
using soundp = class Sound *;

[[nodiscard]] auto sound_init() -> bool;
[[nodiscard]] auto sound_load(float volume, const std::string &name, const std::string &alias, int concurrent_max = 1) -> bool;
[[nodiscard]] auto sound_play(Gamep g, Levelsp v, Levelp l, const std::string &alias, float scale = 1.0, int loops = 0, Thingp me = nullptr)
    -> bool;
[[nodiscard]] auto sound_play(Gamep g, const std::string &alias, float scale = 1.0, int loops = 0) -> bool;

auto sound_fini() -> void;
auto sounds_load(Gamep g) -> void;
auto sound_fade_out(Gamep g) -> void;

enum {
  CHANNEL_MISC,
  CHANNEL_FOOTSTEPS,
  CHANNEL_IMPACT,
  CHANNEL_MONST,
  CHANNEL_MONST_DEATH,
  CHANNEL_MONST_BIRTH,
  CHANNEL_WEAPON,
  CHANNEL_EXPLOSION,
};

#endif
