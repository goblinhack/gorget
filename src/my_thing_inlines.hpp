//
// Copyright goblinhack@gmail.com
//

#ifndef MY_THING_INLINES_H
#define MY_THING_INLINES_H

#ifdef _DEBUG_BUILD_
#include "my_callstack.hpp"
#include "my_globals.hpp"
#include "my_main.hpp"
#endif

#include "my_level.hpp"
#include "my_thing.hpp"

//
// this belongs in my_thing.hpp but as it is inlined, it needs to access
// the levels structure
//
static inline auto thing_find(Gamep g, Levelsp v, ThingId id) -> Thingp
{
#ifdef _DEBUG_BUILD_
  TRACE_NO_INDENT(); // expensive
                     //
  if (! g) {
    ERR("No game pointer set");
    return nullptr;
  }
  //
  if (! v) {
    ERR("No levels pointer set");
    return nullptr;
  }
#endif

  ThingIdPacked id_packed = {};
  id_packed.a.val         = id;
  auto arr_index          = id_packed.c.arr_index;

  auto *t = &v->thing_body[ arr_index ];

#ifdef ENABLE_PER_THING_MEMORY
  if (v->thing_body_debug[ arr_index ]) {
    t = v->thing_body_debug[ arr_index ];
  }
#endif

  if (UNLIKELY(! t || (t->id != id))) {
    t = thing_find_non_inline(g, v, id);
  }

  return t;
}

static inline auto thing_tp(Thingp t) -> Tpp
{
#ifdef _DEBUG_BUILD_
  TRACE_NO_INDENT(); // expensive
                     //
  if (! t) {
    ERR("No thing pointer set");
    return nullptr;
  }
#endif

  return tp_find(t->tp_id);
}

static inline auto thing_is_falling(Thingp t) -> int
{
#ifdef _DEBUG_BUILD_
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return 0;
  }
#endif
  return t->_is_falling_ms;
}

static inline auto thing_is_hit(Thingp t) -> int
{
#ifdef _DEBUG_BUILD_
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return 0;
  }
#endif
  return t->_is_hit;
}

static inline auto thing_is_hot(Thingp t) -> int
{
#ifdef _DEBUG_BUILD_
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return 0;
  }
#endif
  return t->_is_hot;
}

static inline auto thing_is_jumping(Thingp t) -> bool
{
#ifdef _DEBUG_BUILD_
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
#endif
  return t->_is_jumping;
}

static inline auto thing_is_moving(Thingp t) -> bool
{
#ifdef _DEBUG_BUILD_
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
#endif
  return t->_is_moving;
}

static inline auto thing_is_spawned(Thingp t) -> bool
{
#ifdef _DEBUG_BUILD_
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
#endif
  return t->_is_spawned;
}

static inline auto thing_is_dead(Thingp t) -> bool
{
#ifdef _DEBUG_BUILD_
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
#endif
  return t->_is_dead;
}

static inline auto thing_is_physics_temperature(Thingp t) -> bool
{
#ifdef _DEBUG_BUILD_
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
#endif
  return tp_flag(thing_tp(t), is_physics_temperature) != 0;
}

static inline auto thing_is_player(const Thingp t) -> bool
{
#ifdef _DEBUG_BUILD_
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
#endif
  return t->_is_player;
}

static inline auto thing_is_obs_to_vision(Thingp t) -> bool
{
#ifdef _DEBUG_BUILD_
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
#endif
  return tp_flag(thing_tp(t), is_obs_to_vision) != 0;
}

static inline auto thing_pix_at(Thingp t) -> spoint
{
#ifdef _DEBUG_BUILD_
  TRACE_NO_INDENT();
  if (! t) {
    CROAK("No thing pointer set");
  }
#endif
  return t->_curr_pix_at;
}

static inline auto thing_is_open(Thingp t) -> bool
{
#ifdef _DEBUG_BUILD_
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
#endif
  return t->_is_open;
}

static inline auto thing_find_optional(Gamep g, Levelsp v, ThingId id) -> Thingp
{
#ifdef _DEBUG_BUILD_
  TRACE_NO_INDENT(); // expensive
#endif

  if (! static_cast< bool >(id)) {
    return nullptr;
  }

  ThingIdPacked id_packed;
  id_packed.a.val = id;
  auto arr_index  = id_packed.c.arr_index;

  auto *t = &v->thing_body[ arr_index ];
#ifdef ENABLE_PER_THING_MEMORY
  if (v->thing_body_debug[ arr_index ]) {
    t = v->thing_body_debug[ arr_index ];
  }
#endif

  if (t == nullptr) {
    return nullptr;
  }

  if (t->id == id) {
    return t;
  }

  return nullptr;
}

static inline auto thing_is_light_source(Thingp t) -> int
{
#ifdef _DEBUG_BUILD_
  TRACE_NO_INDENT();
  if (! t) {
    ERR("No thing pointer set");
    return false;
  }
#endif
  return tp_flag(thing_tp(t), is_light_source);
}
#endif // MY_THING_INLINES_H
