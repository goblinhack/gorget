//
// Copyright goblinhack@gmail.com
//

#include "my_bpoint.hpp"
#include "my_callstack.hpp"
#include "my_level.hpp"
#include "my_tp.hpp"
#include "my_types.hpp"
#include <cstdint>

[[nodiscard]] auto level_count_is_able_to_collect_items(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_able_to_collect_items, p);
}

[[nodiscard]] auto level_count_is_able_to_collect_keys(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_able_to_collect_keys, p);
}

[[nodiscard]] auto level_count_is_able_to_crush_grass(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_able_to_crush_grass, p);
}

[[nodiscard]] auto level_count_is_able_to_fall_repeatedly(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_able_to_fall_repeatedly, p);
}

[[nodiscard]] auto level_count_is_able_to_fall(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_able_to_fall, p);
}

[[nodiscard]] auto level_count_is_able_to_jump(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_able_to_jump, p);
}

[[nodiscard]] auto level_count_is_able_to_move_diagonally(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_able_to_move_diagonally, p);
}

[[nodiscard]] auto level_count_is_able_to_move_through_walls(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_able_to_move_through_walls, p);
}

[[nodiscard]] auto level_count_is_able_to_open_things(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_able_to_open_things, p);
}

[[nodiscard]] auto level_count_is_able_to_shove(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_able_to_shove, p);
}

[[nodiscard]] auto level_count_is_able_to_see_through_walls(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_able_to_see_through_walls, p);
}

[[nodiscard]] auto level_count_is_animated_can_hflip(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_animated_can_hflip, p);
}

[[nodiscard]] auto level_count_is_animated_no_dir(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_animated_no_dir, p);
}

[[nodiscard]] auto level_count_is_animated_sync_first(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_animated_sync_first, p);
}

[[nodiscard]] auto level_count_is_animated(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_animated, p);
}

[[nodiscard]] auto level_count_is_barrel(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_barrel, p);
}

[[nodiscard]] auto level_count_is_blit_centered(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_blit_centered, p);
}

[[nodiscard]] auto level_count_is_blit_flush_per_line(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_blit_flush_per_line, p);
}

[[nodiscard]] auto level_count_is_blit_if_has_seen(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_blit_if_has_seen, p);
}

[[nodiscard]] auto level_count_is_blit_obscures(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_blit_obscures, p);
}

[[nodiscard]] auto level_count_is_blit_on_ground(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_blit_on_ground, p);
}

[[nodiscard]] auto level_count_is_blit_outlined(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_blit_outlined, p);
}

[[nodiscard]] auto level_count_is_blit_per_pixel_lighting(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_blit_per_pixel_lighting, p);
}

[[nodiscard]] auto level_count_is_blit_shown_in_chasms(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_blit_shown_in_chasms, p);
}

[[nodiscard]] auto level_count_is_blit_shown_in_overlay(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_blit_shown_in_overlay, p);
}

[[nodiscard]] auto level_count_is_blit_square_outlined(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_blit_square_outlined, p);
}

[[nodiscard]] auto level_count_is_blit_when_obscured_faded(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_blit_when_obscured_faded, p);
}

[[nodiscard]] auto level_count_is_border(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_border, p);
}

[[nodiscard]] auto level_count_is_brazier(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_brazier, p);
}

[[nodiscard]] auto level_count_is_bridge(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_bridge, p);
}

[[nodiscard]] auto level_count_is_broken_on_death(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_broken_on_death, p);
}

[[nodiscard]] auto level_count_is_burnable(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_burnable, p);
}

[[nodiscard]] auto level_count_is_chasm(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_chasm, p);
}

[[nodiscard]] auto level_count_is_collectable(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_collectable, p);
}

[[nodiscard]] auto level_count_is_collision_circle_large(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_collision_circle_large, p);
}

[[nodiscard]] auto level_count_is_collision_circle_small(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_collision_circle_small, p);
}

[[nodiscard]] auto level_count_is_collision_detection_enabled(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_collision_detection_enabled, p);
}

[[nodiscard]] auto level_count_is_collision_square(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_collision_square, p);
}

