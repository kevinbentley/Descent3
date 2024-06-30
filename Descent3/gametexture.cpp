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

 * $Logfile: /DescentIII/Main/gametexture.cpp $
 * $Revision: 57 $
 * $Date: 4/19/00 5:07p $
 * $Author: Matt $
 *
 * <GameTexture--Texture management at the game level>
 *
 * $Log: /DescentIII/Main/gametexture.cpp $
 *
 * 57    4/19/00 5:07p Matt
 * From Duane for 1.4
 * Added checks, asserts, and fixes for bad return values
 *
 * 56    10/21/99 6:34p Matt
 * Mac merge
 *
 * 55    5/23/99 7:43p Jason
 * fixed briefing problem with lowmem textures
 *
 * 54    5/07/99 7:22p Jason
 * changes for cards with low videomemory
 *
 * 53    4/30/99 5:06p Kevin
 * misc dedicated server, networking and low memory enhancements
 *
 * 52    4/22/99 3:23p Jason
 *
 * 51    4/17/99 6:15p Samir
 * replaced gr.h with grdefs.h and fixed resulting compile bugs.
 *
 * 50    4/13/99 12:03p Jason
 * more memory savings for dedicated server
 *
 * 49    4/12/99 3:04p Jason
 * changes for low memory
 *
 * 48    4/09/99 7:04p Jason
 * changed some texture defines
 *
 * 47    4/01/99 1:21p Jason
 * don't resize huge textures
 *
 * 46    3/30/99 6:01p Jason
 * added new procedural effect
 *
 * 45    2/12/99 3:37p Jason
 * added client-side interpolation...its not fully debugged though.
 *
 * 44    2/10/99 3:38p Jason
 * table file filter fixups
 *
 * 43    1/29/99 6:29p Jason
 * first pass at adding bumpmaps
 *
 * 42    1/22/99 3:59p Jason
 * added 256x256 textures to help with terrain skies
 *
 * 41    1/21/99 11:15p Jeff
 * pulled out some structs and defines from header files and moved them
 * into seperate header files so that multiplayer dlls don't require major
 * game headers, just those new headers.  Side effect is a shorter build
 * time.  Also cleaned up some header file #includes that weren't needed.
 * This affected polymodel.h, object.h, player.h, vecmat.h, room.h,
 * manage.h and multi.h
 *
 * 40    1/18/99 11:11a Jason
 * made vclips be specular
 *
 * 39    11/30/98 5:50p Jason
 * added 4444 bitmap support
 *
 * 38    10/21/98 9:47a Kevin
 *
 * 37    10/20/98 6:22p Jason
 * added superlowmem mode
 *
 * 36    10/14/98 5:50p Jason
 * added lowmem modes for quartering textures
 *
 * 35    10/13/98 1:26p Jason
 * made new detail level settings work
 *
 * 34    10/08/98 2:27p Jason
 * sped up table file loading
 *
 * 33    10/07/98 5:03p Jason
 * more options for textures
 *
 * 32    10/01/98 2:47p Jason
 * added timed procedurals
 *
 * 31    8/13/98 11:57a Jason
 * added water procedurals
 *
 * 30    7/31/98 10:50a Jason
 * fixed memory leak
 *
 * 29    7/16/98 12:41p Jason
 * fixed dumb bug
 *
 * 28    7/14/98 6:50p Jason
 * made procedurals save out to the table file
 *
 * 27    7/09/98 7:30p Jason
 * more procedural stuff
 *
 * 26    7/07/98 4:12p Jason
 * checkin for procedurals
 *
 * 25    7/06/98 12:55p Jason
 * added first pass at procedurals
 *
 * 24    6/10/98 12:21p Matt
 * Revamped system that controls what textures are displayed on the
 * texture tab.  Should work correctly now, and will now save the settings
 * to the registry.  Also, textures now default to no type set, not all
 * types set.
 *
 * 23    5/20/98 5:44p Jason
 * incremental checkin for bumpmapping
 *
 * 22    5/20/98 1:08p Jason
 * more stuff for adding bumpmaps
 *
 * 21    5/14/98 2:38p Jason
 * made temp solution for vclip residency problem
 *
 * 20    5/14/98 2:17p Jason
 * more changes to be memory friendly
 *
 * 19    3/17/98 4:52p Jason
 * fixed compiler warning
 *
 * 17    3/17/98 4:33p Jason
 * Added size changing to bitmaps/textures
 *
 * 16    2/13/98 12:40p Jason
 * added functions to touch all data in a level when the level is loaded
 *
 * 15    2/11/98 4:58p Jason
 * fixed some memory problems with resizing and mipping
 *
 * 14    2/10/98 11:38a Matt
 * Ripped out the obsolete merge stuff
 *
 * 13    12/19/97 6:07p Jason
 * sped up bitmap loading
 *
 * 12    12/19/97 2:46p Jason
 * implemented bitmap paging routines
 *
 * 11    10/30/97 12:02p Jason
 * fixed an error checking bug
 *
 * 10    10/21/97 12:06p Jason
 * added mprintf warning to resizing of textures
 *
 * 9     10/20/97 6:20p Mark
 * FROM JASON: Fixed dumb no-name bug
 *
 * 8     10/15/97 5:20p Jason
 * did a HUGE overhaul of the bitmap system
 *
 * 7     10/13/97 3:56p Jason
 * made a better 3d bitmap system
 *
 * 6     9/12/97 4:00p Matt
 * If a game texture is not used, return the handle for the error bitmap
 *
 * 5     8/19/97 1:20p Jason
 * set reflectivity to .5 by default
 *
 * 4     8/08/97 12:58p Jason
 * got texture sliding and pingponging working
 *
 * 3     8/04/97 3:28p Jason
 * added alpha blending per texture
 *
 * 21    6/17/97 2:53p Matt
 * Allow 128x128 tmap2s over 64x64 tmap1s by scaling up the bottom
 * texture.  This is only temporary, because I think we'll be totally
 * revising the tmap2 system.
 *
 * 20    6/06/97 3:57p Jason
 * implemented changes for small textures and automatic tmap2 recognition
 *
 * 19    6/03/97 3:28p Jason
 * fixed texturing problems
 *
 * 18    5/27/97 4:39p Jason
 * changes to support OpenGL
 *
 * 17    5/23/97 7:07p Matt
 * Added code, data, & dialogs to keep track of what a texture is used for
 * (mine, terrain, object) so we can display in the texture dialog only
 * the ones we're interested in.
 *
 * 16    5/19/97 5:10p Jason
 * changes for our new abstracted renderer code
 *
 * 15    5/13/97 2:24p Jason
 * fixed a couple of animating texture bugs
 *
 * 14    5/13/97 12:45p Matt
 * Fixed bug in rotated cases of 16-bit texmerge
 *
 * 13    5/12/97 11:41a Jason
 * made game work (default) to 16bit no mip maps mode
 * Saves us alot of memory
 *
 * 12    5/12/97 11:19a Matt
 * Worked on 16-bit merge code, which is still broken
 *
 * 11    5/02/97 7:28p Matt
 * Got tmap2 system working, though I think the merge for 16-bit textures
 * probably doesn't work
 *
 * 10    4/28/97 6:36p Jason
 * fixed a bug with vclips
 *
 * 9     4/25/97 3:59p Jason
 * fixed a bug that my last checkin caused
 *
 * 8     4/25/97 3:31p Jason
 * implemented better memory management for vclips and bitmaps
 *
 * 7     4/21/97 5:29p Jason
 * got animating textures to work on polygonal objects
 *
 * 6     2/19/97 3:23p Jason
 * added hooks to import animated iffs
 *
 * 5     2/19/97 11:37a Jason
 * take gametime into consideration when animating a vclip
 *
 * 4     2/11/97 3:21p Jason
 * added MakeTexture8Bit function
 *
 * 3     1/25/97 5:55p Jason
 * changes to support new 8bit palettized textures and vclips
 *
 * 2     1/16/97 3:01p Jason
 * moved all Gametexture management stuff to the game level instead of in
 * the texmap libarry.
 *
 * $NoKeywords: $
 */

