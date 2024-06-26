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

 * $Logfile: /DescentIII/Main/editor/gameeditor.cpp $
 * $Revision: 1.1.1.1 $
 * $Date: 2003-08-26 03:57:38 $
 * $Author: kevinb $
 *
 * Game to editor/editor to Game interface
 *
 * $Log: not supported by cvs2svn $
 *
 * 103   9/24/99 12:01p Samir
 * use directinput when -alternatejoy is selected (like 1.0)
 *
 * 102   8/18/99 12:05p 3dsmax
 * Joystick fix (from Samir)
 *
 * 101   4/29/99 10:01p Samir
 * use emulation mode of joystick first.
 *
 * 100   4/26/99 9:11p Matt
 * Use small font instead of old UI font.
 *
 * 99    4/09/99 12:02p Samir
 * joystick changes (Win32 DirectInput support)
 *
 * 98    3/27/99 7:22p Jeff
 * fixed cinematics when going from one cut to another immediatly.  Added
 * start transition
 *
 * 97    3/04/99 6:09p Samir
 * initialize slowkey for game.
 *
 * 96    2/27/99 6:24p Sean
 * may fix sequencing problems with rendering windows going in and out of
 * editor.
 *
 * 95    2/20/99 3:43a Jeff
 * removed useless call to free pilot mission data
 *
 * 94    2/15/99 7:47p Jeff
 * new pilot file class and read/write system checked in...should be more
 * robust than old
 *
 * 93    2/11/99 7:24p Nate
 * Added hiding of Dallas when going into game, and restoring of Dallas
 * when returning to editor
 *
 * 92    2/10/99 3:44p Dan
 * pause editor while reloading level
 *
 * 91    2/01/99 10:35a Matt
 * Fixed the initial player position in the game when playing from the
 * editor.
 *
 * 90    1/25/99 6:47p Samir
 * allow slow keyboard
 *
 * 89    1/25/99 11:02a Samir
 * revamped mouse and key controls.
 *
 * 88    1/22/99 3:19p Jason
 * added 256x256 textures to help with terrain skies
 *
 * 87    1/19/99 12:14p Matt
 * Fixed problem if there was no player object when coming back from the
 * game
 *
 * 86    1/15/99 7:52p Chris
 * Updated ObjSetPos() to include a f_update_attach_children flag
 *
 * 85    1/11/99 11:12a Jeff
 * handle untitled levels and scripts
 *
 * 84    1/08/99 2:56p Samir
 * Ripped out OSIRIS1.
 *
 * 83    1/07/99 12:28p Samir
 * Call to InitD3Music added parameter.
 *
 * 82    12/31/98 7:33p Jeff
 * reset osiris timers when going editor->game
 *
 * 81    12/17/98 12:08p Jeff
 * first checkin of new implementation of OSIRIS (old OSIRIS no longer
 * works)
 *
 * 80    12/15/98 4:29p Jeff
 * reset pilot mission data when we go to load in a pilot
 *
 * 79    11/13/98 2:28p Samir
 * new music system.
 *
 * 78    11/06/98 12:45p Chris
 *
 * 77    11/03/98 6:43p Jeff
 * new low-level & high level Force Feedback system implemented, handles
 * window losing focus, etc.
 *
 * 76    11/02/98 6:15p Chris
 * Room AABBs get saved with the level and the sort_face and dec_sort_face
 * list s have been removed
 *
 * 75    10/15/98 1:36p Jeff
 * handle the case where the default pilot gets deleted...forcing  a new
 * pilot to be made
 *
 * 74    10/13/98 3:14p Samir
 * maybe hacked temp fix to one editor restore window problem that keeps
 * coming up but NEVER happens/happened on my machine under 95 or NT.
 *
 * 73    9/30/98 10:25a Jason
 * another attempt to the get the OpenGL window thing working reliably...
 *
 * 72    9/29/98 6:22p Samir
 * this may fix things.
 *
 * 71    9/24/98 1:13p Samir
 * maybe fix weird editor problem.
 *
 * 70    9/22/98 10:32a Jason
 * made preferred renderer default to OpenGL
 *
 * 69    9/18/98 7:38p Jeff
 * creation of low-level forcefeedback and beginning of high-level
 * forcefeedback
 *
 * 68    9/18/98 2:55p Matt
 * Fixed bug resetting viewer position when returning to the editor after
 * playing from the main menu.
 *
 * 67    9/18/98 1:27p Jason
 * cleaned up renderer initting
 *
 * 66    9/08/98 3:25p Matt
 * Fixed, hopefully, problems with getting the the player position &
 * orientation back to the editor when playing from the editor.
 *
 * 65    8/25/98 11:37p Matt
 * Fixed (I think) problem setting the viewer from the player when going
 * from the game to the editor after the player has been deleted.
 *
 * 64    8/15/98 5:16p Matt
 * Added new Base_directory variable.  Got rid of D3_LOCAL check and
 * 'local directory' registry variable.
 *
 * 63    8/07/98 2:44p Jeff
 * reset player ship permissions  when going game->editor
 *
 * 62    7/28/98 5:40p Samir
 * music init and close within editor.
 *
 * 61    7/08/98 6:27p Samir
 * stream library integrated with highlevel sound system.
 *
 * 60    7/01/98 4:59p Samir
 * set mouse mode when entering and leaving game.
 *
 * 59    6/30/98 4:20p Samir
 * added ddio_Close as standalone.   ddio_Init will no longer close
 * itself.
 *
 * 58    6/29/98 6:43p Samir
 * IO system initializes using Descent object always (especially for
 * fullscreen debug!)
 *
 * 57    6/22/98 12:00p Chris
 * Working on sound system to make it in a nice shape.
 *
 * 56    6/16/98 3:48p Chris
 * Updated the sound system and added the start of sound streaming
 *
 * 55    6/12/98 5:09p Samir
 * resize window later.
 *
 * 54    5/11/98 4:40p Chris
 * AI info is now a malloc'ed pointer
 *
 * 53    5/06/98 4:32p Samir
 * moved ui init back to it's proper place.
 *
 * 52    5/05/98 5:16p Samir
 * took out calls to init UI system (that's done now in SetScreenMode)
 *
 * 51    5/01/98 1:54p Jeff
 * sound lib inits before mainmenu when going editor->game
 *
 * 50    4/21/98 2:29p Matt
 * Added mprintf()s
 *
 * 49    3/20/98 1:20p Jeff
 * Save/restore Default_pilot when switching from game<->editor
 *
 * 48    3/19/98 11:27a Samir
 * Better error checking.
 *
 * 47    3/13/98 5:04p Jason
 * fixed problem with preferred renderer
 *
 * 46    3/13/98 1:22p Jason
 * Moved UseHardware flag to the renderer lib where it belongs
 *
 * 45    3/12/98 9:16p Matt
 * When going from the game to the editor, only copy the player's position
 * to the viewer if was playing directly from the editor, and not if went
 * from the editor to the main menu.
 *
 * 44    3/10/98 5:16p Samir
 * Got debug callbacks working when you hit an Int3.
 *
 * 43    3/10/98 12:50p Samir
 * Initialize NewUI system at startup.
 *
 * 42    3/06/98 2:22p Samir
 * Added fullscreen windowed version.
 *
 * 41    3/05/98 6:39p Samir
 * Initialize ui system with UI_FONT
 *
 * 40    2/26/98 1:00p Samir
 * Hopefully keystrokes only reach the game.
 *
 * 39    2/23/98 6:48p Samir
 * Make sure to initialize new window objects.
 *
 * 38    2/11/98 5:55p Samir
 * Now InitD3XDebug and CloseD3XDebug are called when you enter and leave
 * the game.  This as well as ui_Init and ui_Close
 *
 * 37    2/05/98 2:57p Matt
 * Changed code to use ObjSetPos()
 *
 * 36    2/04/98 6:09p Matt
 * Changed object room number to indicate a terrain cell via a flag.  Got
 * rid of the object flag which used to indicate terrain.
 *
 * 35    1/06/98 2:44p Jason
 * another pass for multiplayer
 *
 * 34    1/06/98 1:26p Matt
 * Cleaned up interfaces to rendering routines, deleted unused code, etc.
 *
 * 33    1/02/98 6:39p Matt
 * Got rid of Render_viewport
 *
 * 32    1/02/98 5:29p Samir
 * Set PROGRAM(editor) to 0 when going to game, and 1 when in editor.
 *
 * 31    1/02/98 5:32p Chris
 * More radical changes to the sound system
 *
 * 30    12/29/97 5:46p Samir
 * Implemented new video and font changes
 *
 * 29    12/19/97 12:21p Jason
 * changes for 2d/3d integration
 *
 * 28    12/19/97 11:25a Samir
 * g3_StartFrame and g3_EndFrame replaced by EditorStartFrame and
 * EditorEndFrame
 *
 * 27    12/18/97 3:49p Jason
 * a new first pass at networking!
 *
 * 26    11/05/97 3:45p Samir
 * After ddio_Init, recall InitControls.
 *
 * 25    10/17/97 5:43p Samir
 * Hopefully this fixes things.
 *
 * 24    10/17/97 5:26p Samir
 * Move window after screen res change.
 *
 * 23    10/17/97 5:18p Samir
 * ddio_Init now does mouse opening and closing, where it should be.
 *
 * 22    10/17/97 4:26p Samir
 * More modifications for debug mode.
 *
 * 21    10/17/97 3:14p Samir
 * Hopefully when debugging, you can get back into debugger.
 *
 * 20    10/16/97 7:35p Samir
 * For fullscreen game from editor, hide all user interface elements of
 * the editor window and use the client area for our display. It's REALLY
 * hacked, but seems to be the cleanest method of playing the game in
 * fullscreen.  Old method of blanking window doesn't work.
 *
 * 19    10/16/97 4:41p Samir
 * Don't set game window to be active.  It fucks something up under NT
 * (and only happens in the editor.)
 *
 * 18    10/16/97 2:31p Samir
 * Reinitialize ddio library when going into game.
 *
 * 17    10/02/97 12:35p Samir
 * Free script when loading in GameSave.d3l.
 *
 * 16    9/05/97 1:25p Samir
 * Moved some code to InitThisLevel for game initialization.
 *
 * 15    8/26/97 11:38a Samir
 * Added Editor_active global to determine whether editor is currently
 * active (useful for any window using the gr library.)
 *
 * 14    8/22/97 5:09p Jason
 * save/restore game editor view when appropriate
 *
 * 13    8/12/97 1:13p Chris
 * Added AABBs.
 *
 * 12    8/11/97 5:55p Chris
 * Got rid of a Chrishack.  :)  Added MakeBoa in a correct manner.
 *
 * 11    8/01/97 11:59a Samir
 * Added a preference for debugging in fullscreen.
 *
 * 10    7/25/97 12:02p Samir
 * Funky window resizings gone because we're using the GDI-DirectX
 * graphics system for running the game.
 *
 * 9     7/24/97 6:34p Jeff
 * Turned on mouse by default
 *
 * 8     7/22/97 7:07p Matt
 * Cleaned up D3EditState, moving some vars in and some out, and renaming
 * and changing a few others
 *
 * 7     7/15/97 4:57p Mark
 * Corrected usage of UseHardware flag
 *
 * 41    6/16/97 4:46p Samir
 * OpenGL works in window too.
 *
 * 40    6/16/97 2:34p Jason
 * added 3dfx support
 *
 * 39    6/13/97 4:11p Jason
 * took out redundant call to rend_Close
 *
 * 38    6/12/97 6:35p Samir
 * Implented new changes to GR system
 *
 * 37    6/11/97 2:40p Samir
 * Adjusted to new gameos system.
 *
 * 36    6/09/97 4:15p Samir
 * Hide cursor while in game.
 *
 * 35    5/29/97 3:25p Chris
 *
 * 34    5/27/97 7:23p Matt
 * Fixed (hopefully for real this time) the same problem I tried to fix
 * last time.
 *
 * 33    5/27/97 5:41p Jason
 * added toggling of opengl renderer
 *
 * 32    5/27/97 5:22p Matt
 * Fixed editor->game->editor code to save & load gamesave.d3l in same
 * directory.
 *
 * 31    5/27/97 4:39p Jason
 * changes to support OpenGL
 *
 * 30    5/22/97 4:03p Samir
 * HACK!  Assigned hOpenGLWnd.
 *
 * 29    5/16/97 3:40p Matt
 * When going from game->editor, only copy player to viewer if the levels
 * are the same, which we determine by checking the mission name & level
 * number (though I think it would be better to check the filename.)
 *
 * 28    5/15/97 5:14p Matt
 * When going from game to editor, set terrain/mine editing based on where
 * the player is
 *
 * 27    5/15/97 3:20p Samir
 * Fixed problem with editor being show during gameplay.
 *
 * 26    5/15/97 2:07p Samir
 * minimize editor when going from editor to game.
 *
 * 25    5/15/97 1:59a Chris
 *
 * 24    5/06/97 4:11p Matt
 * Fixed a bunch of code that deals with the player and viewer objects
 * when going between the game and editor.
 *
 * 23    5/06/97 1:17p Jason
 * checked in for matt
 *
 * 22    5/01/97 6:08p Matt
 * When switching between editor & game, save & load level to temp file.
 *
 * 21    4/24/97 1:33p Chris
 * Sound initializations are all now editor friendly.  Fullscreen,
 * windowed, and editor.
 *
 * 20    4/23/97 6:06p Jason
 * made player ship and weapons work correctly together (first pass)
 *
 * 19    4/03/97 8:37p Chris
 * Added the Main_OS object pass in the sound library
 * initialization code.
 *
 * 18    4/03/97 5:45p Jason
 * make player/viewer object switch flags if over terrain
 *
 * 17    4/01/97 11:00p Matt
 * Changed editor to keep a viewer object (type camera) seperate from the
 * player object.  This camera, and not the player, is now moved by
 * slewing, the C key, etc.  When going into the game, the viewer position
 * & orientation are copied to the player.  When going back to the editor,
 * the player position is copied to the viewer, and the player object is
 * reset to its start location.
 *
 * 16    3/31/97 1:23p Samir
 * Fixed problem when going to fullscreen mode when last mode was GDI,
 * which then caused a crash.  Fixed this by moving graphics and sound
 * initialization to after new window is created and processed.
 *
 * 15    3/28/97 11:46a Chris
 * Make sound code use editor's window handle
 *
 * 14    3/27/97 10:48a Chris
 * Removed some bad code
 *
 * 13    3/17/97 5:12p Chris
 * Allowed new sound code to be demo'ed.
 *
 * 12    3/17/97 11:54a Chris
 * Forced a valid mass and drag (hack).  But, I did use chrishack so I
 * will remove it later.  This fixes the problem with imported D2 levels
 * have invalid player data.
 *
 * 11    3/12/97 6:31p Chris
 * Added player flight controls while in game
 *
 * 10    2/28/97 11:03a Samir
 * Changes to reflect newer gameos interface.
 *
 * 9     2/11/97 3:48p Samir
 * Added ddio.h
 *
 * 8     2/11/97 2:45p Samir
 * flushed keyboard when entering or leaving game from editor.
 *
 * 7     2/05/97 12:17p Samir
 * Set window size for both fullscreen and windowed versions.
 *
 * 6     2/04/97 6:23p Samir
 * Don't make windowed game window topmost.
 *
 * 5     2/04/97 5:33p Samir
 * Always assert EDITOR_MODE when leaving MainLoop.
 *
 * 4     2/04/97 5:25p Samir
 * Support entering either menu or game from editor.
 *
 * 3     1/30/97 6:43p Samir
 * stupid forgetting an argument
 *
 * 2     1/30/97 6:21p Samir
 * New gameos.h implementation
 *
 * $NoKeywords: $
 */

