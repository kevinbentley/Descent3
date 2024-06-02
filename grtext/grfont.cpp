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

 * $Logfile: /DescentIII/Main/grtext/grfont.cpp $
 * $Revision: 25 $
 * $Date: 11/16/99 4:56p $
 * $Author: Samir $
 *
 *
 *
 * $Log: /DescentIII/Main/grtext/grfont.cpp $
 *
 * 25    11/16/99 4:56p Samir
 * upped max texture count per font.
 *
 * 24    11/16/99 3:18p Samir
 * added new data to font file and kept compatibility with D3 fonts:
 * tracking value.
 *
 * 23    8/10/99 5:11p Jeff
 * close open files
 *
 * 22    6/08/99 5:45p Samir
 * correctly take care of values about 128 when character passed to
 * grfont_GetCharWidth
 *
 * 21    4/24/99 8:41p Samir
 * fixed clipped text scaling probs.
 *
 * 20    4/17/99 6:16p Samir
 * added kerning and 4444 alphaed font support.
 *
 * 19    4/14/99 1:15a Jeff
 * fixed case mismatched #includes
 *
 * 18    4/01/99 5:23p Samir
 * Added function to get character info.
 *
 * 17    3/02/99 6:26p Samir
 * added font template width and height functions.
 *
 * 16    2/21/99 6:39p Samir
 * added function to get ascii value of font character.
 *
 * 15    10/16/98 1:54p Kevin
 * Changes for Demo Beta 4
 *
 * 14    5/22/98 12:44p Samir
 * fixed grayscale conversion bug.
 *
 * 13    5/15/98 5:36p Samir
 * reset references count of font when freeing.
 *
 * 12    5/08/98 5:23p Samir
 * added font brightness and grayscale caps.
 *
 * 11    5/01/98 3:09p Samir
 * properly translate monochrome fonts to 555 output.
 *
 * 10    4/27/98 3:46p Samir
 * scaling fonts.
 *
 * 9     4/24/98 8:00a Samir
 * hopefully fixed font pixel format translation to 555 problem.
 *
 * 8     4/23/98 6:38p Jason
 * made bitmaps use 1555 format
 *
 * 7     4/15/98 12:10p Samir
 * commented out unnecessary mprints.
 *
 * 6     3/31/98 3:49p Jason
 * added memory lib
 *
 * 5     1/12/98 7:03p Samir
 * Centering works fully.
 *
 * 4     1/12/98 5:24p Samir
 * Fixed font reading and created font spew test function.
 *
 * 3     1/02/98 12:53p Samir
 * Convert lowercase to uppercase if there are no lowercase chars in the
 * font.
 *
 * 2     12/29/97 5:48p Samir
 * Fixed problem with non clipping text rendering (a hack.)
 *
 * 1     12/29/97 3:24p Samir
 * Initial revision
 *
 * $NoKeywords: $
 */

#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <cctype>

#include "grtext.h"
#include "grtextlib.h"
#include "cfile.h"
#include "bitmap.h"
#include "pserror.h"
#include "renderer.h"
#include "mem.h"
#include "ddio_common.h"


const int MAX_FONTS = 16, MAX_FONT_BITMAPS = 32;

#define FT_UPPERCASE 128

#define GRFONT_SURFACE_WIDTH 128
#define GRFONT_SURFACE_HEIGHT 128

#define BITS_TO_BYTES(_c) (((_c) + 7) >> 3)
#define BITS_TO_SHORTS(_c) (((_c) + 15) >> 4)

//////////////////////////////////////////////////////////////////////////////
//	Variables

struct tFontInfo {
  char filename[32];          // filename of font
  int references;             // number of references of that font
  int bmps[MAX_FONT_BITMAPS]; // font bitmap handles
  uint8_t *ch_u, *ch_v, *ch_w, *ch_h;
  int *ch_bmp;
  float *ch_uf, *ch_vf, *ch_wf, *ch_hf;
  tFontFileInfo font;
};

//	Font information stored here.
static tFontInfo Fonts[MAX_FONTS];
static bool Font_init = false;

#define GRFONT_SURFACE_WIDTH 128
#define GRFONT_SURFACE_HEIGHT 128

//	----------------------------------------------------------------------------
//	Macros for file io.
//	----------------------------------------------------------------------------

typedef CFILE *FONTFILE;

static inline int READ_FONT_INT(FONTFILE ffile);
static inline int16_t READ_FONT_SHORT(FONTFILE ffile);
static inline uint8_t READ_FONT_BYTE(FONTFILE ffile);
static inline int READ_FONT_DATA(FONTFILE ffile, void *buf, int size, int nelem);
static inline FONTFILE OPEN_FONT(char *filename);
static inline void CLOSE_FONT(FONTFILE ffile);

inline int READ_FONT_INT(FONTFILE ffile) { return cf_ReadInt(ffile); }

inline int16_t READ_FONT_SHORT(FONTFILE ffile) { return cf_ReadShort(ffile); }

inline uint8_t READ_FONT_BYTE(FONTFILE ffile) { return (uint8_t)cf_ReadByte(ffile); }

inline int READ_FONT_DATA(FONTFILE ffile, void *buf, int size, int nelem) {
  int i;

  i = cf_ReadBytes((uint8_t *)buf, size * nelem, ffile);

  ASSERT(i == (size * nelem));

  return i;
}

