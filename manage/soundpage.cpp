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

 * $Logfile: /DescentIII/Main/manage/soundpage.cpp $
 * $Revision: 23 $
 * $Date: 10/08/01 4:20p $
 * $Author: Matt $
 *
 *
 * $Log: /DescentIII/Main/manage/soundpage.cpp $
 *
 * 23    10/08/01 4:20p Matt
 * Added system to check for errors when reading in add-on data.
 *
 * 21    10/26/99 3:31p Jeff
 * handle extra.gam addon tablefile
 *
 * 20    9/18/99 8:49p Jeff
 * fixed bug with addon pages that have dependencies on other pages in the
 * addon tablefile
 *
 * 19    8/11/99 5:32p Jeff
 * changes to fix addon tablefile support so it works correctly
 *
 * 18    7/28/99 2:24p Kevin
 * Macintosh Fixes!
 *
 * 17    4/19/99 7:37p 3dsmax
 * more demo explosion fixes
 *
 * 16    4/19/99 5:42p Jason
 * fixes for explosions in the demo
 *
 * 15    4/14/99 1:34a Jeff
 * fixed case mismatched #includes
 *
 * 14    3/04/99 4:47p Jason
 * temp fix (ie BAD HACK) for OEM table file woes
 *
 * 13    1/13/99 7:05a Jeff
 * put #ifdef around #include <windows.h>
 *
 * 12    12/29/98 4:30p Jason
 * added add-on data functionality
 *
 * 11    11/06/98 12:35p Jason
 * more speedups for manage system
 *
 * 10    11/05/98 7:55p Jason
 * changes for new manage system
 *
 * 9     11/02/98 6:02p Jason
 * made yes network updates much faster
 *
 * 8     10/19/98 11:57a Chris
 * Update the sound system to use the import volume
 *
 * 7     10/09/98 2:27p Jason
 * reorganized table file system
 *
 * 6     10/08/98 10:03p Jason
 * more filtered table file stuff
 *
 * 5     8/24/98 2:37p Jason
 * made table file more efficient with regards to invalid names
 *
 * 4     6/12/98 1:06p Jason
 * added smart loading from local table file
 *
 * 3     2/23/98 1:22p Jason
 * made FindSpecific* read from the local drive, not the net drive - when
 * starting the editor
 *
 * 2     1/15/98 6:22p Jason
 * added safety checks so the network won't copy over a primitive you have
 * held locally
 *
 * 7     5/08/97 12:41p Jason
 * made manage system work with device dependant path names
 *
 * 6     4/29/97 7:26a Chris
 * Improved the sound code.  It is healthy.
 *
 * 5     4/25/97 6:16p Jason
 * added switcheroo function
 *
 * 4     4/22/97 3:24p Jason
 * added more code for recursive page loading
 *
 * 3     4/08/97 2:25a Chris
 * Fixed a problem with uninitialized data.  In addition it
 * fixed a problem with the .used flag that would happen
 * 1 out of 2^(sizeof(used_flag)) times (it would be zero
 * when it was supposed to be non-zero)
 *
 * 2     4/01/97 2:13p Jason
 * changes for sound page functionality
 *
 * 1     4/01/97 1:48p Jason
 *
 *
 * $NoKeywords: $
 */

#include <cstring>
#include <filesystem>

#include "cfile.h"
#include "manage.h"
#include "soundpage.h"
#include "mono.h"
#include "pserror.h"
#include "soundload.h"
#include "ddio.h"
#include "args.h"

// soundpage commands that are read/written
// A command is followed by a byte count describing how many bytes
// are in the data for the command
#define SOUNDPAGE_COMMAND_NAME 1
#define SOUNDPAGE_COMMAND_END 2
#define SOUNDPAGE_COMMAND_RAW_NAME 3
#define SOUNDPAGE_COMMAND_VERSION 4
#define SOUNDPAGE_COMMAND_FLAGS 5
#define SOUNDPAGE_COMMAND_INNER_CONE_ANGLE 6
#define SOUNDPAGE_COMMAND_OUTER_CONE_ANGLE 7
#define SOUNDPAGE_COMMAND_OUTER_CONE_VOLUME 8
#define SOUNDPAGE_COMMAND_MAX_DIST 9
#define SOUNDPAGE_COMMAND_MIN_DIST 10
#define SOUNDPAGE_COMMAND_LOOP_START 11
#define SOUNDPAGE_COMMAND_LOOP_END 12
#define SOUNDPAGE_COMMAND_IMPORT_VOLUME 13
#define SOUNDPAGE_VERSION 1

