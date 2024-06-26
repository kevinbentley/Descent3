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

 * $Logfile: /DescentIII/Main/game.cpp $
 * $Revision: 190 $
 * $Date: 9/14/01 4:47p $
 * $Author: Matt $
 *
 * Game management
 *
 * $Log: /DescentIII/Main/game.cpp $
 *
 * 190   9/14/01 4:47p Matt
 * Cleaned up problems when screen bit depth set to 32.
 *
 * 189   10/21/99 3:42p Matt
 * Mac merge
 *
 * 188   10/14/99 1:08p Chris
 * Added another custom bounce force field texture slot
 *
 * 187   10/13/99 2:19p Chris
 * Added the ability to disable wind for powerups on a level
 *
 * 186   10/13/99 10:41a Chris
 * Added 'special forcefields' that have custom bounce factors
 *
 * 185   10/08/99 4:28p Chris
 * Added the forcefield and glass breaking override options
 *
 * 184   8/11/99 5:32p Jeff
 * changes to fix addon tablefile support so it works correctly
 *
 * 183   5/07/99 7:22p Jason
 * changes for cards with low videomemory
 *
 * 181   5/03/99 2:07a Samir
 * make sure Frametime is not 0 in GetFPS.
 *
 * 180   5/02/99 11:04p Matt
 * Cleaned up HUD font code, now that we have only two sizes of HUD fonts.
 *
 * 179   5/01/99 1:58a Samir
 * game window width and height get properly saved since we always used to
 * reset the width and height whenever SM_GAME was passed to
 * SetScreenMode.  The only time it should change is when we change
 * resolutions.
 *
 * 178   4/27/99 7:02p Samir
 * took out annoying mprintf.
 *
 * 177   4/27/99 5:18p Samir
 * properly handle switch into cinematic resolution if previous screen
 * mode was SM_NULL.
 *
 * 176   4/26/99 4:32p Samir
 * suspend controls when leaving game.
 *
 * 175   4/26/99 11:33a Samir
 * switch resolution of screen for cinematic under glide in release only.
 *
 * 174   4/23/99 10:22p Kevin
 * Fixed savegame doorways bug!
 *
 * 173   4/14/99 2:50a Jeff
 * fixed some case mismatched #includes
 *
 * 172   4/09/99 7:04p Jason
 * changed some texture defines
 *
 * 171   4/08/99 5:59p Jason
 * check for 16bit mode when initializing renderer
 *
 * 170   4/05/99 5:25p Samir
 * Glide exempt from cinematics resolution switch.
 *
 * 169   4/02/99 11:32p Jeff
 * able to turn off IGC in debug mode.  Better handling of cinematics
 * quick exit if playing via alt-p
 *
 * 168   4/02/99 3:03p Samir
 * shut down renderer for full screen cinematics.
 *
 * 167   3/29/99 7:29p Jason
 * made renderer handle default resolution more gracefully
 *
 * 166   3/19/99 12:54p Jeff
 * base support for requesting the number of teams for a multiplayer game
 *
 * 165   3/09/99 12:04p Samir
 * resize screen when changing resolutions in game to full screen.
 *
 * 164   3/05/99 5:43p Luke
 * Samir: use rend width instead of scr_width to determine font
 * resolution.
 *
 * 163   3/02/99 6:25p Samir
 * more hires font madness.
 *
 * 162   2/28/99 3:23a Samir
 * added superhires fonts.
 *
 * 161   2/25/99 8:54p Jeff
 * Inventory supports level change persistant items.  Inventory supports
 * time-out objects.  Inventory Reset changed (takes a level of reset
 * now).  Quad lasers stay across level change (single player).  Guidebot
 * bug fixed (now back in ship on level start).  Quads time out when
 * spewed.  Invulnerability and cloak powerups no longer use game
 * event/callbacks, so they can be saved in game saves (moved to
 * MakePlayerInvulnerable and MakeObjectInvisible)
 *
 * 160   2/18/99 11:54a Kevin
 * made screenshot filename always use 3 digits
 *
 * 159   2/17/99 7:05p Kevin
 * OEM build setup
 *
 * 158   2/17/99 2:45p Kevin
 * Adde movie making capabilities to the demo playback system
 *
 * 157   2/16/99 12:00p Samir
 * added new video resolution swtich test.
 *
 * 156   2/15/99 7:48p Jeff
 * new pilot file class and read/write system checked in...should be more
 * robust than old
 *
 * 155   2/15/99 3:10p Kevin
 * fixed dumb bug with shutting down renderer
 *
 * 154   2/12/99 6:46p Jeff
 * fixed start frame/end frame stack bug
 *
 * 153   2/11/99 1:21a Jeff
 * made function to switch a player into AI mode, converted code that did
 * this to call this function.
 *
 * 152   2/10/99 2:41p Chris
 * Added debug info
 *
 * 151   2/09/99 9:58a Chris
 * Massive BOA update  :)  Terrain happy now.  Vis happy now.  Sound happy
 * now.
 *
 * 150   2/08/99 7:50p Jeff
 * made StartFrame/EndFrame stack based...no longer have to worry about
 * preserving current frame settings to restore
 *
 * 149   2/08/99 12:03a Jeff
 * added a function to get the current StartFrame parameters (from last
 * call to StartFrame)
 *
 * 148   2/04/99 12:35p Jeff
 * moved cinematic stop to when level is ending, so it will catch it
 * before dlls unloaded
 *
 * 147   2/04/99 11:28a Jeff
 * shutdown cinematics when exiting the game
 *
 * 146   2/01/99 12:57p Jeff
 * fixed bug with turning off OF_DESTROYABLE flag in StartEndLevelSequence
 * (changing wrong flag)
 *
 * 145   1/31/99 9:05p Jeff
 * removed old boss introduction cinematics...now done in new ingame
 * cinematics system
 *
 * 144   1/31/99 7:25p Matt
 * Renamed a bunch of functions to have HUD capitalized
 *
 * 143   1/29/99 6:29p Samir
 * implemented hud scrollback for hud messages.
 *
 * 142   1/29/99 2:08p Jeff
 * localization
 *
 * 141   1/29/99 12:47p Matt
 * Rewrote the doorway system
 *
 * 140   1/27/99 2:58p Jason
 * fixed center small view
 *
 * 139   1/24/99 3:54a Jeff
 * fixed boss-intro cinematic...pretty much complete (besides for the hack
 * to get it to face the target)
 *
 * 138   1/23/99 6:24p Chris
 * Max delta velocity!!!!!!!!!!
 *
 * 137   1/23/99 3:01a Jeff
 * tried to get boss intro stuff working
 *
 * 136   1/22/99 8:44p Chris
 * A few small tweaks to the endlevel path stuff
 *
 * 135   1/22/99 6:53p Chris
 * Fixed LoadandBind Aux notify problems, fixed static path problems,
 * fixed AIF_FORCE_AWARE Problems, improved path code
 *
 * 134   1/22/99 3:59p Jason
 * added 256x256 textures to help with terrain skies
 *
 * 133   1/20/99 3:45a Jeff
 * updated Boss Introduction sequence functions, all but path following is
 * complete
 *
 * 132   1/15/99 7:52p Chris
 * Updated ObjSetPos() to include a f_update_attach_children flag
 *
 * 131   1/10/99 10:23p Jeff
 * added initial start/end boss intro function
 *
 * 130   1/08/99 2:55p Samir
 * Ripped out OSIRIS1.
 *
 * 129   12/30/98 6:51p Matt
 * Fixed compile warnings
 *
 * 128   12/29/98 4:30p Jason
 * added add-on data functionality
 *
 * 127   12/15/98 10:00a Chris
 *
 * 126   12/14/98 1:07p Chris
 * Allowed OSIRIS to change AI types
 *
 * 125   10/23/98 12:51p Samir
 * took out unnecessary calle to SetHudMode.
 *
 * 124   10/22/98 2:40p Samir
 * redid HUD sequencing so multiplayer hud stuff works.
 *
 * 123   10/21/98 7:04p Samir
 * moved init hud and cockpit to init level
 *
 * 122   10/21/98 5:29p Samir
 * set mask controllers at start of game.
 *
 * 121   10/21/98 11:14a Samir
 * added generic code to skip rendering while in game controller config or
 * telcom.
 *
 * 120   10/20/98 7:36p Matt
 * At the start of the endlevel sequence, move the player to the first
 * node on the path.
 *
 * 119   10/19/98 2:50p Samir
 * added function to cleanup ui windows.
 *
 * 118   10/17/98 2:46p Jason
 * better error string reports
 *
 * 117   10/16/98 11:55a Kevin
 * Made dlls loadable in a hog
 *
 * 116   10/15/98 10:42a Matt
 * Changed _DEBUG/RELEASE inconsistancy with slew
 *
 * 115   10/14/98 7:30p Matt
 * Changed StartEndlevelSeqence to take a time parameter for how long to
 * delay before ending the level.
 *
 * 114   10/14/98 6:39p Samir
 * save screen size for game.
 *
 * 113   10/14/98 4:37p Chris
 * Improved endlevel path following again
 *
 * 112   10/14/98 4:18p Chris
 * Improved end level path stuff
 *
 * 111   10/14/98 12:44a Matt
 * Cleaned up endlevel sequence system (though it still doesn't work --
 * ChrisP is going to look at the path-following).
 *
 * 110   10/11/98 5:50p Jeff
 * changed warning/error when the multiplayer dll can't be loaded
 *
 * 109   10/11/98 3:03a Jeff
 * made the game handle the Multiplayer D3M file refusing to load (because
 * it's init failed for some reason)
 *
 * 108   10/08/98 7:28p Samir
 * revamped sequencing.
 *
 * 107   10/08/98 3:36p Jason
 * fixes for the demo
 *
 * 107   10/08/98 3:36p Jason
 * fixes for the demo
 *
 * 106   10/02/98 12:07p Jason
 * fixed buggy resolution switching
 *
 * 105   9/22/98 6:48p Matt
 * Stop and Start time around screenshot
 *
 * 104   9/22/98 3:55p Samir
 * moved simple callback to NewUI system.
 *
 * 103   9/22/98 12:02p Matt
 * Fixed compile warnings
 *
 * 102   9/18/98 1:27p Jason
 * cleaned up renderer initting
 *
 * 101   9/14/98 6:28p Jason
 * first pass at getting dedicated server working
 *
 * 100   9/11/98 6:40p Jason
 * added smoke puffs
 *
 * 99    9/01/98 4:11p Samir
 * moved screenshot code from gameloop to game.cpp
 *
 * 98    8/18/98 1:00a Samir
 * use current pilot ship for cockpit.
 *
 * 97    7/21/98 6:50p Jeff
 * don't initialize or close renderer if set screen mode hasn't been
 * called yet in debug handlers.
 *
 * 96    7/16/98 12:06p Jason
 * added special flags to room structure
 *
 * 95    6/29/98 6:42p Samir
 * Properly handle controller pausing and resumption.
 *
 * 94    6/22/98 12:00p Chris
 * Working on sound system to make it in a nice shape.
 *
 * 93    6/16/98 10:38a Jeff
 * localization, strings pulled out to stringtable.h and d3.str
 *
 * 92    6/11/98 1:58p Jeff
 * ignore last check in comment...it should say ".d3m files renamed to
 * .dll files"
 *
 * 91    6/11/98 1:57p Jeff
 * updated for PLR so that phantom players show
 *
 * 90    5/26/98 10:51p Samir
 * set hud mode to current hud mode when setting game screen mode.
 *
 * 89    5/15/98 5:35p Samir
 * allow usage of hires and lores fonts.
 *
 * 88    5/11/98 4:40p Chris
 * AI info is now a malloc'ed pointer
 *
 * 87    5/11/98 2:47p Samir
 * reset res change flag.
 *
 * 86    5/08/98 12:55p Samir
 * improved ui handling when switch screen modes.
 *
 * 85    5/06/98 4:33p Samir
 * set screen mode for game changes to various resolutions.
 *
 * 84    5/05/98 5:17p Samir
 * set screen mode is a bit more efficient when initializing renderer and
 * setting screen sizes.
 *
 * 83    5/05/98 3:02p Jason
 * attempting to add different screen resolutions
 *
 * 82    4/24/98 1:53a Samir
 * took care of a lot of scripting memory leaks.
 *
 * 81    4/16/98 6:51a Samir
 * moved cockpit init/free code to once per game instead of level.
 *
 * 80    4/15/98 11:34a Samir
 * no more PostLevelResults.
 *
 * 79    4/14/98 9:18p Samir
 * redid post level results.
 *
 * 78    4/02/98 7:59p Samir
 * Created a simple clear screen UI callback.
 *
 * 77    4/02/98 11:11a Samir
 * better managed SetScreenMode.
 *
 * 76    3/27/98 4:01p Jason
 * added external game dlls
 *
 * 75    3/19/98 9:19p Samir
 * removed dependency of hud.h on game.h.
 *
 * 74    3/18/98 5:45p Jason
 * more multiplayer script integration
 *
 * 73    3/17/98 2:40p Samir
 * reorg of hud/gauge system.
 *
 * 72    3/13/98 6:55p Chris
 * DEBUG to _DEBUG
 *
 * 71    3/13/98 5:21p Craig
 *
 * 70    3/13/98 1:28p Jason
 * fixed UseHardware variable bug
 *
 * 69    3/13/98 1:22p Jason
 * Moved UseHardware flag to the renderer lib where it belongs
 *
 * 68    3/13/98 12:09p Samir
 * made changes to reflect new cockpit.cpp and cockpit.h
 *
 * 67    3/11/98 4:58p Chris
 * Changed Show_game_sphere to 3 types
 *
 * 66    3/10/98 5:15p Chris
 * DEL+B shows the bounding-sphere of an object
 *
 * 65    2/25/98 2:05p Jason
 * did FOV and object visibility changes
 *
 * 64    2/18/98 1:11a Samir
 * Some game window mess.
 *
 * 63    2/14/98 10:48p Jason
 * got preferred rendering working
 *
 * 61    2/13/98 10:57a Samir
 * Changed some gamescript initialization.
 *
 * 60    2/12/98 5:08p Matt
 * Reset cockpit mode when starting a level.  Unfortunately, this involved
 * some semi-major mucking with game sequencing.
 *
 * 59    2/12/98 4:28p Matt
 * Added function to start endlevel in-game "cutscene"
 *
 * 58    2/11/98 5:55p Samir
 * Now InitD3XDebug and CloseD3XDebug are called when you enter and leave
 * the game.  This as well as ui_Init and ui_Close
 *
 * 57    2/11/98 4:35p Samir
 * SetGameMode fully implented takes a script.
 *
 * 56    2/10/98 11:28a Samir
 * Added gamemode info support
 *
 * 55    2/10/98 10:21a Matt
 * Added ifdef around some editor code
 *
 * 54    2/09/98 3:20p Matt
 * Added missile camera system
 *
 * 53    2/08/98 5:01p Samir
 * New game sequencing changes.
 *
 * 52    2/06/98 6:07p Jason
 * made multiplayer objects get deleted in single-player mode
 *
 * 51    2/03/98 6:42p Samir
 * SetScreenMode cleaner.
 *
 * 50    2/02/98 7:34p Samir
 * Moved D3X Initialization to PlayGame.
 *
 * 49    1/28/98 3:24p Samir
 * Put error message if SetScreenMode fails!.
 *
 * 48    1/28/98 12:00p Jason
 * more changes for multiplayer
 *
 * 47    1/26/98 5:27p Chris
 * The sound system was not getting re-initialized between levels
 *
 * 46    1/22/98 7:48p Samir
 * Clear out Gametime FIRST in InitThisLevel.
 *
 * 45    1/21/98 1:11p Jason
 * incremental checkin for multiplayer
 *
 * 44    1/20/98 7:24p Samir
 * Reset events at start of level.
 *
 * 43    1/20/98 6:01p Jason
 * first pass at getting multiplayer deaths working
 *
 * 42    1/18/98 4:22p Samir
 * Changed some UI initialization stuff.
 *
 * 41    1/10/98 2:55p Jason
 * changed some things for multiplayer
 *
 * 40    1/08/98 12:15p Samir
 * Initialize UI when screen mode is set.
 *
 * 39    1/06/98 2:44p Jason
 * another pass for multiplayer
 *
 * 38    1/05/98 4:36p Chris
 * Added working ambient sounds to objects.
 *
 * 37    1/05/98 10:34a Samir
 * Some more StartFrame nonsense.
 *
 * 36    12/29/97 5:44p Samir
 * Took out references to grViewport and old 2d library.
 *
 * 35    12/19/97 12:27p Samir
 * Commented out post level results screen.
 *
 * 34    12/18/97 3:49p Jason
 * a new first pass at networking!
 *
 * 33    11/12/97 5:48p Chris
 * Added sizeof() elements in SoarInit
 *
 * 32    11/10/97 12:35p Samir
 * Added SM_CINEMATIC screen mode, and make sure we don't reinit renderer
 * for hardware rendering between two screen modes that use hardware.
 *
 * 31    10/28/97 6:36p Samir
 * Moved SetCockpitMode to gauges.cpp
 *
 * 30    10/28/97 12:46p Samir
 * Moved SetCockpitMode to new gauges.cpp
 *
 * 29    10/21/97 3:17p Samir
 * Letterbox now less obvious.
 *
 * 28    10/16/97 7:36p Samir
 * In editor mode, when switching screen modes, make sure we use the game
 * window specified in gameeditor.cpp (should move this code to
 * gameditor.cpp)
 *
 * 27    10/16/97 4:52p Samir
 * Sped up stats text display.
 *
 * 26    10/16/97 2:32p Samir
 * Fixed up some timing problems.
 *
 * 25    10/14/97 6:53p Chris
 * Added the initial SOAR support
 *
 * 24    10/13/97 10:16a Samir
 * Added some more result-screen stats.
 *
 * 23    10/10/97 3:56p Samir
 * Added a cockpit mode selection function.
 *
 * 22    10/08/97 6:35p Samir
 * Resets player physics when starting new ship.
 *
 * 21    10/03/97 11:58a Samir
 * Added stats screen.
 *
 * 20    10/02/97 12:36p Samir
 * Redid game sequencing flow.
 *
 * 19    9/22/97 6:18p Matt
 * Removed include of stub.h
 *
 * 18    9/17/97 4:20p Samir
 * Don't reinit screen when sarting a new level, unless we specify so.
 *
 * 17    9/17/97 4:14p Jason
 * fixed frametime bug
 *
 * 16    9/17/97 1:22p Samir
 * BIG SEGMENT RIPOUT
 *
 * 15    9/12/97 4:08p Samir
 * Cleaned up screen mode changing.
 *
 * 14    9/10/97 1:55p Samir
 * Initialize script at start of each level
 *
 * 13    9/05/97 3:53p Samir
 * Fixed some more initial player stats.
 *
 * 12    9/05/97 2:37p Samir
 * Some more default values for player object set in InitThisLevel
 *
 * 11    9/05/97 1:21p Samir
 * Moved around a bunch of initialization code to InitThisLevel which is
 * located in game.cpp.   This is called every time you die, start a
 * level, etc.
 *
 * 10    8/12/97 1:13p Chris
 * Added AABBs.
 *
 * 9     8/11/97 7:16p Chris
 * BOA now works on rooms :)
 *
 * 8     8/11/97 5:55p Chris
 * Got rid of a Chrishack.  :)  Added MakeBoa in a correct manner.
 *
 * 7     7/24/97 10:38a Samir
 * When we change screen modes, we set the mouse bounds to the screen
 * size.
 *
 * 6     7/17/97 4:34p Chris
 * Made sure the orientations get orthagonalized.  Yikes.  No more
 * degenerating orientations.  :)
 *
 * 5     7/15/97 7:29p Chris
 * Added a sound for helicopter blades.
 *
 * 4     7/15/97 5:35p Chris
 * New AI code
 *
 * 23    6/16/97 2:34p Jason
 * added 3dfx support
 *
 * 22    6/13/97 11:24a Samir
 * Changes to 2d implemented.
 *
 * 21    6/13/97 11:19a Jason
 * checked in for samir
 *
 * 20    6/11/97 2:24p Samir
 * Changed gameos to new system
 *
 * 19    6/05/97 6:10p Jason
 * added support for zbuffering and bilinear filtering
 *
 * 18    5/27/97 5:41p Jason
 * added toggling of opengl renderer
 *
 * 17    5/27/97 4:39p Jason
 * changes to support OpenGL
 *
 * 16    5/22/97 4:03p Samir
 * SetScreenMode added.
 *
 * 15    5/19/97 7:02 PM Jeremy
 * added initplayernewship to initgame
 *
 * 14    4/23/97 1:06p Samir
 * Implemented Suspend and Resume Controls as well as newer control system
 *
 * $NoKeywords: $
 */

