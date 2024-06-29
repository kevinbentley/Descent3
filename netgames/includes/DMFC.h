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

 * $Logfile: /DescentIII/Main/DMFC.h $
 * $Revision: 1.3 $
 * $Date: 2004/02/09 04:14:49 $
 * $Author: kevinb $
 *
 * Major header file for DMFC
 *
 * $Log: DMFC.h,v $
 * Revision 1.3  2004/02/09 04:14:49  kevinb
 * Added newlines to all headers to reduce number of warnings printed
 *
 * Made some small changes to get everything compiling.
 *
 * All Ready to merge the 1.5 tree.
 *
 * Revision 1.2  2000/09/22 18:50:30  icculus
 * Removing some x86 ASM for non-x86 builds.
 *
 * Revision 1.1.1.1  2000/04/18 00:00:30  icculus
 * initial checkin
 *
 *
 * 125   10/21/99 3:32p Matt
 * Mac merge
 *
 * 124   8/11/99 1:21p Jeff
 * exported needed functions for camera windows
 *
 * 123   7/16/99 2:43p Jeff
 * changed CreateMenuItemWArgs function
 *
 * 122   7/11/99 3:32p Jeff
 * exported game arguments, made command line option to specify
 * autoexec.dmfc
 *
 * 121   7/07/99 12:16p Jeff
 * all mangles symbol names fixed.  Finished making interface functions.
 *
 * 120   6/12/99 10:59p Jeff
 * fixed messed up #ifdef for __LINUX__
 *
 * 119   6/10/99 6:31p Jeff
 * fixed mprintf define
 *
 * 118   5/12/99 11:04p Jeff
 * dmfc and multiplayer games now have endian friendly packets (*whew*)
 *
 * 117   5/10/99 10:21p Ardussi
 * changes to compile on Mac
 *
 * 116   4/27/99 12:36p Jeff
 * fixed flags
 *
 * 115   4/24/99 11:13p Jeff
 * added flags for creating a newui window for a title bar
 *
 * 114   4/20/99 7:27p Jeff
 * fixed new MAX_PLAYERS
 *
 * 113   4/19/99 6:02p Jeff
 * fixed macros (mprintf and Debug_break) for Linux
 *
 * 112   4/19/99 5:46p Jeff
 * added int3/assert macros for Linux
 *
 * 111   4/03/99 9:26p Jeff
 * changed dialogs that weren't using UID_OK and UID_CANCEL to use and
 * handle them properly
 *
 * 110   3/17/99 12:23p Jeff
 * converted DMFC to be COM interface
 *
 * 109   3/11/99 6:30p Jeff
 * numerous fixes to demo system in multiplayer games (when
 * recording/playback a demo in a multiplayer game)
 *
 * 108   3/05/99 12:02p Kevin
 * New color scheme for new art
 *
 * 107   2/28/99 11:05p Jeff
 * fixed ASSERT define in Release builds
 *
 * 106   2/28/99 3:06a Jeff
 * adjust ok/cancel y offset for new ui artwork
 *
 * 105   2/11/99 12:54a Jeff
 * changed names of exported variables
 *
 * 103   2/07/99 1:19a Jeff
 * added new multiplayer game events EVT_GAMEOBJKILLED and
 * EVT_GAMEOBJDESTROYED
 *
 * 102   2/03/99 4:09p Jeff
 * moved function pointers to seperate file. created autoexec.dmfc
 *
 * 101   1/31/99 7:25p Matt
 * Renamed a bunch of functions to have HUD capitalized
 *
 * 100   1/24/99 8:31p Jeff
 * updated stat manager to print team scores
 *
 * 98    1/15/99 3:50a Jeff
 * new events required new handlers
 *
 * 96    1/07/99 5:01p Jeff
 * added Int3's and updated all net games to use stats manager...correctly
 * too
 *
 * 95    1/06/99 7:02p Jeff
 * added a multiplayer event for game controls
 *
 * 94    1/04/99 12:21p Jeff
 * added support for hosts.allow/deny and updates stats manager a little
 *
 * 93    12/13/98 5:32p Jeff
 * fixed ugly crash due to freeing memory allocated in another heap
 *
 * 92    12/08/98 4:47p Jeff
 * umm, various changes, fixed pilot pics so that they work for everyone
 * now
 *
 * 91    12/08/98 3:29p Jeff
 * updated the team control dialog so the server can determine if they
 * want to make the clients wait
 *
 * 90    12/08/98 12:17p Jeff
 * various changes that include an improved Team Control dialog (doesn't
 * switch teams until exit..) and spew/respawn players that change teams
 *
 * 89    12/04/98 7:04p Jeff
 * almost finished up dmfc stat manager
 *
 * 88    12/03/98 7:05p Jeff
 * updated new stats
 *
 * 87    12/01/98 6:56p Jeff
 * put in quick and dirty implementation of pilot pics for testing
 *
 * 86    11/20/98 5:52p Jeff
 * updated hyper anarchy and hoard a little
 *
 * 85    11/19/98 5:56p Jeff
 * added slider exported and improved Hoard
 *
 * 84    11/18/98 5:48p Jeff
 * added function/struct to get information from the DLL before it loads
 *
 * 83    11/17/98 6:29p Jeff
 * mod can specify whether or not to display the team setup dialog on team
 * game start.  Added a menu item to display team setup dialog in mid-game
 *
 * 82    11/16/98 5:35p Jeff
 * removed log functions, added support for changing team names, fixed ctf
 * to work better with different team names
 *
 * 81    11/13/98 6:36p Jeff
 * created dmfc_dll (a DLL version of DMFC) and converted current mods to
 * use it
 *
 * 80    11/12/98 12:16p Jeff
 * more changes to handle (ignore) dedicated server
 *
 * 79    11/11/98 7:18p Jeff
 * changes made so that a dedicated server's team is always -1 (team game
 * or not)
 *
 * 78    11/09/98 11:54a Jeff
 * Added Player_colors
 *
 * 77    11/02/98 4:38p Jeff
 * added ability to sort and display by efficiency
 *
 * 76    11/01/98 1:59a Jeff
 * made a $help inputcommand for help in a dedicated server environment
 *
 * 75    10/30/98 12:46p Jeff
 * cut down a couple bytes on memory usage
 *
 * 74    10/29/98 7:01p Jeff
 * creation of team placement dialog.  Moved TranslateEvent into DMFC
 *
 * 73    10/24/98 2:18p Jeff
 *
 * 72    10/23/98 11:22a Jeff
 * changes to handle mixcase, and display the client netgame info
 * correctly
 *
 * 71    10/20/98 4:35p Jeff
 * added a flag for menu to add a <None> to MIT_PLIST...
 *
 * 70    10/20/98 12:17p Jeff
 *
 * 69    10/19/98 7:18p Matt
 * Added system to support different types of damage to the player and
 * have these different types make different sounds.
 *
 * 68    10/18/98 7:59p Jeff
 * functions added to dmfc for client->server objnum matching.  Banning
 * now uses tracker id when available.
 *
 * 67    10/17/98 7:30p Jeff
 * network_address compares don't compare port on somethings
 *
 * 66    10/15/98 6:18p Jeff
 * created the is player banned event, removed prejoin event
 *
 * 65    10/15/98 1:34p Jeff
 * added scrollable onscreen menu.  Remove ban in dmfc.  prejoin event
 *
 * 64    10/14/98 11:26p Jeff
 * added scrollable menus
 *
 * 63    10/13/98 12:03p Kevin
 * Changed use of preprocessors for debug, etc.
 *
 * 62    10/13/98 2:15a Jeff
 * created new event for when a player leaves a multiplayer game.  Fixed
 * some 'english' bugs in the network games.
 *
 * 61    10/11/98 2:57a Jeff
 * added new multiplayer event EVT_GAME_INTERVAL, which is to be called on
 * interval, and EVT_HUD_INTERVAL is only to be called when the hud is to
 * be rendered
 *
 * 60    10/08/98 3:37p Jeff
 * general improvements (Netgame info things, save to registry).  Changes
 * so it would send packets on NETSEQ_OBJECTS
 *
 * 59    10/05/98 2:49p Jeff
 *
 * 58    10/01/98 7:02p Jeff
 * implemented colored HUD callsigns
 *
 * 57    10/01/98 11:30a Jeff
 * made the observer mode events into just a client event
 *
 * 56    9/30/98 4:21p Jeff
 * team changing is handled correctly
 *
 * 55    9/30/98 3:50p Jeff
 * general improvements (many)
 *
 * 54    9/29/98 3:04p Jeff
 * added time in game and start_time support
 *
 * 53    9/28/98 5:05p Jeff
 * made the statisitical death messages an option in the menu
 *
 * 52    9/25/98 7:25p Jeff
 *
 * 51    9/25/98 4:50p Jeff
 *
 * 50    9/24/98 6:54p Jeff
 * added DisconnectMe() and made use of it when you get kicked/banned
 *
 * 49    9/24/98 5:52p Jeff
 * starting adding statistical death messages, checked in for testing
 *
 * 48    9/23/98 4:17p Jeff
 * basic changes/improvements, started changing death messages
 *
 * 47    9/21/98 7:11p Jeff
 * made InputCommand interface API and moved existing input commands to
 * the interface.  Changed mprintf/ASSERT so they are valid in DMFC
 *
 * $NoKeywords: $
 */