[[nodiscard]] auto level_count_is_combustible(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_combustible, p);
}

[[nodiscard]] auto level_count_is_corpse_on_death(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_corpse_on_death, p);
}

[[nodiscard]] auto level_count_is_corridor(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_corridor, p);
}

[[nodiscard]] auto level_count_is_crushable(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_crushable, p);
}

[[nodiscard]] auto level_count_is_cursor_path_hazard(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_cursor_path_hazard, p);
}

[[nodiscard]] auto level_count_is_cursor_path_none(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_cursor_path_none, p);
}

[[nodiscard]] auto level_count_is_cursor_path_warning(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_cursor_path_warning, p);
}

[[nodiscard]] auto level_count_is_cursor_path(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_cursor_path, p);
}

[[nodiscard]] auto level_count_is_cursor(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_cursor, p);
}

[[nodiscard]] auto level_count_is_damage_capped(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_damage_capped, p);
}

[[nodiscard]] auto level_count_is_dead_on_collision(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_dead_on_collision, p);
}

[[nodiscard]] auto level_count_is_dead_on_shoving(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_dead_on_shoving, p);
}

[[nodiscard]] auto level_count_is_deep_water(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_deep_water, p);
}

[[nodiscard]] auto level_count_is_described_cursor(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_described_cursor, p);
}

[[nodiscard]] auto level_count_is_dirt(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_dirt, p);
}

[[nodiscard]] auto level_count_is_dmap(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_dmap, p);
}

[[nodiscard]] auto level_count_is_door_locked(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_door_locked, p);
}

[[nodiscard]] auto level_count_is_door_secret(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_door_secret, p);
}

[[nodiscard]] auto level_count_is_door_unlocked(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_door_unlocked, p);
}

[[nodiscard]] auto level_count_is_dungeon_entrance(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_dungeon_entrance, p);
}

[[nodiscard]] auto level_count_is_entrance(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_entrance, p);
}

[[nodiscard]] auto level_count_is_ethereal(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_ethereal, p);
}

[[nodiscard]] auto level_count_is_exit(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_exit, p);
}

[[nodiscard]] auto level_count_is_explosion(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_explosion, p);
}

[[nodiscard]] auto level_count_is_extinguished_on_death(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_extinguished_on_death, p);
}

[[nodiscard]] auto level_count_is_fire(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_fire, p);
}

[[nodiscard]] auto level_count_is_lucky(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_lucky, p);
}

[[nodiscard]] auto level_count_is_flesh(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_flesh, p);
}

[[nodiscard]] auto level_count_is_floating(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_floating, p);
}

[[nodiscard]] auto level_count_is_floor(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_floor, p);
}

[[nodiscard]] auto level_count_is_flying(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_flying, p);
}

[[nodiscard]] auto level_count_is_foliage(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_foliage, p);
}

[[nodiscard]] auto level_count_is_gaseous(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_gaseous, p);
}

[[nodiscard]] auto level_count_is_ghost(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_ghost, p);
}

[[nodiscard]] auto level_count_is_glass(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_glass, p);
}

[[nodiscard]] auto level_count_is_gold(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_gold, p);
}

[[nodiscard]] auto level_count_is_grass(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_grass, p);
}

[[nodiscard]] auto level_count_is_shown_health(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_shown_health, p);
}

[[nodiscard]] auto level_count_is_indestructible(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_indestructible, p);
}

[[nodiscard]] auto level_count_is_insectoid(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_insectoid, p);
}

[[nodiscard]] auto level_count_is_inventory_item(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_inventory_item, p);
}

[[nodiscard]] auto level_count_is_droppable(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_droppable, p);
}

[[nodiscard]] auto level_count_is_equippable(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_equippable, p);
}

[[nodiscard]] auto level_count_is_item_mergeable(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_item_mergeable, p);
}

[[nodiscard]] auto level_count_is_item(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_item, p);
}

[[nodiscard]] auto level_count_is_key(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_key, p);
}

[[nodiscard]] auto level_count_is_kobalos(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_kobalos, p);
}

[[nodiscard]] auto level_count_is_lava(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_lava, p);
}

