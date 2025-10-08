//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_color_defs.hpp"
#include "my_cpp_template.hpp"
#include "my_fpoint.hpp"
#include "my_game.hpp"
#include "my_gl.hpp"
#include "my_ptrcheck.hpp"
#include "my_size.hpp"
#include "my_string.hpp"
#include "my_tex.hpp"
#include "my_tile.hpp"

#include <array>
#include <vector>

std::unordered_map< std::string, class Tile * > all_tiles;
std::vector< class Tile * >                     all_tiles_array;

static bool tile_init_done;

class Tile
{
public:
  Tile(void);
  ~Tile(void);
  Tile(const class Tile *tile);

  std::string name;

  //
  // Grabbed by a template
  //
  uint8_t in_use {};
  int     global_index;

  //
  // Index within the overall texture, left to right, top to bottom.
  //
  int index {};

  int pix_width {};
  int pix_height {};

  float pct_width {};
  float pct_height {};

  //
  // Texture co-ordinates within the image.
  //
  float x1 {};
  float y1 {};
  float x2 {};
  float y2 {};

  //
  // As above but not clipped 0.5 pixels. Actually we do not clip anymore,
  // it didn't help. Best to choose a resolution that works.
  //
  float ox1 {};
  float oy1 {};
  float ox2 {};
  float oy2 {};

  //
  // Percentage points that indicate the start of the pixels within the tile
  // texture for use in collisions.
  //
  float px1 {};
  float py1 {};
  float px2 {};
  float py2 {};

  class Tex *tex {};
  class Tex *tex_monochrome {};
  class Tex *tex_mask {};

  std::array< std::array< uint8_t, TILE_HEIGHT_MAX >, TILE_WIDTH_MAX > pix {};

  //
  // Delay in ms between frames.
  //
  uint32_t delay_ms {};

  uint8_t frame {};
  uint8_t dir {};

  bool internal_has_dir_anim     : 1 {};
  bool is_alive_on_end_of_anim   : 1 {};
  bool is_cleanup_on_end_of_anim : 1 {};
  bool is_end_of_anim            : 1 {};
  bool is_outline                : 1 {};
  bool is_loggable               : 1 {};

private:
  int _gl_binding {};
  int _gl_binding_monochrome {};
  int _gl_binding_mask {};

public:
  int  gl_binding(void) const;
  int  gl_binding_monochrome(void) const;
  int  gl_binding_mask(void) const;
  void set_gl_binding(int v);
  void set_gl_binding_monochrome(int v);
  void set_gl_binding_mask(int v);
};

Tile::Tile(void) { newptr(MTYPE_TILE, this, "Tile"); }

Tile::~Tile(void) { oldptr(MTYPE_TILE, this); }

bool tile_init(void)
{
  TRACE_NO_INDENT();

  tile_init_done = true;

  return true;
}

void tile_fini(void)
{
  TRACE_NO_INDENT();

  if (tile_init_done) {
    tile_init_done = false;
  }

  for (auto &t : all_tiles) {
    verify(MTYPE_TILE, t.second);
    delete t.second;
  }

  all_tiles.clear();
  all_tiles_array.clear();
}

Tile::Tile(const class Tile *tile)
{
  newptr(MTYPE_TILE, this, "Tile copy");

  pix_width  = tile->pix_width;
  pix_height = tile->pix_height;
  pct_width  = tile->pct_width;
  pct_height = tile->pct_height;
  x1         = tile->x1;
  y1         = tile->y1;
  x2         = tile->x2;
  y2         = tile->y2;

#ifdef ENABLE_TILE_BOUNDS
  ox1 = tile->ox1;
  oy1 = tile->oy1;
  ox2 = tile->ox2;
  oy2 = tile->oy2;
  px1 = tile->px1;
  py1 = tile->py1;
  px2 = tile->px2;
  py2 = tile->py2;
#endif

  set_gl_binding(tile->gl_binding());
  set_gl_binding_monochrome(tile->gl_binding_monochrome());
  set_gl_binding_mask(tile->gl_binding_mask());

  tex            = tile->tex;
  tex_monochrome = tile->tex_monochrome;
  tex_mask       = tile->tex_mask;

  std::copy(mbegin(tile->pix), mend(tile->pix), mbegin(pix));

  delay_ms                  = tile->delay_ms;
  dir                       = tile->dir;
  is_loggable               = tile->is_loggable;
  is_end_of_anim            = tile->is_end_of_anim;
  is_cleanup_on_end_of_anim = tile->is_cleanup_on_end_of_anim;
  is_alive_on_end_of_anim   = tile->is_alive_on_end_of_anim;
  internal_has_dir_anim     = tile->internal_has_dir_anim;

  index        = 0;
  global_index = all_tiles_array.size() + 1;
  name         = tile->name + " " + std::to_string(global_index);

  auto result = all_tiles.insert(std::make_pair(name, this));
  if (! result.second) {
    ERR("Tile copy insert name [%s] failed", name.c_str());
  }
  all_tiles_array.push_back(this);
}

