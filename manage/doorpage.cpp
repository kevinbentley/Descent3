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

 * $Logfile: /DescentIII/Main/manage/doorpage.cpp $
 * $Revision: 25 $
 * $Date: 10/26/99 3:30p $
 * $Author: Jeff $
 *
 * For loading/saving of door types
 *
 * $Log: /DescentIII/Main/manage/doorpage.cpp $
 *
 * 25    10/26/99 3:30p Jeff
 * handle extra.gam addon tablefile
 *
 * 24    10/20/99 6:27p Jeff
 * sped up addon page popping (by saving page offsets)
 *
 * 23    8/11/99 5:32p Jeff
 * changes to fix addon tablefile support so it works correctly
 *
 * 22    4/14/99 1:33a Jeff
 * fixed case mismatched #includes
 *
 * 21    3/04/99 4:47p Jason
 * temp fix (ie BAD HACK) for OEM table file woes
 *
 * 20    2/04/99 2:05p Matt
 * Added blastable doors
 *
 * 19    1/21/99 11:16p Jeff
 * pulled out some structs and defines from header files and moved them
 * into seperate header files so that multiplayer dlls don't require major
 * game headers, just those new headers.  Side effect is a shorter build
 * time.  Also cleaned up some header file #includes that weren't needed.
 * This affected polymodel.h, object.h, player.h, vecmat.h, room.h,
 * manage.h and multi.h
 *
 * 18    1/13/99 7:04a Jeff
 * put #ifdef around #include <windows.h>
 *
 * 17    12/29/98 4:30p Jason
 * added add-on data functionality
 *
 * 16    12/21/98 5:27p Jeff
 * added osiris module information to door page.  Fixed up dialogs for
 * objects and doors for script interface (added a browse button)
 *
 * 15    12/17/98 12:50p Jason
 * changed doorpage
 *
 * 14    11/06/98 12:35p Jason
 * more speedups for manage system
 *
 * 13    11/05/98 7:54p Jason
 * changes for new manage system
 *
 * 12    11/02/98 6:02p Jason
 * made yes network updates much faster
 *
 * 11    10/09/98 2:27p Jason
 * reorganized table file system
 *
 * 10    5/24/98 11:59p Mark
 * Fixed a bug introduced with last revs
 *
 * 9     5/22/98 8:50p Matt
 * Added sounds for doors
 *
 * 8     4/02/98 3:54p Jason
 * first pass in getting polymodel paging to work
 *
 * 7     2/23/98 1:22p Jason
 * made FindSpecific* read from the local drive, not the net drive - when
 * starting the editor
 *
 * 6     2/02/98 7:07p Matt
 * Added support for doors that can be seen through even when closed
 *
 * 5     1/15/98 6:22p Jason
 * added safety checks so the network won't copy over a primitive you have
 * held locally
 *
 * 4     10/06/97 6:39p Jason
 * got terrain objects working with lightmaps/radiosity
 *
 * 3     10/06/97 4:05p Samir
 * Jason forgot to put a break in a switch-case statement.  I fixed
 * this...
 *
 * 2     10/06/97 1:01p Jason
 * made doors work with scripts (sort of)
 *
 * 9     5/08/97 12:41p Jason
 * made manage system work with device dependant path names
 *
 * 8     4/25/97 6:16p Jason
 * added switcheroo function
 *
 * 7     4/08/97 2:25a Chris
 * Fixed a problem with uninitialized data.  In addition it
 * fixed a problem with the .used flag that would happen
 * 1 out of 2^(sizeof(used_flag)) times (it would be zero
 * when it was supposed to be non-zero)
 *
 * 6     3/17/97 6:39p Jason
 * added staysopen page write
 *
 * 5     3/13/97 6:13p Jason
 * got poly doors working
 *
 * 4     3/11/97 6:03p Chris
 * Fixed the fix to a simple function.  Isn't crossplatform development
 * wonderful.  :)
 *
 * 3     3/11/97 5:08 PM Jeremy
 * in mng_WriteDoorPage there are two for loops.  The second tried to use
 * the int "i" which was declared in the scope of the first.  This breaks
 * under Codewarrior.  I think that's how it's supposed to work under
 * ANSI.
 *
 * 2     3/05/97 12:16p Jason
 * added code to support our new 3d doors
 *
 * 1     3/05/97 11:04a Jason
 *
 *
 * $NoKeywords: $
 */

