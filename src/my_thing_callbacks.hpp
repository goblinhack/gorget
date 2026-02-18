//
// Copyright goblinhack@gmail.com
//

#ifndef _MY_THING_CALLBACKS_H_
#define _MY_THING_CALLBACKS_H_

#include "my_thing.hpp"
#include "my_tile.hpp"
#include "my_tp.hpp"
#include <string>

using thing_display_get_tile_info_t = Tilep (*)(Gamep, Levelsp, Levelp, spoint p, Tpp tp, Thingp t_maybe_null);
void  thing_display_get_tile_info_set(Tpp tp, thing_display_get_tile_info_t /*callback*/);
Tilep thing_display_get_tile_info(Gamep g, Levelsp v, Levelp l, spoint p, Tpp tp, Thingp t_maybe_null);

using thing_assess_tile_t = ThingEnviron (*)(Gamep, Levelsp, Levelp, spoint p, Thingp me);
void         thing_assess_tile_set(Tpp tp, thing_assess_tile_t /*callback*/);
ThingEnviron thing_assess_tile(Gamep g, Levelsp v, Levelp l, spoint p, Thingp me);

using thing_description_get_t = std::string (*)(Gamep, Levelsp, Levelp, Thingp me);
void        thing_description_set(Tpp tp, thing_description_get_t /*callback*/);
std::string thing_description_get(Gamep g, Levelsp v, Levelp l, Thingp me);

using thing_detail_get_t = std::string (*)(Gamep, Levelsp, Levelp, Thingp me);
void        thing_detail_set(Tpp tp, thing_detail_get_t /*callback*/);
std::string thing_detail_get(Gamep g, Levelsp v, Levelp l, Thingp me);

using thing_mouse_down_t = bool (*)(Gamep, Levelsp, Levelp, Thingp me, int x, int y, int button);
void thing_mouse_down_set(Tpp tp, thing_mouse_down_t /*callback*/);
bool thing_mouse_down(Gamep g, Levelsp v, Levelp l, Thingp me, int x, int y, int button);

using thing_on_spawned_t = void (*)(Gamep, Levelsp, Levelp, Thingp me);
void thing_on_spawned_set(Tpp tp, thing_on_spawned_t /*callback*/);
void thing_on_spawned(Gamep g, Levelsp v, Levelp l, Thingp me);

using thing_on_level_enter_t = void (*)(Gamep, Levelsp, Levelp, Thingp me);
void thing_on_level_enter_set(Tpp tp, thing_on_level_enter_t /*callback*/);
void thing_on_level_enter(Gamep g, Levelsp v, Levelp l, Thingp me);

using thing_on_level_leave_t = void (*)(Gamep, Levelsp, Levelp, Thingp me);
void thing_on_level_leave_set(Tpp tp, thing_on_level_leave_t /*callback*/);
void thing_on_level_leave(Gamep g, Levelsp v, Levelp l, Thingp me);

using thing_on_level_populated_t = void (*)(Gamep, Levelsp, Levelp, Thingp me);
void thing_on_level_populated_set(Tpp tp, thing_on_level_populated_t /*callback*/);
void thing_on_level_populated(Gamep g, Levelsp v, Levelp l, Thingp me);

using thing_on_carry_request_t = bool (*)(Gamep, Levelsp, Levelp, Thingp me, Thingp player_or_monst);
void thing_on_carry_request_set(Tpp tp, thing_on_carry_request_t /*callback*/);
bool thing_on_carry_request(Gamep g, Levelsp v, Levelp l, Thingp me, Thingp player_or_monst);

using thing_on_drop_request_t = bool (*)(Gamep, Levelsp, Levelp, Thingp me, Thingp player_or_monst);
void thing_on_drop_request_set(Tpp tp, thing_on_drop_request_t /*callback*/);
bool thing_on_drop_request(Gamep g, Levelsp v, Levelp l, Thingp me, Thingp player_or_monst);

using thing_on_open_request_t = bool (*)(Gamep, Levelsp, Levelp, Thingp me, Thingp player_or_monst);
void thing_on_open_request_set(Tpp tp, thing_on_open_request_t /*callback*/);
bool thing_on_open_request(Gamep g, Levelsp v, Levelp l, Thingp me, Thingp player_or_monst);