#include "stdafx.h"
#include "editor.h"
#include "MainFrm.h"

#include "ui.h"
#include "render.h"
#include "pserror.h"
#include "gr.h"
#include "mono.h"
#include "init.h"
#include "game.h"
#include "descent.h"
#include "Application.h"
#include "AppDatabase.h"
#include "program.h"
#include "ddio.h"
#include "object.h"
#include "slew.h"
#include "hlsoundlib.h" //chrishack
#include "ds3dlib.h"    // chrishack
#include "HView.h"
#include "player.h"
#include "loadlevel.h"
#include "renderer.h"
#include "BOA.h"
//@@#include "d3x.h"
//@@#include "d3xdebug.h"
#include "ObjScript.h"
#include "controls.h"
#include "multi.h"
#include "3d.h"
#include "ddvid.h"
#include "gamefont.h"
#include "newui.h"
#include "pilot.h"
#include "streamaudio.h"
#include "D3ForceFeedback.h"
#include "d3music.h"
#include "osiris_dll.h"
#include "d3edit.h"
#include "editordoc.h"
#include "args.h"
#include "terrain.h"
#include "mem.h"
#include "DallasMainDlg.h"
#include "gamecinematics.h"

//	---------------------------------------------------------------------------
//	local globals
//	---------------------------------------------------------------------------
static oeApplication *Saved_editor_app = NULL; // the editor's app object
static char Editor_dir[_MAX_PATH];             // old editor directory
static RECT Editor_wndrect;                    // editor window rect.
unsigned hGameWnd;                             // used for hack. window handle to draw to.
static HMENU hEditorMenu;
static DWORD EditorWndStyle;
static DWORD EditorBackBrush;
static WINDOWPLACEMENT EditorWndPlacement;

