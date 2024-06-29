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

 * $Logfile: /DescentIII/Main/vclip.cpp $
 * $Revision: 26 $
 * $Date: 5/10/00 2:43p $
 * $Author: Jeff $
 *
 * <insert description of file here>
 *
 * $Log: /DescentIII/Main/vclip.cpp $
 *
 * 26    5/10/00 2:43p Jeff
 * fixed bug when paging in data if the tablefile specifies a full path to
 * a primative instead of just a filename (bug in 3rd party tablefile
 * editors)
 *
 * 25    4/19/00 5:07p Matt
 * From Duane for 1.4
 * Added checks, asserts, and fixes for bad return values
 *
 * 24    10/21/99 9:27p Jeff
 * B.A. Macintosh code merge
 *
 * 23    5/07/99 7:23p Jason
 * changes for low video memory
 *
 * 22    4/14/99 3:57a Jeff
 * fixed case mismatch in #includes
 *
 * 21    4/12/99 3:53p Jason
 * fixed loading of erroneous vclips
 *
 * 20    3/02/99 1:17p Jason
 * fixed loading of alpha numeric IFLs
 *
 * 19    2/10/99 3:47p Jason
 * table filter changes
 *
 * 18    1/22/99 3:59p Jason
 * added 256x256 textures to help with terrain skies
 *
 * 17    1/19/99 11:04a Jason
 * fixed scaling problem
 *
 * 16    1/18/99 11:11a Jason
 * made vclips be specular
 *
 * 15    10/18/98 2:59p Jason
 * fixes for beta4
 *
 * 14    10/14/98 5:50p Jason
 * added lowmem modes for quartering textures
 *
 * 13    10/09/98 3:32p Kevin
 * New memory library
 *
 * 12    10/08/98 4:23p Kevin
 * Changed code to comply with memory library usage. Always use mem_malloc
 * , mem_free and mem_strdup
 *
 * 11    5/19/98 5:43p Jason
 * free all vclips at the end of the program
 *
 * 10    5/14/98 2:38p Jason
 * made temp solution for vclip residency problem
 *
 * 9     5/14/98 12:56p Jason
 * changes to help lower memory usage
 *
 * 8     2/26/98 2:47p Mark
 * added assert
 *
 * 7     2/11/98 4:58p Jason
 * fixed some memory problems with resizing and mipping
 *
 * 6     11/03/97 6:21p Jason
 * fixed some problems with animating textures being remapped improperly
 *
 * 5     10/31/97 6:33p Jason
 * fixed bug with whitespace in ifl files
 *
 * 4     10/15/97 5:20p Jason
 * did a HUGE overhaul of the bitmap system
 *
 * 3     9/04/97 12:03p Matt
 * Got rid of warnings
 *
 * 2     8/20/97 6:09p Jason
 * fixed out of bounds problem that bounds checker reported
 *
 * 16    5/13/97 2:24p Jason
 * fixed a couple of animating texture bugs
 *
 * 15    5/12/97 11:41a Jason
 * made game work (default) to 16bit no mip maps mode
 * Saves us alot of memory
 *
 * 14    5/08/97 1:16p Jason
 * made ChangeEndName work with device independant calls
 *
 * 13    5/01/97 1:05p Mark
 * FROM JASON: Fixed stupid =/== bug in vclip loading
 *
 * 12    4/28/97 6:36p Jason
 * fixed a bug with vclips
 *
 * 11    4/25/97 3:31p Jason
 * implemented better memory management for vclips and bitmaps
 *
 * 10    4/24/97 5:42p Jason
 * got fireball vclips working
 *
 * 9     3/03/97 6:21p Matt
 * Changed cfile functions to use D3 naming convention
 *
 * 8     2/20/97 3:27p Jason
 * made ifl reader ignore lines beginning with spaces
 *
 * 7     2/19/97 3:23p Jason
 * added hooks to import animated iffs
 *
 * 6     2/19/97 11:37a Jason
 * take gametime into consideration when animating a vclip
 *
 * 5     2/10/97 1:58p Jason
 * made vclips free their bitmaps when they are deallocated
 *
 * 4     2/04/97 3:19p Jason
 * better error checking
 *
 * 3     1/25/97 5:56p Jason
 * changes to support new 8bit palettized textures and vclips
 *
 * 2     1/21/97 12:22p Jason
 * added vclip support
 *
 * $NoKeywords: $
 */

#include <cctype>
#include <cstdlib>
#include <cstring>
#include <filesystem>

#include "pstypes.h"
#include "pserror.h"
#include "bitmap.h"
#include "vclip.h"
#include "cfile.h"
#include "mono.h"
#include "ddio.h"
#include "gametexture.h"
#include "mem.h"
#include "game.h"

