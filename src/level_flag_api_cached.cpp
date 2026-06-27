//
// Copyright goblinhack@gmail.com
//

#include "my_bpoint.hpp"
#include "my_callstack.hpp"
#include "my_level.hpp"
#include "my_tp.hpp"
#include "my_types.hpp"

[[nodiscard]] auto level_is_able_to_collect_items_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_able_to_collect_items, p);
}

[[nodiscard]] auto level_is_able_to_collect_keys_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_able_to_collect_keys, p);
}

[[nodiscard]] auto level_is_able_to_crush_grass_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_able_to_crush_grass, p);
}

[[nodiscard]] auto level_is_able_to_fall_repeatedly_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_able_to_fall_repeatedly, p);
}

[[nodiscard]] auto level_is_able_to_fall_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_able_to_fall, p);
}

[[nodiscard]] auto level_is_able_to_throw_items_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_able_to_throw_items, p);
}

[[nodiscard]] auto level_is_able_to_move_diagonally_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_able_to_move_diagonally, p);
}

[[nodiscard]] auto level_is_able_to_move_through_walls_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_able_to_move_through_walls, p);
}

[[nodiscard]] auto level_is_able_to_open_things_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_able_to_open_things, p);
}

[[nodiscard]] auto level_is_able_to_shove_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_able_to_shove, p);
}

[[nodiscard]] auto level_is_able_to_walk_through_walls_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_able_to_walk_through_walls, p);
}

[[nodiscard]] auto level_is_animated_can_hflip_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_animated_can_hflip, p);
}

[[nodiscard]] auto level_is_animated_no_dir_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_animated_no_dir, p);
}

[[nodiscard]] auto level_is_animated_sync_first_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_animated_sync_first, p);
}

[[nodiscard]] auto level_is_animated_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_animated, p);
}

[[nodiscard]] auto level_is_barrel_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_barrel, p);
}

[[nodiscard]] auto level_is_blit_centered_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_blit_centered, p);
}

[[nodiscard]] auto level_is_blit_flush_per_line_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_blit_flush_per_line, p);
}

[[nodiscard]] auto level_is_blit_if_has_seen_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_blit_if_has_seen, p);
}

[[nodiscard]] auto level_is_blit_obscures_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_blit_obscures, p);
}

[[nodiscard]] auto level_is_blit_on_ground_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_blit_on_ground, p);
}

[[nodiscard]] auto level_is_blit_outlined_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_blit_outlined, p);
}

[[nodiscard]] auto level_is_blit_per_pixel_lighting_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_blit_per_pixel_lighting, p);
}

[[nodiscard]] auto level_is_blit_shown_in_chasms_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_blit_shown_in_chasms, p);
}

[[nodiscard]] auto level_is_blit_shown_in_overlay_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_blit_shown_in_overlay, p);
}

[[nodiscard]] auto level_is_blit_square_outlined_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_blit_square_outlined, p);
}

[[nodiscard]] auto level_is_blit_when_obscured_faded_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_blit_when_obscured_faded, p);
}

[[nodiscard]] auto level_is_border_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_border, p);
}

[[nodiscard]] auto level_is_brazier_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_brazier, p);
}

[[nodiscard]] auto level_is_bridge_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_bridge, p);
}

[[nodiscard]] auto level_is_broken_on_death_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_broken_on_death, p);
}

[[nodiscard]] auto level_is_burnable_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_burnable, p);
}

[[nodiscard]] auto level_is_chasm_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_chasm, p);
}

[[nodiscard]] auto level_is_collectable_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_collectable, p);
}

[[nodiscard]] auto level_is_collision_circle_large_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_collision_circle_large, p);
}

[[nodiscard]] auto level_is_collision_circle_small_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_collision_circle_small, p);
}

[[nodiscard]] auto level_is_collision_detection_enabled_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_collision_detection_enabled, p);
}

[[nodiscard]] auto level_is_collision_square_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_collision_square, p);
}

