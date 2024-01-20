//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_level.hpp"
#include "my_thing_template.hpp"

bool Level::is_wall(point p)
{
  TRACE_NO_INDENT();
  if (is_oob(p)) {
    return false;
  }

  if (! data) {
    return false;
  }

  static const auto wall = tp_find("wall");
  if (! wall) {
    return false;
  }

  auto id = data->obj[ p.x ][ p.y ][ wall->z_depth ].id;
  if (! id) {
    return false;
  }

  return id == wall->id;
}

bool Level::is_rock(point p)
{
  TRACE_NO_INDENT();
  if (is_oob(p)) {
    return false;
  }

  if (! data) {
    return false;
  }

  static const auto rock = tp_find("rock");
  if (! rock) {
    return false;
  }

  auto id = data->obj[ p.x ][ p.y ][ rock->z_depth ].id;
  if (! id) {
    return false;
  }

  return id == rock->id;
}
