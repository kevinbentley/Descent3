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

 * $Logfile: /DescentIII/Main/bitmap/iff.cpp $
 * $Revision: 8 $
 * $Date: 10/21/99 9:28p $
 * $Author: Jeff $
 *
 * Code to read IFF files
 *
 * $Log: /DescentIII/Main/bitmap/iff.cpp $
 *
 * 8     10/21/99 9:28p Jeff
 * B.A. Macintosh code merge
 *
 * 7     4/14/99 1:07a Jeff
 * fixed case mismatched #includes
 *
 * 6     10/08/98 4:23p Kevin
 * Changed code to comply with memory library usage. Always use mem_malloc
 * , mem_free and mem_strdup
 *
 * 5     4/23/98 6:38p Jason
 * made bitmaps use 1555 format
 *
 * 4     3/19/98 3:18p Samir
 * enforce constant char* arguments when needed.  done in CFILE and bitmap
 * libraries as well as ddio.
 *
 * 3     12/22/97 7:34p Samir
 * Removed instances of gr.h include.  Replaced with grdefs.h
 *
 * 2     10/15/97 5:20p Jason
 * did a HUGE overhaul of the bitmap system
 *
 * 11    3/07/97 4:02p Samir
 * Took out conio.h and malloc.h for ANSI compliance.
 *
 * 10    3/07/97 1:02p Jason
 * decreased size of bitmap headers array to compensate for stupid mac
 * problem
 *
 * 9     3/03/97 6:20p Matt
 * Changed cfile functions to use D3 naming convention
 *
 * $NoKeywords: $
 */

#define COMPRESS 1   // do the RLE or not? (for debugging mostly)
#define WRITE_TINY 0 // should we write a TINY chunk?

#define MIN_COMPRESS_WIDTH 65 // don't compress if less than this wide

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mem.h"
#include "iff.h"
#include "byteswap.h"
#include "cfile.h"
#include "pserror.h"
#include "pstypes.h"
#include "bitmap.h"
#include "mono.h"
#include "grdefs.h"

// Internal constants and structures for this library

// Compression types
#define cmpNone 0
#define cmpByteRun1 1

// Masking types
#define mskNone 0
#define mskHasMask 1
#define mskHasTransparentColor 2

// Palette entry structure
struct pal_entry {
  uint8_t r, g, b;
};

// structure of the header in the file
struct iff_bitmap_header {
  int16_t w, h;                  // width and height of this bitmap
  int16_t x, y;                  // generally unused
  int16_t type;                  // see types above
  int16_t transparentcolor;      // which color is transparent (if any)
  int16_t pagewidth, pageheight; // width & height of source screen
  uint8_t nplanes;               // number of planes (8 for 256 color image)
  uint8_t masking, compression;  // see constants above
  uint8_t xaspect, yaspect;      // aspect ratio (usually 5/6)
  pal_entry palette[256];      // the palette for this bitmap
  uint8_t *raw_data;             // ptr to array of data
  int16_t row_size;              // offset to next row
};

static int16_t iff_transparent_color;
static int16_t iff_has_transparency; // 0=no transparency, 1=iff_transparent_color is valid

#define MIN(a, b) ((a < b) ? a : b)

#define MAKE_SIG(a, b, c, d) (((int32_t)(a) << 24) + ((int32_t)(b) << 16) + ((c) << 8) + (d))

#define IFF_SIG_FORM 1
#define IFF_SIG_ILBM 2
#define IFF_SIG_BODY 3
#define IFF_SIG_BMHD 4
#define IFF_SIG_CMAP 5
#define IFF_SIG_UNKNOWN 6
#define IFF_SIG_PBM 7
#define IFF_SIG_ANIM 8
#define IFF_SIG_DELTA 9
#define IFF_SIG_ANHD 10

static int bm_iff_get_sig(CFILE *f);
static int bm_iff_parse_bmhd(CFILE *ifile, uint32_t len, iff_bitmap_header *bmheader);

/// the buffer pointed to by raw_data is stuffed with a pointer to decompressed pixel data
static int bm_iff_parse_body(CFILE *ifile, int len, iff_bitmap_header *bmheader);

/// the buffer pointed to by raw_data is stuffed with a pointer to bitplane pixel data
static void bm_iff_skip_chunk(CFILE *ifile, uint32_t len);

/// modify passed bitmap
static int bm_iff_parse_delta(CFILE *ifile, int len, iff_bitmap_header *bmheader);

static int bm_iff_parse_file(CFILE *ifile, iff_bitmap_header *bmheader, iff_bitmap_header *prev_bm);
static void bm_iff_convert_8_to_16(int dest_bm, iff_bitmap_header *iffbm);