#include "game.h"
#include "ddvid.h"
#include "ddio.h"
#include "pserror.h"
#include "program.h"
#include "descent.h"
#include "object.h"
#include "trigger.h"
#include "player.h"
#include "slew.h"
#include "controls.h"
#include "renderer.h"
#include "doorway.h"
#include "hud.h"
#include "multi.h"
#include "gamefont.h"
#include "newui.h"
#include "gamesequence.h"
#include "cinematics.h"
#include "SmallViews.h"
#include "Mission.h"
#include "cfile.h"
#include "gameloop.h"
#include "cockpit.h"
#include "game2dll.h"
#include "config.h"
#include "stringtable.h"
#include "ship.h"
#include "pilot.h"
#include "args.h"
#include "gamepath.h"
#include "AIGoal.h"
#include "aipath.h"
#include "dedicated_server.h"
#include "objinfo.h"
#include <string.h>
#include "osiris_share.h"
#include "demofile.h"

#include <NewBitmap.h>

///////////////////////////////////////////////////////////////////////////////
//	Variables

// Vars for game 3D window
int Game_window_x, Game_window_y, Game_window_w, Game_window_h;
int Max_window_w, Max_window_h;

// The game mode we're in (ie multiplayer vs. single, etc)
int Game_mode = 0;

