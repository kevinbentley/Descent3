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
#include "bumpmap.h"
#include "pstypes.h"
#include "pserror.h"
#include "mono.h"
#include "mem.h"

static int Num_of_bumpmaps = 0;
static uint16_t Free_bumpmap_list[MAX_BUMPMAPS];

// MTS: only used in this file?
bms_bumpmap GameBumpmaps[MAX_BUMPMAPS];
static int Bumpmap_mem_used = 0;

// Sets all the bumpmaps to unused
void bump_InitBumpmaps() {
  int i;

  for (i = 0; i < MAX_BUMPMAPS; i++) {
    GameBumpmaps[i].flags = 0;
    GameBumpmaps[i].data = NULL;
    GameBumpmaps[i].cache_slot = -1;
    Free_bumpmap_list[i] = i;
  }

  atexit(bump_ShutdownBumpmaps);
}
void bump_ShutdownBumpmaps(void) {
  int i;

  mprintf(0, "Freeing all bumpmap memory.\n");

  for (i = 0; i < MAX_BUMPMAPS; i++) {
    while (GameBumpmaps[i].flags & BUMPF_USED)
      bump_FreeBumpmap(i);
  }
}

// Allocs a bumpmap of w*h size
// Returns bumpmap handle if successful, -1 if otherwise

int bump_AllocBumpmap(int w, int h) {
  int n; //,i;

  if (Num_of_bumpmaps == MAX_BUMPMAPS)
    Int3(); // Ran out of bumpmaps!

  n = Free_bumpmap_list[Num_of_bumpmaps++];
  ASSERT(!(GameBumpmaps[n].flags & BUMPF_USED));

  // If no go on the malloc, bail out with -1

  memset(&GameBumpmaps[n], 0, sizeof(bms_bumpmap));

  GameBumpmaps[n].data = (uint16_t *)mem_malloc(w * h * 2);
  if (!GameBumpmaps[n].data) {
    mprintf(0, "NOT ENOUGHT MEMORY FOR BUMPMAP!\n");
    Int3();
    return BAD_BUMP_INDEX;
  }

  GameBumpmaps[n].cache_slot = -1;
  GameBumpmaps[n].flags = BUMPF_USED | BUMPF_CHANGED;
  GameBumpmaps[n].width = w;
  GameBumpmaps[n].height = h;

  Bumpmap_mem_used += (w * h * 2);

  return n;
}

// Given a handle, frees the bumpmap memory and flags this bumpmap as unused
void bump_FreeBumpmap(int handle) {
  ASSERT(GameBumpmaps[handle].flags & BUMPF_USED);

  if (GameBumpmaps[handle].data != NULL)
    mem_free(GameBumpmaps[handle].data);

  Bumpmap_mem_used -= (GameBumpmaps[handle].width * GameBumpmaps[handle].height * 2);

  GameBumpmaps[handle].data = NULL;
  GameBumpmaps[handle].flags &= ~BUMPF_USED;

  Free_bumpmap_list[--Num_of_bumpmaps] = handle;
}

// returns a bumpmaps data else NULL if something is wrong
uint16_t *bump_data(int handle) {
  uint16_t *d;

  if (!(GameBumpmaps[handle].flags & BUMPF_USED)) {
    Int3();
    return NULL;
  }

  d = GameBumpmaps[handle].data;

  return (d);
}

// returns width of bumpmap
uint8_t bump_w(int handle) {
  ASSERT(GameBumpmaps[handle].flags & BUMPF_USED);
  return GameBumpmaps[handle].width;
}

// returns height of bumpmap
uint8_t bump_h(int handle) {
  ASSERT(GameBumpmaps[handle].flags & BUMPF_USED);
  return GameBumpmaps[handle].height;
}
