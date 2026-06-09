//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_level_inlines.hpp" // NOLINT
#include "my_spoint.hpp"
#include "my_sprintf.hpp"
#include "my_string.hpp"
#include "my_thing.hpp"
#include "my_thing_inlines.hpp" // NOLINT
#include "my_tile.hpp"
#include "my_tp.hpp"
#include "my_types.hpp"
#include "my_ui.hpp"
#include "my_wid.hpp"
#include "my_wid_popup.hpp"
#include "my_wid_text_box.hpp"

#include <cstring>
#include <string>

//
// The tp icon
//
[[nodiscard]] auto wid_tp_info_icon(Gamep g, Tpp me, WidPopup *parent) -> bool
{
  TRACE();

  auto *text = parent->wid_text_area;
  auto *b    = parent->wid_text_area->wid_text_area;

  if (tp_tiles_size(me, THING_ANIM_IDLE) == 0) {
    return false;
  }

  Tilep tile = tp_tiles_get(me, THING_ANIM_IDLE, 0);
  if (tile == nullptr) {
    return false;
  }

  auto        *w = wid_new_square_button(g, b, "Icon");
  spoint const tl(0, text->line_count);
  spoint const br(3, text->line_count + 2);
  wid_set_tile(TILE_LAYER_BOX_BG, w, tile);
  wid_set_style(w, UI_WID_STYLE_SPARSE_NONE);
  wid_set_pos(w, tl, br);

  return true;
}

//
// The tp name
//
[[nodiscard]] static auto wid_tp_info_name(Gamep g, Levelsp v, Levelp l, Tpp me, WidPopup *parent) -> bool
{
  TRACE();

  std::string name_str;
  name_str = tp_name_long(me);
  name_str = capitalize(name_str);

  parent->log(g, UI_INFO_FMT_STR + name_str + UI_RESET_FMT);

  return true;
}

//
// Add damage types
//
[[nodiscard]] auto wid_tp_info_damage(Gamep g, Levelsp v, Levelp l, Tpp me, WidPopup *parent, int width) -> bool
{
  TRACE();

  bool printed_something = false;

  FOR_ALL_THING_EVENT(e)
  {
    auto damage_str = tp_damage_string(me, e);
    if (damage_str.empty()) {
      continue;
    }

    bool show_string = false;

    switch (e) {
      case THING_EVENT_SHOVED : //
        show_string = false;
        break;
      case THING_EVENT_CRUSH : //
        show_string = false;
        break;
      case THING_EVENT_LIGHT_DAMAGE : //
        show_string = true;
        break;
      case THING_EVENT_MELEE_DAMAGE : //
        show_string = true;
        break;
      case THING_EVENT_EXPLOSION_DAMAGE : //
        show_string = true;
        break;
      case THING_EVENT_FIRE_DAMAGE : //
        show_string = true;
        break;
      case THING_EVENT_WATER_DAMAGE : //
        show_string = true;
        break;
      case THING_EVENT_NONE :             [[fallthrough]];
      case THING_EVENT_THE_END :          [[fallthrough]];
      case THING_EVENT_MELT :             [[fallthrough]];
      case THING_EVENT_OPEN :             [[fallthrough]];
      case THING_EVENT_LIFESPAN_EXPIRED : [[fallthrough]];
      case THING_EVENT_FALL :             [[fallthrough]];
      case THING_EVENT_CARRIED :          [[fallthrough]];
      case THING_EVENT_CARRIED_MERGED :   [[fallthrough]];
      case THING_EVENT_USER_INITIATED :   [[fallthrough]];
      case THING_EVENT_SPAWNED :          [[fallthrough]];
      case THING_EVENT_THROWN :           [[fallthrough]];
      case THING_EVENT_USED :             [[fallthrough]];
      case THING_EVENT_ENUM_MAX : //
        show_string = false;
        break;
    }

    if (! show_string) {
      continue;
    }

    auto space = (width - 2) / 2;
    auto line  = string_sprintf("%-*s%*s",                                              //
                                space, capitalize(ThingEventType_to_string(e)).c_str(), //
                                space, damage_str.c_str());
    parent->log(g, line, TEXT_FORMAT_LHS);
    printed_something = true;
  }

  return printed_something;
}

