//
// Copyright Neil McGill, goblinhack@gmail.com
//

#pragma once
#ifndef _MY_THING_TEMPLATE_H_
#define _MY_THING_TEMPLATE_H_

#include "my_minimal.hpp"

#include <stdarg.h>

class Tp;

enum {
  MAP_DEPTH_FLOOR,
  MAP_DEPTH_WALL,
  MAP_DEPTH_DOOR,
  MAP_DEPTH_OBJ1,
  MAP_DEPTH_OBJ2,
  MAP_DEPTH_PLAYER,
  MAP_DEPTH_CURSOR,
};

enum {
  THING_RARITY_COMMON,
  THING_RARITY_UNCOMMON,
  THING_RARITY_RARE,
  THING_RARITY_VERY_RARE,
  THING_RARITY_UNIQUE,
};

enum { MONST_CLASS_A, MONST_CLASS_MAX };

bool tp_init(void);

const char *tp_name(Tpp);
const char *text_a_or_an(Tpp);
const char *text_long_capitalised(Tpp);
const char *text_short_capitalised(Tpp);
const char *to_short_string(Tpp);
const char *to_string(Tpp);

int   tp_tiles_size(Tpp tp);
Tilep tp_first_tile(class Tp *);
Tilep tp_tiles_get(Tpp tp, int index);
void  tp_tiles_push_back(Tpp tp, Tilep val);

TpId tp_id_get(Tpp tp);
Tpp  tp_find(TpId id);