static bool Temp_level_saved = 0; // do we have a current temp level saved?
extern bool Disable_editor_rendering;

int Just_returned_from_game = 0;
float Just_returned_time;

//	---------------------------------------------------------------------------
//	Prototypes internal
//	---------------------------------------------------------------------------

void GameToEditor(bool); // deinit game, reinit editor
void EditorToGame();     // deinit editor, reinit game

void InitGameEditSystems();
void InitEditGameSystems();

void DeswInitMainWindow(HINSTANCE hinst);
void DeswCloseMainWindow();

LRESULT WINAPI DescentWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

//	---------------------------------------------------------------------------
//	Function mode switching functions
//	---------------------------------------------------------------------------

void RunGameFromEditor() {
  int game_mode = GetFunctionMode(); // save the mode we're going to (menu or editor_game)
  renderer_type old_rend = PreferredRenderer;

  //	Run the damn game
  mprintf(0, "Entering the game...\n");

  Editor_active = false;
  PROGRAM(editor) = 0;
  if (PROGRAM(windowed))
    PreferredRenderer = RENDERER_OPENGL;

  EditorToGame();
  MainLoop();
  GameToEditor(game_mode == EDITOR_GAME_MODE); // if was playing from editor, copy player pos to viewer
  PROGRAM(editor) = 1;
  PreferredRenderer = old_rend;
  Editor_active = true;
  SetFunctionMode(EDITOR_MODE); // ASSERT WE ARE IN EDITOR MODE!

  mprintf(0, "Returning to editor...\n");
}