using thing_on_close_request_t = bool (*)(Gamep, Levelsp, Levelp, Thingp me, Thingp player_or_monst);
void thing_on_close_request_set(Tpp tp, thing_on_close_request_t /*callback*/);
bool thing_on_close_request(Gamep g, Levelsp v, Levelp l, Thingp me, Thingp player_or_monst);

using thing_on_tick_idle_t = void (*)(Gamep, Levelsp, Levelp, Thingp me);
void thing_on_tick_idle_set(Tpp tp, thing_on_tick_idle_t /*callback*/);
void thing_on_tick_idle(Gamep g, Levelsp v, Levelp l, Thingp me);

using thing_on_tick_begin_t = void (*)(Gamep, Levelsp, Levelp, Thingp me);
void thing_on_tick_begin_set(Tpp tp, thing_on_tick_begin_t /*callback*/);
void thing_on_tick_begin(Gamep g, Levelsp v, Levelp l, Thingp me);

using thing_on_tick_end_t = void (*)(Gamep, Levelsp, Levelp, Thingp me);
void thing_on_tick_end_set(Tpp tp, thing_on_tick_end_t /*callback*/);
void thing_on_tick_end(Gamep g, Levelsp v, Levelp l, Thingp me);

using thing_on_death_t = void (*)(Gamep, Levelsp, Levelp, Thingp me, ThingEvent &);
void thing_on_death_set(Tpp tp, thing_on_death_t /*callback*/);
void thing_on_death(Gamep g, Levelsp v, Levelp l, Thingp me, ThingEvent &e);

using thing_on_moved_t = void (*)(Gamep, Levelsp, Levelp, Thingp me);
void thing_on_moved_set(Tpp tp, thing_on_moved_t /*callback*/);
void thing_on_moved(Gamep g, Levelsp v, Levelp l, Thingp me);

using thing_on_teleported_t = void (*)(Gamep, Levelsp, Levelp, Thingp me);
void thing_on_teleported_set(Tpp tp, thing_on_teleported_t /*callback*/);
void thing_on_teleported(Gamep g, Levelsp v, Levelp l, Thingp me);

using thing_on_shoved_t = void (*)(Gamep, Levelsp, Levelp, Thingp me, Thingp shover);
void thing_on_shoved_set(Tpp tp, thing_on_shoved_t /*callback*/);
void thing_on_shoved(Gamep g, Levelsp v, Levelp l, Thingp me, Thingp shover);

using thing_on_jump_begin_t = void (*)(Gamep, Levelsp, Levelp, Thingp me);
void thing_on_jump_begin_set(Tpp tp, thing_on_jump_begin_t /*callback*/);
void thing_on_jump_begin(Gamep g, Levelsp v, Levelp l, Thingp me);

using thing_on_jump_end_t = void (*)(Gamep, Levelsp, Levelp, Thingp me);
void thing_on_jump_end_set(Tpp tp, thing_on_jump_end_t /*callback*/);
void thing_on_jump_end(Gamep g, Levelsp v, Levelp l, Thingp me);

using thing_on_fall_begin_t = void (*)(Gamep, Levelsp, Levelp, Thingp me);
void thing_on_fall_begin_set(Tpp tp, thing_on_fall_begin_t /*callback*/);
void thing_on_fall_begin(Gamep g, Levelsp v, Levelp l, Thingp me);

using thing_on_melt_t = void (*)(Gamep, Levelsp, Levelp, Thingp me);
void thing_on_melt_set(Tpp tp, thing_on_melt_t /*callback*/);
void thing_on_melt(Gamep g, Levelsp v, Levelp l, Thingp me);

using thing_on_fall_end_t = void (*)(Gamep, Levelsp, Levelp, Thingp me);
void thing_on_fall_end_set(Tpp tp, thing_on_fall_end_t /*callback*/);
void thing_on_fall_end(Gamep g, Levelsp v, Levelp l, Thingp me);

using thing_on_hit_begin_t = void (*)(Gamep, Levelsp, Levelp, Thingp me);
void thing_on_hit_begin_set(Tpp tp, thing_on_hit_begin_t /*callback*/);
void thing_on_hit_begin(Gamep g, Levelsp v, Levelp l, Thingp me);

using thing_on_hit_end_t = void (*)(Gamep, Levelsp, Levelp, Thingp me);
void thing_on_hit_end_set(Tpp tp, thing_on_hit_end_t /*callback*/);
void thing_on_hit_end(Gamep g, Levelsp v, Levelp l, Thingp me);

#endif