Tpp string2tp(const char **s);
Tpp string2tp(const char **s, int *len);
Tpp tp_find(const char *);
Tpp tp_load(const char *);
Tpp tp_random_dungeon_entrance(void);
Tpp tp_random_exit(void);
Tpp tp_random_key(void);
Tpp tp_random_monst(int c);
Tpp tp_random_player(void);
Tpp tp_random_wall(void);
Tpp tp_random_unused1(void);
Tpp tp_random_unused2(void);
Tpp tp_random_unused3(void);
Tpp tp_random_unused4(void);
Tpp tp_random_unused5(void);
Tpp tp_random_unused6(void);
Tpp tp_random_unused7(void);
Tpp tp_random_unused8(void);
Tpp tp_random_unused9(void);
Tpp tp_random_unused10(void);
Tpp tp_random_unused11(void);
Tpp tp_random_unused12(void);
Tpp tp_random_unused13(void);
Tpp tp_random_unused14(void);
Tpp tp_random_unused15(void);
Tpp tp_random_unused16(void);
Tpp tp_random_unused17(void);
Tpp tp_random_unused18(void);
Tpp tp_random_unused19(void);
Tpp tp_random_unused20(void);
Tpp tp_random_unused21(void);
Tpp tp_random_unused22(void);
Tpp tp_random_unused23(void);
Tpp tp_random_unused24(void);
Tpp tp_random_unused25(void);
Tpp tp_random_unused26(void);
Tpp tp_random_unused27(void);
Tpp tp_random_unused28(void);
Tpp tp_random_unused29(void);
Tpp tp_random_unused30(void);
Tpp tp_random_unused31(void);
Tpp tp_random_unused32(void);
Tpp tp_random_unused33(void);
Tpp tp_random_unused34(void);
Tpp tp_random_unused35(void);
Tpp tp_random_unused36(void);
Tpp tp_random_unused37(void);
Tpp tp_random_unused38(void);
Tpp tp_random_unused39(void);
Tpp tp_random_unused40(void);
Tpp tp_random_unused41(void);
Tpp tp_random_unused42(void);
Tpp tp_random_unused43(void);
Tpp tp_random_unused44(void);
Tpp tp_random_unused45(void);
Tpp tp_random_unused46(void);
Tpp tp_random_unused47(void);
Tpp tp_random_unused48(void);
Tpp tp_random_unused49(void);
Tpp tp_random_unused50(void);
Tpp tp_random_unused51(void);
Tpp tp_random_unused52(void);
Tpp tp_random_unused53(void);
Tpp tp_random_unused54(void);
Tpp tp_random_unused55(void);
Tpp tp_random_unused56(void);
Tpp tp_random_unused57(void);
Tpp tp_random_unused58(void);
Tpp tp_random_unused59(void);
Tpp tp_random_unused60(void);
Tpp tp_random_unused61(void);
Tpp tp_random_unused62(void);
Tpp tp_random_unused63(void);
Tpp tp_random_unused64(void);
Tpp tp_random_unused65(void);
Tpp tp_random_unused66(void);
Tpp tp_random_unused67(void);
Tpp tp_random_unused68(void);
Tpp tp_random_unused69(void);
Tpp tp_random_unused70(void);
Tpp tp_random_unused71(void);
Tpp tp_random_unused72(void);
Tpp tp_random_unused73(void);
Tpp tp_random_unused74(void);
Tpp tp_random_unused75(void);
Tpp tp_random_unused76(void);
Tpp tp_random_unused77(void);
Tpp tp_random_unused78(void);
Tpp tp_random_unused79(void);
Tpp tp_random_unused80(void);
Tpp tp_random_unused81(void);
Tpp tp_random_unused82(void);
Tpp tp_random_unused83(void);
Tpp tp_random_unused84(void);
Tpp tp_random_unused85(void);
Tpp tp_random_unused86(void);
Tpp tp_random_unused87(void);
Tpp tp_random_unused88(void);
Tpp tp_random_unused89(void);
Tpp tp_random_unused90(void);
Tpp tp_random_unused91(void);
Tpp tp_random_unused92(void);
Tpp tp_random_unused93(void);
Tpp tp_random_unused94(void);
Tpp tp_random_unused95(void);
Tpp tp_random_unused96(void);
Tpp tp_random_unused97(void);
Tpp tp_random_unused98(void);
Tpp tp_random_unused99(void);
Tpp tp_random_unused100(void);
Tpp tp_random_unused101(void);
Tpp tp_random_unused102(void);
Tpp tp_random_unused103(void);
Tpp tp_random_unused104(void);
Tpp tp_random_unused105(void);
Tpp tp_random_unused106(void);
Tpp tp_random_unused107(void);
Tpp tp_random_unused108(void);
Tpp tp_random_unused109(void);
Tpp tp_random_unused110(void);
Tpp tp_random_unused111(void);
Tpp tp_random_unused112(void);
Tpp tp_random_unused113(void);
Tpp tp_random_unused114(void);
Tpp tp_random_unused115(void);
Tpp tp_random_unused116(void);
Tpp tp_random_unused117(void);
Tpp tp_random_unused118(void);
Tpp tp_random_unused119(void);
Tpp tp_random_unused120(void);
Tpp tp_random_unused121(void);
Tpp tp_random_unused122(void);
Tpp tp_random_unused123(void);
Tpp tp_random_unused124(void);
Tpp tp_random_unused125(void);
Tpp tp_random_unused126(void);
Tpp tp_random_unused127(void);
Tpp tp_random_unused128(void);
Tpp tp_random_unused129(void);
Tpp tp_random_unused130(void);
Tpp tp_random_unused131(void);
Tpp tp_random_unused132(void);
Tpp tp_random_unused133(void);
Tpp tp_random_unused134(void);
Tpp tp_random_unused135(void);
Tpp tp_random_unused136(void);
Tpp tp_random_unused137(void);
Tpp tp_random_unused138(void);
Tpp tp_random_unused139(void);
Tpp tp_random_unused140(void);
Tpp tp_random_unused141(void);
Tpp tp_random_unused142(void);
Tpp tp_random_unused143(void);
Tpp tp_random_unused144(void);
Tpp tp_random_unused145(void);
Tpp tp_random_unused146(void);
Tpp tp_random_unused147(void);
Tpp tp_random_unused148(void);
Tpp tp_random_unused149(void);
Tpp tp_random_unused150(void);
Tpp tp_random_unused151(void);
Tpp tp_random_unused152(void);
Tpp tp_random_unused153(void);
Tpp tp_random_unused154(void);
Tpp tp_random_unused155(void);
Tpp tp_random_unused156(void);
Tpp tp_random_unused157(void);
Tpp tp_random_unused158(void);
Tpp tp_random_unused159(void);
Tpp tp_random_unused160(void);
Tpp tp_random_unused161(void);
Tpp tp_random_unused162(void);
Tpp tp_random_unused163(void);
Tpp tp_random_unused164(void);
Tpp tp_random_unused165(void);
Tpp tp_random_unused166(void);
Tpp tp_random_unused167(void);
Tpp tp_random_unused168(void);
Tpp tp_random_unused169(void);
Tpp tp_random_unused170(void);
Tpp tp_random_unused171(void);
Tpp tp_random_unused172(void);
Tpp tp_random_unused173(void);
Tpp tp_random_unused174(void);
Tpp tp_random_unused175(void);
Tpp tp_random_unused176(void);
Tpp tp_random_unused177(void);
Tpp tp_random_unused178(void);
Tpp tp_random_unused179(void);
Tpp tp_random_unused180(void);
Tpp tp_random_unused181(void);
Tpp tp_random_unused182(void);
Tpp tp_random_unused183(void);
Tpp tp_random_unused184(void);
Tpp tp_random_unused185(void);
Tpp tp_random_unused186(void);
Tpp tp_random_unused187(void);
Tpp tp_random_unused188(void);
Tpp tp_random_unused189(void);
Tpp tp_random_unused190(void);
Tpp tp_random_unused191(void);
Tpp tp_random_unused192(void);
Tpp tp_random_unused193(void);
Tpp tp_random_unused194(void);
Tpp tp_random_unused195(void);
Tpp tp_random_unused196(void);
Tpp tp_random_unused197(void);
Tpp tp_random_unused198(void);

