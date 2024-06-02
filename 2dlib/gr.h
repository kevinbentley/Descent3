/*
* Descent 3 
* Copyright (C) 2024 Parallax Software
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.

--- HISTORICAL COMMENTS FOLLOW ---

 * $Logfile: /DescentIII/Main/Lib/gr.h $
 * $Revision: 18 $
 * $Date: 4/17/99 6:15p $
 * $Author: Samir $
 *
 * the 2d lib main header
 *
 * $Log: /DescentIII/Main/Lib/gr.h $
 *
 * 18    4/17/99 6:15p Samir
 * replaced gr.h with grdefs.h and fixed resulting compile bugs.
 *
 * 17    4/14/99 3:59a Jeff
 * fixed case mismatches in #includes
 *
 * 16    11/30/98 5:50p Jason
 * added 4444 bitmap support
 *
 * 15    12/29/97 5:50p Samir
 * Moved GR_COLOR_CHAR to grdefs.h from gr.h.
 *
 * 14    12/22/97 7:39p Samir
 * Moved color constants from gr.h to grdefs.h
 *
 * 13    12/22/97 7:13p Samir
 * Moved constants to grdefs.h
 *
 * 12    12/19/97 12:33p Samir
 * Added alpha for text and took out abilitiy to create viewports inside
 * viewports.
 *
 * 11    12/12/97 6:40p Samir
 * Some viewport font functions.
 *
 * 10    11/16/97 6:54p Samir
 * Added font::get_name function.
 *
 * 9     11/16/97 2:20p Samir
 * Added macro to draw a bitmap to a viewport.
 *
 * 8     11/11/97 1:27p Samir
 * Added functions to set text alpha values.
 *
 * 7     11/04/97 4:57p Samir
 * Added get_text_color.
 *
 * 6     10/13/97 3:56p Jason
 * made a better 3d bitmap system
 *
 * 5     10/03/97 11:59a Samir
 * Added some color constants.
 *
 * 4     9/19/97 5:37p Samir
 * Software font coloring works.
 *
 * 1     6/23/97 9:25p Samir
 * added because source safe sucks
 *
 * 39    6/16/97 3:01p Samir
 * Changed font system to work better with renderer.  Fonts are rendered
 * on bitmaps of 128x128 at load time.
 *
 * 38    6/12/97 6:30p Samir
 * DDGR v2.0 Changes in 2d system implemented.
 *
 * 37    6/09/97 3:47p Jason
 * fixed some color mapping problems
 *
 * 36    5/21/97 3:39p Jason
 * added terrain editing stuff
 *
 * 35    5/21/97 1:08p Samir
 * added conversion from 565 to ddgr_color format.
 *
 * 34    5/15/97 2:08p Samir
 * Added grSurface::get_surface_desc and grViewport::get_parent.
 *
 * 33    5/13/97 6:36p Samir
 * added lock_clear functions.
 *
 *
 * $NoKeywords: $
 */

#ifndef _GR_H
#define _GR_H

#include "ddgr.h"
#include "fix.h"
#include "pserror.h"
#include "pstypes.h"

class grMemorySurface;
class grViewport;
class grSurface;
class grPen;

//	a 'pen' structure used by the 2d system to draw things.
struct gr_pen {
  char *data;
  int rowsize;
  ddgr_color rgbcolor;
  ddgr_color color;
  ddgr_surface *sf;
};

enum grTextAlign { // used to align text along viewport
  grTextUnjustified,
  grTextLeft,
  grTextCentered,
  grTextRight,
  grTextWordWrap
};

struct tCharProperties {
  uint8_t alpha;
  ddgr_color col[4];
};

#define GR_VPCP_ALPHA 1 // alpha value is valid in CharProperties
#define GR_VPCP_COLOR 2 // color values are valid in CharProperties.
#define GR_VPCP_ALL (1 + 2)

//	----------------------------------------------------------------------------
//	class grFont
//		will load and manage a font's capabilities.
//		all fonts are stored in a 16bit hicolor format, or bitmasked.
//	----------------------------------------------------------------------------

const int MAX_FONTS = 16, MAX_FONT_BITMAPS = 12;

#define DEFAULT_FONT 0

struct gr_font_file_record {
  int16_t width, height;      // width of widest character and height of longest char
  int16_t flags;              // flags used by the character renderer
  int16_t baseline;           // pixels given to lowercase below script line start at baseline
  uint8_t min_ascii;          // minimum ascii value used by font
  uint8_t max_ascii;          // max ascii value used by the font
  int16_t byte_width;         // width of a character in the font in bytes
  uint8_t *raw_data;          // pixel, map data.
  uint8_t **char_data;        // pointers to each character
  int16_t *char_widths;       // individual pixel widths of each character
  uint8_t *kern_data; // kerning information for specific letter combos
};

