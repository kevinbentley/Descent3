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

 * $Logfile: /DescentIII/Main/bitmap/bitmain.cpp $
 * $Revision: 70 $
 * $Date: 5/10/00 5:09p $
 * $Author: Matt $
 *
 * Bitmap handling functions
 *
 * $Log: /DescentIII/Main/bitmap/bitmain.cpp $
 *
 * 70    5/10/00 5:09p Matt
 * Added casts so code would compile under Visual C++.
 *
 * 69    5/10/00 4:34p Jeff
 * handle buggy tablefile editors that put the full path name to a
 * primative instead of just the filename
 *
 * 68    4/19/00 5:29p Matt
 * From Duane for 1.4
 * Added Mac-only error handling
 * Added checks & asserts for error return values
 *
 * 67    4/04/00 6:09p Matt
 * Fixed two problems in the hash code:  the hash values were
 * case-sensitive, which caused misses with mixed-case filenames, and hash
 * table nodes were not freed when a bitmap was freed.
 *
 * 66    3/20/00 12:23p Matt
 * Merge of Duane's post-1.3 changes.
 * Small optimization
 * Error check
 *
 * 65    2/06/00 3:41a Jason
 * fixed memory overrun error in bm_ChangeEndName function
 *
 * 64    10/21/99 9:27p Jeff
 * B.A. Macintosh code merge
 *
 * 63    8/10/99 5:10p Jeff
 * delete the hash table on bitmap lib shutdown...just to be clean
 *
 * 62    7/28/99 5:18p Kevin
 * Mac merge fixes
 *
 * 61    7/28/99 3:37p Kevin
 * Mac!
 *
 * 60    4/29/99 4:59p Jason
 * fixed some preuploaded texture problems
 *
 * 59    4/23/99 10:45p Jeff
 * fixed crash with freeing hash table, set it to NULL to prevent double
 * free
 *
 * 58    4/21/99 11:05a Kevin
 * new ps_rand and ps_srand to replace rand & srand
 *
 * 57    4/16/99 11:51p Jeff
 * renamed strcmpi to stricmp to be linux nice
 *
 * 56    4/15/99 2:56p Kevin
 * Removed unneeded mprintf and unused variable
 *
 * 55    4/15/99 12:36p Kevin
 * Changed bm_FindBitmapName to use a hash table.
 *
 * 54    4/14/99 1:07a Jeff
 * fixed case mismatched #includes
 *
 * 53    3/23/99 10:24a Samir
 * NULL pointer in bm_DestroyChunkedBitmap.
 *
 * 52    2/12/99 12:14p Jason
 * fixed memory scaling problem
 *
 * 51    1/19/99 11:17a Jason
 * fixed another scaling problem
 *
 * 50    1/14/99 2:26p Jason
 * made data tracking more reliable
 *
 * 49    1/04/99 6:19p Jason
 * fixed bitmap format problem
 *
 * 48    12/21/98 11:47a Jason
 * fixed bitmap problem with 4444 mipping
 *
 * 47    12/21/98 11:21a Josh
 * FROM JASON: Fixed format/mip problem
 *
 * 46    11/30/98 5:50p Jason
 * added 4444 bitmap support
 *
 * 45    10/21/98 4:36p Jason
 * more changes for renderering speedups
 *
 * 44    10/19/98 4:22p Jason
 * more fixes for Beta5
 *
 * 43    10/08/98 2:27p Jason
 * sped up table file loading
 *
 * 42    9/25/98 12:01p Samir
 * for ndebug builds, removed the return immediately case in
 * bm_AllocLoadFileBitmap.
 *
 * 41    8/21/98 5:14p Jason
 * made better memory use of primitives
 *
 * 40    7/14/98 10:58a Jason
 * fixed transparency bug in error texture
 *
 * 39    5/27/98 5:17p Jason
 * fixed some bugs for the E3 Demo
 *
 * 38    5/20/98 5:43p Jason
 * incremental checkin for bumpmapping
 *
 * 37    5/07/98 3:30p Jeff
 * optimized CreateChunkBitmap a bit
 *
 * 36    5/05/98 1:01p Jeff
 * improved on Chunk bitmaps
 *
 * 35    4/23/98 6:38p Jason
 * made bitmaps use 1555 format
 *
 * 34    4/22/98 12:10p Chris
 * Fixed path length problems
 *
 * 33    4/03/98 12:23p Jason
 * dealt with overlay types being loaded from disk more than once
 *
 * 32    3/31/98 3:48p Jason
 * added memory lib
 *
 * 31    3/23/98 4:42p Jason
 * took out dumb ifdef
 *
 * 30    3/19/98 3:18p Samir
 * enforce constant char* arguments when needed.  done in CFILE and bitmap
 * libraries as well as ddio.
 *
 * 29    3/17/98 4:33p Jason
 * Added size changing to bitmaps/textures
 *
 * 28    2/17/98 4:57p Jason
 * upped bitmap counts
 *
 * 27    2/13/98 7:23p Brent
 * fixed mipping bug
 *
 * 26    2/12/98 1:32p Jason
 * got mipmapping working
 *
 * 25    2/11/98 7:08p Jason
 * took out dumb mprintf
 *
 * 24    2/09/98 3:38p Jason
 * fixed potential problem with overlay bitmaps
 *
 * 23    2/06/98 7:20p Jason
 * made duplicate bitmaps replace themselves in memory
 *
 * 22    1/26/98 4:32p Jason
 * took out some goofy mprintfs
 *
 * 21    1/16/98 3:14p Samir
 * Now store pixel width and height of chunked bitmap.
 *
 * 20    1/16/98 11:46a Samir
 * Added functions to allocate and destroy chunked bitmaps.
 *
 * 19    1/14/98 12:45p Jeff
 * Added a 'clear bitmap' function. Clears to transparent color.
 *
 * 18    12/23/97 6:32p Mark
 * fixed problem with trying to save a bitmap that hasn't been paged in.
 *
 * 17    12/19/97 5:59p Jason
 * sped up bitmap loading
 *
 * 16    12/19/97 3:36p Jason
 * bug fixes for bitmap paging stuff
 *
 * 15    12/19/97 2:46p Jason
 * implemented bitmap paging routines
 *
 * 14    12/18/97 4:03p Jason
 * added error checking for bitmaps initting
 *
 * 13    11/11/97 1:07p Jason
 * fixed multiple names problem in bitmap naming
 *
 * 12    11/10/97 4:53p Jason
 * added warning for names that are too long
 *
 * 11    10/16/97 4:55p Jason
 * fixed stupid off-by-one bug
 *
 * 10    10/16/97 10:48a Jason
 * added bm_set_priority
 *
 * 9     10/15/97 5:20p Jason
 * did a HUGE overhaul of the bitmap system
 *
 * 8     9/17/97 10:48a Jason
 * added cache_slot variable
 *
 * 7     9/16/97 5:04p Matt
 * Changed conditional for debug code
 *
 * 6     9/12/97 6:06p Samir
 * Added function to get bitmap pixel.
 *
 * 5     9/10/97 12:13p Samir
 * Added function to check if a pixel is transparent.
 *
 * 4     9/02/97 11:18a Jason
 * got rid of compiler warnings
 *
 * 3     8/29/97 1:22p Jason
 * added tga screenshots
 *
 * 2     8/05/97 10:18a Jason
 * added lightmap system
 *
 * 46    6/24/97 12:41p Jason
 * checked in for safety
 *
 * 45    6/06/97 3:57p Jason
 * implemented changes for small textures and automatic tmap2 recognition
 *
 * 44    6/03/97 12:19p Jason
 * cleaned up the bitmap library a bit
 *
 * 43    5/19/97 5:10p Jason
 * changes for our new abstracted renderer code
 *
 * 42    5/12/97 11:41a Jason
 * made game work (default) to 16bit no mip maps mode
 * Saves us alot of memory
 *
 * 41    5/08/97 1:16p Jason
 * made ChangeEndName work with device independant calls
 *
 * 40    5/02/97 5:22p Jason
 * added bm_rowsize to return bytes per row
 *
 * 39    5/01/97 4:37p Jason
 * made bitmaps clear their settings when alloced (bug fixed)
 *
 * 38    4/30/97 3:15p Jason
 * changes to support both 8bit and 16bit rendering in software
 *
 * 37    4/25/97 3:31p Jason
 * implemented better memory management for vclips and bitmaps
 *
 * 36    4/8/97 5:23 PM Jeremy
 * #ifdef editor around calls to decrement bitmap_memory_used by checking
 * _msize of an array location.  _msize is microsoft specific, not cross
 * platform, but this is only used by the editor anyway, thus the ifdef
 * editor.
 *
 * 35    3/31/97 7:18p Jason
 * made bitmaps easier on memory if not in editor mode
 *
 * 34    3/28/97 12:22p Jason
 * implemented memory sharing scheme between 8 bit bitmaps
 *
 * 33    3/13/97 1:05p Matt
 * Fixed extra-stupid bug
 *
 * 32    3/13/97 12:35p Matt
 * Look for error1.ogf in current directory (explicitely)
 *
 * 31    3/03/97 6:20p Matt
 * Changed cfile functions to use D3 naming convention
 *
 * $NoKeywords: $
 */
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "cfile.h"
#include "texture.h"
#include "bitmap.h"
#include "pstypes.h"
#include "pserror.h"
#include "mono.h"
#include "iff.h"
#include "ddio.h"
#include "lightmap.h"
#include "bumpmap.h"
#include "mem.h"
#include "psrand.h"