void con(Tpp, const char *fmt, ...) CHECK_FORMAT_STR(printf, 2, 3);
void con_(Tpp, const char *fmt, va_list args); // compile error without
void dbg_(Tpp, const char *fmt, ...) CHECK_FORMAT_STR(printf, 2, 3);
void die(Tpp, const char *fmt, ...) CHECK_FORMAT_STR(printf, 2, 3);
void die_(Tpp, const char *fmt, va_list args); // compile error without
void err(Tpp, const char *fmt, ...) CHECK_FORMAT_STR(printf, 2, 3);
void err_(Tpp, const char *fmt, va_list args); // compile error without
void log(Tpp, const char *fmt, ...) CHECK_FORMAT_STR(printf, 2, 3);
void log_(Tpp, const char *fmt, va_list args); // compile error without
void tp_fini(void);
void tp_fixup(void);
void tp_get_id(const char *, int *id);
void tp_random_dungeon_init(void);

const char *tp_name(Tpp tp);
const char *to_string(Tpp tp);
const char *to_short_string(Tpp tp);

bool tp_is_animated_can_hflip(Tpp tp);
void tp_is_animated_can_hflip_set(Tpp tp, bool val);

bool tp_is_animated_no_dir(Tpp tp);
void tp_is_animated_no_dir_set(Tpp tp, bool val);

bool tp_is_blit_centered(Tpp tp);
void tp_is_blit_centered_set(Tpp tp, bool val);

bool tp_is_blit_on_ground(Tpp tp);
void tp_is_blit_on_ground_set(Tpp tp, bool val);

bool tp_is_blit_outlined(Tpp tp);
void tp_is_blit_outlined_set(Tpp tp, bool val);

bool tp_is_blit_square_outlined(Tpp tp);
void tp_is_blit_square_outlined_set(Tpp tp, bool val);

bool tp_is_blit_tiled(Tpp tp);
void tp_is_blit_tiled_set(Tpp tp, bool val);

bool tp_is_cursor(Tpp tp);
void tp_is_cursor_set(Tpp tp, bool val);

bool tp_is_door(Tpp tp);
void tp_is_door_set(Tpp tp, bool val);

bool tp_is_dungeon_entrance(Tpp tp);
void tp_is_dungeon_entrance_set(Tpp tp, bool val);

bool tp_is_exit(Tpp tp);
void tp_is_exit_set(Tpp tp, bool val);

bool tp_is_floor(Tpp tp);
void tp_is_floor_set(Tpp tp, bool val);

bool tp_is_unused1(Tpp tp);
void tp_is_unused1_set(Tpp tp, bool val);

bool tp_is_unused2(Tpp tp);
void tp_is_unused2_set(Tpp tp, bool val);

bool tp_is_unused3(Tpp tp);
void tp_is_unused3_set(Tpp tp, bool val);

bool tp_is_unused4(Tpp tp);
void tp_is_unused4_set(Tpp tp, bool val);

bool tp_is_unused5(Tpp tp);
void tp_is_unused5_set(Tpp tp, bool val);

bool tp_is_unused6(Tpp tp);
void tp_is_unused6_set(Tpp tp, bool val);

bool tp_is_unused7(Tpp tp);
void tp_is_unused7_set(Tpp tp, bool val);

bool tp_is_unused8(Tpp tp);
void tp_is_unused8_set(Tpp tp, bool val);