struct gr_font_record {
  char name[32];
  char filename[32];          // filename of font
  int references;             // number of references of that font
  int bmps[MAX_FONT_BITMAPS]; // font bitmap handles
  grMemorySurface *surfs[MAX_FONT_BITMAPS];
  uint8_t *ch_u, *ch_v, *ch_w, *ch_h, *ch_surf;
  float *ch_uf, *ch_vf, *ch_wf, *ch_hf;
  gr_font_file_record font;

};

class grFont {
  static gr_font_record m_FontList[MAX_FONTS];
  static grMemorySurface *m_CharSurf;

  int m_FontHandle; // offset into m_FontList

public:
  grFont();
  ~grFont();
  grFont(const grFont &font) { m_FontHandle = font.m_FontHandle; };

  const grFont &operator=(const grFont &font) {
    m_FontHandle = font.m_FontHandle;
    return *this;
  };

public: // Manipulation functions
  static void init_system();
  static void close_system();
  static int register_font(char *fontname, char *filename);

  void init(const char *fontname);
  void free();

  //	draw_char returns the next x value taking spacing and kerning into consideration.
  int draw_char(grSurface *sf, int x, int y, int ch, tCharProperties *chprop);
  int draw_char(grSurface *sf, int x, int y, int ch, int sx, int sy, int sw, int sh, tCharProperties *chprop);

private:
  static void free_font(gr_font_record *ft);

  static void load(char *filename, int slot);
  static void translate_to_surfaces(int slot);
  static void translate_mono_char(grSurface *sf, int x, int y, int index, gr_font_file_record *ft, int width);

  uint8_t *get_kern_info(uint8_t c1, uint8_t c2);
  void charblt16(grSurface *dsf, ddgr_color col, int dx, int dy, grSurface *ssf, int sx, int sy, int sw, int sh);

public: // Accessor functions
  char *get_name() const {
    if (m_FontHandle == -1)
      return NULL;
    else
      return m_FontList[m_FontHandle].name;
  };
  int min_ascii() const {
    ASSERT(m_FontHandle > -1);
    return m_FontList[m_FontHandle].font.min_ascii;
  };
  int max_ascii() const {
    ASSERT(m_FontHandle > -1);
    return m_FontList[m_FontHandle].font.max_ascii;
  };
  int height() const {
    ASSERT(m_FontHandle > -1);
    return m_FontList[m_FontHandle].font.height;
  };
  int get_char_info(int ch, int *width);
};

//	----------------------------------------------------------------------------
//	class grSurface
//		contains a ddgr_bitmap object and allows for blting
//	----------------------------------------------------------------------------

struct ddgr_surface_node {
  ddgr_surface *sf;
  ddgr_surface_node *prev;
};

const int SURFTYPE_MEMORY = 256;

const int SURFFLAG_RENDERER = 256; // SURFACE will use renderer functions.

class grSurface {
public:
  static void init_system(); // initializes some global stuff for surface system
  static void close_system();

private:
  friend class grViewport;
  int surf_Locked;     // same value for all grViewport objects
  int m_SurfInit;      // surface initialized
  char *m_OrigDataPtr; // non-adjusted data pointer
  char *m_DataPtr;     // adjusted data pointer
  int m_DataRowsize;   // Data rowsize

  static ddgr_surface_node *surf_list;     // the surface list
  static ddgr_surface_node *surf_list_cur; // current node on list.
  static ddgr_surface *scratch_mem_surf;   // use as temporary memory surface

private:
  //	coversion blts.
  void xlat8_16(char *data, int w, int h, char *pal);
  void xlat16_16(char *data, int w, int h, int format = 0);
  void xlat16_24(char *data, int w, int h);
  void xlat24_16(char *data, int w, int h);
  void xlat32_16(char *data, int w, int h);

  void uniblt(int dx, int dy, grSurface *ssf, int sx, int sy, int sw, int sh);

protected:
  ddgr_surface ddsfObj; // Used to call ddgr_surf_ functions

protected:
  void add_to_list(ddgr_surface *sf); // used for surface heap management
  void remove_from_list(ddgr_surface *sf);

  int surf_init() const { return m_SurfInit; };
  void surf_init(int init) { m_SurfInit = init; };

public:
  grSurface();
  virtual ~grSurface();

  //	creates a surface, allocates memory based off of parameters.
  grSurface(int w, int h, int bpp, unsigned type, unsigned flags = 0, const char *name = NULL);

public:
  unsigned get_flags() const { return ddsfObj.flags; };

  void create(int w, int h, int bpp, unsigned type, unsigned flags = 0, const char *name = NULL);

  void load(char *data, int w, int h, int bpp, int format = 0);
  void load(int handle);
  void load(char *data, int w, int h, char *pal);
  void load(int handle, char *pal);

  void free(); // non-dynamic version

