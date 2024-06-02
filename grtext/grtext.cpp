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

 * $Logfile: /DescentIII/Main/grtext/grtext.cpp $
 * $Revision: 38 $
 * $Date: 11/16/99 3:18p $
 * $Author: Samir $
 *
 *
 *
 * $Log: /DescentIII/Main/grtext/grtext.cpp $
 *
 * 38    11/16/99 3:18p Samir
 * added new data to font file and kept compatibility with D3 fonts:
 * tracking value.
 *
 * 37    10/21/99 9:27p Jeff
 * B.A. Macintosh code merge
 *
 * 36    5/02/99 7:16p Samir
 * fixed text line width problem with newline chars.
 *
 * 35    5/02/99 1:50a Samir
 * fixed nasty bug where intrastring text colors weren't getting set due
 * to a change in how we do color for text now.
 *
 * 34    4/26/99 6:56p Kevin
 * doh! forgot the 0 termination
 *
 * 33    4/26/99 6:55p Kevin
 * added some more naughty words
 *
 * 32    4/24/99 8:41p Samir
 * fixed clipped text scaling probs.
 *
 * 31    4/17/99 6:16p Samir
 * added kerning and 4444 alphaed font support.
 *
 * 30    4/13/99 4:39p Samir
 * simplified color scheme.
 *
 * 29    4/09/99 3:16p Kevin
 * Fixed a stupid memory leak
 *
 * 28    4/02/99 3:49p Kevin
 * Added profanity filter code
 *
 * 27    3/02/99 6:26p Samir
 * added font template width and height functions.
 *
 * 26    1/20/99 3:47a Jeff
 * added function to get clipping parameters
 *
 * 25    11/03/98 7:04p Samir
 * made Grtext_spacing global so word wrapper could access it.
 *
 * 24    11/01/98 1:58a Jeff
 * converted the vsprintf calls to use the Pvsprintf, which is a safe
 * vsprintf, no buffer overflows allowed
 *
 * 23    10/22/98 2:41p Samir
 * made grtext_Puts public.
 *
 * 22    10/19/98 10:42p Jason
 * made Int3s into breaks
 *
 * 21    9/24/98 2:56p Samir
 * added ability to format strings inside string.
 *
 * 20    9/21/98 2:58p Samir
 * may have fixed GetTextHeight function.
 *
 * 19    9/18/98 11:29a Samir
 * use strchr instead of strtok.
 *
 * 18    9/08/98 5:42p Samir
 * fixed memory leak
 *
 * 17    9/08/98 10:27a Samir
 * added function to get text height.
 *
 * 16    9/04/98 3:22p Samir
 * newlines handled a bit better.
 *
 * 15    8/24/98 3:12p Samir
 * fixed text clipping
 *
 * 14    6/23/98 5:05p Samir
 * streamlined strlen calls
 *
 * 13    5/15/98 5:35p Samir
 * fixed instring text color formatting.
 *
 * 12    5/05/98 6:29p Samir
 * spaces don't render, just width of it counts.
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
 * 8     2/03/98 12:20p Samir
 * Be sure to set alphatype when Grtext_SetFlags operation occurs.
 *
 * 7     2/03/98 12:13p Samir
 * Font shadowing support added.
 *
 * 6     1/30/98 2:15p Samir
 * Allow for text saturation.
 *
 * 5     1/23/98 6:53p Samir
 * Added grtext_PutChar.
 *
 * 4     1/08/98 12:16p Samir
 * GetLineWidth now takes a const char *
 *
 * 3     12/30/97 5:20p Samir
 * Some stuff.
 *
 * 2     12/29/97 5:49p Samir
 * Added centering text capability.
 *
 * 1     12/29/97 3:24p Samir
 * Initial revision
 *
 * $NoKeywords: $
 */

#include "grtext.h"

#include <cstdarg>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cctype>

#include "grtextlib.h"

#include "renderer.h"
#include "pserror.h"

#define CLIP_LEFT Grtext_left
#define CLIP_TOP Grtext_top
#define CLIP_RIGHT Grtext_right
#define CLIP_BOTTOM Grtext_bottom

