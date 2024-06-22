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

 * $Logfile: /DescentIII/Main/menu.cpp $
 * $Revision: 194 $
 * $Date: 10/17/01 3:43p $
 * $Author: Matt $
 *
 * main menu code
 *
 * $Log: /DescentIII/Main/menu.cpp $
 *
 * 194   10/17/01 3:43p Matt
 * Took out Kevin's -mission changes since we decided to change the readme
 * instead.
 *
 * 193   10/03/01 10:57p Kevin
 * fixed -mission
 *
 * 192   8/30/01 10:48a Matt
 * Check pilot command-line arg only once, not every time we go into main
 * menu.
 *
 * 191   4/19/00 5:17p Matt
 * From Duane for 1.4
 * Added Mac-only mem free
 *
 * 190   3/20/00 12:16p Matt
 * Merge of Duane's post-1.3 changes.
 * Index fix in building mission list (Mac only)
 *
 * 189   11/04/99 8:07a Kevin
 * don't put the player into the training mission the first time in if the
 * -mission flag was specified
 *
 * 188   10/25/99 9:51a Matt
 * Mac merge
 *
 * 187   8/02/99 10:31a Kevin
 * Fixed duplicate games in new game menu
 *
 * 186   7/30/99 1:49p Kevin
 * Fixed Mac related menu bug
 *
 * 185   7/28/99 4:04p Kevin
 * Macintosh!
 *
 * 184   5/25/99 3:44a Jeff
 * reset cheater flag when going into multiplayer game
 *
 * 183   5/24/99 2:12a Matt
 * Fixed stupid bug that caused -pilot to not work.
 *
 * 182   5/12/99 10:54a Kevin
 * When going to the load game screen from the main menu, always set the
 * game mode to none. In some cases where loading a multiplayer level
 * failed, the mode was still GM_MULTI
 *
 * 181   5/05/99 11:16p Kevin
 * heat.net stuff among other things
 *
 * 180   5/03/99 10:16p Kevin
 * added -pilot to work just like +name
 *
 * 179   5/03/99 3:35p Kevin
 * bug fixes
 *
 * 178   5/02/99 7:26p Samir
 * changed some sequencing so when finishing training mission, the main
 * menu does not pop up.
 *
 * 177   5/02/99 12:55a Jeff
 * save ship permissions at highest level achieved and use that on restore
 * to a level previously played
 *
 * 176   4/29/99 3:21a Samir
 * reorganized main menu music to work in config, multiplayer, whereever.
 *
 * 175   4/25/99 6:14p Kevin
 * added "-timetest file.dem" to behave like gamegauge does
 *
 * 174   4/20/99 7:30p Jeff
 * use last directory when displaying load level dialog
 *
 * 173   4/18/99 7:55p Samir
 * new progress indicator for delays when loading data.
 *
 * 172   4/17/99 3:44p Kevin
 * Demo2 changes & fixes
 *
 * 171   4/16/99 11:15p Jeff
 * itoa for linux added
 *
 * 170   4/16/99 6:00p Kevin
 * Bunches of Demo stuff
 *
 * 169   4/16/99 11:56a Matt
 * Changed directplay code to be "ifdef _WIN32" instead of "ifndef
 * __LINUX__" so it will work on the Mac.
 *
 * 168   4/15/99 1:40a Jeff
 * changes for linux compile
 *
 * 167   4/14/99 3:07p Kevin
 * Fixed some multiple CD bugs
 *
 * 166   4/14/99 2:51a Jeff
 * fixed some case mismatched #includes
 *
 * 165   4/08/99 3:12p Matt
 * Finished cleaning up level sequencing code.  Got rid of all the "level
 * minus one" stuff.
 *
 * 164   4/07/99 3:40p Kevin
 * Fixes for Beta 1
 *
 * 163   4/05/99 10:57a Samir
 * fixed potential crash in mission list generation.
 *
 * 162   3/31/99 3:04p Jeff
 * added _real_ temporary credits system...
 *
 * 161   3/29/99 5:32p Kevin
 * Build fixes
 *
 * 160   3/29/99 11:19a Matt
 * Fixed compile warning
 *
 * 159   3/24/99 2:58p Kevin
 * Doh! I forgot to save the files first!!@#@#$
 *
 * 158   3/24/99 2:56p Kevin
 * Fixed level specific progress indicator to have a default for single
 * player missions, and fixed the default mission name (put it in the
 * stringtable)
 *
 * 157   3/24/99 10:54a Kevin
 * Fixed some problems related to splitting up the main d3.mn3 file across
 * 2 CDs
 *
 * 156   3/18/99 3:51p Kevin
 * Fixed support for MN3 files
 *
 * 155   3/18/99 12:51p Samir
 * debug info.
 *
 * 154   3/18/99 10:13a Samir
 * added music.
 *
 * 153   3/09/99 6:34p Kevin
 * Made the training mission not be branching, and fixed the crash with
 * people dying in the demo playback
 *
 * 152   3/09/99 1:37p Kevin
 * Fixed lame sequencing bug in multiplayer
 *
 * 151   3/04/99 6:09p Samir
 * wait message for mission load dialog.
 *
 * 150   3/03/99 7:19p Jeff
 * removed levelwarp dialog for OEM
 *
 * 149   3/03/99 1:56p Samir
 * always assert that game mode is set to GM_NONE when entering main menu.
 * (when trying load game after escaping from multiplayer game list menu,
 * the game mode still seemed to be in GM_MULTI.)
 *
 * 148   3/02/99 11:31p Kevin
 *
 * 147   3/02/99 7:20p Kevin
 *
 * 146   3/02/99 11:52a Kevin
 * Fixes for OEM Beta 4.1
 *
 * 145   3/01/99 9:49p Jeff
 * fixed stray paren
 *
 * 144   3/01/99 9:03p Kevin
 * OEM Beta 4
 *
 * 143   2/28/99 3:26a Samir
 * redid newgame dialog.
 *
 * 142   2/26/99 7:36p Kevin
 * Fixed the oem mission name
 *
 * 141   2/26/99 7:16p Kevin
 * Added extern for ShowStaticScreen so it will compile in OEM
 *
 * 140   2/26/99 5:36p Samir
 * Added credits screens.
 *
 * 139   2/25/99 4:29p Jeff
 * mission data of pilot keeps track of all missions, not just after you
 * beat a level
 *
 * 138   2/24/99 3:15p Kevin
 * OEM menu changes, and bug fixes for the save/load system
 *
 * 137   2/20/99 2:30p Kevin
 * Made multiplayer DLLs return to the game list after a game.
 *
 * 136   2/20/99 1:14a Kevin
 * enabled choosing any mission number in the oem build (for now)
 *
 * 135   2/16/99 12:06p Samir
 * revamped ui for config menus.
 *
 * 134   2/16/99 12:36a Kevin
 * Fixes for release builds of OEM V3 and KAtmai
 *
 * 133   2/15/99 7:49p Jeff
 * new pilot file class and read/write system checked in...should be more
 * robust than old
 *
 * 132   2/08/99 2:39p Kevin
 * Fixed command line joining & disabled gamespy launching in OEM builds
 *
 * 131   2/05/99 7:23p Kevin
 * OEM Changes
 *
 * 130   2/03/99 4:20p Kevin
 * Got multiplayer working with .mn3 files, and setup autodownloading
 *
 * 129   1/31/99 7:26p Matt
 * Renamed a bunch of functions to have HUD capitalized
 *
 * 128   1/29/99 5:22p Jeff
 * localization
 *
 * 127   1/19/99 1:15p Samir
 * add on missions.
 *
 * 126   1/04/99 6:12p Jeff
 * close mission window when displaying level select
 *
 * 125   1/04/99 5:43p Kevin
 * new command line args
 *
 * 124   12/30/98 5:24p Kevin
 * Added +name to specify a default pilot (for gamespy) fixed a gamespy
 * bug, and improved the pxo dll game list screen
 *
 * 123   12/21/98 6:32p Matt
 * Fixed small bug
 *
 * 122   12/21/98 3:33p Samir
 * level warp fully implemented.
 *
 * 121   12/16/98 3:24p Samir
 * new way to get info on a mission (used to determine training mission
 * too.)
 *
 * 120   12/15/98 4:28p Jeff
 * added mission data information to the pilot files to save what the
 * highest level they achieved on a mission is.  Added level select dialog
 * (not hooked up) and level warp cheat.
 *
 * 119   11/23/98 4:52p Kevin
 * Demo system enhancments
 *
 * 118   11/19/98 5:40p Kevin
 * Demo system
 *
 * 117   11/18/98 3:26p Kevin
 * Put multiplayer options into con_dll.h
 *
 * 116   11/06/98 10:53a Kevin
 * Added demo playback
 *
 * 115   10/22/98 10:03a Jeff
 * renamed some things to keep them consistent
 *
 * 114   10/22/98 12:45a Matt
 * Before starting the game, get rid of the menu and leave just the
 * background screen up (while the briefing stuff is loading).
 *
 * 113   10/21/98 7:18p Matt
 * Added quick-exit system to not free individual mem chunks on exit,
 * since the whole heap gets freed at the end.
 *
 * 112   10/19/98 8:07p Matt
 * Added credits screens, and took out blank line in the main menu.
 *
 * 111   10/18/98 7:28p Samir
 * added weapon selection to options menu.
 *
 * 110   10/17/98 7:34p Samir
 * fixed bug when changing video modes, causing screen to not refresh.
 *
 * 109   10/17/98 6:11p Jeff
 * pilot select appears before main menu is shown
 *
 * 108   10/16/98 1:54p Kevin
 * Changes for Demo Beta 4
 *
 * 107   10/15/98 1:15p Kevin
 * Changed #ifndef RELEASE to #ifdef _DEBUG
 *
 * 106   10/13/98 3:48p Samir
 * added credits menu.
 *
 * 105   10/12/98 1:46p Samir
 * initial new main menu
 *
 * 104   10/08/98 10:47p Samir
 * added copyright message.
 *
 * 103   10/08/98 7:31p Samir
 * fixed memory crash bug if there are nomissions to load in listbox.
 *
 * 102   10/08/98 12:00p Kevin
 * Demo system work
 *
 * 101   10/07/98 6:23p Samir
 * added code to bail if in multiplayer for options menu.
 *
 * 100   10/07/98 1:08p Craig
 * fixed some simple multiplayer thing.
 *
 * 99    10/06/98 5:34p Jeff
 * various UI changes/improvements
 *
 * 98    10/02/98 12:30p Samir
 * added version information for beta/demo.
 *
 * 97    10/01/98 12:57p Samir
 * resized mission listbox.
 *
 * 96    9/30/98 12:33p Kevin
 * Added web launching support
 *
 * 95    9/30/98 10:36a Kevin
 * Added command line launching of URLs and command line directory
 * specification
 *
 * 94    9/28/98 4:35p Jeff
 * general UI changes and improvements
 *
 * 93    9/23/98 6:19p Jeff
 * finished up (hopefully) updating the config/ui dialogs to meet our
 * standard.  Keyboard/joystick config still needs some work
 *
 * 92    9/23/98 3:07p Jeff
 * updated the colors and various other items of config and UI
 *
 * 91    9/22/98 3:56p Samir
 * special demo code doesn't allow pilot and mission stuff.
 *
 * 90    9/22/98 10:37a Jason
 * added loadlevel command line argument for autostarting of levels
 *
 * 89    9/08/98 11:41a Jeff
 * call new pilot selection dialog
 *
 * 88    9/02/98 2:54p Jeff
 * added defines for text colors to be used throughout the game...fixed up
 * buddy menu too
 *
 * 87    9/01/98 12:44p Jeff
 * clear screen as soon as user double clicks on mission
 *
 * 86    8/31/98 12:38p Samir
 * new game dialog is no longer a 'menu' based window.
 *
 * 85    8/25/98 10:53a Samir
 * restored simple menu system
 *
 * 84    8/24/98 10:55a Kevin
 * new directplay stuff
 *
 * 83    8/20/98 11:29a Samir
 * adjusted placement of main menu items.
 *
 * 82    8/20/98 10:52a Samir
 * added load game(restore game) functionality from main menu.
 *
 * 81    8/14/98 7:37p Matt
 * Since PSFILENAME_LEN is now considered to be the max length of the
 * string itself (not counting the terminating null), buffers for file
 * name need to be PSFILENAME_LEN+1 bytes long.
 *
 * 80    8/07/98 2:44p Jeff
 * set all ships allowed when going into multiplayer.  Reset permissions
 * when selecting new game
 *
 * 79    7/29/98 6:43p Jeff
 * changed so menu loadlevel used file dialog
 *
 * 78    7/27/98 6:25p Jeff
 * fixed bug when changing screen size in menu
 *
 * 77    7/10/98 12:08p Kevin
 * fixed auto connect to only happen once
 *
 * 76    7/10/98 10:47a Kevin
 * Added command line connecting to games
 *
 * 75    6/19/98 5:40p Samir
 * added hud configuration.
 *
 * 74    6/16/98 10:56a Jeff
 * localization changes
 *
 * 73    6/15/98 4:00p Jason
 * replaced monochromatic polymodel lighting with rgb lighting
 *
 * 72    5/25/98 8:19p Samir
 * display mission menu.
 *
 * 71    5/24/98 2:58a Jeff
 * Options menu changes.  MenuOptions now takes a parameter, whether its
 * being called from the game or not
 *
 * 70    5/23/98 6:33p Jeff
 * renamed the hotspots for the Options menu
 *
 * 69    5/18/98 3:56p Samir
 * added D3_FAST mode to quickly enter and exit games.
 *
 * 68    5/12/98 2:48p Samir
 * show cursor in main menu.
 *
 * 67    5/08/98 4:31p Samir
 * set ui callback to nothing if we're done with main menu.
 *
 * 66    5/08/98 3:58p Samir
 * reposition options menu after video config.
 *
 * 65    5/05/98 5:15p Samir
 * adjusted menus to work in 512x384 as well as 640x480.
 *
 * 64    5/04/98 10:51a Jeff
 * changed menu font color
 *
 * 63    5/01/98 6:25p Samir
 * brightened up options menu.
 *
 * 62    5/01/98 4:25p Samir
 * sped up menu animation.
 *
 * 61    5/01/98 3:26p Samir
 * menu items should be aligned properly.
 *
 * 60    4/29/98 1:04p Jeff
 * fixed up colors in the windows, text strings and others
 *
 * 59    4/28/98 4:46p Samir
 * use new menu font for menu.
 *
 * 58    4/28/98 11:55a Jeff
 * Removed ConfigSave and replaced with SaveGameSettings
 *
 * 57    4/20/98 11:30a Jason
 * Added ShowProgressScreen function
 *
 * 56    4/13/98 7:01p Samir
 * added snazzy listbox and edit box art.
 *
 * 55    4/10/98 7:55p Samir
 * new main menu interface system.
 *
 * 54    4/09/98 5:30p Samir
 * new main  menu art.
 *
 * 53    4/02/98 3:54p Jason
 * first pass in getting polymodel paging to work
 *
 * 52    4/02/98 11:11a Samir
 * Error checking for level load/misison init fail.
 *
 * 51    3/20/98 1:19p Jeff
 * Changes made to use Default_pilot string for pilot filename to use.
 *
 * 50    3/13/98 8:55p Jeff
 * Various changes to move control configuration into Pilot file
 *
 * 49    3/13/98 12:49p Jeff
 * Fixed "Load Level" option it now works
 *
 * 48    3/13/98 12:10p Samir
 * Added a simple load level menu function, UI must be implemented.
 *
 * 47    3/12/98 8:31p Jeff
 * fixed bug in Load A Level option
 *
 * 46    3/12/98 8:29p Jeff
 * Put in Load Level option for non-release
 *
 * 45    3/12/98 7:09p Jeff
 * Added "Pilots" to main menu
 *
 * 44    3/12/98 2:15p Jeff
 * changed options menu text colors
 *
 * 43    3/12/98 2:01p Jeff
 * Made it so user can't cancel out of Pilot dialog (passed true to
 * PilotDisplay)
 *
 * 42    3/11/98 5:38p Jeff
 * Automatically calls PilotDisplay to choose pilot before main menu
 *
 * 41    3/10/98 12:48p Samir
 * Options menu has new look.
 *
 * 40    3/09/98 4:00p Jeff
 * Pilot test (temp) added to main menu for Pilot screen testing
 *
 * 39    3/05/98 6:38p Samir
 * Use UI_FONT now.
 *
 * 38    3/02/98 5:53p Samir
 * Don't set alpha of UI windows.
 *
 * 37    2/27/98 5:35p Jeff
 * Added in loading and saving of a game configuration file
 *
 * 36    2/24/98 3:43p Jeff
 * added more configuration options in the Options menu
 *
 * 35    2/16/98 9:27p Samir
 * Added test code for movies.
 *
 * 34    2/15/98 7:07p Samir
 * Added two controller options in the options menu.
 *
 * 33    2/13/98 6:38p Samir
 * Added menu movie.
 *
 * 32    2/11/98 4:36p Samir
 * Call SetGameMode to modify game mode.
 *
 * 31    2/10/98 3:46p Samir
 * Call config function when choosing 'configuration'.
 *
 * 30    1/30/98 7:33p Samir
 * Jazzed up menus.
 *
 * 29    1/30/98 2:39p Samir
 * Commented out real-time code.
 *
 * 28    1/26/98 2:28p Jason
 * fixed main menu arguments
 *
 * 27    1/26/98 10:36a Samir
 * Changed UI a bit.
 *
 * 26    1/19/98 10:56a Samir
 * Adjusted menu a bit.
 *
 * 25    1/18/98 4:22p Samir
 * Implemented new UIItem system.
 *
 * 24    1/15/98 11:14a Jeff
 * Added/Changed code to get Telcom working again
 *
 * 23    1/13/98 6:29p Samir
 * Moved Large Bitmap code from Menu.cpp to newui.cpp.
 *
 * 22    1/13/98 4:28p Samir
 * Added sliders.
 *
 * 21    1/12/98 5:24p Samir
 * Menu uses new font.
 *
 * 20    1/08/98 12:18p Samir
 * New menu interface.
 *
 * 19    1/06/98 2:44p Jason
 * another pass for multiplayer
 *
 * 18    1/06/98 2:15p Samir
 * Took out test stuff.
 *
 * 17    1/05/98 10:56a Samir
 * New menu stuff.
 *
 * 16    12/19/97 2:12p Samir
 * Fixed menu.
 *
 * 15    12/11/97 3:15p Samir
 * Stubbed out menu code.
 *
 * 14    11/19/97 10:44a Jason
 * minor changes to menu
 *
 * 13    11/18/97 6:34p Jason
 * sped up main menu animation, added alpha support, and made it work in
 * software mode.
 *
 * 12    11/17/97 4:31p Matt
 * Got rid of compile warning
 *
 * 11    11/14/97 7:02p Samir
 * Milestone menu.
 *
 * 10    11/12/97 2:52p Samir
 * Slightly more complicated, slower frame rate animating background.
 *
 * 9     11/11/97 1:28p Samir
 * Simple 3d background.
 *
 * 8     11/04/97 4:56p Samir
 * Main menu beginning to work.
 *
 * 7     10/15/97 3:05p Samir
 * Redraw menu each frame.
 *
 * 6     10/02/97 12:36p Samir
 * Redid game sequencing flow.
 *
 * 5     7/23/97 4:46p Jeff
 * Added call to SetScreenMode() in MainMenu() to init Game_view
 *
 * 7     6/11/97 2:25p Samir
 * Changed gameos to new system
 *
 * 6     5/15/97 2:09p Samir
 * Start mission when new game.
 *
 * 5     4/29/97 5:29p Samir
 * New game calls mission functions.
 *
 * 4     3/17/97 1:15p Matt
 * Cleaned up menu a little
 *
 * 3     2/04/97 5:33p Samir
 * Added Editor option to 'menu'.
 *
 * 2     2/04/97 2:33p Samir
 * Cheap menu
 *
 * 1     2/03/97 5:27p Samir
 * Initial version
 *
 * $NoKeywords: $
 */

