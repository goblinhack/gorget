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

void thing_group_join(Gamep g, Levelsp v, Levelp l, Thingp t, Thingp group)
{
  TRACE();

  if (t->group_id != 0U) {
    return;
  }

  if (! thing_is_grouped_thing(t)) {
    return;
  }

  if (t != group) {
    if (group->group_id == 0U) {
      thing_err(t, "asked to join an empty group");
    }
  }

  t->group_id = group->id;
  thing_dbg(t, "join group %d", group->id);
}

void thing_group_member_leave(Gamep g, Levelsp v, Levelp l, Thingp t)
{
  TRACE();

  thing_dbg(t, "group member leave (group %u)", t->group_id);
  t->group_id = 0;
}

void thing_group_leave(Gamep g, Levelsp v, Levelp l, Thingp t)
{
  TRACE();

  if (t->group_id == 0U) {
    return;
  }

  if (! thing_is_grouped_thing(t)) {
    return;
  }

  auto group_id = t->group_id;

  if (t->id == group_id) {
    t->group_id = 0;
    thing_dbg(t, "group leader leave (group %u)", group_id);
    TRACE_INDENT();

    FOR_ALL_GROUP_THINGS_ON_LEVEL_UNSAFE(g, v, l, o, group_id)
    {
      if (o != t) {
        thing_group_member_leave(g, v, l, o);
      }
    }
  } else {
    thing_group_member_leave(g, v, l, t);
  }
}