void tile_load_arr(const char *file, const char *alias, uint32_t width, uint32_t height, uint32_t nargs,
                   const char *arr[])
{
  TRACE_NO_INDENT();

  Texp tex = tex_load(file, alias, GL_NEAREST);

  float fw = (float) 1.0 / ((((float) tex_get_width(tex))) / (((float) width)));
  float fh = (float) 1.0 / ((((float) tex_get_height(tex))) / (((float) height)));

  int x   = 0;
  int y   = 0;
  int idx = 0;

  isize pixel_size;

  pixel_size.w = width;
  pixel_size.h = height;

  while (nargs--) {
    std::string name = arr[ idx++ ];

    if (name != "") {
      if (tile_find(name)) {
        DIE("Tile name [%s] already used", name.c_str());
      }

      auto t      = new Tile(); // std::make_shared< class Tile >();
      auto result = all_tiles.insert(std::make_pair(name, t));
      if (! result.second) {
        ERR("Tile insert name [%s] failed", name.c_str());
      }

      //
      // Global array of all tiles
      //
      all_tiles_array.push_back(t);
      t->global_index = all_tiles_array.size();

      t->name       = name;
      t->index      = idx - 1;
      t->pix_width  = width;
      t->pix_height = height;
      t->tex        = tex;
      t->set_gl_binding(tex_get_gl_binding(tex));

      t->x1 = fw * ((float) (x));
      t->y1 = fh * ((float) (y));
      t->x2 = t->x1 + fw;
      t->y2 = t->y1 + fh;

#ifdef ENABLE_TILE_BOUNDS
      t->ox1 = t->x1;
      t->oy1 = t->y1;
      t->ox2 = t->x2;
      t->oy2 = t->y2;
#endif

      t->pct_width  = fw;
      t->pct_height = fh;

#ifdef ENABLE_DEBUG_TILE
      printf("Tile: %-10s %ux%u (%u, %u)", name.c_str(), width, height, x, y);
#endif

#ifdef ENABLE_TILE_BOUNDS
      if ((pixel_size.w <= TILE_WIDTH_MAX) && (pixel_size.h <= TILE_HEIGHT_MAX)) {
        SDL_Surface *s = tex_get_surface(tex);

        spoint off(pixel_size.w * x, pixel_size.h * y);

        spoint MAX(pixel_size.w * x, pixel_size.h * y);

        spoint MIN((pixel_size.w * x) + pixel_size.w - 1, (pixel_size.h * y) + pixel_size.h - 1);

        int x1, y1;

        for (y1 = pixel_size.h - 1; y1 >= 0; y1--) {
          for (x1 = 0; x1 < pixel_size.w; x1++) {

            spoint at((pixel_size.w * x) + x1, (pixel_size.h * y) + y1);

            color p;
            getPixel(s, at.x, at.y, p);

            //
            // If solid...
            //
            if (p.a >= 0xef) {
              MIN.x = std::min(at.x, MIN.x);
              MIN.y = std::min(at.y, MIN.y);
              MAX.x = std::max(at.x, MAX.x);
              MAX.y = std::max(at.y, MAX.y);
#ifdef ENABLE_DEBUG_TILE
              printf("X");
#endif
              if ((x1 < TILE_WIDTH_MAX) && (y1 < TILE_HEIGHT_MAX)) {
                t->pix[ x1 ][ y1 ] = (uint8_t) 1;
              }
            } else if (p.a > 0) {
#ifdef ENABLE_DEBUG_TILE
              printf(".");
#endif
            } else {
#ifdef ENABLE_DEBUG_TILE
              printf(" ");
#endif
            }
          }
#ifdef ENABLE_DEBUG_TILE
          printf("\n");
#endif
        }

        t->px1 = (((float) (MIN.x) - off.x)) / ((float) pixel_size.w);
        t->px2 = (((float) (MAX.x) - off.x + 1)) / ((float) pixel_size.w);
        t->py1 = (((float) (MIN.y) - off.y)) / ((float) pixel_size.h);
        t->py2 = (((float) (MAX.y) - off.y + 1)) / ((float) pixel_size.h);
      }
#endif

#ifdef ENABLE_DEBUG_TILE
      printf("^^^  %s %f %f %f %f\n", name.c_str(), t->px1, t->py1, t->px2, t->py2);
#endif
    }

    x++;

    //
    // Check the whole tile can be read
    //
    if ((x * width) + (width - 1) >= tex_get_width(tex)) {
      x = 0;
      y++;
    }

    if (y * height > tex_get_height(tex)) {
      if (name != "") {
        DIE("Overflow reading tile arr[%s]", name.c_str());
      } else {
        ERR("Overflow reading tile arr at x %d y %d", x, y);
      }
    }
  }
}

