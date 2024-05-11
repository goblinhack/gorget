//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_dice.hpp"
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
    "cursor_path",
    "cursor_at",
    "key",
    "exit",
    "door",
    "floor",
  /* end shell marker1 */
};

class Tp
{
public:
  uint8_t z_depth {};

  TpId    id {};

  std::vector<class Tile *> tiles;

  // begin sort marker1 {
  bool is_animated_can_hflip {};
  bool is_animated_no_dir {};
  bool is_blit_centered {};
  bool is_blit_on_ground {};
  bool is_blit_outlined {};
  bool is_blit_square_outlined {};
  bool is_blit_tiled {};
  bool is_cursor {};
  bool is_cursor_at {};
  bool is_cursor_path {};
  bool is_door {};
  bool is_dungeon_entrance {};
  bool is_exit {};
  bool is_floor {};
  bool is_key {};
  bool is_monst {};
  bool is_monst_class[ MONST_CLASS_MAX ] {};
  bool is_obs_monst {};
  bool is_obs_player {};
  bool is_player {};
  bool is_unused1 {};
  bool is_unused10 {};
  bool is_unused100 {};
  bool is_unused101 {};
  bool is_unused102 {};
  bool is_unused103 {};
  bool is_unused104 {};
  bool is_unused105 {};
  bool is_unused106 {};
  bool is_unused107 {};
  bool is_unused108 {};
  bool is_unused109 {};
  bool is_unused11 {};
  bool is_unused110 {};
  bool is_unused111 {};
  bool is_unused112 {};
  bool is_unused113 {};
  bool is_unused114 {};
  bool is_unused115 {};
  bool is_unused116 {};
  bool is_unused117 {};
  bool is_unused118 {};
  bool is_unused119 {};
  bool is_unused12 {};
  bool is_unused120 {};
  bool is_unused121 {};
  bool is_unused122 {};
  bool is_unused123 {};
  bool is_unused124 {};
  bool is_unused125 {};
  bool is_unused126 {};
  bool is_unused127 {};
  bool is_unused128 {};
  bool is_unused129 {};
  bool is_unused13 {};
  bool is_unused130 {};
  bool is_unused131 {};
  bool is_unused132 {};
  bool is_unused133 {};
  bool is_unused134 {};
  bool is_unused135 {};
  bool is_unused136 {};
  bool is_unused137 {};
  bool is_unused138 {};
  bool is_unused139 {};
  bool is_unused14 {};
  bool is_unused140 {};
  bool is_unused141 {};
  bool is_unused142 {};
  bool is_unused143 {};
  bool is_unused144 {};
  bool is_unused145 {};
  bool is_unused146 {};
  bool is_unused147 {};
  bool is_unused148 {};
  bool is_unused149 {};
  bool is_unused15 {};
  bool is_unused150 {};
  bool is_unused151 {};
  bool is_unused152 {};
  bool is_unused153 {};
  bool is_unused154 {};
  bool is_unused155 {};
  bool is_unused156 {};
  bool is_unused157 {};
  bool is_unused158 {};
  bool is_unused159 {};
  bool is_unused16 {};
  bool is_unused160 {};
  bool is_unused161 {};
  bool is_unused162 {};
  bool is_unused163 {};
  bool is_unused164 {};
  bool is_unused165 {};
  bool is_unused166 {};
  bool is_unused167 {};
  bool is_unused168 {};
  bool is_unused169 {};
  bool is_unused17 {};
  bool is_unused170 {};
  bool is_unused171 {};
  bool is_unused172 {};
  bool is_unused173 {};
  bool is_unused174 {};
  bool is_unused175 {};
  bool is_unused176 {};
  bool is_unused177 {};
  bool is_unused178 {};
  bool is_unused179 {};
  bool is_unused18 {};
  bool is_unused180 {};
  bool is_unused181 {};
  bool is_unused182 {};
  bool is_unused183 {};
  bool is_unused184 {};
  bool is_unused185 {};
  bool is_unused186 {};
  bool is_unused187 {};
  bool is_unused188 {};
  bool is_unused189 {};
  bool is_unused19 {};
  bool is_unused190 {};
  bool is_unused191 {};
  bool is_unused192 {};
  bool is_unused193 {};
  bool is_unused194 {};
  bool is_unused195 {};
  bool is_unused196 {};
  bool is_unused197 {};
  bool is_unused198 {};
  bool is_unused2 {};
  bool is_unused20 {};
  bool is_unused21 {};
  bool is_unused22 {};
  bool is_unused23 {};
  bool is_unused24 {};
  bool is_unused25 {};
  bool is_unused26 {};
  bool is_unused27 {};
  bool is_unused28 {};
  bool is_unused29 {};
  bool is_unused3 {};
  bool is_unused30 {};
  bool is_unused31 {};
  bool is_unused32 {};
  bool is_unused33 {};
  bool is_unused34 {};
  bool is_unused35 {};
  bool is_unused36 {};
  bool is_unused37 {};
  bool is_unused38 {};
  bool is_unused39 {};
  bool is_unused4 {};
  bool is_unused40 {};
  bool is_unused41 {};
  bool is_unused42 {};
  bool is_unused43 {};
  bool is_unused44 {};
  bool is_unused45 {};
  bool is_unused46 {};
  bool is_unused47 {};
  bool is_unused48 {};
  bool is_unused49 {};
  bool is_unused5 {};
  bool is_unused50 {};
  bool is_unused51 {};
  bool is_unused52 {};
  bool is_unused53 {};
  bool is_unused54 {};
  bool is_unused55 {};
  bool is_unused56 {};
  bool is_unused57 {};
  bool is_unused58 {};
  bool is_unused59 {};
  bool is_unused6 {};
  bool is_unused60 {};
  bool is_unused61 {};
  bool is_unused62 {};
  bool is_unused63 {};
  bool is_unused64 {};
  bool is_unused65 {};
  bool is_unused66 {};
  bool is_unused67 {};
  bool is_unused68 {};
  bool is_unused69 {};
  bool is_unused7 {};
  bool is_unused70 {};
  bool is_unused71 {};
  bool is_unused72 {};
  bool is_unused73 {};
  bool is_unused74 {};
  bool is_unused75 {};
  bool is_unused76 {};
  bool is_unused77 {};
  bool is_unused78 {};
  bool is_unused79 {};
  bool is_unused8 {};
  bool is_unused80 {};
  bool is_unused81 {};
  bool is_unused82 {};
  bool is_unused83 {};
  bool is_unused84 {};
  bool is_unused85 {};
  bool is_unused86 {};
  bool is_unused87 {};
  bool is_unused88 {};
  bool is_unused89 {};
  bool is_unused9 {};
  bool is_unused90 {};
  bool is_unused91 {};
  bool is_unused92 {};
  bool is_unused93 {};
  bool is_unused94 {};
  bool is_unused95 {};
  bool is_unused96 {};
  bool is_unused97 {};
  bool is_unused98 {};
  bool is_unused99 {};
  bool is_wall {};
  // end sort marker1 }

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
static Tpidmap tp_door;
static Tpidmap tp_dungeon_entrance;
static Tpidmap tp_exit;
static Tpidmap tp_floor;
static Tpidmap tp_is_cursor_at;
static Tpidmap tp_is_cursor_path;
static Tpidmap tp_key;
static Tpidmap tp_monst_class[ MONST_CLASS_MAX ];
static Tpidmap tp_player;
static Tpidmap tp_unused1;
static Tpidmap tp_unused10;
static Tpidmap tp_unused100;
static Tpidmap tp_unused101;
static Tpidmap tp_unused102;
static Tpidmap tp_unused103;
static Tpidmap tp_unused104;
static Tpidmap tp_unused105;
static Tpidmap tp_unused106;
static Tpidmap tp_unused107;
static Tpidmap tp_unused108;
static Tpidmap tp_unused109;
static Tpidmap tp_unused11;
static Tpidmap tp_unused110;
static Tpidmap tp_unused111;
static Tpidmap tp_unused112;
static Tpidmap tp_unused113;
static Tpidmap tp_unused114;
static Tpidmap tp_unused115;
static Tpidmap tp_unused116;
static Tpidmap tp_unused117;
static Tpidmap tp_unused118;
static Tpidmap tp_unused119;
static Tpidmap tp_unused12;
static Tpidmap tp_unused120;
static Tpidmap tp_unused121;
static Tpidmap tp_unused122;
static Tpidmap tp_unused123;
static Tpidmap tp_unused124;
static Tpidmap tp_unused125;
static Tpidmap tp_unused126;
static Tpidmap tp_unused127;
static Tpidmap tp_unused128;
static Tpidmap tp_unused129;
static Tpidmap tp_unused13;
static Tpidmap tp_unused130;
static Tpidmap tp_unused131;
static Tpidmap tp_unused132;
static Tpidmap tp_unused133;
static Tpidmap tp_unused134;
static Tpidmap tp_unused135;
static Tpidmap tp_unused136;
static Tpidmap tp_unused137;
static Tpidmap tp_unused138;
static Tpidmap tp_unused139;
static Tpidmap tp_unused14;
static Tpidmap tp_unused140;
static Tpidmap tp_unused141;
static Tpidmap tp_unused142;
static Tpidmap tp_unused143;
static Tpidmap tp_unused144;
static Tpidmap tp_unused145;
static Tpidmap tp_unused146;
static Tpidmap tp_unused147;
static Tpidmap tp_unused148;
static Tpidmap tp_unused149;
static Tpidmap tp_unused15;
static Tpidmap tp_unused150;
static Tpidmap tp_unused151;
static Tpidmap tp_unused152;
static Tpidmap tp_unused153;
static Tpidmap tp_unused154;
static Tpidmap tp_unused155;
static Tpidmap tp_unused156;
static Tpidmap tp_unused157;
static Tpidmap tp_unused158;
static Tpidmap tp_unused159;
static Tpidmap tp_unused16;
static Tpidmap tp_unused160;
static Tpidmap tp_unused161;
static Tpidmap tp_unused162;
static Tpidmap tp_unused163;
static Tpidmap tp_unused164;
static Tpidmap tp_unused165;
static Tpidmap tp_unused166;
static Tpidmap tp_unused167;
static Tpidmap tp_unused168;
static Tpidmap tp_unused169;
static Tpidmap tp_unused17;
static Tpidmap tp_unused170;
static Tpidmap tp_unused171;
static Tpidmap tp_unused172;
static Tpidmap tp_unused173;
static Tpidmap tp_unused174;
static Tpidmap tp_unused175;
static Tpidmap tp_unused176;
static Tpidmap tp_unused177;
static Tpidmap tp_unused178;
static Tpidmap tp_unused179;
static Tpidmap tp_unused18;
static Tpidmap tp_unused180;
static Tpidmap tp_unused181;
static Tpidmap tp_unused182;
static Tpidmap tp_unused183;
static Tpidmap tp_unused184;
static Tpidmap tp_unused185;
static Tpidmap tp_unused186;
static Tpidmap tp_unused187;
static Tpidmap tp_unused188;
static Tpidmap tp_unused189;
static Tpidmap tp_unused19;
static Tpidmap tp_unused190;
static Tpidmap tp_unused191;
static Tpidmap tp_unused192;
static Tpidmap tp_unused193;
static Tpidmap tp_unused194;
static Tpidmap tp_unused195;
static Tpidmap tp_unused196;
static Tpidmap tp_unused197;
static Tpidmap tp_unused198;
static Tpidmap tp_unused2;
static Tpidmap tp_unused20;
static Tpidmap tp_unused21;
static Tpidmap tp_unused22;
static Tpidmap tp_unused23;
static Tpidmap tp_unused24;
static Tpidmap tp_unused25;
static Tpidmap tp_unused26;
static Tpidmap tp_unused27;
static Tpidmap tp_unused28;
static Tpidmap tp_unused29;
static Tpidmap tp_unused3;
static Tpidmap tp_unused30;
static Tpidmap tp_unused31;
static Tpidmap tp_unused32;
static Tpidmap tp_unused33;
static Tpidmap tp_unused34;
static Tpidmap tp_unused35;
static Tpidmap tp_unused36;
static Tpidmap tp_unused37;
static Tpidmap tp_unused38;
static Tpidmap tp_unused39;
static Tpidmap tp_unused4;
static Tpidmap tp_unused40;
static Tpidmap tp_unused41;
static Tpidmap tp_unused42;
static Tpidmap tp_unused43;
static Tpidmap tp_unused44;
static Tpidmap tp_unused45;
static Tpidmap tp_unused46;
static Tpidmap tp_unused47;
static Tpidmap tp_unused48;
static Tpidmap tp_unused49;
static Tpidmap tp_unused5;
static Tpidmap tp_unused50;
static Tpidmap tp_unused51;
static Tpidmap tp_unused52;
static Tpidmap tp_unused53;
static Tpidmap tp_unused54;
static Tpidmap tp_unused55;
static Tpidmap tp_unused56;
static Tpidmap tp_unused57;
static Tpidmap tp_unused58;
static Tpidmap tp_unused59;
static Tpidmap tp_unused6;
static Tpidmap tp_unused60;
static Tpidmap tp_unused61;
static Tpidmap tp_unused62;
static Tpidmap tp_unused63;
static Tpidmap tp_unused64;
static Tpidmap tp_unused65;
static Tpidmap tp_unused66;
static Tpidmap tp_unused67;
static Tpidmap tp_unused68;
static Tpidmap tp_unused69;
static Tpidmap tp_unused7;
static Tpidmap tp_unused70;
static Tpidmap tp_unused71;
static Tpidmap tp_unused72;
static Tpidmap tp_unused73;
static Tpidmap tp_unused74;
static Tpidmap tp_unused75;
static Tpidmap tp_unused76;
static Tpidmap tp_unused77;
static Tpidmap tp_unused78;
static Tpidmap tp_unused79;
static Tpidmap tp_unused8;
static Tpidmap tp_unused80;
static Tpidmap tp_unused81;
static Tpidmap tp_unused82;
static Tpidmap tp_unused83;
static Tpidmap tp_unused84;
static Tpidmap tp_unused85;
static Tpidmap tp_unused86;
static Tpidmap tp_unused87;
static Tpidmap tp_unused88;
static Tpidmap tp_unused89;
static Tpidmap tp_unused9;
static Tpidmap tp_unused90;
static Tpidmap tp_unused91;
static Tpidmap tp_unused92;
static Tpidmap tp_unused93;
static Tpidmap tp_unused94;
static Tpidmap tp_unused95;
static Tpidmap tp_unused96;
static Tpidmap tp_unused97;
static Tpidmap tp_unused98;
static Tpidmap tp_unused99;
static Tpidmap tp_wall;
// end sort marker3 }

static std::map< std::string, class Tp * > tp_name_map;

static uint8_t tp_init_done;

Tp::Tp(void) { newptr(MTYPE_TP, this, "Tp"); }

Tp::~Tp(void) { oldptr(MTYPE_TP, this); }

Tpp tp_find(const char *name_in)
{
  TRACE_NO_INDENT();

  std::string name(name_in);
  auto        result = tp_name_map.find(name);

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

  tp_id_map = {};
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

  if (tp_find(name_in)) {
    DIE("tp_load: thing template name [%s] already loaded", name_in);
  }

  auto tp = new Tp();
  tp->name = name;
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
  return tp->tiles[0];
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

    if (tp->is_player) {
      tp_player.push_back(tp);
    }

    if (tp->is_key) {
      tp_key.push_back(tp);
    }

    if (tp->is_wall) {
      tp_wall.push_back(tp);
    }

    if (tp->is_door) {
      tp_door.push_back(tp);
    }

    if (tp->is_floor) {
      tp_floor.push_back(tp);
    }

    if (tp->is_unused1) {
      tp_unused1.push_back(tp);
    }

    if (tp->is_unused2) {
      tp_unused2.push_back(tp);
    }

    if (tp->is_unused3) {
      tp_unused3.push_back(tp);
    }

    if (tp->is_unused4) {
      tp_unused4.push_back(tp);
    }

    if (tp->is_unused5) {
      tp_unused5.push_back(tp);
    }

    if (tp->is_unused6) {
      tp_unused6.push_back(tp);
    }

    if (tp->is_unused7) {
      tp_unused7.push_back(tp);
    }

    if (tp->is_unused8) {
      tp_unused8.push_back(tp);
    }

    if (tp->is_unused9) {
      tp_unused9.push_back(tp);
    }

    if (tp->is_unused10) {
      tp_unused10.push_back(tp);
    }

    if (tp->is_unused11) {
      tp_unused11.push_back(tp);
    }

    if (tp->is_unused12) {
      tp_unused12.push_back(tp);
    }

    if (tp->is_unused13) {
      tp_unused13.push_back(tp);
    }

    if (tp->is_unused14) {
      tp_unused14.push_back(tp);
    }

    if (tp->is_unused15) {
      tp_unused15.push_back(tp);
    }

    if (tp->is_unused16) {
      tp_unused16.push_back(tp);
    }

    if (tp->is_unused17) {
      tp_unused17.push_back(tp);
    }

    if (tp->is_unused18) {
      tp_unused18.push_back(tp);
    }

    if (tp->is_unused19) {
      tp_unused19.push_back(tp);
    }

    if (tp->is_unused20) {
      tp_unused20.push_back(tp);
    }

    if (tp->is_unused21) {
      tp_unused21.push_back(tp);
    }

    if (tp->is_unused22) {
      tp_unused22.push_back(tp);
    }

    if (tp->is_unused23) {
      tp_unused23.push_back(tp);
    }

    if (tp->is_unused24) {
      tp_unused24.push_back(tp);
    }

    if (tp->is_unused25) {
      tp_unused25.push_back(tp);
    }

    if (tp->is_unused26) {
      tp_unused26.push_back(tp);
    }

    if (tp->is_unused27) {
      tp_unused27.push_back(tp);
    }

    if (tp->is_unused28) {
      tp_unused28.push_back(tp);
    }

    if (tp->is_unused29) {
      tp_unused29.push_back(tp);
    }

    if (tp->is_unused30) {
      tp_unused30.push_back(tp);
    }

    if (tp->is_unused31) {
      tp_unused31.push_back(tp);
    }

    if (tp->is_unused32) {
      tp_unused32.push_back(tp);
    }

    if (tp->is_unused33) {
      tp_unused33.push_back(tp);
    }

    if (tp->is_unused34) {
      tp_unused34.push_back(tp);
    }

    if (tp->is_unused35) {
      tp_unused35.push_back(tp);
    }

    if (tp->is_unused36) {
      tp_unused36.push_back(tp);
    }

    if (tp->is_unused37) {
      tp_unused37.push_back(tp);
    }

    if (tp->is_unused38) {
      tp_unused38.push_back(tp);
    }

    if (tp->is_unused39) {
      tp_unused39.push_back(tp);
    }

    if (tp->is_unused40) {
      tp_unused40.push_back(tp);
    }

    if (tp->is_unused41) {
      tp_unused41.push_back(tp);
    }

    if (tp->is_unused42) {
      tp_unused42.push_back(tp);
    }

    if (tp->is_unused43) {
      tp_unused43.push_back(tp);
    }

    if (tp->is_unused44) {
      tp_unused44.push_back(tp);
    }

    if (tp->is_unused45) {
      tp_unused45.push_back(tp);
    }

    if (tp->is_unused46) {
      tp_unused46.push_back(tp);
    }

    if (tp->is_unused47) {
      tp_unused47.push_back(tp);
    }

    if (tp->is_unused48) {
      tp_unused48.push_back(tp);
    }

    if (tp->is_unused49) {
      tp_unused49.push_back(tp);
    }

    if (tp->is_unused50) {
      tp_unused50.push_back(tp);
    }

    if (tp->is_unused51) {
      tp_unused51.push_back(tp);
    }

    if (tp->is_unused52) {
      tp_unused52.push_back(tp);
    }

    if (tp->is_unused53) {
      tp_unused53.push_back(tp);
    }

    if (tp->is_unused54) {
      tp_unused54.push_back(tp);
    }

    if (tp->is_unused55) {
      tp_unused55.push_back(tp);
    }

    if (tp->is_unused56) {
      tp_unused56.push_back(tp);
    }

    if (tp->is_unused57) {
      tp_unused57.push_back(tp);
    }

    if (tp->is_unused58) {
      tp_unused58.push_back(tp);
    }

    if (tp->is_unused59) {
      tp_unused59.push_back(tp);
    }

    if (tp->is_unused60) {
      tp_unused60.push_back(tp);
    }

    if (tp->is_unused61) {
      tp_unused61.push_back(tp);
    }

    if (tp->is_unused62) {
      tp_unused62.push_back(tp);
    }

    if (tp->is_unused63) {
      tp_unused63.push_back(tp);
    }

    if (tp->is_unused64) {
      tp_unused64.push_back(tp);
    }

    if (tp->is_unused65) {
      tp_unused65.push_back(tp);
    }

    if (tp->is_unused66) {
      tp_unused66.push_back(tp);
    }

    if (tp->is_unused67) {
      tp_unused67.push_back(tp);
    }

    if (tp->is_unused68) {
      tp_unused68.push_back(tp);
    }

    if (tp->is_unused69) {
      tp_unused69.push_back(tp);
    }

    if (tp->is_unused70) {
      tp_unused70.push_back(tp);
    }

    if (tp->is_unused71) {
      tp_unused71.push_back(tp);
    }

    if (tp->is_unused72) {
      tp_unused72.push_back(tp);
    }

    if (tp->is_unused73) {
      tp_unused73.push_back(tp);
    }

    if (tp->is_unused74) {
      tp_unused74.push_back(tp);
    }

    if (tp->is_unused75) {
      tp_unused75.push_back(tp);
    }

    if (tp->is_unused76) {
      tp_unused76.push_back(tp);
    }

    if (tp->is_unused77) {
      tp_unused77.push_back(tp);
    }

    if (tp->is_unused78) {
      tp_unused78.push_back(tp);
    }

    if (tp->is_unused79) {
      tp_unused79.push_back(tp);
    }

    if (tp->is_unused80) {
      tp_unused80.push_back(tp);
    }

    if (tp->is_unused81) {
      tp_unused81.push_back(tp);
    }

    if (tp->is_unused82) {
      tp_unused82.push_back(tp);
    }

    if (tp->is_unused83) {
      tp_unused83.push_back(tp);
    }

    if (tp->is_unused84) {
      tp_unused84.push_back(tp);
    }

    if (tp->is_unused85) {
      tp_unused85.push_back(tp);
    }

    if (tp->is_unused86) {
      tp_unused86.push_back(tp);
    }

    if (tp->is_unused87) {
      tp_unused87.push_back(tp);
    }

    if (tp->is_unused88) {
      tp_unused88.push_back(tp);
    }

    if (tp->is_unused89) {
      tp_unused89.push_back(tp);
    }

    if (tp->is_unused90) {
      tp_unused90.push_back(tp);
    }

    if (tp->is_unused91) {
      tp_unused91.push_back(tp);
    }

    if (tp->is_unused92) {
      tp_unused92.push_back(tp);
    }

    if (tp->is_unused93) {
      tp_unused93.push_back(tp);
    }

    if (tp->is_unused94) {
      tp_unused94.push_back(tp);
    }

    if (tp->is_unused95) {
      tp_unused95.push_back(tp);
    }

    if (tp->is_unused96) {
      tp_unused96.push_back(tp);
    }

    if (tp->is_unused97) {
      tp_unused97.push_back(tp);
    }

    if (tp->is_unused98) {
      tp_unused98.push_back(tp);
    }

    if (tp->is_unused99) {
      tp_unused99.push_back(tp);
    }

    if (tp->is_unused100) {
      tp_unused100.push_back(tp);
    }

    if (tp->is_unused101) {
      tp_unused101.push_back(tp);
    }

    if (tp->is_unused102) {
      tp_unused102.push_back(tp);
    }

    if (tp->is_unused103) {
      tp_unused103.push_back(tp);
    }

    if (tp->is_unused104) {
      tp_unused104.push_back(tp);
    }

    if (tp->is_unused105) {
      tp_unused105.push_back(tp);
    }

    if (tp->is_unused106) {
      tp_unused106.push_back(tp);
    }

    if (tp->is_unused107) {
      tp_unused107.push_back(tp);
    }

    if (tp->is_unused108) {
      tp_unused108.push_back(tp);
    }

    if (tp->is_unused109) {
      tp_unused109.push_back(tp);
    }

    if (tp->is_unused110) {
      tp_unused110.push_back(tp);
    }

    if (tp->is_unused111) {
      tp_unused111.push_back(tp);
    }

    if (tp->is_unused112) {
      tp_unused112.push_back(tp);
    }

    if (tp->is_unused113) {
      tp_unused113.push_back(tp);
    }

    if (tp->is_unused114) {
      tp_unused114.push_back(tp);
    }

    if (tp->is_unused115) {
      tp_unused115.push_back(tp);
    }

    if (tp->is_unused116) {
      tp_unused116.push_back(tp);
    }

    if (tp->is_unused117) {
      tp_unused117.push_back(tp);
    }

    if (tp->is_unused118) {
      tp_unused118.push_back(tp);
    }

    if (tp->is_unused119) {
      tp_unused119.push_back(tp);
    }

    if (tp->is_unused120) {
      tp_unused120.push_back(tp);
    }

    if (tp->is_unused121) {
      tp_unused121.push_back(tp);
    }

    if (tp->is_unused122) {
      tp_unused122.push_back(tp);
    }

    if (tp->is_unused123) {
      tp_unused123.push_back(tp);
    }

    if (tp->is_unused124) {
      tp_unused124.push_back(tp);
    }

    if (tp->is_unused125) {
      tp_unused125.push_back(tp);
    }

    if (tp->is_unused126) {
      tp_unused126.push_back(tp);
    }

    if (tp->is_unused127) {
      tp_unused127.push_back(tp);
    }

    if (tp->is_unused128) {
      tp_unused128.push_back(tp);
    }

    if (tp->is_unused129) {
      tp_unused129.push_back(tp);
    }

    if (tp->is_unused130) {
      tp_unused130.push_back(tp);
    }

    if (tp->is_unused131) {
      tp_unused131.push_back(tp);
    }

    if (tp->is_unused132) {
      tp_unused132.push_back(tp);
    }

    if (tp->is_unused133) {
      tp_unused133.push_back(tp);
    }

    if (tp->is_unused134) {
      tp_unused134.push_back(tp);
    }

    if (tp->is_unused135) {
      tp_unused135.push_back(tp);
    }

    if (tp->is_unused136) {
      tp_unused136.push_back(tp);
    }

    if (tp->is_unused137) {
      tp_unused137.push_back(tp);
    }

    if (tp->is_unused138) {
      tp_unused138.push_back(tp);
    }

    if (tp->is_unused139) {
      tp_unused139.push_back(tp);
    }

    if (tp->is_unused140) {
      tp_unused140.push_back(tp);
    }

    if (tp->is_unused141) {
      tp_unused141.push_back(tp);
    }

    if (tp->is_unused142) {
      tp_unused142.push_back(tp);
    }

    if (tp->is_unused143) {
      tp_unused143.push_back(tp);
    }

    if (tp->is_unused144) {
      tp_unused144.push_back(tp);
    }

    if (tp->is_unused145) {
      tp_unused145.push_back(tp);
    }

    if (tp->is_unused146) {
      tp_unused146.push_back(tp);
    }

    if (tp->is_unused147) {
      tp_unused147.push_back(tp);
    }

    if (tp->is_unused148) {
      tp_unused148.push_back(tp);
    }

    if (tp->is_unused149) {
      tp_unused149.push_back(tp);
    }

    if (tp->is_unused150) {
      tp_unused150.push_back(tp);
    }

    if (tp->is_unused151) {
      tp_unused151.push_back(tp);
    }

    if (tp->is_unused152) {
      tp_unused152.push_back(tp);
    }

    if (tp->is_unused153) {
      tp_unused153.push_back(tp);
    }

    if (tp->is_unused154) {
      tp_unused154.push_back(tp);
    }

    if (tp->is_unused155) {
      tp_unused155.push_back(tp);
    }

    if (tp->is_unused156) {
      tp_unused156.push_back(tp);
    }

    if (tp->is_unused157) {
      tp_unused157.push_back(tp);
    }

    if (tp->is_unused158) {
      tp_unused158.push_back(tp);
    }

    if (tp->is_unused159) {
      tp_unused159.push_back(tp);
    }

    if (tp->is_unused160) {
      tp_unused160.push_back(tp);
    }

    if (tp->is_unused161) {
      tp_unused161.push_back(tp);
    }

    if (tp->is_unused162) {
      tp_unused162.push_back(tp);
    }

    if (tp->is_unused163) {
      tp_unused163.push_back(tp);
    }

    if (tp->is_unused164) {
      tp_unused164.push_back(tp);
    }

    if (tp->is_unused165) {
      tp_unused165.push_back(tp);
    }

    if (tp->is_unused166) {
      tp_unused166.push_back(tp);
    }

    if (tp->is_unused167) {
      tp_unused167.push_back(tp);
    }

    if (tp->is_unused168) {
      tp_unused168.push_back(tp);
    }

    if (tp->is_unused169) {
      tp_unused169.push_back(tp);
    }

    if (tp->is_unused170) {
      tp_unused170.push_back(tp);
    }

    if (tp->is_unused171) {
      tp_unused171.push_back(tp);
    }

    if (tp->is_unused172) {
      tp_unused172.push_back(tp);
    }

    if (tp->is_unused173) {
      tp_unused173.push_back(tp);
    }

    if (tp->is_unused174) {
      tp_unused174.push_back(tp);
    }

    if (tp->is_unused175) {
      tp_unused175.push_back(tp);
    }

    if (tp->is_unused176) {
      tp_unused176.push_back(tp);
    }

    if (tp->is_unused177) {
      tp_unused177.push_back(tp);
    }

    if (tp->is_unused178) {
      tp_unused178.push_back(tp);
    }

    if (tp->is_unused179) {
      tp_unused179.push_back(tp);
    }

    if (tp->is_unused180) {
      tp_unused180.push_back(tp);
    }

    if (tp->is_unused181) {
      tp_unused181.push_back(tp);
    }

    if (tp->is_unused182) {
      tp_unused182.push_back(tp);
    }

    if (tp->is_unused183) {
      tp_unused183.push_back(tp);
    }

    if (tp->is_unused184) {
      tp_unused184.push_back(tp);
    }

    if (tp->is_unused185) {
      tp_unused185.push_back(tp);
    }

    if (tp->is_unused186) {
      tp_unused186.push_back(tp);
    }

    if (tp->is_unused187) {
      tp_unused187.push_back(tp);
    }

    if (tp->is_unused188) {
      tp_unused188.push_back(tp);
    }

    if (tp->is_unused189) {
      tp_unused189.push_back(tp);
    }

    if (tp->is_unused190) {
      tp_unused190.push_back(tp);
    }

    if (tp->is_unused191) {
      tp_unused191.push_back(tp);
    }

    if (tp->is_unused192) {
      tp_unused192.push_back(tp);
    }

    if (tp->is_unused193) {
      tp_unused193.push_back(tp);
    }

    if (tp->is_unused194) {
      tp_unused194.push_back(tp);
    }

    if (tp->is_unused195) {
      tp_unused195.push_back(tp);
    }

    if (tp->is_unused196) {
      tp_unused196.push_back(tp);
    }

    if (tp->is_unused197) {
      tp_unused197.push_back(tp);
    }

    if (tp->is_unused198) {
      tp_unused198.push_back(tp);
    }

    if (tp->is_cursor_at) {
      tp_is_cursor_at.push_back(tp);
    }

    if (tp->is_cursor_path) {
      tp_is_cursor_path.push_back(tp);
    }

    if (tp->is_dungeon_entrance) {
      tp_dungeon_entrance.push_back(tp);
    }

    if (tp->is_exit) {
      tp_exit.push_back(tp);
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

Tpp tp_random_player(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_player.size())) {
    DIE("No player found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_player);
}

Tpp tp_random_wall(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_wall.size())) {
    DIE("No wall found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_wall);
}

Tpp tp_random_unused1(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused1.size())) {
    DIE("No unused1 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused1);
}

Tpp tp_random_unused2(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused2.size())) {
    DIE("No unused2 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused2);
}

Tpp tp_random_unused3(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused3.size())) {
    DIE("No unused3 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused3);
}

Tpp tp_random_unused4(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused4.size())) {
    DIE("No unused4 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused4);
}

Tpp tp_random_unused5(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused5.size())) {
    DIE("No unused5 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused5);
}

Tpp tp_random_unused6(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused6.size())) {
    DIE("No unused6 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused6);
}

Tpp tp_random_unused7(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused7.size())) {
    DIE("No unused7 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused7);
}

Tpp tp_random_unused8(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused8.size())) {
    DIE("No unused8 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused8);
}

Tpp tp_random_unused9(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused9.size())) {
    DIE("No unused9 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused9);
}

Tpp tp_random_unused10(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused10.size())) {
    DIE("No unused10 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused10);
}

Tpp tp_random_unused11(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused11.size())) {
    DIE("No unused11 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused11);
}

Tpp tp_random_unused12(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused12.size())) {
    DIE("No unused12 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused12);
}

Tpp tp_random_unused13(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused13.size())) {
    DIE("No unused13 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused13);
}

Tpp tp_random_unused14(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused14.size())) {
    DIE("No unused14 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused14);
}

Tpp tp_random_unused15(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused15.size())) {
    DIE("No unused15 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused15);
}

Tpp tp_random_unused16(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused16.size())) {
    DIE("No unused16 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused16);
}

Tpp tp_random_unused17(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused17.size())) {
    DIE("No unused17 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused17);
}

Tpp tp_random_unused18(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused18.size())) {
    DIE("No unused18 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused18);
}

Tpp tp_random_unused19(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused19.size())) {
    DIE("No unused19 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused19);
}

Tpp tp_random_unused20(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused20.size())) {
    DIE("No unused20 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused20);
}

Tpp tp_random_unused21(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused21.size())) {
    DIE("No unused21 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused21);
}

Tpp tp_random_unused22(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused22.size())) {
    DIE("No unused22 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused22);
}

Tpp tp_random_unused23(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused23.size())) {
    DIE("No unused23 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused23);
}

Tpp tp_random_unused24(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused24.size())) {
    DIE("No unused24 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused24);
}

Tpp tp_random_unused25(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused25.size())) {
    DIE("No unused25 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused25);
}

Tpp tp_random_unused26(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused26.size())) {
    DIE("No unused26 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused26);
}

Tpp tp_random_unused27(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused27.size())) {
    DIE("No unused27 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused27);
}

Tpp tp_random_unused28(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused28.size())) {
    DIE("No unused28 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused28);
}

Tpp tp_random_unused29(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused29.size())) {
    DIE("No unused29 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused29);
}

Tpp tp_random_unused30(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused30.size())) {
    DIE("No unused30 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused30);
}

Tpp tp_random_unused31(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused31.size())) {
    DIE("No unused31 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused31);
}

Tpp tp_random_unused32(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused32.size())) {
    DIE("No unused32 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused32);
}

Tpp tp_random_unused33(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused33.size())) {
    DIE("No unused33 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused33);
}

Tpp tp_random_unused34(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused34.size())) {
    DIE("No unused34 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused34);
}

Tpp tp_random_unused35(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused35.size())) {
    DIE("No unused35 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused35);
}

Tpp tp_random_unused36(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused36.size())) {
    DIE("No unused36 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused36);
}

Tpp tp_random_unused37(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused37.size())) {
    DIE("No unused37 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused37);
}

Tpp tp_random_unused38(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused38.size())) {
    DIE("No unused38 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused38);
}

Tpp tp_random_unused39(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused39.size())) {
    DIE("No unused39 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused39);
}

Tpp tp_random_unused40(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused40.size())) {
    DIE("No unused40 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused40);
}

Tpp tp_random_unused41(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused41.size())) {
    DIE("No unused41 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused41);
}

Tpp tp_random_unused42(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused42.size())) {
    DIE("No unused42 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused42);
}

Tpp tp_random_unused43(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused43.size())) {
    DIE("No unused43 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused43);
}

Tpp tp_random_unused44(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused44.size())) {
    DIE("No unused44 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused44);
}

Tpp tp_random_unused45(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused45.size())) {
    DIE("No unused45 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused45);
}

Tpp tp_random_unused46(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused46.size())) {
    DIE("No unused46 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused46);
}

Tpp tp_random_unused47(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused47.size())) {
    DIE("No unused47 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused47);
}

Tpp tp_random_unused48(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused48.size())) {
    DIE("No unused48 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused48);
}

Tpp tp_random_unused49(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused49.size())) {
    DIE("No unused49 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused49);
}

Tpp tp_random_unused50(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused50.size())) {
    DIE("No unused50 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused50);
}

Tpp tp_random_unused51(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused51.size())) {
    DIE("No unused51 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused51);
}

Tpp tp_random_unused52(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused52.size())) {
    DIE("No unused52 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused52);
}

Tpp tp_random_unused53(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused53.size())) {
    DIE("No unused53 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused53);
}

Tpp tp_random_unused54(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused54.size())) {
    DIE("No unused54 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused54);
}

Tpp tp_random_unused55(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused55.size())) {
    DIE("No unused55 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused55);
}

Tpp tp_random_unused56(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused56.size())) {
    DIE("No unused56 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused56);
}

Tpp tp_random_unused57(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused57.size())) {
    DIE("No unused57 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused57);
}

Tpp tp_random_unused58(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused58.size())) {
    DIE("No unused58 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused58);
}

Tpp tp_random_unused59(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused59.size())) {
    DIE("No unused59 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused59);
}

Tpp tp_random_unused60(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused60.size())) {
    DIE("No unused60 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused60);
}

Tpp tp_random_unused61(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused61.size())) {
    DIE("No unused61 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused61);
}

Tpp tp_random_unused62(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused62.size())) {
    DIE("No unused62 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused62);
}

Tpp tp_random_unused63(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused63.size())) {
    DIE("No unused63 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused63);
}

Tpp tp_random_unused64(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused64.size())) {
    DIE("No unused64 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused64);
}

Tpp tp_random_unused65(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused65.size())) {
    DIE("No unused65 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused65);
}

Tpp tp_random_unused66(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused66.size())) {
    DIE("No unused66 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused66);
}

Tpp tp_random_unused67(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused67.size())) {
    DIE("No unused67 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused67);
}

Tpp tp_random_unused68(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused68.size())) {
    DIE("No unused68 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused68);
}

Tpp tp_random_unused69(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused69.size())) {
    DIE("No unused69 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused69);
}

Tpp tp_random_unused70(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused70.size())) {
    DIE("No unused70 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused70);
}

Tpp tp_random_unused71(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused71.size())) {
    DIE("No unused71 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused71);
}

Tpp tp_random_unused72(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused72.size())) {
    DIE("No unused72 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused72);
}

Tpp tp_random_unused73(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused73.size())) {
    DIE("No unused73 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused73);
}

Tpp tp_random_unused74(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused74.size())) {
    DIE("No unused74 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused74);
}

Tpp tp_random_unused75(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused75.size())) {
    DIE("No unused75 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused75);
}

Tpp tp_random_unused76(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused76.size())) {
    DIE("No unused76 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused76);
}

Tpp tp_random_unused77(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused77.size())) {
    DIE("No unused77 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused77);
}

Tpp tp_random_unused78(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused78.size())) {
    DIE("No unused78 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused78);
}

Tpp tp_random_unused79(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused79.size())) {
    DIE("No unused79 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused79);
}

Tpp tp_random_unused80(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused80.size())) {
    DIE("No unused80 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused80);
}

Tpp tp_random_unused81(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused81.size())) {
    DIE("No unused81 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused81);
}

Tpp tp_random_unused82(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused82.size())) {
    DIE("No unused82 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused82);
}

Tpp tp_random_unused83(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused83.size())) {
    DIE("No unused83 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused83);
}

Tpp tp_random_unused84(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused84.size())) {
    DIE("No unused84 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused84);
}

Tpp tp_random_unused85(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused85.size())) {
    DIE("No unused85 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused85);
}

Tpp tp_random_unused86(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused86.size())) {
    DIE("No unused86 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused86);
}

Tpp tp_random_unused87(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused87.size())) {
    DIE("No unused87 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused87);
}

Tpp tp_random_unused88(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused88.size())) {
    DIE("No unused88 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused88);
}

Tpp tp_random_unused89(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused89.size())) {
    DIE("No unused89 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused89);
}

Tpp tp_random_unused90(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused90.size())) {
    DIE("No unused90 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused90);
}

Tpp tp_random_unused91(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused91.size())) {
    DIE("No unused91 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused91);
}

Tpp tp_random_unused92(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused92.size())) {
    DIE("No unused92 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused92);
}

Tpp tp_random_unused93(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused93.size())) {
    DIE("No unused93 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused93);
}

Tpp tp_random_unused94(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused94.size())) {
    DIE("No unused94 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused94);
}

Tpp tp_random_unused95(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused95.size())) {
    DIE("No unused95 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused95);
}

Tpp tp_random_unused96(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused96.size())) {
    DIE("No unused96 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused96);
}

Tpp tp_random_unused97(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused97.size())) {
    DIE("No unused97 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused97);
}

Tpp tp_random_unused98(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused98.size())) {
    DIE("No unused98 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused98);
}

Tpp tp_random_unused99(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused99.size())) {
    DIE("No unused99 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused99);
}

Tpp tp_random_unused100(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused100.size())) {
    DIE("No unused100 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused100);
}

Tpp tp_random_unused101(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused101.size())) {
    DIE("No unused101 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused101);
}

Tpp tp_random_unused102(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused102.size())) {
    DIE("No unused102 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused102);
}

Tpp tp_random_unused103(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused103.size())) {
    DIE("No unused103 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused103);
}

Tpp tp_random_unused104(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused104.size())) {
    DIE("No unused104 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused104);
}

Tpp tp_random_unused105(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused105.size())) {
    DIE("No unused105 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused105);
}

Tpp tp_random_unused106(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused106.size())) {
    DIE("No unused106 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused106);
}

Tpp tp_random_unused107(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused107.size())) {
    DIE("No unused107 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused107);
}

Tpp tp_random_unused108(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused108.size())) {
    DIE("No unused108 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused108);
}

Tpp tp_random_unused109(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused109.size())) {
    DIE("No unused109 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused109);
}

Tpp tp_random_unused110(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused110.size())) {
    DIE("No unused110 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused110);
}

Tpp tp_random_unused111(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused111.size())) {
    DIE("No unused111 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused111);
}

Tpp tp_random_unused112(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused112.size())) {
    DIE("No unused112 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused112);
}

Tpp tp_random_unused113(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused113.size())) {
    DIE("No unused113 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused113);
}

Tpp tp_random_unused114(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused114.size())) {
    DIE("No unused114 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused114);
}

Tpp tp_random_unused115(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused115.size())) {
    DIE("No unused115 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused115);
}

Tpp tp_random_unused116(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused116.size())) {
    DIE("No unused116 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused116);
}

Tpp tp_random_unused117(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused117.size())) {
    DIE("No unused117 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused117);
}

Tpp tp_random_unused118(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused118.size())) {
    DIE("No unused118 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused118);
}

Tpp tp_random_unused119(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused119.size())) {
    DIE("No unused119 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused119);
}

Tpp tp_random_unused120(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused120.size())) {
    DIE("No unused120 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused120);
}

Tpp tp_random_unused121(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused121.size())) {
    DIE("No unused121 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused121);
}

Tpp tp_random_unused122(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused122.size())) {
    DIE("No unused122 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused122);
}

Tpp tp_random_unused123(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused123.size())) {
    DIE("No unused123 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused123);
}

Tpp tp_random_unused124(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused124.size())) {
    DIE("No unused124 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused124);
}

Tpp tp_random_unused125(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused125.size())) {
    DIE("No unused125 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused125);
}

Tpp tp_random_unused126(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused126.size())) {
    DIE("No unused126 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused126);
}

Tpp tp_random_unused127(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused127.size())) {
    DIE("No unused127 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused127);
}

Tpp tp_random_unused128(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused128.size())) {
    DIE("No unused128 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused128);
}

Tpp tp_random_unused129(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused129.size())) {
    DIE("No unused129 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused129);
}

Tpp tp_random_unused130(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused130.size())) {
    DIE("No unused130 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused130);
}

Tpp tp_random_unused131(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused131.size())) {
    DIE("No unused131 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused131);
}

Tpp tp_random_unused132(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused132.size())) {
    DIE("No unused132 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused132);
}

Tpp tp_random_unused133(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused133.size())) {
    DIE("No unused133 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused133);
}

Tpp tp_random_unused134(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused134.size())) {
    DIE("No unused134 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused134);
}

Tpp tp_random_unused135(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused135.size())) {
    DIE("No unused135 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused135);
}

Tpp tp_random_unused136(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused136.size())) {
    DIE("No unused136 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused136);
}

Tpp tp_random_unused137(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused137.size())) {
    DIE("No unused137 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused137);
}

Tpp tp_random_unused138(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused138.size())) {
    DIE("No unused138 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused138);
}

Tpp tp_random_unused139(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused139.size())) {
    DIE("No unused139 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused139);
}

Tpp tp_random_unused140(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused140.size())) {
    DIE("No unused140 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused140);
}

Tpp tp_random_unused141(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused141.size())) {
    DIE("No unused141 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused141);
}

Tpp tp_random_unused142(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused142.size())) {
    DIE("No unused142 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused142);
}

Tpp tp_random_unused143(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused143.size())) {
    DIE("No unused143 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused143);
}

Tpp tp_random_unused144(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused144.size())) {
    DIE("No unused144 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused144);
}

Tpp tp_random_unused145(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused145.size())) {
    DIE("No unused145 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused145);
}

Tpp tp_random_unused146(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused146.size())) {
    DIE("No unused146 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused146);
}

Tpp tp_random_unused147(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused147.size())) {
    DIE("No unused147 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused147);
}

Tpp tp_random_unused148(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused148.size())) {
    DIE("No unused148 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused148);
}

Tpp tp_random_unused149(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused149.size())) {
    DIE("No unused149 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused149);
}

Tpp tp_random_unused150(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused150.size())) {
    DIE("No unused150 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused150);
}

Tpp tp_random_unused151(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused151.size())) {
    DIE("No unused151 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused151);
}

Tpp tp_random_unused152(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused152.size())) {
    DIE("No unused152 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused152);
}

Tpp tp_random_unused153(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused153.size())) {
    DIE("No unused153 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused153);
}

Tpp tp_random_unused154(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused154.size())) {
    DIE("No unused154 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused154);
}

Tpp tp_random_unused155(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused155.size())) {
    DIE("No unused155 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused155);
}

Tpp tp_random_unused156(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused156.size())) {
    DIE("No unused156 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused156);
}

Tpp tp_random_unused157(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused157.size())) {
    DIE("No unused157 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused157);
}

Tpp tp_random_unused158(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused158.size())) {
    DIE("No unused158 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused158);
}

Tpp tp_random_unused159(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused159.size())) {
    DIE("No unused159 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused159);
}

Tpp tp_random_unused160(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused160.size())) {
    DIE("No unused160 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused160);
}

Tpp tp_random_unused161(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused161.size())) {
    DIE("No unused161 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused161);
}

Tpp tp_random_unused162(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused162.size())) {
    DIE("No unused162 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused162);
}

Tpp tp_random_unused163(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused163.size())) {
    DIE("No unused163 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused163);
}

Tpp tp_random_unused164(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused164.size())) {
    DIE("No unused164 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused164);
}

Tpp tp_random_unused165(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused165.size())) {
    DIE("No unused165 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused165);
}

Tpp tp_random_unused166(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused166.size())) {
    DIE("No unused166 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused166);
}

Tpp tp_random_unused167(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused167.size())) {
    DIE("No unused167 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused167);
}

Tpp tp_random_unused168(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused168.size())) {
    DIE("No unused168 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused168);
}

Tpp tp_random_unused169(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused169.size())) {
    DIE("No unused169 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused169);
}

Tpp tp_random_unused170(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused170.size())) {
    DIE("No unused170 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused170);
}

Tpp tp_random_unused171(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused171.size())) {
    DIE("No unused171 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused171);
}

Tpp tp_random_unused172(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused172.size())) {
    DIE("No unused172 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused172);
}

Tpp tp_random_unused173(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused173.size())) {
    DIE("No unused173 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused173);
}

Tpp tp_random_unused174(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused174.size())) {
    DIE("No unused174 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused174);
}

Tpp tp_random_unused175(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused175.size())) {
    DIE("No unused175 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused175);
}

Tpp tp_random_unused176(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused176.size())) {
    DIE("No unused176 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused176);
}

Tpp tp_random_unused177(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused177.size())) {
    DIE("No unused177 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused177);
}

Tpp tp_random_unused178(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused178.size())) {
    DIE("No unused178 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused178);
}

Tpp tp_random_unused179(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused179.size())) {
    DIE("No unused179 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused179);
}

Tpp tp_random_unused180(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused180.size())) {
    DIE("No unused180 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused180);
}

Tpp tp_random_unused181(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused181.size())) {
    DIE("No unused181 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused181);
}

Tpp tp_random_unused182(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused182.size())) {
    DIE("No unused182 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused182);
}

Tpp tp_random_unused183(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused183.size())) {
    DIE("No unused183 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused183);
}

Tpp tp_random_unused184(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused184.size())) {
    DIE("No unused184 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused184);
}

Tpp tp_random_unused185(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused185.size())) {
    DIE("No unused185 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused185);
}

Tpp tp_random_unused186(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused186.size())) {
    DIE("No unused186 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused186);
}

Tpp tp_random_unused187(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused187.size())) {
    DIE("No unused187 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused187);
}

Tpp tp_random_unused188(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused188.size())) {
    DIE("No unused188 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused188);
}

Tpp tp_random_unused189(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused189.size())) {
    DIE("No unused189 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused189);
}

Tpp tp_random_unused190(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused190.size())) {
    DIE("No unused190 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused190);
}

Tpp tp_random_unused191(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused191.size())) {
    DIE("No unused191 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused191);
}

Tpp tp_random_unused192(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused192.size())) {
    DIE("No unused192 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused192);
}

Tpp tp_random_unused193(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused193.size())) {
    DIE("No unused193 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused193);
}

Tpp tp_random_unused194(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused194.size())) {
    DIE("No unused194 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused194);
}

Tpp tp_random_unused195(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused195.size())) {
    DIE("No unused195 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused195);
}

Tpp tp_random_unused196(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused196.size())) {
    DIE("No unused196 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused196);
}

Tpp tp_random_unused197(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused197.size())) {
    DIE("No unused197 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused197);
}

Tpp tp_random_unused198(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_unused198.size())) {
    DIE("No unused198 found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_unused198);
}

Tpp tp_random_is_cursor_at(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_is_cursor_at.size())) {
    DIE("No is_cursor_at found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_is_cursor_at);
}

Tpp tp_random_is_cursor_path(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_is_cursor_path.size())) {
    DIE("No is_cursor_path found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_is_cursor_path);
}

Tpp tp_random_key(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_key.size())) {
    DIE("No keys found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_key);
}

Tpp tp_random_dungeon_entrance(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_dungeon_entrance.size())) {
    DIE("No entrances found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_dungeon_entrance);
}

Tpp tp_random_exit(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_exit.size())) {
    DIE("No exits found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_exit);
}

Tilep tp_tiles_get(Tpp tp, int index) { return tp->tiles[ index ]; }
void  tp_tiles_push_back(Tpp tp, Tilep val) { tp->tiles.push_back(val); }
int   tp_tiles_size(Tpp tp) { return (int) tp->tiles.size(); }

const char *tp_name(Tpp tp) { return tp->name.c_str(); }
const char *to_string(Tpp tp) { return tp->text_short_name.c_str(); }
const char *to_short_string(Tpp tp) { return tp->text_short_name.c_str(); }

bool tp_is_animated_can_hflip_get(Tpp tp) { return tp->is_animated_can_hflip; }
void tp_is_animated_can_hflip_set(Tpp tp, bool val) { tp->is_animated_can_hflip = val; }

bool tp_is_animated_no_dir_get(Tpp tp) { return tp->is_animated_no_dir; }
void tp_is_animated_no_dir_set(Tpp tp, bool val) { tp->is_animated_no_dir = val; }

bool tp_is_blit_centered_get(Tpp tp) { return tp->is_blit_centered; }
void tp_is_blit_centered_set(Tpp tp, bool val) { tp->is_blit_centered = val; }

bool tp_is_blit_on_ground_get(Tpp tp) { return tp->is_blit_on_ground; }
void tp_is_blit_on_ground_set(Tpp tp, bool val) { tp->is_blit_on_ground = val; }

bool tp_is_blit_outlined_get(Tpp tp) { return tp->is_blit_outlined; }
void tp_is_blit_outlined_set(Tpp tp, bool val) { tp->is_blit_outlined = val; }

bool tp_is_blit_square_outlined_get(Tpp tp) { return tp->is_blit_square_outlined; }
void tp_is_blit_square_outlined_set(Tpp tp, bool val) { tp->is_blit_square_outlined = val; }

bool tp_is_blit_tiled_get(Tpp tp) { return tp->is_blit_tiled; }
void tp_is_blit_tiled_set(Tpp tp, bool val) { tp->is_blit_tiled = val; }

bool tp_is_cursor_get(Tpp tp) { return tp->is_cursor; }
void tp_is_cursor_set(Tpp tp, bool val) { tp->is_cursor = val; }

bool tp_is_door_get(Tpp tp) { return tp->is_door; }
void tp_is_door_set(Tpp tp, bool val) { tp->is_door = val; }

bool tp_is_dungeon_entrance_get(Tpp tp) { return tp->is_dungeon_entrance; }
void tp_is_dungeon_entrance_set(Tpp tp, bool val) { tp->is_dungeon_entrance = val; }

bool tp_is_exit_get(Tpp tp) { return tp->is_exit; }
void tp_is_exit_set(Tpp tp, bool val) { tp->is_exit = val; }

bool tp_is_floor_get(Tpp tp) { return tp->is_floor; }
void tp_is_floor_set(Tpp tp, bool val) { tp->is_floor = val; }

bool tp_is_unused1_get(Tpp tp) { return tp->is_unused1; }
void tp_is_unused1_set(Tpp tp, bool val) { tp->is_unused1 = val; }

bool tp_is_unused2_get(Tpp tp) { return tp->is_unused2; }
void tp_is_unused2_set(Tpp tp, bool val) { tp->is_unused2 = val; }

bool tp_is_unused3_get(Tpp tp) { return tp->is_unused3; }
void tp_is_unused3_set(Tpp tp, bool val) { tp->is_unused3 = val; }

bool tp_is_unused4_get(Tpp tp) { return tp->is_unused4; }
void tp_is_unused4_set(Tpp tp, bool val) { tp->is_unused4 = val; }

bool tp_is_unused5_get(Tpp tp) { return tp->is_unused5; }
void tp_is_unused5_set(Tpp tp, bool val) { tp->is_unused5 = val; }

bool tp_is_unused6_get(Tpp tp) { return tp->is_unused6; }
void tp_is_unused6_set(Tpp tp, bool val) { tp->is_unused6 = val; }

bool tp_is_unused7_get(Tpp tp) { return tp->is_unused7; }
void tp_is_unused7_set(Tpp tp, bool val) { tp->is_unused7 = val; }

bool tp_is_unused8_get(Tpp tp) { return tp->is_unused8; }
void tp_is_unused8_set(Tpp tp, bool val) { tp->is_unused8 = val; }

bool tp_is_unused9_get(Tpp tp) { return tp->is_unused9; }
void tp_is_unused9_set(Tpp tp, bool val) { tp->is_unused9 = val; }

bool tp_is_unused10_get(Tpp tp) { return tp->is_unused10; }
void tp_is_unused10_set(Tpp tp, bool val) { tp->is_unused10 = val; }

bool tp_is_unused11_get(Tpp tp) { return tp->is_unused11; }
void tp_is_unused11_set(Tpp tp, bool val) { tp->is_unused11 = val; }

bool tp_is_unused12_get(Tpp tp) { return tp->is_unused12; }
void tp_is_unused12_set(Tpp tp, bool val) { tp->is_unused12 = val; }

bool tp_is_unused13_get(Tpp tp) { return tp->is_unused13; }
void tp_is_unused13_set(Tpp tp, bool val) { tp->is_unused13 = val; }

bool tp_is_unused14_get(Tpp tp) { return tp->is_unused14; }
void tp_is_unused14_set(Tpp tp, bool val) { tp->is_unused14 = val; }

bool tp_is_unused15_get(Tpp tp) { return tp->is_unused15; }
void tp_is_unused15_set(Tpp tp, bool val) { tp->is_unused15 = val; }

bool tp_is_unused16_get(Tpp tp) { return tp->is_unused16; }
void tp_is_unused16_set(Tpp tp, bool val) { tp->is_unused16 = val; }

bool tp_is_unused17_get(Tpp tp) { return tp->is_unused17; }
void tp_is_unused17_set(Tpp tp, bool val) { tp->is_unused17 = val; }

bool tp_is_unused18_get(Tpp tp) { return tp->is_unused18; }
void tp_is_unused18_set(Tpp tp, bool val) { tp->is_unused18 = val; }

bool tp_is_unused19_get(Tpp tp) { return tp->is_unused19; }
void tp_is_unused19_set(Tpp tp, bool val) { tp->is_unused19 = val; }

bool tp_is_unused20_get(Tpp tp) { return tp->is_unused20; }
void tp_is_unused20_set(Tpp tp, bool val) { tp->is_unused20 = val; }

bool tp_is_unused21_get(Tpp tp) { return tp->is_unused21; }
void tp_is_unused21_set(Tpp tp, bool val) { tp->is_unused21 = val; }

bool tp_is_unused22_get(Tpp tp) { return tp->is_unused22; }
void tp_is_unused22_set(Tpp tp, bool val) { tp->is_unused22 = val; }

bool tp_is_unused23_get(Tpp tp) { return tp->is_unused23; }
void tp_is_unused23_set(Tpp tp, bool val) { tp->is_unused23 = val; }

bool tp_is_unused24_get(Tpp tp) { return tp->is_unused24; }
void tp_is_unused24_set(Tpp tp, bool val) { tp->is_unused24 = val; }

bool tp_is_unused25_get(Tpp tp) { return tp->is_unused25; }
void tp_is_unused25_set(Tpp tp, bool val) { tp->is_unused25 = val; }

bool tp_is_unused26_get(Tpp tp) { return tp->is_unused26; }
void tp_is_unused26_set(Tpp tp, bool val) { tp->is_unused26 = val; }

bool tp_is_unused27_get(Tpp tp) { return tp->is_unused27; }
void tp_is_unused27_set(Tpp tp, bool val) { tp->is_unused27 = val; }

bool tp_is_unused28_get(Tpp tp) { return tp->is_unused28; }
void tp_is_unused28_set(Tpp tp, bool val) { tp->is_unused28 = val; }

bool tp_is_unused29_get(Tpp tp) { return tp->is_unused29; }
void tp_is_unused29_set(Tpp tp, bool val) { tp->is_unused29 = val; }

bool tp_is_unused30_get(Tpp tp) { return tp->is_unused30; }
void tp_is_unused30_set(Tpp tp, bool val) { tp->is_unused30 = val; }

bool tp_is_unused31_get(Tpp tp) { return tp->is_unused31; }
void tp_is_unused31_set(Tpp tp, bool val) { tp->is_unused31 = val; }

bool tp_is_unused32_get(Tpp tp) { return tp->is_unused32; }
void tp_is_unused32_set(Tpp tp, bool val) { tp->is_unused32 = val; }

bool tp_is_unused33_get(Tpp tp) { return tp->is_unused33; }
void tp_is_unused33_set(Tpp tp, bool val) { tp->is_unused33 = val; }

bool tp_is_unused34_get(Tpp tp) { return tp->is_unused34; }
void tp_is_unused34_set(Tpp tp, bool val) { tp->is_unused34 = val; }

bool tp_is_unused35_get(Tpp tp) { return tp->is_unused35; }
void tp_is_unused35_set(Tpp tp, bool val) { tp->is_unused35 = val; }

bool tp_is_unused36_get(Tpp tp) { return tp->is_unused36; }
void tp_is_unused36_set(Tpp tp, bool val) { tp->is_unused36 = val; }

bool tp_is_unused37_get(Tpp tp) { return tp->is_unused37; }
void tp_is_unused37_set(Tpp tp, bool val) { tp->is_unused37 = val; }

bool tp_is_unused38_get(Tpp tp) { return tp->is_unused38; }
void tp_is_unused38_set(Tpp tp, bool val) { tp->is_unused38 = val; }

bool tp_is_unused39_get(Tpp tp) { return tp->is_unused39; }
void tp_is_unused39_set(Tpp tp, bool val) { tp->is_unused39 = val; }

bool tp_is_unused40_get(Tpp tp) { return tp->is_unused40; }
void tp_is_unused40_set(Tpp tp, bool val) { tp->is_unused40 = val; }

bool tp_is_unused41_get(Tpp tp) { return tp->is_unused41; }
void tp_is_unused41_set(Tpp tp, bool val) { tp->is_unused41 = val; }

bool tp_is_unused42_get(Tpp tp) { return tp->is_unused42; }
void tp_is_unused42_set(Tpp tp, bool val) { tp->is_unused42 = val; }

bool tp_is_unused43_get(Tpp tp) { return tp->is_unused43; }
void tp_is_unused43_set(Tpp tp, bool val) { tp->is_unused43 = val; }

bool tp_is_unused44_get(Tpp tp) { return tp->is_unused44; }
void tp_is_unused44_set(Tpp tp, bool val) { tp->is_unused44 = val; }

bool tp_is_unused45_get(Tpp tp) { return tp->is_unused45; }
void tp_is_unused45_set(Tpp tp, bool val) { tp->is_unused45 = val; }

bool tp_is_unused46_get(Tpp tp) { return tp->is_unused46; }
void tp_is_unused46_set(Tpp tp, bool val) { tp->is_unused46 = val; }

bool tp_is_unused47_get(Tpp tp) { return tp->is_unused47; }
void tp_is_unused47_set(Tpp tp, bool val) { tp->is_unused47 = val; }

bool tp_is_unused48_get(Tpp tp) { return tp->is_unused48; }
void tp_is_unused48_set(Tpp tp, bool val) { tp->is_unused48 = val; }

bool tp_is_unused49_get(Tpp tp) { return tp->is_unused49; }
void tp_is_unused49_set(Tpp tp, bool val) { tp->is_unused49 = val; }

bool tp_is_unused50_get(Tpp tp) { return tp->is_unused50; }
void tp_is_unused50_set(Tpp tp, bool val) { tp->is_unused50 = val; }

bool tp_is_unused51_get(Tpp tp) { return tp->is_unused51; }
void tp_is_unused51_set(Tpp tp, bool val) { tp->is_unused51 = val; }

bool tp_is_unused52_get(Tpp tp) { return tp->is_unused52; }
void tp_is_unused52_set(Tpp tp, bool val) { tp->is_unused52 = val; }

bool tp_is_unused53_get(Tpp tp) { return tp->is_unused53; }
void tp_is_unused53_set(Tpp tp, bool val) { tp->is_unused53 = val; }

bool tp_is_unused54_get(Tpp tp) { return tp->is_unused54; }
void tp_is_unused54_set(Tpp tp, bool val) { tp->is_unused54 = val; }

bool tp_is_unused55_get(Tpp tp) { return tp->is_unused55; }
void tp_is_unused55_set(Tpp tp, bool val) { tp->is_unused55 = val; }

bool tp_is_unused56_get(Tpp tp) { return tp->is_unused56; }
void tp_is_unused56_set(Tpp tp, bool val) { tp->is_unused56 = val; }

bool tp_is_unused57_get(Tpp tp) { return tp->is_unused57; }
void tp_is_unused57_set(Tpp tp, bool val) { tp->is_unused57 = val; }

bool tp_is_unused58_get(Tpp tp) { return tp->is_unused58; }
void tp_is_unused58_set(Tpp tp, bool val) { tp->is_unused58 = val; }

bool tp_is_unused59_get(Tpp tp) { return tp->is_unused59; }
void tp_is_unused59_set(Tpp tp, bool val) { tp->is_unused59 = val; }

bool tp_is_unused60_get(Tpp tp) { return tp->is_unused60; }
void tp_is_unused60_set(Tpp tp, bool val) { tp->is_unused60 = val; }

bool tp_is_unused61_get(Tpp tp) { return tp->is_unused61; }
void tp_is_unused61_set(Tpp tp, bool val) { tp->is_unused61 = val; }

bool tp_is_unused62_get(Tpp tp) { return tp->is_unused62; }
void tp_is_unused62_set(Tpp tp, bool val) { tp->is_unused62 = val; }

bool tp_is_unused63_get(Tpp tp) { return tp->is_unused63; }
void tp_is_unused63_set(Tpp tp, bool val) { tp->is_unused63 = val; }

bool tp_is_unused64_get(Tpp tp) { return tp->is_unused64; }
void tp_is_unused64_set(Tpp tp, bool val) { tp->is_unused64 = val; }

bool tp_is_unused65_get(Tpp tp) { return tp->is_unused65; }
void tp_is_unused65_set(Tpp tp, bool val) { tp->is_unused65 = val; }

bool tp_is_unused66_get(Tpp tp) { return tp->is_unused66; }
void tp_is_unused66_set(Tpp tp, bool val) { tp->is_unused66 = val; }

bool tp_is_unused67_get(Tpp tp) { return tp->is_unused67; }
void tp_is_unused67_set(Tpp tp, bool val) { tp->is_unused67 = val; }

bool tp_is_unused68_get(Tpp tp) { return tp->is_unused68; }
void tp_is_unused68_set(Tpp tp, bool val) { tp->is_unused68 = val; }

bool tp_is_unused69_get(Tpp tp) { return tp->is_unused69; }
void tp_is_unused69_set(Tpp tp, bool val) { tp->is_unused69 = val; }

bool tp_is_unused70_get(Tpp tp) { return tp->is_unused70; }
void tp_is_unused70_set(Tpp tp, bool val) { tp->is_unused70 = val; }

bool tp_is_unused71_get(Tpp tp) { return tp->is_unused71; }
void tp_is_unused71_set(Tpp tp, bool val) { tp->is_unused71 = val; }

bool tp_is_unused72_get(Tpp tp) { return tp->is_unused72; }
void tp_is_unused72_set(Tpp tp, bool val) { tp->is_unused72 = val; }

bool tp_is_unused73_get(Tpp tp) { return tp->is_unused73; }
void tp_is_unused73_set(Tpp tp, bool val) { tp->is_unused73 = val; }

bool tp_is_unused74_get(Tpp tp) { return tp->is_unused74; }
void tp_is_unused74_set(Tpp tp, bool val) { tp->is_unused74 = val; }

bool tp_is_unused75_get(Tpp tp) { return tp->is_unused75; }
void tp_is_unused75_set(Tpp tp, bool val) { tp->is_unused75 = val; }

bool tp_is_unused76_get(Tpp tp) { return tp->is_unused76; }
void tp_is_unused76_set(Tpp tp, bool val) { tp->is_unused76 = val; }

bool tp_is_unused77_get(Tpp tp) { return tp->is_unused77; }
void tp_is_unused77_set(Tpp tp, bool val) { tp->is_unused77 = val; }

bool tp_is_unused78_get(Tpp tp) { return tp->is_unused78; }
void tp_is_unused78_set(Tpp tp, bool val) { tp->is_unused78 = val; }

bool tp_is_unused79_get(Tpp tp) { return tp->is_unused79; }
void tp_is_unused79_set(Tpp tp, bool val) { tp->is_unused79 = val; }

bool tp_is_unused80_get(Tpp tp) { return tp->is_unused80; }
void tp_is_unused80_set(Tpp tp, bool val) { tp->is_unused80 = val; }

bool tp_is_unused81_get(Tpp tp) { return tp->is_unused81; }
void tp_is_unused81_set(Tpp tp, bool val) { tp->is_unused81 = val; }

bool tp_is_unused82_get(Tpp tp) { return tp->is_unused82; }
void tp_is_unused82_set(Tpp tp, bool val) { tp->is_unused82 = val; }

bool tp_is_unused83_get(Tpp tp) { return tp->is_unused83; }
void tp_is_unused83_set(Tpp tp, bool val) { tp->is_unused83 = val; }

bool tp_is_unused84_get(Tpp tp) { return tp->is_unused84; }
void tp_is_unused84_set(Tpp tp, bool val) { tp->is_unused84 = val; }

bool tp_is_unused85_get(Tpp tp) { return tp->is_unused85; }
void tp_is_unused85_set(Tpp tp, bool val) { tp->is_unused85 = val; }

bool tp_is_unused86_get(Tpp tp) { return tp->is_unused86; }
void tp_is_unused86_set(Tpp tp, bool val) { tp->is_unused86 = val; }

bool tp_is_unused87_get(Tpp tp) { return tp->is_unused87; }
void tp_is_unused87_set(Tpp tp, bool val) { tp->is_unused87 = val; }

bool tp_is_unused88_get(Tpp tp) { return tp->is_unused88; }
void tp_is_unused88_set(Tpp tp, bool val) { tp->is_unused88 = val; }

bool tp_is_unused89_get(Tpp tp) { return tp->is_unused89; }
void tp_is_unused89_set(Tpp tp, bool val) { tp->is_unused89 = val; }

bool tp_is_unused90_get(Tpp tp) { return tp->is_unused90; }
void tp_is_unused90_set(Tpp tp, bool val) { tp->is_unused90 = val; }

bool tp_is_unused91_get(Tpp tp) { return tp->is_unused91; }
void tp_is_unused91_set(Tpp tp, bool val) { tp->is_unused91 = val; }

bool tp_is_unused92_get(Tpp tp) { return tp->is_unused92; }
void tp_is_unused92_set(Tpp tp, bool val) { tp->is_unused92 = val; }

bool tp_is_unused93_get(Tpp tp) { return tp->is_unused93; }
void tp_is_unused93_set(Tpp tp, bool val) { tp->is_unused93 = val; }

bool tp_is_unused94_get(Tpp tp) { return tp->is_unused94; }
void tp_is_unused94_set(Tpp tp, bool val) { tp->is_unused94 = val; }

bool tp_is_unused95_get(Tpp tp) { return tp->is_unused95; }
void tp_is_unused95_set(Tpp tp, bool val) { tp->is_unused95 = val; }

bool tp_is_unused96_get(Tpp tp) { return tp->is_unused96; }
void tp_is_unused96_set(Tpp tp, bool val) { tp->is_unused96 = val; }

bool tp_is_unused97_get(Tpp tp) { return tp->is_unused97; }
void tp_is_unused97_set(Tpp tp, bool val) { tp->is_unused97 = val; }

bool tp_is_unused98_get(Tpp tp) { return tp->is_unused98; }
void tp_is_unused98_set(Tpp tp, bool val) { tp->is_unused98 = val; }

bool tp_is_unused99_get(Tpp tp) { return tp->is_unused99; }
void tp_is_unused99_set(Tpp tp, bool val) { tp->is_unused99 = val; }

bool tp_is_unused100_get(Tpp tp) { return tp->is_unused100; }
void tp_is_unused100_set(Tpp tp, bool val) { tp->is_unused100 = val; }

bool tp_is_unused101_get(Tpp tp) { return tp->is_unused101; }
void tp_is_unused101_set(Tpp tp, bool val) { tp->is_unused101 = val; }

bool tp_is_unused102_get(Tpp tp) { return tp->is_unused102; }
void tp_is_unused102_set(Tpp tp, bool val) { tp->is_unused102 = val; }

bool tp_is_unused103_get(Tpp tp) { return tp->is_unused103; }
void tp_is_unused103_set(Tpp tp, bool val) { tp->is_unused103 = val; }

bool tp_is_unused104_get(Tpp tp) { return tp->is_unused104; }
void tp_is_unused104_set(Tpp tp, bool val) { tp->is_unused104 = val; }

bool tp_is_unused105_get(Tpp tp) { return tp->is_unused105; }
void tp_is_unused105_set(Tpp tp, bool val) { tp->is_unused105 = val; }

bool tp_is_unused106_get(Tpp tp) { return tp->is_unused106; }
void tp_is_unused106_set(Tpp tp, bool val) { tp->is_unused106 = val; }

bool tp_is_unused107_get(Tpp tp) { return tp->is_unused107; }
void tp_is_unused107_set(Tpp tp, bool val) { tp->is_unused107 = val; }

bool tp_is_unused108_get(Tpp tp) { return tp->is_unused108; }
void tp_is_unused108_set(Tpp tp, bool val) { tp->is_unused108 = val; }

bool tp_is_unused109_get(Tpp tp) { return tp->is_unused109; }
void tp_is_unused109_set(Tpp tp, bool val) { tp->is_unused109 = val; }

bool tp_is_unused110_get(Tpp tp) { return tp->is_unused110; }
void tp_is_unused110_set(Tpp tp, bool val) { tp->is_unused110 = val; }

bool tp_is_unused111_get(Tpp tp) { return tp->is_unused111; }
void tp_is_unused111_set(Tpp tp, bool val) { tp->is_unused111 = val; }

bool tp_is_unused112_get(Tpp tp) { return tp->is_unused112; }
void tp_is_unused112_set(Tpp tp, bool val) { tp->is_unused112 = val; }

bool tp_is_unused113_get(Tpp tp) { return tp->is_unused113; }
void tp_is_unused113_set(Tpp tp, bool val) { tp->is_unused113 = val; }

bool tp_is_unused114_get(Tpp tp) { return tp->is_unused114; }
void tp_is_unused114_set(Tpp tp, bool val) { tp->is_unused114 = val; }

bool tp_is_unused115_get(Tpp tp) { return tp->is_unused115; }
void tp_is_unused115_set(Tpp tp, bool val) { tp->is_unused115 = val; }

bool tp_is_unused116_get(Tpp tp) { return tp->is_unused116; }
void tp_is_unused116_set(Tpp tp, bool val) { tp->is_unused116 = val; }

bool tp_is_unused117_get(Tpp tp) { return tp->is_unused117; }
void tp_is_unused117_set(Tpp tp, bool val) { tp->is_unused117 = val; }

bool tp_is_unused118_get(Tpp tp) { return tp->is_unused118; }
void tp_is_unused118_set(Tpp tp, bool val) { tp->is_unused118 = val; }

bool tp_is_unused119_get(Tpp tp) { return tp->is_unused119; }
void tp_is_unused119_set(Tpp tp, bool val) { tp->is_unused119 = val; }

bool tp_is_unused120_get(Tpp tp) { return tp->is_unused120; }
void tp_is_unused120_set(Tpp tp, bool val) { tp->is_unused120 = val; }

bool tp_is_unused121_get(Tpp tp) { return tp->is_unused121; }
void tp_is_unused121_set(Tpp tp, bool val) { tp->is_unused121 = val; }

bool tp_is_unused122_get(Tpp tp) { return tp->is_unused122; }
void tp_is_unused122_set(Tpp tp, bool val) { tp->is_unused122 = val; }

bool tp_is_unused123_get(Tpp tp) { return tp->is_unused123; }
void tp_is_unused123_set(Tpp tp, bool val) { tp->is_unused123 = val; }

bool tp_is_unused124_get(Tpp tp) { return tp->is_unused124; }
void tp_is_unused124_set(Tpp tp, bool val) { tp->is_unused124 = val; }

bool tp_is_unused125_get(Tpp tp) { return tp->is_unused125; }
void tp_is_unused125_set(Tpp tp, bool val) { tp->is_unused125 = val; }

bool tp_is_unused126_get(Tpp tp) { return tp->is_unused126; }
void tp_is_unused126_set(Tpp tp, bool val) { tp->is_unused126 = val; }

bool tp_is_unused127_get(Tpp tp) { return tp->is_unused127; }
void tp_is_unused127_set(Tpp tp, bool val) { tp->is_unused127 = val; }

bool tp_is_unused128_get(Tpp tp) { return tp->is_unused128; }
void tp_is_unused128_set(Tpp tp, bool val) { tp->is_unused128 = val; }

bool tp_is_unused129_get(Tpp tp) { return tp->is_unused129; }
void tp_is_unused129_set(Tpp tp, bool val) { tp->is_unused129 = val; }

bool tp_is_unused130_get(Tpp tp) { return tp->is_unused130; }
void tp_is_unused130_set(Tpp tp, bool val) { tp->is_unused130 = val; }

bool tp_is_unused131_get(Tpp tp) { return tp->is_unused131; }
void tp_is_unused131_set(Tpp tp, bool val) { tp->is_unused131 = val; }

bool tp_is_unused132_get(Tpp tp) { return tp->is_unused132; }
void tp_is_unused132_set(Tpp tp, bool val) { tp->is_unused132 = val; }

bool tp_is_unused133_get(Tpp tp) { return tp->is_unused133; }
void tp_is_unused133_set(Tpp tp, bool val) { tp->is_unused133 = val; }

bool tp_is_unused134_get(Tpp tp) { return tp->is_unused134; }
void tp_is_unused134_set(Tpp tp, bool val) { tp->is_unused134 = val; }

bool tp_is_unused135_get(Tpp tp) { return tp->is_unused135; }
void tp_is_unused135_set(Tpp tp, bool val) { tp->is_unused135 = val; }

bool tp_is_unused136_get(Tpp tp) { return tp->is_unused136; }
void tp_is_unused136_set(Tpp tp, bool val) { tp->is_unused136 = val; }

bool tp_is_unused137_get(Tpp tp) { return tp->is_unused137; }
void tp_is_unused137_set(Tpp tp, bool val) { tp->is_unused137 = val; }

bool tp_is_unused138_get(Tpp tp) { return tp->is_unused138; }
void tp_is_unused138_set(Tpp tp, bool val) { tp->is_unused138 = val; }

bool tp_is_unused139_get(Tpp tp) { return tp->is_unused139; }
void tp_is_unused139_set(Tpp tp, bool val) { tp->is_unused139 = val; }

bool tp_is_unused140_get(Tpp tp) { return tp->is_unused140; }
void tp_is_unused140_set(Tpp tp, bool val) { tp->is_unused140 = val; }

bool tp_is_unused141_get(Tpp tp) { return tp->is_unused141; }
void tp_is_unused141_set(Tpp tp, bool val) { tp->is_unused141 = val; }

bool tp_is_unused142_get(Tpp tp) { return tp->is_unused142; }
void tp_is_unused142_set(Tpp tp, bool val) { tp->is_unused142 = val; }

bool tp_is_unused143_get(Tpp tp) { return tp->is_unused143; }
void tp_is_unused143_set(Tpp tp, bool val) { tp->is_unused143 = val; }

bool tp_is_unused144_get(Tpp tp) { return tp->is_unused144; }
void tp_is_unused144_set(Tpp tp, bool val) { tp->is_unused144 = val; }

bool tp_is_unused145_get(Tpp tp) { return tp->is_unused145; }
void tp_is_unused145_set(Tpp tp, bool val) { tp->is_unused145 = val; }

bool tp_is_unused146_get(Tpp tp) { return tp->is_unused146; }
void tp_is_unused146_set(Tpp tp, bool val) { tp->is_unused146 = val; }

bool tp_is_unused147_get(Tpp tp) { return tp->is_unused147; }
void tp_is_unused147_set(Tpp tp, bool val) { tp->is_unused147 = val; }

bool tp_is_unused148_get(Tpp tp) { return tp->is_unused148; }
void tp_is_unused148_set(Tpp tp, bool val) { tp->is_unused148 = val; }

bool tp_is_unused149_get(Tpp tp) { return tp->is_unused149; }
void tp_is_unused149_set(Tpp tp, bool val) { tp->is_unused149 = val; }

bool tp_is_unused150_get(Tpp tp) { return tp->is_unused150; }
void tp_is_unused150_set(Tpp tp, bool val) { tp->is_unused150 = val; }

bool tp_is_unused151_get(Tpp tp) { return tp->is_unused151; }
void tp_is_unused151_set(Tpp tp, bool val) { tp->is_unused151 = val; }

bool tp_is_unused152_get(Tpp tp) { return tp->is_unused152; }
void tp_is_unused152_set(Tpp tp, bool val) { tp->is_unused152 = val; }

bool tp_is_unused153_get(Tpp tp) { return tp->is_unused153; }
void tp_is_unused153_set(Tpp tp, bool val) { tp->is_unused153 = val; }

bool tp_is_unused154_get(Tpp tp) { return tp->is_unused154; }
void tp_is_unused154_set(Tpp tp, bool val) { tp->is_unused154 = val; }

bool tp_is_unused155_get(Tpp tp) { return tp->is_unused155; }
void tp_is_unused155_set(Tpp tp, bool val) { tp->is_unused155 = val; }

bool tp_is_unused156_get(Tpp tp) { return tp->is_unused156; }
void tp_is_unused156_set(Tpp tp, bool val) { tp->is_unused156 = val; }

bool tp_is_unused157_get(Tpp tp) { return tp->is_unused157; }
void tp_is_unused157_set(Tpp tp, bool val) { tp->is_unused157 = val; }

bool tp_is_unused158_get(Tpp tp) { return tp->is_unused158; }
void tp_is_unused158_set(Tpp tp, bool val) { tp->is_unused158 = val; }

bool tp_is_unused159_get(Tpp tp) { return tp->is_unused159; }
void tp_is_unused159_set(Tpp tp, bool val) { tp->is_unused159 = val; }

bool tp_is_unused160_get(Tpp tp) { return tp->is_unused160; }
void tp_is_unused160_set(Tpp tp, bool val) { tp->is_unused160 = val; }

bool tp_is_unused161_get(Tpp tp) { return tp->is_unused161; }
void tp_is_unused161_set(Tpp tp, bool val) { tp->is_unused161 = val; }

bool tp_is_unused162_get(Tpp tp) { return tp->is_unused162; }
void tp_is_unused162_set(Tpp tp, bool val) { tp->is_unused162 = val; }

bool tp_is_unused163_get(Tpp tp) { return tp->is_unused163; }
void tp_is_unused163_set(Tpp tp, bool val) { tp->is_unused163 = val; }

bool tp_is_unused164_get(Tpp tp) { return tp->is_unused164; }
void tp_is_unused164_set(Tpp tp, bool val) { tp->is_unused164 = val; }

bool tp_is_unused165_get(Tpp tp) { return tp->is_unused165; }
void tp_is_unused165_set(Tpp tp, bool val) { tp->is_unused165 = val; }

bool tp_is_unused166_get(Tpp tp) { return tp->is_unused166; }
void tp_is_unused166_set(Tpp tp, bool val) { tp->is_unused166 = val; }

bool tp_is_unused167_get(Tpp tp) { return tp->is_unused167; }
void tp_is_unused167_set(Tpp tp, bool val) { tp->is_unused167 = val; }

bool tp_is_unused168_get(Tpp tp) { return tp->is_unused168; }
void tp_is_unused168_set(Tpp tp, bool val) { tp->is_unused168 = val; }

bool tp_is_unused169_get(Tpp tp) { return tp->is_unused169; }
void tp_is_unused169_set(Tpp tp, bool val) { tp->is_unused169 = val; }

bool tp_is_unused170_get(Tpp tp) { return tp->is_unused170; }
void tp_is_unused170_set(Tpp tp, bool val) { tp->is_unused170 = val; }

bool tp_is_unused171_get(Tpp tp) { return tp->is_unused171; }
void tp_is_unused171_set(Tpp tp, bool val) { tp->is_unused171 = val; }

bool tp_is_unused172_get(Tpp tp) { return tp->is_unused172; }
void tp_is_unused172_set(Tpp tp, bool val) { tp->is_unused172 = val; }

bool tp_is_unused173_get(Tpp tp) { return tp->is_unused173; }
void tp_is_unused173_set(Tpp tp, bool val) { tp->is_unused173 = val; }

bool tp_is_unused174_get(Tpp tp) { return tp->is_unused174; }
void tp_is_unused174_set(Tpp tp, bool val) { tp->is_unused174 = val; }

bool tp_is_unused175_get(Tpp tp) { return tp->is_unused175; }
void tp_is_unused175_set(Tpp tp, bool val) { tp->is_unused175 = val; }

bool tp_is_unused176_get(Tpp tp) { return tp->is_unused176; }
void tp_is_unused176_set(Tpp tp, bool val) { tp->is_unused176 = val; }

bool tp_is_unused177_get(Tpp tp) { return tp->is_unused177; }
void tp_is_unused177_set(Tpp tp, bool val) { tp->is_unused177 = val; }

bool tp_is_unused178_get(Tpp tp) { return tp->is_unused178; }
void tp_is_unused178_set(Tpp tp, bool val) { tp->is_unused178 = val; }

bool tp_is_unused179_get(Tpp tp) { return tp->is_unused179; }
void tp_is_unused179_set(Tpp tp, bool val) { tp->is_unused179 = val; }

bool tp_is_unused180_get(Tpp tp) { return tp->is_unused180; }
void tp_is_unused180_set(Tpp tp, bool val) { tp->is_unused180 = val; }

bool tp_is_unused181_get(Tpp tp) { return tp->is_unused181; }
void tp_is_unused181_set(Tpp tp, bool val) { tp->is_unused181 = val; }

bool tp_is_unused182_get(Tpp tp) { return tp->is_unused182; }
void tp_is_unused182_set(Tpp tp, bool val) { tp->is_unused182 = val; }

bool tp_is_unused183_get(Tpp tp) { return tp->is_unused183; }
void tp_is_unused183_set(Tpp tp, bool val) { tp->is_unused183 = val; }

bool tp_is_unused184_get(Tpp tp) { return tp->is_unused184; }
void tp_is_unused184_set(Tpp tp, bool val) { tp->is_unused184 = val; }

bool tp_is_unused185_get(Tpp tp) { return tp->is_unused185; }
void tp_is_unused185_set(Tpp tp, bool val) { tp->is_unused185 = val; }

bool tp_is_unused186_get(Tpp tp) { return tp->is_unused186; }
void tp_is_unused186_set(Tpp tp, bool val) { tp->is_unused186 = val; }

bool tp_is_unused187_get(Tpp tp) { return tp->is_unused187; }
void tp_is_unused187_set(Tpp tp, bool val) { tp->is_unused187 = val; }

bool tp_is_unused188_get(Tpp tp) { return tp->is_unused188; }
void tp_is_unused188_set(Tpp tp, bool val) { tp->is_unused188 = val; }

bool tp_is_unused189_get(Tpp tp) { return tp->is_unused189; }
void tp_is_unused189_set(Tpp tp, bool val) { tp->is_unused189 = val; }

bool tp_is_unused190_get(Tpp tp) { return tp->is_unused190; }
void tp_is_unused190_set(Tpp tp, bool val) { tp->is_unused190 = val; }

bool tp_is_unused191_get(Tpp tp) { return tp->is_unused191; }
void tp_is_unused191_set(Tpp tp, bool val) { tp->is_unused191 = val; }

bool tp_is_unused192_get(Tpp tp) { return tp->is_unused192; }
void tp_is_unused192_set(Tpp tp, bool val) { tp->is_unused192 = val; }

bool tp_is_unused193_get(Tpp tp) { return tp->is_unused193; }
void tp_is_unused193_set(Tpp tp, bool val) { tp->is_unused193 = val; }

bool tp_is_unused194_get(Tpp tp) { return tp->is_unused194; }
void tp_is_unused194_set(Tpp tp, bool val) { tp->is_unused194 = val; }

bool tp_is_unused195_get(Tpp tp) { return tp->is_unused195; }
void tp_is_unused195_set(Tpp tp, bool val) { tp->is_unused195 = val; }

bool tp_is_unused196_get(Tpp tp) { return tp->is_unused196; }
void tp_is_unused196_set(Tpp tp, bool val) { tp->is_unused196 = val; }

bool tp_is_unused197_get(Tpp tp) { return tp->is_unused197; }
void tp_is_unused197_set(Tpp tp, bool val) { tp->is_unused197 = val; }

bool tp_is_unused198_get(Tpp tp) { return tp->is_unused198; }
void tp_is_unused198_set(Tpp tp, bool val) { tp->is_unused198 = val; }

bool tp_is_cursor_at_get(Tpp tp) { return tp->is_cursor_at; }
void tp_is_cursor_at_set(Tpp tp, bool val) { tp->is_cursor_at = val; }

bool tp_is_cursor_path_get(Tpp tp) { return tp->is_cursor_path; }
void tp_is_cursor_path_set(Tpp tp, bool val) { tp->is_cursor_path = val; }

bool tp_is_key_get(Tpp tp) { return tp->is_key; }
void tp_is_key_set(Tpp tp, bool val) { tp->is_key = val; }

bool tp_is_monst_get(Tpp tp) { return tp->is_monst; }
void tp_is_monst_set(Tpp tp, bool val) { tp->is_monst = val; }

bool tp_is_monst_class_get(Tpp tp, int val) { return tp->is_monst_class[ val ]; }
void tp_is_monst_class_set(Tpp tp, bool val) { tp->is_monst_class[ val ] = true; }

bool tp_is_obs_monst_get(Tpp tp) { return tp->is_obs_monst; }
void tp_is_obs_monst_set(Tpp tp, bool val) { tp->is_obs_monst = val; }

bool tp_is_obs_player_get(Tpp tp) { return tp->is_obs_player; }
void tp_is_obs_player_set(Tpp tp, bool val) { tp->is_obs_player = val; }

bool tp_is_player_get(Tpp tp) { return tp->is_player; }
void tp_is_player_set(Tpp tp, bool val) { tp->is_player = val; }

bool tp_is_wall_get(Tpp tp) { return tp->is_wall; }
void tp_is_wall_set(Tpp tp, bool val) { tp->is_wall = val; }

uint8_t tp_player_index_get(Tpp tp) { return tp->player_index; };
void    tp_player_index_set(Tpp tp, uint8_t val) { tp->player_index = val; };

void    tp_z_depth_set(Tpp tp, uint8_t val) { tp->z_depth = val; };
uint8_t tp_z_depth_get(Tpp tp) { return tp->z_depth; };

void tp_speed_set(Tpp tp, int val) { tp->speed = val; };
int  tp_speed_get(Tpp tp) { return tp->speed; };