[[nodiscard]] auto level_is_combustible_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_combustible, p);
}

[[nodiscard]] auto level_is_corpse_on_death_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_corpse_on_death, p);
}

[[nodiscard]] auto level_is_corridor_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_corridor, p);
}

[[nodiscard]] auto level_is_crushable_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_crushable, p);
}

[[nodiscard]] auto level_is_cursor_path_hazard_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_cursor_path_hazard, p);
}

[[nodiscard]] auto level_is_cursor_path_none_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_cursor_path_none, p);
}

[[nodiscard]] auto level_is_cursor_path_warning_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_cursor_path_warning, p);
}

[[nodiscard]] auto level_is_cursor_path_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_cursor_path, p);
}

[[nodiscard]] auto level_is_cursor_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_cursor, p);
}

[[nodiscard]] auto level_is_damage_capped_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_damage_capped, p);
}

[[nodiscard]] auto level_is_dead_on_collision_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_dead_on_collision, p);
}

[[nodiscard]] auto level_is_dead_on_shoving_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_dead_on_shoving, p);
}

[[nodiscard]] auto level_is_deep_water_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_deep_water, p);
}

[[nodiscard]] auto level_is_described_cursor_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_described_cursor, p);
}

[[nodiscard]] auto level_is_dirt_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_dirt, p);
}

[[nodiscard]] auto level_is_dmap_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_dmap, p);
}

[[nodiscard]] auto level_is_door_locked_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_door_locked, p);
}

[[nodiscard]] auto level_is_door_secret_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_door_secret, p);
}

[[nodiscard]] auto level_is_door_unlocked_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_door_unlocked, p);
}

[[nodiscard]] auto level_is_dungeon_entrance_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_dungeon_entrance, p);
}

[[nodiscard]] auto level_is_entrance_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_entrance, p);
}

[[nodiscard]] auto level_is_ethereal_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_ethereal, p);
}

[[nodiscard]] auto level_is_exit_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_exit, p);
}

[[nodiscard]] auto level_is_explosion_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_explosion, p);
}

[[nodiscard]] auto level_is_extinguished_on_death_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_extinguished_on_death, p);
}

[[nodiscard]] auto level_is_fire_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_fire, p);
}

[[nodiscard]] auto level_is_unused_99_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_unused_99, p);
}

[[nodiscard]] auto level_is_flesh_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_flesh, p);
}

[[nodiscard]] auto level_is_floating_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_floating, p);
}

[[nodiscard]] auto level_is_floor_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_floor, p);
}

[[nodiscard]] auto level_is_flying_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_flying, p);
}

[[nodiscard]] auto level_is_foliage_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_foliage, p);
}

[[nodiscard]] auto level_is_gaseous_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_gaseous, p);
}

[[nodiscard]] auto level_is_ghost_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_ghost, p);
}

[[nodiscard]] auto level_is_glass_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_glass, p);
}

[[nodiscard]] auto level_is_gold_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_gold, p);
}

[[nodiscard]] auto level_is_grass_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_grass, p);
}

[[nodiscard]] auto level_is_shown_health_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_shown_health, p);
}

[[nodiscard]] auto level_is_indestructible_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_indestructible, p);
}

[[nodiscard]] auto level_is_insectoid_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_insectoid, p);
}

[[nodiscard]] auto level_is_inventory_item_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_inventory_item, p);
}

[[nodiscard]] auto level_is_droppable_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_droppable, p);
}

[[nodiscard]] auto level_is_equippable_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_equippable, p);
}

[[nodiscard]] auto level_is_item_mergeable_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_item_mergeable, p);
}

[[nodiscard]] auto level_is_item_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_item, p);
}

[[nodiscard]] auto level_is_key_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_key, p);
}

[[nodiscard]] auto level_is_kobalos_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_kobalos, p);
}

[[nodiscard]] auto level_is_lava_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_lava, p);
}