int bm_iff_get_sig(CFILE *f) {
  char s[4];
  int i;

  for (i = 0; i < 4; i++)
    s[i] = cf_ReadByte(f);

  if (!strncmp("ILBM", s, 4))
    return IFF_SIG_ILBM;
  if (!strncmp("BODY", s, 4))
    return IFF_SIG_BODY;
  if (!strncmp("CMAP", s, 4))
    return IFF_SIG_CMAP;
  if (!strncmp("BMHD", s, 4))
    return IFF_SIG_BMHD;
  if (!strncmp("FORM", s, 4))
    return IFF_SIG_FORM;
  if (!strncmp("PBM ", s, 4))
    return IFF_SIG_PBM;
  if (!strncmp("ANIM", s, 4))
    return IFF_SIG_ANIM;
  if (!strncmp("DLTA", s, 4))
    return IFF_SIG_DELTA;
  if (!strncmp("ANHD", s, 4))
    return IFF_SIG_ANHD;

  return (IFF_SIG_UNKNOWN);
}
int bm_iff_parse_bmhd(CFILE *ifile, uint32_t len, iff_bitmap_header *bmheader) {
  len = len;

  bmheader->w = cf_ReadShort(ifile);
  bmheader->w = MOTOROLA_SHORT(bmheader->w);
  bmheader->h = cf_ReadShort(ifile);
  bmheader->h = MOTOROLA_SHORT(bmheader->h);
  bmheader->x = cf_ReadShort(ifile);
  bmheader->x = MOTOROLA_SHORT(bmheader->x);
  bmheader->y = cf_ReadShort(ifile);
  bmheader->y = MOTOROLA_SHORT(bmheader->y);

  bmheader->nplanes = cf_ReadByte(ifile);
  bmheader->masking = cf_ReadByte(ifile);
  bmheader->compression = cf_ReadByte(ifile);
  cf_ReadByte(ifile); /* skip pad */

  bmheader->transparentcolor = cf_ReadShort(ifile);
  bmheader->transparentcolor = MOTOROLA_SHORT(bmheader->transparentcolor);
  bmheader->xaspect = cf_ReadByte(ifile);
  bmheader->yaspect = cf_ReadByte(ifile);

  bmheader->pagewidth = cf_ReadShort(ifile);
  bmheader->pageheight = cf_ReadShort(ifile);

  iff_transparent_color = bmheader->transparentcolor;

  iff_has_transparency = 0;

  if (bmheader->masking == mskHasTransparentColor)
    iff_has_transparency = 1;

  else if (bmheader->masking != mskNone && bmheader->masking != mskHasMask)
    return IFF_UNKNOWN_MASK;

  return IFF_NO_ERROR;
}

//  the buffer pointed to by raw_data is stuffed with a pointer to decompressed pixel data
int bm_iff_parse_body(CFILE *ifile, int len, iff_bitmap_header *bmheader) {
  uint8_t *p = bmheader->raw_data;
  int width = 0, depth = 0, done = 0;

  if (bmheader->type == TYPE_PBM) {
    width = bmheader->w;
    depth = 1;
  } else if (bmheader->type == TYPE_ILBM) {
    width = (bmheader->w + 7) / 8;
    depth = bmheader->nplanes;
  }

  if (bmheader->compression == cmpNone) // no compression
  {
    for (int y = 0; y < bmheader->h; y++) {
      int x;

      for (x = 0; x < width * depth; x++)
        *p++ = cf_ReadByte(ifile);

      if (bmheader->masking == mskHasMask) {
        for (int i = 0; i < width; i++)
          cf_ReadByte(ifile); // skip mask!
      }

      if (bmheader->w & 1)
        cf_ReadByte(ifile);
    }

  } else if (bmheader->compression == cmpByteRun1) // compression
  {
    uint8_t *data_end = p + (bmheader->h * depth * width);
    uint8_t mask = (bmheader->masking == mskHasMask);
    int cur_width = 0, skip_mask = 0;
    int command;
    int plane = 0;

    while (!done) {
      if (p >= data_end) {
        done = 1;
        continue;
      }
      if (cur_width == width) {
        plane++;
        if ((plane == depth && !mask) || (plane == depth + 1 && mask)) {
          skip_mask = 0;
          plane = 0;
        }

        if (mask && plane == depth)
          skip_mask = 1;

        cur_width = 0;
      }

      command = cf_ReadByte(ifile);
      if (command >= 0 && command <= 127) {
        if (!skip_mask) {
          for (int i = 0; i < command + 1; i++)
            *p++ = cf_ReadByte(ifile);
        } else {
          for (int i = 0; i < (command + 1); i++)
            cf_ReadByte(ifile);
        }

        cur_width += (command + 1);
      } else if (command >= -127 && command < 0) {
        int run = (-command) + 1;
        int repeat_byte = cf_ReadByte(ifile);

        if (!skip_mask) {
          for (int i = 0; i < run; i++)
            *p++ = repeat_byte;
        }

        cur_width += run;
      }
    }
  }

  return IFF_NO_ERROR;
}