//
// Add immunities
//
[[nodiscard]] static auto wid_tp_info_immunity(Gamep g, Levelsp v, Levelp l, Tpp me, WidPopup *parent, int width) -> bool
{
  TRACE();

  bool printed_something = false;

  FOR_ALL_THING_EVENT(e)
  {
    if (! tp_is_immune_to(me, e)) {
      continue;
    }

    bool show_string = false;

    switch (e) {
      case THING_EVENT_SHOVED : //
        show_string = false;
        break;
      case THING_EVENT_CRUSH : //
        show_string = false;
        break;
      case THING_EVENT_LIGHT_DAMAGE : //
        show_string = true;
        break;
      case THING_EVENT_MELEE_DAMAGE : //
        show_string = true;
        break;
      case THING_EVENT_EXPLOSION_DAMAGE : //
        show_string = true;
        break;
      case THING_EVENT_FIRE_DAMAGE : //
        show_string = true;
        break;
      case THING_EVENT_WATER_DAMAGE : //
        show_string = true;
        break;
      case THING_EVENT_NONE :             [[fallthrough]];
      case THING_EVENT_THE_END :          [[fallthrough]];
      case THING_EVENT_MELT :             [[fallthrough]];
      case THING_EVENT_OPEN :             [[fallthrough]];
      case THING_EVENT_LIFESPAN_EXPIRED : [[fallthrough]];
      case THING_EVENT_FALL :             [[fallthrough]];
      case THING_EVENT_CARRIED :          [[fallthrough]];
      case THING_EVENT_CARRIED_MERGED :   [[fallthrough]];
      case THING_EVENT_USER_INITIATED :   [[fallthrough]];
      case THING_EVENT_SPAWNED :          [[fallthrough]];
      case THING_EVENT_THROWN :           [[fallthrough]];
      case THING_EVENT_USED :             [[fallthrough]];
      case THING_EVENT_ENUM_MAX : //
        show_string = false;
        break;
    }

    if (! show_string) {
      continue;
    }

    auto immune_str = string_sprintf("Immunity:  %*s", width - 13, capitalize(ThingEventType_to_string(e)).c_str());
    parent->log(g, immune_str, TEXT_FORMAT_LHS);
    printed_something = true;
  }

  return printed_something;
}

//
// Add resistances
//
[[nodiscard]] static auto wid_tp_info_resistance(Gamep g, Levelsp v, Levelp l, Tpp me, WidPopup *parent, int width) -> bool
{
  TRACE();

  bool printed_something = false;

  FOR_ALL_THING_EVENT(e)
  {
    if (! tp_is_resistant_to(me, e)) {
      continue;
    }

    bool show_string = false;

    switch (e) {
      case THING_EVENT_SHOVED : //
        show_string = false;
        break;
      case THING_EVENT_CRUSH : //
        show_string = false;
        break;
      case THING_EVENT_LIGHT_DAMAGE : //
        show_string = true;
        break;
      case THING_EVENT_MELEE_DAMAGE : //
        show_string = true;
        break;
      case THING_EVENT_EXPLOSION_DAMAGE : //
        show_string = true;
        break;
      case THING_EVENT_FIRE_DAMAGE : //
        show_string = true;
        break;
      case THING_EVENT_WATER_DAMAGE : //
        show_string = true;
        break;
      case THING_EVENT_NONE :             [[fallthrough]];
      case THING_EVENT_THE_END :          [[fallthrough]];
      case THING_EVENT_MELT :             [[fallthrough]];
      case THING_EVENT_OPEN :             [[fallthrough]];
      case THING_EVENT_LIFESPAN_EXPIRED : [[fallthrough]];
      case THING_EVENT_FALL :             [[fallthrough]];
      case THING_EVENT_CARRIED :          [[fallthrough]];
      case THING_EVENT_CARRIED_MERGED :   [[fallthrough]];
      case THING_EVENT_USER_INITIATED :   [[fallthrough]];
      case THING_EVENT_SPAWNED :          [[fallthrough]];
      case THING_EVENT_THROWN :           [[fallthrough]];
      case THING_EVENT_USED :             [[fallthrough]];
      case THING_EVENT_ENUM_MAX : //
        show_string = false;
        break;
    }

    if (! show_string) {
      continue;
    }

    auto resist_str = string_sprintf("Resists:   %*s", width - 13, capitalize(ThingEventType_to_string(e)).c_str());
    parent->log(g, resist_str, TEXT_FORMAT_LHS);
    printed_something = true;
  }

  return printed_something;
}

//
// Display detailed tp information
//
void wid_tp_info(Gamep g, Levelsp v, Levelp l, Tpp me, WidPopup *parent, int width)
{
  ////////////////////////////////////////////////////////////////////////////////
  // Careful here. If we invoked the random number generator in here it can throw
  // off tests.
  ////////////////////////////////////////////////////////////////////////////////

  TRACE();

  if (me == nullptr) {
    return;
  }

  if (wid_tp_info_icon(g, me, parent)) {
    parent->log_empty_line(g);
  }

  if (wid_tp_info_name(g, v, l, me, parent)) {
    parent->log_empty_line(g);
  }

  if (wid_tp_info_damage(g, v, l, me, parent, width)) {
    parent->log_empty_line(g);
  }

  if (wid_tp_info_immunity(g, v, l, me, parent, width)) {
    parent->log_empty_line(g);
  }

  if (wid_tp_info_resistance(g, v, l, me, parent, width)) {
    parent->log_empty_line(g);
  }
}
