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

 * $Logfile: /DescentIII/Main/manage/manage.cpp $
 * $Revision: 103 $
 * $Date: 10/10/01 11:32a $
 * $Author: Matt $
 *
 * Jason should put something here
 *
 * $Log: /DescentIII/Main/manage/manage.cpp $
 *
 * 103   10/10/01 11:32a Matt
 * Added system to check for errors when reading in add-on data.
 *
 * 102   10/08/01 1:50p Matt
 * Added a case for gamefile pagetype to avoid int3
 *
 * 101   4/19/00 5:07p Matt
 * From Duane for 1.4
 * Added checks, asserts, and fixes for bad return values
 *
 * 100   3/20/00 12:27p Matt
 * Merge of Duane's post-1.3 changes.
 * Mac pilot directory stuff.
 *
 * 99    10/26/99 3:30p Jeff
 * handle extra.gam addon tablefile
 *
 * 98    10/20/99 6:27p Jeff
 * sped up addon page popping (by saving page offsets)
 *
 * 97    10/19/99 9:14p Chris
 * Fixed a memory free bug
 *
 * 96    8/11/99 5:32p Jeff
 * changes to fix addon tablefile support so it works correctly
 *
 * 95    7/28/99 2:29p Kevin
 * Added macintosh DLL extentions (msl)
 *
 * 94    5/14/99 12:45p Matt
 * Removed yet more static data
 *
 * 93    5/14/99 12:33p Matt
 * Fixed another case of too much local data for the Mac.
 *
 * 92    5/13/99 8:36p Matt
 * Made some local variables global to get around the 32K local variable
 * limit on the Mac.
 *
 * 91    5/12/99 3:01p Matt
 * Declared one texpage structure statically for all the functions that
 * need it, because the Mac limits local data to 32K.
 *
 * 90    4/30/99 8:53p Matt
 * Added a "voice" directory for gamefiles.
 *
 * 89    4/22/99 3:26p Jason
 * added transferring of pagelocks
 *
 * 88    4/20/99 12:06a Jeff
 * added so files to data/scripts search path
 *
 * 87    4/15/99 5:21p Jason
 * sped up table file loading
 *
 * 86    4/14/99 10:46a Kevin
 * Removed OutrageMessageBox from release builds
 *
 * 85    4/14/99 1:33a Jeff
 * fixed case mismatched #includes
 *
 * 84    4/12/99 3:05p Jason
 * changes for 256 textures
 *
 * 83    3/05/99 10:42a Jason
 * more deletion of pagelocls
 *
 * 82    3/04/99 1:46p Jason
 * fixed some manage problems
 *
 * 81    2/27/99 5:15p Jason
 * fixed search path bug
 *
 * 80    2/17/99 12:11p Jason
 * added music directory to searchable list
 *
 * 79    2/16/99 11:35a Samir
 * added art directory.
 *
 * 78    2/10/99 3:47p Jason
 * before doing a backup, makes sure that the tablefile version is the
 * same on the net and on the local machine
 *
 * 77    1/29/99 6:29p Jason
 * first pass at adding bumpmaps
 *
 * 76    1/21/99 11:16p Jeff
 * pulled out some structs and defines from header files and moved them
 * into seperate header files so that multiplayer dlls don't require major
 * game headers, just those new headers.  Side effect is a shorter build
 * time.  Also cleaned up some header file #includes that weren't needed.
 * This affected polymodel.h, object.h, player.h, vecmat.h, room.h,
 * manage.h and multi.h
 *
 * 75    1/13/99 2:49p Jeff
 * added .msg to the search path for data\scripts
 *
 * 74    1/13/99 7:08a Jeff
 * put some #ifdef's around some window's specific code (really only used
 * in the editor, but EDITOR is never defined when building manage) so it
 * builds in linux
 *
 * 73    12/30/98 6:52p Matt
 * Fixed compile warnings
 *
 * 72    12/29/98 4:30p Jason
 * added add-on data functionality
 *
 * 71    12/13/98 7:51p Jeff
 * only check the script directory for cpp,dll and def files
 *
 * 70    12/11/98 5:50p Jeff
 * implemented and added changes regarding Level&Scripting manage system
 * and compiler interface
 *
 * 69    11/28/98 2:19p Jason
 * fixed stupid filecopy bug
 *
 * 68    11/18/98 11:02a Jason
 * temp fix for table problems
 *
 * 67    11/16/98 3:49p Jason
 * changes for manage system
 *
 * 66    11/16/98 2:43p Jason
 * better file checking for old files
 *
 * 65    11/13/98 12:30p Jason
 * fixed reordered pages bug
 *
 * 64    11/13/98 12:30p Jason
 * changes for weapons
 *
 * 63    11/06/98 6:00p Josh
 * fixed dumb bug
 *
 * 62    11/06/98 5:28p Josh
 * FROM JASON:upped tracklock limit
 *
 * 61    11/06/98 12:35p Jason
 * more speedups for manage system
 *
 * 60    11/05/98 7:55p Jason
 * changes for new manage system
 *
 * 59    11/04/98 11:02a Jason
 * added levels and briefing directories to new "old files" update method
 *
 * 58    11/02/98 6:35p Jason
 * changes for filter
 *
 * 57    11/02/98 6:02p Jason
 * made yes network updates much faster
 *
 * 56    10/15/98 8:48a Matt
 * Changed some errors to use Error() instead of OutrageMessageBox()
 *
 * 55    10/14/98 5:15p Jason
 * added version checking to the table file
 *
 * 54    10/12/98 11:38p Jeff
 * wrapped all the Object_info[].description whenever freed...trying to
 * find an obscure bug.  Added icon_name to manage page of Generic
 *
 * 53    10/12/98 10:31a Jason
 * don't seach data directories if release
 *
 * 52    10/09/98 4:39p Jason
 * fixed local table file message
 *
 * 51    10/09/98 2:27p Jason
 * reorganized table file system
 *
 * 50    10/09/98 2:40a Jason
 * fixed table file issues with demo
 *
 * 49    10/08/98 10:03p Jason
 * more filtered table file stuff
 *
 * 48    10/08/98 7:05p Jason
 * added file filter support
 *
 * 47    9/28/98 6:53p Kevin
 * localized some multiplayer menus
 *
 * 46    9/25/98 4:37p Jason
 * fixed dedicated server printing out progress messages
 *
 * 45    9/25/98 2:53p Jason
 * added progress bar
 *
 * 44    9/25/98 12:24p Samir
 * fixed bugs for release version.
 *
 * 43    9/24/98 6:22p Jason
 * fixed RELEASE version asking to update network files
 *
 * 42    9/18/98 3:58p Jason
 * change weapon reordering to do countermeasure weapons after generics
 *
 * 41    9/15/98 4:31p Jason
 * added more functionality for the dedicated server
 *
 * 40    9/14/98 6:28p Jason
 * first pass at getting dedicated server working
 *
 * 39    8/25/98 3:42p Jason
 * fixed generic object problems
 *
 * 38    8/25/98 3:25p Jason
 * turned off fast load trick
 *
 * 37    8/17/98 4:00p Jason
 * Added mprintf
 *
 * 36    8/15/98 5:17p Matt
 * Added new Base_directory variable.  Got rid of D3_LOCAL check and
 * 'local directory' registry variable.
 *
 * 35    8/13/98 6:34p Jason
 * made table file loading much faster
 *
 * 34    8/10/98 1:49p Samir
 * added music directory.
 *
 * 33    8/03/98 6:44p Jason
 * set custom graphics in the search path
 *
 * 32    7/27/98 6:25p Jeff
 * added creation of custom directories
 *
 * 31    6/23/98 2:43p Matt
 * Changed calls to OutrageMessageBox() & Debug_MessageBox() to deal with
 * int return value (instead of bool).
 *
 * 30    6/12/98 1:06p Jason
 * added smart loading from local table file
 *
 * 29    5/04/98 5:00p Keneta
 * FROM JASON:Fixed copyfile bug
 *
 * 28    5/04/98 4:42p Jason
 * even better error checking
 *
 * 26    5/04/98 4:24p Jason
 * upped MAX_TRIES
 *
 * 25    5/04/98 4:18p Jason
 * added assert to prevent table file problems
 *
 * 24    3/31/98 3:49p Jason
 * added memory lib
 *
 * 23    3/19/98 3:51p Samir
 * added misc data directory.
 *
 * 22    2/23/98 2:00p Jason
 * Pop up a message box when table file couldn't be opened
 *
 * 21    2/06/98 12:15p Jason
 * upped max times program will try to delete the table file before
 * bailing
 *
 * 20    2/04/98 11:47a Jason
 * added dynamic description field to generic pages
 *
 * 19    1/26/98 11:32a Jason
 * upped the number of times the system will try to delete a table file
 *
 * 18    1/22/98 2:49p Samir
 * Added D3 Local Dir to the search path.
 *
 * 17    1/15/98 6:22p Jason
 * added safety checks so the network won't copy over a primitive you have
 * held locally
 *
 * 16    1/15/98 4:54p Mark
 * FROM JASON:Do switcheroo a few times before giving up
 *
 * 15    12/22/97 3:50p Chris
 *
 * 14    11/17/97 4:16p Jason
 * added briefings directory
 *
 * 13    9/09/97 4:07p Matt
 * Added mprintf()
 *
 * 12    9/04/97 2:53p Samir
 * Added gamefile and generic page strings to PageNames array.
 *
 * 11    8/12/97 12:47p Matt
 * Only copy pagefile from net if different from local copy.
 * When loading pages, print different char for each type
 * Show how long it took to load the pagefile
 *
 * 10    8/11/97 1:54p Matt
 * Ripped out robot & powerup pages, and added generic page
 *
 * 9     8/08/97 5:17p Jason
 * made it so that when you update from the network it doesn't halt other
 * users
 *
 * 8     8/08/97 3:44p Jason
 * added code to support new generic page
 *
 * 7     8/08/97 1:57p Matt
 * Took out error message now handled by mng_MakeLocker()
 *
 * 6     7/29/97 12:07p Jason
 * added gamefile page for auto retrieval of non-standard page types
 *
 * 50    6/27/97 3:11p Jason
 * added room directories
 *
 *
 * 49    6/11/97 1:07p Samir
 * The removal of gameos and replaced with oeApplication, oeDatabase
 *
 * 48    6/10/97 5:08p Jason
 * added reorderpages menu item
 *
 * 47    6/05/97 2:52p Jason
 * added megacell functions
 *
 * 46    5/30/97 11:41a Jason
 * made a better error message if someone already has the table file
 * locked upon startup
 *
 * 45    5/22/97 3:08p Jason
 * added the ReorderPage function
 *
 * 44    5/16/97 3:53p Jason
 * added filepage dialog
 *
 * 43    5/15/97 5:56 PM Jeremy
 * made initlocaltable files check if the file exists by using cfexist
 * rather than trying to open the file and checking the error code
 *
 * 42    5/14/97 6:38p Jason
 * fixed a plethora of potential problems by locking the table file when
 * someone is starting up.
 *
 * 41    5/14/97 6:44 PM Jeremy
 * fixed a bug where local dir backup directory was not being set
 * correctly in init local table files
 *
 * 40    5/13/97 3:41p Jason
 * made all manage code work with the new device independant database
 *
 * 39    5/08/97 12:41p Jason
 * made manage system work with device dependant path names
 *
 * 38    4/29/97 5:07p Samir
 * Added levels directory to search path
 *
 * 37    4/25/97 6:16p Jason
 * added switcheroo function
 *
 * 36    4/01/97 2:13p Jason
 * changes for sound page functionality
 *
 * 35    3/31/97 4:35p Jason
 * added player ship and weapon pages
 *
 * 34    3/25/97 3:10p Jason
 * added robots and robot page functionality
 *
 * 33    3/17/97 4:27p Jason
 * added sounds directory to path list
 *
 * 32    3/14/97 7:18p Matt
 * Added missing include
 *
 * 31    3/14/97 6:13 PM Jeremy
 * changed calls to windows "MessageBox" to OutrageMessageBox, changed
 * call of GetUserName to os_database->get_user_name, #included descent.h
 * in order to refer to the OS_database object, unincluded <windows.h> and
 * <direct.h>
 *
 * 30    3/13/97 7:39p Matt
 * Changed code to use getenv() (ANSI-standard) instead of
 * GetEnvironmentVariable()
 *
 * 29    3/13/97 12:34p Matt
 * Changed code to not leave directory changed after checking for presence
 * of a directory.
 *
 * 28    3/13/97 11:37a Samir
 * Changed os file functions to ddio file functions
 *
 * 27    3/10/97 2:23p Jason
 * added auto creation of models directory
 *
 * 26    3/07/97 1:02p Jason
 * Now uses Samir's OS specific directory functions
 *
 * 25    3/05/97 3:10p Jason
 * added more door functionality
 *
 * 24    3/05/97 12:16p Jason
 * added code to support our new 3d doors
 *
 * 23    3/03/97 6:21p Matt
 * Changed cfile functions to use D3 naming convention
 *
 * $NoKeywords: $
 */

#include <cstdarg>
#include <cstdio>

