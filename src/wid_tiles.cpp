//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_globals.hpp"
#include "my_main.hpp"
#include "my_tex.hpp"
#include "my_tile.hpp"
#include "my_wid_tiles.hpp"

#include <map>

static int                                       wid_tiles_init_done;
static std::map< std::string, class WidTiles * > wid_tiles_all;

bool wid_tiles_init()
{
  TRACE_NO_INDENT();
  wid_tiles_init_done = 1;

  return true;
}

static void wid_tiles_destroy(wid_tilesp w) { TRACE_NO_INDENT(); }

void wid_tiles_fini()
{
  TRACE_NO_INDENT();
  if (wid_tiles_init_done != 0) {
    wid_tiles_init_done = 0;

    auto iter = wid_tiles_all.begin();

    while (iter != wid_tiles_all.end()) {
      wid_tiles_destroy(iter->second);
      iter = wid_tiles_all.erase(iter);
    }
  }
}

wid_tilesp wid_tiles_load(const std::string& name, float scale)
{
  TRACE_NO_INDENT();
  auto *t = wid_tiles_find(name);

  if (t != nullptr) {
    return t;
  }

  if (name.empty()) {
    CROAK("No name for wid_tiles");
    return nullptr;
  }

  t = new class WidTiles();

  auto result = wid_tiles_all.insert(std::make_pair(name, t));

  if (! result.second) {
    CROAK("Wid_tiles insert name [%s] failed", name.c_str());
  }

  char tmp[ 32 ];

  snprintf(tmp, SIZEOF(tmp) - 1, "%s_tl", name.c_str());
  Tilep a_tile = tile_find(tmp);
  if (unlikely(! a_tile)) {
    CROAK("Did not find wid %s tile %s", name.c_str(), tmp);
  }

  Texp tex = tile_tex(a_tile);

  float tile_w = tile_width(a_tile);
  float tile_h = tile_height(a_tile);
  float tex_w  = tex_get_width(tex);
  float tex_h  = tex_get_height(tex);

  t->across = (int) (tex_w / tile_w);
  t->down   = (int) (tex_h / tile_h);
  t->tile_w = (int) tile_w;
  t->tile_h = (int) tile_h;
  t->scale  = scale;

  int i;
  int j;
  int c;

  {
    c = 1;
    for (j = 1; j < t->down - 1; j++) {
      for (i = 1; i < t->across - 1; i++) {
        snprintf(tmp, SIZEOF(tmp) - 1, "%s_%d", name.c_str(), c);
        Tilep tile = tile_find(tmp);
        if (unlikely(! tile)) {
          CROAK("Did not find wid %s tile %s", name.c_str(), tmp);
        }
        t->tile[ i ][ j ] = tile;
        c++;
      }
    }
  }

  {
    c = 1;
    for (i = 1; i < t->across - 1; i++) {
      j = 0;
      snprintf(tmp, SIZEOF(tmp) - 1, "%s_top%d", name.c_str(), c);
      Tilep tile = tile_find(tmp);
      if (unlikely(! tile)) {
        CROAK("Did not find wid %s tile %s", name.c_str(), tmp);
      }

      t->tile[ i ][ j ] = tile;
      c++;
    }
  }

  {
    c = 1;
    for (i = 1; i < t->across - 1; i++) {
      j = t->down - 1;
      ;
      snprintf(tmp, SIZEOF(tmp) - 1, "%s_bot%d", name.c_str(), c);
      Tilep tile = tile_find(tmp);
      if (unlikely(! tile)) {
        CROAK("Did not find wid %s tile %s", name.c_str(), tmp);
      }

      t->tile[ i ][ j ] = tile;
      c++;
    }
  }

  {
    c = 1;
    for (j = 1; j < t->down - 1; j++) {
      i = 0;
      snprintf(tmp, SIZEOF(tmp) - 1, "%s_left%d", name.c_str(), c);
      Tilep tile = tile_find(tmp);
      if (unlikely(! tile)) {
        CROAK("Did not find wid %s tile %s", name.c_str(), tmp);
      }

      t->tile[ i ][ j ] = tile;
      c++;
    }
  }

  {
    c = 1;
    for (j = 1; j < t->down - 1; j++) {
      i = t->across - 1;
      snprintf(tmp, SIZEOF(tmp) - 1, "%s_right%d", name.c_str(), c);
      Tilep tile = tile_find(tmp);
      if (unlikely(! tile)) {
        CROAK("Did not find wid %s tile %s", name.c_str(), tmp);
      }

      t->tile[ i ][ j ] = tile;
      c++;
    }
  }

  {
    i = 0;
    j = 0;
    snprintf(tmp, SIZEOF(tmp) - 1, "%s_tl", name.c_str());
    auto *tile = tile_find(tmp);
    if (unlikely(! tile)) {
      CROAK("Did not find wid %s tile %s", name.c_str(), tmp);
    }

    t->tile[ i ][ j ] = tile;
  }

  {
    i = 0;
    j = t->down - 1;
    snprintf(tmp, SIZEOF(tmp) - 1, "%s_bl", name.c_str());
    auto *tile = tile_find(tmp);
    if (unlikely(! tile)) {
      CROAK("Did not find wid %s tile %s", name.c_str(), tmp);
    }

    t->tile[ i ][ j ] = tile;
  }

  {
    i = t->across - 1;
    j = 0;
    snprintf(tmp, SIZEOF(tmp) - 1, "%s_tr", name.c_str());
    auto *tile = tile_find(tmp);
    if (unlikely(! tile)) {
      CROAK("Did not find wid %s tile %s", name.c_str(), tmp);
    }

    t->tile[ i ][ j ] = tile;
  }

  {
    i = t->across - 1;
    j = t->down - 1;
    snprintf(tmp, SIZEOF(tmp) - 1, "%s_br", name.c_str());
    auto *tile = tile_find(tmp);
    if (unlikely(! tile)) {
      CROAK("Did not find wid %s tile %s", name.c_str(), tmp);
    }

    t->tile[ i ][ j ] = tile;
  }

  return t;
}

wid_tilesp wid_tiles_find(const std::string& file)
{
  TRACE_NO_INDENT();
  if (file.empty()) {
    CROAK("No filename given for wid_tiles find");
  }

  auto result = wid_tiles_all.find(file);
  if (result == wid_tiles_all.end()) {
    return nullptr;
  }

  return result->second;
}