[[nodiscard]] auto level_is_usable_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_usable, p);
}

[[nodiscard]] auto level_is_level_curr_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_level_curr, p);
}

[[nodiscard]] auto level_is_critical_to_level_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_critical_to_level, p);
}

[[nodiscard]] auto level_is_level_final_icon_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_level_final_icon, p);
}

[[nodiscard]] auto level_is_level_next_icon_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_level_next_icon, p);
}

[[nodiscard]] auto level_is_level_locked_icon_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_level_locked_icon, p);
}

[[nodiscard]] auto level_is_level_closed_icon_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_level_closed_icon, p);
}

[[nodiscard]] auto level_is_levitating_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_levitating, p);
}

[[nodiscard]] auto level_is_light_source_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_light_source, p);
}

[[nodiscard]] auto level_is_loggable_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_loggable, p);
}

[[nodiscard]] auto level_is_mantisman_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_mantisman, p);
}

[[nodiscard]] auto level_is_meltable_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_meltable, p);
}

[[nodiscard]] auto level_is_metal_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_metal, p);
}

[[nodiscard]] auto level_is_minion_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_minion, p);
}

[[nodiscard]] auto level_is_mob_kill_minions_on_death_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_mob_kill_minions_on_death, p);
}

[[nodiscard]] auto level_is_mob_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_mob, p);
}

[[nodiscard]] auto level_is_mob1_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_mob1, p);
}

[[nodiscard]] auto level_is_mob2_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_mob2, p);
}

[[nodiscard]] auto level_is_monst1_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_monst1, p);
}

[[nodiscard]] auto level_is_monst2_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_monst2, p);
}

[[nodiscard]] auto level_is_monst_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_monst, p);
}

[[nodiscard]] auto level_is_needs_move_confirm_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_needs_move_confirm, p);
}

[[nodiscard]] auto level_is_obs_to_cursor_path_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_obs_to_cursor_path, p);
}

[[nodiscard]] auto level_is_obs_to_explosion_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_obs_to_explosion, p);
}

[[nodiscard]] auto level_is_obs_to_falling_onto_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_obs_to_falling_onto, p);
}

[[nodiscard]] auto level_is_obs_to_fire_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_obs_to_fire, p);
}

[[nodiscard]] auto level_is_obs_to_jumping_over_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_obs_to_jumping_over, p);
}

[[nodiscard]] auto level_is_obs_to_jumping_onto_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_obs_to_jumping_onto, p);
}

[[nodiscard]] auto level_is_obs_to_jumping_out_of_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_obs_to_jumping_out_of, p);
}

[[nodiscard]] auto level_is_obs_to_movement_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_obs_to_movement, p);
}

[[nodiscard]] auto level_is_obs_to_spawning_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_obs_to_spawning, p);
}

[[nodiscard]] auto level_is_obs_to_teleporting_onto_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_obs_to_teleporting_onto, p);
}

[[nodiscard]] auto level_is_obs_to_vision_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_obs_to_vision, p);
}

[[nodiscard]] auto level_is_obs_when_dead_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_obs_when_dead, p);
}

[[nodiscard]] auto level_is_openable_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_openable, p);
}

[[nodiscard]] auto level_is_physics_explosion_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_physics_explosion, p);
}

[[nodiscard]] auto level_is_physics_temperature_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_physics_temperature, p);
}

[[nodiscard]] auto level_is_physics_water_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_physics_water, p);
}

[[nodiscard]] auto level_is_pillar_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_pillar, p);
}

[[nodiscard]] auto level_is_plant_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_plant, p);
}

[[nodiscard]] auto level_is_player_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_player, p);
}

[[nodiscard]] auto level_is_projectile_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_projectile, p);
}

[[nodiscard]] auto level_is_removable_on_err_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_removable_on_err, p);
}

[[nodiscard]] auto level_is_removable_when_dead_on_err_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_removable_when_dead_on_err, p);
}