#include <stdlib.h>
#include <errno.h>
#include <string.h>
#if defined(__LINUX__)
#include "linux_fix.h"
#endif
#include "descent.h"
#include "manage.h"
#include "pserror.h"
#include "gametexture.h"
#include "texpage.h"
#include "doorpage.h"
#include "soundpage.h"
#include "megapage.h"
#include "shippage.h"
#include "weaponpage.h"
#include "gamefilepage.h"
#include "mono.h"
#include "object.h"
#include "ddio.h"
#include "cfile.h"
#include "appdatabase.h"
#include "genericpage.h"
#include "mem.h"
#include "dedicated_server.h"
#include "appconsole.h"
#include "init.h"
#include "stringtable.h"
#include "args.h"
#include "vclip.h"
#include "polymodel.h"
int Old_table_method = 0;
void mng_WriteNewUnknownPage(CFILE *outfile);
//	This is for levels
char LocalLevelsDir[TABLE_NAME_LEN];
//	This is for pages
char TableLockFilename[TABLE_NAME_LEN], TableFilename[TABLE_NAME_LEN];
char TempTableLockFilename[TABLE_NAME_LEN], TempTableFilename[TABLE_NAME_LEN];
char LocalTableFilename[TABLE_NAME_LEN], LocalTempTableFilename[TABLE_NAME_LEN];
char BackupTableFilename[TABLE_NAME_LEN], BackupLockFilename[TABLE_NAME_LEN];
char ManageGraphicsDir[TABLE_NAME_LEN], LocalManageGraphicsDir[TABLE_NAME_LEN];
char LocalModelsDir[TABLE_NAME_LEN], NetModelsDir[TABLE_NAME_LEN];
char LocalSoundsDir[TABLE_NAME_LEN], NetSoundsDir[TABLE_NAME_LEN];
char LocalRoomsDir[TABLE_NAME_LEN], NetRoomsDir[TABLE_NAME_LEN];
char LocalBriefingDir[TABLE_NAME_LEN], NetBriefingDir[TABLE_NAME_LEN];
char LocalScriptDir[TABLE_NAME_LEN], NetScriptDir[TABLE_NAME_LEN];
char LocalMiscDir[TABLE_NAME_LEN], NetMiscDir[TABLE_NAME_LEN];
char LocalArtDir[TABLE_NAME_LEN], NetArtDir[TABLE_NAME_LEN];
char LocalMusicDir[TABLE_NAME_LEN], NetMusicDir[TABLE_NAME_LEN];
char LocalVoiceDir[TABLE_NAME_LEN], NetVoiceDir[TABLE_NAME_LEN];
char NetTableDir[TABLE_NAME_LEN], LocalTableDir[TABLE_NAME_LEN];
char LocalD3Dir[TABLE_NAME_LEN], NetD3Dir[TABLE_NAME_LEN];
char LocalCustomGraphicsDir[TABLE_NAME_LEN];
char LocalCustomSoundsDir[TABLE_NAME_LEN];
char LockerFile[TABLE_NAME_LEN];
char VersionFile[TABLE_NAME_LEN];
char TableUser[TABLE_NAME_LEN];
char ErrorString[INFO_STRING_LEN], InfoString[INFO_STRING_LEN];
mngs_track_lock GlobalTrackLocks[MAX_TRACKLOCKS];
bool Use_old_update_method = false;
char *TablefileNameOverride = NULL;
// Only valid when first starting the editor
#define MAX_LOCKLIST_ELEMENTS 1000
mngs_Pagelock *LockList;
int Num_locklist, Starting_editor = 0, Loading_locals = 0, Fast_load_trick = 0;
#define PRIMTYPE_OOF 0
#define PRIMTYPE_OGF 1
#define PRIMTYPE_WAV 2
#define PRIMTYPE_OAF 3
#define PRIMTYPE_FILE 4
#if defined(WIN32)
FILETIME TableTimeThreshold;
// Builds a list of old files so we know which ones to update
// Searches through all our netdirectories for old files
void BuildOldFileList(FILETIME threshold);
#endif
struct old_file {
  uint8_t type;
  char name[PAGENAME_LEN];
};
#define MAX_OLDFILE_ELEMENTS 10000
int Num_old_files = 0;
old_file *OldFiles;
const char *PageNames[] = {"Unknown",     "Texture", "Weapon",   "Robot", "Powerup",        "Door",
                     "Player ship", "Sound",   "Megacell", "Files", "Generic objects"};