#include "grdefs.h"
#include "pstypes.h"
#include "gametexture.h"
#include "mono.h"
#include "bitmap.h"
#include "pserror.h"
#include "vclip.h"
#include "texture.h"
#include "game.h"
#include "bumpmap.h"
#include <stdlib.h>
#include <string.h>
#include "procedurals.h"
#include "ddio.h"
#include "config.h"
#include "args.h"
#include "mem.h"

// TODO: MTS: this is only used in this file.
int Num_textures = 0;
std::array<texture, MAX_TEXTURES> GameTextures;

extern bool Mem_superlow_memory_mode;

static int Total_memory_saved = 0;

void FreeAllTextures() {
  for (int i = 0; i < MAX_TEXTURES; i++) {
    if (GameTextures[i].used)
      FreeTexture(i);
  }
}

int InitTextures() {
  // Initalizes the texture system

  int i, tex;

  mprintf(0, "Initializing texture system.\n");
  for (i = 0; i < MAX_TEXTURES; i++)
    GameTextures[i].used = 0;

  tex = AllocTexture();
  GameTextures[tex].bm_handle = BAD_BITMAP_HANDLE;
  strcpy(GameTextures[tex].name, "SAMPLE TEXTURE");

  // Initialize procedural tables and such
  InitProcedurals();

  atexit(FreeAllTextures);

  return 1;
}

