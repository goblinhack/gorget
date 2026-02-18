//
// Copyright goblinhack@gmail.com
//

#pragma once

#include <string>
#include <unordered_map>

using ramdisk_t = struct ramdisk_t_ {
  const unsigned char *data;
  int                  len;
};

extern std::unordered_map< std::string, ramdisk_t_ > ramdisk_data;

extern unsigned char *ramdisk_load(const char *filename, int *outlen);
extern void           ramdisk_init();
