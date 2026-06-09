//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_game.hpp"
#include "my_level.hpp"
#include "my_level_inlines.hpp" // NOLINT
#include "my_main.hpp"
#include "my_spoint.hpp"
#include "my_sprintf.hpp"
#include "my_string.hpp"
#include "my_thing.hpp"
#include "my_thing_callbacks.hpp"
#include "my_thing_inlines.hpp" // NOLINT
#include "my_tile.hpp"
#include "my_tp.hpp"
#include "my_types.hpp"
#include "my_ui.hpp"
#include "my_wid.hpp"
#include "my_wid_popup.hpp"
#include "my_wid_text_box.hpp"
#include "my_wids.hpp"

#include <algorithm>
#include <cstdint>
#include <cstring>
#include <format>
#include <string>

[[nodiscard]] auto wid_thing_info_keys(Gamep g, Levelsp v, Levelp l, Thingp me, WidPopup *parent) -> bool
{
  TRACE();

  auto *text = parent->wid_text_area;
  auto *b    = parent->wid_text_area->wid_text_area;

  auto key_count = thing_keys_carried(me);
  if (key_count == 0) {
    return false;
  }

  {
    auto        *tile = tile_find_mand("key.0");
    auto        *w    = wid_new_square_button(g, b, "Keys");
    spoint const tl(UI_LEFTBAR_WIDTH - 8, text->line_count);
    spoint const br(UI_LEFTBAR_WIDTH - 5, text->line_count + 2);
    wid_set_tile(TILE_LAYER_BOX_BG, w, tile);
    wid_set_style(w, UI_WID_STYLE_SPARSE_NONE);
    wid_set_pos(w, tl, br);
  }

  {
    auto        *w = wid_new_square_button(g, b, "Key count");
    spoint const tl(UI_LEFTBAR_WIDTH - 4, text->line_count);
    spoint const br(UI_LEFTBAR_WIDTH - 2, text->line_count + 2);
    std::string  how_many_keys = "x" + std::to_string(key_count);

    if (key_count > 9) {
      how_many_keys = std::to_string(key_count);
    }

    wid_set_text(w, how_many_keys);
    wid_set_shape_none(w);
    wid_set_pos(w, tl, br);
  }

  return true;
}

//
// The thing name
//
[[nodiscard]] auto wid_thing_info_name(Gamep g, Levelsp v, Levelp l, Thingp me, WidPopup *parent) -> bool
{
  TRACE();

  std::string name_str;
  if (thing_is_player(me)) {
    name_str = game_player_name_get(g);
  } else {
    name_str = thing_name_long(g, v, l, me);
  }
  name_str = capitalize(name_str);

  parent->log(g, UI_INFO_FMT_STR + name_str + UI_RESET_FMT);

  return true;
}

//
// The thing description
//
[[nodiscard]] auto wid_thing_info_detail(Gamep g, Levelsp v, Levelp l, Thingp me, WidPopup *parent) -> bool
{
  TRACE();

  if (thing_is_dead(me)) {
    return false;
  }

  parent->log(g, thing_detail_get(g, v, l, me), TEXT_FORMAT_LHS);

  return true;
}

//
// Score
//
[[nodiscard]] auto wid_thing_info_score(Gamep g, Levelsp v, Levelp l, Thingp me, WidPopup *parent) -> bool
{
  TRACE();

  if (! thing_is_player(me)) {
    return false;
  }

  auto *player_struct = thing_player_struct(g);
  if (player_struct == nullptr) {
    return false;
  }

  auto score    = player_struct->score;
  auto hiscore  = game_hiscore_get(g);
  auto maxscore = std::max(score, hiscore);

  auto score_str = string_sprintf(
      // newline
      UI_INFO1_FMT_STR "Score "
      // newline
      UI_INFO2_FMT_STR " %06u "
      // newline
      UI_INFO1_FMT_STR " Hiscore "
      // newline
      UI_INFO2_FMT_STR " %06u",
      // newline
      score,
      // newline
      maxscore);

  parent->log(g, score_str);

  return true;
}

