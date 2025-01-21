//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_dice.hpp"
#include "my_enums.hpp"
#include "my_main.hpp"
#include "my_ptrcheck.hpp"
#include "my_random.hpp"
#include "my_tile.hpp"
#include "my_tp.hpp"
#include "my_tps.hpp"

#include <inttypes.h>
#include <map>
#include <vector>

//
// Templates can be assigned dynamic IDs - however the levels are more reproducable it
// they have fixed numbers. This list helps to achieve that. It is optional for a template
// to be in this list
//
/* clang-format off */
std::initializer_list< std::string > tps = {
    // clang-format off
    "", // ID 0 means unused
    "wall1",
    "player1",
    "player2",
    "player3",
    "player4",
    /* begin shell marker1 */
    /* shell for i in $(find . -name "*.cpp" | xargs grep -h "tp_load(\"" | awk '{print $4}' | cut -d\" -f2) */
    /* shell do */
    /* shell echo "    \"$i\"", */
    /* shell done */
    "floor",
    "key",
    "exit",
    "door",
    "cursor_path",
    "cursor_at",
  /* end shell marker1 */
};
/* clang-format on */

class Tp
{
public:
  uint8_t z_depth {};

  TpId id {};

  std::vector< class Tile * > tiles;

  bool is_monst_class[ MONST_CLASS_MAX ] {};

  uint8_t flag[ THING_FLAG_MAX ] = {};

  // begin sort marker2 {
  int chance_d1000_appearing {};
  int rarity {};
  int speed {100};
  // end sort marker2 }

  uint8_t player_index {};

  Tp(void);
  ~Tp(void);

  void name_set(const std::string &v);
  void rarity_set(int v);
  void text_real_name_set(const std::string &v);
  void text_short_name_set(const std::string &v);
  void z_depth_set(int v);

  std::string name;
  std::string text_real_name;
  std::string text_short_name;
};

using Tpidmap = std::vector< class Tp * >;
Tpidmap tp_id_map;

// begin sort marker3 {
static Tpidmap tp_flag_map[ THING_FLAG_MAX ];
static Tpidmap tp_monst_class[ MONST_CLASS_MAX ];
// end sort marker3 }

static std::map< std::string, class Tp * > tp_name_map;

static uint8_t tp_init_done;

Tp::Tp(void) { newptr(MTYPE_TP, this, "Tp"); }

Tp::~Tp(void) { oldptr(MTYPE_TP, this); }

Tpp tp_find_mand(const char *name_in)
{
  TRACE_NO_INDENT();

  std::string name(name_in);
  auto        result = tp_name_map.find(name);

  if (unlikely(result != tp_name_map.end())) {
    return result->second;
  }

  DIE("tp_find_mand: thing template %s not found", name_in);
  return nullptr;
}

Tpp tp_find_opt(const char *name_in)
{
  TRACE_NO_INDENT();

  std::string name(name_in);
  auto        result = tp_name_map.find(name);

  if (unlikely(result != tp_name_map.end())) {
    return result->second;
  }

  return nullptr;
}

Tpp tp_find(TpId id)
{
  TRACE_NO_INDENT();

  if ((int) id - 1 >= (int) tp_id_map.size()) {
    DIE("tp_find: thing template %" PRIX16 " bad id", id);
  }

  auto result = tp_id_map[ id - 1 ];
  if (! result) {
    DIE("tp_find: thing template %" PRIX16 " not found", id);
  }

  return result;
}

TpId tp_id_get(Tpp tp)
{
  TRACE_NO_INDENT();
  return tp->id;
}

bool tp_init(void)
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
  if (! tp_init_done) {
    return;
  }
  tp_init_done = false;

  for (auto &tp : tp_name_map) {
    delete tp.second;
  }

  tp_id_map.clear();
  tp_name_map.clear();

  for (auto c = 0; c < MONST_CLASS_MAX; c++) {
    tp_monst_class[ c ].clear();
  }

  for (auto f = 0; f < THING_FLAG_MAX; f++) {
    tp_flag_map[ f ].clear();
  }
}

