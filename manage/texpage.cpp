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

 * $Logfile: /DescentIII/Main/manage/texpage.cpp $
 * $Revision: 61 $
 * $Date: 10/08/01 4:20p $
 * $Author: Matt $
 *
 * For loading/saving of texture types
 *
 * $Log: /DescentIII/Main/manage/texpage.cpp $
 *
 * 61    10/08/01 4:20p Matt
 * Added system to check for errors when reading in add-on data.
 *
 * 59    9/06/01 10:32a Matt
 * Added code to fix problem poping add-on pages when the original pages
 * were in the extra.gam file.
 *
 * 58    3/20/00 12:28p Matt
 * Merge of Duane's post-1.3 changes.
 * Added malloc for temp struct instead of delcaring on the stack.
 *
 * 57    10/26/99 3:31p Jeff
 * handle extra.gam addon tablefile
 *
 * 56    9/18/99 8:49p Jeff
 * fixed bug with addon pages that have dependencies on other pages in the
 * addon tablefile
 *
 * 55    8/11/99 5:32p Jeff
 * changes to fix addon tablefile support so it works correctly
 *
 * 54    5/21/99 6:39a Matt
 * Fixed massive evil caused by recent changes for Mac, which resulted in
 * two functions using the same static data at the same time.
 *
 * 53    5/14/99 12:07p Jeff
 * error handling (Jason)
 *
 * 52    5/13/99 8:36p Matt
 * Made some local variables global to get around the 32K local variable
 * limit on the Mac.
 *
 * 51    4/14/99 1:34a Jeff
 * fixed case mismatched #includes
 *
 * 50    4/12/99 3:05p Jason
 * changes for 256 textures
 *
 * 49    4/09/99 7:04p Jason
 * changed some texture defines
 *
 * 48    4/09/99 12:51p Jason
 * corrected buggy sound resolving code
 *
 * 47    3/30/99 6:01p Jason
 * added new procedural effect
 *
 * 46    2/20/99 2:17p Matt
 * Added texture sounds
 *
 * 45    2/16/99 11:17a Jason
 * took out mprintf
 *
 * 44    2/01/99 11:47a Jason
 * fixed bumpmap errors
 *
 * 43    1/22/99 3:59p Jason
 * added 256x256 textures to help with terrain skies
 *
 * 42    1/13/99 7:05a Jeff
 * put #ifdef around #include <windows.h>
 *
 * 41    12/29/98 4:30p Jason
 * added add-on data functionality
 *
 * 40    12/17/98 12:02p Jason
 * fixed dumb procedural thing
 *
 * 39    11/06/98 12:35p Jason
 * more speedups for manage system
 *
 * 38    11/05/98 7:55p Jason
 * changes for new manage system
 *
 * 37    11/02/98 6:02p Jason
 * made yes network updates much faster
 *
 * 36    10/09/98 2:27p Jason
 * reorganized table file system
 *
 * 35    10/08/98 10:03p Jason
 * more filtered table file stuff
 *
 * 34    10/07/98 5:03p Jason
 * more options for textures
 *
 * 33    10/01/98 2:47p Jason
 * added timed procedurals
 *
 * 32    8/24/98 2:37p Jason
 * made table file more efficient with regards to invalid names
 *
 * 31    8/15/98 3:46p Matt
 * Got rid of compile warning
 *
 * 30    8/13/98 1:03p Jason
 * added some more procedural workers
 *
 * 29    8/12/98 4:24p Luke
 * temporary fix for dumb local table file conundrum
 *
 * 28    7/14/98 6:50p Jason
 * made procedurals save out to the table file
 *
 * 27    6/12/98 1:06p Jason
 * added smart loading from local table file
 *
 * 26    6/11/98 12:54p Mark
 * temp fix
 *
 * 25    6/10/98 12:21p Matt
 * Revamped system that controls what textures are displayed on the
 * texture tab.  Should work correctly now, and will now save the settings
 * to the registry.  Also, textures now default to no type set, not all
 * types set.
 *
 * 24    6/03/98 3:46p Jason
 * made megacell system more robust
 *
 * 23    5/20/98 1:08p Jason
 * more stuff for adding bumpmaps
 *
 * 22    5/04/98 6:08p Jason
 * sped up predictive pagefile loading
 *
 * 21    4/06/98 4:42p Jason
 * added texture alpha change
 *
 * 20    3/17/98 4:33p Jason
 * Added size changing to bitmaps/textures
 *
 * 19    2/23/98 1:22p Jason
 * made FindSpecific* read from the local drive, not the net drive - when
 * starting the editor
 *
 * 18    2/16/98 11:42a Jason
 * added better error checking for checking out files
 *
 * 17    2/12/98 1:32p Jason
 * got mipmapping working
 *
 * 16    1/14/98 7:55p Jason
 * make textures pageable depending on whether or not you're using the
 * network
 *
 * 15    12/19/97 2:46p Jason
 * implemented bitmap paging routines
 *
 * 14    12/10/97 5:29p Jason
 * warn if reusing a net texture
 *
 * 13    11/21/97 2:02p Jason
 * made light textures on model render that model face fully bright
 *
 * 12    10/20/97 5:05p Mark
 * FROM JASON: Changed error bitmap from -1 to 0
 *
 * 11    10/15/97 5:20p Jason
 * did a HUGE overhaul of the bitmap system
 *
 * 10    9/25/97 4:30p Jason
 * got destroyable textures working
 *
 * 9     8/19/97 1:21p Jason
 * set reflectivity to .5 by default
 *
 * 8     8/19/97 1:57a Jason
 * made rgb lighting take floats
 *
 * 7     8/12/97 1:10a Jason
 * added code to support radiosity lighting
 *
 * 6     8/08/97 12:59p Jason
 * got texture sliding and pingponging working
 *
 * 5     8/06/97 2:57p Jason
 * fixed alpha problem with reorder net pages
 *
 * 4     8/04/97 5:05p Jason
 * fixed dumb off-by-one error
 *
 * 3     8/04/97 3:28p Jason
 * added alpha blending per texture
 *
 * 31    6/24/97 12:42p Jason
 * checked in for safety
 *
 * 30    6/06/97 3:57p Jason
 * implemented changes for small textures and automatic tmap2 recognition
 *
 * 29    6/05/97 2:52p Jason
 * added megacell functions
 *
 * 28    5/30/97 5:46p Jason
 * added colored light functionality on a vertex level
 *
 * 27    5/23/97 7:07p Matt
 * Added code, data, & dialogs to keep track of what a texture is used for
 * (mine, terrain, object) so we can display in the texture dialog only
 * the ones we're interested in.
 *
 * 26    5/12/97 1:19p Jason
 * sped up texture loading a little bit
 *
 * 25    5/12/97 11:41a Jason
 * made game work (default) to 16bit no mip maps mode
 * Saves us alot of memory
 *
 * 24    5/08/97 12:41p Jason
 * made manage system work with device dependant path names
 *
 * 23    4/25/97 6:16p Jason
 * added switcheroo function
 *
 * 22    4/08/97 2:25a Chris
 * Fixed a problem with uninitialized data.  In addition it
 * fixed a problem with the .used flag that would happen
 * 1 out of 2^(sizeof(used_flag)) times (it would be zero
 * when it was supposed to be non-zero)
 *
 * 21    3/12/97 6:15 PM Jeremy
 * in mng_WriteTexturePage moved the declaration of int i outside of the
 * first for loop to the top of the function so that it will compile on
 * mac and PC at the same time. :)
 *
 * 20    3/03/97 6:21p Matt
 * Changed cfile functions to use D3 naming convention
 *
 * $NoKeywords: $
 */