#include <cstring>
#include <filesystem>

#include "cfile.h"
#include "manage.h"
#include "door.h"
#include "doorpage.h"
#include "mono.h"
#include "pserror.h"
#include "polymodel.h"
#include "ddio.h"
#include "soundload.h"
#include "soundpage.h"
#include "args.h"

// doorpage commands that are read/written
// A command is followed by a byte count describing how many bytes
// are in the data for the command
#define DOORPAGE_COMMAND_NAME 1
#define DOORPAGE_COMMAND_END 2
#define DOORPAGE_COMMAND_IMAGE_NAME 3
#define DOORPAGE_COMMAND_VERSION 4
#define DOORPAGE_COMMAND_OPEN_TIME 5
#define DOORPAGE_COMMAND_CLOSE_TIME 6
#define DOORPAGE_COMMAND_STAYS_OPEN 7
#define DOORPAGE_COMMAND_SCRIPTNAME 8
#define DOORPAGE_COMMAND_FLAGS 9
#define DOORPAGE_COMMAND_OPEN_SOUND_NAME 10
#define DOORPAGE_COMMAND_CLOSE_SOUND_NAME 11

#define DOORPAGE_VERSION 3

extern char *TablefileNameOverride;

// Given an open file pointer and a door_page struct, writes that door page out
void mng_WriteDoorPage(CFILE *outfile, mngs_door_page *doorpage) {
  int i;

  ASSERT(outfile != NULL);
  ASSERT(doorpage != NULL);

  cf_WriteByte(outfile, PAGETYPE_DOOR);

  cf_WriteByte(outfile, DOORPAGE_COMMAND_NAME); // write out Door name
  cf_WriteByte(outfile, PAGENAME_LEN);
  for (i = 0; i < PAGENAME_LEN; i++)
    cf_WriteByte(outfile, doorpage->door_struct.name[i]);

  // Write out its models name
  cf_WriteByte(outfile, DOORPAGE_COMMAND_IMAGE_NAME); // get ready to write out name
  cf_WriteByte(outfile, PAGENAME_LEN);
  for (i = 0; i < PAGENAME_LEN; i++)
    cf_WriteByte(outfile, doorpage->image_name[i]);

  cf_WriteByte(outfile, DOORPAGE_COMMAND_OPEN_TIME);
  cf_WriteByte(outfile, sizeof(float));
  cf_WriteFloat(outfile, doorpage->door_struct.total_open_time);

  cf_WriteByte(outfile, DOORPAGE_COMMAND_CLOSE_TIME);
  cf_WriteByte(outfile, sizeof(float));
  cf_WriteFloat(outfile, doorpage->door_struct.total_close_time);

  cf_WriteByte(outfile, DOORPAGE_COMMAND_STAYS_OPEN);
  cf_WriteByte(outfile, sizeof(float));
  cf_WriteFloat(outfile, doorpage->door_struct.total_time_open);

  cf_WriteByte(outfile, DOORPAGE_COMMAND_SCRIPTNAME);
  cf_WriteByte(outfile, strlen("") + 1);
  cf_WriteString(outfile, "");

  cf_WriteByte(outfile, DOORPAGE_COMMAND_FLAGS);
  cf_WriteByte(outfile, sizeof(int8_t));
  cf_WriteByte(outfile, doorpage->door_struct.flags);

  Int3(); // this shouldn't be called -- hit points not written out

  cf_WriteByte(outfile, DOORPAGE_COMMAND_OPEN_SOUND_NAME);
  cf_WriteByte(outfile, strlen(doorpage->open_sound_name) + 1);
  cf_WriteString(outfile, doorpage->open_sound_name);

  cf_WriteByte(outfile, DOORPAGE_COMMAND_CLOSE_SOUND_NAME);
  cf_WriteByte(outfile, strlen(doorpage->close_sound_name) + 1);
  cf_WriteString(outfile, doorpage->close_sound_name);

  cf_WriteByte(outfile, DOORPAGE_COMMAND_END); // we're all done
  cf_WriteByte(outfile, 0);
}

