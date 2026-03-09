//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_charmap.hpp"
#include "my_dice_rolls.hpp"
#include "my_globals.hpp"
#include "my_level.hpp"
#include "my_level_ext.hpp"
#include "my_level_inlines.hpp"
#include "my_main.hpp"
#include "my_thing_callbacks.hpp"
#include "my_thing_inlines.hpp"

static void level_group_things_do(Gamep g, Levelsp v, Levelp l, Thingp group, Tpp tp, const spoint &p)

{
  if (is_oob(p)) {
    return;
  }

  bool got_one = {};

  FOR_ALL_THINGS_AT_UNSAFE(g, v, l, t, p)
  {
    if (thing_tp(t) == tp) {
      if (t->group_id != 0U) {
        return;
      }

      thing_group_join(g, v, l, t, group);
      got_one = true;
      break;
    }
  }

  if (got_one) {
    level_group_things_do(g, v, l, group, tp, spoint(p.x - 1, p.y));
    level_group_things_do(g, v, l, group, tp, spoint(p.x + 1, p.y));
    level_group_things_do(g, v, l, group, tp, spoint(p.x, p.y - 1));
    level_group_things_do(g, v, l, group, tp, spoint(p.x, p.y + 1));
  }
}

void level_group_things(Gamep g, Levelsp v, Levelp l, Thingp t)
{
  TRACE();

  if (t->group_id != 0U) {
    return;
  }

  if (! thing_is_grouped_thing(t)) {
    return;
  }

  level_group_things_do(g, v, l, t, thing_tp(t), thing_at(t));
}