//
// Health bar
//
[[nodiscard]] auto wid_thing_info_health_bar(Gamep g, Levelsp v, Levelp l, Thingp me, Tpp tp, WidPopup *parent, int width) -> bool
{
  TRACE();

  if (! tp_is_health_visible(tp)) {
    return false;
  }

  char line_bar[ MAXSHORTSTR ];

  //
  // "Health            "
  //
  memset(line_bar, 0, sizeof(line_bar));
  memset(line_bar, ' ', sizeof(line_bar) - 1);

  if (thing_is_dead(me)) {
    my_strlcpy(line_bar + 1, "Dead", sizeof("Dead "));
  } else {
    my_strlcpy(line_bar + 1, "Health", sizeof("Health "));
  }

  //
  // "Health         a/b"
  //
  auto health_max = thing_health_max(g, v, l, me);
  auto h          = thing_health(g, v, l, me);
  h               = std::max(h, 0);

  std::string const health_str = std::to_string(h) + "/" + std::to_string(health_max);
  my_strlcpy(line_bar + width - health_str.size() - 3, health_str.c_str(), width - health_str.size());
  line_bar[ strlen(line_bar) ] = ' ';

  //
  // "Health         a/b"
  // "xxxxxxxxxxxxxxxxxx"
  //
  auto *w = parent->log(g, std::string(line_bar));
  if (w != nullptr) {
    int health_how_much = static_cast< int >((static_cast< float >(thing_health(g, v, l, me)) / static_cast< float >(health_max))
                                             * (static_cast< float > UI_STAT_BAR_STEPS - 1));
    health_how_much     = std::min(health_how_much, UI_STAT_BAR_STEPS - 1);
    health_how_much     = std::max(health_how_much, 0);
    auto icon           = "stat_bar." + std::to_string(health_how_much + 1);

    wid_set_shape_square(w);
    wid_set_style(w, UI_WID_STYLE_SPARSE_NONE);
    wid_set_color(w, WID_COLOR_TEXT_FG, UI_HIGHLIGHT_COLOR);
    wid_set_tilename(TILE_LAYER_BOX_BG, w, icon);
    wid_set_text_lhs(w, 1u);
  }

  return true;
}

//
// Stamina bar
//
[[nodiscard]] auto wid_thing_info_stamina_bar(Gamep g, Levelsp v, Levelp l, Thingp me, Tpp tp, WidPopup *parent, int width) -> bool
{
  TRACE();

  if (thing_is_dead(me)) {
    return false;
  }

  if (! tp_is_stamina_visible(tp)) {
    return false;
  }

  char line_bar[ MAXSHORTSTR ];

  //
  // "Stamina           "
  //
  memset(line_bar, 0, sizeof(line_bar));
  memset(line_bar, ' ', sizeof(line_bar) - 1);

  if (thing_distance_jump(g, v, l, me) != thing_distance_jump_max(g, v, l, me)) {
    my_strlcpy(line_bar + 1, "Jumping impacted", sizeof("Jumping impacted "));
  } else {
    my_strlcpy(line_bar + 1, "Stamina", sizeof("Stamina "));
  }

  //
  // "Stamina        a/b"
  //
  auto stamina_max = thing_stamina_max(g, v, l, me);
  auto h           = thing_stamina(g, v, l, me);
  h                = std::max(h, 0);

  std::string const stamina_str = std::to_string(h) + "/" + std::to_string(stamina_max);
  my_strlcpy(line_bar + width - stamina_str.size() - 3, stamina_str.c_str(), width - stamina_str.size());
  line_bar[ strlen(line_bar) ] = ' ';

  //
  // "Stamina        a/b"
  // "xxxxxxxxxxxxxxxxxx"
  //
  auto *w = parent->log(g, std::string(line_bar));
  if (w != nullptr) {
    int stamina_how_much = static_cast< int >((static_cast< float >(thing_stamina(g, v, l, me)) / static_cast< float >(stamina_max))
                                              * (static_cast< float > UI_STAT_BAR_STEPS - 1));
    stamina_how_much     = std::min(stamina_how_much, UI_STAT_BAR_STEPS - 1);
    stamina_how_much     = std::max(stamina_how_much, 0);
    auto icon            = "stat_bar." + std::to_string(stamina_how_much + 1);

    wid_set_shape_square(w);
    wid_set_style(w, UI_WID_STYLE_SPARSE_NONE);
    wid_set_color(w, WID_COLOR_TEXT_FG, UI_HIGHLIGHT_COLOR);
    wid_set_tilename(TILE_LAYER_BOX_BG, w, icon);
    wid_set_text_lhs(w, 1u);
  }

  return true;
}