void tile_load_arr_sprites(const char *file, const char *alias, uint32_t width, uint32_t height, uint32_t nargs,
                           const char *arr[], int gl_mode)
{
  TRACE_NO_INDENT();
  Texp tex;
  Texp tex_monochrome;
  Texp tex_mask;

  tex_load(&tex, &tex_monochrome, &tex_mask, file, alias, gl_mode);

  float fw = (float) 1.0 / ((((float) tex_get_width(tex))) / (((float) width)));
  float fh = (float) 1.0 / ((((float) tex_get_height(tex))) / (((float) height)));

  int x   = 0;
  int y   = 0;
  int idx = 0;

  isize pixel_size;

  pixel_size.w = width;
  pixel_size.h = height;

  while (nargs--) {
    std::string name = arr[ idx++ ];

    if (name != "") {
      if (tile_find(name)) {
        DIE("Tile name [%s] already used", name.c_str());
      }

      IF_DEBUG2 { LOG("Add tile name [%s]", name.c_str()); }

      auto t      = new Tile(); // std::make_shared< class Tile >();
      auto result = all_tiles.insert(std::make_pair(name, t));
      if (! result.second) {
        DIE("Tile insert name [%s] failed", name.c_str());
      }

      //
      // Global array of all tiles
      //
      all_tiles_array.push_back(t);
      t->global_index = all_tiles_array.size();

      t->name           = name;
      t->index          = idx - 1;
      t->pix_width      = width;
      t->pix_height     = height;
      t->tex            = tex;
      t->tex_monochrome = tex_monochrome;

      t->tex_mask = tex_mask;

      t->set_gl_binding(tex_get_gl_binding(t->tex));
      t->set_gl_binding_monochrome(tex_get_gl_binding(t->tex_monochrome));
      t->set_gl_binding_mask(tex_get_gl_binding(t->tex_mask));

      t->x1 = fw * ((float) (x));
      t->y1 = fh * ((float) (y));
      t->x2 = t->x1 + fw;
      t->y2 = t->y1 + fh;

#ifdef ENABLE_TILE_BOUNDS
      t->ox1 = t->x1;
      t->oy1 = t->y1;
      t->ox2 = t->x2;
      t->oy2 = t->y2;
#endif

      t->pct_width  = fw;
      t->pct_height = fh;

#ifdef ENABLE_DEBUG_TILE
      printf("Tile: %-10s %ux%u (%u, %u)", name.c_str(), width, height, x, y);
#endif

#ifdef ENABLE_TILE_BOUNDS
      if ((pixel_size.w <= TILE_WIDTH_MAX) && (pixel_size.h <= TILE_HEIGHT_MAX)) {
        SDL_Surface *s = tex_get_surface(tex);

        spoint off(pixel_size.w * x, pixel_size.h * y);

        spoint MAX(pixel_size.w * x, pixel_size.h * y);

        spoint MIN((pixel_size.w * x) + pixel_size.w - 1, (pixel_size.h * y) + pixel_size.h - 1);

        int x1, y1;

        for (y1 = pixel_size.h - 1; y1 >= 0; y1--) {
          for (x1 = 0; x1 < pixel_size.w; x1++) {

            spoint at((pixel_size.w * x) + x1, (pixel_size.h * y) + y1);

            color p;
            getPixel(s, at.x, at.y, p);

            //
            // If solid...
            //
            if (p.a >= 0xef) {
              MIN.x = std::min(at.x, MIN.x);
              MIN.y = std::min(at.y, MIN.y);
              MAX.x = std::max(at.x, MAX.x);
              MAX.y = std::max(at.y, MAX.y);
#ifdef ENABLE_DEBUG_TILE
              printf("X");
#endif
              if ((x1 < TILE_WIDTH_MAX) && (y1 < TILE_HEIGHT_MAX)) {
                t->pix[ x1 ][ y1 ] = (uint8_t) 1;
              }
            } else if (p.a > 0) {
#ifdef ENABLE_DEBUG_TILE
              printf(".");
#endif
            } else {
#ifdef ENABLE_DEBUG_TILE
              printf(" ");
#endif
            }
          }
#ifdef ENABLE_DEBUG_TILE
          printf("\n");
#endif
        }

        t->px1 = (((float) (MIN.x) - off.x)) / ((float) pixel_size.w);
        t->px2 = (((float) (MAX.x) - off.x + 1)) / ((float) pixel_size.w);
        t->py1 = (((float) (MIN.y) - off.y)) / ((float) pixel_size.h);
        t->py2 = (((float) (MAX.y) - off.y + 1)) / ((float) pixel_size.h);
      }
#endif

#ifdef ENABLE_DEBUG_TILE
      printf("^^^  %s %f %f %f %f\n", name.c_str(), t->px1, t->py1, t->px2, t->py2);
#endif
    }

    x++;

    //
    // Check the whole tile can be read
    //
    if ((x * width) + (width - 1) >= tex_get_width(tex)) {
      x = 0;
      y++;
    }

    if (y * height > tex_get_height(tex)) {
      if (name != "") {
        DIE("Overflow reading tile arr[%s]", name.c_str());
      } else {
        DIE("Overflow reading tile arr at x %d y %d", x, y);
      }
    }
  }
}

