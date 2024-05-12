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

 * $Logfile: /DescentIII/Main/lib/grdefs.h $
 * $Revision: 8 $
 * $Date: 10/21/98 11:54p $
 * $Author: Samir $
 *
 *
 *
 * $Log: /DescentIII/Main/lib/grdefs.h $
 *
 * 8     10/21/98 11:54p Samir
 * added GR_NULL
 *
 * 7     5/06/98 4:33p Samir
 * added fixed screen width and height to grdefs.h (default res.)
 *
 * 6     4/23/98 6:38p Jason
 * made bitmaps use 1555 format
 *
 * 5     12/29/97 5:50p Samir
 * Moved GR_COLOR_CHAR to grdefs.h from gr.h.
 *
 * 4     12/22/97 7:39p Samir
 * Moved color constants from gr.h to grdefs.h
 *
 * 3     12/22/97 7:34p Samir
 * Added transparent color info.
 *
 * $NoKeywords: $
 */

#ifndef GRDEFS_H
#define GRDEFS_H

#include "pstypes.h"

//	bit depth info
#define BPP_TO_BYTESPP(x) (((x) + 7) >> 3)

#define BPP_DEFAULT 0 // default for current display
#define BPP_8 8       // 8-bit paletted.
#define BPP_15 15     // 5-5-5 + chroma Hicolor
#define BPP_16 16     // 5-6-5 Hicolor
#define BPP_24 24     // 24 bit true color
#define BPP_32 32     // 32 bit true color

#define FIXED_SCREEN_WIDTH 640
#define FIXED_SCREEN_HEIGHT 480

//	transparent color constant here.
#define OPAQUE_FLAG16 0x8000
#define TRANSPARENT_COLOR32 0x0000FF00
#define NEW_TRANSPARENT_COLOR 0x0000
#define OPAQUE_FLAG OPAQUE_FLAG16

//	a new color definition
typedef uint32_t ddgr_color;

// Color constants
static constexpr ddgr_color GR_NULL = 0xffffffff, // don't do a thing with this.
    GR_BLACK = 0x00000000, GR_GREEN = 0x0000ff00, GR_RED = 0x00ff0000, GR_BLUE = 0x000000ff, GR_DARKGRAY = 0x00404040,
                        GR_LIGHTGRAY = 0x00c0c0c0, GR_WHITE = 0x00ffffff;

#define GR_COLOR_CHAR 1 // ASCII 1 and (r,g,b) changes current text color in string.

//	MACROS
static inline ddgr_color GR_RGB(int r, int g, int b) { return ((r << 16) + (g << 8) + b); }

static inline uint16_t GR_RGB16(int r, int g, int b) { return (((r >> 3) << 10) + ((g >> 3) << 5) + (b >> 3)); }

static inline uint16_t GR_COLOR_TO_16(ddgr_color c) {
  int r, g, b;
  r = ((c & 0x00ff0000) >> 16);
  g = ((c & 0x0000ff00) >> 8);
  b = (c & 0x000000ff);

  return (uint16_t)(((r >> 3) << 10) + ((g >> 3) << 5) + (b >> 3));
}

static inline int GR_COLOR_RED(ddgr_color c) {
  int r = ((c & 0x00ff0000) >> 16);
  return (int)r;
}

static inline int GR_COLOR_GREEN(ddgr_color c) {
  int g = ((c & 0x0000ff00) >> 8);
  return (int)g;
}

static inline int GR_COLOR_BLUE(ddgr_color c) {
  int b = (c & 0x000000ff);
  return (int)b;
}

static inline ddgr_color GR_16_TO_COLOR(uint16_t col) {
  int r, g, b;

  r = (col & 0x7c00) >> 7;
  g = (col & 0x03e0) >> 2;
  b = (col & 0x001f) << 3;

  return GR_RGB(r, g, b);
}

#endif