//  the buffer pointed to by raw_data is stuffed with a pointer to bitplane pixel data
void bm_iff_skip_chunk(CFILE *ifile, uint32_t len) {
  uint32_t i;

  for (i = 0; i < len; i++)
    cf_ReadByte(ifile);
}

// modify passed bitmap
int bm_iff_parse_delta(CFILE *ifile, int len, iff_bitmap_header *bmheader) {
  uint8_t *p = bmheader->raw_data;
  int y;
  int32_t chunk_end = cftell(ifile) + len;

  cf_ReadInt(ifile); // longword, seems to be equal to 4.  Don't know what it is

  for (y = 0; y < bmheader->h; y++) {
    uint8_t n_items;
    int cnt = bmheader->w;
    uint8_t code;

    n_items = cf_ReadByte(ifile);

    while (n_items--) {
      code = cf_ReadByte(ifile);

      if (code == 0) {
        uint8_t rep, val;

        rep = cf_ReadByte(ifile);
        val = cf_ReadByte(ifile);

        cnt -= rep;
        if (cnt == -1)
          rep--;
        while (rep--)
          *p++ = val;
      } else if (code > 0x80) { // skip
        cnt -= (code - 0x80);
        p += (code - 0x80);
        if (cnt == -1)
          p--;
      } else { // literal
        cnt -= code;
        if (cnt == -1)
          code--;

        while (code--)
          *p++ = cf_ReadByte(ifile);

        if (cnt == -1)
          cf_ReadByte(ifile);
      }
    }

    if (cnt == -1) {
      if (!bmheader->w & 1)
        return IFF_CORRUPT;
    } else if (cnt)
      return IFF_CORRUPT;
  }

  if (cftell(ifile) == chunk_end - 1) // pad
    cf_ReadByte(ifile);

  if (cftell(ifile) != chunk_end) {
    Int3();
    return IFF_CORRUPT;
  }

  else
    return IFF_NO_ERROR;
}

// read an PBM
// Pass pointer to opened file, and to empty bitmap_header structure, and form length
int bm_iff_parse_file(CFILE *ifile, iff_bitmap_header *bmheader, iff_bitmap_header *prev_bm) {
  uint32_t sig, len;
  int done = 0;

  while (!done) {
    if (cfeof(ifile)) {
      done = 1;
      continue;
    }

    sig = bm_iff_get_sig(ifile);

    len = cf_ReadInt(ifile);
    len = MOTOROLA_INT(len);

    switch (sig) {
    case IFF_SIG_FORM: {
      int newsig = bm_iff_get_sig(ifile);
      bmheader->type = TYPE_PBM;
      break;
    }
    case IFF_SIG_BMHD: {
      int ret;

      ret = bm_iff_parse_bmhd(ifile, len, bmheader);
      if (ret != IFF_NO_ERROR)
        return ret;
      else {

        bmheader->raw_data = (uint8_t *)mem_malloc(bmheader->w * bmheader->h);
        if (!bmheader->raw_data)
          return IFF_NO_MEM;
      }

    } break;
    case IFF_SIG_ANHD: {

      if (!prev_bm) {
        Int3();
        return IFF_CORRUPT;
      }

      bmheader->w = prev_bm->w;
      bmheader->h = prev_bm->h;
      bmheader->type = prev_bm->type;
      bmheader->raw_data = (uint8_t *)mem_malloc(bmheader->w * bmheader->h);

      if (!bmheader->raw_data)
        return IFF_NO_MEM;

      memcpy(bmheader->raw_data, prev_bm->raw_data, bmheader->w * bmheader->h);

      if (len & 1)
        len++;
      bm_iff_skip_chunk(ifile, len);

      break;
    }

    case IFF_SIG_CMAP: {
      int ncolors = (int)(len / 3), cnum;
      uint8_t r, g, b;

      for (cnum = 0; cnum < ncolors; cnum++) {
        r = cf_ReadByte(ifile);
        g = cf_ReadByte(ifile);
        b = cf_ReadByte(ifile);
        r >>= 2;
        bmheader->palette[cnum].r = r;
        g >>= 2;
        bmheader->palette[cnum].g = g;
        b >>= 2;
        bmheader->palette[cnum].b = b;
      }
      if (len & 1)
        cf_ReadByte(ifile);

    } break;

    case IFF_SIG_BODY: {
      int r;
      if ((r = bm_iff_parse_body(ifile, len, bmheader)) != IFF_NO_ERROR)
        return r;
      done = 1;
      break;
    }
    case IFF_SIG_DELTA: {
      int r;
      if ((r = bm_iff_parse_delta(ifile, len, bmheader)) != IFF_NO_ERROR)
        return r;
      done = 1;
      break;
    }

    default:
      // Don't know this chunk
      if (len & 1)
        len++;
      bm_iff_skip_chunk(ifile, len);
      break;
    }
  }

  return IFF_NO_ERROR; /* ok! */
}

