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

 * $Logfile: /DescentIII/main/hud.cpp $
 * $Revision: 143 $
 * $Date: 4/19/00 5:07p $
 * $Author: Matt $
 *
 * $Log: /DescentIII/main/hud.cpp $
 *
 * 143   4/19/00 5:07p Matt
 * From Duane for 1.4
 * Added checks, asserts, and fixes for bad return values
 *
 * 142   4/06/00 9:25a Matt
 * Fixed a screen clear problem on at ATI Rage Fury Maxx in dual-chip mode
 * by forcing the screen to clear four times (instead of three).
 *
 * 141   3/20/00 12:10p Matt
 * Merge of Duane's post-1.3 changes.
 * Endian/enum fix.
 *
 * 140   10/21/99 4:28p Matt
 * Mac merge
 *
 * 139   7/08/99 6:20p Jason
 * fixed reticle bug
 *
 * 138   5/23/99 9:07p Matt
 * Changed the customtext2 multisafe functions to create the item when
 * it's updated, instead of having a separate create and update functions.
 * This deals with players who join a netgame after the level has started
 * (i.e., everyone but the server).
 *
 * 137   5/21/99 11:15p Samir
 * savegames save hud timer and special text states. restore too.
 *
 * 136   5/21/99 4:06p Matt
 * For customtext2 HUD items, store the buffer length in the HUD item.
 *
 * 135   5/21/99 3:06p Matt
 * Changed customtext2 HUD items so that the HUD system keeps the text
 * buffer an no one else references it directly.
 *
 * 134   5/20/99 5:48p Matt
 * Added a HUD item flag, for use by Dallas-created items, that makes a
 * HUD item persisitent for the duration of one level, but get cleared
 * between levels.
 *
 * 133   5/20/99 2:12a Matt
 * Don't blow away custom HUD items when resetting the HUD.  This fixes
 * one probem, but means that custom HUD items will never go away.  I'll
 * deal with that tomorrow.
 *
 * 132   5/19/99 11:25a Matt
 * Added multisafe functions & Dallas actions for showing a timer on the
 * screen and adding custom HUD messages.
 *
 * 131   5/17/99 6:04p Kevin
 * new training mission localized text
 *
 * 130   5/17/99 5:27p Kevin
 * changed enabled controls display for training mission
 *
 * 129   5/14/99 10:30a Kevin
 * fixed misplaced #endif
 *
 * 128   5/13/99 12:24p Kevin
 * added code for "Beta version"
 *
 * 127   5/05/99 5:45p Samir
 * initialize reticle in cockpit code now.
 *
 * 126   5/01/99 5:52p Samir
 * removed RenderHudMessages, and redid RenderHUDMessages so it did what
 * RenderHudMessages did, resets on screen hud messages.  The HUD message
 * console is resetted in ResetGameMessages.
 *
 * 125   5/01/99 1:56a Samir
 * timer always in debug builds, SCORE is off when dead.
 *
 * 124   4/26/99 5:51p Jason
 * fixed guided bug
 *
 * 123   4/24/99 10:38p Samir
 * cleaned up hud text problems in 'small mode'
 *
 * 122   4/24/99 8:43p Samir
 * when shrinking screen hud messages get rendered in black region.
 *
 * 121   4/22/99 3:43p Kevin
 * Training missions show controls on screen
 *
 * 120   4/21/99 9:29p Samir
 * don't draw score in multiplayer.
 *
 * 119   4/21/99 4:17p Matt
 * Added comments for table file filter
 *
 * 118   4/20/99 11:47a Samir
 * shrinking hud fixes.
 *
 * 117   4/08/99 4:08p Samir
 * moved timer below score and don't compile timer in release builds.
 *
 * 116   4/06/99 6:02p Matt
 * Added score system
 *
 * 115   4/06/99 2:00p Samir
 * added function to initialize hud items that don't go through config
 * file.
 *
 * 114   4/06/99 11:39a Samir
 * added more formatting options for hud items (added two other full
 * screen hud infs for different ships)
 *
 * 113   4/01/99 4:50p Matt
 * Took out Warning() function, chaning those calls to mprintf()
 *
 * 112   3/30/99 5:26p Samir
 * fixed quad weapon reticle problem.
 *
 * 111   3/30/99 2:39p Samir
 * added custom config file for fullscreen hud and hacked mass driver
 * reticle in special reticle code.
 *
 * 110   3/29/99 10:50a Samir
 * added command to move reticle in hud inf file.
 *
 * 109   3/26/99 12:46p Samir
 * configurable reticle.
 *
 * 108   3/22/99 4:26p Samir
 * added toggles for guided missile view and reticle.
 *
 * 107   3/09/99 12:20p Samir
 * do quick close of cockpit if entering letterbox or observer mode from
 * cockpit.
 *
 * 106   3/05/99 3:01p Jeff
 * fixed crash when a persistant message is displayed during a IGC
 *
 * 105   3/04/99 8:11p Samir
 * Don't assert if screen mode != SM_GAME in SetHUDMode, just Int3 and
 * allow user to return.
 *
 * 104   3/03/99 5:34p Matt
 * Added fade-out for goal complete messages
 *
 * 103   3/03/99 3:43a Samir
 * fixed font aspect ratio problem in hires screens.
 *
 * 102   3/02/99 6:26p Samir
 * hires font madness.
 *
 * 101   2/28/99 3:25a Samir
 * stream name debug out.
 *
 * 100   2/27/99 5:07p Jason
 * clear screen 3 times for triple buffer
 *
 * 99    2/24/99 12:25p Jeff
 * fixed guided missile/mass driver reticle/view problems when going into
 * a cinematic
 *
 * 98    2/18/99 4:02p Jeff
 * only save hud mode to pilot file if fullscreen->cockpit or vice-versa
 *
 * 97    2/17/99 2:45p Kevin
 * Adde movie making capabilities to the demo playback system
 *
 * 96    2/15/99 7:49p Jeff
 * new pilot file class and read/write system checked in...should be more
 * robust than old
 *
 * 95    2/10/99 3:03p Samir
 * table file parse changes.
 *
 * 94    1/31/99 9:05p Jeff
 * handle HUD_OBSERVER in render
 *
 * 93    1/31/99 7:26p Matt
 * Renamed a bunch of functions to have HUD capitalized
 *
 * 92    1/29/99 6:29p Samir
 * implemented hud scrollback for hud messages.
 *
 * 91    1/29/99 2:08p Jeff
 * localization
 *
 * 90    1/28/99 2:22p Samir
 * simplified music system for D3.
 *
 * 89    1/27/99 6:05p Samir
 * added scrollback for game messages on HUD.
 *
 * 88    1/08/99 2:55p Samir
 * Ripped out OSIRIS1.
 *
 * 87    12/16/98 1:57p Samir
 * Replaced CleanupString2 with CleanupStr
 *
 * 86    12/03/98 12:52p Samir
 * added hud music debug info timers.
 *
 * 85    12/01/98 3:34p Matt
 * Got rear view working.
 *
 * 84    11/23/98 4:52p Kevin
 * Demo system enhancments
 *
 * 83    11/19/98 5:40p Kevin
 * Demo system
 *
 * 82    11/13/98 4:25p Jason
 * changes for better weapon effects
 *
 * 81    11/13/98 2:28p Samir
 * added debug code for music.
 *
 * 80    10/30/98 1:13p Samir
 * dont' do SetHUDMode if in dedicated server mode.
 *
 * 79    10/22/98 2:40p Samir
 * redid HUD sequencing so multiplayer hud stuff works.
 *
 * 78    10/20/98 1:46p Samir
 * don't close cockpit if it's already open.
 *
 * 77    10/19/98 11:22p Samir
 * added hud observer mode and fixed problems with hud switching and
 * screen size.
 *
 * 76    10/14/98 4:27p Samir
 * improved HUD_ITEM_CUSTOMTEXT
 *
 * 75    10/07/98 5:52p Samir
 * fixed small bug in hud stat masks.
 *
 * 74    10/02/98 5:47p Samir
 * moved reticle down a bit.
 *
 * 73    9/28/98 11:00a Samir
 * fixed stupid bug.
 *
 * 72    9/18/98 4:33p Samir
 * added dummy code for New Inf format hud files.
 *
 * 71    8/31/98 3:39p Samir
 * if no energy or ammo, reticle will reflect this.
 *
 * 70    8/25/98 3:07p Samir
 * when cockpit fails redo hud switch to fullscreen.
 *
 * 69    8/18/98 1:11a Samir
 * fixed some stuff for multi cockpit configs.
 *
 * 68    8/15/98 10:51p Matt
 * Added function ToggleHUDMode(), and made StartHudInputMessage() public.
 *
 * 67    7/06/98 7:34p Samir
 * added countermeasures.
 *
 * 66    6/25/98 12:52p Samir
 * draw afterburner hud in cockpit (special version)
 *
 * 65    6/24/98 7:38p Samir
 * redid graphical/text/cockpit hud item management.
 *
 * 64    6/19/98 5:39p Samir
 * use pilot information to get hud layout.
 *
 * 63    6/17/98 6:31p Samir
 * Added anti-grav warning when dying.
 *
 * 62    6/15/98 6:54p Samir
 * added invulnerability and cloak effect.
 *
 * 61    6/05/98 5:34p Samir
 * if cockpit already up, when setting cockpit mode, do quick open.
 *
 * 60    5/26/98 10:49p Samir
 * default to cockpit.
 *
 * 59    5/26/98 5:05p Samir
 * cockpit and hud config file now 'unified'.   cockpit adds to hudconfig
 * load's funtionality, so cockpit info files can contain same syntax as
 * hud file.
 *
 * 58    5/25/98 8:30p Samir
 * guided missile reticle and added a hud timer.
 *
 * 57    5/22/98 1:36p Samir
 * implemented a lot of hud items.
 *
 * 56    5/15/98 5:36p Samir
 * use correct font scale for lores screens.
 *
 * 55    5/15/98 3:39p Samir
 * reticle alphaed.
 *
 * 54    5/07/98 6:01p Samir
 * allow for certain hud items to  not be resettable.
 *
 * 53    5/07/98 2:51p Samir
 * took out extern functions.
 *
 * 52    5/05/98 6:27p Samir
 * added hud aspect ratio values and reticle is scaled correctly.
 *
 * 51    4/28/98 4:25p Samir
 * scale font with hud shrink.
 *
 * 50    4/27/98 1:14p Jason
 * cleaned up afterburner stuff
 *
 * 49    4/24/98 5:32p Samir
 * new reticle implemented.
 *
 * 48    4/24/98 8:01a Samir
 * don't pass zoom argument to Render functions.
 *
 * 47    4/23/98 4:13a Samir
 * new hud system.
 *
 * 46    4/19/98 5:00p Jason
 * added cool napalm effect, plus made object effects dynamically
 * allocated
 *
 * 45    4/17/98 1:59p Jason
 * added cool object effects
 *
 * 44    4/16/98 6:52a Samir
 * initialize bitmap handle to -1 always when initializing hud item.
 *
 * 43    4/14/98 9:19p Samir
 * made hacked good looking reticle for mag demo.
 *
 * 42    4/13/98 7:02p Samir
 * beginning reticle code.
 *
 * 41    4/01/98 6:23p Jason
 * added a slew of stuff for multiplayer
 *
 * 40    3/25/98 11:59a Samir
 * implemented energy analog fully.
 *
 * 39    3/24/98 4:27p Samir
 * modified energy gauges.
 *
 * 38    3/22/98 5:03p Samir
 * updated cockpit.
 *
 * 37    3/20/98 8:23p Samir
 * new hud and cockpit customization system.
 *
 * 36    3/19/98 9:19p Samir
 * removed dependency of hud.h on game.h.
 *
 * 35    3/18/98 6:25p Samir
 * Added new STAT_ constants/
 *
 * 34    3/17/98 2:40p Samir
 * reorg of cockpit/gauges and hud systems.
 *
 * 33    3/16/98 3:30p Samir
 * incremental checkin.
 *
 * 32    3/13/98 12:09p Samir
 * made changes to reflect new cockpit.cpp and cockpit.h
 *
 * 31    2/17/98 2:22p Jason
 * fixed some potential z sorting problems
 *
 * 30    2/14/98 10:48p Jason
 * got preferred rendering working
 *
 * 29    2/12/98 4:20p Matt
 * Made letterbox window shorter.
 *
 * 28    1/28/98 10:34a Samir
 * Reticle.
 *
 * 27    1/13/98 4:27p Samir
 * Fixed clear screen strangeness.
 *
 * 26    12/29/97 5:44p Samir
 * Took out references to grViewport and old 2d library.
 *
 *
 * 1     5/14/97 11:12a Jason
 * file rendering stuff on the hud
 *
 * $NoKeywords: $
 */