#include <cstring>
#include <filesystem>

#include "cfile.h"
#include "manage.h"
#include "gametexture.h"
#include "bitmap.h"
#include "mono.h"
#include "pserror.h"
#include "texpage.h"
#include "vclip.h"
#include "ddio.h"
#include "args.h"
#include "sounds.h"
#include "soundpage.h"
#include "soundload.h"

// Texpage commands that are read/written
// A command is followed by a byte count describing how many bytes
// are in the data for the command
#define TEXPAGE_COMMAND_NAME 1
#define TEXPAGE_COMMAND_FLAGS 2
#define TEXPAGE_COMMAND_END 3
#define TEXPAGE_COMMAND_BITMAP_NAME 4
#define TEXPAGE_COMMAND_DESTROY_NAME 5
#define TEXPAGE_COMMAND_VERSION 6
#define TEXPAGE_COMMAND_REFLECT 7
#define TEXPAGE_COMMAND_DAMAGE 8
#define TEXPAGE_COMMAND_LIGHTING 9
#define TEXPAGE_COMMAND_SLIDE 10
#define TEXPAGE_COMMAND_NULL_NAME 11 // null terminated name string
#define TEXPAGE_COMMAND_BITMAP_NULL_NAME 12
#define TEXPAGE_COMMAND_DESTROY_NULL_NAME 13
#define TEXPAGE_COMMAND_COLORED_LIGHTING 14
#define TEXPAGE_COMMAND_ALPHA 15
#define TEXPAGE_COMMAND_SLIDE_FLOAT 16
#define TEXPAGE_COMMAND_LIGHTING_FLOAT 17
#define TEXPAGE_COMMAND_SPEED 18
#define TEXPAGE_COMMAND_FIRST_PROC_PAL 19
#define TEXPAGE_COMMAND_SECOND_PROC_PAL 20
#define TEXPAGE_COMMAND_PROCEDURAL 21
#define TEXPAGE_COMMAND_EXTRA_PROCEDURAL 22
#define TEXPAGE_COMMAND_EXTRA_PROCEDURAL2 23
#define TEXPAGE_COMMAND_CORONA 24

// Declare this here because it's too big to put on the stack on the Mac
static mngs_texture_page texpage1;

extern char *TablefileNameOverride;

