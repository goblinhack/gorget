/*
 * Copyright (C) 2011-2020 goblinhack@gmail.com
 *
 * See the README file for license info.
 */

#pragma once

#ifndef _MY_MUSIC_HPP_
#define _MY_MUSIC_HPP_

bool music_init(void);
void music_fini(void);
bool music_load(uint32_t rate, const char *file, const char *name);
bool music_find(const char * /*name_alias*/);
bool music_play(Gamep /*g*/, const char * /*name*/);
bool music_halt(void);
void music_update_volume(Gamep /*g*/);

#endif
