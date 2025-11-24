//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_level.hpp"
#include "my_thing_inlines.hpp"

//
// See what's on the level
//
void level_count_items(Gamep g, Levelsp v, Levelp l)
{
  TRACE_NO_INDENT();

  l->info.monst_count            = 0;
  l->info.monst_group_mob_count  = 0;
  l->info.monst_group_easy_count = 0;
  l->info.monst_group_hard_count = 0;
  l->info.treasure_count         = 0;
  l->info.teleport_count         = 0;
  l->info.door_locked_count      = 0;
  l->info.key_count              = 0;

  FOR_ALL_THINGS_ON_LEVEL(g, v, l, t)
  {
    if (thing_is_monst(t)) {
      l->info.monst_count++;
    }
    if (thing_is_monst_group_mob(t)) {
      l->info.monst_group_mob_count++;
    }
    if (thing_is_monst_group_easy(t)) {
      l->info.monst_group_easy_count++;
    }
    if (thing_is_monst_group_hard(t)) {
      l->info.monst_group_hard_count++;
    }
    if (thing_is_treasure(t)) {
      l->info.treasure_count++;
    }
    if (thing_is_teleport(t)) {
      l->info.teleport_count++;
    }
    if (thing_is_door_locked(t)) {
      l->info.door_locked_count++;
    }
    if (thing_is_key(t)) {
      l->info.key_count++;
    }
  }
}