void tile_load_arr_sprites(std::string file, std::string alias, uint32_t width, uint32_t height,
                           const std::vector< std::string > &arr, int gl_mode)
{
  TRACE_NO_INDENT();
  Texp tex;
  Texp tex_monochrome;
  Texp tex_mask;

  tex_load(&tex, &tex_monochrome, &tex_mask, file, alias, gl_mode);

  float fw = (float) 1.0 / ((((float) tex_get_width(tex))) / (((float) width)));
  float fh = (float) 1.0 / ((((float) tex_get_height(tex))) / (((float) height)));

  int x   = 0;
  int y   = 0;
  int idx = 0;

  isize pixel_size;

  pixel_size.w = width;
  pixel_size.h = height;

  for (auto &name : arr) {
    if (name != "") {
      if (tile_find(name)) {
        DIE("Tile name [%s] already used", name.c_str());
      }

      auto t      = new Tile(); // std::make_shared< class Tile >();
      auto result = all_tiles.insert(std::make_pair(name, t));
      if (! result.second) {
        DIE("Tile insert name [%s] failed", name.c_str());
      }

      //
      // Global array of all tiles
      //
      all_tiles_array.push_back(t);
      t->global_index = all_tiles_array.size();

      t->name           = name;
      t->index          = idx - 1;
      t->pix_width      = width;
      t->pix_height     = height;
      t->tex            = tex;
      t->tex_monochrome = tex_monochrome;
      t->tex_mask       = tex_mask;
      t->set_gl_binding(tex_get_gl_binding(t->tex));
      t->set_gl_binding_monochrome(tex_get_gl_binding(t->tex_monochrome));
      t->set_gl_binding_mask(tex_get_gl_binding(t->tex_mask));

      t->x1 = fw * ((float) (x));
      t->y1 = fh * ((float) (y));
      t->x2 = t->x1 + fw;
      t->y2 = t->y1 + fh;

#ifdef ENABLE_TILE_BOUNDS
      t->ox1 = t->x1;
      t->oy1 = t->y1;
      t->ox2 = t->x2;
      t->oy2 = t->y2;
#endif
      t->pct_width  = fw;
      t->pct_height = fh;

#ifdef ENABLE_DEBUG_TILE
      printf("Tile: %-10s %ux%u (%u, %u)", name.c_str(), width, height, x, y);
#endif

#ifdef ENABLE_TILE_BOUNDS
      if ((pixel_size.w <= TILE_WIDTH_MAX) && (pixel_size.h <= TILE_HEIGHT_MAX)) {
        SDL_Surface *s = tex_get_surface(tex);

        spoint off(pixel_size.w * x, pixel_size.h * y);

        spoint MAX(pixel_size.w * x, pixel_size.h * y);

        spoint MIN((pixel_size.w * x) + pixel_size.w - 1, (pixel_size.h * y) + pixel_size.h - 1);

        int x1, y1;

        for (y1 = pixel_size.h - 1; y1 >= 0; y1--) {
          for (x1 = 0; x1 < pixel_size.w; x1++) {

            spoint at((pixel_size.w * x) + x1, (pixel_size.h * y) + y1);

            color p;
            getPixel(s, at.x, at.y, p);

            //
            // If solid...
            //
            if (p.a >= 0xef) {
              MIN.x = std::min(at.x, MIN.x);
              MIN.y = std::min(at.y, MIN.y);
              MAX.x = std::max(at.x, MAX.x);
              MAX.y = std::max(at.y, MAX.y);
#ifdef ENABLE_DEBUG_TILE
              printf("X");
#endif
              if ((x1 < TILE_WIDTH_MAX) && (y1 < TILE_HEIGHT_MAX)) {
                t->pix[ x1 ][ y1 ] = (uint8_t) 1;
              }
            } else if (p.a > 0) {
#ifdef ENABLE_DEBUG_TILE
              printf(".");
#endif
            } else {
#ifdef ENABLE_DEBUG_TILE
              printf(" ");
#endif
            }
          }
#ifdef ENABLE_DEBUG_TILE
          printf("\n");
#endif
        }

        t->px1 = (((float) (MIN.x) - off.x)) / ((float) pixel_size.w);
        t->px2 = (((float) (MAX.x) - off.x + 1)) / ((float) pixel_size.w);
        t->py1 = (((float) (MIN.y) - off.y)) / ((float) pixel_size.h);
        t->py2 = (((float) (MAX.y) - off.y + 1)) / ((float) pixel_size.h);
      }
#endif

#ifdef ENABLE_DEBUG_TILE
      printf("^^^  %s %f %f %f %f\n", name.c_str(), t->px1, t->py1, t->px2, t->py2);
#endif
    }

    x++;

    //
    // Check the whole tile can be read
    //
    if ((x * width) + (width - 1) >= tex_get_width(tex)) {
      x = 0;
      y++;
    }

    if (y * height > tex_get_height(tex)) {
      if (name != "") {
        DIE("Overflow reading tile arr[%s]", name.c_str());
      } else {
        DIE("Overflow reading tile arr at x %d y %d", x, y);
      }
    }
  }
}