// Vars for getting the viewer position back from the game to the editor
vector editor_player_pos;
matrix editor_player_orient;
int editor_player_roomnum;

uint16_t *Save_sky_data = NULL;

void GameToEditor(bool set_viewer_from_player) {
  /*	We have to reinitialize the DDGR system for windowed mode.
          This will annihilate all previous DDGR settings.
  */
  Cinematic_Close();

  ddio_init_info io_info;

  theApp.pause();
  // Sleep to prevent race conditions with the display drivers
  Sleep(2000);

  // Close down whatever renderer we were using and restore the software renderer
  rend_Init(RENDERER_OPENGL, Saved_editor_app, NULL);

  if (Game_screen)
    delete Game_screen;

  // Restore saved game if one exists
  if (Temp_level_saved) {
    char filename[_MAX_PATH];

    ddio_MakePath(filename, Base_directory, "GameSave.D3L", NULL); // make explicit path
    LoadLevel(filename);
    Temp_level_saved = 0;
  }

  // if no player vars back from the game, use the viewer from the file
  if (editor_player_roomnum == -1) {
    set_viewer_from_player = 0;
    editor_player_roomnum = Player_object->roomnum;
  }

  // Set editor to mine or terrain mode based on current player position
  Editor_view_mode = ROOMNUM_OUTSIDE(editor_player_roomnum) ? VM_TERRAIN : VM_MINE;

  // Make sure there's a viewer object
  SetEditorViewer();

  // Move the viewer to the player's (pre-restore) position, if wasn't playing from the editor
  if (set_viewer_from_player)
    ObjSetPos(Viewer_object, &editor_player_pos, editor_player_roomnum, &editor_player_orient, false);

  //	Reset previous working directory
  ddio_SetWorkingDir(Editor_dir);

  //	close down video system only!
  ddvid_Close();

  ASSERT((OBJECT_OUTSIDE(Viewer_object) != 0) == (Editor_view_mode == VM_TERRAIN));

  SlewStop(Viewer_object);

  // Close forcefeedback
  ForceClose();

  //	restore Current OS object.
  ddio_Close();
  CloseD3Music();

  if (PROGRAM(windowed)) {
    //	reinitialize IO system for editor
    delete Descent;
    Descent = Saved_editor_app;
    io_info.obj = Descent;
  } else if (D3EditState.fullscreen_debug_state) {
    //	reinitialize IO system for editor
    delete Descent;
    Descent = Saved_editor_app;
    io_info.obj = Descent;

    theApp.main_frame->SetMenu(CMenu::FromHandle(hEditorMenu));
  } else {
    Descent = Saved_editor_app;
    io_info.obj = Descent;
    theApp.main_frame->SetMenu(CMenu::FromHandle(hEditorMenu));
    SetClassLong(theApp.main_frame->m_hWnd, GCL_HBRBACKGROUND, EditorBackBrush);
    SetWindowLong(theApp.main_frame->m_hWnd, GWL_STYLE, EditorWndStyle);
  }

  //	this uses information defined above
  io_info.key_emulation = true; //(bool)(FindArg("-slowkey")!=0);
  io_info.joy_emulation = (bool)((FindArg("-alternatejoy") == 0) && (FindArg("-directinput") == 0));

  ddio_Init(&io_info);

  Cinematic_Init();

  // Init force feedback effects
  ForceInit();

  //	This line is needed to disable OpenGL for ddgr
  if (!ddgr_Init(Descent, "GDI32", false)) {
    Error("Graphics initialization failed.\n");
  }

  //	theApp.main_frame->SetWindowPos(&CWnd::wndNoTopMost, Editor_wndrect.left, Editor_wndrect.top,
  //										Editor_wndrect.right-Editor_wndrect.left,
  //										Editor_wndrect.bottom -
  //Editor_wndrect.top, 										SWP_SHOWWINDOW);

  // Restore sky if possible
  if (Save_sky_data) {
    int dome_bm = Terrain_sky.dome_texture;
    if (bm_w(dome_bm, 0) != 256) {
      // It was changed during rendering
      bm_ChangeSize(dome_bm, 256, 256);
      uint16_t *dest_data = (uint16_t *)bm_data(dome_bm, 0);
      memcpy(dest_data, Save_sky_data, 256 * 256 * 2);
    }

    mem_free(Save_sky_data);
    Save_sky_data = NULL;
  }

  //	initialize systems back to editor.
  InitGameEditSystems();
  theApp.resume();

  // If Dallas is running, restore it to where it was
  if (theApp.m_DallasModelessDlgPtr != NULL)
    theApp.m_DallasModelessDlgPtr->ShowWindow(SW_SHOWNA);

  Disable_editor_rendering = false;
}

