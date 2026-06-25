//

#include "my_callstack.hpp"
#include "my_color_defs.hpp"
#include "my_game_defs.hpp"
#include "my_game_popups.hpp"
#include "my_level.hpp"
#include "my_main.hpp"
#include "my_string.hpp"
#include "my_thing.hpp"
#include "my_thing_callbacks.hpp"
#include "my_thing_inlines.hpp"
#include "my_tp.hpp"
#include "my_types.hpp"
#include "my_ui.hpp"

#include <algorithm>
#include <string>

[[nodiscard]] auto thing_age(Thingp t) -> int
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return 0;
  }
  return t->_age;
}

[[nodiscard]] auto thing_age_set(Gamep g, Levelsp v, Levelp l, Thingp t, int val) -> int
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return 0;
  }
  return t->_age = val;
}

[[nodiscard]] auto thing_age_incr(Gamep g, Levelsp v, Levelp l, Thingp t, int val) -> int
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return 0;
  }
  return t->_age += val;
}

[[nodiscard]] auto thing_age_decr(Gamep g, Levelsp v, Levelp l, Thingp t, int val) -> int
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return 0;
  }
  if (t->_age - val <= 0) {
    return t->_age = 0;
  }
  return t->_age -= val;
}
