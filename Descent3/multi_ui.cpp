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

 * $Logfile: /DescentIII/main/multi_ui.cpp $
 * $Revision: 105 $
 * $Date: 7/09/01 3:34p $
 * $Author: Matt $
 *
 *
 *
 * $Log: /DescentIII/main/multi_ui.cpp $
 *
 * 105   7/09/01 3:34p Matt
 * Require at least one allowed ship when starting a netgame.
 *
 * 104   4/20/00 6:25p Matt
 * Netgame info dialog was looking at wrong variable for the difficulty
 * level.
 *
 * 103   8/02/99 9:57a Kevin
 * fixed port parameter with -pxo
 *
 * 102   5/19/99 1:10p Kevin
 * set the default (or previously selected) difficulty level
 *
 * 101   5/09/99 4:55p Kevin
 * Added some options for directplay games
 *
 * 100   5/09/99 1:34p Kevin
 * Added diffuculty level system to multiplayer
 *
 * 99    5/08/99 3:58p Kevin
 * made ESC clear the game info dialog
 *
 * 98    5/06/99 6:11p Kevin
 * fixes for save/load game syste. Also require CD again and added some
 * heat.net stuff
 *
 * 97    5/06/99 1:04a Kevin
 * Fixed stupid default selection problem
 *
 * 96    5/05/99 11:59p Kevin
 * fixed command line parms for auto connecting
 *
 * 95    5/05/99 11:16p Kevin
 * heat.net stuff among other things
 *
 * 94    4/28/99 10:04p Kevin
 * doh! forgot to return a value
 *
 * 93    4/28/99 6:39p Kevin
 * Build 182 fixes
 *
 * 92    4/26/99 9:11p Matt
 * Use small font instead of old UI font.
 *
 * 91    4/25/99 5:02p Kevin
 * Bunches of multiplayer UI improvements
 *
 * 90    4/25/99 9:44a Kevin
 * localized remaining game info strings
 *
 * 89    4/25/99 8:58a Kevin
 * fixes for server info dialog
 *
 * 88    4/24/99 11:58p Kevin
 * Game info list (hit I in the pxo game list)
 *
 * 87    4/23/99 5:32p Kevin
 * Fixed a few mission bugs.
 *
 * 86    4/20/99 11:47a Samir
 * converted protocol help to newui and fixed connection menu so enter
 * worked on listbox.
 *
 * 85    4/17/99 3:44p Kevin
 * Demo2 changes & fixes
 *
 * 84    4/16/99 6:00p Kevin
 * Bunches of Demo stuff
 *
 * 83    4/16/99 3:17p Kevin
 * More mouselook support
 *
 * 82    4/16/99 11:56a Matt
 * Changed directplay code to be "ifdef _WIN32" instead of "ifndef
 * __LINUX__" so it will work on the Mac.
 *
 * 81    4/15/99 3:36p Kevin
 * Added mouselook UI stuff to the multiplayer options menu
 *
 * 80    4/15/99 1:41a Jeff
 * changes for linux compile
 *
 * 79    4/14/99 4:19a Jeff
 * more case mismatch fixes in #includes
 *
 * 78    4/14/99 2:51a Jeff
 * fixed some case mismatched #includes
 *
 * 77    4/08/99 4:54p Kevin
 * Display level warp dialog for multiplayer
 *
 * 76    4/03/99 9:26p Jeff
 * changed dialogs that weren't using UID_OK and UID_CANCEL to use and
 * handle them properly
 *
 * 75    3/25/99 3:29p Jason
 * added option to randomize powerup respawn points
 *
 * 74    3/03/99 12:44p Jason
 * made options mirror that of the 1.1 demo
 *
 * 73    3/01/99 12:55a Matt
 * Deleted some obsolete strings from the string table, and moved some
 * formatting info from the table to the code.
 *
 * 72    2/28/99 6:00p Jeff
 * converted to new ui
 *
 * 71    2/24/99 4:00p Jason
 * fixed flush problem when going to the join menu
 *
 * 70    2/20/99 2:31p Kevin
 * Made multiplayer DLLs return to the game list after a game.
 *
 * 69    2/15/99 7:50p Jeff
 * new pilot file class and read/write system checked in...should be more
 * robust than old
 *
 * 68    2/10/99 1:32p Kevin
 * Added tablefile ignore thingy
 *
 * 67    2/08/99 2:39p Kevin
 * Fixed command line joining & disabled gamespy launching in OEM builds
 *
 * 66    1/29/99 5:22p Jeff
 * localization
 *
 * 65    1/23/99 3:21p Kevin
 * Fixed default selection to work with new sorted listboxes
 *
 * 64    1/05/99 5:09p Jason
 * added permissable server networking (ala Quake/Unreal) to Descent3
 *
 * 63    1/04/99 6:56p Kevin
 * Fixed unmatched if/else
 *
 * 62    12/30/98 3:49p Kevin
 * Moved multiplayer options out of DLL and into main app
 *
 * 61    11/20/98 11:16a Kevin
 * Fixed command line game launching
 *
 * 60    11/19/98 5:40p Kevin
 * Demo system
 *
 * 59    10/24/98 10:49a Kevin
 * Fixed Direct Serial Game
 *
 * 58    10/20/98 5:47p Kevin
 * Gunboy and other fixes
 *
 * 57    10/19/98 11:54a Kevin
 *
 * 56    10/19/98 10:54a Kevin
 * Fixed help option
 *
 * 55    10/16/98 11:55a Kevin
 * Made dlls loadable in a hog
 *
 * 54    10/15/98 10:58a Kevin
 * fixed ~ thingy for the first file in the dir
 *
 * 53    10/14/98 2:48p Kevin
 * Changed memory code to comply with mem lib
 *
 * 52    10/09/98 12:59a Craig
 * Fixed ship name for demo
 *
 * 51    10/06/98 5:34p Jeff
 * various UI changes/improvements
 *
 * 50    10/01/98 11:45a Kevin
 * fixed hotspot colors in allow/disallow screen
 *
 * 49    9/30/98 10:36a Kevin
 * Added command line launching of URLs and command line directory
 * specification
 *
 * 48    9/29/98 2:23p Kevin
 * More UI tweaks
 *
 * 47    9/28/98 6:53p Kevin
 * localized some multiplayer menus
 *
 * 46    9/28/98 4:35p Jeff
 * general UI changes and improvements
 *
 * 45    9/28/98 4:21p Kevin
 * Redesigned game list menus
 *
 * 44    9/28/98 9:53a Kevin
 * Fixing misc UI problems, and fixed some bugs that VC 6 found
 *
 * 43    9/25/98 11:07a Kevin
 * fixed columns to line up and cleaned up some PXO bugs
 *
 * 42    9/23/98 6:33p Kevin
 * Fixed load settings
 *
 * 41    9/23/98 2:54p Kevin
 * Saved multi config and changed UI to conform
 *
 * 40    9/22/98 3:55p Kevin
 * Removed obsolete function
 *
 * 39    9/22/98 2:29p Kevin
 * moved ships allowed code out of dll and into main app. Also added
 * powerup exclusions
 *
 * 38    8/26/98 1:31p Jason
 * Flush buffers before starting a game
 *
 * 37    8/17/98 11:00a Kevin
 * Moved DLLs into subdirectories
 *
 * 36    8/15/98 5:16p Matt
 * Added new Base_directory variable.  Got rid of D3_LOCAL check and
 * 'local directory' registry variable.
 *
 * 35    7/10/98 10:47a Kevin
 * Added command line connecting to games
 *
 * 34    7/01/98 2:52p Kevin
 * coop -- adding sound index
 *
 * 33    6/24/98 6:40p Kevin
 * Added help to main dll menu
 *
 * 32    6/18/98 4:49p Kevin
 * Updated multiplayer menus
 *
 * 31    6/16/98 10:54a Jeff
 *
 * 30    6/11/98 2:33p Kevin
 * Updated dsps for new dll names
 *
 * 29    6/11/98 2:11p Kevin
 * New Main multiplayer menu & dlls renamed to d3c
 *
 * 28    6/01/98 12:09p Kevin
 * closed the menu before loading DLLs
 *
 * 27    6/01/98 10:09a Kevin
 * Added DLL connection interface and auto update DLL
 *
 * 26    5/12/98 5:59p Jason
 * fixed stupid timer bug
 *
 * 25    5/05/98 3:02p Jason
 * attempting to add different screen resolutions
 *
 * 24    5/04/98 10:56a Kevin
 * Mastertracker fixes/enhancements
 *
 * 23    5/01/98 12:28p Kevin
 * Added new user registration button for MT
 *
 * 22    4/30/98 3:50p Kevin
 * Mastertracker pilot stats
 *
 * 21    4/28/98 12:50p Kevin
 * Master tracker login
 *
 * 20    4/27/98 7:12p Kevin
 * Mastertracker pilot tracker
 *
 * 19    4/24/98 3:50p Kevin
 * Added mastertracker game tracking support
 *
 * 18    4/23/98 4:49p Kevin
 * Added Master tracker Game tracker support
 *
 * 17    4/23/98 2:12p Kevin
 * Adding Mastertracker stuff
 *
 * 16    4/14/98 7:56p Matt
 * Moved MSN_NAMELEN from mission.h to descent,h, so multi.h didn't need
 * to include mission.h.
 * Changed code to use ddio_MakePath() instead of sprintf() to make file
 * spec.
 *
 */

#include "args.h"
#include "ui.h"
#include "newui.h"
#include "game.h"
#include "gamefont.h"
#include "descent.h"
#include "multi.h"
#include "multi_ui.h"
#include "multi_server.h"
#include "multi_client.h"
#include "networking.h"
#include "player.h"
#include "manage.h"
#include "pilot.h"
#include <stdlib.h>
#include "ddio.h"
#include "objinfo.h"
#include "stringtable.h"
#include "ConfigItem.h"
#include "appdatabase.h"