#define TEXPAGE_VERSION 7
// Given an open file pointer and a texture handle, writes that texture page out
void mng_WriteTexturePage(CFILE *outfile, mngs_texture_page *texpage) {
  int i = 0;

  ASSERT(outfile != NULL);
  ASSERT(texpage != NULL);

  cf_WriteByte(outfile, PAGETYPE_TEXTURE);

  cf_WriteByte(outfile, TEXPAGE_COMMAND_VERSION);
  cf_WriteByte(outfile, 1);
  cf_WriteByte(outfile, TEXPAGE_VERSION);

  // Write out texture name
  cf_WriteByte(outfile, TEXPAGE_COMMAND_NULL_NAME);
  cf_WriteByte(outfile, strlen(texpage->tex_struct.name) + 1);
  cf_WriteString(outfile, texpage->tex_struct.name);

  // Write out its bitmaps name
  cf_WriteByte(outfile, TEXPAGE_COMMAND_BITMAP_NULL_NAME); // get ready to write out name
  cf_WriteByte(outfile, strlen(texpage->bitmap_name) + 1);
  cf_WriteString(outfile, texpage->bitmap_name);

  // Write out its bitmaps name
  cf_WriteByte(outfile, TEXPAGE_COMMAND_DESTROY_NULL_NAME); // get ready to write out name
  cf_WriteByte(outfile, strlen(texpage->destroy_name) + 1);
  cf_WriteString(outfile, texpage->destroy_name);

  cf_WriteByte(outfile, TEXPAGE_COMMAND_LIGHTING_FLOAT);
  cf_WriteByte(outfile, 4 * 3);
  cf_WriteFloat(outfile, texpage->tex_struct.r);
  cf_WriteFloat(outfile, texpage->tex_struct.g);
  cf_WriteFloat(outfile, texpage->tex_struct.b);

  cf_WriteByte(outfile, TEXPAGE_COMMAND_ALPHA);
  cf_WriteByte(outfile, 4);
  cf_WriteFloat(outfile, texpage->tex_struct.alpha);

  cf_WriteByte(outfile, TEXPAGE_COMMAND_SPEED);
  cf_WriteByte(outfile, 4);
  cf_WriteFloat(outfile, texpage->tex_struct.speed);

  cf_WriteByte(outfile, TEXPAGE_COMMAND_SLIDE_FLOAT);
  cf_WriteByte(outfile, 8);
  cf_WriteFloat(outfile, texpage->tex_struct.slide_u);
  cf_WriteFloat(outfile, texpage->tex_struct.slide_v);

  cf_WriteByte(outfile, TEXPAGE_COMMAND_REFLECT);
  cf_WriteByte(outfile, 4);
  cf_WriteFloat(outfile, texpage->tex_struct.reflectivity);

  cf_WriteByte(outfile, TEXPAGE_COMMAND_CORONA);
  cf_WriteByte(outfile, 1);
  cf_WriteByte(outfile, texpage->tex_struct.corona_type);

  cf_WriteByte(outfile, TEXPAGE_COMMAND_DAMAGE);
  cf_WriteByte(outfile, 4);
  cf_WriteInt(outfile, texpage->tex_struct.damage);

  cf_WriteByte(outfile, TEXPAGE_COMMAND_FLAGS); // write out flags field
  cf_WriteByte(outfile, 4);
  cf_WriteInt(outfile, texpage->tex_struct.flags);

  // Write out the procedural
  if (texpage->tex_struct.flags & TF_PROCEDURAL) {
    // Write out the palette in two halves
    cf_WriteByte(outfile, TEXPAGE_COMMAND_FIRST_PROC_PAL);
    cf_WriteByte(outfile, (uint8_t)255);
    for (i = 0; i < 255; i++) {
      uint16_t val = texpage->proc_palette[i];
      val >>= 8;

      cf_WriteByte(outfile, val);
    }

    cf_WriteByte(outfile, TEXPAGE_COMMAND_SECOND_PROC_PAL);
    cf_WriteByte(outfile, (uint8_t)255);
    for (i = 0; i < 255; i++) {
      uint16_t val = texpage->proc_palette[i];
      val &= 0xFF;

      cf_WriteByte(outfile, val);
    }

    cf_WriteByte(outfile, TEXPAGE_COMMAND_EXTRA_PROCEDURAL);
    cf_WriteByte(outfile, 3);
    cf_WriteByte(outfile, texpage->proc_heat);
    cf_WriteByte(outfile, texpage->proc_light);
    cf_WriteByte(outfile, texpage->proc_thickness);

    cf_WriteByte(outfile, TEXPAGE_COMMAND_EXTRA_PROCEDURAL2);
    cf_WriteByte(outfile, 4);
    cf_WriteFloat(outfile, texpage->proc_evaluation_time);

    // Write out static procedural
    for (i = 0; i < texpage->num_proc_elements; i++) {
      cf_WriteByte(outfile, TEXPAGE_COMMAND_PROCEDURAL);

      cf_WriteByte(outfile, 8);

      cf_WriteByte(outfile, texpage->proc_type[i]);
      cf_WriteByte(outfile, texpage->proc_frequency[i]);
      cf_WriteByte(outfile, texpage->proc_speed[i]);
      cf_WriteByte(outfile, texpage->proc_size[i]);

      cf_WriteByte(outfile, texpage->proc_x1[i]);
      cf_WriteByte(outfile, texpage->proc_y1[i]);

      cf_WriteByte(outfile, texpage->proc_x2[i]);
      cf_WriteByte(outfile, texpage->proc_y2[i]);
    }
  }

  cf_WriteByte(outfile, TEXPAGE_COMMAND_END); // we're all done
  cf_WriteByte(outfile, 0);
}

// Given an open file pointer and a texture handle, writes that texture page out
void mng_WriteNewTexturePage(CFILE *outfile, mngs_texture_page *texpage) {
  int i = 0;

  ASSERT(outfile != NULL);
  ASSERT(texpage != NULL);

  int offset = StartManagePage(outfile, PAGETYPE_TEXTURE);

  cf_WriteShort(outfile, TEXPAGE_VERSION);
  cf_WriteString(outfile, texpage->tex_struct.name);

  // Write out its bitmaps name
  cf_WriteString(outfile, texpage->bitmap_name);

  // Write out destroy bitmap name
  cf_WriteString(outfile, texpage->destroy_name);

  // Write out rgb lighting and alpha
  cf_WriteFloat(outfile, texpage->tex_struct.r);
  cf_WriteFloat(outfile, texpage->tex_struct.g);
  cf_WriteFloat(outfile, texpage->tex_struct.b);
  cf_WriteFloat(outfile, texpage->tex_struct.alpha);

  // Write out animation speed
  cf_WriteFloat(outfile, texpage->tex_struct.speed);

  // Write out sliding values
  cf_WriteFloat(outfile, texpage->tex_struct.slide_u);
  cf_WriteFloat(outfile, texpage->tex_struct.slide_v);

  // Write reflectivity
  cf_WriteFloat(outfile, texpage->tex_struct.reflectivity);

  // Write corona type
  cf_WriteByte(outfile, texpage->tex_struct.corona_type);

  // Write damage
  cf_WriteInt(outfile, texpage->tex_struct.damage);

  // Write flags
  cf_WriteInt(outfile, texpage->tex_struct.flags);

  // Write out the procedural
  if (texpage->tex_struct.flags & TF_PROCEDURAL) {
    // Write procedural palette
    for (i = 0; i < 255; i++) {
      uint16_t val = texpage->proc_palette[i];
      cf_WriteShort(outfile, val);
    }

    // Write procedural globals
    cf_WriteByte(outfile, texpage->proc_heat);
    cf_WriteByte(outfile, texpage->proc_light);
    cf_WriteByte(outfile, texpage->proc_thickness);
    cf_WriteFloat(outfile, texpage->proc_evaluation_time);

    cf_WriteFloat(outfile, texpage->osc_time);
    cf_WriteByte(outfile, texpage->osc_value);

    // Write out static procedurals
    cf_WriteShort(outfile, texpage->num_proc_elements);
    for (i = 0; i < texpage->num_proc_elements; i++) {
      cf_WriteByte(outfile, texpage->proc_type[i]);
      cf_WriteByte(outfile, texpage->proc_frequency[i]);
      cf_WriteByte(outfile, texpage->proc_speed[i]);
      cf_WriteByte(outfile, texpage->proc_size[i]);
      cf_WriteByte(outfile, texpage->proc_x1[i]);
      cf_WriteByte(outfile, texpage->proc_y1[i]);
      cf_WriteByte(outfile, texpage->proc_x2[i]);
      cf_WriteByte(outfile, texpage->proc_y2[i]);
    }
  }

  cf_WriteString(outfile, texpage->sound_name);
  cf_WriteFloat(outfile, texpage->tex_struct.sound_volume);

  EndManagePage(outfile, offset);
}