#include "hud.h"
#include "gauges.h"
#include "grdefs.h"
#include "game.h"
#include "ddio.h"
#include "player.h"
#include "renderer.h"
#include "descent.h"
#include "object.h"
#include "gamefont.h"
#include "polymodel.h"
#include "cockpit.h"
#include "game2dll.h"
#include "ship.h"
#include "pilot.h"
#include "mem.h"
#include "musicapi.h"
#include "demofile.h"
#include "stringtable.h"
#include "pstring.h"
#include "config.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include "gamecinematics.h"
#include "CtlCfgElem.h"
#include "ctlconfig.h"

//////////////////////////////////////////////////////////////////////////////
//	constants

#define FRAMERATE_TIME_DELAY 0.25 // update every quarter second

//////////////////////////////////////////////////////////////////////////////

//	PLAYER SAVEGAME PREFERENCES START
//	determines what's displayable on the hud
#ifdef E3_DEMO
tStatMask Hud_stat_mask = STAT_TIMER;
#else
tStatMask Hud_stat_mask = 0;
#endif

#define STAT_SCORE STAT_TIMER

//	PLAYER SAVEGAME PREFERENCES END

//	hud aspect
float Hud_aspect_x = 1.0f;
float Hud_aspect_y = 1.0f;
bool Small_hud_flag = false; // changes how hud items are drawn in small huds.

// used by reticle system.
static int16_t Ret_x_off, Ret_y_off;
static char Reticle_prefix[PSFILENAME_LEN + 1];

//	Hud mode of display
static tHUDMode Hud_mode = HUD_COCKPIT;

// hud item array.
static tHUDItem HUD_array[MAX_HUD_ITEMS];

#define HUDITEMUSED(_c) (HUD_array[_c].stat ? true : false)

//	hud resource structure
struct sHUDResources HUD_resources;

// initializes non configurable hud items.
static void InitDefaultHUDItems();

//	initializes items based off their type (information, etc.)
static void InitHUDItem(int new_item, tHUDItem *item);

//	iterate through entire hud item list to draw.
static void RenderHUDItems(tStatMask stat_mask);

//	renders the reticle
static void RenderReticle();

//	renders missile reticle
static void RenderMissileReticle();

//	renders zoom reticle
static void RenderZoomReticle();

//	hack!

//	functions in HudDisplay.cpp
extern void HudDisplayRouter(tHUDItem *item);

bool Hud_show_controls = false;

//////////////////////////////////////////////////////////////////////////////

//	initializes hud.
void InitHUD() {
  int i;
  extern bool HUD_disabled; // from gameloop.cpp

  for (i = 0; i < MAX_HUD_ITEMS; i++) {
    HUD_array[i].stat = 0;
    HUD_array[i].flags = 0;
    HUD_array[i].id = HUD_INVALID_ID;
  }

  //	load static hud image resources to be used by HudDisplay.cpp
  HUD_resources.arrow_bmp = -1;
  HUD_resources.goal_bmp = -1;
  HUD_resources.goal_complete_bmp = -1;
  HUD_resources.lock_bmp[0] = -1;
  HUD_resources.lock_bmp[1] = -1;
  HUD_resources.wpn_bmp = -1;
  HUD_resources.dot_bmp = -1;
  HUD_resources.antigrav_bmp[0] = -1;
  HUD_resources.antigrav_bmp[1] = -1;
  strcpy(HUD_resources.hud_inf_name, "hud.inf");

  strcpy(Reticle_prefix, "ret");
  Ret_x_off = 0;
  Ret_y_off = 0;

  for (i = 0; i < NUM_SHIELD_GAUGE_FRAMES; i++)
    HUD_resources.shield_bmp[i] = -1;
  HUD_resources.energy_bmp = -1;
  HUD_resources.afterburn_bmp = -1;
  HUD_resources.invpulse_bmp = -1;

  // this call may be unnecessary since it's called again in InitCockpit.
  //	InitReticle(-1,-1);					// initialize reticle system

  // scrollback windows
  ResetGameMessages(); // resets game message rollback screen.
  ResetHUDMessages();
  HUD_disabled = 0;
}

//	closes hud.
void CloseHUD() {
  int i;

  CloseHUDMessageConsole();  // closes down rollback console
  CloseGameMessageConsole(); // closes game journal rollback
  ResetGameMessages();       // reset game message system.
  ResetHUDMessages();

  //	free hud items.
  for (i = 0; i < MAX_HUD_ITEMS; i++) {
    if (HUD_array[i].stat) {
      FreeHUDItem(i);
    }
  }
}

tHUDItem *GetHUDItem(int id) { return &HUD_array[id]; }

//	initializes hud.
void InitShipHUD(int ship) {
  int i;

  //	load static hud image resources to be used by HudDisplay.cpp
  HUD_resources.arrow_bmp = bm_AllocLoadFileBitmap("hudarrow.ogf", 0);
  HUD_resources.goal_bmp = bm_AllocLoadFileBitmap("hudgoal.ogf", 0);
  HUD_resources.goal_complete_bmp = bm_AllocLoadFileBitmap("hudgoalon.ogf", 0);
  HUD_resources.lock_bmp[0] = bm_AllocLoadFileBitmap("hudlockl.ogf", 0);
  HUD_resources.lock_bmp[1] = bm_AllocLoadFileBitmap("hudlockr.ogf", 0);
  HUD_resources.wpn_bmp = bm_AllocLoadFileBitmap("hudicon.ogf", 0);
  HUD_resources.dot_bmp = bm_AllocLoadFileBitmap("huddot.ogf", 0);
  HUD_resources.antigrav_bmp[0] = bm_AllocLoadFileBitmap("hudantigravl.ogf", 0);
  HUD_resources.antigrav_bmp[1] = bm_AllocLoadFileBitmap("hudantigravr.ogf", 0);

  for (i = 0; i < NUM_SHIELD_GAUGE_FRAMES; i++)
    HUD_resources.shield_bmp[i] = -1;
  HUD_resources.energy_bmp = -1;
  HUD_resources.afterburn_bmp = -1;
  HUD_resources.invpulse_bmp = -1;

  //	sets current hud mode static global
  // DAJ	Current_pilot.get_hud_data((uint8_t *)&Hud_mode);
  uint8_t hud_tmp;
  Current_pilot.get_hud_data(&hud_tmp);
  Hud_mode = (tHUDMode)hud_tmp;
}

// closes hud for current ship
void CloseShipHUD() {
  FreeReticle();

  //	free hud resources
  bm_FreeBitmap(HUD_resources.antigrav_bmp[1]);
  bm_FreeBitmap(HUD_resources.antigrav_bmp[0]);
  bm_FreeBitmap(HUD_resources.dot_bmp);
  bm_FreeBitmap(HUD_resources.wpn_bmp);
  bm_FreeBitmap(HUD_resources.lock_bmp[1]);
  bm_FreeBitmap(HUD_resources.lock_bmp[0]);
  bm_FreeBitmap(HUD_resources.goal_complete_bmp);
  bm_FreeBitmap(HUD_resources.goal_bmp);
  bm_FreeBitmap(HUD_resources.arrow_bmp);
}

//	places an item on the hud
void AddHUDItem(tHUDItem *item) {
  //	find free hud slot.
  int i;

  for (i = 0; i < MAX_HUD_ITEMS; i++) {
    if (!HUD_array[i].stat) {
      //	we will initialize the hud item.
      InitHUDItem(i, item);
      break;
    }
  }

  if (i == MAX_HUD_ITEMS) {
    mprintf(0, "Unable to add hud item (type=%d).\n", item->type);
  }
}

//	resets hud
void ResetHUD() {
  int i;

  for (i = 0; i < MAX_HUD_ITEMS; i++) {
    if (HUD_array[i].stat && !(HUD_array[i].flags & HUD_FLAG_LEVEL) && !(HUD_array[i].flags & HUD_FLAG_PERSISTANT)) {
      FreeHUDItem(i);
    }
  }
}

// clears out HUD level items
void ResetHUDLevelItems() {
  int i;
  for (i = 0; i < MAX_HUD_ITEMS; i++) {
    if (HUD_array[i].stat && (HUD_array[i].flags & HUD_FLAG_LEVEL)) {
      FreeHUDItem(i);
    }
  }
}

// from game.cpp
extern void InitGameScreen(int, int);
extern bool Dedicated_server;