#ifndef RELEASE
int Network_up = 1;
int Stand_alone = 0;
#else
int Network_up = 0;
int Stand_alone = 1;
#endif
void mng_BackupTableFile();
// returns 1 if network is up, 0 if down
int mng_IsNetworkUp() {
  char dir[100];
  int ret;
  if (Stand_alone)
    return 0;

  char net_dir[255] = {0};
  int dirlen = 255;
  Database()->read("net directory", net_dir, &dirlen);
  if (net_dir[0] == 0)
    return 0;
  ddio_MakePath(dir, net_dir, "data", NULL);

  ret = ddio_CreateDir(dir);
  if (!ret) {
    char old_dir[100];
    ddio_GetWorkingDir(old_dir, 100);
    if (!ddio_SetWorkingDir(dir))
      return 0; // network down
    else {
      ddio_SetWorkingDir(old_dir); // restore directory
      return 1;                    // directory is already there
    }
  }

  return 1;
}
void ReorderPages(int);
// #define JASONS_REORDERING
void Read256TextureNames();
// Sets up our table files, get their filenames, etc.
// Returns 1 on success, zero on error
int mng_InitTableFiles() {
  size_t size = TABLE_NAME_LEN;
  int answer;
  Database()->get_user_name(TableUser, &size);
  if (FindArg("-filter"))
    Use_old_update_method = true;
  // Read256TextureNames ();

  if (FindArg("-oldmethod"))
    Use_old_update_method = true;
  if (mng_IsNetworkUp()) {
#ifndef RELEASE
    answer = OutrageMessageBox(MBOX_YESNO, "Do you wish to update your data files from the network?\n(If NO is "
                                           "selected then you will have to restart to use networking functions)");
#else
    answer = IDNO;
#endif
    if (answer == IDNO)
      Network_up = 0;
    else {
      Network_up = 1;
#ifndef RELEASE
#if defined(WIN32)
      if (cfexist("c:\\edload"))
        Use_old_update_method = true;
      else {
        CFILE *fp = cfopen("c:\\edload", "wt");
        cfclose(fp);
      }
#endif
#endif
    }
  } else {
    mprintf(0, "Network is down...\n");
    Network_up = 0;
  }

  if (Network_up == 0) {
    mng_InitLocalTables();
    mng_InitLocalDirectories();
    mng_CheckToCreateLocalTables();
    mng_InitTrackLocks();
  } else {
    // Do locals
    mng_InitLocalTables();
    mng_InitLocalDirectories();
    mng_CheckToCreateLocalTables();

    // Do network
    mng_InitNetTables();
    mng_InitNetDirectories();
    mng_CheckToCreateNetTables();
    mng_BackupTableFile();
    mng_InitPagelocks();
    mng_InitTrackLocks();
#ifdef JASONS_REORDERING
    ReorderPages(0);
    return 0;
#endif
  }
  return 1;
}
// Loads our tables
int mng_LoadTableFiles(int show_progress) {
  if (Network_up) {
    LockList = (mngs_Pagelock *)mem_malloc(MAX_LOCKLIST_ELEMENTS * sizeof(mngs_Pagelock));
    Num_locklist = mng_GetListOfLocks(LockList, MAX_LOCKLIST_ELEMENTS, TableUser);
    OldFiles = (old_file *)mem_malloc(MAX_OLDFILE_ELEMENTS * sizeof(old_file));
    Num_old_files = 0;
    ASSERT(OldFiles);
#if defined(WIN32)
    if (TableTimeThreshold.dwHighDateTime != -1)
      BuildOldFileList(TableTimeThreshold);
#endif

    Starting_editor = 1;
  }
  int ret1, ret2;
  if (Fast_load_trick && !FindArg("-filter"))
    Network_up = 0;

  ret1 = mng_LoadNetPages(show_progress);
  if (Fast_load_trick) {
    Network_up = 1;
    Fast_load_trick = 0;
  }
  ret2 = mng_LoadLocalPages();
  if (Network_up) {
    Starting_editor = 0;
    Num_locklist = 0;
    Num_old_files = 0;
    mem_free(OldFiles);
    mem_free(LockList);
#ifndef RELEASE
#if defined(WIN32)
    remove("c:\\edload");
#endif
#endif
  }
  RemapEverything();

  if (!ret1 || !ret2)
    return 0;
  return 1;
}
// This is for initting tables on STAND_ALONE, if the network is down, or if
// the user doesn't want network support
int mng_InitLocalTables() {
  // Set the local table directory from the base directory
  strcpy(LocalD3Dir, Base_directory);
  mprintf(1, "Local dir:%s\n", LocalD3Dir);

  // Make the CFILE system first look at our local directories.  If the goods aren't
  // found there, try out on the network
  ddio_MakePath(LocalTableDir, LocalD3Dir, "data", "tables", NULL);
  ddio_MakePath(LocalManageGraphicsDir, LocalD3Dir, "data", "graphics", NULL);
  ddio_MakePath(LocalModelsDir, LocalD3Dir, "data", "models", NULL);
  ddio_MakePath(LocalSoundsDir, LocalD3Dir, "data", "sounds", NULL);
  ddio_MakePath(LocalCustomSoundsDir, LocalD3Dir, "custom", "sounds", NULL);
  ddio_MakePath(LocalCustomGraphicsDir, LocalD3Dir, "custom", "graphics", NULL);
  ddio_MakePath(LocalRoomsDir, LocalD3Dir, "data", "rooms", NULL);
  ddio_MakePath(LocalBriefingDir, LocalD3Dir, "data", "briefings", NULL);
  ddio_MakePath(LocalScriptDir, LocalD3Dir, "data", "scripts", NULL);
  ddio_MakePath(LocalMiscDir, LocalD3Dir, "data", "misc", NULL);
  ddio_MakePath(LocalArtDir, LocalD3Dir, "data", "art", NULL);
  ddio_MakePath(LocalMusicDir, LocalD3Dir, "data", "music", NULL);
  ddio_MakePath(LocalVoiceDir, LocalD3Dir, "data", "voice", NULL);
  ddio_MakePath(LocalLevelsDir, LocalD3Dir, "data", "levels", NULL);
  cf_SetSearchPath(LocalD3Dir, NULL);
#ifndef RELEASE
  cf_SetSearchPath(LocalLevelsDir, NULL);
  cf_SetSearchPath(LocalTableDir, NULL); // Local table directory

  cf_SetSearchPath(LocalManageGraphicsDir, NULL);
  cf_SetSearchPath(LocalModelsDir, NULL);
  cf_SetSearchPath(LocalSoundsDir, NULL);
  cf_SetSearchPath(LocalRoomsDir, NULL);
  cf_SetSearchPath(LocalBriefingDir, NULL);
  cf_SetSearchPath(LocalScriptDir, "cpp", "dll", "def", "msg", "so", "msl", "dylib", NULL);
  cf_SetSearchPath(LocalMiscDir, NULL);
  cf_SetSearchPath(LocalArtDir, NULL);
  cf_SetSearchPath(LocalMusicDir, NULL);
  cf_SetSearchPath(LocalVoiceDir, NULL);
#endif

  if (Network_up) {
    ddio_MakePath(LocalTableFilename, LocalTableDir, LOCAL_TABLE, NULL);
    ddio_MakePath(LocalTempTableFilename, LocalTableDir, TEMP_LOCAL_TABLE, NULL);
  } else {
    strcpy(LocalTableFilename, LOCAL_TABLE);
    strcpy(LocalTempTableFilename, TEMP_LOCAL_TABLE);
  }

  return 1;
}
int mng_InitNetTables() {
  char dir[255];
  int dirlen = 255;
  Database()->read("net directory", dir, &dirlen);
  if (dir[0] == 0)
    Error("D3_DIR environment variable not set.");

  strcpy(NetD3Dir, dir);
  mprintf(1, "Net dir:%s\n", NetD3Dir);
  ddio_MakePath(NetModelsDir, NetD3Dir, "data", "models", NULL);
  ddio_MakePath(NetSoundsDir, NetD3Dir, "data", "sounds", NULL);
  ddio_MakePath(NetRoomsDir, NetD3Dir, "data", "rooms", NULL);
  ddio_MakePath(NetBriefingDir, NetD3Dir, "data", "briefings", NULL);
  ddio_MakePath(NetScriptDir, NetD3Dir, "data", "scripts", NULL);
  ddio_MakePath(NetMiscDir, NetD3Dir, "data", "misc", NULL);
  ddio_MakePath(ManageGraphicsDir, NetD3Dir, "data", "graphics", NULL);
  ddio_MakePath(NetTableDir, NetD3Dir, "data", "tables", NULL);
  ddio_MakePath(NetArtDir, NetD3Dir, "data", "art", NULL);
  ddio_MakePath(NetMusicDir, NetD3Dir, "data", "music", NULL);
  ddio_MakePath(NetVoiceDir, NetD3Dir, "data", "voice", NULL);
  ddio_MakePath(TableLockFilename, NetTableDir, "table.lok", NULL);
  ddio_MakePath(BackupLockFilename, NetTableDir, "tablelok.bak", NULL);
  ddio_MakePath(BackupTableFilename, NetTableDir, "table.bak", NULL);
  ddio_MakePath(TableFilename, NetTableDir, NET_TABLE, NULL);
  ddio_MakePath(TempTableLockFilename, NetTableDir, "lock.tmp", NULL);
  ddio_MakePath(TempTableFilename, NetTableDir, TEMP_NET_TABLE, NULL);
  ddio_MakePath(LockerFile, NetTableDir, "locker", NULL);
  ddio_MakePath(VersionFile, NetTableDir, "TableVersion", NULL);

  cf_SetSearchPath(ManageGraphicsDir, NULL);
  cf_SetSearchPath(NetModelsDir, NULL);
  cf_SetSearchPath(NetSoundsDir, NULL);
  cf_SetSearchPath(NetRoomsDir, NULL);
  cf_SetSearchPath(NetMiscDir, NULL);
  cf_SetSearchPath(NetMusicDir, NULL);
  cf_SetSearchPath(NetVoiceDir, NULL);
  return 1;
}
void mng_CheckToCreateNetTables() {
  CFILE *infile, *outfile;

  ASSERT(Stand_alone != 1);

  infile = (CFILE *)cfopen(TableFilename, "rb");
  if (infile == NULL) {
    if (errno == ENOENT) {
      outfile = (CFILE *)cfopen(TableFilename, "wb");
      if (!outfile) {
        mprintf(0, "Error creating table file! The network must be down...\n");
        Network_up = 0;
      } else {
        mng_WriteNewUnknownPage(outfile);
        cfclose(outfile);
      }
    } else {
      mprintf(0, "Error creating table file! The network must be down...\n");
      Network_up = 0;
    }
  }

  if (infile)
    cfclose(infile);
}
// Checks to see if there is a table file...if not, create one with a dummy page
void mng_CheckToCreateLocalTables() {
  CFILE *outfile;

  if (!Network_up) {
    strcpy(TableFilename, NET_TABLE);
    mprintf(0, "table filename = %s\n", TableFilename);
    return;
  }

  if (!cfexist(LocalTableFilename)) {
    outfile = (CFILE *)cfopen(LocalTableFilename, "wb");
    if (!outfile) {
      Error("Error creating local table file!");
      return;
    } else {
      mng_WriteNewUnknownPage(outfile);
      cfclose(outfile);
    }
  }
}
// Creates directories if needed
void mng_InitLocalDirectories() {
  char dir[255];
  ddio_MakePath(dir, LocalD3Dir, "custom", NULL);
  ddio_CreateDir(dir);
  ddio_MakePath(dir, LocalD3Dir, "custom", "graphics", NULL);
  ddio_CreateDir(dir);
  ddio_MakePath(dir, LocalD3Dir, "custom", "sounds", NULL);
  ddio_CreateDir(dir);
  ddio_MakePath(dir, LocalD3Dir, "custom", "cache", NULL);
  ddio_CreateDir(dir);
  ddio_MakePath(dir, LocalD3Dir, "custom", "settings", NULL);
  ddio_CreateDir(dir);
  cf_SetSearchPath(LocalCustomGraphicsDir, NULL);
  cf_SetSearchPath(LocalCustomSoundsDir, NULL);

  if (Network_up) {
    ddio_MakePath(dir, LocalD3Dir, "data", NULL);
    ddio_CreateDir(dir);

    ddio_MakePath(dir, LocalD3Dir, "data", "tables", NULL);
    ddio_CreateDir(dir);

    ddio_MakePath(dir, LocalD3Dir, "data", "graphics", NULL);
    ddio_CreateDir(dir);
    ddio_MakePath(dir, LocalD3Dir, "data", "sounds", NULL);
    ddio_CreateDir(dir);
    ddio_MakePath(dir, LocalD3Dir, "data", "rooms", NULL);
    ddio_CreateDir(dir);
    ddio_MakePath(dir, LocalD3Dir, "data", "levels", NULL);
    ddio_CreateDir(dir);
    ddio_MakePath(dir, LocalD3Dir, "data", "models", NULL);
    ddio_CreateDir(dir);
    ddio_MakePath(dir, LocalD3Dir, "data", "briefings", NULL);
    ddio_CreateDir(dir);
    ddio_MakePath(dir, LocalD3Dir, "data", "scripts", NULL);
    ddio_CreateDir(dir);
    ddio_MakePath(dir, LocalD3Dir, "data", "misc", NULL);
    ddio_CreateDir(dir);
    ddio_MakePath(dir, LocalD3Dir, "data", "art", NULL);
    ddio_CreateDir(dir);
    ddio_MakePath(dir, LocalD3Dir, "data", "music", NULL);
    ddio_CreateDir(dir);
    ddio_MakePath(dir, LocalD3Dir, "data", "voice", NULL);
    ddio_CreateDir(dir);
  }
}
void mng_InitNetDirectories() {
  char dir[255];

  if (Stand_alone)
    return;
  ddio_MakePath(dir, NetD3Dir, "data", NULL);
  ddio_CreateDir(dir);

  ddio_MakePath(dir, NetD3Dir, "data", "tables", NULL);
  ddio_CreateDir(dir);
  ddio_MakePath(dir, NetD3Dir, "data", "graphics", NULL);
  ddio_CreateDir(dir);
  ddio_MakePath(dir, NetD3Dir, "data", "sounds", NULL);
  ddio_CreateDir(dir);
  ddio_MakePath(dir, NetD3Dir, "data", "rooms", NULL);
  ddio_CreateDir(dir);
  ddio_MakePath(dir, NetD3Dir, "data", "levels", NULL);
  ddio_CreateDir(dir);
  ddio_MakePath(dir, NetD3Dir, "data", "models", NULL);
  ddio_CreateDir(dir);
  ddio_MakePath(dir, NetD3Dir, "data", "briefings", NULL);
  ddio_CreateDir(dir);
  ddio_MakePath(dir, NetD3Dir, "data", "scripts", NULL);
  ddio_CreateDir(dir);
  ddio_MakePath(dir, NetD3Dir, "data", "misc", NULL);
  ddio_CreateDir(dir);
  ddio_MakePath(dir, NetD3Dir, "data", "art", NULL);
  ddio_CreateDir(dir);
  ddio_MakePath(dir, NetD3Dir, "data", "music", NULL);
  ddio_CreateDir(dir);
  ddio_MakePath(dir, NetD3Dir, "data", "voice", NULL);
  ddio_CreateDir(dir);
}
extern int TableVersionCurrent();
#if !defined(WIN32)
void mng_BackupTableFile() {}
#else
void mng_BackupTableFile() {
  char str[200];
  Fast_load_trick = 0;
  if (!TableVersionCurrent()) {
    Error("You must do a source update and recompile.  The data on the network is newer that your sourcecode.");
    return;
  }

  ddio_MakePath(str, LocalTableDir, NET_TABLE, NULL);
  if (!cfexist(str)) {
    TableTimeThreshold.dwHighDateTime = 0;
    TableTimeThreshold.dwLowDateTime = 0;
  } else {
    WIN32_FIND_DATA filedata;
    HANDLE filehandle = FindFirstFile(str, &filedata);
    if (filehandle == INVALID_HANDLE_VALUE) {
      Error("Couldn't open net table file for some reason!");
      return;
    }
    TableTimeThreshold = filedata.ftLastWriteTime;
    FindClose(filehandle);
  }

  if (!cfexist(str) || cf_Diff(str, TableFilename)) {
    mprintf(0, "Making local copy of table file.\n");

    if (!cf_CopyFile(str, TableFilename, 1))
      Error("There was an error making a backup copy of the table file.\n");
    ddio_MakePath(str, LocalTableDir, "tablelok.loc", NULL);
    if (!cf_CopyFile(str, TableLockFilename, 1))
      Error("There was an error making a backup copy of the locker table file.\n");
  } else {
    mprintf(0, "Local table file same as network copy.\n");
    TableTimeThreshold.dwHighDateTime = -1;
    Fast_load_trick = 1;
  }
}
#endif
void mng_WriteUnknownPage(CFILE *outfile) {
  // Function for writing out "undefined" page...useful for placeholding
  cf_WriteByte(outfile, PAGETYPE_UNKNOWN);
}
void mng_WriteNewUnknownPage(CFILE *outfile) {
  // Function for writing out "undefined" page...useful for placeholding
  int offset = StartManagePage(outfile, PAGETYPE_UNKNOWN);
  EndManagePage(outfile, offset);
}
// Clear out tracklocks
void mng_InitTrackLocks() {
  for (int i = 0; i < MAX_TRACKLOCKS; i++) {
    GlobalTrackLocks[i].used = 0;
    GlobalTrackLocks[i].pagetype = PAGETYPE_UNKNOWN;
    GlobalTrackLocks[i].name[0] = 0;
  }
}
// Given a name, returns the index of the tracklock with that name
// -1 indicates that it wasn't found
int mng_FindTrackLock(char *name, int pagetype) {
  int i;
  for (i = 0; i < MAX_TRACKLOCKS; i++) {
    if (GlobalTrackLocks[i].used && GlobalTrackLocks[i].pagetype == pagetype &&
        !stricmp(name, GlobalTrackLocks[i].name))
      return i;
  }
  return -1;
}
// Searches through global array of tracklocks and returns first free one
// Sets the tracklock to be named "name" and its type "pagetype"
// returns -1 if none free
int mng_AllocTrackLock(char *name, int pagetype) {
  int i;
  for (i = 0; i < MAX_TRACKLOCKS; i++)
    if (GlobalTrackLocks[i].used == 0) {
      strcpy(GlobalTrackLocks[i].name, name);
      GlobalTrackLocks[i].pagetype = pagetype;
      GlobalTrackLocks[i].used = 1;
      mprintf(0, "Tracklock %s allocated.\n", name);
      return i;
    }
  Error("Couldn't get a free tracklock!");
  return -1;
}
// Frees a tracklock
void mng_FreeTrackLock(int n) {
  mprintf(0, "Tracklock %s freed.\n", GlobalTrackLocks[n].name);
  GlobalTrackLocks[n].pagetype = PAGETYPE_UNKNOWN;
  GlobalTrackLocks[n].used = 0;
  GlobalTrackLocks[n].name[0] = 0;
}
// Displays all the network locks of "name"
void mng_DisplayLockList(char *name) {
  mngs_Pagelock list[100];
  char temp[200];
  int max = 100;
  int num, i;
  int length = 0;
  char str[5000];
#ifndef RELEASE
  // Get the list
  if ((num = mng_GetListOfLocks(list, max, name)) < 0) {
    OutrageMessageBox(MBOX_OK, ErrorString);
    return;
  } else if (num == 0) {
    OutrageMessageBox(MBOX_OK, "User has no pages locked.");
    return;
  }

  // Make a large string with all the info in it
  snprintf(str, sizeof(str), "User %s has the following pages locked:\n\n", TableUser);
  for (i = 0; i < num; i++) {
    snprintf(temp, sizeof(temp), "%s:%s", PageNames[list[i].pagetype], list[i].name);
    strncat(str, temp, sizeof(str) - strlen(str) - 1);
    strncat(str, "\n", sizeof(str) - strlen(str) - 1);
    length += strlen(temp);
    if (length > 5000 - 100)
      break;
  }
  // Display that string
  OutrageMessageBox(MBOX_OK, str);
#endif
}
// Declare these here because it's too big to put on the stack on the Mac
static mngs_texture_page texpage;
static mngs_door_page doorpage;
static mngs_generic_page genericpage;
static mngs_sound_page soundpage;
static mngs_megacell_page megacellpage;
static mngs_ship_page shippage;
static mngs_weapon_page weaponpage;
static mngs_gamefile_page gamefilepage;
// IF YOU ADD ANY NEW PAGETYPE YOU MUST CHANGE THE FUNCTIONS LISTED UNDER THIS LINE
// TO DEAL WITH YOUR PAGE TYPE.  IF YOU FORGET, YOU CAN CORRUPT THE PAGEFILE!!!!!
//------------------------------------------------------------------------------
// Given a pagetype, reads it in but discards it.  Useful for parsing.
void mng_ReadDummyPage(CFILE *infile, uint8_t pagetype) {
  switch (pagetype) {
  case PAGETYPE_TEXTURE:
    mng_ReadNewTexturePage(infile, &texpage);
    break;
  case PAGETYPE_POWERUP:
  case PAGETYPE_ROBOT:
    Error("Your local table file is invalid.  You must update from the network.");
    break;
  case PAGETYPE_DOOR:
    mng_ReadNewDoorPage(infile, &doorpage);
    break;
  case PAGETYPE_GENERIC:
    mng_ReadNewGenericPage(infile, &genericpage);
    if (genericpage.objinfo_struct.description != NULL) {
      mem_free(genericpage.objinfo_struct.description);
      genericpage.objinfo_struct.description = NULL;
    }
    break;
  case PAGETYPE_GAMEFILE:
    mng_ReadNewGamefilePage(infile, &gamefilepage);
    break;
  case PAGETYPE_SOUND:
    mng_ReadNewSoundPage(infile, &soundpage);
    break;
  case PAGETYPE_SHIP:
    mng_ReadNewShipPage(infile, &shippage);
    break;
  case PAGETYPE_WEAPON:
    mng_ReadNewWeaponPage(infile, &weaponpage);
    break;
  case PAGETYPE_MEGACELL:
    mng_ReadNewMegacellPage(infile, &megacellpage);
    break;
  case PAGETYPE_UNKNOWN:
    break;
  default:
    Int3(); // unrecognized pagetype
    break;
  }
}
// Reads a page in that we don't care about, and writes it right back out
// This is useful for replacing a specific page in a file but ignoring others
void mng_ReadWriteDummyPage(CFILE *infile, CFILE *outfile, uint8_t pagetype) {
  switch (pagetype) {
  case PAGETYPE_TEXTURE:
    // Read it in, write it out.
    mng_ReadNewTexturePage(infile, &texpage);
    mng_WriteNewTexturePage(outfile, &texpage);
    break;
  case PAGETYPE_DOOR:
    // Read it in, write it out.
    mng_ReadNewDoorPage(infile, &doorpage);
    mng_WriteNewDoorPage(outfile, &doorpage);
    break;
  case PAGETYPE_GENERIC:
    // Read it in, write it out.
    mng_ReadNewGenericPage(infile, &genericpage);
    mng_WriteNewGenericPage(outfile, &genericpage);
    if (genericpage.objinfo_struct.description != NULL) {
      mem_free(genericpage.objinfo_struct.description);
      genericpage.objinfo_struct.description = NULL;
    }
    break;
  case PAGETYPE_GAMEFILE:
    // Read it in, write it out.
    mng_ReadNewGamefilePage(infile, &gamefilepage);
    mng_WriteNewGamefilePage(outfile, &gamefilepage);
    break;
  case PAGETYPE_SOUND:
    // Read it in, write it out.
    mng_ReadNewSoundPage(infile, &soundpage);
    mng_WriteNewSoundPage(outfile, &soundpage);
    break;
  case PAGETYPE_MEGACELL:
    // Read it in, write it out.
    mng_ReadNewMegacellPage(infile, &megacellpage);
    mng_WriteNewMegacellPage(outfile, &megacellpage);
    break;
  case PAGETYPE_SHIP:
    // Read it in, write it out.
    mng_ReadNewShipPage(infile, &shippage);
    mng_WriteNewShipPage(outfile, &shippage);
    break;
  case PAGETYPE_WEAPON:
    // Read it in, write it out.
    mng_ReadNewWeaponPage(infile, &weaponpage);
    mng_WriteNewWeaponPage(outfile, &weaponpage);
    break;
  case PAGETYPE_UNKNOWN:
    mng_WriteNewUnknownPage(outfile);
    break;
  default:
    Int3(); // unrecognized pagetype
    break;
  }
}
// Renames a page on the network
// This function is called when you rename your object, regardless if you check
// it in
int mng_RenamePage(char *oldname, char *newname, int pagetype) {
  int l, i;
  mngs_Pagelock pl;
  char oname[PAGENAME_LEN];

  mprintf(0, "Renaming %s to %s...\n", oldname, newname);
  strcpy(oname, oldname);
  strcpy(pl.name, oname);
  pl.pagetype = pagetype;
  // Make sure we own it
  l = mng_CheckIfPageOwned(&pl, TableUser);
  ASSERT(l == 1);
  strcpy(pl.name, newname);
  strcpy(pl.holder, TableUser);

  // First, change the name of the network pagelock
  l = mng_ReplacePagelock(oname, &pl);
  ASSERT(l == 1);
  switch (pagetype) {
  // Find the page type with this name and rename it
  case PAGETYPE_TEXTURE:
    i = FindTextureName(oname);
    ASSERT(i != -1);
    strcpy(GameTextures[i].name, newname);

    l = mng_ReplacePage(oname, GameTextures[i].name, i, PAGETYPE_TEXTURE, 0);
    ASSERT(l == 1);
    if (mng_FindTrackLock(oname, PAGETYPE_TEXTURE) != -1)
      mng_ReplacePage(oname, GameTextures[i].name, i, PAGETYPE_TEXTURE, 1);

    break;
  case PAGETYPE_DOOR:
    i = FindDoorName(oname);
    ASSERT(i != -1);
    strcpy(Doors[i].name, newname);
    l = mng_ReplacePage(oname, Doors[i].name, i, PAGETYPE_DOOR, 0);
    if (mng_FindTrackLock(oname, PAGETYPE_DOOR) != -1)
      mng_ReplacePage(oname, Doors[i].name, i, PAGETYPE_DOOR, 1);
    ASSERT(l == 1);
    break;
  case PAGETYPE_GENERIC:
    i = FindObjectIDName(oname);
    ASSERT(i != -1);
    strcpy(Object_info[i].name, newname);

    l = mng_ReplacePage(oname, Object_info[i].name, i, PAGETYPE_GENERIC, 0);

    if (mng_FindTrackLock(oname, PAGETYPE_GENERIC) != -1)
      mng_ReplacePage(oname, Object_info[i].name, i, PAGETYPE_GENERIC, 1);

    ASSERT(l == 1);
    break;
  case PAGETYPE_GAMEFILE:
    i = FindGamefileName(oname);
    ASSERT(i != -1);
    strcpy(Gamefiles[i].name, newname);

    l = mng_ReplacePage(oname, Gamefiles[i].name, i, PAGETYPE_GAMEFILE, 0);
    if (mng_FindTrackLock(oname, PAGETYPE_GAMEFILE) != -1)
      mng_ReplacePage(oname, Gamefiles[i].name, i, PAGETYPE_GAMEFILE, 1);
    ASSERT(l == 1);
    break;
  case PAGETYPE_SOUND:
    i = FindSoundName(oname);
    ASSERT(i != -1);
    strcpy(Sounds[i].name, newname);
    l = mng_ReplacePage(oname, Sounds[i].name, i, PAGETYPE_SOUND, 0);
    if (mng_FindTrackLock(oname, PAGETYPE_SOUND) != -1)
      mng_ReplacePage(oname, Sounds[i].name, i, PAGETYPE_SOUND, 1);
    ASSERT(l == 1);
    break;
  case PAGETYPE_MEGACELL:
    i = FindMegacellName(oname);
    ASSERT(i != -1);
    strcpy(Megacells[i].name, newname);
    l = mng_ReplacePage(oname, Megacells[i].name, i, PAGETYPE_MEGACELL, 0);

    if (mng_FindTrackLock(oname, PAGETYPE_MEGACELL) != -1)
      mng_ReplacePage(oname, Megacells[i].name, i, PAGETYPE_MEGACELL, 1);
    ASSERT(l == 1);
    break;
  case PAGETYPE_SHIP:
    i = FindShipName(oname);
    ASSERT(i != -1);
    strcpy(Ships[i].name, newname);

    l = mng_ReplacePage(oname, Ships[i].name, i, PAGETYPE_SHIP, 0);
    if (mng_FindTrackLock(oname, PAGETYPE_SHIP) != -1)
      mng_ReplacePage(oname, Ships[i].name, i, PAGETYPE_SHIP, 1);

    ASSERT(l == 1);
    break;
  case PAGETYPE_WEAPON:
    i = FindWeaponName(oname);
    ASSERT(i != -1);
    strcpy(Weapons[i].name, newname);

    l = mng_ReplacePage(oname, Weapons[i].name, i, PAGETYPE_WEAPON, 0);
    if (mng_FindTrackLock(oname, PAGETYPE_WEAPON) != -1)
      mng_ReplacePage(oname, Weapons[i].name, i, PAGETYPE_WEAPON, 1);
    ASSERT(l == 1);
    break;
  default:
    Int3(); // Unknown type, get Jason
    break;
  }
  return 1;
}
#define PROGRESS_PERCENTAGE_THRESHOLD 20
// This is the function that opens the table files and reads in the individual pages
// If you want your data to be in the game, it must hook into this function
int mng_LoadNetPages(int show_progress) {
  CFILE *infile;
  uint8_t pagetype;
  char tablename[TABLE_NAME_LEN];
  float start_time;
  int n_pages = 0;
  int total_bytes;
  int current_byte;
  float progress;
  int int_progress = 0;
  int len;

  mprintf(0, "Loading pages...");
  if (Dedicated_server)
    show_progress = 0; // turn off progress meter for dedicated server
  // If the network is up we still want to read from the local table because it
  // will allow others to start the game at the same time
  if (Network_up) {
    int farg = FindArg("-filter");
    if (farg)
      strcpy(tablename, GameArgs[farg + 1]);
    else {
      ddio_MakePath(tablename, LocalTableDir, NET_TABLE, NULL);
    }
    infile = cfopen(tablename, "rb");
  } else
    infile = cfopen(TableFilename, "rb");
  if (!infile) {
    mprintf(0, "Couldn't open table file (%s) to read pages!\n", TableFilename);
    Error("Cannot open table file <%s>", TableFilename);
    return 0;
  }
  if (show_progress) {
    cfseek(infile, 0, SEEK_END);
    total_bytes = cftell(infile);
    cfseek(infile, 0, SEEK_SET);
  }
  start_time = timer_GetTime();
  while (!cfeof(infile)) {
    // Read in a pagetype.  If its a page we recognize, load it
    //		mprintf(0,".");
    if (show_progress) {

      current_byte = cftell(infile);
      progress = (float)current_byte / (float)total_bytes;
      progress *= PROGRESS_PERCENTAGE_THRESHOLD;
      int temp_int_progress = progress;
      if (temp_int_progress > int_progress) {
        int_progress = temp_int_progress;
        InitMessage(TXT_INITDATA, progress / PROGRESS_PERCENTAGE_THRESHOLD);
      }
    }
    pagetype = cf_ReadByte(infile);
    if (!Old_table_method)
      len = cf_ReadInt(infile);
    switch (pagetype) {
    case PAGETYPE_TEXTURE:
      mprintf(0, "T");

      PrintDedicatedMessage("T");
      mng_LoadNetTexturePage(infile);
      break;
    case PAGETYPE_POWERUP:
    case PAGETYPE_ROBOT:
      Error("Your local table file is invalid.  You must update from the network.");
      break;
    case PAGETYPE_DOOR:
      mprintf(0, "D");
      PrintDedicatedMessage("D");
      mng_LoadNetDoorPage(infile);
      break;
    case PAGETYPE_GENERIC:
      mprintf(0, "G");
      PrintDedicatedMessage("G");
      mng_LoadNetGenericPage(infile);
      break;
    case PAGETYPE_GAMEFILE:
      mprintf(0, "F");
      PrintDedicatedMessage("F");
      mng_LoadNetGamefilePage(infile);
      break;
    case PAGETYPE_SOUND:
      mprintf(0, "S");
      PrintDedicatedMessage("S");
      mng_LoadNetSoundPage(infile);
      break;
    case PAGETYPE_SHIP:
      mprintf(0, "P");
      PrintDedicatedMessage("P");
      mng_LoadNetShipPage(infile);
      break;
    case PAGETYPE_WEAPON:
      mprintf(0, "W");
      PrintDedicatedMessage("W");
      mng_LoadNetWeaponPage(infile);
      break;
    case PAGETYPE_MEGACELL:
      mprintf(0, "M");
      PrintDedicatedMessage("M");
      mng_LoadNetMegacellPage(infile);
      break;
    case PAGETYPE_UNKNOWN:
      mprintf(0, "?");
      break;
    default:
      Int3(); // Unrecognized pagetype, possible corrupt data following
      return 0;
      break;
    }
    n_pages++;
  }
  mprintf(0, "\n%d pages read in %.1f seconds.\n", n_pages, timer_GetTime() - start_time);
  mprintf(0, "\n");
  PrintDedicatedMessage((0, "\nPage reading completed.\n"));

  cfclose(infile);

  // attempt to load extra.gam if found
  char name_override[256];
  strcpy(name_override, "extra.gam");
  infile = cfopen(name_override, "rb");
  if (!infile)
    return 1;

  mprintf(0, "==================================================\n");
  mprintf(0, "              Loading extra.gam                   \n");
  mprintf(0, "==================================================\n");
  PrintDedicatedMessage("\nLoading extra.gam.....\n");
  n_pages = 0;

  TablefileNameOverride = name_override;

  while (!cfeof(infile)) {
    pagetype = cf_ReadByte(infile);
    len = cf_ReadInt(infile);
    switch (pagetype) {
    case PAGETYPE_TEXTURE:
      mprintf(0, "T");
      PrintDedicatedMessage("T");
      mng_LoadNetTexturePage(infile, true);
      break;
    case PAGETYPE_DOOR:
      mprintf(0, "D");
      PrintDedicatedMessage("D");
      mng_LoadNetDoorPage(infile, true);
      break;
    case PAGETYPE_GENERIC:
      mprintf(0, "G");
      PrintDedicatedMessage("G");
      mng_LoadNetGenericPage(infile, true);
      break;
    case PAGETYPE_GAMEFILE:
      mprintf(0, "F");
      PrintDedicatedMessage("F");
      mng_LoadNetGamefilePage(infile, true);
      break;
    case PAGETYPE_SOUND:
      mprintf(0, "S");
      PrintDedicatedMessage("S");
      mng_LoadNetSoundPage(infile, true);
      break;
    case PAGETYPE_SHIP:
      mprintf(0, "P");
      PrintDedicatedMessage("P");
      mng_LoadNetShipPage(infile, true);
      break;
    case PAGETYPE_WEAPON:
      mprintf(0, "W");
      PrintDedicatedMessage("W");
      mng_LoadNetWeaponPage(infile, true);
      break;
    case PAGETYPE_UNKNOWN:
      mprintf(0, "?");
      break;
    default:
      Int3(); // Unrecognized pagetype, possible corrupt data following
      cfclose(infile);
      TablefileNameOverride = NULL;
      return 0;
      break;
    }
    n_pages++;
  }
  mprintf(0, "\n%d extra pages read.\n", n_pages);
  TablefileNameOverride = NULL;
  cfclose(infile);
  return 1;
}
// Loads and allocs all pages found locally
int mng_LoadLocalPages() {
  CFILE *infile;
  uint8_t pagetype;
  int len;

  mprintf(0, "Overlaying local pages...");
  infile = cfopen(LocalTableFilename, "rb");
  if (!infile) {
    mprintf(0, "Couldn't open local table file (%s) to read pages!\n", LocalTableFilename);
    return 1;
  }
  Loading_locals = 1;
  while (!cfeof(infile)) {
    // Read in a pagetype.  If its a page we recognize, load it

    pagetype = cf_ReadByte(infile);
    if (!Old_table_method)
      len = cf_ReadInt(infile);
    mprintf(0, ".");
    switch (pagetype) {
    case PAGETYPE_TEXTURE:
      mng_LoadLocalTexturePage(infile);
      break;
    case PAGETYPE_POWERUP:
    case PAGETYPE_ROBOT:
      Error("Your local table file is invalid.  You must update from the network.");
      break;
    case PAGETYPE_DOOR:
      mng_LoadLocalDoorPage(infile);
      break;
    case PAGETYPE_GENERIC:
      mng_LoadLocalGenericPage(infile);
      break;
    case PAGETYPE_GAMEFILE:
      mng_LoadLocalGamefilePage(infile);
      break;
    case PAGETYPE_SOUND:
      mng_LoadLocalSoundPage(infile);
      break;
    case PAGETYPE_SHIP:
      mng_LoadLocalShipPage(infile);
      break;
    case PAGETYPE_WEAPON:
      mng_LoadLocalWeaponPage(infile);
      break;
    case PAGETYPE_MEGACELL:
      mng_LoadLocalMegacellPage(infile);
      break;
    case PAGETYPE_UNKNOWN:
      break;
    default:
      Int3(); // Unrecognized pagetype, possible corrupt data following
      return 0;
      break;
    }
  }
  mprintf(0, "\n");
  cfclose(infile);
  Loading_locals = 0;
  return 1;
}
#define MAX_TRIES 10000
// Removes a file, then renames another file to be the removed file. Get it?
// Returns 1 on success, else 0 on fail
int SwitcherooFiles(char *name, char *tempname) {
  /*// If we're changing the net table file, make a backup first!
  if ((!stricmp (name,TableFilename)))
  {
          cf_CopyFile (BackupTableFilename,TableFilename);
          cf_CopyFile (BackupLockFilename,TableLockFilename);
  }*/
  int num_tries = 0;
  while (!ddio_DeleteFile(name) && num_tries < MAX_TRIES) {
    Sleep(100);
    num_tries++;
  }
  if (num_tries >= MAX_TRIES) {
    strcpy(ErrorString, "MANAGE:There was a problem deleting the table file.");
    ASSERT(0); // GET JASON IMMEDIATELY
    Int3();
    return (0);
  }
  num_tries = 0;
  while ((rename(tempname, name)) && num_tries <= MAX_TRIES) {
    Sleep(100);
    num_tries++;
  }
  if (num_tries >= MAX_TRIES) {
    strcpy(ErrorString, "MANAGE:There was a problem renaming the temp file.");
    ASSERT(0); // Get JASON IMMEDIATELY
    Int3();
    return (0);
  }

  return 1;
}

