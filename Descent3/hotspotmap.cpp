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

 * $Logfile: /DescentIII/main/hotspotmap.cpp $
 * $Revision: 19 $
 * $Date: 4/19/00 5:07p $
 * $Author: Matt $
 *
 * Contains the code for the hotspotmap functions (used in TelCom)
 *
 * $Log: /DescentIII/main/hotspotmap.cpp $
 *
 * 19    4/19/00 5:07p Matt
 * From Duane for 1.4
 * Added checks, asserts, and fixes for bad return values
 *
 * 18    4/17/99 6:15p Samir
 * replaced gr.h with grdefs.h and fixed resulting compile bugs.
 *
 * 17    4/14/99 2:50a Jeff
 * fixed some case mismatched #includes
 *
 * 16    1/21/99 11:15p Jeff
 * pulled out some structs and defines from header files and moved them
 * into seperate header files so that multiplayer dlls don't require major
 * game headers, just those new headers.  Side effect is a shorter build
 * time.  Also cleaned up some header file #includes that weren't needed.
 * This affected polymodel.h, object.h, player.h, vecmat.h, room.h,
 * manage.h and multi.h
 *
 * 15    10/15/98 1:36p Jeff
 * fixed bug vc6 caught
 *
 * 14    10/08/98 4:23p Kevin
 * Changed code to comply with memory library usage. Always use mem_malloc
 * , mem_free and mem_strdup
 *
 * 13    8/15/98 2:49p Matt
 * Took out unneeded include
 *
 * 12    4/23/98 6:38p Jason
 * made bitmaps use 1555 format
 *
 * 11    3/23/98 9:55a Jeff
 * Made changes to remove old telcom
 *
 * 10    3/18/98 8:00p Jeff
 * Added some functionality for text and using the monitor borders
 * correctly in the new Telcom
 *
 * 9     3/12/98 3:32p Jeff
 * Initial changes started for New TelCom
 *
 * 8     2/08/98 5:02p Samir
 * Commented out use of Game_viewport code.
 *
 * 7     1/15/98 11:13a Jeff
 * Got Telcom working again, switched from 2d to 3d
 *
 * 6     10/15/97 5:20p Jason
 * did a HUGE overhaul of the bitmap system
 *
 * 5     8/15/97 12:24p Jeff
 * Changed things around a bit, added code to handle the round corners
 *
 * 4     8/13/97 3:13p Jeff
 * optimized for memory usage (removed the second background from being
 * stored in memory)
 *
 * 3     8/04/97 7:23p Jeff
 *
 * 2     8/04/97 6:23p Jeff
 *
 * 1     8/04/97 6:23p Jeff
 *
 * 2     8/01/97 2:36p Jeff
 *
 * 1     8/01/97 2:35p Jeff
 *
 * 2     8/01/97 2:35p Jeff
 *
 * $NoKeywords: $
 */

#include "mono.h"
#include "renderer.h"
#include "render.h"
#include "grdefs.h"
#include "ddio.h"
#include "descent.h"
#include "game.h"
#include "cfile.h"
#include "application.h"
#include <stdlib.h>
#include <string.h>
#include "hotspotmap.h"
#include "mem.h"
#include "bitmap.h"
#include "manage.h"

static void makecorner(int corner_bmp, int back_bmp, const char *tmap, int l, int t, int r, int b);
static int CreateHotSpotMap(const char *map, int width, int height, hotspotmap_t *hsmap);
static void CreateWindowMap(const char *map, int width, int height, windowmap_t *wndmap);

// just like the old bm_tga_translate_pixel function, but it stores the alpha in the alpha_value parameter
uint16_t menutga_translate_pixel(int pixel, char *alpha_value) {
  int red = ((pixel >> 16) & 0xFF);
  int green = ((pixel >> 8) & 0xFF);
  int blue = ((pixel) & 0xFF);
  int alpha = ((pixel >> 24) & 0xFF);

  *alpha_value = alpha;

  int newred = red >> 3;
  int newgreen = green >> 3;
  int newblue = blue >> 3;
  uint16_t newpix = OPAQUE_FLAG | (newred << 10) | (newgreen << 5) | (newblue);
  if (alpha == 0)
    newpix = NEW_TRANSPARENT_COLOR;

  return newpix;
}

// This takes a char array filled with alphavalues from the TGA and fills in a hotspotmap_t struct with the
// scanline info
// returns the number of windows it found while making the hotspot map
#define HOTSPOT_THERE 1
#define WINDOW_THERE 2
#define NOTHING_THERE 0