//	Text opcodes
#define GRTEXTOP_PUTS 0x1       // 2 shorts, x and y
#define GRTEXTOP_SETCOLOR 0x2   // 1 ddgr_color
#define GRTEXTOP_FANCYCOLOR 0x3 // 4 ddgr_colors
#define GRTEXTOP_SETFONT 0x4    // 1 font handle (int)
#define GRTEXTOP_SETALPHA 0x5   // 1 uint8_t
#define GRTEXTOP_PUTCHAR 0x6    // (2 shorts) 1 uint8_t
#define GRTEXTOP_SETFLAGS 0x7   // (flags) = 1 int.
#define GRTEXTOP_SCALE 0x8      // 1 float (scale) scale current font.

//	Text execution buffer
int Grtext_spacing = 1;
static char Grtext_buffer[GRTEXT_BUFLEN];
static int Grtext_ptr = 0;
static int Grtext_font = 0;
static uint8_t Grtext_alpha = 255;
static int8_t Grtext_alphatype = ATF_TEXTURE + ATF_CONSTANT;
static bool Grtext_shadow = false;
static int Grtext_line_spacing = 1;
static int Grtext_tabspace = 0;
static int Grtext_left, Grtext_top, Grtext_right, Grtext_bottom;
static ddgr_color Grtext_colors[2];
static float Grtext_scale = 1.0f;
static ddgr_color Grtext_color = GR_BLACK;

//	draws a string
static void grtext_RenderString(int x, int y, char *str);
static void grtext_DrawTextLine(int x, int y, char *str);
static void grtext_DrawTextLineClip(int x, int y, char *str);

#define XORVAL 205
#define MAX_BAD_WORD_LEN 10
typedef uint8_t badword[MAX_BAD_WORD_LEN];
// These all need to be lower case!
static badword bad_words[] = {
    // These are just XOR'd with XORVAL
    {0xab, 0xb8, 0xae, 0xa6, 0x00},                   // = fuck
    {0xbe, 0xa5, 0xa4, 0xb9, 0x00},                   // = shit
    {0xae, 0xb8, 0xa3, 0xb9, 0x00},                   // = cunt
    {0xba, 0xa5, 0xa2, 0xbf, 0xa8, 0x00},             // = whore
    {0xac, 0xbe, 0xbe, 0xa5, 0xa2, 0xa1, 0xa8, 0x00}, // = asshole
    {0xa9, 0xac, 0xa0, 0xa3, 0x00},                   // = damn
    {0xbd, 0xb8, 0xbe, 0xbe, 0xb4, 0x00},             // pussy
    {0xaf, 0xa4, 0xb9, 0xae, 0xa5, 0x00},             // bitch
    {0xa9, 0xac, 0xa0, 0xa3, 0x00},                   // damn
    {0xbd, 0xa4, 0xbe, 0xbe, 0x00}                    // piss
};

#define NUM_BAD_WORDS (sizeof(bad_words) / sizeof(badword))

static const char subst_chars[] = "#!&@&#%*";

#define NUM_SUBST_CHARS (sizeof(subst_chars) - 1)

static bool grtext_FilterProfanity = false;

void grtext_SetProfanityFilter(bool enabled) { grtext_FilterProfanity = enabled; }
// Right now this just decrypts the bad words
void grtext_Init(void) {
  for (int i = 0; i < NUM_BAD_WORDS; i++) {
    int pos = 0;

    while (bad_words[i][pos]) {
      bad_words[i][pos] = bad_words[i][pos] ^ XORVAL;
      pos++;
    }
  }
}

//	macro to get character width
static inline int CHAR_WIDTH(int font, int ch) { return (int)(grfont_GetCharWidth(font, ch) * Grtext_scale); }

static inline int CHAR_HEIGHT(int font) { return (int)(grfont_GetHeight(font) * Grtext_scale); }

static inline int CHAR_SPACING(int font, int ch1, int ch2) { return (int)(grfont_GetKernedSpacing(font, ch1, ch2)); }

//	macro to get character width
static inline int CHAR_WIDTH_TEMP(const tFontTemplate *ft, int ch) {
  if (ch > ft->max_ascii && ft->uppercase) {
    ch = toupper(ch);
  } else if (ch < ft->min_ascii || ch > ft->max_ascii) {
    return 0;
  }

  return (int)((ft->proportional) ? ft->ch_widths[ch - ft->min_ascii] : ft->ch_maxwidth);
}

static inline int CHAR_HEIGHT_TEMP(const tFontTemplate *ft) { return (int)ft->ch_height; }

