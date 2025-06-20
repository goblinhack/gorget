//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_game.hpp"
#include "my_level.hpp"
#include "my_main.hpp"
#include "my_point.hpp"
#include "my_string.hpp"
#include "my_tp.hpp"
#include "my_tp_callbacks.hpp"
#include "my_ui.hpp"
#include "my_wid_botcon.hpp"

//
// Describe what is under the cursor
//
void level_cursor_describe(Gamep g, Levelsp v, Levelp l)
{
  //
  // Only if over the map
  //
  if (! level_cursor_is_valid(g, v)) {
    return;
  }

  Thingp      owner = nullptr;
  std::string all_things_description;
  auto        at = v->cursor_at;

  FOR_ALL_THINGS_AT(g, v, l, it, at)
  {
    if (! thing_is_described_cursor(it)) {
      continue;
    }

    auto one_desc = tp_description_get(g, v, l, it, owner, it->at);

    if (one_desc.empty()) {
      continue;
    }

    //
    // Water and deep water exist at the same tile. Don't describe twice.
    //
    if (thing_is_water(it) && level_is_deep_water(g, v, l, at)) {
      continue;
    }

    one_desc = capitalise_first(one_desc);

    if (all_things_description.empty()) {
      all_things_description = one_desc;
      continue;
    }

    all_things_description += ". ";
    all_things_description += one_desc;
  }

#pragma GCC diagnostic ignored "-Wformat-zero-length"
  BOTCON("");
#pragma GCC diagnostic warning "-Wformat-zero-length"

  if ((int) all_things_description.empty()) {
    return;
  }

  if ((int) all_things_description.size() > UI_BOTCON_WIDTH - 1) {
    BOTCON("Multiple items here.");
    return;
  }

  all_things_description += ".";
  wid_botcon_log(all_things_description);
}