#include <cstdio>
#include <cstring>

#include "menu.h"
#include "mmItem.h"
#include "game.h"
#include "gamesequence.h"
#include "Mission.h"
#include "multi_ui.h"
#include "ctlconfig.h"
#include "config.h"
#include "gamesave.h"
#include "demofile.h"
#include "pilot.h"
#include "LoadLevel.h"
#include "stringtable.h"
#include "mem.h"
#include "args.h"
#include "cinematics.h"

#ifdef _WIN32
#define USE_DIRECTPLAY
#endif

#ifdef USE_DIRECTPLAY
#include "directplay.h"
#else
bool Directplay_lobby_launched_game = false;
#endif
#include "multi_dll_mgr.h"
#include "musicapi.h"
#include "newui_core.h"

#define IDV_QUIT 0xff
//	Menu Item Defines
#define IDV_NEWGAME 10
#define IDV_MULTIPLAYER 11
#define IDV_OPTIONS 12
#define IDV_PILOT 13
#define IDV_LOADGAME 14
#define IDV_PLAYDEMO 15
#define IDV_CREDITS 16
#ifdef _DEBUG
#define IDV_LOADLEVEL 20
#define IDV_OK 1
#define IDV_CANCEL 2
bool MenuLoadLevel(void);
#endif
// for command line joining of games
bool Auto_connected = false;
// externed from init.cpp
extern void SaveGameSettings();
//	runs command line options.
bool ProcessCommandLine();
// new game selection
bool MenuNewGame();
extern bool Mem_quick_exit;
bool IsRestoredGame = false;
//////////////////////////////////////////////////////////////////////////////
extern bool Demo_looping;
bool FirstGame = false;

