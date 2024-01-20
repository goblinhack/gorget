//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_level_data.hpp"
#include "my_main.hpp"
#include "my_thing_template.hpp"
#include "my_thing_templates.hpp"

bool templates_init(void)
{
  TRACE_NO_INDENT();

  if (! tp_load_rock()) {
    return false;
  }

  if (! tp_load_wall()) {
    return false;
  }

  if (! tp_load_player()) {
    return false;
  }

  if (! tp_load_key()) {
    return false;
  }

  if (! tp_load_entrance()) {
    return false;
  }

  if (! tp_load_exit()) {
    return false;
  }

  return true;
}
