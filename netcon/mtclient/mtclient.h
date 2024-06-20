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

#ifndef _MTCLIENT_HEADER
#define _MTCLIENT_HEADER
/*
 * $Logfile: /DescentIII/Main/mtclient/mtclient.h $
 * $Revision: 1.1.1.1 $
 * $Date: 2003-08-26 03:58:40 $
 * $Author: kevinb $
 *
 * Mastertracker client DLL
 *
 * $Log: not supported by cvs2svn $
 *
 * 17    7/30/99 1:20p Kevin
 * Fixed problems with sorted game list
 *
 * 16    7/06/99 5:52p Kevin
 * PXO & multiplayer fixes for the patch
 *
 * 15    6/23/99 3:36p Samir
 * took out #define  uint8_t
 *
 * 14    3/02/99 5:50p Kevin
 * Ouch. Duplicate structures existed and were conflicting.
 *
 * 13    2/19/99 5:21p Kevin
 * Fixed some connection DLLs and a Direct Sound bug with threads.
 *
 * 12    11/03/98 9:29a Kevin
 * Added pxo motd
 *
 * 11    9/16/98 8:06p Jason
 * got mastertracker working with the dedicated server
 *
 * 10    8/19/98 11:50a Kevin
 * Got DirectPlay IPX working, and localized connection DLLs
 *
 * 9     8/07/98 12:39p Jeff
 * added "allowed ships" to multiplayer options
 *
 * 8     7/21/98 1:49p Kevin
 * IPX support and peer-peer option for multi
 *
 * 7     7/20/98 2:34p Kevin
 * Re-wrote the DLL wrapper, to allow for better expandability
 *
 * 5     6/24/98 6:40p Kevin
 * Added help to main dll menu
 *
 * 4     6/24/98 3:24p Kevin
 * Updated PXO screens with chat, etc.
 *
 * 3     6/18/98 4:49p Kevin
 * Updated multiplayer menus
 *
 * 2     6/01/98 10:10a Kevin
 * Added DLL connection interface and auto update DLL
 *
 * 1     5/18/98 12:47p Kevin
 *
 * $NoKeywords: $
 */

#include "ui.h"

// Chat tracker
#define CHATTRACKERNAME "tracker.pxo.nottheeye.com"
#define CHATPORT 7170

#define TRACKER_MENU_W 256
#define TRACKER_MENU_H 256
#define TRACKER_MENU_X (320 - (TRACKER_MENU_W / 2))
#define TRACKER_MENU_Y (240 - (TRACKER_MENU_H / 2))

#define MAXTEXTITEMS 100
#define MAXNEWWINDOWS 5
#define MAXNEWGAMEWINDOWS 5
#define MAXUIBUTTONS 20
#define MAXUITEXTS 20
#define MAXEDITS 20
#define MAXLISTS 20

#include "con_dll.h"

#define MAX_GAME_NAME_LEN 100
#define MAX_MISSION_NAME_LEN 100
#define MAX_MISSION_FILE_LEN 40
#define MAX_SCRIPT_LEN 40
#define MAX_FORMAT_STRING 300

typedef struct s_pxo_game_list {
  /*
  char name[MAX_GAME_NAME_LEN];
  network_address address;
  char mission_name[MAX_MISSION_NAME_LEN];
  char mission_file[MAX_MISSION_FILE_LEN];
  char script[MAX_SCRIPT_LEN];
  int16_t level;
  int16_t curr_players;
  int16_t max_players;
  float ping;
  uint32_t flags;
  char format_string[MAX_FORMAT_STRING];

  bool dedicated;
  */
  bool used;
  uint32_t handle;
  void *ti;
  int lb_no;
} pxo_game_list;

int LoginMasterTracker();
int MainMultiplayerMenu();
int SearchMasterTrackerGameMenu();
int StartMultiplayerGameMenu();
void MultiplayerOptionsMenu();
void DoMTFrame();
void DoMTGameOver();
int MTVersionCheck();
int JoinNewLobby(const char *lobby);
const char *SendWhisper(const char *name);
int JoinPrivateLobby();
int FindPilot();
int GetPilotStats(const char *pilot);
void AutoLoginAndJoinGame();
int ShowMessageOfTheDay();
#endif
