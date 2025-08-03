//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_level.hpp"

#include <set>

void level_tick_end_temperature(Gamep g, Levelsp v, Levelp l)
{
  TRACE_NO_INDENT();

  int x, y;

  FOR_ALL_MAP_POINTS(g, v, l, x, y)
  {
    std::vector< Thingp > things;

    //
    // Collect all things at this point into a vector
    //
    spoint p(x, y);
    FOR_ALL_THINGS_AT(g, v, l, t, p)
    {
      //
      // Ignore burnt grass for example
      //
      if (thing_is_dead(t)) {
        continue;
      }

      if (thing_is_physics_temperature(t)) {
        things.push_back(t);
      }
    }

    //
    // Make unique pairs
    //
    std::set< std::pair< Thingp, Thingp > > pairs;

    auto sz = (int) things.size();
    for (auto i = 0; i < sz; i++) {
      for (auto j = 0; j < sz; j++) {
        auto Ti = things[ i ];
        auto Tj = things[ j ];
        if (Ti == Tj) {
          continue;
        }

        if ((void *) Ti > (void *) Tj) {
          std::swap(Ti, Tj);
        }

        pairs.insert(std::make_pair(Ti, Tj));
      }
    }

    for (auto pair : pairs) {
      auto a = pair.first;
      auto b = pair.second;

      //
      // If could be dead now.
      //
      if (thing_is_dead(a) || thing_is_dead(b)) {
        continue;
      }

      float Ta = thing_temperature(a);
      float Wa = thing_weight(a);
      float Tb = thing_temperature(b);
      float Wb = thing_weight(b);

      //
      // Fire has no weight, so give it some so the equations below average the temperatures.
      //
      if (thing_is_gaseous(a)) {
        if (! (int) Wa) {
          Wa = Wb;
        }
      }

      if (thing_is_gaseous(b)) {
        if (! (int) Wb) {
          Wb = Wa;
        }
      }

      if (! (int) Wa || ! (int) Wb) {
        continue;
      }

      //
      // The new temperatures
      //
      int Na = (int) std::round(Ta + ((Tb - Ta) / (Wa + Wb)) * Wb);
      int Nb = (int) std::round(Tb + ((Ta - Tb) / (Wa + Wb)) * Wa);

      if (0) {
        THING_CON(a, "Ta %f Wa %f Na %d", Ta, Wa, Na);
        THING_CON(b, "Tb %f Wb %f Nb %d", Tb, Wb, Nb);
      }

      //
      // First step is to mark things as burning and change temperatures
      //
      if (Ta != Na) {
        if (thing_is_loggable(a)) {
          THING_DBG(a, "temperature change (a) %f -> %d degrees", Ta, Na);
        }
        thing_temperature_handle(g, v, l, b, a, Na);
      }

      if (Tb != Nb) {
        if (thing_is_loggable(b)) {
          THING_DBG(b, "temperature change (b) %f -> %d degrees", Tb, Nb);
        }
        thing_temperature_handle(g, v, l, a, b, Nb);
      }

      //
      // Next step is to apply burning damage
      //
      if (Ta != Na) {
        thing_temperature_damage_handle(g, v, l, b, a, Na);
      }

      if (Tb != Nb) {
        thing_temperature_damage_handle(g, v, l, a, b, Nb);
      }
    }
  }
}

//
// Allow things to return to the initial temperature
//
void level_tick_begin_temperature(Gamep g, Levelsp v, Levelp l)
{
  TRACE_NO_INDENT();

  int x, y;

  FOR_ALL_MAP_POINTS(g, v, l, x, y)
  {
    std::vector< Thingp > things;

    //
    // Collect all things at this point into a vector
    //
    spoint p(x, y);
    FOR_ALL_THINGS_AT(g, v, l, t, p)
    {
      //
      // Ignore burnt grass for example
      //
      if (thing_is_dead(t)) {
        continue;
      }

      if (thing_is_physics_temperature(t)) {
        things.push_back(t);
      }
    }

    for (auto i = 0; i < (int) things.size(); i++) {
      auto t = things[ i ];

      //
      // If could be dead now.
      //
      if (thing_is_dead(t)) {
        continue;
      }

      float Ta = thing_temperature(t);
      float To = tp_temperature_initial_get(thing_tp(t));
      int   Tn = (int) ((Ta + To) / 2.0);

      //
      // No need to handle return to temperature
      //
      if (Tn != Ta) {
        if (thing_is_loggable(t)) {
          THING_DBG(t, "temperature return %f -> %d degrees", Ta, Tn);
        }
        thing_temperature_set(g, v, l, t, Tn);
      }
    }
  }
}