int MainMenu() {
  extern void ShowStaticScreen(char *bitmap_filename, bool timed = false, float delay_time = 0.0f);
  mmInterface main_menu;
  bool exit_game = false;
  bool exit_menu = false;

  // okay over here, we'll decide whether we've finished the training mission and are going into game.
  if (!Demo_looping && !Demo_restart && !MultiDLLGameStarting) {
    if (FirstGame) {
      if (MenuNewGame()) {
        return 0;
      }
    }
  }

  // setup screen
  SetScreenMode(SM_MENU);
  // create interface
  main_menu.Create();
  main_menu.AddItem(IDV_NEWGAME, KEY_N, TXT_MENUNEWGAME, MM_STARTMENU_TYPE);
  main_menu.AddItem(IDV_LOADGAME, KEY_L, TXT_LOADGAME);
  // #ifndef DEMO
  main_menu.AddItem(IDV_PLAYDEMO, KEY_D, TXT_VIEWDEMO);
  // #endif
  main_menu.AddItem(IDV_OPTIONS, KEY_O, TXT_MENUOPTIONS);
  main_menu.AddItem(IDV_PILOT, KEY_P, TXT_MENUPILOTS);
  main_menu.AddItem(IDV_MULTIPLAYER, KEY_M, TXT_MENUMULTIPLAYER);
  main_menu.AddItem(IDV_CREDITS, KEY_C, TXT_MENUCREDITS);
  main_menu.AddItem(IDV_QUIT, KEY_Q, TXT_MENUQUIT, MM_ENDMENU_TYPE);
#ifdef _DEBUG
  main_menu.AddItem(0, 0, NULL);
  main_menu.AddItem(IDV_LOADLEVEL, 0, "Load Level");
#endif
  //	page in ui data.
  newuiCore_PageInBitmaps();
  // do special junk.

  // Only check for pilot arg first time, not every tme
  static bool first_time = true;
  if (first_time) {
    int pilotarg = FindArg("+name");
    if (!pilotarg) {
      pilotarg = FindArg("-pilot");
    }
    if (pilotarg) {
      char pfilename[_MAX_FNAME];
      strcpy(pfilename, GameArgs[pilotarg + 1]);
      strcat(pfilename, ".plt");
      Current_pilot.set_filename(pfilename);
      PltReadFile(&Current_pilot, true);
    }
    first_time = false;
  }
  char pfilename[_MAX_FNAME];
  Current_pilot.get_filename(pfilename);

  if ((pfilename[0] == '\0') || (strlen(pfilename) == 0) || (!strcmp(pfilename, " ")))
    PilotSelect();

  //	always enforce that in main menu we are in normal game mode.
  SetGameMode(GM_NONE);
  // open main menu
  main_menu.Open();
  exit_menu = ProcessCommandLine();
  // Main Menu Code Here
  while (!exit_menu) {
    int res;
    // handle all UI results.
    if ((Demo_looping) || (Demo_restart)) {
      Demo_restart = false;
      SetGameMode(GM_NORMAL);
      SetFunctionMode(LOADDEMO_MODE);
      exit_menu = 1;
      continue;
    } else if (MultiDLLGameStarting) {
      // Go back into the multiplayer DLL @ the game list

      mprintf(0, "Returning to Multiplayer!\n");

      if (ReturnMultiplayerGameMenu()) {
        exit_menu = 1;
        SetFunctionMode(GAME_MODE);
        continue;
      }
    }
    /*
            else
            {
                    if(FirstGame)
                    {
                            //MenuScene();
                            //ui_ShowCursor();
                            //App()->defer();
                            //DoUIFrame();
                            //rend_Flip();
                            //GetUIFrameResult();
                            res = IDV_NEWGAME;
                    }
                    else {
                            main_menu.SetMusicRegion(MM_MUSIC_REGION);
                            res = main_menu.DoUI();
                    }
            }
            if (FirstGame)
                    res = IDV_NEWGAME;
    */
    res = FirstGame ? IDV_NEWGAME : -1;
    if (res == -1) {
      main_menu.SetMusicRegion(MM_MUSIC_REGION);
      res = main_menu.DoUI();
    }
    switch (res) {
    case IDV_NEWGAME:
      main_menu.SetMusicRegion(NEWGAME_MUSIC_REGION);
      DoWaitMessage(true);
      IsCheater = false;
      IsRestoredGame = false;
      // make only the default ships available (we may need to move this depending on load a saved game)
      PlayerResetShipPermissions(-1, true);
      if (MenuNewGame()) {
        exit_menu = 1;
        MenuScene();
        rend_Flip();
      }
      break;
    case IDV_QUIT:
      if (DoMessageBox(TXT_MENUQUIT, TXT_QUITMESSAGE, MSGBOX_YESNO)) {
        exit_game = 1;
        exit_menu = 1;
        Mem_quick_exit = 1; // tell the mem library to not free up each chunk individually
      }
      break;
    case IDV_LOADGAME:
      SetGameMode(GM_NONE);
      if (LoadGameDialog()) {
        SetGameMode(GM_NORMAL);
        SetFunctionMode(RESTORE_GAME_MODE);
        exit_menu = 1;
      }
      break;
    case IDV_OPTIONS:
      main_menu.SetMusicRegion(OPTIONS_MUSIC_REGION);
      OptionsMenu();
      break;
    case IDV_PILOT:
      main_menu.SetMusicRegion(OPTIONS_MUSIC_REGION);
      DoWaitMessage(true);
      PilotSelect();
      break;
    case IDV_MULTIPLAYER: {
      IsCheater = false;
      main_menu.SetMusicRegion(MULTI_MUSIC_REGION);
      mprintf(0, "Multiplayer!\n");
      // make all ships available
      mprintf(0, "Making all ships available\n");
      for (int i = 0; i < MAX_SHIPS; i++) {
        if (Ships[i].used)
          PlayerSetShipPermission(-1, Ships[i].name, true);
      }
      if (MainMultiplayerMenu()) {
        exit_menu = 1;
        SetFunctionMode(GAME_MODE);
      }
    } break;
    case IDV_PLAYDEMO:
      if (LoadDemoDialog()) {
        SetGameMode(GM_NORMAL);
        SetFunctionMode(LOADDEMO_MODE);
        exit_menu = 1;
      }
      break;
    case IDV_CREDITS:
      SetFunctionMode(CREDITS_MODE);
      exit_menu = 1;
      /*
      #if defined(DEMO)
              //extern void ShowStaticScreen(char *bitmap_filename);
              ShowStaticScreen("democredits1.ogf");
              ShowStaticScreen("democredits2.ogf");
      #elif defined(OEM)
              ShowStaticScreen("oemcredits1.ogf");
              ShowStaticScreen("oemcredits2.ogf");
      #else
      //	ShowStaticScreen("oemcredits1.ogf");
      //	ShowStaticScreen("oemcredits2.ogf");
      #endif
      */
      break;
#ifdef _DEBUG
    case IDV_LOADLEVEL: {
      if (MenuLoadLevel()) {
        ShowProgressScreen(TXT_LOADINGLEVEL);
        exit_menu = 1;
      }
    } break;
#endif
    }
  }
  // close menu
  main_menu.Close();
  main_menu.Destroy();
  //	page in ui data.
  newuiCore_ReleaseBitmaps();
  return exit_game ? 1 : 0;
}
//	runs command line options.
bool ProcessCommandLine() {
  int exit_menu = 0;
  // Auto connect to a network game if the parm is there.
  if ((!Auto_connected) && (TCP_active) && (FindArg("-url"))) {
    Auto_connected = true;
    int urlarg = FindArg("-url") + 1;
    char szurl[200];
    char *p;
    char *tokp;
    strcpy(szurl, GameArgs[urlarg]);
#ifdef DEMO
    szurl[strlen("d3demo2://") - 1] = '\0'; // Should make the string "d3demo:/"
    p = szurl + strlen("d3demo2://");       // pointer to the first character of the url after the //
    if (stricmp(szurl, "d3demo2:/") == 0) {
      mprintf(0, "Got a url passed: %s\n", p);
    }
#else
    szurl[strlen("descent3://") - 1] = '\0'; // Should make the string "descent3:/"
    p = szurl + strlen("descent3://");       // pointer to the first character of the url after the //
    if (stricmp(szurl, "descent3:/") == 0) {
      mprintf(0, "Got a url passed: %s\n", p);
    }
#endif
    tokp = strtok(p, "/");
    if (stricmp(tokp, "ip") == 0) {
      tokp = strtok(NULL, "/");
      Auto_login_port[0] = '\0';
      strcpy(Auto_login_addr, tokp);
      //			char seldll[_MAX_PATH*2];
      // ddio_MakePath(seldll,Base_directory,"online","Direct TCP~IP Game.d3c",NULL);
      if (LoadMultiDLL("Direct TCP~IP")) {
        CallMultiDLL(MT_AUTO_LOGIN);
        if (MultiDLLGameStarting) {
          mprintf(0, "Successfully connected to server at specified url.\n");
          exit_menu = 1;
        } else {
          mprintf(0, "Couldn't connect to server at specified url.\n");
        }
      } else {
        mprintf(0, "Couldn't load DLL.\n");
      }
    } else if (stricmp(tokp, "pxo") == 0) {
      tokp = strtok(NULL, "/");
      Auto_login_port[0] = '\0';
      strcpy(Auto_login_addr, tokp);
      //		char seldll[_MAX_PATH*2];
      // ddio_MakePath(seldll,Base_directory,"online","parallax online.d3c",NULL);
      if (LoadMultiDLL("parallax online")) {
        CallMultiDLL(MT_AUTO_LOGIN);
        if (MultiDLLGameStarting) {
          mprintf(0, "Successfully connected to server at specified url.\n");
          exit_menu = 1;
        } else {
          mprintf(0, "Couldn't connect to server at specified url.\n");
        }
      } else {
        mprintf(0, "Couldn't load DLL.\n");
      }
    }
  } else if ((!Auto_connected) && (FindArg("-pxo"))) {
    Auto_connected = true;
    if (AutoConnectPXO()) {
      exit_menu = 1;
    }
  } else if ((!Auto_connected) && (FindArg("-directip"))) {
    Auto_connected = true;
    if (AutoConnectLANIP()) {
      exit_menu = 1;
    }
  } else if ((!Auto_connected) && (FindArg("-heat"))) {
    Auto_connected = true;
    if (AutoConnectHeat()) {
      exit_menu = 1;
    }
  }
#ifndef OEM
  else if ((!Auto_connected) && (FindArg("+connect"))) {
    Auto_connected = true;
    int connarg = FindArg("+connect");
    char connhost[300];
    strcpy(connhost, GameArgs[connarg + 1]);
    char *port = strchr(connhost, ':');
    if (port) {
      // terminate the hostname
      *port = '\0';
      // Increment to the first character of the port name
      port++;
      // get the port number
      strcpy(Auto_login_port, port);
    }
    strcpy(Auto_login_addr, connhost);
    int trackedarg = FindArg("+cl_pxotrack");
    if (trackedarg) {
      if (strcmp("1", GameArgs[trackedarg + 1]) == 0) {
        if (AutoConnectPXO()) {
          exit_menu = 1;
        }
      } else if (AutoConnectLANIP()) {
        exit_menu = 1;
      }
    }
  }
#endif
  else if ((!Auto_connected) && (Directplay_lobby_launched_game)) {
    Auto_connected = true;
#ifdef USE_DIRECTPLAY
    if (dp_AutoConnect()) {
      exit_menu = 1;
    }
#else
    exit_menu = 1;
#endif
  }
#ifndef RELEASE
  int t = FindArg("-loadlevel");
  if (t) {
    SimpleStartLevel(GameArgs[t + 1]);
    exit_menu = 1;
  }
#endif
  // at some point the code above sets exit_menu, so we're going to game mode.
  if (exit_menu) {
    SetFunctionMode(GAME_MODE);
  }
  SetUICallback(DEFAULT_UICALLBACK);
  return exit_menu ? true : false;
}
//////////////////////////////////////////////////////////////////////////////
//	Start New Game
#define MSNDLG_WIDTH 512
#define MSNDLG_HEIGHT 384
#define MSNDLG_X (Max_window_w - MSNDLG_WIDTH) / 2
#define MSNDLG_Y (Max_window_h - MSNDLG_HEIGHT) / 2
#define MSNLB_WIDTH (MSNDLG_WIDTH - 64)
#define MSNLB_HEIGHT (MSNDLG_HEIGHT - 160)
#define MSNLB_X (MSNDLG_WIDTH - MSNLB_WIDTH) / 2
#define MSNLB_Y (MSNDLG_HEIGHT - MSNLB_HEIGHT) / 2
#define MSNBTN_W 96
#define MSNBTN_X ((MSNDLG_WIDTH / 4) - (MSNBTN_W / 2))
#define MSNBTN_X2 ((3 * MSNDLG_WIDTH / 4) - (MSNBTN_W / 2))
#define MSNBTN_Y (MSNDLG_HEIGHT - 64)
#define UID_MSNLB 100
#define UID_MSNINFO 0x1000
#define TRAINING_MISSION_NAME "Pilot Training"
static inline int count_missions(const char *pathname, const char *wildcard) {
  int c = 0;
  char fullpath[_MAX_PATH];
  char filename[_MAX_PATH];
  tMissionInfo msninfo;
  filename[0] = 0;
  ddio_MakePath(fullpath, pathname, wildcard, NULL);

  if (ddio_FindFileStart(fullpath, filename)) {
    do {
      const char *name;
      ddio_MakePath(fullpath, pathname, filename, NULL);

      if (stricmp("d3_2.mn3", filename) == 0)
        continue;
      mprintf(0, "Mission path:%s\n", fullpath);
      name = GetMissionName(filename);
      GetMissionInfo(filename, &msninfo);
      if (name && name[0] && msninfo.single) {
        mprintf(0, "Name:%s\n", name);
        c++;
        if (!(c % 2))
          DoWaitMessage(true);
      } else {
        mprintf(0, "Illegal mission:%s\n", fullpath);
      }
      filename[0] = 0;
    } while (ddio_FindNextFile(filename));
    ddio_FindFileClose();
  }
  return c;
}
static inline int generate_mission_listbox(newuiListBox *lb, int n_maxfiles, char **filelist, const char *pathname,
                                           const char *wildcard) {
  int c = 0;
  char fullpath[_MAX_PATH];
  char filename[_MAX_PATH];
  ddio_MakePath(fullpath, pathname, wildcard, NULL);

  if (ddio_FindFileStart(fullpath, filename)) {
    do {
      tMissionInfo msninfo;
      if (n_maxfiles > c) {
        ddio_MakePath(fullpath, pathname, filename, NULL);
        if (stricmp("d3_2.mn3", filename) == 0)
          continue;
        if (GetMissionInfo(filename, &msninfo) && msninfo.name[0] && msninfo.single) {
          // if (!msninfo.training || (msninfo.training && Current_pilot.find_mission_data(TRAINING_MISSION_NAME)!= -1))
          // {
          filelist[c] = mem_strdup(filename);
          lb->AddItem(msninfo.name);
          filename[0] = 0;
          c++;
          if (!(c % 2))
            DoWaitMessage(true);
          //}
        }
      }
    } while (ddio_FindNextFile(filename));
    ddio_FindFileClose();
  }
  return c;
}
extern bool Skip_next_movie;
#define OEM_TRAINING_FILE "training.mn3"
#define OEM_MISSION_FILE "d3oem.mn3"
bool MenuNewGame() {
  newuiTiledWindow menu;
  newuiSheet *select_sheet;
  newuiListBox *msn_lb;
  char **filelist = NULL;
  int n_missions, i, res; //,k
  bool found = false;
  bool do_menu = true, load_mission = false, retval = true;
#ifdef DEMO
  if (LoadMission("d3demo.mn3")) {
    CurrentPilotUpdateMissionStatus(true);
    // go into game mode.
    SetGameMode(GM_NORMAL);
    SetFunctionMode(GAME_MODE);
    return true;
  } else {
    DoMessageBox(TXT_ERROR, TXT_ERRLOADMSN, MSGBOX_OK);
    return false;
  }
#else
#ifdef RELEASE
  if ((!FindArg("-mission")) && (!FirstGame) && (-1 == Current_pilot.find_mission_data(TRAINING_MISSION_NAME))) {

    FirstGame = true;

    char temppath[_MAX_PATH];
    const char *moviepath;
    moviepath = GetMultiCDPath("level1.mve");
    if (moviepath) {
      strcpy(temppath, moviepath);
      PlayMovie(temppath);
    }
    Skip_next_movie = true;

    if (LoadMission("training.mn3")) {
      CurrentPilotUpdateMissionStatus(true);
      // go into game mode.
      SetGameMode(GM_NORMAL);
      SetFunctionMode(GAME_MODE);
      return true;
    } else {
      DoMessageBox(TXT_ERROR, TXT_ERRLOADMSN, MSGBOX_OK);
      return false;
    }
  } else if (FirstGame) {
    FirstGame = false;
#ifdef OEM
    if (LoadMission(OEM_MISSION_FILE))
#else
    if (LoadMission("d3.mn3"))
#endif
    {
      CurrentPilotUpdateMissionStatus(true);
      // go into game mode.
      SetGameMode(GM_NORMAL);
      SetFunctionMode(GAME_MODE);
      return true;
    } else {
      DoMessageBox(TXT_ERROR, TXT_ERRLOADMSN, MSGBOX_OK);
      return false;
    }
  }
#endif
  // create menu.
  menu.Create(TXT_MENUNEWGAME, 0, 0, 448, 384);

  select_sheet = menu.GetSheet();
  select_sheet->NewGroup(NULL, 10, 0);
  msn_lb = select_sheet->AddListBox(352, 256, UID_MSNLB);
  select_sheet->NewGroup(NULL, 160, 280, NEWUI_ALIGN_HORIZ);
  select_sheet->AddButton(TXT_OK, UID_OK);
  select_sheet->AddButton(TXT_CANCEL, UID_CANCEL);
#ifndef OEM
  select_sheet->AddButton(TXT_MSNINFO, UID_MSNINFO);
#endif
#ifndef OEM
  // add mission names to listbox
  // count valid mission files.
  // add a please wait dialog here.
  n_missions = 0;
#ifndef RELEASE
  n_missions = count_missions(LocalLevelsDir, "*.msn");
#endif
  n_missions += count_missions(D3MissionsDir, "*.mn3");
  if (n_missions) {
    // allocate extra mission slot because of check below which adds a name to the filelist.
    filelist = (char **)mem_malloc(sizeof(char *) * (n_missions + 1));
    for (i = 0; i < (n_missions + 1); i++)
      filelist[i] = NULL;
  } else {
    DoMessageBox(TXT_ERROR, TXT_NOMISSIONS, MSGBOX_OK);
    retval = false;
    DoWaitMessage(false);
    goto missions_fail;
  }
  // generate real listbox now.
  i = 0;
#ifndef RELEASE
  i = generate_mission_listbox(msn_lb, n_missions, filelist, LocalLevelsDir, "*.msn");
#endif
  i += generate_mission_listbox(msn_lb, n_missions - i, filelist + i, D3MissionsDir, "*.mn3");
  // #ifdef RELEASE
  int k;
  for (k = 0; k < n_missions; k++) {
    if (!filelist[k])
      continue;
    if (stricmp(filelist[k], "d3.mn3") == 0) {
      found = true;
      break;
    }
  }
  if (!found) {
    filelist[n_missions] = mem_strdup("d3.mn3");
    msn_lb->AddItem(TXT_MAINMISSION);
    n_missions++;
  }
// #endif
#else
#define OEM_MISSION_NAME "Descent 3: Sol Ascent"
#define OEM_TRAINING_NAME "Pilot Training "
  n_missions = 2;
  filelist = (char **)mem_malloc(sizeof(char *) * 2);
  filelist[0] = mem_strdup(OEM_MISSION_FILE);
  ;
  msn_lb->AddItem(OEM_MISSION_NAME);
  filelist[1] = mem_strdup(OEM_TRAINING_FILE);
  msn_lb->AddItem(OEM_TRAINING_NAME);
#endif
  DoWaitMessage(false);
redo_newgame_menu:
  // run menu
  menu.Open();

  do {
    res = menu.DoUI();
#ifndef OEM
    if (res == UID_MSNINFO) {
      tMissionInfo msninfo;
      int index = msn_lb->GetCurrentIndex();
      if (index >= 0 && index < n_missions) {
        if (GetMissionInfo(filelist[index], &msninfo)) {
          if (msninfo.name[0]) {
            newuiTiledWindow infownd;
            newuiSheet *sheet;
            infownd.Create(NULL, 0, 0, 384, 192);
            infownd.Open();
            sheet = infownd.GetSheet();
            sheet->NewGroup(TXT_MSNNAME, 0, 0);
            sheet->AddText(msninfo.name);
            sheet->NewGroup(TXT_MSNAUTHOR, 0, 32);
            if (msninfo.author[0])
              sheet->AddText(msninfo.author);
            else
              sheet->AddText(TXT_NONE);
            sheet->NewGroup(TXT_MSNNOTES, 0, 64);
            if (msninfo.desc[0])
              sheet->AddText(msninfo.desc);
            else
              sheet->AddText(TXT_NONE);
            sheet->NewGroup(NULL, 240, 118);
            sheet->AddButton(TXT_OK, UID_OK);
            infownd.DoUI();
            infownd.Close();
            infownd.Destroy();
          }
        }
      }
    }
#endif
  } while (res != UID_OK && res != UID_CANCEL && res != UID_MSNLB);
  menu.Close();
  // check stuff
  if (res == UID_CANCEL) {
    retval = false;
  } else if (res == UID_OK || res == UID_MSNLB) {
    int index = msn_lb->GetCurrentIndex();
    char *nameptr = NULL;
    if (index >= 0 && index < n_missions) {
      nameptr = filelist[index];
    }
#ifndef OEM
    if (!nameptr || !LoadMission(nameptr)) {
#else
    if (!LoadMission(nameptr)) {
#endif
      DoMessageBox(TXT_ERROR, TXT_ERRLOADMSN, MSGBOX_OK);
      retval = false;
    } else {
      //	if we didn't escape out of any part of new game start, then go to game.
      int highest;
      CurrentPilotUpdateMissionStatus(true);
      // gets highest level flown for mission
#if defined(_DEBUG) || defined(DAJ_DEBUG)
      highest = Current_mission.num_levels;
#else
      highest = PilotGetHighestLevelAchieved(&Current_pilot, Current_mission.name);
      highest = std::min(highest + 1, Current_mission.num_levels);
#endif
      if (highest > 1) {
        int start_level;
        start_level = DisplayLevelWarpDlg(highest);
        if (start_level == -1) {
          goto redo_newgame_menu;
        } else {
          Current_mission.cur_level = start_level;
          // pull out the ship permssions and use them
          Players[0].ship_permissions = GetPilotShipPermissions(&Current_pilot, Current_mission.name);
        }
      }
      // go into game mode.
      SetGameMode(GM_NORMAL);
      SetFunctionMode(GAME_MODE);
      retval = true;
    }
  }
  menu.Destroy();
missions_fail:
  // free all memory
  for (i = 0; i < n_missions; i++) {
    if (filelist[i]) {
      mem_free(filelist[i]);
    }
  }
  if (filelist) {
    mem_free(filelist);
  }
  return retval;
#endif
}
// DisplayLevelWarpDlg
//	pass in the max level allowed to be chosen, if -1, than all levels are allowed (a.k.a level warp cheat)
int DisplayLevelWarpDlg(int max_level) {
  newuiMessageBox hwnd;
  newuiSheet *sheet;
  int chosen_level = 1, res;
  int highest_allowed;
  char buffer[128];
  char *input_text;
  // creates a sheet
  sheet = hwnd.GetSheet();
  if (max_level != -1) {
    hwnd.Create(TXT_LEVELSELECT, MSGBOX_OKCANCEL);
    highest_allowed = max_level;
    snprintf(buffer, sizeof(buffer), TXT_LEVELSELECTB, highest_allowed);
  } else {
    // level warp
    hwnd.Create(TXT_LEVELWARP, MSGBOX_OKCANCEL);
    highest_allowed = Current_mission.num_levels;
    snprintf(buffer, sizeof(buffer), TXT_LEVELWARPB, Current_mission.num_levels);
  }
  sheet->NewGroup(buffer, 0, 0);
  input_text = sheet->AddEditBox(NULL, 4, 64, IDV_QUIT, UIED_NUMBERS);
  sprintf(input_text, "%d", chosen_level);
redo_level_choose:
  hwnd.Open();
  res = hwnd.DoUI();
  hwnd.Close();
  if (res == UID_OK || res == IDV_QUIT) {
    chosen_level = atoi(input_text);
    if (chosen_level < 1 || chosen_level > highest_allowed) {
      snprintf(buffer, sizeof(buffer), TXT_CHOOSELEVEL, highest_allowed);
      DoMessageBox(TXT_ERROR, buffer, MSGBOX_OK);
      goto redo_level_choose;
    }
  } else {
    chosen_level = -1;
  }
  hwnd.Destroy();
  return chosen_level;
}
#ifdef _DEBUG
// Loads a level and starts the game
bool MenuLoadLevel(void) {
  char buffer[_MAX_PATH];
  buffer[0] = '\0';
  if (DoPathFileDialog(false, buffer, "Load Level", "*.d3l", PFDF_FILEMUSTEXIST)) {
    SimpleStartLevel(buffer);
    SetFunctionMode(GAME_MODE);
    return true;
  }
  return false;
}
#endif