int CreateHotSpotMap(const char *map, int width, int height, hotspotmap_t *hsmap) {
  // make sure we have a clean struct to work with
  if (hsmap->hs) {
    FreeHotSpotMapInternals(hsmap);
  }

  int curr_sl, x, y, count, num_hs = 0;
  uint8_t alpha;
  char whats_there[256];
  int window_count;

  for (count = 0; count < 256; count++)
    whats_there[count] = NOTHING_THERE;

  // Get total number of hotspots (based on highest hotspot value)
  for (y = 0; y < height; y++) {
    for (x = 0; x < width; x++) {
      alpha = (unsigned)map[y * width + x];
      if ((alpha != NO_ALPHA) && (alpha != WRITEABLE_ALPHA) && (whats_there[alpha] == NOTHING_THERE)) {
        if (alpha < MAX_HOTSPOTS) {
          whats_there[alpha] = HOTSPOT_THERE;
          if (alpha >= num_hs)
            num_hs = alpha + 1;
        } else {
          whats_there[alpha] = WINDOW_THERE;
        }
      }
    }
  }

  hsmap->num_of_hotspots = num_hs;
  if (!num_hs)
    return -1;

  hsmap->hs = (hotspot *)mem_malloc(sizeof(hotspot) * num_hs);
  ASSERT(hsmap->hs);
  for (count = 0; count < num_hs; count++) {
    if (whats_there[count] == HOTSPOT_THERE) {
      hsmap->hs[count].starting_y = MAX_MAP_HEIGHT;
      hsmap->hs[count].scanlines = 0;
    } else {
      hsmap->hs[count].starting_y = 0;
      hsmap->hs[count].scanlines = 0;
    }
  }

  scanline sl_x[MAX_MAP_HEIGHT];
  int sl_count, last_y = -1;

  // this is to set the values of start and end initially
  for (count = 0; count < MAX_MAP_HEIGHT; count++) {
    sl_x[count].start = MAX_MAP_WIDTH;
    sl_x[count].end = 0;
  }

  // fill in hotspot info
  // this is really nasty...MUST MAKE BETTER
  for (count = 0; count < num_hs; count++) {
    if (whats_there[count] == HOTSPOT_THERE) {
      sl_count = 0;
      // Get start,end, scanlines and starting_y for each hotspot
      for (y = 0; y < height; y++) {
        for (x = 0; x < width; x++) {
          if ((unsigned)map[y * width + x] == (uint8_t)count) {
            if (last_y != y)
              sl_count++;
            if (hsmap->hs[count].starting_y > y)
              hsmap->hs[count].starting_y = y;
            if (sl_x[y].start > x)
              sl_x[y].start = x;
            if (sl_x[y].end < x)
              sl_x[y].end = x;
            last_y = y;
          }
        }
      }
      // fill in the struct with the start and end values for each scanline
      hsmap->hs[count].scanlines = sl_count;
      if (sl_count) {
        hsmap->hs[count].x = (scanline *)mem_malloc(sizeof(scanline) * sl_count);
        ASSERT(hsmap->hs[count].x);
        memset(hsmap->hs[count].x, 0, sizeof(scanline) * sl_count);
        y = hsmap->hs[count].starting_y;
        for (curr_sl = 0; curr_sl < sl_count; curr_sl++) {
          hsmap->hs[count].x[curr_sl].start = sl_x[y].start;
          hsmap->hs[count].x[curr_sl].end = sl_x[y].end;
          sl_x[y].start = MAX_MAP_WIDTH;
          sl_x[y].end = 0;
          y++;
        } // end for (curr_sl)
      }   // end if (sl_count)
    } else {
      hsmap->hs[count].scanlines = 0;
      hsmap->hs[count].starting_y = 0;
      hsmap->hs[count].x = NULL;
    } // end ifelse (hotspot_there)
  }   // end for (count)

  mprintf(0, "Hunting down empty hotspots....\n");
  for (count = 0; count < num_hs; count++) {
    if (whats_there[count] == NOTHING_THERE) {
      mprintf(0, "Notice: HotSpot %d is empty\n", count);
      hsmap->hs[count].scanlines = 0;
      hsmap->hs[count].starting_y = 0;
      if (hsmap->hs[count].x) {
        mem_free(hsmap->hs[count].x);
      }
      hsmap->hs[count].x = NULL;
    }
  }

  mprintf(0, "Finding window count...");
  window_count = 0;
  for (count = 0; count < 256; count++) {
    if (whats_there[count] == WINDOW_THERE)
      window_count++;
  }
  mprintf(0, "%d windows found\n", window_count);
  return window_count;
}