inline FONTFILE OPEN_FONT(const char *filename) {
  FONTFILE fp;
  int file_id;

  fp = (FONTFILE)cfopen(filename, "rb");
  if (!fp)
    return NULL;

  file_id = READ_FONT_INT(fp);
  if (file_id != 0xfeedbaba)
    return (FONTFILE)(-1);

  return fp;
}

inline void CLOSE_FONT(FONTFILE ffile) { cfclose(ffile); }

typedef FILE *FONTFILE2;

static inline int WRITE_FONT_INT(FONTFILE2 ffile, int i);
static inline int WRITE_FONT_SHORT(FONTFILE2 ffile, int16_t s);
static inline int WRITE_FONT_BYTE(FONTFILE2 ffile, uint8_t c);
static inline int WRITE_FONT_DATA(FONTFILE2 ffile, void *buf, int size, int nelem);
static inline FONTFILE2 OPEN_FONT2(char *filename);
static inline void CLOSE_FONT2(FONTFILE2 ffile);

inline int WRITE_FONT_INT(FONTFILE2 ffile, int i) { return fwrite(&i, sizeof(i), 1, (FILE *)ffile); }

inline int WRITE_FONT_SHORT(FONTFILE2 ffile, int16_t s) { return fwrite(&s, sizeof(s), 1, (FILE *)ffile); }

inline int WRITE_FONT_BYTE(FONTFILE2 ffile, uint8_t c) { return fwrite(&c, sizeof(c), 1, (FILE *)ffile); }

inline int WRITE_FONT_DATA(FONTFILE2 ffile, void *buf, int size, int nelem) {
  int i;
  i = (int)fwrite(buf, size, nelem, (FILE *)ffile);

  ASSERT(i == nelem);

  return i;
}

inline FONTFILE2 OPEN_FONT2(const char *filename) {
  FONTFILE2 fp;

  fp = (FONTFILE2)fopen(filename, "wb");
  if (!fp)
    return NULL;

  return fp;
}

inline void CLOSE_FONT2(FONTFILE2 ffile) { fclose((FILE *)ffile); }

//////////////////////////////////////////////////////////////////////////////
//	Functions

static void grfont_Close();
static void grfont_TranslateToBitmaps(int handle);
static void grfont_XlateMonoChar(int bmp_handle, int x, int y, int index, tFontFileInfo *ft, int width);
static void grfont_XlateColorChar(int bmp_handle, int x, int y, int index, tFontFileInfo *ft, int width);
static void grfont_XlateColorGrayChar(int bmp_handle, int x, int y, int index, tFontFileInfo *ft, int width);
static void grfont_ClearBitmap(int bmp_handle);

//	clears out font buffer.
void grfont_Reset() {
  int i;

  if (Font_init) {
    //	free all allocated fonts.
    grfont_Close();
  } else {
    atexit(grfont_Close);
  }

  for (i = 0; i < MAX_FONTS; i++)
    Fonts[i].references = 0;

  Font_init = true;
}

void grfont_Close() {
  int i;

  ASSERT(Font_init);

  for (i = 0; i < MAX_FONTS; i++)
    if (Fonts[i].references)
      grfont_Free(i);

  Font_init = false;
}