#include "Macros.h"

#include <algorithm>

#define BM_FILETYPE_TGA 1
#define BM_FILETYPE_PCX 2
#define BM_FILETYPE_IFF 3
int Num_of_bitmaps = 0;
bms_bitmap GameBitmaps[MAX_BITMAPS];
uint32_t Bitmap_memory_used = 0;
uint8_t Bitmaps_initted = 0;
/* modify these lines to establish data type */
typedef bms_bitmap *bm_T;      /* type of item to be stored */
typedef int bm_hashTableIndex; /* index into hash table */
#define compEQ(a, b) (stricmp((a)->name, (b)->name) == 0)
struct bm_Node {
  struct bm_Node *next; /* next bm_Node */
  bm_T data;             /* data stored in bm_Node */
};
static bm_Node *bm_findNode(bm_T data);
static void bm_deleteNode(bm_T data);
static bm_Node *bm_insertNode(bm_T data);
static bm_hashTableIndex bm_hash(bm_T data);
static bm_Node **bm_hashTable = NULL;
static const int bm_hashTableSize = (MAX_BITMAPS / 2);
static void bm_InitHashTable();
static void bm_DeleteHashTable();
static int bm_TestName(const char *src);

void bm_InitHashTable() {
  bm_hashTable = (bm_Node **)mem_malloc(bm_hashTableSize * sizeof(bm_Node *));
  for (int a = 0; a < bm_hashTableSize; a++) {
    bm_hashTable[a] = NULL;
  }
}
void bm_DeleteHashTable() {
  if (bm_hashTable) {
    int idx;
    for (idx = 0; idx < bm_hashTableSize; idx++) {
      if (bm_hashTable[idx]) {
        bm_Node *curr, *next;
        curr = bm_hashTable[idx];
        while (curr) {
          next = curr->next;
          mem_free(curr);
          curr = next;
        }
        bm_hashTable[idx] = NULL;
      }
    }

    mem_free(bm_hashTable);
    bm_hashTable = NULL;
  }
}