void mng_InitTexturePage(mngs_texture_page *texpage) {
  memset(texpage, 0, sizeof(mngs_texture_page));
  texpage->proc_thickness = 4;
  texpage->proc_heat = 200;
  texpage->proc_light = 1;
  texpage->num_proc_elements = 0;
  texpage->proc_evaluation_time = 0;
  texpage->osc_time = 0;
  texpage->osc_value = 8;

  texpage->tex_struct.alpha = 1.0;
  texpage->tex_struct.speed = 1.0;
  texpage->tex_struct.reflectivity = .5;
  texpage->tex_struct.corona_type = 0;
  texpage->tex_struct.slide_v = 0;
  texpage->tex_struct.slide_u = 0;
  texpage->tex_struct.bumpmap = -1;
  texpage->tex_struct.sound = -1;
  texpage->tex_struct.sound_volume = 1.0;

  strcpy(texpage->bitmap_name, "");
  strcpy(texpage->destroy_name, "");
  strcpy(texpage->sound_name, "");
}

// Reads a texture page from an open file.  Returns 0 on error.
int mng_ReadTexturePage(CFILE *infile, mngs_texture_page *texpage) {
  int done = 0;
  char command;
  uint8_t len;
  int i;
  int proc_index = 0;

  if (!Old_table_method)
    return mng_ReadNewTexturePage(infile, texpage);

  ASSERT(infile != NULL);
  mng_InitTexturePage(texpage);

  while (!done) {
    command = cf_ReadByte(infile);
    len = cf_ReadByte(infile);

    switch (command) {
    case TEXPAGE_COMMAND_END:
      done = 1;
      break;
    case TEXPAGE_COMMAND_FLAGS:
      texpage->tex_struct.flags = cf_ReadInt(infile);
      break;
    case TEXPAGE_COMMAND_LIGHTING:
      cf_ReadInt(infile); // Ignored
      break;
    case TEXPAGE_COMMAND_LIGHTING_FLOAT:
      texpage->tex_struct.r = cf_ReadFloat(infile);
      texpage->tex_struct.g = cf_ReadFloat(infile);
      texpage->tex_struct.b = cf_ReadFloat(infile);
      break;
    case TEXPAGE_COMMAND_DAMAGE:
      texpage->tex_struct.damage = cf_ReadInt(infile);
      break;
    case TEXPAGE_COMMAND_REFLECT:
      texpage->tex_struct.reflectivity = cf_ReadFloat(infile);
      break;
    case TEXPAGE_COMMAND_CORONA:
      texpage->tex_struct.corona_type = cf_ReadByte(infile);
      break;
    case TEXPAGE_COMMAND_ALPHA:
      texpage->tex_struct.alpha = cf_ReadFloat(infile);
      break;
    case TEXPAGE_COMMAND_SPEED:
      texpage->tex_struct.speed = cf_ReadFloat(infile);
      break;
    case TEXPAGE_COMMAND_SLIDE_FLOAT:
      texpage->tex_struct.slide_u = cf_ReadFloat(infile);
      texpage->tex_struct.slide_v = cf_ReadFloat(infile);
      break;
    case TEXPAGE_COMMAND_BITMAP_NAME: // the name of the texture's bitmap
      for (i = 0; i < BITMAP_NAME_LEN; i++)
        texpage->bitmap_name[i] = cf_ReadByte(infile);
      break;
    case TEXPAGE_COMMAND_DESTROY_NAME: // the name of the texture's bitmap
      for (i = 0; i < BITMAP_NAME_LEN; i++)
        texpage->destroy_name[i] = cf_ReadByte(infile);
      break;
    case TEXPAGE_COMMAND_NAME:
      for (i = 0; i < PAGENAME_LEN; i++)
        texpage->tex_struct.name[i] = cf_ReadByte(infile);
      break;
    case TEXPAGE_COMMAND_NULL_NAME:
      cf_ReadString(texpage->tex_struct.name, PAGENAME_LEN, infile);
      break;
    case TEXPAGE_COMMAND_BITMAP_NULL_NAME: // the name of the texture's bitmap
      cf_ReadString(texpage->bitmap_name, PAGENAME_LEN, infile);
      break;
    case TEXPAGE_COMMAND_DESTROY_NULL_NAME: // the name of the texture's bitmap
      cf_ReadString(texpage->destroy_name, PAGENAME_LEN, infile);
      break;
    case TEXPAGE_COMMAND_FIRST_PROC_PAL:
      for (i = 0; i < 255; i++) {
        uint16_t val = cf_ReadByte(infile);
        val <<= 8;
        texpage->proc_palette[i] &= 0xFF;
        texpage->proc_palette[i] |= val;
      }
      break;
    case TEXPAGE_COMMAND_SECOND_PROC_PAL:
      for (i = 0; i < 255; i++) {
        uint8_t val = cf_ReadByte(infile);
        texpage->proc_palette[i] &= 0xFF00;
        texpage->proc_palette[i] |= val;
      }
      break;
    case TEXPAGE_COMMAND_EXTRA_PROCEDURAL:
      texpage->proc_heat = cf_ReadByte(infile);
      texpage->proc_light = cf_ReadByte(infile);
      texpage->proc_thickness = cf_ReadByte(infile);
      break;
    case TEXPAGE_COMMAND_EXTRA_PROCEDURAL2:
      texpage->proc_evaluation_time = cf_ReadFloat(infile);
      break;
    case TEXPAGE_COMMAND_PROCEDURAL:
      texpage->proc_type[proc_index] = cf_ReadByte(infile);
      texpage->proc_frequency[proc_index] = cf_ReadByte(infile);
      texpage->proc_speed[proc_index] = cf_ReadByte(infile);
      texpage->proc_size[proc_index] = cf_ReadByte(infile);
      texpage->proc_x1[proc_index] = cf_ReadByte(infile);
      texpage->proc_y1[proc_index] = cf_ReadByte(infile);

      texpage->proc_x2[proc_index] = cf_ReadByte(infile);
      texpage->proc_y2[proc_index] = cf_ReadByte(infile);

      proc_index++;
      break;
    default:
      for (i = 0; i < len; i++)
        cf_ReadByte(infile);
      break;
    }
  }

  // Jason hack
  if (texpage->tex_struct.alpha < .9999)
    texpage->tex_struct.flags |= TF_ALPHA;
  else
    texpage->tex_struct.flags &= ~TF_ALPHA;

  texpage->num_proc_elements = proc_index;

  if (texpage->num_proc_elements == 0)
    texpage->tex_struct.flags &= ~TF_PROCEDURAL;

  if (!strnicmp(texpage->destroy_name, "INVALID", 7))
    strcpy(texpage->destroy_name, "");

  texpage->tex_struct.used = 1;

  return 1; // successfully read
}