// #define USE_DIRECTPLAY

#ifdef USE_DIRECTPLAY
#include "directplay.h"
#endif

#include "ship.h"

#include "multi_dll_mgr.h"
#include "Mission.h"
#include "menu.h"

#include "multi_save_settings.h"

#include <algorithm>

#define MAIN_MULTI_MENU_W 384
#define MAIN_MULTI_MENU_H 256
#define MAIN_MULTI_MENU_X 320 - (MAIN_MULTI_MENU_W / 2)
#define MAIN_MULTI_MENU_Y 240 - (MAIN_MULTI_MENU_H / 2)

#define HELP_MULTI_MENU_W 512
#define HELP_MULTI_MENU_H 192
#define HELP_MULTI_MENU_X 320 - (MAIN_MULTI_MENU_W / 2)
#define HELP_MULTI_MENU_Y 240 - (MAIN_MULTI_MENU_H / 2)

#define MAX_HELP_TEXT_LEN 1000
char HelpText1[MAX_HELP_TEXT_LEN];
char HelpText2[MAX_HELP_TEXT_LEN];
char HelpText3[MAX_HELP_TEXT_LEN];
char HelpText4[MAX_HELP_TEXT_LEN];

int MultiDLLGameStarting = 0;

void DisplayNetDLLHelp(const char *topic);
// The first multiplayer menu that the user will see...all multiplayer stuff is
// reached from this menu
// Returns true if we're starting a multiplayer game
#define MAX_DLLS 10
#define JEFF_RED GR_RGB(255, 40, 40)
#define MAX_NET_DLL_LEN 100

#define UID_MULTILB 0x1000

#define HEAT_NAME "HEAT.NET"
#define PXO_NAME "Parallax Online"

int MainMultiplayerMenu() {

  mprintf(0, "Entering MainMultiplayerMenu()\n");

#ifdef USE_DIRECTPLAY
  Num_directplay_games = 0;
#endif
  int exit_menu = 0;
  int ret = 0;
  char sznetgame[MAX_NET_DLL_LEN] = "";
  int netgamelen = MAX_NET_DLL_LEN;
  int i;
  uint32_t j;

  for (i = 0; i < MAX_OBJECT_IDS; i++) {
    if (Object_info[i].type == OBJ_POWERUP) {
      Object_info[i].multi_allowed = 1;
    }
  }
  for (i = 0; i < MAX_SHIPS; i++) {
    if (Ships[i].used) {

#ifdef DEMO
      if (stricmp(Ships[i].name, "pyro-gl") == 0)
#endif
        PlayerSetShipPermission(-1, Ships[i].name, 1);
#ifdef DEMO
      else
        PlayerSetShipPermission(-1, Ships[i].name, 0);
#endif
    }
  }
  // Clear out residual junk
  MultiFlushAllIncomingBuffers();

  SetScreenMode(SM_MENU);

  Database()->read("DefaultNetConn", sznetgame, &netgamelen);
  if (*sznetgame == '\0') {
    strcpy(sznetgame, "HEAT.NET");
    Database()->write("DefaultNetConn", sznetgame, strlen(sznetgame) + 1);
  }

  newuiTiledWindow menu_wnd;
  newuiListBox *lists;
  newuiSheet *sheet;

  menu_wnd.Create(TXT_MULTIPLAYER, 0, 0, MAIN_MULTI_MENU_W, MAIN_MULTI_MENU_H);
  sheet = menu_wnd.GetSheet();

  sheet->NewGroup(TXT_MLTCHOOSETYPE, 25, 0);
  lists = sheet->AddListBox(256, 128, UID_MULTILB, UILB_NOSORT);
  lists->RemoveAll();

  sheet->NewGroup(NULL, 75, 145);
  sheet->AddLongButton(TXT_SETITEMDEFAULT, 0x30);

  sheet->NewGroup(NULL, 55, 160, NEWUI_ALIGN_HORIZ);
  sheet->AddButton(TXT_OK, UID_OK);
  sheet->AddButton(TXT_REALHELP, 0x20);
  sheet->AddButton(TXT_CANCEL, UID_CANCEL);

  int dllcount = 1;
  char buffer[_MAX_PATH], fname[_MAX_PATH], fext[_MAX_PATH], fdir[_MAX_PATH];
  char search[256];

  ddio_MakePath(search, Base_directory, "online", "*.d3c", NULL);

  int dftidx = -1;
  dllcount = 0;

  // Put the HEAT on top.
  if (ddio_FindFileStart(search, buffer)) {

    ddio_SplitPath(buffer, fdir, fname, fext);

    if (!stricmp(HEAT_NAME, fname)) {
      lists->AddItem(fname);
      dllcount++;
    }
    if (!stricmp(sznetgame, fname)) {
      dftidx = 0;
    }

    while ((ddio_FindNextFile(buffer)) && (dllcount < MAX_DLLS)) {
      ddio_SplitPath(buffer, fdir, fname, fext);
      if (!stricmp(HEAT_NAME, fname)) {
        lists->AddItem(fname);
        dllcount++;
      }
      if (!stricmp(sznetgame, fname)) {
        dftidx = 0;
      }
    }
  }

  // Put the PXO next.
  if (ddio_FindFileStart(search, buffer)) {

    ddio_SplitPath(buffer, fdir, fname, fext);

    if (!stricmp(PXO_NAME, fname)) {
      lists->AddItem(fname);
      dllcount++;
    }
    if (!stricmp(sznetgame, fname)) {
      dftidx = 1;
    }

    while ((ddio_FindNextFile(buffer)) && (dllcount < MAX_DLLS)) {
      ddio_SplitPath(buffer, fdir, fname, fext);
      if (!stricmp(PXO_NAME, fname)) {
        lists->AddItem(fname);
        dllcount++;
      }
      if (!stricmp(sznetgame, fname)) {
        dftidx = 1;
      }
    }
  }

  if (ddio_FindFileStart(search, buffer)) {

    ddio_SplitPath(buffer, fdir, fname, fext);

    for (j = 0; j < strlen(fname); j++) {
      if (fname[j] == '~') {
        fname[j] = '/';
      }
    }

    if ((stricmp(HEAT_NAME, fname) != 0) && (stricmp(PXO_NAME, fname) != 0)) {
      lists->AddItem(fname);
      if (!stricmp(sznetgame, fname)) {
        dftidx = dllcount;
      }
      dllcount++;
    }

    uint32_t len;
    while ((ddio_FindNextFile(buffer)) && (dllcount < MAX_DLLS)) {
      ddio_SplitPath(buffer, fdir, fname, fext);
      len = strlen(fname);

      for (j = 0; j < len; j++) {
        if (fname[j] == '~') {
          fname[j] = '/';
        }
      }

      if ((stricmp(HEAT_NAME, fname) != 0) && (stricmp(PXO_NAME, fname) != 0)) {
        lists->AddItem(fname);
        if (!stricmp(sznetgame, fname)) {
          dftidx = dllcount;
        }
        dllcount++;
      }
    }
  } else {
    dllcount = 0;
  }
  ddio_FindFileClose();

  if (dllcount == 0) {
    DoMessageBox(TXT_MULTIPLAYER, TXT_MULTINOFILES, MSGBOX_OK, UICOL_WINDOW_TITLE, UICOL_TEXT_NORMAL);
    exit_menu = 1;
    menu_wnd.Destroy();
    return 0;
  }

  if (dftidx != -1) {
    lists->SetCurrentItem(sznetgame); //>SetCurrentIndex(dftidx);
  }

  MultiDLLGameStarting = 0;
  menu_wnd.Open();

  // Menu loop
  char seldll[_MAX_PATH];

  while (!exit_menu) {
    int res;

    res = menu_wnd.DoUI();

    // handle all UI results.
    switch (res) {
    case UID_CANCEL:
      menu_wnd.Close();
      exit_menu = 1;
      break;

    case UID_MULTILB:
    case UID_OK: {
      menu_wnd.Close();
      lists->GetCurrentItem(seldll, _MAX_PATH);
      uint32_t len = strlen(seldll);

      for (j = 0; j < len; j++) {
        if (seldll[j] == '/') {
          seldll[j] = '~';
        }
      }
      // ddio_MakePath(fulldll,Base_directory,"online",seldll,NULL);
      if (LoadMultiDLL(seldll)) {
        CallMultiDLL(MT_EVT_LOGIN);
        exit_menu = 1;
        ret = MultiDLLGameStarting;
      } else {
        exit_menu = 1;
        ret = 0;
      }
    } break;

    case 0x20:
      // Help
      {
        lists->GetCurrentItem(seldll, _MAX_PATH);
        uint32_t len = strlen(seldll);
        for (j = 0; j < len; j++) {
          if (seldll[j] == '/') {
            seldll[j] = '~';
          }
        }
        // ddio_MakePath(fulldll,Base_directory,"online",seldll,NULL);
        if (LoadMultiDLL(seldll)) {
          CallMultiDLL(MT_EVT_GET_HELP);
          DisplayNetDLLHelp(seldll);
          FreeMultiDLL();
        }
      }
      break;

    case 0x30:
      // case 3:
      {
        char fmtmsg[200];
        char def[256];

        // Mark this baby as default.
        lists->GetCurrentItem(def, 256);

        Database()->write("DefaultNetConn", def, strlen(def) + 1);
        snprintf(fmtmsg, sizeof(fmtmsg), TXT_SETDEFAULT, def);
        DoMessageBox(TXT_MENUMULTIPLAYER, fmtmsg, MSGBOX_OK, UICOL_WINDOW_TITLE, UICOL_TEXT_NORMAL);
        break;
      }
    }
  }
  menu_wnd.Destroy();

  return ret;
}