//	manually sets the cockpit display.
void SetHUDMode(tHUDMode mode) {
  static int saved_window_w = 0, saved_window_h = 0;

  if (Dedicated_server)
    return;

  if (GetScreenMode() != SM_GAME) {
#ifdef _DEBUG
    Int3();
#endif
    return;
  }

  //	clear the screen.
  Clear_screen = 4;

  //	free poly model of cockpit if we're not switching to a cockpit mode.
  if (Hud_mode == HUD_COCKPIT && IsValidCockpit()) {
    if (mode == HUD_LETTERBOX || mode == HUD_OBSERVER) {
      QuickCloseCockpit();
    } else if (mode != HUD_COCKPIT) {
      CloseCockpit();
    }
  }

//	do cockpit specific thing.
redo_hud_switch:
  switch (mode) {
    uint16_t cp_hud_stat, cp_hud_graphical_stat;

  case HUD_LETTERBOX:
    //	our objective here is to display a letterbox screen for the cockpit.
    //	we save the old width and height of the windows.
    saved_window_w = Game_window_w;
    saved_window_h = Game_window_h;

    Game_window_w = Max_window_w;
    Game_window_h = Max_window_h - (Max_window_h / 3);

    if (Game_window_h > Max_window_h)
      Game_window_h = Max_window_h;

    if (Game_window_w > Max_window_w)
      Game_window_w = Max_window_w;

    Game_window_x = (Max_window_w - Game_window_w) / 2;
    Game_window_y = (Max_window_h - Game_window_h) / 2;

    SetHUDState(STAT_MESSAGES | (Hud_stat_mask & STAT_FPS), 0);
    break;

  case HUD_FULLSCREEN:
    //	our objective here is to display a fullscreen box that is resizable.
    LoadHUDConfig(HUD_resources.hud_inf_name);

    InitGameScreen(saved_window_w ? saved_window_w : Game_window_w, saved_window_h ? saved_window_h : Game_window_h);
    saved_window_w = 0;
    saved_window_h = 0;

    Current_pilot.get_hud_data(NULL, &cp_hud_stat, &cp_hud_graphical_stat);

    SetHUDState(cp_hud_stat | STAT_SCORE | (Hud_stat_mask & STAT_FPS), cp_hud_graphical_stat);

    break;

  case HUD_COCKPIT:
    if (!IsValidCockpit()) {
      mode = HUD_FULLSCREEN;
      AddHUDMessage(TXT_NOCOCKPIT);
      goto redo_hud_switch;
    }
    if (Hud_mode == HUD_COCKPIT || Hud_mode == HUD_LETTERBOX || Hud_mode == HUD_OBSERVER)
      QuickOpenCockpit();
    else
      OpenCockpit();

    InitGameScreen(saved_window_w ? saved_window_w : Game_window_w, saved_window_h ? saved_window_h : Game_window_h);

    saved_window_w = 0;
    saved_window_h = 0;

    Current_pilot.get_hud_data(NULL, &cp_hud_stat, &cp_hud_graphical_stat);

    SetHUDState(STAT_MESSAGES | STAT_SHIELDS | STAT_ENERGY | STAT_GOALS | STAT_CUSTOM | STAT_AFTERBURN |
                    STAT_INVENTORY | STAT_CNTRMEASURE | STAT_SCORE | (Hud_stat_mask & STAT_WARNING) |
                    (Hud_stat_mask & STAT_FPS) | (Hud_stat_mask & STAT_SCORE),
                (cp_hud_graphical_stat & STAT_WARNING));
    break;

  case HUD_OBSERVER:
    InitGameScreen(saved_window_w ? saved_window_w : Game_window_w, saved_window_h ? saved_window_h : Game_window_h);
    saved_window_w = 0;
    saved_window_h = 0;

    SetHUDState(STAT_MESSAGES | (Hud_stat_mask & STAT_FPS), 0);
    break;

  default:
    Int3();
  }

  // save out current hud mode
  // JEFF: (only if going from HUD_FULLSCREEN->HUD_COCKPIT or vice-versa)
  if ((Hud_mode == HUD_FULLSCREEN && mode == HUD_COCKPIT) || (Hud_mode == HUD_COCKPIT && mode == HUD_FULLSCREEN)) {
    uint8_t bmode = mode; // DAJ MAC using enums always int
    Current_pilot.set_hud_data((uint8_t *)&bmode);
    mprintf(0, "Saving new hud mode to pilot\n");
    PltWriteFile(&Current_pilot);
  }

  Hud_mode = mode;
}

//	the current cockpit mode;
tHUDMode GetHUDMode() { return Hud_mode; }

// toggle the hud between cockput & fullscreen modes
void ToggleHUDMode() {
  if (GetHUDMode() == HUD_COCKPIT)
    SetHUDMode(HUD_FULLSCREEN);
  else if (GetHUDMode() == HUD_FULLSCREEN)
    SetHUDMode(HUD_COCKPIT);
}

// sets the hud item state(what's visible, how it's drawn, etc)
void SetHUDState(uint16_t hud_mask, uint16_t hud_gr_mask) {
  int i;

  Hud_stat_mask = (hud_mask | hud_gr_mask);

  // now go through each hud item, check if it's hud stat mask includes the requested hud_gr_mask
  //	if it does, then set hud mask to graphical
  for (i = 0; i < MAX_HUD_ITEMS; i++) {
    HUD_array[i].stat &= ~(STAT_GRAPHICAL);
    if (HUD_array[i].stat & hud_gr_mask)
      HUD_array[i].stat |= STAT_GRAPHICAL;
  }
}

//	initializes items based off their type (information, etc.)
void InitHUDItem(int new_item, tHUDItem *item) {
  ASSERT(new_item < MAX_HUD_ITEMS);
  uint16_t stat = 0x0000;

  item->id = new_item;

  switch (item->type) {
  case HUD_ITEM_PRIMARY:
    stat = STAT_PRIMARYLOAD;
    break;

  case HUD_ITEM_SECONDARY:
    stat = STAT_SECONDARYLOAD;
    break;

  case HUD_ITEM_SHIELD:
    stat = STAT_SHIELDS;
    break;

  case HUD_ITEM_ENERGY:
    stat = STAT_ENERGY;
    break;

  case HUD_ITEM_AFTERBURNER:
    stat = STAT_AFTERBURN;
    break;

  case HUD_ITEM_INVENTORY:
    stat = STAT_INVENTORY;
    break;

  case HUD_ITEM_SHIPSTATUS:
    stat = STAT_SHIP;
    break;

  case HUD_ITEM_CNTRMEASURE:
    stat = STAT_CNTRMEASURE;
    break;

  case HUD_ITEM_CUSTOMTEXT:
    if (item->data.text) {
      char *text = mem_strdup(item->data.text);
      HUD_array[new_item].data.text = text;
    }
    stat = STAT_CUSTOM;
    break;

  case HUD_ITEM_CUSTOMTEXT2:  // malloc buffer to be updated later
    HUD_array[new_item].data.text = (char *)mem_malloc(item->buffer_size);
    HUD_array[new_item].data.text[0] = 0;
    HUD_array[new_item].buffer_size = item->buffer_size;
    stat = STAT_CUSTOM;
    break;

  case HUD_ITEM_CUSTOMIMAGE:
    stat = STAT_CUSTOM;
    break;

  case HUD_ITEM_WARNINGS:
    stat = STAT_WARNING;
    break;

  case HUD_ITEM_GOALS:
  case HUD_ITEM_GOALSTATES:
    stat = STAT_GOALS;
    break;

  case HUD_ITEM_SCORE:
    stat = STAT_SCORE;
    break;

  case HUD_ITEM_TIMER:
    HUD_array[new_item].data.timer_handle = item->data.timer_handle;
    stat = STAT_CUSTOM;
    break;

  default:
    Int3();
  }

  //	copy hud item structure.
  HUD_array[new_item].x = item->x;
  HUD_array[new_item].y = item->y;
  HUD_array[new_item].xa = item->xa;
  HUD_array[new_item].ya = item->ya;
  HUD_array[new_item].xb = item->xb;
  HUD_array[new_item].yb = item->yb;
  HUD_array[new_item].tx = item->tx;
  HUD_array[new_item].ty = item->ty;
  HUD_array[new_item].grscalex = item->grscalex;
  HUD_array[new_item].grscaley = item->grscaley;
  HUD_array[new_item].type = item->type;
  HUD_array[new_item].stat = item->stat | stat;
  HUD_array[new_item].flags = item->flags;
  HUD_array[new_item].alpha = item->alpha;
  HUD_array[new_item].color = item->color;
  HUD_array[new_item].tcolor = item->tcolor;
  HUD_array[new_item].saturation_count = item->saturation_count;
  HUD_array[new_item].render_fn = item->render_fn;
  HUD_array[new_item].id = item->id;
  HUD_array[new_item].dirty_rect.reset();
}

// Returns the item number if there's a customtext2 item, else -1
int FindCustomtext2HUDItem() {
  int i;
  for (i = 0; i < MAX_HUD_ITEMS; i++) {
    if (HUD_array[i].stat && (HUD_array[i].type == HUD_ITEM_CUSTOMTEXT2))
      return i;
  }

  return -1;
}

// Updates the customtext2 item, if there is one
void UpdateCustomtext2HUDItem(char *text) {
  int i;

  for (i = 0; i < MAX_HUD_ITEMS; i++) {
    if (HUD_array[i].stat && (HUD_array[i].type == HUD_ITEM_CUSTOMTEXT2)) {
      ASSERT(HUD_array[i].data.text != NULL);
      strncpy(HUD_array[i].data.text, text, HUD_array[i].buffer_size);
      HUD_array[i].data.text[HUD_array[i].buffer_size - 1];
      break;
    }
  }
}

// savegame system hooks
void SGSHudState(CFILE *fp) {
  int i;
  tHUDItem *huditem;

  for (i = 0; i < MAX_HUD_ITEMS; i++) {
    // save custom text2 and timer hud items
    huditem = &HUD_array[i];
    if (huditem->stat) {
      if (huditem->type == HUD_ITEM_CUSTOMTEXT2) {
        cf_WriteShort(fp, (int16_t)huditem->stat);
        cf_WriteByte(fp, (int8_t)huditem->type);
        cf_WriteShort(fp, huditem->x);
        cf_WriteShort(fp, huditem->y);
        cf_WriteInt(fp, huditem->color);
        cf_WriteShort(fp, (int16_t)huditem->flags);
        cf_WriteByte(fp, (int8_t)huditem->alpha);

        cf_WriteShort(fp, (int16_t)huditem->buffer_size);
        cf_WriteString(fp, huditem->data.text);
        mprintf(0, "sg: saved customtext2 (%x,%x,bufsize=%d)\n", huditem->x, huditem->y, huditem->buffer_size);
      } else if (huditem->type == HUD_ITEM_TIMER) {
        cf_WriteShort(fp, (int16_t)huditem->stat);
        cf_WriteByte(fp, (int8_t)huditem->type);
        cf_WriteShort(fp, huditem->x);
        cf_WriteShort(fp, huditem->y);
        cf_WriteInt(fp, huditem->color);
        cf_WriteShort(fp, (int16_t)huditem->flags);
        cf_WriteByte(fp, (int8_t)huditem->alpha);

        cf_WriteInt(fp, huditem->data.timer_handle);
        mprintf(0, "sg: restored timer (%x,%x,timer_hndl=%d)\n", huditem->x, huditem->y, huditem->data.timer_handle);
      } else if (huditem->type == HUD_ITEM_CUSTOMTEXT) {
        // commented out because persistent hud messages are custom text, and its a mess to save the current
        // state of hud persistent messages.
        //	cf_WriteShort(fp, (int16_t)huditem->stat);
        //	cf_WriteByte(fp, (int8_t)huditem->type);
        //	cf_WriteShort(fp, huditem->x);
        //	cf_WriteShort(fp, huditem->y);
        //	cf_WriteInt(fp, huditem->color);
        //	cf_WriteShort(fp, (int16_t)huditem->flags);
        //	cf_WriteByte(fp, (int8_t)huditem->alpha);
        //
        //	cf_WriteString(fp, huditem->data.timer_handle);
      }
    }
  }

  cf_WriteShort(fp, 0); // mark end of saved hud items.
}

