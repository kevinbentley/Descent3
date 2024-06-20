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

* $Logfile: /DescentIII/Main/mtclient/mtclient.cpp $
* $Revision: 1.1.1.1 $
* $Date: 2003-08-26 03:58:40 $
* $Author: kevinb $
*
* Mastertracker Client DLL
*
* $Log: not supported by cvs2svn $
 *
 * 127   10/03/01 12:44a Kevin
 * Smaller version of pxo packets
 *
 * 126   3/26/00 10:30p Kevin
 * MOD Downloader for 1.4 patch.
 *
 * 125   3/20/00 12:29p Matt
 * Merge of Duane's post-1.3 changes.
 * Deleted Mac-only stricmp() function.
 *
 * 124   2/18/00 11:33p Kevin
 * Fixed crash when sorting ping list bug, and clear the game list when
 * joining a private lobby.
 *
 * 123   9/07/99 2:21p Kevin
 * more CR/LF issues for the mac
 *
 * 122   9/07/99 10:24a Kevin
 * Macintosh fixes!
 *
 * 121   9/02/99 3:16p Kevin
 * Macintosh byte ordering fixes
 *
 * 120   8/24/99 5:47p Kevin
 * Macintosh crap
 *
 * 119   8/24/99 10:39a Kevin
 * Hopefully fixed the PXO return to chat bug
 *
 * 118   8/17/99 3:35p Kevin
 * inverse sorts wouldn't show the last item! Doh!
 *
 * 117   8/17/99 1:52p Kevin
 * fixed potential crash bugs as well as formatting for "CS Team Anarchy"
 *
 * 116   8/12/99 10:15a Kevin
 * debugging stuff
 *
 * 115   8/10/99 12:53p Kevin
 * fixed bug with return to chat & sorted gamelist
 *
 * 114   7/30/99 1:20p Kevin
 * Fixed problems with sorted game list
 *
 * 113   7/26/99 11:45a Kevin
 * possible return to chat crash fix
 *
 * 112   7/21/99 9:11a Kevin
 * bandwidth reduction act #1
 *
 * 111   7/12/99 4:15p Kevin
 * Changed the way we determine if we should report stats or not in PXO
 *
 * 110   7/07/99 3:38p Kevin
 * Sorting in PXO gamelist!
 *
 * 109   7/06/99 5:52p Kevin
 * PXO & multiplayer fixes for the patch
 *
 * 108   5/23/99 3:04a Jason
 * fixed bug with player rankings not being updated correctly
 *
 * 107   5/23/99 2:38a Kevin
 * fixed text overlapping thingy
 *
 * 106   5/20/99 9:17p Kevin
 * removed invisible hotspot
 *
 * 105   5/17/99 5:19p Samir
 * added ability for edit box to autoselect when hitting the max number of
 * characters typable.
 *
 * 104   5/08/99 11:32a Kevin
 * increased the gamelist update interval from pxo
 *
 * 103   5/05/99 5:23p Kevin
 * fixed some bugs on the gamelist
 *
 * 102   5/05/99 11:04a Kevin
 * added defer call to game over (previously it was only happening while
 * writing stats
 *
 * 101   5/04/99 10:16p Kevin
 * Fixed problem with 'set default screen'
 *
 * 100   5/04/99 5:39p Kevin
 * connection dll & pxo game tracking improvements (added server type to
 * list)
 *
 * 99    4/28/99 6:39p Kevin
 * Build 182 fixes
 *
 * 98    4/27/99 1:54p Kevin
 * Added pilot name to stats dialog
 *
 * 97    4/27/99 10:23a Kevin
 * nifty titles for dialogs
 *
 * 96    4/25/99 5:02p Kevin
 * Bunches of multiplayer UI improvements
 *
 * 95    4/24/99 11:59p Kevin
 * game info dialog stuff
 *
 * 94    4/23/99 11:49p Kevin
 *
 * 93    4/22/99 3:43p Kevin
 * Training missions show controls on screen
 *
 * 92    4/20/99 8:57p Jeff
 * compile for Linux
 *
 * 91    4/19/99 7:56p Kevin
 * ifdef'd out some win32 specific stuff
 *
 * 90    4/18/99 1:18p Kevin
 * Demo2 build changes
 *
 * 89    4/17/99 3:44p Kevin
 * Demo2 changes & fixes
 *
 * 88    4/16/99 6:00p Kevin
 * Bunches of Demo stuff
 *
 * 87    4/14/99 1:37a Jeff
 * fixed case mismatched #includes
 *
 * 86    4/02/99 12:19p Kevin
 * Fixed chat server failed to connect
 *
 * 85    3/25/99 3:26p Kevin
 * Made PXO games be based on your chat channel
 *
 * 84    3/17/99 4:08p Kevin
 * Changed the way games appear and timeout in the game list.
 *
 * 83    3/05/99 11:35a Kevin
 * new screens
 *
 * 82    3/04/99 12:07p Kevin
 * Fixed stupid bug if you cancel out of connecting.
 *
 * 81    3/02/99 5:50p Kevin
 * Ouch. Duplicate structures existed and were conflicting.
 *
 * 80    2/19/99 5:21p Kevin
 * Fixed some connection DLLs and a Direct Sound bug with threads.
 *
 * 79    2/15/99 7:47p Jeff
 * new pilot file class and read/write system checked in...should be more
 * robust than old
 *
 * 78    2/03/99 4:20p Kevin
 * Got multiplayer working with .mn3 files, and setup autodownloading
 *
 * 77    2/02/99 7:06p Jason
 * added ranking system
 *
 * 76    1/23/99 3:20p Kevin
 * Made gamelist boxes not sort
 *
 * 75    1/11/99 12:29p Jeff
 * changes made not to call the module library directly
 *
 * 74    1/07/99 11:51a Kevin
 * Added support for joining servers on alternate ports and hosting behind
 * a proxy/firewall
 *
 * 73    1/04/99 5:43p Kevin
 * new command line args
 *
 * 72    12/30/98 5:24p Kevin
 * Added +name to specify a default pilot (for gamespy) fixed a gamespy
 * bug, and improved the pxo dll game list screen
 *
 * 71    12/30/98 12:16p Kevin
 * Auto Mission Download system
 *
 * 70    12/23/98 6:38p Kevin
 * All UDP data (except gamespy) now uses one (registered) port number
 *
 * 69    12/14/98 10:53a Jason
 * added bright player ships option
 *
 * 68    12/04/98 4:37p Kevin
 * Fixed selection being reset in game lists...
 *
 * 67    12/01/98 12:47p Jason
 * got rid of NF_DROPMISORDERED and added NF_USE_SMOOTHING
 *
 * 66    11/18/98 3:26p Kevin
 * Put multiplayer options into con_dll.h
 *
 * 65    11/03/98 9:27a Kevin
 * Added PXO message of the day
 *
 * 64    10/30/98 11:25a Kevin
 * Message of the day for PXO
 *
 * 63    10/23/98 10:12a Kevin
 * fixed bug when you hit cancel in the login screen
 *
 * 62    10/22/98 10:14a Kevin
 * Made Stats dialog bigger
 *
 * 61    10/20/98 5:46p Kevin
 * Gunboy and other fixes
 *
 * 60    10/20/98 2:07p Kevin
 * changed tab order of login dialog, and changed strings
 *
 * 59    10/19/98 11:07p Kevin
 * fixed bug
 *
 * 58    10/19/98 2:48p Kevin
 * Added accurate weapon thingy for Chris
 *
 * 57    10/19/98 11:24a Kevin
 * Fixed problem with help
 *
 * 56    10/17/98 2:32p Kevin
 * FIxed problem with banned users getting stuck on the ban message
 * screen.
 *
 * 55    10/17/98 12:46p Kevin
 * Beta 4 fixes
 *
 * 54    10/15/98 3:29p Kevin
 * Fixed dlls to not require runtime debug libraries in release builds
 *
 * 53    10/15/98 12:08p Kevin
 * Changed game list to line up differently
 *
 * 52    10/13/98 3:42p Kevin
 * bug fixes
 *
 * 51    10/12/98 8:39p Kevin
 * removed mprintf's and fixed some smallish bugs
 *
 * 50    10/12/98 11:02a Kevin
 * Changed directory of mtav file
 *
 * 49    10/09/98 2:56p Kevin
 * Changed IP addresses for PXO demo
 *
 * 48    10/08/98 3:37p Jeff
 * removed time_left from Netgame
 *
 * 47    10/05/98 11:00a Kevin
 * Fixed bug with uninitialized variable
 *
 * 46    10/01/98 11:37a Kevin
 * UI fixes and stuff
 *
 * 45    9/30/98 12:33p Kevin
 * Added web launching support
 *
 * 44    9/29/98 2:23p Kevin
 * More UI tweaks
 *
 * 43    9/28/98 4:55p Kevin
 *
 * 42    9/28/98 4:21p Kevin
 * Redesigned game list menus
 *
 * 41    9/28/98 11:10a Kevin
 * fuxed returning onf uninitialized variable
 *
 * 40    9/28/98 9:53a Kevin
 * Fixing misc UI problems, and fixed some bugs that VC 6 found
 *
 * 39    9/25/98 11:07a Kevin
 * fixed columns to line up and cleaned up some PXO bugs
 *
 * 38    9/24/98 12:50p Kevin
 * Added UI for rotational velocity and drop out of order packets in net
 * games
 *
 * 37    9/23/98 6:33p Kevin
 * Fixed load settings
 *
 * 36    9/23/98 2:55p Kevin
 * Saved multi config and changed UI to conform
 *
 * 35    9/22/98 3:55p Kevin
 * Removed obsolete function
 *
 * 34    9/22/98 2:29p Kevin
 * moved ships allowed code out of dll and into main app. Also added
 * powerup exclusions
 *
 * 33    9/21/98 11:19a Kevin
 * check protocol before entering multiplayer screens
 *
 * 32    9/16/98 8:06p Jason
 * got mastertracker working with the dedicated server
 *
 * 31    9/14/98 12:34p Kevin
 * Fixed problems with using strtok and grtext functions.
 *
 * 30    9/09/98 12:41p Kevin
 * Fixed up some UI issues
 *
 * 29    9/04/98 1:51p Kevin
 * implemented asyncronous gethostbyname
 *
 * 28    9/02/98 6:54p Kevin
 * Fixed general directplay support up, and got modem-modem working
 *
 * 27    8/31/98 10:14a Kevin
 * Misc. multi-UI fixes
 *
 * 26    8/27/98 5:03p Kevin
 * Prettied up multiplayer screens and fixed some bugs.
 *
 * 25    8/26/98 3:28p Samir
 * put focus thing back in
 *
 * 24    8/25/98 6:33p Kevin
 * PXO screens
 *
 * 23    8/24/98 5:04p Kevin
 * Made msn files have the option to not be playable in multiplayer
 *
 * 22    8/24/98 10:42a Kevin
 * Updated DLL for directplay and PXO background
 *
 * 21    8/19/98 11:50a Kevin
 * Got DirectPlay IPX working, and localized connection DLLs
 *
 * 20    8/17/98 2:26p Kevin
 * fixed auto update dll directory
 *
 * 19    8/17/98 11:00a Kevin
 * Moved DLLs into subdirectories
 *
 * 18    8/07/98 12:39p Jeff
 * added "allowed ships" to multiplayer options
 *
 * 17    7/27/98 5:31p Kevin
 * Sound/Bitmap exchange system
 *
 * 16    7/22/98 4:34p Kevin
 * fixed bug in MT gamelist with >10 games
 *
 * 15    7/21/98 1:49p Kevin
 * IPX support and peer-peer option for multi
 *
 * 14    7/20/98 2:34p Kevin
 * Re-wrote the DLL wrapper, to allow for better expandability
 *
 * 11    6/30/98 3:20p Kevin
 * fixed ping time
 *
 * 10    6/25/98 10:03a Kevin
 * Minor chat fixes in PXO
 *
 * 9     6/24/98 6:40p Kevin
 * Added help to main dll menu
 *
 * 8     6/24/98 3:24p Kevin
 * Updated PXO screens with chat, etc.
 *
 * 7     6/18/98 4:49p Kevin
 * Updated multiplayer menus
 *
 * 6     6/11/98 1:56p Jeff
 * looks for d3m files instead of dll
 *
 * 5     6/05/98 2:16p Jeff
 * Changes made so Dynamic loading of DLLs done through module library
 *
 * 4     6/05/98 12:40p Kevin
 *
 * 3     6/01/98 3:52p Kevin
 * changed listbox item to be white
 *
 * 2     6/01/98 10:10a Kevin
 * Added DLL connection interface and auto update DLL
 *
 * 1     5/18/98 12:47p Kevin
*
* $NoKeywords: $
*/

#include "ui.h"
#include "newui.h"
#include "grdefs.h"
#include "player.h"
#include "game.h"
#include "pilot.h"
#include "ddio_common.h"
#include "mt_net.h"
#include "mtgametrack.h"
#include "module.h"
#include "inetgetfile.h"
#include "chat_api.h"
#include "mtstrings.h"

#define TXT_DLL_SAVESETTINGS TXT(79)
#define TXT_DLL_LOADSETTINGS TXT(80)

#define TXT_GEN_MPLYROPTIONS TXT_PXO_MPLYROPTIONS
#define TXT_GEN_TIMELIMIT TXT_PXO_TIMELIMIT
#define TXT_GEN_KILLGOAL TXT_PXO_KILLGOAL
#define TXT_GEN_PPS TXT_PXO_PPS
#define TXT_GEN_RESPAWNRATE TXT_PXO_RESPAWNRATE
#define TXT_GEN_MAXPLAYERS TXT_PXO_MAXPLAYERS
#define TXT_GEN_PREVMENU TXT_PXO_PREVMENU
#define TXT_GEN_CANCEL TXT_PXO_CANCEL
#define TXT_GEN_CFGALLOWEDSHIP TXT_PXO_CFGALLOWEDSHIP
#define TXT_GEN_USEROTVEL TXT_PXO_USEROTVEL
#define TXT_GEN_USEROTVEL TXT_PXO_USEROTVEL
#define TXT_GEN_USESMOOTHING TXT_PXO_USESMOOTHING
#define TXT_GEN_CLIENTSERVER TXT_PXO_CLIENTSERVER
#define TXT_GEN_PEERPEER TXT_PXO_PEERPEER
#define TXT_GEN_ACC_WEAP_COLL TXT_PXO_ACC_WEAP_COLL
#define TXT_GEN_BRIGHT_PLAYERS TXT_PXO_BRIGHT_PLAYERS

#define MULTI_USE_ALL_OPTIONS 1

#include "mtclient.h"
#include "mtpilottrack.h"

#include "DLLUiItems.h"

char Ourlobby[50] = "";
bool Login_aborted = false;
bool Auto_start = false;
int Bypass_chat = 0;
int ChatStarted = 0;
extern int Motd_version;

d3_net_game_data_tiny DLLD3_tracker_info;

#define MTADDNEWURL TXT_PXO_REGURL

#define MAX_GAMELIST_ITEMS 300

pxo_game_list PXOGamelist[MAX_GAMELIST_ITEMS];
int NextGameItemNo = 0;
uint16_t DLLPXOPort = 0;

void AutoLoginAndStartGame();

int GetGameByHandle(uint32_t handle) {
  int j;
  for (j = 0; j < *DLLNum_network_games_known; j++) {
    if (DLLNetwork_games[j].handle == handle) {
      return j;
    }
  }
  return -1;
}

int GetPXOItemByHandle(uint32_t handle) {
  for (int i = 0; i < MAX_GAMELIST_ITEMS; i++) {
    if (PXOGamelist[i].used) {
      if (PXOGamelist[i].handle == handle) {
        return i;
      }
    }
  }
  return -1;
}

int GetGameByLBNo(int selno) {
  for (int i = 0; i < MAX_GAMELIST_ITEMS; i++) {
    if (PXOGamelist[i].used) {
      if (PXOGamelist[i].lb_no == selno) {
        return GetGameByHandle(PXOGamelist[i].handle);
      }
    }
  }
  return -1;
}

void FormatServerLine(char *fmt, int servernum, int pxonum) {
  int k = servernum;
  char server_mode[20];
  char server_type[200];

  if (DLLNetwork_games[k].flags & NF_PEER_PEER) {
    strcpy(server_mode, "PP");
  } else if (DLLNetwork_games[k].flags & NF_PERMISSABLE) {
    strcpy(server_mode, "PS");
  } else {
    strcpy(server_mode, "CS");
  }

  if (DLLNetwork_games[k].flags & NF_ALLOW_MLOOK) {
    strcat(server_mode, "-ML");
  }

  snprintf(server_type, sizeof(server_type), "%s %s", server_mode, DLLNetwork_games[k].scriptname);

  int game_type_pos = strlen(server_type);

#define SERVER_TYPE_MAX_LEN 100
  while (DLLgrtext_GetTextLineWidth(server_type) > SERVER_TYPE_MAX_LEN) {
    server_type[game_type_pos] = 0;
    game_type_pos--;
  }

  sprintf(fmt, "%.20s\t\x02\x02b%s\x02\x45%.15s\x02\x63%d\x02\x6d%d/%d\x02\x7e%.3f", DLLNetwork_games[k].name,
          server_type, DLLNetwork_games[k].mission_name, DLLNetwork_games[k].level_num,
          DLLNetwork_games[k].curr_num_players, DLLNetwork_games[k].max_num_players,
          DLLNetwork_games[k].server_response_time);
}

void UpdateGamelist(void *lb) {

  int i, j;

  // Look for items that we need to remove
  for (i = 0; i < MAX_GAMELIST_ITEMS; i++) {
    bool found = false;
    if (PXOGamelist[i].used) {
      for (j = 0; j < *DLLNum_network_games_known; j++) {
        if (DLLNetwork_games[j].handle == PXOGamelist[i].handle) {
          found = true;
        }
      }
      if (!found) {
        // Remove this item!
        /*
        int gameid = GetGameByHandle(PXOGamelist[i].handle);

        if(gameid!=-1)
        {
                DLLmprintf(0,"Removing %s\n",DLLNetwork_games[gameid].name);
        }
        */

        // Now we need to fix up the lb_no items because we removed this one!
        int k = 0;
        for (k = 0; k < MAX_GAMELIST_ITEMS; k++) {
          if (!PXOGamelist[k].used)
            continue;

          // This is yucky, but it accounts for the shifting up of the game items in the list
          if (PXOGamelist[i].lb_no < PXOGamelist[k].lb_no)
            PXOGamelist[k].lb_no--;
        }
        NextGameItemNo--;
        PXOGamelist[i].used = false;
        PXOGamelist[i].handle = -1;
        DLLListRemoveItem(lb, PXOGamelist[i].ti);
        DLLRemoveUITextItem(PXOGamelist[i].ti);
      }
    }
  }

  // Look for items to add
  for (i = 0; i < *DLLNum_network_games_known; i++) {
    bool found = false;
    for (j = 0; j < MAX_GAMELIST_ITEMS; j++) {
      if (DLLNetwork_games[i].handle == PXOGamelist[j].handle) {
        found = true;
      }
    }
    if (!found) {
      // Add this item!
      // Update PXOGamelist[i].ti
      for (j = 0; j < MAX_GAMELIST_ITEMS; j++) {
        if (!PXOGamelist[j].used) {
          // Aha! an empty slot
          break;
        }
      }

      int k = i;
      if (j < MAX_GAMELIST_ITEMS) {
        char fmtline[200];

        PXOGamelist[j].lb_no = NextGameItemNo;
        NextGameItemNo++;
        PXOGamelist[j].handle = DLLNetwork_games[k].handle;
        PXOGamelist[j].used = true;
        DLLmprintf(0, "Adding %s\n", DLLNetwork_games[k].name);

        // DLLmprintf(0,"Found game: %s\n",DLLNetwork_games[k].name);
        FormatServerLine(fmtline, k, j);

        if (DLLNetwork_games[k].dedicated_server) {
          PXOGamelist[j].ti = DLLCreateNewUITextItem(fmtline, UICOL_HOTSPOT_LO);
        } else {
          PXOGamelist[j].ti = DLLCreateNewUITextItem(fmtline, GR_LIGHTGRAY);
        }
        DLLListAddItem(lb, PXOGamelist[j].ti);
      } else {
        // DLLInt3();
        // Out of slots???
      }
    }
  }

  for (j = 0; j < MAX_GAMELIST_ITEMS; j++) {
    if (PXOGamelist[j].used && (PXOGamelist[j].handle != -1)) {
      int gameid = GetGameByHandle(PXOGamelist[j].handle);

      if (gameid != -1) {
        int k = gameid;
        // DLLmprintf(0,"Updating %s\n",DLLNetwork_games[gameid].name);
        char fmtline[200];
        FormatServerLine(fmtline, k, j);
        DLLSetUITextItemText(PXOGamelist[j].ti, fmtline,
                             DLLNetwork_games[k].dedicated_server ? UICOL_HOTSPOT_LO : GR_LIGHTGRAY);
      }
    }
  }
}

#ifdef MACINTOSH
#pragma export on
#endif

// These next two function prototypes MUST appear in the extern "C" block if called
// from a CPP file.
extern "C" {
DLLEXPORT void DLLFUNCCALL DLLMultiInit(int *api_func);
DLLEXPORT void DLLFUNCCALL DLLMultiCall(int eventnum);
DLLEXPORT void DLLFUNCCALL DLLMultiClose();
}

bool All_ok = true;
bool MT_Sock_inited = false;

// Initializes the game function pointers
void DLLFUNCCALL DLLMultiInit(int *api_func) {
  Use_netgame_flags = 1;
#ifdef MACINTOSH
  InitOTSockets();
#endif
#include "mdllinit.h"
  DLLPXOPort = (uint16_t)((size_t)API.vp[32] & 0xffff);
  DLLmprintf(0, "Inside DLLMultiInit...\n");
  *DLLUse_DirectPlay = false;
  Auto_start = false;
  DLLmprintf(0, "About to create string table...\n");
  DLLCreateStringTable("mtclient.str", &StringTable, &StringTableSize);
  DLLmprintf(0, "%d strings loaded from string table\n", StringTableSize);
  if (!StringTableSize) {
    All_ok = false;
    return;
  }

  memset(PXOGamelist, 0, sizeof(PXOGamelist));
}

// Called when the DLL is shutdown
void DLLFUNCCALL DLLMultiClose() {
  DLLmprintf(0, "Closing down PXO DLL\n");
  DLLDestroyStringTable(StringTable, StringTableSize);
  DLLnw_UnRegisterCallback(PXO_NETID_USER_TRACKER);
  DLLnw_UnRegisterCallback(PXO_NETID_GAME_TRACKER);
  if (MT_Sock_inited) {
    CloseMTSockets();
  }
#ifdef MACINTOSH
  ShutdownOTSockets();
#endif
}

// The main entry point where the game calls the dll
void DLLFUNCCALL DLLMultiCall(int eventnum) {
  // We don't need eventnum right now.

  switch (eventnum) {
  case MT_EVT_GET_HELP:
    strcpy(DLLHelpText1, TXT_PXO_HELP1);
    strcpy(DLLHelpText2, TXT_PXO_HELP2);
    strcpy(DLLHelpText3, TXT_PXO_HELP3);
    strcpy(DLLHelpText4, TXT_PXO_HELP4);
    break;
  case MT_EVT_LOGIN:
    DLLDatabaseReadInt("BypassChat", &Bypass_chat);
    if (!DLLTCP_active) {
      DLLDoMessageBox(TXT_PXO_ERROR, TXT_PXO_NO_TCPIP, MSGBOX_OK, UICOL_WINDOW_TITLE, UICOL_TEXT_NORMAL);
      *DLLMultiGameStarting = 0;
      break;
    }

    *DLLMultiGameStarting = 0;
    if (*DLLDedicated_server) {
      InitMTSockets();
    } else {
      DLLCreateSplashScreen(TXT_PXO_CONNECTING, 1);
      InitMTSockets();
      MT_Sock_inited = true;
      DLLCloseSplashScreen();
    }
    if (!All_ok) {
      *DLLMultiGameStarting = 0;
      return;
    }
    {
      UnvalidatedDLL = 0;
      DLLCreateSplashScreen(TXT_PXO_CONNECTING, 1);
      DLLPollUI();
      if (MT_Initialized) {
        DLLPollUI();
        if (!MTVersionCheck()) {
          if (Login_aborted) {
            MT_Initialized = 0;
          } else {
            // If the first call fails, try again
            DLLPollUI();
            if (!MTVersionCheck()) {
              DLLPollUI();
              if (!MTVersionCheck()) {
                // If this call fails, we have a problem, and when MT_EVT_LOGIN is called we will let the user know.
                UnvalidatedDLL = 1;
              }
            }
          }
        }
      }
      DLLCloseSplashScreen();
      if (!MT_Initialized) {
        DLLDoMessageBox(TXT_PXO_MASTERTRACKER, TXT_PXO_CANTCONNECT, MSGBOX_OK, UICOL_WINDOW_TITLE, UICOL_TEXT_NORMAL);
        return;
      }
      // Start off with a login to tracker dialog
      if (UnvalidatedDLL) {
        DLLDoMessageBox(TXT_PXO_MASTERTRACKER, TXT_PXO_CANTAUTOVALIDATE, MSGBOX_OK, UICOL_WINDOW_TITLE,
                        UICOL_TEXT_NORMAL);
        return;
      }

      if (LoginMasterTracker()) {
        // menu.... start a game, or join a game
        if (MainMultiplayerMenu()) {
          *DLLMultiGameStarting = 1;
        } else {
          *DLLMultiGameStarting = 0;
        }
      } else {
        DLLmprintf(0, "Login failed!\n");
        *DLLMultiGameStarting = 0;
        return;
      }
    }
    break;
  case MT_EVT_FRAME:
    DoMTFrame();
    break;
  case MT_EVT_FIRST_FRAME:
    MTWritingPilot = -1;
    MTReadingPilot = -1;
    *DLLGame_is_master_tracker_game = 1;
    // strcpy(DLLD3_tracker_info.game_name,DLLNetgame->name);
    // strcpy(DLLD3_tracker_info.mission_name,DLLNetgame->mission);
    strcpy(DLLD3_tracker_info.lobby, DLLPXO_hosted_lobby_name);
    StartTrackerGame(&DLLD3_tracker_info);
    break;
  case MT_EVT_GAME_OVER:
    DoMTGameOver();
    /*
    if(!All_ok)
            break;
    //menu.... start a game, or join a game
    if(MainMultiplayerMenu())
    {
            *DLLMultiGameStarting = 1;
    }
    else
    {
            *DLLMultiGameStarting = 0;
    }
    */
    break;
  case MT_AUTO_LOGIN:
    if (!DLLTCP_active) {
      DLLDoMessageBox(TXT_PXO_ERROR, TXT_PXO_NO_TCPIP, MSGBOX_OK, UICOL_WINDOW_TITLE, UICOL_TEXT_NORMAL);
      *DLLMultiGameStarting = 0;
      break;
    }
    InitMTSockets();
    if (!All_ok) {
      *DLLMultiGameStarting = 0;
      return;
    }
    AutoLoginAndJoinGame();
    break;
  case MT_AUTO_START:
    InitMTSockets();
    if (!All_ok) {
      *DLLMultiGameStarting = 0;
      return;
    }
    Auto_start = true;
    AutoLoginAndStartGame();
    break;
  case MT_RETURN_TO_GAME_LIST:
    Bypass_chat = 1;

    // menu.... start a game, or join a game
    if (MainMultiplayerMenu()) {
      *DLLMultiGameStarting = 1;
    } else {
      *DLLMultiGameStarting = 0;
    }
    break;
  }
}

#ifdef MACINTOSH
#pragma export off
#endif

int LoginMasterTracker() {

  void *title_text = DLLCreateNewUITextItem(TXT_PXO_LOGINMASTERTRKR, UICOL_WINDOW_TITLE);
  void *cancel_on_text = DLLCreateNewUITextItem(TXT_PXO_CANCEL, UICOL_HOTSPOT_HI);
  void *login_on_text = DLLCreateNewUITextItem(TXT_PXO_LOGIN, UICOL_HOTSPOT_HI);

  void *cancel_off_text = DLLCreateNewUITextItem(TXT_PXO_CANCEL, UICOL_HOTSPOT_LO);
  void *login_off_text = DLLCreateNewUITextItem(TXT_PXO_LOGIN, UICOL_HOTSPOT_LO);

  void *login_id_text = DLLCreateNewUITextItem(TXT_PXO_LOGINID, UICOL_TEXT_NORMAL);
  void *tracker_id_text = DLLCreateNewUITextItem(TXT_PXO_TRACKERID, UICOL_TEXT_NORMAL);
  void *password_text = DLLCreateNewUITextItem(TXT_PXO_PASSWORD, UICOL_TEXT_NORMAL);

  void *new_prof_on_text = DLLCreateNewUITextItem(TXT_PXO_CREATENEWPROFILE, UICOL_HOTSPOT_HI);
  void *new_prof_off_text = DLLCreateNewUITextItem(TXT_PXO_CREATENEWPROFILE, UICOL_HOTSPOT_LO);

  void *blank_text = DLLCreateNewUITextItem(TXT_PXO_BLANK, GR_BLACK);

  int exit_menu = 0;
  int ret = 0;

  int loginlen = LOGIN_LEN;
  int passlen = PASSWORD_LEN;

  void *main_wnd = DLLNewUIGameWindowCreate(TRACKER_MENU_X, TRACKER_MENU_Y, TRACKER_MENU_W, TRACKER_MENU_H,
                                            UIF_PROCESS_ALL | UIF_CENTER | NUWF_TITLEMED);

  void *title = DLLTextCreate(main_wnd, title_text, 0, 7, UIF_CENTER);

  void *password = DLLTextCreate(main_wnd, password_text, 30, 130, UIF_CENTER);
  void *login_id = DLLTextCreate(main_wnd, login_id_text, 50, 80, UIF_CENTER);

  void *pass_edit = DLLEditCreate(main_wnd, UID_OK, 100, 140, 130, 15, UIF_CENTER | UIED_PASSWORD);

  void *login_hs =
      DLLHotSpotCreate(main_wnd, UID_OK, KEY_ENTER, login_off_text, login_on_text, 60, TRACKER_MENU_H - 80, 60, 20, 0);

  void *cancel_hs = DLLHotSpotCreate(main_wnd, UID_CANCEL, KEY_ESC, cancel_off_text, cancel_on_text, 130,
                                     TRACKER_MENU_H - 80, 60, 20, 0);

  void *new_id_hs =
      DLLHotSpotCreate(main_wnd, 4, KEY_N, new_prof_off_text, new_prof_on_text, 0, 45, 120, 20, UIF_CENTER | UIF_FIT);

  void *login_edit = DLLEditCreate(main_wnd, 3, 100, 90, 130, 15, UIF_CENTER);

  // Read defaults

  DLLDatabaseRead("TrackerLogin", szloginid, &loginlen);
  DLLDatabaseRead("TrackerPassword", szpassword, &passlen);

  DLLEditSetText(login_edit, szloginid);
  DLLEditSetText(pass_edit, szpassword);

  DLLNewUIGameWindowOpen(main_wnd);

  while (!exit_menu) {
    int res;

    res = DLLDoUI();

    // handle all UI results.

    switch (res) {
    case 3:
      DLLmprintf(0, "Got event 3!\n");
      break;
    case 4:
#ifdef WIN32
      // TODO: reacivate for site opening
      // ShellExecute(NULL, "open", MTADDNEWURL, NULL, NULL, SW_SHOW);
#endif
      break;
    case UID_OK: {
      DLLEditGetText(login_edit, szloginid, LOGIN_LEN);
      DLLEditGetText(pass_edit, szpassword, PASSWORD_LEN);

      DLLDatabaseWrite("TrackerLogin", szloginid, strlen(szloginid) + 1);
      DLLDatabaseWrite("TrackerPassword", szpassword, strlen(szpassword) + 1);

      if ((!*szloginid) || (!*szpassword)) {
        DLLDoMessageBox(TXT_PXO_MASTERTRACKER, TXT_PXO_BADLOGIN, MSGBOX_OK, UICOL_WINDOW_TITLE, UICOL_TEXT_NORMAL);
        break;
      }

      // Fill out the validate struct and send off the packet
      validate_id_request val_user{};
      strcpy(val_user.tracker_id, sztrackerid);
      strcpy(val_user.login, szloginid);
      strcpy(val_user.password, szpassword);

      DLLCreateSplashScreen(TXT_PXO_CONNECTING, 1);

      int valret = ValidateUser(&val_user, sztrackerid);

      while (valret == 0) {
        valret = ValidateUser(nullptr, nullptr);
        res = DLLPollUI();
        if (res == 99) {
          valret = -2;
        }
        DLLDescentDefer();
      }
      DLLCloseSplashScreen();
      if (valret == 1) {
        // User was validated
        DLLmprintf(0, "Mastertracker user validated!\n");
        // Run this to make sure we properly ACK the server.
        for (int j = 0; j < 10; j++)
          PollPTrackNet();
        strcpy(DLLTracker_id, sztrackerid);
        strcpy(DLLMPlayers[DLLPlayer_num].tracker_id, sztrackerid);
        exit_menu = 1;
        ret = 1;

        break;
      } else if (valret == -1) {
        // User invalid!
        DLLmprintf(0, "Mastertracker user not validated!\n");
        DLLDoMessageBox(TXT_PXO_MASTERTRACKER, TXT_PXO_BADLOGIN, MSGBOX_OK, UICOL_WINDOW_TITLE, UICOL_TEXT_NORMAL);
        // Run this to make sure we properly ACK the server.
        for (int j = 0; j < 10; j++)
          PollPTrackNet();
        break;
      } else {
        // timeout waiting for tracker!
        DLLmprintf(0, "Mastertracker timeout!\n");
        DLLDoMessageBox(TXT_PXO_MASTERTRACKER, TXT_PXO_TIMEOUTMT, MSGBOX_OK, UICOL_WINDOW_TITLE, UICOL_TEXT_NORMAL);
        // Run this to make sure we properly ACK the server.
        for (int j = 0; j < 10; j++)
          PollPTrackNet();
        break;
      }
    }
    case UID_CANCEL:
      exit_menu = 1;
      ret = 0;
      break;
    }
  }

  DLLNewUIGameWindowClose(main_wnd);
  DLLNewUIGameWindowDestroy(main_wnd);

  DLLRemoveUITextItem(title_text);
  DLLRemoveUITextItem(cancel_on_text);
  DLLRemoveUITextItem(login_on_text);
  DLLRemoveUITextItem(cancel_off_text);
  DLLRemoveUITextItem(login_off_text);
  DLLRemoveUITextItem(login_id_text);
  DLLRemoveUITextItem(tracker_id_text);
  DLLRemoveUITextItem(password_text);
  DLLRemoveUITextItem(new_prof_on_text);
  DLLRemoveUITextItem(new_prof_off_text);
  DLLRemoveUITextItem(blank_text);

  DLLDeleteUIItem(main_wnd);
  DLLDeleteUIItem(title);
  DLLDeleteUIItem(cancel_hs);
  DLLDeleteUIItem(login_hs);
  DLLDeleteUIItem(new_id_hs);
  DLLDeleteUIItem(login_edit);
  DLLDeleteUIItem(password);
  DLLDeleteUIItem(login_id);
  DLLDeleteUIItem(pass_edit);

  return ret;
}

// The first multiplayer menu that the user will see...all multiplayer stuff is
// reached from this menu
// Returns true if we're starting a multiplayer game
#define CONNECT_PXO_TIMEOUT 60.0
#define MAX_CHAT_SEND_LEN 200
#define MAX_CHAT_CHANNELS 50
#define CHAT_INFO_LEN 200
#define CHAT_COUNT_LEN 10
#define CHAT_MAX_USERLIST 200
#define CHAT_USER_REFRESH_TIME 5
#define CHAT_LIST_REFRESH_TIME 10

struct {
  char name[CHAT_INFO_LEN];
  char origname[CHAT_INFO_LEN];
  char topic[CHAT_INFO_LEN];
  char count[CHAT_COUNT_LEN];
  char games[CHAT_COUNT_LEN];
} chan_info[MAX_CHAT_CHANNELS];

int MainMultiplayerMenu() {

  DLLmprintf(0, "%d", DESCENT3_BLOCK_SIZE);
  if (!ShowMessageOfTheDay()) {
    return 0;
  }

  DLLmprintf(0, "Inside MainMultiplayerMenu()\n");
  if (Bypass_chat && !ChatStarted) {
    int rcode1 = SearchMasterTrackerGameMenu();
    if (rcode1 == -1)
      rcode1 = 0;
    return rcode1;
  }

  DLLToggleUICallback(0);
  ChatStarted = 1;
  void *title_text = DLLCreateNewUITextItem(TXT_PXO_CONNECTING, UICOL_WINDOW_TITLE);

  void *cancel_on_text = DLLCreateNewUITextItem(TXT_PXO_CANCEL, UICOL_HOTSPOT_HI);
  void *cancel_off_text = DLLCreateNewUITextItem(TXT_PXO_CANCEL, UICOL_HOTSPOT_LO);

  void *exit_on_text = DLLCreateNewUITextItem(TXT_PXO_EXIT, UICOL_HOTSPOT_HI);
  void *exit_off_text = DLLCreateNewUITextItem(TXT_PXO_EXIT, UICOL_HOTSPOT_LO);

  void *priv_msg_on_text = DLLCreateNewUITextItem(TXT_PXO_SENDPRIV, UICOL_HOTSPOT_HI);
  void *priv_msg_off_text = DLLCreateNewUITextItem(TXT_PXO_SENDPRIV, UICOL_HOTSPOT_LO);

  void *join_lobby_on_text = DLLCreateNewUITextItem(TXT_PXO_JOINPRIV, UICOL_HOTSPOT_HI);
  void *join_lobby_off_text = DLLCreateNewUITextItem(TXT_PXO_JOINPRIV, UICOL_HOTSPOT_LO);

  void *join_chan_on_text = DLLCreateNewUITextItem(TXT_PXO_JOINCHAN, UICOL_HOTSPOT_HI);
  void *join_chan_off_text = DLLCreateNewUITextItem(TXT_PXO_JOINCHAN, UICOL_HOTSPOT_LO);

  void *find_pilot_on_text = DLLCreateNewUITextItem(TXT_PXO_FINDPILOT, UICOL_HOTSPOT_HI);
  void *find_pilot_off_text = DLLCreateNewUITextItem(TXT_PXO_FINDPILOT, UICOL_HOTSPOT_LO);

  void *get_pilot_on_text = DLLCreateNewUITextItem(TXT_PXO_GETPILOTINFO, UICOL_HOTSPOT_HI);
  void *get_pilot_off_text = DLLCreateNewUITextItem(TXT_PXO_GETPILOTINFO, UICOL_HOTSPOT_LO);

  void *game_on_text = DLLCreateNewUITextItem(TXT_PXO_JOINSTARTGAME, UICOL_HOTSPOT_HI);
  void *game_off_text = DLLCreateNewUITextItem(TXT_PXO_JOINSTARTGAME, UICOL_HOTSPOT_LO);

  void *send_on_text = DLLCreateNewUITextItem(TXT_PXO_SEND, UICOL_HOTSPOT_HI);
  void *send_off_text = DLLCreateNewUITextItem(TXT_PXO_SEND, UICOL_HOTSPOT_LO);

  char fmtlobbytext[200];
  snprintf(fmtlobbytext, sizeof(fmtlobbytext), TXT_PXO_YOUAREINLOBBY, Ourlobby);
  void *lobby_text = DLLCreateNewUITextItem(fmtlobbytext, UICOL_TEXT_AUX);

  void *blank_text = DLLCreateNewUITextItem(TXT_PXO_BLANK, UICOL_TEXT_AUX);
  char sendline[MAX_CHAT_SEND_LEN];
  int exit_menu = 0;
  int ret = 0;
  int res;
  const char *p;
  int i;
  float lastlisttime = 0;
  float lastchanlisttime = 0;
  void *chan_ti[MAX_CHAT_CHANNELS];
  void *user_ti[CHAT_MAX_USERLIST];
  char selpilot[MAX_CHAT_SEND_LEN];
  char oldselchan[200];
  for (i = 0; i < MAX_CHAT_CHANNELS; i++)
    chan_ti[i] = nullptr;
  for (i = 0; i < CHAT_MAX_USERLIST; i++)
    user_ti[i] = nullptr;

  uint8_t oldalpha = *DLLNewUIWindow_alpha;

  int colx1 = 0;
  int colx2 = 148;
  DLLSetScreenMode(SM_MENU);
  *DLLNewUIWindow_alpha = 255;

  for (i = 0; i < MAX_CHAT_CHANNELS; i++) {
    chan_info[i].origname[0] = '\0';
  }

  // Create our buttons
  void *main_wnd = DLLNewUIWindowCreate(0, 0, 640, 480, UIF_PROCESS_ALL);

  // void HotSpotCreate(int item,int parentitem, int id, int key, int txtitemoff, int txtitemon, int x, int y, int w,
  // int h, int flags,int winnum)
  void *exit_hs = DLLHotSpotCreate(main_wnd, 5, KEY_ESC, exit_off_text, exit_on_text, 33, 427, 70, 15, 0);

  void *priv_hs = DLLHotSpotCreate(main_wnd, 6, 0, priv_msg_off_text, priv_msg_on_text, 328, 403, 170, 15, 0);

#define JOIN_ROW 131
  void *join_lobby_hs =
      DLLHotSpotCreate(main_wnd, 7, 0, join_lobby_off_text, join_lobby_on_text, 400, JOIN_ROW, 170, 15, 0);
  void *join_chan_hs =
      DLLHotSpotCreate(main_wnd, 14, 0, join_chan_off_text, join_chan_on_text, 178, JOIN_ROW, 170, 15, 0);

  void *find_hs = DLLHotSpotCreate(main_wnd, 9, 0, find_pilot_off_text, find_pilot_on_text, 156, 403, 140, 15, 0);
  void *get_pilot_hs =
      DLLHotSpotCreate(main_wnd, 10, 0, get_pilot_off_text, get_pilot_on_text, colx1 + 10, 372, 130, 15, 0);
  void *game_hs = DLLHotSpotCreate(main_wnd, 11, 0, game_off_text, game_on_text, 505, 431, 135, 15, 0);

  void *enter_hs = DLLHotSpotCreate(main_wnd, 15, KEY_ENTER, send_off_text, send_on_text, 550, 370, 70, 15, 0);

  // lobby_text
  void *lobby_txt_gadget = DLLTextCreate(main_wnd, lobby_text, 200, 450, UIF_CENTER);

  // User list box, id #10
  void *user_list = DLLOldListCreate(main_wnd, 10, colx1 + 20, 100, 108, 265, 0);
  // Channel list box, id #14
  void *chan_list = DLLOldListCreate(main_wnd, 14, colx2, 25, 470, 96, 0);

  // Edit box for typing in chat, id # 15
  void *send_edit = DLLOldEditCreate(main_wnd, 15, colx2 + 10, 372, 390, 20, UIED_AUTOSELECT);
  DLLNewUIWindowLoadBackgroundImage(main_wnd, "pxomain.ogf");
  DLLSetOldEditBufferLen(send_edit, 100);
  void *console_item = DLLUIConsoleGadgetCreate(main_wnd, 16, colx2, 165, 0, 51, 16, 0);
  pconsole = console_item;

  DLLNewUIWindowOpen(main_wnd);
  // Menu loop
  // Create status window while we are connecting

  DLLCreateSplashScreen(TXT_PXO_CONNECTING, 1);
  Chat_command *cmd;
  int gotcancel = 0;
  int chat_connected = 0;
  float chat_conn_time = 0;
  char oldseluser[100];
  char chat_whois_info[PILOT_NAME_LEN + TRACKER_ID_LEN + 4];

  char pilot_name[PILOT_STRING_SIZE];
  CurrentPilotName(pilot_name);

  snprintf(chat_whois_info, sizeof(chat_whois_info), "%s %s", sztrackerid, pilot_name);
  chat_conn_time = DLLtimer_GetTime();
  // DLLNewUIWindowSetFocusOnEditGadget(send_edit,main_wnd);
  DLLmprintf(0, "About to connect...\n");
  do {
    chat_connected = ConnectToChatServer(CHATTRACKERNAME, CHATPORT, pilot_name, chat_whois_info);
    // chat_connected = ConnectToChatServer("plasma.outrage.com:7000",pilot_name,chat_whois_info);
    p = GetChatText();
    if (p) {
      DLLUIConsoleGadgetputs(console_item, p);
      DLLUIConsoleGadgetputs(console_item, "\x0a\x0d");
    }
    if ((chat_connected == -1) || ((DLLtimer_GetTime() - chat_conn_time) > CONNECT_PXO_TIMEOUT)) {
      DLLDoMessageBox(TXT_PXO_MASTERTRACKER, TXT_PXO_CANTCONNECT, MSGBOX_OK, UICOL_WINDOW_TITLE, UICOL_TEXT_NORMAL);
      // Go ahead to the game screen.
      // SearchMasterTrackerGameMenu();
      int rcode1 = SearchMasterTrackerGameMenu();
      if (rcode1 == -1)
        rcode1 = 0;
      ret = rcode1;
      exit_menu = 1;
      DLLCloseSplashScreen();
      DLLNewUIWindowClose(main_wnd);
      goto shutdownpxo;
      // gotcancel = 1;
      break;
    }
    res = DLLPollUI();
    if (res == 99) {
      SearchMasterTrackerGameMenu();
      gotcancel = 1;
    }

  } while ((!gotcancel) && (chat_connected == 0));
  DLLCloseSplashScreen();

  if (gotcancel) {
    ret = 0;
    exit_menu = 1;
    DLLNewUIWindowClose(main_wnd);
    goto shutdownpxo;
  }
  DLLmprintf(0, "Connected to chat server!\n");
  if (!JoinNewLobby("#autoselect")) {
    ret = 0;
    exit_menu = 1;
  }
  SendChatString("/list");
  // DLLNewUIWindowSetFocusOnEditGadget(send_edit,main_wnd);
  while (!exit_menu) {

    // Handle commands...
    cmd = GetChatCommandFromQueue();
    if (cmd) {
      switch (cmd->command) {
      case CC_USER_JOINING:
      case CC_USER_LEAVING:
      case CC_KICKED:
      case CC_NICKCHANGED:
        // We will ignore all these things for now
        break;
      case CC_YOURCHANNEL: {
        strcpy(Ourlobby, cmd->data);
        char fmtlobbytext[200];
        char cleanlobby[50];
        memset(cleanlobby, 0, 29);
        strcpy(cleanlobby, Ourlobby + 1);
        for (int l = 0; l < 18; l++) {
          if (cleanlobby[l] == '_')
            cleanlobby[l] = ' ';
          // if(cleanlobby[l]==NULL) cleanlobby[l]= ' ';
        }
        snprintf(fmtlobbytext, sizeof(fmtlobbytext), TXT_PXO_YOUAREINLOBBY, cleanlobby);

        DLLRemoveUITextItem(lobby_text);
        DLLGadgetDestroy(lobby_txt_gadget);
        DLLDeleteUIItem(lobby_txt_gadget);
        lobby_text = DLLCreateNewUITextItem(fmtlobbytext, UICOL_TEXT_AUX);
        lobby_txt_gadget = DLLTextCreate(main_wnd, lobby_text, 0, 450, UIF_CENTER);
        // Now update the text on the bottom of the screen
      } break;
      case CC_DISCONNECTED:
        // Display a message box letting the user know we are disconnected.
        DLLDoMessageBox(TXT_PXO_MASTERTRACKER, TXT_PXO_CHATDISCONNECTED, MSGBOX_OK, UICOL_WINDOW_TITLE,
                        UICOL_TEXT_NORMAL);
        DLLNewUIWindowClose(main_wnd);
        exit_menu = 1;
        break;
      default:
        DLLmprintf(0, "Warning: Received an unknown chat command!\n");
        break;
      }
    }
    if (exit_menu)
      break;
    p = GetChatText();
    if (p) {
      DLLUIConsoleGadgetputs(console_item, p);
      DLLUIConsoleGadgetputs(console_item, "\x0a\x0d");
    }
    // refresh the userlist
    if ((DLLtimer_GetTime() - lastlisttime) > CHAT_USER_REFRESH_TIME) {
      lastlisttime = DLLtimer_GetTime();
      p = GetChatUserList();
      if (p) {

        char *oldsel = DLLOldListGetItem(user_list, DLLOldListGetSelectedIndex(user_list));
        oldseluser[0] = 0;
        if (oldsel)
          strcpy(oldseluser, oldsel);
        void *old_ti = nullptr; // = DLLCreateNewUITextItem(TXT_PXO_JOINSTARTGAME,GR_WHITE);
        // int oldsel = DLLOldListGetSelectedIndex(user_list);
        // void * old_ti =

        DLLOldListRemoveAll(user_list);
        for (i = 0; i < CHAT_MAX_USERLIST; i++) {
          if (user_ti[i] != nullptr)
            DLLRemoveUITextItem(user_ti[i]);
          user_ti[i] = nullptr;
        }
        char seps[] = " ";
        char *tokp;
        tokp = strtok((char *)p, seps);
        if (tokp) {
          for (i = 0; i < CHAT_MAX_USERLIST; i++) {
            user_ti[i] = DLLCreateNewUITextItem(tokp, GR_WHITE);
            DLLOldListAddItem(user_list, user_ti[i]);
            if (strcmp(tokp, oldseluser) == 0)
              old_ti = user_ti[i];
            tokp = strtok(nullptr, seps);
            if (!tokp)
              break;
          }
          if (old_ti)
            DLLOldListSelectItem(user_list, old_ti);
        }
      }
    }
    // refresh the channellist
    if ((DLLtimer_GetTime() - lastchanlisttime) > CHAT_LIST_REFRESH_TIME) {
      lastchanlisttime = DLLtimer_GetTime();
      SendChatString("/list");
    }
    p = GetChannelList();
    if (p) {
      char *pchanlist;
      pchanlist = (char *)DLLmem_malloc(strlen(p) + 1);
      memset(pchanlist, 0, strlen(p));
      strcpy(pchanlist, p);
      char *tokp = nullptr;
      char *nexttok;
      // tokp = strtok(pchanlist,seps);
      nexttok = strchr(pchanlist, '$');
      if (nexttok) {
        *nexttok = '\0';
        nexttok++;
        tokp = nexttok;
        if (nexttok) {
          nexttok = strchr(nexttok, '$');
          if (nexttok) {
            *nexttok = '\0';
            nexttok++;
          }
        }
      }

      if (tokp) {
        // Remove all previous items
        DLLmprintf(0, "Refreshing channel list\n");
        // get the text of the currently selected channel.
        // char * oldsel = DLLOldListGetItem(chan_list,DLLOldListGetSelectedIndex(chan_list));
        //
        int selitem = DLLOldListGetSelectedIndex(chan_list);
        char *oldsel = nullptr;
        oldselchan[0] = 0;

        if ((selitem > 0) && (selitem < MAX_CHAT_CHANNELS)) {
          oldsel = chan_info[selitem].origname;
          strcpy(oldselchan, oldsel);
        }

        DLLOldListRemoveAll(chan_list);
        for (i = 0; i < MAX_CHAT_CHANNELS; i++) {
          if (chan_ti[i] != nullptr)
            DLLRemoveUITextItem(chan_ti[i]);
          chan_ti[i] = nullptr;
        }
        for (i = 0; i < MAX_CHAT_CHANNELS; i++) {
          char fmtchan[500];
          char *pcount = strchr(tokp, ' ');
          // if(pcount)
          {
            if (!pcount) {
              pcount = (char *)"";
            } else {
              // pcount++;
              *pcount = '\0';
            }

            // 17 is the magic number we want all channel names to align with
            memset(chan_info[i].name, 0, 19);
            strcpy(chan_info[i].origname, tokp);
            strcpy(chan_info[i].name, tokp + 1); // skip the #
            for (int l = 0; l < 18; l++) {
              if (chan_info[i].name[l] == '_')
                chan_info[i].name[l] = ' ';
              if (chan_info[i].name[l] == '\0')
                chan_info[i].name[l] = ' ';
            }
            pcount++;
            char *ptopic = pcount;
            while (isdigit(*ptopic)) {
              ptopic++;
            }
            *ptopic = '\0';
            ptopic++;
            // count
            strcpy(chan_info[i].count, pcount);
            // topic
            strcpy(chan_info[i].topic, ptopic);
            // Now we want it formatted nicely.....
            char chan_name[100];
            memset(chan_name, ' ', 99);
            chan_name[99] = '\0';
            char count_list[10];
            memset(count_list, ' ', 9);
            count_list[9] = '\0';

            memset(fmtchan, 0, 500);

            int textx = 0;
            int charpos = 0;
            int endpos;
#define LIST_ROW1 90
#define LIST_ROW2 130

            strcpy(chan_name, chan_info[i].name);
            endpos = strlen(chan_info[i].name);
            chan_name[endpos] = ' ';

            strcpy(count_list, chan_info[i].count);
            endpos = strlen(chan_info[i].count);
            count_list[endpos] = ' ';

            while (DLLgrtext_GetTextLineWidth(fmtchan) < LIST_ROW1) {
              endpos = strlen(fmtchan);
              fmtchan[endpos] = chan_name[charpos];
              fmtchan[endpos + 1] = NULL;
              charpos++;
            }
            strcat(fmtchan, "\t\0");
            charpos = 0;
            while (DLLgrtext_GetTextLineWidth(fmtchan) < LIST_ROW2) {
              endpos = strlen(fmtchan);
              fmtchan[endpos] = count_list[charpos];
              fmtchan[endpos + 1] = NULL;
              charpos++;
            }
            strcat(fmtchan, "\t\0");

            strcat(fmtchan, chan_info[i].topic);
            // sprintf(fmtchan,"%.15s\t%s\t%s",chan_info[i].name,chan_info[i].count,chan_info[i].topic);
            chan_ti[i] = DLLCreateNewUITextItem(fmtchan, GR_WHITE);
            DLLOldListAddItem(chan_list, chan_ti[i]);
            if (strcmp(oldselchan, chan_info[i].origname) == 0) {
              DLLOldListSelectItem(chan_list, chan_ti[i]);
            }
          }
          tokp = nexttok;
          if (nexttok) {
            nexttok = strchr(nexttok, '$');
            if (nexttok) {
              *nexttok = '\0';
              nexttok++;
            }
          }
          // tokp = strtok(NULL,seps);
          if (!tokp)
            break;
        }
      }
      DLLmem_free(pchanlist);
    }

    res = DLLPollUI();
    if (res != -1) {
      // DLLNewUIWindowSetFocusOnEditGadget(send_edit,main_wnd);
    }
    // handle all UI results.
    switch (res) {
    case -1:
      break;
    case 3:
      // Join Mastertracker game
      {
        DLLmprintf(0, "Sending Mastertracker game list request.\n");
        RequestGameList();
        DLLmprintf(0, "Calling SearchMasterTrackerGameMenu().\n");
        DLLNewUIWindowClose(main_wnd);
        *DLLGame_is_master_tracker_game = 1;
        int gamestart = SearchMasterTrackerGameMenu();
        if (gamestart == 1) {
          exit_menu = 1;
          ret = 1;
        } else if (gamestart == 0) {
          DLLNewUIWindowOpen(main_wnd);
        } else if (gamestart == -1) {
          exit_menu = 1;
          ret = 0;
        }
        break;
      }

    case 4:

      // Start Mastertracker game
      //  Start a netgame
      DLLNewUIWindowClose(main_wnd);
      *DLLGame_is_master_tracker_game = 1;
      if (StartMultiplayerGameMenu()) {
        exit_menu = 1;
        ret = 1;
      } else {
        DLLNewUIWindowOpen(main_wnd);
      }
      break;
    case 5:
      DLLNewUIWindowClose(main_wnd);
      exit_menu = 1;
      ret = 0;
      break;
    case 6:
      // Send a private message
      // Create new dialog box, prompt for user and message, then send message
      DLLmprintf(0, "Sending private Message\n");
      // Get the currently selected pilot name
      strcpy(selpilot, DLLOldListGetItem(user_list, DLLOldListGetSelectedIndex(user_list)));
      SendWhisper(selpilot);
      break;
    case 7:
      // Join a private channel
      if (!JoinPrivateLobby()) {
        ret = 0;
        exit_menu = 0;
      }
      break;
    case 8:
      // Join a channel
      // unused
      break;
    case 9:
      // Find a pilot
      DLLmprintf(0, "Finding a pilot\n");
      FindPilot();
      break;
    case 10:
      // Get pilot stats
      DLLmprintf(0, "Getting pilot statistics\n");
      strcpy(selpilot, DLLOldListGetItem(user_list, DLLOldListGetSelectedIndex(user_list)));
      GetPilotStats(selpilot);
      break;
    case 11: {
      DLLmprintf(0, "Sending Mastertracker game list request.\n");
      RequestGameList();
      DLLmprintf(0, "Calling SearchMasterTrackerGameMenu().\n");
      DLLNewUIWindowClose(main_wnd);
      *DLLGame_is_master_tracker_game = 1;
      int gamestart = SearchMasterTrackerGameMenu();
      if (gamestart == 1) {
        exit_menu = 1;
        ret = 1;
      } else if (gamestart == 0) {
        DLLNewUIWindowOpen(main_wnd);
      } else if (gamestart == -1) {
        exit_menu = 1;
        ret = 0;
      }
      break;
    } break;
    case 14:
      // Channel list box
      DLLmprintf(0, "Joining new public channel\n");
      {
        int selitem = 0;
        DLLmprintf(0, "Joining new public channel\n");
        selitem = DLLOldListGetSelectedIndex(chan_list);
        if (!JoinNewLobby(chan_info[selitem].origname)) {
          ret = 0;
          exit_menu = 0;
        } else {
          char txtmessage[200];
          char cleanlobby[50];
          memset(cleanlobby, 0, 29);
          strcpy(cleanlobby, chan_info[selitem].origname + 1);
          for (int l = 0; l < 18; l++) {
            if (cleanlobby[l] == '_')
              cleanlobby[l] = ' ';
          }
          snprintf(txtmessage, sizeof(txtmessage), TXT_PXO_INNEWLOBBY, cleanlobby);
          DLLDoMessageBox(TXT_PXO_MASTERTRACKER, txtmessage, MSGBOX_OK, UICOL_WINDOW_TITLE, UICOL_TEXT_NORMAL);
        }
      }

      break;
    case 15:
      // Send a message
      DLLOldEditGetText(send_edit, sendline, MAX_CHAT_SEND_LEN - 1);
      if (*sendline == '\0') {
        break;
      }
      DLLOldEditSetText(send_edit, "");
      p = SendChatString(sendline);
      if (p) {
        DLLUIConsoleGadgetputs(console_item, p);
        DLLUIConsoleGadgetputs(console_item, "\x0a\x0d");
      }
      DLLNewUIWindowSetFocusOnEditGadget(send_edit, main_wnd);
      break;
    }
  }
shutdownpxo:

  DLLNewUIWindowDestroy(main_wnd);
  DLLOldListRemoveAll(chan_list);
  DLLOldListRemoveAll(user_list);
  for (i = 0; i < MAX_CHAT_CHANNELS; i++) {
    if (chan_ti[i] != nullptr)
      DLLRemoveUITextItem(chan_ti[i]);
    chan_ti[i] = nullptr;
  }
  for (i = 0; i < CHAT_MAX_USERLIST; i++) {
    if (user_ti[i] != nullptr)
      DLLRemoveUITextItem(user_ti[i]);
    user_ti[i] = nullptr;
  }
  *DLLNewUIWindow_alpha = oldalpha;
  DLLmprintf(0, "Disconnecting from PXO.\n");
  DisconnectFromChatServer();
  ChatStarted = 0;
  DLLmprintf(0, "Disconnected.\n");
  DLLToggleUICallback(1);

  // Delete all those items we created
  DLLDeleteUIItem(main_wnd);
  DLLDeleteUIItem(priv_hs);
  DLLDeleteUIItem(join_lobby_hs);
  DLLDeleteUIItem(join_chan_hs);
  DLLDeleteUIItem(find_hs);
  DLLDeleteUIItem(get_pilot_hs);
  DLLDeleteUIItem(game_hs);
  DLLDeleteUIItem(enter_hs);
  DLLDeleteUIItem(user_list);
  DLLDeleteUIItem(chan_list);
  DLLDeleteUIItem(send_edit);
  DLLDeleteUIItem(console_item);
  DLLDeleteUIItem(lobby_txt_gadget);

  DLLRemoveUITextItem(title_text);
  DLLRemoveUITextItem(lobby_text);
  DLLRemoveUITextItem(cancel_on_text);
  DLLRemoveUITextItem(cancel_off_text);
  DLLRemoveUITextItem(exit_on_text);
  DLLRemoveUITextItem(exit_off_text);
  DLLRemoveUITextItem(priv_msg_on_text);
  DLLRemoveUITextItem(priv_msg_off_text);
  DLLRemoveUITextItem(join_lobby_on_text);
  DLLRemoveUITextItem(join_lobby_off_text);
  DLLRemoveUITextItem(join_chan_on_text);
  DLLRemoveUITextItem(join_chan_off_text);
  DLLRemoveUITextItem(find_pilot_on_text);
  DLLRemoveUITextItem(find_pilot_off_text);
  DLLRemoveUITextItem(get_pilot_on_text);
  DLLRemoveUITextItem(get_pilot_off_text);
  DLLRemoveUITextItem(game_on_text);
  DLLRemoveUITextItem(game_off_text);
  DLLRemoveUITextItem(blank_text);
  DLLRemoveUITextItem(send_on_text);
  DLLRemoveUITextItem(send_off_text);
  return ret;
}

#define SORT_GAMENAME 30
#define SORT_GAMETYPE 31
#define SORT_MISSION 32
#define SORT_LEVEL 33
#define SORT_PLAYERS 34
#define SORT_PING 35

int sort_type;

bool invert_sort_gamename = true;
bool invert_sort_gametype = true;
bool invert_sort_mission = true;
bool invert_sort_levels = true;
bool invert_sort_players = true;
bool invert_sort_ping = true;

int net_game_compare(const void *arg1, const void *arg2) {

  network_game *net1 = (network_game *)arg1;
  network_game *net2 = (network_game *)arg2;

  if ((!arg1) || (!arg2))
    return 0;

  switch (sort_type) {
  case SORT_GAMENAME: {
    return stricmp(net1->name, net2->name);
  } break;
  case SORT_GAMETYPE: {
    return stricmp(net1->scriptname, net2->scriptname);
  } break;
  case SORT_MISSION: {
    return stricmp(net1->mission_name, net2->mission_name);
  } break;
  case SORT_LEVEL: {
    if (net1->level_num == net2->level_num)
      return 0;
    else
      return (net1->level_num - net2->level_num);
  } break;
  case SORT_PLAYERS: {
    if (net1->curr_num_players == net2->curr_num_players)
      return 0;
    else
      return (net1->curr_num_players - net2->curr_num_players);
  } break;
  case SORT_PING: {
    if (net1->server_response_time == net2->server_response_time)
      return 0;
    else
      return (net1->server_response_time < net2->server_response_time) ? 1 : -1;
  } break;
  }
  return 0;
}

void ResortGameList(void *lb, int type, bool invert) {

  if (!*DLLNum_network_games_known) {
    return;
  }
  // Make a copy of the games list
  network_game *net_game_copy;
  net_game_copy = (network_game *)DLLmem_malloc(sizeof(network_game) * (*DLLNum_network_games_known));
  memcpy(net_game_copy, &DLLNetwork_games[0], sizeof(network_game) * (*DLLNum_network_games_known));

  // Set the sort type
  sort_type = type;

  // Do the actual sort
  qsort(net_game_copy, *DLLNum_network_games_known, sizeof(network_game), net_game_compare);

  // Now populate the list in the order sorted...
  NextGameItemNo = 0;
  DLLListRemoveAll(lb);
  int i;
  if (!invert) {
    for (i = 0; i < *DLLNum_network_games_known; i++) {
      int pxo_item = GetPXOItemByHandle(net_game_copy[i].handle);
      if (pxo_item != -1) {
        PXOGamelist[pxo_item].lb_no = NextGameItemNo;
        NextGameItemNo++;
        DLLListAddItem(lb, PXOGamelist[pxo_item].ti);
      }
    }
  } else {
    for (i = *DLLNum_network_games_known; i >= 0; i--) {
      int pxo_item = GetPXOItemByHandle(net_game_copy[i].handle);
      if (pxo_item != -1) {
        PXOGamelist[pxo_item].lb_no = NextGameItemNo;
        NextGameItemNo++;
        DLLListAddItem(lb, PXOGamelist[pxo_item].ti);
      }
    }
  }

  DLLmem_free(net_game_copy);
}

#define GET_MT_GAME_TIME 5
#define REQ_GAME_LIST_INTERVAL 8

#define GET_INFO_ID 50

int SearchMasterTrackerGameMenu() {

  int exit_menu = 0;
  int cury = 40;
  int ret = 0;
  int res;

  game_list *games = nullptr;
  int i = 0;
  float last_req_time;
  char selgame[200];
  void *selti = nullptr;
  void *return_text_on = DLLCreateNewUITextItem(TXT_PXO_RETURNTOCHAT, UICOL_HOTSPOT_HI);
  void *return_text_off = DLLCreateNewUITextItem(TXT_PXO_RETURNTOCHAT, UICOL_HOTSPOT_LO);
  void *game_head_text = DLLCreateNewUITextItem(TXT_PXO_GAMELISTHDR, UICOL_TEXT_NORMAL);
  void *exit_on_text = DLLCreateNewUITextItem(TXT_PXO_EXIT, UICOL_HOTSPOT_HI);
  void *exit_off_text = DLLCreateNewUITextItem(TXT_PXO_EXIT, UICOL_HOTSPOT_LO);
  void *join_on_text = DLLCreateNewUITextItem(TXT_PXO_JOINSEL, UICOL_HOTSPOT_HI);
  void *join_off_text = DLLCreateNewUITextItem(TXT_PXO_JOINSEL, UICOL_HOTSPOT_LO);
  void *start_on_text = DLLCreateNewUITextItem(TXT_PXO_STARTNEW, UICOL_HOTSPOT_HI);
  void *start_off_text = DLLCreateNewUITextItem(TXT_PXO_STARTNEW, UICOL_HOTSPOT_LO);

  void *gname_on_text = DLLCreateNewUITextItem(TXT_PXO_GAMENAME2, UICOL_HOTSPOT_HI);
  void *gname_off_text = DLLCreateNewUITextItem(TXT_PXO_GAMENAME2, UICOL_HOTSPOT_LO);
  void *gtype_on_text = DLLCreateNewUITextItem(TXT_PXO_GAMETYPE, UICOL_HOTSPOT_HI);
  void *gtype_off_text = DLLCreateNewUITextItem(TXT_PXO_GAMETYPE, UICOL_HOTSPOT_LO);
  void *msn_on_text = DLLCreateNewUITextItem(TXT_PXO_MISSION, UICOL_HOTSPOT_HI);
  void *msn_off_text = DLLCreateNewUITextItem(TXT_PXO_MISSION, UICOL_HOTSPOT_LO);
  void *lvl_on_text = DLLCreateNewUITextItem(TXT_PXO_LEVEL, UICOL_HOTSPOT_HI);
  void *lvl_off_text = DLLCreateNewUITextItem(TXT_PXO_LEVEL, UICOL_HOTSPOT_LO);
  void *plrs_on_text = DLLCreateNewUITextItem(TXT_PXO_PLAYERS, UICOL_HOTSPOT_HI);
  void *plrs_off_text = DLLCreateNewUITextItem(TXT_PXO_PLAYERS, UICOL_HOTSPOT_LO);
  void *ping_on_text = DLLCreateNewUITextItem(TXT_PXO_PING, UICOL_HOTSPOT_HI);
  void *ping_off_text = DLLCreateNewUITextItem(TXT_PXO_PING, UICOL_HOTSPOT_LO);

  char fmt_textstr[200];
  snprintf(fmt_textstr, sizeof(fmt_textstr), TXT_PXO_MAKEGAMEDEFAULT, 28);
  void *default_on_text = DLLCreateNewUITextItem(fmt_textstr, UICOL_HOTSPOT_HI);
  snprintf(fmt_textstr, sizeof(fmt_textstr), TXT_PXO_MAKEGAMEDEFAULT, 28);

  void *default_off_text = DLLCreateNewUITextItem(fmt_textstr, UICOL_HOTSPOT_LO);
  void *game_hdr_text = DLLCreateNewUITextItem(TXT_PXO_GAME_HDR, UICOL_WINDOW_TITLE);

  void *info_on_text = DLLCreateNewUITextItem("", UICOL_HOTSPOT_HI);
  void *info_off_text = DLLCreateNewUITextItem("", UICOL_HOTSPOT_LO);

  memset(PXOGamelist, 0, sizeof(PXOGamelist));
  NextGameItemNo = 0;

  void *return_hs;
  void *set_dft_hs;

  void *net_game_txt_items[MAX_NET_GAMES];
  int a;
  bool hardexit = false;
  for (a = 0; a < MAX_NET_GAMES; a++)
    net_game_txt_items[a] = nullptr;
  uint8_t oldalpha = *DLLNewUIWindow_alpha;

  DLLSetScreenMode(SM_MENU);
  *DLLNewUIWindow_alpha = 255;

  void *main_wnd = DLLNewUIWindowCreate(0, 0, 640, 480, UIF_PROCESS_ALL);

  void *screen_header = DLLTextCreate(main_wnd, game_hdr_text, 5, 15, UIF_CENTER);
  cury += 30;
  void *start_hs = DLLHotSpotCreate(main_wnd, 7, KEY_S, start_off_text, start_on_text, 320, cury, 150, 15, UIF_CENTER);
  cury += 30; // 25;

  int setdfty;

  return_hs = DLLHotSpotCreate(main_wnd, 8, KEY_R, return_text_off, return_text_on, 490, cury, 250, 15, UIF_CENTER);
  cury += 20;

  if (Bypass_chat) {

    snprintf(fmt_textstr, sizeof(fmt_textstr), TXT_PXO_MAKEGAMEDEFAULT, 29);
    default_on_text = DLLCreateNewUITextItem(fmt_textstr, UICOL_HOTSPOT_HI);
    snprintf(fmt_textstr, sizeof(fmt_textstr), TXT_PXO_MAKEGAMEDEFAULT, 29);
    default_off_text = DLLCreateNewUITextItem(fmt_textstr, UICOL_HOTSPOT_LO);
    setdfty = cury;
    set_dft_hs = DLLHotSpotCreate(main_wnd, 9, 0, default_off_text, default_on_text, 490, cury, 300, 15, UIF_CENTER);
    cury += 20;
  } else {
    snprintf(fmt_textstr, sizeof(fmt_textstr), TXT_PXO_MAKEGAMEDEFAULT, 28);
    default_on_text = DLLCreateNewUITextItem(fmt_textstr, UICOL_HOTSPOT_HI);
    snprintf(fmt_textstr, sizeof(fmt_textstr), TXT_PXO_MAKEGAMEDEFAULT, 28);
    default_off_text = DLLCreateNewUITextItem(fmt_textstr, UICOL_HOTSPOT_LO);
    setdfty = cury;
    set_dft_hs = DLLHotSpotCreate(main_wnd, 9, 0, default_off_text, default_on_text, 490, cury, 300, 15, UIF_CENTER);
    cury += 30;
  }
  // void * game_head = DLLTextCreate(main_wnd,game_head_text,45,cury,0);

  void *gname_hs = DLLHotSpotCreate(main_wnd, SORT_GAMENAME, 0, gname_off_text, gname_on_text, 44, cury,
                                    DLLgrtext_GetTextLineWidth(TXT_PXO_GAMENAME2) + 1, 15, 0);
  void *gtype_hs = DLLHotSpotCreate(main_wnd, SORT_GAMETYPE, 0, gtype_off_text, gtype_on_text, 215, cury,
                                    DLLgrtext_GetTextLineWidth(TXT_PXO_GAMETYPE) + 1, 15, 0);
  void *msn_hs = DLLHotSpotCreate(main_wnd, SORT_MISSION, 0, msn_off_text, msn_on_text, 320, cury,
                                  DLLgrtext_GetTextLineWidth(TXT_PXO_MISSION) + 1, 15, 0);
  void *lvl_hs = DLLHotSpotCreate(main_wnd, SORT_LEVEL, 0, lvl_off_text, lvl_on_text, 428, cury,
                                  DLLgrtext_GetTextLineWidth(TXT_PXO_LEVEL) + 1, 15, 0);
  void *players_hs = DLLHotSpotCreate(main_wnd, SORT_PLAYERS, 0, plrs_off_text, plrs_on_text, 479, cury,
                                      DLLgrtext_GetTextLineWidth(TXT_PXO_PLAYERS) + 1, 15, 0);
  void *ping_hs = DLLHotSpotCreate(main_wnd, SORT_PING, 0, ping_off_text, ping_on_text, 549, cury,
                                   DLLgrtext_GetTextLineWidth(TXT_PXO_PING) + 1, 15, 0);

  cury += 15;
  void *game_list = DLLListCreate(main_wnd, 6, 10, cury, 600, 230, UIF_CENTER | UILB_NOSORT);
  cury += 260;
  void *join_hs = DLLHotSpotCreate(main_wnd, 6, KEY_ENTER, join_off_text, join_on_text, 100, cury, 130, 15, 0);
  void *exit_hs = DLLHotSpotCreate(main_wnd, 5, KEY_ESC, exit_off_text, exit_on_text, 400, cury, 70, 15, 0);

  void *info_hs = DLLHotSpotCreate(main_wnd, GET_INFO_ID, KEY_I, info_off_text, info_on_text, 1, 1, 1, 1, 0);

  DLLNewUIWindowLoadBackgroundImage(main_wnd, "pxogame.ogf");
  DLLNewUIWindowOpen(main_wnd);
  *DLLNum_network_games_known = 0;
  int lastgamesfound = 0;
  int itemp;
  last_req_time = DLLtimer_GetTime();
  RequestGameList();
  *DLLNum_network_games_known = 0;
  DLLmprintf(0, "Waiting for Mastertracker response.\n");

  // Menu loop
  while (!exit_menu) {
    if (ChatStarted)
      const char *p = GetChatText();

    DLLDescentDefer();
    IdleGameTracker();
    games = GetGameList();
    res = DLLPollUI();
    if (games) {
      // DLLmprintf(0,"GetGameList() returned a gamedata.\n");
      for (i = 0; i < (MAX_GAME_LISTS_PER_PACKET * 4); i++) {
        //				char *gn = games->game_name[i];
        if (games->game_type == GT_D3TNG) {
          DLLSearchForGamesPXO(games->game_server[i], games->game_port[i]);
        } else {
          if (games->game_server[i] && games->game_port[i]) {
            DLLmprintf(0, "Bad bad bad!!!!\n");
            DLLSearchForGamesPXO(games->game_server[i], games->game_port[i]);
          }
        }
      }
      games = nullptr;
    }
    if ((DLLtimer_GetTime() - last_req_time) > REQ_GAME_LIST_INTERVAL) {
      last_req_time = DLLtimer_GetTime();
      RequestGameList();
      *DLLMulti_Gamelist_changed = true;
      int selno = DLLListGetSelectedIndex(game_list);
      if (selno >= 0) {
        strcpy(selgame, DLLNetwork_games[selno].name);
      } else {
        selgame[0] = '\0';
      }
    }
    DLLUpdateAndPackGameList();

    if ((itemp = DLLSearchForGamesPXO(0, 0)) || *DLLMulti_Gamelist_changed) {
      UpdateGamelist(game_list);
    }

    if (res == -1) {
      continue;
    }
    // handle all UI results.
    switch (res) {

    case 5:
      // Hard exit. Don't return to chat if in bypass chat mode
      hardexit = true;
      DLLNewUIWindowClose(main_wnd);
      exit_menu = 1;
      break;
    case 6:
      // Double click on listbox, or join selected hit.
      if (*DLLNum_network_games_known) {
        // Get the appropriate game address
        int gameno;
        gameno = DLLListGetSelectedIndex(game_list);

        int gameid = GetGameByLBNo(gameno);

        if (gameid == -1)
          break;
        gameno = gameid;

        DLLmprintf(0, "Selected item is %s\n", DLLNetwork_games[gameno].name);

        network_address s_address;
        s_address.connection_type = NP_TCP;
        memcpy(&s_address.address, &DLLNetwork_games[gameno].addr, sizeof(network_address));
        s_address.port = DLLNetwork_games[gameno].addr.port;
        *DLLGame_is_master_tracker_game = 1;
        DLLMultiStartClient(nullptr);

        if (DLLDoPlayerMouselookCheck(DLLNetwork_games[gameno].flags)) {
          char script_file[500];
          snprintf(script_file, sizeof(script_file), "%s.d3m", DLLNetwork_games[gameno].scriptname);
          if (DLLCheckGetD3M(script_file)) {
            // Check to see if this mission exists!
            if (DLLmsn_CheckGetMission(&s_address, DLLNetwork_games[gameno].mission)) {
              if ((DLLTryToJoinServer(&s_address))) {
                DLLmprintf(0, "Menu: Game joined!\n");
                DLLNewUIWindowClose(main_wnd);
                exit_menu = 1;
                ret = 1;
              } else {
                DLLNewUIWindowClose(main_wnd);
                DLLNewUIWindowOpen(main_wnd);
              }
            }
          }
        }
      } else {
        DLLListRemoveAll(game_list);
        last_req_time = DLLtimer_GetTime() - (REQ_GAME_LIST_INTERVAL * 2);
        DLLDoMessageBox(TXT_PXO_ERROR, TXT_PXO_NO_GAMES, MSGBOX_OK, UICOL_WINDOW_TITLE, UICOL_TEXT_NORMAL);
      }
      break;
    case 7:
      // Start a new game

      DLLNewUIWindowClose(main_wnd);
      *DLLGame_is_master_tracker_game = 1;
      if (StartMultiplayerGameMenu()) {
        exit_menu = 1;
        ret = 1;
      } else {
        DLLNewUIWindowOpen(main_wnd);
      }
      break;
    case 8:
      // We just want to return to chat, not totally exit PXO
      DLLNewUIWindowClose(main_wnd);
      exit_menu = 1;
      ret = 0;
      break;
    case 9:
      //	Change the current selection
      {
        int bypass_chat_curr_val;
        DLLDatabaseReadInt("BypassChat", &bypass_chat_curr_val);

        DLLRemoveUITextItem(default_on_text);
        DLLRemoveUITextItem(default_off_text);
        DLLGadgetDestroy(set_dft_hs);
        DLLDeleteUIItem(set_dft_hs);
        if (bypass_chat_curr_val) {
          bypass_chat_curr_val = 0;
          DLLDatabaseWriteInt("BypassChat", bypass_chat_curr_val);
          snprintf(fmt_textstr, sizeof(fmt_textstr), TXT_PXO_MAKEGAMEDEFAULT, 28);
          default_on_text = DLLCreateNewUITextItem(fmt_textstr, UICOL_HOTSPOT_HI);
          snprintf(fmt_textstr, sizeof(fmt_textstr), TXT_PXO_MAKEGAMEDEFAULT, 28);
          default_off_text = DLLCreateNewUITextItem(fmt_textstr, UICOL_HOTSPOT_LO);
          set_dft_hs =
              DLLHotSpotCreate(main_wnd, 9, 0, default_off_text, default_on_text, 490, setdfty, 300, 15, UIF_CENTER);
        } else {
          bypass_chat_curr_val = 1;
          DLLDatabaseWriteInt("BypassChat", bypass_chat_curr_val);
          snprintf(fmt_textstr, sizeof(fmt_textstr), TXT_PXO_MAKEGAMEDEFAULT, 29);
          default_on_text = DLLCreateNewUITextItem(fmt_textstr, UICOL_HOTSPOT_HI);
          snprintf(fmt_textstr, sizeof(fmt_textstr), TXT_PXO_MAKEGAMEDEFAULT, 29);
          default_off_text = DLLCreateNewUITextItem(fmt_textstr, UICOL_HOTSPOT_LO);
          set_dft_hs =
              DLLHotSpotCreate(main_wnd, 9, 0, default_off_text, default_on_text, 490, setdfty, 300, 15, UIF_CENTER);
        }
      }
      break;
    case GET_INFO_ID: {
      if (*DLLNum_network_games_known) {
        int gameno;
        gameno = DLLListGetSelectedIndex(game_list);
        int gameid = GetGameByLBNo(gameno);
        gameno = gameid;
        if (gameid == -1)
          break;
        DLLmprintf(0, "Selected item is %s\n", DLLNetwork_games[gameno].name);
        DLLShowNetgameInfo(&DLLNetwork_games[gameno]);
      }
    } break;

    case SORT_GAMENAME: {
      DLLmprintf(0, "Sorting by game name.\n");
      invert_sort_gamename = !invert_sort_gamename;
      ResortGameList(game_list, res, invert_sort_gamename);
    } break;
    case SORT_GAMETYPE: {
      DLLmprintf(0, "Sorting by game type.\n");
      invert_sort_gametype = !invert_sort_gametype;
      ResortGameList(game_list, res, invert_sort_gametype);
    } break;
    case SORT_MISSION: {
      DLLmprintf(0, "Sorting by mission.\n");
      invert_sort_mission = !invert_sort_mission;
      ResortGameList(game_list, res, invert_sort_mission);
    } break;
    case SORT_LEVEL: {
      DLLmprintf(0, "Sorting by level.\n");
      invert_sort_levels = !invert_sort_levels;
      ResortGameList(game_list, res, invert_sort_levels);
    } break;
    case SORT_PLAYERS: {
      DLLmprintf(0, "Sorting by players.\n");
      invert_sort_players = !invert_sort_players;
      ResortGameList(game_list, res, invert_sort_players);
    } break;
    case SORT_PING: {
      DLLmprintf(0, "Sorting by ping.\n");
      invert_sort_ping = !invert_sort_ping;
      ResortGameList(game_list, res, invert_sort_ping);
    } break;
    }
  }
  DLLNewUIWindowDestroy(main_wnd);

  *DLLNewUIWindow_alpha = oldalpha;

  // Look for items that we need to remove
  for (i = 0; i < MAX_GAMELIST_ITEMS; i++) {
    if (PXOGamelist[i].used) {
      DLLRemoveUITextItem(PXOGamelist[i].ti);
      PXOGamelist[i].used = false;
    }
  }

  /*
  for(a=0;a<MAX_NET_GAMES;a++)
          if(net_game_txt_items[a])
                  DLLRemoveUITextItem(net_game_txt_items[a]);
  */

  // Clean up
  DLLDeleteUIItem(main_wnd);
  DLLDeleteUIItem(game_list);
  //	DLLDeleteUIItem(game_head);
  DLLDeleteUIItem(exit_hs);
  DLLDeleteUIItem(join_hs);
  DLLDeleteUIItem(start_hs);
  DLLDeleteUIItem(screen_header);
  DLLDeleteUIItem(set_dft_hs);
  DLLDeleteUIItem(return_hs);
  DLLDeleteUIItem(info_hs);
  DLLDeleteUIItem(gname_hs);
  DLLDeleteUIItem(gtype_hs);
  DLLDeleteUIItem(msn_hs);
  DLLDeleteUIItem(lvl_hs);
  DLLDeleteUIItem(players_hs);
  DLLDeleteUIItem(ping_hs);

  DLLRemoveUITextItem(info_on_text);
  DLLRemoveUITextItem(info_off_text);
  DLLRemoveUITextItem(game_hdr_text);
  DLLRemoveUITextItem(return_text_on);
  DLLRemoveUITextItem(return_text_off);
  DLLRemoveUITextItem(game_head_text);
  DLLRemoveUITextItem(exit_on_text);
  DLLRemoveUITextItem(exit_off_text);
  DLLRemoveUITextItem(join_on_text);
  DLLRemoveUITextItem(join_off_text);
  DLLRemoveUITextItem(start_on_text);
  DLLRemoveUITextItem(start_off_text);
  DLLRemoveUITextItem(default_on_text);
  DLLRemoveUITextItem(default_off_text);

  DLLRemoveUITextItem(gname_on_text);
  DLLRemoveUITextItem(gname_off_text);
  DLLRemoveUITextItem(gtype_on_text);
  DLLRemoveUITextItem(gtype_off_text);
  DLLRemoveUITextItem(msn_on_text);
  DLLRemoveUITextItem(msn_off_text);
  DLLRemoveUITextItem(lvl_on_text);
  DLLRemoveUITextItem(lvl_off_text);
  DLLRemoveUITextItem(plrs_on_text);
  DLLRemoveUITextItem(plrs_off_text);
  DLLRemoveUITextItem(ping_on_text);
  DLLRemoveUITextItem(ping_off_text);

  if (hardexit)
    return -1;

  if (!ret && !ChatStarted && Bypass_chat) {
    ChatStarted = 1;
    ret = MainMultiplayerMenu();
  }
  return ret;
}

// This is just a function that does some debugging
void CheckPXOForAnomalies() {
  int i, j;
  for (i = 0; i < MAX_NET_PLAYERS; i++) {
    if (!(DLLMNetPlayers[i].flags & NPF_CONNECTED))
      continue;
    for (j = 0; j < MAX_NET_PLAYERS; j++) {
      if (!(DLLMNetPlayers[j].flags & NPF_CONNECTED))
        continue;
      if (i == j)
        continue;
      if (stricmp(DLLMPlayers[i].tracker_id, DLLMPlayers[j].tracker_id) == 0) {
        // Ok, what we have here is multiple users with the same tracker ID.
        // This is bad. It could be user error, but it could be something worse.
        FILE *errfile;
        char errfilepath[_MAX_PATH];
        DLLddio_MakePath(errfilepath, DLLLocalD3Dir, "pxo.err", NULL);
        errfile = fopen(errfilepath, "at");
        if (errfile) {
          fprintf(errfile, "Dup TID: %s & %s / %s\n", DLLMPlayers[j].callsign, DLLMPlayers[i].callsign,
                  DLLMPlayers[i].tracker_id);
          fclose(errfile);
        }
      }
    }
  }
}

#define MT_DATA_UPDATE_INTERVAL 10 // 30 seconds
void DoMTFrame() {
  int i;
  int rcode;
  IdleGameTracker();
  PollPTrackNet();
  // Periodically update the master tracker's info.
  if ((DLLtimer_GetTime() - LastTrackerDataUpdate) > MT_DATA_UPDATE_INTERVAL) {
    UpdateGameData(&DLLD3_tracker_info);
    LastTrackerDataUpdate = DLLtimer_GetTime();
  }

  if (DLLNetgame->flags & NF_TRACK_RANK) {
    // Loop through all DLLMNetPlayers looking to see if we need to send or receive
    if (MTWritingPilot != -1) {
      // We are already sending a pilot
      rcode = SendD3PilotData(nullptr);
      if (rcode != 0) {
        if (rcode == 1) {
          // Copy data from the DLLMTPilotinfo[MTReadingPilot] struct here
          DLLMNetPlayers[MTWritingPilot].flags &= ~NPF_MT_WRITING_PILOT;
          DLLmprintf(0, "Pilot data wrote to the Mastertracker for Player[%d] %s (tid=%s).\n", MTWritingPilot,
                     DLLMTPilotinfo[MTWritingPilot].pilot_name, DLLMTPilotinfo[MTWritingPilot].tracker_id);
          MTWritingPilot = -1;

        } else {
          DLLMNetPlayers[MTWritingPilot].flags &= ~NPF_MT_WRITING_PILOT;
          DLLmprintf(0, "Pilot write to the mastertracker failed. Error code %d.\n", rcode);
          MTWritingPilot = -1;
        }
      }
    } else {
      // See if se need to look for another
      for (i = 0; i < MAX_NET_PLAYERS; i++) {

        if (DLLMNetPlayers[i].flags & NPF_MT_WRITING_PILOT) {
          if ((!(DLLMNetPlayers[i].flags & NPF_MT_READING_PILOT)) &&
              (DLLMNetPlayers[i].flags & NPF_MT_HAS_PILOT_DATA)) {
            strcpy(DLLMTPilotinfo[i].tracker_id, DLLMPlayers[i].tracker_id);
            strcpy(DLLMTPilotinfo[i].pilot_name, DLLMPlayers[i].callsign);
            DLLMTPilotinfo[i].kills = DLLMPlayers[i].kills;
            DLLMTPilotinfo[i].deaths = DLLMPlayers[i].deaths;
            DLLMTPilotinfo[i].suicides = DLLMPlayers[i].suicides;
            DLLMTPilotinfo[i].rank = (DLLMPlayers[i].rank * 65536.0);
            DLLmprintf(0, "Sending pilot %d rank of %f\n", i, DLLMTPilotinfo[i].rank / 65536.0);

            DLLMTPilotinfo[i].lateral_thrust = DLLMPlayers[i].lateral_thrust;
            DLLMTPilotinfo[i].rotational_thrust = DLLMPlayers[i].rotational_thrust;
            DLLMTPilotinfo[i].online_time += DLLtimer_GetTime() - DLLMPlayers[i].time_in_game;
            DLLMTPilotinfo[i].sliding_pct = 0;                // FIXME
            DLLMPlayers[i].time_in_game = DLLtimer_GetTime(); // when we write this data multiple times we need this

            DLLmprintf(0, "Sending User info to the Mastertracker for Player[%d] %s (tid=%s).\n", i,
                       DLLMTPilotinfo[i].pilot_name, DLLMTPilotinfo[i].tracker_id);
            SendD3PilotData(&DLLMTPilotinfo[i]);

            MTWritingPilot = i;
            i = MAX_NET_PLAYERS + 1;
            break;
          } else {
            // If we never read this pilot's stats, we really don't care what they were.
            DLLMNetPlayers[i].flags &= ~NPF_MT_READING_PILOT;
            DLLMNetPlayers[i].flags &= ~NPF_MT_WRITING_PILOT;
            DLLmprintf(0, "Didn't write Mastertracker stats for %s because we never received any from the tracker!\n",
                       DLLMPlayers[i].callsign);
          }
        }
      }
    }
    // Don't want to read and write at the same time at this point
    if (MTWritingPilot == -1) {
      if (MTReadingPilot != -1) {
        // We are already waiting on a pilot
        rcode = GetD3PilotData(nullptr, nullptr, nullptr);
        if (rcode != 0) {
          if (rcode == 1) {
            DLLMNetPlayers[MTReadingPilot].flags &= ~NPF_MT_READING_PILOT;
            // Copy data into the DLLMTPilotinfo[MTReadingPilot] struct here
            DLLMPlayers[MTReadingPilot].kills = DLLMTPilotinfo[MTReadingPilot].kills;
            DLLMPlayers[MTReadingPilot].deaths = DLLMTPilotinfo[MTReadingPilot].deaths;
            DLLMPlayers[MTReadingPilot].suicides = DLLMTPilotinfo[MTReadingPilot].suicides;
            DLLMPlayers[MTReadingPilot].rank = DLLMTPilotinfo[MTReadingPilot].rank / 65536.0;
            DLLmprintf(0, "Read pilot %s rank of %f\n", DLLMPlayers[MTReadingPilot].callsign,
                       DLLMPlayers[MTReadingPilot].rank);
            DLLMPlayers[MTReadingPilot].lateral_thrust = DLLMTPilotinfo[MTReadingPilot].lateral_thrust;
            DLLMPlayers[MTReadingPilot].rotational_thrust = DLLMTPilotinfo[MTReadingPilot].rotational_thrust;
            // DLLMPlayers[MTReadingPilot].time_in_game = DLLMTPilotinfo[MTReadingPilot].online_time;
            //  Something = DLLMTPilotinfo[i].sliding_pct;//FIXME

            DLLMNetPlayers[MTReadingPilot].flags |= NPF_MT_HAS_PILOT_DATA;
            DLLmprintf(0, "Pilot data received from the Mastertracker for Player[%d] %s (tid=%s).\n", MTReadingPilot,
                       DLLMTPilotinfo[MTReadingPilot].pilot_name, DLLMTPilotinfo[MTReadingPilot].tracker_id);
            MTReadingPilot = -1;
          } else {
            // DLLMNetPlayers[MTReadingPilot].flags &= ~NPF_MT_READING_PILOT;
            DLLmprintf(0, "Pilot read from mastertracker failed. Error code %d.\n", rcode);
            MTReadingPilot = -1;
          }
        }
      } else {
        // See if se need to look for another
        for (i = 0; i < MAX_NET_PLAYERS; i++) {
          if (DLLMNetPlayers[i].flags & NPF_MT_READING_PILOT) {
            MTReadingPilot = i;
            DLLmprintf(0, "Requesting User info from the Mastertracker for Player[%d] %s (tid=%s).\n", i,
                       DLLMTPilotinfo[i].pilot_name, DLLMTPilotinfo[i].tracker_id);
            GetD3PilotData(&DLLMTPilotinfo[i], DLLMPlayers[i].callsign, DLLMPlayers[i].tracker_id);
            CheckPXOForAnomalies();
            break;
          }
        }
      }
    }
  }
}

void DoMTGameOver(void) {
  int i;

  DLLShowProgressScreen(TXT_PXO_WRITINGGAMESTATS, nullptr);

  if (DLLNetgame->local_role != LR_SERVER) {
    return;
  }
  // Send all player info to the mastertracker
  for (i = 0; i < MAX_NET_PLAYERS; i++) {
    if ((DLLMNetPlayers[i].flags & NPF_CONNECTED) || (DLLMNetPlayers[i].flags & NPF_MT_WRITING_PILOT)) {
      if (!(DLLMNetPlayers[i].flags & NPF_MT_READING_PILOT)) {
        if (DLLMNetPlayers[i].flags & NPF_MT_HAS_PILOT_DATA) // Security will do this for us
        {
          strcpy(DLLMTPilotinfo[i].tracker_id, DLLMPlayers[i].tracker_id);
          strcpy(DLLMTPilotinfo[i].pilot_name, DLLMPlayers[i].callsign);
          DLLMTPilotinfo[i].kills = DLLMPlayers[i].kills;
          DLLMTPilotinfo[i].deaths = DLLMPlayers[i].deaths;
          DLLMTPilotinfo[i].suicides = DLLMPlayers[i].suicides;
          DLLMTPilotinfo[i].rank = DLLMPlayers[i].rank * 65536.0;
          DLLMTPilotinfo[i].lateral_thrust = DLLMPlayers[i].lateral_thrust;
          DLLMTPilotinfo[i].rotational_thrust = DLLMPlayers[i].rotational_thrust;
          DLLMTPilotinfo[i].online_time += DLLtimer_GetTime() - DLLMPlayers[i].time_in_game;
          DLLMTPilotinfo[i].sliding_pct = 0; // FIXME
          DLLmprintf(0, "Sending User info to the Mastertracker for Player[%d] %s (tid=%s).\n", i,
                     DLLMTPilotinfo[i].pilot_name, DLLMTPilotinfo[i].tracker_id);
          DLLmprintf(0, "Sending pilot %d rank of %f\n", i, DLLMTPilotinfo[i].rank / 65536.0);
          SendD3PilotData(&DLLMTPilotinfo[i]);
          while (SendD3PilotData(nullptr) == 0) {
            DLLDescentDefer();
          }
        }
      }
    }
  }
  DLLShowProgressScreen(TXT_PXO_SENDINGGAMEOVER, nullptr);
  while (!SendGameOver())
    DLLDescentDefer();
}

int MTVersionCheck() {
#ifdef WIN32
  int rcode;
  InetGetFile *inetfile;
  char sznewdll[_MAX_PATH], szolddll[_MAX_PATH], szbakdll[_MAX_PATH];
  char fulldllpath[_MAX_PATH * 2];
  // char dllpath[_MAX_PATH];
  DLLAVInit = NULL;
  DLLAVCall = NULL;
  DLLAVClose = NULL;
  DLLAVGetVersion = NULL;
  DLLRunCheck = NULL;
  // Start by getting the current MT version and see if a newer is needed
  // Load the DLL and get it's version

  // Specify the correct path
  DLLddio_MakePath(fulldllpath, DLLLocalD3Dir, "mtav.dll", NULL);
  if (!DLLmod_LoadModule(&MTAVDLLHandle, fulldllpath, MODF_LAZY)) {
    DLLmprintf(0, "Unable to load Mastertracker Auto version update DLL (mtav.dll)\n");
    // Try restoring a backup of the DLL
    DLLddio_MakePath(szolddll, DLLLocalD3Dir, "mtav.dll", NULL);
    DLLddio_MakePath(szbakdll, DLLLocalD3Dir, "mtav.bak", NULL);
    CopyFile(szbakdll, szolddll, FALSE);
    return 0;
  }
  DLLAVInit = (DLLAVInit_fp *)DLLmod_GetSymbol(&MTAVDLLHandle, "DLLAVInit", 4);
  if (!DLLAVInit) {
    DLLmprintf(0, "Unable to Find DLLAVInit() function in mtav.dll\n");
    DLLmod_FreeModule(&MTAVDLLHandle);
    // Try restoring a backup of the DLL
    DLLddio_MakePath(szolddll, DLLLocalD3Dir, "mtav.dll", NULL);
    DLLddio_MakePath(szbakdll, DLLLocalD3Dir, "mtav.bak", NULL);
    CopyFile(szbakdll, szolddll, FALSE);
    return 0;
  }
  DLLAVGetVersion = (DLLAVGetVersion_fp *)DLLmod_GetSymbol(&MTAVDLLHandle, "DLLAVGetVersion", 4);
  if (!DLLAVGetVersion) {
    DLLmprintf(0, "Unable to Find DLLAVGetVersion() function in mtav.dll\n");
    DLLmod_FreeModule(&MTAVDLLHandle);
    // Try restoring a backup of the DLL
    DLLddio_MakePath(szolddll, DLLLocalD3Dir, "mtav.dll", NULL);
    DLLddio_MakePath(szbakdll, DLLLocalD3Dir, "mtav.bak", NULL);
    CopyFile(szbakdll, szolddll, FALSE);
    return 0;
  }
  DLLRunCheck = (DLLRunCheck_fp *)DLLmod_GetSymbol(&MTAVDLLHandle, "DLLRunCheck", 4);
  if (!DLLRunCheck) {
    DLLmprintf(0, "Unable to Find DLLRunCheck() function in mtav.dll\n");
    DLLmod_FreeModule(&MTAVDLLHandle);
    // Try restoring a backup of the DLL
    DLLddio_MakePath(szolddll, DLLLocalD3Dir, "mtav.dll", NULL);
    DLLddio_MakePath(szbakdll, DLLLocalD3Dir, "mtav.bak", NULL);
    CopyFile(szbakdll, szolddll, FALSE);
    return 0;
  }
  uint32_t mtver;
  DLLAVGetVersion((int *)&mtver);
  if (MTAVersionCheck(mtver, MTUpdateURL)) {
    DLLmprintf(0, "VersionCheck() returned an unexpected return code!\n");
    DLLmod_FreeModule(&MTAVDLLHandle);
    return 0;
  }
  DLLmprintf(0, "Getting Version # from Mastertracker.\n");
  do {
    //
    rcode = MTAVersionCheck(0, NULL);
  } while (rcode == 0);

  if (rcode == -2) {
    // Don't try anymore... it timed out.
    Login_aborted = true;
  }
  if (rcode == 1) {
    if (MTUpdateURL[0]) {
      // We need to get a new DLL
      DLLmprintf(0, "Mastertracker says we need a new version, which is at %s.\n", MTUpdateURL);
      sprintf(sznewdll, "%s\\newmtav.dll", DLLLocalD3Dir);
      DLLddio_MakePath(sznewdll, DLLLocalD3Dir, "newmtav.dll", NULL);
      inetfile = new InetGetFile(MTUpdateURL, sznewdll);
      while (1) {
        DLLPollUI();
        if (inetfile->IsFileError()) {
          // Error here
          DLLmprintf(0, "Mastertracker update DLL not received. Error code: %d.\n", inetfile->GetErrorCode());
          DLLmod_FreeModule(&MTAVDLLHandle);
          return 0;
        }
        if (inetfile->IsFileReceived()) {
          DLLmprintf(0, "Mastertracker update DLL received.\n");
          DLLmod_FreeModule(&MTAVDLLHandle);
          DLLddio_MakePath(szolddll, DLLLocalD3Dir, "mtav.dll", NULL);
          DLLddio_MakePath(szbakdll, DLLLocalD3Dir, "mtav.bak", NULL);

          // We have the file, now backup & copy it and try to reload.
          CopyFile(szolddll, szbakdll, FALSE);
          CopyFile(sznewdll, szolddll, FALSE);
          return 0;
        }
      };
    } else {
      DLLmprintf(0, "Mastertracker says we are up to date\n");
      // Here is where we call into the DLL so it can do it's magic
      DLLAVInit(0);
      DLLmod_FreeModule(&MTAVDLLHandle);
      return 1;
    }
  } else {
    DLLmprintf(0, "Mastertracker timeout while getting version\n");
    DLLmod_FreeModule(&MTAVDLLHandle);
    return 0;
  }
#endif
  return 1;
}

int JoinNewLobby(const char *lobby) {
  int rcode;
  const char *p;
  DLLmprintf(0, "Entering new lobby");
  void *title_text = DLLCreateNewUITextItem(TXT_PXO_ENTERINGLOBBY, UICOL_WINDOW_TITLE);

  void *cancel_on_text = DLLCreateNewUITextItem(TXT_PXO_CANCEL, UICOL_HOTSPOT_HI);
  void *cancel_off_text = DLLCreateNewUITextItem(TXT_PXO_CANCEL, UICOL_HOTSPOT_LO);

  void *main_wnd = DLLNewUIGameWindowCreate(0, 256, 128, 128, UIF_CENTER | UIF_PROCESS_ALL | NUWF_TITLEMED);
  void *title = DLLTextCreate(main_wnd, title_text, 0, 7, UIF_CENTER);
  void *cancel_hs =
      DLLHotSpotCreate(main_wnd, 5, KEY_ESC, cancel_off_text, cancel_on_text, 20, 100, 70, 15, UIF_CENTER);
  DLLNewUIGameWindowOpen(main_wnd);
  do {
    rcode = SetNewChatChannel(lobby);
    p = GetChatText();
    if (p && pconsole) {
      DLLUIConsoleGadgetputs(pconsole, p);
      DLLUIConsoleGadgetputs(pconsole, "\x0a\x0d");
    }
  } while (rcode == 0);

  DLLNewUIGameWindowClose(main_wnd);
  DLLNewUIGameWindowDestroy(main_wnd);

  if (rcode == 1) {
    strcpy(DLLPXO_hosted_lobby_name, lobby);
    return 1;
  } else {
    DLLmprintf(0, "Unable to join lobby: %d\n", rcode);
    char txtmessage[200];
    char cleanlobby[50];
    memset(cleanlobby, 0, 29);
    strcpy(cleanlobby, lobby + 1);
    for (int l = 0; l < 18; l++) {
      if (cleanlobby[l] == '_')
        cleanlobby[l] = ' ';
    }
    snprintf(txtmessage, sizeof(txtmessage), TXT_PXO_CANTJOINLOBBY, cleanlobby);
    DLLDoMessageBox(TXT_PXO_MASTERTRACKER, txtmessage, MSGBOX_OK, UICOL_WINDOW_TITLE, UICOL_TEXT_NORMAL);
    return 0;
  }

  DLLDeleteUIItem(main_wnd);
  DLLDeleteUIItem(title);
  DLLDeleteUIItem(cancel_hs);

  DLLRemoveUITextItem(title_text);
  DLLRemoveUITextItem(cancel_on_text);
  DLLRemoveUITextItem(cancel_off_text);
}

const char *SendWhisper(const char *name) {

  int exit_menu = 0;
  const char *p;
  char message[MAX_CHAT_SEND_LEN];
  char pilot_name[MAX_CHAT_SEND_LEN];
  static char fmt_msg[MAX_CHAT_SEND_LEN * 2];
  void *title_text = DLLCreateNewUITextItem(TXT_PXO_PRIVATEMESSAGE, UICOL_WINDOW_TITLE);

  void *cancel_on_text = DLLCreateNewUITextItem(TXT_PXO_CANCEL, UICOL_HOTSPOT_HI);
  void *cancel_off_text = DLLCreateNewUITextItem(TXT_PXO_CANCEL, UICOL_HOTSPOT_LO);
  void *send_on_text = DLLCreateNewUITextItem(TXT_PXO_SEND, UICOL_HOTSPOT_HI);
  void *send_off_text = DLLCreateNewUITextItem(TXT_PXO_SEND, UICOL_HOTSPOT_LO);

  void *pilot_text = DLLCreateNewUITextItem(TXT_PXO_PILOTNAME, UICOL_TEXT_NORMAL);
  void *message_text = DLLCreateNewUITextItem(TXT_PXO_MESSAGE, UICOL_TEXT_NORMAL);

  void *main_wnd = DLLNewUIGameWindowCreate(0, 0, 384, 256, UIF_PROCESS_ALL | UIF_CENTER | NUWF_TITLEMED);

  void *title = DLLTextCreate(main_wnd, title_text, 0, 7, UIF_CENTER);
  void *pilot = DLLTextCreate(main_wnd, pilot_text, 50, 55, 0);
  void *message_t = DLLTextCreate(main_wnd, message_text, 50, 110, 0);
  void *user_edit = DLLEditCreate(main_wnd, 10, 50, 75, 130, 15, 0);
  void *msg_edit = DLLEditCreate(main_wnd, 3, 50, 130, 200, 15, 0);

  // HotSpotCreate(int item,int parentitem, int id, int key, int txtitemoff, int txtitemon, int x, int y, int w, int h,
  // int flags,int winnum)
  void *cancel_hs =
      DLLHotSpotCreate(main_wnd, UID_CANCEL, KEY_ESC, cancel_on_text, cancel_off_text, 130, 256 - 80, 60, 20, 0);
  void *send_hs = DLLHotSpotCreate(main_wnd, UID_OK, KEY_ENTER, send_on_text, send_off_text, 60, 256 - 80, 60, 20, 0);
  DLLNewUIGameWindowOpen(main_wnd);
  // DLLNewUIWindowSetFocusOnEditGadget(msg_edit,main_wnd);
  DLLEditSetText(user_edit, name);
  while (!exit_menu) {
    int res;

    res = DLLDoUI();

    // handle all UI results.

    switch (res) {

    case 3:
    case UID_OK:
      DLLEditGetText(user_edit, pilot_name, MAX_CHAT_SEND_LEN);
      DLLEditGetText(msg_edit, message, MAX_CHAT_SEND_LEN);
      snprintf(fmt_msg, sizeof(fmt_msg), "/msg %s %s", pilot_name, message);
      p = SendChatString(fmt_msg);
      if (p && pconsole) {
        DLLUIConsoleGadgetputs(pconsole, p);
        DLLUIConsoleGadgetputs(pconsole, "\x0a\x0d");
      }
      exit_menu = 1;
      break;
    case UID_CANCEL:
      exit_menu = 1;
      break;
    }
  }

  DLLNewUIGameWindowClose(main_wnd);
  DLLNewUIGameWindowDestroy(main_wnd);

  // Clean up
  DLLRemoveUITextItem(title_text);
  DLLRemoveUITextItem(cancel_on_text);
  DLLRemoveUITextItem(cancel_off_text);
  DLLRemoveUITextItem(send_on_text);
  DLLRemoveUITextItem(send_off_text);
  DLLRemoveUITextItem(pilot_text);
  DLLRemoveUITextItem(message_text);

  DLLDeleteUIItem(main_wnd);
  DLLDeleteUIItem(title);
  DLLDeleteUIItem(pilot);
  DLLDeleteUIItem(message_t);
  DLLDeleteUIItem(user_edit);
  DLLDeleteUIItem(msg_edit);
  DLLDeleteUIItem(cancel_hs);
  DLLDeleteUIItem(send_hs);

  return "";
}

int JoinPrivateLobby() {
  int exit_menu = 0;
  int ret = 0;
  char message[MAX_CHAT_SEND_LEN];
  char priv_channel[MAX_CHAT_SEND_LEN];

  void *title_text = DLLCreateNewUITextItem(TXT_PXO_JOINPRIV, UICOL_WINDOW_TITLE);

  void *cancel_on_text = DLLCreateNewUITextItem(TXT_PXO_CANCEL, UICOL_HOTSPOT_HI);
  void *cancel_off_text = DLLCreateNewUITextItem(TXT_PXO_CANCEL, UICOL_HOTSPOT_LO);
  void *join_on_text = DLLCreateNewUITextItem(TXT_PXO_JOIN, UICOL_HOTSPOT_HI);
  void *join_off_text = DLLCreateNewUITextItem(TXT_PXO_JOIN, UICOL_HOTSPOT_LO);

  void *channel_text = DLLCreateNewUITextItem(TXT_PXO_CHANNELNAME, UICOL_TEXT_NORMAL);

  void *main_wnd = DLLNewUIGameWindowCreate(0, 0, 256, 256, UIF_PROCESS_ALL | UIF_CENTER | NUWF_TITLELARGE);

  void *title = DLLTextCreate(main_wnd, title_text, 0, 7, UIF_CENTER);
  void *channel_t = DLLTextCreate(main_wnd, channel_text, 50, 95, UIF_CENTER);
  void *chan_edit = DLLEditCreate(main_wnd, 3, 50, 115, 130, 15, UIF_CENTER);

  // DLLNewUIWindowSetFocusOnEditGadget(chan_edit,main_wnd);
  // HotSpotCreate(int item,int parentitem, int id, int key, int txtitemoff, int txtitemon, int x, int y, int w, int h,
  // int flags,int winnum)
  void *cancel_hs =
      DLLHotSpotCreate(main_wnd, UID_CANCEL, KEY_ESC, cancel_on_text, cancel_off_text, 130, 256 - 80, 60, 20, 0);
  void *join_hs = DLLHotSpotCreate(main_wnd, UID_OK, KEY_ENTER, join_on_text, join_off_text, 60, 256 - 80, 60, 20, 0);
  DLLNewUIGameWindowOpen(main_wnd);
  while (!exit_menu) {
    int res;

    res = DLLDoUI();

    // handle all UI results.

    switch (res) {
    case 3:
    case UID_OK: {
      DLLEditGetText(chan_edit, priv_channel, MAX_CHAT_SEND_LEN);
      for (uint32_t i = 0; i < strlen(priv_channel); i++) {
        if (priv_channel[i] == ' ') {
          priv_channel[i] = '_';
        }
      }
      snprintf(message, sizeof(message), "+%s", priv_channel);
      ret = JoinNewLobby(message);
      exit_menu = 1;
      if (ret) {
        char txtmessage[200];
        char cleanlobby[50];
        memset(cleanlobby, 0, 29);
        strcpy(cleanlobby, message + 1);
        for (int l = 0; l < 18; l++) {
          if (cleanlobby[l] == '_')
            cleanlobby[l] = ' ';
        }
        snprintf(txtmessage, sizeof(txtmessage), TXT_PXO_INNEWLOBBY, cleanlobby);
        DLLDoMessageBox(TXT_PXO_MASTERTRACKER, txtmessage, MSGBOX_OK, UICOL_WINDOW_TITLE, UICOL_TEXT_NORMAL);
        *DLLNum_network_games_known = 0;
      }
    } break;
    case UID_CANCEL:
      exit_menu = 1;
      break;
    }
  }

  DLLNewUIGameWindowClose(main_wnd);
  DLLNewUIGameWindowDestroy(main_wnd);

  DLLRemoveUITextItem(title_text);
  DLLRemoveUITextItem(cancel_on_text);
  DLLRemoveUITextItem(cancel_off_text);
  DLLRemoveUITextItem(join_on_text);
  DLLRemoveUITextItem(join_off_text);
  DLLRemoveUITextItem(channel_text);

  DLLDeleteUIItem(main_wnd);
  DLLDeleteUIItem(title);
  DLLDeleteUIItem(channel_t);
  DLLDeleteUIItem(chan_edit);
  DLLDeleteUIItem(cancel_hs);
  DLLDeleteUIItem(join_hs);
  return ret;
}

int FindPilot() {

  int exit_menu = 0;
  const char *p;
  char message[MAX_CHAT_SEND_LEN];
  char pilot_name[MAX_CHAT_SEND_LEN];
  static char fmt_msg[MAX_CHAT_SEND_LEN * 2];
  void *title_text = DLLCreateNewUITextItem(TXT_PXO_FINDPILOT, UICOL_WINDOW_TITLE);

  void *cancel_on_text = DLLCreateNewUITextItem(TXT_PXO_CANCEL, UICOL_HOTSPOT_HI);
  void *cancel_off_text = DLLCreateNewUITextItem(TXT_PXO_CANCEL, UICOL_HOTSPOT_LO);
  void *search_on_text = DLLCreateNewUITextItem(TXT_PXO_SEARCH, UICOL_HOTSPOT_HI);
  void *search_off_text = DLLCreateNewUITextItem(TXT_PXO_SEARCH, UICOL_HOTSPOT_LO);

  void *pilot_text = DLLCreateNewUITextItem(TXT_PXO_PILOTNAME, UICOL_TEXT_NORMAL);

  void *main_wnd = DLLNewUIGameWindowCreate(0, 0, 256, 256, UIF_PROCESS_ALL | UIF_CENTER | NUWF_TITLEMED);

  void *title_t = DLLTextCreate(main_wnd, title_text, 0, 7, UIF_CENTER);
  void *pilot_t = DLLTextCreate(main_wnd, pilot_text, 50, 95, UIF_CENTER);
  void *pilot_edit = DLLEditCreate(main_wnd, 3, 50, 115, 130, 15, UIF_CENTER);

  // DLLNewUIWindowSetFocusOnEditGadget(pilot_edit,main_wnd);
  // HotSpotCreate(int item,int parentitem, int id, int key, int txtitemoff, int txtitemon, int x, int y, int w, int h,
  // int flags,int winnum)
  void *cancel_hs =
      DLLHotSpotCreate(main_wnd, UID_CANCEL, KEY_ESC, cancel_on_text, cancel_off_text, 130, 256 - 80, 60, 20, 0);
  void *search_hs =
      DLLHotSpotCreate(main_wnd, UID_OK, KEY_ENTER, search_on_text, search_off_text, 60, 256 - 80, 60, 20, 0);
  DLLNewUIGameWindowOpen(main_wnd);
  while (!exit_menu) {
    int res;

    res = DLLDoUI();

    // handle all UI results.

    switch (res) {
    case 3:
    case UID_OK: {
      DLLEditGetText(pilot_edit, pilot_name, MAX_CHAT_SEND_LEN);
      DLLCreateSplashScreen(TXT_PXO_SEARCHINGPILOT, 1);
      p = GetChannelByUser(pilot_name);
      while (p == nullptr) {
        int sres = DLLPollUI();
        // Detect if cancel is hit
        if (sres == 99) {
          p = nullptr;
          // Cancel the lookup
          GetChannelByUser((char *)-1);
          break;
        }
        DLLDescentDefer();
        p = GetChatText();
        if (p && pconsole) {
          DLLUIConsoleGadgetputs(pconsole, p);
          DLLUIConsoleGadgetputs(pconsole, "\x0a\x0d");
        }
        p = GetChannelByUser(pilot_name);
      }
      if ((p == nullptr) || (p == (char *)-1)) {
        exit_menu = 1;
        DLLCloseSplashScreen();
        break;
      }
      strcpy(message, p + 1);
      for (uint32_t i = 0; i < strlen(message); i++)
        if (message[i] == '_')
          message[i] = ' ';
      snprintf(fmt_msg, sizeof(fmt_msg), TXT_PXO_CANBEFOUNDIN, pilot_name, message);
      if (pconsole) {
        DLLUIConsoleGadgetputs(pconsole, fmt_msg);
        DLLUIConsoleGadgetputs(pconsole, "\x0a\x0d");
      }
      exit_menu = 1;
      DLLCloseSplashScreen();
      break;
    }
    case UID_CANCEL:
      exit_menu = 1;
      break;
    }
  }

  DLLNewUIGameWindowClose(main_wnd);
  DLLNewUIGameWindowDestroy(main_wnd);

  DLLRemoveUITextItem(title_text);
  DLLRemoveUITextItem(cancel_on_text);
  DLLRemoveUITextItem(cancel_off_text);
  DLLRemoveUITextItem(search_on_text);
  DLLRemoveUITextItem(search_off_text);
  DLLRemoveUITextItem(pilot_text);

  DLLDeleteUIItem(main_wnd);
  DLLDeleteUIItem(title_t);
  DLLDeleteUIItem(pilot_t);
  DLLDeleteUIItem(pilot_edit);
  DLLDeleteUIItem(cancel_hs);
  DLLDeleteUIItem(search_hs);

  return 1;
}

const char *GetRankString(float ranking) {
  int val = 0;

  if (ranking >= 0 && ranking < 600)
    val = 0;
  else if (ranking >= 600 && ranking < 900)
    val = 1;
  else if (ranking >= 900 && ranking < 1200)
    val = 2;
  else if (ranking >= 1200 && ranking < 1500)
    val = 3;
  else if (ranking >= 1500 && ranking < 1800)
    val = 4;
  else if (ranking >= 1800 && ranking < 2100)
    val = 5;
  else if (ranking >= 2100 && ranking < 2400)
    val = 6;
  else if (ranking >= 2400 && ranking < 2600)
    val = 7;
  else if (ranking >= 2600 && ranking < 3000)
    val = 8;
  else if (ranking >= 3000)
    val = 9;
  return TXT(TXT_RANKING0 + val);
}

int GetNextRank(float ranking) {
  int val = 0;

  if (ranking >= 0 && ranking < 600)
    val = 600;
  else if (ranking >= 600 && ranking < 900)
    val = 900;
  else if (ranking >= 900 && ranking < 1200)
    val = 1200;
  else if (ranking >= 1200 && ranking < 1500)
    val = 1500;
  else if (ranking >= 1500 && ranking < 1800)
    val = 1800;
  else if (ranking >= 1800 && ranking < 2100)
    val = 2100;
  else if (ranking >= 2100 && ranking < 2400)
    val = 2400;
  else if (ranking >= 2400 && ranking < 2600)
    val = 2600;
  else if (ranking >= 2600 && ranking < 3000)
    val = 3000;
  else if (ranking >= 3000)
    val = 3000;
  return val;
}

int GetPilotStats(const char *pilot) {
  int res;
  const char *p;
  char *tokp;
  char tid[MAX_CHAT_SEND_LEN];
  char real_pilot[MAX_CHAT_SEND_LEN];
  char tmp_text[MAX_CHAT_SEND_LEN];
  vmt_descent3_struct d3_pilot_info;

  void *eff_text;
  void *time_text;
  void *main_wnd;
  void *title_t;
  void *kill_t;
  void *death_t;
  void *suicide_t;
  void *eff_t;
  void *time_in_game_t;
  void *pilot_t;
  void *rank_t;

  void *title_text;
  void *pilot_name_text;
  void *close_on_text;
  void *close_off_text;
  void *kills_text;
  void *deaths_text;
  void *suicide_text;
  void *rank_text;

  DLLCreateSplashScreen(TXT_PXO_GETTINGPILOTSTAT, 1);
  // Cancel previously active lookups
  // GetD3PilotData((vmt_descent3_struct *)-1, NULL, NULL);
  GetD3PilotDataCancel();
  GetTrackerIdByUser((char *)-1);
  p = GetTrackerIdByUser(pilot);
  while (p == NULL) {
    res = DLLPollUI();
    DLLDescentDefer();
    p = GetChatText();
    if (p && pconsole) {
      DLLUIConsoleGadgetputs(pconsole, p);
      DLLUIConsoleGadgetputs(pconsole, "\x0a\x0d");
    }
    p = GetTrackerIdByUser(pilot);
    if (res == 99) {
      // cancel was hit
      // Cancel the look
      GetTrackerIdByUser((char *)-1);
      DLLCloseSplashScreen();
    }
  }
  if (p == (char *)-1) {
    DLLmprintf(0, "Timeout looking for user\n");
    DLLDoMessageBox(TXT_PXO_MASTERTRACKER, TXT_PXO_TIMEOUTMT, MSGBOX_OK, UICOL_WINDOW_TITLE, UICOL_TEXT_NORMAL);
    DLLCloseSplashScreen();
    return 0;
  }
  tokp = strchr((char *)p, ' ');
  if (tokp) {
    *tokp = '\0';
    tokp++;
    strcpy(tid, p);
    strcpy(real_pilot, tokp);
    DLLmprintf(0, "Requesting pilot info for %s %s\n", tid, real_pilot);
    memset(&d3_pilot_info, 0, sizeof(vmt_descent3_struct));
    GetD3PilotData(&d3_pilot_info, real_pilot, tid);
    int iresult = 0;
    while (iresult == 0) {
      iresult = GetD3PilotData(nullptr, nullptr, nullptr);
      res = DLLPollUI();
      if (res == 99) {
        // cancel was hit
        // GetD3PilotData((vmt_descent3_struct *)-1, NULL, NULL);
        GetD3PilotDataCancel();
        iresult = -1;
      }
      DLLDescentDefer();
      p = GetChatText();
      if (p && pconsole) {
        DLLUIConsoleGadgetputs(pconsole, p);
        DLLUIConsoleGadgetputs(pconsole, "\x0a\x0d");
      }
    }
    if (iresult == 1) {
      DLLmprintf(0, "Got pilot info for %s %s\n", tid, real_pilot);

      // Do rank thingy here.
      snprintf(tmp_text, sizeof(tmp_text), "Rank: %s (%d) Next Advance at %d",
               GetRankString(d3_pilot_info.rank / 65536), d3_pilot_info.rank / 65536,
               GetNextRank(d3_pilot_info.rank / 65536));
      rank_text = DLLCreateNewUITextItem(tmp_text, UICOL_TEXT_NORMAL);

      title_text = DLLCreateNewUITextItem(TXT_PXO_PILOTSTATS, UICOL_WINDOW_TITLE);

      pilot_name_text = DLLCreateNewUITextItem(real_pilot, UICOL_WINDOW_TITLE, DLL_BIG_BRIEFING_FONT);

      close_on_text = DLLCreateNewUITextItem(TXT_PXO_CLOSE, UICOL_HOTSPOT_HI);
      close_off_text = DLLCreateNewUITextItem(TXT_PXO_CLOSE, UICOL_HOTSPOT_LO);

      snprintf(tmp_text, sizeof(tmp_text), TXT_PXO_TOTALKILLS, d3_pilot_info.kills);
      kills_text = DLLCreateNewUITextItem(tmp_text, UICOL_TEXT_NORMAL);

      snprintf(tmp_text, sizeof(tmp_text), TXT_PXO_TOTALDEATHS, d3_pilot_info.deaths);
      deaths_text = DLLCreateNewUITextItem(tmp_text, UICOL_TEXT_NORMAL);

      snprintf(tmp_text, sizeof(tmp_text), TXT_PXO_SUICIDES, d3_pilot_info.suicides);
      suicide_text = DLLCreateNewUITextItem(tmp_text, UICOL_TEXT_NORMAL);

      int leff = 0;
      int cury;
      if (d3_pilot_info.kills && d3_pilot_info.deaths) {
        // leff = d3_pilot_info.kills/d3_pilot_info.deaths+d3_pilot_info.suicides+d3_pilot_info.kills;
        leff = (int)((float)((float)d3_pilot_info.kills / ((float)d3_pilot_info.deaths + (float)d3_pilot_info.kills +
                                                           (float)d3_pilot_info.suicides)) *
                     100.0);
      }

      snprintf(tmp_text, sizeof(tmp_text), TXT_PXO_EFFECIENCY, leff);
      eff_text = DLLCreateNewUITextItem(tmp_text, UICOL_TEXT_NORMAL);
      snprintf(tmp_text, sizeof(tmp_text), TXT_PXO_TIMEINGAME, d3_pilot_info.online_time / 60);
      time_text = DLLCreateNewUITextItem(tmp_text, UICOL_TEXT_NORMAL);

      main_wnd = DLLNewUIGameWindowCreate(0, 0, 384, 256, UIF_PROCESS_ALL | UIF_CENTER | NUWF_TITLEMED);

      title_t = DLLTextCreate(main_wnd, title_text, 0, 7, UIF_CENTER);
      cury = 30;
      pilot_t = DLLTextCreate(main_wnd, pilot_name_text, 0, cury, UIF_CENTER);
      cury += 30;

      rank_t = DLLTextCreate(main_wnd, rank_text, 0, cury, UIF_CENTER);
      cury += 20;
      kill_t = DLLTextCreate(main_wnd, kills_text, 0, cury, UIF_CENTER);
      cury += 20;
      death_t = DLLTextCreate(main_wnd, deaths_text, 0, cury, UIF_CENTER);
      cury += 20;
      suicide_t = DLLTextCreate(main_wnd, suicide_text, 0, cury, UIF_CENTER);
      cury += 20;
      eff_t = DLLTextCreate(main_wnd, eff_text, 0, cury, UIF_CENTER);
      cury += 20;
      time_in_game_t = DLLTextCreate(main_wnd, time_text, 0, cury, UIF_CENTER);
      cury += 30;

      // HotSpotCreate(int item,int parentitem, int id, int key, int txtitemoff, int txtitemon, int x, int y, int w, int
      // h, int flags,int winnum)
      DLLHotSpotCreate(main_wnd, UID_CANCEL, KEY_ESC, close_on_text, close_off_text, 130, cury, 60, 20, UIF_CENTER);
      DLLNewUIGameWindowOpen(main_wnd);
      int exit_menu = 0;
      while (!exit_menu) {
        int res;

        res = DLLDoUI();
        if (res == UID_CANCEL) {
          exit_menu = 1;
        }
      }
      DLLNewUIGameWindowClose(main_wnd);
      DLLNewUIGameWindowDestroy(main_wnd);
      // Cleanup
      DLLRemoveUITextItem(rank_text);
      DLLRemoveUITextItem(title_text);
      DLLRemoveUITextItem(close_on_text);
      DLLRemoveUITextItem(close_off_text);
      DLLRemoveUITextItem(kills_text);
      DLLRemoveUITextItem(deaths_text);
      DLLRemoveUITextItem(suicide_text);
      DLLRemoveUITextItem(eff_text);
      DLLRemoveUITextItem(time_text);
      DLLRemoveUITextItem(pilot_name_text);

      DLLDeleteUIItem(pilot_t);
      DLLDeleteUIItem(main_wnd);
      DLLDeleteUIItem(title_t);
      DLLDeleteUIItem(kill_t);
      DLLDeleteUIItem(death_t);
      DLLDeleteUIItem(suicide_t);
      DLLDeleteUIItem(eff_t);
      DLLDeleteUIItem(rank_t);
      DLLDeleteUIItem(time_in_game_t);
    }
  }
  DLLCloseSplashScreen();

  return 1;
}

void AutoLoginAndJoinGame() {

  int loginlen = LOGIN_LEN;
  int passlen = PASSWORD_LEN;
  int valret;
  uint16_t port;
  uint32_t iaddr;

  *DLLMultiGameStarting = 0;
  DLLCreateSplashScreen(TXT_PXO_CONNECTING, 0);
  DLLDatabaseRead("TrackerLogin", szloginid, &loginlen);
  DLLDatabaseRead("TrackerPassword", szpassword, &passlen);
  if (!*DLLAuto_login_addr) {
    DLLmprintf(0, "Can't autostart because no IP address was specified!!\n");
    *DLLMultiGameStarting = 0;
    goto failed_login;
  }
  if (*DLLAuto_login_port) {
    port = atoi(DLLAuto_login_port);
  } else {
    port = DEFAULT_GAME_PORT;
  }
  if (!*szloginid || !*szpassword) {
    if (LoginMasterTracker()) {
      // Uh... now connect to the server
    } else {
      goto failed_login;
    }
  }

  // Fill out the validate struct and send off the packet
  validate_id_request val_user;
  strcpy(val_user.tracker_id, sztrackerid);
  strcpy(val_user.login, szloginid);
  strcpy(val_user.password, szpassword);

  valret = ValidateUser(&val_user, sztrackerid);
  while (valret == 0) {
    valret = ValidateUser(nullptr, nullptr);
    DLLDescentDefer();
  }
  if (valret == 1) {
    // User was validated
    DLLmprintf(0, "Mastertracker user validated!\n");
    strcpy(DLLTracker_id, sztrackerid);
    strcpy(DLLMPlayers[DLLPlayer_num].tracker_id, sztrackerid);

  } else if (valret == -1) {
    // User invalid!
    DLLmprintf(0, "Mastertracker user not validated!\n");
    DLLDoMessageBox(TXT_PXO_MASTERTRACKER, TXT_PXO_BADLOGIN, MSGBOX_OK, UICOL_WINDOW_TITLE, UICOL_TEXT_NORMAL);
    goto failed_login;
  } else {
    // timeout waiting for tracker!
    DLLmprintf(0, "Mastertracker timeout!\n");
    DLLDoMessageBox(TXT_PXO_MASTERTRACKER, TXT_PXO_TIMEOUTMT, MSGBOX_OK, UICOL_WINDOW_TITLE, UICOL_TEXT_NORMAL);
    goto failed_login;
  }

  // Now actually connect to the server!

  network_address s_address;
  iaddr = inet_addr(DLLAuto_login_addr);
  memcpy(&s_address.address, &iaddr, sizeof(uint32_t));
  s_address.port = port;
  s_address.connection_type = NP_TCP;
  *DLLGame_is_master_tracker_game = 1;
  DLLMultiStartClient(nullptr);

  if ((DLLTryToJoinServer(&s_address))) {
    DLLmprintf(0, "Menu: Game joined!\n");
    *DLLMultiGameStarting = 1;
  }

failed_login:
  // Run this to make sure we properly ACK the server.
  for (int j = 0; j < 10; j++)
    PollPTrackNet();
  DLLCloseSplashScreen();
}

void AutoLoginAndStartGame() {
  int loginlen = LOGIN_LEN;
  int passlen = PASSWORD_LEN;
  int valret;

  *DLLMultiGameStarting = 0;

  DLLDatabaseRead("TrackerLogin", szloginid, &loginlen);
  DLLDatabaseRead("TrackerPassword", szpassword, &passlen);

  if (!*szloginid || !*szpassword) {
    if (LoginMasterTracker()) {
      // Uh... now connect to the server
    } else {
      goto failed_login;
    }
  }

  // Fill out the validate struct and send off the packet
  validate_id_request val_user;
  strcpy(val_user.tracker_id, sztrackerid);
  strcpy(val_user.login, szloginid);
  strcpy(val_user.password, szpassword);

  valret = ValidateUser(&val_user, sztrackerid);
  while (valret == 0) {
    valret = ValidateUser(nullptr, nullptr);
    DLLDescentDefer();
  }
  if (valret == 1) {
    // User was validated
    DLLmprintf(0, "Mastertracker user validated!\n");
    DLLPrintDedicatedMessage("Mastertracker user validated.\n");
    strcpy(DLLTracker_id, sztrackerid);
    strcpy(DLLMPlayers[DLLPlayer_num].tracker_id, sztrackerid);

  } else if (valret == -1) {
    // User invalid!
    DLLmprintf(0, "Mastertracker user not validated!\n");
    DLLPrintDedicatedMessage("Mastertracker user not validated!\n");
    goto failed_login;
  } else {
    // timeout waiting for tracker!
    DLLmprintf(0, "Mastertracker timeout!\n");
    DLLPrintDedicatedMessage("Mastertracker timeout!\n");
    goto failed_login;
  }

  *DLLMultiGameStarting = 1;
  *DLLGame_is_master_tracker_game = 1;
  //	strcpy(DLLD3_tracker_info.game_name,DLLNetgame->name);
  //	strcpy(DLLD3_tracker_info.mission_name,DLLNetgame->mission);
  strcpy(DLLD3_tracker_info.lobby, DLLPXO_hosted_lobby_name);

failed_login:
  // Run this to make sure we properly ACK the server.
  for (int j = 0; j < 10; j++)
    PollPTrackNet();
}

#define MAX_MOTD_LEN 400
#define NUM_MOTD_LINES 6
#define MOTD_WIDTH 384
#define MOTD_HEIGHT 256

int ShowMessageOfTheDay(void) {
  static char szlastmotd[MAX_MOTD_LEN];
  static char sznewmotd[MAX_MOTD_LEN];
  int motdlen = MAX_MOTD_LEN;
  int res;
  int rval = 0;
  static void *main_wnd;
  void *close_hs;

  int last_motd_version = 0;

  DLLDatabaseReadInt("MOTDVersion", &last_motd_version);

  if (Motd_version == last_motd_version) {
    // MOTD is old....
    DLLmprintf(0, "MOTD is old, skipping\n");
    return 1;
  }

  DLLDatabaseWriteInt("MOTDVersion", Motd_version);

  void *close_on_text = DLLCreateNewUITextItem(TXT_PXO_CLOSE, UICOL_HOTSPOT_HI);
  void *close_off_text = DLLCreateNewUITextItem(TXT_PXO_CLOSE, UICOL_HOTSPOT_LO);
  void *motd_text = DLLCreateNewUITextItem("PXO Message of the day", UICOL_WINDOW_TITLE);

  main_wnd = DLLNewUIGameWindowCreate(0, 0, MOTD_WIDTH, MOTD_HEIGHT, UIF_PROCESS_ALL | UIF_CENTER | NUWF_TITLELARGE);

  void *console_item = DLLUIConsoleGadgetCreate(main_wnd, 15, 20, 30, 0, 40, 20, 0);
  void *title = DLLTextCreate(main_wnd, motd_text, 0, 7, UIF_CENTER);

  close_hs = DLLHotSpotCreate(main_wnd, UID_OK, KEY_ENTER, close_off_text, close_on_text, 60, MOTD_HEIGHT - 60, 60, 20,
                              UIF_CENTER);

  DLLDatabaseRead("LastMOTD", szlastmotd, &motdlen);

  DLLmprintf(0, "Getting message of the day...\n");
  DLLCreateSplashScreen(TXT_PXO_CONNECTING, 1);
  int mcode = GetD3MOTD(sznewmotd, MAX_MOTD_LEN);
  do {
    mcode = GetD3MOTD(nullptr, 0);
    res = DLLPollUI();
    if (res == 99) {
      GetD3MOTDCancel();
      DLLCloseSplashScreen();
      goto close_motd;
    }
    DLLDescentDefer();
  } while (mcode == 0);

  DLLCloseSplashScreen();

  if (mcode == 1) {
    DLLmprintf(0, "Message of the day: %s\n", sznewmotd);
    if (strcmp(szlastmotd, sznewmotd) != 0) {
      DLLNewUIGameWindowOpen(main_wnd);
      DLLUIConsoleGadgetputs(console_item, sznewmotd);
      DLLDatabaseWrite("LastMOTD", sznewmotd, strlen(sznewmotd) + 1);
      do {
        res = DLLPollUI();
        DLLDescentDefer();
      } while (res != UID_OK);
      DLLNewUIGameWindowClose(main_wnd);
      rval = 1;
      goto close_motd;
    } else {
      DLLmprintf(0, "Message of the day is old, ignoring!\n");
      rval = 1;
      goto close_motd;
    }
  } else {
    DLLmprintf(0, "Get message of the day failed (%d)!\n", mcode);
    goto close_motd;
  }

close_motd:
  DLLmprintf(0, "Ending motd\n");
  DLLNewUIGameWindowDestroy(main_wnd);
  DLLRemoveUITextItem(motd_text);
  DLLRemoveUITextItem(close_on_text);
  DLLRemoveUITextItem(close_off_text);

  DLLDeleteUIItem(console_item);
  DLLDeleteUIItem(title);
  DLLDeleteUIItem(close_hs);
  DLLDeleteUIItem(main_wnd);
  return rval;
}