void DisplayNetDLLHelp(const char *topic) {
  // samir- converted to newui.
  newuiTiledWindow menu_wnd;
  newuiSheet *sheet;
  int exit_menu = 0;
  char str[128];

  SetScreenMode(SM_MENU);

  // Create our buttons
  snprintf(str, sizeof(str), "%s: %s", TXT_REALHELP, topic);

  menu_wnd.Create(str, 0, 0, HELP_MULTI_MENU_W, HELP_MULTI_MENU_H);
  sheet = menu_wnd.GetSheet();

  sheet->NewGroup(NULL, 10, 30);
  sheet->AddText(HelpText1);
  sheet->AddText(HelpText2);
  sheet->AddText(HelpText3);
  sheet->AddText(HelpText4);

  sheet->NewGroup(NULL, (HELP_MULTI_MENU_W - 140), HELP_MULTI_MENU_H - 95, NEWUI_ALIGN_HORIZ);
  sheet->AddButton(TXT_CLOSE, UID_OK);

  menu_wnd.Open();

  // Menu loop
  while (!exit_menu) {
    int res;

    res = menu_wnd.DoUI();

    // handle all UI results.
    switch (res) {
    case UID_OK:
      exit_menu = 1;
      break;
    }
  }

  menu_wnd.Close();
  menu_wnd.Destroy();
}

int AutoConnectPXO() {
  // char seldll[_MAX_PATH];
  int iparg;
  int portarg;
  MultiDLLGameStarting = 0;
  iparg = FindArg("-pxo");
  if (!iparg) {
    return 0;
  }

  strcpy(Auto_login_addr, GameArgs[iparg + 1]);

  char *port = strchr(Auto_login_addr, ':');
  if (port) {
    // terminate the hostname
    *port = '\0';
    // Increment to the first character of the port name
    port++;
    // get the port number
    strcpy(Auto_login_port, port);
  } else {
    portarg = FindArg("port");
    if (portarg) {
      strcpy(Auto_login_port, GameArgs[portarg + 1]);
    } else {
      Auto_login_port[0] = '\0';
    }
  }

  // ddio_MakePath(seldll,Base_directory,"online","parallax online.d3c",NULL);
  if (LoadMultiDLL("parallax online")) {
    CallMultiDLL(MT_AUTO_LOGIN);
  }
  return MultiDLLGameStarting;
}

int AutoConnectLANIP() {
  // char seldll[_MAX_PATH];
  int iparg;
  int portarg;
  MultiDLLGameStarting = 0;
  iparg = FindArg("ip");
  if (!iparg) {
    int connarg = FindArg("-directip");

    if (!connarg)
      return 0;
    strcpy(Auto_login_addr, GameArgs[connarg + 1]);
    char *port = strchr(Auto_login_addr, ':');
    if (port) {
      // terminate the hostname
      *port = '\0';
      // Increment to the first character of the port name
      port++;
      // get the port number
      strcpy(Auto_login_port, port);
    }
  } else {
    strcpy(Auto_login_addr, GameArgs[iparg + 1]);

    portarg = FindArg("port");
    if (portarg) {
      strcpy(Auto_login_port, GameArgs[portarg + 1]);
    } else {
      Auto_login_port[0] = '\0';
    }
  }
  // ddio_MakePath(seldll,Base_directory,"online","Direct TCP~IP Game.d3c",NULL);
  if (LoadMultiDLL("Direct TCP~IP")) {
    CallMultiDLL(MT_AUTO_LOGIN);
  }
  return MultiDLLGameStarting;
}

int AutoConnectHeat() {
  // char seldll[_MAX_PATH];
  int iparg;
  int portarg;
  MultiDLLGameStarting = 0;
  iparg = FindArg("ip");
  if (!iparg) {
    int connarg = FindArg("-heat");

    if (!connarg)
      return 0;
    strcpy(Auto_login_addr, GameArgs[connarg + 1]);
    char *port = strchr(Auto_login_addr, ':');
    if (port) {
      // terminate the hostname
      *port = '\0';
      // Increment to the first character of the port name
      port++;
      // get the port number
      strcpy(Auto_login_port, port);
    }
  } else {
    strcpy(Auto_login_addr, GameArgs[iparg + 1]);

    portarg = FindArg("port");
    if (portarg) {
      strcpy(Auto_login_port, GameArgs[portarg + 1]);
    } else {
      Auto_login_port[0] = '\0';
    }
  }
  if (LoadMultiDLL("HEAT.NET")) {
    CallMultiDLL(MT_AUTO_LOGIN);
  }
  return MultiDLLGameStarting;
}

#include "mem.h"

