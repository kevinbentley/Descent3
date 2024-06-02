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

 * $Logfile: /DescentIII/main/lib/uires.h $
 * $Revision: 19 $
 * $Date: 10/21/99 1:53p $
 * $Author: Kevin $
 *
 *	Resources
 *
 * $Log: /DescentIII/main/lib/uires.h $
 *
 * 19    10/21/99 1:53p Kevin
 * Mac Merge
 *
 * 18    7/06/99 5:52p Kevin
 * PXO & multiplayer fixes for the patch
 *
 * 17    5/20/99 10:50p Samir
 * changed way memory was allocated for strings in text items, empty
 * strings all point to same empty buffer for efficiency.
 *
 * 16    5/10/99 10:53p Ardussi
 * changes to compile on Mac
 *
 * 15    9/30/98 4:32p Samir
 * added snazzy text.
 *
 * 14    9/23/98 11:46a Samir
 * added static text saturation.
 *
 * 13    8/20/98 6:45p Samir
 * use const char for UITextItem create.
 *
 * 12    5/25/98 8:18p Samir
 * added function to get text pointer to text item.
 *
 * 11    5/01/98 6:24p Samir
 * added draw class field to draw for each resource.
 *
 * 10    3/13/98 11:51a Samir
 * default text color is black.
 *
 * 9     3/10/98 7:26p Samir
 * Fixed UIBitmapItem::get_chunked_bitmap.
 *
 * 8     3/05/98 6:40p Samir
 * Virtualized a lot of functions.
 *
 * 7     2/13/98 6:34p Samir
 * Added UIStatic class.
 *
 * 6     2/10/98 4:55p Samir
 * Added radio buttons.
 *
 * 5     1/30/98 7:04p Samir
 * Moved from ui.h and uilib.h.
 *
 * 4     1/18/98 4:22p Samir
 * Implemented new UIItem system.
 *
 * 3     1/02/98 12:50p Samir
 * Added font caps to UITextItem.
 *
 * 2     12/30/97 5:13p Samir
 * INitial revision
 *
 * $NoKeywords: $
 */

#ifndef UIRES_H
#define UIRES_H

#include "grdefs.h"
#include "bitmap.h"

enum tUIResClass { uiItem, uiTextItem, uiBitmapItem };

enum tUIDrawClass { uiDrawNormal, uiDrawAlphaSaturate, uiDrawFaded };

//	UIItem
//		the root class for all resource items

class UIItem {
public:
  UIItem(){};
  virtual ~UIItem(){};

  //	if returns false, then it didn't draw.
  virtual bool draw(int x, int y, tUIDrawClass draw_class = uiDrawNormal) { return false; };
  virtual bool draw(int x, int y, int w, int h) { return false; };
  virtual int width() { return 0; };
  virtual int height() { return 0; };
  virtual tUIResClass class_type() { return uiItem; };
  virtual void set_alpha(uint8_t alpha){};
  virtual uint8_t get_alpha() const { return 0; };
  virtual void set_color(ddgr_color col){};
  virtual ddgr_color get_color() const { return GR_BLACK; };
  virtual UIItem *CopyUIItem() { return NULL; };
};

//	UITextItem
//		used by user interface system, contains information about how to render
//		text.  allows for alpha, color and different fonts.

class UITextItem : public UIItem {
  friend void SetUITextItemText(UITextItem *uit, char *newtext, uint32_t color);

  uint8_t m_Alpha;      // alpha value of text.
  ddgr_color m_Color; // color of text.
  int m_Font;

  static int m_DefaultFont;
  static int m_Sat;

protected:
  char *m_Text;

public:
  static void SetDefaultFont(int font) { UITextItem::m_DefaultFont = font; }
  static void SetSaturationFactor(int sat) { UITextItem::m_Sat = sat; }
  static char dummy_str[4];

public:
  UITextItem() {
    m_Text = NULL;
    m_Alpha = 255;
    m_Color = GR_WHITE;
    m_Font = m_DefaultFont;
  };
  UITextItem(const char *text, ddgr_color color = GR_WHITE, uint8_t alpha = 255);
  UITextItem(int font, const char *text, ddgr_color color = GR_WHITE, uint8_t alpha = 255);
  virtual ~UITextItem();

  //	if returns false, then it didn't draw.
  virtual bool draw(int x, int y, tUIDrawClass draw_class = uiDrawNormal);
  virtual bool draw(int x, int y, int w, int h) { return draw(x, y); };
  virtual int width();
  virtual int height();
  virtual tUIResClass class_type() const { return uiTextItem; };
  virtual UIItem *CopyUIItem();

  //	set visual characteristics of text item
  virtual void set_alpha(uint8_t alpha) { m_Alpha = alpha; };
  virtual void set_color(ddgr_color col) { m_Color = col; };

  void set_font(int font) { m_Font = font; };

  //	get visual characteristics of text item
  virtual uint8_t get_alpha() const { return m_Alpha; };
  virtual ddgr_color get_color() const { return m_Color; };
  int get_font() const { return m_Font; };

