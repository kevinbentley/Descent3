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


#ifndef MANAGE_H
#define MANAGE_H

#include <stdio.h>
#include "cfile.h"
#include "bitmap.h"
#include "manage_external.h"

#if defined(__LINUX__)
#include "linux_fix.h" //for strnicmp,etc.
#endif

#define LOCAL_TABLE "Table.loc"
#define TEMP_LOCAL_TABLE "Tablr.loc"

#define NET_TABLE "Table.gam"
#define TEMP_NET_TABLE "Tablr.tmp"

// Notes:	Pagelocks are for keeping track of what pages are locked by which users
//			Tracklocks are for keeping track of what pages the local user is working on or has locked

#define PAGELOCK_NAME_LEN 30
#define TABLE_NAME_LEN _MAX_PATH
#define INFO_STRING_LEN 100
#define MAX_PAGELOCKS 1000
#define MAX_TRACKLOCKS 5000

#define PAGETYPE_UNKNOWN 0
#define PAGETYPE_TEXTURE 1
#define PAGETYPE_WEAPON 2
#define PAGETYPE_ROBOT 3
#define PAGETYPE_POWERUP 4
#define PAGETYPE_DOOR 5
#define PAGETYPE_SHIP 6
#define PAGETYPE_SOUND 7
#define PAGETYPE_MEGACELL 8
#define PAGETYPE_GAMEFILE 9
#define PAGETYPE_GENERIC 10

struct mngs_Pagelock {
  uint8_t pagetype; // of type PAGETYPE above
  char name[PAGENAME_LEN];
  char holder[PAGENAME_LEN];
};

struct mngs_track_lock {
  uint8_t used;
  uint8_t overlay;
  uint8_t pagetype;
  uint8_t __pad;
  int stack_filepos; // file position of this page in the tablefile (the value we are
                     // pushing, for addon tables)
  char name[PAGENAME_LEN];
};

// For addon data
#define MAX_ADDON_TRACKLOCKS 1000
#define MAX_ADDON_TABLES 2

struct AddOnTablefile {
  char AddOnTableFilename[TABLE_NAME_LEN];
  int Num_addon_tracklocks;
  mngs_track_lock *Addon_tracklocks;
};
extern AddOnTablefile AddOnDataTables[MAX_ADDON_TABLES];
extern int Num_addon_tables;

// Takes our addon pages and frees/restores our data to the appropriate pages
void mng_PopAddonPages();

// Simply sets no addon data to be loaded
void mng_ClearAddonTables();

// Push the given table file as an addon table file
// returns true on success
bool mng_SetAddonTable(char *name);

// Pushes an addon pack onto the stack so we can keep track of it
void mng_PushAddonPage(int pagetype, char *name, int overlay);

// Loads and allocs all pages found locally
void mng_LoadAddonPages();

// signifies whether or not the network is up
extern int Network_up, Stand_alone;

// Starting editor?
extern int Starting_editor, Loading_locals, Loading_addon_table;

extern char LocalD3Dir[];
extern char NetD3Dir[];
extern char TableFilename[];
extern char TableLockFilename[];
extern char LocalTableFilename[];
extern char LocalTempTableFilename[];
extern char LocalLevelsDir[];
extern char ManageGraphicsDir[];
extern char LocalManageGraphicsDir[];
extern char LocalModelsDir[];
extern char NetModelsDir[];
extern char LocalSoundsDir[];
extern char NetSoundsDir[];
extern char LocalRoomsDir[];
extern char NetRoomsDir[];
extern char LocalTableDir[];
extern char NetMiscDir[];
extern char LocalMiscDir[];
extern char NetMusicDir[];
extern char LocalMusicDir[];
extern char NetScriptDir[];
extern char LocalScriptDir[];
extern char NetArtDir[];
extern char LocalArtDir[];

extern char LocalCustomGraphicsDir[];
extern char LocalCustomSoundsDir[];

extern char TempTableFilename[];
extern char TempTableLockFilename[];
extern char ErrorString[INFO_STRING_LEN];
extern char InfoString[INFO_STRING_LEN];
extern char TableUser[];
extern char LockerFile[];
extern char VersionFile[];
extern mngs_Pagelock GlobalPagelocks[];
extern mngs_track_lock GlobalTrackLocks[];

int mng_InitTableFiles();

// Loads our tables
int mng_LoadTableFiles(int show_progress);

int mng_InitLocalTables();
int mng_InitNetTables();

// Checks to see if there is a table file...if not, create one with a dummy page
void mng_CheckToCreateLocalTables();
void mng_CheckToCreateNetTables();

// Creates directories if needed
void mng_InitLocalDirectories();
void mng_InitNetDirectories();