char Editor_quickplay_levelname[_MAX_PATH];

void EditorToGame() {
  Disable_editor_rendering = true;

  // Hide Dallas (if it's running) so it doesn't get any keypresses
  if (theApp.m_DallasModelessDlgPtr != NULL)
    theApp.m_DallasModelessDlgPtr->ShowWindow(SW_HIDE);

  /*	Create a new window and display it.  Initialize a new GameOS Object and use this
          for our game
  */
  tLnxAppInfo app_info;
  bool paged = true;
  char subsystem[8];
  ddio_init_info io_info;

  // Save the sky in case it gets changed
  int dome_bm = GetTextureBitmap(Terrain_sky.dome_texture, 0);
  if (bm_w(dome_bm, 0) == 256) {
    Save_sky_data = (uint16_t *)mem_malloc(256 * 256 * 2);
    ASSERT(Save_sky_data);

    uint16_t *src_data = bm_data(dome_bm, 0);
    memcpy(Save_sky_data, src_data, 256 * 256 * 2);
  }

  /*	We have to reinitialize the DDGR system for full screen mode.
          This will annihilate all previous DDGR settings.
  */

  //	theApp.main_frame->ShowWindow(SW_SHOWMINNOACTIVE);

  //	set game working directory
  bool set_size = false;
  ddio_GetWorkingDir(Editor_dir, sizeof(Editor_dir));
  ddio_SetWorkingDir(Base_directory);

  Osiris_ResetAllTimers();

  //	continue
  SlewStop(Viewer_object);

  // Save the player positions
  FindPlayerStarts();

  // Save the level to restore when go back to editor
  mprintf(0, "Make temp copy of level...");
  SaveLevel("GameSave.D3L");
  mprintf(0, "done\n");
  Temp_level_saved = 1; // say that we have a level saved

  // Save the viewer position for the game to use
  editor_player_pos = Viewer_object->pos;
  editor_player_orient = Viewer_object->orient;
  editor_player_roomnum = Viewer_object->roomnum;

  // Set up the player
  SetObjectControlType(Player_object, CT_FLYING); // don't think we really need this
  Viewer_object = Player_object;

  //	create a new OS object, hence a new window (The Descent III window)
  unsigned flags;

  Saved_editor_app = Descent;
  Saved_editor_app->get_info(&app_info);
  theApp.main_frame->GetWindowRect(&Editor_wndrect);

  //	close down ddgr system only.
  ddgr_Close();

  if (PROGRAM(windowed))
    strcpy(subsystem, "GDI");
  else if (Renderer_type == RENDERER_OPENGL)
    strcpy(subsystem, "GDIF");
  else
    strcpy(subsystem, "GDIX");

  if (theApp.main_doc) {
    CString path = theApp.main_doc->GetPathName();
    strcpy(Editor_quickplay_levelname, path.GetBuffer(0));
    if (Editor_quickplay_levelname[0] == '\0')
      strcpy(Editor_quickplay_levelname, "Untitled.d3l");
  } else {
    strcpy(Editor_quickplay_levelname, "Untitled.d3l");
  }

  // close forcefeedback
  ForceClose();

  //	occurs after io initialization
  ddio_Close();
  CloseD3Music();

  //	create window and start game.
  if (PROGRAM(windowed)) {
    flags = OEAPP_WINDOWED;
    Descent = new oeLnxApplication(flags);
    Descent->init();
    set_size = true;
    Descent->get_info(&app_info);
    // TODO: retrieve hwnd from SDL window handle
    // hGameWnd = app_info.hwnd;
    // SetForegroundWindow((HWND)hGameWnd);
    Saved_editor_app->defer();
    Descent->defer();

    //	Initialize graphics and sound this must be done after initialization of new window and
    //	after deferring to OS.
    if (!ddvid_Init(Descent, subsystem))
      Error("Graphics initialization failed.\n");
  } else if (D3EditState.fullscreen_debug_state) {
    CMenu *menu = theApp.main_frame->GetMenu();

    hEditorMenu = menu->m_hMenu;
    theApp.main_frame->SetMenu(NULL);

    flags = OEAPP_FULLSCREEN;
    Descent = new oeLnxApplication(flags);
    Descent->init();
    set_size = true;
    Descent->get_info(&app_info);
    // TODO: get hwnd from SDL Window
    // hGameWnd = app_info.hwnd;
    // SetForegroundWindow((HWND)hGameWnd);
    Saved_editor_app->defer();
    Descent->defer();

    //	Initialize graphics and sound this must be done after initialization of new window and
    //	after deferring to OS.
    if (!ddvid_Init(Saved_editor_app, subsystem))
      Error("Graphics initialization failed.\n");

    //	force application to think it's active.
    SetActiveWindow((HWND)hGameWnd);
    //	Descent->activate();
  } else {
    CMenu *menu = theApp.main_frame->GetMenu();

    hGameWnd = (unsigned)theApp.main_frame->m_hWnd;
    hEditorMenu = menu->m_hMenu;
    theApp.main_frame->SetMenu(NULL);
    EditorWndStyle = GetWindowLong(theApp.main_frame->m_hWnd, GWL_STYLE);
    EditorBackBrush = GetClassLong(theApp.main_frame->m_hWnd, GCL_HBRBACKGROUND);
    SetWindowLong(theApp.main_frame->m_hWnd, GWL_STYLE, EditorWndStyle & ~(WS_CAPTION | WS_THICKFRAME | WS_BORDER));
    SetClassLong(theApp.main_frame->m_hWnd, GCL_HBRBACKGROUND, (DWORD)GetStockObject(HOLLOW_BRUSH));

    //	Initialize graphics and sound this must be done after initialization of new window and
    //	after deferring to OS.
    if (!ddvid_Init(Descent, subsystem))
      Error("Graphics initialization failed.\n");
  }

  //	Initialize IO System for child window
  io_info.obj = Descent;
  io_info.key_emulation = true; //(bool)(FindArg("-slowkey")!=0);
  io_info.joy_emulation = (bool)((FindArg("-alternatejoy") == 0) && (FindArg("-directinput") == 0));
  ddio_Init(&io_info);

  // Init force feedback
  ForceInit();

  //	Create game screen and clear it.
  ddvid_SetVideoHandle(hGameWnd);

  //	Initialize everything else.
  InitEditGameSystems();

  //	maybe we should CLEAR HERE
  if (set_size) {
    ((oeLnxApplication *)Descent)->set_sizepos(0, 0, 640, 480);
  }

  Just_returned_from_game = 1;
  Just_returned_time = timer_GetTime();

  //	if (D3EditState.fullscreen_debug_state)
  //		theApp.main_frame->MoveWindow(-50,-50,20,20);
}

