//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_sound.hpp"

void sounds_init(void)
{
  TRACE_NO_INDENT();

  if (! sound_load(0.1f, "data/sounds/interface/keypress.wav", "keypress")) {
    return;
  }
  if (! sound_load(0.2f, "data/sounds/interface/click2.wav", "click")) {
    return;
  }
  if (! sound_load(0.1f, "data/sounds/impacts/oof.wav", "oof")) {
    return;
  }
  if (! sound_load(0.5f, "data/sounds/impacts/ouch.wav", "ouch")) {
    return;
  }
  if (! sound_load(0.2f, "data/sounds/misc/fall.wav", "fall")) {
    return;
  }
  if (! sound_load(0.2f, "data/sounds/misc/teleport.wav", "teleport")) {
    return;
  }
  if (! sound_load(0.5f, "data/sounds/interface/error.wav", "error")) {
    return;
  }
  if (! sound_load(1.0f, "data/sounds/impacts/explosion.wav", "explosion", 3 /* concurrent_max */)) {
    return;
  }
  if (! sound_load(1.0f, "data/sounds/impacts/door_stone.wav", "door_secret", 2)) {
    return;
  }
  if (! sound_load(1.0f, "data/sounds/impacts/door_open.wav", "door", 2)) {
    return;
  }
  if (! sound_load(1.0f, "data/sounds/impacts/splash.wav", "splash")) {
    return;
  }
  if (! sound_load(1.0f, "data/sounds/misc/footsteps.wav", "footstep")) {
    return;
  }
  if (! sound_load(1.0f, "data/sounds/missiles/arrow.wav", "fireball")) {
    return;
  }
}