bm_hashTableIndex bm_hash(bm_T data) {
  /***********************************
   *  hash function applied to data  *
   ***********************************/
  char *p = data->name;
  uint32_t hval = strlen(p);

  while (*p) {
    hval += tolower(*p);
    p++;
  }

  return (hval % (MAX_BITMAPS / 2));
}
bm_Node *bm_insertNode(bm_T data) {
  bm_Node *p, *p0;
  bm_hashTableIndex bucket;
  /************************************************
   *  allocate bm_Node for data and insert in table  *
   ************************************************/
  /* insert bm_Node at beginning of list */
  bucket = bm_hash(data);
  if ((p = (bm_Node *)mem_malloc(sizeof(bm_Node))) == 0) {
    exit(1);
  }
  p0 = bm_hashTable[bucket];
  bm_hashTable[bucket] = p;
  p->next = p0;
  p->data = data;
  return p;
}
void bm_deleteNode(bm_T data) {
  bm_Node *p0, *p;
  bm_hashTableIndex bucket;
  /********************************************
   *  delete bm_Node containing data from table  *
   ********************************************/
  /* find bm_Node */
  p0 = 0;
  bucket = bm_hash(data);
  p = bm_hashTable[bucket];
  while (p && !compEQ(p->data, data)) {
    p0 = p;
    p = p->next;
  }
  if (!p)
    return;
  /* p designates bm_Node to delete, remove it from list */
  if (p0)
    /* not first bm_Node, p0 points to previous bm_Node */
    p0->next = p->next;
  else
    /* first bm_Node on chain */
    bm_hashTable[bucket] = p->next;
  mem_free(p);
}
bm_Node *bm_findNode(bm_T data) {
  bm_Node *p;
  if (!bm_hashTable)
    return NULL;
  /*******************************
   *  find bm_Node containing data  *
   *******************************/
  p = bm_hashTable[bm_hash(data)];
  while (p && !compEQ(p->data, data))
    p = p->next;
  return p;
}
//	simply frees up a bitmap
void bm_FreeBitmapMain(int handle);
// Sets all the bitmaps to unused
void bm_InitBitmaps() {
  int i, ret;
  bm_InitHashTable();
  Bitmaps_initted = 1;
  for (i = 0; i < MAX_BITMAPS; i++) {
    GameBitmaps[i].used = 0;
    GameBitmaps[i].data16 = NULL;
    GameBitmaps[i].format = BITMAP_FORMAT_STANDARD;
    GameBitmaps[i].cache_slot = -1;
    GameBitmaps[i].flags = 0;
  }
  int bm = bm_AllocBitmap(128, 128, 0);
  ASSERT(bm == BAD_BITMAP_HANDLE);
  if (cfexist(".\\error1.ogf"))
    ret = bm_AllocLoadFileBitmap(".\\error1.ogf", 0);
  else
    ret = -1;
  if (ret == -1)
    bm_MakeBad(bm);
  else {
    bm_ScaleBitmapToBitmap(bm, ret);
    bm_FreeBitmap(ret);
  }

  // bm_GenerateMipMaps (bm);
  atexit(bm_ShutdownBitmaps);
  // Initialize lightmaps and bumpmaps
  lm_InitLightmaps();
  bump_InitBumpmaps();
}
void bm_ShutdownBitmaps(void) {
  int i;
  mprintf(0, "Freeing all bitmap memory.\n");
  bm_FreeBitmapMain(0);
  for (i = 0; i < MAX_BITMAPS; i++) {
    while (GameBitmaps[i].used > 0)
      bm_FreeBitmap(i);
  }
  bm_DeleteHashTable();
}
int bm_AllocateMemoryForIndex(int n, int w, int h, int add_mem) {
  // If no go on the malloc, bail out with -1

  int size = (w * h * 2) + (add_mem) + 2;
  GameBitmaps[n].data16 = (uint16_t *)mem_malloc(size);
  if (!GameBitmaps[n].data16) {
    Int3(); // Ran out of memory!
    return -1;
  }
  Bitmap_memory_used += (size);
  memset(GameBitmaps[n].data16, 0xAA, size);

  GameBitmaps[n].format = BITMAP_FORMAT_STANDARD;
  GameBitmaps[n].width = w;
  GameBitmaps[n].height = h;
  GameBitmaps[n].flags = BF_CHANGED | BF_BRAND_NEW;

#ifdef USE_OPENGL
  for (int tmp = w; tmp > 0; tmp = tmp >> 1)
    GameBitmaps[n].mip_levels++;
#else
  GameBitmaps[n].mip_levels = NUM_MIP_LEVELS;
#endif

  Num_of_bitmaps++;
  return n;
}
// Allocs a bitmap of w x h size
// If add_mem is nonzero, adds that to the amount alloced
// Returns bitmap handle if successful, -1 if otherwise
int bm_AllocBitmap(int w, int h, int add_mem) {
  int n, i;
  if (!Bitmaps_initted) {
    Int3();
    mprintf(0, "Bitmaps not initted!!!\n");
    return -1;
  }

  for (i = 0; i < MAX_BITMAPS; i++) {
    if (GameBitmaps[i].used == 0) {
      n = i;
      break;
    }
  }
  // If we can't find a free slot in which to alloc, bail out
  if (i == MAX_BITMAPS) {
    Int3();
    mprintf(0, "ERROR! Couldn't find a free bitmap to alloc!\n");
    return -1;
  }
  memset(&GameBitmaps[n], 0, sizeof(bms_bitmap));
  int ret = bm_AllocateMemoryForIndex(n, w, h, add_mem);
  if (ret >= 0) {
    GameBitmaps[n].used = 1;
    GameBitmaps[n].cache_slot = -1;
  }
  return ret;
}
// Just like bm_AllocBitmap but doesn't actually allocate memory.  Useful for paging!
int bm_AllocNoMemBitmap(int w, int h) {
  int n, i;
  if (!Bitmaps_initted) {
    Int3();
    mprintf(0, "Bitmaps not initted!!!\n");
    return -1;
  }

  for (i = 0; i < MAX_BITMAPS; i++) {
    if (GameBitmaps[i].used == 0) {
      n = i;
      break;
    }
  }
  // If we can't find a free slot in which to alloc, bail out
  if (i == MAX_BITMAPS) {
    Int3();
    mprintf(0, "ERROR! Couldn't find a free bitmap to alloc!\n");
    return -1;
  }
  // If no go on the malloc, bail out with -1

  memset(&GameBitmaps[n], 0, sizeof(bms_bitmap));

  GameBitmaps[n].width = w;
  GameBitmaps[n].height = h;
  GameBitmaps[n].used = 1;
  GameBitmaps[n].format = BITMAP_FORMAT_STANDARD;
  GameBitmaps[n].flags = BF_NOT_RESIDENT | BF_CHANGED | BF_BRAND_NEW;
  GameBitmaps[n].cache_slot = -1;

  Num_of_bitmaps++;
  return n;
}
// Searches thru all bitmaps for a specific name, returns -1 if not found
// or index of bitmap with name
int bm_FindBitmapName(const char *name) {
  int num_counted = 0;

  bms_bitmap fbmp;
  strcpy(fbmp.name, name);
  bm_Node *fnode = bm_findNode(&fbmp);
  if (fnode) {
    // mprintf(0,"Hash table found bitmap %d\n",fnode->data - GameBitmaps);
    return fnode->data - GameBitmaps;
  } else
    return -1;
}
// Given a handle, frees the bitmap memory and flags this bitmap as unused
void bm_FreeBitmap(int handle) {
  if (!Bitmaps_initted) {
    Int3();
    mprintf(0, "Bitmaps not initted!!!\n");
    return;
  }
  if (handle == BAD_BITMAP_HANDLE)
    return;
  if (GameBitmaps[handle].used < 1)
    return;
  GameBitmaps[handle].used--;
  if (GameBitmaps[handle].used == 0) {
    bm_FreeBitmapMain(handle);
  }
}
//	simply frees up a bitmap
void bm_FreeBitmapData(int handle) {
  if (GameBitmaps[handle].data16 != NULL && !(GameBitmaps[handle].flags & BF_NOT_RESIDENT)) {
    if (!(GameBitmaps[handle].flags & BF_NOT_RESIDENT)) {
      int mem_used = (GameBitmaps[handle].width * GameBitmaps[handle].height * 2);
      Bitmap_memory_used -= mem_used;
      if (GameBitmaps[handle].flags & BF_MIPMAPPED)
        Bitmap_memory_used -= (mem_used / 3);
    }
    mem_free(GameBitmaps[handle].data16);
  }
  GameBitmaps[handle].cache_slot = -1;
  GameBitmaps[handle].flags |= BF_NOT_RESIDENT;
  if (GameBitmaps[handle].flags & BF_MIPMAPPED)
    GameBitmaps[handle].flags |= BF_WANTS_MIP;
  GameBitmaps[handle].data16 = NULL;
}
//	simply frees up a bitmap
void bm_FreeBitmapMain(int handle) {
  bm_deleteNode(&GameBitmaps[handle]);
  bm_FreeBitmapData(handle);
  GameBitmaps[handle].data16 = NULL;
  GameBitmaps[handle].cache_slot = -1;
  GameBitmaps[handle].used = 0;
  Num_of_bitmaps--;
}
// Returns -1 if this name is not already in use, else index of bitmap that is using name
int bm_TestName(const char *src) {
  uint32_t i, limit;

  char namedest[256];
  char path[256], ext[256], filename[256];

  ddio_SplitPath(src, path, filename, ext);
  limit = BITMAP_NAME_LEN - 7;
  // Make sure we don't go over our name length limit
  strncpy(namedest, filename, limit);
  namedest[limit] = 0;

  int cur_len = strlen(namedest);

  // Now, make sure there are no other bitmaps with this name
  strcat(namedest, ".ogf");
  if ((i = bm_FindBitmapName(namedest)) == -1)
    return -1;
  return i;
}
// gets the filename from a path, plus appends our .ogf extension
void bm_ChangeEndName(const char *src, char *dest) {
  uint32_t i, limit;
  int last = -1;
  int curnum = -1;
  char namedest[256+16];
  char path[256], ext[256], filename[256];

  ddio_SplitPath(src, path, filename, ext);
  limit = BITMAP_NAME_LEN - 7;
  // Make sure we don't go over our name length limit
  filename[limit] = 0;
Start:
  if (curnum != -1)
    snprintf(namedest, sizeof(namedest), "%s%d", filename, curnum);
  else
    strcpy(namedest, filename);
  // Now, make sure there are no other bitmaps with this name
  strcat(namedest, ".ogf");
  if ((i = bm_FindBitmapName(namedest)) != -1) {
    curnum++;
    // This name is already taken.  Try same name with different number
    // appended
    goto Start;
  }
  strcpy(dest, namedest);
}
// Checks to see if this file is a kind we can read
int bm_GetFileType(CFILE *infile, const char *dest) {
  char iffcheck[4];
  int i;
  // First, check if its a pcx
  i = strlen(dest);
  if (dest[i - 4] == '.' && (dest[i - 3] == 'p' || dest[i - 3] == 'P') && (dest[i - 2] == 'c' || dest[i - 2] == 'C') &&
      (dest[i - 1] == 'x' || dest[i - 1] == 'X'))
    return BM_FILETYPE_PCX;
  // How about an IFF?
  for (i = 0; i < 4; i++)
    iffcheck[i] = cf_ReadByte(infile);
  cfseek(infile, 0, SEEK_SET);
  if (!strncmp("FORM", iffcheck, 4))
    return BM_FILETYPE_IFF;
  // Lastly, just default to possible TGA or OGF
  return BM_FILETYPE_TGA;
}
// Allocs and loads a bitmap
// Returns the handle of the loaded bitmap
// Returns -1 if something is wrong
// If mipped is non-zero, allocs extra space for mips and computes them
int bm_AllocLoadFileBitmap(const char *fname, int mipped, int format) {
  CFILE *infile;
  if (!Bitmaps_initted) {
    Int3();
    mprintf(0, "Bitmaps not initted!!!\n");
    return -1;
  }

  char name[BITMAP_NAME_LEN];
  int n, src_bm = 0;
  int old_used;
  int overlay = 0;

  char *filename = (char *)fname;

  // due to a bug in some people's tablefile editors, we got to make sure there is
  // no path if there shouldn't be
  if (!cfexist(filename)) {
    // generate a possible new filename
    char *end_ptr, *start_ptr;
    start_ptr = (char *)fname;
    end_ptr = start_ptr + strlen(start_ptr) - 1;
    while ((end_ptr >= start_ptr) && (*end_ptr != '\\'))
      end_ptr--;
    if (end_ptr < start_ptr) {
      mprintf(0, "Unable to find bitmap %s\n", fname);
      return -1;
    }
    ASSERT(*end_ptr == '\\');
    end_ptr++;
    filename = end_ptr;
    mprintf(0, "Couldn't find %s, so gonna try %s\n", fname, filename);
  }

  // Check to see if this bitmap is already in memory, if so, just return that
  // bitmaps handle
  if ((n = bm_TestName(filename)) != -1) {
    mprintf(1, "Found duplicate bitmap %s.\n", GameBitmaps[n].name);
    old_used = GameBitmaps[n].used;
    GameBitmaps[n].used = 1;
    bm_FreeBitmap(n);
    GameBitmaps[n].used = old_used + 1;

    overlay = 1;
  }
  if (!overlay)
    bm_ChangeEndName(filename, name);
  else {
    strcpy(name, GameBitmaps[n].name);
  }
  if (strlen(name) > 33) {
    mprintf(0, "ERROR!! This bitmaps name is too long, try shortening it and retry!\n");
    return -1;
  }
  // Try to open the file.  If we can't load it from the network if possible
  infile = (CFILE *)cfopen(filename, "rb");
  if (!infile) {
    mprintf(0, "bm_AllocLoadFileBitmap: Can't open file named %s.\n", filename);

    return BAD_BITMAP_HANDLE; // return the bad texture
  }
  // Check to see if this is IFF.  If so, call the IFF reader.  If not,
  // rewind the file and read as a TGA

  int filetype = bm_GetFileType(infile, filename);

  switch (filetype) {
  case BM_FILETYPE_IFF:
    src_bm = bm_iff_alloc_file(infile);
    break;
  case BM_FILETYPE_TGA:
    // reads a tga or an outrage graphics file (ogf)
    src_bm = bm_tga_alloc_file(infile, name, format);
    break;
  case BM_FILETYPE_PCX:
    src_bm = bm_pcx_alloc_file(infile);
    break;
  default:
    Int3(); // Can't read this type
    break;
  }
  cfclose(infile);
  if (src_bm < 0) {
    mprintf(0, "Couldn't load %s.", filename);
    return -1;
  }

  // Allocate space for our bitmap.
  if (mipped) {
    if ((bm_mipped(src_bm)) == 0) // If we want a mipped but we don't have one
    {
      int w = bm_w(src_bm, 0);
      int h = bm_h(src_bm, 0);

      if (overlay) {
        bm_AllocateMemoryForIndex(n, w, h, mipped * (((w * h * 2) / 3)));
        GameBitmaps[n].format = GameBitmaps[src_bm].format;
      } else {
        n = bm_AllocBitmap(w, h, mipped * (((w * h * 2) / 3)));
        GameBitmaps[n].format = GameBitmaps[src_bm].format;
      }

      ASSERT(n >= 0);
      bm_ScaleBitmapToBitmap(n, src_bm);
      bm_FreeBitmap(src_bm);

      bm_GenerateMipMaps(n);
    } else {
      if (!overlay)
        n = src_bm;
      else {
        int w = bm_w(src_bm, 0);
        int h = bm_h(src_bm, 0);
        bm_AllocateMemoryForIndex(n, w, h, mipped * (((w * h * 2) / 3)));
        GameBitmaps[n].flags |= BF_MIPMAPPED;
        GameBitmaps[n].format = GameBitmaps[src_bm].format;
        bm_ScaleBitmapToBitmap(n, src_bm);
        bm_FreeBitmap(src_bm);
      }
    }
  } else // If we don't want a mipped
  {
    if ((bm_mipped(src_bm)) == 0) {
      if (!overlay)
        n = src_bm;
      else {
        int w = bm_w(src_bm, 0);
        int h = bm_h(src_bm, 0);
        bm_AllocateMemoryForIndex(n, w, h, mipped * (((w * h * 2) / 3)));
        GameBitmaps[n].format = GameBitmaps[src_bm].format;
        bm_ScaleBitmapToBitmap(n, src_bm);
        bm_FreeBitmap(src_bm);
      }
    } else // And this is already mipped
    {
      int w = bm_w(src_bm, 0);
      int h = bm_h(src_bm, 0);
      uint16_t *src_data, *dest_data;

      if (overlay) {
        bm_AllocateMemoryForIndex(n, w, h, mipped * (((w * h * 2) / 3)));
        GameBitmaps[n].format = GameBitmaps[src_bm].format;
      } else {
        n = bm_AllocBitmap(w, h, mipped * (((w * h * 2) / 3)));
        GameBitmaps[n].format = GameBitmaps[src_bm].format;
      }
      ASSERT(n >= 0);
      src_data = (uint16_t *)bm_data(src_bm, 0);
      dest_data = (uint16_t *)bm_data(n, 0);
      memcpy(dest_data, src_data, w * h * 2);

      bm_FreeBitmap(src_bm);
    }
  }

  strcpy(GameBitmaps[n].name, name);

  // Insert into the hash table!
  bm_insertNode(&GameBitmaps[n]);
  return n; // We made it!
}
// Allocs and loads a bitmap but doesn't actually load texel data!
// Returns the handle of the loaded bitmap
// Returns -1 if something is wrong
int bm_AllocLoadFileNoMemBitmap(const char *fname, int mipped, int format) {
  if (!Bitmaps_initted) {
    Int3();
    mprintf(0, "Bitmaps not initted!!!\n");
    return -1;
  }

  char name[BITMAP_NAME_LEN];
  int n;
  char *filename = (char *)fname;

  // due to a bug in some people's tablefile editors, we got to make sure there is
  // no path if there shouldn't be
  if (!cfexist(filename)) {
    // generate a possible new filename
    char *end_ptr, *start_ptr;
    start_ptr = (char *)fname;
    end_ptr = start_ptr + strlen(start_ptr) - 1;
    while ((end_ptr >= start_ptr) && (*end_ptr != '\\'))
      end_ptr--;
    if (end_ptr < start_ptr) {
      mprintf(0, "Unable to find bitmap %s\n", fname);
      return -1;
    }
    ASSERT(*end_ptr == '\\');
    end_ptr++;
    filename = end_ptr;
    mprintf(0, "Couldn't find %s, so gonna try %s\n", fname, filename);
  }

  // Check to see if this bitmap is already in memory, if so, just return that
  // bitmaps handle
  if ((n = bm_TestName(filename)) != -1) {
    GameBitmaps[n].used++;
    mprintf(1, "Found duplicate bitmap %s.\n", GameBitmaps[n].name);
    return n;
  }

  bm_ChangeEndName(filename, name);
  if (strlen(name) > 33) {
    mprintf(0, "ERROR!! This bitmaps name is too long, try shortening it and retry!\n");
    return -1;
  }
  n = bm_AllocNoMemBitmap(1, 1);
  strcpy(GameBitmaps[n].name, name);
  if (mipped)
    GameBitmaps[n].flags |= BF_WANTS_MIP;
  if (format == BITMAP_FORMAT_4444)
    GameBitmaps[n].flags |= BF_WANTS_4444;

  return n; // We made it!
}
// Allocs and loads a bitmap from an open file
// Returns the handle of the loaded bitmap
// Returns -1 if something is wrong
// If mipped is non-zero, allocs extra space for mips and computes them
int bm_AllocLoadBitmap(CFILE *infile, int mipped, int format) {
  char name[BITMAP_NAME_LEN];
  int n, src_bm;
  if (!Bitmaps_initted) {
    Int3();
    mprintf(0, "Bitmaps not initted!!!\n");
    return -1;
  }

  // Assume this is an ogf

  src_bm = bm_tga_alloc_file(infile, name, format);
  if (src_bm < 0) {
    mprintf(0, "Couldn't load %s.", name);
    return -1;
  }

  // Allocate space for our bitmap
  if (mipped) {
    if ((bm_mipped(src_bm)) == 0) // If we want a mipped but we don't have one
    {
      int w = bm_w(src_bm, 0);
      int h = bm_h(src_bm, 0);

      n = bm_AllocBitmap(w, h, mipped * (((w * h * 2) / 3)));

      ASSERT(n >= 0);
      GameBitmaps[n].format = GameBitmaps[src_bm].format;
      bm_ScaleBitmapToBitmap(n, src_bm);
      bm_FreeBitmap(src_bm);

      bm_GenerateMipMaps(n);
    } else
      n = src_bm;
  } else // If we don't want a mipped
  {
    if ((bm_mipped(src_bm)) == 0)
      n = src_bm;
    else // And this is already mipped
    {
      int w = bm_w(src_bm, 0);
      int h = bm_h(src_bm, 0);
      uint16_t *src_data, *dest_data;

      n = bm_AllocBitmap(w, h, mipped * (((w * h * 2) / 3)));
      ASSERT(n >= 0);
      src_data = (uint16_t *)bm_data(src_bm, 0);
      dest_data = (uint16_t *)bm_data(n, 0);
      memcpy(dest_data, src_data, w * h * 2);

      bm_FreeBitmap(src_bm);
    }
  }
  strcpy(GameBitmaps[n].name, name);
  return n; // We made it!
}
// Given a handle, makes a big random shape to let you know you are screwed.
void bm_MakeBad(int handle) {
  int i, t, limit;
  uint16_t *dest;
  ASSERT(GameBitmaps[handle].used);
  if (handle != BAD_BITMAP_HANDLE)
    Int3(); // hmm, you're assigning a random bitmap to something other than
            // the default.
  if (bm_mipped(handle))
    limit = bm_miplevels(handle);
  else
    limit = 1;
  for (i = 0; i < limit; i++) {
    dest = bm_data(handle, i);

    for (t = 0; t < bm_h(handle, i) * bm_w(handle, i); t++)
      *dest++ = (OPAQUE_FLAG | ps_rand());
  }
}