// Set aside a texture for use
// This function returns a valid texture handle
int AllocTexture(void) {
  int i;

  for (i = 0; i < MAX_TEXTURES; i++)
    if (GameTextures[i].used == 0)
      break;

  ASSERT(i != MAX_TEXTURES); // we've run out of texture slots

  Num_textures++;

  memset(&GameTextures[i], 0, sizeof(texture));

  GameTextures[i].used = 1;

  GameTextures[i].corona_type = 0;
  GameTextures[i].bumpmap = -1;
  GameTextures[i].procedural = NULL;
  GameTextures[i].name[0] = 0;
  GameTextures[i].flags = 0; // default to no type
  GameTextures[i].alpha = 1.0;
  GameTextures[i].speed = 1.0;
  GameTextures[i].reflectivity = .6f;
  GameTextures[i].bm_handle = -1;
  GameTextures[i].destroy_handle = -1;

  return i;
}

// Searches thru all textures for a specific name, returns -1 if not found
// or index of texture with name
int FindTextureName(const char *name) {
  int i, num_counted = 0;
  ;

  ASSERT(name != NULL);

  for (i = 0; i < MAX_TEXTURES && num_counted < Num_textures; i++) {
    if (GameTextures[i].used) {
      num_counted++;
      if (!stricmp(name, GameTextures[i].name))
        return i;
    }
  }

  return -1;
}

// Searches thru all textures for a bitmap of a specific name, returns -1 if not found
// or index of texture with name
int FindTextureBitmapName(const char *name) {
  int i;

  ASSERT(name != NULL);

  for (i = 0; i < MAX_TEXTURES; i++) {
    if (GameTextures[i].used) {
      if (GameTextures[i].flags & TF_ANIMATED) {
        int not_res = 0;
        if (GameVClips[GameTextures[i].bm_handle].flags & VCF_NOT_RESIDENT)
          not_res = 1;

        PageInVClip(GameTextures[i].bm_handle);
        vclip *vc = &GameVClips[GameTextures[i].bm_handle];
        ASSERT(vc->used);

        int t;
        int retval = -1;

        for (t = 0; t < vc->num_frames && retval == -1; t++)
          if ((!stricmp(GameBitmaps[vc->frames[t]].name, name)))
            retval = i;

        if (retval != -1)
          return retval;
      } else {
        if ((!stricmp(GameBitmaps[GameTextures[i].bm_handle].name, name)))
          return i;
      }
    }
  }

  return -1;
}