[[nodiscard]] auto level_count_is_usable(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_usable, p);
}

[[nodiscard]] auto level_count_is_level_curr(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_level_curr, p);
}

[[nodiscard]] auto level_count_is_critical_to_level(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_critical_to_level, p);
}

[[nodiscard]] auto level_count_is_level_final_icon(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_level_final_icon, p);
}

[[nodiscard]] auto level_count_is_level_next_icon(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_level_next_icon, p);
}

[[nodiscard]] auto level_count_is_level_locked_icon(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_level_locked_icon, p);
}

[[nodiscard]] auto level_count_is_level_closed_icon(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_level_closed_icon, p);
}

[[nodiscard]] auto level_count_is_levitating(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_levitating, p);
}

[[nodiscard]] auto level_count_is_light_source(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_light_source, p);
}

[[nodiscard]] auto level_count_is_loggable(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_loggable, p);
}

[[nodiscard]] auto level_count_is_able_to_eat_items(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_able_to_eat_items, p);
}

[[nodiscard]] auto level_count_is_meltable(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_meltable, p);
}

[[nodiscard]] auto level_count_is_metal(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_metal, p);
}

[[nodiscard]] auto level_count_is_minion(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_minion, p);
}

[[nodiscard]] auto level_count_is_mob_kill_minions_on_death(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_mob_kill_minions_on_death, p);
}

[[nodiscard]] auto level_count_is_mob(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_mob, p);
}

[[nodiscard]] auto level_count_is_mob1(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_mob1, p);
}

[[nodiscard]] auto level_count_is_mob2(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_mob2, p);
}

[[nodiscard]] auto level_count_is_monst1(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_monst1, p);
}

[[nodiscard]] auto level_count_is_monst2(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_monst2, p);
}

[[nodiscard]] auto level_count_is_monst(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_monst, p);
}

[[nodiscard]] auto level_count_is_needs_move_confirm(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_needs_move_confirm, p);
}

[[nodiscard]] auto level_count_is_obs_to_cursor_path(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_obs_to_cursor_path, p);
}

[[nodiscard]] auto level_count_is_obs_to_explosion(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_obs_to_explosion, p);
}

[[nodiscard]] auto level_count_is_obs_to_falling_onto(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_obs_to_falling_onto, p);
}

[[nodiscard]] auto level_count_is_obs_to_fire(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_obs_to_fire, p);
}

[[nodiscard]] auto level_count_is_obs_to_jumping_over(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_obs_to_jumping_over, p);
}

[[nodiscard]] auto level_count_is_obs_to_jumping_onto(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_obs_to_jumping_onto, p);
}

[[nodiscard]] auto level_count_is_obs_to_jumping_out_of(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_obs_to_jumping_out_of, p);
}

[[nodiscard]] auto level_count_is_obs_to_movement(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_obs_to_movement, p);
}

[[nodiscard]] auto level_count_is_obs_to_spawning(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_obs_to_spawning, p);
}

[[nodiscard]] auto level_count_is_obs_to_teleporting_onto(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_obs_to_teleporting_onto, p);
}

[[nodiscard]] auto level_count_is_obs_to_vision(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_obs_to_vision, p);
}

[[nodiscard]] auto level_count_is_obs_when_dead(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_obs_when_dead, p);
}

[[nodiscard]] auto level_count_is_openable(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_openable, p);
}

[[nodiscard]] auto level_count_is_physics_explosion(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_physics_explosion, p);
}

[[nodiscard]] auto level_count_is_physics_temperature(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_physics_temperature, p);
}

[[nodiscard]] auto level_count_is_physics_water(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_physics_water, p);
}

[[nodiscard]] auto level_count_is_pillar(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_pillar, p);
}

[[nodiscard]] auto level_count_is_plant(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_plant, p);
}

[[nodiscard]] auto level_count_is_player(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_player, p);
}

[[nodiscard]] auto level_count_is_projectile(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_projectile, p);
}

[[nodiscard]] auto level_count_is_removable_on_err(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_removable_on_err, p);
}

[[nodiscard]] auto level_count_is_removable_when_dead_on_err(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_removable_when_dead_on_err, p);
}