//
// Find an existing tile.
//
Tilep tile_find(std::string name)
{
  TRACE_NO_INDENT();

  if (name == "") {
    return nullptr;
  }

  auto result = all_tiles.find(name);
  if (result == all_tiles.end()) {
    return nullptr;
  }

  return result->second;
}

Tilep tile_find_mand(std::string name)
{
  TRACE_NO_INDENT();

  if (name == "") {
    ERR("No tile name given");
    return nullptr;
  }

  auto result = all_tiles.find(name);
  if (result == all_tiles.end()) {
    DIE("Tile name %s not found", name.c_str());
    return nullptr;
  }

  return result->second;
}

std::string tile_name_get(Tilep tile) { return tile->name; }

int tile_width(Tilep tile) { return tile->pix_width; }

int tile_height(Tilep tile) { return tile->pix_height; }

Texp tile_tex(Tilep tile) { return tile->tex; }

uint32_t tile_index(Tilep tile) { return tile->index; }

void tile_coords(Tilep tile, float *x1, float *y1, float *x2, float *y2)
{
  *x1 = tile->x1;
  *y1 = tile->y1;
  *x2 = tile->x2;
  *y2 = tile->y2;
}

Tilep string2tile(const char **s, int *len)
{
  TRACE_NO_INDENT();
  static char        name[ MAXSHORTSTR ];
  static const char *eo_name = name + MAXSHORTSTR;
  const char        *c       = *s;
  char              *t       = name;

  while (t < eo_name) {
    if ((*c == '\0') || (*c == '$')) {
      break;
    }

    *t++ = *c++;
  }

  if (c == eo_name) {
    return nullptr;
  }

  *t++ = '\0';
  *s += (t - name);

  if (len) {
    *len = t - name;
  }

  auto result = all_tiles.find(name);
  if (result == all_tiles.end()) {
    ERR("Unknown tile [%s]", name);
    return nullptr;
  }

  return result->second;
}