void CreateWindowMap(const char *map, int width, int height, windowmap_t *wndmap) {
  mprintf(0, "Processing %d windows\n", wndmap->num_of_windows);
  int x, y, count;
  uint8_t alpha;
  bool newline = true;

  wndmap->wm = (window_box *)mem_malloc(sizeof(window_box) * wndmap->num_of_windows);
  ASSERT(wndmap->wm);

  for (int index = 0; index < wndmap->num_of_windows; index++) {
    wndmap->wm[index].lt = NULL;
    wndmap->wm[index].rt = NULL;
    wndmap->wm[index].lb = NULL;
    wndmap->wm[index].rb = NULL;
  }

  for (count = 0; count < wndmap->num_of_windows; count++) {
    wndmap->wm[count].x = wndmap->wm[count].y = wndmap->wm[count].width = wndmap->wm[count].height = -1;
    wndmap->wm[count].t_top_y = wndmap->wm[count].b_top_y = -1;
    wndmap->wm[count].t_bottom_y = wndmap->wm[count].b_bottom_y = 0;
    wndmap->wm[count].l_start_x = wndmap->wm[count].r_start_x = MAX_MAP_WIDTH;
    wndmap->wm[count].l_end_x = wndmap->wm[count].r_end_x = 0;
    wndmap->wm[count].on_left = wndmap->wm[count].on_top = true;
  }

  int working_window = -1;

  for (y = 0; y < height; y++) {
    newline = true;
    working_window = -1;
    for (x = 0; x < width; x++) {
      alpha = (unsigned)map[y * width + x];
      if (alpha != 255) {
        if (alpha >= 130)
          alpha = alpha;
      }
      if ((alpha >= MAX_HOTSPOTS) && (alpha != NO_ALPHA)) {
        // set the working_window value (needed so we know which window to work with for the writeable
        if (alpha != WRITEABLE_ALPHA) {
          working_window = alpha - MAX_HOTSPOTS;
        }

        if (newline) {
          int count;
          for (count = 0; count < wndmap->num_of_windows; count++)
            wndmap->wm[count].on_left = true;
          newline = false;
        }

        // Set an initial value for x and y of a window
        if ((wndmap->wm[working_window].x == -1) && (alpha != WRITEABLE_ALPHA)) {
          wndmap->wm[working_window].x = x;
          wndmap->wm[working_window].y = y;
        }

        // Set an initial value for the write_x and write_y for a window
        if ((alpha == WRITEABLE_ALPHA) && (working_window >= 0)) {
          if (wndmap->wm[working_window].t_top_y != -1) {
            if (wndmap->wm[working_window].l_end_x < x - 1) {
              wndmap->wm[working_window].on_left = false;
            } else {
              wndmap->wm[working_window].on_left = true;
            }

            if (wndmap->wm[working_window].t_bottom_y < y - 1) {
              wndmap->wm[working_window].on_top = false;
            } else {
              wndmap->wm[working_window].on_top = true;
            }
          } else {
            wndmap->wm[working_window].on_left = true;
            wndmap->wm[working_window].on_top = true;
          }

          // first time init
          if ((wndmap->wm[working_window].t_top_y == -1) && (wndmap->wm[working_window].on_top)) {
            wndmap->wm[working_window].t_top_y = y;
            wndmap->wm[working_window].t_bottom_y = y;
          }
          if ((wndmap->wm[working_window].b_top_y == -1) && (!wndmap->wm[working_window].on_top)) {
            wndmap->wm[working_window].b_top_y = y;
            wndmap->wm[working_window].b_bottom_y = y;
          }

          // adjust bottom
          if (wndmap->wm[working_window].on_top) {
            if (wndmap->wm[working_window].t_bottom_y < y) {
              wndmap->wm[working_window].t_bottom_y = y;
            }
          } else {
            if (wndmap->wm[working_window].b_bottom_y < y) {
              wndmap->wm[working_window].b_bottom_y = y;
            }
          }

          // adjust edges
          if (wndmap->wm[working_window].on_left) {
            if (wndmap->wm[working_window].l_start_x > x) {
              wndmap->wm[working_window].l_start_x = x;
            }
            if (wndmap->wm[working_window].l_end_x < x) {
              wndmap->wm[working_window].l_end_x = x;
            }
          } else {
            if (wndmap->wm[working_window].r_start_x > x) {
              wndmap->wm[working_window].r_start_x = x;
            }
            if (wndmap->wm[working_window].r_end_x < x) {
              wndmap->wm[working_window].r_end_x = x;
            }
          }
        }

        if (alpha != WRITEABLE_ALPHA) {
          // adjust width and height
          if ((wndmap->wm[working_window].x != -1) && (x > wndmap->wm[working_window].x) &&
              (x - wndmap->wm[working_window].x > wndmap->wm[working_window].width)) {
            wndmap->wm[working_window].width = x - wndmap->wm[working_window].x;
          }

          if ((y - wndmap->wm[working_window].y != -1) && (y > y - wndmap->wm[working_window].y) &&
              (y - wndmap->wm[working_window].y > wndmap->wm[working_window].height)) {
            wndmap->wm[working_window].height = y - wndmap->wm[working_window].y;
          }
        }
      } // end if
    }   // end for x
  }     // end for y

  for (count = 0; count < wndmap->num_of_windows; count++) {
    int h, w;
    int x, y, real_x, real_y;
    int *left_x, *right_x, *top_y, *bottom_y;
    char *array;
    uint8_t alpha;

    // left top
    left_x = &wndmap->wm[count].l_start_x;
    right_x = &wndmap->wm[count].l_end_x;
    top_y = &wndmap->wm[count].t_top_y;
    bottom_y = &wndmap->wm[count].t_bottom_y;

    if (*top_y != -1) {
      w = *right_x - *left_x;
      h = *bottom_y - *top_y;
      wndmap->wm[count].lt = (char *)mem_malloc(w * h);
      array = wndmap->wm[count].lt;
      for (real_y = *top_y, y = 0; real_y < *bottom_y; real_y++, y++) {
        for (real_x = *left_x, x = 0; real_x < *right_x; real_x++, x++) {
          alpha = (unsigned)map[real_y * width + real_x];
          if (alpha == WRITEABLE_ALPHA) {
            array[y * w + x] = true;
          } else {
            array[y * w + x] = false;
          }
        }
      }

      // right top
      left_x = &wndmap->wm[count].r_start_x;
      right_x = &wndmap->wm[count].r_end_x;
      top_y = &wndmap->wm[count].t_top_y;
      bottom_y = &wndmap->wm[count].t_bottom_y;

      w = *right_x - *left_x;
      h = *bottom_y - *top_y;
      wndmap->wm[count].rt = (char *)mem_malloc(w * h);

      array = wndmap->wm[count].rt;
      for (real_y = *top_y, y = 0; real_y < *bottom_y; real_y++, y++) {
        for (real_x = *left_x, x = 0; real_x < *right_x; real_x++, x++) {
          alpha = (unsigned)map[real_y * width + real_x];
          if (alpha == WRITEABLE_ALPHA) {
            array[y * w + x] = true;
          } else {
            array[y * w + x] = false;
          }
        }
      }
    }

    // left bottom
    left_x = &wndmap->wm[count].l_start_x;
    right_x = &wndmap->wm[count].l_end_x;
    top_y = &wndmap->wm[count].b_top_y;
    bottom_y = &wndmap->wm[count].b_bottom_y;

    if (*top_y != -1) {
      w = *right_x - *left_x;
      h = *bottom_y - *top_y;
      wndmap->wm[count].lb = (char *)mem_malloc(w * h);
      array = wndmap->wm[count].lb;

      for (real_y = *top_y, y = 0; real_y < *bottom_y; real_y++, y++) {
        for (real_x = *left_x, x = 0; real_x < *right_x; real_x++, x++) {
          alpha = (unsigned)map[real_y * width + real_x];
          if (alpha == WRITEABLE_ALPHA) {
            array[y * w + x] = true;
          } else {
            array[y * w + x] = false;
          }
        }
      }

      // right bottom
      left_x = &wndmap->wm[count].r_start_x;
      right_x = &wndmap->wm[count].r_end_x;
      top_y = &wndmap->wm[count].b_top_y;
      bottom_y = &wndmap->wm[count].b_bottom_y;

      w = *right_x - *left_x;
      h = *bottom_y - *top_y;
      wndmap->wm[count].rb = (char *)mem_malloc(w * h);
      array = wndmap->wm[count].rb;
      for (real_y = *top_y, y = 0; real_y < *bottom_y; real_y++, y++) {
        for (real_x = *left_x, x = 0; real_x < *right_x; real_x++, x++) {
          alpha = (unsigned)map[real_y * width + real_x];
          if (alpha == WRITEABLE_ALPHA) {
            array[y * w + x] = true;
          } else {
            array[y * w + x] = false;
          }
        }
      }
    }
  }

  for (count = 0; count < wndmap->num_of_windows; count++) {
    mprintf(0, "Window #%d: Left/Top=(%d,%d) Width=%d Height=%d\n", count, wndmap->wm[count].x, wndmap->wm[count].y,
             wndmap->wm[count].width, wndmap->wm[count].height);
    mprintf(0, "---L.T. (%d,%d)->(%d,%d)\n", wndmap->wm[count].l_start_x, wndmap->wm[count].t_top_y,
             wndmap->wm[count].l_end_x, wndmap->wm[count].t_bottom_y);
    mprintf(0, "---R.T. (%d,%d)->(%d,%d)\n", wndmap->wm[count].r_start_x, wndmap->wm[count].t_top_y,
             wndmap->wm[count].r_end_x, wndmap->wm[count].t_bottom_y);
    mprintf(0, "---L.B. (%d,%d)->(%d,%d)\n", wndmap->wm[count].l_start_x, wndmap->wm[count].b_top_y,
             wndmap->wm[count].l_end_x, wndmap->wm[count].b_bottom_y);
    mprintf(0, "---R.B. (%d,%d)->(%d,%d)\n", wndmap->wm[count].r_start_x, wndmap->wm[count].b_top_y,
             wndmap->wm[count].r_end_x, wndmap->wm[count].b_bottom_y);
  }
}