// Allocates memory for a procedural that is attached to a texture
int AllocateProceduralForTexture(int handle) {
  int w, h;

  if (GameTextures[handle].flags & TF_TEXTURE_64) {
    w = h = 64;
  } else if (GameTextures[handle].flags & TF_TEXTURE_32) {
    w = h = 32;
  } else {
    w = h = 128;
  }

  GameTextures[handle].procedural = (proc_struct *)mem_malloc(sizeof(proc_struct));
  ASSERT(GameTextures[handle].procedural);

  GameTextures[handle].procedural->proc1 = NULL;
  GameTextures[handle].procedural->proc2 = NULL;

  GameTextures[handle].procedural->last_evaluation_time = 0;
  GameTextures[handle].procedural->osc_time = 0;
  GameTextures[handle].procedural->osc_value = 8;

  GameTextures[handle].procedural->procedural_bitmap = bm_AllocBitmap(w, h, 0);
  ASSERT(GameTextures[handle].procedural->procedural_bitmap >= 0);

  GameTextures[handle].procedural->memory_type = PROC_MEMORY_TYPE_NONE;

  GameTextures[handle].procedural->palette = (uint16_t *)mem_malloc(256 * 2);

  GameTextures[handle].procedural->last_procedural_frame = -1;
  GameTextures[handle].procedural->heat = 128;

  GameTextures[handle].procedural->dynamic_proc_elements = -1;
  GameTextures[handle].procedural->static_proc_elements = NULL;

  GameTextures[handle].procedural->num_static_elements = 0;

  GameTextures[handle].procedural->light = 1;
  GameTextures[handle].procedural->thickness = 4;

  memcpy(GameTextures[handle].procedural->palette, DefaultProcPalette, 256 * 2);

  return 1;
}

// Allocates the memory needed for static elements for a procedural texture
void AllocateStaticProceduralsForTexture(int handle, int num_elements) {
  GameTextures[handle].procedural->static_proc_elements =
      (static_proc_element *)mem_malloc(sizeof(static_proc_element) * num_elements);
  ASSERT(GameTextures[handle].procedural->static_proc_elements);
}

// Frees the memory used by static procedural elements
void FreeStaticProceduralsForTexture(int handle) {
  if (GameTextures[handle].procedural->static_proc_elements)
    mem_free(GameTextures[handle].procedural->static_proc_elements);
  GameTextures[handle].procedural->static_proc_elements = NULL;
}

// Given a texture handle, returns that textures bitmap
// If the texture is animated, returns framenum mod num_of_frames in the animation
// Force is to force the evaluation of a procedural
// Also figures in gametime
int GetTextureBitmap(int handle, int framenum, bool force) {
  int src_bitmap;

  if (!GameTextures[handle].used)
    return 0;

  if (GameTextures[handle].flags & TF_ANIMATED) {
    float cur_frametime;
    int int_frame;
    texture *tex = &GameTextures[handle];
    PageInVClip(GameTextures[handle].bm_handle);

    vclip *vc = &GameVClips[GameTextures[handle].bm_handle];
    ASSERT(vc->used >= 1);

    if (GameTextures[handle].flags & TF_PING_PONG) {
      // Ping pong this texture

      float frametime = tex->speed / vc->num_frames;
      cur_frametime = Gametime / frametime;
      int_frame = cur_frametime;
      int_frame += framenum;

      int_frame %= (vc->num_frames * 2);
      if (int_frame >= vc->num_frames)
        int_frame = (vc->num_frames - 1) - (int_frame % vc->num_frames);
      else
        int_frame %= vc->num_frames;
      src_bitmap = vc->frames[int_frame];
    } else {
      float frametime = tex->speed / vc->num_frames;
      cur_frametime = Gametime / frametime;
      int_frame = cur_frametime;
      int_frame += framenum;
      src_bitmap = vc->frames[int_frame % vc->num_frames];
    }
  } else {
    src_bitmap = GameTextures[handle].bm_handle;
  }

  if (GameTextures[handle].flags & TF_PROCEDURAL) // Do a procedural
  {
    int do_eval = 1;

    if (GameTextures[handle].procedural == NULL)
      AllocateProceduralForTexture(handle);

    if (GameTextures[handle].procedural->last_procedural_frame == FrameCount)
      do_eval = 0;
    if (timer_GetTime() <
        GameTextures[handle].procedural->last_evaluation_time + GameTextures[handle].procedural->evaluation_time)
      do_eval = 0;

    if (!force && !Detail_settings.Procedurals_enabled) {
      if (timer_GetTime() < GameTextures[handle].procedural->last_evaluation_time + 10.0)
        do_eval = 0;
    }

    if (do_eval) {
      EvaluateProcedural(handle);
      GameTextures[handle].procedural->last_procedural_frame = FrameCount;
      GameTextures[handle].procedural->last_evaluation_time = timer_GetTime();
      src_bitmap = GameTextures[handle].procedural->procedural_bitmap;
      GameBitmaps[src_bitmap].flags |= BF_CHANGED;
    } else
      src_bitmap = GameTextures[handle].procedural->procedural_bitmap;
  }

  return src_bitmap;
}