static inline int CHAR_SPACING_TEMP(const tFontTemplate *ft, int ch1, int ch2) {
  if (ch1 > ft->max_ascii && ft->uppercase) {
    ch1 = toupper(ch1);
  }
  if (ch2 > ft->max_ascii && ft->uppercase) {
    ch2 = toupper(ch2);
  }

  return (int)(grfont_GetKernedSpacingTemp(ft, ch1, ch2));
}

//	 clears text buffer. doesn't render.
void grtext_Reset() {
  Grtext_buffer[0] = 0;
  Grtext_ptr = 0;
  Grtext_alpha = 255;
  Grtext_scale = 1.0f;
  Grtext_spacing = 1;
  grtext_SetFlags(0);
  grtext_SetColor(GR_BLACK);
}

//	sets text clipping parameters
void grtext_SetParameters(int left, int top, int right, int bottom, int tabspace) {
  Grtext_left = left;
  Grtext_top = top;
  Grtext_right = right;
  Grtext_bottom = bottom;
  Grtext_tabspace = tabspace;
}

//	gets text clipping parameters
void grtext_GetParameters(int *left, int *top, int *right, int *bottom, int *tabspace) {
  if (left)
    *left = Grtext_left;
  if (top)
    *top = Grtext_top;
  if (right)
    *right = Grtext_right;
  if (bottom)
    *bottom = Grtext_bottom;
  if (tabspace)
    *tabspace = Grtext_tabspace;
}

// sets the color for text
void grtext_SetColor(ddgr_color col) {
  struct {
    char op;
    ddgr_color col;
  } cmd;

  ASSERT((Grtext_ptr + sizeof(cmd)) < GRTEXT_BUFLEN);

  cmd.op = GRTEXTOP_SETCOLOR;
  cmd.col = col;

  memcpy(&Grtext_buffer[Grtext_ptr], &cmd, sizeof(cmd));
  Grtext_ptr += sizeof(cmd);
  Grtext_color = col;
}

//	returns color set by grtext_SetColor (does not count intra-string color changes)
ddgr_color grtext_GetColor() { return Grtext_color; }

//	sets font scale (1.0 = normal, 0.5 = 1/2, 2.0 = twice as large.
void grtext_SetFontScale(float scale) {
  struct {
    char op;
    float scale;
  } cmd;

  ASSERT((Grtext_ptr + sizeof(cmd)) < GRTEXT_BUFLEN);

  cmd.op = GRTEXTOP_SCALE;
  cmd.scale = scale;

  memcpy(&Grtext_buffer[Grtext_ptr], &cmd, sizeof(cmd));
  Grtext_ptr += sizeof(cmd);

  Grtext_scale = scale;
}

//	sets fancy color for text
void grtext_SetFancyColor(ddgr_color col1, ddgr_color col2, ddgr_color col3, ddgr_color col4) {
  struct {
    char op;
    //	ddgr_color col[4];
    ddgr_color col;
  } cmd;

  ASSERT((Grtext_ptr + sizeof(cmd)) < GRTEXT_BUFLEN);

  cmd.op = GRTEXTOP_FANCYCOLOR;
  cmd.col = col1;

  memcpy(&Grtext_buffer[Grtext_ptr], &cmd, sizeof(cmd));
  Grtext_ptr += sizeof(cmd);
}

//	sets the alpha value for text
void grtext_SetAlpha(uint8_t alpha) {
  struct {
    char op;
    uint8_t alpha;
  } cmd;

  ASSERT((Grtext_ptr + sizeof(cmd)) < GRTEXT_BUFLEN);
  cmd.op = GRTEXTOP_SETALPHA;
  cmd.alpha = alpha;
  Grtext_alpha = alpha;

  memcpy(&Grtext_buffer[Grtext_ptr], &cmd, sizeof(cmd));
  Grtext_ptr += sizeof(cmd);
}

//	gets font alpha
uint8_t grtext_GetAlpha() { return Grtext_alpha; }

// toggles text saturation
void grtext_SetFlags(int flags) {
  struct {
    char op;
    int flags;
  } cmd;

  ASSERT((Grtext_ptr + sizeof(cmd)) < GRTEXT_BUFLEN);

  cmd.op = GRTEXTOP_SETFLAGS;
  cmd.flags = flags;

  memcpy(&Grtext_buffer[Grtext_ptr], &cmd, sizeof(cmd));
  Grtext_ptr += sizeof(cmd);
}