void InitEditGameSystems() {
  tUIInitInfo uiinit;
#if defined(RELEASE)
  SetDebugBreakHandlers(NULL, NULL);
#else
  SetDebugBreakHandlers(D3DebugStopHandler, D3DebugResumeHandler);
#endif

  Descent->set_defer_handler(D3DeferHandler);

  LoadAllFonts();
  InitControls();
  ddio_KeyFlush();
  ddio_MouseMode(MOUSE_EXCLUSIVE_MODE);

  // Sound initialization
  InitD3Music(FindArg("-nomusic") ? false : true);
  Sound_system.InitSoundLib(Descent, Sound_mixer, Sound_quality, false);

  //	UI init.
  uiinit.window_font = SMALL_FONT;
  uiinit.w = 640;
  uiinit.h = 480;
  ui_Init(Descent, &uiinit);
  ui_UseCursor("StdCursor.ogf");

  NewUIInit();

  // Load up the pilot selected by default
  if (cfexist(Default_pilot)) {
    mprintf(0, "Loading up Default Pilot: %s\n", Default_pilot);
    Current_pilot.set_filename(Default_pilot);
    PltReadFile(&Current_pilot, true, true);
  } else {
    strcpy(Default_pilot, " ");
    Current_pilot.set_filename("");
  }
}

