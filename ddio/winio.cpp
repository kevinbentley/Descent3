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

 * $Logfile: /DescentIII/Main/ddio_win/winio.cpp $
 * $Revision: 17 $
 * $Date: 7/09/01 1:55p $
 * $Author: Matt $
 *
 * <insert description of file here>
 *
 * $Log: /DescentIII/Main/ddio_win/winio.cpp $
 *
 * 17    7/09/01 1:55p Matt
 * Try opening DX5 for NT so force feedback will work.
 *
 * 16    4/09/99 12:02p Samir
 * joystick changes (Win32 DirectInput support)
 *
 * 15    1/25/99 11:02a Samir
 * revamped mouse and key controls.
 *
 * 14    11/18/98 5:50p Jeff
 * free up force feedback before unloading DI
 *
 * 13    11/03/98 6:43p Jeff
 * new low-level & high level Force Feedback system implemented, handles
 * window losing focus, etc.
 *
 * 12    11/01/98 1:58a Jeff
 * converted the vsprintf calls to use the Pvsprintf, which is a safe
 * vsprintf, no buffer overflows allowed
 *
 * 11    10/18/98 6:18p Matt
 * Turn the pointer on when shutting down.  This fixes a problem where you
 * couldn't click Ok on an error message box because the pointer was off
 * for our app.
 *
 * 10    9/18/98 7:38p Jeff
 * creation of low-level forcefeedback and beginning of high-level
 * forcefeedback
 *
 * 9     9/15/98 12:25p Jeff
 * If we are in NT, then only require DX3, else require DX6 (we may need
 * to change this due to NT5)
 *
 * 8     9/15/98 12:05p Jeff
 * initial creation of low-level forcefeedback
 *
 * 7     6/29/98 6:43p Samir
 * Took out GetMsgProc and legacy keyboard variables.
 *
 * 6     5/08/98 12:54p Samir
 * newer unused mouse handler.
 *
 * 5     3/31/98 12:46p Samir
 * keyboard IO system better.  uses getmsgproc windows hook.
 *
 * 4     10/23/97 2:58p Samir
 * Took out extranneous messages.
 *
 * 3     10/16/97 2:29p Samir
 * Changed DirectInput Keyboard to FOREGROUND
 *
 * 2     8/01/97 7:30p Samir
 * Better NT keyboard support.
 *
 * 10    6/11/97 1:07p Samir
 * The removal of gameos and replaced with oeApplication, oeDatabase
 *
 * 9     5/08/97 1:56p Samir
 * These functions should only be applicable to windows (no shared code)
 *
 * 8     3/18/97 11:14a Samir
 * Use real error call when DirectInput init fails.
 *
 * 7     2/28/97 11:03a Samir
 * Changes to reflect newer gameos interface.
 *
 * 6     1/30/97 6:08p Samir
 * Reflects changes in gameos.h
 *
 * 5     1/23/97 2:23p Samir
 * Preemptive flag now just affects timer.
 *
 * $NoKeywords: $
 */

// ----------------------------------------------------------------------------
// Win32 IO System Main Library Interface
// ----------------------------------------------------------------------------

#include <cstdarg>
#include <cstdio>

#include <stdlib.h>
#include <windows.h>

#include "pserror.h"
#include "winapp.h"
#include "ddio_win.h"
#include "ddio.h"
#include "dinput.h"

#include "forcefeedback.h"

bool DDIO_init = 0;
dinput_data DInputData;

// ----------------------------------------------------------------------------
//	Initialization and destruction functions
// ----------------------------------------------------------------------------

bool ddio_InternalInit(ddio_init_info *init_info) {
  LPDIRECTINPUT lpdi;
  HRESULT dires;

  ASSERT(!DDIO_init);

  //	Initialize DirectInput subsystem
  mprintf(0, "DI system initializing.\n");

  // Try to open DirectX 5.00
  dires = DirectInputCreate(Win32App()->instance(), DIRECTINPUT_VERSION, &lpdi, NULL);

  // Deal with error opening DX5
  if (dires != DI_OK) {

    // If running NT, try DirectX 3.0
    if (Win32App()->NT()) {

      dires = DirectInputCreate(Win32App()->instance(), 0x0300, &lpdi, NULL);
      if (dires != DI_OK) {
        Error("Unable to DirectInput system (Requires at least DirectX 3.0 For NT) [DirectInput:%x]\n", dires);
      }
    } else { // Not running NT, so error out

      // Couldn't open DirectX, so print error
      Error("Unable to DirectInput system (Requires at least DirectX 5.0) [DirectInput:%x]\n", dires);
    }
  }

  DInputData.lpdi = lpdi;
  DInputData.hwnd = Win32App()->windowHandle();

  DDIO_init = 1;

  return 1;
}

void ddio_InternalClose() {
  ASSERT(DDIO_init);

  //	//Close down forcefeedback
  //	ddio_ff_DetachForce();

  DInputData.lpdi->Release();
  DInputData.lpdi = NULL;
  DDIO_init = 0;

  mprintf(0, "DI system closed.\n");
}

#ifdef _DEBUG
void ddio_DebugMessage(unsigned err, char *fmt, ...) {
  char buf[128];
  std::va_list arglist;

  va_start(arglist, fmt);
  std::vsnprintf(buf, 128, fmt, arglist);
  va_end(arglist);

  mprintf(0, "DDIO: %s\n", buf);
  if (err) {
    mprintf(1, "DIERR %x.\n", err);
  }
}
#endif

bool ddio_GetBinaryPath(char *exec_path, size_t len) {
  if (GetModuleFileName(NULL, exec_path, len) == 0) {
   DWORD error = GetLastError();
   Error("GetModuleFileName failed!");
   return false;
  }
 exec_path[len - 1] = '\0';
 return true;
}