void mng_ReadDummyPage(CFILE *infile, uint8_t pagetype);
void mng_ReadWriteDummyPage(CFILE *infile, CFILE *outfile, uint8_t pagetype);

// Function for writing out "undefined" page...useful for placeholding
void mng_WriteUnknownPage(CFILE *outfile);

// Lock functions
//-----------------------------------------------

// If table lock file not found, create a dummy one
void mng_InitPagelocks();

// Writes a pagelock to an open file
void mng_WritePagelock(CFILE *fp, mngs_Pagelock *pl);

// Reads a pagelock from the fp file.  Returns 1 if successfully read, 0 if eof was encountered.
int mng_ReadPagelock(CFILE *, mngs_Pagelock *);

// Given a page name, checks to see if it is locked.
// Returns 1 if locked, 0 if not.
int mng_CheckIfPageLocked(mngs_Pagelock *);

// Given a page name, checks to see if it is locked by owner.
// Returns 1 if locked, 0 if not.
int mng_CheckIfPageOwned(mngs_Pagelock *, char *owner);

// Given a pagelock, replaces the one already inside the lock file, or if not present, adds it to
// the lock file.  Returns 0 on error, or 1 if successful.
int mng_ReplacePagelock(char *, mngs_Pagelock *);

int mng_GetListOfLocks(mngs_Pagelock *pl, int max, char *who);

// Given a name and a pagetype, deletes the one already inside the lock file
int mng_DeletePagelock(char *name, int pagetype);

// Call this before any chokepoint functions are executed.
// Locks the whole table system for our exclusive use
// Returns 0 if can't lock
int mng_MakeLocker();

// Given a list of names and a pagetype, deletes the ones already inside the lock file
int mng_DeletePagelockSeries(char *names[], int num, int pagetype);

// Simply erases the Lockerfile
void mng_EraseLocker();

// Open the net table file and read in all pages
int mng_LoadNetPages(int show_progress);
int mng_LoadLocalPages();

//---------------------------------------------------------------

// Clear out tracklocks
void mng_InitTrackLocks();

// Given a name, returns the index of the tracklock with that name
// -1 indicates that it wasn't found
int mng_FindTrackLock(char *name, int pagetype);

// Searches through global array of tracklocks and returns first free one
// returns -1 if none free
int mng_AllocTrackLock(char *name, int pagetype);

// Frees a tracklock
void mng_FreeTrackLock(int n);

//----------------------------------------------------------------

// Displays all the locks of "name"
void mng_DisplayLockList(char *name);

// Renames a page on the network
int mng_RenamePage(char *oldname, char *newname, int pagetype);

// Removes a file, then renames another file to be the removed file. Get it?
// Returns 1 on success, else 0 on fail
int SwitcherooFiles(char *name, char *tempname);

// Returns true if the passed in pagelock is in the LockList, else false
bool InLockList(mngs_Pagelock *pl);

// Takes a pagelock and sets its holder name to UNLOCKED
void mng_OverrideToUnlocked(mngs_Pagelock *temp_pl);

// Returns true if the passed in primitive is old (ie needs to be updated from the network)
bool IsPrimitiveOld(char *name);

// Updates a primitive if needed
// Localname = local version of the primname (with path)
// Netname = Network version of the primname (with path)
void UpdatePrimitive(char *localname, char *netname, char *primname, int pagetype, char *pagename);

// Writes a chunk header.  Writes chunk id & placeholder length.  Returns chunk start pos
int StartManagePage(CFILE *ofile, uint8_t pagetype);

// Fill in page length when done writing
void EndManagePage(CFILE *ofile, int chunk_start_pos);

struct physics_info;
struct otype_wb_info;

// Reads a physics chunk in from the table file
void mng_ReadPhysicsChunk(physics_info *phys_info, CFILE *infile);
void mng_WritePhysicsChunk(physics_info *phys_info, CFILE *outfile);

// Writes out weapon battery info
void mng_WriteWeaponBatteryChunk(otype_wb_info *static_wb, CFILE *outfile);

// Reads in weapon battery info
void mng_ReadWeaponBatteryChunk(otype_wb_info *static_wb, CFILE *infile, int version);

// Given a texture handle, searches the table file and replaces the texture with the same name
// If local=1, then does it to the users local copy
// Returns 0 on error, else 1 if all is good
int mng_ReplacePage(char *srcname, char *destname, int handle, int dest_pagetype, int local);

// Given a texture name, finds it in the table file and deletes it
// If local is 1, deletes from the local table file
int mng_DeletePage(char *name, int dest_pagetype, int local);

void mng_FreePagetypePrimitives(int pagetype, char *name, int freetype);

extern int Old_table_method;

// Error reporting
void DataError(const char *fmt, ...);

#endif