void DoMultiAllowed(void) {
  rendering_state rs;
  rend_GetRenderState(&rs);
  int cury = 30;
  int i;
  const char *p;
  int objid;
  int *index_to_id = NULL;
  bool shipsallowed[MAX_SHIPS];
  bool objsallowed[MAX_OBJECTS];
  ConfigItem **ship_list = NULL;
  size_t strMax = std::max(strlen(TXT_ALLOW), strlen(TXT_DISALLOW)) + 3;
  char *str = (char *)mem_malloc(strMax);

  // Create Text Items and Window
  UITextItem cancel_on_text(TXT_CANCEL, UICOL_HOTSPOT_HI);
  UITextItem cancel_off_text(TXT_CANCEL, UICOL_HOTSPOT_LO);

  UITextItem exit_on_text(TXT_DONE, UICOL_HOTSPOT_HI);
  UITextItem exit_off_text(TXT_DONE, UICOL_HOTSPOT_LO);

  snprintf(str, strMax, "\x18 %s", TXT_ALLOW);
  UITextItem add_on(str, UICOL_HOTSPOT_HI);
  UITextItem add_off(str, UICOL_HOTSPOT_LO);

  snprintf(str, strMax, "%s \x1a", TXT_DISALLOW);
  UITextItem remove_on(str, UICOL_HOTSPOT_HI);
  UITextItem remove_off(str, UICOL_HOTSPOT_LO);
  mem_free(str);

  UITextItem allowed_ships(TXT_ALLOWEDSHIPS, UICOL_TEXT_NORMAL);
  UITextItem banned_ships(TXT_DISALLOWDSHIPS, UICOL_TEXT_NORMAL);

  UITextItem allowed_gen(TXT_ALLOWEDITEMS, UICOL_TEXT_NORMAL);
  UITextItem banned_gen(TXT_DISALLOWEDITEM, UICOL_TEXT_NORMAL);

  UITextItem obj_ti[MAX_OBJECT_IDS];
  UITextItem ship_ti[MAX_SHIPS];

  NewUIWindow menu_wnd;
  menu_wnd.Create(0, 0, rs.screen_width, rs.screen_height, UIF_PROCESS_ALL);

  int xcol1 = 110;
  int yrow1 = 50;
  int xcol2 = 374;
  int yrow2 = 250;
  int list_xsize = 160;
  int list_ysize = 160;

  NewUIListBox lb_ships_allowed;
  NewUIListBox lb_ships_banned;

  NewUIListBox lb_generic_allowed;
  NewUIListBox lb_generic_banned;
  UIHotspot exit_hs;
  UIHotspot add_ship_hs;
  UIHotspot remove_ship_hs;
  UIHotspot add_gen_hs;
  UIHotspot remove_gen_hs;
  UIHotspot cancel_hs;

  UIText ship_allowed_txt;
  UIText ship_banned_txt;
  UIText gen_allowed_txt;
  UIText gen_banned_txt;

  int textw;
  int startx;

  grtext_SetFont(SMALL_FONT);

  add_ship_hs.Create(&menu_wnd, 10, 0, &add_off, &add_on, 10, (yrow1 + (list_ysize / 2)) - 25, 130, 30,
                     UIF_FIT | UIF_CENTER);
  remove_ship_hs.Create(&menu_wnd, 11, 0, &remove_off, &remove_on, 10, (yrow1 + (list_ysize / 2)) - 5, 130, 30,
                        UIF_FIT | UIF_CENTER);

  add_gen_hs.Create(&menu_wnd, 12, 0, &add_off, &add_on, 10, (yrow2 + (list_ysize / 2)) - 25, 130, 30,
                    UIF_FIT | UIF_CENTER);
  remove_gen_hs.Create(&menu_wnd, 13, 0, &remove_off, &remove_on, 10, (yrow2 + (list_ysize / 2)) - 5, 130, 30,
                       UIF_FIT | UIF_CENTER);

  textw = grtext_GetTextLineWidth(allowed_ships.GetBuffer());
  startx = ((list_xsize / 2) + xcol1) - (textw / 2);

  ship_allowed_txt.Create(&menu_wnd, &allowed_ships, startx, yrow1 - 15, 0);
  textw = grtext_GetTextLineWidth(banned_ships.GetBuffer());
  startx = ((list_xsize / 2) + xcol2) - (textw / 2);

  ship_banned_txt.Create(&menu_wnd, &banned_ships, startx, yrow1 - 15, 0);
  textw = grtext_GetTextLineWidth(allowed_gen.GetBuffer());
  startx = ((list_xsize / 2) + xcol1) - (textw / 2);

  gen_allowed_txt.Create(&menu_wnd, &allowed_gen, startx, yrow2 - 15, 0);
  textw = grtext_GetTextLineWidth(banned_gen.GetBuffer());
  startx = ((list_xsize / 2) + xcol2) - (textw / 2);

  gen_banned_txt.Create(&menu_wnd, &banned_gen, startx, yrow2 - 15, 0);

  lb_ships_allowed.Create(&menu_wnd, 2, xcol1, yrow1, list_xsize, list_ysize, 0);
  lb_ships_allowed.SetSelectedColor(UICOL_LISTBOX_HI);
  lb_ships_allowed.SetHiliteColor(UICOL_LISTBOX_HI);
  lb_ships_banned.Create(&menu_wnd, 3, xcol2, yrow1, list_xsize, list_ysize, 0);
  lb_ships_banned.SetSelectedColor(UICOL_LISTBOX_HI);
  lb_ships_banned.SetHiliteColor(UICOL_LISTBOX_HI);
  lb_generic_allowed.Create(&menu_wnd, 4, xcol1, yrow2, list_xsize, list_ysize, 0);
  lb_generic_allowed.SetSelectedColor(UICOL_LISTBOX_HI);
  lb_generic_allowed.SetHiliteColor(UICOL_LISTBOX_HI);
  lb_generic_banned.Create(&menu_wnd, 5, xcol2, yrow2, list_xsize, list_ysize, 0);
  lb_generic_banned.SetSelectedColor(UICOL_LISTBOX_HI);
  lb_generic_banned.SetHiliteColor(UICOL_LISTBOX_HI);

  // Exit out Hotspot
  exit_hs.Create(&menu_wnd, UID_OK, KEY_ESC, &exit_off_text, &exit_on_text, 10, 420, 180, 30, UIF_FIT | UIF_CENTER);
  cury += 20;
  cancel_hs.Create(&menu_wnd, UID_CANCEL, 0, &cancel_off_text, &cancel_on_text, 10, 445, 180, 30, UIF_FIT | UIF_CENTER);
  cury += 20;

  NewUIWindowLoadBackgroundImage(&menu_wnd, "multimain.ogf");

  // Object_info[MAX_OBJECT_IDS];
  //
  // if(Object_info[i].type==OBJ_POWERUP)
  for (i = 0; i < MAX_OBJECT_IDS; i++) {
    if (Object_info[i].type == OBJ_POWERUP) {
      obj_ti[i] = UITextItem(Object_info[i].name, UICOL_TEXT_NORMAL);
      if (Object_info[i].multi_allowed) {
        objsallowed[i] = true;
        lb_generic_allowed.AddItem(&obj_ti[i]);
      } else {
        objsallowed[i] = false;
        lb_generic_banned.AddItem(&obj_ti[i]);
      }
    }
  }

  for (i = 0; i < MAX_SHIPS; i++) {
    if (Ships[i].used) {
      ship_ti[i] = UITextItem(Ships[i].name, UICOL_TEXT_NORMAL);

      if (PlayerIsShipAllowed(0, i)) {
        shipsallowed[i] = true;
        lb_ships_allowed.AddItem(&ship_ti[i]);
      } else {
        shipsallowed[i] = false;
        lb_ships_banned.AddItem(&ship_ti[i]);
      }
    }
  }
  //
  // Open the window and process
  menu_wnd.Open();
  int exit_menu = 0;

  while (!exit_menu) {
    int res;

    res = DoUI();
    switch (res) {
    case UID_OK: {
      // Check for at least one ship allowed
      for (i = 0; i < MAX_SHIPS; i++) {
        if (Ships[i].used && PlayerIsShipAllowed(0, i)) {
          break;
        }
      }

      // If no allowed ships found, put up message
      if (i == MAX_SHIPS) {
        DoMessageBox(TXT_MENUMULTIPLAYER, "You must have at least one allowed ship.", MSGBOX_OK, UICOL_WINDOW_TITLE,
                     UICOL_TEXT_NORMAL);
        break;
      }

      // exit
      exit_menu = true;

    } break;
    case UID_CANCEL:
      // restore old settings
      for (i = 0; i < MAX_OBJECT_IDS; i++) {
        if (Object_info[i].type == OBJ_POWERUP) {
          if (objsallowed[i]) {
            Object_info[i].multi_allowed = 1;
          } else {
            Object_info[i].multi_allowed = 0;
          }
        }
      }
      for (i = 0; i < MAX_SHIPS; i++) {
        if (Ships[i].used) {
          if (shipsallowed[i]) {
            PlayerSetShipPermission(-1, Ships[i].name, 1);
          } else {
            PlayerSetShipPermission(-1, Ships[i].name, 0);
          }
        }
      }
      // now exit
      exit_menu = true;
      break;
    case 10:
#ifndef DEMO
    {
      // Make ship allowed
      UITextItem *selti = (UITextItem *)lb_ships_banned.GetItem(lb_ships_banned.GetSelectedIndex());
      if (!selti)
        break;
      p = selti->GetBuffer();
      PlayerSetShipPermission(-1, (char *)p, 1);
      lb_ships_banned.RemoveItem(selti);
      lb_ships_allowed.AddItem(selti);
      break;
    }
#else
      DoMessageBox(TXT_ERROR, TXT_WRONGVERSION, MSGBOX_OK, UICOL_WINDOW_TITLE, UICOL_TEXT_NORMAL);
      break;
#endif
    case 11:
#ifndef DEMO
    {
      // Make ship not allowed
      UITextItem *selti = (UITextItem *)lb_ships_allowed.GetItem(lb_ships_allowed.GetSelectedIndex());
      if (!selti)
        break;
      p = selti->GetBuffer();
      PlayerSetShipPermission(-1, (char *)p, 0);
      lb_ships_allowed.RemoveItem(selti);
      lb_ships_banned.AddItem(selti);
      break;
    }
#else
      DoMessageBox(TXT_ERROR, TXT_WRONGVERSION, MSGBOX_OK, UICOL_WINDOW_TITLE, UICOL_TEXT_NORMAL);
      break;
#endif
    case 12: {
      // make obj allowed
      UITextItem *selti = (UITextItem *)lb_generic_banned.GetItem(lb_generic_banned.GetSelectedIndex());
      if (!selti)
        break;
      p = selti->GetBuffer();
      objid = FindObjectIDName(IGNORE_TABLE(p));
      if (objid != -1) {
        ASSERT(Object_info[objid].type == OBJ_POWERUP);
        ASSERT(Object_info[objid].multi_allowed == 0);
        Object_info[objid].multi_allowed = 1;
        lb_generic_banned.RemoveItem(&obj_ti[objid]);
        lb_generic_allowed.AddItem(&obj_ti[objid]);
      }
      break;
    }
    case 13: {
      // make obj not allowed
      UITextItem *selti = (UITextItem *)lb_generic_allowed.GetItem(lb_generic_allowed.GetSelectedIndex());
      if (!selti)
        break;
      p = selti->GetBuffer();
      objid = FindObjectIDName(IGNORE_TABLE(p));
      if (objid != -1) {
        ASSERT(Object_info[objid].type == OBJ_POWERUP);
        ASSERT(Object_info[objid].multi_allowed == 1);
        Object_info[objid].multi_allowed = 0;
        lb_generic_allowed.RemoveItem(&obj_ti[objid]);
        lb_generic_banned.AddItem(&obj_ti[objid]);
      }
      break;
    }
    default: {
    }
    }
  }
  // handle all UI results.
  menu_wnd.Close();
  menu_wnd.Destroy();
}

void MultiDoConfigSave(void) {
  char file[_MAX_PATH * 2];

  ddio_MakePath(file, Base_directory, "custom", "settings", NULL);
  if (DoPathFileDialog(true, file, TXT_MULTISAVESET, "*.mps", 0)) {
    if (stricmp(file + (strlen(file) - 4), ".mps") != 0)
      strcat(file, ".mps");
    MultiSaveSettings(file);
  }
}

void MultiDoConfigLoad(void) {
  char file[_MAX_PATH * 2];

  ddio_MakePath(file, Base_directory, "custom", "settings", NULL);
  if (DoPathFileDialog(false, file, TXT_MULTILOADSET, "*.mps", PFDF_FILEMUSTEXIST))
    MultiLoadSettings(file);
}

#define CHAR_LEFT_ARROW 24
#define CHAR_UP_ARROW 25
#define CHAR_RIGHT_ARROW 26
#define CHAR_DOWN_ARROW 27
#define CHAR_CHECKBOX_OFF 28
#define CHAR_CHECKBOX_ON 29
#define CHAR_RADIO_OFF 30
#define CHAR_RADIO_ON 31

#define CS_MODE_HS_ID 20
#define PP_MODE_HS_ID 21
#define ROT_VEL_HS_ID 22
#define ACC_WEAP_HS_ID 24
#define BRIGHT_SHIP_HS_ID 25
#define RAND_POWERUP_ID 26
#define PS_MODE_HS_ID 27
#define MLOOK_HS_ID 28
#define DIFF_LIST_ID 30
#define SHIP_ALLOW_HS_ID 0xdd