//	returns a handle to a loaded font.
int grfont_Load(const char *fname) {
  FONTFILE ff;
  tFontFileInfo fnt;
  char fontname[32];
  int num_char, i, handle = -1;

  ASSERT(Font_init);

  //	check if font is in list.  if so, just return the handle.

  //	find free slot in font list.
  for (i = 0; i < MAX_FONTS; i++) {
    if (Fonts[i].references == 0)
      break;
  }
  ASSERT(i < MAX_FONTS);

  handle = i;

  //	open file.
  ff = OPEN_FONT(fname);
  if (!ff) {
    return false;
  } else if (ff == (FONTFILE)0xffffffff) {
    mprintf(0, "Illegal font file: %s.\n", fname);
    return false;
  }

  //	read header information
  fnt.width = READ_FONT_SHORT(ff);
  fnt.height = READ_FONT_SHORT(ff);
  fnt.flags = READ_FONT_SHORT(ff);
  fnt.baseline = READ_FONT_SHORT(ff);
  fnt.min_ascii = READ_FONT_BYTE(ff);
  fnt.max_ascii = READ_FONT_BYTE(ff);
  READ_FONT_DATA(ff, fontname, 32, 1);

  // read new info
  if (fnt.flags & FT_FFI2) {
    fnt.ffi2.tracking = READ_FONT_SHORT(ff);
    READ_FONT_DATA(ff, fnt.ffi2.reserved, sizeof(fnt.ffi2.reserved), 1);
  } else {
    fnt.ffi2.tracking = 0;
  }

  fnt.brightness = ((fnt.baseline >> 8) / 10.0f);
/*
  mprintf(0, "%s font.\n", fname);
  mprintf(0, "  <ht %d>::<min %d>::<max %d>::<base %d>", fnt.height, fnt.min_ascii, fnt.max_ascii, fnt.baseline);
*/
  num_char = fnt.max_ascii - fnt.min_ascii + 1;

  if (fnt.max_ascii < 'a') {
    fnt.flags |= FT_UPPERCASE;
  }

  //	Read in all widths
  if (fnt.flags & FT_PROPORTIONAL) {
    fnt.char_widths = (uint8_t *)mem_malloc(sizeof(uint8_t) * num_char);
    for (i = 0; i < num_char; i++)
      fnt.char_widths[i] = (uint8_t)READ_FONT_SHORT(ff);
    //		mprintf(0, "::proportional");
  } else {
    fnt.char_widths = NULL;
  }

  //	Read in kerning data
  if (fnt.flags & FT_KERNED) {
    int n_pairs = (int)READ_FONT_SHORT(ff);
    fnt.kern_data = (uint8_t *)mem_malloc(sizeof(uint8_t) * 3 * (n_pairs + 1));
    for (i = 0; i < n_pairs; i++) {
      fnt.kern_data[i * 3] = READ_FONT_BYTE(ff);
      fnt.kern_data[i * 3 + 1] = READ_FONT_BYTE(ff);
      fnt.kern_data[i * 3 + 2] = READ_FONT_BYTE(ff);
    }
    fnt.kern_data[i * 3] = 255;
    fnt.kern_data[i * 3 + 1] = 255;
    fnt.kern_data[i * 3 + 2] = 0;
  } else {
    fnt.kern_data = NULL;
  }

  //	Read in pixel data.
  //	for color fonts, read in byte count and then the data,
  //		generate character data pointer table
  //	for mono fonts, read in byte count, then the data, convert to bits and store
  //		generate character data pointer table
  int bytesize = READ_FONT_INT(ff);

  fnt.raw_data = (uint8_t *)mem_malloc(bytesize);
  fnt.char_data = (uint8_t **)mem_malloc(num_char * sizeof(uint8_t *));

  READ_FONT_DATA(ff, fnt.raw_data, bytesize, 1);

  if (fnt.flags & FT_COLOR) {
    int off = 0;
    //		mprintf(0, "::color");
    for (i = 0; i < num_char; i++) {
      fnt.char_data[i] = fnt.raw_data + off;
      if (fnt.flags & FT_PROPORTIONAL)
        off += (fnt.char_widths[i] * fnt.height * BITS_TO_BYTES(BPP_16));
      else
        off += (fnt.width * fnt.height * BITS_TO_BYTES(BPP_16));
    }
  } else { // Monochrome
    uint8_t *ptr = fnt.raw_data;
    //		mprintf(0, "::mono");
    for (i = 0; i < num_char; i++) {
      fnt.char_data[i] = ptr;
      if (fnt.flags & FT_PROPORTIONAL)
        ptr += BITS_TO_BYTES(fnt.char_widths[i]) * fnt.height;
      else
        ptr += BITS_TO_BYTES(fnt.width) * fnt.height;
    }
  }

  //	Then read in
  CLOSE_FONT(ff);

  //	mprintf(0, "\n");

  strcpy(Fonts[handle].filename, fname);
  Fonts[handle].references = 1;
  Fonts[handle].font = fnt;

  //	draw font to bitmaps, load into surfaces too.
  grfont_TranslateToBitmaps(handle);

  return handle;
}

//	frees a loaded font
void grfont_Free(int handle) {
  tFontInfo *ft;
  int i;

  ASSERT(Font_init);
  ASSERT(handle > -1 && handle < MAX_FONTS);

  //	delete font surface info.
  ft = &Fonts[handle];
  if (ft->ch_bmp)
    delete[] ft->ch_bmp;
  if (ft->ch_wf)
    delete[] ft->ch_wf;
  if (ft->ch_hf)
    delete[] ft->ch_hf;
  if (ft->ch_uf)
    delete[] ft->ch_uf;
  if (ft->ch_vf)
    delete[] ft->ch_vf;
  if (ft->ch_w)
    delete[] ft->ch_w;
  if (ft->ch_h)
    delete[] ft->ch_h;
  if (ft->ch_u)
    delete[] ft->ch_u;
  if (ft->ch_v)
    delete[] ft->ch_v;

  for (i = 0; i < MAX_FONT_BITMAPS; i++) {
    if (ft->bmps[i] != -1)
      bm_FreeBitmap(ft->bmps[i]);
  }

  //	delete font file info.
  if ((ft->font.flags & FT_KERNED) && ft->font.kern_data) {
    mem_free(ft->font.kern_data);
  }

  if (ft->font.flags & FT_PROPORTIONAL) {
    mem_free(ft->font.char_widths);
  }

  ft->references = 0;

  mem_free(ft->font.raw_data);
  mem_free(ft->font.char_data);
}

