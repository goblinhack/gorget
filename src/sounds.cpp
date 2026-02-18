//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_sound.hpp"

void sounds_init(void)
{
  TRACE_NO_INDENT();

  if (! sound_load(0.1F, "data/sounds/interface/keypress.ogg", "keypress")) {
    return;
  }
  if (! sound_load(0.2F, "data/sounds/interface/mouse-click.ogg", "click")) {
    return;
  }
  if (! sound_load(0.1F, "data/sounds/impacts/player-oof.ogg", "oof")) {
    return;
  }
  if (! sound_load(0.5F, "data/sounds/impacts/player-ouch.ogg", "ouch")) {
    return;
  }
  if (! sound_load(0.2F, "data/sounds/misc/fall.ogg", "fall")) {
    return;
  }
  if (! sound_load(0.2F, "data/sounds/misc/teleport.ogg", "teleport")) {
    return;
  }
  if (! sound_load(0.5F, "data/sounds/interface/error.ogg", "error")) {
    return;
  }
  if (! sound_load(1.0F, "data/sounds/impacts/explosion.ogg", "explosion", 10 /* concurrent_max */)) {
    return;
  }
  if (! sound_load(1.0F, "data/sounds/impacts/door_stone.ogg", "door_secret", 2)) {
    return;
  }
  if (! sound_load(1.0F, "data/sounds/impacts/door_open.ogg", "door", 2)) {
    return;
  }
  if (! sound_load(1.0F, "data/sounds/impacts/splash.ogg", "splash")) {
    return;
  }
  if (! sound_load(1.0F, "data/sounds/misc/footsteps.ogg", "footstep")) {
    return;
  }
  if (! sound_load(1.0F, "data/sounds/missiles/arrow.ogg", "fireball", 5)) {
    return;
  }
  if (! sound_load(1.0F, "data/sounds/treasure/key.ogg", "key")) {
    return;
  }
}