//
// Assign template IDs
//
static void tp_assign_id(const std::string &tp_name, int *id_out)
{
  static std::map< std::string, int > tp_preferred_id;

  static const std::vector< std::string > tp_arr(tps);

  static int  id;
  static bool init;

  //
  // Assign static IDs
  //
  if (! init) {
    init = true;
    for (auto t : tp_arr) {
      tp_preferred_id[ t ] = id++;
    }
  }

  //
  // Previously known
  //
  if (tp_preferred_id.find(tp_name) == tp_preferred_id.end()) {
    tp_preferred_id[ tp_name ] = *id_out = ++id;
    DIE("Thing template not found [%s] Please edit tp_ids.cpp and add it.", tp_name.c_str());
    return;
  }

  *id_out = tp_preferred_id[ tp_name ];
}

Tpp tp_load(const char *name_in)
{
  TRACE_NO_INDENT();

  std::string name(name_in);

  int id;
  tp_assign_id(name_in, &id);

  if (tp_find_opt(name_in)) {
    DIE("tp_load: thing template name [%s] already loaded", name_in);
  }

  auto tp             = new Tp();
  tp->name            = name;
  tp->text_short_name = name;

  auto result = tp_name_map.insert(std::make_pair(name, tp));
  if (! result.second) {
    DIE("Thing insert name [%s] failed", name_in);
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
  return tp->tiles[ 0 ];
}

void tp_random_dungeon_init(void)
{
  TRACE_NO_INDENT();

  for (auto &tp : tp_id_map) {

    //
    // Monsters
    //
    for (auto c = 0; c < MONST_CLASS_MAX; c++) {
      if (tp->is_monst_class[ c ]) {
        tp_monst_class[ c ].push_back(tp);
      }
    }

    for (auto f = 0; f < THING_FLAG_MAX; f++) {
      if (tp->flag[ f ]) {
        tp_flag_map[ f ].push_back(tp);
      }
    }
  }
}

static Tpp tp_get_with_no_rarity_filter(Tpidmap &m)
{
  TRACE_NO_INDENT();

  int tries = 1000;
  while (tries-- > 0) {
    auto index = pcg_rand() % m.size();
    auto tp    = m[ index ];
    if (! tp) {
      break;
    }

    //
    // If this thing has a limited chance of appearing, roll the dice.
    //
    auto chance = tp->chance_d1000_appearing;
    if (chance) {
      auto roll = d1000();
      if (roll < chance) {
        return tp;
      }
    } else {
      return tp;
    }
  }

  //
  // Give in and return the first we find.
  //
  auto index = pcg_rand() % m.size();
  auto tp    = m[ index ];
  return tp;
}

Tpp tp_random_monst(int c)
{
  TRACE_NO_INDENT();

  if (c >= MONST_CLASS_MAX) {
    DIE("monst bad class %d", c);
    return nullptr;
  }

  if (unlikely(! tp_monst_class[ c ].size())) {
    DIE("No monst class %d found", c);
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_monst_class[ c ]);
}

Tpp tp_random(ThingFlag f)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_flag_map[ f ].size())) {
    DIE("No wall found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_flag_map[ f ]);
}

Tilep tp_tiles_get(Tpp tp, int index) { return tp->tiles[ index ]; }
void  tp_tiles_push_back(Tpp tp, Tilep val) { tp->tiles.push_back(val); }
int   tp_tiles_size(Tpp tp) { return (int) tp->tiles.size(); }

const char *tp_name(Tpp tp) { return tp->name.c_str(); }
const char *to_string(Tpp tp) { return tp->text_short_name.c_str(); }
const char *to_short_string(Tpp tp) { return tp->text_short_name.c_str(); }

bool tp_flag(Tpp tp, ThingFlag f) { return tp->flag[ f ]; }

void tp_flag_set(Tpp tp, ThingFlag f, bool val) { tp->flag[ f ] = val; }

uint8_t tp_player_index_get(Tpp tp) { return tp->player_index; };
void    tp_player_index_set(Tpp tp, uint8_t val) { tp->player_index = val; };

void    tp_z_depth_set(Tpp tp, uint8_t val) { tp->z_depth = val; };
uint8_t tp_z_depth_get(Tpp tp) { return tp->z_depth; };

void tp_speed_set(Tpp tp, int val) { tp->speed = val; };
int  tp_speed_get(Tpp tp) { return tp->speed; };
