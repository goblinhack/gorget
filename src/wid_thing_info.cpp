//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_game.hpp"
#include "my_game_defs.hpp"
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

  if (! tp_is_shown_health(tp)) {
    return false;
  }

  char line_bar[ MAXSHORTSTR ];

  //
  // "Health            "
  //
  memset(line_bar, 0, sizeof(line_bar));
  memset(line_bar, ' ', sizeof(line_bar) - 1);

  if (thing_is_dead(me)) {
    (void) my_strlcpy(line_bar + 1, "Dead", sizeof("Dead "));
  } else {
    (void) my_strlcpy(line_bar + 1, "Health", sizeof("Health "));
  }

  //
  // "Health         a/b"
  //
  auto health_max = thing_health_max(g, v, l, me);
  auto h          = thing_health(g, v, l, me);
  h               = std::max(h, 0);

  std::string const health_str = std::to_string(h) + "/" + std::to_string(health_max);
  (void) my_strlcpy(line_bar + width - health_str.size() - 3, health_str.c_str(), width - health_str.size());
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

  if (! tp_is_shown_stamina(tp)) {
    return false;
  }

  char line_bar[ MAXSHORTSTR ];

  //
  // "Stamina           "
  //
  memset(line_bar, 0, sizeof(line_bar));
  memset(line_bar, ' ', sizeof(line_bar) - 1);

  if (thing_distance_jump(g, v, l, me) != thing_distance_jump_max(g, v, l, me)) {
    (void) my_strlcpy(line_bar + 1, "Jumping impacted", sizeof("Jumping impacted "));
  } else {
    (void) my_strlcpy(line_bar + 1, "Stamina", sizeof("Stamina "));
  }

  //
  // "Stamina        a/b"
  //
  auto stamina_max = thing_stamina_max(g, v, l, me);
  auto stamina     = thing_stamina(g, v, l, me);
  stamina          = std::max(stamina, 0);

  std::string const stamina_str = std::to_string(stamina) + "/" + std::to_string(stamina_max);
  (void) my_strlcpy(line_bar + width - stamina_str.size() - 3, stamina_str.c_str(), width - stamina_str.size());
  line_bar[ strlen(line_bar) ] = ' ';

  //
  // "Stamina        a/b"
  // "xxxxxxxxxxxxxxxxxx"
  //
  auto *w = parent->log(g, std::string(line_bar));
  if (w != nullptr) {
    int stamina_how_much
        = static_cast< int >((static_cast< float >(stamina) / static_cast< float >(stamina_max)) * (static_cast< float > UI_STAT_BAR_STEPS - 1));
    stamina_how_much = std::min(stamina_how_much, UI_STAT_BAR_STEPS - 1);
    stamina_how_much = std::max(stamina_how_much, 0);
    auto icon        = "stat_bar." + std::to_string(stamina_how_much + 1);

    wid_set_shape_square(w);
    wid_set_style(w, UI_WID_STYLE_SPARSE_NONE);
    wid_set_color(w, WID_COLOR_TEXT_FG, UI_HIGHLIGHT_COLOR);
    wid_set_tilename(TILE_LAYER_BOX_BG, w, icon);
    wid_set_text_lhs(w, 1u);
  }

  return true;
}

//
// Stealth bar
//
[[nodiscard]] static auto wid_thing_info_noise_bar(Gamep g, Levelsp v, Levelp l, Thingp me, Tpp tp, WidPopup *parent, int width) -> bool
{
  TRACE();

  if (thing_is_dead(me)) {
    return false;
  }

  if (! tp_is_shown_noise(tp)) {
    return false;
  }

  char line_bar[ MAXSHORTSTR ];

  //
  // "Stealth           "
  //
  memset(line_bar, 0, sizeof(line_bar));
  memset(line_bar, ' ', sizeof(line_bar) - 1);
  (void) my_strlcpy(line_bar + 1, "Stealth", sizeof("Stealth "));

  //
  // "Stealth        a/b"
  //
  auto stealth_max = THING_NOISE_MAX;
  auto stealth     = THING_NOISE_MAX - thing_noise(g, v, l, me);
  stealth          = std::max(stealth, 0);

  std::string const stealth_str = std::to_string(stealth) + "/" + std::to_string(stealth_max);
  (void) my_strlcpy(line_bar + width - stealth_str.size() - 3, stealth_str.c_str(), width - stealth_str.size());
  line_bar[ strlen(line_bar) ] = ' ';

  //
  // "Stealth        a/b"
  // "xxxxxxxxxxxxxxxxxx"
  //
  auto *w = parent->log(g, std::string(line_bar));
  if (w != nullptr) {
    int stealth_how_much
        = static_cast< int >((static_cast< float >(stealth) / static_cast< float >(stealth_max)) * (static_cast< float > UI_STAT_BAR_STEPS - 1));
    stealth_how_much = std::min(stealth_how_much, UI_STAT_BAR_STEPS - 1);
    stealth_how_much = std::max(stealth_how_much, 0);
    auto icon        = "stat_bar." + std::to_string(stealth_how_much + 1);

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
[[nodiscard]] auto wid_thing_info_immunity(Gamep g, Levelsp v, Levelp l, Thingp me, WidPopup *parent, int /*width*/) -> bool
{
  TRACE();

  std::string out;

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

    out = string_append_with_comma(out, capitalize(ThingEventType_to_string(e)));
  }

  if (out.empty()) {
    return false;
  }

  parent->log(g, UI_INFO_FMT_STR "Immunity:", TEXT_FORMAT_LHS);
  parent->log(g, "- " + out, TEXT_FORMAT_LHS);

  return true;
}

//
// Add resistances
//
[[nodiscard]] auto wid_thing_info_resistance(Gamep g, Levelsp v, Levelp l, Thingp me, WidPopup *parent, int /*width*/) -> bool
{
  TRACE();

  std::string out;

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

    out = string_append_with_comma(out, capitalize(ThingEventType_to_string(e)));
  }

  if (out.empty()) {
    return false;
  }

  parent->log(g, UI_INFO_FMT_STR "Resistances (half damage):", TEXT_FORMAT_LHS);
  parent->log(g, "- " + out, TEXT_FORMAT_LHS);

  return true;
}

