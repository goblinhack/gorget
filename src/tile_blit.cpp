//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_color_defs.hpp"
#include "my_game.hpp"
#include "my_random.hpp"
#include "my_tile.hpp"

//
// Blits a whole tile.
//
void tile_blit_at(const Tilep &tile, point tl, point br)
{
  blit(tile->gl_binding(), tile->x1, tile->y2, tile->x2, tile->y1, tl.x, tl.y, br.x, br.y);
}

//
// Blits a whole tile. Y co-ords are inverted.
//
void tile_blit_colored_fat(Tilep tile, point tl, point br, color color_tl, color color_tr, color color_bl,
                           color color_br)
{
  float x1 = tile->x1;
  float x2 = tile->x2;
  float y1 = tile->y1;
  float y2 = tile->y2;

#if 0
  if (unlikely(tp != nullptr)) {
    auto left_off  = (float) tp->blit_left_off();
    auto right_off = (float) tp->blit_right_off();
    auto top_off   = (float) tp->blit_top_off();
    auto bot_off   = (float) tp->blit_bot_off();

    float pct_w = tile->pct_width;
    float pct_h = tile->pct_height;
    float pix_w = br.x - tl.x;
    float pix_h = br.y - tl.y;

    tl.x -= left_off * pix_w;
    br.x += right_off * pix_w;
    tl.y -= top_off * pix_h;
    br.y += bot_off * pix_h;

    x1 -= left_off * pct_w;
    x2 += right_off * pct_w;
    y1 -= top_off * pct_h;
    y2 += bot_off * pct_h;
  }
#endif

  blit_colored(tile->gl_binding(), x1, y2, x2, y1, tl.x, br.y, br.x, tl.y, color_tl, color_tr, color_bl, color_br);
}

void tile_blit_colored(Tilep tile, point tl, point br, color color_tl, color color_tr, color color_bl, color color_br)
{
  float x1 = tile->x1;
  float x2 = tile->x2;
  float y1 = tile->y1;
  float y2 = tile->y2;

  blit_colored(tile->gl_binding(), x1, y2, x2, y1, tl.x, br.y, br.x, tl.y, color_tl, color_tr, color_bl, color_br);
}

std::string tile_name(Tilep t)
{
  TRACE_AND_INDENT();
  return (t->name);
}

uint32_t tile_delay_ms(Tilep t) { return (t->delay_ms); }

uint8_t tile_is_moving(Tilep t) { return (t->is_moving); }

uint8_t tile_is_yyy5(Tilep t) { return (t->is_yyy5); }

uint8_t tile_is_yyy6(Tilep t) { return (t->is_yyy6); }

uint8_t tile_is_yyy7(Tilep t) { return (t->is_yyy7); }

uint8_t tile_is_yyy8(Tilep t) { return (t->is_yyy8); }

uint8_t tile_is_yyy9(Tilep t) { return (t->is_yyy9); }

uint8_t tile_is_sleeping(Tilep t) { return (t->is_sleeping); }

uint8_t tile_is_open(Tilep t) { return (t->is_open); }

uint8_t tile_is_dead(Tilep t) { return (t->is_dead); }

uint8_t tile_is_end_of_anim(Tilep t) { return (t->is_end_of_anim); }

uint8_t tile_is_dead_on_end_of_anim(Tilep t) { return (t->is_dead_on_end_of_anim); }

uint8_t tile_is_alive_on_end_of_anim(Tilep t) { return (t->is_alive_on_end_of_anim); }

uint8_t tile_is_resurrecting(Tilep t) { return (t->is_resurrecting); }

Tilep tile_first(Tilevec *tmap)
{
  if (unlikely(! tmap)) {
    return nullptr;
  }
  std::vector< Tilep > *tiles = &((*tmap));
  if (unlikely(! tiles)) {
    return nullptr;
  }
  if (unlikely(tiles->empty())) {
    return nullptr;
  }
  Tilep tile = (*tiles)[ 0 ];
  return tile_index_to_tile(tile->global_index);
}

Tilep tile_random(Tilevec *tmap)
{
  if (unlikely(! tmap)) {
    return nullptr;
  }
  std::vector< Tilep > *tiles = &((*tmap));
  if (unlikely(! tiles)) {
    return nullptr;
  }
  if (unlikely(tiles->empty())) {
    return nullptr;
  }

  int tries = 999999;
  while (tries--) {
    auto index = pcg_rand() % tiles->size();
    auto tile  = (*tiles)[ index ];

    //
    // Don't really want dead tiles when choosing a random start tile.
    //
    if (tile->is_dead) {
      continue;
    }
    if (unlikely(! tile)) {
      ERR("no tile at index #%d, max %d", (int) index, (int) tiles->size());
      return nullptr;
    }
    return tile_index_to_tile(tile->global_index);
  }

  DIE("failed to choose a random tile");
}

