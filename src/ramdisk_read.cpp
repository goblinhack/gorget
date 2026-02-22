//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_globals.hpp"
#include "my_main.hpp"
#include "my_ptrcheck.hpp"
#include "my_ramdisk.hpp"

#include <cstdlib>
#include <cstring>

std::unordered_map< std::string, ramdisk_t_ > ramdisk_data;

auto ramdisk_load(const char *filename, int *outlen) -> unsigned char *
{
  TRACE_NO_INDENT();

  auto f = ramdisk_data.find(filename);
  if (f == ramdisk_data.end()) {
    return nullptr;
  }

  auto ramfile = f->second;

  auto *out = mymalloc(ramfile.len + 1, "ramdisk load");
  if (out == nullptr) {
    ERR("No memory for loading ramdisk out, %s", filename);
    return nullptr;
  }

  memcpy(out, (unsigned char *) ramfile.data, ramfile.len);
  *((unsigned char *) out + ramfile.len) = 0;
  *outlen                                = ramfile.len;

  return (unsigned char *) out;
}