//
// Add abilities
//
[[nodiscard]] static auto wid_thing_info_abilities(Gamep g, Thingp me, WidPopup *parent) -> bool
{
  TRACE();

  std::string out;

  auto *tp = thing_tp(me);

  if (thing_is_ethereal(me)) {
    out = string_append_with_comma(out, "Ethereal");
  } else {
    //
    // Non ethereal
    //
    if (thing_is_able_to_walk_through_walls(me)) {
      out = string_append_with_comma(out, "Wall-walker");
    }
    if (thing_is_floating(me)) {
      out = string_append_with_comma(out, "Floating");
    }
    if (thing_is_flying(me)) {
      out = string_append_with_comma(out, "Flying");
    }
  }

  if (thing_is_gaseous(me)) {
    out = string_append_with_comma(out, "Gaseous");
  }
  if (thing_is_slime(me)) {
    out = string_append_with_comma(out, "Slimey");
  }
  if (thing_is_able_to_collect_items(me)) {
    if (! thing_is_player(me)) {
      out = string_append_with_comma(out, "Collector");
    }
  }
  if (thing_is_able_to_be_buffed(me)) {
    if (! thing_is_player(me)) {
      out = string_append_with_comma(out, "Buffable");
    }
  }
  if (thing_is_able_to_throw_items(me)) {
    if (! thing_is_player(me)) {
      out = string_append_with_comma(out, "Jumper");
    }
  }
  if (thing_is_able_to_throw_items_items(me)) {
    if (! thing_is_player(me)) {
      out = string_append_with_comma(out, "Thrower");
    }
  }
  if (thing_is_able_to_wield_items(me)) {
    if (! thing_is_player(me)) {
      out = string_append_with_comma(out, "Wielder");
    }
  }
  if (thing_is_burning(me)) {
    if (! thing_is_player(me)) {
      out = string_append_with_comma(out, "Burnable");
    }
  }
  if (thing_is_flammable(me)) {
    if (! thing_is_player(me)) {
      out = string_append_with_comma(out, "Flammable");
    }
  }
  if (thing_is_combustible(me)) {
    if (! thing_is_player(me)) {
      out = string_append_with_comma(out, "Combustible");
    }
  }
  if (tp_attack_count_max_per_tick_get(tp) > 1) {
    out = string_sprintf_append_with_comma(out, "Multi-attack(%u)", tp_attack_count_max_per_tick_get(tp));
  }

  {
    auto *player = thing_player(g);
    if (player != nullptr) {
      const float player_speed = thing_speed(player);

      auto pct = static_cast< int >((thing_speed(me) / player_speed) * 100.0);

      if (thing_speed(me) > player_speed) {
        out = string_sprintf_append_with_comma(out, "Faster(%u%%%%%%)", pct);
      } else if (thing_speed(me) < player_speed) {
        out = string_sprintf_append_with_comma(out, "Slower(%u%%%%%%)", pct);
      }
    }
  }

  if (out.empty()) {
    return false;
  }

  parent->log(g, UI_INFO_FMT_STR "Abilities:", TEXT_FORMAT_LHS);
  parent->log(g, "- " + out, TEXT_FORMAT_LHS);

  return true;
}

//
// Add wielded weapon
//
[[nodiscard]] static auto wid_thing_info_wielded(Gamep g, Levelsp v, Levelp l, Thingp me, WidPopup *parent, int width) -> bool
{
  TRACE();

  auto weapon = thing_wielding(g, v, l, me);
  if (! weapon) {
    return false;
  }

  auto out = string_sprintf("Wielded(%s)", thing_name_short(g, v, l, weapon).c_str());
  parent->log(g, UI_INFO_FMT_STR + out, TEXT_FORMAT_LHS);

  (void) wid_tp_info_damage(g, v, l, thing_tp(weapon), parent, width, false /* title allowed */);
  (void) wid_tp_info_special_attacks(g, v, l, thing_tp(weapon), parent, width, false /* title allowed */);

  return true;
}