bool tp_is_unused9(Tpp tp);
void tp_is_unused9_set(Tpp tp, bool val);

bool tp_is_unused10(Tpp tp);
void tp_is_unused10_set(Tpp tp, bool val);

bool tp_is_unused11(Tpp tp);
void tp_is_unused11_set(Tpp tp, bool val);

bool tp_is_unused12(Tpp tp);
void tp_is_unused12_set(Tpp tp, bool val);

bool tp_is_unused13(Tpp tp);
void tp_is_unused13_set(Tpp tp, bool val);

bool tp_is_unused14(Tpp tp);
void tp_is_unused14_set(Tpp tp, bool val);

bool tp_is_unused15(Tpp tp);
void tp_is_unused15_set(Tpp tp, bool val);

bool tp_is_unused16(Tpp tp);
void tp_is_unused16_set(Tpp tp, bool val);

bool tp_is_unused17(Tpp tp);
void tp_is_unused17_set(Tpp tp, bool val);

bool tp_is_unused18(Tpp tp);
void tp_is_unused18_set(Tpp tp, bool val);

bool tp_is_unused19(Tpp tp);
void tp_is_unused19_set(Tpp tp, bool val);

bool tp_is_unused20(Tpp tp);
void tp_is_unused20_set(Tpp tp, bool val);

bool tp_is_unused21(Tpp tp);
void tp_is_unused21_set(Tpp tp, bool val);

bool tp_is_unused22(Tpp tp);
void tp_is_unused22_set(Tpp tp, bool val);

bool tp_is_unused23(Tpp tp);
void tp_is_unused23_set(Tpp tp, bool val);

bool tp_is_unused24(Tpp tp);
void tp_is_unused24_set(Tpp tp, bool val);

bool tp_is_unused25(Tpp tp);
void tp_is_unused25_set(Tpp tp, bool val);

bool tp_is_unused26(Tpp tp);
void tp_is_unused26_set(Tpp tp, bool val);

bool tp_is_unused27(Tpp tp);
void tp_is_unused27_set(Tpp tp, bool val);

bool tp_is_unused28(Tpp tp);
void tp_is_unused28_set(Tpp tp, bool val);

bool tp_is_unused29(Tpp tp);
void tp_is_unused29_set(Tpp tp, bool val);

bool tp_is_unused30(Tpp tp);
void tp_is_unused30_set(Tpp tp, bool val);

bool tp_is_unused31(Tpp tp);
void tp_is_unused31_set(Tpp tp, bool val);

bool tp_is_unused32(Tpp tp);
void tp_is_unused32_set(Tpp tp, bool val);

bool tp_is_unused33(Tpp tp);
void tp_is_unused33_set(Tpp tp, bool val);

bool tp_is_unused34(Tpp tp);
void tp_is_unused34_set(Tpp tp, bool val);

bool tp_is_unused35(Tpp tp);
void tp_is_unused35_set(Tpp tp, bool val);

bool tp_is_unused36(Tpp tp);
void tp_is_unused36_set(Tpp tp, bool val);

bool tp_is_unused37(Tpp tp);
void tp_is_unused37_set(Tpp tp, bool val);

bool tp_is_unused38(Tpp tp);
void tp_is_unused38_set(Tpp tp, bool val);

bool tp_is_unused39(Tpp tp);
void tp_is_unused39_set(Tpp tp, bool val);

bool tp_is_unused40(Tpp tp);
void tp_is_unused40_set(Tpp tp, bool val);

bool tp_is_unused41(Tpp tp);
void tp_is_unused41_set(Tpp tp, bool val);

bool tp_is_unused42(Tpp tp);
void tp_is_unused42_set(Tpp tp, bool val);

bool tp_is_unused43(Tpp tp);
void tp_is_unused43_set(Tpp tp, bool val);

bool tp_is_unused44(Tpp tp);
void tp_is_unused44_set(Tpp tp, bool val);

bool tp_is_unused45(Tpp tp);
void tp_is_unused45_set(Tpp tp, bool val);

bool tp_is_unused46(Tpp tp);
void tp_is_unused46_set(Tpp tp, bool val);

bool tp_is_unused47(Tpp tp);
void tp_is_unused47_set(Tpp tp, bool val);

bool tp_is_unused48(Tpp tp);
void tp_is_unused48_set(Tpp tp, bool val);

