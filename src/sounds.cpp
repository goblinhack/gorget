//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_sound.hpp"

void sounds_init(void)
{
  TRACE_NO_INDENT();

  sound_load(0.1f, "data/sounds/impacts/oof.wav", "oof");
  sound_load(0.1f, "data/sounds/interface/keypress.wav", "keypress");
  sound_load(0.2f, "data/sounds/interface/click2.wav", "click");
  sound_load(0.2f, "data/sounds/misc/fall.wav", "fall");
  sound_load(0.2f, "data/sounds/misc/teleport.wav", "teleport");
  sound_load(0.5f, "data/sounds/interface/error.wav", "error");
  sound_load(1.0f, "data/sounds/impacts/explosion.wav", "explosion");
  sound_load(1.0f, "data/sounds/impacts/door_stone.wav", "secret_door");
  sound_load(1.0f, "data/sounds/impacts/splash.wav", "splash");
  sound_load(1.0f, "data/sounds/misc/footsteps.wav", "footstep");
}