[[nodiscard]] auto level_is_rock_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_rock, p);
}

[[nodiscard]] auto level_is_shovable_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_shovable, p);
}

[[nodiscard]] auto level_is_slime_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_slime, p);
}

[[nodiscard]] auto level_is_smoke_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_smoke, p);
}

[[nodiscard]] auto level_is_steam_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_steam, p);
}

[[nodiscard]] auto level_is_stone_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_stone, p);
}

[[nodiscard]] auto level_is_submergible_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_submergible, p);
}

[[nodiscard]] auto level_is_teleport_blocked_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_teleport_blocked, p);
}

[[nodiscard]] auto level_is_teleport_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_teleport, p);
}

[[nodiscard]] auto level_is_tick_end_delay_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_tick_end_delay, p);
}

[[nodiscard]] auto level_is_tickable_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_tickable, p);
}

[[nodiscard]] auto level_is_tiled_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_tiled, p);
}

[[nodiscard]] auto level_is_trap_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_trap, p);
}

[[nodiscard]] auto level_is_treasure_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_treasure, p);
}

[[nodiscard]] auto level_is_undead_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_undead, p);
}

[[nodiscard]] auto level_is_unused1_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_unused1, p);
}

[[nodiscard]] auto level_is_obs_to_hearing_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_obs_to_hearing, p);
}

[[nodiscard]] auto level_is_able_to_be_thrown_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_able_to_be_thrown, p);
}

[[nodiscard]] auto level_is_obs_to_throwing_over_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_obs_to_throwing_over, p);
}

[[nodiscard]] auto level_is_obs_to_throwing_onto_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_obs_to_throwing_onto, p);
}

[[nodiscard]] auto level_is_unused_98_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_unused_98, p);
}

[[nodiscard]] auto level_is_tick_on_unwield_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_tick_on_unwield, p);
}

[[nodiscard]] auto level_is_tick_on_wield_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_tick_on_wield, p);
}

[[nodiscard]] auto level_is_buff_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_buff, p);
}

[[nodiscard]] auto level_is_able_to_be_buffed_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_able_to_be_buffed, p);
}

[[nodiscard]] auto level_is_tick_on_drop_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_tick_on_drop, p);
}

[[nodiscard]] auto level_is_unused2_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_unused2, p);
}

[[nodiscard]] auto level_is_tick_on_use_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_tick_on_use, p);
}

[[nodiscard]] auto level_is_able_to_throw_items_items_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_able_to_throw_items_items, p);
}

[[nodiscard]] auto level_is_throwable_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_throwable, p);
}

[[nodiscard]] auto level_is_described_when_killed_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_described_when_killed, p);
}

[[nodiscard]] auto level_is_chest_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_chest, p);
}

[[nodiscard]] auto level_is_flammable_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_flammable, p);
}

[[nodiscard]] auto level_is_auto_wield_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_auto_wield, p);
}

[[nodiscard]] auto level_is_dead_when_discharged_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_dead_when_discharged, p);
}

[[nodiscard]] auto level_is_able_to_fire_weapons_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_able_to_fire_weapons, p);
}

[[nodiscard]] auto level_wieldable_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, wieldable, p);
}

[[nodiscard]] auto level_is_unused3_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_unused3, p);
}

[[nodiscard]] auto level_is_able_to_wield_items_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_able_to_wield_items, p);
}

[[nodiscard]] auto level_is_wand_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_wand, p);
}

[[nodiscard]] auto level_is_staff_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_staff, p);
}

[[nodiscard]] auto level_is_argusul_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_argusul, p);
}

[[nodiscard]] auto level_is_wait_on_anim_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_wait_on_anim, p);
}

[[nodiscard]] auto level_is_flat_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_flat, p);
}

[[nodiscard]] auto level_is_obs_to_beam_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_obs_to_beam, p);
}