// loads a font template
bool grfont_LoadTemplate(const char *fname, tFontTemplate *ft) {
  FONTFILE ff;
  char fontname[32];
  int16_t ft_width, ft_height, ft_flags, ft_minasc, ft_maxasc, num_char, i;
  tFontFileInfo2 ffi2;

  //	open file.
  ff = OPEN_FONT(fname);
  if (!ff) {
    Error("Unable to open font %s.\n", fname);
  } else if (ff == (FONTFILE)0xffffffff) {
    Error("Illegal font file: %s.\n", fname);
  }

  //	read header information
  ft_width = READ_FONT_SHORT(ff);
  ft_height = READ_FONT_SHORT(ff);
  ft_flags = READ_FONT_SHORT(ff);
  READ_FONT_SHORT(ff); // skip baseline value (HACKED FOR BRIGHTNESS)
  ft_minasc = READ_FONT_BYTE(ff);
  ft_maxasc = READ_FONT_BYTE(ff);
  READ_FONT_DATA(ff, fontname, 32, 1); // read namae

  // read ffi2 font info
  if (ft_flags & FT_FFI2) {
    ffi2.tracking = READ_FONT_SHORT(ff);
    READ_FONT_DATA(ff, &ffi2.reserved, sizeof(ffi2.reserved), 1);
  }

  num_char = ft_maxasc - ft_minasc + 1;

  //	Read in all widths
  if (ft_flags & FT_PROPORTIONAL) {
    ft->ch_widths = (uint8_t *)mem_malloc(num_char);
    for (i = 0; i < num_char; i++)
      ft->ch_widths[i] = (uint8_t)READ_FONT_SHORT(ff);
  } else {
    ft->ch_widths = NULL;
  }

  if (ft_flags & FT_KERNED) {
    int n_pairs = (int)READ_FONT_SHORT(ff);
    ft->kern_data = (uint8_t *)mem_malloc(sizeof(uint8_t) * 3 * (n_pairs + 1));
    for (i = 0; i < n_pairs; i++) {
      ft->kern_data[i * 3] = READ_FONT_BYTE(ff);
      ft->kern_data[i * 3 + 1] = READ_FONT_BYTE(ff);
      ft->kern_data[i * 3 + 2] = READ_FONT_BYTE(ff);
    }
    ft->kern_data[i * 3] = 255;
    ft->kern_data[i * 3 + 1] = 255;
    ft->kern_data[i * 3 + 2] = 0;
  } else {
    ft->kern_data = NULL;
  }

  ft->ch_height = (uint8_t)ft_height;
  ft->ch_maxwidth = (uint8_t)ft_width;
  ft->max_ascii = ft_maxasc;
  ft->min_ascii = ft_minasc;
  ft->proportional = (ft_flags & FT_PROPORTIONAL) ? true : false;
  ft->uppercase = (ft_maxasc < 'a');
  ft->monochromatic = (ft_flags & FT_COLOR) ? false : true;
  ft->newstyle = (ft_flags & FT_FMT4444) ? true : false;
  ft->ffi2 = (ft_flags & FT_FFI2) ? true : false;

  ft->ch_tracking = (int8_t)((ft_flags & FT_FFI2) ? ffi2.tracking : 0);

  CLOSE_FONT(ff);

  return true;
}

// frees a font template
void grfont_FreeTemplate(tFontTemplate *ft) {
  if (ft->kern_data) {
    mem_free(ft->kern_data);
    ft->kern_data = NULL;
  }
  if (ft->ch_widths) {
    mem_free(ft->ch_widths);
    ft->ch_widths = NULL;
  }
}