// Given an open file pointer and a door_page struct, writes that door page out
void mng_WriteNewDoorPage(CFILE *outfile, mngs_door_page *doorpage) {
  ASSERT(outfile != NULL);
  ASSERT(doorpage != NULL);

  int offset = StartManagePage(outfile, PAGETYPE_DOOR);

  cf_WriteShort(outfile, DOORPAGE_VERSION);
  cf_WriteString(outfile, doorpage->door_struct.name);
  cf_WriteString(outfile, doorpage->image_name);

  cf_WriteFloat(outfile, doorpage->door_struct.total_open_time);
  cf_WriteFloat(outfile, doorpage->door_struct.total_close_time);
  cf_WriteFloat(outfile, doorpage->door_struct.total_time_open);

  cf_WriteByte(outfile, doorpage->door_struct.flags);
  cf_WriteShort(outfile, doorpage->door_struct.hit_points);

  cf_WriteString(outfile, doorpage->open_sound_name);
  cf_WriteString(outfile, doorpage->close_sound_name);

  cf_WriteString(outfile, doorpage->door_struct.module_name);

  EndManagePage(outfile, offset);
}

// Reads a door page from an open file.  Returns 0 on error.
int mng_ReadNewDoorPage(CFILE *infile, mngs_door_page *doorpage) {
  ASSERT(infile != NULL);

  int version = cf_ReadShort(infile);

  cf_ReadString(doorpage->door_struct.name, PAGENAME_LEN, infile);
  cf_ReadString(doorpage->image_name, PAGENAME_LEN, infile);

  doorpage->door_struct.total_open_time = cf_ReadFloat(infile);
  doorpage->door_struct.total_close_time = cf_ReadFloat(infile);
  doorpage->door_struct.total_time_open = cf_ReadFloat(infile);

  doorpage->door_struct.flags = cf_ReadByte(infile);

  if (version >= 3)
    doorpage->door_struct.hit_points = cf_ReadShort(infile);
  else
    doorpage->door_struct.hit_points = 0;

  cf_ReadString(doorpage->open_sound_name, PAGENAME_LEN, infile);
  cf_ReadString(doorpage->close_sound_name, PAGENAME_LEN, infile);

  if (version >= 2)
    cf_ReadString(doorpage->door_struct.module_name, MAX_MODULENAME_LEN, infile);
  else
    doorpage->door_struct.module_name[0] = '\0';

  // This is a valid new page
  doorpage->door_struct.used = 1;

  return 1; // successfully read
}

// Reads a door page from an open file.  Returns 0 on error.
int mng_ReadDoorPage(CFILE *infile, mngs_door_page *doorpage) {
  int done = 0;
  char command;
  uint8_t len;
  int i;

  if (!Old_table_method)
    return mng_ReadNewDoorPage(infile, doorpage);

  // doorpage->door_struct.script_name[0]=0;
  strcpy(doorpage->open_sound_name, "INVALID SOUND NAME");
  strcpy(doorpage->close_sound_name, "INVALID SOUND NAME");

  ASSERT(infile != NULL);

  while (!done) {
    // Read in command byte then read in the length of that commands data

    command = cf_ReadByte(infile);
    len = cf_ReadByte(infile);

    switch (command) {
    case DOORPAGE_COMMAND_END:
      done = 1;
      break;
    case DOORPAGE_COMMAND_IMAGE_NAME: // the name of the door model
      for (i = 0; i < PAGENAME_LEN; i++)
        doorpage->image_name[i] = cf_ReadByte(infile);
      break;
    case DOORPAGE_COMMAND_NAME:
      for (i = 0; i < PAGENAME_LEN; i++)
        doorpage->door_struct.name[i] = cf_ReadByte(infile);
      break;
    case DOORPAGE_COMMAND_OPEN_TIME:
      doorpage->door_struct.total_open_time = cf_ReadFloat(infile);
      break;
    case DOORPAGE_COMMAND_STAYS_OPEN:
      doorpage->door_struct.total_time_open = cf_ReadFloat(infile);
      break;
    case DOORPAGE_COMMAND_CLOSE_TIME:
      doorpage->door_struct.total_close_time = cf_ReadFloat(infile);
      break;
    case DOORPAGE_COMMAND_SCRIPTNAME: {
      char dummy[256];
      cf_ReadString(dummy, len + 1, infile);
    } break;
    case DOORPAGE_COMMAND_FLAGS:
      doorpage->door_struct.flags = cf_ReadByte(infile);
      break;
    case DOORPAGE_COMMAND_OPEN_SOUND_NAME:
      cf_ReadString(doorpage->open_sound_name, len + 1, infile);
      break;
    case DOORPAGE_COMMAND_CLOSE_SOUND_NAME:
      cf_ReadString(doorpage->close_sound_name, len + 1, infile);
      break;
    default:
      // Ignore the ones we don't know
      for (i = 0; i < len; i++)
        cf_ReadByte(infile);
      return 0;
    }
  }

  // This is a valid new page
  doorpage->door_struct.used = 1;

  return 1; // successfully read
}

