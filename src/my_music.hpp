//
// Copyright goblinhack@gmail.com
//

#ifndef MY_MUSIC_HPP_
#define MY_MUSIC_HPP_

bool music_init();
void music_fini();
bool music_load(uint32_t rate, const char *file, const char *name);
bool music_find(const char * /*name_alias*/);
bool music_play(Gamep g, const char *name);
bool music_halt();
void music_update_volume(Gamep g);

#endif
