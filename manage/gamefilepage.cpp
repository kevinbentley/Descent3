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

#include <cstring>
#include <filesystem>

#include "cfile.h"
#include "manage.h"
#include "mono.h"
#include "pserror.h"
#include "ddio.h"
#include "gamefile.h"
#include "gamefilepage.h"
#include "args.h"

// gamefilepage commands that are read/written
// A command is followed by a byte count describing how many bytes
// are in the data for the command
#define GAMEFILEPAGE_COMMAND_NAME 1
#define GAMEFILEPAGE_COMMAND_DIR_NAME 2
#define GAMEFILEPAGE_COMMAND_END 3

#define GAMEFILE_VERSION 2

extern char *TablefileNameOverride;

// Given an open file pointer and a gamefile_page struct, writes that gamefile page out
void mng_WriteGamefilePage(CFILE *outfile, mngs_gamefile_page *gamefilepage) {
  ASSERT(outfile != NULL);
  ASSERT(gamefilepage != NULL);

  cf_WriteByte(outfile, PAGETYPE_GAMEFILE);

  cf_WriteByte(outfile, GAMEFILEPAGE_COMMAND_NAME); // write out gamefile name
  cf_WriteByte(outfile, strlen(gamefilepage->gamefile_struct.name) + 1);
  cf_WriteString(outfile, gamefilepage->gamefile_struct.name);

  cf_WriteByte(outfile, GAMEFILEPAGE_COMMAND_DIR_NAME); // write out gamefile name
  cf_WriteByte(outfile, strlen(gamefilepage->gamefile_struct.dir_name) + 1);
  cf_WriteString(outfile, gamefilepage->gamefile_struct.dir_name);

  cf_WriteByte(outfile, GAMEFILEPAGE_COMMAND_END); // we're all done
  cf_WriteByte(outfile, 0);
}
// Given an open file pointer and a gamefile_page struct, writes that gamefile page out
void mng_WriteNewGamefilePage(CFILE *outfile, mngs_gamefile_page *gamefilepage) {
  ASSERT(outfile != NULL);
  ASSERT(gamefilepage != NULL);

  int offset = StartManagePage(outfile, PAGETYPE_GAMEFILE);

  cf_WriteShort(outfile, GAMEFILE_VERSION);

  cf_WriteString(outfile, gamefilepage->gamefile_struct.name);
  cf_WriteString(outfile, gamefilepage->gamefile_struct.dir_name);

  EndManagePage(outfile, offset);
}

// Reads a gamefile page from an open file.  Returns 0 on error.
int mng_ReadNewGamefilePage(CFILE *infile, mngs_gamefile_page *gamefilepage) {
  ASSERT(infile != NULL);
  memset(gamefilepage, 0, sizeof(mngs_gamefile_page));

  int version = cf_ReadShort(infile);

  cf_ReadString(gamefilepage->gamefile_struct.name, PAGENAME_LEN, infile);
  cf_ReadString(gamefilepage->gamefile_struct.dir_name, PAGENAME_LEN, infile);

  // This is a valid new page
  gamefilepage->gamefile_struct.used = 1;

  return 1; // successfully read
}

// Reads a gamefile page from an open file.  Returns 0 on error.
int mng_ReadGamefilePage(CFILE *infile, mngs_gamefile_page *gamefilepage) {
  int done = 0;
  char command;
  uint16_t len;
  int i;

  if (!Old_table_method)
    return mng_ReadNewGamefilePage(infile, gamefilepage);

  ASSERT(infile != NULL);
  memset(gamefilepage, 0, sizeof(mngs_gamefile_page));

  while (!done) {
    // Read in command byte then read in the length of that commands data

    command = cf_ReadByte(infile);
    len = cf_ReadByte(infile);

    switch (command) {
    case GAMEFILEPAGE_COMMAND_END:
      done = 1;
      break;
    case GAMEFILEPAGE_COMMAND_NAME: // the name of the gamefile model
      cf_ReadString(gamefilepage->gamefile_struct.name, len + 1, infile);
      break;
    case GAMEFILEPAGE_COMMAND_DIR_NAME:
      cf_ReadString(gamefilepage->gamefile_struct.dir_name, len + 1, infile);
      break;
    default:
      // Ignore the ones we don't know
      for (i = 0; i < len; i++)
        cf_ReadByte(infile);
      break;
    }
  }

  // This is a valid new page
  gamefilepage->gamefile_struct.used = 1;

  return 1; // successfully read
}