// sets the font for text
void grtext_SetFont(int font_handle) {
  struct {
    char op;
    int handle;
  } cmd;

  ASSERT((Grtext_ptr + sizeof(cmd)) < GRTEXT_BUFLEN);
  cmd.op = GRTEXTOP_SETFONT;
  cmd.handle = font_handle;
  Grtext_font = cmd.handle;
  Grtext_spacing = 1 + grfont_GetTracking(Grtext_font);

  memcpy(&Grtext_buffer[Grtext_ptr], &cmd, sizeof(cmd));
  Grtext_ptr += sizeof(cmd);
}

//	puts a formatted string in the text buffer
void grtext_Printf(int x, int y, const char *fmt, ...) {
  std::va_list arglist;
  int len;
  char buf[512];

  va_start(arglist, fmt);
  len = std::vsnprintf(buf, 512, fmt, arglist);
  va_end(arglist);
  if (len < 0)
    return;

  grtext_Puts(x, y, buf);
}

// gets the current font
int grtext_GetFont() { return Grtext_font; }

//	puts a centered string in the text buffer.
void grtext_CenteredPrintf(int xoff, int y, const char *fmt, ...) {
  int new_x;
  std::va_list arglist;
  int len;
  char buf[512];

  va_start(arglist, fmt);
  len = std::vsnprintf(buf, 512, fmt, arglist);
  va_end(arglist);
  if (len < 0)
    return;

  new_x = Grtext_left + (Grtext_right - Grtext_left) / 2 - grtext_GetTextLineWidth(buf) / 2;

  grtext_Puts(new_x + xoff, y, buf);
}

#define GR_STR_LEN 128
//	draws a string
void grtext_Puts(int x, int y, const char *str) {
  struct {
    char op;
    int16_t x, y;
  } cmd;

  ASSERT((Grtext_ptr + sizeof(cmd) + strlen(str) + 1) < GRTEXT_BUFLEN);

  cmd.op = GRTEXTOP_PUTS;
  cmd.x = (int16_t)x;
  cmd.y = (int16_t)y;

  ASSERT((Grtext_ptr + sizeof(cmd) + strlen(str) + 1) < GRTEXT_BUFLEN);

  cmd.op = GRTEXTOP_PUTS;
  cmd.x = (int16_t)x;
  cmd.y = (int16_t)y;
  memcpy(&Grtext_buffer[Grtext_ptr], &cmd, sizeof(cmd));
  Grtext_ptr += sizeof(cmd);
  strcpy(&Grtext_buffer[Grtext_ptr], str);

  if (grtext_FilterProfanity) {
    // DAJ changed to local to reduce memory thrashing
    // DAJ		char *lowerstr = (char *)mem_malloc(strlen(str)+1);
    char lowerstr[GR_STR_LEN];

    int slen = strlen(str);
    if (slen >= GR_STR_LEN)
      slen = GR_STR_LEN - 1;

    for (int a = 0; a < slen; a++)
      lowerstr[a] = tolower(str[a]);

    lowerstr[slen] = '\0';

    for (int i = 0; i < NUM_BAD_WORDS; i++) {
      char *p = strstr(lowerstr, (char *)bad_words[i]);
      while (p) {
        int len = strlen((char *)bad_words[i]);
        char *realp = (char *)((int)(p - lowerstr) + &Grtext_buffer[Grtext_ptr]);
        for (int a = 0; a < len; a++) {
          ASSERT(p);
          *realp = subst_chars[(*realp) % NUM_SUBST_CHARS];
          *p = *realp;
          realp++;
        }
        p = strstr(lowerstr, (char *)bad_words[i]);
      };
    }
    // DAJ		mem_free(lowerstr);
  }

  Grtext_ptr += (strlen(str) + 1);
}

//	puts a character down
void grtext_PutChar(int x, int y, int ch) {
  struct {
    char op;
    int16_t x, y;
    uint8_t ch;
  } cmd;

  ASSERT((Grtext_ptr + sizeof(cmd)) < GRTEXT_BUFLEN);

  cmd.op = GRTEXTOP_PUTCHAR;
  cmd.x = (int16_t)x;
  cmd.y = (int16_t)y;
  cmd.ch = (uint8_t)ch;
  memcpy(&Grtext_buffer[Grtext_ptr], &cmd, sizeof(cmd));
  Grtext_ptr += sizeof(cmd);
}