int sound_override_force_field = -1;
int sound_override_glass_breaking = -1;

int force_field_bounce_texture[MAX_FORCE_FIELD_BOUNCE_TEXTURES] = {-1, -1, -1};
float force_field_bounce_multiplier[MAX_FORCE_FIELD_BOUNCE_TEXTURES] = {1.0f, 1.0f, 1.0f};

bool Level_powerups_ignore_wind = false;

// what renderer?
renderer_type PreferredRenderer = RENDERER_OPENGL;

// Rendering options
rendering_state Render_state;
renderer_preferred_state Render_preferred_state;
int Render_preferred_bitdepth;

// How hard is this game?
int Difficulty_level = 0;

#ifdef _DEBUG
int Game_show_sphere = 0;
int Game_show_portal_vis_pnts = 0;
int Game_update_attach = 1;
int Game_do_walking_sim = 1;
int Game_do_vis_sim = 1;
int Game_do_flying_sim = 1;
int Game_do_ai_movement = 1;
int Game_do_ai_vis = 1;
#endif

//	How much of the mine has been explored?
int Num_rooms_explored = 0;

//	Save and restores per level
int Num_player_saves = 0;
int Num_player_restores = 0;

// Missile camera
int Missile_camera_window = SVW_LEFT; // will default to -1 when interface is in