bool tp_is_unused49(Tpp tp);
void tp_is_unused49_set(Tpp tp, bool val);

bool tp_is_unused50(Tpp tp);
void tp_is_unused50_set(Tpp tp, bool val);

bool tp_is_unused51(Tpp tp);
void tp_is_unused51_set(Tpp tp, bool val);

bool tp_is_unused52(Tpp tp);
void tp_is_unused52_set(Tpp tp, bool val);

bool tp_is_unused53(Tpp tp);
void tp_is_unused53_set(Tpp tp, bool val);

bool tp_is_unused54(Tpp tp);
void tp_is_unused54_set(Tpp tp, bool val);

bool tp_is_unused55(Tpp tp);
void tp_is_unused55_set(Tpp tp, bool val);

bool tp_is_unused56(Tpp tp);
void tp_is_unused56_set(Tpp tp, bool val);

bool tp_is_unused57(Tpp tp);
void tp_is_unused57_set(Tpp tp, bool val);

bool tp_is_unused58(Tpp tp);
void tp_is_unused58_set(Tpp tp, bool val);

bool tp_is_unused59(Tpp tp);
void tp_is_unused59_set(Tpp tp, bool val);

bool tp_is_unused60(Tpp tp);
void tp_is_unused60_set(Tpp tp, bool val);

bool tp_is_unused61(Tpp tp);
void tp_is_unused61_set(Tpp tp, bool val);

bool tp_is_unused62(Tpp tp);
void tp_is_unused62_set(Tpp tp, bool val);

bool tp_is_unused63(Tpp tp);
void tp_is_unused63_set(Tpp tp, bool val);

bool tp_is_unused64(Tpp tp);
void tp_is_unused64_set(Tpp tp, bool val);

bool tp_is_unused65(Tpp tp);
void tp_is_unused65_set(Tpp tp, bool val);

bool tp_is_unused66(Tpp tp);
void tp_is_unused66_set(Tpp tp, bool val);

bool tp_is_unused67(Tpp tp);
void tp_is_unused67_set(Tpp tp, bool val);

bool tp_is_unused68(Tpp tp);
void tp_is_unused68_set(Tpp tp, bool val);

bool tp_is_unused69(Tpp tp);
void tp_is_unused69_set(Tpp tp, bool val);

bool tp_is_unused70(Tpp tp);
void tp_is_unused70_set(Tpp tp, bool val);

bool tp_is_unused71(Tpp tp);
void tp_is_unused71_set(Tpp tp, bool val);

bool tp_is_unused72(Tpp tp);
void tp_is_unused72_set(Tpp tp, bool val);

bool tp_is_unused73(Tpp tp);
void tp_is_unused73_set(Tpp tp, bool val);

bool tp_is_unused74(Tpp tp);
void tp_is_unused74_set(Tpp tp, bool val);

bool tp_is_unused75(Tpp tp);
void tp_is_unused75_set(Tpp tp, bool val);

bool tp_is_unused76(Tpp tp);
void tp_is_unused76_set(Tpp tp, bool val);

bool tp_is_unused77(Tpp tp);
void tp_is_unused77_set(Tpp tp, bool val);

bool tp_is_unused78(Tpp tp);
void tp_is_unused78_set(Tpp tp, bool val);

bool tp_is_unused79(Tpp tp);
void tp_is_unused79_set(Tpp tp, bool val);

bool tp_is_unused80(Tpp tp);
void tp_is_unused80_set(Tpp tp, bool val);

bool tp_is_unused81(Tpp tp);
void tp_is_unused81_set(Tpp tp, bool val);

bool tp_is_unused82(Tpp tp);
void tp_is_unused82_set(Tpp tp, bool val);

bool tp_is_unused83(Tpp tp);
void tp_is_unused83_set(Tpp tp, bool val);

bool tp_is_unused84(Tpp tp);
void tp_is_unused84_set(Tpp tp, bool val);

bool tp_is_unused85(Tpp tp);
void tp_is_unused85_set(Tpp tp, bool val);

bool tp_is_unused86(Tpp tp);
void tp_is_unused86_set(Tpp tp, bool val);

bool tp_is_unused87(Tpp tp);
void tp_is_unused87_set(Tpp tp, bool val);

bool tp_is_unused88(Tpp tp);
void tp_is_unused88_set(Tpp tp, bool val);

bool tp_is_unused89(Tpp tp);
void tp_is_unused89_set(Tpp tp, bool val);