//	renders all text in buffer and clears buffer.  USUALLY CALL THIS TO RENDER TEXT
void grtext_Flush() {
  grtext_Render();
  grtext_Reset();
}

//	renders all text but DOESN'T flush buffer
void grtext_Render() {
  //	setup rendering of text.
  rend_SetTextureType(TT_LINEAR);
  rend_SetOverlayType(OT_NONE);
  rend_SetFiltering(0);
  rend_SetLighting(LS_FLAT_GOURAUD);
  rend_SetAlphaType(ATF_TEXTURE + ATF_CONSTANT);
  rend_SetColorModel(CM_MONO);
  rend_SetZBufferState(0);
  rend_SetAlphaValue(Grtext_alpha);

  //	render text.
  int pos = 0;

  while (pos < Grtext_ptr) {
    switch (Grtext_buffer[pos]) {
    case GRTEXTOP_SETCOLOR: {
      struct {
        char op;
        ddgr_color col;
      } cmd;

      memcpy(&cmd, &Grtext_buffer[pos], sizeof(cmd));
      pos += sizeof(cmd);
      rend_SetFlatColor(cmd.col);
      //	rend_SetCharacterParameters(cmd.col, cmd.col, cmd.col, cmd.col);
      Grtext_colors[0] = cmd.col;
      //	Grtext_colors[1] = cmd.col[1];
      //	Grtext_colors[2] = cmd.col[2];
      //	Grtext_colors[3] = cmd.col[3];
    } break;

    case GRTEXTOP_SETFLAGS: {
      struct {
        char op;
        int flags;
      } cmd;

      memcpy(&cmd, &Grtext_buffer[pos], sizeof(cmd));
      pos += sizeof(cmd);

      if (cmd.flags & GRTEXTFLAG_SATURATE)
        Grtext_alphatype = AT_SATURATE_TEXTURE;
      else
        Grtext_alphatype = ATF_CONSTANT + ATF_TEXTURE;
      rend_SetAlphaType(Grtext_alphatype);

      if (cmd.flags & GRTEXTFLAG_SHADOW)
        Grtext_shadow = true;
      else
        Grtext_shadow = false;
    } break;

    case GRTEXTOP_FANCYCOLOR: {
      struct {
        char op;
        //	ddgr_color col[4];
        ddgr_color col;
      } cmd;

      memcpy(&cmd, &Grtext_buffer[pos], sizeof(cmd));
      pos += sizeof(cmd);
      rend_SetFlatColor(cmd.col);
      //	rend_SetCharacterParameters(cmd.col[0], cmd.col[1], cmd.col[2], cmd.col[3]);
      Grtext_colors[0] = cmd.col;
      //	Grtext_colors[1] = cmd.col[1];
      //	Grtext_colors[2] = cmd.col[2];
      //	Grtext_colors[3] = cmd.col[3];
    } break;

    case GRTEXTOP_SETALPHA: {
      struct {
        char op;
        uint8_t alpha;
      } cmd;

      memcpy(&cmd, &Grtext_buffer[pos], sizeof(cmd));
      pos += sizeof(cmd);
      rend_SetAlphaValue(cmd.alpha);
    } break;

    case GRTEXTOP_SETFONT: {
      struct {
        char op;
        int handle;
      } cmd;

      memcpy(&cmd, &Grtext_buffer[pos], sizeof(cmd));
      pos += sizeof(cmd);
      Grtext_font = cmd.handle;
    } break;

    case GRTEXTOP_PUTS: {
      struct {
        char op;
        int16_t x, y;
      } cmd;

      memcpy(&cmd, &Grtext_buffer[pos], sizeof(cmd));
      pos += sizeof(cmd);
      if (Grtext_shadow) {
        //	rend_SetCharacterParameters(0,0,0,0);
        rend_SetFlatColor(0);
        grtext_RenderString(cmd.x + 1, cmd.y + 1, &Grtext_buffer[pos]);
        rend_SetFlatColor(Grtext_colors[0]);
        //	rend_SetCharacterParameters(Grtext_colors[0],Grtext_colors[1],Grtext_colors[2],Grtext_colors[3]);
      }
      grtext_RenderString(cmd.x, cmd.y, &Grtext_buffer[pos]);
      pos += (strlen(&Grtext_buffer[pos]) + 1);
    } break;

    case GRTEXTOP_PUTCHAR: {
      tCharBlt cbi;
      struct {
        char op;
        int16_t x, y;
        uint8_t ch;
      } cmd;

      memcpy(&cmd, &Grtext_buffer[pos], sizeof(cmd));
      pos += sizeof(cmd);
      cbi.ch = cmd.ch;
      cbi.clipped = false; // if =1, use sx,sy,sw,sh
      cbi.x = cmd.x;
      cbi.y = cmd.y;
      if (Grtext_shadow) {
        //	rend_SetCharacterParameters(0,0,0,0);
        rend_SetFlatColor(0);
        cbi.x += 1;
        cbi.y += 1;
        grfont_BltChar(Grtext_font, &cbi);
        rend_SetFlatColor(Grtext_colors[0]);
        //	rend_SetCharacterParameters(Grtext_colors[0],Grtext_colors[1],Grtext_colors[2],Grtext_colors[3]);
        cbi.x -= 1;
        cbi.y -= 1;
      }
      grfont_BltChar(Grtext_font, &cbi);
    } break;

    case GRTEXTOP_SCALE: {
      struct {
        char op;
        float scale;
      } cmd;

      memcpy(&cmd, &Grtext_buffer[pos], sizeof(cmd));
      pos += sizeof(cmd);
      Grtext_scale = cmd.scale;
    } break;

    default:
      Int3(); // Truly bad.
    }
  }

  //	restore original state
  rend_SetFiltering(1);
  rend_SetZBufferState(1);
}

