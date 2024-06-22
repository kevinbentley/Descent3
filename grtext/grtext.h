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

 * $Logfile: /DescentIII/Main/Lib/grtext.h $
 * $Revision: 25 $
 * $Date: 11/16/99 3:18p $
 * $Author: Samir $
 *
 *
 *
 * $Log: /DescentIII/Main/Lib/grtext.h $
 *
 * 25    11/16/99 3:18p Samir
 * added new data to font file and kept compatibility with D3 fonts:
 * tracking value.
 *
 * 24    4/17/99 6:16p Samir
 * added kerning and 4444 alphaed font support.
 *
 * 23    4/02/99 3:49p Kevin
 * Added profanity filter code
 *
 * 22    4/01/99 5:23p Samir
 * Added function to get character info.
 *
 * 21    3/02/99 6:26p Samir
 * added font template width and height functions.
 *
 * 20    2/21/99 6:39p Samir
 * added function to get ascii value of font character.
 *
 * 19    1/20/99 3:43a Jeff
 * added function to get clipping parameters
 *
 * 18    11/03/98 7:04p Samir
 * made Grtext_spacing global so word wrapper could access it.
 *
 * 17    10/22/98 2:41p Samir
 * made grtext_Puts public.
 *
 * 16    10/21/98 11:50p Samir
 * added prototype for advanced grtext get char info function.
 *
 * 15    10/16/98 1:54p Kevin
 * Changes for Demo Beta 4
 *
 * 14    9/24/98 2:56p Samir
 * added ability to format strings inside string.
 *
 * 13    9/08/98 10:27a Samir
 * added function to get text height.
 *
 * 12    6/23/98 5:04p Samir
 * added grtext_GetColor
 *
 * 11    4/27/98 3:46p Samir
 * scaling fonts.
 *
 * 10    4/18/98 2:08a Samir
 * extended text buffer.
 *
 * 9     2/13/98 6:37p Samir
 * Fixed tabs.
 *
 * 8     2/03/98 12:13p Samir
 * Font shadowing support added.
 *
 * 7     1/30/98 2:15p Samir
 * Allow for text saturation.
 *
 * 6     1/23/98 6:53p Samir
 * Added grtext_PutChar.
 *
 * 5     1/12/98 5:24p Samir
 * Fixed font reading and created font spew test function.
 *
 * 4     1/08/98 12:16p Samir
 * GetLineWidth now takes a const char *
 *
 * 3     12/30/97 5:23p Samir
 * More stuff.
 *
 * 2     12/29/97 5:50p Samir
 * Added ability to set text window.
 *
 * 1     12/29/97 3:24p Samir
 * Initial revision
 *
 * $NoKeywords: $
 */

#ifndef GRTEXT_H
#define GRTEXT_H

#include "pstypes.h"
#include "ddvid.h"

#define GRTEXT_BUFLEN 16384
#define GRTEXT_FORMAT_CHAR 0x2
#define GRTEXT_FORMAT_SCALAR 4 // value mulitplied to formatting value in string.

#define GRTEXTFLAG_SATURATE 1
#define GRTEXTFLAG_SHADOW 2

struct tFontTemplate;

extern int Grtext_spacing;

//	sets text clipping parameters
void grtext_SetParameters(int left, int top, int right, int bottom, int tabspace = 4);

//	gets text clipping parameters
void grtext_GetParameters(int *left, int *top, int *right, int *bottom, int *tabspace);

//	 clears text buffer. doesn't render.
void grtext_Reset();

// sets the color for text
void grtext_SetColor(ddgr_color col);

//	returns color set by grtext_SetColor (does not count intra-string color changes)
ddgr_color grtext_GetColor();

//	sets fancy color for text
void grtext_SetFancyColor(ddgr_color col1, ddgr_color col2, ddgr_color col3, ddgr_color col4);

//	sets the alpha value for text
void grtext_SetAlpha(uint8_t alpha);

//	gets font alpha
uint8_t grtext_GetAlpha();

// toggles text saturation
void grtext_SetFlags(int flags);

// sets the font for text
void grtext_SetFont(int font_handle);

//	sets font scale (1.0 = normal, 0.5 = 1/2, 2.0 = twice as large.
void grtext_SetFontScale(float scale);

// gets the current font
int grtext_GetFont();

// returns the height of a string in current font.
int grtext_GetTextHeight(const char *str);
#define grtext_GetHeight(_s) grtext_GetTextHeight(_s)

// returns height of text using a font template
int grtext_GetTextHeightTemplate(tFontTemplate *ft, const char *str);
#define grtext_GetHeightTemplate(_t, _s) grtext_GetTextHeightTemplate(_t, _s)

//	returns width of text in current font.
int grtext_GetTextLineWidth(const char *str);
#define grtext_GetLineWidth(_s) grtext_GetTextLineWidth(_s)

// returns width of text using a font template
int grtext_GetTextLineWidthTemplate(const tFontTemplate *ft, const char *str);
#define grtext_GetLineWidthTemplate(_t, _s) grtext_GetTextLineWidthTemplate(_t, _s)