vclip GameVClips[MAX_VCLIPS];
int Num_vclips = 0;

#define DEFAULT_FRAMETIME .07f

#define VCLIP_VERSION 1
// Frees all the memory used by vclips
void FreeAllVClips() {
  mprintf(0, "Freeing all vclips!\n");

  for (int i = 0; i < MAX_VCLIPS; i++) {
    if (GameVClips[i].used > 0) {
      GameVClips[i].used = 1;
      FreeVClip(i);
    }
  }
}

// Simply sets all vclips to unused
void InitVClips() {
  for (int i = 0; i < MAX_VCLIPS; i++)
    GameVClips[i].used = 0;

  atexit(FreeAllVClips);
}

// Allocs a vclip for use
// Returns -1 on error
int AllocVClip() {
  int i;

  for (i = 0; i < MAX_VCLIPS; i++) {
    if (GameVClips[i].used == 0) {
      memset(&GameVClips[i], 0, sizeof(vclip));
      GameVClips[i].frames = (int16_t *)mem_malloc(VCLIP_MAX_FRAMES * sizeof(int16_t));
      ASSERT(GameVClips[i].frames);
      GameVClips[i].frame_time = DEFAULT_FRAMETIME;
      GameVClips[i].flags = VCF_NOT_RESIDENT;
      GameVClips[i].used = 1;
      Num_vclips++;
      return i;
    }
  }

  Int3(); // Ran out of vclips.  What the hell are you doing?  Get Jason
  return -1;
}

void FreeVClip(int num) {
  ASSERT(GameVClips[num].used > 0);

  GameVClips[num].used--;
  if (GameVClips[num].used > 0)
    return; // other things are using this vclip

  if (!(GameVClips[num].flags & VCF_NOT_RESIDENT)) {
    for (int i = 0; i < GameVClips[num].num_frames; i++)
      bm_FreeBitmap(GameVClips[num].frames[i]);
  }

  mem_free(GameVClips[num].frames);

  Num_vclips--;
  ASSERT(Num_vclips >= 0);
}

// Saves a given video clip to a file
// Returns 1 if everything ok, 0 otherwise
// "num" is index into GameVClip array
int SaveVClip(const std::filesystem::path& filename, int num) {
  CFILE *outfile;
  vclip *vc = &GameVClips[num];

  ASSERT(vc->used);
  ASSERT(!filename.empty());

  PageInVClip(num);

  outfile = (CFILE *)cfopen(filename, "wb");
  if (!outfile) {
    mprintf(0, "Couldn't save vclip %s!\n", filename.u8string().c_str());
    return 0;
  }

  // write out the header for this vclip
  cf_WriteByte(outfile, 127);
  cf_WriteByte(outfile, (int8_t)VCLIP_VERSION);

  cf_WriteByte(outfile, vc->num_frames);
  // cf_WriteFloat (outfile,vc->play_time);
  cf_WriteFloat(outfile, vc->frame_time);
  // cf_WriteInt (outfile,vc->flags);
  // cf_WriteFloat (outfile,vc->light_value);

  // Now save each frame of this vclip
  for (int i = 0; i < vc->num_frames; i++) {
    if (bm_SaveBitmap(outfile, vc->frames[i]) != 1) {
      mprintf(0, "Couldn't save frame %d of vclip %s!\n", i, filename.u8string().c_str());
      Int3();
      cfclose(outfile);
      return 0;
    }
  }

  cfclose(outfile);
  return 1;
}