#ifndef __DMFC_H__
#define __DMFC_H__

#include <stdio.h>
#include <stdarg.h>
#include <time.h>
#include "gamedll_header.h"
#include "DMFCKeyCodes.h"

#if ((defined __LINUX__) && (!defined __i386__))
#include <signal.h>
#endif

#ifndef RELEASE

#ifdef WIN32
#ifdef DEBUG_BREAK
#undef DEBUG_BREAK
#endif
#define DEBUG_BREAK()                                                                                                  \
  do {                                                                                                                 \
    if (DLLDebugBreak_callback_stop)                                                                                   \
      DLLDebugBreak_callback_stop();                                                                                   \
    debug_break();                                                                                                     \
    if (DebugBreak_callback_resume)                                                                                    \
      DebugBreak_callback_resume();                                                                                    \
  } while (0)

#define DLLASSERT(x)                                                                                                   \
  do {                                                                                                                 \
    DLLassert(x, #x, __FILE__, __LINE__);                                                                              \
  } while (0)
#define DLLmprintf(...) DLLDebug_ConsolePrintf(__VA_ARGS__)
#ifdef ASSERT
#undef ASSERT
#endif
#define ASSERT(x)                                                                                                      \
  do {                                                                                                                 \
    DLLassert(x, #x, __FILE__, __LINE__);                                                                              \
  } while (0)

#ifdef Int3
#undef Int3
#endif
#define Int3()                                                                                                         \
  do {                                                                                                                 \
    mprintf(0, "Int3 at %s line %d.\n", __FILE__, __LINE__);                                                         \
    if (DLLDebugBreak_callback_stop)                                                                                   \
      DLLDebugBreak_callback_stop();                                                                                   \
    debug_break();                                                                                                     \
    if (DLLDebugBreak_callback_resume)                                                                                 \
      DLLDebugBreak_callback_resume();                                                                                 \
  } while (0)
#elif defined(__LINUX__)
// For some reason Linux doesn't like the \ continuation character, so I have to uglify this
#define DLLmprintf(...) DLLDebug_ConsolePrintf(__VA_ARGS__)
#ifdef DEBUG_BREAK
#undef DEBUG_BREAK
#endif
#if (defined __i386__) || defined(__x86_64__)
#define DEBUG_BREAK()                                                                                                  \
  do {                                                                                                                 \
    if (DLLDebugBreak_callback_stop)                                                                                   \
      DLLDebugBreak_callback_stop();                                                                                   \
    __asm__ __volatile__("int $3");                                                                                    \
    if (DLLDebugBreak_callback_resume)                                                                                 \
      DLLDebugBreak_callback_resume();                                                                                 \
  } while (0)
#else
#define DEBUG_BREAK()                                                                                                  \
  do {                                                                                                                 \
    if (DLLDebugBreak_callback_stop)                                                                                   \
      DLLDebugBreak_callback_stop();                                                                                   \
    raise(SIGTRAP);                                                                                                    \
    if (DLLDebugBreak_callback_resume)                                                                                 \
      DLLDebugBreak_callback_resume();                                                                                 \
  } while (0)
#endif

#ifdef ASSERT
#undef ASSERT
#endif
#define ASSERT(x)                                                                                                      \
  do {                                                                                                                 \
    DLLassert(x, #x, __FILE__, __LINE__);                                                                              \
  } while (0)
#define DLLASSERT(x) ASSERT(x)
#ifdef Int3
#undef Int3
#endif
#define Int3()                                                                                                         \
  do {                                                                                                                 \
    mprintf(0, "Int3 at %s line %d.\n", __FILE__, __LINE__);                                                         \
    DEBUG_BREAK();                                                                                                     \
  } while (0)
#define HEAPCHECK()
#else
#ifdef DEBUG_BREAK
#undef DEBUG_BREAK
#define DEBUG_BREAK()
#endif
#define DLLASSERT(x)
#define DLLmprintf(...)
#ifdef Int3
#undef Int3
#define Int3()
#endif
#define Int3()
#ifdef ASSERT
#undef ASSERT
#define ASSERT(x)
#endif
#endif // OS check

#else // Release build
#ifdef DEBUG_BREAK
#undef DEBUG_BREAK
#define DEBUG_BREAK()
#endif
#define DLLASSERT(x)
#define DLLmprintf(...)
#ifdef Int3
#undef Int3
#define Int3()
#endif
#define Int3()
#ifdef ASSERT
#undef ASSERT
#define ASSERT(x)
#endif
#endif

#ifdef mprintf // undefine mprintf and redirect it to use DLLmprintf
#undef mprintf
#endif
#define mprintf DLLmprintf

#define DLLMAX_PLAYERS MAX_PLAYERS
#define DLLMAX_TEAMS 4
#define RED_TEAM 0
#define BLUE_TEAM 1
#define GREEN_TEAM 2
#define YELLOW_TEAM 3

#define GR_GREY GR_RGB(128, 128, 128)
#define GR_GRAY GR_GREY

#define SP_ALL -1
#define SP_SERVER -2
#define SPH_DMFCFUNC 0
#define SPH_FUNC 1

#define HI_TEXT 0
#define HI_BITMAP 1

#define MAX_TEAMNAME_LEN 16

// Defines for the window camera views
#define CV_NONE 0      // View not active
#define CV_REARVIEW 1  // Rear view
#define CV_MARKER1 2   // Marker view
#define CV_MARKER2 3   // Marker view
#define CV_MARKER3 4   // Marker view
#define CV_MARKER4 5   // Marker view
#define CV_MARKER5 6   // Marker view
#define CV_MARKER6 7   // Marker view
#define CV_MARKER7 8   // Last marker view
#define CV_MARKER8 9   // Last marker view
#define CV_GUIDEBOT 10 // Guide-Bot
#define NUM_CAMERA_VIEWS 3

/// special characters in the fonts
#define CHAR_LEFT_ARROW 24
#define CHAR_UP_ARROW 25
#define CHAR_RIGHT_ARROW 26
#define CHAR_DOWN_ARROW 27
#define CHAR_CHECKBOX_OFF 28
#define CHAR_CHECKBOX_ON 29
#define CHAR_RADIO_OFF 30
#define CHAR_RADIO_ON 31

// The following defines are RGB definitions for colors that should be used throughout the UI for text
#define UICOL_HOTSPOT_LO                                                                                               \
  GR_RGB(85, 234, 3) // Color for a hotspot when it isn't in focus//GR_RGB(50,50,255)		// Color for a hotspot
                     // when it isn't in focus
#define UICOL_HOTSPOT_HI GR_RGB(207, 248, 105)   // Color for a hotspot when it is in focus
#define UICOL_TEXT_NORMAL GR_RGB(206, 254, 241)  // Color for text that is used for labels
#define UICOL_WINDOW_TITLE GR_RGB(207, 248, 105) // Color for window title text
#define UICOL_TEXT_AUX GR_RGB(200, 200, 200)     // Color for auxillary text (text that isn't a label)
#define UICOL_LISTBOX_LO GR_RGB(85, 234, 3)      // Color for listbox text that isn't in focus
#define UICOL_LISTBOX_HI GR_RGB(207, 248, 105)   // Color for listbox text that is in focus
#define UICOL_BUTTON_LO GR_RGB(85, 234, 3)       // Color for text on a button that isn't in focus
#define UICOL_BUTTON_HI GR_RGB(207, 248, 105)    // Color for text on a button that is in focus
#define UIALPHA_HOTSPOT_LO 192                   // Alpha value for hotspots not in focus
#define UIALPHA_HOTSPOT_HI 255                   // Alpha value for hotspots in focus
#define OKCANCEL_YOFFSET 50                      // subtract this from the height of the window

// additional flags for creating a newui window
#define NUWF_TITLENONE 0x00000000    // don't display a title bar
#define NUWF_TITLESMALL 0x00100000   // display a small title bar
#define NUWF_TITLEMED 0x00200000     // display a medium size title bar
#define NUWF_TITLELARGE 0x00300000   // display a large title bar
#define NUWF_TITLEBARMASK 0x00300000 // mask to use with flags to get title bar flags

// predefined return values for DLLDoUI/DLLPollUI...exit the dialog immediatly!!
#define NEWUIRES_FORCEQUIT -2
#define UID_OK 0xEE
#define UID_CANCEL 0xEF

#define MAX_MENUNAME 32
#define MF_SERVER 0x0001
#define MF_CLIENT 0x0002
#define MF_ALL 0x0003

#define REGT_STRING 0
#define REGT_DWORD 1
#define CFG_NOERROR 0        // There was no error
#define CFG_ALREADYOPEN 1    // The registry/cfg is already open
#define CFG_OUTOFMEMORY 2    // Out of memory
#define CFG_NOCFGFILE 3      // You didn't give a config file name
#define CFG_NOTOPEN 4        // You haven't opened the config file yet
#define CFG_KEYNOTFOUND 5    // The key you're looking up hasn't been created or isn't in the registry
#define CFG_RECORDNOTFOUND 6 // The record you're lookup up isn't in the active key
#define CFG_CANTCREATE 7     // There was an error trying to create a record

#define MIT_NORMAL 0    // Allowed to have submenus
#define MIT_PLIST 1     // A Player List
#define MIT_STATE 2     // Radio Button like submenu list
#define MIT_STATEITEM 3 // Given to the submenu list items of the above
#define MIT_CUSTOM                                                                                                     \
  4 // use this along with filled in tCustomMenu* (as the only parm in the variable parms section
    // of MenuItem constructor to create a user defined menu list

#define MAX_STRING_LEN 32 // Maximum string length for a menu title
#define MAX_DMFC_TIMERS 16
#define MAX_DEATH_MSGS 32

#define MAX_CALLSIGN_SIZE 25
#define MAX_PLAYER_RECORDS 64
#define DSTAT_LEVEL 0
#define DSTAT_OVERALL 1

#define MAX_DBNAME_SIZE 32
#define MAX_DBLABEL_SIZE 128

struct tCustomMenu {
  int (*GetListCount)(void);   // this function should return the number of items in the list
  char *(*GetItem)(int index); // this function should return a string of the item at the given index, NULL on error
};

struct tPInfoStat {
  int slot;   // player record slot
  int kills;  // number of times you killed this player
  int deaths; // number of times this player killed you
};

enum slot_state { STATE_EMPTY, STATE_INGAME, STATE_DISCONNECTED };

struct t_dstat {
  int kills[2], deaths[2], suicides[2];
};

class PInfo;

struct player_record {
  slot_state state;                 // state of this slot
  char callsign[MAX_CALLSIGN_SIZE]; // Player's callsign
  char *tracker_id;                 // Player's master tracker ID, NULL if there isn't one
  network_address net_addr;         // Player's address
  int pnum;                         // Player's pnum
  union {
    float disconnect_time; // Time player disconnected
    float start_time;      // Time the player entered the game
  };
  float total_time_in_game; // Total time the player has been in the game
  t_dstat dstats;           // DMFC's stats
  void *user_info;          // Multiplayer Mod user defined struct pointer
  int user_info_size;       // Size of user_info;

  int8_t team;   // The player's team (for when they reconnect)
  PInfo *pinfo; // Pointer to player info (who killed whom)
};

#define MIF_INCLUDENONE                                                                                                \
  0x01 // for MIT_PSTATE, this will place a <None> at the top, it will send a -1 to the function, if selected
// #define MIF_IGNORESERVER	0x02	//for MIT_PSTATE, this will keep the server out of the list
// #define MIF_IGNOREME		0x04	//for MIT_PSTATE, this will keep your pnum out of the list

#define MAX_COLUMN_TITLE_SIZE 15

enum tColumnType{
  DSCOL_KILLS_LEVEL,
  DSCOL_KILLS_OVERALL,
  DSCOL_KILLS_BOTH,
  DSCOL_DEATHS_LEVEL,
  DSCOL_DEATHS_OVERALL,
  DSCOL_DEATHS_BOTH,
  DSCOL_SUICIDES_LEVEL,
  DSCOL_SUICIDES_OVERALL,
  DSCOL_SUICIDES_BOTH,
  DSCOL_PILOT_NAME,
  DSCOL_PILOT_TEAM,
  DSCOL_PING,
  DSCOL_CUSTOM,
  DSCOL_BLANK,
  DSCOL_BMP
};

enum tColorType { DSCOLOR_NORMAL, DSCOLOR_TEAM, DSCOLOR_SHIPCOLOR, DSCOLOR_CUSTOM };

struct tDmfcStatsColumnInfo {
  // what type of information should be displayed in this column, use custom if you want
  // the callback to fill in your own data
  tColumnType type;
  // what type of color to use
  tColorType color_type;
  // title for column
  char title[MAX_COLUMN_TITLE_SIZE];
  // width of the column (note: columns will not be rendered if the total width of the
  // columns exceeds the width of the display)
  int width;
  // color of the text for this column (if color type is custom)
  ddgr_color color;
};

//=====================================================================
// tDmfcStatsInit flags
#define DSIF_SEPERATE_BY_TEAM                                                                                          \
  0x00000001 // this tells the stats manager to seperate the players by
             // team (useful only in a team game).  By default it will
             // list all the players in a straight list
#define DSIF_SHOW_PIC                                                                                                  \
  0x00000002 // The pilot's picture (if available else logo if available) should
             // be shown in the detailed section
#define DSIF_ONLY_X_PLAYERS_SHOWN                                                                                      \
  0x000004 // If set, than the MaxNumberDisplayed member of tDmfcStatsInit
           // must also be valid (throughout the lifetime of the stats
           // being displayed).  The stat manager will only display
           // (*MaxNumberDisplayed) stats (checked each frame).
#define DSIF_SHOW_OBSERVERICON                                                                                         \
  0x00000008                           // if this flag is given, the observer mode icon will be
                                       // displayed as the first item in the column
#define DSIF_NOLASTKILLER 0x00000010   // don't display the "Last Killer"
#define DSIF_NOLASTVICTIM 0x00000020   // don't display the "Last Victim"
#define DSIF_NODETAILEDINFO 0x00000040 // don't display the detailed stats
#define DSIF_SHOWPLAYERVIEW                                                                                            \
  0x00000080 // display the current view of the selected player (only available if DSIF_NODETAILEDINFO is also set)

//=====================================================================
struct tDmfcStatsInit {
  // see the DSIF_* for the list of available flags and descriptions
  int flags;
  // points to an array of player record numbers, sorted to however you want them sorted.  Each
  // frame this array will be used when displaying the stats.
  int *SortedPlayerRecords;
  // the number of columns you want printed in the player list column for each player
  int cColumnCountPlayerList;
  // the number of columns you want printed in the detailed player info
  int cColumnCountDetailed;
  // Informtaion for the player list columns (array of tDmfcStatsColumnInfo structs)
  tDmfcStatsColumnInfo *PlayerListColumns;
  // Information for the detailed columns (array of tDmfcStatsColumnInfo structs)
  tDmfcStatsColumnInfo *DetailedColumns;
  // Callback function when the stats manager needs to get information when displaying a playerlist column
  //	precord_num:	contains the player record number of the player it needs information about
  //	column_num:		which column (index into the PlayerListColumns array) it is working on
  //	buffer:			buffer to fill in for your data
  //	buffer_size:	number of bytes you can use for your data (IT MUST BE NULL TERMINATED STRING)
  void (*clbPlayerColumn)(int precord_num, int column_num, char *buffer, int buffer_size);
  // Callback function when the stats manager needs to get information when displaying a detailed column
  //	precord_num:	contains the player record number of the player it needs information about
  //	column_num:		which column (index into the DetailedColumns array) it is working on
  //	buffer:			buffer to fill in for your data
  //	buffer_size:	number of bytes you can use for your data (IT MUST BE NULL TERMINATED STRING)
  void (*clbDetailedColumn)(int precord_num, int column_num, char *buffer, int buffer_size);
  // Callback function when the stats manager needs to draw the custom bitmap on the playerlist column
  //	precord_num:	contains the player record number of the player it displaying
  //	column_num:		which column (index into the PlayerListColumns array) it is working on
  //	x,y,w,h:		the (x,y) position of the upper left corner of the area, and the allowed width/height
  // handle the drawing in this function
  void (*clbPlayerColumnBMP)(int precord_num, int column_num, int x, int y, int w, int h, uint8_t alpha_to_use);
  // Callback function when the stats manager needs to draw the custom bitmap on the detailed column
  //	precord_num:	contains the player record number of the player it displaying
  //	column_num:		which column (index into the DetailedColumns array) it is working on
  //	x,y,w,h:		the (x,y) position of the upper left corner of the area, and the allowed width/height
  // handle the drawing in this function
  void (*clbDetailedColumnBMP)(int precord_num, int column_num, int x, int y, int w, int h, uint8_t alpha_to_use);
  // Callback function when the stats manager needs to display team info for a particular team
  //	team:			contains the team it's displaying about (0 = red, ... 3 = yellow)
  //	buffer:			buffer to fill in for your data
  //	buffer_size:	number of bytes you can use for your data (IT MUST BE NULL TERMINATED STRING)
  void (*clTeamLine)(int team, char *buffer, int buffer_size);
  // Points to a buffer that contains the name of the multiplayer game (NULL TERMINATED STRING)
  char *GameName;
  // if the DSIF_ONLY_X_PLAYERS_SHOWN flag is set, than the stat manager checks this value (dereferenced) every frame
  // and will only show this many players
  int *MaxNumberDisplayed;
};

#endif
