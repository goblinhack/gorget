//
// Copyright goblinhack@gmail.com
//

#include "my_bpoint.hpp"
#include "my_callstack.hpp"
#include "my_level.hpp"
#include "my_tp.hpp"
#include "my_types.hpp"

[[nodiscard]] auto level_is_able_to_collect_items_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_able_to_collect_items, p, me) != nullptr;
}

[[nodiscard]] auto level_is_able_to_collect_keys_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_able_to_collect_keys, p, me) != nullptr;
}

[[nodiscard]] auto level_is_able_to_crush_grass_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_able_to_crush_grass, p, me) != nullptr;
}

[[nodiscard]] auto level_is_able_to_fall_repeatedly_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_able_to_fall_repeatedly, p, me) != nullptr;
}

[[nodiscard]] auto level_is_able_to_fall_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_able_to_fall, p, me) != nullptr;
}

[[nodiscard]] auto level_is_able_to_throw_items_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_able_to_throw_items, p, me) != nullptr;
}

[[nodiscard]] auto level_is_able_to_move_diagonally_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_able_to_move_diagonally, p, me) != nullptr;
}

[[nodiscard]] auto level_is_able_to_move_through_walls_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_able_to_move_through_walls, p, me) != nullptr;
}

[[nodiscard]] auto level_is_able_to_open_things_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_able_to_open_things, p, me) != nullptr;
}

[[nodiscard]] auto level_is_able_to_shove_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_able_to_shove, p, me) != nullptr;
}

[[nodiscard]] auto level_is_able_to_walk_through_walls_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_able_to_walk_through_walls, p, me) != nullptr;
}

[[nodiscard]] auto level_is_animated_can_hflip_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_animated_can_hflip, p, me) != nullptr;
}

[[nodiscard]] auto level_is_animated_no_dir_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_animated_no_dir, p, me) != nullptr;
}

[[nodiscard]] auto level_is_animated_sync_first_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_animated_sync_first, p, me) != nullptr;
}

[[nodiscard]] auto level_is_animated_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_animated, p, me) != nullptr;
}

[[nodiscard]] auto level_is_barrel_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_barrel, p, me) != nullptr;
}

[[nodiscard]] auto level_is_blit_centered_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_blit_centered, p, me) != nullptr;
}

[[nodiscard]] auto level_is_blit_flush_per_line_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_blit_flush_per_line, p, me) != nullptr;
}

[[nodiscard]] auto level_is_blit_if_has_seen_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_blit_if_has_seen, p, me) != nullptr;
}

[[nodiscard]] auto level_is_blit_obscures_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_blit_obscures, p, me) != nullptr;
}

[[nodiscard]] auto level_is_blit_on_ground_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_blit_on_ground, p, me) != nullptr;
}

[[nodiscard]] auto level_is_blit_outlined_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_blit_outlined, p, me) != nullptr;
}

[[nodiscard]] auto level_is_blit_per_pixel_lighting_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_blit_per_pixel_lighting, p, me) != nullptr;
}

[[nodiscard]] auto level_is_blit_shown_in_chasms_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_blit_shown_in_chasms, p, me) != nullptr;
}

[[nodiscard]] auto level_is_blit_shown_in_overlay_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_blit_shown_in_overlay, p, me) != nullptr;
}

[[nodiscard]] auto level_is_blit_square_outlined_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_blit_square_outlined, p, me) != nullptr;
}

[[nodiscard]] auto level_is_blit_when_obscured_faded_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_blit_when_obscured_faded, p, me) != nullptr;
}

[[nodiscard]] auto level_is_border_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_border, p, me) != nullptr;
}

[[nodiscard]] auto level_is_brazier_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_brazier, p, me) != nullptr;
}

[[nodiscard]] auto level_is_bridge_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_bridge, p, me) != nullptr;
}

[[nodiscard]] auto level_is_broken_on_death_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_broken_on_death, p, me) != nullptr;
}

[[nodiscard]] auto level_is_burnable_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_burnable, p, me) != nullptr;
}