void MultiGameOptionsMenu(int alloptions) {

#define MULTI_OPT_TITLE_Y 30
#define MULTI_OPT_EDITS_Y 80
#define MULTI_OPT_EDITS_X_LCOL1 40
#define MULTI_OPT_EDITS_X_COL1 160
#define MULTI_OPT_EDITS_X_LCOL2 300
#define MULTI_OPT_EDITS_X_COL2 460
#define MULTI_OPT_TOGGLES_Y 210
#define MULTI_OPT_TOGGLES_X 40
#define MULTI_OPT_TOGGLES_COL2_X 300
#define MULTI_OPT_LABEL_OFS 10
#define MULTI_OPT_HOTSPOT_X_MID 410
#define MULTI_OPT_HOTSPOT_Y 360

  UITextItem options_title_text(BIG_BRIEFING_FONT, TXT_GEN_MPLYROPTIONS, UICOL_WINDOW_TITLE);
  UITextItem time_limit_text(TXT_GEN_TIMELIMIT, UICOL_TEXT_NORMAL);
  UITextItem kill_goal_text(TXT_GEN_KILLGOAL, UICOL_TEXT_NORMAL);
  UITextItem pps_text(TXT_GEN_PPS, UICOL_TEXT_NORMAL);
  UITextItem respawn_rate_text(TXT_GEN_RESPAWNRATE, UICOL_TEXT_NORMAL);
  UITextItem max_players_text(TXT_GEN_MAXPLAYERS, UICOL_TEXT_NORMAL);

  UITextItem exit_on_text(TXT_DONE, UICOL_HOTSPOT_HI);
  UITextItem exit_off_text(TXT_DONE, UICOL_HOTSPOT_LO);

  UITextItem cancel_on_text(TXT_CANCEL, UICOL_HOTSPOT_HI);
  UITextItem cancel_off_text(TXT_CANCEL, UICOL_HOTSPOT_LO);

  UITextItem ship_on_text(TXT_GEN_CFGALLOWEDSHIP, UICOL_HOTSPOT_HI);
  UITextItem ship_off_text(TXT_GEN_CFGALLOWEDSHIP, UICOL_HOTSPOT_LO);

  UITextItem blank_text("", UICOL_TEXT_NORMAL);

  char str[100];

  int cancel_id;
  rendering_state rs;
  rend_GetRenderState(&rs);

  NewUIWindow main_wnd;
  main_wnd.Create(0, 0, rs.screen_width, rs.screen_height, UIF_PROCESS_ALL);

  int num_text = 0, num_edit = 0;
  int return_id;
  int id = 0;

  UIText title_txt;
  title_txt.Create(&main_wnd, &options_title_text, 0, MULTI_OPT_TITLE_Y, UIF_CENTER);
  int cury = MULTI_OPT_EDITS_Y;
  // Time limit
  UIText time_limit;
  time_limit.Create(&main_wnd, &time_limit_text, MULTI_OPT_EDITS_X_LCOL1, cury + MULTI_OPT_LABEL_OFS, 0);
  NewUIEdit time_limit_edit;
  time_limit_edit.Create(&main_wnd, id++, MULTI_OPT_EDITS_X_COL1, cury, 100, 15, 0);
  cury += 20;
  cury += 20;

  // Kill goal
  UIText kill_goal;
  kill_goal.Create(&main_wnd, &kill_goal_text, MULTI_OPT_EDITS_X_LCOL1, cury + MULTI_OPT_LABEL_OFS, 0);
  NewUIEdit kill_goal_edit;
  kill_goal_edit.Create(&main_wnd, id++, MULTI_OPT_EDITS_X_COL1, cury, 100, 15, 0);
  cury += 20;
  cury += 20;
  NewUIEdit max_players_edit;
  UIText max_players;
  if (alloptions) {
    // Max Players
    max_players.Create(&main_wnd, &max_players_text, MULTI_OPT_EDITS_X_LCOL1, cury + MULTI_OPT_LABEL_OFS, 0);
    max_players_edit.Create(&main_wnd, id++, MULTI_OPT_EDITS_X_COL1, cury, 100, 15, 0);
    cury += 20;
  }
  cury += 20;

  cury = MULTI_OPT_EDITS_Y;

  // Packets per second
  UIText pps;
  pps.Create(&main_wnd, &pps_text, MULTI_OPT_EDITS_X_LCOL2, cury + MULTI_OPT_LABEL_OFS, 0);
  NewUIEdit pps_edit;
  pps_edit.Create(&main_wnd, id++, MULTI_OPT_EDITS_X_COL2, cury, 100, 15, 0);
  cury += 20;
  cury += 20;

  // Respawn rate
  UIText respawn;
  respawn.Create(&main_wnd, &respawn_rate_text, MULTI_OPT_EDITS_X_LCOL2, cury + MULTI_OPT_LABEL_OFS, 0);
  NewUIEdit respawn_edit;
  respawn_edit.Create(&main_wnd, id++, MULTI_OPT_EDITS_X_COL2, cury, 100, 15, 0);
  cury += 20;

  cury = MULTI_OPT_TOGGLES_Y;
  UIHotspot cs_mode_hs;
  UIHotspot pp_mode_hs;
  UIHotspot pcs_mode_hs;
  snprintf(str, sizeof(str), "%c %s", CHAR_CHECKBOX_ON, TXT_GEN_USEROTVEL);
  UITextItem rot_vel_sel_txt_on(str, UICOL_HOTSPOT_LO);
  UITextItem rot_vel_sel_txt_off(str, UICOL_HOTSPOT_LO);

  snprintf(str, sizeof(str), "%c %s", CHAR_CHECKBOX_OFF, TXT_GEN_USEROTVEL);
  UITextItem rot_vel_unsel_txt_on(str, UICOL_HOTSPOT_LO);
  UITextItem rot_vel_unsel_txt_off(str, UICOL_HOTSPOT_LO);

  snprintf(str, sizeof(str), "%c %s", CHAR_CHECKBOX_ON, TXT_GEN_BRIGHT_PLAYERS);
  UITextItem bright_players_sel_on(str, UICOL_HOTSPOT_LO);
  UITextItem bright_players_sel_off(str, UICOL_HOTSPOT_LO);

  snprintf(str, sizeof(str), "%c %s", CHAR_CHECKBOX_OFF, TXT_GEN_BRIGHT_PLAYERS);
  UITextItem bright_players_unsel_on(str, UICOL_HOTSPOT_LO);
  UITextItem bright_players_unsel_off(str, UICOL_HOTSPOT_LO);

  snprintf(str, sizeof(str), "%c %s", CHAR_RADIO_ON, TXT_GEN_CLIENTSERVER);
  UITextItem cs_mode_sel_text_on(str, UICOL_HOTSPOT_HI);
  UITextItem cs_mode_sel_text_off(str, UICOL_HOTSPOT_LO);

  snprintf(str, sizeof(str), "%c %s", CHAR_RADIO_OFF, TXT_GEN_CLIENTSERVER);
  UITextItem cs_mode_unsel_text_on(str, UICOL_HOTSPOT_HI);
  UITextItem cs_mode_unsel_text_off(str, UICOL_HOTSPOT_LO);

  snprintf(str, sizeof(str), "%c %s", CHAR_RADIO_ON, TXT_GEN_PEERPEER);
  UITextItem pp_mode_sel_text_on(str, UICOL_HOTSPOT_HI);
  UITextItem pp_mode_sel_text_off(str, UICOL_HOTSPOT_LO);

  snprintf(str, sizeof(str), "%c %s", CHAR_RADIO_OFF, TXT_GEN_PEERPEER);
  UITextItem pp_mode_unsel_text_on(str, UICOL_HOTSPOT_HI);
  UITextItem pp_mode_unsel_text_off(str, UICOL_HOTSPOT_LO);

  snprintf(str, sizeof(str), "%c %s", CHAR_RADIO_ON, TXT_GEN_PERMISSABLE_CS);
  UITextItem pcs_mode_sel_text_on(str, UICOL_HOTSPOT_HI);
  UITextItem pcs_mode_sel_text_off(str, UICOL_HOTSPOT_LO);

  snprintf(str, sizeof(str), "%c %s", CHAR_RADIO_OFF, TXT_GEN_PERMISSABLE_CS);
  UITextItem pcs_mode_unsel_text_on(str, UICOL_HOTSPOT_HI);
  UITextItem pcs_mode_unsel_text_off(str, UICOL_HOTSPOT_LO);

  snprintf(str, sizeof(str), TXT_GEN_ACC_WEAP_COLL, CHAR_CHECKBOX_ON);
  UITextItem acc_weap_coll_sel_off(str, UICOL_HOTSPOT_LO);
  UITextItem acc_weap_coll_sel_on(str, UICOL_HOTSPOT_HI);

  snprintf(str, sizeof(str), TXT_GEN_ACC_WEAP_COLL, CHAR_CHECKBOX_OFF);
  UITextItem acc_weap_coll_unsel_off(str, UICOL_HOTSPOT_LO);
  UITextItem acc_weap_coll_unsel_on(str, UICOL_HOTSPOT_HI);

  snprintf(str, sizeof(str), "%c %s", CHAR_CHECKBOX_ON, TXT_RANDOMPOWERUPRESPAWN);
  UITextItem powerup_respawn_sel_off(str, UICOL_HOTSPOT_LO);
  UITextItem powerup_respawn_sel_on(str, UICOL_HOTSPOT_HI);

  snprintf(str, sizeof(str), "%c %s", CHAR_CHECKBOX_OFF, TXT_RANDOMPOWERUPRESPAWN);
  UITextItem powerup_respawn_unsel_off(str, UICOL_HOTSPOT_LO);
  UITextItem powerup_respawn_unsel_on(str, UICOL_HOTSPOT_HI);

  snprintf(str, sizeof(str), "%c %s", CHAR_CHECKBOX_ON, TXT_ALLOWMLOOK);
  UITextItem mouselookers_sel_off(str, UICOL_HOTSPOT_LO);
  UITextItem mouselookers_sel_on(str, UICOL_HOTSPOT_HI);

  snprintf(str, sizeof(str), "%c %s", CHAR_CHECKBOX_OFF, TXT_ALLOWMLOOK);
  UITextItem mouselookers_unsel_off(str, UICOL_HOTSPOT_LO);
  UITextItem mouselookers_unsel_on(str, UICOL_HOTSPOT_HI);

  int cs_y;
  int pp_y;
  int pcs_y;
  UIHotspot rot_vel_hs;
  UIHotspot acc_weap_hs;
  UIHotspot powerup_hs;
  UIHotspot mlook_hs;
  UIHotspot bright_players_hs;

  int rotvely;
  int acc_weap_y;
  int powerup_y;
  int mlook_y;
  int bright_players_y;
  int diff_y;

  cury -= 15;
  diff_y = cury;
  if (alloptions) {

    cury += 15;
    if (Netgame.flags & NF_PEER_PEER) {
      cs_mode_hs.Create(&main_wnd, CS_MODE_HS_ID, KEY_C, &cs_mode_unsel_text_off, &cs_mode_unsel_text_on,
                        MULTI_OPT_TOGGLES_X, cury, 180, 30, UIF_FIT);
      cs_y = cury;
      cury += 20;

      pp_mode_hs.Create(&main_wnd, PP_MODE_HS_ID, KEY_C, &pp_mode_sel_text_off, &pp_mode_sel_text_on,
                        MULTI_OPT_TOGGLES_X, cury, 180, 30, UIF_FIT);
      pp_y = cury;
      cury += 20;

      pcs_mode_hs.Create(&main_wnd, PS_MODE_HS_ID, KEY_C, &pcs_mode_unsel_text_off, &pcs_mode_unsel_text_on,
                         MULTI_OPT_TOGGLES_X, cury, 180, 30, UIF_FIT);
      pcs_y = cury;
      cury += 20;
    } else if (Netgame.flags & NF_PERMISSABLE) {
      ////
      cs_mode_hs.Create(&main_wnd, CS_MODE_HS_ID, KEY_C, &cs_mode_unsel_text_off, &cs_mode_unsel_text_on,
                        MULTI_OPT_TOGGLES_X, cury, 180, 30, UIF_FIT);
      cs_y = cury;
      cury += 20;

      pp_mode_hs.Create(&main_wnd, PP_MODE_HS_ID, KEY_C, &pp_mode_unsel_text_off, &pp_mode_unsel_text_on,
                        MULTI_OPT_TOGGLES_X, cury, 180, 30, UIF_FIT);
      pp_y = cury;
      cury += 20;

      pcs_mode_hs.Create(&main_wnd, PS_MODE_HS_ID, KEY_C, &pcs_mode_sel_text_off, &pcs_mode_sel_text_on,
                         MULTI_OPT_TOGGLES_X, cury, 180, 30, UIF_FIT);
      pcs_y = cury;
      cury += 20;
    } else {
      cs_mode_hs.Create(&main_wnd, CS_MODE_HS_ID, KEY_C, &cs_mode_sel_text_off, &cs_mode_sel_text_on,
                        MULTI_OPT_TOGGLES_X, cury, 180, 30, UIF_FIT);
      cs_y = cury;
      cury += 20;
      pp_mode_hs.Create(&main_wnd, PP_MODE_HS_ID, KEY_C, &pp_mode_unsel_text_off, &pp_mode_unsel_text_on,
                        MULTI_OPT_TOGGLES_X, cury, 180, 30, UIF_FIT);
      pp_y = cury;
      cury += 20;

      pcs_mode_hs.Create(&main_wnd, PS_MODE_HS_ID, KEY_C, &pcs_mode_unsel_text_off, &pcs_mode_unsel_text_on,
                         MULTI_OPT_TOGGLES_X, cury, 180, 30, UIF_FIT);
      pcs_y = cury;
      cury += 20;
    }

    cury += 10;
    diff_y = cury;

    // Rotvel toggle

    cury = MULTI_OPT_TOGGLES_Y;
    if (Netgame.flags & NF_SENDROTVEL) {
      rot_vel_hs.Create(&main_wnd, ROT_VEL_HS_ID, 0, &rot_vel_sel_txt_off, &rot_vel_sel_txt_on,
                        MULTI_OPT_TOGGLES_COL2_X, cury, 180, 30, UIF_FIT);
    } else {
      rot_vel_hs.Create(&main_wnd, ROT_VEL_HS_ID, 0, &rot_vel_unsel_txt_off, &rot_vel_unsel_txt_on,
                        MULTI_OPT_TOGGLES_COL2_X, cury, 180, 30, UIF_FIT);
    }
    rotvely = cury;
    cury += 20;
  }
  // Accurate collisions toggle
  if (Netgame.flags & NF_USE_ACC_WEAP) {
    acc_weap_hs.Create(&main_wnd, ACC_WEAP_HS_ID, KEY_A, &acc_weap_coll_sel_off, &acc_weap_coll_sel_on,
                       MULTI_OPT_TOGGLES_COL2_X, cury, 180, 30, UIF_FIT);
  } else {
    acc_weap_hs.Create(&main_wnd, ACC_WEAP_HS_ID, KEY_A, &acc_weap_coll_unsel_off, &acc_weap_coll_unsel_on,
                       MULTI_OPT_TOGGLES_COL2_X, cury, 180, 30, UIF_FIT);
  }
  acc_weap_y = cury;
  cury += 20;

  // Bright players toggle

  if (Netgame.flags & NF_BRIGHT_PLAYERS) {
    bright_players_hs.Create(&main_wnd, BRIGHT_SHIP_HS_ID, KEY_B, &bright_players_sel_off, &bright_players_sel_on,
                             MULTI_OPT_TOGGLES_COL2_X, cury, 180, 30, UIF_FIT);
  } else {
    bright_players_hs.Create(&main_wnd, BRIGHT_SHIP_HS_ID, KEY_B, &bright_players_unsel_off, &bright_players_unsel_on,
                             MULTI_OPT_TOGGLES_COL2_X, cury, 180, 30, UIF_FIT);
  }
  bright_players_y = cury;
  cury += 20;

  if (Netgame.flags & NF_RANDOMIZE_RESPAWN) {
    powerup_hs.Create(&main_wnd, RAND_POWERUP_ID, KEY_B, &powerup_respawn_sel_off, &powerup_respawn_sel_on,
                      MULTI_OPT_TOGGLES_COL2_X, cury, 180, 30, UIF_FIT);
  } else {
    powerup_hs.Create(&main_wnd, RAND_POWERUP_ID, KEY_B, &powerup_respawn_unsel_off, &powerup_respawn_unsel_on,
                      MULTI_OPT_TOGGLES_COL2_X, cury, 180, 30, UIF_FIT);
  }
  powerup_y = cury;
  cury += 20;

  if (Netgame.flags & NF_ALLOW_MLOOK) {
    mlook_hs.Create(&main_wnd, MLOOK_HS_ID, KEY_B, &mouselookers_sel_off, &mouselookers_sel_on,
                    MULTI_OPT_TOGGLES_COL2_X, cury, 180, 30, UIF_FIT);
  } else {
    mlook_hs.Create(&main_wnd, MLOOK_HS_ID, KEY_B, &mouselookers_unsel_off, &mouselookers_unsel_on,
                    MULTI_OPT_TOGGLES_COL2_X, cury, 180, 30, UIF_FIT);
  }
  mlook_y = cury;
  cury += 20;

  // Difficulty Listbox & title
  UITextItem diff_title_text(TXT_PLTDIFFICULT, UICOL_WINDOW_TITLE);
  UITextItem trainee(TXT_TRAINEE, GR_LIGHTGRAY);
  UITextItem rookie(TXT_ROOKIE, GR_LIGHTGRAY);
  UITextItem hotshot(TXT_HOTSHOT, GR_LIGHTGRAY);
  UITextItem ace(TXT_ACE, GR_LIGHTGRAY);
  UITextItem insane(TXT_INSANE, GR_LIGHTGRAY);

  UIText diff_title;

  diff_title.Create(&main_wnd, &diff_title_text, MULTI_OPT_TOGGLES_X, diff_y, 0);
  diff_y += 15;
  NewUIListBox diff_list;

  diff_list.SetSelectedColor(UICOL_LISTBOX_HI);
  diff_list.SetHiliteColor(UICOL_LISTBOX_HI);
  diff_list.Create(&main_wnd, DIFF_LIST_ID, MULTI_OPT_TOGGLES_X, diff_y, 160, 96, UILB_NOSORT);

  diff_list.AddItem(&trainee);
  diff_list.AddItem(&rookie);
  diff_list.AddItem(&hotshot);
  diff_list.AddItem(&ace);
  diff_list.AddItem(&insane);

  switch (Netgame.difficulty) {
  case 0:
    diff_list.SelectItem(&trainee);
    break;
  case 1:
    diff_list.SelectItem(&rookie);
    break;
  case 2:
    diff_list.SelectItem(&hotshot);
    break;
  case 3:
    diff_list.SelectItem(&ace);
    break;
  case 4:
    diff_list.SelectItem(&insane);
    break;
  }

  cury = MULTI_OPT_HOTSPOT_Y;
  // int hsmid = MULTI_OPT_HOTSPOT_X_MID - (DLLgrtext_GetTextLineWidth(TXT_GEN_CFGALLOWEDSHIP)/2);
  UIHotspot ship_hs;
  ship_hs.Create(&main_wnd, SHIP_ALLOW_HS_ID, KEY_S, &ship_off_text, &ship_on_text, 0, cury, 180, 30,
                 UIF_FIT | UIF_CENTER);
  cury += 20;
  return_id = UID_OK;
  cury += 10;
  // hsmid = MULTI_OPT_HOTSPOT_X_MID - (DLLgrtext_GetTextLineWidth(TXT_GEN_PREVMENU)/2);
  UIHotspot exit_hs;
  exit_hs.Create(&main_wnd, UID_OK, KEY_ESC, &exit_off_text, &exit_on_text, 0, cury, 180, 30, UIF_FIT | UIF_CENTER);
  cury += 20;
  cancel_id = UID_CANCEL;
  ///	hsmid = MULTI_OPT_HOTSPOT_X_MID - (DLLgrtext_GetTextLineWidth(TXT_GEN_CANCEL)/2);
  UIHotspot cancel_hs;
  cancel_hs.Create(&main_wnd, UID_CANCEL, 0, &cancel_off_text, &cancel_on_text, 0, cury, 180, 30, UIF_FIT | UIF_CENTER);
  cury += 20;
  // Bash some values

  if (Netgame.flags & NF_TIMER)
    snprintf(str, sizeof(str), "%d", Netgame.timelimit);
  else
    snprintf(str, sizeof(str), "%d", 0);

  time_limit_edit.SetText(str);

  if (Netgame.flags & NF_KILLGOAL)
    snprintf(str, sizeof(str), "%d", Netgame.killgoal);
  else
    snprintf(str, sizeof(str), "%d", 0);

  kill_goal_edit.SetText(str);

  snprintf(str, sizeof(str), "%d", Netgame.packets_per_second);
  pps_edit.SetText(str);

  snprintf(str, sizeof(str), "%d", Netgame.max_players);
  if (alloptions) {
    max_players_edit.SetText(str);
  }

  snprintf(str, sizeof(str), "%d", Netgame.respawn_time);
  respawn_edit.SetText(str);

  main_wnd.LoadBackgroundImage("multimain.ogf");
  main_wnd.Open();
  int exit_menu = 0;

  while (!exit_menu) {
    int res;

    res = DoUI();
    if (res == cancel_id) {
      exit_menu = true;
      break;
    }
    if (alloptions) {
      if (res == CS_MODE_HS_ID) {
        cs_mode_hs.Destroy();
        pp_mode_hs.Destroy();
        pcs_mode_hs.Destroy();

        cs_mode_hs.Create(&main_wnd, CS_MODE_HS_ID, KEY_C, &cs_mode_sel_text_off, &cs_mode_sel_text_on,
                          MULTI_OPT_TOGGLES_X, cs_y, 180, 30, UIF_FIT);
        pp_mode_hs.Create(&main_wnd, PP_MODE_HS_ID, KEY_C, &pp_mode_unsel_text_off, &pp_mode_unsel_text_on,
                          MULTI_OPT_TOGGLES_X, pp_y, 180, 30, UIF_FIT);
        pcs_mode_hs.Create(&main_wnd, PS_MODE_HS_ID, KEY_C, &pcs_mode_unsel_text_off, &pcs_mode_unsel_text_on,
                           MULTI_OPT_TOGGLES_X, pcs_y, 180, 30, UIF_FIT);
        Netgame.flags &= ~NF_PEER_PEER;
        Netgame.flags &= ~NF_PERMISSABLE;
        mprintf(0, "Using Client/Server model\n");
      } else if (res == PP_MODE_HS_ID) {
        cs_mode_hs.Destroy();
        pp_mode_hs.Destroy();
        pcs_mode_hs.Destroy();

        cs_mode_hs.Create(&main_wnd, CS_MODE_HS_ID, KEY_C, &cs_mode_unsel_text_off, &cs_mode_unsel_text_on,
                          MULTI_OPT_TOGGLES_X, cs_y, 180, 30, UIF_FIT);
        pp_mode_hs.Create(&main_wnd, PP_MODE_HS_ID, KEY_C, &pp_mode_sel_text_off, &pp_mode_sel_text_on,
                          MULTI_OPT_TOGGLES_X, pp_y, 180, 30, UIF_FIT);
        pcs_mode_hs.Create(&main_wnd, PS_MODE_HS_ID, KEY_C, &pcs_mode_unsel_text_off, &pcs_mode_unsel_text_on,
                           MULTI_OPT_TOGGLES_X, pcs_y, 180, 30, UIF_FIT);
        Netgame.flags |= NF_PEER_PEER;
        Netgame.flags &= ~NF_PERMISSABLE;

        mprintf(0, "Using Peer/Peer model\n");
      } else if (res == PS_MODE_HS_ID) {
        cs_mode_hs.Destroy();
        pp_mode_hs.Destroy();
        pcs_mode_hs.Destroy();

        cs_mode_hs.Create(&main_wnd, CS_MODE_HS_ID, KEY_C, &cs_mode_unsel_text_off, &cs_mode_unsel_text_on,
                          MULTI_OPT_TOGGLES_X, cs_y, 180, 30, UIF_FIT);
        pp_mode_hs.Create(&main_wnd, PP_MODE_HS_ID, KEY_C, &pp_mode_unsel_text_off, &pp_mode_unsel_text_on,
                          MULTI_OPT_TOGGLES_X, pp_y, 180, 30, UIF_FIT);
        pcs_mode_hs.Create(&main_wnd, PS_MODE_HS_ID, KEY_C, &pcs_mode_sel_text_off, &pcs_mode_sel_text_on,
                           MULTI_OPT_TOGGLES_X, pcs_y, 180, 30, UIF_FIT);
        Netgame.flags |= NF_PERMISSABLE;
        Netgame.flags &= ~NF_PEER_PEER;

        mprintf(0, "Using Permissable model\n");
      } else if (res == ROT_VEL_HS_ID) {
        rot_vel_hs.Destroy();

        if (Netgame.flags & NF_SENDROTVEL) {
          rot_vel_hs.Create(&main_wnd, ROT_VEL_HS_ID, 0, &rot_vel_unsel_txt_off, &rot_vel_unsel_txt_on,
                            MULTI_OPT_TOGGLES_COL2_X, rotvely, 180, 30, UIF_FIT);
          Netgame.flags &= ~NF_SENDROTVEL;
        } else {
          rot_vel_hs.Create(&main_wnd, ROT_VEL_HS_ID, 0, &rot_vel_sel_txt_off, &rot_vel_sel_txt_on,
                            MULTI_OPT_TOGGLES_COL2_X, rotvely, 180, 30, UIF_FIT);
          Netgame.flags |= NF_SENDROTVEL;
        }
      }
    }

    if (res == SHIP_ALLOW_HS_ID) {
      // Ships allowed
      main_wnd.Close();
      DoMultiAllowed();
      main_wnd.Open();
    } else if (res == ACC_WEAP_HS_ID) {
      acc_weap_hs.Destroy();
      if (Netgame.flags & NF_USE_ACC_WEAP) {
        acc_weap_hs.Create(&main_wnd, ACC_WEAP_HS_ID, KEY_A, &acc_weap_coll_unsel_off, &acc_weap_coll_unsel_on,
                           MULTI_OPT_TOGGLES_COL2_X, acc_weap_y, 180, 30, UIF_FIT);
        Netgame.flags &= ~NF_USE_ACC_WEAP;
      } else {
        acc_weap_hs.Create(&main_wnd, ACC_WEAP_HS_ID, KEY_A, &acc_weap_coll_sel_off, &acc_weap_coll_sel_on,
                           MULTI_OPT_TOGGLES_COL2_X, acc_weap_y, 180, 30, UIF_FIT);
        Netgame.flags |= NF_USE_ACC_WEAP;
      }

    } else if (res == BRIGHT_SHIP_HS_ID) {
      bright_players_hs.Destroy();

      if (Netgame.flags & NF_BRIGHT_PLAYERS) {
        bright_players_hs.Create(&main_wnd, BRIGHT_SHIP_HS_ID, KEY_B, &bright_players_unsel_off,
                                 &bright_players_unsel_on, MULTI_OPT_TOGGLES_COL2_X, bright_players_y, 180, 30,
                                 UIF_FIT);
        Netgame.flags &= ~NF_BRIGHT_PLAYERS;
      } else {
        bright_players_hs.Create(&main_wnd, BRIGHT_SHIP_HS_ID, KEY_B, &bright_players_sel_off, &bright_players_sel_on,
                                 MULTI_OPT_TOGGLES_COL2_X, bright_players_y, 180, 30, UIF_FIT);
        Netgame.flags |= NF_BRIGHT_PLAYERS;
      }
    }

    else if (res == RAND_POWERUP_ID) {
      powerup_hs.Destroy();

      if (Netgame.flags & NF_RANDOMIZE_RESPAWN) {
        powerup_hs.Create(&main_wnd, RAND_POWERUP_ID, KEY_B, &powerup_respawn_unsel_off, &powerup_respawn_unsel_on,
                          MULTI_OPT_TOGGLES_COL2_X, powerup_y, 180, 30, UIF_FIT);
        Netgame.flags &= ~NF_RANDOMIZE_RESPAWN;
      } else {
        powerup_hs.Create(&main_wnd, RAND_POWERUP_ID, KEY_B, &powerup_respawn_sel_off, &powerup_respawn_sel_on,
                          MULTI_OPT_TOGGLES_COL2_X, powerup_y, 180, 30, UIF_FIT);
        Netgame.flags |= NF_RANDOMIZE_RESPAWN;
      }
    }

    else if (res == MLOOK_HS_ID) {
      mlook_hs.Destroy();

      if (Netgame.flags & NF_ALLOW_MLOOK) {
        mlook_hs.Create(&main_wnd, MLOOK_HS_ID, KEY_B, &mouselookers_unsel_off, &mouselookers_unsel_on,
                        MULTI_OPT_TOGGLES_COL2_X, mlook_y, 180, 30, UIF_FIT);
        Netgame.flags &= ~NF_ALLOW_MLOOK;
      } else {
        mlook_hs.Create(&main_wnd, MLOOK_HS_ID, KEY_B, &mouselookers_sel_off, &mouselookers_sel_on,
                        MULTI_OPT_TOGGLES_COL2_X, mlook_y, 180, 30, UIF_FIT);
        Netgame.flags |= NF_ALLOW_MLOOK;
      }
    } else if (res == return_id) {
      int val;

      // Get kill goal
      // edits[killgoal_edit].GetText (str,100);
      kill_goal_edit.GetText(str, 100);
      val = atoi(str);
      if (val > 1) {
        if (val > 10000)
          val = 10000;
        Netgame.flags |= NF_KILLGOAL;
      } else {
        Netgame.flags &= ~NF_KILLGOAL;
        val = 0;
      }

      Netgame.killgoal = val;

      // Get timelimit
      // edits[timer_edit].GetText (str,100);
      time_limit_edit.GetText(str, 100);
      val = atoi(str);
      if (val > 0) {
        if (val > 10000)
          val = 10000;
        Netgame.flags |= NF_TIMER;
      } else {
        Netgame.flags &= ~NF_TIMER;
        val = 0;
      }

      Netgame.timelimit = val;

      // Get packets per second
      pps_edit.GetText(str, 100);
      val = atoi(str);
      Netgame.packets_per_second = val;
      if (val > 20)
        val = 20;
      if (val < 2)
        val = 2;

      if (alloptions) {
        // Get Max players
        max_players_edit.GetText(str, 100);
        val = atoi(str);
        Netgame.max_players = val;
        if (val > MAX_NET_PLAYERS)
          Netgame.max_players = MAX_NET_PLAYERS;
        if (val < 2)
          val = 2;
      }
      // Get respawn rate
      // edits[respawn_edit].GetText (str,100);
      respawn_edit.GetText(str, 100);
      val = atoi(str);
      if (val < 15)
        val = 15;
      if (val > 300)
        val = 300;

      Netgame.respawn_time = val;

      int difficulty = diff_list.GetSelectedIndex();

      Netgame.difficulty = difficulty;

      exit_menu = 1;
    }
  }

  main_wnd.Close();
  main_wnd.Destroy();
}

