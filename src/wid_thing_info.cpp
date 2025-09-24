//
// Copyright goblinhack@gmail.com
//

#include "my_ascii.hpp"
#include "my_callstack.hpp"
#include "my_color_defs.hpp"
#include "my_game.hpp"
#include "my_level.hpp"
#include "my_ptrcheck.hpp"
#include "my_sprintf.hpp"
#include "my_string.hpp"
#include "my_thing.hpp"
#include "my_tp_callbacks.hpp"
#include "my_wids.hpp"

//
// The thing icon
//
static bool wid_thing_info_icon(Gamep g, Levelsp v, Levelp l, Thingp t, Tpp tp, WidPopup *parent, int width)
{
  TRACE_NO_INDENT();

  auto  text = parent->wid_text_area;
  auto  b    = parent->wid_text_area->wid_text_area;
  Tilep tile = tp_tiles_get(tp, THING_ANIM_IDLE, 0);
  if (! tile) {
    return false;
  }

  auto   w = wid_new_square_button(g, b, "Icon");
  spoint tl(0, text->line_count);
  spoint br(3, text->line_count + 2);
  wid_set_tile(TILE_LAYER_BG_0, w, tile);
  wid_set_style(w, UI_WID_STYLE_SPARSE_NONE);
  wid_set_pos(w, tl, br);

  return true;
}

//
// The thing name
//
static bool wid_thing_info_name(Gamep g, Levelsp v, Levelp l, Thingp t, Tpp tp, WidPopup *parent, int width)
{
  TRACE_NO_INDENT();

  std::string name_str;
  if (thing_is_player(t)) {
    name_str = game_player_name_get(g);
  } else {
    name_str = tp_long_name(tp);
  }
  name_str = capitalize(name_str);

  parent->log(g, UI_INFO_FMT_STR + name_str + UI_RESET_FMT);

  return true;
}

//
// The thing description
//
static bool wid_thing_info_detail(Gamep g, Levelsp v, Levelp l, Thingp t, Tpp tp, WidPopup *parent, int width)
{
  TRACE_NO_INDENT();

  parent->log(g, tp_detail_get(g, v, l, t), TEXT_FORMAT_LHS);

  return true;
}

//
// Health bar
//
static bool wid_thing_info_health_bar(Gamep g, Levelsp v, Levelp l, Thingp t, Tpp tp, WidPopup *parent, int width)
{
  TRACE_NO_INDENT();

  if (! tp_is_health_bar_shown(tp)) {
    return false;
  }

  char tmp[ width * 2 ];

  //
  // "Health            "
  //
  memset(tmp, 0, sizeof(tmp));
  memset(tmp, ' ', sizeof(tmp) - 1);
  strncpy(tmp + 1, "Health", sizeof("Health") - 1);

  //
  // "Health         a/b"
  //
  auto        health_max = tp_health_max_get(tp);
  std::string health_str = std::to_string(thing_health(t)) + "/" + std::to_string(health_max);
  strncpy(tmp + width - health_str.size() - 3, health_str.c_str(), width - health_str.size());
  tmp[ strlen(tmp) ] = ' ';

  //
  // "Health         a/b"
  // "xxxxxxxxxxxxxxxxxx"
  //
  auto w = parent->log(g, std::string(tmp));
  if (w) {
    int health_how_much = (int) (((float) thing_health(t) / (float) health_max) * ((float) UI_HEALTH_BAR_STEPS - 1));
    health_how_much     = std::min(health_how_much, UI_HEALTH_BAR_STEPS - 1);
    health_how_much     = std::max(health_how_much, 0);
    auto icon           = "health_bar." + std::to_string(health_how_much + 1);

    wid_set_shape_square(w);
    wid_set_style(w, UI_WID_STYLE_SPARSE_NONE);
    wid_set_color(w, WID_COLOR_TEXT_FG, UI_HIGHLIGHT_COLOR);
    wid_set_tilename(TILE_LAYER_BG_0, w, icon);
    wid_set_text_lhs(w, true);
  }

  return true;
}

//
// Add immunities
//
static bool wid_thing_info_immunities(Gamep g, Levelsp v, Levelp l, Thingp t, Tpp tp, WidPopup *parent, int width)
{
  TRACE_NO_INDENT();

  bool printed_something = false;

  FOR_ALL_THING_EVENT(e)
  {
    if (! thing_is_immune_to(t, e)) {
      continue;
    }

    bool skip = true;

    switch (e) {
      case THING_EVENT_SHOVED : //
        skip = true;
        break;
      case THING_EVENT_CRUSH : //
        skip = true;
        break;
      case THING_EVENT_MELEE_DAMAGE : //
        break;
      case THING_EVENT_HEAT_DAMAGE : //
        break;
      case THING_EVENT_EXPLOSION_DAMAGE : //
        break;
      case THING_EVENT_FIRE_DAMAGE : //
        break;
      case THING_EVENT_WATER_DAMAGE : //
        skip = true;
        break;
      case THING_EVENT_NONE : //
        skip = true;
        break;
      case THING_EVENT_OPEN : //
        skip = true;
        break;
      case THING_EVENT_LIFESPAN_EXPIRED : //
        skip = true;
        break;
      case THING_EVENT_FALL : //
        skip = true;
        break;
      case THING_EVENT_CARRIED : //
        skip = true;
        break;
      case THING_EVENT_CARRIED_MERGED : //
        skip = true;
        break;
      case THING_EVENT_ENUM_MAX : //
        skip = true;
        break;
    }

    if (skip) {
      continue;
    }

    auto immune_str = string_sprintf("Immune to: %*s", width - 13, capitalize(ThingEventType_to_string(e)).c_str());
    parent->log(g, immune_str, TEXT_FORMAT_LHS);
    printed_something = true;
  }

  return printed_something;
}

//
// Add special damage
//
static bool wid_thing_info_special_damage(Gamep g, Levelsp v, Levelp l, Thingp t, Tpp tp, WidPopup *parent, int width)
{
  TRACE_NO_INDENT();

  bool printed_something = false;

  if (! thing_is_immune_to(t, THING_EVENT_WATER_DAMAGE)) {
    parent->log(g, "Takes damage from water.", TEXT_FORMAT_LHS);
    printed_something = true;
  }

  return printed_something;
}

//
// Display detailed thing information
//
void wid_thing_info(Gamep g, Levelsp v, Levelp l, Thingp t, WidPopup *parent, int width)
{
  ////////////////////////////////////////////////////////////////////////////////
  // Careful here. If we invoked the random number generator in here it can throw
  // off tests.
  ////////////////////////////////////////////////////////////////////////////////

  TRACE_NO_INDENT();

  if (! t) {
    return;
  }

  auto tp = thing_tp(t);
  if (! tp) {
    return;
  }

  if (wid_thing_info_icon(g, v, l, t, tp, parent, width)) {
    parent->log_empty_line(g);
  }

  if (wid_thing_info_name(g, v, l, t, tp, parent, width)) {
    parent->log_empty_line(g);
  }

  if (wid_thing_info_detail(g, v, l, t, tp, parent, width)) {
    parent->log_empty_line(g);
  }

  if (wid_thing_info_health_bar(g, v, l, t, tp, parent, width)) {
    parent->log_empty_line(g);
  }

  wid_thing_info_immunities(g, v, l, t, tp, parent, width);
  wid_thing_info_special_damage(g, v, l, t, tp, parent, width);
}