[[nodiscard]] auto level_is_chasm_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_chasm, p, me) != nullptr;
}

[[nodiscard]] auto level_is_collectable_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_collectable, p, me) != nullptr;
}

[[nodiscard]] auto level_is_collision_circle_large_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_collision_circle_large, p, me) != nullptr;
}

[[nodiscard]] auto level_is_collision_circle_small_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_collision_circle_small, p, me) != nullptr;
}

[[nodiscard]] auto level_is_collision_detection_enabled_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_collision_detection_enabled, p, me) != nullptr;
}

[[nodiscard]] auto level_is_collision_square_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_collision_square, p, me) != nullptr;
}

[[nodiscard]] auto level_is_combustible_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_combustible, p, me) != nullptr;
}

[[nodiscard]] auto level_is_corpse_on_death_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_corpse_on_death, p, me) != nullptr;
}

[[nodiscard]] auto level_is_corridor_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_corridor, p, me) != nullptr;
}

[[nodiscard]] auto level_is_crushable_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_crushable, p, me) != nullptr;
}

[[nodiscard]] auto level_is_cursor_path_hazard_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_cursor_path_hazard, p, me) != nullptr;
}

[[nodiscard]] auto level_is_cursor_path_none_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_cursor_path_none, p, me) != nullptr;
}

[[nodiscard]] auto level_is_cursor_path_warning_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_cursor_path_warning, p, me) != nullptr;
}

[[nodiscard]] auto level_is_cursor_path_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_cursor_path, p, me) != nullptr;
}

[[nodiscard]] auto level_is_cursor_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_cursor, p, me) != nullptr;
}

[[nodiscard]] auto level_is_damage_capped_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_damage_capped, p, me) != nullptr;
}

[[nodiscard]] auto level_is_dead_on_collision_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_dead_on_collision, p, me) != nullptr;
}

[[nodiscard]] auto level_is_dead_on_shoving_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_dead_on_shoving, p, me) != nullptr;
}

[[nodiscard]] auto level_is_deep_water_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_deep_water, p, me) != nullptr;
}

[[nodiscard]] auto level_is_described_cursor_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_described_cursor, p, me) != nullptr;
}

[[nodiscard]] auto level_is_dirt_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_dirt, p, me) != nullptr;
}

[[nodiscard]] auto level_is_dmap_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_dmap, p, me) != nullptr;
}

[[nodiscard]] auto level_is_door_locked_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_door_locked, p, me) != nullptr;
}

[[nodiscard]] auto level_is_door_secret_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_door_secret, p, me) != nullptr;
}

[[nodiscard]] auto level_is_door_unlocked_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_door_unlocked, p, me) != nullptr;
}

[[nodiscard]] auto level_is_dungeon_entrance_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_dungeon_entrance, p, me) != nullptr;
}

[[nodiscard]] auto level_is_entrance_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_entrance, p, me) != nullptr;
}

[[nodiscard]] auto level_is_ethereal_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_ethereal, p, me) != nullptr;
}

[[nodiscard]] auto level_is_exit_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_exit, p, me) != nullptr;
}

[[nodiscard]] auto level_is_explosion_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_explosion, p, me) != nullptr;
}

[[nodiscard]] auto level_is_extinguished_on_death_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_extinguished_on_death, p, me) != nullptr;
}

[[nodiscard]] auto level_is_fire_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_fire, p, me) != nullptr;
}

[[nodiscard]] auto level_is_unused_99_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_unused_99, p, me) != nullptr;
}

[[nodiscard]] auto level_is_flesh_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_flesh, p, me) != nullptr;
}

[[nodiscard]] auto level_is_floating_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_floating, p, me) != nullptr;
}

[[nodiscard]] auto level_is_floor_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_floor, p, me) != nullptr;
}

[[nodiscard]] auto level_is_flying_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_flying, p, me) != nullptr;
}

[[nodiscard]] auto level_is_foliage_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_foliage, p, me) != nullptr;
}