// MTS: unused?
// sets a template to a font, be careful.
bool grfont_SetTemplate(const char *pathname, const tFontTemplate *ft) {
  // okay, load the font manually, set the template members, then save it out.
  tFontFileInfo fnt;
  char tempstr[32];
  FONTFILE ffin;
  FONTFILE2 ffout;
  int num_char, i;

  tFontFileInfo2 ffi2;

  ffin = OPEN_FONT(pathname);
  if (!ffin) {
    return false;
  } else if (ffin == (FONTFILE)0xffffffff) {
    mprintf(0, "Illegal font file %s\n", pathname);
    return false;
  }

  //	read header information
  fnt.width = READ_FONT_SHORT(ffin);
  fnt.height = READ_FONT_SHORT(ffin);
  fnt.flags = READ_FONT_SHORT(ffin);
  fnt.baseline = READ_FONT_SHORT(ffin);
  fnt.min_ascii = READ_FONT_BYTE(ffin);
  fnt.max_ascii = READ_FONT_BYTE(ffin);
  READ_FONT_DATA(ffin, tempstr, 32, 1);

  // read ffi2 font info
  if (fnt.flags & FT_FFI2) {
    ffi2.tracking = READ_FONT_SHORT(ffin);
    READ_FONT_DATA(ffin, &ffi2.reserved, sizeof(ffi2.reserved), 1);
  }

  fnt.brightness = ((fnt.baseline >> 8) / 10.0f);

  num_char = fnt.max_ascii - fnt.min_ascii + 1;

  //	Read in all widths
  if (fnt.flags & FT_PROPORTIONAL) {
    fnt.char_widths = (uint8_t *)mem_malloc(sizeof(uint8_t) * num_char);
    for (i = 0; i < num_char; i++)
      fnt.char_widths[i] = (uint8_t)READ_FONT_SHORT(ffin);
  } else {
    fnt.char_widths = NULL;
  }

  //	Read in kerning data
  if (fnt.flags & FT_KERNED) {
    int n_pairs = (int)READ_FONT_SHORT(ffin);
    fnt.kern_data = (uint8_t *)mem_malloc(sizeof(uint8_t) * 3 * (n_pairs + 1));
    for (i = 0; i < n_pairs; i++) {
      fnt.kern_data[i * 3] = READ_FONT_BYTE(ffin);
      fnt.kern_data[i * 3 + 1] = READ_FONT_BYTE(ffin);
      fnt.kern_data[i * 3 + 2] = READ_FONT_BYTE(ffin);
    }
    fnt.kern_data[i * 3] = 255;
    fnt.kern_data[i * 3 + 1] = 255;
    fnt.kern_data[i * 3 + 2] = 0;
  } else {
    fnt.kern_data = NULL;
  }

  //	Read in pixel data.
  int bytesize = READ_FONT_INT(ffin);

  fnt.raw_data = (uint8_t *)mem_malloc(bytesize);

  READ_FONT_DATA(ffin, fnt.raw_data, bytesize, 1);

  CLOSE_FONT(ffin);

  // set template values
  fnt.width = ft->ch_maxwidth;
  fnt.height = ft->ch_height;
  fnt.flags = (ft->proportional ? FT_PROPORTIONAL : 0) + ((!ft->monochromatic) ? FT_COLOR : 0) +
              (ft->kern_data ? FT_KERNED : 0) + (ft->newstyle ? FT_FMT4444 : 0);
  fnt.min_ascii = (uint8_t)ft->min_ascii;
  fnt.max_ascii = (uint8_t)ft->max_ascii;

  if (ft->ffi2)
    fnt.flags |= FT_FFI2;

  if (fnt.kern_data) {
    mem_free(fnt.kern_data);
  }
  if (fnt.char_widths) {
    mem_free(fnt.char_widths);
  }
  fnt.kern_data = ft->kern_data;
  fnt.char_widths = ft->ch_widths;

  // write out font.
  ffout = OPEN_FONT2(pathname);
  if (!ffout) {
    return false;
  }

  //	Write file id.
  WRITE_FONT_INT(ffout, 0xfeedbaba);
  WRITE_FONT_SHORT(ffout, fnt.width);
  WRITE_FONT_SHORT(ffout, fnt.height);
  WRITE_FONT_SHORT(ffout, fnt.flags);
  WRITE_FONT_SHORT(ffout, fnt.baseline);
  WRITE_FONT_BYTE(ffout, fnt.min_ascii);
  WRITE_FONT_BYTE(ffout, fnt.max_ascii);
  WRITE_FONT_DATA(ffout, tempstr, 32, 1);

  if (fnt.flags & FT_FFI2) {
    WRITE_FONT_SHORT(ffout, (int16_t)ft->ch_tracking);
    WRITE_FONT_DATA(ffout, ffi2.reserved, sizeof(ffi2.reserved), 1);
  }

  num_char = ft->max_ascii - ft->min_ascii + 1;

  //	Write widths now if necessary.(FT_PROPORTIONAL)
  if (fnt.flags & FT_PROPORTIONAL) {
    for (int i = 0; i < num_char; i++)
      WRITE_FONT_SHORT(ffout, (int16_t)fnt.char_widths[i]);
  }

  if (fnt.flags & FT_KERNED) {
    // iterate new kerning info bytes
    uint8_t *ch = fnt.kern_data;
    int n_bytes = 0, n_pairs;
    while (ch[n_bytes] != 255) {
      n_bytes += 3;
    }

    ASSERT((n_bytes % 3) == 0);
    n_pairs = n_bytes / 3;
    WRITE_FONT_SHORT(ffout, (int16_t)n_pairs);

    for (i = 0; i < n_pairs; i++) {
      WRITE_FONT_BYTE(ffout, ch[i * 3]);
      WRITE_FONT_BYTE(ffout, ch[i * 3 + 1]);
      WRITE_FONT_BYTE(ffout, ch[i * 3 + 2]);
    }
  }

  WRITE_FONT_INT(ffout, bytesize);
  WRITE_FONT_DATA(ffout, fnt.raw_data, bytesize, 1);

  CLOSE_FONT2(ffout);

  // free raw data loaded, don't free kern and widths, already freed, template versions remain
  mem_free(fnt.raw_data);

  return true;
}

// MTS: Unused?
// sets a font's template without saving...
bool grfont_SetKerning(int font, uint8_t *kern_data) {
  tFontInfo *oldft = &Fonts[font];
  int n_pairs = 0;

  // reset kerning...
  if (oldft->font.kern_data) {
    mem_free(oldft->font.kern_data);
    oldft->font.kern_data = NULL;
  }

  if (kern_data) {
    while (kern_data[n_pairs * 3] != 255)
      n_pairs++;

    oldft->font.kern_data = (uint8_t *)mem_malloc((n_pairs + 1) * 3 * sizeof(uint8_t));
    n_pairs = 0;
    while (kern_data[n_pairs * 3] != 255) {
      oldft->font.kern_data[n_pairs * 3] = kern_data[n_pairs * 3];
      oldft->font.kern_data[n_pairs * 3 + 1] = kern_data[n_pairs * 3 + 1];
      oldft->font.kern_data[n_pairs * 3 + 2] = kern_data[n_pairs * 3 + 2];
      n_pairs++;
    }
    oldft->font.kern_data[n_pairs * 3] = 255;
    oldft->font.kern_data[n_pairs * 3 + 1] = 255;
    oldft->font.kern_data[n_pairs * 3 + 2] = 0;
  }

  // we're not going to reset other stuff for now... just kerning!
  return true;
}

// MTS: Unused?
// sets a font's tracking
bool grfont_SetTracking(int font, int tracking) {
  ASSERT(font >= 0 && font < MAX_FONTS);

  tFontInfo *oldft = &Fonts[font];

  oldft->font.ffi2.tracking = (int16_t)tracking;

  return false;
}

int grfont_GetTracking(int font) {
  ASSERT(font >= 0 && font < MAX_FONTS);
  //	if (Fonts[font].font.flags & FT_FFI2) {
  return (int)Fonts[font].font.ffi2.tracking;
  //	}

  //	return 0;
}