// Reads a texture page from an open file.  Returns 0 on error.
int mng_ReadNewTexturePage(CFILE *infile, mngs_texture_page *texpage) {
  int i;

  ASSERT(infile != NULL);
  mng_InitTexturePage(texpage);

  int version = cf_ReadShort(infile);

  cf_ReadString(texpage->tex_struct.name, PAGENAME_LEN, infile);
  cf_ReadString(texpage->bitmap_name, PAGENAME_LEN, infile);
  cf_ReadString(texpage->destroy_name, PAGENAME_LEN, infile);

  texpage->tex_struct.r = cf_ReadFloat(infile);
  texpage->tex_struct.g = cf_ReadFloat(infile);
  texpage->tex_struct.b = cf_ReadFloat(infile);
  texpage->tex_struct.alpha = cf_ReadFloat(infile);

  texpage->tex_struct.speed = cf_ReadFloat(infile);

  texpage->tex_struct.slide_u = cf_ReadFloat(infile);
  texpage->tex_struct.slide_v = cf_ReadFloat(infile);
  texpage->tex_struct.reflectivity = cf_ReadFloat(infile);

  texpage->tex_struct.corona_type = cf_ReadByte(infile);
  texpage->tex_struct.damage = cf_ReadInt(infile);
  texpage->tex_struct.flags = cf_ReadInt(infile);

  if (texpage->tex_struct.flags & TF_PROCEDURAL) {
    for (i = 0; i < 255; i++) {
      uint16_t val = cf_ReadShort(infile);
      texpage->proc_palette[i] = val;
    }

    texpage->proc_heat = cf_ReadByte(infile);
    texpage->proc_light = cf_ReadByte(infile);
    texpage->proc_thickness = cf_ReadByte(infile);
    texpage->proc_evaluation_time = cf_ReadFloat(infile);

    if (version >= 6) {
      texpage->osc_time = cf_ReadFloat(infile);
      texpage->osc_value = cf_ReadByte(infile);
    }

    texpage->num_proc_elements = cf_ReadShort(infile);

    if (texpage->num_proc_elements > MAX_PROC_ELEMENTS) {
      mprintf(0, "Warning!  Too many procedural elements!\n");
      Int3();
    }

    for (i = 0; i < texpage->num_proc_elements; i++) {
      texpage->proc_type[i] = cf_ReadByte(infile);
      texpage->proc_frequency[i] = cf_ReadByte(infile);
      texpage->proc_speed[i] = cf_ReadByte(infile);
      texpage->proc_size[i] = cf_ReadByte(infile);
      texpage->proc_x1[i] = cf_ReadByte(infile);
      texpage->proc_y1[i] = cf_ReadByte(infile);

      texpage->proc_x2[i] = cf_ReadByte(infile);
      texpage->proc_y2[i] = cf_ReadByte(infile);
    }
  }

  if (texpage->tex_struct.flags & TF_PROCEDURAL) {
    if (texpage->num_proc_elements == 0)
      texpage->tex_struct.flags &= ~TF_PROCEDURAL;
  }

  if (!strnicmp(texpage->destroy_name, "INVALID", 7))
    strcpy(texpage->destroy_name, "");

  if (version >= 5) {

    if (version < 7) {
      // Kill buggy version of sound resolving code
      texpage->tex_struct.sound = cf_ReadInt(infile);
      texpage->tex_struct.sound = -1;
      strcpy(texpage->sound_name, "");
    } else
      cf_ReadString(texpage->sound_name, PAGENAME_LEN, infile);

    texpage->tex_struct.sound_volume = cf_ReadFloat(infile);
  } else {
    texpage->tex_struct.sound = -1;
    texpage->tex_struct.sound_volume = 1.0;
  }

  texpage->tex_struct.used = 1;

  return 1; // successfully read
}