//	draws a string
void grtext_RenderString(int x, int y, char *str) {
  int cur_x = x, cur_y = y, gx, gy;
  char *line = str, *save_pos;

  do {
    // Look for newline, and if found, put in a 0 to terminate the line
    save_pos = strchr(line, '\n');
    if (save_pos)    // found an newline
      *save_pos = 0; // terminate the line

    int line_width;
    int clipped;

    line_width = grtext_GetTextLineWidth(line);

    gy = cur_y;
    gx = cur_x; // Clip function needs global coords.

    clipped = 0;
    if ((CLIP_TOP > (gy + CHAR_HEIGHT(Grtext_font))) || (CLIP_BOTTOM < gy))
      clipped = 2;
    else if ((CLIP_LEFT > (gx + line_width)) || (CLIP_RIGHT < gx))
      clipped = 2;

    if (clipped != 2) {
      if (CLIP_LEFT > gx || CLIP_RIGHT < (gx + line_width))
        clipped = 1;
      if (CLIP_TOP > gy || CLIP_BOTTOM < (gy + CHAR_HEIGHT(Grtext_font)))
        clipped = 1;

      if (clipped == 0)
        grtext_DrawTextLine(gx, gy, line);
      else if (clipped == 1)
        grtext_DrawTextLineClip(gx, gy, line);
    }
    cur_y += (Grtext_line_spacing + CHAR_HEIGHT(Grtext_font));
    cur_x = CLIP_LEFT;

    // replace the newline, if there was one
    if (save_pos)
      *save_pos++ = '\n';

    line = save_pos;

  } while (line);
}

int grtext_GetTextHeightTemplate(tFontTemplate *ft, const char *str) {
  int cur_h = 0;
  const char *spos = str;

  do {
    cur_h += (Grtext_line_spacing + CHAR_HEIGHT_TEMP(ft));

    spos = strchr(spos, '\n');
    if (spos)
      spos++;
  } while (spos);

  return cur_h;
}

int grtext_GetTextHeight(const char *str) {
  int cur_h = 0;
  const char *spos = str;

  do {
    cur_h += (Grtext_line_spacing + CHAR_HEIGHT(Grtext_font));

    spos = strchr(spos, '\n');
    if (spos)
      spos++;
  } while (spos);

  return cur_h;
}

