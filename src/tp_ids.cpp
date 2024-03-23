//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_tp.hpp"

//
// Templates can be assigned dynamic IDs - however the levels are more reproducable it
// they have fixed numbers. This list helps to achieve that. It is optional for a template
// to be in this list
//
std::initializer_list< std::string > tps = {
    // clang-format off
    "", // ID 0 means unused
    "wall1",
    "wall2",
    /* begin shell marker1 */
    /* shell for i in $(find . -name "*.cpp" | xargs grep -h "tp_load(\"" | awk '{print $4}' | cut -d\" -f2) */
    /* shell do */
    /* shell echo "    \"$i\"", */
    /* shell done */
    "player",
    "exit",
    "door",
    "key",
    "floor",
  /* end shell marker1 */
};

static std::map< std::string, int > tp_preferred_id;

//
// Assign template IDs
//
void tp_get_id(const std::string &tp_name, int *id_out)
{
  static const std::vector< std::string > tp_arr(tps);

  static int  id;
  static bool init;

  //
  // Assign static IDs
  //
  if (! init) {
    init = true;
    for (auto t : tp_arr) {
      tp_preferred_id[ t ] = id++;
    }
  }

  //
  // Previously known
  //
  if (tp_preferred_id.find(tp_name) == tp_preferred_id.end()) {
    tp_preferred_id[ tp_name ] = *id_out = ++id;
    DIE("Thing template not found [%s] Please edit tp_ids.cpp and add it.", tp_name.c_str());
    return;
  }

  *id_out = tp_preferred_id[ tp_name ];
}