// Saves a bitmap to an open file.  Saves the bitmap as an OUTRAGE_COMPRESSED_OGF.
// Returns -1 if something is wrong.
int bm_SaveBitmap(CFILE *fp, int handle) {
  uint8_t dumbbyte = 0, image_type = OUTRAGE_1555_COMPRESSED_MIPPED, pixsize = 32, desc = 8 + 32;
  int i, done = 0;
  int num_mips;
  mprintf(0, "Saving bitmap %s...\n", GameBitmaps[handle].name);
  if (!GameBitmaps[handle].used) {
    mprintf(0, "bm_SaveBitmap: Trying to save a bitmap that isn't used!\n");
    Int3();
    return -1;
  }
  if (handle == BAD_BITMAP_HANDLE) {
    Int3(); // Hey, you shouldn't be saving this bitmap!
    return -1;
  }
  if (GameBitmaps[handle].format == BITMAP_FORMAT_4444)
    image_type = OUTRAGE_4444_COMPRESSED_MIPPED;
  if (!fp) {
    mprintf(0, "bm_SaveBitmap: Trying to save a bitmap to a closed file!\n");
    Int3();
    return -1;
  }
  cf_WriteByte(fp, dumbbyte);
  cf_WriteByte(fp, dumbbyte);
  cf_WriteByte(fp, image_type);
  cf_WriteString(fp, GameBitmaps[handle].name);

  if ((bm_mipped(handle)))
    num_mips = bm_miplevels(handle);
  else
    num_mips = 1;
  cf_WriteByte(fp, num_mips);
  for (i = 0; i < 9; i++)
    cf_WriteByte(fp, 0);
  cf_WriteShort(fp, GameBitmaps[handle].width);
  cf_WriteShort(fp, GameBitmaps[handle].height);
  cf_WriteByte(fp, pixsize);
  cf_WriteByte(fp, desc);

  // write compressed info
  for (int m = 0; m < num_mips; m++) {
    int curptr = 0;
    int total = bm_w(handle, m) * bm_h(handle, m);
    uint16_t *src_data = (uint16_t *)bm_data(handle, m);
    done = 0;
    while (!done) {
      if (curptr == total) {
        done = 1;
        continue;
      }
      ASSERT(curptr < total);
      uint16_t curpix = src_data[curptr];
      uint8_t count = 1;
      while (src_data[curptr + count] == curpix && count < 250 && (curptr + count) < total)
        count++;
      if (count == 1) {
        cf_WriteByte(fp, 0);
        cf_WriteShort(fp, curpix);
      } else {
        cf_WriteByte(fp, count);
        cf_WriteShort(fp, curpix);
      }
      curptr += count;
    }
  }

  return 1;
}
// Makes sure a bitmap is in memory...if not it attempts to page it in
int bm_MakeBitmapResident(int handle) {
  if (GameBitmaps[handle].flags & BF_NOT_RESIDENT) {
    if (bm_page_in_file(handle) > 0) // DAJ -1FIX
    {
      GameBitmaps[handle].flags &= ~BF_NOT_RESIDENT;
      GameBitmaps[handle].flags |= BF_CHANGED | BF_BRAND_NEW;
    } else {
      mprintf(0, "Error paging in bitmap %s!\n", GameBitmaps[handle].name);
      return 0;
    }
  }
  return 1;
}
// Saves a bitmap to a file.  Saves the bitmap as an OUTRAGE_COMPRESSED_OGF.
// Returns -1 if something is wrong.
int bm_SaveFileBitmap(const char *filename, int handle) {
  int ret;
  CFILE *fp;
  if (!GameBitmaps[handle].used) {
    mprintf(0, "bm_SaveBitmap: Trying to save a bitmap that isn't used!\n");
    Int3();
    return -1;
  }
  if (handle == BAD_BITMAP_HANDLE) {
    Int3(); // Hey, you shouldn't be saving this bitmap!
    return -1;
  }
  if (!bm_MakeBitmapResident(handle)) {
    mprintf(0, "There was a problem paging this bitmap in!\n");
    return -1;
  }
  fp = (CFILE *)cfopen(filename, "wb");

  if (!fp) {
    mprintf(0, "bm_SaveBitmap: Trying to save a bitmap to a closed file!\n");
    Int3();
    return -1;
  }
  ret = bm_SaveBitmap(fp, handle);

  cfclose(fp);
  return ret;
}
// returns a bitmaps width (based on miplevel), else -1 if something is wrong
int bm_w(int handle, int miplevel) {
  int w;
  if (!GameBitmaps[handle].used) {
    Int3();
    return -1;
  }
  if (GameBitmaps[handle].flags & BF_NOT_RESIDENT)
    if (!bm_MakeBitmapResident(handle))
      return 0;
  if (!(GameBitmaps[handle].flags & BF_MIPMAPPED))
    miplevel = 0;
  w = GameBitmaps[handle].width;
  w >>= miplevel;
  return (w);
}
// returns a bitmaps height (based on miplevel), else -1 if something is wrong
int bm_h(int handle, int miplevel) {
  int h;
  if (!GameBitmaps[handle].used) {
    Int3();
    return -1;
  }
  // If this bitmap is not page in, do so!
  if (GameBitmaps[handle].flags & BF_NOT_RESIDENT)
    if (!bm_MakeBitmapResident(handle))
      return 0;
  if (!(GameBitmaps[handle].flags & BF_MIPMAPPED))
    miplevel = 0;
  h = GameBitmaps[handle].height;
  h >>= miplevel;
  return (h);
}