bool tp_is_unused90(Tpp tp);
void tp_is_unused90_set(Tpp tp, bool val);

bool tp_is_unused91(Tpp tp);
void tp_is_unused91_set(Tpp tp, bool val);

bool tp_is_unused92(Tpp tp);
void tp_is_unused92_set(Tpp tp, bool val);

bool tp_is_unused93(Tpp tp);
void tp_is_unused93_set(Tpp tp, bool val);

bool tp_is_unused94(Tpp tp);
void tp_is_unused94_set(Tpp tp, bool val);

bool tp_is_unused95(Tpp tp);
void tp_is_unused95_set(Tpp tp, bool val);

bool tp_is_unused96(Tpp tp);
void tp_is_unused96_set(Tpp tp, bool val);

bool tp_is_unused97(Tpp tp);
void tp_is_unused97_set(Tpp tp, bool val);

bool tp_is_unused98(Tpp tp);
void tp_is_unused98_set(Tpp tp, bool val);

bool tp_is_unused99(Tpp tp);
void tp_is_unused99_set(Tpp tp, bool val);

bool tp_is_unused100(Tpp tp);
void tp_is_unused100_set(Tpp tp, bool val);

bool tp_is_unused101(Tpp tp);
void tp_is_unused101_set(Tpp tp, bool val);

bool tp_is_unused102(Tpp tp);
void tp_is_unused102_set(Tpp tp, bool val);

bool tp_is_unused103(Tpp tp);
void tp_is_unused103_set(Tpp tp, bool val);

bool tp_is_unused104(Tpp tp);
void tp_is_unused104_set(Tpp tp, bool val);

bool tp_is_unused105(Tpp tp);
void tp_is_unused105_set(Tpp tp, bool val);

bool tp_is_unused106(Tpp tp);
void tp_is_unused106_set(Tpp tp, bool val);

bool tp_is_unused107(Tpp tp);
void tp_is_unused107_set(Tpp tp, bool val);

bool tp_is_unused108(Tpp tp);
void tp_is_unused108_set(Tpp tp, bool val);

bool tp_is_unused109(Tpp tp);
void tp_is_unused109_set(Tpp tp, bool val);

bool tp_is_unused110(Tpp tp);
void tp_is_unused110_set(Tpp tp, bool val);

bool tp_is_unused111(Tpp tp);
void tp_is_unused111_set(Tpp tp, bool val);

bool tp_is_unused112(Tpp tp);
void tp_is_unused112_set(Tpp tp, bool val);

bool tp_is_unused113(Tpp tp);
void tp_is_unused113_set(Tpp tp, bool val);

bool tp_is_unused114(Tpp tp);
void tp_is_unused114_set(Tpp tp, bool val);

bool tp_is_unused115(Tpp tp);
void tp_is_unused115_set(Tpp tp, bool val);

bool tp_is_unused116(Tpp tp);
void tp_is_unused116_set(Tpp tp, bool val);

bool tp_is_unused117(Tpp tp);
void tp_is_unused117_set(Tpp tp, bool val);

bool tp_is_unused118(Tpp tp);
void tp_is_unused118_set(Tpp tp, bool val);

bool tp_is_unused119(Tpp tp);
void tp_is_unused119_set(Tpp tp, bool val);

bool tp_is_unused120(Tpp tp);
void tp_is_unused120_set(Tpp tp, bool val);

bool tp_is_unused121(Tpp tp);
void tp_is_unused121_set(Tpp tp, bool val);

bool tp_is_unused122(Tpp tp);
void tp_is_unused122_set(Tpp tp, bool val);

bool tp_is_unused123(Tpp tp);
void tp_is_unused123_set(Tpp tp, bool val);

bool tp_is_unused124(Tpp tp);
void tp_is_unused124_set(Tpp tp, bool val);

bool tp_is_unused125(Tpp tp);
void tp_is_unused125_set(Tpp tp, bool val);

bool tp_is_unused126(Tpp tp);
void tp_is_unused126_set(Tpp tp, bool val);

bool tp_is_unused127(Tpp tp);
void tp_is_unused127_set(Tpp tp, bool val);

bool tp_is_unused128(Tpp tp);
void tp_is_unused128_set(Tpp tp, bool val);

bool tp_is_unused129(Tpp tp);
void tp_is_unused129_set(Tpp tp, bool val);

bool tp_is_unused130(Tpp tp);
void tp_is_unused130_set(Tpp tp, bool val);