// Reads in the gamefile named "name" into gamefilepage struct
// Returns 0 on error or couldn't find, else 1 if all is good
int mng_FindSpecificGamefilePage(char *name, mngs_gamefile_page *gamefilepage, int offset) {
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

  if (!infile)
    Error("Cannot open table file.");

  // Read in the entire page file until we find the page we want
  while (!done) {
    if (cfeof(infile)) {
      done = 1;
      continue;
    }
    pagetype = cf_ReadByte(infile);
    int len = cf_ReadInt(infile);

    // If not a gamefile page, just read it in and ignore it
    if (pagetype != PAGETYPE_GAMEFILE) {
      cfseek(infile, len - 4, SEEK_CUR);
      continue;
    }

    mng_ReadNewGamefilePage(infile, gamefilepage);

    if (!stricmp(name, gamefilepage->gamefile_struct.name)) {
      // This is the page we want
      found = 1;
      done = 1;
    }
  }

  cfclose(infile);

  return found; // successful!
}

// Given a gamefile page, allocs a gamefile and calls AssignGamefilePageToGamefile to actually
// load models and values. Rturns gamefile handle on success, -1 if fail
int mng_SetAndLoadGamefile(mngs_gamefile_page *gamefilepage) {
  int n;

  n = AllocGamefile();
  if (n < 0)
    return -1;
  if (!mng_AssignGamefilePageToGamefile(gamefilepage, n))
    return -1;

  return n;
}

// Given a gamefilepage and a gamefile handle, attempts to make gamefile n correspond to
// to the gamefilepage.
// Returns 1 on success, 0 otherwise
int mng_AssignGamefilePageToGamefile(mngs_gamefile_page *gamefilepage, int n) {
  gamefile *gamefilepointer = &Gamefiles[n];

  // copy our values
  memcpy(gamefilepointer, &gamefilepage->gamefile_struct, sizeof(gamefile));
  strcpy(gamefilepointer->name, gamefilepage->gamefile_struct.name);
  strcpy(gamefilepointer->dir_name, gamefilepage->gamefile_struct.dir_name);

  // First see if our image differs from the one on the net
  // If it is, make a copy
  // If its a release version, don't do any of this

#ifndef RELEASE
  if (Network_up) {
    std::filesystem::path str =
        std::filesystem::path(LocalD3Dir) / "data" / gamefilepointer->dir_name / gamefilepointer->name;
    std::filesystem::path netstr =
        std::filesystem::path(NetD3Dir) / "data" / gamefilepointer->dir_name / gamefilepointer->name;

    UpdatePrimitive(str, netstr, gamefilepointer->name, PAGETYPE_GAMEFILE, gamefilepointer->name);

    if (!Starting_editor) {
      if (cf_Diff(str, netstr)) {
        ASSERT(1); // Get Jason Immediately...versions between local and net don't match!

        // Do it again so we can trace to see what is wrong
        UpdatePrimitive(str, netstr, gamefilepointer->name, PAGETYPE_GAMEFILE, gamefilepointer->name);
      }
    }
  }
#endif

  return 1;
}

// Copies values from a gamefile into a gamefile_page
void mng_AssignGamefileToGamefilePage(int n, mngs_gamefile_page *gamefilepage) {
  gamefile *gamefilepointer = &Gamefiles[n];

  // Assign the  values
  memcpy(&gamefilepage->gamefile_struct, gamefilepointer, sizeof(gamefile));

  strcpy(gamefilepage->gamefile_struct.name, gamefilepointer->name);
  strcpy(gamefilepage->gamefile_struct.dir_name, gamefilepointer->dir_name);
}

