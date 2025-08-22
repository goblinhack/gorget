//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_sound.hpp"

void sounds_init(void)
{
  TRACE_NO_INDENT();

  sound_load(0.2, "data/sounds/interface/click2.wav", "click");
  sound_load(0.5, "data/sounds/interface/error.wav", "error");
  sound_load(0.1, "data/sounds/interface/keypress.wav", "keypress");
  sound_load(1.0, "data/sounds/misc/footsteps.wav", "footstep");
  sound_load(1.0, "data/sounds/impacts/splash.wav", "splash");
  sound_load(0.5, "data/sounds/impacts/oof.wav", "oof");
  sound_load(0.2, "data/sounds/misc/fall.wav", "fall");
  sound_load(0.2, "data/sounds/misc/teleport.wav", "teleport");
}