bool LGSHudState(CFILE *fp) {
  //	restore hud items
  uint16_t stat_mask = 0;

  while ((stat_mask = (uint16_t)cf_ReadShort(fp)) != 0) {
    tHUDItem huditem;
    uint8_t item_type = (uint8_t)cf_ReadByte(fp);

    memset(&huditem, 0, sizeof(huditem));
    huditem.type = item_type;
    huditem.stat = stat_mask;

    switch (item_type) {
      char *buffer;
      extern void RenderHUDTimer(tHUDItem * item);

    case HUD_ITEM_CUSTOMTEXT2:
      huditem.x = cf_ReadShort(fp);
      huditem.y = cf_ReadShort(fp);
      huditem.color = (ddgr_color)cf_ReadInt(fp);
      huditem.flags = (uint16_t)cf_ReadShort(fp);
      huditem.alpha = (uint8_t)cf_ReadByte(fp);

      huditem.buffer_size = (int)cf_ReadShort(fp);
      huditem.render_fn = NULL; // use pointer to function void (*fn)(struct tHUDItem *)
      AddHUDItem(&huditem);

      buffer = (char *)mem_malloc(huditem.buffer_size);
      cf_ReadString(buffer, huditem.buffer_size, fp);
      UpdateCustomtext2HUDItem(buffer);
      mem_free(buffer);
      mprintf(0, "lg: restored customtext2 (%x,%x,bufsize=%d)\n", huditem.x, huditem.y, huditem.buffer_size);
      break;

    case HUD_ITEM_TIMER:
      huditem.x = cf_ReadShort(fp);
      huditem.y = cf_ReadShort(fp);
      huditem.color = (ddgr_color)cf_ReadInt(fp);
      huditem.flags = (uint16_t)cf_ReadShort(fp);
      huditem.alpha = (uint8_t)cf_ReadByte(fp);

      huditem.data.timer_handle = cf_ReadInt(fp);
      huditem.render_fn = RenderHUDTimer; // use pointer to function void (*fn)(struct tHUDItem *)
      AddHUDItem(&huditem);
      mprintf(0, "lg: restored timer (%x,%x,timer_hndl=%d)\n", huditem.x, huditem.y, huditem.data.timer_handle);
      break;

    // case HUD_ITEM_CUSTOMTEXT:
    //	break;
    default:
      return false;
    }
  }

  return true;
}

//	frees hud items based off their type class.
void FreeHUDItem(int item) {
  ASSERT(item < MAX_HUD_ITEMS);

  HUD_array[item].stat = 0;
  HUD_array[item].flags = 0;
  HUD_array[item].id = HUD_INVALID_ID;
  if (((HUD_array[item].type == HUD_ITEM_CUSTOMTEXT) || (HUD_array[item].type == HUD_ITEM_CUSTOMTEXT2)) &&
      HUD_array[item].data.text) {
    mem_free(HUD_array[item].data.text);
    HUD_array[item].data.text = NULL;
  }
}

extern void RenderHUDScore(tHUDItem *item);

// initializes non configurable hud items.
void InitDefaultHUDItems() {
  tHUDItem huditem;

  memset(&huditem, 0, sizeof(huditem));
  huditem.type = HUD_ITEM_SCORE; // KEEP THIS
  huditem.stat = STAT_SCORE;     // This is bound to timer. in release builds, no timer code but just score
  huditem.x = 640;               // position on HUD in 640,480 coordinates
  huditem.y = 5;
  huditem.color = HUD_COLOR;          // you can ignore this if you dont use this value passed into your render function
  huditem.render_fn = RenderHUDScore; // use pointer to function void (*fn)(struct tHUDItem *)
  AddHUDItem(&huditem);
}

//	loads in hud configuration file, adds hud items.
void LoadHUDConfig(const char *filename, bool (*fn)(const char *, const char *, void *), void *ext_data) {
  CFILE *fp;
  char srcline[128];     // One line of mission source
  bool text_pos = false; // text position defined?

  //	start over.
  ResetHUD();
  InitDefaultHUDItems();

  //	open file
  fp = cfopen(filename, "rt");
  if (!fp) {
    mprintf(0, "Unable to find hud.inf file.\n");
    return;
  }

  //	check if valid cockpit file
  cf_ReadString(srcline, sizeof(srcline), fp);

  if (stricmp(srcline, "[hud file]") == 0) {
    tHUDItem hud_item;

    memset(&hud_item, 0, sizeof(hud_item));
    hud_item.alpha = HUD_ALPHA;
    hud_item.color = HUD_COLOR;
    hud_item.tcolor = HUD_COLOR;

    while (!cfeof(fp)) {
      char command[32]; // Command read from line.
      char operand[96]; // operand read from line
      char *keyword;    // parsed keyword
      int readcount;    // read-in count

      readcount = cf_ReadString(srcline, sizeof(srcline), fp);
      if (readcount) {
        //	we have a line of source.  parse out primary keyword
        //	then parse out remainder.
        keyword = strtok(srcline, " \t=");
        CleanupStr(command, srcline, sizeof(command));
        CleanupStr(operand, srcline + strlen(command) + 1, sizeof(operand));

        //	skip comments
        if (command[0] == '@')
          continue;

        //	find command,
        if (!stricmp(command, "type")) {
          //	get operand.
          hud_item.type = atoi(operand);
        } else if (!stricmp(command, "pos")) {
          //	get two numbers from line
          int ix, iy;
          sscanf(operand, "%d,%d", &ix, &iy);
          hud_item.x = ix;
          hud_item.y = iy;
        } else if (!stricmp(command, "posA")) {
          //	get two numbers from line
          int ix, iy;
          sscanf(operand, "%d,%d", &ix, &iy);
          hud_item.xa = ix;
          hud_item.ya = iy;
        } else if (!stricmp(command, "posB")) {
          //	get two numbers from line
          int ix, iy;
          sscanf(operand, "%d,%d", &ix, &iy);
          hud_item.xb = ix;
          hud_item.yb = iy;
        } else if (!stricmp(command, "grscale")) {
          sscanf(operand, "%f,%f", &hud_item.grscalex, &hud_item.grscaley);
        } else if (!stricmp(command, "textpos")) {
          //	get two numbers from line
          int ix, iy;
          sscanf(operand, "%d,%d", &ix, &iy);
          hud_item.tx = ix;
          hud_item.ty = iy;
          text_pos = true;
        } else if (!stricmp(command, "alpha")) {
          // get alpha value.
          hud_item.alpha = atoi(operand);
        } else if (!stricmp(command, "sat")) {
          // saturation count
          hud_item.saturation_count = atoi(operand);
        } else if (!stricmp(command, "rgb")) {
          // saturation count
          int r, g, b;
          sscanf(operand, "%d,%d,%d", &r, &g, &b);
          hud_item.color = GR_RGB(r, g, b);
        } else if (!stricmp(command, "textrgb")) {
          int r, g, b;
          sscanf(operand, "%d,%d,%d", &r, &g, &b);
          hud_item.tcolor = GR_RGB(r, g, b);
        } else if (!stricmp(command, "special")) {
          hud_item.stat |= STAT_SPECIAL;
        } else if (!stricmp(command, "create")) {
          //	create hud item.
          if (!text_pos) {
            hud_item.tx = hud_item.x;
            hud_item.ty = hud_item.y;
          }
          hud_item.render_fn = HudDisplayRouter;
          AddHUDItem(&hud_item);

          //	reset hud item.
          memset(&hud_item, 0, sizeof(hud_item));
          hud_item.alpha = HUD_ALPHA;
          hud_item.color = HUD_COLOR;
          hud_item.tcolor = HUD_COLOR;
          text_pos = false;
        } else if (!stricmp(command, "reticleprefix")) {
          // copy prefix of reticle bitmaps.
          strcpy(Reticle_prefix, operand);
        } else if (!stricmp(command, "reticleoffset")) {
          int x, y;
          sscanf(operand, "%d,%d", &x, &y);
          Ret_x_off = (int16_t)x;
          Ret_y_off = (int16_t)y;
        } else if (fn && (*fn)(command, operand, ext_data)) {
          continue;
        } else {
          mprintf(0, "Error reading hud file.\n");
          Int3(); // contact samir.
          break;
        }
      }
    }
  } else {
    mprintf(0, "Not a valid hud file.\n");
  }

  // use any reticle specified.
  FreeReticle();
  InitReticle(0, 0);

  cfclose(fp);
}

//////////////////////////////////////////////////////////////////////////////
//	render cockpit and gauges frame
//		checks to see what cockpit mode we are in.
//		draws stuff accordingly.
//		render internal gauges too.

void RenderHUDFrame() {
  extern bool Guided_missile_smallview; // from smallviews.cpp

  rend_SetOverlayType(OT_NONE);

  // determine hud rendering properties.
  Hud_aspect_x = (float)Game_window_w / DEFAULT_HUD_WIDTH;
  Hud_aspect_y = (float)Game_window_h / DEFAULT_HUD_HEIGHT;
  Small_hud_flag = (((float)Game_window_w / (float)Max_window_w) <= 0.80f) ? true : false;

  //	render special missile hud if available
  if (Players[Player_num].guided_obj && !Guided_missile_smallview) {
    if (!Cinematic_inuse)
      RenderMissileReticle();
  } else if (Players[Player_num].flags & PLAYER_FLAGS_ZOOMED) {
    if (!Cinematic_inuse)
      RenderZoomReticle();
  } else if (!(Players[Player_num].flags & PLAYER_FLAGS_REARVIEW)) {
    switch (GetHUDMode()) {
    case HUD_FULLSCREEN:
      RenderHUDItems(Hud_stat_mask);
      RenderCockpit(); // needed to render animated deactivation sequence and should be dormant
      if (Game_toggles.show_reticle) {
        RenderReticle();
      }
      break;

    case HUD_COCKPIT:
      RenderHUDItems(Hud_stat_mask);
      RenderCockpit(); // called when cockpit is activating and functioning.
      if (Game_toggles.show_reticle) {
        RenderReticle();
      }
      break;

    case HUD_LETTERBOX:
      if (!Cinematic_inuse)
        RenderHUDItems(Hud_stat_mask);
      break;

    case HUD_OBSERVER:
      if (!Cinematic_inuse)
        RenderHUDItems(Hud_stat_mask);
      break;

    default:
      Int3();
    }
  }

  // Do dll stuff
  CallGameDLL(EVT_CLIENT_HUD_INTERVAL, &DLLInfo);

  rend_SetZBufferState(1);
  mprintf_at(2, 0, 0, "FPS: %f", GetFPS());
}