//	contains all relevent information for gamemode pertaining to d3x system.
gamemode Gamemode_info;

///////////////////////////////////////////////////////////////////////////////
//	Game setup
///////////////////////////////////////////////////////////////////////////////

bool InitGameScript();
void CloseGameScript();

float GetFPS() {
  if (Frametime == 0.0f) {
    Frametime = 0.1f;
  }
  return 1.0 / Frametime;
}

///////////////////////////////////////////////////////////////////////////////
//	Game Execution
///////////////////////////////////////////////////////////////////////////////

// Setup the game screen
void InitGameScreen(int w, int h) {
  if (w > Max_window_w)
    w = Max_window_w;
  if (h > Max_window_h)
    h = Max_window_h;

  Game_window_w = w;
  Game_window_h = h;

  Game_window_x = (Max_window_w - Game_window_w) / 2;
  Game_window_y = (Max_window_h - Game_window_h) / 2;
}

// Setup whatever needs to be setup for game mode
bool InitGame() {
#ifdef _DEBUG
  // Put player in flying mode
  SlewStop(Player_object);
#endif

  InitHUD();

  if (!InitGameScript()) // initializes game script
    return false;

  Frametime = 0.1f;
  Skip_render_game_frame = false;

  // reset controllers.
  Controller->mask_controllers((Current_pilot.read_controller & READF_JOY) ? true : false,
                               (Current_pilot.read_controller & READF_MOUSE) ? true : false);

  return true;
}