[[nodiscard]] auto level_is_gaseous_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_gaseous, p, me) != nullptr;
}

[[nodiscard]] auto level_is_ghost_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_ghost, p, me) != nullptr;
}

[[nodiscard]] auto level_is_glass_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_glass, p, me) != nullptr;
}

[[nodiscard]] auto level_is_gold_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_gold, p, me) != nullptr;
}

[[nodiscard]] auto level_is_grass_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_grass, p, me) != nullptr;
}

[[nodiscard]] auto level_is_shown_health_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_shown_health, p, me) != nullptr;
}

[[nodiscard]] auto level_is_indestructible_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_indestructible, p, me) != nullptr;
}

[[nodiscard]] auto level_is_insectoid_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_insectoid, p, me) != nullptr;
}

[[nodiscard]] auto level_is_inventory_item_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_inventory_item, p, me) != nullptr;
}

[[nodiscard]] auto level_is_droppable_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_droppable, p, me) != nullptr;
}

[[nodiscard]] auto level_is_equippable_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_equippable, p, me) != nullptr;
}

[[nodiscard]] auto level_is_item_mergeable_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_item_mergeable, p, me) != nullptr;
}

[[nodiscard]] auto level_is_item_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_item, p, me) != nullptr;
}

[[nodiscard]] auto level_is_key_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_key, p, me) != nullptr;
}

[[nodiscard]] auto level_is_kobalos_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_kobalos, p, me) != nullptr;
}

[[nodiscard]] auto level_is_lava_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_lava, p, me) != nullptr;
}

[[nodiscard]] auto level_is_usable_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_usable, p, me) != nullptr;
}

[[nodiscard]] auto level_is_level_curr_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_level_curr, p, me) != nullptr;
}

[[nodiscard]] auto level_is_critical_to_level_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_critical_to_level, p, me) != nullptr;
}

[[nodiscard]] auto level_is_level_final_icon_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_level_final_icon, p, me) != nullptr;
}

[[nodiscard]] auto level_is_level_next_icon_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_level_next_icon, p, me) != nullptr;
}

[[nodiscard]] auto level_is_level_locked_icon_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_level_locked_icon, p, me) != nullptr;
}

[[nodiscard]] auto level_is_level_closed_icon_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_level_closed_icon, p, me) != nullptr;
}

[[nodiscard]] auto level_is_levitating_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_levitating, p, me) != nullptr;
}

[[nodiscard]] auto level_is_light_source_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_light_source, p, me) != nullptr;
}

[[nodiscard]] auto level_is_loggable_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_loggable, p, me) != nullptr;
}

[[nodiscard]] auto level_is_mantisman_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_mantisman, p, me) != nullptr;
}

[[nodiscard]] auto level_is_meltable_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_meltable, p, me) != nullptr;
}

[[nodiscard]] auto level_is_metal_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_metal, p, me) != nullptr;
}

[[nodiscard]] auto level_is_minion_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_minion, p, me) != nullptr;
}

[[nodiscard]] auto level_is_mob_kill_minions_on_death_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_mob_kill_minions_on_death, p, me) != nullptr;
}

[[nodiscard]] auto level_is_mob_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_mob, p, me) != nullptr;
}

[[nodiscard]] auto level_is_mob1_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_mob1, p, me) != nullptr;
}

[[nodiscard]] auto level_is_mob2_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_mob2, p, me) != nullptr;
}

[[nodiscard]] auto level_is_monst1_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_monst1, p, me) != nullptr;
}

[[nodiscard]] auto level_is_monst2_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_monst2, p, me) != nullptr;
}

[[nodiscard]] auto level_is_monst_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_monst, p, me) != nullptr;
}

[[nodiscard]] auto level_is_needs_move_confirm_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_needs_move_confirm, p, me) != nullptr;
}

[[nodiscard]] auto level_is_obs_to_cursor_path_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_obs_to_cursor_path, p, me) != nullptr;
}

