//
// Copyright goblinhack@gmail.com
//

#include <SDL_mixer.h>
#include <map>

#include "my_callstack.hpp"
#include "my_file.hpp"
#include "my_game.hpp"
#include "my_ptrcheck.hpp"
#include "my_sound.hpp"

class sound
{
public:
  sound(std::string valias) : alias(valias) {}

  ~sound(void)
  {
    Mix_FreeChunk(chunk);
    myfree(data);
  }

  std::string    alias;
  Mix_Chunk     *chunk = {};
  unsigned char *data  = {};
  int            len   = {};
  float          volume {};
};

static std::unordered_map< std::string, class sound * > all_sound;

static bool sound_init_done;

bool sound_init(void)
{
  TRACE_NO_INDENT();
  Mix_AllocateChannels(16);

  sound_init_done = true;

  return true;
}

void sound_fini(void)
{
  LOG("Sound fini");
  TRACE_NO_INDENT();

  if (sound_init_done) {
    sound_init_done = false;

    for (;;) {
      auto iter = all_sound.begin();
      if (iter == all_sound.end()) {
        break;
      }
      delete iter->second;
      iter = all_sound.erase(iter);
    }
  }
  all_sound.clear();
}

bool sound_load(float volume, const char *file_in, const char *alias_in)
{
  TRACE_NO_INDENT();
  auto file  = std::string(file_in);
  auto alias = std::string(alias_in);

  return sound_load(volume, file, alias);
}

bool sound_load(float volume, const std::string &file, const std::string &alias)
{
  TRACE_NO_INDENT();
  if (alias == "") {
    auto s = sound_find(alias);
    if (s) {
      return true;
    }
  }

  auto *s = new sound(alias);

  s->volume = volume;
  s->data   = file_load(file.c_str(), &s->len);
  if (! s->data) {
    ERR("Cannot load sound [%s]", file.c_str());
    delete s;
    return false;
  }

  SDL_RWops *rw;

  rw = SDL_RWFromMem(s->data, s->len);
  if (! rw) {
    ERR("SDL_RWFromMem fail [%s]: %s %s", file.c_str(), Mix_GetError(), SDL_GetError());
    SDL_ClearError();
    delete s;
    return false;
  }

  s->chunk = Mix_LoadWAV_RW(rw, false /* A non-zero value mean is will automatically close/free the src for you. */);
  if (! s->chunk) {
    ERR("Mix_LoadWAV_RW fail [%s]: %s %s", file.c_str(), Mix_GetError(), SDL_GetError());
    SDL_ClearError();
    SDL_RWclose(rw);
    delete s;
    return false;
  }

  auto result = all_sound.insert(std::make_pair(alias, s));
  if (! result.second) {
    ERR("Cannot insert sound name [%s]", alias.c_str());
    SDL_RWclose(rw);
    delete s;
    return false;
  }

  SDL_RWclose(rw);
  // DBG("Load %s", file.c_str());

  return true;
}

//
// Find an existing pice of sound.
//
bool sound_find(const std::string &alias)
{
  TRACE_NO_INDENT();
  auto result = all_sound.find(alias);
  return result != all_sound.end();
}

bool sound_play(Gamep g, const std::string &alias)
{
  TRACE_NO_INDENT();

  DBG2("Play sound %s", alias.c_str());

  auto sound = all_sound.find(alias);
  if (sound == all_sound.end()) {
    ERR("Cannot find sound %s", alias.c_str());
    return false;
  }

  if (! sound->second) {
    ERR("Cannot find sound data %s", alias.c_str());
    return false;
  }

  float volume = sound->second->volume * (((float) game_sound_volume_get(g)) / ((float) MIX_MAX_VOLUME));

  volume *= MIX_MAX_VOLUME;

  if (! sound->second->chunk) {
    ERR("Cannot find sound chunk %s", alias.c_str());
    return false;
  }

  Mix_VolumeChunk(sound->second->chunk, (int) volume);

  if (Mix_PlayChannel(-1 /* first free channel */, sound->second->chunk, 0 /* loops */) == -1) {
    DBG2("Cannot play sound %s on any channel", alias.c_str());
    Mix_HaltChannel(0);
    SDL_ClearError();

    if (Mix_PlayChannel(-1 /* first free channel */, sound->second->chunk, 0 /* loops */) == -1) {
      ERR("Cannot play sound %s: %s", alias.c_str(), Mix_GetError());
      SDL_ClearError();
    }
  }

  return true;
}

bool sound_play_optional(Gamep g, const std::string &alias)
{
  TRACE_NO_INDENT();

  DBG2("Play sound %s", alias.c_str());

  auto sound = all_sound.find(alias);
  if (sound == all_sound.end()) {
    ERR("Cannot find sound %s", alias.c_str());
    return false;
  }

  if (! sound->second) {
    ERR("Cannot find sound data %s", alias.c_str());
    return false;
  }

  float volume = sound->second->volume * (((float) game_sound_volume_get(g)) / ((float) MIX_MAX_VOLUME));

  volume *= MIX_MAX_VOLUME;

  if (! sound->second->chunk) {
    ERR("Cannot find sound chunk %s", alias.c_str());
    return false;
  }

  Mix_VolumeChunk(sound->second->chunk, (int) volume);

  if (Mix_PlayChannel(-1 /* first free channel */, sound->second->chunk, 0 /* loops */) == -1) {
    DBG2("Cannot play sound %s on any channel", alias.c_str());
  }

  return true;
}

bool sound_play_channel(Gamep g, int channel, const std::string &alias)
{
  TRACE_NO_INDENT();

  DBG2("Play sound %s on channel %d", alias.c_str(), channel);

  auto sound = all_sound.find(alias);
  if (sound == all_sound.end()) {
    ERR("Cannot find sound %s", alias.c_str());
    return false;
  }

  if (! sound->second) {
    ERR("Cannot find sound data %s", alias.c_str());
    return false;
  }

  float volume = sound->second->volume * (((float) game_sound_volume_get(g)) / ((float) MIX_MAX_VOLUME));

  volume *= MIX_MAX_VOLUME;

  Mix_VolumeChunk(sound->second->chunk, (int) volume);

  if (Mix_Playing(channel)) {
    if (Mix_PlayChannel(-1, sound->second->chunk, 0 /* loops */) == -1) {
      DBG2("Cannot play sound %s on channel %d", alias.c_str(), channel);
      return false;
    }
    return true;
  }

  if (! sound->second->chunk) {
    ERR("Cannot find sound chunk %s", alias.c_str());
    return false;
  }

  if (Mix_PlayChannel(channel, sound->second->chunk, 0 /* loops */) == -1) {
    if (Mix_PlayChannel(-1, sound->second->chunk, 0 /* loops */) == -1) {
      DBG2("Cannot play sound %s on channel %d", alias.c_str(), channel);
      return false;
    }
  }

  return true;
}

void sound_halt(void) { TRACE_NO_INDENT(); }
