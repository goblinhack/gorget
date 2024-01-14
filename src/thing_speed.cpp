//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include <iostream>
#include <sstream>
#include <string.h>

#include "my_level.hpp"
#include "my_level_data.hpp"
#include "my_main.hpp"
#include "my_thing.hpp"
#include "my_thing_id.hpp"
#include "my_thing_template.hpp"

void thing_update_speed(LevelData *data, Thingp t)
{
  TRACE_NO_INDENT();

  auto tp = tp_find(t->tp_id);

  //
  // TODO if not in the air
  //
  if (tp->is_friction_applied) {
    if (t->dx > 0) {
      t->dx--;
    } else if (t->dx < 0) {
      t->dx++;
    }
  }

  auto max_speed = tp->max_speed;

  if (t->dx > max_speed) {
    t->dx--;
  } else if (t->dx < -max_speed) {
    t->dx++;
  }

  if (t->dy > max_speed) {
    t->dy--;
  } else if (t->dy < -max_speed) {
    t->dy++;
  }
}

void Level::thing_update_speed(Thingp t)
{
  TRACE_NO_INDENT();
  return ::thing_update_speed(data, t);
}
