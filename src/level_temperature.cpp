//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_level.hpp"
#include "my_thing_inlines.hpp"

#include "math.h"

#include <set>
#include <vector>

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

    std::vector< std::pair< Thingp, Thingp > > sorted_pairs;
    for (auto a_pair : pairs) {
      sorted_pairs.push_back(a_pair);
    }

    if (0)
      for (auto a_pair : sorted_pairs) {
        auto a = a_pair.first;
        auto b = a_pair.second;

        THING_CON(a, "A before %d", a->_priority + b->_priority);
        THING_CON(b, "B before");
      }

    //
    // Sort my event priority
    //
    std::sort(sorted_pairs.begin(), sorted_pairs.end(),
              [](const std::pair< Thingp, Thingp > &a, const std::pair< Thingp, Thingp > &b) {
                auto t1 = a.first;
                auto t2 = a.second;
                auto t3 = b.first;
                auto t4 = b.second;
                return t1->_priority + t2->_priority < t3->_priority + t4->_priority;
              });

    if (0)
      for (auto a_pair : sorted_pairs) {
        auto a = a_pair.first;
        auto b = a_pair.second;

        THING_CON(a, "A after %d", a->_priority + b->_priority);
        THING_CON(b, "B after");
      }

    for (auto a_pair : sorted_pairs) {
      auto a = a_pair.first;
      auto b = a_pair.second;

      //
      // It could be dead now.
      //
      if (thing_is_dead(a) || thing_is_dead(b)) {
        continue;
      }

      float Ta = thing_temperature(a);
      float Wa = thing_weight(a);
      float Tb = thing_temperature(b);
      float Wb = thing_weight(b);

      if (0) {
        THING_CON(a, "A Ta %f Wa %f", Ta, Wa);
        THING_CON(b, "B Tb %f Wb %f", Tb, Wb);
      }

      //
      // Fire has no weight, so give it some so the equations below average the temperatures.
      //
      // Take care not to give too much weight or you end up with steam able to heat up a
      // tile of water, which seems wrong.
      //
      if (thing_is_gaseous(a)) {
        if (! (int) Wa) {
          Wa = WEIGHT_HUMAN;
        }
      }

      if (thing_is_gaseous(b)) {
        if (! (int) Wb) {
          Wb = WEIGHT_HUMAN;
        }
      }

      if (! (int) Wa || ! (int) Wb) {
        continue;
      }

      //
      // The new temperatures
      //
      int Na = (int) round(Ta + ((Tb - Ta) / (Wa + Wb)) * Wb);
      int Nb = (int) round(Tb + ((Ta - Tb) / (Wa + Wb)) * Wa);

      if (0) {
        THING_CON(a, "Ta %f Wa %f Na %d", Ta, Wa, Na);
        THING_CON(b, "Tb %f Wb %f Nb %d", Tb, Wb, Nb);
      }

      //
      // First step is to mark things as burning and change temperatures
      //
      if (Ta != Na) {
        THING_DBG(a, "temperature change (a) %f -> %d degrees", Ta, Na);
        thing_temperature_handle(g, v, l, b, a, Na);
      }

      if (Tb != Nb) {
        THING_DBG(b, "temperature change (b) %f -> %d degrees", Tb, Nb);
        thing_temperature_handle(g, v, l, a, b, Nb);
      }

      //
      // Next step is to apply burning damage if the temperature increases
      //
      // If it decreases (e.g. cooling in water) then no damage.
      //
      if (Na > Ta) {
        thing_temperature_damage_handle(g, v, l, b /* source */, a, Na);
      }

      if (Nb > Tb) {
        thing_temperature_damage_handle(g, v, l, a /* source */, b, Nb);
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
      if (! thing_is_physics_temperature(t)) {
        continue;
      }

      //
      // Ignore burnt grass for example
      //
      if (thing_is_dead(t)) {
        continue;
      }

      things.push_back(t);
    }

    for (auto i = 0; i < (int) things.size(); i++) {
      auto t = things[ i ];

      //
      // It could be dead now.
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
        THING_DBG(t, "temperature return %f -> %d degrees", Ta, Tn);
        thing_temperature_set(g, v, l, t, Tn);
      }
    }
  }
}