#ifdef EDITOR
bool Game_being_played_from_quick_play = false;
void QuickPlayGame() {
  if (InitGame()) {
    Game_being_played_from_quick_play = true;
    QuickStartMission();

    //	Run the game (note, if this call returns false, we couldn't play a level. Display an error maybe?
    GameSequencer();
    QuickEndMission();
  } else {
  }
  Game_being_played_from_quick_play = false;

  //	Close down some game stuff
  //	close down any systems not needed outside game.
  CloseGameScript();
  CloseHUD();
  DoorwayDeactivateAll(); // deactivate doorways
  ui_RemoveAllWindows();  // remove any ui windows left open.
  SuspendControls();
}
#endif

void PlayGame() {
  //	Initialize misc game
  if (InitGame()) {
    //	Run the game (note, if this call returns false, we couldn't play a level. Display an error maybe?
    GameSequencer();
  } else {
    SetFunctionMode(MENU_MODE);

    // if they were going into a multiplayer game than we need to handle cleaning all that up
    if (Game_mode & GM_MULTI) {
      SetGameMode(GM_NORMAL);
      for (int i = 0; i < MAX_PLAYERS; i++) {
        NetPlayers[i].flags &= ~NPF_CONNECTED;
      }
    }
  }

  //	Close down some game stuff
  //	close down any systems not needed outside game.

  // we must pop the pages before closing the mission, since we need to have the mn3 hog file open
  mng_ClearAddonTables();

  ResetMission();
  CloseGameScript();
  CloseHUD();
  // DoorwayDeactivateAll();		// deactivate doorways
  ui_RemoveAllWindows(); // remove any ui windows left open.
  SuspendControls();
}