// Given some texture names, finds them in the table file and deletes them
// If local is 1, deletes from the local table file
int mng_DeleteTexPageSeries(char *names[], int num_textures, int local) {
  CFILE *infile, *outfile;
  uint8_t pagetype, replaced = 0;
  int done = 0;
  int deleted = 0;
  memset(&texpage1, 0, sizeof(mngs_texture_page));

  if (local)
    infile = cfopen(LocalTableFilename, "rb");
  else
    infile = cfopen(TableFilename, "rb");

  if (!infile) {
    mprintf(0, "Couldn't open table file to delete texture!\n");
    Int3();
    return 0;
  }

  if (local)
    outfile = cfopen(LocalTempTableFilename, "wb");
  else
    outfile = cfopen(TempTableFilename, "wb");

  if (!outfile) {
    mprintf(0, "Couldn't open temp table file to delete texture!\n");
    cfclose(infile);
    Int3();
    return 0;
  }

  while (!done) {
    if (cfeof(infile)) {
      done = 1;
      continue;
    }
    pagetype = cf_ReadByte(infile);
    int len = cf_ReadInt(infile);

    // If not a texture page, just read it in and write it right back out
    if (pagetype != PAGETYPE_TEXTURE) {
      mng_ReadWriteDummyPage(infile, outfile, pagetype);
      continue;
    }

    mng_ReadNewTexturePage(infile, &texpage1);

    int found = -1;
    for (int i = 0; i < num_textures && found == -1; i++) {
      if (!stricmp(names[i], texpage1.tex_struct.name)) {
        found = i;
      }
    }

    if (found == -1) // Not found
    {
      mng_WriteNewTexturePage(outfile, &texpage1);
    } else
      mprintf(0, "Deleting %s (%s).\n", names[found], local ? "locally" : "on network");
  }

  cfclose(infile);
  cfclose(outfile);

  // Now, remove our table file and rename the temp file to be the table file

  if (local) {
    if (!SwitcherooFiles(LocalTableFilename, LocalTempTableFilename))
      return 0;
  } else {
    if (!SwitcherooFiles(TableFilename, TempTableFilename))
      return 0;
  }

  return 1; // successful!
}

// Reads in the texpage named "name" into texpage struct
// Returns 0 on error or couldn't find, else 1 if all is good
int mng_FindSpecificTexPage(char *name, mngs_texture_page *texpage, int offset) {
  CFILE *infile;
  uint8_t pagetype;
  int done = 0, found = 0;
  int first_try = 1;
  std::filesystem::path tablename;

  if (Loading_locals) {
    infile = cfopen(LocalTableFilename, "rb");
  } else if (Loading_addon_table != -1) {
    infile = cfopen(AddOnDataTables[Loading_addon_table].AddOnTableFilename, "rb");
  } else {
    if (Network_up && Starting_editor) {
      int farg = FindArg("-filter");

      if (farg)
        tablename = GameArgs[farg + 1];
      else
        tablename = LocalTableDir / NET_TABLE;

      infile = cfopen(tablename, "rb");
    } else {
      infile = NULL;
      if (TablefileNameOverride) {
        infile = cfopen(TablefileNameOverride, "rb");
      }

      if (!infile)
        infile = cfopen(TableFilename, "rb");
    }
  }

  if (!infile) {
    mprintf(0, "Couldn't open table file to find texture!\n");
    Int3();
    return 0;
  }

try_again:;
  if (offset)
    cfseek(infile, offset, SEEK_SET);

  while (!done) {
    if (cfeof(infile)) {
      done = 1;
      continue;
    }
    pagetype = cf_ReadByte(infile);
    int len = cf_ReadInt(infile);

    // If not a texture page, just read it in and ignore it
    if (pagetype != PAGETYPE_TEXTURE) {
      cfseek(infile, len - 4, SEEK_CUR);
      continue;
    }

    mng_ReadNewTexturePage(infile, texpage);

    if (!stricmp(name, texpage->tex_struct.name)) {
      // This is the page we want
      found = 1;
      done = 1;
    }
  }

  cfclose(infile);

  if (!found && first_try) {
    done = first_try = 0;
    infile = cfopen("extra.gam", "rb");
    if (infile)
      goto try_again;
  }

  return found; // successful!
}

// Given a texture page, allocs a texture and calls AssignTexPageToTexture to actually
// load bitmaps and values. Rturns texture handle on success, -1 if fail
int mng_SetAndLoadTexture(mngs_texture_page *texpage, CFILE *infile) {
  int n;

  n = AllocTexture();
  if (n < 0)
    return -1;
  if (!mng_AssignTexPageToTexture(texpage, n, infile))
    return -1;

  return n;
}