// Given a filename, loads either the bitmap or vclip found in that file.  If type
// is not NULL, sets it to 1 if file is animation, otherwise sets it to zero
int LoadTextureImage(const char *filename, int *type, int texture_size, int mipped, int pageable, int format) {
  int anim = 0, bm_handle;
  char extension[10];
  int w, h;

  int len = strlen(filename);

  if (len < 4)
    return -1;

  strncpy(extension, &filename[len - 3], 5);

  if ((!strnicmp("oaf", extension, 3)) || (!strnicmp("ifl", extension, 3)) || (!strnicmp("abm", extension, 3)))
    anim = 1;

  if (type != NULL)
    *type = anim;

  if (anim)
    bm_handle = AllocLoadVClip(IGNORE_TABLE(filename), texture_size, mipped, pageable, format);
  else {
    if (pageable)
      bm_handle = bm_AllocLoadFileNoMemBitmap(IGNORE_TABLE(filename), mipped, format);
    else
      bm_handle = bm_AllocLoadFileBitmap(IGNORE_TABLE(filename), mipped, format);

    if (bm_handle < 1)
      return -1;

    if (texture_size == NORMAL_TEXTURE) {
      w = TEXTURE_WIDTH;
      h = TEXTURE_HEIGHT;
    } else if (texture_size == SMALL_TEXTURE) {
      // Make small textures a quarter of the size of normal textures
      w = TEXTURE_WIDTH / 2;
      h = TEXTURE_HEIGHT / 2;
    } else if (texture_size == TINY_TEXTURE) {
      // Make these tinys an eigth of the size of normal textures
      w = TEXTURE_WIDTH / 4;
      h = TEXTURE_HEIGHT / 4;
    } else if (texture_size == HUGE_TEXTURE) {
      // Make these tinys an eigth of the size of normal textures
      w = TEXTURE_WIDTH * 2;
      h = TEXTURE_HEIGHT * 2;
    } else
      return bm_handle;

    // If differing size, resize!
    if (!pageable && (w != bm_w(bm_handle, 0) || h != bm_h(bm_handle, 0))) {
      int dest_bm;

      mprintf(0, "WARNING: Resizing bitmap %s from %d x %d to %d x %d!\n", GameBitmaps[bm_handle].name,
               bm_w(bm_handle, 0), bm_h(bm_handle, 0), w, h);

      dest_bm = bm_AllocBitmap(w, h, mipped * ((w * h * 2) / 3));
      ASSERT(dest_bm >= 0);

      if (mipped)
        GameBitmaps[dest_bm].flags |= BF_MIPMAPPED;
      GameBitmaps[dest_bm].format = format;

      bm_ScaleBitmapToBitmap(dest_bm, bm_handle);
      strcpy(GameBitmaps[dest_bm].name, GameBitmaps[bm_handle].name);
      bm_FreeBitmap(bm_handle);

      bm_handle = dest_bm;
    }
  }

  return bm_handle;
}