int grtext_GetTextLineWidth(const char *str) {
  int line_width = 0, max_width = 0;
  int rgb_define_mode = 0;
  int strsize = strlen(str);
  int line_idx = 0;

  for (int i = 0; i < strsize; i++) {
    int width;
    char ch = str[i], ch2 = str[i + 1];

    // note that if we hit the GR_COLOR_CHAR then the next three values should
    //	not count when defining the width of the line.
    if (rgb_define_mode == 3)
      rgb_define_mode = 0;
    else if (ch == GR_COLOR_CHAR)
      rgb_define_mode = 1;
    if (!rgb_define_mode) {
      if (ch == '\t') { // tab char
        int space_width;
        space_width = (CHAR_WIDTH(Grtext_font, ' ') + Grtext_spacing) * Grtext_tabspace;
        line_width = (line_width + space_width) / space_width * space_width;
      } else if (ch == GRTEXT_FORMAT_CHAR) {
        if ((i + 1) >= strsize)
          break;
        line_width = ((int)str[i + 1] * GRTEXT_FORMAT_SCALAR);
        i++;
      } else if (ch == '\n') {
        if (line_width > max_width) {
          max_width = line_width;
        }
        line_width = 0;
      } else {
        width = CHAR_WIDTH(Grtext_font, ch);
        line_width += (width + Grtext_spacing + CHAR_SPACING(Grtext_font, ch, ch2));
      }
    } else
      rgb_define_mode++;
  }

  if (line_width > max_width) {
    max_width = line_width;
  }
  return (max_width) ? max_width - Grtext_spacing : 0;
}

// returns width of text using a font template
int grtext_GetTextLineWidthTemplate(const tFontTemplate *ft, const char *str) {
  int max_width = 0, i, line_width = 0, strsize = strlen(str);
  int rgb_define_mode = 0;

  for (i = 0; i < strsize; i++) {
    int width;
    char ch = str[i], ch2 = str[i + 1];

    // note that if we hit the GR_COLOR_CHAR then the next three values should
    //	not count when defining the width of the line.
    if (rgb_define_mode == 3)
      rgb_define_mode = 0;
    else if (ch == GR_COLOR_CHAR)
      rgb_define_mode = 1;
    if (!rgb_define_mode) {
      if (ch == '\t') { // tab char
        int space_width;
        space_width = (CHAR_WIDTH_TEMP(ft, ' ') + Grtext_spacing) * Grtext_tabspace;
        line_width = (line_width + space_width) / space_width * space_width;
      } else if (ch == GRTEXT_FORMAT_CHAR) {
        if ((i + 1) >= strsize)
          break;
        line_width = ((int)str[i + 1] * GRTEXT_FORMAT_SCALAR);
        i++;
      } else if (ch == '\n') {
        if (line_width > max_width) {
          max_width = line_width;
        }
        line_width = 0;
      } else {
        width = CHAR_WIDTH_TEMP(ft, ch);
        line_width += (width + Grtext_spacing + CHAR_SPACING_TEMP(ft, ch, ch2));
      }
    } else
      rgb_define_mode++;
  }

  if (max_width < line_width) {
    max_width = line_width;
  }
  return (max_width) ? max_width - Grtext_spacing : 0;
}

