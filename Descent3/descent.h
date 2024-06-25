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

 * $Logfile: /DescentIII/main/descent.h $
 * $Revision: 33 $
 * $Date: 11/04/99 12:35a $
 * $Author: Chris $
 *
 * Descent 3 header file
 *
 * $Log: /DescentIII/main/descent.h $
 *
 * 33    11/04/99 12:35a Chris
 * Added support for Merc
 *
 * 32    10/21/99 3:27p Matt
 * Mac merge
 *
 * 31    7/20/99 12:59p Jason
 * added auto katmai support
 *
 * 30    5/12/99 2:24p Jeff
 * Descent3 now has a setable temp directory for all temp files
 *
 * 29    4/14/99 3:56a Jeff
 * fixed case mismatch in #includes
 *
 * 28    3/31/99 3:04p Jeff
 * added _real_ temporary credits system...
 *
 * 27    3/19/99 4:30p Kevin
 * multi-cd support
 *
 * 26    2/16/99 12:36a Kevin
 * Fixes for release builds of OEM V3 and KAtmai
 *
 * 25    2/03/99 4:40p Kevin
 * Added new port number for OEM
 *
 * 24    1/15/99 7:16p Kevin
 * Added GameGauge Configuration & code
 *
 * 23    12/23/98 6:38p Kevin
 * All UDP data (except gamespy) now uses one (registered) port number
 *
 * 22    10/18/98 8:55p Matt
 * Added a constant with the name of the program.
 *
 * 21    10/16/98 1:54p Kevin
 * Changes for Demo Beta 4
 *
 * 20    10/08/98 7:26p Samir
 * changed the prototype for the defer handler callback.
 *
 * 19    10/08/98 12:00p Kevin
 * Demo system work
 *
 * 18    9/22/98 3:54p Samir
 * no include slew in release version.
 *
 * 17    9/15/98 4:31p Jason
 * added more functionality for the dedicated server
 *
 * 16    8/20/98 10:51a Samir
 * added the RESTORE_GAME_MODE function mode,.
 *
 * 15    8/15/98 5:16p Matt
 * Added new Base_directory variable.  Got rid of D3_LOCAL check and
 * 'local directory' registry variable.
 *
 * 14    7/02/98 12:57p Jason
 * upped FOV
 *
 * 13    4/22/98 3:24p Jason
 * made FOV be 65 degrees by default
 *
 * 12    4/14/98 7:56p Matt
 * Moved MSN_NAMELEN from mission.h to descent,h, so multi.h didn't need
 * to include mission.h.
 *
 * 11    3/23/98 8:06p Samir
 * change return type of D3DeferHandler to match changes in library.
 *
 * 10    3/19/98 11:27a Samir
 * Better error checking.
 *
 * 9     3/10/98 5:16p Samir
 * Got debug callbacks working when you hit an Int3.
 *
 * 8     2/25/98 2:05p Jason
 * did FOV and object visibility changes
 *
 * 7     10/16/97 2:30p Samir
 * Added defer handler.
 *
 * 6     9/17/97 10:56a Matt
 * Deleted Room_engine variable
 *
 * 5     9/16/97 1:04p Samir
 * Added delay function.
 *
 * 4     7/24/97 6:35p Matt
 * Created symbolic constant for default zoom, and used it every place
 * that specifies zoom
 *
 * 3     7/24/97 2:53p Matt
 * Added SourceSafe header and missing include
 *
 * $NoKeywords: $
 */

#ifndef _DESCENT_H
#define _DESCENT_H

#include <stdlib.h>
#include "application.h"

// The name of this product
#ifdef DEMO
#define PRODUCT_NAME "Descent 3 Demo"
#else
#define PRODUCT_NAME "Descent 3"
#endif

// This is the port number assigned to "descent3" by the IANA (Internet Assigned Numbers Authority)
// Don't arbitrarily change this number!
#ifdef OEM
// The port used for the OEM version isn't a legitimate IANA port number
#define D3_DEFAULT_PORT 2092
#else
#define D3_DEFAULT_PORT 2092
#endif

class grScreen;
class oeApplication;
class oeAppDatabase;
class grViewport;

//	---------------------------------------------------------------------------
//	Constants and Types

enum function_mode {
  INIT_MODE,
  GAME_MODE,
  RESTORE_GAME_MODE,
  EDITOR_MODE,
  EDITOR_GAME_MODE,
  MENU_MODE,
  QUIT_MODE,
  LOADDEMO_MODE,
  GAMEGAUGE_MODE, // Unused
  CREDITS_MODE
};

extern bool Descent_overrided_intro;

// This is the default FOV
#define D3_DEFAULT_FOV 72.0
// This is the default zoom factor to be used for the game 3D view.
#define D3_DEFAULT_ZOOM 0.726f

// How long the a mission name can be
#define MSN_NAMELEN 32

// The "root" directory of the D3 file tree
extern char Base_directory[];

//	---------------------------------------------------------------------------
//	Globals

extern grScreen *Game_screen;                   // The Descent 3 screen.
extern oeApplication *Descent;                  // The Descent object
extern oeAppDatabase *Database;                 // The Database
extern char Descent3_temp_directory[_MAX_PATH]; // temp directory to put temp files
extern bool Katmai;                             // whether or not katmai is detected
//	---------------------------------------------------------------------------
//	Functions

#ifdef EDITOR
void WinMainInitEditor(unsigned hwnd, unsigned hinst);
#endif

//	Runs Descent III
void Descent3();

//	Runs the game, or editor
void MainLoop();

//	the defer handler
void D3DeferHandler(bool is_active);

//	Set and retrieve the current function mode of Descent 3
void SetFunctionMode(function_mode mode);
function_mode GetFunctionMode();

//	these functions create viewports from the game screen in a 'nice' C way
void CreateGameViewport(grViewport **vp);
void DestroyGameViewport(grViewport *vp);

inline void CREATE_VIEWPORT(grViewport **vp) { CreateGameViewport(vp); }

inline void DESTROY_VIEWPORT(grViewport *vp) { DestroyGameViewport(vp); }

inline void DELAY(float secs) { Descent->delay(secs); }

#ifndef RELEASE
//	this is called when you hit a debug break!
void D3DebugStopHandler();
void D3DebugResumeHandler();
#endif

#endif
