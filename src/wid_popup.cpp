//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_main.hpp"
#include "my_ui.hpp"
#include "my_wid_popup.hpp"

WidPopup::~WidPopup()
{
  TRACE_NO_INDENT();

  extern Gamep game;
  auto         g = game;

  LOG("~WidPopup");
  wid_destroy_nodelay(g, &wid_popup_container);
  delete wid_text_area;
}

WidPopup::WidPopup(Gamep g, const std::string vname, spoint vtl, spoint vbr, Tilep vtitle_tile,
                   const std::string vbackground, bool horiz_scroll, bool vert_scoll, int scroll_height)
    : tl(vtl), br(vbr), title_tile(vtitle_tile), background(vbackground)
{
  TRACE_NO_INDENT();

  outer_w = br.x - tl.x;
  outer_h = br.y - tl.y;

  int width  = outer_w;
  int height = outer_h;

  this->name = vname;

  spoint inner_tl = spoint(0, 0);
  spoint inner_br = spoint(width, height);
  inner_w         = inner_br.x - inner_tl.x;
  inner_h         = inner_br.y - inner_tl.y;

  int tile_size;
  if (title_tile) {
    tile_size = 4;
  } else {
    tile_size = 0;
  }

  if (title_tile) {
    inner_h -= tile_size;
    inner_tl.y += tile_size;
  }

  {
    wid_popup_container = wid_new_square_window(g, "wid_popup " + this->name);
    wid_set_pos(wid_popup_container, tl, br);
    wid_set_style(wid_popup_container, UI_WID_STYLE_SPARSE_NONE);
    if (background != "") {
      wid_set_tile(TILE_LAYER_BG_0, wid_popup_container, tile_find_mand(background));
    } else {
      wid_set_style(wid_popup_container, UI_WID_STYLE_NORMAL);
    }
  }

  if (title_tile) {
    auto w       = wid_new_square_button(g, wid_popup_container, "wid title " + this->name);
    wid_title    = w;
    auto title_x = (outer_w - tile_size) / 2;
    wid_set_pos(w, spoint(title_x + 0, 1), spoint(title_x + tile_size - 1, tile_size));
    wid_set_style(w, UI_WID_STYLE_NORMAL);
    wid_set_style(w, UI_WID_STYLE_SPARSE_NONE);
    wid_set_tile(TILE_LAYER_FG_0, w, title_tile);
  }

  {
    spoint box_tl(0, tile_size);
    spoint box_br(inner_w, inner_h + tile_size);
    wid_text_area = new WidTextBox(g, box_tl, box_br, wid_popup_container, horiz_scroll, vert_scoll, scroll_height);
  }

  wid_update(g, wid_popup_container);
}

//
// Log a message to the popup
//
Widp WidPopup::log(Gamep g, std::string s, wid_text_format format, std::string col)
{
  TRACE_NO_INDENT();

  return wid_text_area->log(g, s, format, col);
}

//
// Log a blank line to the popup
//
Widp WidPopup::log_empty_line(Gamep g)
{
  TRACE_NO_INDENT();

  return wid_text_area->log_empty_line(g);
}

//
// Get rid of trailing empty lines
//
void WidPopup::compress(Gamep g)
{
  TRACE_NO_INDENT();

  int utilized = wid_text_area->line_count;

  wid_resize(g, wid_popup_container, -1, utilized + 1);
  wid_resize(g, wid_text_area->wid_text_area, -1, utilized + 1);
  wid_resize(g, wid_text_area->wid_text_box_container, -1, utilized + 1);

  //
  // We don't need a scrollbar if we've not exceeded size limits
  //
  if (utilized < inner_h) {
    if (wid_text_area->wid_vert_scroll) {
      wid_hide(g, wid_text_area->wid_vert_scroll);
      wid_hide(g, wid_get_parent(wid_text_area->wid_vert_scroll));
    }
  }
}
