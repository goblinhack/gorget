//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_game.hpp"
#include "my_level.hpp"
#include "my_main.hpp"
#include "my_thing.hpp"

bool thing_is_dead(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return false;
  }
  return t->_is_dead;
}
void thing_is_dead_set(Thingp t, bool val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return;
  }
  t->_is_dead = val;
}

bool thing_is_open(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return false;
  }
  return t->_is_open;
}
void thing_is_open_set(Thingp t, bool val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return;
  }
  t->_is_open = val;
}

bool thing_is_on_map(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return false;
  }
  return t->_is_on_map;
}
void thing_is_on_map_set(Thingp t, bool val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return;
  }
  t->_is_on_map = val;
}

bool thing_is_moving(Thingp t)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return false;
  }
  return t->_is_moving;
}
void thing_is_moving_set(Thingp t, bool val)
{
  TRACE_NO_INDENT();
  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return;
  }
  t->_is_moving = val;
}