extern int Low_vidmem;
// Pages in a vclip if it needs to be
void PageInVClip(int vcnum) {
  ASSERT(GameVClips[vcnum].used);
  if (!(GameVClips[vcnum].flags & VCF_NOT_RESIDENT))
    return;

  int mipped = 0;
  int texture_size = GameVClips[vcnum].target_size;
  vclip *vc = &GameVClips[vcnum];
  if (vc->flags & VCF_WANTS_MIPPED)
    mipped = 1;

  CFILE *infile = (CFILE *)cfopen(vc->name, "rb");
  if (!infile) {
    // due to a bug in some 3rd party tablefile editors, full paths might
    // have been used when they shouldn't have been
    char *end_ptr, *start_ptr;
    start_ptr = vc->name;
    end_ptr = start_ptr + strlen(start_ptr) - 1;
    while ((end_ptr >= start_ptr) && (*end_ptr != '\\'))
      end_ptr--;
    if (end_ptr < start_ptr) {
      mprintf(0, "Couldn't load vclip %s!\n", vc->name);
      return;
    }

    ASSERT(*end_ptr == '\\');
    end_ptr++;

    infile = (CFILE *)cfopen(end_ptr, "rb");
    if (!infile) {
      mprintf(0, "Couldn't load vclip %s!\n", vc->name);
      return;
    }
  }

  mprintf(0, "Paging in vclip %s!\n", vc->name);

  uint8_t start_val = cf_ReadByte(infile);
  int version = 0;
  if (start_val != 127) {
    version = 0;
    vc->num_frames = start_val;
    cf_ReadFloat(infile);
    vc->frame_time = cf_ReadFloat(infile);
    cf_ReadInt(infile);
    cf_ReadFloat(infile);
    vc->frame_time = DEFAULT_FRAMETIME;
  } else {
    version = cf_ReadByte(infile);
    vc->num_frames = cf_ReadByte(infile);
    vc->frame_time = cf_ReadFloat(infile);
    vc->frame_time = DEFAULT_FRAMETIME;
  }

  for (int i = 0; i < vc->num_frames; i++) {
    int n = bm_AllocLoadBitmap(infile, mipped);

    ASSERT(n > 0);

    int w, h;

    if (texture_size == NORMAL_TEXTURE) {
      w = TEXTURE_WIDTH;
      h = TEXTURE_HEIGHT;

#ifndef EDITOR
      if (Mem_low_memory_mode || Low_vidmem)
      {
        w = TEXTURE_WIDTH / 2;
        h = TEXTURE_HEIGHT / 2;
      }
#endif
    } else if (texture_size == SMALL_TEXTURE) {
      // Make small textures a quarter of the size of normal textures
      w = TEXTURE_WIDTH / 2;
      h = TEXTURE_HEIGHT / 2;

#ifndef EDITOR
      if (Mem_low_memory_mode || Low_vidmem)
      {
        w = TEXTURE_WIDTH / 4;
        h = TEXTURE_HEIGHT / 4;
      }
#endif
    } else if (texture_size == TINY_TEXTURE) {
      // Make these tinys an eigth of the size of normal textures
      w = TEXTURE_WIDTH / 4;
      h = TEXTURE_HEIGHT / 4;
    } else if (texture_size == HUGE_TEXTURE) {
      // Make these tinys an eigth of the size of normal textures
      w = TEXTURE_WIDTH * 2;
      h = TEXTURE_HEIGHT * 2;
    } else {
      w = bm_w(n, 0);
      h = bm_h(n, 0);
    }

    // If differing size, resize!
    if (w != bm_w(n, 0) || h != bm_h(n, 0)) {
      int dest_bm;

      dest_bm = bm_AllocBitmap(w, h, mipped * ((w * h * 2) / 3));
      ASSERT(dest_bm >= 0);
      if (mipped)
        GameBitmaps[dest_bm].flags |= BF_MIPMAPPED;
      GameBitmaps[dest_bm].format = GameBitmaps[n].format;

      bm_ScaleBitmapToBitmap(dest_bm, n);
      strcpy(GameBitmaps[dest_bm].name, GameBitmaps[n].name);
      bm_FreeBitmap(n);

      n = dest_bm;
    }

    ASSERT(n >= 0);
    vc->frames[i] = n; // assign frame to bitmap
  }

  cfclose(infile);

  vc->flags &= ~VCF_NOT_RESIDENT;
}

// Allocs and loads a vclip from the file named "filename"
// Returns -1 on error, index into GameVClip array on success
int AllocLoadVClip(const char *filename, int texture_size, int mipped, int pageable, int format) {
  char name[PAGENAME_LEN];
  int i;

  ASSERT(filename != NULL);

  i = strlen(filename);

  if (filename[i - 4] == '.' && filename[i - 3] == 'i' && filename[i - 2] == 'f' && filename[i - 1] == 'l')
    return AllocLoadIFLVClip(IGNORE_TABLE(filename), texture_size, mipped, format);

  if (filename[i - 4] == '.' && filename[i - 3] == 'a' && filename[i - 2] == 'b' && filename[i - 1] == 'm')
    Int3(); // Get Jason
            // return AllocLoadIFFAnimClip(filename,);

  ChangeVClipName(filename, name);

  // Check to see if this vclip already exists in memory
  if ((i = FindVClipName(IGNORE_TABLE(name))) != -1) {
    GameVClips[i].used++;
    return i;
  }

  // mprintf(0,"Loading OAF vclip %s\n",name);

  int vcnum = AllocVClip();

  ASSERT(vcnum >= 0);
  strncpy(GameVClips[vcnum].name, name, PAGENAME_LEN);

  if (mipped)
    GameVClips[vcnum].flags |= VCF_WANTS_MIPPED;

  GameVClips[vcnum].target_size = texture_size;

  if (pageable == 1)
    return vcnum;

  PageInVClip(vcnum);

  if (GameVClips[vcnum].num_frames < 1) {
    FreeVClip(vcnum);
    return -1;
  }

  return vcnum;
}