[[nodiscard]] auto level_count_is_rock(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_rock, p);
}

[[nodiscard]] auto level_count_is_shovable(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_shovable, p);
}

[[nodiscard]] auto level_count_is_slime(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_slime, p);
}

[[nodiscard]] auto level_count_is_smoke(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_smoke, p);
}

[[nodiscard]] auto level_count_is_steam(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_steam, p);
}

[[nodiscard]] auto level_count_is_stone(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_stone, p);
}

[[nodiscard]] auto level_count_is_submergible(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_submergible, p);
}

[[nodiscard]] auto level_count_is_teleport_blocked(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_teleport_blocked, p);
}

[[nodiscard]] auto level_count_is_teleport(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_teleport, p);
}

[[nodiscard]] auto level_count_is_tick_end_delay(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_tick_end_delay, p);
}

[[nodiscard]] auto level_count_is_tickable(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_tickable, p);
}

[[nodiscard]] auto level_count_is_tiled(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_tiled, p);
}

[[nodiscard]] auto level_count_is_trap(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_trap, p);
}

[[nodiscard]] auto level_count_is_treasure(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_treasure, p);
}

[[nodiscard]] auto level_count_is_undead(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_undead, p);
}

[[nodiscard]] auto level_count_is_unused1(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_unused1, p);
}

[[nodiscard]] auto level_count_is_obs_to_hearing(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_obs_to_hearing, p);
}

[[nodiscard]] auto level_count_is_throwable(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_throwable, p);
}

[[nodiscard]] auto level_count_is_obs_to_throwing_over(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_obs_to_throwing_over, p);
}

[[nodiscard]] auto level_count_is_obs_to_throwing_onto(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_obs_to_throwing_onto, p);
}

[[nodiscard]] auto level_count_is_physics_trap(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_physics_trap, p);
}

[[nodiscard]] auto level_count_is_tick_on_unwield(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_tick_on_unwield, p);
}

[[nodiscard]] auto level_count_is_tick_on_wield(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_tick_on_wield, p);
}

[[nodiscard]] auto level_count_is_buff(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_buff, p);
}

[[nodiscard]] auto level_count_is_able_to_be_buffed(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_able_to_be_buffed, p);
}

[[nodiscard]] auto level_count_is_tick_on_drop(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_tick_on_drop, p);
}

[[nodiscard]] auto level_count_is_lava_bg(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_lava_bg, p);
}

[[nodiscard]] auto level_count_is_tick_on_use(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_tick_on_use, p);
}

[[nodiscard]] auto level_count_is_able_to_throw(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_able_to_throw, p);
}

[[nodiscard]] auto level_count_is_described_when_killed(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_described_when_killed, p);
}

[[nodiscard]] auto level_count_is_chest(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_chest, p);
}

[[nodiscard]] auto level_count_is_flammable(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_flammable, p);
}

[[nodiscard]] auto level_count_is_auto_wield(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_auto_wield, p);
}

[[nodiscard]] auto level_count_is_dead_when_discharged(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_dead_when_discharged, p);
}

[[nodiscard]] auto level_count_is_able_to_fire_weapons(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_able_to_fire_weapons, p);
}

[[nodiscard]] auto level_count_wieldable(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, wieldable, p);
}

[[nodiscard]] auto level_count_is_light_flicker(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_light_flicker, p);
}

[[nodiscard]] auto level_count_is_able_to_wield_items(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_able_to_wield_items, p);
}

[[nodiscard]] auto level_count_is_wand(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_wand, p);
}

[[nodiscard]] auto level_count_is_staff(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_staff, p);
}

[[nodiscard]] auto level_count_is_able_to_eat_treasure(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_able_to_eat_treasure, p);
}

[[nodiscard]] auto level_count_is_wait_on_anim(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_wait_on_anim, p);
}

[[nodiscard]] auto level_count_is_flat(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_flat, p);
}

[[nodiscard]] auto level_count_is_obs_to_beam(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_obs_to_beam, p);
}

[[nodiscard]] auto level_count_is_beam_weapon(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_beam_weapon, p);
}

