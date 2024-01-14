//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_array_bounds_check.hpp"
#include "my_font.hpp"

Fontp font_ui;

static std::map< std::string, Fontp > fonts;

void font_fini(void) { TRACE_AND_INDENT(); }

static Fontp font_load(std::string name)
{
  TRACE_AND_INDENT();
  auto f = font_find(name);

  if (f) {
    return f;
  }

  if (name == "") {
    ERR("No name for font %s", __FUNCTION__);
    return nullptr;
  }

  f = new Font();

  auto result = fonts.insert(std::make_pair(name, f));

  if (! result.second) {
    ERR("Font insert name [%s] failed", name.c_str());
    return f;
  }

  uint32_t d = 0;
  uint32_t c = FONT_CHAR_MIN;

  while (d < FONT_CHAR_MAX) {
    if (c >= FONT_CHAR_MAX) {
      break;
    }

    f->u_to_c[ c ] = d;
    c++;
    d++;
  }

  return f;
}

Fontp font_find(std::string file)
{
  TRACE_AND_INDENT();
  if (file == "") {
    ERR("No filename given for font find %s", __FUNCTION__);
    return nullptr;
  }

  auto result = fonts.find(file);
  if (result == fonts.end()) {
    return nullptr;
  }

  return (result->second);
}

Tilep Font::font_get_tile(int u)
{
  Font *me = this;
  if (unlikely(! me)) {
    DIE("No font");
  }

  if ((u < 0) || (u >= FONT_CHAR_MAX)) {
    if (u == '?') {
      DIE("char 0x%X/%d -> bad index", u, u);
      return (font_get_tile('?'));
    } else {
      DIE("char 0x%X/%d -> bad index", u, u);
      return (font_get_tile('?'));
    }
    return (font_get_tile('?'));
  }

  auto index = get(this->u_to_c, u);

  if ((index < 0) || (index >= FONT_CHAR_MAX)) {
    if (u == '?') {
      DIE("char 0x%X/%d -> bad index %d", u, u, index);
      return (font_get_tile('?'));
    } else {
      DIE("char 0x%X/%d -> bad index %d", u, u, index);
      return (font_get_tile('?'));
    }
    return (font_get_tile('?'));
  }

  auto tile = get(this->cache, index);
  if (tile) {
    return tile;
  }

  char tile_name[ 10 ];
  snprintf(tile_name, sizeof(tile_name), "%d.%d", tile_index, index);

  tile = tile_find(tile_name);
  if (unlikely(! tile)) {
    if (u == '?') {
      DIE("char 0x%X/%d -> not found as tile %s", u, u, tile_name);
      return (font_get_tile('?'));
    }
    DIE("char 0x%X/%d -> not found as tile %s", u, u, tile_name);
    return (font_get_tile('?'));
  }

  set(this->cache, index, tile);

  return tile;
}

uint8_t font_init(void)
{
  TRACE_AND_INDENT();

  font_ui             = font_load("PressStart");
  font_ui->tile_index = 1;

  return true;
}