Tilep tile_n(Tilevec *tmap, int n)
{
  if (unlikely(! tmap)) {
    return nullptr;
  }
  std::vector< Tilep > *tiles = &((*tmap));
  if (unlikely(! tiles)) {
    return nullptr;
  }
  if (unlikely(tiles->empty())) {
    return nullptr;
  }
  auto index = n % tiles->size();
  auto tile  = (*tiles)[ index ];
  if (unlikely(! tile)) {
    ERR("no tile at index #%d, max %d", (int) index, (int) tiles->size());
    return nullptr;
  }
  return tile_index_to_tile(tile->global_index);
}

int tile_get_n(Tilevec *tmap, Tile *p)
{
  int n = 0;
  for (const auto t : *tmap) {
    if (t == p) {
      return n;
    }
    n++;
  }
  return -1;
}

Tilep tile_get_frame(Tilevec *tmap, uint32_t frame)
{
  for (const auto t : *tmap) {
    if (t->frame == frame) {
      return t;
    }
  }
  return nullptr;
}

Tilep tile_next(Tilevec *tmap, Tilep in)
{
  if (unlikely(! tmap)) {
    return nullptr;
  }
  std::vector< Tilep > *tiles = &((*tmap));
  if (unlikely(tiles->empty())) {
    return nullptr;
  }
  auto cursor = in->index;
  cursor++;
  if (cursor >= tiles->size()) {
    cursor = 0;
  }
  auto tile = ((*tiles)[ cursor ]);
  return tile_index_to_tile(tile->global_index);
}

int Tile::gl_binding(void) const { return _gl_binding; }

void Tile::set_gl_binding(int v) { _gl_binding = v; }

int Tile::gl_binding_monochrome(void) const { return _gl_binding_monochrome; }

void Tile::set_gl_binding_monochrome(int v) { _gl_binding_monochrome = v; }

int Tile::gl_binding_mask(void) const { return _gl_binding_mask; }

void Tile::set_gl_binding_mask(int v) { _gl_binding_mask = v; }

//
// Blits a whole tile. Y co-ords are inverted.
//
void tile_blit_outline(const Tilep &tile, const point tl, const point br, const color &c, bool square)
{
  float x1, x2, y1, y2;

  if (unlikely(! tile)) {
    return;
  }

  x1 = tile->x1;
  x2 = tile->x2;
  y1 = tile->y1;
  y2 = tile->y2;

  color outline = {10, 10, 10, 255};
  glcolor(outline);

  const float dx = 1;
  const float dy = 1;

  auto binding = tile->gl_binding_mask();

  if (square) {
    blit(binding, x1, y2, x2, y1, tl.x - dx, br.y - dy, br.x - dx, tl.y - dy);
    blit(binding, x1, y2, x2, y1, tl.x + dx, br.y + dy, br.x + dx, tl.y + dy);
    blit(binding, x1, y2, x2, y1, tl.x - dx, br.y + dy, br.x - dx, tl.y + dy);
    blit(binding, x1, y2, x2, y1, tl.x + dx, br.y - dy, br.x + dx, tl.y - dy);
  }
  blit(binding, x1, y2, x2, y1, tl.x + dx, br.y, br.x + dx, tl.y);
  blit(binding, x1, y2, x2, y1, tl.x - dx, br.y, br.x - dx, tl.y);
  blit(binding, x1, y2, x2, y1, tl.x, br.y + dy, br.x, tl.y + dy);
  blit(binding, x1, y2, x2, y1, tl.x, br.y - dy, br.x, tl.y - dy);

  glcolor(c);
  binding = tile->gl_binding();
  blit(binding, x1, y2, x2, y1, tl.x, br.y, br.x, tl.y);
}