  int width() const {
    ASSERT(m_SurfInit);
    return ddsfObj.w;
  };
  int height() const {
    ASSERT(m_SurfInit);
    return ddsfObj.h;
  };
  int bpp() const {
    ASSERT(m_SurfInit);
    return ddsfObj.bpp;
  };
  unsigned flags() const {
    ASSERT(m_SurfInit);
    return ddsfObj.flags;
  };

  int rowsize() const {
    ASSERT(m_SurfInit);
    return m_DataRowsize;
  };
  char *data() const {
    ASSERT(m_SurfInit);
    return m_DataPtr;
  };

  void clear(ddgr_color col = 0);
  void clear(int l, int t, int w, int h, ddgr_color col = 0);
  void replace_color(ddgr_color sc, ddgr_color dc);

  void blt(int dx, int dy, grSurface *ssf);
  void blt(int dx, int dy, grSurface *ssf, int sx, int sy, int sw, int sh);

  char *lock(int *rowsize);
  char *lock(int x, int y, int *rowsize);
  void unlock();

  void get_surface_desc(ddgr_surface *surf) { *surf = ddsfObj; };

  //	This is VERY system dependent when called, sorry but I think this may be necessary
  void attach_to_window(unsigned handle);
};

//	----------------------------------------------------------------------------
//	class grMemorySurface
//		this is a software bitmap not video driver dependant
//	----------------------------------------------------------------------------

class grMemorySurface : public grSurface {
  bool m_FirstTimeInit; // do special stuff if we are initializing for first time
  bool m_AllowInit;     // we only allow initialization if we didn't create it.

public:
  grMemorySurface();
  virtual ~grMemorySurface();

  //	allocates a surface from system memory (quicker version of grSurface)
  grMemorySurface(int w, int h, int bpp, unsigned flags = 0, const char *name = NULL);

  //	initializes a surface using a bitmap handle (no allocation)
  grMemorySurface(int bm);

  //	inititalizes a surface using raw data,width,rowsize info information.
  bool init(int w, int h, int bpp, char *data, int rowsize, unsigned flags = 0, const char *name = NULL);
};

//	----------------------------------------------------------------------------
//	class grHardwareSurface
//		this is a hardware bitmap allocated from the video driver
//	----------------------------------------------------------------------------

class grHardwareSurface : public grSurface {
public:
  grHardwareSurface();
  grHardwareSurface(int w, int h, int bpp, unsigned flags = 0, const char *name = NULL);
  virtual ~grHardwareSurface();

  bool create(int w, int h, int bpp, unsigned flags = 0, const char *name = NULL);
};

//	----------------------------------------------------------------------------
//	class grScreen
//		child class of grSurface.   Handles initializing the screen, and
//		is used by the grViewport class to draw onto the screen
//	----------------------------------------------------------------------------

class grScreen : public grSurface {
  friend class grViewport;

public:
  grScreen(int w, int h, int bpp, const char *name = NULL);
  virtual ~grScreen();

  void flip();
};

//	----------------------------------------------------------------------------
//	class grViewport
//		a viewport is a bounded rectangle on either a screen or bitmap.
//		one should be able to draw any 2d object on a viewport region.
//	----------------------------------------------------------------------------

//	contains state information for a viewport.
struct tVPState {
  grFont font;
  int text_spacing;
  int text_line_spacing;
  tCharProperties chprops;
};

class grViewport {
  static int vp_Locked;             // tells us if any viewport is locked
  static grViewport *vp_Current_VP; // current locked viewport

  grFont text_Font;
  int text_Spacing;
  int text_Line_spacing;
  tCharProperties char_Props;

private:
  void draw_text(grTextAlign align, int x, int y, char *str);
  void draw_text_line(int x, int y, char *str);
  void draw_text_line_clip(int x, int y, char *str);
  int clip_line(int &l, int &t, int &r, int &b);
  int clip_rect(int &x1, int &y1, int &x2, int &y2);

protected:
  int vp_Left, vp_Top, vp_Right, // viewport's global screen/bitmap bounds
      vp_Bottom;

  int vp_InitLeft, vp_InitTop, vp_InitRight, vp_InitBottom; // viewport's initial global screen coords

  grSurface *sf_Parent; // bitmap where viewport points to
  gr_pen pen_Obj;

public:
  grViewport(grScreen *scr_parent);
  grViewport(grSurface *sf_parent);
  ~grViewport();

  grSurface *get_parent() const { return sf_Parent; };

  //	these are the viewport's initial bounds with respect to parent surface
  //	these can't be changed.
  int width() const { return (vp_InitRight - vp_InitLeft) + 1; };
  int height() const { return (vp_InitBottom - vp_InitTop) + 1; };
  int left() const { return vp_InitLeft; };
  int top() const { return vp_InitTop; };
  int right() const { return vp_InitRight; };
  int bottom() const { return vp_InitBottom; };

