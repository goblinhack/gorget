//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_main.hpp"
#include "my_thing_callbacks.hpp"
#include "my_tp.hpp"
#include "my_tps.hpp"
#include "my_ui.hpp"

static auto tp_buff_immunity_fire_detail_get(Gamep g, Levelsp v, Levelp l, Thingp me) -> std::string
{
  TRACE();

  return UI_INFO1_FMT_STR "With this buff you are completely immune to fire damage of any kind.";
}

[[nodiscard]] auto tp_load_buff_immunity_fire() -> bool
{
  TRACE();

  auto *tp   = tp_load("buff_immunity_fire"); // keep as string for scripts
  auto  name = tp_name(tp);

  // begin sort marker1 {
  thing_detail_set(tp, tp_buff_immunity_fire_detail_get);
  tp_flag_set(tp, is_buff);
  tp_flag_set(tp, is_loggable);
  tp_flag_set(tp, is_tick_on_use);
  tp_flag_set(tp, is_tickable);
  tp_is_immune_add(tp, THING_EVENT_FIRE_DAMAGE);
  tp_lifespan_set(tp, "1d100+100");
  tp_name_short_set(tp, "immunity, fire");
  // end sort marker1 }

  return true;
}