void InitGameEditSystems() {
  // UnLoad the pilot and fill in the default
  char p_fname[_MAX_FNAME];

  Current_pilot.get_filename(p_fname);
  if (p_fname[0] != '\0')
    strcpy(Default_pilot, p_fname);
  else
    strcpy(Default_pilot, " ");

  // reset ship permissions
  PlayerResetShipPermissions(-1, true);

  CloseControls();
  ddio_KeyFlush();
  ddio_MouseMode(MOUSE_STANDARD_MODE);

  // Sound initialization for editor
  InitD3Music(FindArg("-nomusic") ? false : true);
  Sound_system.InitSoundLib(Descent, Sound_mixer, Sound_quality, false);

  NewUIClose();
  ui_Close();

  SetDebugBreakHandlers(NULL, NULL);
}

//	THESE FUNCTIONS DEAL WITH INTERFACING EDITOR AND GAME 3D system

static grViewport *Editor_g3_vp = NULL;

void StartEditorFrame(grViewport *vp, vector *viewer_eye, matrix *viewer_orient, float zoom) {
  grSurface *surf;

  ASSERT(vp != NULL);

  Editor_g3_vp = vp;
  surf = Editor_g3_vp->lock();
  if (!surf)
    Int3(); // This surface should be locked.  bad?

  rend_StartFrame(0, 0, surf->width(), surf->height());
  g3_StartFrame(viewer_eye, viewer_orient, zoom);
}

void EndEditorFrame() {
  Editor_g3_vp->unlock();
  Editor_g3_vp = NULL;
  g3_EndFrame();
  rend_EndFrame();
}
