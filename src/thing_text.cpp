//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_game.hpp"
#include "my_sprintf.hpp"
#include "my_thing.hpp"

std::string thing_pluralize_name(Thingp t)
{
  TRACE_NO_INDENT();

  auto tp  = thing_tp(t);
  auto out = tp_pluralize_name(tp);

  if (out.empty()) {
    return tp_long_name(tp) + "s";
  }

  return out;
}

std::string thing_apostrophize_name(Thingp t)
{
  TRACE_NO_INDENT();

  auto tp  = thing_tp(t);
  auto out = tp_apostrophize_name(tp);

  if (out == "") {
    return tp_long_name(tp) + "'s";
  }

  return out;
}

std::string thing_long_name(Gamep g, Levelsp v, Levelp l, Thingp t, ThingTextFlags f)
{
  TRACE_NO_INDENT();

  if (unlikely(! t)) {
    return ("<no name>");
  }

  auto tp = thing_tp(t);

  std::string out;

#if 0
  //
  // Tamed?
  //
  auto l = leader();
  if (l && (l == level->player)) {
    out = "your ";
  }

#endif
  //
  // "the kobalos's short sword" for example
  //
  auto t_o = top_owner(g, v, l, t);
  if (f & TEXT_INCLUDE_OWNER) {
    if (t_o && ! thing_is_player(t_o)) {

      out += tp_long_name(thing_tp(t_o));
      out += "'s ";
    }
  }

  if (! (f & TEXT_EXCLUDE_DEATH)) {
    if (thing_is_burning(t)) {
      out += "burning ";
    }

    if (thing_is_dead(t)) {
      if (thing_is_player(t) || thing_is_monst(t)) {
        if (thing_is_undead(t)) {
          out += "extra dead ";
        } else {
          out += "dead ";
        }
      }
      if (thing_is_broken_on_death(t)) {
        out += "broken ";
      }
      if (thing_is_extinguished_on_death(t)) {
        out += "extinguished ";
      }
    }

#if 0
  if (is_frozen) {
    out += "frozen ";
  } else if (is_gaseous) {
    out += "burnt ";
  } else if (tp->charge_count() && ! charge_count()) {
    out += "spent ";
  }
#endif
  }

#if 0
  //
  // Tamed?
  //
  if (l && (l == level->player)) {
    if (is_not_shown_as_a_pet()) {
      //
      // Not really a pet
      //
    } else {
      out += "pet ";
    }
  }
#endif

  if (f & TEXT_APOSTROPHIZE) {
    out += thing_apostrophize_name(t);
  } else if (f & TEXT_APOSTROPHIZE) {
    out += thing_pluralize_name(t);
  } else {
    auto name = tp_long_name(tp);
    if (g && thing_is_player(t)) {
      name = game_player_name_get(g);
    }

    out += name;
  }

#if 0
  if (tp->is_spell()) {
    out += " spell";
  }

  if (tp->is_skill()) {
    out += " skill";
  }
#endif

  return out;
}

std::string thing_the_long_name(Gamep g, Levelsp v, Levelp l, Thingp t, ThingTextFlags f)
{
  TRACE_NO_INDENT();

  return "the " + thing_long_name(g, v, l, t, f);
}