bool tp_is_unused131(Tpp tp);
void tp_is_unused131_set(Tpp tp, bool val);

bool tp_is_unused132(Tpp tp);
void tp_is_unused132_set(Tpp tp, bool val);

bool tp_is_unused133(Tpp tp);
void tp_is_unused133_set(Tpp tp, bool val);

bool tp_is_unused134(Tpp tp);
void tp_is_unused134_set(Tpp tp, bool val);

bool tp_is_unused135(Tpp tp);
void tp_is_unused135_set(Tpp tp, bool val);

bool tp_is_unused136(Tpp tp);
void tp_is_unused136_set(Tpp tp, bool val);

bool tp_is_unused137(Tpp tp);
void tp_is_unused137_set(Tpp tp, bool val);

bool tp_is_unused138(Tpp tp);
void tp_is_unused138_set(Tpp tp, bool val);

bool tp_is_unused139(Tpp tp);
void tp_is_unused139_set(Tpp tp, bool val);

bool tp_is_unused140(Tpp tp);
void tp_is_unused140_set(Tpp tp, bool val);

bool tp_is_unused141(Tpp tp);
void tp_is_unused141_set(Tpp tp, bool val);

bool tp_is_unused142(Tpp tp);
void tp_is_unused142_set(Tpp tp, bool val);

bool tp_is_unused143(Tpp tp);
void tp_is_unused143_set(Tpp tp, bool val);

bool tp_is_unused144(Tpp tp);
void tp_is_unused144_set(Tpp tp, bool val);

bool tp_is_unused145(Tpp tp);
void tp_is_unused145_set(Tpp tp, bool val);

bool tp_is_unused146(Tpp tp);
void tp_is_unused146_set(Tpp tp, bool val);

bool tp_is_unused147(Tpp tp);
void tp_is_unused147_set(Tpp tp, bool val);

bool tp_is_unused148(Tpp tp);
void tp_is_unused148_set(Tpp tp, bool val);

bool tp_is_unused149(Tpp tp);
void tp_is_unused149_set(Tpp tp, bool val);

bool tp_is_unused150(Tpp tp);
void tp_is_unused150_set(Tpp tp, bool val);

bool tp_is_unused151(Tpp tp);
void tp_is_unused151_set(Tpp tp, bool val);

bool tp_is_unused152(Tpp tp);
void tp_is_unused152_set(Tpp tp, bool val);

bool tp_is_unused153(Tpp tp);
void tp_is_unused153_set(Tpp tp, bool val);

bool tp_is_unused154(Tpp tp);
void tp_is_unused154_set(Tpp tp, bool val);

bool tp_is_unused155(Tpp tp);
void tp_is_unused155_set(Tpp tp, bool val);

bool tp_is_unused156(Tpp tp);
void tp_is_unused156_set(Tpp tp, bool val);

bool tp_is_unused157(Tpp tp);
void tp_is_unused157_set(Tpp tp, bool val);

bool tp_is_unused158(Tpp tp);
void tp_is_unused158_set(Tpp tp, bool val);

bool tp_is_unused159(Tpp tp);
void tp_is_unused159_set(Tpp tp, bool val);

bool tp_is_unused160(Tpp tp);
void tp_is_unused160_set(Tpp tp, bool val);

bool tp_is_unused161(Tpp tp);
void tp_is_unused161_set(Tpp tp, bool val);

bool tp_is_unused162(Tpp tp);
void tp_is_unused162_set(Tpp tp, bool val);

bool tp_is_unused163(Tpp tp);
void tp_is_unused163_set(Tpp tp, bool val);

bool tp_is_unused164(Tpp tp);
void tp_is_unused164_set(Tpp tp, bool val);

bool tp_is_unused165(Tpp tp);
void tp_is_unused165_set(Tpp tp, bool val);

bool tp_is_unused166(Tpp tp);
void tp_is_unused166_set(Tpp tp, bool val);

bool tp_is_unused167(Tpp tp);
void tp_is_unused167_set(Tpp tp, bool val);

bool tp_is_unused168(Tpp tp);
void tp_is_unused168_set(Tpp tp, bool val);

bool tp_is_unused169(Tpp tp);
void tp_is_unused169_set(Tpp tp, bool val);

bool tp_is_unused170(Tpp tp);
void tp_is_unused170_set(Tpp tp, bool val);