//	render a character
int grfont_BltChar(int font, tCharBlt *cbi) {
  ASSERT(font > -1 && font < MAX_FONTS);

  tFontInfo *ft = &Fonts[font];

  //	save current x and get this font
  if (cbi->ch > ft->font.max_ascii && (ft->font.flags & FT_UPPERCASE)) {
    cbi->ch = toupper(cbi->ch);
  }

  if ((cbi->ch < ft->font.min_ascii) || (cbi->ch > ft->font.max_ascii))
    return (cbi->x + 1);

  cbi->ch = cbi->ch - ft->font.min_ascii;

  if (!cbi->clipped) {

    if (ft->font.flags & FT_PROPORTIONAL)
      cbi->sw = (int)(ft->font.char_widths[cbi->ch]);
    else
      cbi->sw = (int)(ft->font.width);
    cbi->sh = (int)(ft->font.height);
    cbi->sx = 0;
    cbi->sy = 0;

    rend_DrawFontCharacter(ft->bmps[ft->ch_bmp[cbi->ch]], cbi->x, cbi->y, (int)(cbi->x + cbi->sw * cbi->dsw),
                           (int)(cbi->y + cbi->sh * cbi->dsh), ft->ch_uf[cbi->ch], ft->ch_vf[cbi->ch],
                           ft->ch_wf[cbi->ch], ft->ch_hf[cbi->ch]);
    return (cbi->x + (int)(cbi->sw * cbi->dsw));
    //@@		rend_DrawFontCharacter (ft->bmps[ft->ch_bmp[cbi->ch]], cbi->x,cbi->y,
    //@@ cbi->x+ft->ch_w[cbi->ch], cbi->y+ft->ch_h[cbi->ch],
    //@@											ft->ch_uf[cbi->ch],
    // ft->ch_vf[cbi->ch],
    //@@											ft->ch_wf[cbi->ch],
    // ft->ch_hf[cbi->ch]);
    //@@		return (cbi->x + ft->ch_w[cbi->ch] - 1);
  } else {
    rend_DrawFontCharacter(
        ft->bmps[ft->ch_bmp[cbi->ch]], cbi->x, cbi->y,
        (int)(cbi->x + cbi->sw), // don't scale since these values are already scaled
        (int)(cbi->y + cbi->sh), ft->ch_uf[cbi->ch] + (((float)cbi->sx) / ((float)GRFONT_SURFACE_WIDTH)),
        ft->ch_vf[cbi->ch] + (((float)cbi->sy) / ((float)GRFONT_SURFACE_HEIGHT)),
        ((float)cbi->sw) / ((float)GRFONT_SURFACE_WIDTH), ((float)cbi->sh) / ((float)GRFONT_SURFACE_HEIGHT));
    return (cbi->x + (int)(cbi->sw)); // scaled value already
  }
}

//	returns a character's width
int grfont_GetCharWidth(int font, int ch) {
  tFontFileInfo *ft;

  ASSERT(font > -1 && font < MAX_FONTS);

  ft = &Fonts[font].font;
  ch = (int)((uint8_t)ch);

  if (ch > ft->max_ascii && (ft->flags & FT_UPPERCASE)) {
    ch = toupper(ch);
  }

  if (ch < ft->min_ascii || ch > ft->max_ascii)
    return 0;
  else if (ft->flags & FT_PROPORTIONAL)
    return ft->char_widths[ch - ft->min_ascii];
  else
    return ft->width;
}

//	returns a font's height
int grfont_GetHeight(int font) {
  ASSERT(font > -1 && font < MAX_FONTS);
  return Fonts[font].font.height;
}