// TODO: MTS: only used in this file
// Loads a tga or ogf file into a bitmap...returns handle to bm or -1 on error, and fills in the alphamap
int menutga_alloc_file(const char *name, char *hsmap[1], int *w, int *h) {
  uint8_t image_id_len, color_map_type, image_type, pixsize, descriptor;
  uint8_t upside_down = 0;
  uint16_t width, height;
  uint32_t pixel;
  int i, t, n;
  char alphavalue;
  CFILE *infile;

  if (!cfexist(name))
    return -1;

  infile = (CFILE *)cfopen(name, "rb");
  if (!infile) {
    Int3(); // get jeff!
  }

  image_id_len = cf_ReadByte(infile);
  color_map_type = cf_ReadByte(infile);
  image_type = cf_ReadByte(infile);

  if (color_map_type != 0 || (image_type != 2)) {
    mprintf(0, "menutga: Can't read this type of TGA.\n");
    return -1;
  }

  for (i = 0; i < 9; i++) // ingore next 9 bytes
    cf_ReadByte(infile);

  *w = width = cf_ReadShort(infile);
  *h = height = cf_ReadShort(infile);
  pixsize = cf_ReadByte(infile);

  hsmap[0] = (char *)mem_malloc(width * height);

  ASSERT(hsmap);

  if (pixsize != 32) {
    mprintf(0, "menutga: This file has a pixsize of field of %d, it should be 32. ", pixsize);
    return -1;
  }

  descriptor = cf_ReadByte(infile);
  if ((descriptor & 0x0F) != 8) {
    mprintf(0, "menutga: Descriptor field & 0x0F must be 8, but this is %d.", descriptor & 0x0F);
    return -1;
  }

  for (i = 0; i < image_id_len; i++)
    cf_ReadByte(infile);

  n = bm_AllocBitmap(width, height, 0);

  if (n < 0) {
    mprintf(0, "menutga: Failed to allocate memory.\n");
    Int3();
  }

  upside_down = (descriptor & 0x20) >> 5;
  upside_down = 1 - upside_down;

  // Load the actual bitmap data in, converting it from 32 bit to 16 bit, and replacing
  // that pesky transparency color without our replacement

  for (i = 0; i < height; i++) {
    for (t = 0; t < width; t++) {
      pixel = cf_ReadInt(infile);

      uint16_t newpix = menutga_translate_pixel(pixel, &alphavalue);

      if (upside_down) {
        GameBitmaps[n].data16[((height - 1) - i) * width + t] = newpix;
        hsmap[0][((height - 1) - i) * width + t] = alphavalue;
      } else {
        GameBitmaps[n].data16[i * width + t] = newpix;
        hsmap[0][i * width + t] = alphavalue;
      }
    }
  }

  cfclose(infile);
  return (n);
}

