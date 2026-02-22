//
// Copyright goblinhack@gmail.com
//

#ifndef MY_MUSIC_HPP_
#define MY_MUSIC_HPP_

auto music_init() -> bool;
void music_fini();
auto music_load(uint32_t rate, const char *file, const char *name) -> bool;
auto music_find(const char * /*name_alias*/) -> bool;
auto music_play(Gamep g, const char *name) -> bool;
auto music_halt() -> bool;
void music_update_volume(Gamep g);

#endif