//	translates raw font data to bitmaps.
void grfont_TranslateToBitmaps(int handle) {
  tFontFileInfo *fntfile;
  tFontInfo *fnt;
  int i;

  fnt = &Fonts[handle];
  fntfile = &Fonts[handle].font;

  //	start creating font surfaces, map these surfaces onto bitmaps created via bitmap library
  //	this is needed for the renderer library.
  //	create a 128x128 bitmap.
  //	draw each character into bitmap until we need to create another
  //	surface.
  uint8_t u = 0, v = 0, w;
  int ch, num_ch;
  uint8_t surf_index = 0;

  num_ch = fntfile->max_ascii - fntfile->min_ascii + 1;

  //	initialize memory
  fnt->ch_w = new uint8_t[num_ch];
  fnt->ch_h = new uint8_t[num_ch];
  fnt->ch_u = new uint8_t[num_ch];
  fnt->ch_v = new uint8_t[num_ch];
  fnt->ch_bmp = new int[num_ch];
  fnt->ch_uf = new float[num_ch];
  fnt->ch_vf = new float[num_ch];
  fnt->ch_wf = new float[num_ch];
  fnt->ch_hf = new float[num_ch];

  for (i = 0; i < MAX_FONT_BITMAPS; i++)
    fnt->bmps[i] = -1;

  fnt->bmps[surf_index] = bm_AllocBitmap(GRFONT_SURFACE_WIDTH, GRFONT_SURFACE_HEIGHT, 0);
  if (fnt->bmps[surf_index] == -1 || fnt->bmps[surf_index] == BAD_BITMAP_HANDLE)
    Error("TranslateToBitmaps <Bitmap allocation error>");
  if (fntfile->flags & FT_FMT4444) {
    GameBitmaps[fnt->bmps[surf_index]].format = BITMAP_FORMAT_4444;
  }

  grfont_ClearBitmap(fnt->bmps[surf_index]);
  surf_index++;

  for (ch = 0; ch < num_ch; ch++) {
    if (fntfile->flags & FT_PROPORTIONAL)
      w = (int)fntfile->char_widths[ch];
    else
      w = (int)fntfile->width;

    if ((u + w) > GRFONT_SURFACE_WIDTH) {
      u = 0;
      v += fntfile->height;
      if ((v + fntfile->height) > GRFONT_SURFACE_HEIGHT) {
        if (surf_index == MAX_FONT_BITMAPS)
          Int3();
        fnt->bmps[surf_index] = bm_AllocBitmap(GRFONT_SURFACE_WIDTH, GRFONT_SURFACE_HEIGHT, 0);
        if (fnt->bmps[surf_index] == -1 || fnt->bmps[surf_index] == BAD_BITMAP_HANDLE)
          Error("TranslateToBitmaps <Bitmap allocation error>");
        if (fntfile->flags & FT_FMT4444) {
          GameBitmaps[fnt->bmps[surf_index]].format = BITMAP_FORMAT_4444;
        }
        grfont_ClearBitmap(fnt->bmps[surf_index]);
        surf_index++;
        v = 0;
      }
    }

    // blt each character
    if (fntfile->flags & FT_COLOR) {
      if (fntfile->flags & FT_GRADIENT)
        grfont_XlateColorGrayChar(fnt->bmps[surf_index - 1], u, v, ch, fntfile, w);
      //			else
      grfont_XlateColorChar(fnt->bmps[surf_index - 1], u, v, ch, fntfile, w);
    } else { //	font monochrome, convert bits to pixels
      grfont_XlateMonoChar(fnt->bmps[surf_index - 1], u, v, ch, fntfile, w);
    }

    fnt->ch_h[ch] = (uint8_t)fntfile->height;
    fnt->ch_w[ch] = w;
    fnt->ch_u[ch] = u;
    fnt->ch_v[ch] = v;
    fnt->ch_bmp[ch] = surf_index - 1;
    fnt->ch_hf[ch] = ((float)fntfile->height) / ((float)GRFONT_SURFACE_HEIGHT);
    fnt->ch_wf[ch] = ((float)w) / ((float)GRFONT_SURFACE_WIDTH);
    fnt->ch_uf[ch] = ((float)u) / ((float)GRFONT_SURFACE_WIDTH);
    fnt->ch_vf[ch] = ((float)v) / ((float)GRFONT_SURFACE_HEIGHT);

    //	check to adjust uv's if we are outside surface.
    u += w;
  }
}

//	Font translation routines
void grfont_XlateMonoChar(int bmp_handle, int x, int y, int index, tFontFileInfo *ft, int width) {
  int row, col; // byte width of char
  uint8_t bit_mask = 0, byte;
  uint8_t *fp;

  fp = ft->char_data[index];

  /*	draw one-bit one color. */
  uint16_t *dest_ptr;
  uint16_t col_w = GR_COLOR_TO_16(GR_RGB(255, 255, 255));
  int rowsize_w;

  dest_ptr = bm_data(bmp_handle, 0);
  rowsize_w = bm_rowsize(bmp_handle, 0) >> 1;
  dest_ptr += (y * rowsize_w) + x;

  for (row = 0; row < ft->height; row++) {
    bit_mask = 0;
    for (col = 0; col < width; col++) {
      if (bit_mask == 0) {
        byte = *fp++;
        bit_mask = 0x80;
      }

      if (byte & bit_mask)
        dest_ptr[col] = (col_w | OPAQUE_FLAG);

      bit_mask >>= 1;
    }
    dest_ptr += rowsize_w;
  }
}

void grfont_XlateColorChar(int bmp_handle, int x, int y, int index, tFontFileInfo *ft, int width) {
  /*	16-bit copy from source bitmap to destination surface just created and
          locked
          This function performs scaling if the source width and height don't match
          that of the destinations - JL
  */
  uint16_t *dptr, *sptr;
  int row, col;
  int rowsize_w;

  dptr = bm_data(bmp_handle, 0);
  sptr = (uint16_t *)ft->char_data[index];
  rowsize_w = bm_rowsize(bmp_handle, 0) / 2;

  // height = std::min(h, ddsfObj.h);
  // width = std::min(w, ddsfObj.w);
  dptr = dptr + (y * rowsize_w);

  if (ft->flags & FT_FMT4444) {
    for (row = 0; row < ft->height; row++) {
      for (col = 0; col < width; col++) {
        dptr[x + col] = *(sptr++);
      }
      dptr += rowsize_w;
    }
  } else {
    // old style
    for (row = 0; row < ft->height; row++) {
      for (col = 0; col < width; col++) {
        uint16_t col565 = *(sptr++);
        if (col565 == 0x07e0)
          dptr[x + col] = NEW_TRANSPARENT_COLOR;
        else
          dptr[x + col] = (((col565 & 0xf800) >> 1) | ((col565 & 0x07c0) >> 1) | (col565 & 0x001f)) | OPAQUE_FLAG;
      }
      dptr += rowsize_w;
    }
  }
}