// TODO: MTS: only used in this file
// Given a filename and a hotspotmap structure, it saves it to disk (.HSM)
void menutga_SaveHotSpotMap(const std::filesystem::path &filename, hotspotmap_t *hsmap, windowmap_t *wndmap) {
  CFILE *file;
  mprintf(0, "Saving HotSpotMap %s ", filename.u8string().c_str());
  file = (CFILE *)cfopen(filename, "wb");
  if (!file) {
    Int3(); // get jeff!
    return;
  }

  int curr_hs, curr_sl;
  mprintf(0, "Number of HotSpots=%d\n", hsmap->num_of_hotspots);
  cf_WriteByte(file, hsmap->num_of_hotspots);

  for (curr_hs = 0; curr_hs < hsmap->num_of_hotspots; curr_hs++) {
    cf_WriteInt(file, hsmap->hs[curr_hs].starting_y);
    cf_WriteInt(file, hsmap->hs[curr_hs].scanlines);
    for (curr_sl = 0; curr_sl < hsmap->hs[curr_hs].scanlines; curr_sl++) {
      cf_WriteInt(file, hsmap->hs[curr_hs].x[curr_sl].start);
      cf_WriteInt(file, hsmap->hs[curr_hs].x[curr_sl].end);
    }
  }

  int count;
  int index, size;

  cf_WriteInt(file, wndmap->num_of_windows);
  for (count = 0; count < wndmap->num_of_windows; count++) {
    cf_WriteInt(file, wndmap->wm[count].x);
    cf_WriteInt(file, wndmap->wm[count].y);
    cf_WriteInt(file, wndmap->wm[count].width);
    cf_WriteInt(file, wndmap->wm[count].height);
    cf_WriteInt(file, wndmap->wm[count].l_start_x);
    cf_WriteInt(file, wndmap->wm[count].l_end_x);
    cf_WriteInt(file, wndmap->wm[count].r_start_x);
    cf_WriteInt(file, wndmap->wm[count].r_end_x);
    cf_WriteInt(file, wndmap->wm[count].t_top_y);
    cf_WriteInt(file, wndmap->wm[count].t_bottom_y);
    cf_WriteInt(file, wndmap->wm[count].b_top_y);
    cf_WriteInt(file, wndmap->wm[count].b_bottom_y);

    if (wndmap->wm[count].t_top_y != -1) {
      // left top
      size = ((wndmap->wm[count].l_end_x) - (wndmap->wm[count].l_start_x)) *
             ((wndmap->wm[count].t_bottom_y) - (wndmap->wm[count].t_top_y));
      for (index = 0; index < size; index++) {
        cf_WriteByte(file, wndmap->wm[count].lt[index]);
      }
      // right top
      size = ((wndmap->wm[count].r_end_x) - (wndmap->wm[count].r_start_x)) *
             ((wndmap->wm[count].t_bottom_y) - (wndmap->wm[count].t_top_y));
      for (index = 0; index < size; index++) {
        cf_WriteByte(file, wndmap->wm[count].rt[index]);
      }
    }
    if (wndmap->wm[count].b_top_y != -1) {
      // left bottom
      size = ((wndmap->wm[count].l_end_x) - (wndmap->wm[count].l_start_x)) *
             ((wndmap->wm[count].b_bottom_y) - (wndmap->wm[count].b_top_y));
      for (index = 0; index < size; index++) {
        cf_WriteByte(file, wndmap->wm[count].lb[index]);
      }
      // right bottom
      size = ((wndmap->wm[count].r_end_x) - (wndmap->wm[count].r_start_x)) *
             ((wndmap->wm[count].b_bottom_y) - (wndmap->wm[count].b_top_y));
      for (index = 0; index < size; index++) {
        cf_WriteByte(file, wndmap->wm[count].rb[index]);
      }
    }
  }
  cfclose(file);
}