// renders hud frame before any graphics are drawn
void RenderPreHUDFrame() {
  extern void RenderHUDMsgDirtyRects();

  // render any dirty rectangles if small hud flag is set
  if (Small_hud_flag) {
    int i;

    for (i = 0; i < MAX_HUD_ITEMS; i++) {
      if ((Hud_stat_mask & HUD_array[i].stat) && (HUD_array[i].flags & HUD_FLAG_SMALL)) {
        HUD_array[i].dirty_rect.fill(GR_BLACK);
      }
    }

    // messages.
    if ((Hud_stat_mask & STAT_MESSAGES)) {
      RenderHUDMsgDirtyRects();
    }
  }
}

extern MsgListConsole Game_msg_con;
extern MsgListConsole HUD_msg_con;

// render auxillary hud
void RenderAuxHUDFrame() {
  //	take care of any 'small hud' stuff
  //	render hud array list for items drawn differently on a smaller hud.
  if (Small_hud_flag) {
    int cur_game_win_w = Game_window_w;
    int cur_game_win_h = Game_window_h;
    int cur_game_win_x = Game_window_x;
    int cur_game_win_y = Game_window_y;
    int i;
    uint16_t stat_mask = Hud_stat_mask;

    // emulating hud that takes up entire screen
    Game_window_w = Max_window_w;
    Game_window_h = Max_window_h;
    Game_window_x = 0;
    Game_window_y = 0;

    // determine hud rendering properties.
    Hud_aspect_x = (float)Game_window_w / DEFAULT_HUD_WIDTH;
    Hud_aspect_y = (float)Game_window_h / DEFAULT_HUD_HEIGHT;

    for (i = 0; i < MAX_HUD_ITEMS; i++) {
      if ((stat_mask & HUD_array[i].stat) && (HUD_array[i].flags & HUD_FLAG_SMALL)) {
        if (!HUD_array[i].render_fn) {
          HudDisplayRouter(&HUD_array[i]);
        } else {
          (*HUD_array[i].render_fn)(&HUD_array[i]);
        }
      }
    }

    // messages.
    if ((stat_mask & STAT_MESSAGES)) {
      RenderHUDMessages();
    }

    grtext_Flush();

    Game_window_w = cur_game_win_w;
    Game_window_h = cur_game_win_h;
    Game_window_x = cur_game_win_x;
    Game_window_y = cur_game_win_y;
  }

  // render game and hud message consoles.
  Game_msg_con.DoInput();
  Game_msg_con.Draw();
  HUD_msg_con.DoInput();
  HUD_msg_con.Draw();
}

char *GetControllerBindingText(int fidcont) {
  static char *cont_bind_txt;
  ct_type ctype[CTLBINDS_PER_FUNC];
  uint8_t cfgflags[CTLBINDS_PER_FUNC];
  ct_config_data cfgdata;
  tCfgDataParts cfgparts;
  if (-1 == fidcont)
    return NULL;
  cont_bind_txt = NULL;
  fidcont = CtlFindBinding(fidcont, false);
  if (fidcont == -1) // DAJ -1FIX
    return NULL;

  Controller->get_controller_function(Cfg_joy_elements[fidcont].fn_id, ctype, &cfgdata, cfgflags);
  parse_config_data(&cfgparts, ctype[0], ctype[1], cfgdata);
  uint8_t one_binding = cfgparts.bind_0;
  uint8_t one_ctrlbind = cfgparts.ctrl_0;

  cont_bind_txt = (char *)cfg_binding_text(ctype[0], one_ctrlbind, one_binding);
  return cont_bind_txt;
}

char *GetKeyBindingText(int fidkey) {
  static char *key_bind_txt;
  ct_type ctype[CTLBINDS_PER_FUNC];
  uint8_t cfgflags[CTLBINDS_PER_FUNC];
  ct_config_data cfgdata;
  tCfgDataParts cfgparts;
  if (-1 == fidkey)
    return NULL;
  key_bind_txt = NULL;
  fidkey = CtlFindBinding(fidkey, true);
  if (fidkey == -1) // DAJ -1FIX
    return NULL;

  Controller->get_controller_function(Cfg_key_elements[fidkey].fn_id, ctype, &cfgdata, cfgflags);
  parse_config_data(&cfgparts, ctype[0], ctype[1], cfgdata);
  uint8_t one_binding = cfgparts.bind_0;
  uint8_t one_ctrlbind = cfgparts.ctrl_0;

  key_bind_txt = (char *)cfg_binding_text(ctype[0], one_ctrlbind, one_binding);
  return key_bind_txt;
}

void DoEnabledControlsLine(const char *controlp, const char *keyp, const char *label, int y, const char *axis = NULL) {
  char control_text[200] = "";

  strcpy(control_text, label);
  strcat(control_text, " : ");
  if (keyp)
    strcat(control_text, keyp);
  if (keyp && (controlp || axis))
    strcat(control_text, " / ");
  if (controlp)
    strcat(control_text, controlp);
  if (controlp && axis)
    strcat(control_text, " / ");
  if (axis)
    strcat(control_text, axis);

  if (keyp || controlp || axis)
    RenderHUDTextFlags(0, GR_GREEN, HUD_ALPHA, 0, 30, y, control_text);
}

extern bool Demo_make_movie;

#define HUD_KEYS_NEXT_LINE hudconty += 14