// Loads a gamefile found in the net table file.  It then allocs a gamefile and
// then calls SetAndLoadGamefile to actually load in any images/models associated
// with it
void mng_LoadNetGamefilePage(CFILE *infile, bool overlay) {
  mngs_gamefile_page gamefilepage;
  memset(&gamefilepage, 0, sizeof(mngs_gamefile_page));

  if (mng_ReadNewGamefilePage(infile, &gamefilepage)) {
    int n = FindGamefileName(gamefilepage.gamefile_struct.name);
    if (n != -1) {
      if (overlay) {
        mprintf(0, "OVERLAYING GAMEFILE %s\n", gamefilepage.gamefile_struct.name);
        mng_FreePagetypePrimitives(PAGETYPE_GAMEFILE, gamefilepage.gamefile_struct.name, 0);
        mng_AssignGamefilePageToGamefile(&gamefilepage, n);
      }
      return;
    }

    int ret = mng_SetAndLoadGamefile(&gamefilepage);
    ASSERT(ret >= 0);
  } else
    mprintf(0, "Could not load gamefilepage named %s!\n", gamefilepage.gamefile_struct.name);
}

// Reads a gamefile page from a local table file.  It then allocs a gamefile and
// loads any images/models associated with that gamefile
void mng_LoadLocalGamefilePage(CFILE *infile) {
  mngs_gamefile_page gamefilepage;
  int ok = 0;
  memset(&gamefilepage, 0, sizeof(mngs_gamefile_page));

  if (mng_ReadNewGamefilePage(infile, &gamefilepage)) {
    // Check to see if this is a local copy that is supposed
    // to go over a network copy (supersede the net copy)

    int i = FindGamefileName(gamefilepage.gamefile_struct.name);
    if (i != -1) {
      // Make sure we really have this page checked out
      mngs_Pagelock pl;

      strcpy(pl.name, gamefilepage.gamefile_struct.name);
      pl.pagetype = PAGETYPE_GAMEFILE;

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
          if (addon->Addon_tracklocks[tidx].pagetype == PAGETYPE_GAMEFILE &&
              !stricmp(addon->Addon_tracklocks[tidx].name, gamefilepage.gamefile_struct.name)) {
            // found it!!
            mprintf(0, "GamefilePage: %s previously loaded\n", gamefilepage.gamefile_struct.name);
            need_to_load_page = false;
            break;
          }
        }
      }

      if (need_to_load_page) {
        mng_FreePagetypePrimitives(PAGETYPE_GAMEFILE, gamefilepage.gamefile_struct.name, 0);
        mng_AssignGamefilePageToGamefile(&gamefilepage, i);

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
              if (addon->Addon_tracklocks[tidx].pagetype == PAGETYPE_GAMEFILE &&
                  !stricmp(addon->Addon_tracklocks[tidx].name, gamefilepage.gamefile_struct.name)) {
                // found it!!
                found = true;
                overlay = addidx + 2;
                break;
              }
            }

            if (found)
              break;
          }

          mng_PushAddonPage(PAGETYPE_GAMEFILE, gamefilepage.gamefile_struct.name, overlay);
        }
      }
    } else {
      // This is a local gamefile that has never been checked in
      if (mng_SetAndLoadGamefile(&gamefilepage) < 0)
        ok = 0;
      else
        ok = 1;

      // For addon data
      if (ok && Loading_addon_table != -1)
        mng_PushAddonPage(PAGETYPE_GAMEFILE, gamefilepage.gamefile_struct.name, 0);
    }

    ASSERT(ok == 1); // There was problem loading a page!

    if (Loading_addon_table == -1)
      mng_AllocTrackLock(gamefilepage.gamefile_struct.name, PAGETYPE_GAMEFILE);

  } else
    mprintf(0, "Could not load gamefilepage named %s!\n", gamefilepage.gamefile_struct.name);
}