// Given a filename and a hotspotmap structure, it loads the hotspot map (.HSM)
void menutga_LoadHotSpotMap(int back_bmp, const char *filename, hotspotmap_t *hsmap, windowmap_t *wndmap) {
  // start with a clean struct
  if (hsmap->hs) {
    FreeHotSpotMapInternals(hsmap);
  }

  mprintf(0, "Loading hotspotmap %s ", filename);

  CFILE *infile;
  infile = (CFILE *)cfopen(filename, "rb");
  if (!infile) {
    Int3(); // get Jeff
    return;
  }

  hsmap->num_of_hotspots = cf_ReadByte(infile);

  mprintf(0, "Contains: (%d hotspots) ", hsmap->num_of_hotspots);

  int curr_hs, curr_sl, num_sl;

  hsmap->hs = (hotspot *)mem_malloc(sizeof(hotspot) * hsmap->num_of_hotspots);
  memset(hsmap->hs, 0, sizeof(hotspot) * hsmap->num_of_hotspots);
  for (curr_hs = 0; curr_hs < hsmap->num_of_hotspots; curr_hs++) {
    hsmap->hs[curr_hs].starting_y = cf_ReadInt(infile);
    num_sl = hsmap->hs[curr_hs].scanlines = cf_ReadInt(infile);
    if (num_sl) {
      hsmap->hs[curr_hs].x = (scanline *)mem_malloc(sizeof(scanline) * hsmap->hs[curr_hs].scanlines);
      memset(hsmap->hs[curr_hs].x, 0, sizeof(scanline) * hsmap->hs[curr_hs].scanlines);
      for (curr_sl = 0; curr_sl < hsmap->hs[curr_hs].scanlines; curr_sl++) {
        hsmap->hs[curr_hs].x[curr_sl].start = cf_ReadInt(infile);
        hsmap->hs[curr_hs].x[curr_sl].end = cf_ReadInt(infile);
      }
    } else {
      hsmap->hs[curr_hs].x = NULL;
    }
  }

  int count, index, size;
  wndmap->num_of_windows = cf_ReadInt(infile);
  mprintf(0, "(%d Windows)\n", wndmap->num_of_windows);
  wndmap->wm = (window_box *)mem_malloc(sizeof(window_box) * wndmap->num_of_windows);
  for (count = 0; count < wndmap->num_of_windows; count++) {
    wndmap->wm[count].x = cf_ReadInt(infile);
    wndmap->wm[count].y = cf_ReadInt(infile);
    wndmap->wm[count].width = cf_ReadInt(infile);
    wndmap->wm[count].height = cf_ReadInt(infile);
    wndmap->wm[count].l_start_x = cf_ReadInt(infile);
    wndmap->wm[count].l_end_x = cf_ReadInt(infile);
    wndmap->wm[count].r_start_x = cf_ReadInt(infile);
    wndmap->wm[count].r_end_x = cf_ReadInt(infile);
    wndmap->wm[count].t_top_y = cf_ReadInt(infile);
    wndmap->wm[count].t_bottom_y = cf_ReadInt(infile);
    wndmap->wm[count].b_top_y = cf_ReadInt(infile);
    wndmap->wm[count].b_bottom_y = cf_ReadInt(infile);

    if (wndmap->wm[count].t_top_y != -1) {
      // left top
      size = ((wndmap->wm[count].l_end_x) - (wndmap->wm[count].l_start_x)) *
             ((wndmap->wm[count].t_bottom_y) - (wndmap->wm[count].t_top_y));
      wndmap->wm[count].lt = (char *)mem_malloc(size);
      for (index = 0; index < size; index++) {
        wndmap->wm[count].lt[index] = cf_ReadByte(infile);
      }

      // right top
      size = ((wndmap->wm[count].r_end_x) - (wndmap->wm[count].r_start_x)) *
             ((wndmap->wm[count].t_bottom_y) - (wndmap->wm[count].t_top_y));
      wndmap->wm[count].rt = (char *)mem_malloc(size);
      for (index = 0; index < size; index++) {
        wndmap->wm[count].rt[index] = cf_ReadByte(infile);
      }
    }

    if (wndmap->wm[count].b_top_y != -1) {
      // left bottom
      size = ((wndmap->wm[count].l_end_x) - (wndmap->wm[count].l_start_x)) *
             ((wndmap->wm[count].b_bottom_y) - (wndmap->wm[count].b_top_y));
      wndmap->wm[count].lb = (char *)mem_malloc(size);
      for (index = 0; index < size; index++) {
        wndmap->wm[count].lb[index] = cf_ReadByte(infile);
      }
      // right bottom
      size = ((wndmap->wm[count].r_end_x) - (wndmap->wm[count].r_start_x)) *
             ((wndmap->wm[count].b_bottom_y) - (wndmap->wm[count].b_top_y));
      wndmap->wm[count].rb = (char *)mem_malloc(size);
      for (index = 0; index < size; index++) {
        wndmap->wm[count].rb[index] = cf_ReadByte(infile);
      }
    }
  }
  cfclose(infile);

  // make the corner bitmaps, with transparency
  for (count = 0; count < wndmap->num_of_windows; count++) {
    if (wndmap->wm[count].t_top_y != -1) {
      // left top
      wndmap->wm[count].lt_bmp = bm_AllocBitmap(wndmap->wm[count].l_end_x - wndmap->wm[count].l_start_x,
                                                wndmap->wm[count].t_bottom_y - wndmap->wm[count].t_top_y, 0);
      makecorner(wndmap->wm[count].lt_bmp, back_bmp, wndmap->wm[count].lt, wndmap->wm[count].l_start_x,
                 wndmap->wm[count].t_top_y, wndmap->wm[count].l_end_x, wndmap->wm[count].t_bottom_y);

      // right top
      wndmap->wm[count].rt_bmp = bm_AllocBitmap(wndmap->wm[count].r_end_x - wndmap->wm[count].r_start_x,
                                                wndmap->wm[count].t_bottom_y - wndmap->wm[count].t_top_y, 0);
      makecorner(wndmap->wm[count].rt_bmp, back_bmp, wndmap->wm[count].rt, wndmap->wm[count].r_start_x,
                 wndmap->wm[count].t_top_y, wndmap->wm[count].r_end_x, wndmap->wm[count].t_bottom_y);
      if (wndmap->wm[count].lt)
        mem_free(wndmap->wm[count].lt);
      if (wndmap->wm[count].rt)
        mem_free(wndmap->wm[count].rt);
    }

    if (wndmap->wm[count].b_top_y != -1) {
      // left bottom
      wndmap->wm[count].lb_bmp = bm_AllocBitmap(wndmap->wm[count].l_end_x - wndmap->wm[count].l_start_x,
                                                wndmap->wm[count].b_bottom_y - wndmap->wm[count].b_top_y, 0);
      makecorner(wndmap->wm[count].lb_bmp, back_bmp, wndmap->wm[count].lb, wndmap->wm[count].l_start_x,
                 wndmap->wm[count].b_top_y, wndmap->wm[count].l_end_x, wndmap->wm[count].b_bottom_y);

      // right bottom
      wndmap->wm[count].rb_bmp = bm_AllocBitmap(wndmap->wm[count].r_end_x - wndmap->wm[count].r_start_x,
                                                wndmap->wm[count].b_bottom_y - wndmap->wm[count].b_top_y, 0);
      makecorner(wndmap->wm[count].rb_bmp, back_bmp, wndmap->wm[count].rb, wndmap->wm[count].r_start_x,
                 wndmap->wm[count].b_top_y, wndmap->wm[count].r_end_x, wndmap->wm[count].b_bottom_y);
      if (wndmap->wm[count].lb)
        mem_free(wndmap->wm[count].lb);
      if (wndmap->wm[count].rb)
        mem_free(wndmap->wm[count].rb);
    }
  }
}