Tilep string2tile(std::string &s, int *len)
{
  TRACE_NO_INDENT();
  auto        iter = s.begin();
  std::string name;

  while (iter != s.end()) {
    auto c = *iter;

    if ((c == '\0') || (c == '$')) {
      break;
    }

    name += c;
    iter++;
  }

  if (iter == s.end()) {
    ERR("Unknown tile [%s]", name.c_str());
  }

  if (len) {
    *len = iter - s.begin();
  }

  auto result = all_tiles.find(name);
  if (result == all_tiles.end()) {
    ERR("Unknown tile [%s]", name.c_str());
  }

  return result->second;
}

Tilep tile_index_to_tile(int i)
{
  if (unlikely(! i)) {
    return nullptr;
  }

  return all_tiles_array[ i - 1 ];
}

//
// Blits a whole tile. Y co-ords are inverted.
//
void tile_blit_colored_fat(Tilep tile, spoint tl, spoint br, color color_tl, color color_tr, color color_bl,
                           color color_br)
{
  float x1 = tile->x1;
  float x2 = tile->x2;
  float y1 = tile->y1;
  float y2 = tile->y2;

  blit_colored(tile->gl_binding(), x1, y2, x2, y1, tl.x, br.y, br.x, tl.y, color_tl, color_tr, color_bl, color_br);
}

std::string tile_name(Tilep t)
{
  TRACE_NO_INDENT();
  return t->name;
}

uint32_t tile_delay_ms(Tilep t)
{
  TRACE_NO_INDENT();

  if (! t->delay_ms) {
    return 5000;
  }
  return t->delay_ms;
}
void tile_delay_ms_set(Tilep t, uint32_t val)
{
  TRACE_NO_INDENT();
  t->delay_ms = val;
}

uint32_t tile_global_index(Tilep t)
{
  TRACE_NO_INDENT();
  return t->global_index;
}
void tile_global_index_set(Tilep t, uint32_t val)
{
  TRACE_NO_INDENT();
  t->global_index = val;
}

bool tile_is_loggable(Tilep t)
{
  TRACE_NO_INDENT();
  return t->is_loggable ? true : false;
}

bool tile_is_end_of_anim(Tilep t)
{
  TRACE_NO_INDENT();
  return t->is_end_of_anim ? true : false;
}

bool tile_is_cleanup_on_end_of_anim(Tilep t)
{
  TRACE_NO_INDENT();
  return t->is_cleanup_on_end_of_anim ? true : false;
}

void tile_is_cleanup_on_end_of_anim_set(Tilep t)
{
  TRACE_NO_INDENT();
  t->is_cleanup_on_end_of_anim = true;
}

bool tile_is_alive_on_end_of_anim(Tilep t)
{
  TRACE_NO_INDENT();
  return t->is_alive_on_end_of_anim ? true : false;
}

void tile_is_alive_on_end_of_anim_set(Tilep t)
{
  TRACE_NO_INDENT();
  t->is_alive_on_end_of_anim = true;
}

int Tile::gl_binding(void) const
{
  TRACE_NO_INDENT();
  if (g_monochrome) {
    return _gl_binding_monochrome;
  }
  return _gl_binding;
}

void Tile::set_gl_binding(int v)
{
  TRACE_NO_INDENT();
  _gl_binding = v;
}

int tile_gl_binding(Tilep t)
{
  TRACE_NO_INDENT();
  return t->gl_binding();
}

int Tile::gl_binding_monochrome(void) const
{
  TRACE_NO_INDENT();
  return _gl_binding_monochrome;
}

void Tile::set_gl_binding_monochrome(int v)
{
  TRACE_NO_INDENT();
  _gl_binding_monochrome = v;
}

int Tile::gl_binding_mask(void) const
{
  TRACE_NO_INDENT();
  return _gl_binding_mask;
}

void Tile::set_gl_binding_mask(int v)
{
  TRACE_NO_INDENT();
  _gl_binding_mask = v;
}