// Goes through and marks a texture as a tmap2 if its bitmap(s) have transparency
bool CheckIfTextureIsTmap2(int texnum) {
  if (GameTextures[texnum].flags & TF_ANIMATED) {
    vclip *vc = &GameVClips[GameTextures[texnum].bm_handle];
    PageInVClip(GameTextures[texnum].bm_handle);

    ASSERT(vc->used);
    for (int i = 0; i < vc->num_frames; i++) {
      if (bm_SetBitmapIfTransparent(vc->frames[i])) {
        GameTextures[texnum].flags |= TF_TMAP2;
        return 1;
      }
    }
  } else {
    if (bm_SetBitmapIfTransparent(GameTextures[texnum].bm_handle)) {
      GameTextures[texnum].flags |= TF_TMAP2;
      return 1;
    }
  }

  return 0;
}

extern int Low_vidmem;
// Pages a texture into memory, optionally resizing it if in low mem mode
// Doesn't resize if resize is false
void PageInTexture(int n, bool resize) {
  static int super_low_mem = -1;

  if (super_low_mem == -1) {
    if (Mem_superlow_memory_mode || FindArg("-dedicated"))
      super_low_mem = 1;
    else
      super_low_mem = 0;
  }
  if (GameTextures[n].used == 0)
    return;

  texture *texp = &GameTextures[n];

  bm_data(texp->bm_handle, 0);

#ifndef EDITOR
  if (resize == true && (Mem_low_memory_mode || Low_vidmem))
  {
    if (!(texp->flags & (TF_TEXTURE_32 | TF_TEXTURE_256)) && !(texp->flags & TF_PROCEDURAL)) {
      int bm_handle = texp->bm_handle;
      int w = TEXTURE_WIDTH, h = TEXTURE_HEIGHT;

      if (texp->flags & TF_TEXTURE_64) {
        w /= 2;
        h /= 2;
      }

      w /= 2;
      h /= 2;

      if (super_low_mem)
      {
        if (w != 32 || h != 32) {
          w = 32;
          h = 32;
        }
      }

      if ((w != bm_w(bm_handle, 0) || h != bm_h(bm_handle, 0))) {
        int dest_bm;
        int mipped = 0;
        int saved = 0;

        if (texp->flags & TF_TEXTURE_64)
          saved = 6144;
        else
          saved = 24576;

        if (bm_mipped(bm_handle))
          mipped = 1;

        if (mipped)
          saved += (saved / 3);

        Total_memory_saved += saved;

        mprintf(0, "Low mem: Resizing bitmap %s to %d x %d!\n", GameBitmaps[bm_handle].name, w, h);
        mprintf(0, "Total memory saved=%d\n", Total_memory_saved);

        dest_bm = bm_AllocBitmap(w, h, mipped * ((w * h * 2) / 3));
        ASSERT(dest_bm >= 0);
        if (mipped)
          GameBitmaps[dest_bm].flags |= BF_MIPMAPPED;

        GameBitmaps[dest_bm].format = GameBitmaps[bm_handle].format;

        bm_ScaleBitmapToBitmap(dest_bm, bm_handle);
        strcpy(GameBitmaps[dest_bm].name, GameBitmaps[bm_handle].name);
        bm_FreeBitmap(bm_handle);

        texp->bm_handle = dest_bm;
      }
    }
  }
#endif
}

// Pages in this particular texture
void TouchTexture(int n) {
  if (GameTextures[n].flags & TF_ANIMATED) {
    PageInVClip(GameTextures[n].bm_handle);
  } else
    PageInTexture(n, true);
}

// Frees all the bumpmaps associated with a texture
void FreeTextureBumpmaps(int tex_handle) {
  ASSERT(GameTextures[tex_handle].used > 0);

  if (GameTextures[tex_handle].bumpmap != -1) {
    bump_FreeBumpmap(GameTextures[tex_handle].bumpmap);
    GameTextures[tex_handle].bumpmap = -1;
  }
}