[[nodiscard]] auto level_is_obs_to_explosion_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_obs_to_explosion, p, me) != nullptr;
}

[[nodiscard]] auto level_is_obs_to_falling_onto_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_obs_to_falling_onto, p, me) != nullptr;
}

[[nodiscard]] auto level_is_obs_to_fire_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_obs_to_fire, p, me) != nullptr;
}

[[nodiscard]] auto level_is_obs_to_jumping_over_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_obs_to_jumping_over, p, me) != nullptr;
}

[[nodiscard]] auto level_is_obs_to_jumping_onto_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_obs_to_jumping_onto, p, me) != nullptr;
}

[[nodiscard]] auto level_is_obs_to_jumping_out_of_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_obs_to_jumping_out_of, p, me) != nullptr;
}

[[nodiscard]] auto level_is_obs_to_movement_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_obs_to_movement, p, me) != nullptr;
}

[[nodiscard]] auto level_is_obs_to_spawning_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_obs_to_spawning, p, me) != nullptr;
}

[[nodiscard]] auto level_is_obs_to_teleporting_onto_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_obs_to_teleporting_onto, p, me) != nullptr;
}

[[nodiscard]] auto level_is_obs_to_vision_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_obs_to_vision, p, me) != nullptr;
}

[[nodiscard]] auto level_is_obs_when_dead_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_obs_when_dead, p, me) != nullptr;
}

[[nodiscard]] auto level_is_openable_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_openable, p, me) != nullptr;
}

[[nodiscard]] auto level_is_physics_explosion_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_physics_explosion, p, me) != nullptr;
}

[[nodiscard]] auto level_is_physics_temperature_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_physics_temperature, p, me) != nullptr;
}

[[nodiscard]] auto level_is_physics_water_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_physics_water, p, me) != nullptr;
}

[[nodiscard]] auto level_is_pillar_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_pillar, p, me) != nullptr;
}

[[nodiscard]] auto level_is_plant_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_plant, p, me) != nullptr;
}

[[nodiscard]] auto level_is_player_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_player, p, me) != nullptr;
}

[[nodiscard]] auto level_is_projectile_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_projectile, p, me) != nullptr;
}

[[nodiscard]] auto level_is_removable_on_err_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_removable_on_err, p, me) != nullptr;
}

[[nodiscard]] auto level_is_removable_when_dead_on_err_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_removable_when_dead_on_err, p, me) != nullptr;
}

[[nodiscard]] auto level_is_rock_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_rock, p, me) != nullptr;
}

[[nodiscard]] auto level_is_shovable_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_shovable, p, me) != nullptr;
}

[[nodiscard]] auto level_is_slime_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_slime, p, me) != nullptr;
}

[[nodiscard]] auto level_is_smoke_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_smoke, p, me) != nullptr;
}

[[nodiscard]] auto level_is_steam_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_steam, p, me) != nullptr;
}

[[nodiscard]] auto level_is_stone_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_stone, p, me) != nullptr;
}

[[nodiscard]] auto level_is_submergible_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_submergible, p, me) != nullptr;
}

[[nodiscard]] auto level_is_teleport_blocked_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_teleport_blocked, p, me) != nullptr;
}

[[nodiscard]] auto level_is_teleport_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_teleport, p, me) != nullptr;
}

[[nodiscard]] auto level_is_tick_end_delay_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_tick_end_delay, p, me) != nullptr;
}

[[nodiscard]] auto level_is_tickable_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_tickable, p, me) != nullptr;
}

[[nodiscard]] auto level_is_tiled_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_tiled, p, me) != nullptr;
}

[[nodiscard]] auto level_is_trap_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_trap, p, me) != nullptr;
}

[[nodiscard]] auto level_is_treasure_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_treasure, p, me) != nullptr;
}

[[nodiscard]] auto level_is_undead_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_undead, p, me) != nullptr;
}

[[nodiscard]] auto level_is_unused1_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_unused1, p, me) != nullptr;
}

