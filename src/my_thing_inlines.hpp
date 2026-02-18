//
// Copyright goblinhack@gmail.com
//

#pragma once
#ifndef _MY_THING_INLINES_H_
#define MY_THING_INLINES_H_

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
static inline Thingp thing_find(Gamep g, Levelsp v, ThingId id)
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

  if (unlikely(! t || (t->id != id))) {
    t = thing_find_non_inline(g, v, id);
  }

  return t;
}

static inline Tpp thing_tp(Thingp t)
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

static inline int thing_is_falling(Thingp t)
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

static inline int thing_is_hit(Thingp t)
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

static inline int thing_is_hot(Thingp t)
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

static inline bool thing_is_jumping(Thingp t)
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

static inline bool thing_is_moving(Thingp t)
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

static inline bool thing_is_spawned(Thingp t)
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

static inline bool thing_is_dead(Thingp t)
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

static inline bool thing_is_physics_temperature(Thingp t)
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

static inline bool thing_is_player(const Thingp t)
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

static inline bool thing_is_obs_to_vision(Thingp t)
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

static inline spoint thing_pix_at(Thingp t)
{
#ifdef _DEBUG_BUILD_
  TRACE_NO_INDENT();
  if (! t) {
    CROAK("No thing pointer set");
  }
#endif
  return t->_curr_pix_at;
}

static inline bool thing_is_open(Thingp t)
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

static inline Thingp thing_find_optional(Gamep g, Levelsp v, ThingId id)
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

static inline int thing_is_light_source(Thingp t)
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
#endif // _MY_THING_INLINES_H_
