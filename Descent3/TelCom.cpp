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

 * $Logfile: /DescentIII/main/TelCom.cpp $
 * $Revision: 152 $
 * $Date: 4/19/00 5:13p $
 * $Author: Matt $
 *
 * Contains the code to initialize, use and control TelCom system
 *
 * $Log: /DescentIII/main/TelCom.cpp $
 *
 * 152   4/19/00 5:13p Matt
 * From Duane for 1.4
 * Added checks, asserts, and fixes for bad return values
 * Removed Mac OpenGL hack
 *
 * 151   3/20/00 12:21p Matt
 * Merge of Duane's post-1.3 changes.
 * Minor optimization.
 *
 * 150   10/21/99 9:29p Jeff
 * B.A. Macintosh code merge
 *
 * 149   10/12/99 11:08a Jeff
 * fixed bug regarding ship permissions to start (for level 1) if the ship
 * is non-code default
 *
 * 148   7/13/99 3:33p Samir
 * music plays in automap and all telcom screens from within game.
 *
 * 147   5/23/99 7:43p Jason
 * fixed briefing problem with lowmem textures
 *
 * 146   5/13/99 3:42p Ardussi
 * changes for compiling on the Mac
 *
 * 145   5/12/99 1:58p Jason
 * made telcom use the global AllowedShips array instead of its own local
 * array
 *
 * 144   5/05/99 3:02a Jeff
 * added single player ship selection text
 *
 * 143   5/03/99 1:16p Jeff
 * play sounds at full volume
 *
 * 142   4/26/99 4:33p Samir
 * mouse input changed a little so that ddio_MouseGetState is called once
 * per frame.
 *
 * 141   4/21/99 11:05a Kevin
 * new ps_rand and ps_srand to replace rand & srand
 *
 * 140   4/20/99 12:46p Jeff
 * telcom main menu, mouse over button sets focus.  if you go into telcom
 * main menu, when you leave a system it will return you to main menu.
 *
 * 139   4/17/99 3:44p Kevin
 * Demo2 changes & fixes
 *
 * 138   4/15/99 10:06p Matt
 * Changed briefing file foreign-language filenames to be in the form
 * "level1_frn.brf".
 *
 * 137   4/14/99 3:57a Jeff
 * fixed case mismatch in #includes
 *
 * 136   4/06/99 1:53p Samir
 * added improved progress bar.
 *
 * 135   4/02/99 8:32p Jeff
 * added system event queue.  Arrow keys work in main menu and ship
 * selection
 *
 * 134   3/31/99 5:36p Jeff
 * cargo shouldn't display in main menu (not done...if it will be done)
 *
 * 133   3/31/99 5:28p Jeff
 * new way of key processesing...can capture printscreen now
 *
 * 132   3/28/99 12:44p Jeff
 * fixed table file parsing to add back in the ships
 *
 * 131   3/24/99 2:22p Jeff
 * fixed power button bug
 *
 * 130   3/02/99 6:59p Jeff
 * no cargo in oem
 *
 * 129   2/28/99 3:17p Jeff
 * single player ship selection not called in OEM
 *
 * 128   2/25/99 4:14a Jeff
 * shift-esc always exits to Main Menu, skips past ship selection
 *
 * 127   2/22/99 3:37p Jason
 * fixed markers in telcom
 *
 * 126   2/22/99 3:19p Jeff
 * random bug fixes
 *
 * 125   2/20/99 9:22p Jeff
 * finished telcom level goals screen.  Made it so if you go into the
 * telcom from the game it goes to main menu instead of briefings.
 *
 * 124   2/17/99 6:55p Jeff
 * added jump button type.  Added no early render flag for bitmaps.  Fixed
 * color bug for type text
 *
 * 123   2/10/99 4:45p Jeff
 * table file parser stuff
 *
 * 122   2/09/99 6:49p Jeff
 * removed extra call to startframe...no longer needed with stack based
 *
 * 121   2/09/99 3:32p Jeff
 * table file parser takes quotes strings for force keywords
 *
 * 120   2/08/99 1:03a Jeff
 * click made when changing ships in single player ship selection
 *
 * 119   2/05/99 7:04p Jeff
 * table file parsing macros put in
 *
 * 118   2/04/99 7:19p Jeff
 * added sound id for button click. main menu handling., briefing missing
 * fix
 *
 * 117   2/03/99 1:23p Jeff
 * more updates to single player ship selection...all thats left is stats
 *
 * 116   2/03/99 11:44a Jeff
 * selected ship hooked into the game
 *
 * 115   2/03/99 1:03a Jeff
 * almost done with single player ship selection...added rotating model
 *
 * 113   2/02/99 7:32p Jeff
 * begining of single player ship selection
 *
 * 112   2/01/99 4:52p Jeff
 * screenshots work in telcom
 *
 * 111   1/30/99 2:43p Jeff
 * fixed infinite loop bug
 *
 * 110   1/29/99 7:13p Jeff
 * localization
 *
 * 109   1/25/99 11:02a Samir
 * revamped mouse and key controls.
 *
 * 108   12/15/98 4:39p Jason
 * added some more telcom functions
 *
 * 107   12/15/98 10:53a Jason
 * yet more changes for 1.1
 *
 * 106   12/11/98 11:30p Jeff
 * oops forgot to remove test #define DEMO
 *
 * 105   12/11/98 11:22p Jeff
 * fixed telcom briefings so they can be called within game in the
 * demo...fixed some minor bugs that needed to be rounded up (typing sound
 * and initialization screen text)
 *
 * 104   12/11/98 1:48p Kevin
 * Took out automap ifdefs for demo
 *
 * 103   12/11/98 11:37a Jason
 *
 * 102   12/09/98 2:36p Jeff
 * added function to enable/disable telcom system keys and disabled most
 * system keys while in Automap
 *
 * 101   12/09/98 1:09p Jason
 * second draft of automap
 *
 * 100   11/02/98 6:00p Jeff
 * began adding single player ship selection
 *
 * 99    10/27/98 4:22p Jeff
 * changed the framerate cap to use Sleep(), to possibly help sound
 * performance
 *
 * 98    10/22/98 1:31a Jeff
 * optimized creating the static bitmaps
 *
 * 97    10/22/98 12:03a Matt
 * Disable creation of static bitmaps to speed the briefing startup.
 *
 * 96    10/21/98 11:12p Jeff
 * page in all data on Telcom init
 *
 * 95    10/21/98 4:51p Jeff
 * removed automap
 *
 * 94    10/21/98 11:14a Samir
 * added generic code to skip rendering while in game controller config or
 * telcom.
 *
 * 93    10/16/98 2:43p Jeff
 * only call Gameframe if not multi_ui_bail_menu
 *
 * 92    10/14/98 11:24p Jeff
 * turn off bilinear filtering in TC now
 *
 * 91    10/12/98 11:39p Jeff
 * finished up new focus system of telcom
 *
 * 90    10/12/98 8:32p Jeff
 * changed the way focus is handled
 *
 * 89    10/12/98 3:03p Jeff
 * fixed Shift-esc, and right arrow doesn't exit out of telcom if on the
 * last page
 *
 * 88    10/11/98 2:59a Jeff
 * TelCom is completly multiplayer friendly.  Removed cheat codes to
 * GameCheat.cpp.  Fixed up TelCom Mainmenu to handle certain systems not
 * available
 *
 * 87    10/09/98 7:47p Jeff
 * Fixed killrobot cheat
 *
 * 86    10/09/98 6:20p Jeff
 * fixed weapon cheat
 *
 * 85    10/09/98 6:18p Jeff
 * added camera cheat
 *
 * 84    10/09/98 3:05p Jeff
 * commented out slew cheat...
 *
 * 83    10/09/98 1:10p Jeff
 * removed call to SlewStop in cheat code section (not defined in release)
 *
 * 82    10/09/98 12:22p Jeff
 * cheat code system put in here (temporary?)
 *
 * 81    10/08/98 4:23p Kevin
 * Changed code to comply with memory library usage. Always use mem_malloc
 * , mem_free and mem_strdup
 *
 * 80    9/29/98 2:51p Jeff
 * put internal serial number check function in here to keep it from the
 * rest of the serialization stuff
 *
 * 79    8/28/98 12:57p Jeff
 * added sounds and some key functionality
 *
 * 78    8/27/98 2:51p Jeff
 * New TelCom finally checked in
 *
 * 77    8/19/98 2:29p Jeff
 * if not a release build then you can escape to main menu
 *
 * 76    8/19/98 1:38p Jeff
 * removed update2dsound
 *
 * 75    8/18/98 11:57a Jeff
 * fixed sound problem
 *
 * 74    8/15/98 2:46p Matt
 * Took out unneeded include
 *
 * 73    7/13/98 4:11p Jeff
 * sped up entering telcom by about 3-4 times
 *
 * 72    7/11/98 9:16p Jeff
 * moved automatically drawing monitor overlay graphics from update() to a
 * function of it's own, that way the TelCom API can be avoided if needed
 *
 * 71    7/08/98 8:06p Jeff
 * Initial creation of TelComCargo
 *
 * 70    6/16/98 10:54a Jeff
 *
 * 69    5/24/98 2:56a Jeff
 * Adjust x offset for main menu buttons
 *
 * 68    5/19/98 10:48a Jeff
 * if D3_FAST is set, TelCom doesn't run
 *
 * 67    5/18/98 4:21p Jeff
 * setup TelCom so D3_FAST zips it through
 *
 * 66    5/18/98 2:23p Jeff
 * Hooked up Automap
 *
 * 65    5/15/98 5:16p Jeff
 * Added Main Menu
 *
 * 64    5/11/98 6:22p Jeff
 * adjusted sound stopping position and removed calls to show/hide mouse
 *
 * 63    5/05/98 6:50p Jeff
 * Telcom doesn't use rend_DrawLFBitmap anymore...more speed!
 *
 * 62    5/04/98 6:22p Jeff
 * fixed possible sound bugs
 *
 * 61    5/04/98 5:29p Jeff
 * Added sounds to TelCom events
 *
 * 60    5/04/98 1:35p Jeff
 * Changes made for mouse handling
 *
 * 59    5/03/98 7:58p Jeff
 * changes made to handle mouse and input from within TelCom instead of UI
 *
 * 58    5/01/98 2:16p Jeff
 * changed default background colors for monitors
 *
 * 57    4/30/98 7:17p Jeff
 * added a main menu and going back and forth between it and systems.
 * Added a poweron initializing screen
 *
 * 56    4/26/98 7:19p Jeff
 * Power down effect done only when in hardware (some weird bug puts it in
 * an infinite loop in software
 *
 * 55    4/24/98 6:35p Jeff
 * Move prototypes to telcom.h
 *
 * 54    4/24/98 3:28p Jeff
 * fixed power down effect
 *
 * 53    4/23/98 7:09p Jeff
 * added power up/down support
 *
 * 52    4/23/98 6:38p Jason
 * made bitmaps use 1555 format
 *
 * 51    4/22/98 7:43p Jeff
 * Added support for monitor hilites
 *
 * 50    4/21/98 4:22p Jeff
 * Added functions for drawing hotspot in on/off positions
 *
 * 49    4/20/98 6:44p Jeff
 * removed extra code after briefings, so when you exit briefings you
 * don't hang around in limbo
 *
 * 48    4/17/98 6:54p Jeff
 * added scanline and changed order or drawing screen and zbuffer state
 * set on exit
 *
 * 47    4/15/98 6:28p Jeff
 * removed some built in code for the briefings parser
 *
 * 46    4/02/98 12:07p Jeff
 * Added framework for desktop effects, fixed corner bug
 *
 * 45    4/01/98 5:10p Jeff
 * Added speed for Flash text
 *
 * 44    3/30/98 10:50a Jeff
 * Initial Flash text put in
 *
 * 43    3/23/98 2:18p Jeff
 * Moved structures to hotspotmap.h
 *
 * 42    3/23/98 11:08a Jeff
 * Moved monitor and input stuff to seperate file
 *
 * 41    3/23/98 9:55a Jeff
 * Made changes to remove old telcom
 *
 * 40    3/18/98 8:00p Jeff
 * Added some functionality for text and using the monitor borders
 * correctly in the new Telcom
 *
 * 39    3/12/98 3:32p Jeff
 * Initial changes started for New TelCom
 *
 * 38    2/06/98 2:03p Jeff
 * added start/stop time calls
 *
 * 37    2/04/98 5:26p Jeff
 * Added movie support back into Telcom, and inventory stuff
 *
 * 36    1/31/98 8:50p Jeff
 * Added a very very crude inventory screen to telcom
 *
 * 35    1/26/98 6:35p Jeff
 * added a 'quick fast forward' key (spacebar)
 *
 * 34    1/21/98 1:09p Jeff
 * Prettied up the code, comments
 *
 * 33    1/20/98 9:16p Jeff
 * Added back in fading bitmaps
 *
 * 32    1/20/98 6:12p Jeff
 *
 * 31    1/20/98 12:08p Jeff
 *
 * 30    1/19/98 5:37p Jeff
 * Got briefing up to par, and even better than before, added timer so
 * scroll and type fonts are time based.
 *
 * 29    1/16/98 2:40p Jeff
 * Adjusted so everything is displayed in correct spots, took out
 * DefaultControl timer, added support for non fading bitmaps
 *
 * 28    1/15/98 11:11a Jeff
 * Got TelCom in a working state again, switch from 2d to 3d
 *
 * 27    12/19/97 2:26p Jason
 * more fixes for 2d/3d intergration
 *
 * 26    11/10/97 12:36p Samir
 * Telcom sets screen mode itself, and use menu font, not d2menu.
 *
 * 25    10/15/97 5:20p Jason
 * did a HUGE overhaul of the bitmap system
 *
 * 24    9/15/97 4:21p Samir
 * Added ddio_KeyFlush when quitting telecom to prevent untreated
 * keystrokes.
 *
 * 23    8/19/97 2:11p Matt
 * Closed files after they've been opened
 *
 * 22    8/15/97 3:17p Jeff
 * Fixed some functions affected by last change
 *
 * 21    8/15/97 12:24p Jeff
 * Changed things around a bit, added code to handle the round corners
 *
 * 20    8/13/97 3:13p Jeff
 * optimized for memory usage (removed the second background from being
 * stored in memory)
 *
 * 19    8/12/97 6:10p Jeff
 *
 * 18    8/12/97 5:34p Jeff
 * Added some comments, made the code a bit spiffier
 *
 * 17    8/12/97 12:35p Jeff
 * added scroll speed, fixed some more bugs and tweaks
 *
 * 16    8/11/97 6:43p Jeff
 * Added user defined function hook for subwindows, fixed some bugs
 *
 * 15    8/08/97 6:36p Jeff
 * fixed various bugs, did some tweaking
 *
 * 14    8/07/97 6:18p Jeff
 *
 * 13    8/07/97 12:03p Jeff
 *
 * 12    8/06/97 6:35p Jeff
 * added rough multitasking to subwindows
 *
 * 11    8/06/97 3:51p Jeff
 * fixed some bugs with the new subwindowing
 *
 * 10    8/06/97 11:57a Jeff
 *
 * 9     8/04/97 7:23p Jeff
 *
 * 8     8/04/97 6:23p Jeff
 *
 * 7     8/01/97 6:57p Jeff
 * Added enable/disable for vcr and system buttons.  Added screensaver
 *
 * 6     8/01/97 2:35p Jeff
 * Added windows to the hotspotmap
 *
 * 5     7/30/97 3:59p Jeff
 * Fixed VCR controls, updated for new artwork
 *
 * $NoKeywords: $
 */

#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "mono.h"
#include "renderer.h"
#include "render.h"
#include "ddio.h"
#include "descent.h"
#include "game.h"
#include "cfile.h"
#include "application.h"
#include "TelCom.h"
#include "TelComEffects.h"
#include "Briefing.h"
#include "TelComAutoMap.h"
#include "TelComCargo.h"
#include "TelComGoals.h"
#include "mem.h"
#include "Mission.h"
#include "stringtable.h"
#include "multi.h"
#include "ship.h"
#include "polymodel.h"
#include "localization.h"
#include "hlsoundlib.h"
#include "soundload.h"
#include "textaux.h"
#include "psrand.h"
#include "controls.h"
#include "musicapi.h"

#define FRAME_RATE 30.0f
#define TCPE_TIME 0.5f

//------------------------------New TelCom Stuff---------------------------------------

static void TelCom_BltToMem(int dest_bmp, int dx, int dy, int src_bmp, int sx, int sy, int sw, int sh,
                            bool trans = true);
static void TelCom_BltToScreen(int dx, int dy, chunked_bitmap *src_bmp);
static void TelCom_BltToScreen(int dx, int dy, chunked_bitmap *src_bmp, int sx, int sy, int sw, int sh);
static void DrawHotSpotOn(int hotspot);

//*************************************************************************************

// Globals---------------------------------------------------------------------------

static bool TelCom_init = false; // Whether the TelComInit() function was called
static bool Telcom_first_render = true;
static bool Telcom_exit_to_mainmenu = false;
bool Telcom_called_from_game = false;
static int Telcom_mouse_last_effect = -1; // the last efxnum the mouse was over

hotspotmap_t hotspotmap; // Holds hotspot data (position)
windowmap_t windowmap;   // Holds window data (position)
tTelComInfo Telcom_system;

chunked_bitmap Telcom_bitmap; // background bitmap for telcom system
static chunked_bitmap *hotspot_bitmaps;
static int LoadTelcomBitmap(const char *filename, chunked_bitmap *bmp);
static bool TelComMainMenu(tTelComInfo *tcs);

static void TelCom_PrepareCustomKeyEvents(void);
static void TelCom_PostProcessCustomKeyEvents(void);

static int Telcom_mouse_x, Telcom_mouse_y;

//===================================================================================================
// Functions
//===================================================================================================

// Initializes the TelCom system, only to be called once during game initialization
void TelComInit(void) {
  mprintf(0, "Initializing TelCom System\n");

  // load background screens
  if (!(cfexist(TELCOM_DISPLAY_OGF))) {
    mprintf(0, "%s file not found, exiting TelCom Init\n", TELCOM_DISPLAY_OGF);
    return;
  }

  if (!LoadTelcomBitmap(TELCOM_DISPLAY_OGF, &Telcom_bitmap))
    Error("Unable to open %s in TelCom system.", TELCOM_DISPLAY_OGF);

  TelCom_init = true;

  // init telcom system structs
  InitSystems();

  atexit(TelComFree);

  TelcomPageAllIn();
}

// Cleanup crew, don't worry about calling this guy, it's an atexit() in the init
void TelComFree() { bm_DestroyChunkedBitmap(&Telcom_bitmap); }

// This is the main loop for the active TelCom...think of it as a void main(void)
void TelComMain(bool ingame, bool SelectShip) {
  // Initialize sound system
  TelcomInitSounds();

  // Initialize screens
  InitAllScreens();

  // Initialize the Effects
  EfxInit();

  // Initialize the Telcom Render Engine
  TelcomRenderInit();

  // Initialize the TelCom System Event Manager
  TelComInitEventManager();
  TelcomRenderSetScreen(DUMMY_SCREEN);

  // kinda a quick hack...it may stay only if there is no way to enter the briefings directly from the game
  bool noescape = false;
  if (!ingame)
    noescape = true;

  Telcom_system.state = TCS_POWERON;

  TelcomCreateStartupScreen();

  TelcomStartSound(TCSND_STARTUP);
  TelcomStartSound(TCSND_RUNNING);
  TelcomStopSound(TCSND_STARTUP);

  // #ifdef DEMO
  //	Telcom_system.current_status = TS_MISSION;
  // #endif

  // initialize this to -1 so we get events right away
  Telcom_mouse_last_effect = -1;

  // if we are coming from the game into the main menu, then any system we select, when
  // we exit should take us back to main menu
  bool return_to_main_menu = false;
  if (ingame && Telcom_system.current_status == TS_MAINMENU) {
    return_to_main_menu = true;
  }

  while (Telcom_system.state != TCS_POWEROFF) {

    TelComEnableSystemKey(TCSYS_MAXKEYS, true);

    switch (Telcom_system.current_status) {
    case TS_MISSION:
      // if we are in briefings, then show the briefing
      if (Current_level->flags & LVLFLAG_BRIEFING) {
        // determine the correct language of briefing to look at
        char basefilename[_MAX_FNAME];
        char briefingname[_MAX_FNAME];
        char extension[_MAX_FNAME];
        const char *tag[] = {"", "_GER", "_SPN", "_ITN", "_FRN"};
        bool ok_to_go = false;

        ddio_SplitPath(Current_level->briefname, NULL, basefilename, extension);

        strcpy(briefingname, basefilename);
        strcat(briefingname, tag[Localization_GetLanguage()]);
        strcat(briefingname, extension);

        if (!cfexist(briefingname)) {
          // language version doesn't exist
          strcpy(briefingname, Current_level->briefname);

          if (cfexist(briefingname)) {
            ok_to_go = true;
          }

        } else {
          ok_to_go = true;
        }

        if (ok_to_go) {
          ParseBriefing(briefingname, &Telcom_system);

          if (return_to_main_menu && (!((Game_mode & GM_MULTI) && Multi_bail_ui_menu))) {
            // return to main menu
            Telcom_system.current_status = TS_MAINMENU;
            Telcom_system.state = TCS_POWERON;
          }

        } else {
          Telcom_system.current_status = TS_OFF;
        }
      } else {
        Telcom_system.current_status = TS_OFF;
      }
#ifdef DEMO
      // Telcom_system.state=TCS_POWEROFF;
#endif
      break;
    case TS_MAP:
      TelComAutoMap(&Telcom_system);
      if (return_to_main_menu && (!((Game_mode & GM_MULTI) && Multi_bail_ui_menu))) {
        // return to main menu
        Telcom_system.current_status = TS_MAINMENU;
        Telcom_system.state = TCS_POWERON;
      }

#ifdef DEMO
      // Telcom_system.state=TCS_POWEROFF;
#endif
      break;
    case TS_CARGO:
#ifdef DEMO
      // Telcom_system.state=TCS_POWEROFF;
#else
      // show the inventory information
      TelComCargo(&Telcom_system);
      if (return_to_main_menu && (!((Game_mode & GM_MULTI) && Multi_bail_ui_menu))) {
        // return to main menu
        Telcom_system.current_status = TS_MAINMENU;
        Telcom_system.state = TCS_POWERON;
      }
#endif
      break;
    case TS_GOALS:
      // show goal screen
      TelComGoalStatus(&Telcom_system);
      if (return_to_main_menu && (!((Game_mode & GM_MULTI) && Multi_bail_ui_menu))) {
        // return to main menu
        Telcom_system.current_status = TS_MAINMENU;
        Telcom_system.state = TCS_POWERON;
      }
      break;
    default:
      if (!noescape) {
        // display main menu
        TelComMainMenu(&Telcom_system);
      } else {
        Telcom_system.state = TCS_POWEROFF;
      }
      break;
    }
  }

  TelcomStopSound(TCSND_TYPING);

  // see if we should display the Single Player Ship Selection
#if (!defined(DEMO)) && (!defined(OEM))
  if (SelectShip && !Telcom_exit_to_mainmenu)
    TelComSingleShipSelect(&Telcom_system);
#endif

  TelcomStopSound(TCSND_STARTUP);
  TelcomStopSound(TCSND_RUNNING);
  TelcomStartSound(TCSND_SHUTDOWN);

  TelcomCreateShutdownScreen();
  TelcomRenderSetScreen(DUMMY_SCREEN);

  float starttime = timer_GetTime();

  while (timer_GetTime() - starttime < TCPE_TIME) {
    // Process all waiting events for the TelCom	(we may only want to handle this once a frame!)
    TelComHandleAllEvents(&Telcom_system);
    TelcomRenderScreen(false, false, 2);
    Descent->defer();
  }

  TelcomStopSound(TCSND_SHUTDOWN);

  TelcomCloseSounds();

  TelcomRenderClose();

  DestroyAllScreens(true);

  EfxClose();
}

// This will make the TelCom system active, displaying it on the screen.  This version of TelComShow() takes
// a system as an argument and it will display that system
// Returns true on success
bool TelComShow(int system, bool ingame, bool ShipSelect) {
  if (system > NUMBER_OF_SYSTEMS)
    Telcom_system.current_status = TS_OFF;

  Telcom_system.current_status = system;
  return TelComShow(ingame, ShipSelect);
}

// This will make the TelCom system active, displaying it on the screen.  This version of TelComShow() will make
// whatever the current system (either whatever the last system to be displayed or whatever TelComSetSystem() set
// it to.
// Returns true on success

// externed from GameLoop.cpp
extern bool Skip_render_game_frame;

bool TelComShow(bool ingame, bool ShipSelect) {
  Skip_render_game_frame = true;
  Telcom_called_from_game = ingame;

  bool result = false;
  int old_sm;

  Telcom_exit_to_mainmenu = false;

  // must do this to clear out keyboard events
  ddio_KeyFlush();

  uint8_t oldmip = Render_preferred_state.mipping;
  uint8_t oldbil = Render_preferred_state.filtering;

  if (!TelCom_init) {
    mprintf(0, "TELCOM SYSTEM WARNING: TelComInit() error!\n");
    return false;
  }

  // Set Screen mode
  old_sm = GetScreenMode();
  SetScreenMode(SM_MENU);

  hotspot_bitmaps = NULL;

  int TelCom_bitmap = bm_AllocLoadFileBitmap(IGNORE_TABLE(TELCOM_DISPLAY_OGF), 0);
  if (!cfexist(HOTSPOT_DISPLAY)) {
    mprintf(0, "Couldn't find HotSpot map, so I'm going to make one\n");
    if (!cfexist(TELCOM_DISPLAY_TGA)) {
      mprintf(0, "Unable to find %s to extract HotSqpots...skipping TelCom System\n", TELCOM_DISPLAY_TGA);
      FreeViewports();
      if (windowmap.wm)
        mem_free(windowmap.wm);
      goto telcom_bad_error;
    }
    menutga_ConvertTGAtoHSM(TELCOM_DISPLAY_TGA);
  }

  // Load up the hotspot map into the structure
  menutga_LoadHotSpotMap(TelCom_bitmap, IGNORE_TABLE(HOTSPOT_DISPLAY), &hotspotmap, &windowmap);
  if (TelCom_bitmap >= 0)
    bm_FreeBitmap(TelCom_bitmap);

  if (hotspotmap.num_of_hotspots) {
    int TelCom_onbmp = bm_AllocLoadFileBitmap(IGNORE_TABLE(TELCOM_DISPLAY_OGF_ON), 0);
    if (TelCom_onbmp != -1) {
      hotspot_bitmaps = (chunked_bitmap *)mem_malloc(sizeof(chunked_bitmap) * hotspotmap.num_of_hotspots);
      ASSERT(hotspot_bitmaps);
      CompressTelComOnImage(TelCom_onbmp, hotspot_bitmaps);
      bm_FreeBitmap(TelCom_onbmp);
    }
  }

  // turn off mipmapping
  Render_preferred_state.mipping = 0;
  // turn off bilinear filtering
  Render_preferred_state.filtering = 1;
  rend_SetPreferredState(&Render_preferred_state);
  rend_SetFiltering(0);

  // keep the mouse in view
  ddio_MouseReset();
  ddio_MouseSetVCoords(Game_window_w, Game_window_h);

  // hang out in here until the user presses POWER
  TelComMain(ingame, ShipSelect);

  // do some final deactivation
  TelComDeactivate();

  result = true;

telcom_bad_error:

  if (hotspot_bitmaps)
    mem_free(hotspot_bitmaps);

  // must do this to clear out keyboard events
  ddio_KeyFlush();

  // reset screen mode
  SetScreenMode(old_sm);

  // reset some states
  rend_SetZBufferState(1);
  Render_preferred_state.mipping = oldmip;
  Render_preferred_state.filtering = oldbil;
  rend_SetPreferredState(&Render_preferred_state);
  rend_SetFiltering(1);
  rend_SetWrapType(WT_WRAP);

  Skip_render_game_frame = false;

  return Telcom_exit_to_mainmenu;
}

// Initializes the systems so it has correct values
void InitSystems() {
  Telcom_system.current_status = TS_MISSION;
  Telcom_system.state = TCS_POWERON;
}

// Frees allocated memory used by the windows
void FreeViewports() {
  int count;

  if (windowmap.wm) {
    for (count = 0; count < windowmap.num_of_windows; count++) {
      if (windowmap.wm[count].lt_bmp > BAD_BITMAP_HANDLE)
        bm_FreeBitmap(windowmap.wm[count].lt_bmp);
      if (windowmap.wm[count].rt_bmp > BAD_BITMAP_HANDLE)
        bm_FreeBitmap(windowmap.wm[count].rt_bmp);
      if (windowmap.wm[count].lb_bmp > BAD_BITMAP_HANDLE)
        bm_FreeBitmap(windowmap.wm[count].lb_bmp);
      if (windowmap.wm[count].rb_bmp > BAD_BITMAP_HANDLE)
        bm_FreeBitmap(windowmap.wm[count].rb_bmp);
    }
  }
}

// This function 'compresses' the on-state background, to save space
void CompressTelComOnImage(int bitmap, chunked_bitmap *array) {
  if (!array)
    return;
  int count;
  int width, height;
  int handle;

  // the first hotspot bitmap doesn't exist so we can skip it
  for (count = 1; count < hotspotmap.num_of_hotspots; count++) {
    width = HotSpotW(count);
    ASSERT(width != -1); // DAJ -1FIX
    height = HotSpotH(count);
    ASSERT(height != -1); // DAJ -1FIX
    handle = bm_AllocBitmap(width, height, 0);
    TelCom_BltToMem(handle, 0, 0, bitmap, HotSpotL(count), HotSpotT(count), width, height);
    bm_CreateChunkedBitmap(handle, &array[count]);
    bm_FreeBitmap(handle);
  }
}

// frees up on-state bitmaps
void FreeTelComOnBitmaps(chunked_bitmap *array) {
  if (!array)
    return;
  int count;

  // the first hotspot bitmap doesn't exist, so we can skip it
  for (count = 1; count < hotspotmap.num_of_hotspots; count++) {
    bm_DestroyChunkedBitmap(&array[count]);
  }
}

// This deactivates the TelCom system
void TelComDeactivate(void) {
  mprintf(0, "TelCom System being deactivated\n");
  FreeTelComOnBitmaps(hotspot_bitmaps);
  FreeHotSpotMapInternals(&hotspotmap);
  FreeViewports();
  if (windowmap.wm)
    mem_free(windowmap.wm);
}

// draws a hotspot with the on bitmap
void DrawHotSpotOn(int hotspot) {
  if (!hotspot_bitmaps)
    return;
  if ((hotspot < 0) || (hotspot >= hotspotmap.num_of_hotspots))
    return;
  TelCom_BltToScreen(HotSpotL(hotspot), HotSpotT(hotspot), &hotspot_bitmaps[hotspot]);
}

//	---------------------------------------------------------------------------
//	performs 16-bit blts.

void TelCom_BltToScreen(int dx, int dy, chunked_bitmap *src_bmp) {
  TelCom_BltToScreen(dx, dy, src_bmp, 0, 0, src_bmp->pw, src_bmp->ph);
}

void TelCom_BltToScreen(int dx, int dy, chunked_bitmap *src_bmp, int sx, int sy, int sw, int sh) {
  rend_DrawScaledChunkedBitmap(src_bmp, dx, dy, sw, sh, 255);
}

void TelCom_BltToMem(int dest_bmp, int dx, int dy, int src_bmp, int sx, int sy, int sw, int sh, bool trans) {
  uint16_t *dbits;
  uint16_t *sbits;
  int srowsize_w, drowsize_w, row, col;

  //	set up blt.
  srowsize_w = bm_w(src_bmp, 0); // rowsize in shorts
  drowsize_w = bm_w(dest_bmp, 0);
  dbits = (uint16_t *)bm_data(dest_bmp, 0) + (dy * drowsize_w) + dx;
  sbits = (uint16_t *)bm_data(src_bmp, 0) + (sy * srowsize_w) + sx;

  if (trans) {
    for (row = 0; row < sh; row++) {
      for (col = 0; col < sw; col++)
        if (sbits[col] & OPAQUE_FLAG)
          dbits[col] = sbits[col];

      sbits += srowsize_w;
      dbits += drowsize_w;
    }
  } else {
    for (row = 0; row < sh; row++) {
      for (col = 0; col < sw; col++)
        dbits[col] = sbits[col];

      sbits += srowsize_w;
      dbits += drowsize_w;
    }
  }
}

// returns left edge of hotspot
int HotSpotL(int hotspot) {
  if (hotspot >= hotspotmap.num_of_hotspots)
    return -1;
  return hotspotmap.hs[hotspot].x[0].start;
}

// returns width of hotspot
int HotSpotW(int hotspot) {
  if (hotspot >= hotspotmap.num_of_hotspots)
    return -1;
  return hotspotmap.hs[hotspot].x[0].end - hotspotmap.hs[hotspot].x[0].start + 1;
}

// returns the top edge of a hotspot
int HotSpotT(int hotspot) {
  if (hotspot >= hotspotmap.num_of_hotspots)
    return -1;
  return hotspotmap.hs[hotspot].starting_y;
}

// returns the height of a hotspot
int HotSpotH(int hotspot) {
  if (hotspot >= hotspotmap.num_of_hotspots)
    return -1;
  return hotspotmap.hs[hotspot].scanlines;
}

// returns the right edge of a hotspot
int HotSpotR(int hotspot) {
  if (hotspot >= hotspotmap.num_of_hotspots)
    return -1;
  return hotspotmap.hs[hotspot].x[0].end;
}

// returns the bottom edge of a hotspot
int HotSpotB(int hotspot) {
  if (hotspot >= hotspotmap.num_of_hotspots)
    return -1;
  return hotspotmap.hs[hotspot].starting_y + hotspotmap.hs[hotspot].scanlines;
}

int LoadTelcomBitmap(const char *filename, chunked_bitmap *chunk) {
  int bm_handle = bm_AllocLoadFileBitmap(IGNORE_TABLE(filename), 0);
  if (bm_handle == -1)
    return 0;

  // make monitor windows transparent
  menutga_LoadHotSpotMap(bm_handle, IGNORE_TABLE(HOTSPOT_DISPLAY), &hotspotmap, &windowmap);

  uint16_t *data = bm_data(bm_handle, 0);
  int wnd, x, y, bmw;
  int bord_left, bord_right, bord_top, bord_bottom;

  bmw = bm_w(bm_handle, 0);

  int starty, startx, endy, endx;
  for (wnd = 0; wnd < windowmap.num_of_windows; wnd++) {
    bord_left = windowmap.wm[wnd].l_start_x - windowmap.wm[wnd].x;
    bord_right = windowmap.wm[wnd].x + windowmap.wm[wnd].width - windowmap.wm[wnd].r_end_x;
    bord_top = windowmap.wm[wnd].t_top_y - windowmap.wm[wnd].y;
    bord_bottom = windowmap.wm[wnd].y + windowmap.wm[wnd].height - windowmap.wm[wnd].b_bottom_y;

    starty = windowmap.wm[wnd].y + bord_top;
    endy = windowmap.wm[wnd].y + windowmap.wm[wnd].height - bord_bottom;
    startx = windowmap.wm[wnd].x + bord_left;
    endx = windowmap.wm[wnd].x + windowmap.wm[wnd].width - bord_right;
    for (y = starty; y < endy; y++)
      for (x = startx; x < endx; x++) {
        data[y * bmw + x] = NEW_TRANSPARENT_COLOR;
      }
  }

  FreeHotSpotMapInternals(&hotspotmap);
  FreeViewports();
  if (windowmap.wm)
    mem_free(windowmap.wm);

  bm_CreateChunkedBitmap(bm_handle, chunk);

  if (bm_handle > BAD_BITMAP_HANDLE)
    bm_FreeBitmap(bm_handle);

  return 1;
}

#define MAINMENU_BUTTON "TelComMenuButton.ogf"
#define MAINMENU_BUTTONGLOW "TelComMenuButtonGlow.ogf"
#define MAINMENU_BUTTONFOCUS "Forward.ogf"
#define MAINMENU_BUTTONGLOWFOCUS "ForwardFocus.ogf"
/*
$$TABLE_GAMEFILE "TelComMenuButton.ogf"
$$TABLE_GAMEFILE "TelComMenuButtonGlow.ogf"
$$TABLE_GAMEFILE "Forward.ogf"
$$TABLE_GAMEFILE "ForwardFocus.ogf"
*/
#define BOFF_L 40
#define BOFF_T 15
#define MM_BUTTONX 99
#define MM_BUTTONY 60
#define MM_BUTTONOFFSET 50

// Main Menu button info
#define TCBRIEFING 0
#define TCCARGO 1
#define TCAUTOMAP 2
#define TCGOALS 3
#define TCMAX_MMBUTTONS 4

int TCMMButtonDesc[] = {TXI_TCMM_BRIEFINGS, TXI_TCMM_CARGO, TXI_TCMM_AUTOMAP, TXI_TCMM_GOALS};

int mainmenu_system;

struct tMenuButton {
  bool enabled;
  int efxid;
  int system;
  char text[128];
};
tMenuButton MMButtons[TCMAX_MMBUTTONS];

void TCMainMenuCallback(int efxnum) { mainmenu_system = efxnum; }
void TCMainMenuRenderCallback(void) {
  grtext_SetFont(BIG_BRIEFING_FONT);
  grtext_SetColor(GR_RGB(255, 255, 255));
  grtext_SetAlpha(255);

  int mm_y, mm_x;
  mm_y = Telcom_system.Monitor_coords[MONITOR_MAIN].top + BOFF_T + MM_BUTTONY;
  mm_x = Telcom_system.Monitor_coords[MONITOR_MAIN].left + BOFF_L + MM_BUTTONX;

  for (int i = 0; i < TCMAX_MMBUTTONS; i++) {
    if (MMButtons[i].enabled) {
      // draw the button text
      grtext_Printf(mm_x, mm_y, MMButtons[i].text);

      // adjust y value
      mm_y += MM_BUTTONOFFSET;
    }
  }
}

// Main menu
bool TelComMainMenu(tTelComInfo *tcs) {
  bool exitparse = false;
  int mm;

  mainmenu_system = -1;

  DestroyAllScreens();

  for (mm = 0; mm < TCMAX_MMBUTTONS; mm++) {
    MMButtons[mm].enabled = false;
    MMButtons[mm].system = TS_OFF;
  }

  TCBKGDESC backg;
  backg.color = BACKGROUND_COLOR;
  backg.caps = TCBGD_COLOR;
  backg.type = TC_BACK_STATIC;

  TCBMPDESC bmpdesc;
  bmpdesc.type = TC_BMP_STATIC;
  bmpdesc.flags = 0;
  bmpdesc.caps = TCBD_XY;
  bmpdesc.x = 0;
  bmpdesc.y = 0;
  strcpy(bmpdesc.filename, "TelComMainMenu.ogf");
  /*
  $$TABLE_GAMEFILE "TelComMainMenu.ogf"
  */

  TCTEXTDESC textdesc;
  textdesc.type = TC_TEXT_STATIC;
  textdesc.font = BBRIEF_FONT_INDEX;
  textdesc.caps = TCTD_TEXTBOX | TCTD_COLOR | TCTD_FONT;
  textdesc.textbox.left = 65;
  textdesc.textbox.right = 380;
  textdesc.textbox.top = 2;
  textdesc.textbox.bottom = 50;
  textdesc.color = GR_RGB(255, 255, 255);

  TCBUTTONDESC buttdesc;
  strcpy(buttdesc.filename, MAINMENU_BUTTON);
  strcpy(buttdesc.flash_filename, MAINMENU_BUTTONGLOW);

#if 0 // def DEMO
      // strcpy(buttdesc.filename_focus,			MAINMENU_BUTTONFOCUS);
      // strcpy(buttdesc.flash_filename_focus,	MAINMENU_BUTTONGLOWFOCUS);
#else
  strcpy(buttdesc.filename_focus, MAINMENU_BUTTONGLOW);
  strcpy(buttdesc.flash_filename_focus, MAINMENU_BUTTONGLOW);
#endif
  buttdesc.sibling_id = buttdesc.parent_id = -1;
  buttdesc.internal = TCMainMenuCallback;
  buttdesc.flash_time = 0;
  buttdesc.button_type = BUTT_INTERNAL;
  buttdesc.flasher = true;
  buttdesc.click_type = CLICKTYPE_CLICKUP;
  buttdesc.osflags = OBF_GLOW | OBF_MOUSEOVERFOCUS;
  buttdesc.x = 0;
  buttdesc.y = 0;
  buttdesc.tab_stop = true; // all main menu buttons can have focus

  // Add effects to screen 0
  TelcomStartScreen(0);
  CreateBitmapEffect(&bmpdesc, MONITOR_MAIN, 0);

  int mm_y, mm_x;
  mm_y = MM_BUTTONY + Telcom_system.Monitor_coords[MONITOR_MAIN].top;
  mm_x = MM_BUTTONX + Telcom_system.Monitor_coords[MONITOR_MAIN].left;

  bool ok_to_run = false;

  // Now create all the main menu buttons
  for (mm = 0; mm < TCMAX_MMBUTTONS; mm++) {
    // first determine if this button should be enabled (they are all disabled by default)
    // also set all the systems in here
    switch (mm) {
    case TCBRIEFING:
      // Briefings should only be enabled if there is a briefing
      if (Current_level->flags & LVLFLAG_BRIEFING) {
        MMButtons[mm].enabled = true;
        MMButtons[mm].system = TS_MISSION;
        ok_to_run = true;
      } else {
        MMButtons[mm].enabled = false;
        MMButtons[mm].system = TS_OFF;
      }
      break;
    case TCCARGO:
      // #if (defined DEMO)||(defined OEM)
      MMButtons[mm].enabled = false;
      MMButtons[mm].system = TS_OFF;
      /*
      #else
                              //Cargo should only be enabled if we are in the game
                              if(Telcom_called_from_game){
                                      MMButtons[mm].enabled = true;
                                      MMButtons[mm].system = TS_CARGO;
                                      ok_to_run = true;
                              }else{
                                      MMButtons[mm].enabled = false;
                                      MMButtons[mm].system = TS_OFF;
                              }
      #endif
      */
      break;
    case TCGOALS:
      if (Telcom_called_from_game) {
        MMButtons[mm].enabled = true;
        MMButtons[mm].system = TS_GOALS;
        ok_to_run = true;
      } else {
        MMButtons[mm].enabled = false;
        MMButtons[mm].system = TS_OFF;
      }
      break;
    case TCAUTOMAP:
      // Automap should only be enabled if we are in the game
      if (Telcom_called_from_game) {
        MMButtons[mm].enabled = true;
        MMButtons[mm].system = TS_MAP;
        ok_to_run = true;
      } else {
        MMButtons[mm].enabled = false;
        MMButtons[mm].system = TS_OFF;
      }
      break;
    }

    strcpy(MMButtons[mm].text, TXT(TCMMButtonDesc[mm]));

    // now if it's enabled,fill in it's info
    // create the button
    if (MMButtons[mm].enabled) {
      buttdesc.x = mm_x;
      buttdesc.y = mm_y;
      MMButtons[mm].efxid = CreateButtonEffect(&buttdesc, MONITOR_MAIN, 0);
      // adjust y
      mm_y += MM_BUTTONOFFSET;
    } else {
      MMButtons[mm].efxid = -1;
    }
  }

  if (!ok_to_run) {
    // no systems available
    tcs->state = TCS_POWEROFF;
  }

  CreateBackgroundEffect(&backg, MONITOR_TOP, 0);
  CreateTextEffect(&textdesc, format(TXT_TCMAINMENU), MONITOR_TOP, 0);
  TelcomEndScreen();

  TelcomRenderSetCallback(TCMainMenuRenderCallback);

  // Set the screen active
  TelcomRenderSetScreen(0);

  bool done = false;

  TelCom_ClearCustomKeyEvents();
  TelCom_AddCustomKeyEvent(KEY_DOWN, 0x13); // down arrow
  TelCom_AddCustomKeyEvent(KEY_UP, 0x14);   // up arrow

  while (!done) {
    Sound_system.BeginSoundFrame(Telcom_called_from_game);

    if (tcs->state == TCS_POWEROFF || mainmenu_system != -1 || tcs->current_status != TS_OFF) {
      // we're done with the loop
      done = true;

      if (mainmenu_system != -1) {
        // go through the buttons and compare efx id's
        for (int i = 0; i < TCMAX_MMBUTTONS; i++) {
          if (MMButtons[i].enabled && MMButtons[i].efxid == mainmenu_system) {
            // we found our system
            tcs->current_status = MMButtons[i].system;
          } // endif
        }   // endfor
      }     // endif
    }

    // Process all waiting events for the TelCom	(we may only want to handle this once a frame!)
    TelComHandleAllEvents(&Telcom_system);

    // Process custom events
    tTCEvent evt;
    while (TelCom_PopSystemEvent(&evt)) {
      switch (evt.id) {
      case 0x13: // up arrow
        TelComSendEvent(TEVT_FAKEKEYPRESS, TCSYS_TAB);
        break;
      case 0x14: // down arrow
        TelComSendEvent(TEVT_FAKEKEYPRESS, TCSYS_REVERSETAB);
        break;
      }
    }

    TelcomRenderScreen();
    Descent->defer();
    if (KEY_STATE(KEY_ESC))
      Telcom_system.state = TCS_POWEROFF;

    Sound_system.EndSoundFrame();
  }
  TelCom_ClearCustomKeyEvents();

  DestroyAllScreens();
  TelcomRenderSetScreen(DUMMY_SCREEN);
  TelcomRenderSetCallback(NULL);
  return true;
}

/*
 ************************************************************************
 *				TelCom Render Functions *
 ************************************************************************
 *
 */
/// internal prototypes *************************************
//	Creates the screen overlays for the main monitor
static void TelcomCreateScreenOverlays(void);
//	Destroys the screen overlays that were used for the main monitor
static void TelcomDestroyScreenOverlays(void);
//	Renders the screen overlays
static void TelcomRenderOverlays(void);
//	Renders the screen hilights
static void TelcomRenderDrawHiLites(void);
//	Loads the Hilites for a monitor
static void TelcomLoadHiLites(const char *filelist[], int monitor, int xoff, int yoff);
//	Frees all the memory allocated for the hilites
static void TelcomFreeHiLites(void);
//	Renders the scanline to be drawn
static void TelcomRenderScanline(void);
//	Creates the scanline
static void TelcomCreateScanLine(void);
//	Destroys the scanline
static void TelcomDestroyScanLine(void);
//	Loads the mouse cursor
static void TelcomLoadMouseCursor(void);
//	Frees the mouse cursor
static void TelcomFreeMouseCursor(void);
//	Renders the mouse cursor
static void TelcomRenderMouse(void);
// draws the telcom background, handles flickering lights, power button etc
static void TelcomDrawScreen(bool poweron, bool powerup);
// used to display the rounded corners of the monitor screens
static void TelcomDisplayCorners(void);
//	Frees the bitmaps used for the corners of each monitor
static void TelcomFreeCorners(void);
//	Allocates the bitmaps for corners of each monitor
static void TelcomCreateCorners(void);
//	Displays static on the screen
static void TelcomDisplayStatic(float amount);
//	Frees the static bitmap overlays
static void TelcomFreeStaticOverlays(void);
//	Creates the static bitmap overlays
static void TelcomCreateStaticOverlays(void);
//	Initializes the bitmaps, etc needed for power up/down effect
static void TelcomInitPowerEffect(void);
//	Frees the bitmaps, etc for power up/down effect
static void TelcomFreePowerEffect(void);
//	Draws a frame of the power up/down effect
static void TelcomDoPowerEffect(bool power_down, float frametime);

/// global variables ****************************************
// Telcom rendering globals
static void (*TC_callback)() = NULL;
static int TC_current_screen = DUMMY_SCREEN;
int TC_cursor = -1;

// Monitor hilight variables
static int TelcomHiLiteCount[MAX_MONITOR];
static int *TelcomHiLites[MAX_MONITOR];
struct {
  int x, y;
} TelcomHiLiteOffset[MAX_MONITOR];
// Main monitor scanline info
static float scanline_nexttime, scanline_speed;
static int scanliney, scanline_handle;
static float last_rendertime = 0;
float last_frametime = 0;
// Monitor corner variables
static chunked_bitmap lt_corners[MAX_MONITOR];
static chunked_bitmap rt_corners[MAX_MONITOR];
static chunked_bitmap lb_corners[MAX_MONITOR];
static chunked_bitmap rb_corners[MAX_MONITOR];
static bool has_corners[MAX_MONITOR];
// Screen variables
static int TCWorking_screen;
// Static variables
#define STATIC_BMPS 12
static int StaticBmps[STATIC_BMPS];
static bool Telcom_show_static = false;
static bool Telcom_static_last_frame = false;
static float Telcom_static_setting = 0;
// Glitch variables
static bool Telcom_show_glitch = false;
static bool Telcom_glitch_screen = false;
static float Telcom_glitch_setting = 0;
static float myrand(float max);
// Powereffect variables
static int PowerBmps[2];

//	Initializes the Telcom rendering engine
void TelcomRenderInit(void) {
  for (int monitor = 0; monitor < MAX_MONITOR; monitor++) {
    ASSERT(monitor < windowmap.num_of_windows);

    Telcom_system.Monitor_coords[monitor].left = windowmap.wm[monitor].x;
    Telcom_system.Monitor_coords[monitor].top = windowmap.wm[monitor].y;
    Telcom_system.Monitor_coords[monitor].right = windowmap.wm[monitor].x + windowmap.wm[monitor].width;
    Telcom_system.Monitor_coords[monitor].bottom = windowmap.wm[monitor].y + windowmap.wm[monitor].height;

    // Do we want to save these seperatly?
    Telcom_system.Monitor_coords[monitor].left += windowmap.wm[monitor].l_start_x - windowmap.wm[monitor].x;
    Telcom_system.Monitor_coords[monitor].right -=
        windowmap.wm[monitor].x + windowmap.wm[monitor].width - windowmap.wm[monitor].r_end_x;
    Telcom_system.Monitor_coords[monitor].top += windowmap.wm[monitor].t_top_y - windowmap.wm[monitor].y;
    Telcom_system.Monitor_coords[monitor].bottom -=
        windowmap.wm[monitor].y + windowmap.wm[monitor].height - windowmap.wm[monitor].b_bottom_y;
  }

  TC_callback = NULL;
  TC_current_screen = DUMMY_SCREEN;
  TelcomCreateScreenOverlays();
  last_rendertime = timer_GetTime();
  TelcomCreateDummyScreen();
  TelcomRenderSetScreen(DUMMY_SCREEN);
  TelcomDisableGlitch();
  TelcomDisableStatic();
  Telcom_first_render = true;
}

//	Closes down the Telcom rendering engine
void TelcomRenderClose(void) {
  TelcomDestroyScreenOverlays();
  TC_current_screen = DUMMY_SCREEN;
}

//	Renders the current screen for 1 frame
void TelcomRenderScreen(bool poweron, bool powerup, uint8_t power_effect) {
  if (TC_current_screen == -1)
    return;

  float frametime, newtime;
  newtime = timer_GetTime();

  float cap_time = last_rendertime + (1.0f / FRAME_RATE);
  if (cap_time > newtime) {
    Descent->delay(cap_time - newtime);
    newtime = timer_GetTime();
  }

  frametime = newtime - last_rendertime;
  last_rendertime = newtime;
  last_frametime = frametime;

  if (Telcom_first_render) {
    Telcom_first_render = false;
    frametime = 0;
  }

  StartFrame(0, 0, Game_window_w, Game_window_h);

  if (Telcom_show_glitch) {
    if (((int)myrand(100 * (1.0 - Telcom_glitch_setting))) == 0) {
      Telcom_glitch_screen = true;
      glitch_dx = (int)(myrand(20) - 10.0);
      glitch_dy = (int)(myrand(12) - 6.0);
    }
  }

  // first render all the effects
  RenderScreen(TC_current_screen, &Telcom_system, frametime);

  // call the callback if it exists to render anything on the monitor screen
  if (TC_callback)
    TC_callback();

  // Render the screen overlays
  TelcomRenderOverlays();

  grtext_Flush();

  switch (power_effect) {
  case 1:
    TelcomDoPowerEffect(false, frametime);
    break;
  case 2:
    TelcomDoPowerEffect(true, frametime);
    break;
  };

  // Draw the TelCom System
  TelcomDrawScreen(poweron, powerup);

  TelcomRenderMouse();

  EndFrame();
  rend_Flip();

  Telcom_glitch_screen = false;
}

//	Sets the callback of the Render.  This will get called after Effects are drawn, before the screen overlays
void TelcomRenderSetCallback(void (*callback)()) { TC_callback = callback; }

//	Sets what screen should be drawn by the Telcom
void TelcomRenderSetScreen(int screen) {
  ASSERT(screen >= 0 && screen < MAX_TELCOM_SCREENS);

  if (Telcom_system.Screen_state[screen] != SS_READY) {
    mprintf(0, "Telcom Warning: Trying to set screen %d active when it isn't ready\n", screen);
    return;
  }
  TC_current_screen = screen;
}

//	Creates a placeholder screen that can be used if no screens are available
void TelcomCreateDummyScreen(void) {
  TelcomStartScreen(DUMMY_SCREEN);

  TCBKGDESC backg;
  backg.color = BACKGROUND_COLOR;
  backg.caps = TCBGD_COLOR;
  backg.type = TC_BACK_STATIC;
  TCBMPDESC bmpdesc;
  bmpdesc.caps = 0;
  bmpdesc.type = TC_BMP_STATIC;
  bmpdesc.flags = 0;
  strcpy(bmpdesc.filename, "TelComInit.ogf");
  /*
  $$TABLE_GAMEFILE "TelComInit.ogf"
  */
  TCTEXTDESC textdesc;
  textdesc.type = TC_TEXT_FADE;
  textdesc.flags = TC_TEXTF_IN;
  textdesc.speed = 1.0f;
  textdesc.font = BBRIEF_FONT_INDEX;
  textdesc.caps = TCTD_TEXTBOX | TCTD_COLOR | TCTD_SPEED | TCTD_FONT;
  textdesc.textbox.left = 25;
  textdesc.textbox.right = 540;
  textdesc.textbox.top = 113;
  textdesc.textbox.bottom = 260;
  textdesc.color = GR_RGB(255, 255, 255);

  CreateBitmapEffect(&bmpdesc, MONITOR_MAIN, DUMMY_SCREEN);
#ifdef DEMO
  // CreateTextEffect(&textdesc,TXT_TCINITIALIZING,MONITOR_MAIN,DUMMY_SCREEN);
#else
  CreateTextEffect(&textdesc, TXT_TCPLEASEWAIT, MONITOR_MAIN, DUMMY_SCREEN);
#endif
  CreateBackgroundEffect(&backg, MONITOR_TOP, DUMMY_SCREEN);

  TelcomEndScreen();
}

//	Creates a placeholder screen that can be used for startup
void TelcomCreateStartupScreen(void) {
  TelcomStartScreen(DUMMY_SCREEN);

  TCBKGDESC backg;
  backg.color = BACKGROUND_COLOR;
  backg.caps = TCBGD_COLOR;
  backg.type = TC_BACK_STATIC;
  TCBMPDESC bmpdesc;
  bmpdesc.caps = 0;
  bmpdesc.type = TC_BMP_STATIC;
  bmpdesc.flags = 0;
  strcpy(bmpdesc.filename, "TelComInit.ogf");
  /*
  $$TABLE_GAMEFILE "TelComInit.ogf"
  */
  TCTEXTDESC textdesc;
  textdesc.type = TC_TEXT_FADE;
  textdesc.flags = TC_TEXTF_IN;
  textdesc.speed = 1.0f;
  textdesc.font = BBRIEF_FONT_INDEX;
  textdesc.caps = TCTD_TEXTBOX | TCTD_COLOR | TCTD_SPEED | TCTD_FONT;
  textdesc.textbox.left = 25;
  textdesc.textbox.right = 280;
  textdesc.textbox.top = 113;
  textdesc.textbox.bottom = 260;
  textdesc.color = GR_RGB(255, 255, 255);

  CreateBitmapEffect(&bmpdesc, MONITOR_MAIN, DUMMY_SCREEN);
  CreateTextEffect(&textdesc, TXT_TCPLEASEWAIT, MONITOR_MAIN, DUMMY_SCREEN);
  CreateBackgroundEffect(&backg, MONITOR_TOP, DUMMY_SCREEN);

  TelcomEndScreen();
}

//	Creates a placeholder screen that can be used for shutdown
void TelcomCreateShutdownScreen(void) {
  TelcomStartScreen(DUMMY_SCREEN);

  TCBKGDESC backg;
  backg.color = BACKGROUND_COLOR;
  backg.caps = TCBGD_COLOR;
  backg.type = TC_BACK_STATIC;
  TCBMPDESC bmpdesc;
  bmpdesc.caps = 0;
  bmpdesc.type = TC_BMP_STATIC;
  bmpdesc.flags = 0;
  strcpy(bmpdesc.filename, "TelComInit.ogf");

  /*
  $$TABLE_GAMEFILE "TelComInit.ogf"
  */
  TCTEXTDESC textdesc;
  textdesc.type = TC_TEXT_FADE;
  textdesc.flags = TC_TEXTF_IN;
  textdesc.speed = 1.0f;
  textdesc.font = BBRIEF_FONT_INDEX;
  textdesc.caps = TCTD_TEXTBOX | TCTD_COLOR | TCTD_SPEED | TCTD_FONT;
  textdesc.textbox.left = 25;
  textdesc.textbox.right = 280;
  textdesc.textbox.top = 113;
  textdesc.textbox.bottom = 260;
  textdesc.color = GR_RGB(255, 255, 255);

  CreateBitmapEffect(&bmpdesc, MONITOR_MAIN, DUMMY_SCREEN);
  CreateTextEffect(&textdesc, TXT_TCSHUTDOWN, MONITOR_MAIN, DUMMY_SCREEN);
  CreateBackgroundEffect(&backg, MONITOR_TOP, DUMMY_SCREEN);

  TelcomEndScreen();
}

//	Enables Static on the Telcom main screen, setting is the probability of static happening
void TelcomEnableStatic(float setting) {
  Telcom_show_static = true;
  Telcom_static_setting = setting;
}

//	Disables static on the Telcom main screen
void TelcomDisableStatic(void) {
  Telcom_show_static = false;
  // TCEndStaticSound();
  Telcom_static_last_frame = false;
}

//	Enables glitching on the Telcom main screen
void TelcomEnableGlitch(float setting) {
  Telcom_show_glitch = true;
  Telcom_glitch_setting = setting;
}

//	Disables glitching on the TelCom
void TelcomDisableGlitch(void) { Telcom_show_glitch = false; }

#define NEON_STATEOFF 85.0
#define NEON_OFF 0
#define NEON_OFF2 1
#define NEON_OFF3 2
#define NEON_ON1 10
#define NEON_ON2 11
#define NEON_ON3 12
#define NEON_ON1_TIME 0.05
#define NEON_OFF2_TIME 0.02
#define NEON_ON2_TIME 0.03
#define NEON_OFF3_TIME 0.02
// draws the telcom background, handles flickering lights, power button etc
void TelcomDrawScreen(bool poweron, bool powerup) {
  static int neon_state = NEON_OFF;
  static float start_time = 0;
  static float off_time = 0, on_time = 0;

  if (powerup) {
    neon_state = NEON_OFF;
    start_time = timer_GetTime();
    off_time = myrand(5);
  }

  switch (neon_state) {
  case NEON_OFF:
    if (((timer_GetTime() - start_time) > off_time) && (myrand(100.0) >= NEON_STATEOFF)) {
      start_time = timer_GetTime();
      neon_state = NEON_ON1;
    }
    break;
  case NEON_ON1:
    TelcomStartSound(TCSND_LIGHTBULB);
    if ((timer_GetTime() - start_time) > NEON_ON1_TIME) {
      start_time = timer_GetTime();
      neon_state = NEON_OFF2;
    }
    break;
  case NEON_OFF2:
    if ((timer_GetTime() - start_time) > NEON_OFF2_TIME) {
      start_time = timer_GetTime();
      neon_state = NEON_ON2;
    }
    break;
  case NEON_ON2:
    if ((timer_GetTime() - start_time) > NEON_ON2_TIME) {
      start_time = timer_GetTime();
      neon_state = NEON_OFF3;
    }
    break;
  case NEON_OFF3:
    if ((timer_GetTime() - start_time) > NEON_OFF3_TIME) {
      start_time = timer_GetTime();
      neon_state = NEON_ON3;
      on_time = myrand(3);
    }
    break;
  case NEON_ON3:
    if (((timer_GetTime() - start_time) > on_time) && (myrand(100.0) < NEON_STATEOFF)) {
      start_time = timer_GetTime();
      neon_state = NEON_OFF;
      off_time = myrand(5);
    }
    break;
  }

  rend_SetFiltering(0);

  // draw telcom background
  rend_DrawChunkedBitmap(&Telcom_bitmap, 0, 0, 255);

  if (neon_state >= NEON_ON1)
    DrawHotSpotOn(NEON_LIGHT);
  if (poweron)
    DrawHotSpotOn(POWER_BUTTON);

  rend_SetFiltering(1);

  TelcomDisplayCorners();
}

//	Allocates the bitmaps for corners of each monitor
void TelcomCreateCorners(void) {
  for (int monitor = 0; monitor < MAX_MONITOR; monitor++) {
    if ((windowmap.wm[monitor].t_top_y != -1) && (windowmap.wm[monitor].b_top_y != -1)) {
      bm_CreateChunkedBitmap(windowmap.wm[monitor].lt_bmp, &lt_corners[monitor]);
      bm_CreateChunkedBitmap(windowmap.wm[monitor].rt_bmp, &rt_corners[monitor]);
      bm_CreateChunkedBitmap(windowmap.wm[monitor].lb_bmp, &lb_corners[monitor]);
      bm_CreateChunkedBitmap(windowmap.wm[monitor].rb_bmp, &rb_corners[monitor]);
      has_corners[monitor] = true;
    } else {
      lt_corners[monitor].pw = lt_corners[monitor].ph = 0;
      rt_corners[monitor].pw = rt_corners[monitor].ph = 0;
      lb_corners[monitor].pw = lb_corners[monitor].ph = 0;
      rb_corners[monitor].pw = rb_corners[monitor].ph = 0;
      has_corners[monitor] = false;
    }
  }
}

//	Frees the bitmaps used for the corners of each monitor
void TelcomFreeCorners(void) {
  for (int monitor = 0; monitor < MAX_MONITOR; monitor++) {
    if (!has_corners[monitor])
      continue;

    // destroy the chunked bitmaps of the corners
    if (lt_corners[monitor].pw != 0) {
      bm_DestroyChunkedBitmap(&lt_corners[monitor]);
      lt_corners[monitor].pw = lt_corners[monitor].ph = 0;
    }
    if (rt_corners[monitor].pw != 0) {
      bm_DestroyChunkedBitmap(&rt_corners[monitor]);
      rt_corners[monitor].pw = rt_corners[monitor].ph = 0;
    }
    if (lb_corners[monitor].pw != 0) {
      bm_DestroyChunkedBitmap(&lb_corners[monitor]);
      lb_corners[monitor].pw = lb_corners[monitor].ph = 0;
    }
    if (rb_corners[monitor].pw != 0) {
      bm_DestroyChunkedBitmap(&rb_corners[monitor]);
      rb_corners[monitor].pw = rb_corners[monitor].ph = 0;
    }
  }
}

void TelcomDisplayCorners(void) {
  for (int monitor = 0; monitor < MAX_MONITOR; monitor++) {
    if (!has_corners[monitor])
      continue;

    int left = Telcom_system.Monitor_coords[monitor].left;
    int right = Telcom_system.Monitor_coords[monitor].right;
    int top = Telcom_system.Monitor_coords[monitor].top;
    int bottom = Telcom_system.Monitor_coords[monitor].bottom;

    BltBmpToScreen(left, top, &lt_corners[monitor]);
    BltBmpToScreen(right - rt_corners[monitor].pw, top, &rt_corners[monitor]);
    BltBmpToScreen(left, bottom - lb_corners[monitor].ph, &lb_corners[monitor]);
    BltBmpToScreen(right - rb_corners[monitor].pw, bottom - rb_corners[monitor].ph, &rb_corners[monitor]);
  }
}

const char *hilites[] = {"hilite0", "hilite1", "hilite2", "hilite3", "hilite4", "hilite5", NULL};
const char *smhilites[] = {"smhilite01", "smhilite11", "smhilite21", "smhilite31", "smhilite41",
                     "smhilite51", "smhilite61", "smhilite71", NULL};

/*
$$TABLE_TEXTURE "hilite0"
$$TABLE_TEXTURE "hilite1"
$$TABLE_TEXTURE "hilite2"
$$TABLE_TEXTURE "hilite3"
$$TABLE_TEXTURE "hilite4"
$$TABLE_TEXTURE "hilite5"
$$TABLE_TEXTURE "smhilite01"
$$TABLE_TEXTURE "smhilite11"
$$TABLE_TEXTURE "smhilite21"
$$TABLE_TEXTURE "smhilite31"
$$TABLE_TEXTURE "smhilite41"
$$TABLE_TEXTURE "smhilite51"
$$TABLE_TEXTURE "smhilite61"
$$TABLE_TEXTURE "smhilite71"
*/

//	Creates the screen overlays for the main monitor
void TelcomCreateScreenOverlays(void) {
  TelcomLoadHiLites(hilites, MONITOR_MAIN, 130, -2);
  TelcomLoadHiLites(smhilites, MONITOR_TOP, 0, -8);

  TelcomCreateScanLine();
  TelcomLoadMouseCursor();
  TelcomCreateCorners();
  //	TelcomCreateStaticOverlays();
  TelcomInitPowerEffect();
}

//	Destroys the screen overlays that were used for the main monitor
void TelcomDestroyScreenOverlays(void) {
  TelcomFreeHiLites();
  TelcomDestroyScanLine();
  TelcomFreeMouseCursor();
  TelcomFreeCorners();
  //	TelcomFreeStaticOverlays();
  TelcomFreePowerEffect();
}

#define HIGH_STATIC 50.0
#define NEG_CUT 40.0
#define LOW_LEVEL -20.0
#define HIGH_LEVEL 40.0
//	Renders the screen overlays
void TelcomRenderOverlays(void) {
  static float stat = 0;

  TelcomRenderScanline();
  TelcomRenderDrawHiLites();

  // Display static
  if (Telcom_show_static) {
    stat += (myrand(HIGH_STATIC) - NEG_CUT);
    if (stat > 0) {
      Telcom_static_last_frame = true;
      float amp = stat * Telcom_static_setting / HIGH_STATIC;
      // TCStartStaticSound(amp);
      TelcomDisplayStatic(amp);
    } else {
      if (Telcom_glitch_screen) {
        float amp = myrand(1) - 0.3;
        Telcom_static_last_frame = true;
        // TCStartStaticSound(amp);
        TelcomDisplayStatic(amp);
      } else {
        /*
        if(Telcom_static_last_frame)
                TCEndStaticSound();
                */
        Telcom_static_last_frame = false;
      }
    }

    if (stat > HIGH_STATIC)
      stat = HIGH_LEVEL;
    if (stat < LOW_LEVEL)
      stat = 0;
  }
}

//	Renders the screen hilights
void TelcomRenderDrawHiLites(void) {
  float alphas[4];

  rend_SetAlphaType(AT_SATURATE_TEXTURE_VERTEX);
  rend_SetAlphaValue(120);
  rend_SetLighting(LS_NONE);
  rend_SetColorModel(CM_MONO);
  rend_SetOverlayType(OT_NONE);
  rend_SetFiltering(0);
  rend_SetWrapType(WT_CLAMP);

  alphas[0] = 0.3f;
  alphas[1] = 0.3f;
  alphas[2] = 0;
  alphas[3] = 0;

  for (int monitor = 0; monitor < MAX_MONITOR; monitor++) {
    if ((!TelcomHiLiteCount[monitor]) || (!TelcomHiLites[monitor]))
      continue;

    int curr_x, curr_y, i, w, h;
    int *HiLites;

    curr_x = TelcomHiLiteOffset[monitor].x + Telcom_system.Monitor_coords[monitor].left;
    curr_y = TelcomHiLiteOffset[monitor].y + Telcom_system.Monitor_coords[monitor].top;
    HiLites = TelcomHiLites[monitor];

    for (i = 0; i < TelcomHiLiteCount[monitor]; i++) {
      w = bm_w(HiLites[i], 0);
      h = bm_h(HiLites[i], 0);
      rend_DrawScaledBitmap(curr_x, curr_y, curr_x + w, curr_y + h, HiLites[i], 0, 0, 1, 1, -1, alphas);
      curr_x += w;
    }
  }

  rend_SetFiltering(1);
}

//	Loads the Hilites for a monitor
void TelcomLoadHiLites(const char *filelist[], int monitor, int xoff, int yoff) {
  if (!filelist)
    return;
  ASSERT(monitor >= 0 && monitor < MAX_MONITOR);

  TelcomHiLiteCount[monitor] = 0;
  while (filelist[TelcomHiLiteCount[monitor]])
    TelcomHiLiteCount[monitor]++;

  if (!TelcomHiLiteCount[monitor])
    TelcomHiLites[monitor] = NULL;

  TelcomHiLites[monitor] = (int *)mem_malloc(sizeof(int) * TelcomHiLiteCount[monitor]);
  if (!TelcomHiLites[monitor]) {
    mprintf(0, "Unable to allocate memory for hilights monitor=%d\n", monitor);
    TelcomHiLiteCount[monitor] = 0;
    return;
  }

  int *HiLites;
  HiLites = TelcomHiLites[monitor];
  for (int i = 0; i < TelcomHiLiteCount[monitor]; i++) {
    HiLites[i] = FindTextureName(IGNORE_TABLE(filelist[i]));
    if (HiLites[i] == -1)
      HiLites[i] = BAD_BITMAP_HANDLE;
    else
      HiLites[i] = GetTextureBitmap(HiLites[i], 0);
  }

  TelcomHiLiteOffset[monitor].x = xoff;
  TelcomHiLiteOffset[monitor].y = yoff;
}

//	Frees all the memory allocated for the hilites
void TelcomFreeHiLites(void) {
  int *HiLites;
  for (int monitor = 0; monitor < MAX_MONITOR; monitor++) {
    HiLites = TelcomHiLites[monitor];

    if (HiLites) {
      mem_free(HiLites);
    }
    TelcomHiLiteCount[monitor] = 0;
  }
}

//	Renders the scanline to be drawn
void TelcomRenderScanline(void) {
  if (scanline_handle <= BAD_BITMAP_HANDLE)
    return;

  rend_SetAlphaType(AT_SATURATE_TEXTURE_VERTEX);
  rend_SetAlphaValue(120);
  rend_SetLighting(LS_NONE);
  rend_SetColorModel(CM_MONO);
  rend_SetOverlayType(OT_NONE);
  rend_SetFiltering(0);
  rend_SetWrapType(WT_CLAMP);

  int x, end_x, start_x;
  float alphas[4];
  alphas[0] = 0;
  alphas[1] = 0;
  alphas[2] = 0.05f;
  alphas[3] = 0.05f;

  start_x = Telcom_system.Monitor_coords[MONITOR_MAIN].left;
  end_x = start_x + Telcom_system.Monitor_coords[MONITOR_MAIN].right - Telcom_system.Monitor_coords[MONITOR_MAIN].left;

  float end_time = timer_GetTime();

  while (end_time > scanline_nexttime) {
    for (x = start_x; x < end_x; x += 32)
      rend_DrawScaledBitmap(x, scanliney, x + 32, scanliney + 16, scanline_handle, 0, 0, 1, 1, -1, alphas);
    scanliney++;
    scanline_nexttime += scanline_speed;
  }

  if (scanliney > Telcom_system.Monitor_coords[MONITOR_MAIN].bottom)
    scanliney = Telcom_system.Monitor_coords[MONITOR_MAIN].top - 32;

  rend_SetFiltering(1);
}

//	Creates the scanline
void TelcomCreateScanLine(void) {
  scanliney = Telcom_system.Monitor_coords[MONITOR_MAIN].top - 32;
  scanline_speed = 1.0f / 50.0f;
  scanline_nexttime = timer_GetTime() + scanline_speed;
  scanline_handle = bm_AllocBitmap(32, 32, 0);

  if (scanline_handle <= BAD_BITMAP_HANDLE) {
    return;
  }

  int start_pixel;
  start_pixel = 0;

  uint16_t *data = bm_data(scanline_handle, 0);

  int x, y;
  for (y = 0; y < 32; y++) {
    for (x = 0; x < 32; x++) {
      if (y >= start_pixel)
        data[y * 32 + x] = OPAQUE_FLAG | GR_RGB16(128, 128, 200);
      else
        data[y * 32 + x] = NEW_TRANSPARENT_COLOR;
    }
  }
}

//	Destroys the scanline
void TelcomDestroyScanLine(void) {
  if (scanline_handle <= BAD_BITMAP_HANDLE)
    return;

  bm_FreeBitmap(scanline_handle);
  scanline_handle = -1;
}

//	Loads the mouse cursor
void TelcomLoadMouseCursor(void) {
  TC_cursor = bm_AllocLoadFileBitmap("StdCursor.ogf", 0);
  if (TC_cursor == -1)
    TC_cursor = BAD_BITMAP_HANDLE;
}

//	Renders the mouse cursor
void TelcomRenderMouse(void) {
  rend_SetOverlayType(OT_NONE);
  rend_SetLighting(LS_NONE);
  rend_SetColorModel(CM_MONO);
  rend_SetZBufferState(0);
  rend_SetAlphaType(AT_CONSTANT + AT_TEXTURE);
  rend_SetAlphaValue(255);

  if (TC_cursor > -1) {
    int mx, my;
    mx = Telcom_mouse_x;
    my = Telcom_mouse_y;

    float u0 = 0.0f, v0 = 0.0f, u1 = 1.0f, v1 = 1.0f;
    int cur_w = bm_w(TC_cursor, 0);
    int cur_h = bm_h(TC_cursor, 0);

    if (mx > (Game_window_w - cur_w))
      u1 = ((float)(Game_window_w - mx)) / ((float)cur_w);
    if (my > (Game_window_h - cur_h))
      v1 = ((float)(Game_window_h - my)) / ((float)cur_h);

    rend_DrawScaledBitmap(mx, my, mx + (int)((float)cur_w * u1), my + (int)((float)cur_h * v1), TC_cursor, u0, v0, u1,
                          v1);
  }
  rend_SetZBufferState(1);
}

//	Creates the static bitmap overlays
void TelcomCreateStaticOverlays(void) {
  int i;
  for (i = 0; i < STATIC_BMPS; i++)
    StaticBmps[i] = BAD_BITMAP_HANDLE;

  int j;
  int size;
  int saturation = 10;
  int result;
  float amount;
  uint16_t *data[8];

  amount = ((float)saturation) * 0.4f;

  uint16_t def_color = OPAQUE_FLAG | GR_RGB16(24, 255, 0);

  size = 64 * 64;
  for (i = 0; i < 4; i++) {
    // last 4 bitmaps
    StaticBmps[i + 8] = bm_AllocBitmap(64, 64, 0);
    data[i + 4] = bm_data(StaticBmps[i + 8], 0);

    // middle 4 bitmaps
    StaticBmps[i + 4] = bm_AllocBitmap(64, 64, 0);
    data[i] = bm_data(StaticBmps[i + 4], 0);

    // first 4 bitmaps
    StaticBmps[i] = bm_AllocBitmap(128, 128, 0);
    data[i] = bm_data(StaticBmps[i], 0);
  }

  float t = timer_GetTime();

  for (j = 0; j < size; j++) {
    for (i = 0; i < 4; i++) {

      // last 4 bitmaps
      result = (int)myrand(amount);
      if (!result) {
        if ((int)myrand(5) == 3)
          data[i + 4][j] = def_color;
        else {
          uint8_t grey = (uint8_t)myrand(200) + 55;
          data[i + 4][j] = OPAQUE_FLAG | GR_RGB16(grey, grey, grey);
        }
      } else
        data[i + 4][j] = NEW_TRANSPARENT_COLOR;

      // middle 4 bitmaps
      ps_srand(t * 674338);
      result = (int)myrand(amount);
      if (!result) {
        if ((int)myrand(5) == 3)
          data[i][j] = def_color;
        else {
          uint8_t grey = (uint8_t)myrand(200) + 55;
          data[i][j] = OPAQUE_FLAG | GR_RGB16(grey, grey, grey);
        }
      } else
        data[i][j] = NEW_TRANSPARENT_COLOR;
    }
  }

  // first 4 bitmaps
  size = 128 * 128;
  for (j = 0; j < size; j++) {
    for (i = 0; i < 4; i++) {
      ps_srand((t * 43243 + ps_rand()));
      result = (int)myrand(amount);
      if (!result) {
        if ((int)myrand(5) == 3)
          data[i][j] = def_color;
        else {
          uint8_t grey = (uint8_t)myrand(200) + 55;
          data[i][j] = OPAQUE_FLAG | GR_RGB16(grey, grey, grey);
        }
      } else
        data[i][j] = NEW_TRANSPARENT_COLOR;
    }
  }
}

//	Frees the static bitmap overlays
void TelcomFreeStaticOverlays(void) {
  for (int i = 0; i < STATIC_BMPS; i++)
    if ((StaticBmps[i] != -1) && (StaticBmps[i] != BAD_BITMAP_HANDLE))
      bm_FreeBitmap(StaticBmps[i]);
}

//	Displays static on the screen
void TelcomDisplayStatic(float alpha) {
  int x, y;
  int height = (Telcom_system.Monitor_coords[MONITOR_MAIN].bottom) - (Telcom_system.Monitor_coords[MONITOR_MAIN].top);
  int width = (Telcom_system.Monitor_coords[MONITOR_MAIN].right) - (Telcom_system.Monitor_coords[MONITOR_MAIN].left);
  int type;

  if (alpha < 0)
    alpha = 0;
  if (alpha > 1)
    alpha = 1;

  type = (int)myrand(21);
  if ((type < 7))
    type = 0;
  else if ((type < 14))
    type = 4;
  else
    type = 8;

  int xoff = Telcom_system.Monitor_coords[MONITOR_MAIN].left;
  int yoff = Telcom_system.Monitor_coords[MONITOR_MAIN].top;

  rend_SetAlphaType(AT_CONSTANT_TEXTURE);
  rend_SetAlphaValue(alpha * 255.0);
  rend_SetLighting(LS_NONE);
  rend_SetColorModel(CM_MONO);
  rend_SetOverlayType(OT_NONE);
  rend_SetWrapType(WT_CLAMP);
  rend_SetFiltering(0);

  int dy = ((int)myrand(32)) - 16;

  int h = bm_h(StaticBmps[type], 0);
  int w = bm_w(StaticBmps[type], 0);
  int j = 0;
  for (y = dy; y < height; y += h)
    for (x = 0; x < width; x += w) {
      rend_DrawScaledBitmap(x + xoff, y + yoff, x + w + xoff, y + h + yoff, StaticBmps[type + (j % 4)], 0, 0, 1, 1);
      h = bm_h(StaticBmps[type + (j % 4)], 0);
      w = bm_w(StaticBmps[type + (j % 4)], 0);
      j++;
    }

  rend_SetFiltering(1);
}

//	Frees the mouse cursor
void TelcomFreeMouseCursor(void) {
  // remove the mouse cursor
  if (TC_cursor > BAD_BITMAP_HANDLE) {
    bm_FreeBitmap(TC_cursor);
    TC_cursor = -1;
  }
}

float TC_effect_position;

//	Initializes the bitmaps, etc needed for power up/down effect
void TelcomInitPowerEffect(void) {
  PowerBmps[0] = bm_AllocBitmap(32, 32, 0);
  if (PowerBmps[0] == -1)
    return;

  int i;
  uint16_t *bmpdata = bm_data(PowerBmps[0], 0);
  for (i = 0; i < 32 * 32; i++)
    bmpdata[i] = OPAQUE_FLAG | GR_RGB(0, 0, 0);

  PowerBmps[1] = FindTextureName("TelcomPowerbar");
  if (PowerBmps[1] == -1)
    return;
  PowerBmps[1] = GetTextureBitmap(PowerBmps[1], 0);
  TC_effect_position = 0;
}

//	Frees the bitmaps, etc for power up/down effect
void TelcomFreePowerEffect(void) {
  if ((PowerBmps[0] != -1) && (PowerBmps[0] != BAD_BITMAP_HANDLE))
    bm_FreeBitmap(PowerBmps[0]);
}

#define TCPE_START 0.1f
#define TCPE_STAGE1 0.3f
#define TCPE_STAGE2 0.8f
#define TCPE_END 1.0f

//	Draws a frame of the power up/down effect
void TelcomDoPowerEffect(bool power_down, float frametime) {
  int height = (Telcom_system.Monitor_coords[MONITOR_MAIN].bottom) - (Telcom_system.Monitor_coords[MONITOR_MAIN].top);
  int width = (Telcom_system.Monitor_coords[MONITOR_MAIN].right) - (Telcom_system.Monitor_coords[MONITOR_MAIN].left);
  int xoff = Telcom_system.Monitor_coords[MONITOR_MAIN].left;
  int yoff = Telcom_system.Monitor_coords[MONITOR_MAIN].top;

  if (!power_down && TC_effect_position >= TCPE_STAGE2)
    goto tcpe_adjust;

  // draw the power effect at it's current state
  rend_SetAlphaType(AT_CONSTANT_TEXTURE);
  rend_SetAlphaValue(255);
  rend_SetLighting(LS_NONE);
  rend_SetColorModel(CM_MONO);
  rend_SetOverlayType(OT_NONE);
  rend_SetWrapType(WT_CLAMP);
  rend_SetFiltering(0);
  rend_SetZBufferState(0);

  if (TC_effect_position <= TCPE_STAGE1) {
    // stage 1
    int i, x, y;
    int line_count = (TC_effect_position - TCPE_START) / (TCPE_STAGE1 - TCPE_START) * ((float)((width / 32) + 3));
    if (line_count < 0)
      line_count = 0;

    for (y = 0; y < height; y += 32)
      for (x = 0; x < width; x += 32) {
        rend_DrawScaledBitmap(x + xoff, y + yoff, x + 32 + xoff, y + 32 + yoff, PowerBmps[0], 0, 0, 1, 1);
      }

    if (TC_effect_position < TCPE_START)
      goto tcpe_adjust;

    x = (width / 2) - (16 * line_count) + xoff;
    y = (height / 2) - 16 + yoff;

    for (i = 0; i < line_count; i++) {
      rend_DrawScaledBitmap(x, y, x + 32, y + 32, PowerBmps[1], 0, 0, 1, 1);
      x += 32;
    }
  } else {
    // stage 2
    int x, y, i;
    int gap;

    gap = ((float)height) * (TC_effect_position - TCPE_STAGE1) / (TCPE_STAGE2 - TCPE_STAGE1);
    int hcount = ((((float)height) / 2.0f) - (((float)gap) / 2.0f)) / 32.0f;

    for (i = 0; i < hcount; i++)
      for (x = 0; x < width; x += 32) {
        y = (i << 5);
        if (i == (hcount - 1)) {
          rend_SetAlphaType(AT_SATURATE_TEXTURE);
          rend_DrawScaledBitmap(x + xoff, y + 10 + yoff, x + 32 + xoff, y + 42 + yoff, PowerBmps[1], 0, 0, 1, 1);
          rend_SetAlphaType(AT_CONSTANT_TEXTURE);
        }
        rend_DrawScaledBitmap(x + xoff, y + yoff, x + 32 + xoff, y + 32 + yoff, PowerBmps[0], 0, 0, 1, 1);
      }

    y = height - 32;
    for (i = 0; i < hcount; i++) {
      for (x = 0; x < width; x += 32) {
        if (i == (hcount - 1)) {
          rend_SetAlphaType(AT_SATURATE_TEXTURE);
          rend_DrawScaledBitmap(x + xoff, y - 10 + yoff, x + 32 + xoff, y + 22 + yoff, PowerBmps[1], 0, 0, 1, 1);
          rend_SetAlphaType(AT_CONSTANT_TEXTURE);
        }
        rend_DrawScaledBitmap(x + xoff, y + yoff, x + 32 + xoff, y + 32 + yoff, PowerBmps[0], 0, 0, 1, 1);
      }
      y -= 32;
    }
  }

tcpe_adjust:

  // Now adjust effect
  if (power_down)
    frametime = -frametime;

  frametime = frametime / TCPE_TIME; // scale it to a percentage of total time

  TC_effect_position += frametime;
  if (TC_effect_position < 0)
    TC_effect_position = 0;
  if (TC_effect_position > 1)
    TC_effect_position = 1;

  rend_SetFiltering(1);
  rend_SetZBufferState(1);
}

/***************************************************
 *			TelCom Event Handling
 ***************************************************
 */

//	returns the true if there is a next screen (from the current)
static bool TelComIsThereANextScreen(void);

/*
 *	Initializes the TelCom Event manager system
 *		Call this as soon as possible
 *	You can call it whenever the events need to be flushed
 */
void TelComInitEventManager(void) {
  int i;

  for (i = 0; i < MAX_TELCOM_EVENTS; i++) {
    Telcom_system.Telcom_event_queue[i].id = -1;
  }
  for (i = 0; i < TCSYS_MAXKEYS; i++) {
    Telcom_system.Telcom_systemkey_states[i] = false;
  }

  // Setup the key translation table
  Telcom_system.TranslateSysKey[TCSYS_TAB] = KEY_TAB;
  Telcom_system.TranslateSysKey[TCSYS_UP] = KEY_UP;
  Telcom_system.TranslateSysKey[TCSYS_DOWN] = KEY_DOWN;
  Telcom_system.TranslateSysKey[TCSYS_LEFT] = KEY_LEFT;
  Telcom_system.TranslateSysKey[TCSYS_RIGHT] = KEY_RIGHT;
  Telcom_system.TranslateSysKey[TCSYS_ENTER] = KEY_ENTER;
  Telcom_system.TranslateSysKey[TCSYS_SPACE] = KEY_SPACEBAR;
  Telcom_system.TranslateSysKey[TCSYS_Q] = KEY_Q;
  Telcom_system.TranslateSysKey[TCSYS_F1] = KEY_F1;
  Telcom_system.TranslateSysKey[TCSYS_F2] = KEY_F2;
  Telcom_system.TranslateSysKey[TCSYS_F3] = KEY_F3;
  Telcom_system.TranslateSysKey[TCSYS_PRINTSCRN] = KEY_PRINT_SCREEN;
  Telcom_system.TranslateSysKey[TCSYS_1] = KEY_1;
  Telcom_system.TranslateSysKey[TCSYS_2] = KEY_2;
  Telcom_system.TranslateSysKey[TCSYS_3] = KEY_3;
  Telcom_system.TranslateSysKey[TCSYS_4] = KEY_4;
  Telcom_system.TranslateSysKey[TCSYS_5] = KEY_5;
  Telcom_system.TranslateSysKey[TCSYS_6] = KEY_6;
  Telcom_system.TranslateSysKey[TCSYS_7] = KEY_7;
  Telcom_system.TranslateSysKey[TCSYS_8] = KEY_8;
  Telcom_system.TranslateSysKey[TCSYS_REVERSETAB] = KEY_TAB + KEY_SHIFTED;

  Telcom_system.Telcom_mouse_downtime = 0;
}

/*
 *	Enables/Disables a TelCom system key, pass in TCSYS_MAXKEYS to enable/disable all keys
 *
 */
void TelComEnableSystemKey(int key, bool enable) {
  if (key < 0 || key > TCSYS_MAXKEYS)
    return;

  int bit = 0x01;

  if (key == TCSYS_MAXKEYS) {
    bit = 0xFFFFFFFF;
  } else {
    bit = (bit << key);
  }

  if (enable)
    Telcom_system.TelComSysKeyEnable |= bit;
  else
    Telcom_system.TelComSysKeyEnable &= ~bit;
}

/*
 *	Calling this sends an event message to the TelCom, adding it to it's event queue
 *
 */
void TelComSendEvent(int event_num, int parm1, int parm2) {
  for (int i = 0; i < MAX_TELCOM_EVENTS; i++) {
    if (Telcom_system.Telcom_event_queue[i].id == -1) {
      // add the event here
      Telcom_system.Telcom_event_queue[i].id = event_num;
      Telcom_system.Telcom_event_queue[i].parms[0] = parm1;
      Telcom_system.Telcom_event_queue[i].parms[1] = parm2;
      return;
    }
  }

  mprintf(0, "Warning: TelCom Event Queue Overflow\n");
}

/*
 *	Call this when handling the TelCom system events, returns true if there is an event waiting, it will then fill
 *	in the passed struct.  You should call this repeatedly until a value of false is returned, signaling no more
 *	events in the queue
 */
bool TelComPopEvent(tTCEvent *evt) {
  if (Telcom_system.Telcom_event_queue[0].id != -1) {
    memcpy(evt, &Telcom_system.Telcom_event_queue[0], sizeof(tTCEvent));

    // move all items up in the queue
    for (int i = 1; i < MAX_TELCOM_EVENTS; i++) {
      memcpy(&Telcom_system.Telcom_event_queue[i - 1], &Telcom_system.Telcom_event_queue[i], sizeof(tTCEvent));
    }
    Telcom_system.Telcom_event_queue[MAX_TELCOM_EVENTS - 1].id = -1;
    return true;
  }

  return false;
}

/*
 *	Forces an effect to have focus (if is allowed to have focus)
 *
 */
void TelComSetFocusOnEffect(int efxnum) {
  int screen;
  int effect_with_focus;

  if (TCEffects[efxnum].type == EFX_NONE)
    return;

  screen = TCEffects[efxnum].screen;

  if (TCEffects[efxnum].has_focus)
    return; // already has focus

  if (!TCEffects[efxnum].tab_stop)
    return; // not allowed to have focus

  // find the effect on the screen with focus
  int i = Screen_roots[screen];
  effect_with_focus = -1;

  while (i != -1) {
    if (TCEffects[i].tab_stop && TCEffects[i].has_focus) {
      effect_with_focus = i;
      break;
    }

    i = TCEffects[i].next;
  }

  bool send_click = false;

  if (TCEffects[efxnum].flags & OBF_CHANGEFOCUSISCLICK)
    send_click = true;

  // send out our events and process focus change
  if (i != -1)
    TCEffects[i].has_focus = false;
  TCEffects[efxnum].has_focus = true;

  if (i != -1)
    SendEventToEffect(i, TEVT_LOSTFOCUS);
  SendEventToEffect(efxnum, TEVT_GAINFOCUS);

  if (send_click)
    SendEventToEffect(efxnum, TEVT_MOUSECLICK);
}

/*
 *	This should be called once a frame, it will handle all events in the TelCom system and send off any system
 *	events to the effects/buttons
 */
#define TELCOM_FRAMERATE_CAP 25.0f
void GameFrame(void);
void TelComHandleAllEvents(tTelComInfo *tcs) {
  static float last_frame_time = 0;
  float frame_time;

  volatile float curr_time = timer_GetTime();
  volatile float next_time = last_frame_time + (1 / TELCOM_FRAMERATE_CAP);

  if (curr_time < next_time) {
    Sleep((next_time - curr_time) * 1000.0f);
  }
  if (last_frame_time == 0) {
    frame_time = 0.1f;
  }
  frame_time = curr_time - last_frame_time;
  last_frame_time = curr_time;

  // First handle all events that the TelCom system has waiting
  tTCEvent event;
  while (TelComPopEvent(&event)) {
    // handle the event
    switch (event.id) {
    case -1:
      mprintf(0, "TelCom Error: Trying to process an event of type -1\n");
      Int3(); // Hey!! How'd we pop off a -1!!! Get Jeff
      break;
    case TEVT_TCQUIT: {
      // the user wants to quit out of the TelCom
      tcs->current_status = TS_OFF;
    } break;
    case TEVT_SCREENSHOT: {
      // take a screenshot
      mprintf(0, "Taking Screenshot\n");
      DoScreenshot();
    } break;
    case TEVT_TCNEXT: {
      // the user wants to go to the next screen
      if (TelcomAdvanceScreen() && tcs->current_status == TS_MISSION && !Telcom_called_from_game) {
        // exit out of TelCom
        tcs->state = TCS_POWEROFF;
      }
    } break;
    case TEVT_TCPREV: {
      // the user wants to go to the prev screen
      TelcomBackupScreen();
    } break;
    case TEVT_TCJUMP: {
      int screen = event.parms[0];
      ASSERT(screen >= 0 && screen < MAX_TELCOM_SCREENS);

      // the user wants to jump to a screen
      TelComJumpScreen(screen);
    } break;
    case TEVT_FAKEKEYPRESS: {
      TelComHandleKeyPress(event.parms[0], true, TC_current_screen);
    } break;
    default:
      mprintf(0, "TelCom System Warning: Unhandled event %d\n", event.id);
      break;
    }
  }

  // Now that all the events for the TelCom system have been handled, send off any events that need
  // to be sent to the effects or buttons

  // First check all TelCom system keys
  int screen = TC_current_screen;
  int key;

  if ((KEY_STATE(KEY_LSHIFT) || KEY_STATE(KEY_RSHIFT)) && KEY_STATE(KEY_ESC)) {
    Telcom_exit_to_mainmenu = true;
    Telcom_system.state = TCS_POWEROFF;
  }

  int i;
  bool processed[TCSYS_MAXKEYS];
  for (i = 0; i < TCSYS_MAXKEYS; i++)
    processed[i] = false;

  TelCom_PrepareCustomKeyEvents();

  while ((key = ddio_KeyInKey()) != 0) {
    for (i = 0; i < TCSYS_MAXKEYS; i++) {
      TelCom_ProcessCustomKeyEvent(key);

      if (Telcom_system.TranslateSysKey[i] != key)
        continue;

      if (!Telcom_system.Telcom_systemkey_states[i]) {
        // the key has just been pressed, handle button press
        TelComHandleKeyPress(i, true, screen);
      }

      if (Telcom_system.Telcom_systemkey_states[i]) {
        // the key is being held down, handle button down
        TelComHandleKeyPress(i, false, screen);
      }
      Telcom_system.Telcom_systemkey_states[i] = true;
      processed[i] = true;
    }
  }

  for (i = 0; i < TCSYS_MAXKEYS; i++) {
    if (!processed[i]) {
      Telcom_system.Telcom_systemkey_states[i] = false;
    }
  }

  TelCom_PostProcessCustomKeyEvents();

  // Now check mouse position and button state
  int x, y;
  int buttons;
  int effect_clicktype;
  float frametime;

  if (Control_poll_flag) {
    buttons = Controller->get_mouse_raw_values(&x, &y);
  } else {
    buttons = ddio_MouseGetState(&x, &y, NULL, NULL);
  }

  Telcom_mouse_x = x;
  Telcom_mouse_y = y;

  // check to see if the power button was clicked
  if (!buttons && Telcom_system.Telcom_mouse_downtime > 0 && (x >= HotSpotL(POWER_BUTTON)) &&
      (x <= HotSpotR(POWER_BUTTON)) && (y >= HotSpotT(POWER_BUTTON)) && (y <= HotSpotB(POWER_BUTTON))) {
    Telcom_system.state = TCS_POWEROFF;
  }

  frametime = last_frametime;

  // see if the mouse is over any button
  int efxnum = FindButtonEffectByXY(x, y, screen);

  if (efxnum != -1) {
    // check to see if this is the effect num the mouse was last over, if not, then
    // register it as mouse enter
    if (Telcom_mouse_last_effect != efxnum) {
      SendEventToEffect(efxnum, TEVT_MOUSEENTER);
      Telcom_mouse_last_effect = efxnum;
    }

    // the mouse is over a button
    SendEventToEffect(efxnum, TEVT_MOUSEOVER);

    effect_clicktype = TCEffects[efxnum].buttoninfo.click_type;

    if (buttons) {
      if (effect_clicktype == CLICKTYPE_DOWN) {
        SendEventToEffect(efxnum, TEVT_MOUSEDOWN);
      } else if (Telcom_system.Telcom_mouse_downtime == 0 && effect_clicktype == CLICKTYPE_CLICKDOWN) {
        SendEventToEffect(efxnum, TEVT_MOUSECLICK);
      }
    } else {
      if (Telcom_system.Telcom_mouse_downtime > 0 && effect_clicktype == CLICKTYPE_CLICKUP) {
        // send the mouse up event
        SendEventToEffect(efxnum, TEVT_MOUSEUP);
      }
    }
  } else {
    // the mouse is not over any effect, reset it's efxnum owner (we can do a mouseleave event here)
    Telcom_mouse_last_effect = -1;
  }

  if (buttons) {
    Telcom_system.Telcom_mouse_downtime += frametime;
  } else {
    Telcom_system.Telcom_mouse_downtime = 0;
  }

  // If we are calling the telcom from inside the game, than we have some processing to do
  if (Telcom_called_from_game && (Game_mode & GM_MULTI)) {
    // Process all game frames
    if (!Multi_bail_ui_menu)
      GameFrame();

    // If we are in a multiplayer game and we have been told to bail, than do so!
    if (Multi_bail_ui_menu) {
      tcs->current_status = TS_OFF;
      tcs->state = TCS_POWEROFF;
    }
  }

  // handle music if in game.
  if (Telcom_called_from_game) {
    tMusicSeqInfo music_info;
    music_info.frametime = frame_time;
    music_info.player_dead = false;
    music_info.started_level = false;
    D3MusicDoFrame(&music_info);
  }
}

/*
 *	Given the key that has been pressed, or being held down, it processes the event depending on what key
 *	it is.
 *
 */

extern int AM_terrain, AM_realign, AM_center_on_player, AM_current_marker;
void TelComHandleKeyPress(int key, bool click, int screen_id) {
  int bit = 0x01;
  bit = (bit << key);
  if (!(Telcom_system.TelComSysKeyEnable & bit))
    return;

  switch (key) {
  case TCSYS_REVERSETAB: {
    if (!click)
      break;

    int first = -1, curr_focus = -1;
    int i = Screen_roots[screen_id];

    while (i != -1) {
      if (TCEffects[i].tab_stop) {
        // this is effect is a tab stop
        if (first == -1)
          first = i;
        if (TCEffects[i].has_focus) {
          // this effect is the one with focus
          curr_focus = i;
          break;
        }
      }
      i = TCEffects[i].next;
    }

    if (curr_focus == -1) {
      // none currently have focus!, make the effect we found (if any) have focus
      if (first != -1) {
        SendEventToEffect(first, TEVT_GAINFOCUS);
        TCEffects[first].has_focus = true;
      }
      break; // our work is done here
    }

    bool done = false;
    int end_node = Screen_roots[screen_id];
    int t = end_node;
    if (t == -1) {
      Int3();
      break;
    }

    while (!done) {
      if (TCEffects[t].next == -1) {
        done = true;
        end_node = t;
      } else {
        t = TCEffects[t].next;
      }
    }

    done = false;
    int new_focus = -1;
    while (!done) {
      if (i == -1) {
        // start back at the end of the monitor list
        i = end_node;
      } else
        i = TCEffects[i].prev;

      if (i == curr_focus)
        done = true;
      else {
        if (TCEffects[i].tab_stop) {
          // we found another effect on the screen
          new_focus = i;
          done = true;
        }
      }
    }

    if (new_focus == -1) {
      // there is only 1 button on this screen, no change of focus
      break;
    }
    bool send_click = false;

    if (TCEffects[new_focus].flags & OBF_CHANGEFOCUSISCLICK)
      send_click = true;

    // send out our events and process focus change
    TCEffects[curr_focus].has_focus = false;
    TCEffects[new_focus].has_focus = true;
    SendEventToEffect(new_focus, TEVT_GAINFOCUS);

    if (send_click)
      SendEventToEffect(new_focus, TEVT_MOUSECLICK);
    SendEventToEffect(curr_focus, TEVT_LOSTFOCUS);

  } break;
  case TCSYS_TAB: {
    if (!click)
      break;

    int first = -1, curr_focus = -1;
    int i = Screen_roots[screen_id];

    while (i != -1) {
      if (TCEffects[i].tab_stop) {
        // this is effect is a tab stop
        if (first == -1)
          first = i;
        if (TCEffects[i].has_focus) {
          // this effect is the one with focus
          curr_focus = i;
          break;
        }
      }
      i = TCEffects[i].next;
    }

    if (curr_focus == -1) {
      // none currently have focus!, make the effect we found (if any) have focus
      if (first != -1) {
        SendEventToEffect(first, TEVT_GAINFOCUS);
        TCEffects[first].has_focus = true;
      }
      break; // our work is done here
    }

    bool done = false;
    int new_focus = -1;
    while (!done) {
      if (i == -1) {
        // start back at the beginning of the monitor list
        i = Screen_roots[screen_id];
      } else
        i = TCEffects[i].next;

      if (i == curr_focus)
        done = true;
      else {
        if (TCEffects[i].tab_stop) {
          // we found another effect on the screen
          new_focus = i;
          done = true;
        }
      }
    }

    if (new_focus == -1) {
      // there is only 1 button on this screen, no change of focus
      break;
    }
    bool send_click = false;

    if (TCEffects[new_focus].flags & OBF_CHANGEFOCUSISCLICK)
      send_click = true;

    // send out our events and process focus change
    TCEffects[curr_focus].has_focus = false;
    TCEffects[new_focus].has_focus = true;
    SendEventToEffect(new_focus, TEVT_GAINFOCUS);

    if (send_click)
      SendEventToEffect(new_focus, TEVT_MOUSECLICK);
    SendEventToEffect(curr_focus, TEVT_LOSTFOCUS);
  } break;
  case TCSYS_UP:
  case TCSYS_DOWN: {
    int curr_focus = -1;
    int node = Screen_roots[screen_id];
    while (node != -1) {
      if (TCEffects[node].has_focus) {
        // this guy has focus
        curr_focus = node;
        break;
      }
      node = TCEffects[node].next;
    }

    if (curr_focus == -1) {
      // nothing has focus
      break;
    }

    bool need_to_find_text = false;

    // the up/down arrow keys require either a text box to have focus
    // or an up/down arrow to have focus
    if (TCEffects[curr_focus].type != EFX_BUTTON && TCEffects[curr_focus].type != EFX_TEXT_STATIC &&
        TCEffects[curr_focus].type != EFX_TEXT_TYPE && TCEffects[curr_focus].type != EFX_TEXT_FADE) {
      // we don't have a text box or a button as focus
      need_to_find_text = true;
    }

    if (TCEffects[curr_focus].type == EFX_BUTTON && TCEffects[curr_focus].buttoninfo.button_type != BUTT_UPARROW &&
        TCEffects[curr_focus].buttoninfo.button_type != BUTT_DOWNARROW) {
      // we have a button, but it's not an up/down arrow
      need_to_find_text = true;
    }

    if (need_to_find_text) {
      // we need to hunt through the effect list, find the first text box with a tabstop
      // and use that as the text to scroll
      int found = -1;
      int node = Screen_roots[screen_id];
      while (node != -1) {
        if (TCEffects[node].has_focus) {
          // this guy has focus
          found = node;
          break;
        }
        node = TCEffects[node].next;
      }

      if (found == -1) {
        // we found nothing, we're done
        break;
      }
      curr_focus = found;
    }

    // if the effect to use (curr_focus) is a button, than get it's parent ID, make sure it is a text effect
    if (TCEffects[curr_focus].type == EFX_BUTTON) {
      int parent_id = TCEffects[curr_focus].buttoninfo.parent;
      if (parent_id == -1 ||
          (TCEffects[parent_id].type != EFX_TEXT_STATIC && TCEffects[parent_id].type != EFX_TEXT_TYPE &&
           TCEffects[parent_id].type != EFX_TEXT_FADE)) {
        // there is no parent, or it's not a text effect
        break;
      }

      curr_focus = parent_id;
    }

    // when we get here curr_focus should be pointing to a text effect to scroll
    ASSERT(curr_focus >= 0 && curr_focus < MAX_TCEFFECTS);
    ASSERT(TCEffects[curr_focus].type == EFX_TEXT_STATIC || TCEffects[curr_focus].type == EFX_TEXT_TYPE ||
           TCEffects[curr_focus].type == EFX_TEXT_FADE);
    ASSERT(TCEffects[curr_focus].tab_stop);

    if (key == TCSYS_UP) {
      // scroll up
      SendEventToEffect(curr_focus, TEVT_SCROLLUP);
    } else {
      // scroll down
      SendEventToEffect(curr_focus, TEVT_SCROLLDOWN);
    }
  } break;
  case TCSYS_LEFT: {
    if (!click)
      break;
    TelComSendEvent(TEVT_TCPREV);
  } break;
  case TCSYS_SPACE: {
    if (!click)
      break;
    TelComSendEvent(TEVT_TCNEXT);
  } break;
  case TCSYS_RIGHT: {
    if (!click)
      break;
    // check to see if there is a next page, if there is go to it, else don't
    if (TelComIsThereANextScreen())
      TelComSendEvent(TEVT_TCNEXT);
  } break;
  case TCSYS_ENTER: {
    int curr_focus = -1;
    for (int i = 0; i < MAX_TCEFFECTS; i++) {
      if (TCEffects[i].type == EFX_BUTTON && TCEffects[i].screen == screen_id) {
        // this is a button on the screen
        if (TCEffects[i].has_focus) {
          // this button is the one with focus currently
          curr_focus = i;
          break;
        }
      }
    }
    if (curr_focus == -1)
      break;
    if (TCEffects[curr_focus].buttoninfo.click_type == CLICKTYPE_DOWN) {
      SendEventToEffect(curr_focus, TEVT_MOUSEDOWN);
    } else if (click) {
      SendEventToEffect(curr_focus, TEVT_MOUSECLICK);
    }
  } break;
  case TCSYS_Q: {
    if (!click)
      break;

    TelComSendEvent(TEVT_TCQUIT);
  } break;
  case TCSYS_F1: {
    if (!click)
      break;

    AM_terrain = !AM_terrain;
  } break;
  case TCSYS_F2: {
    if (!click)
      break;

    AM_center_on_player = 1;
  } break;
  case TCSYS_F3: {
    if (!click)
      break;

    AM_realign = 1;
  } break;
  case TCSYS_PRINTSCRN: {
    if (!click)
      break;

    TelComSendEvent(TEVT_SCREENSHOT);

  } break;
  case TCSYS_1:
  case TCSYS_2:
  case TCSYS_3:
  case TCSYS_4:
  case TCSYS_5:
  case TCSYS_6:
  case TCSYS_7:
  case TCSYS_8: {
    int index = key - TCSYS_1;

    if (index < Players[Player_num].num_markers)
      AM_current_marker = index;

    break;
  }
  default:
    mprintf(0, "TelCom Warning: Keypressed not valid\n");
  }
}

/*
 *****************************************************************************
 *				TelCom Screen Control Functions *
 *****************************************************************************
 *
 */

//	Initializes the TelCom Screens so they're ready for input
void InitAllScreens(void) {
  for (int i = 0; i < MAX_TELCOM_SCREENS; i++) {
    Telcom_system.Screen_state[i] = SS_EMPTY;
  }
  TCWorking_screen = -1;
}

//	Advances to the next screen
//	returns true is there is no screen (it's not being made, nor ready)
bool TelcomAdvanceScreen(void) {
  int next_screen = TC_current_screen + 1;
  if (next_screen >= MAX_TELCOM_SCREENS)
    return true;
  switch (Telcom_system.Screen_state[next_screen]) {
  case SS_EMPTY:
    // no screen even being worked on...return true
    return true;
    break;
  case SS_BEING_MADE:
    return false;
    break;
  case SS_READY:
    TelcomRenderSetScreen(TC_current_screen + 1);
    return false;
    break;
  }
  return true;
}

//	returns the true if there is a next screen (from the current)
bool TelComIsThereANextScreen(void) {
  int next_screen = TC_current_screen + 1;
  if (next_screen >= MAX_TELCOM_SCREENS)
    return false;
  switch (Telcom_system.Screen_state[next_screen]) {
  case SS_EMPTY:
    // no screen even being worked on...return true
    return false;
    break;
  case SS_READY:
  case SS_BEING_MADE:
    return true;
    break;
  }
  return false;
}

//	Backs up a screen
//	returns true is there is no screen (it's not being made, nor ready)
bool TelcomBackupScreen(void) {
  int next_screen = TC_current_screen - 1;
  if (next_screen < 0)
    return true;
  switch (Telcom_system.Screen_state[next_screen]) {
  case SS_EMPTY:
    // no screen even being worked on...return true
    return true;
    break;
  case SS_BEING_MADE:
    return false;
    break;
  case SS_READY:
    TelcomRenderSetScreen(TC_current_screen - 1);
    return false;
    break;
  }
  return true;
}

bool TelComJumpScreen(int screen) {
  if (screen < 0 || screen >= MAX_TELCOM_SCREENS)
    return true;
  switch (Telcom_system.Screen_state[screen]) {
  case SS_EMPTY:
    // no screen even being worked on...return true
    return true;
    break;
  case SS_BEING_MADE:
    return false;
    break;
  case SS_READY:
    TelcomRenderSetScreen(screen);
    return false;
    break;
  }

  return true;
}

//	Destroys and clears all screens of the TelCom
void DestroyAllScreens(bool remove_dummy) {
  int end = (remove_dummy) ? MAX_TELCOM_SCREENS : DUMMY_SCREEN;

  for (int i = 0; i < end; i++) {
    if (Telcom_system.Screen_state[i] != SS_EMPTY) {
      Telcom_system.Screen_state[i] = SS_EMPTY;
      EfxDestroyScreen(i);
    }
  }
  TCWorking_screen = -1;
}

//	Starts a TelCom screen so it can be created
void TelcomStartScreen(int screen) {
  ASSERT(screen >= 0 && screen < MAX_TELCOM_SCREENS);
  ASSERT(TCWorking_screen == -1);

  if (Telcom_system.Screen_state[screen] != SS_EMPTY) {
    EfxDestroyScreen(screen);
  }

  Telcom_system.Screen_state[screen] = SS_BEING_MADE;
  TCWorking_screen = screen;
}

//	Ends a TelCom screen.  Calling this enables the screen to be displayed
void TelcomEndScreen(void) {
  ASSERT(TCWorking_screen != -1);

  Telcom_system.Screen_state[TCWorking_screen] = SS_READY;
  TCWorking_screen = -1;
}

float myrand(float max) { return (max * (((float)ps_rand()) / ((float)D3_RAND_MAX))); }

/////////////////////////////////////////////////////////////////////////////
//	These are the functions used for serialization, yes they are out of place,
//	But that is to keep them away from other parts of the code that has
//	the rest of the serialization.  These probably can be moved to some other
//	file....if this function returns:
//	1 : than it's a serialized exe, num will be given the serial num
//	0 : than it isn't a serialized exe
//	-1 : detected a hacked exe
#define INTERNAL_SERIALNUM_TAG "XFCABBFFAX"
char GetInternalSerializationNumber(int *num) {
  static char mydata[] = INTERNAL_SERIALNUM_TAG;

  // first check to see if the value is the same (non-serialized EXE)
  if (mydata[0] == 'X' && ((mydata[9] + 2) == 'Z')) {
    int value = 0;
    char c;
    for (int i = 0; i < 8; i++) {
      c = mydata[i + 1];
      if (c >= 'A' && c <= 'F') {
        value = value * 16 + (c - 'A' + 10);
      } else
        goto get_num;
    }

    if (value == 0xFCABBFFA)
      return 0;
  }

get_num:
  // we got to get the serial num if we can
  int value = 0;
  char c;
  for (int i = 0; i < 8; i++) {
    c = mydata[i + 1];
    if (c >= '0' && c <= '9') {
      value = value * 16 + c - '0';
    } else if (c >= 'A' && c <= 'F') {
      value = value * 16 + c - 'A' + 10;
    } else
      return -1;
  }

  // now byte swap the value to get it to it's original value
  value = (((value & 0xFF000000) >> 24) | ((value & 0xFF0000) >> 8) | ((value & 0xFF) << 24) | ((value & 0xFF00) << 8));

  *num = value;
  return 1;
}

/*
 ****************************************************************
 *				TelCom Sound Functions							*
 ****************************************************************
 *
 */

struct TCSound {
  int hlhandle, handle;
};

TCSound TelcomSounds[TCSND_SOUNDCOUNT];

const char *TCSoundFiles[] = {"Briefstartup1", "BriefStatic",  "Briefmonitoroff1", "Briefingrunning",
                        "Briefbulb1",    "Briefingtype", "Menu Slider Click"};

/*
$$TABLE_SOUND "Briefstartup1"
$$TABLE_SOUND "BriefStatic"
$$TABLE_SOUND "Briefmonitoroff1"
$$TABLE_SOUND "Briefingrunning"
$$TABLE_SOUND "Briefbulb1"
$$TABLE_SOUND "Briefingtype"
$$TABLE_SOUND "Menu Slider Click"
*/

//	Initalizes the Telcom sound sytem
void TelcomInitSounds(void) {
  for (int i = 0; i < TCSND_SOUNDCOUNT; i++) {
    TelcomSounds[i].hlhandle = -1;
    TelcomSounds[i].handle = FindSoundName(IGNORE_TABLE(TCSoundFiles[i]));
  }
}

//	Closes down the Telcom sound system
void TelcomCloseSounds(void) {
  Sound_system.BeginSoundFrame(Telcom_called_from_game);
  for (int i = 0; i < TCSND_SOUNDCOUNT; i++) {
    if (TelcomSounds[i].hlhandle != -1) {
      Sound_system.StopSoundImmediate(TelcomSounds[i].hlhandle);
    }
  }
  Sound_system.EndSoundFrame();
}

//	Starts a sound playing (if it isn't already)
void TelcomStartSound(int sid) {
  ASSERT(sid >= 0 && sid < TCSND_SOUNDCOUNT);

  // make sure the handle is there
  if (TelcomSounds[sid].handle == -1) {
    mprintf(0, "TelCom Sound Warning: '%s' hasn't been loaded yet, trying to load\n", TCSoundFiles[sid]);
    TelcomSounds[sid].handle = FindSoundName(IGNORE_TABLE(TCSoundFiles[sid]));

    if (TelcomSounds[sid].handle == -1) {
      mprintf(0, "TelCom Sound Warning: 2nd try failed, bailing\n");
      return;
    }
  }

  // see if the sound is already playing
  if (TelcomSounds[sid].hlhandle != -1) {
    if (Sound_system.IsSoundPlaying(TelcomSounds[sid].hlhandle)) {
      // the sound is still playing, we don't need to play again
      return;
    }
  }

  TelcomSounds[sid].hlhandle = Sound_system.Play2dSound(TelcomSounds[sid].handle, MAX_GAME_VOLUME);
}

//	Stops a sound playing
void TelcomStopSound(int sid) {
  ASSERT(sid >= 0 && sid < TCSND_SOUNDCOUNT);

  // see if the sound is already playing
  if (TelcomSounds[sid].hlhandle != -1) {
    Sound_system.StopSoundLooping(TelcomSounds[sid].hlhandle);
  }
  TelcomSounds[sid].hlhandle = -1;
}

//------------------------------------------------------------------------------
// Pages a texture into memory, optionally resizing it if in low mem mode
void PageInTexture(int n, bool resize);

//	Pages in all the necessary bitmaps, textures & sounds for the TelCom so that they are in memory
void TelcomPageAllIn(void) {
  extern void UpdateInitMessage(float amount); // amount is 0 to 1
  const float TELCOM_SOUND_PORTION = 0.3f, TELCOM_BITMAP_PORTION = 0.3f, TELCOM_TEXTUREHI_PORTION = 0.2f,
              TELCOM_TEXTURELO_PORTION = 0.2f;

  int i;
  int count;
  float amount_loaded = 0.0f;

  // Page in all sounds
  for (i = 0; i < TCSND_SOUNDCOUNT; i++) {
    int id = FindSoundName(IGNORE_TABLE(TCSoundFiles[i]));
    if (id != -1) {
      Sound_system.CheckAndForceSoundDataAlloc(id);
      amount_loaded += (1.0f * TELCOM_SOUND_PORTION) / (float)TCSND_SOUNDCOUNT;
      if ((i % 4) == 0) {
        UpdateInitMessage(amount_loaded);
      }
    }
  }

  // Page in all bitmaps
  count = Telcom_bitmap.w * Telcom_bitmap.h;
  for (i = 0; i < count; i++) {
    bm_data(Telcom_bitmap.bm_array[i], 0);
    UpdateInitMessage(amount_loaded);
  }
  amount_loaded += TELCOM_BITMAP_PORTION;

  // Page in all textures
  count = 0;
  while (hilites[count]) {
    i = FindTextureName(IGNORE_TABLE(hilites[count]));
    if (i != -1) {
      PageInTexture(i, false);
    }
    count++;
  }
  amount_loaded += TELCOM_TEXTURELO_PORTION;
  UpdateInitMessage(amount_loaded);

  count = 0;
  while (smhilites[count]) {
    i = FindTextureName(IGNORE_TABLE(smhilites[count]));
    if (i != -1)
      PageInTexture(i, false);
    count++;
  }

  i = FindTextureName("TelcomPowerbar");
  if (i != -1)
    PageInTexture(i, false);

  amount_loaded += TELCOM_TEXTURELO_PORTION;
  UpdateInitMessage(amount_loaded);
}

/*
****************************************************************************************
                Single Player Ship Selection
****************************************************************************************
*/
void TCSSSCallback(void);
// collects information about the ships, returns the number of ships available
int TCSSCollectInfo(void);
void TCSSButtonCallback(int efxnum);
void TCSSPutButtonsOnScreen(void);
int TCSSGetSelectedShipIndex(void);

struct {
  int ShipCount;
  int CurrentSelectID;
  matrix orient;
  int ship_model;
  float cam_dist;
} TCShipSelect;

struct tShipInfo {
  int max_speed;
  int maneuverability;
  int shield;
  int ordnance;
  int wingspan;
  int length;
  int height;
  int weight;
};

#define MAX_NUM_SHIPS 3

tShipInfo TCSSInfo[MAX_NUM_SHIPS] = {{TXI_SS_PY_SPEED, TXI_SS_PY_MANEUVERABILITY, TXI_SS_PY_SHIELDS, TXI_SS_PY_ORDANCE,
                                      TXI_SS_PY_WINGSPAN, TXI_SS_PY_LENGTH, TXI_SS_PY_HEIGHT, TXI_SS_PY_WEIGHT},
                                     {TXI_SS_PH_SPEED, TXI_SS_PH_MANEUVERABILITY, TXI_SS_PH_SHIELDS, TXI_SS_PH_ORDANCE,
                                      TXI_SS_PH_WINGSPAN, TXI_SS_PH_LENGTH, TXI_SS_PH_HEIGHT, TXI_SS_PH_WEIGHT},
                                     {TXI_SS_M_SPEED, TXI_SS_M_MANEUVERABILITY, TXI_SS_M_SHIELDS, TXI_SS_M_ORDANCE,
                                      TXI_SS_M_WINGSPAN, TXI_SS_M_LENGTH, TXI_SS_M_HEIGHT, TXI_SS_M_WEIGHT}};

/*
$$TABLE_SHIP "Pyro-GL"
$$TABLE_SHIP "Phoenix"
$$TABLE_SHIP "Magnum-AHT"
*/
struct tSSShipInfo {
  bool found;
  int ship_index;
  int efxnum;
};
tSSShipInfo SSShips[MAX_NUM_SHIPS];

// two buttons
#define SSA_LEFTX 165
#define SSA_TOPY 360
#define SSA_GAP -2

// three buttons
#define SSB_LEFTX 165
#define SSB_TOPY 360
#define SSB_GAP -2

// This is the function called by TelCom to choose a ship
void TelComSingleShipSelect(tTelComInfo *tcs) {
  int found_ships = TCSSCollectInfo();
  if (found_ships < 2 || found_ships > 3) {
    // not supported
    mprintf(0, "Skipping Single Player Ship Selecting, %d ships found\n", found_ships);

    int ship_index_to_use = 0;
    int bit = 0x01;
    bool found = true;

    for (ship_index_to_use = 0; ship_index_to_use < MAX_SHIPS; ship_index_to_use++) {
      if (Players[Player_num].ship_permissions & bit) {
        found = true;
        break;
      }
      bit = bit << 1;
    }

    if (!found) {
      bit = 0x01;
      for (ship_index_to_use = 0; ship_index_to_use < MAX_SHIPS; ship_index_to_use++) {
        if (Default_ship_permission & bit) {
          found = true;
          break;
        }
        bit = bit << 1;
      }
    }

    Players[Player_num].ship_index = ship_index_to_use;
    return;
  }

  bool done = false;

  TCShipSelect.CurrentSelectID = -1;
  TCShipSelect.ship_model = -1;
  vm_MakeIdentity(&TCShipSelect.orient);

  TelcomStartScreen(0);

  // setup general background, plain color
  TCBKGDESC backg;
  backg.color = BACKGROUND_COLOR;
  backg.caps = TCBGD_COLOR;
  backg.type = TC_BACK_STATIC;

  TCBMPDESC bmpdesc;
  bmpdesc.type = TC_BMP_STATIC;
  bmpdesc.flags = 0;
  bmpdesc.caps = TCBD_XY;
  bmpdesc.x = 0;
  bmpdesc.y = 0;
  strcpy(bmpdesc.filename, "SS Background.ogf");
  /*
  $$TABLE_GAMEFILE "SS Background.ogf"
  */

  // setup text for the top monitor "Select Ship"
  TCTEXTDESC textdesc;
  textdesc.type = TC_TEXT_STATIC;
  textdesc.font = BBRIEF_FONT_INDEX;
  textdesc.caps = TCTD_TEXTBOX | TCTD_COLOR | TCTD_FONT;
  textdesc.textbox.left = 5;
  textdesc.textbox.right = 380;
  textdesc.textbox.top = 33;
  textdesc.textbox.bottom = 68;
  textdesc.color = GR_RGB(255, 255, 255);

  // Setup Main Monitor
  CreateBitmapEffect(&bmpdesc, MONITOR_MAIN, 0);
  CreateTextEffect(&textdesc, TXT_SELECTSHIP, MONITOR_MAIN, 0);

  // Create buttons to select ship (either 2 or 3)
  TCSSPutButtonsOnScreen();

  // Setup Location Monitor (small window at top)
  textdesc.textbox.left = 65;
  textdesc.textbox.right = 380;
  textdesc.textbox.top = 5;
  textdesc.textbox.bottom = 50;
  CreateBackgroundEffect(&backg, MONITOR_TOP, 0);
  CreateTextEffect(&textdesc, TXT_SELECTSHIP, MONITOR_TOP, 0);

  TelcomEndScreen();
  TelcomRenderSetScreen(0);
  TelcomRenderSetCallback(TCSSSCallback);

  Telcom_system.state = TCS_POWERON; // turn back on telcom
  tcs->current_status = TS_SHIPSELECT;

  // set focus to the ship we currently have selected
  int focus_ship = -1;
  for (int j = 0; j < MAX_NUM_SHIPS; j++) {
    if (SSShips[j].found && SSShips[j].ship_index == Players[Player_num].ship_index) {
      mprintf(0, "Current Ship: %s\n", Ships[SSShips[j].ship_index].name);
      focus_ship = SSShips[j].efxnum;
      break;
    }
  }

  if (focus_ship != -1) {
    if (TCEffects[focus_ship].has_focus)
      TCSSButtonCallback(focus_ship);
    else
      TelComSetFocusOnEffect(focus_ship);
  }

  TelCom_ClearCustomKeyEvents();
  TelCom_AddCustomKeyEvent(KEY_LEFT, 0x13);  // left arrow
  TelCom_AddCustomKeyEvent(KEY_RIGHT, 0x14); // right arrow
  TelCom_AddCustomKeyEvent(KEY_ENTER, 0x15); // enter key

  while (!done) {
    Sound_system.BeginSoundFrame(Telcom_called_from_game);

    if (Telcom_system.state != TCS_POWERON || tcs->current_status != TS_SHIPSELECT) {
      // we're done with the loop
      done = true;
    }

    // Process all waiting events for the TelCom	(we may only want to handle this once a frame!)
    TelComHandleAllEvents(tcs);

    // Process custom events
    tTCEvent evt;
    while (TelCom_PopSystemEvent(&evt)) {
      switch (evt.id) {
      case 0x13: // left arrow
        TelComSendEvent(TEVT_FAKEKEYPRESS, TCSYS_REVERSETAB);
        break;
      case 0x14: // right arrow
        TelComSendEvent(TEVT_FAKEKEYPRESS, TCSYS_TAB);
        break;
      case 0x15: // enter key
        tcs->state = TCS_POWEROFF;
        break;
      }
    }

    TelcomRenderScreen();
    Descent->defer();
    if (KEY_STATE(KEY_ESC))
      tcs->state = TCS_POWEROFF;

    Sound_system.EndSoundFrame();
  }

  Telcom_system.state = TCS_POWEROFF; // turn back off telcom

  DestroyAllScreens();
  TelcomRenderSetScreen(DUMMY_SCREEN);
  TelcomRenderSetCallback(NULL);

  int ship_index_to_use = TCSSGetSelectedShipIndex();
  mprintf(0, "Selected: %s\n", Ships[ship_index_to_use].name);
  Players[Player_num].ship_index = ship_index_to_use;

  TelCom_ClearCustomKeyEvents();
}

// returns the ship index that is selected
int TCSSGetSelectedShipIndex(void) {
  int id = SSShips[SHIP_PYRO_ID].ship_index;
  for (int i = 0; i < MAX_NUM_SHIPS; i++) {
    if (SSShips[i].found) {
      int efxnum = SSShips[i].efxnum;
      if (TCEffects[efxnum].has_focus) {
        id = SSShips[i].ship_index;
        break;
      }
    }
  }

  return id;
}

// collects information about the ships, returns the number of ships available
int TCSSCollectInfo(void) {
  int found = 0;
  int i, j;

  for (i = 0; i < MAX_NUM_SHIPS; i++) {
    SSShips[i].found = false;
  }

  for (i = 0; i < MAX_SHIPS; i++) {
#ifdef _DEBUG
    if (Ships[i].used) {
#else
    if (Ships[i].used && PlayerIsShipAllowed(Player_num, i)) {
#endif
      for (j = 0; j < MAX_NUM_SHIPS; j++) {
        if (!stricmp(Ships[i].name, AllowedShips[j])) {
          // found the ship
          SSShips[j].found = true;
          SSShips[j].ship_index = i;
          found++;
          break;
        }
      }
    }
  }

  mprintf(0, "Collecting Ship Info: %d ships available\n", found);
  TCShipSelect.ShipCount = found;

  return found;
}

//====================================
// returns the optimal distance to place the camera
float getdist(angle ang, float height); // in pilot.cpp
extern float Render_zoom;

//====================================

void TCSSButtonCallback(int efxnum) {
  if (!TCEffects[efxnum].has_focus) {
    // make sure we have focus...be careful, because by setting focus
    // the call is going to come back into this function
    TelComSetFocusOnEffect(efxnum);
    return;
  }

  int selected_id = -1;

  // which ship id are we talking about?
  for (int i = 0; i < MAX_NUM_SHIPS; i++) {
    if (SSShips[i].found && SSShips[i].efxnum == efxnum) {
      // this is the id;
      selected_id = i;
      break;
    }
  }

  if (selected_id == -1) {
    mprintf(0, "Invalid selected id for efxnum %d\n", efxnum);
    return;
  }

  bool first_click = false;

  if (TCShipSelect.CurrentSelectID == -1)
    first_click = true;

  if (TCShipSelect.CurrentSelectID == selected_id) {
    // not a change
    return;
  }

  TCShipSelect.CurrentSelectID = selected_id;

  // PUT CODE TO HANDLE NEW SHIP BEING SELECTED HERE
  float size;
  TCShipSelect.ship_model = Ships[SSShips[selected_id].ship_index].model_handle;
  if (TCShipSelect.ship_model == -1) {
    mprintf(0, "ship_model is -1\n");
    Int3();
  }

  PageInPolymodel(TCShipSelect.ship_model, OBJ_PLAYER, &size);
  poly_model *pm = GetPolymodelPointer(TCShipSelect.ship_model);
  TCShipSelect.cam_dist = pm->anim_size / Render_zoom + 6;

  TelcomStopSound(TCSND_CLICK);
  if (!first_click)
    TelcomStartSound(TCSND_CLICK);
}

void TCSSSCallback(void) {
  if (TCShipSelect.ship_model == -1) {
    // no ship selected yet
    return;
  }

  vector viewer_eye = {0, 0, 0};
  matrix viewer_orient = IDENTITY_MATRIX;
  viewer_eye.z = -TCShipSelect.cam_dist;

  grtext_Flush();
  StartFrame(325, 142, 535, 280);
  g3_StartFrame(&viewer_eye, &viewer_orient, D3_DEFAULT_ZOOM);
  rend_SetFlatColor(0);

  float normalized_time[MAX_SUBOBJECTS];
  float light_scalar, size;
  PageInPolymodel(TCShipSelect.ship_model, OBJ_PLAYER, &size);
  poly_model *pm = GetPolymodelPointer(TCShipSelect.ship_model);
  vector view_pos;
  vector light_vec;
  matrix view_orient = IDENTITY_MATRIX;
  matrix final_mat = IDENTITY_MATRIX;
  matrix rot_mat;

  //	draw model.
  SetNormalizedTimeAnim(0, normalized_time, pm);

  view_pos = pm->anim_size_offset;

  // move 30 degrees a sec
  vm_AnglesToMatrix(&rot_mat, 0, (last_frametime) * (65535 / 360) * 30, 0);

  vm_MatrixMul(&view_orient, &rot_mat, &TCShipSelect.orient);
  vm_Orthogonalize(&view_orient);
  TCShipSelect.orient = view_orient;

  light_vec.x = 0.0f;
  light_vec.y = -1.0f;
  light_vec.z = -1.0f;
  light_scalar = 0.8f;
  vm_NormalizeVector(&light_vec);

  rend_SetZBufferState(1);
  rend_SetAlphaType(AT_CONSTANT_TEXTURE);
  rend_SetAlphaValue(255);
  rend_SetLighting(LS_NONE);
  rend_SetColorModel(CM_MONO);
  rend_SetOverlayType(OT_NONE);

  DrawPolygonModel(&view_pos, &view_orient, TCShipSelect.ship_model, normalized_time, 0, &light_vec, light_scalar,
                   light_scalar, light_scalar);

  g3_EndFrame();
  EndFrame();

  // Render the name of the selected ship
  uint8_t old_alpha = grtext_GetAlpha();
  int old_font = grtext_GetFont();
  ddgr_color old_color = grtext_GetColor();
  grtext_SetAlpha(255);
  grtext_SetFont(BIG_BRIEFING_FONT);
  grtext_SetColor(GR_WHITE);

  char *name = Ships[SSShips[TCShipSelect.CurrentSelectID].ship_index].name;
  int line_length = grtext_GetTextLineWidth(name);
  int line_height = grfont_GetHeight(BIG_BRIEFING_FONT);
  int bar_width = 177;
  int bar_height = 34;
  int bar_x = 287 + Telcom_system.Monitor_coords[MONITOR_MAIN].left;
  int bar_y = 246 + Telcom_system.Monitor_coords[MONITOR_MAIN].top;

  int x, y;
  x = bar_x + ((bar_width / 2) - (line_length / 2));
  y = bar_y + ((bar_height / 2) - (line_height / 2));

  grtext_Printf(x, y, name);

  // write ship descriptions
  tShipInfo *si = &TCSSInfo[TCShipSelect.CurrentSelectID];
  x = 115;
  y = 130;
  int width = 210;
  int max_height = y + 150;
  grtext_SetFont(BRIEFING_FONT);
  int height = grfont_GetHeight(BRIEFING_FONT);
  const char *line_text;
  char buffy[512];
  char linebuffer[512];

  for (int q = 0; q < 8; q++) {
    switch (q) {
    case 0:
      line_text = TXT(si->max_speed);
      break;
    case 1:
      line_text = TXT(si->maneuverability);
      break;
    case 2:
      line_text = TXT(si->shield);
      break;
    case 3:
      line_text = TXT(si->ordnance);
      break;
    case 4:
      line_text = TXT(si->wingspan);
      break;
    case 5:
      line_text = TXT(si->length);
      break;
    case 6:
      line_text = TXT(si->height);
      break;
    case 7:
      line_text = TXT(si->weight);
      break;
    }

    textaux_WordWrap(line_text, buffy, width, BRIEFING_FONT);

    line_text = textaux_CopyTextLine(buffy, linebuffer);
    while ((line_text) && ((y + height) < max_height)) {
      grtext_Printf(x, y, linebuffer);
      y += height;
      line_text = textaux_CopyTextLine(line_text, linebuffer);
    }
    grtext_Printf(x, y, linebuffer);
    y += height;
  }

  grtext_SetAlpha(old_alpha);
  grtext_SetFont(old_font);
  grtext_SetColor(old_color);
  grtext_Flush();
}

void TCSSPutButtonsOnScreen(void) {
  int monitor_y, monitor_x;
  monitor_y = Telcom_system.Monitor_coords[MONITOR_MAIN].top;
  monitor_x = Telcom_system.Monitor_coords[MONITOR_MAIN].left;

  TCBMPDESC bmpdesc;
  bmpdesc.type = TC_BMP_STATIC;
  bmpdesc.flags = 0;
  bmpdesc.caps = TCBD_XY;

  TCBUTTONDESC buttdesc;
  buttdesc.sibling_id = buttdesc.parent_id = -1;
  buttdesc.internal = TCSSButtonCallback;
  buttdesc.flash_time = 0;
  buttdesc.button_type = BUTT_INTERNAL;
  buttdesc.flasher = false;
  buttdesc.click_type = CLICKTYPE_CLICKUP;
  buttdesc.osflags = OBF_GLOW | OBF_CHANGEFOCUSISCLICK;
  buttdesc.tab_stop = true; // all main menu buttons can have focus

  int left_x, top_y, gap;
  if (TCShipSelect.ShipCount == 2) {
    left_x = SSA_LEFTX;
    top_y = SSA_TOPY;
    gap = SSA_GAP;

    bmpdesc.x = left_x - monitor_x;
    bmpdesc.y = top_y - monitor_y;
    strcpy(bmpdesc.filename, "SS 2 button group.ogf");
  } else {
    left_x = SSB_LEFTX;
    top_y = SSB_TOPY;
    gap = SSB_GAP;

    bmpdesc.x = left_x - monitor_x;
    bmpdesc.y = top_y - monitor_y;
    strcpy(bmpdesc.filename, "SS 3 button group.ogf");
  }
  /*
  $$TABLE_GAMEFILE "SS 3 button group.ogf"
  $$TABLE_GAMEFILE "SS 2 button group.ogf"
  */
  CreateBitmapEffect(&bmpdesc, MONITOR_MAIN, 0);

  int i;
  int width;
  int curr_x, curr_y;
  curr_x = left_x + 3;
  curr_y = top_y + 2;
  const char *lit_name, *name;

  for (i = 0; i < MAX_NUM_SHIPS; i++) {
    if (SSShips[i].found) {
      buttdesc.x = curr_x;
      buttdesc.y = curr_y;

      switch (i) {
      case SHIP_PYRO_ID:
        lit_name = "SS Lit Pyro button.ogf";
        name = "SS Pyro button.ogf";
        break;
      case SHIP_MAGNUM_ID:
        lit_name = "SS Lit Magnum button.ogf";
        name = "SS Magnum button.ogf";
        break;
      case SHIP_PHOENIX_ID:
        lit_name = "SS Lit Phoenix button.ogf";
        name = "SS Phoenix button.ogf";
        break;
      }

      /*
      $$TABLE_GAMEFILE "SS Lit Pyro button.ogf"
      $$TABLE_GAMEFILE "SS Pyro button.ogf"
      $$TABLE_GAMEFILE "SS Lit Magnum button.ogf"
      $$TABLE_GAMEFILE "SS Magnum button.ogf"
      $$TABLE_GAMEFILE "SS Lit Phoenix button.ogf"
      $$TABLE_GAMEFILE "SS Phoenix button.ogf"
      */

      int bmp_handle = bm_AllocLoadFileBitmap(IGNORE_TABLE(name), 0);
      if (bmp_handle <= BAD_BITMAP_HANDLE) {
        width = 10;
      } else {
        width = bm_w(bmp_handle, 0);
        bm_FreeBitmap(bmp_handle);
      }

      strcpy(buttdesc.filename, name);
      strcpy(buttdesc.flash_filename, name);
      strcpy(buttdesc.filename_focus, lit_name);
      strcpy(buttdesc.flash_filename_focus, lit_name);
      SSShips[i].efxnum = CreateButtonEffect(&buttdesc, MONITOR_MAIN, 0);

      curr_x += (width + gap);
    }
  }
}

/////////////////////////////////////////
tTCEvent Telcom_system_queue[MAX_TELCOM_EVENTS]; // Event queue for TelCom System

void TelCom_ClearSystemQueue(void) {
  for (int i = 0; i < MAX_TELCOM_EVENTS; i++) {
    Telcom_system_queue[i].id = -1;
  }
}

/*
 *	Calling this sends an event message to the TelCom System Queue, adding it to it's event queue
 *
 */
void TelCom_SendSystemEvent(int event_num, int parm1, int parm2) {
  for (int i = 0; i < MAX_TELCOM_EVENTS; i++) {
    if (Telcom_system_queue[i].id == -1) {
      // add the event here
      Telcom_system_queue[i].id = event_num;
      Telcom_system_queue[i].parms[0] = parm1;
      Telcom_system_queue[i].parms[1] = parm2;
      return;
    }
  }

  mprintf(0, "Warning: TelCom System Event Queue Overflow\n");
}

/*
 *	Call this when handling the TelCom system events, returns true if there is an event waiting, it will then fill
 *	in the passed struct.  You should call this repeatedly until a value of false is returned, signaling no more
 *	events in the queue
 */
bool TelCom_PopSystemEvent(tTCEvent *evt) {
  if (Telcom_system_queue[0].id != -1) {
    memcpy(evt, &Telcom_system_queue[0], sizeof(tTCEvent));

    // move all items up in the queue
    for (int i = 1; i < MAX_TELCOM_EVENTS; i++) {
      memcpy(&Telcom_system_queue[i - 1], &Telcom_system_queue[i], sizeof(tTCEvent));
    }
    Telcom_system_queue[MAX_TELCOM_EVENTS - 1].id = -1;
    return true;
  }

  return false;
}

struct tCustomKeyEventID {
  int downcount;
  int key_id;
  int event_id;
  tCustomKeyEventID *next;
};
tCustomKeyEventID *Telcom_custom_key_event_root = NULL;

/*
        Removes any custom key event translation masks
*/
void TelCom_ClearCustomKeyEvents(void) {
  tCustomKeyEventID *next, *curr = Telcom_custom_key_event_root;

  while (curr) {
    next = curr->next;

    mem_free(curr);
    curr = next;
  }
  Telcom_custom_key_event_root = NULL;
}

/*
        Adds a custom key event translation mask
*/
void TelCom_AddCustomKeyEvent(int key_id, int event_id) {
  tCustomKeyEventID *curr = Telcom_custom_key_event_root;

  if (!curr) {
    curr = Telcom_custom_key_event_root = (tCustomKeyEventID *)mem_malloc(sizeof(tCustomKeyEventID));
  } else {
    while (curr->next) {
      curr = curr->next;
    }
    curr->next = (tCustomKeyEventID *)mem_malloc(sizeof(tCustomKeyEventID));
    curr = curr->next;
  }

  curr->next = NULL;
  curr->event_id = event_id;
  curr->key_id = key_id;
}

/*
        Prepares to handle custom keys
*/
void TelCom_PrepareCustomKeyEvents(void) {
  tCustomKeyEventID *curr = Telcom_custom_key_event_root;

  while (curr) {
    curr->downcount = 0;
    curr = curr->next;
  }
}

/*
        Post process custom keys
*/
void TelCom_PostProcessCustomKeyEvents(void) {
  tCustomKeyEventID *curr = Telcom_custom_key_event_root;

  while (curr) {
    if (curr->downcount) {
      TelCom_SendSystemEvent(curr->event_id);
      return;
    }

    curr = curr->next;
  }
}

/*
        Handles a possible custom key event
*/
void TelCom_ProcessCustomKeyEvent(int key_id) {
  tCustomKeyEventID *curr = Telcom_custom_key_event_root;

  while (curr) {
    if (key_id == curr->key_id) {
      curr->downcount++;
      return;
    }

    curr = curr->next;
  }
}