[[nodiscard]] auto level_is_obs_to_hearing_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_obs_to_hearing, p, me) != nullptr;
}

[[nodiscard]] auto level_is_able_to_be_thrown_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_able_to_be_thrown, p, me) != nullptr;
}

[[nodiscard]] auto level_is_obs_to_throwing_over_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_obs_to_throwing_over, p, me) != nullptr;
}

[[nodiscard]] auto level_is_obs_to_throwing_onto_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_obs_to_throwing_onto, p, me) != nullptr;
}

[[nodiscard]] auto level_is_unused_98_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_unused_98, p, me) != nullptr;
}

[[nodiscard]] auto level_is_tick_on_unwield_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_tick_on_unwield, p, me) != nullptr;
}

[[nodiscard]] auto level_is_tick_on_wield_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_tick_on_wield, p, me) != nullptr;
}

[[nodiscard]] auto level_is_buff_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_buff, p, me) != nullptr;
}

[[nodiscard]] auto level_is_able_to_be_buffed_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_able_to_be_buffed, p, me) != nullptr;
}

[[nodiscard]] auto level_is_tick_on_drop_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_tick_on_drop, p, me) != nullptr;
}

[[nodiscard]] auto level_is_unused2_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_unused2, p, me) != nullptr;
}

[[nodiscard]] auto level_is_tick_on_use_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_tick_on_use, p, me) != nullptr;
}

[[nodiscard]] auto level_is_able_to_throw_items_items_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_able_to_throw_items_items, p, me) != nullptr;
}

[[nodiscard]] auto level_is_throwable_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_throwable, p, me) != nullptr;
}

[[nodiscard]] auto level_is_described_when_killed_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_described_when_killed, p, me) != nullptr;
}

[[nodiscard]] auto level_is_chest_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_chest, p, me) != nullptr;
}

[[nodiscard]] auto level_is_flammable_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_flammable, p, me) != nullptr;
}

[[nodiscard]] auto level_is_auto_wield_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_auto_wield, p, me) != nullptr;
}

[[nodiscard]] auto level_is_dead_when_discharged_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_dead_when_discharged, p, me) != nullptr;
}

[[nodiscard]] auto level_is_able_to_fire_weapons_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_able_to_fire_weapons, p, me) != nullptr;
}

[[nodiscard]] auto level_wieldable_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, wieldable, p, me) != nullptr;
}

[[nodiscard]] auto level_is_unused3_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_unused3, p, me) != nullptr;
}

[[nodiscard]] auto level_is_able_to_wield_items_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_able_to_wield_items, p, me) != nullptr;
}

[[nodiscard]] auto level_is_wand_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_wand, p, me) != nullptr;
}

[[nodiscard]] auto level_is_staff_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_staff, p, me) != nullptr;
}

[[nodiscard]] auto level_is_argusul_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_argusul, p, me) != nullptr;
}

[[nodiscard]] auto level_is_wait_on_anim_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_wait_on_anim, p, me) != nullptr;
}

[[nodiscard]] auto level_is_flat_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_flat, p, me) != nullptr;
}

[[nodiscard]] auto level_is_obs_to_beam_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_obs_to_beam, p, me) != nullptr;
}

[[nodiscard]] auto level_is_beam_weapon_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_beam_weapon, p, me) != nullptr;
}

[[nodiscard]] auto level_is_shown_stamina_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_shown_stamina, p, me) != nullptr;
}

[[nodiscard]] auto level_is_reeds_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_reeds, p, me) != nullptr;
}

[[nodiscard]] auto level_is_unused4_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_unused4, p, me) != nullptr;
}

[[nodiscard]] auto level_is_vault_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_vault, p, me) != nullptr;
}

[[nodiscard]] auto level_is_biome_underhell_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_biome_underhell, p, me) != nullptr;
}

[[nodiscard]] auto level_is_biome_graveyard_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_biome_graveyard, p, me) != nullptr;
}

[[nodiscard]] auto level_is_biome_nethervoid_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_biome_nethervoid, p, me) != nullptr;
}