void makecorner(int corner_bmp, int back_bmp, const char *tmap, int l, int t, int r, int b) {
  int real_x, real_y, awidth, ax, ay;
  int16_t *backdata, *cornerdata;
  int back_rowsize, corner_rowsize;

  awidth = r - l;
  bm_ClearBitmap(corner_bmp);
  backdata = (int16_t *)bm_data(back_bmp, 0);
  back_rowsize = bm_rowsize(back_bmp, 0);
  cornerdata = (int16_t *)bm_data(corner_bmp, 0);
  corner_rowsize = bm_rowsize(corner_bmp, 0);

  backdata += (t * (back_rowsize / 2));

  for (real_y = t, ay = 0; real_y < b; real_y++, ay++) {
    for (real_x = l, ax = 0; real_x < r; real_x++, ax++) {
      if (!tmap[ay * awidth + ax]) {
        // not transparent
        cornerdata[ax] = backdata[real_x];
      }
    }
    cornerdata += (corner_rowsize / 2);
    backdata += (back_rowsize / 2);
  }
}

// This function frees up the allocated memory within a hotspotmap struct.  It does not free up the struct though.
void FreeHotSpotMapInternals(hotspotmap_t *hsmap) {
  mprintf(0, "Freeing HSM internals\n");

  ASSERT(hsmap);

  if (!hsmap->hs)
    return;

  int curr_hs;
  int num_hs;

  num_hs = hsmap->num_of_hotspots;
  for (curr_hs = 0; curr_hs < num_hs; curr_hs++) {
    if (hsmap->hs[curr_hs].scanlines) {
      if (hsmap->hs[curr_hs].x) {
        mem_free(hsmap->hs[curr_hs].x);
        hsmap->hs[curr_hs].x = NULL;
      }
    }
  }
  if (hsmap->hs) {
    mem_free(hsmap->hs);
    hsmap->hs = NULL;
  }
}

// This function (given a filename) loads a TGA file, extracts a hotspot map, and saves the hotspot map
bool menutga_ConvertTGAtoHSM(const char *fpath) {
  char path[255], filename[255], ext[8];
  ddio_SplitPath(fpath, path, filename, ext);
  mprintf(0, "Extracting hotspots from %s\n", filename);

  // strip file name
  int index, width = 0, height = 0;
  char *menu_filename;
  hotspotmap_t hsmap;
  windowmap_t wndmap;

  wndmap.num_of_windows = 0;
  wndmap.wm = NULL;
  hsmap.hs = NULL;
  hsmap.num_of_hotspots = 0;

  for (index = (signed)strlen(filename); index >= 0; index--) {
    if (filename[index] == '.') {
      filename[index] = '\0';
      index = -1;
    }
  }

  int size = strlen(filename) + 5;
  menu_filename = (char *)mem_malloc(size);
  strcpy(menu_filename, filename);
  strcat(menu_filename, ".HSM"); // Hot Spot Map
  mprintf(0, "HSM=%s\n", menu_filename);

  std::filesystem::path save_path = LocalManageGraphicsDir / menu_filename;

  // now load up the tga and alloc it, then save it with the alpha hotspots
  int bm_handle;
  char *map[1];
  bm_handle = menutga_alloc_file(fpath, map, &width, &height);
  if (bm_handle == -1)
    return false;
  wndmap.num_of_windows = CreateHotSpotMap(map[0], width, height, &hsmap);
  if (wndmap.num_of_windows == -1)
    return false; // DAJ -1FIX
  CreateWindowMap(map[0], width, height, &wndmap);
  menutga_SaveHotSpotMap(save_path, &hsmap, &wndmap);
  ExportHotSpot("C:\\hotspot.txt", &hsmap);
  mem_free(menu_filename);
  mem_free(map[0]);
  FreeHotSpotMapInternals(&hsmap);
  for (index = 0; index < wndmap.num_of_windows; index++) {
    if (wndmap.wm[index].lt)
      mem_free(wndmap.wm[index].lt);
    if (wndmap.wm[index].rt)
      mem_free(wndmap.wm[index].rt);
    if (wndmap.wm[index].lb)
      mem_free(wndmap.wm[index].lb);
    if (wndmap.wm[index].rb)
      mem_free(wndmap.wm[index].rb);
  }
  if (wndmap.wm)
    mem_free(wndmap.wm);
  return true;
}