///////////////////////////////////////////////////////////////////////////////
// Sets the game mode.  this will reinitialize the game mode script.
///////////////////////////////////////////////////////////////////////////////

void SetGamemodeScript(const char *scrfilename, int num_teams) {
  if (scrfilename != NULL)
    strcpy(Gamemode_info.scriptname, scrfilename);
  else
    Gamemode_info.scriptname[0] = 0;
  Gamemode_info.requested_num_teams = num_teams;
}

void RenderBlankScreen(void);
bool InitGameScript() {
  //	initialize gamemode script here.
  if (Gamemode_info.scriptname[0]) {
    //@@		char d3xname[255];
    char dllname[255];

    snprintf(dllname, sizeof(dllname), "%s", Gamemode_info.scriptname);

    if (!LoadGameDLL(dllname, Gamemode_info.requested_num_teams)) {
      if (!Dedicated_server) {
        void (*old_callback)();
        old_callback = GetUICallback();
        SetUICallback(RenderBlankScreen);
        ShowProgressScreen(TXT_LOADMODULEERR);
        DoMessageBox(TXT_ERROR, TXT_INITMODULEERR, MSGBOX_OK);
        SetUICallback(old_callback);
      }
      return false;
    }
  }
  return true;
}

void CloseGameScript() {
  //	free any gamemode info.
  FreeGameDLL();
}

//	call this to set the game mode
void SetGameMode(int mode) {
  //	do any gamemode specific code here.

  Game_mode = mode;
}

///////////////////////////////////////////////////////////////////////////////
//	Sets screen mode
///////////////////////////////////////////////////////////////////////////////

static int Screen_mode = SM_NULL;

int GetScreenMode() { return Screen_mode; }

//	use to sync to debug break handlers
int rend_initted = 0;
int Low_vidmem = 0;

