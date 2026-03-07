//
// Copyright goblinhack@gmail.com
//

#ifndef MY_RAMDISK_HPP
#define MY_RAMDISK_HPP

#include <string>
#include <unordered_map>

using ramdisk_t = struct RamdiskT {
  const uint8_t *data;
  int                  len;
};

extern std::unordered_map< std::string, RamdiskT > ramdisk_data;

extern auto ramdisk_load(const char *filename, int *outlen) -> uint8_t *;
extern void           ramdisk_init();

#endif
