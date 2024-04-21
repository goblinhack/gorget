/*
 * Copyright (C) 2011-2020 goblinhack@gmail.com
 *
 * See the README file for license info.
 */

#pragma once

#ifndef _MY_SOUND_HPP_
#define _MY_SOUND_HPP_

class sound;
using soundp = class sound *;

bool sound_init(void);
void sound_fini(void);
bool sound_load(float volume, const std::string &file, const std::string &alias);
bool sound_load(float volume, const char *file, const char *alias);
bool sound_find(const std::string &alias);
bool sound_play(const std::string &alias);
bool sound_play_channel(int chan, const std::string &alias);
void sound_halt(void);

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