// Reads in the door named "name" into doorpage struct
// Returns 0 on error or couldn't find, else 1 if all is good
int mng_FindSpecificDoorPage(char *name, mngs_door_page *doorpage, int offset) {
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
    mprintf(0, "Couldn't open table file to find door!\n");
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

    // If not a door page, just read it in and ignore it
    if (pagetype != PAGETYPE_DOOR) {
      cfseek(infile, len - 4, SEEK_CUR);
      continue;
    }

    mng_ReadNewDoorPage(infile, doorpage);

    if (!stricmp(name, doorpage->door_struct.name)) {
      // This is the page we want
      found = 1;
      done = 1;
    }
  }

  cfclose(infile);

  return found; // successful!
}

// Given a door page, allocs a door and calls AssignDoorPageToDoor to actually
// load models and values. Rturns door handle on success, -1 if fail
int mng_SetAndLoadDoor(mngs_door_page *doorpage) {
  int n;

  n = AllocDoor();
  if (n < 0)
    return -1;
  if (!mng_AssignDoorPageToDoor(doorpage, n))
    return -1;

  return n;
}

// Given a doorpage and a door handle, attempts to make door n correspond to
// to the doorpage.
// Returns 1 on success, 0 otherwise
int mng_AssignDoorPageToDoor(mngs_door_page *doorpage, int n) {
  door *doorpointer = &Doors[n];
  int img_handle;

  // copy our values
  memcpy(doorpointer, &doorpage->door_struct, sizeof(door));
  strcpy(doorpointer->name, doorpage->door_struct.name);

  // First see if our image differs from the one on the net
  // If it is, make a copy
  // If its a release version, don't do any of this

#ifndef RELEASE
  if (Network_up) {
    UpdatePrimitive(LocalModelsDir / doorpage->image_name, NetModelsDir / doorpage->image_name, doorpage->image_name,
                    PAGETYPE_DOOR, doorpointer->name);
  }
#endif

  // Try and load our door model from the disk

  img_handle = LoadPolyModel(doorpage->image_name, 1);

  // Set sounds
  doorpointer->open_sound = mng_GetGuaranteedSoundPage(doorpage->open_sound_name);
  doorpointer->close_sound = mng_GetGuaranteedSoundPage(doorpage->close_sound_name);

  if (img_handle < 0) {
    mprintf(0, "Couldn't load file '%s' in AssignDoorPage...\n", doorpage->image_name);
    doorpointer->model_handle = -1;
    return 0;
  } else
    doorpointer->model_handle = img_handle;

  return 1;
}