//	iterate through entire hud item list to draw.
void RenderHUDItems(tStatMask stat_mask) {
  static float framerate_timer = 0;
  static float last_fps;
  float font_aspect_x, font_aspect_y;
  int i;

  grtext_Reset();
  grtext_SetFont(HUD_FONT);

  //	for lores screens, we use different fonts, so DONT SCALE.
  font_aspect_x = (float)Game_window_w / Max_window_w;
  font_aspect_y = (float)Game_window_h / Max_window_h;

  if (font_aspect_x <= 0.60f) {
    grtext_SetFontScale(0.60f);
  } else if (font_aspect_x <= 0.80f) {
    grtext_SetFontScale(0.80f);
  } else {
    grtext_SetFontScale(1.0f);
  }

  //	do framerate calculations
  framerate_timer -= Frametime;
  while (framerate_timer < 0) {
    framerate_timer += FRAMERATE_TIME_DELAY;
    last_fps = GetFPS();
  }

  //	show framerate text gauge
  if (stat_mask & STAT_FPS) {
    RenderHUDText(HUD_COLOR, HUD_ALPHA, 0, 10, 10, "FPS: %.1f", last_fps);
  }

  // show music spew

#ifdef _DEBUG
  if (Music_debug_verbose) {
    int min, sec;
    RenderHUDText(HUD_COLOR, HUD_ALPHA, 0, 10, 60, "Music: %s", IsD3MusicOn() ? "ON" : "OFF");
    RenderHUDText(HUD_COLOR, HUD_ALPHA, 0, 10, 72, "Region: %d", D3MusicGetRegion());
    RenderHUDText(HUD_COLOR, HUD_ALPHA, 0, 10, 84, "Song: %s", Music_type_names[Game_music_info.cur_song]);
    min = (int)(Game_music_info.peace_timer / 60);
    sec = (int)((Game_music_info.peace_timer / 60.0f - (float)min) * 60.0f);
    RenderHUDText(HUD_COLOR, HUD_ALPHA, 0, 10, 96, "Peace time: %d:%.2d", min, sec);

    if (Game_music_info.cur_loop_name) {
      RenderHUDText(HUD_COLOR, HUD_ALPHA, 0, 10, 108, "Loop: %s", Game_music_info.cur_loop_name);
    }
  }

  //	show timer
  if (1) {
    // timer always displayed in debug builds.
    int min, sec, y;

    min = (int)(Gametime / 60);
    sec = (int)((Gametime / 60.0f - (float)min) * 60.0f);

    y = (Game_mode & GM_MULTI) ? 10 : 40;

    RenderHUDText(HUD_COLOR, HUD_ALPHA, 0, 605, y, "%d:%.2d", min, sec);
  }
#endif

  //	render hud array list.
  for (i = 0; i < MAX_HUD_ITEMS; i++) {
    if ((HUD_array[i].flags & HUD_FLAG_SMALL) && Small_hud_flag) {
      continue; // skip items renderered differently on a small hud if we are in a small hud (see RenderAUXHUDFrame)
    }
    if ((stat_mask & HUD_array[i].stat)) {
      if (!HUD_array[i].render_fn) {
        HudDisplayRouter(&HUD_array[i]);
      } else {
        (*HUD_array[i].render_fn)(&HUD_array[i]);
      }
    }
  }
  if (Demo_flags == DF_RECORDING) {
    RenderHUDTextFlags(HUDTEXT_CENTERED, GR_BLUE, HUD_ALPHA, 0, 10, 300, TXT_RECORDINGDEMO);
  } else if (Demo_flags == DF_PLAYBACK) {
    if (!Demo_make_movie) {
      if (Demo_paused) {
        RenderHUDTextFlags(HUDTEXT_CENTERED, GR_BLUE, HUD_ALPHA, 0, 10, 300, TXT_DEMOPAUSED);
      } else {
        RenderHUDTextFlags(HUDTEXT_CENTERED, GR_BLUE, HUD_ALPHA, 0, 10, 300, TXT_PLAYINGDEMO);
      }
    }
  }

  // This is a big pain in the butt. It's for the training mission.
  if (Hud_show_controls && (Players[Player_num].controller_bitflags != 0xffffffff)) {
    char *controlp = NULL;
    char *keyp = NULL;
    char *axis = NULL;
    player *pp = &Players[Player_num];
    int fidkey = -1, fidcont = -1;
    int hudconty = 130;

    RenderHUDTextFlags(0, GR_GREEN, HUD_ALPHA, 0, 15, hudconty, TXT_ENABLED_CONTROLS);
    HUD_KEYS_NEXT_LINE;

    if (pp->controller_bitflags & PCBF_FORWARD) {
      keyp = GetKeyBindingText(ctfFORWARD_THRUSTKEY);
      controlp = GetControllerBindingText(ctfFORWARD_BUTTON);
      if (keyp || controlp) {
        DoEnabledControlsLine(controlp, keyp, TXT_ENABLED_CONT_FORWARD, hudconty);
        HUD_KEYS_NEXT_LINE;
      }
    }
    if (pp->controller_bitflags & PCBF_REVERSE) {
      keyp = GetKeyBindingText(ctfREVERSE_THRUSTKEY);

      controlp = GetControllerBindingText(ctfREVERSE_BUTTON);
      if (keyp || controlp) {
        DoEnabledControlsLine(controlp, keyp, TXT_ENABLED_CONT_REVERSE, hudconty);
        HUD_KEYS_NEXT_LINE;
      }
    }
    if (pp->controller_bitflags & PCBF_LEFT) {
      keyp = GetKeyBindingText(ctfLEFT_THRUSTKEY);
      controlp = GetControllerBindingText(ctfLEFT_BUTTON);
      if (keyp || controlp) {
        DoEnabledControlsLine(controlp, keyp, TXT_ENABLED_CONT_SLIDELEFT, hudconty);
        HUD_KEYS_NEXT_LINE;
      }
    }
    if (pp->controller_bitflags & PCBF_RIGHT) {
      keyp = GetKeyBindingText(ctfRIGHT_THRUSTKEY);
      controlp = GetControllerBindingText(ctfRIGHT_BUTTON);
      if (keyp || controlp) {
        DoEnabledControlsLine(controlp, keyp, TXT_ENABLED_CONT_SLIDERIGHT, hudconty);
        HUD_KEYS_NEXT_LINE;
      }
    }
    if (pp->controller_bitflags & PCBF_UP) {
      keyp = GetKeyBindingText(ctfUP_THRUSTKEY);
      controlp = GetControllerBindingText(ctfUP_BUTTON);
      if (keyp || controlp) {
        DoEnabledControlsLine(controlp, keyp, TXT_ENABLED_CONT_SLIDEUP, hudconty);
        HUD_KEYS_NEXT_LINE;
      }
    }
    if (pp->controller_bitflags & PCBF_DOWN) {
      keyp = GetKeyBindingText(ctfDOWN_THRUSTKEY);
      controlp = GetControllerBindingText(ctfDOWN_BUTTON);
      if (keyp || controlp) {
        DoEnabledControlsLine(controlp, keyp, TXT_ENABLED_CONT_SLIDEDOWN, hudconty);
        HUD_KEYS_NEXT_LINE;
      }
    }
    if (pp->controller_bitflags & PCBF_PITCHUP) {
      axis = NULL;
      if ((pp->controller_bitflags & PCBF_PITCHUP) && (pp->controller_bitflags & PCBF_PITCHDOWN)) {
        axis = GetControllerBindingText(ctfPITCH_DOWNAXIS);
      }
      keyp = GetKeyBindingText(ctfPITCH_UPKEY);
      controlp = GetControllerBindingText(ctfPITCH_UPBUTTON);
      if (keyp || controlp || axis) {
        DoEnabledControlsLine(controlp, keyp, TXT_ENABLED_CONT_PITCHUP, hudconty, axis);
        HUD_KEYS_NEXT_LINE;
      }
    }
    if (pp->controller_bitflags & PCBF_PITCHDOWN) {
      axis = NULL;
      if ((pp->controller_bitflags & PCBF_PITCHUP) && (pp->controller_bitflags & PCBF_PITCHDOWN)) {
        axis = GetControllerBindingText(ctfPITCH_DOWNAXIS);
      }
      keyp = GetKeyBindingText(ctfPITCH_DOWNKEY);
      controlp = GetControllerBindingText(ctfPITCH_DOWNBUTTON);
      if (keyp || controlp || axis) {
        DoEnabledControlsLine(controlp, keyp, TXT_ENABLED_CONT_PITCHDOWN, hudconty, axis);
        HUD_KEYS_NEXT_LINE;
      }
    }
    /*
    else if((pp->controller_bitflags & PCBF_HEADINGLEFT) && (pp->controller_bitflags & PCBF_HEADINGRIGHT))
    {
            axis = GetControllerBindingText(ctfHEADING_RIGHTAXIS);
            DoEnabledControlsLine(NULL,NULL,"Pitch",hudconty);
            HUD_KEYS_NEXT_LINE;

    }
    */
    if (pp->controller_bitflags & PCBF_HEADINGLEFT) {
      axis = NULL;
      if ((pp->controller_bitflags & PCBF_HEADINGLEFT) && (pp->controller_bitflags & PCBF_HEADINGRIGHT)) {
        axis = GetControllerBindingText(ctfHEADING_RIGHTAXIS);
      }
      keyp = GetKeyBindingText(ctfHEADING_LEFTKEY);
      controlp = GetControllerBindingText(ctfHEADING_LEFTBUTTON);
      if (keyp || controlp || axis) {
        DoEnabledControlsLine(controlp, keyp, TXT_ENABLED_CONT_HEADLEFT, hudconty, axis);
        HUD_KEYS_NEXT_LINE;
      }
    }
    if (pp->controller_bitflags & PCBF_HEADINGRIGHT) {
      axis = NULL;
      if ((pp->controller_bitflags & PCBF_HEADINGLEFT) && (pp->controller_bitflags & PCBF_HEADINGRIGHT)) {
        axis = GetControllerBindingText(ctfHEADING_RIGHTAXIS);
      }
      keyp = GetKeyBindingText(ctfHEADING_RIGHTKEY);
      controlp = GetControllerBindingText(ctfHEADING_RIGHTBUTTON);
      if (keyp || controlp || axis) {
        DoEnabledControlsLine(controlp, keyp, TXT_ENABLED_CONT_HEADRIGHT, hudconty, axis);
        HUD_KEYS_NEXT_LINE;
      }
    }
    if (pp->controller_bitflags & PCBF_BANKLEFT) {
      axis = NULL;
      if ((pp->controller_bitflags & PCBF_BANKLEFT) && (pp->controller_bitflags & PCBF_BANKLEFT)) {
        axis = GetControllerBindingText(ctfBANK_RIGHTAXIS);
      }
      keyp = GetKeyBindingText(ctfBANK_LEFTKEY);
      controlp = GetControllerBindingText(ctfBANK_LEFTBUTTON);
      if (keyp || controlp || axis) {
        DoEnabledControlsLine(controlp, keyp, TXT_ENABLED_CONT_BANKLEFT, hudconty, axis);
        HUD_KEYS_NEXT_LINE;
      }
    }
    if (pp->controller_bitflags & PCBF_BANKRIGHT) {
      axis = NULL;
      if ((pp->controller_bitflags & PCBF_BANKLEFT) && (pp->controller_bitflags & PCBF_BANKLEFT)) {
        axis = GetControllerBindingText(ctfBANK_RIGHTAXIS);
      }
      keyp = GetKeyBindingText(ctfBANK_RIGHTKEY);
      controlp = GetControllerBindingText(ctfBANK_RIGHTBUTTON);
      if (keyp || controlp || axis) {
        DoEnabledControlsLine(controlp, keyp, TXT_ENABLED_CONT_BANKRIGHT, hudconty, axis);
        HUD_KEYS_NEXT_LINE;
      }
    }
    if (pp->controller_bitflags & PCBF_PRIMARY) {
      keyp = GetKeyBindingText(ctfFIREPRIMARY_KEY);
      controlp = GetControllerBindingText(ctfFIREPRIMARY_BUTTON);
      if (keyp || controlp) {
        DoEnabledControlsLine(controlp, keyp, TXT_ENABLED_CONT_PRIMWEAP, hudconty);
        HUD_KEYS_NEXT_LINE;
      }
    }
    if (pp->controller_bitflags & PCBF_SECONDARY) {
      keyp = GetKeyBindingText(ctfFIRESECONDARY_KEY);
      controlp = GetControllerBindingText(ctfFIRESECONDARY_BUTTON);
      if (keyp || controlp) {
        DoEnabledControlsLine(controlp, keyp, TXT_ENABLED_CONT_SECWEAP, hudconty);
        HUD_KEYS_NEXT_LINE;
      }
    }
    if (pp->controller_bitflags & PCBF_AFTERBURNER) {
      keyp = GetKeyBindingText(ctfAFTERBURN_KEY);
      controlp = GetControllerBindingText(ctfAFTERBURN_BUTTON);
      if (keyp || controlp) {
        DoEnabledControlsLine(controlp, keyp, TXT_ENABLED_CONT_AFTERBURN, hudconty);
        HUD_KEYS_NEXT_LINE;
      }
    }
  }

  //	render hud messages. if in a small hud, don't do it now but inside RenderAuxHUDFrame
  if ((stat_mask & STAT_MESSAGES) && !Small_hud_flag) {
    RenderHUDMessages();
  }
#if 0
	grtext_SetColor(GR_GREEN);
	grtext_SetAlpha(128);
	grtext_SetFont(BIG_BRIEFING_FONT);
	grtext_CenteredPrintf(0,300,"Beta Version");
#endif
  grtext_Flush();
}

//////////////////////////////////////////////////////////////////////////////
//	RETICLE SYSTEM

#include "robotfire.h"

#define RET_IMAGE_WIDTH 32
#define RET_IMAGE_HEIGHT 32

#define MAX_RETICLE_ELEMS 18
#define RET_CPRIMARY 0
#define RET_L1PRIMARY 1
#define RET_R1PRIMARY 2
#define RET_L2PRIMARY 3
#define RET_R2PRIMARY 4
#define RET_CPRIMARY2 5
#define RET_CSECONDARY 8
#define RET_L1SECONDARY 9
#define RET_R1SECONDARY 10
#define RET_L2SECONDARY 11
#define RET_R2SECONDARY 12
#define RET_LGUNSIGHT 16
#define RET_RGUNSIGHT 17

