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

 * $Logfile: /DescentIII/main/Mission.h $
 * $Revision: 41 $
 * $Date: 4/23/99 3:33p $
 * $Author: Kevin $
 *
 * Mission level sequencing and management.
 *
 * $Log: /DescentIII/main/Mission.h $
 *
 * 41    4/23/99 3:33p Kevin
 * mission file/multiplayer mod keyword system
 *
 * 40    4/22/99 6:21p Kevin
 * mission keywords
 *
 * 39    4/08/99 3:13p Matt
 * Finished cleaning up level sequencing code.  Got rid of all the "level
 * minus one" stuff.
 *
 * 38    4/03/99 5:23p Matt
 * Removed name, author, & description from the mission level structure.
 *
 * 37    4/03/99 5:05p Samir
 * added ENDMISSION keyword to end a mission after a certain level.
 *
 * 36    3/24/99 1:23p Kevin
 * Support for level specific progress screens.
 *
 * 35    2/10/99 4:56p Kevin
 * Better progress indicator & prepare for Descent message
 *
 * 34    1/20/99 4:20p Samir
 * finished secret level implementation.
 *
 * 33    1/19/99 1:15p Samir
 * add on missions.
 *
 * 32    1/13/99 12:43p Jason
 * fixed flickering exit menu screen
 *
 * 31    1/08/99 2:55p Samir
 * Ripped out OSIRIS1.
 *
 * 30    1/05/99 10:59a Samir
 * readded level objective flags.
 *
 * 29    1/04/99 5:44p Samir
 * added game state flags.
 *
 * 28    12/16/98 3:24p Samir
 * new way to get info on a mission (used to determine training mission
 * too.)
 *
 * 27    12/16/98 1:57p Samir
 * Replaced CleanupString2 with CleanupStr
 *
 * 26    12/03/98 12:51p Samir
 * music score specified per level.
 *
 * 25    10/18/98 2:58p Jason
 * fixes for beta4
 *
 * 24    10/13/98 3:48p Samir
 * added error checking if script failed to load (default).
 *
 * 23    10/08/98 7:29p Samir
 * revamped sequencing.
 *
 * 22    10/02/98 5:46p Samir
 * took out mission file objective text and replaced with level goals.
 *
 * 21    8/24/98 5:04p Kevin
 * Made msn files have the option to not be playable in multiplayer
 *
 * 20    8/18/98 1:10a Samir
 * some reorg of scripting and intrasave mission managment.
 *
 * 19    7/31/98 5:19p Samir
 * mission filenames are dynamically allocated now to allow for pathnames
 * (since we'd have too many 256 char arrays per level.
 *
 * 18    6/18/98 4:49p Kevin
 * Updated multiplayer menus
 *
 * 17    5/21/98 2:32p Samir
 * added full support for intra-mission level branching.
 *
 * 16    4/20/98 11:30a Jason
 * Added ShowProgressScreen function
 *
 * 15    4/18/98 7:17a Samir
 * Added level objective descriptions to mission file.
 *
 * 14    4/14/98 7:50p Matt
 * Added system to keep info for each level
 *
 * 13    4/02/98 11:11a Samir
 * Error checking for level load/misison init fail.
 *
 * 12    3/13/98 12:09p Samir
 * Added InitMissionScript function header.
 *
 * 11    2/08/98 5:01p Samir
 * New game sequencing changes.
 *
 * 10    11/12/97 2:47p Samir
 * Added mission briefing name.
 *
 * 9     10/03/97 11:58a Samir
 * Added mission name
 *
 * 8     10/02/97 12:36p Samir
 * Redid game sequencing flow.
 *
 * 7     9/30/97 5:33p Samir
 * Added GameSequencer.
 *
 * 6     9/24/97 2:58p Samir
 * Moved some script defines from mission.h to ObjScript.h
 *
 * 5     9/10/97 1:59p Samir
 * Added D3XProgram var to level structure.
 *
 * 4     8/15/97 6:33p Samir
 * Changes reflecting enhanced editor scripting.
 *
 * 3     8/12/97 3:25p Samir
 * Added QuickStart functions.
 *
 * 2     8/05/97 9:59a Samir
 * Scripting stuff.
 *
 * 4     6/05/97 12:21p Samir
 * Added more mission commands.
 *
 * 3     5/16/97 3:11p Samir
 * Added a mission name and mission initializer.
 *
 * 2     5/15/97 2:09p Samir
 * Added a bunch of sequencing from level to level, loading mission.
 *
 * 1     4/29/97 11:57a Samir
 * Initial revision
 *
 * $NoKeywords: $
 */

#ifndef MISSION_H
#define MISSION_H

#include "pstypes.h"
#include "descent.h"

//	*** CONSTANTS ***
#define LOAD_PROGRESS_START 1
#define LOAD_PROGRESS_LOADING_LEVEL 2
#define LOAD_PROGRESS_PAGING_DATA 3
#define LOAD_PROGRESS_PREPARE 4
#define LOAD_PROGRESS_DONE 200

// Load level progress worker
void LoadLevelProgress(int step, float percent, const char *chunk = NULL);

//	array constants
static constexpr int MSN_FILENAMELEN = PSPATHNAME_LEN, MSN_URLLEN = 256;

#define MAX_KEYWORDLEN 300

//	increase this value if you are going to add more levels to a mission than the max.
static constexpr int MAX_LEVELS_PER_MISSION = 30;

//	mission flags. TODO: move into an enum?
static constexpr unsigned LVLFLAG_STARTMOVIE = 1, LVLFLAG_ENDMOVIE = 2, LVLFLAG_BRIEFING = 4, LVLFLAG_SHIPSELECT = 8,
                          LVLFLAG_SPAWNSECRET = 16, LVLFLAG_SPECIALHOG = 32, LVLFLAG_BRANCH = 64, LVLFLAG_UNUSED = 128,
                          LVLFLAG_SCORE = 256, LVLFLAG_FINAL = 512;

static constexpr int LVLOBJ_NUM = 4;
static constexpr uint16_t LVLOBJF_SECONDARY1 = 1, LVLOBJF_SECONDARY2 = 2, LVLOBJF_SECONDARY3 = 4, LVLOBJF_SECONDARY4 = 8;

extern bool Skip_next_movie;

// Struct for info about the current level
struct level_info {
  char name[100];
  char designer[100];
  char copyright[100];
  char notes[1000];
};

// Info about the current level
extern level_info Level_info;

//	level information
struct tLevelNode {
  //	level flags
  unsigned flags;           // level flags
  unsigned objective_flags; // level objective flags

  //	movies
  char *moviename;
  char *endmovie;

  //	level filename
  char *filename;  // mine filename.
  char *briefname; // briefing filename
  char *hog;       // hog file name for this level
  char *score;     // music score of level
  char *progress;  // File name containing the progress background screen

  //	level branching
  uint8_t lvlbranch0, lvlbranch1; // FORK or BRANCH command
  uint8_t secretlvl;              // SECRET command
  uint8_t pad;
};

// predefine mission state flags
#define MSN_STATE_SECRET_LEVEL 0x80000000

struct tMission {
  int mn3_handle; // if this mission was loaded from an MN3, this is the handle.

  unsigned game_state_flags;  // game state information stored here (manipulated by scripting)
  char *filename;             // filename of mission.
  char name[MSN_NAMELEN];     // name of mission
  char author[MSN_NAMELEN];   // author of mission.
  char desc[MSN_NAMELEN * 4]; // description of mission
  char *hog;                  // default hog filename
  char email[MSN_URLLEN];     // email and web location
  char web[MSN_URLLEN];
  bool multiplayable;    // this level is multiplayer playable
  bool singleplayable;   // this level is playable as a single player game
  bool training_mission; // is this mission a training mission?

  //	listing of levels.
  int num_levels;     // number of levels
  int cur_level;      // current level playing.
  tLevelNode *levels; // array of levels
};

// structyre used to get information about a mission
struct tMissionInfo {
  char name[MSN_NAMELEN];
  char author[MSN_NAMELEN];
  char desc[MSN_NAMELEN * 4];
  bool multi;
  bool single;
  bool training;
  int n_levels;
  char keywords[MAX_KEYWORDLEN]; // Keywords for mods, so you can see if this mission supports a given mod
};

//	Scripting information

//	the current mission being played.
extern tMission Current_mission;
extern tLevelNode *Current_level;

extern char D3MissionsDir[];

// Get the name field out of the mission file
const char *GetMissionName(const char *mission);

//	initializes mission system.
void InitMission();

//	reset all states for a mission
void ResetMission();

//	loads and verifies a mission as the current mission, returns if valid of not.
bool LoadMission(const char *msn);

//	initializes a level's script.
void InitLevelScript();

//	frees a level's script
void FreeLevelScript();

//	does a mission briefing, returns if mission was canceled, a false, or 0 value.
bool DoMissionBriefing(int level);

//	does the end mission stuff
void DoEndMission();

//	does the mission movie stuff
void DoMissionMovie(const char *movie);

//	loads a level and sets it as current level in mission
bool LoadMissionLevel(int level);

//	initializes the mission script
bool InitMissionScript();

//	Objectives
void CompletedPrimaryObjective();

// Shows text on a background
void ShowProgressScreen(const char *str, const char *str2 = NULL, bool flip = true);

// See if a mission file is multiplayer playable.
bool IsMissionMultiPlayable(const char *mission);

//	return information about a mission
bool GetMissionInfo(const char *msnfile, tMissionInfo *msn);

// Returns the max number of teams this mission can support for this mod, or
//-1 if this level shouldn't be played with this mission
// Return values:
// -1	Bad match -- this level and this mod shouldn't be played together!
// MAX_NET_PLAYERS	-- This is playable with any number of teams the mod wants
int MissionGetKeywords(const char *mission, char *keywords);

//  MN3 based mission functions.
/// Loads the msn file from the mn3 file specified, specifies the hog and table file.
extern bool mn3_Open(const char *mn3file);
/// Closes the current mn3 file.
extern void mn3_Close();

#ifdef EDITOR
//	Used by editor to load all necessary elements for level playing for systems
//	not initialized in editor, but only in game.
void QuickStartMission();

// Used by game->editor to free up all extra game mission elements not needed in editor.
void QuickEndMission();

#endif

#endif