void tile_blit_outline(const Tilep &tile, const point tl, const point br, const color &c, const color &outline,
                       bool square)
{
  float x1, x2, y1, y2;

  if (unlikely(! tile)) {
    return;
  }

  x1 = tile->x1;
  x2 = tile->x2;
  y1 = tile->y1;
  y2 = tile->y2;

  glcolor(outline);

  const float dx = 1;
  const float dy = 1;

  auto binding = tile->gl_binding_mask();

  if (square) {
    blit(binding, x1, y2, x2, y1, tl.x - dx, br.y - dy, br.x - dx, tl.y - dy);
    blit(binding, x1, y2, x2, y1, tl.x + dx, br.y + dy, br.x + dx, tl.y + dy);
    blit(binding, x1, y2, x2, y1, tl.x - dx, br.y + dy, br.x - dx, tl.y + dy);
    blit(binding, x1, y2, x2, y1, tl.x + dx, br.y - dy, br.x + dx, tl.y - dy);
  }
  blit(binding, x1, y2, x2, y1, tl.x + dx, br.y, br.x + dx, tl.y);
  blit(binding, x1, y2, x2, y1, tl.x - dx, br.y, br.x - dx, tl.y);
  blit(binding, x1, y2, x2, y1, tl.x, br.y + dy, br.x, tl.y + dy);
  blit(binding, x1, y2, x2, y1, tl.x, br.y - dy, br.x, tl.y - dy);

  glcolor(c);
  binding = tile->gl_binding();
  blit(binding, x1, y2, x2, y1, tl.x, br.y, br.x, tl.y);
}

void tile_blit_outline(uint16_t index, const point tl, const point br, const color &c, bool square)
{
  tile_blit_outline(tile_index_to_tile(index), tl, br, c, square);
}

void tile_blit(const Tilep &tile, const point tl, const point br, const color &c)
{
  float x1, x2, y1, y2;

  if (unlikely(! tile)) {
    return;
  }

  x1 = tile->x1;
  x2 = tile->x2;
  y1 = tile->y1;
  y2 = tile->y2;

  auto binding = tile->gl_binding();
  glcolor(c);
  blit(binding, x1, y2, x2, y1, tl.x, br.y, br.x, tl.y);
}

//
// Blits a whole tile. Y co-ords are inverted.
//
static void tile_blit_outline_section(const Tilep &tile, const fpoint &tile_tl, const fpoint &tile_br, const point tl,
                                      const point br, float scale)
{
  float x1, x2, y1, y2;

  if (unlikely(! tile)) {
    return;
  }

  float tw = tile->x2 - tile->x1;
  float th = tile->y2 - tile->y1;

  x1 = tile->x1 + tile_tl.x * tw;
  x2 = tile->x1 + tile_br.x * tw;
  y1 = tile->y1 + tile_tl.y * th;
  y2 = tile->y1 + tile_br.y * th;

  glcolor(BLACK);

  if (scale < 0.2) {
    scale = 0.2;
  }
  const float dx = 1;
  const float dy = 1;

  blit(tile->gl_binding(), x1, y2, x2, y1, tl.x - dx, br.y - dy, br.x - dx, tl.y - dy);
  blit(tile->gl_binding(), x1, y2, x2, y1, tl.x + dx, br.y + dy, br.x + dx, tl.y + dy);
  blit(tile->gl_binding(), x1, y2, x2, y1, tl.x - dx, br.y + dy, br.x - dx, tl.y + dy);
  blit(tile->gl_binding(), x1, y2, x2, y1, tl.x + dx, br.y - dy, br.x + dx, tl.y - dy);
  blit(tile->gl_binding(), x1, y2, x2, y1, tl.x + dx, br.y, br.x + dx, tl.y);
  blit(tile->gl_binding(), x1, y2, x2, y1, tl.x - dx, br.y, br.x - dx, tl.y);
  blit(tile->gl_binding(), x1, y2, x2, y1, tl.x, br.y + dy, br.x, tl.y + dy);
  blit(tile->gl_binding(), x1, y2, x2, y1, tl.x, br.y - dy, br.x, tl.y - dy);

  glcolor(WHITE);
  blit(tile->gl_binding(), x1, y2, x2, y1, tl.x, br.y, br.x, tl.y);
}

void tile_blit(const Tilep &tile, const point tl, const point br)
{
  float x1, x2, y1, y2;

  //
  // Only some walls have deco tiles, so the pointer is left null for
  // those that do not.
  //
  if (unlikely(! tile)) {
    return;
  }

  x1 = tile->x1;
  x2 = tile->x2;
  y1 = tile->y1;
  y2 = tile->y2;

  blit(tile->gl_binding(), x1, y2, x2, y1, tl.x, br.y, br.x, tl.y);
}

void tile_blit_mask(const Tilep &tile, const point tl, const point br)
{
  float x1, x2, y1, y2;

  //
  // Only some walls have deco tiles, so the pointer is left null for
  // those that do not.
  //
  if (unlikely(! tile)) {
    return;
  }

  x1 = tile->x1;
  x2 = tile->x2;
  y1 = tile->y1;
  y2 = tile->y2;

  blit(tile->gl_binding_mask(), x1, y2, x2, y1, tl.x, br.y, br.x, tl.y);
}