int ReturnMultiplayerGameMenu(void) {
  MultiFlushAllIncomingBuffers();
  CallMultiDLL(MT_RETURN_TO_GAME_LIST);
  return MultiDLLGameStarting;
}

int MultiLevelSelection(void) {
  if (Current_mission.num_levels == 1)
    return 1;

  Current_mission.cur_level = DisplayLevelWarpDlg(Current_mission.num_levels);

  if (Current_mission.cur_level < 1) {
    Current_mission.cur_level = 1;
    return -1;
  }
  return Current_mission.cur_level;
}

bool DoPlayerMouselookCheck(uint32_t flags) {
  if (Current_pilot.mouselook_control) {
    if (flags & NF_ALLOW_MLOOK) {
      return true;
    } else {
      int ret = DoMessageBox(TXT_NOMOUSELOOK, TXT_MLOOK_JOINANYWAY, MSGBOX_YESNO);
      return ret ? true : false;
    }
  }

  return true;
}

#define GAME_INFO_MENU_W 384
#define GAME_INFO_MENU_H 384
#define GAME_INFO_MENU_X 320 - (GAME_INFO_MENU_W / 2)
#define GAME_INFO_MENU_Y 240 - (GAME_INFO_MENU_H / 2)

#define GAME_INFO_COL1 10