// returns the number of levels of mips a bitmap should have
int bm_miplevels(int handle) {
  int levels = 0;
  if (!GameBitmaps[handle].used) {
    Int3();
    return -1;
  }
  if (GameBitmaps[handle].mip_levels)
    return GameBitmaps[handle].mip_levels;

  // If this bitmap is not page in, do so!
  if (GameBitmaps[handle].flags & BF_NOT_RESIDENT)
    if (!bm_MakeBitmapResident(handle))
      return 0;
  if (GameBitmaps[handle].flags & BF_MIPMAPPED) {
    for (int tmp = GameBitmaps[handle].width; tmp > 0; tmp = tmp >> 1) {
      levels++;
    }
    return levels;
  }
  return 0;
}

// returns a bitmaps mipped status, else -1 if something is wrong
int bm_mipped(int handle) {
  if (!GameBitmaps[handle].used) {
    Int3();
    return -1;
  }
  // If this bitmap is not page in, do so!
  if (GameBitmaps[handle].flags & BF_NOT_RESIDENT)
    if (!bm_MakeBitmapResident(handle))
      return 0;
  if (GameBitmaps[handle].flags & BF_MIPMAPPED)
    return 1;
  return 0;
}
// returns a bitmaps data (based on given miplevel), else NULL if something is wrong
uint16_t *bm_data(int handle, int miplevel) {
  uint16_t *d;
  int i;
  if (!GameBitmaps[handle].used) {
    Int3();
    return NULL;
  }

  // If this bitmap is not page in, do so!
  if (GameBitmaps[handle].flags & BF_NOT_RESIDENT)
    if (!bm_MakeBitmapResident(handle))
      return NULL;

  d = GameBitmaps[handle].data16;
  for (i = 0; i < miplevel; i++) {
    d += (GameBitmaps[handle].width >> i) * (GameBitmaps[handle].height >> i);
  }
  return (d);
}
// Given a source bitmap, generates mipmaps for it
void bm_GenerateMipMaps(int handle) {
  int width = bm_w(handle, 0);
  int height = bm_h(handle, 0);
  int jump = 2; // how many pixels to jump in x and y on source

  // mprintf(0,"We got a mipper! %d \n",handle);

  ASSERT(GameBitmaps[handle].used);
  GameBitmaps[handle].flags |= BF_MIPMAPPED;

  int levels = bm_miplevels(handle);

  uint16_t *destdata;
  for (int miplevel = 1; miplevel < levels; miplevel++) {
    width /= 2;
    height /= 2;

    for (int i = 0; i < height; i++) {
      int adjheight = (i * jump) * bm_w(handle, miplevel - 1); // find our y offset

      for (int t = 0; t < width; t++) {
        int adjwidth = (t * jump); // find our x offset
        uint16_t *srcptr = bm_data(handle, miplevel - 1);
        srcptr += (adjheight + adjwidth);

        int rsum, gsum, bsum, asum;
        rsum = gsum = bsum = asum = 0;
        uint16_t destpix = 0;
        if (GameBitmaps[handle].format == BITMAP_FORMAT_1555) {
          for (int y = 0; y < 2; y++)
            for (int x = 0; x < 2; x++) {
              uint16_t pix = srcptr[y * bm_w(handle, miplevel - 1) + x];
              int r = (pix >> 10) & 0x1f;
              int g = (pix >> 5) & 0x1f;
              int b = (pix & 0x1f);

              if (!(pix & OPAQUE_FLAG))
                asum++;
              else {
                rsum += r;
                gsum += g;
                bsum += b;
              }
            }
          // Average our source pixels
          rsum /= 4;
          gsum /= 4;
          bsum /= 4;
          destpix = OPAQUE_FLAG | (rsum << 10) | (gsum << 5) | bsum;

          if (asum > 2)
            destpix = NEW_TRANSPARENT_COLOR;
        } else if (GameBitmaps[handle].format == BITMAP_FORMAT_4444) {
          for (int y = 0; y < 2; y++)
            for (int x = 0; x < 2; x++) {
              uint16_t pix = srcptr[y * bm_w(handle, miplevel - 1) + x];
              int a = (pix >> 12) & 0x0f;
              int r = (pix >> 8) & 0x0f;
              int g = (pix >> 4) & 0x0f;
              int b = (pix & 0x0f);

              asum += a;
              rsum += r;
              gsum += g;
              bsum += b;
            }
          // Average our source pixels
          rsum /= 4;
          gsum /= 4;
          bsum /= 4;
          asum /= 4;
          destpix = (asum << 12) | (rsum << 8) | (gsum << 4) | bsum;
        } else {
          Int3();
        }
        destdata = bm_data(handle, miplevel);
        int sw = bm_w(handle, miplevel);
        destdata[(i * sw) + t] = destpix;
      }
    }
  }
}
// Gets bits per pixel for a particular bitmap
// As of 12/30/96 always returns 16
int bm_bpp(int handle) { return BPP_16; }
// Given two bitmaps, scales the data from src to the size of dest
// Not a particularly fast implementation
void bm_ScaleBitmapToBitmap(int dest, int src) {
  uint16_t *dp = bm_data(dest, 0);
  uint16_t *sp = bm_data(src, 0);
  ASSERT(GameBitmaps[dest].used && dp);
  ASSERT(GameBitmaps[src].used && sp);
  int smipped = bm_mipped(src);
  int dmipped = bm_mipped(dest);
  int limit;
  ASSERT(smipped == dmipped);
  ASSERT(GameBitmaps[dest].format == GameBitmaps[src].format);

  int sw = bm_w(src, 0);
  int sh = bm_h(src, 0);
  int dw = bm_w(dest, 0);
  int dh = bm_h(dest, 0);
  int i, t;
  uint16_t *sdata;
  uint16_t *ddata;
  if (sw == dw && sh == dh) {
    if (smipped)
      limit = bm_miplevels(src);
    else
      limit = 1;
    for (i = 0; i < limit; i++) {
      sdata = (uint16_t *)bm_data(src, i);
      ddata = (uint16_t *)bm_data(dest, i);
      dw = bm_w(dest, i);
      dh = bm_h(dest, i);
      memcpy(ddata, sdata, dw * dh * sizeof(uint16_t));
    }
    return;
  }
  if (smipped)
    limit = bm_miplevels(src);
  else
    limit = 1;
  for (int m = 0; m < limit; m++) {
    sw = bm_w(src, m);
    sh = bm_h(src, m);
    dw = bm_w(dest, m);
    dh = bm_h(dest, m);

    sdata = (uint16_t *)bm_data(src, m);
    ddata = (uint16_t *)bm_data(dest, m);
    // These are our interpolant variables
    float xstep = (float)sw / (float)dw;
    float ystep = (float)sh / (float)dh;
    float xoff = 0;
    float yoff = 0;
    for (i = 0; i < dh; i++, yoff += ystep) {
      for (xoff = 0, t = 0; t < dw; t++, xoff += xstep) {
        ddata[i * dw + t] = sdata[(int)yoff * sw + (int)xoff];
      }
    }
  }
  GameBitmaps[dest].flags |= BF_CHANGED;
}
// given a handle and a miplevel, returns the bytes per bitmap row
int bm_rowsize(int handle, int miplevel) {
  int w;
  ASSERT(GameBitmaps[handle].used > 0);
  w = bm_w(handle, miplevel);
  w *= 2;
  return w;
}
//	a function to determine if a pixel in a bitmap is transparent
bool bm_pixel_transparent(int bm_handle, int x, int y) {
  if ((bm_data(bm_handle, 0)) == NULL)
    return 0; // only check 16bit stuff
  uint16_t *data = bm_data(bm_handle, 0);
  data = data + (bm_w(bm_handle, 0) * y) + x;
  if (GameBitmaps[bm_handle].format == BITMAP_FORMAT_4444) {
    int pix = *data;
    if (!(pix >> 12))
      return true;
  } else {
    if (!(*data & OPAQUE_FLAG))
      return true;
  }
  return false;
}
//	a function to determine if a pixel in a bitmap is transparent
uint16_t bm_pixel(int bm_handle, int x, int y) {
  if ((bm_data(bm_handle, 0)) == NULL)
    return 0; // only check 16bit stuff
  uint16_t *data = bm_data(bm_handle, 0);
  data = data + (bm_w(bm_handle, 0) * y) + x;
  return *data;
}
// Goes through the bitmap and sees if there is any transparency...if so, flag it!
int bm_SetBitmapIfTransparent(int handle) {
  if ((bm_data(handle, 0)) == NULL)
    return 0; // only check 16bit stuff
  int w = bm_w(handle, 0);
  int h = bm_h(handle, 0);
  uint16_t *data = bm_data(handle, 0);
  if (GameBitmaps[handle].format == BITMAP_FORMAT_4444) {
    for (int i = 0; i < w * h; i++) {
      int pix = data[i] >> 12;
      if (!pix) {
        GameBitmaps[handle].flags |= BF_TRANSPARENT;
        return 1;
      }
    }
  } else {
    for (int i = 0; i < w * h; i++) {
      if (!(data[i] & OPAQUE_FLAG)) {
        GameBitmaps[handle].flags |= BF_TRANSPARENT;
        return 1;
      }
    }
  }
  return 0;
}