void tile_blit(const Tilep &tile, const point tl, const point tr, const point bl, const point br)
{
  float x1, x2, y1, y2;

  //
  // Only some walls have deco tiles, so the pointer is left null for
  // those that do not.
  //
  if (unlikely(! tile)) {
    return;
  }

  x1 = tile->x1;
  x2 = tile->x2;
  y1 = tile->y1;
  y2 = tile->y2;

  blit(tile->gl_binding(), x1, y2, x2, y1, tl, tr, bl, br);
}

void tile_blit(uint16_t index, const point tl, const point br) { tile_blit(tile_index_to_tile(index), tl, br); }

void tile_blit_section(const Tilep &tile, const point tile_tl, const point tile_br, const point tl, const point br)
{
  float x1, x2, y1, y2;

  //
  // Only some walls have deco tiles, so the pointer is left null for
  // those that do not.
  //
  if (unlikely(! tile)) {
    return;
  }

  float tw = tile->x2 - tile->x1;
  float th = tile->y2 - tile->y1;

  x1 = tile->x1 + tile_tl.x * tw;
  x2 = tile->x1 + tile_br.x * tw;
  y1 = tile->y1 + tile_tl.y * th;
  y2 = tile->y1 + tile_br.y * th;

  blit(tile->gl_binding(), x1, y2, x2, y1, tl.x, br.y, br.x, tl.y);
}

void tile_blit_section(uint16_t index, const point tile_tl, const point tile_br, const point tl, const point br)
{
  tile_blit_section(tile_index_to_tile(index), tile_tl, tile_br, tl, br);
}

void tile_blit_section_colored(const Tilep &tile, const fpoint &tile_tl, const fpoint &tile_br, const point tl,
                               const point br, color color_tl, color color_tr, color color_bl, color color_br)
{
  float x1, x2, y1, y2;

  //
  // Only some walls have deco tiles, so the pointer is left null for
  // those that do not.
  //
  if (unlikely(! tile)) {
    return;
  }

  float tw = tile->x2 - tile->x1;
  float th = tile->y2 - tile->y1;

  x1 = tile->x1 + tile_tl.x * tw;
  x2 = tile->x1 + tile_br.x * tw;
  y1 = tile->y1 + tile_tl.y * th;
  y2 = tile->y1 + tile_br.y * th;

  blit_colored(tile->gl_binding(), x1, y2, x2, y1, tl.x, br.y, br.x, tl.y, color_tl, color_tr, color_bl, color_br);
}

void tile_blit_section_colored(uint16_t index, const fpoint &tile_tl, const fpoint &tile_br, const point tl,
                               const point br, color color_tl, color color_tr, color color_bl, color color_br)
{
  tile_blit_section_colored(tile_index_to_tile(index), tile_tl, tile_br, tl, br, color_tl, color_tr, color_bl,
                            color_br);
}

void tile_blit_outline_section_colored(const Tilep &tile, const fpoint &tile_tl, const fpoint &tile_br,
                                       const point tl, const point br, color color_tl, color color_tr, color color_bl,
                                       color color_br)
{
  tile_blit_outline_section(tile, tile_tl, tile_br, tl, br, 0.75);
}

void tile_blit_outline_section_colored(uint16_t index, const fpoint &tile_tl, const fpoint &tile_br, const point tl,
                                       const point br, color color_tl, color color_tr, color color_bl, color color_br)
{
  tile_blit_outline_section_colored(tile_index_to_tile(index), tile_tl, tile_br, tl, br, color_tl, color_tr, color_bl,
                                    color_br);
}

void tile_blit_outline_section_colored(const Tilep &tile, const fpoint &tile_tl, const fpoint &tile_br,
                                       const point tl, const point br, color color_tl, color color_tr, color color_bl,
                                       color color_br, float scale)
{
  tile_blit_outline_section(tile, tile_tl, tile_br, tl, br, scale);
}

void tile_blit_outline_section_colored(uint16_t index, const fpoint &tile_tl, const fpoint &tile_br, const point tl,
                                       const point br, color color_tl, color color_tr, color color_bl, color color_br,
                                       float scale)
{
  tile_blit_outline_section_colored(tile_index_to_tile(index), tile_tl, tile_br, tl, br, color_bl, color_br, color_tl,
                                    color_tr, scale);
}