#define GAME_INFO_GOTO_NEXT_LINE cury += 13

#define UID_GAMEINFO_PLAYERS 1000

extern char *Multi_recieved_player_list;
extern bool Multi_got_player_list;

void RequestPlayerList(network_address *addr);

#define ASK_PLAYERS_RETRY_INTERVAL 2.0
#define ASK_PLAYERS_RETRIES 4

// Display a dialog box showing the information relating to this particular net game
void ShowNetgameInfo(network_game *game) {
  char str[200];
  int cury = 10;
  int exit_menu = 0;
  newuiTiledWindow menu_wnd;
  newuiListBox *lists;
  newuiSheet *sheet;
  char *plyr;

  ASSERT(game);

  menu_wnd.Create(TXT_GAME_INFO, 0, 0, GAME_INFO_MENU_W, GAME_INFO_MENU_H);
  sheet = menu_wnd.GetSheet();

  sheet->NewGroup(game->name, GAME_INFO_COL1, cury);
  cury += 15;
  snprintf(str, sizeof(str), TXT_GINFO_MISSION, game->mission_name);
  sheet->NewGroup(str, GAME_INFO_COL1, cury);
  GAME_INFO_GOTO_NEXT_LINE;

  snprintf(str, sizeof(str), TXT_PLAYERS_X_OF_X, game->curr_num_players, game->max_num_players);
  sheet->NewGroup(str, GAME_INFO_COL1, cury);
  GAME_INFO_GOTO_NEXT_LINE;

  const char *szdiff = TXT_ERROR;

  switch (game->difficulty) {
  case 0:
    szdiff = TXT_TRAINEE;
    break;
  case 1:
    szdiff = TXT_ROOKIE;
    break;
  case 2:
    szdiff = TXT_HOTSHOT;
    break;
  case 3:
    szdiff = TXT_ACE;
    break;
  case 4:
    szdiff = TXT_INSANE;
    break;
  default:
    szdiff = TXT_ERROR;
  }

  snprintf(str, sizeof(str), "%s: %s", TXT_PLTDIFFICULT, szdiff);
  sheet->NewGroup(str, GAME_INFO_COL1, cury);
  GAME_INFO_GOTO_NEXT_LINE;

  const char *mode;
  if ((game->flags & NF_PEER_PEER)) {
    mode = TXT_GEN_PEERPEER;
  } else if ((game->flags & NF_PERMISSABLE)) {
    mode = TXT_GEN_PERMISSABLE_CS;
  } else {
    mode = TXT_GEN_CLIENTSERVER;
  }

  if (game->dedicated_server)
    snprintf(str, sizeof(str), TXT_DEDICATED_SERVER, mode);
  else
    snprintf(str, sizeof(str), TXT_NONDEDICATED_SERVER, mode);
  sheet->NewGroup(str, GAME_INFO_COL1, cury);
  GAME_INFO_GOTO_NEXT_LINE;

  snprintf(str, sizeof(str), TXT_GINFO_ALLOWMOUSELOOK, (game->flags & NF_ALLOW_MLOOK) ? TXT_DOES : TXT_DOESNOT);
  sheet->NewGroup(str, GAME_INFO_COL1, cury);
  GAME_INFO_GOTO_NEXT_LINE;

  snprintf(str, sizeof(str), "%s: %s", TXT_GEN_BRIGHT_PLAYERS, (game->flags & NF_BRIGHT_PLAYERS) ? TXT_ON : TXT_OFF);
  sheet->NewGroup(str, GAME_INFO_COL1, cury);
  GAME_INFO_GOTO_NEXT_LINE;

  snprintf(str, sizeof(str), TXT_GINFO_ACC_WEAPCOLL, (game->flags & NF_USE_ACC_WEAP) ? TXT_ON : TXT_OFF);
  sheet->NewGroup(str, GAME_INFO_COL1, cury);
  GAME_INFO_GOTO_NEXT_LINE;

  snprintf(str, sizeof(str), TXT_USE_ROTATIONAL_VEL, (game->flags & NF_SENDROTVEL) ? TXT_ON : TXT_OFF);
  sheet->NewGroup(str, GAME_INFO_COL1, cury);
  GAME_INFO_GOTO_NEXT_LINE;

  snprintf(str, sizeof(str), TXT_RANDOMIZEPOWERUPSPAWN, (game->flags & NF_RANDOMIZE_RESPAWN) ? TXT_ON : TXT_OFF);
  sheet->NewGroup(str, GAME_INFO_COL1, cury);
  GAME_INFO_GOTO_NEXT_LINE;

  // GAME_INFO_GOTO_NEXT_LINE;

  snprintf(str, sizeof(str), "%s:", TXT_GAMEINFOPLAYERSTITLE);
  sheet->NewGroup(str, GAME_INFO_COL1, cury);
  GAME_INFO_GOTO_NEXT_LINE;

  lists = sheet->AddListBox(256, 128, UID_GAMEINFO_PLAYERS);
  lists->RemoveAll();

  sheet->NewGroup(NULL, (GAME_INFO_MENU_W - 140), GAME_INFO_MENU_H - 95, NEWUI_ALIGN_HORIZ);
  sheet->AddButton(TXT_DONE, UID_CANCEL);
  // Get players
  Multi_recieved_player_list = (char *)mem_malloc(((CALLSIGN_LEN + 1) * MAX_NET_PLAYERS) + 1);
  memset(Multi_recieved_player_list, 0, ((CALLSIGN_LEN + 1) * MAX_NET_PLAYERS) + 1);

  Multi_got_player_list = false;

  CreateSplashScreen(TXT_GETTINGPLAYERLIST, 1);

  RequestPlayerList(&game->addr);
  float last_asked_time = timer_GetTime();
  int retries = 0;
  do {
    MultiProcessIncoming();
    int res = PollUI();
    // If the user hit cancel...
    if (res == 99) {
      CloseSplashScreen();
      goto no_players;
    }
    if ((timer_GetTime() - last_asked_time) > ASK_PLAYERS_RETRY_INTERVAL) {
      last_asked_time = timer_GetTime();
      RequestPlayerList(&game->addr);
      retries++;
    }
    if (retries >= ASK_PLAYERS_RETRIES) {
      DoMessageBox(TXT_ERROR, TXT_CANTGETPLAYERLIST, MSGBOX_OK);
      CloseSplashScreen();
      goto no_players;
    }

  } while (!Multi_got_player_list);

  CloseSplashScreen();

  // Ok, now we've got the list of players.. let's parse it and add the players to the list
  plyr = Multi_recieved_player_list;

  while (*plyr) {
    lists->AddItem(plyr);
    // Move on to the next item
    while (*plyr) {
      plyr++;
    }
    // Move past the NULL
    plyr++;
  }

  if (Multi_recieved_player_list) {
    mem_free(Multi_recieved_player_list);
    Multi_recieved_player_list = NULL;
  }

  menu_wnd.Open();

  while (!exit_menu) {
    int res;

    res = menu_wnd.DoUI();

    // handle all UI results.
    switch (res) {
    case UID_CANCEL:
      menu_wnd.Close();
      exit_menu = 1;
      break;
    }
  }
  menu_wnd.Destroy();

no_players:
  if (Multi_recieved_player_list) {
    mem_free(Multi_recieved_player_list);
    Multi_recieved_player_list = NULL;
  }
}