// extern char Texture256Names[][80];
// extern int Num_256s;
// Given a texpage and a texture handle, attempts to make texture n correspond to
// to the texpage.
// Returns 1 on success, 0 otherwise
int mng_AssignTexPageToTexture(mngs_texture_page *texpage, int n, CFILE *infile) {
  texture *tex = &GameTextures[n];
  int bm_handle;

  // copy our values
  memcpy(tex, &texpage->tex_struct, sizeof(texture));

// Check to see if this image differs from the one on the net
// If so, make a local copy
// If this is a release, don't do any of this stuff
#ifndef RELEASE
  if (Network_up) {
    UpdatePrimitive(LocalManageGraphicsDir / texpage->bitmap_name, ManageGraphicsDir / texpage->bitmap_name,
                    texpage->bitmap_name, PAGETYPE_TEXTURE, tex->name);
  }
#endif

  // Try and load our textures bitmaps from the disk
  uint8_t pageable;
  uint8_t mipped = 1;

  if (Network_up)
    pageable = 0;
  else
    pageable = 1;

  pageable = 1;

  /*int done=0;
  for (int i=0;i<Num_256s && !done;i++)
  {
          if (!stricmp (Texture256Names[i],tex->name))
          {
                  tex->flags&=~(TF_TEXTURE_64|TF_TEXTURE_32);
                  tex->flags|=TF_TEXTURE_256;
                  mprintf(0,"Found 256...%s\n",tex->name);
                  int len=strlen (texpage->bitmap_name);
                  texpage->bitmap_name[len-3]='t';
                  texpage->bitmap_name[len-2]='g';
                  texpage->bitmap_name[len-1]='a';

                  done=1;
          }
  }*/

  if (tex->flags & TF_TEXTURE_64) {
    bm_handle = LoadTextureImage(texpage->bitmap_name, NULL, SMALL_TEXTURE, mipped, pageable);
  } else if (tex->flags & TF_TEXTURE_32) {
    bm_handle = LoadTextureImage(texpage->bitmap_name, NULL, TINY_TEXTURE, mipped, pageable);
  } else if (tex->flags & TF_TEXTURE_256) {
    mipped = 0;
    bm_handle = LoadTextureImage(texpage->bitmap_name, NULL, HUGE_TEXTURE, mipped, pageable);
  } else
    bm_handle = LoadTextureImage(texpage->bitmap_name, NULL, NORMAL_TEXTURE, mipped, pageable);

  if (bm_handle < 0) {
    mprintf(0, "Couldn't load bitmap '%s' in AssignTexPage...\n", texpage->bitmap_name);
    tex->bm_handle = 0;
    return 0;
  } else
    tex->bm_handle = bm_handle;

  // Load the destroyed texture
  if (tex->flags & TF_DESTROYABLE) {
    // Are destroyed and non-destroyed the same?
    if (!(stricmp(texpage->destroy_name, tex->name))) {
      tex->flags &= ~TF_DESTROYABLE;
      tex->destroy_handle = -1;
    } else {

      int destroy_handle = mng_GetGuaranteedTexturePage(texpage->destroy_name, infile);
      if (destroy_handle < 0)
        tex->destroy_handle = 0;
      else
        tex->destroy_handle = destroy_handle;
    }
  }

  // Get sound if needed
  if (stricmp("", texpage->sound_name))
    tex->sound = mng_GetGuaranteedSoundPage(texpage->sound_name, infile);
  else
    tex->sound = -1;

  // Set lighting flag
  if (tex->r > 0 || tex->g > 0 || tex->b > 0)
    tex->flags |= TF_LIGHT;
  else
    tex->flags &= ~TF_LIGHT;

  // Set procedural if there is one
  if (tex->flags & TF_PROCEDURAL) {
    if (tex->procedural != NULL)
      FreeProceduralForTexture(n);

    if (texpage->num_proc_elements == 0) {
      tex->flags &= ~TF_PROCEDURAL;

    } else {
      AllocateProceduralForTexture(n);
      AllocateStaticProceduralsForTexture(n, texpage->num_proc_elements);
      GameTextures[n].procedural->num_static_elements = texpage->num_proc_elements;
      GameTextures[n].procedural->heat = texpage->proc_heat;
      GameTextures[n].procedural->light = texpage->proc_light;
      GameTextures[n].procedural->thickness = texpage->proc_thickness;
      GameTextures[n].procedural->evaluation_time = texpage->proc_evaluation_time;
      GameTextures[n].procedural->osc_time = texpage->osc_time;
      GameTextures[n].procedural->osc_value = texpage->osc_value;

      // Last 2 colors are the same
      texpage->proc_palette[255] = texpage->proc_palette[254];

      memcpy(GameTextures[n].procedural->palette, texpage->proc_palette, 256 * 2);

      for (int i = 0; i < texpage->num_proc_elements; i++) {
        static_proc_element *proc = &GameTextures[n].procedural->static_proc_elements[i];
        proc->type = texpage->proc_type[i];
        proc->frequency = texpage->proc_frequency[i];
        proc->speed = texpage->proc_speed[i];
        proc->size = texpage->proc_size[i];
        proc->x1 = texpage->proc_x1[i];
        proc->y1 = texpage->proc_y1[i];
        proc->x2 = texpage->proc_x2[i];
        proc->y2 = texpage->proc_y2[i];
      }
    }
  }
  return 1;
}

// Copies values from a texture into a texture_page
void mng_AssignTextureToTexPage(int n, mngs_texture_page *texpage) {
  texture *tex = &GameTextures[n];

  memcpy(&texpage->tex_struct, tex, sizeof(texture));

  if (tex->bm_handle != -1) {
    if (tex->flags & TF_ANIMATED)
      strcpy(texpage->bitmap_name, GameVClips[tex->bm_handle].name);
    else
      strcpy(texpage->bitmap_name, GameBitmaps[tex->bm_handle].name);
  } else
    strcpy(texpage->bitmap_name, "");

  if (tex->destroy_handle != -1)
    strcpy(texpage->destroy_name, GameTextures[tex->destroy_handle].name);
  else
    strcpy(texpage->destroy_name, "");

  if (texpage->tex_struct.sound != -1)
    strcpy(texpage->sound_name, Sounds[texpage->tex_struct.sound].name);
  else
    strcpy(texpage->sound_name, "");

  // assign procedural if there is one
  if (tex->flags & TF_PROCEDURAL) {
    memcpy(texpage->proc_palette, tex->procedural->palette, 256 * 2);
    texpage->num_proc_elements = tex->procedural->num_static_elements;
    texpage->proc_heat = tex->procedural->heat;
    texpage->proc_light = tex->procedural->light;
    texpage->proc_thickness = tex->procedural->thickness;
    texpage->proc_evaluation_time = tex->procedural->evaluation_time;
    texpage->osc_time = tex->procedural->osc_time;
    texpage->osc_value = tex->procedural->osc_value;

    for (int i = 0; i < tex->procedural->num_static_elements; i++) {
      texpage->proc_type[i] = tex->procedural->static_proc_elements[i].type;
      texpage->proc_frequency[i] = tex->procedural->static_proc_elements[i].frequency;
      texpage->proc_speed[i] = tex->procedural->static_proc_elements[i].speed;
      texpage->proc_size[i] = tex->procedural->static_proc_elements[i].size;

      texpage->proc_x1[i] = tex->procedural->static_proc_elements[i].x1;
      texpage->proc_y1[i] = tex->procedural->static_proc_elements[i].y1;
      texpage->proc_x2[i] = tex->procedural->static_proc_elements[i].x2;
      texpage->proc_y2[i] = tex->procedural->static_proc_elements[i].y2;
    }
  }
}