[[nodiscard]] auto level_is_biome_bogland_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_biome_bogland, p, me) != nullptr;
}

[[nodiscard]] auto level_is_biome_dungeon_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_biome_dungeon, p, me) != nullptr;
}

[[nodiscard]] auto level_is_level_open_icon_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_level_open_icon, p, me) != nullptr;
}

[[nodiscard]] auto level_is_blit_bg_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_blit_bg, p, me) != nullptr;
}

[[nodiscard]] auto level_is_level_select_bg_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_level_select_bg, p, me) != nullptr;
}

[[nodiscard]] auto level_is_blit_hit_outline_w_black_inside_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_blit_hit_outline_w_black_inside, p, me) != nullptr;
}

[[nodiscard]] auto level_is_flameskull_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_flameskull, p, me) != nullptr;
}

[[nodiscard]] auto level_is_able_to_fall_sound_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_able_to_fall_sound, p, me) != nullptr;
}

[[nodiscard]] auto level_is_collision_hit_first_on_tile_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_collision_hit_first_on_tile, p, me) != nullptr;
}

[[nodiscard]] auto level_is_collision_hit_all_on_tile_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_collision_hit_all_on_tile, p, me) != nullptr;
}

[[nodiscard]] auto level_is_blit_hit_outline_w_invis_inside_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_blit_hit_outline_w_invis_inside, p, me) != nullptr;
}

[[nodiscard]] auto level_is_blit_when_obscured_outline_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_blit_when_obscured_outline, p, me) != nullptr;
}

[[nodiscard]] auto level_is_attackable_by_player_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_attackable_by_player, p, me) != nullptr;
}

[[nodiscard]] auto level_is_attackable_by_monst_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_attackable_by_monst, p, me) != nullptr;
}

[[nodiscard]] auto level_is_effect_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_effect, p, me) != nullptr;
}

[[nodiscard]] auto level_is_effect_attack_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_effect_attack, p, me) != nullptr;
}

[[nodiscard]] auto level_is_effect_blood_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_effect_blood, p, me) != nullptr;
}

[[nodiscard]] auto level_is_effect_ripple_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_effect_ripple, p, me) != nullptr;
}

[[nodiscard]] auto level_is_hit_when_dead_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_hit_when_dead, p, me) != nullptr;
}

[[nodiscard]] auto level_is_blitzhound_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_blitzhound, p, me) != nullptr;
}

[[nodiscard]] auto level_is_potion_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_potion, p, me) != nullptr;
}

[[nodiscard]] auto level_is_grouped_thing_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_grouped_thing, p, me) != nullptr;
}

[[nodiscard]] auto level_is_vision_360_degrees_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_vision_360_degrees, p, me) != nullptr;
}

[[nodiscard]] auto level_is_vision_180_degrees_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_vision_180_degrees, p, me) != nullptr;
}

[[nodiscard]] auto level_is_able_to_lunge_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_able_to_lunge, p, me) != nullptr;
}

[[nodiscard]] auto level_is_obs_to_paths_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_obs_to_paths, p, me) != nullptr;
}

[[nodiscard]] auto level_is_stealthy_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_stealthy, p, me) != nullptr;
}

[[nodiscard]] auto level_is_tireless_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_tireless, p, me) != nullptr;
}

[[nodiscard]] auto level_is_shown_noise_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_shown_noise, p, me) != nullptr;
}

[[nodiscard]] auto level_is_wait_on_dead_anim_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_wait_on_dead_anim, p, me) != nullptr;
}

[[nodiscard]] auto level_is_wall_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_wall, p, me) != nullptr;
}

[[nodiscard]] auto level_is_water_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_water, p, me) != nullptr;
}

[[nodiscard]] auto level_is_wood_bool(Gamep g, Levelsp v, Levelp l, const bpoint &p, Thingp me) -> bool
{
  TRACE_DEBUG();
  return level_flag(g, v, l, is_wood, p, me) != nullptr;
}