// TODO: MTS: Unused?
// Given a hotspotmap structure, it draws the pretty hotspot map to the screen (blue areas are the hotspots)
void DisplayHotSpots(hotspotmap_t *hsmap, windowmap_t *wndmap) {
  //@@	grSurface *cursurf;
  //@@	int count,curr_y,scanline_count;
  //@@	hotspot *curr_hotspot;
  //@@
  //@@
  //@@	cursurf=Game_viewport->lock();
  //@@	for(count=0;count<hsmap->num_of_hotspots;count++)
  //@@	{
  //@@		curr_hotspot=&hsmap->hs[count];
  //@@		curr_y=curr_hotspot->starting_y;
  //@@		for(scanline_count=0;scanline_count<curr_hotspot->scanlines;scanline_count++)
  //@@		{
  //@@			Game_viewport->hline(GR_RGB(0,0,255),curr_hotspot->x[scanline_count].start,
  //@@
  // curr_hotspot->x[scanline_count].end,curr_y+scanline_count);
  //@@		}
  //@@	}
  //@@
  //@@	for(count=0;count<wndmap->num_of_windows;count++)
  //@@	{
  //@@		for(scanline_count=0;scanline_count<curr_hotspot->scanlines;scanline_count++)
  //@@		{
  //@@			Game_viewport->fillrect(GR_RGB(255,0,0), wndmap->wm[count].x,wndmap->wm[count].y,
  //@@
  // wndmap->wm[count].x+wndmap->wm[count].width-1,wndmap->wm[count].y+wndmap->wm[count].height-1);
  //@@			//if there is a writeable area, display it
  //@@			if(wndmap->wm[count].t_top_y!=-1)
  //@@			{
  //@@				Game_viewport->fillrect(GR_RGB(128,128,128),
  // wndmap->wm[count].l_start_x,wndmap->wm[count].t_top_y,
  //@@					wndmap->wm[count].l_end_x,wndmap->wm[count].t_bottom_y);
  //@@				Game_viewport->fillrect(GR_RGB(128,128,128),
  // wndmap->wm[count].r_start_x,wndmap->wm[count].t_top_y,
  //@@					wndmap->wm[count].r_end_x,wndmap->wm[count].t_bottom_y);
  //@@			}
  //@@			if(wndmap->wm[count].b_top_y!=-1)
  //@@			{
  //@@				Game_viewport->fillrect(GR_RGB(128,128,128),
  // wndmap->wm[count].l_start_x,wndmap->wm[count].b_top_y,
  //@@					wndmap->wm[count].l_end_x,wndmap->wm[count].b_bottom_y);
  //@@				Game_viewport->fillrect(GR_RGB(128,128,128),
  // wndmap->wm[count].r_start_x,wndmap->wm[count].b_top_y,
  //@@					wndmap->wm[count].r_end_x,wndmap->wm[count].b_bottom_y);
  //@@			}
  //@@
  //@@		}
  //@@	}
  //@@
  //@@	Game_viewport->unlock();
  //@@	Game_screen->flip();
}

// TODO: MTS: only used in this file
// Writes a hotspotmap_t struct to a text file
void ExportHotSpot(const char *filename, hotspotmap_t *hsmap) {
  CFILE *file;
  file = (CFILE *)cfopen(filename, "wt");
  ASSERT(file);
  char buffer[256];

  int i, j;
  snprintf(buffer, sizeof(buffer), "Number of HotSpots = %d", hsmap->num_of_hotspots);
  cf_WriteString(file, buffer);
  for (i = 0; i < hsmap->num_of_hotspots; i++) {
    snprintf(buffer, sizeof(buffer), "\n-%d-Scanlines = %d", i, hsmap->hs[i].scanlines);
    cf_WriteString(file, buffer);
    for (j = 0; j < hsmap->hs[i].scanlines; j++) {
      snprintf(buffer, sizeof(buffer), "----Y=%d StartX=%d EndX=%d", hsmap->hs[i].starting_y + j,
               hsmap->hs[i].x[j].start, hsmap->hs[i].x[j].end);
      cf_WriteString(file, buffer);
    }
  }

  cfclose(file);
}