//	puts a formatted string in the text buffer
void grtext_Printf(int x, int y, const char *fmt, ...);

//	puts a string on the buffer
void grtext_Puts(int x, int y, const char *str);

//	puts a character down
void grtext_PutChar(int x, int y, int ch);

//	puts a centered string in the text buffer.
void grtext_CenteredPrintf(int xoff, int y, const char *fmt, ...);

//	renders all text in buffer and clears buffer.  USUALLY CALL THIS TO RENDER TEXT
void grtext_Flush();

//	renders all text but DOESN'T flush buffer
void grtext_Render();

// gets character information for the current string
//		ch is a SINGLE CHARACTER
//		col is the color of the current string as reported through formatting, or GR_NULL if no info
//		x is the old x before call and the new potential adjusted x after the call.
//		newline if it's a newline.
//		line start x;
struct tGetCharInfo {
  int sx; // this will not be modified. the initial x on the same line as the string

  ddgr_color col; // these values will be modified
  int x, w;       // x of char, and width of char.
  bool newline;   // reached a newline?
  bool font_char; // character exists in font?
  char ch;
};

const char *grtext_GetChar(const char *str, tGetCharInfo *ci);

//////////////////////////////////////////////////////////////////////////////
//	font functions!

// we can load a font template into this structure.  call grfont_FreeTemplate(tFontTemplate) to free memory here.
struct tFontTemplate {
  uint16_t min_ascii, max_ascii;
  uint8_t *ch_widths;
  uint8_t *kern_data;
  uint8_t ch_height;
  uint8_t ch_maxwidth;  // max width of character in font.
  bool proportional;  // is this font proportional? if so use array of widths, else use maxwidth
  bool uppercase;     // uppercase font?
  bool monochromatic; // font is monochromatic?
  bool newstyle;      // new style 4444 font.
  bool ffi2;          // new font info added.

  // ffi2 style (font file info 2)
  int8_t ch_tracking; // global tracking for font.
};

//	clears out font buffer.
void grfont_Reset();

//	returns a handle to a loaded font.
int grfont_Load(const char *fname);

//	frees a loaded font
void grfont_Free(int handle);

// loads a font template
bool grfont_LoadTemplate(const char *fname, tFontTemplate *ft);

// frees a font template
void grfont_FreeTemplate(tFontTemplate *ft);

//	returns a character's width
int grfont_GetCharWidth(int font, int ch);

//	returns a font's height
int grfont_GetHeight(int font);

//	returns a character's width
int grfont_GetKernedSpacing(int font, int ch1, int ch2);

//	returns a character's width
int grfont_GetKernedSpacingTemp(const tFontTemplate *ft, int ch1, int ch2);

// converts a key code to ascii version, and checks if in font.  converts lowercase to upper if font
// doesn't have a lowercase set.  useful alternative to ddio_KeyToAscii.
int grfont_KeyToAscii(int font, int key);

// returns the raw bitmap data for a character in a font, its width and height
// returned data should be in 565 hicolor format if (*mono) is false.  if (*mono) is true,
//	then a bitmask will be returned, and you should treat a bit as a pixel.
uint16_t *grfont_GetRawCharacterData(int font, int ch, int *w, int *h, bool *mono);

/////////////////////////////////////////////////////////////////////
// EDITING FUNCTIONS ONLY

// sets a template to a font, be careful.
bool grfont_SetTemplate(const char *pathname, const tFontTemplate *ft);

// sets a font's template without saving...
bool grfont_SetKerning(int font, uint8_t *kern_data);

// sets a font's tracking
bool grfont_SetTracking(int font, int tracking);
int grfont_GetTracking(int font);

/////////////////////////////////////////////////////////////////////

// Init functions -- call before anything is rendered!
void grtext_Init(void);

#ifndef RELEASE
void grfont_Spew(int font, int x, int y);
#endif

struct tFontFileInfo2 // to maintain compatibility with older fonts (64 bytes long)
{
  int16_t tracking;
  char reserved[62];
};

//	font data structure internal to library but available for font editors
struct tFontFileInfo {
  int16_t width, height; // width of widest character and height of longest char
  int16_t flags;         // flags used by the character renderer
  int16_t baseline;      // pixels given to lowercase below script line start at baseline
  uint8_t min_ascii;     // minimum ascii value used by font
  uint8_t max_ascii;     // max ascii value used by the font
  int16_t byte_width;    // width of a character in the font in bytes
  uint8_t *raw_data;     // pixel, map data.
  uint8_t **char_data;   // pointers to each character
  uint8_t *char_widths;  // individual pixel widths of each character
  uint8_t *kern_data;    // kerning information for specific letter combos

  // FFI2 (newstyle) data
  tFontFileInfo2 ffi2;

  //	misc.
  float brightness; // this IS NOT in the file, but a part of the baseline element. (upper 8bits)
};

#define FT_COLOR 1
#define FT_PROPORTIONAL 2
#define FT_KERNED 4
#define FT_GRADIENT 8
#define FT_FMT4444 16
#define FT_FFI2 32 // all fonts made after D3 should have this flag set.

#endif
