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

 * $Logfile: /DescentIII/Main/Mission.cpp $
 * $Revision: 193 $
 * $Date: 10/21/01 4:19p $
 * $Author: Kevin $
 *
 * Mission level sequencing and management.
 *
 * $Log: /DescentIII/Main/Mission.cpp $
 *
 * 193   10/21/01 4:19p Kevin
 * Fix for bug 5566. Reset the URL structure on mission init
 *
 * 192   10/08/01 4:21p Matt
 * If the mission has data errors, tell the user on the loading screen.
 *
 * 191   3/20/00 12:17p Matt
 * Merge of Duane's post-1.3 changes.
 * Mission name changes (Mac only)
 *
 * 190   11/05/99 12:18p Jay
 * Fixed bugs with Jeff's fix
 *
 * 189   11/05/99 11:05a Jeff
 * fixed mission movie playing
 *
 * 188   11/04/99 12:35a Chris
 * Added support for Merc
 *
 * 187   10/25/99 9:52a Matt
 * Mac merge
 *
 * 186   10/12/99 11:05a Jeff
 * new msn keyword "SHIP" to override default ship to something else
 *
 * 185   10/04/99 9:58a Kevin
 * Demo fixes for mac demo
 *
 * 184   8/10/99 5:12p Jeff
 * fixed memory leak
 *
 * 183   7/28/99 4:03p Kevin
 * Macintosh!
 *
 * 182   7/08/99 10:30a Kevin
 * when loading a save game >level 4 from a minimal install, don't ask for
 * CD1
 *
 * 181   6/16/99 12:03p Kevin
 * Fix a stupid bug where minimal installs won't open d3voicex.hog
 *
 * 180   6/10/99 4:12p Kevin
 * Fixed SetLevel in dedicated server for HEAT.NET, and added
 * level_names.str for level name localization.
 *
 * 179   6/03/99 8:48a Kevin
 * fixes for new OEM version....
 *
 * 178   5/20/99 6:21p Kevin
 * Fixed HOARD keyword thingy
 *
 * 177   5/20/99 4:54p Jason
 * added heartbeats to server
 *
 * 176   5/20/99 4:10p Jason
 * added heartbeat to multiplayer so clients wouldn't time out, also
 * various multiplayer fixes
 *
 * 175   5/20/99 3:40p Jason
 * made mission looping work correctly in multiplayer
 *
 * 174   5/07/99 5:06p Jason
 * display level name on loading screen
 *
 * 173   5/03/99 5:12p Jason
 * fixing BOA vis problem...
 *
 * 172   5/03/99 3:35p Kevin
 * bug fixes
 *
 * 171   5/02/99 2:32p Kevin
 * fixed various dedicated server problems.
 *
 * 170   5/01/99 5:12p Jason
 * put BOA check back in
 *
 * 169   5/01/99 4:06p Jeff
 * fixed #include for linux
 *
 * 168   5/01/99 12:42p Kevin
 * removed BOA warning. It was showing up for all levels with no terrain
 *
 * 167   4/30/99 5:41p Jason
 * fixed some boa/terrain level issues
 *
 * 166   4/30/99 3:03p Kevin
 * improved times restored count
 *
 * 165   4/30/99 2:21p Jason
 * changes to verify level completeness
 *
 * 164   4/25/99 2:18p Kevin
 * moved d3 main mission voice files into seperate hogs
 *
 * 163   4/23/99 10:34p Kevin
 * fixed bad things with multiple CD code
 *
 * 162   4/23/99 5:32p Kevin
 * Fixed a few mission bugs.
 *
 * 161   4/23/99 3:33p Kevin
 * mission file/multiplayer mod keyword system
 *
 * 160   4/23/99 10:35a Kevin
 * minor cosmetic changes to the load level screen
 *
 * 159   4/22/99 8:29p Kevin
 * made psrand.h come after stdlib.h
 *
 * 158   4/22/99 9:53a Kevin
 * Fixed some dedicated server crashes
 *
 * 157   4/21/99 2:15p Samir
 * table file filter fixes.
 *
 * 156   4/20/99 3:32p Kevin
 * new prepare for descent behaivor
 *
 * 155   4/20/99 2:47p Matt
 * When playing from the editor, set the level number to 1.
 *
 * 154   4/20/99 12:44a Matt
 * Use briefing font instead of HUD font for level loading messages.
 *
 * 153   4/19/99 6:10p Kevin
 * Demo now only has one multiplayer level
 *
 * 152   4/18/99 1:56p Kevin
 * Movie player fixes to avoid crashes running under the editor
 *
 * 151   4/17/99 6:15p Samir
 * replaced gr.h with grdefs.h and fixed resulting compile bugs.
 *
 * 150   4/17/99 3:44p Kevin
 * Demo2 changes & fixes
 *
 * 149   4/16/99 6:00p Kevin
 * Bunches of Demo stuff
 *
 * 148   4/15/99 1:40a Jeff
 * changes for linux compile
 *
 * 147   4/14/99 3:07p Kevin
 * Fixed some multiple CD bugs
 *
 * 146   4/14/99 12:35p Samir
 * localization issues.
 *
 * 145   4/14/99 2:51a Jeff
 * fixed some case mismatched #includes
 *
 * 144   4/13/99 6:15p Kevin
 * added TXT_PREPARE_FOR_DESCENT
 *
 * 143   4/11/99 4:45p Matt
 * Added code for localization of level goal text.
 *
 * 142   4/08/99 3:13p Matt
 * Finished cleaning up level sequencing code.  Got rid of all the "level
 * minus one" stuff.
 *
 * 141   4/07/99 3:40p Kevin
 * Fixes for Beta 1
 *
 * 140   4/07/99 12:30p Matt
 * Added code for failed missions.
 *
 * 139   4/05/99 2:54p Samir
 * display more errors for mission file load failures.
 *
 * 138   4/03/99 5:23p Matt
 * Removed name, author, & description from the mission level structure.
 *
 * 137   4/03/99 5:05p Samir
 * added ENDMISSION keyword to end a mission after a certain level.
 *
 * 136   3/31/99 10:28a Samir
 * I think this is abug in DoMissionMovie.  Passed the parameter
 * (filename) to GetMultiCDPath.
 *
 * 135   3/29/99 5:32p Kevin
 * Build fixes
 *
 * 134   3/24/99 3:54p Jeff
 * much prettier dedicated server load progress indicators
 *
 * 133   3/24/99 2:56p Kevin
 * Fixed level specific progress indicator to have a default for single
 * player missions, and fixed the default mission name (put it in the
 * stringtable)
 *
 * 132   3/24/99 1:23p Kevin
 * Support for level specific progress screens.
 *
 * 131   3/24/99 11:42a Kevin
 * Fixed multiplayer missions
 *
 * 130   3/24/99 10:54a Kevin
 * Fixed some problems related to splitting up the main d3.mn3 file across
 * 2 CDs
 *
 * 129   3/19/99 4:08p Kevin
 * Multiple CD installation support
 *
 * 128   3/18/99 12:51p Samir
 * debug info.
 *
 * 127   3/09/99 6:34p Kevin
 * Made the training mission not be branching, and fixed the crash with
 * people dying in the demo playback
 *
 * 126   3/05/99 5:24p Jeff
 * fixed mission names for multiplayer levels in oem
 *
 * 125   3/04/99 5:24p Kevin
 * Added filenames for OEM
 *
 * 124   3/03/99 7:20p Jeff
 * music score added for oem levels
 *
 * 123   3/03/99 12:33a Kevin
 * Minor OEM changes
 *
 * 122   3/02/99 7:20p Kevin
 *
 * 121   3/02/99 1:18p Samir
 * reset srclinenum in LoadMission so error box reports correct line num.
 *
 * 120   3/02/99 11:52a Kevin
 * Fixes for OEM Beta 4.1
 *
 * 119   3/02/99 1:23a Kevin
 *
 * 117   3/02/99 12:32a Kevin
 *
 * 116   3/01/99 11:47p Kevin
 *
 * 115   3/01/99 11:38p Kevin
 *
 * 113   3/01/99 9:39p Kevin
 * Doh! #elseif should have been #else
 *
 * 112   3/01/99 9:03p Kevin
 * OEM Beta 4
 *
 * 111   2/28/99 3:26a Samir
 * redid newgame dialog.
 *
 * 110   2/26/99 2:11a Samir
 * messagebox if misison load failed.
 *
 * 109   2/24/99 3:15p Kevin
 * OEM menu changes, and bug fixes for the save/load system
 *
 * 108   2/24/99 2:03p Kevin
 * fixed bug with flickering status bar
 *
 * 107   2/17/99 8:33p Samir
 * fixed potential bugs with mission files that fail top open.
 *
 * 106   2/16/99 12:39p Kevin
 * Improved paging data progress indicator
 *
 * 105   2/16/99 12:36a Kevin
 * Fixes for release builds of OEM V3 and KAtmai
 *
 * 104   2/13/99 1:56p Kevin
 *
 * 103   2/10/99 4:56p Kevin
 * Better progress indicator & prepare for Descent message
 *
 * 102   2/10/99 11:25a Kevin
 *
 * 101   2/09/99 7:01p Kevin
 * First work for new and improved progress screen while loading a level.
 * Note that this is a hack at this point, while I get the details worked
 * out, then I'll make it cleaner.
 *
 * 100   2/04/99 9:28a Kevin
 * Added a few OEM #ifdefs
 *
 * 99    2/03/99 4:20p Kevin
 * Got multiplayer working with .mn3 files, and setup autodownloading
 *
 * 98    2/03/99 2:54p Jeff
 * display telcom if there is a briefing and/or ships to choose from
 *
 * 97    1/29/99 5:22p Jeff
 * localization
 *
 * 96    1/21/99 11:15p Jeff
 * pulled out some structs and defines from header files and moved them
 * into seperate header files so that multiplayer dlls don't require major
 * game headers, just those new headers.  Side effect is a shorter build
 * time.  Also cleaned up some header file #includes that weren't needed.
 * This affected polymodel.h, object.h, player.h, vecmat.h, room.h,
 * manage.h and multi.h
 *
 * 95    1/19/99 1:15p Samir
 * add on missions.
 *
 * 94    1/16/99 10:39a Jeff
 * added mission memory management to Osiris...only slightly tested.  Need
 * to solve game save/restore problem still
 *
 * 93    1/13/99 12:43p Jason
 * fixed flickering exit menu screen
 *
 * 92    1/11/99 12:47p Jason
 * misc changes for polishing
 *
 * 91    1/08/99 2:55p Samir
 * Ripped out OSIRIS1.
 *
 * 90    1/04/99 5:44p Samir
 * added game state flags.
 *
 * 89    12/30/98 12:15p Kevin
 * Auto Mission Download system
 *
 * 88    12/17/98 12:08p Jeff
 * first checkin of new implementation of OSIRIS (old OSIRIS no longer
 * works)
 *
 * 87    12/16/98 3:24p Samir
 * new way to get info on a mission (used to determine training mission
 * too.)
 *
 * 86    12/16/98 1:57p Samir
 * Replaced CleanupString2 with CleanupStr
 *
 * 85    12/03/98 12:51p Samir
 * music score specified per level.
 *
 * 84    11/02/98 6:00p Jeff
 * began adding single player ship selection
 *
 * 83    10/23/98 8:28p Samir
 * enhanced load level screen.
 *
 * 82    10/23/98 12:52p Samir
 * added gray backbar for non splash loading screens.
 *
 * 81    10/22/98 10:49p Samir
 * print out real messages for loadlevel and clear bar when collating.
 *
 * 80    10/22/98 12:46a Matt
 * Got rid of the loading screen before the briefing. Instead, menu.cpp
 * shows the menu background screen (without the menu).
 *
 * 79    10/20/98 6:34p Jeff
 * changes made to get dedicated server working
 *
 * 78    10/19/98 10:35p Kevin
 *
 * 77    10/19/98 7:51p Kevin
 * performance testing
 *
 * 76    10/19/98 5:41p Samir
 * fixed booboo.
 *
 * 75    10/19/98 5:39p Samir
 * added loading level screen.
 *
 * 74    10/18/98 2:58p Jason
 * fixes for beta4
 *
 * 73    10/18/98 12:14p Jeff
 * demo multiplayer mission loops
 *
 * 72    10/14/98 7:30p Matt
 * Fixed compile warning
 *
 * 71    10/14/98 7:19p Kevin
 * More dsp changes...
 *
 * 70    10/14/98 6:40p Samir
 * ShowProgressScreen uses Max_window_w, and height.
 *
 * 69    10/13/98 3:48p Samir
 * added error checking if script failed to load (default).
 *
 * 68    10/11/98 3:04a Jeff
 * for the demo, new was being used to alloc the level node, when it
 * should have been mem_malloc
 *
 * 67    10/09/98 6:58p Kevin
 * changed demo level to polaris.d3l
 *
 * 66    10/08/98 7:29p Samir
 * revamped sequencing.
 *
 * 65    10/08/98 4:23p Kevin
 * Changed code to comply with memory library usage. Always use mem_malloc
 * , mem_free and mem_strdup
 *
 * 64    10/07/98 11:34a Kevin
 *
 * 63    10/06/98 10:36a Kevin
 * updated level names for demo
 *
 * 62    10/06/98 10:34a Kevin
 * Put in demo code for multi
 *
 * 61    10/02/98 5:46p Samir
 * took out mission file objective text and replaced with level goals.
 *
 * 60    9/22/98 3:56p Samir
 * special demo code doesn't allow pilot and mission stuff.
 *
 * 59    9/15/98 4:31p Jason
 * added more functionality for the dedicated server
 *
 * 58    9/14/98 6:28p Jason
 * first pass at getting dedicated server working
 *
 * 57    8/28/98 12:57p Jeff
 * parm added to TelComShow
 *
 * 56    8/27/98 2:51p Jeff
 * made it so SHIFT-ESC exits the TelCom back to Main Menu
 *
 * 55    8/24/98 5:04p Kevin
 * Made msn files have the option to not be playable in multiplayer
 *
 * 54    8/20/98 10:53a Samir
 * check Current_level pointer for validity.
 *
 * 53    8/18/98 1:10a Samir
 * some reorg of scripting and intrasave mission managment.
 *
 * 52    7/31/98 5:19p Samir
 * mission filenames are dynamically allocated now to allow for pathnames
 * (since we'd have too many 256 char arrays per level.
 *
 * 51    6/18/98 4:49p Kevin
 * Updated multiplayer menus
 *
 * 50    6/16/98 10:54a Jeff
 *
 * 49    5/25/98 8:19p Samir
 * skip telcom if no briefing file and other stuff.
 *
 * 48    5/21/98 2:32p Samir
 * added full support for intra-mission level branching.
 *
 * 47    5/18/98 3:56p Samir
 * added D3_FAST mode to quickly enter and exit games.
 *
 * 46    5/05/98 5:17p Samir
 * took out loading level message.
 *
 * 45    4/24/98 1:53a Samir
 * took care of a lot of scripting memory leaks.
 *
 * 44    4/21/98 4:15a Samir
 * memory stuf.
 *
 * 43    4/20/98 11:30a Jason
 * Added ShowProgressScreen function
 *
 * 42    4/18/98 7:17a Samir
 * Added level objective descriptions to mission file.
 *
 * 41    4/14/98 7:50p Matt
 * Added system to keep info for each level
 *
 * 40    4/02/98 11:11a Samir
 * Error checking for level load/misison init fail.
 *
 * 39    3/31/98 3:49p Jason
 * added memory lib
 *
 * 38    3/30/98 6:29p Samir
 * Load default null script.
 *
 * 37    2/17/98 6:54p Samir
 * clear screen.
 *
 * 36    2/17/98 6:13p Jeff
 * Changed it so TelCom is forced to go into Briefings when called
 *
 * 35    2/17/98 4:42p Samir
 * Current_level is now defined after calling DoLevelIntro.
 *
 * 34    2/13/98 10:57a Samir
 * Changed some gamescript initialization.
 *
 * 33    2/12/98 5:08p Matt
 * Reset cockpit mode when starting a level.  Unfortunately, this involved
 * some semi-major mucking with game sequencing.
 *
 * 32    2/08/98 5:01p Samir
 * New game sequencing changes.
 *
 * 31    1/21/98 5:27p Jason
 * Don't reposition player object if going from editor to game
 *
 * 30    1/21/98 1:11p Jason
 * incremental checkin for multiplayer
 *
 * 29    1/20/98 6:01p Jason
 * first pass at getting multiplayer deaths working
 *
 * 28    1/15/98 11:10a Jeff
 * Added call to set font color before 'loading level' so its white, also
 * turned back on Telcom
 *
 * 27    1/08/98 12:32p Samir
 * Initialize new player ship when quick starting mission.
 *
 * 26    12/29/97 5:51p Samir
 * Use new text system to draw "loading" screen.
 *
 * 25    12/19/97 12:33p Samir
 * Dont call telcom for now.
 *
 * 24    11/16/97 3:43p Samir
 * Briefing filename now defined in mission level structure.
 *
 * 23    11/10/97 12:37p Samir
 * When leaving telcom, restore to cinematics mode for simple 2d message.
 *
 * 22    10/16/97 4:41p Samir
 * Set initial level state to start when quick starting mission.
 *
 * 21    10/03/97 11:58a Samir
 * Added mission name
 *
 * 20    10/02/97 12:36p Samir
 * Redid game sequencing flow.
 *
 * 19    9/30/97 5:33p Samir
 * Added GameSequencer.
 *
 * 18    9/22/97 5:59p Samir
 * Changed ObjCScript system, so everything is broken, but it shouldn't
 * crash the game.
 *
 * 17    9/15/97 6:26p Samir
 * Added loading level message.
 *
 * 16    9/12/97 4:07p Samir
 * Simplified movie playing.
 *
 * 15    9/10/97 4:40p Samir
 * Fixed a boo-boo
 *
 * 14    9/10/97 3:59p Samir
 * Inititalize a mini mission when playing from editor, and compile level
 * script when playing from editor always.
 *
 * 13    9/10/97 1:56p Samir
 * Added more scripting initialization.
 *
 * 12    9/05/97 1:21p Samir
 * Moved around a bunch of initialization code to InitThisLevel which is
 * located in game.cpp.   This is called every time you die, start a
 * level, etc.
 *
 * 11    8/21/97 5:57p Samir
 * Added some scripti loading/saving calls and took out some useless
 * interface stuff
 *
 * 10    8/15/97 6:33p Samir
 * Changes reflecting enhanced editor scripting.
 *
 * 9     8/12/97 5:31p Jason
 * nulled out pointer when quitting mission.
 *
 * 8     8/12/97 3:22p Samir
 * Initialize scripts at start of level.
 *
 * 7     8/06/97 10:38a Samir
 * Fixed call to D3XReallocProgram
 *
 * 6     8/05/97 9:59a Samir
 * Scripting stuff.
 *
 * 5     7/23/97 3:55p Jeff
 * fixed TeleCom* calls to TelCom
 *
 * 4     7/23/97 3:53p Jeff
 *
 * 3     7/23/97 3:43p Samir
 * Added telecom stuff.
 *
 * 7     6/11/97 2:20p Samir
 * Changed gameos to new system.
 *
 * 6     6/05/97 12:21p Samir
 * Added more mission commands.
 *
 * 5     5/16/97 6:13p Samir
 * Check for EOF in mission file this time.
 *
 * 4     5/16/97 3:11p Samir
 * Added a mission name and mission initializer.
 *
 * 3     5/15/97 6:58p Samir
 * Small briefing changes.
 *
 * 2     5/15/97 2:09p Samir
 * Added a bunch of sequencing from level to level, loading mission.
 *
 * 1     4/29/97 11:57a Samir
 * Initial revision
 *
 * $NoKeywords: $
 */
#include "Mission.h"
#include "3d.h"
#include "LoadLevel.h"
#include "pserror.h"
#include "cfile.h"
#include "gamefont.h"
#include "grdefs.h"
#include "descent.h"
#include "ddio.h"
#include "movie.h"
#include "program.h"
#include "object.h"
#include "objinit.h"
#include "ObjScript.h"
#include "application.h"
#include "TelCom.h"
#include "game.h"
#include "cinematics.h"
#include "player.h"
#include "gamesequence.h"
#include "mem.h"
#include "newui.h"
#include "stringtable.h"
#include "AppConsole.h"
#include "pstring.h"
#include "dedicated_server.h"
#include "osiris_dll.h"
#include "mission_download.h"
#include "manage.h"
#include <string.h>
#include <stdlib.h>
#include "ship.h"
#include "BOA.h"
#include "terrain.h"
#include "multi.h"
#include "hud.h"
//	---------------------------------------------------------------------------
//	Data
//	---------------------------------------------------------------------------
// Info about the current level
level_info Level_info;
tMission Current_mission;
tLevelNode *Current_level = NULL;
char D3MissionsDir[_MAX_PATH];
extern int Times_game_restored;
extern msn_urls Net_msn_URLs;

//	---------------------------------------------------------------------------
//	Function prototypes
//	---------------------------------------------------------------------------
bool InitMissionScript();
void DoEndMission();
void DoMissionMovie(const char *movie);
void FreeMission();
// used in load level callback
void LoadLevelCB(const char *chunk, int curlen, int filelen);
//	MN3 based mission functions.
// loads the msn file from the mn3 file specified, specifies the hog and table file.
bool mn3_Open(const char *mn3file);
// returns mission information given the mn3 file.
bool mn3_GetInfo(const char *mn3file, tMissionInfo *msn);
// closes the current mn3 file
void mn3_Close();

static inline bool IS_MN3_FILE(const char *fname) {
  char name[PSFILENAME_LEN + 1];
  char ext[PSFILENAME_LEN + 1];
  ddio_SplitPath(fname, NULL, name, ext);
  return (stricmp(ext, ".mn3") == 0) ? true : false;
}

static inline char *MN3_TO_MSN_NAME(const char *mn3name, char *msnname) {
  char fname[PSFILENAME_LEN + 1];
  ddio_SplitPath(mn3name, NULL, fname, NULL);

  if (stricmp(fname, "d3_2") == 0) {
    strcpy(fname, "d3");
  }
  strcat(fname, ".msn");
  strcpy(msnname, fname);
  return msnname;
}

//	---------------------------------------------------------------------------
//	Functions
//	---------------------------------------------------------------------------

///////////////////////////////////////////////////////////////////////////////
//	High level mission stuff
///////////////////////////////////////////////////////////////////////////////
void InitMission() {
  mprintf(0, "In InitMission()\n");
  Current_mission.num_levels = 0;
  Current_mission.cur_level = 0;
  memset(Current_mission.desc, 0, sizeof(Current_mission.desc));
  memset(Current_mission.name, 0, MSN_NAMELEN);
  memset(Current_mission.author, 0, MSN_NAMELEN);
  memset(Current_mission.email, 0, MSN_URLLEN);
  memset(Current_mission.web, 0, MSN_URLLEN);
  Current_mission.hog = NULL;
  Current_mission.levels = NULL;
  Current_mission.filename = NULL;
  Current_mission.game_state_flags = 0;
  Current_mission.mn3_handle = 0;
  //	create add on mission directory
  ddio_MakePath(D3MissionsDir, LocalD3Dir, "missions", NULL);
  if (!ddio_DirExists(D3MissionsDir)) {
    if (!ddio_CreateDir(D3MissionsDir)) {
      Error(TXT_MSN_FAILEDCREATEDIR);
    }
  }
  atexit(ResetMission);
}
//	reset all states for a mission
void ResetMission() {
  mprintf(0, "In ResetMission()\n");
  FreeMission();
  Current_mission.num_levels = 0;
  Current_mission.cur_level = 0;
  memset(Current_mission.desc, 0, sizeof(Current_mission.desc));
  memset(Current_mission.name, 0, MSN_NAMELEN);
  memset(Current_mission.author, 0, MSN_NAMELEN);
  memset(Current_mission.email, 0, MSN_URLLEN);
  memset(Current_mission.web, 0, MSN_URLLEN);
  Current_mission.hog = NULL;
  Current_mission.levels = NULL;
  Current_mission.filename = NULL;
  Current_mission.game_state_flags = 0;

  // clear out old URLs from memory
  for (int a = 0; a < MAX_MISSION_URL_COUNT; a++) {
    Net_msn_URLs.URL[a][0] = '\0';
  }
}
#if (defined(OEM) || defined(DEMO))
bool DemoMission(int mode = 0) {
  tMission *msn = &Current_mission;
  tLevelNode *lvls = (tLevelNode *)mem_malloc(sizeof(tLevelNode) * 5);
  msn->cur_level = 1;
  msn->num_levels = 1;
  msn->levels = lvls;

  msn->multiplayable = true;
  msn->singleplayable = true;

  memset(lvls, 0, sizeof(tLevelNode) * msn->num_levels);
  strncpy(msn->author, "Outrage", MSN_NAMELEN - 1);
  if (!mode) {
    strcpy(msn->name, "Descent 3: Sol Ascent");
    msn->num_levels = 5;
    memset(lvls, 0, sizeof(tLevelNode) * msn->num_levels);
#ifdef DEMO
    msn->multiplayable = false;
    strcpy(msn->name, "Descent 3: Demo2");
    msn->num_levels = 1;
    msn->filename = mem_strdup("d3demo.mn3");
#else
    strcpy(msn->name, "Descent 3: Sol Ascent");
    msn->num_levels = 5;
    msn->filename = mem_strdup("d3oem.mn3");
#endif
    // strncpy(lvls[0].name, "Search for Sweitzer", MSN_NAMELEN-1);
    lvls[0].flags = LVLFLAG_BRIEFING | LVLFLAG_SCORE;
    lvls[0].filename = mem_strdup("level1.d3l");
    lvls[0].briefname = mem_strdup("level1.brf");
    lvls[0].score = mem_strdup("level1.omf");
    lvls[0].progress = mem_strdup("l1load.ogf");
    lvls[0].moviename = mem_strdup("level1.mve");
#ifndef DEMO
    // strncpy(lvls[0].name, "Into the Heart of the Ship", MSN_NAMELEN-1);
    lvls[1].flags = LVLFLAG_BRIEFING | LVLFLAG_SCORE;
    lvls[1].filename = mem_strdup("level3.d3l");
    lvls[1].briefname = mem_strdup("level2o.brf");
    lvls[1].score = mem_strdup("level3.omf");
    lvls[1].progress = mem_strdup("l3load.ogf");
    // strncpy(lvls[0].name, "The Nomad Caves", MSN_NAMELEN-1);
    lvls[2].flags = LVLFLAG_BRIEFING | LVLFLAG_SCORE;
    lvls[2].filename = mem_strdup("level6.d3l");
    lvls[2].briefname = mem_strdup("level3o.brf");
    lvls[2].score = mem_strdup("level6.omf");
    lvls[2].progress = mem_strdup("l6load.ogf");
    // strncpy(lvls[0].name, "The Transmode Virus", MSN_NAMELEN-1);
    lvls[3].flags = LVLFLAG_BRIEFING | LVLFLAG_SCORE;
    lvls[3].filename = mem_strdup("level7.d3l");
    lvls[3].briefname = mem_strdup("level4o.brf");
    lvls[3].score = mem_strdup("level7.omf");
    lvls[3].progress = mem_strdup("l7load.ogf");
    // strncpy(lvls[0].name, "The Rescue", MSN_NAMELEN-1);
    lvls[4].flags = LVLFLAG_BRIEFING | LVLFLAG_SCORE;
    lvls[4].filename = mem_strdup("level11.d3l");
    lvls[4].briefname = mem_strdup("level5o.brf");
    lvls[4].score = mem_strdup("level11.omf");
    lvls[4].progress = mem_strdup("l11load.ogf");
    mn3_Open("d3oem.mn3");
#endif

  }

  else if (mode == 1) {
    strcpy(msn->name, "Polaris");
    msn->filename = mem_strdup("Polaris.d3l");
    // strncpy(lvls[0].name, "Polaris", MSN_NAMELEN-1);
    lvls[0].filename = mem_strdup("polaris.d3l");
    lvls[0].flags |= LVLFLAG_BRANCH;
    lvls[0].lvlbranch0 = 1;
    lvls[0].progress = mem_strdup("polaris.ogf");
  } else if (mode == 2) {
    strcpy(msn->name, "The Core");
    msn->filename = mem_strdup("TheCore.d3l");
    // strncpy(lvls[0].name, "The Core", MSN_NAMELEN-1);
    lvls[0].filename = mem_strdup("thecore.d3l");
    lvls[0].flags |= LVLFLAG_BRANCH;
    lvls[0].lvlbranch0 = 1;
    lvls[0].progress = mem_strdup("thecore.ogf");
  } else if (mode == 3) {
    strcpy(msn->name, "Taurus");
    msn->filename = mem_strdup("Taurus.d3l");
    // strncpy(lvls[0].name, "Taurus", MSN_NAMELEN-1);
    lvls[0].filename = mem_strdup("taurus.d3l");
    lvls[0].flags |= LVLFLAG_BRANCH;
    lvls[0].lvlbranch0 = 1;
    lvls[0].progress = mem_strdup("taurus.ogf");
  }
#ifndef DEMO
  else if (mode == 4) {
    strcpy(msn->name, "Pilot Training");
    msn->filename = mem_strdup("training.mn3");
    // strncpy(lvls[0].name, "Training", MSN_NAMELEN-1);
    lvls[0].filename = mem_strdup("trainingmission.d3l");
    lvls[0].briefname = NULL; // mem_strdup("training.brf");
    lvls[0].flags = 0;
    lvls[0].lvlbranch0 = 0;
    lvls[0].progress = mem_strdup("trainingload.ogf");
    mn3_Open("training.mn3");
  }
#endif
  //	load default script here.
  InitMissionScript();
  return true;
}
#endif

bool LoadMission(const char *mssn) {
  Times_game_restored = 0;
  mprintf(0, "In LoadMission()\n");
//	ShowProgressScreen(TXT_LOADINGLEVEL);
#if (defined(OEM) || defined(DEMO))
#ifdef OEM
  if (stricmp(mssn, "d3oem.mn3") == 0)
    return DemoMission(0);
#elif defined(DEMO)
  if (stricmp(mssn, "d3demo.mn3") == 0)
    return DemoMission(0);
#endif
  else if (stricmp(mssn, "polaris.d3l") == 0)
    return DemoMission(1);
  else if (stricmp(mssn, "thecore.d3l") == 0)
    return DemoMission(2);
  else if (stricmp(mssn, "taurus.d3l") == 0)
    return DemoMission(3);
#ifdef OEM
  else if (stricmp(mssn, "training.mn3") == 0)
    return DemoMission(4);
#endif
#else

  // #endif
  tLevelNode *lvls = NULL; // Temporary storage for level data.
  tMission *msn;
  CFILE *fp = NULL; // Mission file
  char errtext[80]; // Stores error if unable to read mission
  char msnfname[_MAX_PATH];
  char mission[_MAX_PATH];
  int srclinenum = 0; // Current line of source.
  int curlvlnum;      // Current level number
  int numlevels;      // Number of levels required to read in.
  int cur_objective;  // current objective reading.
  bool indesc;        // are we in a multi-line block
  bool res = false;   // used to specify if no error has occurred.
  char pathname[_MAX_PATH];
  ResetMission(); // Reset everything.
                  // open MN3 if filename passed was an mn3 file.

  if (IS_MN3_FILE(mssn)) {
    strcpy(mission, mssn);
    ddio_MakePath(pathname, D3MissionsDir, mission, NULL);
  } else {
    strcpy(mission, mssn);
    strcpy(pathname, mssn);
    strcpy(msnfname, mssn);
    // ddio_MakePath(pathname, D3MissionsDir, mission, NULL);
  }
  if (IS_MN3_FILE(mission)) {

    if (!mn3_Open(pathname)) {
      strcpy(errtext, TXT_MSN_OPENMN3FAILED);
      goto msnfile_error;
    }
    MN3_TO_MSN_NAME(mission, msnfname);
  }
  //	open mission file
  fp = cfopen(msnfname, "rt");
  if (!fp) {
    strcpy(errtext, TXT_MISSIONNOTFOUND);
    goto msnfile_error;
  }
  msn = &Current_mission;

  //	read in mission file
  srclinenum = 1;
  numlevels = -1;
  curlvlnum = 0;
  indesc = 0;
  cur_objective = -1;
  msn->multiplayable = true;
  msn->singleplayable = true;
  msn->training_mission = false;

  while (!cfeof(fp)) {
    char srcline[128]; // One line of mission source
    char command[32];  // Command read from line.
    char operand[96];  // operand read from line
    char *keyword;     // parsed keyword
    int readcount;     // read-in count
    readcount = cf_ReadString(srcline, sizeof(srcline), fp);
    if (readcount) {
      //	we have a line of source.  parse out primary keyword
      //	then parse out remainder.
      keyword = strtok(srcline, " \t");
      CleanupStr(command, srcline, sizeof(command));
      CleanupStr(operand, srcline + strlen(command) + 1, sizeof(operand));
      if (strlen(command) && indesc)
        indesc = 0;
      if (!stricmp(command, "NAME")) {
        strncpy(msn->name, operand, MSN_NAMELEN - 1);
      } else if (!stricmp(command, "MULTI")) {
        if (stricmp("no", operand) == 0)
          msn->multiplayable = false;
      } else if (!stricmp(command, "SINGLE")) {
        if (stricmp("no", operand) == 0)
          msn->singleplayable = false;
      } else if (!stricmp(command, "TRAINER")) {
        if (curlvlnum == 0) {
          msn->training_mission = true;
        } else {
          strcpy(errtext, TXT_MSN_MSNCOMMAND);
          goto msnfile_error;
        }
      } else if (!stricmp(command, "AUTHOR")) {
        strncpy(msn->author, operand, MSN_NAMELEN - 1);
      } else if (!stricmp(command, "KEYWORDS")) {
        // Don't do anything with this
      } else if (!stricmp(command, "DESCRIPTION") || indesc) {
        //	multi-line descriptions require the strcat.  the initial
        //	strings should be empty for this to work.
        strcat(msn->desc, operand);
        if (indesc)
          strcat(msn->desc, "\n");
        indesc = 1; // this is a multiline command
      } else if (!stricmp(command, "URL")) {
        if (curlvlnum != 0) {
          strcpy(errtext, TXT_MSN_LVLCOMMAND);
          goto msnfile_error;
        } else {
          for (int a = 0; a < MAX_MISSION_URL_COUNT; a++) {
            if (Net_msn_URLs.URL[a][0] == '\0') {
              strncpy(Net_msn_URLs.URL[a], operand, MAX_MISSION_URL_LEN - 1);
              Net_msn_URLs.URL[a][MAX_MISSION_URL_LEN - 1] = '\0';
              mprintf(0, "Found a Mission URL: %s\n", operand);
              break;
            }
          }
        }
      } else if (!stricmp(command, "SHIP")) {
        // there is a different default ship
        if (curlvlnum != 0) {
          strcpy(errtext, TXT_MSN_LVLCOMMAND);
          goto msnfile_error;
        } else {
          int ship_index = FindShipName(operand);
          if (ship_index != -1) {
            // ok the ship exists, make this guy the new default ship
            PlayerResetShipPermissions(-1, false);
            PlayerSetShipPermission(-1, operand, true);
            mprintf(0, "MAKING %s THE NEW DEFAULT SHIP!\n", operand);
          } else {
            Int3();
          }
        }
      } else if (!stricmp(command, "EMAIL")) {
        if (curlvlnum != 0) {
          strcpy(errtext, TXT_MSN_LVLCOMMAND);
          goto msnfile_error;
        } else
          strncpy(msn->email, operand, MSN_URLLEN - 1);
      } else if (!stricmp(command, "SCORE")) {
        if (curlvlnum == 0) {
          strcpy(errtext, TXT_MSN_LVLCOMMAND);
          goto msnfile_error;
        } else {
          lvls[curlvlnum - 1].flags |= LVLFLAG_SCORE;
          lvls[curlvlnum - 1].score = mem_strdup(operand);
          if (!lvls[curlvlnum - 1].score)
            goto fatal_error;
        }
      } else if (!stricmp(command, "PROGRESS")) {
        if (curlvlnum == 0) {
          strcpy(errtext, TXT_MSN_LVLCOMMAND);
          goto msnfile_error;
        } else {
          lvls[curlvlnum - 1].progress = mem_strdup(operand);
          if (!lvls[curlvlnum - 1].progress)
            goto fatal_error;
        }
      } else if (!stricmp(command, "HOG")) {
        if (curlvlnum == 0) {
          msn->hog = mem_strdup(operand);
          if (!msn->hog)
            goto fatal_error;
        } else {
          lvls[curlvlnum - 1].flags |= LVLFLAG_SPECIALHOG;
          if (!(lvls[curlvlnum - 1].hog = mem_strdup(operand)))
            goto fatal_error;
        }
      } else if (!stricmp(command, "NUMLEVELS")) {
        if (curlvlnum != 0) {
          strcpy(errtext, TXT_MSN_LVLCOMMAND);
          goto msnfile_error;
        } else {
          //	get number of levels
          int value = atoi(operand);
          if (value == 0) {
            strcpy(errtext, TXT_MSN_LVLNUMINVALID);
            goto msnfile_error;
          }
          lvls = (tLevelNode *)mem_malloc(sizeof(tLevelNode) * value);
          memset(lvls, 0, sizeof(tLevelNode) * value);
          numlevels = value;
        }
      } else if (!stricmp(command, "LEVEL")) {
        // first check if number of level is greater than num_levels
        if ((curlvlnum == numlevels) && (numlevels != -1)) {
          strcpy(errtext, TXT_MSN_NUMLVLSINVALID);
          goto msnfile_error;
        }
        curlvlnum = atoi(operand);
        if (curlvlnum == 0) {
          strcpy(errtext, TXT_MSN_LVLNUMINVALID);
          goto msnfile_error;
        } else if (curlvlnum > numlevels || curlvlnum < 0) {
          strcpy(errtext, TXT_MSN_LVLNUMINVALID);
          goto msnfile_error;
        }
      } else if (!stricmp(command, "INTROMOVIE")) {
        if (curlvlnum == 0) {
          strcpy(errtext, TXT_MSN_LVLCOMMAND);
          goto msnfile_error;
        } else {
          lvls[curlvlnum - 1].flags |= LVLFLAG_STARTMOVIE;
          if (!(lvls[curlvlnum - 1].moviename = mem_strdup(operand)))
            goto fatal_error;
        }
      } else if (!stricmp(command, "INTRODEFAULT")) {
        if (curlvlnum == 0) {
          strcpy(errtext, TXT_MSN_LVLCOMMAND);
          goto msnfile_error;
        } else if (!Descent_overrided_intro) {
          lvls[curlvlnum - 1].flags |= LVLFLAG_STARTMOVIE;
          if (!(lvls[curlvlnum - 1].moviename = mem_strdup(operand)))
            goto fatal_error;
        }
      } else if (!stricmp(command, "ENDMOVIE")) {
        if (curlvlnum == 0) {
          strcpy(errtext, TXT_MSN_LVLCOMMAND);
          goto msnfile_error;
        } else {
          lvls[curlvlnum - 1].flags |= LVLFLAG_ENDMOVIE;
          if (!(lvls[curlvlnum - 1].endmovie = mem_strdup(operand)))
            goto fatal_error;
        }
      } else if (!stricmp(command, "MINE")) {
        if (curlvlnum == 0) {
          strcpy(errtext, TXT_MSN_LVLCOMMAND);
          goto msnfile_error;
        } else {
          if (!(lvls[curlvlnum - 1].filename = mem_strdup(operand)))
            goto fatal_error;
        }
      } else if (!stricmp(command, "SECRET")) {
        if (curlvlnum == 0) {
          strcpy(errtext, TXT_MSN_LVLCOMMAND);
          goto msnfile_error;
        } else {
          lvls[curlvlnum - 1].flags |= LVLFLAG_SPAWNSECRET;
          lvls[curlvlnum - 1].secretlvl = atoi(operand);
        }
      } else if (!stricmp(command, "BRIEFING")) {
        if (curlvlnum == 0) {
          strcpy(errtext, TXT_MSN_LVLCOMMAND);
          goto msnfile_error;
        } else {
          lvls[curlvlnum - 1].flags |= LVLFLAG_BRIEFING;
          if (!(lvls[curlvlnum - 1].briefname = mem_strdup(operand)))
            goto fatal_error;
        }
      } else if (!stricmp(command, "BRANCH")) {
        // first check if number of level is greater than num_levels
        int lvlnum;
        if (curlvlnum == 0) {
          strcpy(errtext, TXT_MSN_LVLCOMMAND);
          goto msnfile_error;
        }
        lvlnum = atoi(operand);
        if (lvlnum == 0 || lvlnum > numlevels) {
          strcpy(errtext, TXT_MSN_LVLNUMINVALID);
          goto msnfile_error;
        }
        lvls[curlvlnum - 1].flags |= LVLFLAG_BRANCH;
        lvls[curlvlnum - 1].lvlbranch0 = lvlnum;
      } else if (!stricmp(command, "ENDMISSION")) {
        if (curlvlnum == 0) {
          strcpy(errtext, TXT_MSN_LVLCOMMAND);
          goto msnfile_error;
        } else {
          lvls[curlvlnum - 1].flags |= LVLFLAG_FINAL;
        }
      } else {
        snprintf(errtext, sizeof(errtext), TXT_MSN_ILLEGALCMD, command);
        goto msnfile_error;
      }
    }
    srclinenum++;
  }
  //	set up current mission (movies are already set above)
  msn->cur_level = 1;
  msn->num_levels = numlevels;
  msn->levels = lvls;
  msn->filename = mem_strdup(mission);
  msn->game_state_flags = 0;
  strcpy(Net_msn_URLs.msnname, mission);
  res = true; // everthing is ok.
//	if error, print it out, else end.
msnfile_error:
  if (!res) {
    char str_text[128];
    snprintf(str_text, sizeof(str_text), "%s\nline %d.", errtext, srclinenum);
    if (!Dedicated_server) {
      DoMessageBox(TXT_ERROR, str_text, MSGBOX_OK);
    } else {
      PrintDedicatedMessage("%s: %s\n", TXT_ERROR, str_text);
    }
    if (lvls)
      mem_free(lvls);
  }
  if (fp)
    cfclose(fp);
  //	load default script here.
  if (!InitMissionScript()) {
    return false;
  }
  return res;
fatal_error:
  mem_error();
  return false;
#endif
  return false;
}
void FreeMission() {
  //	Free up mission script
  int i; //,j;
  // close MN3 file if there is one.
  mn3_Close();
  // Tell Osiris to shutdown the Osiris Mission Memory System, freeing all memory
  Osiris_CloseOMMS();
  if (Current_mission.levels) {
    //	free up any data allocated per level node.
    for (i = 0; i < Current_mission.num_levels; i++) {
      if (Current_mission.levels[i].filename)
        mem_free(Current_mission.levels[i].filename);
      if (Current_mission.levels[i].briefname)
        mem_free(Current_mission.levels[i].briefname);
      if (Current_mission.levels[i].hog)
        mem_free(Current_mission.levels[i].hog);
      if (Current_mission.levels[i].moviename)
        mem_free(Current_mission.levels[i].moviename);
      if (Current_mission.levels[i].endmovie)
        mem_free(Current_mission.levels[i].endmovie);
      if (Current_mission.levels[i].score)
        mem_free(Current_mission.levels[i].score);
      if (Current_mission.levels[i].progress)
        mem_free(Current_mission.levels[i].progress);
    }
    mem_free(Current_mission.levels);
    Current_mission.levels = NULL;
  }
  //@@	if (Current_mission.d3xmod) {
  //@@		D3XFreeProgram(Current_mission.d3xmod);
  //@@		Current_mission.d3xmod = NULL;
  //@@	}
  if (Current_mission.hog)
    mem_free(Current_mission.hog);
  if (Current_mission.filename) {
    // these DON't USE mem_free since we use _strdup, which doesn't use our memory routines.
    mem_free(Current_mission.filename);
    Current_mission.filename = NULL;
  }
  Current_mission.hog = NULL;
  Current_level = NULL;
}
#include "localization.h"
#include "levelgoal.h"
// Load the text (goal strings) for a level
void LoadLevelText(const char *level_filename) {
  char pathname[_MAX_FNAME], filename[_MAX_FNAME];
  int n_strings;
  ddio_SplitPath(level_filename, pathname, filename, NULL);
  strcat(pathname, filename);
  strcat(pathname, ".str");
  char **goal_strings;
  if (CreateStringTable(pathname, &goal_strings, &n_strings)) {
    int n_goals = Level_goals.GetNumGoals();
    ASSERT(n_strings == (n_goals * 3));
    for (int i = 0; i < n_goals; i++) {
      Level_goals.GoalSetName(i, goal_strings[i * 3]);
      Level_goals.GoalSetItemName(i, goal_strings[i * 3 + 1]);
      Level_goals.GoalSetDesc(i, goal_strings[i * 3 + 2]);
    }
    DestroyStringTable(goal_strings, n_strings);
  }
}

/*	loads a level and sets it as current level in mission
 */
bool LoadMissionLevel(int level) {
  Hud_show_controls = false;
  LoadLevelProgress(LOAD_PROGRESS_START, 0);
  if (!LoadLevel(Current_mission.levels[level - 1].filename, NULL)) {
    char buf[128];
    snprintf(buf, sizeof(buf), TXT_MSNERROR, Current_mission.levels[level - 1].filename);
    SetUICallback(DEFAULT_UICALLBACK);
    DoMessageBox(TXT_ERROR, buf, MSGBOX_OK);
    LoadLevelProgress(LOAD_PROGRESS_DONE, 0);
    return false;
  }
  // Test to see if levels are valid
  bool boa = true, terrain = true;
  char str[255];

  if (BOAGetMineChecksum() != BOA_vis_checksum)
    boa = false;
  if (GetTerrainGeometryChecksum() != Terrain_checksum)
    terrain = false;

  // JC: This isn't going to be fixed for a while, so silence the error
  /*
  if (!boa) {
    snprintf(str, sizeof(str), "BOA NOT VALID! %s", terrain ? "" : "TERRAINOCC NOT VALID!");
    ShowProgressScreen(str, NULL, true);
    Sleep(2000);
  } */

  LoadLevelText(Current_mission.levels[level - 1].filename);

  return true;
}
#define LOADBAR_X (16 * (float)Max_window_w / (float)FIXED_SCREEN_WIDTH)
#define LOADBAR_Y1 (376 * (float)Max_window_h / (float)FIXED_SCREEN_HEIGHT)
#define LOADBAR_Y2 (440 * (float)Max_window_h / (float)FIXED_SCREEN_HEIGHT)
#define LOADBAR_W (260 * (float)Max_window_w / (float)FIXED_SCREEN_WIDTH)
#define LOADBAR_H (22 * (float)Max_window_h / (float)FIXED_SCREEN_HEIGHT)
#define N_LOAD_MSGS 12
bool started_page = 0;
/*
$$TABLE_GAMEFILE "tunnelload.ogf"
*/
bool Progress_screen_loaded = false;
void LoadLevelProgress(int step, float percent, const char *chunk) {
  static tLargeBitmap level_bmp;
  static bool level_bmp_loaded = false;
  static int dedicated_last_string_len = -1;
  float lvl_percent_loaded = 0;
  float pag_percent_loaded = 0;
  int i;
  static int n_text_msgs = 0;
  static char text_msgs[N_LOAD_MSGS][80];
  char str[80];
  // If we're loading a level, send out a heartbeat
  if ((Game_mode & GM_MULTI)) {
    MultiSendHeartbeat();
  }
  if (percent > 1.0f) {
    percent = 1.0f;
  } else if (percent < 0.0f) {
    percent = 0.0f;
  }
  if ((!Progress_screen_loaded) && (step != LOAD_PROGRESS_START))
    return;
  switch (step) {
  case LOAD_PROGRESS_START: {
    lvl_percent_loaded = 0.0f;
    pag_percent_loaded = 0.0f;
    dedicated_last_string_len = -1;
    const char *p = NULL;
    if ((!(Game_mode & GM_MULTI)) && (!Current_mission.levels[Current_mission.cur_level - 1].progress)) {
      p = "tunnelload.ogf";
    } else {
      p = Current_mission.levels[Current_mission.cur_level - 1].progress;
    }

    if (p) {
      if (LoadLargeBitmap(IGNORE_TABLE(p), &level_bmp)) {
        SetScreenMode(SM_MENU);
        level_bmp_loaded = true;
        n_text_msgs = 0;
      }
    }
    /*
    else
    {
            ShowProgressScreen (TXT_LOADINGLEVEL);
    }
    */
    Progress_screen_loaded = true;
    return;
  } break;
  case LOAD_PROGRESS_LOADING_LEVEL: {
    lvl_percent_loaded = percent;
  } break;
  case LOAD_PROGRESS_PAGING_DATA: {
    lvl_percent_loaded = 1.0f;
    pag_percent_loaded = percent;
  } break;
  case LOAD_PROGRESS_PREPARE:
    if (Dedicated_server) {
      PrintDedicatedMessage("\n");
    }
    lvl_percent_loaded = 1.0f;
    pag_percent_loaded = 1.0f;
    mprintf(0, "Prepare for Descent goes here...\n");
    // ShowProgressScreen(TXT_PREPARE_FOR_DESCENT,NULL,true);
    // return;
    break;
  case LOAD_PROGRESS_DONE: {
    if (level_bmp_loaded) {
      // print out final message
      FreeLargeBitmap(&level_bmp);
      level_bmp_loaded = false;
    }
    Progress_screen_loaded = false;
    if (Dedicated_server) {
      PrintDedicatedMessage("\n");
    }
    return;
  } break;
  default:
    mprintf(0, "Unknown step in LoadLevelProgress()\n");
    Int3();
  }
  if (Dedicated_server) {
    char tbuffer[512];
    char tbuffer1[512];
    nw_DoNetworkIdle();
    if (dedicated_last_string_len != -1) {
      memset(tbuffer, '\b', dedicated_last_string_len);
      tbuffer[dedicated_last_string_len] = '\0';
      PrintDedicatedMessage(tbuffer);
    }
    char levelname[100];
    snprintf(levelname, sizeof(levelname), "%s level %d", Current_mission.name, Current_mission.cur_level);
    if (lvl_percent_loaded < 1.0f) {
      snprintf(tbuffer1, sizeof(tbuffer1), TXT_DS_LEVELLOADSTATUS, levelname, lvl_percent_loaded * 100.0f);
      snprintf(tbuffer, sizeof(tbuffer), "%s%s", TXT_LOADINGLEVEL, tbuffer1);
      PrintDedicatedMessage(tbuffer);
      dedicated_last_string_len = strlen(tbuffer);
    } else {
      snprintf(tbuffer1, sizeof(tbuffer1), TXT_DS_LEVELLOADSTATUS, levelname, pag_percent_loaded * 100.0f);
      snprintf(tbuffer, sizeof(tbuffer), "%s%s", TXT_LL_PAGINGDATA, tbuffer1);
      PrintDedicatedMessage(tbuffer);
      dedicated_last_string_len = strlen(tbuffer);
    }
    return;
  }
  StartFrame(0, 0, Max_window_w, Max_window_h);
  // do background.
  if (!level_bmp_loaded) {
    int text_height;
    ASSERT(Current_level);
    rend_ClearScreen(GR_BLACK);
    grtext_SetFont(MENU_FONT);
    text_height = grfont_GetHeight(MENU_FONT);
    grtext_SetColor(GR_WHITE);
    grtext_CenteredPrintf(0, Max_window_h / 2, TXT_LOADINGLEVEL);
    // grtext_CenteredPrintf(0, (Max_window_h/2)+(text_height*2), Current_level->name);
  } else {
#ifdef STEALTH // DAJ
    rend_ClearScreen(GR_BLACK);
#else
    DrawLargeBitmap(&level_bmp, 0, 0, 1.0f);
#endif
    // do relevent text.
    str[0] = 0;
    if (chunk) {
      if (strncmp(CHUNK_TERRAIN, chunk, strlen(CHUNK_TERRAIN)) == 0)
        strcpy(str, TXT_LL_TERRAIN);
      else if (strncmp(CHUNK_SCRIPT_CODE, chunk, strlen(CHUNK_SCRIPT_CODE)) == 0)
        strcpy(str, TXT_LL_SCRIPTLOADED);
      else if (strncmp(CHUNK_ROOMS, chunk, strlen(CHUNK_ROOMS)) == 0)
        strcpy(str, TXT_LL_ROOMSLOADED);
      else if (strncmp(CHUNK_OBJECTS, chunk, strlen(CHUNK_OBJECTS)) == 0)
        strcpy(str, TXT_LL_OBJECTSLOADED);
    }
    if (str[0]) {
      if (n_text_msgs == N_LOAD_MSGS) {
        for (i = 1; i < n_text_msgs; i++) {
          strcpy(text_msgs[i - 1], text_msgs[i]);
        }
      } else {
        n_text_msgs++;
      }
      strcpy(text_msgs[n_text_msgs - 1], str);
    }
    grtext_SetFont(BRIEFING_FONT);
    grtext_SetColor(GR_WHITE);
    grtext_SetAlpha(230);
    for (i = 0; i < n_text_msgs; i++) {
      grtext_Printf(14, 32 + (i * 15), text_msgs[i]);
    }
  }
  g3Point *pntlist[4], points[4];
  points[0].p3_sx = LOADBAR_X;
  points[0].p3_sy = LOADBAR_Y1;
  points[1].p3_sx = LOADBAR_X + LOADBAR_W;
  points[1].p3_sy = LOADBAR_Y1;
  points[2].p3_sx = LOADBAR_X + LOADBAR_W;
  points[2].p3_sy = LOADBAR_Y1 + LOADBAR_H;
  points[3].p3_sx = LOADBAR_X;
  points[3].p3_sy = LOADBAR_Y1 + LOADBAR_H;
  for (i = 0; i < 4; i++) {
    points[i].p3_z = 0;
    points[i].p3_flags = PF_PROJECTED;
    pntlist[i] = &points[i];
  }
  rend_SetZBufferState(0);
  rend_SetTextureType(TT_FLAT);
  rend_SetAlphaType(AT_CONSTANT);
  rend_SetLighting(LS_NONE);
  rend_SetAlphaValue(230);
  if (!level_bmp_loaded) {
    rend_SetFlatColor(GR_RGB(192, 192, 192));
    rend_DrawPolygon2D(0, pntlist, 4);
  }

  pntlist[1]->p3_sx = LOADBAR_X + ((float)LOADBAR_W * lvl_percent_loaded);
  pntlist[2]->p3_sx = LOADBAR_X + ((float)LOADBAR_W * lvl_percent_loaded);

  rend_SetFlatColor(GR_RGB(166, 7, 7));
  rend_DrawPolygon2D(0, pntlist, 4);

  grtext_SetFont(BRIEFING_FONT);
  grtext_SetColor(GR_WHITE);
  if (lvl_percent_loaded != 1.0) {
    strcpy(str, TXT_LOADINGLEVEL);
  } else {
    strcpy(str, TXT_DONE);
  }
  grtext_Printf(LOADBAR_X + (LOADBAR_W - grtext_GetLineWidth(str)) / 2,
                LOADBAR_Y1 + (LOADBAR_H - grtext_GetHeight(str)) / 2, str);
  points[0].p3_sx = LOADBAR_X;
  points[0].p3_sy = LOADBAR_Y2;
  points[1].p3_sx = LOADBAR_X + LOADBAR_W;
  points[1].p3_sy = LOADBAR_Y2;
  points[2].p3_sx = LOADBAR_X + LOADBAR_W;
  points[2].p3_sy = LOADBAR_Y2 + LOADBAR_H;
  points[3].p3_sx = LOADBAR_X;
  points[3].p3_sy = LOADBAR_Y2 + LOADBAR_H;
  for (i = 0; i < 4; i++) {
    points[i].p3_z = 0;
    points[i].p3_flags = PF_PROJECTED;
    pntlist[i] = &points[i];
  }
  rend_SetZBufferState(0);
  rend_SetTextureType(TT_FLAT);
  rend_SetAlphaType(AT_CONSTANT);
  rend_SetLighting(LS_NONE);
  rend_SetAlphaValue(230);
  if (!level_bmp_loaded) {
    rend_SetFlatColor(GR_RGB(192, 192, 192));
    rend_DrawPolygon2D(0, pntlist, 4);
  }

  pntlist[1]->p3_sx = LOADBAR_X + ((float)LOADBAR_W * pag_percent_loaded);
  pntlist[2]->p3_sx = LOADBAR_X + ((float)LOADBAR_W * pag_percent_loaded);

  rend_SetFlatColor(GR_RGB(166, 7, 7));
  rend_DrawPolygon2D(0, pntlist, 4);

  grtext_SetFont(BRIEFING_FONT);
  grtext_SetColor(GR_WHITE);
  if (pag_percent_loaded == 1.0) {
    strcpy(str, TXT_DONE);
  } else {
    strcpy(str, TXT_LL_PAGINGDATA);
  }

  if (pag_percent_loaded > 0.0)
    grtext_Printf(LOADBAR_X + (LOADBAR_W - grtext_GetLineWidth(str)) / 2,
                  LOADBAR_Y2 + (LOADBAR_H - grtext_GetHeight(str)) / 2, str);

  // Display data errors
  extern int Data_error_count;
  if (Data_error_count) {
    char buf[1024];
    snprintf(buf, sizeof(buf), "This mission has %d data errors", Data_error_count);
    int y = 200 + 40;
    int x = 320 - (grtext_GetLineWidth(buf) / 2);
    grtext_Printf(x, y, buf);
  }

  if (step == LOAD_PROGRESS_PREPARE) {
    grtext_SetFont(BIG_BRIEFING_FONT);
    grtext_SetColor(GR_WHITE);

    int preparey = 200;
    int preparex = 320 - (grtext_GetLineWidth(TXT_PREPARE_FOR_DESCENT) / 2);
    if (preparex < 0)
      preparex = 0;
    grtext_Printf(preparex, preparey, TXT_PREPARE_FOR_DESCENT);
  }
  // Display level name if still loading
  if ((pag_percent_loaded > 0.0) && step != LOAD_PROGRESS_PREPARE) {
    char str[255];

    snprintf(str, sizeof(str), "\"%s\"", Level_info.name);
    grtext_SetFont(BIG_BRIEFING_FONT);
    grtext_SetColor(GR_WHITE);

    int preparey = 200;
    int preparex = 320 - (grtext_GetLineWidth(str) / 2);
    if (preparex < 0)
      preparex = 0;
    grtext_Printf(preparex, preparey, str);
  }
  grtext_Flush();
  EndFrame();
  rend_Flip();
}
/*	this functions performs the end mission code
 */
void DoEndMission() {
  if (Game_mode & GM_MULTI) // If multiplayer, just loop
  {
    if (Dedicated_server)
      PrintDedicatedMessage(TXT_DS_MISSIONDONE);
    SetCurrentLevel(1);
    return;
  }
}
// Shows some text on a background, useful for telling the player what is going on
// ie "Loading level...", "Receiving data...", etc
void ShowProgressScreen(const char *str, const char *str2, bool flip) {
  if (Dedicated_server) {
    PrintDedicatedMessage("%s\n", str);
    if (str2)
      PrintDedicatedMessage("%s\n", str2);
    return;
  }
  StartFrame(0, 0, Max_window_w, Max_window_h);
  rend_ClearScreen(GR_BLACK);
  grtext_SetFont(MENU_FONT);
  int text_height = grfont_GetHeight(MENU_FONT);
  grtext_SetColor(GR_WHITE);
  grtext_CenteredPrintf(0, Max_window_h / 2, str);
  if (str2)
    grtext_CenteredPrintf(0, (Max_window_h / 2) + (text_height * 2), str2);
  grtext_Flush();
  EndFrame();
  if (flip)
    rend_Flip();
}
/*	does a mission briefing, returns if mission was canceled, a false, or 0 value.
        first displays mission goals and some warnings or advice.
        may allow for selection of player ships
*/
bool DoMissionBriefing(int level) {
  tLevelNode *lvl = Current_level;
  bool ret = true;
  int num_ships = 0;
  for (int i = 0; i < MAX_SHIPS; i++) {
    if (Ships[i].used && PlayerIsShipAllowed(Player_num, i))
      num_ships++;
  }
  if (lvl->briefname[0] || num_ships > 1)
    ret = !TelComShow(TS_MISSION, false, true);
  return ret;
}
extern bool FirstGame;
bool Skip_next_movie = false;
//	---------------------------------------------------------------------------
//	 play movie
void DoMissionMovie(const char *movie) {
  char temppath[_MAX_PATH];
  if (PROGRAM(windowed)) {
    mprintf(0, "Skipping movie...can't do in windowed mode!\n");
    return;
  }
  // Don't play this movie the first time through. This is a horrible hack.
  if (Skip_next_movie) {
    Skip_next_movie = false;
    return;
  }
#ifdef D3_FAST
  return;
#endif
  if (movie && *movie) {
    char mpath[_MAX_PATH];
    ddio_MakePath(mpath, LocalD3Dir, "movies", movie, NULL);
    PlayMovie(mpath);
  }
  // PlayMovie(movie);
}
///////////////////////////////////////////////////////////////////////////////
//	Script Management for Missions and Levels
///////////////////////////////////////////////////////////////////////////////
//	Initializes a mission's default script
bool InitMissionScript() {
  // need to do this so when UI runs, it has a background.
  //	SetUICallback(DEFAULT_UICALLBACK);
  //	if there is no default script, we will load a null script, which means that whatever object
  //	uses scripts, will not do anything.
  //@@	fp = cfopen(DEFAULT_SCROBJ_NAME, "rb");
  //@@	if (!fp) {
  //@@		DoMessageBox("Error", "Unable to find mission script.", MSGBOX_OK, UICOL_WINDOW_TITLE,
  // UICOL_TEXT_NORMAL);
  //@@		mprintf(0, "Unable to open default script. Loading null script...\n");
  //@@		return false;
  //@@	}
  //@@	else {
  //@@		Current_mission.d3xmod = D3XLoadProgram(fp);
  //@@		if (!Current_mission.d3xmod) {
  //@@			DoMessageBox("Error", "Unable to find mission script.", MSGBOX_OK, UICOL_WINDOW_TITLE,
  // UICOL_TEXT_NORMAL);
  //@@			mprintf(0, "Unable to open default script. Loading null script...\n");
  //@@			return false;
  //@@		}
  //@@		cfclose(fp);
  //@@	}
  return true;
}
extern bool IsRestoredGame;
void InitLevelScript() {
  if (Current_level->filename) {
    char filename[_MAX_PATH], ext[_MAX_EXT];
    ddio_SplitPath(Current_level->filename, NULL, filename, ext);
#if defined(WIN32)
    strcat(filename, ".dll");
#else
#if defined(MACOSX)
    strcat(filename, ".dylib");
#else
    strcat(filename, ".so");
#endif
#endif
    Osiris_LoadLevelModule(filename);
  }
  //@$-D3XExecScript(Current_level->d3xthread, Current_mission.cur_level, REF_LEVELTYPE, EVT_LEVELSTART, 0, 0);
  tOSIRISEventInfo ei;
  // This is a hack... we don't want the level start script to be called when restoring a save game
  if (!IsRestoredGame)
    Osiris_CallLevelEvent(EVT_LEVELSTART, &ei);
  AssignScriptsForLevel(); // initialize all scripts for level.
}
void FreeLevelScript() {
  Osiris_UnloadLevelModule();
  if (Current_level) {
    //	free level's script and thread
    //@$-D3XExecScript(Current_level->d3xthread, Current_mission.cur_level, REF_LEVELTYPE, EVT_LEVELEND, 0, 0);
    tOSIRISEventInfo ei;
    Osiris_CallLevelEvent(EVT_LEVELEND, &ei);
  }
}
//	return information about a mission
bool GetMissionInfo(const char *msnfile, tMissionInfo *msn) {
  CFILE *fp;
  bool indesc = false; // are we in a multi-line block
  //	open mission file
  if (IS_MN3_FILE(msnfile)) {
    return mn3_GetInfo(msnfile, msn);
  }
  fp = cfopen(msnfile, "rt");
  if (!fp) {
    mprintf(0, "Failed to open mission file %s in GetMissionInfo.\n", msnfile);
    return false;
  }
  msn->multi = true;
  msn->single = true;
  msn->training = false;
  msn->author[0] = 0;
  msn->desc[0] = 0;
  while (!cfeof(fp)) {
    char srcline[128]; // One line of mission source
    char command[32];  // Command read from line.
    char operand[96];  // operand read from line
    char *keyword;     // parsed keyword
    int readcount;     // read-in count
    readcount = cf_ReadString(srcline, sizeof(srcline), fp);
    if (readcount) {
      //	we have a line of source.  parse out primary keyword
      //	then parse out remainder.
      keyword = strtok(srcline, " \t");
      CleanupStr(command, srcline, sizeof(command));
      CleanupStr(operand, srcline + strlen(command) + 1, sizeof(operand));
      if (strlen(command) && indesc)
        indesc = false;
      if (!stricmp(command, "NAME")) {
        strncpy(msn->name, operand, MSN_NAMELEN - 1);
      } else if (!stricmp(command, "MULTI")) {
        if (stricmp("no", operand) == 0)
          msn->multi = false;
      } else if (!stricmp(command, "SINGLE")) {
        if (stricmp("no", operand) == 0)
          msn->single = false;
      } else if (!stricmp(command, "TRAINER")) {
        msn->training = true;
      } else if (!stricmp(command, "AUTHOR")) {
        strncpy(msn->author, operand, MSN_NAMELEN - 1);
      } else if (!stricmp(command, "DESCRIPTION") || indesc) {
        //	multi-line descriptions require the strcat.  the initial
        //	strings should be empty for this to work.
        strcat(msn->desc, operand);
        if (indesc)
          strcat(msn->desc, "\n");
        indesc = true; // this is a multiline command
      } else if (!stricmp(command, "NUMLEVELS")) {
        //	get number of levels
        int value = atoi(operand);
        msn->n_levels = value;
      } else if (!stricmp(command, "LEVEL")) {
        break;
      } else if (!stricmp(command, "KEYWORDS")) {
        // Read in all the keywords
        strncpy(msn->keywords, operand, MAX_KEYWORDLEN);
      }
    }
  }
  cfclose(fp);
  return true;
}
//	---------------------------------------------------------------------------
const char *GetMissionName(const char *mission) {
  tMissionInfo msninfo;
  static char msnname[MSN_NAMELEN];
  msnname[0] = 0;
  if (GetMissionInfo(mission, &msninfo)) {
    strcpy(msnname, msninfo.name);
  } else {
    mprintf(0, "MISSION:GetMissionName failed from call to GetMissionInfo\n");
  }
  return msnname;
}
bool IsMissionMultiPlayable(const char *mission) {
  tMissionInfo msninfo;
  if (GetMissionInfo(mission, &msninfo)) {
    return msninfo.multi;
  }
  return false;
}
bool IsMissionSinglePlayable(const char *mission) {
  tMissionInfo msninfo;
  if (GetMissionInfo(mission, &msninfo)) {
    return msninfo.single;
  }
  return false;
}
int Mission_voice_hog_handle = 0;
//	MN3 based mission functions.
// loads the msn file from the mn3 file specified, specifies the hog and table file.
bool mn3_Open(const char *mn3file) {
  char pathname[_MAX_PATH];
  char filename[PSFILENAME_LEN + 1];
  char ext[PSFILENAME_LEN];
  int mn3_handle;
  // concatanate the mn3 extension if it isn't there.
  char tempMn3File[_MAX_PATH];
  if (!IS_MN3_FILE(mn3file)) {
    strncpy(tempMn3File, mn3file, sizeof(tempMn3File) - 1);
    tempMn3File[sizeof(tempMn3File) - 1] = 0;
    strcat(tempMn3File, ".mn3");
    mn3file = tempMn3File;
  }

  ddio_MakePath(pathname, D3MissionsDir, mn3file, NULL);
  // open MN3 HOG.
  mn3_handle = cf_OpenLibrary(mn3file);
  if (mn3_handle == 0) {
    return false;
  } else {
    Osiris_ExtractScriptsFromHog(mn3_handle, true);
  }
  // do table file stuff.
  ddio_SplitPath(mn3file, NULL, filename, ext);

  char voice_hog[_MAX_PATH*2];
  if ((stricmp(filename, "d3") == 0) || (stricmp(filename, "training") == 0)) {
    // Open audio hog file
    ddio_MakePath(voice_hog, D3MissionsDir, "d3voice1.hog", nullptr); // Audio for levels 1-4
    Mission_voice_hog_handle = cf_OpenLibrary(voice_hog);
  } else if (stricmp(filename, "d3_2") == 0) {
    // Open audio hog file
    ddio_MakePath(voice_hog, D3MissionsDir, "d3voice2.hog", nullptr); // Audio for levels 5-17
    Mission_voice_hog_handle = cf_OpenLibrary(voice_hog);
  }
  strcat(filename, ".gam");
  mng_SetAddonTable(filename);
  Current_mission.mn3_handle = mn3_handle;
  return true;
}

// returns mission information given the mn3 file.
bool mn3_GetInfo(const char *mn3file, tMissionInfo *msn) {
  int handle;
  bool retval;
  char pathname[_MAX_PATH];
  char filename[PSFILENAME_LEN + 1];

  ddio_MakePath(pathname, D3MissionsDir, mn3file, nullptr);
  handle = cf_OpenLibrary(pathname);
  if (handle == 0) {
    mprintf(0, "MISSION: MN3 failed to open.\n");
    return false;
  }
  MN3_TO_MSN_NAME(mn3file, filename);
  retval = GetMissionInfo(filename, msn);
  cf_CloseLibrary(handle);
  return retval;
}
// closes the current mn3 file
void mn3_Close() {
  if (Current_mission.mn3_handle) {
    Osiris_ClearExtractedScripts(true);
    cf_CloseLibrary(Current_mission.mn3_handle);
  }
  if (Mission_voice_hog_handle) {
    cf_CloseLibrary(Mission_voice_hog_handle);
    Mission_voice_hog_handle = 0;
  }
  Current_mission.mn3_handle = 0;
}
#define KEYWORD_LEN 16
#define NUM_KEYWORDS 16
#define GOALSTEXT "GOALS"
#define GOALSTEXTLEN strlen(GOALSTEXT)
#define MODMINGOALS "MINGOALS"
#define MODMINGOALSLEN strlen(MODMINGOALS)
// Returns the max number of teams this mission can support for this mod, or
//-1 if this level shouldn't be played with this mission
// Return values:
// -1	Bad match -- this level and this mod shouldn't be played together!
// MAX_NET_PLAYERS	-- This is playable with any number of teams the mod wants
int MissionGetKeywords(const char *mission, char *keywords) {
  ASSERT(mission);
  ASSERT(keywords);

  char msn_keywords[NUM_KEYWORDS][KEYWORD_LEN];
  char mod_keywords[NUM_KEYWORDS][KEYWORD_LEN];
  int i;
  char *parse_keys = mem_strdup(keywords);
  char seps[] = ",";
  int teams = MAX_NET_PLAYERS;
  int goals = 0;
  int goalsneeded = 0;
  int mod_key_count = 0;
  int msn_key_count = 0;
  bool goal_per_team = false;
  tMissionInfo msn_info;

  memset(msn_keywords, 0, sizeof(msn_keywords));
  memset(mod_keywords, 0, sizeof(mod_keywords));
  mprintf(0, "MissionGetKeywords(%s,%s)\n", mission, keywords);
  if (!GetMissionInfo(mission, &msn_info)) {
    return -1;
  }

  if (!*parse_keys) {
    return MAX_NET_PLAYERS;
  }
  // Break up the mod keywords into an array
  char *tokp = strtok(parse_keys, seps);
  if (tokp) {
    do {
      strcpy(mod_keywords[mod_key_count], tokp);
      mod_key_count++;
      tokp = strtok(NULL, seps);
    } while ((tokp) && (mod_key_count < NUM_KEYWORDS));
  }
  // Break up the msn keywords into an array
  tokp = strtok(msn_info.keywords, seps);
  if (tokp) {
    do {
      strcpy(msn_keywords[msn_key_count], tokp);
      msn_key_count++;
      tokp = strtok(NULL, seps);
    } while ((tokp) && (msn_key_count < NUM_KEYWORDS));
  }

  for (i = 0; i < NUM_KEYWORDS; i++) {
    if (msn_keywords[i][0] == 0) {
      continue;
    }
    if (strnicmp(GOALSTEXT, msn_keywords[i], GOALSTEXTLEN) == 0) {
      // Get the number of goals this game has
      goals = atoi(msn_keywords[i] + GOALSTEXTLEN);
    }
  }
  mem_free(parse_keys);

  // Loop through looking for matches
  for (i = 0; i < NUM_KEYWORDS; i++) {
    if (mod_keywords[i][0] == 0) {
      continue;
    }
    if (strnicmp(mod_keywords[i], MODMINGOALS, MODMINGOALSLEN) == 0) {
      goalsneeded = atoi(mod_keywords[i] + MODMINGOALSLEN);
    } else if (stricmp("GOALPERTEAM", mod_keywords[i]) == 0) {
      goal_per_team = true;
    } else {
      bool found_keyword = false;
      // Loop through looking for matches
      for (int a = 0; a < NUM_KEYWORDS; a++) {
        if (msn_keywords[a][0] == 0) {
          continue;
        }
        if (stricmp(msn_keywords[a], mod_keywords[i]) == 0) {
          // Woohoo! it's found
          found_keyword = true;
          break;
        }
      }
      // We never found one we needed, so return -1;
      if (!found_keyword) {
        mprintf(0, "%s keyword needed in %s not found!\n", mod_keywords[i], mission);
        return -1;
      }
    }
  }
  if (goal_per_team) {
    teams = goals;
  }
  if (teams < goalsneeded) {
    mprintf(0, "Not enough goals in this level!\n");
    teams = -1;
  }
  if (goals < goalsneeded) {
    mprintf(0, "Not enough goals in this level!\n");
    teams = -1;
  }
  return teams;
}
//////////////////////////////////////////////////////////////////////////////
#ifdef EDITOR
//	Used by editor->game to load all necessary elements for level playing for systems
//	not initialized in editor, but only in game.
extern char Editor_quickplay_levelname[_MAX_PATH];
void QuickStartMission() {
  //	create the level script code here, if we really need to.
  ResetGamemode();
  //	this initializes a mini one level mission with no frills.
  Current_mission.cur_level = 1;
  Current_mission.num_levels = 1;
  Current_mission.levels = (tLevelNode *)mem_malloc(sizeof(tLevelNode));
  memset(Current_mission.levels, 0, sizeof(tLevelNode));
  Current_level = Current_mission.levels;
  if (Editor_quickplay_levelname[0] != '\0')
    Current_level->filename = mem_strdup(Editor_quickplay_levelname);
  else
    Current_level->filename = NULL;
  //	proceed with initialization.
  InitMissionScript();
  SetGameState(GAMESTATE_LVLSTART);
}
// Used by game->editor to free up all extra game mission elements not needed in editor.
void QuickEndMission() {
  //@@	FreeScriptsForLevel();
  //@@	D3XFreeProgram(Current_mission.d3xmod);
  //@@	Current_mission.d3xmod = NULL;
  //	free up mini mission.
  //@@	Current_level = NULL;
  //@@	mem_free(Current_mission.levels);
  //@@	Current_mission.levels = NULL;
  ResetMission();
}
#endif