[[nodiscard]] auto level_count_is_shown_stamina(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_shown_stamina, p);
}

[[nodiscard]] auto level_count_is_reeds(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_reeds, p);
}

[[nodiscard]] auto level_count_is_able_to_drop_all_items_on_death(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_able_to_drop_all_items_on_death, p);
}

[[nodiscard]] auto level_count_is_vault(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_vault, p);
}

[[nodiscard]] auto level_count_is_biome_underhell(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_biome_underhell, p);
}

[[nodiscard]] auto level_count_is_biome_graveyard(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_biome_graveyard, p);
}

[[nodiscard]] auto level_count_is_biome_nethervoid(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_biome_nethervoid, p);
}

[[nodiscard]] auto level_count_is_biome_bogland(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_biome_bogland, p);
}

[[nodiscard]] auto level_count_is_biome_dungeon(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_biome_dungeon, p);
}

[[nodiscard]] auto level_count_is_level_open_icon(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_level_open_icon, p);
}

[[nodiscard]] auto level_count_is_blit_bg(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_blit_bg, p);
}

[[nodiscard]] auto level_count_is_level_select_bg(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_level_select_bg, p);
}

[[nodiscard]] auto level_count_is_blit_hit_outline_w_black_inside(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_blit_hit_outline_w_black_inside, p);
}

[[nodiscard]] auto level_count_is_able_to_engulf(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_able_to_engulf, p);
}

[[nodiscard]] auto level_count_is_able_to_fall_sound(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_able_to_fall_sound, p);
}

[[nodiscard]] auto level_count_is_collision_hit_first_on_tile(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_collision_hit_first_on_tile, p);
}

[[nodiscard]] auto level_count_is_collision_hit_all_on_tile(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_collision_hit_all_on_tile, p);
}

[[nodiscard]] auto level_count_is_blit_hit_outline_w_invis_inside(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_blit_hit_outline_w_invis_inside, p);
}

[[nodiscard]] auto level_count_is_blit_when_obscured_outline(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_blit_when_obscured_outline, p);
}

[[nodiscard]] auto level_count_is_attackable_by_player(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_attackable_by_player, p);
}

[[nodiscard]] auto level_count_is_attackable_by_monst(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_attackable_by_monst, p);
}

[[nodiscard]] auto level_count_is_effect(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_effect, p);
}

[[nodiscard]] auto level_count_is_effect_attack(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_effect_attack, p);
}

[[nodiscard]] auto level_count_is_effect_blood(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_effect_blood, p);
}

[[nodiscard]] auto level_count_is_effect_ripple(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_effect_ripple, p);
}

[[nodiscard]] auto level_count_is_hit_when_dead(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_hit_when_dead, p);
}

[[nodiscard]] auto level_count_is_able_to_be_engulfed(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_able_to_be_engulfed, p);
}

[[nodiscard]] auto level_count_is_potion(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_potion, p);
}

[[nodiscard]] auto level_count_is_grouped_thing(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_grouped_thing, p);
}

[[nodiscard]] auto level_count_is_vision_360_degrees(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_vision_360_degrees, p);
}

[[nodiscard]] auto level_count_is_vision_180_degrees(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_vision_180_degrees, p);
}

[[nodiscard]] auto level_count_is_able_to_lunge(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_able_to_lunge, p);
}

[[nodiscard]] auto level_count_is_obs_to_paths(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_obs_to_paths, p);
}

[[nodiscard]] auto level_count_is_stealthy(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_stealthy, p);
}

[[nodiscard]] auto level_count_is_tireless(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_tireless, p);
}

[[nodiscard]] auto level_count_is_shown_noise(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_shown_noise, p);
}

[[nodiscard]] auto level_count_is_wait_on_dead_anim(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_wait_on_dead_anim, p);
}

[[nodiscard]] auto level_count_is_wall(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_wall, p);
}

[[nodiscard]] auto level_count_is_water(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_water, p);
}

[[nodiscard]] auto level_count_is_wood(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> uint32_t
{
  TRACE_DEBUG();
  return level_count(g, v, l, is_wood, p);
}
