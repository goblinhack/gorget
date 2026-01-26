//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_sound.hpp"

void sounds_init(void)
{
  TRACE_NO_INDENT();

  sound_load(0.1f, "data/sounds/impacts/oof.mp3", "oof");
  sound_load(0.5f, "data/sounds/impacts/ouch.mp3", "ouch");
  sound_load(0.1f, "data/sounds/interface/keypress.mp3", "keypress");
  sound_load(0.2f, "data/sounds/interface/click2.mp3", "click");
  sound_load(0.2f, "data/sounds/misc/fall.mp3", "fall");
  sound_load(0.2f, "data/sounds/misc/teleport.mp3", "teleport");
  sound_load(0.5f, "data/sounds/interface/error.mp3", "error");
  sound_load(1.0f, "data/sounds/impacts/explosion.mp3", "explosion", 3 /* concurrent_max */);
  sound_load(1.0f, "data/sounds/impacts/door_stone.mp3", "door_secret", 2);
  sound_load(1.0f, "data/sounds/impacts/door_open.mp3", "door", 2);
  sound_load(1.0f, "data/sounds/impacts/splash.mp3", "splash");
  sound_load(1.0f, "data/sounds/misc/footsteps.mp3", "footstep");
  sound_load(1.0f, "data/sounds/missiles/arrow.mp3", "fireball");
  sound_load(1.0f, "data/sounds/treasure/keys.mp3", "keys");
}
