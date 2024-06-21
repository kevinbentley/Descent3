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

#include <stdlib.h>
#include <string.h>
#include "lightmap.h"
#include "pstypes.h"
#include "pserror.h"
#include "bitmap.h"
#include "mono.h"
#include "mem.h"
#if !defined(__LINUX__) && !defined(ANDROID)
#include "Macros.h"
#endif

#include <algorithm>

static int Num_of_lightmaps = 0;
static uint16_t Free_lightmap_list[MAX_LIGHTMAPS];
bms_lightmap GameLightmaps[MAX_LIGHTMAPS];
static int Lightmap_mem_used = 0;
// Sets all the lightmaps to unused
void lm_InitLightmaps() {
  int i;
  for (i = 0; i < MAX_LIGHTMAPS; i++) {
    GameLightmaps[i].flags = 0;
    GameLightmaps[i].used = 0;
    GameLightmaps[i].data = NULL;
    GameLightmaps[i].cache_slot = -1;
    Free_lightmap_list[i] = i;
  }
  atexit(lm_ShutdownLightmaps);
}
void lm_ShutdownLightmaps(void) {
  int i;
  mprintf(0, "Freeing all lightmap memory.\n");
  for (i = 0; i < MAX_LIGHTMAPS; i++) {
    while (GameLightmaps[i].used > 0)
      lm_FreeLightmap(i);
  }
}
// Allocs a lightmap of w x h size
// Returns lightmap handle if successful, -1 if otherwise
int lm_AllocLightmap(int w, int h) {
  int n; //,i;
  if (Num_of_lightmaps == MAX_LIGHTMAPS)
    Int3(); // Ran out of lightmaps!

  n = Free_lightmap_list[Num_of_lightmaps++];
  ASSERT(GameLightmaps[n].used == 0);
  // If no go on the malloc, bail out with -1

  memset(&GameLightmaps[n], 0, sizeof(bms_lightmap));
  GameLightmaps[n].data = (uint16_t *)mem_malloc((w * h * 2));
  if (!GameLightmaps[n].data) {
    mprintf(0, "NOT ENOUGHT MEMORY FOR LIGHTMAP!\n");
    Int3();
    return BAD_LM_INDEX;
  }

  GameLightmaps[n].width = w;
  GameLightmaps[n].height = h;
  GameLightmaps[n].used = 1;
  GameLightmaps[n].cache_slot = -1;
  GameLightmaps[n].flags = LF_CHANGED;
  // Figure out square size
  // Find power of 2 number
  int res = std::max(w, h);
  int lightmap_res = 2;
  for (int i = 0; i <= 7; i++) {
    int low_num = 1 < i;
    int hi_num = 2 << i;
    if (res <= hi_num && res > low_num) {
      lightmap_res = hi_num;
      break;
    }
  }
  ASSERT(lightmap_res >= 2 && lightmap_res <= 128);
  GameLightmaps[n].square_res = lightmap_res;
  Lightmap_mem_used += (w * h * 2);

  return n;
}
// Given a handle, frees the lightmap memory and flags this lightmap as unused
void lm_FreeLightmap(int handle) {
  if (GameLightmaps[handle].used < 1)
    return;
  GameLightmaps[handle].used--;
  if (GameLightmaps[handle].used == 0) {
    if (GameLightmaps[handle].data != NULL)
      mem_free(GameLightmaps[handle].data);
    Lightmap_mem_used -= (GameLightmaps[handle].width * GameLightmaps[handle].height * 2);

    GameLightmaps[handle].data = NULL;
    GameLightmaps[handle].cache_slot = -1;

    Free_lightmap_list[--Num_of_lightmaps] = handle;
  }
}
// returns a lightmaps width  else -1 if something is wrong
int lm_w(int handle) {
  int w;
  if (!GameLightmaps[handle].used) {
    Int3();
    return -1;
  }
  w = GameLightmaps[handle].width;

  return (w);
}
// returns a lightmaps height , else -1 if something is wrong
int lm_h(int handle) {
  int h;
  if (!GameLightmaps[handle].used) {
    Int3();
    return -1;
  }
  h = GameLightmaps[handle].height;

  return (h);
}
// returns a lightmaps data else NULL if something is wrong
uint16_t *lm_data(int handle) {
  uint16_t *d;
  if (!GameLightmaps[handle].used) {
    Int3();
    return NULL;
  }

  d = GameLightmaps[handle].data;
  return (d);
}