// clears bitmap
void bm_ClearBitmap(int handle) {
  int dx, dy;
  // DAJ	int rowsize_w = bm_rowsize(handle,0) >> 1;
  uint16_t *bmpdata = bm_data(handle, 0);
  int w = bm_w(handle, 0);
  int h = bm_h(handle, 0);
  for (dy = 0; dy < h; dy++) {
    for (dx = 0; dx < w; dx++)
      bmpdata[dx] = NEW_TRANSPARENT_COLOR;

    bmpdata += w;
  }
}
// Given a bitmap handle, breaks a bitmap into smaller pieces.
// Note, this routine isn't terrible fast or efficient, and you
// must free the bitmaps returned to you in the bm_array
bool bm_CreateChunkedBitmap(int bm_handle, chunked_bitmap *chunk) {
  int i;
  int *bm_array;
  int bw = bm_w(bm_handle, 0);
  int bh = bm_h(bm_handle, 0);
  // determine optimal size of the square bitmaps
  float fopt = 128.0f;
  int iopt;
  // find the smallest dimension and base off that
  int smallest = std::min(bw, bh);
  if (smallest <= 32)
    fopt = 32;
  else if (smallest <= 64)
    fopt = 64;
  else
    fopt = 128;
  iopt = (int)fopt;
  // Get how many pieces we need across and down
  float temp = bw / fopt;
  int how_many_across = temp;
  if ((temp - how_many_across) > 0)
    how_many_across++;
  temp = bh / fopt;
  int how_many_down = temp;
  if ((temp - how_many_down) > 0)
    how_many_down++;
  ASSERT(how_many_across > 0);
  ASSERT(how_many_down > 0);
  // Allocate memory to hold our list of pieces
  bm_array = (int *)mem_malloc(how_many_down * how_many_across * sizeof(int));
  ASSERT(bm_array);
  for (i = 0; i < how_many_down * how_many_across; i++) {
    bm_array[i] = bm_AllocBitmap(iopt, iopt, 0);
    ASSERT(bm_array[i] > -1);
    // Fill our new pieces with transparency
    bm_ClearBitmap(bm_array[i]);
  }
  // Now go through our big bitmap and partition it into pieces
  uint16_t *src_data = bm_data(bm_handle, 0);
  uint16_t *sdata;
  uint16_t *ddata;
  int shift;
  switch (iopt) {
  case 32:
    shift = 5;
    break;
  case 64:
    shift = 6;
    break;
  case 128:
    shift = 7;
    break;
  default:
    Int3(); // Get Jeff
    break;
  }
  int maxx, maxy;
  int windex, hindex;
  int s_y, s_x, d_y, d_x;
  for (hindex = 0; hindex < how_many_down; hindex++) {
    for (windex = 0; windex < how_many_across; windex++) {
      // loop through the chunks
      // find end x and y
      if (windex < how_many_across - 1)
        maxx = iopt;
      else
        maxx = bw - (windex << shift);
      if (hindex < how_many_down - 1)
        maxy = iopt;
      else
        maxy = bh - (hindex << shift);
      // find the starting source x and y
      s_x = (windex << shift);
      s_y = (hindex << shift);
      // get the pointers pointing to the right spot
      ddata = bm_data(bm_array[hindex * how_many_across + windex], 0);
      sdata = &src_data[s_y * bw + s_x];
      // copy the data
      for (d_y = 0; d_y < maxy; d_y++) {
        for (d_x = 0; d_x < maxx; d_x++) {
          ddata[d_x] = sdata[d_x];
        } // end for d_x
        sdata += bw;
        ddata += iopt;
      } // end for d_y
    }   // end for windex
  }     // end for hindex
  // Sirrah, we're done!
  // Tell the calling function how many pieces we have in x and y
  chunk->pw = bw;
  chunk->ph = bh;
  chunk->w = how_many_across;
  chunk->h = how_many_down;
  chunk->bm_array = bm_array;
  return true;
}
//	destroys a chunked bitmap.
void bm_DestroyChunkedBitmap(chunked_bitmap *chunk) {
  int i, num_bmps = chunk->w * chunk->h;
  for (i = 0; i < num_bmps; i++)
    bm_FreeBitmap(chunk->bm_array[i]);
  mem_free(chunk->bm_array);
  chunk->bm_array = NULL;
}
// Changes the size of a bitmap to a new size
void bm_ChangeSize(int handle, int new_w, int new_h) {
  int mipped = bm_mipped(handle);
  int n;
  int mem_used = (GameBitmaps[handle].width * GameBitmaps[handle].height * 2);
  n = bm_AllocBitmap(new_w, new_h, mipped * ((new_w * new_h * 2) / 3));
  ASSERT(n >= 0);
  if (mipped)
    GameBitmaps[n].flags |= BF_MIPMAPPED;
  if (GameBitmaps[handle].format == BITMAP_FORMAT_4444)
    GameBitmaps[n].format = BITMAP_FORMAT_4444;

  bm_ScaleBitmapToBitmap(n, handle);
  Bitmap_memory_used -= mem_used + (mipped * (mem_used / 3));
  mem_free(GameBitmaps[handle].data16);
  GameBitmaps[handle].data16 = GameBitmaps[n].data16;
  GameBitmaps[handle].width = new_w;
  GameBitmaps[handle].height = new_h;
  GameBitmaps[n].used = 0;
  Num_of_bitmaps--;
}
// Returns the format of this bitmap
int bm_format(int handle) {
  if (!GameBitmaps[handle].used) {
    Int3();
    return -1;
  }
  if (GameBitmaps[handle].flags & BF_NOT_RESIDENT)
    if (!bm_MakeBitmapResident(handle))
      return 0;
  return (GameBitmaps[handle].format);
}