[[nodiscard]] auto level_is_beam_weapon_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_beam_weapon, p);
}

[[nodiscard]] auto level_is_shown_stamina_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_shown_stamina, p);
}

[[nodiscard]] auto level_is_reeds_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_reeds, p);
}

[[nodiscard]] auto level_is_unused4_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_unused4, p);
}

[[nodiscard]] auto level_is_vault_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_vault, p);
}

[[nodiscard]] auto level_is_biome_underhell_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_biome_underhell, p);
}

[[nodiscard]] auto level_is_biome_graveyard_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_biome_graveyard, p);
}

[[nodiscard]] auto level_is_biome_nethervoid_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_biome_nethervoid, p);
}

[[nodiscard]] auto level_is_biome_bogland_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_biome_bogland, p);
}

[[nodiscard]] auto level_is_biome_dungeon_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_biome_dungeon, p);
}

[[nodiscard]] auto level_is_level_open_icon_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_level_open_icon, p);
}

[[nodiscard]] auto level_is_blit_bg_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_blit_bg, p);
}

[[nodiscard]] auto level_is_level_select_bg_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_level_select_bg, p);
}

[[nodiscard]] auto level_is_blit_hit_outline_w_black_inside_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_blit_hit_outline_w_black_inside, p);
}

[[nodiscard]] auto level_is_unused5_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_unused5, p);
}

[[nodiscard]] auto level_is_able_to_fall_sound_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_able_to_fall_sound, p);
}

[[nodiscard]] auto level_is_collision_hit_first_on_tile_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_collision_hit_first_on_tile, p);
}

[[nodiscard]] auto level_is_collision_hit_all_on_tile_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_collision_hit_all_on_tile, p);
}

[[nodiscard]] auto level_is_blit_hit_outline_w_invis_inside_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_blit_hit_outline_w_invis_inside, p);
}

[[nodiscard]] auto level_is_blit_when_obscured_outline_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_blit_when_obscured_outline, p);
}

[[nodiscard]] auto level_is_attackable_by_player_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_attackable_by_player, p);
}

[[nodiscard]] auto level_is_attackable_by_monst_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_attackable_by_monst, p);
}

[[nodiscard]] auto level_is_effect_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_effect, p);
}

[[nodiscard]] auto level_is_effect_attack_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_effect_attack, p);
}

[[nodiscard]] auto level_is_effect_blood_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_effect_blood, p);
}

[[nodiscard]] auto level_is_unused6_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_unused6, p);
}

[[nodiscard]] auto level_is_hit_when_dead_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_hit_when_dead, p);
}

[[nodiscard]] auto level_is_blitzhound_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_blitzhound, p);
}

[[nodiscard]] auto level_is_potion_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_potion, p);
}

[[nodiscard]] auto level_is_grouped_thing_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_grouped_thing, p);
}

[[nodiscard]] auto level_is_vision_360_degrees_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_vision_360_degrees, p);
}

[[nodiscard]] auto level_is_vision_180_degrees_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_vision_180_degrees, p);
}

[[nodiscard]] auto level_is_able_to_lunge_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_able_to_lunge, p);
}

[[nodiscard]] auto level_is_obs_to_paths_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_obs_to_paths, p);
}

[[nodiscard]] auto level_is_stealthy_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_stealthy, p);
}

[[nodiscard]] auto level_is_tireless_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_tireless, p);
}

[[nodiscard]] auto level_is_shown_noise_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_shown_noise, p);
}

[[nodiscard]] auto level_is_wait_on_dead_anim_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_wait_on_dead_anim, p);
}

[[nodiscard]] auto level_is_wall_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_wall, p);
}

[[nodiscard]] auto level_is_water_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_water, p);
}

[[nodiscard]] auto level_is_wood_cached(Gamep g, Levelsp v, Levelp l, const bpoint &p) -> bool
{
  TRACE_DEBUG();
  return level_flag_cached(g, v, l, is_wood, p);
}