/*	These internal routines just draw a line of text.  depending on the function
        we clip or don't clip
*/
void grtext_DrawTextLineClip(int x, int y, char *str) {
  int ch_y, ch_x, ch_w, ch_h;   // what part of the character to draw
  int i, cur_x, draw_x, draw_y; // where to draw character section
  int h;
  tCharBlt cbi;
  int strsize = strlen(str);

  /*	by clipping, we should first determine what our vertical clipping is.  then
          go through each character in the line and determine what is totally clipped,
          partially clipped and by how much, and not clipped at all and draw accordingly
  */
  h = CHAR_HEIGHT(Grtext_font);
  ch_y = 0;
  ch_h = h;
  draw_y = y;
  //	determine each character bitmap y and height to blt.
  if (CLIP_TOP >= y) {
    ch_y = CLIP_TOP - y;
    draw_y = CLIP_TOP;
  }
  if (CLIP_BOTTOM < (y + CHAR_HEIGHT(Grtext_font))) {
    ch_h = CLIP_BOTTOM - y;
  }
  ch_h = ch_h - ch_y; // do this to clip both top and bottom

  cur_x = x;
  for (i = 0; i < strsize; i++) {
    uint8_t ch, ch2;
    int w;
    ch = (uint8_t)str[i];
    ch2 = (uint8_t)str[i + 1];

    w = CHAR_WIDTH(Grtext_font, ch);

    if (ch == GR_COLOR_CHAR) {
      ddgr_color col;
      if ((i + 3) >= strsize)
        break; // This shouldn't happen!  bad string!
      col = GR_RGB(str[i + 1], str[i + 2], str[i + 3]);
      rend_SetFlatColor(col);
      //	rend_SetCharacterParameters(col, col, col, col);
      i += 3;
    } else if (ch == '\t') { // tab char
      int space_width;
      space_width = (CHAR_WIDTH(Grtext_font, ' ') + Grtext_spacing) * Grtext_tabspace;
      cur_x = (cur_x + space_width) / space_width * space_width;
    } else if (((cur_x + w) < CLIP_LEFT) || (cur_x > CLIP_RIGHT)) {
      cur_x += (Grtext_spacing + w);
    } else if (ch == GRTEXT_FORMAT_CHAR) {
      if ((i + 1) >= strsize)
        break; // This shouldn't happen!  bad string!
      cur_x = x + ((int)str[i + 1] * GRTEXT_FORMAT_SCALAR);
      i++;
    } else if (ch == ' ') {
      cur_x += (CHAR_WIDTH(Grtext_font, ' ') + Grtext_spacing + CHAR_SPACING(Grtext_font, ch, ch2));
    } else {
      ch_x = 0;
      ch_w = w;
      draw_x = cur_x;
      if (CLIP_LEFT > cur_x) {
        ch_x = CLIP_LEFT - cur_x;
        draw_x = CLIP_LEFT;
      }
      if (CLIP_RIGHT < (cur_x + w)) {
        ch_w = CLIP_RIGHT - cur_x;
      }
      ch_w = ch_w - ch_x;

      if (ch_x == 0 && ch_w == w && ch_y == 0 && ch_h == h) {
        cbi.ch = ch;
        cbi.clipped = false; // if =1, use sx,sy,sw,sh
        cbi.x = draw_x;
        cbi.y = draw_y;
        cbi.dsw = cbi.dsh = Grtext_scale;
      } else {
        cbi.ch = ch;
        cbi.clipped = true; // if =1, use sx,sy,sw,sh
        cbi.x = draw_x;
        cbi.y = draw_y;
        cbi.dsw = cbi.dsh = Grtext_scale; // this should be useless since ch_w and ch_h are scaled values
        cbi.sx = ch_x;
        cbi.sy = ch_y;
        cbi.sw = ch_w;
        cbi.sh = ch_h;
      }
      cur_x = grfont_BltChar(Grtext_font, &cbi);
      cur_x += (Grtext_spacing + CHAR_SPACING(Grtext_font, ch, ch2));
    }
  }
}

void grtext_DrawTextLine(int x, int y, char *str) {
  int i, cur_x;
  tCharBlt cbi;
  int strsize = strlen(str);

  /*	by clipping, we should first determine what our vertical clipping is.  then
          go through each character in the line and determine what is totally clipped,
          partially clipped and by how much, and not clipped at all and draw accordingly

          perform string drawing without viewport clipping.
          supports bitmap fonts or color(alpha) mapped fonts.
  */
  cur_x = x;
  for (i = 0; i < strsize; i++) {
    uint8_t ch, ch2;
    int w;
    ch = (uint8_t)str[i];
    ch2 = (uint8_t)str[i + 1];
    w = CHAR_WIDTH(Grtext_font, ch);

    if (ch == GR_COLOR_CHAR) {
      ddgr_color col;
      if ((i + 3) >= strsize)
        break; // This shouldn't happen!  bad string!
      col = GR_RGB(str[i + 1], str[i + 2], str[i + 3]);
      rend_SetFlatColor(col);
      //			rend_SetCharacterParameters(col, col, col, col);
      i += 3;
    } else if (ch == '\t') { // tab char
      int space_width;
      space_width = (CHAR_WIDTH(Grtext_font, ' ') + Grtext_spacing) * Grtext_tabspace;
      cur_x = (cur_x + space_width) / space_width * space_width;
    } else if (ch == GRTEXT_FORMAT_CHAR) {
      if ((i + 1) >= strsize)
        break; // This shouldn't happen!  bad string!
      cur_x = x + ((int)str[i + 1] * GRTEXT_FORMAT_SCALAR);
      i++;
    } else if (ch == ' ') {
      cur_x += (CHAR_WIDTH(Grtext_font, ' ') + Grtext_spacing);
    } else {
      cbi.ch = ch;
      cbi.clipped = false; // if =1, use sx,sy,sw,sh
      cbi.x = cur_x;
      cbi.y = y;
      cbi.dsw = cbi.dsh = Grtext_scale;
      cur_x = grfont_BltChar(Grtext_font, &cbi);
      cur_x += (Grtext_spacing + CHAR_SPACING(Grtext_font, ch, ch2));
    }
  }
}