void grfont_XlateColorGrayChar(int bmp_handle, int x, int y, int index, tFontFileInfo *ft, int width) {
  /*	16-bit copy from source bitmap to destination surface just created and
          locked
          This function performs scaling if the source width and height don't match
          that of the destinations - JL
  */
  uint16_t *dptr, *sptr;
  int row, col;
  int rowsize_w;

  dptr = bm_data(bmp_handle, 0);
  sptr = (uint16_t *)ft->char_data[index];
  rowsize_w = bm_rowsize(bmp_handle, 0) / 2;

  // height = std::min(h, ddsfObj.h);
  // width = std::min(w, ddsfObj.w);
  dptr = dptr + (y * rowsize_w);

  float recip32 = 1.0f / 32.0f;

  for (row = 0; row < ft->height; row++) {
    for (col = 0; col < width; col++) {
      uint16_t col565 = *(sptr++);
      if (col565 == 0x07e0)
        dptr[x + col] = NEW_TRANSPARENT_COLOR;
      else {
        uint8_t r = (uint8_t)((col565 & 0xf800) >> 11);
        uint8_t g = (uint8_t)((col565 & 0x07c0) >> 6);
        uint8_t b = (uint8_t)(col565 & 0x001f);
        float brightness = ((r * 0.30f) + (g * 0.59f) + (b * 0.11f)) * recip32;
        uint8_t elem = (uint8_t)(255 * brightness * ft->brightness);
        if ((brightness * ft->brightness) > 1.0f)
          elem = 255;
        dptr[x + col] = GR_RGB16(elem, elem, elem) | OPAQUE_FLAG;
      }
    }
    dptr += rowsize_w;
  }
}

void grfont_ClearBitmap(int bmp_handle) {
  int dx, dy;
  int rowsize_w = bm_rowsize(bmp_handle, 0) / 2;
  uint16_t *bmpdata = bm_data(bmp_handle, 0);

  for (dy = 0; dy < bm_h(bmp_handle, 0); dy++) {
    for (dx = 0; dx < rowsize_w; dx++)
      bmpdata[dx] = NEW_TRANSPARENT_COLOR;

    bmpdata += rowsize_w;
  }
}

#ifndef RELEASE
void grfont_Spew(int font, int x, int y) {
  int i;
  tFontInfo *fnt;

  fnt = &Fonts[font];

  for (i = 0; i < MAX_FONT_BITMAPS; i++)
    if (fnt->bmps[i] > -1)
      rend_DrawScaledBitmap(i * GRFONT_SURFACE_WIDTH, 0, (i + 1) * GRFONT_SURFACE_WIDTH, GRFONT_SURFACE_HEIGHT,
                            fnt->bmps[i], 0, 0, 1.0, 1.0);
}
#endif

// returns character equivalent in font (converts lowercase to uppercase if no lowercase version avail)
// similar to ddio_KeyToAscii
int grfont_KeyToAscii(int font, int key) {
  key = ddio_KeyToAscii(key);

  if (font >= 0 && font < MAX_FONTS) {
    tFontInfo *ft = &Fonts[font];

    //	save current x and get this font
    if (key > ft->font.max_ascii && (ft->font.flags & FT_UPPERCASE)) {
      return toupper(key);
    }
  }

  return key;
}

// MTS: Unused?
// returns the raw bitmap data for a character in a font, its width and height
// returned data should be in 565 hicolor format if (*mono) is false.  if (*mono) is true,
//	then a bitmask will be returned, and you should treat a bit as a pixel.
uint16_t *grfont_GetRawCharacterData(int font, int ch, int *w, int *h, bool *mono) {
  tFontFileInfo *fntfile;
  tFontInfo *fnt;

  ASSERT(font > -1 && font < MAX_FONTS);

  fnt = &Fonts[font];
  fntfile = &fnt->font;

  if (ch > fnt->font.max_ascii && (fntfile->flags & FT_UPPERCASE)) {
    ch = toupper(ch);
  }

  if ((ch < fnt->font.min_ascii) || (ch > fnt->font.max_ascii))
    return NULL;

  ch = ch - fnt->font.min_ascii;
  *mono = !(fnt->font.flags & FT_COLOR);

  if (fnt->font.flags & FT_PROPORTIONAL) {
    *w = (int)(fnt->font.char_widths[ch]);
  } else {
    *w = (int)(fnt->font.width);
  }

  *h = fnt->font.height;

  return (uint16_t *)fnt->font.char_data[ch];
}

//	returns a character's width
int grfont_GetKernedSpacing(int font, int ch1, int ch2) {
  tFontFileInfo *ft;

  ASSERT(font > -1 && font < MAX_FONTS);

  ft = &Fonts[font].font;

  if (ft->kern_data) {
    uint8_t *kern = ft->kern_data;
    while (kern[0] != 255) {
      if (ch1 == kern[0] && ch2 == kern[1]) {
        return (int)((int8_t)kern[2]);
      }
      kern += 3;
    }
  }
  return 0;
}

//	returns a character's width
int grfont_GetKernedSpacingTemp(const tFontTemplate *ft, int ch1, int ch2) {
  if (ft->kern_data) {
    uint8_t *kern = ft->kern_data;
    while (kern[0] != 255) {
      if (ch1 == kern[0] && ch2 == kern[1]) {
        return (int)((int8_t)kern[2]);
      }
      kern += 3;
    }
  }
  return 0;
}