// Builds the bumpmaps for the past in texture
void BuildTextureBumpmaps(int texhandle) {
  int i, t;
  int8_t *buffer;

  if (GameTextures[texhandle].flags & TF_ANIMATED)
    return; // No bumps for animated textures

  mprintf(0, "Calculating bumpmap for texture named %s.\n", GameTextures[texhandle].name);

  // Make sure there is no bump already
  ASSERT(GameTextures[texhandle].bumpmap == -1);

  // Get width and height
  int w = bm_w(GameTextures[texhandle].bm_handle, 0);
  int h = bm_h(GameTextures[texhandle].bm_handle, 0);

  // Allocate a bumpmap
  int bump = bump_AllocBumpmap(w, h);
  ASSERT(bump != -1);
  GameTextures[texhandle].bumpmap = bump;

  // allocate memory for our buffer
  buffer = (int8_t *)mem_malloc(w * h);
  ASSERT(buffer);

  uint16_t *src_data = (uint16_t *)bm_data(GameTextures[texhandle].bm_handle, 0);

  // create the grayscale
  for (i = 0; i < h; i++) {
    for (t = 0; t < w; t++) {
      uint16_t color = src_data[i * w + t];

      int red = ((color >> 10) & 0x1f) << 3;
      int green = ((color >> 5) & 0x1f) << 3;
      int blue = ((color) & 0x1f) << 3;

      buffer[i * w + t] = (int8_t)(0.29 * red + 0.60 * green + 0.11 * blue);
    }
  }

  uint16_t *dest_data = (uint16_t *)bump_data(bump);

  for (i = 0; i < h; i++) {
    int8_t *pDst = (int8_t *)(dest_data + i * w);
    for (t = 0; t < w; t++) {
      int v00, v01, v10;

      v00 = buffer[(i * w + t)]; // Get current pixel. *3 for 24 bits src

      if (t == w - 1)              // Special case for last column
        v01 = buffer[(i * w + t)]; // Get pixel to the right
      else
        v01 = buffer[(i * h + t + 1)]; // Get pixel to the right

      if (i == h - 1)            // Special case for last row
        v10 = buffer[i * w + t]; // Get pixel one line below
      else
        v10 = buffer[((i + 1) * w) + t]; // Get pixel one line below

      int iDu = v00 - v01; // The delta-u bump value
      int iDv = v00 - v10; // The delta-v bump value
      *pDst++ = (int8_t)iDu;
      *pDst++ = (int8_t)iDv;
    }
  }

  mem_free(buffer);
}

// Frees all the procedural memory for a texture
void FreeProceduralForTexture(int n) {
  if (GameTextures[n].procedural != NULL) {
    FreeStaticProceduralsForTexture(n);
    mem_free(GameTextures[n].procedural->proc1);
    mem_free(GameTextures[n].procedural->proc2);
    bm_FreeBitmap(GameTextures[n].procedural->procedural_bitmap);
    mem_free(GameTextures[n].procedural->palette);
    mem_free(GameTextures[n].procedural);

    GameTextures[n].procedural = NULL;
  }
}

// Frees a texture that is being used and
// Decrements number of textures in use
void FreeTexture(int n) {
  ASSERT(GameTextures[n].used);

  FreeTextureBumpmaps(n);

  GameTextures[n].used = 0;
  GameTextures[n].name[0] = 0;
  Num_textures--;

  FreeProceduralForTexture(n);
}

// Given current index, gets index of next texture in use
int GetNextTexture(int n) {
  int i;

  if (Num_textures == 0)
    return -1;

  for (i = n + 1; i < MAX_TEXTURES; i++) {
    if (GameTextures[i].used)
      return i;
  }
  for (i = 0; i < n; i++) {
    if (GameTextures[i].used)
      return i;
  }

  return n;
}
// Given current index, gets index of prev texture in use
int GetPreviousTexture(int n) {
  int i;

  if (Num_textures == 0)
    return -1;

  for (i = n - 1; i >= 0; i--) {
    if (GameTextures[i].used)
      return i;
  }
  for (i = MAX_TEXTURES - 1; i > n; i--) {
    if (GameTextures[i].used)
      return i;
  }

  return n;
}