/*
$$TABLE_GAMEFILE "ret_pr0a.ogf"
$$TABLE_GAMEFILE "ret_pr0b.ogf"
$$TABLE_GAMEFILE "ret_pr1b.ogf"
$$TABLE_GAMEFILE "ret_pr2b.ogf"
$$TABLE_GAMEFILE "ret_pr3b.ogf"
$$TABLE_GAMEFILE "ret_pr4b.ogf"
$$TABLE_GAMEFILE "ret_pr13a.ogf"
$$TABLE_GAMEFILE "ret_pr24a.ogf"
$$TABLE_GAMEFILE "ret_se0a.ogf"
$$TABLE_GAMEFILE "ret_se1a.ogf"
$$TABLE_GAMEFILE "ret_se2a.ogf"
$$TABLE_GAMEFILE "ret_se3a.ogf"
$$TABLE_GAMEFILE "ret_se4a.ogf"
$$TABLE_GAMEFILE "ret_se0b.ogf"
$$TABLE_GAMEFILE "ret_se1b.ogf"
$$TABLE_GAMEFILE "ret_se2b.ogf"
$$TABLE_GAMEFILE "ret_se3b.ogf"
$$TABLE_GAMEFILE "ret_se4b.ogf"
$$TABLE_GAMEFILE "ret_lguna.ogf"
$$TABLE_GAMEFILE "ret_rguna.ogf"
$$TABLE_GAMEFILE "ret_pr5a.ogf"
$$TABLE_GAMEFILE "ret_pr5b.ogf"

$$TABLE_GAMEFILE "phx_pr0a.ogf"
$$TABLE_GAMEFILE "phx_pr0b.ogf"
$$TABLE_GAMEFILE "phx_pr1b.ogf"
$$TABLE_GAMEFILE "phx_pr2b.ogf"
$$TABLE_GAMEFILE "phx_pr3b.ogf"
$$TABLE_GAMEFILE "phx_pr4b.ogf"
$$TABLE_GAMEFILE "phx_pr13a.ogf"
$$TABLE_GAMEFILE "phx_pr24a.ogf"
$$TABLE_GAMEFILE "phx_se0a.ogf"
$$TABLE_GAMEFILE "phx_se1a.ogf"
$$TABLE_GAMEFILE "phx_se2a.ogf"
$$TABLE_GAMEFILE "phx_se3a.ogf"
$$TABLE_GAMEFILE "phx_se4a.ogf"
$$TABLE_GAMEFILE "phx_se0b.ogf"
$$TABLE_GAMEFILE "phx_se1b.ogf"
$$TABLE_GAMEFILE "phx_se2b.ogf"
$$TABLE_GAMEFILE "phx_se3b.ogf"
$$TABLE_GAMEFILE "phx_se4b.ogf"
$$TABLE_GAMEFILE "phx_lguna.ogf"
$$TABLE_GAMEFILE "phx_rguna.ogf"
$$TABLE_GAMEFILE "phx_pr5a.ogf"
$$TABLE_GAMEFILE "phx_pr5b.ogf"

$$TABLE_GAMEFILE "mag_pr0a.ogf"
$$TABLE_GAMEFILE "mag_pr0b.ogf"
$$TABLE_GAMEFILE "mag_pr1b.ogf"
$$TABLE_GAMEFILE "mag_pr2b.ogf"
$$TABLE_GAMEFILE "mag_pr3b.ogf"
$$TABLE_GAMEFILE "mag_pr4b.ogf"
$$TABLE_GAMEFILE "mag_pr13a.ogf"
$$TABLE_GAMEFILE "mag_pr24a.ogf"
$$TABLE_GAMEFILE "mag_se0a.ogf"
$$TABLE_GAMEFILE "mag_se1a.ogf"
$$TABLE_GAMEFILE "mag_se2a.ogf"
$$TABLE_GAMEFILE "mag_se3a.ogf"
$$TABLE_GAMEFILE "mag_se4a.ogf"
$$TABLE_GAMEFILE "mag_se0b.ogf"
$$TABLE_GAMEFILE "mag_se1b.ogf"
$$TABLE_GAMEFILE "mag_se2b.ogf"
$$TABLE_GAMEFILE "mag_se3b.ogf"
$$TABLE_GAMEFILE "mag_se4b.ogf"
$$TABLE_GAMEFILE "mag_lguna.ogf"
$$TABLE_GAMEFILE "mag_rguna.ogf"
$$TABLE_GAMEFILE "mag_pr5a.ogf"
$$TABLE_GAMEFILE "mag_pr5b.ogf"
*/

//	this should map to the reticle element defines
//		column 0 = off bitmap
//		column 1 = on bitmap (if any).
//		column 2 = left, center or right aligned bitmap.
const char *Reticle_image_names[MAX_RETICLE_ELEMS][3] = {
    {"_pr0a.ogf", "_pr0b.ogf", "c"},
    {"_pr13a.ogf", "_pr1b.ogf", "l"}, // gp1
    {"_pr24a.ogf", "_pr2b.ogf", "r"}, // gp2
    {"_pr13a.ogf", "_pr3b.ogf", "l"}, // since off version is same as gp1
    {"_pr24a.ogf", "_pr4b.ogf", "r"}, // since off version is same as gp2
    {"_pr5a.ogf", "_pr5b.ogf", "c"},  // center gunpoint version of gp0 (ammo based, single gp)
    {NULL, NULL, "l"},
    {NULL, NULL, "l"},
    {"_se0a.ogf", "_se0b.ogf", "c"},
    {"_se1a.ogf", "_se1b.ogf", "l"},
    {"_se2a.ogf", "_se2b.ogf", "r"},
    {"_se3a.ogf", "_se3b.ogf", "l"},
    {"_se4a.ogf", "_se4b.ogf", "r"},
    {NULL, NULL, "l"},
    {NULL, NULL, "l"},
    {NULL, NULL, "l"},
    {"_lguna.ogf", NULL, "l"},
    {"_rguna.ogf", NULL, "r"}};

//	reticle slot element array
static struct {
  int bmp_off;
  int bmp_on;
  char align; //	'l', 'r', or 'c'  (clever, huh?)
} Reticle_elem_array[MAX_RETICLE_ELEMS];

const int Ret_prim_wb[MAX_WB_GUNPOINTS + 1] = {
    RET_CPRIMARY, // reserved for NON mass driver
    RET_R1PRIMARY, RET_L1PRIMARY, RET_R2PRIMARY, RET_L2PRIMARY, -1, -1, -1,
    RET_CPRIMARY2 // reserved for mass driver slot weapons.
};

const int Ret_sec_wb[MAX_WB_GUNPOINTS + 1] = {
    RET_CSECONDARY, RET_R1SECONDARY, RET_L1SECONDARY, RET_R2SECONDARY, RET_L2SECONDARY, -1, -1, -1, -1};

#define RETMASK_FLAG_AUXPRIMARY0 (1 << 8) // matches 9th bit (bit 8) of reticle mask

static uint16_t Ret_prim_mask = 0;
static uint16_t Ret_sec_mask = 0;

//	Initializes Reticle on Hud.  Usually called when weapon changes.
void InitReticle(int primary_slots, int secondary_slots) {
  int i;

  for (i = 0; i < MAX_RETICLE_ELEMS; i++) {
    char filename[PSFILENAME_LEN + 1];

    if (Reticle_image_names[i][0] && primary_slots >= 0) {
      snprintf(filename, sizeof(filename), "%s%s", Reticle_prefix, Reticle_image_names[i][0]);
      Reticle_elem_array[i].bmp_off = bm_AllocLoadFileBitmap(IGNORE_TABLE(filename), 0);
      if (Reticle_elem_array[i].bmp_off <= BAD_BITMAP_HANDLE) {
        Reticle_elem_array[i].bmp_off = -1;
        mprintf(0, "Unable to load %s reticle image.\n", filename);
      }
    } else {
      Reticle_elem_array[i].bmp_off = -1;
    }

    if (Reticle_image_names[i][1] && primary_slots >= 0) {
      snprintf(filename, sizeof(filename), "%s%s", Reticle_prefix, Reticle_image_names[i][1]);
      Reticle_elem_array[i].bmp_on = bm_AllocLoadFileBitmap(IGNORE_TABLE(filename), 0);
      if (Reticle_elem_array[i].bmp_on <= BAD_BITMAP_HANDLE) {
        mprintf(0, "Unable to load %s reticle image.\n", filename);
        Reticle_elem_array[i].bmp_on = -1;
      }
    } else {
      Reticle_elem_array[i].bmp_on = -1;
    }

    Reticle_elem_array[i].align = Reticle_image_names[i][2][0];
  }
}

//	frees up bitmaps associated with reticle.
void FreeReticle() {
  int i;

  for (i = 0; i < MAX_RETICLE_ELEMS; i++) {
    if (Reticle_elem_array[i].bmp_off > BAD_BITMAP_HANDLE)
      bm_FreeBitmap(Reticle_elem_array[i].bmp_off);
    Reticle_elem_array[i].bmp_off = -1;
    if (Reticle_elem_array[i].bmp_on > BAD_BITMAP_HANDLE)
      bm_FreeBitmap(Reticle_elem_array[i].bmp_on);
    Reticle_elem_array[i].bmp_on = -1;
  }
}

//	resets reticle based off current player object.
//	and the ship's weapon configuration
void ResetReticle() {
  player *player = &Players[Player_num];
  object *pobj = &Objects[player->objnum];

  ASSERT(player->objnum >= 0);

  // Make sure we're not resetting a non-existent object
  if (!pobj || (pobj->type != OBJ_PLAYER && pobj->type != OBJ_GHOST && pobj->type != OBJ_OBSERVER))
    return;

  poly_model *pm = &Poly_models[Objects[player->objnum].rtype.pobj_info.model_num];
  otype_wb_info *prim_wb = &Ships[player->ship_index].static_wb[player->weapon[PW_PRIMARY].index];
  otype_wb_info *sec_wb = &Ships[player->ship_index].static_wb[player->weapon[PW_SECONDARY].index];
  dynamic_wb_info *prim_dyn_wb = &pobj->dynamic_wb[player->weapon[PW_PRIMARY].index];

  int i, j;

  //	assign reticle elements to the Ret_prim_xx array.
  //	create battery mask
  Ret_prim_mask = 0;

  // iterate through all battery masks to determine which gun points occupy the primary weapon
  // on the player ship!
  for (j = 0; j < prim_wb->num_masks; j++) {
    for (i = 0; i < pm->poly_wb[0].num_gps; i++) {
      if (prim_wb->gp_fire_masks[j] & (1 << i)) {
        Ret_prim_mask |= (1 << i);
      } else if ((prim_dyn_wb->flags & DWBF_QUAD) && (prim_wb->gp_quad_fire_mask & (1 << i))) {
        Ret_prim_mask |= (1 << i);
      }
    }
  }

  if (player->weapon[PW_PRIMARY].index == MASSDRIVER_INDEX && (Ret_prim_mask & (1 << 0))) {
    // special hack for mass driver weapons
    Ret_prim_mask &= (~(1 << 0));
    Ret_prim_mask |= RETMASK_FLAG_AUXPRIMARY0;
  }

  // iterate through all battery masks to determine which gun points occupy the secondary weapon
  // on the player ship!
  Ret_sec_mask = 0;

  for (j = 0; j < sec_wb->num_masks; j++) {
    for (i = 0; i < pm->poly_wb[0].num_gps; i++) {
      if (sec_wb->gp_fire_masks[j] & (1 << i))
        Ret_sec_mask |= (1 << i);
    }
  }
}

//	creates the reticle display bitmap mask to be used by the reticle renderer.
static inline uint16_t reticle_mask(object *pobj, otype_wb_info *static_wb, int wb_index) {
  poly_model *pm = &Poly_models[pobj->rtype.pobj_info.model_num];
  dynamic_wb_info *dyn_wb = &pobj->dynamic_wb[wb_index];
  unsigned mask = 0;
  int i;

  // determine if weapon battery is charged, if not, then return 0, indicating no 'on' weapon baterries
  if (!WBIsBatteryReady(pobj, static_wb, wb_index))
    return 0;

  if (static_wb->ammo_usage) {
    if (Players[pobj->id].weapon_ammo[wb_index] == 0)
      return 0;
  } else if (static_wb->energy_usage) {
    if (Players[pobj->id].energy < static_wb->energy_usage)
      return 0;
  }

  //	create battery mask
  for (i = 0; i < pm->poly_wb[0].num_gps; i++) {
    if (static_wb->gp_fire_masks[dyn_wb->cur_firing_mask] & (1 << i)) {
      mask |= (1 << i);
    } else if ((dyn_wb->flags & DWBF_QUAD) && (static_wb->gp_quad_fire_mask & (1 << i))) {
      mask |= (1 << i);
    }
  }

  if (wb_index == MASSDRIVER_INDEX && (mask & (1 << 0))) {
    // special hack for mass driver weapons
    mask &= (~(1 << 0));
    mask |= RETMASK_FLAG_AUXPRIMARY0;
  }

  return mask;
}