bool tp_is_unused171(Tpp tp);
void tp_is_unused171_set(Tpp tp, bool val);

bool tp_is_unused172(Tpp tp);
void tp_is_unused172_set(Tpp tp, bool val);

bool tp_is_unused173(Tpp tp);
void tp_is_unused173_set(Tpp tp, bool val);

bool tp_is_unused174(Tpp tp);
void tp_is_unused174_set(Tpp tp, bool val);

bool tp_is_unused175(Tpp tp);
void tp_is_unused175_set(Tpp tp, bool val);

bool tp_is_unused176(Tpp tp);
void tp_is_unused176_set(Tpp tp, bool val);

bool tp_is_unused177(Tpp tp);
void tp_is_unused177_set(Tpp tp, bool val);

bool tp_is_unused178(Tpp tp);
void tp_is_unused178_set(Tpp tp, bool val);

bool tp_is_unused179(Tpp tp);
void tp_is_unused179_set(Tpp tp, bool val);

bool tp_is_unused180(Tpp tp);
void tp_is_unused180_set(Tpp tp, bool val);

bool tp_is_unused181(Tpp tp);
void tp_is_unused181_set(Tpp tp, bool val);

bool tp_is_unused182(Tpp tp);
void tp_is_unused182_set(Tpp tp, bool val);

bool tp_is_unused183(Tpp tp);
void tp_is_unused183_set(Tpp tp, bool val);

bool tp_is_unused184(Tpp tp);
void tp_is_unused184_set(Tpp tp, bool val);

bool tp_is_unused185(Tpp tp);
void tp_is_unused185_set(Tpp tp, bool val);

bool tp_is_unused186(Tpp tp);
void tp_is_unused186_set(Tpp tp, bool val);

bool tp_is_unused187(Tpp tp);
void tp_is_unused187_set(Tpp tp, bool val);

bool tp_is_unused188(Tpp tp);
void tp_is_unused188_set(Tpp tp, bool val);

bool tp_is_unused189(Tpp tp);
void tp_is_unused189_set(Tpp tp, bool val);

bool tp_is_unused190(Tpp tp);
void tp_is_unused190_set(Tpp tp, bool val);

bool tp_is_unused191(Tpp tp);
void tp_is_unused191_set(Tpp tp, bool val);

bool tp_is_unused192(Tpp tp);
void tp_is_unused192_set(Tpp tp, bool val);

bool tp_is_unused193(Tpp tp);
void tp_is_unused193_set(Tpp tp, bool val);

bool tp_is_unused194(Tpp tp);
void tp_is_unused194_set(Tpp tp, bool val);

bool tp_is_unused195(Tpp tp);
void tp_is_unused195_set(Tpp tp, bool val);

bool tp_is_unused196(Tpp tp);
void tp_is_unused196_set(Tpp tp, bool val);

bool tp_is_unused197(Tpp tp);
void tp_is_unused197_set(Tpp tp, bool val);

bool tp_is_unused198(Tpp tp);
void tp_is_unused198_set(Tpp tp, bool val);

bool tp_is_cursor_at(Tpp tp);
void tp_is_cursor_at_set(Tpp tp, bool val);

bool tp_is_cursor_path(Tpp tp);
void tp_is_cursor_path_set(Tpp tp, bool val);

bool tp_is_key(Tpp tp);
void tp_is_key_set(Tpp tp, bool val);

bool tp_is_monst(Tpp tp);
void tp_is_monst_set(Tpp tp, bool val);

bool tp_is_monst_class(Tpp tp, int val);
void tp_is_monst_class_set(Tpp tp, bool val);

bool tp_is_obs_monst(Tpp tp);
void tp_is_obs_monst_set(Tpp tp, bool val);

bool tp_is_obs_player(Tpp tp);
void tp_is_obs_player_set(Tpp tp, bool val);

bool tp_is_player(Tpp tp);
void tp_is_player_set(Tpp tp, bool val);

bool tp_is_wall(Tpp tp);
void tp_is_wall_set(Tpp tp, bool val);

uint8_t tp_player_index_get(Tpp tp);
void    tp_player_index_set(Tpp tp, uint8_t val);

void    tp_z_depth_set(Tpp tp, uint8_t val);
uint8_t tp_z_depth_get(Tpp tp);

void tp_speed_set(Tpp tp, int val);
int  tp_speed_get(Tpp tp);

#endif // THING_TEMPLATE_H_