//
// Add danger level
//
[[nodiscard]] static auto wid_thing_info_danger(Gamep g, Levelsp v, Levelp l, Thingp me, WidPopup *parent) -> bool
{
  TRACE();

  auto *player = thing_player(g);
  if (player == nullptr) {
    return false;
  }

  //
  // Check for things mathing the dice roll first.
  //
  auto max_damage = thing_damage_max(g, v, l, me);
  if (max_damage == 0) {
    return false;
  }

  auto monst_defeat_count = thing_health(g, v, l, player) / max_damage;

  //
  // Oh dear. You my friend are toast.
  //
  if (monst_defeat_count == 0) {
    monst_defeat_count = 1;
  }

  parent->log(g, UI_INFO_FMT_STR "Danger level:", TEXT_FORMAT_LHS);

  if (monst_defeat_count == 1) {
    parent->log(g, UI_IMPORTANT_FMT_STR "- Could defeat you in " + std::to_string(monst_defeat_count) + " hit!", TEXT_FORMAT_LHS);
  } else if (monst_defeat_count <= 2) {
    parent->log(g, UI_IMPORTANT_FMT_STR "- Could defeat you in " + std::to_string(monst_defeat_count) + " hits", TEXT_FORMAT_LHS);
  } else if (monst_defeat_count <= 5) {
    parent->log(g, UI_WARN_FMT_STR "- Could defeat you in " + std::to_string(monst_defeat_count) + " hits", TEXT_FORMAT_LHS);
  } else if (monst_defeat_count <= 10) {
    parent->log(g, "- Could defeat you in " + std::to_string(monst_defeat_count) + " hits", TEXT_FORMAT_LHS);
  } else {
    parent->log(g, "- Could defeat you eventually.", TEXT_FORMAT_LHS);
  }

  auto player_max_dmg = thing_damage_max(g, v, l, player);
  if (player_max_dmg != 0) {
    auto player_defeat_count = thing_health(g, v, l, me) / player_max_dmg;

    //
    // Oh dear. The monst is toast.
    //
    if (player_defeat_count == 0) {
      player_defeat_count = 1;
    }

    if (player_defeat_count == 1) {
      parent->log(g, "- You could beat it in " + std::to_string(player_defeat_count) + " hit.", TEXT_FORMAT_LHS);
      parent->log(g, "- More likely, " + std::to_string(player_defeat_count * 2) + " hits", TEXT_FORMAT_LHS);
    } else if (player_defeat_count <= 2) {
      parent->log(g, "- You could beat it in " + std::to_string(player_defeat_count) + " hits.", TEXT_FORMAT_LHS);
      parent->log(g, "- More likely, " + std::to_string(player_defeat_count * 2) + " hits.", TEXT_FORMAT_LHS);
    } else if (player_defeat_count <= 10) {
      parent->log(g, "- You could beat it in " + std::to_string(player_defeat_count) + " hits.", TEXT_FORMAT_LHS);
      parent->log(g, "- More likely, " + std::to_string(player_defeat_count * 2) + " hits.", TEXT_FORMAT_LHS);
    } else {
      parent->log(g, "- Will take many hits to beat.");
    }
  }

  return true;
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
      (void) parent->log(g, UI_INFO_FMT_STR "Carrying:", TEXT_FORMAT_LHS);
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

    (void) my_strlcpy(line_bar, line.c_str(), line.size() + 1);
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

  if (wid_thing_info_noise_bar(g, v, l, me, tp, parent, width)) {
    parent->log_empty_line(g);
  }

  if (wid_thing_info_buffs(g, v, l, me, parent)) {
    parent->log_empty_line(g);
  }

  if (wid_thing_info_wielded(g, v, l, me, parent, width)) {
    parent->log_empty_line(g);
  }

  if (thing_is_player(me)) {
    if (wid_tp_info_damage(g, v, l, tp, parent, width, true /* title allowed */)) {
      parent->log_empty_line(g);
    }

    if (wid_tp_info_special_attacks(g, v, l, tp, parent, width, true /* title allowed */)) {
      parent->log_empty_line(g);
    }

    if (wid_thing_info_immunity(g, v, l, me, parent, width)) {
      parent->log_empty_line(g);
    }

    if (wid_thing_info_resistance(g, v, l, me, parent, width)) {
      parent->log_empty_line(g);
    }

    if (wid_thing_info_abilities(g, me, parent)) {
      parent->log_empty_line(g);
    }
  } else if (! thing_is_dead(me)) {
    if (wid_tp_info_damage(g, v, l, tp, parent, width, true /* title allowed */)) {
      parent->log_empty_line(g);
    }

    if (wid_tp_info_special_attacks(g, v, l, tp, parent, width, true /* title allowed */)) {
      parent->log_empty_line(g);
    }

    if (wid_thing_info_immunity(g, v, l, me, parent, width)) {
      parent->log_empty_line(g);
    }

    if (wid_thing_info_resistance(g, v, l, me, parent, width)) {
      parent->log_empty_line(g);
    }

    if (wid_thing_info_abilities(g, me, parent)) {
      parent->log_empty_line(g);
    }

    if (wid_thing_info_danger(g, v, l, me, parent)) {
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