void mng_TransferPages() {
  CFILE *infile, *outfile;
  int pagetype;
  int num_tracklocks = 0;
  mprintf(0, "Transferring pages, please wait...\n");
  if (!mng_MakeLocker())
    return;
  infile = cfopen(TableFilename, "rb");

  if (!infile) {
    mprintf(0, "Couldn't open table file to transfer!\n");
    Int3();
    return;
  }
  mngs_track_lock *local_tracklocks = (mngs_track_lock *)mem_malloc(sizeof(*local_tracklocks) * 5000);
  // Do textures
  int done = 0;
  while (!done) {
    if (cfeof(infile)) {
      done = 1;
      continue;
    }
    pagetype = cf_ReadByte(infile);
    int len = cf_ReadInt(infile);
    switch (pagetype) {
    case PAGETYPE_TEXTURE:
      mng_ReadNewTexturePage(infile, &texpage);
      strcpy(local_tracklocks[num_tracklocks].name, texpage.tex_struct.name);
      local_tracklocks[num_tracklocks].pagetype = PAGETYPE_TEXTURE;
      num_tracklocks++;

      break;
    case PAGETYPE_SOUND:
      mng_ReadNewSoundPage(infile, &soundpage);
      strcpy(local_tracklocks[num_tracklocks].name, soundpage.sound_struct.name);
      local_tracklocks[num_tracklocks].pagetype = PAGETYPE_SOUND;
      num_tracklocks++;
      break;
    case PAGETYPE_WEAPON:
      mng_ReadNewWeaponPage(infile, &weaponpage);
      strcpy(local_tracklocks[num_tracklocks].name, weaponpage.weapon_struct.name);
      local_tracklocks[num_tracklocks].pagetype = PAGETYPE_WEAPON;
      num_tracklocks++;
      break;
    case PAGETYPE_GENERIC:
      mng_ReadNewGenericPage(infile, &genericpage);
      strcpy(local_tracklocks[num_tracklocks].name, genericpage.objinfo_struct.name);
      local_tracklocks[num_tracklocks].pagetype = PAGETYPE_GENERIC;
      num_tracklocks++;
      break;
    case PAGETYPE_DOOR:
      mng_ReadNewDoorPage(infile, &doorpage);
      strcpy(local_tracklocks[num_tracklocks].name, doorpage.door_struct.name);
      local_tracklocks[num_tracklocks].pagetype = PAGETYPE_DOOR;
      num_tracklocks++;
      break;
    case PAGETYPE_SHIP:
      mng_ReadNewShipPage(infile, &shippage);
      strcpy(local_tracklocks[num_tracklocks].name, shippage.ship_struct.name);
      local_tracklocks[num_tracklocks].pagetype = PAGETYPE_SHIP;
      num_tracklocks++;
      break;
    case PAGETYPE_GAMEFILE:
      mng_ReadNewGamefilePage(infile, &gamefilepage);
      strcpy(local_tracklocks[num_tracklocks].name, gamefilepage.gamefile_struct.name);
      local_tracklocks[num_tracklocks].pagetype = PAGETYPE_GAMEFILE;
      num_tracklocks++;
      break;
    case PAGETYPE_MEGACELL:
      Int3(); // huh?
      break;
    default:
      break;
    }
  }
  cfclose(infile);
  // Now go through and filter out all unused lock files
  infile = (CFILE *)cfopen(TableLockFilename, "rb");
  if (!infile) {
    strcpy(ErrorString, "Couldn't open Table lock file!");
    goto done;
  }
  outfile = (CFILE *)cfopen(TempTableLockFilename, "wb");
  if (!outfile) {
    cfclose(infile);
    strcpy(ErrorString, "Couldn't open temporary table lock file!");
    goto done;
  }
  done = 0;
  mngs_Pagelock temp_pl;
  while (!done) {
    if (cfeof(infile)) {
      done = 1;
      continue;
    }
    if (mng_ReadPagelock(infile, &temp_pl)) {
      int found = -1;
      for (int i = 0; i < num_tracklocks && found == -1; i++) {
        if (local_tracklocks[i].pagetype == temp_pl.pagetype && !stricmp(local_tracklocks[i].name, temp_pl.name)) {
          found = i;
        }
      }
      if (found != -1)
        mng_WritePagelock(outfile, &temp_pl);
      else {
        mprintf(0, "Found unused lock file %s\n", temp_pl.name);
      }

    } else
      done = 1;
  }
  cfclose(infile);
  cfclose(outfile);

  if (remove(TableLockFilename)) {
    snprintf(ErrorString, sizeof(ErrorString), "There was a problem deleting the temp file - errno %d", errno);
    goto done;
  }
  if (rename(TempTableLockFilename, TableLockFilename)) {
    snprintf(ErrorString, sizeof(ErrorString), "There was a problem renaming the temp file - errno %d", errno);

    goto done;
  }
  mng_EraseLocker();
  mprintf(0, "Done transferring pages...good luck!\n");
done:;
  mem_free(local_tracklocks);
}
// #define DELETING_PAGELOCKS	1
// #define CLEANING_PAGELOCKS	1
//  Given a list of names and a pagetype, unlocks the ones already inside the lock file
int mng_UnlockPagelockSeries(const char *names[], int *pagetypes, int num);
// Goes through the pagelock table and deletes all duplicate entries
int mng_DeleteDuplicatePagelocks();
void ReorderPagelocks() {
  const char *names[] = {"Lava"};
  int types[] = {PAGETYPE_SOUND};
  if (!mng_MakeLocker())
    return;
  mng_UnlockPagelockSeries(names, types, 1);

  // mng_DeleteDuplicatePagelocks ();

  mng_EraseLocker();
}
// THIS IS A SPECIAL FUNCTION THAT YOU SHOULD ONLY USE IF YOU KNOW WHAT YOU ARE
// DOING...it simply reorders the table file so that the "primitives" are first.
// This helps in the load time of a table file.
void ReorderPages(int local) {
  CFILE *infile, *outfile;
  uint8_t pagetype;
  int done = 0;
  int len;
#ifdef CLEANING_PAGELOCKS
  mng_TransferPages();
  return;
#endif
#ifdef DELETING_PAGELOCKS
  ReorderPagelocks();
  return;
#endif
  mprintf(0, "Reordering pages, please wait...\n");
  if (local)
    infile = cfopen(LocalTableFilename, "rb");
  else {
    if (!mng_MakeLocker())
      return;
    infile = cfopen(TableFilename, "rb");
  }
  if (!infile) {
    mprintf(0, "Couldn't open table file to reorder!\n");
    Int3();
    return;
  }
  if (local)
    outfile = cfopen(LocalTempTableFilename, "wb");
  else
    outfile = cfopen(TempTableFilename, "wb");
  if (!outfile) {
    mprintf(0, "Couldn't open temp table file to reorder!\n");
    cfclose(infile);
    Int3();
    return;
  }
  // Do textures
  while (!done) {
    if (cfeof(infile)) {
      done = 1;
      continue;
    }
    pagetype = cf_ReadByte(infile);
    len = cf_ReadInt(infile);
    // If not a door page, just read it in and ignore it
    if (pagetype != PAGETYPE_TEXTURE) {
      cfseek(infile, len - 4, SEEK_CUR);
      continue;
    }
    mng_ReadNewTexturePage(infile, &texpage);
    mng_WriteNewTexturePage(outfile, &texpage);
  }
  // Do sounds
  done = 0;
  cfseek(infile, 0, SEEK_SET);
  while (!done) {
    if (cfeof(infile)) {
      done = 1;
      continue;
    }
    pagetype = cf_ReadByte(infile);
    len = cf_ReadInt(infile);
    // If not a door page, just read it in and ignore it
    if (pagetype != PAGETYPE_SOUND) {
      cfseek(infile, len - 4, SEEK_CUR);
      continue;
    }
    mng_ReadNewSoundPage(infile, &soundpage);
    mng_WriteNewSoundPage(outfile, &soundpage);
  }
  // Do weapons
  done = 0;
  cfseek(infile, 0, SEEK_SET);
  while (!done) {
    if (cfeof(infile)) {
      done = 1;
      continue;
    }
    pagetype = cf_ReadByte(infile);
    len = cf_ReadInt(infile);
    // If not a door page, just read it in and ignore it
    if (pagetype != PAGETYPE_WEAPON) {
      cfseek(infile, len - 4, SEEK_CUR);
      continue;
    }
    mng_ReadNewWeaponPage(infile, &weaponpage);
    // Ignore counter measure weapons
    if (!(weaponpage.weapon_struct.flags & WF_SPAWNS_ROBOT))
      mng_WriteNewWeaponPage(outfile, &weaponpage);
  }
  // Do powerup generics
  done = 0;
  cfseek(infile, 0, SEEK_SET);
  while (!done) {
    if (cfeof(infile)) {
      done = 1;
      continue;
    }
    pagetype = cf_ReadByte(infile);
    len = cf_ReadInt(infile);
    // If not a door page, just read it in and ignore it
    if (pagetype != PAGETYPE_GENERIC) {
      cfseek(infile, len - 4, SEEK_CUR);
      continue;
    }
    mng_ReadNewGenericPage(infile, &genericpage);
    if (genericpage.objinfo_struct.type == OBJ_POWERUP)
      mng_WriteNewGenericPage(outfile, &genericpage);
    if (genericpage.objinfo_struct.description != NULL) {
      mem_free(genericpage.objinfo_struct.description);
      genericpage.objinfo_struct.description = NULL;
    }
  }
  // Do standard generics
  done = 0;
  cfseek(infile, 0, SEEK_SET);
  while (!done) {
    if (cfeof(infile)) {
      done = 1;
      continue;
    }
    pagetype = cf_ReadByte(infile);
    len = cf_ReadInt(infile);
    // If not a door page, just read it in and ignore it
    if (pagetype != PAGETYPE_GENERIC) {
      cfseek(infile, len - 4, SEEK_CUR);
      continue;
    }
    mng_ReadNewGenericPage(infile, &genericpage);
    if (genericpage.objinfo_struct.type != OBJ_POWERUP)
      mng_WriteNewGenericPage(outfile, &genericpage);
    if (genericpage.objinfo_struct.description != NULL) {
      mem_free(genericpage.objinfo_struct.description);
      genericpage.objinfo_struct.description = NULL;
    }
  }
  // Do countermeasure weapons
  done = 0;
  cfseek(infile, 0, SEEK_SET);
  while (!done) {
    if (cfeof(infile)) {
      done = 1;
      continue;
    }
    pagetype = cf_ReadByte(infile);
    len = cf_ReadInt(infile);
    // If not a door page, just read it in and ignore it
    if (pagetype != PAGETYPE_WEAPON) {
      cfseek(infile, len - 4, SEEK_CUR);
      continue;
    }
    mng_ReadNewWeaponPage(infile, &weaponpage);
    if ((weaponpage.weapon_struct.flags & WF_SPAWNS_ROBOT))
      mng_WriteNewWeaponPage(outfile, &weaponpage);
  }

  // Do doors
  done = 0;
  cfseek(infile, 0, SEEK_SET);
  while (!done) {
    if (cfeof(infile)) {
      done = 1;
      continue;
    }
    pagetype = cf_ReadByte(infile);
    len = cf_ReadInt(infile);
    // If not a door page, just read it in and ignore it
    if (pagetype != PAGETYPE_DOOR) {
      cfseek(infile, len - 4, SEEK_CUR);
      continue;
    }
    mng_ReadNewDoorPage(infile, &doorpage);
    mng_WriteNewDoorPage(outfile, &doorpage);
  }
  // Do player ships
  done = 0;
  cfseek(infile, 0, SEEK_SET);
  while (!done) {
    if (cfeof(infile)) {
      done = 1;
      continue;
    }
    pagetype = cf_ReadByte(infile);
    len = cf_ReadInt(infile);
    // If not a door page, just read it in and ignore it
    if (pagetype != PAGETYPE_SHIP) {
      cfseek(infile, len - 4, SEEK_CUR);
      continue;
    }
    mng_ReadNewShipPage(infile, &shippage);
    mng_WriteNewShipPage(outfile, &shippage);
  }
  // Do gamefiles
  done = 0;
  cfseek(infile, 0, SEEK_SET);
  while (!done) {
    if (cfeof(infile)) {
      done = 1;
      continue;
    }
    pagetype = cf_ReadByte(infile);
    len = cf_ReadInt(infile);
    // If not a door page, just read it in and ignore it
    if (pagetype != PAGETYPE_GAMEFILE) {
      cfseek(infile, len - 4, SEEK_CUR);
      continue;
    }
    mng_ReadNewGamefilePage(infile, &gamefilepage);
    mng_WriteNewGamefilePage(outfile, &gamefilepage);
  }
  // Do megacells
  done = 0;
  cfseek(infile, 0, SEEK_SET);
  while (!done) {
    if (cfeof(infile)) {
      done = 1;
      continue;
    }
    pagetype = cf_ReadByte(infile);
    len = cf_ReadInt(infile);
    // If not a door page, just read it in and ignore it
    if (pagetype != PAGETYPE_MEGACELL) {
      cfseek(infile, len - 4, SEEK_CUR);
      continue;
    }
    mng_ReadNewMegacellPage(infile, &megacellpage);
    mng_WriteNewMegacellPage(outfile, &megacellpage);
  }

  cfclose(infile);
  cfclose(outfile);
  if (local) {
    SwitcherooFiles(LocalTableFilename, LocalTempTableFilename);
  } else {
    SwitcherooFiles(TableFilename, TempTableFilename);
  }
  mng_EraseLocker();
}
// Returns true if the passed in pagelock is in the LockList, else false
bool InLockList(mngs_Pagelock *pl) {
  if (Starting_editor) {
    for (int i = 0; i < Num_locklist; i++) {
      if (LockList[i].pagetype == pl->pagetype) {
        if (!stricmp(LockList[i].name, pl->name))
          return true;
      }
    }
  } else {
    if ((mng_CheckIfPageOwned(pl, TableUser)) > 0) // DAJ -1FIX
      return true;
  }
  return false;
}
// Given a filename, returns the type of primitive it is
int GetPrimType(char *name) {
  char ext[10];
  char tname[_MAX_PATH];
  int primtype;
  ddio_SplitPath(name, tname, tname, ext);
  if (!stricmp("oof", ext))
    primtype = PRIMTYPE_OOF;
  else if (!stricmp("ogf", ext))
    primtype = PRIMTYPE_OGF;
  else if (!stricmp("oaf", ext))
    primtype = PRIMTYPE_OAF;
  else if (!stricmp("wav", ext))
    primtype = PRIMTYPE_WAV;
  else
    primtype = PRIMTYPE_FILE;
  return primtype;
}
#if defined(WIN32)
// Builds a list of old files in a path
void BuildOldFilesForDirectory(char *path, FILETIME threshold) {
  HANDLE filehandle;
  WIN32_FIND_DATA filedata;
  char newpath[_MAX_PATH];
  ddio_MakePath(newpath, path, "*.*", NULL);
  filehandle = FindFirstFile(newpath, &filedata);
  bool go_ahead = true;
  if (filehandle == INVALID_HANDLE_VALUE)
    go_ahead = false;
  while (go_ahead) {
    bool add_it = false;

    //	if this file is newer than the last time we updated, add it to the list

    if (filedata.ftLastWriteTime.dwHighDateTime > threshold.dwHighDateTime)
      add_it = true;
    if (filedata.ftLastWriteTime.dwHighDateTime == threshold.dwHighDateTime) {
      if (filedata.ftLastWriteTime.dwLowDateTime > threshold.dwLowDateTime)
        add_it = true;
    }
    if (filedata.ftCreationTime.dwHighDateTime > threshold.dwHighDateTime)
      add_it = true;
    if (filedata.ftCreationTime.dwHighDateTime == threshold.dwHighDateTime) {
      if (filedata.ftCreationTime.dwLowDateTime > threshold.dwLowDateTime)
        add_it = true;
    }
    // Add it to the list!
    if (add_it) {
      int primtype = GetPrimType(filedata.cFileName);
      OldFiles[Num_old_files].type = primtype;
      strcpy(OldFiles[Num_old_files].name, filedata.cFileName);
      Num_old_files++;
    }
    go_ahead = (FindNextFile(filehandle, &filedata) != 0);
  }
  if (filehandle != INVALID_HANDLE_VALUE)
    FindClose(filehandle);
}
// Builds a list of old files so we know which ones to update
// Searches through all our netdirectories for old files
void BuildOldFileList(FILETIME threshold) {
  char str[_MAX_PATH];
  mprintf(0, "Building old files list!\n");
  BuildOldFilesForDirectory(NetModelsDir, threshold);
  BuildOldFilesForDirectory(NetSoundsDir, threshold);
  BuildOldFilesForDirectory(NetMiscDir, threshold);
  BuildOldFilesForDirectory(ManageGraphicsDir, threshold);
  BuildOldFilesForDirectory(NetArtDir, threshold);
  BuildOldFilesForDirectory(NetMusicDir, threshold);
  BuildOldFilesForDirectory(NetVoiceDir, threshold);
  ddio_MakePath(str, NetD3Dir, "data", "levels", NULL);
  BuildOldFilesForDirectory(str, threshold);
  ddio_MakePath(str, NetD3Dir, "data", "briefings", NULL);
  BuildOldFilesForDirectory(str, threshold);
  ddio_MakePath(str, NetD3Dir, "data", "scripts", NULL);
  BuildOldFilesForDirectory(str, threshold);
  mprintf(0, "Found %d old files.\n", Num_old_files);
}
#endif
// Returns true if the passed in primitive is old (ie needs to be updated from the network)
bool IsPrimitiveOld(char *name) {
  int primtype = GetPrimType(name);
  for (int i = 0; i < Num_old_files; i++) {
    if (OldFiles[i].type == primtype && !stricmp(OldFiles[i].name, name))
      return true;
  }

  return false;
}
// Updates a primitive if needed
// Localname = local version of the primname (with path)
// Netname = Network version of the primname (with path)
void UpdatePrimitive(char *localname, char *netname, char *primname, int pagetype, char *pagename) {
  bool update = false;
  if (Starting_editor && !Use_old_update_method) {
    if (IsPrimitiveOld(primname))
      update = true;
  } else {
    if (!cfexist(localname) || (cfexist(netname) && cf_Diff(localname, netname)))
      update = true;
  }

  if (update) {
    mngs_Pagelock temp_pl;
    temp_pl.pagetype = pagetype;
    strcpy(temp_pl.name, pagename);
    if (!InLockList(&temp_pl)) {
      mprintf(0, "Making a local copy of %s for next time.\n", primname);
      if (!cf_CopyFile(localname, netname, 1)) {
        Int3(); // get Jason
        return;
      }
    }
  }
}
// Writes a chunk header.  Writes chunk id & placeholder length.  Returns chunk start pos
int StartManagePage(CFILE *ofile, uint8_t pagetype) {
  int chunk_start_pos;
  // Write pagetype
  cf_WriteByte(ofile, pagetype);
  chunk_start_pos = cftell(ofile);
  cf_WriteInt(ofile, 0); // placeholder for chunk len

  return chunk_start_pos;
}
// Fill in page length when done writing
void EndManagePage(CFILE *ofile, int chunk_start_pos) {
  int save_pos = cftell(ofile);
  int len = save_pos - chunk_start_pos;
  // seek back to len field and fill in value
  cfseek(ofile, chunk_start_pos, SEEK_SET);
  cf_WriteInt(ofile, len); // write chunk length
  // go back to end of file
  cfseek(ofile, save_pos, SEEK_SET);
}
// Assigns a page to its appropriate structure and writes it out
void mng_AssignAndWritePage(int handle, int pagetype, CFILE *outfile) {
  switch (pagetype) {
  case PAGETYPE_TEXTURE:
    mng_AssignTextureToTexPage(handle, &texpage);
    mng_WriteNewTexturePage(outfile, &texpage);
    break;
  case PAGETYPE_SOUND:
    mng_AssignSoundToSoundPage(handle, &soundpage);
    mng_WriteNewSoundPage(outfile, &soundpage);
    break;
  case PAGETYPE_WEAPON:
    mng_AssignWeaponToWeaponPage(handle, &weaponpage);
    mng_WriteNewWeaponPage(outfile, &weaponpage);
    break;
  case PAGETYPE_GENERIC:
    mng_AssignObjInfoToGenericPage(handle, &genericpage);
    mng_WriteNewGenericPage(outfile, &genericpage);
    break;
  case PAGETYPE_DOOR:
    mng_AssignDoorToDoorPage(handle, &doorpage);
    mng_WriteNewDoorPage(outfile, &doorpage);
    break;
  case PAGETYPE_MEGACELL:
    mng_AssignMegacellToMegacellPage(handle, &megacellpage);
    mng_WriteNewMegacellPage(outfile, &megacellpage);
    break;
  case PAGETYPE_SHIP:
    mng_AssignShipToShipPage(handle, &shippage);
    mng_WriteNewShipPage(outfile, &shippage);
    break;
  case PAGETYPE_GAMEFILE:
    mng_AssignGamefileToGamefilePage(handle, &gamefilepage);
    mng_WriteNewGamefilePage(outfile, &gamefilepage);
    break;
  default:
    break;
  }
}
#define COPYBUFFER_SIZE 200000
// Given a texture handle, searches the table file and replaces the texture with the same name
// If local=1, then does it to the users local copy
// Returns 0 on error, else 1 if all is good
int mng_ReplacePage(char *srcname, char *destname, int handle, int dest_pagetype, int local) {
  CFILE *infile, *outfile;
  uint8_t pagetype, replaced = 0;
  int done = 0, len;
  mprintf(0, "Replacing '%s' with '%s' (%s).\n", srcname, destname, local ? "locally" : "to network");

  if (local)
    infile = cfopen(LocalTableFilename, "rb");
  else
    infile = cfopen(TableFilename, "rb");
  if (!infile) {
    mprintf(0, "Couldn't open table file to replace page %s!\n", srcname);
    Int3();
    return 0;
  }
  if (local)
    outfile = cfopen(LocalTempTableFilename, "wb");
  else
    outfile = cfopen(TempTableFilename, "wb");
  if (!outfile) {
    mprintf(0, "Couldn't open temp table file to replace page %s!\n", srcname);
    cfclose(infile);
    Int3();
    return 0;
  }
  // Allocate memory for copying
  uint8_t *copybuffer = (uint8_t *)mem_malloc(COPYBUFFER_SIZE);
  if (!copybuffer) {
    mprintf(0, "Couldn't allocate memory to replace page %s!\n", srcname);
    cfclose(infile);
    cfclose(outfile);
    Int3();
    return 0;
  }
  while (!done) {
    if (cfeof(infile)) {
      done = 1;
      continue;
    }
    pagetype = cf_ReadByte(infile);
    len = cf_ReadInt(infile);
    // If not a texture page, just read it in and write it right back out
    if (pagetype != dest_pagetype) {
      ASSERT(len < COPYBUFFER_SIZE);

      cf_ReadBytes(copybuffer, len - 4, infile);
      cf_WriteByte(outfile, pagetype);
      cf_WriteInt(outfile, len);
      if (len - 4 > 0)
        cf_WriteBytes(copybuffer, len - 4, outfile);

      continue;
    }
    switch (pagetype) {
    case PAGETYPE_TEXTURE: {
      mng_ReadNewTexturePage(infile, &texpage);
      if (!stricmp(srcname, texpage.tex_struct.name)) {
        mng_AssignAndWritePage(handle, pagetype, outfile);
        replaced = 1;
      } else {
        mng_WriteNewTexturePage(outfile, &texpage);
      }
      break;
    }
    case PAGETYPE_SOUND: {
      mng_ReadNewSoundPage(infile, &soundpage);
      if (!stricmp(srcname, soundpage.sound_struct.name)) {
        mng_AssignAndWritePage(handle, pagetype, outfile);
        replaced = 1;
      } else {
        mng_WriteNewSoundPage(outfile, &soundpage);
      }
      break;
    }
    case PAGETYPE_WEAPON: {
      mng_ReadNewWeaponPage(infile, &weaponpage);
      if (!stricmp(srcname, weaponpage.weapon_struct.name)) {
        mng_AssignAndWritePage(handle, pagetype, outfile);
        replaced = 1;
      } else {
        mng_WriteNewWeaponPage(outfile, &weaponpage);
      }
      break;
    }
    case PAGETYPE_GENERIC: {
      mng_ReadNewGenericPage(infile, &genericpage);
      if (!stricmp(srcname, genericpage.objinfo_struct.name)) {
        // This is the page we want to replace, so write the new one out.
        if (genericpage.objinfo_struct.description != NULL) {
          mem_free(genericpage.objinfo_struct.description);
          genericpage.objinfo_struct.description = NULL;
        }
        genericpage.objinfo_struct.icon_name[0] = '\0';

        mng_AssignAndWritePage(handle, pagetype, outfile);
        replaced = 1;
      } else {
        mng_WriteNewGenericPage(outfile, &genericpage);
      }
      break;
    }
    case PAGETYPE_DOOR: {
      mng_ReadNewDoorPage(infile, &doorpage);
      if (!stricmp(srcname, doorpage.door_struct.name)) {
        mng_AssignAndWritePage(handle, pagetype, outfile);
        replaced = 1;
      } else {
        mng_WriteNewDoorPage(outfile, &doorpage);
      }
      break;
    }
    case PAGETYPE_MEGACELL: {
      mng_ReadNewMegacellPage(infile, &megacellpage);
      if (!stricmp(srcname, megacellpage.megacell_struct.name)) {
        mng_AssignAndWritePage(handle, pagetype, outfile);
        replaced = 1;
      } else {
        mng_WriteNewMegacellPage(outfile, &megacellpage);
      }
      break;
    }
    case PAGETYPE_SHIP: {
      mng_ReadNewShipPage(infile, &shippage);
      if (!stricmp(srcname, shippage.ship_struct.name)) {
        mng_AssignAndWritePage(handle, pagetype, outfile);
        replaced = 1;
      } else {
        mng_WriteNewShipPage(outfile, &shippage);
      }
      break;
    }
    case PAGETYPE_GAMEFILE: {
      mng_ReadNewGamefilePage(infile, &gamefilepage);
      if (!stricmp(srcname, gamefilepage.gamefile_struct.name)) {
        mng_AssignAndWritePage(handle, pagetype, outfile);
        replaced = 1;
      } else {
        mng_WriteNewGamefilePage(outfile, &gamefilepage);
      }
      break;
    }
    default:
      break;
    }
  }

  if (!replaced) {
    // This is a new page, so append it to the end of file.
    mng_AssignAndWritePage(handle, dest_pagetype, outfile);
  }
  if (replaced)
    mprintf(0, "Page replaced.\n");
  else
    mprintf(0, "New page added.\n");
  cfclose(infile);
  cfclose(outfile);
  mem_free(copybuffer);
  if (local) {
    if (!SwitcherooFiles(LocalTableFilename, LocalTempTableFilename))
      return 0;
  } else {
    if (!SwitcherooFiles(TableFilename, TempTableFilename))
      return 0;
  }
  return 1; // successful!
}
// Given a texture name, finds it in the table file and deletes it
// If local is 1, deletes from the local table file
int mng_DeletePage(char *name, int dest_pagetype, int local) {
  CFILE *infile, *outfile;
  uint8_t pagetype, replaced = 0;
  int done = 0;
  int deleted = 0;

  mprintf(0, "Deleting %s (%s).\n", name, local ? "locally" : "on network");

  if (local)
    infile = cfopen(LocalTableFilename, "rb");
  else
    infile = cfopen(TableFilename, "rb");
  if (!infile) {
    mprintf(0, "Couldn't open table file to delete page!\n");
    Int3();
    return 0;
  }
  if (local)
    outfile = cfopen(LocalTempTableFilename, "wb");
  else
    outfile = cfopen(TempTableFilename, "wb");
  if (!outfile) {
    mprintf(0, "Couldn't open temp table file to delete page!\n");
    cfclose(infile);
    Int3();
    return 0;
  }
  // Allocate memory for copying
  uint8_t *copybuffer = (uint8_t *)mem_malloc(COPYBUFFER_SIZE);
  if (!copybuffer) {
    mprintf(0, "Couldn't allocate memory to delete page!\n");
    cfclose(infile);
    cfclose(outfile);
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
    if (pagetype != dest_pagetype) {
      ASSERT(len < COPYBUFFER_SIZE);

      cf_ReadBytes(copybuffer, len - 4, infile);
      cf_WriteByte(outfile, pagetype);
      cf_WriteInt(outfile, len);
      if (len - 4 > 0)
        cf_WriteBytes(copybuffer, len - 4, outfile);

      continue;
    }
    switch (pagetype) {

    case PAGETYPE_TEXTURE: {
      mng_ReadNewTexturePage(infile, &texpage);
      if (stricmp(name, texpage.tex_struct.name))
        mng_WriteNewTexturePage(outfile, &texpage);
      else
        deleted = 1; // Don't write out the one we want to delete
      break;
    }
    case PAGETYPE_DOOR: {
      mng_ReadNewDoorPage(infile, &doorpage);
      if (stricmp(name, doorpage.door_struct.name))
        mng_WriteNewDoorPage(outfile, &doorpage);
      else
        deleted = 1; // Don't write out the one we want to delete
      break;
    }
    case PAGETYPE_GENERIC: {
      mng_ReadNewGenericPage(infile, &genericpage);
      if (stricmp(name, genericpage.objinfo_struct.name))
        mng_WriteNewGenericPage(outfile, &genericpage);
      else
        deleted = 1; // Don't write out the one we want to delete
      if (genericpage.objinfo_struct.description != NULL) {
        mem_free(genericpage.objinfo_struct.description);
        genericpage.objinfo_struct.description = NULL;
      }
      genericpage.objinfo_struct.icon_name[0] = '\0';
      break;
    }
    case PAGETYPE_SOUND: {
      mng_ReadNewSoundPage(infile, &soundpage);
      if (stricmp(name, soundpage.sound_struct.name))
        mng_WriteNewSoundPage(outfile, &soundpage);
      else
        deleted = 1; // Don't write out the one we want to delete
      break;
    }
    case PAGETYPE_SHIP: {
      mng_ReadNewShipPage(infile, &shippage);
      if (stricmp(name, shippage.ship_struct.name))
        mng_WriteNewShipPage(outfile, &shippage);
      else
        deleted = 1; // Don't write out the one we want to delete
      break;
    }
    case PAGETYPE_WEAPON: {
      mng_ReadNewWeaponPage(infile, &weaponpage);
      if (stricmp(name, weaponpage.weapon_struct.name))
        mng_WriteNewWeaponPage(outfile, &weaponpage);
      else
        deleted = 1; // Don't write out the one we want to delete
      break;
    }
    case PAGETYPE_MEGACELL: {
      mng_ReadNewMegacellPage(infile, &megacellpage);
      if (stricmp(name, megacellpage.megacell_struct.name))
        mng_WriteNewMegacellPage(outfile, &megacellpage);
      else
        deleted = 1; // Don't write out the one we want to delete
      break;
    }
    case PAGETYPE_GAMEFILE: {
      mng_ReadNewGamefilePage(infile, &gamefilepage);
      if (stricmp(name, gamefilepage.gamefile_struct.name))
        mng_WriteNewGamefilePage(outfile, &gamefilepage);
      else
        deleted = 1; // Don't write out the one we want to delete
      break;
    }
    default:
      break;
    }
  }

  if (!local) {
    // It's gotta be there if on the network
    ASSERT(deleted == 1);
  } else {
    if (!deleted) {
      mprintf(0, "Not found locally?!\n");
    }
  }
  cfclose(infile);
  cfclose(outfile);
  mem_free(copybuffer);
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
// Reads in a physics chunk from an open file
void mng_ReadPhysicsChunk(physics_info *phys_info, CFILE *infile) {
  phys_info->mass = cf_ReadFloat(infile);
  phys_info->drag = cf_ReadFloat(infile);
  phys_info->full_thrust = cf_ReadFloat(infile);
  phys_info->flags = cf_ReadInt(infile);
  phys_info->rotdrag = cf_ReadFloat(infile);
  phys_info->full_rotthrust = cf_ReadFloat(infile);
  phys_info->num_bounces = cf_ReadInt(infile);
  phys_info->velocity.z = cf_ReadFloat(infile);
  phys_info->rotvel.x = cf_ReadFloat(infile);
  phys_info->rotvel.y = cf_ReadFloat(infile);
  phys_info->rotvel.z = cf_ReadFloat(infile);
  phys_info->wiggle_amplitude = cf_ReadFloat(infile);
  phys_info->wiggles_per_sec = cf_ReadFloat(infile);
  phys_info->coeff_restitution = cf_ReadFloat(infile);
  phys_info->hit_die_dot = cf_ReadFloat(infile);
  phys_info->max_turnroll_rate = cf_ReadFloat(infile);
  phys_info->turnroll_ratio = cf_ReadFloat(infile);
}
// Writes out a physics chunk to an open file
void mng_WritePhysicsChunk(physics_info *phys_info, CFILE *outfile) {
  cf_WriteFloat(outfile, phys_info->mass);
  cf_WriteFloat(outfile, phys_info->drag);
  cf_WriteFloat(outfile, phys_info->full_thrust);
  cf_WriteInt(outfile, phys_info->flags);
  cf_WriteFloat(outfile, phys_info->rotdrag);
  cf_WriteFloat(outfile, phys_info->full_rotthrust);
  cf_WriteInt(outfile, phys_info->num_bounces);
  cf_WriteFloat(outfile, phys_info->velocity.z);
  cf_WriteFloat(outfile, phys_info->rotvel.x);
  cf_WriteFloat(outfile, phys_info->rotvel.y);
  cf_WriteFloat(outfile, phys_info->rotvel.z);
  cf_WriteFloat(outfile, phys_info->wiggle_amplitude);
  cf_WriteFloat(outfile, phys_info->wiggles_per_sec);
  cf_WriteFloat(outfile, phys_info->coeff_restitution);
  cf_WriteFloat(outfile, phys_info->hit_die_dot);
  cf_WriteFloat(outfile, phys_info->max_turnroll_rate);
  cf_WriteFloat(outfile, phys_info->turnroll_ratio);
}
// Writes out weapon battery info
void mng_WriteWeaponBatteryChunk(otype_wb_info *static_wb, CFILE *outfile) {
  int j;
  cf_WriteFloat(outfile, static_wb->energy_usage);
  cf_WriteFloat(outfile, static_wb->ammo_usage);
  for (j = 0; j < MAX_WB_GUNPOINTS; j++) {
    cf_WriteShort(outfile, static_wb->gp_weapon_index[j]);
  }

  for (j = 0; j < MAX_WB_FIRING_MASKS; j++) {
    cf_WriteByte(outfile, static_wb->gp_fire_masks[j]);
    cf_WriteFloat(outfile, static_wb->gp_fire_wait[j]);
    cf_WriteFloat(outfile, static_wb->anim_time[j]);
    cf_WriteFloat(outfile, static_wb->anim_start_frame[j]);
    cf_WriteFloat(outfile, static_wb->anim_fire_frame[j]);
    cf_WriteFloat(outfile, static_wb->anim_end_frame[j]);
  }
  cf_WriteByte(outfile, static_wb->num_masks);
  cf_WriteShort(outfile, static_wb->aiming_gp_index);
  cf_WriteByte(outfile, static_wb->aiming_flags);
  cf_WriteFloat(outfile, static_wb->aiming_3d_dot);
  cf_WriteFloat(outfile, static_wb->aiming_3d_dist);
  cf_WriteFloat(outfile, static_wb->aiming_XZ_dot);
  cf_WriteShort(outfile, static_wb->flags);
  cf_WriteByte(outfile, static_wb->gp_quad_fire_mask);
}
// Reads in weapon battery info
void mng_ReadWeaponBatteryChunk(otype_wb_info *static_wb, CFILE *infile, int version) {
  int j;

  static_wb->energy_usage = cf_ReadFloat(infile);
  static_wb->ammo_usage = cf_ReadFloat(infile);

  for (j = 0; j < MAX_WB_GUNPOINTS; j++) {
    static_wb->gp_weapon_index[j] = cf_ReadShort(infile);
  }

  for (j = 0; j < MAX_WB_FIRING_MASKS; j++) {
    static_wb->gp_fire_masks[j] = cf_ReadByte(infile);
    static_wb->gp_fire_wait[j] = cf_ReadFloat(infile);
    static_wb->anim_time[j] = cf_ReadFloat(infile);
    static_wb->anim_start_frame[j] = cf_ReadFloat(infile);
    static_wb->anim_fire_frame[j] = cf_ReadFloat(infile);
    static_wb->anim_end_frame[j] = cf_ReadFloat(infile);
  }
  static_wb->num_masks = cf_ReadByte(infile);
  static_wb->aiming_gp_index = cf_ReadShort(infile);
  static_wb->aiming_flags = cf_ReadByte(infile);
  static_wb->aiming_3d_dot = cf_ReadFloat(infile);
  static_wb->aiming_3d_dist = cf_ReadFloat(infile);
  static_wb->aiming_XZ_dot = cf_ReadFloat(infile);
  if (version >= 2)
    static_wb->flags = cf_ReadShort(infile);
  else
    static_wb->flags = cf_ReadByte(infile);
  static_wb->gp_quad_fire_mask = cf_ReadByte(infile);
}
// Writes a lighting chunk in from an open file
void mng_WriteLightingChunk(light_info *lighting_info, CFILE *outfile) {
  cf_WriteFloat(outfile, lighting_info->light_distance);
  cf_WriteFloat(outfile, lighting_info->red_light1);
  cf_WriteFloat(outfile, lighting_info->green_light1);
  cf_WriteFloat(outfile, lighting_info->blue_light1);
  cf_WriteFloat(outfile, lighting_info->time_interval);
  cf_WriteFloat(outfile, lighting_info->flicker_distance);
  cf_WriteFloat(outfile, lighting_info->directional_dot);
  cf_WriteFloat(outfile, lighting_info->red_light2);
  cf_WriteFloat(outfile, lighting_info->green_light2);
  cf_WriteFloat(outfile, lighting_info->blue_light2);
  cf_WriteInt(outfile, lighting_info->flags);
  cf_WriteInt(outfile, lighting_info->timebits);
  cf_WriteByte(outfile, lighting_info->angle);
  cf_WriteByte(outfile, lighting_info->lighting_render_type);
}
// Reads a lighting chunk in from an open file
void mng_ReadLightingChunk(light_info *lighting_info, CFILE *infile) {
  lighting_info->light_distance = cf_ReadFloat(infile);
  lighting_info->red_light1 = cf_ReadFloat(infile);
  lighting_info->green_light1 = cf_ReadFloat(infile);
  lighting_info->blue_light1 = cf_ReadFloat(infile);
  lighting_info->time_interval = cf_ReadFloat(infile);
  lighting_info->flicker_distance = cf_ReadFloat(infile);
  lighting_info->directional_dot = cf_ReadFloat(infile);
  lighting_info->red_light2 = cf_ReadFloat(infile);
  lighting_info->green_light2 = cf_ReadFloat(infile);
  lighting_info->blue_light2 = cf_ReadFloat(infile);
  lighting_info->flags = cf_ReadInt(infile);
  lighting_info->timebits = cf_ReadInt(infile);
  lighting_info->angle = cf_ReadByte(infile);
  lighting_info->lighting_render_type = cf_ReadByte(infile);
}

// Record keeping
AddOnTablefile AddOnDataTables[MAX_ADDON_TABLES];

// the number of addon tables currently in memory
int Num_addon_tables = 0;

// if not -1, then it is the addon table we are working with
int Loading_addon_table = -1;

//----------------------
// Add-on data routines
//----------------------
// Frees all the primitives associated with an page
void mng_FreePagetypePrimitives(int pagetype, char *name, int freetype) {
  int n;
  switch (pagetype) {
  case PAGETYPE_TEXTURE:
    n = FindTextureName(name);
    ASSERT(n >= 0);
    if (GameTextures[n].flags & TF_ANIMATED)
      FreeVClip(GameTextures[n].bm_handle);
    else
      bm_FreeBitmap(GameTextures[n].bm_handle);
    if (GameTextures[n].flags & TF_DESTROYABLE && GameTextures[n].destroy_handle >= 0 &&
        GameTextures[n].destroy_handle != n) {
      int oldn = n;
      n = GameTextures[n].destroy_handle;
      if (GameTextures[n].flags & TF_ANIMATED)
        FreeVClip(GameTextures[n].bm_handle);
      else
        bm_FreeBitmap(GameTextures[n].bm_handle);
      n = oldn;
    }
    if (freetype)
      FreeTexture(n);

    break;
  case PAGETYPE_SOUND:
    n = FindSoundName(name);
    ASSERT(n >= 0);
    FreeSoundFile(Sounds[n].sample_index);
    if (freetype)
      FreeSound(n);
    break;
  case PAGETYPE_WEAPON:
    n = FindWeaponName(name);
    ASSERT(n >= 0);
    // Free weapon images
    if (Weapons[n].flags & WF_HUD_ANIMATED)
      FreeVClip(Weapons[n].hud_image_handle);
    else
      bm_FreeBitmap(Weapons[n].hud_image_handle);
    if (Weapons[n].fire_image_handle != -1) {
      if (Weapons[n].flags & WF_IMAGE_BITMAP)
        bm_FreeBitmap(Weapons[n].fire_image_handle);
      else if (Weapons[n].flags & WF_IMAGE_VCLIP)
        FreeVClip(Weapons[n].fire_image_handle);
      else
        FreePolyModel(Weapons[n].fire_image_handle);
    }
    if (freetype)
      FreeWeapon(n);
    break;
  case PAGETYPE_SHIP:
    n = FindShipName(name);
    ASSERT(n >= 0);
    FreePolyModel(Ships[n].model_handle);
    if (Ships[n].dying_model_handle != -1)
      FreePolyModel(Ships[n].dying_model_handle);
    if (Ships[n].med_render_handle != -1)
      FreePolyModel(Ships[n].med_render_handle);
    if (Ships[n].lo_render_handle != -1)
      FreePolyModel(Ships[n].lo_render_handle);
    if (freetype)
      FreeShip(n);
    break;
  case PAGETYPE_GENERIC:
    n = FindObjectIDName(name);
    ASSERT(n >= 0);

    FreePolyModel(Object_info[n].render_handle);
    if (Object_info[n].med_render_handle != -1)
      FreePolyModel(Object_info[n].med_render_handle);
    if (Object_info[n].lo_render_handle != -1)
      FreePolyModel(Object_info[n].lo_render_handle);
    if (freetype)
      FreeObjectID(n);
    break;
  case PAGETYPE_DOOR:
    n = FindDoorName(name);
    ASSERT(n >= 0);
    FreePolyModel(Doors[n].model_handle);
    if (freetype)
      FreeDoor(n);
    break;
  default:
    break;
  }
}
// Takes our addon pages and frees/restores our data to the appropriate pages
void mng_PopAddonPages() {
  int i, n, ok;

  ASSERT(Num_addon_tables > 0);
  if (Num_addon_tables <= 0)
    return; // no addon pages to pop off

  Num_addon_tables--;
  Loading_locals = 0;
  AddOnTablefile *addondata = &AddOnDataTables[Num_addon_tables];

  for (i = 0; i < addondata->Num_addon_tracklocks; i++) {
    mprintf(0, "Freeing addon page %s [%s].\n", addondata->Addon_tracklocks[i].name, addondata->AddOnTableFilename);

    // set the Loading_addon_table to the appropriate value...
    // it depends on if we are overlaying from a previous tablefile
    // or this isn't an overlay at all
    // overlay = 0 (not an overlay of anything)
    // overlay = 1 (overlay of main tablefile)
    // overlay > 1 (overlay of addon table [overlay-2])
    if (addondata->Addon_tracklocks[i].overlay > 1) {
      // this is an overlay of another table file
      Loading_addon_table = addondata->Addon_tracklocks[i].overlay - 2;
    } else {
      // this is an overlay of the main table file
      // or not an overlay at all
      Loading_addon_table = -1;
    }

    if (addondata->Addon_tracklocks[i].overlay > 0) {
      // Free this data, then read the old stuff back in
      mng_FreePagetypePrimitives(addondata->Addon_tracklocks[i].pagetype, addondata->Addon_tracklocks[i].name, 0);
      char *name = addondata->Addon_tracklocks[i].name;
      switch (addondata->Addon_tracklocks[i].pagetype) {
      case PAGETYPE_TEXTURE: {
        n = FindTextureName(name);
        ASSERT(n >= 0);
        ok = mng_FindSpecificTexPage(name, &texpage, addondata->Addon_tracklocks[i].stack_filepos);
        if (ok) {
          ok = mng_AssignTexPageToTexture(&texpage, n);
          if (!ok)
            Error("Error 1 restoring page %s from addon data!", name);
        } else
          Error("Error 2 restoring page %s from addon data!", name);
        break;
      }
      case PAGETYPE_SOUND: {
        n = FindSoundName(name);
        ASSERT(n >= 0);
        ok = mng_FindSpecificSoundPage(name, &soundpage, addondata->Addon_tracklocks[i].stack_filepos);
        if (ok) {
          ok = mng_AssignSoundPageToSound(&soundpage, n);
          if (!ok)
            Error("Error 1 restoring page %s from addon data!", name);
        } else
          Error("Error 2 restoring page %s from addon data!", name);
        break;
      }
      case PAGETYPE_DOOR: {
        n = FindDoorName(name);
        ASSERT(n >= 0);
        ok = mng_FindSpecificDoorPage(name, &doorpage, addondata->Addon_tracklocks[i].stack_filepos);
        if (ok) {
          ok = mng_AssignDoorPageToDoor(&doorpage, n);
          if (!ok)
            Error("Error 1 restoring page %s from addon data!", name);
        } else
          Error("Error 2 restoring page %s from addon data!", name);
        break;
      }
      case PAGETYPE_GENERIC: {
        n = FindObjectIDName(name);
        ASSERT(n >= 0);
        ok = mng_FindSpecificGenericPage(name, &genericpage, addondata->Addon_tracklocks[i].stack_filepos);
        if (ok) {
          ok = mng_AssignGenericPageToObjInfo(&genericpage, n);
          if (!ok)
            Error("Error 1 restoring page %s from addon data!", name);
        } else
          Error("Error 2 restoring page %s from addon data!", name);
        break;
      }
      case PAGETYPE_SHIP: {
        n = FindShipName(name);
        ASSERT(n >= 0);
        ok = mng_FindSpecificShipPage(name, &shippage, addondata->Addon_tracklocks[i].stack_filepos);
        if (ok) {
          ok = mng_AssignShipPageToShip(&shippage, n);
          if (!ok)
            Error("Error 1 restoring page %s from addon data!", name);
        } else
          Error("Error 2 restoring page %s from addon data!", name);
        break;
      }
      case PAGETYPE_WEAPON: {
        n = FindWeaponName(name);
        ASSERT(n >= 0);
        ok = mng_FindSpecificWeaponPage(name, &weaponpage, addondata->Addon_tracklocks[i].stack_filepos);
        if (ok) {
          ok = mng_AssignWeaponPageToWeapon(&weaponpage, n);
          if (!ok)
            Error("Error 1 restoring page %s from addon data!", name);
        } else
          Error("Error 2 restoring page %s from addon data!", name);
        break;
      }
      case PAGETYPE_GAMEFILE:
        // I don't think there's anything we need to do here
        break;
      default:
        Int3(); // bad type in list? Get Jason
        break;
      }

    } else {
      // Not overlay, just free this data
      mng_FreePagetypePrimitives(addondata->Addon_tracklocks[i].pagetype, addondata->Addon_tracklocks[i].name, 1);
    }
  }

  Loading_addon_table = -1;
}
// Simply sets no addon data to be loaded
void mng_ClearAddonTables() {
  int count = Num_addon_tables;
  while (count > 0) {
    ASSERT(count == Num_addon_tables);

    if (AddOnDataTables[count - 1].Addon_tracklocks) {
      mng_PopAddonPages();
      mem_free(AddOnDataTables[count - 1].Addon_tracklocks);
      AddOnDataTables[count - 1].Addon_tracklocks = NULL;
      AddOnDataTables[count - 1].Num_addon_tracklocks = 0;
    }

    count--;
  }
}
// Push the given table file as an addon table file
// returns true on success
bool mng_SetAddonTable(char *name) {
  ASSERT(Num_addon_tables < MAX_ADDON_TABLES);
  if (Num_addon_tables >= MAX_ADDON_TABLES)
    return false;

  // make sure the table file exists!
  if (!cfexist(name))
    return false;

  strcpy(AddOnDataTables[Num_addon_tables].AddOnTableFilename, name);
  AddOnDataTables[Num_addon_tables].Addon_tracklocks =
      (mngs_track_lock *)mem_malloc(MAX_ADDON_TRACKLOCKS * sizeof(mngs_track_lock));
  AddOnDataTables[Num_addon_tables].Num_addon_tracklocks = 0;
  ASSERT(AddOnDataTables[Num_addon_tables].Addon_tracklocks);
  memset(AddOnDataTables[Num_addon_tables].Addon_tracklocks, 0, MAX_ADDON_TRACKLOCKS * sizeof(mngs_track_lock));

  Num_addon_tables++;
  return true;
}

// Pushes an addon pack onto the stack so we can keep track of it
void mng_PushAddonPage(int pagetype, char *name, int overlay) {
  ASSERT(Loading_addon_table >= 0 && Loading_addon_table < MAX_ADDON_TABLES);

  AddOnTablefile *addon = &AddOnDataTables[Loading_addon_table];

  ASSERT(addon->Num_addon_tracklocks < MAX_ADDON_TRACKLOCKS);

  // First check to see if this is a redundant page
  for (int i = 0; i < addon->Num_addon_tracklocks; i++) {
    if (addon->Addon_tracklocks[i].used && addon->Addon_tracklocks[i].pagetype == pagetype) {
      if (!stricmp(addon->Addon_tracklocks[i].name, name)) {
        Int3();
        Error("Redundant addon page '%s' loaded...", name);
        return;
      }
    }
  }
  mprintf(0, "Adding addon page %s [%s] to list.\n", name, addon->AddOnTableFilename);
  addon->Addon_tracklocks[addon->Num_addon_tracklocks].used = 1;
  addon->Addon_tracklocks[addon->Num_addon_tracklocks].pagetype = pagetype;
  addon->Addon_tracklocks[addon->Num_addon_tracklocks].overlay = overlay;
  addon->Addon_tracklocks[addon->Num_addon_tracklocks].stack_filepos = 0;
  strcpy(addon->Addon_tracklocks[addon->Num_addon_tracklocks].name, name);
  addon->Num_addon_tracklocks++;
}

// Compiles the addon pages.  By looking at all the addon pages (after they have been
// loaded) and does some compiling and saving of information to speed up addon page
// freeing
void mng_CompileAddonPages(void) {
  if (Num_addon_tables <= 0)
    return; // no addon pages to pop off

  int curr_tablefile, i, tf, pagetype, len, next_pos, page_pos;
  CFILE *file;
  char pagename[256];
  bool found_page;

  for (curr_tablefile = 1; curr_tablefile <= Num_addon_tables; curr_tablefile++) {
    // find all the pages that are loaded from this tablefile
    // overlay = 0 (not from any tablefile)
    // overlay = 1 (from main tablefile)
    // overlay > 1 (from addontable[overlay-2]
    if (curr_tablefile == 1) {
      file = cfopen(TableFilename, "rb");
      mprintf(0, "Compiling addon pages of %s\n", TableFilename);
    } else {
      file = cfopen(AddOnDataTables[curr_tablefile - 2].AddOnTableFilename, "rb");
      mprintf(0, "Compiling addon pages of %s\n", AddOnDataTables[curr_tablefile - 2].AddOnTableFilename);
    }
    ASSERT(file != NULL);

    // start reading the pages from this tablefile
    // as we come across each page, check to see if it was
    // ever overlayed.
    while (!cfeof(file)) {
      // Read in a pagetype.  If its a page we recognize, load it
      page_pos = cftell(file);
      pagetype = cf_ReadByte(file);
      len = cf_ReadInt(file);
      next_pos = (page_pos + 1) + len;

      // get the name of the page
      switch (pagetype) {
      case PAGETYPE_TEXTURE:
        cf_ReadShort(file); // version
        cf_ReadString(pagename, PAGENAME_LEN, file);
        break;
      case PAGETYPE_DOOR:
        cf_ReadShort(file); // version
        cf_ReadString(pagename, PAGENAME_LEN, file);
        break;
      case PAGETYPE_GENERIC:
        cf_ReadShort(file); // version
        cf_ReadByte(file);  // type
        cf_ReadString(pagename, PAGENAME_LEN, file);
        break;
      case PAGETYPE_GAMEFILE:
        cf_ReadShort(file); // version
        cf_ReadString(pagename, PAGENAME_LEN, file);
        break;
      case PAGETYPE_SOUND:
        cf_ReadShort(file); // version
        cf_ReadString(pagename, PAGENAME_LEN, file);
        break;
      case PAGETYPE_SHIP:
        cf_ReadShort(file); // version
        cf_ReadString(pagename, PAGENAME_LEN, file);
        break;
      case PAGETYPE_WEAPON:
        cf_ReadShort(file); // version
        cf_ReadString(pagename, PAGENAME_LEN, file);
        break;
      case PAGETYPE_UNKNOWN:
        continue;
        break;
      default:
        Int3(); // Unrecognized pagetype, possible corrupt data following
        break;
      }

      // now look for all the places where this page is overlayed
      found_page = false;
      for (tf = 0; tf < Num_addon_tables; tf++) {
        for (i = 0; i < AddOnDataTables[tf].Num_addon_tracklocks; i++) {
          if (!AddOnDataTables[tf].Addon_tracklocks[i].used)
            continue;
          if (AddOnDataTables[tf].Addon_tracklocks[i].overlay != curr_tablefile)
            continue;
          if (AddOnDataTables[tf].Addon_tracklocks[i].pagetype != pagetype)
            continue;
          if (stricmp(pagename, AddOnDataTables[tf].Addon_tracklocks[i].name))
            continue;

          // this is it!
          mprintf(0, "***Compiling: %s[%s] to %d\n",
                  AddOnDataTables[tf].Addon_tracklocks[i].name,
                  (curr_tablefile == 1) ? TableFilename : AddOnDataTables[curr_tablefile - 2].AddOnTableFilename,
                  page_pos);
          ASSERT(AddOnDataTables[tf].Addon_tracklocks[i].stack_filepos == 0);
          AddOnDataTables[tf].Addon_tracklocks[i].stack_filepos = page_pos;
          found_page = true;
          break;
        }

        if (found_page)
          break;
      }

      // move on to the next page
      cfseek(file, next_pos, SEEK_SET);
    }

    // done with this tablefile
    cfclose(file);
  }
}

// Error checking variables
bool Loading_addon = false;
int Data_error_count = 0;
FILE *Data_error_file = NULL;
char *Addon_filename;

// Loads and allocs all pages found locally
void mng_LoadAddonPages() {
  CFILE *infile;
  uint8_t pagetype;
  int len;

  // Set flag & Clear error count
  Loading_addon = true;
  Data_error_count = 0;

  if (Num_addon_tables == 0)
    return; // No addons to load

  Loading_locals = 0;

  int c;
  AddOnTablefile *addon;

  for (c = 0; c < Num_addon_tables; c++) {
    addon = &AddOnDataTables[c];

    mprintf(0, "------------------------------------\nLoading addon pages for %s....\n", addon->AddOnTableFilename);
    Addon_filename = addon->AddOnTableFilename;
    infile = cfopen(addon->AddOnTableFilename, "rb");
    if (!infile) {
      mprintf(0, "Couldn't addon table file (%s) to read pages!\n", addon->AddOnTableFilename);
      return;
    }
    Loading_addon_table = c;
    while (!cfeof(infile)) {
      // Read in a pagetype.  If its a page we recognize, load it
      pagetype = cf_ReadByte(infile);
      len = cf_ReadInt(infile);

      mprintf(0, ".");
      switch (pagetype) {
      case PAGETYPE_TEXTURE:
        mng_LoadLocalTexturePage(infile);
        break;
      case PAGETYPE_POWERUP:
      case PAGETYPE_ROBOT:
        Error("Your local table file is invalid.  You must update from the network.");
        break;
      case PAGETYPE_DOOR:
        mng_LoadLocalDoorPage(infile);
        break;
      case PAGETYPE_GENERIC:
        mng_LoadLocalGenericPage(infile);
        break;
      case PAGETYPE_GAMEFILE:
        mng_LoadLocalGamefilePage(infile);
        break;
      case PAGETYPE_SOUND:
        mng_LoadLocalSoundPage(infile);
        break;
      case PAGETYPE_SHIP:
        mng_LoadLocalShipPage(infile);
        break;
      case PAGETYPE_WEAPON:
        mng_LoadLocalWeaponPage(infile);
        break;
      case PAGETYPE_MEGACELL:
        mng_LoadLocalMegacellPage(infile);
        break;
      case PAGETYPE_UNKNOWN:
        break;
      default:
        Int3(); // Unrecognized pagetype, possible corrupt data following
        break;
      }
    }
    mprintf(0, "------------------------------------\n");
    cfclose(infile);
  }

  Loading_locals = 0;
  Loading_addon_table = -1;

  mng_CompileAddonPages();

  // Close error file
  if (Data_error_file != NULL) {
    fprintf(Data_error_file, "\nTotal errors: %d", Data_error_count);
    fclose(Data_error_file);
  }

  // Clear flag
  Loading_addon = false;
}
/*
#define MAX_256s	200
int Num_256s=0;
char Texture256Names[MAX_256s][80];
void Read256TextureNames ()
{
        int n=FindArg ("-File256");
        if (!n)
                return;
        CFILE *infile;
        infile=(CFILE *)cfopen (GameArgs[n+1],"rt");
        if (!infile)
        {
                mprintf(0,"Couldn't open 256 file!\n");
                return;
        }

        char curline[200];
        int done=0;
        while (!done)
        {
                if (cfeof(infile))
                {
                        done=1;
                        continue;
                }

                // Read a line and parse it
                cf_ReadString (curline,200,infile);
                if (curline[0]==';' || curline[1]==';' || curline[0]==' ' || curline[1]==' ')
                        continue;
                if (!(isalnum(curline[0])))
                        continue;
                strcpy (Texture256Names[Num_256s],curline);
                Num_256s++;
        }
        cfclose (infile);
}*/

void DataError(const char *fmt, ...) {
  // Got a data error!
  //	Int3();

  // Ignore this if not loading add-on data
  if (!Loading_addon)
    return;

  // Increment error count
  Data_error_count++;

  // Write to file if switch specified
  if (FindArg("-datacheck")) {
    static char last_filename[_MAX_PATH];
    std::va_list arglist;
    char buf[1024];

    va_start(arglist, fmt);
    std::vsnprintf(buf, sizeof(buf), fmt, arglist);
    va_end(arglist);

    // Open file if not already open
    if (Data_error_file == NULL) {
      Data_error_file = fopen("datacheck.out", "wt");

      if (Data_error_file == NULL)
        return;

      last_filename[0] = 0;
    }

    // If this is a new addon file, print the name
    if (strcmp(last_filename, Addon_filename)) {
      if (last_filename[0])
        fprintf(Data_error_file, "\n\n");
      fprintf(Data_error_file, "Errors in addon file <%s>:\n\n", Addon_filename);
      strcpy(last_filename, Addon_filename);
    }

    // Print the message
    fprintf(Data_error_file, "  ");
    fprintf(Data_error_file, "%s", buf);
  }
}