  //	these clipping coordinates are local to the viewports initial rectangle, based off
  //	of parent surface.  All 2d functions use these coords to base their drawing.
  //	If we draw at (0,0) and the clip region is at (80,90,200,160) then we will draw at 80,90.
  int clip_width() const { return (vp_Right - vp_Left) + 1; };
  int clip_height() const { return (vp_Bottom - vp_Top) + 1; };
  int clip_left() const { return vp_Left; };
  int clip_top() const { return vp_Top; };
  int clip_right() const { return vp_Right; };
  int clip_bottom() const { return vp_Bottom; };
  void set_clipping_rect(int left, int top, int right, int bottom);

  //	these convert local viewport coords to global screen/surface coords
  int global_x(int lx) const { return vp_InitLeft + vp_Left + lx; };
  int global_y(int ly) const { return vp_InitTop + vp_Top + ly; };
  int local_x(int gx) const { return gx - vp_Left - vp_InitLeft; };
  int local_y(int gy) const { return gy - vp_Top - vp_InitTop; };

  //	these functions set and restore the state of the viewport (font, colors, etc.)
  void get_state(tVPState *state);
  void set_state(const tVPState *state);

  //	bltting functions on viewport
  void clear(ddgr_color col = 0);      // clear with background color
  void lock_clear(ddgr_color col = 0); // software clear.  must be used in lock
  void lock_clear(ddgr_color col, int l, int t, int w, int h);
  void blt(int dx, int dy, grSurface *ssf);
  void blt(int dx, int dy, grSurface *ssf, int sx, int sy, int sw, int sh);

public:
  grSurface *lock(); // lock and
  void unlock();     // unlock  (implicitly locks surface)

  friend grSurface *VP_GET_DRAWING_SURFACE();
  friend void VP_BEGIN_DRAWING(grViewport *vp);
  friend void VP_END_DRAWING();

  //	these functions only work on locked surfaces.
  void hline(ddgr_color, int x1, int x2, int y1);
  void line(ddgr_color color, int x1, int y1, int x2, int y2);
  void rect(ddgr_color color, int l, int t, int r, int b);
  void fillrect(ddgr_color color, int l, int t, int r, int b);
  void setpixel(ddgr_color col, int x, int y);
  void setpixelc(ddgr_color col, int x, int y);
  ddgr_color getpixel(int x, int y);
  ddgr_color getpixelc(int x, int y);
  void circle(ddgr_color col, int xc, int yc, int r);
  void fillcircle(ddgr_color col, int xc, int yc, int r);
  //	end

public:
  //	These functions only work on locked surfaces
  int printf(grTextAlign align, int x, int y, char *fmt, ...);
  int printf(int x, int y, char *fmt, ...);
  int puts(grTextAlign align, int x, int y, char *str);
  int puts(int x, int y, char *str);

  //	text formatting functions
public:
  int get_text_line_width(char *text);
  void set_font(const char *fontname);
  void get_font(char *fontname, int size);
  int get_current_font_height() const { return text_Font.height(); };
  int get_text_spacing() const { return text_Spacing; };
  int get_text_line_spacing() const { return text_Line_spacing; };
  void set_text_spacing(int spacing) { text_Spacing = spacing; };
  void set_text_line_spacing(int spacing) { text_Line_spacing = spacing; };

  //	visual properties of text functions
public:
  void set_text_color(ddgr_color color);
  ddgr_color get_text_color() const;
  void set_char_properties(unsigned flags, const tCharProperties *props);
  void get_char_properties(tCharProperties *props) const;
  //	end
};

//	inline definitions for grViewport functions

inline void grViewport::set_text_color(ddgr_color color) {
  char_Props.col[0] = color;
  char_Props.col[1] = color;
  char_Props.col[2] = color;
  char_Props.col[3] = color;
}

inline ddgr_color grViewport::get_text_color() const { return char_Props.col[0]; }

inline void grViewport::set_char_properties(unsigned flags, const tCharProperties *props) {
  if (flags & GR_VPCP_COLOR) {
    char_Props.col[0] = props->col[0];
    char_Props.col[1] = props->col[1];
    char_Props.col[2] = props->col[2];
    char_Props.col[3] = props->col[3];
  }
  if (flags & GR_VPCP_ALPHA) {
    char_Props.alpha = props->alpha;
  }
}

inline void grViewport::get_char_properties(tCharProperties *props) const {
  props->col[0] = char_Props.col[0];
  props->col[1] = char_Props.col[1];
  props->col[2] = char_Props.col[2];
  props->col[3] = char_Props.col[3];
  props->alpha = char_Props.alpha;
}

//	useful macros

static inline void VP_BITBLT(grViewport *vp, int dx, int dy, int bm) {
  grMemorySurface surf(bm);
  vp->blt(dx, dy, &surf);
}

#endif