//
// Add immunities
//
[[nodiscard]] auto wid_thing_info_immunity(Gamep g, Levelsp v, Levelp l, Thingp me, WidPopup *parent, int width) -> bool
{
  TRACE();

  bool printed_something = false;

  FOR_ALL_THING_EVENT(e)
  {
    if (! thing_is_immune_to(g, v, l, me, e)) {
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
[[nodiscard]] auto wid_thing_info_resistance(Gamep g, Levelsp v, Levelp l, Thingp me, WidPopup *parent, int width) -> bool
{
  TRACE();

  bool printed_something = false;

  FOR_ALL_THING_EVENT(e)
  {
    if (! thing_is_resistant_to(g, v, l, me, e)) {
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
// Add abilities
//
[[nodiscard]] static auto wid_thing_info_abilities(Gamep g, Thingp me, WidPopup *parent, int width) -> bool
{
  TRACE();

  bool printed_something = false;

  if (thing_is_ethereal(me)) {
    auto immune_str = string_sprintf("Abilitiy:  %*s", width - 13, "Ethereal");
    parent->log(g, immune_str, TEXT_FORMAT_LHS);
    printed_something = true;
  } else {
    //
    // Non ethereal
    //
    if (thing_is_able_to_walk_through_walls(me)) {
      auto immune_str = string_sprintf("Abilitiy:  %*s", width - 13, "Wall walker");
      parent->log(g, immune_str, TEXT_FORMAT_LHS);
      printed_something = true;
    }
    if (thing_is_floating(me)) {
      auto immune_str = string_sprintf("Abilitiy:  %*s", width - 13, "Floating");
      parent->log(g, immune_str, TEXT_FORMAT_LHS);
      printed_something = true;
    }
    if (thing_is_flying(me)) {
      auto immune_str = string_sprintf("Abilitiy:  %*s", width - 13, "Flying");
      parent->log(g, immune_str, TEXT_FORMAT_LHS);
      printed_something = true;
    }
  }

  if (thing_is_gaseous(me)) {
    auto immune_str = string_sprintf("Abilitiy:  %*s", width - 13, "Gaseous");
    parent->log(g, immune_str, TEXT_FORMAT_LHS);
    printed_something = true;
  }
  if (thing_is_slime(me)) {
    auto immune_str = string_sprintf("Abilitiy:  %*s", width - 13, "Slimey");
    parent->log(g, immune_str, TEXT_FORMAT_LHS);
    printed_something = true;
  }
  if (thing_is_able_to_collect_items(me)) {
    auto immune_str = string_sprintf("Abilitiy:  %*s", width - 13, "Collector");
    parent->log(g, immune_str, TEXT_FORMAT_LHS);
    printed_something = true;
  }
  if (thing_is_able_to_be_buffed(me)) {
    auto immune_str = string_sprintf("Abilitiy:  %*s", width - 13, "Buffable");
    parent->log(g, immune_str, TEXT_FORMAT_LHS);
    printed_something = true;
  }
  if (thing_is_able_to_jump(me)) {
    auto immune_str = string_sprintf("Abilitiy:  %*s", width - 13, "Jumper");
    parent->log(g, immune_str, TEXT_FORMAT_LHS);
    printed_something = true;
  }
  if (thing_is_able_to_throw_items(me)) {
    auto immune_str = string_sprintf("Abilitiy:  %*s", width - 13, "Thrower");
    parent->log(g, immune_str, TEXT_FORMAT_LHS);
    printed_something = true;
  }
  if (thing_is_able_to_wield_items(me)) {
    auto immune_str = string_sprintf("Abilitiy:  %*s", width - 13, "Wielder");
    parent->log(g, immune_str, TEXT_FORMAT_LHS);
    printed_something = true;
  }
  if (thing_is_burning(me)) {
    auto immune_str = string_sprintf("Abilitiy:  %*s", width - 13, "Burnable");
    parent->log(g, immune_str, TEXT_FORMAT_LHS);
    printed_something = true;
  }
  if (thing_is_flammable(me)) {
    auto immune_str = string_sprintf("Abilitiy:  %*s", width - 13, "Flammable");
    parent->log(g, immune_str, TEXT_FORMAT_LHS);
    printed_something = true;
  }
  if (thing_is_combustible(me)) {
    auto immune_str = string_sprintf("Abilitiy:  %*s", width - 13, "Combustible");
    parent->log(g, immune_str, TEXT_FORMAT_LHS);
    printed_something = true;
  }

  return printed_something;
}

static void wid_thing_info_item_mouse_over_begin(Gamep g, Widp w, int /*relx*/, int /*rely*/, int /*wheelx*/, int /*wheely*/)
{
  TRACE();

  auto *v = game_levels_get(g);
  if (v == nullptr) {
    return;
  }

  auto *t = wid_get_thing_context(g, v, w, 0);
  if (t == nullptr) {
    return;
  }

  level_cursor_describe_clear(g, v);
  (void) level_cursor_describe_add(g, v, t);
  (void) wid_rightbar_init(g);
}

static void wid_thing_info_item_mouse_over_end(Gamep g, Widp w)
{
  TRACE();

  auto *v = game_levels_get(g);
  if (v == nullptr) {
    return;
  }

  auto *t = wid_get_thing_context(g, v, w, 0);
  if (t == nullptr) {
    return;
  }

  (void) level_cursor_describe_remove(g, v, t);
  (void) wid_rightbar_init(g);
}

[[nodiscard]] static auto wid_thing_info_item_mouse_up(Gamep g, Widp w, int x, int y, uint32_t button) -> bool
{
  TRACE();

  auto *v = game_levels_get(g);
  if (v == nullptr) {
    return false;
  }

  auto *t = wid_get_thing_context(g, v, w, 0);
  if (t == nullptr) {
    return false;
  }

  if (game_state(g) != STATE_PLAYING) {
    return true;
  }

  wid_item_menu_select(g, v, t, false /* not from inventory */);

  return true;
}

//
// Items
//
[[nodiscard]] static auto wid_thing_info_items(Gamep g, Levelsp v, Levelp l, Thingp me, WidPopup *parent) -> bool
{
  TRACE();

  bool printed_something = false;

  if (! thing_is_player(me)) {
    return printed_something;
  }

  bool first = true;

  FOR_ALL_INVENTORY_SLOTS(g, v, l, me, slot, item)
  {
    auto *item_tp = (item != nullptr) ? thing_tp(item) : nullptr;
    if (item_tp == nullptr) {
      continue;
    }

    if (first) {
      first = false;
      (void) parent->log(g, "Carrying:", TEXT_FORMAT_LHS);
    }

    printed_something = true;

    std::string line = "- ";

    line += "%%tp=";
    line += tp_name(item_tp);
    line += "$";
    line += " ";
    line += thing_name_short(g, v, l, item);

    if (slot->count > 1) {
      line += " x";
      line += std::to_string(slot->count);
    }

    line += " ";

    auto charge_count = thing_charge_count(item);
    if (charge_count > 0) {
      line += std::to_string(charge_count);
      line += "%%tile=icon_lightning$";
    }

    if (thing_is_wielded(item)) {
      line += "%%tile=icon_hand$";
    }

    Widp w = parent->log(g, line, TEXT_FORMAT_LHS);

    wid_set_thing_context(g, v, w, item);
    wid_set_on_mouse_up(w, wid_thing_info_item_mouse_up);
    wid_set_on_mouse_over_begin(w, wid_thing_info_item_mouse_over_begin);
    wid_set_on_mouse_over_end(w, wid_thing_info_item_mouse_over_end);
  }

  return printed_something;
}

//
// Buffs
//
[[nodiscard]] static auto wid_thing_info_buffs(Gamep g, Levelsp v, Levelp l, Thingp me, WidPopup *parent) -> bool
{
  TRACE();

  bool printed_something = false;

  if (! thing_is_player(me)) {
    return printed_something;
  }

  bool first = true;

  FOR_ALL_BUFFS(g, v, l, me, buff)
  {
    if (first) {
      first = false;
      (void) parent->log(g, "Buffs:", TEXT_FORMAT_LHS);
    }

    printed_something = true;

    std::string line = "- ";

    line += thing_name_short(g, v, l, buff);

    auto lifespan = thing_lifespan(buff);
    if (lifespan > 0) {
      line += ", ";
      line += std::to_string(lifespan);
      line += " moves";
    }

    char line_bar[ MAXSHORTSTR ];

    memset(line_bar, 0, sizeof(line_bar));
    memset(line_bar, ' ', sizeof(line_bar) - 1);

    auto lifespan_max = thing_lifespan_initial(buff);
    auto h            = thing_lifespan(buff);
    h                 = std::max(h, 0);

    my_strlcpy(line_bar, line.c_str(), line.size() + 1);
    auto *w = parent->log(g, std::string(line_bar));
    if (w != nullptr) {
      int lifespan_how_much = static_cast< int >((static_cast< float >(thing_lifespan(buff)) / static_cast< float >(lifespan_max))
                                                 * (static_cast< float > UI_STAT_BAR_STEPS - 1));
      lifespan_how_much     = std::min(lifespan_how_much, UI_STAT_BAR_STEPS - 1);
      lifespan_how_much     = std::max(lifespan_how_much, 0);
      auto icon             = "stat_bar." + std::to_string(lifespan_how_much + 1);

      wid_set_shape_square(w);
      wid_set_style(w, UI_WID_STYLE_SPARSE_NONE);
      wid_set_color(w, WID_COLOR_TEXT_FG, UI_HIGHLIGHT_COLOR);
      wid_set_tilename(TILE_LAYER_BOX_BG, w, icon);
      wid_set_text_lhs(w, 1u);
      wid_set_thing_context(g, v, w, buff);
      wid_set_on_mouse_over_begin(w, wid_thing_info_item_mouse_over_begin);
      wid_set_on_mouse_over_end(w, wid_thing_info_item_mouse_over_end);
    }
  }

  return printed_something;
}

//
// Display detailed thing information
//
void wid_thing_info(Gamep g, Levelsp v, Levelp l, Thingp me, WidPopup *parent, int width)
{
  ////////////////////////////////////////////////////////////////////////////////
  // Careful here. If we invoked the random number generator in here it can throw
  // off tests.
  ////////////////////////////////////////////////////////////////////////////////

  TRACE();

  if (me == nullptr) {
    return;
  }

  auto *tp = thing_tp(me);
  if (tp == nullptr) [[unlikely]] {
    return;
  }

  if (wid_tp_info_icon(g, tp, parent)) {
    parent->log_empty_line(g);
  }

  (void) wid_thing_info_keys(g, v, l, me, parent);

  if (wid_thing_info_name(g, v, l, me, parent)) {
    parent->log_empty_line(g);
  }

  if (wid_thing_info_detail(g, v, l, me, parent)) {
    parent->log_empty_line(g);
  }

  if (wid_thing_info_score(g, v, l, me, parent)) {
    parent->log_empty_line(g);
  }

  if (wid_thing_info_health_bar(g, v, l, me, tp, parent, width)) {
    parent->log_empty_line(g);
  }

  if (wid_thing_info_stamina_bar(g, v, l, me, tp, parent, width)) {
    parent->log_empty_line(g);
  }

  if (wid_thing_info_buffs(g, v, l, me, parent)) {
    parent->log_empty_line(g);
  }

  if (thing_is_monst(me)) {
    if (wid_tp_info_damage(g, v, l, tp, parent, width)) {
      parent->log_empty_line(g);
    }

    if (wid_thing_info_immunity(g, v, l, me, parent, width)) {
      parent->log_empty_line(g);
    }

    if (wid_thing_info_resistance(g, v, l, me, parent, width)) {
      parent->log_empty_line(g);
    }

    if (wid_thing_info_abilities(g, me, parent, width)) {
      parent->log_empty_line(g);
    }
  }

  if (wid_thing_info_items(g, v, l, me, parent)) {
    parent->log_empty_line(g);
  }

  auto *owner = thing_owner(g, v, l, me);
  if (owner != nullptr) {
    auto *fire_what_tp = thing_on_use_weapon_request(g, v, l, me, owner);
    if (fire_what_tp != nullptr) {
      wid_tp_info(g, v, l, fire_what_tp, parent, width);
    }
  }

  IF_DEBUG
  {
    parent->log(g, "Thing:");
    parent->log(g, to_string(g, v, l, me), TEXT_FORMAT_LHS);
    parent->log_empty_line(g);
    parent->log(g, "Things:");

    //
    // Dump the contents at this tile
    //
    auto at = thing_at(me);
    FOR_ALL_THINGS_AT_UNSAFE(g, v, l, it, at)
    {
      auto s = std::format("- {}", thing_name_short(g, v, l, it));
      parent->log(g, s, TEXT_FORMAT_LHS);
    }
  }
}