static inline void draw_reticle_sub(int cx, int cy, int rw, int rh, uint16_t on_mask, uint16_t gp_mask, const int *wb_elem_array) {
  int i, x, y;
  int bmp_handle;
  char align;

  for (i = 0; i < (MAX_WB_GUNPOINTS + 1); i++) {
    if (gp_mask & (1 << i)) {
      // we can definitely draw a reticle image, which one is the question now.
      ASSERT(wb_elem_array[i] > -1);
      if (on_mask & (1 << i))
        bmp_handle = Reticle_elem_array[wb_elem_array[i]].bmp_on;
      else
        bmp_handle = Reticle_elem_array[wb_elem_array[i]].bmp_off;
      align = Reticle_elem_array[wb_elem_array[i]].align;

      if (bmp_handle > -1) {
        // draw on image based off of alignment to cx,cy and 'align'
        switch (align) {
        case 'l':
          x = cx - rw;
          y = cy - rh / 2;
          break;
        case 'r':
          x = cx;
          y = cy - rh / 2;
          break;
        case 'c':
          x = cx - rw / 2;
          y = cy - rh / 2;
          break;
        default:
          x = cx;
          y = cy;
          Int3();
        }

        RenderHUDQuad(x, y, rw, rh, 0, 0, 1, 1, bmp_handle, 192);
      }
    }
  }
}

//	renders the reticle
void RenderReticle() {
  static uint16_t primary_index_last_frame = 0xffff;
  static bool quad_primary_last_frame = false;
  player *player = &Players[Player_num];
  object *pobj = &Objects[player->objnum];
  ship *ship = &Ships[player->ship_index];
  player_weapon *prim_pw = &player->weapon[PW_PRIMARY];
  player_weapon *sec_pw = &player->weapon[PW_SECONDARY];
  int prim_wb_index = prim_pw->index;
  int sec_wb_index = sec_pw->index;
  otype_wb_info *prim_wb = &ship->static_wb[prim_wb_index];
  otype_wb_info *sec_wb = &ship->static_wb[sec_wb_index];
  dynamic_wb_info *prim_dyn_wb = &pobj->dynamic_wb[prim_wb_index];

  int cx = Ret_x_off + (FIXED_SCREEN_WIDTH >> 1);
  int cy = Ret_y_off + (FIXED_SCREEN_HEIGHT >> 1) + 6;
  int rw = RET_IMAGE_WIDTH;
  int rh = RET_IMAGE_HEIGHT;

  //	quad weapon check hack (any weapon states that change should be noted here.)
  if (prim_dyn_wb->flags & DWBF_QUAD) {
    if (!quad_primary_last_frame || primary_index_last_frame != prim_wb_index) {
      ResetReticle();
    }
    quad_primary_last_frame = true;
  } else {
    if (quad_primary_last_frame) {
      ResetReticle();
    }
    quad_primary_last_frame = false;
  }

  primary_index_last_frame = prim_wb_index;

  //	determine which primary batteries are open.
  draw_reticle_sub(cx, cy, rw, rh, reticle_mask(pobj, prim_wb, prim_wb_index), Ret_prim_mask, Ret_prim_wb);
  draw_reticle_sub(cx, cy, rw, rh, reticle_mask(pobj, sec_wb, sec_wb_index), Ret_sec_mask, Ret_sec_wb);

  if (Reticle_elem_array[RET_LGUNSIGHT].bmp_off > -1)
    RenderHUDQuad(cx - rw, cy - rh / 2, rw, rh, 0, 0, 1, 1, Reticle_elem_array[RET_LGUNSIGHT].bmp_off, 192);

  if (Reticle_elem_array[RET_RGUNSIGHT].bmp_off > -1)
    RenderHUDQuad(cx, cy - rh / 2, rw, rh, 0, 0, 1, 1, Reticle_elem_array[RET_RGUNSIGHT].bmp_off, 192);
}

//	renders missile reticle
void RenderMissileReticle() {
  //	Crosshair reticle
  int cx = Game_window_w / 2;
  int cy = Game_window_h / 2;

  RenderHUDTextFlags(HUDTEXT_CENTERED, GR_RED, HUD_ALPHA, 0, 10, cy - 50, TXT_HUD_GUIDED);
  grtext_Flush();

  rend_SetZBufferState(0);
  rend_SetFlatColor(GR_GREEN);

  rend_DrawLine(cx - 6, cy, cx + 6, cy);
  rend_DrawLine(cx, cy - 6, cx, cy + 6);
  rend_SetZBufferState(1);
}

//	renders missile reticle
void RenderZoomReticle() {
  //	Crosshair reticle
  int cx = Game_window_w / 2;
  int cy = Game_window_h / 2;
  int text_height = grfont_GetHeight(HUD_FONT);
  char str[255];

  RenderHUDTextFlags(HUDTEXT_CENTERED, GR_RED, HUD_ALPHA, 0, 10, cy - 50, TXT_HUD_ZOOM);

  snprintf(str, sizeof(str), TXT_HUD_ZOOM_UNITS, Players[Player_num].zoom_distance);

  RenderHUDTextFlags(HUDTEXT_CENTERED, GR_RED, HUD_ALPHA, 0, 10, cy - 50 + text_height, str);
  grtext_Flush();

  rend_SetZBufferState(0);

  if (Players[Player_num].flags & PLAYER_FLAGS_BULLSEYE)
    rend_SetFlatColor(GR_RED);
  else
    rend_SetFlatColor(GR_GREEN);

  rend_DrawLine(cx - 8, cy, cx + 8, cy);
  rend_DrawLine(cx, cy - 8, cx, cy + 8);
}

/*
//	HUD FILE FUNCTIONS
#define HUDCMD_NUM			22
#define HUDCMD_TYPE			0
#define HUDCMD_RED			1
#define HUDCMD_GREEN			2
#define HUDCMD_BLUE			3
#define HUDCMD_X				4
#define HUDCMD_Y				5
#define HUDCMD_TX				6
#define HUDCMD_TY				7
#define HUDCMD_CREATE		8
#define HUDCMD_SAT			9
#define HUDCMD_SPECIAL		10
#define HUDCMD_CKPTMODEL	11
#define HUDCMD_AFTERBURN	12
#define HUDCMD_ENERGY		13
#define HUDCMD_INVPULSE		14
#define HUDCMD_SHIP			15
#define HUDCMD_SHIELDIMG0	16
#define HUDCMD_SHIELDIMG1	17
#define HUDCMD_SHIELDIMG2	18
#define HUDCMD_SHIELDIMG3	19
#define HUDCMD_SHIELDIMG4	20
#define HUDCMD_ALPHA			21

const char *HUDCommands[HUDCMD_NUM] = {
        "type",
        "r",
        "g",
        "b",
        "x",
        "y",
        "tx",
        "ty",
        "create",
        "sat",
        "special",
        "ckptmodel",
        "afterburnimg",
        "energyimg",
        "invpulseimg",
        "shipimg",
        "shieldimg0",
        "shieldimg1",
        "shieldimg2",
        "shieldimg3",
        "shieldimg4",
        "alpha"
};


int HUDLex(const char *command)
{
        for (int i = 0; i < HUDCMD_NUM; i++)
                if (strcmp(HUDCommands[i], command) == 0)
                        return i;

        return INFFILE_ERROR;
}


// takes a filename containing oms data.
void LoadHudConfig(const char *filename, bool (*fn)(const char*, const char *, void*), void *ext_data)
{
        InfFile inf;
        tHUDItem hud_item;
        char operand[INFFILE_LINELEN];			// operand
        bool txpos = false, typos = false;
        uint8_t r=GR_COLOR_RED(HUD_COLOR);
        uint8_t g=GR_COLOR_GREEN(HUD_COLOR);
        uint8_t b=GR_COLOR_BLUE(HUD_COLOR);

//	start over.
        ResetHud();

        memset(&hud_item, 0, sizeof(hud_item));
        hud_item.alpha = HUD_ALPHA;

//	open file
        if (!inf.Open(file, "[hud file]", HUDLex)) {
                Warning("Unable to find requested theme %s or bad file.\n", file);
                return false;
        }

//	check if valid cockpit file
        while (inf.ReadLine())
        {
                int cmd;

                while ((cmd = inf.ParseLine(operand, INFFILE_LINELEN)) > INFFILE_ERROR)
                {
                        switch (cmd)
                        {
                        case HUDCMD_TYPE:	hud_item.type = atoi(operand); break;
                        case HUDCMD_RED: r=(uint8_t)atoi(operand); break;
                        case HUDCMD_GREEN: g=(uint8_t)atoi(operand); break;
                        case HUDCMD_BLUE:	b=(uint8_t)atoi(operand);	break;
                        case HUDCMD_X:	hud_item.x = atoi(operand); break;
                        case HUDCMD_Y: hud_item.y = atoi(operand); break;
                        case HUDCMD_TX: hud_item.tx = atoi(operand); txpos = true; break;
                        case HUDCMD_TY: hud_item.ty = atoi(operand); typos = true; break;
                        case HUDCMD_SAT: hud_item.saturation_count = atoi(operand); break;
                        case HUDCMD_SPECIAL: hud_item.stat |= STAT_SPECIAL; break;
                        case HUDCMD_ALPHA: hud_item.alpha = atoi(operand); break;
                        case HUDCMD_CREATE:
                                hud_item.color = GR_RGB(r,g,b);
                                if (!txpos) hud_item.tx = hud_item.x;
                                if (!typos) hud_item.ty = hud_item.y;
                                hud_item.render_fn = HudDisplayRouter;
                                AddHudItem(&hud_item);

                                memset(&hud_item, 0, sizeof(hud_item));
                                hud_item.alpha = HUD_ALPHA;
                                r=GR_COLOR_RED(HUD_COLOR);
                                g=GR_COLOR_GREEN(HUD_COLOR);
                                b=GR_COLOR_BLUE(HUD_COLOR);
                                txpos = false;
                                typos = false;
                                break;
                        case HUDCMD_AFTERBURN:
                        case HUDCMD_ENERGY:
                        case HUDCMD_INVPULSE:
                        case HUDCMD_SHIP:
                        case HUDCMD_SHIELDIMG0:
                        case HUDCMD_SHIELDIMG1:
                        case HUDCMD_SHIELDIMG2:
                        case HUDCMD_SHIELDIMG3:
                        case HUDCMD_SHIELDIMG4:
                        case HUDCMD_CKPTMODEL:
                        default:
                                if (fn && !(*fn)(HUDCommands[cmd], operand, ext_data)) {
                                        goto force_error;
                                }
                        }
                }

force_error:
                if (cmd == INFFILE_ERROR)
                        Warning("Error in hud file %s line %d.\n", file, inf.line());
        }

        inf.Close();

        return true;
}

*/
