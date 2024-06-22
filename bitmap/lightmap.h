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
*/

#ifndef LIGHTMAP_H
#define LIGHTMAP_H

#include "pstypes.h"

#define MAX_LIGHTMAPS (65534)
#define BAD_LM_INDEX 65535

// lightmap flags
#define LF_CHANGED 1   // this bitmap has changed since last frame (useful for hardware cacheing)
#define LF_LIMITS 2    // This lightmap has a specific area that has changed since last frame
#define LF_WRAP 4      // This lightmap should be drawn with wrapping (not clamping)
#define LF_BRAND_NEW 8 // This lightmap is brand new and hasn't been to the video card yet

struct bms_lightmap {
  uint8_t width, height; // Width and height in pixels
  uint16_t *data;        // 16bit data

  uint16_t used;
  uint8_t flags;
  int16_t cache_slot;         // for the renderers use
  uint8_t square_res;         // for renderers use
  uint8_t cx1, cy1, cx2, cy2; // Change x and y coords
};

extern bms_lightmap GameLightmaps[MAX_LIGHTMAPS];

// Sets all the lightmaps to unused
void lm_InitLightmaps();

void lm_ShutdownLightmaps(void);

// Allocs a lightmap of w x h size
// Returns lightmap handle if successful, -1 if otherwise
int lm_AllocLightmap(int w, int h);

// Given a handle, frees the lightmap memory and flags this lightmap as unused
void lm_FreeLightmap(int handle);

// returns a lightmaps width  else -1 if something is wrong
int lm_w(int handle);

// returns a lightmaps height , else -1 if something is wrong
int lm_h(int handle);

// returns a lightmaps data else NULL if something is wrong
uint16_t *lm_data(int handle);

#endif