void bm_iff_convert_8_to_16(int dest_bm, iff_bitmap_header *iffbm) {
  ASSERT(bm_w(dest_bm, 0) == iffbm->w);
  ASSERT(bm_h(dest_bm, 0) == iffbm->h);

  uint16_t *data;

  data = (uint16_t *)bm_data(dest_bm, 0);

  for (int i = 0; i < iffbm->h; i++)
    for (int t = 0; t < iffbm->w; t++) {
      uint16_t pixel;
      uint8_t c = iffbm->raw_data[i * iffbm->w + t];

      int r = iffbm->palette[c].r >> 1;
      int g = iffbm->palette[c].g >> 1;
      int b = iffbm->palette[c].b >> 1;

      pixel = OPAQUE_FLAG | (r << 10) | (g << 5) | b;
      if (c == iffbm->transparentcolor)
        pixel = NEW_TRANSPARENT_COLOR;

      data[i * bm_w(dest_bm, 0) + t] = pixel;
    }
}

// Loads an iff into a structure, allocs bitmap memory and converts 8 bit iff file into
// 16bit bitmap
// Returns bitmap handle on success, or -1 if failed
int bm_iff_alloc_file(CFILE *ifile) {
  int ret; // return code
  iff_bitmap_header bmheader;
  int src_bm;
  char cur_sig[4];

  // Ignore FORM and form length
  cf_ReadInt(ifile);
  cf_ReadInt(ifile);

  // check if this an ILBM

  for (int i = 0; i < 4; i++)
    cur_sig[i] = cf_ReadByte(ifile);

  if (strncmp("PBM ", cur_sig, 4)) {
    mprintf(0, "IFF file isn't a PBM...aborting.\n");
    return -1;
  }
  if (!strncmp("PBM ", cur_sig, 4))
    bmheader.type = TYPE_PBM;
  else
    Int3(); // Huh? Get Jason!

  ret = bm_iff_parse_file(ifile, &bmheader, NULL);

  if (ret != IFF_NO_ERROR) {
    mprintf(0, "Couldn't load IFF file.\n");
    return -1;
  }

  // Alloc our bitmap
  src_bm = bm_AllocBitmap(bmheader.w, bmheader.h, 0);
  if (src_bm < 0) {
    mem_free(bmheader.raw_data);
    return -1;
  }

  // Convert our 8 bit bitmap to 16bit
  bm_iff_convert_8_to_16(src_bm, &bmheader);
  free(bmheader.raw_data);

  return src_bm;
}

// returns number of bitmaps or -1 on error
int bm_iff_read_animbrush(const char *ifilename, int *bm_list) {
  CFILE *ifile;
  iff_bitmap_header bm_headers[40];
  iff_bitmap_header *temp_bm_head;
  int32_t sig, form_len;
  int32_t form_type;
  int num_bitmaps = 0;
  int ret, i;

  for (int t = 0; t < 40; t++)
    bm_headers[t].raw_data = 0;

  ifile = cfopen(ifilename, "rb");
  if (!ifile)
    return -1;

  sig = bm_iff_get_sig(ifile);
  form_len = cf_ReadInt(ifile);

  if (sig != IFF_SIG_FORM) {
    mprintf(0, "Not a valid IFF file.\n");
    cfclose(ifile);
    return -1;
  }

  form_type = bm_iff_get_sig(ifile);

  if (form_type == IFF_SIG_ANIM) {
    while (!cfeof(ifile) && num_bitmaps < 40) {
      ret = bm_iff_parse_file(ifile, &bm_headers[num_bitmaps], num_bitmaps > 0 ? &bm_headers[num_bitmaps - 1] : NULL);

      if (ret != IFF_NO_ERROR)
        goto done;

      num_bitmaps++;
    }

  } else {
    cfclose(ifile);
    return -1;
  }

done:
  cfclose(ifile);

  for (i = 0; i < num_bitmaps; i++) {
    int src_bm;
    temp_bm_head = &bm_headers[i];

    memcpy(temp_bm_head->palette, bm_headers[0].palette, sizeof(pal_entry) * 256);
    temp_bm_head->transparentcolor = bm_headers[0].transparentcolor;

    src_bm = bm_AllocBitmap(temp_bm_head->w, temp_bm_head->h, 0);
    ASSERT(src_bm > 0);

    bm_iff_convert_8_to_16(src_bm, temp_bm_head);
    bm_list[i] = src_bm;
  }

  for (i = 0; i < num_bitmaps; i++)
    mem_free(bm_headers[i].raw_data);

  return num_bitmaps;
}