void SetScreenMode(int sm, bool force_res_change) {
  static int old_sm = SM_NULL;
  static int rend_width = 0, rend_height = 0;
  rendering_state rs;

  if (sm == SM_CINEMATIC) {
    // force cinematic to menu
    sm = SM_MENU;
  }

  if (Dedicated_server)
    return;

  if (old_sm == sm && !force_res_change)
    return;

  //	close down any systems previously opened and that must be closed (like software->hardware, etc.)
  //	make sure renderer is initialized
  //	also set any preferred renderer states.
  if (sm == SM_NULL) { // || (sm == SM_CINEMATIC && Renderer_type == RENDERER_OPENGL)) {
    if (rend_initted) {
      rend_Close();
      rend_initted = 0;
    }
  } else if (sm == SM_CINEMATIC) { // && (Renderer_type == RENDERER_OPENGL || Renderer_type == RENDERER_DIRECT3D)) {
    if (rend_initted) {
      rend_Close();
      rend_initted = 0;
    }
  }
  // #ifdef RELEASE
  //	else if (sm == SM_CINEMATIC && (Renderer_type == RENDERER_GLIDE) ) {
  //		if (rend_initted) {
  //			rend_Close();
  //			rend_initted = 0;
  //		}
  //	}
  // #endif
  else {
    int scr_width, scr_height, scr_bitdepth;

    if (sm == SM_GAME) {
      scr_width = Video_res_list[Game_video_resolution].width;
      scr_height = Video_res_list[Game_video_resolution].height;
      scr_bitdepth = Render_preferred_bitdepth;
    } else {
      scr_width = FIXED_SCREEN_WIDTH;
      scr_height = FIXED_SCREEN_HEIGHT;
      scr_bitdepth = 32;
    }

    if (!rend_initted) {

      Render_preferred_state.width = scr_width;
      Render_preferred_state.height = scr_height;
      Render_preferred_state.bit_depth = scr_bitdepth;

      rend_initted = rend_Init(PreferredRenderer, Descent, &Render_preferred_state);
      rend_width = rend_height = 0;
    } else {

      // If bitdepth changed but not initting, switch bitdepth
      if (Render_preferred_state.bit_depth != scr_bitdepth) {
        Render_preferred_state.bit_depth = scr_bitdepth;
        rend_SetPreferredState(&Render_preferred_state);
      }
    }

    if (!rend_initted) {
      Error(rend_GetErrorMessage());
    } else {
      int t = FindArg("-ForceStateLimited");
      if (t) {
        StateLimited = (atoi((const char *)GameArgs[t + 1]) != 0);
      }

      if (rend_initted == -1) {
        // We're using the default, so change some values for the menus
        rend_initted = 1;
        mprintf(0, "Changing menu settings to default!\n");
        Game_video_resolution = RES_640X480;
        Render_preferred_state.bit_depth = 32;
        scr_width = 640;
        scr_height = 480;
      }

      if (rend_width != scr_width || rend_height != scr_height) {
        Render_preferred_state.width = scr_width;
        Render_preferred_state.height = scr_height;
        Render_preferred_state.bit_depth = scr_bitdepth;

        mprintf(0, "Setting rend_width=%d height=%d\n", scr_width, scr_height);
        int retval = rend_SetPreferredState(&Render_preferred_state);

        if (retval == -1) {
          // We're using the default, so change some values for the menus
          rend_initted = 1;
          mprintf(0, "Changing menu settings to default!\n");
          Game_video_resolution = RES_640X480;
          Render_preferred_state.bit_depth = 32;
          scr_width = 640;
          scr_height = 480;
          Render_preferred_state.width = scr_width;
          Render_preferred_state.height = scr_height;
        }
      }
    }
  }

  if (rend_initted) {
    // Get the amount of video memory
    Low_vidmem = rend_LowVidMem();

    if (FindArg("-hividmem"))
      Low_vidmem = 0;

    //	get current render width and height.
    rend_GetRenderState(&rs);
    rend_width = rs.screen_width;
    rend_height = rs.screen_height;

    //	sets up the screen resolution for the system
    if (!UseHardware) {
      ddvid_SetVideoMode(rend_width, rend_height, BPP_16, true);
    } else {
      if (PreferredRenderer == RENDERER_OPENGL) {
        ddvid_SetVideoMode(rend_width, rend_height, BPP_16, false);
      }
    }

    //	chose font.
    SelectHUDFont(rend_width);

    // Setup the screen
    Max_window_w = rend_width;
    Max_window_h = rend_height;

    InitGameScreen(Max_window_w, Max_window_h);

    //	initialize ui system again
    ui_SetScreenMode(Max_window_w, Max_window_h);

    mprintf(0, "rend_width=%d height=%d\n", Max_window_w, Max_window_h);
  }

  //	assign current screen mode
  Screen_mode = sm;
  old_sm = sm;

  //	Adjust mouse mapping to current screen
  //	do screen mode stuff
  switch (sm) {
  case SM_GAME: {
    ui_HideCursor();
    SetUICallback(NULL);
    int gw, gh;
    Current_pilot.get_hud_data(NULL, NULL, NULL, &gw, &gh);
    if (force_res_change) {
      gw = Max_window_w;
      gh = Max_window_h;
    }
    InitGameScreen(gw, gh);
    // need to do this since the pilot w,h could change.
    Current_pilot.set_hud_data(NULL, NULL, NULL, &Game_window_w, &Game_window_h);
    break;
  }

  case SM_MENU: {
    //	sets up the menu screen
    SetUICallback(DEFAULT_UICALLBACK);
    ui_ShowCursor();
    break;
  }

  case SM_CINEMATIC: {
    SetMovieProperties(0, 0, FIXED_SCREEN_WIDTH, FIXED_SCREEN_HEIGHT, (rend_initted) ? Renderer_type : RENDERER_NONE);
    break;
  }

  case SM_NULL: {
    //	cleans up
    return;
  }
  }

  mprintf(0, "NEW rend_width=%d height=%d\n", Max_window_w, Max_window_h);

  //	mark res change as false.

#ifdef EDITOR
  extern unsigned hGameWnd;
  //	HACK!!! In editor, to get things working fine, reassert window handle attached to game screen
  //	is the topmost window, since in the editor, if we're fullscreen the parent window is still
  //	the editor window, the screen would belong to the editor window.
  tLnxAppInfo appinfo;
  Descent->get_info(&appinfo);
  // LGT - Disabled: not using ddvid
  // ddvid_SetVideoHandle(hGameWnd);
#endif
}

//	These functions are called to start and end a rendering frame
struct tFrameStackFrame {
  int x1, x2, y1, y2;
  bool clear;
  tFrameStackFrame *next;
  tFrameStackFrame *prev;
};
tFrameStackFrame *FrameStackRoot = NULL;
tFrameStackFrame *FrameStackPtr = NULL;
tFrameStackFrame FrameStack[8];
int FrameStackDepth = 0;

void FramePush(int x1, int y1, int x2, int y2, bool clear) {
  tFrameStackFrame *curr = FrameStackPtr;

  if (!curr) {
    ASSERT(!FrameStackRoot);

    // we need to allocate for the root
    //		curr = FrameStackRoot = FrameStackPtr = (tFrameStackFrame *)mem_malloc(sizeof(tFrameStackFrame));
    curr = FrameStackRoot = FrameStackPtr = &FrameStack[0];
    if (!curr) {
      Error("Out of memory\n");
    }

    curr->prev = NULL;
    curr->next = NULL;
  } else {
    // add on to the end of the list
    curr->next = FrameStackPtr = &FrameStack[FrameStackDepth];
    //		curr->next = FrameStackPtr = (tFrameStackFrame *)mem_malloc(sizeof(tFrameStackFrame));
    if (!curr->next) {
      Error("Out of memory\n");
    }
    curr->next->prev = curr; // setup previous frame
    curr = curr->next;
    curr->next = NULL;
  }

  // at this point curr should be a valid frame, with prev and next set
  curr->x1 = x1;
  curr->x2 = x2;
  curr->y1 = y1;
  curr->y2 = y2;
  curr->clear = clear;
  FrameStackDepth++;
  // DAJ
  if (FrameStackDepth > 7) {
    mprintf(2, "FrameStack Overflow\n");
    Int3();
  }
}

