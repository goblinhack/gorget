//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_sound.hpp"

void sounds_init(void)
{
  TRACE_NO_INDENT();

  if (! sound_load(0.1f, "data/sounds/interface/keypress.ogg", "keypress")) {
    return;
  }
  if (! sound_load(0.2f, "data/sounds/interface/click2.ogg", "click")) {
    return;
  }
  if (! sound_load(0.1f, "data/sounds/impacts/oof.ogg", "oof")) {
    return;
  }
  if (! sound_load(0.5f, "data/sounds/impacts/ouch.ogg", "ouch")) {
    return;
  }
  if (! sound_load(0.2f, "data/sounds/misc/fall.ogg", "fall")) {
    return;
  }
  if (! sound_load(0.2f, "data/sounds/misc/teleport.ogg", "teleport")) {
    return;
  }
  if (! sound_load(0.5f, "data/sounds/interface/error.ogg", "error")) {
    return;
  }
  if (! sound_load(1.0f, "data/sounds/impacts/explosion.ogg", "explosion", 3 /* concurrent_max */)) {
    return;
  }
  if (! sound_load(1.0f, "data/sounds/impacts/door_stone.ogg", "door_secret", 2)) {
    return;
  }
  if (! sound_load(1.0f, "data/sounds/impacts/door_open.ogg", "door", 2)) {
    return;
  }
  if (! sound_load(1.0f, "data/sounds/impacts/splash.ogg", "splash")) {
    return;
  }
  if (! sound_load(1.0f, "data/sounds/misc/footsteps.ogg", "footstep")) {
    return;
  }
  if (! sound_load(1.0f, "data/sounds/missiles/arrow.ogg", "fireball")) {
    return;
  }
}