extern char *TablefileNameOverride;

// Given an open file pointer and a sound_page struct, writes that sound page out
void mng_WriteSoundPage(CFILE *outfile, mngs_sound_page *soundpage) {
  int i;
  ASSERT(outfile != NULL);
  ASSERT(soundpage != NULL);

  cf_WriteByte(outfile, PAGETYPE_SOUND);

  cf_WriteByte(outfile, SOUNDPAGE_COMMAND_NAME); // write out sound name
  cf_WriteByte(outfile, PAGENAME_LEN);
  for (i = 0; i < PAGENAME_LEN; i++)
    cf_WriteByte(outfile, soundpage->sound_struct.name[i]);
  // Write out its rawfile name
  cf_WriteByte(outfile, SOUNDPAGE_COMMAND_RAW_NAME); // get ready to write out name
  cf_WriteByte(outfile, PAGENAME_LEN);
  for (i = 0; i < PAGENAME_LEN; i++)
    cf_WriteByte(outfile, soundpage->raw_name[i]);

  cf_WriteByte(outfile, SOUNDPAGE_COMMAND_FLAGS);
  cf_WriteByte(outfile, 4);
  cf_WriteInt(outfile, soundpage->sound_struct.flags);
  cf_WriteByte(outfile, SOUNDPAGE_COMMAND_LOOP_START);
  cf_WriteByte(outfile, 4);
  cf_WriteInt(outfile, soundpage->sound_struct.loop_start);
  cf_WriteByte(outfile, SOUNDPAGE_COMMAND_LOOP_END);
  cf_WriteByte(outfile, 4);
  cf_WriteInt(outfile, soundpage->sound_struct.loop_end);
  cf_WriteByte(outfile, SOUNDPAGE_COMMAND_OUTER_CONE_VOLUME);
  cf_WriteByte(outfile, 4);
  cf_WriteFloat(outfile, soundpage->sound_struct.outer_cone_volume);
  cf_WriteByte(outfile, SOUNDPAGE_COMMAND_INNER_CONE_ANGLE);
  cf_WriteByte(outfile, 4);
  cf_WriteInt(outfile, soundpage->sound_struct.inner_cone_angle);
  cf_WriteByte(outfile, SOUNDPAGE_COMMAND_OUTER_CONE_ANGLE);
  cf_WriteByte(outfile, 4);
  cf_WriteInt(outfile, soundpage->sound_struct.outer_cone_angle);
  cf_WriteByte(outfile, SOUNDPAGE_COMMAND_MAX_DIST);
  cf_WriteByte(outfile, 4);
  cf_WriteFloat(outfile, soundpage->sound_struct.max_distance);
  cf_WriteByte(outfile, SOUNDPAGE_COMMAND_MIN_DIST);
  cf_WriteByte(outfile, 4);
  cf_WriteFloat(outfile, soundpage->sound_struct.min_distance);
  cf_WriteByte(outfile, SOUNDPAGE_COMMAND_IMPORT_VOLUME);
  cf_WriteByte(outfile, 4);
  cf_WriteFloat(outfile, soundpage->sound_struct.import_volume);
  cf_WriteByte(outfile, SOUNDPAGE_COMMAND_END); // we're all done
  cf_WriteByte(outfile, 0);
}
// Given an open file pointer and a sound_page struct, writes that sound page out
void mng_WriteNewSoundPage(CFILE *outfile, mngs_sound_page *soundpage) {
  ASSERT(outfile != NULL);
  ASSERT(soundpage != NULL);

  int offset = StartManagePage(outfile, PAGETYPE_SOUND);
  cf_WriteShort(outfile, SOUNDPAGE_VERSION);
  // Write out name,rawfile name
  cf_WriteString(outfile, soundpage->sound_struct.name);
  cf_WriteString(outfile, soundpage->raw_name);
  cf_WriteInt(outfile, soundpage->sound_struct.flags);
  cf_WriteInt(outfile, soundpage->sound_struct.loop_start);
  cf_WriteInt(outfile, soundpage->sound_struct.loop_end);
  cf_WriteFloat(outfile, soundpage->sound_struct.outer_cone_volume);
  cf_WriteInt(outfile, soundpage->sound_struct.inner_cone_angle);
  cf_WriteInt(outfile, soundpage->sound_struct.outer_cone_angle);
  cf_WriteFloat(outfile, soundpage->sound_struct.max_distance);
  cf_WriteFloat(outfile, soundpage->sound_struct.min_distance);
  cf_WriteFloat(outfile, soundpage->sound_struct.import_volume);
  EndManagePage(outfile, offset);
}
// Reads a sound page from an open file.  Returns 0 on error.
int mng_ReadNewSoundPage(CFILE *infile, mngs_sound_page *soundpage) {
  ASSERT(infile != NULL);
  int version = cf_ReadShort(infile);
  // read in name,rawfile name
  cf_ReadString(soundpage->sound_struct.name, PAGENAME_LEN, infile);
  cf_ReadString(soundpage->raw_name, PAGENAME_LEN, infile);
  soundpage->sound_struct.flags = cf_ReadInt(infile);

  soundpage->sound_struct.loop_start = cf_ReadInt(infile);
  soundpage->sound_struct.loop_end = cf_ReadInt(infile);
  soundpage->sound_struct.outer_cone_volume = cf_ReadFloat(infile);
  soundpage->sound_struct.inner_cone_angle = cf_ReadInt(infile);
  soundpage->sound_struct.outer_cone_angle = cf_ReadInt(infile);
  soundpage->sound_struct.max_distance = cf_ReadFloat(infile);
  soundpage->sound_struct.min_distance = cf_ReadFloat(infile);
  soundpage->sound_struct.import_volume = cf_ReadFloat(infile);
#ifdef DEMO
  if (!stricmp("DefaultBuildingExplode", soundpage->sound_struct.name)) {
    soundpage->sound_struct.import_volume = 1.0;
    soundpage->sound_struct.flags &= ~(SPF_OBJ_UPDATE | SPF_FIXED_FREQ);
  }
  if (!stricmp("DefaultRobotExplode1", soundpage->sound_struct.name)) {
    soundpage->sound_struct.import_volume = 1.0;
    soundpage->sound_struct.flags &= ~(SPF_OBJ_UPDATE | SPF_FIXED_FREQ);
  }
  if (!stricmp("DefaultRobotExplode2", soundpage->sound_struct.name)) {
    soundpage->sound_struct.import_volume = 1.0;
    soundpage->sound_struct.flags &= ~(SPF_OBJ_UPDATE | SPF_FIXED_FREQ);
  }
#endif
  // This is a valid new page
  soundpage->sound_struct.used = 1;
  return 1; // successfully read
}
// Reads a sound page from an open file.  Returns 0 on error.
int mng_ReadSoundPage(CFILE *infile, mngs_sound_page *soundpage) {
  int done = 0;
  char command;
  uint8_t len;
  int i;
  if (!Old_table_method)
    return mng_ReadNewSoundPage(infile, soundpage);
  ASSERT(infile != NULL);
  soundpage->sound_struct.import_volume = 1.0f;
  while (!done) {
    // Read in command byte then read in the length of that commands data

    command = cf_ReadByte(infile);
    len = cf_ReadByte(infile);
    switch (command) {
    case SOUNDPAGE_COMMAND_END:
      done = 1;
      break;
    case SOUNDPAGE_COMMAND_RAW_NAME: // the name of the sound sample
      for (i = 0; i < PAGENAME_LEN; i++)
        soundpage->raw_name[i] = cf_ReadByte(infile);
      break;
    case SOUNDPAGE_COMMAND_NAME:
      for (i = 0; i < PAGENAME_LEN; i++)
        soundpage->sound_struct.name[i] = cf_ReadByte(infile);
      break;
    case SOUNDPAGE_COMMAND_FLAGS:
      soundpage->sound_struct.flags = cf_ReadInt(infile);
      break;
    case SOUNDPAGE_COMMAND_LOOP_START:
      soundpage->sound_struct.loop_start = cf_ReadInt(infile);
      break;
    case SOUNDPAGE_COMMAND_LOOP_END:
      soundpage->sound_struct.loop_end = cf_ReadInt(infile);
      break;
    case SOUNDPAGE_COMMAND_OUTER_CONE_VOLUME:
      soundpage->sound_struct.outer_cone_volume = cf_ReadFloat(infile);
      break;
    case SOUNDPAGE_COMMAND_INNER_CONE_ANGLE:
      soundpage->sound_struct.inner_cone_angle = cf_ReadInt(infile);
      break;
    case SOUNDPAGE_COMMAND_OUTER_CONE_ANGLE:
      soundpage->sound_struct.outer_cone_angle = cf_ReadInt(infile);
      break;
    case SOUNDPAGE_COMMAND_MAX_DIST:
      soundpage->sound_struct.max_distance = cf_ReadFloat(infile);
      break;
    case SOUNDPAGE_COMMAND_MIN_DIST:
      soundpage->sound_struct.min_distance = cf_ReadFloat(infile);
      break;
    case SOUNDPAGE_COMMAND_IMPORT_VOLUME:
      soundpage->sound_struct.import_volume = cf_ReadFloat(infile);
      break;
    default:
      // Ignore the ones we don't know
      for (i = 0; i < len; i++)
        cf_ReadByte(infile);
      break;
    }
  }
  // This is a valid new page
  soundpage->sound_struct.used = 1;
  return 1; // successfully read
}
// Reads in the sound named "name" into soundpage struct
// Returns 0 on error or couldn't find, else 1 if all is good
int mng_FindSpecificSoundPage(char *name, mngs_sound_page *soundpage, int offset) {
  CFILE *infile;
  uint8_t pagetype;
  int done = 0, found = 0;
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
    mprintf(0, "Couldn't open table file to find sound!\n");
    Int3();
    return 0;
  }
  if (offset)
    cfseek(infile, offset, SEEK_SET);

  // Read in the entire page file until we find the page we want
  while (!done) {
    if (cfeof(infile)) {
      done = 1;
      continue;
    }
    pagetype = cf_ReadByte(infile);
    int len = cf_ReadInt(infile);
    // If not a sound page, just read it in and ignore it
    if (pagetype != PAGETYPE_SOUND) {
      cfseek(infile, len - 4, SEEK_CUR);
      continue;
    }
    mng_ReadNewSoundPage(infile, soundpage);

    if (!stricmp(name, soundpage->sound_struct.name)) {
      // This is the page we want
      found = 1;
      done = 1;
    }
  }
  cfclose(infile);

  return found; // successful!
}
// Given a sound page, allocs a sound and calls AssignSoundPageToSound to actually
// load raws and values. Rturns sound handle on success, -1 if fail
int mng_SetAndLoadSound(mngs_sound_page *soundpage) {
  int n;

  n = AllocSound();
  if (n < 0)
    return -1;
  if (!mng_AssignSoundPageToSound(soundpage, n))
    return -1;

  return n;
}
// Given a soundpage and a sound handle, attempts to make sound n correspond to
// to the soundpage.
// Returns 1 on success, 0 otherwise
int mng_AssignSoundPageToSound(mngs_sound_page *soundpage, int n) {
  sound_info *soundpointer = &Sounds[n];
  int raw_handle;
  // copy our values
  memcpy(soundpointer, &soundpage->sound_struct, sizeof(sound_info));
  strcpy(soundpointer->name, soundpage->sound_struct.name);
// First see if our raw differs from the one on the net
// If it is, make a copy
// If its a release version, don't do any of this
#ifndef RELEASE
  if (Network_up) {
    UpdatePrimitive(LocalSoundsDir / soundpage->raw_name, NetSoundsDir / soundpage->raw_name, soundpage->raw_name,
                    PAGETYPE_SOUND, soundpointer->name);
  }
#endif
  // Try and load our sound raw from the disk
  raw_handle = LoadSoundFile(soundpage->raw_name, Sounds[n].import_volume, false);
  if (raw_handle < 0) {
    mprintf(0, "Couldn't load file '%s' in AssignSoundPage...\n", soundpage->raw_name);
    soundpointer->sample_index = -1;
    return 0;
  } else
    soundpointer->sample_index = raw_handle;
  return 1;
}
// Copies values from a sound into a sound_page
void mng_AssignSoundToSoundPage(int n, mngs_sound_page *soundpage) {
  sound_info *soundpointer = &Sounds[n];
  // Assign the  values
  memcpy(&soundpage->sound_struct, soundpointer, sizeof(sound_info));

  strcpy(soundpage->sound_struct.name, soundpointer->name);
  if (soundpointer->sample_index != -1)
    strcpy(soundpage->raw_name, SoundFiles[soundpointer->sample_index].name);
  else
    strcpy(soundpage->raw_name, "");
}
// Loads a sound found in the net table file.  It then allocs a sound and
// then calls SetAndLoadSound to actually load in any raws associated
// with it
void mng_LoadNetSoundPage(CFILE *infile, bool overlay) {
  mngs_sound_page soundpage;
  memset(&soundpage, 0, sizeof(mngs_sound_page));

  if (mng_ReadNewSoundPage(infile, &soundpage)) {
    int n = FindSoundName(soundpage.sound_struct.name);
    if (n != -1) {
      if (overlay) {
        mprintf(0, "OVERLAYING SOUND %s\n", soundpage.sound_struct.name);
        mng_FreePagetypePrimitives(PAGETYPE_SOUND, soundpage.sound_struct.name, 0);
        mng_AssignSoundPageToSound(&soundpage, n);
      }
      return; // already in memory
    }
    int ret = mng_SetAndLoadSound(&soundpage);
    ASSERT(ret >= 0);
  } else
    mprintf(0, "Could not load soundpage named %s!\n", soundpage.sound_struct.name);
}
// Reads a sound page from a local table file.  It then allocs a sound and
// loads any raws associated with that sound
void mng_LoadLocalSoundPage(CFILE *infile) {
  mngs_sound_page soundpage;
  int ok = 0;
  memset(&soundpage, 0, sizeof(mngs_sound_page));
  if (mng_ReadNewSoundPage(infile, &soundpage)) {
    // Check to see if this is a local copy that is supposed
    // to go over a network copy (supersede the net copy)
    int i = FindSoundName(soundpage.sound_struct.name);
    if (i != -1) {
      // Make sure we really have this page checked out
      mngs_Pagelock pl;

      strcpy(pl.name, soundpage.sound_struct.name);
      pl.pagetype = PAGETYPE_SOUND;

      /*if (Network_up && Stand_alone==0)
      {
              int locked=mng_CheckIfPageOwned(&pl,TableUser);
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
          if (addon->Addon_tracklocks[tidx].pagetype == PAGETYPE_SOUND &&
              !stricmp(addon->Addon_tracklocks[tidx].name, soundpage.sound_struct.name)) {
            // found it!!
            mprintf(0, "SoundPage: %s previously loaded\n", soundpage.sound_struct.name);
            need_to_load_page = false;
            break;
          }
        }
      }

      if (need_to_load_page) {
        mng_FreePagetypePrimitives(PAGETYPE_SOUND, soundpage.sound_struct.name, 0);
        mng_AssignSoundPageToSound(&soundpage, i);

        // For addon data
        if (Loading_addon_table != -1) {
          int overlay = 1;
          int addidx, tidx;
          bool found = false;
          AddOnTablefile *addon;

          // this is an overlay of some sort..see which we are overlaying
          for (addidx = Num_addon_tables - 1; addidx >= 0; addidx--) {
            if (addidx == Loading_addon_table)
              continue;
            addon = &AddOnDataTables[addidx];

            // look for the page in this table file
            for (tidx = 0; tidx < addon->Num_addon_tracklocks; tidx++) {
              if (addon->Addon_tracklocks[tidx].pagetype == PAGETYPE_SOUND &&
                  !stricmp(addon->Addon_tracklocks[tidx].name, soundpage.sound_struct.name)) {
                // found it!!
                found = true;
                overlay = addidx + 2;
                break;
              }
            }

            if (found)
              break;
          }

          mng_PushAddonPage(PAGETYPE_SOUND, soundpage.sound_struct.name, overlay);
        }
      }
    } else {
      // This is a local sound that has never been checked in
      if ((i = mng_SetAndLoadSound(&soundpage)) < 0)
        ok = 0;
      else
        ok = 1;
      // For addon data
      if (ok && Loading_addon_table != -1)
        mng_PushAddonPage(PAGETYPE_SOUND, soundpage.sound_struct.name, 0);
    }

    ASSERT(ok == 1);
    if (Loading_addon_table == -1)
      mng_AllocTrackLock(soundpage.sound_struct.name, PAGETYPE_SOUND);
  } else
    mprintf(0, "Could not load soundpage named %s!\n", soundpage.sound_struct.name);
}
// First searches through the sound index to see if the sound is already
// loaded.  If not, searches in the table file and loads it.
// Returns index of sound found, -1 if not
int mng_GetGuaranteedSoundPage(char *name, CFILE *infile) {
  int i;
  mngs_sound_page soundpage;
  // See if its in memory
  i = FindSoundName(name);
  if (i != -1)
    return i;
  // Not in memory.  Load it from the table file.  Start searching from the
  // current spot in the open table file
  int ret = mng_FindSpecificSoundPage(name, &soundpage, infile ? infile->position : 0);
  if (!ret)
    return -1;
  // We've found it in the table file, now load it.
  ret = mng_SetAndLoadSound(&soundpage);
  // ASSERT (ret>=0);
  if (ret < 0)
    DataError("Cannot load sound <%s>, wav file <%s>\n", soundpage.sound_struct.name, soundpage.raw_name);

  if (Loading_addon_table != -1) {
    // we're loading addon table pages, this will not overlay anything
    mng_PushAddonPage(PAGETYPE_SOUND, soundpage.sound_struct.name, 0);
  }
  return ret;
}
