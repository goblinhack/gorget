//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include <inttypes.h>

#include "my_ptrcheck.hpp"
#include "my_string.hpp"
#include "my_tp.hpp"
#include "my_tps.hpp"
#include "my_vector_bounds_check.hpp"

Tpnamemap tp_name_map;
Tpidmap   tp_id_map;

static uint8_t tp_init_done;

Tp::Tp(void) { newptr(MTYPE_TP, this, "Tp"); }

Tp::~Tp(void) { oldptr(MTYPE_TP, this); }

Tpp tp_find(const std::string &name)
{
  TRACE_NO_INDENT();

  auto result = tp_name_map.find(name);

  if (unlikely(result != tp_name_map.end())) {
    return (result->second);
  }

  return nullptr;
}

Tpp tp_find(TpId id)
{
  TRACE_NO_INDENT();

  if ((int) id - 1 >= (int) tp_id_map.size()) {
    DIE("tp_find: thing template %" PRIX16 " bad id", id);
  }

  auto result = get(tp_id_map, id - 1);
  if (! result) {
    DIE("tp_find: thing template %" PRIX16 " not found", id);
  }

  return result;
}

uint8_t tp_init(void)
{
  TRACE_NO_INDENT();
  tp_init_done = true;

  templates_init();
  tp_random_dungeon_init();
  tp_fixup();

  return true;
}

void tp_fini(void)
{
  TRACE_NO_INDENT();
  if (tp_init_done) {
    tp_init_done = false;
  }
  for (auto &tp : tp_name_map) {
    delete tp.second;
  }
}

Tpp tp_load(std::string const &name)
{
  TRACE_NO_INDENT();

  int id;
  tp_get_id(name, &id);

  if (tp_find(name)) {
    DIE("tp_load: thing template name [%s] already loaded", name.c_str());
  }

  auto tp = new Tp();
  tp->name_set(name);
  tp->text_short_name_set(name);

  auto result = tp_name_map.insert(std::make_pair(name, tp));
  if (! result.second) {
    DIE("Thing insert name [%s] failed", name.c_str());
  }

  tp_id_map.push_back(tp);
  tp->id = tp_id_map.size();

  return tp;
}

Tilep tp_first_tile(Tpp tp)
{
  TRACE_NO_INDENT();
  if (! tp) {
    return nullptr;
  }

  auto tiles = &tp->tiles;

  if (! tiles || tiles->empty()) {
    ERR("Tp %s has no tiles", tp->name.c_str());
  }

  //
  // Get the first anim tile.
  //
  return tile_first(tiles);
}
