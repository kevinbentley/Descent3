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

 * $Logfile: /DescentIII/main/hotspotmap.h $
 * $Revision: 10 $
 * $Date: 4/17/99 6:15p $
 * $Author: Samir $
 *
 * Hotspot stuff for TelCom
 *
 * $Log: /DescentIII/main/hotspotmap.h $
 *
 * 10    4/17/99 6:15p Samir
 * replaced gr.h with grdefs.h and fixed resulting compile bugs.
 *
 * 9     3/23/98 2:18p Jeff
 * Moved structures from telcom.h to here to make less dependent
 *
 * 8     3/23/98 9:55a Jeff
 * Made changes to remove old telcom
 *
 * 7     3/18/98 8:00p Jeff
 * Added some functionality for text and using the monitor borders
 * correctly in the new Telcom
 *
 * 6     3/12/98 3:56p Jeff
 * Added header comments to file
 *
 * $NoKeywords: $
 */

#ifndef __HOTSPOTMAP_H_
#define __HOTSPOTMAP_H_

#include <filesystem>
#include "grdefs.h"

// for the next two defines this is how they work when converting the alpha values into hotspots/windows
// 0 to MAX_HOTSPOTS-1 = HotSpot (button)
// MAX_HOTSPOTS to 255 = Window Display
// The NO_ALPHA value is which value (0-255) means it's neither HotSpot or Window
#define MAX_HOTSPOTS 128
#define NO_ALPHA 255
#define WRITEABLE_ALPHA 254
#define MAX_MAP_WIDTH 640  // Max hotspot map width
#define MAX_MAP_HEIGHT 480 // Max hotspot map height
#define TELCOM_MAX_ALPHA 130

// structure for a hotspot scanline
struct scanline {
  int start, end;
};

// structure for 1 hotspot
struct hotspot {
  int starting_y;
  int scanlines;
  scanline *x;
};

// structure for all hotspots
struct hotspotmap_t {
  char num_of_hotspots;
  hotspot *hs;
};

// structure for 1 window
struct window_box {
  int x, y; // leftmost x, topmost y
  int width, height;

  int l_start_x, l_end_x, r_start_x, r_end_x, t_top_y, t_bottom_y, b_top_y, b_bottom_y;
  bool on_left, on_top;    // used for creating window
  char *lt, *rt, *lb, *rb; // used for holding the transparent information of the corners
  int lt_bmp, rt_bmp, lb_bmp, rb_bmp;
};

// structure for all the windows
struct windowmap_t {
  int num_of_windows;
  window_box *wm;
};

// Loads a tga or ogf file into a bitmap...returns handle to bm or -1 on error, and fills in the alphamap
int menutga_alloc_file(const char *name, char *hsmap[], int *w, int *h);
// Given a filename and a HotSpotMap structure, it saves it to disk (.HSM)
void menutga_SaveHotSpotMap(const std::filesystem::path &filename, hotspotmap_t *hsmap, windowmap_t *wndmap);
// Given a filename and a HotSpotMap structure, it loads the hotspot map (.HSM)
void menutga_LoadHotSpotMap(int back_bmp, const char *filename, hotspotmap_t *hsmap, windowmap_t *wndmap);
// This function (given a filename) loads a TGA file, extracts a hotspot map, and saves the hotspot map
bool menutga_ConvertTGAtoHSM(const char *filename);

void ExportHotSpot(const char *filename, hotspotmap_t *hsmap); // Exports a hotspotmap to an ASCII file, nice and readable
void DisplayHotSpots(hotspotmap_t *hsmap,
                     windowmap_t *wndmap); // Displays the hotspots of the given hotspot map to the screen (in blue)
void FreeHotSpotMapInternals(hotspotmap_t *hsmap); // Deletes allocated memory within a hotspotmap struct
uint16_t menutga_translate_pixel(int pixel, char *alpha_value);

#endif
