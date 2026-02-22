//
// Copyright goblinhack@gmail.com
//

#ifndef MY_RAMDISK_HPP_
#define MY_RAMDISK_HPP_

#include <string>
#include <unordered_map>

using ramdisk_t = struct ramdisk_t_ {
  const unsigned char *data;
  int                  len;
};

extern std::unordered_map< std::string, ramdisk_t_ > ramdisk_data;

extern auto ramdisk_load(const char *filename, int *outlen) -> unsigned char *;
extern void           ramdisk_init();

#endif