  //	operators
  operator const char *() const { // access m_Text
    return m_Text;
  };

  const char *GetBuffer() const { return m_Text; };

  const UITextItem &operator=(const UITextItem &item);
};

#define UISNAZZYTEXTF_BLINKING 0x1
#define UISNAZZYTEXTF_RESERVED 0xffff0000

class UISnazzyTextItem : public UITextItem {
  unsigned m_flags;

  union {
    int i;
    float f;
  } m_internaldata;

  union {
    int i;
    float f;
  } m_data;

public:
  UISnazzyTextItem() { m_flags = m_data.i = m_internaldata.i = 0; };
  UISnazzyTextItem(unsigned flags, const char *text, ddgr_color color = GR_WHITE, uint8_t alpha = 255);
  UISnazzyTextItem(unsigned flags, int font, const char *text, ddgr_color color = GR_WHITE, uint8_t alpha = 255);

  void set_data(int data) { m_data.i = data; };
  void set_data(float data) { m_data.f = data; };

  void set_flags(unsigned flags);

  virtual bool draw(int x, int y, tUIDrawClass draw_class = uiDrawNormal);
  virtual UIItem *CopyUIItem();

  const UISnazzyTextItem &operator=(const UISnazzyTextItem &item);
};

//	UIBitmapItem
//		used by user interface system, contains information about how to render
//		text.  allows for alpha, color and different fonts.

class UIBitmapItem : public UIItem {
  bool m_IsValid;
  bool m_IsChunked; // is this a chunked bitmap?

  union {
    chunked_bitmap *chunk; // a chunked bitmap.
    int handle;            // a simple bitmap
  } m_Bitmap;              // a bitmap.

  uint8_t m_Alpha; // alpha value of text.

public:
  UIBitmapItem() {
    m_IsValid = false;
    m_Alpha = 255;
  };
  UIBitmapItem(chunked_bitmap *chunk, uint8_t alpha = 255) {
    m_IsValid = true;
    m_Bitmap.chunk = chunk;
    m_Alpha = alpha;
    m_IsChunked = true;
  };
  UIBitmapItem(int bm_handle, uint8_t alpha = 255) {
    m_IsValid = true;
    m_Alpha = alpha;
    m_IsChunked = false;
    m_Bitmap.handle = bm_handle;
  };
  virtual ~UIBitmapItem(){};

  //	if returns false, then it didn't draw.
  virtual bool draw(int x, int y, tUIDrawClass draw_class = uiDrawNormal);
  virtual bool draw(int x, int y, int w, int h) { return draw(x, y); };
  virtual int width();
  virtual int height();
  virtual tUIResClass class_type() const { return uiBitmapItem; };
  virtual UIItem *CopyUIItem();

  //	flag checking
  bool is_chunked() const { return m_IsChunked; };
  bool is_valid() const { return m_IsValid; };

  //	set visual characteristics of bitmap
  void set_chunked_bitmap(chunked_bitmap *chunk) {
    m_IsValid = true;
    m_IsChunked = true;
    m_Bitmap.chunk = chunk;
  };
  void set_bitmap(int bm_handle) {
    m_IsValid = true;
    m_IsChunked = false;
    m_Bitmap.handle = bm_handle;
  };
  virtual void set_alpha(uint8_t alpha) { // sets the alpha
    m_Alpha = alpha;
  };

  // get visual characteristics
  chunked_bitmap *get_chunked_bitmap() const { return (chunked_bitmap *)m_Bitmap.chunk; };
  int get_bitmap() const { return m_Bitmap.handle; };
  virtual uint8_t get_alpha() const { // gets alpha.
    return m_Alpha;
  };

  // const UIBitmapItem& UIBitmapItem::operator =(const UIBitmapItem& item);	// JCA made Mac compatible
  const UIBitmapItem &operator=(const UIBitmapItem &item);
};

//	UIPrimativeItem
//		used to render simple 2d backgrounds.

class UIPrimativeItem : public UIItem {
  ddgr_color color;
  uint8_t alpha;

public:
  UIPrimativeItem(ddgr_color col, uint8_t alph = 255) {
    color = col;
    alpha = alph;
  };

  virtual UIItem *CopyUIItem();

  virtual void set_color(ddgr_color col) { color = col; };
  virtual ddgr_color get_color() const { return color; };
  virtual void set_alpha(uint8_t alph) { alpha = alph; };
  virtual uint8_t get_alpha() const { return alpha; };

  // const UIPrimativeItem& UIPrimativeItem::operator =(const UIPrimativeItem& item)	// JCA made Mac compatible
  const UIPrimativeItem &operator=(const UIPrimativeItem &item) {
    color = item.color;
    alpha = item.alpha;
    return *this;
  };

  //	if returns false, then it didn't draw.
  virtual bool draw(int x, int y, tUIDrawClass draw_class = uiDrawNormal) { return false; };
  virtual bool draw(int x, int y, int w, int h);
};

#endif