// Loads in a texture page
void mng_LoadNetTexturePage(CFILE *infile, bool overlay) {
  memset(&texpage1, 0, sizeof(mngs_texture_page));

  if (mng_ReadNewTexturePage(infile, &texpage1)) {
    int n;
    n = FindTextureName(texpage1.tex_struct.name);
    if (n != -1) {
      if (overlay) {
        mprintf(0, "OVERLAYING TEXTURE %s\n", texpage1.tex_struct.name);
        mng_FreePagetypePrimitives(PAGETYPE_TEXTURE, texpage1.tex_struct.name, 0);
        mng_AssignTexPageToTexture(&texpage1, n);
      }
      return;
    }

    int ret = mng_SetAndLoadTexture(&texpage1, infile);
    ASSERT(ret >= 0);
  } else
    mprintf(0, "Could not load texpage named %s!\n", texpage1.tex_struct.name);
}

// Loads in a texture page from a file, superseding any texture with that name
// already in memory
void mng_LoadLocalTexturePage(CFILE *infile) {
  int ok = 0;
  memset(&texpage1, 0, sizeof(mngs_texture_page));

  if (mng_ReadNewTexturePage(infile, &texpage1)) {
    int i = FindTextureName(texpage1.tex_struct.name);
    if (i != -1) {
      // Make sure we really have this page checked out
      mngs_Pagelock pl;
      // int locked;

      strcpy(pl.name, texpage1.tex_struct.name);
      pl.pagetype = PAGETYPE_TEXTURE;

      /*if (Network_up)
      {
              locked=mng_CheckIfPageOwned(&pl,TableUser);
              if (locked!=1)
                      Int3(); // Your local vs net copies of the lock file do not match
      }*/

      ok = 1;
      bool need_to_load_page = true;

      if (Loading_addon_table != -1) {
        AddOnTablefile *addon;
        int tidx;

        // see if we really need to load this page
        // check to see if we already have loaded this page (because it was
        // a dependancy of another)
        addon = &AddOnDataTables[Loading_addon_table];
        for (tidx = 0; tidx < addon->Num_addon_tracklocks; tidx++) {
          if (addon->Addon_tracklocks[tidx].pagetype == PAGETYPE_TEXTURE &&
              !stricmp(addon->Addon_tracklocks[tidx].name, texpage1.tex_struct.name)) {
            // found it!!
            mprintf(0, "TexturePage: %s previously loaded\n", texpage1.tex_struct.name);
            need_to_load_page = false;
            break;
          }
        }
      }

      if (need_to_load_page) {
        mng_FreePagetypePrimitives(PAGETYPE_TEXTURE, texpage1.tex_struct.name, 0);
        mng_AssignTexPageToTexture(&texpage1, i);

        // For addon data
        if (Loading_addon_table != -1) {
          // this is an overlay of some sort..see which we are overlaying
          int overlay = 1;
          int addidx, tidx;
          bool found = false;
          for (addidx = Num_addon_tables - 1; addidx >= 0; addidx--) {
            if (addidx == Loading_addon_table)
              continue;
            AddOnTablefile *addon = &AddOnDataTables[addidx];

            // look for the page in this table file
            for (tidx = 0; tidx < addon->Num_addon_tracklocks; tidx++) {
              if (addon->Addon_tracklocks[tidx].pagetype == PAGETYPE_TEXTURE &&
                  !stricmp(addon->Addon_tracklocks[tidx].name, texpage1.tex_struct.name)) {
                // found it!!
                found = true;
                overlay = addidx + 2;
                break;
              }
            }

            if (found)
              break;
          }

          mng_PushAddonPage(PAGETYPE_TEXTURE, texpage1.tex_struct.name, overlay);
        }
      }
    } else {
      // This is a local texture that has never been checked in
      if ((i = mng_SetAndLoadTexture(&texpage1, infile)) < 0)
        ok = 0;
      else
        ok = 1;

      // For addon data
      if (ok && Loading_addon_table != -1)
        mng_PushAddonPage(PAGETYPE_TEXTURE, texpage1.tex_struct.name, 0);
    }

    // ASSERT (ok==1);	// There was problem loading a page!
    if (ok != 1)
      DataError("Cannot load texture <%s>, bitmap name <%s>\n", texpage1.tex_struct.name, texpage1.bitmap_name);

    if (Loading_addon_table == -1)
      mng_AllocTrackLock(texpage1.tex_struct.name, PAGETYPE_TEXTURE);

  } else
    mprintf(0, "Could not load texpage named %s!\n", texpage1.tex_struct.name);
}

#include "mem.h"

// First searches through the texture index to see if the texture is already
// loaded.  If not, searches in the table file and loads it.
// Returns index of texture found, -1 if not
int mng_GetGuaranteedTexturePage(char *name, CFILE *infile) {
  int i;

  // See if its in memory
  i = FindTextureName(name);
  if (i != -1)
    return i;

  mngs_texture_page *texpage = (mngs_texture_page *)mem_malloc(sizeof(*texpage));

  // Not in memory.  Load it from the table file.  Start searching from the
  // current spot in the open table file
  int ret = mng_FindSpecificTexPage(name, texpage, infile ? infile->position : 0);
  if (!ret)
    return -1;

  // We've found it in the table file, now load it.
  ret = mng_SetAndLoadTexture(texpage, infile);
  // ASSERT (ret>=0);
  if (ret < 0)
    DataError("Cannot load texture <%s>, bitmap name <%s>\n", texpage->tex_struct.name, texpage->bitmap_name);

  if (Loading_addon_table != -1) {
    // we're loading addon table pages, this will not overlay anything
    mng_PushAddonPage(PAGETYPE_TEXTURE, texpage->tex_struct.name, 0);
  }
  mem_free(texpage);

  return ret;
}