// Copies values from a door into a door_page
void mng_AssignDoorToDoorPage(int n, mngs_door_page *doorpage) {
  door *doorpointer = &Doors[n];

  // Assign the  values
  memcpy(&doorpage->door_struct, doorpointer, sizeof(door));

  strcpy(doorpage->door_struct.name, doorpointer->name);

  if (doorpointer->model_handle != -1)
    strcpy(doorpage->image_name, Poly_models[doorpointer->model_handle].name);
  else
    strcpy(doorpage->image_name, "INVALID IMAGE NAME");

  if (doorpointer->open_sound != -1)
    strcpy(doorpage->open_sound_name, Sounds[doorpointer->open_sound].name);
  else
    strcpy(doorpage->open_sound_name, "INVALID SOUND NAME");

  if (doorpointer->close_sound != -1)
    strcpy(doorpage->close_sound_name, Sounds[doorpointer->close_sound].name);
  else
    strcpy(doorpage->close_sound_name, "INVALID SOUND NAME");
}

// Loads a door found in the net table file.  It then allocs a door and
// then calls SetAndLoadDoor to actually load in any images/models associated
// with it
void mng_LoadNetDoorPage(CFILE *infile, bool overlay) {
  mngs_door_page doorpage;
  memset(&doorpage, 0, sizeof(mngs_door_page));

  if (mng_ReadNewDoorPage(infile, &doorpage)) {
    int n;
    n = FindDoorName(doorpage.door_struct.name);
    if (n != -1) {
      if (overlay) {
        mprintf(0, "OVERLAYING DOOR %s\n", doorpage.door_struct.name);
        mng_FreePagetypePrimitives(PAGETYPE_DOOR, doorpage.door_struct.name, 0);
        mng_AssignDoorPageToDoor(&doorpage, n);
      }
      return;
    }

    int ret = mng_SetAndLoadDoor(&doorpage);
    ASSERT(ret >= 0);
  } else
    mprintf(0, "Could not load doorpage named %s!\n", doorpage.door_struct.name);
}

// Reads a door page from a local table file.  It then allocs a door and
// loads any images/models associated with that door
void mng_LoadLocalDoorPage(CFILE *infile) {
  mngs_door_page doorpage;
  int ok = 0;
  memset(&doorpage, 0, sizeof(mngs_door_page));

  if (mng_ReadNewDoorPage(infile, &doorpage)) {
    // Check to see if this is a local copy that is supposed
    // to go over a network copy (supersede the net copy)

    int i = FindDoorName(doorpage.door_struct.name);
    if (i != -1) {
      // Make sure we really have this page checked out
      mngs_Pagelock pl;

      strcpy(pl.name, doorpage.door_struct.name);
      pl.pagetype = PAGETYPE_DOOR;

      /*if (Network_up && Stand_alone==0)
      {
              int locked;
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
          if (addon->Addon_tracklocks[tidx].pagetype == PAGETYPE_DOOR &&
              !stricmp(addon->Addon_tracklocks[tidx].name, doorpage.door_struct.name)) {
            // found it!!
            mprintf(0, "DoorPage: %s previously loaded\n", doorpage.door_struct.name);
            need_to_load_page = false;
            break;
          }
        }
      }

      if (need_to_load_page) {
        mng_FreePagetypePrimitives(PAGETYPE_DOOR, doorpage.door_struct.name, 0);
        mng_AssignDoorPageToDoor(&doorpage, i);

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
              if (addon->Addon_tracklocks[tidx].pagetype == PAGETYPE_DOOR &&
                  !stricmp(addon->Addon_tracklocks[tidx].name, doorpage.door_struct.name)) {
                // found it!!
                found = true;
                overlay = addidx + 2;
                break;
              }
            }

            if (found)
              break;
          }

          mng_PushAddonPage(PAGETYPE_DOOR, doorpage.door_struct.name, overlay);
        }
      }
    } else {
      // This is a local door that has never been checked in
      if ((i = mng_SetAndLoadDoor(&doorpage)) < 0)
        ok = 0;
      else
        ok = 1;

      // For addon data
      if (ok && Loading_addon_table != -1)
        mng_PushAddonPage(PAGETYPE_DOOR, doorpage.door_struct.name, 0);
    }

    ASSERT(ok == 1);

    if (Loading_addon_table == -1)
      mng_AllocTrackLock(doorpage.door_struct.name, PAGETYPE_DOOR);
  } else

    mprintf(0, "Could not load doorpage named %s!\n", doorpage.door_struct.name);
}