// Allocs and loads a vclip from a 3DS ILS file
// Returns -1 on error, else index into GameVClips on success
// Argument texture means that this vclip is an animated texture and
// needs to have an 8bit version
int AllocLoadIFLVClip(const char *filename, int texture_size, int mipped, int format) {
  CFILE *infile;
  char name[PAGENAME_LEN];
  uint32_t i, done = 0;

  ASSERT(filename != NULL);

  ChangeVClipName(filename, name);

  // Check to see if this vclip already exists in memory
  if ((i = FindVClipName(IGNORE_TABLE(name))) != -1) {
    GameVClips[i].used++;
    return i;
  }

  infile = (CFILE *)cfopen(filename, "rt");
  if (!infile) {
    mprintf(0, "Couldn't load IFL vclip %s!\n", filename);
    return -1;
  }

  mprintf(0, "Loading IFL vclip %s\n", name);

  int vcnum = AllocVClip();

  ASSERT(vcnum >= 0);

  vclip *vc = &GameVClips[vcnum];

  while (!done) {
    char curline[200];

    if (cfeof(infile)) {
      done = 1;
      continue;
    }

    // Read a line and parse it
    cf_ReadString(curline, 200, infile);

    if (curline[0] == ';' || curline[1] == ';' || curline[0] == ' ' || curline[1] == ' ')
      continue;
    if (!(isalnum(curline[0])))
      continue;

    else if (curline[0] == '$') {
      char new_command[50];

      int i;
      for (i = 0; curline[i + 1] != '=' && i < 50; i++) {
        new_command[i] = curline[i + 1];
      }
      if (i == 50) {
        Int3(); // bad command in IFL!
        return -1;
      }

      i++; // advance to data

      // parse data
      if (!stricmp(new_command, "TIME")) {
        // Set play time
        float play_time = atof(&curline[i]);
        ASSERT(play_time >= 0);
      }
    } else {
      int lastslash = -1;
      char bmname[200];

      for (i = 0; i < strlen(curline); i++)
        if (curline[i] == '\\')
          lastslash = i;

      if (lastslash == -1) {
        for (i = 0; i < strlen(filename); i++)
          if (filename[i] == '\\')
            lastslash = i;

        ASSERT(lastslash != -1);

        strcpy(bmname, filename);
        bmname[lastslash + 1] = 0;
        strcat(bmname, curline);
      } else
        strcpy(bmname, curline);

      // Try and load this file

      int bm = bm_AllocLoadFileBitmap(IGNORE_TABLE(bmname), 0, format);
      if (bm < 1) {
        Error("Error loading frame %d of ILS file %s!\n", vc->num_frames, filename);
        cfclose(infile);
        return -1;
      }

      int w, h;

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
      } else {
        w = bm_w(bm, 0);
        h = bm_h(bm, 0);
      }

      // If differing size, resize!
      if (w != bm_w(bm, 0) || h != bm_h(bm, 0)) {
        int dest_bm;

        dest_bm = bm_AllocBitmap(w, h, mipped * ((w * h) / 3));
        ASSERT(dest_bm >= 0);
        if (mipped)
          GameBitmaps[dest_bm].flags |= BF_MIPMAPPED;
        GameBitmaps[dest_bm].format = GameBitmaps[bm].format;

        bm_ScaleBitmapToBitmap(dest_bm, bm);
        strcpy(GameBitmaps[dest_bm].name, GameBitmaps[bm].name);
        bm_FreeBitmap(bm);

        bm = dest_bm;
      }

      vc->frames[vc->num_frames] = bm;
      vc->num_frames++;
    }
  }

  cfclose(infile);

  if (vc->num_frames == 0) {
    mprintf(0, "vclip had no valid bitmap names!\n");
    FreeVClip(vcnum);
    return -1;
  }

  strcpy(vc->name, name);
  return vcnum;
}

// gets the filename from a path, plus appends our .oaf extension
void ChangeVClipName(const char *src, char *dest) {
  int limit;
  char path[256], ext[256], filename[256];

  limit = PAGENAME_LEN - 5;

  ddio_SplitPath(src, path, filename, ext);

  // Make sure we don't go over our name length limit
  strncpy(dest, filename, limit);

  strcat(dest, ".oaf");
}
// Searches thru all vclips for a specific name, returns -1 if not found
// or index of vclip with name
int FindVClipName(const char *name) {
  int i;

  for (i = 0; i < MAX_VCLIPS; i++)
    if (GameVClips[i].used && !stricmp(GameVClips[i].name, name))
      return i;

  return -1;
}
