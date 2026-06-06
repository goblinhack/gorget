//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_main.hpp"
#include "my_tp.hpp"
#include "my_tps.hpp"

[[nodiscard]] auto tp_load_buff_immunity_fire_damage() -> bool
{
  TRACE();

  auto *tp   = tp_load("buff_immunity_fire_damage"); // keep as string for scripts
  auto  name = tp_name(tp);

  // begin sort marker1 {
  tp_flag_set(tp, is_buff);
  tp_flag_set(tp, is_loggable);
  tp_flag_set(tp, is_tick_on_use);
  tp_flag_set(tp, is_tickable);
  tp_is_immune_add(tp, THING_EVENT_FIRE_DAMAGE);
  tp_lifespan_set(tp, "1d100+100");
  tp_name_short_set(tp, "immune to fire damage");
  // end sort marker1 }

  return true;
}