void FramePop(int *x1, int *y1, int *x2, int *y2, bool *clear) {
  if (!FrameStackRoot || !FrameStackPtr) {
    mprintf(0, "StartFrame/EndFrame mismatch\n");
    Int3();
    *clear = true;
    *x1 = Game_window_x;
    *y1 = Game_window_y;
    *x2 = *x1 + Game_window_w;
    *y2 = *y1 + Game_window_h;
    return;
  }

  tFrameStackFrame *frame = FrameStackPtr;

  *x1 = FrameStackPtr->x1;
  *x2 = FrameStackPtr->x2;
  *y1 = FrameStackPtr->y1;
  *y2 = FrameStackPtr->y2;
  *clear = FrameStackPtr->clear;

  if (frame == FrameStackRoot) {
    // we're popping off the root
    // DAJ		mem_free(FrameStackRoot);
    FrameStackRoot = NULL;
    FrameStackPtr = NULL;
  } else {
    // we're just going back a frame, but still have a stack
    FrameStackPtr = FrameStackPtr->prev; // pop back a frame
    FrameStackPtr->next = NULL;
    // DAJ		mem_free(frame);
  }
  FrameStackDepth--;
}

// peeks at the current frame
// returns false if there is no current frame
bool FramePeek(int *x1, int *y1, int *x2, int *y2, bool *clear) {
  if (!FrameStackPtr)
    return false;

  *x1 = FrameStackPtr->x1;
  *x2 = FrameStackPtr->x2;
  *y1 = FrameStackPtr->y1;
  *y2 = FrameStackPtr->y2;
  *clear = FrameStackPtr->clear;
  return true;
}

void StartFrame(bool clear) {
  StartFrame(Game_window_x, Game_window_y, Game_window_x + Game_window_w, Game_window_y + Game_window_h, clear);
}

void StartFrame(int x, int y, int x2, int y2, bool clear, bool push_on_stack) {
  static float last_fov = -1;
  // Check to see if our FOV has changed since last frame
  if (last_fov != Render_FOV) {
    // Figure out new zoom factor
    float num = (Render_FOV / 2);
    num = (3.14 * (float)num / 180.0);
    Render_zoom = tan(num);

    last_fov = Render_FOV;
  }

  if (push_on_stack) {
    // push this frame onto the stack
    FramePush(x, y, x2, y2, clear);
  }

  rend_StartFrame(x, y, x2, y2);

  grtext_SetParameters(0, 0, (x2 - x), (y2 - y));
}

// retrives the settings of the last call to StartFrame
bool GetFrameParameters(int *x1, int *y1, int *x2, int *y2) {
  return false;
  /*
  if(!Frame_inside)
          return false;
  *x1 = Frame_x1;
  *y1 = Frame_y1;
  *x2 = Frame_x2;
  *y2 = Frame_y2;
  return true;
  */
}

void EndFrame() {
  //@@Frame_inside = false;
  rend_EndFrame();

  // pop off frame
  int x1, x2, y1, y2;
  bool clear;

  FramePop(&x1, &y1, &x2, &y2, &clear); // pop off frame just ending

  // see if there is a frame on the stack...if so, restore it's settings
  if (FramePeek(&x1, &y1, &x2, &y2, &clear)) {
    // restore this frame
    StartFrame(x1, y1, x2, y2, clear, false);
  }
}

// Does a screenshot and tells the bitmap lib to save out the picture as a tga
void DoScreenshot() {
  int count;
  char str[255], filename[255];
  CFILE *infile;
  int done = 0;
  int width = 640, height = 480;

  if (UseHardware) {
    rendering_state rs;
    rend_GetRenderState(&rs);
    width = rs.screen_width;
    height = rs.screen_height;
  }

  StopTime();

  // Tell our renderer lib to take a screen shot
  auto screenshot = rend_Screenshot();

  if (!screenshot || screenshot->getData() == nullptr) {
    AddHUDMessage(TXT_ERRSCRNSHT);
    return;
  }

  // Find a valid filename
  count = 1;
  while (!done) {
    snprintf(str, sizeof(str), "Screenshot%.3d.png", count);
    ddio_MakePath(filename, Base_directory, str, NULL);
    infile = (CFILE *)cfopen(filename, "rb");
    if (infile == NULL) {
      done = 1;
      continue;
    } else
      cfclose(infile);

    count++;
    if (count > 999)
      break;
  }

  // Now save it
  screenshot->saveAsPNG(filename);

  if (Demo_flags != DF_PLAYBACK) {
    AddHUDMessage(TXT_SCRNSHT, filename);
  }

  StartTime();
}