//
// Blits a whole tile. Y co-ords are inverted.
//
void tile_blit_outline(const Tilep &tile, float x1, float x2, float y1, float y2, const spoint tl, const spoint br,
                       const color &c, int single_pix_size, bool square)
{
  color outline = {10, 10, 10, 255};

  auto binding = tile->gl_binding_mask();

  if (single_pix_size) {
    int dx = single_pix_size - 1;
    int dy = single_pix_size - 1;

    if (! dx) {
      dx = 1;
    }
    if (! dy) {
      dy = 1;
    }

    if (square) {
      blit(binding, x1, y2, x2, y1, tl.x - dx, br.y - dy, br.x - dx, tl.y - dy, outline);
      blit(binding, x1, y2, x2, y1, tl.x + dx, br.y + dy, br.x + dx, tl.y + dy, outline);
      blit(binding, x1, y2, x2, y1, tl.x - dx, br.y + dy, br.x - dx, tl.y + dy, outline);
      blit(binding, x1, y2, x2, y1, tl.x + dx, br.y - dy, br.x + dx, tl.y - dy, outline);
    }
    blit(binding, x1, y2, x2, y1, tl.x + dx, br.y, br.x + dx, tl.y, outline);
    blit(binding, x1, y2, x2, y1, tl.x - dx, br.y, br.x - dx, tl.y, outline);
    blit(binding, x1, y2, x2, y1, tl.x, br.y + dy, br.x, tl.y + dy, outline);
    blit(binding, x1, y2, x2, y1, tl.x, br.y - dy, br.x, tl.y - dy, outline);
  }

  binding = tile->gl_binding();
  blit(binding, x1, y2, x2, y1, tl.x, br.y, br.x, tl.y, c);
}

void tile_blit_outline(const Tilep &tile, float x1, float x2, float y1, float y2, const spoint tl, const spoint br,
                       const color &c, const color &outline, int single_pix_size, bool square)
{
  auto binding = tile->gl_binding_mask();

  if (single_pix_size) {
    int dx = single_pix_size - 1;
    int dy = single_pix_size - 1;

    if (! dx) {
      dx = 1;
    }
    if (! dy) {
      dy = 1;
    }

    if (square) {
      blit(binding, x1, y2, x2, y1, tl.x - dx, br.y - dy, br.x - dx, tl.y - dy, outline);
      blit(binding, x1, y2, x2, y1, tl.x + dx, br.y + dy, br.x + dx, tl.y + dy, outline);
      blit(binding, x1, y2, x2, y1, tl.x - dx, br.y + dy, br.x - dx, tl.y + dy, outline);
      blit(binding, x1, y2, x2, y1, tl.x + dx, br.y - dy, br.x + dx, tl.y - dy, outline);
    }
    blit(binding, x1, y2, x2, y1, tl.x + dx, br.y, br.x + dx, tl.y, outline);
    blit(binding, x1, y2, x2, y1, tl.x - dx, br.y, br.x - dx, tl.y, outline);
    blit(binding, x1, y2, x2, y1, tl.x, br.y + dy, br.x, tl.y + dy, outline);
    blit(binding, x1, y2, x2, y1, tl.x, br.y - dy, br.x, tl.y - dy, outline);
  }

  binding = tile->gl_binding();
  blit(binding, x1, y2, x2, y1, tl.x, br.y, br.x, tl.y, c);
}

void tile_blit(const Tilep &tile, const spoint tl, const spoint br, const color &c)
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
  blit(binding, x1, y2, x2, y1, tl.x, br.y, br.x, tl.y, c);
}

void tile_blit(const Tilep &tile, float x1, float x2, float y1, float y2, const spoint tl, const spoint br, color c)
{
  blit(tile->gl_binding(), x1, y2, x2, y1, tl.x, br.y, br.x, tl.y, c);
}

void tile_blit_section_colored(const Tilep &tile, const fpoint &tile_tl, const fpoint &tile_br, const spoint tl,
                               const spoint br, color color_tl, color color_tr, color color_bl, color color_br)
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

//
// Shift the coordinates of a tile by a given percentage, so the bottom is
// trimmed and looks submerged.
//
void tile_submerge_pct(Gamep g, spoint &tl, spoint &br, float &x1, float &x2, float &y1, float &y2, float percent)
{
  float h1 = br.y - tl.y;
  float h2 = y2 - y1;

  float off1 = ((h1 / 100) * percent);
  float off2 = ((h2 / 100) * percent);

  tl.y += (int) off1;
  y2 -= off2;

  tl.y -= ((int) off1) / 2;
  br.y -= ((int) off1) / 2;

  //
  // Round back to the nearest pixel size
  //
  float pix = game_map_single_pix_size_get(g);
  auto  h   = br.y - tl.y;
  tl.y      = (int) (floor((float) tl.y / pix) * pix);
  br.y      = tl.y + h;
}
